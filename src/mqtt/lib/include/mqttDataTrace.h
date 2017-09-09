#ifndef MQTT_DATA_TRACE_H
#define MQTT_DATA_TRACE_H

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
#include <stdint.h>
#include "mqtt_constants.h"
#include "mqttTraceHelper.h"
#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#ifndef getcwd
#define getcwd _getcwd
#endif
#else
#include <unistd.h>
#endif

// Max allowable message data length to be published is 256 KB
#define MQTT_MAX_MESSAGE_LENGTH                     (256 * 1024)

/*
This structure contains the tracer state , please don't change it directly even if you can.
Please use the approperate API call to make changes to this structure.
*/
struct  mqtt_data_trace_params
{
    char filePath[PATH_LENGTH+1];
    unsigned char isON;
    long file_rolling_period;
    mqtt_time_t file_creation_time;
    int mqtt_logging_last_error;
};

typedef struct mqtt_data_trace_params mqtt_dtp_t;

/**
Function to create and initialize Topic/Data Tracing , it creates the full path string for trace file and by default turn logging ON
@param    brokerIP We use this as a part of tracing file name signature according to M0 requirement document , this can't be null.
@param    path it's the path where you want to place trace file , if NULL or empty it uses current working direcotry.
@param    file_rolling_period period in seconds after which the trace file will be rolled and a new trace file being created.
@return  a data tracing parameters structur that holds the tracer state , mqtt_logging_last_error indicates success or error of the operation
*/
mqtt_dtp_t mqtt_make_topic_data_trace(char const* brokerIP,char const* path, int file_rolling_period);


/**
Function to turn on the tracing.
*/
void mqtt_trace_data_turnOn(mqtt_dtp_t *data_params);


/**
Function to turn off the tracing , if you tried to call any tracing api the return code should be mqtt_error_trace_turned_off
@param    tdt data_params data trace parameter received when initialized the tracing functionality
*/
void mqtt_trace_data_turnOff(mqtt_dtp_t *data_params);


/**
Function to trace published messages from client to server
@param tdt topic data trace parameter received when initialized the tracing functionality
@param topic is the topic name used to publish the message on it.
@param QoS Quality of service required for this message
@param data Message being published.
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_tdt_published(mqtt_dtp_t *tdt,char const* topic,short QoS, char const* const data);


/**
Function to trace received messages from client to server
@param tdt topic data trace parameter received when initialized the tracing functionality
@param topic is the topic name used of received message.
@param QoS Quality of service required for this message
@param data Message being received. 
@retval mqtt_success in case of succesess.
@retval mqtt_error_trace_not_initialized if this function call was done before initializing the tracer using mqtt_make_topic_data_trace before this call.
@retval mqtt_error_trace_turned_off if the current state of the tracing is turned off.
*/
enum mqtt_status_enum mqtt_tdt_received(mqtt_dtp_t *tdt,char const* topic,short QoS, char const* data);

#endif