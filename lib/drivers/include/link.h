#ifndef LINK_H
#define LINK_H

//-----------------------------
//----- INCLUDE 	  -----
//-----------------------------
#include "./lib/mavlink/standard/mavlink.h"
#include "hiredis/hiredis.h"

// On inclut les diff�rents drivers
#include "./socket.h"

//-----------------------------
//----- DEFINE 		  -----
//-----------------------------
#define BUF_SIZE 2041

//-----------------------------
//----- STRUCTURE 	  -----
//-----------------------------

//D�finition de la structure d'informations globales � l'ensemble des types de transfert d'informations
typedef struct GlobalDataLink GlobalDataLink;

struct GlobalDataLink {
    
    /* Type de liaison
     * 1: Socket
     * 2: Module t�l�m�trie
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
};

//-----------------------------
//----- Prototypes 	  -----
//-----------------------------
void getInitGlobal(GlobalDataLink *structDataLink);


#endif /* LINK_H */

