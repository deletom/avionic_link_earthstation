#ifndef SOCKET_H
#define SOCKET_H

//-----------------------------
//----- INCLUDE 	  -----
//-----------------------------
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

//-----------------------------
//----- DEFINE 		  -----
//-----------------------------
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define CRLF  "\r\n"
#define IP_HOST "127.0.0.1"
#define PORT  1977

//-----------------------------
//----- STRUCTURE 	  -----
//-----------------------------
typedef struct SocketDataLink SocketDataLink;

struct SocketDataLink {
    SOCKET sock;
    SOCKADDR_IN to;
    socklen_t tosize;
    struct hostent *hostinfo;
    const char *hostname;
};

typedef struct GlobalDataLink GlobalDataLink;

//-----------------------------
//----- Prototypes 	  -----
//-----------------------------
int getInitSocket(SocketDataLink *structDataLinkSocket, GlobalDataLink *structDataLink);
int sendDataBySocket(SocketDataLink *structDataLinkSocket, GlobalDataLink *structDataLink);


#endif /* SOCKET_H */

