/*******************************************************************************
:
:  rpc_1.c  --  GSI regression test for G2 to GSI RPCs.
:
:
:
:  Note, no other modules needed other than the GSI library.
:
:.............................................................................*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "gsi_main.h"
#include "gsi_misc.h"


#define TCPIP_PORT_NUMBER          0
#define TIMEOUT_INTERVAL         360 /* six minutes */
#define ARG_CNT                  200
#define INTERNAL_INCONSISTENCY     1
#define SEND                       1
#define NO_SEND                    0
#define NO_DATA              9999999

gsi_int exit_flag;		/* new exit mechanism */
long return_code = 0;		/* value to be returned via exit(). */

gsi_int       construct;
gsi_int       response;
gsi_int       set_result;

gsi_rpc_arg  *mod_arg_array;
gsi_rpc_arg  *master_arg_array;

extern declare_gsi_rpc_local_fn(destruct);
extern declare_gsi_rpc_local_fn(rsvp);
extern declare_gsi_rpc_local_fn(force_gsi_exit);
extern declare_gsi_rpc_local_fn(receive_and_return_copy);

extern declare_gsi_rpc_receiver_fn(construct_return_receiver);

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
      printf("rpc_1: fatal error occurred.  The exit flag was");

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
	  printf("rpc_1: fatal error occurred.  The exit flag was");
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


void destruct(arg_array,count,call_index)
    gsi_rpc_arg   arg_array[];
    gsi_int       count;
    gsi_int       call_index;
{
    gsi_int              i, length;
    char 		*two_char_part;

/*
 *  Check if count matches expected value.
 */
    if (count != ARG_CNT)
        gsi_signal_error("destruct",1000,"count != ARG_CNT");

    two_char_part = (char *) calloc(3, sizeof(char));

/*
 *  Iterate over the arguments, separating each numeric and textual value
 *  into two parts placing one part in the modified array, the other in args.
 */
    for (i=0; i<count; i++) {
      switch(type_of(arg_array[i])) {
        case GSI_INTEGER_TAG:
          set_int(master_arg_array[i], int_of(arg_array[i]));
          set_int(arg_array[i], int_of(arg_array[i]) - i);
          set_int(mod_arg_array[i], i);
          break;
        case GSI_FLOAT64_TAG:
          set_flt(master_arg_array[i], flt_of(arg_array[i]));
          set_flt(arg_array[i], gsi_flt_of(arg_array[i]) - i);
          set_flt(mod_arg_array[i], (double) i);
          break;
        case GSI_STRING_TAG:
          length = strlen(str_of(arg_array[i]));
          set_str(master_arg_array[i], str_of(arg_array[i]));
          if (length > 1) {
            memset(two_char_part,0,3); 
            strncpy(two_char_part, str_of(arg_array[i]), 2);
            set_str(mod_arg_array[i],two_char_part);
            set_str(arg_array[i],str_of(arg_array[i])+2); }
          else
            strcpy(str_of(mod_arg_array[i]),"");
          break;
        case GSI_SYMBOL_TAG: 
          length = strlen(sym_of(arg_array[i]));
          set_sym(master_arg_array[i], sym_of(arg_array[i]));
          if (length > 1) {
            memset(two_char_part,0,3);	
            strncpy(two_char_part,sym_of(arg_array[i]),2);
            set_sym(mod_arg_array[i], two_char_part);
            set_sym(arg_array[i],sym_of(arg_array[i])+2);  }
          else
            set_sym(mod_arg_array[i],"");
          break;
        case GSI_LOGICAL_TAG:
          set_log(master_arg_array[i], log_of(arg_array[i]));
          set_log(mod_arg_array[i], GSI_FALSE); 
          break;
        default:
          gsi_signal_error("destruct",1000,"unexpected type");
      } /* end switch */
    } /* end for */


/*
 *  Call remote procedure CONSTRUCT passing the modified arguments,
 *  and return the other half of each argument to whomever called me.
 */
    gsi_rpc_call(construct,mod_arg_array,current_context);
    gsi_rpc_return_values(arg_array,count,call_index,current_context);

} /* end destruct */


void rsvp(arg_array,count,call_index)
    gsi_rpc_arg   arg_array[];
    gsi_int       count;
    gsi_int       call_index;
{
/*
 *  Check if count matches expected value.
 */
    if (count != ARG_CNT)
        gsi_signal_error("rsvp",1000,"count != ARG_CNT");

/*
 *  Start remote procedure RESPONSE passing the received arguments unchanged.
 */
    gsi_rpc_start(response,arg_array,current_context);
}

