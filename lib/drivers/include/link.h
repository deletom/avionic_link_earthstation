#ifndef LINK_H
#define LINK_H

//-----------------------------
//----- INCLUDE 	  -----
//-----------------------------
#include <time.h>
#include "./lib/mavlink/standard/mavlink.h"
#include "hiredis/hiredis.h"

// On inclut les différents drivers
#include "./socket.h"
#include "./serial.h"


//-----------------------------
//----- DEFINE 		  -----
//-----------------------------
#define BUF_SIZE 2041
#define MAVLINK_MSG_ID 1
#define MAVLINK_COMP_ID 200

//-----------------------------
//----- STRUCTURE 	  -----
//-----------------------------

//Définition de la structure d'informations globales à l'ensemble des types de transfert d'informations
typedef struct GlobalDataLink GlobalDataLink;

struct GlobalDataLink {
    /* Type de liaison
     * 1: Socket
     * 2: Module télémétrie
     */
    int typeLink;

    /*
     * Pointeur vers la connexion Redis
     */
    redisContext *redisContext;

    /*
     * Pointeur vers le "reply" Redis
     */
    redisReply *redisReply;

    /*
     * Informations utilisées pour les messages mavlink
     */
    uint8_t buffer[BUF_SIZE];
    uint8_t buffer_return[BUF_SIZE];
    mavlink_message_t msg;
    uint16_t len;

};

typedef struct dataMavlink dataMavlink;

//-----------------------------
//----- Prototypes 	  -----
//-----------------------------
void getInitGlobal(GlobalDataLink *structDataLink);

void setDataMavlinkHeartBeat(GlobalDataLink *structDataLink);
void setDataMavlinkStatus(GlobalDataLink *structDataLink);
void setDataMavlinkAttitude(GlobalDataLink *structDataLink);
void setDataMavlinkPosition(GlobalDataLink *structDataLink);

#endif /* LINK_H */

