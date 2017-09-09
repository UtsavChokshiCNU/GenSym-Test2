/*****************
 * gsi_bench.c *
 *****************/

/* jh, 6/3/90
 * This file contains template code for GSI regression suite.
 * The idea is to allow G2 to specify a regression test
 * in the initialization string.  Then all GSI bridge functions
 * in this template will call the appropriate "hook" function for
 * that regression test.  Each bridge function will obtain its
 * hook function by lookup in a table called regression_hooks.
 * This table has two keys: the bridge code function (specified
 * by a C constant) and the regression test number (specified
 * by an integer derived from the "remote process initialization
 * string" that G2 sends to the GSI extension).  Each regression
 * module will extern its hook functions, so they can be read into 
 * regression_hooks at initialization time.
 *
 * cpm, 7/14/95
 * Converted by PAF, around 12/22/94, to the new GSI 4.0 API.
 * He also merged the gsi_benchmark.c and gsi_regress_for_benchmark.c into
 * this one file.
 *
 * cpm, 7/16/95
 * Fix so that GSI does not lose the connection during the first benchmark test.
 * Replaced use of GSI_SUCCESS with GSI_ACCEPT, in this C file.
 * This fix was suggested by NCC.
 *
 * cpm, 7/16/95
 * Modifed RPC calls to accept a call_handle argument.
 * Modified calls to gsi_rpc_return_values to accept new call_handle and
 * current_context arguments.
 */


/* 
 * This file must be edited from time to time.  Grounds for editing are:
 *   1) a new regression test is introduced.
 *   2) a new GSI feature is added.
 * Look for the following comments:
 *   "must be edited for each new regression test"
 *   "must be checked for each new regression test"
 *   "must be edited for each feature addition"
 *   "must be checked for each feature addition"
 * As long as you're checking and editing things for feature additions,
 * consider yourself encouraged to write a regression test while you're at it.
 * 
 * Remember to edit the makefile for this regression suite, currently (6/3/90)
 * called MakeGSIregression, canonically in ma:>jrh>
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "gsi_main.h"



#define LARGE_NUMBER_OF_CALL_INS 510 /* > 500 sometimes causes a crash */

#define GSI_REGRESSION_PORT 33333

#define UNKNOWN_GET_MODE            0
#define GET_DATA_MODE               1
#define SET_DATA_MODE               2
#define GET_TIMED_DATA_MODE         3
#define SET_TIMED_DATA_MODE         4
#define GET_VECTOR_DATA_MODE        5
#define SET_VECTOR_DATA_MODE        6
#define GET_TIMED_VECTOR_DATA_MODE  7
#define SET_TIMED_VECTOR_DATA_MODE  8

#define GSI_REGRESSION_TRACE_OFF 0
#define GSI_REGRESSION_TRACE_ON  1

#define MEASUREMENT_INACTIVE  0
#define MEASURING_LATENCY    1
#define MEASURING_THROUGHPUT 2
#define MAX_CALL_IN_ARGS 5

#define NUMBER_OF_VECTOR_ATTRIBUTES 3

#ifndef NULL
#define NULL 0
#endif

#define PRINT_BENCH_MESSAGES 0

function_handle_type  handle_for_announce_rpcs_quiescent;
function_handle_type  current_call_in_handle;
gsi_int               current_call_in_argcount;

/* 
 * regression_trace_mode is a global variable which holds
 * the current regression trace mode.
 * It is set by parse_gsi_regression_info below.
 */

gsi_int  regression_trace_mode;
gsi_int  print_template_messages = 1;

gsi_item             *ret_items;
gsi_registered_item  *registered_items;
gsi_attr             *attribute_descriptions;

gsi_int  gsi_to_g2_measurement_mode;
gsi_int  rpcs_completed = 0; /* for latency measurements */
gsi_int  rpc_events = 0;
gsi_int  rpcs_outstanding = 0;

function_handle_type  handle_for_noop;
function_handle_type  handle_for_noop_return;
function_handle_type  handle_for_noop_arg;
function_handle_type  handle_for_noop_arg_return;

gsi_int regression_hooks_unloaded_p = TRUE;

