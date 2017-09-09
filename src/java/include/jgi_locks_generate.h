

#ifndef __JGSI_LOCKS__
#define __JGSI_LOCKS__

#include "gsi_main.h"

#define __GENSYM_NOALIAS__


#if defined(__GENSYMKR__) || ! defined(__STDC__)
typedef void *gsi_struct;
#endif

/*--------------------------------------------------------------------------
 *	     Function Prototype declarations for GSI API functions
 *--------------------------------------------------------------------------
 *
 *  Startup, network, and miscellaneous system-level operations.
 */
#if defined(WIN32)
void_fn_with_two_args(HANDLE,char*,jgsi_initialize_for_win32,gsi_initialize_for_win32)
#endif
fn_with_three_args_returning_value(gsi_int,gsi_char*,gsi_char*,gsi_int,jgsi_establish_listener,gsi_establish_listener)
void_fn_with_no_arg(jgsi_close_listeners,gsi_close_listeners)
void_fn_with_one_arg(gsi_int,jgsi_set_context_limit,gsi_set_context_limit)
void_fn_with_one_arg(gsi_int, jgsi_kill_context,gsi_kill_context)
void_fn_with_one_arg(gsi_int,jgsi_set_option,gsi_set_option)
void_fn_with_one_arg(gsi_int,jgsi_reset_option,gsi_reset_option)
fn_with_one_arg_returning_value(gsi_int,gsi_int,jgsi_option_is_set,gsi_option_is_set)
void_fn_with_one_arg(long,jgsi_watch_fd,gsi_watch_fd)
void_fn_with_one_arg(long,jgsi_unwatch_fd,gsi_unwatch_fd)
void_fn_with_one_arg(long,jgsi_watch_fd_for_writing,gsi_watch_fd_for_writing)
void_fn_with_one_arg(long,jgsi_unwatch_fd_for_writing,gsi_unwatch_fd_for_writing)
fn_with_no_arg_returning_value(gsi_int,jgsi_current_context,gsi_current_context)
fn_with_one_arg_returning_value(double,gsi_int,jgsi_context_remote_process_start_time,gsi_context_remote_process_start_time)
fn_with_one_arg_returning_value(gsi_char*,gsi_int,jgsi_context_remote_host,gsi_context_remote_host)
fn_with_one_arg_returning_value(gsi_int,gsi_int,jgsi_context_remote_listener_port,gsi_context_remote_listener_port)
fn_with_one_arg_returning_value(gsi_context_user_data_type,gsi_int,jgsi_context_user_data,gsi_context_user_data)
void_fn_with_two_args(gsi_int,gsi_context_user_data_type,jgsi_set_context_user_data,gsi_set_context_user_data)
void_fn_with_one_arg(gsi_int,jgsi_flush,gsi_flush)
fn_with_no_arg_returning_value(gsi_int,jgsi_wakeup,gsi_wakeup)
void_fn_with_two_args_fn(x,gsi_int,jgsi_watchdog,gsi_watchdog)
fn_with_one_arg_returning_value(gsi_int,gsi_int,jgsi_context_socket,gsi_context_socket)
fn_with_no_arg_returning_value(gsi_int,jgsi_listener_socket,gsi_listener_socket)
fn_with_one_arg_returning_value(gsi_int,gsi_int,jgsi_context_received_data,gsi_context_received_data)
void_fn_with_one_arg(gsi_int,jgsi_set_run_loop_timeout,gsi_set_run_loop_timeout)
void_fn_with_no_arg(jgsi_run_loop,gsi_run_loop)
void_fn_with_one_arg(gsi_int,jgsi_set_pause_timeout,gsi_set_pause_timeout)
void_fn_with_no_arg(jgsi_pause,gsi_pause)
fn_with_seven_args_returning_value(gsi_int,gsi_char*,gsi_char*,gsi_int,gsi_char*,gsi_char*,gsi_char*,gsi_char*,jgsi_initiate_connection,gsi_initiate_connection)
fn_with_eight_args_returning_value(gsi_int,gsi_char*,gsi_char*,gsi_int,gsi_char*,gsi_char*,gsi_char*,gsi_char*,gsi_context_user_data_type,jgsi_initiate_connection_with_user_data,gsi_initiate_connection_with_user_data)


