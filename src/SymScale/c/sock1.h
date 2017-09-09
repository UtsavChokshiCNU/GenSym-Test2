/* sock1.h -- Header File for sock1.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qerror;
extern Object Qsequence;

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

extern Object add_buffer_to_socket(Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_empty_evaluation_sequence(Object);
extern Object bytes_per_simple_vector(Object);
extern Object c_get_peer_address_string(Object,Object,Object);
extern Object c_get_peer_hostname(Object,Object,Object);
extern Object c_network_write_string(Object,Object,Object,Object);
extern Object cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object clear_optimized_constants(void);
extern Object close_socket(int,...);
extern Object connect_socket(Object,Object,Object,Object);
extern Object constant_queue_push_right(Object,Object);
extern Object copy_evaluation_sequence_elements(Object,Object,Object,Object,Object);
extern Object copy_foreign_string_arg_if_appropriate(Object);
extern Object copy_null_terminated_string_as_text_string(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text_string(Object);
extern Object data_available_p(Object);
extern Object direct_structure_method(Object,Object);
extern Object enqueue_tcp_cleanups(Object);
extern Object evaluation_sequence_aref(Object,Object);
extern Object extend_current_gensym_string(int,...);
extern Object getfq_function_no_default(Object,Object);
extern Object handle_network_accept_internals(Object,Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object make_permanent_socket_output_buffer_structure_internal(void);
extern Object make_permanent_tcp_socket_structure_internal(void);
extern Object make_socket_output_buffer_1(void);
extern Object make_tcp_socket_1(void);
extern Object make_thread_array(Object);
extern Object make_variable_fill_icp_buffer(void);
extern Object maybe_read_buffer_from_socket(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object network_connect(int,...);
extern Object network_peer_address_string(Object);
extern Object network_peer_name(Object);
extern Object notify_user_at_console(int,...);
extern Object obtain_simple_gensym_string_of_quantized_length(Object);
extern Object outstanding_socket_output_buffer_count(void);
extern Object outstanding_tcp_socket_count(void);
extern Object peek_socket(Object);
extern Object push_optimized_constant(Object);
extern Object read_buffer_from_socket(Object);
extern Object read_byte_from_socket(Object);
extern Object read_from_socket(Object);
extern Object read_from_socket_until_char(Object,Object);
extern Object read_n_chars_from_socket(Object,Object);
extern Object reclaim_evaluation_sequence(Object);
extern Object reclaim_gensym_string(Object);
extern Object reclaim_if_socket_buffer(Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_socket_buffer_data(Object);
extern Object reclaim_socket_output_buffer_1(Object);
extern Object reclaim_tcp_socket_1(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_variable_fill_icp_buffer(Object);
extern Object reclaim_wide_string(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object register_socket_to_handle(Object,Object);
extern Object socket_close_cleanups(Object);
extern Object socket_output_buffer_structure_memory_usage(void);
extern Object tcp_socket_structure_memory_usage(void);
extern Object text_string_length(Object);
extern Object tformat_gensym_string(int,...);
extern Object try_to_send_socket_buffer(Object);
extern Object try_to_send_socket_sequence(Object);
extern Object twrite_wide_character(Object);
extern Object update_object_pool_meters_list(Object);
extern Object write_bytes_to_socket(Object,Object);
extern Object write_to_socket(Object,Object);

#else

extern Object add_buffer_to_socket();
extern Object allocate_byte_vector_16();
extern Object allocate_empty_evaluation_sequence();
extern Object bytes_per_simple_vector();
extern Object c_get_peer_address_string();
extern Object c_get_peer_hostname();
extern Object c_network_write_string();
extern Object cancel_and_reclaim_scheduled_queue_element_1();
extern Object clear_optimized_constants();
extern Object close_socket();
extern Object connect_socket();
extern Object constant_queue_push_right();
extern Object copy_evaluation_sequence_elements();
extern Object copy_foreign_string_arg_if_appropriate();
extern Object copy_null_terminated_string_as_text_string();
extern Object copy_out_current_wide_string();
extern Object copy_text_string();
extern Object data_available_p();
extern Object direct_structure_method();
extern Object enqueue_tcp_cleanups();
extern Object evaluation_sequence_aref();
extern Object extend_current_gensym_string();
extern Object getfq_function_no_default();
extern Object handle_network_accept_internals();
extern Object load_and_initialize_type_description();
extern Object make_permanent_schedule_task_structure_internal();
extern Object make_permanent_socket_output_buffer_structure_internal();
extern Object make_permanent_tcp_socket_structure_internal();
extern Object make_socket_output_buffer_1();
extern Object make_tcp_socket_1();
extern Object make_thread_array();
extern Object make_variable_fill_icp_buffer();
extern Object maybe_read_buffer_from_socket();
extern Object mutate_global_property();
extern Object network_connect();
extern Object network_peer_address_string();
extern Object network_peer_name();
extern Object notify_user_at_console();
extern Object obtain_simple_gensym_string_of_quantized_length();
extern Object outstanding_socket_output_buffer_count();
extern Object outstanding_tcp_socket_count();
extern Object peek_socket();
extern Object push_optimized_constant();
extern Object read_buffer_from_socket();
extern Object read_byte_from_socket();
extern Object read_from_socket();
extern Object read_from_socket_until_char();
extern Object read_n_chars_from_socket();
extern Object reclaim_evaluation_sequence();
extern Object reclaim_gensym_string();
extern Object reclaim_if_socket_buffer();
extern Object reclaim_schedule_task_args();
extern Object reclaim_socket_buffer_data();
extern Object reclaim_socket_output_buffer_1();
extern Object reclaim_tcp_socket_1();
extern Object reclaim_text_string();
extern Object reclaim_variable_fill_icp_buffer();
extern Object reclaim_wide_string();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object register_socket_to_handle();
extern Object socket_close_cleanups();
extern Object socket_output_buffer_structure_memory_usage();
extern Object tcp_socket_structure_memory_usage();
extern Object text_string_length();
extern Object tformat_gensym_string();
extern Object try_to_send_socket_buffer();
extern Object try_to_send_socket_sequence();
extern Object twrite_wide_character();
extern Object update_object_pool_meters_list();
extern Object write_bytes_to_socket();
extern Object write_to_socket();

#endif

/* variables/constants */
extern Object Chain_of_available_schedule_tasks_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_socket_output_buffers, Qchain_of_available_socket_output_buffers);
extern Object Chain_of_available_socket_output_buffers_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_tcp_sockets, Qchain_of_available_tcp_sockets);
extern Object Chain_of_available_tcp_sockets_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_g2_time, Qcurrent_g2_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_gensym_string, Qcurrent_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_real_time, Qcurrent_real_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_schedule_task, Qcurrent_schedule_task);
extern Object Current_task_queue_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
extern Object Deferred_task_queue_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_gensym_string, Qfill_pointer_for_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
#define Ne_blocked_value FIX((SI_Long)0L)
#define Ne_eof_value FIX((SI_Long)-1L)
#define Ne_error_value FIX((SI_Long)-2L)
extern Object Network_status_success;
DECLARE_VARIABLE_WITH_SYMBOL(Priority_of_next_task, Qpriority_of_next_task);
DECLARE_VARIABLE_WITH_SYMBOL(Socket_output_buffer_count, Qsocket_output_buffer_count);
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
DECLARE_VARIABLE_WITH_SYMBOL(Tcp_socket_count, Qtcp_socket_count);
extern Object The_type_description_of_socket_output_buffer;
extern Object The_type_description_of_tcp_socket;
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_gensym_string, Qtotal_length_of_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
