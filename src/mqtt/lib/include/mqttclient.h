#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "mqttSocket.h"
#include "mqttSessionTrace.h"
#include "mqttDataTrace.h"

// MQTT Connection stores last message type
#define MQTT_MSG_CONNECT                            (1<<4)
#define MQTT_MSG_CONNACK                            (2<<4)
#define MQTT_MSG_DISCONNECT                         (14<<4)

// Flags to prepare CONNECT message for sending to Broker
#define MQTT_CLEAN_SESSION                          (1<<1)
#define MQTT_WILL_FLAG                              (1<<2)
#define MQTT_WILL_RETAIN                            (1<<5)
#define MQTT_USERNAME_FLAG                          (1<<7)
#define MQTT_PASSWORD_FLAG                          (1<<6)

// Length limits
#define FIXED_HEADER_SIZE                           2
#define MQTT_BROKER_ADDRESS_LENGTH                  45
#define MQTT_CLIENT_ID_LENGTH                       64
#define MQTT_USERNAME_LENGTH                        13 // MQTT Specification (12 '\0')
#define MQTT_PASSWORD_LENGTH                        13 // MQTT Specification (12 '\0')
#define MQTT_TOPIC_LENGTH                           13 // MQTT Specification (12 '\0')
#define MQTT_MESSAGE_LENGTH                         13 // MQTT Specification (12 '\0')

// Invalid context handle
#define MQTT_INVALID_CONTEXT                        -1

// CONNACK packet length
#define MQTT_CONNACK_PACKET_LENGTH                  4

// Invalid packet type
#define MQTT_INAVLID_PACKET                         -1

// Do not poll socket
#define MQTT_DONTPOLL_SOCKET                        -1

// Protocol state is used to set mqtt protocol state.
enum mqtt_protocol_state {
    MQTT_STATE_INITIAL,                             // Socket is not opened yet
    MQTT_STATE_CONNECTING,                          // Socket in connecting state
    MQTT_STATE_CONNECTED,                           // Socket is connected
    MQTT_STATE_DISCONNECTED,                        // Socket opened before but is now disconnected
    MQTT_STATE_AWAIT_CONNACK,                       // MQTT protocol awaiting CONNACK            
    MQTT_STATE_CONNACK_RECEIVED,                    // MQTT protocol CONNACK received
    MQTT_STATE_PUBLISH,                             // MQTT protocol awaiting PUBACK
    MQTT_STATE_DISCONNECT_SENT                      // MQTT protocol DISCONNECT sent
};

// Events enum can be either RECEIVED_EVENT or SENT_EVENT
enum mqtt_protocol_event {
    MQTT_EVENT_RECEIVED,
    MQTT_EVENT_SENT
};

#define MQTT_MAX_BUFFER_LENGTH                      1024

// MQTT Broker struct
typedef struct MQTTBroker {
    /**
     * MQTT Broker ip address.
     *
     */
    char brokerAddress[MQTT_BROKER_ADDRESS_LENGTH];
    /**
     * MQTT Broker ip port.
     *
     */
    int brokerPort;
    /**
     * MQTT Client id.
     *
     */
    char clientId[MQTT_CLIENT_ID_LENGTH];
    /**
     * MQTT Connection timeout value.
     *
     */
    uint8_t connectionTimeout;
    /**
     * MQTT protocol clean session.
     *
     */
    uint8_t cleanSession;
    /**
     * MQTT auto reconnection support.
     *
     */
    uint8_t autoReconnect;
    /**
     * MQTT max number of messages inflight.
     *
     */
    uint8_t maxInflightMessages;
    /**
     * MQTT protocol version.
     *
     */
    uint8_t mqttVersion;
    /**
     * MQTT control packet logging enabled or disabled.
     *
     */
    uint8_t controlPacketLogging;
    /**
     * MQTT date packet logging enabled or disabled.
     *
     */
    uint8_t messageDataLogging;
    /**
     * MQTT control and data packet rolling logs limit in days.
     *
     */
    uint8_t rollingLogsLimit;
    /**
     *
     *
     */
    uint8_t ackTimeLimit;
    //Auth fields
    /**
     * MQTT Broker username.
     *
     */
    char username[MQTT_USERNAME_LENGTH];
    /**
     * MQTT Broker password.
     *
     */
    char password[MQTT_PASSWORD_LENGTH];
    //SSL/TLS - 1.2 version support only
    /**
     * SSL protocol for secure communictation with MQTT broker.
     *
     */
    uint8_t sslTls;
    // LWT fields
    /**
     * MQTT protocol - Last Will Topic QoS.
     *
     */
    uint8_t lwtQos;
    /**
     * MQTT protocol - Last Will Topic.
     *
     */
    char lwtTopic[MQTT_TOPIC_LENGTH];
    /**
     * MQTT protocol - Last Will Message.
     *
     */
    char lwtMessage[MQTT_MESSAGE_LENGTH];
    /**
     * MQTT protocol - Last Will Topic retain enabled or disabled.
     *
     */
    uint8_t lwtRetain;
} broker_t;

