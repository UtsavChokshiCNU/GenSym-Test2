/*******************************************************************************
:
:  item_1.c  --  GSI regression test for G2 to GSI RPCs.
:
:
:
:  Note, no other modules needed other than the GSI library.
:
:.............................................................................*/

/*#define GSI_USE_USER_DATA_FOR_CALLBACKS */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "gsi_main.h"
#include "gsi_misc.h"


#define PRINT_ARG_COUNT_FOR_CALL(FN_NAME) printf ("%s called with %d arguments\n", FN_NAME, (int)count);
#define PRINT_CALL_INDEX_FOR_CALL(FN_NAME) printf ("Call Index for %s = %d\n", FN_NAME, (int)call_index);

#ifdef GSI_USE_USER_DATA_FOR_CALLBACKS
#define USER_DATA(X) (procedure_user_data_type)X,
#define USER_DATA_ARG  procedure_user_data,
#define USER_DATA_ARG_DECL  procedure_user_data_type procedure_user_data;
#define PRINT_USER_DATA(FN_NAME) printf ("User Data for %s = %d\n", FN_NAME, (int)procedure_user_data);
#define PRINT_CALL_ARGUMENTS(FN_NAME) \
        PRINT_USER_DATA(FN_NAME);\
        PRINT_ARG_COUNT_FOR_CALL(FN_NAME);\
        PRINT_CALL_INDEX_FOR_CALL(FN_NAME);
#define CALL_USING_USER_INDEX(N) N,
#else
#define USER_DATA(X)
#define USER_DATA_ARG
#define USER_DATA_ARG_DECL
#define PRINT_USER_DATA(FN_NAME)
#define PRINT_CALL_ARGUMENTS(FN_NAME) \
        PRINT_ARG_COUNT_FOR_CALL(FN_NAME);\
        PRINT_CALL_INDEX_FOR_CALL(FN_NAME);
#define CALL_USING_USER_INDEX(N)
#endif

#ifdef GSI_USE_USER_DATA_FOR_CALLBACKS
#define CALL_INDEX_ARG , call_index
#define CALL_INDEX_ARG_DECL call_identifier_type call_index;
#define PRINT_CALL_INDEX(FN_NAME) printf ("Returned from call# %d to receiver %s.\n", call_index, FN_NAME);
#else
#define CALL_INDEX_ARG
#define PRINT_CALL_INDEX(FN_NAME)
#endif

#define UD_ITEM_COPY               112
#define UD_ITEM_HANDLE             223
#define UD_INITIATE_CNXN           334
#define UD_RSVP                    0
#define UD_FORCE_EXIT              0
#define UD_ITEM_PROC               445
#define UD_UNIQUE_NAMED_ITEM_PROC  556

#define TCPIP_PORT_NUMBER          0
#define TIMEOUT_INTERVAL         360 /* six minutes */
#define ARG_CNT                    1
#define RETURN_ARG_CNT             2
#define INITATE_XN_ARG_COUNT       7
#define INTERNAL_INCONSISTENCY     1
#define SEND                       1
#define NO_SEND                    0
#define NO_DATA              9999999
#define SUCCESS                    1

gsi_int       my_error_variable;
function_handle_type construct, g2_proc_rec_copy_index ,g2_proc_rec_handle_index;
function_handle_type g2_kb_proc_returning_item_index, g2_system_rpc_returning_item_index;
function_handle_type response;
function_handle_type set_result;

gsi_rpc_arg  *mod_arg_array;
gsi_rpc_arg  *my_arg_array;
gsi_rpc_arg  *master_arg_array;
gsi_item      passback_item_copy, passback_item_handle; /* items received as arguments */
gsi_item      received_item_copy, received_item_handle; /* items received as return values */
call_identifier_type call_index_for_item_receiver_to_return;

int           item_copy_received = FALSE, item_handle_received = FALSE;
int           item_is_copy;
void          test_recoverable_error_handling GSI_API_PROTO((gsi_item));

