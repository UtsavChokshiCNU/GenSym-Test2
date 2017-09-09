/* *************************************************************
   
   File : gsi-icp-functions.c
	  icp.c
	  gsi.c
	  kfep_server.c  
	  asynch.c
	  foreign.c
  
 This code implements a foreign function server (FFS).  Using a server is intended
 to supplant the old method of calling foreign functions within the G2 image
 itself, which carried a risk of memory corruption from user-written foreign code.

 As a first pass, we will use the ICP internals of GSI to communicate with the
 foreign function server.  Eventually, we will need a faster approach, one using
 shared memory.  The shared memory approach will of course use the same ICP
 abstraction.
   
 Legal Notice:           Copyright (C) 1986-2017 Gensym Corporation.,
                         125 CambridgePark Drive, Cambridge MA 02140
                         All rights reserved.

jh, 5/28/91.  Adapted this file from ma:>jh>c>asynch.c
*******************************************************************/


/*  The following are include files required by this file.  The constant
    EXTERN_DEFINED is set to TRUE to prevent stuff from being defined twice.

*******************************************************************************/

#define   EXTERNS_DEFINED TRUE     /* To turn off part of icp.h include.      */
#include "gensym-features.h"       /* Machine dependent defines and includes. */
#include "foreign.h"             /* Defines and typedefs required by foreign 
                                      function application programs.          */
#define   DEFINE_GLOBALS TRUE      /* To turn on definitions of globals.      */
#include "icp_pvt.h"             /* Defines, typedefs and globals required by
                                      all ICP extensions.                     */
#include "ffe_pvt.h"             /* Defines, typedefs and globals required by
                                      the foreign function extension only.    */
#ifndef WIN32
#  include <stdlib.h>
#endif
#include <math.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h> /* added for FFS */

#include "cprim.h"

#ifdef FILE_NAME
static char file_name[80] = {"foreign.c v1.0"};
#endif

extern void ext_error(icp_int  error, char *circumstance, icp_int data, icp_int send);
extern void wr_icp_str(char *string);
extern void wr_icp_int(icp_int value);

extern icp_int rd_icp_int(void);
extern icp_int rd_icp_str(obj_value_type *value_ptr);
extern icp_int read_object_value(obj_value_type *value_ptr);
extern icp_int write_object_value(obj_value_type *value_ptr);
extern icp_int icp_flush(void);
extern icp_int extension_start(int argc, char *argv[]);
extern void ext_message(char *message, icp_int send);

/*
 * The following code is specific to the foreign function server (FFS).  FFS is a
 * minimal extension process which simply listens for commands relating to foreign
 * functions.
 */

/*
 * set up signal handling
 * do forever:
 *   listen on ICP socket a la GSI
 *   read an ICP byte into message
 *   if message is out of bounds, exit
 *   otherwise, dispatch on message:
 *
 *    REQUEST_CONNECTION:
 *      if connection is already open
 *         send SIGNAL_ERROR message and CONNECTION_OPEN_ALREADY code
 *      else
 *         reply with ACCEPT_CONNECTION message and version info
 * 
 *     REQUEST_FOREIGN_REGISTRY:
 *       reply with PROVIDE_FOREIGN_REGISTRY message
 *         and list of foreign function names
 *
 *     CALL_FOREIGN_FUNCTION:
 *       if cannot locate foreign function
 *          send SIGNAL_ERROR message and UNKNOWN_FUNCTION code
 *       else 
 *         begin
 *           call foreign code with TEMP_PARAM array
 *           if a signal was caught 
 *              send SIGNAL_ERROR message and SIGNAL_CAUGHT_DURING_CALL code
 *           else if the return value has an unknown type tag
 *              send SIGNAL_ERROR and UNKNOWN_RETURN_VALUE code
 *           else
 *              reply with RETURN_FOREIGN_VALUE sending TEMP_PARAM value
 *         end
 *
 *     otherwise:
 *       exit because an unknown message was received
 */




/*
 * The GSI shell calls this function to get the port number for the ICP socket
 * across which communication will occur, when the transport layer is TCP/IP.
 */

ffe_int gsi_get_tcp_port()
{
    return(ffs_socket_number);
}


/************************** 
 * sender for IMAGE_READY *
 **************************/

