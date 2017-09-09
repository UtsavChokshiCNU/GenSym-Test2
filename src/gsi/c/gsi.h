/* gsi.h -- Header File for gsi.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qerror;
extern Object Kinitial_element;
extern Object Klocal;
extern Object Ktest;
extern Object Qunsigned_byte;

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

extern Object g2int_abort(int,...);
extern Object g2int_abort_gsi_top_level(void);
extern Object g2int_add_vectors_to_gsi_history(Object,Object,Object);
extern Object g2int_allocate_byte_vector_16(Object);
extern Object g2int_allocate_gsi_context_number(void);
extern Object g2int_allocate_initialized_managed_simple_vector(Object);
extern Object g2int_allocate_managed_long_box(void);
extern Object g2int_allocate_managed_simple_float_array(Object);
extern Object g2int_allocate_managed_simple_vector(Object);
extern Object g2int_announce_system_presence(Object);
extern Object g2int_assq_function(Object,Object);
extern Object g2int_build_id_digit_offset(Object);
extern Object g2int_build_id_letter_offset(Object);
extern Object g2int_bytes_per_double_float_simple_array(Object);
extern Object g2int_c_native_clock_ticks_or_cache(Object,Object);
extern Object g2int_c_string_to_gensym_string(Object);
extern Object g2int_c_string_to_gsi_string(Object);
extern Object g2int_c_string_to_text_string(Object);
extern Object g2int_c_unsigned_short_vector_to_text_string(Object,Object);
extern Object g2int_c_wide_string_to_gensym_string(Object);
extern Object g2int_c_wide_string_to_gsi_string(Object);
extern Object g2int_c_wide_string_to_text_string(Object);
extern Object g2int_cache_command_line_if_necessary(void);
extern Object g2int_call_gsi_callback(int,...);
extern Object g2int_call_gsi_close_fd_callback(Object);
extern Object g2int_call_gsi_not_writing_fd_callback(Object);
extern Object g2int_call_gsi_open_fd_callback(Object);
extern Object g2int_call_gsi_writing_fd_callback(Object);
extern Object g2int_cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object g2int_check_gsi_value_vector(Object);
extern Object g2int_check_transfer_wrapper(Object,Object,Object);
extern Object g2int_chestnut_floorf_function(Object,Object);
extern Object g2int_clear_gsi_error_message(void);
extern Object g2int_close_and_disconnect_icp_socket_handle(Object);
extern Object g2int_convert_gsi_value_to_value(Object);
extern Object g2int_convert_value_to_gsi_value(Object);
extern Object g2int_copy_constant_wide_string_given_length(Object,Object);
extern Object g2int_copy_gensym_string(Object);
extern Object g2int_copy_managed_float(Object);
extern Object g2int_copy_out_current_wide_string(void);
extern Object g2int_copy_partial_text_string(Object,Object);
extern Object g2int_copy_text_string(Object);
extern Object g2int_create_transcode_text_conversion_style(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_create_transfer_wrapper_array(Object);
extern Object g2int_current_gsi_application(void);
extern Object g2int_current_gsi_string_conversion_style(void);
extern Object g2int_default_owner_for_gsi_objects(void);
extern Object g2int_delete_gensym_element_1(Object,Object);
extern Object g2int_dequeue_and_execute_next_task(void);
extern Object g2int_derive_network_listeners(void);
extern Object g2int_direct_structure_method(Object,Object);
extern Object g2int_do_not_catch_aborts_p(void);
extern Object g2int_element_type_for_gsi_type(Object);
extern Object g2int_encode_build_identification_integer(Object);
extern Object g2int_end_icp_message_group(void);
extern Object g2int_enlarge_index_space(Object,Object);
extern Object g2int_enqueue_scheduler_events_if_necessary(Object);
extern Object g2int_enter_abyss(void);
extern Object g2int_entering_signal_handler_function(void);
extern Object g2int_equalw(Object,Object);
extern Object g2int_establish_gsi_listener(int,...);
extern Object g2int_establish_gsi_listeners(void);
extern Object g2int_establish_initial_gsi_listener(Object,Object);
extern Object g2int_export_text_string_per_text_conversion_style(int,...);
extern Object g2int_filter_text_for_gsi_p(void);
extern Object g2int_finalize_and_reclaim_icp_socket(Object);
extern Object g2int_find_or_load_gsi_application(Object);
extern Object g2int_fixnum_time_interval(Object);
extern Object g2int_flush_and_shutdown_icp_socket(Object);
extern Object g2int_flush_icp_output_ports(void);
extern Object g2int_future_task_schedule_2(Object);
extern Object g2int_g2_event_ready_p(void);
extern Object g2int_g2_unrecoverable_error_exit(void);
extern Object g2int_generate_float_vector(Object);
extern Object g2int_gensym_cons_1(Object,Object);
extern Object g2int_gensym_decode_unix_time(Object);
extern Object g2int_gensym_encode_unix_time_as_managed_float(Object,Object,Object,Object,Object,Object);
extern Object g2int_gensym_list_2(Object,Object);
extern Object g2int_gensym_list_3(Object,Object,Object);
extern Object g2int_gensym_list_4(Object,Object,Object,Object);
extern Object g2int_gensym_make_pathname_with_copied_components(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_gensym_string_to_wide_string_for_gsi(Object);
extern Object g2int_get_command_line_flag_argument(int,...);
extern Object g2int_get_command_line_keyword_argument(int,...);
extern Object g2int_get_command_line_keyword_argument_as_integer(int,...);
extern Object g2int_get_connect_address_from_command_line(void);
extern Object g2int_get_from_icp_port_if_any(Object,Object,Object);
extern Object g2int_get_gensym_command_line_argument(Object);
extern Object g2int_get_gensym_command_line_argument_as_text_string(Object);
extern Object g2int_get_gensym_command_line_argument_count(void);
extern Object g2int_get_gsi_instance_plist_value(Object,Object);
extern Object g2int_get_icp_object_index_for_gsi_instance(Object,Object);
extern Object g2int_get_icp_socket_from_context(Object,Object);
extern Object g2int_get_instance_for_read_1(Object,Object);
extern Object g2int_get_instance_for_write_1(Object);
extern Object g2int_get_listener_from_command_line(Object);
extern Object g2int_get_local_host_addresses(void);
extern Object g2int_get_local_host_name(void);
extern Object g2int_get_network_listener(Object);
extern Object g2int_get_preset_tcp_port_number(void);
extern Object g2int_get_remote_g2_time_at_start(Object);
extern Object g2int_get_remote_home_name(Object);
extern Object g2int_get_remote_host_name(Object);
extern Object g2int_get_remote_listener_port(Object);
extern Object g2int_get_tcp_listener_port_number(Object);
extern Object g2int_getfq_function_no_default(Object,Object);
extern Object g2int_gsi_allocate_managed_array(Object);
extern Object g2int_gsi_api_symbol_to_symbol_or_nil_1(Object,Object);
extern Object g2int_gsi_application_for_socket(Object);
extern Object g2int_gsi_attribute_qualified_name(Object);
extern Object g2int_gsi_connect_p(void);
extern Object g2int_gsi_connection_error(int,...);
extern Object g2int_gsi_connection_error_no_exit(int,...);
extern Object g2int_gsi_connection_loss_notifier(Object,Object);
extern Object g2int_gsi_continue_from_error(void);
extern Object g2int_gsi_continue_run_loop(void);
extern Object g2int_gsi_current_context_number(void);
extern Object g2int_gsi_deregister_items_wrapper_for_known_sensor(Object,Object);
extern Object g2int_gsi_displaced_array_from_c_contents(Object,Object);
extern Object g2int_gsi_error(int,...);
extern Object g2int_gsi_error_no_exit(int,...);
extern Object g2int_gsi_event_cycle_handling_windows_quit(void);
extern Object g2int_gsi_event_wait(void);
extern Object g2int_gsi_failure_p(Object);
extern Object g2int_gsi_fatal_error(int,...);
extern Object g2int_gsi_flush_internal_1(Object,Object);
extern Object g2int_gsi_get_item_of_attribute_named(Object,Object);
extern Object g2int_gsi_get_network_configuration(int,...);
extern Object g2int_gsi_handle_error_1(Object,Object,Object);
extern Object g2int_gsi_init_error(int,...);
extern Object g2int_gsi_intern(Object);
extern Object g2int_gsi_item_is_value_p(Object);
extern Object g2int_gsi_last_converted_string(void);
extern Object g2int_gsi_make_appropriate_array(int,...);
extern Object g2int_gsi_make_array_for_user_or_gsi(Object,Object);
extern Object g2int_gsi_make_attributes_for_user_or_gsi(Object,Object);
extern Object g2int_gsi_make_attributes_with_items_for_user_or_gsi(Object,Object);
extern Object g2int_gsi_make_items_for_user_or_gsi(Object,Object);
extern Object g2int_gsi_managed_array_length(Object);
extern Object g2int_gsi_maybe_initiate_delayed_connection(Object);
extern Object g2int_gsi_maybe_notice_delayed_connection_failure(Object);
extern Object g2int_gsi_message(int,...);
extern Object g2int_gsi_no_connect_p(void);
extern Object g2int_gsi_no_listener_p(void);
extern Object g2int_gsi_option_is_set_p(Object);
extern Object g2int_gsi_priority_of_data_service_function(void);
extern Object g2int_gsi_push_onto_appropriate_list(int,...);
extern Object g2int_gsi_read_state_change(Object,Object);
extern Object g2int_gsi_reclaim_contents(Object,Object);
extern Object g2int_gsi_reclaim_displaced_array(Object);
extern Object g2int_gsi_reclaim_instance_value_array(Object,Object,Object);
extern Object g2int_gsi_reclaim_managed_array(Object);
extern Object g2int_gsi_return_attrs_internal(Object,Object,Object,Object);
extern Object g2int_gsi_return_values_internal(Object,Object,Object);
extern Object g2int_gsi_send_reply_to_initial_ping_internal(Object);
extern Object g2int_gsi_sensor_index(Object);
extern Object g2int_gsi_set_history_type(Object,Object);
extern Object g2int_gsi_set_last_converted_string(Object);
extern Object g2int_gsi_simple_content_copy_internal(Object,Object);
extern Object g2int_gsi_store_desired_tcp_port_number(Object);
extern Object g2int_gsi_string_for_symbol(Object,Object);
extern Object g2int_gsi_symbol_name_length(Object);
extern Object g2int_gsi_wakeup_maybe_initiate_delayed_connection(Object);
extern Object g2int_gsi_wakeup_maybe_notice_delayed_connection_failure(Object);
extern Object g2int_gsi_warning(int,...);
extern Object g2int_gsi_write_state_change(Object,Object);
extern Object g2int_handle_extend_current_text_string_error(void);
extern Object g2int_handle_watchdog_task(Object);
extern Object g2int_icp_connection_being_shutdownqm(Object);
extern Object g2int_icp_connection_is_secure(Object);
extern Object g2int_icp_connection_open_p(Object);
extern Object g2int_icp_error_internal(Object,Object,Object,Object,Object);
extern Object g2int_import_text_string_per_text_conversion_style(int,...);
extern Object g2int_initialize_gensym_time(void);
extern Object g2int_initialize_gsi(void);
extern Object g2int_initialize_gsi_context_number_table(Object);
extern Object g2int_initialize_scheduler(void);
extern Object g2int_initiate_gsi_connection(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_initiate_gsi_connection_after_connect(Object,Object,Object,Object,Object,Object);
extern Object g2int_initiate_gsi_wakeup_connection(void);
extern Object g2int_intern_gensym_string(int,...);
extern Object g2int_intern_text_string(int,...);
extern Object g2int_invalid_gsi_context_p(Object,Object);
extern Object g2int_launch_system_process(Object);
extern Object g2int_lengthw(Object);
extern Object g2int_lisp_string_to_c_string(Object);
extern Object g2int_lisp_string_to_c_unsigned_short_vector(Object);
extern Object g2int_lisp_string_to_c_wide_string(Object);
extern Object g2int_load_and_initialize_type_description(Object,Object);
extern Object g2int_load_gsi_application(Object);
extern Object g2int_load_library(Object,Object,Object);
extern Object g2int_load_library_for_gsi(Object);
extern Object g2int_lookup_attr_by_name_1(Object,Object);
extern Object g2int_make_and_install_network_listener(Object,Object);
extern Object g2int_make_default_gsi_application(void);
extern Object g2int_make_gensym_list_1(Object);
extern Object g2int_make_gsi_application_1(Object);
extern Object g2int_make_gsi_array_wrapper_1(Object,Object);
extern Object g2int_make_gsi_attribute(int,...);
extern Object g2int_make_gsi_attribute_1_1(Object,Object,Object);
extern Object g2int_make_gsi_attribute_for_user_or_gsi(Object);
extern Object g2int_make_gsi_circularity_table(void);
extern Object g2int_make_gsi_history(int,...);
extern Object g2int_make_gsi_history_1_1(Object,Object,Object,Object);
extern Object g2int_make_gsi_history_from_specification(Object,Object,Object);
extern Object g2int_make_gsi_instance(int,...);
extern Object g2int_make_gsi_instance_1_1(void);
extern Object g2int_make_gsi_instance_extension_1(void);
extern Object g2int_make_gsi_instance_for_user_or_gsi(Object);
extern Object g2int_make_gsi_sequence(Object);
extern Object g2int_make_gsi_structure(Object);
extern Object g2int_make_gsi_transfer_wrapper(void);
extern Object g2int_make_gsi_transfer_wrapper_1_1(Object,Object,Object,Object,Object);
extern Object g2int_make_gsi_user_transfer_wrapper(void);
extern Object g2int_make_localnet_connection(int,...);
extern Object g2int_make_network_connection(int,...);
extern Object g2int_make_network_pathname(Object);
extern Object g2int_make_permanent_gsi_application_structure_internal(void);
extern Object g2int_make_permanent_schedule_task_structure_internal(void);
extern Object g2int_make_transcode_purpose_array(Object,Object);
extern Object g2int_maybe_call_gsi_shutdown_context_callback(Object);
extern Object g2int_milliseconds_to_next_scheduler_event(void);
extern Object g2int_minimal_internal_error_given_format_info(Object,Object,Object);
extern Object g2int_mutate_global_property(Object,Object,Object);
extern Object g2int_namestring_as_gensym_string(Object);
extern Object g2int_next_icp_message_group(void);
extern Object g2int_notify_user_at_console(int,...);
extern Object g2int_obtain_simple_gensym_string(Object);
extern Object g2int_obtain_simple_text_string(Object);
extern Object g2int_pathname_gtshared_file_pathname(Object);
extern Object g2int_position_of_two_colons(Object);
extern Object g2int_protect_gsi_api_call_p(void);
extern Object g2int_reclaim_gensym_list_1(Object);
extern Object g2int_reclaim_gensym_pathname(Object);
extern Object g2int_reclaim_gensym_string(Object);
extern Object g2int_reclaim_gsi_application_1(Object);
extern Object g2int_reclaim_gsi_array_wrapper_1(Object);
extern Object g2int_reclaim_gsi_attribute(Object);
extern Object g2int_reclaim_gsi_attribute_1_1(Object);
extern Object g2int_reclaim_gsi_history(Object);
extern Object g2int_reclaim_gsi_history_1_1(Object);
extern Object g2int_reclaim_gsi_instance(Object,Object);
extern Object g2int_reclaim_gsi_instance_1_1(Object);
extern Object g2int_reclaim_gsi_instance_extension(Object,Object);
extern Object g2int_reclaim_gsi_instance_extension_1_1(Object);
extern Object g2int_reclaim_gsi_instance_for_context(Object);
extern Object g2int_reclaim_gsi_instance_for_gsi(Object);
extern Object g2int_reclaim_gsi_instance_for_user(Object);
extern Object g2int_reclaim_gsi_instance_value(Object,Object,Object,Object);
extern Object g2int_reclaim_gsi_remote_procedure(Object);
extern Object g2int_reclaim_gsi_remote_procedures(Object);
extern Object g2int_reclaim_gsi_transfer_wrapper(Object);
extern Object g2int_reclaim_gsi_transfer_wrapper_1_1(Object);
extern Object g2int_reclaim_gsi_transfer_wrapper_array(Object);
extern Object g2int_reclaim_gsi_user_attribute(Object);
extern Object g2int_reclaim_gsi_user_transfer_wrapper(Object);
extern Object g2int_reclaim_icp_object_map_for_gsi_instance(Object);
extern Object g2int_reclaim_icp_sockets(void);
extern Object g2int_reclaim_if_text_or_gensym_string_function(Object);
extern Object g2int_reclaim_list_of_local_functions(Object);
extern Object g2int_reclaim_managed_simple_float_array(Object);
extern Object g2int_reclaim_managed_simple_float_array_of_length_1(Object);
extern Object g2int_reclaim_managed_simple_long_array_of_length_1(Object);
extern Object g2int_reclaim_managed_simple_vector(Object);
extern Object g2int_reclaim_network_addresses(Object);
extern Object g2int_reclaim_resumable_attribute_spec_function(Object);
extern Object g2int_reclaim_schedule_task_args(Object);
extern Object g2int_reclaim_text_or_gensym_string(Object);
extern Object g2int_reclaim_text_string(Object);
extern Object g2int_reclaim_wide_string(Object);
extern Object g2int_record_direct_structure_method(Object,Object,Object);
extern Object g2int_record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_regenerate_optimized_constant(Object);
extern Object g2int_register_all_signal_handlers(void);
extern Object g2int_register_all_signal_handlers_unconditionally(void);
extern Object g2int_register_gsi_connection_callbacks(Object,Object);
extern Object g2int_register_icp_accept_callback(Object,Object);
extern Object g2int_register_icp_connection_loss_callback(Object,Object);
extern Object g2int_register_icp_read_callback(Object,Object);
extern Object g2int_register_icp_write_callback(Object,Object);
extern Object g2int_report_memory_usage(Object);
extern Object g2int_reset_counters_for_all_icp_sockets(void);
extern Object g2int_resumable_icp_pop(void);
extern Object g2int_resumable_icp_pop_list_if_end_marker(void);
extern Object g2int_resumable_icp_push(Object);
extern Object g2int_run_gsi(Object);
extern Object g2int_run_gsi_1(void);
extern Object g2int_run_gsi_process_top_level(Object);
extern Object g2int_run_one_gsi_scheduler_cycle(void);
extern Object g2int_run_system_process(Object,Object,Object);
extern Object g2int_schedule_processing_for_inhibited_messages(void);
extern Object g2int_secure_icp_requested_p(void);
extern Object g2int_secure_icp_string(int,...);
extern Object g2int_send_icp_initialize_gsi_interface(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_send_icp_nop(Object);
extern Object g2int_send_icp_receive_gsi_sensor_value_vector(Object,Object,Object,Object);
extern Object g2int_send_icp_receive_timestamped_gsi_sensor_value_vector(Object,Object,Object,Object,Object);
extern Object g2int_send_icp_receive_value_for_gsi_sensor(Object,Object,Object);
extern Object g2int_send_icp_receive_value_for_gsi_sensor_with_timestamp(Object,Object,Object,Object);
extern Object g2int_send_icp_receive_values_for_gsi_sensors(Object);
extern Object g2int_send_icp_receive_values_for_gsi_sensors_with_timestamp(Object);
extern Object g2int_send_icp_receive_values_for_gsi_sensors_without_timestamp(Object);
extern Object g2int_send_icp_write_user_message_string(Object,Object,Object,Object);
extern Object g2int_send_or_enqueue_icp_write_task(Object,Object,Object,Object,Object,Object);
extern Object g2int_set_gsi_attribute_is_identifying_p(Object,Object);
extern Object g2int_set_gsi_attribute_is_transient_p(Object,Object);
extern Object g2int_set_gsi_attribute_name(Object,Object);
extern Object g2int_set_gsi_current_application(Object);
extern Object g2int_set_gsi_error_message_1(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_set_gsi_instance_owner(Object,Object);
extern Object g2int_set_gsi_instance_plist_value(Object,Object,Object);
extern Object g2int_set_gsi_instance_value_type(Object,Object);
extern Object g2int_set_gsi_option(Object,Object);
extern Object g2int_set_up_lisp_memory_management(Object);
extern Object g2int_set_up_secure_icp(int,...);
extern Object g2int_setup_network_connection_for_connect(int,...);
extern Object g2int_shutdown_data_server_wrapper(void);
extern Object g2int_shutdown_icp_socket_connection(int,...);
extern Object g2int_shutdown_or_exit(int,...);
extern Object g2int_signal_gsi_extend_current_gensym_string_error(void);
extern Object g2int_signal_gsi_extend_current_text_string_error(void);
extern Object g2int_signal_gsi_icp_message_out_of_synch_case_2_error(void);
extern Object g2int_signal_gsi_icp_message_too_long_error(void);
extern Object g2int_signal_gsi_index_space_full_error(void);
extern Object g2int_signal_gsi_maximum_gensym_string_length_error(Object,Object);
extern Object g2int_signal_gsi_maximum_text_string_length_error(Object,Object);
extern Object g2int_signal_gsi_network_error(Object,Object);
extern Object g2int_signal_gsi_undefined_structure_method_error(void);
extern Object g2int_simple_or_null_value_type_p(Object);
extern Object g2int_simple_text_string_copy_from_attribute_name_1(Object,Object,Object);
extern Object g2int_string_equalw(Object,Object);
extern Object g2int_suitable_string_for_tcp_addressqm(Object);
extern Object g2int_symbol_for_gsi_string(Object);
extern Object g2int_symbol_name_text_string(Object);
extern Object g2int_text_conversion_style_for_gsi(Object,Object);
extern Object g2int_text_string_length(Object);
extern Object g2int_text_string_p(Object);
extern Object g2int_text_string_parse_integer_function(Object,Object,Object,Object);
extern Object g2int_text_string_substring(Object,Object,Object);
extern Object g2int_tformat(int,...);
extern Object g2int_tformat_text_string(int,...);
extern Object g2int_transfer_wrapper_components(Object,Object,Object);
extern Object g2int_unicode_lowercase_if_uppercase(Object);
extern Object g2int_update_server_certificate(Object);
extern Object g2int_visible_window_is_present_p(void);
extern Object g2int_wakeup_gsi_internal(void);
extern Object g2int_wide_string_to_gensym_string_for_gsi(Object);
extern Object g2int_write_icp_boolean(Object);
extern Object g2int_write_icp_byte(Object);
extern Object g2int_write_icp_fixnum(Object);
extern Object g2int_write_icp_gsi_timestamp(Object);
extern Object g2int_write_icp_gsi_value_vector(Object);
extern Object g2int_write_icp_gsi_values(Object);
extern Object g2int_write_icp_icp_tree(Object);
extern Object g2int_write_icp_remote_value(Object);
extern Object g2int_write_icp_returned_gsi_sensor(Object);
extern Object g2int_write_icp_text_string(Object);
extern Object g2int_write_icp_unsigned_integer(Object);
extern Object launch_gsi(void);

#else

extern Object g2int_abort();
extern Object g2int_abort_gsi_top_level();
extern Object g2int_add_vectors_to_gsi_history();
extern Object g2int_allocate_byte_vector_16();
extern Object g2int_allocate_gsi_context_number();
extern Object g2int_allocate_initialized_managed_simple_vector();
extern Object g2int_allocate_managed_long_box();
extern Object g2int_allocate_managed_simple_float_array();
extern Object g2int_allocate_managed_simple_vector();
extern Object g2int_announce_system_presence();
extern Object g2int_assq_function();
extern Object g2int_build_id_digit_offset();
extern Object g2int_build_id_letter_offset();
extern Object g2int_bytes_per_double_float_simple_array();
extern Object g2int_c_native_clock_ticks_or_cache();
extern Object g2int_c_string_to_gensym_string();
extern Object g2int_c_string_to_gsi_string();
extern Object g2int_c_string_to_text_string();
extern Object g2int_c_unsigned_short_vector_to_text_string();
extern Object g2int_c_wide_string_to_gensym_string();
extern Object g2int_c_wide_string_to_gsi_string();
extern Object g2int_c_wide_string_to_text_string();
extern Object g2int_cache_command_line_if_necessary();
extern Object g2int_call_gsi_callback();
extern Object g2int_call_gsi_close_fd_callback();
extern Object g2int_call_gsi_not_writing_fd_callback();
extern Object g2int_call_gsi_open_fd_callback();
extern Object g2int_call_gsi_writing_fd_callback();
extern Object g2int_cancel_and_reclaim_scheduled_queue_element_1();
extern Object g2int_check_gsi_value_vector();
extern Object g2int_check_transfer_wrapper();
extern Object g2int_chestnut_floorf_function();
extern Object g2int_clear_gsi_error_message();
extern Object g2int_close_and_disconnect_icp_socket_handle();
extern Object g2int_convert_gsi_value_to_value();
extern Object g2int_convert_value_to_gsi_value();
extern Object g2int_copy_constant_wide_string_given_length();
extern Object g2int_copy_gensym_string();
extern Object g2int_copy_managed_float();
extern Object g2int_copy_out_current_wide_string();
extern Object g2int_copy_partial_text_string();
extern Object g2int_copy_text_string();
extern Object g2int_create_transcode_text_conversion_style();
extern Object g2int_create_transfer_wrapper_array();
extern Object g2int_current_gsi_application();
extern Object g2int_current_gsi_string_conversion_style();
extern Object g2int_default_owner_for_gsi_objects();
extern Object g2int_delete_gensym_element_1();
extern Object g2int_dequeue_and_execute_next_task();
extern Object g2int_derive_network_listeners();
extern Object g2int_direct_structure_method();
extern Object g2int_do_not_catch_aborts_p();
extern Object g2int_element_type_for_gsi_type();
extern Object g2int_encode_build_identification_integer();
extern Object g2int_end_icp_message_group();
extern Object g2int_enlarge_index_space();
extern Object g2int_enqueue_scheduler_events_if_necessary();
extern Object g2int_enter_abyss();
extern Object g2int_entering_signal_handler_function();
extern Object g2int_equalw();
extern Object g2int_establish_gsi_listener();
extern Object g2int_establish_gsi_listeners();
extern Object g2int_establish_initial_gsi_listener();
extern Object g2int_export_text_string_per_text_conversion_style();
extern Object g2int_filter_text_for_gsi_p();
extern Object g2int_finalize_and_reclaim_icp_socket();
extern Object g2int_find_or_load_gsi_application();
extern Object g2int_fixnum_time_interval();
extern Object g2int_flush_and_shutdown_icp_socket();
extern Object g2int_flush_icp_output_ports();
extern Object g2int_future_task_schedule_2();
extern Object g2int_g2_event_ready_p();
extern Object g2int_g2_unrecoverable_error_exit();
extern Object g2int_generate_float_vector();
extern Object g2int_gensym_cons_1();
extern Object g2int_gensym_decode_unix_time();
extern Object g2int_gensym_encode_unix_time_as_managed_float();
extern Object g2int_gensym_list_2();
extern Object g2int_gensym_list_3();
extern Object g2int_gensym_list_4();
extern Object g2int_gensym_make_pathname_with_copied_components();
extern Object g2int_gensym_string_to_wide_string_for_gsi();
extern Object g2int_get_command_line_flag_argument();
extern Object g2int_get_command_line_keyword_argument();
extern Object g2int_get_command_line_keyword_argument_as_integer();
extern Object g2int_get_connect_address_from_command_line();
extern Object g2int_get_from_icp_port_if_any();
extern Object g2int_get_gensym_command_line_argument();
extern Object g2int_get_gensym_command_line_argument_as_text_string();
extern Object g2int_get_gensym_command_line_argument_count();
extern Object g2int_get_gsi_instance_plist_value();
extern Object g2int_get_icp_object_index_for_gsi_instance();
extern Object g2int_get_icp_socket_from_context();
extern Object g2int_get_instance_for_read_1();
extern Object g2int_get_instance_for_write_1();
extern Object g2int_get_listener_from_command_line();
extern Object g2int_get_local_host_addresses();
extern Object g2int_get_local_host_name();
extern Object g2int_get_network_listener();
extern Object g2int_get_preset_tcp_port_number();
extern Object g2int_get_remote_g2_time_at_start();
extern Object g2int_get_remote_home_name();
extern Object g2int_get_remote_host_name();
extern Object g2int_get_remote_listener_port();
extern Object g2int_get_tcp_listener_port_number();
extern Object g2int_getfq_function_no_default();
extern Object g2int_gsi_allocate_managed_array();
extern Object g2int_gsi_api_symbol_to_symbol_or_nil_1();
extern Object g2int_gsi_application_for_socket();
extern Object g2int_gsi_attribute_qualified_name();
extern Object g2int_gsi_connect_p();
extern Object g2int_gsi_connection_error();
extern Object g2int_gsi_connection_error_no_exit();
extern Object g2int_gsi_connection_loss_notifier();
extern Object g2int_gsi_continue_from_error();
extern Object g2int_gsi_continue_run_loop();
extern Object g2int_gsi_current_context_number();
extern Object g2int_gsi_deregister_items_wrapper_for_known_sensor();
extern Object g2int_gsi_displaced_array_from_c_contents();
extern Object g2int_gsi_error();
extern Object g2int_gsi_error_no_exit();
extern Object g2int_gsi_event_cycle_handling_windows_quit();
extern Object g2int_gsi_event_wait();
extern Object g2int_gsi_failure_p();
extern Object g2int_gsi_fatal_error();
extern Object g2int_gsi_flush_internal_1();
extern Object g2int_gsi_get_item_of_attribute_named();
extern Object g2int_gsi_get_network_configuration();
extern Object g2int_gsi_handle_error_1();
extern Object g2int_gsi_init_error();
extern Object g2int_gsi_intern();
extern Object g2int_gsi_item_is_value_p();
extern Object g2int_gsi_last_converted_string();
extern Object g2int_gsi_make_appropriate_array();
extern Object g2int_gsi_make_array_for_user_or_gsi();
extern Object g2int_gsi_make_attributes_for_user_or_gsi();
extern Object g2int_gsi_make_attributes_with_items_for_user_or_gsi();
extern Object g2int_gsi_make_items_for_user_or_gsi();
extern Object g2int_gsi_managed_array_length();
extern Object g2int_gsi_maybe_initiate_delayed_connection();
extern Object g2int_gsi_maybe_notice_delayed_connection_failure();
extern Object g2int_gsi_message();
extern Object g2int_gsi_no_connect_p();
extern Object g2int_gsi_no_listener_p();
extern Object g2int_gsi_option_is_set_p();
extern Object g2int_gsi_priority_of_data_service_function();
extern Object g2int_gsi_push_onto_appropriate_list();
extern Object g2int_gsi_read_state_change();
extern Object g2int_gsi_reclaim_contents();
extern Object g2int_gsi_reclaim_displaced_array();
extern Object g2int_gsi_reclaim_instance_value_array();
extern Object g2int_gsi_reclaim_managed_array();
extern Object g2int_gsi_return_attrs_internal();
extern Object g2int_gsi_return_values_internal();
extern Object g2int_gsi_send_reply_to_initial_ping_internal();
extern Object g2int_gsi_sensor_index();
extern Object g2int_gsi_set_history_type();
extern Object g2int_gsi_set_last_converted_string();
extern Object g2int_gsi_simple_content_copy_internal();
extern Object g2int_gsi_store_desired_tcp_port_number();
extern Object g2int_gsi_string_for_symbol();
extern Object g2int_gsi_symbol_name_length();
extern Object g2int_gsi_wakeup_maybe_initiate_delayed_connection();
extern Object g2int_gsi_wakeup_maybe_notice_delayed_connection_failure();
extern Object g2int_gsi_warning();
extern Object g2int_gsi_write_state_change();
extern Object g2int_handle_extend_current_text_string_error();
extern Object g2int_handle_watchdog_task();
extern Object g2int_icp_connection_being_shutdownqm();
extern Object g2int_icp_connection_is_secure();
extern Object g2int_icp_connection_open_p();
extern Object g2int_icp_error_internal();
extern Object g2int_import_text_string_per_text_conversion_style();
extern Object g2int_initialize_gensym_time();
extern Object g2int_initialize_gsi();
extern Object g2int_initialize_gsi_context_number_table();
extern Object g2int_initialize_scheduler();
extern Object g2int_initiate_gsi_connection();
extern Object g2int_initiate_gsi_connection_after_connect();
extern Object g2int_initiate_gsi_wakeup_connection();
extern Object g2int_intern_gensym_string();
extern Object g2int_intern_text_string();
extern Object g2int_invalid_gsi_context_p();
extern Object g2int_launch_system_process();
extern Object g2int_lengthw();
extern Object g2int_lisp_string_to_c_string();
extern Object g2int_lisp_string_to_c_unsigned_short_vector();
extern Object g2int_lisp_string_to_c_wide_string();
extern Object g2int_load_and_initialize_type_description();
extern Object g2int_load_gsi_application();
extern Object g2int_load_library();
extern Object g2int_load_library_for_gsi();
extern Object g2int_lookup_attr_by_name_1();
extern Object g2int_make_and_install_network_listener();
extern Object g2int_make_default_gsi_application();
extern Object g2int_make_gensym_list_1();
extern Object g2int_make_gsi_application_1();
extern Object g2int_make_gsi_array_wrapper_1();
extern Object g2int_make_gsi_attribute();
extern Object g2int_make_gsi_attribute_1_1();
extern Object g2int_make_gsi_attribute_for_user_or_gsi();
extern Object g2int_make_gsi_circularity_table();
extern Object g2int_make_gsi_history();
extern Object g2int_make_gsi_history_1_1();
extern Object g2int_make_gsi_history_from_specification();
extern Object g2int_make_gsi_instance();
extern Object g2int_make_gsi_instance_1_1();
extern Object g2int_make_gsi_instance_extension_1();
extern Object g2int_make_gsi_instance_for_user_or_gsi();
extern Object g2int_make_gsi_sequence();
extern Object g2int_make_gsi_structure();
extern Object g2int_make_gsi_transfer_wrapper();
extern Object g2int_make_gsi_transfer_wrapper_1_1();
extern Object g2int_make_gsi_user_transfer_wrapper();
extern Object g2int_make_localnet_connection();
extern Object g2int_make_network_connection();
extern Object g2int_make_network_pathname();
extern Object g2int_make_permanent_gsi_application_structure_internal();
extern Object g2int_make_permanent_schedule_task_structure_internal();
extern Object g2int_make_transcode_purpose_array();
extern Object g2int_maybe_call_gsi_shutdown_context_callback();
extern Object g2int_milliseconds_to_next_scheduler_event();
extern Object g2int_minimal_internal_error_given_format_info();
extern Object g2int_mutate_global_property();
extern Object g2int_namestring_as_gensym_string();
extern Object g2int_next_icp_message_group();
extern Object g2int_notify_user_at_console();
extern Object g2int_obtain_simple_gensym_string();
extern Object g2int_obtain_simple_text_string();
extern Object g2int_pathname_gtshared_file_pathname();
extern Object g2int_position_of_two_colons();
extern Object g2int_protect_gsi_api_call_p();
extern Object g2int_reclaim_gensym_list_1();
extern Object g2int_reclaim_gensym_pathname();
extern Object g2int_reclaim_gensym_string();
extern Object g2int_reclaim_gsi_application_1();
extern Object g2int_reclaim_gsi_array_wrapper_1();
extern Object g2int_reclaim_gsi_attribute();
extern Object g2int_reclaim_gsi_attribute_1_1();
extern Object g2int_reclaim_gsi_history();
extern Object g2int_reclaim_gsi_history_1_1();
extern Object g2int_reclaim_gsi_instance();
extern Object g2int_reclaim_gsi_instance_1_1();
extern Object g2int_reclaim_gsi_instance_extension();
extern Object g2int_reclaim_gsi_instance_extension_1_1();
extern Object g2int_reclaim_gsi_instance_for_context();
extern Object g2int_reclaim_gsi_instance_for_gsi();
extern Object g2int_reclaim_gsi_instance_for_user();
extern Object g2int_reclaim_gsi_instance_value();
extern Object g2int_reclaim_gsi_remote_procedure();
extern Object g2int_reclaim_gsi_remote_procedures();
extern Object g2int_reclaim_gsi_transfer_wrapper();
extern Object g2int_reclaim_gsi_transfer_wrapper_1_1();
extern Object g2int_reclaim_gsi_transfer_wrapper_array();
extern Object g2int_reclaim_gsi_user_attribute();
extern Object g2int_reclaim_gsi_user_transfer_wrapper();
extern Object g2int_reclaim_icp_object_map_for_gsi_instance();
extern Object g2int_reclaim_icp_sockets();
extern Object g2int_reclaim_if_text_or_gensym_string_function();
extern Object g2int_reclaim_list_of_local_functions();
extern Object g2int_reclaim_managed_simple_float_array();
extern Object g2int_reclaim_managed_simple_float_array_of_length_1();
extern Object g2int_reclaim_managed_simple_long_array_of_length_1();
extern Object g2int_reclaim_managed_simple_vector();
extern Object g2int_reclaim_network_addresses();
extern Object g2int_reclaim_resumable_attribute_spec_function();
extern Object g2int_reclaim_schedule_task_args();
extern Object g2int_reclaim_text_or_gensym_string();
extern Object g2int_reclaim_text_string();
extern Object g2int_reclaim_wide_string();
extern Object g2int_record_direct_structure_method();
extern Object g2int_record_system_variable();
extern Object g2int_regenerate_optimized_constant();
extern Object g2int_register_all_signal_handlers();
extern Object g2int_register_all_signal_handlers_unconditionally();
extern Object g2int_register_gsi_connection_callbacks();
extern Object g2int_register_icp_accept_callback();
extern Object g2int_register_icp_connection_loss_callback();
extern Object g2int_register_icp_read_callback();
extern Object g2int_register_icp_write_callback();
extern Object g2int_report_memory_usage();
extern Object g2int_reset_counters_for_all_icp_sockets();
extern Object g2int_resumable_icp_pop();
extern Object g2int_resumable_icp_pop_list_if_end_marker();
extern Object g2int_resumable_icp_push();
extern Object g2int_run_gsi();
extern Object g2int_run_gsi_1();
extern Object g2int_run_gsi_process_top_level();
extern Object g2int_run_one_gsi_scheduler_cycle();
extern Object g2int_run_system_process();
extern Object g2int_schedule_processing_for_inhibited_messages();
extern Object g2int_secure_icp_requested_p();
extern Object g2int_secure_icp_string();
extern Object g2int_send_icp_initialize_gsi_interface();
extern Object g2int_send_icp_nop();
extern Object g2int_send_icp_receive_gsi_sensor_value_vector();
extern Object g2int_send_icp_receive_timestamped_gsi_sensor_value_vector();
extern Object g2int_send_icp_receive_value_for_gsi_sensor();
extern Object g2int_send_icp_receive_value_for_gsi_sensor_with_timestamp();
extern Object g2int_send_icp_receive_values_for_gsi_sensors();
extern Object g2int_send_icp_receive_values_for_gsi_sensors_with_timestamp();
extern Object g2int_send_icp_receive_values_for_gsi_sensors_without_timestamp();
extern Object g2int_send_icp_write_user_message_string();
extern Object g2int_send_or_enqueue_icp_write_task();
extern Object g2int_set_gsi_attribute_is_identifying_p();
extern Object g2int_set_gsi_attribute_is_transient_p();
extern Object g2int_set_gsi_attribute_name();
extern Object g2int_set_gsi_current_application();
extern Object g2int_set_gsi_error_message_1();
extern Object g2int_set_gsi_instance_owner();
extern Object g2int_set_gsi_instance_plist_value();
extern Object g2int_set_gsi_instance_value_type();
extern Object g2int_set_gsi_option();
extern Object g2int_set_up_lisp_memory_management();
extern Object g2int_set_up_secure_icp();
extern Object g2int_setup_network_connection_for_connect();
extern Object g2int_shutdown_data_server_wrapper();
extern Object g2int_shutdown_icp_socket_connection();
extern Object g2int_shutdown_or_exit();
extern Object g2int_signal_gsi_extend_current_gensym_string_error();
extern Object g2int_signal_gsi_extend_current_text_string_error();
extern Object g2int_signal_gsi_icp_message_out_of_synch_case_2_error();
extern Object g2int_signal_gsi_icp_message_too_long_error();
extern Object g2int_signal_gsi_index_space_full_error();
extern Object g2int_signal_gsi_maximum_gensym_string_length_error();
extern Object g2int_signal_gsi_maximum_text_string_length_error();
extern Object g2int_signal_gsi_network_error();
extern Object g2int_signal_gsi_undefined_structure_method_error();
extern Object g2int_simple_or_null_value_type_p();
extern Object g2int_simple_text_string_copy_from_attribute_name_1();
extern Object g2int_string_equalw();
extern Object g2int_suitable_string_for_tcp_addressqm();
extern Object g2int_symbol_for_gsi_string();
extern Object g2int_symbol_name_text_string();
extern Object g2int_text_conversion_style_for_gsi();
extern Object g2int_text_string_length();
extern Object g2int_text_string_p();
extern Object g2int_text_string_parse_integer_function();
extern Object g2int_text_string_substring();
extern Object g2int_tformat();
extern Object g2int_tformat_text_string();
extern Object g2int_transfer_wrapper_components();
extern Object g2int_unicode_lowercase_if_uppercase();
extern Object g2int_update_server_certificate();
extern Object g2int_visible_window_is_present_p();
extern Object g2int_wakeup_gsi_internal();
extern Object g2int_wide_string_to_gensym_string_for_gsi();
extern Object g2int_write_icp_boolean();
extern Object g2int_write_icp_byte();
extern Object g2int_write_icp_fixnum();
extern Object g2int_write_icp_gsi_timestamp();
extern Object g2int_write_icp_gsi_value_vector();
extern Object g2int_write_icp_gsi_values();
extern Object g2int_write_icp_icp_tree();
extern Object g2int_write_icp_remote_value();
extern Object g2int_write_icp_returned_gsi_sensor();
extern Object g2int_write_icp_text_string();
extern Object g2int_write_icp_unsigned_integer();
extern Object launch_gsi();

#endif

/* Externally callable routines */