extern declare_gsi_rpc_local_fn(gsibench_noop);
extern declare_gsi_rpc_local_fn(gsibench_noop_return);
extern declare_gsi_rpc_local_fn(gsibench_noop_arg);
extern declare_gsi_rpc_local_fn(gsibench_noop_arg_return);
extern declare_gsi_rpc_local_fn(gsibench_finished_with_rpc);
extern declare_gsi_rpc_local_fn(gsibench_ready_for_noop);
extern declare_gsi_rpc_local_fn(gsibench_ready_for_noop_return);
extern declare_gsi_rpc_local_fn(gsibench_ready_for_noop_arg);
extern declare_gsi_rpc_local_fn(r_noop_arg_return);
extern declare_gsi_rpc_local_fn(gsibench_finished_with_rpc_thru);
extern declare_gsi_rpc_local_fn(gsibench_ready_for_noop_thru);
extern declare_gsi_rpc_local_fn(r_noop_return_thru);
extern declare_gsi_rpc_local_fn(r_noop_arg_thru);
extern declare_gsi_rpc_local_fn(r_noop_arg_return_thru);

extern declare_gsi_rpc_receiver_fn(gsibench_continue_rpc_call_ins);

#define GSI_REGRESSION_FILE "GSIregress.log"

void log_gsi_regression_message(message)
  char     *message;
{
  FILE	  *stream;

  stream = fopen(GSI_REGRESSION_FILE, "a");
  if (stream) {
    fprintf(stream, "%s", message);
    fclose(stream); }
}

main(argc, argv)
  int     argc;
  char   *argv[];
{
  gsi_start(argc, argv);
  return 0;
}

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

void gsi_set_up()
{
  gsi_install_error_handler(my_example_error_handler);

  gsi_rpc_declare_local(gsibench_noop,"GSIBENCH_NOOP");
  gsi_rpc_declare_local(gsibench_noop_return,"GSIBENCH_NOOP_RETURN");
  gsi_rpc_declare_local(gsibench_noop_arg,"GSIBENCH_NOOP_ARG");
  gsi_rpc_declare_local(gsibench_noop_arg_return,"GSIBENCH_NOOP_ARG_RETURN");
  gsi_rpc_declare_local(gsibench_finished_with_rpc,"GSIBENCH_FINISHED_WITH_RPC");
  gsi_rpc_declare_local(gsibench_ready_for_noop,"READY_FOR_NOOP");
  gsi_rpc_declare_local(gsibench_ready_for_noop_return,"READY_FOR_NOOP_RETURN");
  gsi_rpc_declare_local(gsibench_ready_for_noop_arg,"READY_FOR_NOOP_ARG");
  gsi_rpc_declare_local(r_noop_arg_return,"READY_FOR_NOOP_ARG_RETURN");
  gsi_rpc_declare_local(gsibench_finished_with_rpc_thru,"FINISHED_WITH_RPC_THRU"); 
  gsi_rpc_declare_local(gsibench_ready_for_noop_thru,"READY_FOR_NOOP_THRU");
  gsi_rpc_declare_local(r_noop_return_thru,"READY_FOR_NOOP_RETURN_THRU");
  gsi_rpc_declare_local(r_noop_arg_thru,"READY_FOR_NOOP_ARG_THRU");
  gsi_rpc_declare_local(r_noop_arg_return_thru,"R_NOOP_ARG_RETURN_THRU");

  ret_items = gsi_make_items(2);
  registered_items = gsi_make_registered_items(1);
  attribute_descriptions = gsi_make_attrs_with_items(NUMBER_OF_VECTOR_ATTRIBUTES);
}

/******************************
 * RPC calls from G2 into GSI *
 ******************************/

void gsibench_noop(arg_list,count, call_handle)
  gsi_item  arg_list[];
  gsi_int  count;
  call_identifier_type call_handle;
{
  set_int(ret_items[0],123);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);
}

void gsibench_noop_return(arg_list,count, call_handle)
  gsi_item  arg_list[];
  gsi_int   count;
  call_identifier_type call_handle;
{
  set_int(ret_items[0],123);
  set_flt(ret_items[1],123.456);
  gsi_rpc_return_values(ret_items,2,call_handle,current_context);
}

void gsibench_noop_arg(arg_list,count, call_handle)
  gsi_item  arg_list[];
  gsi_int   count;
  call_identifier_type call_handle;
{
  set_int(ret_items[0],123);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);
}

