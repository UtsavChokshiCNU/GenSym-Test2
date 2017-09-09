/*******************************************************************************
:
:  context_1.c	--  GSI regression test.		   (for GSI 4.0)
:
:  This tests GSI multi-contexting ability, including the ability to call GSI
:  API functions to send data to contexts other than the current context, and
:  the ability to return data to specific contexts from outside the call tree
:  gsi_run_loop().
:
:  Updated by ncc on 5/10/94, to support GSI 4.0.
:  Updated by rh on 10/11/97, to support GSI 5.0.1.
:  Must be linked against libgsi.a, libnet.a and librtl.a
:
:.............................................................................*/

#include <stdio.h>
#include <time.h>
#include "gsi_main.h"

#define TCPIP_PORT_NUMBER     0
#define TIMEOUT_INTERVAL    360	/* six minutes */
#define MAX_CONTEXTS	     50

void perform_extra_context_rpcs(); /* Forward reference */

function_handle_type cross_context_counter;
function_handle_type extra_context_counter;
gsi_rpc_arg	    *report_arg_array;
gsi_rpc_arg	    *context_arg_ptr;
gsi_registered_item *temp_registered_item_ptr;
gsi_int		     first_context = -1;
gsi_int		     extra_context_test_enabled = FALSE;
long		     context_count = 0;

struct {
    gsi_int context;
    gsi_int index;
} context_array[MAX_CONTEXTS];

gsi_int exit_flag;

extern declare_gsi_rpc_local_fn(force_gsi_exit);
extern declare_gsi_rpc_local_fn(cross_context_test);
extern declare_gsi_rpc_local_fn(extra_context_test);