void construct_return_receiver(arg_array,count)
    gsi_rpc_arg   arg_array[];
    gsi_int       count;
{
    gsi_int       i;
    gsi_rpc_arg  *result_ptr = gsi_make_rpc_args(1); /* _MUST_ alloc rpc args this way now.  */
    gsi_rpc_arg   result = *result_ptr;

/*
 *  Check if count matches expected value.
 */
    if (count != ARG_CNT)
        gsi_signal_error("construct_return_receiver",1000,"count != ARG_CNT");

/*
 *  Iterate over args, comparing each against its twin in master_arg_array, 
 *  and freeing memory in master_arg_array as I go.

 XXX  I don't see how this frees memory in master_arg_array.  -ncc, 4/26/94

 */
    for (i=0; i<count; i++) {
        if (type_of(arg_array[i]) != type_of(master_arg_array[i]))
            gsi_signal_error("construct_return_receiver",1000,"types don' match");
        switch(type_of(arg_array[i])) {
          case GSI_INTEGER_TAG:
            if (int_of(arg_array[i]) != int_of(master_arg_array[i])) {
                set_log(result,GSI_FALSE);
                gsi_rpc_start(set_result,result_ptr,current_context); }
            break;
          case GSI_FLOAT64_TAG:
            if (flt_of(arg_array[i]) != flt_of(master_arg_array[i])) {
                set_log(result,GSI_FALSE);
                gsi_rpc_start(set_result,result_ptr,current_context); }
            break;
          case GSI_STRING_TAG:
            if (strcmp(str_of(arg_array[i]),str_of(master_arg_array[i])) != 0) {
                set_log(result,GSI_FALSE);
                gsi_rpc_start(set_result,result_ptr,current_context); }
            break;
          case GSI_SYMBOL_TAG:
            if (strcmp(sym_of(arg_array[i]),sym_of(master_arg_array[i])) != 0) {
                set_log(result,GSI_FALSE);
                gsi_rpc_start(set_result,result_ptr,current_context); }
            break;
          case GSI_LOGICAL_TAG:
            if (log_of(arg_array[i]) != log_of(master_arg_array[i])) {
                set_log(result,GSI_FALSE);
                gsi_rpc_start(set_result,result_ptr,current_context); }
            break;
          default:
            gsi_signal_error("construct_return_receiver",1000,"unexpected type");
	} /* end switch */
    } /* end for */

    set_log(result,GSI_TRUE);
    gsi_rpc_start(set_result,result_ptr,current_context);

} /* end construct_return_receiver */

void force_gsi_exit(arg_array, count, call_index)
    gsi_rpc_arg   arg_array[];
    gsi_int       count;
    gsi_int      call_index;
{
  exit_flag = TRUE;
  return_code = 0;
}



void receive_and_return_copy(arg_array,count,call_index)
    gsi_item  arg_array[];
    gsi_int   count;
    gsi_int   call_index;
{
    gsi_item  *duplicate_ptr;
    gsi_item   duplicate;

/*
 *  Allocate memory for a duplicate.
 */
    duplicate_ptr = gsi_make_items(1);
    duplicate = *duplicate_ptr;

/*
 *  Display the entire contents of the argument to standard out.
 *  Items arguments are displayed recursively attribute by attribute.
 */
    printf("\n");
    printf("-------------------------\n");
    printf("  Printing argument\n");
    printf("-------------------------\n");
    gsirtl_display_item_or_value(arg_array[0],STARTING_LEVEL,STANDARD_OUT);
    printf("------------------------- end of argument.\n");

/*
 *  Make the copy.
 */
    gsirtl_copy_item_or_value(arg_array[0],duplicate);

/*
 *  Return the copy to G2, then reclaim the memory.
 */
    gsi_rpc_return_values(duplicate_ptr,1,call_index,current_context);
    gsirtl_free_i_or_v_contents(duplicate);

} /* end receive_and_return_copy */


void gsi_set_up()
{
    long i;

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
    gsi_rpc_declare_local(destruct,"DESTRUCT");
    gsi_rpc_declare_local(rsvp,"RSVP");
    gsi_rpc_declare_local(force_gsi_exit,"FORCE-GSI-EXIT");
    gsi_rpc_declare_local(receive_and_return_copy,
			  "RECEIVE-AND-RETURN-ITEM-COPY");

/*
 *  Allocate any data structures that will be needed to support this
 *  program's features.  Note, that these are never explicitly reclaimed
 *  because they are needed for the entire life of the process and are
 *  implicitly reclaimed upon exit of the process.
 */
    mod_arg_array = gsi_make_rpc_args(ARG_CNT);
    master_arg_array = gsi_make_rpc_args(ARG_CNT);
    for (i=160; i<200; i++)
        set_type(mod_arg_array[i], GSI_LOGICAL_TAG);

} /* end gsi_set_up */

gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{
    gsi_clear_last_error();
    gsi_rpc_declare_remote(&construct, "CONSTRUCT",construct_return_receiver,ARG_CNT,
			 ARG_CNT,current_context);
    gsi_rpc_declare_remote(&response, "RESPONSE",NULL,ARG_CNT,0,current_context);
    gsi_rpc_declare_remote(&set_result, "SET-RESULT",NULL,1,0,current_context);

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