/*
 *  Error handling.
 */
void_fn_with_one_arg(gsi_int*,jgsi_initialize_error_variable,gsi_initialize_error_variable)
fn_with_one_arg_returning_value(gsi_char*,gsi_int,jgsi_error_message,gsi_error_message)
void_fn_with_no_arg(jgsi_clear_last_error,gsi_clear_last_error)
fn_with_no_arg_returning_value(gsi_int,jgsi_last_error,gsi_last_error)
fn_with_no_arg_returning_value(gsi_char*,jgsi_last_error_message,gsi_last_error_message)
fn_with_no_arg_returning_value(gsi_call_identifier_type,jgsi_last_error_call_handle,gsi_last_error_call_handle)
void_fn_with_three_args(gsi_char*,gsi_int,gsi_char*,jgsi_signal_error,gsi_signal_error)
void_fn_with_one_arg(int,jgsi_signal_handler,gsi_signal_handler)


/*
 *  GSI structure allocation and reclamation.
 */
fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_owner_of,gsi_owner_of)
fn_with_one_arg_returning_value(gsi_item*,gsi_int,jgsi_make_array,gsi_make_array)
fn_with_no_arg_returning_value(gsi_item, jgsi_make_item,gsi_make_item)
fn_with_one_arg_returning_value(gsi_item*,gsi_int,jgsi_make_items,gsi_make_items)
fn_with_one_arg_returning_value(gsi_attr*,gsi_int,jgsi_make_attrs,gsi_make_attrs)
fn_with_one_arg_returning_value(gsi_attr*,gsi_int,jgsi_make_attrs_with_items,gsi_make_attrs_with_items)
fn_with_one_arg_returning_value(gsi_registered_item*,gsi_int,jgsi_make_registered_items,gsi_make_registered_items)

void_fn_with_one_arg(gsi_item*,jgsi_reclaim_array,gsi_reclaim_array)
void_fn_with_one_arg(gsi_item,jgsi_reclaim_item,gsi_reclaim_item)
void_fn_with_one_arg(gsi_item*,jgsi_reclaim_items,gsi_reclaim_items)
void_fn_with_one_arg(gsi_attr*,jgsi_reclaim_attrs,gsi_reclaim_attrs)
void_fn_with_one_arg(gsi_attr*,jgsi_reclaim_attrs_with_items,gsi_reclaim_attrs_with_items)
void_fn_with_one_arg(gsi_registered_item*,jgsi_reclaim_registered_items,gsi_reclaim_registered_items)


/*
 * Symbol functions
 */
fn_with_one_arg_returning_value(gsi_symbol,gsi_char*,jgsi_make_symbol,gsi_make_symbol)
fn_with_one_arg_returning_value(gsi_char*,gsi_symbol,jgsi_symbol_name,gsi_symbol_name)
fn_with_one_arg_returning_value(gsi_symbol_user_data_type,gsi_symbol,jgsi_symbol_user_data,gsi_symbol_user_data)
void_fn_with_two_args(gsi_symbol,gsi_symbol_user_data_type,jgsi_set_symbol_user_data,gsi_set_symbol_user_data)


/*
 *  Returning data to G2.
 */
void_fn_with_three_args(gsi_registered_item*,gsi_int,gsi_int,jgsi_return_values,gsi_return_values)
void_fn_with_four_args(gsi_registered_item,gsi_attr*,gsi_int,gsi_int,jgsi_return_attrs,gsi_return_attrs)
void_fn_with_two_args(gsi_char*,gsi_int,jgsi_return_message,gsi_return_message)
void_fn_with_three_args(gsi_registered_item*,gsi_int,gsi_int,jgsi_return_timed_values,gsi_return_timed_values)
void_fn_with_four_args(gsi_registered_item*,gsi_attr*,gsi_int,gsi_int,jgsi_return_timed_attrs,gsi_return_timed_attrs)
fn_with_one_arg_returning_value(gsi_int,gsi_item,jgsi_item_append_flag,gsi_item_append_flag)
void_fn_with_two_args(gsi_item,gsi_int,jgsi_set_item_append_flag,gsi_set_item_append_flag)
fn_with_one_arg_returning_value(gsi_int,gsi_item,jgsi_update_items_in_lists_and_arrays_flag,gsi_update_items_in_lists_and_arrays_flag)
void_fn_with_two_args(gsi_item,gsi_int,jgsi_set_update_items_in_lists_and_arrays_flag,gsi_set_update_items_in_lists_and_arrays_flag)

