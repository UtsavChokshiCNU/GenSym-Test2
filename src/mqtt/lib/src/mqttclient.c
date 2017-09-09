#include "mqttclient.h"

#define MQTT_SECONDS_IN_DAYS                        86400
#define MQTT_CLIENT_LOG_FILENAME                    "mqttclient.log"
#define DEFAULT_BROKER_IP_ADDRESS                   "127.0.0.1"
#define DEFAULT_BROKER_PORT_NUMBER                  1883
#define DEFAULT_CONTROL_PACKET_PATH                 ""
#define DEFAULT_DATA_PACKET_PATH                    ""

static volatile int initialized = 0;

static int numSockets;
static context_t mqttContexts[MQTT_MAX_ACTIVE_SOCKETS];
static buffer_data_t mqttBuffers[MQTT_MAX_ACTIVE_SOCKETS];
static protocol_data_t mqttProtocols[MQTT_MAX_ACTIVE_SOCKETS];

static struct pollfd fdArray[MQTT_MAX_ACTIVE_SOCKETS];

static broker_t mqttBroker;
static connection_t mqttConnection;

enum mqtt_status_enum CreateMQTTContext(struct MQTTContext* ctx, struct MQTTBroker* mbroker, struct MQTTConnection* mconnection)
{
    int length = 0;

    enum mqtt_status_enum return_code;

    if (ctx == NULL) 
    {
        return mqtt_error_context_invalid;
    }

    ctx->MQTTHandle = (intptr_t) ctx;
    ctx->mqttBroker = mbroker;
    ctx->mqttConnection = mconnection;
    ctx->mqttConnection->socket = INVALID_SOCKET;

    // Set default values for broker ip and port
    length = strlen(DEFAULT_BROKER_IP_ADDRESS);
    strncpy(mbroker->brokerAddress, DEFAULT_BROKER_IP_ADDRESS, length);
    mbroker->brokerAddress[length] = '\0'; //NUL terminate
    mbroker->brokerPort = DEFAULT_BROKER_PORT_NUMBER;

    if (!initialized) 
    {
        //Initialize Socket only once
        return_code = initSocket();
        if (return_code != mqtt_success) 
        {
            return return_code;
        }
        initialized = 1;

        // Initialize client log file for all contexts
        logFile = fopen(MQTT_CLIENT_LOG_FILENAME, "ab+");

        if ((NULL == logFile) || (errno == ENOENT))
        {
            return mqtt_error_log_not_initialized;
        }
    }

    // Save the create context with connection details and store it
    // N.B. - Even though new context is created, it is not valid until valid socket is also associated with the context object.
    // Code must check if the context is valid, before using the context by calling isContextValid helper function.
    mqttContexts[numSockets] = *ctx;

    if (logFile != NULL)
    {
        fprintf(logFile, "New MQTT context has been created\n");
    }

    return mqtt_success;
}

long G2InitializeMQTTClientAndConnectToBroker(uint8_t flags, uint8_t rollingLogsLimit, 
    const wchar_t* userName, const wchar_t* password, 
    const wchar_t* lastWillTopic, uint8_t lastWillQos, const wchar_t* lastWillMessage, int keepAlive)
{
    int context_handle;
    enum mqtt_status_enum return_code;

    context_handle = InitializeMQTTClientAndConnectToBroker(NULL, numSockets, flags, rollingLogsLimit, userName, password, lastWillTopic,
        lastWillQos, lastWillMessage, keepAlive);

    return_code = MqttFSM(context_handle, MQTT_EVENT_SENT, MQTT_MSG_CONNECT);

    if (return_code == mqtt_success)
    {
        return context_handle;
    }
    else
    {
        return MQTT_INVALID_CONTEXT;
    }
}

