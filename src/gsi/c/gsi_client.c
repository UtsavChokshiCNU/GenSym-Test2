/*******************************************************************************
:
:  gsi_client.c  --  GSI regression test for GSI Clients connecting to G2s
:
:
:
:  Note, no other modules needed other than the GSI library.
:
:.............................................................................*/

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "gsi_main.h"
#include "gsi_misc.h"


#define TCPIP_PORT_NUMBER          0
#define TIMEOUT_INTERVAL         360 /* six minutes */
#define ARG_CNT                    1
#define RETURN_ARG_CNT             2
#define INITATE_XN_ARG_COUNT       7
#define INTERNAL_INCONSISTENCY     1
#define SEND                       1
#define NO_SEND                    0
#define NO_DATA              9999999
#define SUCCESS                    1
#define CONNECTION_WAIT           10

function_handle_type  g2_proc_index, g2_sys_proc_index;
function_handle_type  g2_kb_proc_returning_item_index, g2_system_rpc_returning_item_index;
gsi_int       response;
gsi_int       set_result;

gsi_rpc_arg  *mod_arg_array;
gsi_rpc_arg  *my_arg_array;
gsi_rpc_arg  *master_arg_array;
gsi_item      passback_item_copy, passback_item_handle; /* items received as arguments */
gsi_item      received_item_copy, received_item_handle; /* items received as return values */
gsi_int       call_index_for_item_receiver_to_return;

char          *hostname_arg, *portnumber_arg;
int           item_copy_received = FALSE, item_handle_received = FALSE;
int           connected_p = FALSE, remote_procedure_done = FALSE;
int           item_is_copy;
gsi_int       open_context_id;

void gsi_initiate_unsolicited_connection_to_g2 
     GSI_API_PROTO((char *host_name, char *port_number));


main(argc, argv)
    int   argc;
    char *argv[];
{
    time_t  time_now;
    time_t  start_time;

/*
 *  Set the version control variables to the values defined in gsi_main.h.
 *  Though optional, this is recommended to ensure version consistency between
 *  the GSI object libraries, and the include files used to compile your 
 *  application code.
 */
    gsi_include_file_major_version = GSI_INCLUDE_MAJ_VER_NUM;
    gsi_include_file_minor_version = GSI_INCLUDE_MIN_VER_NUM;
    gsi_include_file_revision_version = GSI_INCLUDE_REV_VER_NUM;

/*
 *  Initialize GSI and enter the event handler loop.
 */
    if (argc < 3) {
      printf ("Unexpected number of arguments.\nUsage: gsi_client host portnumber\n");
      exit (0);
    }
    hostname_arg = argv[1];
    portnumber_arg = argv[2];
    argc = 1;
    gsi_start(argc, argv);
    if (gsi_last_error() != 0) 
        return 1;
      
/*
 *  Keep calling the main run loop until timeout is reached.  No regression
 *  test should take more time to complete than that given by timeout interval.
 */
    time(&start_time);
    time(&time_now);
    while (time_now < start_time+TIMEOUT_INTERVAL) {
        gsi_clear_last_error();
        gsi_run_loop();
	gsi_pause();
        time(&time_now);
	if (!connected_p && (time_now > start_time + CONNECTION_WAIT)) {
	  gsi_initiate_unsolicited_connection_to_g2 (hostname_arg, portnumber_arg);
	  connected_p = TRUE;
	} else if (!remote_procedure_done && (time_now >start_time + CONNECTION_WAIT + CONNECTION_WAIT)) {
	  gsi_item procedure_arg = my_arg_array[0];
	  gsi_set_int (procedure_arg, (gsi_int)0);
	  gsi_rpc_call (g2_proc_index, my_arg_array, open_context_id);

	  gsi_set_int (my_arg_array[1], (gsi_int)5);
	  gsi_set_int (my_arg_array[2], (gsi_int)99);
	  gsi_rpc_call (g2_sys_proc_index, my_arg_array, open_context_id);
	  remote_procedure_done = TRUE;
	}
	if (gsi_last_error() != 0)
	  return 1; 
    } /* end while */

    return 0;

} /* end main */


void my_example_error_handler(econtext, ecode, emessage)
    gsi_int  econtext;
    gsi_int  ecode;
    char    *emessage;
{ 
/*
 *  Any behavior desired upon error may be implemnted from this function.
 *  By the time this function is called the error has already been reported to
 *  standard out (unless the message suppression option has been set).  If and
 *  when this function returns, the context in which the error occurred will be
 *  shut down and either control will be passed to within gsi_run_loop(), or 
 *  gsi_run_loop() will return -  depending on whether the program is running 
 *  in continuous or one-cycle modes respectively.
 */
    printf("The error handler was called\n");
}



