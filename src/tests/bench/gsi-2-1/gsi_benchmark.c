/*******************
 * gsi_benchmark.c *
 *******************/

/* 
 * jh, 10/29/90.
 * This is bridge code designed to get benchmarks for GSI performance,
 * so we know when we have improved it.  It is patterned after the
 * G2-to-G2 benchmarks of CPM and JRA, and contains a set of RPC functions
 * taking or not taking arguments, returning no or some values, and
 * calling into or out of G2.
 */

#include "gsi_icp.h"
#include "gsi_user.h"
#include "gsi_regress.h"

#include <stdio.h>

#ifndef NULL
#define NULL 0
#endif




#define PRINT_BENCH_MESSAGES 0

extern CORR_OBJ_TYPE   *GSI_OBJ_PTRS;


/******************************
 * RPC calls from G2 into GSI *
 ******************************/

/* These calls measure both latency and throughput from G2 into GSI. */



/* gsibench_noop takes no args and returns no values. */

int gsibench_noop (arg_list,count)
TEMP_PARAM       *arg_list[];
unsigned short    count;
{
 /* have to return at least one value, even if it's a dummy */
 /* ptr submitted, 10/30/90 */
 TEMP_PARAM ret_arg[1];

#if PRINT_BENCH_MESSAGES
    printf("\ngsibench_noop called\n");
#endif

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 123;

 RetRpcVals(ret_arg, 1);
 return(GSI_SUCCESS);
}


/* 
 * gsibench_noop_return takes no args and returns two values,
 * an int and a float. 
 */

int gsibench_noop_return (arg_list,count)
TEMP_PARAM        *arg_list[];
unsigned short     count;
{
 TEMP_PARAM ret_arg[2];

#if PRINT_BENCH_MESSAGES
    printf("\ngsibench_noop_return called\n");
#endif

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 123;

 ret_arg[1].p_type = FLOAT64_TAG;
 ret_arg[1].p_value.float_p = 123.456;

 RetRpcVals(ret_arg, 2);
 return(GSI_SUCCESS);
}


/*
 * gsibench_noop_arg takes two args, an int and a float, and
 * returns no values.
 */

int gsibench_noop_arg (arg_list,count)
TEMP_PARAM       *arg_list[];
unsigned short    count;
{
 /* have to return at least one value, even if it's a dummy */
 /* ptr submitted, 10/30/90 */
 TEMP_PARAM ret_arg[1];

#if PRINT_BENCH_MESSAGES
    printf("\ngsibench_noop_arg called\n");
#endif

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 123;

 /* 
  * The body of gsibench_noop_arg is identical to gsibench_noop, 
  * since the measured overhead should come exclusively from 
  * transmitting and "unpacking" the remote procedure arguments,
  * not from any processing in this body.
  */
 RetRpcVals(ret_arg, 1);
 return(GSI_SUCCESS);
}



/*
 * gsibench_noop_arg_return takes two args, an int and a float,
 * and returns two values, an int and a float.
 */

