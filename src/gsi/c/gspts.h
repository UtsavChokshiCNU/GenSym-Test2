/* gspts.h -- Header File for gspts.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */

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
extern Object g2int_add_delta_time_to_variables_and_parameters(Object);
extern Object g2int_add_to_workspace(int,...);
extern Object g2int_block_p_function(Object);
extern Object g2int_bytes_allocated_for_image_tiles(void);
extern Object g2int_c_x11_close(Object);
extern Object g2int_c_x11_initialize(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_cache_deferred_rule_invocation_indices(void);
extern Object g2int_cache_main_thread_id(void);
extern Object g2int_close_log_file(void);
extern Object g2int_compute_newest_thrashing_ratio(Object,Object);
extern Object g2int_copy_evaluation_value_1(Object);
extern Object g2int_copy_list_using_streams_conses_function(Object);
extern Object g2int_define_or_configure_gsi_sensor(Object,Object,Object);
extern Object g2int_detail_pane(Object);
extern Object g2int_do_all_ole_cleanup(Object);
extern Object g2int_do_all_ole_initialization(Object);
extern Object g2int_encode_user_password_string_function(Object);
extern Object g2int_equal_rule_context(Object,Object);
extern Object g2int_exit_current_profiling_context(Object);
extern Object g2int_framep_function(Object);
extern Object g2int_g2_cancel_flush_of_partial_icp_buffer(void);
extern Object g2int_g2_priority_of_data_service_function(void);
extern Object g2int_g2_reclaim_sending_resumable_object(Object);
extern Object g2int_g2_stream_close(Object);
extern Object g2int_g2_stream_directory_p(Object);
extern Object g2int_g2_stream_p(Object);
extern Object g2int_g2_stream_write_char(Object,Object);
extern Object g2int_g2_stream_write_string(Object,Object);
extern Object g2int_gensym_probe_file(Object);
extern Object g2int_get_available_image_plane(Object,Object,Object);
extern Object g2int_get_default_x11_display(void);
extern Object g2int_get_frame_window_type(Object);
extern Object g2int_get_gensym_window_parameter(Object,Object);
extern Object g2int_get_gsi_interface_for_gsi_sensor_if_any(Object);
extern Object g2int_get_icon_name_from_command_line_if_any(void);
extern Object g2int_get_or_make_up_designation_for_block(Object);
extern Object g2int_get_values_from_x11_parse_geometry(Object);
extern Object g2int_get_window_name_from_command_line_if_any(void);
extern Object g2int_gsi_receive_value_for_gsi_sensor(Object,Object,Object,Object,Object);
extern Object g2int_gsi_receive_value_for_ping_request(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_handle_unclogged_connection_if_necessary(Object);
extern Object g2int_install_system_table(Object);
extern Object g2int_item_references_enabled_p(Object);
extern Object g2int_kill_foreign_image_unconditionally(Object);
extern Object g2int_kill_possibly_leftover_spawned_process(Object);
extern Object g2int_local_gensym_x11_display(void);
extern Object g2int_lookup_frame_description_reference_of_frame_style(Object,Object);
extern Object g2int_make_dialog_button(Object,Object,Object);
extern Object g2int_make_dialog_message(Object);
extern Object g2int_make_evaluation_truth_value_function(Object);
extern Object g2int_make_or_revise_window_per_native_window(Object,Object);
extern Object g2int_make_system_frame(Object);
extern Object g2int_make_workspace(int,...);
extern Object g2int_maximum_bytes_for_image_tiles(void);
extern Object g2int_minimum_scheduling_interval_function(Object);
extern Object g2int_name_and_class_for_computation_instance(Object);
extern Object g2int_network_access_allowed_p(int,...);
extern Object g2int_no_local_window_p(void);
extern Object g2int_notify_engineer(int,...);
extern Object g2int_notify_user(int,...);
extern Object g2int_pause_for_internal_error(Object);
extern Object g2int_posit_profiling_structure(Object);
extern Object g2int_post_on_message_board(int,...);
extern Object g2int_print_constant(int,...);
extern Object g2int_print_designation(Object);
extern Object g2int_print_display_error(void);
extern Object g2int_put_image_on_image_plane(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_reclaim_evaluation_value(Object);
extern Object g2int_reclaim_evaluation_value_if_any_function(Object);
extern Object g2int_reclaim_slot_value_tree_function(Object);
extern Object g2int_reclaim_streams_list_function(Object);
extern Object g2int_reclaim_sysproc_list_function(Object);
extern Object g2int_reclaim_text(Object);
extern Object g2int_replace_format_using_equivalent_font(Object);
extern Object g2int_report_simple_string_allocation(Object);
extern Object g2int_report_simple_string_reclamation(Object,Object);
extern Object g2int_rule_invocation_updates_needed_p(void);
extern Object g2int_run_al_for_recursive_descent(Object,Object);
extern Object g2int_run_chinese_for_recursive_descent(Object,Object);
extern Object g2int_run_embedded_option_for_recursive_descent(Object,Object);
extern Object g2int_run_ent_for_recursive_descent(Object,Object);
extern Object g2int_run_g1_for_recursive_descent(Object,Object);
extern Object g2int_run_gfi_for_recursive_descent(Object,Object);
extern Object g2int_run_gsi_for_recursive_descent(Object,Object);
extern Object g2int_run_icp_for_recursive_descent(Object,Object);
extern Object g2int_run_japanese_for_recursive_descent(Object,Object);
extern Object g2int_run_jl_for_recursive_descent(Object,Object);
extern Object g2int_run_jp_for_recursive_descent(Object,Object);
extern Object g2int_run_kfep_for_recursive_descent(Object,Object);
extern Object g2int_run_korean_for_recursive_descent(Object,Object);
extern Object g2int_run_nupec_for_recursive_descent(Object,Object);
extern Object g2int_run_restricted_use_option_for_recursive_descent(Object,Object);
extern Object g2int_run_runtime_option_for_recursive_descent(Object,Object);
extern Object g2int_schedule_g2_legacy_heartbeat_tasks_if_necessary(void);
extern Object g2int_scheduler_mode_function(Object);
extern Object g2int_shift_rule_ordering_heuristics(void);
extern Object g2int_signal_error_to_rpc_caller_and_reclaim_identifier(Object);
extern Object g2int_signal_floating_point_exception_stack_error(void);
extern Object g2int_system_pause(void);
extern Object g2int_take_actions_at_start_of_clock_tick(Object);
extern Object g2int_twrite_designation_for_item(Object);
extern Object g2int_update_trend_charts_for_clock_discontinuity(Object);
extern Object g2int_warn_of_big_bignum(Object);
extern Object g2int_wild_regular_expression_string_p(Object);
extern Object g2int_write_block_or_evaluation_value(Object);
extern Object g2int_write_error_text(Object);
extern Object g2int_write_evaluation_value(int,...);
extern Object g2int_write_expression(Object);
extern Object g2int_write_gensym_pathname(Object);
extern Object g2int_write_name_denotation(Object);
extern Object g2int_write_name_denotation_components(Object,Object);
extern Object g2int_write_name_denotation_for_slot(Object,Object);
extern Object g2int_write_type_specification(Object);
extern Object g2int_x11_display_specified_p(void);
extern Object g2int_x11_preinitialize_if_necessary(void);
extern Object g2int_x_events_pendingqm(void);

#else

extern Object g2int_abort_rpc_call_and_reclaim_identifier();
extern Object g2int_add_delta_time_to_variables_and_parameters();
extern Object g2int_add_to_workspace();
extern Object g2int_block_p_function();
extern Object g2int_bytes_allocated_for_image_tiles();
extern Object g2int_c_x11_close();
extern Object g2int_c_x11_initialize();
extern Object g2int_cache_deferred_rule_invocation_indices();
extern Object g2int_cache_main_thread_id();
extern Object g2int_close_log_file();
extern Object g2int_compute_newest_thrashing_ratio();
extern Object g2int_copy_evaluation_value_1();
extern Object g2int_copy_list_using_streams_conses_function();
extern Object g2int_define_or_configure_gsi_sensor();
extern Object g2int_detail_pane();
extern Object g2int_do_all_ole_cleanup();
extern Object g2int_do_all_ole_initialization();
extern Object g2int_encode_user_password_string_function();
extern Object g2int_equal_rule_context();
extern Object g2int_exit_current_profiling_context();
extern Object g2int_framep_function();
extern Object g2int_g2_cancel_flush_of_partial_icp_buffer();
extern Object g2int_g2_priority_of_data_service_function();
extern Object g2int_g2_reclaim_sending_resumable_object();
extern Object g2int_g2_stream_close();
extern Object g2int_g2_stream_directory_p();
extern Object g2int_g2_stream_p();
extern Object g2int_g2_stream_write_char();
extern Object g2int_g2_stream_write_string();
extern Object g2int_gensym_probe_file();
extern Object g2int_get_available_image_plane();
extern Object g2int_get_default_x11_display();
extern Object g2int_get_frame_window_type();
extern Object g2int_get_gensym_window_parameter();
extern Object g2int_get_gsi_interface_for_gsi_sensor_if_any();
extern Object g2int_get_icon_name_from_command_line_if_any();
extern Object g2int_get_or_make_up_designation_for_block();
extern Object g2int_get_values_from_x11_parse_geometry();
extern Object g2int_get_window_name_from_command_line_if_any();
extern Object g2int_gsi_receive_value_for_gsi_sensor();
extern Object g2int_gsi_receive_value_for_ping_request();
extern Object g2int_handle_unclogged_connection_if_necessary();
extern Object g2int_install_system_table();
extern Object g2int_item_references_enabled_p();
extern Object g2int_kill_foreign_image_unconditionally();
extern Object g2int_kill_possibly_leftover_spawned_process();
extern Object g2int_local_gensym_x11_display();
extern Object g2int_lookup_frame_description_reference_of_frame_style();
extern Object g2int_make_dialog_button();
extern Object g2int_make_dialog_message();
extern Object g2int_make_evaluation_truth_value_function();
extern Object g2int_make_or_revise_window_per_native_window();
extern Object g2int_make_system_frame();
extern Object g2int_make_workspace();
extern Object g2int_maximum_bytes_for_image_tiles();
extern Object g2int_minimum_scheduling_interval_function();
extern Object g2int_name_and_class_for_computation_instance();
extern Object g2int_network_access_allowed_p();
extern Object g2int_no_local_window_p();
extern Object g2int_notify_engineer();
extern Object g2int_notify_user();
extern Object g2int_pause_for_internal_error();
extern Object g2int_posit_profiling_structure();
extern Object g2int_post_on_message_board();
extern Object g2int_print_constant();
extern Object g2int_print_designation();
extern Object g2int_print_display_error();
extern Object g2int_put_image_on_image_plane();
extern Object g2int_reclaim_evaluation_value();
extern Object g2int_reclaim_evaluation_value_if_any_function();
extern Object g2int_reclaim_slot_value_tree_function();
extern Object g2int_reclaim_streams_list_function();
extern Object g2int_reclaim_sysproc_list_function();
extern Object g2int_reclaim_text();
extern Object g2int_replace_format_using_equivalent_font();
extern Object g2int_report_simple_string_allocation();
extern Object g2int_report_simple_string_reclamation();
extern Object g2int_rule_invocation_updates_needed_p();
extern Object g2int_run_al_for_recursive_descent();
extern Object g2int_run_chinese_for_recursive_descent();
extern Object g2int_run_embedded_option_for_recursive_descent();
extern Object g2int_run_ent_for_recursive_descent();
extern Object g2int_run_g1_for_recursive_descent();
extern Object g2int_run_gfi_for_recursive_descent();
extern Object g2int_run_gsi_for_recursive_descent();
extern Object g2int_run_icp_for_recursive_descent();
extern Object g2int_run_japanese_for_recursive_descent();
extern Object g2int_run_jl_for_recursive_descent();
extern Object g2int_run_jp_for_recursive_descent();
extern Object g2int_run_kfep_for_recursive_descent();
extern Object g2int_run_korean_for_recursive_descent();
extern Object g2int_run_nupec_for_recursive_descent();
extern Object g2int_run_restricted_use_option_for_recursive_descent();
extern Object g2int_run_runtime_option_for_recursive_descent();
extern Object g2int_schedule_g2_legacy_heartbeat_tasks_if_necessary();
extern Object g2int_scheduler_mode_function();
extern Object g2int_shift_rule_ordering_heuristics();
extern Object g2int_signal_error_to_rpc_caller_and_reclaim_identifier();
extern Object g2int_signal_floating_point_exception_stack_error();
extern Object g2int_system_pause();
extern Object g2int_take_actions_at_start_of_clock_tick();
extern Object g2int_twrite_designation_for_item();
extern Object g2int_update_trend_charts_for_clock_discontinuity();
extern Object g2int_warn_of_big_bignum();
extern Object g2int_wild_regular_expression_string_p();
extern Object g2int_write_block_or_evaluation_value();
extern Object g2int_write_error_text();
extern Object g2int_write_evaluation_value();
extern Object g2int_write_expression();
extern Object g2int_write_gensym_pathname();
extern Object g2int_write_name_denotation();
extern Object g2int_write_name_denotation_components();
extern Object g2int_write_name_denotation_for_slot();
extern Object g2int_write_type_specification();
extern Object g2int_x11_display_specified_p();
extern Object g2int_x11_preinitialize_if_necessary();
extern Object g2int_x_events_pendingqm();

#endif

/* variables/constants */
extern Object G2int_bytes_allocated_for_image_tiles;
extern Object G2int_do_not_initialize_g2_array_elements_p;
extern Object G2int_g2_stream_all_open_streams;
extern Object G2int_log_file_outputtingqm;
extern Object G2int_saved_initial_status;
extern Object G2int_system_window;
extern Object G2int_time_slice_expired_p;
extern Object G2int_timing_parameters;
extern Object G2int_warmboot_current_time;
extern Object G2int_warmboot_simulated_time;
extern Object G2int_warmbooting_with_catch_upqm;
extern Object G2int_warmbootingqm;
extern Object G2int_workstations_in_service;
extern Object G2int_x11_window;
