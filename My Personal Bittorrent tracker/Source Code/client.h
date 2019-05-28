#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <pthread.h>
#include <map>
#include <dirent.h>
#include <signal.h>
#include <iomanip>
#include <fstream>

using namespace std;

#define SOCKET_ERROR        -1
#define PORT				4444
#define TRACKER_PORT		3333

int hSocket, hServerSocket, mySocket;			// Handle to socket.
struct hostent* pHostInfo;						// Holds info about a machine.
struct sockaddr_in Address, Address1;  			//	 Internet socket address stuct.
long nHostAddress, nHostAddress1;
char strHostName[255];
string request_file_name;						// Store peer request file name.
int nAddressSize = sizeof(struct sockaddr_in);
pthread_mutex_t my_mutex;

struct peer {
	string ip;
	int socket;
	bool status;
	vector<string> files;
	vector<string> neighbours;
}server;

map <string,peer*> peer_list;	
map <string,vector <string> > file_list;

void clean_exit(int b);
static int filter_file (const struct dirent *entry);
static int check_file (const struct dirent *entry);
void tokenize (peer *temp, char *incoming);
string posses_files(peer *temp);
void display_peer_table ();
void *request_file (void *arg);
void *send_update (void *arg);
void *get_peer_update(void *arg);
void *reset_status(void *arg);
void make_connection(int &hServerSocket, char* strHostName, int port, struct sockaddr_in &Address);
void *accept_connection (void *arg);


#endif
