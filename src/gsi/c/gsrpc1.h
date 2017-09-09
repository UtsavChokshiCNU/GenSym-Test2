/* gsrpc1.h -- Header File for gsrpc1.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qerror;
extern Object Qreturn;

extern Object Pclos;
extern Object Pclos_run;
extern Object Pclosx;
extern Object Pcl;
extern Object Pcl_user;
extern Object Pkeyword;
extern Object Ptrun;
extern Object Ptx;

/* function declarations */

#ifdef USE_PROTOTYPES

extern Object g2int_build_procedure_identifier_icp_list(Object,Object);
extern Object g2int_c_string_to_gensym_string(Object);
extern Object g2int_c_wide_string_to_text_string(Object);
extern Object g2int_call_gsi_callback(int,...);
extern Object g2int_check_gsi_error_argument_list(Object);
extern Object g2int_convert_gsi_value_to_value(Object);
extern Object g2int_copy_tree_using_gensym_conses_1(Object);
extern Object g2int_current_gsi_application(void);
extern Object g2int_end_icp_message_group(void);
extern Object g2int_establish_new_object_indices_as_required(Object);
extern Object g2int_flush_outgoing_item_list(Object);
extern Object g2int_gensym_cons_1(Object,Object);
extern Object g2int_gensym_list_2(Object,Object);
extern Object g2int_gensym_list_3(Object,Object,Object);
extern Object g2int_get_icp_socket_from_context(Object,Object);
extern Object g2int_gsi_add_new_remote_procedure(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_gsi_call_missing_procedure_handler(Object);
extern Object g2int_gsi_define_new_remote_procedure(Object);
extern Object g2int_gsi_displaced_array_from_c_contents(Object,Object);
extern Object g2int_gsi_error(int,...);
extern Object g2int_gsi_flush_internal_1(Object,Object);
extern Object g2int_gsi_get_item_of_attribute_named(Object,Object);
extern Object g2int_gsi_handle_define_remote_procedure_name(Object);
extern Object g2int_gsi_handle_error_1(Object,Object,Object);
extern Object g2int_gsi_lookup_new_remote_procedure_name(Object);
extern Object g2int_gsi_managed_array_length(Object);
extern Object g2int_gsi_option_is_set_p(Object);
extern Object g2int_gsi_reclaim_displaced_array(Object);
extern Object g2int_gsi_rpc_call_internal(Object,Object,Object,Object,Object);
extern Object g2int_gsi_rpc_return_values_internal(Object,Object,Object,Object);
extern Object g2int_gsi_rpc_start_internal(Object,Object,Object);
extern Object g2int_gsi_start_or_call_local_function_or_handle_return_values(Object,Object,Object,Object);
extern Object g2int_gsi_warning(int,...);
extern Object g2int_icp_connection_being_shutdownqm(Object);
extern Object g2int_icp_connection_open_p(Object);
extern Object g2int_invalid_gsi_context_p(Object,Object);
extern Object g2int_lookup_or_create_gsi_local_function(Object,Object);
extern Object g2int_make_gensym_list_1(Object);
extern Object g2int_make_gsi_local_function_1(void);
extern Object g2int_make_gsi_remote_procedure_1(void);
extern Object g2int_make_outgoing_remote_procedure_identifier_with_info(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_memq_function(Object,Object);
extern Object g2int_protect_gsi_api_call_p(void);
extern Object g2int_reclaim_gensym_list_1(Object);
extern Object g2int_reclaim_gensym_string(Object);
extern Object g2int_reclaim_gensym_tree_1(Object);
extern Object g2int_reclaim_gsi_local_function_1(Object);
extern Object g2int_reclaim_if_text_string_function(Object);
extern Object g2int_reclaim_list_of_local_functions(Object);
extern Object g2int_reclaim_outgoing_remote_procedure_identifier_and_index(Object);
extern Object g2int_send_icp_resumable_rpc_call(Object,Object,Object);
extern Object g2int_send_icp_resumable_rpc_error_to_caller(Object,Object,Object,Object,Object,Object);
extern Object g2int_send_icp_resumable_rpc_return_values(Object,Object);
extern Object g2int_send_icp_resumable_rpc_start(Object,Object);
extern Object g2int_send_icp_rpc_acknowledge_abort(Object);
extern Object g2int_send_icp_rpc_call(Object,Object,Object);
extern Object g2int_send_icp_rpc_error(Object,Object,Object,Object);
extern Object g2int_send_icp_rpc_error_to_caller(Object,Object,Object,Object,Object,Object);
extern Object g2int_send_icp_rpc_return_values(Object,Object);
extern Object g2int_send_icp_rpc_start(Object,Object);
extern Object g2int_send_or_enqueue_icp_write_task(Object,Object,Object,Object,Object,Object);
extern Object g2int_set_gsi_error_message_1(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_symbol_for_gsi_string(Object);
extern Object g2int_symbol_name_text_string(Object);
extern Object g2int_text_string_p(Object);
extern Object g2int_twrite_gsi_rpc_backtrace_info(void);
extern Object g2int_wide_string_to_gensym_string_for_gsi(Object);

#else

extern Object g2int_build_procedure_identifier_icp_list();
extern Object g2int_c_string_to_gensym_string();
extern Object g2int_c_wide_string_to_text_string();
extern Object g2int_call_gsi_callback();
extern Object g2int_check_gsi_error_argument_list();
extern Object g2int_convert_gsi_value_to_value();
extern Object g2int_copy_tree_using_gensym_conses_1();
extern Object g2int_current_gsi_application();
extern Object g2int_end_icp_message_group();
extern Object g2int_establish_new_object_indices_as_required();
extern Object g2int_flush_outgoing_item_list();
extern Object g2int_gensym_cons_1();
extern Object g2int_gensym_list_2();
extern Object g2int_gensym_list_3();
extern Object g2int_get_icp_socket_from_context();
extern Object g2int_gsi_add_new_remote_procedure();
extern Object g2int_gsi_call_missing_procedure_handler();
extern Object g2int_gsi_define_new_remote_procedure();
extern Object g2int_gsi_displaced_array_from_c_contents();
extern Object g2int_gsi_error();
extern Object g2int_gsi_flush_internal_1();
extern Object g2int_gsi_get_item_of_attribute_named();
extern Object g2int_gsi_handle_define_remote_procedure_name();
extern Object g2int_gsi_handle_error_1();
extern Object g2int_gsi_lookup_new_remote_procedure_name();
extern Object g2int_gsi_managed_array_length();
extern Object g2int_gsi_option_is_set_p();
extern Object g2int_gsi_reclaim_displaced_array();
extern Object g2int_gsi_rpc_call_internal();
extern Object g2int_gsi_rpc_return_values_internal();
extern Object g2int_gsi_rpc_start_internal();
extern Object g2int_gsi_start_or_call_local_function_or_handle_return_values();
extern Object g2int_gsi_warning();
extern Object g2int_icp_connection_being_shutdownqm();
extern Object g2int_icp_connection_open_p();
extern Object g2int_invalid_gsi_context_p();
extern Object g2int_lookup_or_create_gsi_local_function();
extern Object g2int_make_gensym_list_1();
extern Object g2int_make_gsi_local_function_1();
extern Object g2int_make_gsi_remote_procedure_1();
extern Object g2int_make_outgoing_remote_procedure_identifier_with_info();
extern Object g2int_memq_function();
extern Object g2int_protect_gsi_api_call_p();
extern Object g2int_reclaim_gensym_list_1();
extern Object g2int_reclaim_gensym_string();
extern Object g2int_reclaim_gensym_tree_1();
extern Object g2int_reclaim_gsi_local_function_1();
extern Object g2int_reclaim_if_text_string_function();
extern Object g2int_reclaim_list_of_local_functions();
extern Object g2int_reclaim_outgoing_remote_procedure_identifier_and_index();
extern Object g2int_send_icp_resumable_rpc_call();
extern Object g2int_send_icp_resumable_rpc_error_to_caller();
extern Object g2int_send_icp_resumable_rpc_return_values();
extern Object g2int_send_icp_resumable_rpc_start();
extern Object g2int_send_icp_rpc_acknowledge_abort();
extern Object g2int_send_icp_rpc_call();
extern Object g2int_send_icp_rpc_error();
extern Object g2int_send_icp_rpc_error_to_caller();
extern Object g2int_send_icp_rpc_return_values();
extern Object g2int_send_icp_rpc_start();
extern Object g2int_send_or_enqueue_icp_write_task();
extern Object g2int_set_gsi_error_message_1();
extern Object g2int_symbol_for_gsi_string();
extern Object g2int_symbol_name_text_string();
extern Object g2int_text_string_p();
extern Object g2int_twrite_gsi_rpc_backtrace_info();
extern Object g2int_wide_string_to_gensym_string_for_gsi();

#endif

/* Externally callable routines */

#ifdef USE_PROTOTYPES

extern Object g2int_shared_gsi_rpc_call(Object,Object,SI_Long);
extern Object g2int_shared_gsi_rpc_call_with_count(Object,Object,SI_Long,SI_Long);
extern Object g2int_shared_gsi_rpc_call_with_count_u_d(Object,Object,SI_Long,Object,SI_Long);
extern Object g2int_shared_gsi_rpc_call_with_u_d(Object,Object,Object,SI_Long);
extern void g2int_shared_gsi_rpc_declare_local_plain(Object,Object,Object);
extern void g2int_shared_gsi_rpc_declare_local_w_u_d(Object,Object,Object,Object);
extern void g2int_shared_gsi_rpc_declare_remote_plain(Object,Object,Object,Object,SI_Long,SI_Long,SI_Long);
extern void g2int_shared_gsi_rpc_declare_remote_w_e_u_d(Object,Object,Object,Object,Object,Object,SI_Long,SI_Long,SI_Long);
extern void g2int_shared_gsi_rpc_declare_remote_w_u_d(Object,Object,Object,Object,Object,SI_Long,SI_Long,SI_Long);
extern void g2int_shared_gsi_rpc_return_error_values(Object,SI_Long,Object,SI_Long);
extern void g2int_shared_gsi_rpc_return_values(Object,SI_Long,Object,SI_Long);
extern void g2int_shared_gsi_rpc_start(Object,Object,SI_Long);
extern void g2int_shared_gsi_rpc_start_with_count(Object,Object,SI_Long,SI_Long);
extern void g2int_shared_gsi_set_rpc_remote_r_i_a_s_a_e(Object,Object);
extern void g2int_shared_gsi_set_rpc_remote_return_e_u_a(Object,Object);
extern void g2int_shared_gsi_set_rpc_remote_return_i_s_a(Object,Object);
extern void g2int_shared_gsi_set_rpc_remote_return_v_k(Object,Object,SI_Long,Object);
DLLEXPORT extern Object gsi_rpc_call(Object,Object,SI_Long);
DLLEXPORT extern Object gsi_rpc_call_with_count(Object,Object,SI_Long,SI_Long);
DLLEXPORT extern Object gsi_rpc_call_with_count_u_d(Object,Object,SI_Long,Object,SI_Long);
DLLEXPORT extern Object gsi_rpc_call_with_u_d(Object,Object,Object,SI_Long);
DLLEXPORT extern void gsi_rpc_declare_local_plain(Object,Object);
DLLEXPORT extern void gsi_rpc_declare_local_w_u_d(Object,Object,Object);
DLLEXPORT extern void gsi_rpc_declare_remote_plain(Object,Object,Object,SI_Long,SI_Long,SI_Long);
DLLEXPORT extern void gsi_rpc_declare_remote_w_e_u_d(Object,Object,Object,Object,Object,SI_Long,SI_Long,SI_Long);
DLLEXPORT extern void gsi_rpc_declare_remote_w_u_d(Object,Object,Object,Object,SI_Long,SI_Long,SI_Long);
DLLEXPORT extern void gsi_rpc_return_error_values(Object,SI_Long,Object,SI_Long);
DLLEXPORT extern void gsi_rpc_return_values(Object,SI_Long,Object,SI_Long);
DLLEXPORT extern void gsi_rpc_start(Object,Object,SI_Long);
DLLEXPORT extern void gsi_rpc_start_with_count(Object,Object,SI_Long,SI_Long);
DLLEXPORT extern void gsi_set_rpc_remote_r_i_a_s_a_e(Object,Object);
DLLEXPORT extern void gsi_set_rpc_remote_return_e_u_a(Object,Object);
DLLEXPORT extern void gsi_set_rpc_remote_return_i_s_a(Object,Object);
DLLEXPORT extern void gsi_set_rpc_remote_return_v_k(Object,SI_Long,Object);

#else

extern Object g2int_shared_gsi_rpc_call();
extern Object g2int_shared_gsi_rpc_call_with_count();
extern Object g2int_shared_gsi_rpc_call_with_count_u_d();
extern Object g2int_shared_gsi_rpc_call_with_u_d();
extern void g2int_shared_gsi_rpc_declare_local_plain();
extern void g2int_shared_gsi_rpc_declare_local_w_u_d();
extern void g2int_shared_gsi_rpc_declare_remote_plain();
extern void g2int_shared_gsi_rpc_declare_remote_w_e_u_d();
extern void g2int_shared_gsi_rpc_declare_remote_w_u_d();
extern void g2int_shared_gsi_rpc_return_error_values();
extern void g2int_shared_gsi_rpc_return_values();
extern void g2int_shared_gsi_rpc_start();
extern void g2int_shared_gsi_rpc_start_with_count();
extern void g2int_shared_gsi_set_rpc_remote_r_i_a_s_a_e();
extern void g2int_shared_gsi_set_rpc_remote_return_e_u_a();
extern void g2int_shared_gsi_set_rpc_remote_return_i_s_a();
extern void g2int_shared_gsi_set_rpc_remote_return_v_k();
DLLEXPORT extern Object gsi_rpc_call();
DLLEXPORT extern Object gsi_rpc_call_with_count();
DLLEXPORT extern Object gsi_rpc_call_with_count_u_d();
DLLEXPORT extern Object gsi_rpc_call_with_u_d();
DLLEXPORT extern void gsi_rpc_declare_local_plain();
DLLEXPORT extern void gsi_rpc_declare_local_w_u_d();
DLLEXPORT extern void gsi_rpc_declare_remote_plain();
DLLEXPORT extern void gsi_rpc_declare_remote_w_e_u_d();
DLLEXPORT extern void gsi_rpc_declare_remote_w_u_d();
DLLEXPORT extern void gsi_rpc_return_error_values();
DLLEXPORT extern void gsi_rpc_return_values();
DLLEXPORT extern void gsi_rpc_start();
DLLEXPORT extern void gsi_rpc_start_with_count();
DLLEXPORT extern void gsi_set_rpc_remote_r_i_a_s_a_e();
DLLEXPORT extern void gsi_set_rpc_remote_return_e_u_a();
DLLEXPORT extern void gsi_set_rpc_remote_return_i_s_a();
DLLEXPORT extern void gsi_set_rpc_remote_return_v_k();

#endif

/* variables/constants */
extern Object G2int_abort_level_0_tag;
extern Object G2int_available_gensym_conses;
extern Object G2int_backtrace_stack_for_internal_error;
extern Object G2int_current_icp_buffer;
extern Object G2int_current_icp_port;
extern Object G2int_current_icp_socket;
extern Object G2int_current_invocation_remotely_started_p;
extern Object G2int_current_remote_procedure_identifier;
extern Object G2int_current_write_icp_byte_position;
extern Object G2int_disable_resumability;
#define G2int_gsi_bad_magic_number FIX((SI_Long)23L)
#define G2int_gsi_bad_rpc_state FIX((SI_Long)65L)
#define G2int_gsi_illegal_error_arguments FIX((SI_Long)80L)
#define G2int_gsi_incompatible_type FIX((SI_Long)16L)
#define G2int_gsi_integer_too_large FIX((SI_Long)81L)
#define G2int_gsi_integer_too_small FIX((SI_Long)82L)
#define G2int_gsi_invalid_call_handle FIX((SI_Long)18L)
#define G2int_gsi_invalid_return_value_index FIX((SI_Long)75L)
#define G2int_gsi_invalid_return_value_kind FIX((SI_Long)76L)
#define G2int_gsi_local_function_undefined FIX((SI_Long)17L)
#define G2int_gsi_magic_offset FIX((SI_Long)1L)
#define G2int_gsi_malformed_socket FIX((SI_Long)66L)
#define G2int_gsi_missing_procedure_handler FIX((SI_Long)18L)
extern Object G2int_gsi_most_recent_error_remote_procedure_identifier;
#define G2int_gsi_remote_declaration_not_found FIX((SI_Long)19L)
#define G2int_gsi_rpc_error_from_g2_procedure FIX((SI_Long)35L)
#define G2int_gsi_run_state_change FIX((SI_Long)16L)
#define G2int_gsi_run_state_direction_entering_gsi FIX((SI_Long)1L)
#define G2int_gsi_run_state_direction_leaving_gsi FIX((SI_Long)2L)
#define G2int_gsi_run_state_type_api FIX((SI_Long)1L)
#define G2int_gsi_run_state_type_callback FIX((SI_Long)2L)
#define G2int_gsi_symbol_type_tag FIX((SI_Long)3L)
#define G2int_gsi_user_data_for_callbacks FIX((SI_Long)7L)
extern Object G2int_gsi_wide_api_p;
extern Object G2int_icp_buffer_of_start_of_message_seriesqm;
extern Object G2int_icp_buffers_for_message_group;
extern Object G2int_icp_byte_position_of_start_of_message_seriesqm;
extern Object G2int_in_recursive_gsi_context;
extern Object G2int_in_unprotected_gsi_api_call_p;
extern Object G2int_index_of_top_of_backtrace_stack;
extern Object G2int_maximum_index_in_backtrace_stack_for_internal_error;
extern Object G2int_number_of_icp_bytes_for_message_series;
extern Object G2int_number_of_icp_bytes_in_message_group;
extern Object G2int_number_of_icp_bytes_to_fill_buffer;
extern Object G2int_resumable_priority_of_gsi_rpc_service;
extern Object G2int_shutdown_catch_tag;
#define G2int_size_of_basic_backtrace_information FIX((SI_Long)3L)
extern Object G2int_top_level_error_catcher_tag;
extern Object G2int_use_new_message_group_for_send_icp_enlarge_index_space_p;
extern Object G2int_writing_icp_message_group;
