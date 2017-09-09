/***************************************************************************
 *
 *		Callbacks.c
 *
 *			Contains the required GSI callback functions. Several are
 *			not used in this project, but must be implemented in order
 *			to keep the compiler and linker happy.
 *
 *		Feel free to use this code as is, or modified to suit your needs.
 *		Although this software has been extensively tested, Gensym cannot
 *		guarantee error-free performance in all applications.  Accordingly,
 *		use of the software is at the customer's sole risk.
 *
 *		This file has been imported and converted from earlier an earlier
 *		version written in ANSI C.
 *
 ***************************************************************************/



#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdarg.h>
#include	<errno.h>
#include	<malloc.h>
#include	<math.h>
#include	<time.h>

#include	<sys/types.h>
#include	<signal.h>

#include	"G2Agent.h"


#ifdef	__cplusplus
extern "C" {
#endif

	gsi_int gsi_get_tcp_port(void);
	void gsi_set_up(void);
	gsi_int gsi_initialize_context(gsi_char *remote_process_init_string, gsi_int length);
	void gsi_shutdown_context(void);
	void gsi_pause_context(void);
	void gsi_resume_context(void);
	void gsi_receive_registration(gsi_registration item_registration);
	void gsi_receive_deregistrations(gsi_registered_item registered_items[], gsi_int count);
	void gsi_get_data(gsi_registered_item registered_items[], gsi_int count);
	void gsi_set_data(gsi_registered_item registered_items[], gsi_int count);
	void gsi_g2_poll(void);
	void gsi_receive_message(gsi_char *message, gsi_int length);

#ifdef	__cplusplus
}
#endif


/*-------------------------------------------------------------------------*
 *
 *	Variable definition
 *
 *-------------------------------------------------------------------------*/

gsi_item	*local_gsi_itemP;
FILE		*f_ptrs[MAX_FPTRS];


/*-------------------------------------------------------------------------*
 *
 *	This is our GSI error handler. We can use it to log all errors.
 *
 *-------------------------------------------------------------------------*/

void G2_ip_error_handler(gsi_int error_context,
						 gsi_int error_code, char *error_message)
{
	gsi_item	*itemP		= gsi_make_items(2);
	gsi_char	msg[2048];

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_ip_error_handler().\n");

	sprintf(msg, "Error in context %d ; code = %d, Message = %s\n", error_context, error_code, error_message);
	log_with_timestamp(LOG_MODE_DEBUG, "GSI INTERNAL ERROR. %s\n", msg);

	if (G2_Context >= 0 && G2_is_paused == FALSE) {

		gsi_set_sym( itemP[0], "GSI-INTERNAL-ERROR");
		gsi_set_str( itemP[1], msg);

		gsi_rpc_start(G2_error_handler, itemP, G2_Context);
	}

	gsi_reclaim_items(itemP);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_ip_error_handler().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	This is our default RPC call receiver. It does peform any task
 *
 *-------------------------------------------------------------------------*/

void G2_rpc_call_receiver(gsi_item args[], gsi_int count)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering g2_rpc_call_receiver().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  g2_rpc_call_receiver().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Called upon startup to query the desired TCP/IP port
 *	GSI should be listen on.
 *
 *-------------------------------------------------------------------------*/

gsi_int gsi_get_tcp_port(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_get_tcp_port().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_get_tcp_port(). Returning: %d\n\n", TCPIP_PORT_NUMBER);

    return(TCPIP_PORT_NUMBER);
}



/*-------------------------------------------------------------------------*
 *
 *	Called upon startup for an initial setup after some internal
 *	GSI information has been setup.
 *
 *-------------------------------------------------------------------------*/

void gsi_set_up(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_set_up().\n");

	/*
	 *	Setup some default and re-usage variables
	 */
	G2_Context			= -1;
	G2_is_paused		= FALSE;

	local_gsi_itemP		= gsi_make_items( _NB_LOCAL_GSI_ITEMS );


	/*
	 *	Define our GSI error handler and select the single mode
	 */
	gsi_install_error_handler( G2_ip_error_handler );
	gsi_set_option( GSI_ONE_CYCLE | GSI_STRING_CHECK);
	gsi_set_pause_timeout(50);

	/*
	 *	Declare the local Remote Procedure Calls G2 may call
	 */
    gsi_rpc_declare_local(rpc_exit,							"GDSM-AGENT-RPC-EXIT");
    gsi_rpc_declare_local(rpc_ping,							"GDSM-AGENT-RPC-PING");

    gsi_rpc_declare_local(rpc_fopen_append,					"GDSM-AGENT-RPC-OPEN-FILE-FOR-APPEND");
    gsi_rpc_declare_local(rpc_fopen_read,					"GDSM-AGENT-RPC-OPEN-FILE-FOR-READ");
    gsi_rpc_declare_local(rpc_fopen_read_write,				"GDSM-AGENT-RPC-OPEN-FILE-FOR-READ-AND-WRITE");
    gsi_rpc_declare_local(rpc_fopen_write,					"GDSM-AGENT-RPC-OPEN-FILE-FOR-WRITE");
    gsi_rpc_declare_local(rpc_fclose,						"GDSM-AGENT-RPC-CLOSE-FILE");
    gsi_rpc_declare_local(rpc_fclose_all,					"GDSM-AGENT-RPC-CLOSE-ALL-FILES");
    gsi_rpc_declare_local(rpc_fread,						"GDSM-AGENT-RPC-READ-FROM-FILE");
    gsi_rpc_declare_local(rpc_freadline,					"GDSM-AGENT-RPC-READ-LINE-FROM-FILE");
    gsi_rpc_declare_local(rpc_fwrite,						"GDSM-AGENT-RPC-WRITE-TO-FILE");
    gsi_rpc_declare_local(rpc_fseek,						"GDSM-AGENT-RPC-FILE-SEEK");
    gsi_rpc_declare_local(rpc_fstats,						"GDSM-AGENT-RPC-FILE-STATS");
    gsi_rpc_declare_local(rpc_fdelete,						"GDSM-AGENT-RPC-DELETE-FILE");
    gsi_rpc_declare_local(rpc_frename,						"GDSM-AGENT-RPC-RENAME-FILE");

    gsi_rpc_declare_local(rpc_create_directory,				"GDSM-AGENT-RPC-CREATE-DIRECTORY");
    gsi_rpc_declare_local(rpc_directory_exists,				"GDSM-AGENT-RPC-DIRECTORY-EXIST");

    gsi_rpc_declare_local(rpc_spawn_process,				"GDSM-AGENT-RPC-SPAWN-PROCESS");
    gsi_rpc_declare_local(rpc_kill_process,					"GDSM-AGENT-RPC-KILL-PROCESS");
    gsi_rpc_declare_local(rpc_process_exists,				"GDSM-AGENT-RPC-PROCESS-EXISTS");

    gsi_rpc_declare_local(rpc_add_log_event_source,			"GDSM-AGENT-RPC-ADD-LOG-EVENT-SOURCE");
    gsi_rpc_declare_local(rpc_log_error_event,				"GDSM-AGENT-RPC-LOG-ERROR-EVENT");
    gsi_rpc_declare_local(rpc_log_warning_event,			"GDSM-AGENT-RPC-LOG-WARNING-EVENT");
    gsi_rpc_declare_local(rpc_log_information_event,		"GDSM-AGENT-RPC-LOG-INFORMATION-EVENT");
    gsi_rpc_declare_local(rpc_get_log_info,					"GDSM-AGENT-RPC-GET-LOG-INFO");
    gsi_rpc_declare_local(rpc_get_log_entries,				"GDSM-AGENT-RPC-GET-LOG-ENTRIES");
	
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_set_up().\n\n");
}



/*-------------------------------------------------------------------------*
 *
 *	Called each time a G2 KB requests a connections to this GSI
 *
 *-------------------------------------------------------------------------*/

gsi_int gsi_initialize_context(char *remote_process_init_string, gsi_int length)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_initialize_context().\n");

	/*
	 *	In this application, we only accept one conenction per bridge.
	 */
	if (G2_Context >= 0) {

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_initialize_context(). Denied additional G2 connection.\n\n");
		return (GSI_REJECT);
	}

	/*
	 *	And ensure the desired conenction context is valid
	 */
	if ((G2_Context = gsi_current_context()) < -1) {

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_initialize_context(). Denied G2 connection with invalid context.\n\n");
		return (GSI_REJECT);
	}


	/*
	 *	Declate the Remote Procedure Calls GSI may call
	 */
	gsi_rpc_declare_remote(	&G2_error_handler,
							"_GDSM-AGENT-RPC-CB-ERROR-HANDLER",
							G2_rpc_call_receiver, 2, 0, G2_Context);


	/*
	 *	And accept the connection
	 */
	log_with_timestamp(LOG_MODE_ENTRY_EXIT,
		"Leaving  gsi_initialize_context(). Accepted new G2 connection. Context: %d\n",
		G2_Context);


	return (GSI_ACCEPT);
}



