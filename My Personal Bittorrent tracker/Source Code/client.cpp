#include "client.h"

// Called on control-C or kill. To handle inappropriate program termination. 
void clean_exit(int b)
{
	shutdown(server.socket, 2);
	close(server.socket);
	pthread_mutex_lock( &my_mutex );
	for (map<string, peer*>::iterator it = peer_list.begin(); it != peer_list.end(); it++)
	{
		if (it->second != NULL)
		{
			shutdown(it->second->socket, 2);
			close(it->second->socket);
		}
	}
	pthread_mutex_unlock( &my_mutex );
	exit(0);     
}


// Return the file only if its name is not "." and ".."
static int filter_file (const struct dirent *entry)
{
	if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
		return false;
	else
		return true;
}


// Return the file if it is found in directory
static int check_file (const struct dirent *entry)
{
	if ((strcmp(entry->d_name, request_file_name.c_str()) == 0))
		return true;
	else
		return false;
}


// Tokenize and catogorize incoming message.
void tokenize (peer *temp, char *incoming)
{
	char *pch = strtok (incoming, "#");
	
	// Process UPDATE file.
	if (strcmp(pch, "UPDATE") == 0)
	{
		temp->files.clear();
		temp->neighbours.clear();
		while (pch != NULL)	
		{
			pch = strtok (NULL, "#");
			if (pch == NULL)
				break;
			
			if (strcmp(pch, "NEIGHBOUR") == 0)
				break;
			else
				temp->files.push_back(pch);
		}
		while (pch != NULL)	
		{
			pch = strtok (NULL, "#");
			if (pch == NULL)
				break;
			temp->neighbours.push_back(pch);
		}
	}

	else if (strcmp(pch, "OUTFILE") == 0)
	{
		pch = strtok (NULL, "#");
		string f = pch;
		fstream in;
		string input = "INFILE#" + f + "#";
		string s;
		in.open(pch);
		
		if (in.fail())
			send(temp->socket, "-1", 2, 0);
		while (getline(in, s))
			input = input + s + "\n";
		
		in.close();
		send(temp->socket, input.c_str(), input.size(), 0);
	}
	
	else if (strcmp(pch, "INFILE") == 0)
	{
		pch = strtok (NULL, "#");
		string file = pch;
		ofstream out;
		out.open(pch);
		if (out.fail())
			cout << "Cannot download file. Try again later." << endl;;
		pch = strtok (NULL, "");
		out << pch;
		out.close();
	}
	temp->status = true;
}


// Combine the current hold files to 1 string. 
string posses_files(peer *temp)
{
	// Scan the current directory to get files.
	struct dirent **eps;
	int n = scandir (".", &eps, filter_file, alphasort);
	
	if (n >= 1)
	{
		// Concatenate all the file name to become 1 string.
		string input = "";
		for (int cnt = 0; cnt < n; ++cnt) 
		{
			input = input + eps[cnt]->d_name + "#";
	        free(eps[cnt]);
		}
		free(eps);
		return input;
	}
	
	else if (n == 0)
	{
		cout << "No file found!" << endl;
		return "-1";
	}
	
	else
	{
		cout << "Couldn't open the directory" << endl;
		return "-1";
	}
}


// For displaying list of peer.
void display_peer_table ()
{
	cout << endl << "                         List of Peers" << endl;
	cout << "+-----------------+-------------------------+-----------------+" << endl;
	cout << "| Peer IP         | File List               | Neighbours      |" << endl;
	cout << "+-----------------+-------------------------+-----------------+" << endl;
	for (map<string,peer*>::iterator it = peer_list.begin(); it != peer_list.end(); it++)
	{
		cout << "| " << setw(15) << left << (*it).first << " |";
								
		int s;
		if (it->second->neighbours.size() >= it->second->files.size())
			s = it->second->neighbours.size();
		else
			s = it->second->files.size();
		
		if (s == 0)
			cout << "                         |                 |" << endl;
		
		else
		{
			
			for (int i = 0; i < s; i++)
			{
				if (i != 0)
					cout << "|                 |";
				if ( i >= it->second->files.size())
					cout << "                         |";
				
				if (i < it->second->files.size())
					cout << " " << setw(24) << it->second->files[i] << "|";
				if (i < it->second->neighbours.size())
					cout << " " << setw(16) << it->second->neighbours[i] << "|";
				else
					cout << "                 |";
				cout << endl;
			}
		}
		cout << "+-----------------+-------------------------+-----------------+" << endl;
	}
}


