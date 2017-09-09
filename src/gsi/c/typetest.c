/*****************************************************************************
: 
:  typetest.c  --  Sample GSI Bridge Code for use with gsi_exam.kb
:
:  This file contains the standard GSI toolkit functions required for any GSI
:  application.  These functions have been coded to support the sample
:  knowledge base `gsi_exam.kb' provided with G2.  This file is linked
:  with `gsi_main.o' to create the executable `typetest'.  This file contains
:  code that supports one of four example uses of GSI demonstrated from G2 in
:  `gsi_exam.kb'.
:
:  Although this software has been extensively tested, Gensym cannot
:  guarantee error-free performance in all applications.  Accordingly,
:  use of the software is at the customer's sole risk.
:
:  28jul93 by paf! -- Upgraded to GSI 3.1
:  25jul94 by paf! -- Upgraded to GSI 4.0
:  11oct97 by rh   -- Upgraded to GSI 5.0.1
   22apr09         -- added int64-related tests
   17aug09         -- added int64 RPC-related tests
:...........................................................................*/


#include <stdio.h>
#include <string.h>
#include "gsi_main.h"

#define TCPIP_PORT_NUMBER             22040
#define MAX_REGISTERED_ITEMS_REQUIRED    10

gsi_int around = 1;
char    globstr[100];
gsi_int exit_on_pause;

gsi_registered_item  *my_registered_item_array;

gsi_int string_handle;
gsi_int symbol_handle;
gsi_int integer_handle;
gsi_int float64_handle;
gsi_int logical_handle;
gsi_int long_handle;
gsi_int ulong_handle;

double  float64_dat = 0.0;
gsi_int integer_dat = 0;
gsi_int logical_dat = 0;
char    string_dat[50];
char    symbol_dat[50];
gsi_long i64_dat = -15834758375737492L;
gsi_ulong ui64_dat = 2847283472811119L;
gsi_function_handle_type remote_long_function;
gsi_rpc_receiver_fn_type long_receiver_function;

/* test G2 to GSI RPC call */
void rpc_long_sum_test(gsi_item* rpc_args, gsi_int args_count, gsi_call_identifier_type call_id) {
	gsi_long a,b,c;
	printf("In the rpc_long_sum_test...\n");
	a = long_of(rpc_args[0]);
	b = long_of(rpc_args[1]);
	printf("Arguments: a=%I64d, b=%I64d\n", a, b);
	c = a + b;
	set_long(rpc_args[0], c);
	gsi_rpc_return_values(rpc_args, 1, call_id, gsi_current_context());
	set_long(rpc_args[0], 12345);
	gsi_rpc_call(remote_long_function, rpc_args, gsi_current_context());
}

void long_receiver_function(gsi_item* arguments, gsi_int args_count) {
	printf("Value received from the remote G2 procedure: %I64d\n", long_of(arguments[0]));
}

extern declare_gsi_rpc_receiver_fn(long_receiver_function);

extern declare_gsi_rpc_local_fn(rpc_long_sum_test);

extern declare_gsi_error_handler(my_example_error_handler);

void my_example_error_handler(econtext, ecode, emessage)
    gsi_int  econtext;
    gsi_int  ecode;
    char    *emessage;
{ 
/*
 *  Any behavior desired upon error may be implemnted from this function.
 *  By the time this function is called the error has already been reported to
 *  standard out (unless the message suppression option has been set).  If and
 *  when this function returns, the context in which the error occurred will be
 *  shut down and either control will be passed to within gsi_run_loop(), or 
 *  gsi_run_loop() will return -  depending on whether the program is running 
 *  in continuous or one-cycle modes respectively.
 */
    printf("  Empty error handler \n");
}


void gsi_set_up()
{
/*
 *  Install optional GSI error handler.  This error handler does nothing and
 *  its installation serves only to demonstrate how and when error handlers
 *  are to be installed for GSI.
 */
    gsi_install_error_handler(my_example_error_handler);

/*
 *  Specify Continuous Mode (not GSI_ONE_CYCLE)  which causes the call to
 *  gsi_start() and subsequent calls to gsi_run_loop() to return.
 *
 *  Unless specified otherwise, GSI uses D floats under VAX/VMS, and 
 *  IEEE floats under Alpha/OpenVMS.  In VAX/VMS systems, G floats may
 *  be specified as a run-time option.  In the code below the selection
 *  of floating point format is automated for VMS platforms via the use
 *  of the symbol CC$gfloat.  CC$gfloat is set on VAXen when this file
 *  has been compiled with the /G_FLOAT option.
 */
    gsi_reset_option(GSI_ONE_CYCLE);
#   ifdef vax
#       if CC$gfloat
          gsi_set_option(GSI_USE_GFLOATS);
#       endif
#   endif

/*
 *  Allocate data structures that will be needed to support this program's 
 *  features.  Note, that these are never explicitly reclaimed because they
 *  are needed for the entire life of the process and are implicitly 
 *  reclaimed upon exit of the process.
 */
    my_registered_item_array = gsi_make_registered_items(MAX_REGISTERED_ITEMS_REQUIRED);

/*
 Declare RPC function for G2 Server.
  */
	gsi_rpc_declare_local(rpc_long_sum_test, "RPC-LONG-SUM-TEST");

} /* end gsi_set_up */


