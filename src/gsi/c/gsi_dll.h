#if defined(LINK_DYNAMICALLY_WITH_GSI)
#define gsi_convert_str_to_ustr (*gsi_convert_str_to_ustr_fn)
#define gsi_convert_ustr_to_str (*gsi_convert_ustr_to_str_fn)
#define gsi_convert_ustr_to_wstr (*gsi_convert_ustr_to_wstr_fn)
#define gsi_convert_wstr_to_ustr (*gsi_convert_wstr_to_ustr_fn)
#define gsi_attr_count_of (*gsi_attr_count_of_fn)
#define gsi_attr_is_transient (*gsi_attr_is_transient_fn)
#define gsi_attr_name_is_qualified (*gsi_attr_name_is_qualified_fn)
#define gsi_attr_name_of (*gsi_attr_name_of_fn)
#define gsi_attrs_of (*gsi_attrs_of_fn)
#define gsi_class_name_of (*gsi_class_name_of_fn)
#define gsi_class_qualifier_of (*gsi_class_qualifier_of_fn)
#define gsi_class_type_of (*gsi_class_type_of_fn)
#define gsi_clear_item (*gsi_clear_item_fn)
#define gsi_clear_last_error (*gsi_clear_last_error_fn)
#define gsi_close_listeners (*gsi_close_listeners_fn)
#define gsi_context_received_data (*gsi_context_received_data_fn)
#define gsi_context_socket (*gsi_context_socket_fn)
#define gsi_context_user_data (*gsi_context_user_data_fn)
#define gsi_current_context (*gsi_current_context_fn)
#define gsi_current_context_is_secure (*gsi_current_context_is_secure_fn)
#define gsi_context_is_secure (*gsi_context_is_secure_fn)
#define gsi_decode_timestamp (*gsi_decode_timestamp_fn)
#define gsi_element_count_of (*gsi_element_count_of_fn)
#define gsi_elements_of (*gsi_elements_of_fn)
#define gsi_encode_timestamp (*gsi_encode_timestamp_fn)
#define gsi_error_message (*gsi_error_message_fn)
#define gsi_establish_listener (*gsi_establish_listener_fn)
#define gsi_establish_secure_listener (*gsi_establish_secure_listener_fn)
#define gsi_extract_history (*gsi_extract_history_fn)
#define gsi_extract_history_spec (*gsi_extract_history_spec_fn)
#define gsi_flt_array_of (*gsi_flt_array_of_fn)
#define gsi_flt_list_of (*gsi_flt_list_of_fn)
#define gsi_flt_of (*gsi_flt_of_fn)
#define gsi_flush (*gsi_flush_fn)
#define gsi_handle_of (*gsi_handle_of_fn)
#define gsi_history_count_of (*gsi_history_count_of_fn)
#define gsi_initialize_callbacks (*gsi_initialize_callbacks_fn)
#define gsi_initialize_error_variable (*gsi_initialize_error_variable_fn)
#define gsi_initiate_connection (*gsi_initiate_connection_fn)
#define gsi_initiate_connection_w_u_d (*gsi_initiate_connection_w_u_d_fn)
#define gsi_initiate_secure_connection (*gsi_initiate_secure_connection_fn)
#define gsi_initiate_secure_conn_w_u_d (*gsi_initiate_secure_conn_w_u_d_fn)
#define gsi_int_array_of (*gsi_int_array_of_fn)
#define gsi_int_list_of (*gsi_int_list_of_fn)
#define gsi_int_of (*gsi_int_of_fn)
#define gsi_interval_of (*gsi_interval_of_fn)
#define gsi_is_item (*gsi_is_item_fn)
#define gsi_item_append_flag (*gsi_item_append_flag_fn)
#define gsi_item_of_attr (*gsi_item_of_attr_fn)
#define gsi_item_of_attr_by_name (*gsi_item_of_attr_by_name_fn)
#define gsi_item_of_identifying_attr_of (*gsi_item_of_identifying_attr_of_fn)
#define gsi_item_of_registered_item (*gsi_item_of_registered_item_fn)
#define gsi_item_reference_flag (*gsi_item_reference_flag_fn)
#define gsi_kill_context (*gsi_kill_context_fn)
#define gsi_last_error (*gsi_last_error_fn)
#define gsi_last_error_call_handle (*gsi_last_error_call_handle_fn)
#define gsi_last_error_message (*gsi_last_error_message_fn)
#define gsi_listener_socket (*gsi_listener_socket_fn)
#define gsi_log_array_of (*gsi_log_array_of_fn)
#define gsi_log_list_of (*gsi_log_list_of_fn)
#define gsi_log_of (*gsi_log_of_fn)
#define gsi_make_array (*gsi_make_array_fn)
#define gsi_make_attrs (*gsi_make_attrs_fn)
#define gsi_make_attrs_with_items (*gsi_make_attrs_with_items_fn)
#define gsi_make_item (*gsi_make_item_fn)
#define gsi_make_items (*gsi_make_items_fn)
#define gsi_make_registered_items (*gsi_make_registered_items_fn)
#define gsi_make_symbol (*gsi_make_symbol_fn)
#define gsi_name_of (*gsi_name_of_fn)
#define gsi_option_is_set (*gsi_option_is_set_fn)
#define gsi_owner_of (*gsi_owner_of_fn)
#define gsi_pause (*gsi_pause_fn)
#define gsi_reclaim_array (*gsi_reclaim_array_fn)
#define gsi_reclaim_attrs (*gsi_reclaim_attrs_fn)
#define gsi_reclaim_attrs_with_items (*gsi_reclaim_attrs_with_items_fn)
#define gsi_reclaim_item (*gsi_reclaim_item_fn)
#define gsi_reclaim_items (*gsi_reclaim_items_fn)
#define gsi_reclaim_registered_items (*gsi_reclaim_registered_items_fn)
#define gsi_registration_of_handle (*gsi_registration_of_handle_fn)
#define gsi_registration_of_item (*gsi_registration_of_item_fn)
#define gsi_reset_option (*gsi_reset_option_fn)
#define gsi_return_attrs (*gsi_return_attrs_fn)
#define gsi_return_message (*gsi_return_message_fn)
#define gsi_return_timed_attrs (*gsi_return_timed_attrs_fn)
#define gsi_return_timed_values (*gsi_return_timed_values_fn)
#define gsi_return_values (*gsi_return_values_fn)
#define gsi_rpc_call (*gsi_rpc_call_fn)
#define gsi_rpc_call_with_count (*gsi_rpc_call_with_count_fn)
#define gsi_rpc_declare_local_plain (*gsi_rpc_declare_local_plain_fn)
#define gsi_rpc_declare_remote_plain (*gsi_rpc_declare_remote_plain_fn)
#define gsi_rpc_return_error_values (*gsi_rpc_return_error_values_fn)
#define gsi_rpc_return_values (*gsi_rpc_return_values_fn)
#define gsi_rpc_start (*gsi_rpc_start_fn)
#define gsi_rpc_start_with_count (*gsi_rpc_start_with_count_fn)
#define gsi_run_loop (*gsi_run_loop_fn)
#define gsi_set_attr_count (*gsi_set_attr_count_fn)
#define gsi_set_attr_is_transient (*gsi_set_attr_is_transient_fn)
#define gsi_set_attr_name (*gsi_set_attr_name_fn)
#define gsi_set_attrs (*gsi_set_attrs_fn)
#define gsi_set_class_name (*gsi_set_class_name_fn)
#define gsi_set_class_qualifier (*gsi_set_class_qualifier_fn)
#define gsi_set_context_limit (*gsi_set_context_limit_fn)
#define gsi_set_context_user_data (*gsi_set_context_user_data_fn)
#define gsi_set_element_count (*gsi_set_element_count_fn)
#define gsi_set_elements (*gsi_set_elements_fn)
#define gsi_set_flt (*gsi_set_flt_fn)
#define gsi_set_flt_array (*gsi_set_flt_array_fn)
#define gsi_set_flt_list (*gsi_set_flt_list_fn)
#define gsi_set_handle (*gsi_set_handle_fn)
#define gsi_set_history (*gsi_set_history_fn)
#define gsi_set_include_file_version (*gsi_set_include_file_version_fn)
#define gsi_set_int (*gsi_set_int_fn)
#define gsi_set_int_array (*gsi_set_int_array_fn)
#define gsi_set_int_list (*gsi_set_int_list_fn)
#define gsi_set_interval (*gsi_set_interval_fn)
#define gsi_set_item_append_flag (*gsi_set_item_append_flag_fn)
#define gsi_set_item_of_attr (*gsi_set_item_of_attr_fn)
#define gsi_set_item_of_attr_by_name (*gsi_set_item_of_attr_by_name_fn)
#define gsi_set_item_reference_flag (*gsi_set_item_reference_flag_fn)
#define gsi_set_log (*gsi_set_log_fn)
#define gsi_set_log_array (*gsi_set_log_array_fn)
#define gsi_set_log_list (*gsi_set_log_list_fn)
#define gsi_set_name (*gsi_set_name_fn)
#define gsi_set_option (*gsi_set_option_fn)
#define gsi_set_pause_timeout (*gsi_set_pause_timeout_fn)
#define gsi_set_rpc_remote_return_v_k (*gsi_set_rpc_remote_return_v_k_fn)
#define gsi_set_run_loop_timeout (*gsi_set_run_loop_timeout_fn)
#define gsi_set_status (*gsi_set_status_fn)
#define gsi_set_str (*gsi_set_str_fn)
#define gsi_set_str_array (*gsi_set_str_array_fn)
#define gsi_set_str_list (*gsi_set_str_list_fn)
#define gsi_set_string_conversion_style (*gsi_set_string_conversion_style_fn)
#define gsi_set_sym (*gsi_set_sym_fn)
#define gsi_set_sym_array (*gsi_set_sym_array_fn)
#define gsi_set_sym_list (*gsi_set_sym_list_fn)
#define gsi_set_symbol_user_data (*gsi_set_symbol_user_data_fn)
#define gsi_set_timestamp (*gsi_set_timestamp_fn)
#define gsi_set_type (*gsi_set_type_fn)
#define gsi_set_unqualified_attr_name (*gsi_set_unqualified_attr_name_fn)
#define gsi_set_update_items_flag (*gsi_set_update_items_flag_fn)
#define gsi_set_user_data (*gsi_set_user_data_fn)
#define gsi_set_usv (*gsi_set_usv_fn)
#define gsi_signal_error (*gsi_signal_error_fn)
#define gsi_signal_handler (*gsi_signal_handler_fn)
#define gsi_simple_content_copy (*gsi_simple_content_copy_fn)
#define gsi_start (*gsi_start_fn)
#define gsi_status_of (*gsi_status_of_fn)
#define gsi_str_array_of (*gsi_str_array_of_fn)
#define gsi_str_list_of (*gsi_str_list_of_fn)
#define gsi_str_of (*gsi_str_of_fn)
#define gsi_string_conversion_style (*gsi_string_conversion_style_fn)
#define gsi_sym_array_of (*gsi_sym_array_of_fn)
#define gsi_sym_list_of (*gsi_sym_list_of_fn)
#define gsi_sym_of (*gsi_sym_of_fn)
#define gsi_symbol_name (*gsi_symbol_name_fn)
#define gsi_symbol_user_data (*gsi_symbol_user_data_fn)
#define gsi_timestamp_of (*gsi_timestamp_of_fn)
#define gsi_type_of (*gsi_type_of_fn)
#define gsi_unqualified_attr_name_of (*gsi_unqualified_attr_name_of_fn)
#define gsi_update_items_flag (*gsi_update_items_flag_fn)
#define gsi_user_data_of (*gsi_user_data_of_fn)
#define gsi_usv_of (*gsi_usv_of_fn)
#define gsi_wakeup (*gsi_wakeup_fn)
#define gsi_watchdog (*gsi_watchdog_fn)
#define gsi_watch_fd (*gsi_watch_fd_fn)
#define gsi_unwatch_fd (*gsi_unwatch_fd_fn)
#define gsi_watch_fd_for_writing (*gsi_watch_fd_for_writing_fn)
#define gsi_unwatch_fd_for_writing (*gsi_unwatch_fd_for_writing_fn)

