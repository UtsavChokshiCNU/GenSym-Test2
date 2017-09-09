/*******************************************************************************
:
:  integer_1.c  --  GSI regression test for integer and logical passing via RPC.
:                                                                  (for GSI 4.0)
:
:  In this test, G2 first calls integer_test() a number of times with a range of
:  integer values to test integer passing, then calls logical_test() a number of
:  times with 'true' and an number of times with 'false'.  In both cases, the
:  GSI test function is called twice for each value.  The first time, an integer
:  or logical value is passed as the argument, and the same type of argument is
:  returned whereupon G2 confirms a match or reports an error.  The second time
:  the integer or logical is converted to a textual representation which is
:  passed as the argument, GSI converts it to an integer or logical and returns
:  it to G2 where it is checked against the original value before conversion to
:  text.  In this way integer and logical data passing is tested for corruption
:  in either direction, and for reciprocal corruption not detectable in a simple
:  "return me the value I send to you" test.
:
:  Note, this must be linked with skeleton.c as it is an RPC-only bridge.
:
:.............................................................................*/

#include <stdio.h>
#include <time.h>
#include "gsi_main.h"        /* Required to support use of GSI API. */

#define TCPIP_PORT_NUMBER     0
#define TIMEOUT_INTERVAL    360 /* six minutes */

gsi_int exit_flag;		/* new exit mechanism */
long return_code = 0;		/* value to be returned via exit(). */

gsi_rpc_arg  *ret_arg_ptr;
gsi_rpc_arg   ret_arg;

extern declare_gsi_rpc_local_fn(integer_test);
extern declare_gsi_rpc_local_fn(logical_test);
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
      printf("integer_1: fatal error occurred.  The exit flag was");

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
	  printf("integer_1: fatal error occurred.  The exit flag was");
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

	/*	gsi_pause(); */
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


void integer_test(arg_array,count,call_index)
    gsi_rpc_arg  arg_array[];
    gsi_int      count;
    call_identifier_type  call_index;
{
    gsi_int       value;

/*
 *  Convert incoming string to an integer value and return it to G2.
 */
    if (type_of(arg_array[0]) == GSI_INTEGER_TAG)
        set_int(ret_arg,int_of(arg_array[0]));
    else if (type_of(arg_array[0]) == GSI_STRING_TAG) {
        sscanf(str_of(arg_array[0]),"%ld",&value);
        set_int(ret_arg,value); }
    else
        set_int(ret_arg,-12345678);

    gsi_rpc_return_values(ret_arg_ptr,1,call_index,current_context);
}


void logical_test(arg_array,count,call_index)
    gsi_rpc_arg   arg_array[];
    gsi_int       count;
    call_identifier_type  call_index;
{
/*
 *  Take the incoming logical and return it to G2.
 */
    if (type_of(arg_array[0]) == GSI_LOGICAL_TAG)
        set_log(ret_arg,log_of(arg_array[0]));
    else if (type_of(arg_array[0]) == GSI_STRING_TAG)
        if (strcmp(str_of(arg_array[0]),"true") == 0)
            set_log(ret_arg,GSI_TRUE);
        else if (strcmp(str_of(arg_array[0]),"false") == 0)
            set_log(ret_arg,GSI_FALSE);
        else
            set_log(ret_arg,0);
    else
        set_log(ret_arg,0);

    gsi_rpc_return_values(ret_arg_ptr,1,call_index,current_context);
}


void force_gsi_exit(arg_array, count, call_index)
    gsi_rpc_arg   arg_array[];
    gsi_int       count;
    call_identifier_type call_index;
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
    gsi_rpc_declare_local(integer_test,"INTEGER-TEST");
    gsi_rpc_declare_local(logical_test,"LOGICAL-TEST");
    gsi_rpc_declare_local(force_gsi_exit,"FORCE-GSI-EXIT");

/*
 *  Allocate any data structures that will be needed to support this
 *  program's features.  Note, that these are never explicitly reclaimed
 *  because they are needed for the entire life of the process and are
 *  implicitly reclaimed upon exit of the process.
 */
    ret_arg_ptr = gsi_make_rpc_args(1);
    ret_arg = *ret_arg_ptr;

} /* end gsi_set_up */



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
