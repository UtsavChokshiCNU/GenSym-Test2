/* kbsv2.h -- Header File for kbsv2.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
extern Object Knewest;
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

extern Object ab_member_equal(Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object any_wild_pathnames_p(Object);
extern Object assq_function(Object,Object);
extern Object change_color_of_icon(Object,Object,Object);
extern Object change_color_of_text_box(int,...);
extern Object change_color_of_workspace(Object,Object,Object,Object);
extern Object change_color_pattern_of_connection(Object,Object,Object);
extern Object change_color_pattern_of_icon(Object,Object,Object);
extern Object change_slot_value(int,...);
extern Object check_denotation_well_defined(Object,Object);
extern Object check_pane_description_for_unwritten_workspaces(Object);
extern Object check_savability_of_kb_in_terms_of_modularity(int,...);
extern Object check_table_for_entanglement(Object);
extern Object clear_all_twng_disconnect_callbacks(void);
extern Object clear_base_name_from_default_load_pathnames(void);
extern Object clear_inspect_command_history_list(void);
extern Object clear_kb(int,...);
extern Object close_logbooks(void);
extern Object collect_subclasses(Object);
extern Object completely_shut_down_g2(int,...);
extern Object constant_queue_next(Object,Object);
extern Object convert_text_string_to_text(Object);
extern Object convert_to_magnification(Object);
extern Object copy_denotation(Object);
extern Object copy_for_slot_value(Object);
extern Object copy_frame_serial_number(Object);
extern Object copy_if_evaluation_value_1(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text(Object);
extern Object copy_text_string(Object);
extern Object copy_tree_using_slot_value_conses_1(Object);
extern Object create_pseudo_frame(Object);
extern Object delete_classes_queued_by_delete_frame(Object);
extern Object delete_frame(Object);
extern Object delete_frame_list(Object);
extern Object delete_image_plane(Object);
extern Object delete_slot_value_element_1(Object,Object);
extern Object denotations_of_slots_given_state_change_name(Object,Object);
extern Object denote_slot_using_slot_value_conses(Object,Object);
extern Object detail_pane(Object);
extern Object determine_extreme_edges_of_workspace_subblocks(Object);
extern Object display_credits(int,...);
extern Object do_g2_init_file(void);
extern Object do_g2_kb_load_at_launch(void);
extern Object empty_kb_p(void);
extern Object force_process_drawing(void);
extern Object frame_serial_number_0(void);
extern Object frame_serial_number_setf_helper_1(Object,Object);
extern Object g2_array_length_function(Object);
extern Object g2_initialize_gsi_interface(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2_stream_close(Object);
extern Object g2_stream_open_for_input(Object);
extern Object g2_stream_read_line(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_3(Object,Object,Object);
extern Object gensym_make_pathname_with_copied_components(Object,Object,Object,Object,Object,Object,Object);
extern Object gensym_merge_pathnames_function(Object,Object,Object);
extern Object gensym_namestring(int,...);
extern Object gensym_pathname(Object);
extern Object gensym_wild_pathname_p(Object);
extern Object get_available_image_plane(Object,Object,Object);
extern Object get_color_pattern_of_item(int,...);
extern Object get_command_line_flag_argument(int,...);
extern Object get_connection_color_pattern(int,...);
extern Object get_current_user_name(void);
extern Object get_error_string_for_illegal_wildcards_in_filename(Object);
extern Object get_gensym_environment_variable(Object);
extern Object get_gensym_window_parameter(Object,Object);
extern Object get_icon_color_pattern(int,...);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_module_block_is_in(Object);
extern Object get_or_make_up_designation_for_block(Object);
extern Object get_or_use_g2_init_pathname(int,...);
extern Object get_or_use_g2_kb_pathname(int,...);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object get_slot_description_value(Object,Object);
extern Object get_slot_represented_by_text_cell_if_any(Object);
extern Object get_slot_value_function(Object,Object,Object);
extern Object get_slot_value_if_any_function(Object,Object,Object);
extern Object get_slots_to_save_in_clear_kb_for_representation(Object);
extern Object get_text_box_color_pattern(int,...);
extern Object get_value_for_current_workstation_new_g2_classic_ui_p(void);
extern Object get_workspace_color_pattern(int,...);
extern Object getfq_function_no_default(Object,Object);
extern Object give_warning_1(int,...);
extern Object identify_all_savable_kb_workspaces(void);
extern Object import_text_string(int,...);
extern Object increment_current_frame_serial_number(void);
extern Object inform_ui_client_interface_of_module_creation(Object,Object);
extern Object inform_ui_client_interfaces_of_clear_kb(void);
extern Object initialize_current_kb_serial_number(void);
extern Object initialize_default_g2_init_pathname(void);
extern Object initializer_for_pathname_for_disabling_g2_init_command_line(void);
extern Object initializer_for_pathname_for_disabling_g2_kb_command_line(void);
extern Object install_subscription(Object,Object,Object,Object);
extern Object inverse_scalef_function(Object,Object);
extern Object invert_reflection_and_rotation(Object);
extern Object item_x_position(Object);
extern Object item_y_position(Object);
extern Object kb_is_savable_p(void);
extern Object kb_property_cons_1(Object,Object);
extern Object lookup_frame_description_reference_of_block_qm(Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_command_frame(int,...);
extern Object make_default_file_type(Object);
extern Object make_frame(Object);
extern Object make_gensym_list_1(Object);
extern Object make_image_plane_description(Object,Object);
extern Object make_or_clear_complete_kb_name(int,...);
extern Object make_original_value_for_text_box_font_kb_state_change(Object);
extern Object make_pane_description(Object,Object,Object,Object);
extern Object make_pseudo_frame_1(Object,Object);
extern Object make_slot_value_list_1(Object);
extern Object make_storage_of_representation_data(Object);
extern Object make_text_representation_for_slot_description_value(Object,Object);
extern Object make_ui_client_session_internal(void);
extern Object mark_kb_workspace_if_savable(Object);
extern Object memq_function(Object,Object);
extern Object modify_pane_description(Object);
extern Object move_icon(Object,Object,Object);
extern Object move_item_by(int,...);
extern Object multiply_reflection_and_rotation(Object,Object);
extern Object new_change_workspace_edges(Object,Object,Object,Object,Object);
extern Object note_as_frame_with_kb_state_changes(Object);
extern Object note_change_to_block_1(Object,Object);
extern Object note_gensym_window_initialized(Object);
extern Object note_kb_state_change(Object,Object);
extern Object note_kb_state_change_to_slot_by_saving_text(Object,Object);
extern Object note_permanent_change(Object,Object);
extern Object note_permanent_change_to_component(Object,Object,Object,Object);
extern Object note_permanent_change_to_slot_group_for_block(Object);
extern Object note_permanent_changes(Object,Object);
extern Object note_progress(int,...);
extern Object note_saving_frame(Object);
extern Object notify_user(int,...);
extern Object notify_user_of_autostart_and_reason(Object);
extern Object orphan_workspace_p(Object);
extern Object parent(Object);
extern Object parent_variable_function(Object);
extern Object parse_text_for_slot(int,...);
extern Object permanently_retract_consistency_analysis(Object);
extern Object provide_pathname_for_launch_time_load(Object,Object,Object,Object,Object,Object);
extern Object put_image_on_image_plane(int,...);
extern Object put_workspace_into_detail_pane_layout(Object);
extern Object put_workspace_into_detail_panes(Object);
extern Object put_workspace_on_detail_panes_now_or_later(Object);
extern Object put_workspace_on_pane_function(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object read_kb_or_group_thereof(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object reason_to_exclude_slot_description_for_compute_class_description_node_attributes(Object);
extern Object reclaim_frame_serial_number(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_pathname(Object);
extern Object reclaim_kb_property_cons_1(Object);
extern Object reclaim_kb_property_list_1(Object);
extern Object reclaim_kb_specific_properties(Object);
extern Object reclaim_modified_pane_description(Object);
extern Object reclaim_pathname_or_string(Object);
extern Object reclaim_pseudo_frame_1(Object);
extern Object reclaim_slot_value(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_values_of_kb_specific_variables(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object reject_save_kb_if_filename_problems(Object);
extern Object reject_save_kb_if_not_authorized(void);
extern Object reject_save_kb_if_not_savable(void);
extern Object reject_save_kb_if_run_time_only(Object);
extern Object reject_save_kb_if_save_or_backup_in_progress(void);
extern Object reject_save_kb_if_saving_modules_without_consistency(void);
extern Object release_all_kb_write_locks(void);
extern Object release_kb(Object,Object,Object,Object);
extern Object remove_as_frame_with_kb_state_changes(Object);
extern Object remove_kb_state_changes(Object);
extern Object remove_kb_state_variable_record(Object,Object);
extern Object require_that_image_plane_be_visible(int,...);
extern Object reset_current_frame_serial_number(void);
extern Object restore_current_workstation_detail_pane(int,...);
extern Object restore_icp_object_map_for_registered_item(Object,Object);
extern Object restore_image_planes_to_pane(int,...);
extern Object restore_image_planes_to_pane_now_or_later(int,...);
extern Object restore_original_value_for_text_box_font_kb_state_change(Object,Object);
extern Object restore_ui_client_interfaces(void);
extern Object restore_ui_client_session_item_representation(Object,Object);
extern Object restore_ui_client_session_item_representations(Object,Object);
extern Object rotate_and_reflect_icon(Object,Object,Object,Object,Object,Object);
extern Object run_state_change_hook(Object);
extern Object savable_block_p(Object);
extern Object savable_computation_style_p(Object);
extern Object save_and_delete_ui_client_interfaces(void);
extern Object save_icp_object_map_for_registered_item(Object);
extern Object send_ws_representations_item_color_pattern_change(Object,Object,Object);
extern Object send_ws_representations_item_moved(Object,Object,Object);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object set_slot_value_function(Object,Object,Object,Object);
extern Object set_window_title(Object,Object);
extern Object shut_down_g2ds_clients_for_clear_kb(void);
extern Object slot_value_cons_1(Object,Object);
extern Object slot_value_is_permanent_p(Object,Object);
extern Object slot_value_list_2(Object,Object);
extern Object slot_value_list_4(Object,Object,Object,Object);
extern Object start_kb_after_load_from_system_table_qm(void);
extern Object store_callback_representation(Object);
extern Object string_equalw(Object,Object);
extern Object superior_frame(Object);
extern Object switch_to_kb(Object);
extern Object switch_to_new_empty_kb(void);
extern Object system_reset(void);
extern Object system_start(void);
extern Object text_string_length(Object);
extern Object text_string_p(Object);
extern Object text_string_trim(Object,Object);
extern Object tformat(int,...);
extern Object tformat_text_string(int,...);
extern Object try_to_do_deferred_user_notifications(void);
extern Object undo_kb_state_changes(void);
extern Object undo_kb_state_changes_for_frame(Object);
extern Object unedit_up_to_date_modules(void);
extern Object unwind_current_workstation_back_to_top_level(void);
extern Object update_connection_images(Object,Object,Object);
extern Object wide_character_member(Object,Object);
extern Object workspaces_can_be_shown_at_this_kb_level_p(Object,Object);
extern Object write_list_in_chicago_style(int,...);
extern Object write_list_of_forced_names(Object);
extern Object write_problems_saving_kb(Object,Object,Object);

#else

extern Object ab_member_equal();
extern Object allocate_byte_vector_16();
extern Object any_wild_pathnames_p();
extern Object assq_function();
extern Object change_color_of_icon();
extern Object change_color_of_text_box();
extern Object change_color_of_workspace();
extern Object change_color_pattern_of_connection();
extern Object change_color_pattern_of_icon();
extern Object change_slot_value();
extern Object check_denotation_well_defined();
extern Object check_pane_description_for_unwritten_workspaces();
extern Object check_savability_of_kb_in_terms_of_modularity();
extern Object check_table_for_entanglement();
extern Object clear_all_twng_disconnect_callbacks();
extern Object clear_base_name_from_default_load_pathnames();
extern Object clear_inspect_command_history_list();
extern Object clear_kb();
extern Object close_logbooks();
extern Object collect_subclasses();
extern Object completely_shut_down_g2();
extern Object constant_queue_next();
extern Object convert_text_string_to_text();
extern Object convert_to_magnification();
extern Object copy_denotation();
extern Object copy_for_slot_value();
extern Object copy_frame_serial_number();
extern Object copy_if_evaluation_value_1();
extern Object copy_out_current_wide_string();
extern Object copy_text();
extern Object copy_text_string();
extern Object copy_tree_using_slot_value_conses_1();
extern Object create_pseudo_frame();
extern Object delete_classes_queued_by_delete_frame();
extern Object delete_frame();
extern Object delete_frame_list();
extern Object delete_image_plane();
extern Object delete_slot_value_element_1();
extern Object denotations_of_slots_given_state_change_name();
extern Object denote_slot_using_slot_value_conses();
extern Object detail_pane();
extern Object determine_extreme_edges_of_workspace_subblocks();
extern Object display_credits();
extern Object do_g2_init_file();
extern Object do_g2_kb_load_at_launch();
extern Object empty_kb_p();
extern Object force_process_drawing();
extern Object frame_serial_number_0();
extern Object frame_serial_number_setf_helper_1();
extern Object g2_array_length_function();
extern Object g2_initialize_gsi_interface();
extern Object g2_stream_close();
extern Object g2_stream_open_for_input();
extern Object g2_stream_read_line();
extern Object gensym_cons_1();
extern Object gensym_list_3();
extern Object gensym_make_pathname_with_copied_components();
extern Object gensym_merge_pathnames_function();
extern Object gensym_namestring();
extern Object gensym_pathname();
extern Object gensym_wild_pathname_p();
extern Object get_available_image_plane();
extern Object get_color_pattern_of_item();
extern Object get_command_line_flag_argument();
extern Object get_connection_color_pattern();
extern Object get_current_user_name();
extern Object get_error_string_for_illegal_wildcards_in_filename();
extern Object get_gensym_environment_variable();
extern Object get_gensym_window_parameter();
extern Object get_icon_color_pattern();
extern Object get_lookup_slot_value_given_default();
extern Object get_module_block_is_in();
extern Object get_or_make_up_designation_for_block();
extern Object get_or_use_g2_init_pathname();
extern Object get_or_use_g2_kb_pathname();
extern Object get_slot_description_of_class_description_function();
extern Object get_slot_description_value();
extern Object get_slot_represented_by_text_cell_if_any();
extern Object get_slot_value_function();
extern Object get_slot_value_if_any_function();
extern Object get_slots_to_save_in_clear_kb_for_representation();
extern Object get_text_box_color_pattern();
extern Object get_value_for_current_workstation_new_g2_classic_ui_p();
extern Object get_workspace_color_pattern();
extern Object getfq_function_no_default();
extern Object give_warning_1();
extern Object identify_all_savable_kb_workspaces();
extern Object import_text_string();
extern Object increment_current_frame_serial_number();
extern Object inform_ui_client_interface_of_module_creation();
extern Object inform_ui_client_interfaces_of_clear_kb();
extern Object initialize_current_kb_serial_number();
extern Object initialize_default_g2_init_pathname();
extern Object initializer_for_pathname_for_disabling_g2_init_command_line();
extern Object initializer_for_pathname_for_disabling_g2_kb_command_line();
extern Object install_subscription();
extern Object inverse_scalef_function();
extern Object invert_reflection_and_rotation();
extern Object item_x_position();
extern Object item_y_position();
extern Object kb_is_savable_p();
extern Object kb_property_cons_1();
extern Object lookup_frame_description_reference_of_block_qm();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_command_frame();
extern Object make_default_file_type();
extern Object make_frame();
extern Object make_gensym_list_1();
extern Object make_image_plane_description();
extern Object make_or_clear_complete_kb_name();
extern Object make_original_value_for_text_box_font_kb_state_change();
extern Object make_pane_description();
extern Object make_pseudo_frame_1();
extern Object make_slot_value_list_1();
extern Object make_storage_of_representation_data();
extern Object make_text_representation_for_slot_description_value();
extern Object make_ui_client_session_internal();
extern Object mark_kb_workspace_if_savable();
extern Object memq_function();
extern Object modify_pane_description();
extern Object move_icon();
extern Object move_item_by();
extern Object multiply_reflection_and_rotation();
extern Object new_change_workspace_edges();
extern Object note_as_frame_with_kb_state_changes();
extern Object note_change_to_block_1();
extern Object note_gensym_window_initialized();
extern Object note_kb_state_change();
extern Object note_kb_state_change_to_slot_by_saving_text();
extern Object note_permanent_change();
extern Object note_permanent_change_to_component();
extern Object note_permanent_change_to_slot_group_for_block();
extern Object note_permanent_changes();
extern Object note_progress();
extern Object note_saving_frame();
extern Object notify_user();
extern Object notify_user_of_autostart_and_reason();
extern Object orphan_workspace_p();
extern Object parent();
extern Object parent_variable_function();
extern Object parse_text_for_slot();
extern Object permanently_retract_consistency_analysis();
extern Object provide_pathname_for_launch_time_load();
extern Object put_image_on_image_plane();
extern Object put_workspace_into_detail_pane_layout();
extern Object put_workspace_into_detail_panes();
extern Object put_workspace_on_detail_panes_now_or_later();
extern Object put_workspace_on_pane_function();
extern Object read_kb_or_group_thereof();
extern Object reason_to_exclude_slot_description_for_compute_class_description_node_attributes();
extern Object reclaim_frame_serial_number();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_pathname();
extern Object reclaim_kb_property_cons_1();
extern Object reclaim_kb_property_list_1();
extern Object reclaim_kb_specific_properties();
extern Object reclaim_modified_pane_description();
extern Object reclaim_pathname_or_string();
extern Object reclaim_pseudo_frame_1();
extern Object reclaim_slot_value();
extern Object reclaim_text_string();
extern Object reclaim_values_of_kb_specific_variables();
extern Object record_system_variable();
extern Object reject_save_kb_if_filename_problems();
extern Object reject_save_kb_if_not_authorized();
extern Object reject_save_kb_if_not_savable();
extern Object reject_save_kb_if_run_time_only();
extern Object reject_save_kb_if_save_or_backup_in_progress();
extern Object reject_save_kb_if_saving_modules_without_consistency();
extern Object release_all_kb_write_locks();
extern Object release_kb();
extern Object remove_as_frame_with_kb_state_changes();
extern Object remove_kb_state_changes();
extern Object remove_kb_state_variable_record();
extern Object require_that_image_plane_be_visible();
extern Object reset_current_frame_serial_number();
extern Object restore_current_workstation_detail_pane();
extern Object restore_icp_object_map_for_registered_item();
extern Object restore_image_planes_to_pane();
extern Object restore_image_planes_to_pane_now_or_later();
extern Object restore_original_value_for_text_box_font_kb_state_change();
extern Object restore_ui_client_interfaces();
extern Object restore_ui_client_session_item_representation();
extern Object restore_ui_client_session_item_representations();
extern Object rotate_and_reflect_icon();
extern Object run_state_change_hook();
extern Object savable_block_p();
extern Object savable_computation_style_p();
extern Object save_and_delete_ui_client_interfaces();
extern Object save_icp_object_map_for_registered_item();
extern Object send_ws_representations_item_color_pattern_change();
extern Object send_ws_representations_item_moved();
extern Object set_non_savable_lookup_slot_value();
extern Object set_slot_value_function();
extern Object set_window_title();
extern Object shut_down_g2ds_clients_for_clear_kb();
extern Object slot_value_cons_1();
extern Object slot_value_is_permanent_p();
extern Object slot_value_list_2();
extern Object slot_value_list_4();
extern Object start_kb_after_load_from_system_table_qm();
extern Object store_callback_representation();
extern Object string_equalw();
extern Object superior_frame();
extern Object switch_to_kb();
extern Object switch_to_new_empty_kb();
extern Object system_reset();
extern Object system_start();
extern Object text_string_length();
extern Object text_string_p();
extern Object text_string_trim();
extern Object tformat();
extern Object tformat_text_string();
extern Object try_to_do_deferred_user_notifications();
extern Object undo_kb_state_changes();
extern Object undo_kb_state_changes_for_frame();
extern Object unedit_up_to_date_modules();
extern Object unwind_current_workstation_back_to_top_level();
extern Object update_connection_images();
extern Object wide_character_member();
extern Object workspaces_can_be_shown_at_this_kb_level_p();
extern Object write_list_in_chicago_style();
extern Object write_list_of_forced_names();
extern Object write_problems_saving_kb();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Autostart_after_doing_init_file_qm, Qautostart_after_doing_init_file_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Autostart_reason_in_init_file_qm, Qautostart_reason_in_init_file_qm);
extern Object Available_gensym_conses_tail_vector;
extern Object Available_gensym_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);
DECLARE_VARIABLE_WITH_SYMBOL(Backup_case_qm, Qbackup_case_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Block_class_description, Qblock_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Class_definition_class_description, Qclass_definition_class_description);
extern Object Class_description_gkbprop;
extern Object Classes_to_delete_when_releasing_kb;
DECLARE_VARIABLE_WITH_SYMBOL(Command_line_qm, Qcommand_line_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Connection_class_description, Qconnection_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Current_attribute_file_pathname_qm, Qcurrent_attribute_file_pathname_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_serial_number, Qcurrent_frame_serial_number);
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_transform_qm, Qcurrent_frame_transform_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_g2_user_mode_qm, Qcurrent_g2_user_mode_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm, Qcurrent_g2_window_for_this_workstation_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_socket, Qcurrent_icp_socket);
DECLARE_VARIABLE_WITH_SYMBOL(Current_image_x_scale, Qcurrent_image_x_scale);
DECLARE_VARIABLE_WITH_SYMBOL(Current_image_y_scale, Qcurrent_image_y_scale);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_pathname_qm, Qcurrent_kb_pathname_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_serial_number, Qcurrent_kb_serial_number);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_specific_property_list_property_name, Qcurrent_kb_specific_property_list_property_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_saving_context_qm, Qcurrent_saving_context_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_statistics_file_pathname_qm, Qcurrent_statistics_file_pathname_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_system_name, Qcurrent_system_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation, Qcurrent_workstation);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation_context, Qcurrent_workstation_context);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation_detail_pane, Qcurrent_workstation_detail_pane);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation_native_window_qm, Qcurrent_workstation_native_window_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation_window, Qcurrent_workstation_window);
DECLARE_VARIABLE_WITH_SYMBOL(Current_x_origin_of_drawing, Qcurrent_x_origin_of_drawing);
DECLARE_VARIABLE_WITH_SYMBOL(Current_y_origin_of_drawing, Qcurrent_y_origin_of_drawing);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2_init_pathname, Qdefault_g2_init_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2_kb_pathname, Qdefault_g2_kb_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Deleting_ui_client_interfaces_for_clear_kb, Qdeleting_ui_client_interfaces_for_clear_kb);
DECLARE_VARIABLE_WITH_SYMBOL(Do_not_note_permanent_changes_p, Qdo_not_note_permanent_changes_p);
DECLARE_VARIABLE_WITH_SYMBOL(Doing_g2_init_file_p, Qdoing_g2_init_file_p);
DECLARE_VARIABLE_WITH_SYMBOL(Doing_g2_init_kb_p, Qdoing_g2_init_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(For_workstation, Qfor_workstation);
DECLARE_VARIABLE_WITH_SYMBOL(G2_has_v5_mode_windows_p, Qg2_has_v5_mode_windows_p);
DECLARE_VARIABLE_WITH_SYMBOL(Ignore_kb_state_changes_p, Qignore_kb_state_changes_p);
DECLARE_VARIABLE_WITH_SYMBOL(In_clear_kb_p, Qin_clear_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Inhibit_modularity_consistency_checking_qm, Qinhibit_modularity_consistency_checking_qm);
extern Object Instances_specific_to_this_class_kbprop;
extern Object Isqrt_of_most_positive_fixnum;
DECLARE_VARIABLE_WITH_SYMBOL(Kb_save_termination_reason_qm, Qkb_save_termination_reason_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Kb_state_changes, Qkb_state_changes);
DECLARE_VARIABLE_WITH_SYMBOL(Kb_workspace_class_description, Qkb_workspace_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Last_assigned_kb_serial_number, Qlast_assigned_kb_serial_number);
DECLARE_VARIABLE_WITH_SYMBOL(Last_system_class_bit_number, Qlast_system_class_bit_number);
DECLARE_VARIABLE_WITH_SYMBOL(List_of_module_pre_conflict_resolution_post_loading_functions, Qlist_of_module_pre_conflict_resolution_post_loading_functions);
DECLARE_VARIABLE_WITH_SYMBOL(List_of_switched_and_module_post_loading_functions, Qlist_of_switched_and_module_post_loading_functions);
extern Object Local_pseudo_socket;
DECLARE_VARIABLE_WITH_SYMBOL(Main_kb_being_read_qm, Qmain_kb_being_read_qm);
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
extern Object Minus_of_isqrt_of_most_positive_fixnum;
DECLARE_VARIABLE_WITH_SYMBOL(Module_information, Qmodule_information);
DECLARE_VARIABLE_WITH_SYMBOL(New_g2_classic_ui_p, Qnew_g2_classic_ui_p);
DECLARE_VARIABLE_WITH_SYMBOL(Next_class_bit_number, Qnext_class_bit_number);
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2_init_command_line, Qpathname_for_disabling_g2_init_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2_kb_command_line, Qpathname_for_disabling_g2_kb_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Process_specific_system_pathname, Qprocess_specific_system_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Reference_serial_number_for_saved_detail_pane_description, Qreference_serial_number_for_saved_detail_pane_description);
DECLARE_VARIABLE_WITH_SYMBOL(Releasing_kb_qm, Qreleasing_kb_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Represented_frames_in_limbo, Qrepresented_frames_in_limbo);
DECLARE_VARIABLE_WITH_SYMBOL(Saved_detail_pane_description, Qsaved_detail_pane_description);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Servicing_workstation_qm, Qservicing_workstation_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_subtable_class_description, Qsimulation_subtable_class_description);
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Specific_structure_for_current_workstation_context, Qspecific_structure_for_current_workstation_context);
DECLARE_VARIABLE_WITH_SYMBOL(Suppress_warning_message_header_qm, Qsuppress_warning_message_header_qm);
DECLARE_VARIABLE_WITH_SYMBOL(System_has_paused, Qsystem_has_paused);
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
DECLARE_VARIABLE_WITH_SYMBOL(Table_class_description, Qtable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Transients_to_delete, Qtransients_to_delete);
DECLARE_VARIABLE_WITH_SYMBOL(Type_of_current_workstation_context, Qtype_of_current_workstation_context);
DECLARE_VARIABLE_WITH_SYMBOL(Type_of_current_workstation_window, Qtype_of_current_workstation_window);
DECLARE_VARIABLE_WITH_SYMBOL(Ui_client_interface_saved_icp_socket_list, Qui_client_interface_saved_icp_socket_list);
DECLARE_VARIABLE_WITH_SYMBOL(Ui_client_interface_saved_session_list, Qui_client_interface_saved_session_list);
extern Object Ui_client_session_slots_to_save_for_clear_kb;
DECLARE_VARIABLE_WITH_SYMBOL(Unevaluated_expression, Qunevaluated_expression);
DECLARE_VARIABLE_WITH_SYMBOL(Use_current_time_for_next_uuid, Quse_current_time_for_next_uuid);
DECLARE_VARIABLE_WITH_SYMBOL(Warning_message_level, Qwarning_message_level);
extern Object Within_side_limits;
DECLARE_VARIABLE_WITH_SYMBOL(Workspace_class_description, Qworkspace_class_description);
extern Object Workstations_in_service;
extern Object Ws_protocol_handle_moves_from_edge_change_p;
