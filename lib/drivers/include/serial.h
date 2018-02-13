#ifndef SERIAL_H
#define SERIAL_H

//-----------------------------
//----- INCLUDE 	  -----
//-----------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <termios.h> 
#include <sys/ioctl.h>
#include <getopt.h>
#include "link.h"

//-----------------------------
//----- DEFINE 		  -----
//-----------------------------
#define INVALID_FILE NULL
#define CRLF  "\r\n"
#define PATH_INTERFACE "/dev/serial/by-path/platform-3f980000.usb-usb-0:1.2:1.0-port0"

//-----------------------------
//----- STRUCTURE 	  -----
//-----------------------------
typedef struct SerialDataLink SerialDataLink;

struct SerialDataLink {
    int openSerial;
    speed_t brate;
    int lenDataRec;
};

typedef struct GlobalDataLink GlobalDataLink;

//-----------------------------
//----- Prototypes 	  -----
//-----------------------------
int getInitSerial(SerialDataLink *structDataLinkSerial, GlobalDataLink *structDataLink);
int sendDataBySerial(SerialDataLink *structDataLinkSerial, GlobalDataLink *structDataLink);


#endif /* SERIAL_H */

