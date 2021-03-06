/* grphs2.h -- Header File for grphs2.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qeq;
extern Object Qeval;
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

extern Object absolute_range_specified_p(Object);
extern Object activate_for_graph(Object);
extern Object add_frame_note(int,...);
extern Object add_frame_representation_if_necessary(Object,Object);
extern Object add_subblock(Object,Object);
extern Object adjust_and_compute_x_value_on_graph(Object,Object,Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_managed_array(int,...);
extern Object bad_desired_range_too_small_qm(Object);
extern Object bad_horizontal_range_zero_qm(Object);
extern Object bad_plot_range_specs_qm(Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object change_edges_of_block(Object,Object,Object,Object,Object);
extern Object change_size_of_graph(Object,Object,Object,Object,Object);
extern Object chestnut_floorf_function(Object,Object);
extern Object clear_display_for_graph(Object);
extern Object clear_plot(Object);
extern Object clear_plot_marker_data(Object);
extern Object coerce_managed_float_or_fixnum_to_gensym_float(Object);
extern Object compute_erase_dateline(Object);
extern Object compute_high_value_for_horizontal_axis(Object,Object);
extern Object compute_horizontal_axis_range(Object,Object,Object);
extern Object compute_low_value_for_horizontal_axis(Object,Object);
extern Object compute_minimum_bottom_edge_for_graph_grid(Object);
extern Object compute_minimum_right_edge_for_graph_grid(Object);
extern Object compute_new_parameters_for_horizontal_axis_of_grid(int,...);
extern Object compute_new_parameters_for_vertical_axis_of_grid(Object,Object);
extern Object compute_next_maximum_x_value(Object,Object);
extern Object compute_next_minimum_x_value(Object,Object);
extern Object compute_shift_for_scrolling(Object,Object,Object,Object,Object,Object);
extern Object compute_time_of_newest_data_point(Object,Object);
extern Object compute_time_of_newest_data_point_given_variable(Object,Object);
extern Object compute_time_of_oldest_data_point(Object,Object);
extern Object compute_time_of_oldest_data_point_given_variable(Object,Object);
extern Object compute_y_value_on_graph_new_with_less_truncation(Object);
extern Object constant_queue_next(Object,Object);
extern Object convert_text_string_to_text(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text_string(Object);
extern Object data_exists_for_plot_p(Object);
extern Object deactivate_for_graph(Object);
extern Object decache_and_remove_all_graph_renderings_from_graph_grid(Object);
extern Object decode_gensym_time(Object);
extern Object delete_all_frame_notes_for_graph(Object);
extern Object delete_eval_element_1(Object,Object);
extern Object delete_frame(Object);
extern Object delete_frame_note_if_any(Object,Object);
extern Object determine_format_for_non_time_axis_label(Object);
extern Object determine_ruling_for_axis(Object,Object,Object,Object);
extern Object determine_ruling_for_time_axis(Object,Object,Object,Object,Object);
extern Object determine_rulings_automatically(Object,Object);
extern Object determine_rulings_based_on_interval(Object,Object,Object);
extern Object draw_graph_grid_current_time_display(Object);
extern Object draw_only_new_data_for_graph_grid(Object);
extern Object enlarge_workspace_for_block_rectangle_if_necessary(Object,Object);
extern Object evaluate_designation(Object,Object);
extern Object expand_plot_data_ring_buffer(Object);
extern Object extend_current_gensym_string(int,...);
extern Object future_task_schedule_2(Object);
extern Object generate_float_vector(Object);
extern Object get_history_current_time(Object,Object,Object);
extern Object get_history_element_using_best_search(Object,Object,Object);
extern Object get_history_index_by_binary_search(Object,Object,Object);
extern Object get_instance_with_name_if_any(Object,Object);
extern Object get_lookup_slot_value(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_or_make_icon_rendering(Object,Object);
extern Object get_or_make_up_designation_for_block(Object);
extern Object get_previous_history_time(void);
extern Object get_ring_buffer_in_cascade_for_history_time(Object,Object);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object get_type_of_slot_if_any(int,...);
extern Object get_value_at_history_time(Object,Object,Object);
extern Object get_value_at_history_time_given_variable(Object,Object,Object);
extern Object get_variable_given_graph_expression(Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object give_warning_1(int,...);
extern Object graph_cons_1(Object,Object);
extern Object graph_must_be_refreshed_for_old_data_qm(Object);
extern Object label_values_same_p(Object,Object,Object);
extern Object low_and_high_values_specified_for_vertical_axis_qm(Object);
extern Object make_format_frame(Object);
extern Object make_frame(Object);
extern Object make_graph(Object);
extern Object make_graph_axis_label(int,...);
extern Object make_graph_not_up_to_date(Object);
extern Object make_horizontal_axis_graph_heading_text(Object);
extern Object make_horizontal_axis_graph_heading_text_1(Object,Object,Object);
extern Object make_horizontal_axis_label(int,...);
extern Object make_icon_slot_group_1(void);
extern Object make_new_time_axis_label(int,...);
extern Object make_new_variable_axis_label(int,...);
extern Object make_or_reformat_graph_grid(int,...);
extern Object make_or_reformat_table(int,...);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object make_plot(Object,Object,Object,Object,Object);
extern Object make_plot_data_ring_buffer_1(void);
extern Object make_symbol_properties_hash_table_skip_list_sentinel(Object,Object);
extern Object make_text_cell_for_slot(int,...);
extern Object make_text_string_for_time_axis_label(Object,Object,Object,Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object mutate_plot_max_given_plot_min_and_max(Object);
extern Object mutate_plot_min_given_plot_min_and_max(Object);
extern Object need_to_reformat_horizontal_axis_qm(Object,Object,Object);
extern Object need_to_reformat_vertical_axis_qm(Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object note_change_to_dependent_frame_1(void);
extern Object notify_user(int,...);
extern Object paint_marker_onto_graph_raster(Object,Object,Object,Object);
extern Object paint_nupec_plot_marker(Object,Object,Object,Object,Object,Object);
extern Object parse_desired_absolute_or_relative_range(Object);
extern Object plot_marker_given_plot(Object);
extern Object plot_min_and_max_given_plot(Object);
extern Object post_reformat_warning_note_for_graph(Object);
extern Object print_day_of_week_and_hour(Object,Object);
extern Object print_hour_and_minute(Object,Object);
extern Object print_minute_and_second(Object,Object);
extern Object print_month_and_date(Object,Object);
extern Object print_month_and_year(Object,Object);
extern Object print_relative_days(Object);
extern Object print_relative_hours(Object);
extern Object print_relative_hours_and_minutes(Object,Object);
extern Object print_relative_weeks(Object);
extern Object put_up_label_for_graph_horizontal_axis(Object,Object);
extern Object put_up_new_high_value_label_for_horizontal_axis(Object);
extern Object put_up_new_labels_for_horizontal_graph_axis(Object,Object,Object);
extern Object put_up_new_labels_for_vertical_graph_axis(Object,Object);
extern Object reclaim_graph_list_1(Object);
extern Object reclaim_plot_marker_indices(Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_slot_value(Object);
extern Object reclaim_temporary_constant_1(Object);
extern Object rectangle_visible_p(Object);
extern Object reformat_table_in_place(int,...);
extern Object refresh_data_for_plots(Object,Object,Object);
extern Object refresh_plot_data_buffer(Object,Object,Object,Object,Object);
extern Object remove_as_subblock_if_necessary(int,...);
extern Object remove_axis_labels_from_graph_grid(Object,Object);
extern Object replenish_lookup_cons_pool(void);
extern Object resize_for_graph_grid(Object,Object,Object,Object);
extern Object restore_graph_to_normal_size(Object);
extern Object round_for_graphs(Object);
extern Object scale_y_data_for_plot(Object,Object);
extern Object scale_y_data_for_plots_if_necessary(Object);
extern Object scalef_function(Object,Object);
extern Object set_edges_of_block(Object,Object,Object,Object,Object);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object set_skip_list_entry(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object set_up_next_plot_marker_if_appropriate_for_new_plot_data(void);
extern Object set_up_time_and_data_at_current_index(Object);
extern Object single_color_line_drawing_description_p(Object);
extern Object slot_value_cons_1(Object,Object);
extern Object slot_value_list_2(Object,Object);
extern Object slot_value_number_p(Object);
extern Object store_data_to_display_for_enough_pixels_case(Object);
extern Object store_data_to_display_for_more_data_than_pixels_case(Object);
extern Object store_managed_number_or_value_function(Object,Object);
extern Object store_min_and_max_plot_data_points(Object,Object,Object,Object,Object);
extern Object store_new_element_in_plot_function(Object,Object,Object,Object);
extern Object store_new_plot_data_1(Object);
extern Object store_new_plot_data_3(void);
extern Object store_new_plot_data_4(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object store_new_plot_data_with_scaling(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object store_new_plot_data_without_scaling(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object text_string_p(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_wide_character(Object);
extern Object update_display_for_graph(Object,Object,Object,Object);
extern Object update_images(int,...);
extern Object update_images_of_block(Object,Object,Object);
extern Object update_images_of_graph(Object,Object);
extern Object update_images_of_graph_grid_and_data(Object,Object);
extern Object update_images_of_only_new_data_for_graph_grid(Object,Object);
extern Object variable_has_subsecond_history_p(Object,Object);
extern Object withdraw_backward_chaining(Object);
extern Object write_floating_point_number(int,...);

#else

extern Object absolute_range_specified_p();
extern Object activate_for_graph();
extern Object add_frame_note();
extern Object add_frame_representation_if_necessary();
extern Object add_subblock();
extern Object adjust_and_compute_x_value_on_graph();
extern Object allocate_byte_vector_16();
extern Object allocate_managed_array();
extern Object bad_desired_range_too_small_qm();
extern Object bad_horizontal_range_zero_qm();
extern Object bad_plot_range_specs_qm();
extern Object bytes_per_double_float_simple_array();
extern Object cancel_and_reclaim_scheduled_queue_element_1();
extern Object change_edges_of_block();
extern Object change_size_of_graph();
extern Object chestnut_floorf_function();
extern Object clear_display_for_graph();
extern Object clear_plot();
extern Object clear_plot_marker_data();
extern Object coerce_managed_float_or_fixnum_to_gensym_float();
extern Object compute_erase_dateline();
extern Object compute_high_value_for_horizontal_axis();
extern Object compute_horizontal_axis_range();
extern Object compute_low_value_for_horizontal_axis();
extern Object compute_minimum_bottom_edge_for_graph_grid();
extern Object compute_minimum_right_edge_for_graph_grid();
extern Object compute_new_parameters_for_horizontal_axis_of_grid();
extern Object compute_new_parameters_for_vertical_axis_of_grid();
extern Object compute_next_maximum_x_value();
extern Object compute_next_minimum_x_value();
extern Object compute_shift_for_scrolling();
extern Object compute_time_of_newest_data_point();
extern Object compute_time_of_newest_data_point_given_variable();
extern Object compute_time_of_oldest_data_point();
extern Object compute_time_of_oldest_data_point_given_variable();
extern Object compute_y_value_on_graph_new_with_less_truncation();
extern Object constant_queue_next();
extern Object convert_text_string_to_text();
extern Object copy_out_current_wide_string();
extern Object copy_text_string();
extern Object data_exists_for_plot_p();
extern Object deactivate_for_graph();
extern Object decache_and_remove_all_graph_renderings_from_graph_grid();
extern Object decode_gensym_time();
extern Object delete_all_frame_notes_for_graph();
extern Object delete_eval_element_1();
extern Object delete_frame();
extern Object delete_frame_note_if_any();
extern Object determine_format_for_non_time_axis_label();
extern Object determine_ruling_for_axis();
extern Object determine_ruling_for_time_axis();
extern Object determine_rulings_automatically();
extern Object determine_rulings_based_on_interval();
extern Object draw_graph_grid_current_time_display();
extern Object draw_only_new_data_for_graph_grid();
extern Object enlarge_workspace_for_block_rectangle_if_necessary();
extern Object evaluate_designation();
extern Object expand_plot_data_ring_buffer();
extern Object extend_current_gensym_string();
extern Object future_task_schedule_2();
extern Object generate_float_vector();
extern Object get_history_current_time();
extern Object get_history_element_using_best_search();
extern Object get_history_index_by_binary_search();
extern Object get_instance_with_name_if_any();
extern Object get_lookup_slot_value();
extern Object get_lookup_slot_value_given_default();
extern Object get_or_make_icon_rendering();
extern Object get_or_make_up_designation_for_block();
extern Object get_previous_history_time();
extern Object get_ring_buffer_in_cascade_for_history_time();
extern Object get_slot_description_of_class_description_function();
extern Object get_type_of_slot_if_any();
extern Object get_value_at_history_time();
extern Object get_value_at_history_time_given_variable();
extern Object get_variable_given_graph_expression();
extern Object getfq_function_no_default();
extern Object give_warning_1();
extern Object graph_cons_1();
extern Object graph_must_be_refreshed_for_old_data_qm();
extern Object label_values_same_p();
extern Object low_and_high_values_specified_for_vertical_axis_qm();
extern Object make_format_frame();
extern Object make_frame();
extern Object make_graph();
extern Object make_graph_axis_label();
extern Object make_graph_not_up_to_date();
extern Object make_horizontal_axis_graph_heading_text();
extern Object make_horizontal_axis_graph_heading_text_1();
extern Object make_horizontal_axis_label();
extern Object make_icon_slot_group_1();
extern Object make_new_time_axis_label();
extern Object make_new_variable_axis_label();
extern Object make_or_reformat_graph_grid();
extern Object make_or_reformat_table();
extern Object make_permanent_schedule_task_structure_internal();
extern Object make_plot();
extern Object make_plot_data_ring_buffer_1();
extern Object make_symbol_properties_hash_table_skip_list_sentinel();
extern Object make_text_cell_for_slot();
extern Object make_text_string_for_time_axis_label();
extern Object memq_function();
extern Object mutate_global_property();
extern Object mutate_plot_max_given_plot_min_and_max();
extern Object mutate_plot_min_given_plot_min_and_max();
extern Object need_to_reformat_horizontal_axis_qm();
extern Object need_to_reformat_vertical_axis_qm();
extern Object note_change_to_block_1();
extern Object note_change_to_dependent_frame_1();
extern Object notify_user();
extern Object paint_marker_onto_graph_raster();
extern Object paint_nupec_plot_marker();
extern Object parse_desired_absolute_or_relative_range();
extern Object plot_marker_given_plot();
extern Object plot_min_and_max_given_plot();
extern Object post_reformat_warning_note_for_graph();
extern Object print_day_of_week_and_hour();
extern Object print_hour_and_minute();
extern Object print_minute_and_second();
extern Object print_month_and_date();
extern Object print_month_and_year();
extern Object print_relative_days();
extern Object print_relative_hours();
extern Object print_relative_hours_and_minutes();
extern Object print_relative_weeks();
extern Object put_up_label_for_graph_horizontal_axis();
extern Object put_up_new_high_value_label_for_horizontal_axis();
extern Object put_up_new_labels_for_horizontal_graph_axis();
extern Object put_up_new_labels_for_vertical_graph_axis();
extern Object reclaim_graph_list_1();
extern Object reclaim_plot_marker_indices();
extern Object reclaim_schedule_task_args();
extern Object reclaim_slot_value();
extern Object reclaim_temporary_constant_1();
extern Object rectangle_visible_p();
extern Object reformat_table_in_place();
extern Object refresh_data_for_plots();
extern Object refresh_plot_data_buffer();
extern Object remove_as_subblock_if_necessary();
extern Object remove_axis_labels_from_graph_grid();
extern Object replenish_lookup_cons_pool();
extern Object resize_for_graph_grid();
extern Object restore_graph_to_normal_size();
extern Object round_for_graphs();
extern Object scale_y_data_for_plot();
extern Object scale_y_data_for_plots_if_necessary();
extern Object scalef_function();
extern Object set_edges_of_block();
extern Object set_non_savable_lookup_slot_value();
extern Object set_skip_list_entry();
extern Object set_up_next_plot_marker_if_appropriate_for_new_plot_data();
extern Object set_up_time_and_data_at_current_index();
extern Object single_color_line_drawing_description_p();
extern Object slot_value_cons_1();
extern Object slot_value_list_2();
extern Object slot_value_number_p();
extern Object store_data_to_display_for_enough_pixels_case();
extern Object store_data_to_display_for_more_data_than_pixels_case();
extern Object store_managed_number_or_value_function();
extern Object store_min_and_max_plot_data_points();
extern Object store_new_element_in_plot_function();
extern Object store_new_plot_data_1();
extern Object store_new_plot_data_3();
extern Object store_new_plot_data_4();
extern Object store_new_plot_data_with_scaling();
extern Object store_new_plot_data_without_scaling();
extern Object text_string_p();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_wide_character();
extern Object update_display_for_graph();
extern Object update_images();
extern Object update_images_of_block();
extern Object update_images_of_graph();
extern Object update_images_of_graph_grid_and_data();
extern Object update_images_of_only_new_data_for_graph_grid();
extern Object variable_has_subsecond_history_p();
extern Object withdraw_backward_chaining();
extern Object write_floating_point_number();

#endif

/* variables/constants */
extern Object Available_eval_conses_tail_vector;
extern Object Available_eval_conses_vector;
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
extern Object Available_lookup_conses_tail_vector;
extern Object Available_lookup_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Axis, Qaxis);
extern Object Chain_of_available_schedule_tasks_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm, Qchanging_colors_of_graphic_elements_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Changing_graph_margins_qm, Qchanging_graph_margins_qm);
extern Object Class_description_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_block_of_dependent_frame, Qcurrent_block_of_dependent_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_cascaded_ring_buffer, Qcurrent_cascaded_ring_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_flags, Qcurrent_computation_flags);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_frame, Qcurrent_computation_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_instance, Qcurrent_computation_instance);
DECLARE_VARIABLE_WITH_SYMBOL(Current_data_buffer_for_plot, Qcurrent_data_buffer_for_plot);
DECLARE_VARIABLE_WITH_SYMBOL(Current_g2_time, Qcurrent_g2_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_gensym_string, Qcurrent_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_graph_grid, Qcurrent_graph_grid);
DECLARE_VARIABLE_WITH_SYMBOL(Current_graph_grid_in_minimal_update, Qcurrent_graph_grid_in_minimal_update);
DECLARE_VARIABLE_WITH_SYMBOL(Current_image_x_scale, Qcurrent_image_x_scale);
DECLARE_VARIABLE_WITH_SYMBOL(Current_image_y_scale, Qcurrent_image_y_scale);
DECLARE_VARIABLE_WITH_SYMBOL(Current_index, Qcurrent_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_specific_property_list_property_name, Qcurrent_kb_specific_property_list_property_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_minimal_grid_draw_has_seen_one_image_plane_p, Qcurrent_minimal_grid_draw_has_seen_one_image_plane_p);
DECLARE_VARIABLE_WITH_SYMBOL(Current_plot, Qcurrent_plot);
DECLARE_VARIABLE_WITH_SYMBOL(Current_plot_number, Qcurrent_plot_number);
DECLARE_VARIABLE_WITH_SYMBOL(Current_schedule_task, Qcurrent_schedule_task);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Data_point_value, Qdata_point_value);
extern Object Default_axis_half_range;
extern Object Default_interval_between_vertical_grid_lines;
extern Object Default_number_of_markers;
extern Object Default_number_of_vertical_grid_lines;
DECLARE_VARIABLE_WITH_SYMBOL(Desired_high_value_for_horizontal_axis, Qdesired_high_value_for_horizontal_axis);
DECLARE_VARIABLE_WITH_SYMBOL(Desired_high_value_for_vertical_axis, Qdesired_high_value_for_vertical_axis);
DECLARE_VARIABLE_WITH_SYMBOL(Desired_low_value_for_horizontal_axis, Qdesired_low_value_for_horizontal_axis);
DECLARE_VARIABLE_WITH_SYMBOL(Desired_low_value_for_vertical_axis, Qdesired_low_value_for_vertical_axis);
DECLARE_VARIABLE_WITH_SYMBOL(Erase_dateline, Qerase_dateline);
extern Object Erase_zone_ratio;
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_gensym_string, Qfill_pointer_for_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Finished_storing_in_plot_data_1_qm, Qfinished_storing_in_plot_data_1_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Fixnum_maximum_y_value, Qfixnum_maximum_y_value);
DECLARE_VARIABLE_WITH_SYMBOL(Fixnum_minimum_y_value, Qfixnum_minimum_y_value);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_time_at_start, Qgensym_time_at_start);
DECLARE_VARIABLE_WITH_SYMBOL(Grid_height, Qgrid_height);
DECLARE_VARIABLE_WITH_SYMBOL(Grid_width, Qgrid_width);
DECLARE_VARIABLE_WITH_SYMBOL(Handy_float_1, Qhandy_float_1);
DECLARE_VARIABLE_WITH_SYMBOL(High_value_for_horizontal_grid_lines, Qhigh_value_for_horizontal_grid_lines);
DECLARE_VARIABLE_WITH_SYMBOL(High_value_for_vertical_grid_lines, Qhigh_value_for_vertical_grid_lines);
DECLARE_VARIABLE_WITH_SYMBOL(History_time_per_pixel, Qhistory_time_per_pixel);
DECLARE_VARIABLE_WITH_SYMBOL(History_time_to_evaluate_display_expression_with, Qhistory_time_to_evaluate_display_expression_with);
DECLARE_VARIABLE_WITH_SYMBOL(Horizontal_grid_line_spacing, Qhorizontal_grid_line_spacing);
DECLARE_VARIABLE_WITH_SYMBOL(Index_for_stop_time, Qindex_for_stop_time);
DECLARE_VARIABLE_WITH_SYMBOL(Interval_between_horizontal_grid_lines, Qinterval_between_horizontal_grid_lines);
DECLARE_VARIABLE_WITH_SYMBOL(Interval_between_plot_markers, Qinterval_between_plot_markers);
DECLARE_VARIABLE_WITH_SYMBOL(Interval_between_vertical_grid_lines, Qinterval_between_vertical_grid_lines);
extern Object Isqrt_of_most_positive_fixnum;
DECLARE_VARIABLE_WITH_SYMBOL(Label_scale_for_vertical_grid_lines, Qlabel_scale_for_vertical_grid_lines);
DECLARE_VARIABLE_WITH_SYMBOL(Last_history_time_for_data_point_on_pixel, Qlast_history_time_for_data_point_on_pixel);
extern Object List_of_graph_frame_note_types;
DECLARE_VARIABLE_WITH_SYMBOL(Low_and_high_values_specified_for_vertical_axis_qm, Qlow_and_high_values_specified_for_vertical_axis_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Low_value_for_horizontal_axis, Qlow_value_for_horizontal_axis);
DECLARE_VARIABLE_WITH_SYMBOL(Low_value_for_horizontal_grid_lines, Qlow_value_for_horizontal_grid_lines);
DECLARE_VARIABLE_WITH_SYMBOL(Low_value_for_vertical_axis, Qlow_value_for_vertical_axis);
DECLARE_VARIABLE_WITH_SYMBOL(Low_value_for_vertical_grid_lines, Qlow_value_for_vertical_grid_lines);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Managed_array_unique_marker;
DECLARE_VARIABLE_WITH_SYMBOL(Many_more_data_points_than_pixels_qm, Qmany_more_data_points_than_pixels_qm);
extern Object Maximum_in_place_array_size;
extern Object Maximum_number_of_horizontal_grid_lines;
DECLARE_VARIABLE_WITH_SYMBOL(Maximum_y_value, Qmaximum_y_value);
DECLARE_VARIABLE_WITH_SYMBOL(Maximum_y_value_for_pixel, Qmaximum_y_value_for_pixel);
DECLARE_VARIABLE_WITH_SYMBOL(Minimum_and_maximum_y_value_set_qm, Qminimum_and_maximum_y_value_set_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Minimum_grid_height, Qminimum_grid_height);
extern Object Minimum_grid_height_for_resizing_graph;
DECLARE_VARIABLE_WITH_SYMBOL(Minimum_grid_width, Qminimum_grid_width);
extern Object Minimum_grid_width_for_resizing_graph;
extern Object Minimum_range_to_maximum_value_ratio;
DECLARE_VARIABLE_WITH_SYMBOL(Minimum_y_value, Qminimum_y_value);
DECLARE_VARIABLE_WITH_SYMBOL(Minimum_y_value_for_pixel, Qminimum_y_value_for_pixel);
extern Object Minus_of_isqrt_of_most_positive_fixnum;
extern Object Most_negative_gensym_float;
extern Object Most_positive_gensym_float;
DECLARE_VARIABLE_WITH_SYMBOL(Most_recent_extremum_maximum_for_pixel_p, Qmost_recent_extremum_maximum_for_pixel_p);
DECLARE_VARIABLE_WITH_SYMBOL(Most_recent_extremum_maximum_p, Qmost_recent_extremum_maximum_p);
extern Object No_specific_property_value;
DECLARE_VARIABLE_WITH_SYMBOL(No_value, Qno_value);
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_horizontal_grid_lines, Qnumber_of_horizontal_grid_lines);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_vertical_grid_lines, Qnumber_of_vertical_grid_lines);
extern Object Offset_ratio_for_plot_markers;
DECLARE_VARIABLE_WITH_SYMBOL(Painting_for_graph_activation_p, Qpainting_for_graph_activation_p);
DECLARE_VARIABLE_WITH_SYMBOL(Parameter_class_description, Qparameter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Plot_marker_qm, Qplot_marker_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Plot_max_qm, Qplot_max_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Plot_min_and_max_qm, Qplot_min_and_max_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Plot_min_qm, Qplot_min_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Previous_cascaded_ring_buffer_accessed, Qprevious_cascaded_ring_buffer_accessed);
DECLARE_VARIABLE_WITH_SYMBOL(Previous_index_for_ring_buffer, Qprevious_index_for_ring_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Problems_reformatting_graph_qm, Qproblems_reformatting_graph_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Range_too_small_qm, Qrange_too_small_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Redraw_as_well_as_reformat_p, Qredraw_as_well_as_reformat_p);
DECLARE_VARIABLE_WITH_SYMBOL(Region_invalidation_is_preferred, Qregion_invalidation_is_preferred);
DECLARE_VARIABLE_WITH_SYMBOL(Ring_buffer_for_history_time, Qring_buffer_for_history_time);
DECLARE_VARIABLE_WITH_SYMBOL(Scale_y_data_points_qm, Qscale_y_data_points_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
extern Object Smallest_ring_buffer_vector_size;
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
extern Object Symbol_properties_table;
DECLARE_VARIABLE_WITH_SYMBOL(System_has_paused, Qsystem_has_paused);
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_gensym_string, Qtotal_length_of_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Transfer_in_progress, Qtransfer_in_progress);
DECLARE_VARIABLE_WITH_SYMBOL(Variable_class_description, Qvariable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Variable_or_parameter_class_description, Qvariable_or_parameter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Variables_that_did_not_have_values, Qvariables_that_did_not_have_values);
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
DECLARE_VARIABLE_WITH_SYMBOL(Vertical_axis_range, Qvertical_axis_range);
DECLARE_VARIABLE_WITH_SYMBOL(Vertical_grid_line_spacing, Qvertical_grid_line_spacing);
DECLARE_VARIABLE_WITH_SYMBOL(Warning_message_level, Qwarning_message_level);
DECLARE_VARIABLE_WITH_SYMBOL(Working_on_lexical_computation_of_frame, Qworking_on_lexical_computation_of_frame);
DECLARE_VARIABLE_WITH_SYMBOL(X_data_min_set_qm, Qx_data_min_set_qm);
DECLARE_VARIABLE_WITH_SYMBOL(X_value_on_graph, Qx_value_on_graph);
