#ifndef MQTT_SESSION_TRACE_H
#define MQTT_SESSION_TRACE_H
/**
*   <p>
*       <b> Important Note </b> <br />
*   </p>
*   @note   Each tracing API accepts none constant pointer to tracing structure parameter, 
*           this is requiredto support some features that needs to update it like tracing log rolling.
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include "mqtt_constants.h"
#include "mqttTraceHelper.h"
#ifdef _WIN32
#include <direct.h>
#ifndef getcwd
#define getcwd _getcwd
#endif
#else
#include <unistd.h>
#endif

struct  mqtt_packet_trace_params
{
    char filePath[PATH_LENGTH+1];
    short isON;
    long file_rolling_period;
    mqtt_time_t file_creation_time;
    int mqtt_logging_last_error;
};

struct mqtt_protocol_subscribe_topic
{
    char *topicname;
    short QoS;
};

typedef struct mqtt_protocol_subscribe_topic mqtt_sub_topic;
typedef struct mqtt_packet_trace_params mqtt_pts_t;

/**
Function to create and initialize Session/Control Command Tracing ,  it creates the trace file if not exist and append to it if exists
@param    brokerIP We use this as a part of tracing file name signature according to M0 requirement document ,  this can't be null.
@param    path it's the path where you want to place trace file ,  it null or empty it uses current working direcotry.
@param    file_rolling_period the period in seconds to hold trace file before backing it up and creating a new trace file.
@return   pointer to session trace parameter structur created to hold the tracer state ,
the success or failure code is found in mqtt_logging_last_error parameter of returned structure
*/
mqtt_pts_t mqtt_make_packet_trace_params(char const *brokerIP,  char const *path, int file_rolling_period);

/**
Function to turn on tracing of session/controll_command data
@param pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
*/
void mqtt_trace_session_turnOn(mqtt_pts_t *pts);

/**
Function to turn off tracing of session/controll_command data.
@warnning If any tracing function called after calling this method and before calling mqtt_trace_session_turnOn again you will receive error mqtt_error_trace_turned_off
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
*/
void mqtt_trace_session_turnOff(mqtt_pts_t *pts);

/**
Function to trace CONNECT control command with all its associated parameters
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_CONNECT(mqtt_pts_t* pts, const char* clientid,  short protocol_level, 
    unsigned char sendUsername, unsigned char sendPwd, unsigned char willRetain,short willQoS,unsigned char willFlag, unsigned char cleanSession, int keepAlive, 
    char const* willTopic, char const* willMessage, char const* userName, char const* pwd);


/**
Function to trace CONNACK control command with all its associated parameters
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_CONNACK(mqtt_pts_t *pts, unsigned char sessionPresent,  unsigned short connackCode);


/**
Function to trace PUBLISH control command with all its associated parameters
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_PUBLISH(mqtt_pts_t *pts, unsigned char dup,  short QoS, char const *topicName, int packetId, char const *message);


/**
Function to trace PUBACK control command with ts associated parameter.
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@return   one of the following values 
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_PUBACK(mqtt_pts_t *pts, char const *packetId);


/**
Function to trace PUBREC control command with its associated parameter.
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_PUBREC(mqtt_pts_t *pts, char const *packetId);


/**
Function to trace PUBREL control command with its associated parameter
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_PUBREL(mqtt_pts_t *pts, char const *packetId);


/**
Function to trace PUBCOMP control command with its associated parameter
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_PUBCOMP(mqtt_pts_t *pts, char const *packetId);


/**
Function to trace SUBSCRIBE control command with all its associated parameters
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality 
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_SUBSCRIBE(mqtt_pts_t *pts, char const *packetId, const mqtt_sub_topic *topics,  short topicsCount);


/**
Function to trace SUBACK control command with all its associated parameters
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_SUBACK(mqtt_pts_t *pts, char const *packetId, const short returnCodes[],  short topicsCount);


/**
Function to trace UNSUBSCRIBE control command with all its associated parameters
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_UNSUBSCRIBE(mqtt_pts_t *pts, char const *packetId, const mqtt_sub_topic *topics,  short topicsCount);


/**
Function to trace UNSUBACK control command with all its associated parameter.
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_UNSUBACK(mqtt_pts_t *pts, char const *packetId);

/**
Function to trace PINTREQ control command.
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_PINGREQ(mqtt_pts_t *pts);


/**
Function to trace PINGRES control command.
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_PINGRESP(mqtt_pts_t *pts);


/**
Function to trace DISCONNECT control command.
@param    pts pointer to session trace parameter structur rereceived when initialized the tracing functionality
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_trace_packet_DISCONNECT(mqtt_pts_t *pts);


#endif
