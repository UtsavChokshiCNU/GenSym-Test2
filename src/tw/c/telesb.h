/* telesb.h -- Header File for telesb.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qerror;
extern Object Qinteger;

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

extern Object absorb_local_event_ab_side(Object);
extern Object absorb_local_event_ab_side_1(Object,Object,Object,Object,Object,Object);
extern Object accept_saved_user_settings_for_telewindows(Object,Object);
extern Object accept_telewindows_connection_license_info(Object,Object);
extern Object accept_telewindows_connection_license_level(Object,Object);
extern Object add_icp_message_handler(Object,Object);
extern Object assign_corresponding_icp_object_index(Object,Object,Object);
extern Object backtranslate_key_code(Object);
extern Object beep_at_user(void);
extern Object beep_in_window(Object);
extern Object beep_in_window_1(Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object c_native_clock_ticks_or_cache(Object,Object);
extern Object cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object check_shape_of_window_without_lookahead(Object,Object);
extern Object check_shape_of_window_without_lookahead_for_g2(Object,Object);
extern Object close_telewindows_connection(Object);
extern Object close_telewindows_connection_internal(Object);
extern Object copy_list_using_gensym_conses_1(Object);
extern Object copy_text_string(Object);
extern Object copy_text_string_to_cut_buffer(Object,Object);
extern Object disallow_new_icp_listener_connection(Object);
extern Object emit_icp_read_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_write_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object enable_or_disable_clipboard_polling_in_gensym_window(Object,Object);
extern Object end_icp_message_group(void);
extern Object enlarge_index_space(Object,Object);
extern Object enqueue_local_event(int,...);
extern Object enqueue_local_paste_availability_event(Object,Object,Object);
extern Object enqueue_local_paste_event(Object,Object,Object);
extern Object enqueue_window_paste_event(Object,Object,Object,Object,Object);
extern Object establish_new_object_index_for_workstation(int,...);
extern Object flush_and_shutdown_icp_socket(Object);
extern Object future_task_schedule_2(Object);
extern Object g2_global_paint_mode_p(void);
extern Object g2_handle_kill_remote_process_reply(Object,Object);
extern Object g2_handle_remote_process_exists_p_reply(Object,Object);
extern Object g2_handle_spawn_remote_process_reply(Object,Object);
extern Object generate_float_vector(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object gensym_list_4(Object,Object,Object,Object);
extern Object gensym_window_session_id(Object);
extern Object get_all_x11_events(Object);
extern Object get_event_queue_of_native_window(Object);
extern Object get_g2_window_given_icp_socket(Object);
extern Object get_gensym_window_for_g2_window(Object);
extern Object get_gensym_window_parameter(Object,Object);
extern Object get_icp_object_index_for_workstation(Object,Object);
extern Object get_last_local_mouse_motion_event(Object);
extern Object get_paste_event_queue_of_native_window(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object global_paint_mode_p(void);
extern Object handle_about_box_event(Object,Object);
extern Object handle_copy_text_string_to_cut_buffer(Object,Object);
extern Object handle_event_in_telewindows(Object,Object);
extern Object handle_event_in_telewindows_p(Object);
extern Object handle_icp_beep_in_window(void);
extern Object handle_icp_beep_in_window__body(Object);
extern Object handle_icp_copy_text_string_to_cut_buffer(void);
extern Object handle_icp_copy_text_string_to_cut_buffer__body(Object,Object);
extern Object handle_icp_define_telewindows_workstation(void);
extern Object handle_icp_define_telewindows_workstation__body(Object);
extern Object handle_icp_enable_or_disable_clipboard_polling(void);
extern Object handle_icp_enable_or_disable_clipboard_polling__body(Object,Object);
extern Object handle_icp_extended_telewindows_workstation_event(void);
extern Object handle_icp_extended_telewindows_workstation_event__body(Object,Object,Object,Object,Object,Object);
extern Object handle_icp_initialize_ntw_workstation(void);
extern Object handle_icp_initialize_ntw_workstation__body(Object,Object);
extern Object handle_icp_initialize_telewindows_workstation(void);
extern Object handle_icp_initialize_telewindows_workstation__body(Object,Object);
extern Object handle_icp_kill_remote_process(void);
extern Object handle_icp_kill_remote_process__body(Object,Object);
extern Object handle_icp_kill_remote_process_reply(void);
extern Object handle_icp_kill_remote_process_reply__body(Object,Object);
extern Object handle_icp_launch_peer_window(void);
extern Object handle_icp_launch_peer_window__body(Object,Object);
extern Object handle_icp_paste_from_telewindows_to_g2(void);
extern Object handle_icp_paste_from_telewindows_to_g2__body(Object,Object,Object);
extern Object handle_icp_remote_process_exists_p(void);
extern Object handle_icp_remote_process_exists_p__body(Object,Object);
extern Object handle_icp_remote_process_exists_p_reply(void);
extern Object handle_icp_remote_process_exists_p_reply__body(Object,Object);
extern Object handle_icp_request_paste_availability_status(void);
extern Object handle_icp_request_paste_availability_status__body(Object,Object);
extern Object handle_icp_request_paste_of_cut_buffer_text(void);
extern Object handle_icp_request_paste_of_cut_buffer_text__body(Object,Object);
extern Object handle_icp_request_to_close_telewindows_connection(void);
extern Object handle_icp_request_to_close_telewindows_connection__body(Object);
extern Object handle_icp_reroute_telewindow(void);
extern Object handle_icp_reroute_telewindow__body(Object,Object,Object,Object,Object);
extern Object handle_icp_save_user_settings_for_telewindows(void);
extern Object handle_icp_save_user_settings_for_telewindows__body(Object,Object);
extern Object handle_icp_set_background_color_value(void);
extern Object handle_icp_set_background_color_value__body(Object);
extern Object handle_icp_set_position_of_mouse(void);
extern Object handle_icp_set_position_of_mouse__body(Object,Object);
extern Object handle_icp_set_position_of_mouse_in_window(void);
extern Object handle_icp_set_position_of_mouse_in_window__body(Object,Object,Object);
extern Object handle_icp_set_scroll_info(void);
extern Object handle_icp_set_scroll_info__body(Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_set_telewindows_connection_license_info(void);
extern Object handle_icp_set_telewindows_connection_license_info__body(Object,Object);
extern Object handle_icp_set_transfer_mode(void);
extern Object handle_icp_set_transfer_mode__body(Object);
extern Object handle_icp_set_window_license_level(void);
extern Object handle_icp_set_window_license_level__body(Object,Object);
extern Object handle_icp_set_window_protocol_version(void);
extern Object handle_icp_set_window_protocol_version__body(Object,Object);
extern Object handle_icp_set_window_show_status(void);
extern Object handle_icp_set_window_show_status__body(Object,Object);
extern Object handle_icp_shift_position_of_mouse(void);
extern Object handle_icp_shift_position_of_mouse__body(Object,Object);
extern Object handle_icp_shift_position_of_mouse_in_window(void);
extern Object handle_icp_shift_position_of_mouse_in_window__body(Object,Object,Object);
extern Object handle_icp_show_window_with_geometry(void);
extern Object handle_icp_show_window_with_geometry__body(Object,Object,Object,Object,Object,Object);
extern Object handle_icp_spawn_remote_executable(void);
extern Object handle_icp_spawn_remote_executable__body(Object,Object);
extern Object handle_icp_spawn_remote_process(void);
extern Object handle_icp_spawn_remote_process__body(Object,Object);
extern Object handle_icp_spawn_remote_process_reply(void);
extern Object handle_icp_spawn_remote_process_reply__body(Object,Object);
extern Object handle_icp_start_mouse_tracking_in_window(void);
extern Object handle_icp_start_mouse_tracking_in_window__body(Object);
extern Object handle_icp_stop_mouse_tracking_in_window(void);
extern Object handle_icp_stop_mouse_tracking_in_window__body(Object);
extern Object handle_icp_telewindows_start_mouse_tracking(void);
extern Object handle_icp_telewindows_start_mouse_tracking__body(void);
extern Object handle_icp_telewindows_stop_mouse_tracking(void);
extern Object handle_icp_telewindows_stop_mouse_tracking__body(void);
extern Object handle_icp_telewindows_workstation_event(void);
extern Object handle_icp_telewindows_workstation_event__body(Object,Object,Object,Object,Object);
extern Object handle_icp_tw_command(void);
extern Object handle_icp_tw_command__body(Object,Object);
extern Object handle_icp_update_paste_availability_status(void);
extern Object handle_icp_update_paste_availability_status__body(Object,Object);
extern Object handle_paste_availability_event_in_g2(Object,Object,Object);
extern Object handle_paste_event(Object,Object);
extern Object handle_paste_event_in_g2(Object,Object,Object,Object);
extern Object handle_print_window_event(Object,Object);
extern Object handle_request_paste_availability_status(Object,Object);
extern Object handle_request_paste_of_cut_buffer_text(Object,Object);
extern Object handle_set_position_of_mouse_in_window(Object,Object,Object);
extern Object handle_shift_position_of_mouse_in_window(Object,Object,Object);
extern Object handle_start_mouse_tracking_in_window(Object);
extern Object handle_stop_mouse_tracking_in_window(Object);
extern Object handle_unclogged_connection_if_necessary(Object);
extern Object icp_connection_being_shutdown_qm(Object);
extern Object icp_connection_open_p(Object);
extern Object icp_error_internal(Object,Object,Object,Object,Object);
extern Object initialize_g2_process_telewindows_icp_socket(Object);
extern Object initialize_i_am_alive_info(Object,Object);
extern Object initialize_icp_object_type(Object,Object,Object,Object);
extern Object initialize_icp_object_type_compile(Object,Object,Object);
extern Object initialize_telewindows_process_telewindows_icp_socket(Object);
extern Object initialize_workstation(Object,Object,Object);
extern Object instantaneous_icp_reader_byte_count(void);
extern Object instantaneous_icp_writer_byte_count(void);
extern Object lay_out_window(Object);
extern Object local_clipboard_has_text_p(Object);
extern Object make_corresponding_icp_gensym_window(Object);
extern Object make_corresponding_icp_symbol(Object);
extern Object make_corresponding_icp_workstation(Object);
extern Object make_local_event_1(void);
extern Object make_new_value_for_star_if_appropriate(Object);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object make_workstation_1(Object);
extern Object memq_function(Object,Object);
extern Object mouse_motion_key_code(Object);
extern Object multiwindow_option_p(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object native_menu_bar_p(Object);
extern Object network_access_allowed_p(int,...);
extern Object nms_revert_to_unconnected_menu_bar(Object);
extern Object notify_user_at_console(int,...);
extern Object notify_user_at_console_and_on_logbook(int,...);
extern Object number_of_outstanding_message_groups(Object);
extern Object number_of_outstanding_output_icp_bytes(Object);
extern Object offer_g2_user_settings_back_to_telewindows(Object,Object);
extern Object old_style_mdi_frame_p(Object);
extern Object paste_for_telewindows(Object,Object,Object);
extern Object permit_connection_from_telewindows_p(Object);
extern Object poll_native_window_workstation(void);
extern Object poll_player(void);
extern Object poll_workstation(void);
extern Object post_telewindows_connection_clogged(Object,Object);
extern Object push_back_telewindows_mouse_motion_event(Object);
extern Object queue_empty_p(Object);
extern Object queue_insert(Object,Object);
extern Object queue_pop(Object);
extern Object queue_push(Object,Object);
extern Object read_clipboard(Object);
extern Object read_icp_boolean(void);
extern Object read_icp_corresponding_object_index(void);
extern Object read_icp_fixnum(void);
extern Object read_icp_integer(void);
extern Object read_icp_list(void);
extern Object read_icp_managed_double_float(void);
extern Object read_icp_text_string(void);
extern Object read_icp_unsigned_integer(void);
extern Object reason_to_reject_telewindows_connection(Object);
extern Object receive_initial_message(Object,Object);
extern Object receive_telewindows_workstation_event_for_g2(int,...);
extern Object reclaim_cached_structures_for_window(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_icon_rendering_and_remove_from_icon_description_if_g2(Object);
extern Object reclaim_icp_object_map(Object,Object,Object);
extern Object reclaim_icp_object_map_for_workstation(Object);
extern Object reclaim_icp_port_entry(Object,Object,Object,Object);
extern Object reclaim_icp_port_entry_for_workstation(Object,Object);
extern Object reclaim_local_event(Object);
extern Object reclaim_mouse_pointers_if_g2(Object);
extern Object reclaim_non_kb_workspaces_for_this_workstation_only_if_g2(Object);
extern Object reclaim_panes_in_window_if_g2(Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_telewindows_workstation_function(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_things_to_update_when_unclogged_qm(Object);
extern Object reclaim_workstation_context_stack_if_g2(Object);
extern Object reclaim_workstation_event_queue_if_g2(Object);
extern Object reclaim_workstation_tasks(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object refresh_window(Object);
extern Object register_icp_connection_loss_callback(Object,Object);
extern Object register_icp_write_callback(Object,Object);
extern Object reject_telewindows_connection(Object);
extern Object request_paste_availability_status(Object,Object);
extern Object request_paste_of_cut_buffer_text(Object,Object);
extern Object reroute_telewindow(Object,Object,Object,Object,Object);
extern Object reroute_telewindows_connection(Object,Object,Object,Object,Object);
extern Object resumable_icp_pop(void);
extern Object resumable_icp_pop_list_if_end_marker(void);
extern Object resumable_icp_push(Object);
extern Object send_icp_beep_in_window(Object);
extern Object send_icp_copy_text_string_to_cut_buffer(Object,Object);
extern Object send_icp_define_telewindows_workstation(Object);
extern Object send_icp_enable_or_disable_clipboard_polling(Object,Object);
extern Object send_icp_extended_telewindows_workstation_event(Object,Object,Object,Object,Object,Object);
extern Object send_icp_initialize_ntw_workstation(Object,Object);
extern Object send_icp_initialize_telewindows_workstation(Object,Object);
extern Object send_icp_kill_remote_process(Object,Object);
extern Object send_icp_kill_remote_process_reply(Object,Object);
extern Object send_icp_launch_peer_window(Object,Object);
extern Object send_icp_paste_from_telewindows_to_g2(Object,Object,Object);
extern Object send_icp_remote_process_exists_p(Object,Object);
extern Object send_icp_remote_process_exists_p_reply(Object,Object);
extern Object send_icp_request_paste_availability_status(Object,Object);
extern Object send_icp_request_paste_of_cut_buffer_text(Object,Object);
extern Object send_icp_request_to_close_telewindows_connection(Object);
extern Object send_icp_reroute_telewindow(Object,Object,Object,Object,Object);
extern Object send_icp_save_user_settings_for_telewindows(Object,Object);
extern Object send_icp_set_background_color_value(Object);
extern Object send_icp_set_position_of_mouse(Object,Object);
extern Object send_icp_set_position_of_mouse_in_window(Object,Object,Object);
extern Object send_icp_set_scroll_info(Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_set_telewindows_connection_license_info(Object,Object);
extern Object send_icp_set_transfer_mode(Object);
extern Object send_icp_set_window_license_level(Object,Object);
extern Object send_icp_set_window_protocol_version(Object,Object);
extern Object send_icp_set_window_show_status(Object,Object);
extern Object send_icp_shift_position_of_mouse(Object,Object);
extern Object send_icp_shift_position_of_mouse_in_window(Object,Object,Object);
extern Object send_icp_show_window_with_geometry(Object,Object,Object,Object,Object,Object);
extern Object send_icp_spawn_remote_executable(Object,Object);
extern Object send_icp_spawn_remote_process(Object,Object);
extern Object send_icp_spawn_remote_process_reply(Object,Object);
extern Object send_icp_start_mouse_tracking_in_window(Object);
extern Object send_icp_stop_mouse_tracking_in_window(Object);
extern Object send_icp_telewindows_start_mouse_tracking(void);
extern Object send_icp_telewindows_stop_mouse_tracking(void);
extern Object send_icp_telewindows_workstation_event(Object,Object,Object,Object,Object);
extern Object send_icp_tw_command(Object,Object);
extern Object send_icp_update_paste_availability_status(Object,Object);
extern Object send_telewindows_workstation_event(Object,Object);
extern Object set_access_form_for_workstation(Object,Object);
extern Object set_cursor_position(Object,Object);
extern Object set_icp_object_index_for_workstation(Object,Object,Object);
extern Object set_position_of_mouse(Object,Object);
extern Object set_position_of_mouse_in_window(Object,Object,Object);
extern Object set_up_workstation_on_ab_side(Object,Object,Object);
extern Object shift_cursor_position(Object,Object);
extern Object shift_position_of_mouse(Object,Object);
extern Object shift_position_of_mouse_in_window(Object,Object,Object);
extern Object shutdown_icp_socket_connection(int,...);
extern Object slave_gensym_window_qm(Object);
extern Object start_clipboard_polling(Object);
extern Object start_mouse_tracking(Object);
extern Object start_mouse_tracking_in_window(Object);
extern Object start_or_stop_clipboard_polling(Object,Object);
extern Object start_writing_icp_message(Object);
extern Object stop_clipboard_polling(Object);
extern Object stop_mouse_tracking(Object);
extern Object stop_mouse_tracking_in_local_window(Object);
extern Object stop_mouse_tracking_in_window(Object);
extern Object store_corresponding_icp_object(Object,Object);
extern Object talking_to_a_pre_version_4_g2_p(Object);
extern Object telewindows_check_version_of_remote_g2(Object);
extern Object telewindows_connection_clogged_for_g2_qm(Object,Object);
extern Object telewindows_write_state_change(Object,Object);
extern Object time_for_another_synthetic_motion_event_qm(void);
extern Object tw_handle_kill_remote_process(Object,Object);
extern Object tw_handle_remote_process_exists_p(Object,Object);
extern Object tw_handle_spawn_remote_command_line_process(Object,Object);
extern Object tw_handle_spawn_remote_executable_process(Object,Object);
extern Object twng_p(Object);
extern Object update_paste_availability_status(Object,Object,Object);
extern Object update_paste_availability_status_for_telewindows(Object,Object);
extern Object window_supports_mouse_hover_events_p(Object);
extern Object write_clipboard(Object,Object);
extern Object write_icp_boolean(Object);
extern Object write_icp_corresponding_object_index(Object);
extern Object write_icp_fixnum(Object);
extern Object write_icp_integer(Object);
extern Object write_icp_list(Object);
extern Object write_icp_managed_double_float(Object);
extern Object write_icp_maybe_suspend(void);
extern Object write_icp_text_string(Object);
extern Object write_icp_unsigned_integer(Object);

#else

extern Object absorb_local_event_ab_side();
extern Object absorb_local_event_ab_side_1();
extern Object accept_saved_user_settings_for_telewindows();
extern Object accept_telewindows_connection_license_info();
extern Object accept_telewindows_connection_license_level();
extern Object add_icp_message_handler();
extern Object assign_corresponding_icp_object_index();
extern Object backtranslate_key_code();
extern Object beep_at_user();
extern Object beep_in_window();
extern Object beep_in_window_1();
extern Object bytes_per_double_float_simple_array();
extern Object c_native_clock_ticks_or_cache();
extern Object cancel_and_reclaim_scheduled_queue_element_1();
extern Object check_shape_of_window_without_lookahead();
extern Object check_shape_of_window_without_lookahead_for_g2();
extern Object close_telewindows_connection();
extern Object close_telewindows_connection_internal();
extern Object copy_list_using_gensym_conses_1();
extern Object copy_text_string();
extern Object copy_text_string_to_cut_buffer();
extern Object disallow_new_icp_listener_connection();
extern Object emit_icp_read_trace();
extern Object emit_icp_write_trace();
extern Object enable_or_disable_clipboard_polling_in_gensym_window();
extern Object end_icp_message_group();
extern Object enlarge_index_space();
extern Object enqueue_local_event();
extern Object enqueue_local_paste_availability_event();
extern Object enqueue_local_paste_event();
extern Object enqueue_window_paste_event();
extern Object establish_new_object_index_for_workstation();
extern Object flush_and_shutdown_icp_socket();
extern Object future_task_schedule_2();
extern Object g2_global_paint_mode_p();
extern Object g2_handle_kill_remote_process_reply();
extern Object g2_handle_remote_process_exists_p_reply();
extern Object g2_handle_spawn_remote_process_reply();
extern Object generate_float_vector();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object gensym_list_4();
extern Object gensym_window_session_id();
extern Object get_all_x11_events();
extern Object get_event_queue_of_native_window();
extern Object get_g2_window_given_icp_socket();
extern Object get_gensym_window_for_g2_window();
extern Object get_gensym_window_parameter();
extern Object get_icp_object_index_for_workstation();
extern Object get_last_local_mouse_motion_event();
extern Object get_paste_event_queue_of_native_window();
extern Object getfq_function_no_default();
extern Object global_paint_mode_p();
extern Object handle_about_box_event();
extern Object handle_copy_text_string_to_cut_buffer();
extern Object handle_event_in_telewindows();
extern Object handle_event_in_telewindows_p();
extern Object handle_icp_beep_in_window();
extern Object handle_icp_beep_in_window__body();
extern Object handle_icp_copy_text_string_to_cut_buffer();
extern Object handle_icp_copy_text_string_to_cut_buffer__body();
extern Object handle_icp_define_telewindows_workstation();
extern Object handle_icp_define_telewindows_workstation__body();
extern Object handle_icp_enable_or_disable_clipboard_polling();
extern Object handle_icp_enable_or_disable_clipboard_polling__body();
extern Object handle_icp_extended_telewindows_workstation_event();
extern Object handle_icp_extended_telewindows_workstation_event__body();
extern Object handle_icp_initialize_ntw_workstation();
extern Object handle_icp_initialize_ntw_workstation__body();
extern Object handle_icp_initialize_telewindows_workstation();
extern Object handle_icp_initialize_telewindows_workstation__body();
extern Object handle_icp_kill_remote_process();
extern Object handle_icp_kill_remote_process__body();
extern Object handle_icp_kill_remote_process_reply();
extern Object handle_icp_kill_remote_process_reply__body();
extern Object handle_icp_launch_peer_window();
extern Object handle_icp_launch_peer_window__body();
extern Object handle_icp_paste_from_telewindows_to_g2();
extern Object handle_icp_paste_from_telewindows_to_g2__body();
extern Object handle_icp_remote_process_exists_p();
extern Object handle_icp_remote_process_exists_p__body();
extern Object handle_icp_remote_process_exists_p_reply();
extern Object handle_icp_remote_process_exists_p_reply__body();
extern Object handle_icp_request_paste_availability_status();
extern Object handle_icp_request_paste_availability_status__body();
extern Object handle_icp_request_paste_of_cut_buffer_text();
extern Object handle_icp_request_paste_of_cut_buffer_text__body();
extern Object handle_icp_request_to_close_telewindows_connection();
extern Object handle_icp_request_to_close_telewindows_connection__body();
extern Object handle_icp_reroute_telewindow();
extern Object handle_icp_reroute_telewindow__body();
extern Object handle_icp_save_user_settings_for_telewindows();
extern Object handle_icp_save_user_settings_for_telewindows__body();
extern Object handle_icp_set_background_color_value();
extern Object handle_icp_set_background_color_value__body();
extern Object handle_icp_set_position_of_mouse();
extern Object handle_icp_set_position_of_mouse__body();
extern Object handle_icp_set_position_of_mouse_in_window();
extern Object handle_icp_set_position_of_mouse_in_window__body();
extern Object handle_icp_set_scroll_info();
extern Object handle_icp_set_scroll_info__body();
extern Object handle_icp_set_telewindows_connection_license_info();
extern Object handle_icp_set_telewindows_connection_license_info__body();
extern Object handle_icp_set_transfer_mode();
extern Object handle_icp_set_transfer_mode__body();
extern Object handle_icp_set_window_license_level();
extern Object handle_icp_set_window_license_level__body();
extern Object handle_icp_set_window_protocol_version();
extern Object handle_icp_set_window_protocol_version__body();
extern Object handle_icp_set_window_show_status();
extern Object handle_icp_set_window_show_status__body();
extern Object handle_icp_shift_position_of_mouse();
extern Object handle_icp_shift_position_of_mouse__body();
extern Object handle_icp_shift_position_of_mouse_in_window();
extern Object handle_icp_shift_position_of_mouse_in_window__body();
extern Object handle_icp_show_window_with_geometry();
extern Object handle_icp_show_window_with_geometry__body();
extern Object handle_icp_spawn_remote_executable();
extern Object handle_icp_spawn_remote_executable__body();
extern Object handle_icp_spawn_remote_process();
extern Object handle_icp_spawn_remote_process__body();
extern Object handle_icp_spawn_remote_process_reply();
extern Object handle_icp_spawn_remote_process_reply__body();
extern Object handle_icp_start_mouse_tracking_in_window();
extern Object handle_icp_start_mouse_tracking_in_window__body();
extern Object handle_icp_stop_mouse_tracking_in_window();
extern Object handle_icp_stop_mouse_tracking_in_window__body();
extern Object handle_icp_telewindows_start_mouse_tracking();
extern Object handle_icp_telewindows_start_mouse_tracking__body();
extern Object handle_icp_telewindows_stop_mouse_tracking();
extern Object handle_icp_telewindows_stop_mouse_tracking__body();
extern Object handle_icp_telewindows_workstation_event();
extern Object handle_icp_telewindows_workstation_event__body();
extern Object handle_icp_tw_command();
extern Object handle_icp_tw_command__body();
extern Object handle_icp_update_paste_availability_status();
extern Object handle_icp_update_paste_availability_status__body();
extern Object handle_paste_availability_event_in_g2();
extern Object handle_paste_event();
extern Object handle_paste_event_in_g2();
extern Object handle_print_window_event();
extern Object handle_request_paste_availability_status();
extern Object handle_request_paste_of_cut_buffer_text();
extern Object handle_set_position_of_mouse_in_window();
extern Object handle_shift_position_of_mouse_in_window();
extern Object handle_start_mouse_tracking_in_window();
extern Object handle_stop_mouse_tracking_in_window();
extern Object handle_unclogged_connection_if_necessary();
extern Object icp_connection_being_shutdown_qm();
extern Object icp_connection_open_p();
extern Object icp_error_internal();
extern Object initialize_g2_process_telewindows_icp_socket();
extern Object initialize_i_am_alive_info();
extern Object initialize_icp_object_type();
extern Object initialize_icp_object_type_compile();
extern Object initialize_telewindows_process_telewindows_icp_socket();
extern Object initialize_workstation();
extern Object instantaneous_icp_reader_byte_count();
extern Object instantaneous_icp_writer_byte_count();
extern Object lay_out_window();
extern Object local_clipboard_has_text_p();
extern Object make_corresponding_icp_gensym_window();
extern Object make_corresponding_icp_symbol();
extern Object make_corresponding_icp_workstation();
extern Object make_local_event_1();
extern Object make_new_value_for_star_if_appropriate();
extern Object make_permanent_schedule_task_structure_internal();
extern Object make_workstation_1();
extern Object memq_function();
extern Object mouse_motion_key_code();
extern Object multiwindow_option_p();
extern Object mutate_global_property();
extern Object native_menu_bar_p();
extern Object network_access_allowed_p();
extern Object nms_revert_to_unconnected_menu_bar();
extern Object notify_user_at_console();
extern Object notify_user_at_console_and_on_logbook();
extern Object number_of_outstanding_message_groups();
extern Object number_of_outstanding_output_icp_bytes();
extern Object offer_g2_user_settings_back_to_telewindows();
extern Object old_style_mdi_frame_p();
extern Object paste_for_telewindows();
extern Object permit_connection_from_telewindows_p();
extern Object poll_native_window_workstation();
extern Object poll_player();
extern Object poll_workstation();
extern Object post_telewindows_connection_clogged();
extern Object push_back_telewindows_mouse_motion_event();
extern Object queue_empty_p();
extern Object queue_insert();
extern Object queue_pop();
extern Object queue_push();
extern Object read_clipboard();
extern Object read_icp_boolean();
extern Object read_icp_corresponding_object_index();
extern Object read_icp_fixnum();
extern Object read_icp_integer();
extern Object read_icp_list();
extern Object read_icp_managed_double_float();
extern Object read_icp_text_string();
extern Object read_icp_unsigned_integer();
extern Object reason_to_reject_telewindows_connection();
extern Object receive_initial_message();
extern Object receive_telewindows_workstation_event_for_g2();
extern Object reclaim_cached_structures_for_window();
extern Object reclaim_gensym_list_1();
extern Object reclaim_icon_rendering_and_remove_from_icon_description_if_g2();
extern Object reclaim_icp_object_map();
extern Object reclaim_icp_object_map_for_workstation();
extern Object reclaim_icp_port_entry();
extern Object reclaim_icp_port_entry_for_workstation();
extern Object reclaim_local_event();
extern Object reclaim_mouse_pointers_if_g2();
extern Object reclaim_non_kb_workspaces_for_this_workstation_only_if_g2();
extern Object reclaim_panes_in_window_if_g2();
extern Object reclaim_schedule_task_args();
extern Object reclaim_telewindows_workstation_function();
extern Object reclaim_text_string();
extern Object reclaim_things_to_update_when_unclogged_qm();
extern Object reclaim_workstation_context_stack_if_g2();
extern Object reclaim_workstation_event_queue_if_g2();
extern Object reclaim_workstation_tasks();
extern Object record_system_variable();
extern Object refresh_window();
extern Object register_icp_connection_loss_callback();
extern Object register_icp_write_callback();
extern Object reject_telewindows_connection();
extern Object request_paste_availability_status();
extern Object request_paste_of_cut_buffer_text();
extern Object reroute_telewindow();
extern Object reroute_telewindows_connection();
extern Object resumable_icp_pop();
extern Object resumable_icp_pop_list_if_end_marker();
extern Object resumable_icp_push();
extern Object send_icp_beep_in_window();
extern Object send_icp_copy_text_string_to_cut_buffer();
extern Object send_icp_define_telewindows_workstation();
extern Object send_icp_enable_or_disable_clipboard_polling();
extern Object send_icp_extended_telewindows_workstation_event();
extern Object send_icp_initialize_ntw_workstation();
extern Object send_icp_initialize_telewindows_workstation();
extern Object send_icp_kill_remote_process();
extern Object send_icp_kill_remote_process_reply();
extern Object send_icp_launch_peer_window();
extern Object send_icp_paste_from_telewindows_to_g2();
extern Object send_icp_remote_process_exists_p();
extern Object send_icp_remote_process_exists_p_reply();
extern Object send_icp_request_paste_availability_status();
extern Object send_icp_request_paste_of_cut_buffer_text();
extern Object send_icp_request_to_close_telewindows_connection();
extern Object send_icp_reroute_telewindow();
extern Object send_icp_save_user_settings_for_telewindows();
extern Object send_icp_set_background_color_value();
extern Object send_icp_set_position_of_mouse();
extern Object send_icp_set_position_of_mouse_in_window();
extern Object send_icp_set_scroll_info();
extern Object send_icp_set_telewindows_connection_license_info();
extern Object send_icp_set_transfer_mode();
extern Object send_icp_set_window_license_level();
extern Object send_icp_set_window_protocol_version();
extern Object send_icp_set_window_show_status();
extern Object send_icp_shift_position_of_mouse();
extern Object send_icp_shift_position_of_mouse_in_window();
extern Object send_icp_show_window_with_geometry();
extern Object send_icp_spawn_remote_executable();
extern Object send_icp_spawn_remote_process();
extern Object send_icp_spawn_remote_process_reply();
extern Object send_icp_start_mouse_tracking_in_window();
extern Object send_icp_stop_mouse_tracking_in_window();
extern Object send_icp_telewindows_start_mouse_tracking();
extern Object send_icp_telewindows_stop_mouse_tracking();
extern Object send_icp_telewindows_workstation_event();
extern Object send_icp_tw_command();
extern Object send_icp_update_paste_availability_status();
extern Object send_telewindows_workstation_event();
extern Object set_access_form_for_workstation();
extern Object set_cursor_position();
extern Object set_icp_object_index_for_workstation();
extern Object set_position_of_mouse();
extern Object set_position_of_mouse_in_window();
extern Object set_up_workstation_on_ab_side();
extern Object shift_cursor_position();
extern Object shift_position_of_mouse();
extern Object shift_position_of_mouse_in_window();
extern Object shutdown_icp_socket_connection();
extern Object slave_gensym_window_qm();
extern Object start_clipboard_polling();
extern Object start_mouse_tracking();
extern Object start_mouse_tracking_in_window();
extern Object start_or_stop_clipboard_polling();
extern Object start_writing_icp_message();
extern Object stop_clipboard_polling();
extern Object stop_mouse_tracking();
extern Object stop_mouse_tracking_in_local_window();
extern Object stop_mouse_tracking_in_window();
extern Object store_corresponding_icp_object();
extern Object talking_to_a_pre_version_4_g2_p();
extern Object telewindows_check_version_of_remote_g2();
extern Object telewindows_connection_clogged_for_g2_qm();
extern Object telewindows_write_state_change();
extern Object time_for_another_synthetic_motion_event_qm();
extern Object tw_handle_kill_remote_process();
extern Object tw_handle_remote_process_exists_p();
extern Object tw_handle_spawn_remote_command_line_process();
extern Object tw_handle_spawn_remote_executable_process();
extern Object twng_p();
extern Object update_paste_availability_status();
extern Object update_paste_availability_status_for_telewindows();
extern Object window_supports_mouse_hover_events_p();
extern Object write_clipboard();
extern Object write_icp_boolean();
extern Object write_icp_corresponding_object_index();
extern Object write_icp_fixnum();
extern Object write_icp_integer();
extern Object write_icp_list();
extern Object write_icp_managed_double_float();
extern Object write_icp_maybe_suspend();
extern Object write_icp_text_string();
extern Object write_icp_unsigned_integer();

#endif

/* variables/constants */
extern Object Abort_for_icp_catcher_qm;
#define Alternate_bit FIX((SI_Long)524288L)
extern Object Available_gensym_conses;
extern Object Backtrace_stack_for_internal_error;
extern Object Chain_of_available_schedule_tasks;
#define Control_bit FIX((SI_Long)8388608L)
extern Object Created_simple_float_array_pool_arrays;
extern Object Current_background_color_value;
extern Object Current_drawing_priority;
extern Object Current_drawing_transfer_mode;
extern Object Current_icp_buffer;
extern Object Current_icp_port;
extern Object Current_icp_read_trace_level;
extern Object Current_icp_socket;
extern Object Current_icp_write_trace_level;
extern Object Current_real_time;
extern Object Current_schedule_task;
extern Object Current_standard_icp_object_index_space;
extern Object Current_system_name;
extern Object Current_temporary_icp_object_index_space;
extern Object Current_workstation;
extern Object Current_workstation_native_window_qm;
extern Object Current_workstation_window;
extern Object Current_write_icp_byte_position;
extern Object Disable_resumability;
extern Object Fixnum_time_units_per_second;
extern Object Icp_buffer_of_start_of_message_series_qm;
extern Object Icp_buffers_for_message_group;
extern Object Icp_byte_position_of_start_of_message_series_qm;
extern Object Icp_read_trace_cutoff_level_qm;
extern Object Icp_suspend;
extern Object Icp_window_protocol_70_prerelease;
#define Icp_window_protocol_70r0 FIX((SI_Long)30L)
#define Icp_window_protocol_supports_chart_views_in_panes FIX((SI_Long)79L)
#define Icp_window_protocol_supports_native_cut_and_paste FIX((SI_Long)19L)
#define Icp_window_protocol_supports_saving_user_settings FIX((SI_Long)16L)
#define Icp_window_protocol_supports_scrolling FIX((SI_Long)4L)
#define Icp_window_protocol_supports_transparent_copy FIX((SI_Long)3L)
#define Icp_window_protocol_supports_views_in_listbars FIX((SI_Long)86L)
extern Object Icp_write_trace_cutoff_level_qm;
extern Object Illegal_key_index;
extern Object Index_of_top_of_backtrace_stack;
extern Object Inhibit_corresponding_icp_object_making;
extern Object Key_index_bits;
extern Object Key_modifier_bits;
extern Object Local_event_queue;
extern Object Local_paste_event_queue;
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
#define Meta_bit FIX((SI_Long)4194304L)
extern Object Number_of_icp_bytes_for_message_series;
extern Object Number_of_icp_bytes_in_message_group;
extern Object Number_of_icp_bytes_to_fill_buffer;
extern Object Player_state;
extern Object Recheck_if_clipboard_has_text_qm;
extern Object Resumable_icp_state;
extern Object Simple_float_array_pool_memory_usage;
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
extern Object Structure_being_reclaimed;
extern Object Telewindows_i_am_alive_send_interval;
extern Object Telewindows_max_number_of_icp_bytes_before_clogged;
extern Object Telewindows_max_number_of_message_groups_before_clogged;
extern Object Telewindows_min_number_of_icp_bytes_before_unclogged;
extern Object Telewindows_min_number_of_message_groups_before_unclogged;
extern Object Telewindows_seconds_to_wait_before_judging_clogged;
extern Object Time_of_last_synthetic_motion_event_qm;
extern Object Type_of_current_workstation_window;
#define Unicode_bit FIX((SI_Long)16777216L)
extern Object Unicode_character_bits;
extern Object Use_telewindows_clogging_mechanism_p;
extern Object Vector_of_simple_float_array_pools;
extern Object Workstations_in_service;
extern Object Writing_icp_message_group;
extern Object Writing_resumable_icp_messages_p;
