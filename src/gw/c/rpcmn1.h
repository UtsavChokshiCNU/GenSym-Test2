/* rpcmn1.h -- Header File for rpcmn1.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qerror;
extern Object Qfloat;
extern Object Qinteger;
extern Object Qnull;

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

extern Object g2int_abort_rpc_call_and_reclaim_identifier(Object);
extern Object g2int_add_icp_message_handler(Object,Object);
extern Object g2int_assign_corresponding_icp_object_index(Object,Object,Object);
extern Object g2int_assign_index_in_index_space(Object);
extern Object g2int_assoc_equal(Object,Object);
extern Object g2int_assq_function(Object,Object);
extern Object g2int_convert_gsi_value_to_value(Object);
extern Object g2int_convert_value_to_gsi_value(Object);
extern Object g2int_copy_tree_for_interned_list(Object);
extern Object g2int_deassign_index_in_index_space(Object,Object);
extern Object g2int_default_owner_for_gsi_objects(void);
extern Object g2int_direct_structure_method(Object,Object);
extern Object g2int_element_type_for_gsi_type(Object);
extern Object g2int_end_icp_message_group(void);
extern Object g2int_enlarge_index_space(Object,Object);
extern Object g2int_establish_new_object_index_for_remote_procedure_identifier(int,...);
extern Object g2int_establish_new_object_index_for_remote_procedure_name(int,...);
extern Object g2int_gensym_cons_1(Object,Object);
extern Object g2int_gensym_string_to_wide_string(Object);
extern Object g2int_get_gsi_instance_plist_value(Object,Object);
extern Object g2int_get_icp_object_index_for_remote_procedure_identifier(Object,Object);
extern Object g2int_get_icp_object_index_for_remote_procedure_name(Object,Object);
extern Object g2int_getfq_function_no_default(Object,Object);
extern Object g2int_gsi_define_new_remote_procedure(Object);
extern Object g2int_gsi_item_is_value_p(Object);
extern Object g2int_gsi_reclaim_managed_array(Object);
extern Object g2int_gsi_warning(int,...);
extern Object g2int_handle_icp_define_remote_procedure_identifier(void);
extern Object g2int_handle_icp_define_remote_procedure_identifier__body(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_handle_icp_define_remote_procedure_name(void);
extern Object g2int_handle_icp_define_remote_procedure_name__body(Object,Object);
extern Object g2int_handle_icp_define_temporary_index_space(void);
extern Object g2int_handle_icp_define_temporary_index_space__body(Object);
extern Object g2int_handle_icp_release_temporary_index_space(void);
extern Object g2int_handle_icp_release_temporary_index_space__body(void);
extern Object g2int_handle_icp_rpc_acknowledge_abort(void);
extern Object g2int_handle_icp_rpc_acknowledge_abort__body(Object);
extern Object g2int_handle_icp_rpc_asynchronous_abort(void);
extern Object g2int_handle_icp_rpc_asynchronous_abort__body(Object);
extern Object g2int_icp_connection_being_shutdownqm(Object);
extern Object g2int_icp_connection_open_p(Object);
extern Object g2int_icp_error_internal(Object,Object,Object,Object,Object);
extern Object g2int_icp_socket_description(Object);
extern Object g2int_initialize_icp_object_type(Object,Object,Object,Object);
extern Object g2int_initialize_icp_object_type_compile(Object,Object,Object);
extern Object g2int_intern_attributes_of_gsi_structure(Object);
extern Object g2int_intern_attributes_of_structure(Object);
extern Object g2int_intern_list(Object);
extern Object g2int_interned_list_cons(Object,Object);
extern Object g2int_load_and_initialize_type_description(Object,Object);
extern Object g2int_lookup_remote_procedure_identifier_from_index(Object);
extern Object g2int_make_corresponding_icp_remote_procedure_identifier(Object);
extern Object g2int_make_corresponding_icp_remote_procedure_name(Object);
extern Object g2int_make_corresponding_icp_symbol(Object);
extern Object g2int_make_gensym_list_1(Object);
extern Object g2int_make_gsi_instance(int,...);
extern Object g2int_make_gsi_local_function_1(void);
extern Object g2int_make_gsi_remote_procedure_1(void);
extern Object g2int_make_gsi_sequence(Object);
extern Object g2int_make_gsi_structure(Object);
extern Object g2int_make_incoming_remote_procedure_identifier(Object,Object);
extern Object g2int_make_index_space_1(Object,Object);
extern Object g2int_make_initial_remote_procedure_identifier_array(void);
extern Object g2int_make_interned_list_1(Object);
extern Object g2int_make_interned_remote_procedure_item_passing_info_1_1(Object);
extern Object g2int_make_outgoing_remote_procedure_identifier(Object,Object);
extern Object g2int_make_outgoing_remote_procedure_identifier_with_info(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_make_permanent_gsi_local_function_structure_internal(void);
extern Object g2int_make_permanent_gsi_remote_procedure_structure_internal(void);
extern Object g2int_make_permanent_interned_remote_procedure_item_passing_info_structure_internal(void);
extern Object g2int_make_permanent_remote_procedure_identifier_structure_internal(void);
extern Object g2int_make_permanent_remote_procedure_item_passing_info_structure_internal(void);
extern Object g2int_make_permanent_remote_procedure_name_structure_internal(void);
extern Object g2int_make_remote_procedure_identifier_1(Object,Object);
extern Object g2int_make_remote_procedure_item_info(Object,Object,Object,Object,Object,Object);
extern Object g2int_make_remote_procedure_item_info_old(Object,Object,Object,Object,Object);
extern Object g2int_make_remote_procedure_item_passing_info_1_1(Object);
extern Object g2int_make_remote_procedure_item_passing_info_from_specs(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_make_remote_procedure_item_passing_info_from_specs_1(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_make_remote_procedure_name_1(Object);
extern Object g2int_make_remote_procedure_name_function(Object);
extern Object g2int_mutate_global_property(Object,Object,Object);
extern Object g2int_notify_user_at_console(int,...);
extern Object g2int_peek_icp_byte(void);
extern Object g2int_read_evaluation_structure_from_list(Object,Object);
extern Object g2int_read_icp_byte(void);
extern Object g2int_read_icp_corresponding_object_index(void);
extern Object g2int_read_icp_evaluation_sequence(void);
extern Object g2int_read_icp_evaluation_structure(void);
extern Object g2int_read_icp_fixnum(void);
extern Object g2int_read_icp_float(void);
extern Object g2int_read_icp_gensym_string(void);
extern Object g2int_read_icp_gsi_permanent_remote_value(void);
extern Object g2int_read_icp_index_space(void);
extern Object g2int_read_icp_integer(void);
extern Object g2int_read_icp_interned_list_as_value_type(void);
extern Object g2int_read_icp_item(void);
extern Object g2int_read_icp_item_reference(void);
extern Object g2int_read_icp_list_of_excluded_return_attributes(void);
extern Object g2int_read_icp_list_of_include_all_return_system_attributes(void);
extern Object g2int_read_icp_list_of_include_all_return_system_attributes_except(void);
extern Object g2int_read_icp_list_of_included_return_attributes(void);
extern Object g2int_read_icp_list_of_included_return_system_attributes(void);
extern Object g2int_read_icp_list_of_return_kinds(void);
extern Object g2int_read_icp_managed_double_float(void);
extern Object g2int_read_icp_managed_long(void);
extern Object g2int_read_icp_remote_procedure_varargs_p(void);
extern Object g2int_read_icp_remote_value(void);
extern Object g2int_read_icp_remote_value_1(void);
extern Object g2int_read_icp_symbol_as_value_type(void);
extern Object g2int_read_icp_text_string(void);
extern Object g2int_read_icp_unsigned_integer(void);
extern Object g2int_read_icp_wide_string(void);
extern Object g2int_reclaim_gensym_list_1(Object);
extern Object g2int_reclaim_gensym_string(Object);
extern Object g2int_reclaim_gensym_tree_1(Object);
extern Object g2int_reclaim_gsi_instance(Object,Object);
extern Object g2int_reclaim_gsi_local_function_1(Object);
extern Object g2int_reclaim_gsi_remote_procedure(Object);
extern Object g2int_reclaim_gsi_remote_procedure_internal_1(Object);
extern Object g2int_reclaim_icp_object_map(Object,Object,Object);
extern Object g2int_reclaim_icp_object_map_for_remote_procedure_identifier(Object);
extern Object g2int_reclaim_icp_object_map_for_remote_procedure_name(Object);
extern Object g2int_reclaim_icp_port_entry(Object,Object,Object,Object);
extern Object g2int_reclaim_icp_port_entry_for_remote_procedure_identifier(Object,Object);
extern Object g2int_reclaim_icp_port_entry_for_remote_procedure_name(Object,Object);
extern Object g2int_reclaim_if_index_space(Object);
extern Object g2int_reclaim_incoming_remote_procedure_identifier(Object);
extern Object g2int_reclaim_index_space_1(Object);
extern Object g2int_reclaim_interned_remote_procedure_item_passing_info_1(Object);
extern Object g2int_reclaim_outgoing_remote_procedure_identifier(Object);
extern Object g2int_reclaim_outgoing_remote_procedure_identifier_and_index(Object);
extern Object g2int_reclaim_outgoing_remote_procedure_identifier_from_index(Object);
extern Object g2int_reclaim_remote_procedure_identifier_1(Object);
extern Object g2int_reclaim_remote_procedure_identifier_for_connection_loss(Object,Object);
extern Object g2int_reclaim_remote_procedure_item_passing_info(Object);
extern Object g2int_reclaim_remote_procedure_item_passing_info_1_1(Object);
extern Object g2int_reclaim_remote_procedure_name(Object);
extern Object g2int_reclaim_remote_procedure_name_for_connection_loss(Object,Object);
extern Object g2int_reclaim_remote_procedure_name_internal_1(Object);
extern Object g2int_reclaim_remote_procedure_name_structure(Object);
extern Object g2int_reclaim_remote_value(Object);
extern Object g2int_reclaim_rpc_argument_list(Object,Object);
extern Object g2int_reclaim_text_string(Object);
extern Object g2int_reclaim_transformed_rpc_argument_list(Object,Object);
extern Object g2int_reclaim_unprocessed_rpc_argument_list(int,...);
extern Object g2int_reclaim_wide_string(Object);
extern Object g2int_record_direct_structure_method(Object,Object,Object);
extern Object g2int_record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_regenerate_optimized_constant(Object);
extern Object g2int_remote_procedure_item_info_excluded_attributes(Object);
extern Object g2int_remote_procedure_item_info_include_all_system_attributes(Object);
extern Object g2int_remote_procedure_item_info_include_all_system_attributes_except(Object);
extern Object g2int_remote_procedure_item_info_included_attributes(Object);
extern Object g2int_remote_procedure_item_info_included_system_attributes(Object);
extern Object g2int_remote_procedure_item_info_kind(Object);
extern Object g2int_remote_procedure_item_info_kind_function(Object);
extern Object g2int_resumable_icp_pop(void);
extern Object g2int_resumable_icp_pop_list_if_end_marker(void);
extern Object g2int_resumable_icp_push(Object);
extern Object g2int_rpc_acknowledge_abort_error(Object);
extern Object g2int_send_icp_define_remote_procedure_identifier(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_send_icp_define_remote_procedure_name(Object,Object);
extern Object g2int_send_icp_define_temporary_index_space(Object);
extern Object g2int_send_icp_release_temporary_index_space(void);
extern Object g2int_send_icp_rpc_acknowledge_abort(Object);
extern Object g2int_send_icp_rpc_asynchronous_abort(Object);
extern Object g2int_set_access_form_for_remote_procedure_identifier(Object,Object);
extern Object g2int_set_access_form_for_remote_procedure_name(Object,Object);
extern Object g2int_set_icp_object_index_for_remote_procedure_identifier(Object,Object,Object);
extern Object g2int_set_icp_object_index_for_remote_procedure_name(Object,Object,Object);
extern Object g2int_signal_error_to_rpc_caller_and_reclaim_identifier(Object);
extern Object g2int_start_writing_icp_message(Object);
extern Object g2int_store_corresponding_icp_object(Object,Object);
extern Object g2int_text_string_p(Object);
extern Object g2int_write_icp_byte(Object);
extern Object g2int_write_icp_corresponding_object_index(Object);
extern Object g2int_write_icp_evaluation_sequence(Object);
extern Object g2int_write_icp_evaluation_structure(Object);
extern Object g2int_write_icp_fixnum(Object);
extern Object g2int_write_icp_float(Object);
extern Object g2int_write_icp_gsi_permanent_remote_value(Object);
extern Object g2int_write_icp_index_space(Object);
extern Object g2int_write_icp_integer(Object);
extern Object g2int_write_icp_interned_list_as_value_type(Object);
extern Object g2int_write_icp_item(Object);
extern Object g2int_write_icp_item_reference_1_function(Object);
extern Object g2int_write_icp_list_of_excluded_return_attributes(Object);
extern Object g2int_write_icp_list_of_include_all_return_system_attributes(Object);
extern Object g2int_write_icp_list_of_include_all_return_system_attributes_except(Object);
extern Object g2int_write_icp_list_of_included_return_attributes(Object);
extern Object g2int_write_icp_list_of_included_return_system_attributes(Object);
extern Object g2int_write_icp_list_of_return_kinds(Object);
extern Object g2int_write_icp_managed_double_float(Object);
extern Object g2int_write_icp_managed_long(Object);
extern Object g2int_write_icp_maybe_suspend(void);
extern Object g2int_write_icp_remote_procedure_varargs_p(Object);
extern Object g2int_write_icp_remote_value(Object);
extern Object g2int_write_icp_remote_value_1(Object);
extern Object g2int_write_icp_symbol_as_value_type(Object);
extern Object g2int_write_icp_text_string(Object);
extern Object g2int_write_icp_unsigned_integer(Object);
extern Object g2int_write_icp_wide_string(Object);

#else

extern Object g2int_abort_rpc_call_and_reclaim_identifier();
extern Object g2int_add_icp_message_handler();
extern Object g2int_assign_corresponding_icp_object_index();
extern Object g2int_assign_index_in_index_space();
extern Object g2int_assoc_equal();
extern Object g2int_assq_function();
extern Object g2int_convert_gsi_value_to_value();
extern Object g2int_convert_value_to_gsi_value();
extern Object g2int_copy_tree_for_interned_list();
extern Object g2int_deassign_index_in_index_space();
extern Object g2int_default_owner_for_gsi_objects();
extern Object g2int_direct_structure_method();
extern Object g2int_element_type_for_gsi_type();
extern Object g2int_end_icp_message_group();
extern Object g2int_enlarge_index_space();
extern Object g2int_establish_new_object_index_for_remote_procedure_identifier();
extern Object g2int_establish_new_object_index_for_remote_procedure_name();
extern Object g2int_gensym_cons_1();
extern Object g2int_gensym_string_to_wide_string();
extern Object g2int_get_gsi_instance_plist_value();
extern Object g2int_get_icp_object_index_for_remote_procedure_identifier();
extern Object g2int_get_icp_object_index_for_remote_procedure_name();
extern Object g2int_getfq_function_no_default();
extern Object g2int_gsi_define_new_remote_procedure();
extern Object g2int_gsi_item_is_value_p();
extern Object g2int_gsi_reclaim_managed_array();
extern Object g2int_gsi_warning();
extern Object g2int_handle_icp_define_remote_procedure_identifier();
extern Object g2int_handle_icp_define_remote_procedure_identifier__body();
extern Object g2int_handle_icp_define_remote_procedure_name();
extern Object g2int_handle_icp_define_remote_procedure_name__body();
extern Object g2int_handle_icp_define_temporary_index_space();
extern Object g2int_handle_icp_define_temporary_index_space__body();
extern Object g2int_handle_icp_release_temporary_index_space();
extern Object g2int_handle_icp_release_temporary_index_space__body();
extern Object g2int_handle_icp_rpc_acknowledge_abort();
extern Object g2int_handle_icp_rpc_acknowledge_abort__body();
extern Object g2int_handle_icp_rpc_asynchronous_abort();
extern Object g2int_handle_icp_rpc_asynchronous_abort__body();
extern Object g2int_icp_connection_being_shutdownqm();
extern Object g2int_icp_connection_open_p();
extern Object g2int_icp_error_internal();
extern Object g2int_icp_socket_description();
extern Object g2int_initialize_icp_object_type();
extern Object g2int_initialize_icp_object_type_compile();
extern Object g2int_intern_attributes_of_gsi_structure();
extern Object g2int_intern_attributes_of_structure();
extern Object g2int_intern_list();
extern Object g2int_interned_list_cons();
extern Object g2int_load_and_initialize_type_description();
extern Object g2int_lookup_remote_procedure_identifier_from_index();
extern Object g2int_make_corresponding_icp_remote_procedure_identifier();
extern Object g2int_make_corresponding_icp_remote_procedure_name();
extern Object g2int_make_corresponding_icp_symbol();
extern Object g2int_make_gensym_list_1();
extern Object g2int_make_gsi_instance();
extern Object g2int_make_gsi_local_function_1();
extern Object g2int_make_gsi_remote_procedure_1();
extern Object g2int_make_gsi_sequence();
extern Object g2int_make_gsi_structure();
extern Object g2int_make_incoming_remote_procedure_identifier();
extern Object g2int_make_index_space_1();
extern Object g2int_make_initial_remote_procedure_identifier_array();
extern Object g2int_make_interned_list_1();
extern Object g2int_make_interned_remote_procedure_item_passing_info_1_1();
extern Object g2int_make_outgoing_remote_procedure_identifier();
extern Object g2int_make_outgoing_remote_procedure_identifier_with_info();
extern Object g2int_make_permanent_gsi_local_function_structure_internal();
extern Object g2int_make_permanent_gsi_remote_procedure_structure_internal();
extern Object g2int_make_permanent_interned_remote_procedure_item_passing_info_structure_internal();
extern Object g2int_make_permanent_remote_procedure_identifier_structure_internal();
extern Object g2int_make_permanent_remote_procedure_item_passing_info_structure_internal();
extern Object g2int_make_permanent_remote_procedure_name_structure_internal();
extern Object g2int_make_remote_procedure_identifier_1();
extern Object g2int_make_remote_procedure_item_info();
extern Object g2int_make_remote_procedure_item_info_old();
extern Object g2int_make_remote_procedure_item_passing_info_1_1();
extern Object g2int_make_remote_procedure_item_passing_info_from_specs();
extern Object g2int_make_remote_procedure_item_passing_info_from_specs_1();
extern Object g2int_make_remote_procedure_name_1();
extern Object g2int_make_remote_procedure_name_function();
extern Object g2int_mutate_global_property();
extern Object g2int_notify_user_at_console();
extern Object g2int_peek_icp_byte();
extern Object g2int_read_evaluation_structure_from_list();
extern Object g2int_read_icp_byte();
extern Object g2int_read_icp_corresponding_object_index();
extern Object g2int_read_icp_evaluation_sequence();
extern Object g2int_read_icp_evaluation_structure();
extern Object g2int_read_icp_fixnum();
extern Object g2int_read_icp_float();
extern Object g2int_read_icp_gensym_string();
extern Object g2int_read_icp_gsi_permanent_remote_value();
extern Object g2int_read_icp_index_space();
extern Object g2int_read_icp_integer();
extern Object g2int_read_icp_interned_list_as_value_type();
extern Object g2int_read_icp_item();
extern Object g2int_read_icp_item_reference();
extern Object g2int_read_icp_list_of_excluded_return_attributes();
extern Object g2int_read_icp_list_of_include_all_return_system_attributes();
extern Object g2int_read_icp_list_of_include_all_return_system_attributes_except();
extern Object g2int_read_icp_list_of_included_return_attributes();
extern Object g2int_read_icp_list_of_included_return_system_attributes();
extern Object g2int_read_icp_list_of_return_kinds();
extern Object g2int_read_icp_managed_double_float();
extern Object g2int_read_icp_managed_long();
extern Object g2int_read_icp_remote_procedure_varargs_p();
extern Object g2int_read_icp_remote_value();
extern Object g2int_read_icp_remote_value_1();
extern Object g2int_read_icp_symbol_as_value_type();
extern Object g2int_read_icp_text_string();
extern Object g2int_read_icp_unsigned_integer();
extern Object g2int_read_icp_wide_string();
extern Object g2int_reclaim_gensym_list_1();
extern Object g2int_reclaim_gensym_string();
extern Object g2int_reclaim_gensym_tree_1();
extern Object g2int_reclaim_gsi_instance();
extern Object g2int_reclaim_gsi_local_function_1();
extern Object g2int_reclaim_gsi_remote_procedure();
extern Object g2int_reclaim_gsi_remote_procedure_internal_1();
extern Object g2int_reclaim_icp_object_map();
extern Object g2int_reclaim_icp_object_map_for_remote_procedure_identifier();
extern Object g2int_reclaim_icp_object_map_for_remote_procedure_name();
extern Object g2int_reclaim_icp_port_entry();
extern Object g2int_reclaim_icp_port_entry_for_remote_procedure_identifier();
extern Object g2int_reclaim_icp_port_entry_for_remote_procedure_name();
extern Object g2int_reclaim_if_index_space();
extern Object g2int_reclaim_incoming_remote_procedure_identifier();
extern Object g2int_reclaim_index_space_1();
extern Object g2int_reclaim_interned_remote_procedure_item_passing_info_1();
extern Object g2int_reclaim_outgoing_remote_procedure_identifier();
extern Object g2int_reclaim_outgoing_remote_procedure_identifier_and_index();
extern Object g2int_reclaim_outgoing_remote_procedure_identifier_from_index();
extern Object g2int_reclaim_remote_procedure_identifier_1();
extern Object g2int_reclaim_remote_procedure_identifier_for_connection_loss();
extern Object g2int_reclaim_remote_procedure_item_passing_info();
extern Object g2int_reclaim_remote_procedure_item_passing_info_1_1();
extern Object g2int_reclaim_remote_procedure_name();
extern Object g2int_reclaim_remote_procedure_name_for_connection_loss();
extern Object g2int_reclaim_remote_procedure_name_internal_1();
extern Object g2int_reclaim_remote_procedure_name_structure();
extern Object g2int_reclaim_remote_value();
extern Object g2int_reclaim_rpc_argument_list();
extern Object g2int_reclaim_text_string();
extern Object g2int_reclaim_transformed_rpc_argument_list();
extern Object g2int_reclaim_unprocessed_rpc_argument_list();
extern Object g2int_reclaim_wide_string();
extern Object g2int_record_direct_structure_method();
extern Object g2int_record_system_variable();
extern Object g2int_regenerate_optimized_constant();
extern Object g2int_remote_procedure_item_info_excluded_attributes();
extern Object g2int_remote_procedure_item_info_include_all_system_attributes();
extern Object g2int_remote_procedure_item_info_include_all_system_attributes_except();
extern Object g2int_remote_procedure_item_info_included_attributes();
extern Object g2int_remote_procedure_item_info_included_system_attributes();
extern Object g2int_remote_procedure_item_info_kind();
extern Object g2int_remote_procedure_item_info_kind_function();
extern Object g2int_resumable_icp_pop();
extern Object g2int_resumable_icp_pop_list_if_end_marker();
extern Object g2int_resumable_icp_push();
extern Object g2int_rpc_acknowledge_abort_error();
extern Object g2int_send_icp_define_remote_procedure_identifier();
extern Object g2int_send_icp_define_remote_procedure_name();
extern Object g2int_send_icp_define_temporary_index_space();
extern Object g2int_send_icp_release_temporary_index_space();
extern Object g2int_send_icp_rpc_acknowledge_abort();
extern Object g2int_send_icp_rpc_asynchronous_abort();
extern Object g2int_set_access_form_for_remote_procedure_identifier();
extern Object g2int_set_access_form_for_remote_procedure_name();
extern Object g2int_set_icp_object_index_for_remote_procedure_identifier();
extern Object g2int_set_icp_object_index_for_remote_procedure_name();
extern Object g2int_signal_error_to_rpc_caller_and_reclaim_identifier();
extern Object g2int_start_writing_icp_message();
extern Object g2int_store_corresponding_icp_object();
extern Object g2int_text_string_p();
extern Object g2int_write_icp_byte();
extern Object g2int_write_icp_corresponding_object_index();
extern Object g2int_write_icp_evaluation_sequence();
extern Object g2int_write_icp_evaluation_structure();
extern Object g2int_write_icp_fixnum();
extern Object g2int_write_icp_float();
extern Object g2int_write_icp_gsi_permanent_remote_value();
extern Object g2int_write_icp_index_space();
extern Object g2int_write_icp_integer();
extern Object g2int_write_icp_interned_list_as_value_type();
extern Object g2int_write_icp_item();
extern Object g2int_write_icp_item_reference_1_function();
extern Object g2int_write_icp_list_of_excluded_return_attributes();
extern Object g2int_write_icp_list_of_include_all_return_system_attributes();
extern Object g2int_write_icp_list_of_include_all_return_system_attributes_except();
extern Object g2int_write_icp_list_of_included_return_attributes();
extern Object g2int_write_icp_list_of_included_return_system_attributes();
extern Object g2int_write_icp_list_of_return_kinds();
extern Object g2int_write_icp_managed_double_float();
extern Object g2int_write_icp_managed_long();
extern Object g2int_write_icp_maybe_suspend();
extern Object g2int_write_icp_remote_procedure_varargs_p();
extern Object g2int_write_icp_remote_value();
extern Object g2int_write_icp_remote_value_1();
extern Object g2int_write_icp_symbol_as_value_type();
extern Object g2int_write_icp_text_string();
extern Object g2int_write_icp_unsigned_integer();
extern Object g2int_write_icp_wide_string();

#endif

/* variables/constants */
extern Object G2int_abort_for_icp_catcherqm;
extern Object G2int_backtrace_stack_for_internal_error;
extern Object G2int_chain_of_available_gsi_local_functions;
extern Object G2int_chain_of_available_gsi_remote_procedures;
extern Object G2int_chain_of_available_interned_remote_procedure_item_passing_infos;
extern Object G2int_chain_of_available_remote_procedure_identifiers;
extern Object G2int_chain_of_available_remote_procedure_item_passing_infos;
extern Object G2int_chain_of_available_remote_procedure_names;
extern Object G2int_current_computation_flags;
extern Object G2int_current_icp_buffer;
extern Object G2int_current_icp_port;
extern Object G2int_current_icp_socket;
extern Object G2int_current_invocation_remotely_started_p;
extern Object G2int_current_remote_procedure_identifier;
extern Object G2int_current_standard_icp_object_index_space;
extern Object G2int_current_temporary_icp_object_index_space;
extern Object G2int_current_write_icp_byte_position;
extern Object G2int_disable_resumability;
#define G2int_gsi_64bit_float_type_tag FIX((SI_Long)6L)
#define G2int_gsi_integer_type_tag FIX((SI_Long)1L)
#define G2int_gsi_item_handle_type_tag FIX((SI_Long)9L)
extern Object G2int_gsi_local_function_count;
#define G2int_gsi_logical_type_tag FIX((SI_Long)5L)
#define G2int_gsi_long_type_tag FIX((SI_Long)51L)
#define G2int_gsi_magic_offset FIX((SI_Long)1L)
extern Object G2int_gsi_reclaim_listqm;
extern Object G2int_gsi_remote_procedure_count;
extern Object G2int_gsi_remote_value_conses_logical_p;
extern Object G2int_gsi_remote_value_creates_instance_p;
#define G2int_gsi_rpc_async_abort FIX((SI_Long)258L)
#define G2int_gsi_string_type_tag FIX((SI_Long)4L)
#define G2int_gsi_symbol_type_tag FIX((SI_Long)3L)
#define G2int_gsi_unsigned_short_vector_type_tag FIX((SI_Long)11L)
extern Object G2int_icp_buffer_of_start_of_message_seriesqm;
extern Object G2int_icp_buffers_for_message_group;
extern Object G2int_icp_byte_position_of_start_of_message_seriesqm;
extern Object G2int_icp_suspend;
extern Object G2int_identifying_attribute_count_for_item_new_copy;
extern Object G2int_index_of_top_of_backtrace_stack;
extern Object G2int_inhibit_corresponding_icp_object_making;
extern Object G2int_interned_list_nil;
extern Object G2int_interned_list_non_symbol_root;
extern Object G2int_interned_list_symbols;
extern Object G2int_interned_remote_procedure_item_passing_info_count;
extern Object G2int_item_copy_index_space;
extern Object G2int_maximum_concurrent_remote_procedure_calls;
extern Object G2int_maximum_index_in_backtrace_stack_for_internal_error;
extern Object G2int_number_of_icp_bytes_for_message_series;
extern Object G2int_number_of_icp_bytes_in_message_group;
extern Object G2int_number_of_icp_bytes_to_fill_buffer;
extern Object G2int_remote_procedure_identifier_array;
extern Object G2int_remote_procedure_identifier_count;
extern Object G2int_remote_procedure_item_passing_info_count;
extern Object G2int_remote_procedure_name_count;
extern Object G2int_remote_value_is_binary_p;
extern Object G2int_remote_value_known_typetag;
extern Object G2int_rpc_argument_count_overrideqm;
#define G2int_size_of_basic_backtrace_information FIX((SI_Long)3L)
extern Object G2int_starresumable_icp_statestar;
extern Object G2int_structure_being_reclaimed;
extern Object G2int_the_type_description_of_gsi_local_function;
extern Object G2int_the_type_description_of_gsi_remote_procedure;
extern Object G2int_the_type_description_of_interned_remote_procedure_item_passing_info;
extern Object G2int_the_type_description_of_remote_procedure_identifier;
extern Object G2int_the_type_description_of_remote_procedure_item_passing_info;
extern Object G2int_the_type_description_of_remote_procedure_name;
extern Object G2int_write_remote_value_items_kind;
extern Object G2int_write_value_of_gsi_item_p;
extern Object G2int_writing_icp_message_group;
extern Object G2int_writing_resumable_icp_messages_p;