int send_icp_ffs_image_ready()
{
 if (FFS_DEBUG)
    printf("About to send IMAGE_READY (%d).\n",
           FFS_IMAGE_READY_MESSAGE);

 /* Reply with "image ready" message. */
 wricpbyte(ICP_MSG_OFFSET + FFS_IMAGE_READY_MESSAGE);
 wr_icp_int(ICP_MAJ_VER_NUM);
 wr_icp_int(ICP_MIN_VER_NUM);

 /* G2 will ignore these spare arguments for now. */
 wr_icp_int(0);
 wr_icp_str("");

 ffs_connection_open_p = TRUE;

 send_ffs_message(); /* a macro - beware! */

 if (FFS_DEBUG)
    printf("Sent IMAGE_READY.\n");
 return 0;
}

/****************************************
 * sender for  PROVIDE_FOREIGN_REGISTRY *
 ****************************************/

/* 
 * The user inserts one or more calls to register_foreign_function in main().
 * This happens when foreign image is initialized, before it starts waiting on the
 * ICP socket.
 */

int register_foreign_function(g2_name, function_address, argcount, typetags, return_type)
char              *g2_name;
obj_value_type    *(*function_address)();
ffe_int             argcount;
ffe_int            *typetags;
ffe_int             return_type;
{
 ffe_int         i;
 obj_value_type *arglist;
 ffe_int        *typelist;
 obj_value_type  preallocated_arg;

 FOREIGN_FUNCTION_ENTRY     *foreign_entry;

 if ((foreign_entry =  (FOREIGN_FUNCTION_ENTRY *) 
                  malloc(sizeof(FOREIGN_FUNCTION_ENTRY))) == NULL) {
   printf ("\nforeign.c -- Out of memory in register_foreign_function 1st.\n");
 }
 if ((foreign_entry->name = (char *) malloc (strlen(g2_name)+1)) == NULL) {
   printf ("\nforeign.c -- Out of memory in register_foreign_function 2nd.\n");
 }
 strcpy(foreign_entry->name, g2_name);

 if (latest_foreign_entry == NULL)
    foreign_entry->index = 1;
 else
    foreign_entry->index = 1 + latest_foreign_entry->index;

 foreign_entry->function_address = function_address;

 foreign_entry->argcount = argcount;

 typelist = (ffe_int *) calloc(argcount, sizeof(ffe_int));
 if (argcount > 0 && typelist == NULL) 
  {
   printf ("\nforeign.c -- Out of memory in register_foreign_function 3rd.\n");
  }
 for (i = 0; i < argcount; i++)
  {
   typelist[i] = typetags[i];
  }
 foreign_entry->typelist = typelist;

 /* cache TEMP_PARAM structs to use as arguments to the overlay functions */
 arglist = (TEMP_PARAM *) calloc(argcount, sizeof preallocated_arg);
 if (argcount > 0 && arglist == NULL) 
  {
   printf ("\nforeign.c -- Out of memory in register_foreign_function 4th.\n");
  }
 foreign_entry->arglist = arglist;

 foreign_entry->return_type = return_type;

 foreign_entry->next_entry = latest_foreign_entry;
 latest_foreign_entry = foreign_entry;
 return 0;
}

/*  
 * jh, 2/22/92.  The following resumption machinery is no longer used,
 * since all signals are fatal.  Keep it around in case we add
 * continuable signals.  Note that errors (improper arg count and the
 * like) will not cause an exit, since the foreign image sustains no
 * damage in this case -- we simply refrain from returning a value and
 * let G2 time out.
 */
jmp_buf     ffs_toplevel_catcher;
ffe_int     ffs_toplevel_catcher_established_p = FALSE;

ffe_int     error_within_error_p = FALSE;

