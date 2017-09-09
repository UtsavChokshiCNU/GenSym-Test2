#include "mqttDataTrace.h"
#include <errno.h>
char const* data_trace_file_tag = "MessageData";

mqtt_dtp_t mqtt_make_topic_data_trace(char const* brokerIP, char const* path, int file_rolling_period)
{
    mqtt_dtp_t data_params;
    int filepath_ret;
    int timestamp_path_ret;

    strcpy(data_params.filePath,"");

    // We ensure to initiate empty string in filepath here for the case if brokerIP = NULL then ensure filepath doesn't contains rubish.
    if (brokerIP == NULL) 
    {
        data_params.mqtt_logging_last_error = mqtt_error_invalid_parameter;
        return data_params;
    }


    timestamp_path_ret = mqtt_configure_timestamp(brokerIP, path, data_trace_file_tag, &data_params.file_creation_time);

    if (timestamp_path_ret != mqtt_success) 
    {
        data_params.mqtt_logging_last_error = timestamp_path_ret;
        return data_params;
    }

    filepath_ret = mqtt_trace_getfilePath(path,  brokerIP, data_trace_file_tag, "log", data_params.filePath,  PATH_LENGTH);
    
    data_params.mqtt_logging_last_error = filepath_ret;
    data_params.isON = filepath_ret == mqtt_success;
    data_params.file_rolling_period = file_rolling_period;

    return data_params;
}


static enum mqtt_status_enum mqtt_trace_data_format(mqtt_dtp_t *data_params, const char *tag, char const* topic, short QoS,  char const* data)
{
    time_t now;
    enum mqtt_status_enum ret;

    char hexData[MQTT_MAX_MESSAGE_LENGTH * 3];

    int inputLen;
    int outputLen;

    char date[28];
    FILE *tracefile;

    if (data_params->filePath == NULL || strlen(data_params->filePath)<=0) 
    {
        return mqtt_error_trace_not_initialized;
    }
    
    if (data_params->isON == 0) 
    {
        return mqtt_error_trace_turned_off;
    }

    ret = mqtt_check_do_rolling(&data_params->file_creation_time,data_params->file_rolling_period, data_params->filePath);
    
    if(ret!=mqtt_success) 
    {
        return ret;
    }

    tracefile = fopen(data_params->filePath,  "ab+");
    
    if ( NULL == tracefile) 
    {
        /* should work on Windows and Linux, but may not be portable to other system */
        if ( errno == ENOENT ) 
        {
            return mqtt_error_trace_not_initialized;
        }

        printf("strerror says open failed: %s, %d\n",  strerror(errno),  errno);
        return mqtt_error_unable_to_create_file;
    }

    time(&now);
    mqtt_ctime_s(&now, date, 28);
    date[strlen(date) - 1] = '\0';
    inputLen = strlen(data);
    outputLen = inputLen * 3;

    if (outputLen > (MQTT_MAX_MESSAGE_LENGTH * 3))
    {
        if (fprintf(tracefile,  "%s, %s, QoS=%d, topic=%s, Data=%s, HexData max length limit=[%d] exceeded\n", 
                date, tag,  QoS, topic, data, outputLen) <= 0) 
        {
            fclose(tracefile);
            return mqtt_error_failed_to_write_to_the_file;
        }

        return mqtt_error_message_too_long;
    }

    if (u8_isvalid((const char*) data, strlen(data)) != 0) 
    {

        ret = toHex((unsigned char*) data, inputLen, hexData, outputLen);
        if (ret != mqtt_success)
        {
            return ret;
        }

        if (fprintf(tracefile,  "%s, %s, QoS=%d, topic=%s, Data=%s, HexData=%s\n", date, tag,  QoS, topic, data, hexData) <= 0) 
        {
            fclose(tracefile);
            return mqtt_error_failed_to_write_to_the_file;
        }
    } else {

        ret = toHex((unsigned char*) data, inputLen, hexData, outputLen);
        if (ret != mqtt_success)
        {
            return ret;
        }

        if (fprintf(tracefile,  "%s, %s, QoS=%d, topic=%s, HexData=%s\n", date, tag,  QoS, topic, hexData) <= 0) 
        {
            fclose(tracefile);
            return mqtt_error_failed_to_write_to_the_file;
        }
    }

    fclose(tracefile);

    return mqtt_success;
}


enum mqtt_status_enum mqtt_tdt_published(mqtt_dtp_t *data_params, char const* topic, short QoS,  char const* data)
{
    return mqtt_trace_data_format(data_params, "Published_data", topic, QoS, data);
}


enum mqtt_status_enum mqtt_tdt_received(mqtt_dtp_t *data_params, char const* topic, short QoS,  char const* data)
{
    return mqtt_trace_data_format(data_params, "Received_data", topic, QoS, data);
}


void mqtt_trace_data_turnOn(mqtt_dtp_t *data_params)
{
    data_params->isON = 1;
}


void mqtt_trace_data_turnOff(mqtt_dtp_t *data_params)
{
    data_params->isON = 0;
}