// Request file from neighbour or server.
void *request_file (void *arg)
{ 
	peer *temp = (peer *)arg;
	
	peer *temp1;
	pthread_t tid;
	
	while (1)
	{
		//system("clear");
		cout << "What you wish to do?" << endl;
		cout << "1. Request a file." << endl;
		cout << "2. Leave." << endl;
		
		char a;
		cin >> a;
		cin.ignore(10000, '\n');
		
		if (a == '1')
		{
			cout << "Please type the file name (with extension)." << endl;
			cin >> request_file_name;
			
			// Check whether there is file with same name exists in current directory.
			struct dirent **eps;
			int n = scandir (".", &eps, check_file, alphasort);
			
			// There is file with same name request in current directory.
			if (n >= 1)
			{
				cout << "File with same name exists in the same directory!" << endl;
				cout << "Please rename it if you want to request this file." << endl;
			}
			
			else
			{			
				char incoming[1024];
				bool found = false;
				
				// File found in neighbour.
				pthread_mutex_lock (&my_mutex);
				for (map <string,peer*>::iterator it = peer_list.begin(); it != peer_list.end(); it++)
				{
					for (int i = 0; i < it->second->files.size(); i++)
					{
						if (strcmp(request_file_name.c_str(), it->second->files[i].c_str()) == 0)
						{
							found = true;
 							string input = "OUTFILE#" + request_file_name + "#";
 							send (it->second->socket, input.c_str(), input.size(), 0);
							goto close;
						}
					}
				}
				close:
				pthread_mutex_unlock (&my_mutex);
				
				if (!found)
				{
					// Request file from server.
					string input = "REQUEST#" + request_file_name + "#";
										
					// Send Requested name.
					send(server.socket, input.c_str(), input.size(), 0);
					
					// Receive ip.
					int bytes_received = recv(server.socket, incoming, 1024, 0);
					incoming[bytes_received] = '\0';
					
					// No such file.
					if (strcmp (incoming, "-1") == 0)
						cout << "No peer is sharing this file now. Try again later." << endl;
						
					// Connected to the client who has the file.
					else
					{
						// Connect to the client.
						make_connection(hServerSocket, incoming, PORT, Address);					
							
						// Store necessary information.
						temp1 = new peer;
						temp1->socket = hServerSocket;
						temp1->ip = inet_ntoa(Address.sin_addr);
						
						pthread_mutex_lock( &my_mutex );
						peer_list.insert(pair <string,peer*>(inet_ntoa(Address.sin_addr), temp1));
						pthread_mutex_unlock( &my_mutex );

 						string input = "OUTFILE#" + request_file_name + "#";
 						send(temp1->socket, input.c_str(), input.size(), 0);

						// Create thread to update with the peer periodically.
						pthread_create(&tid, NULL, send_update, temp1);
						pthread_create(&tid, NULL, get_peer_update, temp1);
					}
				}
			}	
		}
		
		else if (a == '2')
		{
			shutdown(server.socket, 2);
			close(server.socket);
			
			pthread_mutex_lock( &my_mutex );
			for (map<string, peer*>::iterator it = peer_list.begin(); it != peer_list.end(); it++)
			{
				if (it->second != NULL)
				{
					shutdown(it->second->socket, 2);
					close(it->second->socket);
				}
			}
			pthread_mutex_unlock( &my_mutex );
			exit(0);
		}
		
		else
			cout << "Invalid input, key in again." << endl;
	}
}


// Regulary update (file list and neighbour list) with server or peer.
void *send_update (void *arg)
{
	peer *temp = (peer*)arg;
	while(1)
	{
		sleep(10);
			
		string n = "UPDATE#";
		
		// Send file list.
		n += posses_files(temp);					
		
		n += "NEIGHBOUR#";
				
		// Send neighbour list.
		pthread_mutex_lock (&my_mutex);		
		for (map <string,peer*>::iterator it = peer_list.begin(); it != peer_list.end(); it++)
				n = n + it->first + "#";
		pthread_mutex_unlock (&my_mutex);
		
		send(temp->socket, n.c_str(), n.size(), 0);	
	}
}


// Received message from each peer.
void *get_peer_update(void *arg) 
{
	peer *temp = (peer *)arg;
	
 	// Waiting for update from peer.
	char incoming[1000000];
 	while (1)
 	{
		// Receive all the message.
		int bytes_received = recv(temp->socket, incoming, 1000000, 0); 
		if (bytes_received <= 0)
		{ 	shutdown(temp->socket, 2);
			close(temp->socket);
			break;}
	
		incoming[bytes_received] = '\0';
		
		// Tokenize incoming message.
		pthread_mutex_lock( &my_mutex );
		tokenize(temp, incoming);
		pthread_mutex_unlock( &my_mutex );
 	}


}