int wait_for_foreign_calls(argc, argv)
int     argc;
char   *argv[];
{
 FOREIGN_FUNCTION_ENTRY    *entry;

#ifdef unix
 if (argc > 1)
    ffs_socket_number = atoi(argv[1]);
#endif

 /* sanity check */
 if (latest_foreign_entry == NULL)
    printf("FFS: No foreign functions are present in this image.\n");

 /* 
  * create an array for foreign function entries for O(1) access.  up to this
  * point they are in a linked list, which is O(n).
  */
 if ((foreign_function_registry = 
   (FOREIGN_FUNCTION_ENTRY *)
   calloc (latest_foreign_entry->index, 
           sizeof(FOREIGN_FUNCTION_ENTRY))) == NULL) {
   printf ("\nforeign.c -- Out of memory in wait_for_foreign_calls.\n");
 }

 entry = latest_foreign_entry;
 while (entry != NULL)
  {
   ffe_int     index;

   index = entry->index - 1;

   /* 
    * Note that foreign_function_registry is an array of FOREIGN_FUNCTION_ENTRY
    * structs, not an array of pointers to same.  Thus we have to copy the
    * contents here.  This only happens once in the life of a foreign function
    * server, and thus is no drain on efficiency.  jh, 7/30/91.
    */
   foreign_function_registry[index].name = entry->name;
   foreign_function_registry[index].index = entry->index;
   foreign_function_registry[index].function_address = entry->function_address;
   foreign_function_registry[index].argcount = entry->argcount;
   foreign_function_registry[index].arglist = entry->arglist;
   foreign_function_registry[index].typelist = entry->typelist;
   foreign_function_registry[index].return_type = entry->return_type;

   entry = entry->next_entry;
  }

/*
 * jh, 2/22/92.  No longer used, but may be again someday.  See the
 * declaration of ffs_toplevel_catcher for rationale.
 */
/*
 setjmp(ffs_toplevel_catcher);
 ffs_toplevel_catcher_established_p = TRUE;
*/

 if (FFS_DEBUG)
  {
   printf("Foreign function server ready");
#ifdef unix
   printf(" at port %d", (int) gsi_get_tcp_port());
#endif
   printf(".\n");
  }

 if (FFS_DEBUG_VERBOSE)
  {
   int     i;

   for (i = 0; i < latest_foreign_entry->index; i++)
       printf_foreign_entry(&foreign_function_registry[i]);
  }

 /* Customize some GSI settings. */
#if FFS_DEBUG
ResetIcpMode(ICP_SUPPRESS_OUTPUT);
#else
SetIcpMode(ICP_SUPPRESS_OUTPUT);
#endif

 error_within_error_p = FALSE;

 /* Enter the main extension loop.  */
 extension_start(argc, argv);
 return 0;
}

ffe_int foreign_registry_provided_p = FALSE;

/* Forward refs */
void decline_foreign_reg_req();
void comply_with_foreign_reg_req();
void send_icp_signal_ffs_error();

int send_icp_prov_foreign_registry()
{
 if (foreign_registry_provided_p)
   decline_foreign_reg_req();
 else
   comply_with_foreign_reg_req();
 return 0;
}

void decline_foreign_reg_req()
{
 if (FFS_DEBUG)
    printf("About to send PROVIDE_FOREIGN_REGISTRY (%d), declining.\n",
           FFS_PROVIDE_FOREIGN_REGISTRY_MESSAGE);

 /* Reply with "provide foreign registry" message. */
 wricpbyte(ICP_MSG_OFFSET + FFS_PROVIDE_FOREIGN_REGISTRY_MESSAGE);

 /* 0 foreign functions available */
 wr_icp_int(0);

 /* spare args */
 wr_icp_int(0);
 wr_icp_str("");

 send_ffs_message(); /* a macro - beware! */

 if (FFS_DEBUG)
    printf("Sent PROVIDE_FOREIGN_REGISTRY, declined.\n");
}