/*
 *  RPC related operations. Totally incomplete -vkp, 3/10/98
 */
void_fn_with_seven_args(gsi_function_handle_type*,gsi_char*,gsi_rpc_receiver_fn_type*,gsi_procedure_user_data_type,gsi_int,gsi_int,gsi_int,jgsi_rpc_declare_remote,gsi_rpc_declare_remote)
void_fn_with_eight_args(gsi_function_handle_type*,gsi_char*,gsi_rpc_receiver_fn_type*,gsi_rpc_receiver_fn_type*,gsi_procedure_user_data_type,gsi_int,gsi_int,gsi_int,jgsi_rpc_declare_remote_with_error_handler_and_user_data,gsi_rpc_declare_remote_with_error_handler_and_user_data)
void_fn_with_three_args_fn(void*,gsi_procedure_user_data_type, gsi_char*,jgsi_rpc_declare_local,gsi_rpc_declare_local)
void_fn_with_three_args(gsi_function_handle_type,gsi_int,gsi_char*,jgsi_set_rpc_remote_return_value_kind,gsi_set_rpc_remote_return_value_kind)
void_fn_with_three_args(gsi_function_handle_type,gsi_item*,gsi_int,jgsi_rpc_start,gsi_rpc_start)
void_fn_with_four_args(gsi_function_handle_type,gsi_item*,gsi_int,gsi_int,jgsi_rpc_start_with_count,gsi_rpc_start_with_count)

void_fn_with_four_args(gsi_function_handle_type,gsi_item*,gsi_call_identifier_type,gsi_int,jgsi_rpc_call,gsi_rpc_call)
void_fn_with_five_args(gsi_function_handle_type,gsi_item*,gsi_int,gsi_call_identifier_type,gsi_int,jgsi_rpc_call_with_count_and_user_data,gsi_rpc_call_with_count_and_user_data)
void_fn_with_four_args(gsi_item*,gsi_int,gsi_call_identifier_type,gsi_int,jgsi_rpc_return_values,gsi_rpc_return_values)
void_fn_with_four_args(gsi_item*,gsi_int,gsi_call_identifier_type,gsi_int,jgsi_rpc_return_error_values,gsi_rpc_return_error_values)


/*
 *  For accessing the main object array.
 */
fn_with_two_args_returning_value(gsi_registration,gsi_int,gsi_int,jgsi_registration_of_handle,gsi_registration_of_handle)
fn_with_two_args_returning_value(gsi_registration,gsi_int,gsi_int,jgsi_registration_of,gsi_registration_of)
fn_with_one_arg_returning_value(gsi_registration,gsi_struct,jgsi_registration_of_item,gsi_registration_of_item)
fn_with_one_arg_returning_value(gsi_item_user_data_type,gsi_registration,jgsi_user_data_of,gsi_user_data_of)
void_fn_with_two_args(gsi_registration,gsi_item_user_data_type,jgsi_set_user_data,gsi_set_user_data)


/*
 *  For accessing name and class
 *  information from item registrations, 
 *  registered items, items, or attributes.
 */
fn_with_one_arg_returning_value(gsi_symbol,gsi_struct,jgsi_name_of,gsi_name_of)
fn_with_one_arg_returning_value(gsi_symbol,gsi_struct,jgsi_class_name_of,gsi_class_name_of)
void_fn_with_two_args(gsi_item,gsi_symbol,jgsi_set_name,gsi_set_name)
void_fn_with_two_args(gsi_struct,gsi_symbol,jgsi_set_class_name,gsi_set_class_name)


/*
 *  For accessing information unique to item
 *  registrations and/or registered items.
 */
fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_handle_of,gsi_handle_of)
fn_with_one_arg_returning_value(double,gsi_struct,jgsi_interval_of,gsi_interval_of)
fn_with_one_arg_returning_value(gsi_int,gsi_registered_item,jgsi_status_of,gsi_status_of)
fn_with_two_args_returning_value(gsi_attr,gsi_registration,gsi_int,jgsi_identifying_attr_of,gsi_identifying_attr_of)
void_fn_with_two_args(gsi_struct,gsi_int,jgsi_set_handle,gsi_set_handle)
void_fn_with_two_args(gsi_registered_item,gsi_int,jgsi_set_interval,gsi_set_interval)
void_fn_with_two_args(gsi_registered_item,gsi_int,jgsi_set_status,gsi_set_status)


/*
 *  Accessing the value(s) of an item, 
 *  registered item, or attribute.
 */
fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_type_of,gsi_type_of)
void_fn_with_two_args(gsi_struct,gsi_int,jgsi_set_type,gsi_set_type)
fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_int_of,gsi_int_of)
fn_with_one_arg_returning_value(double,gsi_struct,jgsi_flt_of,gsi_flt_of)
fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_log_of,gsi_log_of)
fn_with_one_arg_returning_value(gsi_char*,gsi_struct,jgsi_str_of,gsi_str_of)
fn_with_one_arg_returning_value(gsi_symbol,gsi_struct,jgsi_sym_of,gsi_sym_of)
fn_with_one_arg_returning_value(unsigned short*,gsi_struct,jgsi_usv_of,gsi_usv_of)
/**fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_handle_of,gsi_handle_of)*/
fn_with_one_arg_returning_value(gsi_int*,gsi_struct,jgsi_int_array_of,gsi_int_array_of)
fn_with_one_arg_returning_value(double*,gsi_struct,jgsi_flt_array_of,gsi_flt_array_of)
fn_with_one_arg_returning_value(gsi_int*,gsi_struct,jgsi_log_array_of,gsi_log_array_of)
fn_with_one_arg_returning_value(gsi_symbol*,gsi_struct,jgsi_sym_array_of,gsi_sym_array_of)
fn_with_one_arg_returning_value(gsi_char**,gsi_struct,jgsi_str_array_of,gsi_str_array_of)
fn_with_one_arg_returning_value(gsi_int*,gsi_struct,jgsi_int_list_of,gsi_int_list_of)
fn_with_one_arg_returning_value(double*,gsi_struct,jgsi_flt_list_of,gsi_flt_list_of)
fn_with_one_arg_returning_value(gsi_int*,gsi_struct,jgsi_log_list_of,gsi_log_list_of)
fn_with_one_arg_returning_value(gsi_symbol*,gsi_struct,jgsi_sym_list_of,gsi_sym_list_of)
fn_with_one_arg_returning_value(gsi_char**,gsi_struct,jgsi_str_list_of,gsi_str_list_of)
fn_with_one_arg_returning_value(gsi_item*,gsi_struct,jgsi_elements_of,gsi_elements_of)
void_fn_with_two_args(gsi_struct,gsi_int,jgsi_set_int,gsi_set_int)
void_fn_with_two_args(gsi_struct,double,jgsi_set_flt,gsi_set_flt)
void_fn_with_two_args(gsi_struct,gsi_int,jgsi_set_log,gsi_set_log)
void_fn_with_two_args(gsi_struct,gsi_char*,jgsi_set_str,gsi_set_str)
void_fn_with_two_args(gsi_struct,gsi_symbol,jgsi_set_sym,gsi_set_sym)
/*void_fn_with_two_args(gsi_struct,gsi_int,jgsi_set_handle,gsi_set_handle)*/
void_fn_with_three_args(gsi_struct,gsi_int*,gsi_int,jgsi_set_int_array,gsi_set_int_array)
void_fn_with_three_args(gsi_struct,double*,gsi_int,jgsi_set_flt_array,gsi_set_flt_array)
void_fn_with_three_args(gsi_struct,gsi_int*,gsi_int,jgsi_set_log_array,gsi_set_log_array)
void_fn_with_three_args(gsi_struct,gsi_symbol*,gsi_int,jgsi_set_sym_array,gsi_set_sym_array)
void_fn_with_three_args(gsi_struct,gsi_char**,gsi_int,jgsi_set_str_array,gsi_set_str_array)
void_fn_with_three_args(gsi_struct,gsi_int*,gsi_int,jgsi_set_int_list,gsi_set_int_list)
void_fn_with_three_args(gsi_struct,double*,gsi_int,jgsi_set_flt_list,gsi_set_flt_list)
void_fn_with_three_args(gsi_struct,gsi_int*,gsi_int,jgsi_set_log_list,gsi_set_log_list)
void_fn_with_three_args(gsi_struct,gsi_symbol*,gsi_int,jgsi_set_sym_list,gsi_set_sym_list)
void_fn_with_three_args(gsi_struct,gsi_char**,gsi_int,jgsi_set_str_list,gsi_set_str_list)
void_fn_with_three_args(gsi_struct,unsigned short*,gsi_int,jgsi_set_usv,gsi_set_usv)
void_fn_with_four_args(gsi_struct,gsi_item*,gsi_int,gsi_int,jgsi_set_elements,gsi_set_elements)


