#ifndef MQTT_CONSTANTS_H
#define MQTT_CONSTANTS_H
#define MQTTClient_Release_Ver "01"

/**
*   Enumeration of MQTT status codes
*/
enum mqtt_status_enum {
    /**
    *   Called operation finished successfully.
    */
    mqtt_success,
    /**
    * Failed to create a new file due to fopen failure.
    */
    mqtt_error_unable_to_create_file,
    /**
    *   Some tracing API being called without initializing the session structure by calling correct mqtt_trace_make api
    */
    mqtt_error_trace_not_initialized,
    /*
     * Log file not initialized
     */
    mqtt_error_log_not_initialized,
    /**
    *   Failed to allocate memory.
    */
    mqtt_error_no_enough_memory,
    /**
    *   Call done to some trace writing API while the logging is switched off
    */
    mqtt_error_trace_turned_off,
    /**
    *   Failed to write to file due to i/o operation failure
    */
    mqtt_error_failed_to_write_to_the_file,
    /**
    *   Invalid parameter passed to an API call.
    */
    mqtt_error_invalid_parameter,
    /**
    *   Content of stamp file contains invalid data
    */
    mqtt_error_invalid_content_of_stamp_file,
    /**
    *   Failed to read from file due to i/o operation failure
    */
    mqtt_error_failed_to_read_from_file,
    /**
    *   Error while calling sprintf to concatinate to strings
    */
    mqtt_error_string_concat_error,
    /**
    *   Failed to rename old file during rolling
    */
    mqtt_error_cannot_rename_file,
    /**
    *   Failed to delete old log/trace file
    */
    mqtt_error_cannot_remove_file,
    /**
    *   File is not valid time stamp file
    */
    mqtt_error_invalid_timestamp_file,
    /**
    *   Error happened when doing sprintf to create trace file path from file path parts.
    */
    mqtt_error_cant_create_filepath,
    /*
     * Socket initialization failure
     */
    mqtt_error_socket_initialization,
    /**
     * Socket create failure
     */
    mqtt_error_socket_creation,
    /**
     * Socket non-blocking mode failure
     */
    mqtt_error_socket_mode,
    /**
     * Could not connect on socket
     */
    mqtt_error_socket_connect,
    /**
     * Connect is still pending
     */
    mqtt_error_socket_pending,
    /**
     * Could not send on socket
     */
    mqtt_error_socket_send,
    /**
     * Represents SOCKET_ERROR case
     */
    mqtt_error_socket_error,
    /**
     * Could not receive on socket
     */
    mqtt_error_socket_receive,
    /**
     * Could not poll socket
     */
    mqtt_error_socket_poll,
    /**
     * Invalid server response
     */
    mqtt_error_invalid_server_response,
    /**
     * Unsolicited CONNACK response
     */
    mqtt_error_unsolicited_connack,
    /*
     * Encoded packet is larger than max length
     */
    mqtt_error_packet_overflow,
    /**
     * Invalid context
     */
    mqtt_error_context_invalid,
    /**
     * Connack message has error
     */
    mqtt_error_message_connack,
    /**
     * Socket close has error
     */
    mqtt_error_socket_close,
    /**
     * Socket connection already closed
     */
    mqtt_error_socket_closed,
    /*
     * Received message is not complete, expected more data
     */
    mqtt_error_data_pending,
    /**
     * Invalid mqtt protocol state
     */
    mqtt_error_protocol_invalid,
    /*
     * Publish message exceeds max allowable length
     */
    mqtt_error_message_too_long
};

typedef double mqtt_time_t;
#define MQTT_TIME_PRINTF_FORMAT "%f"

#ifdef _WIN32
#define PATH_LENGTH 260
#define PATH_SEP    '\\'
#include <io.h>
#define F_OK    0
#define access _access
#define snprintf _snprintf
#else
#include <unistd.h>
#include <errno.h>
#define PATH_SEP    '/'
#define PATH_LENGTH 260
#endif
#endif
