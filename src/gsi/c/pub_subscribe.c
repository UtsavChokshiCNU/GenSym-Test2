/***************************************************************************
:
:  skeleton.c  --  Sample user function file to link with GSI toolkit.
:
:  This file contains all of the function stubs required of GSI user code --
:  plus some printf's.  Feel free to use this as a basis for your GSI
:  application by adding code to the functions to suit your needs.
:
:  Note that this must be linked with the standard gsi_main.c.
:
:  This file conforms to GSI 4.0 and GSI 5.0.
:
:..........................................................................*/

#include <stdio.h>
#include "gsi_main.h"
#include "gsi_misc.h"

/* gsi_show_callback and gsi_show_registered_items are utility functions */
/* defined at the end of this file.                                      */
extern void gsi_show_callback(); 
extern void gsi_show_registered_items(); 

/* Allow the local procedure that is the callback to receive values from G2 */
extern declare_gsi_rpc_local_fn(rpc_remote_callback);

/*Create a handle for the remote procedure in G2 */
gsi_function_handle_type subscribe_to_tank_changes_with_remote_callback;

#define TCPIP_PORT_NUMBER  0

void gsi_set_up ()
{
  gsi_rpc_declare_local(rpc_remote_callback, "RPC-REMOTE-CALLBACK");
}

gsi_int gsi_get_tcp_port()
{
  return(TCPIP_PORT_NUMBER);
}

gsi_int gsi_initialize_context(remote_process_init_string, length)
    gsi_char *remote_process_init_string;
    gsi_int  length;
{
  gsi_int context = gsi_current_context();
  double start_time = gsi_context_remote_process_start_time(context);
  gsi_int listener_port = gsi_context_remote_listener_port(context);
  gsi_char *host = gsi_context_remote_host(context);
  gsi_int year, month, day, hour, minute, second;

  gsi_item* args;

  gsi_show_callback("gsi_initialize_context");
  if (host && listener_port != 0 && start_time > 0.0) {
    gsi_decode_timestamp(start_time, &year, &month, &day, &hour, &minute, &second);
    printf("G2 host=%s, port=%d, start time=%d %d %d %d %d %d\n",
	   host,
	   listener_port,
	   year, month, day, hour, minute, second);
  } else if (host && 0 != strcmp(host,""))
    printf("G2 host=%s\n",host);
  printf("remote_process_init_string: %s\n",remote_process_init_string);
  
  /* Declare a remote procedure for the subscription procedure in G2 */
  gsi_rpc_declare_remote(&subscribe_to_tank_changes_with_remote_callback, "SUBSCRIBE-TO-TANK-CHANGES-WITH-REMOTE-CALLBACK", NULL_PTR, 1, 0, context);

  args = gsi_make_items(1);

  /* Tell G2 the name of the remote callback */
  gsi_set_sym(args[0], "RPC-REMOTE-CALLBACK"); 

  /* Start the subscription procedure in G2 */
  gsi_rpc_start(subscribe_to_tank_changes_with_remote_callback, args, context); 
  
  return (GSI_ACCEPT);
}


void gsi_receive_registration(item_registration)
    gsi_registration item_registration;
{
  gsi_show_callback("gsi_receive_registration");
  printf("   handle: %d\n", gsi_handle_of(item_registration));
}

void gsi_receive_deregistrations(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
  gsi_show_registered_items("gsi_receive_deregistrations", 
			    registered_items, count);
}

void gsi_get_data(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
  gsi_show_registered_items("gsi_get_data", 
			    registered_items, count);
}

void gsi_set_data(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
  gsi_show_registered_items("gsi_set_data", 
			    registered_items, count);
}

void gsi_pause_context()
{
  gsi_show_callback("gsi_pause_context");
}

void gsi_resume_context()
{
  gsi_show_callback("gsi_resume_context");
}

void gsi_shutdown_context()
{
  gsi_show_callback("gsi_shutdown_context");
}

void gsi_g2_poll()
{
  gsi_show_callback("gsi_g2_poll");
}

void gsi_receive_message(message, length)
    gsi_char     *message;
    gsi_int      length;
{
  gsi_show_callback("gsi_receive_message");
  printf("message from G2:%s\n",message);
}

/* --------------------------------------------------------- */

/* Utility functions used in this file, to aid in debugging. */

void gsi_show_callback(name)
    char *name;
{
  printf("%s: context %d\n",name,gsi_current_context());
}

void gsi_show_registered_items(name, registered_items, count)
    char                 *name;
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
  printf("%s: context %d\n",name,gsi_current_context());
  if (0 < count) {
    int i;
    printf("   handles: ");
    printf("%d",gsi_handle_of(registered_items[0]));
    for(i=1; i< count; i++) printf(",%d",gsi_handle_of(registered_items[i]));
    printf("\n");
  }
}

/* Remote callback that G2 invokes when an attribute of the tank changes */
void rpc_remote_callback(item_array, count, call_index)
    gsi_item item_array[];
    gsi_int count;
    call_identifier_type call_index;
{
  int i;
  /* event: symbol, handle: integer, info: sequence, new-val: item-or-value,
     user-data: item-or-value, callback-handle: integer */
 	printf("Event: %s, Item-handle: %d, Level: %d\n",

	gsi_sym_of(item_array[0]),
	gsi_handle_of(item_array[1]),
	gsi_int_of(item_array[3]));

   
for (i=0;i<count;i++)
    gsirtl_display_item_or_value(item_array[i], 0, 0);

}