int gsibench_noop_arg_return (arg_list, count)
TEMP_PARAM       *arg_list[];
unsigned short    count;
{
 /*
  * The body of gsibench_noop_arg_return does no processing of the
  * rpc arglist, since the measured overhead should come exclusively
  * from transmitting and "unpacking" the remote procedure arguments,
  * not from any processing in this body.
  */
 TEMP_PARAM ret_arg[2];

#if PRINT_BENCH_MESSAGES
    printf("\ngsibench_noop_arg_return called\n");
#endif

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 123;

 ret_arg[1].p_type = FLOAT64_TAG;
 ret_arg[1].p_value.float_p = 123.456;

 RetRpcVals(ret_arg, 2);
 return(GSI_SUCCESS);
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

#define MEASUREMENT_INACTIVE  0
#define MEASURING_LATENCY    1
#define MEASURING_THROUGHPUT 2
int     gsi_to_g2_measurement_mode;

int     rpcs_completed = 0; /* for latency measurements */

int     rpc_events = 0;

int rpcs_outstanding = 0;

#define MAX_CALL_IN_ARGS 5


unsigned short     handle_for_announce_rpcs_quiescent;


unsigned short  current_call_in_handle;
TEMP_PARAM      current_call_in_args[MAX_CALL_IN_ARGS];
int             current_call_in_argcount;

gsibench_continue_rpc_call_ins(args, count)
TEMP_PARAM       *args[];
unsigned short    count;
{
 switch (gsi_to_g2_measurement_mode)
  {
   case MEASURING_LATENCY:
   g2_call_rpc(current_call_in_handle, 
               current_call_in_args, 
               current_call_in_argcount);
   return(GSI_SUCCESS);
   break;

   case MEASURING_THROUGHPUT:
#if PRINT_BENCH_MESSAGES
      printf(".");
      if (rpc_events++ % 80 == 79) printf("\n");
#endif
   if (--rpcs_outstanding == 0)
      g2_start_rpc(handle_for_announce_rpcs_quiescent,
                   NULL,
                   0);
   rpcs_completed++;
   return(GSI_SUCCESS);
   break;

   case MEASUREMENT_INACTIVE:
   return(GSI_SUCCESS);
   break;

   otherwise:
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

gsibench_finished_with_rpc(arg_list, count)
TEMP_PARAM        *arg_list[];
unsigned short     count;
{
 TEMP_PARAM ret_arg[1];

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 1;
 RetRpcVals(ret_arg, 1);

#if PRINT_BENCH_MESSAGES
    printf("\ngsibench_finished_with_rpc returned\n");
#endif

 current_call_in_argcount = 0;
 gsi_to_g2_measurement_mode = MEASUREMENT_INACTIVE;
}


unsigned short     handle_for_noop;
unsigned short     handle_for_noop_return;
unsigned short     handle_for_noop_arg;
unsigned short     handle_for_noop_arg_return;



gsibench_ready_for_noop (arg_list, count)
TEMP_PARAM *arg_list[];
unsigned short count;
{
 TEMP_PARAM ret_arg[1];

#if PRINT_BENCH_MESSAGES
    rpc_events = 0;
    printf("\nentering gsibench_ready_for_noop\n");
#endif

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 1;
 RetRpcVals(ret_arg, 1);

#if PRINT_BENCH_MESSAGES
    printf("\ngsibench_ready_for_noop returned\n");
#endif

 gsi_to_g2_measurement_mode = MEASURING_LATENCY;

 current_call_in_handle = handle_for_noop;
 current_call_in_argcount = 0;

 gsibench_continue_rpc_call_ins();
}


gsibench_ready_for_noop_return (arg_list, count)
TEMP_PARAM *arg_list[];
unsigned short count;
{
 TEMP_PARAM ret_arg[1];

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 1;
 RetRpcVals(ret_arg, 1);

#if PRINT_BENCH_MESSAGES
    rpc_events = 0;
    printf("\ngsibench_ready_for_noop_return returned\n");
#endif

 gsi_to_g2_measurement_mode = MEASURING_LATENCY;

 current_call_in_handle = handle_for_noop_return;
 current_call_in_argcount = 0;

 gsibench_continue_rpc_call_ins();
}

gsibench_ready_for_noop_arg (arg_list, count)
TEMP_PARAM *arg_list[];
unsigned short count;
{
 TEMP_PARAM ret_arg[1];

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 1;
 RetRpcVals(ret_arg, 1);

#if PRINT_BENCH_MESSAGES
    rpc_events = 0;
    printf("\ngsibench_ready_for_noop_arg returned\n");
#endif

 gsi_to_g2_measurement_mode = MEASURING_LATENCY;

 current_call_in_handle = handle_for_noop_arg;
 current_call_in_argcount = 2;

 current_call_in_args[0].p_type = INTEGER_TAG;
 current_call_in_args[0].p_value.integer_p = 123;

 current_call_in_args[1].p_type = FLOAT64_TAG;
 current_call_in_args[1].p_value.float_p = 123.456;

 gsibench_continue_rpc_call_ins();
}


r_noop_arg_return (arg_list, count)
TEMP_PARAM *arg_list[];
unsigned short count;
{
 TEMP_PARAM ret_arg[1];

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 1;
 RetRpcVals(ret_arg, 1);

#if PRINT_BENCH_MESSAGES
    rpc_events = 0;
    printf("\nr_noop_arg_return returned\n");
#endif

 gsi_to_g2_measurement_mode = MEASURING_LATENCY;

 current_call_in_handle = handle_for_noop_arg_return;
 current_call_in_argcount = 2;

 current_call_in_args[0].p_type = INTEGER_TAG;
 current_call_in_args[0].p_value.integer_p = 123;

 current_call_in_args[1].p_type = FLOAT64_TAG;
 current_call_in_args[1].p_value.float_p = 123.456;

 gsibench_continue_rpc_call_ins();
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

#define LARGE_NUMBER_OF_CALL_INS 510 /* > 500 sometimes causes a crash */

gsibench_finished_with_rpc_thru(arg_list, count)
TEMP_PARAM        *arg_list[];
unsigned short     count;
{
 TEMP_PARAM     ret_arg[1];

#if PRINT_BENCH_MESSAGES
    printf("\nfinished_with_rpc_thru called\n");
#endif

 gsi_to_g2_measurement_mode = MEASUREMENT_INACTIVE;

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = rpcs_completed;

#if PRINT_BENCH_MESSAGES
    printf("\nfinished_with_rpc_thru returned\n");
#endif

 RetRpcVals(ret_arg,1);
 return(GSI_SUCCESS);
}


gsibench_ready_for_noop_thru (arg_list, count)
TEMP_PARAM *arg_list[];
unsigned short count;
{
 int     i;
 TEMP_PARAM ret_arg[1];

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 1;
 RetRpcVals(ret_arg, 1);

#if PRINT_BENCH_MESSAGES
    rpc_events = 0;
    printf("\ngsibench_ready_for_noop_thru returned\n");
#endif

 rpcs_outstanding = 0;
 rpcs_completed = 0;
 gsi_to_g2_measurement_mode = MEASURING_THROUGHPUT;

 for (i = 0; i < LARGE_NUMBER_OF_CALL_INS; i++)
     {

#if PRINT_BENCH_MESSAGES
      printf("!");
      if (rpc_events++ % 80 == 79) printf("\n");
#endif
      rpcs_outstanding++;
      g2_call_rpc(handle_for_noop,
    	         NULL,
        	 0);
      }
}


r_noop_return_thru (arg_list, count)
TEMP_PARAM *arg_list[];
unsigned short count;
{
 int     i;
 TEMP_PARAM ret_arg[1];

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 1;
 RetRpcVals(ret_arg, 1);

#if PRINT_BENCH_MESSAGES
    rpc_events = 0;
    printf("\nr_noop_return_thru returned\n");
#endif

 rpcs_outstanding = 0;
 rpcs_completed = 0;
 gsi_to_g2_measurement_mode = MEASURING_THROUGHPUT;

 for (i = 0; i < LARGE_NUMBER_OF_CALL_INS; i++)
     {
      rpcs_outstanding++;
      g2_call_rpc(handle_for_noop_return,
    	         NULL,
        	 0);
     }
}

r_noop_arg_thru (arg_list, count)
TEMP_PARAM *arg_list[];
unsigned short count;
{
 int            i; 
 TEMP_PARAM     ret_arg[2];

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 1;
 RetRpcVals(ret_arg, 1);

#if PRINT_BENCH_MESSAGES
    rpc_events = 0;
    printf("\nr_noop_arg_thru returned\n");
#endif

 rpcs_outstanding = 0;
 rpcs_completed = 0;
 gsi_to_g2_measurement_mode = MEASURING_THROUGHPUT;

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 123;

 ret_arg[1].p_type = FLOAT64_TAG;
 ret_arg[1].p_value.float_p = 123.456;

 for (i = 0; i < LARGE_NUMBER_OF_CALL_INS; i++)
     {
      rpcs_outstanding++;
      g2_call_rpc(handle_for_noop_arg,
    	         ret_arg,
        	 2);
     }
}


r_noop_arg_return_thru (arg_list, count)
TEMP_PARAM *arg_list[];
unsigned short count;
{
 int     i;
 TEMP_PARAM     ret_arg[2];

#if PRINT_BENCH_MESSAGES
    rpc_events = 0;
    printf("\nr_noop_arg_return_thru called\n");
#endif

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 1;
 RetRpcVals(ret_arg, 1);

#if PRINT_BENCH_MESSAGES
    rpc_events = 0;
    printf("\nr_noop_arg_return_thru returned\n");
#endif

 rpcs_outstanding = 0;
 rpcs_completed = 0;
 gsi_to_g2_measurement_mode = MEASURING_THROUGHPUT;

 ret_arg[0].p_type = INTEGER_TAG;
 ret_arg[0].p_value.integer_p = 123;

 ret_arg[1].p_type = FLOAT64_TAG;
 ret_arg[1].p_value.float_p = 123.456;

 for (i = 0; i < LARGE_NUMBER_OF_CALL_INS; i++)
     {
      rpcs_outstanding++;
      g2_call_rpc(handle_for_noop_arg_return,
    	          ret_arg,
        	  2);
     }
}





/****************************
 * GSI bridge functions for *
 * benchmark test           *
 ****************************/



bench_gsi_init_ds(init_str, str_len)
    char            *init_str;
    unsigned long    str_len;
{
 int     status, deletable;


 status = declare_g2_rpc("INWARD-NOOP-RETURN", 
                         gsibench_continue_rpc_call_ins, 
                         0, 2, &handle_for_noop_return);
 status = declare_g2_rpc("INWARD-NOOP-ARG", 
                         gsibench_continue_rpc_call_ins, 
                         2, 0, &handle_for_noop_arg);
 /* the third declaration is bad luck - tell pvl */
 status = declare_g2_rpc("DELETABLE",
		         gsibench_continue_rpc_call_ins, 
                         0, 0, &deletable);
 status = declare_g2_rpc("INWARD-NOOP", 
		         gsibench_continue_rpc_call_ins, 
                         0, 0, &handle_for_noop);
 status = declare_g2_rpc("INWARD-NOOP-ARG-RETURN", 
                         gsibench_continue_rpc_call_ins, 
                         2, 2, &handle_for_noop_arg_return);
 status = declare_g2_rpc("ANNOUNCE-RPCS-QUIESCENT", 
                         NULL,
                         0, 0, &handle_for_announce_rpcs_quiescent);

#if PRINT_BENCH_MESSAGES
    printf("bench_gsi_init_ds called\n");
#endif
}






bench_gsi_pause_ds()
{
#if PRINT_BENCH_MESSAGES
    printf("gsi_pause_ds called\n");
#endif
return;
}




bench_gsi_resume_ds()
{
#if PRINT_BENCH_MESSAGES
    printf("gsi_resume_ds called\n");
#endif
return;
}




bench_gsi_shutdown()
{
#if PRINT_BENCH_MESSAGES
    printf("\nbench_gsi_shutdown_ds called\n");
#endif
return;
}




bench_gsi_def_obj(new, old)
USER_ARG_TYPE     *new, *old;
{
#if PRINT_BENCH_MESSAGES
 printf("\nbench_gsi_def_obj called\n");
#endif
return;
}


gsi_get_timed_data(return_int, index)
int                return_int;
int                index;
{
 TIME_ARG_TYPE      time_arg[1];
 int                j;

 time_arg[0].obj_index = index;

 time_arg[0].value.p_type = INTEGER_TAG;
 time_arg[0].value.p_value.integer_p = return_int;

 time_arg[0].date.year = 1990;
 time_arg[0].date.month = 12;
 time_arg[0].date.day = 17;
 time_arg[0].date.hour = 12;
 time_arg[0].date.minute = 0;
 time_arg[0].date.second = 0;

 gsi_ret_tvals(time_arg, 1);
}


#define NUMBER_OF_VECTOR_ATTRIBUTES 3

gsi_get_vector_data(temp_arg, return_int)
TEMP_ARG_TYPE     *temp_arg;
int                return_int;
{
 char               attribute_buffer;
 VECTOR_TYPE        attribute_description[NUMBER_OF_VECTOR_ATTRIBUTES];
 int                j;

 temp_arg->value.p_type = INTEGER_TAG;
 temp_arg->value.p_value.integer_p = return_int;

 for (j=0; j < NUMBER_OF_VECTOR_ATTRIBUTES; j++)
  {
   sprintf(attribute_description[j].attribute, "VECTOR_ATTRIBUTE_%d", j);

   attribute_description[j].value.p_type = INTEGER_TAG;
   attribute_description[j].value.p_value.integer_p = 789 + j;
  }
 gsi_ret_vector(temp_arg, attribute_description, NUMBER_OF_VECTOR_ATTRIBUTES);
}


gsi_get_timed_vector_data(return_int, index)
int                return_int;
int                index;
{
 TIME_ARG_TYPE      time_arg;
 VECTOR_TYPE        attribute_description[NUMBER_OF_VECTOR_ATTRIBUTES];
 int                j;

 time_arg.obj_index = index;

 time_arg.value.p_type = INTEGER_TAG;
 time_arg.value.p_value.integer_p = return_int;

 time_arg.date.year = 1990;
 time_arg.date.month = 12;
 time_arg.date.day = 17;
 time_arg.date.hour = 12;
 time_arg.date.minute = 0;
 time_arg.date.second = 0;

 for (j=0; j < NUMBER_OF_VECTOR_ATTRIBUTES; j++)
  {
   sprintf(attribute_description[j].attribute, "ATTRIBUTE_%d", j);

   attribute_description[j].value.p_type = INTEGER_TAG;
   attribute_description[j].value.p_value.integer_p = 789 + j;
  }
 gsi_ret_tvector(time_arg, attribute_description, NUMBER_OF_VECTOR_ATTRIBUTES);
}



#define UNKNOWN_GET_MODE            0
#define GET_DATA_MODE               1
#define SET_DATA_MODE               2
#define GET_TIMED_DATA_MODE         3
#define SET_TIMED_DATA_MODE         4
#define GET_VECTOR_DATA_MODE        5
#define SET_VECTOR_DATA_MODE        6
#define GET_TIMED_VECTOR_DATA_MODE  7
#define SET_TIMED_VECTOR_DATA_MODE  8

bench_gsi_get_data(arglist, argcount)
TEMP_ARG_TYPE     *arglist;
short int          argcount;
{
 int                i, mode= UNKNOWN_GET_MODE;
 USER_ARG_TYPE     *first_sensor; 

#if PRINT_BENCH_MESSAGES
 printf("\nbench_gsi_get_data called\n");
#endif

 first_sensor = GSI_OBJ_PTRS[arglist[0].obj_index].obj_ptr;

 if (first_sensor->param_1.p_type != SYMBOL_TAG)
  {
   printf("non-symbolic sensor tag in get_data");
   return;
  }

 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "GET-DATA"))
    mode = GET_DATA_MODE;
 else
 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "SET-DATA"))
    mode = SET_DATA_MODE;

 if (mode == GET_DATA_MODE || mode == SET_DATA_MODE)
  {
   for (i = 0; i < argcount; i++)
    {
     arglist[i].value.p_type = INTEGER_TAG;
     arglist[i].value.p_value.integer_p = (mode == GET_DATA_MODE) ? 123 : 456;
    }
   gsi_ret_vals(arglist, argcount); 
   return;
  }

 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "GET-TIMED-DATA"))
    mode = GET_TIMED_DATA_MODE;
 else
 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "SET-TIMED-DATA"))
    mode = SET_TIMED_DATA_MODE;
 else
 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "GET-VECTOR-DATA"))
    mode = GET_VECTOR_DATA_MODE;
 else
 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "SET-VECTOR-DATA"))
    mode = SET_VECTOR_DATA_MODE;
 else
 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "GET-TIMED-VECTOR-DATA"))
    mode = GET_TIMED_VECTOR_DATA_MODE;
 else
 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "SET-TIMED-VECTOR-DATA"))
    mode = SET_TIMED_VECTOR_DATA_MODE;

 for (i = 0; i < argcount; i++)
  {
   int     inherited_index;

   inherited_index = arglist[i].obj_index;
   switch (mode)
    {
     case GET_TIMED_DATA_MODE: gsi_get_timed_data(123, inherited_index);
          break;
     case SET_TIMED_DATA_MODE: gsi_get_timed_data(456, inherited_index);
          break;
     case GET_VECTOR_DATA_MODE: gsi_get_vector_data(arglist+i, 123);
          break;
     case SET_VECTOR_DATA_MODE: gsi_get_vector_data(arglist+i, 456);
          break;
     case GET_TIMED_VECTOR_DATA_MODE: gsi_get_timed_vector_data(123, inherited_index);
          break;
     case SET_TIMED_VECTOR_DATA_MODE: gsi_get_timed_vector_data(456, inherited_index);
          break;

     default: printf("unknown get data mode %d", mode);
              return;
    }
  }
}




