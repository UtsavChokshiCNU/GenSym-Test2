/****************************************************************************
:
:  reposit.c  --  Sample GSI Bridge Code for use with gsi_exam.kb
:
:  Maintains a multi-user transaction-based object repository.
:
:  This file contains the standard GSI toolkit functions required for 
:  any GSI application and several other functions coded to support 
:  part of the sample knowledge base `gsi_exam.kb' provided with G2.
:  This file requires the standard GSI libraries and the sample main
:  module 'gsi_main.c' to create the executable `matrix'.
:
:  This file conforms to GSI 4.0.
:
:  Created 15mar95 by paf!
:...........................................................................*/

#include <stdio.h>
#include "gsi_main.h"
#include "gsi_misc.h"

#define TCPIP_PORT_NUMBER   22040

#define MAX_RPC_ARG_COUNT_USED  3
#define MAX_USER_COUNT         10
#define REPOSITORY_SIZE       100
#define NO_WATCH                0
#define INVALID_REPOSITORY_TAG -1

#define ACTIVE                  1
#define INACTIVE                0

typedef struct {
  long      occupied;
  long      locked;
  gsi_int   tag;
  gsi_int   user[MAX_USER_COUNT];
  gsi_item  item;
} repository_cell;

static repository_cell repository[REPOSITORY_SIZE];
static gsi_int         context_status[MAX_USER_COUNT];
static gsi_item       *rpc_arg_array;
static gsi_item       *void_item_ptr;
static gsi_item       *repository_items;
static gsi_item        snapshot_return_args[2];
static gsi_item        void_item;
static function_handle_type r_update_client_copy;

extern declare_gsi_rpc_local_fn(tag_query);
extern declare_gsi_rpc_local_fn(add_object);
extern declare_gsi_rpc_local_fn(remove_object);
extern declare_gsi_rpc_local_fn(snapshot);
extern declare_gsi_rpc_local_fn(lock_object);
extern declare_gsi_rpc_local_fn(unlock_object);
extern declare_gsi_rpc_local_fn(watch_object);
extern declare_gsi_rpc_local_fn(unwatch_object);
extern declare_gsi_rpc_local_fn(modify_object);

/*****************************************************************************
:  FUNCTION: modify_object_attr
:
:  Given a pair of GSI items containing simple values, make the first be like 
:  the second.
:
:  Arguments (2):
:    destination item
:    source item
:
:............................................................................*/
void modify_object_attr(destination, source)
  gsi_item destination;
  gsi_item source;

{
  switch (type_of(source)) {
  case INTEGER_TAG:
    set_int(destination,int_of(source)); break;
  case LOGICAL_TAG:
    set_log(destination,log_of(source)); break;
  case FLOAT64_TAG:
    set_flt(destination,flt_of(source)); break;
  case SYMBOL_TAG:
    set_sym(destination,sym_of(source)); break;
  case STRING_TAG:
    set_str(destination,str_of(source)); break;
  default:
    break;
  } /* end switch */

} /* end modify_object_attr */


/*****************************************************************************
:  FUNCTION: broadcast_update
:
:  Broadcast a change to an attribute of a repository object identified by tag
:  to every client (max one per context).
:
:  Arguments (3):
:    tag
:    attribute name
:    change
:
:............................................................................*/
void broadcast_update(tag, attr_name, change)
  gsi_int  tag;
  char    *attr_name;
  gsi_item change;
{
  long     context;
  gsi_int  handle;

  set_sym(rpc_arg_array[1],attr_name);
  rpc_arg_array[2] = change;            /* This is a first-time-only leak. */

  for (context=0; context<MAX_USER_COUNT; context++) {
    if (context_status[context] == ACTIVE) {
      handle = repository[tag].user[context];
      if (handle > NO_WATCH) {
	set_handle(rpc_arg_array[0],handle);
	gsi_rpc_start(r_update_client_copy,rpc_arg_array,context); }
    } /* end if ACTIVE */
  } /* end for */

} /* end broadcast_update */