long G2ConnectToBroker(long handle, uint8_t flags, const wchar_t* userName, const wchar_t* password, 
    const wchar_t* lastWillTopic, uint8_t lastWillQos, const wchar_t* lastWillMessage, int keepAlive)
{
    int context_handle;
    enum mqtt_status_enum return_code;

    context_t* ctx = &mqttContexts[handle];

    if (isContextValid(ctx) != mqtt_success)
    {
        return MQTT_INVALID_CONTEXT;
    }

    context_handle = InitializeMQTTClientAndConnectToBroker(ctx, handle, flags, ctx->mqttBroker->rollingLogsLimit, userName, password, lastWillTopic,
        lastWillQos, lastWillMessage, keepAlive);

    return_code = MqttFSM(handle, MQTT_EVENT_SENT, MQTT_MSG_CONNECT);

    if (return_code == mqtt_success)
    {
        return context_handle;
    }
    else
    {
        return MQTT_INVALID_CONTEXT;
    }
}

long InitializeMQTTClientAndConnectToBroker(struct MQTTContext* ctx, long handle, uint8_t flags, uint8_t rollingLogsLimit,
    const wchar_t* userName, const wchar_t* password,
    const wchar_t* lastWillTopic, uint8_t lastWillQos, const wchar_t* lastWillMessage, int keepAlive)
{
    uint8_t   cleanSession;
    uint8_t   controlPacketLogging;
    uint8_t   messageDataLogging;
    uint8_t   lastWillRetain;

    size_t userNameLen = wcslen(userName);
    size_t passwordLen = wcslen(password);
    size_t lastWillTopicLen = wcslen(lastWillTopic);
    size_t lastWillMessageLen = wcslen(lastWillMessage);

    char c_userName[MQTT_USERNAME_LENGTH * 2] = "";
    char c_password[MQTT_PASSWORD_LENGTH * 2] = "";
    char c_lastWillTopic[MQTT_TOPIC_LENGTH * 2] = "";
    char c_lastWillMessage[MQTT_MESSAGE_LENGTH * 2] = "";

    cleanSession = flags & 0x1;
    lastWillRetain = (flags >> 3) & 0x1;

    if (isContextValid(ctx) != mqtt_success)
    {
        // Create MQTTContext
        ctx = &mqttContexts[numSockets];
        CreateMQTTContext(ctx, &mqttBroker, &mqttConnection);

        controlPacketLogging = (flags >> 1) & 0x1;
        messageDataLogging = (flags >> 2) & 0x1;

        ctx->MQTTHandle = (intptr_t) ctx;
        //Set logging options in the context
        ctx->mqttBroker->controlPacketLogging = controlPacketLogging;
        ctx->mqttBroker->messageDataLogging = messageDataLogging;
        ctx->mqttBroker->rollingLogsLimit = rollingLogsLimit;
    }

    if (ctx->mqttBroker->controlPacketLogging == 1) 
    {
        mqtt_trace_session_turnOn(&(ctx->packet_params));
        ctx->packet_params = mqtt_make_packet_trace_params(DEFAULT_BROKER_IP_ADDRESS, DEFAULT_CONTROL_PACKET_PATH, 
            rollingLogsLimit * MQTT_SECONDS_IN_DAYS);
    }
    else
    {
        mqtt_trace_session_turnOff(&(ctx->packet_params));
    }

    if (messageDataLogging == 1) 
    {
        ctx->data_params = mqtt_make_topic_data_trace(DEFAULT_BROKER_IP_ADDRESS, DEFAULT_DATA_PACKET_PATH, 
            rollingLogsLimit * MQTT_SECONDS_IN_DAYS);
        mqtt_trace_data_turnOn(&(ctx->data_params));
    }
    else
    {
        mqtt_trace_data_turnOff(&(ctx->data_params));
    }

    if (userNameLen != 0) 
    {
        memset(c_userName, 0, userNameLen * 2);
        wcstombs(c_userName, userName, userNameLen);
    }
    if (passwordLen != 0) 
    {
        memset(c_password, 0, passwordLen * 2);
        wcstombs(c_password, password, passwordLen);
    }
    if (lastWillTopicLen != 0) 
    {
        memset(c_lastWillTopic, 0, lastWillTopicLen * 2);
        wcstombs(c_lastWillTopic, lastWillTopic, lastWillTopicLen);
    }
    if (lastWillMessageLen != 0) 
    {
        memset(c_lastWillMessage, 0, lastWillMessageLen * 2);
        wcstombs(c_lastWillMessage, lastWillMessage, lastWillMessageLen);
    }

    // Send connect to MQTT broker
    // TODO - Client id needs to be generated dynamically or will it be sent by KB? Need to finalize this
    // Does the client id uniquely identify G2 instance? Or can user send an arbitratry value of clientId?
    ConnectToBroker(ctx, handle, "cid1", cleanSession, c_userName, c_password, 
        c_lastWillTopic, lastWillQos, c_lastWillMessage, lastWillRetain, keepAlive);

    // Safe to send numSocket as handle
    return (numSockets - 1);
}

