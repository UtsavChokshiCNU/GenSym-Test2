#include "MQTTClientFunctions.h"

Object XANALYS_API G2InitializeMQTTClientAndConnectToBroker(
    Object flags, 
    Object rollingLogsLimit,
    Object userName, 
    Object password,
    Object lastWillTopic,
    Object lastWillQos,
    Object lastWillMessage,
    Object keepAlive)
{
    return NIL;
}

Object XANALYS_API G2ConnectToBroker(
    Object handle,
    Object flags, 
    Object userName, 
    Object password,
    Object lastWillTopic,
    Object lastWillQos,
    Object lastWillMessage,
    Object keepAlive)
{
    return NIL;
}

Object XANALYS_API G2SetLoggingProperties(
    Object handle,
    Object controlPacketLogging,
    Object messageDataLogging,
    Object rollingLogsLimit)
{
    return NIL;
}

Object XANALYS_API G2MqttPoll(
    Object handle)
{
    return NIL;
}

Object XANALYS_API G2DisconnectFromBroker(
    Object handle)
{
    return NIL;
}

Object XANALYS_API G2PublishToBroker(
    Object handle,
    Object packetId,
    Object topicName,
    Object qos,
    Object retainFlag,
    Object payload,
    Object dupFlag)
{
    return NIL;
}
