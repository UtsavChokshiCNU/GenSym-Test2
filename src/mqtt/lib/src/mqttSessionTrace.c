#include "mqttSessionTrace.h"
#include <errno.h>
char const* session_trace_file_tag = "ControlPacket";
char const* bool_str[] = { "False",  "True" };


// Broker IP : all . and : replaced by _ and method returns null if it's null
// path: if empty or null will use current working directory to store log file
//
mqtt_pts_t mqtt_make_packet_trace_params(char const *brokerIP,  char const *path, int file_rolling_period)
{
    mqtt_pts_t params;
    int filepath_ret;
    int timestamp_path_ret;

    // We ensure to initiate empty string in filepath here for the case if brokerIP = NULL then ensure filepath doesn't contains rubish.
    strcpy(params.filePath,"");
    
    if (brokerIP == NULL) 
    {
        params.mqtt_logging_last_error = mqtt_error_invalid_parameter;
        return params;
    }


    timestamp_path_ret = mqtt_configure_timestamp(brokerIP, path, session_trace_file_tag, &params.file_creation_time);

    if (timestamp_path_ret != mqtt_success) 
    {
        params.mqtt_logging_last_error = timestamp_path_ret;
        return params;
    }
    
    filepath_ret = mqtt_trace_getfilePath(path,  brokerIP, session_trace_file_tag, "log", params.filePath,  PATH_LENGTH);

    params.file_rolling_period = file_rolling_period;
    params.mqtt_logging_last_error = filepath_ret;
    params.isON = filepath_ret == mqtt_success;
    return params;
}

static FILE* open_trace_file(mqtt_pts_t *const session_trace_params, enum mqtt_status_enum* result)
{
    FILE* tracefile = NULL;

    if (session_trace_params->filePath == NULL || strlen(session_trace_params->filePath)<=0) 
    {
        *result = mqtt_error_trace_not_initialized;
        return tracefile;
    }

    if (session_trace_params->isON == 0 ) 
    {
        *result = mqtt_error_trace_turned_off;
        return tracefile;
    }

    *result = mqtt_check_do_rolling(&session_trace_params->file_creation_time,
        session_trace_params->file_rolling_period, session_trace_params->filePath);
    if(*result != mqtt_success) 
    {
        return tracefile;
    }

    tracefile = fopen(session_trace_params->filePath,  "ab+");
    
    if ( NULL == tracefile) 
    {
        /* should work on Windows and Linux, but may not be portable to other system */
        if ( errno == ENOENT  ) 
        {
            *result = mqtt_error_trace_not_initialized;
        }

        return tracefile;
    }
    return tracefile;
}


static enum mqtt_status_enum mqtt_trace_session_format(mqtt_pts_t *const session_trace_params, const char* tag,  const char* message,  ...) 
{
    va_list args;
    enum mqtt_status_enum open_result = mqtt_success;
    time_t now;
    FILE* tracefile;

    char date[28];
    
    tracefile = open_trace_file(session_trace_params, &open_result);
    
    if ( NULL == tracefile) 
    {
        return open_result;
    }

    va_start(args,  message);
    time(&now);
    mqtt_ctime_s(&now, date, 28);
    date[strlen(date) - 1] = '\0';

    if (fprintf(tracefile,  "%s [%s] ",  date,  tag) <=0) 
    {
        mqtt_log_critical_error(stdout, "Session", ferror(tracefile));
        fclose(tracefile);
        return mqtt_error_failed_to_write_to_the_file;
    }
    
    if (message !=NULL && vfprintf(tracefile,  message,  args) <= 0) 
    {
        mqtt_log_critical_error(stdout, "Session", ferror(tracefile));
        fclose(tracefile);
        return mqtt_error_failed_to_write_to_the_file;
    }

    fclose(tracefile);

    return mqtt_success;
}