/*
 *  For accessing other relevant data common to
 *  items, registered items, and attributes.
 */
fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_class_type_of,gsi_class_type_of)
fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_element_count_of,gsi_element_count_of)
fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_usv_length_of,gsi_usv_length_of)
fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_attr_count_of,gsi_attr_count_of)
fn_with_one_arg_returning_value(gsi_attr*,gsi_struct,jgsi_attrs_of,gsi_attrs_of)
fn_with_two_args_returning_value(gsi_attr*,gsi_struct,gsi_symbol,jgsi_attr_by_name,gsi_attr_by_name)
fn_with_one_arg_returning_value(gsi_int,gsi_struct,jgsi_history_count_of,gsi_history_count_of)
fn_with_four_args_returning_value(gsi_int,gsi_item,void**,double**,gsi_int*,jgsi_extract_history,gsi_extract_history)
fn_with_four_args_returning_value(gsi_int,gsi_item,gsi_int*,gsi_int*,gsi_int*,jgsi_extract_history_spec,gsi_extract_history_spec)
void_fn_with_two_args(gsi_item,gsi_int,jgsi_set_element_count,gsi_set_element_count)
void_fn_with_two_args(gsi_struct,gsi_int,jgsi_set_attr_count,gsi_set_attr_count)
void_fn_with_three_args(gsi_struct,gsi_attr*,gsi_int,jgsi_set_attrs,gsi_set_attrs)
void_fn_with_three_args(gsi_struct,gsi_symbol,gsi_item,jgsi_set_attr_by_name,gsi_set_attr_by_name)
void_fn_with_eight_args(gsi_struct,void*,double*,gsi_int,gsi_int,gsi_int,gsi_int,gsi_int,jgsi_set_history,gsi_set_history)


/*
 *  For accessing data unique to attributes.
 */
fn_with_one_arg_returning_value(gsi_symbol,gsi_attr,jgsi_attr_name_of,gsi_attr_name_of)
fn_with_one_arg_returning_value(gsi_item,gsi_attr,jgsi_item_of_attr,gsi_item_of_attr)
fn_with_one_arg_returning_value(gsi_symbol,gsi_attr,jgsi_unqualified_attr_name_of,gsi_unqualified_attr_name_of)
fn_with_one_arg_returning_value(gsi_symbol,gsi_attr,jgsi_class_qualifier_of,gsi_class_qualifier_of)
fn_with_one_arg_returning_value(gsi_int,gsi_attr,jgsi_attr_name_is_qualified,gsi_attr_name_is_qualified)
void_fn_with_two_args(gsi_attr,gsi_symbol,jgsi_set_attr_name,gsi_set_attr_name)
void_fn_with_two_args(gsi_attr,gsi_item,jgsi_set_item_of_attr,gsi_set_item_of_attr)
void_fn_with_two_args(gsi_attr,gsi_symbol,jgsi_set_unqualified_attr_name,gsi_set_unqualified_attr_name)
void_fn_with_two_args(gsi_attr,gsi_symbol,jgsi_set_class_qualifier,gsi_set_class_qualifier)
fn_with_one_arg_returning_value(gsi_int,gsi_attr,jgsi_attr_is_transient,gsi_attr_is_transient)
void_fn_with_two_args(gsi_attr,gsi_int,jgsi_set_attr_is_transient,gsi_set_attr_is_transient)

/*
 *  For converting between timestamp formats
 */