enum mqtt_status_enum closeMQTTClient(void)
{
    // Log file will be closed
    if (initialized == 1 && logFile != NULL)
    {
        CleanupWinSock();
        fclose(logFile);
        logFile = NULL;
    }
    return mqtt_success;
}

long G2SetLoggingProperties(long handle, uint8_t controlPacketLogging, uint8_t messageDataLogging, uint8_t rollingLogsLimit)
{
    context_t* ctx = &mqttContexts[handle];

    ctx->mqttBroker->controlPacketLogging = controlPacketLogging;
    ctx->mqttBroker->messageDataLogging = messageDataLogging;
    ctx->mqttBroker->rollingLogsLimit = rollingLogsLimit;

    if (ctx->mqttBroker->controlPacketLogging == 1)
    {
        mqtt_trace_session_turnOn(&(ctx->packet_params));
    }
    else
    {
        mqtt_trace_session_turnOff(&(ctx->packet_params));
    }

    if (ctx->mqttBroker->messageDataLogging == 1)
    {
        mqtt_trace_data_turnOn(&(ctx->data_params));
    }
    else
    {
        mqtt_trace_data_turnOff(&(ctx->data_params));
    }

    return handle;
}

int G2MqttPoll(struct MQTTContext* mctx)
{
    int i = 0;
    int result = 0;
    int bytes_sent = 0;
    int received_message_length = 0;

    uint8_t control_packet_type = 0;

    enum mqtt_status_enum return_code;

    if (!initialized)
    {
        return mqtt_success;
    }

    // Poll each socket created so far
    result = poll(fdArray, numSockets, 0);
    if (result == SOCKET_ERROR)
    {
        return mqtt_error_socket_poll;
    }

    if (logFile != NULL)
    {
        fprintf(logFile, "Polled [%d] sockets on pollFDArray successfully\n", numSockets);
    }

    if (result > 0)
    {
        for (i = 0; i < numSockets; i++) 
        {
            if (fdArray[i].revents & POLLOUT)
            {
                // Set connection state to connected
                if (mqttProtocols[i].protocolState == MQTT_STATE_CONNECTING)
                {
                    mqttProtocols[i].protocolState = MQTT_STATE_CONNECTED;
                }

                if (mqttBuffers[i].sendOffset > 0)
                {
                    //Send data
                    return_code = sendToServer(fdArray[i].fd, mqttBuffers[i].sendBuffer, mqttBuffers[i].sendOffset, &bytes_sent);
                    if (return_code != mqtt_success)
                    {
                        return mqtt_error_socket_send;
                    }
                    else
                    {
                        if (bytes_sent > 0)
                        {
                            if (logFile != NULL)
                            {
                                fprintf(logFile, "Sent remaining data of length=[%d] on socket=[%d]\n", 
                                    mqttBuffers[i].sendOffset, fdArray[i].fd);
                            }

                            mqttBuffers[i].sendOffset -= bytes_sent;

                            // Send offset cannot be negative
                            assert(mqttBuffers[i].sendOffset < 0);

                            memmove(mqttBuffers[i].sendBuffer, &(mqttBuffers[i].sendBuffer) + bytes_sent, bytes_sent);

                            // If all data is sent, we check for pending actions
                            // In case of DISCONNECT packet, pending function to call is closeSocket()
                            if (mqttBuffers[i].sendOffset == 0)
                            {
                                MqttFSM(i, MQTT_EVENT_SENT, MQTT_MSG_DISCONNECT);
                            }
                        } 
                    }
                }
            }
            if (fdArray[i].revents & POLLIN)
            {
                //Receive data
                return_code = receiveFromServer(fdArray[i].fd, mqttBuffers[i].receiveBuffer + mqttBuffers[i].receiveOffset, 
                    &received_message_length);

                if (return_code != mqtt_success)
                {
                    return return_code;
                }

                // Assert the max receive buffer size before proceeding
                assert((mqttBuffers[i].receiveOffset + received_message_length) <= sizeof(mqttBuffers[i].receiveBuffer));

                mqttBuffers[i].receiveOffset += received_message_length;

                if (logFile != NULL)
                {
                    fprintf(logFile, "Received remaining data of length=[%d] on socket=[%d]\n", received_message_length, fdArray[i].fd);
                }
                
                // If the chunk size is less than max receive length, we have received all data
                control_packet_type = checkIfPacketDataReceived(i);
                if ((received_message_length < MQTT_MAX_RECEIVE_LENGTH) && (control_packet_type != MQTT_INAVLID_PACKET))
                {
                    {
                        return_code = MqttFSM(i, MQTT_EVENT_RECEIVED, control_packet_type);
                        if (return_code != mqtt_success)
                        {
                            return return_code;
                        }
                    }
                }
            }
        }
    }

    return mqtt_success;
}