gsi_int gsi_get_tcp_port()
{
    return(TCPIP_PORT_NUMBER);
}

gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{
/*
 *  Set pause escape flag if specified.
 */
    if (strcmp(remote_process_init_string,"exit_on_pause") == 0)
        exit_on_pause = TRUE;
    else
        exit_on_pause = FALSE;

    string_handle  = 0;
    symbol_handle  = 0;
    integer_handle = 0;
    float64_handle = 0;
    logical_handle = 0;
    long_handle = 0;
    ulong_handle = 0;
/*
 Declare remote procedure which will be called from this application.
 */

    gsi_rpc_declare_remote(&remote_long_function, "CALLABLE-FROM-GSI", &long_receiver_function, 
		1,1,gsi_current_context() );
    return (GSI_ACCEPT); 
} 
 

void gsi_receive_registration(registration)
    gsi_registration registration;
{
    gsi_attr  identifying_attribute_one = identifying_attr_of(registration,1);
    char     *identifying_attribute_value = str_of(identifying_attribute_one);

/*  Print out the default update interval specified within G2, and then
 *  set up the global indices and value holders in accordance with the type
 *  as specified in the first identifying attribute.
 */
    printf("update interval =  %f\n", interval_of(registration)); 

    if(!strcmp(identifying_attribute_value,"string")) { 
        printf("STRING WAS DEFINED \n"); 
        string_handle = handle_of(registration);
        strcpy(string_dat,"INITIALIZED"); } 
 
    else if(!strcmp(identifying_attribute_value, "symbol"))  { 
        printf("SYMBOL WAS DEFINED \n"); 
        symbol_handle = handle_of(registration); 
        strcpy(symbol_dat,"INITIALIZED"); }
 
    else if(!strcmp(identifying_attribute_value, "float64")) { 
        printf("FLOAT 64 WAS DEFINED \n"); 
        float64_handle = handle_of(registration);  }
 
    else if(!strcmp(identifying_attribute_value, "integer")) { 
        printf("INTEGER WAS DEFINED \n"); 
        integer_handle = handle_of(registration); }
 
    else if(!strcmp(identifying_attribute_value, "logical")) { 
        printf("LOGICAL WAS DEFINED \n"); 
        logical_handle = handle_of(registration); }

    else if(!strcmp(identifying_attribute_value, "long")) { 
        printf("LONG WAS DEFINED \n"); 
        long_handle = handle_of(registration); }

    else if(!strcmp(identifying_attribute_value, "ulong")) { 
        printf("ULONG WAS DEFINED \n"); 
        ulong_handle = handle_of(registration); }

    else
        printf("Error - Invalid type description '%s' found by gsi_register_item().\n",
                     identifying_attribute_value);
 
} /* end gsi_register_item */