#define GSI_API_FUNCTION_POINTER_LIST \
(void_fn_type **)&gsi_convert_str_to_ustr_fn,\
(void_fn_type **)&gsi_convert_ustr_to_str_fn,\
(void_fn_type **)&gsi_convert_ustr_to_wstr_fn,\
(void_fn_type **)&gsi_convert_wstr_to_ustr_fn,\
(void_fn_type **)&gsi_attr_count_of_fn,\
(void_fn_type **)&gsi_attr_is_transient_fn,\
(void_fn_type **)&gsi_attr_name_is_qualified_fn,\
(void_fn_type **)&gsi_attr_name_of_fn,\
(void_fn_type **)&gsi_attrs_of_fn,\
(void_fn_type **)&gsi_class_name_of_fn,\
(void_fn_type **)&gsi_class_qualifier_of_fn,\
(void_fn_type **)&gsi_class_type_of_fn,\
(void_fn_type **)&gsi_clear_item_fn,\
(void_fn_type **)&gsi_clear_last_error_fn,\
(void_fn_type **)&gsi_close_listeners_fn,\
(void_fn_type **)&gsi_context_received_data_fn,\
(void_fn_type **)&gsi_context_socket_fn,\
(void_fn_type **)&gsi_context_user_data_fn,\
(void_fn_type **)&gsi_current_context_fn,\
(void_fn_type **)&gsi_current_context_is_secure_fn,\
(void_fn_type **)&gsi_context_is_secure_fn,\
(void_fn_type **)&gsi_decode_timestamp_fn,\
(void_fn_type **)&gsi_element_count_of_fn,\
(void_fn_type **)&gsi_elements_of_fn,\
(void_fn_type **)&gsi_encode_timestamp_fn,\
(void_fn_type **)&gsi_error_message_fn,\
(void_fn_type **)&gsi_establish_listener_fn,\
(void_fn_type **)&gsi_establish_secure_listener_fn,\
(void_fn_type **)&gsi_extract_history_fn,\
(void_fn_type **)&gsi_extract_history_spec_fn,\
(void_fn_type **)&gsi_flt_array_of_fn,\
(void_fn_type **)&gsi_flt_list_of_fn,\
(void_fn_type **)&gsi_flt_of_fn,\
(void_fn_type **)&gsi_flush_fn,\
(void_fn_type **)&gsi_handle_of_fn,\
(void_fn_type **)&gsi_history_count_of_fn,\
(void_fn_type **)&gsi_initialize_callbacks_fn,\
(void_fn_type **)&gsi_initialize_error_variable_fn,\
(void_fn_type **)&gsi_initiate_connection_fn,\
(void_fn_type **)&gsi_initiate_connection_w_u_d_fn,\
(void_fn_type **)&gsi_initiate_secure_connection_fn,\
(void_fn_type **)&gsi_initiate_secure_conn_w_u_d_fn,\
(void_fn_type **)&gsi_int_array_of_fn,\
(void_fn_type **)&gsi_int_list_of_fn,\
(void_fn_type **)&gsi_int_of_fn,\
(void_fn_type **)&gsi_interval_of_fn,\
(void_fn_type **)&gsi_is_item_fn,\
(void_fn_type **)&gsi_item_append_flag_fn,\
(void_fn_type **)&gsi_item_of_attr_fn,\
(void_fn_type **)&gsi_item_of_attr_by_name_fn,\
(void_fn_type **)&gsi_item_of_identifying_attr_of_fn,\
(void_fn_type **)&gsi_item_of_registered_item_fn,\
(void_fn_type **)&gsi_item_reference_flag_fn,\
(void_fn_type **)&gsi_kill_context_fn,\
(void_fn_type **)&gsi_last_error_fn,\
(void_fn_type **)&gsi_last_error_call_handle_fn,\
(void_fn_type **)&gsi_last_error_message_fn,\
(void_fn_type **)&gsi_listener_socket_fn,\
(void_fn_type **)&gsi_log_array_of_fn,\
(void_fn_type **)&gsi_log_list_of_fn,\
(void_fn_type **)&gsi_log_of_fn,\
(void_fn_type **)&gsi_make_array_fn,\
(void_fn_type **)&gsi_make_attrs_fn,\
(void_fn_type **)&gsi_make_attrs_with_items_fn,\
(void_fn_type **)&gsi_make_item_fn,\
(void_fn_type **)&gsi_make_items_fn,\
(void_fn_type **)&gsi_make_registered_items_fn,\
(void_fn_type **)&gsi_make_symbol_fn,\
(void_fn_type **)&gsi_name_of_fn,\
(void_fn_type **)&gsi_option_is_set_fn,\
(void_fn_type **)&gsi_owner_of_fn,\
(void_fn_type **)&gsi_pause_fn,\
(void_fn_type **)&gsi_reclaim_array_fn,\
(void_fn_type **)&gsi_reclaim_attrs_fn,\
(void_fn_type **)&gsi_reclaim_attrs_with_items_fn,\
(void_fn_type **)&gsi_reclaim_item_fn,\
(void_fn_type **)&gsi_reclaim_items_fn,\
(void_fn_type **)&gsi_reclaim_registered_items_fn,\
(void_fn_type **)&gsi_registration_of_handle_fn,\
(void_fn_type **)&gsi_registration_of_item_fn,\
(void_fn_type **)&gsi_reset_option_fn,\
(void_fn_type **)&gsi_return_attrs_fn,\
(void_fn_type **)&gsi_return_message_fn,\
(void_fn_type **)&gsi_return_timed_attrs_fn,\
(void_fn_type **)&gsi_return_timed_values_fn,\
(void_fn_type **)&gsi_return_values_fn,\
(void_fn_type **)&gsi_rpc_call_fn,\
(void_fn_type **)&gsi_rpc_call_with_count_fn,\
(void_fn_type **)&gsi_rpc_declare_local_plain_fn,\
(void_fn_type **)&gsi_rpc_declare_remote_plain_fn,\
(void_fn_type **)&gsi_rpc_return_error_values_fn,\
(void_fn_type **)&gsi_rpc_return_values_fn,\
(void_fn_type **)&gsi_rpc_start_fn,\
(void_fn_type **)&gsi_rpc_start_with_count_fn,\
(void_fn_type **)&gsi_run_loop_fn,\
(void_fn_type **)&gsi_set_attr_count_fn,\
(void_fn_type **)&gsi_set_attr_is_transient_fn,\
(void_fn_type **)&gsi_set_attr_name_fn,\
(void_fn_type **)&gsi_set_attrs_fn,\
(void_fn_type **)&gsi_set_class_name_fn,\
(void_fn_type **)&gsi_set_class_qualifier_fn,\
(void_fn_type **)&gsi_set_context_limit_fn,\
(void_fn_type **)&gsi_set_context_user_data_fn,\
(void_fn_type **)&gsi_set_element_count_fn,\
(void_fn_type **)&gsi_set_elements_fn,\
(void_fn_type **)&gsi_set_flt_fn,\
(void_fn_type **)&gsi_set_flt_array_fn,\
(void_fn_type **)&gsi_set_flt_list_fn,\
(void_fn_type **)&gsi_set_handle_fn,\
(void_fn_type **)&gsi_set_history_fn,\
(void_fn_type **)&gsi_set_include_file_version_fn,\
(void_fn_type **)&gsi_set_int_fn,\
(void_fn_type **)&gsi_set_int_array_fn,\
(void_fn_type **)&gsi_set_int_list_fn,\
(void_fn_type **)&gsi_set_interval_fn,\
(void_fn_type **)&gsi_set_item_append_flag_fn,\
(void_fn_type **)&gsi_set_item_of_attr_fn,\
(void_fn_type **)&gsi_set_item_of_attr_by_name_fn,\
(void_fn_type **)&gsi_set_item_reference_flag_fn,\
(void_fn_type **)&gsi_set_log_fn,\
(void_fn_type **)&gsi_set_log_array_fn,\
(void_fn_type **)&gsi_set_log_list_fn,\
(void_fn_type **)&gsi_set_name_fn,\
(void_fn_type **)&gsi_set_option_fn,\
(void_fn_type **)&gsi_set_pause_timeout_fn,\
(void_fn_type **)&gsi_set_rpc_remote_return_v_k_fn,\
(void_fn_type **)&gsi_set_run_loop_timeout_fn,\
(void_fn_type **)&gsi_set_status_fn,\
(void_fn_type **)&gsi_set_str_fn,\
(void_fn_type **)&gsi_set_str_array_fn,\
(void_fn_type **)&gsi_set_str_list_fn,\
(void_fn_type **)&gsi_set_string_conversion_style_fn,\
(void_fn_type **)&gsi_set_sym_fn,\
(void_fn_type **)&gsi_set_sym_array_fn,\
(void_fn_type **)&gsi_set_sym_list_fn,\
(void_fn_type **)&gsi_set_symbol_user_data_fn,\
(void_fn_type **)&gsi_set_timestamp_fn,\
(void_fn_type **)&gsi_set_type_fn,\
(void_fn_type **)&gsi_set_unqualified_attr_name_fn,\
(void_fn_type **)&gsi_set_update_items_flag_fn,\
(void_fn_type **)&gsi_set_user_data_fn,\
(void_fn_type **)&gsi_set_usv_fn,\
(void_fn_type **)&gsi_signal_error_fn,\
(void_fn_type **)&gsi_signal_handler_fn,\
(void_fn_type **)&gsi_simple_content_copy_fn,\
(void_fn_type **)&gsi_start_fn,\
(void_fn_type **)&gsi_status_of_fn,\
(void_fn_type **)&gsi_str_array_of_fn,\
(void_fn_type **)&gsi_str_list_of_fn,\
(void_fn_type **)&gsi_str_of_fn,\
(void_fn_type **)&gsi_string_conversion_style_fn,\
(void_fn_type **)&gsi_sym_array_of_fn,\
(void_fn_type **)&gsi_sym_list_of_fn,\
(void_fn_type **)&gsi_sym_of_fn,\
(void_fn_type **)&gsi_symbol_name_fn,\
(void_fn_type **)&gsi_symbol_user_data_fn,\
(void_fn_type **)&gsi_timestamp_of_fn,\
(void_fn_type **)&gsi_type_of_fn,\
(void_fn_type **)&gsi_unqualified_attr_name_of_fn,\
(void_fn_type **)&gsi_update_items_flag_fn,\
(void_fn_type **)&gsi_user_data_of_fn,\
(void_fn_type **)&gsi_usv_of_fn,\
(void_fn_type **)&gsi_wakeup_fn,\
(void_fn_type **)&gsi_watchdog_fn,\
(void_fn_type **)&gsi_watch_fd_fn,\
(void_fn_type **)&gsi_unwatch_fd_fn,\
(void_fn_type **)&gsi_watch_fd_for_writing_fn,\
(void_fn_type **)&gsi_unwatch_fd_for_writing_fn,\
(void_fn_type **)0

#endif

