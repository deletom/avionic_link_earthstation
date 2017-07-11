#include "../include/link.h"
#include "hiredis/hiredis.h"

void getInitGlobal(GlobalDataLink *structDataLink) {
    // Connexion à Redis
    struct timeval timeout = {1, 500000}; // 1.5 seconds
    structDataLink->redisContext = redisConnectWithTimeout("127.0.0.1", 6379, timeout);
    if (structDataLink->redisContext == NULL || structDataLink->redisContext->err) {
        if (structDataLink->redisContext) {
            redisFree(structDataLink->redisContext);
        }
    }

    // Récupération du statut du GPS
    structDataLink->redisReply = redisCommand(structDataLink->redisContext, "GET config_link_earth_station_type");

    if (structDataLink->redisReply->type == REDIS_REPLY_STRING && strcmp(structDataLink->redisReply->str, "socket") == 0) {
        freeReplyObject(structDataLink->redisReply);
        structDataLink->typeLink = 1;
    } else {
        freeReplyObject(structDataLink->redisReply);
        structDataLink->typeLink = 2;
    }
}