// Reset all peers status.
void *reset_status(void *arg)
{
	while(1)
	{
		vector <string> a;
		sleep(15);
		pthread_mutex_lock( &my_mutex );
		for (map<string,peer*>::iterator it = peer_list.begin(); it != peer_list.end(); it++)
		{		
			// Store the leave peer for later delete.
			if (it->second->status == false)
				a.push_back(it->first);
 			else
 				it->second->status = false;
		}
		for (int i = 0; i < a.size(); i++) 
		{
			map <string,peer*>::iterator it = peer_list.find(a[i]);
			delete it->second;
			it->second = NULL;
			peer_list.erase(it);
		}
		pthread_mutex_unlock( &my_mutex );
		
		pthread_mutex_lock (&my_mutex);
		display_peer_table();
		pthread_mutex_unlock(&my_mutex);
	}
}


// For connecting to others.
void make_connection(int &hServerSocket, char* strHostName, int port, struct sockaddr_in &Address)
{
	hServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(hServerSocket == SOCKET_ERROR)
    {
        cout << "Could not make a socket" << endl;
        exit(0);
    }

    // Get IP address from name
    pHostInfo = gethostbyname(strHostName);
	
    // Copy address into long
    memcpy(&nHostAddress, pHostInfo->h_addr, pHostInfo->h_length);

    // Fill address struct
    Address.sin_addr.s_addr = nHostAddress;
    Address.sin_port = htons(port);
    Address.sin_family = AF_INET;

    cout << "Connecting to " << strHostName << " on port " << port << endl;

	// Connect to host.
	if(connect(hServerSocket, (struct sockaddr*) &Address, sizeof(Address)) == SOCKET_ERROR)
	{
	    cout << "Could not connect to host\n" << endl;
	    exit(0);
	}
}


// For accepting connection from other peers.
void *accept_connection (void *arg)
{
	peer *temp;
	pthread_t id;

	while (1)
    {
    	cout << "Waiting for a connection...\n";		
		hSocket = accept(mySocket, (struct sockaddr *) &Address1,(socklen_t *) &nAddressSize);
		cout << "Peer with IP: " << inet_ntoa(Address1.sin_addr) << " connected." << endl;
		
		// Store necessary information.
		temp = new peer;
		temp->socket = hSocket;
		temp->ip = inet_ntoa(Address1.sin_addr);
		temp->status = true;
		
		pthread_mutex_lock( &my_mutex );
		peer_list.insert(pair <string,peer*>(inet_ntoa(Address1.sin_addr), temp));
		pthread_mutex_unlock( &my_mutex );

		// Create new thread to handle communication between this peer and tracker.
		pthread_create(&id, NULL, get_peer_update, temp);
		pthread_create(&id, NULL, send_update, temp);
	}
}


int main(int argc, char* argv[])
{
	signal(SIGTERM, clean_exit);
	signal(SIGINT, clean_exit);
	system("clear");
	cout << "Please specify the tracker ip address." << endl;
	cin >> strHostName;
	
	pthread_mutex_init( &my_mutex, NULL );
	
	// Connect to tracker.
	make_connection(hServerSocket, strHostName, TRACKER_PORT, Address);
	
	// Create thread to handle request to tracker.
	pthread_t tid;
	server.ip = inet_ntoa(Address.sin_addr);
	server.socket = hServerSocket;
	
	// Receive message from tracker.
	cout << "Connection Established!" << endl;
	
	// Create thread to update with server periodically.
	pthread_create(&tid, NULL, send_update, &server);
	
	// Create thread to handle file request for this peer.
	pthread_create(&tid, NULL, request_file, &server);		
	pthread_create(&tid, NULL, reset_status, NULL);
	
	
	
	// Make a socket for accepting other peer connection.
    mySocket = socket(AF_INET, SOCK_STREAM, 0);

    if(mySocket == SOCKET_ERROR)
    {
        cout << "Could not make a socket." << endl;
        return -1;
    }

    // Fill address struct.
    Address1.sin_addr.s_addr = INADDR_ANY;
    Address1.sin_port = htons(PORT);
    Address1.sin_family = AF_INET;

    // Bind to a port.
    if(bind(mySocket, (struct sockaddr *) &Address1, sizeof(Address1)) == SOCKET_ERROR)
    {
        cout << "Could not connect to port" << endl;
        return -1;
    }

	// Establish listen queue.
    if(listen(mySocket, 11) == SOCKET_ERROR)
    {
        cout << "Could not listen\n";
        return -1;
    }

	// Create a thread for accepting new connection.
	pthread_create(&tid, NULL, accept_connection, NULL);

	pthread_exit(NULL);

	return 0;
}
