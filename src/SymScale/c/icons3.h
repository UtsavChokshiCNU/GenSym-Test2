/* icons3.h -- Header File for icons3.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qplus;
extern Object Qspecial;
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

extern Object add_to_workspace(int,...);
extern Object calculate_center_and_radius_of_circle(Object,Object,Object,Object,Object,Object);
extern Object clear_icon_editor_translator_state_information(Object);
extern Object clip_x_in_workspace_to_engine(Object,Object,Object);
extern Object clip_y_in_workspace_to_engine(Object,Object,Object);
extern Object compute_arc_bounding_box(Object,Object,Object,Object,Object,Object);
extern Object compute_bounded_point_in_workspace(Object,Object,Object,Object,Object);
extern Object compute_edges_for_text_drawing_element(Object);
extern Object compute_maximum_and_minimum_bounds_for_layer(Object,Object,Object,Object);
extern Object compute_maximums_and_minimums_for_drawing_elements(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object compute_maximums_and_minimums_for_points(Object,Object,Object,Object,Object);
extern Object convert_list_of_layers_to_line_drawing_description(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object copy_constant_wide_string_given_length(Object,Object);
extern Object copy_list_using_icon_editor_conses_1(Object);
extern Object create_and_place_icon_of_current_layer_for_view_pad(Object,Object,Object,Object,Object);
extern Object delete_icon_editor_view_pad_icon_for_current_layer(Object);
extern Object enqueue_icon_editor_engine_event(Object,Object,Object,Object,Object,Object);
extern Object enqueue_icon_editor_translator_event(Object,Object,Object,Object);
extern Object enqueue_icon_editor_translator_state_information(Object,Object);
extern Object find_image_data(Object);
extern Object frame_serial_number_setf_helper_1(Object,Object);
extern Object get_color_of_region_in_icon_editor(Object,Object);
extern Object handle_icon_editor_visual_event(Object,Object,Object,Object);
extern Object handle_layers_pad_translator_event(Object,Object,Object,Object);
extern Object handle_mouse_motion_for_moving_layer(Object,Object,Object,Object,Object,Object,Object);
extern Object handle_move_layer_in_xy_plane_in_translator(Object,Object);
extern Object handle_translator_view_pad_mouse_down_event(Object,Object,Object,Object,Object,Object);
extern Object icon_editor_cons_1(Object,Object);
extern Object icon_editor_list_2(Object,Object);
extern Object inverse_scalef_function(Object,Object);
extern Object make_entity_with_icon_description_for_moving_layer(Object,Object,Object,Object,Object);
extern Object make_entity_with_specific_icon_description(int,...);
extern Object move_blocks_with_their_external_connections(Object,Object,Object,Object);
extern Object point_in_draw_area_of_view_pad_p(Object,Object,Object,Object);
extern Object pop_icon_editor_translator_state_information(Object);
extern Object pop_last_marker_if_drawn(Object,Object);
extern Object push_icon_editor_translator_state_information(Object,Object);
extern Object reclaim_icon_editor_cons_1(Object);
extern Object reclaim_icon_editor_slot_value(Object);
extern Object reclaim_icon_editor_tree_1(Object);
extern Object scalef_function(Object,Object);
extern Object simple_eval_for_icon(Object);
extern Object snap_to_limits_of_width_and_height_if_necessary(Object,Object,Object,Object);
extern Object translator_cancel_current_state(Object,Object,Object,Object);
extern Object translator_end_current_state(int,...);
extern Object translator_end_moving_layer_in_xy_plane(Object,Object,Object);

#else

extern Object add_to_workspace();
extern Object calculate_center_and_radius_of_circle();
extern Object clear_icon_editor_translator_state_information();
extern Object clip_x_in_workspace_to_engine();
extern Object clip_y_in_workspace_to_engine();
extern Object compute_arc_bounding_box();
extern Object compute_bounded_point_in_workspace();
extern Object compute_edges_for_text_drawing_element();
extern Object compute_maximum_and_minimum_bounds_for_layer();
extern Object compute_maximums_and_minimums_for_drawing_elements();
extern Object compute_maximums_and_minimums_for_points();
extern Object convert_list_of_layers_to_line_drawing_description();
extern Object copy_constant_wide_string_given_length();
extern Object copy_list_using_icon_editor_conses_1();
extern Object create_and_place_icon_of_current_layer_for_view_pad();
extern Object delete_icon_editor_view_pad_icon_for_current_layer();
extern Object enqueue_icon_editor_engine_event();
extern Object enqueue_icon_editor_translator_event();
extern Object enqueue_icon_editor_translator_state_information();
extern Object find_image_data();
extern Object frame_serial_number_setf_helper_1();
extern Object get_color_of_region_in_icon_editor();
extern Object handle_icon_editor_visual_event();
extern Object handle_layers_pad_translator_event();
extern Object handle_mouse_motion_for_moving_layer();
extern Object handle_move_layer_in_xy_plane_in_translator();
extern Object handle_translator_view_pad_mouse_down_event();
extern Object icon_editor_cons_1();
extern Object icon_editor_list_2();
extern Object inverse_scalef_function();
extern Object make_entity_with_icon_description_for_moving_layer();
extern Object make_entity_with_specific_icon_description();
extern Object move_blocks_with_their_external_connections();
extern Object point_in_draw_area_of_view_pad_p();
extern Object pop_icon_editor_translator_state_information();
extern Object pop_last_marker_if_drawn();
extern Object push_icon_editor_translator_state_information();
extern Object reclaim_icon_editor_cons_1();
extern Object reclaim_icon_editor_slot_value();
extern Object reclaim_icon_editor_tree_1();
extern Object scalef_function();
extern Object simple_eval_for_icon();
extern Object snap_to_limits_of_width_and_height_if_necessary();
extern Object translator_cancel_current_state();
extern Object translator_end_current_state();
extern Object translator_end_moving_layer_in_xy_plane();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_serial_number, Qcurrent_frame_serial_number);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icon_untransformed_height, Qcurrent_icon_untransformed_height);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icon_untransformed_width, Qcurrent_icon_untransformed_width);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icon_variables_override_plist, Qcurrent_icon_variables_override_plist);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icon_variables_plist, Qcurrent_icon_variables_plist);
DECLARE_VARIABLE_WITH_SYMBOL(Distance_to_snap_points_together_in_view_pad, Qdistance_to_snap_points_together_in_view_pad);
extern Object Isqrt_of_most_positive_fixnum;
extern Object Minus_of_isqrt_of_most_positive_fixnum;