void gsibench_noop_arg_return(arg_list, count, call_handle)
  gsi_item  arg_list[];
  gsi_int   count;
  call_identifier_type call_handle;
{
  set_int(ret_items[0],123);
  set_flt(ret_items[1],123.456);
  gsi_rpc_return_values(ret_items,2,call_handle,current_context);
}


/******************************
 * RPC calls from GSI into G2 *
 ******************************/

/*
 * The following are utilities for measuring both latency and throughput
 * in RPC calls from GSI into G2.  Notice that, unlike RPC calls from G2 into
 * GSI, different mecahanisms are used to measure these two performance 
 * characteristics.
 */

void gsibench_continue_rpc_call_ins(args, count)
  gsi_item   args[];
  gsi_int    count;
{
 switch (gsi_to_g2_measurement_mode)
  {
   case MEASURING_LATENCY:
     gsi_rpc_call(current_call_in_handle,ret_items,current_context);
     return;
     break;

   case MEASURING_THROUGHPUT:
     if (--rpcs_outstanding == 0)
       gsi_rpc_start(handle_for_announce_rpcs_quiescent,NULL,current_context);
     rpcs_completed++;
     return;
     break;

   case MEASUREMENT_INACTIVE:
     return;
     break;

   default:
     printf("unknown GSI-to-G2 measurement mode %d\n", 
             gsi_to_g2_measurement_mode);
     break;
  }
}


/******************************
 * RPC calls from GSI into G2 *
 * (measuring latency)        *
 ******************************/

/* 
 * These functions keep calling into G2 until told to stop
 * when G2 calls gsibench_finished_with_rpc.  Latency is measured
 * because a new call won't start until the old one returns.
 */

void gsibench_finished_with_rpc(arg_list, count, call_handle)
  gsi_item    arg_list[];
  gsi_int     count;
  call_identifier_type call_handle;
{
  set_int(ret_items[0],1);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);

  current_call_in_argcount = 0;
  gsi_to_g2_measurement_mode = MEASUREMENT_INACTIVE;
}

void gsibench_ready_for_noop (arg_list, count, call_handle)
  gsi_item arg_list[];
  gsi_int  count;
  call_identifier_type call_handle;
{
  set_int(ret_items[0],1);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);

  gsi_to_g2_measurement_mode = MEASURING_LATENCY;
  current_call_in_handle = handle_for_noop;
  current_call_in_argcount = 0;

  gsibench_continue_rpc_call_ins(0,0);
}

void gsibench_ready_for_noop_return (arg_list, count, call_handle)
  gsi_item arg_list[];
  gsi_int count;
  call_identifier_type call_handle;
{
  set_int(ret_items[0],1);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);

  gsi_to_g2_measurement_mode = MEASURING_LATENCY;

  current_call_in_handle = handle_for_noop_return;
  current_call_in_argcount = 0;

  gsibench_continue_rpc_call_ins(0,0);
}

void gsibench_ready_for_noop_arg (arg_list, count, call_handle)
  gsi_item arg_list[];
  gsi_int count;
  call_identifier_type call_handle;
{
  set_int(ret_items[0],1);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);

  gsi_to_g2_measurement_mode = MEASURING_LATENCY;

  current_call_in_handle = handle_for_noop_arg;
  current_call_in_argcount = 2;

  set_int(ret_items[0],123);
  set_flt(ret_items[1],123.456);

  gsibench_continue_rpc_call_ins(0,0);
}


void r_noop_arg_return (arg_list, count, call_handle)
  gsi_item arg_list[];
  gsi_int count;
  call_identifier_type call_handle;
{
  set_int(ret_items[0],1);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);

  gsi_to_g2_measurement_mode = MEASURING_LATENCY;

  current_call_in_handle = handle_for_noop_arg_return;
  current_call_in_argcount = 2;

  set_int(ret_items[0],123);
  set_flt(ret_items[1],123.456);

  gsibench_continue_rpc_call_ins(0,0);
}


/******************************
 * RPC calls from GSI into G2 *
 * (measuring throughput)     *
 ******************************/

/* 
 * We initiate a large number of calls into G2 simultaneously.
 * Throughput is measured by how many of these calls G2 can service
 * in a constant time interval.
 */

