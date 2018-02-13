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

    // Création de la structure global à la liaison
    GlobalDataLink structDataLink;

    // Initialisation des informations communes à l'ensemble des liaisons
    getInitGlobal(&structDataLink);

    // Initialisation des informations Serial
    SerialDataLink structDataLinkSerial;
    
    if (getInitSerial(&structDataLinkSerial, &structDataLink) != EXIT_FAILURE) {
        return sendDataBySerial(&structDataLinkSerial, &structDataLink);
        printf("LINK EARTHSTATION : INIT OK \r\n ");
    } else {
        printf("LINK EARTHSTATION : INIT KO \r\n ");
    }

    return EXIT_SUCCESS;
}


