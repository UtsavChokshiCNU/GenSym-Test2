/* icons5.h -- Header File for icons5.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
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

extern Object abort_current_workstation_context(Object);
extern Object add_keymap_to_workstation_context(Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object any_mouse_up_or_down_in_bounding_box_state(Object);
extern Object bounding_box_state_structure_memory_usage(void);
extern Object bytes_per_simple_vector(Object);
extern Object change_slot_value(int,...);
extern Object clear_optimized_constants(void);
extern Object color_or_metacolor_p(Object);
extern Object convert_line_drawing_description_to_list_of_layers(Object,Object,Object);
extern Object copy_drawing_element_with_icon_editor_conses(Object,Object,Object);
extern Object copy_of_current_frame_serial_number_function(void);
extern Object copy_out_current_wide_string(void);
extern Object copy_tree_including_leaves_using_icon_editor_conses(Object);
extern Object create_icon_editor(Object);
extern Object delete_icon_editor_main_color_menu(Object);
extern Object direct_structure_method(Object,Object);
extern Object edit_attribute_table_slot_in_place(int,...);
extern Object enqueue_icon_editor_engine_event(Object,Object,Object,Object,Object,Object);
extern Object enqueue_icon_editor_translator_event(Object,Object,Object,Object);
extern Object enqueue_icon_editor_translator_event_on_return(Object);
extern Object enter_button_down_context(Object,Object);
extern Object enter_context_in_current_workstation(int,...);
extern Object enter_icon_editor(Object);
extern Object establish_next_workstation_context_continuation(Object,Object,Object,Object);
extern Object event_blackboard_function(Object);
extern Object execute_icon_editor_mouse_down_event(Object,Object,Object);
extern Object execute_icon_editor_mouse_down_in_view_pad(Object,Object,Object,Object,Object,Object,Object);
extern Object execute_icon_editor_workstation_event(Object,Object);
extern Object exit_current_workstation_context_in_return_function(Object);
extern Object find_frame_of_class_in_mouse_pointer(Object,Object);
extern Object find_object_near_mouse(Object,Object,Object,Object,Object);
extern Object finish_doing_icon_editor_type_in(Object);
extern Object finish_moving_bounding_box_for_icon_editor(Object);
extern Object frame_serial_number_setf_helper_1(Object,Object);
extern Object get_icon_stipple_if_any(Object);
extern Object get_inherited_background_image(Object);
extern Object get_inherited_drawing_description(Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object get_slot_represented_by_text_cell_if_any(Object);
extern Object get_ui_parameter(int,...);
extern Object get_variable_specification_if_any(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object handle_icon_editor_visual_event(Object,Object,Object,Object);
extern Object handle_menu_choice_for_layer_color(Object,Object,Object,Object);
extern Object icon_editor_cons_1(Object,Object);
extern Object icon_editor_list_2(Object,Object);
extern Object image_of_layer_qm(Object);
extern Object inform_user_of_current_regions(Object);
extern Object inverse_scalef_function(Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object make_bounding_box_state_1(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_context_description(Object,Object,Object,Object);
extern Object make_keymap(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_permanent_bounding_box_state_structure_internal(void);
extern Object make_thread_array(Object);
extern Object memq_function(Object,Object);
extern Object mouse_gesture_on_image_plane_icon_editor(Object);
extern Object mouse_motion_in_bounding_box_state(Object);
extern Object mouse_pointer_blackboard_function(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object new_icon_layer(Object,Object,Object,Object);
extern Object outstanding_bounding_box_state_count(void);
extern Object pick_cell_from_table(int,...);
extern Object point_in_view_pad_p(Object,Object,Object);
extern Object post_full_color_menu(Object,Object,Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object put_workspace_on_pane_function(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object reclaim_bounding_box_state_1(Object);
extern Object reclaim_frame_serial_number(Object);
extern Object reclaim_icon_editor_slot_value(Object);
extern Object reclaim_slot_value_list_1(Object);
extern Object recompute_scale_for_layers_pad(Object);
extern Object recompute_view_pad_size(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object release_mouse_pointers(Object);
extern Object return_from_current_workstation_context(int,...);
extern Object run_top_level_event_handler(Object);
extern Object select_edge_or_corner_of_bounding_box(int,...);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object slot_value_cons_1(Object,Object);
extern Object slot_value_list_2(Object,Object);
extern Object some_event_in_icon_editor(Object);
extern Object stipple_of_layer_qm(Object);
extern Object text_of_layer_qm(Object);
extern Object tformat(int,...);
extern Object type_of_slot_if_editable(int,...);
extern Object update_border_of_bounding_box(Object,Object,Object,Object,Object);
extern Object update_moving_bounding_box_for_icon_editor(Object,Object,Object);
extern Object update_moving_bounding_box_with_expanded_arguments(Object,Object,Object,Object);
extern Object update_object_pool_meters_list(Object);
extern Object workstation_context_specifics_blackboard_function(Object);
extern Object write_stipple_specification(Object);
extern Object write_text_specification(Object);
extern Object x_in_window_blackboard_function(Object);
extern Object x_in_workspace_blackboard_function(Object);
extern Object y_in_window_blackboard_function(Object);
extern Object y_in_workspace_blackboard_function(Object);

#else

extern Object abort_current_workstation_context();
extern Object add_keymap_to_workstation_context();
extern Object allocate_byte_vector_16();
extern Object any_mouse_up_or_down_in_bounding_box_state();
extern Object bounding_box_state_structure_memory_usage();
extern Object bytes_per_simple_vector();
extern Object change_slot_value();
extern Object clear_optimized_constants();
extern Object color_or_metacolor_p();
extern Object convert_line_drawing_description_to_list_of_layers();
extern Object copy_drawing_element_with_icon_editor_conses();
extern Object copy_of_current_frame_serial_number_function();
extern Object copy_out_current_wide_string();
extern Object copy_tree_including_leaves_using_icon_editor_conses();
extern Object create_icon_editor();
extern Object delete_icon_editor_main_color_menu();
extern Object direct_structure_method();
extern Object edit_attribute_table_slot_in_place();
extern Object enqueue_icon_editor_engine_event();
extern Object enqueue_icon_editor_translator_event();
extern Object enqueue_icon_editor_translator_event_on_return();
extern Object enter_button_down_context();
extern Object enter_context_in_current_workstation();
extern Object enter_icon_editor();
extern Object establish_next_workstation_context_continuation();
extern Object event_blackboard_function();
extern Object execute_icon_editor_mouse_down_event();
extern Object execute_icon_editor_mouse_down_in_view_pad();
extern Object execute_icon_editor_workstation_event();
extern Object exit_current_workstation_context_in_return_function();
extern Object find_frame_of_class_in_mouse_pointer();
extern Object find_object_near_mouse();
extern Object finish_doing_icon_editor_type_in();
extern Object finish_moving_bounding_box_for_icon_editor();
extern Object frame_serial_number_setf_helper_1();
extern Object get_icon_stipple_if_any();
extern Object get_inherited_background_image();
extern Object get_inherited_drawing_description();
extern Object get_lookup_slot_value_given_default();
extern Object get_slot_description_of_class_description_function();
extern Object get_slot_represented_by_text_cell_if_any();
extern Object get_ui_parameter();
extern Object get_variable_specification_if_any();
extern Object getfq_function_no_default();
extern Object handle_icon_editor_visual_event();
extern Object handle_menu_choice_for_layer_color();
extern Object icon_editor_cons_1();
extern Object icon_editor_list_2();
extern Object image_of_layer_qm();
extern Object inform_user_of_current_regions();
extern Object inverse_scalef_function();
extern Object load_and_initialize_type_description();
extern Object lookup_global_or_kb_specific_property_value();
extern Object make_bounding_box_state_1();
extern Object make_context_description();
extern Object make_keymap();
extern Object make_permanent_bounding_box_state_structure_internal();
extern Object make_thread_array();
extern Object memq_function();
extern Object mouse_gesture_on_image_plane_icon_editor();
extern Object mouse_motion_in_bounding_box_state();
extern Object mouse_pointer_blackboard_function();
extern Object mutate_global_property();
extern Object new_icon_layer();
extern Object outstanding_bounding_box_state_count();
extern Object pick_cell_from_table();
extern Object point_in_view_pad_p();
extern Object post_full_color_menu();
extern Object push_optimized_constant();
extern Object put_workspace_on_pane_function();
extern Object reclaim_bounding_box_state_1();
extern Object reclaim_frame_serial_number();
extern Object reclaim_icon_editor_slot_value();
extern Object reclaim_slot_value_list_1();
extern Object recompute_scale_for_layers_pad();
extern Object recompute_view_pad_size();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object release_mouse_pointers();
extern Object return_from_current_workstation_context();
extern Object run_top_level_event_handler();
extern Object select_edge_or_corner_of_bounding_box();
extern Object set_non_savable_lookup_slot_value();
extern Object slot_value_cons_1();
extern Object slot_value_list_2();
extern Object some_event_in_icon_editor();
extern Object stipple_of_layer_qm();
extern Object text_of_layer_qm();
extern Object tformat();
extern Object type_of_slot_if_editable();
extern Object update_border_of_bounding_box();
extern Object update_moving_bounding_box_for_icon_editor();
extern Object update_moving_bounding_box_with_expanded_arguments();
extern Object update_object_pool_meters_list();
extern Object workstation_context_specifics_blackboard_function();
extern Object write_stipple_specification();
extern Object write_text_specification();
extern Object x_in_window_blackboard_function();
extern Object x_in_workspace_blackboard_function();
extern Object y_in_window_blackboard_function();
extern Object y_in_workspace_blackboard_function();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Bounding_box_state_count, Qbounding_box_state_count);
DECLARE_VARIABLE_WITH_SYMBOL(Button_class_description, Qbutton_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_bounding_box_states, Qchain_of_available_bounding_box_states);
extern Object Chain_of_available_bounding_box_states_vector;
extern Object Class_definition_gkbprop;
extern Object Class_description_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_serial_number, Qcurrent_frame_serial_number);
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_transform_qm, Qcurrent_frame_transform_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icon_editor, Qcurrent_icon_editor);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icon_editor_event, Qcurrent_icon_editor_event);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icon_editor_workspace, Qcurrent_icon_editor_workspace);
DECLARE_VARIABLE_WITH_SYMBOL(Current_image_plane_qm, Qcurrent_image_plane_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_image_x_scale, Qcurrent_image_x_scale);
DECLARE_VARIABLE_WITH_SYMBOL(Current_image_y_scale, Qcurrent_image_y_scale);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workspace_on_image_plane_qm, Qcurrent_workspace_on_image_plane_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation, Qcurrent_workstation);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation_detail_pane, Qcurrent_workstation_detail_pane);
DECLARE_VARIABLE_WITH_SYMBOL(Current_x_origin_of_drawing, Qcurrent_x_origin_of_drawing);
DECLARE_VARIABLE_WITH_SYMBOL(Current_y_origin_of_drawing, Qcurrent_y_origin_of_drawing);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
extern Object Isqrt_of_most_positive_fixnum;
extern Object Minus_of_isqrt_of_most_positive_fixnum;
DECLARE_VARIABLE_WITH_SYMBOL(New_g2_classic_ui_p, Qnew_g2_classic_ui_p);
DECLARE_VARIABLE_WITH_SYMBOL(Specific_structure_for_current_workstation_context, Qspecific_structure_for_current_workstation_context);
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
DECLARE_VARIABLE_WITH_SYMBOL(Table_class_description, Qtable_class_description);
extern Object The_type_description_of_bounding_box_state;
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