/*-------------------------------------------------------------------------*
 *
 *	Called each time a G2 KB requests a disconnect from this GSI
 *
 *-------------------------------------------------------------------------*/

void gsi_shutdown_context(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_shutdown_context().\n");

	if (G2_Context != gsi_current_context()) {

		log_with_timestamp(LOG_MODE_DEBUG,      "Shutdown for not connected and current context.\n");
		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_shutdown_context().\n\n");
		return;
	}


	/*
	 *	Reset context status
	 */
	G2_Context			= -1;
	G2_is_paused		= FALSE;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_shutdown_context().\n\n");
}



/*-------------------------------------------------------------------------*
 *
 *	Called each time the G2 KB is paused
 *
 *-------------------------------------------------------------------------*/

void gsi_pause_context(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_pause_context().\n");

	G2_is_paused = TRUE;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_pause_context().\n\n");
}



/*-------------------------------------------------------------------------*
 *
 *	Called each time the G2 KB is resumed
 *
 *-------------------------------------------------------------------------*/

void gsi_resume_context(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_resume_context().\n");

	G2_is_paused = FALSE;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_resume_context().\n\n");
}




/*-------------------------------------------------------------------------*
 *
 *	The following GSI callbacks are not used in this application.
 *	Only stub functions are defined to keep the compiler/linker happy.
 *
 *-------------------------------------------------------------------------*/

void gsi_receive_registration(gsi_registration item_registration)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_receive_registration().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_receive_registration().\n\n");
}


void gsi_receive_deregistrations(gsi_registered_item registered_items[], gsi_int count)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_receive_deregistrations().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_receive_deregistrations().\n\n");
}


void gsi_get_data(gsi_registered_item registered_items[], gsi_int count)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_get_data().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_get_data().\n\n");
}


void gsi_set_data(gsi_registered_item registered_items[], gsi_int count)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_set_data().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_set_data().\n\n");
}


void gsi_g2_poll(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_g2_poll().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_g2_poll().\n\n");
}


void gsi_receive_message(char *message, gsi_int length)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_receive_message().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_receive_message().\n\n");
}