enum mqtt_status_enum DisconnectFromBroker(long handle)
{
    int length = 2; // DISCONNECT packet is 2 bytes
    int bytes_sent = 0;
    int mqtt_socket = INVALID_SOCKET;

    enum mqtt_status_enum return_code;

    buffer_data_t* buffer_ptr = &(mqttBuffers[handle]);
    struct MQTTContext* ctx = &(mqttContexts[handle]);

    mqtt_socket = ctx->mqttConnection->socket;

    if (isContextValid(ctx) != mqtt_success)
    {
        // Connection already closed
        return mqtt_error_socket_closed;
    }

    // Default size = one byte Message Type + one byte Remaining Length
    buffer_ptr->sendBuffer[0] = MQTT_MSG_DISCONNECT;
    buffer_ptr->sendBuffer[1] = 0;

    buffer_ptr->sendOffset = length;

    if (logFile != NULL)
    {
        fprintf(logFile, "Buffering [%d] byte(s) of CONNECT packet on socket=[%d]\n", length, mqtt_socket);
    }

    //Send DISCONNECT message to MQTT broker
    return_code = sendToServer(ctx->mqttConnection->socket, (const char*) buffer_ptr->sendBuffer, length, &bytes_sent);
    if (return_code != mqtt_success) 
    {
        return return_code;
    }

    if (logFile != NULL)
    {
        fprintf(logFile, "Sending DISCONNECT packet on socket=[%d]\n", length, mqtt_socket);
    }

    //Log DISCONNECT control packet
    if (ctx->packet_params.isON == 1) 
    {
        mqtt_trace_packet_DISCONNECT(&(ctx->packet_params));
    }

    return_code = BufferRemainingData(mqtt_socket, buffer_ptr, bytes_sent, length);
    if (return_code == mqtt_error_data_pending)
    {
        return mqtt_success;
    }
    
    //Close socket
    return_code = closeSocket(mqtt_socket);
    if (return_code != mqtt_success) 
    {
        return return_code;
    }
    else
    {
        fdArray[handle].fd = MQTT_DONTPOLL_SOCKET;
        ctx->mqttConnection->socket = INVALID_SOCKET;

        if (logFile != NULL)
        {
            fprintf(logFile, "Socket=[%d] is now closed\n", length, mqtt_socket);
        }
    }

    return mqtt_success;
}

int G2DisconnectFromBroker(long handle)
{
    enum mqtt_status_enum return_code = DisconnectFromBroker(handle);

    if (return_code == mqtt_success)
    {
        return MqttFSM(handle, MQTT_EVENT_SENT, MQTT_MSG_DISCONNECT);
    }

    return return_code;
} 

