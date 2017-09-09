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

/* gsi_show_callback and gsi_show_registered_items are utility functions */
/* defined at the end of this file.                                      */
extern void gsi_show_callback(); 
extern void gsi_show_registered_items(); 

#define TCPIP_PORT_NUMBER  0

void gsi_set_up ()
{
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

	
