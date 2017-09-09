/*******************************************************************************
:
:  string_1.c  --  GSI regression test.                             (for GSI 4.0)
:
:  In this test, G2 calls string_test() as often as it likes and G2 determines
:  if the strings are being properly handled.  string_test() takes a string as
:  an argument and returns the length determined by strlen() the length as given
:  by the GSI access function length_of() and the string as received into GSI. 
:  G2 may also call set_filtering() with a logical to turn on or
:  off string filtering.
:
:  jv, 8/1/05: I believe this regression test has never been used; if it has, it
:  was over eleven years ago.  This file does not even get compiled.  There's a
:  commented out line in gsi-dependencies.rel to add it to the makefile.  The
:  comment with it says, "it's only string, and besides, it's not working yet."
:  That comment was added by ncc, 16-May-94 (ab-9oct95 repository).  So it's
:  pretty safe to say that this file has never been used.
:
:.............................................................................*/

#include <stdio.h>
#include <time.h>
#include "gsi_main.h"        /* Required to support use of GSI API. */

#define TCPIP_PORT_NUMBER     0
#define TIMEOUT_INTERVAL    360 /* six minutes */

void set_filtering(args,count,call_index)
  gsi_item      args[];
  gsi_int       count;
  gsi_int       call_index;
{
  if (log_of(args[0]) == GSI_TRUE) {
    gsi_set_option(GSI_STRING_CHECK);
    printf("\nString filtering on!\n"); }
  else {
    gsi_reset_option(GSI_STRING_CHECK);
    printf("\nString filtering off!\n"); }
}

void string_test(args,count,call_index)
  gsi_item      args[];
  gsi_int       count;
  gsi_int       call_index;
{
  gsi_item  *ret_args = gsi_make_items(3);
  char      *test_string;
  
  test_string = str_of(args[0]);
  printf("\n%s\n",test_string);
  set_int(ret_args[0],strlen(test_string));
  set_int(ret_args[1],element_count_of(args[0]));
  set_str(ret_args[2],test_string);
  gsi_rpc_return_values(ret_args,3,call_index,current_context);
  gsi_reclaim_items(ret_args);
}

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


void force_gsi_exit(arg_array, count, call_index)
    gsi_rpc_arg  arg_array[];
    gsi_int      count;
    gsi_int      call_index;
{
    exit(0);
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
    gsi_rpc_declare_local(string_test,"STRING-TEST");
    gsi_rpc_declare_local(set_filtering,"SET-FILTERING");

/*
 *  Allocate any data structures that will be needed to support this
 *  program's features.  Note, that these are never explicitly reclaimed
 *  because they are needed for the entire life of the process and are
 *  implicitly reclaimed upon exit of the process.
 */
    /* None required */

} /* end gsi_set_up */


void gsi_set_data(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
  gsi_int         i;
  float           f;
  gsi_attr       *temp_attr_ptr;
  gsi_attr        temp_attr;

  temp_attr_ptr = gsi_make_attrs_with_items (1); /* just one please */
  temp_attr = *temp_attr_ptr;

  /*
   *  This converts each incoming string into a floating point number
   *  and returns the value as a float via an attr return call.
   *  Note, the float value is returned in both the value and an attr.
   */
  for (i=0; i<count; i++) {
    sscanf(str_of(registered_items[i]),"%f",&f);
    set_flt(registered_items[i],(double) f);
    set_attr_name(temp_attr,"OLDFLOAT");
    set_flt(temp_attr,(double) f);
    gsi_return_attrs(registered_items[i],temp_attr_ptr,1,current_context); 
  }

  gsi_reclaim_attrs(temp_attr_ptr);

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


