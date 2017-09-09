/*****************
 * gsi_regress.c *
 *****************/

/* jh, 6/3/90 */

/* 
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
#include <ctype.h>
#include "gsi_icp.h"
#include "gsi_user.h"

extern CORR_OBJ_TYPE   *GSI_OBJ_PTRS;

extern unsigned short *EXT_STATUS;
extern unsigned short CurrentContext;
extern unsigned long IcpMode;
extern unsigned short *DO_EXT_PROC;



#define GSI_REGRESSION_PORT 33333




/* must be checked for each feature addition */
#define GSI_INIT_DS_INDEX      0
#define GSI_PAUSE_DS_INDEX     1
#define GSI_RESUME_DS_INDEX    2
#define GSI_SHUTDOWN_INDEX     3
#define GSI_DEF_OBJ_INDEX      4
#define GSI_GET_DATA_INDEX     5
#define GSI_SET_DATA_INDEX     6
#define GSI_ACCEPT_DATA_INDEX  7
#define GSI_STOP_DATA_INDEX    8
#define GSI_RD_TXT_INDEX       9

/* must be checked for each new regression test */
#define MAX_GSI_REGRESSIONS     100

/* must be checked for each feature addition */
#define MAX_GSI_BRIDGES         20




/* 
 * regression_hooks is a global table which holds all 
 * known regression test bridge functions.
 * It is initialized by fill_gsi_regression_hooks below 
 */
int    (*regression_hooks[MAX_GSI_REGRESSIONS][MAX_GSI_BRIDGES])();



/* 
 * regression_index is a global variable which holds
 * the current regression test number.
 * It is set by parse_gsi_regression_info below.
 * This variable is -1 if no regression test is intended, as
 * is the case during initialization.
 */
int regression_index = -1;




#define GSI_REGRESSION_TRACE_OFF 0
#define GSI_REGRESSION_TRACE_ON  1

/* 
 * regression_trace_mode is a global variable which holds
 * the current regression trace mode.
 * It is set by parse_gsi_regression_info below.
 */

int      regression_trace_mode;

int      print_template_messages = 1;


/* 
 *The following function is a dummy required by the beta 3 enhancements.
 * Make sure allow_ext_proc has not been #defined earlier, 
 * say by gsi_icp.h.
 */
int allow_ext_proc() {return(1);}




