#define   EXTERNS_DEFINED TRUE     /* To turn off part of icp.h include.      */
#include "gensym-features.h"       /* Machine dependent defines and includes. */
#include "foreign.h"             /* Defines and typedefs required by foreign 
                                      function application programs.          */
#include "icp_pvt.h"             /* Defines, typedefs and globals required by
                                      all ICP extensions.                     */
#include "cprim.h"
#include "networks.h"
#include "netevent.h"

extern icp_int ext_switch_context(icp_int context);
extern icp_int process_allocated_context(icp_int context);
extern icp_int add_context(icp_int socket, icp_int *context_ptr, icp_int partner_type);
extern void ext_error(icp_int  error, char *circumstance, icp_int data, icp_int send);
extern void ext_message(char *message, icp_int send);

#include <math.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h> /* added for FFS */

static icp_int stcm[256];			/* socket to context mapping */
char message[256];


void g2int_network_event_handler(ecode, socket_handle, event_status)
{
  icp_int context;
  int status, new_socket_handle;

  ext_switch_context(stcm[socket_handle]);
  
  if (ecode < 0) { 
    perror("error getting next event");
    if (errno != EINTR)
      exit(errno);
  }
  switch (ecode) {
  case read_event:
    ne_enable_read_events(socket_handle);
  case write_event:
    process_allocated_context(stcm[socket_handle]);
    break;
  case connect_event:
    printf("Foreign Function Server attempted to connect -- internal inconsistency. Please call Gensym Support.\n");
    exit(-1);
    break;
  case accept_event:
    new_socket_handle = g2ext_network_accept(socket_handle);

    if (add_context(new_socket_handle,&context,CLIENT) != ICP_SUCCESS) {
      if (g2ext_network_close(new_socket_handle) == NETWORK_FAIL)
	ext_error(CLOSE_SOCKET_FAILED,"extension_run_loop", NO_DATA,NO_SEND);
      status = ICP_FAILURE; }

    stcm[new_socket_handle] = context;

    sprintf(message, "Connection accepted - context %d", (int)context);
    ext_message(message,NO_SEND); /* end else */

    if (status != ICP_SUCCESS)
      goto EXIT_LOOP;
    break;

  case close_event:
    if (icp_shutdown_function != NULL) {
      (void)(*icp_shutdown_function)(); /* Status ignored - always FALSE */
    } 
    stcm[socket_handle] = (icp_int) -1;
    break;
    
  case scheduler_event: /* timer event, really.   No scheduler in FF! */
    break;
  }

EXIT_LOOP:
 
  ne_set_next_timer_event(5000);	/* XXX ? sleep for at most 5 seconds */
  return;
}


void fgn_event_loop ()
{
  for (;;) {
    g2_event_cycle(1); /* 1 means "wait allowed" */
  }
}

void g2int_run_trace_function(){}

long g2int_unix_command_callback(){return 0;}

