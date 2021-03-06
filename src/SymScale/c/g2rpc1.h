/* g2rpc1.h -- Header File for g2rpc1.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qnum_eq;
extern Object Qand;
extern Object Qcdr;
extern Object Qdeclare;
extern Object Qerror;
extern Object Qfloat;
extern Object Qinteger;
extern Object Qmember;
extern Object Qnot;
extern Object Qnumber;
extern Object Qquote;
extern Object Qsequence;
extern Object Qsymbol;
extern Object Ktype;
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

extern Object abort_incoming_rpc_call(Object);
extern Object abort_outgoing_remote_procedure_call(Object);
extern Object abort_procedure_invocation(int,...);
extern Object abort_rpc_call_and_reclaim_identifier(Object);
extern Object activate_for_remote_procedure_declaration(Object);
extern Object add_class_to_environment(int,...);
extern Object add_grammar_rules_function(Object);
extern Object add_interface_to_alist(Object,Object,Object);
extern Object all_elements_ok_for_parallel_rpc_start(Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_evaluation_sequence(Object);
extern Object allocate_evaluation_structure(Object);
extern Object allocate_managed_simple_vector(Object);
extern Object analyze_compiled_items_for_consistency(Object);
extern Object assign_index_in_index_space(Object);
extern Object break_out_of_debug_messages(void);
extern Object bytes_per_double_float_simple_array(Object);
extern Object bytes_per_simple_vector(Object);
extern Object call_remote_procedure(Object,Object,Object,Object);
extern Object call_remote_procedure_after_checks(Object,Object,Object,Object,Object);
extern Object call_system_defined_rpc(Object,Object,Object,Object);
extern Object cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object change_slot_value(int,...);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object check_that_remote_procedure_can_be_started_or_called(Object,Object,Object,Object);
extern Object class_type_specification_p(Object);
extern Object clear_optimized_constants(void);
extern Object collect_subclasses(Object);
extern Object compile_remote_procedure_declaration_for_slot(int,...);
extern Object compile_remote_procedure_name_for_slot(int,...);
extern Object constant_queue_delete(int,...);
extern Object constant_queue_pop_left(int,...);
extern Object constant_queue_push_right(Object,Object);
extern Object convert_description_list_to_managed_array(int,...);
extern Object convert_remote_procedure_description_to_structure(Object);
extern Object copy_for_phrase(Object);
extern Object copy_for_slot_value(Object);
extern Object copy_frame_serial_number(Object);
extern Object copy_gensym_string_portion(Object,Object,Object);
extern Object copy_icp_buffer_chain(Object);
extern Object copy_list_using_eval_conses_1(Object);
extern Object copy_list_using_phrase_conses(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_partial_gensym_string(Object,Object);
extern Object copy_text_string(Object);
extern Object copy_wide_string(Object);
extern Object deactivate_for_remote_procedure_declaration(Object);
extern Object deassign_index_in_index_space(Object,Object);
extern Object define_type_specification_explicit_complex_type(Object,Object);
extern Object delete_frame(Object);
extern Object delete_proc_element_1(Object,Object);
extern Object deregister_remote_procedure_call_for_start(Object);
extern Object direct_structure_method(Object,Object);
extern Object encode_remaining_into_remote_procedure_type(Object);
extern Object encode_remaining_into_remote_procedure_type_1(Object);
extern Object encode_remaining_into_remote_procedure_type_2(Object);
extern Object end_icp_message_group(void);
extern Object enlarge_index_space(Object,Object);
extern Object error_text_p(Object);
extern Object eval_cons_1(Object,Object);
extern Object evaluate_designation(Object,Object);
extern Object evaluate_procedure_or_method_designation(Object);
extern Object evaluation_truth_value_is_true_p(Object);
extern Object evaluation_value_type(Object);
extern Object evaluation_value_value(Object);
extern Object execute_fast_parallel_remote_procedure_start(Object,Object,Object,Object,Object,Object);
extern Object execute_parallel_remote_procedure_start(Object,Object,Object,Object);
extern Object execute_remote_procedure_start(Object,Object,Object,Object,Object);
extern Object execute_scheduled_remote_procedure_start(Object,Object);
extern Object find_network_interface_for_icp_socket(Object,Object);
extern Object find_remote_procedure_call_for_code_body_invocation(Object);
extern Object fix_remote_procedure_declaration_descriptions(Object);
extern Object flush_icp_output_ports(void);
extern Object frame_serial_number_setf_helper_1(Object,Object);
extern Object framep_function(Object);
extern Object future_task_schedule_2(Object);
extern Object g2_api_test_1_system_rpc_internal(Object,Object);
extern Object g2_current_remote_interface_lisp_side(void);
extern Object g2_list_or_array_element_type_may_contain_item_p(Object);
extern Object g2_list_structure_next(Object,Object);
extern Object g2_prefer_kb_procedures_to_system_defined(Object);
extern Object g2_prefer_kb_procedures_to_system_defined_system_rpc_internal(Object,Object);
extern Object g2_reclaim_sending_resumable_object(int,...);
extern Object g2_to_g2_data_interface_p_function(Object);
extern Object generate_float_vector(Object);
extern Object generate_procedure_and_code_body_invocation_in_place(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object gensym_search_simple(Object,Object);
extern Object gensym_string_length(Object);
extern Object gensym_symbol_name(Object);
extern Object get_copy_of_rpd_spec(Object,Object);
extern Object get_icp_interface_for_remote_procedure_call(Object,Object);
extern Object get_instance_with_name_if_any(Object,Object);
extern Object get_item_from_local_handle(Object,Object);
extern Object get_local_host_name(void);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_procedure_argument_list_error_if_any(Object,Object,Object);
extern Object get_rpc_priority_from_computation_context(void);
extern Object get_specific_method_for_arg_list_given_name(Object,Object,Object);
extern Object get_specific_methods_for_class_or_superior_class(Object,Object);
extern Object get_symbol_properties_function(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object give_warning_1(int,...);
extern Object gsi_interface_p_function(Object);
extern Object icp_connection_being_shutdown_qm(Object);
extern Object icp_connection_open_p(Object);
extern Object icp_cons_1(Object,Object);
extern Object icp_list_2(Object,Object);
extern Object icp_list_4(Object,Object,Object,Object);
extern Object icp_socket_description(Object);
extern Object icp_socket_of_interface_object(Object);
extern Object in_order_p(Object);
extern Object intern_gensym_string(int,...);
extern Object intern_text_string(int,...);
extern Object invalid_stack_value_or_object_for_return_to_remote_caller_qm(Object,Object,Object);
extern Object issue_tracing_and_breakpoint_exit_message(Object,Object);
extern Object item_references_enabled_p(Object);
extern Object item_remotely_callable_p(Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_empty_constant_queue(void);
extern Object make_error_text(Object,Object);
extern Object make_icp_socket(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_incoming_remote_procedure_call(Object,Object);
extern Object make_index_space_1(Object,Object);
extern Object make_outgoing_remote_procedure_identifier_from_declaration(Object);
extern Object make_outgoing_remote_procedure_identifier_with_info(Object,Object,Object,Object,Object,Object,Object);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object make_permanent_scheduled_remote_procedure_start_structure_internal(void);
extern Object make_permanent_system_rpc_instance_structure_internal(void);
extern Object make_remote_procedure_item_info(Object,Object,Object,Object,Object,Object);
extern Object make_remote_procedure_name_1(Object);
extern Object make_scheduled_remote_procedure_start_1(Object,Object,Object,Object);
extern Object make_system_rpc_1(Object,Object,Object);
extern Object make_system_rpc_instance_1(Object,Object,Object);
extern Object make_thread_array(Object);
extern Object make_vector_of_some_evaluation_values_for_remote_procedure(Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object non_resumable_icp_socket_p(Object);
extern Object note_change_to_block_1(Object,Object);
extern Object notify_user_1(Object);
extern Object outstanding_scheduled_remote_procedure_start_count(void);
extern Object outstanding_system_rpc_instance_count(void);
extern Object phrase_cons(Object,Object);
extern Object phrase_list_2(Object,Object);
extern Object phrase_list_3(Object,Object,Object);
extern Object phrase_list_4(Object,Object,Object,Object);
extern Object plausible_remote_method_call_p(Object,Object);
extern Object print_constant(int,...);
extern Object proc_cons_1(Object,Object);
extern Object propagate_error_to_code_body_invocation(Object,Object,Object,Object);
extern Object propagate_error_to_remote_caller_reclaim(Object,Object);
extern Object push_optimized_constant(Object);
extern Object put_box_translation_and_text_slot_value_for_remote_procedure_declaration(Object,Object,Object);
extern Object put_name_in_remote_system(Object,Object,Object);
extern Object raw_stack_error_named_error(Object,Object);
extern Object receive_remote_procedure_asynchronous_abort(Object,Object);
extern Object receive_remote_procedure_error(Object,Object,Object,Object,Object);
extern Object receive_remote_procedure_error_for_caller(Object,Object,Object,Object,Object);
extern Object receive_remote_procedure_values(Object,Object);
extern Object receive_remote_procedure_values_1(Object,Object,Object,Object,Object,Object);
extern Object receive_start_or_call_remote_procedure(Object,Object,Object,Object);
extern Object receive_start_or_call_remote_procedure_1(Object,Object,Object,Object);
extern Object reclaim_after_rpc_return_values(Object);
extern Object reclaim_constant_queue(Object);
extern Object reclaim_error_text(Object);
extern Object reclaim_error_text_but_not_string(Object);
extern Object reclaim_eval_cons_1(Object);
extern Object reclaim_eval_list_1(Object);
extern Object reclaim_evaluation_quantity(Object);
extern Object reclaim_evaluation_value(Object);
extern Object reclaim_frame_serial_number(Object);
extern Object reclaim_gensym_cons_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_icp_buffer_list(Object);
extern Object reclaim_icp_list_1(Object);
extern Object reclaim_icp_socket(Object);
extern Object reclaim_if_evaluation_value_1(Object);
extern Object reclaim_incoming_remote_procedure_call(Object);
extern Object reclaim_incoming_remote_procedure_identifier(Object);
extern Object reclaim_list_of_block_snapshots(Object);
extern Object reclaim_managed_number_or_value_function(Object);
extern Object reclaim_managed_simple_float_array_of_length_1(Object);
extern Object reclaim_managed_simple_vector(Object);
extern Object reclaim_outgoing_remote_procedure_call(Object);
extern Object reclaim_outgoing_remote_procedure_identifier_and_index(Object);
extern Object reclaim_proc_list_1(Object);
extern Object reclaim_receiving_resumable_object(Object);
extern Object reclaim_remote_procedure_name(Object);
extern Object reclaim_remote_procedure_name_structure_value(Object,Object);
extern Object reclaim_rpc_and_invocation_after_rpc_return_values(Object,Object);
extern Object reclaim_rpc_argument_list(Object,Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_scheduled_remote_procedure_start_1(Object);
extern Object reclaim_slot_value(Object);
extern Object reclaim_slot_value_cons_1(Object);
extern Object reclaim_system_rpc_instance_1(Object);
extern Object reclaim_temporary_constant_1(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_transformed_rpc_argument_list(Object,Object);
extern Object reclaim_unprocessed_rpc_argument_list(int,...);
extern Object reclaim_wide_string(Object);
extern Object record_block_for_tformat(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object reformat_remote_procedure_declaration_descriptions(void);
extern Object regenerate_optimized_constant(Object);
extern Object register_remote_procedure_call_for_start(Object,Object);
extern Object remote_procedure_arg_type_error_p(Object,Object);
extern Object remote_procedure_arg_type_error_p_1(Object,Object,Object);
extern Object remote_procedure_argument_description_function(Object);
extern Object remote_procedure_call_authorized_p(Object);
extern Object remote_procedure_call_being_aborted(Object,Object,Object);
extern Object remote_procedure_error(Object,Object,Object,Object);
extern Object remote_procedure_error_1(Object,Object,Object,Object,Object,Object);
extern Object remote_procedure_item_info_kind(Object);
extern Object remote_procedure_return_value_types_function(Object);
extern Object remote_procedure_returned_values_description_function(Object);
extern Object remote_return_exit_message(Object,Object);
extern Object remove_remote_procedure_calls_from_start_map(Object,Object,Object);
extern Object return_from_system_defined_rpc(Object,Object);
extern Object return_stack_values_to_remote_caller(Object,Object,Object,Object,Object);
extern Object scheduled_remote_procedure_start_structure_memory_usage(void);
extern Object send_icp_define_temporary_index_space(Object);
extern Object send_icp_release_temporary_index_space(void);
extern Object send_icp_resumable_rpc_error(Object,Object,Object,Object);
extern Object send_icp_resumable_rpc_error_to_caller(Object,Object,Object,Object,Object,Object);
extern Object send_icp_resumable_rpc_return_values(Object,Object);
extern Object send_icp_rpc_asynchronous_abort(Object);
extern Object send_icp_rpc_error(Object,Object,Object,Object);
extern Object send_icp_rpc_error_to_caller(Object,Object,Object,Object,Object,Object);
extern Object send_icp_rpc_return_values_deferring_objects(Object,Object,Object);
extern Object send_or_enqueue_icp_write_task(Object,Object,Object,Object,Object,Object);
extern Object send_rpc_return_values(Object,Object,Object,Object);
extern Object send_rpc_start(Object,Object,Object,Object,Object);
extern Object serve_item_p(Object);
extern Object set_evaluation_value_to_category_function(Object,Object);
extern Object set_property_value_function(Object,Object,Object);
extern Object set_remote_procedure_argument_description_function(Object,Object);
extern Object set_remote_procedure_returned_values_description_function(Object,Object);
extern Object set_slot_value_to_evaluation_value_function(Object,Object);
extern Object signal_code_body_invocation_error(int,...);
extern Object signal_error_to_rpc_caller_and_reclaim_identifier(Object);
extern Object simplify_associative_operation(Object);
extern Object slot_value_cons_1(Object,Object);
extern Object start_procedure_invocation_in_place(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object start_remote_procedure(Object,Object,Object,Object,Object,Object);
extern Object supply_a_or_an(Object);
extern Object symbol_name_text_string(Object);
extern Object system_rpc_error(Object,Object,Object);
extern Object system_rpc_instance_structure_memory_usage(void);
extern Object text_string_p(Object);
extern Object tformat(int,...);
extern Object tformat_stack_error_text_string(int,...);
extern Object tformat_text_string(int,...);
extern Object tprin(Object,Object);
extern Object transform_rpc_argument_or_result_list(int,...);
extern Object transform_system_rpc_arguments(Object,Object,Object,Object,Object);
extern Object transmit_completed_icp_message_group(void);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_general_string(Object);
extern Object type_error_in_setter(Object,Object,Object,Object,Object,Object,Object);
extern Object type_specification_type_p(Object,Object);
extern Object type_specification_type_p__with_explanation(Object,Object);
extern Object update_frame_status(Object,Object,Object);
extern Object update_object_pool_meters_list(Object);
extern Object validate_computation_instance_environment(Object,Object,Object);
extern Object var_count(Object);
extern Object var_rpc_info_from_index(Object,Object);
extern Object wake_up_code_body_invocation(Object);
extern Object write_evaluation_value(int,...);
extern Object write_major_trace_for_rpc_call_or_start(Object,Object);
extern Object write_major_trace_message_function(Object);
extern Object write_procedure_invocation_instance_from_slot(Object,Object);
extern Object write_remote_procedure_name_from_slot(Object,Object);
extern Object write_warning_message_header(Object);

#else

extern Object abort_incoming_rpc_call();
extern Object abort_outgoing_remote_procedure_call();
extern Object abort_procedure_invocation();
extern Object abort_rpc_call_and_reclaim_identifier();
extern Object activate_for_remote_procedure_declaration();
extern Object add_class_to_environment();
extern Object add_grammar_rules_function();
extern Object add_interface_to_alist();
extern Object all_elements_ok_for_parallel_rpc_start();
extern Object allocate_byte_vector_16();
extern Object allocate_evaluation_sequence();
extern Object allocate_evaluation_structure();
extern Object allocate_managed_simple_vector();
extern Object analyze_compiled_items_for_consistency();
extern Object assign_index_in_index_space();
extern Object break_out_of_debug_messages();
extern Object bytes_per_double_float_simple_array();
extern Object bytes_per_simple_vector();
extern Object call_remote_procedure();
extern Object call_remote_procedure_after_checks();
extern Object call_system_defined_rpc();
extern Object cancel_and_reclaim_scheduled_queue_element_1();
extern Object change_slot_value();
extern Object check_if_superior_classes_are_defined();
extern Object check_that_remote_procedure_can_be_started_or_called();
extern Object class_type_specification_p();
extern Object clear_optimized_constants();
extern Object collect_subclasses();
extern Object compile_remote_procedure_declaration_for_slot();
extern Object compile_remote_procedure_name_for_slot();
extern Object constant_queue_delete();
extern Object constant_queue_pop_left();
extern Object constant_queue_push_right();
extern Object convert_description_list_to_managed_array();
extern Object convert_remote_procedure_description_to_structure();
extern Object copy_for_phrase();
extern Object copy_for_slot_value();
extern Object copy_frame_serial_number();
extern Object copy_gensym_string_portion();
extern Object copy_icp_buffer_chain();
extern Object copy_list_using_eval_conses_1();
extern Object copy_list_using_phrase_conses();
extern Object copy_out_current_wide_string();
extern Object copy_partial_gensym_string();
extern Object copy_text_string();
extern Object copy_wide_string();
extern Object deactivate_for_remote_procedure_declaration();
extern Object deassign_index_in_index_space();
extern Object define_type_specification_explicit_complex_type();
extern Object delete_frame();
extern Object delete_proc_element_1();
extern Object deregister_remote_procedure_call_for_start();
extern Object direct_structure_method();
extern Object encode_remaining_into_remote_procedure_type();
extern Object encode_remaining_into_remote_procedure_type_1();
extern Object encode_remaining_into_remote_procedure_type_2();
extern Object end_icp_message_group();
extern Object enlarge_index_space();
extern Object error_text_p();
extern Object eval_cons_1();
extern Object evaluate_designation();
extern Object evaluate_procedure_or_method_designation();
extern Object evaluation_truth_value_is_true_p();
extern Object evaluation_value_type();
extern Object evaluation_value_value();
extern Object execute_fast_parallel_remote_procedure_start();
extern Object execute_parallel_remote_procedure_start();
extern Object execute_remote_procedure_start();
extern Object execute_scheduled_remote_procedure_start();
extern Object find_network_interface_for_icp_socket();
extern Object find_remote_procedure_call_for_code_body_invocation();
extern Object fix_remote_procedure_declaration_descriptions();
extern Object flush_icp_output_ports();
extern Object frame_serial_number_setf_helper_1();
extern Object framep_function();
extern Object future_task_schedule_2();
extern Object g2_api_test_1_system_rpc_internal();
extern Object g2_current_remote_interface_lisp_side();
extern Object g2_list_or_array_element_type_may_contain_item_p();
extern Object g2_list_structure_next();
extern Object g2_prefer_kb_procedures_to_system_defined();
extern Object g2_prefer_kb_procedures_to_system_defined_system_rpc_internal();
extern Object g2_reclaim_sending_resumable_object();
extern Object g2_to_g2_data_interface_p_function();
extern Object generate_float_vector();
extern Object generate_procedure_and_code_body_invocation_in_place();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object gensym_search_simple();
extern Object gensym_string_length();
extern Object gensym_symbol_name();
extern Object get_copy_of_rpd_spec();
extern Object get_icp_interface_for_remote_procedure_call();
extern Object get_instance_with_name_if_any();
extern Object get_item_from_local_handle();
extern Object get_local_host_name();
extern Object get_lookup_slot_value_given_default();
extern Object get_procedure_argument_list_error_if_any();
extern Object get_rpc_priority_from_computation_context();
extern Object get_specific_method_for_arg_list_given_name();
extern Object get_specific_methods_for_class_or_superior_class();
extern Object get_symbol_properties_function();
extern Object getfq_function_no_default();
extern Object give_warning_1();
extern Object gsi_interface_p_function();
extern Object icp_connection_being_shutdown_qm();
extern Object icp_connection_open_p();
extern Object icp_cons_1();
extern Object icp_list_2();
extern Object icp_list_4();
extern Object icp_socket_description();
extern Object icp_socket_of_interface_object();
extern Object in_order_p();
extern Object intern_gensym_string();
extern Object intern_text_string();
extern Object invalid_stack_value_or_object_for_return_to_remote_caller_qm();
extern Object issue_tracing_and_breakpoint_exit_message();
extern Object item_references_enabled_p();
extern Object item_remotely_callable_p();
extern Object load_and_initialize_type_description();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_empty_constant_queue();
extern Object make_error_text();
extern Object make_icp_socket();
extern Object make_incoming_remote_procedure_call();
extern Object make_index_space_1();
extern Object make_outgoing_remote_procedure_identifier_from_declaration();
extern Object make_outgoing_remote_procedure_identifier_with_info();
extern Object make_permanent_schedule_task_structure_internal();
extern Object make_permanent_scheduled_remote_procedure_start_structure_internal();
extern Object make_permanent_system_rpc_instance_structure_internal();
extern Object make_remote_procedure_item_info();
extern Object make_remote_procedure_name_1();
extern Object make_scheduled_remote_procedure_start_1();
extern Object make_system_rpc_1();
extern Object make_system_rpc_instance_1();
extern Object make_thread_array();
extern Object make_vector_of_some_evaluation_values_for_remote_procedure();
extern Object memq_function();
extern Object mutate_global_property();
extern Object non_resumable_icp_socket_p();
extern Object note_change_to_block_1();
extern Object notify_user_1();
extern Object outstanding_scheduled_remote_procedure_start_count();
extern Object outstanding_system_rpc_instance_count();
extern Object phrase_cons();
extern Object phrase_list_2();
extern Object phrase_list_3();
extern Object phrase_list_4();
extern Object plausible_remote_method_call_p();
extern Object print_constant();
extern Object proc_cons_1();
extern Object propagate_error_to_code_body_invocation();
extern Object propagate_error_to_remote_caller_reclaim();
extern Object push_optimized_constant();
extern Object put_box_translation_and_text_slot_value_for_remote_procedure_declaration();
extern Object put_name_in_remote_system();
extern Object raw_stack_error_named_error();
extern Object receive_remote_procedure_asynchronous_abort();
extern Object receive_remote_procedure_error();
extern Object receive_remote_procedure_error_for_caller();
extern Object receive_remote_procedure_values();
extern Object receive_remote_procedure_values_1();
extern Object receive_start_or_call_remote_procedure();
extern Object receive_start_or_call_remote_procedure_1();
extern Object reclaim_after_rpc_return_values();
extern Object reclaim_constant_queue();
extern Object reclaim_error_text();
extern Object reclaim_error_text_but_not_string();
extern Object reclaim_eval_cons_1();
extern Object reclaim_eval_list_1();
extern Object reclaim_evaluation_quantity();
extern Object reclaim_evaluation_value();
extern Object reclaim_frame_serial_number();
extern Object reclaim_gensym_cons_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_icp_buffer_list();
extern Object reclaim_icp_list_1();
extern Object reclaim_icp_socket();
extern Object reclaim_if_evaluation_value_1();
extern Object reclaim_incoming_remote_procedure_call();
extern Object reclaim_incoming_remote_procedure_identifier();
extern Object reclaim_list_of_block_snapshots();
extern Object reclaim_managed_number_or_value_function();
extern Object reclaim_managed_simple_float_array_of_length_1();
extern Object reclaim_managed_simple_vector();
extern Object reclaim_outgoing_remote_procedure_call();
extern Object reclaim_outgoing_remote_procedure_identifier_and_index();
extern Object reclaim_proc_list_1();
extern Object reclaim_receiving_resumable_object();
extern Object reclaim_remote_procedure_name();
extern Object reclaim_remote_procedure_name_structure_value();
extern Object reclaim_rpc_and_invocation_after_rpc_return_values();
extern Object reclaim_rpc_argument_list();
extern Object reclaim_schedule_task_args();
extern Object reclaim_scheduled_remote_procedure_start_1();
extern Object reclaim_slot_value();
extern Object reclaim_slot_value_cons_1();
extern Object reclaim_system_rpc_instance_1();
extern Object reclaim_temporary_constant_1();
extern Object reclaim_text_string();
extern Object reclaim_transformed_rpc_argument_list();
extern Object reclaim_unprocessed_rpc_argument_list();
extern Object reclaim_wide_string();
extern Object record_block_for_tformat();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object reformat_remote_procedure_declaration_descriptions();
extern Object regenerate_optimized_constant();
extern Object register_remote_procedure_call_for_start();
extern Object remote_procedure_arg_type_error_p();
extern Object remote_procedure_arg_type_error_p_1();
extern Object remote_procedure_argument_description_function();
extern Object remote_procedure_call_authorized_p();
extern Object remote_procedure_call_being_aborted();
extern Object remote_procedure_error();
extern Object remote_procedure_error_1();
extern Object remote_procedure_item_info_kind();
extern Object remote_procedure_return_value_types_function();
extern Object remote_procedure_returned_values_description_function();
extern Object remote_return_exit_message();
extern Object remove_remote_procedure_calls_from_start_map();
extern Object return_from_system_defined_rpc();
extern Object return_stack_values_to_remote_caller();
extern Object scheduled_remote_procedure_start_structure_memory_usage();
extern Object send_icp_define_temporary_index_space();
extern Object send_icp_release_temporary_index_space();
extern Object send_icp_resumable_rpc_error();
extern Object send_icp_resumable_rpc_error_to_caller();
extern Object send_icp_resumable_rpc_return_values();
extern Object send_icp_rpc_asynchronous_abort();
extern Object send_icp_rpc_error();
extern Object send_icp_rpc_error_to_caller();
extern Object send_icp_rpc_return_values_deferring_objects();
extern Object send_or_enqueue_icp_write_task();
extern Object send_rpc_return_values();
extern Object send_rpc_start();
extern Object serve_item_p();
extern Object set_evaluation_value_to_category_function();
extern Object set_property_value_function();
extern Object set_remote_procedure_argument_description_function();
extern Object set_remote_procedure_returned_values_description_function();
extern Object set_slot_value_to_evaluation_value_function();
extern Object signal_code_body_invocation_error();
extern Object signal_error_to_rpc_caller_and_reclaim_identifier();
extern Object simplify_associative_operation();
extern Object slot_value_cons_1();
extern Object start_procedure_invocation_in_place();
extern Object start_remote_procedure();
extern Object supply_a_or_an();
extern Object symbol_name_text_string();
extern Object system_rpc_error();
extern Object system_rpc_instance_structure_memory_usage();
extern Object text_string_p();
extern Object tformat();
extern Object tformat_stack_error_text_string();
extern Object tformat_text_string();
extern Object tprin();
extern Object transform_rpc_argument_or_result_list();
extern Object transform_system_rpc_arguments();
extern Object transmit_completed_icp_message_group();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_general_string();
extern Object type_error_in_setter();
extern Object type_specification_type_p();
extern Object type_specification_type_p__with_explanation();
extern Object update_frame_status();
extern Object update_object_pool_meters_list();
extern Object validate_computation_instance_environment();
extern Object var_count();
extern Object var_rpc_info_from_index();
extern Object wake_up_code_body_invocation();
extern Object write_evaluation_value();
extern Object write_major_trace_for_rpc_call_or_start();
extern Object write_major_trace_message_function();
extern Object write_procedure_invocation_instance_from_slot();
extern Object write_remote_procedure_name_from_slot();
extern Object write_warning_message_header();

#endif

/* variables/constants */
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
extern Object Available_icp_conses_tail_vector;
extern Object Available_icp_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);
extern Object Bad_phrase;
DECLARE_VARIABLE_WITH_SYMBOL(Breakpoint_level, Qbreakpoint_level);
DECLARE_VARIABLE_WITH_SYMBOL(Cached_top_of_stack, Qcached_top_of_stack);
extern Object Chain_of_available_schedule_tasks_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_scheduled_remote_procedure_starts, Qchain_of_available_scheduled_remote_procedure_starts);
extern Object Chain_of_available_scheduled_remote_procedure_starts_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_system_rpc_instances, Qchain_of_available_system_rpc_instances);
extern Object Chain_of_available_system_rpc_instances_vector;
extern Object Class_description_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Context_of_type_failure, Qcontext_of_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_flags, Qcurrent_computation_flags);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_frame, Qcurrent_computation_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_instance, Qcurrent_computation_instance);
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_serial_number, Qcurrent_frame_serial_number);
DECLARE_VARIABLE_WITH_SYMBOL(Current_g2_time, Qcurrent_g2_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_buffer, Qcurrent_icp_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_port, Qcurrent_icp_port);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_socket, Qcurrent_icp_socket);
DECLARE_VARIABLE_WITH_SYMBOL(Current_real_time, Qcurrent_real_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_schedule_task, Qcurrent_schedule_task);
DECLARE_VARIABLE_WITH_SYMBOL(Current_system_name, Qcurrent_system_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_system_rpc_icp_socket_qm, Qcurrent_system_rpc_icp_socket_qm);
extern Object Current_task_queue_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_write_icp_byte_position, Qcurrent_write_icp_byte_position);
DECLARE_VARIABLE_WITH_SYMBOL(Debugging_parameters, Qdebugging_parameters);
DECLARE_VARIABLE_WITH_SYMBOL(Debugging_reset, Qdebugging_reset);
DECLARE_VARIABLE_WITH_SYMBOL(Defer_notifications_qm, Qdefer_notifications_qm);
extern Object Deferred_task_queue_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Defined_evaluation_value_types, Qdefined_evaluation_value_types);
DECLARE_VARIABLE_WITH_SYMBOL(Disable_resumability, Qdisable_resumability);
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(G2_array_class_description, Qg2_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_list_class_description, Qg2_list_class_description);
#define Highest_system_priority FIX((SI_Long)0L)
DECLARE_VARIABLE_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm, Qicp_buffer_of_start_of_message_series_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_buffers_for_message_group, Qicp_buffers_for_message_group);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm, Qicp_byte_position_of_start_of_message_series_qm);
extern Object Icp_connection_closed;
extern Object Icp_connection_running;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_output_ports_to_flush, Qicp_output_ports_to_flush);
DECLARE_VARIABLE_WITH_SYMBOL(In_suspend_resume_p, Qin_suspend_resume_p);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Inference_engine_parameters, Qinference_engine_parameters);
DECLARE_VARIABLE_WITH_SYMBOL(Inhibit_corresponding_icp_object_making, Qinhibit_corresponding_icp_object_making);
DECLARE_VARIABLE_WITH_SYMBOL(Inside_breakpoint_p, Qinside_breakpoint_p);
extern Object Instances_specific_to_this_class_kbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Kb_flags, Qkb_flags);
DECLARE_VARIABLE_WITH_SYMBOL(Kb_flags_from_last_kb_read, Qkb_flags_from_last_kb_read);
DECLARE_VARIABLE_WITH_SYMBOL(Last_slot_checked_of_type_failure, Qlast_slot_checked_of_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(List_of_module_pre_conflict_resolution_post_loading_functions, Qlist_of_module_pre_conflict_resolution_post_loading_functions);
DECLARE_VARIABLE_WITH_SYMBOL(List_of_switched_and_module_post_loading_functions, Qlist_of_switched_and_module_post_loading_functions);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
DECLARE_VARIABLE_WITH_SYMBOL(Method_declaration_class_description, Qmethod_declaration_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(No_value, Qno_value);
DECLARE_VARIABLE_WITH_SYMBOL(Note_blocks_in_tformat, Qnote_blocks_in_tformat);
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_for_message_series, Qnumber_of_icp_bytes_for_message_series);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_in_message_group, Qnumber_of_icp_bytes_in_message_group);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer, Qnumber_of_icp_bytes_to_fill_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Prefer_kb_procedures_to_system_defined_p, Qprefer_kb_procedures_to_system_defined_p);
DECLARE_VARIABLE_WITH_SYMBOL(Priority_of_next_task, Qpriority_of_next_task);
DECLARE_VARIABLE_WITH_SYMBOL(Procedure_class_description, Qprocedure_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Profiling_enabled_qm, Qprofiling_enabled_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Reason_for_type_failure, Qreason_for_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Remote_procedure_declaration_class_description, Qremote_procedure_declaration_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Rpc_argument_list_error, Qrpc_argument_list_error);
DECLARE_VARIABLE_WITH_SYMBOL(Saved_breakpoint_level, Qsaved_breakpoint_level);
DECLARE_VARIABLE_WITH_SYMBOL(Saved_source_stepping_level, Qsaved_source_stepping_level);
DECLARE_VARIABLE_WITH_SYMBOL(Saved_tracing_level, Qsaved_tracing_level);
DECLARE_VARIABLE_WITH_SYMBOL(Saved_warning_level, Qsaved_warning_level);
DECLARE_VARIABLE_WITH_SYMBOL(Scheduled_remote_procedure_start_count, Qscheduled_remote_procedure_start_count);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Snapshots_of_related_blocks, Qsnapshots_of_related_blocks);
DECLARE_VARIABLE_WITH_SYMBOL(Source_stepping_level, Qsource_stepping_level);
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
DECLARE_VARIABLE_WITH_SYMBOL(Suppress_warning_message_header_qm, Qsuppress_warning_message_header_qm);
extern Object System_defined_rpc_prop;
DECLARE_VARIABLE_WITH_SYMBOL(System_defined_rpcs, Qsystem_defined_rpcs);
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
DECLARE_VARIABLE_WITH_SYMBOL(System_rpc_instance_count, Qsystem_rpc_instance_count);
extern Object The_type_description_of_scheduled_remote_procedure_start;
extern Object The_type_description_of_system_rpc_instance;
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Tracing_message_level, Qtracing_message_level);
DECLARE_VARIABLE_WITH_SYMBOL(Type_at_type_failure, Qtype_at_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Value_at_type_failure, Qvalue_at_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
DECLARE_VARIABLE_WITH_SYMBOL(Warning_message_level, Qwarning_message_level);
DECLARE_VARIABLE_WITH_SYMBOL(With_icp_buffer_coelescing_scope_qm, Qwith_icp_buffer_coelescing_scope_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Writing_icp_message_group, Qwriting_icp_message_group);
