#include "../include/link.h"
#include "hiredis/hiredis.h"

/**
 * Initialisation des paramètres globaux au module de liaison sol.
 * - Récupération du type de liaison.
 * @param structDataLink
 */
void getInitGlobal(GlobalDataLink *structDataLink) {

    // Connexion à Redis
    struct timeval timeout = {1, 500000}; // 1.5 seconds
    structDataLink->redisContext = redisConnectWithTimeout("127.0.0.1", 6379, timeout);
    if (structDataLink->redisContext == NULL || structDataLink->redisContext->err) {
        if (structDataLink->redisContext) {
            redisFree(structDataLink->redisContext);
        }
    }
}

/**
 * Positionnement des informations du heartBeat
 * @param structDataLink
 */
void setDataMavlinkHeartBeat(GlobalDataLink *structDataLink) {
    mavlink_msg_heartbeat_pack(MAVLINK_MSG_ID, MAVLINK_COMP_ID, &structDataLink->msg, MAV_TYPE_FIXED_WING, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
    structDataLink->len = mavlink_msg_to_send_buffer(structDataLink->buffer, &structDataLink->msg);
     
    printf("HEARTBEAT %d :  %d,%d,%d \n", structDataLink->len, MAV_TYPE_FIXED_WING, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED);
    fflush(stdout);
}

/**
 * Statut de l'appareil
 * @param structDataLink
 */
void setDataMavlinkStatus(GlobalDataLink *structDataLink) {
    mavlink_msg_sys_status_pack(MAVLINK_MSG_ID, MAVLINK_COMP_ID, &structDataLink->msg, 0, 0, 0, 500, 11000, -1, -1, 0, 0, 0, 0, 0, 0);
    structDataLink->len = mavlink_msg_to_send_buffer(structDataLink->buffer, &structDataLink->msg);
}

/**
 * Attitude de l'appareil
 * - x y z
 * - acceleromètre x y z
 * @param structDataLink
 */
void setDataMavlinkAttitude(GlobalDataLink *structDataLink) {

    float roll;
    float pitch;
    float yaw;
    float rollspeed;
    float pitchspeed;
    float yawspeed;
    char *ptr;
    time_t timeElement;

    // Roll
    structDataLink->redisReply = redisCommand(structDataLink->redisContext, "GET current_x");
    if (structDataLink->redisReply->type == REDIS_REPLY_STRING && strcmp(structDataLink->redisReply->str, "nil") != 0) {
        roll = strtof(structDataLink->redisReply->str, &ptr);
    }
    freeReplyObject(structDataLink->redisReply);

    // Pitch
    structDataLink->redisReply = redisCommand(structDataLink->redisContext, "GET current_y");
    if (structDataLink->redisReply->type == REDIS_REPLY_STRING && strcmp(structDataLink->redisReply->str, "nil") != 0) {
        pitch = strtof(structDataLink->redisReply->str, &ptr);
    }
    freeReplyObject(structDataLink->redisReply);

    // Yaw
    structDataLink->redisReply = redisCommand(structDataLink->redisContext, "GET current_z");
    if (structDataLink->redisReply->type == REDIS_REPLY_STRING && strcmp(structDataLink->redisReply->str, "nil") != 0) {
        yaw = strtof(structDataLink->redisReply->str, &ptr);
    }
    freeReplyObject(structDataLink->redisReply);

    // Rollspeed
    structDataLink->redisReply = redisCommand(structDataLink->redisContext, "GET current_accel_x");
    if (structDataLink->redisReply->type == REDIS_REPLY_STRING && strcmp(structDataLink->redisReply->str, "nil") != 0) {
        rollspeed = strtof(structDataLink->redisReply->str, &ptr);
    }
    freeReplyObject(structDataLink->redisReply);

    // Pitchspeed
    structDataLink->redisReply = redisCommand(structDataLink->redisContext, "GET current_accel_y");
    if (structDataLink->redisReply->type == REDIS_REPLY_STRING && strcmp(structDataLink->redisReply->str, "nil") != 0) {
        pitchspeed = strtof(structDataLink->redisReply->str, &ptr);
    }
    freeReplyObject(structDataLink->redisReply);

    // Yawspeed
    structDataLink->redisReply = redisCommand(structDataLink->redisContext, "GET current_accel_z");
    if (structDataLink->redisReply->type == REDIS_REPLY_STRING && strcmp(structDataLink->redisReply->str, "nil") != 0) {
        yawspeed = strtof(structDataLink->redisReply->str, &ptr);
    }
    freeReplyObject(structDataLink->redisReply);

    timeElement = time(NULL);

    mavlink_msg_attitude_pack(MAVLINK_MSG_ID, MAVLINK_COMP_ID, &structDataLink->msg, timeElement, roll, pitch, yaw, rollspeed, pitchspeed, yawspeed);
    structDataLink->len = mavlink_msg_to_send_buffer(structDataLink->buffer, &structDataLink->msg);
    
    printf("ATTITUDE %d :  %f,%f,%f - %f,%f,%f \n", structDataLink->len, roll, pitch, yaw, rollspeed, pitchspeed, yawspeed);
    fflush(stdout);
}

/**
 * Position de l'appareil
 * - Latitude
 * - Longitude
 * - Altitude
 * @param structDataLink
 */
void setDataMavlinkPosition(GlobalDataLink *structDataLink) {

    float lat;
    float lon;
    float alt;
    char *ptr;
    time_t timeElement;

    // Latitude
    structDataLink->redisReply = redisCommand(structDataLink->redisContext, "GET current_Latitude");
    if (structDataLink->redisReply->type == REDIS_REPLY_STRING && strcmp(structDataLink->redisReply->str, "nil") != 0) {
        lat = strtof(structDataLink->redisReply->str, &ptr);
    }
    freeReplyObject(structDataLink->redisReply);


    // Longitude
    structDataLink->redisReply = redisCommand(structDataLink->redisContext, "GET current_Longitude");
    if (structDataLink->redisReply->type == REDIS_REPLY_STRING && strcmp(structDataLink->redisReply->str, "nil") != 0) {
        lon = strtof(structDataLink->redisReply->str, &ptr);
    }
    freeReplyObject(structDataLink->redisReply);

    // Altitude
    structDataLink->redisReply = redisCommand(structDataLink->redisContext, "GET current_altitude");
    if (structDataLink->redisReply->type == REDIS_REPLY_STRING && strcmp(structDataLink->redisReply->str, "nil") != 0) {
        alt = strtof(structDataLink->redisReply->str, &ptr);
    }
    freeReplyObject(structDataLink->redisReply);

    timeElement = time(NULL);

    mavlink_msg_gps_raw_int_pack(MAVLINK_MSG_ID, MAVLINK_COMP_ID, &structDataLink->msg, timeElement, 0, lat, lon, alt, 0, 0, 0, 0, 0);
    structDataLink->len = mavlink_msg_to_send_buffer(structDataLink->buffer, &structDataLink->msg); 
    
    printf("POSITION %d :  %f,%f,%f \n", structDataLink->len, lat, lon, alt);
    fflush(stdout);
}