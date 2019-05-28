#ifndef TRACKER_H
#define TRACKER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <map>
#include <iomanip>

using namespace std;

#define SOCKET_ERROR        -1
#define QUEUE_SIZE          5
#define PORT				3333

int hSocket,hServerSocket;  	// handle to socket
struct hostent* pHostInfo;   	// holds info about a machine 
struct sockaddr_in Address; 	// Internet socket address stuct
int nAddressSize = sizeof(struct sockaddr_in);

struct peer {
	string ip;
	int socket;
	bool status;
	vector<string> files;
	vector<string> neighbours;
};

map <string,peer*> peer_list;
map <string, vector <string> > file_list;

pthread_mutex_t my_mutex;

void *accept_connection (void *arg);
void tokenize (peer *temp, char *incoming);
void *get_peer_update(void *arg);
void *reset_status(void *arg);
void display_peer_table ();
void display_file_table();


#endif