void gsibench_finished_with_rpc_thru(arg_list, count, call_handle)
  gsi_item   arg_list[];
  gsi_int    count;
  call_identifier_type call_handle;
{
  gsi_to_g2_measurement_mode = MEASUREMENT_INACTIVE;

  set_int(ret_items[0],rpcs_completed);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);
}

void gsibench_ready_for_noop_thru (arg_list, count, call_handle)
  gsi_item arg_list[];
  gsi_int count;
  call_identifier_type call_handle;
{
  gsi_int     i;

  set_int(ret_items[0],1);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);

  rpcs_outstanding = 0;
  rpcs_completed = 0;
  gsi_to_g2_measurement_mode = MEASURING_THROUGHPUT;

  for (i = 0; i < LARGE_NUMBER_OF_CALL_INS; i++) {
    rpcs_outstanding++;
    gsi_rpc_call(handle_for_noop,NULL,current_context); }
}

void r_noop_return_thru (arg_list, count, call_handle)
  gsi_item arg_list[];
  gsi_int count;
  call_identifier_type call_handle;
{
  gsi_int  i;

  set_int(ret_items[0],1);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);

  rpcs_outstanding = 0;
  rpcs_completed = 0;
  gsi_to_g2_measurement_mode = MEASURING_THROUGHPUT;

  for (i = 0; i < LARGE_NUMBER_OF_CALL_INS; i++) {
    rpcs_outstanding++;
    gsi_rpc_call(handle_for_noop_return,NULL,current_context); }
}

void r_noop_arg_thru (arg_list, count, call_handle)
  gsi_item arg_list[];
  gsi_int count;
  call_identifier_type call_handle;
{
  gsi_int            i; 

  set_int(ret_items[0],1);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);

  rpcs_outstanding = 0;
  rpcs_completed = 0;
  gsi_to_g2_measurement_mode = MEASURING_THROUGHPUT;

  set_int(ret_items[0],123);
  set_flt(ret_items[1],123.456);

  for (i = 0; i < LARGE_NUMBER_OF_CALL_INS; i++) {
    rpcs_outstanding++;
    gsi_rpc_call(handle_for_noop_arg,ret_items,current_context); }
}

void r_noop_arg_return_thru (arg_list, count, call_handle)
  gsi_item arg_list[];
  gsi_int count;
  call_identifier_type call_handle;
{
  gsi_int     i;

  set_int(ret_items[0],1);
  gsi_rpc_return_values(ret_items,1,call_handle,current_context);

  rpcs_outstanding = 0;
  rpcs_completed = 0;
  gsi_to_g2_measurement_mode = MEASURING_THROUGHPUT;

  set_int(ret_items[0],123);
  set_flt(ret_items[1],123.456);

  for (i = 0; i < LARGE_NUMBER_OF_CALL_INS; i++) {
    rpcs_outstanding++;
    gsi_rpc_call(handle_for_noop_arg_return,ret_items,current_context);}
}


/****************************
 * GSI bridge functions for *
 * benchmark test           *
 ****************************/

void gsi_get_timed_data(return_int, handle)
  gsi_int return_int;
  gsi_int handle;
{
  set_handle(registered_items[0],handle);
  set_status(registered_items[0],0);
  set_int(registered_items[0],return_int);
  set_timestamp(registered_items[0],encode_timestamp(1990,12,17,12,0,0));
  gsi_return_values(registered_items,1,current_context);
}

void gsi_get_vector_data(temp_arg,return_int)
  gsi_registered_item  temp_arg;
  gsi_int              return_int;
{
  char     attribute_buffer[40];
  gsi_int  j;

  set_int(temp_arg,return_int);

  for (j=0; j<NUMBER_OF_VECTOR_ATTRIBUTES; j++) {
    sprintf(attribute_buffer, "VECTOR_ATTRIBUTE_%d", j);
    set_attr_name(attribute_descriptions[j],attribute_buffer);
    set_int(attribute_descriptions[j],789 + j); }

  gsi_return_attrs(temp_arg,attribute_descriptions,NUMBER_OF_VECTOR_ATTRIBUTES,current_context);
}

