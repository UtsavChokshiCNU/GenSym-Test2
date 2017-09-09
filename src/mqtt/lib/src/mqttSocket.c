#include "mqttSocket.h"

void CleanupWinSock() 
{
#if defined _WIN32
    WSACleanup();
#endif
}

// Initialize socket
enum mqtt_status_enum initSocket()
{
#if defined _WIN32
    WSADATA wsaData;
    int result_code = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result_code != 0)
    {
        return mqtt_error_socket_initialization;
    }
#endif
    return mqtt_success;
}

// Create non-blocking socket
enum mqtt_status_enum createSocket(int* mqttSocket)
{
    u_long mode = 1L;

    int flags = 0;
    int return_code = 0;

    *mqttSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*mqttSocket < 0)
    { 
        //socket creation failed
        closesocket(*mqttSocket);
        CleanupWinSock();
        return mqtt_error_socket_creation;
    }

    // TODO - Should we disable Nagle algorithm?
    // setsockopt(*mqttSocket, IPPROTO_TCP, TCP_NODELAY, (const char*) &mode, 1);

#if defined _WIN32
    return_code = ioctlsocket(*mqttSocket, FIONBIO, &mode);
    if (return_code != NO_ERROR)
    {
        closesocket(*mqttSocket);
        CleanupWinSock();
        return mqtt_error_socket_mode;
    }
#else
    if (flags = fcntl(*mqttSocket, F_GETFL, 0))
    {
        flags = 0;
    }
    return_code = fcntl(*mqttSocket, F_SETFL, flags | O_NONBLOCK);
    if (return_code == SOCKET_ERROR)
    {
        return mqtt_error_socket_mode;
    }
#endif

    return mqtt_success;
};

// Connect to server
enum mqtt_status_enum connectToServer(int mqttSocket, const char* ipAddress, int port)
{
    int return_code;

    struct sockaddr_in socketAddress;
    memset(&socketAddress, 0, sizeof(socketAddress));
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = inet_addr(ipAddress); // Broker IP address
    socketAddress.sin_port = htons(port); // Broker port

    return_code = connect(mqttSocket, (struct sockaddr *) &socketAddress, sizeof(socketAddress));
    if ((return_code < 0) && (checkSocketError(return_code) != mqtt_success)) 
    {
        closesocket(mqttSocket); // Failed to connect 
        return mqtt_error_socket_connect;
    }
    return mqtt_success;
};

// Send to server
enum mqtt_status_enum sendToServer(int mqttSocket, const char* inputString, int length, int* bytesSent)
{
    int return_code = send(mqttSocket, inputString, length, 0);
    if (return_code != length)
    {
        if (checkSocketError(return_code) != mqtt_success) 
        {
            // Socket error
            closesocket(mqttSocket); 
            return mqtt_error_socket_send;
        }
    }
    *bytesSent = return_code;

    return mqtt_success;
};

// Receive from server
enum mqtt_status_enum receiveFromServer(int mqttSocket, char* receivedBytes, int* length)
{
    int bytesReceived = recv(mqttSocket, receivedBytes, MQTT_MAX_RECEIVE_LENGTH - 1, 0);
    if ((bytesReceived < 0) && (checkSocketError(bytesReceived) != mqtt_success)) 
    {
        closesocket(mqttSocket);
        return mqtt_error_socket_receive;
    }
    *length = bytesReceived;
    return mqtt_success;
}

// Close socket
enum mqtt_status_enum closeSocket(int mqttSocket)
{
    int result = closesocket(mqttSocket);

    if ( (result != 0) && (checkSocketError(result) != mqtt_success) )
    {
        return mqtt_error_socket_close;
    }
    return mqtt_success;
};

// Check valid error
enum mqtt_status_enum checkSocketError(int returnCode)
{
    int error_code;

#if defined _WIN32
    error_code = WSAGetLastError();
#else
    error_code = errno;
#endif

    if (returnCode != 0 && error_code != EINTR && error_code != EINPROGRESS && error_code != EAGAIN && error_code != EWOULDBLOCK)
    {
        return mqtt_error_socket_error;
    }

    return mqtt_success;
}
