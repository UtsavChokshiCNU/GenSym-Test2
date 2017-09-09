#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "mqttTraceHelper.h"

void replaceInvalidPathChar(char *p)
{
    char const invalid[]=":.; \n]|=,\t/\\";
    int idx = 0;

    if (p == NULL) return;

    for (p += strcspn(p, invalid); *p != '\0'; p += 1 + strcspn(p+1, invalid)) 
    {
     *p = '_';
    }
}


enum mqtt_status_enum mqtt_trace_getfilePath(char const* path, char const* brokerIP, const char *tag, char const *extension, char *fullpath_out, int size)
{

    char cwd[PATH_LENGTH+1];
    char adjusted_broker_ip[PATH_LENGTH+1];
    int broker_strlen = 0;
    
    *fullpath_out = '\0';
    if (path == NULL || strlen(path) <= 0) 
    {
        char *cwd_result = getcwd(cwd,  PATH_LENGTH + 1);
        
        if(cwd_result == NULL) 
        {
            return mqtt_error_cant_create_filepath;
        }
        
    } 
    else 
    {
        strcpy(cwd, path);
    }
    // From M0 document
    // Session Log File name:<BrokerIP>_TAG_<MQTTClientReleaseVer>.log.
    if(NULL == brokerIP) 
    {
        return mqtt_error_invalid_parameter;
    }
    broker_strlen = strlen(brokerIP);

    if (broker_strlen > 0 && broker_strlen < PATH_LENGTH) 
    {
        strcpy(adjusted_broker_ip, brokerIP);
    } 
    else 
    {
        return mqtt_error_invalid_parameter;
    }

    replaceInvalidPathChar(adjusted_broker_ip);

    if ( snprintf(fullpath_out,size,  "%s%c%s_%s_%s.%s",  cwd, PATH_SEP, adjusted_broker_ip, tag, MQTTClient_Release_Ver, extension) <= 0 ) 
    {
        mqtt_log_critical_error(stdout, "mqtt_trace_getfilePath snprintf", errno);
        return mqtt_error_cant_create_filepath;
    }

    return mqtt_success;
}


void mqtt_ctime_s(const time_t *clock, char *buffer, int len)
{
#ifdef _WIN32
    ctime_s(buffer, len, clock);
#else
    ctime_r(clock, buffer);
#endif

}

void mqtt_log_critical_error(FILE* errorfile, char const *tag, int ferr)
{
    time_t now;
    char date[28];

    if ( errorfile == NULL) 
    {
        errorfile = stdout;
    }

    time(&now);

    mqtt_ctime_s(&now, date, 28);
    date[strlen(date) - 1] = '\0';

    fprintf(errorfile, "MQTT %s Trace,%s,ERROR,fprintf failed with the following error %d", tag, date, ferr);
}

enum mqtt_status_enum mqtt_trace_get_file_creationtime(char const* filepath, mqtt_time_t *output)
{
    enum mqtt_status_enum result = mqtt_success;
    FILE *traceFile = fopen(filepath, "r");
    char tmp[PATH_LENGTH+1];
    *tmp = '\0';
    *output = time_t_to_mqtt_time_t(time(NULL));

    //if file exists find the 1st recorded message time , else time is now
    if(traceFile != NULL) 
    {
        if(1 > fscanf(traceFile, "%s", tmp)) 
        {
            mqtt_log_critical_error(stdout, "Can't read from file fscanf failed", mqtt_error_failed_to_read_from_file); 
            mqtt_log_critical_error(stdout, filepath, mqtt_error_failed_to_read_from_file); 
            result = mqtt_error_failed_to_read_from_file;

        } 
        else if(isdigit((unsigned char)tmp[0]) != 0) 
        {
            
            *output = strtod((const char*)tmp, NULL);
            result = mqtt_success;
        } else {
            mqtt_log_critical_error(stdout, "Invalid time stamp", mqtt_error_invalid_content_of_stamp_file);
            mqtt_log_critical_error(stdout, (const char*) tmp, mqtt_error_failed_to_read_from_file); 
            result = mqtt_error_invalid_content_of_stamp_file;
        }
             
        fclose(traceFile);
    } 
    else 
    {
         FILE *new_file = fopen(filepath,"w");
         if(new_file == NULL) 
         {
             return mqtt_error_unable_to_create_file;
         }
         
         if(fprintf(new_file, MQTT_TIME_PRINTF_FORMAT, *output) <= 0) 
         {
             result = mqtt_error_failed_to_write_to_the_file;
         }

         fclose(new_file);
    }

    return result;
}


int mqtt_configure_timestamp(char const *brokerIP, char const *path, char const *tag , mqtt_time_t *outputstamp)
{
    enum mqtt_status_enum timestamp_path_ret = mqtt_success;
    char stampfilepath[PATH_LENGTH];
    
    timestamp_path_ret = mqtt_trace_getfilePath(path,  brokerIP, tag, "timestamp",  stampfilepath,  PATH_LENGTH);

    if (timestamp_path_ret != mqtt_success) 
    {
        *outputstamp = -1;
        return timestamp_path_ret;
    }

    timestamp_path_ret = mqtt_trace_get_file_creationtime(stampfilepath, outputstamp);

    if (timestamp_path_ret != mqtt_success) 
    {
        *outputstamp = -1;
        return timestamp_path_ret;
    }
    return timestamp_path_ret;
}


static enum mqtt_status_enum mqtt_update_timestamp(char const *stampfilename, mqtt_time_t *filecreationtime)
{
    FILE *stampfile;

    *filecreationtime = time_t_to_mqtt_time_t(time(NULL));

    stampfile = fopen(stampfilename,"w");

    if(stampfile == NULL) 
    {
        return mqtt_error_unable_to_create_file;
    }
         