void gsi_initiate_unsolicited_connection_to_g2(host_name, port_number)
  char *host_name, *port_number;
{
    char g2msg[100];
    char *interface_name, *class_name, *transport_type, *rpis;
    gsi_int keep_xn_perm_p;

    printf ("Starting gsi_initiate_connection_to_g2.\n");
    fflush (stdout);

    interface_name = "NTW-CONNECTION";
    class_name     = "GSI-INTERFACE";
    keep_xn_perm_p = 1;
    transport_type = "TCP-IP";
    rpis           = "Return Me this String";

    printf ("Opening Xn type %s to %s at port %s : with a %s named %s and rpis = %s.\n",
	    transport_type, host_name, port_number, class_name,
	    interface_name, rpis);
    gsi_initiate_connection (interface_name, class_name, keep_xn_perm_p,
			     transport_type, host_name, port_number, rpis);

} /* end gsi_initiate_unsolicited_connection_to_g2 */



void force_gsi_exit(arg_array, count, call_index)
    gsi_rpc_arg   arg_array[];
    gsi_int       count;
    gsi_int      call_index;
{
    exit(0);
}


/*  This function is intentionally verbose, because it is a first
 *  check on the return values from the procedure.
 */
void generic_void_return_receiver(arg_array,count)
    gsi_rpc_arg   arg_array[];
    gsi_int       count;
{
  int i;

  printf ("generic_void_return_receiver called with %d return values.\n", count);
  for (i=0; i<count; i++)
    gsirtl_display_item_or_value (arg_array[i], 0, 0);
  fflush (stdout);
}




void gsi_set_up()
{
    long i;
    gsi_item* new_itm_ptr;

/*
 *  Install optional GSI error handler.  This error handler does nothing and
 *  its installation serves only to demonstrate how and when error handlers
 *  are to be installed for GSI.
 */
    gsi_install_error_handler(my_example_error_handler);

/*
 *  Specify GSI run-time option GSI_ONE_CYCLE which causes the call to
 *  gsi_start() and subsequent calls to gsi_run_loop() to return.
 *
 *  Unless specified otherwise, GSI uses D floats under VAX/VMS, and 
 *  IEEE floats under Alpha/OpenVMS.  In both VMS systems, G floats may
 *  be specified as a run-time option.  In the code below the selection
 *  of floating point format is automated for VMS platforms via the use
 *  of the symbol CC$gfloat.  CC$gfloat is set on VAXen when this file
 *  has been compiled with the /G_FLOAT option, and is set by default on
 *  Alphas (we have chosen IEEE as the default in all GSI example code).
 */
    gsi_set_option(GSI_ONE_CYCLE);
#   ifdef vms
#       if CC$gfloat
          gsi_set_option(GSI_USE_GFLOATS);
#       endif
#   endif

/*
 *  Declare the local functions called by G2 for this test.
 */
    gsi_clear_last_error();
    /*
    gsi_rpc_declare_local(gsi_receive_item_copy,
			  "GSI-RECEIVE-ITEM-COPY");
    gsi_rpc_declare_local(gsi_receive_item_handle,
			  "GSI-RECEIVE-ITEM-HANDLE");
    gsi_rpc_declare_local(gsi_call_g2_with_item_copy,
			  "GSI-CALL-G2-WITH-ITEM-COPY");
    gsi_rpc_declare_local(gsi_call_g2_with_item_handle,
			  "GSI-CALL-G2-WITH-ITEM-HANDLE");
    gsi_rpc_declare_local(gsi_initiate_connection_to_g2,
			  "GSI-INITIATE-CONNECTION-TO-G2");
    gsi_rpc_declare_local(gsi_initiate_rpc_call_returning_copy,
			  "GSI-INITIATE-RPC-CALL-RETURNING-COPY");
    gsi_rpc_declare_local(gsi_initiate_rpc_call_returning_handle,
			  "GSI-INITIATE-RPC-CALL-RETURNING-HANDLE");
    gsi_rpc_declare_local(gsi_initiate_system_rpc_call_returning_copy,
			  "GSI-INITIATE-SYSTEM-RPC-CALL-RETURNING-COPY");
    gsi_rpc_declare_local(gsi_initiate_system_rpc_call_returning_handle,
			  "GSI-INITIATE-SYSTEM-RPC-CALL-RETURNING-HANDLE");
    gsi_rpc_declare_local(gsi_return_received_copy,
			  "GSI-RETURN-RECEIVED-COPY");
    gsi_rpc_declare_local(gsi_return_received_handle,
			  "GSI-RETURN-RECEIVED-HANDLE");
    gsi_rpc_declare_local(rsvp,"RSVP");
    gsi_rpc_declare_local(force_gsi_exit,"FORCE-GSI-EXIT");
    gsi_rpc_declare_local(receive_and_return_copy,
			  "RECEIVE-AND-RETURN-ITEM-COPY");
			  */
/*
 *  Allocate any data structures that will be needed to support this
 *  program's features.  Note, that these are never explicitly reclaimed
 *  because they are needed for the entire life of the process and are
 *  implicitly reclaimed upon exit of the process.
 */
    my_arg_array = gsi_make_rpc_args(5);
    new_itm_ptr = gsi_make_items (1);
    passback_item_copy = *new_itm_ptr;
    new_itm_ptr = gsi_make_items (1);
    passback_item_handle = *new_itm_ptr;
    new_itm_ptr = gsi_make_items (1);
    received_item_copy = *new_itm_ptr;
    new_itm_ptr = gsi_make_items (1);
    received_item_handle = *new_itm_ptr;    
    master_arg_array = gsi_make_rpc_args(ARG_CNT);

} /* end gsi_set_up */

gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{
    gsi_clear_last_error();
    open_context_id = current_context;
    gsi_rpc_declare_remote(&g2_proc_index,
			   "G2-REMOTE-CALLABLE-PROCEDURE",
			   generic_void_return_receiver,
			   ARG_CNT, ARG_CNT,
			   current_context);
    gsi_rpc_declare_remote(&g2_sys_proc_index,
			   "G2-API-BOGUS-1",
			   generic_void_return_receiver,
			   3, 2,
			   current_context);
    /*
    gsi_rpc_declare_remote(&g2_proc_rec_copy_index,
			   "G2-PROCEDURE-RECEIVING-ITEM-COPY",
			   generic_void_return_receiver,
			   ARG_CNT, ARG_CNT,
			   current_context);
    gsi_rpc_declare_remote(&g2_proc_rec_handle_index,
			   "G2-PROCEDURE-RECEIVING-ITEM-HANDLE",
			   generic_void_return_receiver,
			   ARG_CNT, ARG_CNT,
			   current_context);
    gsi_rpc_declare_remote(&g2_kb_proc_returning_item_index,
			   "G2-PROCEDURE-RETURNING-ITEM",
			   generic_item_return_receiver,
			   0, 1,
			   current_context);
    gsi_rpc_declare_remote(&g2_system_rpc_returning_item_index,
			   "G2-API-GET-UNIQUE-NAMED-ITEM",
			   generic_item_return_receiver,
			   2, 1,
			   current_context);

    gsi_rpc_declare_remote(&construct, "CONSTRUCT",construct_return_receiver,ARG_CNT,
			 ARG_CNT,current_context);
    gsi_rpc_declare_remote(&response, "RESPONSE",NULL,ARG_CNT,0,current_context);
    gsi_rpc_declare_remote(&set_result, "SET-RESULT",NULL,1,0,current_context);
    */
    return(GSI_ACCEPT);
} 

/************************************************
*
*  The remaining functions are all empty stubs.
*
*************************************************/

gsi_int gsi_get_tcp_port()
{
    return(TCPIP_PORT_NUMBER);
}

void gsi_receive_registration(registration)
    gsi_registration registration;
{
  printf ("Received registration for %d.\n", gsi_handle_of (registration));
  fflush (stdout);
}

void gsi_get_data(registered_item_array, count)
    gsi_registered_item registered_item_array[];
    gsi_int             count;
{}

void gsi_set_data(registered_item_array, count)
    gsi_registered_item  registered_item_array[];
    gsi_int              count;
{}

void gsi_pause_context()
{}

void gsi_resume_context()
{}

void gsi_shutdown_context()
{}

void gsi_g2_poll()
{}

void gsi_receive_deregistrations(registered_item_array, count)
    gsi_registered_item  registered_item_array[];
    gsi_int              count;
{}

void gsi_receive_message(message, length)
    char     *message;
    gsi_int   length;
{}