int G2PublishToBroker(long handle, int packetId, wchar_t* topicName, int qos, int retainFlag, wchar_t* payload, int dupFlag)
{
    char c_topicName[MQTT_TOPIC_LENGTH];
    char c_payload[MQTT_MAX_BUFFER_LENGTH];

    context_t* ctx = &(mqttContexts[handle]);

    size_t topicNameLen = wcslen(topicName);
    size_t payloadLen = wcslen(payload);

    if (topicNameLen != 0) 
    {
        memset(c_topicName, 0, topicNameLen * 2);
        wcstombs(c_topicName, topicName, topicNameLen);
    }

    if (payload != 0) 
    {
        memset(c_payload, 0, payloadLen * 2);
        wcstombs(c_payload, payload, payloadLen);
    }

    if (ctx->mqttBroker->controlPacketLogging == 1) 
    {
        mqtt_trace_packet_PUBLISH(&(ctx->packet_params), dupFlag, qos, c_topicName, packetId, c_payload);
    }

    if (ctx->mqttBroker->messageDataLogging == 1) 
    {
        mqtt_tdt_published(&(ctx->data_params), c_topicName, qos, c_payload);
    }

    return mqtt_success;
}

/* MQTT 3.1.1 Spec    - http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html#_Toc398718028
 * Fixed header       - 2 bytes
 * Variable header    - 10 bytes
 * Payload            - 2 bytes data (Data length MSB, Data Length LSB, Data) ClientId
 * Payload            - 2 bytes data (Will Topic, Will Message, Username, Password etc.)
 */
enum mqtt_status_enum ConnectToBroker(struct MQTTContext* ctx, long handle, const char* clientId, 
    uint8_t cleanSession, const char* userName, const char* password, 
    const char* lastWillTopic, uint8_t lastWillQos, const char* lastWillMessage, uint8_t lastWillRetain, int keepAlive)
{
    int length = 0;
    int bytes_sent = 0;
    int mqtt_socket = INVALID_SOCKET;

    buffer_data_t* buffer_ptr = &(mqttBuffers[handle]);

    size_t clientIdLength = strlen(clientId);
    size_t lwtTopicLength = strlen(lastWillTopic);
    size_t lwtMessageLength = strlen(lastWillMessage);
    size_t userNameLength = strlen(userName);
    size_t passwordLength = strlen(password);
    size_t payloadLength = clientIdLength + 2;

    uint8_t encodedPacket[MQTT_MAX_SEND_LENGTH];

    enum mqtt_status_enum return_code;

    if (isContextValid(ctx) != mqtt_success)
    {
        //Create Socket
        return_code = createSocket(&mqtt_socket);
        if (return_code != mqtt_success) 
        {
            return return_code;
        }

        //Connect to Server
        return_code = connectToServer(mqtt_socket, ctx->mqttBroker->brokerAddress, ctx->mqttBroker->brokerPort);

        if (return_code == mqtt_success) 
        {
            mqttProtocols[handle].protocolState = MQTT_STATE_CONNECTED; // socket connected
        }
        else if (return_code == mqtt_error_socket_pending)
        {
            mqttProtocols[handle].protocolState = MQTT_STATE_CONNECTING; // socket connect pending
        }
        else
        {
            return return_code;
        }
    
        fdArray[handle].fd = mqtt_socket;
        fdArray[handle].events = POLLIN|POLLOUT;
        fdArray[handle].revents = 0;

        numSockets++;

        ctx->mqttConnection->socket = mqtt_socket;

        if (logFile != NULL)
        {
            fprintf(logFile, "Created new socket connection=[%d] on socket=[%d]\n", numSockets, mqtt_socket);
        }
    }
    else
    {
        mqtt_socket = ctx->mqttConnection->socket;
    }

    // Set socket and input parameters into MQTT Context object
    strncpy(ctx->mqttBroker->clientId, clientId, clientIdLength);
    ctx->mqttBroker->clientId[clientIdLength] = '\0';
    ctx->mqttBroker->cleanSession = cleanSession;
    strncpy(ctx->mqttBroker->username, userName, userNameLength);
    ctx->mqttBroker->username[userNameLength] = '\0';
    strncpy(ctx->mqttBroker->password, password, passwordLength);
    ctx->mqttBroker->password[passwordLength] = '\0';
    strncpy(ctx->mqttBroker->lwtTopic, lastWillTopic, lwtTopicLength);
    ctx->mqttBroker->lwtTopic[lwtTopicLength] = '\0';
    ctx->mqttBroker->lwtQos = lastWillQos;
    strncpy(ctx->mqttBroker->lwtMessage, lastWillMessage, lwtMessageLength);
    ctx->mqttBroker->lwtMessage[lwtMessageLength] = '\0';
    ctx->mqttBroker->lwtRetain = lastWillRetain;

    return_code = EncodeConnectPacket(encodedPacket, &length, clientId, clientIdLength, cleanSession, userName, userNameLength, 
        password, passwordLength, lastWillTopic, lwtTopicLength, lastWillQos, lastWillMessage, lwtMessageLength, 
        lastWillRetain, keepAlive);

    if (return_code != mqtt_success)
    {
        return return_code;
    }

    // Buffer data and send later
    memcpy(buffer_ptr->sendBuffer, (char*) encodedPacket, length);
    buffer_ptr->sendOffset = length;

    if (logFile != NULL)
    {
        fprintf(logFile, "Buffering [%d] byte(s) of CONNECT packet on socket=[%d]\n", length, mqtt_socket);
    }

    //Send CONNECT message to MQTT broker
    return_code = sendToServer(mqtt_socket, (const char*) encodedPacket, length, &bytes_sent);
    if (return_code != mqtt_success) 
    {
        return return_code;
    }

    if (ctx->packet_params.isON == 1) 
    {
        mqtt_trace_packet_CONNECT(&(ctx->packet_params), clientId, 0, (userNameLength != 0) ? 1 : 0, 
            (passwordLength != 0) ? 1 : 0, lastWillRetain, lastWillQos, (lwtMessageLength != 0) ? 1 : 0, 
            cleanSession, keepAlive, lastWillTopic, lastWillMessage, userName, password);
    }

    return_code = BufferRemainingData(mqtt_socket, buffer_ptr, bytes_sent, length);
    if (return_code == mqtt_error_data_pending)
    {
        return mqtt_success;
    }

    return mqtt_success;
}

