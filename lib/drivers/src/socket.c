#include "../include/socket.h"

int getInitSocket(SocketDataLink *structDataLinkSocket, GlobalDataLink *structDataLink) {

    structDataLinkSocket->to.sin_family = 0;
    structDataLinkSocket->to.sin_port = 0;  
    
    structDataLinkSocket->tosize = sizeof structDataLinkSocket->to;
    structDataLinkSocket->hostinfo = NULL;
    structDataLinkSocket->hostname = IP_HOST;


    structDataLinkSocket->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (structDataLinkSocket->sock == INVALID_SOCKET) {
        perror("socket()");
        return errno;
    }

    structDataLinkSocket->hostinfo = gethostbyname(structDataLinkSocket->hostname);
    if (structDataLinkSocket->hostinfo == NULL) {
        fprintf(stderr, "Unknown host %s.\n", structDataLinkSocket->hostname);
        return EXIT_FAILURE;
    }

    structDataLinkSocket->to.sin_addr = *(IN_ADDR *) structDataLinkSocket->hostinfo->h_addr;
    structDataLinkSocket->to.sin_port = htons(PORT);
    structDataLinkSocket->to.sin_family = AF_INET;

    return EXIT_SUCCESS;
}

int sendDataBySocket(SocketDataLink *structDataLinkSocket, GlobalDataLink *structDataLink) {

    return EXIT_SUCCESS;
}