/*****************************************************************************
:  RPC FUNCTION: tag_query
:
:  This function, which is declared as RPC-invocable from a G2 process,
:  returns the tag for an object in the repository given a class and name.
:
:  RPC Arguments (2):
:    [0]  query class name    
:    [1]  query object name
:  RPC Returns (1):
:    [0]  repository tag
:
:  Note, this function does not support being invoked via a 'start', and must
:  be invoked with a 'call' action.
:............................................................................*/
void tag_query(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  call_identifier_type   call_index;
{
  long      i;
  gsi_item  item;
  char     *query_class_name = sym_of(arg_array[0]);
  char     *query_object_name = sym_of(arg_array[1]);

  set_int(arg_array[0],INVALID_REPOSITORY_TAG);
  for (i=0; i<REPOSITORY_SIZE; i++) {
    if (repository[i].occupied) {
      item = repository[i].item;
      if (strcmp(class_name_of(item),query_class_name) == 0)
	if (strcmp(name_of(item),query_object_name) == 0) {
	  set_int(arg_array[0],i);
	  break; }
    } /* end if occupied */
  } /* end for */
    
  gsi_rpc_return_values(arg_array,1,call_index,current_context);

} /* end tag_query */


/*****************************************************************************
:  RPC FUNCTION: add_object
:
:  This function, which is declared as RPC-invocable from a G2 process, adds
:  an object to the repository.  The repository tag chosen for the new object
:  is returned.
:
:  RPC Arguments (1):
:    [0]  new object
:  RPC Returns (1):
:    [0]  repository tag
:
:  Note, a generic template is used from within the KB, and 'generic-' must 
:  be stripped from the class name when committing it to the repository.
:
:  Note, this function does not support being invoked via a 'start', and must
:  be invoked with a 'call' action.
:............................................................................*/
void add_object(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  call_identifier_type   call_index;
{
  long      i,u;
  char     *class_name;

  for (i=0; i<REPOSITORY_SIZE; i++) {
    if (repository[i].occupied)
      continue;
    else {
      gsirtl_copy_item(type_of(arg_array[0]),arg_array[0],repository[i].item);
      class_name = class_name_of(arg_array[0]);
      class_name += strlen("generic-");
      set_class_name(repository[i].item,class_name);
      repository[i].tag = i;
      repository[i].occupied = TRUE;
      repository[i].locked = FALSE;
      for (u=0; u<MAX_USER_COUNT; u++)
	repository[i].user[u] = NO_WATCH;
      break; }
  } /* end for */

  set_class_name(arg_array[0],NULL_PTR);
  if (i == REPOSITORY_SIZE)
    set_int(arg_array[0],INVALID_REPOSITORY_TAG);
  else
    set_int(arg_array[0],i);

  gsi_rpc_return_values(arg_array,1,call_index,current_context);

} /* end add_object */


/*****************************************************************************
:  RPC FUNCTION: remove_object
:
:  This function, which is declared as RPC-invocable from a G2 process, 
:  removes an object from the repository given its tag number.
:
:  Objects with active clients (watchers) may not be removed.
:
:  RPC Arguments (1):
:    [0]  repository tag
:  RPC Return Arguments (1):
:    [0]  status symbol
:
:  Note, this function does not support being invoked via a 'start', and must
:  be invoked with a 'call' action.
:............................................................................*/
void remove_object(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  call_identifier_type   call_index;
{
  long      u;
  long      active_clients = FALSE;
  gsi_int   tag = int_of(arg_array[0]);

/*
 *  If the repository slot identified by tag is occupied, iterate
 *  over its user array to see if anyone is watching this object.
 */
  set_sym(arg_array[0],"SUCCESS");
  if (repository[tag].occupied) {
    for (u=0; u<MAX_USER_COUNT; u++)
      if (repository[tag].user[u]) {
	active_clients = TRUE;
	break; }
    if (active_clients)
      set_sym(arg_array[0],"FAILURE");
    else {
      gsirtl_free_item_memory(repository[tag].item);
      gsi_reclaim_items(&repository[tag].item);
      repository[tag].occupied = FALSE; }
  } /* end if */

  gsi_rpc_return_values(arg_array,1,call_index,current_context);

} /* end remove_object */


/*****************************************************************************
:  RPC FUNCTION: snapshot
:
:  This function, which is declared as RPC-invocable from a G2 process, gets
:  a snapshot (copy) of a repository object identified by a tag argument, and
:  returns the copy and a status.
:
:  RPC Arguments (1):
:    [0]  repository tag
:  RPC Return Arguments (2):
:    [0]  object copy
:    [1]  status symbol
:
:  Note, snapshot_return_args is an array of 'empty' gsi_items (null pointers)
:  initially and its elements are made to point to gsi_items 'owned' by other
:  arrays.
:
:  Note, this function does not support being invoked via a 'start', and must
:  be invoked with a 'call' action.
:............................................................................*/
void snapshot(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  call_identifier_type   call_index;
{
  gsi_int  tag = int_of(arg_array[0]);

  snapshot_return_args[1] = rpc_arg_array[0];
  if (repository[tag].occupied) {
    snapshot_return_args[0] = repository[tag].item;
    set_sym(snapshot_return_args[1],"SUCCESS"); }
  else {
    snapshot_return_args[0] = void_item;
    set_sym(snapshot_return_args[1],"FAILURE"); }

  gsi_rpc_return_values(snapshot_return_args,2,call_index,current_context);

} /* end snapshot */



/*****************************************************************************
:  RPC FUNCTION: lock_object
:
:  This function, which is declared as RPC-invocable from a G2 process, locks
:  an object preventing other clients from modifying it.
:
:  RPC Arguments (1):
:    [0]  repository tag
:  RPC Return Arguments (1):
:    [0]  status symbol
:
:  Note, this function does not support being invoked via a 'start', and must
:  be invoked with a 'call' action.
:
:  Note, implementation of a re-try mechanism with a real timeout was omitted
:  as it does not directly relate to GSI.
:............................................................................*/
void lock_object(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  call_identifier_type   call_index;
{
  gsi_int  tag = int_of(arg_array[0]);

  if (repository[tag].occupied)
    if (repository[tag].locked)
      set_sym(arg_array[0],"TIMEOUT"); /* really a simple failure (see notes) */
    else {
      repository[tag].locked = TRUE;
      set_sym(arg_array[0],"SUCCESS"); }
  else
    set_sym(arg_array[0],"UNOCCUPIED");

  gsi_rpc_return_values(arg_array,1,call_index,current_context);

} /* end lock_object */


/*****************************************************************************
:  RPC FUNCTION: unlock_object
:
:  This function, which is declared as RPC-invocable from a G2 process, unlocks
:  an object allowing other clients to modify it.
:
:  RPC Arguments (1):
:    [0]  repository tag
:
:  Note, this function does not support being invoked via a 'call', and must
:  be invoked with a 'start' action.
:............................................................................*/
void unlock_object(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  call_identifier_type   call_index;
{
  gsi_int  tag = int_of(arg_array[0]);

  repository[tag].locked = FALSE;

} /* end unlock_object */


/*****************************************************************************
:  RPC FUNCTION: watch_object
:
:  This function, which is declared as RPC-invocable from a G2 process, sets
:  the user array slot (identified by the current context) of an existing 
:  repository object (identified by the tag argument), to the handle which
:  uniquely identifies the object copy within the G2 connected at this
:  context.
:
:  RPC Arguments (2):
:    [0]  tag
:    [1]  handle
:  RPC Return Arguments (1):
:    [0]  status symbol
:
:  Note, this function does not support being invoked via a 'start', and must
:  be invoked with a 'call' action.
:............................................................................*/
void watch_object(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  call_identifier_type   call_index;
{
  gsi_int  tag = int_of(arg_array[0]);
  gsi_int  handle = handle_of(arg_array[1]);

  if (repository[tag].occupied) {
    repository[tag].user[current_context] = handle;
    set_sym(arg_array[0],"SUCCESS"); }
  else
    set_sym(arg_array[0],"FAILURE");

  gsi_rpc_return_values(arg_array,1,call_index,current_context);

} /* end watch_object */


/*****************************************************************************
:  RPC FUNCTION: unwatch_object
:
:  This function, which is declared as RPC-invocable from a G2 process, zeros
:  the user array slot (identified by the current context) of an existing 
:  repository object (identified by the tag argument) such that changes to
:  the object will no longer be broadcast to the G2 connected at this context.
:
:  RPC Arguments (1):
:    [0]  tag
:
:  Note, this function does not support being invoked via a 'call', and must
:  be invoked with a 'start' action.
:............................................................................*/
void unwatch_object(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  call_identifier_type   call_index;
{
  gsi_int  tag = int_of(arg_array[0]);

  if (repository[tag].occupied)
    repository[tag].user[current_context] = NO_WATCH;

} /* end unwatch_object */


/*****************************************************************************
:  RPC FUNCTION: modify_object
:
:  This function, which is declared as RPC-invocable from a G2 process, 
:  modifies an attribute of a repository object and triggers the broadcast of
:  the modification to all clients (watchers) of the object.
:
:  RPC Arguments (3):
:    [0]  tag
:    [1]  attribute name
:    [2]  new value
:  RPC Return Arguments (1):
:    [0]  status symbol
:
:  Note, this function does not support being invoked via a 'start', and must
:  be invoked with a 'call' action.
:............................................................................*/
void modify_object(arg_array, count, call_index)
  gsi_item *arg_array;
  gsi_int   count;
  call_identifier_type   call_index;
{
  gsi_int   tag = int_of(arg_array[0]);
  char     *attr_name = sym_of(arg_array[1]);
  gsi_item  existing_attr_item;

  if (repository[tag].occupied)
    if (repository[tag].locked) {
      existing_attr_item = attr_by_name(repository[tag].item,attr_name);
      if (gsi_last_error() == GSI_ATTRIBUTE_NAME_NOT_FOUND)
	set_sym(arg_array[0],"ATTRIBUTE_NOT_FOUND");
      else {
	modify_object_attr(existing_attr_item,arg_array[2]);
	broadcast_update(tag,attr_name,existing_attr_item);
	set_sym(arg_array[0],"SUCCESS"); }
    } /* end if locked */
    else
      set_sym(arg_array[0],"BRIDGE_CODE_INCONSISTENCY");
  else
    set_sym(arg_array[0],"OBJECT_NOT_FOUND");

  gsi_rpc_return_values(arg_array,1,call_index,current_context);

} /* end modify_object */


/********************************************************************************
*
*  The remaining functions are the standard GSI Toolkit functions required of all
*  GSI applications.  Those which are used preceed those which are stubbed out.
*
********************************************************************************/

void gsi_set_up ()
{
  gsi_int  context;
  gsi_int  i;

/*
 *  Declare local function to be remotely invocable.
 */
  gsi_rpc_declare_local(tag_query,"R-TAG-QUERY");
  gsi_rpc_declare_local(add_object,"R-ADD-OBJECT");
  gsi_rpc_declare_local(remove_object,"R-REMOVE-OBJECT");
  gsi_rpc_declare_local(snapshot,"R-SNAPSHOT");
  gsi_rpc_declare_local(lock_object,"R-LOCK-OBJECT");
  gsi_rpc_declare_local(unlock_object,"R-UNLOCK-OBJECT");
  gsi_rpc_declare_local(watch_object,"R-WATCH-OBJECT");
  gsi_rpc_declare_local(unwatch_object,"R-UNWATCH-OBJECT");
  gsi_rpc_declare_local(modify_object,"R-MODIFY-OBJECT");

/*
 * Initialize global structures and allocate memory for them.
 */
  for (context=0; context<MAX_USER_COUNT; context++)
    context_status[context] = INACTIVE;

  rpc_arg_array = gsi_make_items(MAX_RPC_ARG_COUNT_USED);

  void_item_ptr = gsi_make_items(1);
  void_item = *void_item_ptr;
  set_class_name(void_item,"OBJECT");
  set_type(void_item,GSI_NULL_TAG); /* ..but with no attributes and no value. */

  repository_items = gsi_make_items(REPOSITORY_SIZE);
  for (i=0; i<REPOSITORY_SIZE; i++)
    repository[i].item = repository_items[i];

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

gsi_int gsi_initialize_context (remote_process_init_string, length)
  char   *remote_process_init_string;
  gsi_int length;
{
  context_status[current_context] = ACTIVE;
  gsi_rpc_declare_remote(&r_update_client_copy,
			 "R-UPDATE-CLIENT-COPY",
			 NULL_PTR,
			 3,
			 0,
			 current_context);

  return (GSI_ACCEPT);
}

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

void gsi_shutdown_context()
{
  context_status[current_context] = INACTIVE;
}

void gsi_receive_deregistrations (registered_items, count)
  gsi_registered_item *registered_items;
  gsi_int              count;
{}

void gsi_g2_poll()
{}

void gsi_receive_message (message,length)
  char     *message;
  gsi_int   length;
{}
