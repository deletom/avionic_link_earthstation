#include "../include/serial.h"

/**
 * Initialisation de la connexion via le port série (USB ici)
 * @param structDataLinkSerial
 * @param structDataLink
 */
int getInitSerial(SerialDataLink *structDataLinkSerial, GlobalDataLink *structDataLink) {

    struct termios toptions;

    // Ouverture de la connexion
    structDataLinkSerial->openSerial = open(PATH_INTERFACE, O_RDWR | O_NOCTTY | O_NDELAY);

    if (structDataLinkSerial->openSerial == -1) {
        return EXIT_FAILURE;
    }

    if (tcgetattr(structDataLinkSerial->openSerial, &toptions) < 0) {
        return EXIT_FAILURE;
    }

    structDataLinkSerial->brate = B57600;

    cfsetispeed(&toptions, structDataLinkSerial->brate);
    cfsetospeed(&toptions, structDataLinkSerial->brate);

    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    toptions.c_cflag &= ~CRTSCTS;
    toptions.c_cflag |= CREAD | CLOCAL;
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    toptions.c_oflag &= ~OPOST;
    toptions.c_cc[VMIN] = 0;
    toptions.c_cc[VTIME] = 20;

    if (tcsetattr(structDataLinkSerial->openSerial, TCSANOW, &toptions) < 0) {
        return EXIT_FAILURE;
    }

    return structDataLinkSerial->openSerial;
}

/**
 * Récupération des données et envoi via sérial
 * @param structDataLinkSerial
 * @param structDataLink
 */
int sendDataBySerial(SerialDataLink *structDataLinkSerial, GlobalDataLink *structDataLink) {

    int returnWrite = 0;

    while (1) {

        // Envoi du HeartBeat 
        setDataMavlinkHeartBeat(structDataLink);
        returnWrite = write(structDataLinkSerial->openSerial, structDataLink->buffer, structDataLink->len);
        if (returnWrite == -1) {
            perror("LINK: Erreur HeartBeat");
        }
        usleep(22000); 

        // Envoi Statut
        setDataMavlinkStatus(structDataLink);
        returnWrite = write(structDataLinkSerial->openSerial, structDataLink->buffer, structDataLink->len);
        if (returnWrite == -1) {
            perror("LINK sendDataBySerial: Erreur Status");
        }
        usleep(22000);

        // Envoi Attitude
        setDataMavlinkAttitude(structDataLink);
        returnWrite = write(structDataLinkSerial->openSerial, structDataLink->buffer, structDataLink->len);
        if (returnWrite == -1) {
            perror("LINK sendDataBySerial: Erreur Attitude");
        }
        usleep(22000);

        // Envoi Position
        setDataMavlinkPosition(structDataLink);
        returnWrite = write(structDataLinkSerial->openSerial, structDataLink->buffer, structDataLink->len);
        if (returnWrite == -1) {
            perror("LINK sendDataBySerial: Erreur Position");
        }
        usleep(22000);
    }

    return EXIT_SUCCESS;
}