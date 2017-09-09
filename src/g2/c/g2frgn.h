/* g2frgn.h -- Header File for g2frgn.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qnum_eq;
extern Object Qeql;
extern Object Qerror;
extern Object Qfloat;
extern Object Qfunction;
extern Object Kinitial_element;
extern Object Qinteger;
extern Object Qmember;
extern Object Qquote;
extern Object Qsequence;
extern Object Qsymbol;
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

extern Object abort_g2(int,...);
extern Object add_as_frame_with_name(Object,Object);
extern Object add_class_to_environment(int,...);
extern Object add_frame_note(int,...);
extern Object add_grammar_rules_function(Object);
extern Object add_icp_message_handler(Object,Object);
extern Object add_to_frame_note_particulars_list_if_necessary(Object,Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_evaluation_sequence(Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object bytes_per_simple_vector(Object);
extern Object bytes_per_typed_simple_array(Object,Object);
extern Object c_native_clock_ticks_or_cache(Object,Object);
extern Object c_spawn_command_line_process(Object);
extern Object call_connected_foreign_function(Object,Object,Object,Object,Object,Object,Object);
extern Object call_foreign_function(Object,Object);
extern Object cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object change_slot_value(int,...);
extern Object check_foreign_function_for_argcount_agreement(Object,Object);
extern Object check_foreign_function_for_argtype_agreement(Object,Object);
extern Object check_foreign_function_for_return_type_agreement(Object,Object);
extern Object check_foreign_function_for_type_and_count_agreement(Object,Object);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object chestnut_floorf_function(Object,Object);
extern Object cleanup_for_foreign_function_declaration(Object);
extern Object clear_foreign_function_registry_internal(Object);
extern Object clear_foreign_function_registry_internal_tree(Object);
extern Object clear_optimized_constants(void);
extern Object close_foreign_image_socket(Object);
extern Object collect_subclasses(Object);
extern Object compile_default_foreign_function_timeout_interval_for_slot(int,...);
extern Object compile_foreign_function_declaration_for_slot(int,...);
extern Object compile_foreign_function_name_for_slot(int,...);
extern Object compile_foreign_function_timeout_interval_for_slot(int,...);
extern Object connect_to_external_foreign_image(Object);
extern Object connect_to_foreign_image(Object);
extern Object connection_specification_to_foreign_image_function(Object);
extern Object convert_text_string_to_ascii_filename_as_much_as_possible(Object);
extern Object copy_for_slot_value(Object);
extern Object copy_frame_serial_number(Object);
extern Object copy_gensym_pathname(Object);
extern Object copy_list_using_gensym_conses_1(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text_string(Object);
extern Object copy_wide_string(Object);
extern Object create_external_foreign_image_connection(Object,Object);
extern Object create_foreign_image_connection(Object);
extern Object define_type_specification_explicit_complex_type(Object,Object);
extern Object delete_as_frame_with_name(Object,Object);
extern Object delete_balanced_binary_tree_entry(Object,Object,Object,Object);
extern Object delete_frame_note_if_any(Object,Object);
extern Object delete_gensym_element_1(Object,Object);
extern Object deregister_all_icp_connection_loss_callbacks(Object);
extern Object direct_structure_method(Object,Object);
extern Object disconnect_from_all_foreign_images(void);
extern Object disconnect_from_external_foreign_image(Object);
extern Object disconnect_from_foreign_image(Object);
extern Object disconnect_from_foreign_images_in_list(Object);
extern Object element_of_foreign_linking_info_structure_memory_usage(void);
extern Object emit_icp_read_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_write_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object end_icp_message_group(void);
extern Object end_of_foreign_linking_info_p(Object);
extern Object equalw(Object,Object);
extern Object extend_current_gensym_string(int,...);
extern Object external_foreign_image_disconnection_spec_p(Object);
extern Object ff_connect_callback(Object);
extern Object fixnum_time_interval(Object);
extern Object flatten_binary_tree(Object);
extern Object flatten_foreign_function_registry_internal(Object);
extern Object flush_and_shutdown_icp_socket(Object);
extern Object flush_icp_output_ports(void);
extern Object foreign_function_call_info_structure_memory_usage(void);
extern Object foreign_function_entry_structure_memory_usage(void);
extern Object foreign_function_image_info_structure_memory_usage(void);
extern Object foreign_function_registry_internal_hash_vector_131_vector_memory_usage(void);
extern Object future_task_schedule_2(Object);
extern Object g2_event_cycle_handling_windows_quit(void);
extern Object generate_float_vector(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_delete_file(Object);
extern Object gensym_equal(Object,Object);
extern Object gensym_list_3(Object,Object,Object);
extern Object gensym_list_4(Object,Object,Object,Object);
extern Object gensym_namestring_as_text_string(int,...);
extern Object gensym_pathname(Object);
extern Object gensym_pathnames_equal_enough_p(Object,Object);
extern Object gensym_probe_file(Object);
extern Object gensym_search_complex(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object get_foreign_image_info_from_connection_spec(Object);
extern Object get_foreign_image_info_from_icp_socket(Object);
extern Object get_foreign_image_info_from_pathname(Object);
extern Object get_local_host_addresses(void);
extern Object get_local_host_name(void);
extern Object get_next_unused_foreign_image_port_or_task(void);
extern Object get_or_create_foreign_function_image_index(void);
extern Object get_or_make_foreign_function_entry(Object,Object,Object,Object,Object,Object);
extern Object get_or_make_up_designation_for_block(Object);
extern Object get_symbol_properties_function(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object handle_external_foreign_image_connection_failure(Object,Object);
extern Object handle_ff_connect_failure(Object,Object);
extern Object handle_icp_call_foreign_function(void);
extern Object handle_icp_kill_foreign_function_server(void);
extern Object handle_icp_provide_foreign_function_registry(void);
extern Object handle_icp_provide_foreign_function_registry__body(Object,Object,Object);
extern Object handle_icp_request_foreign_function_registry(void);
extern Object handle_icp_request_foreign_function_registry__body(Object,Object);
extern Object handle_icp_return_foreign_function_value(void);
extern Object handle_icp_return_foreign_function_value__body(Object);
extern Object handle_icp_shut_down_foreign_server_context(void);
extern Object handle_icp_signal_foreign_function_error(void);
extern Object handle_icp_signal_foreign_function_error__body(Object,Object,Object,Object,Object,Object);
extern Object handle_internal_foreign_image_connection_failure(Object,Object);
extern Object icp_connection_being_shutdown_qm(Object);
extern Object icp_connection_open_p(Object);
extern Object icp_error_internal(Object,Object,Object,Object,Object);
extern Object initialize_current_foreign_function_call_info(void);
extern Object initialize_external_foreign_function_image(Object,Object);
extern Object initialize_for_foreign_function_declaration(Object);
extern Object initialize_foreign_function_image(Object);
extern Object initialize_foreign_function_image_if_possible(int,...);
extern Object initialize_foreign_image_connection_mode(void);
extern Object instantaneous_icp_reader_byte_count(void);
extern Object instantaneous_icp_writer_byte_count(void);
extern Object intern_text_string(int,...);
extern Object kill_foreign_image(Object);
extern Object kill_foreign_image_and_possibly_reconnect(Object);
extern Object kill_foreign_image_process_unconditionally(Object);
extern Object kill_foreign_image_unconditionally(Object);
extern Object link_completed_foreign_function_declarations(void);
extern Object load_and_initialize_type_description(Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_element_of_foreign_linking_info_1(Object,Object);
extern Object make_empty_foreign_linking_info(void);
extern Object make_foreign_function_call_info_1(void);
extern Object make_foreign_function_entry_1(Object,Object,Object,Object,Object);
extern Object make_foreign_function_image_info_1(void);
extern Object make_foreign_function_registry(void);
extern Object make_foreign_function_registry_internal_hash_vector(void);
extern Object make_gensym_list_1(Object);
extern Object make_icp_connection(int,...);
extern Object make_icp_connection_to_foreign_image(Object);
extern Object make_permanent_element_of_foreign_linking_info_structure_internal(void);
extern Object make_permanent_foreign_function_call_info_structure_internal(void);
extern Object make_permanent_foreign_function_entry_structure_internal(void);
extern Object make_permanent_foreign_function_image_info_structure_internal(void);
extern Object make_permanent_foreign_function_registry_internal_hash_vector_131_vector_internal(void);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object mutate_global_property(Object,Object,Object);
extern Object new_call_foreign_function(Object,Object,Object,Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object notify_user(int,...);
extern Object out_foreign_function_registry_internal_hash_vector_131_vectors(void);
extern Object outstanding_element_of_foreign_linking_info_count(void);
extern Object outstanding_foreign_function_call_info_count(void);
extern Object outstanding_foreign_function_entry_count(void);
extern Object outstanding_foreign_function_image_info_count(void);
extern Object pathname_of_a_connected_foreign_image_p(Object);
extern Object phrase_cons(Object,Object);
extern Object print_constant(int,...);
extern Object push_optimized_constant(Object);
extern Object put_box_translation_and_text_slot_value_for_foreign_function_declaration(Object,Object,Object);
extern Object put_foreign_function_linked_p_where_slot_is_absent(Object,Object);
extern Object put_name_in_foreign_image(Object,Object,Object);
extern Object put_name_in_foreign_language_where_slot_is_absent(Object,Object);
extern Object put_wait_strategy_where_slot_is_absent(Object,Object);
extern Object raw_stack_error_named_error(Object,Object);
extern Object read_icp_byte(void);
extern Object read_icp_fixnum(void);
extern Object read_icp_foreign_function_argument(void);
extern Object read_icp_foreign_function_value(void);
extern Object read_icp_integer(void);
extern Object read_icp_list_of_foreign_function_registrations_qm(void);
extern Object read_icp_text_string(void);
extern Object reclaim_binary_tree_element_1(Object);
extern Object reclaim_element_of_foreign_linking_info_1(Object);
extern Object reclaim_empty_foreign_linking_info(Object);
extern Object reclaim_foreign_function_call_info_1(Object);
extern Object reclaim_foreign_function_entry(Object);
extern Object reclaim_foreign_function_entry_internal_1(Object);
extern Object reclaim_foreign_function_image_info(Object);
extern Object reclaim_foreign_function_registry_internal(Object);
extern Object reclaim_foreign_function_registry_internal_hash_vector(Object);
extern Object reclaim_foreign_function_registry_internal_tree_for_hash_leaves(Object);
extern Object reclaim_foreign_image_info_internal_1(Object);
extern Object reclaim_frame_serial_number(Object);
extern Object reclaim_gensym_cons_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_pathname(Object);
extern Object reclaim_gensym_tree_1(Object);
extern Object reclaim_list_of_foreign_function_registrations(Object);
extern Object reclaim_managed_simple_float_array_of_length_1(Object);
extern Object reclaim_network_addresses(Object);
extern Object reclaim_pathname_or_string(Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_slot_value(Object);
extern Object reclaim_text_string(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object register_icp_connection_loss_callback(Object,Object);
extern Object remove_foreign_image_info_from_all_foreign_function_images(Object);
extern Object remove_unlinkability_info_from_foreign_function_declaration(Object);
extern Object replenish_gensym_cons_pool(void);
extern Object resumable_icp_pop(void);
extern Object resumable_icp_pop_list_if_end_marker(void);
extern Object resumable_icp_push(Object);
extern Object send_icp_call_foreign_function(Object);
extern Object send_icp_kill_foreign_function_server(Object,Object);
extern Object send_icp_provide_foreign_function_registry(Object,Object,Object);
extern Object send_icp_request_foreign_function_registry(Object,Object);
extern Object send_icp_return_foreign_function_value(Object);
extern Object send_icp_shut_down_foreign_server_context(void);
extern Object send_icp_signal_foreign_function_error(Object,Object,Object,Object,Object,Object);
extern Object set_balanced_binary_tree_entry(Object,Object,Object,Object,Object,Object,Object);
extern Object set_evaluation_value_to_category_function(Object,Object);
extern Object set_lookup_slot_value_1(Object,Object,Object);
extern Object set_property_value_function(Object,Object,Object);
extern Object set_slot_value_to_evaluation_value_function(Object,Object);
extern Object setup_network_connection_for_connect(int,...);
extern Object shutdown_icp_socket_connection(int,...);
extern Object spawn_foreign_function_image(Object,Object,Object);
extern Object splice_element_into_foreign_linking_info(Object,Object);
extern Object splice_element_out_of_foreign_linking_info(Object);
extern Object start_writing_icp_message(Object);
extern Object string_eq_w(Object,Object);
extern Object sxhashw(Object);
extern Object symbol_name_text_string(Object);
extern Object text_string_p(Object);
extern Object text_string_parse_integer_function(Object,Object,Object,Object);
extern Object tformat(int,...);
extern Object tformat_stack_error_text_string(int,...);
extern Object tformat_text_string(int,...);
extern Object tprin(Object,Object);
extern Object twrite(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_fixnum(Object);
extern Object twrite_foreign_image_connection_spec(Object);
extern Object twrite_general_string(Object);
extern Object twrite_icp_connection_spec(Object);
extern Object twrite_wide_character(Object);
extern Object type_error_in_setter(Object,Object,Object,Object,Object,Object,Object);
extern Object type_specification_type_p__with_explanation(Object,Object);
extern Object update_foreign_function_linking(Object,Object,Object);
extern Object update_foreign_function_registry(Object,Object);
extern Object update_frame_status(Object,Object,Object);
extern Object update_object_pool_meters_list(Object);
extern Object windows_platform_p(void);
extern Object write_default_foreign_function_timeout_interval_from_slot(Object,Object);
extern Object write_foreign_function_name_from_slot(Object,Object);
extern Object write_foreign_function_timeout_interval_from_slot(Object,Object);
extern Object write_icp_byte(Object);
extern Object write_icp_foreign_function_argument(Object);
extern Object write_icp_foreign_function_value(Object);
extern Object write_icp_integer(Object);
extern Object write_icp_list_of_foreign_function_registrations_qm(Object);
extern Object write_icp_text_string(Object);

#else

extern Object abort_g2();
extern Object add_as_frame_with_name();
extern Object add_class_to_environment();
extern Object add_frame_note();
extern Object add_grammar_rules_function();
extern Object add_icp_message_handler();
extern Object add_to_frame_note_particulars_list_if_necessary();
extern Object allocate_byte_vector_16();
extern Object allocate_evaluation_sequence();
extern Object bytes_per_double_float_simple_array();
extern Object bytes_per_simple_vector();
extern Object bytes_per_typed_simple_array();
extern Object c_native_clock_ticks_or_cache();
extern Object c_spawn_command_line_process();
extern Object call_connected_foreign_function();
extern Object call_foreign_function();
extern Object cancel_and_reclaim_scheduled_queue_element_1();
extern Object change_slot_value();
extern Object check_foreign_function_for_argcount_agreement();
extern Object check_foreign_function_for_argtype_agreement();
extern Object check_foreign_function_for_return_type_agreement();
extern Object check_foreign_function_for_type_and_count_agreement();
extern Object check_if_superior_classes_are_defined();
extern Object chestnut_floorf_function();
extern Object cleanup_for_foreign_function_declaration();
extern Object clear_foreign_function_registry_internal();
extern Object clear_foreign_function_registry_internal_tree();
extern Object clear_optimized_constants();
extern Object close_foreign_image_socket();
extern Object collect_subclasses();
extern Object compile_default_foreign_function_timeout_interval_for_slot();
extern Object compile_foreign_function_declaration_for_slot();
extern Object compile_foreign_function_name_for_slot();
extern Object compile_foreign_function_timeout_interval_for_slot();
extern Object connect_to_external_foreign_image();
extern Object connect_to_foreign_image();
extern Object connection_specification_to_foreign_image_function();
extern Object convert_text_string_to_ascii_filename_as_much_as_possible();
extern Object copy_for_slot_value();
extern Object copy_frame_serial_number();
extern Object copy_gensym_pathname();
extern Object copy_list_using_gensym_conses_1();
extern Object copy_out_current_wide_string();
extern Object copy_text_string();
extern Object copy_wide_string();
extern Object create_external_foreign_image_connection();
extern Object create_foreign_image_connection();
extern Object define_type_specification_explicit_complex_type();
extern Object delete_as_frame_with_name();
extern Object delete_balanced_binary_tree_entry();
extern Object delete_frame_note_if_any();
extern Object delete_gensym_element_1();
extern Object deregister_all_icp_connection_loss_callbacks();
extern Object direct_structure_method();
extern Object disconnect_from_all_foreign_images();
extern Object disconnect_from_external_foreign_image();
extern Object disconnect_from_foreign_image();
extern Object disconnect_from_foreign_images_in_list();
extern Object element_of_foreign_linking_info_structure_memory_usage();
extern Object emit_icp_read_trace();
extern Object emit_icp_write_trace();
extern Object end_icp_message_group();
extern Object end_of_foreign_linking_info_p();
extern Object equalw();
extern Object extend_current_gensym_string();
extern Object external_foreign_image_disconnection_spec_p();
extern Object ff_connect_callback();
extern Object fixnum_time_interval();
extern Object flatten_binary_tree();
extern Object flatten_foreign_function_registry_internal();
extern Object flush_and_shutdown_icp_socket();
extern Object flush_icp_output_ports();
extern Object foreign_function_call_info_structure_memory_usage();
extern Object foreign_function_entry_structure_memory_usage();
extern Object foreign_function_image_info_structure_memory_usage();
extern Object foreign_function_registry_internal_hash_vector_131_vector_memory_usage();
extern Object future_task_schedule_2();
extern Object g2_event_cycle_handling_windows_quit();
extern Object generate_float_vector();
extern Object gensym_cons_1();
extern Object gensym_delete_file();
extern Object gensym_equal();
extern Object gensym_list_3();
extern Object gensym_list_4();
extern Object gensym_namestring_as_text_string();
extern Object gensym_pathname();
extern Object gensym_pathnames_equal_enough_p();
extern Object gensym_probe_file();
extern Object gensym_search_complex();
extern Object get_foreign_image_info_from_connection_spec();
extern Object get_foreign_image_info_from_icp_socket();
extern Object get_foreign_image_info_from_pathname();
extern Object get_local_host_addresses();
extern Object get_local_host_name();
extern Object get_next_unused_foreign_image_port_or_task();
extern Object get_or_create_foreign_function_image_index();
extern Object get_or_make_foreign_function_entry();
extern Object get_or_make_up_designation_for_block();
extern Object get_symbol_properties_function();
extern Object getfq_function_no_default();
extern Object handle_external_foreign_image_connection_failure();
extern Object handle_ff_connect_failure();
extern Object handle_icp_call_foreign_function();
extern Object handle_icp_kill_foreign_function_server();
extern Object handle_icp_provide_foreign_function_registry();
extern Object handle_icp_provide_foreign_function_registry__body();
extern Object handle_icp_request_foreign_function_registry();
extern Object handle_icp_request_foreign_function_registry__body();
extern Object handle_icp_return_foreign_function_value();
extern Object handle_icp_return_foreign_function_value__body();
extern Object handle_icp_shut_down_foreign_server_context();
extern Object handle_icp_signal_foreign_function_error();
extern Object handle_icp_signal_foreign_function_error__body();
extern Object handle_internal_foreign_image_connection_failure();
extern Object icp_connection_being_shutdown_qm();
extern Object icp_connection_open_p();
extern Object icp_error_internal();
extern Object initialize_current_foreign_function_call_info();
extern Object initialize_external_foreign_function_image();
extern Object initialize_for_foreign_function_declaration();
extern Object initialize_foreign_function_image();
extern Object initialize_foreign_function_image_if_possible();
extern Object initialize_foreign_image_connection_mode();
extern Object instantaneous_icp_reader_byte_count();
extern Object instantaneous_icp_writer_byte_count();
extern Object intern_text_string();
extern Object kill_foreign_image();
extern Object kill_foreign_image_and_possibly_reconnect();
extern Object kill_foreign_image_process_unconditionally();
extern Object kill_foreign_image_unconditionally();
extern Object link_completed_foreign_function_declarations();
extern Object load_and_initialize_type_description();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_element_of_foreign_linking_info_1();
extern Object make_empty_foreign_linking_info();
extern Object make_foreign_function_call_info_1();
extern Object make_foreign_function_entry_1();
extern Object make_foreign_function_image_info_1();
extern Object make_foreign_function_registry();
extern Object make_foreign_function_registry_internal_hash_vector();
extern Object make_gensym_list_1();
extern Object make_icp_connection();
extern Object make_icp_connection_to_foreign_image();
extern Object make_permanent_element_of_foreign_linking_info_structure_internal();
extern Object make_permanent_foreign_function_call_info_structure_internal();
extern Object make_permanent_foreign_function_entry_structure_internal();
extern Object make_permanent_foreign_function_image_info_structure_internal();
extern Object make_permanent_foreign_function_registry_internal_hash_vector_131_vector_internal();
extern Object make_permanent_schedule_task_structure_internal();
extern Object mutate_global_property();
extern Object new_call_foreign_function();
extern Object note_change_to_block_1();
extern Object notify_user();
extern Object out_foreign_function_registry_internal_hash_vector_131_vectors();
extern Object outstanding_element_of_foreign_linking_info_count();
extern Object outstanding_foreign_function_call_info_count();
extern Object outstanding_foreign_function_entry_count();
extern Object outstanding_foreign_function_image_info_count();
extern Object pathname_of_a_connected_foreign_image_p();
extern Object phrase_cons();
extern Object print_constant();
extern Object push_optimized_constant();
extern Object put_box_translation_and_text_slot_value_for_foreign_function_declaration();
extern Object put_foreign_function_linked_p_where_slot_is_absent();
extern Object put_name_in_foreign_image();
extern Object put_name_in_foreign_language_where_slot_is_absent();
extern Object put_wait_strategy_where_slot_is_absent();
extern Object raw_stack_error_named_error();
extern Object read_icp_byte();
extern Object read_icp_fixnum();
extern Object read_icp_foreign_function_argument();
extern Object read_icp_foreign_function_value();
extern Object read_icp_integer();
extern Object read_icp_list_of_foreign_function_registrations_qm();
extern Object read_icp_text_string();
extern Object reclaim_binary_tree_element_1();
extern Object reclaim_element_of_foreign_linking_info_1();
extern Object reclaim_empty_foreign_linking_info();
extern Object reclaim_foreign_function_call_info_1();
extern Object reclaim_foreign_function_entry();
extern Object reclaim_foreign_function_entry_internal_1();
extern Object reclaim_foreign_function_image_info();
extern Object reclaim_foreign_function_registry_internal();
extern Object reclaim_foreign_function_registry_internal_hash_vector();
extern Object reclaim_foreign_function_registry_internal_tree_for_hash_leaves();
extern Object reclaim_foreign_image_info_internal_1();
extern Object reclaim_frame_serial_number();
extern Object reclaim_gensym_cons_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_pathname();
extern Object reclaim_gensym_tree_1();
extern Object reclaim_list_of_foreign_function_registrations();
extern Object reclaim_managed_simple_float_array_of_length_1();
extern Object reclaim_network_addresses();
extern Object reclaim_pathname_or_string();
extern Object reclaim_schedule_task_args();
extern Object reclaim_slot_value();
extern Object reclaim_text_string();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object register_icp_connection_loss_callback();
extern Object remove_foreign_image_info_from_all_foreign_function_images();
extern Object remove_unlinkability_info_from_foreign_function_declaration();
extern Object replenish_gensym_cons_pool();
extern Object resumable_icp_pop();
extern Object resumable_icp_pop_list_if_end_marker();
extern Object resumable_icp_push();
extern Object send_icp_call_foreign_function();
extern Object send_icp_kill_foreign_function_server();
extern Object send_icp_provide_foreign_function_registry();
extern Object send_icp_request_foreign_function_registry();
extern Object send_icp_return_foreign_function_value();
extern Object send_icp_shut_down_foreign_server_context();
extern Object send_icp_signal_foreign_function_error();
extern Object set_balanced_binary_tree_entry();
extern Object set_evaluation_value_to_category_function();
extern Object set_lookup_slot_value_1();
extern Object set_property_value_function();
extern Object set_slot_value_to_evaluation_value_function();
extern Object setup_network_connection_for_connect();
extern Object shutdown_icp_socket_connection();
extern Object spawn_foreign_function_image();
extern Object splice_element_into_foreign_linking_info();
extern Object splice_element_out_of_foreign_linking_info();
extern Object start_writing_icp_message();
extern Object string_eq_w();
extern Object sxhashw();
extern Object symbol_name_text_string();
extern Object text_string_p();
extern Object text_string_parse_integer_function();
extern Object tformat();
extern Object tformat_stack_error_text_string();
extern Object tformat_text_string();
extern Object tprin();
extern Object twrite();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_fixnum();
extern Object twrite_foreign_image_connection_spec();
extern Object twrite_general_string();
extern Object twrite_icp_connection_spec();
extern Object twrite_wide_character();
extern Object type_error_in_setter();
extern Object type_specification_type_p__with_explanation();
extern Object update_foreign_function_linking();
extern Object update_foreign_function_registry();
extern Object update_frame_status();
extern Object update_object_pool_meters_list();
extern Object windows_platform_p();
extern Object write_default_foreign_function_timeout_interval_from_slot();
extern Object write_foreign_function_name_from_slot();
extern Object write_foreign_function_timeout_interval_from_slot();
extern Object write_icp_byte();
extern Object write_icp_foreign_function_argument();
extern Object write_icp_foreign_function_value();
extern Object write_icp_integer();
extern Object write_icp_list_of_foreign_function_registrations_qm();
extern Object write_icp_text_string();

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
extern Object Abort_for_icp_catcher_qm;
extern Object Active_icp_sockets;
extern Object All_external_foreign_function_images_qm;
extern Object All_foreign_function_images_qm;
extern Object Available_foreign_function_registry_internal_hash_vector_131_vectors;
extern Object Available_gensym_conses;
extern Object Backtrace_stack_for_internal_error;
extern Object Bad_phrase;
extern Object Cached_tcpip_listener_address_qm;
extern Object Cached_timed_out_foreign_function_name_qm;
extern Object Cached_top_of_stack;
extern Object Chain_of_available_element_of_foreign_linking_infos;
extern Object Chain_of_available_foreign_function_call_infos;
extern Object Chain_of_available_foreign_function_entrys;
extern Object Chain_of_available_foreign_function_image_infos;
extern Object Chain_of_available_schedule_tasks;
extern Object Class_description_gkbprop;
extern Object Context_of_type_failure;
extern Object Count_of_foreign_function_registry_internal_hash_vector_131_vectors;
extern Object Created_simple_float_array_pool_arrays;
extern Object Current_foreign_function_call_info;
extern Object Current_foreign_image_pathname_qm;
extern Object Current_g2_time;
extern Object Current_gensym_string;
extern Object Current_icp_buffer;
extern Object Current_icp_port;
extern Object Current_icp_read_trace_level;
extern Object Current_icp_socket;
extern Object Current_icp_write_trace_level;
extern Object Current_schedule_task;
extern Object Current_twriting_output_type;
extern Object Current_wide_string;
extern Object Current_wide_string_list;
extern Object Current_write_icp_byte_position;
extern Object Disable_resumability;
extern Object During_ffi_call_qm;
extern Object Element_of_foreign_linking_info_count;
extern Object Ff_connect_finalized;
extern Object Fill_pointer_for_current_gensym_string;
extern Object Fill_pointer_for_current_wide_string;
extern Object Final_element_marker_for_foreign_linking_info;
extern Object Fixnum_time_units_per_second;
extern Object Foreign_function_call_info_count;
extern Object Foreign_function_declaration_class_description;
extern Object Foreign_function_entry_count;
extern Object Foreign_function_image_info_count;
#define Foreign_function_integer_type_tag FIX((SI_Long)1L)
#define Foreign_function_real_type_tag FIX((SI_Long)6L)
extern Object Foreign_function_registry;
#define Foreign_function_symbol_type_tag FIX((SI_Long)3L)
#define Foreign_function_text_type_tag FIX((SI_Long)4L)
extern Object Foreign_image_connection_checkup_interval_in_ms;
extern Object Foreign_image_connection_mode;
extern Object Frame_note_index;
extern Object Frame_note_index_skip;
extern Object Highest_foreign_image_index;
extern Object Icp_buffer_of_start_of_message_series_qm;
extern Object Icp_buffers_for_message_group;
extern Object Icp_byte_position_of_start_of_message_series_qm;
extern Object Icp_output_ports_to_flush;
extern Object Icp_read_trace_cutoff_level_qm;
extern Object Icp_suspend;
extern Object Icp_write_trace_cutoff_level_qm;
extern Object Index_of_top_of_backtrace_stack;
extern Object Initial_icp_version_info_enabled_p;
extern Object Instances_specific_to_this_class_kbprop;
extern Object Largest_allowable_foreign_function_timeout_interval;
#define Largest_known_fixnum_time_units_per_second FIX((SI_Long)1000L)
extern Object Last_slot_checked_of_type_failure;
extern Object List_of_module_pre_conflict_resolution_post_loading_functions;
extern Object List_of_switched_and_module_post_loading_functions;
extern Object Local_file_system;
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
extern Object Maximum_retries_for_foreign_image_connection;
extern Object Milliseconds_between_retries_for_foreign_image_connection;
extern Object Milliseconds_to_sleep_after_connection_on_pc_platforms;
extern Object Milliseconds_to_sleep_before_connecting_to_foreign_image;
extern Object No_value;
extern Object Noting_changes_to_kb_p;
extern Object Number_of_icp_bytes_for_message_series;
extern Object Number_of_icp_bytes_in_message_group;
extern Object Number_of_icp_bytes_to_fill_buffer;
extern Object Profiling_enabled_qm;
extern Object Reading_kb_p;
extern Object Reason_for_type_failure;
extern Object Resumable_icp_state;
extern Object Scheduler_enabled_qm;
extern Object Scope_conses;
#define Shutdown_context_only_flag_clear FIX((SI_Long)0L)
#define Shutdown_context_only_flag_set FIX((SI_Long)1L)
extern Object Simple_float_array_pool_memory_usage;
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
extern Object Spawn_command_line_process_failure;
extern Object Starting_element_marker_for_foreign_linking_info;
extern Object Structure_being_reclaimed;
extern Object Tcp_ip_port_offset_for_foreign_images;
extern Object Tcpip_external_foreign_image_prologue;
extern Object The_type_description_of_element_of_foreign_linking_info;
extern Object The_type_description_of_foreign_function_call_info;
extern Object The_type_description_of_foreign_function_entry;
extern Object The_type_description_of_foreign_function_image_info;
extern Object Timing_parameters;
extern Object Too_long_timeout_error_text;
extern Object Total_foreign_image_connection_checkup_interval_in_ms;
extern Object Total_length_of_current_gensym_string;
extern Object Total_length_of_current_wide_string;
extern Object Type_at_type_failure;
extern Object Unused_foreign_image_indices;
extern Object Value_at_type_failure;
extern Object Vector_of_simple_float_array_pools;
extern Object Wait_interval_before_killing_foreign_process;
extern Object Writing_icp_message_group;