bench_gsi_set_data(arglist, argcount)
TEMP_ARG_TYPE     *arglist;
short int          argcount;
{
 int                i, mode= UNKNOWN_GET_MODE;
 USER_ARG_TYPE     *first_sensor; 

#if PRINT_BENCH_MESSAGES
 printf("\nbench_gsi_get_data called\n");
#endif

 first_sensor = GSI_OBJ_PTRS[arglist[0].obj_index].obj_ptr;

 if (first_sensor->param_1.p_type != SYMBOL_TAG)
  {
   printf("non-symbolic sensor tag in get_data");
   return;
  }

 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "SET-DATA"))
  {
   for (i = 0; i < argcount; i++)
    {
     arglist[i].value.p_type = INTEGER_TAG;
     arglist[i].value.p_value.integer_p = 456;
    }
   gsi_ret_vals(arglist, argcount); 
   return;
  }

 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "SET-TIMED-DATA"))
    mode = SET_TIMED_DATA_MODE;
 else
 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "SET-VECTOR-DATA"))
    mode = SET_VECTOR_DATA_MODE;
 else
 if (!strcmp(first_sensor->param_1.p_value.symbol_p, "SET-TIMED-VECTOR-DATA"))
    mode = SET_TIMED_VECTOR_DATA_MODE;

 for (i = 0; i < argcount; i++)
  {
   int     inherited_index;

   inherited_index = arglist[i].obj_index;
   switch (mode)
    {
     case SET_TIMED_DATA_MODE: gsi_get_timed_data(456, inherited_index);
          break;
     case SET_VECTOR_DATA_MODE: gsi_get_vector_data(arglist+i, 456);
          break;
     case SET_TIMED_VECTOR_DATA_MODE: gsi_get_timed_vector_data(456, inherited_index);
          break;

     default: printf("unknown set data mode %d", mode);
              return;
    }
  }
}





bench_gsi_accept_data()
{
return;
}




bench_gsi_stop_data(arglist, argcount)
TEMP_ARG_TYPE     *arglist;
short int          argcount;
{
return;
}






bench_gsi_rd_txt(textstring, textstring_length, object_index)
char         *textstring;
short int     textstring_length, object_index;
{
return;
}
 


bench_InitUsrRpcs()
{
#if PRINT_BENCH_MESSAGES
    printf("\nInitUsrRpcs called\n");
#endif
return;
}