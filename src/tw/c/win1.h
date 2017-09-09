/* win1.h -- Header File for win1.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qnum_lt;
extern Object Qcar;
extern Object Qcdr;
extern Object Qerror;
extern Object Qinteger;
extern Object Kkey;
extern Object Qstring_lessp;
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
extern Object add_icp_message_type_code(Object,Object,Object);
extern Object add_twng_disconnect_callback(Object,Object);
extern Object allocate_bigger_stored_raster(Object,Object,Object,Object);
extern Object allocate_just_tiled_raster(Object,Object,Object,Object,Object);
extern Object allocate_managed_array(int,...);
extern Object allocate_scratchpad_raster(Object,Object,Object,Object);
extern Object allocate_small_2d_array(Object);
extern Object allocate_stored_raster(Object,Object,Object,Object,Object);
extern Object allocate_stored_raster_1(Object,Object,Object,Object,Object);
extern Object allocate_tiled_raster(Object,Object,Object,Object);
extern Object assign_corresponding_icp_object_index(Object,Object,Object);
extern Object beep_in_window_1(Object);
extern Object bitmap_memory_used(Object,Object,Object);
extern Object block_pending_activity(Object,Object);
extern Object bytes_per_simple_vector(Object);
extern Object cancel_list_of_pending_activity(Object);
extern Object canonical_color_name(Object);
extern Object change_icp_window_protocol_version(Object,Object);
extern Object clear_all_image_renderings_for_window(Object);
extern Object clear_optimized_constants(void);
extern Object clear_stored_raster(Object,Object,Object,Object);
extern Object clear_twng_disconnect_callbacks(Object);
extern Object close_native_window(void);
extern Object color_map_structure_memory_usage(void);
extern Object compute_rows_columns_given_tile_size(Object,Object,Object);
extern Object compute_standard_gensym_colors(int,...);
extern Object compute_tile_size_given_required_area(Object,Object);
extern Object convert_current_scratchpad_raster_to_stored_raster(Object,Object,Object,Object,Object);
extern Object convert_raster_sizes_to_memory_used(Object);
extern Object copy_foreign_string_arg_if_appropriate(Object);
extern Object copy_gensym_tree_with_text_strings(Object);
extern Object copy_gensym_window_parameters_plist(Object);
extern Object copy_tree_using_gensym_conses_1(Object);
extern Object create_stored_raster(Object,Object,Object,Object,Object);
extern Object debug_x11(void);
extern Object decode_icp_window_protocol_version(Object);
extern Object default_value_for_image_palette(void);
extern Object delete_gensym_element_1(Object,Object);
extern Object derive_standard_gensym_color_data(void);
extern Object dialog_units_to_pixels(Object,Object,Object);
extern Object direct_structure_method(Object,Object);
extern Object emit_icp_read_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_write_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object end_icp_message_group(void);
extern Object enlarge_index_space(Object,Object);
extern Object enqueue_window_reshape_event(int,...);
extern Object establish_new_object_index_for_gensym_window(int,...);
extern Object establish_telewindows_license_level(Object);
extern Object finalize_indexed_md5_context(Object,Object);
extern Object find_gensym_window_with_session_id(Object);
extern Object find_identified_drawing_activity(Object,Object);
extern Object find_irregular_size_stored_raster(Object,Object,Object,Object);
extern Object find_nearest_color(Object,Object,Object,Object,Object);
extern Object finish_pending_activity(Object);
extern Object flush_graphics_on_current_window(void);
extern Object flush_graphics_on_native_window(Object);
extern Object force_graphics_on_window(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object gensym_list_4(Object,Object,Object,Object);
extern Object gensym_window_has_not_been_reprocessed_p(Object,Object);
extern Object gensym_window_host_name(Object);
extern Object gensym_window_os_type(Object);
extern Object gensym_window_session_id(Object);
extern Object gensym_window_structure_memory_usage(void);
extern Object get_command_line_flag_argument(int,...);
extern Object get_event_queue_of_native_window(Object);
extern Object get_from_icp_port(Object,Object,Object);
extern Object get_g2_license_level(void);
extern Object get_gensym_window_of_native_window(Object);
extern Object get_gensym_window_parameter(Object,Object);
extern Object get_gensym_window_reshape_event_queue(Object);
extern Object get_icp_object_index_for_gensym_window(Object,Object);
extern Object get_local_host_name(void);
extern Object get_paste_event_queue_of_native_window(Object);
extern Object get_reshape_event_queue_of_native_window(Object);
extern Object get_system_metric(int,...);
extern Object get_ui_property(int,...);
extern Object getfq_function_no_default(Object,Object);
extern Object global_paint_mode_p(void);
extern Object handle_icp_define_gensym_window(void);
extern Object handle_icp_define_gensym_window__body(Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_force_graphics_on_window(void);
extern Object handle_icp_initialize_scratchpad_raster(void);
extern Object handle_icp_ping_drawing(void);
extern Object handle_icp_ping_drawing_reply(void);
extern Object handle_icp_ping_drawing_reply__body(Object,Object);
extern Object handle_icp_set_up_palette(void);
extern Object handle_no_solution_to_raster_allocation_failure(Object,Object,Object);
extern Object handle_ping_drawing_reply_1(Object,Object);
extern Object hard_reclaim_all_irregular_size_reclaimed_stored_rasters(Object);
extern Object hard_reclaim_all_reclaimed_stored_rasters(Object);
extern Object hard_reclaim_all_regular_size_reclaimed_stored_rasters(Object);
extern Object hue_less_p(Object,Object);
extern Object hue_saturation_value(Object,Object,Object);
extern Object icon_bitmap_memory_used(Object);
extern Object icp_connection_being_shutdown_qm(Object);
extern Object icp_connection_open_p(Object);
extern Object icp_error_internal(Object,Object,Object,Object,Object);
extern Object icp_message_functions_icp_prologue(Object);
extern Object icp_prologue_send_begin_window_update(Object);
extern Object icp_prologue_set_background_color_value(Object);
extern Object icp_prologue_set_transfer_mode(Object);
extern Object icp_socket_for_gensym_window_qm(Object);
extern Object icp_socket_number_of_outstanding_bytes(Object);
extern Object identified_drawing_activity_structure_memory_usage(void);
extern Object increment_current_gensym_window_serial_number(void);
extern Object initialize_gensym_window_after_connection(Object);
extern Object initialize_icp_object_type(Object,Object,Object,Object);
extern Object initialize_icp_object_type_compile(Object,Object,Object);
extern Object initialize_image_palette_of_new_gensym_window(Object);
extern Object initialize_scratchpad_raster(Object,Object,Object,Object,Object);
extern Object initialize_v5_mode(void);
extern Object instantaneous_icp_reader_byte_count(void);
extern Object instantaneous_icp_writer_byte_count(void);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_color_map(Object,Object);
extern Object make_color_map_structure_1(Object,Object,Object,Object,Object);
extern Object make_corresponding_icp_gensym_window(Object);
extern Object make_gensym_list_1(Object);
extern Object make_gensym_window(Object);
extern Object make_gensym_window_internal_1(Object);
extern Object make_identified_drawing_activity(Object,Object,Object,Object,Object,Object);
extern Object make_identified_drawing_activity_1_1(Object,Object,Object,Object,Object,Object);
extern Object make_named_dynamic_extent_description(Object,Object,Object,Object,Object,Object,Object);
extern Object make_or_revise_window(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_permanent_color_map_structure_internal(void);
extern Object make_permanent_gensym_window_structure_internal(void);
extern Object make_permanent_identified_drawing_activity_structure_internal(void);
extern Object make_permanent_pixmap_structure_internal(void);
extern Object make_permanent_tiled_raster_structure_internal(void);
extern Object make_pixmap_1(Object,Object,Object,Object);
extern Object make_queue(void);
extern Object make_singleton_tile_array(Object,Object);
extern Object make_tile_arrays(Object,Object,Object,Object,Object,Object);
extern Object make_tiled_raster_1(void);
extern Object make_window_visible(Object);
extern Object map_to_black_or_white(Object);
extern Object map_to_color(Object);
extern Object map_to_color_value(Object);
extern Object map_to_color_value_1(Object);
extern Object maximum_window_height(Object);
extern Object maximum_window_width(Object);
extern Object maybe_update_remote_icp_version_info_for_version(Object,Object,Object);
extern Object memq_function(Object,Object);
extern Object mutate_gensym_plist(Object,Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object negotiate_telewindows_licensing(Object);
extern Object nms_note_menu_deletion(Object,Object);
extern Object nms_reclaim_menu_table(Object);
extern Object notify_user_at_console(int,...);
extern Object obtain_max_window_protocol(Object);
extern Object outstanding_color_map_count(void);
extern Object outstanding_gensym_window_count(void);
extern Object outstanding_identified_drawing_activity_count(void);
extern Object outstanding_pixmap_count(void);
extern Object outstanding_tiled_raster_count(void);
extern Object ping_drawing(Object);
extern Object pixmap_structure_memory_usage(void);
extern Object printing_window_p(Object);
extern Object push_optimized_constant(Object);
extern Object raster_dimensions_given_max_and_offset(Object,Object,Object,Object,Object,Object);
extern Object read_icp_boolean(void);
extern Object read_icp_color_map_using_function(void);
extern Object read_icp_corresponding_object_index(void);
extern Object read_icp_integer(void);
extern Object read_icp_list(void);
extern Object read_icp_unsigned_integer(void);
extern Object read_icp_unsigned_integer_qm(void);
extern Object reclaim_all_scaled_fonts(int,...);
extern Object reclaim_cached_structures_for_window(Object);
extern Object reclaim_color_map_1(Object);
extern Object reclaim_color_map_if_any(Object);
extern Object reclaim_contents_of_nms_menu_table(Object);
extern Object reclaim_default_pane_background_color_or_tiling_pattern(Object);
extern Object reclaim_gensym_cons_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_string(Object);
extern Object reclaim_gensym_tree_1(Object);
extern Object reclaim_gensym_tree_with_text_strings(Object);
extern Object reclaim_gensym_window_internal_1(Object);
extern Object reclaim_gensym_window_parameters_plist(Object);
extern Object reclaim_icp_object_map(Object,Object,Object);
extern Object reclaim_icp_object_map_for_gensym_window(Object);
extern Object reclaim_icp_port_entry(Object,Object,Object,Object);
extern Object reclaim_icp_port_entry_for_gensym_window(Object,Object);
extern Object reclaim_identified_drawing_activity_1_1(Object);
extern Object reclaim_irregular_size_stored_raster(Object,Object,Object,Object,Object);
extern Object reclaim_local_event_queue(Object);
extern Object reclaim_managed_array(Object);
extern Object reclaim_managed_simple_vector(Object);
extern Object reclaim_native_icons_table(Object);
extern Object reclaim_native_menu_table(Object);
extern Object reclaim_native_windows(Object);
extern Object reclaim_panes_in_window_if_g2(Object);
extern Object reclaim_pixmap(Object);
extern Object reclaim_pixmap_1_1(Object);
extern Object reclaim_stored_raster(Object,Object,Object,Object,Object,Object);
extern Object reclaim_stored_raster_1(Object,Object,Object,Object,Object,Object);
extern Object reclaim_tiled_raster(Object);
extern Object reclaim_tiled_raster_internal_1(Object);
extern Object reclaim_window_for_workstation(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object remove_identified_drawing_activity(Object,Object);
extern Object remove_twng_disconnect_callback(Object,Object);
extern Object remove_ui_property(Object,Object);
extern Object resumable_icp_pop(void);
extern Object resumable_icp_pop_list_if_end_marker(void);
extern Object resumable_icp_push(Object);
extern Object rgb_color_intensity(Object);
extern Object rgb_color_nearest_standard_color(Object);
extern Object rgb_color_p(Object);
extern Object rgb_color_value(Object);
extern Object rgb_color_value_qm(Object);
extern Object rgb_from_color(Object);
extern Object rgb_value_of_gensym_color(Object);
extern Object send_icp_begin_window_update(Object,Object,Object,Object,Object);
extern Object send_icp_define_gensym_window(Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_ping_drawing_reply(Object,Object);
extern Object send_icp_set_background_color_value(Object);
extern Object send_icp_set_telewindows_connection_license_info(Object,Object);
extern Object send_icp_set_transfer_mode(Object);
extern Object send_icp_set_window_license_level(Object,Object);
extern Object send_icp_set_window_protocol_version(Object,Object);
extern Object send_ping_drawing_reply(Object,Object);
extern Object set_access_form_for_gensym_window(Object,Object);
extern Object set_current_background_color_value(Object);
extern Object set_gensym_window_parameter(Object,Object,Object);
extern Object set_icp_object_index_for_gensym_window(Object,Object,Object);
extern Object set_ui_property(Object,Object,Object);
extern Object set_up_palette(Object,Object);
extern Object set_v5_mode_state(Object);
extern Object slave_gensym_window_qm(Object);
extern Object start_identified_drawing_activity(int,...);
extern Object start_writing_icp_message(Object);
extern Object store_corresponding_icp_object(Object,Object);
extern Object stored_raster_in_regular_pool_qm(Object,Object,Object,Object);
extern Object sync_graphics_on_current_window(void);
extern Object sync_graphics_on_native_window(Object);
extern Object sync_graphics_on_native_window_1(Object);
extern Object synchronize_background_color_value(void);
extern Object synchronize_icp_on_window_with_drawing(Object,Object,Object,Object,Object);
extern Object synchronize_transfer_mode(void);
extern Object tiled_raster_structure_memory_usage(void);
extern Object time_to_decache_p(Object);
extern Object transfer_region_to_smaller_raster(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object twrite_color(Object);
extern Object twrite_symbol(int,...);
extern Object update_indexed_md5_context(Object,Object);
extern Object update_object_pool_meters_list(Object);
extern Object update_window(int,...);
extern Object v5_mode_option_specified_p(void);
extern Object window_supports_request_for_paste_availability_function(Object);
extern Object workstation_dead_p(Object);
extern Object write_icp_boolean(Object);
extern Object write_icp_color_map_using_function(Object);
extern Object write_icp_corresponding_object_index(Object);
extern Object write_icp_integer(Object);
extern Object write_icp_list(Object);
extern Object write_icp_maybe_suspend(void);
extern Object write_icp_unsigned_integer(Object);
extern Object write_icp_unsigned_integer_qm(Object);

#else

extern Object add_icp_message_handler();
extern Object add_icp_message_type_code();
extern Object add_twng_disconnect_callback();
extern Object allocate_bigger_stored_raster();
extern Object allocate_just_tiled_raster();
extern Object allocate_managed_array();
extern Object allocate_scratchpad_raster();
extern Object allocate_small_2d_array();
extern Object allocate_stored_raster();
extern Object allocate_stored_raster_1();
extern Object allocate_tiled_raster();
extern Object assign_corresponding_icp_object_index();
extern Object beep_in_window_1();
extern Object bitmap_memory_used();
extern Object block_pending_activity();
extern Object bytes_per_simple_vector();
extern Object cancel_list_of_pending_activity();
extern Object canonical_color_name();
extern Object change_icp_window_protocol_version();
extern Object clear_all_image_renderings_for_window();
extern Object clear_optimized_constants();
extern Object clear_stored_raster();
extern Object clear_twng_disconnect_callbacks();
extern Object close_native_window();
extern Object color_map_structure_memory_usage();
extern Object compute_rows_columns_given_tile_size();
extern Object compute_standard_gensym_colors();
extern Object compute_tile_size_given_required_area();
extern Object convert_current_scratchpad_raster_to_stored_raster();
extern Object convert_raster_sizes_to_memory_used();
extern Object copy_foreign_string_arg_if_appropriate();
extern Object copy_gensym_tree_with_text_strings();
extern Object copy_gensym_window_parameters_plist();
extern Object copy_tree_using_gensym_conses_1();
extern Object create_stored_raster();
extern Object debug_x11();
extern Object decode_icp_window_protocol_version();
extern Object default_value_for_image_palette();
extern Object delete_gensym_element_1();
extern Object derive_standard_gensym_color_data();
extern Object dialog_units_to_pixels();
extern Object direct_structure_method();
extern Object emit_icp_read_trace();
extern Object emit_icp_write_trace();
extern Object end_icp_message_group();
extern Object enlarge_index_space();
extern Object enqueue_window_reshape_event();
extern Object establish_new_object_index_for_gensym_window();
extern Object establish_telewindows_license_level();
extern Object finalize_indexed_md5_context();
extern Object find_gensym_window_with_session_id();
extern Object find_identified_drawing_activity();
extern Object find_irregular_size_stored_raster();
extern Object find_nearest_color();
extern Object finish_pending_activity();
extern Object flush_graphics_on_current_window();
extern Object flush_graphics_on_native_window();
extern Object force_graphics_on_window();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object gensym_list_4();
extern Object gensym_window_has_not_been_reprocessed_p();
extern Object gensym_window_host_name();
extern Object gensym_window_os_type();
extern Object gensym_window_session_id();
extern Object gensym_window_structure_memory_usage();
extern Object get_command_line_flag_argument();
extern Object get_event_queue_of_native_window();
extern Object get_from_icp_port();
extern Object get_g2_license_level();
extern Object get_gensym_window_of_native_window();
extern Object get_gensym_window_parameter();
extern Object get_gensym_window_reshape_event_queue();
extern Object get_icp_object_index_for_gensym_window();
extern Object get_local_host_name();
extern Object get_paste_event_queue_of_native_window();
extern Object get_reshape_event_queue_of_native_window();
extern Object get_system_metric();
extern Object get_ui_property();
extern Object getfq_function_no_default();
extern Object global_paint_mode_p();
extern Object handle_icp_define_gensym_window();
extern Object handle_icp_define_gensym_window__body();
extern Object handle_icp_force_graphics_on_window();
extern Object handle_icp_initialize_scratchpad_raster();
extern Object handle_icp_ping_drawing();
extern Object handle_icp_ping_drawing_reply();
extern Object handle_icp_ping_drawing_reply__body();
extern Object handle_icp_set_up_palette();
extern Object handle_no_solution_to_raster_allocation_failure();
extern Object handle_ping_drawing_reply_1();
extern Object hard_reclaim_all_irregular_size_reclaimed_stored_rasters();
extern Object hard_reclaim_all_reclaimed_stored_rasters();
extern Object hard_reclaim_all_regular_size_reclaimed_stored_rasters();
extern Object hue_less_p();
extern Object hue_saturation_value();
extern Object icon_bitmap_memory_used();
extern Object icp_connection_being_shutdown_qm();
extern Object icp_connection_open_p();
extern Object icp_error_internal();
extern Object icp_message_functions_icp_prologue();
extern Object icp_prologue_send_begin_window_update();
extern Object icp_prologue_set_background_color_value();
extern Object icp_prologue_set_transfer_mode();
extern Object icp_socket_for_gensym_window_qm();
extern Object icp_socket_number_of_outstanding_bytes();
extern Object identified_drawing_activity_structure_memory_usage();
extern Object increment_current_gensym_window_serial_number();
extern Object initialize_gensym_window_after_connection();
extern Object initialize_icp_object_type();
extern Object initialize_icp_object_type_compile();
extern Object initialize_image_palette_of_new_gensym_window();
extern Object initialize_scratchpad_raster();
extern Object initialize_v5_mode();
extern Object instantaneous_icp_reader_byte_count();
extern Object instantaneous_icp_writer_byte_count();
extern Object load_and_initialize_type_description();
extern Object make_color_map();
extern Object make_color_map_structure_1();
extern Object make_corresponding_icp_gensym_window();
extern Object make_gensym_list_1();
extern Object make_gensym_window();
extern Object make_gensym_window_internal_1();
extern Object make_identified_drawing_activity();
extern Object make_identified_drawing_activity_1_1();
extern Object make_named_dynamic_extent_description();
extern Object make_or_revise_window();
extern Object make_permanent_color_map_structure_internal();
extern Object make_permanent_gensym_window_structure_internal();
extern Object make_permanent_identified_drawing_activity_structure_internal();
extern Object make_permanent_pixmap_structure_internal();
extern Object make_permanent_tiled_raster_structure_internal();
extern Object make_pixmap_1();
extern Object make_queue();
extern Object make_singleton_tile_array();
extern Object make_tile_arrays();
extern Object make_tiled_raster_1();
extern Object make_window_visible();
extern Object map_to_black_or_white();
extern Object map_to_color();
extern Object map_to_color_value();
extern Object map_to_color_value_1();
extern Object maximum_window_height();
extern Object maximum_window_width();
extern Object maybe_update_remote_icp_version_info_for_version();
extern Object memq_function();
extern Object mutate_gensym_plist();
extern Object mutate_global_property();
extern Object negotiate_telewindows_licensing();
extern Object nms_note_menu_deletion();
extern Object nms_reclaim_menu_table();
extern Object notify_user_at_console();
extern Object obtain_max_window_protocol();
extern Object outstanding_color_map_count();
extern Object outstanding_gensym_window_count();
extern Object outstanding_identified_drawing_activity_count();
extern Object outstanding_pixmap_count();
extern Object outstanding_tiled_raster_count();
extern Object ping_drawing();
extern Object pixmap_structure_memory_usage();
extern Object printing_window_p();
extern Object push_optimized_constant();
extern Object raster_dimensions_given_max_and_offset();
extern Object read_icp_boolean();
extern Object read_icp_color_map_using_function();
extern Object read_icp_corresponding_object_index();
extern Object read_icp_integer();
extern Object read_icp_list();
extern Object read_icp_unsigned_integer();
extern Object read_icp_unsigned_integer_qm();
extern Object reclaim_all_scaled_fonts();
extern Object reclaim_cached_structures_for_window();
extern Object reclaim_color_map_1();
extern Object reclaim_color_map_if_any();
extern Object reclaim_contents_of_nms_menu_table();
extern Object reclaim_default_pane_background_color_or_tiling_pattern();
extern Object reclaim_gensym_cons_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_string();
extern Object reclaim_gensym_tree_1();
extern Object reclaim_gensym_tree_with_text_strings();
extern Object reclaim_gensym_window_internal_1();
extern Object reclaim_gensym_window_parameters_plist();
extern Object reclaim_icp_object_map();
extern Object reclaim_icp_object_map_for_gensym_window();
extern Object reclaim_icp_port_entry();
extern Object reclaim_icp_port_entry_for_gensym_window();
extern Object reclaim_identified_drawing_activity_1_1();
extern Object reclaim_irregular_size_stored_raster();
extern Object reclaim_local_event_queue();
extern Object reclaim_managed_array();
extern Object reclaim_managed_simple_vector();
extern Object reclaim_native_icons_table();
extern Object reclaim_native_menu_table();
extern Object reclaim_native_windows();
extern Object reclaim_panes_in_window_if_g2();
extern Object reclaim_pixmap();
extern Object reclaim_pixmap_1_1();
extern Object reclaim_stored_raster();
extern Object reclaim_stored_raster_1();
extern Object reclaim_tiled_raster();
extern Object reclaim_tiled_raster_internal_1();
extern Object reclaim_window_for_workstation();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object remove_identified_drawing_activity();
extern Object remove_twng_disconnect_callback();
extern Object remove_ui_property();
extern Object resumable_icp_pop();
extern Object resumable_icp_pop_list_if_end_marker();
extern Object resumable_icp_push();
extern Object rgb_color_intensity();
extern Object rgb_color_nearest_standard_color();
extern Object rgb_color_p();
extern Object rgb_color_value();
extern Object rgb_color_value_qm();
extern Object rgb_from_color();
extern Object rgb_value_of_gensym_color();
extern Object send_icp_begin_window_update();
extern Object send_icp_define_gensym_window();
extern Object send_icp_ping_drawing_reply();
extern Object send_icp_set_background_color_value();
extern Object send_icp_set_telewindows_connection_license_info();
extern Object send_icp_set_transfer_mode();
extern Object send_icp_set_window_license_level();
extern Object send_icp_set_window_protocol_version();
extern Object send_ping_drawing_reply();
extern Object set_access_form_for_gensym_window();
extern Object set_current_background_color_value();
extern Object set_gensym_window_parameter();
extern Object set_icp_object_index_for_gensym_window();
extern Object set_ui_property();
extern Object set_up_palette();
extern Object set_v5_mode_state();
extern Object slave_gensym_window_qm();
extern Object start_identified_drawing_activity();
extern Object start_writing_icp_message();
extern Object store_corresponding_icp_object();
extern Object stored_raster_in_regular_pool_qm();
extern Object sync_graphics_on_current_window();
extern Object sync_graphics_on_native_window();
extern Object sync_graphics_on_native_window_1();
extern Object synchronize_background_color_value();
extern Object synchronize_icp_on_window_with_drawing();
extern Object synchronize_transfer_mode();
extern Object tiled_raster_structure_memory_usage();
extern Object time_to_decache_p();
extern Object transfer_region_to_smaller_raster();
extern Object twrite_color();
extern Object twrite_symbol();
extern Object update_indexed_md5_context();
extern Object update_object_pool_meters_list();
extern Object update_window();
extern Object v5_mode_option_specified_p();
extern Object window_supports_request_for_paste_availability_function();
extern Object workstation_dead_p();
extern Object write_icp_boolean();
extern Object write_icp_color_map_using_function();
extern Object write_icp_corresponding_object_index();
extern Object write_icp_integer();
extern Object write_icp_list();
extern Object write_icp_maybe_suspend();
extern Object write_icp_unsigned_integer();
extern Object write_icp_unsigned_integer_qm();

#endif

/* variables/constants */
extern Object Abort_for_icp_catcher_qm;
extern Object All_colors;
extern Object All_metacolors;
extern Object Available_gensym_conses;
extern Object Backtrace_stack_for_internal_error;
extern Object Bottom_edge_of_draw_area;
extern Object Cache_al_semantics_graph;
extern Object Cache_chinese_semantics_graph;
extern Object Cache_ent_semantics_graph;
extern Object Cache_g1_semantics_graph;
extern Object Cache_gfi_semantics_graph;
extern Object Cache_gsi_semantics_graph;
extern Object Cache_icp_semantics_graph;
extern Object Cache_japanese_semantics_graph;
extern Object Cache_jl_semantics_graph;
extern Object Cache_jp_semantics_graph;
extern Object Cache_korean_semantics_graph;
extern Object Cache_nupec_semantics_graph;
extern Object Chain_of_available_color_maps;
extern Object Chain_of_available_gensym_windows;
extern Object Chain_of_available_identified_drawing_activitys;
extern Object Chain_of_available_pixmaps;
extern Object Chain_of_available_tiled_rasters;
extern Object Color_map_count;
extern Object Color_value_vector_index_and_intensity_prop;
extern Object Command_line_arguments;
extern Object Current_background_color_value;
extern Object Current_color_map;
extern Object Current_draw_document_p;
extern Object Current_draw_paper_p;
extern Object Current_drawing_priority;
extern Object Current_drawing_transfer_mode;
extern Object Current_foreground_color_value;
extern Object Current_gensym_window_serial_number;
extern Object Current_icp_buffer;
extern Object Current_icp_port;
extern Object Current_icp_read_trace_level;
extern Object Current_icp_socket;
extern Object Current_icp_write_trace_level;
extern Object Current_image_x_scale;
extern Object Current_image_y_scale;
extern Object Current_native_window_qm;
extern Object Current_pane;
extern Object Current_scratchpad_color_value_list;
extern Object Current_scratchpad_raster;
extern Object Current_scratchpad_raster_depth;
extern Object Current_scratchpad_raster_height;
extern Object Current_scratchpad_raster_list;
extern Object Current_scratchpad_raster_tiled_p;
extern Object Current_scratchpad_raster_type;
extern Object Current_scratchpad_raster_width;
extern Object Current_standard_icp_object_index_space;
extern Object Current_system_name;
extern Object Current_temporary_icp_object_index_space;
extern Object Current_window;
extern Object Current_write_icp_byte_position;
extern Object Current_x_max_for_stored_raster_qm;
extern Object Current_x_offset_for_stored_raster_qm;
extern Object Current_x_origin_of_drawing;
extern Object Current_y_max_for_stored_raster_qm;
extern Object Current_y_offset_for_stored_raster_qm;
extern Object Current_y_origin_of_drawing;
extern Object Currently_jump_out_of_drawing_image_plane_when_empty_rectangle_p;
extern Object Deepest_depth;
extern Object Default_image_palette;
extern Object Default_maximum_icon_bitmap_memory;
extern Object Default_maximum_icon_bitmaps;
extern Object Defer_notifications_qm;
extern Object Delete_corresponding_object_qm;
extern Object Disable_resumability;
extern Object Do_icp_flow_control_qm;
extern Object Do_not_error_in_x11_create_pixmap_on_failed_allocation;
extern Object Drawing_on_window;
extern Object Edit_type_alias_mapping;
extern Object Flush_graphics_immediately_qm;
extern Object G2_has_v5_mode_windows_p;
extern Object G2_operating_system;
extern Object Gensym_window_count;
extern Object Get_object_on_kb_workspace_for_item;
extern Object Gfi_list_of_converters;
extern Object Icp_buffer_of_start_of_message_series_qm;
extern Object Icp_buffers_for_message_group;
extern Object Icp_byte_position_of_start_of_message_series_qm;
extern Object Icp_connection_closed;
extern Object Icp_printing_message_handler_array;
extern Object Icp_read_trace_cutoff_level_qm;
extern Object Icp_suspend;
#define Icp_window_protocol_supports_floating_telewindows FIX((SI_Long)6L)
#define Icp_window_protocol_supports_request_for_paste_availability FIX((SI_Long)20L)
#define Icp_window_protocol_supports_setting_protocol_level FIX((SI_Long)4L)
#define Icp_window_protocol_supports_telewindows_connection_license_info FIX((SI_Long)9L)
#define Icp_window_protocol_supports_transparent_copy FIX((SI_Long)3L)
#define Icp_window_protocol_supports_unicode_character_events FIX((SI_Long)21L)
extern Object Icp_write_trace_cutoff_level_qm;
extern Object Identified_drawing_activity_count;
extern Object Index_of_open_windows;
extern Object Index_of_top_of_backtrace_stack;
extern Object Inhibit_corresponding_icp_object_making;
extern Object Initialize_gensym_window_after_connection_done;
extern Object Journal_shutout_scan_p;
extern Object Largest_regular_raster_size;
extern Object Largest_regular_raster_size_index;
extern Object Latest_icp_window_protocol_version;
extern Object Left_edge_of_draw_area;
extern Object List_of_regular_raster_memory_usage;
extern Object List_of_regular_raster_sizes;
extern Object Listed_continuation_servers;
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
#define Maximum_managed_simple_vector_size FIX((SI_Long)1024L)
extern Object Menu_colors;
extern Object Menu_colors_sorted_alphabetically;
extern Object Menu_colors_sorted_by_hue;
extern Object Minimum_index_for_icons;
#define Minimum_intensity_for_white FIX((SI_Long)192L)
extern Object Minimum_tile_size_for_icons;
extern Object Native_menu_table;
extern Object New_pastel_color_qm_prop;
extern Object No_arg;
extern Object Number_of_icp_bytes_for_message_series;
extern Object Number_of_icp_bytes_in_message_group;
extern Object Number_of_icp_bytes_to_fill_buffer;
extern Object Number_of_regular_raster_sizes;
extern Object On_monochrome_raster_list_p;
extern Object Optional_modules_map;
#define Original_icp_window_protocol_version FIX((SI_Long)0L)
extern Object Overflow_byte_count;
extern Object Paint_only_target_monochrome_raster_p;
extern Object Pixmap_count;
extern Object Pop_fonts_stack;
extern Object Popup_frames_available;
extern Object Prefer_to_hard_reclaim_irregular_sized_rasters_p;
extern Object Radio_button_status_flags;
extern Object Radio_button_status_flags_1;
extern Object Reclaim_fonts_stack;
extern Object Region_and_tile_x_offset;
extern Object Region_and_tile_y_offset;
extern Object Resumable_icp_state;
extern Object Rgb_color_intensity_cache_prop;
extern Object Rgb_color_nearest_standard_color_cache_prop;
extern Object Rgb_color_value_cache_prop;
extern Object Right_edge_of_draw_area;
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
#define Sm_cxdialog FIX((SI_Long)82L)
#define Sm_cxframe FIX((SI_Long)32L)
#define Sm_cxmaxtrack FIX((SI_Long)59L)
#define Sm_cycaption FIX((SI_Long)4L)
#define Sm_cydialog FIX((SI_Long)83L)
#define Sm_cyframe FIX((SI_Long)33L)
#define Sm_cymaxtrack FIX((SI_Long)60L)
extern Object Standard_gensym_color_alist;
extern Object Structure_being_reclaimed;
extern Object System_window;
extern Object The_type_description_of_color_map;
extern Object The_type_description_of_gensym_window;
extern Object The_type_description_of_identified_drawing_activity;
extern Object The_type_description_of_pixmap;
extern Object The_type_description_of_tiled_raster;
extern Object Tiled_raster_count;
extern Object Top_edge_of_draw_area;
extern Object Trace_image_planes_p;
extern Object Type_of_current_window;
extern Object Workspace_for_current_draw_document_qm;
extern Object Workstations_in_service;
extern Object Writing_icp_message_group;
extern Object Writing_resumable_icp_messages_p;
extern Object X_debugging_on;
