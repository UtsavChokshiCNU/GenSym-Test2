/* win2.h -- Header File for win2.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qerror;

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
extern Object assign_corresponding_icp_object_index(Object,Object,Object);
extern Object assq_function(Object,Object);
extern Object bytes_per_simple_vector(Object);
extern Object c_x11_pfill_clipped_polygon(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object calculate_bounds_of_unsigned_point_list(Object);
extern Object calculate_center_and_radius_of_circle(Object,Object,Object,Object,Object,Object);
extern Object calculate_center_of_circle(Object,Object,Object,Object,Object,Object);
extern Object chestnut_floorf_function(Object,Object);
extern Object circle_convert_float_to_integer(Object,Object);
extern Object clear_optimized_constants(void);
extern Object clear_stored_raster(Object,Object,Object,Object);
extern Object clockwise_arc_qm(Object,Object,Object,Object,Object,Object);
extern Object combine_x_and_y_coordinates(Object,Object);
extern Object compute_arc_bounding_box(Object,Object,Object,Object,Object,Object);
extern Object compute_circle_bounding_box(Object,Object,Object,Object,Object,Object);
extern Object compute_float_circle_radius(Object,Object,Object,Object);
extern Object convert_current_scratchpad_raster_to_stored_raster(Object,Object,Object,Object,Object);
extern Object copy_tree_using_gensym_conses_1(Object);
extern Object direct_structure_method(Object,Object);
extern Object emit_icp_read_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_write_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object enlarge_index_space(Object,Object);
extern Object establish_new_object_index_for_tiling_pattern(int,...);
extern Object fill_polygon_data_buffer_from_unsigned_point_list(Object);
extern Object fill_rectangle_on_scratchpad_raster(Object,Object,Object,Object,Object,Object,Object);
extern Object fill_rectangle_on_scratchpad_raster_1(Object,Object,Object,Object,Object,Object,Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_probe_file_for_truth_value(Object);
extern Object get_background_color_for_symbol(Object);
extern Object get_background_color_or_tiling_pattern(void);
extern Object get_background_color_or_tiling_pattern_from_command_line(void);
extern Object get_icp_object_index_for_tiling_pattern(Object,Object);
extern Object get_tiling_pattern(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object graphics_cons_1(Object,Object);
extern Object handle_icp_make_tiling_pattern(void);
extern Object handle_icp_make_tiling_pattern__body(Object,Object,Object);
extern Object handle_icp_paint_arc_or_circle_in_current_scratchpad_raster(void);
extern Object handle_icp_paint_clearing_rectangle_in_current_scratchpad_raster(void);
extern Object handle_icp_paint_filled_polygon_in_current_scratchpad_raster(void);
extern Object handle_icp_paint_filled_triangle_in_current_scratchpad_raster(void);
extern Object handle_icp_paint_line_in_current_scratchpad_raster(void);
extern Object handle_icp_paint_point_in_current_scratchpad_raster(void);
extern Object handle_icp_paint_solid_rectangle_in_current_scratchpad_raster(void);
extern Object handle_icp_paint_wide_line_in_current_scratchpad_raster(void);
extern Object handle_icp_stipple_rectangle_in_current_scratchpad_raster(void);
extern Object icp_error_internal(Object,Object,Object,Object,Object);
extern Object icp_message_functions_icp_prologue(Object);
extern Object initialize_icp_object_type(Object,Object,Object,Object);
extern Object initialize_icp_object_type_compile(Object,Object,Object);
extern Object initialize_scratchpad_raster(Object,Object,Object,Object,Object);
extern Object install_tiling_pattern(Object);
extern Object instantaneous_icp_reader_byte_count(void);
extern Object instantaneous_icp_writer_byte_count(void);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_and_install_tiling_pattern(Object,Object);
extern Object make_corresponding_icp_gensym_window(Object);
extern Object make_corresponding_icp_symbol(Object);
extern Object make_corresponding_icp_tiling_pattern(Object);
extern Object make_permanent_tiling_pattern_structure_internal(void);
extern Object make_thread_array(Object);
extern Object make_tiling_pattern(Object,Object);
extern Object make_tiling_pattern_structure_1(Object,Object,Object,Object,Object);
extern Object map_to_color_value(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object notify_user_at_console(int,...);
extern Object obtain_simple_gensym_string(Object);
extern Object outstanding_tiling_pattern_count(void);
extern Object paint_arc_or_circle_in_current_scratchpad_raster(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object paint_arc_or_circle_in_current_scratchpad_raster_1(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object paint_arc_or_circle_in_current_scratchpad_raster_2(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object paint_clearing_rectangle_in_current_scratchpad_raster(Object,Object,Object,Object,Object);
extern Object paint_filled_polygon_in_current_scratchpad_raster(Object,Object);
extern Object paint_filled_triangle_in_current_scratchpad_raster(Object,Object,Object,Object,Object,Object,Object);
extern Object paint_line_in_current_scratchpad_raster(Object,Object,Object,Object,Object,Object);
extern Object paint_point_in_current_scratchpad_raster(Object,Object,Object);
extern Object paint_solid_rectangle_in_current_scratchpad_raster(Object,Object,Object,Object,Object);
extern Object paint_wide_line_in_current_scratchpad_raster(Object,Object,Object,Object,Object,Object,Object);
extern Object paint_wide_line_in_current_scratchpad_raster_1(Object,Object,Object,Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object quadrant_of_point(Object,Object);
extern Object read_icp_boolean(void);
extern Object read_icp_corresponding_object_index(void);
extern Object read_icp_integer(void);
extern Object read_icp_tiling_pattern_rows_with_color_values(void);
extern Object read_icp_unsigned_integer(void);
extern Object read_raster(int,...);
extern Object reclaim_default_pane_background_color_or_tiling_pattern(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_tree_1(Object);
extern Object reclaim_graphics_list_1(Object);
extern Object reclaim_graphics_tree_1(Object);
extern Object reclaim_icp_object_map(Object,Object,Object);
extern Object reclaim_icp_object_map_for_tiling_pattern(Object);
extern Object reclaim_icp_port_entry(Object,Object,Object,Object);
extern Object reclaim_icp_port_entry_for_tiling_pattern(Object,Object);
extern Object reclaim_shredded_raster(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_tiling_pattern_1(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object replenish_gensym_cons_pool(void);
extern Object resumable_icp_pop(void);
extern Object resumable_icp_pop_list_if_end_marker(void);
extern Object resumable_icp_push(Object);
extern Object rgb_from_color(Object);
extern Object scalef_function(Object,Object);
extern Object send_icp_make_tiling_pattern(Object,Object,Object);
extern Object separate_x_y_coordinates(Object);
extern Object set_access_form_for_tiling_pattern(Object,Object);
extern Object set_icp_object_index_for_tiling_pattern(Object,Object,Object);
extern Object shredded_raster_to_background_tile(Object);
extern Object start_writing_icp_message(Object);
extern Object stipple_rectangle_in_current_scratchpad_raster(Object,Object,Object,Object,Object,Object);
extern Object stipple_rectangle_in_scratchpad_raster(Object,Object,Object,Object,Object,Object,Object);
extern Object stipple_rectangle_in_scratchpad_raster_1(Object,Object,Object,Object,Object,Object,Object);
extern Object store_corresponding_icp_object(Object,Object);
extern Object telewindows_check_version_of_remote_g2(Object);
extern Object telewindows_mdi_frame_p(void);
extern Object text_string_p(Object);
extern Object tiling_pattern_structure_memory_usage(void);
extern Object transfer_region_to_smaller_raster(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object update_object_pool_meters_list(Object);
extern Object write_icp_boolean(Object);
extern Object write_icp_corresponding_object_index(Object);
extern Object write_icp_integer(Object);
extern Object write_icp_list_of_unsigned_integers(Object);
extern Object write_icp_maybe_suspend(void);
extern Object write_icp_tiling_pattern_rows_with_color_values(Object);
extern Object write_icp_unsigned_integer(Object);

#else

extern Object add_icp_message_handler();
extern Object assign_corresponding_icp_object_index();
extern Object assq_function();
extern Object bytes_per_simple_vector();
extern Object c_x11_pfill_clipped_polygon();
extern Object calculate_bounds_of_unsigned_point_list();
extern Object calculate_center_and_radius_of_circle();
extern Object calculate_center_of_circle();
extern Object chestnut_floorf_function();
extern Object circle_convert_float_to_integer();
extern Object clear_optimized_constants();
extern Object clear_stored_raster();
extern Object clockwise_arc_qm();
extern Object combine_x_and_y_coordinates();
extern Object compute_arc_bounding_box();
extern Object compute_circle_bounding_box();
extern Object compute_float_circle_radius();
extern Object convert_current_scratchpad_raster_to_stored_raster();
extern Object copy_tree_using_gensym_conses_1();
extern Object direct_structure_method();
extern Object emit_icp_read_trace();
extern Object emit_icp_write_trace();
extern Object enlarge_index_space();
extern Object establish_new_object_index_for_tiling_pattern();
extern Object fill_polygon_data_buffer_from_unsigned_point_list();
extern Object fill_rectangle_on_scratchpad_raster();
extern Object fill_rectangle_on_scratchpad_raster_1();
extern Object gensym_cons_1();
extern Object gensym_probe_file_for_truth_value();
extern Object get_background_color_for_symbol();
extern Object get_background_color_or_tiling_pattern();
extern Object get_background_color_or_tiling_pattern_from_command_line();
extern Object get_icp_object_index_for_tiling_pattern();
extern Object get_tiling_pattern();
extern Object getfq_function_no_default();
extern Object graphics_cons_1();
extern Object handle_icp_make_tiling_pattern();
extern Object handle_icp_make_tiling_pattern__body();
extern Object handle_icp_paint_arc_or_circle_in_current_scratchpad_raster();
extern Object handle_icp_paint_clearing_rectangle_in_current_scratchpad_raster();
extern Object handle_icp_paint_filled_polygon_in_current_scratchpad_raster();
extern Object handle_icp_paint_filled_triangle_in_current_scratchpad_raster();
extern Object handle_icp_paint_line_in_current_scratchpad_raster();
extern Object handle_icp_paint_point_in_current_scratchpad_raster();
extern Object handle_icp_paint_solid_rectangle_in_current_scratchpad_raster();
extern Object handle_icp_paint_wide_line_in_current_scratchpad_raster();
extern Object handle_icp_stipple_rectangle_in_current_scratchpad_raster();
extern Object icp_error_internal();
extern Object icp_message_functions_icp_prologue();
extern Object initialize_icp_object_type();
extern Object initialize_icp_object_type_compile();
extern Object initialize_scratchpad_raster();
extern Object install_tiling_pattern();
extern Object instantaneous_icp_reader_byte_count();
extern Object instantaneous_icp_writer_byte_count();
extern Object load_and_initialize_type_description();
extern Object make_and_install_tiling_pattern();
extern Object make_corresponding_icp_gensym_window();
extern Object make_corresponding_icp_symbol();
extern Object make_corresponding_icp_tiling_pattern();
extern Object make_permanent_tiling_pattern_structure_internal();
extern Object make_thread_array();
extern Object make_tiling_pattern();
extern Object make_tiling_pattern_structure_1();
extern Object map_to_color_value();
extern Object mutate_global_property();
extern Object notify_user_at_console();
extern Object obtain_simple_gensym_string();
extern Object outstanding_tiling_pattern_count();
extern Object paint_arc_or_circle_in_current_scratchpad_raster();
extern Object paint_arc_or_circle_in_current_scratchpad_raster_1();
extern Object paint_arc_or_circle_in_current_scratchpad_raster_2();
extern Object paint_clearing_rectangle_in_current_scratchpad_raster();
extern Object paint_filled_polygon_in_current_scratchpad_raster();
extern Object paint_filled_triangle_in_current_scratchpad_raster();
extern Object paint_line_in_current_scratchpad_raster();
extern Object paint_point_in_current_scratchpad_raster();
extern Object paint_solid_rectangle_in_current_scratchpad_raster();
extern Object paint_wide_line_in_current_scratchpad_raster();
extern Object paint_wide_line_in_current_scratchpad_raster_1();
extern Object push_optimized_constant();
extern Object quadrant_of_point();
extern Object read_icp_boolean();
extern Object read_icp_corresponding_object_index();
extern Object read_icp_integer();
extern Object read_icp_tiling_pattern_rows_with_color_values();
extern Object read_icp_unsigned_integer();
extern Object read_raster();
extern Object reclaim_default_pane_background_color_or_tiling_pattern();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_tree_1();
extern Object reclaim_graphics_list_1();
extern Object reclaim_graphics_tree_1();
extern Object reclaim_icp_object_map();
extern Object reclaim_icp_object_map_for_tiling_pattern();
extern Object reclaim_icp_port_entry();
extern Object reclaim_icp_port_entry_for_tiling_pattern();
extern Object reclaim_shredded_raster();
extern Object reclaim_text_string();
extern Object reclaim_tiling_pattern_1();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object replenish_gensym_cons_pool();
extern Object resumable_icp_pop();
extern Object resumable_icp_pop_list_if_end_marker();
extern Object resumable_icp_push();
extern Object rgb_from_color();
extern Object scalef_function();
extern Object send_icp_make_tiling_pattern();
extern Object separate_x_y_coordinates();
extern Object set_access_form_for_tiling_pattern();
extern Object set_icp_object_index_for_tiling_pattern();
extern Object shredded_raster_to_background_tile();
extern Object start_writing_icp_message();
extern Object stipple_rectangle_in_current_scratchpad_raster();
extern Object stipple_rectangle_in_scratchpad_raster();
extern Object stipple_rectangle_in_scratchpad_raster_1();
extern Object store_corresponding_icp_object();
extern Object telewindows_check_version_of_remote_g2();
extern Object telewindows_mdi_frame_p();
extern Object text_string_p();
extern Object tiling_pattern_structure_memory_usage();
extern Object transfer_region_to_smaller_raster();
extern Object update_object_pool_meters_list();
extern Object write_icp_boolean();
extern Object write_icp_corresponding_object_index();
extern Object write_icp_integer();
extern Object write_icp_list_of_unsigned_integers();
extern Object write_icp_maybe_suspend();
extern Object write_icp_tiling_pattern_rows_with_color_values();
extern Object write_icp_unsigned_integer();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Abort_for_icp_catcher_qm, Qabort_for_icp_catcher_qm);
extern Object All_stipples;
extern Object Available_gensym_conses_tail_vector;
extern Object Available_gensym_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Available_tiling_patterns, Qavailable_tiling_patterns);
DECLARE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_tiling_patterns, Qchain_of_available_tiling_patterns);
extern Object Chain_of_available_tiling_patterns_vector;
extern Object Command_line_arguments;
DECLARE_VARIABLE_WITH_SYMBOL(Current_color_map, Qcurrent_color_map);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_port, Qcurrent_icp_port);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_read_trace_level, Qcurrent_icp_read_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_write_trace_level, Qcurrent_icp_write_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_color_value_list, Qcurrent_scratchpad_color_value_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster, Qcurrent_scratchpad_raster);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_depth, Qcurrent_scratchpad_raster_depth);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_height, Qcurrent_scratchpad_raster_height);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_list, Qcurrent_scratchpad_raster_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_tiled_p, Qcurrent_scratchpad_raster_tiled_p);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_type, Qcurrent_scratchpad_raster_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_width, Qcurrent_scratchpad_raster_width);
DECLARE_VARIABLE_WITH_SYMBOL(Current_standard_icp_object_index_space, Qcurrent_standard_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_system_name, Qcurrent_system_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_temporary_icp_object_index_space, Qcurrent_temporary_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_x_max_for_stored_raster_qm, Qcurrent_x_max_for_stored_raster_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_x_offset_for_stored_raster_qm, Qcurrent_x_offset_for_stored_raster_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_y_max_for_stored_raster_qm, Qcurrent_y_max_for_stored_raster_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_y_offset_for_stored_raster_qm, Qcurrent_y_offset_for_stored_raster_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Disable_resumability, Qdisable_resumability);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_printing_message_handler_array, Qicp_printing_message_handler_array);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_read_trace_cutoff_level_qm, Qicp_read_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_suspend, Qicp_suspend);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_write_trace_cutoff_level_qm, Qicp_write_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Inhibit_corresponding_icp_object_making, Qinhibit_corresponding_icp_object_making);
extern Object Isqrt_of_most_positive_fixnum;
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Map_to_stipple_value_prop;
extern Object Maximum_in_place_array_size;
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
extern Object Minus_of_isqrt_of_most_positive_fixnum;
#define No_stipple_value FIX((SI_Long)0L)
DECLARE_VARIABLE_WITH_SYMBOL(On_monochrome_raster_list_p, Qon_monochrome_raster_list_p);
DECLARE_VARIABLE_WITH_SYMBOL(Paint_only_target_monochrome_raster_p, Qpaint_only_target_monochrome_raster_p);
DECLARE_VARIABLE_WITH_SYMBOL(Region_and_tile_x_offset, Qregion_and_tile_x_offset);
DECLARE_VARIABLE_WITH_SYMBOL(Region_and_tile_y_offset, Qregion_and_tile_y_offset);
DECLARE_VARIABLE_WITH_SYMBOL(Resumable_icp_state, Qresumable_icp_state);
DECLARE_VARIABLE_WITH_SYMBOL(Scratchpad_raster, Qscratchpad_raster);
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
DECLARE_VARIABLE_WITH_SYMBOL(The_polygon_data_buffer, Qthe_polygon_data_buffer);
extern Object The_type_description_of_tiling_pattern;
extern Object Tiling_pattern_background_color;
DECLARE_VARIABLE_WITH_SYMBOL(Tiling_pattern_count, Qtiling_pattern_count);
extern Object Tiling_pattern_foreground_color;
DECLARE_VARIABLE_WITH_SYMBOL(Writing_resumable_icp_messages_p, Qwriting_resumable_icp_messages_p);