enum mqtt_status_enum EncodeConnectPacket(uint8_t* encodedPacket, int* encodedPacketlength, const char* clientId, size_t clientIdLength, 
    uint8_t cleanSession, const char* userName, size_t userNameLength, const char* password, size_t passwordLength, 
    const char* lastWillTopic, size_t lwtTopicLength, uint8_t lastWillQos, const char* lastWillMessage, size_t lwtMessageLength, 
    uint8_t lastWillRetain, int keepAlive)
{
    uint8_t flags = 0x00;

    size_t payloadLength = clientIdLength + 2;

    // Fixed header
    uint8_t fixedHeaderSize = 2; // Default size = one byte Message Type one byte Remaining Length
    uint8_t fixed_header[3]; // Fixed header may be 3 bytes if variable header length and payload length > 127

    size_t remainLen = 0;

    int length = 0;
    int bytes_sent = 0;
    int mqtt_socket = INVALID_SOCKET;

    // Variable header
    uint8_t var_header[] = {
        0x00,0x04,'M','Q','T','T', // Protocol name: MQTT
        0x04, // Protocol version
        flags, // Connect flags, will be set later
        keepAlive>>8, keepAlive &0xFF, // Keep alive
    };


    // Preparing the flags
    if(lwtTopicLength) 
    {
        payloadLength += lwtTopicLength + 2;
        flags |= lastWillRetain << 5;
        flags |= lastWillQos << 4;
        flags |= MQTT_WILL_FLAG;
    }
    if(lwtMessageLength) 
    {
        payloadLength += lwtMessageLength + 2;
    }
    if(userNameLength) 
    {
        payloadLength += userNameLength + 2;
        flags |= MQTT_USERNAME_FLAG;
    }
    if(passwordLength) 
    {
        payloadLength += passwordLength + 2;
        flags |= MQTT_PASSWORD_FLAG;
    }
    if(cleanSession) 
    {
        flags |= MQTT_CLEAN_SESSION;
    }

    remainLen = sizeof(var_header) + payloadLength;
  
    if (remainLen > 127) 
    {
        fixedHeaderSize++; // add an additional byte for Remaining Length
    }
    
    // Message Type
    fixed_header[0] = MQTT_MSG_CONNECT;

    // Assert that remaining length must be at most 2 bytes
    assert(remainLen <= 0xFFFF);

    // Remaining Length
    if (remainLen <= 127) 
    {
        fixed_header[1] = remainLen;
    } 
    else 
    {
        // first byte is remainder (mod) of 128, set the MSB for more bytes
        fixed_header[1] = remainLen % 128 | 0x80;
        fixed_header[2] = remainLen / 128;
    }
    
    var_header[7] = flags; // Connect flags

    memcpy(encodedPacket, fixed_header, fixedHeaderSize);
    length += fixedHeaderSize;
    memcpy(encodedPacket+length, var_header, sizeof(var_header));
    length += sizeof(var_header);

    if ((length + clientIdLength) > MQTT_MAX_SEND_LENGTH)
    {
        return mqtt_error_packet_overflow;
    }
    
    // Client ID - UTF encoded
    encodedPacket[length++] = clientIdLength >> 8;
    encodedPacket[length++] = clientIdLength & 0xFF;
    memcpy(encodedPacket+length, clientId, clientIdLength);
    length += clientIdLength;

    if(lwtTopicLength) 
    {
        if ( (length + lwtTopicLength) > MQTT_MAX_SEND_LENGTH)
        {
            return mqtt_error_packet_overflow;
        }

        // lastWillTopic - UTF encoded
        encodedPacket[length++] = lwtTopicLength >> 8;
        encodedPacket[length++] = lwtTopicLength & 0xFF;

        memcpy(encodedPacket+length, lastWillTopic, lwtTopicLength);
        length += lwtTopicLength;
    }

    if(lwtMessageLength) 
    {
        if ((length + lwtMessageLength) > MQTT_MAX_SEND_LENGTH)
        {
            return mqtt_error_packet_overflow;
        }

        // lastWillMessage - UTF encoded
        encodedPacket[length++] = lwtMessageLength >> 8;
        encodedPacket[length++] = lwtMessageLength & 0xFF;
        memcpy(encodedPacket+length, lastWillMessage, lwtMessageLength);
        length += lwtMessageLength;
    }

    if(userNameLength) 
    {
        if ((length + userNameLength) > MQTT_MAX_SEND_LENGTH)
        {
            return mqtt_error_packet_overflow;
        }

        // Username - UTF encoded
        encodedPacket[length++] = userNameLength >> 8;
        encodedPacket[length++] = userNameLength & 0xFF;
        memcpy(encodedPacket+length, userName, userNameLength);
        length += userNameLength;
    }

    if(passwordLength) 
    {
        if ((length + passwordLength) > MQTT_MAX_SEND_LENGTH)
        {
            return mqtt_error_packet_overflow;
        }

        // Password - UTF encoded
        encodedPacket[length++] = passwordLength >> 8;
        encodedPacket[length++] = passwordLength & 0xFF;
        memcpy(encodedPacket+length, password, passwordLength);
        length += passwordLength;
    }

    *encodedPacketlength = length;

    return mqtt_success;
}