void comply_with_foreign_reg_req()
{
 FOREIGN_FUNCTION_ENTRY    *entry;

 if (FFS_DEBUG)
    printf("About to send PROVIDE_FOREIGN_REGISTRY (%d).\n",
           FFS_PROVIDE_FOREIGN_REGISTRY_MESSAGE);

 /* Reply with "provide foreign registry" message. */
 wricpbyte(ICP_MSG_OFFSET + FFS_PROVIDE_FOREIGN_REGISTRY_MESSAGE);

 /* Send the number of foreign functions in the registry. */
 if (latest_foreign_entry != NULL)
    wr_icp_int(latest_foreign_entry->index);
 else
     wr_icp_int(0);

 /* 
  * Alternate name of each foreign function and its index.  Note that this loop
  * does not use foreign_function_registry.
  */
 entry = latest_foreign_entry;
 while (entry != NULL)
  {
   ffe_int     i;

   wr_icp_str(entry->name);                 /* name        */
   wr_icp_int(entry->index);                /* entry code  */
   wr_icp_int(entry->argcount);             /* argcount    */

   for (i = 0; i < entry->argcount; i++)    /* typelist    */
    {
     wr_icp_int((entry->typelist)[i]);
    }
   wr_icp_int(entry->return_type);          /* return type */

   entry = entry->next_entry; 
  }

 /* G2 will ignore these spare arguments for now. */
 wr_icp_int(0);
 wr_icp_str("");

 send_ffs_message(); /* a macro - beware! */

 foreign_registry_provided_p = TRUE;

 if (FFS_DEBUG)
    printf("Sent PROVIDE_FOREIGN_REGISTRY.\n");
}


/***********************************
 * sender for RETURN_FOREIGN_VALUE * 
 ***********************************/

int send_icp_return_foreign_value(foreign_value)
obj_value_type    *foreign_value;
{
 if (FFS_DEBUG)
    printf("About to send RETURN_FOREIGN_VALUE (%d).\n",
           FFS_RETURN_FOREIGN_VALUE_MESSAGE);

 /* Reply with "return foreign value" message. */
 wricpbyte(ICP_MSG_OFFSET + FFS_RETURN_FOREIGN_VALUE_MESSAGE);

 /* 
  * handler has already checked p_value to be sure it is correct -- we might want
  * to give the user the chance to switch off such checks for speed.
  */
 write_object_value(foreign_value);

 /* no spare arguments here, for speed's sake */

 send_ffs_message(); /* a macro - beware! */

 if (FFS_DEBUG)
    printf("Sent RETURN_FOREIGN_VALUE.\n");
 return 0;
}




/***************************
 * sender for SIGNAL_ERROR * 
 ***************************/

/*
 * The user can call catch_signals_inside_foreign_calls to arrange for
 * core-dumping signals (bus errors, segmentation violations, etc.) to be handled
 * by the foreign function server.  If FFS catches a signal, it will send a
 * SIGNAL_ERROR message with code SIGNAL_CAUGHT_DURING_CALL.
 */

ffe_int         check_for_errors_p = FALSE;

/*
 * The function error_check_around_foreign_calls is provided to give the user
 * control over the trade-off between speed and safety.  Note that this function
 * has no effect on signal catching, since that can be done without performance
 * degradation.  We give the user control over signal catching by providing the
 * function catch_signals_in_foreign_calls.
 */
int error_check_around_foreign_calls()
{
 check_for_errors_p = TRUE;
 return 0;
}


char *signal_to_string_array[] =
     {
      "quit",
      "illegal instruction",
      "trace trap",
      "IOT instruction or abort",
      "EMT instruction",
      "floating point exception",
      "bus error",
      "segmentation violation",
      "bad argument to system call",
      "resource lost",
      "FFS: unknwon signal"
     };

char *
signal_code_to_string(signal_code)
int     signal_code;
{
 switch (signal_code)
 {
#if !defined(WIN32)
  case SIGQUIT: return signal_to_string_array[0]; break;
  case SIGTRAP: return signal_to_string_array[2]; break;
  case SIGIOT:  return signal_to_string_array[3]; break;
#ifndef linux
  case SIGEMT:  return signal_to_string_array[4]; break;
#endif
  case SIGBUS:  return signal_to_string_array[6]; break;
#ifndef linux
  case SIGSYS:  return signal_to_string_array[8]; break;
#endif
#endif
  case SIGILL:  return signal_to_string_array[1]; break;
  case SIGFPE:  return signal_to_string_array[5]; break;
  case SIGSEGV: return signal_to_string_array[7]; break;
#if defined(sun) && !defined(sparcsol)
  case SIGLOST: return signal_to_string_array[9]; break;
#endif /* sun */
  default:      return signal_to_string_array[10]; break;
  }
}