int           outstanding_rpc_calls=0;

extern declare_gsi_rpc_local_fn(gsi_receive_item_copy);
extern declare_gsi_rpc_local_fn(gsi_receive_item_handle);
extern declare_gsi_rpc_local_fn(gsi_call_g2_with_item_copy);
extern declare_gsi_rpc_local_fn(gsi_call_g2_with_item_handle);
extern declare_gsi_rpc_local_fn(gsi_initiate_connection_to_g2);
extern declare_gsi_rpc_local_fn(gsi_initiate_rpc_call_returning_copy);
extern declare_gsi_rpc_local_fn(gsi_initiate_rpc_call_returning_handle);
extern declare_gsi_rpc_local_fn(gsi_initiate_system_rpc_call_returning_copy);
extern declare_gsi_rpc_local_fn(gsi_initiate_system_rpc_call_returning_handle);
extern declare_gsi_rpc_local_fn(gsi_return_received_copy);
extern declare_gsi_rpc_local_fn(gsi_return_received_handle);
extern declare_gsi_rpc_local_fn(rsvp);
extern declare_gsi_rpc_local_fn(force_gsi_exit);
extern declare_gsi_rpc_local_fn(receive_and_return_copy);

extern declare_gsi_rpc_receiver_fn(generic_void_return_receiver);
extern declare_gsi_rpc_receiver_fn(generic_item_return_receiver);
extern declare_gsi_rpc_receiver_fn(construct_return_receiver);

int main(argc, argv)
    int   argc;
    char *argv[];
{
    time_t  time_now;
    time_t  start_time;

/*
 *  Set the version control variables to the values defined in gsi_main.h.
 *  Though optional, this is recommended to ensure version consistency between
 *  the GSI object libraries, and the include files used to compile your 
 *  application code.
 */
#if GSI_INCLUDE_MAJ_VER_NUM > 4L

  gsi_set_include_file_version(GSI_INCLUDE_MAJ_VER_NUM, 
			       GSI_INCLUDE_MIN_VER_NUM,
			       GSI_INCLUDE_REV_VER_NUM);
  GSI_SET_OPTIONS_FROM_COMPILE();

#else

  gsi_include_file_major_version = GSI_INCLUDE_MAJ_VER_NUM;
  gsi_include_file_minor_version = GSI_INCLUDE_MIN_VER_NUM;
  gsi_include_file_revision_version = GSI_INCLUDE_REV_VER_NUM;

#endif

/*
 *  Initialize GSI and enter the event handler loop.
 */
    gsi_start(argc, argv);
    if (gsi_last_error() != 0) 
        return 1;
      
/*
 *  Keep calling the main run loop until timeout is reached.  No regression
 *  test should take more time to complete than that given by timeout interval.
 */
    time(&start_time);
    time(&time_now);
    while (time_now < start_time+TIMEOUT_INTERVAL) {
        gsi_clear_last_error();
        gsi_run_loop();
	gsi_pause();
        time(&time_now);
	if (gsi_last_error() != 0)
	  return 1; 
    } /* end while */

    return 0;

} /* end main */


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
    printf("The error handler was called\n");
}


void gsi_receive_item_copy (USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
    gsi_item gsiitm;
    char g2msg[100];

    printf ("Starting gsi_receive_item_copy.\n");
    PRINT_CALL_ARGUMENTS("gsi_receive_item_copy");
    fflush (stdout);
/*
 *  Check if count matches expected value.
 */
    if (count != ARG_CNT) {
      printf ("#args (%d) != #expected (%d)\n", count, ARG_CNT);
      gsi_signal_error("gsi_receive_item_copy",2000,"count != ARG_CNT");
    }

    gsiitm = arg_array[0];
    if (gsi_is_item (gsiitm)) {
      set_int (my_arg_array[0], SUCCESS);
      sprintf (g2msg, "GSI received a %s named %s.",
	       gsi_class_name_of (gsiitm),
	       gsi_name_of (gsiitm));
      set_str (my_arg_array[1], g2msg);
      gsi_rpc_return_values (my_arg_array, 2, call_index, current_context);
      gsirtl_copy_item_or_value (gsiitm, passback_item_copy);
    } else {
      gsi_signal_error("gsi_receive_item_copy",2000,"unexpected type");
    } /* end if */
    test_recoverable_error_handling (gsiitm);
} /* end gsi_receive_item_copy */