enum mqtt_status_enum isContextValid(struct MQTTContext* ctx)
{
    if ((ctx != NULL) && (ctx->mqttConnection->socket > 0))
    {
        return mqtt_success;
    }
    else
    {
        return mqtt_error_context_invalid;
    }
}

enum mqtt_status_enum MqttFSM(int handle, enum mqtt_protocol_event mqttEvent, uint8_t controlPacketType)
{
    enum mqtt_status_enum return_code;

    protocol_data_t* pd_ptr = &(mqttProtocols[handle]);

    switch (pd_ptr->protocolState)
    {
        case MQTT_STATE_CONNECTED:
            if (controlPacketType == MQTT_MSG_CONNECT)
            {
                pd_ptr->protocolState = MQTT_STATE_AWAIT_CONNACK;
            }
            break;
        case MQTT_STATE_AWAIT_CONNACK:

            if (controlPacketType == MQTT_MSG_CONNACK)
            {
                return_code = ProcessConnack(handle);
                if (return_code == mqtt_success)
                {
                    pd_ptr->protocolState = MQTT_STATE_CONNACK_RECEIVED;
                }
                else
                {
                    return return_code;
                }
            }
            else
            {
                return mqtt_error_protocol_invalid;
            }
            break;
        case MQTT_STATE_CONNACK_RECEIVED:
            // We have either sent or received DISCONNECT, in both cases we will close socket
            if (controlPacketType == MQTT_MSG_DISCONNECT)
            {
                pd_ptr->protocolState = MQTT_STATE_DISCONNECT_SENT;

                // Check if context is valid and socket is still open, if so, it should be closed now
                if (isContextValid(&(mqttContexts[handle])) == mqtt_success)
                {
                    //Close socket
                    return_code = closeSocket(mqttContexts[handle].mqttConnection->socket);
                    if (return_code != mqtt_success) 
                    {
                        return return_code;
                    }
                    else
                    {
                        // Socket is now closed and context is invalidated
                        pd_ptr->protocolState = MQTT_STATE_DISCONNECTED; // Socket closed
                    }
                }
                else
                {
                    // Socket is already closed and context is invalidated
                    pd_ptr->protocolState = MQTT_STATE_DISCONNECTED; // Socket closed
                }
            }
            if (mqttEvent == MQTT_EVENT_RECEIVED)
            {
                return mqtt_error_protocol_invalid;
            }
        // Fall through in case of unsolicited CONNACK, if already in CONNACK_RECEIVED state
        default:
            // Check for unsolicited CONNACK
            if (controlPacketType == MQTT_MSG_CONNACK) 
            {
                if (logFile != NULL)
                {
                    fprintf(logFile, "Connack received, but is unsolicited\n");
                }

                // Stop processing further and return error
                return mqtt_error_unsolicited_connack;
            }
            break;
    }

