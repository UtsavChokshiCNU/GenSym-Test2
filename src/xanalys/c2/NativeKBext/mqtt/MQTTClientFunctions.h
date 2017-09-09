#ifndef MQTT_CLIENT_FUNCTIONS_H
#define MQTT_CLIENT_FUNCTIONS_H

#include "common_config.h"
#include "runtime.h"

Object XANALYS_API G2InitializeMQTTClientAndConnectToBroker(
    Object flags, 
    Object rollingLogsLimit,
    Object userName, 
    Object password,
    Object lastWillTopic,
    Object lastWillQos,
    Object lastWillMessage,
    Object keepAlive);

Object XANALYS_API G2ConnectToBroker(
    Object handle,
    Object flags, 
    Object userName, 
    Object password,
    Object lastWillTopic,
    Object lastWillQos,
    Object lastWillMessage,
    Object keepAlive);

Object XANALYS_API G2SetLoggingProperties(
    Object handle,
    Object controlPacketLogging,
    Object messageDataLogging,
    Object rollingLogsLimit);

Object XANALYS_API G2MqttPoll(
    Object handle);

Object XANALYS_API G2DisconnectFromBroker(
    Object handle);

Object XANALYS_API G2PublishToBroker(
    Object handle,
    Object packetId,
    Object topicName,
    Object qos,
    Object retainFlag,
    Object payload,
    Object dupFlag);

#endif
