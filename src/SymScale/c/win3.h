/* win3.h -- Header File for win3.c
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

extern Object accumulate_thrashing_cost_and_decache(Object,Object,Object,Object);
extern Object add_downward_sloping_line_to_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object add_ellipse_to_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object add_from_icon_rendering_to_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object add_icp_message_handler(Object,Object);
extern Object add_polygon_to_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object add_solid_rectangle_to_current_window(Object,Object,Object,Object,Object,Object);
extern Object add_upward_sloping_line_to_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object add_wide_polyline_to_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_offscreen_pixmap(Object,Object,Object,Object);
extern Object assign_corresponding_icp_object_index(Object,Object,Object);
extern Object bitblt_offscreen_bitmap(Object);
extern Object bytes_per_simple_vector(Object);
extern Object c_x11_draw_polygon(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_x11_draw_wide_polyline(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object clear_optimized_constants(void);
extern Object compute_cost_of_decaching_icon_rendering(Object);
extern Object compute_size_of_icon_rendering(Object);
extern Object compute_size_of_icon_rendering_1(Object,Object);
extern Object compute_true_size_of_icon_rendering(Object);
extern Object compute_true_size_of_icon_rendering_1(Object,Object);
extern Object convert_current_scratchpad_raster_to_stored_raster(Object,Object,Object,Object,Object);
extern Object copy_from_tiling_pattern_to_current_window(Object,Object,Object,Object,Object);
extern Object copy_managed_float(Object);
extern Object copy_text_string(Object);
extern Object copy_tree_including_leaves_using_gensym_conses(Object);
extern Object decache_icon_rendering(Object);
extern Object delete_icon_rendering_and_reclaim_icp_index(Object);
extern Object direct_structure_method(Object,Object);
extern Object draw_ellipse_on_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object draw_offscreen(Object,Object,Object,Object,Object);
extern Object draw_polygon_on_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object draw_wide_polyline_on_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_read_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_write_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object encode_poly_line_pattern(Object);
extern Object encode_poly_line_style(Object,Object);
extern Object enlarge_index_space(Object,Object);
extern Object ensure_offscreen_pixmap(Object);
extern Object establish_new_object_index_for_icon_rendering(int,...);
extern Object find_irregular_size_stored_raster(Object,Object,Object,Object);
extern Object flush_queued_reclaim_index_space_messages(Object);
extern Object gensym_cons_1(Object,Object);
extern Object get_color_value_1(Object);
extern Object get_icp_object_index_for_icon_rendering(Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object handle_icp_add_downward_sloping_line_to_current_window(void);
extern Object handle_icp_add_ellipse_to_current_window(void);
extern Object handle_icp_add_from_icon_rendering_to_current_window(void);
extern Object handle_icp_add_polygon_to_current_window(void);
extern Object handle_icp_add_solid_rectangle_to_current_window(void);
extern Object handle_icp_add_upward_sloping_line_to_current_window(void);
extern Object handle_icp_add_wide_polyline_to_current_window(void);
extern Object handle_icp_begin_making_icon_rendering(void);
extern Object handle_icp_begin_making_icon_rendering__body(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_copy_from_tiling_pattern_to_current_window(void);
extern Object handle_icp_draw_offscreen(void);
extern Object handle_icp_messages(Object);
extern Object handle_icp_paint_solid_rectangle_in_current_window(void);
extern Object handle_icp_region_extrema_for_stored_raster(void);
extern Object handle_icp_region_extrema_for_stored_raster__body(Object,Object,Object,Object);
extern Object handle_icp_scroll_rectangle_in_current_window(void);
extern Object icon_rendering_structure_memory_usage(void);
extern Object icp_error_internal(Object,Object,Object,Object,Object);
extern Object icp_message_functions_icp_prologue(Object);
extern Object icp_socket_for_gensym_window_qm(Object);
extern Object initialize_icp_object_type(Object,Object,Object,Object);
extern Object initialize_icp_object_type_compile(Object,Object,Object);
extern Object initialize_memory_limit_info(Object,Object);
extern Object initialize_scratchpad_raster(Object,Object,Object,Object,Object);
extern Object install_lru_element_in_queue(Object,Object);
extern Object instantaneous_icp_reader_byte_count(void);
extern Object instantaneous_icp_writer_byte_count(void);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_corresponding_icp_icon_rendering(Object);
extern Object make_corresponding_icp_symbol(Object);
extern Object make_corresponding_icp_tiling_pattern(Object);
extern Object make_decacheable_icon_rendering(int,...);
extern Object make_icon_rendering(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_icon_rendering_internal_1(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_lru_queue(void);
extern Object make_permanent_icon_rendering_structure_internal(void);
extern Object make_permanent_region_bounds_and_raster_structure_internal(void);
extern Object make_pixmap_1(Object,Object,Object,Object);
extern Object make_region_bounds_and_raster_1(void);
extern Object make_region_raster_according_to_messages(Object);
extern Object make_rendering_structure(Object,Object);
extern Object make_thread_array(Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object note_increase_in_size_of_icon_rendering(Object);
extern Object notify_user_at_console(int,...);
extern Object outstanding_icon_rendering_count(void);
extern Object outstanding_region_bounds_and_raster_count(void);
extern Object paint_solid_rectangle_in_current_window(Object,Object,Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object read_icp_boolean(void);
extern Object read_icp_corresponding_object_index(void);
extern Object read_icp_fixnum(void);
extern Object read_icp_integer(void);
extern Object read_icp_unsigned_integer(void);
extern Object reclaim_byte_vector_16(Object);
extern Object reclaim_computed_values_plist(Object);
extern Object reclaim_gensym_cons_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_tree_1(Object);
extern Object reclaim_icon_bitmap_parameters(Object);
extern Object reclaim_icon_region_extrema_qm(Object);
extern Object reclaim_icon_rendering_1(Object);
extern Object reclaim_icon_rendering_and_raster(Object);
extern Object reclaim_icon_rendering_and_remove_from_icon_description(Object);
extern Object reclaim_icon_rendering_and_remove_from_icon_description_if_g2(Object);
extern Object reclaim_icp_object_map(Object,Object,Object);
extern Object reclaim_icp_object_map_for_icon_rendering(Object);
extern Object reclaim_icp_port_entry(Object,Object,Object,Object);
extern Object reclaim_icp_port_entry_for_icon_rendering(Object,Object);
extern Object reclaim_managed_simple_float_array_of_length_1(Object);
extern Object reclaim_managed_simple_vector(Object);
extern Object reclaim_offscreen_pixmap(Object);
extern Object reclaim_pixmap(Object);
extern Object reclaim_region_bounds_and_raster_1(Object);
extern Object reclaim_region_extrema_for_rendering_qm(Object);
extern Object reclaim_rendering_structure(Object);
extern Object reclaim_stored_raster(Object,Object,Object,Object,Object,Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_tree_including_leaves_for_gensym_conses(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object region_bounds_and_raster_structure_memory_usage(void);
extern Object remove_icon_rendering_from_icon_description(Object,Object);
extern Object remove_lru_element(Object);
extern Object replenish_gensym_cons_pool(void);
extern Object resumable_icp_pop(void);
extern Object resumable_icp_pop_list_if_end_marker(void);
extern Object resumable_icp_push(Object);
extern Object scroll_rectangle_in_current_window(Object,Object,Object,Object,Object,Object);
extern Object send_icp_begin_making_icon_rendering(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_region_extrema_for_stored_raster(Object,Object,Object,Object);
extern Object send_queued_reclaim_index_space_messages(Object);
extern Object set_access_form_for_icon_rendering(Object,Object);
extern Object set_icp_object_index_for_icon_rendering(Object,Object,Object);
extern Object start_writing_icp_message(Object);
extern Object store_corresponding_icp_object(Object,Object);
extern Object text_string_p(Object);
extern Object update_object_pool_meters_list(Object);
extern Object windows_platform_p(void);
extern Object write_icp_boolean(Object);
extern Object write_icp_corresponding_object_index(Object);
extern Object write_icp_fixnum(Object);
extern Object write_icp_integer(Object);
extern Object write_icp_list_of_integers(Object);
extern Object write_icp_list_of_unsigned_integers(Object);
extern Object write_icp_maybe_suspend(void);
extern Object write_icp_unsigned_integer(Object);

#else

extern Object accumulate_thrashing_cost_and_decache();
extern Object add_downward_sloping_line_to_current_window();
extern Object add_ellipse_to_current_window();
extern Object add_from_icon_rendering_to_current_window();
extern Object add_icp_message_handler();
extern Object add_polygon_to_current_window();
extern Object add_solid_rectangle_to_current_window();
extern Object add_upward_sloping_line_to_current_window();
extern Object add_wide_polyline_to_current_window();
extern Object allocate_byte_vector_16();
extern Object allocate_offscreen_pixmap();
extern Object assign_corresponding_icp_object_index();
extern Object bitblt_offscreen_bitmap();
extern Object bytes_per_simple_vector();
extern Object c_x11_draw_polygon();
extern Object c_x11_draw_wide_polyline();
extern Object clear_optimized_constants();
extern Object compute_cost_of_decaching_icon_rendering();
extern Object compute_size_of_icon_rendering();
extern Object compute_size_of_icon_rendering_1();
extern Object compute_true_size_of_icon_rendering();
extern Object compute_true_size_of_icon_rendering_1();
extern Object convert_current_scratchpad_raster_to_stored_raster();
extern Object copy_from_tiling_pattern_to_current_window();
extern Object copy_managed_float();
extern Object copy_text_string();
extern Object copy_tree_including_leaves_using_gensym_conses();
extern Object decache_icon_rendering();
extern Object delete_icon_rendering_and_reclaim_icp_index();
extern Object direct_structure_method();
extern Object draw_ellipse_on_current_window();
extern Object draw_offscreen();
extern Object draw_polygon_on_current_window();
extern Object draw_wide_polyline_on_window();
extern Object emit_icp_read_trace();
extern Object emit_icp_write_trace();
extern Object encode_poly_line_pattern();
extern Object encode_poly_line_style();
extern Object enlarge_index_space();
extern Object ensure_offscreen_pixmap();
extern Object establish_new_object_index_for_icon_rendering();
extern Object find_irregular_size_stored_raster();
extern Object flush_queued_reclaim_index_space_messages();
extern Object gensym_cons_1();
extern Object get_color_value_1();
extern Object get_icp_object_index_for_icon_rendering();
extern Object getfq_function_no_default();
extern Object handle_icp_add_downward_sloping_line_to_current_window();
extern Object handle_icp_add_ellipse_to_current_window();
extern Object handle_icp_add_from_icon_rendering_to_current_window();
extern Object handle_icp_add_polygon_to_current_window();
extern Object handle_icp_add_solid_rectangle_to_current_window();
extern Object handle_icp_add_upward_sloping_line_to_current_window();
extern Object handle_icp_add_wide_polyline_to_current_window();
extern Object handle_icp_begin_making_icon_rendering();
extern Object handle_icp_begin_making_icon_rendering__body();
extern Object handle_icp_copy_from_tiling_pattern_to_current_window();
extern Object handle_icp_draw_offscreen();
extern Object handle_icp_messages();
extern Object handle_icp_paint_solid_rectangle_in_current_window();
extern Object handle_icp_region_extrema_for_stored_raster();
extern Object handle_icp_region_extrema_for_stored_raster__body();
extern Object handle_icp_scroll_rectangle_in_current_window();
extern Object icon_rendering_structure_memory_usage();
extern Object icp_error_internal();
extern Object icp_message_functions_icp_prologue();
extern Object icp_socket_for_gensym_window_qm();
extern Object initialize_icp_object_type();
extern Object initialize_icp_object_type_compile();
extern Object initialize_memory_limit_info();
extern Object initialize_scratchpad_raster();
extern Object install_lru_element_in_queue();
extern Object instantaneous_icp_reader_byte_count();
extern Object instantaneous_icp_writer_byte_count();
extern Object load_and_initialize_type_description();
extern Object make_corresponding_icp_icon_rendering();
extern Object make_corresponding_icp_symbol();
extern Object make_corresponding_icp_tiling_pattern();
extern Object make_decacheable_icon_rendering();
extern Object make_icon_rendering();
extern Object make_icon_rendering_internal_1();
extern Object make_lru_queue();
extern Object make_permanent_icon_rendering_structure_internal();
extern Object make_permanent_region_bounds_and_raster_structure_internal();
extern Object make_pixmap_1();
extern Object make_region_bounds_and_raster_1();
extern Object make_region_raster_according_to_messages();
extern Object make_rendering_structure();
extern Object make_thread_array();
extern Object memq_function();
extern Object mutate_global_property();
extern Object note_increase_in_size_of_icon_rendering();
extern Object notify_user_at_console();
extern Object outstanding_icon_rendering_count();
extern Object outstanding_region_bounds_and_raster_count();
extern Object paint_solid_rectangle_in_current_window();
extern Object push_optimized_constant();
extern Object read_icp_boolean();
extern Object read_icp_corresponding_object_index();
extern Object read_icp_fixnum();
extern Object read_icp_integer();
extern Object read_icp_unsigned_integer();
extern Object reclaim_byte_vector_16();
extern Object reclaim_computed_values_plist();
extern Object reclaim_gensym_cons_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_tree_1();
extern Object reclaim_icon_bitmap_parameters();
extern Object reclaim_icon_region_extrema_qm();
extern Object reclaim_icon_rendering_1();
extern Object reclaim_icon_rendering_and_raster();
extern Object reclaim_icon_rendering_and_remove_from_icon_description();
extern Object reclaim_icon_rendering_and_remove_from_icon_description_if_g2();
extern Object reclaim_icp_object_map();
extern Object reclaim_icp_object_map_for_icon_rendering();
extern Object reclaim_icp_port_entry();
extern Object reclaim_icp_port_entry_for_icon_rendering();
extern Object reclaim_managed_simple_float_array_of_length_1();
extern Object reclaim_managed_simple_vector();
extern Object reclaim_offscreen_pixmap();
extern Object reclaim_pixmap();
extern Object reclaim_region_bounds_and_raster_1();
extern Object reclaim_region_extrema_for_rendering_qm();
extern Object reclaim_rendering_structure();
extern Object reclaim_stored_raster();
extern Object reclaim_text_string();
extern Object reclaim_tree_including_leaves_for_gensym_conses();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object region_bounds_and_raster_structure_memory_usage();
extern Object remove_icon_rendering_from_icon_description();
extern Object remove_lru_element();
extern Object replenish_gensym_cons_pool();
extern Object resumable_icp_pop();
extern Object resumable_icp_pop_list_if_end_marker();
extern Object resumable_icp_push();
extern Object scroll_rectangle_in_current_window();
extern Object send_icp_begin_making_icon_rendering();
extern Object send_icp_region_extrema_for_stored_raster();
extern Object send_queued_reclaim_index_space_messages();
extern Object set_access_form_for_icon_rendering();
extern Object set_icp_object_index_for_icon_rendering();
extern Object start_writing_icp_message();
extern Object store_corresponding_icp_object();
extern Object text_string_p();
extern Object update_object_pool_meters_list();
extern Object windows_platform_p();
extern Object write_icp_boolean();
extern Object write_icp_corresponding_object_index();
extern Object write_icp_fixnum();
extern Object write_icp_integer();
extern Object write_icp_list_of_integers();
extern Object write_icp_list_of_unsigned_integers();
extern Object write_icp_maybe_suspend();
extern Object write_icp_unsigned_integer();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Abort_for_icp_catcher_qm, Qabort_for_icp_catcher_qm);
extern Object Available_gensym_conses_tail_vector;
extern Object Available_gensym_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);
#define Bitblt_offscreen_pixmap FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Bottom_edge_of_draw_area, Qbottom_edge_of_draw_area);
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_icon_renderings, Qchain_of_available_icon_renderings);
extern Object Chain_of_available_icon_renderings_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_region_bounds_and_rasters, Qchain_of_available_region_bounds_and_rasters);
extern Object Chain_of_available_region_bounds_and_rasters_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_background_color_value, Qcurrent_background_color_value);
DECLARE_VARIABLE_WITH_SYMBOL(Current_drawing_transfer_mode, Qcurrent_drawing_transfer_mode);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_port, Qcurrent_icp_port);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_read_trace_level, Qcurrent_icp_read_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_write_trace_level, Qcurrent_icp_write_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_native_window_qm, Qcurrent_native_window_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster, Qcurrent_scratchpad_raster);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_depth, Qcurrent_scratchpad_raster_depth);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_height, Qcurrent_scratchpad_raster_height);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_tiled_p, Qcurrent_scratchpad_raster_tiled_p);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_type, Qcurrent_scratchpad_raster_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_width, Qcurrent_scratchpad_raster_width);
DECLARE_VARIABLE_WITH_SYMBOL(Current_standard_icp_object_index_space, Qcurrent_standard_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_temporary_icp_object_index_space, Qcurrent_temporary_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_window, Qcurrent_window);
DECLARE_VARIABLE_WITH_SYMBOL(Current_x_max_for_stored_raster_qm, Qcurrent_x_max_for_stored_raster_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_x_offset_for_stored_raster_qm, Qcurrent_x_offset_for_stored_raster_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_y_max_for_stored_raster_qm, Qcurrent_y_max_for_stored_raster_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_y_offset_for_stored_raster_qm, Qcurrent_y_offset_for_stored_raster_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Decache_occurred_since_last_update_qm, Qdecache_occurred_since_last_update_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Disable_resumability, Qdisable_resumability);
DECLARE_VARIABLE_WITH_SYMBOL(Do_not_error_in_x11_create_pixmap_on_failed_allocation, Qdo_not_error_in_x11_create_pixmap_on_failed_allocation);
DECLARE_VARIABLE_WITH_SYMBOL(G2_machine_type, Qg2_machine_type);
DECLARE_VARIABLE_WITH_SYMBOL(Icon_rendering_count, Qicon_rendering_count);
extern Object Icon_rendering_lru_queue;
extern Object Icon_rendering_memory_limit_info;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_printing_message_handler_array, Qicp_printing_message_handler_array);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_read_trace_cutoff_level_qm, Qicp_read_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_suspend, Qicp_suspend);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_write_trace_cutoff_level_qm, Qicp_write_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Inhibit_corresponding_icp_object_making, Qinhibit_corresponding_icp_object_making);
DECLARE_VARIABLE_WITH_SYMBOL(Left_edge_of_draw_area, Qleft_edge_of_draw_area);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
DECLARE_VARIABLE_WITH_SYMBOL(Memory_limit_variable_names_for_decacheable_structures, Qmemory_limit_variable_names_for_decacheable_structures);
DECLARE_VARIABLE_WITH_SYMBOL(Names_and_sizes_for_decacheable_structures, Qnames_and_sizes_for_decacheable_structures);
DECLARE_VARIABLE_WITH_SYMBOL(On_monochrome_raster_list_p, Qon_monochrome_raster_list_p);
#define Ps_dash FIX((SI_Long)1L)
#define Ps_dashdot FIX((SI_Long)3L)
#define Ps_dashdotdot FIX((SI_Long)4L)
#define Ps_dot FIX((SI_Long)2L)
#define Ps_endcap_flat FIX((SI_Long)512L)
#define Ps_endcap_round FIX((SI_Long)0L)
#define Ps_join_miter FIX((SI_Long)8192L)
#define Ps_join_round FIX((SI_Long)0L)
#define Ps_solid FIX((SI_Long)0L)
#define Ps_userstyle FIX((SI_Long)7L)
#define Reclaim_offscreen_pixmap FIX((SI_Long)4L)
DECLARE_VARIABLE_WITH_SYMBOL(Region_bounds_and_raster_count, Qregion_bounds_and_raster_count);
DECLARE_VARIABLE_WITH_SYMBOL(Region_x_max_qm, Qregion_x_max_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Region_x_offset_qm, Qregion_x_offset_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Region_y_max_qm, Qregion_y_max_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Region_y_offset_qm, Qregion_y_offset_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Resumable_icp_state, Qresumable_icp_state);
DECLARE_VARIABLE_WITH_SYMBOL(Right_edge_of_draw_area, Qright_edge_of_draw_area);
DECLARE_VARIABLE_WITH_SYMBOL(Scratchpad_raster, Qscratchpad_raster);
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Special_variable_for_use_value_macro, Qspecial_variable_for_use_value_macro);
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
extern Object The_type_description_of_icon_rendering;
extern Object The_type_description_of_region_bounds_and_raster;
DECLARE_VARIABLE_WITH_SYMBOL(Top_edge_of_draw_area, Qtop_edge_of_draw_area);
#define Transparent_color_value FIX((SI_Long)16777216L)
DECLARE_VARIABLE_WITH_SYMBOL(Type_of_current_window, Qtype_of_current_window);
DECLARE_VARIABLE_WITH_SYMBOL(Writing_resumable_icp_messages_p, Qwriting_resumable_icp_messages_p);
#define X11_copy FIX((SI_Long)1L)
#define X11_stippled FIX((SI_Long)4L)
#define X11_xor FIX((SI_Long)2L)
