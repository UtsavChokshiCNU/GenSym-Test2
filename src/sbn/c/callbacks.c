/*
  GSI callbacks
 */

#include <stdio.h>
#include "g2sbn.h"

/* Utility functions */
extern void gsi_show_callback(); 
extern void gsi_show_registered_items(); 
extern void gsi_report_error(char *msg, gsi_call_identifier_type call_id);
extern void gsi_return_int(int val, gsi_call_identifier_type call_id);

#define TCPIP_PORT_NUMBER  0

sbn_t SBN; /* global for GSI callbacks */

gsi_function_handle_type sbn_app_message_callback; /* needed for GSI-to-G2 call */

gsi_int sbn_context; /* only one G2 connection is supported */

/**
 * sets the main loop delay
 * @param delay in milliseconds
 */
static declare_gsi_rpc_local_fn(set_forever_loop_wait_time);

/**
 * sets period of heartbeat messages in loop cycles
 * @param period in loop cycles
 */
static declare_gsi_rpc_local_fn(set_heartbeat_timeout_cycles);

/**
 * Subscribe to application message
 * @param message id
 */
static declare_gsi_rpc_local_fn(rpc_sbn_subscribe);

/**
 * Unsubscribe to application message
 * @param message id
 */
static declare_gsi_rpc_local_fn(rpc_sbn_unsubscribe);

/**
 * Send application message
 * @param message id
 * @param command
 * @param payload
 * @param payload size
 */
static declare_gsi_rpc_local_fn(send_app_message);

sbn_status_t app_message_callback(SBN_MsgId_t id, void *payload, int size)
{
    gsi_int buf[SBN_MAX_MSG_SIZE];
    unsigned char *msg = (unsigned char *)payload;
    int i;
    gsi_item *callback_args;

    if (payload == NULL && size != 0) {
        SBN_Log(SBN_MODULE, &SBN, SBN_ERROR_LEVEL, SBN_NULL_POINTER_EID,
                "payload is NULL but its size is not zero");
        return SBN_ERROR;
    }

    if (size < 0) {
        SBN_Log(SBN_MODULE, &SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "payload size is negative");
        return SBN_ERROR;
    }

    if (size > SBN_MAX_MSG_SIZE) {
        SBN_Log(SBN_MODULE, &SBN, SBN_ERROR_LEVEL, SBN_MISC_ERROR_EID,
                "payload size is %d, which is greater than max size %d",
                size, SBN_MAX_MSG_SIZE);
        return SBN_ERROR;
    }

    if (sbn_context == -1) {
        return SBN_SKIP;
    }
    
    /* In the G2 CORBA mapping, octet is mapped to integer, 
       so we have a precedent and do the same here.
       It's not too bad, as the total message size is below usual value of 
       MTU - Maximum Transmission Unit, that is, less than 1500 bytes */
    for (i=0; i<size; i++) { 
        buf[i] = msg[i];
    }

    callback_args = gsi_make_items(2);
    gsi_set_int(callback_args[0], id);
    gsi_set_class_name(callback_args[1], "INTEGER-ARRAY");
    gsi_set_int_array(callback_args[1], buf, size);
    gsi_rpc_start(sbn_app_message_callback,callback_args,0);
    gsi_reclaim_items(callback_args);
    
    return SBN_OK;
}

