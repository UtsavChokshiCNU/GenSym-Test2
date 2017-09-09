/* gscmn.h -- Header File for gscmn.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qcons;
extern Object Qerror;
extern Object Qsecond;
extern Object Qstring;
extern Object Qstringp;
extern Object Qsymbol;
extern Object Qvector;

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
extern Object allocate_byte_vector_16(Object);
extern Object allocate_gsi_context_number(void);
extern Object allocate_managed_float_box(void);
extern Object assign_corresponding_icp_object_index(Object,Object,Object);
extern Object assign_index_in_index_space(Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object bytes_per_simple_vector(Object);
extern Object c_string_to_gensym_string(Object);
extern Object c_string_to_text_string(Object);
extern Object c_unsigned_short_vector_to_text_string(Object,Object);
extern Object c_wide_string_to_gensym_string(Object);
extern Object c_wide_string_to_text_string(Object);
extern Object call_initialize_context_and_maybe_reject_connection(void);
extern Object call_initialize_context_callback(void);
extern Object clear_optimized_constants(void);
extern Object copy_list_using_gsi_conses_1(Object);
extern Object copy_text_string(Object);
extern Object copy_tree_using_gsi_conses_1(Object);
extern Object create_transfer_wrapper_array(Object);
extern Object current_gsi_string_conversion_style(void);
extern Object deassign_index_in_index_space(Object,Object);
extern Object delete_gsi_cons_1(Object,Object);
extern Object delete_gsi_element_1(Object,Object);
extern Object direct_structure_method(Object,Object);
extern Object disallow_new_icp_listener_connection(Object);
extern Object emit_icp_read_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_write_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object end_icp_message_group(void);
extern Object enlarge_index_space(Object,Object);
extern Object establish_new_object_index_for_gsi_instance(int,...);
extern Object framep_function(Object);
extern Object free_gsi_context_number(Object);
extern Object g2_initialize_gsi_interface(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object generate_float_vector(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_decode_unix_time(Object);
extern Object gensym_encode_unix_time_as_gensym_float(Object,Object,Object,Object,Object,Object);
extern Object gensym_encode_unix_time_as_managed_float(Object,Object,Object,Object,Object,Object);
extern Object gensym_string_to_wide_string(Object);
extern Object gensym_string_to_wide_string_for_gsi(Object);
extern Object get_corresponding_icp_object(Object);
extern Object get_from_icp_port_if_any(Object,Object,Object);
extern Object get_gsi_instance_plist_value(Object,Object);
extern Object get_icp_object_index_for_gsi_instance(Object,Object);
extern Object get_system_major_version(Object);
extern Object get_system_minor_version(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object gsi_add_new_sensor_attribute(Object,Object,Object,Object);
extern Object gsi_allocate_managed_array(Object);
extern Object gsi_api_symbol_to_symbol_or_nil_1(Object,Object);
extern Object gsi_array_wrapper_structure_memory_usage(void);
extern Object gsi_attribute_structure_memory_usage(void);
extern Object gsi_cons_1(Object,Object);
extern Object gsi_cons_memory_usage(void);
extern Object gsi_extension_data_structure_memory_usage(void);
extern Object gsi_history_structure_memory_usage(void);
extern Object gsi_incoming_symbol_name(Object);
extern Object gsi_initialize_icp_socket(Object);
extern Object gsi_instance_extension_structure_memory_usage(void);
extern Object gsi_instance_structure_memory_usage(void);
extern Object gsi_instance_value_function(Object);
extern Object gsi_intern(Object);
extern Object gsi_list_2(Object,Object);
extern Object gsi_list_3(Object,Object,Object);
extern Object gsi_list_4(Object,Object,Object,Object);
extern Object gsi_list_trace_hook(Object);
extern Object gsi_option_is_set_p(Object);
extern Object gsi_outgoing_symbol_name(Object);
extern Object gsi_push_onto_appropriate_list(int,...);
extern Object gsi_receive_value_for_gsi_sensor(Object,Object,Object,Object,Object);
extern Object gsi_receive_value_for_gsi_sensor_1(Object,Object,Object,Object);
extern Object gsi_receive_value_for_ping_request(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object gsi_reclaim_displaced_array(Object);
extern Object gsi_reclaim_managed_array(Object);
extern Object gsi_register_new_sensor(int,...);
extern Object gsi_reply_to_initial_ping(void);
extern Object gsi_send_reply_to_initial_ping_internal(Object);
extern Object gsi_sensor_index(Object);
extern Object gsi_sensor_p_function(Object);
extern Object gsi_string_for_symbol(Object,Object);
extern Object gsi_string_type_p(Object);
extern Object gsi_transfer_wrapper_structure_memory_usage(void);
extern Object gsi_write_user_message_string(Object,Object,Object,Object);
extern Object handle_icp_begin_sensor_list(void);
extern Object handle_icp_begin_sensor_list__body(void);
extern Object handle_icp_define_gsi_interface(void);
extern Object handle_icp_define_gsi_interface__body(Object);
extern Object handle_icp_define_gsi_sensor(void);
extern Object handle_icp_define_gsi_sensor__body(Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_end_sensor_list(void);
extern Object handle_icp_end_sensor_list__body(void);
extern Object handle_icp_get_values_for_sensors_in_list(void);
extern Object handle_icp_get_values_for_sensors_in_list__body(void);
extern Object handle_icp_initialize_data_server(void);
extern Object handle_icp_initialize_data_server__body(Object);
extern Object handle_icp_initialize_gsi_interface(void);
extern Object handle_icp_initialize_gsi_interface__body(Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_load_sensor_list_element(void);
extern Object handle_icp_load_sensor_list_element__body(Object,Object,Object);
extern Object handle_icp_modify_gsi_sensor_definition(void);
extern Object handle_icp_modify_gsi_sensor_definition__body(Object,Object,Object,Object,Object);
extern Object handle_icp_pause_data_server(void);
extern Object handle_icp_pause_data_server__body(void);
extern Object handle_icp_receive_gsi_sensor_value_vector(void);
extern Object handle_icp_receive_gsi_sensor_value_vector__body(Object,Object,Object,Object);
extern Object handle_icp_receive_timestamped_gsi_sensor_value_vector(void);
extern Object handle_icp_receive_timestamped_gsi_sensor_value_vector__body(Object,Object,Object,Object,Object);
extern Object handle_icp_receive_value_for_gsi_sensor(void);
extern Object handle_icp_receive_value_for_gsi_sensor__body(Object,Object,Object);
extern Object handle_icp_receive_value_for_gsi_sensor_with_timestamp(void);
extern Object handle_icp_receive_value_for_gsi_sensor_with_timestamp__body(Object,Object,Object,Object);
extern Object handle_icp_receive_value_for_ping_request(void);
extern Object handle_icp_receive_value_for_ping_request__body(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_receive_values_for_gsi_sensors(void);
extern Object handle_icp_receive_values_for_gsi_sensors__body(Object);
extern Object handle_icp_register_corresponding_icp_object(void);
extern Object handle_icp_register_corresponding_icp_object__body(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_reset_data_server(void);
extern Object handle_icp_reset_data_server__body(void);
extern Object handle_icp_resume_data_server(void);
extern Object handle_icp_resume_data_server__body(void);
extern Object handle_icp_return_initialize_gsi_interface_status(void);
extern Object handle_icp_return_initialize_gsi_interface_status__body(Object);
extern Object handle_icp_return_peer_version(void);
extern Object handle_icp_return_peer_version__body(Object,Object);
extern Object handle_icp_send_data_values_if_any(void);
extern Object handle_icp_send_data_values_if_any__body(Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_set_values_for_sensors_in_list(void);
extern Object handle_icp_set_values_for_sensors_in_list__body(void);
extern Object handle_icp_start_data_server(void);
extern Object handle_icp_start_data_server__body(void);
extern Object handle_icp_stop_sending_values_for_sensors_in_list(void);
extern Object handle_icp_stop_sending_values_for_sensors_in_list__body(void);
extern Object handle_icp_write_user_message_string(void);
extern Object handle_icp_write_user_message_string__body(Object,Object,Object,Object);
extern Object icp_connection_being_shutdown_qm(Object);
extern Object icp_connection_open_p(Object);
extern Object icp_cons_1(Object,Object);
extern Object icp_error_internal(Object,Object,Object,Object,Object);
extern Object icp_list_4(Object,Object,Object,Object);
extern Object initialize_gsi_context_number_table(Object);
extern Object initialize_icp_object_type(Object,Object,Object,Object);
extern Object initialize_icp_object_type_compile(Object,Object,Object);
extern Object instantaneous_icp_reader_byte_count(void);
extern Object instantaneous_icp_writer_byte_count(void);
extern Object intern_text_string(int,...);
extern Object lisp_string_to_c_string(Object);
extern Object lisp_string_to_c_unsigned_short_vector(Object);
extern Object lisp_string_to_c_wide_string(Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_corresponding_icp_gsi_instance(Object);
extern Object make_corresponding_icp_symbol(Object);
extern Object make_gsi_array_wrapper_1(Object,Object);
extern Object make_gsi_attribute_1_1(Object,Object,Object);
extern Object make_gsi_extension_data_1(void);
extern Object make_gsi_history_1_1(Object,Object,Object,Object);
extern Object make_gsi_instance_1_1(void);
extern Object make_gsi_instance_extension_1(void);
extern Object make_gsi_list_1(Object);
extern Object make_gsi_transfer_wrapper_1_1(Object,Object,Object,Object,Object);
extern Object make_gsi_user_transfer_wrapper(void);
extern Object make_index_space_1(Object,Object);
extern Object make_permanent_gsi_array_wrapper_structure_internal(void);
extern Object make_permanent_gsi_attribute_structure_internal(void);
extern Object make_permanent_gsi_extension_data_structure_internal(void);
extern Object make_permanent_gsi_history_structure_internal(void);
extern Object make_permanent_gsi_instance_extension_structure_internal(void);
extern Object make_permanent_gsi_instance_structure_internal(void);
extern Object make_permanent_gsi_transfer_wrapper_structure_internal(void);
extern Object make_thread_array(Object);
extern Object maybe_declare_all_gsi_sensors(void);
extern Object maybe_update_remote_icp_version_info_for_version(Object,Object,Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object network_access_allowed_p(int,...);
extern Object notify_user(int,...);
extern Object notify_user_of_out_of_bounds_timestamp(Object,Object);
extern Object outstanding_gsi_array_wrapper_count(void);
extern Object outstanding_gsi_attribute_count(void);
extern Object outstanding_gsi_conses(void);
extern Object outstanding_gsi_extension_data_count(void);
extern Object outstanding_gsi_history_count(void);
extern Object outstanding_gsi_instance_count(void);
extern Object outstanding_gsi_instance_extension_count(void);
extern Object outstanding_gsi_transfer_wrapper_count(void);
extern Object peek_icp_byte(void);
extern Object post_on_message_board(int,...);
extern Object protect_gsi_api_call_p(void);
extern Object push_optimized_constant(Object);
extern Object read_icp_boolean(void);
extern Object read_icp_byte(void);
extern Object read_icp_corresponding_object_index(void);
extern Object read_icp_do_not_reformat_message_p(void);
extern Object read_icp_fixnum(void);
extern Object read_icp_gsi_ds_update_interval(void);
extern Object read_icp_gsi_ds_value(void);
extern Object read_icp_gsi_permanent_remote_value(void);
extern Object read_icp_gsi_timestamp(void);
extern Object read_icp_gsi_value_vector(void);
extern Object read_icp_gsi_values(void);
extern Object read_icp_icp_tree(void);
extern Object read_icp_integer(void);
extern Object read_icp_item_reference(void);
extern Object read_icp_managed_double_float(void);
extern Object read_icp_remote_value(void);
extern Object read_icp_returned_gsi_sensor(void);
extern Object read_icp_text_string(void);
extern Object read_icp_unsigned_integer(void);
extern Object read_icp_unsigned_integer_or_nil(void);
extern Object receive_initial_message(Object,Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_string(Object);
extern Object reclaim_gsi_array_wrapper_1(Object);
extern Object reclaim_gsi_attribute_1_1(Object);
extern Object reclaim_gsi_cons_1(Object);
extern Object reclaim_gsi_extension_data(Object);
extern Object reclaim_gsi_extension_data_internal_1(Object);
extern Object reclaim_gsi_history_1_1(Object);
extern Object reclaim_gsi_instance(Object,Object);
extern Object reclaim_gsi_instance_1_1(Object);
extern Object reclaim_gsi_instance_extension_1_1(Object);
extern Object reclaim_gsi_instance_for_context(Object);
extern Object reclaim_gsi_instance_for_gsi(Object);
extern Object reclaim_gsi_instance_for_user(Object);
extern Object reclaim_gsi_list_1(Object);
extern Object reclaim_gsi_list_function(Object);
extern Object reclaim_gsi_list_star_1(Object);
extern Object reclaim_gsi_remote_procedures(Object);
extern Object reclaim_gsi_transfer_wrapper_1_1(Object);
extern Object reclaim_gsi_transfer_wrapper_array(Object);
extern Object reclaim_gsi_tree_1(Object);
extern Object reclaim_gsi_value_vector(Object);
extern Object reclaim_icp_list_1(Object);
extern Object reclaim_icp_object_map(Object,Object,Object);
extern Object reclaim_icp_object_map_for_gsi_instance(Object);
extern Object reclaim_icp_port_entry(Object,Object,Object,Object);
extern Object reclaim_icp_port_entry_for_gsi_instance(Object,Object);
extern Object reclaim_if_evaluation_value_1(Object);
extern Object reclaim_if_evaluation_value_function(Object);
extern Object reclaim_if_gsi_instance_for_context(Object);
extern Object reclaim_if_managed_float(Object);
extern Object reclaim_if_text_or_gensym_string_function(Object);
extern Object reclaim_managed_simple_float_array_of_length_1(Object);
extern Object reclaim_text_or_gensym_string(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_wide_string(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object replenish_gsi_cons_pool(void);
extern Object replenish_gsi_list_pool(Object);
extern Object resumable_icp_pop(void);
extern Object resumable_icp_pop_list_if_end_marker(void);
extern Object resumable_icp_push(Object);
extern Object round_post4_dot_0_managed_float(Object);
extern Object send_icp_begin_sensor_list(void);
extern Object send_icp_create_item_reference(Object);
extern Object send_icp_define_gsi_interface(Object);
extern Object send_icp_define_gsi_sensor(Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_end_sensor_list(void);
extern Object send_icp_get_values_for_sensors_in_list(void);
extern Object send_icp_initialize_data_server(Object);
extern Object send_icp_initialize_gsi_interface(Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_load_sensor_list_element(Object,Object,Object);
extern Object send_icp_modify_gsi_sensor_definition(Object,Object,Object,Object,Object);
extern Object send_icp_pause_data_server(void);
extern Object send_icp_receive_gsi_sensor_value_vector(Object,Object,Object,Object);
extern Object send_icp_receive_timestamped_gsi_sensor_value_vector(Object,Object,Object,Object,Object);
extern Object send_icp_receive_value_for_gsi_sensor(Object,Object,Object);
extern Object send_icp_receive_value_for_gsi_sensor_with_timestamp(Object,Object,Object,Object);
extern Object send_icp_receive_value_for_ping_request(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_receive_values_for_gsi_sensors(Object);
extern Object send_icp_register_corresponding_icp_object(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_reset_data_server(void);
extern Object send_icp_resume_data_server(void);
extern Object send_icp_return_initialize_gsi_interface_status(Object);
extern Object send_icp_return_peer_version(Object,Object);
extern Object send_icp_send_data_values_if_any(Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_set_values_for_sensors_in_list(void);
extern Object send_icp_start_data_server(void);
extern Object send_icp_stop_sending_values_for_sensors_in_list(void);
extern Object send_icp_write_user_message_string(Object,Object,Object,Object);
extern Object send_version_info(void);
extern Object set_access_form_for_gsi_instance(Object,Object);
extern Object set_gsi_attribute_is_identifying_p(Object,Object);
extern Object set_gsi_attribute_is_transient_p(Object,Object);
extern Object set_gsi_instance_owner(Object,Object);
extern Object set_gsi_instance_plist_value(Object,Object,Object);
extern Object set_gsi_instance_value_type(Object,Object);
extern Object set_icp_object_index_for_gsi_instance(Object,Object,Object);
extern Object shutdown_icp_socket_connection(int,...);
extern Object start_writing_icp_message(Object);
extern Object symbol_for_gsi_string(Object);
extern Object symbol_name_text_string(Object);
extern Object update_object_pool_meters_list(Object);
extern Object wide_string_to_gensym_string(Object);
extern Object wide_string_to_gensym_string_for_gsi(Object);
extern Object write_icp_boolean(Object);
extern Object write_icp_byte(Object);
extern Object write_icp_corresponding_object_index(Object);
extern Object write_icp_do_not_reformat_message_p(Object);
extern Object write_icp_fixnum(Object);
extern Object write_icp_gsi_ds_update_interval(Object);
extern Object write_icp_gsi_ds_value(Object);
extern Object write_icp_gsi_permanent_remote_value(Object);
extern Object write_icp_gsi_timestamp(Object);
extern Object write_icp_gsi_value_vector(Object);
extern Object write_icp_gsi_values(Object);
extern Object write_icp_integer(Object);
extern Object write_icp_item_reference(Object);
extern Object write_icp_managed_double_float(Object);
extern Object write_icp_maybe_suspend(void);
extern Object write_icp_remote_value(Object);
extern Object write_icp_returned_gsi_sensor(Object);
extern Object write_icp_text_string(Object);
extern Object write_icp_unsigned_integer(Object);
extern Object write_icp_unsigned_integer_or_nil(Object);

#else

extern Object add_icp_message_handler();
extern Object allocate_byte_vector_16();
extern Object allocate_gsi_context_number();
extern Object allocate_managed_float_box();
extern Object assign_corresponding_icp_object_index();
extern Object assign_index_in_index_space();
extern Object bytes_per_double_float_simple_array();
extern Object bytes_per_simple_vector();
extern Object c_string_to_gensym_string();
extern Object c_string_to_text_string();
extern Object c_unsigned_short_vector_to_text_string();
extern Object c_wide_string_to_gensym_string();
extern Object c_wide_string_to_text_string();
extern Object call_initialize_context_and_maybe_reject_connection();
extern Object call_initialize_context_callback();
extern Object clear_optimized_constants();
extern Object copy_list_using_gsi_conses_1();
extern Object copy_text_string();
extern Object copy_tree_using_gsi_conses_1();
extern Object create_transfer_wrapper_array();
extern Object current_gsi_string_conversion_style();
extern Object deassign_index_in_index_space();
extern Object delete_gsi_cons_1();
extern Object delete_gsi_element_1();
extern Object direct_structure_method();
extern Object disallow_new_icp_listener_connection();
extern Object emit_icp_read_trace();
extern Object emit_icp_write_trace();
extern Object end_icp_message_group();
extern Object enlarge_index_space();
extern Object establish_new_object_index_for_gsi_instance();
extern Object framep_function();
extern Object free_gsi_context_number();
extern Object g2_initialize_gsi_interface();
extern Object generate_float_vector();
extern Object gensym_cons_1();
extern Object gensym_decode_unix_time();
extern Object gensym_encode_unix_time_as_gensym_float();
extern Object gensym_encode_unix_time_as_managed_float();
extern Object gensym_string_to_wide_string();
extern Object gensym_string_to_wide_string_for_gsi();
extern Object get_corresponding_icp_object();
extern Object get_from_icp_port_if_any();
extern Object get_gsi_instance_plist_value();
extern Object get_icp_object_index_for_gsi_instance();
extern Object get_system_major_version();
extern Object get_system_minor_version();
extern Object getfq_function_no_default();
extern Object gsi_add_new_sensor_attribute();
extern Object gsi_allocate_managed_array();
extern Object gsi_api_symbol_to_symbol_or_nil_1();
extern Object gsi_array_wrapper_structure_memory_usage();
extern Object gsi_attribute_structure_memory_usage();
extern Object gsi_cons_1();
extern Object gsi_cons_memory_usage();
extern Object gsi_extension_data_structure_memory_usage();
extern Object gsi_history_structure_memory_usage();
extern Object gsi_incoming_symbol_name();
extern Object gsi_initialize_icp_socket();
extern Object gsi_instance_extension_structure_memory_usage();
extern Object gsi_instance_structure_memory_usage();
extern Object gsi_instance_value_function();
extern Object gsi_intern();
extern Object gsi_list_2();
extern Object gsi_list_3();
extern Object gsi_list_4();
extern Object gsi_list_trace_hook();
extern Object gsi_option_is_set_p();
extern Object gsi_outgoing_symbol_name();
extern Object gsi_push_onto_appropriate_list();
extern Object gsi_receive_value_for_gsi_sensor();
extern Object gsi_receive_value_for_gsi_sensor_1();
extern Object gsi_receive_value_for_ping_request();
extern Object gsi_reclaim_displaced_array();
extern Object gsi_reclaim_managed_array();
extern Object gsi_register_new_sensor();
extern Object gsi_reply_to_initial_ping();
extern Object gsi_send_reply_to_initial_ping_internal();
extern Object gsi_sensor_index();
extern Object gsi_sensor_p_function();
extern Object gsi_string_for_symbol();
extern Object gsi_string_type_p();
extern Object gsi_transfer_wrapper_structure_memory_usage();
extern Object gsi_write_user_message_string();
extern Object handle_icp_begin_sensor_list();
extern Object handle_icp_begin_sensor_list__body();
extern Object handle_icp_define_gsi_interface();
extern Object handle_icp_define_gsi_interface__body();
extern Object handle_icp_define_gsi_sensor();
extern Object handle_icp_define_gsi_sensor__body();
extern Object handle_icp_end_sensor_list();
extern Object handle_icp_end_sensor_list__body();
extern Object handle_icp_get_values_for_sensors_in_list();
extern Object handle_icp_get_values_for_sensors_in_list__body();
extern Object handle_icp_initialize_data_server();
extern Object handle_icp_initialize_data_server__body();
extern Object handle_icp_initialize_gsi_interface();
extern Object handle_icp_initialize_gsi_interface__body();
extern Object handle_icp_load_sensor_list_element();
extern Object handle_icp_load_sensor_list_element__body();
extern Object handle_icp_modify_gsi_sensor_definition();
extern Object handle_icp_modify_gsi_sensor_definition__body();
extern Object handle_icp_pause_data_server();
extern Object handle_icp_pause_data_server__body();
extern Object handle_icp_receive_gsi_sensor_value_vector();
extern Object handle_icp_receive_gsi_sensor_value_vector__body();
extern Object handle_icp_receive_timestamped_gsi_sensor_value_vector();
extern Object handle_icp_receive_timestamped_gsi_sensor_value_vector__body();
extern Object handle_icp_receive_value_for_gsi_sensor();
extern Object handle_icp_receive_value_for_gsi_sensor__body();
extern Object handle_icp_receive_value_for_gsi_sensor_with_timestamp();
extern Object handle_icp_receive_value_for_gsi_sensor_with_timestamp__body();
extern Object handle_icp_receive_value_for_ping_request();
extern Object handle_icp_receive_value_for_ping_request__body();
extern Object handle_icp_receive_values_for_gsi_sensors();
extern Object handle_icp_receive_values_for_gsi_sensors__body();
extern Object handle_icp_register_corresponding_icp_object();
extern Object handle_icp_register_corresponding_icp_object__body();
extern Object handle_icp_reset_data_server();
extern Object handle_icp_reset_data_server__body();
extern Object handle_icp_resume_data_server();
extern Object handle_icp_resume_data_server__body();
extern Object handle_icp_return_initialize_gsi_interface_status();
extern Object handle_icp_return_initialize_gsi_interface_status__body();
extern Object handle_icp_return_peer_version();
extern Object handle_icp_return_peer_version__body();
extern Object handle_icp_send_data_values_if_any();
extern Object handle_icp_send_data_values_if_any__body();
extern Object handle_icp_set_values_for_sensors_in_list();
extern Object handle_icp_set_values_for_sensors_in_list__body();
extern Object handle_icp_start_data_server();
extern Object handle_icp_start_data_server__body();
extern Object handle_icp_stop_sending_values_for_sensors_in_list();
extern Object handle_icp_stop_sending_values_for_sensors_in_list__body();
extern Object handle_icp_write_user_message_string();
extern Object handle_icp_write_user_message_string__body();
extern Object icp_connection_being_shutdown_qm();
extern Object icp_connection_open_p();
extern Object icp_cons_1();
extern Object icp_error_internal();
extern Object icp_list_4();
extern Object initialize_gsi_context_number_table();
extern Object initialize_icp_object_type();
extern Object initialize_icp_object_type_compile();
extern Object instantaneous_icp_reader_byte_count();
extern Object instantaneous_icp_writer_byte_count();
extern Object intern_text_string();
extern Object lisp_string_to_c_string();
extern Object lisp_string_to_c_unsigned_short_vector();
extern Object lisp_string_to_c_wide_string();
extern Object load_and_initialize_type_description();
extern Object make_corresponding_icp_gsi_instance();
extern Object make_corresponding_icp_symbol();
extern Object make_gsi_array_wrapper_1();
extern Object make_gsi_attribute_1_1();
extern Object make_gsi_extension_data_1();
extern Object make_gsi_history_1_1();
extern Object make_gsi_instance_1_1();
extern Object make_gsi_instance_extension_1();
extern Object make_gsi_list_1();
extern Object make_gsi_transfer_wrapper_1_1();
extern Object make_gsi_user_transfer_wrapper();
extern Object make_index_space_1();
extern Object make_permanent_gsi_array_wrapper_structure_internal();
extern Object make_permanent_gsi_attribute_structure_internal();
extern Object make_permanent_gsi_extension_data_structure_internal();
extern Object make_permanent_gsi_history_structure_internal();
extern Object make_permanent_gsi_instance_extension_structure_internal();
extern Object make_permanent_gsi_instance_structure_internal();
extern Object make_permanent_gsi_transfer_wrapper_structure_internal();
extern Object make_thread_array();
extern Object maybe_declare_all_gsi_sensors();
extern Object maybe_update_remote_icp_version_info_for_version();
extern Object memq_function();
extern Object mutate_global_property();
extern Object network_access_allowed_p();
extern Object notify_user();
extern Object notify_user_of_out_of_bounds_timestamp();
extern Object outstanding_gsi_array_wrapper_count();
extern Object outstanding_gsi_attribute_count();
extern Object outstanding_gsi_conses();
extern Object outstanding_gsi_extension_data_count();
extern Object outstanding_gsi_history_count();
extern Object outstanding_gsi_instance_count();
extern Object outstanding_gsi_instance_extension_count();
extern Object outstanding_gsi_transfer_wrapper_count();
extern Object peek_icp_byte();
extern Object post_on_message_board();
extern Object protect_gsi_api_call_p();
extern Object push_optimized_constant();
extern Object read_icp_boolean();
extern Object read_icp_byte();
extern Object read_icp_corresponding_object_index();
extern Object read_icp_do_not_reformat_message_p();
extern Object read_icp_fixnum();
extern Object read_icp_gsi_ds_update_interval();
extern Object read_icp_gsi_ds_value();
extern Object read_icp_gsi_permanent_remote_value();
extern Object read_icp_gsi_timestamp();
extern Object read_icp_gsi_value_vector();
extern Object read_icp_gsi_values();
extern Object read_icp_icp_tree();
extern Object read_icp_integer();
extern Object read_icp_item_reference();
extern Object read_icp_managed_double_float();
extern Object read_icp_remote_value();
extern Object read_icp_returned_gsi_sensor();
extern Object read_icp_text_string();
extern Object read_icp_unsigned_integer();
extern Object read_icp_unsigned_integer_or_nil();
extern Object receive_initial_message();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_string();
extern Object reclaim_gsi_array_wrapper_1();
extern Object reclaim_gsi_attribute_1_1();
extern Object reclaim_gsi_cons_1();
extern Object reclaim_gsi_extension_data();
extern Object reclaim_gsi_extension_data_internal_1();
extern Object reclaim_gsi_history_1_1();
extern Object reclaim_gsi_instance();
extern Object reclaim_gsi_instance_1_1();
extern Object reclaim_gsi_instance_extension_1_1();
extern Object reclaim_gsi_instance_for_context();
extern Object reclaim_gsi_instance_for_gsi();
extern Object reclaim_gsi_instance_for_user();
extern Object reclaim_gsi_list_1();
extern Object reclaim_gsi_list_function();
extern Object reclaim_gsi_list_star_1();
extern Object reclaim_gsi_remote_procedures();
extern Object reclaim_gsi_transfer_wrapper_1_1();
extern Object reclaim_gsi_transfer_wrapper_array();
extern Object reclaim_gsi_tree_1();
extern Object reclaim_gsi_value_vector();
extern Object reclaim_icp_list_1();
extern Object reclaim_icp_object_map();
extern Object reclaim_icp_object_map_for_gsi_instance();
extern Object reclaim_icp_port_entry();
extern Object reclaim_icp_port_entry_for_gsi_instance();
extern Object reclaim_if_evaluation_value_1();
extern Object reclaim_if_evaluation_value_function();
extern Object reclaim_if_gsi_instance_for_context();
extern Object reclaim_if_managed_float();
extern Object reclaim_if_text_or_gensym_string_function();
extern Object reclaim_managed_simple_float_array_of_length_1();
extern Object reclaim_text_or_gensym_string();
extern Object reclaim_text_string();
extern Object reclaim_wide_string();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object replenish_gsi_cons_pool();
extern Object replenish_gsi_list_pool();
extern Object resumable_icp_pop();
extern Object resumable_icp_pop_list_if_end_marker();
extern Object resumable_icp_push();
extern Object round_post4_dot_0_managed_float();
extern Object send_icp_begin_sensor_list();
extern Object send_icp_create_item_reference();
extern Object send_icp_define_gsi_interface();
extern Object send_icp_define_gsi_sensor();
extern Object send_icp_end_sensor_list();
extern Object send_icp_get_values_for_sensors_in_list();
extern Object send_icp_initialize_data_server();
extern Object send_icp_initialize_gsi_interface();
extern Object send_icp_load_sensor_list_element();
extern Object send_icp_modify_gsi_sensor_definition();
extern Object send_icp_pause_data_server();
extern Object send_icp_receive_gsi_sensor_value_vector();
extern Object send_icp_receive_timestamped_gsi_sensor_value_vector();
extern Object send_icp_receive_value_for_gsi_sensor();
extern Object send_icp_receive_value_for_gsi_sensor_with_timestamp();
extern Object send_icp_receive_value_for_ping_request();
extern Object send_icp_receive_values_for_gsi_sensors();
extern Object send_icp_register_corresponding_icp_object();
extern Object send_icp_reset_data_server();
extern Object send_icp_resume_data_server();
extern Object send_icp_return_initialize_gsi_interface_status();
extern Object send_icp_return_peer_version();
extern Object send_icp_send_data_values_if_any();
extern Object send_icp_set_values_for_sensors_in_list();
extern Object send_icp_start_data_server();
extern Object send_icp_stop_sending_values_for_sensors_in_list();
extern Object send_icp_write_user_message_string();
extern Object send_version_info();
extern Object set_access_form_for_gsi_instance();
extern Object set_gsi_attribute_is_identifying_p();
extern Object set_gsi_attribute_is_transient_p();
extern Object set_gsi_instance_owner();
extern Object set_gsi_instance_plist_value();
extern Object set_gsi_instance_value_type();
extern Object set_icp_object_index_for_gsi_instance();
extern Object shutdown_icp_socket_connection();
extern Object start_writing_icp_message();
extern Object symbol_for_gsi_string();
extern Object symbol_name_text_string();
extern Object update_object_pool_meters_list();
extern Object wide_string_to_gensym_string();
extern Object wide_string_to_gensym_string_for_gsi();
extern Object write_icp_boolean();
extern Object write_icp_byte();
extern Object write_icp_corresponding_object_index();
extern Object write_icp_do_not_reformat_message_p();
extern Object write_icp_fixnum();
extern Object write_icp_gsi_ds_update_interval();
extern Object write_icp_gsi_ds_value();
extern Object write_icp_gsi_permanent_remote_value();
extern Object write_icp_gsi_timestamp();
extern Object write_icp_gsi_value_vector();
extern Object write_icp_gsi_values();
extern Object write_icp_integer();
extern Object write_icp_item_reference();
extern Object write_icp_managed_double_float();
extern Object write_icp_maybe_suspend();
extern Object write_icp_remote_value();
extern Object write_icp_returned_gsi_sensor();
extern Object write_icp_text_string();
extern Object write_icp_unsigned_integer();
extern Object write_icp_unsigned_integer_or_nil();

#endif

/* Externally callable routines */