int main(argc, argv)
    int   argc;
    char *argv[];
{
    time_t  time_now;
    time_t  start_time;

    GSI_SET_OPTIONS_FROM_COMPILE();

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
    exit_flag = FALSE;
    while (time_now < start_time+TIMEOUT_INTERVAL) {
	gsi_clear_last_error();
	gsi_run_loop();
	gsi_pause();
	time(&time_now);
	if (extra_context_test_enabled) {
	    perform_extra_context_rpcs();
	    extra_context_test_enabled = FALSE; }
	if (gsi_last_error() != 0)
	    printf("\n context_1 top level: Last error was fatal, exiting.\n"); 

	if (exit_flag && (context_count == 0)) { 
	  printf ("\nLast context closed, exiting. \n");
	  exit (0);
	}
	
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
 *  standard out (unless the message suppression option has been set).	If and
 *  when this function returns, the context in which the error occurred will be
 *  shut down and either control will be passed to within gsi_run_loop(), or 
 *  gsi_run_loop() will return -  depending on whether the program is running 
 *  in continuous or one-cycle modes respectively.
 */
    printf("The error handler was called\n");
}


void cross_context_test(arg_array, count, call_index)
    gsi_rpc_arg	  arg_array[];
    gsi_int	  count;
    call_identifier_type	  call_index;
{
    set_int(*context_arg_ptr,first_context);
    gsi_rpc_start(cross_context_counter,context_arg_ptr,first_context);
}


void extra_context_test(arg_array, count, call_index)
    gsi_rpc_arg	  arg_array[];
    gsi_int	  count;
    call_identifier_type	  call_index;
{
/*
 *  Set the flag that will cause the extra-context test to be
 *  performed once we are out of this iteration of the amin run loop.
 */
    extra_context_test_enabled = TRUE;
}


void perform_extra_context_rpcs()
{
    long	  i;

/*
 *  Call a G2 procedure through each defined context sending the context
 *  number as an argument.  Also return a value to each GSI variable through
 *  its context.  Again note that each context may have only one variable.
 */
    for (i=0; i<context_count; i++) {
	set_int(*context_arg_ptr,context_array[i].context);
	gsi_rpc_start(extra_context_counter,context_arg_ptr,context_array[i].context);
	set_handle(*temp_registered_item_ptr,context_array[i].index);
	set_status(*temp_registered_item_ptr,NO_ERR);
	set_int(*temp_registered_item_ptr,9999);
	gsi_return_values(temp_registered_item_ptr,1,context_array[i].context); }
}


void force_gsi_exit(arg_array, count, call_index)
    gsi_rpc_arg	  arg_array[];
    gsi_int	  count;
    gsi_int	 call_index;
{
  exit_flag = TRUE;
}


void gsi_set_up()
{
    long i;

/*
 *  Install optional GSI error handler.	 This error handler does nothing and
 *  its installation serves only to demonstrate how and when error handlers
 *  are to be installed for GSI.
 */
    gsi_install_error_handler(my_example_error_handler);

/*
 *  Specify GSI run-time option GSI_ONE_CYCLE which causes the call to
 *  gsi_start() and subsequent calls to gsi_run_loop() to return.
 */
    gsi_set_option(GSI_ONE_CYCLE);

/*  Unless specified otherwise, GSI uses D floats under VAX/VMS, and 
 *  IEEE floats under Alpha/OpenVMS.  In both VMS systems, G floats may
 *  be specified as a run-time option.	In the code below the selection
 *  of floating point format is automated for VMS platforms via the use
 *  of the symbol CC$gfloat.  CC$gfloat is set on VAXen when this file
 *  has been compiled with the /G_FLOAT option, and is set by default on
 *  Alphas (we have chosen IEEE as the default in all GSI example code).
 */
#   ifdef vms
#	if CC$gfloat
	  gsi_set_option(GSI_USE_GFLOATS);
#	endif
#   endif

/*
 *  Declare the local functions called by G2 for this test.
 */
    gsi_rpc_declare_local(force_gsi_exit,"FORCE-GSI-EXIT");
    gsi_rpc_declare_local(cross_context_test,"CROSS-CONTEXT-TEST");
    gsi_rpc_declare_local(extra_context_test,"EXTRA-CONTEXT-TEST");

/*
 *  Allocate any data structures that will be needed to support this
 *  program's features.	 Note, that these are never explicitly reclaimed
 *  because they are needed for the entire life of the process and are
 *  implicitly reclaimed upon exit of the process.
 */
    report_arg_array = gsi_make_rpc_args(2);
    context_arg_ptr = gsi_make_rpc_args(1);
    temp_registered_item_ptr = gsi_make_registered_items(1);	

/*
 *  Initialize the context array.
 */
    for (i=0; i<MAX_CONTEXTS; i++) {
	context_array[i].context = -1;
	context_array[i].index = -1; }

} /* end gsi_set_up */


gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{

/*
 *  Declare G2 procedures that will be called from this program.
 */
    gsi_rpc_declare_remote(&cross_context_counter,"CROSS-CONTEXT-COUNTER",NULL,1,0,current_context);
    gsi_rpc_declare_remote(&extra_context_counter,"EXTRA-CONTEXT-COUNTER",NULL,1,0,current_context);

/*
 *  Add an entry into the context table for this context.
 */
    context_array[context_count++].context = current_context;
    if (first_context == -1)
	first_context = current_context;

    return(GSI_ACCEPT); 
} 


void gsi_receive_registration(registration)
    gsi_registration registration;
{
    long       i;

/*
 *  Iterate over the context table to set the index associated with
 *  this context.  Note, only one variable per context is allowed.
 */
    for (i=0; i<context_count; i++)
      if (context_array[i].context == current_context) {
	context_array[i].index = handle_of(registration);
	break; }

/*
 *  Return a value to the object being defined through the current context.
 */
    set_handle(*temp_registered_item_ptr,handle_of(registration));
    set_status(*temp_registered_item_ptr,NO_ERR);
    set_int(*temp_registered_item_ptr,5678);
    gsi_return_values(temp_registered_item_ptr,1,current_context);
} 
 

void gsi_set_data(registered_item_array, count)
    gsi_registered_item	 registered_item_array[];
    gsi_int		 count;
{
    gsi_attr		*temp_attr_ptr;
    long		 i;


    temp_attr_ptr = gsi_make_attrs_with_items(1);

/*
 *  For each object set from G2, return an attribute
 *  value without updating the "last recorded value".
 */
    for (i=0; i<count; i++) {
      set_status(registered_item_array[i],0);
      set_int(registered_item_array[i],0);
      set_type(registered_item_array[i],GSI_NULL_TAG);
      gsi_set_attr_name(temp_attr_ptr[0],"MY-COLOR");
      set_sym(temp_attr_ptr[0],"GREEN");
      gsi_return_attrs(registered_item_array[i],temp_attr_ptr,1,current_context);
    }

    gsi_reclaim_attrs_with_items(temp_attr_ptr);
}


void gsi_shutdown_context() 
{
/*
 *  Remove this context's entry from the context
 *  array, and decrement the count of contexts.
 */
    context_array[current_context].context = -1;
    context_array[current_context].index = -1;
    context_count--;
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

void gsi_get_data(registered_item_array, count)
    gsi_registered_item registered_item_array[];
    gsi_int		count;
{}

void gsi_pause_context()
{}

void gsi_resume_context()
{}

void gsi_g2_poll()
{}

void gsi_receive_deregistrations(registered_item_array, count)
    gsi_registered_item	 registered_item_array[];
    gsi_int		 count;
{}

void gsi_receive_message(message, length)
    char     *message;
    gsi_int   length;
{}
