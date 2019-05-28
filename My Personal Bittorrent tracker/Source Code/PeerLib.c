#include <PeerLib.h>

const char* hostname ( const char* name ) {
	struct hostent*	host;
	struct in_addr*	in;
	
	host	= gethostbyname(name);
	if ( host == NULL )
		return "";
	in		= (struct in_addr*) host->h_addr;
	return inet_ntoa(*in);
}

int connectServer ( const int sockDes, const char* host, const uint16_t port ) {
	struct sockaddr_in	name;
	socklen_t			len;
	
	len						= sizeof(struct sockaddr_in);
	name.sin_family			= AF_INET;
	name.sin_addr.s_addr	= inet_addr(host);
	name.sin_port			= htons(port);
	
	return connect(sockDes, (struct sockaddr*) &name, len);
}

int startServer ( const int sockDes, const uint16_t port ) {
	struct sockaddr_in	name;
	socklen_t			len;
	int					queue_size;
	
	queue_size				= 10;
	len						= sizeof(struct sockaddr_in);
	name.sin_family			= AF_INET;
	name.sin_addr.s_addr	= htonl(INADDR_ANY);
	name.sin_port			= htons(port);
	
	if ( bind(sockDes, (struct sockaddr*) &name, len) == -1 ) return -1;
	if ( listen(sockDes, queue_size) == -1 ) return -1;
	
	return 0;
}

struct PeerInfo* acceptConnection ( const int sockDes ) {
	struct PeerInfo*	newpeer;
	socklen_t			len;
	
	newpeer	= (struct PeerInfo*) malloc(sizeof(struct PeerInfo));
	len		= sizeof(struct sockaddr_in);
	if ( (newpeer->sockDes = accept(sockDes, (struct sockaddr*) &(newpeer->peer), &len)) == -1 ) return NULL;
	return newpeer;
}

int closeSocket ( const int sockDes ) {
	/**
	shutdown ( int socket, int how );
	how:
	0	Stop receiving for this socket.
	1	Stop transmiting data from this socket.
	2	Stop both.
	*/
	return shutdown(sockDes, 2);
}

int sendData ( const int sockDes, const char* buff, const size_t size ) {
	return send(sockDes, buff, size, 0);
}

int recvData ( const int sockDes, char* buff ) {
	size_t	len;
	len	= recv(sockDes, buff, 1024, 0);
	buff[len] = '\0';
	return len;
}

