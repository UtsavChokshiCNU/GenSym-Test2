/*****************************************************************************
: 
:  itemtest.c  --  Sample GSI Bridge Code for use with itempass.kb
:
:  This file contains the standard GSI toolkit functions required for any GSI
:  application.  These functions have been coded to support the sample
:  knowledge base `itempass.kb' provided with G2.  This file requires only the
:  standard GSI libraries to create the executable `itemtest'.
:
:  Although this software has been extensively tested, Gensym cannot
:  guarantee error-free performance in all applications.  Accordingly,
:  use of the software is at the customer's sole risk.
:
:  03nov94 by paf! -- Created
:  11oct97 by rh   -- Updated for GSI 5.0.1
:..........................................................................*/

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "gsi_main.h"
#include "gsi_misc.h"

#define TCPIP_PORT_NUMBER        0 /* Returning 0 from gsi_get_tcp_port() */
				   /* will cause GSI to pick the first    */
                                   /* number available starting at 22041. */
#define STORE_SIZE               5
#define MAX_STORE_INDEX          STORE_SIZE - 1

gsi_item *item_or_value_store;
long      store_index = 0;
gsi_item *error_object_ptr;

extern declare_gsi_error_handler(itemtest_error_handler);

extern declare_gsi_rpc_local_fn(receive_item_or_value);
extern declare_gsi_rpc_local_fn(receive_and_return_copy);
extern declare_gsi_rpc_local_fn(receive_item_transfer);
extern declare_gsi_rpc_local_fn(receive_request_for_copy);

main(argc, argv)
    int   argc;
    char *argv[];
{
/*
 *  Set the version control variables to the values defined in gsi_main.h.
 *  Though optional, this is recommended to ensure version consistency between
 *  the GSI object libraries, and the include files used to compile your 
 *  application code.
 */
  gsi_set_include_file_version(GSI_INCLUDE_MAJ_VER_NUM, 
			       GSI_INCLUDE_MIN_VER_NUM,
			       GSI_INCLUDE_REV_VER_NUM);
  GSI_SET_OPTIONS_FROM_COMPILE();

/*
 *  Initialize GSI and enter the event handler loop.
 */
    gsi_start(argc, argv);
 
    return 0;

} /* end main */


void itemtest_error_handler(econtext, ecode, emessage)
    gsi_int  econtext;
    gsi_int  ecode;
    char    *emessage;
{ 
/*
 *  GSI application designer may place code here to react in
 *  accordance with various errors e.g. call abort or exit.  In
 *  this case we do nothing and allow the built in error handler
 *  to continue from errors by jumping out to the main run loop.
 */
}


void receive_item_or_value(arg_array,count,call_index)
    gsi_item  arg_array[];
    gsi_int   count;
    gsi_int   call_index;
{
/*
 *  Display the entire contents of the argument to standard out.
 *  Items arguments are displayed recursively attribute by attribute.
 */
    printf("count = %d, store_index = %d\n",count,store_index);
    printf("-------------------------\n");
    printf("  Printing argument\n");
    printf("-------------------------\n");
    gsirtl_display_item_or_value(arg_array[0],STARTING_LEVEL,STANDARD_OUT);
    printf("------------------------- end of argument.\n");

/*
 *  This program keeps a rotating store of STORE_SIZE items.
 *  Copy the argument into the item_or_value_store which is 
 *  an array of gsi_item's.
 */
    gsirtl_copy_item_or_value(arg_array[0],item_or_value_store[store_index]);

/*
 *  Increment the store index (resetting it if it is maxed) and free
 *  memory for displaced items.  Note that the item structure itself
 *  is not reclaimed but any sub parts (values or attributes) which
 *  take up memory are reclaimed.
 */
    if (store_index == MAX_STORE_INDEX)
      store_index = 0;
    else
      store_index++;
    gsirtl_free_i_or_v_contents(item_or_value_store[store_index]);

} /* end receive_item_or_value */


void receive_item_transfer(arg_array,count,call_index)
    gsi_item  arg_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
/*
 *  The contract of this function is a simple superset of 
 *  that for receive_item_or_value(), so it is called here.
 */
    receive_item_or_value(arg_array,count,call_index);

/*
 *  This function is called as opposed to started by G2 and as such
 *  must return even if no arguments are returned.
 */
    gsi_rpc_return_values(NULL_PTR,0,call_index,current_context);

} /* end receive_item_transfer */


void receive_and_return_copy(arg_array,count,call_index)
    gsi_item  arg_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    gsi_int   duplicate_index;