//Client request to connect to Server
// returns : 0 = Success
//         -110 = mqtt_error_trace_not_initialized
enum mqtt_status_enum mqtt_trace_packet_CONNECT(mqtt_pts_t *pts, const char *clientid/* 1- 23 char */,  short protocol_level, 
    unsigned char sendUsername,  unsigned char sendPwd,  unsigned char willRetain,  short willQoS,  unsigned char willFlag,  unsigned char cleanSession,  int keepAlive, 
    const char *willTopic,  const char *willMessage,  const char *userName,  const char *pwd)
{
    return mqtt_trace_session_format(pts, "CONNECT", 
        "clientid=%s, protocollevel=%c, sendUsername=%s, sendPwd=%s, willRetain=%s, willQoS=%d, willFlag=%s, cleanSession=%s, keepAlive=%d, willTopic=%s, willMessage=%s, userName=%s, pwd=\"***""\n", 
        clientid,  protocol_level,  bool_str[sendUsername], 
        bool_str[sendPwd],  bool_str[willRetain],  willQoS,  bool_str[willFlag],  bool_str[cleanSession], 
        keepAlive,  willTopic,  willMessage,  userName);
}

//Connect acknowledgment from the server to client
enum mqtt_status_enum mqtt_trace_packet_CONNACK(mqtt_pts_t *pts, unsigned char sessionPresent,  unsigned short connackCode)
{
    return mqtt_trace_session_format(pts, "CONNACK",  "session present=%s, connackCode=%d\n",  bool_str[sessionPresent],  connackCode);
}

//Clients send request to publish a message to the server
enum mqtt_status_enum mqtt_trace_packet_PUBLISH(mqtt_pts_t *pts, unsigned char dup,  short QoS, const char *topicName, int packetId, const char *message)
{
    return mqtt_trace_session_format(pts, "PUBLISH",  "DUP=%s, QoS=%d, Topic Name=%s, packetId=%d, Message=%s\n",  bool_str[dup],  QoS,  topicName,  packetId,  message);
}


//Server sends Publish acknowledgment to client
enum mqtt_status_enum mqtt_trace_packet_PUBACK(mqtt_pts_t *pts, const char *packetId)
{
    return mqtt_trace_session_format(pts, "PUBACK",  "PacketID=%s\n",  packetId);
}


//Publish received (assured delivery part 1)
enum mqtt_status_enum mqtt_trace_packet_PUBREC(mqtt_pts_t *pts, const char *packetId)
{
    return mqtt_trace_session_format(pts, "PUBREC",  "PacketID=%s\n",  packetId);
}


//Publish release (assured delivery part 2)
enum mqtt_status_enum mqtt_trace_packet_PUBREL(mqtt_pts_t *pts, const char *packetId)
{
    return mqtt_trace_session_format(pts, "PUBREL",  "PacketID=%s\n",  packetId);
}


//Publish complete (assured delivery part 3)
enum mqtt_status_enum mqtt_trace_packet_PUBCOMP(mqtt_pts_t *pts, const char *packetId)
{
    return mqtt_trace_session_format(pts, "PUBCOMP",  "PacketID=%s\n",  packetId);
}


//Internal use
static enum mqtt_status_enum mqtt_trace_packet_SUBSCRIBE_UNSUBSCRIBE(mqtt_pts_t *pts, const char *tag, const char *packetId, const mqtt_sub_topic *topics,  short topicsCount)
{
    FILE *tracefile;
    enum mqtt_status_enum err=mqtt_success;
    int j=0;

    err = mqtt_trace_session_format(pts, tag,  "PacketId=%s,\n", packetId);

    if ( err != mqtt_success) 
    {
        return err;
    }

    tracefile = open_trace_file(pts, &err);
    
    if ( NULL == tracefile) 
    {
        return err;
    }

