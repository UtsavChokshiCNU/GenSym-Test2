/* win3a.h -- Header File for win3a.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qcons;
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
extern Object add_from_graph_rendering_to_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object add_from_graph_ring_raster_to_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object add_icp_message_handler(Object,Object);
extern Object allocate_stored_raster_1(Object,Object,Object,Object,Object);
extern Object assign_corresponding_icp_object_index(Object,Object,Object);
extern Object bytes_per_simple_vector(Object);
extern Object clear_data_clipping_rectangles(void);
extern Object clear_optimized_constants(void);
extern Object compute_cost_of_decaching_graph_rendering(Object);
extern Object compute_size_of_graph_rendering(Object);
extern Object compute_size_of_graph_rendering_1(Object,Object);
extern Object compute_true_size_of_graph_rendering(Object);
extern Object compute_true_size_of_graph_rendering_1(Object,Object);
extern Object copy_list_using_gensym_conses_1(Object);
extern Object copy_list_using_graph_conses_1(Object);
extern Object copy_tree_using_graph_conses_1(Object);
extern Object decache_graph_rendering(Object);
extern Object delete_graph_cons_1(Object,Object);
extern Object delete_graph_element_1(Object,Object);
extern Object delete_graph_rendering_and_reclaim_icp_index(Object);
extern Object direct_structure_method(Object,Object);
extern Object emit_icp_read_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_write_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object enlarge_index_space(Object,Object);
extern Object establish_new_object_index_for_graph_rendering(int,...);
extern Object gensym_cons_1(Object,Object);
extern Object get_bracketing_sizes(Object,Object);
extern Object get_icp_object_index_for_graph_rendering(Object,Object);
extern Object get_memory_limit_info_given_size(Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object graph_cons_1(Object,Object);
extern Object graph_cons_memory_usage(void);
extern Object graph_list_2(Object,Object);
extern Object graph_list_3(Object,Object,Object);
extern Object graph_list_4(Object,Object,Object,Object);
extern Object graph_list_trace_hook(Object);
extern Object graph_rendering_structure_memory_usage(void);
extern Object handle_icp_add_from_graph_rendering_to_current_window(void);
extern Object handle_icp_begin_making_graph_rendering(void);
extern Object handle_icp_begin_making_graph_rendering__body(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object handle_icp_clear_data_clipping_rectangles(void);
extern Object handle_icp_messages(Object);
extern Object handle_icp_prepare_for_painting_graph(void);
extern Object handle_icp_prepare_for_painting_graph__body(Object);
extern Object handle_icp_set_graph_rendering_foreground_only_mode(void);
extern Object handle_icp_update_graph_data_extrema(void);
extern Object handle_icp_update_graph_dateline(void);
extern Object handle_icp_update_ring_raster_for_graph_given_color_values(void);
extern Object handle_icp_update_ring_raster_for_graph_given_color_values_2(void);
extern Object icp_error_internal(Object,Object,Object,Object,Object);
extern Object icp_message_functions_icp_prologue(Object);
extern Object initialize_icp_object_type(Object,Object,Object,Object);
extern Object initialize_icp_object_type_compile(Object,Object,Object);
extern Object install_lru_element_in_queue(Object,Object);
extern Object instantaneous_icp_reader_byte_count(void);
extern Object instantaneous_icp_writer_byte_count(void);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_corresponding_icp_graph_rendering(Object);
extern Object make_corresponding_icp_symbol(Object);
extern Object make_decacheable_graph_rendering(int,...);
extern Object make_graph_list_1(Object);
extern Object make_graph_rendering(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_graph_rendering_internal_1(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_graph_rendering_structure(Object);
extern Object make_permanent_graph_rendering_structure_internal(void);
extern Object make_permanent_ring_raster_for_graph_structure_internal(void);
extern Object make_ring_raster_for_graph_1(void);
extern Object make_thread_array(Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object outstanding_graph_conses(void);
extern Object outstanding_graph_rendering_count(void);
extern Object outstanding_ring_raster_for_graph_count(void);
extern Object printing_window_p(Object);
extern Object push_optimized_constant(Object);
extern Object read_icp_boolean(void);
extern Object read_icp_corresponding_object_index(void);
extern Object read_icp_integer(void);
extern Object read_icp_unsigned_integer(void);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_graph_cons_1(Object);
extern Object reclaim_graph_list_1(Object);
extern Object reclaim_graph_list_star_1(Object);
extern Object reclaim_graph_rendering_1(Object);
extern Object reclaim_graph_rendering_and_raster(Object);
extern Object reclaim_graph_rendering_and_raster_1(Object);
extern Object reclaim_graph_tree_1(Object);
extern Object reclaim_icp_object_map(Object,Object,Object);
extern Object reclaim_icp_object_map_for_graph_rendering(Object);
extern Object reclaim_icp_port_entry(Object,Object,Object,Object);
extern Object reclaim_icp_port_entry_for_graph_rendering(Object,Object);
extern Object reclaim_ring_raster_for_graph_1(Object);
extern Object reclaim_stored_raster(Object,Object,Object,Object,Object,Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object remove_graph_rendering_from_graph_grid(Object,Object);
extern Object remove_lru_element(Object);
extern Object replenish_graph_cons_pool(void);
extern Object replenish_graph_list_pool(Object);
extern Object resumable_icp_pop(void);
extern Object resumable_icp_pop_list_if_end_marker(void);
extern Object resumable_icp_push(Object);
extern Object ring_raster_for_graph_structure_memory_usage(void);
extern Object send_icp_begin_making_graph_rendering(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object send_icp_prepare_for_painting_graph(Object);
extern Object set_access_form_for_graph_rendering(Object,Object);
extern Object set_graph_rendering_foreground_only_mode(Object,Object);
extern Object set_icp_object_index_for_graph_rendering(Object,Object,Object);
extern Object start_writing_icp_message(Object);
extern Object store_corresponding_icp_object(Object,Object);
extern Object update_graph_data_extrema(Object,Object,Object,Object);
extern Object update_graph_dateline(Object,Object,Object);
extern Object update_object_pool_meters_list(Object);
extern Object update_ring_raster_for_graph_given_color_values(Object,Object);
extern Object update_ring_raster_for_graph_given_color_values_2(Object,Object);
extern Object write_icp_boolean(Object);
extern Object write_icp_corresponding_object_index(Object);
extern Object write_icp_integer(Object);
extern Object write_icp_list_of_unsigned_integers(Object);
extern Object write_icp_maybe_suspend(void);
extern Object write_icp_unsigned_integer(Object);

#else

extern Object accumulate_thrashing_cost_and_decache();
extern Object add_from_graph_rendering_to_current_window();
extern Object add_from_graph_ring_raster_to_current_window();
extern Object add_icp_message_handler();
extern Object allocate_stored_raster_1();
extern Object assign_corresponding_icp_object_index();
extern Object bytes_per_simple_vector();
extern Object clear_data_clipping_rectangles();
extern Object clear_optimized_constants();
extern Object compute_cost_of_decaching_graph_rendering();
extern Object compute_size_of_graph_rendering();
extern Object compute_size_of_graph_rendering_1();
extern Object compute_true_size_of_graph_rendering();
extern Object compute_true_size_of_graph_rendering_1();
extern Object copy_list_using_gensym_conses_1();
extern Object copy_list_using_graph_conses_1();
extern Object copy_tree_using_graph_conses_1();
extern Object decache_graph_rendering();
extern Object delete_graph_cons_1();
extern Object delete_graph_element_1();
extern Object delete_graph_rendering_and_reclaim_icp_index();
extern Object direct_structure_method();
extern Object emit_icp_read_trace();
extern Object emit_icp_write_trace();
extern Object enlarge_index_space();
extern Object establish_new_object_index_for_graph_rendering();
extern Object gensym_cons_1();
extern Object get_bracketing_sizes();
extern Object get_icp_object_index_for_graph_rendering();
extern Object get_memory_limit_info_given_size();
extern Object getfq_function_no_default();
extern Object graph_cons_1();
extern Object graph_cons_memory_usage();
extern Object graph_list_2();
extern Object graph_list_3();
extern Object graph_list_4();
extern Object graph_list_trace_hook();
extern Object graph_rendering_structure_memory_usage();
extern Object handle_icp_add_from_graph_rendering_to_current_window();
extern Object handle_icp_begin_making_graph_rendering();
extern Object handle_icp_begin_making_graph_rendering__body();
extern Object handle_icp_clear_data_clipping_rectangles();
extern Object handle_icp_messages();
extern Object handle_icp_prepare_for_painting_graph();
extern Object handle_icp_prepare_for_painting_graph__body();
extern Object handle_icp_set_graph_rendering_foreground_only_mode();
extern Object handle_icp_update_graph_data_extrema();
extern Object handle_icp_update_graph_dateline();
extern Object handle_icp_update_ring_raster_for_graph_given_color_values();
extern Object handle_icp_update_ring_raster_for_graph_given_color_values_2();
extern Object icp_error_internal();
extern Object icp_message_functions_icp_prologue();
extern Object initialize_icp_object_type();
extern Object initialize_icp_object_type_compile();
extern Object install_lru_element_in_queue();
extern Object instantaneous_icp_reader_byte_count();
extern Object instantaneous_icp_writer_byte_count();
extern Object load_and_initialize_type_description();
extern Object make_corresponding_icp_graph_rendering();
extern Object make_corresponding_icp_symbol();
extern Object make_decacheable_graph_rendering();
extern Object make_graph_list_1();
extern Object make_graph_rendering();
extern Object make_graph_rendering_internal_1();
extern Object make_graph_rendering_structure();
extern Object make_permanent_graph_rendering_structure_internal();
extern Object make_permanent_ring_raster_for_graph_structure_internal();
extern Object make_ring_raster_for_graph_1();
extern Object make_thread_array();
extern Object memq_function();
extern Object mutate_global_property();
extern Object outstanding_graph_conses();
extern Object outstanding_graph_rendering_count();
extern Object outstanding_ring_raster_for_graph_count();
extern Object printing_window_p();
extern Object push_optimized_constant();
extern Object read_icp_boolean();
extern Object read_icp_corresponding_object_index();
extern Object read_icp_integer();
extern Object read_icp_unsigned_integer();
extern Object reclaim_gensym_list_1();
extern Object reclaim_graph_cons_1();
extern Object reclaim_graph_list_1();
extern Object reclaim_graph_list_star_1();
extern Object reclaim_graph_rendering_1();
extern Object reclaim_graph_rendering_and_raster();
extern Object reclaim_graph_rendering_and_raster_1();
extern Object reclaim_graph_tree_1();
extern Object reclaim_icp_object_map();
extern Object reclaim_icp_object_map_for_graph_rendering();
extern Object reclaim_icp_port_entry();
extern Object reclaim_icp_port_entry_for_graph_rendering();
extern Object reclaim_ring_raster_for_graph_1();
extern Object reclaim_stored_raster();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object remove_graph_rendering_from_graph_grid();
extern Object remove_lru_element();
extern Object replenish_graph_cons_pool();
extern Object replenish_graph_list_pool();
extern Object resumable_icp_pop();
extern Object resumable_icp_pop_list_if_end_marker();
extern Object resumable_icp_push();
extern Object ring_raster_for_graph_structure_memory_usage();
extern Object send_icp_begin_making_graph_rendering();
extern Object send_icp_prepare_for_painting_graph();
extern Object set_access_form_for_graph_rendering();
extern Object set_graph_rendering_foreground_only_mode();
extern Object set_icp_object_index_for_graph_rendering();
extern Object start_writing_icp_message();
extern Object store_corresponding_icp_object();
extern Object update_graph_data_extrema();
extern Object update_graph_dateline();
extern Object update_object_pool_meters_list();
extern Object update_ring_raster_for_graph_given_color_values();
extern Object update_ring_raster_for_graph_given_color_values_2();
extern Object write_icp_boolean();
extern Object write_icp_corresponding_object_index();
extern Object write_icp_integer();
extern Object write_icp_list_of_unsigned_integers();
extern Object write_icp_maybe_suspend();
extern Object write_icp_unsigned_integer();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Abort_for_icp_catcher_qm, Qabort_for_icp_catcher_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Available_graph_conses, Qavailable_graph_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Available_graph_conses_tail, Qavailable_graph_conses_tail);
extern Object Available_graph_conses_tail_vector;
extern Object Available_graph_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);
extern Object Bytes_per_rtl_ptr;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_graph_renderings, Qchain_of_available_graph_renderings);
extern Object Chain_of_available_graph_renderings_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_ring_raster_for_graphs, Qchain_of_available_ring_raster_for_graphs);
extern Object Chain_of_available_ring_raster_for_graphs_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Clipping_rectangles_for_new_data_qm, Qclipping_rectangles_for_new_data_qm);
extern Object Cons_pool_conses_to_make_at_a_time;
DECLARE_VARIABLE_WITH_SYMBOL(Current_graph_rendering, Qcurrent_graph_rendering);
DECLARE_VARIABLE_WITH_SYMBOL(Current_graph_rendering_structure, Qcurrent_graph_rendering_structure);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_port, Qcurrent_icp_port);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_read_trace_level, Qcurrent_icp_read_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_write_trace_level, Qcurrent_icp_write_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_native_window_qm, Qcurrent_native_window_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_color_value_list, Qcurrent_scratchpad_color_value_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster, Qcurrent_scratchpad_raster);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_depth, Qcurrent_scratchpad_raster_depth);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_height, Qcurrent_scratchpad_raster_height);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_list, Qcurrent_scratchpad_raster_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_tiled_p, Qcurrent_scratchpad_raster_tiled_p);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_type, Qcurrent_scratchpad_raster_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_width, Qcurrent_scratchpad_raster_width);
DECLARE_VARIABLE_WITH_SYMBOL(Current_standard_icp_object_index_space, Qcurrent_standard_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_temporary_icp_object_index_space, Qcurrent_temporary_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_window, Qcurrent_window);
DECLARE_VARIABLE_WITH_SYMBOL(Decache_occurred_since_last_update_qm, Qdecache_occurred_since_last_update_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Disable_resumability, Qdisable_resumability);
DECLARE_VARIABLE_WITH_SYMBOL(Erase_dateline, Qerase_dateline);
DECLARE_VARIABLE_WITH_SYMBOL(Graph_cons_counter, Qgraph_cons_counter);
extern Object Graph_cons_counter_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Graph_rendering_count, Qgraph_rendering_count);
extern Object Graph_rendering_lru_queue;
extern Object Graph_rendering_memory_limit_info;
DECLARE_VARIABLE_WITH_SYMBOL(Icp_printing_message_handler_array, Qicp_printing_message_handler_array);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_read_trace_cutoff_level_qm, Qicp_read_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_suspend, Qicp_suspend);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_write_trace_cutoff_level_qm, Qicp_write_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Inhibit_corresponding_icp_object_making, Qinhibit_corresponding_icp_object_making);
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
DECLARE_VARIABLE_WITH_SYMBOL(Memory_limit_variable_names_for_decacheable_structures, Qmemory_limit_variable_names_for_decacheable_structures);
DECLARE_VARIABLE_WITH_SYMBOL(Names_and_sizes_for_decacheable_structures, Qnames_and_sizes_for_decacheable_structures);
DECLARE_VARIABLE_WITH_SYMBOL(On_monochrome_raster_list_p, Qon_monochrome_raster_list_p);
DECLARE_VARIABLE_WITH_SYMBOL(Resumable_icp_state, Qresumable_icp_state);
DECLARE_VARIABLE_WITH_SYMBOL(Ring_raster_for_graph_count, Qring_raster_for_graph_count);
DECLARE_VARIABLE_WITH_SYMBOL(Scratchpad_raster, Qscratchpad_raster);
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
extern Object The_type_description_of_graph_rendering;
extern Object The_type_description_of_ring_raster_for_graph;
DECLARE_VARIABLE_WITH_SYMBOL(Type_of_current_window, Qtype_of_current_window);
DECLARE_VARIABLE_WITH_SYMBOL(Writing_resumable_icp_messages_p, Qwriting_resumable_icp_messages_p);
#define X11_copy FIX((SI_Long)1L)
#define X11_stippled FIX((SI_Long)4L)
#define X11_xor FIX((SI_Long)2L)