// MQTT Protocol FSM states
typedef struct MQTTProtocol {
    /**
     * Current MQTT protocol state.
     *
     */
    enum mqtt_protocol_state protocolState;
} protocol_data_t;

// MQTT Connection struct
typedef struct MQTTConnection {
    /**
     * Socket on which connection is establised.
     *
     */
    int socket;
    /**
     * Whether session with the MQTT broker is setup.
     *
     */
    uint8_t sesionPresent;
} connection_t;

// Buffer data for socket polling
typedef struct MQTTBufferData {
    /**
     * Socket on which connection is establised.
     *
     */
    int socket;
    /**
     * Receive buffer stores the buffer until recv() completes.
     *
     */
    char receiveBuffer[MQTT_MAX_BUFFER_LENGTH];
    /**
     * Offset into receive buffer.
     *
     */
    int receiveOffset;
    /**
     * Send buffer stores the buffer until send() completes.
     *
     */
    char sendBuffer[MQTT_MAX_BUFFER_LENGTH];
    /**
     * Offset into send buffer.
     *
     */
    int sendOffset;
} buffer_data_t;

// MQTT Context struct
typedef struct MQTTContext {
    /**
     * Handle to MQTT Context object.
     *
     */
    intptr_t MQTTHandle;
    /**
     * MQTT Broker object.
     *
     */
    broker_t* mqttBroker;
    /**
     * MQTT Connection object.
     *
     */
    connection_t* mqttConnection;
    /**
     * MQTT control packet logging parameters.
     *
     */
    mqtt_pts_t packet_params;
    /**
     * MQTT data packet logging parameters.
     *
     */
    mqtt_dtp_t data_params;
} context_t;

/**
 * Create MQTT Context creates context which stores following information
 *    1. Broker properties including clientId, username, password and others
 *    2. Connection properties including socket and connection state
 *
 * Unique handle is set to refer to each context. Each context would represent
 * multiple broker connections (in future).
 *
 * @param context struct
 * @param broker struct
 * @param connection struct
 * @return mqtt status enum
 * 
 */
enum mqtt_status_enum CreateMQTTContext(struct MQTTContext* mctx, struct MQTTBroker* mbroker, struct MQTTConnection* mconnection);

/**
 * Poll open sockets to check if there is any activity.
 *
 */
int G2MqttPoll(struct MQTTContext* mctx);

/**
 * Convenience function to create new context and connect to broker.
 *
 */
long G2InitializeMQTTClientAndConnectToBroker(uint8_t flags, uint8_t rollingLogsLimit, 
    const wchar_t* userName, const wchar_t* password, 
    const wchar_t* lastWillTopic, uint8_t lastWillQos, const wchar_t* lastWillMessage, int keepAlive);

/**
 * Send DISCONNECT packet to MQTT Broker
 *
 */
int G2DisconnectFromBroker(long contextHandle);

/**
 * Send PUBLISH message to MQTT Broker
 *
 */
int G2PublishToBroker(long handle, int packetId, wchar_t* topicName, int qos, int retainFlag, wchar_t* payload, int dupFlag);

/**
 * Send PUBLISH message to MQTT Broker
 *
 */