void
handle_ffs_signals(int ffs_signal)
{
 if (error_within_error_p)
  {
   printf("Error while handling error in foreign function server.\n");
   printf("Sorry, must exit.\n");
   exit(-1);
  }

 error_within_error_p = TRUE;

 signal(ffs_signal, handle_ffs_signals);
 send_icp_signal_ffs_error(FFS_SIGNAL_CAUGHT_DURING_CALL, 
                           ffs_signal, 
                           errno,
			   signal_code_to_string(ffs_signal));
 if (FFS_DEBUG)
    printf("FFS caught signal %d.  Exiting.\n", ffs_signal);

 exit(-1);
/* 
 * jh, 2/22/92.  Keep the following around in case we decide to try
 * continuable signals.  For now, though, we have no way of knowing how
 * much damage the foreign image has sustained, so we simply exit().
 */
/*
 if (ffs_toplevel_catcher_established_p)
    {
     longjmp(ffs_toplevel_catcher, 1);
    }
 else
    {
     printf("No resumption point established in foreign function server.\n");
     printf("Sorry, must exit.\n");
     exit(-1);
    }
*/
}


int catch_signals_in_foreign_calls()
{
 /* The following signals cause a core dump and probably should be trapped */
#if !defined(WIN32)
 signal(SIGQUIT, handle_ffs_signals); /* quit                        */
 signal(SIGTRAP, handle_ffs_signals); /* trace trap                  */
 signal(SIGIOT, handle_ffs_signals);  /* IOT instruction or abort    */
#ifndef linux
 signal(SIGEMT, handle_ffs_signals);  /* EMT instruction             */
#endif
 signal(SIGBUS, handle_ffs_signals);  /* bus error                   */
#ifndef linux
 signal(SIGSYS, handle_ffs_signals);  /* bad argument to system call */
#endif
#endif
 signal(SIGILL, handle_ffs_signals);  /* illegal instruction         */
 signal(SIGFPE, handle_ffs_signals);  /* floating point exception    */
 signal(SIGSEGV, handle_ffs_signals); /* segmentation violation      */
#if defined(sun) && !defined(sparcsol)
 signal(SIGLOST, handle_ffs_signals); /* resource lost               */
#endif
 return 0;
}


/*
 * IMPORTANT NOTE:
 * send_icp_signal_ffs_error must never send the following values for
 * local_error_code unless it has received CALL_FOREIGN_FUNCTION message and has
 * not yet sent a corresponding RETURN_FOREIGN_VALUE message:
 *   SIGNAL_CAUGHT_DURING_CALL
 *   UNKNOWN_FUNCTION
 *   UNKNOWN_RETURN_TYPE
 * Sending these codes outside this interval will crash G2, since it will cause
 * G2 to report a stack error when there is no top-of-stack available.  For
 * further details, see the Lisp module G2-FOREIGN, under the
 * signal-foreign-function-error ICP handler.  jh, 9/5/91.

 */
void send_icp_signal_ffs_error(local_error_code,
			       signal_caught_if_any,
			       errno_if_applicable,
			       error_string)
int     local_error_code;
int     signal_caught_if_any;
int     errno_if_applicable;
char   *error_string;
{
 if (FFS_DEBUG)
    {
     printf("\nAbout to send SIGNAL_ERROR (%d).\n",
            FFS_SIGNAL_ERROR_MESSAGE);
     printf("  local code: %d\n", local_error_code);
     printf("  signal    : %d\n", signal_caught_if_any);
     printf("  errno     : %d\n", errno_if_applicable);
     printf("  message:  : \"%s\"\n", error_string);
    }

 /* Reply with "FFS in error" message */
 wricpbyte(ICP_MSG_OFFSET + FFS_SIGNAL_ERROR_MESSAGE);

 wr_icp_int(local_error_code);
 wr_icp_int(signal_caught_if_any);
 wr_icp_int(errno_if_applicable);

 wr_icp_str(error_string);

 /* These spare slots are unused for now. */
 wr_icp_int(0);
 wr_icp_str("");

 send_ffs_message(); /* A macro - beware! */

 if (FFS_DEBUG)
    printf("Sent SIGNAL_ERROR.\n\n");
}










/****************************************
 * handler for REQUEST_FOREIGN_REGISTRY * 
 ****************************************/

