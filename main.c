/**
 * Envoie des informations vers la station sol
 * Au format mavlink : https://github.com/mavlink/c_library_v2
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "lib/drivers/include/link.h"

int main(void) {

    // Cr�ation de la structure global � la liaison
    GlobalDataLink structDataLink;

    // Initialisation des informations communes � l'ensemble des liaisons
    getInitGlobal(&structDataLink);

    // Envoi des donn�es par Socket
    if (structDataLink.typeLink == 1) {
        printf("LINK : Type Socket \n");

        // Initialisation des informations Socket
        SocketDataLink structDataLinkSocket;
        if (getInitSocket(&structDataLinkSocket, &structDataLink) == EXIT_SUCCESS) {
            return sendDataBySocket(&structDataLinkSocket, &structDataLink);
        }

        // Envoi des donn�es via les modules de t�l�m�trie (serial)
    } else if (structDataLink.typeLink == 2) {
        printf("LINK : Type Telemetrie \n");

        // Initialisation des informations Serial
        SerialDataLink structDataLinkSerial;
        if (getInitSerial(&structDataLinkSerial, &structDataLink) == EXIT_SUCCESS) {
            return sendDataBySerial(&structDataLinkSerial, &structDataLink);
        }
    }

    return EXIT_SUCCESS;
}


