/**
 * Envoie des informations vers la station sol
 * Au format mavlink
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "lib/drivers/include/link.h"

/**
 * Définition des informations de la station sol
 */


int main(void) {

    // Création de la structure global à la liaison
    GlobalDataLink structDataLink;

    // Initialisation des informations communes à l'ensemble des liaisons
    getInitGlobal(&structDataLink);

    printf("Type Link: %d \n", structDataLink.typeLink);

    // Envoi des données par Socket
    if (structDataLink.typeLink == 1) {
        
       /* // Initialisation des informations Socket
        SocketDataLink structDataLinkSocket;
        getInitSocket(&structDataLinkSocket, &structDataLink);
        return sendDataBySocket(&structDataLinkSocket, &structDataLink);*/

    // Envoi des données via les modules de télémétrie
    } else if (structDataLink.typeLink == 2) {


    }

    /* int n = 0;
     uint8_t buffer[BUF_SIZE];
     mavlink_message_t msg;
     uint16_t len;*/

    /* sock = socket(AF_INET, SOCK_DGRAM, 0);
     if (sock == INVALID_SOCKET) {
         perror("socket()");
         exit(errno);
     }

     hostinfo = gethostbyname(hostname);
     if (hostinfo == NULL) {
         fprintf(stderr, "Unknown host %s.\n", hostname);
         exit(EXIT_FAILURE);
     }

     to.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
     to.sin_port = htons(PORT);
     to.sin_family = AF_INET;

     while (1) {

         // Envoi Heartbeat
         mavlink_msg_heartbeat_pack(1, 200, &msg, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
         len = mavlink_msg_to_send_buffer(buffer, &msg);

         if (sendto(sock, buffer, len, 0, (SOCKADDR *) & to, tosize) < 0) {
             perror("sendto()");
             exit(errno);
         }

         // Envoi Statut
         mavlink_msg_sys_status_pack(1, 200, &msg, 0, 0, 0, 500, 11000, -1, -1, 0, 0, 0, 0, 0, 0);
         len = mavlink_msg_to_send_buffer(buffer, &msg);

         if (sendto(sock, buffer, len, 0, (SOCKADDR *) & to, tosize) < 0) {
             perror("sendto()");
             exit(errno);
         }

         // Reception acquittement du serveur
         if ((n = recvfrom(sock, buffer, sizeof buffer - 1, 0, (SOCKADDR *) & to, &tosize)) < 0) {
             perror("recvfrom()");
             exit(errno);
         }
         buffer[n] = '\0';

         sleep(0.5);
     }

     closesocket(sock);*/
    return EXIT_SUCCESS;
}