void gsi_get_timed_vector_data(return_int, handle)
  gsi_int  return_int;
  gsi_int  handle;
{
  char     attribute_buffer[40];
  gsi_int  j;

  set_handle(registered_items[0],handle);
  set_status(registered_items[0],0);
  set_int(registered_items[0],return_int);
  set_timestamp(registered_items[0],encode_timestamp(1990,12,17,12,0,0));

  for (j=0; j < NUMBER_OF_VECTOR_ATTRIBUTES; j++) {
    sprintf(attribute_buffer, "ATTRIBUTE_%d", j);
    set_attr_name(attribute_descriptions[j],attribute_buffer);
    set_int(attribute_descriptions[j],789 + j);
    set_timestamp(attribute_descriptions[j],encode_timestamp(1990,12,17,12,0,0)); }

  gsi_return_attrs(registered_items[0],attribute_descriptions,NUMBER_OF_VECTOR_ATTRIBUTES,current_context);
}

parse_gsi_regression_info(initstring)
  char *initstring;
{
 char      regression_index_buff[80];
 char      regression_trace_mode_buff[80];
 gsi_int   regression_index_temp;
 gsi_int   regression_trace_mode_temp;
 gsi_int   i, len;

 sscanf(initstring, "%s %s", regression_index_buff, regression_trace_mode_buff);

 len = strlen(regression_index_buff);
         
 regression_index_temp = atoi(regression_index_buff);

 if (regression_index_temp < 0)
    {
     if (print_template_messages)
        printf("\nreceived regression init: doing nothing\n");
     return(FALSE);
    }

 len = strlen(regression_trace_mode_buff);
 for (i = 0; i < len; i++)
  {
   if (!isdigit(regression_trace_mode_buff[i]))
    {
     printf("Warning: unreadable GSI regression trace mode %s.  Disabling trace.\n",
            regression_trace_mode_buff); 
     regression_trace_mode = GSI_REGRESSION_TRACE_OFF;
     return(TRUE);
    }
  }

 regression_trace_mode_temp = atoi(regression_trace_mode_buff);

 switch (regression_trace_mode_temp)
  {
   case GSI_REGRESSION_TRACE_OFF:
   case GSI_REGRESSION_TRACE_ON:
   /* other GSI trace modes go here ... */

     if (print_template_messages)
        printf("selecting regression trace mode %d\n", regression_trace_mode_temp);
     regression_trace_mode = regression_trace_mode_temp;
     break;
   default:
     printf("Warning: unknown GSI regression trace mode %d.  Disabling trace.\n",
            regression_trace_mode_temp);
     regression_trace_mode = GSI_REGRESSION_TRACE_OFF;
     break;
  }

 return(TRUE);
 
} /* parse_gsi_regression_info */

init_gsi_regression(initstring)
  char  *initstring;
{
  gsi_int  parse_succeeded_p;

  parse_succeeded_p = parse_gsi_regression_info(initstring);
  return parse_succeeded_p;
}

gsi_int gsi_get_tcp_port()
{
  return(GSI_REGRESSION_PORT);
}

gsi_int gsi_initialize_context(initstring, length)
    char    *initstring;
    gsi_int  length;
{
  init_gsi_regression(initstring);
  gsi_rpc_declare_remote(&handle_for_noop_return,"INWARD-NOOP-RETURN",gsibench_continue_rpc_call_ins,0,2,current_context);
  gsi_rpc_declare_remote(&handle_for_noop_arg,"INWARD-NOOP-ARG",gsibench_continue_rpc_call_ins,2,0,current_context);
  gsi_rpc_declare_remote(&handle_for_noop,"INWARD-NOOP",gsibench_continue_rpc_call_ins,0,0,current_context);
  gsi_rpc_declare_remote(&handle_for_noop_arg_return,"INWARD-NOOP-ARG-RETURN",gsibench_continue_rpc_call_ins,2,2,current_context);
  gsi_rpc_declare_remote(&handle_for_announce_rpcs_quiescent,"ANNOUNCE-RPCS-QUIESCENT",NULL,0,0,current_context);

  return(GSI_ACCEPT);
}

void gsi_pause_context()
{}

void gsi_resume_context()
{}

void gsi_shutdown_context()
{
  printf("\nShutting down in gsi_shutdown");
}

void gsi_receive_registration(registration)
    gsi_registration registration;
{}