void gsi_get_data(registered_item_array, count)
    gsi_registered_item  registered_item_array[];
    gsi_int              count;
{
    long i; 

/*
 *  For each object sent by G2...
 */
    for(i=0; i<count; ++i) {
 
    /*
     *  Set the status to 0 (ok), then use the globals
     *  to set the value in accordance with its type.
     */
        set_status(registered_item_array[i],NO_ERR);

        if(handle_of(registered_item_array[i]) == string_handle) { 
            set_str(registered_item_array[i],string_dat); 
            continue; } 
        if(handle_of(registered_item_array[i]) == symbol_handle) { 
            set_sym(registered_item_array[i],symbol_dat); 
            continue; } 
        if(handle_of(registered_item_array[i]) == float64_handle) { 
            set_flt(registered_item_array[i],float64_dat); 
            printf("get: FLOAT64 = %g\n",flt_of(registered_item_array[i])); 
            continue; }
        if(handle_of(registered_item_array[i]) == integer_handle) { 
            set_int(registered_item_array[i],integer_dat); 
            printf("get: INTEGER = %d\n",int_of(registered_item_array[i])); 
            continue; }
        if(handle_of(registered_item_array[i]) == logical_handle) { 
            set_log(registered_item_array[i],logical_dat); 
            continue; }
        if(handle_of(registered_item_array[i]) == long_handle) { 
            set_long(registered_item_array[i],i64_dat); 
            printf("get: LONG = %I64d\n",long_of(registered_item_array[i])); 
            continue; }
        if(handle_of(registered_item_array[i]) == ulong_handle) { 
            set_ulong(registered_item_array[i],ui64_dat); 
            printf("get: ULONG = %I64u\n",ulong_of(registered_item_array[i])); 
            continue; }

    /*
     *  If an object has an invalid type set type to
     *  return to NULL and set the status to an error code.
     */
        set_type(registered_item_array[i],NULL_TAG); 
        set_status(registered_item_array[i],10);
 
    } /* end for */ 

/*
 *  Send the data back to G2.
 */
    gsi_return_values(registered_item_array, count, current_context); 

} /* end gsi_get_data */


void gsi_set_data(registered_item_array, count)
    gsi_registered_item  registered_item_array[];
    gsi_int              count;
{
    gsi_int i; 
 
/*
 *  For each object sent by G2...
 */
    for(i=0; i<count; ++i) {
 
    /*
     *  Set a global in accordance with its type.
     */
        if(handle_of(registered_item_array[i]) == string_handle) {
            strcpy(string_dat,str_of(registered_item_array[i])); 
            continue; }
        if(handle_of(registered_item_array[i]) == symbol_handle) {
            strcpy(symbol_dat,sym_of(registered_item_array[i])); 
            continue; }
        if(handle_of(registered_item_array[i]) == float64_handle) {
            float64_dat = flt_of(registered_item_array[i]); 
            continue; }
        if(handle_of(registered_item_array[i]) == integer_handle) {
            integer_dat = int_of(registered_item_array[i]); 
            continue; }
        if(handle_of(registered_item_array[i]) == logical_handle) {
            logical_dat = log_of(registered_item_array[i]); 
            continue; }
        if(handle_of(registered_item_array[i]) == long_handle) {
            i64_dat = long_of(registered_item_array[i]); 
            printf("set: LONG = %I64d\n",i64_dat); 
            continue; }
        if(handle_of(registered_item_array[i]) == ulong_handle) {
            ui64_dat = ulong_of(registered_item_array[i]); 
            printf("set: ULONG = %I64u\n",ui64_dat); 
            continue; }

    } /* end for */

} /* end gsi_set_data */


void gsi_pause_context()
{
    if (exit_on_pause)
        exit(0);
}


void gsi_resume_context()
{}

 
void gsi_shutdown_context()
{}


void gsi_g2_poll()
{ 
    gsi_int   count = 0; 

/*
 *  For each value type that has been defined (up to five
 *  types may be defined), add an item to the array to send back.
 */
    if(string_handle) { 
        set_str(my_registered_item_array[count],string_dat); 
        set_status(my_registered_item_array[count],0); 
        set_handle(my_registered_item_array[count],string_handle); 
        count++; } 
    if(symbol_handle) { 
        set_sym(my_registered_item_array[count],symbol_dat); 
        set_status(my_registered_item_array[count],0); 
        set_handle(my_registered_item_array[count],symbol_handle); 
        count++; } 
    if(float64_handle) { 
        set_flt(my_registered_item_array[count],float64_dat); 
        set_status(my_registered_item_array[count],0); 
        set_handle(my_registered_item_array[count],float64_handle); 
        count++; } 
    if(integer_handle) { 
        set_int(my_registered_item_array[count],integer_dat); 
        set_status(my_registered_item_array[count],0); 
        set_handle(my_registered_item_array[count],integer_handle); 
        count++; } 
    if(logical_handle) { 
        set_log(my_registered_item_array[count],logical_dat); 
        set_status(my_registered_item_array[count],0); 
        set_handle(my_registered_item_array[count],logical_handle); 
        count++; } 
 
    if (count) 
        gsi_return_values(my_registered_item_array, count, current_context); 

} /* end gsi_accept_data */
 
 
void gsi_receive_deregistrations(registered_item_array, count)
    gsi_registered_item  registered_item_array[];
    gsi_int              count;
{}


void gsi_receive_message(message, length)
    char     *message;
    gsi_int   length;
{}



