/* mqttclnt.c
 * Input file:  mqttclient.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "mqttclnt.h"


Object Mqtt_context_handle = UNBOUND;

/* C-G2INITIALIZEMQTTCLIENTANDCONNECTTOBROKER */
Object c_g2initializemqttclientandconnecttobroker(flags,rollinglogslimit,
	    username,password,lastwilltopic,lastwillqos,lastwillmessage,
	    keepalive)
    Object flags, rollinglogslimit, username, password, lastwilltopic;
    Object lastwillqos, lastwillmessage, keepalive;
{
    Object temp;

    x_note_fn_call(241,0);
    temp = 
	    LONG_TO_FIXNUM(G2InitializeMQTTClientAndConnectToBroker(IFIX(flags),
	    IFIX(rollinglogslimit),UBYTE_16_SARRAY_TO_USHORT_PTR(username),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(password),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(lastwilltopic),IFIX(lastwillqos),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(lastwillmessage),IFIX(keepalive)));
    return VALUES_1(temp);
}

/* KB-G2INITIALIZEMQTTCLIENTANDCONNECTTOBROKER */
Object kb_g2initializemqttclientandconnecttobroker(flags,rollinglogslimit,
	    username,password,lastwilltopic,lastwillqos,lastwillmessage,
	    keepalive)
    Object flags, rollinglogslimit, username, password, lastwilltopic;
    Object lastwillqos, lastwillmessage, keepalive;
{
    x_note_fn_call(241,1);
    Mqtt_context_handle = c_g2initializemqttclientandconnecttobroker(flags,
	    rollinglogslimit,username,password,lastwilltopic,lastwillqos,
	    lastwillmessage,keepalive);
    return VALUES_1(Mqtt_context_handle);
}

/* C-G2CONNECTTOBROKER */
Object c_g2connecttobroker(handle,flags,username,password,lastwilltopic,
	    lastwillqos,lastwillmessage,keepalive)
    Object handle, flags, username, password, lastwilltopic, lastwillqos;
    Object lastwillmessage, keepalive;
{
    Object temp;

    x_note_fn_call(241,2);
    temp = LONG_TO_FIXNUM(G2ConnectToBroker(IFIX(handle),IFIX(flags),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(username),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(password),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(lastwilltopic),IFIX(lastwillqos),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(lastwillmessage),IFIX(keepalive)));
    return VALUES_1(temp);
}

/* KB-G2CONNECTTOBROKER */
Object kb_g2connecttobroker(handle,flags,username,password,lastwilltopic,
	    lastwillqos,lastwillmessage,keepalive)
    Object handle, flags, username, password, lastwilltopic, lastwillqos;
    Object lastwillmessage, keepalive;
{
    x_note_fn_call(241,3);
    return c_g2connecttobroker(handle,flags,username,password,
	    lastwilltopic,lastwillqos,lastwillmessage,keepalive);
}

/* KB-G2SETLOGGINGPROPERTIES */
Object kb_g2setloggingproperties(handle,controlpacketlogging,
	    messagedatalogging,rollinglogslimit)
    Object handle, controlpacketlogging, messagedatalogging, rollinglogslimit;
{
    x_note_fn_call(241,4);
    return VALUES_1(LONG_TO_FIXNUM(G2SetLoggingProperties(IFIX(handle),
	    IFIX(controlpacketlogging),IFIX(messagedatalogging),
	    IFIX(rollinglogslimit))));
}

/* MQTT-POLL-WATCHER */
Object mqtt_poll_watcher()
{
    Object temp;

    x_note_fn_call(241,5);
    temp = LONG_TO_FIXNUM(G2MqttPoll(IFIX(Mqtt_context_handle)));
    return VALUES_1(temp);
}

/* C-G2PUBLISHTOBROKER */
Object c_g2publishtobroker(handle,packetid,topicname,qos,retainflag,
	    payload,dupflag)
    Object handle, packetid, topicname, qos, retainflag, payload, dupflag;
{
    Object temp;

    x_note_fn_call(241,6);
    temp = LONG_TO_FIXNUM(G2PublishToBroker(IFIX(handle),IFIX(packetid),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(topicname),IFIX(qos),
	    IFIX(retainflag),UBYTE_16_SARRAY_TO_USHORT_PTR(payload),
	    IFIX(dupflag)));
    return VALUES_1(temp);
}

/* KB-G2PUBLISHTOBROKER */
Object kb_g2publishtobroker(handle,packetid,topicname,qos,retainflag,
	    payload,dupflag)
    Object handle, packetid, topicname, qos, retainflag, payload, dupflag;
{
    x_note_fn_call(241,7);
    return c_g2publishtobroker(handle,packetid,topicname,qos,retainflag,
	    payload,dupflag);
}

/* KB-G2DISCONNECTFROMBROKER */
Object kb_g2disconnectfrombroker(handle)
    Object handle;
{
    x_note_fn_call(241,8);
    return VALUES_1(LONG_TO_FIXNUM(G2DisconnectFromBroker(IFIX(handle))));
}

void mqttclient_INIT()
{
    Object gensymed_symbol;
    Object Qkb_g2disconnectfrombroker;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qkb_g2publishtobroker, Qkb_g2setloggingproperties;
    Object Qkb_g2connecttobroker, Qkb_g2initializemqttclientandconnecttobroker;

    x_note_fn_call(241,9);
    if (Mqtt_context_handle == UNBOUND)
	Mqtt_context_handle = FIX((SI_Long)0L);
    AB_package = STATIC_PACKAGE("AB");
    Qkb_g2initializemqttclientandconnecttobroker = 
	    STATIC_SYMBOL("KB-G2INITIALIZEMQTTCLIENTANDCONNECTTOBROKER",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkb_g2initializemqttclientandconnecttobroker,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qkb_g2initializemqttclientandconnecttobroker,
	    STATIC_FUNCTION(kb_g2initializemqttclientandconnecttobroker,
	    NIL,FALSE,8,8));
    Qkb_g2connecttobroker = STATIC_SYMBOL("KB-G2CONNECTTOBROKER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkb_g2connecttobroker,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qkb_g2connecttobroker,
	    STATIC_FUNCTION(kb_g2connecttobroker,NIL,FALSE,8,8));
    Qkb_g2setloggingproperties = STATIC_SYMBOL("KB-G2SETLOGGINGPROPERTIES",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkb_g2setloggingproperties,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qkb_g2setloggingproperties,
	    STATIC_FUNCTION(kb_g2setloggingproperties,NIL,FALSE,4,4));
    Qkb_g2publishtobroker = STATIC_SYMBOL("KB-G2PUBLISHTOBROKER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkb_g2publishtobroker,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qkb_g2publishtobroker,
	    STATIC_FUNCTION(kb_g2publishtobroker,NIL,FALSE,7,7));
    Qkb_g2disconnectfrombroker = STATIC_SYMBOL("KB-G2DISCONNECTFROMBROKER",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkb_g2disconnectfrombroker,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qkb_g2disconnectfrombroker,
	    STATIC_FUNCTION(kb_g2disconnectfrombroker,NIL,FALSE,1,1));
}