void gsi_receive_item_handle (USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
    gsi_item gsiitm;
    char g2msg[100];
    int handle;

    printf ("Starting gsi_receive_item_handle.\n");
    PRINT_CALL_ARGUMENTS("gsi_receive_item_handle");
    fflush (stdout);
/*
 *  Check if count matches expected value.
 */
    if (count != ARG_CNT)
        gsi_signal_error("gsi_receive_item_handle",2000,"count != ARG_CNT");

    gsiitm = arg_array[0];
    gsirtl_display_item_or_value (gsiitm, 0, 0);
    sprintf (g2msg, "GSI received an object with handle %d.",
	     gsi_handle_of (gsiitm));
    set_str (my_arg_array[1], g2msg);
    gsi_rpc_return_values (my_arg_array, 2, call_index, current_context);
    gsirtl_copy_item_or_value (gsiitm, passback_item_handle);

} /* end gsi_receive_item_handle */


void gsi_call_g2_with_item_copy (USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
    gsi_item gsiitm;
    char g2msg[100];
    int itmindex;

    printf ("Starting gsi_call_g2_with_item_copy.\n");
    PRINT_CALL_ARGUMENTS("gsi_call_g2_with_item_copy");
    fflush (stdout);
/*
 *  Check if count matches expected value.
 */
    if (count != ARG_CNT)
        gsi_signal_error("gsi_call_g2_with_item_copy",2000,"count != ARG_CNT");

    itmindex = gsi_int_of (arg_array[0]);
    if (0 == itmindex) {
      call_identifier_type remote_call_index = outstanding_rpc_calls++;
      my_arg_array[0] = passback_item_copy;
      gsi_rpc_call (g2_proc_rec_copy_index, my_arg_array, CALL_USING_USER_INDEX(remote_call_index) current_context);
      printf ("Called G2-PROCEDURE-RECEIVING-ITEM-COPY -> handle = %d\n", remote_call_index);
    } else
      gsi_signal_error("gsi_call_g2_with_item_copy", 2000, "arg value != 0");
    gsi_rpc_return_values (my_arg_array, 0, call_index, current_context);

} /* end gsi_call_g2_with_item_copy */

void gsi_call_g2_with_item_handle (USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
    gsi_item gsiitm;
    char g2msg[100];
    int itmindex;

    printf ("Starting gsi_call_g2_with_item_handle.\n");
    PRINT_CALL_ARGUMENTS("gsi_call_g2_with_item_handle");
    fflush (stdout);
/*
 *  Check if count matches expected value.
 */
    if (count != ARG_CNT)
        gsi_signal_error("gsi_call_g2_with_item_handle",2000,"count != ARG_CNT");

    itmindex = gsi_int_of (arg_array[0]);
    if (0 == itmindex) {
      call_identifier_type remote_call_index = outstanding_rpc_calls++;
      my_arg_array[0] = passback_item_handle;
      gsi_rpc_call (g2_proc_rec_handle_index, my_arg_array, CALL_USING_USER_INDEX(remote_call_index) current_context);
      printf ("Calling G2-PROCEDURE-RECEIVING-ITEM-HANDLE -> handle = %d.\n", remote_call_index);
    } else
      gsi_signal_error("gsi_call_g2_with_item_handle", 2000, "arg value != 0");
    gsi_rpc_return_values (my_arg_array, 0, call_index, current_context);

} /* end gsi_call_g2_with_item_copy */