void send_app_message(gsi_item *arguments, gsi_int count, gsi_call_identifier_type call_id)
{
    int max_ccsds_header_size = sizeof(CCSDS_CmdPkt_t) > sizeof(CCSDS_TlmPkt8_t) ? sizeof(CCSDS_CmdPkt_t) : sizeof(CCSDS_TlmPkt8_t);
    int max_payload_size = SBN_MAX_MSG_SIZE - sizeof(SBN_NetMsgHeader_t) - max_ccsds_header_size;
    char error_msg[256];
    snprintf(error_msg, 256, "Invalid arguments, usage: uint16, uint16, int*, int; max payload size is %d bytes", max_payload_size);
    error_msg[255] = 0;
    
    if ((count == 4) &&
        (gsi_int_of(arguments[0]) > -1) &&
        (gsi_int_of(arguments[0]) < 65536) &&
        (gsi_int_of(arguments[1]) > -1) &&
        (gsi_int_of(arguments[1]) < 65536) &&
        (gsi_type_of(arguments[2]) == GSI_INTEGER_ARRAY_TAG) &&
        (gsi_int_of(arguments[3]) > -1) &&
        (gsi_int_of(arguments[3]) < max_payload_size))  {
        
        SBN_MsgId_t id = gsi_int_of(arguments[0]);
        uint16_t command = gsi_int_of(arguments[1]);
        gsi_int* ints = gsi_int_array_of(arguments[2]);
        int size = gsi_int_of(arguments[3]);
        unsigned char buf[SBN_MAX_MSG_SIZE];
        int i;
        
        /* In the G2 CORBA mapping, octet is mapped to integer, 
           so we have a precedent and do the same here.
           It's not too bad, as the total message size is below usual value of 
           MTU - Maximum Transmission Unit, that is, less than 1500 bytes */
        for (i=0; i<size; i++) { 
            buf[i] = (unsigned char)ints[i];
        }
        gsi_return_int(SBN_SendAppMessage(&SBN, id, command, buf, size),
                       call_id);
    } else {
        gsi_report_error(error_msg, call_id);
    }
}

void set_forever_loop_wait_time(gsi_item *arguments, gsi_int count, gsi_call_identifier_type call_id)
{
    if ((count == 1) && (gsi_int_of(arguments[0]) > 0)) {
        gsi_return_int(SBN.MainLoopDelay, call_id);
        SBN.MainLoopDelay = gsi_int_of(arguments[0]);
        SBN_Log(SBN_MODULE, &SBN, SBN_DEBUG_LEVEL, SBN_CMD_EID, "SET-LOOP_WAIT-TIME called from G2: val=%d", SBN.MainLoopDelay);
    } else {
        gsi_report_error("Invalid arguments, should be one positive integer - delay in milliseconds", call_id);
    }
}

void set_heartbeat_timeout_cycles(gsi_item *arguments, gsi_int count, gsi_call_identifier_type call_id)
{
    if ((count == 1) && (gsi_int_of(arguments[0]) > 0)) {
        gsi_return_int(SBN.TimeoutCycles, call_id);
        SBN.TimeoutCycles = gsi_int_of(arguments[0]);
        SBN_Log(SBN_MODULE, &SBN, SBN_DEBUG_LEVEL, SBN_CMD_EID, "SET-HEARTBEAT-TIMEOUT-CYCLES called from G2: val=%d", SBN.TimeoutCycles);
    } else {
        gsi_report_error("Invalid arguments, should be one positive integer - period in cycles", call_id);
    }
}

void rpc_sbn_subscribe(gsi_item args[], gsi_int count, gsi_call_identifier_type call_id)
{
    int msg_id;
    if (count != 1) {
        gsi_report_error("Invalid arguments, should be one positive integer - message Id", call_id);
        return;
    }

    msg_id = gsi_int_of(args[0]);
    SBN_Log(SBN_MODULE, &SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "SUBSCRIBE called from G2: msg_id=%d", msg_id);
    if (SBN_Subscribe(&SBN, msg_id) != SBN_OK) {
        gsi_report_error("SBN Subscribe failed", call_id);
        gsi_return_int(SBN_ERROR, call_id);
        return;
    }

    gsi_return_int(SBN_OK, call_id);
}

void rpc_sbn_unsubscribe(gsi_item *args, gsi_int count, gsi_call_identifier_type call_id)
{
    int msg_id;
    if (count != 1) {
        gsi_report_error("Invalid arguments, should be one positive integer - message Id", call_id);
        return;
    }

    msg_id = gsi_int_of(args[0]);
    SBN_Log(SBN_MODULE, &SBN, SBN_DEBUG_LEVEL, SBN_PAYLOAD_MSG_EID, "UNSUBSCRIBE called from G2: msg_id=%d", msg_id);

    if (SBN_Unsubscribe(&SBN, msg_id) != SBN_OK) {
        gsi_report_error("SBN Subscribe failed", call_id);
        gsi_return_int(SBN_ERROR, call_id);
        return;
    }

    gsi_return_int(SBN_OK, call_id);
}

