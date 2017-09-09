/****************************************************************************
:
:  alarmer.c  --  Sample GSI Bridge Code for use with gsi_exam.kb
:
:  When enabled, sends a sample alarm (as if from some external system)
:  every so often to G2 for processing.
:
:  This file contains the standard GSI toolkit functions required for 
:  any GSI application and several other functions coded to support 
:  part of the sample knowledge base `gsi_exam.kb' provided with G2.
:  This file requires the standard GSI libraries and the sample main
:  module 'gsi_main.c' to create the executable `alarmer'.
:
:  This file conforms to GSI 4.0.
:
:  Created 10mar95 by paf!
:...........................................................................*/

#include <stdio.h>
#include "gsi_main.h"

#define TCPIP_PORT_NUMBER   22040

#define G2_ALARM_ATTR_COUNT 3

#define MESSAGE_SYMBOL      "MESSAGE"
#define PRIORITY_SYMBOL     "PRIORITY"
#define DATA_POINT_SYMBOL   "DATA-POINT"

#define FAILURE  1
#define WARNING  2
#define INFORM   3

#define FAILURE_SYMBOL "FAILURE"
#define WARNING_SYMBOL "WARNING"
#define INFORM_SYMBOL  "INFORM"

typedef struct {
  long   data_point_tag;
  long   priority;
  char  *message;
} p3_alarm;

static function_handle_type   display_new_alarm;
static int       alarming_enabled = FALSE;
static p3_alarm  sample_alarm = { 99,
				  WARNING,
				  "The flywheel's gone askew on the treadmill" };
static gsi_item *g2_alarm_ptr;
static gsi_item  g2_alarm;

extern declare_gsi_rpc_local_fn(enable_alarming);
extern declare_gsi_rpc_local_fn(disable_alarming);

/*****************************************************************************
:  RPC FUNCTION: enable_alarming
:
:  This function, which is declared as RPC-invocable from a G2 process, sets a
:  flag that enables the transmission of alarm objects to G2.
:
:  RPC Arguments (0)
:
:  Note, this function does not support being invoked via a 'call', and must
:  be invoked with a 'start' action.
:............................................................................*/
void enable_alarming(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  gsi_int   call_index;
{
  alarming_enabled = TRUE;

} /* end enable_alarming */


/*****************************************************************************
:  RPC FUNCTION: disable_alarming
:
:  This function, which is declared as RPC-invocable from a G2 process, sets a
:  flag that disables the transmission of alarm objects to G2.
:
:  RPC Arguments (0)
:
:  Note, this function does not support being invoked via a 'call', and must
:  be invoked with a 'start' action.
:............................................................................*/
void disable_alarming(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  gsi_int   call_index;
{
  alarming_enabled = FALSE;

} /* end disable_alarming */


/*****************************************************************************
:  FUNCTION: send_alarm_to_g2
:
:  This function sends an alarm to G2, based on an alarm structure defined by
:  some hypothetical third party system.  Most of the work is in copying the 
:  contents of the alarm into a GSI structure for transmission to G2.
:
:  Arguments (1):
:    alarm_ptr    A pointer to an alarm.
:
:  Note, this could be made more efficient by using additional globals to 
:  maintain references to the attribute structures instead of using the API
:  function attr_by_name for each every time this function is called.
:............................................................................*/
void send_alarm_to_g2(alarm_ptr)
  p3_alarm *alarm_ptr;
{
/*
 *  Copy the data from the p3_alarm into the g2_alarm.
 */
  set_int(attr_by_name(g2_alarm,DATA_POINT_SYMBOL),alarm_ptr->data_point_tag);
  switch(alarm_ptr->priority) {
    case FAILURE:
      set_sym(attr_by_name(g2_alarm,PRIORITY_SYMBOL),FAILURE_SYMBOL); break;
    case WARNING:
      set_sym(attr_by_name(g2_alarm,PRIORITY_SYMBOL),WARNING_SYMBOL); break;
    case INFORM:
      set_sym(attr_by_name(g2_alarm,PRIORITY_SYMBOL),FAILURE_SYMBOL); break; }
  set_str(attr_by_name(g2_alarm,MESSAGE_SYMBOL),alarm_ptr->message);

/*
 *  Send the alarm to G2 via RPC.
 */
  gsi_rpc_start(display_new_alarm,g2_alarm_ptr,current_context);
}


/********************************************************************************
*
*  The remaining functions are the standard GSI Toolkit functions required of all
*  GSI applications.  Those which are used preceed those which are stubbed out.
*
********************************************************************************/

void gsi_set_up ()
{
  gsi_attr *attrs;

/*
 *  Construct the alarm item to be used each time an alarm is
 *  send to G2.  No initial values are given for the attributes.
 */
  g2_alarm_ptr = gsi_make_items(1);
  g2_alarm = *g2_alarm_ptr;
  set_class_name(g2_alarm,"ALARM");
  attrs = gsi_make_attrs_with_items(G2_ALARM_ATTR_COUNT);
  set_attr_name(attrs[0],DATA_POINT_SYMBOL);
  set_attr_name(attrs[1],PRIORITY_SYMBOL);
  set_attr_name(attrs[2],MESSAGE_SYMBOL);
  set_attrs(g2_alarm,attrs,G2_ALARM_ATTR_COUNT);

/*
 *  Declare local functions to be remotely invocable.
 */
  gsi_rpc_declare_local(enable_alarming,"ENABLE-ALARMING");
  gsi_rpc_declare_local(disable_alarming,"DISABLE-ALARMING");
}

gsi_int gsi_get_tcp_port()
{
  return(TCPIP_PORT_NUMBER);
}

gsi_int gsi_initialize_context (remote_process_init_string, length)
  char   *remote_process_init_string;
  gsi_int length;
{
/*
 *  Declare G2 procedure to be invocable from GSI.
 */
  gsi_rpc_declare_remote(&display_new_alarm,"DISPLAY-NEW-ALARM",NULL_PTR,1,0,current_context);

  return (GSI_ACCEPT);
}

void gsi_g2_poll()
{
  if (alarming_enabled)
    send_alarm_to_g2(&sample_alarm);
}

void gsi_shutdown_context()
{
  alarming_enabled = FALSE;
}




/************************************************
*
*  The remaining functions are all empty stubs.
*
*************************************************/

void gsi_receive_registration (item_registration)
  gsi_registration item_registration;
{}

void gsi_get_data (registered_items, count)
  gsi_registered_item *registered_items;
  gsi_int              count;
{}

void gsi_set_data (registered_items, count)
  gsi_registered_item *registered_items;
  gsi_int              count;
{}

void gsi_pause_context()
{}

void gsi_resume_context()
{}

void gsi_receive_deregistrations (registered_items, count)
  gsi_registered_item *registered_items;
  gsi_int              count;
{}

void gsi_receive_message (message,length)
  char    *message;
  gsi_int  length;
{}
