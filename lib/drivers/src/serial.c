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
        perror("LINK getInitSerial: Erreur lors de l ouverture du port");
        return EXIT_FAILURE;
    }

    if (tcgetattr(structDataLinkSerial->openSerial, &toptions) < 0) {
        perror("LINK getInitSerial: Probleme dans la recuperation des attributs");
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
        perror("LINK getInitSerial: Probleme dans la recuperation des attributs options");
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

    int i = 0;

    while (1) {

        setDataMavlinkHeartBeat(structDataLink);
        int n = write(structDataLinkSerial->openSerial, structDataLink->buffer, structDataLink->len);
        if (n == -1) {
            perror("LINK sendDataBySerial: Erreur HeartBeat");
        }

        // Envoi Statut
        setDataMavlinkStatus(structDataLink);
        int n = write(structDataLinkSerial->openSerial, structDataLink->buffer, structDataLink->len);
        if (n == -1) {
            perror("LINK sendDataBySerial: Erreur Status");
        }

        // Envoi Attitude
        setDataMavlinkAttitude(structDataLink);
        int n = write(structDataLinkSerial->openSerial, structDataLink->buffer, structDataLink->len);
        if (n == -1) {
            perror("LINK sendDataBySerial: Erreur Attitude");
        }

        // Envoi Position
        setDataMavlinkPosition(structDataLink);
        int n = write(structDataLinkSerial->openSerial, structDataLink->buffer, structDataLink->len);
        if (n == -1) {
            perror("LINK sendDataBySerial: Erreur Position");
        }

        sleep(1);
    }


    return EXIT_SUCCESS;
}