void gsi_get_data(arglist, argcount)
  gsi_registered_item arglist[];
  gsi_int             argcount;
{
  gsi_int             i, mode= UNKNOWN_GET_MODE;
  gsi_registration    first_sensor; 

  first_sensor = registration_of(handle_of(arglist[0]),current_context);

  if (type_of(identifying_attr_of(first_sensor,1)) != SYMBOL_TAG) {
    printf("non-symbolic sensor tag in get_data");
    return; }

  if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)), "GET-DATA"))
    mode = GET_DATA_MODE;
  else
  if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)), "SET-DATA"))
    mode = SET_DATA_MODE;

  if (mode == GET_DATA_MODE || mode == SET_DATA_MODE) {
    for (i = 0; i < argcount; i++)
      set_int(arglist[i],(mode == GET_DATA_MODE) ? 123 : 456);
    gsi_return_values(arglist,argcount,current_context); 
    return; }

  if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)),"GET-TIMED-DATA"))
    mode = GET_TIMED_DATA_MODE;
  else if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)),"SET-TIMED-DATA"))
    mode = SET_TIMED_DATA_MODE;
  else if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)),"GET-VECTOR-DATA"))
    mode = GET_VECTOR_DATA_MODE;
  else if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)),"SET-VECTOR-DATA"))
    mode = SET_VECTOR_DATA_MODE;
  else if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)),"GET-TIMED-VECTOR-DATA"))
    mode = GET_TIMED_VECTOR_DATA_MODE;
  else if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)),"SET-TIMED-VECTOR-DATA"))
    mode = SET_TIMED_VECTOR_DATA_MODE;

  for (i = 0; i < argcount; i++) {
    gsi_int     inherited_handle;

    inherited_handle = handle_of(arglist[i]);
    switch (mode) {
     case GET_TIMED_DATA_MODE: gsi_get_timed_data(123, inherited_handle);
          break;
     case SET_TIMED_DATA_MODE: gsi_get_timed_data(456, inherited_handle);
          break;
     case GET_VECTOR_DATA_MODE: gsi_get_vector_data(arglist[i], 123);
          break;
     case SET_VECTOR_DATA_MODE: gsi_get_vector_data(arglist[i], 456);
          break;
     case GET_TIMED_VECTOR_DATA_MODE: gsi_get_timed_vector_data(123, inherited_handle);
          break;
     case SET_TIMED_VECTOR_DATA_MODE: gsi_get_timed_vector_data(456, inherited_handle);
          break;

     default: printf("unknown get data mode %d", mode);
              return;
    }
  }
}

void gsi_set_data(arglist, argcount)
  gsi_registered_item arglist[];
  gsi_int             argcount;
{
  gsi_int             i, mode= UNKNOWN_GET_MODE;
  gsi_registration    first_sensor; 

  first_sensor = registration_of(handle_of(arglist[0]),current_context);

  if (type_of(identifying_attr_of(first_sensor,1)) != SYMBOL_TAG) {
    printf("non-symbolic sensor tag in set_data");
    return; }

  if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)),"SET-DATA")) {
    for (i = 0; i < argcount; i++)
      set_int(arglist[i],456);
    gsi_return_values(arglist,argcount,current_context); 
    return; }

  if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)),"SET-TIMED-DATA"))
    mode = SET_TIMED_DATA_MODE;
  else if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)),"SET-VECTOR-DATA"))
    mode = SET_VECTOR_DATA_MODE;
  else if (!strcmp(sym_of(identifying_attr_of(first_sensor,1)),"SET-TIMED-VECTOR-DATA"))
    mode = SET_TIMED_VECTOR_DATA_MODE;

  for (i = 0; i < argcount; i++) {
    gsi_int     inherited_handle;

    inherited_handle = handle_of(arglist[i]);
    switch (mode) {
     case SET_TIMED_DATA_MODE: gsi_get_timed_data(456, inherited_handle);
          break;
     case SET_VECTOR_DATA_MODE: gsi_get_vector_data(arglist[i], 456);
          break;
     case SET_TIMED_VECTOR_DATA_MODE: gsi_get_timed_vector_data(456, inherited_handle);
          break;

     default: printf("unknown set data mode %d", mode);
              return;
    }
  }
}

void gsi_g2_poll()
{}

void gsi_receive_deregistrations(arglist, argcount)
  gsi_registered_item arglist[];
  gsi_int             argcount;
{}

void gsi_receive_message(textstring, textstring_length)
  char       *textstring;
  gsi_int     textstring_length;
{}