ffe_int handle_req_foreign_registry()
{
 int      spare_code;
 obj_value_type temp_value;

 if (FFS_DEBUG)
    printf("About to handle REQUEST_FOREIGN_REGISTRY (%d).\n",
           FFS_REQUEST_FOREIGN_REGISTRY_MESSAGE);

 /* FFS ignores these spare arguments for now. */
 spare_code = rd_icp_int();
 rd_icp_str(&temp_value);

 send_icp_prov_foreign_registry();

 if (FFS_DEBUG)
    printf("Handled REQUEST_FOREIGN_REGISTRY.\n\n");

 return FFE_SUCCESS;
}




/*************************************
 * handler for CALL_FOREIGN_FUNCTION *
 *************************************/


ffe_int handle_call_foreign_function()
{
 int                      key, i;
 FOREIGN_FUNCTION_ENTRY  *entry;
 TEMP_PARAM              *foreign_result;

 if (FFS_DEBUG)
    printf("About to handle CALL_FOREIGN_FUNCTION (%d).\n",
            FFS_CALL_FOREIGN_FUNCTION_MESSAGE);

 /* need function key (integer to avoid string search) */
 key = rd_icp_int();
 if (check_for_errors_p &&
     (key < 0 || key > latest_foreign_entry->index))
    {
     send_icp_signal_ffs_error(FFS_UNKNOWN_FUNCTION, 0, 0, "unknown function");
     return FFE_SUCCESS;
    }
 entry = &foreign_function_registry[key - 1];

 if (FFS_DEBUG_VERBOSE)
  {
   printf_foreign_entry(entry);
  }

 /* store arg values in pre-allocated TEMP_PARAMs */
 /* How do we check for correct argcount?  Perhaps on the G2 side. */
 for (i = 0; i < entry->argcount; i++)
  {
   read_object_value(&(entry->arglist)[i]);
  }

 if (FFS_DEBUG_VERBOSE)
  {
   for (i = 0; i < entry->argcount; i++)
    {
     printf("  received arg#%d (%s): %s\n",
            i, 
            foreign_typetag_to_string((entry->arglist)[i].p_type),
            foreign_value_to_string(&entry->arglist[i])
           );
    }
  }

 /* 
  * call registered foreign function - remember to check for existence here, in a
  * test users can disable for speed
  */
 foreign_result = (entry->function_address)(entry->arglist, entry->argcount);

 /* check for correct types here, in a test that users can disable for speed */
 if (check_for_errors_p &&
     foreign_result->p_type != INTEGER_TAG &&
     foreign_result->p_type != FLOAT64_TAG &&
     foreign_result->p_type != SYMBOL_TAG &&
     foreign_result->p_type != STRING_TAG)
    {
     send_icp_signal_ffs_error(FFS_UNKNOWN_RETURN_TYPE, 0, 0, "unknown return type");
     return FFE_SUCCESS;    
    }

 if (FFS_DEBUG_VERBOSE)
  {
  printf("  returning value  (%s): %s\n",
         foreign_typetag_to_string(foreign_result->p_type),
         foreign_value_to_string(foreign_result)
        );
  }

 /* return the result of the foreign call to G2 */
 send_icp_return_foreign_value(foreign_result);

 if (FFS_DEBUG)
    printf("Handled CALL_FOREIGN_FUNCTION.\n\n");

 return FFE_SUCCESS;
}



/***************************
 * handler for KILL_SERVER *
 ***************************/

int exit_foreign_function_server()
{
 if (FFS_DEBUG)
    printf("Normal exit of foreign function server.\n\n");

/*
 * Check with Paul to see that this suffices to clean up all open sockets.
 */
 exit(0);
}

#define EXIT_FFS_SERVER   0
#define CLOSE_FFS_CONTEXT 1