void gsi_initiate_connection_to_g2(USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
    char g2msg[100];
    char *interface_name, *class_name, *transport_type,
      *host_name, *port_number, *rpis;
    gsi_int keep_xn_perm_p;

    printf ("Starting gsi_initiate_connection_to_g2.\n");
    PRINT_CALL_ARGUMENTS("gsi_initiate_connection_to_g2");
    fflush (stdout);
/*
 *  Check if count matches expected value.
 */
    if (count != INITATE_XN_ARG_COUNT)
        gsi_signal_error("gsi_call_g2_with_item_handle",2000,"count != INITATE_XN_ARG_CNT");

    interface_name = gsi_str_of (arg_array[0]);
    class_name     = gsi_str_of (arg_array[1]);
    keep_xn_perm_p = gsi_int_of (arg_array[2]);
    transport_type = gsi_str_of (arg_array[3]);
    host_name      = gsi_str_of (arg_array[4]);
    port_number    = gsi_str_of (arg_array[5]);
    rpis           = gsi_str_of (arg_array[6]);

    printf ("Opening Xn type %s to %s at port %s : with a %s named %s and rpis = %s.\n",
	    transport_type, host_name, port_number, class_name,
	    interface_name, rpis);
    gsi_initiate_connection (interface_name, class_name, keep_xn_perm_p,
			     transport_type, host_name, port_number, rpis);
    gsi_rpc_return_values (my_arg_array, 0, call_index, current_context);

} /* end gsi_call_g2_with_item_copy */

void gsi_initiate_rpc_call_returning_copy(USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
  call_identifier_type remote_call_index = outstanding_rpc_calls++;
  
  printf ("Starting gsi_initiate_rpc_call_returning_copy.\n");
  PRINT_CALL_ARGUMENTS("gsi_initiate_rpc_call_returning_copy");
  gsi_set_rpc_remote_return_value_kind (g2_kb_proc_returning_item_index, 0, "COPY");
  gsi_rpc_call (g2_kb_proc_returning_item_index, my_arg_array, CALL_USING_USER_INDEX(remote_call_index) current_context);
  printf ("Calling G2-PROCEDURE-RETURNING-ITEM to get copy -> handle = %d.\n", remote_call_index);
  printf ("gsi_initiate_rpc_call_returning_copy done!\n");
  call_index_for_item_receiver_to_return = call_index;
  item_is_copy = TRUE;
}

void gsi_initiate_rpc_call_returning_handle (USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
  call_identifier_type remote_call_index = outstanding_rpc_calls++;

  printf ("Starting gsi_initiate_rpc_call_returning_handle.\n");
  PRINT_CALL_ARGUMENTS("gsi_initiate_rpc_call_returning_handle");
  fflush (stdout);
  gsi_set_rpc_remote_return_value_kind (g2_kb_proc_returning_item_index, 0, "HANDLE");
  gsi_rpc_call (g2_kb_proc_returning_item_index, my_arg_array, CALL_USING_USER_INDEX(remote_call_index) current_context);
  printf ("Calling G2-PROCEDURE-RETURNING-ITEM to get handle -> handle = %d.\n", remote_call_index);
  printf ("gsi_initiate_rpc_call_returning_handle done!\n");
  call_index_for_item_receiver_to_return = call_index;
  item_is_copy = FALSE;
}

void gsi_return_received_copy(USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
  printf ("Starting gsi_return_received_copy.\n");
  PRINT_CALL_ARGUMENTS("gsi_return_received_copy");
  fflush (stdout);
  if (!item_copy_received)
    printf ("Error in gsi_return_received_copy. Never received COPY.\n");
  else {
    printf ("Returning COPY:\n");
    gsirtl_display_item_or_value (received_item_copy, 0, 0);
    gsi_rpc_return_values (&received_item_copy, 1, call_index, current_context);
    item_copy_received = FALSE;
  }
}