parse_gsi_regression_info(initstring)
{
 char      regression_index_buff[80];
 char      regression_trace_mode_buff[80];
 int       regression_index_temp;
 int       regression_trace_mode_temp;
 int       i, len;

 sscanf(initstring, "%s %s", regression_index_buff, regression_trace_mode_buff);

 len = strlen(regression_index_buff);
         
 regression_index_temp = atoi(regression_index_buff);

 if (regression_index_temp < 0)
    {
     if (print_template_messages)
        printf("\nreceived regression init: doing nothing\n");
     regression_index = -1;
     return(FALSE);
    }

 if (regression_index_temp < MAX_GSI_REGRESSIONS)
  {
   if (print_template_messages)
      printf("\nselecting regression test #%d\n", regression_index_temp);
   regression_index = regression_index_temp;
  }
 else
  {
   printf("Out of bounds GSI regression index %d.  Sorry, can't continue.\n",
          regression_index_temp);
   exit(0);
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


/* 
 *The externs for each regression hook are not in a separate
 * include file because they are only used here.
 */

/*
extern basic_gsi_init_ds();
extern basic_gsi_pause_ds();
extern basic_gsi_resume_ds();
extern basic_gsi_shutdown();
extern basic_gsi_def_obj();
extern basic_gsi_get_data();
extern basic_gsi_set_data();
extern basic_gsi_accept_data();
extern basic_gsi_stop_data();
extern basic_gsi_rd_txt();


extern mutable_gsi_init_ds();
extern mutable_gsi_pause_ds();
extern mutable_gsi_resume_ds();
extern mutable_gsi_shutdown();
extern mutable_gsi_def_obj();
extern mutable_gsi_get_data();
extern mutable_gsi_set_data();
extern mutable_gsi_accept_data();
extern mutable_gsi_stop_data();
extern mutable_gsi_rd_txt();


extern spurious_gsi_init_ds();
extern spurious_gsi_pause_ds();
extern spurious_gsi_resume_ds();
extern spurious_gsi_shutdown();
extern spurious_gsi_def_obj();
extern spurious_gsi_get_data();
extern spurious_gsi_set_data();
extern spurious_gsi_accept_data();
extern spurious_gsi_stop_data();
extern spurious_gsi_rd_txt();


extern disappear_gsi_init_ds();
extern disappear_gsi_pause_ds();
extern disappear_gsi_resume_ds();
extern disappear_gsi_shutdown();
extern disappear_gsi_def_obj();
extern disappear_gsi_get_data();
extern disappear_gsi_set_data();
extern disappear_gsi_accept_data();
extern disappear_gsi_stop_data();
extern disappear_gsi_rd_txt();


extern crosstalk_gsi_init_ds();
extern crosstalk_gsi_pause_ds();
extern crosstalk_gsi_resume_ds();
extern crosstalk_gsi_shutdown();
extern crosstalk_gsi_def_obj();
extern crosstalk_gsi_get_data();
extern crosstalk_gsi_set_data();
extern crosstalk_gsi_accept_data();
extern crosstalk_gsi_stop_data();
extern crosstalk_gsi_rd_txt();


extern timestamp_gsi_init_ds();
extern timestamp_gsi_pause_ds();
extern timestamp_gsi_resume_ds();
extern timestamp_gsi_shutdown();
extern timestamp_gsi_def_obj();
extern timestamp_gsi_get_data();
extern timestamp_gsi_set_data();
extern timestamp_gsi_accept_data();
extern timestamp_gsi_stop_data();
extern timestamp_gsi_rd_txt();


extern typetest_gsi_init_ds();
extern typetest_gsi_pause_ds();
extern typetest_gsi_resume_ds();
extern typetest_gsi_shutdown();
extern typetest_gsi_def_obj();
extern typetest_gsi_get_data();
extern typetest_gsi_set_data();
extern typetest_gsi_accept_data();
extern typetest_gsi_stop_data();
extern typetest_gsi_rd_txt();


extern rpc_file_gsi_init_ds();
extern rpc_file_gsi_pause_ds();
extern rpc_file_gsi_resume_ds();
extern rpc_file_gsi_shutdown();
extern rpc_file_gsi_def_obj();
extern rpc_file_gsi_get_data();
extern rpc_file_gsi_set_data();
extern rpc_file_gsi_accept_data();
extern rpc_file_gsi_stop_data();
extern rpc_file_gsi_rd_txt();


extern rpc_types_gsi_init_ds();
extern rpc_types_gsi_pause_ds();
extern rpc_types_gsi_resume_ds();
extern rpc_types_gsi_shutdown();
extern rpc_types_gsi_def_obj();
extern rpc_types_gsi_get_data();
extern rpc_types_gsi_set_data();
extern rpc_types_gsi_accept_data();
extern rpc_types_gsi_stop_data();
extern rpc_types_gsi_rd_txt();



extern skeleton_gsi_init_ds();
extern skeleton_gsi_pause_ds();
extern skeleton_gsi_resume_ds();
extern skeleton_gsi_shutdown();
extern skeleton_gsi_def_obj();
extern skeleton_gsi_get_data();
extern skeleton_gsi_set_data();
extern skeleton_gsi_accept_data();
extern skeleton_gsi_stop_data();
extern skeleton_gsi_rd_txt();


extern floats_gsi_init_ds();
extern floats_gsi_pause_ds();
extern floats_gsi_resume_ds();
extern floats_gsi_shutdown();
extern floats_gsi_def_obj();
extern floats_gsi_get_data();
extern floats_gsi_set_data();
extern floats_gsi_accept_data();
extern floats_gsi_stop_data();
extern floats_gsi_rd_txt();


extern time_stamp_gsi_init_ds();
extern time_stamp_gsi_pause_ds();
extern time_stamp_gsi_resume_ds();
extern time_stamp_gsi_shutdown();
extern time_stamp_gsi_def_obj();
extern time_stamp_gsi_get_data();
extern time_stamp_gsi_set_data();
extern time_stamp_gsi_accept_data();
extern time_stamp_gsi_stop_data();
extern time_stamp_gsi_rd_txt();


extern retmsg_gsi_init_ds();
extern retmsg_gsi_pause_ds();
extern retmsg_gsi_resume_ds();
extern retmsg_gsi_shutdown();
extern retmsg_gsi_def_obj();
extern retmsg_gsi_get_data();
extern retmsg_gsi_set_data();
extern retmsg_gsi_accept_data();
extern retmsg_gsi_stop_data();
extern retmsg_gsi_rd_txt();



extern watchdog_gsi_init_ds();
extern watchdog_gsi_pause_ds();
extern watchdog_gsi_resume_ds();
extern watchdog_gsi_shutdown();
extern watchdog_gsi_def_obj();
extern watchdog_gsi_get_data();
extern watchdog_gsi_set_data();
extern watchdog_gsi_accept_data();
extern watchdog_gsi_stop_data();
extern watchdog_gsi_rd_txt();


extern singlept_gsi_init_ds();
extern singlept_gsi_pause_ds();
extern singlept_gsi_resume_ds();
extern singlept_gsi_shutdown();
extern singlept_gsi_def_obj();
extern singlept_gsi_get_data();
extern singlept_gsi_set_data();
extern singlept_gsi_accept_data();
extern singlept_gsi_stop_data();
extern singlept_gsi_rd_txt();
*/

extern bench_gsi_init_ds();
extern bench_gsi_pause_ds();
extern bench_gsi_resume_ds();
extern bench_gsi_shutdown();
extern bench_gsi_def_obj();
extern bench_gsi_get_data();
extern bench_gsi_set_data();
extern bench_gsi_accept_data();
extern bench_gsi_stop_data();
extern bench_gsi_rd_txt();

/* the above externs must be edited for each new regression test */




clear_gsi_regression_hooks()
{
 int    i;

 for (i = 0; i < MAX_GSI_REGRESSIONS; i++)
     {
      regression_hooks[GSI_INIT_DS_INDEX]    [i] = 0;
      regression_hooks[GSI_PAUSE_DS_INDEX]   [i] = 0;
      regression_hooks[GSI_RESUME_DS_INDEX]  [i] = 0;
      regression_hooks[GSI_SHUTDOWN_INDEX]   [i] = 0;
      regression_hooks[GSI_DEF_OBJ_INDEX]    [i] = 0;
      regression_hooks[GSI_GET_DATA_INDEX]   [i] = 0;
      regression_hooks[GSI_SET_DATA_INDEX]   [i] = 0;
      regression_hooks[GSI_ACCEPT_DATA_INDEX][i] = 0;
      regression_hooks[GSI_STOP_DATA_INDEX]  [i] = 0;
      regression_hooks[GSI_RD_TXT_INDEX]     [i] = 0;
     }
}



fill_gsi_regression_hooks()
{
 /* must be edited for each new regression test */ 

/*
 regression_hooks[GSI_INIT_DS_INDEX]    [0] = basic_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [0] = basic_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [0] = basic_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [0] = basic_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [0] = basic_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [0] = basic_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [0] = basic_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][0] = basic_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [0] = basic_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [0] = basic_gsi_rd_txt;

 regression_hooks[GSI_INIT_DS_INDEX]    [1] = mutable_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [1] = mutable_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [1] = mutable_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [1] = mutable_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [1] = mutable_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [1] = mutable_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [1] = mutable_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][1] = mutable_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [1] = mutable_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [1] = mutable_gsi_rd_txt;

 regression_hooks[GSI_INIT_DS_INDEX]    [2] = spurious_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [2] = spurious_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [2] = spurious_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [2] = spurious_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [2] = spurious_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [2] = spurious_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [2] = spurious_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][2] = spurious_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [2] = spurious_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [2] = spurious_gsi_rd_txt;

 regression_hooks[GSI_INIT_DS_INDEX]    [3] = disappear_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [3] = disappear_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [3] = disappear_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [3] = disappear_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [3] = disappear_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [3] = disappear_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [3] = disappear_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][3] = disappear_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [3] = disappear_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [3] = disappear_gsi_rd_txt;

 regression_hooks[GSI_INIT_DS_INDEX]    [4] = crosstalk_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [4] = crosstalk_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [4] = crosstalk_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [4] = crosstalk_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [4] = crosstalk_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [4] = crosstalk_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [4] = crosstalk_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][4] = crosstalk_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [4] = crosstalk_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [4] = crosstalk_gsi_rd_txt;


 regression_hooks[GSI_INIT_DS_INDEX]    [5] = timestamp_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [5] = timestamp_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [5] = timestamp_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [5] = timestamp_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [5] = timestamp_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [5] = timestamp_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [5] = timestamp_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][5] = timestamp_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [5] = timestamp_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [5] = timestamp_gsi_rd_txt;


 regression_hooks[GSI_INIT_DS_INDEX]    [6] = typetest_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [6] = typetest_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [6] = typetest_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [6] = typetest_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [6] = typetest_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [6] = typetest_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [6] = typetest_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][6] = typetest_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [6] = typetest_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [6] = typetest_gsi_rd_txt;


 regression_hooks[GSI_INIT_DS_INDEX]    [7] = rpc_file_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [7] = rpc_file_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [7] = rpc_file_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [7] = rpc_file_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [7] = rpc_file_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [7] = rpc_file_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [7] = rpc_file_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][7] = rpc_file_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [7] = rpc_file_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [7] = rpc_file_gsi_rd_txt;


 regression_hooks[GSI_INIT_DS_INDEX]    [8] = rpc_types_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [8] = rpc_types_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [8] = rpc_types_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [8] = rpc_types_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [8] = rpc_types_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [8] = rpc_types_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [8] = rpc_types_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][8] = rpc_types_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [8] = rpc_types_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [8] = rpc_types_gsi_rd_txt;


 regression_hooks[GSI_INIT_DS_INDEX]    [9] = skeleton_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [9] = skeleton_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [9] = skeleton_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [9] = skeleton_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [9] = skeleton_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [9] = skeleton_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [9] = skeleton_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][9] = skeleton_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [9] = skeleton_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [9] = skeleton_gsi_rd_txt;

 regression_hooks[GSI_INIT_DS_INDEX]    [10] = floats_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [10] = floats_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [10] = floats_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [10] = floats_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [10] = floats_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [10] = floats_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [10] = floats_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][10] = floats_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [10] = floats_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [10] = floats_gsi_rd_txt;

 regression_hooks[GSI_INIT_DS_INDEX]    [11] = time_stamp_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [11] = time_stamp_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [11] = time_stamp_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [11] = time_stamp_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [11] = time_stamp_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [11] = time_stamp_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [11] = time_stamp_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][11] = time_stamp_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [11] = time_stamp_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [11] = time_stamp_gsi_rd_txt;

 regression_hooks[GSI_INIT_DS_INDEX]    [12] = retmsg_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [12] = retmsg_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [12] = retmsg_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [12] = retmsg_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [12] = retmsg_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [12] = retmsg_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [12] = retmsg_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][12] = retmsg_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [12] = retmsg_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [12] = retmsg_gsi_rd_txt;

 regression_hooks[GSI_INIT_DS_INDEX]    [13] = watchdog_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [13] = watchdog_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [13] = watchdog_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [13] = watchdog_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [13] = watchdog_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [13] = watchdog_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [13] = watchdog_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][13] = watchdog_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [13] = watchdog_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [13] = watchdog_gsi_rd_txt;

 regression_hooks[GSI_INIT_DS_INDEX]    [14] = singlept_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [14] = singlept_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [14] = singlept_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [14] = singlept_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [14] = singlept_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [14] = singlept_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [14] = singlept_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][14] = singlept_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [14] = singlept_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [14] = singlept_gsi_rd_txt;
*/
 regression_hooks[GSI_INIT_DS_INDEX]    [15] = bench_gsi_init_ds;
 regression_hooks[GSI_PAUSE_DS_INDEX]   [15] = bench_gsi_pause_ds;
 regression_hooks[GSI_RESUME_DS_INDEX]  [15] = bench_gsi_resume_ds;
 regression_hooks[GSI_SHUTDOWN_INDEX]   [15] = bench_gsi_shutdown;
 regression_hooks[GSI_DEF_OBJ_INDEX]    [15] = bench_gsi_def_obj;
 regression_hooks[GSI_GET_DATA_INDEX]   [15] = bench_gsi_get_data;
 regression_hooks[GSI_SET_DATA_INDEX]   [15] = bench_gsi_set_data;
 regression_hooks[GSI_ACCEPT_DATA_INDEX][15] = bench_gsi_accept_data;
 regression_hooks[GSI_STOP_DATA_INDEX]  [15] = bench_gsi_stop_data;
 regression_hooks[GSI_RD_TXT_INDEX]     [15] = bench_gsi_rd_txt;

 if (print_template_messages)
    printf("\nloaded regression hooks\n");
}


int regression_hooks_unloaded_p = TRUE;

init_gsi_regression(initstring)
 char     *initstring;
{
 int       parse_succeeded_p;

 parse_succeeded_p = parse_gsi_regression_info(initstring);

 if (regression_hooks_unloaded_p &&
     parse_succeeded_p)
    {
     clear_gsi_regression_hooks();

     fill_gsi_regression_hooks();

     regression_hooks_unloaded_p = FALSE;
    }
}



gsi_init_ds(initstring, initstring_length)
char             *initstring;
unsigned long     initstring_length;
{
 int     (*regression_hook)();

 init_gsi_regression(initstring);

 if (regression_index < 0) return;

 regression_hook = regression_hooks[GSI_INIT_DS_INDEX][regression_index];
 if (regression_hook)
    (*regression_hook)(initstring, initstring_length);
 return(GSI_SUCCESS);
}




gsi_pause_ds()
{
 int     (*regression_hook)();

 if (regression_index < 0) return;

 regression_hook = regression_hooks[GSI_PAUSE_DS_INDEX][regression_index];
 if (regression_hook)
    (*regression_hook)();
 return(GSI_SUCCESS);
}




gsi_resume_ds()
{
 int     (*regression_hook)();

 if (regression_index < 0) return;

 regression_hook = regression_hooks[GSI_RESUME_DS_INDEX][regression_index];
 if (regression_hook)
    (*regression_hook)();
 return(GSI_SUCCESS);
}




gsi_shutdown()
{
 int     (*regression_hook)();

 if (regression_index < 0) return;

 regression_hook = regression_hooks[GSI_SHUTDOWN_INDEX][regression_index];
 if (regression_hook)
    (*regression_hook)();
 printf("\nShutting down in gsi_shutdown");
 return(GSI_SUCCESS);
}




gsi_def_obj(new, old)
USER_ARG_TYPE     *new, *old;
{
 int     (*regression_hook)();

 if (regression_index < 0) return;

 regression_hook = regression_hooks[GSI_DEF_OBJ_INDEX][regression_index];
 if (regression_hook)
    (*regression_hook)(new, old);
 return(GSI_SUCCESS);
}




gsi_get_data(arglist, argcount)
TEMP_ARG_TYPE     *arglist;
short int          argcount;
{
 int     (*regression_hook)();

 if (regression_index < 0) return;

 regression_hook = regression_hooks[GSI_GET_DATA_INDEX][regression_index];
 if (regression_hook)
    (*regression_hook)(arglist, argcount);
 return(GSI_SUCCESS);
}




gsi_set_data(arglist, argcount)
TEMP_ARG_TYPE     *arglist;
short int          argcount;
{
 int     (*regression_hook)();

 if (regression_index < 0) return;

 regression_hook = regression_hooks[GSI_SET_DATA_INDEX][regression_index];
 if (regression_hook)
    (*regression_hook)(arglist, argcount);
 return(GSI_SUCCESS);
}




gsi_accept_data()
{
 int     (*regression_hook)();

 if (regression_index < 0) return;

 regression_hook = regression_hooks[GSI_ACCEPT_DATA_INDEX][regression_index];
 if (regression_hook)
    (*regression_hook)();
 return(GSI_SUCCESS);
}






gsi_stop_data(arglist, argcount)
TEMP_ARG_TYPE     *arglist;
short int          argcount;
{
 int     (*regression_hook)();

 if (regression_index < 0) return;

 regression_hook = regression_hooks[GSI_STOP_DATA_INDEX][regression_index];
 if (regression_hook)
    (*regression_hook)(arglist, argcount);
 return(GSI_SUCCESS);
}






gsi_rd_txt(textstring, textstring_length, object_index)
char         *textstring;
short int     textstring_length, object_index;
{
 int     (*regression_hook)();

 if (regression_index < 0) return;

 regression_hook = regression_hooks[GSI_RD_TXT_INDEX][regression_index];
 if (regression_hook)
    (*regression_hook)(textstring, textstring_length, object_index);
 return(GSI_SUCCESS);
}

/*
extern int rpc_fopen();
extern int rpc_fclose();
extern int rpc_fread();
extern int rpc_fwrite();
extern int rpc_return_int();
extern int rpc_return_float();
extern int rpc_return_float64();
extern int rpc_return_symbol();
extern int rpc_return_string();
*/

extern int gsibench_noop(); 
extern int gsibench_noop_return(); 
extern int gsibench_noop_arg();
extern int gsibench_noop_arg_return();
extern int gsibench_finished_with_rpc();
extern int gsibench_ready_for_noop(); 
extern int gsibench_ready_for_noop_return(); 
extern int gsibench_ready_for_noop_arg();
extern int r_noop_arg_return(); /* too long for VMS linker */
extern int gsibench_finished_with_rpc_thru();
extern int gsibench_ready_for_noop_thru(); 
extern int r_noop_return_thru();  /* too long for VMS linker */
extern int r_noop_arg_thru(); /* too long for VMS linker */
extern int r_noop_arg_return_thru(); /* too long for VMS linker */



InitUsrRpcs()
{
 int temp, status;
 int     (*regression_hook)();

/* must be edited for each new regression test that uses RPCs. */
/*
  status = LoadUsrRpc(rpc_fopen, "OPEN" , &temp);
  status = LoadUsrRpc(rpc_fclose, "CLOSE" , &temp);
  status = LoadUsrRpc(rpc_fread, "READ" , &temp);
  status = LoadUsrRpc(rpc_fwrite, "WRITE" , &temp);
  status = LoadUsrRpc(rpc_return_int, "RETURN-INT" , &temp);
  status = LoadUsrRpc(rpc_return_float, "RETURN-FLOAT" , &temp);
  status = LoadUsrRpc(rpc_return_float64, "RETURN-FLOAT64" , &temp);
  status = LoadUsrRpc(rpc_return_symbol, "RETURN-SYMBOL" , &temp);
  status = LoadUsrRpc(rpc_return_string, "RETURN-STRING" , &temp);
*/
  status = LoadUsrRpc(gsibench_noop, 
                      "GSIBENCH_NOOP", &temp);
  status = LoadUsrRpc(gsibench_noop_return, 
                      "GSIBENCH_NOOP_RETURN", &temp);
  status = LoadUsrRpc(gsibench_noop_arg,
 		      "GSIBENCH_NOOP_ARG", &temp);
  status = LoadUsrRpc(gsibench_noop_arg_return,
		      "GSIBENCH_NOOP_ARG_RETURN", &temp);

  status = LoadUsrRpc(gsibench_finished_with_rpc,
		      "GSIBENCH_FINISHED_WITH_RPC", &temp);

  status = LoadUsrRpc(gsibench_ready_for_noop, 
                      "READY_FOR_NOOP", &temp);
  status = LoadUsrRpc(gsibench_ready_for_noop_return, 
                      "READY_FOR_NOOP_RETURN", &temp);
  status = LoadUsrRpc(gsibench_ready_for_noop_arg,
 		      "READY_FOR_NOOP_ARG", &temp);
  status = LoadUsrRpc(r_noop_arg_return,
		      "READY_FOR_NOOP_ARG_RETURN", &temp);

  status = LoadUsrRpc(gsibench_finished_with_rpc_thru,
		      "FINISHED_WITH_RPC_THRU", &temp);

  status = LoadUsrRpc(gsibench_ready_for_noop_thru, 
                      "READY_FOR_NOOP_THRU", &temp);
  status = LoadUsrRpc(r_noop_return_thru, 
                      "READY_FOR_NOOP_RETURN_THRU", &temp);
  status = LoadUsrRpc(r_noop_arg_thru,
 		      "READY_FOR_NOOP_ARG_THRU", &temp);
  status = LoadUsrRpc(r_noop_arg_return_thru,
		      "R_NOOP_ARG_RETURN_THRU", &temp);
 return(GSI_SUCCESS);
}




getgsiport()
{
 return(GSI_REGRESSION_PORT);
} 



/* trace machinery */

/* 
 * Rudimentary for now, only appends to a file.
 * No provision for format strings or file versions.
 * Eventually cause it to loop back into G2 with
 * retvals, inform statements and suchlike.
 */

#define GSI_REGRESSION_FILE "GSIregress.log"

log_gsi_regression_message(message)
char     *message;
{
 FILE	  *stream;

 stream = fopen(GSI_REGRESSION_FILE, "a");

 if (stream)
  {
   fprintf(stream, "%s", message);
   fclose(stream);
  }
}