void_fn_with_seven_args(double,gsi_int*,gsi_int*,gsi_int*,gsi_int*,gsi_int*,gsi_int*,jgsi_decode_timestamp,gsi_decode_timestamp)
fn_with_six_args_returning_value(double,gsi_int,gsi_int,gsi_int,gsi_int,gsi_int,gsi_int,jgsi_encode_timestamp,gsi_encode_timestamp)

/*
 *  Miscellaneous functions
 */
void_fn_with_one_arg(gsi_item,jgsi_clear_item,gsi_clear_item)
fn_with_one_arg_returning_value(gsi_int,gsi_item,jgsi_is_item,gsi_is_item)
fn_with_one_arg_returning_value(gsi_item,gsi_registered_item,jgsi_item_of_registered_item,gsi_item_of_registered_item)
void_fn_with_two_args(gsi_item,gsi_item,jgsi_simple_content_copy,gsi_simple_content_copy)
fn_with_one_arg_returning_value(double,gsi_struct,jgsi_timestamp_of,gsi_timestamp_of)
void_fn_with_two_args(gsi_struct,double,jgsi_set_timestamp,gsi_set_timestamp)

/*
 * GSI Character Set Selection Functions
 */
fn_with_no_arg_returning_value(gsi_int,jgsi_string_conversion_style,gsi_string_conversion_style)
void_fn_with_one_arg(gsi_int,jgsi_set_string_conversion_style,gsi_set_string_conversion_style)

/*
 *  String Conversion Functions
 */
fn_with_two_args_returning_value(short*,char*,gsi_int,jgsi_convert_string_to_unicode,gsi_convert_string_to_unicode)
fn_with_two_args_returning_value(short*,short*,gsi_int,jgsi_convert_wide_string_to_unicode,gsi_convert_wide_string_to_unicode)
fn_with_two_args_returning_value(char*,short*,gsi_int,jgsi_convert_unicode_to_string,gsi_convert_unicode_to_string)
fn_with_two_args_returning_value(short*,short*,gsi_int,jgsi_convert_unicode_to_wide_string,gsi_convert_unicode_to_wide_string)

#define jgsi_attr_by_name        jgsi_item_of_attr_by_name
#define jgsi_set_attr_by_name    jgsi_set_item_of_attr_by_name

#define jgsi_identifying_attr_of jgsi_item_of_identifying_attr_of
#define jgsi_registration_of     jgsi_registration_of

#define jgsi_history_type_of     jgsi_class_type_of

/*--------------------------------------------------------------------------
 *		 Declarations for optional version control                  
 *--------------------------------------------------------------------------*/
void_fn_with_three_args(gsi_int,gsi_int,gsi_int,jgsi_set_include_file_version,gsi_set_include_file_version)

/*
<<<<<<<<<<<<<<<<<<< WARNING WARNING WARNING WARNING WARNING >>>>>>>>>>>>>>>>>>>

Always compile with __GENSYM_NOALIAS__ defined.
These default macros could hurt us.
The safe versions of these macros are defined below.
*/



/*--------------------------------------------------------------------------
 *			Alias and convenience macros
 *--------------------------------------------------------------------------*/
/* 
#define jgsi_make_rpc_args(numargs)     jgsi_make_items(numargs)
#define jgsi_reclaim_rpc_args(numargs)	jgsi_reclaim_items(numargs)
#define is_array_type(type)		(type & 0x00000010)
#define is_list_type(type)		(type & 0x00000020)
#define is_simple_value_type(type)	((type>=GSI_INTEGER_TAG)&&(type<=GSI_FLOAT64_TAG))
#define current_context			jgsi_current_context()
*/

/*--------------------------------------------------------------------------
 *			Backwards compatibility macros
 *--------------------------------------------------------------------------*/
/*
#define value_of(x)	 jgsi_item_of_registered_item(x)
#define set_value(x,y)	 jgsi_simple_content_copy(x,y)
#define obj_of(x)	 x
#define attr_of(x)	 jgsi_item_of_attr(x)
#define set_attr(x,y)	 jgsi_simple_content_copy(x,y)
*/

/*--------------------------------------------------------------------------
 *			 Prefix eliminating macros
 *--------------------------------------------------------------------------*/
