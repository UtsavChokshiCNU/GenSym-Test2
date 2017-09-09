#ifndef MQTT_SOCKET_H
#define MQTT_SOCKET_H

#include <stdio.h>

#if defined _WIN32

#include <WinSock2.h>
#include <WS2tcpip.h>

#define poll WSAPoll

#undef EAGAIN
#define EAGAIN WSAEWOULDBLOCK
#undef EINTR
#define EINTR WSAEINTR
#undef EINPROGRESS
#define EINPROGRESS WSAEINPROGRESS
#undef EWOULDBLOCK
#define EWOULDBLOCK WSAEWOULDBLOCK

#else

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>

#define closesocket close
#define INVALID_SOCKET SOCKET_ERROR

#endif

#if !defined(SOCKET_ERROR)
    /** error in socket operations */
    #define SOCKET_ERROR -1
#endif

#include "mqtt_constants.h"

// Max number of sockets supported
#define MQTT_MAX_ACTIVE_SOCKETS                     1024
#define MQTT_DEFAULT_WAIT                           60000
#define MQTT_MAX_SEND_LENGTH                        1024
#define MQTT_MAX_RECEIVE_LENGTH                     1024

static int socketCount = 0;

static FILE* logFile = NULL;

 /**
 * Initialize socket library.
 *
 */
enum mqtt_status_enum initSocket();

/**
 * Cleanup Windows sockets.
 */
void CleanupWinSock();

/**
 * Create socket.
 *
 */
enum mqtt_status_enum createSocket(int* mqttSocket);

/**
 * Connect to server.
 *
 */
enum mqtt_status_enum connectToServer(int mqttSocket, const char* ipAddress, int port);

/**
 *Send to server.
 *
 */
enum mqtt_status_enum sendToServer(int mqttSocket, const char* inputString, int length, int* bytesSent);

/**
 * Receive from server.
 *
 */
enum mqtt_status_enum receiveFromServer(int mqttSocket, char* receivedBytes, int* length);

/**
 *Close socket.
 *
 */
enum mqtt_status_enum closeSocket(int mqttSocket);

/*
 * Check valid error
 *
 */
enum mqtt_status_enum checkSocketError(int returnCode);

#endif