    if(fprintf(stampfile, MQTT_TIME_PRINTF_FORMAT, *filecreationtime) <= 0) 
    {
        fclose(stampfile);
        return mqtt_error_failed_to_write_to_the_file;
    }

    fclose(stampfile);
    return mqtt_success;
}


enum mqtt_status_enum mqtt_check_do_rolling(mqtt_time_t* file_creation_time, long file_rolling_period, char const *current_file_path)
{
    mqtt_time_t now;
    int rename_return;
    enum mqtt_status_enum updatestamp_result = mqtt_success;
    now = time_t_to_mqtt_time_t(time(NULL));
    
    if(file_rolling_period <= (now - *file_creation_time)) 
    {
        char timestamp_file_name[PATH_LENGTH+1];
        char rolled_trace_file_old_name[PATH_LENGTH+1];
        char file_name_without_extension[PATH_LENGTH+1];
        char const *dotPtr;
        int snprintf_ret = 0;
        time_t current_time;
        int dotindex = -1;
        char date[28];

        current_time = time(NULL);
        mqtt_ctime_s(&current_time, date, 28);
        replaceInvalidPathChar(date);
        dotPtr = strchr(current_file_path, '.');

        if( NULL == dotPtr || dotPtr == current_file_path) 
        {
            return mqtt_error_invalid_parameter;
        }

        dotindex = dotPtr - current_file_path;
        memcpy(file_name_without_extension, current_file_path, dotindex);
        file_name_without_extension[dotindex]= '\0';
        snprintf_ret = snprintf(rolled_trace_file_old_name, PATH_LENGTH, "%s.old", file_name_without_extension);

        if(snprintf_ret <=0) 
        {
            mqtt_log_critical_error(stdout, "open_trace_file session sprintf create backup path too long", 0);
            return mqtt_error_string_concat_error;
        }

        // ensure of null trmination , _snprintf might not zero-terminate string
        rolled_trace_file_old_name[snprintf_ret] = '\0';

        remove(rolled_trace_file_old_name);

        rename_return = rename(current_file_path, rolled_trace_file_old_name);

        if(rename_return != 0) 
        {
             mqtt_log_critical_error(stdout, "Can't rename old trace file to a backup file", rename_return);

        }

        if(snprintf(timestamp_file_name, PATH_LENGTH, "%s.timestamp", file_name_without_extension)<=0) 
        {
            mqtt_log_critical_error(stdout, "open_trace_file: session snprintf create timestamp file name string", 0);
        }

        updatestamp_result = mqtt_update_timestamp(timestamp_file_name, file_creation_time);

        if(updatestamp_result != mqtt_success) 
        {
            mqtt_log_critical_error(stdout, "open_trace_file: session Failed to update timestamp file with the followng error ", updatestamp_result);
        }
    }

    return mqtt_success;
}

mqtt_time_t time_t_to_mqtt_time_t(time_t t)
{
    mqtt_time_t ret;

    ret = difftime(t, 0); 

    return ret;
}

/* Used by u8_isvalid below */
static const char trailingBytesForUTF8[256] = 
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

/* Based on valid_utf8 routine from PCRE library by Philip Hazel */
int u8_isvalid(const char *string, size_t length)
{
    const unsigned char *p, *pending = (unsigned char*)string + length;
    unsigned char c;
    int return_code = 1; /* ASCII */
    size_t trailingBytes;

    for (p = (unsigned char*)string; p < pending; p++) 
    {
        c = *p;
        if (c < 128)
            continue;
        return_code = 2; /* non-ASCII UTF-8 */
        if ((c & 0xc0) != 0xc0)
            return 0;
        trailingBytes = trailingBytesForUTF8[c];
        if (length < trailingBytes)
            return 0;
        length -= trailingBytes;

        p++;
        /* Check top bits in the second byte */
        if ((*p & 0xc0) != 0x80)
            return 0;

        /* Check for overlong sequences for each different length */
        switch (trailingBytes) 
        {
            /* Check for xx00 000x */
        case 1:
            if ((c & 0x3e) == 0) return 0;
            continue;   /* We know there aren't any more bytes to check */

            /* Check for 1110 0000, xx0x xxxx */
        case 2:
            if (c == 0xe0 && (*p & 0x20) == 0) return 0;
            break;

            /* Check for 1111 0000, xx00 xxxx */
        case 3:
            if (c == 0xf0 && (*p & 0x30) == 0) return 0;
            break;

            /* Check for 1111 1000, xx00 0xxx */
        case 4:
            if (c == 0xf8 && (*p & 0x38) == 0) return 0;
            break;

            /* Check for leading 0xfe or 0xff,
               and then for 1111 1100, xx00 00xx */
        case 5:
            if (c == 0xfe || c == 0xff ||
                (c == 0xfc && (*p & 0x3c) == 0)) return 0;
            break;
        }

        /* Check for valid bytes after the 2nd, if any; all must start 10 */
        while (--trailingBytes > 0) 
        {
            if ((*(++p) & 0xc0) != 0x80) return 0;
        }
    }

    return return_code;
}

enum mqtt_status_enum toHex(unsigned char* input, size_t inputLen, char* output, size_t outputLen)
{
    unsigned char* p_input = input;
    const char* hex = "0123456789ABCDEF";
    char* p_output = output;
    for(; p_input < input + inputLen; p_output +=3, p_input++)
    {
        p_output[0] = hex[(*p_input>>4) & 0xF];
        p_output[1] = hex[*p_input & 0xF];
        p_output[2] = ':';
        if (p_output + 3 - output > outputLen)
        {
            break;
        }
    }
    p_output[-1] = 0;
    return mqtt_success;
}