ffe_int handle_kill_server()
{
 int      response_code;
 obj_value_type temp_value;

 if (FFS_DEBUG)
    printf("About to handle KILL_SERVER (%d).\n",
           FFS_KILL_SERVER_MESSAGE);

 response_code = rd_icp_int();
 /* FFS ignores this spare argument for now. */
 rd_icp_str(&temp_value);

 switch (response_code)
  {
   case EXIT_FFS_SERVER: exit_foreign_function_server(); break;
   /* 
    * jh, 6/27/94.  With the advice of paf!, the code for the following case was
    * extracted from the function shutdown_rcvr() in /bt/ab/ext/c/gsi.c, used in
    * the GSI 3.2 product.  The purpose is to allow an external foreign image to
    * receive a KILL_SERVER message without exiting, since G2 is not the parent
    * process of an external foreign image.
    */
   case CLOSE_FFS_CONTEXT: 
    {
     char    msg_buff[64];

     foreign_registry_provided_p = FALSE;
     g2ext_network_close(curr_ctx->socket);
     icp_context_table[icp_current_context].state = RE_USE;
     icp_active_contexts--;
     /* 
      * OK to call ext_message() because output suppression is always on for the
      * end-user of foreign images and de-suppressing output might be useful
      * when we debug.
      */
     sprintf(msg_buff,"Connection closed - context %d", (int)icp_current_context);
     ext_message(msg_buff,NO_SEND);
     break;
    }
   default: 
    printf("Unknown response code %d for foreign function server.\n",
           response_code);
    exit_foreign_function_server();
    break;
  }

 if (FFS_DEBUG)
    printf("Handled KILL_SERVER.\n");

 return(FFE_SUCCESS);
}

/*********************************
 * handler for SHUT_DOWN_CONTEXT *
 *********************************/

/* 
 * jh, 11/3/93.  handle_shut_down_context() is copied from shutdown_rcvr() in
 * gsi.c.  I dispensed with some of the more sophisticated error reporting.
 */

ffe_int handle_shut_down_context()
{
 if (FFS_DEBUG)
    printf("About to handle SHUT_DOWN_CONTEXT (%d).\n",
           FFS_SHUT_DOWN_CONTEXT_MESSAGE);

/*  For some reason this
    function is sometimes called when it shouldn't be. 
    So exit if this port has already been recycled.
    -------------------------------------------------*/
    if (icp_context_table[icp_current_context].state == RE_USE) {
        if (FFS_DEBUG)
	  printf("doubly reclaimed context in handler for SHUT_DOWN_CONTEXT\n");
        return(FFE_FAILURE); }

/*  Close (free) the handle that corresponds to the current context.
    ------------------------------------------------------------------*/
    g2ext_network_close(curr_ctx->socket);

/*  Reset a flag in the current context structure and decrement
    global count of active contexts.
    --------------------------------------------------------------------*/
    icp_context_table[icp_current_context].state = RE_USE;
    icp_active_contexts--;

/*  Return in accordance with status of previous calls.
    ------------------------------------------------------*/
    return(FFE_SUCCESS);

} /* end handle_shut_down_context() */


/*
 * The following functions are dummies intended to catch reversed
 * or otherwise bizarrely configured connections.
 */


int reversed_ffs_connection_error(message_name)
char     *message_name;
{
 if (FFS_DEBUG)
    printf(
"WARNING: FFS extension process received %s, which should never happen.\n\
(The FFS extension should exclusively transmit, not receive, this message.)\n\
The FFS connection is reversed or otherwise corrupt.  Sorry, must exit.\n",
           message_name
          );
 exit_foreign_function_server();
 return 0;
}


ffe_int handle_image_ready()
{
 reversed_ffs_connection_error("FFS_IMAGE_READY");
 return(FFE_SUCCESS);
}

ffe_int handle_prov_foreign_registry()
{
 reversed_ffs_connection_error("FFS_PROVIDE_FOREIGN_REGISTRY");
 return(FFE_SUCCESS);
}

ffe_int handle_return_foreign_value()
{
 reversed_ffs_connection_error("FFS_RETURN_FOREIGN_VALUE");
 return(FFE_SUCCESS);
}

ffe_int handle_signal_error()
{
 reversed_ffs_connection_error("FFS_SIGNAL_ERROR");
 return(FFE_SUCCESS);
}




/* **********************************************************

   Function load_icp_functions()
   Args: none

   This function is called to load the array of icp functions that
   will be executed by the icp handler.

   *************************************************************/

