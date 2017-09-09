/*******************************************************************************
:
:  sysattrs.c  --  GSI regression test receiving system attributes in GSI
:
:  Copyright (C) 1986-2017 Gensym Corporation.
:  All Rights Reserved.
:
:  Usage summary:
:
:    sysattrs [-exclude-user-attrs | -include-system-attrs | include-all-system-attrs-except] 
:              [host [port]]
:        -include-system-attrs - Tests including system attributes
:        -exclude-user-attrs - Tests excluding user attributes
:        -include-all-system-attrs-except - Tests including all system attributes
:                               while excluding some
:        host   host name or ip address; defaults to "localhost"
:        port   tcp/ip port to use; defaults to 1111
:
:  Allan Scott, 3/19/04
:
:.............................................................................*/

#define GSI_USE_USER_DATA_FOR_CALLBACKS

#include <stdio.h>
#include "gsi_main.h"
#include "gsi_misc.h"

gsi_function_handle_type getitem;

extern declare_gsi_rpc_receiver_fn(getitem_return_receiver);

int connected = 0;
int my_context = -1;
int processing_rpc = 0;
int include_system_attrs = 0;
int exclude_user_attrs = 0;
int include_all_system_attrs_except = 0;


void getitem_return_receiver(gsi_procedure_user_data_type data,
			gsi_item *args,
			gsi_int count,
			gsi_call_identifier_type call_identifier)
{
  gsi_item item;
  
  item = args[0];
  
  printf("-------------------------\n");
  printf("Item returned:\n");
  gsirtl_display_item_or_value(item,STARTING_LEVEL,STANDARD_OUT);
  printf("-------------------------\n");

  processing_rpc = 0;
}

void exit_if_gsi_error()
{
  if (gsi_last_error() == 0)
    return;
  fprintf(stderr, "Error!");
  fflush (stderr);    
  exit(2);
}


static void usage()
{
  printf("sysattrs [-exclude-user-attrs | -include-system-attrs |\n");
  printf("         -include-all-system-attrs-except] [host [port]]\n\n"); 
  printf("-include-system-attrs            Tests including system attributes\n");
  printf("-exclude-user-attrs              Tests excluding user attributes\n");
  printf("-include-all-system-attrs-except Tests including all system attributes\n");
  printf("                                 while excluding some\n");
  printf("host                             host name or ip address; defaults to localhost\n");
  printf("port                             tcp/ip port to use; defaults to 1111\n");
}


int main(int argc, char *argv[])
{
  char *host = "localhost";
  char *port_string = "1111";
  int i, port;
  char *option;

  if (argc > 4 ||
      argc < 2) {
    usage();
    exit(1);
  }
   
  i = 1;
  option = argv[i];
  
  if (! strcmp("-include-system-attrs",option)) {
    include_system_attrs = 1;
  }
  else if (! strcmp("-exclude-user-attrs",option)) {
    exclude_user_attrs = 1;
  }
  else if (! strcmp("-include-all-system-attrs-except",option)) {
    include_all_system_attrs_except = 1;
  }
  else {
    usage();
    exit(1);
  }

  i++;
  if (i < argc) {
    host = argv[i]; 
    i++;
    if (i < argc) {
      if (sscanf(argv[i], "%d", &port) == EOF) {
	usage();
	exit(1);
      }
      port_string = (char *)strdup(argv[i]);
    }
  }

  gsi_set_include_file_version
    (GSI_INCLUDE_MAJ_VER_NUM, GSI_INCLUDE_MIN_VER_NUM, GSI_INCLUDE_REV_VER_NUM);
  GSI_SET_OPTIONS_FROM_COMPILE();
  gsi_start(argc, argv);
  exit_if_gsi_error();
  gsi_initiate_connection
    (NULL,NULL, FALSE, "TCP-IP", host,
     port_string, "hello from GSI");
  while (!connected) {
    exit_if_gsi_error();
    gsi_set_pause_timeout(10);	/* pause period = 10 milliseconds */
    gsi_pause();
    gsi_run_loop();
  }

  processing_rpc = 1;
  gsi_rpc_call(getitem, NULL, (gsi_call_identifier_type) 1, my_context);

  while (processing_rpc) {
    gsi_run_loop();
    gsi_pause();
    exit_if_gsi_error();
  }

  gsi_close_listeners();
  return 0;
}

void gsi_set_up()
{
  gsi_set_option(GSI_ONE_CYCLE);
  gsi_clear_last_error();
}


gsi_int gsi_initialize_context(remote_process_init_string, length)
    gsi_char *remote_process_init_string;
    gsi_int  length;
{
  gsi_item *items;  

  if (include_system_attrs) {
    gsi_char *uuidName = gsirtl_strdup("UUID");
    gsi_char *itemWidthName = gsirtl_strdup("ITEM-WIDTH");
    gsi_char *itemNotesName = gsirtl_strdup("ITEM-NOTES");
  
    items = gsi_make_items(3);
    
    gsi_set_sym(items[0],gsi_make_symbol(uuidName));
    gsi_set_sym(items[1],gsi_make_symbol(itemWidthName));
    gsi_set_sym(items[2],gsi_make_symbol(itemNotesName));
    
    gsi_clear_last_error();
    
    gsi_rpc_declare_remote
      (&getitem, "GETITEM", getitem_return_receiver,
       (procedure_user_data_type)NULL, 0, 1, current_context);
    
    gsi_set_rpc_remote_return_include_system_attrs(getitem, items); 
  }
  else if (exclude_user_attrs) {
    gsi_char *csaName = gsirtl_strdup("CSA");
    
    items = gsi_make_items(1);
    gsi_set_sym(items[0],gsi_make_symbol(csaName));
    
    gsi_clear_last_error();
    
    gsi_rpc_declare_remote
      (&getitem, "GETITEM", getitem_return_receiver,
       (procedure_user_data_type)NULL, 0, 1, current_context);
    
    gsi_set_rpc_remote_return_exclude_user_attrs(getitem, items);
  }
  else if (include_all_system_attrs_except)
  {
    gsi_char *uuidName = gsirtl_strdup("UUID");

    items = gsi_make_items(1);
    gsi_set_sym(items[0],gsi_make_symbol(uuidName));
    
    gsi_clear_last_error();
    
    gsi_rpc_declare_remote
    (&getitem, "GETITEM", getitem_return_receiver,
    (procedure_user_data_type)NULL, 0, 1, current_context);
    
    gsi_set_rpc_remote_return_include_all_system_attrs_except(getitem, items);
  }
  
  my_context = gsi_current_context();
  
  connected = 1;
  
  return(GSI_ACCEPT);
}

/* The remaining callback functions are required by GSI, but they're for now
   defined as empty stubs.*/

gsi_int gsi_get_tcp_port()
{
  return 0;
}

void gsi_receive_registration(gsi_registration registration)
{
}

void gsi_get_data(gsi_registered_item registered_item_array[], gsi_int count)
{}

void gsi_set_data(gsi_registered_item  registered_item_array[], gsi_int count)
{}

void gsi_pause_context()
{}

void gsi_resume_context()
{}

void gsi_shutdown_context()
{}

void gsi_g2_poll()
{}

void gsi_receive_deregistrations(gsi_registered_item  registered_item_array[], gsi_int count)
{}

void gsi_receive_message(gsi_char *message, gsi_int length)
{}



