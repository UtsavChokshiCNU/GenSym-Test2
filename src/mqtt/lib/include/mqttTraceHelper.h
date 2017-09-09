#ifndef MQTT_TRACE_HELPER_H
#define MQTT_TRACE_HELPER_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "mqtt_constants.h"
#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif

/**
Function to replace characters that could cause the file path to be invalide like : , . and white space to by _
@param    p pointer characters array which may contain invalid characters .
*/
void replaceInvalidPathChar(char *p);

/**
Function to build full path name according to M0 specifications for log file name <BrokerIP>_TAG_<MQTTClientReleaseVer>.log

@param  path pointer to path where caller need to put the log file , if path is NULL or empty we use Current Workign directory as path.
@param  brokerIP is char const pointer identifying the caller broker by its IP or Name.
@param  tag is place holder for string identifying if this file is Session trace or MessageData trace
@param  extension extension of the trace file to be created
@param  fullpath_out char pointer to hold the output full path name of the file , it should be large enough to hold the output.
@param  max size of fullpath_out char array.
@retval mqtt_success in case of succesess.
@retval mqtt_error_no_enough_memory if memory can't be allocated to hold any char pointer required.
@retval mqtt_error_invalid_parameter brokerIP is NULL or empty.
@retval mqtt_error_cant_create_filepath is the function failed to concatinate the path parts due to failure in sprintf
*/
enum mqtt_status_enum mqtt_trace_getfilePath(char const *path, char const *brokerIP, char const *tag, char const *extension, char *fullpath_out,  int size);

/**
Adapter to allow ctime_s behaviour to be used on both Windows and Linux.
*/
void mqtt_ctime_s(const time_t *clock, char *buffer, int len);

/**
Helper function to log into stdout or stderr in case of logging to files fails.
@param  file where to log the error , if file = NULL the logs goes to stdout
@param  tag string passed to fprintf format parameter
@param  ferr error code happned during failed file operation
*/
void mqtt_log_critical_error(FILE *errorfile, char const *tag,int ferr);
/**
Function to get the creation time of the given trace file.
If stamp file exists find the 1st recorded message time , create a new time stamp file and write current time into it.
@param filepath full path for file to calculate its creation time
@param result pointer to mqtt_status_enum varialbe to hold result which may be mqtt_succes or any other mqtt_status_enum member expressing errors
@Return creation time in seconds
*/
enum mqtt_status_enum mqtt_trace_get_file_creationtime(char const* filepath, mqtt_time_t *output);


/**
This helper function configure the logfile creation time stamp , it reads the time stamp file and returns it into output time stamp varialbe.
<p>
If the time stam file doesn't exists it careates a new file and writes current time to it.

@param outputstamp is pointer to int variable that will hold the final time stamp , in case of failure it will contain -1
@retval mqtt_success on success
@retval mqtt_error_no_enough_memory in case of failure to allocate memory for any string
@retval mqtt_error_invalid_parameter if any part of file name (brokerIP , path , tag ) is NULL
@retval mqtt_error_cant_create_filepath faile during path parts concatnation.
@retval mqtt_error_failed_to_read_from_file if failed to read from existing time stamp file
@retval mqtt_error_unable_to_create_file failed to create a new .timestamp file
@retval mqtt_error_failed_to_write_to_the_file in case of failure to write the new time into newly created .timestamp file
*/
int mqtt_configure_timestamp(char const *brokerIP,char const *path, char const *tag, mqtt_time_t *outputstamp);

/**
Function to check if the file needs to be rolled and if so it makes the rolling else do nothing just return success
@param file_creation_time the current time stamp of the file to be cheked for rolling
@param file_rolling_period the period to keep the logs before rolling
@param current_file_path current file to be checked for rolling
@retval mqtt_success.
@retval mqtt_error_string_concat_error faile during string parts concatnation.
@retval mqtt_error_cannot_rename_file error due to i/o failure during rename of the old trace file
@retval mqtt_error_invalid_parameter if the current_file_path deosn't have correct name as per file name format specifications
*/
enum mqtt_status_enum mqtt_check_do_rolling(mqtt_time_t* file_creation_time, long file_rolling_period, char const *current_file_path);

/**
*   Converts the time_t which is cause cross platform issues to mqtt_time_t which is aware of cross platform issues
*/
mqtt_time_t time_t_to_mqtt_time_t(time_t t);

/**
 * Utility function to check validity of UTF-8 string
 * @param UTF-8 string
 * @param UTF-8 string length
 * @return 1 - if string is valid utf8
 *
 */
int u8_isvalid(const char *str, size_t length);

/**
 * Utility function to convert UTF-8 string to Hex
 * @param input string to be converted to hex value
 * @param length of input string
 * @param output hex string
 * @param max length of output hex string
 * @return mqtt status enum
 */
enum mqtt_status_enum toHex(unsigned char* input, size_t inputLen, char* output, size_t outputLen);

#endif
