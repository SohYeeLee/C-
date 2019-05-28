#include "tracker.h"

// Accept connection from new nodes.
void *accept_connection (void *arg)
{
	peer *temp;
	pthread_t id;

	while (1)
    {
    	cout << "Waiting for a connection...\n";		
		hSocket = accept(hServerSocket, (struct sockaddr *) &Address,(socklen_t *) &nAddressSize);
		cout << "Peer with IP: " << inet_ntoa(Address.sin_addr) << " connected." << endl;
		
		// Store necessary information.
		temp = new peer;
		temp->socket = hSocket;
		temp->ip = inet_ntoa(Address.sin_addr);
		temp->status = true;
		
		pthread_mutex_lock( &my_mutex );
		peer_list.insert(pair <string,peer*>(inet_ntoa(Address.sin_addr), temp));
		pthread_mutex_unlock( &my_mutex );
		
		// Create new thread to receive update from peer.
		pthread_create(&id, NULL, get_peer_update, temp);
	}
}


// Tokenize and catogorize incoming message.
void tokenize (peer *temp, char *incoming)
{
	char *pch = strtok (incoming, "#");
	
	// Process REQUEST file.
	if (strcmp(pch, "REQUEST") == 0)
	{
		pch = strtok (NULL, "#");
		bool found = false;
		
		for (map <string,peer*>::iterator it = peer_list.begin(); it != peer_list.end(); it++)
		{
			for (int i = 0; i < it->second->files.size(); i++)
			{
				if (strcmp(pch, it->second->files[i].c_str()) == 0)
				{
					found = true;
					
					// Send ip to peer.
					send (temp->socket, it->first.c_str(), it->first.size(), 0);
					goto hell;
				}
			}
		}
		hell:
		if (!found)
			send(temp->socket, "-1", 2, 0);	
	}
	
	// Process UPDATE file.
	else if (strcmp(pch, "UPDATE") == 0)
	{
		temp->neighbours.clear();
		temp->files.clear();
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
	temp->status = true;
}


// Received regulary update from each peer.
void *get_peer_update(void *arg) 
{
	peer *temp = (peer *)arg;
	
 	// Waiting for update from peer.
	char incoming[1000000];
 	while (1)
 	{
		// Receive all the message
		int bytes_received = recv(temp->socket, incoming, 1000000, 0); 
		if (bytes_received <= 0)
			break;
	
		incoming[bytes_received] = '\0';
		
		// Tokenize incoming message.
		pthread_mutex_lock( &my_mutex );
		tokenize(temp, incoming);
		pthread_mutex_unlock( &my_mutex );

 	}
	shutdown (temp->socket, 2) ;
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
		
		// Erase the peer that is already die from map.
		for (int i = 0; i < a.size(); i++) 
		{
			map <string,peer*>::iterator it = peer_list.find(a[i]);
			close(it->second->socket);
			delete it->second;
			it->second = NULL;
			peer_list.erase(it);
		}
		pthread_mutex_unlock( &my_mutex );

		display_peer_table();
		display_file_table();
	}
}


// Display all the peers that are currently connected to tracker.
void display_peer_table ()
{
	pthread_mutex_lock( &my_mutex );
	vector <string> a;
	file_list.clear();
	for (map<string,peer*>::iterator it = peer_list.begin(); it != peer_list.end(); it++)
	{
		for (int i = 0; i < it->second->files.size(); i++)
		{
			map <string, vector <string> >::iterator a = file_list.find(it->second->files[i]);

			// File not exist in the list.
			if (a == file_list.end())
			{
				vector <string> p;
				p.push_back(it->first);
				file_list.insert(pair <string, vector <string> > (it->second->files[i], p));
			}
			else
				a->second.push_back(it->first);		
		}
	}
	pthread_mutex_unlock( &my_mutex );

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


// Display current file and their 
void display_file_table()
{
	cout << endl << "               List of Files" << endl;
	cout << "+------------------+--------------------------+" << endl;
	cout << "| File Name        | IP Address               |" << endl;
	cout << "+------------------+--------------------------+" << endl;
	for (map<string,vector <string> >::iterator it = file_list.begin(); it != file_list.end(); it++)
	{
		cout << "| " << setw(16) << left << (*it).first << " |";
										
		for (int i = 0; i < it->second.size(); i++)
		{
			if (i != 0)
				cout << "|                  |";
			
			cout << " " << setw(25) << it->second[i] << "|";
			cout << endl;
		}
			cout << "+------------------+--------------------------+" << endl;
	}
}


// Main Function.
int main(int argc, char* argv[])
{
	system("clear");

    // Make a socket.
    hServerSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(hServerSocket == SOCKET_ERROR)
    {
        cout << "Could not make a socket." << endl;
        return -1;
    }

    // Fill address struct.
    Address.sin_addr.s_addr = INADDR_ANY;
    Address.sin_port = htons(PORT);
    Address.sin_family = AF_INET;

    // Bind to a port.
    if(bind(hServerSocket, (struct sockaddr *) &Address, sizeof(Address)) == SOCKET_ERROR)
    {
        cout << "Could not connect to port" << endl;
        return -1;
    }

	// Establish listen queue.
    if(listen(hServerSocket, QUEUE_SIZE) == SOCKET_ERROR)
    {
        cout << "Could not listen\n";
        return -1;
    }

	cout << "Tracker started!" << endl;
	pthread_t tid;
	
	pthread_mutex_init( &my_mutex, NULL );
	
	// Create a thread for accepting new connection.
	pthread_create(&tid, NULL, accept_connection, NULL);
	pthread_create(&tid, NULL, reset_status, NULL);
	pthread_exit(NULL);

	return 0;
}
