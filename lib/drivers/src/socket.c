#include "../include/socket.h"

/**
 * Initialisation de la connexion via socket
 * @param structDataLinkSerial
 * @param structDataLink
 */
int getInitSocket(SocketDataLink *structDataLinkSocket, GlobalDataLink *structDataLink) {

    structDataLinkSocket->to.sin_family = 0;
    structDataLinkSocket->to.sin_port = 0;

    structDataLinkSocket->tosize = sizeof structDataLinkSocket->to;
    structDataLinkSocket->hostinfo = NULL;
    structDataLinkSocket->hostname = IP_HOST;


    structDataLinkSocket->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (structDataLinkSocket->sock == INVALID_SOCKET) {
        perror("LINK getInitSocket: Socket invalide");
        return EXIT_FAILURE;
    }

    structDataLinkSocket->hostinfo = gethostbyname(structDataLinkSocket->hostname);
    if (structDataLinkSocket->hostinfo == NULL) {
        perror("LINK getInitSocket: Hote inconnu");
        return EXIT_FAILURE;
    }

    structDataLinkSocket->to.sin_addr = *(IN_ADDR *) structDataLinkSocket->hostinfo->h_addr;
    structDataLinkSocket->to.sin_port = htons(PORT);
    structDataLinkSocket->to.sin_family = AF_INET;

    return EXIT_SUCCESS;
}

int sendDataBySocket(SocketDataLink *structDataLinkSocket, GlobalDataLink *structDataLink) {

    while (1) {

        // Envoi HeartBeat
        setDataMavlinkHeartBeat(structDataLink);
        if (sendto(structDataLinkSocket->sock, structDataLink->buffer, structDataLink->len, 0, (SOCKADDR *) & structDataLinkSocket->to, structDataLinkSocket->tosize) < 0) {
            perror("LINK sendDataBySerial: Erreur HeartBeat");
        }

        // Envoi Statut
        setDataMavlinkStatus(structDataLink);
        if (sendto(structDataLinkSocket->sock, structDataLink->buffer, structDataLink->len, 0, (SOCKADDR *) & structDataLinkSocket->to, structDataLinkSocket->tosize) < 0) {
            perror("LINK sendDataBySerial: Erreur Status");
        }

        // Envoi Attitude
        setDataMavlinkAttitude(structDataLink);
        if (sendto(structDataLinkSocket->sock, structDataLink->buffer, structDataLink->len, 0, (SOCKADDR *) & structDataLinkSocket->to, structDataLinkSocket->tosize) < 0) {
            perror("LINK sendDataBySerial: Erreur Attitude");
        }

        // Envoi Position
        setDataMavlinkPosition(structDataLink);
        if (sendto(structDataLinkSocket->sock, structDataLink->buffer, structDataLink->len, 0, (SOCKADDR *) & structDataLinkSocket->to, structDataLinkSocket->tosize) < 0) {
            perror("LINK sendDataBySerial: Erreur Position");
        }

        // Reception acquittement du serveur
        if ((structDataLinkSocket->lenDataRec = recvfrom(structDataLinkSocket->sock, structDataLink->buffer_return, sizeof structDataLink->buffer_return - 1, 0, (SOCKADDR *) & structDataLinkSocket->to, &structDataLinkSocket->tosize)) < 0) {
            perror("LINK sendDataBySerial: Erreur Acquittement");
        }

        structDataLink->buffer_return[structDataLinkSocket->lenDataRec] = '\0';

        sleep(0.5);
    }

    closesocket(structDataLinkSocket->sock);

    return EXIT_SUCCESS;
}