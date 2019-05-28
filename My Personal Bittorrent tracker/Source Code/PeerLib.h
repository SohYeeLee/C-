#ifndef _PEER_LIB_H_
#define _PEER_LIB_H_
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>

struct PeerInfo {
	int					sockDes;
	struct sockaddr_in	peer;
};


const char*			hostname ( const char* name );
int					connectServer ( const int sockDes, const char* host, const uint16_t port );
int					startServer ( const int sockDes, const uint16_t port );
struct PeerInfo*	acceptConnection ( const int sockDes );
int					closeSocket ( const int sockDes );
int					sendData ( const int sockDes, const char* buff, const size_t size );
int					recvData ( const int sockDes, char* buff );

#endif