void gsi_return_received_handle(USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
  printf ("Starting gsi_return_received_handle.\n");
  PRINT_CALL_ARGUMENTS("gsi_return_received_handle");
  fflush (stdout);
  if (!item_handle_received)
    printf ("Error in gsi_return_received_handle. Never received HANDLE.\n");
  else {
    printf ("Returning HANDLE:\n");
    gsirtl_display_item_or_value (received_item_handle, 0, 0);
    gsi_rpc_return_values (&received_item_handle, 1, call_index, current_context);
    item_handle_received = FALSE;
  }
}

void gsi_initiate_system_rpc_call_returning_copy(USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
  printf ("Starting gsi_initiate_system_rpc_call_returning_copy.\n");
  PRINT_CALL_ARGUMENTS("gsi_initiate_system_rpc_call_returning_copy");
  gsi_set_rpc_remote_return_value_kind (g2_system_rpc_returning_item_index, 0, "COPY");
  /* gsi_rpc_call (g2_system_rpc_returning_item_index, arg_array, CALL_USING_USER_INDEX(remote_call_index) current_context); */
  /* printf ("Calling G2-API-GET-UNIQUE-NAMED-ITEM to get copy -> handle = %d.\n", remote_call_index); */
  printf ("gsi_initiate_system_rpc_call_returning_copy done!\n");
  call_index_for_item_receiver_to_return = call_index;
  item_is_copy = TRUE;
}

void gsi_initiate_system_rpc_call_returning_handle(USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
  printf ("Starting gsi_initiate_system_rpc_call_returning_handle.\n");
  PRINT_CALL_ARGUMENTS("gsi_initiate_system_rpc_call_returning_handle");
  gsi_set_rpc_remote_return_value_kind (g2_system_rpc_returning_item_index, 0, "HANDLE");
  /* gsi_rpc_call (g2_system_rpc_returning_item_index, arg_array, CALL_USING_USER_INDEX(remote_call_index) current_context); */
  /* printf ("Calling G2-API-GET-UNIQUE-NAMED-ITEM to get handle -> handle = %d.\n", remote_call_index); */
  printf ("gsi_initiate_system_rpc_call_returning_handle done!\n");
  call_index_for_item_receiver_to_return = call_index;
  item_is_copy = FALSE;
}

void rsvp(USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
/*
 *  Check if count matches expected value.
 */
    if (count != ARG_CNT)
        gsi_signal_error("rsvp",2000,"count != ARG_CNT");
    PRINT_CALL_ARGUMENTS("rsvp");

/*
 *  Start remote procedure RESPONSE passing the received arguments unchanged.
 */
    gsi_rpc_start(response,arg_array,current_context);
}

void generic_void_return_receiver(USER_DATA_ARG arg_array, count CALL_INDEX_ARG)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; CALL_INDEX_ARG
{
  printf ("generic_void_return_receiver called.\n");
  PRINT_USER_DATA("generic_void_return_receiver");
  PRINT_CALL_INDEX("generic_void_return_receiver");
  outstanding_rpc_calls--;
}

void generic_item_return_receiver(USER_DATA_ARG arg_array, count CALL_INDEX_ARG)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; CALL_INDEX_ARG
{
  gsi_int type_of_item_returned;

  outstanding_rpc_calls--;
  printf ("generic_item_return_receiver called.\n");
  PRINT_USER_DATA("generic_item_return_receiver");
  PRINT_CALL_INDEX("generic_item_return_receiver");
  if (count != 1) {
    printf ("ERROR: in generic_item_return_receiver. #Arguments = %d, expected = 1.\n", count);
  } else {
    gsi_item rpc_return_value = arg_array[0];
    printf ("Type of item received as return value : %d\n\t", gsi_type_of (rpc_return_value));
    gsirtl_display_item_or_value (rpc_return_value, 0, 0);
    type_of_item_returned = gsi_type_of (rpc_return_value);
    if (item_is_copy) {
      printf ("Saving as copy in received_item_copy\n");
      gsirtl_copy_item_or_value (rpc_return_value, received_item_copy);
      item_copy_received = TRUE;
    } else {
      gsirtl_copy_item_or_value (rpc_return_value, received_item_handle);
      if (GSI_HANDLE_TAG != type_of_item_returned)
	gsi_signal_error ("generic_item_return_receiver", 2020, "Expecting Handle, received Copy?");
      printf ("Saving as handle in received_item_handle\n");
      item_handle_received = TRUE;
    }
  }
    gsi_rpc_return_values (my_arg_array, 0, call_index_for_item_receiver_to_return, current_context);
}

