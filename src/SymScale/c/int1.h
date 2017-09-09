/* int1.h -- Header File for int1.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qcons;
extern Object Kelement_type;
extern Object Kend1;
extern Object Qeq;
extern Object Qerror;
extern Object Kinitial_element;
extern Object Qintern;
extern Object Qsymbol;
extern Object Qunsigned_byte;
extern Object Qwrite;

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

extern Object add_icp_message_handler(Object,Object);
extern Object add_icp_message_type_code(Object,Object,Object);
extern Object add_to_active_icp_sockets(Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_managed_simple_vector_for_skip_list(Object);
extern Object assq_function(Object,Object);
extern Object bytes_per_simple_vector(Object);
extern Object bytes_per_typed_simple_array(Object,Object);
extern Object cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object clear_frame_serial_number_to_item_table(Object);
extern Object clear_frame_serial_number_to_item_table_tree(Object);
extern Object clear_items_registered_with_handle_on_port(Object,Object);
extern Object clear_optimized_constants(void);
extern Object constant_queue_push_right(Object,Object);
extern Object copy_icp_buffer(Object);
extern Object copy_icp_buffer_chain(Object);
extern Object copy_icp_buffer_vector(Object,Object,Object,Object);
extern Object copy_list_using_icp_buffer_ref_count_conses_1(Object);
extern Object copy_list_using_icp_callback_conses_1(Object);
extern Object copy_list_using_icp_conses_1(Object);
extern Object copy_list_using_icp_conses_function(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_tree_using_icp_buffer_ref_count_conses_1(Object);
extern Object copy_tree_using_icp_callback_conses_1(Object);
extern Object copy_tree_using_icp_conses_1(Object);
extern Object def_bombout_clean_up_function(Object);
extern Object delete_gensym_element_1(Object,Object);
extern Object delete_icp_buffer_ref_count_cons_1(Object,Object);
extern Object delete_icp_buffer_ref_count_element_1(Object,Object);
extern Object delete_icp_callback_cons_1(Object,Object);
extern Object delete_icp_callback_element_1(Object,Object);
extern Object delete_icp_cons_1(Object,Object);
extern Object delete_icp_element_1(Object,Object);
extern Object delete_skip_list_entry(Object,Object,Object,Object,Object);
extern Object deregister_all_icp_accept_callbacks(Object);
extern Object deregister_all_icp_connect_callbacks(Object);
extern Object deregister_all_icp_connection_loss_callbacks(Object);
extern Object deregister_all_icp_read_callbacks(Object);
extern Object deregister_all_icp_write_callbacks(Object);
extern Object deregister_item_with_handle_on_port(Object,Object,Object);
extern Object describe_icp_trace_level(Object,Object);
extern Object direct_structure_method(Object,Object);
extern Object emit_icp_read_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_write_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object enlarge_index_space(Object,Object);
extern Object ensure_icp_buffer_vector_writability(Object,Object);
extern Object execute_icp_accept_callbacks(Object,Object);
extern Object execute_icp_connect_callbacks(Object);
extern Object execute_icp_connection_loss_callbacks(Object,Object);
extern Object execute_icp_read_callbacks(Object,Object);
extern Object execute_icp_write_callbacks(Object,Object);
extern Object extend_current_gensym_string(int,...);
extern Object flatten_frame_serial_number_to_item_table(Object);
extern Object flatten_skip_list(Object);
extern Object flush_icp_output_ports(void);
extern Object frame_serial_number_to_item_table(Object);
extern Object frame_serial_number_to_item_table_hash_vector_67_vector_memory_usage(void);
extern Object framep_function(Object);
extern Object future_task_schedule_2(Object);
extern Object gensym_cons_1(Object,Object);
extern Object get_from_icp_port(Object,Object,Object);
extern Object get_from_icp_port_if_any(Object,Object,Object);
extern Object get_remote_host_name(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object i_am_alive_info_structure_memory_usage(void);
extern Object icp_buffer_ref_count_cons_1(Object,Object);
extern Object icp_buffer_ref_count_cons_memory_usage(void);
extern Object icp_buffer_ref_count_list_2(Object,Object);
extern Object icp_buffer_ref_count_list_3(Object,Object,Object);
extern Object icp_buffer_ref_count_list_4(Object,Object,Object,Object);
extern Object icp_buffer_ref_count_list_trace_hook(Object);
extern Object icp_buffer_structure_memory_usage(void);
extern Object icp_callback_cons_1(Object,Object);
extern Object icp_callback_cons_memory_usage(void);
extern Object icp_callback_list_2(Object,Object);
extern Object icp_callback_list_3(Object,Object,Object);
extern Object icp_callback_list_4(Object,Object,Object,Object);
extern Object icp_callback_list_trace_hook(Object);
extern Object icp_connection_being_shutdown_qm(Object);
extern Object icp_connection_can_process_messages_qm(Object);
extern Object icp_connection_in_progress_p(Object);
extern Object icp_connection_open_p(Object);
extern Object icp_connection_timeout_task_1(Object,Object);
extern Object icp_connection_timeout_task_2(Object);
extern Object icp_cons_1(Object,Object);
extern Object icp_cons_memory_usage(void);
extern Object icp_list_2(Object,Object);
extern Object icp_list_3(Object,Object,Object);
extern Object icp_list_4(Object,Object,Object,Object);
extern Object icp_list_trace_hook(Object);
extern Object icp_object_type_given_icp_object(Object,Object);
extern Object icp_port_structure_memory_usage(void);
extern Object icp_socket_description(Object);
extern Object icp_socket_structure_memory_usage(void);
extern Object icp_trace(Object,Object);
extern Object icp_untrace(void);
extern Object initialize_icp_object_type(Object,Object,Object,Object);
extern Object initialize_icp_object_type_compile(Object,Object,Object);
extern Object instantaneous_icp_reader_byte_count(void);
extern Object instantaneous_icp_writer_byte_count(void);
extern Object item_index_space(Object);
extern Object item_with_handle_index_space(Object);
extern Object items_registered_with_handle_on_port(Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_frame_serial_number_to_item_table(void);
extern Object make_frame_serial_number_to_item_table_hash_vector(void);
extern Object make_frame_serial_number_to_item_table_tree_for_hash_skip_list_sentinel(Object,Object);
extern Object make_i_am_alive_info_1(void);
extern Object make_icp_buffer_internal_1(Object);
extern Object make_icp_buffer_ref_count_list_1(Object);
extern Object make_icp_callback_list_1(Object);
extern Object make_icp_list_1(Object);
extern Object make_icp_port(Object,Object,Object,Object);
extern Object make_icp_port_structure_1(Object,Object,Object,Object);
extern Object make_icp_socket(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_icp_socket_structure_1(Object,Object,Object,Object,Object);
extern Object make_permanent_frame_serial_number_to_item_table_hash_vector_67_vector_internal(void);
extern Object make_permanent_i_am_alive_info_structure_internal(void);
extern Object make_permanent_icp_buffer_structure_internal(void);
extern Object make_permanent_icp_port_structure_internal(void);
extern Object make_permanent_icp_socket_structure_internal(void);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object make_permanent_socket_structure_internal(void);
extern Object make_permanent_variable_fill_icp_buffer_4096_vector_internal(void);
extern Object make_skip_list_element_1(Object,Object,Object,Object);
extern Object make_socket_1(void);
extern Object make_thread_array(Object);
extern Object make_variable_fill_icp_buffer(void);
extern Object memq_function(Object,Object);
extern Object mutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry(Object,Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object nil_out_car_of_cons(Object);
extern Object not_a_listener_p(Object);
extern Object note_item_deleted_from_frame_serial_number_table(Object);
extern Object notify_user(int,...);
extern Object notify_user_in_parent_window(int,...);
extern Object out_frame_serial_number_to_item_table_hash_vector_67_vectors(void);
extern Object out_variable_fill_icp_buffer_4096_vectors(void);
extern Object outstanding_i_am_alive_info_count(void);
extern Object outstanding_icp_buffer_count(void);
extern Object outstanding_icp_buffer_ref_count_conses(void);
extern Object outstanding_icp_callback_conses(void);
extern Object outstanding_icp_conses(void);
extern Object outstanding_icp_port_count(void);
extern Object outstanding_icp_socket_count(void);
extern Object outstanding_socket_count(void);
extern Object push_optimized_constant(Object);
extern Object reclaim_enclosing_interface_frame_serial_number(Object);
extern Object reclaim_frame_serial_number(Object);
extern Object reclaim_frame_serial_number_to_item_table(Object);
extern Object reclaim_frame_serial_number_to_item_table_hash_vector(Object);
extern Object reclaim_gensym_cons_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gsi_extension_data_for_gsi(Object);
extern Object reclaim_i_am_alive_info_1(Object);
extern Object reclaim_i_am_alive_info_qm(Object);
extern Object reclaim_icp_accept_callbacks(Object);
extern Object reclaim_icp_buffer(Object);
extern Object reclaim_icp_buffer_internal_1(Object);
extern Object reclaim_icp_buffer_ref_count_cons_1(Object);
extern Object reclaim_icp_buffer_ref_count_list_1(Object);
extern Object reclaim_icp_buffer_ref_count_list_star_1(Object);
extern Object reclaim_icp_buffer_ref_count_tree_1(Object);
extern Object reclaim_icp_callback_cons_1(Object);
extern Object reclaim_icp_callback_list_1(Object);
extern Object reclaim_icp_callback_list_star_1(Object);
extern Object reclaim_icp_callback_tree_1(Object);
extern Object reclaim_icp_callbacks(Object);
extern Object reclaim_icp_connect_callbacks(Object);
extern Object reclaim_icp_connection_loss_callbacks(Object);
extern Object reclaim_icp_cons_1(Object);
extern Object reclaim_icp_list_1(Object);
extern Object reclaim_icp_list_function(Object);
extern Object reclaim_icp_list_star_1(Object);
extern Object reclaim_icp_object_map(Object,Object,Object);
extern Object reclaim_icp_port_entry(Object,Object,Object,Object);
extern Object reclaim_icp_port_internal_1(Object);
extern Object reclaim_icp_read_callbacks(Object);
extern Object reclaim_icp_socket_internal_1(Object);
extern Object reclaim_icp_tree_1(Object);
extern Object reclaim_icp_tree_with_text_strings(Object);
extern Object reclaim_icp_version_info(Object);
extern Object reclaim_icp_write_callbacks(Object);
extern Object reclaim_if_frame_serial_number_to_item_table(Object);
extern Object reclaim_if_index_space(Object);
extern Object reclaim_index_space_1(Object);
extern Object reclaim_index_space_location_and_corresponding_objects(Object,Object,Object,Object);
extern Object reclaim_remote_procedure_call_start_map(Object);
extern Object reclaim_resumable_icp_output_task_queue_vector(Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_skip_list_element(Object);
extern Object reclaim_socket_1(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_things_to_update_when_unclogged_qm(Object);
extern Object reclaim_variable_fill_icp_buffer(Object);
extern Object reclaim_wide_string(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object register_icp_accept_callback(Object,Object);
extern Object register_icp_connect_callback(Object,Object);
extern Object register_icp_connection_loss_callback(Object,Object);
extern Object register_icp_read_callback(Object,Object);
extern Object register_icp_write_callback(Object,Object);
extern Object register_item_with_handle_on_port(Object,Object,Object);
extern Object replenish_icp_buffer_ref_count_cons_pool(void);
extern Object replenish_icp_buffer_ref_count_list_pool(Object);
extern Object replenish_icp_callback_cons_pool(void);
extern Object replenish_icp_callback_list_pool(Object);
extern Object replenish_icp_cons_pool(void);
extern Object replenish_icp_list_pool(Object);
extern Object replenish_lookup_cons_pool(void);
extern Object replenish_vector_pool_cons_pool(void);
extern Object resumable_icp_pop(void);
extern Object resumable_icp_pop_list_if_end_marker(void);
extern Object resumable_icp_push(Object);
extern Object set_icp_tracing_level_from_command_line(void);
extern Object set_in_icp_port(Object,Object,Object,Object);
extern Object set_skip_list_entry(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object set_socket_debug_status(Object,Object);
extern Object set_up_icp_object_index_space(Object);
extern Object shutdown_icp_socket_connection(int,...);
extern Object socket_structure_memory_usage(void);
extern Object stringw(Object);
extern Object sxhashw(Object);
extern Object text_string_p(Object);
extern Object tformat(int,...);
extern Object transmit_icp_output_if_ready(Object,Object);
extern Object twrite_general_string(Object);
extern Object twrite_icp_socket_connection_name(Object);
extern Object twrite_wide_character(Object);
extern Object unicode_uppercase_if_lowercase(Object);
extern Object update_object_pool_meters_list(Object);
extern Object validate_icp_trace_cutoff_value(Object,Object,Object);
extern Object variable_fill_icp_buffer_4096_vector_memory_usage(void);

#else

extern Object add_icp_message_handler();
extern Object add_icp_message_type_code();
extern Object add_to_active_icp_sockets();
extern Object allocate_byte_vector_16();
extern Object allocate_managed_simple_vector_for_skip_list();
extern Object assq_function();
extern Object bytes_per_simple_vector();
extern Object bytes_per_typed_simple_array();
extern Object cancel_and_reclaim_scheduled_queue_element_1();
extern Object clear_frame_serial_number_to_item_table();
extern Object clear_frame_serial_number_to_item_table_tree();
extern Object clear_items_registered_with_handle_on_port();
extern Object clear_optimized_constants();
extern Object constant_queue_push_right();
extern Object copy_icp_buffer();
extern Object copy_icp_buffer_chain();
extern Object copy_icp_buffer_vector();
extern Object copy_list_using_icp_buffer_ref_count_conses_1();
extern Object copy_list_using_icp_callback_conses_1();
extern Object copy_list_using_icp_conses_1();
extern Object copy_list_using_icp_conses_function();
extern Object copy_out_current_wide_string();
extern Object copy_tree_using_icp_buffer_ref_count_conses_1();
extern Object copy_tree_using_icp_callback_conses_1();
extern Object copy_tree_using_icp_conses_1();
extern Object def_bombout_clean_up_function();
extern Object delete_gensym_element_1();
extern Object delete_icp_buffer_ref_count_cons_1();
extern Object delete_icp_buffer_ref_count_element_1();
extern Object delete_icp_callback_cons_1();
extern Object delete_icp_callback_element_1();
extern Object delete_icp_cons_1();
extern Object delete_icp_element_1();
extern Object delete_skip_list_entry();
extern Object deregister_all_icp_accept_callbacks();
extern Object deregister_all_icp_connect_callbacks();
extern Object deregister_all_icp_connection_loss_callbacks();
extern Object deregister_all_icp_read_callbacks();
extern Object deregister_all_icp_write_callbacks();
extern Object deregister_item_with_handle_on_port();
extern Object describe_icp_trace_level();
extern Object direct_structure_method();
extern Object emit_icp_read_trace();
extern Object emit_icp_write_trace();
extern Object enlarge_index_space();
extern Object ensure_icp_buffer_vector_writability();
extern Object execute_icp_accept_callbacks();
extern Object execute_icp_connect_callbacks();
extern Object execute_icp_connection_loss_callbacks();
extern Object execute_icp_read_callbacks();
extern Object execute_icp_write_callbacks();
extern Object extend_current_gensym_string();
extern Object flatten_frame_serial_number_to_item_table();
extern Object flatten_skip_list();
extern Object flush_icp_output_ports();
extern Object frame_serial_number_to_item_table();
extern Object frame_serial_number_to_item_table_hash_vector_67_vector_memory_usage();
extern Object framep_function();
extern Object future_task_schedule_2();
extern Object gensym_cons_1();
extern Object get_from_icp_port();
extern Object get_from_icp_port_if_any();
extern Object get_remote_host_name();
extern Object getfq_function_no_default();
extern Object i_am_alive_info_structure_memory_usage();
extern Object icp_buffer_ref_count_cons_1();
extern Object icp_buffer_ref_count_cons_memory_usage();
extern Object icp_buffer_ref_count_list_2();
extern Object icp_buffer_ref_count_list_3();
extern Object icp_buffer_ref_count_list_4();
extern Object icp_buffer_ref_count_list_trace_hook();
extern Object icp_buffer_structure_memory_usage();
extern Object icp_callback_cons_1();
extern Object icp_callback_cons_memory_usage();
extern Object icp_callback_list_2();
extern Object icp_callback_list_3();
extern Object icp_callback_list_4();
extern Object icp_callback_list_trace_hook();
extern Object icp_connection_being_shutdown_qm();
extern Object icp_connection_can_process_messages_qm();
extern Object icp_connection_in_progress_p();
extern Object icp_connection_open_p();
extern Object icp_connection_timeout_task_1();
extern Object icp_connection_timeout_task_2();
extern Object icp_cons_1();
extern Object icp_cons_memory_usage();
extern Object icp_list_2();
extern Object icp_list_3();
extern Object icp_list_4();
extern Object icp_list_trace_hook();
extern Object icp_object_type_given_icp_object();
extern Object icp_port_structure_memory_usage();
extern Object icp_socket_description();
extern Object icp_socket_structure_memory_usage();
extern Object icp_trace();
extern Object icp_untrace();
extern Object initialize_icp_object_type();
extern Object initialize_icp_object_type_compile();
extern Object instantaneous_icp_reader_byte_count();
extern Object instantaneous_icp_writer_byte_count();
extern Object item_index_space();
extern Object item_with_handle_index_space();
extern Object items_registered_with_handle_on_port();
extern Object load_and_initialize_type_description();
extern Object make_frame_serial_number_to_item_table();
extern Object make_frame_serial_number_to_item_table_hash_vector();
extern Object make_frame_serial_number_to_item_table_tree_for_hash_skip_list_sentinel();
extern Object make_i_am_alive_info_1();
extern Object make_icp_buffer_internal_1();
extern Object make_icp_buffer_ref_count_list_1();
extern Object make_icp_callback_list_1();
extern Object make_icp_list_1();
extern Object make_icp_port();
extern Object make_icp_port_structure_1();
extern Object make_icp_socket();
extern Object make_icp_socket_structure_1();
extern Object make_permanent_frame_serial_number_to_item_table_hash_vector_67_vector_internal();
extern Object make_permanent_i_am_alive_info_structure_internal();
extern Object make_permanent_icp_buffer_structure_internal();
extern Object make_permanent_icp_port_structure_internal();
extern Object make_permanent_icp_socket_structure_internal();
extern Object make_permanent_schedule_task_structure_internal();
extern Object make_permanent_socket_structure_internal();
extern Object make_permanent_variable_fill_icp_buffer_4096_vector_internal();
extern Object make_skip_list_element_1();
extern Object make_socket_1();
extern Object make_thread_array();
extern Object make_variable_fill_icp_buffer();
extern Object memq_function();
extern Object mutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry();
extern Object mutate_global_property();
extern Object nil_out_car_of_cons();
extern Object not_a_listener_p();
extern Object note_item_deleted_from_frame_serial_number_table();
extern Object notify_user();
extern Object notify_user_in_parent_window();
extern Object out_frame_serial_number_to_item_table_hash_vector_67_vectors();
extern Object out_variable_fill_icp_buffer_4096_vectors();
extern Object outstanding_i_am_alive_info_count();
extern Object outstanding_icp_buffer_count();
extern Object outstanding_icp_buffer_ref_count_conses();
extern Object outstanding_icp_callback_conses();
extern Object outstanding_icp_conses();
extern Object outstanding_icp_port_count();
extern Object outstanding_icp_socket_count();
extern Object outstanding_socket_count();
extern Object push_optimized_constant();
extern Object reclaim_enclosing_interface_frame_serial_number();
extern Object reclaim_frame_serial_number();
extern Object reclaim_frame_serial_number_to_item_table();
extern Object reclaim_frame_serial_number_to_item_table_hash_vector();
extern Object reclaim_gensym_cons_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gsi_extension_data_for_gsi();
extern Object reclaim_i_am_alive_info_1();
extern Object reclaim_i_am_alive_info_qm();
extern Object reclaim_icp_accept_callbacks();
extern Object reclaim_icp_buffer();
extern Object reclaim_icp_buffer_internal_1();
extern Object reclaim_icp_buffer_ref_count_cons_1();
extern Object reclaim_icp_buffer_ref_count_list_1();
extern Object reclaim_icp_buffer_ref_count_list_star_1();
extern Object reclaim_icp_buffer_ref_count_tree_1();
extern Object reclaim_icp_callback_cons_1();
extern Object reclaim_icp_callback_list_1();
extern Object reclaim_icp_callback_list_star_1();
extern Object reclaim_icp_callback_tree_1();
extern Object reclaim_icp_callbacks();
extern Object reclaim_icp_connect_callbacks();
extern Object reclaim_icp_connection_loss_callbacks();
extern Object reclaim_icp_cons_1();
extern Object reclaim_icp_list_1();
extern Object reclaim_icp_list_function();
extern Object reclaim_icp_list_star_1();
extern Object reclaim_icp_object_map();
extern Object reclaim_icp_port_entry();
extern Object reclaim_icp_port_internal_1();
extern Object reclaim_icp_read_callbacks();
extern Object reclaim_icp_socket_internal_1();
extern Object reclaim_icp_tree_1();
extern Object reclaim_icp_tree_with_text_strings();
extern Object reclaim_icp_version_info();
extern Object reclaim_icp_write_callbacks();
extern Object reclaim_if_frame_serial_number_to_item_table();
extern Object reclaim_if_index_space();
extern Object reclaim_index_space_1();
extern Object reclaim_index_space_location_and_corresponding_objects();
extern Object reclaim_remote_procedure_call_start_map();
extern Object reclaim_resumable_icp_output_task_queue_vector();
extern Object reclaim_schedule_task_args();
extern Object reclaim_skip_list_element();
extern Object reclaim_socket_1();
extern Object reclaim_text_string();
extern Object reclaim_things_to_update_when_unclogged_qm();
extern Object reclaim_variable_fill_icp_buffer();
extern Object reclaim_wide_string();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object register_icp_accept_callback();
extern Object register_icp_connect_callback();
extern Object register_icp_connection_loss_callback();
extern Object register_icp_read_callback();
extern Object register_icp_write_callback();
extern Object register_item_with_handle_on_port();
extern Object replenish_icp_buffer_ref_count_cons_pool();
extern Object replenish_icp_buffer_ref_count_list_pool();
extern Object replenish_icp_callback_cons_pool();
extern Object replenish_icp_callback_list_pool();
extern Object replenish_icp_cons_pool();
extern Object replenish_icp_list_pool();
extern Object replenish_lookup_cons_pool();
extern Object replenish_vector_pool_cons_pool();
extern Object resumable_icp_pop();
extern Object resumable_icp_pop_list_if_end_marker();
extern Object resumable_icp_push();
extern Object set_icp_tracing_level_from_command_line();
extern Object set_in_icp_port();
extern Object set_skip_list_entry();
extern Object set_socket_debug_status();
extern Object set_up_icp_object_index_space();
extern Object shutdown_icp_socket_connection();
extern Object socket_structure_memory_usage();
extern Object stringw();
extern Object sxhashw();
extern Object text_string_p();
extern Object tformat();
extern Object transmit_icp_output_if_ready();
extern Object twrite_general_string();
extern Object twrite_icp_socket_connection_name();
extern Object twrite_wide_character();
extern Object unicode_uppercase_if_lowercase();
extern Object update_object_pool_meters_list();
extern Object validate_icp_trace_cutoff_value();
extern Object variable_fill_icp_buffer_4096_vector_memory_usage();

#endif

/* variables/constants */
#define Abort_icp_task_icp_version FIX((SI_Long)13L)
extern Object Access_form_for_corresponding_icp_object_map_prop;
#define Acknowledge_deregister_corresponding_icp_object_icp_version FIX((SI_Long)12L)
DECLARE_VARIABLE_WITH_SYMBOL(Active_icp_sockets, Qactive_icp_sockets);
DECLARE_VARIABLE_WITH_SYMBOL(All_index_space_names, Qall_index_space_names);
DECLARE_VARIABLE_WITH_SYMBOL(Available_frame_serial_number_to_item_table_hash_vector_67_vectors, Qavailable_frame_serial_number_to_item_table_hash_vector_67_vectors);
extern Object Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Available_icp_buffer_ref_count_conses, Qavailable_icp_buffer_ref_count_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Available_icp_buffer_ref_count_conses_tail, Qavailable_icp_buffer_ref_count_conses_tail);
extern Object Available_icp_buffer_ref_count_conses_tail_vector;
extern Object Available_icp_buffer_ref_count_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Available_icp_callback_conses, Qavailable_icp_callback_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Available_icp_callback_conses_tail, Qavailable_icp_callback_conses_tail);
extern Object Available_icp_callback_conses_tail_vector;
extern Object Available_icp_callback_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Available_icp_conses, Qavailable_icp_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Available_icp_conses_tail, Qavailable_icp_conses_tail);
extern Object Available_icp_conses_tail_vector;
extern Object Available_icp_conses_vector;
extern Object Available_lookup_conses_tail_vector;
extern Object Available_lookup_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Available_variable_fill_icp_buffer_4096_vectors, Qavailable_variable_fill_icp_buffer_4096_vectors);
extern Object Available_variable_fill_icp_buffer_4096_vectors_vector;
extern Object Available_vector_pool_conses_tail_vector;
extern Object Available_vector_pool_conses_vector;
extern Object Blank_traced_icp_byte_column;
#define By_copy_with_handle_supports_references_icp_version FIX((SI_Long)16L)
extern Object Bytes_per_rtl_ptr;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_i_am_alive_infos, Qchain_of_available_i_am_alive_infos);
extern Object Chain_of_available_i_am_alive_infos_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_icp_buffers, Qchain_of_available_icp_buffers);
extern Object Chain_of_available_icp_buffers_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_icp_ports, Qchain_of_available_icp_ports);
extern Object Chain_of_available_icp_ports_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_icp_sockets, Qchain_of_available_icp_sockets);
extern Object Chain_of_available_icp_sockets_vector;
extern Object Chain_of_available_schedule_tasks_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_sockets, Qchain_of_available_sockets);
extern Object Chain_of_available_sockets_vector;
extern Object Command_line_arguments;
#define Compressed_image_data_chunk_icp_version FIX((SI_Long)27L)
extern Object Cons_pool_conses_to_make_at_a_time;
DECLARE_VARIABLE_WITH_SYMBOL(Count_of_frame_serial_number_to_item_table_hash_vector_67_vectors, Qcount_of_frame_serial_number_to_item_table_hash_vector_67_vectors);
DECLARE_VARIABLE_WITH_SYMBOL(Count_of_variable_fill_icp_buffer_4096_vectors, Qcount_of_variable_fill_icp_buffer_4096_vectors);
DECLARE_VARIABLE_WITH_SYMBOL(Current_g2_time, Qcurrent_g2_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_gensym_string, Qcurrent_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_port, Qcurrent_icp_port);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_read_trace_level, Qcurrent_icp_read_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_socket, Qcurrent_icp_socket);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_write_trace_level, Qcurrent_icp_write_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_real_time, Qcurrent_real_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_schedule_task, Qcurrent_schedule_task);
DECLARE_VARIABLE_WITH_SYMBOL(Current_standard_icp_object_index_space, Qcurrent_standard_icp_object_index_space);
extern Object Current_task_queue_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_temporary_icp_object_index_space, Qcurrent_temporary_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
#define Data_servers_can_run_while_inactive_version FIX((SI_Long)15L)
extern Object Data_service_i_am_alive_messages;
extern Object Deferred_task_queue_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Delete_corresponding_object_qm, Qdelete_corresponding_object_qm);
#define Deregister_corresponding_icp_object_index_space_name_icp_version FIX((SI_Long)10L)
DECLARE_VARIABLE_WITH_SYMBOL(Deregister_corresponding_object_qm, Qderegister_corresponding_object_qm);
#define Deregister_icp_objects_icp_version FIX((SI_Long)13L)
#define Deregister_original_icp_object_icp_version FIX((SI_Long)10L)
#define Dialog_component_with_font_icp_version FIX((SI_Long)28L)
DECLARE_VARIABLE_WITH_SYMBOL(Disable_resumability, Qdisable_resumability);
DECLARE_VARIABLE_WITH_SYMBOL(Do_not_reclaim_runs_while_inactive_entries, Qdo_not_reclaim_runs_while_inactive_entries);
#define Do_not_reformat_message_icp_version FIX((SI_Long)21L)
#define Does_not_require_enlarge_corresponding_icp_object_index_space_icp_version FIX((SI_Long)8L)
#define Double_float_icp_version FIX((SI_Long)2L)
#define Ds_update_interval_as_float_icp_version FIX((SI_Long)5L)
extern Object Equivalent_icp_value_type_prop;
#define Evaluation_sequences_and_structures_icp_version FIX((SI_Long)8L)
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_gensym_string, Qfill_pointer_for_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
extern Object Fixnum_time_units_per_second;
extern Object Fp_mutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry;
extern Object Function_for_icp_value_reader_qm_prop;
extern Object Function_for_icp_value_writer_qm_prop;
#define G2_supports_update_with_delete_icp_version FIX((SI_Long)19L)
#define G2_version_reply_to_gsi_icp_version FIX((SI_Long)5L)
extern Object Gsi_connection_established;
extern Object Gsi_connection_initializing;
#define Gsi_dataservice_uses_full_remote_value_protocol_icp_version FIX((SI_Long)11L)
#define Gsi_item_registration_icp_version FIX((SI_Long)5L)
#define Gsi_sends_returned_gsi_sensor_as_reference_icp_version FIX((SI_Long)18L)
#define Gsi_timestamp_as_float_icp_version FIX((SI_Long)5L)
#define Gsi_undefined_context FIX((SI_Long)-1L)
#define Gsi_uninitialized_context FIX((SI_Long)-2L)
DECLARE_VARIABLE_WITH_SYMBOL(Highest_icp_socket_session_id, Qhighest_icp_socket_session_id);
DECLARE_VARIABLE_WITH_SYMBOL(I_am_alive_info_count, Qi_am_alive_info_count);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_buffer_count, Qicp_buffer_count);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_buffer_ref_count_cons_counter, Qicp_buffer_ref_count_cons_counter);
extern Object Icp_buffer_ref_count_cons_counter_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_callback_cons_counter, Qicp_callback_cons_counter);
extern Object Icp_callback_cons_counter_vector;
extern Object Icp_connection_awaiting_acknowledgement;
extern Object Icp_connection_closed;
extern Object Icp_connection_connect_in_progress;
extern Object Icp_connection_running;
extern Object Icp_connection_shutdown_acknowledgement_rundown;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_cons_counter, Qicp_cons_counter);
extern Object Icp_cons_counter_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_message_handler_array, Qicp_message_handler_array);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_message_handler_name_array, Qicp_message_handler_name_array);
extern Object Icp_message_type_code_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_output_ports_to_flush, Qicp_output_ports_to_flush);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_port_count, Qicp_port_count);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_printing_message_handler_array, Qicp_printing_message_handler_array);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_priority_categories_for_gsi, Qicp_priority_categories_for_gsi);
extern Object Icp_priority_category_for_message_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_read_trace_cutoff_level_qm, Qicp_read_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_socket_connect_negotiation_timeout_default, Qicp_socket_connect_negotiation_timeout_default);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_socket_count, Qicp_socket_count);
extern Object Icp_socket_error;
extern Object Icp_socket_listening;
extern Object Icp_socket_shutdown_handshake_timeout;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_suspend, Qicp_suspend);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_trace_level_descriptions, Qicp_trace_level_descriptions);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_trace_print_message_series_p, Qicp_trace_print_message_series_p);
extern Object Icp_value_reader_function_prop;
extern Object Icp_value_reclaimer_prop;
extern Object Icp_value_write_function_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_write_trace_cutoff_level_qm, Qicp_write_trace_cutoff_level_qm);
#define Independent_layered_rendering_version FIX((SI_Long)15L)
DECLARE_VARIABLE_WITH_SYMBOL(Inhibit_corresponding_icp_object_making, Qinhibit_corresponding_icp_object_making);
#define Intern_keyword_icp_version FIX((SI_Long)22L)
#define Item_index_space_icp_version FIX((SI_Long)10L)
#define Item_reference_icp_version FIX((SI_Long)12L)
#define Long_string_icp_version FIX((SI_Long)23L)
#define Lowest_system_priority FIX((SI_Long)11L)
DECLARE_VARIABLE_WITH_SYMBOL(Maximum_object_passing_bandwidth, Qmaximum_object_passing_bandwidth);
#define Modify_gsi_sensor_definition_icp_version FIX((SI_Long)2L)
extern Object Name_of_corresponding_icp_object_index_space_prop;
#define Native_long_icp_version FIX((SI_Long)30L)
#define New_connect_scheme_icp_version FIX((SI_Long)5L)
#define New_remote_procedure_identifer_protocol_icp_version FIX((SI_Long)9L)
#define New_rpc_kinds_icp_version FIX((SI_Long)8L)
extern Object Newest_icp_version;
#define No_frame_serial_index_space_icp_version FIX((SI_Long)21L)
#define No_licence_icp_version FIX((SI_Long)18L)
#define No_telewindows_clogging_icp_version FIX((SI_Long)9L)
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_for_message_series, Qnumber_of_icp_bytes_for_message_series);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_left_in_message_series, Qnumber_of_icp_bytes_left_in_message_series);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_ready_to_read, Qnumber_of_icp_bytes_ready_to_read);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer, Qnumber_of_icp_bytes_to_fill_buffer);
#define Pass_item_as_copy_icp_version FIX((SI_Long)5L)
#define Pass_item_as_handle_icp_version FIX((SI_Long)5L)
extern Object Priority_for_icp_priority_category_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Priority_of_next_task, Qpriority_of_next_task);
DECLARE_VARIABLE_WITH_SYMBOL(Profiling_enabled_qm, Qprofiling_enabled_qm);
#define Reclaim_remote_corresponding_object_icp_version FIX((SI_Long)2L)
extern Object Reclaimer_for_icp_object_prop;
extern Object Reclaimer_for_icp_port_entry_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Recycled_icp_buffers, Qrecycled_icp_buffers);
DECLARE_VARIABLE_WITH_SYMBOL(Recycled_variable_fill_icp_buffers, Qrecycled_variable_fill_icp_buffers);
#define Rel4_rpc_protocol_supports_non_objects_icp_version FIX((SI_Long)8L)
#define Release_1_dot_0_icp_version FIX((SI_Long)1L)
#define Release_2_dot_0_icp_version FIX((SI_Long)2L)
#define Release_3_dot_0_icp_version FIX((SI_Long)4L)
#define Release_4_dot_0_icp_version FIX((SI_Long)5L)
#define Remote_procedure_include_all_system_attributes_except_icp_version FIX((SI_Long)25L)
#define Remote_procedure_include_all_system_attributes_icp_version FIX((SI_Long)9L)
#define Remote_procedure_include_attribute_icp_version FIX((SI_Long)5L)
#define Remote_procedure_varargs_p_icp_version FIX((SI_Long)9L)
#define Remote_value_supports_item_icp_version FIX((SI_Long)8L)
#define Resumable_gsi_ds_icp_version FIX((SI_Long)9L)
DECLARE_VARIABLE_WITH_SYMBOL(Resumable_icp_state, Qresumable_icp_state);
#define Resumable_icp_version FIX((SI_Long)8L)
#define Return_g2ds_version_sends_class_icp_version FIX((SI_Long)17L)
#define Rpc_use_value_structure_using_unix_time_icp_version FIX((SI_Long)10L)
#define Send_text_of_expressions_for_g2ds_icp_version FIX((SI_Long)24L)
#define Shutdown_protocol_icp_version FIX((SI_Long)5L)
extern Object Shutdown_reclaimer_for_icp_object_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Socket_count, Qsocket_count);
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
#define Supports_font_in_grid_view_icp_version FIX((SI_Long)29L)
#define Supports_icp_version_protocol_icp_version FIX((SI_Long)8L)
#define Supports_new_references_icp_version FIX((SI_Long)18L)
#define Supports_non_resumability_icp_version FIX((SI_Long)17L)
#define Supports_optional_remote_value_tags_icp_version FIX((SI_Long)8L)
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
#define T2_supports_item_layer_change FIX((SI_Long)20L)
DECLARE_VARIABLE_WITH_SYMBOL(Tformat_fresh_line_is_newline_p, Qtformat_fresh_line_is_newline_p);
DECLARE_VARIABLE_WITH_SYMBOL(The_g2_defstruct_package, Qthe_g2_defstruct_package);
extern Object The_type_description_of_i_am_alive_info;
extern Object The_type_description_of_icp_buffer;
extern Object The_type_description_of_icp_port;
extern Object The_type_description_of_icp_socket;
extern Object The_type_description_of_socket;
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_gensym_string, Qtotal_length_of_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Trace_skip_data_service_i_am_alive_messages_p, Qtrace_skip_data_service_i_am_alive_messages_p);
DECLARE_VARIABLE_WITH_SYMBOL(Transmitted_variable_fill_icp_buffers, Qtransmitted_variable_fill_icp_buffers);
#define Transparent_color_index_icp_version FIX((SI_Long)26L)
DECLARE_VARIABLE_WITH_SYMBOL(Trif_block_value_alist, Qtrif_block_value_alist);
#define Unsigned_short_vector_icp_version FIX((SI_Long)14L)
#define Value_vector_names_are_symbols_icp_version FIX((SI_Long)8L)
#define Values_as_handle_icp_version FIX((SI_Long)10L)
#define Wide_strings_icp_version FIX((SI_Long)6L)
DECLARE_VARIABLE_WITH_SYMBOL(With_icp_buffer_coelescing_scope_qm, Qwith_icp_buffer_coelescing_scope_qm);
#define Writing_coalesced_icp_message_group_icp_version FIX((SI_Long)7L)