#ifdef USE_PROTOTYPES

extern double read_icp_double_float_1(void);
extern Object write_icp_double_float_1(double);

#else

extern double read_icp_double_float_1();
extern Object write_icp_double_float_1();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Abort_for_icp_catcher_qm, Qabort_for_icp_catcher_qm);
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Available_gsi_conses, Qavailable_gsi_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Available_gsi_conses_tail, Qavailable_gsi_conses_tail);
extern Object Available_gsi_conses_tail_vector;
extern Object Available_gsi_conses_vector;
extern Object Available_icp_conses_tail_vector;
extern Object Available_icp_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);
#define Bad_configuration FIX((SI_Long)1L)
extern Object Bytes_per_rtl_ptr;
#define Cancel_collection FIX((SI_Long)-1L)
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_gsi_array_wrappers, Qchain_of_available_gsi_array_wrappers);
extern Object Chain_of_available_gsi_array_wrappers_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_gsi_attributes, Qchain_of_available_gsi_attributes);
extern Object Chain_of_available_gsi_attributes_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_gsi_extension_datas, Qchain_of_available_gsi_extension_datas);
extern Object Chain_of_available_gsi_extension_datas_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_gsi_historys, Qchain_of_available_gsi_historys);
extern Object Chain_of_available_gsi_historys_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_gsi_instance_extensions, Qchain_of_available_gsi_instance_extensions);
extern Object Chain_of_available_gsi_instance_extensions_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_gsi_instances, Qchain_of_available_gsi_instances);
extern Object Chain_of_available_gsi_instances_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_gsi_transfer_wrappers, Qchain_of_available_gsi_transfer_wrappers);
extern Object Chain_of_available_gsi_transfer_wrappers_vector;
#define Collect_one_now FIX((SI_Long)0L)
extern Object Cons_pool_conses_to_make_at_a_time;
DECLARE_VARIABLE_WITH_SYMBOL(Corresponding_icp_object_index_for_item_reference, Qcorresponding_icp_object_index_for_item_reference);
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_buffer, Qcurrent_icp_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_port, Qcurrent_icp_port);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_read_trace_level, Qcurrent_icp_read_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_socket, Qcurrent_icp_socket);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_write_trace_level, Qcurrent_icp_write_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_slot_value_of_user_slot, Qcurrent_slot_value_of_user_slot);
DECLARE_VARIABLE_WITH_SYMBOL(Current_standard_icp_object_index_space, Qcurrent_standard_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_system_name, Qcurrent_system_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_temporary_icp_object_index_space, Qcurrent_temporary_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_write_icp_byte_position, Qcurrent_write_icp_byte_position);
#define Default_gsi_interface_countdown_timer_limit FIX((SI_Long)10L)
DECLARE_VARIABLE_WITH_SYMBOL(Disable_resumability, Qdisable_resumability);
#define G2_gsi_get_data FIX((SI_Long)13L)
#define G2_gsi_set_data FIX((SI_Long)14L)
extern Object Gsi_allocated_array_list_qm;
extern Object Gsi_allocated_string_list_qm;
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_array_wrapper_count, Qgsi_array_wrapper_count);
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_attribute_count, Qgsi_attribute_count);
#define Gsi_bits_per_instance_owner FIX((SI_Long)3L)
#define Gsi_close_fd FIX((SI_Long)9L)
extern Object Gsi_connection_established;
extern Object Gsi_connection_initializing;
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_cons_counter, Qgsi_cons_counter);
extern Object Gsi_cons_counter_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_context_to_socket_map, Qgsi_context_to_socket_map);
#define Gsi_disable_interleaving FIX((SI_Long)12L)
#define Gsi_do_not_reformat_messages FIX((SI_Long)15L)
extern Object Gsi_encoded_symbol_names_prop;
#define Gsi_error_handler FIX((SI_Long)17L)
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_extension_data_count, Qgsi_extension_data_count);
#define Gsi_g2_poll FIX((SI_Long)5L)
#define Gsi_get_tcp_port FIX((SI_Long)1L)
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_history_count, Qgsi_history_count);
#define Gsi_idle FIX((SI_Long)20L)
#define Gsi_initialize_context FIX((SI_Long)10L)
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_instance_count, Qgsi_instance_count);
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_instance_extension_count, Qgsi_instance_extension_count);
#define Gsi_interface_assumed_dead FIX((SI_Long)-1L)
#define Gsi_interface_icp_connection_dead FIX((SI_Long)-2L)
#define Gsi_interface_initializing FIX((SI_Long)0L)
#define Gsi_interface_running_ok FIX((SI_Long)2L)
#define Gsi_interface_waiting_for_response FIX((SI_Long)1L)
#define Gsi_interface_waiting_for_shutdown_ack FIX((SI_Long)-3L)
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_local_home, Qgsi_local_home);
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_magic_number, Qgsi_magic_number);
#define Gsi_magic_offset FIX((SI_Long)1L)
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_maximum_number_of_contexts, Qgsi_maximum_number_of_contexts);
#define Gsi_missing_procedure_handler FIX((SI_Long)18L)
extern Object Gsi_most_recent_error;
extern Object Gsi_most_recent_error_message;
extern Object Gsi_most_recent_error_remote_procedure_identifier;
#define Gsi_new_symbol_api FIX((SI_Long)10L)
#define Gsi_no_flush FIX((SI_Long)8L)
#define Gsi_no_signal_handlers FIX((SI_Long)5L)
#define Gsi_non_c FIX((SI_Long)3L)
#define Gsi_not_writing_fd FIX((SI_Long)24L)
#define Gsi_number_of_callbacks FIX((SI_Long)25L)
#define Gsi_number_of_options FIX((SI_Long)17L)
#define Gsi_one_cycle FIX((SI_Long)0L)
#define Gsi_open_fd FIX((SI_Long)8L)
#define Gsi_pause_context FIX((SI_Long)2L)
#define Gsi_protect_inner_calls FIX((SI_Long)14L)
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_protect_inner_calls_p, Qgsi_protect_inner_calls_p);
#define Gsi_read_callback FIX((SI_Long)6L)
#define Gsi_receive_deregistrations FIX((SI_Long)12L)
#define Gsi_receive_message FIX((SI_Long)15L)
#define Gsi_receive_registration FIX((SI_Long)11L)
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_reclaim_list_level, Qgsi_reclaim_list_level);
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_reclaim_list_qm, Qgsi_reclaim_list_qm);
#define Gsi_reset_context FIX((SI_Long)22L)
#define Gsi_resume_context FIX((SI_Long)3L)
#define Gsi_run_state_change FIX((SI_Long)16L)
#define Gsi_set_up FIX((SI_Long)0L)
#define Gsi_shutdown_context FIX((SI_Long)4L)
#define Gsi_start_context FIX((SI_Long)21L)
#define Gsi_string_check FIX((SI_Long)4L)
extern Object Gsi_suppress_output;
extern Object Gsi_timestamp_upper_bound;
#define Gsi_trace_run_loop FIX((SI_Long)13L)
#define Gsi_trace_run_state FIX((SI_Long)9L)
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_transfer_wrapper_count, Qgsi_transfer_wrapper_count);
#define Gsi_undefined_context FIX((SI_Long)-1L)
#define Gsi_use_gfloats FIX((SI_Long)2L)
#define Gsi_use_references FIX((SI_Long)11L)
#define Gsi_user_data_for_callbacks FIX((SI_Long)7L)
extern Object Gsi_user_data_of_symbol_prop;
#define Gsi_user_owns_gsi_items FIX((SI_Long)16L)
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_vector_length, Qgsi_vector_length);
#define Gsi_watchdog_function FIX((SI_Long)19L)
#define Gsi_wide_string_api FIX((SI_Long)6L)
#define Gsi_write_callback FIX((SI_Long)7L)
#define Gsi_writing_fd FIX((SI_Long)23L)
DECLARE_VARIABLE_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm, Qicp_buffer_of_start_of_message_series_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_buffers_for_message_group, Qicp_buffers_for_message_group);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm, Qicp_byte_position_of_start_of_message_series_qm);
extern Object Icp_connection_running;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_read_trace_cutoff_level_qm, Qicp_read_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_suspend, Qicp_suspend);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_write_trace_cutoff_level_qm, Qicp_write_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(In_unprotected_gsi_api_call_p, Qin_unprotected_gsi_api_call_p);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Index_to_array_of_transfer_wrappers, Qindex_to_array_of_transfer_wrappers);
DECLARE_VARIABLE_WITH_SYMBOL(Inhibit_corresponding_icp_object_making, Qinhibit_corresponding_icp_object_making);
DECLARE_VARIABLE_WITH_SYMBOL(Last_gsi_timestamp_day, Qlast_gsi_timestamp_day);
DECLARE_VARIABLE_WITH_SYMBOL(Last_gsi_timestamp_hour, Qlast_gsi_timestamp_hour);
DECLARE_VARIABLE_WITH_SYMBOL(Last_gsi_timestamp_month, Qlast_gsi_timestamp_month);
DECLARE_VARIABLE_WITH_SYMBOL(Last_gsi_timestamp_unix_time, Qlast_gsi_timestamp_unix_time);
DECLARE_VARIABLE_WITH_SYMBOL(Last_gsi_timestamp_year, Qlast_gsi_timestamp_year);
DECLARE_VARIABLE_WITH_SYMBOL(Make_gsi_instance_existing_instance, Qmake_gsi_instance_existing_instance);
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
#define No_error FIX((SI_Long)0L)
#define No_value_to_set Qnil
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_contexts_allocated, Qnumber_of_contexts_allocated);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_for_message_series, Qnumber_of_icp_bytes_for_message_series);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_in_message_group, Qnumber_of_icp_bytes_in_message_group);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer, Qnumber_of_icp_bytes_to_fill_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Profiling_enabled_qm, Qprofiling_enabled_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Resumable_icp_state, Qresumable_icp_state);
DECLARE_VARIABLE_WITH_SYMBOL(Rpc_argument_list_error, Qrpc_argument_list_error);
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
#define Size_of_array_of_transfer_wrappers FIX((SI_Long)50L)
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
DECLARE_VARIABLE_WITH_SYMBOL(Temporary_string_buffer, Qtemporary_string_buffer);
extern Object The_type_description_of_gsi_array_wrapper;
extern Object The_type_description_of_gsi_attribute;
extern Object The_type_description_of_gsi_extension_data;
extern Object The_type_description_of_gsi_history;
extern Object The_type_description_of_gsi_instance;
extern Object The_type_description_of_gsi_instance_extension;
extern Object The_type_description_of_gsi_transfer_wrapper;
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
DECLARE_VARIABLE_WITH_SYMBOL(Writing_icp_message_group, Qwriting_icp_message_group);
DECLARE_VARIABLE_WITH_SYMBOL(Writing_resumable_icp_messages_p, Qwriting_resumable_icp_messages_p);