/* This function is called with an item copy.
 * Trying to get a handle from it is an error, but this
 * should not kill GSI.
 */

void test_recoverable_error_handling (itm)
gsi_item itm;
{

  int handle = gsi_handle_of (itm);

  printf ("Error Code: %d\n", my_error_variable);
  printf ("Error Msg : %s\n", (gsi_char*)gsi_last_error_message());
  printf ("ERROR HANDLING TEST DONE!\n");
  gsi_clear_last_error();
}

void construct_return_receiver(USER_DATA_ARG arg_array, count CALL_INDEX_ARG)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; CALL_INDEX_ARG
{
    gsi_int       i;
    gsi_rpc_arg  *result_ptr = gsi_make_rpc_args(1); /* _MUST_ alloc rpc args this way now.  */
    gsi_rpc_arg   result = *result_ptr;

/*
 *  Check if count matches expected value.
 */
    if (count != ARG_CNT)
        gsi_signal_error("construct_return_receiver",2000,"count != ARG_CNT");

/*
 *  Iterate over args, comparing each against its twin in master_arg_array, 
 *  and freeing memory in master_arg_array as I go.

 XXX  I don't see how this frees memory in master_arg_array.  -ncc, 4/26/94

 */
    for (i=0; i<count; i++) {
        if (type_of(arg_array[i]) != type_of(master_arg_array[i]))
            gsi_signal_error("construct_return_receiver",2000,"types don' match");
        switch(type_of(arg_array[i])) {
          case GSI_INTEGER_TAG:
            if (int_of(arg_array[i]) != int_of(master_arg_array[i])) {
                set_log(result,GSI_FALSE);
                gsi_rpc_start(set_result,result_ptr,current_context); }
            break;
          case GSI_FLOAT64_TAG:
            if (flt_of(arg_array[i]) != flt_of(master_arg_array[i])) {
                set_log(result,GSI_FALSE);
                gsi_rpc_start(set_result,result_ptr,current_context); }
            break;
          case GSI_STRING_TAG:
            if (strcmp(str_of(arg_array[i]),str_of(master_arg_array[i])) != 0) {
                set_log(result,GSI_FALSE);
                gsi_rpc_start(set_result,result_ptr,current_context); }
            break;
          case GSI_SYMBOL_TAG:
            if (strcmp(sym_of(arg_array[i]),sym_of(master_arg_array[i])) != 0) {
                set_log(result,GSI_FALSE);
                gsi_rpc_start(set_result,result_ptr,current_context); }
            break;
          case GSI_LOGICAL_TAG:
            if (log_of(arg_array[i]) != log_of(master_arg_array[i])) {
                set_log(result,GSI_FALSE);
                gsi_rpc_start(set_result,result_ptr,current_context); }
            break;
          default:
            gsi_signal_error("construct_return_receiver",2000,"unexpected type");
	} /* end switch */
    } /* end for */

    set_log(result,GSI_TRUE);
    gsi_rpc_start(set_result,result_ptr,current_context);

} /* end construct_return_receiver */

void force_gsi_exit(USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
    exit(0);
}