/*
#define NULL_TAG		GSI_NULL_TAG
#define INTEGER_TAG		GSI_INTEGER_TAG
#define SYMBOL_TAG		GSI_SYMBOL_TAG
#define STRING_TAG		GSI_STRING_TAG
#define LOGICAL_TAG		GSI_LOGICAL_TAG
#define FLOAT64_TAG		GSI_FLOAT64_TAG
#define ITEM_TAG		GSI_ITEM_TAG
#define VALUE_TAG		GSI_VALUE_TAG
#define HANDLE_TAG		GSI_HANDLE_TAG
#define INTEGER_ARRAY_TAG	GSI_INTEGER_ARRAY_TAG
#define SYMBOL_ARRAY_TAG	GSI_SYMBOL_ARRAY_TAG
#define STRING_ARRAY_TAG	GSI_STRING_ARRAY_TAG
#define LOGICAL_ARRAY_TAG	GSI_LOGICAL_ARRAY_TAG
#define FLOAT64_ARRAY_TAG	GSI_FLOAT64_ARRAY_TAG
#define ITEM_ARRAY_TAG		GSI_ITEM_ARRAY_TAG
#define VALUE_ARRAY_TAG		GSI_VALUE_ARRAY_TAG
#define INTEGER_LIST_TAG	GSI_INTEGER_LIST_TAG
#define SYMBOL_LIST_TAG		GSI_SYMBOL_LIST_TAG
#define STRING_LIST_TAG		GSI_STRING_LIST_TAG
#define LOGICAL_LIST_TAG	GSI_LOGICAL_LIST_TAG
#define FLOAT64_LIST_TAG	GSI_FLOAT64_LIST_TAG
#define ITEM_LIST_TAG		GSI_ITEM_LIST_TAG
#define VALUE_LIST_TAG		GSI_VALUE_LIST_TAG

#define context_socket(c)		  jgsi_context_socket(c)
#define listener_socket()		  jgsi_listener_socket()
#define registration_of(x,y)		  jgsi_registration_of(x,y)
#define user_data_of(x)			  jgsi_user_data_of(x)
#define set_user_data(x,y  )		  jgsi_set_user_data(x,y)
#define handle_of(x)			  jgsi_handle_of(x)
#define interval_of(x)			  jgsi_interval_of(x)
#define status_of(x)			  jgsi_status_of(x)
#define identifying_attr_of(x,y)	  jgsi_identifying_attr_of(x,y)
#define set_handle(x,y)			  jgsi_set_handle(x,y)
#define set_interval(x,y)		  jgsi_set_interval(x,y)
#define set_status(x,y)			  jgsi_set_status(x,y)
#define timestamp_of(x)			  jgsi_timestamp_of(x)
#define int_of(x)			  jgsi_int_of(x)
#define flt_of(x)			  jgsi_flt_of(x)
#define log_of(x)			  jgsi_log_of(x)
#define str_of(x)			  jgsi_str_of(x)
#define sym_of(x)			  jgsi_sym_of(x)
#define handle_of(x)			  jgsi_handle_of(x)
#define int_array_of(x)			  jgsi_int_array_of(x)
#define flt_array_of(x)			  jgsi_flt_array_of(x)
#define log_array_of(x)			  jgsi_log_array_of(x)
#define sym_array_of(x)			  jgsi_sym_array_of(x)
#define str_array_of(x)			  jgsi_str_array_of(x)
#define int_list_of(x)			  jgsi_int_list_of(x)
#define flt_list_of(x)			  jgsi_flt_list_of(x)
#define log_list_of(x)			  jgsi_log_list_of(x)
#define sym_list_of(x)			  jgsi_sym_list_of(x)
#define str_list_of(x)			  jgsi_str_list_of(x)
#define elements_of(x)			  jgsi_elements_of(x)
#define set_timestamp(x,y)		  jgsi_set_timestamp(x,y)
#define set_int(x,y)			  jgsi_set_int(x,y)
#define set_flt(x,y)			  jgsi_set_flt(x,y)
#define set_log(x,y)			  jgsi_set_log(x,y)
#define set_str(x,y)			  jgsi_set_str(x,y)
#define set_sym(x,y)			  jgsi_set_sym(x,y)
#define set_handle(x,y)			  jgsi_set_handle(x,y)
#define set_int_array(x,y,z)		  jgsi_set_int_array(x,y,z)
#define set_flt_array(x,y,z)		  jgsi_set_flt_array(x,y,z)
#define set_log_array(x,y,z)		  jgsi_set_log_array(x,y,z)
#define set_sym_array(x,y,z)		  jgsi_set_sym_array(x,y,z)
#define set_str_array(x,y,z)		  jgsi_set_str_array(x,y,z)
#define set_int_list(x,y,z)		  jgsi_set_int_list(x,y,z)
#define set_flt_list(x,y,z)		  jgsi_set_flt_list(x,y,z)
#define set_log_list(x,y,z)		  jgsi_set_log_list(x,y,z)
#define set_sym_list(x,y,z)		  jgsi_set_sym_list(x,y,z)
#define set_str_list(x,y,z)		  jgsi_set_str_list(x,y,z)
#define set_elements(x,y,z,w)		  jgsi_set_elements(x,y,z,w)
#define type_of(x)			  jgsi_type_of(x)
#define name_of(x)			  jgsi_name_of(x)
#define class_name_of(x)		  jgsi_class_name_of(x)
#define element_count_of(x)		  jgsi_element_count_of(x)
#define attr_count_of(x)		  jgsi_attr_count_of(x)
#define attrs_of(x)			  jgsi_attrs_of(x)
#define attr_by_name(x,y)		  jgsi_attr_by_name(x,y)
#define history_count_of(x)		  jgsi_history_count_of(x)
#define extract_history(w,x,y,z)	  jgsi_extract_history(w,x,y,z)
#define extract_history_spec(w,x,y,z)	  jgsi_extract_history_spec(w,x,y,z)
#define set_type(x,y)			  jgsi_set_type(x,y)
#define set_name(x,y)			  jgsi_set_name(x,y)
#define set_class_name(x,y)		  jgsi_set_class_name(x,y)
#define set_element_count(x,y)		  jgsi_set_element_count(x,y)
#define set_attr_count(x,y)		  jgsi_set_attr_count(x,y)
#define set_attrs(x,y,z)		  jgsi_set_attrs(x,y,z)
#define set_attr_by_name(x,y,z)		  jgsi_set_attr_by_name(x,y,z)
#define set_history(s,t,u,v,w,x,y,z)	  jgsi_set_history(s,t,u,v,w,x,y,z)
#define attr_name_of(x)			  jgsi_attr_name_of(x)
#define item_of_attr(x)			  jgsi_item_of_attr(x)
#define unqualified_attr_name_of(x)	  jgsi_unqualified_attr_name_of(x)
#define class_qualifier_of(x)		  jgsi_class_qualifier_of(x)
#define attr_name_is_qualified(x)	  jgsi_attr_name_is_qualified(x)
#define set_attr_name(x,y)		  jgsi_set_attr_name(x,y)
#define set_item_of_attr(x,y)		  jgsi_set_item_of_attr(x,y)
#define set_unqualified_attr_name(x,y)	  jgsi_set_unqualified_attr_name(x,y)
#define set_class_qualifier(x,y)	  jgsi_set_class_qualifier(x,y)
#define decode_timestamp(t,u,v,w,x,y,z)	  jgsi_decode_timestamp(t,u,v,w,x,y,z)
#define encode_timestamp(u,v,w,x,y,z)	  jgsi_encode_timestamp(u,v,w,x,y,z)
#define is_item(x)			  jgsi_is_item(x)
*/

/*--------------------------------------------------------------------------
 *			     GSI startup macro
 *--------------------------------------------------------------------------

#if !defined(__GENSYMKR__) && defined(__STDC__)
void gsi_version_consistency_check( void );
void gsi_log_command_line( int argc, char *argv[] );
void gsi_initialize_region_increments( void );
void init_top_level( void );
void userinit( void ); 
void launch_gsi( void );
#endif / * !defined(__GENSYMKR__) && defined(__STDC__) * /

#define gsi_start(argc,argv)  gsi_version_consistency_check();	\
			      gsi_log_command_line(argc,argv);	\
			      gsi_initialize_region_increments(); \
			      init_top_level();			\
			      userinit();			\
			      launch_gsi();
#endif / * ifdef GSI_DEFINED * /

*/

#endif /* ifndef __GENSYM_NOALIAS__ */