void load_icp_functions()
{
    icp_func_array[FFS_IMAGE_READY_MESSAGE]
                                                 = handle_image_ready;
    icp_func_array[FFS_REQUEST_FOREIGN_REGISTRY_MESSAGE]
                                                 = handle_req_foreign_registry;
    icp_func_array[FFS_PROVIDE_FOREIGN_REGISTRY_MESSAGE]
                                                 = handle_prov_foreign_registry;
    icp_func_array[FFS_CALL_FOREIGN_FUNCTION_MESSAGE]
                                                 = handle_call_foreign_function;
    icp_func_array[FFS_RETURN_FOREIGN_VALUE_MESSAGE]
                                                 = handle_return_foreign_value;
    icp_func_array[FFS_SIGNAL_ERROR_MESSAGE]
                                                 = handle_signal_error;
    icp_func_array[FFS_KILL_SERVER_MESSAGE]
                                                 = handle_kill_server;
    icp_func_array[FFS_SHUT_DOWN_CONTEXT_MESSAGE]
                                                 = handle_shut_down_context;

/*  Load the FFS shutdown function into a global function pointer.
    -----------------------------------------------------------------*/
    icp_shutdown_function = handle_shut_down_context;
}


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION get_version_info:                 Copyright (C) 1986-2017 Gensym Corporation
:
:  This function stuffs the version information for foreign functions into the
:  given string.
:
:  Arguments:        version_buffer  A string.
:  Return Behavior:  None (void function).
:  Users:            extensn.c:  start_extension().
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  001  13sep94  paf!       Added support for release qualifiers Alpha and Beta.
:.............................................................................*/
ffe_int get_version_info(version_buffer)
    char *version_buffer;
{
#ifdef DEBUG
    strcpy(where_in_extension,"get_version_info");
    printf("  %s\n",where_in_extension);
#endif

/*  If the version of foreign module matches versions of include files used to 
    compile user code, format version info, otherwise print an error message.
    --------------------------------------------------------------------------*/
    if ((ffe_include_file_major_version == ICP_MAJ_VER_NUM) &&
        (ffe_include_file_minor_version == ICP_MIN_VER_NUM) &&
        (ffe_include_file_major_version == icp_include_file_major_version) &&
        (ffe_include_file_minor_version == icp_include_file_minor_version)) {

        sprintf(version_buffer,"\nForeign Function Version %ld.%ld %sRev. %ld",
                                               ICP_MAJ_VER_NUM,
                                               ICP_MIN_VER_NUM,
                                               ICP_RELEASE_QUALIFIER,
                                               ICP_DELTA_REV_NUM);
	return(FFE_SUCCESS); }

    if ((ffe_include_file_major_version != icp_include_file_major_version) ||
        (ffe_include_file_minor_version != icp_include_file_minor_version)) {

        printf("\nError - version mismatch between foreign.h and icp.h which\n");
        printf("were used to compile your application.\n");
        printf("    foreign.h: %d.%d\n", (int)ffe_include_file_major_version,
                                         (int)ffe_include_file_minor_version);
        printf("    icp.h: %d.%d\n\n", (int)icp_include_file_major_version,
	                               (int)icp_include_file_minor_version); }

    if ((ffe_include_file_major_version != ICP_MAJ_VER_NUM) ||
        (ffe_include_file_minor_version != ICP_MIN_VER_NUM)) {

        printf("\nError - version mismatch between the forgn.a library and the\n");
        printf("include files used to compile your application.\n");
        printf("    Foreign Functions Library: %d.%d\n", (int)ICP_MAJ_VER_NUM,
                                                         (int)ICP_MIN_VER_NUM);
        printf("    foreign.h: %d.%d\n", (int)ffe_include_file_major_version,
                                         (int)ffe_include_file_minor_version);
        printf("    icp.h: %d.%d\n\n", (int)ffe_include_file_major_version,
                                       (int)ffe_include_file_minor_version); }

    return(FFE_FAILURE);

} /* end get_version_info */

ffe_int allow_ext_proc()
{
    return (FFE_SUCCESS);
}

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION InitUsrRpcs:                      Copyright (C) 1986-2017 Gensym Corporation
:
:  This function is here to satisfy extension_start which will assume RPCS are
:  used in all ICP extension products.  They are not used in Foreign Functions.
:
:  Arguments:        None.
:  Return Behavior:  None (void function).
:  Users:            extensn.c:  extension_start().
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
ffe_int InitUsrRpcs()
{
    return(FFE_SUCCESS);
}