/*
 *  The contract of this function is a simple superset of 
 *  that for receive_item_or_value(), so it is called here.
 */
    receive_item_or_value(arg_array,count,call_index);

/*
 *  Return the copy to G2.  Note, that receive_item_or_value()
 *  increments the store index so we have to look back one to
 *  get at the duplicate that was generated by the function.
 */
    if (store_index == 0)
      duplicate_index = MAX_STORE_INDEX;
    else
      duplicate_index = store_index - 1;
    printf("\n------>\n"); 
    gsi_rpc_return_values(&item_or_value_store[duplicate_index],1,call_index,current_context);
    printf("   <\n");
} /* end receive_and_return_copy */


void receive_request_for_copy(arg_array,count,call_index)
    gsi_item  arg_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    long      i;
    char     *search_name = sym_of(arg_array[0]);
    char     *iv_name;
    gsi_item  item_or_value;

/*
 *  This function, searches the item_or_value_store 
 *  for an item given the item's name.
 */
    for (i=0; i<=MAX_STORE_INDEX; i++) {
      item_or_value = item_or_value_store[i];
      iv_name = name_of(item_or_value);
      if (strcmp(iv_name,search_name) == 0) {
	gsi_rpc_return_values(&item_or_value,1,call_index,current_context);
	return; }
    } /* end for */

    gsi_rpc_return_values(error_object_ptr,1,call_index,current_context);

} /* receive_request_for_copy */


void gsi_set_up()
{
    gsi_item  error_object;
    gsi_attr *name_attr_ptr;
    gsi_attr  name_attr;

/*
 *  The following two lines only have relevance on VAX systems
 *  where more than one floating point format are supported.
 */
#   ifdef vax
#       if CC$gfloat
          gsi_set_option(GSI_USE_GFLOATS);
#       endif
#   endif

/*
 *  Install custom error handler to be called after GSI internal
 *  errors occur and are handled by the internal error handler.
 */
    gsi_install_error_handler(itemtest_error_handler);


/*
 *  Declare the local functions called by G2 for this test.
 */
    gsi_rpc_declare_local(receive_item_or_value,
			  "RECEIVE-AND-DISPLAY-ITEM");
    gsi_rpc_declare_local(receive_and_return_copy,
			  "RECEIVE-AND-RETURN-ITEM-COPY");
    gsi_rpc_declare_local(receive_item_transfer,
			  "RECEIVE-AND-DISPLAY-TRANSFER");
    gsi_rpc_declare_local(receive_request_for_copy,
			  "RECEIVE-REQUEST-ITEM-COPY");

/*
 *  Allocate and set up context-independent global GSI structures.
 *  The error object which G2 expects to receive when an error occurs
 *  here is a simple object with only one attribute - the system
 *  attribute 'NAME'.  The value of this attribute is 'ERROR-OBJECT'.
 */
    error_object_ptr = gsi_make_items(1);
    error_object = *error_object_ptr;
    name_attr_ptr = gsi_make_attrs_with_items(1);
    name_attr = *name_attr_ptr;
    set_attr_name(name_attr,"NAME");
    set_sym(name_attr,"ERROR-OBJECT");
    set_attrs(error_object,name_attr_ptr,1);
    set_class_name(error_object,"OBJECT");

} /* end gsi_set_up */

gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{
/*
 *  Allocate memory for the item_or_value_store.
 */
    item_or_value_store = gsi_make_items(STORE_SIZE);
    store_index = 0;

    return(GSI_ACCEPT);
} 


void gsi_shutdown_context()
{
/*
 *  Reclaim the item_or_value_store in its entirety.
 */
    for (store_index=0;store_index<STORE_SIZE;store_index++)
      gsirtl_free_i_or_v_contents(item_or_value_store[store_index]);
    gsi_reclaim_items(item_or_value_store);
}


     
/************************************************
*
*  The remaining functions are all empty stubs.
*
*************************************************/

gsi_int gsi_get_tcp_port()
{
    return(TCPIP_PORT_NUMBER);
}

void gsi_receive_registration(registration)
    gsi_registration registration;
{}

void gsi_get_data(registered_item_array, count)
    gsi_registered_item registered_item_array[];
    gsi_int             count;
{}

void gsi_set_data(registered_item_array, count)
    gsi_registered_item  registered_item_array[];
    gsi_int              count;
{}

void gsi_pause_context()
{}

void gsi_resume_context()
{}

void gsi_g2_poll()
{}

void gsi_receive_deregistrations(registered_item_array, count)
    gsi_registered_item  registered_item_array[];
    gsi_int              count;
{}

void gsi_receive_message(message, length)
    char     *message;
    gsi_int   length;
{}
