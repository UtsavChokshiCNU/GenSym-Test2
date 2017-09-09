/*****************************************************************************
:
:  gw_main.h  --  Include file used by gw_main.c
:
:  Copyright (C) 1986-2017 Gensym Corporation.
:  52 Second Avenue, Burlington, MA  01803
:  All rights reserved.
:
:...........................................................................*/


#ifndef __GW_MAIN_INCLUDED__
#  define __GW_MAIN_INCLUDED__

#include "gsi_main.h"


#ifdef WIN32
#  include <stdlib.h>
#else
#  include <unistd.h>
#endif

/*
#define gw_socket_write                g2int_gw_socket_write
#define gw_socket_read                 g2int_gw_socket_read
*/

#define GC_SILENCE g2rtl_Gc_silence
#define GSI_INSTALL_ERROR_HANDLER gsi_install_error_handler
#define GSI_RPC_DECLARE_LOCAL gsi_rpc_declare_local_plain
#define GSI_RPC_DECLARE_REMOTE gsi_rpc_declare_remote_plain
#define GW_ERROR_HANDLER gw_error_handler
#define INNER_INITIALIZE_CONTEXT inner_initialize_context
#define KICK_BRIDGE_TASKS g2int_kick_bridge_tasks
#define SHUTDOWN_BRIDGE g2int_shutdown_bridge
#define SHUTDOWN_REQUESTED G2int_shutdown_requested
#define STARTUP_BRIDGE g2int_startup_bridge

extern gsi_int SHUTDOWN_REQUESTED;
extern void *GC_SILENCE;


extern long g2pvt_tcpip_connect();

/* stage1(), stage2() in gsi_brg.c: */ 
extern short int stage1();
extern short int stage2();
extern short int periodic();
extern int gw_flush_console_streams();
extern char *gw_version_info();
extern void zgw_configure_bridge();
extern void zgw_ping();
extern void zgw_kill_bridge();
extern void zgw_decline_to_serve_url();
extern void zgw_set_url_reply_charset();
extern void zgw_add_to_url_reply();
extern void zgw_finish_url_reply();
extern void zgw_get_attribute_of_request();
extern void zgw_start_http_server();
extern void zgw_tender_resources();
extern void zgw_make_base64_encoded();
extern void zgw_set_header_field();

extern int GW_ERROR_HANDLER();
extern long INNER_INITIALIZE_CONTEXT();
extern void KICK_BRIDGE_TASKS(); 
extern void SHUTDOWN_BRIDGE();
extern void STARTUP_BRIDGE();

extern long my_gsi_get_tcp_port();
extern long my_gsi_pause_context();
extern long my_gsi_resume_context();
extern long my_gsi_g2_poll();
extern long my_gsi_receive_registration(/* Object registration */);
extern long my_gsi_receive_deregistrations(/* Object registration_item_array, long count_1 */);
extern long my_gsi_get_data(/* Object registration_item_array, long count_1 */);
extern long my_gsi_set_data(/* Object registration_item_array, long count_1 */);
extern long my_gsi_receive_message(/* Object message, long length_1 */);
extern long my_inner_initialize_context();
extern long my_gsi_shutdown_context();


#endif /* ifdef __GW_MAIN_INCLUDED__ */