int G2PublishToBroker(long handle, int packetId, wchar_t* topicName, int qos, int retainFlag, wchar_t* payload, int dupFlag);

/**
 * Connect to broker.
 *
 */
long G2ConnectToBroker(long handle, uint8_t flags, const wchar_t* userName, const wchar_t* password, 
    const wchar_t* lastWillTopic, uint8_t lastWillQos, const wchar_t* lastWillMessage, int keepAlive);

/**
 * Internal function to optionally create context and connect to broker.
 *
 */
long InitializeMQTTClientAndConnectToBroker(struct MQTTContext* ctx, long handle, uint8_t flags, uint8_t rollingLogsLimit,
    const wchar_t* userName, const wchar_t* password,
    const wchar_t* lastWillTopic, uint8_t lastWillQos, const wchar_t* lastWillMessage, int keepAlive);

/**
 * Sets broker connection logging properties.
 *
 */
long G2SetLoggingProperties(long handle, uint8_t controlPacketLogging, uint8_t messageDataLogging, uint8_t rollingLogsLimit);

/**
 * Frees up any malloc'd memory and closes MQTT log file.
 *
 * @param none
 * @return mqtt status enum
 */
enum mqtt_status_enum closeMQTTClient(void);

/**
 * Helper function to check whether context is valid.
 *
 */
enum mqtt_status_enum isContextValid(struct MQTTContext* ctx);

/**
 * Connects to MQTT broker with the specified parameters.
 *
 * @param context struct
 * @param client id
 * @param clean session - can be 0 or 1
 * @param user name
 * @param password
 * @param last will topic
 * @param last will QoS
 * @param last will message
 * @param last will retain
 * @param keep alive
 * @return mqtt status enum
 *
 */
enum mqtt_status_enum ConnectToBroker(struct MQTTContext* ctx, long handle, const char* clientId, 
    uint8_t cleanSession, const char* userName, const char* password, 
    const char* lastWillTopic, uint8_t lastWillQos, const char* lastWillMessage, uint8_t lastWillRetain, int keepAlive);

/**
 * Sends DISCONNECT packet to MQTT broker.
 * @param handle to MQTT context
 * @return mqtt status enum
 *
 */
enum mqtt_status_enum DisconnectFromBroker(long handle);

/**
 * Handle broker response
 * @param context handle
 * @param control packet type - can be CONNECT, CONNACK, PUBLISH etc.
 * @return mqtt status enum
 */
enum mqtt_status_enum MqttFSM(int handle, enum mqtt_protocol_event mqttEvent, uint8_t controlPacketType);

/**
 * Process CONNACK response
 * @param context handle
 */
enum mqtt_status_enum ProcessConnack(int handle);

/*
 * Helper function to encode CONNECT packet.
 *
 * @param encoded packet to return
 * @param length of encoded packet 
 * @param client id
 * @param client id length
 * @param clean session
 * @param user name
 * @param user name length
 * @param password
 * @param password length
 * @param last will topic
 * @param last will topic length
 * @param last will QoS
 * @param last will message
 * @param last will message length
 * @param last will retain
 * @param keep alive
 * @return mqtt status enum
 */
enum mqtt_status_enum EncodeConnectPacket(uint8_t* encodedPacket, int* encodedPacketlength, const char* clientId, size_t clientIdLength, 
    uint8_t cleanSession, const char* userName, size_t userNameLength, const char* password, size_t passwordLength, 
    const char* lastWillTopic, size_t lwtTopicLength, uint8_t lastWillQos, const char* lastWillMessage, size_t lwtMessageLength, 
    uint8_t lastWillRetain, int keepAlive);

/**
 * Buffer remaining data for sending to MQTT Broker.
 * @param mqtt socket
 * @param mqtt buffer for passed in handle
 * @param number of bytes sent over socket already
 * @param length of bytes to be sent
 */
enum mqtt_status_enum BufferRemainingData(int mqttSocket, buffer_data_t* bufferPtr, int bytesSent, int length);

/*
 * Check if all pending data is received for packet bytes received so far.
 * @param context handle
 * @return control packet type
 */
uint8_t checkIfPacketDataReceived(int handle);

#endif