void gsi_return_int(int val, gsi_call_identifier_type call_id)
{
    gsi_item *return_value_pointer = gsi_make_items(1);
    gsi_set_int(*return_value_pointer, val);
    gsi_rpc_return_values(return_value_pointer, 1, call_id, gsi_current_context());
    gsi_reclaim_items(return_value_pointer);
}

void gsi_report_error(char *msg, gsi_call_identifier_type call_id)
{
    gsi_item *error_transient_gsi_items = gsi_make_array(2);
    gsi_item gsierror_sym = gsi_make_item();
    gsi_item gsierror_str = gsi_make_item();
    error_transient_gsi_items[0] = gsierror_sym;
    gsi_set_sym(gsierror_sym, gsi_make_symbol ("RPC-ERROR"));
    error_transient_gsi_items[1] = gsierror_str;
    gsi_set_str(gsierror_str, msg);
    gsi_rpc_return_error_values(error_transient_gsi_items, 2, call_id, gsi_current_context());
    gsi_reclaim_array (error_transient_gsi_items);
    gsi_reclaim_item (gsierror_sym);
    gsi_reclaim_item (gsierror_str);
}

void gsi_set_up ()
{
    gsi_set_option(GSI_ONE_CYCLE);
    gsi_rpc_declare_local(set_forever_loop_wait_time,
              "SET-FOREVER-LOOP-WAIT-TIME");
    gsi_rpc_declare_local(set_heartbeat_timeout_cycles,
              "SET-HEARTBEAT-TIMEOUT-CYCLES");
    gsi_rpc_declare_local(rpc_sbn_subscribe, "RPC-SBN-SUBSCRIBE");
    gsi_rpc_declare_local(rpc_sbn_unsubscribe, "RPC-SBN-UNSUBSCRIBE");
    gsi_rpc_declare_local(send_app_message, "SEND-APP-MESSAGE");
}

gsi_int gsi_get_tcp_port()
{
    return(TCPIP_PORT_NUMBER);
}

gsi_int gsi_initialize_context(gsi_char *remote_process_init_string, gsi_int length)
{
    gsi_rpc_declare_remote(&sbn_app_message_callback,
                           "SBN-APP-MESSAGE-CALLBACK", NULL, 2, 0,
                           gsi_current_context());
    sbn_context = gsi_current_context();
    return (GSI_ACCEPT);
}


void gsi_receive_registration(item_registration)
    gsi_registration item_registration;
{
    gsi_show_callback("gsi_receive_registration");
    printf("   handle: %ld\n", gsi_handle_of(item_registration));
}

void gsi_receive_deregistrations(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
    gsi_show_registered_items("gsi_receive_deregistrations", 
                              registered_items, count);
}

void gsi_get_data(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
    gsi_show_registered_items("gsi_get_data", 
                              registered_items, count);
}

void gsi_set_data(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
    gsi_show_registered_items("gsi_set_data", 
                              registered_items, count);
}

void gsi_pause_context()
{
    gsi_show_callback("gsi_pause_context");
}

void gsi_resume_context()
{
    gsi_show_callback("gsi_resume_context");
}

void gsi_shutdown_context()
{
    gsi_show_callback("gsi_shutdown_context");
    sbn_context = -1;
}

void gsi_g2_poll()
{
    gsi_show_callback("gsi_g2_poll");
}

void gsi_receive_message(message, length)
    gsi_char     *message;
    gsi_int      length;
{
    gsi_show_callback("gsi_receive_message");
    printf("message from G2:%s\n",message);
}

/* --------------------------------------------------------- */

/* Utility functions used in this file, to aid in debugging. */

void gsi_show_callback(name)
    char *name;
{
    printf("%s: context %ld\n",name,gsi_current_context());
}

void gsi_show_registered_items(name, registered_items, count)
    char                 *name;
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
    printf("%s: context %ld\n",name,gsi_current_context());
    if (0 < count) {
      int i;
      printf("   handles: ");
      printf("%ld",gsi_handle_of(registered_items[0]));
      for(i=1; i< count; i++) printf(",%ld",gsi_handle_of(registered_items[i]));
      printf("\n");
    }
}