#ifdef USE_PROTOTYPES

extern SI_Long g2int_shared_gsi_attr_array_index_of(Object);
extern Object g2int_shared_gsi_attr_by_name(Object,Object,Object);
extern SI_Long g2int_shared_gsi_attr_count_of(Object);
extern SI_Long g2int_shared_gsi_attr_is_array_index(Object);
extern SI_Long g2int_shared_gsi_attr_is_identifying(Object);
extern SI_Long g2int_shared_gsi_attr_is_list_index(Object);
extern SI_Long g2int_shared_gsi_attr_is_transient(Object);
extern SI_Long g2int_shared_gsi_attr_list_index_of(Object);
extern SI_Long g2int_shared_gsi_attr_name_is_qualified(Object);
extern Object g2int_shared_gsi_attr_name_of(Object,Object);
extern Object g2int_shared_gsi_attrs_of(Object);
extern SI_Long g2int_shared_gsi_build_id_integer(void);
extern Object g2int_shared_gsi_class_name_of(Object,Object);
extern Object g2int_shared_gsi_class_qualifier_of(Object,Object);
extern SI_Long g2int_shared_gsi_class_type_of(Object);
extern void g2int_shared_gsi_clear_item(Object);
extern void g2int_shared_gsi_clear_last_error(void);
extern void g2int_shared_gsi_close_listeners(void);
extern SI_Long g2int_shared_gsi_context_is_secure(SI_Long);
extern SI_Long g2int_shared_gsi_context_received_data(SI_Long);
extern Object g2int_shared_gsi_context_remote_home(SI_Long);
extern Object g2int_shared_gsi_context_remote_host(Object,SI_Long);
extern SI_Long g2int_shared_gsi_context_remote_port(SI_Long);
extern double g2int_shared_gsi_context_remote_start_time(SI_Long);
extern SI_Long g2int_shared_gsi_context_socket(SI_Long);
extern Object g2int_shared_gsi_context_user_data(SI_Long);
extern Object g2int_shared_gsi_convert_str_to_ustr(Object,Object,SI_Long);
extern Object g2int_shared_gsi_convert_ustr_to_str(Object,Object,SI_Long);
extern Object g2int_shared_gsi_convert_ustr_to_wstr(Object,Object,SI_Long);
extern Object g2int_shared_gsi_convert_wstr_to_ustr(Object,Object,SI_Long);
extern SI_Long g2int_shared_gsi_current_context(void);
extern SI_Long g2int_shared_gsi_current_context_is_secure(void);
extern void g2int_shared_gsi_decode_timestamp(double,Object,Object,Object,Object,Object,Object);
extern SI_Long g2int_shared_gsi_element_count_of(Object);
extern Object g2int_shared_gsi_elements_of(Object);
extern double g2int_shared_gsi_encode_timestamp(SI_Long,SI_Long,SI_Long,SI_Long,SI_Long,SI_Long);
extern Object g2int_shared_gsi_error_message(Object,SI_Long);
extern SI_Long g2int_shared_gsi_establish_listener(Object,Object,Object,SI_Long);
extern SI_Long g2int_shared_gsi_establish_secure_listener(Object,Object,Object,SI_Long,Object);
extern void g2int_shared_gsi_extract_history(Object,Object,Object,Object);
extern void g2int_shared_gsi_extract_history_spec(Object,Object,Object,Object);
extern Object g2int_shared_gsi_flt_array_of(Object);
extern Object g2int_shared_gsi_flt_list_of(Object);
extern double g2int_shared_gsi_flt_of(Object);
extern void g2int_shared_gsi_flush(SI_Long);
extern SI_Long g2int_shared_gsi_handle_of(Object);
extern SI_Long g2int_shared_gsi_has_network_connections(void);
extern SI_Long g2int_shared_gsi_history_count_of(Object);
extern Object g2int_shared_gsi_i64_of(Object);
extern void g2int_shared_gsi_initialize_callback(Object,Object,Object);
extern void g2int_shared_gsi_initialize_error_variable(Object);
extern SI_Long g2int_shared_gsi_initiate_connection(Object,Object,Object,SI_Long,Object,Object,Object,Object);
extern SI_Long g2int_shared_gsi_initiate_connection_w_u_d(Object,Object,Object,SI_Long,Object,Object,Object,Object,Object);
extern SI_Long g2int_shared_gsi_initiate_secure_conn_w_u_d(Object,Object,Object,SI_Long,Object,Object,Object,Object,Object);
extern SI_Long g2int_shared_gsi_initiate_secure_connection(Object,Object,Object,SI_Long,Object,Object,Object,Object);
extern Object g2int_shared_gsi_int_array_of(Object);
extern Object g2int_shared_gsi_int_list_of(Object);
extern SI_Long g2int_shared_gsi_int_of(Object);
extern double g2int_shared_gsi_interval_of(Object);
extern SI_Long g2int_shared_gsi_is_idle(void);
extern SI_Long g2int_shared_gsi_is_item(Object);
extern int g2int_shared_gsi_item_append_flag(Object);
extern int g2int_shared_gsi_item_class_is_ident_flag(Object);
extern int g2int_shared_gsi_item_delete_flag(Object);
extern SI_Long g2int_shared_gsi_item_has_a_value(Object);
extern int g2int_shared_gsi_item_name_is_ident_flag(Object);
extern Object g2int_shared_gsi_item_of_attr(Object);
extern Object g2int_shared_gsi_item_of_attr_by_name(Object,Object,Object);
extern Object g2int_shared_gsi_item_of_identifying_attr_of(Object,SI_Long);
extern Object g2int_shared_gsi_item_of_registered_item(Object);
extern int g2int_shared_gsi_item_reference_flag(Object);
extern void g2int_shared_gsi_kill_context(SI_Long);
extern SI_Long g2int_shared_gsi_last_error(void);
extern Object g2int_shared_gsi_last_error_call_handle(void);
extern Object g2int_shared_gsi_last_error_message(Object);
extern SI_Long g2int_shared_gsi_listener_socket(void);
extern Object g2int_shared_gsi_log_array_of(Object);
extern Object g2int_shared_gsi_log_list_of(Object);
extern SI_Long g2int_shared_gsi_log_of(Object);
extern SI_Long g2int_shared_gsi_major_version(void);
extern Object g2int_shared_gsi_make_array(SI_Long);
extern Object g2int_shared_gsi_make_attrs(SI_Long);
extern Object g2int_shared_gsi_make_attrs_with_items(SI_Long);
extern Object g2int_shared_gsi_make_item(void);
extern Object g2int_shared_gsi_make_items(SI_Long);
extern Object g2int_shared_gsi_make_registered_items(SI_Long);
extern Object g2int_shared_gsi_make_symbol(Object,Object);
extern SI_Long g2int_shared_gsi_minor_version(void);
extern Object g2int_shared_gsi_name_of(Object,Object);
extern int g2int_shared_gsi_option_is_set(int);
extern SI_Long g2int_shared_gsi_owner_of(Object);
extern void g2int_shared_gsi_pause(void);
extern void g2int_shared_gsi_reclaim_array(Object);
extern void g2int_shared_gsi_reclaim_attrs(Object);
extern void g2int_shared_gsi_reclaim_attrs_with_items(Object);
extern void g2int_shared_gsi_reclaim_item(Object);
extern void g2int_shared_gsi_reclaim_items(Object);
extern void g2int_shared_gsi_reclaim_registered_items(Object);
extern Object g2int_shared_gsi_registration_of_handle(SI_Long,SI_Long);
extern Object g2int_shared_gsi_registration_of_item(Object);
extern SI_Long g2int_shared_gsi_release_quality(void);
extern void g2int_shared_gsi_reset_option(int);
extern void g2int_shared_gsi_return_attrs(Object,Object,SI_Long,SI_Long);
extern void g2int_shared_gsi_return_message(Object,Object,SI_Long);
extern void g2int_shared_gsi_return_timed_attrs(Object,Object,SI_Long,SI_Long);
extern void g2int_shared_gsi_return_timed_values(Object,SI_Long,SI_Long);
extern void g2int_shared_gsi_return_values(Object,SI_Long,SI_Long);
extern SI_Long g2int_shared_gsi_revision_number(void);
extern void g2int_shared_gsi_run_loop(void);
extern void g2int_shared_gsi_set_attr_array_index(Object,SI_Long);
extern void g2int_shared_gsi_set_attr_by_name(Object,Object,Object,Object);
extern void g2int_shared_gsi_set_attr_count(Object,SI_Long);
extern void g2int_shared_gsi_set_attr_is_identifying(Object,SI_Long);
extern void g2int_shared_gsi_set_attr_is_transient(Object,SI_Long);
extern void g2int_shared_gsi_set_attr_list_index(Object,SI_Long);
extern void g2int_shared_gsi_set_attr_name(Object,Object,Object);
extern void g2int_shared_gsi_set_attrs(Object,Object,SI_Long);
extern void g2int_shared_gsi_set_class_name(Object,Object,Object);
extern void g2int_shared_gsi_set_class_qualifier(Object,Object,Object);
extern void g2int_shared_gsi_set_class_type(Object,SI_Long);
extern void g2int_shared_gsi_set_context_limit(SI_Long);
extern void g2int_shared_gsi_set_context_user_data(SI_Long,Object);
extern void g2int_shared_gsi_set_current_application(Object,Object);
extern void g2int_shared_gsi_set_element_count(Object,SI_Long);
extern void g2int_shared_gsi_set_elements(Object,Object,SI_Long,SI_Long);
extern void g2int_shared_gsi_set_flt(Object,double);
extern void g2int_shared_gsi_set_flt_array(Object,Object,SI_Long);
extern void g2int_shared_gsi_set_flt_list(Object,Object,SI_Long);
extern void g2int_shared_gsi_set_handle(Object,SI_Long);
extern void g2int_shared_gsi_set_history(Object,Object,Object,Object,SI_Long,SI_Long,SI_Long,SI_Long,SI_Long);
extern void g2int_shared_gsi_set_i64(Object,Object);
extern void g2int_shared_gsi_set_int(Object,SI_Long);
extern void g2int_shared_gsi_set_int_array(Object,Object,SI_Long);
extern void g2int_shared_gsi_set_int_list(Object,Object,SI_Long);
extern void g2int_shared_gsi_set_interval(Object,double);
extern void g2int_shared_gsi_set_item_append_flag(Object,int);
extern void g2int_shared_gsi_set_item_class_is_iden_flag(Object,int);
extern void g2int_shared_gsi_set_item_delete_flag(Object,int);
extern void g2int_shared_gsi_set_item_name_is_ident_flag(Object,int);
extern void g2int_shared_gsi_set_item_of_attr(Object,Object);
extern void g2int_shared_gsi_set_item_of_attr_by_name(Object,Object,Object,Object);
extern void g2int_shared_gsi_set_item_reference_flag(Object,int);
extern void g2int_shared_gsi_set_local_home(Object);
extern void g2int_shared_gsi_set_log(Object,SI_Long);
extern void g2int_shared_gsi_set_log_array(Object,Object,SI_Long);
extern void g2int_shared_gsi_set_log_list(Object,Object,SI_Long);
extern void g2int_shared_gsi_set_name(Object,Object,Object);
extern void g2int_shared_gsi_set_option(int);
extern void g2int_shared_gsi_set_pause_timeout(SI_Long);
extern void g2int_shared_gsi_set_run_loop_timeout(SI_Long);
extern void g2int_shared_gsi_set_status(Object,SI_Long);
extern void g2int_shared_gsi_set_str(Object,Object,Object);
extern void g2int_shared_gsi_set_str_array(Object,Object,Object,SI_Long);
extern void g2int_shared_gsi_set_str_list(Object,Object,Object,SI_Long);
extern void g2int_shared_gsi_set_string_conversion_style(SI_Long);
extern void g2int_shared_gsi_set_sym(Object,Object,Object);
extern void g2int_shared_gsi_set_sym_array(Object,Object,Object,SI_Long);
extern void g2int_shared_gsi_set_sym_list(Object,Object,Object,SI_Long);
extern void g2int_shared_gsi_set_symbol_user_data(Object,Object,Object);
extern void g2int_shared_gsi_set_timestamp(Object,double);
extern void g2int_shared_gsi_set_type(Object,SI_Long);
extern void g2int_shared_gsi_set_unqualified_attr_name(Object,Object,Object);
extern void g2int_shared_gsi_set_update_items_flag(Object,int);
extern void g2int_shared_gsi_set_user_data(Object,Object);
extern void g2int_shared_gsi_set_usv(Object,Object,SI_Long);
extern void g2int_shared_gsi_signal_error(Object,Object,SI_Long,Object);
extern void g2int_shared_gsi_simple_content_copy(Object,Object);
extern void g2int_shared_gsi_start(SI_Long,Object);
extern SI_Long g2int_shared_gsi_status_of(Object);
extern Object g2int_shared_gsi_str_array_of(Object,Object);
extern Object g2int_shared_gsi_str_list_of(Object,Object);
extern Object g2int_shared_gsi_str_of(Object,Object);
extern SI_Long g2int_shared_gsi_string_conversion_style(void);
extern Object g2int_shared_gsi_sym_array_of(Object,Object);
extern Object g2int_shared_gsi_sym_list_of(Object,Object);
extern Object g2int_shared_gsi_sym_of(Object,Object);
extern Object g2int_shared_gsi_symbol_name(Object,Object);
extern Object g2int_shared_gsi_symbol_user_data(Object,Object);
extern double g2int_shared_gsi_timestamp_of(Object);
extern SI_Long g2int_shared_gsi_type_of(Object);
extern Object g2int_shared_gsi_unqualified_attr_name_of(Object,Object);
extern int g2int_shared_gsi_update_items_flag(Object);
extern Object g2int_shared_gsi_user_data_of(Object);
extern Object g2int_shared_gsi_usv_of(Object,Object);
extern SI_Long g2int_shared_gsi_wakeup(void);
extern void g2int_shared_gsi_watchdog(Object,int);
extern Object g2int_shared_gsin_close_fd(Object);
extern Object g2int_shared_gsin_error_handler(Object);
extern Object g2int_shared_gsin_g2_poll(Object);
extern Object g2int_shared_gsin_get_data(Object);
extern Object g2int_shared_gsin_get_tcp_port(Object);
extern Object g2int_shared_gsin_idle(Object);
extern Object g2int_shared_gsin_initialize_context(Object);
extern Object g2int_shared_gsin_missing_procedure_handler(Object);
extern Object g2int_shared_gsin_not_writing_fd(Object);
extern Object g2int_shared_gsin_open_fd(Object);
extern Object g2int_shared_gsin_pause_context(Object);
extern Object g2int_shared_gsin_read_callback(Object);
extern Object g2int_shared_gsin_receive_deregistrations(Object);
extern Object g2int_shared_gsin_receive_message(Object);
extern Object g2int_shared_gsin_receive_registration(Object);
extern Object g2int_shared_gsin_reset_context(Object);
extern Object g2int_shared_gsin_resume_context(Object);
extern Object g2int_shared_gsin_run_state_change(Object);
extern Object g2int_shared_gsin_set_data(Object);
extern Object g2int_shared_gsin_set_up(Object);
extern Object g2int_shared_gsin_shutdown_context(Object);
extern Object g2int_shared_gsin_start_context(Object);
extern Object g2int_shared_gsin_watchdog_function(Object);
extern Object g2int_shared_gsin_write_callback(Object);
extern Object g2int_shared_gsin_writing_fd(Object);
DLLEXPORT extern SI_Long gsi_attr_array_index_of(Object);
DLLEXPORT extern Object gsi_attr_by_name(Object,Object);
DLLEXPORT extern SI_Long gsi_attr_count_of(Object);
DLLEXPORT extern SI_Long gsi_attr_is_array_index(Object);
DLLEXPORT extern SI_Long gsi_attr_is_identifying(Object);
DLLEXPORT extern SI_Long gsi_attr_is_list_index(Object);
DLLEXPORT extern SI_Long gsi_attr_is_transient(Object);
DLLEXPORT extern SI_Long gsi_attr_list_index_of(Object);
DLLEXPORT extern SI_Long gsi_attr_name_is_qualified(Object);
DLLEXPORT extern Object gsi_attr_name_of(Object);
DLLEXPORT extern Object gsi_attrs_of(Object);
DLLEXPORT extern SI_Long gsi_build_id_integer(void);
DLLEXPORT extern Object gsi_class_name_of(Object);
DLLEXPORT extern Object gsi_class_qualifier_of(Object);
DLLEXPORT extern SI_Long gsi_class_type_of(Object);
DLLEXPORT extern void gsi_clear_item(Object);
DLLEXPORT extern void gsi_clear_last_error(void);
DLLEXPORT extern void gsi_close_listeners(void);
DLLEXPORT extern SI_Long gsi_context_is_secure(SI_Long);
DLLEXPORT extern SI_Long gsi_context_received_data(SI_Long);
DLLEXPORT extern Object gsi_context_remote_home(SI_Long);
DLLEXPORT extern Object gsi_context_remote_host(SI_Long);
DLLEXPORT extern SI_Long gsi_context_remote_port(SI_Long);
DLLEXPORT extern double gsi_context_remote_start_time(SI_Long);
DLLEXPORT extern SI_Long gsi_context_socket(SI_Long);
DLLEXPORT extern Object gsi_context_user_data(SI_Long);
DLLEXPORT extern Object gsi_convert_str_to_ustr(Object,SI_Long);
DLLEXPORT extern Object gsi_convert_ustr_to_str(Object,SI_Long);
DLLEXPORT extern Object gsi_convert_ustr_to_wstr(Object,SI_Long);
DLLEXPORT extern Object gsi_convert_wstr_to_ustr(Object,SI_Long);
DLLEXPORT extern SI_Long gsi_current_context(void);
DLLEXPORT extern SI_Long gsi_current_context_is_secure(void);
DLLEXPORT extern void gsi_decode_timestamp(double,Object,Object,Object,Object,Object,Object);
DLLEXPORT extern SI_Long gsi_element_count_of(Object);
DLLEXPORT extern Object gsi_elements_of(Object);
DLLEXPORT extern double gsi_encode_timestamp(SI_Long,SI_Long,SI_Long,SI_Long,SI_Long,SI_Long);
DLLEXPORT extern Object gsi_error_message(SI_Long);
DLLEXPORT extern SI_Long gsi_establish_listener(Object,Object,SI_Long);
DLLEXPORT extern SI_Long gsi_establish_secure_listener(Object,Object,SI_Long,Object);
DLLEXPORT extern void gsi_extract_history(Object,Object,Object,Object);
DLLEXPORT extern void gsi_extract_history_spec(Object,Object,Object,Object);
DLLEXPORT extern Object gsi_flt_array_of(Object);
DLLEXPORT extern Object gsi_flt_list_of(Object);
DLLEXPORT extern double gsi_flt_of(Object);
DLLEXPORT extern void gsi_flush(SI_Long);
DLLEXPORT extern SI_Long gsi_handle_of(Object);
DLLEXPORT extern SI_Long gsi_has_network_connections(void);
DLLEXPORT extern SI_Long gsi_history_count_of(Object);
DLLEXPORT extern Object gsi_i64_of(Object);
DLLEXPORT extern void gsi_initialize_callback(Object,Object);
DLLEXPORT extern void gsi_initialize_error_variable(Object);
DLLEXPORT extern SI_Long gsi_initiate_connection(Object,Object,SI_Long,Object,Object,Object,Object);
DLLEXPORT extern SI_Long gsi_initiate_connection_w_u_d(Object,Object,SI_Long,Object,Object,Object,Object,Object);
DLLEXPORT extern SI_Long gsi_initiate_secure_conn_w_u_d(Object,Object,SI_Long,Object,Object,Object,Object,Object);
DLLEXPORT extern SI_Long gsi_initiate_secure_connection(Object,Object,SI_Long,Object,Object,Object,Object);
DLLEXPORT extern Object gsi_int_array_of(Object);
DLLEXPORT extern Object gsi_int_list_of(Object);
DLLEXPORT extern SI_Long gsi_int_of(Object);
DLLEXPORT extern double gsi_interval_of(Object);
DLLEXPORT extern SI_Long gsi_is_idle(void);
DLLEXPORT extern SI_Long gsi_is_item(Object);
DLLEXPORT extern int gsi_item_append_flag(Object);
DLLEXPORT extern int gsi_item_class_is_ident_flag(Object);
DLLEXPORT extern int gsi_item_delete_flag(Object);
DLLEXPORT extern SI_Long gsi_item_has_a_value(Object);
DLLEXPORT extern int gsi_item_name_is_ident_flag(Object);
DLLEXPORT extern Object gsi_item_of_attr(Object);
DLLEXPORT extern Object gsi_item_of_attr_by_name(Object,Object);
DLLEXPORT extern Object gsi_item_of_identifying_attr_of(Object,SI_Long);
DLLEXPORT extern Object gsi_item_of_registered_item(Object);
DLLEXPORT extern int gsi_item_reference_flag(Object);
DLLEXPORT extern void gsi_kill_context(SI_Long);
DLLEXPORT extern SI_Long gsi_last_error(void);
DLLEXPORT extern Object gsi_last_error_call_handle(void);
DLLEXPORT extern Object gsi_last_error_message(void);
DLLEXPORT extern SI_Long gsi_listener_socket(void);
DLLEXPORT extern Object gsi_log_array_of(Object);
DLLEXPORT extern Object gsi_log_list_of(Object);
DLLEXPORT extern SI_Long gsi_log_of(Object);
DLLEXPORT extern SI_Long gsi_major_version(void);
DLLEXPORT extern Object gsi_make_array(SI_Long);
DLLEXPORT extern Object gsi_make_attrs(SI_Long);
DLLEXPORT extern Object gsi_make_attrs_with_items(SI_Long);
DLLEXPORT extern Object gsi_make_item(void);
DLLEXPORT extern Object gsi_make_items(SI_Long);
DLLEXPORT extern Object gsi_make_registered_items(SI_Long);
DLLEXPORT extern Object gsi_make_symbol(Object);
DLLEXPORT extern SI_Long gsi_minor_version(void);
DLLEXPORT extern Object gsi_name_of(Object);
DLLEXPORT extern int gsi_option_is_set(int);
DLLEXPORT extern SI_Long gsi_owner_of(Object);
DLLEXPORT extern void gsi_pause(void);
DLLEXPORT extern void gsi_reclaim_array(Object);
DLLEXPORT extern void gsi_reclaim_attrs(Object);
DLLEXPORT extern void gsi_reclaim_attrs_with_items(Object);
DLLEXPORT extern void gsi_reclaim_item(Object);
DLLEXPORT extern void gsi_reclaim_items(Object);
DLLEXPORT extern void gsi_reclaim_registered_items(Object);
DLLEXPORT extern Object gsi_registration_of_handle(SI_Long,SI_Long);
DLLEXPORT extern Object gsi_registration_of_item(Object);
DLLEXPORT extern SI_Long gsi_release_quality(void);
DLLEXPORT extern void gsi_reset_option(int);
DLLEXPORT extern void gsi_return_attrs(Object,Object,SI_Long,SI_Long);
DLLEXPORT extern void gsi_return_message(Object,SI_Long);
DLLEXPORT extern void gsi_return_timed_attrs(Object,Object,SI_Long,SI_Long);
DLLEXPORT extern void gsi_return_timed_values(Object,SI_Long,SI_Long);
DLLEXPORT extern void gsi_return_values(Object,SI_Long,SI_Long);
DLLEXPORT extern SI_Long gsi_revision_number(void);
DLLEXPORT extern void gsi_run_loop(void);
DLLEXPORT extern void gsi_set_attr_array_index(Object,SI_Long);
DLLEXPORT extern void gsi_set_attr_by_name(Object,Object,Object);
DLLEXPORT extern void gsi_set_attr_count(Object,SI_Long);
DLLEXPORT extern void gsi_set_attr_is_identifying(Object,SI_Long);
DLLEXPORT extern void gsi_set_attr_is_transient(Object,SI_Long);
DLLEXPORT extern void gsi_set_attr_list_index(Object,SI_Long);
DLLEXPORT extern void gsi_set_attr_name(Object,Object);
DLLEXPORT extern void gsi_set_attrs(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_class_name(Object,Object);
DLLEXPORT extern void gsi_set_class_qualifier(Object,Object);
DLLEXPORT extern void gsi_set_class_type(Object,SI_Long);
DLLEXPORT extern void gsi_set_context_limit(SI_Long);
DLLEXPORT extern void gsi_set_context_user_data(SI_Long,Object);
DLLEXPORT extern void gsi_set_current_application(Object);
DLLEXPORT extern void gsi_set_element_count(Object,SI_Long);
DLLEXPORT extern void gsi_set_elements(Object,Object,SI_Long,SI_Long);
DLLEXPORT extern void gsi_set_flt(Object,double);
DLLEXPORT extern void gsi_set_flt_array(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_flt_list(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_handle(Object,SI_Long);
DLLEXPORT extern void gsi_set_history(Object,Object,Object,SI_Long,SI_Long,SI_Long,SI_Long,SI_Long);
DLLEXPORT extern void gsi_set_i64(Object,Object);
DLLEXPORT extern void gsi_set_int(Object,SI_Long);
DLLEXPORT extern void gsi_set_int_array(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_int_list(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_interval(Object,double);
DLLEXPORT extern void gsi_set_item_append_flag(Object,int);
DLLEXPORT extern void gsi_set_item_class_is_iden_flag(Object,int);
DLLEXPORT extern void gsi_set_item_delete_flag(Object,int);
DLLEXPORT extern void gsi_set_item_name_is_ident_flag(Object,int);
DLLEXPORT extern void gsi_set_item_of_attr(Object,Object);
DLLEXPORT extern void gsi_set_item_of_attr_by_name(Object,Object,Object);
DLLEXPORT extern void gsi_set_item_reference_flag(Object,int);
DLLEXPORT extern void gsi_set_local_home(Object);
DLLEXPORT extern void gsi_set_log(Object,SI_Long);
DLLEXPORT extern void gsi_set_log_array(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_log_list(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_name(Object,Object);
DLLEXPORT extern void gsi_set_option(int);
DLLEXPORT extern void gsi_set_pause_timeout(SI_Long);
DLLEXPORT extern void gsi_set_run_loop_timeout(SI_Long);
DLLEXPORT extern void gsi_set_status(Object,SI_Long);
DLLEXPORT extern void gsi_set_str(Object,Object);
DLLEXPORT extern void gsi_set_str_array(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_str_list(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_string_conversion_style(SI_Long);
DLLEXPORT extern void gsi_set_sym(Object,Object);
DLLEXPORT extern void gsi_set_sym_array(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_sym_list(Object,Object,SI_Long);
DLLEXPORT extern void gsi_set_symbol_user_data(Object,Object);
DLLEXPORT extern void gsi_set_timestamp(Object,double);
DLLEXPORT extern void gsi_set_type(Object,SI_Long);
DLLEXPORT extern void gsi_set_unqualified_attr_name(Object,Object);
DLLEXPORT extern void gsi_set_update_items_flag(Object,int);
DLLEXPORT extern void gsi_set_user_data(Object,Object);
DLLEXPORT extern void gsi_set_usv(Object,Object,SI_Long);
DLLEXPORT extern void gsi_signal_error(Object,SI_Long,Object);
DLLEXPORT extern void gsi_simple_content_copy(Object,Object);
DLLEXPORT extern void gsi_start(SI_Long,Object);
DLLEXPORT extern SI_Long gsi_status_of(Object);
DLLEXPORT extern Object gsi_str_array_of(Object);
DLLEXPORT extern Object gsi_str_list_of(Object);
DLLEXPORT extern Object gsi_str_of(Object);
DLLEXPORT extern SI_Long gsi_string_conversion_style(void);
DLLEXPORT extern Object gsi_sym_array_of(Object);
DLLEXPORT extern Object gsi_sym_list_of(Object);
DLLEXPORT extern Object gsi_sym_of(Object);
DLLEXPORT extern Object gsi_symbol_name(Object);
DLLEXPORT extern Object gsi_symbol_user_data(Object);
DLLEXPORT extern double gsi_timestamp_of(Object);
DLLEXPORT extern SI_Long gsi_type_of(Object);
DLLEXPORT extern Object gsi_unqualified_attr_name_of(Object);
DLLEXPORT extern int gsi_update_items_flag(Object);
DLLEXPORT extern Object gsi_user_data_of(Object);
DLLEXPORT extern Object gsi_usv_of(Object);
DLLEXPORT extern SI_Long gsi_wakeup(void);
DLLEXPORT extern void gsi_watchdog(Object,int);
DLLEXPORT extern Object gsin_close_fd(void);
DLLEXPORT extern Object gsin_error_handler(void);
DLLEXPORT extern Object gsin_g2_poll(void);
DLLEXPORT extern Object gsin_get_data(void);
DLLEXPORT extern Object gsin_get_tcp_port(void);
DLLEXPORT extern Object gsin_idle(void);
DLLEXPORT extern Object gsin_initialize_context(void);
DLLEXPORT extern Object gsin_missing_procedure_handler(void);
DLLEXPORT extern Object gsin_not_writing_fd(void);
DLLEXPORT extern Object gsin_open_fd(void);
DLLEXPORT extern Object gsin_pause_context(void);
DLLEXPORT extern Object gsin_read_callback(void);
DLLEXPORT extern Object gsin_receive_deregistrations(void);
DLLEXPORT extern Object gsin_receive_message(void);
DLLEXPORT extern Object gsin_receive_registration(void);
DLLEXPORT extern Object gsin_reset_context(void);
DLLEXPORT extern Object gsin_resume_context(void);
DLLEXPORT extern Object gsin_run_state_change(void);
DLLEXPORT extern Object gsin_set_data(void);
DLLEXPORT extern Object gsin_set_up(void);
DLLEXPORT extern Object gsin_shutdown_context(void);
DLLEXPORT extern Object gsin_start_context(void);
DLLEXPORT extern Object gsin_watchdog_function(void);
DLLEXPORT extern Object gsin_write_callback(void);
DLLEXPORT extern Object gsin_writing_fd(void);

#else

extern SI_Long g2int_shared_gsi_attr_array_index_of();
extern Object g2int_shared_gsi_attr_by_name();
extern SI_Long g2int_shared_gsi_attr_count_of();
extern SI_Long g2int_shared_gsi_attr_is_array_index();
extern SI_Long g2int_shared_gsi_attr_is_identifying();
extern SI_Long g2int_shared_gsi_attr_is_list_index();
extern SI_Long g2int_shared_gsi_attr_is_transient();
extern SI_Long g2int_shared_gsi_attr_list_index_of();
extern SI_Long g2int_shared_gsi_attr_name_is_qualified();
extern Object g2int_shared_gsi_attr_name_of();
extern Object g2int_shared_gsi_attrs_of();
extern SI_Long g2int_shared_gsi_build_id_integer();
extern Object g2int_shared_gsi_class_name_of();
extern Object g2int_shared_gsi_class_qualifier_of();
extern SI_Long g2int_shared_gsi_class_type_of();
extern void g2int_shared_gsi_clear_item();
extern void g2int_shared_gsi_clear_last_error();
extern void g2int_shared_gsi_close_listeners();
extern SI_Long g2int_shared_gsi_context_is_secure();
extern SI_Long g2int_shared_gsi_context_received_data();
extern Object g2int_shared_gsi_context_remote_home();
extern Object g2int_shared_gsi_context_remote_host();
extern SI_Long g2int_shared_gsi_context_remote_port();
extern double g2int_shared_gsi_context_remote_start_time();
extern SI_Long g2int_shared_gsi_context_socket();
extern Object g2int_shared_gsi_context_user_data();
extern Object g2int_shared_gsi_convert_str_to_ustr();
extern Object g2int_shared_gsi_convert_ustr_to_str();
extern Object g2int_shared_gsi_convert_ustr_to_wstr();
extern Object g2int_shared_gsi_convert_wstr_to_ustr();
extern SI_Long g2int_shared_gsi_current_context();
extern SI_Long g2int_shared_gsi_current_context_is_secure();
extern void g2int_shared_gsi_decode_timestamp();
extern SI_Long g2int_shared_gsi_element_count_of();
extern Object g2int_shared_gsi_elements_of();
extern double g2int_shared_gsi_encode_timestamp();
extern Object g2int_shared_gsi_error_message();
extern SI_Long g2int_shared_gsi_establish_listener();
extern SI_Long g2int_shared_gsi_establish_secure_listener();
extern void g2int_shared_gsi_extract_history();
extern void g2int_shared_gsi_extract_history_spec();
extern Object g2int_shared_gsi_flt_array_of();
extern Object g2int_shared_gsi_flt_list_of();
extern double g2int_shared_gsi_flt_of();
extern void g2int_shared_gsi_flush();
extern SI_Long g2int_shared_gsi_handle_of();
extern SI_Long g2int_shared_gsi_has_network_connections();
extern SI_Long g2int_shared_gsi_history_count_of();
extern Object g2int_shared_gsi_i64_of();
extern void g2int_shared_gsi_initialize_callback();
extern void g2int_shared_gsi_initialize_error_variable();
extern SI_Long g2int_shared_gsi_initiate_connection();
extern SI_Long g2int_shared_gsi_initiate_connection_w_u_d();
extern SI_Long g2int_shared_gsi_initiate_secure_conn_w_u_d();
extern SI_Long g2int_shared_gsi_initiate_secure_connection();
extern Object g2int_shared_gsi_int_array_of();
extern Object g2int_shared_gsi_int_list_of();
extern SI_Long g2int_shared_gsi_int_of();
extern double g2int_shared_gsi_interval_of();
extern SI_Long g2int_shared_gsi_is_idle();
extern SI_Long g2int_shared_gsi_is_item();
extern int g2int_shared_gsi_item_append_flag();
extern int g2int_shared_gsi_item_class_is_ident_flag();
extern int g2int_shared_gsi_item_delete_flag();
extern SI_Long g2int_shared_gsi_item_has_a_value();
extern int g2int_shared_gsi_item_name_is_ident_flag();
extern Object g2int_shared_gsi_item_of_attr();
extern Object g2int_shared_gsi_item_of_attr_by_name();
extern Object g2int_shared_gsi_item_of_identifying_attr_of();
extern Object g2int_shared_gsi_item_of_registered_item();
extern int g2int_shared_gsi_item_reference_flag();
extern void g2int_shared_gsi_kill_context();
extern SI_Long g2int_shared_gsi_last_error();
extern Object g2int_shared_gsi_last_error_call_handle();
extern Object g2int_shared_gsi_last_error_message();
extern SI_Long g2int_shared_gsi_listener_socket();
extern Object g2int_shared_gsi_log_array_of();
extern Object g2int_shared_gsi_log_list_of();
extern SI_Long g2int_shared_gsi_log_of();
extern SI_Long g2int_shared_gsi_major_version();
extern Object g2int_shared_gsi_make_array();
extern Object g2int_shared_gsi_make_attrs();
extern Object g2int_shared_gsi_make_attrs_with_items();
extern Object g2int_shared_gsi_make_item();
extern Object g2int_shared_gsi_make_items();
extern Object g2int_shared_gsi_make_registered_items();
extern Object g2int_shared_gsi_make_symbol();
extern SI_Long g2int_shared_gsi_minor_version();
extern Object g2int_shared_gsi_name_of();
extern int g2int_shared_gsi_option_is_set();
extern SI_Long g2int_shared_gsi_owner_of();
extern void g2int_shared_gsi_pause();
extern void g2int_shared_gsi_reclaim_array();
extern void g2int_shared_gsi_reclaim_attrs();
extern void g2int_shared_gsi_reclaim_attrs_with_items();
extern void g2int_shared_gsi_reclaim_item();
extern void g2int_shared_gsi_reclaim_items();
extern void g2int_shared_gsi_reclaim_registered_items();
extern Object g2int_shared_gsi_registration_of_handle();
extern Object g2int_shared_gsi_registration_of_item();
extern SI_Long g2int_shared_gsi_release_quality();
extern void g2int_shared_gsi_reset_option();
extern void g2int_shared_gsi_return_attrs();
extern void g2int_shared_gsi_return_message();
extern void g2int_shared_gsi_return_timed_attrs();
extern void g2int_shared_gsi_return_timed_values();
extern void g2int_shared_gsi_return_values();
extern SI_Long g2int_shared_gsi_revision_number();
extern void g2int_shared_gsi_run_loop();
extern void g2int_shared_gsi_set_attr_array_index();
extern void g2int_shared_gsi_set_attr_by_name();
extern void g2int_shared_gsi_set_attr_count();
extern void g2int_shared_gsi_set_attr_is_identifying();
extern void g2int_shared_gsi_set_attr_is_transient();
extern void g2int_shared_gsi_set_attr_list_index();
extern void g2int_shared_gsi_set_attr_name();
extern void g2int_shared_gsi_set_attrs();
extern void g2int_shared_gsi_set_class_name();
extern void g2int_shared_gsi_set_class_qualifier();
extern void g2int_shared_gsi_set_class_type();
extern void g2int_shared_gsi_set_context_limit();
extern void g2int_shared_gsi_set_context_user_data();
extern void g2int_shared_gsi_set_current_application();
extern void g2int_shared_gsi_set_element_count();
extern void g2int_shared_gsi_set_elements();
extern void g2int_shared_gsi_set_flt();
extern void g2int_shared_gsi_set_flt_array();
extern void g2int_shared_gsi_set_flt_list();
extern void g2int_shared_gsi_set_handle();
extern void g2int_shared_gsi_set_history();
extern void g2int_shared_gsi_set_i64();
extern void g2int_shared_gsi_set_int();
extern void g2int_shared_gsi_set_int_array();
extern void g2int_shared_gsi_set_int_list();
extern void g2int_shared_gsi_set_interval();
extern void g2int_shared_gsi_set_item_append_flag();
extern void g2int_shared_gsi_set_item_class_is_iden_flag();
extern void g2int_shared_gsi_set_item_delete_flag();
extern void g2int_shared_gsi_set_item_name_is_ident_flag();
extern void g2int_shared_gsi_set_item_of_attr();
extern void g2int_shared_gsi_set_item_of_attr_by_name();
extern void g2int_shared_gsi_set_item_reference_flag();
extern void g2int_shared_gsi_set_local_home();
extern void g2int_shared_gsi_set_log();
extern void g2int_shared_gsi_set_log_array();
extern void g2int_shared_gsi_set_log_list();
extern void g2int_shared_gsi_set_name();
extern void g2int_shared_gsi_set_option();
extern void g2int_shared_gsi_set_pause_timeout();
extern void g2int_shared_gsi_set_run_loop_timeout();
extern void g2int_shared_gsi_set_status();
extern void g2int_shared_gsi_set_str();
extern void g2int_shared_gsi_set_str_array();
extern void g2int_shared_gsi_set_str_list();
extern void g2int_shared_gsi_set_string_conversion_style();
extern void g2int_shared_gsi_set_sym();
extern void g2int_shared_gsi_set_sym_array();
extern void g2int_shared_gsi_set_sym_list();
extern void g2int_shared_gsi_set_symbol_user_data();
extern void g2int_shared_gsi_set_timestamp();
extern void g2int_shared_gsi_set_type();
extern void g2int_shared_gsi_set_unqualified_attr_name();
extern void g2int_shared_gsi_set_update_items_flag();
extern void g2int_shared_gsi_set_user_data();
extern void g2int_shared_gsi_set_usv();
extern void g2int_shared_gsi_signal_error();
extern void g2int_shared_gsi_simple_content_copy();
extern void g2int_shared_gsi_start();
extern SI_Long g2int_shared_gsi_status_of();
extern Object g2int_shared_gsi_str_array_of();
extern Object g2int_shared_gsi_str_list_of();
extern Object g2int_shared_gsi_str_of();
extern SI_Long g2int_shared_gsi_string_conversion_style();
extern Object g2int_shared_gsi_sym_array_of();
extern Object g2int_shared_gsi_sym_list_of();
extern Object g2int_shared_gsi_sym_of();
extern Object g2int_shared_gsi_symbol_name();
extern Object g2int_shared_gsi_symbol_user_data();
extern double g2int_shared_gsi_timestamp_of();
extern SI_Long g2int_shared_gsi_type_of();
extern Object g2int_shared_gsi_unqualified_attr_name_of();
extern int g2int_shared_gsi_update_items_flag();
extern Object g2int_shared_gsi_user_data_of();
extern Object g2int_shared_gsi_usv_of();
extern SI_Long g2int_shared_gsi_wakeup();
extern void g2int_shared_gsi_watchdog();
extern Object g2int_shared_gsin_close_fd();
extern Object g2int_shared_gsin_error_handler();
extern Object g2int_shared_gsin_g2_poll();
extern Object g2int_shared_gsin_get_data();
extern Object g2int_shared_gsin_get_tcp_port();
extern Object g2int_shared_gsin_idle();
extern Object g2int_shared_gsin_initialize_context();
extern Object g2int_shared_gsin_missing_procedure_handler();
extern Object g2int_shared_gsin_not_writing_fd();
extern Object g2int_shared_gsin_open_fd();
extern Object g2int_shared_gsin_pause_context();
extern Object g2int_shared_gsin_read_callback();
extern Object g2int_shared_gsin_receive_deregistrations();
extern Object g2int_shared_gsin_receive_message();
extern Object g2int_shared_gsin_receive_registration();
extern Object g2int_shared_gsin_reset_context();
extern Object g2int_shared_gsin_resume_context();
extern Object g2int_shared_gsin_run_state_change();
extern Object g2int_shared_gsin_set_data();
extern Object g2int_shared_gsin_set_up();
extern Object g2int_shared_gsin_shutdown_context();
extern Object g2int_shared_gsin_start_context();
extern Object g2int_shared_gsin_watchdog_function();
extern Object g2int_shared_gsin_write_callback();
extern Object g2int_shared_gsin_writing_fd();
DLLEXPORT extern SI_Long gsi_attr_array_index_of();
DLLEXPORT extern Object gsi_attr_by_name();
DLLEXPORT extern SI_Long gsi_attr_count_of();
DLLEXPORT extern SI_Long gsi_attr_is_array_index();
DLLEXPORT extern SI_Long gsi_attr_is_identifying();
DLLEXPORT extern SI_Long gsi_attr_is_list_index();
DLLEXPORT extern SI_Long gsi_attr_is_transient();
DLLEXPORT extern SI_Long gsi_attr_list_index_of();
DLLEXPORT extern SI_Long gsi_attr_name_is_qualified();
DLLEXPORT extern Object gsi_attr_name_of();
DLLEXPORT extern Object gsi_attrs_of();
DLLEXPORT extern SI_Long gsi_build_id_integer();
DLLEXPORT extern Object gsi_class_name_of();
DLLEXPORT extern Object gsi_class_qualifier_of();
DLLEXPORT extern SI_Long gsi_class_type_of();
DLLEXPORT extern void gsi_clear_item();
DLLEXPORT extern void gsi_clear_last_error();
DLLEXPORT extern void gsi_close_listeners();
DLLEXPORT extern SI_Long gsi_context_is_secure();
DLLEXPORT extern SI_Long gsi_context_received_data();
DLLEXPORT extern Object gsi_context_remote_home();
DLLEXPORT extern Object gsi_context_remote_host();
DLLEXPORT extern SI_Long gsi_context_remote_port();
DLLEXPORT extern double gsi_context_remote_start_time();
DLLEXPORT extern SI_Long gsi_context_socket();
DLLEXPORT extern Object gsi_context_user_data();
DLLEXPORT extern Object gsi_convert_str_to_ustr();
DLLEXPORT extern Object gsi_convert_ustr_to_str();
DLLEXPORT extern Object gsi_convert_ustr_to_wstr();
DLLEXPORT extern Object gsi_convert_wstr_to_ustr();
DLLEXPORT extern SI_Long gsi_current_context();
DLLEXPORT extern SI_Long gsi_current_context_is_secure();
DLLEXPORT extern void gsi_decode_timestamp();
DLLEXPORT extern SI_Long gsi_element_count_of();
DLLEXPORT extern Object gsi_elements_of();
DLLEXPORT extern double gsi_encode_timestamp();
DLLEXPORT extern Object gsi_error_message();
DLLEXPORT extern SI_Long gsi_establish_listener();
DLLEXPORT extern SI_Long gsi_establish_secure_listener();
DLLEXPORT extern void gsi_extract_history();
DLLEXPORT extern void gsi_extract_history_spec();
DLLEXPORT extern Object gsi_flt_array_of();
DLLEXPORT extern Object gsi_flt_list_of();
DLLEXPORT extern double gsi_flt_of();
DLLEXPORT extern void gsi_flush();
DLLEXPORT extern SI_Long gsi_handle_of();
DLLEXPORT extern SI_Long gsi_has_network_connections();
DLLEXPORT extern SI_Long gsi_history_count_of();
DLLEXPORT extern Object gsi_i64_of();
DLLEXPORT extern void gsi_initialize_callback();
DLLEXPORT extern void gsi_initialize_error_variable();
DLLEXPORT extern SI_Long gsi_initiate_connection();
DLLEXPORT extern SI_Long gsi_initiate_connection_w_u_d();
DLLEXPORT extern SI_Long gsi_initiate_secure_conn_w_u_d();
DLLEXPORT extern SI_Long gsi_initiate_secure_connection();
DLLEXPORT extern Object gsi_int_array_of();
DLLEXPORT extern Object gsi_int_list_of();
DLLEXPORT extern SI_Long gsi_int_of();
DLLEXPORT extern double gsi_interval_of();
DLLEXPORT extern SI_Long gsi_is_idle();
DLLEXPORT extern SI_Long gsi_is_item();
DLLEXPORT extern int gsi_item_append_flag();
DLLEXPORT extern int gsi_item_class_is_ident_flag();
DLLEXPORT extern int gsi_item_delete_flag();
DLLEXPORT extern SI_Long gsi_item_has_a_value();
DLLEXPORT extern int gsi_item_name_is_ident_flag();
DLLEXPORT extern Object gsi_item_of_attr();
DLLEXPORT extern Object gsi_item_of_attr_by_name();
DLLEXPORT extern Object gsi_item_of_identifying_attr_of();
DLLEXPORT extern Object gsi_item_of_registered_item();
DLLEXPORT extern int gsi_item_reference_flag();
DLLEXPORT extern void gsi_kill_context();
DLLEXPORT extern SI_Long gsi_last_error();
DLLEXPORT extern Object gsi_last_error_call_handle();
DLLEXPORT extern Object gsi_last_error_message();
DLLEXPORT extern SI_Long gsi_listener_socket();
DLLEXPORT extern Object gsi_log_array_of();
DLLEXPORT extern Object gsi_log_list_of();
DLLEXPORT extern SI_Long gsi_log_of();
DLLEXPORT extern SI_Long gsi_major_version();
DLLEXPORT extern Object gsi_make_array();
DLLEXPORT extern Object gsi_make_attrs();
DLLEXPORT extern Object gsi_make_attrs_with_items();
DLLEXPORT extern Object gsi_make_item();
DLLEXPORT extern Object gsi_make_items();
DLLEXPORT extern Object gsi_make_registered_items();
DLLEXPORT extern Object gsi_make_symbol();
DLLEXPORT extern SI_Long gsi_minor_version();
DLLEXPORT extern Object gsi_name_of();
DLLEXPORT extern int gsi_option_is_set();
DLLEXPORT extern SI_Long gsi_owner_of();
DLLEXPORT extern void gsi_pause();
DLLEXPORT extern void gsi_reclaim_array();
DLLEXPORT extern void gsi_reclaim_attrs();
DLLEXPORT extern void gsi_reclaim_attrs_with_items();
DLLEXPORT extern void gsi_reclaim_item();
DLLEXPORT extern void gsi_reclaim_items();
DLLEXPORT extern void gsi_reclaim_registered_items();
DLLEXPORT extern Object gsi_registration_of_handle();
DLLEXPORT extern Object gsi_registration_of_item();
DLLEXPORT extern SI_Long gsi_release_quality();
DLLEXPORT extern void gsi_reset_option();
DLLEXPORT extern void gsi_return_attrs();
DLLEXPORT extern void gsi_return_message();
DLLEXPORT extern void gsi_return_timed_attrs();
DLLEXPORT extern void gsi_return_timed_values();
DLLEXPORT extern void gsi_return_values();
DLLEXPORT extern SI_Long gsi_revision_number();
DLLEXPORT extern void gsi_run_loop();
DLLEXPORT extern void gsi_set_attr_array_index();
DLLEXPORT extern void gsi_set_attr_by_name();
DLLEXPORT extern void gsi_set_attr_count();
DLLEXPORT extern void gsi_set_attr_is_identifying();
DLLEXPORT extern void gsi_set_attr_is_transient();
DLLEXPORT extern void gsi_set_attr_list_index();
DLLEXPORT extern void gsi_set_attr_name();
DLLEXPORT extern void gsi_set_attrs();
DLLEXPORT extern void gsi_set_class_name();
DLLEXPORT extern void gsi_set_class_qualifier();
DLLEXPORT extern void gsi_set_class_type();
DLLEXPORT extern void gsi_set_context_limit();
DLLEXPORT extern void gsi_set_context_user_data();
DLLEXPORT extern void gsi_set_current_application();
DLLEXPORT extern void gsi_set_element_count();
DLLEXPORT extern void gsi_set_elements();
DLLEXPORT extern void gsi_set_flt();
DLLEXPORT extern void gsi_set_flt_array();
DLLEXPORT extern void gsi_set_flt_list();
DLLEXPORT extern void gsi_set_handle();
DLLEXPORT extern void gsi_set_history();
DLLEXPORT extern void gsi_set_i64();
DLLEXPORT extern void gsi_set_int();
DLLEXPORT extern void gsi_set_int_array();
DLLEXPORT extern void gsi_set_int_list();
DLLEXPORT extern void gsi_set_interval();
DLLEXPORT extern void gsi_set_item_append_flag();
DLLEXPORT extern void gsi_set_item_class_is_iden_flag();
DLLEXPORT extern void gsi_set_item_delete_flag();
DLLEXPORT extern void gsi_set_item_name_is_ident_flag();
DLLEXPORT extern void gsi_set_item_of_attr();
DLLEXPORT extern void gsi_set_item_of_attr_by_name();
DLLEXPORT extern void gsi_set_item_reference_flag();
DLLEXPORT extern void gsi_set_local_home();
DLLEXPORT extern void gsi_set_log();
DLLEXPORT extern void gsi_set_log_array();
DLLEXPORT extern void gsi_set_log_list();
DLLEXPORT extern void gsi_set_name();
DLLEXPORT extern void gsi_set_option();
DLLEXPORT extern void gsi_set_pause_timeout();
DLLEXPORT extern void gsi_set_run_loop_timeout();
DLLEXPORT extern void gsi_set_status();
DLLEXPORT extern void gsi_set_str();
DLLEXPORT extern void gsi_set_str_array();
DLLEXPORT extern void gsi_set_str_list();
DLLEXPORT extern void gsi_set_string_conversion_style();
DLLEXPORT extern void gsi_set_sym();
DLLEXPORT extern void gsi_set_sym_array();
DLLEXPORT extern void gsi_set_sym_list();
DLLEXPORT extern void gsi_set_symbol_user_data();
DLLEXPORT extern void gsi_set_timestamp();
DLLEXPORT extern void gsi_set_type();
DLLEXPORT extern void gsi_set_unqualified_attr_name();
DLLEXPORT extern void gsi_set_update_items_flag();
DLLEXPORT extern void gsi_set_user_data();
DLLEXPORT extern void gsi_set_usv();
DLLEXPORT extern void gsi_signal_error();
DLLEXPORT extern void gsi_simple_content_copy();
DLLEXPORT extern void gsi_start();
DLLEXPORT extern SI_Long gsi_status_of();
DLLEXPORT extern Object gsi_str_array_of();
DLLEXPORT extern Object gsi_str_list_of();
DLLEXPORT extern Object gsi_str_of();
DLLEXPORT extern SI_Long gsi_string_conversion_style();
DLLEXPORT extern Object gsi_sym_array_of();
DLLEXPORT extern Object gsi_sym_list_of();
DLLEXPORT extern Object gsi_sym_of();
DLLEXPORT extern Object gsi_symbol_name();
DLLEXPORT extern Object gsi_symbol_user_data();
DLLEXPORT extern double gsi_timestamp_of();
DLLEXPORT extern SI_Long gsi_type_of();
DLLEXPORT extern Object gsi_unqualified_attr_name_of();
DLLEXPORT extern int gsi_update_items_flag();
DLLEXPORT extern Object gsi_user_data_of();
DLLEXPORT extern Object gsi_usv_of();
DLLEXPORT extern SI_Long gsi_wakeup();
DLLEXPORT extern void gsi_watchdog();
DLLEXPORT extern Object gsin_close_fd();
DLLEXPORT extern Object gsin_error_handler();
DLLEXPORT extern Object gsin_g2_poll();
DLLEXPORT extern Object gsin_get_data();
DLLEXPORT extern Object gsin_get_tcp_port();
DLLEXPORT extern Object gsin_idle();
DLLEXPORT extern Object gsin_initialize_context();
DLLEXPORT extern Object gsin_missing_procedure_handler();
DLLEXPORT extern Object gsin_not_writing_fd();
DLLEXPORT extern Object gsin_open_fd();
DLLEXPORT extern Object gsin_pause_context();
DLLEXPORT extern Object gsin_read_callback();
DLLEXPORT extern Object gsin_receive_deregistrations();
DLLEXPORT extern Object gsin_receive_message();
DLLEXPORT extern Object gsin_receive_registration();
DLLEXPORT extern Object gsin_reset_context();
DLLEXPORT extern Object gsin_resume_context();
DLLEXPORT extern Object gsin_run_state_change();
DLLEXPORT extern Object gsin_set_data();
DLLEXPORT extern Object gsin_set_up();
DLLEXPORT extern Object gsin_shutdown_context();
DLLEXPORT extern Object gsin_start_context();
DLLEXPORT extern Object gsin_watchdog_function();
DLLEXPORT extern Object gsin_write_callback();
DLLEXPORT extern Object gsin_writing_fd();

#endif

/* variables/constants */
extern Object G2int_ab_package_1;
extern Object G2int_abort_level_0_tag;
extern Object G2int_active_icp_sockets;
extern Object G2int_all_gsi_applications;
extern Object G2int_array_element_attribute_spec;
extern Object G2int_available_gensym_conses;
extern Object G2int_build_identification_integer;
extern Object G2int_build_identification_string;
extern Object G2int_callback_is_global_array;
extern Object G2int_chain_of_available_gsi_applications;
extern Object G2int_chain_of_available_schedule_tasks;
extern Object G2int_created_simple_float_array_pool_arrays;
extern Object G2int_current_gsi_application;
extern Object G2int_current_gsi_string_conversion_style_code;
extern Object G2int_current_icp_buffer;
extern Object G2int_current_icp_port;
extern Object G2int_current_icp_socket;
extern Object G2int_current_real_time;
extern Object G2int_current_receiving_resumable_object;
extern Object G2int_current_remote_procedure_identifier;
extern Object G2int_current_schedule_task;
extern Object G2int_current_twriting_output_type;
extern Object G2int_current_wide_string;
extern Object G2int_current_wide_string_list;
extern Object G2int_current_write_icp_byte_position;
#define G2int_day_bit_offset FIX((SI_Long)0L)
extern Object G2int_default_gsi_application;
extern Object G2int_default_gsi_extension_tcp_address;
extern Object G2int_disable_resumability;
extern Object G2int_do_error_trappingqm;
extern Object G2int_enable_global_errors;
extern Object G2int_enable_run_gsi;
extern Object G2int_fake_array_of_one_wrapper;
extern Object G2int_fill_pointer_for_current_wide_string;
extern Object G2int_gensym_error_argument_list;
extern Object G2int_gensym_error_format_string;
extern Object G2int_gensym_error_sure_of_format_info_p;
#define G2int_gsi_64bit_float_array_type_tag FIX((SI_Long)22L)
#define G2int_gsi_64bit_float_list_type_tag FIX((SI_Long)38L)
#define G2int_gsi_64bit_float_type_tag FIX((SI_Long)6L)
extern Object G2int_gsi_application_count;
#define G2int_gsi_application_load_failed FIX((SI_Long)89L)
#define G2int_gsi_argument_count_too_big FIX((SI_Long)33L)
#define G2int_gsi_attribute_name_not_found FIX((SI_Long)256L)
#define G2int_gsi_bad_magic_number FIX((SI_Long)23L)
#define G2int_gsi_bad_magic_number_in_query FIX((SI_Long)48L)
#define G2int_gsi_bad_rpc_state FIX((SI_Long)65L)
#define G2int_gsi_base_information_code FIX((SI_Long)512L)
#define G2int_gsi_base_success_code FIX((SI_Long)768L)
#define G2int_gsi_base_user_error_code FIX((SI_Long)1024L)
#define G2int_gsi_base_warning_code FIX((SI_Long)256L)
#define G2int_gsi_callback_name_not_found FIX((SI_Long)87L)
extern Object G2int_gsi_callback_name_string_array;
extern Object G2int_gsi_callback_name_symbol_array;
#define G2int_gsi_cannot_establish_listener FIX((SI_Long)70L)
#define G2int_gsi_circularity_not_supported FIX((SI_Long)63L)
#define G2int_gsi_close_fd FIX((SI_Long)9L)
extern Object G2int_gsi_command_line_host;
extern Object G2int_gsi_command_line_network;
extern Object G2int_gsi_command_line_port;
#define G2int_gsi_connection_denied FIX((SI_Long)72L)
extern Object G2int_gsi_connection_initializing;
#define G2int_gsi_connection_lost FIX((SI_Long)38L)
#define G2int_gsi_context_has_been_killed FIX((SI_Long)85L)
#define G2int_gsi_context_has_been_shut_down FIX((SI_Long)86L)
extern Object G2int_gsi_context_to_socket_map;
#define G2int_gsi_context_undefined FIX((SI_Long)49L)
#define G2int_gsi_count_out_of_array_bounds FIX((SI_Long)29L)
#define G2int_gsi_custom_user_error FIX((SI_Long)37L)
#define G2int_gsi_disable_interleaving FIX((SI_Long)12L)
#define G2int_gsi_do_not_reformat_messages FIX((SI_Long)15L)
#define G2int_gsi_error_code_out_of_range FIX((SI_Long)-1L)
extern Object G2int_gsi_error_code_table;
#define G2int_gsi_error_handler FIX((SI_Long)17L)
#define G2int_gsi_error_in_connect FIX((SI_Long)74L)
#define G2int_gsi_extend_current_text_string_error FIX((SI_Long)60L)
extern Object G2int_gsi_extension_tcp_addressqm;
#define G2int_gsi_failure FIX((SI_Long)1L)
#define G2int_gsi_false FIX((SI_Long)0L)
extern Object G2int_gsi_flag_arguments;
#define G2int_gsi_g2_logical_out_of_bounds FIX((SI_Long)27L)
extern Object G2int_gsi_gensym_string_text_conversion_style_array;
#define G2int_gsi_get_tcp_port FIX((SI_Long)1L)
extern Object G2int_gsi_global_option_array;
#define G2int_gsi_icp_message_out_of_synch_case_2 FIX((SI_Long)58L)
#define G2int_gsi_icp_message_too_long FIX((SI_Long)57L)
extern Object G2int_gsi_icp_sockets_waiting_for_connect;
#define G2int_gsi_identifying_attribute_index_out_of_range FIX((SI_Long)25L)
#define G2int_gsi_idle FIX((SI_Long)20L)
#define G2int_gsi_illegal_error_arguments FIX((SI_Long)80L)
#define G2int_gsi_illegal_nesting_of_run_loop FIX((SI_Long)43L)
#define G2int_gsi_incompatible_history_spec FIX((SI_Long)45L)
#define G2int_gsi_incompatible_structure FIX((SI_Long)30L)
#define G2int_gsi_incompatible_structure2 FIX((SI_Long)56L)
#define G2int_gsi_incompatible_type FIX((SI_Long)16L)
#define G2int_gsi_incorrect_argument_count FIX((SI_Long)20L)
#define G2int_gsi_index_space_full_error FIX((SI_Long)62L)
#define G2int_gsi_integer_array_type_tag FIX((SI_Long)17L)
#define G2int_gsi_integer_list_type_tag FIX((SI_Long)33L)
#define G2int_gsi_integer_too_large FIX((SI_Long)81L)
#define G2int_gsi_integer_too_small FIX((SI_Long)82L)
#define G2int_gsi_integer_type_tag FIX((SI_Long)1L)
#define G2int_gsi_internal_memory_inconsistency FIX((SI_Long)22L)
#define G2int_gsi_invalid_attribute_type FIX((SI_Long)77L)
#define G2int_gsi_invalid_call_handle FIX((SI_Long)18L)
#define G2int_gsi_invalid_context FIX((SI_Long)24L)
#define G2int_gsi_invalid_decnet_object_name FIX((SI_Long)4L)
#define G2int_gsi_invalid_handle FIX((SI_Long)50L)
#define G2int_gsi_invalid_handle_for_context FIX((SI_Long)54L)
#define G2int_gsi_invalid_handle_of_nth FIX((SI_Long)51L)
#define G2int_gsi_invalid_history_type FIX((SI_Long)68L)
#define G2int_gsi_invalid_network_address FIX((SI_Long)5L)
#define G2int_gsi_invalid_network_combo FIX((SI_Long)2L)
#define G2int_gsi_invalid_option_index FIX((SI_Long)88L)
#define G2int_gsi_invalid_protocol FIX((SI_Long)1L)
#define G2int_gsi_invalid_return_value_index FIX((SI_Long)75L)
#define G2int_gsi_invalid_return_value_kind FIX((SI_Long)76L)
#define G2int_gsi_invalid_tcp_port_number FIX((SI_Long)3L)
#define G2int_gsi_invalid_timestamp FIX((SI_Long)53L)
#define G2int_gsi_invalid_type FIX((SI_Long)46L)
extern Object G2int_gsi_io_blocked;
extern Object G2int_gsi_io_unblocked;
extern Object G2int_gsi_is_not_initialized;
#define G2int_gsi_item_array_type_tag FIX((SI_Long)23L)
#define G2int_gsi_item_definitions_are_read_only FIX((SI_Long)6L)
#define G2int_gsi_item_handle_type_tag FIX((SI_Long)9L)
#define G2int_gsi_item_has_no_value FIX((SI_Long)41L)
#define G2int_gsi_item_list_type_tag FIX((SI_Long)39L)
#define G2int_gsi_item_or_value_array_type_tag FIX((SI_Long)25L)
#define G2int_gsi_item_or_value_list_type_tag FIX((SI_Long)41L)
#define G2int_gsi_item_type_tag FIX((SI_Long)7L)
extern Object G2int_gsi_keyword_arguments;
#define G2int_gsi_local_function_undefined FIX((SI_Long)17L)
extern Object G2int_gsi_local_home;
#define G2int_gsi_logical_array_type_tag FIX((SI_Long)21L)
#define G2int_gsi_logical_list_type_tag FIX((SI_Long)37L)
#define G2int_gsi_logical_type_tag FIX((SI_Long)5L)
#define G2int_gsi_long_type_tag FIX((SI_Long)51L)
extern Object G2int_gsi_magic_number;
#define G2int_gsi_magic_offset FIX((SI_Long)1L)
#define G2int_gsi_malformed_socket FIX((SI_Long)66L)
#define G2int_gsi_max_number_of_identifying_attributes FIX((SI_Long)6L)
#define G2int_gsi_maximum_contexts_exceeded FIX((SI_Long)71L)
extern Object G2int_gsi_maximum_idle_interval;
extern Object G2int_gsi_maximum_number_of_contexts;
#define G2int_gsi_maximum_text_string_length_error FIX((SI_Long)59L)
#define G2int_gsi_missing_attribute_name FIX((SI_Long)28L)
#define G2int_gsi_missing_instance_structure FIX((SI_Long)15L)
extern Object G2int_gsi_most_recent_error;
extern Object G2int_gsi_most_recent_error_message;
extern Object G2int_gsi_most_recent_error_remote_procedure_identifier;
#define G2int_gsi_network_error FIX((SI_Long)90L)
#define G2int_gsi_new_symbol_api FIX((SI_Long)10L)
#define G2int_gsi_no_class_in_registered_item FIX((SI_Long)26L)
#define G2int_gsi_no_class_name_specified FIX((SI_Long)32L)
#define G2int_gsi_no_flush FIX((SI_Long)8L)
#define G2int_gsi_no_license FIX((SI_Long)84L)
#define G2int_gsi_no_more_rpc_identifiers FIX((SI_Long)64L)
#define G2int_gsi_no_name_in_registered_item FIX((SI_Long)55L)
#define G2int_gsi_no_signal_handlers FIX((SI_Long)5L)
#define G2int_gsi_non_c FIX((SI_Long)3L)
#define G2int_gsi_noop_code_accessed FIX((SI_Long)42L)
#define G2int_gsi_not_a_symbol FIX((SI_Long)83L)
#define G2int_gsi_not_writing_fd FIX((SI_Long)24L)
#define G2int_gsi_null_pointer_argument FIX((SI_Long)40L)
#define G2int_gsi_null_type_tag FIX((SI_Long)0L)
#define G2int_gsi_number_of_callbacks FIX((SI_Long)25L)
#define G2int_gsi_number_of_options FIX((SI_Long)17L)
#define G2int_gsi_one_cycle FIX((SI_Long)0L)
#define G2int_gsi_open_fd FIX((SI_Long)8L)
#define G2int_gsi_owner_is_context FIX((SI_Long)2L)
#define G2int_gsi_owner_is_gsi FIX((SI_Long)1L)
#define G2int_gsi_owner_is_user FIX((SI_Long)0L)
#define G2int_gsi_ownerous_reclamation_violation FIX((SI_Long)39L)
#define G2int_gsi_product_tag FIX((SI_Long)2L)
extern Object G2int_gsi_protect_inner_calls_p;
#define G2int_gsi_quantity_array_type_tag FIX((SI_Long)26L)
#define G2int_gsi_quantity_list_type_tag FIX((SI_Long)42L)
#define G2int_gsi_quantity_type_tag FIX((SI_Long)10L)
#define G2int_gsi_read_callback FIX((SI_Long)6L)
#define G2int_gsi_receive_deregistrations FIX((SI_Long)12L)
extern Object G2int_gsi_reclaim_list_level;
extern Object G2int_gsi_reclaim_listqm;
extern Object G2int_gsi_references_in_use;
#define G2int_gsi_remote_declaration_not_found FIX((SI_Long)19L)
#define G2int_gsi_reserved_error_code FIX((SI_Long)36L)
#define G2int_gsi_resumable_icp_error FIX((SI_Long)78L)
#define G2int_gsi_rpc_async_abort FIX((SI_Long)258L)
#define G2int_gsi_rpc_error_from_g2 FIX((SI_Long)34L)
#define G2int_gsi_rpc_error_from_g2_procedure FIX((SI_Long)35L)
#define G2int_gsi_rpc_late_async_abort FIX((SI_Long)259L)
#define G2int_gsi_run_state_change FIX((SI_Long)16L)
#define G2int_gsi_run_state_direction_entering_gsi FIX((SI_Long)1L)
#define G2int_gsi_run_state_direction_entering_gsi_by_signal FIX((SI_Long)5L)
#define G2int_gsi_run_state_direction_entering_watchdog FIX((SI_Long)3L)
#define G2int_gsi_run_state_direction_leaving_gsi FIX((SI_Long)2L)
#define G2int_gsi_run_state_direction_leaving_watchdog FIX((SI_Long)4L)
#define G2int_gsi_run_state_type_api FIX((SI_Long)1L)
#define G2int_gsi_run_state_type_callback FIX((SI_Long)2L)
#define G2int_gsi_run_state_type_signal FIX((SI_Long)4L)
#define G2int_gsi_run_state_type_wait FIX((SI_Long)3L)
extern Object G2int_gsi_scheduled_tasks_time_limit;
extern Object G2int_gsi_sensor_to_deregisterqm;
#define G2int_gsi_sequence_type_tag FIX((SI_Long)49L)
#define G2int_gsi_set_up FIX((SI_Long)0L)
#define G2int_gsi_shutdown_context FIX((SI_Long)4L)
extern Object G2int_gsi_shutdown_reason;
#define G2int_gsi_string_array_type_tag FIX((SI_Long)20L)
#define G2int_gsi_string_check FIX((SI_Long)4L)
#define G2int_gsi_string_list_type_tag FIX((SI_Long)36L)
#define G2int_gsi_string_type_tag FIX((SI_Long)4L)
#define G2int_gsi_structure_has_no_attribute_name FIX((SI_Long)14L)
#define G2int_gsi_structure_has_no_class_qualifier FIX((SI_Long)31L)
#define G2int_gsi_structure_has_no_handle FIX((SI_Long)7L)
#define G2int_gsi_structure_has_no_history FIX((SI_Long)44L)
#define G2int_gsi_structure_has_no_identifying_attrs FIX((SI_Long)8L)
#define G2int_gsi_structure_has_no_instance FIX((SI_Long)9L)
#define G2int_gsi_structure_has_no_interval FIX((SI_Long)12L)
#define G2int_gsi_structure_has_no_status FIX((SI_Long)13L)
#define G2int_gsi_structure_has_no_timed_flag FIX((SI_Long)11L)
#define G2int_gsi_structure_has_no_timestamp FIX((SI_Long)10L)
#define G2int_gsi_structure_type_tag FIX((SI_Long)50L)
#define G2int_gsi_success FIX((SI_Long)0L)
extern Object G2int_gsi_suppress_output;
#define G2int_gsi_symbol_array_type_tag FIX((SI_Long)19L)
#define G2int_gsi_symbol_list_type_tag FIX((SI_Long)35L)
#define G2int_gsi_symbol_type_tag FIX((SI_Long)3L)
extern Object G2int_gsi_text_conversion_style_list;
extern Object G2int_gsi_throw_to_run_loop_may_be_harmful_p;
#define G2int_gsi_timestamp_not_found FIX((SI_Long)257L)
#define G2int_gsi_timestamp_out_of_bounds FIX((SI_Long)52L)
#define G2int_gsi_trace_run_loop FIX((SI_Long)13L)
#define G2int_gsi_trace_run_state FIX((SI_Long)9L)
extern Object G2int_gsi_transfer_array_for_deregistration;
#define G2int_gsi_true FIX((SI_Long)1L)
#define G2int_gsi_type_for_data_service FIX((SI_Long)47L)
#define G2int_gsi_uncaught_exception FIX((SI_Long)69L)
#define G2int_gsi_undefined_context FIX((SI_Long)-1L)
#define G2int_gsi_undefined_structure_method_error FIX((SI_Long)61L)
#define G2int_gsi_unexpected_operation FIX((SI_Long)21L)
#define G2int_gsi_unknown_calling_procedure_index FIX((SI_Long)79L)
#define G2int_gsi_unknown_string_conversion_style FIX((SI_Long)73L)
#define G2int_gsi_unknown_type_tag FIX((SI_Long)67L)
#define G2int_gsi_unsigned_short_vector_type_tag FIX((SI_Long)11L)
#define G2int_gsi_use_gfloats FIX((SI_Long)2L)
#define G2int_gsi_use_references FIX((SI_Long)11L)
extern Object G2int_gsi_use_references_p;
#define G2int_gsi_user_owns_gsi_items FIX((SI_Long)16L)
#define G2int_gsi_value_array_type_tag FIX((SI_Long)24L)
#define G2int_gsi_value_list_type_tag FIX((SI_Long)40L)
#define G2int_gsi_value_type_tag FIX((SI_Long)8L)
extern Object G2int_gsi_wakeup_icp_socket;
extern Object G2int_gsi_wakeup_icp_socket_active_p;
#define G2int_gsi_watchdog_function FIX((SI_Long)19L)
extern Object G2int_gsi_wide_api_p;
extern Object G2int_gsi_wide_string_text_conversion_style_array;
#define G2int_gsi_write_callback FIX((SI_Long)7L)
#define G2int_gsi_writing_fd FIX((SI_Long)23L)
extern Object G2int_have_default_gsi_application;
#define G2int_highest_system_priority FIX((SI_Long)0L)
extern Object G2int_icp_buffer_of_start_of_message_seriesqm;
extern Object G2int_icp_buffers_for_message_group;
extern Object G2int_icp_byte_position_of_start_of_message_seriesqm;
extern Object G2int_icp_connection_closed;
extern Object G2int_icp_connection_running;
extern Object G2int_icp_socket_for_handle_icp_messages;
extern Object G2int_icp_socket_for_reclaimqm;
extern Object G2int_icp_socket_listening;
extern Object G2int_icp_suspend;
extern Object G2int_in_error_handler;
extern Object G2int_in_recursive_gsi_context;
extern Object G2int_in_unprotected_gsi_api_call_p;
extern Object G2int_index_of_gsi_sensor_to_deregisterqm;
extern Object G2int_inhibit_icp_message_processing;
extern Object G2int_inhibit_icp_message_processing_enabled;
#define G2int_initial_maximum_number_of_contexts FIX((SI_Long)50L)
extern Object G2int_inner_abort_level_tag;
extern Object G2int_item_name_attribute_spec;
extern Object G2int_keyword_package_1;
extern Object G2int_list_element_attribute_spec;
extern Object G2int_loadable_bridges_enabled_p;
#define G2int_major_version_number_of_current_gensym_product_line FIX((SI_Long)12L)
extern Object G2int_make_gsi_instance_existing_instance;
#define G2int_max_build_id_digit FIX((SI_Long)9L)
#define G2int_max_build_id_letter FIX((SI_Long)26L)
#define G2int_max_number_of_bits_for_day_code FIX((SI_Long)5L)
#define G2int_max_number_of_bits_for_month_code FIX((SI_Long)5L)
#define G2int_max_number_of_bits_for_year_code FIX((SI_Long)5L)
#define G2int_minor_version_number_of_current_gensym_product_line FIX((SI_Long)0L)
#define G2int_month_bit_offset FIX((SI_Long)5L)
extern Object G2int_next_available_context_number;
extern Object G2int_no_arg;
#define G2int_no_error FIX((SI_Long)0L)
extern Object G2int_number_of_contexts_allocated;
extern Object G2int_number_of_icp_bytes_for_message_series;
extern Object G2int_number_of_icp_bytes_in_message_group;
extern Object G2int_number_of_icp_bytes_to_fill_buffer;
extern Object G2int_pending_gsi_callbacks;
#define G2int_release_quality_of_current_gensym_product_line FIX((SI_Long)2L)
extern Object G2int_resumable_priority_of_gsi_data_service;
extern Object G2int_reusable_circularity_table;
extern Object G2int_reusable_name_instance;
extern Object G2int_reusable_value_instance;
#define G2int_revision_number_of_current_gensym_product_line FIX((SI_Long)20L)
extern Object G2int_secure_icp_default_p;
extern Object G2int_secure_icp_initialized_p;
extern Object G2int_send_timestamp_with_gsi_sensor_p;
extern Object G2int_shutdown_catch_tag;
extern Object G2int_simple_float_array_pool_memory_usage;
extern Object G2int_simple_item_value_attribute_spec;
#define G2int_size_of_array_of_transfer_wrappers FIX((SI_Long)50L)
extern Object G2int_starresumable_icp_statestar;
extern Object G2int_starscheduler_enabledqmstar;
extern Object G2int_starwrite_console_pstar;
extern Object G2int_structure_being_reclaimed;
extern Object G2int_tcp_listener_port_number;
extern Object G2int_the_type_description_of_gsi_application;
extern Object G2int_time_slice_start_time;
extern Object G2int_top_level_error_catcher_tag;
extern Object G2int_top_level_error_seen;
extern Object G2int_total_length_of_current_wide_string;
extern Object G2int_unix_command_line_argument_count;
extern Object G2int_unrecoverable_error_p;
#define G2int_use_tcpip_protocol_only FIX((SI_Long)13L)
extern Object G2int_vector_of_simple_float_array_pools;
extern Object G2int_within_run_loop_extent;
extern Object G2int_write_value_of_gsi_item_p;
extern Object G2int_writing_icp_message_group;
extern Object G2int_year_bit_offset;