    for (j = 0; j < topicsCount; j++) 
    {
        if (fprintf(tracefile, "Topic=%s, QoS=%d\n", topics[j].topicname,  topics[j].QoS)<=0) 
        {
            mqtt_log_critical_error(stdout, "Session", ferror(tracefile));
            fclose(tracefile);
            return mqtt_error_failed_to_write_to_the_file;
        }
    }

    if (fprintf(tracefile,  "\n") <= 0) 
    {
        mqtt_log_critical_error(stdout, "Session", ferror(tracefile));
        fclose(tracefile);
        return mqtt_error_failed_to_write_to_the_file;
    }

    fclose(tracefile);
    return mqtt_success;
}


//Client subscribe request
enum mqtt_status_enum mqtt_trace_packet_SUBSCRIBE(mqtt_pts_t *pts, const char *packetId,  const mqtt_sub_topic *topics, short topicsCount)
{
    return mqtt_trace_packet_SUBSCRIBE_UNSUBSCRIBE(pts, "SUBSCRIBE",  packetId,  topics,  topicsCount);
}


//Unsubscribe request
enum mqtt_status_enum mqtt_trace_packet_UNSUBSCRIBE(mqtt_pts_t *pts, const char *packetId, const mqtt_sub_topic *topics,  short topicsCount)
{
    return mqtt_trace_packet_SUBSCRIBE_UNSUBSCRIBE(pts, "UNSUBSCRIBE",  packetId,  topics,  topicsCount);

}


//Subscribe acknowledgment
enum mqtt_status_enum mqtt_trace_packet_SUBACK(mqtt_pts_t *pts, const char *packetId, const short returnCodes[],  short topicsCount)
{
    //According to MQTT standard lines 1030 - 1035 possible values is 0, 1, 2, 0x80
    enum mqtt_status_enum err=mqtt_success;
    int j = 0;
    FILE *tracefile;

    err = mqtt_trace_session_format(pts, "SUBACK",  "PacketID=%s, Return Codes:", packetId);

    if ( err != mqtt_success) 
    {
        return err;
    }

    tracefile = open_trace_file(pts, &err);
    
    if ( NULL == tracefile) 
    {
        return err;
    }
    
    for (j = 0; j < topicsCount; j++)
    {
        if (fprintf(tracefile,"%d, ",  returnCodes[j])<=0) 
        {
            mqtt_log_critical_error(stdout, "Session", ferror(tracefile));
            fclose(tracefile);
            return mqtt_error_failed_to_write_to_the_file;
        }
    }

    if (fprintf(tracefile,"\n")<=0) 
    {
            mqtt_log_critical_error(stdout, "Session", ferror(tracefile));
            fclose(tracefile);
            return mqtt_error_failed_to_write_to_the_file;
    }
    fclose(tracefile);
    return mqtt_success;

}


//Unsubscribe acknowledgment
enum mqtt_status_enum mqtt_trace_packet_UNSUBACK(mqtt_pts_t *pts, const char *packetId)
{
    return mqtt_trace_session_format(pts, "UNSUBACK",  "PacketID=%s\n",  packetId);

}


//PING request
enum mqtt_status_enum mqtt_trace_packet_PINGREQ(mqtt_pts_t *pts)
{
    return mqtt_trace_session_format(pts, "PINGREQ",  "%s\n",  ".");
}


//PING response
enum mqtt_status_enum mqtt_trace_packet_PINGRESP(mqtt_pts_t *pts)
{
    return mqtt_trace_session_format(pts, "PINGRESP",  "%s\n",  ".");
}


//Client is disconnecting
enum mqtt_status_enum mqtt_trace_packet_DISCONNECT(mqtt_pts_t *pts)
{
    return mqtt_trace_session_format(pts, "DISCONNECT",  "%s\n",  ".");
}


void mqtt_trace_session_turnOn(mqtt_pts_t *pts)
{
    pts->isON = 1;
}


void mqtt_trace_session_turnOff(mqtt_pts_t *pts)
{
    pts->isON = 0;
}
