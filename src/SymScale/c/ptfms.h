/* ptfms.h -- Header File for ptfms.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Kname;
extern Object Qtan;
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

extern Object allocate_byte_vector_16(Object);
extern Object allocate_x11_colors(Object);
extern Object allocate_x11_pixel_value(Object,Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object bytes_per_simple_vector(Object);
extern Object c_native_clock_ticks_or_cache(Object,Object);
extern Object c_read_clipboard(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_uuid_create(Object);
extern Object c_write_clipboard(Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_allocate_x_font(Object,Object);
extern Object c_x11_draw_polygon(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_draw_string(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_draw_string_in_font(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_draw_string_in_font_with_clipping(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_draw_string_with_clipping(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_draw_wide_polyline(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_get_pixel_value(Object,Object,Object);
extern Object c_x11_initialize(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_last_event_value(Object,Object,Object);
extern Object c_x11_parse_geometry(Object);
extern Object c_x11_pfill_clipped_polygon(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_preinitialize(Object,Object);
extern Object c_x11_read_cut_buffer(Object,Object,Object);
extern Object c_x11_write_cut_buffer(Object,Object,Object);
extern Object canonicalize_gensym_key_code(Object);
extern Object change_icp_window_protocol_version(Object,Object);
extern Object charting_library_version_qm(void);
extern Object check_shape_of_window_without_lookahead(Object,Object);
extern Object clear_optimized_constants(void);
extern Object construct_local_event_plist(Object);
extern Object convert_key_code_to_key_symbol(Object);
extern Object copy_constant_wide_string_given_length(Object,Object);
extern Object copy_event_plist(Object);
extern Object copy_foreign_string_arg_if_appropriate(Object);
extern Object copy_local_event(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_symbol_name(int,...);
extern Object copy_text_string(Object);
extern Object copy_tree_using_gensym_conses_1(Object);
extern Object create_x11_color_plist_from_color_hierarchy(int,...);
extern Object decode_native_control_event(Object,Object,Object,Object,Object,Object,Object);
extern Object delete_gensym_element_1(Object,Object);
extern Object direct_structure_method(Object,Object);
extern Object downcase_text_string_in_place(Object);
extern Object enqueue_local_event(int,...);
extern Object enqueue_local_paste_availability_event(Object,Object,Object);
extern Object enqueue_window_reshape_event(int,...);
extern Object exit_lisp_process(int,...);
extern Object export_text_string(int,...);
extern Object extract_ethernet_address_from_string(Object,Object,Object,Object);
extern Object file_descriptor_for_native_window(Object);
extern Object find_local_reshape_event(Object,Object,Object,Object,Object,Object);
extern Object flush_window_reshape_local_event_queue(Object);
extern Object generate_float_vector(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object gensym_list_4(Object,Object,Object,Object);
extern Object gensym_string_length(Object);
extern Object get_all_x11_events(Object);
extern Object get_background_color_or_tiling_pattern(void);
extern Object get_clock_sequence_for_uuid_1(void);
extern Object get_command_line_flag_argument(int,...);
extern Object get_command_line_keyword_argument(int,...);
extern Object get_default_scale_from_command_line_1(Object,Object);
extern Object get_default_x11_display(void);
extern Object get_default_x_and_y_scale_from_command_line_if_any(int,...);
extern Object get_ethernet_address_if_possible(Object);
extern Object get_ethernet_address_if_possible_for_unix(void);
extern Object get_event_queue_of_native_window(Object);
extern Object get_gensym_environment_variable(Object);
extern Object get_gensym_window_reshape_event_queue(Object);
extern Object get_height_of_native_window(Object);
extern Object get_icon_name_from_command_line_if_any(void);
extern Object get_last_local_mouse_motion_event(Object);
extern Object get_local_machine_id_function(void);
extern Object get_node_id_for_uuid_1(void);
extern Object get_parent_windowhandle(void);
extern Object get_pixel_value(Object,Object,Object);
extern Object get_position_of_mouse(void);
extern Object get_reshape_event_queue_of_native_window(Object);
extern Object get_system_metrics_for_local_window(void);
extern Object get_time_for_uuid(void);
extern Object get_time_for_uuid_internal(Object);
extern Object get_values_from_x11_parse_geometry(Object);
extern Object get_width_of_native_window(Object);
extern Object get_win32_uuid(Object);
extern Object get_window_name_from_command_line_if_any(void);
extern Object get_x11_pixel_value_from_rgb(Object,Object,Object,Object,Object);
extern Object get_x_position_of_native_window(Object);
extern Object get_y_position_of_native_window(Object);
extern Object handle_no_solution_to_raster_allocation_failure(Object,Object,Object);
extern Object handle_reshape_event(Object,Object);
extern Object hash_wide_string_portion(Object,Object,Object);
extern Object import_text_string(int,...);
extern Object last_exposure_event_already_queued_p(Object);
extern Object lay_out_window(Object);
extern Object lengthw(Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object local_clipboard_has_text_p(Object);
extern Object local_event_structure_memory_usage(void);
extern Object local_gensym_x11_display(void);
extern Object make_block_near_mouse_cache(void);
extern Object make_block_near_mouse_cache_internal_1(void);
extern Object make_gensym_list_1(Object);
extern Object make_local_event_1(void);
extern Object make_monochrome_color_description_plist(Object,Object);
extern Object make_named_dynamic_extent_description(Object,Object,Object,Object,Object,Object,Object);
extern Object make_or_revise_window(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_or_revise_window_per_native_window(Object,Object);
extern Object make_permanent_local_event_structure_internal(void);
extern Object make_permanent_workstation_structure_internal(void);
extern Object make_queue(void);
extern Object make_thread_array(Object);
extern Object make_uuid(void);
extern Object make_window_parameters_plist(Object);
extern Object make_workstation_1(Object);
extern Object map_client_dialog_id_to_global_dialog_id(Object);
extern Object map_to_black_or_white(Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object native_window_handle_for_last_event_qm(Object);
extern Object no_local_window_p(void);
extern Object note_change_in_gensym_window(Object);
extern Object notify_user_at_console(int,...);
extern Object notify_user_at_console_and_on_logbook(int,...);
extern Object obtain_long_enough_adjustable_gensym_string(Object);
extern Object obtain_simple_gensym_string(Object);
extern Object obtain_text_string(Object);
extern Object outstanding_local_event_count(void);
extern Object outstanding_workstation_count(void);
extern Object position_in_wide_string(Object,Object);
extern Object print_display_error(void);
extern Object process_command_line_resolution_arg(int,...);
extern Object process_command_line_scale_arg(int,...);
extern Object push_optimized_constant(Object);
extern Object queue_insert(Object,Object);
extern Object queue_non_empty_p(Object);
extern Object queue_peek(Object);
extern Object queue_pop(Object);
extern Object read_clipboard(Object);
extern Object read_fixnum_from_string(int,...);
extern Object read_number_from_string(Object,Object,Object);
extern Object read_x_window_cut_buffer(Object);
extern Object reclaim_block_near_mouse_cache_1(Object);
extern Object reclaim_block_near_mouse_cache_function(Object);
extern Object reclaim_event_plist(Object);
extern Object reclaim_gensym_cons_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_string(Object);
extern Object reclaim_gensym_tree_with_text_strings(Object);
extern Object reclaim_icp_object_map_for_workstation(Object);
extern Object reclaim_if_managed_float(Object);
extern Object reclaim_local_event(Object);
extern Object reclaim_local_event_1_1(Object);
extern Object reclaim_local_event_queue(Object);
extern Object reclaim_mouse_pointers_if_g2(Object);
extern Object reclaim_non_kb_workspaces_for_this_workstation_only_if_g2(Object);
extern Object reclaim_queue(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_wide_string(Object);
extern Object reclaim_window_for_workstation(Object);
extern Object reclaim_workstation(Object);
extern Object reclaim_workstation_context_stack_if_g2(Object);
extern Object reclaim_workstation_event_queue_if_g2(Object);
extern Object reclaim_workstation_internal_1(Object);
extern Object reclaim_workstation_tasks(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object refresh_window(Object);
extern Object regenerate_optimized_constant(Object);
extern Object remove_dialog_given_client_id(Object);
extern Object reset_clock_sequence_for_uuid(void);
extern Object reshape_native_g2_window(Object,Object);
extern Object rgb2gray(Object,Object,Object);
extern Object scale_scale(Object,Object,Object);
extern Object scrollbar_code_name(Object);
extern Object set_position_of_mouse_1(Object,Object);
extern Object shift_position_of_mouse_1(Object,Object);
extern Object slave_gensym_window_qm(Object);
extern Object start_mouse_tracking(Object);
extern Object stop_mouse_tracking(Object);
extern Object string_value_for_last_event_qm(Object);
extern Object sync_graphics_on_native_window(Object);
extern Object text_string_p(Object);
extern Object tformat_gensym_string(int,...);
extern Object tformat_text_string(int,...);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_binary_string_printed_representation(Object);
extern Object twrite_general_string(Object);
extern Object twrite_positive_fixnum_in_radix(Object,Object);
extern Object twrite_uuid_printed_representation(Object);
extern Object unix_command_output_as_string(Object);
extern Object unpack_list_directory_request_value(Object);
extern Object update_object_pool_meters_list(Object);
extern Object wide_string_substring(Object,Object,Object);
extern Object wide_string_to_gensym_string(Object);
extern Object window_for_workstation_function(Object);
extern Object window_supports_request_for_paste_availability_function(Object);
extern Object windows_platform_p(void);
extern Object workstation_structure_memory_usage(void);
extern Object write_clipboard(Object,Object);
extern Object write_x_window_cut_buffer(Object,Object);
extern Object x11_display_specified_p(void);
extern Object x11_preinitialize_if_necessary(void);

#else

extern Object allocate_byte_vector_16();
extern Object allocate_x11_colors();
extern Object allocate_x11_pixel_value();
extern Object bytes_per_double_float_simple_array();
extern Object bytes_per_simple_vector();
extern Object c_native_clock_ticks_or_cache();
extern Object c_read_clipboard();
extern Object c_uuid_create();
extern Object c_write_clipboard();
extern Object c_x11_allocate_x_font();
extern Object c_x11_draw_polygon();
extern Object c_x11_draw_string();
extern Object c_x11_draw_string_in_font();
extern Object c_x11_draw_string_in_font_with_clipping();
extern Object c_x11_draw_string_with_clipping();
extern Object c_x11_draw_wide_polyline();
extern Object c_x11_get_pixel_value();
extern Object c_x11_initialize();
extern Object c_x11_last_event_value();
extern Object c_x11_parse_geometry();
extern Object c_x11_pfill_clipped_polygon();
extern Object c_x11_preinitialize();
extern Object c_x11_read_cut_buffer();
extern Object c_x11_write_cut_buffer();
extern Object canonicalize_gensym_key_code();
extern Object change_icp_window_protocol_version();
extern Object charting_library_version_qm();
extern Object check_shape_of_window_without_lookahead();
extern Object clear_optimized_constants();
extern Object construct_local_event_plist();
extern Object convert_key_code_to_key_symbol();
extern Object copy_constant_wide_string_given_length();
extern Object copy_event_plist();
extern Object copy_foreign_string_arg_if_appropriate();
extern Object copy_local_event();
extern Object copy_out_current_wide_string();
extern Object copy_symbol_name();
extern Object copy_text_string();
extern Object copy_tree_using_gensym_conses_1();
extern Object create_x11_color_plist_from_color_hierarchy();
extern Object decode_native_control_event();
extern Object delete_gensym_element_1();
extern Object direct_structure_method();
extern Object downcase_text_string_in_place();
extern Object enqueue_local_event();
extern Object enqueue_local_paste_availability_event();
extern Object enqueue_window_reshape_event();
extern Object exit_lisp_process();
extern Object export_text_string();
extern Object extract_ethernet_address_from_string();
extern Object file_descriptor_for_native_window();
extern Object find_local_reshape_event();
extern Object flush_window_reshape_local_event_queue();
extern Object generate_float_vector();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object gensym_list_4();
extern Object gensym_string_length();
extern Object get_all_x11_events();
extern Object get_background_color_or_tiling_pattern();
extern Object get_clock_sequence_for_uuid_1();
extern Object get_command_line_flag_argument();
extern Object get_command_line_keyword_argument();
extern Object get_default_scale_from_command_line_1();
extern Object get_default_x11_display();
extern Object get_default_x_and_y_scale_from_command_line_if_any();
extern Object get_ethernet_address_if_possible();
extern Object get_ethernet_address_if_possible_for_unix();
extern Object get_event_queue_of_native_window();
extern Object get_gensym_environment_variable();
extern Object get_gensym_window_reshape_event_queue();
extern Object get_height_of_native_window();
extern Object get_icon_name_from_command_line_if_any();
extern Object get_last_local_mouse_motion_event();
extern Object get_local_machine_id_function();
extern Object get_node_id_for_uuid_1();
extern Object get_parent_windowhandle();
extern Object get_pixel_value();
extern Object get_position_of_mouse();
extern Object get_reshape_event_queue_of_native_window();
extern Object get_system_metrics_for_local_window();
extern Object get_time_for_uuid();
extern Object get_time_for_uuid_internal();
extern Object get_values_from_x11_parse_geometry();
extern Object get_width_of_native_window();
extern Object get_win32_uuid();
extern Object get_window_name_from_command_line_if_any();
extern Object get_x11_pixel_value_from_rgb();
extern Object get_x_position_of_native_window();
extern Object get_y_position_of_native_window();
extern Object handle_no_solution_to_raster_allocation_failure();
extern Object handle_reshape_event();
extern Object hash_wide_string_portion();
extern Object import_text_string();
extern Object last_exposure_event_already_queued_p();
extern Object lay_out_window();
extern Object lengthw();
extern Object load_and_initialize_type_description();
extern Object local_clipboard_has_text_p();
extern Object local_event_structure_memory_usage();
extern Object local_gensym_x11_display();
extern Object make_block_near_mouse_cache();
extern Object make_block_near_mouse_cache_internal_1();
extern Object make_gensym_list_1();
extern Object make_local_event_1();
extern Object make_monochrome_color_description_plist();
extern Object make_named_dynamic_extent_description();
extern Object make_or_revise_window();
extern Object make_or_revise_window_per_native_window();
extern Object make_permanent_local_event_structure_internal();
extern Object make_permanent_workstation_structure_internal();
extern Object make_queue();
extern Object make_thread_array();
extern Object make_uuid();
extern Object make_window_parameters_plist();
extern Object make_workstation_1();
extern Object map_client_dialog_id_to_global_dialog_id();
extern Object map_to_black_or_white();
extern Object memq_function();
extern Object mutate_global_property();
extern Object native_window_handle_for_last_event_qm();
extern Object no_local_window_p();
extern Object note_change_in_gensym_window();
extern Object notify_user_at_console();
extern Object notify_user_at_console_and_on_logbook();
extern Object obtain_long_enough_adjustable_gensym_string();
extern Object obtain_simple_gensym_string();
extern Object obtain_text_string();
extern Object outstanding_local_event_count();
extern Object outstanding_workstation_count();
extern Object position_in_wide_string();
extern Object print_display_error();
extern Object process_command_line_resolution_arg();
extern Object process_command_line_scale_arg();
extern Object push_optimized_constant();
extern Object queue_insert();
extern Object queue_non_empty_p();
extern Object queue_peek();
extern Object queue_pop();
extern Object read_clipboard();
extern Object read_fixnum_from_string();
extern Object read_number_from_string();
extern Object read_x_window_cut_buffer();
extern Object reclaim_block_near_mouse_cache_1();
extern Object reclaim_block_near_mouse_cache_function();
extern Object reclaim_event_plist();
extern Object reclaim_gensym_cons_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_string();
extern Object reclaim_gensym_tree_with_text_strings();
extern Object reclaim_icp_object_map_for_workstation();
extern Object reclaim_if_managed_float();
extern Object reclaim_local_event();
extern Object reclaim_local_event_1_1();
extern Object reclaim_local_event_queue();
extern Object reclaim_mouse_pointers_if_g2();
extern Object reclaim_non_kb_workspaces_for_this_workstation_only_if_g2();
extern Object reclaim_queue();
extern Object reclaim_text_string();
extern Object reclaim_wide_string();
extern Object reclaim_window_for_workstation();
extern Object reclaim_workstation();
extern Object reclaim_workstation_context_stack_if_g2();
extern Object reclaim_workstation_event_queue_if_g2();
extern Object reclaim_workstation_internal_1();
extern Object reclaim_workstation_tasks();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object refresh_window();
extern Object regenerate_optimized_constant();
extern Object remove_dialog_given_client_id();
extern Object reset_clock_sequence_for_uuid();
extern Object reshape_native_g2_window();
extern Object rgb2gray();
extern Object scale_scale();
extern Object scrollbar_code_name();
extern Object set_position_of_mouse_1();
extern Object shift_position_of_mouse_1();
extern Object slave_gensym_window_qm();
extern Object start_mouse_tracking();
extern Object stop_mouse_tracking();
extern Object string_value_for_last_event_qm();
extern Object sync_graphics_on_native_window();
extern Object text_string_p();
extern Object tformat_gensym_string();
extern Object tformat_text_string();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_binary_string_printed_representation();
extern Object twrite_general_string();
extern Object twrite_positive_fixnum_in_radix();
extern Object twrite_uuid_printed_representation();
extern Object unix_command_output_as_string();
extern Object unpack_list_directory_request_value();
extern Object update_object_pool_meters_list();
extern Object wide_string_substring();
extern Object wide_string_to_gensym_string();
extern Object window_for_workstation_function();
extern Object window_supports_request_for_paste_availability_function();
extern Object windows_platform_p();
extern Object workstation_structure_memory_usage();
extern Object write_clipboard();
extern Object write_x_window_cut_buffer();
extern Object x11_display_specified_p();
extern Object x11_preinitialize_if_necessary();

#endif

/* variables/constants */
#define Allocated_clipboard_text_length FIX((SI_Long)65536L)
DECLARE_VARIABLE_WITH_SYMBOL(Always_use_current_time_for_uuid, Qalways_use_current_time_for_uuid);
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);
DECLARE_VARIABLE_WITH_SYMBOL(Cached_local_gensym_x11_display, Qcached_local_gensym_x11_display);
#define Caps_lock_bit FIX((SI_Long)131072L)
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_local_events, Qchain_of_available_local_events);
extern Object Chain_of_available_local_events_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_workstations, Qchain_of_available_workstations);
extern Object Chain_of_available_workstations_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Charting_library_version_qm, Qcharting_library_version_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Check_time_on_next_uuid, Qcheck_time_on_next_uuid);
#define Clipboard_read_results_failure_code FIX((SI_Long)65535L)
#define Clipboard_reading_results_vector_length FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Clock_sequence_for_uuid, Qclock_sequence_for_uuid);
DECLARE_VARIABLE_WITH_SYMBOL(Color_hierarchy, Qcolor_hierarchy);
DECLARE_VARIABLE_WITH_SYMBOL(Column, Qcolumn);
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation, Qcurrent_workstation);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation_context, Qcurrent_workstation_context);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation_native_window_qm, Qcurrent_workstation_native_window_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation_window, Qcurrent_workstation_window);
extern Object Default_width_of_window_border;
DECLARE_VARIABLE_WITH_SYMBOL(Delete_corresponding_object_qm, Qdelete_corresponding_object_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Do_not_error_in_x11_create_pixmap_on_failed_allocation, Qdo_not_error_in_x11_create_pixmap_on_failed_allocation);
extern Object Extract_ethernet_script;
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
extern Object Fixnum_time_interval_for_automatic_xsync;
DECLARE_VARIABLE_WITH_SYMBOL(Fixnum_time_of_last_xsync, Qfixnum_time_of_last_xsync);
extern Object Fixnum_time_units_per_second;
DECLARE_VARIABLE_WITH_SYMBOL(For_workstation_context, Qfor_workstation_context);
DECLARE_VARIABLE_WITH_SYMBOL(For_workstation_polling, Qfor_workstation_polling);
DECLARE_VARIABLE_WITH_SYMBOL(G2_machine_type, Qg2_machine_type);
DECLARE_VARIABLE_WITH_SYMBOL(G2_operating_system, Qg2_operating_system);
#define Gensym_windows_maximum_supported_dpi FIX((SI_Long)200L)
extern Object Gensym_windows_maximum_supported_scale;
#define Gensym_windows_minimum_supported_dpi FIX((SI_Long)36L)
extern Object Gensym_windows_minimum_supported_scale;
#define Gensym_windows_standard_dpi FIX((SI_Long)75L)
extern Object Gray_gensym_color_alist;
#define Icp_window_protocol_supports_append_control_ex FIX((SI_Long)78L)
#define Icp_window_protocol_supports_chart_views FIX((SI_Long)54L)
#define Icp_window_protocol_supports_chart_views_in_panes FIX((SI_Long)79L)
#define Icp_window_protocol_supports_choose_directory FIX((SI_Long)84L)
#define Icp_window_protocol_supports_choose_directory_on_server FIX((SI_Long)87L)
#define Icp_window_protocol_supports_custom_dialogs FIX((SI_Long)38L)
#define Icp_window_protocol_supports_debugger_dialog FIX((SI_Long)48L)
#define Icp_window_protocol_supports_dialog_panes FIX((SI_Long)58L)
#define Icp_window_protocol_supports_extended_dialog_text_boxes FIX((SI_Long)76L)
#define Icp_window_protocol_supports_file_dialog_ex FIX((SI_Long)45L)
#define Icp_window_protocol_supports_grid_view_delimiter_fix FIX((SI_Long)89L)
#define Icp_window_protocol_supports_grid_view_small_chunks FIX((SI_Long)70L)
#define Icp_window_protocol_supports_grid_views FIX((SI_Long)55L)
#define Icp_window_protocol_supports_hide_toolbar FIX((SI_Long)75L)
#define Icp_window_protocol_supports_html_help_ex FIX((SI_Long)67L)
#define Icp_window_protocol_supports_html_views FIX((SI_Long)47L)
#define Icp_window_protocol_supports_incremental_editor_updates FIX((SI_Long)80L)
#define Icp_window_protocol_supports_list_directory FIX((SI_Long)40L)
#define Icp_window_protocol_supports_manage_dialog FIX((SI_Long)72L)
#define Icp_window_protocol_supports_manage_logbook FIX((SI_Long)69L)
#define Icp_window_protocol_supports_manage_pane FIX((SI_Long)60L)
#define Icp_window_protocol_supports_manage_status_bar FIX((SI_Long)43L)
#define Icp_window_protocol_supports_manage_status_bar_ex FIX((SI_Long)83L)
#define Icp_window_protocol_supports_manage_ui_properties FIX((SI_Long)68L)
#define Icp_window_protocol_supports_mdi FIX((SI_Long)37L)
#define Icp_window_protocol_supports_modify_node FIX((SI_Long)73L)
#define Icp_window_protocol_supports_native_editor FIX((SI_Long)49L)
#define Icp_window_protocol_supports_native_editor_ex FIX((SI_Long)81L)
#define Icp_window_protocol_supports_native_printing_ex FIX((SI_Long)50L)
#define Icp_window_protocol_supports_new_grid_views FIX((SI_Long)59L)
#define Icp_window_protocol_supports_nip_rescale_window FIX((SI_Long)82L)
#define Icp_window_protocol_supports_nms_controls FIX((SI_Long)39L)
#define Icp_window_protocol_supports_nms_modify_control FIX((SI_Long)42L)
#define Icp_window_protocol_supports_nms_selection_callbacks FIX((SI_Long)44L)
#define Icp_window_protocol_supports_nms_set_theme FIX((SI_Long)62L)
#define Icp_window_protocol_supports_nms_unposting_callbacks FIX((SI_Long)51L)
#define Icp_window_protocol_supports_polyarcs FIX((SI_Long)53L)
#define Icp_window_protocol_supports_property_grid FIX((SI_Long)77L)
#define Icp_window_protocol_supports_scroll_while_minimized_fix FIX((SI_Long)61L)
#define Icp_window_protocol_supports_set_background_color FIX((SI_Long)90L)
#define Icp_window_protocol_supports_set_window_title FIX((SI_Long)41L)
#define Icp_window_protocol_supports_shortcut_bars FIX((SI_Long)52L)
#define Icp_window_protocol_supports_simple_dialog_ex FIX((SI_Long)64L)
#define Icp_window_protocol_supports_tabbed_mdi_mode FIX((SI_Long)71L)
#define Icp_window_protocol_supports_tabular_view_selected_rows FIX((SI_Long)56L)
#define Icp_window_protocol_supports_tabular_view_selection_changed_events FIX((SI_Long)88L)
#define Icp_window_protocol_supports_tabular_views FIX((SI_Long)85L)
#define Icp_window_protocol_supports_toolbar_docking FIX((SI_Long)63L)
#define Icp_window_protocol_supports_tree_views FIX((SI_Long)46L)
#define Icp_window_protocol_supports_tree_views_ex FIX((SI_Long)65L)
#define Icp_window_protocol_supports_views_api FIX((SI_Long)66L)
#define Icp_window_protocol_supports_views_in_dialogs FIX((SI_Long)74L)
#define Icp_window_protocol_supports_views_in_listbars FIX((SI_Long)86L)
#define Icp_window_protocol_supports_zorder_native_window FIX((SI_Long)57L)
extern Object Illegal_key_index;
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);
extern Object Key_index_bits;
extern Object Last_session_id_for_g2;
DECLARE_VARIABLE_WITH_SYMBOL(Last_workstation_serviced, Qlast_workstation_serviced);
extern Object Latest_icp_window_protocol_version;
#define Latin_1_clipboard_read_results_entry FIX((SI_Long)0L)
DECLARE_VARIABLE_WITH_SYMBOL(Local_event_count, Qlocal_event_count);
extern Object Local_event_queue;
extern Object Local_reshape_event_queue;
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
extern Object Maximum_interval_between_new_time_for_uuid;
extern Object Maximum_polygon_coordinates;
#define Maximum_polygon_points FIX((SI_Long)500L)
extern Object Maximum_suggested_length_for_simple_gensym_strings;
extern Object Maximum_x11_cut_buffer_length;
DECLARE_VARIABLE_WITH_SYMBOL(Native_window_notices_enter_and_leave_events_p, Qnative_window_notices_enter_and_leave_events_p);
extern Object Native_window_polling_interval;
extern Object Native_window_polling_interval_default;
extern Object Native_window_polling_interval_fast;
extern Object No_local_window_p;
extern Object No_local_window_p_cached;
DECLARE_VARIABLE_WITH_SYMBOL(Node_id_for_uuid, Qnode_id_for_uuid);
DECLARE_VARIABLE_WITH_SYMBOL(Node_id_for_uuid_uses_ethernet_address_p, Qnode_id_for_uuid_uses_ethernet_address_p);
#define Number_of_system_metrics FIX((SI_Long)84L)
#define Original_icp_window_protocol_version FIX((SI_Long)0L)
DECLARE_VARIABLE_WITH_SYMBOL(Result_index, Qresult_index);
DECLARE_VARIABLE_WITH_SYMBOL(Row, Qrow);
#define Rpc_s_uuid_local_only FIX((SI_Long)1824L)
extern Object Rpc_s_uuid_local_only_message;
#define Rpc_s_uuid_no_address FIX((SI_Long)1739L)
extern Object Rpc_s_uuid_no_address_message;
extern Object Scrollbar_code_names;
DECLARE_VARIABLE_WITH_SYMBOL(Service_workstations, Qservice_workstations);
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Specific_structure_for_current_workstation_context, Qspecific_structure_for_current_workstation_context);
#define Specified_max_clipboard_text_length FIX((SI_Long)65535L)
DECLARE_VARIABLE_WITH_SYMBOL(Standard_gensym_color_alist, Qstandard_gensym_color_alist);
extern Object Standard_gensym_color_subset;
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
extern Object The_type_description_of_local_event;
extern Object The_type_description_of_workstation;
DECLARE_VARIABLE_WITH_SYMBOL(Time_of_last_uuid, Qtime_of_last_uuid);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Type_of_current_workstation_context, Qtype_of_current_workstation_context);
DECLARE_VARIABLE_WITH_SYMBOL(Type_of_current_workstation_window, Qtype_of_current_workstation_window);
#define Unicode_bit FIX((SI_Long)16777216L)
extern Object Unicode_character_bits;
#define Unicode_text_clipboard_read_results_entry FIX((SI_Long)2L)
DECLARE_VARIABLE_WITH_SYMBOL(Use_current_time_for_next_uuid, Quse_current_time_for_next_uuid);
DECLARE_VARIABLE_WITH_SYMBOL(User_notified_of_uuid_uniqueness_problem_p, Quser_notified_of_uuid_uniqueness_problem_p);
#define Uuid_offset_mask FIX((SI_Long)255L)
DECLARE_VARIABLE_WITH_SYMBOL(Uuid_time_b0, Quuid_time_b0);
DECLARE_VARIABLE_WITH_SYMBOL(Uuid_time_b1, Quuid_time_b1);
DECLARE_VARIABLE_WITH_SYMBOL(Uuid_time_b2, Quuid_time_b2);
DECLARE_VARIABLE_WITH_SYMBOL(Uuid_time_b3, Quuid_time_b3);
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
DECLARE_VARIABLE_WITH_SYMBOL(Workstation_count, Qworkstation_count);
extern Object Workstations_in_service;
DECLARE_VARIABLE_WITH_SYMBOL(Write_strings_parsably_qm, Qwrite_strings_parsably_qm);
#define X11_button_press FIX((SI_Long)2L)
#define X11_button_release FIX((SI_Long)3L)
extern Object X11_event_codes_mask;
#define X11_keypress FIX((SI_Long)1L)
#define X11_no_more_events FIX((SI_Long)-1L)
#define X11_pointer_motion FIX((SI_Long)4L)
DECLARE_VARIABLE_WITH_SYMBOL(X11_preinitialized_p, Qx11_preinitialized_p);
#define X_compound_text_clipboard_read_results_entry FIX((SI_Long)1L)