    return mqtt_success;
}

enum mqtt_status_enum ProcessConnack(int handle)
{
    unsigned short connack_code;

    buffer_data_t* buf = &(mqttBuffers[handle]);
    context_t* ctx = &(mqttContexts[handle]);

    if (buf->receiveOffset == 0) 
    {
        return mqtt_error_invalid_server_response;
    }

    connack_code = buf->receiveBuffer[3];
    ctx->mqttConnection->sesionPresent = buf->receiveBuffer[2] & 0x01;

    if (ctx->packet_params.isON == 1) 
    {
        mqtt_trace_packet_CONNACK(&(ctx->packet_params), ctx->mqttConnection->sesionPresent, connack_code);
    }

    if (connack_code == 0) 
    {
        if (logFile != NULL)
        {
            fprintf(logFile, "Connack received successfully\n");
        }
    } 
    else 
    {
        if (logFile != NULL)
        {
            fprintf(logFile, "Connack processing is not successful, code=[%d]\n", connack_code);
        }
        return mqtt_error_message_connack;
    }

    // CONNACK packet is fully processed, we need to reduce receive offset by processed packet size
    buf->receiveOffset -= MQTT_CONNACK_PACKET_LENGTH;

    // Receive offset cannot be negative
    assert(buf->receiveOffset >= 0);

    return mqtt_success;
}

enum mqtt_status_enum BufferRemainingData(int mqttSocket, buffer_data_t* bufferPtr, int bytesSent, int length)
{

    if (bytesSent == length)
    {
        // All data is sent now
        if (logFile != NULL)
        {
            fprintf(logFile, "Sent remaining data of length=[%d] on socket=[%d]\n", 
                bufferPtr->sendOffset, mqttSocket);
        }

        bufferPtr->sendOffset = 0;
    }
    else if (bytesSent > 0)
    {
        bufferPtr->sendOffset -= bytesSent;

        // Assert if there is no room in buffer
        assert(bufferPtr->sendOffset < 0);

        memmove(bufferPtr->sendBuffer, bufferPtr->sendBuffer + bytesSent, bytesSent);

        if (logFile != NULL)
        {
            fprintf(logFile, "Sent remaining data of length=[%d] on socket=[%d]\n", 
                bufferPtr->sendOffset, mqttSocket);
        }
        return mqtt_error_data_pending;
    }

    return mqtt_success;
}

uint8_t checkIfPacketDataReceived(int handle)
{
    buffer_data_t* buf_ptr = &(mqttBuffers[handle]);

    // If atleast 2 bytes are available, check if remaining length bytes of MQTT packet are received and return the packet type
    if ((buf_ptr->receiveOffset > 2) && (buf_ptr->receiveOffset >= buf_ptr->receiveBuffer[1]))
    {
        // TODO - We need to further check variable length in case of PUBREL packet
        return buf_ptr->receiveBuffer[0];
    }
    return MQTT_INAVLID_PACKET;
}