void receive_and_return_copy(USER_DATA_ARG arg_array, count, call_index)
  USER_DATA_ARG_DECL gsi_rpc_arg arg_array[]; gsi_int count; call_identifier_type call_index;
{
    gsi_item  *duplicate_ptr;
    gsi_item   duplicate;

/*
 *  Allocate memory for a duplicate.
 */
    duplicate_ptr = gsi_make_items(1);
    duplicate = *duplicate_ptr;

/*
 *  Display the entire contents of the argument to standard out.
 *  Items arguments are displayed recursively attribute by attribute.
 */
    printf("\n");
    printf("-------------------------\n");
    printf("  Printing argument\n");
    printf("-------------------------\n");
    gsirtl_display_item_or_value(arg_array[0],STARTING_LEVEL,STANDARD_OUT);
    printf("------------------------- end of argument.\n");

/*
 *  Make the copy.
 */
    gsirtl_copy_item_or_value(arg_array[0],duplicate);

/*
 *  Return the copy to G2, then reclaim the memory.
 */
    gsi_rpc_return_values(duplicate_ptr,1,call_index,current_context);
    gsirtl_free_i_or_v_contents(duplicate);

} /* end receive_and_return_copy */


void gsi_set_up()
{
    long i;
    gsi_item* new_itm_ptr;

/*
 *  Install optional GSI error handler.  This error handler does nothing and
 *  its installation serves only to demonstrate how and when error handlers
 *  are to be installed for GSI.
 */
    gsi_install_error_handler(my_example_error_handler);
    gsi_initialize_error_variable(&my_error_variable);

/*
 *  Specify GSI run-time option GSI_ONE_CYCLE which causes the call to
 *  gsi_start() and subsequent calls to gsi_run_loop() to return.
 *
 *  Unless specified otherwise, GSI uses D floats under VAX/VMS, and 
 *  IEEE floats under Alpha/OpenVMS.  In both VMS systems, G floats may
 *  be specified as a run-time option.  In the code below the selection
 *  of floating point format is automated for VMS platforms via the use
 *  of the symbol CC$gfloat.  CC$gfloat is set on VAXen when this file
 *  has been compiled with the /G_FLOAT option, and is set by default on
 *  Alphas (we have chosen IEEE as the default in all GSI example code).
 */
    gsi_set_option(GSI_ONE_CYCLE);
#   ifdef vms
#       if CC$gfloat
          gsi_set_option(GSI_USE_GFLOATS);
#       endif
#   endif

/*
 *  Declare the local functions called by G2 for this test.
 */
    gsi_clear_last_error();
    gsi_rpc_declare_local(gsi_receive_item_copy, USER_DATA(UD_ITEM_COPY)
			  "GSI-RECEIVE-ITEM-COPY");
    gsi_rpc_declare_local(gsi_receive_item_handle, USER_DATA(UD_ITEM_HANDLE)
			  "GSI-RECEIVE-ITEM-HANDLE");
    gsi_rpc_declare_local(gsi_call_g2_with_item_copy, USER_DATA(UD_ITEM_COPY)
			  "GSI-CALL-G2-WITH-ITEM-COPY");
    gsi_rpc_declare_local(gsi_call_g2_with_item_handle, USER_DATA(UD_ITEM_HANDLE)
			  "GSI-CALL-G2-WITH-ITEM-HANDLE");
    gsi_rpc_declare_local(gsi_initiate_connection_to_g2, USER_DATA(UD_INITIATE_CNXN)
			  "GSI-INITIATE-CONNECTION-TO-G2");
    gsi_rpc_declare_local(gsi_initiate_rpc_call_returning_copy, USER_DATA(UD_ITEM_COPY)
			  "GSI-INITIATE-RPC-CALL-RETURNING-COPY");
    gsi_rpc_declare_local(gsi_initiate_rpc_call_returning_handle, USER_DATA(UD_ITEM_HANDLE)
			  "GSI-INITIATE-RPC-CALL-RETURNING-HANDLE");
    gsi_rpc_declare_local(gsi_initiate_system_rpc_call_returning_copy, USER_DATA(UD_ITEM_COPY)
			  "GSI-INITIATE-SYSTEM-RPC-CALL-RETURNING-COPY");
    gsi_rpc_declare_local(gsi_initiate_system_rpc_call_returning_handle, USER_DATA(UD_ITEM_HANDLE)
			  "GSI-INITIATE-SYSTEM-RPC-CALL-RETURNING-HANDLE");
    gsi_rpc_declare_local(gsi_return_received_copy, USER_DATA(UD_ITEM_COPY)
			  "GSI-RETURN-RECEIVED-COPY");
    gsi_rpc_declare_local(gsi_return_received_handle, USER_DATA(UD_ITEM_HANDLE)
			  "GSI-RETURN-RECEIVED-HANDLE");
    gsi_rpc_declare_local(rsvp, USER_DATA(UD_RSVP) "RSVP");
    gsi_rpc_declare_local(force_gsi_exit,USER_DATA(UD_FORCE_EXIT) "FORCE-GSI-EXIT");
    gsi_rpc_declare_local(receive_and_return_copy, USER_DATA(UD_ITEM_COPY)
			  "RECEIVE-AND-RETURN-ITEM-COPY");

/*
 *  Allocate any data structures that will be needed to support this
 *  program's features.  Note, that these are never explicitly reclaimed
 *  because they are needed for the entire life of the process and are
 *  implicitly reclaimed upon exit of the process.
 */
    my_arg_array = gsi_make_rpc_args(RETURN_ARG_CNT);
    new_itm_ptr = gsi_make_items (1);
    passback_item_copy = *new_itm_ptr;
    new_itm_ptr = gsi_make_items (1);
    passback_item_handle = *new_itm_ptr;
    new_itm_ptr = gsi_make_items (1);
    received_item_copy = *new_itm_ptr;
    new_itm_ptr = gsi_make_items (1);
    received_item_handle = *new_itm_ptr;    
    master_arg_array = gsi_make_rpc_args(ARG_CNT);

} /* end gsi_set_up */

gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{
    gsi_clear_last_error();
    gsi_rpc_declare_remote(&g2_proc_rec_copy_index,
			   "G2-PROCEDURE-RECEIVING-ITEM-COPY",
			   generic_void_return_receiver, USER_DATA(UD_ITEM_COPY)
			   ARG_CNT, ARG_CNT,
			   current_context);
    gsi_rpc_declare_remote(&g2_proc_rec_handle_index,
			   "G2-PROCEDURE-RECEIVING-ITEM-HANDLE",
			   generic_void_return_receiver, USER_DATA(UD_ITEM_HANDLE)
			   ARG_CNT, ARG_CNT,
			   current_context);
    gsi_rpc_declare_remote(&g2_kb_proc_returning_item_index,
			   "G2-PROCEDURE-RETURNING-ITEM",
			   generic_item_return_receiver, USER_DATA(UD_ITEM_PROC)
			   0, 1,
			   current_context);
    gsi_rpc_declare_remote(&g2_system_rpc_returning_item_index,
			   "G2-API-GET-UNIQUE-NAMED-ITEM",
			   generic_item_return_receiver, USER_DATA(UD_UNIQUE_NAMED_ITEM_PROC)
			   2, 1,
			   current_context);

    gsi_rpc_declare_remote(&construct, "CONSTRUCT",
			   construct_return_receiver, USER_DATA(0) ARG_CNT,
			   ARG_CNT,current_context);
    gsi_rpc_declare_remote(&response, "RESPONSE",
			   NULL, USER_DATA(0) ARG_CNT,0,current_context);
    gsi_rpc_declare_remote(&set_result, "SET-RESULT",
			   NULL, USER_DATA(0) 1,0,current_context);

    return(GSI_ACCEPT);
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
{
  printf ("Received registration for %d.\n", gsi_handle_of (registration));
  fflush (stdout);
}

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

void gsi_shutdown_context()
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
