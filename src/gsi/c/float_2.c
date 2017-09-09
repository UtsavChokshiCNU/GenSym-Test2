/*******************************************************************************
:
:  float_2.c  --  GSI regression test.                             (for GSI 4.0)
:
:  This tests the quality of translation of floating point in a round trip from
:  G2 to GSI and back to G2.  For each value tested, G2 send a float, GSI sends
:  it right back and G2 checks if the value returned is the same as was sent.
:
:  Note, this test will not find reciprocal bugs wherein a value is incorrectly
:  translated as it is passed to GSI, then incorrectly translated back to G2
:  resulting in the same value in G2 but an incorrect value while in GSI.
:  This test alone is not sufficient to test float passing between G2 and
:  GSI.  See float_1.c.
:
:  Further note, no other modules needed other than the GSI library.
:
:.............................................................................*/

#include <stdio.h>
#include <time.h>
#include "gsi_main.h"        /* Required to support use of GSI API. */

#define TCPIP_PORT_NUMBER     0
#define TIMEOUT_INTERVAL    360 /* six minutes */

gsi_int exit_flag;		/* new exit mechanism */
long return_code = 0;		/* value to be returned via exit(). */

extern declare_gsi_rpc_local_fn(force_gsi_exit);

main(argc, argv)
    int   argc;
    char *argv[];
{
    time_t  time_now;
    time_t  start_time;

    exit_flag = FALSE;

/*
 *  Initialize GSI and enter the event handler loop.
 */
    GSI_SET_OPTIONS_FROM_COMPILE();
    gsi_start(argc, argv);
    if (gsi_last_error() != 0)  {
      printf("float_2_1: fatal error occurred.  The exit flag was");

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
	  printf("float_2: fatal error occurred.  The exit flag was");
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
    /* None required */

} /* end gsi_set_up */


void gsi_set_data(registered_item_array, count) 
    gsi_registered_item  registered_item_array[]; 
    gsi_int              count; 
{
/*
 *  Whatever is received, send it right back.
 */
    gsi_return_values(registered_item_array,count,current_context);
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

gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{
    return (GSI_ACCEPT);
}

void gsi_receive_registration(registration)
    gsi_registration registration;
{}

void gsi_get_data(registered_item_array, count)
    gsi_registered_item registered_item_array[];
    gsi_int             count;
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
