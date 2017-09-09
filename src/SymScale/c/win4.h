/* win4.h -- Header File for win4.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qerror;
extern Object Qnumber;
extern Object Qstring;
extern Object Qtype;
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

extern Object add_icp_message_handler(Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_native_window_handle(Object);
extern Object allocated_named_gensym_structure_p(Object);
extern Object bytes_per_simple_vector(Object);
extern Object c_manage_editor(Object,Object,Object,Object,Object);
extern Object c_x11_create_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_manage_window(Object,Object,Object,Object,Object,Object,Object);
extern Object classic_ui_p(Object);
extern Object clear_optimized_constants(void);
extern Object clear_window(int,...);
extern Object clear_window_1(Object,Object,Object,Object,Object);
extern Object compute_native_window_style(int,...);
extern Object compute_workspace_view_region(Object);
extern Object construct_local_event_plist(Object);
extern Object copy_32bit_integer(Object);
extern Object copy_gensym_window_attributes_into_g2_window(Object);
extern Object copy_text_string(Object);
extern Object create_native_window_1(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object default_native_window_style(Object);
extern Object delete_graphics_element_1(Object,Object);
extern Object direct_structure_method(Object,Object);
extern Object editor_show_completions_1(Object,Object);
extern Object embedded_window_p(Object);
extern Object emit_icp_read_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_write_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object encode_text_alignment(Object);
extern Object end_icp_message_group(void);
extern Object enlarge_index_space(Object,Object);
extern Object equalw(Object,Object);
extern Object find_native_window_by_handle(Object,Object);
extern Object find_native_window_by_index(Object,Object);
extern Object fixnum_list_to_word_vector(Object);
extern Object floating_pane_p(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_default_ui(void);
extern Object gensym_list_2(Object,Object);
extern Object gensym_window_ui(Object);
extern Object get_command_line_keyword_argument(int,...);
extern Object get_frame_window_type(Object);
extern Object get_gensym_window_parameter(Object,Object);
extern Object get_local_ui_toolkit_name(void);
extern Object get_remote_icp_version_info_value(Object,Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object graphics_cons_1(Object,Object);
extern Object guess_screen_depth(Object);
extern Object handle_icp_begin_window_update(void);
extern Object handle_icp_begin_window_update__body(Object,Object,Object,Object,Object);
extern Object handle_icp_create_window(void);
extern Object handle_icp_create_window__body(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_manage_editor(void);
extern Object handle_icp_manage_editor__body(Object,Object,Object,Object,Object,Object);
extern Object handle_icp_manage_scrollbars(void);
extern Object handle_icp_manage_scrollbars__body(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_manage_window(void);
extern Object handle_icp_manage_window__body(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_mega_refresh(void);
extern Object handle_icp_mega_refresh__body(Object);
extern Object handle_icp_messages(Object);
extern Object handle_icp_paint_icon_onto_graph_raster(void);
extern Object handle_icp_paint_marker_onto_graph_raster(void);
extern Object handle_icp_redirect_window(void);
extern Object handle_icp_redirect_window__body(Object,Object,Object,Object);
extern Object handle_icp_request_to_move_native_window(void);
extern Object handle_icp_request_to_move_native_window__body(Object,Object,Object);
extern Object handle_icp_request_to_move_window(void);
extern Object handle_icp_request_to_move_window__body(Object,Object,Object);
extern Object handle_icp_request_to_refresh_window(void);
extern Object handle_icp_request_to_refresh_window__body(Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_request_to_reshape_native_window(void);
extern Object handle_icp_request_to_reshape_native_window__body(Object,Object,Object,Object,Object);
extern Object handle_icp_request_to_reshape_window(void);
extern Object handle_icp_request_to_reshape_window__body(Object,Object,Object,Object,Object);
extern Object handle_icp_scroll_window(void);
extern Object handle_icp_scroll_window__body(Object,Object,Object,Object);
extern Object handle_icp_stack_windows(void);
extern Object handle_icp_stack_windows__body(Object,Object);
extern Object handle_reshape_event(Object,Object);
extern Object handler_body_for_begin_window_update(Object,Object,Object,Object,Object);
extern Object handler_body_for_request_to_move_window(Object,Object,Object);
extern Object handler_body_for_request_to_reshape_window(Object,Object,Object,Object,Object);
extern Object icp_connection_being_shutdown_qm(Object);
extern Object icp_connection_open_p(Object);
extern Object icp_error_internal(Object,Object,Object,Object,Object);
extern Object icp_message_functions_icp_prologue(Object);
extern Object inhibit_restore_detail_pane_p(Object);
extern Object initialize_native_window(Object,Object,Object,Object);
extern Object initialize_native_window_type(Object,Object);
extern Object install_tiling_pattern(Object);
extern Object instantaneous_icp_reader_byte_count(void);
extern Object instantaneous_icp_writer_byte_count(void);
extern Object lay_out_window(Object);
extern Object limit_native_window_size(Object,Object,Object,Object,Object);
extern Object limit_native_window_size_1(Object,Object,Object,Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_32bit_integer(Object,Object);
extern Object make_basic_native_window(Object,Object,Object,Object,Object);
extern Object make_color_map(Object,Object);
extern Object make_corresponding_icp_gensym_window(Object);
extern Object make_corresponding_icp_icon_rendering(Object);
extern Object make_gensym_list_1(Object);
extern Object make_gensym_window(Object);
extern Object make_monochrome_color_description_plist(Object,Object);
extern Object make_native_view_1(void);
extern Object make_native_window_1_1(void);
extern Object make_or_revise_window(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_permanent_native_view_structure_internal(void);
extern Object make_permanent_native_window_structure_internal(void);
extern Object make_permanent_workspace_view_structure_internal(void);
extern Object make_rendering_structure(Object,Object);
extern Object make_thread_array(Object);
extern Object make_tiling_pattern(Object,Object);
extern Object make_unbounded_region(void);
extern Object make_workspace_view_1_1(void);
extern Object make_workspace_view_structure(Object,Object);
extern Object manage_native_editor(int,...);
extern Object manage_native_window_1(Object,Object,Object,Object,Object,Object,Object);
extern Object manage_native_window_locally(Object,Object,Object);
extern Object manage_scrollbars_1(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object map_to_color_value(Object);
extern Object map_to_color_value_1(Object);
extern Object maximum_window_height(Object);
extern Object maximum_window_width(Object);
extern Object mdi_child_p(Object);
extern Object mdi_frame_p(Object);
extern Object mega_refresh_1(Object);
extern Object memq_function(Object,Object);
extern Object multiwindow_option_p(Object);
extern Object multiwindow_ui_p(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object n_32bit_integer_high_part(Object);
extern Object n_32bit_integer_low_part(Object);
extern Object n_32bit_integer_p(Object);
extern Object native_animation_control_p(Object);
extern Object native_basic_dialogs_p(Object);
extern Object native_custom_dialogs_p(Object);
extern Object native_debugger_dialog_p(Object);
extern Object native_file_dialog_p(Object);
extern Object native_file_dialog_without_custom_buttons_p(Object);
extern Object native_icons_p(Object);
extern Object native_menu_bar_p(Object);
extern Object native_pane_p(Object);
extern Object native_pop_up_menus_p(Object);
extern Object native_progress_bar_p(Object);
extern Object native_simple_dialogs_p(Object);
extern Object native_view_p(Object);
extern Object native_window_center(Object);
extern Object native_window_container_type(Object);
extern Object native_window_embedded_p(Object);
extern Object native_window_handle_for_last_event_qm(Object);
extern Object native_window_has_style(Object,Object);
extern Object native_window_p(Object);
extern Object native_window_structure_memory_usage(void);
extern Object native_window_type_for_type_code(Object);
extern Object native_window_workstation(Object);
extern Object native_windows_p(Object);
extern Object nms_controls_p(Object);
extern Object nms_toolbars_p(Object);
extern Object note_change_in_gensym_window(Object);
extern Object old_style_mdi_frame_p(Object);
extern Object outstanding_native_window_count(void);
extern Object outstanding_workspace_view_count(void);
extern Object paint_clipped_icon_onto_graph_raster(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object paint_clipped_marker_onto_graph_raster(Object,Object,Object,Object,Object,Object);
extern Object paint_icon_onto_graph_raster(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object paint_marker_onto_graph_raster(Object,Object,Object,Object);
extern Object paint_solid_rectangle_in_current_window(Object,Object,Object,Object,Object);
extern Object parse_ui_style(Object);
extern Object printing_window_p(Object);
extern Object process_window_style_options(Object,Object);
extern Object push_optimized_constant(Object);
extern Object queue_pop(Object);
extern Object read_icp_32bit_integer(void);
extern Object read_icp_boolean(void);
extern Object read_icp_corresponding_object_index(void);
extern Object read_icp_fixnum(void);
extern Object read_icp_icp_tree(void);
extern Object read_icp_integer(void);
extern Object read_icp_unsigned_integer(void);
extern Object read_icp_wide_string(void);
extern Object reclaim_32bit_integer(Object);
extern Object reclaim_byte_vector_16(Object);
extern Object reclaim_color_map_if_any(Object);
extern Object reclaim_default_pane_background_color_or_tiling_pattern(Object);
extern Object reclaim_gensym_cons_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_tree_with_text_strings(Object);
extern Object reclaim_icp_tree_with_text_strings(Object);
extern Object reclaim_if_evaluation_item_reference(Object);
extern Object reclaim_local_event(Object);
extern Object reclaim_native_window(Object);
extern Object reclaim_native_window_1_1(Object);
extern Object reclaim_native_window_by_handle(Object,Object);
extern Object reclaim_native_windows(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_wide_string(Object);
extern Object reclaim_workspace_view_1_1(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object redirect_window_1(Object,Object,Object,Object);
extern Object refresh_rectangle_of_window(Object,Object,Object,Object,Object);
extern Object refresh_telewindow(int,...);
extern Object refresh_window(Object);
extern Object regenerate_optimized_constant(Object);
extern Object request_to_refresh_window_1(Object,Object,Object,Object,Object,Object,Object);
extern Object reshape_native_g2_window(Object,Object);
extern Object reshape_telewindow(Object,Object);
extern Object resumable_icp_pop(void);
extern Object resumable_icp_pop_list_if_end_marker(void);
extern Object resumable_icp_push(Object);
extern Object save_native_window_geometry(Object);
extern Object scroll_native_window_1(Object,Object,Object,Object);
extern Object selection_ui_p(Object);
extern Object send_icp_begin_window_update(Object,Object,Object,Object,Object);
extern Object send_icp_create_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_manage_editor(Object,Object,Object,Object,Object,Object);
extern Object send_icp_manage_scrollbars(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_manage_window(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_mega_refresh(Object);
extern Object send_icp_redirect_window(Object,Object,Object,Object);
extern Object send_icp_request_to_move_native_window(Object,Object,Object);
extern Object send_icp_request_to_move_window(Object,Object,Object);
extern Object send_icp_request_to_refresh_window(Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_request_to_reshape_native_window(Object,Object,Object,Object,Object);
extern Object send_icp_request_to_reshape_window(Object,Object,Object,Object,Object);
extern Object send_icp_scroll_window(Object,Object,Object,Object);
extern Object send_icp_stack_windows(Object,Object);
extern Object server_and_client_are_same_host_p(Object);
extern Object server_and_client_share_file_system_p(Object);
extern Object set_native_window_x_scroll(Object,Object);
extern Object set_native_window_y_scroll(Object,Object);
extern Object stack_native_windows_1(Object,Object);
extern Object standard_ui_p(Object);
extern Object start_writing_icp_message(Object);
extern Object string_equalw(Object,Object);
extern Object structure_type_p(Object,Object);
extern Object symbol_from_key_code(Object);
extern Object sync_graphics_on_current_window(void);
extern Object synchronize_icp_on_window_with_drawing(Object,Object,Object,Object,Object);
extern Object telewindows_embedded_p(void);
extern Object telewindows_mdi_frame_p(void);
extern Object telewindows_multiwindow_ui_p(void);
extern Object telewindows_twaxl_mode_p(void);
extern Object telewindows_win32_window_p(void);
extern Object telewindows_window_p(Object);
extern Object text_string_p(Object);
extern Object this_is_twng_p(void);
extern Object top_level_window_p(Object);
extern Object trace_reshape_event(int,...);
extern Object twaxl_window_p(Object);
extern Object twng_p(Object);
extern Object twng_window_p(Object);
extern Object update_object_pool_meters_list(Object);
extern Object update_window(int,...);
extern Object win32_window_p(Object);
extern Object windows_platform_p(void);
extern Object word_vector_to_fixnum_list(Object);
extern Object workspace_view_structure_memory_usage(void);
extern Object write_icp_32bit_integer(Object);
extern Object write_icp_boolean(Object);
extern Object write_icp_corresponding_object_index(Object);
extern Object write_icp_fixnum(Object);
extern Object write_icp_icp_tree(Object);
extern Object write_icp_integer(Object);
extern Object write_icp_list_of_unsigned_integers(Object);
extern Object write_icp_unsigned_integer(Object);
extern Object write_icp_wide_string(Object);

#else

extern Object add_icp_message_handler();
extern Object allocate_byte_vector_16();
extern Object allocate_native_window_handle();
extern Object allocated_named_gensym_structure_p();
extern Object bytes_per_simple_vector();
extern Object c_manage_editor();
extern Object c_x11_create_window();
extern Object c_x11_manage_window();
extern Object classic_ui_p();
extern Object clear_optimized_constants();
extern Object clear_window();
extern Object clear_window_1();
extern Object compute_native_window_style();
extern Object compute_workspace_view_region();
extern Object construct_local_event_plist();
extern Object copy_32bit_integer();
extern Object copy_gensym_window_attributes_into_g2_window();
extern Object copy_text_string();
extern Object create_native_window_1();
extern Object default_native_window_style();
extern Object delete_graphics_element_1();
extern Object direct_structure_method();
extern Object editor_show_completions_1();
extern Object embedded_window_p();
extern Object emit_icp_read_trace();
extern Object emit_icp_write_trace();
extern Object encode_text_alignment();
extern Object end_icp_message_group();
extern Object enlarge_index_space();
extern Object equalw();
extern Object find_native_window_by_handle();
extern Object find_native_window_by_index();
extern Object fixnum_list_to_word_vector();
extern Object floating_pane_p();
extern Object gensym_cons_1();
extern Object gensym_default_ui();
extern Object gensym_list_2();
extern Object gensym_window_ui();
extern Object get_command_line_keyword_argument();
extern Object get_frame_window_type();
extern Object get_gensym_window_parameter();
extern Object get_local_ui_toolkit_name();
extern Object get_remote_icp_version_info_value();
extern Object getfq_function_no_default();
extern Object graphics_cons_1();
extern Object guess_screen_depth();
extern Object handle_icp_begin_window_update();
extern Object handle_icp_begin_window_update__body();
extern Object handle_icp_create_window();
extern Object handle_icp_create_window__body();
extern Object handle_icp_manage_editor();
extern Object handle_icp_manage_editor__body();
extern Object handle_icp_manage_scrollbars();
extern Object handle_icp_manage_scrollbars__body();
extern Object handle_icp_manage_window();
extern Object handle_icp_manage_window__body();
extern Object handle_icp_mega_refresh();
extern Object handle_icp_mega_refresh__body();
extern Object handle_icp_messages();
extern Object handle_icp_paint_icon_onto_graph_raster();
extern Object handle_icp_paint_marker_onto_graph_raster();
extern Object handle_icp_redirect_window();
extern Object handle_icp_redirect_window__body();
extern Object handle_icp_request_to_move_native_window();
extern Object handle_icp_request_to_move_native_window__body();
extern Object handle_icp_request_to_move_window();
extern Object handle_icp_request_to_move_window__body();
extern Object handle_icp_request_to_refresh_window();
extern Object handle_icp_request_to_refresh_window__body();
extern Object handle_icp_request_to_reshape_native_window();
extern Object handle_icp_request_to_reshape_native_window__body();
extern Object handle_icp_request_to_reshape_window();
extern Object handle_icp_request_to_reshape_window__body();
extern Object handle_icp_scroll_window();
extern Object handle_icp_scroll_window__body();
extern Object handle_icp_stack_windows();
extern Object handle_icp_stack_windows__body();
extern Object handle_reshape_event();
extern Object handler_body_for_begin_window_update();
extern Object handler_body_for_request_to_move_window();
extern Object handler_body_for_request_to_reshape_window();
extern Object icp_connection_being_shutdown_qm();
extern Object icp_connection_open_p();
extern Object icp_error_internal();
extern Object icp_message_functions_icp_prologue();
extern Object inhibit_restore_detail_pane_p();
extern Object initialize_native_window();
extern Object initialize_native_window_type();
extern Object install_tiling_pattern();
extern Object instantaneous_icp_reader_byte_count();
extern Object instantaneous_icp_writer_byte_count();
extern Object lay_out_window();
extern Object limit_native_window_size();
extern Object limit_native_window_size_1();
extern Object load_and_initialize_type_description();
extern Object make_32bit_integer();
extern Object make_basic_native_window();
extern Object make_color_map();
extern Object make_corresponding_icp_gensym_window();
extern Object make_corresponding_icp_icon_rendering();
extern Object make_gensym_list_1();
extern Object make_gensym_window();
extern Object make_monochrome_color_description_plist();
extern Object make_native_view_1();
extern Object make_native_window_1_1();
extern Object make_or_revise_window();
extern Object make_permanent_native_view_structure_internal();
extern Object make_permanent_native_window_structure_internal();
extern Object make_permanent_workspace_view_structure_internal();
extern Object make_rendering_structure();
extern Object make_thread_array();
extern Object make_tiling_pattern();
extern Object make_unbounded_region();
extern Object make_workspace_view_1_1();
extern Object make_workspace_view_structure();
extern Object manage_native_editor();
extern Object manage_native_window_1();
extern Object manage_native_window_locally();
extern Object manage_scrollbars_1();
extern Object map_to_color_value();
extern Object map_to_color_value_1();
extern Object maximum_window_height();
extern Object maximum_window_width();
extern Object mdi_child_p();
extern Object mdi_frame_p();
extern Object mega_refresh_1();
extern Object memq_function();
extern Object multiwindow_option_p();
extern Object multiwindow_ui_p();
extern Object mutate_global_property();
extern Object n_32bit_integer_high_part();
extern Object n_32bit_integer_low_part();
extern Object n_32bit_integer_p();
extern Object native_animation_control_p();
extern Object native_basic_dialogs_p();
extern Object native_custom_dialogs_p();
extern Object native_debugger_dialog_p();
extern Object native_file_dialog_p();
extern Object native_file_dialog_without_custom_buttons_p();
extern Object native_icons_p();
extern Object native_menu_bar_p();
extern Object native_pane_p();
extern Object native_pop_up_menus_p();
extern Object native_progress_bar_p();
extern Object native_simple_dialogs_p();
extern Object native_view_p();
extern Object native_window_center();
extern Object native_window_container_type();
extern Object native_window_embedded_p();
extern Object native_window_handle_for_last_event_qm();
extern Object native_window_has_style();
extern Object native_window_p();
extern Object native_window_structure_memory_usage();
extern Object native_window_type_for_type_code();
extern Object native_window_workstation();
extern Object native_windows_p();
extern Object nms_controls_p();
extern Object nms_toolbars_p();
extern Object note_change_in_gensym_window();
extern Object old_style_mdi_frame_p();
extern Object outstanding_native_window_count();
extern Object outstanding_workspace_view_count();
extern Object paint_clipped_icon_onto_graph_raster();
extern Object paint_clipped_marker_onto_graph_raster();
extern Object paint_icon_onto_graph_raster();
extern Object paint_marker_onto_graph_raster();
extern Object paint_solid_rectangle_in_current_window();
extern Object parse_ui_style();
extern Object printing_window_p();
extern Object process_window_style_options();
extern Object push_optimized_constant();
extern Object queue_pop();
extern Object read_icp_32bit_integer();
extern Object read_icp_boolean();
extern Object read_icp_corresponding_object_index();
extern Object read_icp_fixnum();
extern Object read_icp_icp_tree();
extern Object read_icp_integer();
extern Object read_icp_unsigned_integer();
extern Object read_icp_wide_string();
extern Object reclaim_32bit_integer();
extern Object reclaim_byte_vector_16();
extern Object reclaim_color_map_if_any();
extern Object reclaim_default_pane_background_color_or_tiling_pattern();
extern Object reclaim_gensym_cons_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_tree_with_text_strings();
extern Object reclaim_icp_tree_with_text_strings();
extern Object reclaim_if_evaluation_item_reference();
extern Object reclaim_local_event();
extern Object reclaim_native_window();
extern Object reclaim_native_window_1_1();
extern Object reclaim_native_window_by_handle();
extern Object reclaim_native_windows();
extern Object reclaim_text_string();
extern Object reclaim_wide_string();
extern Object reclaim_workspace_view_1_1();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object redirect_window_1();
extern Object refresh_rectangle_of_window();
extern Object refresh_telewindow();
extern Object refresh_window();
extern Object regenerate_optimized_constant();
extern Object request_to_refresh_window_1();
extern Object reshape_native_g2_window();
extern Object reshape_telewindow();
extern Object resumable_icp_pop();
extern Object resumable_icp_pop_list_if_end_marker();
extern Object resumable_icp_push();
extern Object save_native_window_geometry();
extern Object scroll_native_window_1();
extern Object selection_ui_p();
extern Object send_icp_begin_window_update();
extern Object send_icp_create_window();
extern Object send_icp_manage_editor();
extern Object send_icp_manage_scrollbars();
extern Object send_icp_manage_window();
extern Object send_icp_mega_refresh();
extern Object send_icp_redirect_window();
extern Object send_icp_request_to_move_native_window();
extern Object send_icp_request_to_move_window();
extern Object send_icp_request_to_refresh_window();
extern Object send_icp_request_to_reshape_native_window();
extern Object send_icp_request_to_reshape_window();
extern Object send_icp_scroll_window();
extern Object send_icp_stack_windows();
extern Object server_and_client_are_same_host_p();
extern Object server_and_client_share_file_system_p();
extern Object set_native_window_x_scroll();
extern Object set_native_window_y_scroll();
extern Object stack_native_windows_1();
extern Object standard_ui_p();
extern Object start_writing_icp_message();
extern Object string_equalw();
extern Object structure_type_p();
extern Object symbol_from_key_code();
extern Object sync_graphics_on_current_window();
extern Object synchronize_icp_on_window_with_drawing();
extern Object telewindows_embedded_p();
extern Object telewindows_mdi_frame_p();
extern Object telewindows_multiwindow_ui_p();
extern Object telewindows_twaxl_mode_p();
extern Object telewindows_win32_window_p();
extern Object telewindows_window_p();
extern Object text_string_p();
extern Object this_is_twng_p();
extern Object top_level_window_p();
extern Object trace_reshape_event();
extern Object twaxl_window_p();
extern Object twng_p();
extern Object twng_window_p();
extern Object update_object_pool_meters_list();
extern Object update_window();
extern Object win32_window_p();
extern Object windows_platform_p();
extern Object word_vector_to_fixnum_list();
extern Object workspace_view_structure_memory_usage();
extern Object write_icp_32bit_integer();
extern Object write_icp_boolean();
extern Object write_icp_corresponding_object_index();
extern Object write_icp_fixnum();
extern Object write_icp_icp_tree();
extern Object write_icp_integer();
extern Object write_icp_list_of_unsigned_integers();
extern Object write_icp_unsigned_integer();
extern Object write_icp_wide_string();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Abort_for_icp_catcher_qm, Qabort_for_icp_catcher_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);
DECLARE_VARIABLE_WITH_SYMBOL(Bottom_edge_of_draw_area, Qbottom_edge_of_draw_area);
extern Object Cached_found_ui_for_gensym_window_ui;
extern Object Cached_gensym_window_for_gensym_window_ui;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_native_windows, Qchain_of_available_native_windows);
extern Object Chain_of_available_native_windows_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_workspace_views, Qchain_of_available_workspace_views);
extern Object Chain_of_available_workspace_views_vector;
extern Object Command_line_arguments;
DECLARE_VARIABLE_WITH_SYMBOL(Current_background_color_value, Qcurrent_background_color_value);
DECLARE_VARIABLE_WITH_SYMBOL(Current_color_map, Qcurrent_color_map);
DECLARE_VARIABLE_WITH_SYMBOL(Current_drawing_transfer_mode, Qcurrent_drawing_transfer_mode);
DECLARE_VARIABLE_WITH_SYMBOL(Current_foreground_color_value, Qcurrent_foreground_color_value);
DECLARE_VARIABLE_WITH_SYMBOL(Current_graph_rendering, Qcurrent_graph_rendering);
DECLARE_VARIABLE_WITH_SYMBOL(Current_graph_rendering_structure, Qcurrent_graph_rendering_structure);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_buffer, Qcurrent_icp_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_port, Qcurrent_icp_port);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_read_trace_level, Qcurrent_icp_read_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_socket, Qcurrent_icp_socket);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_write_trace_level, Qcurrent_icp_write_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_native_window_qm, Qcurrent_native_window_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_color_value_list, Qcurrent_scratchpad_color_value_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster, Qcurrent_scratchpad_raster);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_list, Qcurrent_scratchpad_raster_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_type, Qcurrent_scratchpad_raster_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_standard_icp_object_index_space, Qcurrent_standard_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_system_name, Qcurrent_system_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_temporary_icp_object_index_space, Qcurrent_temporary_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_window, Qcurrent_window);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation_window, Qcurrent_workstation_window);
DECLARE_VARIABLE_WITH_SYMBOL(Current_write_icp_byte_position, Qcurrent_write_icp_byte_position);
extern Object Default_mdi_child_style;
extern Object Default_pane_window_style;
extern Object Default_top_level_window_style;
DECLARE_VARIABLE_WITH_SYMBOL(Defer_notifications_qm, Qdefer_notifications_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Disable_resumability, Qdisable_resumability);
DECLARE_VARIABLE_WITH_SYMBOL(Do_icp_flow_control_qm, Qdo_icp_flow_control_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Drawing_on_window, Qdrawing_on_window);
#define Dt_center FIX((SI_Long)1L)
#define Dt_left FIX((SI_Long)0L)
#define Dt_right FIX((SI_Long)2L)
#define Editor_append_output FIX((SI_Long)52L)
#define Editor_clear_output FIX((SI_Long)51L)
#define Editor_disabled_breakpoint_flag FIX((SI_Long)1048576L)
#define Editor_set_breakpoints FIX((SI_Long)23L)
#define Editor_show_completions FIX((SI_Long)57L)
#define Editor_style_category FIX((SI_Long)1L)
#define Editor_style_completion FIX((SI_Long)2L)
DECLARE_VARIABLE_WITH_SYMBOL(Flush_graphics_immediately_qm, Qflush_graphics_immediately_qm);
#define Frame_type_child FIX((SI_Long)2L)
#define Frame_type_classic FIX((SI_Long)1L)
#define Frame_type_mdi FIX((SI_Long)4L)
#define Frame_type_none FIX((SI_Long)0L)
#define Frame_type_sdi FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(G2_machine_type, Qg2_machine_type);
DECLARE_VARIABLE_WITH_SYMBOL(G2_operating_system, Qg2_operating_system);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm, Qicp_buffer_of_start_of_message_series_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_buffers_for_message_group, Qicp_buffers_for_message_group);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm, Qicp_byte_position_of_start_of_message_series_qm);
extern Object Icp_connection_closed;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_printing_message_handler_array, Qicp_printing_message_handler_array);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_read_trace_cutoff_level_qm, Qicp_read_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_suspend, Qicp_suspend);
#define Icp_window_protocol_supports_basic_dialogs FIX((SI_Long)36L)
#define Icp_window_protocol_supports_debugger_dialog FIX((SI_Long)48L)
#define Icp_window_protocol_supports_event_plists FIX((SI_Long)26L)
#define Icp_window_protocol_supports_list_directory FIX((SI_Long)40L)
#define Icp_window_protocol_supports_mdi FIX((SI_Long)37L)
#define Icp_window_protocol_supports_native_editor_ex FIX((SI_Long)81L)
#define Icp_window_protocol_supports_native_icons FIX((SI_Long)33L)
#define Icp_window_protocol_supports_native_progress_bar FIX((SI_Long)35L)
#define Icp_window_protocol_supports_native_widgets FIX((SI_Long)27L)
#define Icp_window_protocol_supports_nms_controls FIX((SI_Long)39L)
#define Icp_window_protocol_supports_nms_menus FIX((SI_Long)29L)
#define Icp_window_protocol_supports_scroll_while_minimized_fix FIX((SI_Long)61L)
#define Icp_window_protocol_supports_wide_polyline FIX((SI_Long)24L)
DECLARE_VARIABLE_WITH_SYMBOL(Icp_write_trace_cutoff_level_qm, Qicp_write_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);
extern Object Known_ui_styles;
DECLARE_VARIABLE_WITH_SYMBOL(Left_edge_of_draw_area, Qleft_edge_of_draw_area);
DECLARE_VARIABLE_WITH_SYMBOL(Local_host_name, Qlocal_host_name);
#define Managed_array_index_offset FIX((SI_Long)2L)
DECLARE_VARIABLE_WITH_SYMBOL(Maximum_height, Qmaximum_height);
extern Object Maximum_in_place_array_size;
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
DECLARE_VARIABLE_WITH_SYMBOL(Maximum_width, Qmaximum_width);
DECLARE_VARIABLE_WITH_SYMBOL(Native_window_count, Qnative_window_count);
#define Nip_caption_window FIX((SI_Long)7L)
#define Nip_destroy_window FIX((SI_Long)6L)
#define Nip_set_closeable FIX((SI_Long)15L)
#define Nip_set_icon FIX((SI_Long)14L)
#define Nip_wintype_classic FIX((SI_Long)0L)
#define Nip_wintype_embedded FIX((SI_Long)2L)
#define Nip_wintype_mask FIX((SI_Long)15L)
#define Nip_wintype_mdichild FIX((SI_Long)1L)
#define Nip_wintype_pane FIX((SI_Long)4L)
#define Nip_wintype_toplevel FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_for_message_series, Qnumber_of_icp_bytes_for_message_series);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_in_message_group, Qnumber_of_icp_bytes_in_message_group);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer, Qnumber_of_icp_bytes_to_fill_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(On_monochrome_raster_list_p, Qon_monochrome_raster_list_p);
DECLARE_VARIABLE_WITH_SYMBOL(On_window_with_drawing, Qon_window_with_drawing);
DECLARE_VARIABLE_WITH_SYMBOL(On_window_without_drawing, Qon_window_without_drawing);
DECLARE_VARIABLE_WITH_SYMBOL(Paint_only_target_monochrome_raster_p, Qpaint_only_target_monochrome_raster_p);
DECLARE_VARIABLE_WITH_SYMBOL(Profiling_enabled_qm, Qprofiling_enabled_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Resumable_icp_state, Qresumable_icp_state);
DECLARE_VARIABLE_WITH_SYMBOL(Right_edge_of_draw_area, Qright_edge_of_draw_area);
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
extern Object The_type_description_of_native_view;
extern Object The_type_description_of_native_window;
extern Object The_type_description_of_workspace_view;
DECLARE_VARIABLE_WITH_SYMBOL(Top_edge_of_draw_area, Qtop_edge_of_draw_area);
DECLARE_VARIABLE_WITH_SYMBOL(Trace_reshape_events, Qtrace_reshape_events);
DECLARE_VARIABLE_WITH_SYMBOL(Type_of_current_window, Qtype_of_current_window);
DECLARE_VARIABLE_WITH_SYMBOL(Workspace_view_count, Qworkspace_view_count);
DECLARE_VARIABLE_WITH_SYMBOL(Writing_icp_message_group, Qwriting_icp_message_group);
#define Ws_caption FIX((SI_Long)192L)
#define Ws_child FIX((SI_Long)16384L)
#define Ws_clipchildren FIX((SI_Long)512L)
#define Ws_clipsiblings FIX((SI_Long)1024L)
#define Ws_hscroll FIX((SI_Long)16L)
#define Ws_maximize FIX((SI_Long)256L)
#define Ws_maximizebox FIX((SI_Long)1L)
#define Ws_minimize FIX((SI_Long)8192L)
#define Ws_minimizebox FIX((SI_Long)2L)
#define Ws_overlapped FIX((SI_Long)0L)
#define Ws_popup FIX((SI_Long)32768L)
#define Ws_sysmenu FIX((SI_Long)8L)
#define Ws_thickframe FIX((SI_Long)4L)
#define Ws_visible FIX((SI_Long)4096L)
#define Ws_vscroll FIX((SI_Long)32L)
