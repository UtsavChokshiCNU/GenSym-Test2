/*******************************************************************************
:
:  toolkit_1.c  --  GSI regression test                            (for GSI 4.0)
:
:  This tests the system level functionality of GSI to check whether the various
:  GSI toolkit funcitons are called at the appropriate times in accordance with
:  actions occurring within G2.
:
:  Further note, no modules needed other than the GSI library.
:
:.............................................................................*/

#include <stdio.h>
#include <time.h>
#include "gsi_main.h"        /* Required to support use of GSI API. */

#define TCPIP_PORT_NUMBER     0
#define TIMEOUT_INTERVAL    360 /* six minutes */
#define GSI_VAR_STATUS       99

gsi_int exit_flag;		/* new exit mechanism */
long return_code = 0;		/* value to be returned via exit(). */

gsi_rpc_arg  *report_arg_array;	/* an array of rpc argument structures. */
gsi_int       report_and_react;	/* "handle" to remote procedure in G2.  */
gsi_int       get_data_called = FALSE;
gsi_int       shutdown_called = FALSE;

extern declare_gsi_rpc_local_fn(force_gsi_exit);

main(argc, argv)
    int   argc;
    char *argv[];
{
    time_t  time_now;
    time_t  start_time;

    exit_flag = FALSE;
    

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
    gsi_start(argc, argv);
    if (gsi_last_error() != 0)  {
      printf("toolkit_1: fatal error occurred.  The exit flag was");

      if (exit_flag == TRUE)
	printf(" set.\n");
      else
	printf(" not set.  (Problem in error handling!) \n");

      exit(1);
    }
      
/*
 *  Keep calling the main run loop until timeout is reached.  No regression
 *  test should take more time to complete than that given by timeout interval.
 */
    time(&start_time);
    time(&time_now);
    while (time_now < start_time+TIMEOUT_INTERVAL) {
        gsi_clear_last_error();
        gsi_run_loop();

        if (gsi_last_error() != 0) {
	  printf("toolkit_1: fatal error occurred.  The exit flag was");
	  return_code = 1;
	  if (exit_flag == TRUE)
	    printf(" set.\n");
	  else
	    printf(" not set.  (Problem in error handling!) \n");
	}
	
	if (exit_flag) { 
	  printf ("\nExit flag set, exiting. \n");
	  exit (return_code);
	}

	gsi_pause();
        time(&time_now);
    } /* end while */

    return 0;

} /* end main */


void my_example_error_handler(econtext, ecode, emessage)
    gsi_int  econtext;
    gsi_int  ecode;
    char    *emessage;
{ 
    printf("The error handler was called\n");
    exit_flag = TRUE;
}


void force_gsi_exit(arg_array, count, call_index)
    gsi_rpc_arg  arg_array[];
    gsi_int      count;
    gsi_int      call_index;
{
  exit_flag = TRUE;
  return_code = 0;
}


void gsi_set_up()
{
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
    gsi_rpc_declare_local(force_gsi_exit,"FORCE-GSI-EXIT");

/*
 *  Allocate any data structures that will be needed to support this
 *  program's features.  Note, that these are never explicitly reclaimed
 *  because they are needed for the entire life of the process and are
 *  implicitly reclaimed upon exit of the process.
 */
    report_arg_array = gsi_make_rpc_args(2);    

} /* end gsi_set_up */

gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{

    gsi_rpc_declare_remote(&report_and_react, "REPORT-AND-REACT",NULL,2,0,
                           current_context);
    if (shutdown_called) {
        set_sym(report_arg_array[0],"GSI_SHUTDOWN");
        get_data_called = FALSE;
        shutdown_called = FALSE; }
    else
        set_sym(report_arg_array[0],"GSI_INIT_DS");
    set_str(report_arg_array[1],"");
    gsi_rpc_start(report_and_react,report_arg_array,current_context);
    return(GSI_ACCEPT); 
} 

void gsi_receive_registration(registration) 
     gsi_registration registration;
{ 
    set_sym(report_arg_array[0],"GSI_DEF_OBJ");
    set_str(report_arg_array[1],"");
    gsi_rpc_start(report_and_react,report_arg_array,current_context);
} 
 
void gsi_get_data(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
    if (count != 1)
        gsi_signal_error("gsi_get_data",1000,"gsi_get_data() called with count > 1");

    if (get_data_called) {
        set_status(registered_items[0],0L); /* XXX this was NO_ERR, a constant from icp.h -ncc, 3/28/94 */
        gsi_return_values(registered_items,count,current_context); }
    else {
        set_status(registered_items[0],GSI_VAR_STATUS);
        gsi_return_values(registered_items,count,current_context);
        set_sym(report_arg_array[0],"GSI_GET_DATA");
        set_str(report_arg_array[1],"");
        gsi_rpc_start(report_and_react,report_arg_array,current_context);
        get_data_called = TRUE; }
} 

void gsi_set_data(registered_items, count) 
     gsi_registered_item  registered_items[]; 
     gsi_int              count; 
{
    set_sym(report_arg_array[0],"GSI_SET_DATA");
    set_str(report_arg_array[1],str_of(registered_items[0]));
    gsi_rpc_start(report_and_react,report_arg_array,current_context);
} 

void gsi_receive_deregistrations(registered_items, count)
     gsi_registered_item  registered_items[]; /* an array of count gsi_item_registrations  */
     gsi_int              count;
{ 
  set_sym(report_arg_array[0],"GSI_STOP_DATA");
  set_str(report_arg_array[1],"");
  gsi_rpc_start(report_and_react,report_arg_array,current_context);
}

void gsi_receive_message(message, length)
    char     *message;
    gsi_int   length;
{
    set_sym(report_arg_array[0],"GSI_RD_TEXT");
    set_str(report_arg_array[1],message);
    gsi_rpc_start(report_and_react,report_arg_array,current_context);
} 

void gsi_shutdown_context() 
{ 
  printf("gsi_shutdown_context: called while current context is %d\n", current_context);
  shutdown_called = TRUE;
} 

gsi_int gsi_get_tcp_port() 
{ 
    return(TCPIP_PORT_NUMBER); 
} 
 

/************************************************
*
*  The remaining functions are all empty stubs.
*
*************************************************/

void gsi_pause_context()
{}

void gsi_resume_context()
{}

void gsi_g2_poll()
{}
