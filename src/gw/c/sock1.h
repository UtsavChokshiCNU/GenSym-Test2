/* sock1.h -- Header File for sock1.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qerror;

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

extern Object g2int_add_buffer_to_socket(Object,Object);
extern Object g2int_allocate_byte_vector_16(Object);
extern Object g2int_c_get_peer_address_string(Object,Object,Object);
extern Object g2int_c_get_peer_hostname(Object,Object,Object);
extern Object g2int_c_network_write_string(Object,Object,Object,Object);
extern Object g2int_cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object g2int_close_socket(int,...);
extern Object g2int_connect_socket(Object,Object,Object,Object);
extern Object g2int_copy_foreign_string_arg_if_appropriate(Object);
extern Object g2int_copy_null_terminated_string_as_text_string(Object);
extern Object g2int_copy_out_current_wide_string(void);
extern Object g2int_copy_text_string(Object);
extern Object g2int_data_available_p(Object);
extern Object g2int_direct_structure_method(Object,Object);
extern Object g2int_enqueue_tcp_cleanups(Object);
extern Object g2int_extend_current_gensym_string(int,...);
extern Object g2int_getfq_function_no_default(Object,Object);
extern Object g2int_handle_network_accept_internals(Object,Object,Object);
extern Object g2int_load_and_initialize_type_description(Object,Object);
extern Object g2int_make_permanent_queue_element_structure_internal(void);
extern Object g2int_make_permanent_schedule_task_structure_internal(void);
extern Object g2int_make_permanent_socket_output_buffer_structure_internal(void);
extern Object g2int_make_permanent_tcp_socket_structure_internal(void);
extern Object g2int_make_socket_output_buffer_1(void);
extern Object g2int_make_tcp_socket_1(void);
extern Object g2int_make_variable_fill_icp_buffer(void);
extern Object g2int_maybe_read_buffer_from_socket(Object);
extern Object g2int_mutate_global_property(Object,Object,Object);
extern Object g2int_network_connect(int,...);
extern Object g2int_network_peer_address_string(Object);
extern Object g2int_network_peer_name(Object);
extern Object g2int_notify_user_at_console(int,...);
extern Object g2int_obtain_simple_gensym_string_of_quantized_length(Object);
extern Object g2int_peek_socket(Object);
extern Object g2int_read_buffer_from_socket(Object);
extern Object g2int_read_byte_from_socket(Object);
extern Object g2int_read_from_socket(Object);
extern Object g2int_read_from_socket_until_char(Object,Object);
extern Object g2int_read_n_chars_from_socket(Object,Object);
extern Object g2int_reclaim_gensym_string(Object);
extern Object g2int_reclaim_if_socket_buffer(Object);
extern Object g2int_reclaim_schedule_task_args(Object);
extern Object g2int_reclaim_socket_buffer_data(Object);
extern Object g2int_reclaim_socket_output_buffer_1(Object);
extern Object g2int_reclaim_tcp_socket_1(Object);
extern Object g2int_reclaim_text_string(Object);
extern Object g2int_reclaim_variable_fill_icp_buffer(Object);
extern Object g2int_reclaim_wide_string(Object);
extern Object g2int_record_direct_structure_method(Object,Object,Object);
extern Object g2int_record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_regenerate_optimized_constant(Object);
extern Object g2int_register_socket_to_handle(Object,Object);
extern Object g2int_socket_close_cleanups(Object);
extern Object g2int_text_string_length(Object);
extern Object g2int_tformat_gensym_string(int,...);
extern Object g2int_try_to_send_socket_buffer(Object);
extern Object g2int_twrite_wide_character(Object);
extern Object g2int_write_to_socket(Object,Object);

#else

extern Object g2int_add_buffer_to_socket();
extern Object g2int_allocate_byte_vector_16();
extern Object g2int_c_get_peer_address_string();
extern Object g2int_c_get_peer_hostname();
extern Object g2int_c_network_write_string();
extern Object g2int_cancel_and_reclaim_scheduled_queue_element_1();
extern Object g2int_close_socket();
extern Object g2int_connect_socket();
extern Object g2int_copy_foreign_string_arg_if_appropriate();
extern Object g2int_copy_null_terminated_string_as_text_string();
extern Object g2int_copy_out_current_wide_string();
extern Object g2int_copy_text_string();
extern Object g2int_data_available_p();
extern Object g2int_direct_structure_method();
extern Object g2int_enqueue_tcp_cleanups();
extern Object g2int_extend_current_gensym_string();
extern Object g2int_getfq_function_no_default();
extern Object g2int_handle_network_accept_internals();
extern Object g2int_load_and_initialize_type_description();
extern Object g2int_make_permanent_queue_element_structure_internal();
extern Object g2int_make_permanent_schedule_task_structure_internal();
extern Object g2int_make_permanent_socket_output_buffer_structure_internal();
extern Object g2int_make_permanent_tcp_socket_structure_internal();
extern Object g2int_make_socket_output_buffer_1();
extern Object g2int_make_tcp_socket_1();
extern Object g2int_make_variable_fill_icp_buffer();
extern Object g2int_maybe_read_buffer_from_socket();
extern Object g2int_mutate_global_property();
extern Object g2int_network_connect();
extern Object g2int_network_peer_address_string();
extern Object g2int_network_peer_name();
extern Object g2int_notify_user_at_console();
extern Object g2int_obtain_simple_gensym_string_of_quantized_length();
extern Object g2int_peek_socket();
extern Object g2int_read_buffer_from_socket();
extern Object g2int_read_byte_from_socket();
extern Object g2int_read_from_socket();
extern Object g2int_read_from_socket_until_char();
extern Object g2int_read_n_chars_from_socket();
extern Object g2int_reclaim_gensym_string();
extern Object g2int_reclaim_if_socket_buffer();
extern Object g2int_reclaim_schedule_task_args();
extern Object g2int_reclaim_socket_buffer_data();
extern Object g2int_reclaim_socket_output_buffer_1();
extern Object g2int_reclaim_tcp_socket_1();
extern Object g2int_reclaim_text_string();
extern Object g2int_reclaim_variable_fill_icp_buffer();
extern Object g2int_reclaim_wide_string();
extern Object g2int_record_direct_structure_method();
extern Object g2int_record_system_variable();
extern Object g2int_regenerate_optimized_constant();
extern Object g2int_register_socket_to_handle();
extern Object g2int_socket_close_cleanups();
extern Object g2int_text_string_length();
extern Object g2int_tformat_gensym_string();
extern Object g2int_try_to_send_socket_buffer();
extern Object g2int_twrite_wide_character();
extern Object g2int_write_to_socket();

#endif

/* variables/constants */
extern Object G2int_chain_of_available_queue_elements;
extern Object G2int_chain_of_available_schedule_tasks;
extern Object G2int_chain_of_available_socket_output_buffers;
extern Object G2int_chain_of_available_tcp_sockets;
extern Object G2int_current_g2_time;
extern Object G2int_current_gensym_string;
extern Object G2int_current_real_time;
extern Object G2int_current_schedule_task;
extern Object G2int_current_task_queue_vector;
extern Object G2int_current_twriting_output_type;
extern Object G2int_current_wide_string;
extern Object G2int_current_wide_string_list;
extern Object G2int_deferred_task_queue_vector;
extern Object G2int_fill_pointer_for_current_gensym_string;
extern Object G2int_fill_pointer_for_current_wide_string;
#define G2int_ne_blocked_value FIX((SI_Long)0L)
#define G2int_ne_eof_value FIX((SI_Long)-1L)
#define G2int_ne_error_value FIX((SI_Long)-2L)
extern Object G2int_network_status_success;
extern Object G2int_priority_of_next_task;
extern Object G2int_socket_output_buffer_count;
extern Object G2int_structure_being_reclaimed;
extern Object G2int_system_is_running;
extern Object G2int_tcp_socket_count;
extern Object G2int_the_type_description_of_socket_output_buffer;
extern Object G2int_the_type_description_of_tcp_socket;
extern Object G2int_total_length_of_current_gensym_string;
extern Object G2int_total_length_of_current_wide_string;
