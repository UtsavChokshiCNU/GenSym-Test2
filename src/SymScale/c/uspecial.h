/* uspecial.h -- application-defined special variables in form of C macro
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#if SI_SUPPORT_THREAD

struct SI_Tls_data {
    INCLUDE_SI_SPECIAL(Object, LOCAL);
    Object A_list_of_classes_with_instances_in_modules_that_do_not_require_them_LOCAL;
    Object A_list_of_relations_with_related_items_in_modules_that_do_not_require_them_LOCAL;
    Object Ab_package_1_LOCAL;
    Object Ab_system_pathname_LOCAL;
    Object Abbreviate_frame_notes_p_LOCAL;
    Object Abbreviate_wide_strings_for_legibility_LOCAL;
    Object Abort_file_written_p_LOCAL;
    Object Abort_for_icp_catcher_qm_LOCAL;
    Object Abort_level_0_tag_LOCAL;
    Object Absolutely_prohibited_restriction_set_LOCAL;
    Object Absolutely_selected_choice_qm_LOCAL;
    Object Accept_any_version_component_p_LOCAL;
    Object Access_direction_slot_description_LOCAL;
    Object Access_error_count_LOCAL;
    Object Action_button_class_description_LOCAL;
    Object Action_templates_LOCAL;
    Object Active_icp_sockets_LOCAL;
    Object Activities_currently_being_converted_to_xml_LOCAL;
    Object Activities_currently_being_laid_out_LOCAL;
    Object Activity_class_code_vector_LOCAL;
    Object Actual_arg_LOCAL;
    Object Add_as_item_referring_to_name_qm_LOCAL;
    Object Adding_from_graph_rendering_p_LOCAL;
    Object Additional_related_blocks_LOCAL;
    Object Adjustable_gensym_string_byte_use_counter_LOCAL;
    Object Adjustable_gensym_string_counter_LOCAL;
    Object Adjustable_gensym_string_counts_LOCAL;
    Object Adjustable_gensym_strings_LOCAL;
    Object Align_selection_command_operations_LOCAL;
    Object Alist_of_dialog_mappings_LOCAL;
    Object Alist_of_local_names_and_role_names_LOCAL;
    Object All_ab_font_names_LOCAL;
    Object All_branch_destinations_possible_LOCAL;
    Object All_classes_for_cached_class_description_node_attributes_LOCAL;
    Object All_classes_for_cached_class_description_node_attributes_for_external_definition_LOCAL;
    Object All_classes_for_indirectly_referenced_class_LOCAL;
    Object All_colors_LOCAL;
    Object All_command_line_keyword_arguments_LOCAL;
    Object All_computation_instances_above_breakpoint_LOCAL;
    Object All_cons_pools_LOCAL;
    Object All_cycles_found_so_far_in_module_hierarchy_LOCAL;
    Object All_directory_namestrings_in_directory_of_names_LOCAL;
    Object All_external_foreign_function_images_qm_LOCAL;
    Object All_file_namestrings_in_directory_of_names_LOCAL;
    Object All_foreign_function_images_qm_LOCAL;
    Object All_formats_in_module_LOCAL;
    Object All_frames_with_simple_debugging_names_LOCAL;
    Object All_g2gl_operators_LOCAL;
    Object All_gensym_pathnames_containing_open_streams_LOCAL;
    Object All_gesture_instruction_names_LOCAL;
    Object All_image_data_structures_LOCAL;
    Object All_index_space_names_LOCAL;
    Object All_known_command_line_plist_elements_LOCAL;
    Object All_known_file_systems_LOCAL;
    Object All_menu_heading_format_names_LOCAL;
    Object All_module_frame_notes_for_workspaces_LOCAL;
    Object All_permanently_changed_things_are_marked_LOCAL;
    Object All_region_info_LOCAL;
    Object All_signal_handlers_registered_p_LOCAL;
    Object All_supported_2022_escape_sequences_LOCAL;
    Object All_systems_LOCAL;
    Object All_unicode_block_names_LOCAL;
    Object All_valid_superior_test_functions_LOCAL;
    Object All_virtual_attributes_LOCAL;
    Object All_write_locks_LOCAL;
    Object All_xml_checksums_LOCAL;
    Object Allocated_byte_vector_16_vectors_LOCAL;
    Object Allocated_strings_reported_LOCAL;
    Object Allow_activation_of_name_boxes_p_LOCAL;
    Object Allow_activation_of_table_items_p_LOCAL;
    Object Allow_comparison_of_slot_value_to_parse_result_LOCAL;
    Object Allow_debugger_pause_LOCAL;
    Object Allow_extensionless_dos_filenames_p_LOCAL;
    Object Allow_in_line_designations_qm_LOCAL;
    Object Allow_inline_evaluate_role_instructions_p_LOCAL;
    Object Allow_internal_procedure_environment_printing_qm_LOCAL;
    Object Allow_invalidate_on_printing_window_p_LOCAL;
    Object Allow_name_box_creation_LOCAL;
    Object Allow_name_box_creation_without_workspace_LOCAL;
    Object Allow_no_value_p_LOCAL;
    Object Allow_user_defined_logbook_handlers_p_LOCAL;
    Object Alphabet_canonical_element_st_test_LOCAL;
    Object Alphabet_character_class_st_test_LOCAL;
    Object Alphabet_count_of_standard_state_transition_tests_LOCAL;
    Object Alphabet_equality_st_test_LOCAL;
    Object Alphabet_members_LOCAL;
    Object Alphabet_standard_state_transition_tests_LOCAL;
    Object Alphabet_subset_function_LOCAL;
    Object Already_mutated_evaluators_LOCAL;
    Object Alternate_chaining_queue_LOCAL;
    Object Alternate_symbols_for_translation_LOCAL;
    Object Always_impose_device_set_widths_qm_LOCAL;
    Object Always_make_runtime_nil_checks_LOCAL;
    Object Always_recompile_on_load_LOCAL;
    Object Always_use_current_time_for_uuid_LOCAL;
    Object Analyze_for_consistency_in_progress_LOCAL;
    Object Analyzing_export_definition_for_consistency_p_LOCAL;
    Object Annotation_count_LOCAL;
    Object Any_cached_evaluator_slot_info_p_LOCAL;
    Object Append_into_arrays_and_lists_LOCAL;
    Object Archtypal_stripped_text_LOCAL;
    Object Args_for_g2gl_object_class_icon_description_override_LOCAL;
    Object Arithmetic_errors_are_stack_errors_p_LOCAL;
    Object Array_initialization_evaluation_values_use_designations_p_LOCAL;
    Object Arrow_button_class_description_LOCAL;
    Object As_fast_as_possible_model_queue_LOCAL;
    Object Ascii_to_kana_map_LOCAL;
    Object Asian_double_byte_count_LOCAL;
    Object Assignment_section_forms_LOCAL;
    Object At_end_of_icp_message_block_qm_LOCAL;
    Object At_end_of_icp_message_group_qm_LOCAL;
    Object Attempting_save_via_system_procedure_qm_LOCAL;
    Object Attr_not_found_LOCAL;
    Object Attribute_display_spot_count_LOCAL;
    Object Attribute_file_input_frame_LOCAL;
    Object Attribute_items_LOCAL;
    Object Attribute_mimic_count_LOCAL;
    Object Attribute_name_errors_LOCAL;
    Object Attribute_name_represented_by_table_spot_count_LOCAL;
    Object Attribute_name_xml_checksum_LOCAL;
    Object Attribute_nesting_depth_LOCAL;
    Object Attribute_represented_by_table_spot_count_LOCAL;
    Object Attribute_table_spot_count_LOCAL;
    Object Attribute_value_represented_by_table_spot_count_LOCAL;
    Object Attributes_collector_LOCAL;
    Object Attributes_collector_tail_LOCAL;
    Object Attributes_of_history_element_structure_as_interned_list_LOCAL;
    Object Attributes_of_history_specification_structure_as_interned_list_LOCAL;
    Object Authorized_products_of_this_machine_LOCAL;
    Object Authorized_user_class_description_LOCAL;
    Object Authorized_user_records_of_g2_ok_file_LOCAL;
    Object Authorized_users_list_LOCAL;
    Object Authorizing_ok_pathname_LOCAL;
    Object Automatic_deadlock_detection_frequency_LOCAL;
    Object Automatic_deadlock_detection_task_LOCAL;
    Object Automatically_resolve_conflicts_by_default_LOCAL;
    Object Autostart_after_doing_init_file_qm_LOCAL;
    Object Autostart_reason_in_init_file_qm_LOCAL;
    Object Available_8859_reverse_unicode_map_hash_vector_43_vectors_LOCAL;
    Object Available_backtrace_conses_LOCAL;
    Object Available_backtrace_conses_tail_LOCAL;
    Object Available_blocks_hash_hash_vector_43_vectors_LOCAL;
    Object Available_byte_vector_conses_LOCAL;
    Object Available_byte_vector_conses_tail_LOCAL;
    Object Available_call_hash_hash_vector_43_vectors_LOCAL;
    Object Available_class_description_conses_LOCAL;
    Object Available_class_description_conses_tail_LOCAL;
    Object Available_compiler_conses_LOCAL;
    Object Available_compiler_conses_tail_LOCAL;
    Object Available_connection_conses_LOCAL;
    Object Available_connection_conses_tail_LOCAL;
    Object Available_custom_dialog_conses_LOCAL;
    Object Available_custom_dialog_conses_tail_LOCAL;
    Object Available_dragging_conses_LOCAL;
    Object Available_dragging_conses_tail_LOCAL;
    Object Available_duplicates_check_hash_table_hash_vector_50021_vectors_LOCAL;
    Object Available_dynamic_rule_displays_hash_vector_43_vectors_LOCAL;
    Object Available_entity_conses_LOCAL;
    Object Available_entity_conses_tail_LOCAL;
    Object Available_eval_conses_LOCAL;
    Object Available_eval_conses_tail_LOCAL;
    Object Available_filter_conses_LOCAL;
    Object Available_filter_conses_tail_LOCAL;
    Object Available_float_array_conses_LOCAL;
    Object Available_float_array_conses_tail_LOCAL;
    Object Available_fonts_conses_LOCAL;
    Object Available_fonts_conses_tail_LOCAL;
    Object Available_foreign_function_registry_internal_hash_vector_131_vectors_LOCAL;
    Object Available_frame_conses_LOCAL;
    Object Available_frame_conses_tail_LOCAL;
    Object Available_frame_display_conses_LOCAL;
    Object Available_frame_display_conses_tail_LOCAL;
    Object Available_frame_serial_conses_LOCAL;
    Object Available_frame_serial_conses_tail_LOCAL;
    Object Available_frame_serial_number_to_item_table_hash_vector_67_vectors_LOCAL;
    Object Available_g2_list_conses_LOCAL;
    Object Available_g2_list_conses_tail_LOCAL;
    Object Available_g2ds_conses_LOCAL;
    Object Available_g2ds_conses_tail_LOCAL;
    Object Available_generic_rule_instance_displays_hash_vector_43_vectors_LOCAL;
    Object Available_gensym_conses_LOCAL;
    Object Available_gensym_conses_tail_LOCAL;
    Object Available_gfi_conses_LOCAL;
    Object Available_gfi_conses_tail_LOCAL;
    Object Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_LOCAL;
    Object Available_grammar_conses_LOCAL;
    Object Available_grammar_conses_tail_LOCAL;
    Object Available_graph_conses_LOCAL;
    Object Available_graph_conses_tail_LOCAL;
    Object Available_graph_layout_conses_LOCAL;
    Object Available_graph_layout_conses_tail_LOCAL;
    Object Available_graph_node_of_graphed_thing_hash_vector_43_vectors_LOCAL;
    Object Available_graphics_conses_LOCAL;
    Object Available_graphics_conses_tail_LOCAL;
    Object Available_gsi_conses_LOCAL;
    Object Available_gsi_conses_tail_LOCAL;
    Object Available_hashed_rule_instance_hash_vector_43_vectors_LOCAL;
    Object Available_history_conses_LOCAL;
    Object Available_history_conses_tail_LOCAL;
    Object Available_icon_editor_conses_LOCAL;
    Object Available_icon_editor_conses_tail_LOCAL;
    Object Available_icp_buffer_ref_count_conses_LOCAL;
    Object Available_icp_buffer_ref_count_conses_tail_LOCAL;
    Object Available_icp_callback_conses_LOCAL;
    Object Available_icp_callback_conses_tail_LOCAL;
    Object Available_icp_conses_LOCAL;
    Object Available_icp_conses_tail_LOCAL;
    Object Available_indexed_attribute_parent_objects_hash_vector_43_vectors_LOCAL;
    Object Available_installation_conses_LOCAL;
    Object Available_installation_conses_tail_LOCAL;
    Object Available_item_or_name_hash_hash_vector_43_vectors_LOCAL;
    Object Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_LOCAL;
    Object Available_java_conses_LOCAL;
    Object Available_java_conses_tail_LOCAL;
    Object Available_jis_map_hash_vector_307_vectors_LOCAL;
    Object Available_journal_conses_LOCAL;
    Object Available_journal_conses_tail_LOCAL;
    Object Available_kanji_font_cache_vector_137_vectors_LOCAL;
    Object Available_kb_fsn_hash_table_hash_vector_131_vectors_LOCAL;
    Object Available_kb_property_conses_LOCAL;
    Object Available_kb_property_conses_tail_LOCAL;
    Object Available_long_array_conses_LOCAL;
    Object Available_long_array_conses_tail_LOCAL;
    Object Available_lookup_conses_LOCAL;
    Object Available_lookup_conses_tail_LOCAL;
    Object Available_module_required_by_relationships_hash_vector_43_vectors_LOCAL;
    Object Available_native_font_set_width_equivalence_table_256_vectors_LOCAL;
    Object Available_native_icon_handle_hash_vector_43_vectors_LOCAL;
    Object Available_nms_menu_for_hmenu_hash_vector_43_vectors_LOCAL;
    Object Available_non_kanji_font_vector_257_vectors_LOCAL;
    Object Available_object_circularity_hashtable_hash_vector_131_vectors_LOCAL;
    Object Available_ok_file_token_conses_LOCAL;
    Object Available_ok_file_token_conses_tail_LOCAL;
    Object Available_part_stack_conses_LOCAL;
    Object Available_part_stack_conses_tail_LOCAL;
    Object Available_path_conses_LOCAL;
    Object Available_path_conses_tail_LOCAL;
    Object Available_phrase_pool_conses_LOCAL;
    Object Available_phrase_pool_conses_tail_LOCAL;
    Object Available_player_conses_LOCAL;
    Object Available_player_conses_tail_LOCAL;
    Object Available_printing_conses_LOCAL;
    Object Available_printing_conses_tail_LOCAL;
    Object Available_proc_conses_LOCAL;
    Object Available_proc_conses_tail_LOCAL;
    Object Available_procedure_invocations_hash_vector_43_vectors_LOCAL;
    Object Available_queue_item_conses_LOCAL;
    Object Available_queue_item_conses_tail_LOCAL;
    Object Available_regexp_conses_LOCAL;
    Object Available_regexp_conses_tail_LOCAL;
    Object Available_region_conses_LOCAL;
    Object Available_region_conses_tail_LOCAL;
    Object Available_representation_handle_hash_vector_109_vectors_LOCAL;
    Object Available_reusable_gensyms_LOCAL;
    Object Available_role_conses_LOCAL;
    Object Available_role_conses_tail_LOCAL;
    Object Available_scaled_font_kanji_font_cache_vector_1096_vectors_LOCAL;
    Object Available_scaled_font_non_kanji_font_vector_2049_vectors_LOCAL;
    Object Available_sequence_conses_LOCAL;
    Object Available_sequence_conses_tail_LOCAL;
    Object Available_sexp_annotation_hash_vector_43_vectors_LOCAL;
    Object Available_simulate_conses_LOCAL;
    Object Available_simulate_conses_tail_LOCAL;
    Object Available_slot_value_conses_LOCAL;
    Object Available_slot_value_conses_tail_LOCAL;
    Object Available_stack_change_conses_LOCAL;
    Object Available_stack_change_conses_tail_LOCAL;
    Object Available_stack_conses_LOCAL;
    Object Available_stack_conses_tail_LOCAL;
    Object Available_streams_conses_LOCAL;
    Object Available_streams_conses_tail_LOCAL;
    Object Available_string_pool_conses_LOCAL;
    Object Available_string_pool_conses_tail_LOCAL;
    Object Available_sub_call_hash_hash_vector_43_vectors_LOCAL;
    Object Available_subseries_of_values_64_vectors_LOCAL;
    Object Available_sysproc_conses_LOCAL;
    Object Available_sysproc_conses_tail_LOCAL;
    Object Available_sysproc_continuation_hashtable_hash_vector_131_vectors_LOCAL;
    Object Available_tiling_patterns_LOCAL;
    Object Available_timestamp_conses_LOCAL;
    Object Available_timestamp_conses_tail_LOCAL;
    Object Available_token_conses_LOCAL;
    Object Available_token_conses_tail_LOCAL;
    Object Available_token_stack_conses_LOCAL;
    Object Available_token_stack_conses_tail_LOCAL;
    Object Available_tracked_items_call_vector_table_hash_vector_43_vectors_LOCAL;
    Object Available_tree_ordering_conses_LOCAL;
    Object Available_tree_ordering_conses_tail_LOCAL;
    Object Available_ui_callback_table_hash_vector_43_vectors_LOCAL;
    Object Available_uo_memory_usage_information_hash_vector_43_vectors_LOCAL;
    Object Available_user_hash_table_internal_hash_vector_43_vectors_LOCAL;
    Object Available_variable_fill_icp_buffer_4096_vectors_LOCAL;
    Object Available_vector_pool_conses_LOCAL;
    Object Available_vector_pool_conses_tail_LOCAL;
    Object Available_warmboot_conses_LOCAL;
    Object Available_warmboot_conses_tail_LOCAL;
    Object Available_workstation_contexts_LOCAL;
    Object Axis_LOCAL;
    Object Axis_automatic_LOCAL;
    Object Axis_crossover_LOCAL;
    Object Axis_heading_LOCAL;
    Object Axis_index_LOCAL;
    Object Axis_is_discrete_p_LOCAL;
    Object Axis_maximum_LOCAL;
    Object Axis_minimum_LOCAL;
    Object Axis_pane_count_LOCAL;
    Object Axis_tickmark_count_LOCAL;
    Object Axis_tickmark_count_as_fixnum_LOCAL;
    Object Axis_tickmark_label_frequency_LOCAL;
    Object Axis_tickmark_label_max_digits_after_point_LOCAL;
    Object Axis_tickmark_label_max_digits_before_point_LOCAL;
    Object Axis_tickmark_label_max_digits_in_exponent_LOCAL;
    Object Axis_tickmark_step_LOCAL;
    Object Background_color_value_from_postponed_erase_LOCAL;
    Object Background_color_value_of_graphic_element_LOCAL;
    Object Background_print_workspace_process_state_block_count_LOCAL;
    Object Background_processes_LOCAL;
    Object Background_processes_task_LOCAL;
    Object Backoff_limit_LOCAL;
    Object Backtrace_cons_counter_LOCAL;
    Object Backtrace_stack_for_internal_error_LOCAL;
    Object Backtrace_text_buffer_for_internal_error_LOCAL;
    Object Backtrace_text_buffer_for_string_metering_LOCAL;
    Object Backup_case_qm_LOCAL;
    Object Backward_chaining_display_count_LOCAL;
    Object Backward_chaining_displays_LOCAL;
    Object Backward_chaining_link_class_description_LOCAL;
    Object Bad_rule_LOCAL;
    Object Base_36_digits_string_LOCAL;
    Object Base_code_body_return_tag_LOCAL;
    Object Base_reference_LOCAL;
    Object Baseline_in_window_for_line_of_text_of_graphic_element_LOCAL;
    Object Basic_part_LOCAL;
    Object Basic_profiling_structure_count_LOCAL;
    Object Basis_kb_frame_serial_number_LOCAL;
    Object Best_text_matched_by_player_LOCAL;
    Object Bignum_overflow_count_LOCAL;
    Object Binary_tree_element_count_LOCAL;
    Object Binary_xml_checksum_LOCAL;
    Object Bindable_keysyms_LOCAL;
    Object Bitmap_array_count_LOCAL;
    Object Bitmap_for_printing_qm_LOCAL;
    Object Block_change_count_LOCAL;
    Object Block_class_description_LOCAL;
    Object Block_near_mouse_cache_count_LOCAL;
    Object Block_of_frame_LOCAL;
    Object Blocking_socket_count_LOCAL;
    Object Blocks_to_delete_after_reading_kb_LOCAL;
    Object Blocks_to_delete_after_unsquirreling_LOCAL;
    Object Blocks_with_bad_connections_LOCAL;
    Object Blocks_with_connections_from_kb_read_LOCAL;
    Object Blocks_with_relation_instances_from_kb_read_LOCAL;
    Object Blocks_with_specialized_method_qm_LOCAL;
    Object Blocks_with_subblocks_from_kb_read_LOCAL;
    Object Bogus_preflight_from_printing_to_graphs_LOCAL;
    Object Bombout_clean_up_functions_LOCAL;
    Object Boolean_composition_over_symbols_allows_top_level_symbols_p_LOCAL;
    Object Bootstrap_information_LOCAL;
    Object Bottom_edge_in_window_of_graphic_element_LOCAL;
    Object Bottom_edge_of_draw_area_LOCAL;
    Object Bottom_edge_of_frame_LOCAL;
    Object Bottom_scroll_arrow_rubber_stamp_widget_LOCAL;
    Object Bounding_box_class_description_LOCAL;
    Object Bounding_box_spot_count_LOCAL;
    Object Bounding_box_state_count_LOCAL;
    Object Bounding_state_count_LOCAL;
    Object Bpel_xml_namespace_LOCAL;
    Object Break_if_name_inconsistency_qm_LOCAL;
    Object Breakpoint_level_LOCAL;
    Object Breakpoints_enabled_p_LOCAL;
    Object Buffer_for_internal_error_on_console_LOCAL;
    Object Buffer_for_internal_error_on_logbook_LOCAL;
    Object Buffer_for_read_file_into_string_LOCAL;
    Object Buffer_for_string_metering_LOCAL;
    Object Buffer_for_write_internal_error_LOCAL;
    Object Buffer_index_of_ok_file_reader_LOCAL;
    Object Buffer_length_of_ok_file_reader_LOCAL;
    Object Buffer_of_ok_file_reader_LOCAL;
    Object Buffer_of_resumable_p_LOCAL;
    Object Buffered_plot_painting_color_LOCAL;
    Object Buffered_plot_painting_line_style_LOCAL;
    Object Buffered_plot_painting_one_pixel_in_seconds_LOCAL;
    Object Buffered_plot_painting_plot_LOCAL;
    Object Buffered_plot_painting_style_arg_LOCAL;
    Object Buffered_plot_painting_value_axis_LOCAL;
    Object Buggy_polyline_p_LOCAL;
    Object Built_in_character_codes_LOCAL;
    Object Button_class_description_LOCAL;
    Object Button_down_state_count_LOCAL;
    Object Button_label_class_description_LOCAL;
    Object Button_menu_spot_count_LOCAL;
    Object Button_spot_count_LOCAL;
    Object Buttons_in_button_down_state_LOCAL;
    Object Bypass_add_class_export_info_attributes_p_LOCAL;
    Object Bypass_fix_for_exported_method_overloading_p_LOCAL;
    Object Byte_code_body_count_LOCAL;
    Object Byte_code_stream_count_LOCAL;
    Object Byte_vector_16_pool_counts_LOCAL;
    Object Byte_vector_16_pool_number_to_malloc_LOCAL;
    Object Byte_vector_16_pools_LOCAL;
    Object Byte_vector_cons_counter_LOCAL;
    Object Bytes_allocated_for_image_tiles_LOCAL;
    Object Bytes_consumed_by_one_undefaulted_lookup_slot_LOCAL;
    Object Bytes_in_allocated_byte_vector_16_vectors_LOCAL;
    Object Bytes_per_double_float_simple_array_cached_LOCAL;
    Object Bytes_per_long_simple_array_cached_LOCAL;
    Object C_byte_code_body_result_1_LOCAL;
    Object C_byte_code_body_result_2_LOCAL;
    Object C_byte_code_body_result_3_LOCAL;
    Object C_byte_code_body_result_4_LOCAL;
    Object C_byte_code_body_result_5_LOCAL;
    Object C_byte_code_body_result_6_LOCAL;
    Object C_byte_code_body_result_7_LOCAL;
    Object C_byte_code_body_result_8_LOCAL;
    Object Cache_al_semantics_graph_LOCAL;
    Object Cache_chinese_semantics_graph_LOCAL;
    Object Cache_embedded_option_semantics_graph_LOCAL;
    Object Cache_ent_semantics_graph_LOCAL;
    Object Cache_g1_semantics_graph_LOCAL;
    Object Cache_gfi_semantics_graph_LOCAL;
    Object Cache_gsi_semantics_graph_LOCAL;
    Object Cache_gspan_semantics_graph_LOCAL;
    Object Cache_icp_semantics_graph_LOCAL;
    Object Cache_japanese_semantics_graph_LOCAL;
    Object Cache_jl_semantics_graph_LOCAL;
    Object Cache_jp_semantics_graph_LOCAL;
    Object Cache_kfep_semantics_graph_LOCAL;
    Object Cache_korean_semantics_graph_LOCAL;
    Object Cache_nupec_semantics_graph_LOCAL;
    Object Cache_restricted_use_option_semantics_graph_LOCAL;
    Object Cache_runtime_option_semantics_graph_LOCAL;
    Object Cache_stack_and_locals_LOCAL;
    Object Cached_byte_code_body_LOCAL;
    Object Cached_classes_for_backward_chaining_LOCAL;
    Object Cached_classes_for_forward_chaining_LOCAL;
    Object Cached_compareoperator_LOCAL;
    Object Cached_event_bit_LOCAL;
    Object Cached_eventflag_LOCAL;
    Object Cached_explanation_from_data_server_or_initial_value_count_LOCAL;
    Object Cached_explanation_from_frame_count_LOCAL;
    Object Cached_explanation_from_generic_formula_count_LOCAL;
    Object Cached_explanation_from_rule_count_LOCAL;
    Object Cached_explanation_from_specific_formula_count_LOCAL;
    Object Cached_fellow_val_LOCAL;
    Object Cached_fixnum_start_time_LOCAL;
    Object Cached_fixnum_time_limit_qm_LOCAL;
    Object Cached_fixnum_time_qm_LOCAL;
    Object Cached_gensym_user_home_directory_LOCAL;
    Object Cached_local_gensym_x11_display_LOCAL;
    Object Cached_local_icp_version_info_LOCAL;
    Object Cached_long_code_constant_form_LOCAL;
    Object Cached_machine_id_qm_LOCAL;
    Object Cached_matching_machine_id_qm_LOCAL;
    Object Cached_n_LOCAL;
    Object Cached_name_for_local_home_LOCAL;
    Object Cached_nstart_LOCAL;
    Object Cached_requiredgoodsize_LOCAL;
    Object Cached_restrictions_alist_LOCAL;
    Object Cached_result_LOCAL;
    Object Cached_stack_frame_base_LOCAL;
    Object Cached_stack_program_counter_LOCAL;
    Object Cached_stack_program_counter_form_LOCAL;
    Object Cached_subj_LOCAL;
    Object Cached_tcpip_listener_address_qm_LOCAL;
    Object Cached_timed_out_foreign_function_name_qm_LOCAL;
    Object Cached_top_of_stack_LOCAL;
    Object Cached_top_of_stack_form_LOCAL;
    Object Cached_unknown_error_string_with_code_qm_LOCAL;
    Object Calendar_cv_count_LOCAL;
    Object Call_check_node_attribute_value_p_LOCAL;
    Object Call_statement_processed_qm_LOCAL;
    Object Called_within_clear_text_loading_LOCAL;
    Object Called_within_locate_or_create_junction_block_definition_LOCAL;
    Object Calling_float_function_cleverly_p_LOCAL;
    Object Calling_tformat_for_give_warning_qm_LOCAL;
    Object Cascaded_ring_buffer_count_LOCAL;
    Object Catch_for_let_in_expression_context_LOCAL;
    Object Category_evaluator_interface_count_LOCAL;
    Object Category_for_category_symbol_count_LOCAL;
    Object Category_for_token_count_LOCAL;
    Object Category_instance_menu_workspace_class_description_LOCAL;
    Object Category_menu_button_spot_count_LOCAL;
    Object Category_menu_class_description_LOCAL;
    Object Category_set_count_LOCAL;
    Object Category_symbols_for_non_contributing_categories_LOCAL;
    Object Category_visit_vector_qm_LOCAL;
    Object Cell_LOCAL;
    Object Cell_contents_LOCAL;
    Object Cell_index_currently_being_registered_LOCAL;
    Object Chain_of_available_access_errors_LOCAL;
    Object Chain_of_available_annotations_LOCAL;
    Object Chain_of_available_asian_double_bytes_LOCAL;
    Object Chain_of_available_attribute_display_spots_LOCAL;
    Object Chain_of_available_attribute_mimics_LOCAL;
    Object Chain_of_available_attribute_name_represented_by_table_spots_LOCAL;
    Object Chain_of_available_attribute_represented_by_table_spots_LOCAL;
    Object Chain_of_available_attribute_table_spots_LOCAL;
    Object Chain_of_available_attribute_value_represented_by_table_spots_LOCAL;
    Object Chain_of_available_axis_panes_LOCAL;
    Object Chain_of_available_background_print_workspace_process_state_blocks_LOCAL;
    Object Chain_of_available_backward_chaining_displays_LOCAL;
    Object Chain_of_available_basic_profiling_structures_LOCAL;
    Object Chain_of_available_binary_tree_elements_LOCAL;
    Object Chain_of_available_bitmap_arrays_LOCAL;
    Object Chain_of_available_block_changes_LOCAL;
    Object Chain_of_available_block_near_mouse_caches_LOCAL;
    Object Chain_of_available_blocking_sockets_LOCAL;
    Object Chain_of_available_bounding_box_spots_LOCAL;
    Object Chain_of_available_bounding_box_states_LOCAL;
    Object Chain_of_available_bounding_states_LOCAL;
    Object Chain_of_available_button_down_states_LOCAL;
    Object Chain_of_available_button_menu_spots_LOCAL;
    Object Chain_of_available_button_spots_LOCAL;
    Object Chain_of_available_byte_code_bodys_LOCAL;
    Object Chain_of_available_byte_code_streams_LOCAL;
    Object Chain_of_available_cached_explanation_from_data_server_or_initial_values_LOCAL;
    Object Chain_of_available_cached_explanation_from_frames_LOCAL;
    Object Chain_of_available_cached_explanation_from_generic_formulas_LOCAL;
    Object Chain_of_available_cached_explanation_from_rules_LOCAL;
    Object Chain_of_available_cached_explanation_from_specific_formulas_LOCAL;
    Object Chain_of_available_calendar_cvs_LOCAL;
    Object Chain_of_available_cascaded_ring_buffers_LOCAL;
    Object Chain_of_available_category_evaluator_interfaces_LOCAL;
    Object Chain_of_available_category_for_category_symbols_LOCAL;
    Object Chain_of_available_category_for_tokens_LOCAL;
    Object Chain_of_available_category_menu_button_spots_LOCAL;
    Object Chain_of_available_category_sets_LOCAL;
    Object Chain_of_available_character_descriptions_LOCAL;
    Object Chain_of_available_character_images_LOCAL;
    Object Chain_of_available_character_sequence_token_menu_button_spots_LOCAL;
    Object Chain_of_available_chart_spots_LOCAL;
    Object Chain_of_available_chart_views_LOCAL;
    Object Chain_of_available_check_box_cvs_LOCAL;
    Object Chain_of_available_checkable_list_box_cvs_LOCAL;
    Object Chain_of_available_class_descriptions_LOCAL;
    Object Chain_of_available_class_file_streams_LOCAL;
    Object Chain_of_available_class_instances_memory_infos_LOCAL;
    Object Chain_of_available_class_subscriptions_LOCAL;
    Object Chain_of_available_class_subscriptionss_LOCAL;
    Object Chain_of_available_close_box_spots_LOCAL;
    Object Chain_of_available_code_body_continuations_LOCAL;
    Object Chain_of_available_code_body_invocations_LOCAL;
    Object Chain_of_available_color_maps_LOCAL;
    Object Chain_of_available_compiled_resources_LOCAL;
    Object Chain_of_available_compiler_code_body_entrys_LOCAL;
    Object Chain_of_available_component_change_reports_LOCAL;
    Object Chain_of_available_compound_fixnum_simulation_times_LOCAL;
    Object Chain_of_available_compound_slot_descriptors_LOCAL;
    Object Chain_of_available_compound_type_descriptors_LOCAL;
    Object Chain_of_available_computation_instances_LOCAL;
    Object Chain_of_available_connection_items_LOCAL;
    Object Chain_of_available_connection_spots_LOCAL;
    Object Chain_of_available_connection_subrectangle_structures_LOCAL;
    Object Chain_of_available_connections_LOCAL;
    Object Chain_of_available_credits_table_spots_LOCAL;
    Object Chain_of_available_data_servers_LOCAL;
    Object Chain_of_available_date_formats_LOCAL;
    Object Chain_of_available_deferred_updates_LOCAL;
    Object Chain_of_available_detail_pane_spots_LOCAL;
    Object Chain_of_available_dial_spots_LOCAL;
    Object Chain_of_available_dialog_components_LOCAL;
    Object Chain_of_available_dialog_errors_structures_LOCAL;
    Object Chain_of_available_dialog_states_LOCAL;
    Object Chain_of_available_dialog_views_LOCAL;
    Object Chain_of_available_display_panes_LOCAL;
    Object Chain_of_available_drag_handle_states_LOCAL;
    Object Chain_of_available_dragging_states_LOCAL;
    Object Chain_of_available_drawing_tasks_LOCAL;
    Object Chain_of_available_duration_cvs_LOCAL;
    Object Chain_of_available_dynamic_dialogs_LOCAL;
    Object Chain_of_available_dynamic_workspace_associated_structures_LOCAL;
    Object Chain_of_available_edit_box_changes_LOCAL;
    Object Chain_of_available_edit_box_spots_LOCAL;
    Object Chain_of_available_edit_caches_LOCAL;
    Object Chain_of_available_edit_menu_states_LOCAL;
    Object Chain_of_available_edit_states_LOCAL;
    Object Chain_of_available_element_of_foreign_linking_infos_LOCAL;
    Object Chain_of_available_elevator_of_scroll_bar_spots_LOCAL;
    Object Chain_of_available_elevator_shaft_spots_LOCAL;
    Object Chain_of_available_elevator_states_LOCAL;
    Object Chain_of_available_entire_focus_menu_spots_LOCAL;
    Object Chain_of_available_entire_g2_window_spots_LOCAL;
    Object Chain_of_available_entire_menu_spots_LOCAL;
    Object Chain_of_available_eq_hash_tables_LOCAL;
    Object Chain_of_available_error_codes_LOCAL;
    Object Chain_of_available_evaluator_slot_infos_LOCAL;
    Object Chain_of_available_event_detectors_LOCAL;
    Object Chain_of_available_expression_for_compilations_LOCAL;
    Object Chain_of_available_external_class_infos_LOCAL;
    Object Chain_of_available_external_method_infos_LOCAL;
    Object Chain_of_available_external_set_pointerss_LOCAL;
    Object Chain_of_available_external_simulation_objects_LOCAL;
    Object Chain_of_available_extremum_caches_LOCAL;
    Object Chain_of_available_filename_parser_informations_LOCAL;
    Object Chain_of_available_for_structures_LOCAL;
    Object Chain_of_available_foreign_function_call_infos_LOCAL;
    Object Chain_of_available_foreign_function_entrys_LOCAL;
    Object Chain_of_available_foreign_function_image_infos_LOCAL;
    Object Chain_of_available_foreign_struct_infos_LOCAL;
    Object Chain_of_available_formula_invocations_LOCAL;
    Object Chain_of_available_frame_component_spots_LOCAL;
    Object Chain_of_available_frame_description_references_LOCAL;
    Object Chain_of_available_frame_displays_LOCAL;
    Object Chain_of_available_frame_transforms_LOCAL;
    Object Chain_of_available_fsm_states_LOCAL;
    Object Chain_of_available_function_infos_LOCAL;
    Object Chain_of_available_function_invocations_LOCAL;
    Object Chain_of_available_future_task_queue_holders_LOCAL;
    Object Chain_of_available_g2_list_elements_LOCAL;
    Object Chain_of_available_g2_login_states_LOCAL;
    Object Chain_of_available_g2_stream_structures_LOCAL;
    Object Chain_of_available_g2_tokens_LOCAL;
    Object Chain_of_available_g2ds_interfaces_LOCAL;
    Object Chain_of_available_g2ds_server_connections_LOCAL;
    Object Chain_of_available_g2ds_variables_LOCAL;
    Object Chain_of_available_g2gl_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_activity_optionss_LOCAL;
    Object Chain_of_available_g2gl_alarm_event_handler_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_assign_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_attribute_display_compilations_LOCAL;
    Object Chain_of_available_g2gl_body_compilations_LOCAL;
    Object Chain_of_available_g2gl_break_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_call_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_call_invocations_LOCAL;
    Object Chain_of_available_g2gl_compensate_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_compensation_handler_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_compilation_versions_LOCAL;
    Object Chain_of_available_g2gl_do_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_empty_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_execution_faults_LOCAL;
    Object Chain_of_available_g2gl_execution_frames_LOCAL;
    Object Chain_of_available_g2gl_execution_threads_LOCAL;
    Object Chain_of_available_g2gl_exit_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_fault_handler_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_flow_discriminator_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_flow_gate_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_flow_signal_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_flow_split_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_flow_sync_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_flow_terminator_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_invoke_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_message_event_handler_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_message_transmissions_LOCAL;
    Object Chain_of_available_g2gl_n_out_of_m_flow_join_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_pick_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_pick_join_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_process_invocation_threads_LOCAL;
    Object Chain_of_available_g2gl_receive_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_reply_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_return_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_scope_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_service_ports_LOCAL;
    Object Chain_of_available_g2gl_switch_fork_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_switch_join_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_text_box_compilations_LOCAL;
    Object Chain_of_available_g2gl_throw_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_wait_activity_compilations_LOCAL;
    Object Chain_of_available_g2gl_while_activity_compilations_LOCAL;
    Object Chain_of_available_gb_2312s_LOCAL;
    Object Chain_of_available_gensym_grammars_LOCAL;
    Object Chain_of_available_gensym_pathnames_LOCAL;
    Object Chain_of_available_gensym_string_streams_LOCAL;
    Object Chain_of_available_gensym_string_text_sequences_LOCAL;
    Object Chain_of_available_gensym_windows_LOCAL;
    Object Chain_of_available_geometrys_LOCAL;
    Object Chain_of_available_gesture_functions_LOCAL;
    Object Chain_of_available_gesture_locals_LOCAL;
    Object Chain_of_available_gesture_threads_LOCAL;
    Object Chain_of_available_gfi_queue_items_LOCAL;
    Object Chain_of_available_global_profiling_structures_LOCAL;
    Object Chain_of_available_goto_tag_entrys_LOCAL;
    Object Chain_of_available_graph_displays_LOCAL;
    Object Chain_of_available_graph_nodes_LOCAL;
    Object Chain_of_available_graph_renderings_LOCAL;
    Object Chain_of_available_graph_table_spots_LOCAL;
    Object Chain_of_available_graphic_character_sets_LOCAL;
    Object Chain_of_available_grid_panes_LOCAL;
    Object Chain_of_available_grid_view_cells_LOCAL;
    Object Chain_of_available_group_index_structures_LOCAL;
    Object Chain_of_available_gsi_array_wrappers_LOCAL;
    Object Chain_of_available_gsi_attributes_LOCAL;
    Object Chain_of_available_gsi_extension_datas_LOCAL;
    Object Chain_of_available_gsi_historys_LOCAL;
    Object Chain_of_available_gsi_icp_interfaces_LOCAL;
    Object Chain_of_available_gsi_instance_extensions_LOCAL;
    Object Chain_of_available_gsi_instances_LOCAL;
    Object Chain_of_available_gsi_local_functions_LOCAL;
    Object Chain_of_available_gsi_remote_procedures_LOCAL;
    Object Chain_of_available_gsi_transfer_wrappers_LOCAL;
    Object Chain_of_available_halt_infos_LOCAL;
    Object Chain_of_available_hfep_hanc_types_LOCAL;
    Object Chain_of_available_history_ring_buffers_LOCAL;
    Object Chain_of_available_hot_spot_states_LOCAL;
    Object Chain_of_available_html_views_LOCAL;
    Object Chain_of_available_i_am_alive_infos_LOCAL;
    Object Chain_of_available_icmp_sockets_LOCAL;
    Object Chain_of_available_icon_descriptions_LOCAL;
    Object Chain_of_available_icon_editor_buttons_LOCAL;
    Object Chain_of_available_icon_editor_engines_LOCAL;
    Object Chain_of_available_icon_editor_layers_pads_LOCAL;
    Object Chain_of_available_icon_editor_tables_LOCAL;
    Object Chain_of_available_icon_editor_translators_LOCAL;
    Object Chain_of_available_icon_editor_view_pads_LOCAL;
    Object Chain_of_available_icon_editors_LOCAL;
    Object Chain_of_available_icon_renderings_LOCAL;
    Object Chain_of_available_icon_slot_groups_LOCAL;
    Object Chain_of_available_icp_buffers_LOCAL;
    Object Chain_of_available_icp_ports_LOCAL;
    Object Chain_of_available_icp_read_tasks_LOCAL;
    Object Chain_of_available_icp_sockets_LOCAL;
    Object Chain_of_available_icp_write_tasks_LOCAL;
    Object Chain_of_available_identified_drawing_activitys_LOCAL;
    Object Chain_of_available_image_cvs_LOCAL;
    Object Chain_of_available_image_datas_LOCAL;
    Object Chain_of_available_image_plane_spots_LOCAL;
    Object Chain_of_available_image_planes_LOCAL;
    Object Chain_of_available_image_renderings_LOCAL;
    Object Chain_of_available_image_tiles_LOCAL;
    Object Chain_of_available_incomplete_painting_actions_LOCAL;
    Object Chain_of_available_incomplete_phrases_LOCAL;
    Object Chain_of_available_index_spaces_LOCAL;
    Object Chain_of_available_inference_background_collections_LOCAL;
    Object Chain_of_available_inform_message_informations_LOCAL;
    Object Chain_of_available_inlining_data_holders_LOCAL;
    Object Chain_of_available_input_table_spots_LOCAL;
    Object Chain_of_available_inspect_command_spots_LOCAL;
    Object Chain_of_available_integer_cvs_LOCAL;
    Object Chain_of_available_inter_g2_data_request_queues_LOCAL;
    Object Chain_of_available_internal_tokens_LOCAL;
    Object Chain_of_available_interned_lists_LOCAL;
    Object Chain_of_available_interned_remote_procedure_item_passing_infos_LOCAL;
    Object Chain_of_available_invalid_spots_LOCAL;
    Object Chain_of_available_iso_2022_transcoders_LOCAL;
    Object Chain_of_available_iso_646s_LOCAL;
    Object Chain_of_available_iso_8859_10s_LOCAL;
    Object Chain_of_available_iso_8859_1s_LOCAL;
    Object Chain_of_available_iso_8859_2s_LOCAL;
    Object Chain_of_available_iso_8859_3s_LOCAL;
    Object Chain_of_available_iso_8859_4s_LOCAL;
    Object Chain_of_available_iso_8859_5s_LOCAL;
    Object Chain_of_available_iso_8859_6s_LOCAL;
    Object Chain_of_available_iso_8859_7s_LOCAL;
    Object Chain_of_available_iso_8859_8s_LOCAL;
    Object Chain_of_available_iso_8859_9s_LOCAL;
    Object Chain_of_available_iso_8859_abstracts_LOCAL;
    Object Chain_of_available_iso_8859_transcoders_LOCAL;
    Object Chain_of_available_item_access_caches_LOCAL;
    Object Chain_of_available_item_represented_by_table_spots_LOCAL;
    Object Chain_of_available_java_classs_LOCAL;
    Object Chain_of_available_java_code_exceptions_LOCAL;
    Object Chain_of_available_java_codes_LOCAL;
    Object Chain_of_available_java_descriptors_LOCAL;
    Object Chain_of_available_java_fields_LOCAL;
    Object Chain_of_available_java_methods_LOCAL;
    Object Chain_of_available_java_symbols_LOCAL;
    Object Chain_of_available_javalink_versioned_call_datas_LOCAL;
    Object Chain_of_available_jis_x_0208s_LOCAL;
    Object Chain_of_available_kb_saves_LOCAL;
    Object Chain_of_available_kb_transfers_LOCAL;
    Object Chain_of_available_kb_workspace_image_plane_spots_LOCAL;
    Object Chain_of_available_kfep_batchs_LOCAL;
    Object Chain_of_available_kfep_conversion_choice_menu_button_spots_LOCAL;
    Object Chain_of_available_kfep_masters_LOCAL;
    Object Chain_of_available_ks_c_5601s_LOCAL;
    Object Chain_of_available_label_box_spots_LOCAL;
    Object Chain_of_available_large_scaled_font_buckets_LOCAL;
    Object Chain_of_available_layer_boxs_LOCAL;
    Object Chain_of_available_legend_panes_LOCAL;
    Object Chain_of_available_lexing_tables_LOCAL;
    Object Chain_of_available_line_drawing_for_printings_LOCAL;
    Object Chain_of_available_lisp_grid_views_LOCAL;
    Object Chain_of_available_list_box_cvs_LOCAL;
    Object Chain_of_available_local_events_LOCAL;
    Object Chain_of_available_local_nupec_variables_LOCAL;
    Object Chain_of_available_logbook_views_LOCAL;
    Object Chain_of_available_loose_end_spots_LOCAL;
    Object Chain_of_available_lru_elements_LOCAL;
    Object Chain_of_available_media_streams_LOCAL;
    Object Chain_of_available_memory_limit_infos_LOCAL;
    Object Chain_of_available_menu_button_spots_LOCAL;
    Object Chain_of_available_menu_choose_states_LOCAL;
    Object Chain_of_available_menu_item_spots_LOCAL;
    Object Chain_of_available_menu_pane_spots_LOCAL;
    Object Chain_of_available_menu_title_spots_LOCAL;
    Object Chain_of_available_meter_or_dial_spots_LOCAL;
    Object Chain_of_available_meter_spots_LOCAL;
    Object Chain_of_available_minimal_character_descriptions_LOCAL;
    Object Chain_of_available_modal_menu_states_LOCAL;
    Object Chain_of_available_model_queues_LOCAL;
    Object Chain_of_available_model_runtime_infos_LOCAL;
    Object Chain_of_available_modify_control_action_types_LOCAL;
    Object Chain_of_available_modify_control_structures_LOCAL;
    Object Chain_of_available_modify_dialog_structures_LOCAL;
    Object Chain_of_available_mouse_drag_detector_states_LOCAL;
    Object Chain_of_available_mouse_pointers_LOCAL;
    Object Chain_of_available_mouse_watch_states_LOCAL;
    Object Chain_of_available_move_dragging_states_LOCAL;
    Object Chain_of_available_multiframe_table_spots_LOCAL;
    Object Chain_of_available_multiply_wild_regular_expression_nodes_LOCAL;
    Object Chain_of_available_name_box_spots_LOCAL;
    Object Chain_of_available_named_gensym_structures_LOCAL;
    Object Chain_of_available_native_dialogs_LOCAL;
    Object Chain_of_available_native_fonts_LOCAL;
    Object Chain_of_available_native_simple_dialog_states_LOCAL;
    Object Chain_of_available_native_windows_LOCAL;
    Object Chain_of_available_new_table_background_spots_LOCAL;
    Object Chain_of_available_new_table_cell_spots_LOCAL;
    Object Chain_of_available_new_table_spots_LOCAL;
    Object Chain_of_available_nms_menu_items_LOCAL;
    Object Chain_of_available_nms_menus_LOCAL;
    Object Chain_of_available_non_kb_workspace_image_plane_spots_LOCAL;
    Object Chain_of_available_normal_completions_LOCAL;
    Object Chain_of_available_nupec_synchronize_variable_or_parameters_LOCAL;
    Object Chain_of_available_object_building_problems_LOCAL;
    Object Chain_of_available_object_passing_infos_LOCAL;
    Object Chain_of_available_ok_file_tokens_LOCAL;
    Object Chain_of_available_output_only_table_spots_LOCAL;
    Object Chain_of_available_outside_window_spots_LOCAL;
    Object Chain_of_available_overview_pane_spots_LOCAL;
    Object Chain_of_available_pane_background_spots_LOCAL;
    Object Chain_of_available_pane_border_spots_LOCAL;
    Object Chain_of_available_pane_component_spots_LOCAL;
    Object Chain_of_available_pane_spots_LOCAL;
    Object Chain_of_available_panes_LOCAL;
    Object Chain_of_available_parse_objects_LOCAL;
    Object Chain_of_available_parse_tables_LOCAL;
    Object Chain_of_available_parsing_contexts_LOCAL;
    Object Chain_of_available_parsing_tokens_LOCAL;
    Object Chain_of_available_partial_commands_LOCAL;
    Object Chain_of_available_pathname_component_token_menu_button_spots_LOCAL;
    Object Chain_of_available_pending_activitys_LOCAL;
    Object Chain_of_available_phrase_rule_completions_LOCAL;
    Object Chain_of_available_pixmaps_LOCAL;
    Object Chain_of_available_place_reference_internalss_LOCAL;
    Object Chain_of_available_plot_data_ring_buffers_LOCAL;
    Object Chain_of_available_possible_phrases_LOCAL;
    Object Chain_of_available_procedure_invocations_LOCAL;
    Object Chain_of_available_processs_LOCAL;
    Object Chain_of_available_productions_LOCAL;
    Object Chain_of_available_prop_grid_verbs_LOCAL;
    Object Chain_of_available_property_grid_nodes_LOCAL;
    Object Chain_of_available_property_grids_LOCAL;
    Object Chain_of_available_pseudo_attributes_LOCAL;
    Object Chain_of_available_pseudo_frames_LOCAL;
    Object Chain_of_available_pseudo_instruction_streams_LOCAL;
    Object Chain_of_available_push_button_cvs_LOCAL;
    Object Chain_of_available_quantity_cvs_LOCAL;
    Object Chain_of_available_query_cell_streams_LOCAL;
    Object Chain_of_available_queue_elements_LOCAL;
    Object Chain_of_available_queues_LOCAL;
    Object Chain_of_available_readout_table_spots_LOCAL;
    Object Chain_of_available_receiving_resumable_objects_LOCAL;
    Object Chain_of_available_receiving_rpc_arglist_structures_LOCAL;
    Object Chain_of_available_reference_structures_LOCAL;
    Object Chain_of_available_region_bounds_and_rasters_LOCAL;
    Object Chain_of_available_regular_expression_node_for_set_of_characterss_LOCAL;
    Object Chain_of_available_regular_expression_node_for_single_characters_LOCAL;
    Object Chain_of_available_regular_expression_node_for_single_wild_characters_LOCAL;
    Object Chain_of_available_regular_expression_node_for_subexpressions_LOCAL;
    Object Chain_of_available_regular_expression_node_for_wild_characterss_LOCAL;
    Object Chain_of_available_regular_expression_nodes_LOCAL;
    Object Chain_of_available_relation_instances_LOCAL;
    Object Chain_of_available_relative_time_panes_LOCAL;
    Object Chain_of_available_remote_procedure_calls_LOCAL;
    Object Chain_of_available_remote_procedure_identifiers_LOCAL;
    Object Chain_of_available_remote_procedure_item_passing_infos_LOCAL;
    Object Chain_of_available_remote_procedure_names_LOCAL;
    Object Chain_of_available_replacement_token_menu_button_spots_LOCAL;
    Object Chain_of_available_resize_box_spots_LOCAL;
    Object Chain_of_available_resumable_circular_nodes_LOCAL;
    Object Chain_of_available_resumable_evaluation_sequence_node_mixins_LOCAL;
    Object Chain_of_available_resumable_evaluation_sequence_nodes_LOCAL;
    Object Chain_of_available_resumable_evaluation_structure_nodes_LOCAL;
    Object Chain_of_available_resumable_history_nodes_LOCAL;
    Object Chain_of_available_resumable_icp_node_mixins_LOCAL;
    Object Chain_of_available_resumable_icp_object_mixins_LOCAL;
    Object Chain_of_available_resumable_instance_node_mixins_LOCAL;
    Object Chain_of_available_resumable_instance_or_complex_value_node_mixins_LOCAL;
    Object Chain_of_available_resumable_list_node_mixins_LOCAL;
    Object Chain_of_available_resumable_node_mixins_LOCAL;
    Object Chain_of_available_resumable_object_list_nodes_LOCAL;
    Object Chain_of_available_resumable_object_mixins_LOCAL;
    Object Chain_of_available_resumable_object_nodes_LOCAL;
    Object Chain_of_available_resumable_object_vector_nodes_LOCAL;
    Object Chain_of_available_resumable_sequence_node_mixins_LOCAL;
    Object Chain_of_available_resumable_value_list_nodes_LOCAL;
    Object Chain_of_available_resumable_value_nodes_LOCAL;
    Object Chain_of_available_resumable_value_vector_nodes_LOCAL;
    Object Chain_of_available_resumable_vector_node_mixins_LOCAL;
    Object Chain_of_available_ring_buffer_states_LOCAL;
    Object Chain_of_available_ring_raster_for_graphs_LOCAL;
    Object Chain_of_available_rule_instances_LOCAL;
    Object Chain_of_available_saving_contexts_LOCAL;
    Object Chain_of_available_scaled_fonts_LOCAL;
    Object Chain_of_available_schedule_tasks_LOCAL;
    Object Chain_of_available_scheduled_remote_procedure_starts_LOCAL;
    Object Chain_of_available_search_state_table_spots_LOCAL;
    Object Chain_of_available_selection_handle_spots_LOCAL;
    Object Chain_of_available_selection_rectangle_states_LOCAL;
    Object Chain_of_available_selections_LOCAL;
    Object Chain_of_available_sending_resumable_objects_LOCAL;
    Object Chain_of_available_sensor_groups_LOCAL;
    Object Chain_of_available_sensor_groups_headers_LOCAL;
    Object Chain_of_available_set_of_possible_phrasess_LOCAL;
    Object Chain_of_available_shift_jis_transcoders_LOCAL;
    Object Chain_of_available_short_duration_cvs_LOCAL;
    Object Chain_of_available_short_representation_table_spots_LOCAL;
    Object Chain_of_available_shortcut_bars_LOCAL;
    Object Chain_of_available_show_parameters_decoders_LOCAL;
    Object Chain_of_available_shredded_rasters_LOCAL;
    Object Chain_of_available_simple_item_spots_LOCAL;
    Object Chain_of_available_simulation_infos_LOCAL;
    Object Chain_of_available_skip_list_elements_LOCAL;
    Object Chain_of_available_slider_spots_LOCAL;
    Object Chain_of_available_slot_component_descriptors_LOCAL;
    Object Chain_of_available_slot_descriptions_LOCAL;
    Object Chain_of_available_snapshot_invocation_infos_LOCAL;
    Object Chain_of_available_snapshot_of_blocks_LOCAL;
    Object Chain_of_available_socket_output_buffers_LOCAL;
    Object Chain_of_available_sockets_LOCAL;
    Object Chain_of_available_source_nupec_synchronizations_LOCAL;
    Object Chain_of_available_sparse_arrays_LOCAL;
    Object Chain_of_available_spinner_cvs_LOCAL;
    Object Chain_of_available_spots_LOCAL;
    Object Chain_of_available_stack_node_instructions_LOCAL;
    Object Chain_of_available_stack_nodes_LOCAL;
    Object Chain_of_available_state_transitions_LOCAL;
    Object Chain_of_available_status_bar_panes_LOCAL;
    Object Chain_of_available_status_bars_LOCAL;
    Object Chain_of_available_status_pane_spots_LOCAL;
    Object Chain_of_available_stepper_of_scroll_bar_spots_LOCAL;
    Object Chain_of_available_strict_subcategory_infos_LOCAL;
    Object Chain_of_available_sub_profiling_structures_LOCAL;
    Object Chain_of_available_subcommand_menu_button_spots_LOCAL;
    Object Chain_of_available_subcommand_states_LOCAL;
    Object Chain_of_available_symbol_trees_LOCAL;
    Object Chain_of_available_system_rpc_instances_LOCAL;
    Object Chain_of_available_system_rpcs_LOCAL;
    Object Chain_of_available_t2_nonce_datas_LOCAL;
    Object Chain_of_available_table_background_spots_LOCAL;
    Object Chain_of_available_table_header_spots_LOCAL;
    Object Chain_of_available_table_spots_LOCAL;
    Object Chain_of_available_tabular_views_LOCAL;
    Object Chain_of_available_target_nupec_synchronizations_LOCAL;
    Object Chain_of_available_tcp_sockets_LOCAL;
    Object Chain_of_available_temporary_constants_LOCAL;
    Object Chain_of_available_text_box_cvs_LOCAL;
    Object Chain_of_available_text_box_spots_LOCAL;
    Object Chain_of_available_text_inserter_spots_LOCAL;
    Object Chain_of_available_text_marking_states_LOCAL;
    Object Chain_of_available_text_sequences_LOCAL;
    Object Chain_of_available_text_spots_LOCAL;
    Object Chain_of_available_text_tokenization_states_LOCAL;
    Object Chain_of_available_thrashing_ratio_ring_buffers_LOCAL;
    Object Chain_of_available_tiled_rasters_LOCAL;
    Object Chain_of_available_tiling_patterns_LOCAL;
    Object Chain_of_available_time_of_day_cvs_LOCAL;
    Object Chain_of_available_title_bar_spots_LOCAL;
    Object Chain_of_available_token_menu_button_spots_LOCAL;
    Object Chain_of_available_top_level_states_LOCAL;
    Object Chain_of_available_transcode_text_conversion_styles_LOCAL;
    Object Chain_of_available_transcoders_LOCAL;
    Object Chain_of_available_transfer_dragging_states_LOCAL;
    Object Chain_of_available_tree_view_nodes_LOCAL;
    Object Chain_of_available_tree_views_LOCAL;
    Object Chain_of_available_trend_chart_panes_LOCAL;
    Object Chain_of_available_trend_chart_spots_LOCAL;
    Object Chain_of_available_type_descriptions_LOCAL;
    Object Chain_of_available_type_in_box_spots_LOCAL;
    Object Chain_of_available_ui_callbacks_LOCAL;
    Object Chain_of_available_unicode_blocks_LOCAL;
    Object Chain_of_available_unicode_byte_swapped_transcoders_LOCAL;
    Object Chain_of_available_unicode_transcoders_LOCAL;
    Object Chain_of_available_unicode_ucs_2_transcoders_LOCAL;
    Object Chain_of_available_uninteresting_block_spots_LOCAL;
    Object Chain_of_available_uri_references_LOCAL;
    Object Chain_of_available_user_mode_aliass_LOCAL;
    Object Chain_of_available_user_mouse_tracking_states_LOCAL;
    Object Chain_of_available_utf_7_transcoders_LOCAL;
    Object Chain_of_available_utf_8_transcoders_LOCAL;
    Object Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_LOCAL;
    Object Chain_of_available_utf_g_transcoders_LOCAL;
    Object Chain_of_available_uuid_blocks_LOCAL;
    Object Chain_of_available_variable_group_update_structures_LOCAL;
    Object Chain_of_available_variable_simulation_runtime_structures_LOCAL;
    Object Chain_of_available_virtual_attributes_LOCAL;
    Object Chain_of_available_walking_menus_states_LOCAL;
    Object Chain_of_available_wide_string_text_sequences_LOCAL;
    Object Chain_of_available_widget_pending_states_LOCAL;
    Object Chain_of_available_workspace_background_spots_LOCAL;
    Object Chain_of_available_workspace_dock_spots_LOCAL;
    Object Chain_of_available_workspace_regions_LOCAL;
    Object Chain_of_available_workspace_views_LOCAL;
    Object Chain_of_available_workstation_context_frames_LOCAL;
    Object Chain_of_available_workstation_context_with_selection_focuss_LOCAL;
    Object Chain_of_available_workstation_contexts_LOCAL;
    Object Chain_of_available_workstation_events_LOCAL;
    Object Chain_of_available_workstations_LOCAL;
    Object Chain_of_available_ws_representation_types_LOCAL;
    Object Chain_of_available_xml_namespace_lists_LOCAL;
    Object Chain_of_available_xml_namespaces_LOCAL;
    Object Chain_of_available_xml_node_lists_LOCAL;
    Object Chain_of_available_xml_nodes_LOCAL;
    Object Chain_of_available_xml_structures_LOCAL;
    Object Chain_of_recycled_edit_states_LOCAL;
    Object Chaining_refresh_list_LOCAL;
    Object Chaining_refresh_version_LOCAL;
    Object Change_the_text_of_attributes_without_category_evaluator_interfaces_p_LOCAL;
    Object Changing_colors_of_graphic_elements_qm_LOCAL;
    Object Changing_graph_margins_qm_LOCAL;
    Object Changing_validity_interval_invalidates_current_value_p_LOCAL;
    Object Character_bitmap_scratch_list_LOCAL;
    Object Character_case_mode_for_generalized_dos_LOCAL;
    Object Character_description_count_LOCAL;
    Object Character_image_count_LOCAL;
    Object Character_sequence_token_menu_button_spot_count_LOCAL;
    Object Characters_in_buffer_of_ok_file_reader_qm_LOCAL;
    Object Chart_LOCAL;
    Object Chart_bottom_LOCAL;
    Object Chart_bottom_margin_LOCAL;
    Object Chart_class_description_LOCAL;
    Object Chart_color_value_for_this_raster_LOCAL;
    Object Chart_current_raster_is_monochrome_raster_list_p_LOCAL;
    Object Chart_current_raster_is_polychrome_p_LOCAL;
    Object Chart_data_point_LOCAL;
    Object Chart_drawing_LOCAL;
    Object Chart_left_LOCAL;
    Object Chart_left_margin_LOCAL;
    Object Chart_origin_x_LOCAL;
    Object Chart_origin_y_LOCAL;
    Object Chart_pen_color_LOCAL;
    Object Chart_pen_color_value_LOCAL;
    Object Chart_pen_x_LOCAL;
    Object Chart_pen_y_LOCAL;
    Object Chart_really_drawing_LOCAL;
    Object Chart_right_LOCAL;
    Object Chart_right_margin_LOCAL;
    Object Chart_spot_count_LOCAL;
    Object Chart_top_LOCAL;
    Object Chart_top_margin_LOCAL;
    Object Chart_tuple_1_maximum_LOCAL;
    Object Chart_tuple_1_minimum_LOCAL;
    Object Chart_tuple_2_maximum_LOCAL;
    Object Chart_tuple_2_minimum_LOCAL;
    Object Chart_view_count_LOCAL;
    Object Charting_library_version_qm_LOCAL;
    Object Check_box_cv_count_LOCAL;
    Object Check_for_circular_formula_paths_qm_LOCAL;
    Object Check_icp_handshaking_p_LOCAL;
    Object Check_time_on_next_uuid_LOCAL;
    Object Checkable_list_box_cv_count_LOCAL;
    Object Choice_conflict_LOCAL;
    Object Class_and_foundation_class_directory_categories_LOCAL;
    Object Class_bit_numbers_pool_LOCAL;
    Object Class_change_timestamp_LOCAL;
    Object Class_definition_class_description_LOCAL;
    Object Class_description_cons_counter_LOCAL;
    Object Class_description_count_LOCAL;
    Object Class_description_for_next_frame_qm_LOCAL;
    Object Class_file_stream_count_LOCAL;
    Object Class_info_attributes_LOCAL;
    Object Class_instance_header_type_of_slot_LOCAL;
    Object Class_instances_memory_info_count_LOCAL;
    Object Class_is_undergoing_inheritance_change_qm_LOCAL;
    Object Class_name_conflicts_LOCAL;
    Object Class_name_max_length_LOCAL;
    Object Class_name_read_while_reading_current_ghost_definition_LOCAL;
    Object Class_specific_instances_lock_LOCAL;
    Object Class_subscription_count_LOCAL;
    Object Class_subscriptions_count_LOCAL;
    Object Classes_and_directory_categories_for_classes_LOCAL;
    Object Classes_needing_data_interface_initialization_LOCAL;
    Object Classes_not_defined_in_any_module_LOCAL;
    Object Classes_of_objects_to_not_consider_qm_LOCAL;
    Object Classes_remaining_to_sort_LOCAL;
    Object Classes_sorted_so_far_LOCAL;
    Object Classes_visited_byte_vector_LOCAL;
    Object Classes_whose_superiors_are_not_defined_in_required_modules_LOCAL;
    Object Clear_text_grammar_rules_added_p_LOCAL;
    Object Clear_text_item_layering_info_LOCAL;
    Object Clear_text_primitive_value_style_LOCAL;
    Object Clear_text_saving_problems_were_encountered_p_LOCAL;
    Object Clipping_rectangles_for_new_data_qm_LOCAL;
    Object Clock_sequence_for_uuid_LOCAL;
    Object Clogged_count_LOCAL;
    Object Close_box_rubber_stamp_widget_LOCAL;
    Object Close_box_spot_count_LOCAL;
    Object Closing_procedure_invocation_LOCAL;
    Object Code_body_LOCAL;
    Object Code_body_continuation_count_LOCAL;
    Object Code_body_entries_in_compilation_LOCAL;
    Object Code_body_invocation_count_LOCAL;
    Object Collected_frame_notes_for_class_export_qm_LOCAL;
    Object Collected_items_with_warnings_alist_LOCAL;
    Object Collected_menu_content_structure_LOCAL;
    Object Collected_updates_to_sensor_attributes_LOCAL;
    Object Collecting_denotation_errors_p_LOCAL;
    Object Collecting_exported_method_text_p_LOCAL;
    Object Collecting_frame_notes_for_class_export_p_LOCAL;
    Object Collecting_free_references_LOCAL;
    Object Collecting_procedures_to_warn_about_p_LOCAL;
    Object Collecting_updates_to_sensor_attributes_p_LOCAL;
    Object Collecting_warnings_p_LOCAL;
    Object Color_change_indicator_LOCAL;
    Object Color_changes_indicator_LOCAL;
    Object Color_code_differences_LOCAL;
    Object Color_difference_for_line_of_text_of_graphic_element_LOCAL;
    Object Color_hierarchy_LOCAL;
    Object Color_map_count_LOCAL;
    Object Color_parameters_LOCAL;
    Object Color_values_of_graph_rasters_of_graphic_element_LOCAL;
    Object Column_LOCAL;
    Object Column_maximum_LOCAL;
    Object Column_width_LOCAL;
    Object Combiners_for_defun_incremental_LOCAL;
    Object Command_line_qm_LOCAL;
    Object Comp_trace_level_LOCAL;
    Object Compare_xml_collect_diffs_p_LOCAL;
    Object Compilation_local_name_listed_next_symbol_LOCAL;
    Object Compilation_local_name_symbol_counter_LOCAL;
    Object Compilation_local_name_symbol_supply_LOCAL;
    Object Compilations_were_removed_in_this_kb_module_qm_LOCAL;
    Object Compile_reference_to_system_slot_LOCAL;
    Object Compiled_antecedent_1_LOCAL;
    Object Compiled_cell_expression_LOCAL;
    Object Compiled_code_grammar_rules_added_p_LOCAL;
    Object Compiled_consequent_1_LOCAL;
    Object Compiled_consequent_2_LOCAL;
    Object Compiled_item_being_analyzed_LOCAL;
    Object Compiled_item_being_analyzed_started_out_incomplete_qm_LOCAL;
    Object Compiled_items_deferred_for_analysis_LOCAL;
    Object Compiled_kb_indent_LOCAL;
    Object Compiled_kb_initialization_array_initialized_p_LOCAL;
    Object Compiled_resource_count_LOCAL;
    Object Compiler_code_body_entry_count_LOCAL;
    Object Compiler_cons_counter_LOCAL;
    Object Compiler_errors_LOCAL;
    Object Compiler_free_references_LOCAL;
    Object Compiler_warnings_LOCAL;
    Object Compiling_antecedent_p_LOCAL;
    Object Compiling_expression_p_LOCAL;
    Object Compiling_incomplete_items_after_analyze_p_LOCAL;
    Object Compiling_rule_p_LOCAL;
    Object Complete_kb_name_qm_LOCAL;
    Object Component_change_report_count_LOCAL;
    Object Compound_fixnum_simulation_time_count_LOCAL;
    Object Compound_slot_descriptor_count_LOCAL;
    Object Compound_type_descriptor_count_LOCAL;
    Object Computation_frame_at_breakpoint_LOCAL;
    Object Computation_instance_at_breakpoint_LOCAL;
    Object Computation_instance_count_LOCAL;
    Object Computation_style_description_LOCAL;
    Object Compute_menu_items_list_LOCAL;
    Object Conclude_attribute_binding_listed_next_symbol_LOCAL;
    Object Conclude_attribute_binding_symbol_counter_LOCAL;
    Object Conclude_attribute_binding_symbol_supply_LOCAL;
    Object Conclude_parent_attribute_bindings_LOCAL;
    Object Conditional_selected_choice_qm_LOCAL;
    Object Conditional_termination_state_qm_LOCAL;
    Object Connected_subnet_LOCAL;
    Object Connection_class_description_LOCAL;
    Object Connection_classes_warned_about_for_this_kb_LOCAL;
    Object Connection_cons_counter_LOCAL;
    Object Connection_count_LOCAL;
    Object Connection_definition_class_description_LOCAL;
    Object Connection_handling_block_queue_LOCAL;
    Object Connection_handling_connection_queue_LOCAL;
    Object Connection_handling_connection_type_queue_LOCAL;
    Object Connection_handling_fsn_queue_LOCAL;
    Object Connection_handling_procedure_fsn_qm_LOCAL;
    Object Connection_handling_procedure_qm_LOCAL;
    Object Connection_handling_window_queue_LOCAL;
    Object Connection_item_count_LOCAL;
    Object Connection_post_class_description_LOCAL;
    Object Connection_spot_count_LOCAL;
    Object Connection_subrectangle_structure_count_LOCAL;
    Object Connections_in_connection_paths_LOCAL;
    Object Connections_in_modules_a_list_LOCAL;
    Object Connections_to_be_excluded_qm_LOCAL;
    Object Connections_to_delete_after_reading_kb_LOCAL;
    Object Consider_asian_language_initializations_qm_LOCAL;
    Object Consistency_tree_focus_shifts_LOCAL;
    Object Contains_either_really_transient_or_proprietary_p_1_LOCAL;
    Object Contains_proprietary_p_1_LOCAL;
    Object Context_iteration_forms_LOCAL;
    Object Context_of_type_failure_LOCAL;
    Object Continuation_task_for_current_backup_LOCAL;
    Object Continue_current_kb_save_failure_LOCAL;
    Object Contour_of_ok_file_tokens_LOCAL;
    Object Control_sequence_record_LOCAL;
    Object Control_stack_of_frame_projecting_LOCAL;
    Object Convert_file_strings_to_uppercase_p_LOCAL;
    Object Copyright_boilerplate_lines_of_text_1_LOCAL;
    Object Copyright_boilerplate_lines_of_text_2_LOCAL;
    Object Corresponding_icp_object_index_for_item_new_copy_LOCAL;
    Object Corresponding_icp_object_index_for_item_reference_LOCAL;
    Object Count_of_8859_reverse_unicode_map_hash_vector_43_vectors_LOCAL;
    Object Count_of_blocks_hash_hash_vector_43_vectors_LOCAL;
    Object Count_of_call_hash_hash_vector_43_vectors_LOCAL;
    Object Count_of_duplicates_check_hash_table_hash_vector_50021_vectors_LOCAL;
    Object Count_of_dynamic_rule_displays_hash_vector_43_vectors_LOCAL;
    Object Count_of_foreign_function_registry_internal_hash_vector_131_vectors_LOCAL;
    Object Count_of_frame_serial_number_to_item_table_hash_vector_67_vectors_LOCAL;
    Object Count_of_generic_rule_instance_displays_hash_vector_43_vectors_LOCAL;
    Object Count_of_gfi_spreadsheet_field_index_hash_vector_131_vectors_LOCAL;
    Object Count_of_graph_node_of_graphed_thing_hash_vector_43_vectors_LOCAL;
    Object Count_of_hashed_rule_instance_hash_vector_43_vectors_LOCAL;
    Object Count_of_indexed_attribute_parent_objects_hash_vector_43_vectors_LOCAL;
    Object Count_of_interned_gensym_strings_LOCAL;
    Object Count_of_interned_text_strings_LOCAL;
    Object Count_of_item_or_name_hash_hash_vector_43_vectors_LOCAL;
    Object Count_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_LOCAL;
    Object Count_of_jis_map_hash_vector_307_vectors_LOCAL;
    Object Count_of_kanji_font_cache_vector_137_vectors_LOCAL;
    Object Count_of_kb_fsn_hash_table_hash_vector_131_vectors_LOCAL;
    Object Count_of_module_required_by_relationships_hash_vector_43_vectors_LOCAL;
    Object Count_of_native_font_set_width_equivalence_table_256_vectors_LOCAL;
    Object Count_of_native_icon_handle_hash_vector_43_vectors_LOCAL;
    Object Count_of_nms_menu_for_hmenu_hash_vector_43_vectors_LOCAL;
    Object Count_of_non_kanji_font_vector_257_vectors_LOCAL;
    Object Count_of_object_circularity_hashtable_hash_vector_131_vectors_LOCAL;
    Object Count_of_pending_workspace_drawing_LOCAL;
    Object Count_of_procedure_invocations_hash_vector_43_vectors_LOCAL;
    Object Count_of_representation_handle_hash_vector_109_vectors_LOCAL;
    Object Count_of_scaled_font_kanji_font_cache_vector_1096_vectors_LOCAL;
    Object Count_of_scaled_font_non_kanji_font_vector_2049_vectors_LOCAL;
    Object Count_of_sexp_annotation_hash_vector_43_vectors_LOCAL;
    Object Count_of_sub_call_hash_hash_vector_43_vectors_LOCAL;
    Object Count_of_subseries_of_values_64_vectors_LOCAL;
    Object Count_of_sysproc_continuation_hashtable_hash_vector_131_vectors_LOCAL;
    Object Count_of_tracked_items_call_vector_table_hash_vector_43_vectors_LOCAL;
    Object Count_of_ui_callback_table_hash_vector_43_vectors_LOCAL;
    Object Count_of_uo_memory_usage_information_hash_vector_43_vectors_LOCAL;
    Object Count_of_user_hash_table_internal_hash_vector_43_vectors_LOCAL;
    Object Count_of_variable_fill_icp_buffer_4096_vectors_LOCAL;
    Object Countdown_for_checking_LOCAL;
    Object Create_frames_and_connections_reading_past_qm_LOCAL;
    Object Create_process_instance_for_current_process_p_LOCAL;
    Object Create_subpart_upon_tracking_p_LOCAL;
    Object Created_oversized_simple_float_array_pool_arrays_LOCAL;
    Object Created_simple_float_array_pool_arrays_LOCAL;
    Object Created_simple_long_array_pool_arrays_LOCAL;
    Object Created_simple_vector_pool_vectors_LOCAL;
    Object Credits_table_spot_count_LOCAL;
    Object Ctlc_cons_count_LOCAL;
    Object Cumulative_x_scaled_connection_stripe_half_width_LOCAL;
    Object Cumulative_x_scaled_connection_stripe_width_LOCAL;
    Object Cumulative_y_scaled_connection_stripe_half_width_LOCAL;
    Object Cumulative_y_scaled_connection_stripe_width_LOCAL;
    Object Current_2d_rendering_LOCAL;
    Object Current_2d_state_LOCAL;
    Object Current_a_matrix_LOCAL;
    Object Current_ab_font_qm_LOCAL;
    Object Current_agenda_accumulating_LOCAL;
    Object Current_anchor_p_LOCAL;
    Object Current_annotated_frame_LOCAL;
    Object Current_attribute_description_class_LOCAL;
    Object Current_attribute_description_index_LOCAL;
    Object Current_attribute_file_pathname_qm_LOCAL;
    Object Current_axis_LOCAL;
    Object Current_axis_pane_LOCAL;
    Object Current_b_vector_LOCAL;
    Object Current_background_color_value_LOCAL;
    Object Current_background_process_LOCAL;
    Object Current_backup_definition_workspace_qm_LOCAL;
    Object Current_backup_definition_workspace_serial_number_qm_LOCAL;
    Object Current_basic_part_LOCAL;
    Object Current_best_match_for_eyes_LOCAL;
    Object Current_block_of_dependent_frame_LOCAL;
    Object Current_callback_representation_subscription_handle_LOCAL;
    Object Current_cascaded_ring_buffer_LOCAL;
    Object Current_category_name_for_type_specification_type_p_LOCAL;
    Object Current_category_visit_stamp_LOCAL;
    Object Current_cell_LOCAL;
    Object Current_character_LOCAL;
    Object Current_character_index_after_token_LOCAL;
    Object Current_character_syntax_table_LOCAL;
    Object Current_chart_LOCAL;
    Object Current_chart_data_point_LOCAL;
    Object Current_chart_frame_LOCAL;
    Object Current_chart_raster_color_value_LOCAL;
    Object Current_code_body_entry_LOCAL;
    Object Current_color_map_LOCAL;
    Object Current_column_LOCAL;
    Object Current_compiled_cell_expression_LOCAL;
    Object Current_component_type_for_sorting_LOCAL;
    Object Current_computation_activity_LOCAL;
    Object Current_computation_component_particulars_LOCAL;
    Object Current_computation_flags_LOCAL;
    Object Current_computation_frame_LOCAL;
    Object Current_computation_instance_LOCAL;
    Object Current_computation_slot_component_group_LOCAL;
    Object Current_computation_style_LOCAL;
    Object Current_computation_style_description_LOCAL;
    Object Current_conclude_frame_list_LOCAL;
    Object Current_conclude_innermost_attribute_description_LOCAL;
    Object Current_conclude_innermost_frame_LOCAL;
    Object Current_conclude_innermost_item_index_LOCAL;
    Object Current_connection_path_LOCAL;
    Object Current_create_frame_description_reference_1_LOCAL;
    Object Current_custom_reclamation_stamp_qm_LOCAL;
    Object Current_cvs_command_LOCAL;
    Object Current_data_buffer_for_plot_LOCAL;
    Object Current_data_series_LOCAL;
    Object Current_ddd_dot_dddd_format_qm_LOCAL;
    Object Current_default_line_color_LOCAL;
    Object Current_delta_LOCAL;
    Object Current_description_of_new_table_LOCAL;
    Object Current_dialog_errors_structure_LOCAL;
    Object Current_directory_of_binary_truenames_LOCAL;
    Object Current_directory_of_source_truenames_qm_LOCAL;
    Object Current_display_pane_bottom_LOCAL;
    Object Current_display_pane_height_LOCAL;
    Object Current_display_pane_left_LOCAL;
    Object Current_display_pane_right_LOCAL;
    Object Current_display_pane_top_LOCAL;
    Object Current_display_pane_width_LOCAL;
    Object Current_dragging_states_LOCAL;
    Object Current_draw_document_p_LOCAL;
    Object Current_draw_paper_p_LOCAL;
    Object Current_drawing_priority_LOCAL;
    Object Current_drawing_transfer_mode_LOCAL;
    Object Current_edit_state_LOCAL;
    Object Current_edit_workspace_LOCAL;
    Object Current_environment_LOCAL;
    Object Current_extended_utf_g_low_half_character_qm_LOCAL;
    Object Current_filters_search_result_LOCAL;
    Object Current_foreground_color_value_LOCAL;
    Object Current_foreign_function_call_info_LOCAL;
    Object Current_foreign_image_pathname_qm_LOCAL;
    Object Current_formatted_part_LOCAL;
    Object Current_frame_serial_number_LOCAL;
    Object Current_frame_serial_number_before_reading_LOCAL;
    Object Current_frame_transform_qm_LOCAL;
    Object Current_g2_rdf_module_LOCAL;
    Object Current_g2_time_LOCAL;
    Object Current_g2_user_mode_qm_LOCAL;
    Object Current_g2_window_for_this_workstation_qm_LOCAL;
    Object Current_g2binary_file_symbol_index_LOCAL;
    Object Current_g2gl_definition_LOCAL;
    Object Current_gensym_string_LOCAL;
    Object Current_gensym_window_serial_number_LOCAL;
    Object Current_gesture_code_sequence_LOCAL;
    Object Current_gesture_code_sequences_LOCAL;
    Object Current_gesture_frame_pointer_LOCAL;
    Object Current_gesture_label_index_LOCAL;
    Object Current_gesture_sequence_index_LOCAL;
    Object Current_gesture_stack_pointer_LOCAL;
    Object Current_grammar_LOCAL;
    Object Current_graph_grid_LOCAL;
    Object Current_graph_grid_in_minimal_update_LOCAL;
    Object Current_graph_layout_hashing_function_LOCAL;
    Object Current_graph_rendering_LOCAL;
    Object Current_graph_rendering_embedded_icons_LOCAL;
    Object Current_graph_rendering_structure_LOCAL;
    Object Current_grid_LOCAL;
    Object Current_grid_painting_actions_to_delete_LOCAL;
    Object Current_grid_painting_background_color_value_LOCAL;
    Object Current_grid_painting_color_mode_LOCAL;
    Object Current_grid_painting_earliest_time_LOCAL;
    Object Current_grid_painting_foreground_color_value_LOCAL;
    Object Current_grid_painting_is_full_qm_LOCAL;
    Object Current_grid_painting_latest_time_LOCAL;
    Object Current_grid_painting_mode_LOCAL;
    Object Current_grid_painting_queue_LOCAL;
    Object Current_grid_painting_queue_tail_LOCAL;
    Object Current_grid_painting_x_scale_LOCAL;
    Object Current_grid_painting_y_scale_LOCAL;
    Object Current_height_of_formatted_part_LOCAL;
    Object Current_hfep_c_act_LOCAL;
    Object Current_hfep_c_state_LOCAL;
    Object Current_hfep_cchar_LOCAL;
    Object Current_hfep_nchar_LOCAL;
    Object Current_icon_editor_LOCAL;
    Object Current_icon_editor_event_LOCAL;
    Object Current_icon_editor_workspace_LOCAL;
    Object Current_icon_substitution_list_LOCAL;
    Object Current_icon_untransformed_height_LOCAL;
    Object Current_icon_untransformed_width_LOCAL;
    Object Current_icon_variables_override_plist_LOCAL;
    Object Current_icon_variables_plist_LOCAL;
    Object Current_icp_buffer_LOCAL;
    Object Current_icp_port_LOCAL;
    Object Current_icp_read_trace_level_LOCAL;
    Object Current_icp_socket_LOCAL;
    Object Current_icp_write_trace_level_LOCAL;
    Object Current_image_plane_LOCAL;
    Object Current_image_plane_for_button_LOCAL;
    Object Current_image_plane_qm_LOCAL;
    Object Current_image_x_scale_LOCAL;
    Object Current_image_y_scale_LOCAL;
    Object Current_include_denotation_for_block_flag_LOCAL;
    Object Current_index_LOCAL;
    Object Current_index_array_LOCAL;
    Object Current_indicator_for_category_of_symbol_token_LOCAL;
    Object Current_indicator_for_category_of_this_name_LOCAL;
    Object Current_input_stack_LOCAL;
    Object Current_invocation_remotely_started_p_LOCAL;
    Object Current_jemit_args_LOCAL;
    Object Current_jemit_class_description_LOCAL;
    Object Current_jemit_class_object_table_LOCAL;
    Object Current_jemit_compound_statement_list_LOCAL;
    Object Current_jemit_indent_LOCAL;
    Object Current_jemit_locals_LOCAL;
    Object Current_jemit_node_stack_LOCAL;
    Object Current_jemit_return_type_specification_qm_LOCAL;
    Object Current_jemit_self_name_LOCAL;
    Object Current_jemit_stream_LOCAL;
    Object Current_jemit_text_style_qm_LOCAL;
    Object Current_kb_file_progress_for_modules_qm_LOCAL;
    Object Current_kb_pathname_qm_LOCAL;
    Object Current_kb_save_LOCAL;
    Object Current_kb_serial_number_LOCAL;
    Object Current_kb_specific_property_list_property_name_LOCAL;
    Object Current_kind_of_change_LOCAL;
    Object Current_let_action_bindings_LOCAL;
    Object Current_lexing_patterns_LOCAL;
    Object Current_lexing_rule_number_LOCAL;
    Object Current_lexing_strings_LOCAL;
    Object Current_line_index_for_end_of_token_LOCAL;
    Object Current_linearized_kb_required_modules_LOCAL;
    Object Current_localization_domains_qm_LOCAL;
    Object Current_localization_purpose_qm_LOCAL;
    Object Current_logbook_qm_LOCAL;
    Object Current_logbook_serial_number_qm_LOCAL;
    Object Current_long_operation_notification_workspace_LOCAL;
    Object Current_lookup_data_LOCAL;
    Object Current_lr_states_LOCAL;
    Object Current_lu_matrix_LOCAL;
    Object Current_machine_ids_of_g2_ok_file_qm_LOCAL;
    Object Current_message_board_qm_LOCAL;
    Object Current_message_serial_number_LOCAL;
    Object Current_message_unix_time_qm_LOCAL;
    Object Current_minimal_grid_draw_has_seen_one_image_plane_p_LOCAL;
    Object Current_model_definition_qm_LOCAL;
    Object Current_model_queue_qm_LOCAL;
    Object Current_model_runtime_info_qm_LOCAL;
    Object Current_modularity_problems_LOCAL;
    Object Current_modularity_problems_fatal_qm_LOCAL;
    Object Current_module_being_saved_LOCAL;
    Object Current_module_data_LOCAL;
    Object Current_module_directory_binding_alist_LOCAL;
    Object Current_module_lisp_binary_filename_LOCAL;
    Object Current_module_pathname_override_binding_alist_LOCAL;
    Object Current_module_qm_LOCAL;
    Object Current_module_source_filename_LOCAL;
    Object Current_native_image_plane_LOCAL;
    Object Current_native_simple_dialog_handle_LOCAL;
    Object Current_native_window_qm_LOCAL;
    Object Current_network_interface_LOCAL;
    Object Current_new_table_LOCAL;
    Object Current_nonterminals_LOCAL;
    Object Current_painting_action_LOCAL;
    Object Current_pane_LOCAL;
    Object Current_parse_table_LOCAL;
    Object Current_parsing_context_character_LOCAL;
    Object Current_parsing_context_line_LOCAL;
    Object Current_parsing_context_qm_LOCAL;
    Object Current_parsing_context_text_LOCAL;
    Object Current_parsing_context_text_length_LOCAL;
    Object Current_parsing_contexts_LOCAL;
    Object Current_part_description_LOCAL;
    Object Current_plot_LOCAL;
    Object Current_plot_number_LOCAL;
    Object Current_post_mortem_ring_buffer_LOCAL;
    Object Current_post_mortem_ring_buffer_length_LOCAL;
    Object Current_process_handle_LOCAL;
    Object Current_productions_LOCAL;
    Object Current_profile_structure_qm_LOCAL;
    Object Current_projection_function_for_funcall_LOCAL;
    Object Current_read_icp_byte_position_LOCAL;
    Object Current_real_time_LOCAL;
    Object Current_receiving_resumable_object_LOCAL;
    Object Current_region_maximum_x_LOCAL;
    Object Current_region_maximum_y_LOCAL;
    Object Current_region_minimum_x_LOCAL;
    Object Current_region_minimum_y_LOCAL;
    Object Current_remote_procedure_identifier_LOCAL;
    Object Current_remote_search_representation_qm_LOCAL;
    Object Current_resumable_icp_read_task_LOCAL;
    Object Current_return_values_position_LOCAL;
    Object Current_ri_completion_notification_collection_qm_LOCAL;
    Object Current_row_LOCAL;
    Object Current_rule_local_name_reference_info_LOCAL;
    Object Current_saving_context_LOCAL;
    Object Current_saving_context_qm_LOCAL;
    Object Current_schedule_task_LOCAL;
    Object Current_score_of_best_match_for_eyes_LOCAL;
    Object Current_scratchpad_color_value_list_LOCAL;
    Object Current_scratchpad_raster_LOCAL;
    Object Current_scratchpad_raster_depth_LOCAL;
    Object Current_scratchpad_raster_height_LOCAL;
    Object Current_scratchpad_raster_list_LOCAL;
    Object Current_scratchpad_raster_tiled_p_LOCAL;
    Object Current_scratchpad_raster_type_LOCAL;
    Object Current_scratchpad_raster_width_LOCAL;
    Object Current_simulation_category_LOCAL;
    Object Current_simulation_runtime_structure_LOCAL;
    Object Current_slice_size_qm_LOCAL;
    Object Current_slot_value_of_user_slot_LOCAL;
    Object Current_source_line_LOCAL;
    Object Current_source_nupec_synchronization_LOCAL;
    Object Current_standard_icp_object_index_space_LOCAL;
    Object Current_start_state_LOCAL;
    Object Current_state_stack_LOCAL;
    Object Current_statistics_file_pathname_qm_LOCAL;
    Object Current_style_if_other_than_default_LOCAL;
    Object Current_subcategory_path_LOCAL;
    Object Current_subscribe_innermost_class_LOCAL;
    Object Current_subscribe_innermost_item_index_LOCAL;
    Object Current_system_being_loaded_LOCAL;
    Object Current_system_dummy_workstation_qm_LOCAL;
    Object Current_system_name_LOCAL;
    Object Current_system_rpc_icp_socket_qm_LOCAL;
    Object Current_system_version_LOCAL;
    Object Current_t2_dialog_sequence_number_LOCAL;
    Object Current_table_updates_task_qm_LOCAL;
    Object Current_target_nupec_synchronization_LOCAL;
    Object Current_task_to_run_propagate_all_workspace_changes_to_image_planes_LOCAL;
    Object Current_telewindows_workstation_LOCAL;
    Object Current_temporary_g2gl_values_LOCAL;
    Object Current_temporary_icp_object_index_space_LOCAL;
    Object Current_terminals_LOCAL;
    Object Current_text_box_format_LOCAL;
    Object Current_text_cell_plist_LOCAL;
    Object Current_text_focus_for_eyes_qm_LOCAL;
    Object Current_text_tokenization_state_LOCAL;
    Object Current_thing_changed_LOCAL;
    Object Current_thread_index_LOCAL;
    Object Current_token_stack_LOCAL;
    Object Current_tokenizer_LOCAL;
    Object Current_tracking_subcomponent_LOCAL;
    Object Current_tracking_x_in_window_LOCAL;
    Object Current_tracking_y_in_window_LOCAL;
    Object Current_transform_constituent_array_LOCAL;
    Object Current_transform_constituent_count_LOCAL;
    Object Current_trend_chart_LOCAL;
    Object Current_trend_chart_has_remote_representation_p_LOCAL;
    Object Current_twriting_output_type_LOCAL;
    Object Current_ui_client_session_LOCAL;
    Object Current_wide_string_LOCAL;
    Object Current_wide_string_list_LOCAL;
    Object Current_width_of_formatted_part_LOCAL;
    Object Current_window_LOCAL;
    Object Current_workspace_on_image_plane_qm_LOCAL;
    Object Current_workstation_LOCAL;
    Object Current_workstation_context_LOCAL;
    Object Current_workstation_detail_pane_LOCAL;
    Object Current_workstation_event_LOCAL;
    Object Current_workstation_native_window_qm_LOCAL;
    Object Current_workstation_window_LOCAL;
    Object Current_write_icp_byte_position_LOCAL;
    Object Current_x_for_eyes_qm_LOCAL;
    Object Current_x_max_for_stored_raster_qm_LOCAL;
    Object Current_x_offset_for_stored_raster_qm_LOCAL;
    Object Current_x_origin_of_drawing_LOCAL;
    Object Current_x_vector_LOCAL;
    Object Current_xml_structures_LOCAL;
    Object Current_y_for_eyes_qm_LOCAL;
    Object Current_y_max_for_stored_raster_qm_LOCAL;
    Object Current_y_offset_for_stored_raster_qm_LOCAL;
    Object Current_y_origin_of_drawing_LOCAL;
    Object Currently_active_event_handlers_via_object_configuration_LOCAL;
    Object Currently_automatically_resolving_class_name_conflicts_qm_LOCAL;
    Object Currently_exposed_workspaces_LOCAL;
    Object Currently_jump_out_of_drawing_image_plane_when_empty_rectangle_p_LOCAL;
    Object Currently_loading_modules_qm_LOCAL;
    Object Currently_posting_message_on_logbook_p_LOCAL;
    Object Currently_supressing_part_highlighting_LOCAL;
    Object Currently_tracking_subcategory_path_max_LOCAL;
    Object Currently_within_make_transient_instruction_p_LOCAL;
    Object Currently_working_on_drawing_p_LOCAL;
    Object Currently_working_on_drawing_workspace_LOCAL;
    Object Custom_dialog_cons_counter_LOCAL;
    Object Cvs_command_initial_timeout_LOCAL;
    Object Cvs_command_timed_out_p_LOCAL;
    Object Daily_countdown_LOCAL;
    Object Data_point_first_x_LOCAL;
    Object Data_point_first_y_LOCAL;
    Object Data_point_index_LOCAL;
    Object Data_point_indicator_LOCAL;
    Object Data_point_indicator_projection_function_LOCAL;
    Object Data_point_last_x_LOCAL;
    Object Data_point_last_y_LOCAL;
    Object Data_point_show_connecting_line_LOCAL;
    Object Data_point_show_indicator_LOCAL;
    Object Data_point_tuple_1_LOCAL;
    Object Data_point_tuple_2_LOCAL;
    Object Data_point_tuple_valid_qm_LOCAL;
    Object Data_point_value_LOCAL;
    Object Data_point_value_and_collection_time_interned_list_LOCAL;
    Object Data_point_value_interned_list_LOCAL;
    Object Data_point_x_LOCAL;
    Object Data_point_y_LOCAL;
    Object Data_series_LOCAL;
    Object Data_series_connect_first_and_last_point_LOCAL;
    Object Data_series_data_cache_1_qm_LOCAL;
    Object Data_series_data_cache_2_qm_LOCAL;
    Object Data_series_failed_to_compile_LOCAL;
    Object Data_series_generator_info_1_LOCAL;
    Object Data_series_generator_info_2_LOCAL;
    Object Data_series_illustration_kind_LOCAL;
    Object Data_series_index_LOCAL;
    Object Data_series_info_1_LOCAL;
    Object Data_series_info_2_LOCAL;
    Object Data_series_source_kind_LOCAL;
    Object Data_series_subparts_LOCAL;
    Object Data_server_count_LOCAL;
    Object Data_server_error_code_alist_LOCAL;
    Object Data_server_parameters_LOCAL;
    Object Data_server_pretty_name_alist_LOCAL;
    Object Date_format_count_LOCAL;
    Object Datum_type_LOCAL;
    Object Day_of_the_week_names_LOCAL;
    Object Deadman_switch_time_interval_LOCAL;
    Object Debug_1_LOCAL;
    Object Debug_10_LOCAL;
    Object Debug_11_LOCAL;
    Object Debug_12_LOCAL;
    Object Debug_2_LOCAL;
    Object Debug_3_LOCAL;
    Object Debug_4_LOCAL;
    Object Debug_5_LOCAL;
    Object Debug_6_LOCAL;
    Object Debug_7_LOCAL;
    Object Debug_8_LOCAL;
    Object Debug_9_LOCAL;
    Object Debug_out_of_synch_LOCAL;
    Object Debug_print_byte_code_pc_p_LOCAL;
    Object Debugging_consing_LOCAL;
    Object Debugging_name_index_LOCAL;
    Object Debugging_parameters_LOCAL;
    Object Debugging_reset_LOCAL;
    Object Decache_attribute_description_lists_of_interned_lists_function_LOCAL;
    Object Decache_occurred_since_last_update_qm_LOCAL;
    Object Default_accept_timeout_LOCAL;
    Object Default_axis_data_series_instance_LOCAL;
    Object Default_duration_for_data_point_LOCAL;
    Object Default_entity_line_drawing_description_template_LOCAL;
    Object Default_fin_length_LOCAL;
    Object Default_float_to_text_format_LOCAL;
    Object Default_format_structure_LOCAL;
    Object Default_g2_hangul_star_pathname_LOCAL;
    Object Default_g2_init_pathname_LOCAL;
    Object Default_g2_kanji_star_pathname_LOCAL;
    Object Default_g2_kb_pathname_LOCAL;
    Object Default_g2_minm_star_pathname_LOCAL;
    Object Default_g2_module_map_pathname_LOCAL;
    Object Default_g2_ok_pathname_LOCAL;
    Object Default_g2v11_ok_pathname_LOCAL;
    Object Default_g2v12_ok_pathname_LOCAL;
    Object Default_g2v51_ok_pathname_LOCAL;
    Object Default_g2v5_ok_pathname_LOCAL;
    Object Default_g2v6_ok_pathname_LOCAL;
    Object Default_g2v7_ok_pathname_LOCAL;
    Object Default_g2v83_ok_pathname_LOCAL;
    Object Default_g2v8_ok_pathname_LOCAL;
    Object Default_g2v9_ok_pathname_LOCAL;
    Object Default_graph_line_color_value_LOCAL;
    Object Default_icon_slot_group_LOCAL;
    Object Default_junction_class_description_LOCAL;
    Object Default_kb_pathname_qm_LOCAL;
    Object Default_language_LOCAL;
    Object Default_maximum_icon_bitmap_memory_LOCAL;
    Object Default_maximum_icon_bitmaps_LOCAL;
    Object Default_most_recent_bandwidth_per_timeslice_LOCAL;
    Object Default_size_of_spacial_index_LOCAL;
    Object Default_stub_length_LOCAL;
    Object Default_text_conversion_style_LOCAL;
    Object Default_tw_hangul_star_pathname_LOCAL;
    Object Default_tw_kanji_star_pathname_LOCAL;
    Object Default_tw_minm_star_pathname_LOCAL;
    Object Default_tw_ok_pathname_LOCAL;
    Object Default_twv11_ok_pathname_LOCAL;
    Object Default_twv12_ok_pathname_LOCAL;
    Object Default_twv5_ok_pathname_LOCAL;
    Object Default_twv6_ok_pathname_LOCAL;
    Object Default_twv7_ok_pathname_LOCAL;
    Object Default_twv8_ok_pathname_LOCAL;
    Object Default_twv9_ok_pathname_LOCAL;
    Object Defaults_namestring_for_directory_of_names_qm_LOCAL;
    Object Defer_consistency_analysis_qm_LOCAL;
    Object Defer_notifications_qm_LOCAL;
    Object Deferred_class_definitions_alist_LOCAL;
    Object Deferred_errors_for_class_export_qm_LOCAL;
    Object Deferred_update_count_LOCAL;
    Object Deferring_errors_for_class_export_p_LOCAL;
    Object Defined_evaluation_datum_types_LOCAL;
    Object Defined_evaluation_value_types_LOCAL;
    Object Definition_being_analyzed_for_savability_LOCAL;
    Object Definition_class_description_LOCAL;
    Object Definition_with_subclass_or_instance_in_kb_hierarchy_LOCAL;
    Object Definitions_for_saving_LOCAL;
    Object Definitions_in_module_LOCAL;
    Object Definitions_in_module_to_go_LOCAL;
    Object Definitions_not_required_LOCAL;
    Object Definitions_read_in_this_module_LOCAL;
    Object Definitions_that_have_been_visited_LOCAL;
    Object Defun_incremental_compile_time_registry_LOCAL;
    Object Defun_incremental_runtime_registry_LOCAL;
    Object Defvar_for_informational_tests_for_mhd_LOCAL;
    Object Delay_item_array_initializations_p_LOCAL;
    Object Delayed_item_array_initializations_LOCAL;
    Object Delete_as_item_referring_to_name_qm_LOCAL;
    Object Delete_compiled_kb_source_p_LOCAL;
    Object Delete_connections_without_leaving_stubs_qm_LOCAL;
    Object Delete_corresponding_object_qm_LOCAL;
    Object Delete_files_after_external_diff_p_LOCAL;
    Object Delete_old_elements_from_arrays_and_lists_LOCAL;
    Object Deleting_ui_client_interfaces_for_clear_kb_LOCAL;
    Object Denotation_error_list_LOCAL;
    Object Denotation_size_vector_LOCAL;
    Object Dependent_frame_class_description_LOCAL;
    Object Depth_of_post_mortem_checkpoint_reporting_LOCAL;
    Object Deregister_and_register_item_p_LOCAL;
    Object Deregister_but_do_not_remove_from_table_p_LOCAL;
    Object Deregister_corresponding_object_qm_LOCAL;
    Object Derived_icp_input_port_LOCAL;
    Object Derived_icp_output_port_LOCAL;
    Object Designation_marker_LOCAL;
    Object Designations_from_explicit_iteration_forms_LOCAL;
    Object Designations_in_rule_LOCAL;
    Object Desired_distance_between_fins_LOCAL;
    Object Desired_distance_between_fins_on_link_LOCAL;
    Object Desired_high_value_for_horizontal_axis_LOCAL;
    Object Desired_high_value_for_vertical_axis_LOCAL;
    Object Desired_low_value_for_horizontal_axis_LOCAL;
    Object Desired_low_value_for_vertical_axis_LOCAL;
    Object Desired_parent_of_native_window_qm_LOCAL;
    Object Destination_for_symbol_with_preserved_cells_LOCAL;
    Object Detail_pane_spot_count_LOCAL;
    Object Development_world_save_p_LOCAL;
    Object Dial_class_description_LOCAL;
    Object Dial_spot_count_LOCAL;
    Object Dialog_button_class_description_LOCAL;
    Object Dialog_component_count_LOCAL;
    Object Dialog_errors_structure_count_LOCAL;
    Object Dialog_state_count_LOCAL;
    Object Dialog_view_count_LOCAL;
    Object Dialogs_error_handling_LOCAL;
    Object Digital_clock_class_description_LOCAL;
    Object Digits_of_extremal_fixnum_as_string_LOCAL;
    Object Digits_of_largest_float_as_string_LOCAL;
    Object Digits_of_most_negative_fixnum_as_string_LOCAL;
    Object Digits_of_most_positive_fixnum_as_string_LOCAL;
    Object Digits_of_smallest_normalized_float_as_string_LOCAL;
    Object Directory_nil_LOCAL;
    Object Directory_of_built_in_menu_choices_LOCAL;
    Object Disable_parameter_strings_for_internal_proprietary_procedures_LOCAL;
    Object Disable_resumability_LOCAL;
    Object Disable_stack_error_LOCAL;
    Object Disable_subworkspace_connection_posts_LOCAL;
    Object Disable_tracing_and_breakpoints_warning_LOCAL;
    Object Disable_update_button_LOCAL;
    Object Disassemble_enabled_qm_LOCAL;
    Object Display_pane_count_LOCAL;
    Object Distance_to_snap_points_together_in_view_pad_LOCAL;
    Object Distribute_selection_command_operations_LOCAL;
    Object Do_backpatching_LOCAL;
    Object Do_circularity_check_walking_through_conses_p_LOCAL;
    Object Do_circularity_check_walking_through_simple_vectors_p_LOCAL;
    Object Do_g2_init_file_qm_LOCAL;
    Object Do_icp_flow_control_qm_LOCAL;
    Object Do_not_allow_user_interactions_during_kb_load_qm_LOCAL;
    Object Do_not_error_in_x11_create_pixmap_on_failed_allocation_LOCAL;
    Object Do_not_initialize_g2_array_elements_p_LOCAL;
    Object Do_not_initialize_specializations_LOCAL;
    Object Do_not_invoke_rules_for_user_icon_movement_qm_LOCAL;
    Object Do_not_load_modules_p_LOCAL;
    Object Do_not_note_permanent_changes_p_LOCAL;
    Object Do_not_notify_user_during_kb_load_qm_LOCAL;
    Object Do_not_reclaim_runs_while_inactive_entries_LOCAL;
    Object Do_not_restore_image_planes_qm_LOCAL;
    Object Do_not_show_conflicts_during_kb_load_qm_LOCAL;
    Object Do_not_stop_search_once_found_qm_LOCAL;
    Object Do_not_update_file_progress_display_qm_LOCAL;
    Object Do_not_update_frame_authors_qm_LOCAL;
    Object Do_not_update_selection_highlights_LOCAL;
    Object Do_not_update_simulated_value_qm_LOCAL;
    Object Doing_g2_init_file_p_LOCAL;
    Object Doing_g2_init_kb_p_LOCAL;
    Object Doing_long_operation_with_notification_qm_LOCAL;
    Object Doing_password_change_p_LOCAL;
    Object Dont_backward_chain_in_sim_eval_qm_LOCAL;
    Object Dont_cerror_for_slot_changes_while_on_window_qm_LOCAL;
    Object Dont_include_offset_for_end_position_qm_LOCAL;
    Object Dont_load_if_definitions_have_changed_p_LOCAL;
    Object Dont_proceed_to_next_variable_qm_LOCAL;
    Object Drag_handle_state_count_LOCAL;
    Object Dragging_cons_counter_LOCAL;
    Object Dragging_state_count_LOCAL;
    Object Drawing_is_locked_qm_LOCAL;
    Object Drawing_on_window_LOCAL;
    Object Drawing_parameters_LOCAL;
    Object Drawing_state_for_project_paper_LOCAL;
    Object Drawing_task_count_LOCAL;
    Object Drawing_to_printer_p_LOCAL;
    Object Dummy_evaluators_list_LOCAL;
    Object Dummy_place_for_chestnut_internals_LOCAL;
    Object Duplicate_local_names_already_reported_LOCAL;
    Object Duplicates_check_hash_LOCAL;
    Object Duration_cv_count_LOCAL;
    Object During_ffi_call_qm_LOCAL;
    Object Dynamic_dialog_count_LOCAL;
    Object Dynamic_menus_modification_tick_LOCAL;
    Object Dynamic_rule_display_hash_table_LOCAL;
    Object Dynamic_workspace_associated_structure_count_LOCAL;
    Object Echo_dialog_spec_p_LOCAL;
    Object Edit_box_change_count_LOCAL;
    Object Edit_box_class_description_LOCAL;
    Object Edit_box_spot_count_LOCAL;
    Object Edit_cache_count_LOCAL;
    Object Edit_menu_state_count_LOCAL;
    Object Edit_state_count_LOCAL;
    Object Edit_states_LOCAL;
    Object Edit_type_alias_mapping_LOCAL;
    Object Editing_context_LOCAL;
    Object Editing_new_table_LOCAL;
    Object Editor_background_color_override_qm_LOCAL;
    Object Editor_caption_text_override_qm_LOCAL;
    Object Editor_font_size_override_qm_LOCAL;
    Object Editor_frame_style_override_qm_LOCAL;
    Object Editor_initial_editor_height_override_qm_LOCAL;
    Object Editor_parameters_LOCAL;
    Object Editor_prompt_filter_qm_LOCAL;
    Object Editor_scroll_decision_override_qm_LOCAL;
    Object Editor_specific_natural_language_override_qm_LOCAL;
    Object Editor_text_color_override_qm_LOCAL;
    Object Editor_toolbar_user_callback_LOCAL;
    Object Editor_window_handle_LOCAL;
    Object Effectively_infinite_region_LOCAL;
    Object Element_of_foreign_linking_info_count_LOCAL;
    Object Elevator_of_scroll_bar_spot_count_LOCAL;
    Object Elevator_shaft_spot_count_LOCAL;
    Object Elevator_state_count_LOCAL;
    Object Email_abort_message_sent_p_LOCAL;
    Object Embedded_fuzzy_conditionals_list_LOCAL;
    Object Emit_postscript_line_length_LOCAL;
    Object Enable_click_to_edit_kludge_LOCAL;
    Object Enable_loading_compiled_kbs_p_LOCAL;
    Object Enable_native_fonts_qm_LOCAL;
    Object Enable_running_compiled_code_p_LOCAL;
    Object Enable_saving_compiled_kbs_p_LOCAL;
    Object Enclosing_form_will_wrap_LOCAL;
    Object Ensure_expanded_instruction_macros_has_run_p_LOCAL;
    Object Entire_focus_menu_spot_count_LOCAL;
    Object Entire_g2_window_spot_count_LOCAL;
    Object Entire_menu_spot_count_LOCAL;
    Object Entities_or_triples_found_in_search_LOCAL;
    Object Entities_to_be_excluded_qm_LOCAL;
    Object Entity_class_description_LOCAL;
    Object Entity_cons_counter_LOCAL;
    Object Entity_height_in_ws_LOCAL;
    Object Entity_width_in_ws_LOCAL;
    Object Eq_hash_table_count_LOCAL;
    Object Erase_dateline_LOCAL;
    Object Erase_instead_qm_LOCAL;
    Object Error_code_count_LOCAL;
    Object Error_of_ok_file_reader_qm_LOCAL;
    Object Error_within_error_p_LOCAL;
    Object Eval_cons_counter_LOCAL;
    Object Evaluating_simulator_procedure_qm_LOCAL;
    Object Evaluation_value_indentation_depth_LOCAL;
    Object Evaluation_value_writing_target_length_qm_LOCAL;
    Object Evaluator_slot_info_count_LOCAL;
    Object Event_detector_count_LOCAL;
    Object Event_handler_args_LOCAL;
    Object Exact_class_names_for_menu_restrictions_LOCAL;
    Object Exclude_secondary_attributes_LOCAL;
    Object Executing_change_item_color_instruction_p_LOCAL;
    Object Execution_time_stack_LOCAL;
    Object Existence_classes_already_checked_LOCAL;
    Object Expanded_bindings_forms_LOCAL;
    Object Expanded_check_timeout_form_LOCAL;
    Object Expanded_default_clause_form_LOCAL;
    Object Expanded_exit_form_LOCAL;
    Object Expanded_exit_stack_eval_major_form_LOCAL;
    Object Expanded_exit_stack_eval_minor_form_LOCAL;
    Object Expanded_return_values_form_LOCAL;
    Object Explanation_table_class_description_LOCAL;
    Object Explanation_variables_LOCAL;
    Object Explicit_branch_destination_LOCAL;
    Object Explicit_dragger_x_in_window_qm_LOCAL;
    Object Explicit_dragger_y_in_window_qm_LOCAL;
    Object Expression_bound_local_names_LOCAL;
    Object Expression_cell_index_LOCAL;
    Object Expression_for_compilation_count_LOCAL;
    Object Expression_list_indicator_LOCAL;
    Object Expression_source_text_LOCAL;
    Object Expressions_to_display_slot_description_LOCAL;
    Object External_class_info_count_LOCAL;
    Object External_diff_options_qm_LOCAL;
    Object External_diff_program_qm_LOCAL;
    Object External_method_info_count_LOCAL;
    Object External_set_pointers_count_LOCAL;
    Object External_simulation_definition_class_description_LOCAL;
    Object External_simulation_object_count_LOCAL;
    Object Externaldefinitions_fixups_LOCAL;
    Object Extra_time_for_drawing_LOCAL;
    Object Extreme_bottom_edge_so_far_LOCAL;
    Object Extreme_left_edge_so_far_LOCAL;
    Object Extreme_right_edge_so_far_LOCAL;
    Object Extreme_top_edge_so_far_LOCAL;
    Object Extremum_cache_count_LOCAL;
    Object Failure_marker_LOCAL;
    Object Fake_attribute_LOCAL;
    Object Fasl_extension_LOCAL;
    Object Fatal_focus_error_info_for_all_compilations_LOCAL;
    Object Fatal_focus_error_info_qm_LOCAL;
    Object Feature_blt_LOCAL;
    Object Ff_connect_finalized_LOCAL;
    Object File_format_version_of_g2_ok_file_qm_LOCAL;
    Object File_punctuation_mark_grammar_rules_LOCAL;
    Object File_system_directory_search_cache_LOCAL;
    Object File_system_directory_search_cache_active_p_LOCAL;
    Object File_system_directory_search_cache_wildcard_string_LOCAL;
    Object File_system_for_interception_qm_LOCAL;
    Object File_system_slot_description_LOCAL;
    Object File_template_instance_counter_LOCAL;
    Object Filename_of_module_being_loaded_qm_LOCAL;
    Object Filename_parser_information_count_LOCAL;
    Object Filename_special_character_registry_LOCAL;
    Object Fill_pointer_for_current_gensym_string_LOCAL;
    Object Fill_pointer_for_current_wide_string_LOCAL;
    Object Fill_pointer_for_match_pattern_for_inspect_binding_vector_LOCAL;
    Object Filter_cons_counter_LOCAL;
    Object Finding_object_near_mouse_LOCAL;
    Object Finish_current_kb_save_failure_LOCAL;
    Object Finished_storing_in_plot_data_1_qm_LOCAL;
    Object First_kb_in_group_read_in_yet_qm_LOCAL;
    Object First_string_in_pool_group_LOCAL;
    Object First_subexpression_node_for_reclaiming_qm_LOCAL;
    Object Fixnum_maximum_y_value_LOCAL;
    Object Fixnum_minimum_y_value_LOCAL;
    Object Fixnum_time_at_start_of_current_long_notification_LOCAL;
    Object Fixnum_time_interval_for_one_second_LOCAL;
    Object Fixnum_time_of_last_g2_tick_LOCAL;
    Object Fixnum_time_of_last_real_time_tick_LOCAL;
    Object Fixnum_time_of_last_xsync_LOCAL;
    Object Fixnum_time_units_of_sleep_this_clock_tick_LOCAL;
    Object Fixnum_time_until_g2_time_tick_LOCAL;
    Object Fixup_authors_to_skip_LOCAL;
    Object Flattened_menu_maximum_remaining_elements_LOCAL;
    Object Flattened_menu_reverse_LOCAL;
    Object Float_array_class_description_LOCAL;
    Object Float_array_cons_counter_LOCAL;
    Object Float_contagion_stack_operators_LOCAL;
    Object Float_errors_are_possible_LOCAL;
    Object Float_list_class_description_LOCAL;
    Object Float_parameter_class_description_LOCAL;
    Object Float_variable_class_description_LOCAL;
    Object Floating_telewindows_limit_LOCAL;
    Object Floating_tw2_limit_LOCAL;
    Object Flush_graphics_immediately_qm_LOCAL;
    Object Focal_entity_for_simulation_formula_LOCAL;
    Object Focus_for_graph_detailed_procedures_LOCAL;
    Object Focus_local_name_for_rule_compilation_qm_LOCAL;
    Object Focus_local_names_for_focus_role_name_LOCAL;
    Object Focus_name_for_rule_or_formula_compilation_LOCAL;
    Object Focus_range_LOCAL;
    Object Focus_too_narrow_qm_LOCAL;
    Object Font_feature_list_LOCAL;
    Object Font_map_for_line_of_text_of_graphic_element_LOCAL;
    Object Fonts_LOCAL;
    Object Fonts_cons_counter_LOCAL;
    Object Fonts_needing_corresponding_kanji_font_LOCAL;
    Object Fonts_used_in_print_job_LOCAL;
    Object For_image_plane_LOCAL;
    Object For_structure_count_LOCAL;
    Object For_workstation_LOCAL;
    Object For_workstation_context_LOCAL;
    Object For_workstation_polling_LOCAL;
    Object Force_change_to_minimum_size_p_LOCAL;
    Object Force_clock_tick_LOCAL;
    Object Foreground_color_difference_of_graphic_element_LOCAL;
    Object Foreground_color_difference_or_differences_of_graphic_element_LOCAL;
    Object Foreground_color_value_of_graphic_element_LOCAL;
    Object Foreign_function_call_info_count_LOCAL;
    Object Foreign_function_declaration_class_description_LOCAL;
    Object Foreign_function_entry_count_LOCAL;
    Object Foreign_function_image_info_count_LOCAL;
    Object Foreign_function_registry_LOCAL;
    Object Foreign_image_connection_checkup_interval_in_ms_LOCAL;
    Object Foreign_image_connection_mode_LOCAL;
    Object Foreign_struct_info_count_LOCAL;
    Object Foremost_attribute_for_multiplexed_chaining_qm_LOCAL;
    Object Forgive_long_procedure_instruction_qm_LOCAL;
    Object Format_frame_class_description_LOCAL;
    Object Formatted_part_LOCAL;
    Object Formatted_part_highlight_flag_LOCAL;
    Object Formatted_part_true_line_color_LOCAL;
    Object Formula_invocation_count_LOCAL;
    Object Forward_chaining_link_class_description_LOCAL;
    Object Forward_compiled_antecedent_LOCAL;
    Object Forward_compiled_consequent_qm_LOCAL;
    Object Forward_referenced_format_frames_LOCAL;
    Object Frame_being_made_LOCAL;
    Object Frame_being_read_qm_LOCAL;
    Object Frame_component_spot_count_LOCAL;
    Object Frame_cons_counter_LOCAL;
    Object Frame_description_reference_count_LOCAL;
    Object Frame_display_cons_counter_LOCAL;
    Object Frame_display_count_LOCAL;
    Object Frame_for_write_frame_for_kb_LOCAL;
    Object Frame_note_count_LOCAL;
    Object Frame_note_index_LOCAL;
    Object Frame_note_index_has_been_written_qm_LOCAL;
    Object Frame_note_index_skip_LOCAL;
    Object Frame_projecting_LOCAL;
    Object Frame_serial_cons_counter_LOCAL;
    Object Frame_serial_number_map_LOCAL;
    Object Frame_serial_number_of_current_message_board_LOCAL;
    Object Frame_transform_count_LOCAL;
    Object Frame_transform_of_frame_LOCAL;
    Object Frame_vector_count_LOCAL;
    Object Frame_vector_memory_used_LOCAL;
    Object Frame_vector_pool_vector_LOCAL;
    Object Frames_for_rendezvous_in_aggregate_values_qm_LOCAL;
    Object Frames_with_substitute_classes_LOCAL;
    Object Free_floater_allowed_qm_LOCAL;
    Object Free_global_stacks_LOCAL;
    Object Free_malloced_arrays_LOCAL;
    Object Fsm_state_count_LOCAL;
    Object Funcalled_evaluator_array_LOCAL;
    Object Funcalled_evaluator_dispatch_type_LOCAL;
    Object Funcalled_evaluator_functions_LOCAL;
    Object Funcalled_instruction_functions_LOCAL;
    Object Funcalled_instructions_LOCAL;
    Object Function_definition_class_description_LOCAL;
    Object Function_info_count_LOCAL;
    Object Function_invocation_count_LOCAL;
    Object Function_templates_LOCAL;
    Object Future_task_queue_holder_count_LOCAL;
    Object Future_task_to_run_propagate_all_workspace_changes_to_image_planes_LOCAL;
    Object G2_array_class_description_LOCAL;
    Object G2_cell_array_cell_class_description_LOCAL;
    Object G2_cell_array_class_description_LOCAL;
    Object G2_comment_tokenizer_LOCAL;
    Object G2_datatypes_xml_namespace_prefix_LOCAL;
    Object G2_designation_cell_class_description_LOCAL;
    Object G2_element_types_that_can_contain_datum_LOCAL;
    Object G2_expression_cell_class_description_LOCAL;
    Object G2_has_been_started_qm_LOCAL;
    Object G2_has_v5_mode_windows_p_LOCAL;
    Object G2_identification_for_write_locks_LOCAL;
    Object G2_list_class_description_LOCAL;
    Object G2_list_cons_counter_LOCAL;
    Object G2_list_element_count_LOCAL;
    Object G2_load_kb_tokenizer_LOCAL;
    Object G2_login_class_description_LOCAL;
    Object G2_login_state_count_LOCAL;
    Object G2_machine_type_LOCAL;
    Object G2_meter_names_and_forms_LOCAL;
    Object G2_meter_task_count_LOCAL;
    Object G2_module_file_name_map_LOCAL;
    Object G2_module_search_path_LOCAL;
    Object G2_operating_system_LOCAL;
    Object G2_query_cell_class_description_LOCAL;
    Object G2_save_module_flag_LOCAL;
    Object G2_save_module_list_LOCAL;
    Object G2_simple_tokenizer_LOCAL;
    Object G2_standard_tokenizer_LOCAL;
    Object G2_stream_all_open_streams_LOCAL;
    Object G2_stream_device_buffer_LOCAL;
    Object G2_stream_directory_buffer_LOCAL;
    Object G2_stream_error_string_table_LOCAL;
    Object G2_stream_of_ok_file_reader_LOCAL;
    Object G2_stream_status_slot_description_LOCAL;
    Object G2_stream_structure_count_LOCAL;
    Object G2_symbol_tokenizer_LOCAL;
    Object G2_time_at_start_LOCAL;
    Object G2_time_at_start_as_text_string_LOCAL;
    Object G2_time_to_tick_p_base_LOCAL;
    Object G2_to_g2_uses_references_p_LOCAL;
    Object G2_token_count_LOCAL;
    Object G2_tokenizer_tokenizer_LOCAL;
    Object G2_window_class_description_LOCAL;
    Object G2_window_for_save_via_system_procedure_qm_LOCAL;
    Object G2binary_file_name_LOCAL;
    Object G2binary_file_position_LOCAL;
    Object G2binary_file_stream_LOCAL;
    Object G2binary_file_symbol_index_space_LOCAL;
    Object G2binary_file_symbol_list_LOCAL;
    Object G2ds_cons_counter_LOCAL;
    Object G2ds_data_value_write_truth_value_as_integer_p_LOCAL;
    Object G2ds_interface_count_LOCAL;
    Object G2ds_interface_status_changed_p_LOCAL;
    Object G2ds_interface_transition_table_LOCAL;
    Object G2ds_server_connection_count_LOCAL;
    Object G2ds_server_connections_LOCAL;
    Object G2ds_variable_count_LOCAL;
    Object G2ds_variable_list_LOCAL;
    Object G2gl_activity_compilation_count_LOCAL;
    Object G2gl_activity_implementations_alist_LOCAL;
    Object G2gl_activity_options_count_LOCAL;
    Object G2gl_alarm_event_handler_LOCAL;
    Object G2gl_alarm_event_handler_activity_compilation_count_LOCAL;
    Object G2gl_arg_variable_LOCAL;
    Object G2gl_assign_LOCAL;
    Object G2gl_assign_activity_compilation_count_LOCAL;
    Object G2gl_attribute_display_compilation_count_LOCAL;
    Object G2gl_body_being_laid_out_LOCAL;
    Object G2gl_body_compilation_count_LOCAL;
    Object G2gl_break_LOCAL;
    Object G2gl_break_activity_compilation_count_LOCAL;
    Object G2gl_call_LOCAL;
    Object G2gl_call_activity_compilation_count_LOCAL;
    Object G2gl_call_invocation_count_LOCAL;
    Object G2gl_compensate_LOCAL;
    Object G2gl_compensate_activity_compilation_count_LOCAL;
    Object G2gl_compensation_handler_LOCAL;
    Object G2gl_compensation_handler_activity_compilation_count_LOCAL;
    Object G2gl_compilation_version_count_LOCAL;
    Object G2gl_correlation_variable_LOCAL;
    Object G2gl_do_LOCAL;
    Object G2gl_do_activity_compilation_count_LOCAL;
    Object G2gl_empty_LOCAL;
    Object G2gl_empty_activity_compilation_count_LOCAL;
    Object G2gl_eval_error_LOCAL;
    Object G2gl_execution_fault_count_LOCAL;
    Object G2gl_execution_frame_count_LOCAL;
    Object G2gl_execution_thread_count_LOCAL;
    Object G2gl_exit_LOCAL;
    Object G2gl_exit_activity_compilation_count_LOCAL;
    Object G2gl_expression_compilation_error_LOCAL;
    Object G2gl_expression_language_symbol_LOCAL;
    Object G2gl_failed_activity_name_LOCAL;
    Object G2gl_false_LOCAL;
    Object G2gl_fault_handler_LOCAL;
    Object G2gl_fault_handler_activity_compilation_count_LOCAL;
    Object G2gl_flow_discriminator_LOCAL;
    Object G2gl_flow_discriminator_activity_compilation_count_LOCAL;
    Object G2gl_flow_gate_LOCAL;
    Object G2gl_flow_gate_activity_compilation_count_LOCAL;
    Object G2gl_flow_signal_LOCAL;
    Object G2gl_flow_signal_activity_compilation_count_LOCAL;
    Object G2gl_flow_split_LOCAL;
    Object G2gl_flow_split_activity_compilation_count_LOCAL;
    Object G2gl_flow_sync_LOCAL;
    Object G2gl_flow_sync_activity_compilation_count_LOCAL;
    Object G2gl_flow_terminator_LOCAL;
    Object G2gl_flow_terminator_activity_compilation_count_LOCAL;
    Object G2gl_import_added_start_activity_p_LOCAL;
    Object G2gl_import_errors_LOCAL;
    Object G2gl_import_flow_link_p_list_LOCAL;
    Object G2gl_invoke_LOCAL;
    Object G2gl_invoke_activity_compilation_count_LOCAL;
    Object G2gl_link_connection_arrows_LOCAL;
    Object G2gl_link_connection_line_pattern_LOCAL;
    Object G2gl_local_variable_LOCAL;
    Object G2gl_message_event_handler_LOCAL;
    Object G2gl_message_event_handler_activity_compilation_count_LOCAL;
    Object G2gl_message_transmission_count_LOCAL;
    Object G2gl_n_out_of_m_flow_join_LOCAL;
    Object G2gl_n_out_of_m_flow_join_activity_compilation_count_LOCAL;
    Object G2gl_object_icon_descriptions_info_LOCAL;
    Object G2gl_object_icon_substitutions_may_be_in_use_p_LOCAL;
    Object G2gl_operators_LOCAL;
    Object G2gl_parameters_LOCAL;
    Object G2gl_partner_link_variable_LOCAL;
    Object G2gl_pick_LOCAL;
    Object G2gl_pick_activity_compilation_count_LOCAL;
    Object G2gl_pick_join_LOCAL;
    Object G2gl_pick_join_activity_compilation_count_LOCAL;
    Object G2gl_process_invocation_thread_count_LOCAL;
    Object G2gl_query_language_symbol_LOCAL;
    Object G2gl_receive_LOCAL;
    Object G2gl_receive_activity_compilation_count_LOCAL;
    Object G2gl_reply_LOCAL;
    Object G2gl_reply_activity_compilation_count_LOCAL;
    Object G2gl_return_LOCAL;
    Object G2gl_return_activity_compilation_count_LOCAL;
    Object G2gl_scope_LOCAL;
    Object G2gl_scope_activity_compilation_count_LOCAL;
    Object G2gl_service_port_count_LOCAL;
    Object G2gl_standard_connection_arrows_LOCAL;
    Object G2gl_standard_connection_line_pattern_LOCAL;
    Object G2gl_standard_service_switch_LOCAL;
    Object G2gl_switch_fork_LOCAL;
    Object G2gl_switch_fork_activity_compilation_count_LOCAL;
    Object G2gl_switch_join_LOCAL;
    Object G2gl_switch_join_activity_compilation_count_LOCAL;
    Object G2gl_text_box_compilation_count_LOCAL;
    Object G2gl_throw_LOCAL;
    Object G2gl_throw_activity_compilation_count_LOCAL;
    Object G2gl_true_LOCAL;
    Object G2gl_variable_LOCAL;
    Object G2gl_wait_LOCAL;
    Object G2gl_wait_activity_compilation_count_LOCAL;
    Object G2gl_while_LOCAL;
    Object G2gl_while_activity_compilation_count_LOCAL;
    Object G2gl_xml_namespace_LOCAL;
    Object G2gl_xml_namespace_prefix_LOCAL;
    Object G2passwdexe_LOCAL;
    Object G2passwdexe_is_executable_p_LOCAL;
    Object Gathering_normally_editable_slots_for_search_qm_LOCAL;
    Object Gb_2312_count_LOCAL;
    Object Generate_source_annotation_info_LOCAL;
    Object Generated_var_spots_for_base_code_body_return_LOCAL;
    Object Generic_action_button_class_description_LOCAL;
    Object Generic_formula_class_description_LOCAL;
    Object Generic_listener_initialized_qm_LOCAL;
    Object Generic_rule_instance_display_hash_table_LOCAL;
    Object Generic_simulation_formula_class_description_LOCAL;
    Object Generic_simulation_formulas_used_p_LOCAL;
    Object Gensym_base_time_as_managed_float_LOCAL;
    Object Gensym_char_or_code_for_bullet_LOCAL;
    Object Gensym_char_or_code_for_capital_ligature_oe_LOCAL;
    Object Gensym_char_or_code_for_linebreak_LOCAL;
    Object Gensym_char_or_code_for_paragraph_break_LOCAL;
    Object Gensym_char_or_code_for_small_letter_f_with_hook_LOCAL;
    Object Gensym_char_or_code_for_small_ligature_oe_LOCAL;
    Object Gensym_char_or_code_for_trade_mark_sign_LOCAL;
    Object Gensym_code_for_bullet_LOCAL;
    Object Gensym_code_for_capital_ligature_oe_LOCAL;
    Object Gensym_code_for_linebreak_LOCAL;
    Object Gensym_code_for_paragraph_break_LOCAL;
    Object Gensym_code_for_small_letter_f_with_hook_LOCAL;
    Object Gensym_code_for_small_ligature_oe_LOCAL;
    Object Gensym_code_for_trade_mark_sign_LOCAL;
    Object Gensym_cons_counter_LOCAL;
    Object Gensym_default_pathname_defaults_LOCAL;
    Object Gensym_environment_variable_buffer_LOCAL;
    Object Gensym_error_argument_list_LOCAL;
    Object Gensym_error_format_string_LOCAL;
    Object Gensym_error_sure_of_format_info_p_LOCAL;
    Object Gensym_esc_for_bullet_qm_LOCAL;
    Object Gensym_esc_for_capital_ligature_oe_qm_LOCAL;
    Object Gensym_esc_for_linebreak_qm_LOCAL;
    Object Gensym_esc_for_paragraph_break_qm_LOCAL;
    Object Gensym_esc_for_small_letter_f_with_hook_qm_LOCAL;
    Object Gensym_esc_for_small_ligature_oe_qm_LOCAL;
    Object Gensym_esc_for_trade_mark_sign_qm_LOCAL;
    Object Gensym_file_error_occurred_p_LOCAL;
    Object Gensym_grammar_count_LOCAL;
    Object Gensym_logo_style_LOCAL;
    Object Gensym_pathname_count_LOCAL;
    Object Gensym_string_stream_count_LOCAL;
    Object Gensym_string_text_sequence_count_LOCAL;
    Object Gensym_time_LOCAL;
    Object Gensym_time_array_LOCAL;
    Object Gensym_time_at_start_LOCAL;
    Object Gensym_window_count_LOCAL;
    Object Gensym_window_for_printing_LOCAL;
    Object Geometric_change_to_connection_is_temporary_p_LOCAL;
    Object Geometry_count_LOCAL;
    Object Gesture_function_count_LOCAL;
    Object Gesture_local_count_LOCAL;
    Object Gesture_source_recording_p_LOCAL;
    Object Gesture_source_stack_LOCAL;
    Object Gesture_thread_count_LOCAL;
    Object Gesture_unbound_value_LOCAL;
    Object Get_focal_entity_for_simulation_formula_qm_LOCAL;
    Object Get_object_on_kb_workspace_for_item_LOCAL;
    Object Gfi_cons_counter_LOCAL;
    Object Gfi_list_of_converters_LOCAL;
    Object Gfi_queue_item_count_LOCAL;
    Object Global_desired_thrashing_setpoint_LOCAL;
    Object Global_domain_LOCAL;
    Object Global_draw_diagonally_qm_LOCAL;
    Object Global_keyboard_command_choices_LOCAL;
    Object Global_list_of_all_data_servers_LOCAL;
    Object Global_nms_menu_choiced_item_id_LOCAL;
    Object Global_nmsci_id_for_attributes_pane_LOCAL;
    Object Global_nmsci_id_for_hidden_attributes_pane_LOCAL;
    Object Global_output_stream_for_expand_syntax_template_LOCAL;
    Object Global_profiling_structure_count_LOCAL;
    Object Global_stack_LOCAL;
    Object Global_table_of_attributes_pane_LOCAL;
    Object Global_table_of_attributes_pane_pointer_LOCAL;
    Object Global_table_of_hidden_attributes_pane_LOCAL;
    Object Global_table_of_hidden_attributes_pane_pointer_LOCAL;
    Object Global_temp_1_LOCAL;
    Object Global_temp_2_LOCAL;
    Object Global_temp_3_LOCAL;
    Object Goto_tag_entry_count_LOCAL;
    Object Goto_tags_in_compilation_LOCAL;
    Object Grammar_categories_getting_choose_existing_class_feature_LOCAL;
    Object Grammar_categories_getting_yes_no_feature_LOCAL;
    Object Grammar_cons_counter_LOCAL;
    Object Grammar_rules_to_add_for_nupec_after_authorization_LOCAL;
    Object Graph_allocation_factor_LOCAL;
    Object Graph_background_color_value_LOCAL;
    Object Graph_class_description_LOCAL;
    Object Graph_cons_counter_LOCAL;
    Object Graph_display_changed_during_update_qm_LOCAL;
    Object Graph_display_count_LOCAL;
    Object Graph_expression_uses_local_name_qm_LOCAL;
    Object Graph_grid_class_description_LOCAL;
    Object Graph_grid_for_data_LOCAL;
    Object Graph_layout_cons_counter_LOCAL;
    Object Graph_month_strings_LOCAL;
    Object Graph_node_count_LOCAL;
    Object Graph_nodes_needing_children_connections_LOCAL;
    Object Graph_nodes_to_add_as_subblocks_LOCAL;
    Object Graph_or_icon_rendering_of_graphic_element_LOCAL;
    Object Graph_rendering_count_LOCAL;
    Object Graph_table_spot_count_LOCAL;
    Object Graphed_block_groups_to_move_LOCAL;
    Object Graphic_character_set_count_LOCAL;
    Object Graphic_element_projection_LOCAL;
    Object Graphics_cons_counter_LOCAL;
    Object Grid_LOCAL;
    Object Grid_color_LOCAL;
    Object Grid_height_LOCAL;
    Object Grid_painting_LOCAL;
    Object Grid_pane_count_LOCAL;
    Object Grid_view_cell_count_LOCAL;
    Object Grid_visible_LOCAL;
    Object Grid_width_LOCAL;
    Object Group_index_structure_count_LOCAL;
    Object Gsi_application_name_LOCAL;
    Object Gsi_array_wrapper_count_LOCAL;
    Object Gsi_attribute_count_LOCAL;
    Object Gsi_connection_checkup_interval_in_ms_LOCAL;
    Object Gsi_cons_counter_LOCAL;
    Object Gsi_context_to_socket_map_LOCAL;
    Object Gsi_extension_data_count_LOCAL;
    Object Gsi_history_count_LOCAL;
    Object Gsi_icp_interface_count_LOCAL;
    Object Gsi_instance_count_LOCAL;
    Object Gsi_instance_extension_count_LOCAL;
    Object Gsi_interface_status_changed_p_LOCAL;
    Object Gsi_interfaces_to_process_head_LOCAL;
    Object Gsi_interfaces_to_process_tail_LOCAL;
    Object Gsi_local_function_count_LOCAL;
    Object Gsi_local_home_LOCAL;
    Object Gsi_magic_number_LOCAL;
    Object Gsi_maximum_contexts_exceeded_LOCAL;
    Object Gsi_maximum_idle_interval_LOCAL;
    Object Gsi_maximum_number_of_contexts_LOCAL;
    Object Gsi_protect_inner_calls_p_LOCAL;
    Object Gsi_reclaim_list_level_LOCAL;
    Object Gsi_reclaim_list_qm_LOCAL;
    Object Gsi_remote_procedure_count_LOCAL;
    Object Gsi_remote_value_conses_logical_p_LOCAL;
    Object Gsi_remote_value_creates_instance_p_LOCAL;
    Object Gsi_throw_to_run_loop_may_be_harmful_p_LOCAL;
    Object Gsi_transfer_wrapper_count_LOCAL;
    Object Gsi_vector_length_LOCAL;
    Object Halt_info_count_LOCAL;
    Object Han_interpretation_mode_LOCAL;
    Object Handle_to_socket_mapping_LOCAL;
    Object Handle_ui_client_interface_messages_immediately_p_LOCAL;
    Object Handling_solitary_i_am_alive_qm_LOCAL;
    Object Handy_float_1_LOCAL;
    Object Height_for_change_size_qm_LOCAL;
    Object Hfep_action_LOCAL;
    Object Hfep_capability_qm_LOCAL;
    Object Hfep_cho_ksc2c_LOCAL;
    Object Hfep_hanc_type_count_LOCAL;
    Object Hfep_jong_ksc2c_LOCAL;
    Object Hfep_jung_ksc2c_LOCAL;
    Object Hfep_ksc2cs_LOCAL;
    Object Hfep_state_LOCAL;
    Object High_bound_system_variable_for_get_current_bounds_for_plot_LOCAL;
    Object High_bound_system_variable_for_get_current_min_and_max_for_plot_from_history_LOCAL;
    Object High_value_for_horizontal_grid_lines_LOCAL;
    Object High_value_for_vertical_grid_lines_LOCAL;
    Object Highest_foreign_image_index_LOCAL;
    Object Highest_icp_socket_session_id_LOCAL;
    Object Highest_inspect_session_id_LOCAL;
    Object Highest_parsing_context_handle_LOCAL;
    Object Highest_remote_spawn_index_LOCAL;
    Object Highest_state_index_LOCAL;
    Object History_cons_counter_LOCAL;
    Object History_ring_buffer_count_LOCAL;
    Object History_time_per_pixel_LOCAL;
    Object History_time_to_evaluate_display_expression_with_LOCAL;
    Object Home_name_separator_LOCAL;
    Object Horizontal_grid_line_color_qm_LOCAL;
    Object Horizontal_grid_line_spacing_LOCAL;
    Object Horizontal_grid_line_width_LOCAL;
    Object Hot_spot_state_count_LOCAL;
    Object Hour_of_last_message_LOCAL;
    Object Hourly_countdown_LOCAL;
    Object Html_view_count_LOCAL;
    Object I_am_alive_info_count_LOCAL;
    Object I_am_alive_send_time_interval_LOCAL;
    Object I_am_alive_send_time_interval_in_seconds_LOCAL;
    Object I_am_alive_send_time_interval_in_seconds_as_float_LOCAL;
    Object Icmp_socket_count_LOCAL;
    Object Icon_cell_class_description_LOCAL;
    Object Icon_description_count_LOCAL;
    Object Icon_editor_button_count_LOCAL;
    Object Icon_editor_cons_counter_LOCAL;
    Object Icon_editor_count_LOCAL;
    Object Icon_editor_engine_count_LOCAL;
    Object Icon_editor_layers_pad_count_LOCAL;
    Object Icon_editor_table_count_LOCAL;
    Object Icon_editor_table_info_frame_class_description_LOCAL;
    Object Icon_editor_translator_count_LOCAL;
    Object Icon_editor_view_pad_count_LOCAL;
    Object Icon_editor_workspace_class_description_LOCAL;
    Object Icon_list_notes_LOCAL;
    Object Icon_offset_clip_bottom_LOCAL;
    Object Icon_offset_clip_left_LOCAL;
    Object Icon_offset_clip_right_LOCAL;
    Object Icon_offset_clip_top_LOCAL;
    Object Icon_offset_left_LOCAL;
    Object Icon_offset_top_LOCAL;
    Object Icon_rendering_count_LOCAL;
    Object Icon_renderings_being_bulk_decached_LOCAL;
    Object Icon_slot_group_count_LOCAL;
    Object Icp_bits_current_bits_LOCAL;
    Object Icp_bits_current_value_LOCAL;
    Object Icp_buffer_count_LOCAL;
    Object Icp_buffer_of_start_of_message_series_qm_LOCAL;
    Object Icp_buffer_ref_count_cons_counter_LOCAL;
    Object Icp_buffers_for_message_group_LOCAL;
    Object Icp_byte_position_of_start_of_message_series_qm_LOCAL;
    Object Icp_callback_cons_counter_LOCAL;
    Object Icp_cons_counter_LOCAL;
    Object Icp_error_suspend_p_LOCAL;
    Object Icp_message_handler_array_LOCAL;
    Object Icp_message_handler_name_array_LOCAL;
    Object Icp_message_trace_stream_qm_LOCAL;
    Object Icp_output_ports_to_flush_LOCAL;
    Object Icp_player_message_handler_array_LOCAL;
    Object Icp_port_count_LOCAL;
    Object Icp_port_for_reclaim_LOCAL;
    Object Icp_printing_message_handler_array_LOCAL;
    Object Icp_priority_categories_for_gsi_LOCAL;
    Object Icp_protocol_version_LOCAL;
    Object Icp_read_task_count_LOCAL;
    Object Icp_read_trace_cutoff_level_qm_LOCAL;
    Object Icp_socket_connect_negotiation_timeout_default_LOCAL;
    Object Icp_socket_count_LOCAL;
    Object Icp_socket_for_handle_icp_messages_LOCAL;
    Object Icp_socket_for_reclaim_qm_LOCAL;
    Object Icp_socket_index_LOCAL;
    Object Icp_socket_transacting_message_group_LOCAL;
    Object Icp_sockets_now_initializing_g2ds_LOCAL;
    Object Icp_sockets_now_initializing_gsi_LOCAL;
    Object Icp_sockets_to_be_reclaimed_LOCAL;
    Object Icp_sockets_waiting_for_icp_message_processing_LOCAL;
    Object Icp_suspend_LOCAL;
    Object Icp_trace_level_descriptions_LOCAL;
    Object Icp_trace_print_message_series_p_LOCAL;
    Object Icp_write_task_count_LOCAL;
    Object Icp_write_trace_cutoff_level_qm_LOCAL;
    Object Identified_drawing_activity_count_LOCAL;
    Object Identifying_attribute_count_for_item_new_copy_LOCAL;
    Object Idling_wait_state_string_LOCAL;
    Object Ignore_kb_flags_in_kbs_qm_LOCAL;
    Object Ignore_kb_state_changes_p_LOCAL;
    Object Image_cv_count_LOCAL;
    Object Image_data_count_LOCAL;
    Object Image_data_of_graphic_element_LOCAL;
    Object Image_left_offset_in_ws_LOCAL;
    Object Image_plane_count_LOCAL;
    Object Image_plane_for_finding_object_near_mouse_LOCAL;
    Object Image_plane_is_obscured_p_LOCAL;
    Object Image_plane_spot_count_LOCAL;
    Object Image_rendering_count_LOCAL;
    Object Image_tile_count_LOCAL;
    Object Image_tile_lru_queue_LOCAL;
    Object Image_top_offset_in_ws_LOCAL;
    Object Image_x_scale_for_finding_object_near_mouse_LOCAL;
    Object Image_y_scale_for_finding_object_near_mouse_LOCAL;
    Object In_clear_kb_p_LOCAL;
    Object In_edit_warning_context_p_LOCAL;
    Object In_external_definitions_for_module_p_LOCAL;
    Object In_find_stripped_text_slot_p_LOCAL;
    Object In_line_evaluator_array_LOCAL;
    Object In_local_source_code_control_scope_p_LOCAL;
    Object In_non_top_level_context_qm_LOCAL;
    Object In_recompile_item_p_LOCAL;
    Object In_recursive_gsi_context_LOCAL;
    Object In_suspend_resume_p_LOCAL;
    Object In_text_for_item_or_value_p_LOCAL;
    Object In_unprotected_gsi_api_call_p_LOCAL;
    Object In_write_module_as_clear_text_p_LOCAL;
    Object Include_slots_visible_only_to_roles_p_LOCAL;
    Object Incomplete_painting_action_count_LOCAL;
    Object Incomplete_phrase_count_LOCAL;
    Object Incomplete_phrases_at_frontier_LOCAL;
    Object Indent_sequences_and_structures_p_LOCAL;
    Object Index_for_stop_time_LOCAL;
    Object Index_of_open_windows_LOCAL;
    Object Index_of_resumable_p_in_icp_buffer_LOCAL;
    Object Index_of_top_of_backtrace_stack_LOCAL;
    Object Index_space_count_LOCAL;
    Object Index_to_array_of_transfer_wrappers_LOCAL;
    Object Indexed_attributes_LOCAL;
    Object Inference_background_collection_count_LOCAL;
    Object Inference_engine_parameters_LOCAL;
    Object Inform_message_information_count_LOCAL;
    Object Information_from_caught_signal_LOCAL;
    Object Information_from_trapped_error_LOCAL;
    Object Inhibit_corresponding_icp_object_making_LOCAL;
    Object Inhibit_free_reference_recording_LOCAL;
    Object Inhibit_icp_message_processing_LOCAL;
    Object Inhibit_icp_message_processing_enabled_LOCAL;
    Object Inhibit_icp_socket_reclamation_LOCAL;
    Object Inhibit_model_install_qm_LOCAL;
    Object Inhibit_modularity_consistency_checking_qm_LOCAL;
    Object Inhibit_non_real_time_clock_ticks_qm_LOCAL;
    Object Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm_LOCAL;
    Object Init_orientation_horizontal_p_LOCAL;
    Object Initial_icp_version_info_enabled_p_LOCAL;
    Object Initial_java_class_LOCAL;
    Object Initial_stack_offsets_LOCAL;
    Object Initialization_inhibit_LOCAL;
    Object Initialize_gensym_window_after_connection_done_LOCAL;
    Object Initialize_items_count_LOCAL;
    Object Initializing_clear_text_p_LOCAL;
    Object Initializing_compound_slot_qm_LOCAL;
    Object Initializing_items_needing_initialization_LOCAL;
    Object Initializing_simulator_qm_LOCAL;
    Object Initializing_state_variables_qm_LOCAL;
    Object Inline_timeout_checks_LOCAL;
    Object Inlining_data_LOCAL;
    Object Inlining_data_holder_count_LOCAL;
    Object Inner_abort_level_tag_LOCAL;
    Object Inner_paint_loop_counter_LOCAL;
    Object Input_gensym_string_for_buffer_for_internal_error_on_console_LOCAL;
    Object Input_gensym_string_for_buffer_for_string_metering_LOCAL;
    Object Input_gensym_string_for_gensym_error_message_buffer_LOCAL;
    Object Input_string_for_backtrace_text_buffer_for_internal_error_LOCAL;
    Object Input_string_for_backtrace_text_buffer_for_string_metering_LOCAL;
    Object Input_string_for_buffer_for_internal_error_on_logbook_LOCAL;
    Object Input_string_for_buffer_for_write_internal_error_LOCAL;
    Object Input_table_spot_count_LOCAL;
    Object Insertion_location_for_embedded_expressions_qm_LOCAL;
    Object Inside_action_iteration_p_LOCAL;
    Object Inside_avoid_arithmetic_errors_p_LOCAL;
    Object Inside_breakpoint_p_LOCAL;
    Object Inside_handle_event_LOCAL;
    Object Inside_handling_gensym_file_errors_scope_p_LOCAL;
    Object Inspect_command_class_description_LOCAL;
    Object Inspect_command_for_modularity_problems_qm_LOCAL;
    Object Inspect_command_history_list_LOCAL;
    Object Inspect_command_spot_count_LOCAL;
    Object Inspection_instance_counter_LOCAL;
    Object Install_item_in_model_if_appropriate_LOCAL;
    Object Installation_code_in_ok_file_LOCAL;
    Object Installation_cons_counter_LOCAL;
    Object Integer_array_class_description_LOCAL;
    Object Integer_cv_count_LOCAL;
    Object Integer_list_class_description_LOCAL;
    Object Integer_parameter_class_description_LOCAL;
    Object Integer_variable_class_description_LOCAL;
    Object Intentionally_bogus_vector_for_g2_cause_asynchronous_abort_LOCAL;
    Object Inter_g2_data_request_queue_count_LOCAL;
    Object Interesting_blocks_found_in_search_LOCAL;
    Object Intern_string_buffer_LOCAL;
    Object Internal_error_trapped_format_string_LOCAL;
    Object Internal_g2_element_types_that_can_contain_datum_LOCAL;
    Object Internal_signal_caught_format_string_LOCAL;
    Object Internal_status_of_most_recent_file_operation_LOCAL;
    Object Internal_token_count_LOCAL;
    Object Interned_list_conses_LOCAL;
    Object Interned_list_conses_in_use_LOCAL;
    Object Interned_list_count_LOCAL;
    Object Interned_list_nil_LOCAL;
    Object Interned_list_non_symbol_root_LOCAL;
    Object Interned_list_symbols_LOCAL;
    Object Interned_remote_procedure_item_passing_info_count_LOCAL;
    Object Interval_between_horizontal_grid_lines_LOCAL;
    Object Interval_between_plot_markers_LOCAL;
    Object Interval_between_vertical_grid_lines_LOCAL;
    Object Interval_for_telewindows_modernization_LOCAL;
    Object Invalid_address_LOCAL;
    Object Invalid_spot_count_LOCAL;
    Object Invisible_entity_class_description_LOCAL;
    Object Is_g2_enterprise_qm_LOCAL;
    Object Is_icon_mask_drawing_LOCAL;
    Object Iso_2022_transcoder_count_LOCAL;
    Object Iso_646_count_LOCAL;
    Object Iso_8859_10_count_LOCAL;
    Object Iso_8859_1_count_LOCAL;
    Object Iso_8859_2_count_LOCAL;
    Object Iso_8859_3_count_LOCAL;
    Object Iso_8859_4_count_LOCAL;
    Object Iso_8859_5_count_LOCAL;
    Object Iso_8859_6_count_LOCAL;
    Object Iso_8859_7_count_LOCAL;
    Object Iso_8859_8_count_LOCAL;
    Object Iso_8859_9_count_LOCAL;
    Object Iso_8859_abstract_count_LOCAL;
    Object Iso_8859_transcoder_count_LOCAL;
    Object Iso_latin1_special_character_code_map_LOCAL;
    Object Item_access_cache_count_LOCAL;
    Object Item_array_class_description_LOCAL;
    Object Item_being_read_for_new_reference_LOCAL;
    Object Item_class_description_LOCAL;
    Object Item_color_pattern_returns_overrides_only_p_LOCAL;
    Object Item_copy_handle_for_root_item_LOCAL;
    Object Item_copy_index_space_LOCAL;
    Object Item_copy_root_item_LOCAL;
    Object Item_copy_rpc_item_info_LOCAL;
    Object Item_list_class_description_LOCAL;
    Object Item_represented_by_table_spot_count_LOCAL;
    Object Items_deleted_since_load_or_save_LOCAL;
    Object Items_deleted_since_load_or_save_tail_LOCAL;
    Object Items_encountered_in_memory_walk_LOCAL;
    Object Items_made_incomplete_LOCAL;
    Object Items_made_incomplete_were_recorded_qm_LOCAL;
    Object Items_needing_initialization_LOCAL;
    Object Items_needing_initialization_tree_LOCAL;
    Object Items_to_traverse_LOCAL;
    Object Items_warned_in_edit_warning_context_LOCAL;
    Object Iteration_forms_for_embedded_expressions_qm_LOCAL;
    Object Java_class_count_LOCAL;
    Object Java_code_count_LOCAL;
    Object Java_code_exception_count_LOCAL;
    Object Java_cons_counter_LOCAL;
    Object Java_descriptor_count_LOCAL;
    Object Java_editing_categories_LOCAL;
    Object Java_field_count_LOCAL;
    Object Java_grammar_stream_qm_LOCAL;
    Object Java_method_count_LOCAL;
    Object Java_symbol_count_LOCAL;
    Object Java_tokenizer_LOCAL;
    Object Javalink_notification_versions_LOCAL;
    Object Javalink_versioned_call_data_count_LOCAL;
    Object Jis_x_0208_count_LOCAL;
    Object Joes_graph_hax_p_LOCAL;
    Object Joes_graph_hax_trace_p_LOCAL;
    Object Journal_cons_counter_LOCAL;
    Object Journal_shutout_scan_p_LOCAL;
    Object Junction_blocks_not_to_be_deleted_LOCAL;
    Object Just_update_representations_of_slot_value_LOCAL;
    Object Kana_to_ascii_map_LOCAL;
    Object Kanji_fonts_used_in_print_job_LOCAL;
    Object Kanji_row_to_font_file_name_mapping_vector_LOCAL;
    Object Kb_configuration_LOCAL;
    Object Kb_file_progress_LOCAL;
    Object Kb_file_progress_is_currently_for_modules_p_LOCAL;
    Object Kb_flags_LOCAL;
    Object Kb_flags_for_saving_LOCAL;
    Object Kb_flags_from_last_kb_read_LOCAL;
    Object Kb_format_identifier_read_qm_LOCAL;
    Object Kb_format_write_integer_buffer_LOCAL;
    Object Kb_frame_class_description_LOCAL;
    Object Kb_load_case_qm_LOCAL;
    Object Kb_module_currently_to_save_qm_LOCAL;
    Object Kb_object_index_property_name_pool_LOCAL;
    Object Kb_object_index_space_LOCAL;
    Object Kb_procedure_completion_form_qm_LOCAL;
    Object Kb_property_cons_counter_LOCAL;
    Object Kb_restrictions_LOCAL;
    Object Kb_restrictions_names_LOCAL;
    Object Kb_save_count_LOCAL;
    Object Kb_save_termination_reason_qm_LOCAL;
    Object Kb_serial_number_before_loading_this_group_LOCAL;
    Object Kb_state_changes_LOCAL;
    Object Kb_transfer_count_LOCAL;
    Object Kb_uses_crlf_p_LOCAL;
    Object Kb_window_for_initializing_definitions_LOCAL;
    Object Kb_workspace_class_description_LOCAL;
    Object Kb_workspace_image_plane_spot_count_LOCAL;
    Object Keep_edit_workspace_hidden_no_matter_what_qm_LOCAL;
    Object Key_cap_to_gensym_cyrillic_character_code_map_LOCAL;
    Object Key_index_to_key_symbol_array_LOCAL;
    Object Key_index_to_lisp_character_array_LOCAL;
    Object Keytab1_LOCAL;
    Object Keyword_package_1_LOCAL;
    Object Kfep_batch_count_LOCAL;
    Object Kfep_batchyomi_LOCAL;
    Object Kfep_batchyomilen_LOCAL;
    Object Kfep_battable_LOCAL;
    Object Kfep_capability_qm_LOCAL;
    Object Kfep_conversion_choice_menu_button_spot_count_LOCAL;
    Object Kfep_conversion_choice_menu_class_description_LOCAL;
    Object Kfep_converters_have_been_initialized_qm_LOCAL;
    Object Kfep_ghyoki_hptr_LOCAL;
    Object Kfep_ghyoki_idxbuf_LOCAL;
    Object Kfep_ghyoki_idxbuf_cache_alist_LOCAL;
    Object Kfep_ghyoki_savtblnum_LOCAL;
    Object Kfep_hensaisyo_getpos_LOCAL;
    Object Kfep_hensaisyo_gonum_LOCAL;
    Object Kfep_hensaisyo_saventry_LOCAL;
    Object Kfep_hensaisyo_tno_LOCAL;
    Object Kfep_index_file_stream_LOCAL;
    Object Kfep_kka_p_batkanakan_position_LOCAL;
    Object Kfep_kka_usetblnum_LOCAL;
    Object Kfep_kojin_bunpobits_LOCAL;
    Object Kfep_kojin_file_stream_LOCAL;
    Object Kfep_kojin_header_LOCAL;
    Object Kfep_kojin_hyolen_LOCAL;
    Object Kfep_kojin_index_LOCAL;
    Object Kfep_kojin_usedbits_LOCAL;
    Object Kfep_m_table_LOCAL;
    Object Kfep_main_file_stream_LOCAL;
    Object Kfep_master_count_LOCAL;
    Object Kfep_master_header_LOCAL;
    Object Kfep_master_header_in_characters_LOCAL;
    Object Kfep_search_limit_1_LOCAL;
    Object Kfep_search_limit_2_LOCAL;
    Object Kfep_tablemax_LOCAL;
    Object Known_gensym_acronyms_LOCAL;
    Object Known_localizations_LOCAL;
    Object Known_process_ids_qm_LOCAL;
    Object Known_regexp_functions_LOCAL;
    Object Ks_c_5601_count_LOCAL;
    Object Ksc_contiguous_character_group_lengths_LOCAL;
    Object Label_box_spot_count_LOCAL;
    Object Label_scale_for_vertical_grid_lines_LOCAL;
    Object Language_parameters_LOCAL;
    Object Language_translation_class_description_LOCAL;
    Object Large_byte_vector_LOCAL;
    Object Large_scaled_font_bucket_count_LOCAL;
    Object Largest_non_malloced_byte_vector_16_pool_index_LOCAL;
    Object Largest_non_malloced_string_pool_index_LOCAL;
    Object Last_assigned_category_index_LOCAL;
    Object Last_assigned_global_kb_number_LOCAL;
    Object Last_assigned_grammar_number_LOCAL;
    Object Last_assigned_kb_serial_number_LOCAL;
    Object Last_bootstrap_mode_qm_LOCAL;
    Object Last_deletable_token_in_namestring_LOCAL;
    Object Last_event_socket_handle_LOCAL;
    Object Last_event_socket_handle_holder_LOCAL;
    Object Last_event_status_code_LOCAL;
    Object Last_event_status_code_0_LOCAL;
    Object Last_event_status_code_1_LOCAL;
    Object Last_event_status_code_holder_LOCAL;
    Object Last_gsi_timestamp_day_LOCAL;
    Object Last_gsi_timestamp_hour_LOCAL;
    Object Last_gsi_timestamp_month_LOCAL;
    Object Last_gsi_timestamp_unix_time_LOCAL;
    Object Last_gsi_timestamp_year_LOCAL;
    Object Last_history_time_for_data_point_on_pixel_LOCAL;
    Object Last_image_plane_serial_number_LOCAL;
    Object Last_memory_stats_snapshot_LOCAL;
    Object Last_part_features_index_allocated_LOCAL;
    Object Last_player_event_time_LOCAL;
    Object Last_player_mouse_x_LOCAL;
    Object Last_player_mouse_y_LOCAL;
    Object Last_postscript_composite_object_index_LOCAL;
    Object Last_reason_for_complex_type_rejection_LOCAL;
    Object Last_roman_kana_g2_length_LOCAL;
    Object Last_roman_kata_g2_length_LOCAL;
    Object Last_semantic_check_error_string_LOCAL;
    Object Last_slot_checked_of_type_failure_LOCAL;
    Object Last_source_line_LOCAL;
    Object Last_system_class_bit_number_LOCAL;
    Object Last_ui_callback_handle_LOCAL;
    Object Last_workstation_serviced_LOCAL;
    Object Launch_recompile_for_compilations_removed_in_this_kb_qm_LOCAL;
    Object Layer_box_count_LOCAL;
    Object Lazy_assignment_of_uuids_LOCAL;
    Object Leak_list_LOCAL;
    Object Learned_list_to_expedite_ui_LOCAL;
    Object Leave_text_representation_as_a_single_line_qm_LOCAL;
    Object Left_braket_written_qm_LOCAL;
    Object Left_edge_in_window_of_graphic_element_LOCAL;
    Object Left_edge_of_draw_area_LOCAL;
    Object Left_edge_of_frame_LOCAL;
    Object Left_edge_of_line_of_text_in_window_of_graphic_element_LOCAL;
    Object Left_marker_for_cascading_menu_rubber_stamp_widget_LOCAL;
    Object Left_scroll_arrow_rubber_stamp_widget_LOCAL;
    Object Legacy_subsecond_heartbeat_adjustment_interval_LOCAL;
    Object Legend_pane_count_LOCAL;
    Object Length_of_most_negative_fixnum_as_string_LOCAL;
    Object Length_of_xml_output_line_LOCAL;
    Object Level_of_group_kb_read_LOCAL;
    Object Lexically_visible_code_bodies_LOCAL;
    Object Lexically_visible_goto_tags_LOCAL;
    Object Lexing_table_count_LOCAL;
    Object Lfsi_bound_marker_LOCAL;
    Object Lfsi_label_index_space_LOCAL;
    Object Lfsi_local_var_index_space_LOCAL;
    Object Lfsi_stack_var_index_space_LOCAL;
    Object Lfsi_unbound_marker_LOCAL;
    Object Limit_dos_filename_component_lengths_p_LOCAL;
    Object Limit_profiling_based_on_licence_level_p_LOCAL;
    Object Line_drawing_for_printing_count_LOCAL;
    Object Line_number_of_ok_file_reader_LOCAL;
    Object Links_and_objects_LOCAL;
    Object Lisp_character_to_key_index_alist_LOCAL;
    Object Lisp_grid_view_count_LOCAL;
    Object Lisp_highest_printable_character_code_LOCAL;
    Object Lisp_int_character_to_key_index_array_LOCAL;
    Object Lisp_memory_expanded_qm_LOCAL;
    Object Lisp_package_1_LOCAL;
    Object List_box_cv_count_LOCAL;
    Object List_for_import_LOCAL;
    Object List_of_all_data_servers_LOCAL;
    Object List_of_all_g2ds_interfaces_LOCAL;
    Object List_of_all_gsi_interfaces_LOCAL;
    Object List_of_already_defined_tokenizer_matching_tests_LOCAL;
    Object List_of_argument_lists_to_add_menu_items_for_category_LOCAL;
    Object List_of_bad_status_compiler_frame_note_types_LOCAL;
    Object List_of_compiler_frame_note_types_LOCAL;
    Object List_of_connection_roles_LOCAL;
    Object List_of_exported_method_texts_LOCAL;
    Object List_of_expressions_for_compilation_LOCAL;
    Object List_of_for_structures_LOCAL;
    Object List_of_funcalled_functions_LOCAL;
    Object List_of_g2ds_values_to_process_head_LOCAL;
    Object List_of_g2ds_values_to_process_tail_LOCAL;
    Object List_of_generated_contexts_LOCAL;
    Object List_of_generated_contexts_tail_LOCAL;
    Object List_of_grid_attributes_LOCAL;
    Object List_of_grid_tokens_LOCAL;
    Object List_of_gsi_values_to_process_head_LOCAL;
    Object List_of_gsi_values_to_process_tail_LOCAL;
    Object List_of_known_names_LOCAL;
    Object List_of_module_pre_conflict_resolution_post_loading_functions_LOCAL;
    Object List_of_once_only_post_conflict_resolution_post_loading_functions_LOCAL;
    Object List_of_once_only_pre_conflict_resolution_post_loading_functions_LOCAL;
    Object List_of_once_only_switched_post_loading_functions_LOCAL;
    Object List_of_previously_optimized_procedures_LOCAL;
    Object List_of_reference_structures_LOCAL;
    Object List_of_switched_and_module_post_loading_functions_LOCAL;
    Object List_of_symbols_for_symbol_value_LOCAL;
    Object List_of_types_to_be_analyzed_LOCAL;
    Object List_of_user_overridable_system_slots_LOCAL;
    Object Listed_continuation_servers_LOCAL;
    Object Listed_print_to_server_command_LOCAL;
    Object Loading_compiled_kb_p_LOCAL;
    Object Loading_kb_p_LOCAL;
    Object Local_event_count_LOCAL;
    Object Local_file_system_LOCAL;
    Object Local_filename_parser_LOCAL;
    Object Local_host_name_LOCAL;
    Object Local_insertion_location_LOCAL;
    Object Local_iteration_forms_LOCAL;
    Object Local_name_errors_LOCAL;
    Object Local_name_to_cached_designation_alist_LOCAL;
    Object Local_names_not_associated_with_roles_LOCAL;
    Object Local_namestring_generator_LOCAL;
    Object Local_nupec_variable_count_LOCAL;
    Object Local_paste_event_queue_LOCAL;
    Object Local_source_code_control_buffer_LOCAL;
    Object Local_source_code_control_number_of_characters_LOCAL;
    Object Local_ui_client_test_mode_p_LOCAL;
    Object Localization_context_LOCAL;
    Object Locked_to_kb_qm_LOCAL;
    Object Log_file_count_LOCAL;
    Object Log_file_default_pathname_qm_LOCAL;
    Object Log_file_message_count_LOCAL;
    Object Log_file_message_count_at_last_update_LOCAL;
    Object Log_file_outputting_qm_LOCAL;
    Object Log_file_parameters_LOCAL;
    Object Log_file_pathnames_LOCAL;
    Object Log_file_stream_LOCAL;
    Object Log_file_string_LOCAL;
    Object Log_file_time_at_last_update_LOCAL;
    Object Log_file_time_at_open_LOCAL;
    Object Log_file_writing_message_qm_LOCAL;
    Object Log_post_mortem_ring_buffer_to_file_p_LOCAL;
    Object Log_simple_string_data_LOCAL;
    Object Log_simple_string_reclaims_LOCAL;
    Object Logbook_page_class_description_LOCAL;
    Object Logbook_parameters_LOCAL;
    Object Logbook_view_count_LOCAL;
    Object Logical_parameter_class_description_LOCAL;
    Object Logical_variable_class_description_LOCAL;
    Object Login_handler_LOCAL;
    Object Login_handler_fsn_LOCAL;
    Object Long_array_cons_counter_LOCAL;
    Object Long_operation_notification_has_been_put_up_qm_LOCAL;
    Object Long_simple_gensym_string_counts_LOCAL;
    Object Long_simple_gensym_strings_LOCAL;
    Object Long_thrashing_cost_update_interval_LOCAL;
    Object Long_variable_class_description_LOCAL;
    Object Lookup_cons_counter_LOCAL;
    Object Loose_bottom_edge_of_visible_workspace_area_LOCAL;
    Object Loose_end_class_description_LOCAL;
    Object Loose_end_spot_count_LOCAL;
    Object Loose_left_edge_of_visible_workspace_area_LOCAL;
    Object Loose_right_edge_of_visible_workspace_area_LOCAL;
    Object Loose_top_edge_of_visible_workspace_area_LOCAL;
    Object Low_and_high_values_specified_for_vertical_axis_qm_LOCAL;
    Object Low_bound_system_variable_for_get_current_bounds_for_plot_LOCAL;
    Object Low_bound_system_variable_for_get_current_min_and_max_for_plot_from_history_LOCAL;
    Object Low_value_for_horizontal_axis_LOCAL;
    Object Low_value_for_horizontal_grid_lines_LOCAL;
    Object Low_value_for_vertical_axis_LOCAL;
    Object Low_value_for_vertical_grid_lines_LOCAL;
    Object Lower_match_rank_for_player_eyes_p_LOCAL;
    Object Lr0_follow_LOCAL;
    Object Lru_element_count_LOCAL;
    Object Lt_asterisk_gt_LOCAL;
    Object Lt_backslash_gt_LOCAL;
    Object Lt_colon_gt_LOCAL;
    Object Lt_comma_gt_LOCAL;
    Object Lt_dot_gt_LOCAL;
    Object Lt_double_quote_gt_LOCAL;
    Object Lt_end_of_sequence_gt_LOCAL;
    Object Lt_exclamation_gt_LOCAL;
    Object Lt_hyphen_gt_LOCAL;
    Object Lt_left_angle_bracket_gt_LOCAL;
    Object Lt_left_bracket_gt_LOCAL;
    Object Lt_right_angle_bracket_gt_LOCAL;
    Object Lt_right_bracket_gt_LOCAL;
    Object Lt_semicolon_gt_LOCAL;
    Object Lt_sharp_sign_gt_LOCAL;
    Object Lt_slash_gt_LOCAL;
    Object Lt_space_gt_LOCAL;
    Object Lt_tilde_gt_LOCAL;
    Object Machine_model_var_LOCAL;
    Object Macroexpanding_for_instruction_expander_LOCAL;
    Object Main_kb_being_read_qm_LOCAL;
    Object Main_menu_choices_LOCAL;
    Object Main_model_runtime_info_LOCAL;
    Object Maintain_stack_of_current_part_descriptions_p_LOCAL;
    Object Maintaining_g2ds_interface_status_changed_p_LOCAL;
    Object Maintaining_gsi_interface_status_changed_p_LOCAL;
    Object Make_gsi_instance_existing_instance_LOCAL;
    Object Making_distribution_system_qm_LOCAL;
    Object Managed_bignum_pool_LOCAL;
    Object Many_more_data_points_than_pixels_qm_LOCAL;
    Object Mark_for_modules_with_unsaved_changes_LOCAL;
    Object Marker_for_meter_class_description_LOCAL;
    Object Master_hierarchy_reconciliation_switches_LOCAL;
    Object Match_pattern_for_inspect_binding_vector_LOCAL;
    Object Match_regular_expression_for_g2_stream_directory_hook_LOCAL;
    Object Max_gsi_sensors_in_a_group_LOCAL;
    Object Max_stack_index_LOCAL;
    Object Max_var_index_LOCAL;
    Object Maximum_clock_tick_length_LOCAL;
    Object Maximum_file_name_length_qm_LOCAL;
    Object Maximum_height_LOCAL;
    Object Maximum_length_for_sax_strings_LOCAL;
    Object Maximum_length_of_ascii_string_LOCAL;
    Object Maximum_length_of_kana_string_LOCAL;
    Object Maximum_log_file_name_prefix_length_qm_LOCAL;
    Object Maximum_number_of_array_or_list_elements_to_describe_LOCAL;
    Object Maximum_number_of_slots_in_structure_type_LOCAL;
    Object Maximum_number_of_tries_to_create_temp_file_LOCAL;
    Object Maximum_object_passing_bandwidth_LOCAL;
    Object Maximum_region_complexity_LOCAL;
    Object Maximum_retries_for_foreign_image_connection_LOCAL;
    Object Maximum_significant_decimal_digits_in_gensym_float_LOCAL;
    Object Maximum_time_slice_size_LOCAL;
    Object Maximum_width_LOCAL;
    Object Maximum_x_value_for_new_data_LOCAL;
    Object Maximum_y_value_LOCAL;
    Object Maximum_y_value_for_new_data_LOCAL;
    Object Maximum_y_value_for_pixel_LOCAL;
    Object May_create_simulation_subtable_from_module_data_p_LOCAL;
    Object May_return_from_breakpoint_LOCAL;
    Object Media_stream_count_LOCAL;
    Object Memory_category_count_LOCAL;
    Object Memory_limit_info_count_LOCAL;
    Object Memory_limit_variable_names_for_decacheable_structures_LOCAL;
    Object Memory_used_for_interned_gensym_strings_LOCAL;
    Object Memory_used_for_interned_text_strings_LOCAL;
    Object Memory_walk_verbose_p_LOCAL;
    Object Menu_button_spot_count_LOCAL;
    Object Menu_choose_state_count_LOCAL;
    Object Menu_class_description_LOCAL;
    Object Menu_clean_up_menu_to_keep_LOCAL;
    Object Menu_colors_LOCAL;
    Object Menu_colors_sorted_alphabetically_LOCAL;
    Object Menu_colors_sorted_by_hue_LOCAL;
    Object Menu_item_spot_count_LOCAL;
    Object Menu_items_for_parsing_LOCAL;
    Object Menu_pane_spot_count_LOCAL;
    Object Menu_parameters_LOCAL;
    Object Menu_title_spot_count_LOCAL;
    Object Menu_workspace_class_description_LOCAL;
    Object Merge_pathnames_rules_LOCAL;
    Object Merge_pathnames_rules_sorted_p_LOCAL;
    Object Message_board_class_description_LOCAL;
    Object Message_board_parameters_LOCAL;
    Object Message_class_description_LOCAL;
    Object Message_completion_interval_LOCAL;
    Object Message_definition_class_description_LOCAL;
    Object Message_illegal_symbol_text_string_contains_a_newline_LOCAL;
    Object Message_illegal_symbol_text_string_contains_fffe_LOCAL;
    Object Message_illegal_symbol_text_string_contains_ffff_LOCAL;
    Object Message_illegal_symbol_text_string_empty_LOCAL;
    Object Message_illegal_symbol_text_string_too_long_LOCAL;
    Object Meter_class_description_LOCAL;
    Object Meter_lag_time_variables_LOCAL;
    Object Meter_or_dial_spot_count_LOCAL;
    Object Meter_spot_count_LOCAL;
    Object Metered_clock_tick_length_LOCAL;
    Object Method_class_description_LOCAL;
    Object Method_declaration_class_description_LOCAL;
    Object Milliseconds_between_retries_for_foreign_image_connection_LOCAL;
    Object Milliseconds_to_sleep_after_connection_on_pc_platforms_LOCAL;
    Object Milliseconds_to_sleep_before_connecting_to_foreign_image_LOCAL;
    Object Min_string_length_to_report_LOCAL;
    Object Minimal_character_description_count_LOCAL;
    Object Minimal_fragmentation_seeds_LOCAL;
    Object Minimnal_bandwidth_for_resumable_sequence_range_LOCAL;
    Object Minimum_and_maximum_y_value_set_qm_LOCAL;
    Object Minimum_bandwidth_per_timeslice_LOCAL;
    Object Minimum_distance_between_fins_LOCAL;
    Object Minimum_distance_for_data_points_LOCAL;
    Object Minimum_grid_height_LOCAL;
    Object Minimum_grid_width_LOCAL;
    Object Minimum_number_of_blocks_for_spacial_index_LOCAL;
    Object Minimum_number_of_blocks_to_retain_spacial_index_LOCAL;
    Object Minimum_simulation_time_increment_LOCAL;
    Object Minimum_x_value_for_new_data_LOCAL;
    Object Minimum_y_value_LOCAL;
    Object Minimum_y_value_for_new_data_LOCAL;
    Object Minimum_y_value_for_pixel_LOCAL;
    Object Minus_one_integer_LOCAL;
    Object Miscellaneous_parameters_LOCAL;
    Object Missing_local_names_already_reported_LOCAL;
    Object Modal_menu_state_count_LOCAL;
    Object Model_definition_class_description_LOCAL;
    Object Model_queue_count_LOCAL;
    Object Model_runtime_info_count_LOCAL;
    Object Models_used_p_LOCAL;
    Object Modify_control_action_type_count_LOCAL;
    Object Modify_control_structure_count_LOCAL;
    Object Modify_dialog_structure_count_LOCAL;
    Object Modularity_checking_LOCAL;
    Object Module_information_LOCAL;
    Object Module_required_by_relationships_LOCAL;
    Object Module_search_path_tokenizer_LOCAL;
    Object Modules_and_system_tables_a_list_LOCAL;
    Object Modules_considered_in_loading_schedule_so_far_LOCAL;
    Object Modules_listed_so_far_LOCAL;
    Object Modules_loaded_in_this_group_LOCAL;
    Object Modules_scheduled_so_far_LOCAL;
    Object Modules_scheduled_so_far_by_save_all_modules_of_kb_LOCAL;
    Object Modules_that_have_already_been_loaded_LOCAL;
    Object Modules_to_translate_verbosely_LOCAL;
    Object Most_fixnum_digits_LOCAL;
    Object Most_lefthand_float_digits_LOCAL;
    Object Most_negative_fixnum_as_string_LOCAL;
    Object Most_recent_bandwidth_per_timeslice_qm_LOCAL;
    Object Most_recent_defun_warned_for_catch_qm_LOCAL;
    Object Most_recent_defun_warned_for_unwind_protect_qm_LOCAL;
    Object Most_recent_extremum_maximum_for_pixel_p_LOCAL;
    Object Most_recent_extremum_maximum_p_LOCAL;
    Object Most_recent_g2_time_LOCAL;
    Object Most_recent_trend_chart_checked_LOCAL;
    Object Most_recent_xml_checksum_differences_LOCAL;
    Object Most_righthand_float_zeros_LOCAL;
    Object Mouse_drag_detector_state_count_LOCAL;
    Object Mouse_pointer_count_LOCAL;
    Object Mouse_pointer_of_frame_LOCAL;
    Object Mouse_watch_state_count_LOCAL;
    Object Mouse_x_in_workspace_LOCAL;
    Object Mouse_y_in_workspace_LOCAL;
    Object Move_dragging_state_count_LOCAL;
    Object Ms_to_wait_for_cvs_LOCAL;
    Object Msw_cyrillic_code_map_LOCAL;
    Object Multiframe_table_spot_count_LOCAL;
    Object Multiplicative_counter_for_evaluation_LOCAL;
    Object Multiplier_for_turning_off_data_collection_LOCAL;
    Object Multiply_wild_regular_expression_node_count_LOCAL;
    Object Mutable_slot_description_list_head_LOCAL;
    Object N_32bit_constants_LOCAL;
    Object Name_box_class_description_LOCAL;
    Object Name_box_spot_count_LOCAL;
    Object Name_for_find_menu_item_LOCAL;
    Object Name_for_local_home_LOCAL;
    Object Name_of_current_editor_command_qm_LOCAL;
    Object Name_of_customer_in_ok_file_LOCAL;
    Object Name_of_file_slot_description_LOCAL;
    Object Name_of_kb_being_read_LOCAL;
    Object Name_of_module_being_read_qm_LOCAL;
    Object Name_text_string_for_kb_being_read_LOCAL;
    Object Named_gensym_structure_count_LOCAL;
    Object Names_and_info_for_chaining_LOCAL;
    Object Names_and_sizes_for_decacheable_structures_LOCAL;
    Object Names_of_grammars_to_add_rules_to_LOCAL;
    Object Names_used_for_more_than_one_item_LOCAL;
    Object Namestring_for_kb_being_read_LOCAL;
    Object Native_alias_creation_dialog_LOCAL;
    Object Native_dialog_count_LOCAL;
    Object Native_dialog_handle_parity_LOCAL;
    Object Native_editor_already_updated_LOCAL;
    Object Native_font_count_LOCAL;
    Object Native_image_plane_options_LOCAL;
    Object Native_image_plane_updated_by_client_LOCAL;
    Object Native_login_dialog_LOCAL;
    Object Native_menu_counter_LOCAL;
    Object Native_menu_id_to_handle_and_item_number_table_LOCAL;
    Object Native_menu_table_LOCAL;
    Object Native_menu_unique_id_counter_LOCAL;
    Object Native_printer_information_LOCAL;
    Object Native_printing_color_differences_LOCAL;
    Object Native_printing_icon_x_in_window_LOCAL;
    Object Native_printing_icon_y_in_window_LOCAL;
    Object Native_simple_dialog_state_count_LOCAL;
    Object Native_window_client_operation_LOCAL;
    Object Native_window_count_LOCAL;
    Object Native_window_heartbeat_task_LOCAL;
    Object Native_window_notices_enter_and_leave_events_p_LOCAL;
    Object Native_window_updated_by_client_LOCAL;
    Object Need_to_check_plist_p_LOCAL;
    Object Needed_domain_LOCAL;
    Object Negative_shutdown_interval_for_disallowed_icp_connection_LOCAL;
    Object Network_octet_buffer_length_LOCAL;
    Object New_byte_code_body_list_LOCAL;
    Object New_compiled_byte_code_body_list_LOCAL;
    Object New_dateline_qm_LOCAL;
    Object New_descriptions_LOCAL;
    Object New_g2_classic_ui_p_LOCAL;
    Object New_goto_tag_counter_LOCAL;
    Object New_position_of_horizontal_elevator_of_frame_LOCAL;
    Object New_position_of_vertical_elevator_of_frame_LOCAL;
    Object New_saved_kb_format_p_LOCAL;
    Object New_table_LOCAL;
    Object New_table_background_spot_count_LOCAL;
    Object New_table_cell_spot_count_LOCAL;
    Object New_table_spot_count_LOCAL;
    Object New_value_computed_in_formula_qm_LOCAL;
    Object Newline_characters_LOCAL;
    Object Next_character_for_kb_qm_LOCAL;
    Object Next_class_bit_number_LOCAL;
    Object Next_continuation_function_qm_LOCAL;
    Object Next_element_to_be_sorted_qm_LOCAL;
    Object Next_eq_hash_value_LOCAL;
    Object Next_info_LOCAL;
    Object Next_info_reclaimer_qm_LOCAL;
    Object Next_native_eq_dialog_handle_LOCAL;
    Object Next_object_index_property_number_LOCAL;
    Object Next_old_style_return_function_qm_LOCAL;
    Object Next_serial_number_to_be_generated_LOCAL;
    Object Next_stack_frame_var_location_LOCAL;
    Object Nil_indicator_LOCAL;
    Object Nil_interned_LOCAL;
    Object Nms_constructing_built_in_menus_p_LOCAL;
    Object Nms_menu_count_LOCAL;
    Object Nms_menu_hash_table_LOCAL;
    Object Nms_menu_item_count_LOCAL;
    Object Nms_reclaim_hook_LOCAL;
    Object No_arg_LOCAL;
    Object No_data_server_error_LOCAL;
    Object No_grouping_tag_for_grouping_specification_LOCAL;
    Object No_saved_initial_value_LOCAL;
    Object No_value_LOCAL;
    Object Node_id_for_uuid_LOCAL;
    Object Node_id_for_uuid_uses_ethernet_address_p_LOCAL;
    Object Nodes_for_generalized_dos_filename_parser_LOCAL;
    Object Nodes_for_unix_filename_parser_LOCAL;
    Object Nodes_for_vms_filename_parser_LOCAL;
    Object Non_context_top_level_binding_forms_LOCAL;
    Object Non_kb_workspace_class_description_LOCAL;
    Object Non_kb_workspace_image_plane_spot_count_LOCAL;
    Object Non_menu_choices_LOCAL;
    Object Non_procedure_root_invocations_LOCAL;
    Object Normal_completion_count_LOCAL;
    Object Note_as_kb_state_change_qm_LOCAL;
    Object Note_blocks_in_tformat_LOCAL;
    Object Note_kb_state_changes_via_system_procedures_qm_LOCAL;
    Object Note_things_encountered_during_role_service_qm_LOCAL;
    Object Notification_data_version_map_LOCAL;
    Object Noting_changes_to_kb_p_LOCAL;
    Object Null_char_LOCAL;
    Object Number_of_contexts_allocated_LOCAL;
    Object Number_of_horizontal_grid_lines_LOCAL;
    Object Number_of_icp_bytes_for_message_series_LOCAL;
    Object Number_of_icp_bytes_in_message_group_LOCAL;
    Object Number_of_icp_bytes_left_in_current_buffer_LOCAL;
    Object Number_of_icp_bytes_left_in_message_series_LOCAL;
    Object Number_of_icp_bytes_ready_to_read_LOCAL;
    Object Number_of_icp_bytes_to_fill_buffer_LOCAL;
    Object Number_of_kb_characters_so_far_qm_LOCAL;
    Object Number_of_kb_lines_so_far_LOCAL;
    Object Number_of_ksc_codes_LOCAL;
    Object Number_of_lexing_tables_in_cache_LOCAL;
    Object Number_of_memory_regions_LOCAL;
    Object Number_of_no_binds_LOCAL;
    Object Number_of_raster_oddspaces_LOCAL;
    Object Number_of_significant_digits_LOCAL;
    Object Number_of_simulated_variables_processed_LOCAL;
    Object Number_of_variables_to_process_at_a_time_LOCAL;
    Object Number_of_vertical_grid_lines_LOCAL;
    Object Nupec_catch_up_mode_caught_up_qm_LOCAL;
    Object Nupec_synchronize_variable_or_parameter_count_LOCAL;
    Object Object_building_problem_count_LOCAL;
    Object Object_class_description_LOCAL;
    Object Object_definition_class_description_LOCAL;
    Object Object_file_pathname_for_machine_LOCAL;
    Object Object_map_plist_for_icp_tree_LOCAL;
    Object Object_passing_info_count_LOCAL;
    Object Object_pool_meters_LOCAL;
    Object Objects_to_not_consider_qm_LOCAL;
    Object Obsolete_frame_note_types_from_modularity_development_LOCAL;
    Object Off_window_color_map_LOCAL;
    Object Ok_authorized_packages_LOCAL;
    Object Ok_authorized_products_LOCAL;
    Object Ok_class_description_LOCAL;
    Object Ok_expiration_date_qm_LOCAL;
    Object Ok_file_saving_mode_qm_LOCAL;
    Object Ok_file_token_cons_counter_LOCAL;
    Object Ok_file_token_count_LOCAL;
    Object Ok_make_g2_secure_qm_LOCAL;
    Object Ok_maximum_number_of_concurrent_floating_telewindows_allowed_LOCAL;
    Object Ok_maximum_number_of_concurrent_floating_tw2_allowed_LOCAL;
    Object Ok_modified_LOCAL;
    Object Ok_number_of_processes_authorized_LOCAL;
    Object Old_exposed_region_LOCAL;
    Object Old_timespan_system_variable_for_compute_trend_chart_time_bounds_LOCAL;
    Object On_monochrome_raster_list_p_LOCAL;
    Object On_window_with_drawing_LOCAL;
    Object On_window_without_drawing_LOCAL;
    Object One_integer_LOCAL;
    Object One_sequence_of_following_tokens_only_p_LOCAL;
    Object Only_impose_device_set_widths_to_squeeze_qm_LOCAL;
    Object Operation_around_record_of_items_made_incomplete_LOCAL;
    Object Operation_of_graphic_element_LOCAL;
    Object Operative_task_list_LOCAL;
    Object Optimized_constant_op_codes_LOCAL;
    Object Optimized_constant_pc_LOCAL;
    Object Optimized_constant_vector_LOCAL;
    Object Optimized_constant_vector_index_LOCAL;
    Object Optional_modules_map_LOCAL;
    Object Orientation_horizontal_p_LOCAL;
    Object Orientation_of_frame_LOCAL;
    Object Original_kb_state_plist_written_qm_LOCAL;
    Object Out_of_memory_handler_LOCAL;
    Object Outer_native_image_plane_LOCAL;
    Object Outermost_stack_frame_var_binding_qm_LOCAL;
    Object Output_only_table_spot_count_LOCAL;
    Object Output_vector_for_object_LOCAL;
    Object Output_window_for_printing_qm_LOCAL;
    Object Outputting_to_gensym_string_LOCAL;
    Object Outputting_to_wide_string_LOCAL;
    Object Outside_window_spot_count_LOCAL;
    Object Outstanding_float_function_floats_LOCAL;
    Object Outstanding_frame_vector_count_LOCAL;
    Object Overflow_byte_count_LOCAL;
    Object Override_eliminate_for_gsi_no_utf_g_p_LOCAL;
    Object Override_eliminate_for_gsi_p_LOCAL;
    Object Override_preferred_editor_LOCAL;
    Object Overriding_alignment_LOCAL;
    Object Oversized_simple_float_array_pool_memory_usage_LOCAL;
    Object Oversized_simple_vector_pool_counts_LOCAL;
    Object Overview_pane_spot_count_LOCAL;
    Object Package_preparation_mode_LOCAL;
    Object Pad_for_ok_file_reader_LOCAL;
    Object Page_class_description_LOCAL;
    Object Paint_only_target_monochrome_raster_p_LOCAL;
    Object Painting_for_graph_activation_p_LOCAL;
    Object Pane_background_spot_count_LOCAL;
    Object Pane_border_spot_count_LOCAL;
    Object Pane_component_spot_count_LOCAL;
    Object Pane_count_LOCAL;
    Object Pane_for_debugger_pause_LOCAL;
    Object Pane_spot_count_LOCAL;
    Object Parameter_class_description_LOCAL;
    Object Parent_trend_chart_LOCAL;
    Object Parse_object_count_LOCAL;
    Object Parse_table_count_LOCAL;
    Object Parsing_context_count_LOCAL;
    Object Parsing_token_count_LOCAL;
    Object Part_exceptions_from_parents_LOCAL;
    Object Part_feature_enter_methods_LOCAL;
    Object Part_feature_exit_methods_LOCAL;
    Object Part_feature_indexes_LOCAL;
    Object Part_feature_recall_stack_LOCAL;
    Object Part_features_to_write_LOCAL;
    Object Part_index_LOCAL;
    Object Part_stack_cons_counter_LOCAL;
    Object Part_text_size_parameters_LOCAL;
    Object Partial_command_count_LOCAL;
    Object Partition_details_of_current_branch_of_frame_LOCAL;
    Object Partition_float_union_LOCAL;
    Object Partition_long_union_LOCAL;
    Object Parts_of_annotated_frames_currently_erased_LOCAL;
    Object Path_cons_counter_LOCAL;
    Object Pathname_component_token_menu_button_spot_count_LOCAL;
    Object Pathname_for_disabling_g2_hangul_star_command_line_LOCAL;
    Object Pathname_for_disabling_g2_init_command_line_LOCAL;
    Object Pathname_for_disabling_g2_kanji_star_command_line_LOCAL;
    Object Pathname_for_disabling_g2_kb_command_line_LOCAL;
    Object Pathname_for_disabling_g2_minm_star_command_line_LOCAL;
    Object Pathname_for_disabling_g2_module_map_command_line_LOCAL;
    Object Pathname_for_disabling_g2_ok_command_line_LOCAL;
    Object Pathname_for_disabling_g2v11_ok_command_line_LOCAL;
    Object Pathname_for_disabling_g2v12_ok_command_line_LOCAL;
    Object Pathname_for_disabling_g2v51_ok_command_line_LOCAL;
    Object Pathname_for_disabling_g2v5_ok_command_line_LOCAL;
    Object Pathname_for_disabling_g2v6_ok_command_line_LOCAL;
    Object Pathname_for_disabling_g2v7_ok_command_line_LOCAL;
    Object Pathname_for_disabling_g2v83_ok_command_line_LOCAL;
    Object Pathname_for_disabling_g2v8_ok_command_line_LOCAL;
    Object Pathname_for_disabling_g2v9_ok_command_line_LOCAL;
    Object Pathname_for_disabling_tw_hangul_star_command_line_LOCAL;
    Object Pathname_for_disabling_tw_kanji_star_command_line_LOCAL;
    Object Pathname_for_disabling_tw_minm_star_command_line_LOCAL;
    Object Pathname_for_disabling_tw_ok_command_line_LOCAL;
    Object Pathname_for_disabling_twv11_ok_command_line_LOCAL;
    Object Pathname_for_disabling_twv12_ok_command_line_LOCAL;
    Object Pathname_for_disabling_twv5_ok_command_line_LOCAL;
    Object Pathname_for_disabling_twv6_ok_command_line_LOCAL;
    Object Pathname_for_disabling_twv7_ok_command_line_LOCAL;
    Object Pathname_for_disabling_twv8_ok_command_line_LOCAL;
    Object Pathname_for_disabling_twv9_ok_command_line_LOCAL;
    Object Pathname_for_distribution_binaries_qm_LOCAL;
    Object Pathname_with_default_type_if_required_for_module_pathnames_qm_LOCAL;
    Object Pattern_checking_inverse_references_LOCAL;
    Object Pending_activity_count_LOCAL;
    Object Pending_native_dialogs_LOCAL;
    Object Pending_write_reference_list_LOCAL;
    Object Percent_running_LOCAL;
    Object Permanent_mutable_list_LOCAL;
    Object Permit_cvs_timeout_dialog_p_LOCAL;
    Object Permit_spacial_index_p_LOCAL;
    Object Permit_transfer_of_permanent_items_p_LOCAL;
    Object Permitted_restriction_set_LOCAL;
    Object Phrase_copying_needs_annotation_rehashing_LOCAL;
    Object Phrase_pool_cons_counter_LOCAL;
    Object Phrase_rule_completion_count_LOCAL;
    Object Ping_seq_id_array_LOCAL;
    Object Pixmap_count_LOCAL;
    Object Place_for_for_telewindows_modernization_LOCAL;
    Object Place_reference_internals_count_LOCAL;
    Object Platform_independent_print_spool_command_file_name_LOCAL;
    Object Player_cons_counter_LOCAL;
    Object Player_control_stack_LOCAL;
    Object Player_current_instruction_LOCAL;
    Object Player_definition_stack_LOCAL;
    Object Player_icp_connection_LOCAL;
    Object Player_lexical_binding_stack_LOCAL;
    Object Player_location_stack_LOCAL;
    Object Player_mouse_x_LOCAL;
    Object Player_mouse_y_LOCAL;
    Object Player_named_locations_LOCAL;
    Object Player_pace_LOCAL;
    Object Player_require_modules_already_sent_LOCAL;
    Object Player_state_LOCAL;
    Object Player_target_gensym_window_g2_struct_qm_LOCAL;
    Object Player_value_stack_LOCAL;
    Object Plist_from_end_element_qm_LOCAL;
    Object Plist_has_been_checked_p_LOCAL;
    Object Plist_of_corresponding_icp_object_maps_for_font_maps_LOCAL;
    Object Plot_class_description_LOCAL;
    Object Plot_connector_painting_buffer_head_LOCAL;
    Object Plot_connector_painting_buffer_limit_LOCAL;
    Object Plot_connector_painting_buffer_size_LOCAL;
    Object Plot_connector_painting_buffer_tail_LOCAL;
    Object Plot_data_ring_buffer_count_LOCAL;
    Object Plot_marker_qm_LOCAL;
    Object Plot_max_qm_LOCAL;
    Object Plot_min_and_max_qm_LOCAL;
    Object Plot_min_qm_LOCAL;
    Object Pm_max_length_LOCAL;
    Object Pm_slot_names_LOCAL;
    Object Pm_temp_string_LOCAL;
    Object Pointer_for_dial_class_description_LOCAL;
    Object Poly_line_pattern_LOCAL;
    Object Poly_line_style_LOCAL;
    Object Poly_line_width_LOCAL;
    Object Poly_vertices_LOCAL;
    Object Polygon_fill_color_difference_LOCAL;
    Object Polygon_fill_pattern_LOCAL;
    Object Pop_fonts_stack_LOCAL;
    Object Popup_frames_available_LOCAL;
    Object Position_in_file_slot_description_LOCAL;
    Object Possible_label_dispatch_destination_LOCAL;
    Object Possible_phrase_count_LOCAL;
    Object Post_analyzer_warning_note_qm_LOCAL;
    Object Post_analyzer_warning_notes_for_generic_simulation_formulas_qm_LOCAL;
    Object Post_compiler_warning_note_qm_LOCAL;
    Object Post_draw_methods_for_text_box_formats_LOCAL;
    Object Post_kb_loading_consistency_analysis_LOCAL;
    Object Post_loading_functions_will_be_executed_again_later_qm_LOCAL;
    Object Post_mortem_internal_buffer_LOCAL;
    Object Post_mortem_report_buffer_LOCAL;
    Object Post_mortem_ring_buffer_logfile_line_count_LOCAL;
    Object Post_mortem_ring_buffer_logfile_namestring_LOCAL;
    Object Post_mortem_ring_buffer_logfile_stream_LOCAL;
    Object Postpone_cell_erase_until_redraw_p_LOCAL;
    Object Postscript_composite_object_mapping_LOCAL;
    Object Postscript_computed_variables_mapping_LOCAL;
    Object Postscript_current_graph_line_drawing_index_LOCAL;
    Object Postscript_definition_operation_counter_LOCAL;
    Object Postscript_emit_composite_object_without_name_LOCAL;
    Object Postscript_emit_integers_as_color_differences_LOCAL;
    Object Postscript_emitting_definition_LOCAL;
    Object Postscript_object_mapping_for_graph_renderings_LOCAL;
    Object Postscript_object_mapping_for_icon_renderings_LOCAL;
    Object Postscript_printing_icon_renderings_LOCAL;
    Object Preexisting_frames_LOCAL;
    Object Prefer_bitmap_to_scaled_outline_font_at_full_scale_qm_LOCAL;
    Object Prefer_bitmap_to_scaled_outline_font_qm_LOCAL;
    Object Prefer_bitmap_to_scaled_outline_if_matched_at_any_scale_qm_LOCAL;
    Object Prefer_kb_procedures_to_system_defined_p_LOCAL;
    Object Preprocessing_tokenizer_LOCAL;
    Object Preprocessor_errors_qm_LOCAL;
    Object Presentation_mode_LOCAL;
    Object Preserve_non_default_icon_colors_or_variables_qm_LOCAL;
    Object Previous_cascaded_ring_buffer_accessed_LOCAL;
    Object Previous_index_for_ring_buffer_LOCAL;
    Object Previous_modulus_counter_for_evaluation_LOCAL;
    Object Previous_timestamp_qm_LOCAL;
    Object Print_spooling_LOCAL;
    Object Print_wide_string_max_length_LOCAL;
    Object Printer_setup_LOCAL;
    Object Printing_cons_counter_LOCAL;
    Object Printing_format_LOCAL;
    Object Printing_graph_rendering_color_list_qm_LOCAL;
    Object Printing_icon_current_region_index_qm_LOCAL;
    Object Printing_in_progress_p_LOCAL;
    Object Printing_pass_number_LOCAL;
    Object Printing_stream_LOCAL;
    Object Priority_10_last_gensym_time_LOCAL;
    Object Priority_1_last_gensym_time_LOCAL;
    Object Priority_2_last_gensym_time_LOCAL;
    Object Priority_3_last_gensym_time_LOCAL;
    Object Priority_4_last_gensym_time_LOCAL;
    Object Priority_5_last_gensym_time_LOCAL;
    Object Priority_6_last_gensym_time_LOCAL;
    Object Priority_7_last_gensym_time_LOCAL;
    Object Priority_8_last_gensym_time_LOCAL;
    Object Priority_9_last_gensym_time_LOCAL;
    Object Priority_of_current_task_LOCAL;
    Object Priority_of_icp_control_messages_LOCAL;
    Object Priority_of_icp_message_service_LOCAL;
    Object Priority_of_next_task_LOCAL;
    Object Priority_of_rpc_service_LOCAL;
    Object Problems_reformatting_graph_qm_LOCAL;
    Object Proc_cons_counter_LOCAL;
    Object Procedure_alist_LOCAL;
    Object Procedure_branch_short_cuts_LOCAL;
    Object Procedure_class_description_LOCAL;
    Object Procedure_current_time_LOCAL;
    Object Procedure_end_time_LOCAL;
    Object Procedure_function_template_alist_LOCAL;
    Object Procedure_invocation_class_description_LOCAL;
    Object Procedure_invocation_count_LOCAL;
    Object Procedure_start_time_LOCAL;
    Object Procedures_to_warn_about_p_LOCAL;
    Object Proceed_with_edit_LOCAL;
    Object Process_checksum_for_image_data_p_LOCAL;
    Object Process_count_LOCAL;
    Object Process_initializations_alist_LOCAL;
    Object Process_instance_created_for_current_process_qm_LOCAL;
    Object Process_specific_system_pathname_LOCAL;
    Object Processing_as_fast_as_possible_models_qm_LOCAL;
    Object Production_count_LOCAL;
    Object Profiling_enabled_qm_LOCAL;
    Object Profiling_structure_LOCAL;
    Object Prohibited_restriction_set_LOCAL;
    Object Projecting_to_collect_description_for_new_table_LOCAL;
    Object Projection_LOCAL;
    Object Projection_computing_path_of_focus_LOCAL;
    Object Projection_drawing_LOCAL;
    Object Projection_focus_annotation_LOCAL;
    Object Projection_focus_cell_index_LOCAL;
    Object Projection_focus_cell_new_cached_value_LOCAL;
    Object Projection_focus_method_LOCAL;
    Object Projection_focus_path_LOCAL;
    Object Projection_funcall_on_focus_LOCAL;
    Object Projection_mode_LOCAL;
    Object Projection_of_new_table_accumulating_size_LOCAL;
    Object Projection_tracking_LOCAL;
    Object Projection_update_dependencies_LOCAL;
    Object Prop_grid_contents_LOCAL;
    Object Prop_grid_verb_count_LOCAL;
    Object Property_grid_count_LOCAL;
    Object Property_grid_node_count_LOCAL;
    Object Prune_token_categories_visited_more_than_once_p_LOCAL;
    Object Pseudo_attribute_count_LOCAL;
    Object Pseudo_class_slot_description_LOCAL;
    Object Pseudo_frame_count_LOCAL;
    Object Pseudo_instruction_stream_count_LOCAL;
    Object Pseudo_keysyms_LOCAL;
    Object Pulse_rate_multiplier_LOCAL;
    Object Pulse_rate_options_LOCAL;
    Object Purpose_of_extreme_edges_LOCAL;
    Object Purpose_of_frame_projecting_LOCAL;
    Object Push_button_cv_count_LOCAL;
    Object Put_current_evaluation_value_old_value_qm_LOCAL;
    Object Put_current_evaluation_value_return_value_LOCAL;
    Object Put_current_value_called_from_simulator_p_LOCAL;
    Object Quality_of_graphic_element_LOCAL;
    Object Quantitative_parameter_class_description_LOCAL;
    Object Quantitative_variable_class_description_LOCAL;
    Object Quantity_array_class_description_LOCAL;
    Object Quantity_cv_count_LOCAL;
    Object Quantity_list_class_description_LOCAL;
    Object Query_cell_stream_count_LOCAL;
    Object Question_mark_box_class_description_LOCAL;
    Object Queue_count_LOCAL;
    Object Queue_element_count_LOCAL;
    Object Queue_existential_rules_LOCAL;
    Object Queue_existential_rules_tail_LOCAL;
    Object Queue_item_cons_counter_LOCAL;
    Object Queue_of_active_gfi_input_interface_objects_LOCAL;
    Object Queue_of_active_gfi_output_interface_objects_LOCAL;
    Object Queue_of_active_uninterruptable_gfi_input_interface_objects_LOCAL;
    Object Queue_of_active_uninterruptable_gfi_output_interface_objects_LOCAL;
    Object Queue_of_classes_to_be_undefined_LOCAL;
    Object Radio_button_status_flags_LOCAL;
    Object Radio_button_status_flags_1_LOCAL;
    Object Ran_out_of_time_qm_LOCAL;
    Object Random_real_0_result_LOCAL;
    Object Random_state_array_LOCAL;
    Object Random_state_array_24_pointer_LOCAL;
    Object Random_state_array_current_pointer_LOCAL;
    Object Random_variation_LOCAL;
    Object Random_variation_2_LOCAL;
    Object Range_too_small_qm_LOCAL;
    Object Read_kb_buffer_LOCAL;
    Object Read_kb_buffer_index_LOCAL;
    Object Read_kb_buffer_length_LOCAL;
    Object Read_kb_next_character_LOCAL;
    Object Read_kb_stream_LOCAL;
    Object Read_ok_file_buffer_1_LOCAL;
    Object Read_xml_line_LOCAL;
    Object Reading_ghost_definitions_p_LOCAL;
    Object Reading_initial_plist_for_clear_text_kb_LOCAL;
    Object Reading_kb_p_LOCAL;
    Object Reading_ok_file_LOCAL;
    Object Readout_table_class_description_LOCAL;
    Object Readout_table_spot_count_LOCAL;
    Object Real_time_of_last_g2_tick_LOCAL;
    Object Real_time_to_tick_p_base_LOCAL;
    Object Really_large_byte_vector_LOCAL;
    Object Reason_for_type_failure_LOCAL;
    Object Receiving_resumable_object_count_LOCAL;
    Object Receiving_rpc_arglist_structure_count_LOCAL;
    Object Recent_enough_g2_revision_for_trend_charts_LOCAL;
    Object Recent_loaded_kbs_LOCAL;
    Object Reclaim_fonts_stack_LOCAL;
    Object Reclaim_text_value_from_postponed_erase_p_LOCAL;
    Object Reclaimed_strings_reported_LOCAL;
    Object Reclaimed_telewindows_boxes_LOCAL;
    Object Reclaimed_temporary_character_bitmaps_LOCAL;
    Object Reclaimed_things_LOCAL;
    Object Recompile_from_inspect_LOCAL;
    Object Recompile_on_next_load_LOCAL;
    Object Record_class_name_conflicts_qm_LOCAL;
    Object Record_definitional_name_conflicts_qm_LOCAL;
    Object Record_fixnum_time_units_of_sleep_this_clock_tick_qm_LOCAL;
    Object Record_of_class_name_conflicts_qm_LOCAL;
    Object Record_of_definitional_name_conflicts_qm_LOCAL;
    Object Recording_items_made_incomplete_qm_LOCAL;
    Object Recursive_depth_LOCAL;
    Object Recycled_icp_buffers_LOCAL;
    Object Recycled_resumption_conses_LOCAL;
    Object Recycled_variable_fill_icp_buffers_LOCAL;
    Object Redef_class_instance_LOCAL;
    Object Redo_saved_changes_LOCAL;
    Object Redraw_as_well_as_reformat_p_LOCAL;
    Object Reference_class_info_p_LOCAL;
    Object Reference_date_for_interval_encoding_LOCAL;
    Object Reference_serial_number_for_saved_detail_pane_description_LOCAL;
    Object Reference_structure_count_LOCAL;
    Object Reference_structures_originating_from_within_existence_predicate_LOCAL;
    Object Reformat_as_appropriate_qm_LOCAL;
    Object Refresh_all_windows_after_merging_qm_LOCAL;
    Object Refused_icp_listener_connections_LOCAL;
    Object Regexp_cons_counter_LOCAL;
    Object Regexp_preprocessing_parser_LOCAL;
    Object Region_1_info_LOCAL;
    Object Region_2_info_LOCAL;
    Object Region_3_info_LOCAL;
    Object Region_and_tile_x_offset_LOCAL;
    Object Region_and_tile_y_offset_LOCAL;
    Object Region_bounds_and_raster_count_LOCAL;
    Object Region_cons_counter_LOCAL;
    Object Region_invalidation_is_preferred_LOCAL;
    Object Region_x_max_qm_LOCAL;
    Object Region_x_offset_qm_LOCAL;
    Object Region_y_max_qm_LOCAL;
    Object Region_y_offset_qm_LOCAL;
    Object Registered_activities_symbol_array_LOCAL;
    Object Regular_expression_node_count_LOCAL;
    Object Regular_expression_node_for_set_of_characters_count_LOCAL;
    Object Regular_expression_node_for_single_character_count_LOCAL;
    Object Regular_expression_node_for_single_wild_character_count_LOCAL;
    Object Regular_expression_node_for_subexpression_count_LOCAL;
    Object Regular_expression_node_for_wild_characters_count_LOCAL;
    Object Regular_expression_parser_LOCAL;
    Object Regular_expression_tokenizer_LOCAL;
    Object Relation_class_description_LOCAL;
    Object Relation_instance_count_LOCAL;
    Object Relations_tag_list_LOCAL;
    Object Relative_time_pane_count_LOCAL;
    Object Releasing_kb_qm_LOCAL;
    Object Remaining_bytes_in_g2binary_data_LOCAL;
    Object Remaining_number_of_size_pieces_of_frame_LOCAL;
    Object Remaining_space_for_variable_size_pieces_of_frame_LOCAL;
    Object Remote_gsi_interface_list_LOCAL;
    Object Remote_procedure_call_count_LOCAL;
    Object Remote_procedure_declaration_class_description_LOCAL;
    Object Remote_procedure_identifier_array_LOCAL;
    Object Remote_procedure_identifier_count_LOCAL;
    Object Remote_procedure_item_passing_info_count_LOCAL;
    Object Remote_procedure_name_count_LOCAL;
    Object Remote_query_id_for_kb_recompile_LOCAL;
    Object Remote_value_is_binary_p_LOCAL;
    Object Remote_value_known_typetag_LOCAL;
    Object Remove_as_inferior_block_1_LOCAL;
    Object Remove_unused_labels_LOCAL;
    Object Rendezvous_successful_blocks_qm_LOCAL;
    Object Replacement_token_menu_button_spot_count_LOCAL;
    Object Report_filename_parsing_errors_in_development_p_LOCAL;
    Object Represented_frames_in_limbo_LOCAL;
    Object Required_definitions_LOCAL;
    Object Required_token_types_LOCAL;
    Object Resize_box_rubber_stamp_widget_LOCAL;
    Object Resize_box_spot_count_LOCAL;
    Object Resolving_definitional_name_conflicts_qm_LOCAL;
    Object Restrict_edits_to_modules_having_read_only_files_p_LOCAL;
    Object Result_end_time_system_variable_for_compute_trend_chart_time_bounds_LOCAL;
    Object Result_index_LOCAL;
    Object Result_of_ask_user_about_checking_pathname_out_for_editing_LOCAL;
    Object Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug_LOCAL;
    Object Result_timespan_system_variable_for_compute_trend_chart_time_bounds_LOCAL;
    Object Resumable_circular_node_count_LOCAL;
    Object Resumable_evaluation_sequence_node_count_LOCAL;
    Object Resumable_evaluation_sequence_node_mixin_count_LOCAL;
    Object Resumable_evaluation_structure_node_count_LOCAL;
    Object Resumable_history_node_count_LOCAL;
    Object Resumable_icp_node_mixin_count_LOCAL;
    Object Resumable_icp_object_mixin_count_LOCAL;
    Object Resumable_icp_read_ignore_p_LOCAL;
    Object Resumable_icp_state_LOCAL;
    Object Resumable_instance_node_mixin_count_LOCAL;
    Object Resumable_instance_or_complex_value_node_mixin_count_LOCAL;
    Object Resumable_list_node_mixin_count_LOCAL;
    Object Resumable_node_mixin_count_LOCAL;
    Object Resumable_object_list_node_count_LOCAL;
    Object Resumable_object_mixin_count_LOCAL;
    Object Resumable_object_node_count_LOCAL;
    Object Resumable_object_vector_node_count_LOCAL;
    Object Resumable_priority_of_gsi_data_service_LOCAL;
    Object Resumable_priority_of_gsi_rpc_service_LOCAL;
    Object Resumable_sequence_node_mixin_count_LOCAL;
    Object Resumable_value_list_node_count_LOCAL;
    Object Resumable_value_node_count_LOCAL;
    Object Resumable_value_vector_node_count_LOCAL;
    Object Resumable_vector_node_mixin_count_LOCAL;
    Object Return_from_ask_user_about_checking_pathname_out_for_editing_p_LOCAL;
    Object Return_from_breakpoint_task_LOCAL;
    Object Return_from_save_to_caller_for_continuation_qm_LOCAL;
    Object Return_statement_processed_qm_LOCAL;
    Object Return_to_waiting_for_cvs_p_LOCAL;
    Object Returned_values_description_LOCAL;
    Object Reusable_gensyms_LOCAL;
    Object Reverse_iso_latin1_special_character_code_map_LOCAL;
    Object Revert_marker_LOCAL;
    Object Revert_to_fuzzy_cache_p_LOCAL;
    Object Right_edge_in_window_of_graphic_element_LOCAL;
    Object Right_edge_of_draw_area_LOCAL;
    Object Right_edge_of_frame_LOCAL;
    Object Right_marker_for_cascading_menu_rubber_stamp_widget_LOCAL;
    Object Right_recursion_limit_list_LOCAL;
    Object Right_scroll_arrow_rubber_stamp_widget_LOCAL;
    Object Ring_buffer_for_history_time_LOCAL;
    Object Ring_buffer_queue_for_kfep_LOCAL;
    Object Ring_buffer_state_count_LOCAL;
    Object Ring_raster_for_graph_count_LOCAL;
    Object Role_and_domains_for_nth_element_expression_LOCAL;
    Object Role_caching_enabled_qm_LOCAL;
    Object Role_cons_counter_LOCAL;
    Object Role_names_and_local_names_for_runtime_items_LOCAL;
    Object Roman_character_map_LOCAL;
    Object Roman_font_special_character_code_map_LOCAL;
    Object Root_name_for_temp_file_LOCAL;
    Object Rotation_of_graphic_element_LOCAL;
    Object Row_LOCAL;
    Object Row_height_LOCAL;
    Object Row_maximum_LOCAL;
    Object Rpc_argument_count_override_qm_LOCAL;
    Object Rpc_argument_list_error_LOCAL;
    Object Rpc_object_arguments_to_run_or_schedule_qm_LOCAL;
    Object Rpc_throw_tag_LOCAL;
    Object Rule_certainty_var_LOCAL;
    Object Rule_class_description_LOCAL;
    Object Rule_expiration_var_LOCAL;
    Object Rule_instance_count_LOCAL;
    Object Rule_local_name_references_LOCAL;
    Object Ruling_for_dial_class_description_LOCAL;
    Object Ruling_for_meter_class_description_LOCAL;
    Object Run_traverse_kb_xml_object_type_LOCAL;
    Object Running_trace_function_p_LOCAL;
    Object Safe_to_access_attribute_display_update_interval_p_LOCAL;
    Object Sample_and_hold_plot_in_representation_update_p_LOCAL;
    Object Save_kb_state_for_system_procedure_save_LOCAL;
    Object Save_only_if_interrupting_qm_LOCAL;
    Object Saved_breakpoint_level_LOCAL;
    Object Saved_detail_pane_description_LOCAL;
    Object Saved_directories_for_module_truename_search_LOCAL;
    Object Saved_initial_status_LOCAL;
    Object Saved_local_var_vector_LOCAL;
    Object Saved_position_or_next_lower_thing_LOCAL;
    Object Saved_source_stepping_level_LOCAL;
    Object Saved_tracing_level_LOCAL;
    Object Saved_warning_level_LOCAL;
    Object Saving_context_count_LOCAL;
    Object Saving_kb_p_LOCAL;
    Object Saving_parameters_LOCAL;
    Object Saw_more_than_one_machine_authorization_qm_LOCAL;
    Object Scale_y_data_points_qm_LOCAL;
    Object Scaled_font_count_LOCAL;
    Object Scanning_subparts_of_block_LOCAL;
    Object Schedule_task_count_LOCAL;
    Object Scheduled_remote_procedure_start_count_LOCAL;
    Object Scheduler_enabled_qm_LOCAL;
    Object Scheduler_has_been_initialized_p_LOCAL;
    Object Scope_conses_LOCAL;
    Object Scrap_class_description_LOCAL;
    Object Scratch_add_item_to_workspace_LOCAL;
    Object Scratch_attribute_denotation_LOCAL;
    Object Scratch_character_rectangle_array_LOCAL;
    Object Scratch_custom_event_denotation_LOCAL;
    Object Scratch_incomplete_painting_action_LOCAL;
    Object Scratch_item_color_pattern_change_denotation_LOCAL;
    Object Scratch_item_event_denotation_LOCAL;
    Object Scratch_rectangle_region_LOCAL;
    Object Scratch_remove_item_from_workspace_LOCAL;
    Object Scratch_variable_value_denotation_LOCAL;
    Object Scratch_virtual_attribute_denotation_LOCAL;
    Object Scratchpad_raster_LOCAL;
    Object Scroll_bar_elevator_rubber_stamp_widget_LOCAL;
    Object Search_state_table_spot_count_LOCAL;
    Object Secret_return_value_LOCAL;
    Object See_also_for_warn_about_editing_item_LOCAL;
    Object Selected_file_progress_attributes_to_show_subsets_plist_LOCAL;
    Object Selected_module_load_request_attributes_to_show_subsets_plist_LOCAL;
    Object Selection_count_LOCAL;
    Object Selection_handle_icon_LOCAL;
    Object Selection_handle_spot_count_LOCAL;
    Object Selection_rectangle_state_count_LOCAL;
    Object Semi_open_category_map_LOCAL;
    Object Send_image_data_immediately_qm_LOCAL;
    Object Send_logbook_messages_to_console_p_LOCAL;
    Object Send_messages_to_console_p_LOCAL;
    Object Send_messages_to_logbook_p_LOCAL;
    Object Sending_i_am_alive_qm_LOCAL;
    Object Sending_resumable_object_count_LOCAL;
    Object Sensor_group_count_LOCAL;
    Object Sensor_groups_header_count_LOCAL;
    Object Separate_imminent_actions_p_LOCAL;
    Object Sequence_cons_counter_LOCAL;
    Object Serial_number_in_ok_file_LOCAL;
    Object Server_parameters_LOCAL;
    Object Service_workstations_LOCAL;
    Object Servicing_workstation_event_LOCAL;
    Object Servicing_workstation_qm_LOCAL;
    Object Set_of_all_component_kinds_LOCAL;
    Object Set_of_all_permanent_computation_style_LOCAL;
    Object Set_of_possible_phrases_count_LOCAL;
    Object Set_of_variables_to_simulation_evaluate_LOCAL;
    Object Shift_jis_transcoder_count_LOCAL;
    Object Shift_variant_for_cursor_movement_p_LOCAL;
    Object Short_duration_cv_count_LOCAL;
    Object Short_menus_qm_LOCAL;
    Object Short_representation_table_spot_count_LOCAL;
    Object Short_simple_gensym_string_counts_LOCAL;
    Object Short_simple_gensym_strings_LOCAL;
    Object Shortcut_bar_count_LOCAL;
    Object Show_deletions_in_xml_changes_p_LOCAL;
    Object Show_parameters_decoder_count_LOCAL;
    Object Show_procedure_invocation_hierarchy_on_debugger_pause_p_LOCAL;
    Object Show_stack_bytes_qm_LOCAL;
    Object Shredded_raster_count_LOCAL;
    Object Shunned_machine_ids_list_LOCAL;
    Object Shutdown_catch_tag_LOCAL;
    Object Shutdown_interval_for_disallowed_icp_connection_LOCAL;
    Object Shutdown_interval_for_disallowed_icp_connection_in_seconds_LOCAL;
    Object Sigfpe_LOCAL;
    Object Signal_code_registry_LOCAL;
    Object Simple_dialog_fill_text_p_LOCAL;
    Object Simple_dialog_plist_qm_LOCAL;
    Object Simple_dialog_title_qm_LOCAL;
    Object Simple_float_array_pool_memory_usage_LOCAL;
    Object Simple_for_image_plane_LOCAL;
    Object Simple_gensym_string_byte_use_counter_LOCAL;
    Object Simple_gensym_string_counter_LOCAL;
    Object Simple_item_spot_count_LOCAL;
    Object Simple_long_array_pool_memory_usage_LOCAL;
    Object Simple_string_stats_header_needed_LOCAL;
    Object Simple_string_stats_namestring_LOCAL;
    Object Simple_vector_pool_counts_LOCAL;
    Object Simple_vector_pool_memory_usage_LOCAL;
    Object Simulate_cons_counter_LOCAL;
    Object Simulate_proprietary_qm_LOCAL;
    Object Simulation_info_count_LOCAL;
    Object Simulation_no_value_LOCAL;
    Object Simulation_parameters_LOCAL;
    Object Simulation_procedure_completion_form_LOCAL;
    Object Simulation_subtable_class_description_LOCAL;
    Object Simulation_time_accumulator_LOCAL;
    Object Simulation_time_managed_float_LOCAL;
    Object Simulator_initialized_as_data_server_qm_LOCAL;
    Object Single_element_string_LOCAL;
    Object Single_escape_character_for_gensym_filenames_LOCAL;
    Object Size_of_cached_subsequence_for_resumable_history_LOCAL;
    Object Size_of_icon_slot_group_LOCAL;
    Object Skip_list_element_count_LOCAL;
    Object Skip_list_find_preds_LOCAL;
    Object Skip_list_find_succs_LOCAL;
    Object Slider_minimum_value_label_class_description_LOCAL;
    Object Slider_needle_class_description_LOCAL;
    Object Slider_readout_class_description_LOCAL;
    Object Slider_spot_count_LOCAL;
    Object Slot_alias_for_restrictions_LOCAL;
    Object Slot_component_descriptor_count_LOCAL;
    Object Slot_description_count_LOCAL;
    Object Slot_description_for_restrictions_LOCAL;
    Object Slot_description_for_slot_value_being_read_qm_LOCAL;
    Object Slot_name_for_write_frame_for_kb_LOCAL;
    Object Slot_pad_of_ok_file_reader_LOCAL;
    Object Slot_value_cons_counter_LOCAL;
    Object Slot_value_for_write_frame_for_kb_LOCAL;
    Object Slots_containing_circular_unnamed_simple_vectors_LOCAL;
    Object Slots_to_skip_saving_in_ok_files_LOCAL;
    Object Smoothed_subsecond_adjustment_LOCAL;
    Object Snapshot_invocation_info_count_LOCAL;
    Object Snapshot_of_block_count_LOCAL;
    Object Snapshots_of_related_blocks_LOCAL;
    Object Socket_count_LOCAL;
    Object Socket_output_buffer_count_LOCAL;
    Object Some_module_is_clear_text_p_LOCAL;
    Object Sorted_static_evaluate_role_dispatchers_LOCAL;
    Object Source_code_control_grammar_is_present_p_LOCAL;
    Object Source_code_control_is_enabled_by_default_LOCAL;
    Object Source_code_control_support_enabled_p_LOCAL;
    Object Source_designations_from_explicit_iteration_forms_LOCAL;
    Object Source_nupec_synchronization_count_LOCAL;
    Object Source_stepping_level_LOCAL;
    Object Sparse_array_count_LOCAL;
    Object Sparse_known_pathnames_list_LOCAL;
    Object Spawn_command_line_process_failure_LOCAL;
    Object Special_globally_known_references_LOCAL;
    Object Special_slot_names_for_memory_walk_LOCAL;
    Object Special_variable_for_use_value_macro_LOCAL;
    Object Specific_structure_for_current_workstation_context_LOCAL;
    Object Specified_kfep_index_filename_qm_LOCAL;
    Object Specified_kfep_kojin_filename_qm_LOCAL;
    Object Specified_kfep_main_filename_qm_LOCAL;
    Object Speedup_tagname_string_LOCAL;
    Object Speedup_tagname_string_index_LOCAL;
    Object Spinner_cv_count_LOCAL;
    Object Spot_count_LOCAL;
    Object Stack_change_cons_counter_LOCAL;
    Object Stack_cons_counter_LOCAL;
    Object Stack_eval_qm_LOCAL;
    Object Stack_expiration_LOCAL;
    Object Stack_frame_vars_ok_in_procedure_qm_LOCAL;
    Object Stack_instructions_LOCAL;
    Object Stack_node_count_LOCAL;
    Object Stack_node_instruction_count_LOCAL;
    Object Stack_nodes_to_reclaim_LOCAL;
    Object Stack_of_current_part_descriptions_LOCAL;
    Object Stack_of_deferred_notification_strings_LOCAL;
    Object Stack_of_slot_value_changes_LOCAL;
    Object Standard_8_bit_non_graphic_characters_skip_spec_LOCAL;
    Object Standard_gensym_color_alist_LOCAL;
    Object Star_character_index_LOCAL;
    Object Star_character_index_in_string_to_insert_qm_LOCAL;
    Object Star_character_index_of_change_qm_LOCAL;
    Object Star_character_index_past_deletion_qm_LOCAL;
    Object Star_current_indentation_LOCAL;
    Object Star_explicit_paragraph_or_newline_qm_LOCAL;
    Object Star_line_buffer_LOCAL;
    Object Star_line_buffer_fill_pointer_LOCAL;
    Object Star_line_buffer_limit_LOCAL;
    Object Star_line_index_LOCAL;
    Object Star_line_index_of_change_qm_LOCAL;
    Object Star_line_index_past_deletion_qm_LOCAL;
    Object Star_line_length_LOCAL;
    Object Star_lost_space_at_end_of_line_LOCAL;
    Object Star_next_text_tail_qm_LOCAL;
    Object Star_string_to_insert_qm_LOCAL;
    Object Star_text_line_LOCAL;
    Object Star_text_line_is_simple_qm_LOCAL;
    Object Star_text_string_to_insert_is_simple_qm_LOCAL;
    Object Star_this_text_tail_qm_LOCAL;
    Object State_transition_count_LOCAL;
    Object Statement_class_description_LOCAL;
    Object Static_attributes_LOCAL;
    Object Status_bar_count_LOCAL;
    Object Status_bar_pane_count_LOCAL;
    Object Status_pane_spot_count_LOCAL;
    Object Stepper_of_scroll_bar_spot_count_LOCAL;
    Object Strange_cons_LOCAL;
    Object Streams_cons_counter_LOCAL;
    Object Strict_subcategory_info_count_LOCAL;
    Object Strict_subcategory_info_last_category_1_LOCAL;
    Object Strict_subcategory_info_last_category_2_LOCAL;
    Object Strict_subcategory_info_last_result_LOCAL;
    Object Strict_subcategory_infos_exist_p_LOCAL;
    Object String_allocations_until_next_report_LOCAL;
    Object String_chars_to_print_LOCAL;
    Object String_for_returning_floats_LOCAL;
    Object String_pool_cons_counter_LOCAL;
    Object String_pool_number_to_malloc_LOCAL;
    Object String_reclaims_until_next_report_LOCAL;
    Object String_report_frequency_LOCAL;
    Object Stringw_should_not_cons_p_LOCAL;
    Object Structure_being_reclaimed_LOCAL;
    Object Structure_slot_not_bound_LOCAL;
    Object Structure_specs_allow_unknown_slots_p_LOCAL;
    Object Stub_length_to_use_qm_LOCAL;
    Object Sub_profiling_structure_count_LOCAL;
    Object Subcommand_menu_button_spot_count_LOCAL;
    Object Subcommand_state_count_LOCAL;
    Object Subframe_depth_LOCAL;
    Object Subordinate_text_box_class_description_LOCAL;
    Object Subpart_defaults_LOCAL;
    Object Subpart_exceptions_LOCAL;
    Object Subparts_LOCAL;
    Object Subtract_arrays_instead_qm_LOCAL;
    Object Subworkspace_currently_being_deleted_qm_LOCAL;
    Object Success_of_ok_file_reader_qm_LOCAL;
    Object Superior_frame_being_cloned_qm_LOCAL;
    Object Superior_frame_for_restrictions_frame_qm_LOCAL;
    Object Superior_frame_for_restrictions_superior_qm_LOCAL;
    Object Supported_combining_classes_LOCAL;
    Object Supported_control_actions_by_id_LOCAL;
    Object Supported_control_actions_by_symbol_LOCAL;
    Object Supported_dialog_component_types_LOCAL;
    Object Supported_ok_file_format_version_LOCAL;
    Object Supports_dialog_component_with_font_LOCAL;
    Object Supports_font_in_grid_view_LOCAL;
    Object Supports_transparent_color_index_LOCAL;
    Object Suppress_consistency_analysis_warnings_notes_qm_LOCAL;
    Object Suppress_notification_for_kb_save_qm_LOCAL;
    Object Suppress_scrolling_into_view_global_flag_qm_LOCAL;
    Object Suppress_updates_to_name_boxes_LOCAL;
    Object Suppress_updating_of_self_representations_qm_LOCAL;
    Object Suppress_updating_of_slot_value_representations_qm_LOCAL;
    Object Suppress_use_of_stack_of_slot_value_changes_p_LOCAL;
    Object Suppress_warning_message_header_qm_LOCAL;
    Object Symbol_array_class_description_LOCAL;
    Object Symbol_list_class_description_LOCAL;
    Object Symbol_tree_count_LOCAL;
    Object Symbolic_parameter_class_description_LOCAL;
    Object Symbolic_variable_class_description_LOCAL;
    Object Symbols_not_to_add_to_semi_open_category_directories_LOCAL;
    Object Synchronous_model_queue_LOCAL;
    Object Sysproc_cons_counter_LOCAL;
    Object Sysproc_continuation_table_LOCAL;
    Object System_class_method_tables_processed_qm_LOCAL;
    Object System_defined_rpcs_LOCAL;
    Object System_has_aborted_LOCAL;
    Object System_has_paused_LOCAL;
    Object System_is_running_LOCAL;
    Object System_item_class_description_LOCAL;
    Object System_quality_from_last_kb_read_LOCAL;
    Object System_revision_from_last_kb_read_LOCAL;
    Object System_rpc_count_LOCAL;
    Object System_rpc_instance_count_LOCAL;
    Object System_slot_accessor_LOCAL;
    Object System_statistics_writers_LOCAL;
    Object System_tables_read_for_this_module_LOCAL;
    Object System_version_from_kb_being_read_LOCAL;
    Object System_version_from_last_kb_read_LOCAL;
    Object System_version_of_current_gensym_product_line_LOCAL;
    Object System_window_LOCAL;
    Object System_window_title_and_info_text_string_qm_LOCAL;
    Object Systems_in_gensym_product_line_LOCAL;
    Object Systemtables_are_initialized_p_LOCAL;
    Object Systemtables_fixups_LOCAL;
    Object T2_dialog_result_alist_LOCAL;
    Object T2_nonce_data_count_LOCAL;
    Object T2_nonce_table_LOCAL;
    Object Tab_length_for_counter_report_LOCAL;
    Object Table_background_spot_count_LOCAL;
    Object Table_class_description_LOCAL;
    Object Table_header_spot_count_LOCAL;
    Object Table_menu_choices_LOCAL;
    Object Table_representation_update_schedule_LOCAL;
    Object Table_spot_count_LOCAL;
    Object Table_to_map_generic_method_id_to_generic_method_name_LOCAL;
    Object Table_to_map_structure_id_to_method_name_LOCAL;
    Object Tabular_function_class_description_LOCAL;
    Object Tabular_function_of_1_arg_class_description_LOCAL;
    Object Tabular_view_action_LOCAL;
    Object Tabular_view_count_LOCAL;
    Object Target_nupec_synchronization_count_LOCAL;
    Object Task_for_display_of_simulation_time_LOCAL;
    Object Task_scheduled_to_process_gsi_values_qm_LOCAL;
    Object Task_to_process_g2ds_values_LOCAL;
    Object Task_to_process_gsi_interfaces_LOCAL;
    Object Task_to_process_gsi_values_LOCAL;
    Object Task_to_run_service_workstations_final_LOCAL;
    Object Task_to_warn_user_of_previously_aborted_g2_LOCAL;
    Object Tcp_ip_port_offset_for_foreign_images_LOCAL;
    Object Tcp_listener_port_number_LOCAL;
    Object Tcp_socket_count_LOCAL;
    Object Tcpip_external_foreign_image_prologue_LOCAL;
    Object Telewindows_authorized_products_LOCAL;
    Object Telewindows_license_level_LOCAL;
    Object Telewindows_screen_utilization_LOCAL;
    Object Temporary_constant_count_LOCAL;
    Object Temporary_file_count_LOCAL;
    Object Temporary_g2binary_file_symbol_indices_LOCAL;
    Object Temporary_name_number_1_LOCAL;
    Object Temporary_name_number_2_LOCAL;
    Object Temporary_string_buffer_LOCAL;
    Object Temporary_workspace_class_description_LOCAL;
    Object Terminate_kb_save_stream_error_message_qm_LOCAL;
    Object Test_removal_of_unsigned_vector_16_LOCAL;
    Object Testing_parsing_context_locally_p_LOCAL;
    Object Text_array_class_description_LOCAL;
    Object Text_box_class_description_LOCAL;
    Object Text_box_cv_count_LOCAL;
    Object Text_box_spot_count_LOCAL;
    Object Text_conversion_style_for_transcoder_being_created_LOCAL;
    Object Text_inserter_spot_count_LOCAL;
    Object Text_line_for_line_of_text_of_graphic_element_LOCAL;
    Object Text_list_class_description_LOCAL;
    Object Text_marking_state_count_LOCAL;
    Object Text_of_definition_being_compiled_LOCAL;
    Object Text_parameter_class_description_LOCAL;
    Object Text_region_class_description_LOCAL;
    Object Text_representation_of_our_ok_object_LOCAL;
    Object Text_sequence_count_LOCAL;
    Object Text_spot_count_LOCAL;
    Object Text_time_stamp_seconds_LOCAL;
    Object Text_tokenization_state_count_LOCAL;
    Object Text_value_LOCAL;
    Object Text_value_from_postponed_erase_LOCAL;
    Object Text_variable_class_description_LOCAL;
    Object Text_xml_checksum_LOCAL;
    Object Tformat_fresh_line_is_newline_p_LOCAL;
    Object The_denotation_conversion_buffer_LOCAL;
    Object The_g2_defstruct_package_LOCAL;
    Object The_java_symbol_table_LOCAL;
    Object The_only_dynamic_computation_style_LOCAL;
    Object The_polygon_data_buffer_LOCAL;
    Object The_representation_handle_hashtable_LOCAL;
    Object The_transform_LOCAL;
    Object The_type_description_of_t_LOCAL;
    Object There_exists_p_LOCAL;
    Object There_is_a_current_kb_qm_LOCAL;
    Object Things_that_affect_this_formula_LOCAL;
    Object Thrashing_cost_update_interval_LOCAL;
    Object Thrashing_ratio_ring_buffer_count_LOCAL;
    Object Throws_from_breakpoints_are_possible_LOCAL;
    Object Tick_mark_part_to_draw_LOCAL;
    Object Tickmark_label_char_width_LOCAL;
    Object Tickmark_label_min_height_LOCAL;
    Object Tickmark_label_min_width_LOCAL;
    Object Tightest_end_of_loop_tag_LOCAL;
    Object Tightness_of_text_spot_for_click_to_edit_LOCAL;
    Object Tiled_raster_count_LOCAL;
    Object Tiling_pattern_count_LOCAL;
    Object Time_of_day_cv_count_LOCAL;
    Object Time_of_frame_edit_base_time_LOCAL;
    Object Time_of_last_call_to_set_user_password_LOCAL;
    Object Time_of_last_expiration_check_LOCAL;
    Object Time_of_last_synthetic_motion_event_qm_LOCAL;
    Object Time_of_last_thrashing_cost_update_LOCAL;
    Object Time_of_last_uuid_LOCAL;
    Object Time_slice_expired_p_LOCAL;
    Object Time_slice_start_time_LOCAL;
    Object Time_to_check_network_events_LOCAL;
    Object Time_used_to_adjust_histories_qm_LOCAL;
    Object Timestamp_cons_counter_LOCAL;
    Object Timing_parameters_LOCAL;
    Object Title_bar_spot_count_LOCAL;
    Object Token_cons_counter_LOCAL;
    Object Token_menu_button_spot_count_LOCAL;
    Object Token_sequence_location_plist_LOCAL;
    Object Token_stack_cons_counter_LOCAL;
    Object Tokenize_with_editing_context_p_LOCAL;
    Object Top_edge_in_window_of_graphic_element_LOCAL;
    Object Top_edge_of_draw_area_LOCAL;
    Object Top_edge_of_frame_LOCAL;
    Object Top_level_error_catcher_tag_LOCAL;
    Object Top_level_error_seen_LOCAL;
    Object Top_level_reference_tree_LOCAL;
    Object Top_level_state_count_LOCAL;
    Object Top_scroll_arrow_rubber_stamp_widget_LOCAL;
    Object Total_foreign_image_connection_checkup_interval_in_ms_LOCAL;
    Object Total_items_in_file_LOCAL;
    Object Total_length_of_current_gensym_string_LOCAL;
    Object Total_length_of_current_wide_string_LOCAL;
    Object Trace_compiled_function_execution_LOCAL;
    Object Trace_drawing_for_build_LOCAL;
    Object Trace_filename_parsing_p_LOCAL;
    Object Trace_image_planes_p_LOCAL;
    Object Trace_images_LOCAL;
    Object Trace_instruction_execution_LOCAL;
    Object Trace_messages_within_extent_of_rule_LOCAL;
    Object Trace_parsing_context_p_LOCAL;
    Object Trace_parsing_context_tokenizing_p_LOCAL;
    Object Trace_reshape_events_LOCAL;
    Object Trace_skip_data_service_i_am_alive_messages_p_LOCAL;
    Object Trace_system_calls_p_LOCAL;
    Object Trace_validate_p_LOCAL;
    Object Trace_workstation_events_LOCAL;
    Object Tracing_in_events_modules_p_LOCAL;
    Object Tracing_message_level_LOCAL;
    Object Tracked_items_call_depth_LOCAL;
    Object Tracked_items_call_vector_table_LOCAL;
    Object Tracking_items_grammar_installed_p_LOCAL;
    Object Tracking_items_p_LOCAL;
    Object Transcode_text_conversion_style_count_LOCAL;
    Object Transcoder_count_LOCAL;
    Object Transfer_dragging_state_count_LOCAL;
    Object Transfer_in_progress_LOCAL;
    Object Transform_image_operation_hint_LOCAL;
    Object Transient_connection_error_qm_LOCAL;
    Object Transients_to_delete_LOCAL;
    Object Transmitted_variable_fill_icp_buffers_LOCAL;
    Object Traverse_kb_queued_nodes_LOCAL;
    Object Traverse_kb_queued_nodes_tail_LOCAL;
    Object Traversing_kb_attribute_LOCAL;
    Object Traversing_xml_object_p_LOCAL;
    Object Tree_ordering_cons_counter_LOCAL;
    Object Tree_view_count_LOCAL;
    Object Tree_view_node_count_LOCAL;
    Object Trend_chart_layout_bottom_LOCAL;
    Object Trend_chart_layout_grid_LOCAL;
    Object Trend_chart_layout_left_LOCAL;
    Object Trend_chart_layout_parent_LOCAL;
    Object Trend_chart_layout_relative_time_pane_LOCAL;
    Object Trend_chart_layout_right_LOCAL;
    Object Trend_chart_layout_top_LOCAL;
    Object Trend_chart_pane_count_LOCAL;
    Object Trend_chart_spot_count_LOCAL;
    Object Trif_block_value_alist_LOCAL;
    Object True_value_update_recipient_class_description_LOCAL;
    Object Truth_value_array_class_description_LOCAL;
    Object Truth_value_list_class_description_LOCAL;
    Object Tw_deferred_actions_LOCAL;
    Object Tw_evaluate_trace_level_LOCAL;
    Object Tw_expiration_check_interval_LOCAL;
    Object Tw_source_debug_p_LOCAL;
    Object Twrite_control_as_ctrl_LOCAL;
    Object Twrite_fixnum_buffer_LOCAL;
    Object Type_at_type_failure_LOCAL;
    Object Type_description_count_LOCAL;
    Object Type_in_box_class_description_LOCAL;
    Object Type_in_box_spot_count_LOCAL;
    Object Type_in_text_box_class_description_LOCAL;
    Object Type_of_current_window_LOCAL;
    Object Type_of_current_workstation_context_LOCAL;
    Object Type_of_current_workstation_window_LOCAL;
    Object Type_of_file_being_read_LOCAL;
    Object Ucs_4_to_utf_8_1st_octet_table_LOCAL;
    Object Ui_callback_count_LOCAL;
    Object Ui_callbacks_LOCAL;
    Object Ui_client_interface_in_which_to_launch_recompilation_qm_LOCAL;
    Object Ui_client_interface_saved_icp_socket_list_LOCAL;
    Object Ui_client_interface_saved_session_list_LOCAL;
    Object Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing_LOCAL;
    Object Ui_client_interfaces_for_timeout_of_source_code_control_LOCAL;
    Object Ui_command_context_LOCAL;
    Object Unbound_value_for_ok_reader_LOCAL;
    Object Unevaluated_expression_LOCAL;
    Object Unicode_block_count_LOCAL;
    Object Unicode_byte_swapped_transcoder_count_LOCAL;
    Object Unicode_index_to_slavic_font_direct_index_map_LOCAL;
    Object Unicode_offset_for_gensym_cyrillic_LOCAL;
    Object Unicode_offset_for_gensym_general_punctuation_LOCAL;
    Object Unicode_offset_for_gensym_letterlike_symbol_LOCAL;
    Object Unicode_to_gb_2312_map_LOCAL;
    Object Unicode_to_jis_x_0208_map_LOCAL;
    Object Unicode_to_ks_c_5601_map_LOCAL;
    Object Unicode_transcoder_count_LOCAL;
    Object Unicode_ucs_2_transcoder_count_LOCAL;
    Object Uninteresting_block_spot_count_LOCAL;
    Object Unique_temp_filename_LOCAL;
    Object Unique_value_roles_LOCAL;
    Object Units_of_measure_declaration_class_description_LOCAL;
    Object Unix_command_callback_function_LOCAL;
    Object Unix_command_line_argument_count_LOCAL;
    Object Unix_command_line_arguments_LOCAL;
    Object Unix_command_line_arguments_as_text_strings_LOCAL;
    Object Unix_time_offset_for_encoding_LOCAL;
    Object Unix_time_offset_was_computed_qm_LOCAL;
    Object Unknown_references_LOCAL;
    Object Unread_char_of_ok_file_reader_qm_LOCAL;
    Object Unrecoverable_error_p_LOCAL;
    Object Unused_foreign_image_indices_LOCAL;
    Object Unused_known_offsets_LOCAL;
    Object Uo_memory_usage_information_hash_table_LOCAL;
    Object Update_before_loading_by_default_LOCAL;
    Object Update_images_in_xor_overlay_p_LOCAL;
    Object Update_menu_values_LOCAL;
    Object Updated_only_qm_LOCAL;
    Object Updated_users_list_LOCAL;
    Object Uri_reference_count_LOCAL;
    Object Use_current_time_for_next_uuid_LOCAL;
    Object Use_directory_lists_for_bootstrapping_qm_LOCAL;
    Object Use_interpreter_debug_format_LOCAL;
    Object Use_jit_p_LOCAL;
    Object Use_minimal_time_slice_for_continue_current_kb_save_p_LOCAL;
    Object Use_new_message_group_for_send_icp_enlarge_index_space_p_LOCAL;
    Object Use_scaleable_set_widths_qm_LOCAL;
    Object Use_telewindows_clogging_mechanism_p_LOCAL;
    Object Use_type_info_LOCAL;
    Object Used_positional_command_line_argument_default_LOCAL;
    Object Used_remote_spawn_indices_qm_LOCAL;
    Object Useful_machine_authorization_info_LOCAL;
    Object User_defined_default_error_handling_procedure_fsn_LOCAL;
    Object User_defined_default_error_handling_procedure_qm_LOCAL;
    Object User_defined_logbook_handling_procedure_fsn_LOCAL;
    Object User_defined_logbook_handling_procedure_qm_LOCAL;
    Object User_defined_message_board_handling_procedure_fsn_LOCAL;
    Object User_defined_message_board_handling_procedure_qm_LOCAL;
    Object User_menu_choice_class_description_LOCAL;
    Object User_mode_alias_count_LOCAL;
    Object User_mouse_tracking_state_count_LOCAL;
    Object User_notified_of_uuid_uniqueness_problem_p_LOCAL;
    Object User_overridable_connection_slots_LOCAL;
    Object User_overridable_g2_array_slots_LOCAL;
    Object User_overridable_g2_list_slots_LOCAL;
    Object User_overridable_message_slots_LOCAL;
    Object User_overridable_object_slots_LOCAL;
    Object User_overridable_parameter_slots_LOCAL;
    Object User_overridable_variable_slots_LOCAL;
    Object User_package_in_this_lisp_LOCAL;
    Object User_random_seed_qm_LOCAL;
    Object Using_pending_write_reference_list_LOCAL;
    Object Using_temporary_g2binary_file_symbol_indices_p_LOCAL;
    Object Utf_7_transcoder_count_LOCAL;
    Object Utf_8_transcoder_count_LOCAL;
    Object Utf_g_ascii_as_much_as_possible_conversion_style_LOCAL;
    Object Utf_g_ascii_as_much_as_possible_transcoder_count_LOCAL;
    Object Utf_g_transcoder_count_LOCAL;
    Object Uuid_block_count_LOCAL;
    Object Uuid_block_hash_table_LOCAL;
    Object Uuid_for_next_frame_qm_LOCAL;
    Object Uuid_hash_block_table_for_merge_kb_LOCAL;
    Object Uuid_time_b0_LOCAL;
    Object Uuid_time_b1_LOCAL;
    Object Uuid_time_b2_LOCAL;
    Object Uuid_time_b3_LOCAL;
    Object Uuid_xml_checksum_LOCAL;
    Object Valid_token_actions_LOCAL;
    Object Value_array_class_description_LOCAL;
    Object Value_at_type_failure_LOCAL;
    Object Value_list_class_description_LOCAL;
    Object Value_xml_checksum_LOCAL;
    Object Var_vector_caching_backpatch_locations_LOCAL;
    Object Var_vector_decaching_backpatch_locations_LOCAL;
    Object Variable_class_description_LOCAL;
    Object Variable_group_update_structure_count_LOCAL;
    Object Variable_is_at_bottom_of_stack_qm_LOCAL;
    Object Variable_or_parameter_class_description_LOCAL;
    Object Variable_simulation_runtime_structure_count_LOCAL;
    Object Variables_that_did_not_have_values_LOCAL;
    Object Vars_settable_at_runtime_LOCAL;
    Object Vector_of_oversized_simple_float_array_pools_LOCAL;
    Object Vector_of_oversized_simple_vector_pools_LOCAL;
    Object Vector_of_simple_float_array_pools_LOCAL;
    Object Vector_of_simple_long_array_pools_LOCAL;
    Object Vector_of_simple_vector_pools_LOCAL;
    Object Vector_pool_cons_counter_LOCAL;
    Object Verbosity_level_LOCAL;
    Object Version_control_parameters_LOCAL;
    Object Vertical_axis_range_LOCAL;
    Object Vertical_grid_line_color_qm_LOCAL;
    Object Vertical_grid_line_spacing_LOCAL;
    Object Vertical_grid_line_width_LOCAL;
    Object Virtual_attribute_class_instance_header_type_of_slot_LOCAL;
    Object Virtual_attribute_count_LOCAL;
    Object Virtual_attributes_not_local_to_a_class_LOCAL;
    Object Vms_directory_filenames_can_dangle_p_LOCAL;
    Object Wait_interval_before_killing_foreign_process_LOCAL;
    Object Walking_menus_state_count_LOCAL;
    Object Warmboot_cons_counter_LOCAL;
    Object Warmboot_current_time_LOCAL;
    Object Warmboot_simulated_time_LOCAL;
    Object Warmbooting_qm_LOCAL;
    Object Warmbooting_with_catch_up_qm_LOCAL;
    Object Warning_message_level_LOCAL;
    Object Weighting_factors_for_thrashing_ratio_ring_buffers_LOCAL;
    Object Whitespace_characters_LOCAL;
    Object Whitespace_wide_characters_LOCAL;
    Object Wide_string_text_sequence_count_LOCAL;
    Object Wide_twrite_fixnum_buffer_LOCAL;
    Object Widget_pending_state_count_LOCAL;
    Object Width_for_change_size_qm_LOCAL;
    Object Window_for_bitmap_for_gsi_LOCAL;
    Object Window_instigating_this_rule_instance_qm_LOCAL;
    Object With_extreme_edges_LOCAL;
    Object With_icp_buffer_coelescing_scope_qm_LOCAL;
    Object Within_activate_for_kb_workspace_LOCAL;
    Object Within_backward_chaining_task_LOCAL;
    Object Within_delete_frame_scope_qm_LOCAL;
    Object Within_managed_object_scope_LOCAL;
    Object Within_simulate_until_consistent_with_gensym_time_LOCAL;
    Object Within_simulator_for_stack_error_qm_LOCAL;
    Object Within_writing_procedure_invocation_p_LOCAL;
    Object Word_spacing_for_line_of_text_of_graphic_element_LOCAL;
    Object Working_on_annotated_frame_LOCAL;
    Object Working_on_chart_LOCAL;
    Object Working_on_drawing_LOCAL;
    Object Working_on_drawing_image_plane_LOCAL;
    Object Working_on_drawing_pane_LOCAL;
    Object Working_on_drawing_schedule_LOCAL;
    Object Working_on_drawing_workspace_LOCAL;
    Object Working_on_lexical_computation_of_frame_LOCAL;
    Object Working_on_new_table_LOCAL;
    Object Working_on_variables_that_need_simulated_values_stack_qm_LOCAL;
    Object Workspace_background_spot_count_LOCAL;
    Object Workspace_class_description_LOCAL;
    Object Workspace_dock_spot_count_LOCAL;
    Object Workspace_for_current_draw_document_qm_LOCAL;
    Object Workspace_image_plane_per_window_LOCAL;
    Object Workspace_invalidation_handling_event_type_queue_LOCAL;
    Object Workspace_invalidation_handling_fsn_queue_LOCAL;
    Object Workspace_invalidation_handling_procedure_fsn_qm_LOCAL;
    Object Workspace_invalidation_handling_procedure_qm_LOCAL;
    Object Workspace_invalidation_handling_window_queue_LOCAL;
    Object Workspace_invalidation_handling_workspace_queue_LOCAL;
    Object Workspace_menu_choices_LOCAL;
    Object Workspace_name_box_class_description_LOCAL;
    Object Workspace_region_count_LOCAL;
    Object Workspace_view_count_LOCAL;
    Object Workstation_context_count_LOCAL;
    Object Workstation_context_frame_count_LOCAL;
    Object Workstation_context_with_selection_focus_count_LOCAL;
    Object Workstation_count_LOCAL;
    Object Workstation_event_count_LOCAL;
    Object Workstation_in_which_to_launch_recompilation_qm_LOCAL;
    Object Workstation_with_image_plane_being_refreshed_LOCAL;
    Object Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing_LOCAL;
    Object Workstations_with_their_stacks_for_timeout_of_source_code_control_LOCAL;
    Object Wrap_conservatively_LOCAL;
    Object Wrapper_references_for_left_side_of_formula_qm_LOCAL;
    Object Write_all_byte_code_bodies_for_kb_p_LOCAL;
    Object Write_annotations_indent_LOCAL;
    Object Write_annotations_part_pattern_stack_LOCAL;
    Object Write_annotations_suppress_the_p_LOCAL;
    Object Write_checksums_in_xml_file_p_LOCAL;
    Object Write_compound_slots_parseably_qm_LOCAL;
    Object Write_console_p_LOCAL;
    Object Write_diffs_after_saving_clear_text_p_LOCAL;
    Object Write_floats_accurately_p_LOCAL;
    Object Write_initial_icp_version_info_p_LOCAL;
    Object Write_proprietary_package_while_saving_xml_kb_LOCAL;
    Object Write_remote_value_items_kind_LOCAL;
    Object Write_strings_parsably_qm_LOCAL;
    Object Write_symbols_in_lower_case_qm_LOCAL;
    Object Write_symbols_parsably_qm_LOCAL;
    Object Write_value_of_gsi_item_p_LOCAL;
    Object Write_xml_attribute_change_old_value_p_LOCAL;
    Object Write_xml_object_items_collected_LOCAL;
    Object Writing_annotations_LOCAL;
    Object Writing_g2_rdf_file_p_LOCAL;
    Object Writing_icp_message_group_LOCAL;
    Object Writing_resumable_icp_messages_p_LOCAL;
    Object Writing_xml_cdata_p_LOCAL;
    Object Writing_xml_p_LOCAL;
    Object Wrote_first_annotation_flag_LOCAL;
    Object Ws_representation_slots_to_update_LOCAL;
    Object Ws_representation_type_count_LOCAL;
    Object X11_preinitialized_p_LOCAL;
    Object X_data_min_set_qm_LOCAL;
    Object X_debugging_on_LOCAL;
    Object X_in_window_for_finding_object_near_mouse_LOCAL;
    Object X_in_window_of_graphic_element_LOCAL;
    Object X_scale_of_graphic_element_LOCAL;
    Object X_value_on_graph_LOCAL;
    Object Xml_checksums_enabled_p_LOCAL;
    Object Xml_namespace_count_LOCAL;
    Object Xml_namespace_list_count_LOCAL;
    Object Xml_nil_LOCAL;
    Object Xml_node_count_LOCAL;
    Object Xml_node_list_count_LOCAL;
    Object Xml_object_changes_LOCAL;
    Object Xml_output_buffer_LOCAL;
    Object Xml_output_position_LOCAL;
    Object Xml_output_stream_LOCAL;
    Object Xml_structure_count_LOCAL;
    Object Xml_structures_extent_LOCAL;
    Object Xsd_datatypes_xml_namespace_prefix_LOCAL;
    Object Y_in_window_for_finding_object_near_mouse_LOCAL;
    Object Y_in_window_of_graphic_element_LOCAL;
    Object Y_scale_of_graphic_element_LOCAL;
    Object Year_at_compilation_time_LOCAL;
    Object ab_Dummy_var_LOCAL;
};

struct SI_Tls_count {
    INCLUDE_SI_SPECIAL(short, COUNT);
    short A_list_of_classes_with_instances_in_modules_that_do_not_require_them_COUNT;
    short A_list_of_relations_with_related_items_in_modules_that_do_not_require_them_COUNT;
    short Ab_package_1_COUNT;
    short Ab_system_pathname_COUNT;
    short Abbreviate_frame_notes_p_COUNT;
    short Abbreviate_wide_strings_for_legibility_COUNT;
    short Abort_file_written_p_COUNT;
    short Abort_for_icp_catcher_qm_COUNT;
    short Abort_level_0_tag_COUNT;
    short Absolutely_prohibited_restriction_set_COUNT;
    short Absolutely_selected_choice_qm_COUNT;
    short Accept_any_version_component_p_COUNT;
    short Access_direction_slot_description_COUNT;
    short Access_error_count_COUNT;
    short Action_button_class_description_COUNT;
    short Action_templates_COUNT;
    short Active_icp_sockets_COUNT;
    short Activities_currently_being_converted_to_xml_COUNT;
    short Activities_currently_being_laid_out_COUNT;
    short Activity_class_code_vector_COUNT;
    short Actual_arg_COUNT;
    short Add_as_item_referring_to_name_qm_COUNT;
    short Adding_from_graph_rendering_p_COUNT;
    short Additional_related_blocks_COUNT;
    short Adjustable_gensym_string_byte_use_counter_COUNT;
    short Adjustable_gensym_string_counter_COUNT;
    short Adjustable_gensym_string_counts_COUNT;
    short Adjustable_gensym_strings_COUNT;
    short Align_selection_command_operations_COUNT;
    short Alist_of_dialog_mappings_COUNT;
    short Alist_of_local_names_and_role_names_COUNT;
    short All_ab_font_names_COUNT;
    short All_branch_destinations_possible_COUNT;
    short All_classes_for_cached_class_description_node_attributes_COUNT;
    short All_classes_for_cached_class_description_node_attributes_for_external_definition_COUNT;
    short All_classes_for_indirectly_referenced_class_COUNT;
    short All_colors_COUNT;
    short All_command_line_keyword_arguments_COUNT;
    short All_computation_instances_above_breakpoint_COUNT;
    short All_cons_pools_COUNT;
    short All_cycles_found_so_far_in_module_hierarchy_COUNT;
    short All_directory_namestrings_in_directory_of_names_COUNT;
    short All_external_foreign_function_images_qm_COUNT;
    short All_file_namestrings_in_directory_of_names_COUNT;
    short All_foreign_function_images_qm_COUNT;
    short All_formats_in_module_COUNT;
    short All_frames_with_simple_debugging_names_COUNT;
    short All_g2gl_operators_COUNT;
    short All_gensym_pathnames_containing_open_streams_COUNT;
    short All_gesture_instruction_names_COUNT;
    short All_image_data_structures_COUNT;
    short All_index_space_names_COUNT;
    short All_known_command_line_plist_elements_COUNT;
    short All_known_file_systems_COUNT;
    short All_menu_heading_format_names_COUNT;
    short All_module_frame_notes_for_workspaces_COUNT;
    short All_permanently_changed_things_are_marked_COUNT;
    short All_region_info_COUNT;
    short All_signal_handlers_registered_p_COUNT;
    short All_supported_2022_escape_sequences_COUNT;
    short All_systems_COUNT;
    short All_unicode_block_names_COUNT;
    short All_valid_superior_test_functions_COUNT;
    short All_virtual_attributes_COUNT;
    short All_write_locks_COUNT;
    short All_xml_checksums_COUNT;
    short Allocated_byte_vector_16_vectors_COUNT;
    short Allocated_strings_reported_COUNT;
    short Allow_activation_of_name_boxes_p_COUNT;
    short Allow_activation_of_table_items_p_COUNT;
    short Allow_comparison_of_slot_value_to_parse_result_COUNT;
    short Allow_debugger_pause_COUNT;
    short Allow_extensionless_dos_filenames_p_COUNT;
    short Allow_in_line_designations_qm_COUNT;
    short Allow_inline_evaluate_role_instructions_p_COUNT;
    short Allow_internal_procedure_environment_printing_qm_COUNT;
    short Allow_invalidate_on_printing_window_p_COUNT;
    short Allow_name_box_creation_COUNT;
    short Allow_name_box_creation_without_workspace_COUNT;
    short Allow_no_value_p_COUNT;
    short Allow_user_defined_logbook_handlers_p_COUNT;
    short Alphabet_canonical_element_st_test_COUNT;
    short Alphabet_character_class_st_test_COUNT;
    short Alphabet_count_of_standard_state_transition_tests_COUNT;
    short Alphabet_equality_st_test_COUNT;
    short Alphabet_members_COUNT;
    short Alphabet_standard_state_transition_tests_COUNT;
    short Alphabet_subset_function_COUNT;
    short Already_mutated_evaluators_COUNT;
    short Alternate_chaining_queue_COUNT;
    short Alternate_symbols_for_translation_COUNT;
    short Always_impose_device_set_widths_qm_COUNT;
    short Always_make_runtime_nil_checks_COUNT;
    short Always_recompile_on_load_COUNT;
    short Always_use_current_time_for_uuid_COUNT;
    short Analyze_for_consistency_in_progress_COUNT;
    short Analyzing_export_definition_for_consistency_p_COUNT;
    short Annotation_count_COUNT;
    short Any_cached_evaluator_slot_info_p_COUNT;
    short Append_into_arrays_and_lists_COUNT;
    short Archtypal_stripped_text_COUNT;
    short Args_for_g2gl_object_class_icon_description_override_COUNT;
    short Arithmetic_errors_are_stack_errors_p_COUNT;
    short Array_initialization_evaluation_values_use_designations_p_COUNT;
    short Arrow_button_class_description_COUNT;
    short As_fast_as_possible_model_queue_COUNT;
    short Ascii_to_kana_map_COUNT;
    short Asian_double_byte_count_COUNT;
    short Assignment_section_forms_COUNT;
    short At_end_of_icp_message_block_qm_COUNT;
    short At_end_of_icp_message_group_qm_COUNT;
    short Attempting_save_via_system_procedure_qm_COUNT;
    short Attr_not_found_COUNT;
    short Attribute_display_spot_count_COUNT;
    short Attribute_file_input_frame_COUNT;
    short Attribute_items_COUNT;
    short Attribute_mimic_count_COUNT;
    short Attribute_name_errors_COUNT;
    short Attribute_name_represented_by_table_spot_count_COUNT;
    short Attribute_name_xml_checksum_COUNT;
    short Attribute_nesting_depth_COUNT;
    short Attribute_represented_by_table_spot_count_COUNT;
    short Attribute_table_spot_count_COUNT;
    short Attribute_value_represented_by_table_spot_count_COUNT;
    short Attributes_collector_COUNT;
    short Attributes_collector_tail_COUNT;
    short Attributes_of_history_element_structure_as_interned_list_COUNT;
    short Attributes_of_history_specification_structure_as_interned_list_COUNT;
    short Authorized_products_of_this_machine_COUNT;
    short Authorized_user_class_description_COUNT;
    short Authorized_user_records_of_g2_ok_file_COUNT;
    short Authorized_users_list_COUNT;
    short Authorizing_ok_pathname_COUNT;
    short Automatic_deadlock_detection_frequency_COUNT;
    short Automatic_deadlock_detection_task_COUNT;
    short Automatically_resolve_conflicts_by_default_COUNT;
    short Autostart_after_doing_init_file_qm_COUNT;
    short Autostart_reason_in_init_file_qm_COUNT;
    short Available_8859_reverse_unicode_map_hash_vector_43_vectors_COUNT;
    short Available_backtrace_conses_COUNT;
    short Available_backtrace_conses_tail_COUNT;
    short Available_blocks_hash_hash_vector_43_vectors_COUNT;
    short Available_byte_vector_conses_COUNT;
    short Available_byte_vector_conses_tail_COUNT;
    short Available_call_hash_hash_vector_43_vectors_COUNT;
    short Available_class_description_conses_COUNT;
    short Available_class_description_conses_tail_COUNT;
    short Available_compiler_conses_COUNT;
    short Available_compiler_conses_tail_COUNT;
    short Available_connection_conses_COUNT;
    short Available_connection_conses_tail_COUNT;
    short Available_custom_dialog_conses_COUNT;
    short Available_custom_dialog_conses_tail_COUNT;
    short Available_dragging_conses_COUNT;
    short Available_dragging_conses_tail_COUNT;
    short Available_duplicates_check_hash_table_hash_vector_50021_vectors_COUNT;
    short Available_dynamic_rule_displays_hash_vector_43_vectors_COUNT;
    short Available_entity_conses_COUNT;
    short Available_entity_conses_tail_COUNT;
    short Available_eval_conses_COUNT;
    short Available_eval_conses_tail_COUNT;
    short Available_filter_conses_COUNT;
    short Available_filter_conses_tail_COUNT;
    short Available_float_array_conses_COUNT;
    short Available_float_array_conses_tail_COUNT;
    short Available_fonts_conses_COUNT;
    short Available_fonts_conses_tail_COUNT;
    short Available_foreign_function_registry_internal_hash_vector_131_vectors_COUNT;
    short Available_frame_conses_COUNT;
    short Available_frame_conses_tail_COUNT;
    short Available_frame_display_conses_COUNT;
    short Available_frame_display_conses_tail_COUNT;
    short Available_frame_serial_conses_COUNT;
    short Available_frame_serial_conses_tail_COUNT;
    short Available_frame_serial_number_to_item_table_hash_vector_67_vectors_COUNT;
    short Available_g2_list_conses_COUNT;
    short Available_g2_list_conses_tail_COUNT;
    short Available_g2ds_conses_COUNT;
    short Available_g2ds_conses_tail_COUNT;
    short Available_generic_rule_instance_displays_hash_vector_43_vectors_COUNT;
    short Available_gensym_conses_COUNT;
    short Available_gensym_conses_tail_COUNT;
    short Available_gfi_conses_COUNT;
    short Available_gfi_conses_tail_COUNT;
    short Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_COUNT;
    short Available_grammar_conses_COUNT;
    short Available_grammar_conses_tail_COUNT;
    short Available_graph_conses_COUNT;
    short Available_graph_conses_tail_COUNT;
    short Available_graph_layout_conses_COUNT;
    short Available_graph_layout_conses_tail_COUNT;
    short Available_graph_node_of_graphed_thing_hash_vector_43_vectors_COUNT;
    short Available_graphics_conses_COUNT;
    short Available_graphics_conses_tail_COUNT;
    short Available_gsi_conses_COUNT;
    short Available_gsi_conses_tail_COUNT;
    short Available_hashed_rule_instance_hash_vector_43_vectors_COUNT;
    short Available_history_conses_COUNT;
    short Available_history_conses_tail_COUNT;
    short Available_icon_editor_conses_COUNT;
    short Available_icon_editor_conses_tail_COUNT;
    short Available_icp_buffer_ref_count_conses_COUNT;
    short Available_icp_buffer_ref_count_conses_tail_COUNT;
    short Available_icp_callback_conses_COUNT;
    short Available_icp_callback_conses_tail_COUNT;
    short Available_icp_conses_COUNT;
    short Available_icp_conses_tail_COUNT;
    short Available_indexed_attribute_parent_objects_hash_vector_43_vectors_COUNT;
    short Available_installation_conses_COUNT;
    short Available_installation_conses_tail_COUNT;
    short Available_item_or_name_hash_hash_vector_43_vectors_COUNT;
    short Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_COUNT;
    short Available_java_conses_COUNT;
    short Available_java_conses_tail_COUNT;
    short Available_jis_map_hash_vector_307_vectors_COUNT;
    short Available_journal_conses_COUNT;
    short Available_journal_conses_tail_COUNT;
    short Available_kanji_font_cache_vector_137_vectors_COUNT;
    short Available_kb_fsn_hash_table_hash_vector_131_vectors_COUNT;
    short Available_kb_property_conses_COUNT;
    short Available_kb_property_conses_tail_COUNT;
    short Available_long_array_conses_COUNT;
    short Available_long_array_conses_tail_COUNT;
    short Available_lookup_conses_COUNT;
    short Available_lookup_conses_tail_COUNT;
    short Available_module_required_by_relationships_hash_vector_43_vectors_COUNT;
    short Available_native_font_set_width_equivalence_table_256_vectors_COUNT;
    short Available_native_icon_handle_hash_vector_43_vectors_COUNT;
    short Available_nms_menu_for_hmenu_hash_vector_43_vectors_COUNT;
    short Available_non_kanji_font_vector_257_vectors_COUNT;
    short Available_object_circularity_hashtable_hash_vector_131_vectors_COUNT;
    short Available_ok_file_token_conses_COUNT;
    short Available_ok_file_token_conses_tail_COUNT;
    short Available_part_stack_conses_COUNT;
    short Available_part_stack_conses_tail_COUNT;
    short Available_path_conses_COUNT;
    short Available_path_conses_tail_COUNT;
    short Available_phrase_pool_conses_COUNT;
    short Available_phrase_pool_conses_tail_COUNT;
    short Available_player_conses_COUNT;
    short Available_player_conses_tail_COUNT;
    short Available_printing_conses_COUNT;
    short Available_printing_conses_tail_COUNT;
    short Available_proc_conses_COUNT;
    short Available_proc_conses_tail_COUNT;
    short Available_procedure_invocations_hash_vector_43_vectors_COUNT;
    short Available_queue_item_conses_COUNT;
    short Available_queue_item_conses_tail_COUNT;
    short Available_regexp_conses_COUNT;
    short Available_regexp_conses_tail_COUNT;
    short Available_region_conses_COUNT;
    short Available_region_conses_tail_COUNT;
    short Available_representation_handle_hash_vector_109_vectors_COUNT;
    short Available_reusable_gensyms_COUNT;
    short Available_role_conses_COUNT;
    short Available_role_conses_tail_COUNT;
    short Available_scaled_font_kanji_font_cache_vector_1096_vectors_COUNT;
    short Available_scaled_font_non_kanji_font_vector_2049_vectors_COUNT;
    short Available_sequence_conses_COUNT;
    short Available_sequence_conses_tail_COUNT;
    short Available_sexp_annotation_hash_vector_43_vectors_COUNT;
    short Available_simulate_conses_COUNT;
    short Available_simulate_conses_tail_COUNT;
    short Available_slot_value_conses_COUNT;
    short Available_slot_value_conses_tail_COUNT;
    short Available_stack_change_conses_COUNT;
    short Available_stack_change_conses_tail_COUNT;
    short Available_stack_conses_COUNT;
    short Available_stack_conses_tail_COUNT;
    short Available_streams_conses_COUNT;
    short Available_streams_conses_tail_COUNT;
    short Available_string_pool_conses_COUNT;
    short Available_string_pool_conses_tail_COUNT;
    short Available_sub_call_hash_hash_vector_43_vectors_COUNT;
    short Available_subseries_of_values_64_vectors_COUNT;
    short Available_sysproc_conses_COUNT;
    short Available_sysproc_conses_tail_COUNT;
    short Available_sysproc_continuation_hashtable_hash_vector_131_vectors_COUNT;
    short Available_tiling_patterns_COUNT;
    short Available_timestamp_conses_COUNT;
    short Available_timestamp_conses_tail_COUNT;
    short Available_token_conses_COUNT;
    short Available_token_conses_tail_COUNT;
    short Available_token_stack_conses_COUNT;
    short Available_token_stack_conses_tail_COUNT;
    short Available_tracked_items_call_vector_table_hash_vector_43_vectors_COUNT;
    short Available_tree_ordering_conses_COUNT;
    short Available_tree_ordering_conses_tail_COUNT;
    short Available_ui_callback_table_hash_vector_43_vectors_COUNT;
    short Available_uo_memory_usage_information_hash_vector_43_vectors_COUNT;
    short Available_user_hash_table_internal_hash_vector_43_vectors_COUNT;
    short Available_variable_fill_icp_buffer_4096_vectors_COUNT;
    short Available_vector_pool_conses_COUNT;
    short Available_vector_pool_conses_tail_COUNT;
    short Available_warmboot_conses_COUNT;
    short Available_warmboot_conses_tail_COUNT;
    short Available_workstation_contexts_COUNT;
    short Axis_COUNT;
    short Axis_automatic_COUNT;
    short Axis_crossover_COUNT;
    short Axis_heading_COUNT;
    short Axis_index_COUNT;
    short Axis_is_discrete_p_COUNT;
    short Axis_maximum_COUNT;
    short Axis_minimum_COUNT;
    short Axis_pane_count_COUNT;
    short Axis_tickmark_count_COUNT;
    short Axis_tickmark_count_as_fixnum_COUNT;
    short Axis_tickmark_label_frequency_COUNT;
    short Axis_tickmark_label_max_digits_after_point_COUNT;
    short Axis_tickmark_label_max_digits_before_point_COUNT;
    short Axis_tickmark_label_max_digits_in_exponent_COUNT;
    short Axis_tickmark_step_COUNT;
    short Background_color_value_from_postponed_erase_COUNT;
    short Background_color_value_of_graphic_element_COUNT;
    short Background_print_workspace_process_state_block_count_COUNT;
    short Background_processes_COUNT;
    short Background_processes_task_COUNT;
    short Backoff_limit_COUNT;
    short Backtrace_cons_counter_COUNT;
    short Backtrace_stack_for_internal_error_COUNT;
    short Backtrace_text_buffer_for_internal_error_COUNT;
    short Backtrace_text_buffer_for_string_metering_COUNT;
    short Backup_case_qm_COUNT;
    short Backward_chaining_display_count_COUNT;
    short Backward_chaining_displays_COUNT;
    short Backward_chaining_link_class_description_COUNT;
    short Bad_rule_COUNT;
    short Base_36_digits_string_COUNT;
    short Base_code_body_return_tag_COUNT;
    short Base_reference_COUNT;
    short Baseline_in_window_for_line_of_text_of_graphic_element_COUNT;
    short Basic_part_COUNT;
    short Basic_profiling_structure_count_COUNT;
    short Basis_kb_frame_serial_number_COUNT;
    short Best_text_matched_by_player_COUNT;
    short Bignum_overflow_count_COUNT;
    short Binary_tree_element_count_COUNT;
    short Binary_xml_checksum_COUNT;
    short Bindable_keysyms_COUNT;
    short Bitmap_array_count_COUNT;
    short Bitmap_for_printing_qm_COUNT;
    short Block_change_count_COUNT;
    short Block_class_description_COUNT;
    short Block_near_mouse_cache_count_COUNT;
    short Block_of_frame_COUNT;
    short Blocking_socket_count_COUNT;
    short Blocks_to_delete_after_reading_kb_COUNT;
    short Blocks_to_delete_after_unsquirreling_COUNT;
    short Blocks_with_bad_connections_COUNT;
    short Blocks_with_connections_from_kb_read_COUNT;
    short Blocks_with_relation_instances_from_kb_read_COUNT;
    short Blocks_with_specialized_method_qm_COUNT;
    short Blocks_with_subblocks_from_kb_read_COUNT;
    short Bogus_preflight_from_printing_to_graphs_COUNT;
    short Bombout_clean_up_functions_COUNT;
    short Boolean_composition_over_symbols_allows_top_level_symbols_p_COUNT;
    short Bootstrap_information_COUNT;
    short Bottom_edge_in_window_of_graphic_element_COUNT;
    short Bottom_edge_of_draw_area_COUNT;
    short Bottom_edge_of_frame_COUNT;
    short Bottom_scroll_arrow_rubber_stamp_widget_COUNT;
    short Bounding_box_class_description_COUNT;
    short Bounding_box_spot_count_COUNT;
    short Bounding_box_state_count_COUNT;
    short Bounding_state_count_COUNT;
    short Bpel_xml_namespace_COUNT;
    short Break_if_name_inconsistency_qm_COUNT;
    short Breakpoint_level_COUNT;
    short Breakpoints_enabled_p_COUNT;
    short Buffer_for_internal_error_on_console_COUNT;
    short Buffer_for_internal_error_on_logbook_COUNT;
    short Buffer_for_read_file_into_string_COUNT;
    short Buffer_for_string_metering_COUNT;
    short Buffer_for_write_internal_error_COUNT;
    short Buffer_index_of_ok_file_reader_COUNT;
    short Buffer_length_of_ok_file_reader_COUNT;
    short Buffer_of_ok_file_reader_COUNT;
    short Buffer_of_resumable_p_COUNT;
    short Buffered_plot_painting_color_COUNT;
    short Buffered_plot_painting_line_style_COUNT;
    short Buffered_plot_painting_one_pixel_in_seconds_COUNT;
    short Buffered_plot_painting_plot_COUNT;
    short Buffered_plot_painting_style_arg_COUNT;
    short Buffered_plot_painting_value_axis_COUNT;
    short Buggy_polyline_p_COUNT;
    short Built_in_character_codes_COUNT;
    short Button_class_description_COUNT;
    short Button_down_state_count_COUNT;
    short Button_label_class_description_COUNT;
    short Button_menu_spot_count_COUNT;
    short Button_spot_count_COUNT;
    short Buttons_in_button_down_state_COUNT;
    short Bypass_add_class_export_info_attributes_p_COUNT;
    short Bypass_fix_for_exported_method_overloading_p_COUNT;
    short Byte_code_body_count_COUNT;
    short Byte_code_stream_count_COUNT;
    short Byte_vector_16_pool_counts_COUNT;
    short Byte_vector_16_pool_number_to_malloc_COUNT;
    short Byte_vector_16_pools_COUNT;
    short Byte_vector_cons_counter_COUNT;
    short Bytes_allocated_for_image_tiles_COUNT;
    short Bytes_consumed_by_one_undefaulted_lookup_slot_COUNT;
    short Bytes_in_allocated_byte_vector_16_vectors_COUNT;
    short Bytes_per_double_float_simple_array_cached_COUNT;
    short Bytes_per_long_simple_array_cached_COUNT;
    short C_byte_code_body_result_1_COUNT;
    short C_byte_code_body_result_2_COUNT;
    short C_byte_code_body_result_3_COUNT;
    short C_byte_code_body_result_4_COUNT;
    short C_byte_code_body_result_5_COUNT;
    short C_byte_code_body_result_6_COUNT;
    short C_byte_code_body_result_7_COUNT;
    short C_byte_code_body_result_8_COUNT;
    short Cache_al_semantics_graph_COUNT;
    short Cache_chinese_semantics_graph_COUNT;
    short Cache_embedded_option_semantics_graph_COUNT;
    short Cache_ent_semantics_graph_COUNT;
    short Cache_g1_semantics_graph_COUNT;
    short Cache_gfi_semantics_graph_COUNT;
    short Cache_gsi_semantics_graph_COUNT;
    short Cache_gspan_semantics_graph_COUNT;
    short Cache_icp_semantics_graph_COUNT;
    short Cache_japanese_semantics_graph_COUNT;
    short Cache_jl_semantics_graph_COUNT;
    short Cache_jp_semantics_graph_COUNT;
    short Cache_kfep_semantics_graph_COUNT;
    short Cache_korean_semantics_graph_COUNT;
    short Cache_nupec_semantics_graph_COUNT;
    short Cache_restricted_use_option_semantics_graph_COUNT;
    short Cache_runtime_option_semantics_graph_COUNT;
    short Cache_stack_and_locals_COUNT;
    short Cached_byte_code_body_COUNT;
    short Cached_classes_for_backward_chaining_COUNT;
    short Cached_classes_for_forward_chaining_COUNT;
    short Cached_compareoperator_COUNT;
    short Cached_event_bit_COUNT;
    short Cached_eventflag_COUNT;
    short Cached_explanation_from_data_server_or_initial_value_count_COUNT;
    short Cached_explanation_from_frame_count_COUNT;
    short Cached_explanation_from_generic_formula_count_COUNT;
    short Cached_explanation_from_rule_count_COUNT;
    short Cached_explanation_from_specific_formula_count_COUNT;
    short Cached_fellow_val_COUNT;
    short Cached_fixnum_start_time_COUNT;
    short Cached_fixnum_time_limit_qm_COUNT;
    short Cached_fixnum_time_qm_COUNT;
    short Cached_gensym_user_home_directory_COUNT;
    short Cached_local_gensym_x11_display_COUNT;
    short Cached_local_icp_version_info_COUNT;
    short Cached_long_code_constant_form_COUNT;
    short Cached_machine_id_qm_COUNT;
    short Cached_matching_machine_id_qm_COUNT;
    short Cached_n_COUNT;
    short Cached_name_for_local_home_COUNT;
    short Cached_nstart_COUNT;
    short Cached_requiredgoodsize_COUNT;
    short Cached_restrictions_alist_COUNT;
    short Cached_result_COUNT;
    short Cached_stack_frame_base_COUNT;
    short Cached_stack_program_counter_COUNT;
    short Cached_stack_program_counter_form_COUNT;
    short Cached_subj_COUNT;
    short Cached_tcpip_listener_address_qm_COUNT;
    short Cached_timed_out_foreign_function_name_qm_COUNT;
    short Cached_top_of_stack_COUNT;
    short Cached_top_of_stack_form_COUNT;
    short Cached_unknown_error_string_with_code_qm_COUNT;
    short Calendar_cv_count_COUNT;
    short Call_check_node_attribute_value_p_COUNT;
    short Call_statement_processed_qm_COUNT;
    short Called_within_clear_text_loading_COUNT;
    short Called_within_locate_or_create_junction_block_definition_COUNT;
    short Calling_float_function_cleverly_p_COUNT;
    short Calling_tformat_for_give_warning_qm_COUNT;
    short Cascaded_ring_buffer_count_COUNT;
    short Catch_for_let_in_expression_context_COUNT;
    short Category_evaluator_interface_count_COUNT;
    short Category_for_category_symbol_count_COUNT;
    short Category_for_token_count_COUNT;
    short Category_instance_menu_workspace_class_description_COUNT;
    short Category_menu_button_spot_count_COUNT;
    short Category_menu_class_description_COUNT;
    short Category_set_count_COUNT;
    short Category_symbols_for_non_contributing_categories_COUNT;
    short Category_visit_vector_qm_COUNT;
    short Cell_COUNT;
    short Cell_contents_COUNT;
    short Cell_index_currently_being_registered_COUNT;
    short Chain_of_available_access_errors_COUNT;
    short Chain_of_available_annotations_COUNT;
    short Chain_of_available_asian_double_bytes_COUNT;
    short Chain_of_available_attribute_display_spots_COUNT;
    short Chain_of_available_attribute_mimics_COUNT;
    short Chain_of_available_attribute_name_represented_by_table_spots_COUNT;
    short Chain_of_available_attribute_represented_by_table_spots_COUNT;
    short Chain_of_available_attribute_table_spots_COUNT;
    short Chain_of_available_attribute_value_represented_by_table_spots_COUNT;
    short Chain_of_available_axis_panes_COUNT;
    short Chain_of_available_background_print_workspace_process_state_blocks_COUNT;
    short Chain_of_available_backward_chaining_displays_COUNT;
    short Chain_of_available_basic_profiling_structures_COUNT;
    short Chain_of_available_binary_tree_elements_COUNT;
    short Chain_of_available_bitmap_arrays_COUNT;
    short Chain_of_available_block_changes_COUNT;
    short Chain_of_available_block_near_mouse_caches_COUNT;
    short Chain_of_available_blocking_sockets_COUNT;
    short Chain_of_available_bounding_box_spots_COUNT;
    short Chain_of_available_bounding_box_states_COUNT;
    short Chain_of_available_bounding_states_COUNT;
    short Chain_of_available_button_down_states_COUNT;
    short Chain_of_available_button_menu_spots_COUNT;
    short Chain_of_available_button_spots_COUNT;
    short Chain_of_available_byte_code_bodys_COUNT;
    short Chain_of_available_byte_code_streams_COUNT;
    short Chain_of_available_cached_explanation_from_data_server_or_initial_values_COUNT;
    short Chain_of_available_cached_explanation_from_frames_COUNT;
    short Chain_of_available_cached_explanation_from_generic_formulas_COUNT;
    short Chain_of_available_cached_explanation_from_rules_COUNT;
    short Chain_of_available_cached_explanation_from_specific_formulas_COUNT;
    short Chain_of_available_calendar_cvs_COUNT;
    short Chain_of_available_cascaded_ring_buffers_COUNT;
    short Chain_of_available_category_evaluator_interfaces_COUNT;
    short Chain_of_available_category_for_category_symbols_COUNT;
    short Chain_of_available_category_for_tokens_COUNT;
    short Chain_of_available_category_menu_button_spots_COUNT;
    short Chain_of_available_category_sets_COUNT;
    short Chain_of_available_character_descriptions_COUNT;
    short Chain_of_available_character_images_COUNT;
    short Chain_of_available_character_sequence_token_menu_button_spots_COUNT;
    short Chain_of_available_chart_spots_COUNT;
    short Chain_of_available_chart_views_COUNT;
    short Chain_of_available_check_box_cvs_COUNT;
    short Chain_of_available_checkable_list_box_cvs_COUNT;
    short Chain_of_available_class_descriptions_COUNT;
    short Chain_of_available_class_file_streams_COUNT;
    short Chain_of_available_class_instances_memory_infos_COUNT;
    short Chain_of_available_class_subscriptions_COUNT;
    short Chain_of_available_class_subscriptionss_COUNT;
    short Chain_of_available_close_box_spots_COUNT;
    short Chain_of_available_code_body_continuations_COUNT;
    short Chain_of_available_code_body_invocations_COUNT;
    short Chain_of_available_color_maps_COUNT;
    short Chain_of_available_compiled_resources_COUNT;
    short Chain_of_available_compiler_code_body_entrys_COUNT;
    short Chain_of_available_component_change_reports_COUNT;
    short Chain_of_available_compound_fixnum_simulation_times_COUNT;
    short Chain_of_available_compound_slot_descriptors_COUNT;
    short Chain_of_available_compound_type_descriptors_COUNT;
    short Chain_of_available_computation_instances_COUNT;
    short Chain_of_available_connection_items_COUNT;
    short Chain_of_available_connection_spots_COUNT;
    short Chain_of_available_connection_subrectangle_structures_COUNT;
    short Chain_of_available_connections_COUNT;
    short Chain_of_available_credits_table_spots_COUNT;
    short Chain_of_available_data_servers_COUNT;
    short Chain_of_available_date_formats_COUNT;
    short Chain_of_available_deferred_updates_COUNT;
    short Chain_of_available_detail_pane_spots_COUNT;
    short Chain_of_available_dial_spots_COUNT;
    short Chain_of_available_dialog_components_COUNT;
    short Chain_of_available_dialog_errors_structures_COUNT;
    short Chain_of_available_dialog_states_COUNT;
    short Chain_of_available_dialog_views_COUNT;
    short Chain_of_available_display_panes_COUNT;
    short Chain_of_available_drag_handle_states_COUNT;
    short Chain_of_available_dragging_states_COUNT;
    short Chain_of_available_drawing_tasks_COUNT;
    short Chain_of_available_duration_cvs_COUNT;
    short Chain_of_available_dynamic_dialogs_COUNT;
    short Chain_of_available_dynamic_workspace_associated_structures_COUNT;
    short Chain_of_available_edit_box_changes_COUNT;
    short Chain_of_available_edit_box_spots_COUNT;
    short Chain_of_available_edit_caches_COUNT;
    short Chain_of_available_edit_menu_states_COUNT;
    short Chain_of_available_edit_states_COUNT;
    short Chain_of_available_element_of_foreign_linking_infos_COUNT;
    short Chain_of_available_elevator_of_scroll_bar_spots_COUNT;
    short Chain_of_available_elevator_shaft_spots_COUNT;
    short Chain_of_available_elevator_states_COUNT;
    short Chain_of_available_entire_focus_menu_spots_COUNT;
    short Chain_of_available_entire_g2_window_spots_COUNT;
    short Chain_of_available_entire_menu_spots_COUNT;
    short Chain_of_available_eq_hash_tables_COUNT;
    short Chain_of_available_error_codes_COUNT;
    short Chain_of_available_evaluator_slot_infos_COUNT;
    short Chain_of_available_event_detectors_COUNT;
    short Chain_of_available_expression_for_compilations_COUNT;
    short Chain_of_available_external_class_infos_COUNT;
    short Chain_of_available_external_method_infos_COUNT;
    short Chain_of_available_external_set_pointerss_COUNT;
    short Chain_of_available_external_simulation_objects_COUNT;
    short Chain_of_available_extremum_caches_COUNT;
    short Chain_of_available_filename_parser_informations_COUNT;
    short Chain_of_available_for_structures_COUNT;
    short Chain_of_available_foreign_function_call_infos_COUNT;
    short Chain_of_available_foreign_function_entrys_COUNT;
    short Chain_of_available_foreign_function_image_infos_COUNT;
    short Chain_of_available_foreign_struct_infos_COUNT;
    short Chain_of_available_formula_invocations_COUNT;
    short Chain_of_available_frame_component_spots_COUNT;
    short Chain_of_available_frame_description_references_COUNT;
    short Chain_of_available_frame_displays_COUNT;
    short Chain_of_available_frame_transforms_COUNT;
    short Chain_of_available_fsm_states_COUNT;
    short Chain_of_available_function_infos_COUNT;
    short Chain_of_available_function_invocations_COUNT;
    short Chain_of_available_future_task_queue_holders_COUNT;
    short Chain_of_available_g2_list_elements_COUNT;
    short Chain_of_available_g2_login_states_COUNT;
    short Chain_of_available_g2_stream_structures_COUNT;
    short Chain_of_available_g2_tokens_COUNT;
    short Chain_of_available_g2ds_interfaces_COUNT;
    short Chain_of_available_g2ds_server_connections_COUNT;
    short Chain_of_available_g2ds_variables_COUNT;
    short Chain_of_available_g2gl_activity_compilations_COUNT;
    short Chain_of_available_g2gl_activity_optionss_COUNT;
    short Chain_of_available_g2gl_alarm_event_handler_activity_compilations_COUNT;
    short Chain_of_available_g2gl_assign_activity_compilations_COUNT;
    short Chain_of_available_g2gl_attribute_display_compilations_COUNT;
    short Chain_of_available_g2gl_body_compilations_COUNT;
    short Chain_of_available_g2gl_break_activity_compilations_COUNT;
    short Chain_of_available_g2gl_call_activity_compilations_COUNT;
    short Chain_of_available_g2gl_call_invocations_COUNT;
    short Chain_of_available_g2gl_compensate_activity_compilations_COUNT;
    short Chain_of_available_g2gl_compensation_handler_activity_compilations_COUNT;
    short Chain_of_available_g2gl_compilation_versions_COUNT;
    short Chain_of_available_g2gl_do_activity_compilations_COUNT;
    short Chain_of_available_g2gl_empty_activity_compilations_COUNT;
    short Chain_of_available_g2gl_execution_faults_COUNT;
    short Chain_of_available_g2gl_execution_frames_COUNT;
    short Chain_of_available_g2gl_execution_threads_COUNT;
    short Chain_of_available_g2gl_exit_activity_compilations_COUNT;
    short Chain_of_available_g2gl_fault_handler_activity_compilations_COUNT;
    short Chain_of_available_g2gl_flow_discriminator_activity_compilations_COUNT;
    short Chain_of_available_g2gl_flow_gate_activity_compilations_COUNT;
    short Chain_of_available_g2gl_flow_signal_activity_compilations_COUNT;
    short Chain_of_available_g2gl_flow_split_activity_compilations_COUNT;
    short Chain_of_available_g2gl_flow_sync_activity_compilations_COUNT;
    short Chain_of_available_g2gl_flow_terminator_activity_compilations_COUNT;
    short Chain_of_available_g2gl_invoke_activity_compilations_COUNT;
    short Chain_of_available_g2gl_message_event_handler_activity_compilations_COUNT;
    short Chain_of_available_g2gl_message_transmissions_COUNT;
    short Chain_of_available_g2gl_n_out_of_m_flow_join_activity_compilations_COUNT;
    short Chain_of_available_g2gl_pick_activity_compilations_COUNT;
    short Chain_of_available_g2gl_pick_join_activity_compilations_COUNT;
    short Chain_of_available_g2gl_process_invocation_threads_COUNT;
    short Chain_of_available_g2gl_receive_activity_compilations_COUNT;
    short Chain_of_available_g2gl_reply_activity_compilations_COUNT;
    short Chain_of_available_g2gl_return_activity_compilations_COUNT;
    short Chain_of_available_g2gl_scope_activity_compilations_COUNT;
    short Chain_of_available_g2gl_service_ports_COUNT;
    short Chain_of_available_g2gl_switch_fork_activity_compilations_COUNT;
    short Chain_of_available_g2gl_switch_join_activity_compilations_COUNT;
    short Chain_of_available_g2gl_text_box_compilations_COUNT;
    short Chain_of_available_g2gl_throw_activity_compilations_COUNT;
    short Chain_of_available_g2gl_wait_activity_compilations_COUNT;
    short Chain_of_available_g2gl_while_activity_compilations_COUNT;
    short Chain_of_available_gb_2312s_COUNT;
    short Chain_of_available_gensym_grammars_COUNT;
    short Chain_of_available_gensym_pathnames_COUNT;
    short Chain_of_available_gensym_string_streams_COUNT;
    short Chain_of_available_gensym_string_text_sequences_COUNT;
    short Chain_of_available_gensym_windows_COUNT;
    short Chain_of_available_geometrys_COUNT;
    short Chain_of_available_gesture_functions_COUNT;
    short Chain_of_available_gesture_locals_COUNT;
    short Chain_of_available_gesture_threads_COUNT;
    short Chain_of_available_gfi_queue_items_COUNT;
    short Chain_of_available_global_profiling_structures_COUNT;
    short Chain_of_available_goto_tag_entrys_COUNT;
    short Chain_of_available_graph_displays_COUNT;
    short Chain_of_available_graph_nodes_COUNT;
    short Chain_of_available_graph_renderings_COUNT;
    short Chain_of_available_graph_table_spots_COUNT;
    short Chain_of_available_graphic_character_sets_COUNT;
    short Chain_of_available_grid_panes_COUNT;
    short Chain_of_available_grid_view_cells_COUNT;
    short Chain_of_available_group_index_structures_COUNT;
    short Chain_of_available_gsi_array_wrappers_COUNT;
    short Chain_of_available_gsi_attributes_COUNT;
    short Chain_of_available_gsi_extension_datas_COUNT;
    short Chain_of_available_gsi_historys_COUNT;
    short Chain_of_available_gsi_icp_interfaces_COUNT;
    short Chain_of_available_gsi_instance_extensions_COUNT;
    short Chain_of_available_gsi_instances_COUNT;
    short Chain_of_available_gsi_local_functions_COUNT;
    short Chain_of_available_gsi_remote_procedures_COUNT;
    short Chain_of_available_gsi_transfer_wrappers_COUNT;
    short Chain_of_available_halt_infos_COUNT;
    short Chain_of_available_hfep_hanc_types_COUNT;
    short Chain_of_available_history_ring_buffers_COUNT;
    short Chain_of_available_hot_spot_states_COUNT;
    short Chain_of_available_html_views_COUNT;
    short Chain_of_available_i_am_alive_infos_COUNT;
    short Chain_of_available_icmp_sockets_COUNT;
    short Chain_of_available_icon_descriptions_COUNT;
    short Chain_of_available_icon_editor_buttons_COUNT;
    short Chain_of_available_icon_editor_engines_COUNT;
    short Chain_of_available_icon_editor_layers_pads_COUNT;
    short Chain_of_available_icon_editor_tables_COUNT;
    short Chain_of_available_icon_editor_translators_COUNT;
    short Chain_of_available_icon_editor_view_pads_COUNT;
    short Chain_of_available_icon_editors_COUNT;
    short Chain_of_available_icon_renderings_COUNT;
    short Chain_of_available_icon_slot_groups_COUNT;
    short Chain_of_available_icp_buffers_COUNT;
    short Chain_of_available_icp_ports_COUNT;
    short Chain_of_available_icp_read_tasks_COUNT;
    short Chain_of_available_icp_sockets_COUNT;
    short Chain_of_available_icp_write_tasks_COUNT;
    short Chain_of_available_identified_drawing_activitys_COUNT;
    short Chain_of_available_image_cvs_COUNT;
    short Chain_of_available_image_datas_COUNT;
    short Chain_of_available_image_plane_spots_COUNT;
    short Chain_of_available_image_planes_COUNT;
    short Chain_of_available_image_renderings_COUNT;
    short Chain_of_available_image_tiles_COUNT;
    short Chain_of_available_incomplete_painting_actions_COUNT;
    short Chain_of_available_incomplete_phrases_COUNT;
    short Chain_of_available_index_spaces_COUNT;
    short Chain_of_available_inference_background_collections_COUNT;
    short Chain_of_available_inform_message_informations_COUNT;
    short Chain_of_available_inlining_data_holders_COUNT;
    short Chain_of_available_input_table_spots_COUNT;
    short Chain_of_available_inspect_command_spots_COUNT;
    short Chain_of_available_integer_cvs_COUNT;
    short Chain_of_available_inter_g2_data_request_queues_COUNT;
    short Chain_of_available_internal_tokens_COUNT;
    short Chain_of_available_interned_lists_COUNT;
    short Chain_of_available_interned_remote_procedure_item_passing_infos_COUNT;
    short Chain_of_available_invalid_spots_COUNT;
    short Chain_of_available_iso_2022_transcoders_COUNT;
    short Chain_of_available_iso_646s_COUNT;
    short Chain_of_available_iso_8859_10s_COUNT;
    short Chain_of_available_iso_8859_1s_COUNT;
    short Chain_of_available_iso_8859_2s_COUNT;
    short Chain_of_available_iso_8859_3s_COUNT;
    short Chain_of_available_iso_8859_4s_COUNT;
    short Chain_of_available_iso_8859_5s_COUNT;
    short Chain_of_available_iso_8859_6s_COUNT;
    short Chain_of_available_iso_8859_7s_COUNT;
    short Chain_of_available_iso_8859_8s_COUNT;
    short Chain_of_available_iso_8859_9s_COUNT;
    short Chain_of_available_iso_8859_abstracts_COUNT;
    short Chain_of_available_iso_8859_transcoders_COUNT;
    short Chain_of_available_item_access_caches_COUNT;
    short Chain_of_available_item_represented_by_table_spots_COUNT;
    short Chain_of_available_java_classs_COUNT;
    short Chain_of_available_java_code_exceptions_COUNT;
    short Chain_of_available_java_codes_COUNT;
    short Chain_of_available_java_descriptors_COUNT;
    short Chain_of_available_java_fields_COUNT;
    short Chain_of_available_java_methods_COUNT;
    short Chain_of_available_java_symbols_COUNT;
    short Chain_of_available_javalink_versioned_call_datas_COUNT;
    short Chain_of_available_jis_x_0208s_COUNT;
    short Chain_of_available_kb_saves_COUNT;
    short Chain_of_available_kb_transfers_COUNT;
    short Chain_of_available_kb_workspace_image_plane_spots_COUNT;
    short Chain_of_available_kfep_batchs_COUNT;
    short Chain_of_available_kfep_conversion_choice_menu_button_spots_COUNT;
    short Chain_of_available_kfep_masters_COUNT;
    short Chain_of_available_ks_c_5601s_COUNT;
    short Chain_of_available_label_box_spots_COUNT;
    short Chain_of_available_large_scaled_font_buckets_COUNT;
    short Chain_of_available_layer_boxs_COUNT;
    short Chain_of_available_legend_panes_COUNT;
    short Chain_of_available_lexing_tables_COUNT;
    short Chain_of_available_line_drawing_for_printings_COUNT;
    short Chain_of_available_lisp_grid_views_COUNT;
    short Chain_of_available_list_box_cvs_COUNT;
    short Chain_of_available_local_events_COUNT;
    short Chain_of_available_local_nupec_variables_COUNT;
    short Chain_of_available_logbook_views_COUNT;
    short Chain_of_available_loose_end_spots_COUNT;
    short Chain_of_available_lru_elements_COUNT;
    short Chain_of_available_media_streams_COUNT;
    short Chain_of_available_memory_limit_infos_COUNT;
    short Chain_of_available_menu_button_spots_COUNT;
    short Chain_of_available_menu_choose_states_COUNT;
    short Chain_of_available_menu_item_spots_COUNT;
    short Chain_of_available_menu_pane_spots_COUNT;
    short Chain_of_available_menu_title_spots_COUNT;
    short Chain_of_available_meter_or_dial_spots_COUNT;
    short Chain_of_available_meter_spots_COUNT;
    short Chain_of_available_minimal_character_descriptions_COUNT;
    short Chain_of_available_modal_menu_states_COUNT;
    short Chain_of_available_model_queues_COUNT;
    short Chain_of_available_model_runtime_infos_COUNT;
    short Chain_of_available_modify_control_action_types_COUNT;
    short Chain_of_available_modify_control_structures_COUNT;
    short Chain_of_available_modify_dialog_structures_COUNT;
    short Chain_of_available_mouse_drag_detector_states_COUNT;
    short Chain_of_available_mouse_pointers_COUNT;
    short Chain_of_available_mouse_watch_states_COUNT;
    short Chain_of_available_move_dragging_states_COUNT;
    short Chain_of_available_multiframe_table_spots_COUNT;
    short Chain_of_available_multiply_wild_regular_expression_nodes_COUNT;
    short Chain_of_available_name_box_spots_COUNT;
    short Chain_of_available_named_gensym_structures_COUNT;
    short Chain_of_available_native_dialogs_COUNT;
    short Chain_of_available_native_fonts_COUNT;
    short Chain_of_available_native_simple_dialog_states_COUNT;
    short Chain_of_available_native_windows_COUNT;
    short Chain_of_available_new_table_background_spots_COUNT;
    short Chain_of_available_new_table_cell_spots_COUNT;
    short Chain_of_available_new_table_spots_COUNT;
    short Chain_of_available_nms_menu_items_COUNT;
    short Chain_of_available_nms_menus_COUNT;
    short Chain_of_available_non_kb_workspace_image_plane_spots_COUNT;
    short Chain_of_available_normal_completions_COUNT;
    short Chain_of_available_nupec_synchronize_variable_or_parameters_COUNT;
    short Chain_of_available_object_building_problems_COUNT;
    short Chain_of_available_object_passing_infos_COUNT;
    short Chain_of_available_ok_file_tokens_COUNT;
    short Chain_of_available_output_only_table_spots_COUNT;
    short Chain_of_available_outside_window_spots_COUNT;
    short Chain_of_available_overview_pane_spots_COUNT;
    short Chain_of_available_pane_background_spots_COUNT;
    short Chain_of_available_pane_border_spots_COUNT;
    short Chain_of_available_pane_component_spots_COUNT;
    short Chain_of_available_pane_spots_COUNT;
    short Chain_of_available_panes_COUNT;
    short Chain_of_available_parse_objects_COUNT;
    short Chain_of_available_parse_tables_COUNT;
    short Chain_of_available_parsing_contexts_COUNT;
    short Chain_of_available_parsing_tokens_COUNT;
    short Chain_of_available_partial_commands_COUNT;
    short Chain_of_available_pathname_component_token_menu_button_spots_COUNT;
    short Chain_of_available_pending_activitys_COUNT;
    short Chain_of_available_phrase_rule_completions_COUNT;
    short Chain_of_available_pixmaps_COUNT;
    short Chain_of_available_place_reference_internalss_COUNT;
    short Chain_of_available_plot_data_ring_buffers_COUNT;
    short Chain_of_available_possible_phrases_COUNT;
    short Chain_of_available_procedure_invocations_COUNT;
    short Chain_of_available_processs_COUNT;
    short Chain_of_available_productions_COUNT;
    short Chain_of_available_prop_grid_verbs_COUNT;
    short Chain_of_available_property_grid_nodes_COUNT;
    short Chain_of_available_property_grids_COUNT;
    short Chain_of_available_pseudo_attributes_COUNT;
    short Chain_of_available_pseudo_frames_COUNT;
    short Chain_of_available_pseudo_instruction_streams_COUNT;
    short Chain_of_available_push_button_cvs_COUNT;
    short Chain_of_available_quantity_cvs_COUNT;
    short Chain_of_available_query_cell_streams_COUNT;
    short Chain_of_available_queue_elements_COUNT;
    short Chain_of_available_queues_COUNT;
    short Chain_of_available_readout_table_spots_COUNT;
    short Chain_of_available_receiving_resumable_objects_COUNT;
    short Chain_of_available_receiving_rpc_arglist_structures_COUNT;
    short Chain_of_available_reference_structures_COUNT;
    short Chain_of_available_region_bounds_and_rasters_COUNT;
    short Chain_of_available_regular_expression_node_for_set_of_characterss_COUNT;
    short Chain_of_available_regular_expression_node_for_single_characters_COUNT;
    short Chain_of_available_regular_expression_node_for_single_wild_characters_COUNT;
    short Chain_of_available_regular_expression_node_for_subexpressions_COUNT;
    short Chain_of_available_regular_expression_node_for_wild_characterss_COUNT;
    short Chain_of_available_regular_expression_nodes_COUNT;
    short Chain_of_available_relation_instances_COUNT;
    short Chain_of_available_relative_time_panes_COUNT;
    short Chain_of_available_remote_procedure_calls_COUNT;
    short Chain_of_available_remote_procedure_identifiers_COUNT;
    short Chain_of_available_remote_procedure_item_passing_infos_COUNT;
    short Chain_of_available_remote_procedure_names_COUNT;
    short Chain_of_available_replacement_token_menu_button_spots_COUNT;
    short Chain_of_available_resize_box_spots_COUNT;
    short Chain_of_available_resumable_circular_nodes_COUNT;
    short Chain_of_available_resumable_evaluation_sequence_node_mixins_COUNT;
    short Chain_of_available_resumable_evaluation_sequence_nodes_COUNT;
    short Chain_of_available_resumable_evaluation_structure_nodes_COUNT;
    short Chain_of_available_resumable_history_nodes_COUNT;
    short Chain_of_available_resumable_icp_node_mixins_COUNT;
    short Chain_of_available_resumable_icp_object_mixins_COUNT;
    short Chain_of_available_resumable_instance_node_mixins_COUNT;
    short Chain_of_available_resumable_instance_or_complex_value_node_mixins_COUNT;
    short Chain_of_available_resumable_list_node_mixins_COUNT;
    short Chain_of_available_resumable_node_mixins_COUNT;
    short Chain_of_available_resumable_object_list_nodes_COUNT;
    short Chain_of_available_resumable_object_mixins_COUNT;
    short Chain_of_available_resumable_object_nodes_COUNT;
    short Chain_of_available_resumable_object_vector_nodes_COUNT;
    short Chain_of_available_resumable_sequence_node_mixins_COUNT;
    short Chain_of_available_resumable_value_list_nodes_COUNT;
    short Chain_of_available_resumable_value_nodes_COUNT;
    short Chain_of_available_resumable_value_vector_nodes_COUNT;
    short Chain_of_available_resumable_vector_node_mixins_COUNT;
    short Chain_of_available_ring_buffer_states_COUNT;
    short Chain_of_available_ring_raster_for_graphs_COUNT;
    short Chain_of_available_rule_instances_COUNT;
    short Chain_of_available_saving_contexts_COUNT;
    short Chain_of_available_scaled_fonts_COUNT;
    short Chain_of_available_schedule_tasks_COUNT;
    short Chain_of_available_scheduled_remote_procedure_starts_COUNT;
    short Chain_of_available_search_state_table_spots_COUNT;
    short Chain_of_available_selection_handle_spots_COUNT;
    short Chain_of_available_selection_rectangle_states_COUNT;
    short Chain_of_available_selections_COUNT;
    short Chain_of_available_sending_resumable_objects_COUNT;
    short Chain_of_available_sensor_groups_COUNT;
    short Chain_of_available_sensor_groups_headers_COUNT;
    short Chain_of_available_set_of_possible_phrasess_COUNT;
    short Chain_of_available_shift_jis_transcoders_COUNT;
    short Chain_of_available_short_duration_cvs_COUNT;
    short Chain_of_available_short_representation_table_spots_COUNT;
    short Chain_of_available_shortcut_bars_COUNT;
    short Chain_of_available_show_parameters_decoders_COUNT;
    short Chain_of_available_shredded_rasters_COUNT;
    short Chain_of_available_simple_item_spots_COUNT;
    short Chain_of_available_simulation_infos_COUNT;
    short Chain_of_available_skip_list_elements_COUNT;
    short Chain_of_available_slider_spots_COUNT;
    short Chain_of_available_slot_component_descriptors_COUNT;
    short Chain_of_available_slot_descriptions_COUNT;
    short Chain_of_available_snapshot_invocation_infos_COUNT;
    short Chain_of_available_snapshot_of_blocks_COUNT;
    short Chain_of_available_socket_output_buffers_COUNT;
    short Chain_of_available_sockets_COUNT;
    short Chain_of_available_source_nupec_synchronizations_COUNT;
    short Chain_of_available_sparse_arrays_COUNT;
    short Chain_of_available_spinner_cvs_COUNT;
    short Chain_of_available_spots_COUNT;
    short Chain_of_available_stack_node_instructions_COUNT;
    short Chain_of_available_stack_nodes_COUNT;
    short Chain_of_available_state_transitions_COUNT;
    short Chain_of_available_status_bar_panes_COUNT;
    short Chain_of_available_status_bars_COUNT;
    short Chain_of_available_status_pane_spots_COUNT;
    short Chain_of_available_stepper_of_scroll_bar_spots_COUNT;
    short Chain_of_available_strict_subcategory_infos_COUNT;
    short Chain_of_available_sub_profiling_structures_COUNT;
    short Chain_of_available_subcommand_menu_button_spots_COUNT;
    short Chain_of_available_subcommand_states_COUNT;
    short Chain_of_available_symbol_trees_COUNT;
    short Chain_of_available_system_rpc_instances_COUNT;
    short Chain_of_available_system_rpcs_COUNT;
    short Chain_of_available_t2_nonce_datas_COUNT;
    short Chain_of_available_table_background_spots_COUNT;
    short Chain_of_available_table_header_spots_COUNT;
    short Chain_of_available_table_spots_COUNT;
    short Chain_of_available_tabular_views_COUNT;
    short Chain_of_available_target_nupec_synchronizations_COUNT;
    short Chain_of_available_tcp_sockets_COUNT;
    short Chain_of_available_temporary_constants_COUNT;
    short Chain_of_available_text_box_cvs_COUNT;
    short Chain_of_available_text_box_spots_COUNT;
    short Chain_of_available_text_inserter_spots_COUNT;
    short Chain_of_available_text_marking_states_COUNT;
    short Chain_of_available_text_sequences_COUNT;
    short Chain_of_available_text_spots_COUNT;
    short Chain_of_available_text_tokenization_states_COUNT;
    short Chain_of_available_thrashing_ratio_ring_buffers_COUNT;
    short Chain_of_available_tiled_rasters_COUNT;
    short Chain_of_available_tiling_patterns_COUNT;
    short Chain_of_available_time_of_day_cvs_COUNT;
    short Chain_of_available_title_bar_spots_COUNT;
    short Chain_of_available_token_menu_button_spots_COUNT;
    short Chain_of_available_top_level_states_COUNT;
    short Chain_of_available_transcode_text_conversion_styles_COUNT;
    short Chain_of_available_transcoders_COUNT;
    short Chain_of_available_transfer_dragging_states_COUNT;
    short Chain_of_available_tree_view_nodes_COUNT;
    short Chain_of_available_tree_views_COUNT;
    short Chain_of_available_trend_chart_panes_COUNT;
    short Chain_of_available_trend_chart_spots_COUNT;
    short Chain_of_available_type_descriptions_COUNT;
    short Chain_of_available_type_in_box_spots_COUNT;
    short Chain_of_available_ui_callbacks_COUNT;
    short Chain_of_available_unicode_blocks_COUNT;
    short Chain_of_available_unicode_byte_swapped_transcoders_COUNT;
    short Chain_of_available_unicode_transcoders_COUNT;
    short Chain_of_available_unicode_ucs_2_transcoders_COUNT;
    short Chain_of_available_uninteresting_block_spots_COUNT;
    short Chain_of_available_uri_references_COUNT;
    short Chain_of_available_user_mode_aliass_COUNT;
    short Chain_of_available_user_mouse_tracking_states_COUNT;
    short Chain_of_available_utf_7_transcoders_COUNT;
    short Chain_of_available_utf_8_transcoders_COUNT;
    short Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_COUNT;
    short Chain_of_available_utf_g_transcoders_COUNT;
    short Chain_of_available_uuid_blocks_COUNT;
    short Chain_of_available_variable_group_update_structures_COUNT;
    short Chain_of_available_variable_simulation_runtime_structures_COUNT;
    short Chain_of_available_virtual_attributes_COUNT;
    short Chain_of_available_walking_menus_states_COUNT;
    short Chain_of_available_wide_string_text_sequences_COUNT;
    short Chain_of_available_widget_pending_states_COUNT;
    short Chain_of_available_workspace_background_spots_COUNT;
    short Chain_of_available_workspace_dock_spots_COUNT;
    short Chain_of_available_workspace_regions_COUNT;
    short Chain_of_available_workspace_views_COUNT;
    short Chain_of_available_workstation_context_frames_COUNT;
    short Chain_of_available_workstation_context_with_selection_focuss_COUNT;
    short Chain_of_available_workstation_contexts_COUNT;
    short Chain_of_available_workstation_events_COUNT;
    short Chain_of_available_workstations_COUNT;
    short Chain_of_available_ws_representation_types_COUNT;
    short Chain_of_available_xml_namespace_lists_COUNT;
    short Chain_of_available_xml_namespaces_COUNT;
    short Chain_of_available_xml_node_lists_COUNT;
    short Chain_of_available_xml_nodes_COUNT;
    short Chain_of_available_xml_structures_COUNT;
    short Chain_of_recycled_edit_states_COUNT;
    short Chaining_refresh_list_COUNT;
    short Chaining_refresh_version_COUNT;
    short Change_the_text_of_attributes_without_category_evaluator_interfaces_p_COUNT;
    short Changing_colors_of_graphic_elements_qm_COUNT;
    short Changing_graph_margins_qm_COUNT;
    short Changing_validity_interval_invalidates_current_value_p_COUNT;
    short Character_bitmap_scratch_list_COUNT;
    short Character_case_mode_for_generalized_dos_COUNT;
    short Character_description_count_COUNT;
    short Character_image_count_COUNT;
    short Character_sequence_token_menu_button_spot_count_COUNT;
    short Characters_in_buffer_of_ok_file_reader_qm_COUNT;
    short Chart_COUNT;
    short Chart_bottom_COUNT;
    short Chart_bottom_margin_COUNT;
    short Chart_class_description_COUNT;
    short Chart_color_value_for_this_raster_COUNT;
    short Chart_current_raster_is_monochrome_raster_list_p_COUNT;
    short Chart_current_raster_is_polychrome_p_COUNT;
    short Chart_data_point_COUNT;
    short Chart_drawing_COUNT;
    short Chart_left_COUNT;
    short Chart_left_margin_COUNT;
    short Chart_origin_x_COUNT;
    short Chart_origin_y_COUNT;
    short Chart_pen_color_COUNT;
    short Chart_pen_color_value_COUNT;
    short Chart_pen_x_COUNT;
    short Chart_pen_y_COUNT;
    short Chart_really_drawing_COUNT;
    short Chart_right_COUNT;
    short Chart_right_margin_COUNT;
    short Chart_spot_count_COUNT;
    short Chart_top_COUNT;
    short Chart_top_margin_COUNT;
    short Chart_tuple_1_maximum_COUNT;
    short Chart_tuple_1_minimum_COUNT;
    short Chart_tuple_2_maximum_COUNT;
    short Chart_tuple_2_minimum_COUNT;
    short Chart_view_count_COUNT;
    short Charting_library_version_qm_COUNT;
    short Check_box_cv_count_COUNT;
    short Check_for_circular_formula_paths_qm_COUNT;
    short Check_icp_handshaking_p_COUNT;
    short Check_time_on_next_uuid_COUNT;
    short Checkable_list_box_cv_count_COUNT;
    short Choice_conflict_COUNT;
    short Class_and_foundation_class_directory_categories_COUNT;
    short Class_bit_numbers_pool_COUNT;
    short Class_change_timestamp_COUNT;
    short Class_definition_class_description_COUNT;
    short Class_description_cons_counter_COUNT;
    short Class_description_count_COUNT;
    short Class_description_for_next_frame_qm_COUNT;
    short Class_file_stream_count_COUNT;
    short Class_info_attributes_COUNT;
    short Class_instance_header_type_of_slot_COUNT;
    short Class_instances_memory_info_count_COUNT;
    short Class_is_undergoing_inheritance_change_qm_COUNT;
    short Class_name_conflicts_COUNT;
    short Class_name_max_length_COUNT;
    short Class_name_read_while_reading_current_ghost_definition_COUNT;
    short Class_specific_instances_lock_COUNT;
    short Class_subscription_count_COUNT;
    short Class_subscriptions_count_COUNT;
    short Classes_and_directory_categories_for_classes_COUNT;
    short Classes_needing_data_interface_initialization_COUNT;
    short Classes_not_defined_in_any_module_COUNT;
    short Classes_of_objects_to_not_consider_qm_COUNT;
    short Classes_remaining_to_sort_COUNT;
    short Classes_sorted_so_far_COUNT;
    short Classes_visited_byte_vector_COUNT;
    short Classes_whose_superiors_are_not_defined_in_required_modules_COUNT;
    short Clear_text_grammar_rules_added_p_COUNT;
    short Clear_text_item_layering_info_COUNT;
    short Clear_text_primitive_value_style_COUNT;
    short Clear_text_saving_problems_were_encountered_p_COUNT;
    short Clipping_rectangles_for_new_data_qm_COUNT;
    short Clock_sequence_for_uuid_COUNT;
    short Clogged_count_COUNT;
    short Close_box_rubber_stamp_widget_COUNT;
    short Close_box_spot_count_COUNT;
    short Closing_procedure_invocation_COUNT;
    short Code_body_COUNT;
    short Code_body_continuation_count_COUNT;
    short Code_body_entries_in_compilation_COUNT;
    short Code_body_invocation_count_COUNT;
    short Collected_frame_notes_for_class_export_qm_COUNT;
    short Collected_items_with_warnings_alist_COUNT;
    short Collected_menu_content_structure_COUNT;
    short Collected_updates_to_sensor_attributes_COUNT;
    short Collecting_denotation_errors_p_COUNT;
    short Collecting_exported_method_text_p_COUNT;
    short Collecting_frame_notes_for_class_export_p_COUNT;
    short Collecting_free_references_COUNT;
    short Collecting_procedures_to_warn_about_p_COUNT;
    short Collecting_updates_to_sensor_attributes_p_COUNT;
    short Collecting_warnings_p_COUNT;
    short Color_change_indicator_COUNT;
    short Color_changes_indicator_COUNT;
    short Color_code_differences_COUNT;
    short Color_difference_for_line_of_text_of_graphic_element_COUNT;
    short Color_hierarchy_COUNT;
    short Color_map_count_COUNT;
    short Color_parameters_COUNT;
    short Color_values_of_graph_rasters_of_graphic_element_COUNT;
    short Column_COUNT;
    short Column_maximum_COUNT;
    short Column_width_COUNT;
    short Combiners_for_defun_incremental_COUNT;
    short Command_line_qm_COUNT;
    short Comp_trace_level_COUNT;
    short Compare_xml_collect_diffs_p_COUNT;
    short Compilation_local_name_listed_next_symbol_COUNT;
    short Compilation_local_name_symbol_counter_COUNT;
    short Compilation_local_name_symbol_supply_COUNT;
    short Compilations_were_removed_in_this_kb_module_qm_COUNT;
    short Compile_reference_to_system_slot_COUNT;
    short Compiled_antecedent_1_COUNT;
    short Compiled_cell_expression_COUNT;
    short Compiled_code_grammar_rules_added_p_COUNT;
    short Compiled_consequent_1_COUNT;
    short Compiled_consequent_2_COUNT;
    short Compiled_item_being_analyzed_COUNT;
    short Compiled_item_being_analyzed_started_out_incomplete_qm_COUNT;
    short Compiled_items_deferred_for_analysis_COUNT;
    short Compiled_kb_indent_COUNT;
    short Compiled_kb_initialization_array_initialized_p_COUNT;
    short Compiled_resource_count_COUNT;
    short Compiler_code_body_entry_count_COUNT;
    short Compiler_cons_counter_COUNT;
    short Compiler_errors_COUNT;
    short Compiler_free_references_COUNT;
    short Compiler_warnings_COUNT;
    short Compiling_antecedent_p_COUNT;
    short Compiling_expression_p_COUNT;
    short Compiling_incomplete_items_after_analyze_p_COUNT;
    short Compiling_rule_p_COUNT;
    short Complete_kb_name_qm_COUNT;
    short Component_change_report_count_COUNT;
    short Compound_fixnum_simulation_time_count_COUNT;
    short Compound_slot_descriptor_count_COUNT;
    short Compound_type_descriptor_count_COUNT;
    short Computation_frame_at_breakpoint_COUNT;
    short Computation_instance_at_breakpoint_COUNT;
    short Computation_instance_count_COUNT;
    short Computation_style_description_COUNT;
    short Compute_menu_items_list_COUNT;
    short Conclude_attribute_binding_listed_next_symbol_COUNT;
    short Conclude_attribute_binding_symbol_counter_COUNT;
    short Conclude_attribute_binding_symbol_supply_COUNT;
    short Conclude_parent_attribute_bindings_COUNT;
    short Conditional_selected_choice_qm_COUNT;
    short Conditional_termination_state_qm_COUNT;
    short Connected_subnet_COUNT;
    short Connection_class_description_COUNT;
    short Connection_classes_warned_about_for_this_kb_COUNT;
    short Connection_cons_counter_COUNT;
    short Connection_count_COUNT;
    short Connection_definition_class_description_COUNT;
    short Connection_handling_block_queue_COUNT;
    short Connection_handling_connection_queue_COUNT;
    short Connection_handling_connection_type_queue_COUNT;
    short Connection_handling_fsn_queue_COUNT;
    short Connection_handling_procedure_fsn_qm_COUNT;
    short Connection_handling_procedure_qm_COUNT;
    short Connection_handling_window_queue_COUNT;
    short Connection_item_count_COUNT;
    short Connection_post_class_description_COUNT;
    short Connection_spot_count_COUNT;
    short Connection_subrectangle_structure_count_COUNT;
    short Connections_in_connection_paths_COUNT;
    short Connections_in_modules_a_list_COUNT;
    short Connections_to_be_excluded_qm_COUNT;
    short Connections_to_delete_after_reading_kb_COUNT;
    short Consider_asian_language_initializations_qm_COUNT;
    short Consistency_tree_focus_shifts_COUNT;
    short Contains_either_really_transient_or_proprietary_p_1_COUNT;
    short Contains_proprietary_p_1_COUNT;
    short Context_iteration_forms_COUNT;
    short Context_of_type_failure_COUNT;
    short Continuation_task_for_current_backup_COUNT;
    short Continue_current_kb_save_failure_COUNT;
    short Contour_of_ok_file_tokens_COUNT;
    short Control_sequence_record_COUNT;
    short Control_stack_of_frame_projecting_COUNT;
    short Convert_file_strings_to_uppercase_p_COUNT;
    short Copyright_boilerplate_lines_of_text_1_COUNT;
    short Copyright_boilerplate_lines_of_text_2_COUNT;
    short Corresponding_icp_object_index_for_item_new_copy_COUNT;
    short Corresponding_icp_object_index_for_item_reference_COUNT;
    short Count_of_8859_reverse_unicode_map_hash_vector_43_vectors_COUNT;
    short Count_of_blocks_hash_hash_vector_43_vectors_COUNT;
    short Count_of_call_hash_hash_vector_43_vectors_COUNT;
    short Count_of_duplicates_check_hash_table_hash_vector_50021_vectors_COUNT;
    short Count_of_dynamic_rule_displays_hash_vector_43_vectors_COUNT;
    short Count_of_foreign_function_registry_internal_hash_vector_131_vectors_COUNT;
    short Count_of_frame_serial_number_to_item_table_hash_vector_67_vectors_COUNT;
    short Count_of_generic_rule_instance_displays_hash_vector_43_vectors_COUNT;
    short Count_of_gfi_spreadsheet_field_index_hash_vector_131_vectors_COUNT;
    short Count_of_graph_node_of_graphed_thing_hash_vector_43_vectors_COUNT;
    short Count_of_hashed_rule_instance_hash_vector_43_vectors_COUNT;
    short Count_of_indexed_attribute_parent_objects_hash_vector_43_vectors_COUNT;
    short Count_of_interned_gensym_strings_COUNT;
    short Count_of_interned_text_strings_COUNT;
    short Count_of_item_or_name_hash_hash_vector_43_vectors_COUNT;
    short Count_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors_COUNT;
    short Count_of_jis_map_hash_vector_307_vectors_COUNT;
    short Count_of_kanji_font_cache_vector_137_vectors_COUNT;
    short Count_of_kb_fsn_hash_table_hash_vector_131_vectors_COUNT;
    short Count_of_module_required_by_relationships_hash_vector_43_vectors_COUNT;
    short Count_of_native_font_set_width_equivalence_table_256_vectors_COUNT;
    short Count_of_native_icon_handle_hash_vector_43_vectors_COUNT;
    short Count_of_nms_menu_for_hmenu_hash_vector_43_vectors_COUNT;
    short Count_of_non_kanji_font_vector_257_vectors_COUNT;
    short Count_of_object_circularity_hashtable_hash_vector_131_vectors_COUNT;
    short Count_of_pending_workspace_drawing_COUNT;
    short Count_of_procedure_invocations_hash_vector_43_vectors_COUNT;
    short Count_of_representation_handle_hash_vector_109_vectors_COUNT;
    short Count_of_scaled_font_kanji_font_cache_vector_1096_vectors_COUNT;
    short Count_of_scaled_font_non_kanji_font_vector_2049_vectors_COUNT;
    short Count_of_sexp_annotation_hash_vector_43_vectors_COUNT;
    short Count_of_sub_call_hash_hash_vector_43_vectors_COUNT;
    short Count_of_subseries_of_values_64_vectors_COUNT;
    short Count_of_sysproc_continuation_hashtable_hash_vector_131_vectors_COUNT;
    short Count_of_tracked_items_call_vector_table_hash_vector_43_vectors_COUNT;
    short Count_of_ui_callback_table_hash_vector_43_vectors_COUNT;
    short Count_of_uo_memory_usage_information_hash_vector_43_vectors_COUNT;
    short Count_of_user_hash_table_internal_hash_vector_43_vectors_COUNT;
    short Count_of_variable_fill_icp_buffer_4096_vectors_COUNT;
    short Countdown_for_checking_COUNT;
    short Create_frames_and_connections_reading_past_qm_COUNT;
    short Create_process_instance_for_current_process_p_COUNT;
    short Create_subpart_upon_tracking_p_COUNT;
    short Created_oversized_simple_float_array_pool_arrays_COUNT;
    short Created_simple_float_array_pool_arrays_COUNT;
    short Created_simple_long_array_pool_arrays_COUNT;
    short Created_simple_vector_pool_vectors_COUNT;
    short Credits_table_spot_count_COUNT;
    short Ctlc_cons_count_COUNT;
    short Cumulative_x_scaled_connection_stripe_half_width_COUNT;
    short Cumulative_x_scaled_connection_stripe_width_COUNT;
    short Cumulative_y_scaled_connection_stripe_half_width_COUNT;
    short Cumulative_y_scaled_connection_stripe_width_COUNT;
    short Current_2d_rendering_COUNT;
    short Current_2d_state_COUNT;
    short Current_a_matrix_COUNT;
    short Current_ab_font_qm_COUNT;
    short Current_agenda_accumulating_COUNT;
    short Current_anchor_p_COUNT;
    short Current_annotated_frame_COUNT;
    short Current_attribute_description_class_COUNT;
    short Current_attribute_description_index_COUNT;
    short Current_attribute_file_pathname_qm_COUNT;
    short Current_axis_COUNT;
    short Current_axis_pane_COUNT;
    short Current_b_vector_COUNT;
    short Current_background_color_value_COUNT;
    short Current_background_process_COUNT;
    short Current_backup_definition_workspace_qm_COUNT;
    short Current_backup_definition_workspace_serial_number_qm_COUNT;
    short Current_basic_part_COUNT;
    short Current_best_match_for_eyes_COUNT;
    short Current_block_of_dependent_frame_COUNT;
    short Current_callback_representation_subscription_handle_COUNT;
    short Current_cascaded_ring_buffer_COUNT;
    short Current_category_name_for_type_specification_type_p_COUNT;
    short Current_category_visit_stamp_COUNT;
    short Current_cell_COUNT;
    short Current_character_COUNT;
    short Current_character_index_after_token_COUNT;
    short Current_character_syntax_table_COUNT;
    short Current_chart_COUNT;
    short Current_chart_data_point_COUNT;
    short Current_chart_frame_COUNT;
    short Current_chart_raster_color_value_COUNT;
    short Current_code_body_entry_COUNT;
    short Current_color_map_COUNT;
    short Current_column_COUNT;
    short Current_compiled_cell_expression_COUNT;
    short Current_component_type_for_sorting_COUNT;
    short Current_computation_activity_COUNT;
    short Current_computation_component_particulars_COUNT;
    short Current_computation_flags_COUNT;
    short Current_computation_frame_COUNT;
    short Current_computation_instance_COUNT;
    short Current_computation_slot_component_group_COUNT;
    short Current_computation_style_COUNT;
    short Current_computation_style_description_COUNT;
    short Current_conclude_frame_list_COUNT;
    short Current_conclude_innermost_attribute_description_COUNT;
    short Current_conclude_innermost_frame_COUNT;
    short Current_conclude_innermost_item_index_COUNT;
    short Current_connection_path_COUNT;
    short Current_create_frame_description_reference_1_COUNT;
    short Current_custom_reclamation_stamp_qm_COUNT;
    short Current_cvs_command_COUNT;
    short Current_data_buffer_for_plot_COUNT;
    short Current_data_series_COUNT;
    short Current_ddd_dot_dddd_format_qm_COUNT;
    short Current_default_line_color_COUNT;
    short Current_delta_COUNT;
    short Current_description_of_new_table_COUNT;
    short Current_dialog_errors_structure_COUNT;
    short Current_directory_of_binary_truenames_COUNT;
    short Current_directory_of_source_truenames_qm_COUNT;
    short Current_display_pane_bottom_COUNT;
    short Current_display_pane_height_COUNT;
    short Current_display_pane_left_COUNT;
    short Current_display_pane_right_COUNT;
    short Current_display_pane_top_COUNT;
    short Current_display_pane_width_COUNT;
    short Current_dragging_states_COUNT;
    short Current_draw_document_p_COUNT;
    short Current_draw_paper_p_COUNT;
    short Current_drawing_priority_COUNT;
    short Current_drawing_transfer_mode_COUNT;
    short Current_edit_state_COUNT;
    short Current_edit_workspace_COUNT;
    short Current_environment_COUNT;
    short Current_extended_utf_g_low_half_character_qm_COUNT;
    short Current_filters_search_result_COUNT;
    short Current_foreground_color_value_COUNT;
    short Current_foreign_function_call_info_COUNT;
    short Current_foreign_image_pathname_qm_COUNT;
    short Current_formatted_part_COUNT;
    short Current_frame_serial_number_COUNT;
    short Current_frame_serial_number_before_reading_COUNT;
    short Current_frame_transform_qm_COUNT;
    short Current_g2_rdf_module_COUNT;
    short Current_g2_time_COUNT;
    short Current_g2_user_mode_qm_COUNT;
    short Current_g2_window_for_this_workstation_qm_COUNT;
    short Current_g2binary_file_symbol_index_COUNT;
    short Current_g2gl_definition_COUNT;
    short Current_gensym_string_COUNT;
    short Current_gensym_window_serial_number_COUNT;
    short Current_gesture_code_sequence_COUNT;
    short Current_gesture_code_sequences_COUNT;
    short Current_gesture_frame_pointer_COUNT;
    short Current_gesture_label_index_COUNT;
    short Current_gesture_sequence_index_COUNT;
    short Current_gesture_stack_pointer_COUNT;
    short Current_grammar_COUNT;
    short Current_graph_grid_COUNT;
    short Current_graph_grid_in_minimal_update_COUNT;
    short Current_graph_layout_hashing_function_COUNT;
    short Current_graph_rendering_COUNT;
    short Current_graph_rendering_embedded_icons_COUNT;
    short Current_graph_rendering_structure_COUNT;
    short Current_grid_COUNT;
    short Current_grid_painting_actions_to_delete_COUNT;
    short Current_grid_painting_background_color_value_COUNT;
    short Current_grid_painting_color_mode_COUNT;
    short Current_grid_painting_earliest_time_COUNT;
    short Current_grid_painting_foreground_color_value_COUNT;
    short Current_grid_painting_is_full_qm_COUNT;
    short Current_grid_painting_latest_time_COUNT;
    short Current_grid_painting_mode_COUNT;
    short Current_grid_painting_queue_COUNT;
    short Current_grid_painting_queue_tail_COUNT;
    short Current_grid_painting_x_scale_COUNT;
    short Current_grid_painting_y_scale_COUNT;
    short Current_height_of_formatted_part_COUNT;
    short Current_hfep_c_act_COUNT;
    short Current_hfep_c_state_COUNT;
    short Current_hfep_cchar_COUNT;
    short Current_hfep_nchar_COUNT;
    short Current_icon_editor_COUNT;
    short Current_icon_editor_event_COUNT;
    short Current_icon_editor_workspace_COUNT;
    short Current_icon_substitution_list_COUNT;
    short Current_icon_untransformed_height_COUNT;
    short Current_icon_untransformed_width_COUNT;
    short Current_icon_variables_override_plist_COUNT;
    short Current_icon_variables_plist_COUNT;
    short Current_icp_buffer_COUNT;
    short Current_icp_port_COUNT;
    short Current_icp_read_trace_level_COUNT;
    short Current_icp_socket_COUNT;
    short Current_icp_write_trace_level_COUNT;
    short Current_image_plane_COUNT;
    short Current_image_plane_for_button_COUNT;
    short Current_image_plane_qm_COUNT;
    short Current_image_x_scale_COUNT;
    short Current_image_y_scale_COUNT;
    short Current_include_denotation_for_block_flag_COUNT;
    short Current_index_COUNT;
    short Current_index_array_COUNT;
    short Current_indicator_for_category_of_symbol_token_COUNT;
    short Current_indicator_for_category_of_this_name_COUNT;
    short Current_input_stack_COUNT;
    short Current_invocation_remotely_started_p_COUNT;
    short Current_jemit_args_COUNT;
    short Current_jemit_class_description_COUNT;
    short Current_jemit_class_object_table_COUNT;
    short Current_jemit_compound_statement_list_COUNT;
    short Current_jemit_indent_COUNT;
    short Current_jemit_locals_COUNT;
    short Current_jemit_node_stack_COUNT;
    short Current_jemit_return_type_specification_qm_COUNT;
    short Current_jemit_self_name_COUNT;
    short Current_jemit_stream_COUNT;
    short Current_jemit_text_style_qm_COUNT;
    short Current_kb_file_progress_for_modules_qm_COUNT;
    short Current_kb_pathname_qm_COUNT;
    short Current_kb_save_COUNT;
    short Current_kb_serial_number_COUNT;
    short Current_kb_specific_property_list_property_name_COUNT;
    short Current_kind_of_change_COUNT;
    short Current_let_action_bindings_COUNT;
    short Current_lexing_patterns_COUNT;
    short Current_lexing_rule_number_COUNT;
    short Current_lexing_strings_COUNT;
    short Current_line_index_for_end_of_token_COUNT;
    short Current_linearized_kb_required_modules_COUNT;
    short Current_localization_domains_qm_COUNT;
    short Current_localization_purpose_qm_COUNT;
    short Current_logbook_qm_COUNT;
    short Current_logbook_serial_number_qm_COUNT;
    short Current_long_operation_notification_workspace_COUNT;
    short Current_lookup_data_COUNT;
    short Current_lr_states_COUNT;
    short Current_lu_matrix_COUNT;
    short Current_machine_ids_of_g2_ok_file_qm_COUNT;
    short Current_message_board_qm_COUNT;
    short Current_message_serial_number_COUNT;
    short Current_message_unix_time_qm_COUNT;
    short Current_minimal_grid_draw_has_seen_one_image_plane_p_COUNT;
    short Current_model_definition_qm_COUNT;
    short Current_model_queue_qm_COUNT;
    short Current_model_runtime_info_qm_COUNT;
    short Current_modularity_problems_COUNT;
    short Current_modularity_problems_fatal_qm_COUNT;
    short Current_module_being_saved_COUNT;
    short Current_module_data_COUNT;
    short Current_module_directory_binding_alist_COUNT;
    short Current_module_lisp_binary_filename_COUNT;
    short Current_module_pathname_override_binding_alist_COUNT;
    short Current_module_qm_COUNT;
    short Current_module_source_filename_COUNT;
    short Current_native_image_plane_COUNT;
    short Current_native_simple_dialog_handle_COUNT;
    short Current_native_window_qm_COUNT;
    short Current_network_interface_COUNT;
    short Current_new_table_COUNT;
    short Current_nonterminals_COUNT;
    short Current_painting_action_COUNT;
    short Current_pane_COUNT;
    short Current_parse_table_COUNT;
    short Current_parsing_context_character_COUNT;
    short Current_parsing_context_line_COUNT;
    short Current_parsing_context_qm_COUNT;
    short Current_parsing_context_text_COUNT;
    short Current_parsing_context_text_length_COUNT;
    short Current_parsing_contexts_COUNT;
    short Current_part_description_COUNT;
    short Current_plot_COUNT;
    short Current_plot_number_COUNT;
    short Current_post_mortem_ring_buffer_COUNT;
    short Current_post_mortem_ring_buffer_length_COUNT;
    short Current_process_handle_COUNT;
    short Current_productions_COUNT;
    short Current_profile_structure_qm_COUNT;
    short Current_projection_function_for_funcall_COUNT;
    short Current_read_icp_byte_position_COUNT;
    short Current_real_time_COUNT;
    short Current_receiving_resumable_object_COUNT;
    short Current_region_maximum_x_COUNT;
    short Current_region_maximum_y_COUNT;
    short Current_region_minimum_x_COUNT;
    short Current_region_minimum_y_COUNT;
    short Current_remote_procedure_identifier_COUNT;
    short Current_remote_search_representation_qm_COUNT;
    short Current_resumable_icp_read_task_COUNT;
    short Current_return_values_position_COUNT;
    short Current_ri_completion_notification_collection_qm_COUNT;
    short Current_row_COUNT;
    short Current_rule_local_name_reference_info_COUNT;
    short Current_saving_context_COUNT;
    short Current_saving_context_qm_COUNT;
    short Current_schedule_task_COUNT;
    short Current_score_of_best_match_for_eyes_COUNT;
    short Current_scratchpad_color_value_list_COUNT;
    short Current_scratchpad_raster_COUNT;
    short Current_scratchpad_raster_depth_COUNT;
    short Current_scratchpad_raster_height_COUNT;
    short Current_scratchpad_raster_list_COUNT;
    short Current_scratchpad_raster_tiled_p_COUNT;
    short Current_scratchpad_raster_type_COUNT;
    short Current_scratchpad_raster_width_COUNT;
    short Current_simulation_category_COUNT;
    short Current_simulation_runtime_structure_COUNT;
    short Current_slice_size_qm_COUNT;
    short Current_slot_value_of_user_slot_COUNT;
    short Current_source_line_COUNT;
    short Current_source_nupec_synchronization_COUNT;
    short Current_standard_icp_object_index_space_COUNT;
    short Current_start_state_COUNT;
    short Current_state_stack_COUNT;
    short Current_statistics_file_pathname_qm_COUNT;
    short Current_style_if_other_than_default_COUNT;
    short Current_subcategory_path_COUNT;
    short Current_subscribe_innermost_class_COUNT;
    short Current_subscribe_innermost_item_index_COUNT;
    short Current_system_being_loaded_COUNT;
    short Current_system_dummy_workstation_qm_COUNT;
    short Current_system_name_COUNT;
    short Current_system_rpc_icp_socket_qm_COUNT;
    short Current_system_version_COUNT;
    short Current_t2_dialog_sequence_number_COUNT;
    short Current_table_updates_task_qm_COUNT;
    short Current_target_nupec_synchronization_COUNT;
    short Current_task_to_run_propagate_all_workspace_changes_to_image_planes_COUNT;
    short Current_telewindows_workstation_COUNT;
    short Current_temporary_g2gl_values_COUNT;
    short Current_temporary_icp_object_index_space_COUNT;
    short Current_terminals_COUNT;
    short Current_text_box_format_COUNT;
    short Current_text_cell_plist_COUNT;
    short Current_text_focus_for_eyes_qm_COUNT;
    short Current_text_tokenization_state_COUNT;
    short Current_thing_changed_COUNT;
    short Current_thread_index_COUNT;
    short Current_token_stack_COUNT;
    short Current_tokenizer_COUNT;
    short Current_tracking_subcomponent_COUNT;
    short Current_tracking_x_in_window_COUNT;
    short Current_tracking_y_in_window_COUNT;
    short Current_transform_constituent_array_COUNT;
    short Current_transform_constituent_count_COUNT;
    short Current_trend_chart_COUNT;
    short Current_trend_chart_has_remote_representation_p_COUNT;
    short Current_twriting_output_type_COUNT;
    short Current_ui_client_session_COUNT;
    short Current_wide_string_COUNT;
    short Current_wide_string_list_COUNT;
    short Current_width_of_formatted_part_COUNT;
    short Current_window_COUNT;
    short Current_workspace_on_image_plane_qm_COUNT;
    short Current_workstation_COUNT;
    short Current_workstation_context_COUNT;
    short Current_workstation_detail_pane_COUNT;
    short Current_workstation_event_COUNT;
    short Current_workstation_native_window_qm_COUNT;
    short Current_workstation_window_COUNT;
    short Current_write_icp_byte_position_COUNT;
    short Current_x_for_eyes_qm_COUNT;
    short Current_x_max_for_stored_raster_qm_COUNT;
    short Current_x_offset_for_stored_raster_qm_COUNT;
    short Current_x_origin_of_drawing_COUNT;
    short Current_x_vector_COUNT;
    short Current_xml_structures_COUNT;
    short Current_y_for_eyes_qm_COUNT;
    short Current_y_max_for_stored_raster_qm_COUNT;
    short Current_y_offset_for_stored_raster_qm_COUNT;
    short Current_y_origin_of_drawing_COUNT;
    short Currently_active_event_handlers_via_object_configuration_COUNT;
    short Currently_automatically_resolving_class_name_conflicts_qm_COUNT;
    short Currently_exposed_workspaces_COUNT;
    short Currently_jump_out_of_drawing_image_plane_when_empty_rectangle_p_COUNT;
    short Currently_loading_modules_qm_COUNT;
    short Currently_posting_message_on_logbook_p_COUNT;
    short Currently_supressing_part_highlighting_COUNT;
    short Currently_tracking_subcategory_path_max_COUNT;
    short Currently_within_make_transient_instruction_p_COUNT;
    short Currently_working_on_drawing_p_COUNT;
    short Currently_working_on_drawing_workspace_COUNT;
    short Custom_dialog_cons_counter_COUNT;
    short Cvs_command_initial_timeout_COUNT;
    short Cvs_command_timed_out_p_COUNT;
    short Daily_countdown_COUNT;
    short Data_point_first_x_COUNT;
    short Data_point_first_y_COUNT;
    short Data_point_index_COUNT;
    short Data_point_indicator_COUNT;
    short Data_point_indicator_projection_function_COUNT;
    short Data_point_last_x_COUNT;
    short Data_point_last_y_COUNT;
    short Data_point_show_connecting_line_COUNT;
    short Data_point_show_indicator_COUNT;
    short Data_point_tuple_1_COUNT;
    short Data_point_tuple_2_COUNT;
    short Data_point_tuple_valid_qm_COUNT;
    short Data_point_value_COUNT;
    short Data_point_value_and_collection_time_interned_list_COUNT;
    short Data_point_value_interned_list_COUNT;
    short Data_point_x_COUNT;
    short Data_point_y_COUNT;
    short Data_series_COUNT;
    short Data_series_connect_first_and_last_point_COUNT;
    short Data_series_data_cache_1_qm_COUNT;
    short Data_series_data_cache_2_qm_COUNT;
    short Data_series_failed_to_compile_COUNT;
    short Data_series_generator_info_1_COUNT;
    short Data_series_generator_info_2_COUNT;
    short Data_series_illustration_kind_COUNT;
    short Data_series_index_COUNT;
    short Data_series_info_1_COUNT;
    short Data_series_info_2_COUNT;
    short Data_series_source_kind_COUNT;
    short Data_series_subparts_COUNT;
    short Data_server_count_COUNT;
    short Data_server_error_code_alist_COUNT;
    short Data_server_parameters_COUNT;
    short Data_server_pretty_name_alist_COUNT;
    short Date_format_count_COUNT;
    short Datum_type_COUNT;
    short Day_of_the_week_names_COUNT;
    short Deadman_switch_time_interval_COUNT;
    short Debug_1_COUNT;
    short Debug_10_COUNT;
    short Debug_11_COUNT;
    short Debug_12_COUNT;
    short Debug_2_COUNT;
    short Debug_3_COUNT;
    short Debug_4_COUNT;
    short Debug_5_COUNT;
    short Debug_6_COUNT;
    short Debug_7_COUNT;
    short Debug_8_COUNT;
    short Debug_9_COUNT;
    short Debug_out_of_synch_COUNT;
    short Debug_print_byte_code_pc_p_COUNT;
    short Debugging_consing_COUNT;
    short Debugging_name_index_COUNT;
    short Debugging_parameters_COUNT;
    short Debugging_reset_COUNT;
    short Decache_attribute_description_lists_of_interned_lists_function_COUNT;
    short Decache_occurred_since_last_update_qm_COUNT;
    short Default_accept_timeout_COUNT;
    short Default_axis_data_series_instance_COUNT;
    short Default_duration_for_data_point_COUNT;
    short Default_entity_line_drawing_description_template_COUNT;
    short Default_fin_length_COUNT;
    short Default_float_to_text_format_COUNT;
    short Default_format_structure_COUNT;
    short Default_g2_hangul_star_pathname_COUNT;
    short Default_g2_init_pathname_COUNT;
    short Default_g2_kanji_star_pathname_COUNT;
    short Default_g2_kb_pathname_COUNT;
    short Default_g2_minm_star_pathname_COUNT;
    short Default_g2_module_map_pathname_COUNT;
    short Default_g2_ok_pathname_COUNT;
    short Default_g2v11_ok_pathname_COUNT;
    short Default_g2v12_ok_pathname_COUNT;
    short Default_g2v51_ok_pathname_COUNT;
    short Default_g2v5_ok_pathname_COUNT;
    short Default_g2v6_ok_pathname_COUNT;
    short Default_g2v7_ok_pathname_COUNT;
    short Default_g2v83_ok_pathname_COUNT;
    short Default_g2v8_ok_pathname_COUNT;
    short Default_g2v9_ok_pathname_COUNT;
    short Default_graph_line_color_value_COUNT;
    short Default_icon_slot_group_COUNT;
    short Default_junction_class_description_COUNT;
    short Default_kb_pathname_qm_COUNT;
    short Default_language_COUNT;
    short Default_maximum_icon_bitmap_memory_COUNT;
    short Default_maximum_icon_bitmaps_COUNT;
    short Default_most_recent_bandwidth_per_timeslice_COUNT;
    short Default_size_of_spacial_index_COUNT;
    short Default_stub_length_COUNT;
    short Default_text_conversion_style_COUNT;
    short Default_tw_hangul_star_pathname_COUNT;
    short Default_tw_kanji_star_pathname_COUNT;
    short Default_tw_minm_star_pathname_COUNT;
    short Default_tw_ok_pathname_COUNT;
    short Default_twv11_ok_pathname_COUNT;
    short Default_twv12_ok_pathname_COUNT;
    short Default_twv5_ok_pathname_COUNT;
    short Default_twv6_ok_pathname_COUNT;
    short Default_twv7_ok_pathname_COUNT;
    short Default_twv8_ok_pathname_COUNT;
    short Default_twv9_ok_pathname_COUNT;
    short Defaults_namestring_for_directory_of_names_qm_COUNT;
    short Defer_consistency_analysis_qm_COUNT;
    short Defer_notifications_qm_COUNT;
    short Deferred_class_definitions_alist_COUNT;
    short Deferred_errors_for_class_export_qm_COUNT;
    short Deferred_update_count_COUNT;
    short Deferring_errors_for_class_export_p_COUNT;
    short Defined_evaluation_datum_types_COUNT;
    short Defined_evaluation_value_types_COUNT;
    short Definition_being_analyzed_for_savability_COUNT;
    short Definition_class_description_COUNT;
    short Definition_with_subclass_or_instance_in_kb_hierarchy_COUNT;
    short Definitions_for_saving_COUNT;
    short Definitions_in_module_COUNT;
    short Definitions_in_module_to_go_COUNT;
    short Definitions_not_required_COUNT;
    short Definitions_read_in_this_module_COUNT;
    short Definitions_that_have_been_visited_COUNT;
    short Defun_incremental_compile_time_registry_COUNT;
    short Defun_incremental_runtime_registry_COUNT;
    short Defvar_for_informational_tests_for_mhd_COUNT;
    short Delay_item_array_initializations_p_COUNT;
    short Delayed_item_array_initializations_COUNT;
    short Delete_as_item_referring_to_name_qm_COUNT;
    short Delete_compiled_kb_source_p_COUNT;
    short Delete_connections_without_leaving_stubs_qm_COUNT;
    short Delete_corresponding_object_qm_COUNT;
    short Delete_files_after_external_diff_p_COUNT;
    short Delete_old_elements_from_arrays_and_lists_COUNT;
    short Deleting_ui_client_interfaces_for_clear_kb_COUNT;
    short Denotation_error_list_COUNT;
    short Denotation_size_vector_COUNT;
    short Dependent_frame_class_description_COUNT;
    short Depth_of_post_mortem_checkpoint_reporting_COUNT;
    short Deregister_and_register_item_p_COUNT;
    short Deregister_but_do_not_remove_from_table_p_COUNT;
    short Deregister_corresponding_object_qm_COUNT;
    short Derived_icp_input_port_COUNT;
    short Derived_icp_output_port_COUNT;
    short Designation_marker_COUNT;
    short Designations_from_explicit_iteration_forms_COUNT;
    short Designations_in_rule_COUNT;
    short Desired_distance_between_fins_COUNT;
    short Desired_distance_between_fins_on_link_COUNT;
    short Desired_high_value_for_horizontal_axis_COUNT;
    short Desired_high_value_for_vertical_axis_COUNT;
    short Desired_low_value_for_horizontal_axis_COUNT;
    short Desired_low_value_for_vertical_axis_COUNT;
    short Desired_parent_of_native_window_qm_COUNT;
    short Destination_for_symbol_with_preserved_cells_COUNT;
    short Detail_pane_spot_count_COUNT;
    short Development_world_save_p_COUNT;
    short Dial_class_description_COUNT;
    short Dial_spot_count_COUNT;
    short Dialog_button_class_description_COUNT;
    short Dialog_component_count_COUNT;
    short Dialog_errors_structure_count_COUNT;
    short Dialog_state_count_COUNT;
    short Dialog_view_count_COUNT;
    short Dialogs_error_handling_COUNT;
    short Digital_clock_class_description_COUNT;
    short Digits_of_extremal_fixnum_as_string_COUNT;
    short Digits_of_largest_float_as_string_COUNT;
    short Digits_of_most_negative_fixnum_as_string_COUNT;
    short Digits_of_most_positive_fixnum_as_string_COUNT;
    short Digits_of_smallest_normalized_float_as_string_COUNT;
    short Directory_nil_COUNT;
    short Directory_of_built_in_menu_choices_COUNT;
    short Disable_parameter_strings_for_internal_proprietary_procedures_COUNT;
    short Disable_resumability_COUNT;
    short Disable_stack_error_COUNT;
    short Disable_subworkspace_connection_posts_COUNT;
    short Disable_tracing_and_breakpoints_warning_COUNT;
    short Disable_update_button_COUNT;
    short Disassemble_enabled_qm_COUNT;
    short Display_pane_count_COUNT;
    short Distance_to_snap_points_together_in_view_pad_COUNT;
    short Distribute_selection_command_operations_COUNT;
    short Do_backpatching_COUNT;
    short Do_circularity_check_walking_through_conses_p_COUNT;
    short Do_circularity_check_walking_through_simple_vectors_p_COUNT;
    short Do_g2_init_file_qm_COUNT;
    short Do_icp_flow_control_qm_COUNT;
    short Do_not_allow_user_interactions_during_kb_load_qm_COUNT;
    short Do_not_error_in_x11_create_pixmap_on_failed_allocation_COUNT;
    short Do_not_initialize_g2_array_elements_p_COUNT;
    short Do_not_initialize_specializations_COUNT;
    short Do_not_invoke_rules_for_user_icon_movement_qm_COUNT;
    short Do_not_load_modules_p_COUNT;
    short Do_not_note_permanent_changes_p_COUNT;
    short Do_not_notify_user_during_kb_load_qm_COUNT;
    short Do_not_reclaim_runs_while_inactive_entries_COUNT;
    short Do_not_restore_image_planes_qm_COUNT;
    short Do_not_show_conflicts_during_kb_load_qm_COUNT;
    short Do_not_stop_search_once_found_qm_COUNT;
    short Do_not_update_file_progress_display_qm_COUNT;
    short Do_not_update_frame_authors_qm_COUNT;
    short Do_not_update_selection_highlights_COUNT;
    short Do_not_update_simulated_value_qm_COUNT;
    short Doing_g2_init_file_p_COUNT;
    short Doing_g2_init_kb_p_COUNT;
    short Doing_long_operation_with_notification_qm_COUNT;
    short Doing_password_change_p_COUNT;
    short Dont_backward_chain_in_sim_eval_qm_COUNT;
    short Dont_cerror_for_slot_changes_while_on_window_qm_COUNT;
    short Dont_include_offset_for_end_position_qm_COUNT;
    short Dont_load_if_definitions_have_changed_p_COUNT;
    short Dont_proceed_to_next_variable_qm_COUNT;
    short Drag_handle_state_count_COUNT;
    short Dragging_cons_counter_COUNT;
    short Dragging_state_count_COUNT;
    short Drawing_is_locked_qm_COUNT;
    short Drawing_on_window_COUNT;
    short Drawing_parameters_COUNT;
    short Drawing_state_for_project_paper_COUNT;
    short Drawing_task_count_COUNT;
    short Drawing_to_printer_p_COUNT;
    short Dummy_evaluators_list_COUNT;
    short Dummy_place_for_chestnut_internals_COUNT;
    short Duplicate_local_names_already_reported_COUNT;
    short Duplicates_check_hash_COUNT;
    short Duration_cv_count_COUNT;
    short During_ffi_call_qm_COUNT;
    short Dynamic_dialog_count_COUNT;
    short Dynamic_menus_modification_tick_COUNT;
    short Dynamic_rule_display_hash_table_COUNT;
    short Dynamic_workspace_associated_structure_count_COUNT;
    short Echo_dialog_spec_p_COUNT;
    short Edit_box_change_count_COUNT;
    short Edit_box_class_description_COUNT;
    short Edit_box_spot_count_COUNT;
    short Edit_cache_count_COUNT;
    short Edit_menu_state_count_COUNT;
    short Edit_state_count_COUNT;
    short Edit_states_COUNT;
    short Edit_type_alias_mapping_COUNT;
    short Editing_context_COUNT;
    short Editing_new_table_COUNT;
    short Editor_background_color_override_qm_COUNT;
    short Editor_caption_text_override_qm_COUNT;
    short Editor_font_size_override_qm_COUNT;
    short Editor_frame_style_override_qm_COUNT;
    short Editor_initial_editor_height_override_qm_COUNT;
    short Editor_parameters_COUNT;
    short Editor_prompt_filter_qm_COUNT;
    short Editor_scroll_decision_override_qm_COUNT;
    short Editor_specific_natural_language_override_qm_COUNT;
    short Editor_text_color_override_qm_COUNT;
    short Editor_toolbar_user_callback_COUNT;
    short Editor_window_handle_COUNT;
    short Effectively_infinite_region_COUNT;
    short Element_of_foreign_linking_info_count_COUNT;
    short Elevator_of_scroll_bar_spot_count_COUNT;
    short Elevator_shaft_spot_count_COUNT;
    short Elevator_state_count_COUNT;
    short Email_abort_message_sent_p_COUNT;
    short Embedded_fuzzy_conditionals_list_COUNT;
    short Emit_postscript_line_length_COUNT;
    short Enable_click_to_edit_kludge_COUNT;
    short Enable_loading_compiled_kbs_p_COUNT;
    short Enable_native_fonts_qm_COUNT;
    short Enable_running_compiled_code_p_COUNT;
    short Enable_saving_compiled_kbs_p_COUNT;
    short Enclosing_form_will_wrap_COUNT;
    short Ensure_expanded_instruction_macros_has_run_p_COUNT;
    short Entire_focus_menu_spot_count_COUNT;
    short Entire_g2_window_spot_count_COUNT;
    short Entire_menu_spot_count_COUNT;
    short Entities_or_triples_found_in_search_COUNT;
    short Entities_to_be_excluded_qm_COUNT;
    short Entity_class_description_COUNT;
    short Entity_cons_counter_COUNT;
    short Entity_height_in_ws_COUNT;
    short Entity_width_in_ws_COUNT;
    short Eq_hash_table_count_COUNT;
    short Erase_dateline_COUNT;
    short Erase_instead_qm_COUNT;
    short Error_code_count_COUNT;
    short Error_of_ok_file_reader_qm_COUNT;
    short Error_within_error_p_COUNT;
    short Eval_cons_counter_COUNT;
    short Evaluating_simulator_procedure_qm_COUNT;
    short Evaluation_value_indentation_depth_COUNT;
    short Evaluation_value_writing_target_length_qm_COUNT;
    short Evaluator_slot_info_count_COUNT;
    short Event_detector_count_COUNT;
    short Event_handler_args_COUNT;
    short Exact_class_names_for_menu_restrictions_COUNT;
    short Exclude_secondary_attributes_COUNT;
    short Executing_change_item_color_instruction_p_COUNT;
    short Execution_time_stack_COUNT;
    short Existence_classes_already_checked_COUNT;
    short Expanded_bindings_forms_COUNT;
    short Expanded_check_timeout_form_COUNT;
    short Expanded_default_clause_form_COUNT;
    short Expanded_exit_form_COUNT;
    short Expanded_exit_stack_eval_major_form_COUNT;
    short Expanded_exit_stack_eval_minor_form_COUNT;
    short Expanded_return_values_form_COUNT;
    short Explanation_table_class_description_COUNT;
    short Explanation_variables_COUNT;
    short Explicit_branch_destination_COUNT;
    short Explicit_dragger_x_in_window_qm_COUNT;
    short Explicit_dragger_y_in_window_qm_COUNT;
    short Expression_bound_local_names_COUNT;
    short Expression_cell_index_COUNT;
    short Expression_for_compilation_count_COUNT;
    short Expression_list_indicator_COUNT;
    short Expression_source_text_COUNT;
    short Expressions_to_display_slot_description_COUNT;
    short External_class_info_count_COUNT;
    short External_diff_options_qm_COUNT;
    short External_diff_program_qm_COUNT;
    short External_method_info_count_COUNT;
    short External_set_pointers_count_COUNT;
    short External_simulation_definition_class_description_COUNT;
    short External_simulation_object_count_COUNT;
    short Externaldefinitions_fixups_COUNT;
    short Extra_time_for_drawing_COUNT;
    short Extreme_bottom_edge_so_far_COUNT;
    short Extreme_left_edge_so_far_COUNT;
    short Extreme_right_edge_so_far_COUNT;
    short Extreme_top_edge_so_far_COUNT;
    short Extremum_cache_count_COUNT;
    short Failure_marker_COUNT;
    short Fake_attribute_COUNT;
    short Fasl_extension_COUNT;
    short Fatal_focus_error_info_for_all_compilations_COUNT;
    short Fatal_focus_error_info_qm_COUNT;
    short Feature_blt_COUNT;
    short Ff_connect_finalized_COUNT;
    short File_format_version_of_g2_ok_file_qm_COUNT;
    short File_punctuation_mark_grammar_rules_COUNT;
    short File_system_directory_search_cache_COUNT;
    short File_system_directory_search_cache_active_p_COUNT;
    short File_system_directory_search_cache_wildcard_string_COUNT;
    short File_system_for_interception_qm_COUNT;
    short File_system_slot_description_COUNT;
    short File_template_instance_counter_COUNT;
    short Filename_of_module_being_loaded_qm_COUNT;
    short Filename_parser_information_count_COUNT;
    short Filename_special_character_registry_COUNT;
    short Fill_pointer_for_current_gensym_string_COUNT;
    short Fill_pointer_for_current_wide_string_COUNT;
    short Fill_pointer_for_match_pattern_for_inspect_binding_vector_COUNT;
    short Filter_cons_counter_COUNT;
    short Finding_object_near_mouse_COUNT;
    short Finish_current_kb_save_failure_COUNT;
    short Finished_storing_in_plot_data_1_qm_COUNT;
    short First_kb_in_group_read_in_yet_qm_COUNT;
    short First_string_in_pool_group_COUNT;
    short First_subexpression_node_for_reclaiming_qm_COUNT;
    short Fixnum_maximum_y_value_COUNT;
    short Fixnum_minimum_y_value_COUNT;
    short Fixnum_time_at_start_of_current_long_notification_COUNT;
    short Fixnum_time_interval_for_one_second_COUNT;
    short Fixnum_time_of_last_g2_tick_COUNT;
    short Fixnum_time_of_last_real_time_tick_COUNT;
    short Fixnum_time_of_last_xsync_COUNT;
    short Fixnum_time_units_of_sleep_this_clock_tick_COUNT;
    short Fixnum_time_until_g2_time_tick_COUNT;
    short Fixup_authors_to_skip_COUNT;
    short Flattened_menu_maximum_remaining_elements_COUNT;
    short Flattened_menu_reverse_COUNT;
    short Float_array_class_description_COUNT;
    short Float_array_cons_counter_COUNT;
    short Float_contagion_stack_operators_COUNT;
    short Float_errors_are_possible_COUNT;
    short Float_list_class_description_COUNT;
    short Float_parameter_class_description_COUNT;
    short Float_variable_class_description_COUNT;
    short Floating_telewindows_limit_COUNT;
    short Floating_tw2_limit_COUNT;
    short Flush_graphics_immediately_qm_COUNT;
    short Focal_entity_for_simulation_formula_COUNT;
    short Focus_for_graph_detailed_procedures_COUNT;
    short Focus_local_name_for_rule_compilation_qm_COUNT;
    short Focus_local_names_for_focus_role_name_COUNT;
    short Focus_name_for_rule_or_formula_compilation_COUNT;
    short Focus_range_COUNT;
    short Focus_too_narrow_qm_COUNT;
    short Font_feature_list_COUNT;
    short Font_map_for_line_of_text_of_graphic_element_COUNT;
    short Fonts_COUNT;
    short Fonts_cons_counter_COUNT;
    short Fonts_needing_corresponding_kanji_font_COUNT;
    short Fonts_used_in_print_job_COUNT;
    short For_image_plane_COUNT;
    short For_structure_count_COUNT;
    short For_workstation_COUNT;
    short For_workstation_context_COUNT;
    short For_workstation_polling_COUNT;
    short Force_change_to_minimum_size_p_COUNT;
    short Force_clock_tick_COUNT;
    short Foreground_color_difference_of_graphic_element_COUNT;
    short Foreground_color_difference_or_differences_of_graphic_element_COUNT;
    short Foreground_color_value_of_graphic_element_COUNT;
    short Foreign_function_call_info_count_COUNT;
    short Foreign_function_declaration_class_description_COUNT;
    short Foreign_function_entry_count_COUNT;
    short Foreign_function_image_info_count_COUNT;
    short Foreign_function_registry_COUNT;
    short Foreign_image_connection_checkup_interval_in_ms_COUNT;
    short Foreign_image_connection_mode_COUNT;
    short Foreign_struct_info_count_COUNT;
    short Foremost_attribute_for_multiplexed_chaining_qm_COUNT;
    short Forgive_long_procedure_instruction_qm_COUNT;
    short Format_frame_class_description_COUNT;
    short Formatted_part_COUNT;
    short Formatted_part_highlight_flag_COUNT;
    short Formatted_part_true_line_color_COUNT;
    short Formula_invocation_count_COUNT;
    short Forward_chaining_link_class_description_COUNT;
    short Forward_compiled_antecedent_COUNT;
    short Forward_compiled_consequent_qm_COUNT;
    short Forward_referenced_format_frames_COUNT;
    short Frame_being_made_COUNT;
    short Frame_being_read_qm_COUNT;
    short Frame_component_spot_count_COUNT;
    short Frame_cons_counter_COUNT;
    short Frame_description_reference_count_COUNT;
    short Frame_display_cons_counter_COUNT;
    short Frame_display_count_COUNT;
    short Frame_for_write_frame_for_kb_COUNT;
    short Frame_note_count_COUNT;
    short Frame_note_index_COUNT;
    short Frame_note_index_has_been_written_qm_COUNT;
    short Frame_note_index_skip_COUNT;
    short Frame_projecting_COUNT;
    short Frame_serial_cons_counter_COUNT;
    short Frame_serial_number_map_COUNT;
    short Frame_serial_number_of_current_message_board_COUNT;
    short Frame_transform_count_COUNT;
    short Frame_transform_of_frame_COUNT;
    short Frame_vector_count_COUNT;
    short Frame_vector_memory_used_COUNT;
    short Frame_vector_pool_vector_COUNT;
    short Frames_for_rendezvous_in_aggregate_values_qm_COUNT;
    short Frames_with_substitute_classes_COUNT;
    short Free_floater_allowed_qm_COUNT;
    short Free_global_stacks_COUNT;
    short Free_malloced_arrays_COUNT;
    short Fsm_state_count_COUNT;
    short Funcalled_evaluator_array_COUNT;
    short Funcalled_evaluator_dispatch_type_COUNT;
    short Funcalled_evaluator_functions_COUNT;
    short Funcalled_instruction_functions_COUNT;
    short Funcalled_instructions_COUNT;
    short Function_definition_class_description_COUNT;
    short Function_info_count_COUNT;
    short Function_invocation_count_COUNT;
    short Function_templates_COUNT;
    short Future_task_queue_holder_count_COUNT;
    short Future_task_to_run_propagate_all_workspace_changes_to_image_planes_COUNT;
    short G2_array_class_description_COUNT;
    short G2_cell_array_cell_class_description_COUNT;
    short G2_cell_array_class_description_COUNT;
    short G2_comment_tokenizer_COUNT;
    short G2_datatypes_xml_namespace_prefix_COUNT;
    short G2_designation_cell_class_description_COUNT;
    short G2_element_types_that_can_contain_datum_COUNT;
    short G2_expression_cell_class_description_COUNT;
    short G2_has_been_started_qm_COUNT;
    short G2_has_v5_mode_windows_p_COUNT;
    short G2_identification_for_write_locks_COUNT;
    short G2_list_class_description_COUNT;
    short G2_list_cons_counter_COUNT;
    short G2_list_element_count_COUNT;
    short G2_load_kb_tokenizer_COUNT;
    short G2_login_class_description_COUNT;
    short G2_login_state_count_COUNT;
    short G2_machine_type_COUNT;
    short G2_meter_names_and_forms_COUNT;
    short G2_meter_task_count_COUNT;
    short G2_module_file_name_map_COUNT;
    short G2_module_search_path_COUNT;
    short G2_operating_system_COUNT;
    short G2_query_cell_class_description_COUNT;
    short G2_save_module_flag_COUNT;
    short G2_save_module_list_COUNT;
    short G2_simple_tokenizer_COUNT;
    short G2_standard_tokenizer_COUNT;
    short G2_stream_all_open_streams_COUNT;
    short G2_stream_device_buffer_COUNT;
    short G2_stream_directory_buffer_COUNT;
    short G2_stream_error_string_table_COUNT;
    short G2_stream_of_ok_file_reader_COUNT;
    short G2_stream_status_slot_description_COUNT;
    short G2_stream_structure_count_COUNT;
    short G2_symbol_tokenizer_COUNT;
    short G2_time_at_start_COUNT;
    short G2_time_at_start_as_text_string_COUNT;
    short G2_time_to_tick_p_base_COUNT;
    short G2_to_g2_uses_references_p_COUNT;
    short G2_token_count_COUNT;
    short G2_tokenizer_tokenizer_COUNT;
    short G2_window_class_description_COUNT;
    short G2_window_for_save_via_system_procedure_qm_COUNT;
    short G2binary_file_name_COUNT;
    short G2binary_file_position_COUNT;
    short G2binary_file_stream_COUNT;
    short G2binary_file_symbol_index_space_COUNT;
    short G2binary_file_symbol_list_COUNT;
    short G2ds_cons_counter_COUNT;
    short G2ds_data_value_write_truth_value_as_integer_p_COUNT;
    short G2ds_interface_count_COUNT;
    short G2ds_interface_status_changed_p_COUNT;
    short G2ds_interface_transition_table_COUNT;
    short G2ds_server_connection_count_COUNT;
    short G2ds_server_connections_COUNT;
    short G2ds_variable_count_COUNT;
    short G2ds_variable_list_COUNT;
    short G2gl_activity_compilation_count_COUNT;
    short G2gl_activity_implementations_alist_COUNT;
    short G2gl_activity_options_count_COUNT;
    short G2gl_alarm_event_handler_COUNT;
    short G2gl_alarm_event_handler_activity_compilation_count_COUNT;
    short G2gl_arg_variable_COUNT;
    short G2gl_assign_COUNT;
    short G2gl_assign_activity_compilation_count_COUNT;
    short G2gl_attribute_display_compilation_count_COUNT;
    short G2gl_body_being_laid_out_COUNT;
    short G2gl_body_compilation_count_COUNT;
    short G2gl_break_COUNT;
    short G2gl_break_activity_compilation_count_COUNT;
    short G2gl_call_COUNT;
    short G2gl_call_activity_compilation_count_COUNT;
    short G2gl_call_invocation_count_COUNT;
    short G2gl_compensate_COUNT;
    short G2gl_compensate_activity_compilation_count_COUNT;
    short G2gl_compensation_handler_COUNT;
    short G2gl_compensation_handler_activity_compilation_count_COUNT;
    short G2gl_compilation_version_count_COUNT;
    short G2gl_correlation_variable_COUNT;
    short G2gl_do_COUNT;
    short G2gl_do_activity_compilation_count_COUNT;
    short G2gl_empty_COUNT;
    short G2gl_empty_activity_compilation_count_COUNT;
    short G2gl_eval_error_COUNT;
    short G2gl_execution_fault_count_COUNT;
    short G2gl_execution_frame_count_COUNT;
    short G2gl_execution_thread_count_COUNT;
    short G2gl_exit_COUNT;
    short G2gl_exit_activity_compilation_count_COUNT;
    short G2gl_expression_compilation_error_COUNT;
    short G2gl_expression_language_symbol_COUNT;
    short G2gl_failed_activity_name_COUNT;
    short G2gl_false_COUNT;
    short G2gl_fault_handler_COUNT;
    short G2gl_fault_handler_activity_compilation_count_COUNT;
    short G2gl_flow_discriminator_COUNT;
    short G2gl_flow_discriminator_activity_compilation_count_COUNT;
    short G2gl_flow_gate_COUNT;
    short G2gl_flow_gate_activity_compilation_count_COUNT;
    short G2gl_flow_signal_COUNT;
    short G2gl_flow_signal_activity_compilation_count_COUNT;
    short G2gl_flow_split_COUNT;
    short G2gl_flow_split_activity_compilation_count_COUNT;
    short G2gl_flow_sync_COUNT;
    short G2gl_flow_sync_activity_compilation_count_COUNT;
    short G2gl_flow_terminator_COUNT;
    short G2gl_flow_terminator_activity_compilation_count_COUNT;
    short G2gl_import_added_start_activity_p_COUNT;
    short G2gl_import_errors_COUNT;
    short G2gl_import_flow_link_p_list_COUNT;
    short G2gl_invoke_COUNT;
    short G2gl_invoke_activity_compilation_count_COUNT;
    short G2gl_link_connection_arrows_COUNT;
    short G2gl_link_connection_line_pattern_COUNT;
    short G2gl_local_variable_COUNT;
    short G2gl_message_event_handler_COUNT;
    short G2gl_message_event_handler_activity_compilation_count_COUNT;
    short G2gl_message_transmission_count_COUNT;
    short G2gl_n_out_of_m_flow_join_COUNT;
    short G2gl_n_out_of_m_flow_join_activity_compilation_count_COUNT;
    short G2gl_object_icon_descriptions_info_COUNT;
    short G2gl_object_icon_substitutions_may_be_in_use_p_COUNT;
    short G2gl_operators_COUNT;
    short G2gl_parameters_COUNT;
    short G2gl_partner_link_variable_COUNT;
    short G2gl_pick_COUNT;
    short G2gl_pick_activity_compilation_count_COUNT;
    short G2gl_pick_join_COUNT;
    short G2gl_pick_join_activity_compilation_count_COUNT;
    short G2gl_process_invocation_thread_count_COUNT;
    short G2gl_query_language_symbol_COUNT;
    short G2gl_receive_COUNT;
    short G2gl_receive_activity_compilation_count_COUNT;
    short G2gl_reply_COUNT;
    short G2gl_reply_activity_compilation_count_COUNT;
    short G2gl_return_COUNT;
    short G2gl_return_activity_compilation_count_COUNT;
    short G2gl_scope_COUNT;
    short G2gl_scope_activity_compilation_count_COUNT;
    short G2gl_service_port_count_COUNT;
    short G2gl_standard_connection_arrows_COUNT;
    short G2gl_standard_connection_line_pattern_COUNT;
    short G2gl_standard_service_switch_COUNT;
    short G2gl_switch_fork_COUNT;
    short G2gl_switch_fork_activity_compilation_count_COUNT;
    short G2gl_switch_join_COUNT;
    short G2gl_switch_join_activity_compilation_count_COUNT;
    short G2gl_text_box_compilation_count_COUNT;
    short G2gl_throw_COUNT;
    short G2gl_throw_activity_compilation_count_COUNT;
    short G2gl_true_COUNT;
    short G2gl_variable_COUNT;
    short G2gl_wait_COUNT;
    short G2gl_wait_activity_compilation_count_COUNT;
    short G2gl_while_COUNT;
    short G2gl_while_activity_compilation_count_COUNT;
    short G2gl_xml_namespace_COUNT;
    short G2gl_xml_namespace_prefix_COUNT;
    short G2passwdexe_COUNT;
    short G2passwdexe_is_executable_p_COUNT;
    short Gathering_normally_editable_slots_for_search_qm_COUNT;
    short Gb_2312_count_COUNT;
    short Generate_source_annotation_info_COUNT;
    short Generated_var_spots_for_base_code_body_return_COUNT;
    short Generic_action_button_class_description_COUNT;
    short Generic_formula_class_description_COUNT;
    short Generic_listener_initialized_qm_COUNT;
    short Generic_rule_instance_display_hash_table_COUNT;
    short Generic_simulation_formula_class_description_COUNT;
    short Generic_simulation_formulas_used_p_COUNT;
    short Gensym_base_time_as_managed_float_COUNT;
    short Gensym_char_or_code_for_bullet_COUNT;
    short Gensym_char_or_code_for_capital_ligature_oe_COUNT;
    short Gensym_char_or_code_for_linebreak_COUNT;
    short Gensym_char_or_code_for_paragraph_break_COUNT;
    short Gensym_char_or_code_for_small_letter_f_with_hook_COUNT;
    short Gensym_char_or_code_for_small_ligature_oe_COUNT;
    short Gensym_char_or_code_for_trade_mark_sign_COUNT;
    short Gensym_code_for_bullet_COUNT;
    short Gensym_code_for_capital_ligature_oe_COUNT;
    short Gensym_code_for_linebreak_COUNT;
    short Gensym_code_for_paragraph_break_COUNT;
    short Gensym_code_for_small_letter_f_with_hook_COUNT;
    short Gensym_code_for_small_ligature_oe_COUNT;
    short Gensym_code_for_trade_mark_sign_COUNT;
    short Gensym_cons_counter_COUNT;
    short Gensym_default_pathname_defaults_COUNT;
    short Gensym_environment_variable_buffer_COUNT;
    short Gensym_error_argument_list_COUNT;
    short Gensym_error_format_string_COUNT;
    short Gensym_error_sure_of_format_info_p_COUNT;
    short Gensym_esc_for_bullet_qm_COUNT;
    short Gensym_esc_for_capital_ligature_oe_qm_COUNT;
    short Gensym_esc_for_linebreak_qm_COUNT;
    short Gensym_esc_for_paragraph_break_qm_COUNT;
    short Gensym_esc_for_small_letter_f_with_hook_qm_COUNT;
    short Gensym_esc_for_small_ligature_oe_qm_COUNT;
    short Gensym_esc_for_trade_mark_sign_qm_COUNT;
    short Gensym_file_error_occurred_p_COUNT;
    short Gensym_grammar_count_COUNT;
    short Gensym_logo_style_COUNT;
    short Gensym_pathname_count_COUNT;
    short Gensym_string_stream_count_COUNT;
    short Gensym_string_text_sequence_count_COUNT;
    short Gensym_time_COUNT;
    short Gensym_time_array_COUNT;
    short Gensym_time_at_start_COUNT;
    short Gensym_window_count_COUNT;
    short Gensym_window_for_printing_COUNT;
    short Geometric_change_to_connection_is_temporary_p_COUNT;
    short Geometry_count_COUNT;
    short Gesture_function_count_COUNT;
    short Gesture_local_count_COUNT;
    short Gesture_source_recording_p_COUNT;
    short Gesture_source_stack_COUNT;
    short Gesture_thread_count_COUNT;
    short Gesture_unbound_value_COUNT;
    short Get_focal_entity_for_simulation_formula_qm_COUNT;
    short Get_object_on_kb_workspace_for_item_COUNT;
    short Gfi_cons_counter_COUNT;
    short Gfi_list_of_converters_COUNT;
    short Gfi_queue_item_count_COUNT;
    short Global_desired_thrashing_setpoint_COUNT;
    short Global_domain_COUNT;
    short Global_draw_diagonally_qm_COUNT;
    short Global_keyboard_command_choices_COUNT;
    short Global_list_of_all_data_servers_COUNT;
    short Global_nms_menu_choiced_item_id_COUNT;
    short Global_nmsci_id_for_attributes_pane_COUNT;
    short Global_nmsci_id_for_hidden_attributes_pane_COUNT;
    short Global_output_stream_for_expand_syntax_template_COUNT;
    short Global_profiling_structure_count_COUNT;
    short Global_stack_COUNT;
    short Global_table_of_attributes_pane_COUNT;
    short Global_table_of_attributes_pane_pointer_COUNT;
    short Global_table_of_hidden_attributes_pane_COUNT;
    short Global_table_of_hidden_attributes_pane_pointer_COUNT;
    short Global_temp_1_COUNT;
    short Global_temp_2_COUNT;
    short Global_temp_3_COUNT;
    short Goto_tag_entry_count_COUNT;
    short Goto_tags_in_compilation_COUNT;
    short Grammar_categories_getting_choose_existing_class_feature_COUNT;
    short Grammar_categories_getting_yes_no_feature_COUNT;
    short Grammar_cons_counter_COUNT;
    short Grammar_rules_to_add_for_nupec_after_authorization_COUNT;
    short Graph_allocation_factor_COUNT;
    short Graph_background_color_value_COUNT;
    short Graph_class_description_COUNT;
    short Graph_cons_counter_COUNT;
    short Graph_display_changed_during_update_qm_COUNT;
    short Graph_display_count_COUNT;
    short Graph_expression_uses_local_name_qm_COUNT;
    short Graph_grid_class_description_COUNT;
    short Graph_grid_for_data_COUNT;
    short Graph_layout_cons_counter_COUNT;
    short Graph_month_strings_COUNT;
    short Graph_node_count_COUNT;
    short Graph_nodes_needing_children_connections_COUNT;
    short Graph_nodes_to_add_as_subblocks_COUNT;
    short Graph_or_icon_rendering_of_graphic_element_COUNT;
    short Graph_rendering_count_COUNT;
    short Graph_table_spot_count_COUNT;
    short Graphed_block_groups_to_move_COUNT;
    short Graphic_character_set_count_COUNT;
    short Graphic_element_projection_COUNT;
    short Graphics_cons_counter_COUNT;
    short Grid_COUNT;
    short Grid_color_COUNT;
    short Grid_height_COUNT;
    short Grid_painting_COUNT;
    short Grid_pane_count_COUNT;
    short Grid_view_cell_count_COUNT;
    short Grid_visible_COUNT;
    short Grid_width_COUNT;
    short Group_index_structure_count_COUNT;
    short Gsi_application_name_COUNT;
    short Gsi_array_wrapper_count_COUNT;
    short Gsi_attribute_count_COUNT;
    short Gsi_connection_checkup_interval_in_ms_COUNT;
    short Gsi_cons_counter_COUNT;
    short Gsi_context_to_socket_map_COUNT;
    short Gsi_extension_data_count_COUNT;
    short Gsi_history_count_COUNT;
    short Gsi_icp_interface_count_COUNT;
    short Gsi_instance_count_COUNT;
    short Gsi_instance_extension_count_COUNT;
    short Gsi_interface_status_changed_p_COUNT;
    short Gsi_interfaces_to_process_head_COUNT;
    short Gsi_interfaces_to_process_tail_COUNT;
    short Gsi_local_function_count_COUNT;
    short Gsi_local_home_COUNT;
    short Gsi_magic_number_COUNT;
    short Gsi_maximum_contexts_exceeded_COUNT;
    short Gsi_maximum_idle_interval_COUNT;
    short Gsi_maximum_number_of_contexts_COUNT;
    short Gsi_protect_inner_calls_p_COUNT;
    short Gsi_reclaim_list_level_COUNT;
    short Gsi_reclaim_list_qm_COUNT;
    short Gsi_remote_procedure_count_COUNT;
    short Gsi_remote_value_conses_logical_p_COUNT;
    short Gsi_remote_value_creates_instance_p_COUNT;
    short Gsi_throw_to_run_loop_may_be_harmful_p_COUNT;
    short Gsi_transfer_wrapper_count_COUNT;
    short Gsi_vector_length_COUNT;
    short Halt_info_count_COUNT;
    short Han_interpretation_mode_COUNT;
    short Handle_to_socket_mapping_COUNT;
    short Handle_ui_client_interface_messages_immediately_p_COUNT;
    short Handling_solitary_i_am_alive_qm_COUNT;
    short Handy_float_1_COUNT;
    short Height_for_change_size_qm_COUNT;
    short Hfep_action_COUNT;
    short Hfep_capability_qm_COUNT;
    short Hfep_cho_ksc2c_COUNT;
    short Hfep_hanc_type_count_COUNT;
    short Hfep_jong_ksc2c_COUNT;
    short Hfep_jung_ksc2c_COUNT;
    short Hfep_ksc2cs_COUNT;
    short Hfep_state_COUNT;
    short High_bound_system_variable_for_get_current_bounds_for_plot_COUNT;
    short High_bound_system_variable_for_get_current_min_and_max_for_plot_from_history_COUNT;
    short High_value_for_horizontal_grid_lines_COUNT;
    short High_value_for_vertical_grid_lines_COUNT;
    short Highest_foreign_image_index_COUNT;
    short Highest_icp_socket_session_id_COUNT;
    short Highest_inspect_session_id_COUNT;
    short Highest_parsing_context_handle_COUNT;
    short Highest_remote_spawn_index_COUNT;
    short Highest_state_index_COUNT;
    short History_cons_counter_COUNT;
    short History_ring_buffer_count_COUNT;
    short History_time_per_pixel_COUNT;
    short History_time_to_evaluate_display_expression_with_COUNT;
    short Home_name_separator_COUNT;
    short Horizontal_grid_line_color_qm_COUNT;
    short Horizontal_grid_line_spacing_COUNT;
    short Horizontal_grid_line_width_COUNT;
    short Hot_spot_state_count_COUNT;
    short Hour_of_last_message_COUNT;
    short Hourly_countdown_COUNT;
    short Html_view_count_COUNT;
    short I_am_alive_info_count_COUNT;
    short I_am_alive_send_time_interval_COUNT;
    short I_am_alive_send_time_interval_in_seconds_COUNT;
    short I_am_alive_send_time_interval_in_seconds_as_float_COUNT;
    short Icmp_socket_count_COUNT;
    short Icon_cell_class_description_COUNT;
    short Icon_description_count_COUNT;
    short Icon_editor_button_count_COUNT;
    short Icon_editor_cons_counter_COUNT;
    short Icon_editor_count_COUNT;
    short Icon_editor_engine_count_COUNT;
    short Icon_editor_layers_pad_count_COUNT;
    short Icon_editor_table_count_COUNT;
    short Icon_editor_table_info_frame_class_description_COUNT;
    short Icon_editor_translator_count_COUNT;
    short Icon_editor_view_pad_count_COUNT;
    short Icon_editor_workspace_class_description_COUNT;
    short Icon_list_notes_COUNT;
    short Icon_offset_clip_bottom_COUNT;
    short Icon_offset_clip_left_COUNT;
    short Icon_offset_clip_right_COUNT;
    short Icon_offset_clip_top_COUNT;
    short Icon_offset_left_COUNT;
    short Icon_offset_top_COUNT;
    short Icon_rendering_count_COUNT;
    short Icon_renderings_being_bulk_decached_COUNT;
    short Icon_slot_group_count_COUNT;
    short Icp_bits_current_bits_COUNT;
    short Icp_bits_current_value_COUNT;
    short Icp_buffer_count_COUNT;
    short Icp_buffer_of_start_of_message_series_qm_COUNT;
    short Icp_buffer_ref_count_cons_counter_COUNT;
    short Icp_buffers_for_message_group_COUNT;
    short Icp_byte_position_of_start_of_message_series_qm_COUNT;
    short Icp_callback_cons_counter_COUNT;
    short Icp_cons_counter_COUNT;
    short Icp_error_suspend_p_COUNT;
    short Icp_message_handler_array_COUNT;
    short Icp_message_handler_name_array_COUNT;
    short Icp_message_trace_stream_qm_COUNT;
    short Icp_output_ports_to_flush_COUNT;
    short Icp_player_message_handler_array_COUNT;
    short Icp_port_count_COUNT;
    short Icp_port_for_reclaim_COUNT;
    short Icp_printing_message_handler_array_COUNT;
    short Icp_priority_categories_for_gsi_COUNT;
    short Icp_protocol_version_COUNT;
    short Icp_read_task_count_COUNT;
    short Icp_read_trace_cutoff_level_qm_COUNT;
    short Icp_socket_connect_negotiation_timeout_default_COUNT;
    short Icp_socket_count_COUNT;
    short Icp_socket_for_handle_icp_messages_COUNT;
    short Icp_socket_for_reclaim_qm_COUNT;
    short Icp_socket_index_COUNT;
    short Icp_socket_transacting_message_group_COUNT;
    short Icp_sockets_now_initializing_g2ds_COUNT;
    short Icp_sockets_now_initializing_gsi_COUNT;
    short Icp_sockets_to_be_reclaimed_COUNT;
    short Icp_sockets_waiting_for_icp_message_processing_COUNT;
    short Icp_suspend_COUNT;
    short Icp_trace_level_descriptions_COUNT;
    short Icp_trace_print_message_series_p_COUNT;
    short Icp_write_task_count_COUNT;
    short Icp_write_trace_cutoff_level_qm_COUNT;
    short Identified_drawing_activity_count_COUNT;
    short Identifying_attribute_count_for_item_new_copy_COUNT;
    short Idling_wait_state_string_COUNT;
    short Ignore_kb_flags_in_kbs_qm_COUNT;
    short Ignore_kb_state_changes_p_COUNT;
    short Image_cv_count_COUNT;
    short Image_data_count_COUNT;
    short Image_data_of_graphic_element_COUNT;
    short Image_left_offset_in_ws_COUNT;
    short Image_plane_count_COUNT;
    short Image_plane_for_finding_object_near_mouse_COUNT;
    short Image_plane_is_obscured_p_COUNT;
    short Image_plane_spot_count_COUNT;
    short Image_rendering_count_COUNT;
    short Image_tile_count_COUNT;
    short Image_tile_lru_queue_COUNT;
    short Image_top_offset_in_ws_COUNT;
    short Image_x_scale_for_finding_object_near_mouse_COUNT;
    short Image_y_scale_for_finding_object_near_mouse_COUNT;
    short In_clear_kb_p_COUNT;
    short In_edit_warning_context_p_COUNT;
    short In_external_definitions_for_module_p_COUNT;
    short In_find_stripped_text_slot_p_COUNT;
    short In_line_evaluator_array_COUNT;
    short In_local_source_code_control_scope_p_COUNT;
    short In_non_top_level_context_qm_COUNT;
    short In_recompile_item_p_COUNT;
    short In_recursive_gsi_context_COUNT;
    short In_suspend_resume_p_COUNT;
    short In_text_for_item_or_value_p_COUNT;
    short In_unprotected_gsi_api_call_p_COUNT;
    short In_write_module_as_clear_text_p_COUNT;
    short Include_slots_visible_only_to_roles_p_COUNT;
    short Incomplete_painting_action_count_COUNT;
    short Incomplete_phrase_count_COUNT;
    short Incomplete_phrases_at_frontier_COUNT;
    short Indent_sequences_and_structures_p_COUNT;
    short Index_for_stop_time_COUNT;
    short Index_of_open_windows_COUNT;
    short Index_of_resumable_p_in_icp_buffer_COUNT;
    short Index_of_top_of_backtrace_stack_COUNT;
    short Index_space_count_COUNT;
    short Index_to_array_of_transfer_wrappers_COUNT;
    short Indexed_attributes_COUNT;
    short Inference_background_collection_count_COUNT;
    short Inference_engine_parameters_COUNT;
    short Inform_message_information_count_COUNT;
    short Information_from_caught_signal_COUNT;
    short Information_from_trapped_error_COUNT;
    short Inhibit_corresponding_icp_object_making_COUNT;
    short Inhibit_free_reference_recording_COUNT;
    short Inhibit_icp_message_processing_COUNT;
    short Inhibit_icp_message_processing_enabled_COUNT;
    short Inhibit_icp_socket_reclamation_COUNT;
    short Inhibit_model_install_qm_COUNT;
    short Inhibit_modularity_consistency_checking_qm_COUNT;
    short Inhibit_non_real_time_clock_ticks_qm_COUNT;
    short Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm_COUNT;
    short Init_orientation_horizontal_p_COUNT;
    short Initial_icp_version_info_enabled_p_COUNT;
    short Initial_java_class_COUNT;
    short Initial_stack_offsets_COUNT;
    short Initialization_inhibit_COUNT;
    short Initialize_gensym_window_after_connection_done_COUNT;
    short Initialize_items_count_COUNT;
    short Initializing_clear_text_p_COUNT;
    short Initializing_compound_slot_qm_COUNT;
    short Initializing_items_needing_initialization_COUNT;
    short Initializing_simulator_qm_COUNT;
    short Initializing_state_variables_qm_COUNT;
    short Inline_timeout_checks_COUNT;
    short Inlining_data_COUNT;
    short Inlining_data_holder_count_COUNT;
    short Inner_abort_level_tag_COUNT;
    short Inner_paint_loop_counter_COUNT;
    short Input_gensym_string_for_buffer_for_internal_error_on_console_COUNT;
    short Input_gensym_string_for_buffer_for_string_metering_COUNT;
    short Input_gensym_string_for_gensym_error_message_buffer_COUNT;
    short Input_string_for_backtrace_text_buffer_for_internal_error_COUNT;
    short Input_string_for_backtrace_text_buffer_for_string_metering_COUNT;
    short Input_string_for_buffer_for_internal_error_on_logbook_COUNT;
    short Input_string_for_buffer_for_write_internal_error_COUNT;
    short Input_table_spot_count_COUNT;
    short Insertion_location_for_embedded_expressions_qm_COUNT;
    short Inside_action_iteration_p_COUNT;
    short Inside_avoid_arithmetic_errors_p_COUNT;
    short Inside_breakpoint_p_COUNT;
    short Inside_handle_event_COUNT;
    short Inside_handling_gensym_file_errors_scope_p_COUNT;
    short Inspect_command_class_description_COUNT;
    short Inspect_command_for_modularity_problems_qm_COUNT;
    short Inspect_command_history_list_COUNT;
    short Inspect_command_spot_count_COUNT;
    short Inspection_instance_counter_COUNT;
    short Install_item_in_model_if_appropriate_COUNT;
    short Installation_code_in_ok_file_COUNT;
    short Installation_cons_counter_COUNT;
    short Integer_array_class_description_COUNT;
    short Integer_cv_count_COUNT;
    short Integer_list_class_description_COUNT;
    short Integer_parameter_class_description_COUNT;
    short Integer_variable_class_description_COUNT;
    short Intentionally_bogus_vector_for_g2_cause_asynchronous_abort_COUNT;
    short Inter_g2_data_request_queue_count_COUNT;
    short Interesting_blocks_found_in_search_COUNT;
    short Intern_string_buffer_COUNT;
    short Internal_error_trapped_format_string_COUNT;
    short Internal_g2_element_types_that_can_contain_datum_COUNT;
    short Internal_signal_caught_format_string_COUNT;
    short Internal_status_of_most_recent_file_operation_COUNT;
    short Internal_token_count_COUNT;
    short Interned_list_conses_COUNT;
    short Interned_list_conses_in_use_COUNT;
    short Interned_list_count_COUNT;
    short Interned_list_nil_COUNT;
    short Interned_list_non_symbol_root_COUNT;
    short Interned_list_symbols_COUNT;
    short Interned_remote_procedure_item_passing_info_count_COUNT;
    short Interval_between_horizontal_grid_lines_COUNT;
    short Interval_between_plot_markers_COUNT;
    short Interval_between_vertical_grid_lines_COUNT;
    short Interval_for_telewindows_modernization_COUNT;
    short Invalid_address_COUNT;
    short Invalid_spot_count_COUNT;
    short Invisible_entity_class_description_COUNT;
    short Is_g2_enterprise_qm_COUNT;
    short Is_icon_mask_drawing_COUNT;
    short Iso_2022_transcoder_count_COUNT;
    short Iso_646_count_COUNT;
    short Iso_8859_10_count_COUNT;
    short Iso_8859_1_count_COUNT;
    short Iso_8859_2_count_COUNT;
    short Iso_8859_3_count_COUNT;
    short Iso_8859_4_count_COUNT;
    short Iso_8859_5_count_COUNT;
    short Iso_8859_6_count_COUNT;
    short Iso_8859_7_count_COUNT;
    short Iso_8859_8_count_COUNT;
    short Iso_8859_9_count_COUNT;
    short Iso_8859_abstract_count_COUNT;
    short Iso_8859_transcoder_count_COUNT;
    short Iso_latin1_special_character_code_map_COUNT;
    short Item_access_cache_count_COUNT;
    short Item_array_class_description_COUNT;
    short Item_being_read_for_new_reference_COUNT;
    short Item_class_description_COUNT;
    short Item_color_pattern_returns_overrides_only_p_COUNT;
    short Item_copy_handle_for_root_item_COUNT;
    short Item_copy_index_space_COUNT;
    short Item_copy_root_item_COUNT;
    short Item_copy_rpc_item_info_COUNT;
    short Item_list_class_description_COUNT;
    short Item_represented_by_table_spot_count_COUNT;
    short Items_deleted_since_load_or_save_COUNT;
    short Items_deleted_since_load_or_save_tail_COUNT;
    short Items_encountered_in_memory_walk_COUNT;
    short Items_made_incomplete_COUNT;
    short Items_made_incomplete_were_recorded_qm_COUNT;
    short Items_needing_initialization_COUNT;
    short Items_needing_initialization_tree_COUNT;
    short Items_to_traverse_COUNT;
    short Items_warned_in_edit_warning_context_COUNT;
    short Iteration_forms_for_embedded_expressions_qm_COUNT;
    short Java_class_count_COUNT;
    short Java_code_count_COUNT;
    short Java_code_exception_count_COUNT;
    short Java_cons_counter_COUNT;
    short Java_descriptor_count_COUNT;
    short Java_editing_categories_COUNT;
    short Java_field_count_COUNT;
    short Java_grammar_stream_qm_COUNT;
    short Java_method_count_COUNT;
    short Java_symbol_count_COUNT;
    short Java_tokenizer_COUNT;
    short Javalink_notification_versions_COUNT;
    short Javalink_versioned_call_data_count_COUNT;
    short Jis_x_0208_count_COUNT;
    short Joes_graph_hax_p_COUNT;
    short Joes_graph_hax_trace_p_COUNT;
    short Journal_cons_counter_COUNT;
    short Journal_shutout_scan_p_COUNT;
    short Junction_blocks_not_to_be_deleted_COUNT;
    short Just_update_representations_of_slot_value_COUNT;
    short Kana_to_ascii_map_COUNT;
    short Kanji_fonts_used_in_print_job_COUNT;
    short Kanji_row_to_font_file_name_mapping_vector_COUNT;
    short Kb_configuration_COUNT;
    short Kb_file_progress_COUNT;
    short Kb_file_progress_is_currently_for_modules_p_COUNT;
    short Kb_flags_COUNT;
    short Kb_flags_for_saving_COUNT;
    short Kb_flags_from_last_kb_read_COUNT;
    short Kb_format_identifier_read_qm_COUNT;
    short Kb_format_write_integer_buffer_COUNT;
    short Kb_frame_class_description_COUNT;
    short Kb_load_case_qm_COUNT;
    short Kb_module_currently_to_save_qm_COUNT;
    short Kb_object_index_property_name_pool_COUNT;
    short Kb_object_index_space_COUNT;
    short Kb_procedure_completion_form_qm_COUNT;
    short Kb_property_cons_counter_COUNT;
    short Kb_restrictions_COUNT;
    short Kb_restrictions_names_COUNT;
    short Kb_save_count_COUNT;
    short Kb_save_termination_reason_qm_COUNT;
    short Kb_serial_number_before_loading_this_group_COUNT;
    short Kb_state_changes_COUNT;
    short Kb_transfer_count_COUNT;
    short Kb_uses_crlf_p_COUNT;
    short Kb_window_for_initializing_definitions_COUNT;
    short Kb_workspace_class_description_COUNT;
    short Kb_workspace_image_plane_spot_count_COUNT;
    short Keep_edit_workspace_hidden_no_matter_what_qm_COUNT;
    short Key_cap_to_gensym_cyrillic_character_code_map_COUNT;
    short Key_index_to_key_symbol_array_COUNT;
    short Key_index_to_lisp_character_array_COUNT;
    short Keytab1_COUNT;
    short Keyword_package_1_COUNT;
    short Kfep_batch_count_COUNT;
    short Kfep_batchyomi_COUNT;
    short Kfep_batchyomilen_COUNT;
    short Kfep_battable_COUNT;
    short Kfep_capability_qm_COUNT;
    short Kfep_conversion_choice_menu_button_spot_count_COUNT;
    short Kfep_conversion_choice_menu_class_description_COUNT;
    short Kfep_converters_have_been_initialized_qm_COUNT;
    short Kfep_ghyoki_hptr_COUNT;
    short Kfep_ghyoki_idxbuf_COUNT;
    short Kfep_ghyoki_idxbuf_cache_alist_COUNT;
    short Kfep_ghyoki_savtblnum_COUNT;
    short Kfep_hensaisyo_getpos_COUNT;
    short Kfep_hensaisyo_gonum_COUNT;
    short Kfep_hensaisyo_saventry_COUNT;
    short Kfep_hensaisyo_tno_COUNT;
    short Kfep_index_file_stream_COUNT;
    short Kfep_kka_p_batkanakan_position_COUNT;
    short Kfep_kka_usetblnum_COUNT;
    short Kfep_kojin_bunpobits_COUNT;
    short Kfep_kojin_file_stream_COUNT;
    short Kfep_kojin_header_COUNT;
    short Kfep_kojin_hyolen_COUNT;
    short Kfep_kojin_index_COUNT;
    short Kfep_kojin_usedbits_COUNT;
    short Kfep_m_table_COUNT;
    short Kfep_main_file_stream_COUNT;
    short Kfep_master_count_COUNT;
    short Kfep_master_header_COUNT;
    short Kfep_master_header_in_characters_COUNT;
    short Kfep_search_limit_1_COUNT;
    short Kfep_search_limit_2_COUNT;
    short Kfep_tablemax_COUNT;
    short Known_gensym_acronyms_COUNT;
    short Known_localizations_COUNT;
    short Known_process_ids_qm_COUNT;
    short Known_regexp_functions_COUNT;
    short Ks_c_5601_count_COUNT;
    short Ksc_contiguous_character_group_lengths_COUNT;
    short Label_box_spot_count_COUNT;
    short Label_scale_for_vertical_grid_lines_COUNT;
    short Language_parameters_COUNT;
    short Language_translation_class_description_COUNT;
    short Large_byte_vector_COUNT;
    short Large_scaled_font_bucket_count_COUNT;
    short Largest_non_malloced_byte_vector_16_pool_index_COUNT;
    short Largest_non_malloced_string_pool_index_COUNT;
    short Last_assigned_category_index_COUNT;
    short Last_assigned_global_kb_number_COUNT;
    short Last_assigned_grammar_number_COUNT;
    short Last_assigned_kb_serial_number_COUNT;
    short Last_bootstrap_mode_qm_COUNT;
    short Last_deletable_token_in_namestring_COUNT;
    short Last_event_socket_handle_COUNT;
    short Last_event_socket_handle_holder_COUNT;
    short Last_event_status_code_COUNT;
    short Last_event_status_code_0_COUNT;
    short Last_event_status_code_1_COUNT;
    short Last_event_status_code_holder_COUNT;
    short Last_gsi_timestamp_day_COUNT;
    short Last_gsi_timestamp_hour_COUNT;
    short Last_gsi_timestamp_month_COUNT;
    short Last_gsi_timestamp_unix_time_COUNT;
    short Last_gsi_timestamp_year_COUNT;
    short Last_history_time_for_data_point_on_pixel_COUNT;
    short Last_image_plane_serial_number_COUNT;
    short Last_memory_stats_snapshot_COUNT;
    short Last_part_features_index_allocated_COUNT;
    short Last_player_event_time_COUNT;
    short Last_player_mouse_x_COUNT;
    short Last_player_mouse_y_COUNT;
    short Last_postscript_composite_object_index_COUNT;
    short Last_reason_for_complex_type_rejection_COUNT;
    short Last_roman_kana_g2_length_COUNT;
    short Last_roman_kata_g2_length_COUNT;
    short Last_semantic_check_error_string_COUNT;
    short Last_slot_checked_of_type_failure_COUNT;
    short Last_source_line_COUNT;
    short Last_system_class_bit_number_COUNT;
    short Last_ui_callback_handle_COUNT;
    short Last_workstation_serviced_COUNT;
    short Launch_recompile_for_compilations_removed_in_this_kb_qm_COUNT;
    short Layer_box_count_COUNT;
    short Lazy_assignment_of_uuids_COUNT;
    short Leak_list_COUNT;
    short Learned_list_to_expedite_ui_COUNT;
    short Leave_text_representation_as_a_single_line_qm_COUNT;
    short Left_braket_written_qm_COUNT;
    short Left_edge_in_window_of_graphic_element_COUNT;
    short Left_edge_of_draw_area_COUNT;
    short Left_edge_of_frame_COUNT;
    short Left_edge_of_line_of_text_in_window_of_graphic_element_COUNT;
    short Left_marker_for_cascading_menu_rubber_stamp_widget_COUNT;
    short Left_scroll_arrow_rubber_stamp_widget_COUNT;
    short Legacy_subsecond_heartbeat_adjustment_interval_COUNT;
    short Legend_pane_count_COUNT;
    short Length_of_most_negative_fixnum_as_string_COUNT;
    short Length_of_xml_output_line_COUNT;
    short Level_of_group_kb_read_COUNT;
    short Lexically_visible_code_bodies_COUNT;
    short Lexically_visible_goto_tags_COUNT;
    short Lexing_table_count_COUNT;
    short Lfsi_bound_marker_COUNT;
    short Lfsi_label_index_space_COUNT;
    short Lfsi_local_var_index_space_COUNT;
    short Lfsi_stack_var_index_space_COUNT;
    short Lfsi_unbound_marker_COUNT;
    short Limit_dos_filename_component_lengths_p_COUNT;
    short Limit_profiling_based_on_licence_level_p_COUNT;
    short Line_drawing_for_printing_count_COUNT;
    short Line_number_of_ok_file_reader_COUNT;
    short Links_and_objects_COUNT;
    short Lisp_character_to_key_index_alist_COUNT;
    short Lisp_grid_view_count_COUNT;
    short Lisp_highest_printable_character_code_COUNT;
    short Lisp_int_character_to_key_index_array_COUNT;
    short Lisp_memory_expanded_qm_COUNT;
    short Lisp_package_1_COUNT;
    short List_box_cv_count_COUNT;
    short List_for_import_COUNT;
    short List_of_all_data_servers_COUNT;
    short List_of_all_g2ds_interfaces_COUNT;
    short List_of_all_gsi_interfaces_COUNT;
    short List_of_already_defined_tokenizer_matching_tests_COUNT;
    short List_of_argument_lists_to_add_menu_items_for_category_COUNT;
    short List_of_bad_status_compiler_frame_note_types_COUNT;
    short List_of_compiler_frame_note_types_COUNT;
    short List_of_connection_roles_COUNT;
    short List_of_exported_method_texts_COUNT;
    short List_of_expressions_for_compilation_COUNT;
    short List_of_for_structures_COUNT;
    short List_of_funcalled_functions_COUNT;
    short List_of_g2ds_values_to_process_head_COUNT;
    short List_of_g2ds_values_to_process_tail_COUNT;
    short List_of_generated_contexts_COUNT;
    short List_of_generated_contexts_tail_COUNT;
    short List_of_grid_attributes_COUNT;
    short List_of_grid_tokens_COUNT;
    short List_of_gsi_values_to_process_head_COUNT;
    short List_of_gsi_values_to_process_tail_COUNT;
    short List_of_known_names_COUNT;
    short List_of_module_pre_conflict_resolution_post_loading_functions_COUNT;
    short List_of_once_only_post_conflict_resolution_post_loading_functions_COUNT;
    short List_of_once_only_pre_conflict_resolution_post_loading_functions_COUNT;
    short List_of_once_only_switched_post_loading_functions_COUNT;
    short List_of_previously_optimized_procedures_COUNT;
    short List_of_reference_structures_COUNT;
    short List_of_switched_and_module_post_loading_functions_COUNT;
    short List_of_symbols_for_symbol_value_COUNT;
    short List_of_types_to_be_analyzed_COUNT;
    short List_of_user_overridable_system_slots_COUNT;
    short Listed_continuation_servers_COUNT;
    short Listed_print_to_server_command_COUNT;
    short Loading_compiled_kb_p_COUNT;
    short Loading_kb_p_COUNT;
    short Local_event_count_COUNT;
    short Local_file_system_COUNT;
    short Local_filename_parser_COUNT;
    short Local_host_name_COUNT;
    short Local_insertion_location_COUNT;
    short Local_iteration_forms_COUNT;
    short Local_name_errors_COUNT;
    short Local_name_to_cached_designation_alist_COUNT;
    short Local_names_not_associated_with_roles_COUNT;
    short Local_namestring_generator_COUNT;
    short Local_nupec_variable_count_COUNT;
    short Local_paste_event_queue_COUNT;
    short Local_source_code_control_buffer_COUNT;
    short Local_source_code_control_number_of_characters_COUNT;
    short Local_ui_client_test_mode_p_COUNT;
    short Localization_context_COUNT;
    short Locked_to_kb_qm_COUNT;
    short Log_file_count_COUNT;
    short Log_file_default_pathname_qm_COUNT;
    short Log_file_message_count_COUNT;
    short Log_file_message_count_at_last_update_COUNT;
    short Log_file_outputting_qm_COUNT;
    short Log_file_parameters_COUNT;
    short Log_file_pathnames_COUNT;
    short Log_file_stream_COUNT;
    short Log_file_string_COUNT;
    short Log_file_time_at_last_update_COUNT;
    short Log_file_time_at_open_COUNT;
    short Log_file_writing_message_qm_COUNT;
    short Log_post_mortem_ring_buffer_to_file_p_COUNT;
    short Log_simple_string_data_COUNT;
    short Log_simple_string_reclaims_COUNT;
    short Logbook_page_class_description_COUNT;
    short Logbook_parameters_COUNT;
    short Logbook_view_count_COUNT;
    short Logical_parameter_class_description_COUNT;
    short Logical_variable_class_description_COUNT;
    short Login_handler_COUNT;
    short Login_handler_fsn_COUNT;
    short Long_array_cons_counter_COUNT;
    short Long_operation_notification_has_been_put_up_qm_COUNT;
    short Long_simple_gensym_string_counts_COUNT;
    short Long_simple_gensym_strings_COUNT;
    short Long_thrashing_cost_update_interval_COUNT;
    short Long_variable_class_description_COUNT;
    short Lookup_cons_counter_COUNT;
    short Loose_bottom_edge_of_visible_workspace_area_COUNT;
    short Loose_end_class_description_COUNT;
    short Loose_end_spot_count_COUNT;
    short Loose_left_edge_of_visible_workspace_area_COUNT;
    short Loose_right_edge_of_visible_workspace_area_COUNT;
    short Loose_top_edge_of_visible_workspace_area_COUNT;
    short Low_and_high_values_specified_for_vertical_axis_qm_COUNT;
    short Low_bound_system_variable_for_get_current_bounds_for_plot_COUNT;
    short Low_bound_system_variable_for_get_current_min_and_max_for_plot_from_history_COUNT;
    short Low_value_for_horizontal_axis_COUNT;
    short Low_value_for_horizontal_grid_lines_COUNT;
    short Low_value_for_vertical_axis_COUNT;
    short Low_value_for_vertical_grid_lines_COUNT;
    short Lower_match_rank_for_player_eyes_p_COUNT;
    short Lr0_follow_COUNT;
    short Lru_element_count_COUNT;
    short Lt_asterisk_gt_COUNT;
    short Lt_backslash_gt_COUNT;
    short Lt_colon_gt_COUNT;
    short Lt_comma_gt_COUNT;
    short Lt_dot_gt_COUNT;
    short Lt_double_quote_gt_COUNT;
    short Lt_end_of_sequence_gt_COUNT;
    short Lt_exclamation_gt_COUNT;
    short Lt_hyphen_gt_COUNT;
    short Lt_left_angle_bracket_gt_COUNT;
    short Lt_left_bracket_gt_COUNT;
    short Lt_right_angle_bracket_gt_COUNT;
    short Lt_right_bracket_gt_COUNT;
    short Lt_semicolon_gt_COUNT;
    short Lt_sharp_sign_gt_COUNT;
    short Lt_slash_gt_COUNT;
    short Lt_space_gt_COUNT;
    short Lt_tilde_gt_COUNT;
    short Machine_model_var_COUNT;
    short Macroexpanding_for_instruction_expander_COUNT;
    short Main_kb_being_read_qm_COUNT;
    short Main_menu_choices_COUNT;
    short Main_model_runtime_info_COUNT;
    short Maintain_stack_of_current_part_descriptions_p_COUNT;
    short Maintaining_g2ds_interface_status_changed_p_COUNT;
    short Maintaining_gsi_interface_status_changed_p_COUNT;
    short Make_gsi_instance_existing_instance_COUNT;
    short Making_distribution_system_qm_COUNT;
    short Managed_bignum_pool_COUNT;
    short Many_more_data_points_than_pixels_qm_COUNT;
    short Mark_for_modules_with_unsaved_changes_COUNT;
    short Marker_for_meter_class_description_COUNT;
    short Master_hierarchy_reconciliation_switches_COUNT;
    short Match_pattern_for_inspect_binding_vector_COUNT;
    short Match_regular_expression_for_g2_stream_directory_hook_COUNT;
    short Max_gsi_sensors_in_a_group_COUNT;
    short Max_stack_index_COUNT;
    short Max_var_index_COUNT;
    short Maximum_clock_tick_length_COUNT;
    short Maximum_file_name_length_qm_COUNT;
    short Maximum_height_COUNT;
    short Maximum_length_for_sax_strings_COUNT;
    short Maximum_length_of_ascii_string_COUNT;
    short Maximum_length_of_kana_string_COUNT;
    short Maximum_log_file_name_prefix_length_qm_COUNT;
    short Maximum_number_of_array_or_list_elements_to_describe_COUNT;
    short Maximum_number_of_slots_in_structure_type_COUNT;
    short Maximum_number_of_tries_to_create_temp_file_COUNT;
    short Maximum_object_passing_bandwidth_COUNT;
    short Maximum_region_complexity_COUNT;
    short Maximum_retries_for_foreign_image_connection_COUNT;
    short Maximum_significant_decimal_digits_in_gensym_float_COUNT;
    short Maximum_time_slice_size_COUNT;
    short Maximum_width_COUNT;
    short Maximum_x_value_for_new_data_COUNT;
    short Maximum_y_value_COUNT;
    short Maximum_y_value_for_new_data_COUNT;
    short Maximum_y_value_for_pixel_COUNT;
    short May_create_simulation_subtable_from_module_data_p_COUNT;
    short May_return_from_breakpoint_COUNT;
    short Media_stream_count_COUNT;
    short Memory_category_count_COUNT;
    short Memory_limit_info_count_COUNT;
    short Memory_limit_variable_names_for_decacheable_structures_COUNT;
    short Memory_used_for_interned_gensym_strings_COUNT;
    short Memory_used_for_interned_text_strings_COUNT;
    short Memory_walk_verbose_p_COUNT;
    short Menu_button_spot_count_COUNT;
    short Menu_choose_state_count_COUNT;
    short Menu_class_description_COUNT;
    short Menu_clean_up_menu_to_keep_COUNT;
    short Menu_colors_COUNT;
    short Menu_colors_sorted_alphabetically_COUNT;
    short Menu_colors_sorted_by_hue_COUNT;
    short Menu_item_spot_count_COUNT;
    short Menu_items_for_parsing_COUNT;
    short Menu_pane_spot_count_COUNT;
    short Menu_parameters_COUNT;
    short Menu_title_spot_count_COUNT;
    short Menu_workspace_class_description_COUNT;
    short Merge_pathnames_rules_COUNT;
    short Merge_pathnames_rules_sorted_p_COUNT;
    short Message_board_class_description_COUNT;
    short Message_board_parameters_COUNT;
    short Message_class_description_COUNT;
    short Message_completion_interval_COUNT;
    short Message_definition_class_description_COUNT;
    short Message_illegal_symbol_text_string_contains_a_newline_COUNT;
    short Message_illegal_symbol_text_string_contains_fffe_COUNT;
    short Message_illegal_symbol_text_string_contains_ffff_COUNT;
    short Message_illegal_symbol_text_string_empty_COUNT;
    short Message_illegal_symbol_text_string_too_long_COUNT;
    short Meter_class_description_COUNT;
    short Meter_lag_time_variables_COUNT;
    short Meter_or_dial_spot_count_COUNT;
    short Meter_spot_count_COUNT;
    short Metered_clock_tick_length_COUNT;
    short Method_class_description_COUNT;
    short Method_declaration_class_description_COUNT;
    short Milliseconds_between_retries_for_foreign_image_connection_COUNT;
    short Milliseconds_to_sleep_after_connection_on_pc_platforms_COUNT;
    short Milliseconds_to_sleep_before_connecting_to_foreign_image_COUNT;
    short Min_string_length_to_report_COUNT;
    short Minimal_character_description_count_COUNT;
    short Minimal_fragmentation_seeds_COUNT;
    short Minimnal_bandwidth_for_resumable_sequence_range_COUNT;
    short Minimum_and_maximum_y_value_set_qm_COUNT;
    short Minimum_bandwidth_per_timeslice_COUNT;
    short Minimum_distance_between_fins_COUNT;
    short Minimum_distance_for_data_points_COUNT;
    short Minimum_grid_height_COUNT;
    short Minimum_grid_width_COUNT;
    short Minimum_number_of_blocks_for_spacial_index_COUNT;
    short Minimum_number_of_blocks_to_retain_spacial_index_COUNT;
    short Minimum_simulation_time_increment_COUNT;
    short Minimum_x_value_for_new_data_COUNT;
    short Minimum_y_value_COUNT;
    short Minimum_y_value_for_new_data_COUNT;
    short Minimum_y_value_for_pixel_COUNT;
    short Minus_one_integer_COUNT;
    short Miscellaneous_parameters_COUNT;
    short Missing_local_names_already_reported_COUNT;
    short Modal_menu_state_count_COUNT;
    short Model_definition_class_description_COUNT;
    short Model_queue_count_COUNT;
    short Model_runtime_info_count_COUNT;
    short Models_used_p_COUNT;
    short Modify_control_action_type_count_COUNT;
    short Modify_control_structure_count_COUNT;
    short Modify_dialog_structure_count_COUNT;
    short Modularity_checking_COUNT;
    short Module_information_COUNT;
    short Module_required_by_relationships_COUNT;
    short Module_search_path_tokenizer_COUNT;
    short Modules_and_system_tables_a_list_COUNT;
    short Modules_considered_in_loading_schedule_so_far_COUNT;
    short Modules_listed_so_far_COUNT;
    short Modules_loaded_in_this_group_COUNT;
    short Modules_scheduled_so_far_COUNT;
    short Modules_scheduled_so_far_by_save_all_modules_of_kb_COUNT;
    short Modules_that_have_already_been_loaded_COUNT;
    short Modules_to_translate_verbosely_COUNT;
    short Most_fixnum_digits_COUNT;
    short Most_lefthand_float_digits_COUNT;
    short Most_negative_fixnum_as_string_COUNT;
    short Most_recent_bandwidth_per_timeslice_qm_COUNT;
    short Most_recent_defun_warned_for_catch_qm_COUNT;
    short Most_recent_defun_warned_for_unwind_protect_qm_COUNT;
    short Most_recent_extremum_maximum_for_pixel_p_COUNT;
    short Most_recent_extremum_maximum_p_COUNT;
    short Most_recent_g2_time_COUNT;
    short Most_recent_trend_chart_checked_COUNT;
    short Most_recent_xml_checksum_differences_COUNT;
    short Most_righthand_float_zeros_COUNT;
    short Mouse_drag_detector_state_count_COUNT;
    short Mouse_pointer_count_COUNT;
    short Mouse_pointer_of_frame_COUNT;
    short Mouse_watch_state_count_COUNT;
    short Mouse_x_in_workspace_COUNT;
    short Mouse_y_in_workspace_COUNT;
    short Move_dragging_state_count_COUNT;
    short Ms_to_wait_for_cvs_COUNT;
    short Msw_cyrillic_code_map_COUNT;
    short Multiframe_table_spot_count_COUNT;
    short Multiplicative_counter_for_evaluation_COUNT;
    short Multiplier_for_turning_off_data_collection_COUNT;
    short Multiply_wild_regular_expression_node_count_COUNT;
    short Mutable_slot_description_list_head_COUNT;
    short N_32bit_constants_COUNT;
    short Name_box_class_description_COUNT;
    short Name_box_spot_count_COUNT;
    short Name_for_find_menu_item_COUNT;
    short Name_for_local_home_COUNT;
    short Name_of_current_editor_command_qm_COUNT;
    short Name_of_customer_in_ok_file_COUNT;
    short Name_of_file_slot_description_COUNT;
    short Name_of_kb_being_read_COUNT;
    short Name_of_module_being_read_qm_COUNT;
    short Name_text_string_for_kb_being_read_COUNT;
    short Named_gensym_structure_count_COUNT;
    short Names_and_info_for_chaining_COUNT;
    short Names_and_sizes_for_decacheable_structures_COUNT;
    short Names_of_grammars_to_add_rules_to_COUNT;
    short Names_used_for_more_than_one_item_COUNT;
    short Namestring_for_kb_being_read_COUNT;
    short Native_alias_creation_dialog_COUNT;
    short Native_dialog_count_COUNT;
    short Native_dialog_handle_parity_COUNT;
    short Native_editor_already_updated_COUNT;
    short Native_font_count_COUNT;
    short Native_image_plane_options_COUNT;
    short Native_image_plane_updated_by_client_COUNT;
    short Native_login_dialog_COUNT;
    short Native_menu_counter_COUNT;
    short Native_menu_id_to_handle_and_item_number_table_COUNT;
    short Native_menu_table_COUNT;
    short Native_menu_unique_id_counter_COUNT;
    short Native_printer_information_COUNT;
    short Native_printing_color_differences_COUNT;
    short Native_printing_icon_x_in_window_COUNT;
    short Native_printing_icon_y_in_window_COUNT;
    short Native_simple_dialog_state_count_COUNT;
    short Native_window_client_operation_COUNT;
    short Native_window_count_COUNT;
    short Native_window_heartbeat_task_COUNT;
    short Native_window_notices_enter_and_leave_events_p_COUNT;
    short Native_window_updated_by_client_COUNT;
    short Need_to_check_plist_p_COUNT;
    short Needed_domain_COUNT;
    short Negative_shutdown_interval_for_disallowed_icp_connection_COUNT;
    short Network_octet_buffer_length_COUNT;
    short New_byte_code_body_list_COUNT;
    short New_compiled_byte_code_body_list_COUNT;
    short New_dateline_qm_COUNT;
    short New_descriptions_COUNT;
    short New_g2_classic_ui_p_COUNT;
    short New_goto_tag_counter_COUNT;
    short New_position_of_horizontal_elevator_of_frame_COUNT;
    short New_position_of_vertical_elevator_of_frame_COUNT;
    short New_saved_kb_format_p_COUNT;
    short New_table_COUNT;
    short New_table_background_spot_count_COUNT;
    short New_table_cell_spot_count_COUNT;
    short New_table_spot_count_COUNT;
    short New_value_computed_in_formula_qm_COUNT;
    short Newline_characters_COUNT;
    short Next_character_for_kb_qm_COUNT;
    short Next_class_bit_number_COUNT;
    short Next_continuation_function_qm_COUNT;
    short Next_element_to_be_sorted_qm_COUNT;
    short Next_eq_hash_value_COUNT;
    short Next_info_COUNT;
    short Next_info_reclaimer_qm_COUNT;
    short Next_native_eq_dialog_handle_COUNT;
    short Next_object_index_property_number_COUNT;
    short Next_old_style_return_function_qm_COUNT;
    short Next_serial_number_to_be_generated_COUNT;
    short Next_stack_frame_var_location_COUNT;
    short Nil_indicator_COUNT;
    short Nil_interned_COUNT;
    short Nms_constructing_built_in_menus_p_COUNT;
    short Nms_menu_count_COUNT;
    short Nms_menu_hash_table_COUNT;
    short Nms_menu_item_count_COUNT;
    short Nms_reclaim_hook_COUNT;
    short No_arg_COUNT;
    short No_data_server_error_COUNT;
    short No_grouping_tag_for_grouping_specification_COUNT;
    short No_saved_initial_value_COUNT;
    short No_value_COUNT;
    short Node_id_for_uuid_COUNT;
    short Node_id_for_uuid_uses_ethernet_address_p_COUNT;
    short Nodes_for_generalized_dos_filename_parser_COUNT;
    short Nodes_for_unix_filename_parser_COUNT;
    short Nodes_for_vms_filename_parser_COUNT;
    short Non_context_top_level_binding_forms_COUNT;
    short Non_kb_workspace_class_description_COUNT;
    short Non_kb_workspace_image_plane_spot_count_COUNT;
    short Non_menu_choices_COUNT;
    short Non_procedure_root_invocations_COUNT;
    short Normal_completion_count_COUNT;
    short Note_as_kb_state_change_qm_COUNT;
    short Note_blocks_in_tformat_COUNT;
    short Note_kb_state_changes_via_system_procedures_qm_COUNT;
    short Note_things_encountered_during_role_service_qm_COUNT;
    short Notification_data_version_map_COUNT;
    short Noting_changes_to_kb_p_COUNT;
    short Null_char_COUNT;
    short Number_of_contexts_allocated_COUNT;
    short Number_of_horizontal_grid_lines_COUNT;
    short Number_of_icp_bytes_for_message_series_COUNT;
    short Number_of_icp_bytes_in_message_group_COUNT;
    short Number_of_icp_bytes_left_in_current_buffer_COUNT;
    short Number_of_icp_bytes_left_in_message_series_COUNT;
    short Number_of_icp_bytes_ready_to_read_COUNT;
    short Number_of_icp_bytes_to_fill_buffer_COUNT;
    short Number_of_kb_characters_so_far_qm_COUNT;
    short Number_of_kb_lines_so_far_COUNT;
    short Number_of_ksc_codes_COUNT;
    short Number_of_lexing_tables_in_cache_COUNT;
    short Number_of_memory_regions_COUNT;
    short Number_of_no_binds_COUNT;
    short Number_of_raster_oddspaces_COUNT;
    short Number_of_significant_digits_COUNT;
    short Number_of_simulated_variables_processed_COUNT;
    short Number_of_variables_to_process_at_a_time_COUNT;
    short Number_of_vertical_grid_lines_COUNT;
    short Nupec_catch_up_mode_caught_up_qm_COUNT;
    short Nupec_synchronize_variable_or_parameter_count_COUNT;
    short Object_building_problem_count_COUNT;
    short Object_class_description_COUNT;
    short Object_definition_class_description_COUNT;
    short Object_file_pathname_for_machine_COUNT;
    short Object_map_plist_for_icp_tree_COUNT;
    short Object_passing_info_count_COUNT;
    short Object_pool_meters_COUNT;
    short Objects_to_not_consider_qm_COUNT;
    short Obsolete_frame_note_types_from_modularity_development_COUNT;
    short Off_window_color_map_COUNT;
    short Ok_authorized_packages_COUNT;
    short Ok_authorized_products_COUNT;
    short Ok_class_description_COUNT;
    short Ok_expiration_date_qm_COUNT;
    short Ok_file_saving_mode_qm_COUNT;
    short Ok_file_token_cons_counter_COUNT;
    short Ok_file_token_count_COUNT;
    short Ok_make_g2_secure_qm_COUNT;
    short Ok_maximum_number_of_concurrent_floating_telewindows_allowed_COUNT;
    short Ok_maximum_number_of_concurrent_floating_tw2_allowed_COUNT;
    short Ok_modified_COUNT;
    short Ok_number_of_processes_authorized_COUNT;
    short Old_exposed_region_COUNT;
    short Old_timespan_system_variable_for_compute_trend_chart_time_bounds_COUNT;
    short On_monochrome_raster_list_p_COUNT;
    short On_window_with_drawing_COUNT;
    short On_window_without_drawing_COUNT;
    short One_integer_COUNT;
    short One_sequence_of_following_tokens_only_p_COUNT;
    short Only_impose_device_set_widths_to_squeeze_qm_COUNT;
    short Operation_around_record_of_items_made_incomplete_COUNT;
    short Operation_of_graphic_element_COUNT;
    short Operative_task_list_COUNT;
    short Optimized_constant_op_codes_COUNT;
    short Optimized_constant_pc_COUNT;
    short Optimized_constant_vector_COUNT;
    short Optimized_constant_vector_index_COUNT;
    short Optional_modules_map_COUNT;
    short Orientation_horizontal_p_COUNT;
    short Orientation_of_frame_COUNT;
    short Original_kb_state_plist_written_qm_COUNT;
    short Out_of_memory_handler_COUNT;
    short Outer_native_image_plane_COUNT;
    short Outermost_stack_frame_var_binding_qm_COUNT;
    short Output_only_table_spot_count_COUNT;
    short Output_vector_for_object_COUNT;
    short Output_window_for_printing_qm_COUNT;
    short Outputting_to_gensym_string_COUNT;
    short Outputting_to_wide_string_COUNT;
    short Outside_window_spot_count_COUNT;
    short Outstanding_float_function_floats_COUNT;
    short Outstanding_frame_vector_count_COUNT;
    short Overflow_byte_count_COUNT;
    short Override_eliminate_for_gsi_no_utf_g_p_COUNT;
    short Override_eliminate_for_gsi_p_COUNT;
    short Override_preferred_editor_COUNT;
    short Overriding_alignment_COUNT;
    short Oversized_simple_float_array_pool_memory_usage_COUNT;
    short Oversized_simple_vector_pool_counts_COUNT;
    short Overview_pane_spot_count_COUNT;
    short Package_preparation_mode_COUNT;
    short Pad_for_ok_file_reader_COUNT;
    short Page_class_description_COUNT;
    short Paint_only_target_monochrome_raster_p_COUNT;
    short Painting_for_graph_activation_p_COUNT;
    short Pane_background_spot_count_COUNT;
    short Pane_border_spot_count_COUNT;
    short Pane_component_spot_count_COUNT;
    short Pane_count_COUNT;
    short Pane_for_debugger_pause_COUNT;
    short Pane_spot_count_COUNT;
    short Parameter_class_description_COUNT;
    short Parent_trend_chart_COUNT;
    short Parse_object_count_COUNT;
    short Parse_table_count_COUNT;
    short Parsing_context_count_COUNT;
    short Parsing_token_count_COUNT;
    short Part_exceptions_from_parents_COUNT;
    short Part_feature_enter_methods_COUNT;
    short Part_feature_exit_methods_COUNT;
    short Part_feature_indexes_COUNT;
    short Part_feature_recall_stack_COUNT;
    short Part_features_to_write_COUNT;
    short Part_index_COUNT;
    short Part_stack_cons_counter_COUNT;
    short Part_text_size_parameters_COUNT;
    short Partial_command_count_COUNT;
    short Partition_details_of_current_branch_of_frame_COUNT;
    short Partition_float_union_COUNT;
    short Partition_long_union_COUNT;
    short Parts_of_annotated_frames_currently_erased_COUNT;
    short Path_cons_counter_COUNT;
    short Pathname_component_token_menu_button_spot_count_COUNT;
    short Pathname_for_disabling_g2_hangul_star_command_line_COUNT;
    short Pathname_for_disabling_g2_init_command_line_COUNT;
    short Pathname_for_disabling_g2_kanji_star_command_line_COUNT;
    short Pathname_for_disabling_g2_kb_command_line_COUNT;
    short Pathname_for_disabling_g2_minm_star_command_line_COUNT;
    short Pathname_for_disabling_g2_module_map_command_line_COUNT;
    short Pathname_for_disabling_g2_ok_command_line_COUNT;
    short Pathname_for_disabling_g2v11_ok_command_line_COUNT;
    short Pathname_for_disabling_g2v12_ok_command_line_COUNT;
    short Pathname_for_disabling_g2v51_ok_command_line_COUNT;
    short Pathname_for_disabling_g2v5_ok_command_line_COUNT;
    short Pathname_for_disabling_g2v6_ok_command_line_COUNT;
    short Pathname_for_disabling_g2v7_ok_command_line_COUNT;
    short Pathname_for_disabling_g2v83_ok_command_line_COUNT;
    short Pathname_for_disabling_g2v8_ok_command_line_COUNT;
    short Pathname_for_disabling_g2v9_ok_command_line_COUNT;
    short Pathname_for_disabling_tw_hangul_star_command_line_COUNT;
    short Pathname_for_disabling_tw_kanji_star_command_line_COUNT;
    short Pathname_for_disabling_tw_minm_star_command_line_COUNT;
    short Pathname_for_disabling_tw_ok_command_line_COUNT;
    short Pathname_for_disabling_twv11_ok_command_line_COUNT;
    short Pathname_for_disabling_twv12_ok_command_line_COUNT;
    short Pathname_for_disabling_twv5_ok_command_line_COUNT;
    short Pathname_for_disabling_twv6_ok_command_line_COUNT;
    short Pathname_for_disabling_twv7_ok_command_line_COUNT;
    short Pathname_for_disabling_twv8_ok_command_line_COUNT;
    short Pathname_for_disabling_twv9_ok_command_line_COUNT;
    short Pathname_for_distribution_binaries_qm_COUNT;
    short Pathname_with_default_type_if_required_for_module_pathnames_qm_COUNT;
    short Pattern_checking_inverse_references_COUNT;
    short Pending_activity_count_COUNT;
    short Pending_native_dialogs_COUNT;
    short Pending_write_reference_list_COUNT;
    short Percent_running_COUNT;
    short Permanent_mutable_list_COUNT;
    short Permit_cvs_timeout_dialog_p_COUNT;
    short Permit_spacial_index_p_COUNT;
    short Permit_transfer_of_permanent_items_p_COUNT;
    short Permitted_restriction_set_COUNT;
    short Phrase_copying_needs_annotation_rehashing_COUNT;
    short Phrase_pool_cons_counter_COUNT;
    short Phrase_rule_completion_count_COUNT;
    short Ping_seq_id_array_COUNT;
    short Pixmap_count_COUNT;
    short Place_for_for_telewindows_modernization_COUNT;
    short Place_reference_internals_count_COUNT;
    short Platform_independent_print_spool_command_file_name_COUNT;
    short Player_cons_counter_COUNT;
    short Player_control_stack_COUNT;
    short Player_current_instruction_COUNT;
    short Player_definition_stack_COUNT;
    short Player_icp_connection_COUNT;
    short Player_lexical_binding_stack_COUNT;
    short Player_location_stack_COUNT;
    short Player_mouse_x_COUNT;
    short Player_mouse_y_COUNT;
    short Player_named_locations_COUNT;
    short Player_pace_COUNT;
    short Player_require_modules_already_sent_COUNT;
    short Player_state_COUNT;
    short Player_target_gensym_window_g2_struct_qm_COUNT;
    short Player_value_stack_COUNT;
    short Plist_from_end_element_qm_COUNT;
    short Plist_has_been_checked_p_COUNT;
    short Plist_of_corresponding_icp_object_maps_for_font_maps_COUNT;
    short Plot_class_description_COUNT;
    short Plot_connector_painting_buffer_head_COUNT;
    short Plot_connector_painting_buffer_limit_COUNT;
    short Plot_connector_painting_buffer_size_COUNT;
    short Plot_connector_painting_buffer_tail_COUNT;
    short Plot_data_ring_buffer_count_COUNT;
    short Plot_marker_qm_COUNT;
    short Plot_max_qm_COUNT;
    short Plot_min_and_max_qm_COUNT;
    short Plot_min_qm_COUNT;
    short Pm_max_length_COUNT;
    short Pm_slot_names_COUNT;
    short Pm_temp_string_COUNT;
    short Pointer_for_dial_class_description_COUNT;
    short Poly_line_pattern_COUNT;
    short Poly_line_style_COUNT;
    short Poly_line_width_COUNT;
    short Poly_vertices_COUNT;
    short Polygon_fill_color_difference_COUNT;
    short Polygon_fill_pattern_COUNT;
    short Pop_fonts_stack_COUNT;
    short Popup_frames_available_COUNT;
    short Position_in_file_slot_description_COUNT;
    short Possible_label_dispatch_destination_COUNT;
    short Possible_phrase_count_COUNT;
    short Post_analyzer_warning_note_qm_COUNT;
    short Post_analyzer_warning_notes_for_generic_simulation_formulas_qm_COUNT;
    short Post_compiler_warning_note_qm_COUNT;
    short Post_draw_methods_for_text_box_formats_COUNT;
    short Post_kb_loading_consistency_analysis_COUNT;
    short Post_loading_functions_will_be_executed_again_later_qm_COUNT;
    short Post_mortem_internal_buffer_COUNT;
    short Post_mortem_report_buffer_COUNT;
    short Post_mortem_ring_buffer_logfile_line_count_COUNT;
    short Post_mortem_ring_buffer_logfile_namestring_COUNT;
    short Post_mortem_ring_buffer_logfile_stream_COUNT;
    short Postpone_cell_erase_until_redraw_p_COUNT;
    short Postscript_composite_object_mapping_COUNT;
    short Postscript_computed_variables_mapping_COUNT;
    short Postscript_current_graph_line_drawing_index_COUNT;
    short Postscript_definition_operation_counter_COUNT;
    short Postscript_emit_composite_object_without_name_COUNT;
    short Postscript_emit_integers_as_color_differences_COUNT;
    short Postscript_emitting_definition_COUNT;
    short Postscript_object_mapping_for_graph_renderings_COUNT;
    short Postscript_object_mapping_for_icon_renderings_COUNT;
    short Postscript_printing_icon_renderings_COUNT;
    short Preexisting_frames_COUNT;
    short Prefer_bitmap_to_scaled_outline_font_at_full_scale_qm_COUNT;
    short Prefer_bitmap_to_scaled_outline_font_qm_COUNT;
    short Prefer_bitmap_to_scaled_outline_if_matched_at_any_scale_qm_COUNT;
    short Prefer_kb_procedures_to_system_defined_p_COUNT;
    short Preprocessing_tokenizer_COUNT;
    short Preprocessor_errors_qm_COUNT;
    short Presentation_mode_COUNT;
    short Preserve_non_default_icon_colors_or_variables_qm_COUNT;
    short Previous_cascaded_ring_buffer_accessed_COUNT;
    short Previous_index_for_ring_buffer_COUNT;
    short Previous_modulus_counter_for_evaluation_COUNT;
    short Previous_timestamp_qm_COUNT;
    short Print_spooling_COUNT;
    short Print_wide_string_max_length_COUNT;
    short Printer_setup_COUNT;
    short Printing_cons_counter_COUNT;
    short Printing_format_COUNT;
    short Printing_graph_rendering_color_list_qm_COUNT;
    short Printing_icon_current_region_index_qm_COUNT;
    short Printing_in_progress_p_COUNT;
    short Printing_pass_number_COUNT;
    short Printing_stream_COUNT;
    short Priority_10_last_gensym_time_COUNT;
    short Priority_1_last_gensym_time_COUNT;
    short Priority_2_last_gensym_time_COUNT;
    short Priority_3_last_gensym_time_COUNT;
    short Priority_4_last_gensym_time_COUNT;
    short Priority_5_last_gensym_time_COUNT;
    short Priority_6_last_gensym_time_COUNT;
    short Priority_7_last_gensym_time_COUNT;
    short Priority_8_last_gensym_time_COUNT;
    short Priority_9_last_gensym_time_COUNT;
    short Priority_of_current_task_COUNT;
    short Priority_of_icp_control_messages_COUNT;
    short Priority_of_icp_message_service_COUNT;
    short Priority_of_next_task_COUNT;
    short Priority_of_rpc_service_COUNT;
    short Problems_reformatting_graph_qm_COUNT;
    short Proc_cons_counter_COUNT;
    short Procedure_alist_COUNT;
    short Procedure_branch_short_cuts_COUNT;
    short Procedure_class_description_COUNT;
    short Procedure_current_time_COUNT;
    short Procedure_end_time_COUNT;
    short Procedure_function_template_alist_COUNT;
    short Procedure_invocation_class_description_COUNT;
    short Procedure_invocation_count_COUNT;
    short Procedure_start_time_COUNT;
    short Procedures_to_warn_about_p_COUNT;
    short Proceed_with_edit_COUNT;
    short Process_checksum_for_image_data_p_COUNT;
    short Process_count_COUNT;
    short Process_initializations_alist_COUNT;
    short Process_instance_created_for_current_process_qm_COUNT;
    short Process_specific_system_pathname_COUNT;
    short Processing_as_fast_as_possible_models_qm_COUNT;
    short Production_count_COUNT;
    short Profiling_enabled_qm_COUNT;
    short Profiling_structure_COUNT;
    short Prohibited_restriction_set_COUNT;
    short Projecting_to_collect_description_for_new_table_COUNT;
    short Projection_COUNT;
    short Projection_computing_path_of_focus_COUNT;
    short Projection_drawing_COUNT;
    short Projection_focus_annotation_COUNT;
    short Projection_focus_cell_index_COUNT;
    short Projection_focus_cell_new_cached_value_COUNT;
    short Projection_focus_method_COUNT;
    short Projection_focus_path_COUNT;
    short Projection_funcall_on_focus_COUNT;
    short Projection_mode_COUNT;
    short Projection_of_new_table_accumulating_size_COUNT;
    short Projection_tracking_COUNT;
    short Projection_update_dependencies_COUNT;
    short Prop_grid_contents_COUNT;
    short Prop_grid_verb_count_COUNT;
    short Property_grid_count_COUNT;
    short Property_grid_node_count_COUNT;
    short Prune_token_categories_visited_more_than_once_p_COUNT;
    short Pseudo_attribute_count_COUNT;
    short Pseudo_class_slot_description_COUNT;
    short Pseudo_frame_count_COUNT;
    short Pseudo_instruction_stream_count_COUNT;
    short Pseudo_keysyms_COUNT;
    short Pulse_rate_multiplier_COUNT;
    short Pulse_rate_options_COUNT;
    short Purpose_of_extreme_edges_COUNT;
    short Purpose_of_frame_projecting_COUNT;
    short Push_button_cv_count_COUNT;
    short Put_current_evaluation_value_old_value_qm_COUNT;
    short Put_current_evaluation_value_return_value_COUNT;
    short Put_current_value_called_from_simulator_p_COUNT;
    short Quality_of_graphic_element_COUNT;
    short Quantitative_parameter_class_description_COUNT;
    short Quantitative_variable_class_description_COUNT;
    short Quantity_array_class_description_COUNT;
    short Quantity_cv_count_COUNT;
    short Quantity_list_class_description_COUNT;
    short Query_cell_stream_count_COUNT;
    short Question_mark_box_class_description_COUNT;
    short Queue_count_COUNT;
    short Queue_element_count_COUNT;
    short Queue_existential_rules_COUNT;
    short Queue_existential_rules_tail_COUNT;
    short Queue_item_cons_counter_COUNT;
    short Queue_of_active_gfi_input_interface_objects_COUNT;
    short Queue_of_active_gfi_output_interface_objects_COUNT;
    short Queue_of_active_uninterruptable_gfi_input_interface_objects_COUNT;
    short Queue_of_active_uninterruptable_gfi_output_interface_objects_COUNT;
    short Queue_of_classes_to_be_undefined_COUNT;
    short Radio_button_status_flags_COUNT;
    short Radio_button_status_flags_1_COUNT;
    short Ran_out_of_time_qm_COUNT;
    short Random_real_0_result_COUNT;
    short Random_state_array_COUNT;
    short Random_state_array_24_pointer_COUNT;
    short Random_state_array_current_pointer_COUNT;
    short Random_variation_COUNT;
    short Random_variation_2_COUNT;
    short Range_too_small_qm_COUNT;
    short Read_kb_buffer_COUNT;
    short Read_kb_buffer_index_COUNT;
    short Read_kb_buffer_length_COUNT;
    short Read_kb_next_character_COUNT;
    short Read_kb_stream_COUNT;
    short Read_ok_file_buffer_1_COUNT;
    short Read_xml_line_COUNT;
    short Reading_ghost_definitions_p_COUNT;
    short Reading_initial_plist_for_clear_text_kb_COUNT;
    short Reading_kb_p_COUNT;
    short Reading_ok_file_COUNT;
    short Readout_table_class_description_COUNT;
    short Readout_table_spot_count_COUNT;
    short Real_time_of_last_g2_tick_COUNT;
    short Real_time_to_tick_p_base_COUNT;
    short Really_large_byte_vector_COUNT;
    short Reason_for_type_failure_COUNT;
    short Receiving_resumable_object_count_COUNT;
    short Receiving_rpc_arglist_structure_count_COUNT;
    short Recent_enough_g2_revision_for_trend_charts_COUNT;
    short Recent_loaded_kbs_COUNT;
    short Reclaim_fonts_stack_COUNT;
    short Reclaim_text_value_from_postponed_erase_p_COUNT;
    short Reclaimed_strings_reported_COUNT;
    short Reclaimed_telewindows_boxes_COUNT;
    short Reclaimed_temporary_character_bitmaps_COUNT;
    short Reclaimed_things_COUNT;
    short Recompile_from_inspect_COUNT;
    short Recompile_on_next_load_COUNT;
    short Record_class_name_conflicts_qm_COUNT;
    short Record_definitional_name_conflicts_qm_COUNT;
    short Record_fixnum_time_units_of_sleep_this_clock_tick_qm_COUNT;
    short Record_of_class_name_conflicts_qm_COUNT;
    short Record_of_definitional_name_conflicts_qm_COUNT;
    short Recording_items_made_incomplete_qm_COUNT;
    short Recursive_depth_COUNT;
    short Recycled_icp_buffers_COUNT;
    short Recycled_resumption_conses_COUNT;
    short Recycled_variable_fill_icp_buffers_COUNT;
    short Redef_class_instance_COUNT;
    short Redo_saved_changes_COUNT;
    short Redraw_as_well_as_reformat_p_COUNT;
    short Reference_class_info_p_COUNT;
    short Reference_date_for_interval_encoding_COUNT;
    short Reference_serial_number_for_saved_detail_pane_description_COUNT;
    short Reference_structure_count_COUNT;
    short Reference_structures_originating_from_within_existence_predicate_COUNT;
    short Reformat_as_appropriate_qm_COUNT;
    short Refresh_all_windows_after_merging_qm_COUNT;
    short Refused_icp_listener_connections_COUNT;
    short Regexp_cons_counter_COUNT;
    short Regexp_preprocessing_parser_COUNT;
    short Region_1_info_COUNT;
    short Region_2_info_COUNT;
    short Region_3_info_COUNT;
    short Region_and_tile_x_offset_COUNT;
    short Region_and_tile_y_offset_COUNT;
    short Region_bounds_and_raster_count_COUNT;
    short Region_cons_counter_COUNT;
    short Region_invalidation_is_preferred_COUNT;
    short Region_x_max_qm_COUNT;
    short Region_x_offset_qm_COUNT;
    short Region_y_max_qm_COUNT;
    short Region_y_offset_qm_COUNT;
    short Registered_activities_symbol_array_COUNT;
    short Regular_expression_node_count_COUNT;
    short Regular_expression_node_for_set_of_characters_count_COUNT;
    short Regular_expression_node_for_single_character_count_COUNT;
    short Regular_expression_node_for_single_wild_character_count_COUNT;
    short Regular_expression_node_for_subexpression_count_COUNT;
    short Regular_expression_node_for_wild_characters_count_COUNT;
    short Regular_expression_parser_COUNT;
    short Regular_expression_tokenizer_COUNT;
    short Relation_class_description_COUNT;
    short Relation_instance_count_COUNT;
    short Relations_tag_list_COUNT;
    short Relative_time_pane_count_COUNT;
    short Releasing_kb_qm_COUNT;
    short Remaining_bytes_in_g2binary_data_COUNT;
    short Remaining_number_of_size_pieces_of_frame_COUNT;
    short Remaining_space_for_variable_size_pieces_of_frame_COUNT;
    short Remote_gsi_interface_list_COUNT;
    short Remote_procedure_call_count_COUNT;
    short Remote_procedure_declaration_class_description_COUNT;
    short Remote_procedure_identifier_array_COUNT;
    short Remote_procedure_identifier_count_COUNT;
    short Remote_procedure_item_passing_info_count_COUNT;
    short Remote_procedure_name_count_COUNT;
    short Remote_query_id_for_kb_recompile_COUNT;
    short Remote_value_is_binary_p_COUNT;
    short Remote_value_known_typetag_COUNT;
    short Remove_as_inferior_block_1_COUNT;
    short Remove_unused_labels_COUNT;
    short Rendezvous_successful_blocks_qm_COUNT;
    short Replacement_token_menu_button_spot_count_COUNT;
    short Report_filename_parsing_errors_in_development_p_COUNT;
    short Represented_frames_in_limbo_COUNT;
    short Required_definitions_COUNT;
    short Required_token_types_COUNT;
    short Resize_box_rubber_stamp_widget_COUNT;
    short Resize_box_spot_count_COUNT;
    short Resolving_definitional_name_conflicts_qm_COUNT;
    short Restrict_edits_to_modules_having_read_only_files_p_COUNT;
    short Result_end_time_system_variable_for_compute_trend_chart_time_bounds_COUNT;
    short Result_index_COUNT;
    short Result_of_ask_user_about_checking_pathname_out_for_editing_COUNT;
    short Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug_COUNT;
    short Result_timespan_system_variable_for_compute_trend_chart_time_bounds_COUNT;
    short Resumable_circular_node_count_COUNT;
    short Resumable_evaluation_sequence_node_count_COUNT;
    short Resumable_evaluation_sequence_node_mixin_count_COUNT;
    short Resumable_evaluation_structure_node_count_COUNT;
    short Resumable_history_node_count_COUNT;
    short Resumable_icp_node_mixin_count_COUNT;
    short Resumable_icp_object_mixin_count_COUNT;
    short Resumable_icp_read_ignore_p_COUNT;
    short Resumable_icp_state_COUNT;
    short Resumable_instance_node_mixin_count_COUNT;
    short Resumable_instance_or_complex_value_node_mixin_count_COUNT;
    short Resumable_list_node_mixin_count_COUNT;
    short Resumable_node_mixin_count_COUNT;
    short Resumable_object_list_node_count_COUNT;
    short Resumable_object_mixin_count_COUNT;
    short Resumable_object_node_count_COUNT;
    short Resumable_object_vector_node_count_COUNT;
    short Resumable_priority_of_gsi_data_service_COUNT;
    short Resumable_priority_of_gsi_rpc_service_COUNT;
    short Resumable_sequence_node_mixin_count_COUNT;
    short Resumable_value_list_node_count_COUNT;
    short Resumable_value_node_count_COUNT;
    short Resumable_value_vector_node_count_COUNT;
    short Resumable_vector_node_mixin_count_COUNT;
    short Return_from_ask_user_about_checking_pathname_out_for_editing_p_COUNT;
    short Return_from_breakpoint_task_COUNT;
    short Return_from_save_to_caller_for_continuation_qm_COUNT;
    short Return_statement_processed_qm_COUNT;
    short Return_to_waiting_for_cvs_p_COUNT;
    short Returned_values_description_COUNT;
    short Reusable_gensyms_COUNT;
    short Reverse_iso_latin1_special_character_code_map_COUNT;
    short Revert_marker_COUNT;
    short Revert_to_fuzzy_cache_p_COUNT;
    short Right_edge_in_window_of_graphic_element_COUNT;
    short Right_edge_of_draw_area_COUNT;
    short Right_edge_of_frame_COUNT;
    short Right_marker_for_cascading_menu_rubber_stamp_widget_COUNT;
    short Right_recursion_limit_list_COUNT;
    short Right_scroll_arrow_rubber_stamp_widget_COUNT;
    short Ring_buffer_for_history_time_COUNT;
    short Ring_buffer_queue_for_kfep_COUNT;
    short Ring_buffer_state_count_COUNT;
    short Ring_raster_for_graph_count_COUNT;
    short Role_and_domains_for_nth_element_expression_COUNT;
    short Role_caching_enabled_qm_COUNT;
    short Role_cons_counter_COUNT;
    short Role_names_and_local_names_for_runtime_items_COUNT;
    short Roman_character_map_COUNT;
    short Roman_font_special_character_code_map_COUNT;
    short Root_name_for_temp_file_COUNT;
    short Rotation_of_graphic_element_COUNT;
    short Row_COUNT;
    short Row_height_COUNT;
    short Row_maximum_COUNT;
    short Rpc_argument_count_override_qm_COUNT;
    short Rpc_argument_list_error_COUNT;
    short Rpc_object_arguments_to_run_or_schedule_qm_COUNT;
    short Rpc_throw_tag_COUNT;
    short Rule_certainty_var_COUNT;
    short Rule_class_description_COUNT;
    short Rule_expiration_var_COUNT;
    short Rule_instance_count_COUNT;
    short Rule_local_name_references_COUNT;
    short Ruling_for_dial_class_description_COUNT;
    short Ruling_for_meter_class_description_COUNT;
    short Run_traverse_kb_xml_object_type_COUNT;
    short Running_trace_function_p_COUNT;
    short Safe_to_access_attribute_display_update_interval_p_COUNT;
    short Sample_and_hold_plot_in_representation_update_p_COUNT;
    short Save_kb_state_for_system_procedure_save_COUNT;
    short Save_only_if_interrupting_qm_COUNT;
    short Saved_breakpoint_level_COUNT;
    short Saved_detail_pane_description_COUNT;
    short Saved_directories_for_module_truename_search_COUNT;
    short Saved_initial_status_COUNT;
    short Saved_local_var_vector_COUNT;
    short Saved_position_or_next_lower_thing_COUNT;
    short Saved_source_stepping_level_COUNT;
    short Saved_tracing_level_COUNT;
    short Saved_warning_level_COUNT;
    short Saving_context_count_COUNT;
    short Saving_kb_p_COUNT;
    short Saving_parameters_COUNT;
    short Saw_more_than_one_machine_authorization_qm_COUNT;
    short Scale_y_data_points_qm_COUNT;
    short Scaled_font_count_COUNT;
    short Scanning_subparts_of_block_COUNT;
    short Schedule_task_count_COUNT;
    short Scheduled_remote_procedure_start_count_COUNT;
    short Scheduler_enabled_qm_COUNT;
    short Scheduler_has_been_initialized_p_COUNT;
    short Scope_conses_COUNT;
    short Scrap_class_description_COUNT;
    short Scratch_add_item_to_workspace_COUNT;
    short Scratch_attribute_denotation_COUNT;
    short Scratch_character_rectangle_array_COUNT;
    short Scratch_custom_event_denotation_COUNT;
    short Scratch_incomplete_painting_action_COUNT;
    short Scratch_item_color_pattern_change_denotation_COUNT;
    short Scratch_item_event_denotation_COUNT;
    short Scratch_rectangle_region_COUNT;
    short Scratch_remove_item_from_workspace_COUNT;
    short Scratch_variable_value_denotation_COUNT;
    short Scratch_virtual_attribute_denotation_COUNT;
    short Scratchpad_raster_COUNT;
    short Scroll_bar_elevator_rubber_stamp_widget_COUNT;
    short Search_state_table_spot_count_COUNT;
    short Secret_return_value_COUNT;
    short See_also_for_warn_about_editing_item_COUNT;
    short Selected_file_progress_attributes_to_show_subsets_plist_COUNT;
    short Selected_module_load_request_attributes_to_show_subsets_plist_COUNT;
    short Selection_count_COUNT;
    short Selection_handle_icon_COUNT;
    short Selection_handle_spot_count_COUNT;
    short Selection_rectangle_state_count_COUNT;
    short Semi_open_category_map_COUNT;
    short Send_image_data_immediately_qm_COUNT;
    short Send_logbook_messages_to_console_p_COUNT;
    short Send_messages_to_console_p_COUNT;
    short Send_messages_to_logbook_p_COUNT;
    short Sending_i_am_alive_qm_COUNT;
    short Sending_resumable_object_count_COUNT;
    short Sensor_group_count_COUNT;
    short Sensor_groups_header_count_COUNT;
    short Separate_imminent_actions_p_COUNT;
    short Sequence_cons_counter_COUNT;
    short Serial_number_in_ok_file_COUNT;
    short Server_parameters_COUNT;
    short Service_workstations_COUNT;
    short Servicing_workstation_event_COUNT;
    short Servicing_workstation_qm_COUNT;
    short Set_of_all_component_kinds_COUNT;
    short Set_of_all_permanent_computation_style_COUNT;
    short Set_of_possible_phrases_count_COUNT;
    short Set_of_variables_to_simulation_evaluate_COUNT;
    short Shift_jis_transcoder_count_COUNT;
    short Shift_variant_for_cursor_movement_p_COUNT;
    short Short_duration_cv_count_COUNT;
    short Short_menus_qm_COUNT;
    short Short_representation_table_spot_count_COUNT;
    short Short_simple_gensym_string_counts_COUNT;
    short Short_simple_gensym_strings_COUNT;
    short Shortcut_bar_count_COUNT;
    short Show_deletions_in_xml_changes_p_COUNT;
    short Show_parameters_decoder_count_COUNT;
    short Show_procedure_invocation_hierarchy_on_debugger_pause_p_COUNT;
    short Show_stack_bytes_qm_COUNT;
    short Shredded_raster_count_COUNT;
    short Shunned_machine_ids_list_COUNT;
    short Shutdown_catch_tag_COUNT;
    short Shutdown_interval_for_disallowed_icp_connection_COUNT;
    short Shutdown_interval_for_disallowed_icp_connection_in_seconds_COUNT;
    short Sigfpe_COUNT;
    short Signal_code_registry_COUNT;
    short Simple_dialog_fill_text_p_COUNT;
    short Simple_dialog_plist_qm_COUNT;
    short Simple_dialog_title_qm_COUNT;
    short Simple_float_array_pool_memory_usage_COUNT;
    short Simple_for_image_plane_COUNT;
    short Simple_gensym_string_byte_use_counter_COUNT;
    short Simple_gensym_string_counter_COUNT;
    short Simple_item_spot_count_COUNT;
    short Simple_long_array_pool_memory_usage_COUNT;
    short Simple_string_stats_header_needed_COUNT;
    short Simple_string_stats_namestring_COUNT;
    short Simple_vector_pool_counts_COUNT;
    short Simple_vector_pool_memory_usage_COUNT;
    short Simulate_cons_counter_COUNT;
    short Simulate_proprietary_qm_COUNT;
    short Simulation_info_count_COUNT;
    short Simulation_no_value_COUNT;
    short Simulation_parameters_COUNT;
    short Simulation_procedure_completion_form_COUNT;
    short Simulation_subtable_class_description_COUNT;
    short Simulation_time_accumulator_COUNT;
    short Simulation_time_managed_float_COUNT;
    short Simulator_initialized_as_data_server_qm_COUNT;
    short Single_element_string_COUNT;
    short Single_escape_character_for_gensym_filenames_COUNT;
    short Size_of_cached_subsequence_for_resumable_history_COUNT;
    short Size_of_icon_slot_group_COUNT;
    short Skip_list_element_count_COUNT;
    short Skip_list_find_preds_COUNT;
    short Skip_list_find_succs_COUNT;
    short Slider_minimum_value_label_class_description_COUNT;
    short Slider_needle_class_description_COUNT;
    short Slider_readout_class_description_COUNT;
    short Slider_spot_count_COUNT;
    short Slot_alias_for_restrictions_COUNT;
    short Slot_component_descriptor_count_COUNT;
    short Slot_description_count_COUNT;
    short Slot_description_for_restrictions_COUNT;
    short Slot_description_for_slot_value_being_read_qm_COUNT;
    short Slot_name_for_write_frame_for_kb_COUNT;
    short Slot_pad_of_ok_file_reader_COUNT;
    short Slot_value_cons_counter_COUNT;
    short Slot_value_for_write_frame_for_kb_COUNT;
    short Slots_containing_circular_unnamed_simple_vectors_COUNT;
    short Slots_to_skip_saving_in_ok_files_COUNT;
    short Smoothed_subsecond_adjustment_COUNT;
    short Snapshot_invocation_info_count_COUNT;
    short Snapshot_of_block_count_COUNT;
    short Snapshots_of_related_blocks_COUNT;
    short Socket_count_COUNT;
    short Socket_output_buffer_count_COUNT;
    short Some_module_is_clear_text_p_COUNT;
    short Sorted_static_evaluate_role_dispatchers_COUNT;
    short Source_code_control_grammar_is_present_p_COUNT;
    short Source_code_control_is_enabled_by_default_COUNT;
    short Source_code_control_support_enabled_p_COUNT;
    short Source_designations_from_explicit_iteration_forms_COUNT;
    short Source_nupec_synchronization_count_COUNT;
    short Source_stepping_level_COUNT;
    short Sparse_array_count_COUNT;
    short Sparse_known_pathnames_list_COUNT;
    short Spawn_command_line_process_failure_COUNT;
    short Special_globally_known_references_COUNT;
    short Special_slot_names_for_memory_walk_COUNT;
    short Special_variable_for_use_value_macro_COUNT;
    short Specific_structure_for_current_workstation_context_COUNT;
    short Specified_kfep_index_filename_qm_COUNT;
    short Specified_kfep_kojin_filename_qm_COUNT;
    short Specified_kfep_main_filename_qm_COUNT;
    short Speedup_tagname_string_COUNT;
    short Speedup_tagname_string_index_COUNT;
    short Spinner_cv_count_COUNT;
    short Spot_count_COUNT;
    short Stack_change_cons_counter_COUNT;
    short Stack_cons_counter_COUNT;
    short Stack_eval_qm_COUNT;
    short Stack_expiration_COUNT;
    short Stack_frame_vars_ok_in_procedure_qm_COUNT;
    short Stack_instructions_COUNT;
    short Stack_node_count_COUNT;
    short Stack_node_instruction_count_COUNT;
    short Stack_nodes_to_reclaim_COUNT;
    short Stack_of_current_part_descriptions_COUNT;
    short Stack_of_deferred_notification_strings_COUNT;
    short Stack_of_slot_value_changes_COUNT;
    short Standard_8_bit_non_graphic_characters_skip_spec_COUNT;
    short Standard_gensym_color_alist_COUNT;
    short Star_character_index_COUNT;
    short Star_character_index_in_string_to_insert_qm_COUNT;
    short Star_character_index_of_change_qm_COUNT;
    short Star_character_index_past_deletion_qm_COUNT;
    short Star_current_indentation_COUNT;
    short Star_explicit_paragraph_or_newline_qm_COUNT;
    short Star_line_buffer_COUNT;
    short Star_line_buffer_fill_pointer_COUNT;
    short Star_line_buffer_limit_COUNT;
    short Star_line_index_COUNT;
    short Star_line_index_of_change_qm_COUNT;
    short Star_line_index_past_deletion_qm_COUNT;
    short Star_line_length_COUNT;
    short Star_lost_space_at_end_of_line_COUNT;
    short Star_next_text_tail_qm_COUNT;
    short Star_string_to_insert_qm_COUNT;
    short Star_text_line_COUNT;
    short Star_text_line_is_simple_qm_COUNT;
    short Star_text_string_to_insert_is_simple_qm_COUNT;
    short Star_this_text_tail_qm_COUNT;
    short State_transition_count_COUNT;
    short Statement_class_description_COUNT;
    short Static_attributes_COUNT;
    short Status_bar_count_COUNT;
    short Status_bar_pane_count_COUNT;
    short Status_pane_spot_count_COUNT;
    short Stepper_of_scroll_bar_spot_count_COUNT;
    short Strange_cons_COUNT;
    short Streams_cons_counter_COUNT;
    short Strict_subcategory_info_count_COUNT;
    short Strict_subcategory_info_last_category_1_COUNT;
    short Strict_subcategory_info_last_category_2_COUNT;
    short Strict_subcategory_info_last_result_COUNT;
    short Strict_subcategory_infos_exist_p_COUNT;
    short String_allocations_until_next_report_COUNT;
    short String_chars_to_print_COUNT;
    short String_for_returning_floats_COUNT;
    short String_pool_cons_counter_COUNT;
    short String_pool_number_to_malloc_COUNT;
    short String_reclaims_until_next_report_COUNT;
    short String_report_frequency_COUNT;
    short Stringw_should_not_cons_p_COUNT;
    short Structure_being_reclaimed_COUNT;
    short Structure_slot_not_bound_COUNT;
    short Structure_specs_allow_unknown_slots_p_COUNT;
    short Stub_length_to_use_qm_COUNT;
    short Sub_profiling_structure_count_COUNT;
    short Subcommand_menu_button_spot_count_COUNT;
    short Subcommand_state_count_COUNT;
    short Subframe_depth_COUNT;
    short Subordinate_text_box_class_description_COUNT;
    short Subpart_defaults_COUNT;
    short Subpart_exceptions_COUNT;
    short Subparts_COUNT;
    short Subtract_arrays_instead_qm_COUNT;
    short Subworkspace_currently_being_deleted_qm_COUNT;
    short Success_of_ok_file_reader_qm_COUNT;
    short Superior_frame_being_cloned_qm_COUNT;
    short Superior_frame_for_restrictions_frame_qm_COUNT;
    short Superior_frame_for_restrictions_superior_qm_COUNT;
    short Supported_combining_classes_COUNT;
    short Supported_control_actions_by_id_COUNT;
    short Supported_control_actions_by_symbol_COUNT;
    short Supported_dialog_component_types_COUNT;
    short Supported_ok_file_format_version_COUNT;
    short Supports_dialog_component_with_font_COUNT;
    short Supports_font_in_grid_view_COUNT;
    short Supports_transparent_color_index_COUNT;
    short Suppress_consistency_analysis_warnings_notes_qm_COUNT;
    short Suppress_notification_for_kb_save_qm_COUNT;
    short Suppress_scrolling_into_view_global_flag_qm_COUNT;
    short Suppress_updates_to_name_boxes_COUNT;
    short Suppress_updating_of_self_representations_qm_COUNT;
    short Suppress_updating_of_slot_value_representations_qm_COUNT;
    short Suppress_use_of_stack_of_slot_value_changes_p_COUNT;
    short Suppress_warning_message_header_qm_COUNT;
    short Symbol_array_class_description_COUNT;
    short Symbol_list_class_description_COUNT;
    short Symbol_tree_count_COUNT;
    short Symbolic_parameter_class_description_COUNT;
    short Symbolic_variable_class_description_COUNT;
    short Symbols_not_to_add_to_semi_open_category_directories_COUNT;
    short Synchronous_model_queue_COUNT;
    short Sysproc_cons_counter_COUNT;
    short Sysproc_continuation_table_COUNT;
    short System_class_method_tables_processed_qm_COUNT;
    short System_defined_rpcs_COUNT;
    short System_has_aborted_COUNT;
    short System_has_paused_COUNT;
    short System_is_running_COUNT;
    short System_item_class_description_COUNT;
    short System_quality_from_last_kb_read_COUNT;
    short System_revision_from_last_kb_read_COUNT;
    short System_rpc_count_COUNT;
    short System_rpc_instance_count_COUNT;
    short System_slot_accessor_COUNT;
    short System_statistics_writers_COUNT;
    short System_tables_read_for_this_module_COUNT;
    short System_version_from_kb_being_read_COUNT;
    short System_version_from_last_kb_read_COUNT;
    short System_version_of_current_gensym_product_line_COUNT;
    short System_window_COUNT;
    short System_window_title_and_info_text_string_qm_COUNT;
    short Systems_in_gensym_product_line_COUNT;
    short Systemtables_are_initialized_p_COUNT;
    short Systemtables_fixups_COUNT;
    short T2_dialog_result_alist_COUNT;
    short T2_nonce_data_count_COUNT;
    short T2_nonce_table_COUNT;
    short Tab_length_for_counter_report_COUNT;
    short Table_background_spot_count_COUNT;
    short Table_class_description_COUNT;
    short Table_header_spot_count_COUNT;
    short Table_menu_choices_COUNT;
    short Table_representation_update_schedule_COUNT;
    short Table_spot_count_COUNT;
    short Table_to_map_generic_method_id_to_generic_method_name_COUNT;
    short Table_to_map_structure_id_to_method_name_COUNT;
    short Tabular_function_class_description_COUNT;
    short Tabular_function_of_1_arg_class_description_COUNT;
    short Tabular_view_action_COUNT;
    short Tabular_view_count_COUNT;
    short Target_nupec_synchronization_count_COUNT;
    short Task_for_display_of_simulation_time_COUNT;
    short Task_scheduled_to_process_gsi_values_qm_COUNT;
    short Task_to_process_g2ds_values_COUNT;
    short Task_to_process_gsi_interfaces_COUNT;
    short Task_to_process_gsi_values_COUNT;
    short Task_to_run_service_workstations_final_COUNT;
    short Task_to_warn_user_of_previously_aborted_g2_COUNT;
    short Tcp_ip_port_offset_for_foreign_images_COUNT;
    short Tcp_listener_port_number_COUNT;
    short Tcp_socket_count_COUNT;
    short Tcpip_external_foreign_image_prologue_COUNT;
    short Telewindows_authorized_products_COUNT;
    short Telewindows_license_level_COUNT;
    short Telewindows_screen_utilization_COUNT;
    short Temporary_constant_count_COUNT;
    short Temporary_file_count_COUNT;
    short Temporary_g2binary_file_symbol_indices_COUNT;
    short Temporary_name_number_1_COUNT;
    short Temporary_name_number_2_COUNT;
    short Temporary_string_buffer_COUNT;
    short Temporary_workspace_class_description_COUNT;
    short Terminate_kb_save_stream_error_message_qm_COUNT;
    short Test_removal_of_unsigned_vector_16_COUNT;
    short Testing_parsing_context_locally_p_COUNT;
    short Text_array_class_description_COUNT;
    short Text_box_class_description_COUNT;
    short Text_box_cv_count_COUNT;
    short Text_box_spot_count_COUNT;
    short Text_conversion_style_for_transcoder_being_created_COUNT;
    short Text_inserter_spot_count_COUNT;
    short Text_line_for_line_of_text_of_graphic_element_COUNT;
    short Text_list_class_description_COUNT;
    short Text_marking_state_count_COUNT;
    short Text_of_definition_being_compiled_COUNT;
    short Text_parameter_class_description_COUNT;
    short Text_region_class_description_COUNT;
    short Text_representation_of_our_ok_object_COUNT;
    short Text_sequence_count_COUNT;
    short Text_spot_count_COUNT;
    short Text_time_stamp_seconds_COUNT;
    short Text_tokenization_state_count_COUNT;
    short Text_value_COUNT;
    short Text_value_from_postponed_erase_COUNT;
    short Text_variable_class_description_COUNT;
    short Text_xml_checksum_COUNT;
    short Tformat_fresh_line_is_newline_p_COUNT;
    short The_denotation_conversion_buffer_COUNT;
    short The_g2_defstruct_package_COUNT;
    short The_java_symbol_table_COUNT;
    short The_only_dynamic_computation_style_COUNT;
    short The_polygon_data_buffer_COUNT;
    short The_representation_handle_hashtable_COUNT;
    short The_transform_COUNT;
    short The_type_description_of_t_COUNT;
    short There_exists_p_COUNT;
    short There_is_a_current_kb_qm_COUNT;
    short Things_that_affect_this_formula_COUNT;
    short Thrashing_cost_update_interval_COUNT;
    short Thrashing_ratio_ring_buffer_count_COUNT;
    short Throws_from_breakpoints_are_possible_COUNT;
    short Tick_mark_part_to_draw_COUNT;
    short Tickmark_label_char_width_COUNT;
    short Tickmark_label_min_height_COUNT;
    short Tickmark_label_min_width_COUNT;
    short Tightest_end_of_loop_tag_COUNT;
    short Tightness_of_text_spot_for_click_to_edit_COUNT;
    short Tiled_raster_count_COUNT;
    short Tiling_pattern_count_COUNT;
    short Time_of_day_cv_count_COUNT;
    short Time_of_frame_edit_base_time_COUNT;
    short Time_of_last_call_to_set_user_password_COUNT;
    short Time_of_last_expiration_check_COUNT;
    short Time_of_last_synthetic_motion_event_qm_COUNT;
    short Time_of_last_thrashing_cost_update_COUNT;
    short Time_of_last_uuid_COUNT;
    short Time_slice_expired_p_COUNT;
    short Time_slice_start_time_COUNT;
    short Time_to_check_network_events_COUNT;
    short Time_used_to_adjust_histories_qm_COUNT;
    short Timestamp_cons_counter_COUNT;
    short Timing_parameters_COUNT;
    short Title_bar_spot_count_COUNT;
    short Token_cons_counter_COUNT;
    short Token_menu_button_spot_count_COUNT;
    short Token_sequence_location_plist_COUNT;
    short Token_stack_cons_counter_COUNT;
    short Tokenize_with_editing_context_p_COUNT;
    short Top_edge_in_window_of_graphic_element_COUNT;
    short Top_edge_of_draw_area_COUNT;
    short Top_edge_of_frame_COUNT;
    short Top_level_error_catcher_tag_COUNT;
    short Top_level_error_seen_COUNT;
    short Top_level_reference_tree_COUNT;
    short Top_level_state_count_COUNT;
    short Top_scroll_arrow_rubber_stamp_widget_COUNT;
    short Total_foreign_image_connection_checkup_interval_in_ms_COUNT;
    short Total_items_in_file_COUNT;
    short Total_length_of_current_gensym_string_COUNT;
    short Total_length_of_current_wide_string_COUNT;
    short Trace_compiled_function_execution_COUNT;
    short Trace_drawing_for_build_COUNT;
    short Trace_filename_parsing_p_COUNT;
    short Trace_image_planes_p_COUNT;
    short Trace_images_COUNT;
    short Trace_instruction_execution_COUNT;
    short Trace_messages_within_extent_of_rule_COUNT;
    short Trace_parsing_context_p_COUNT;
    short Trace_parsing_context_tokenizing_p_COUNT;
    short Trace_reshape_events_COUNT;
    short Trace_skip_data_service_i_am_alive_messages_p_COUNT;
    short Trace_system_calls_p_COUNT;
    short Trace_validate_p_COUNT;
    short Trace_workstation_events_COUNT;
    short Tracing_in_events_modules_p_COUNT;
    short Tracing_message_level_COUNT;
    short Tracked_items_call_depth_COUNT;
    short Tracked_items_call_vector_table_COUNT;
    short Tracking_items_grammar_installed_p_COUNT;
    short Tracking_items_p_COUNT;
    short Transcode_text_conversion_style_count_COUNT;
    short Transcoder_count_COUNT;
    short Transfer_dragging_state_count_COUNT;
    short Transfer_in_progress_COUNT;
    short Transform_image_operation_hint_COUNT;
    short Transient_connection_error_qm_COUNT;
    short Transients_to_delete_COUNT;
    short Transmitted_variable_fill_icp_buffers_COUNT;
    short Traverse_kb_queued_nodes_COUNT;
    short Traverse_kb_queued_nodes_tail_COUNT;
    short Traversing_kb_attribute_COUNT;
    short Traversing_xml_object_p_COUNT;
    short Tree_ordering_cons_counter_COUNT;
    short Tree_view_count_COUNT;
    short Tree_view_node_count_COUNT;
    short Trend_chart_layout_bottom_COUNT;
    short Trend_chart_layout_grid_COUNT;
    short Trend_chart_layout_left_COUNT;
    short Trend_chart_layout_parent_COUNT;
    short Trend_chart_layout_relative_time_pane_COUNT;
    short Trend_chart_layout_right_COUNT;
    short Trend_chart_layout_top_COUNT;
    short Trend_chart_pane_count_COUNT;
    short Trend_chart_spot_count_COUNT;
    short Trif_block_value_alist_COUNT;
    short True_value_update_recipient_class_description_COUNT;
    short Truth_value_array_class_description_COUNT;
    short Truth_value_list_class_description_COUNT;
    short Tw_deferred_actions_COUNT;
    short Tw_evaluate_trace_level_COUNT;
    short Tw_expiration_check_interval_COUNT;
    short Tw_source_debug_p_COUNT;
    short Twrite_control_as_ctrl_COUNT;
    short Twrite_fixnum_buffer_COUNT;
    short Type_at_type_failure_COUNT;
    short Type_description_count_COUNT;
    short Type_in_box_class_description_COUNT;
    short Type_in_box_spot_count_COUNT;
    short Type_in_text_box_class_description_COUNT;
    short Type_of_current_window_COUNT;
    short Type_of_current_workstation_context_COUNT;
    short Type_of_current_workstation_window_COUNT;
    short Type_of_file_being_read_COUNT;
    short Ucs_4_to_utf_8_1st_octet_table_COUNT;
    short Ui_callback_count_COUNT;
    short Ui_callbacks_COUNT;
    short Ui_client_interface_in_which_to_launch_recompilation_qm_COUNT;
    short Ui_client_interface_saved_icp_socket_list_COUNT;
    short Ui_client_interface_saved_session_list_COUNT;
    short Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing_COUNT;
    short Ui_client_interfaces_for_timeout_of_source_code_control_COUNT;
    short Ui_command_context_COUNT;
    short Unbound_value_for_ok_reader_COUNT;
    short Unevaluated_expression_COUNT;
    short Unicode_block_count_COUNT;
    short Unicode_byte_swapped_transcoder_count_COUNT;
    short Unicode_index_to_slavic_font_direct_index_map_COUNT;
    short Unicode_offset_for_gensym_cyrillic_COUNT;
    short Unicode_offset_for_gensym_general_punctuation_COUNT;
    short Unicode_offset_for_gensym_letterlike_symbol_COUNT;
    short Unicode_to_gb_2312_map_COUNT;
    short Unicode_to_jis_x_0208_map_COUNT;
    short Unicode_to_ks_c_5601_map_COUNT;
    short Unicode_transcoder_count_COUNT;
    short Unicode_ucs_2_transcoder_count_COUNT;
    short Uninteresting_block_spot_count_COUNT;
    short Unique_temp_filename_COUNT;
    short Unique_value_roles_COUNT;
    short Units_of_measure_declaration_class_description_COUNT;
    short Unix_command_callback_function_COUNT;
    short Unix_command_line_argument_count_COUNT;
    short Unix_command_line_arguments_COUNT;
    short Unix_command_line_arguments_as_text_strings_COUNT;
    short Unix_time_offset_for_encoding_COUNT;
    short Unix_time_offset_was_computed_qm_COUNT;
    short Unknown_references_COUNT;
    short Unread_char_of_ok_file_reader_qm_COUNT;
    short Unrecoverable_error_p_COUNT;
    short Unused_foreign_image_indices_COUNT;
    short Unused_known_offsets_COUNT;
    short Uo_memory_usage_information_hash_table_COUNT;
    short Update_before_loading_by_default_COUNT;
    short Update_images_in_xor_overlay_p_COUNT;
    short Update_menu_values_COUNT;
    short Updated_only_qm_COUNT;
    short Updated_users_list_COUNT;
    short Uri_reference_count_COUNT;
    short Use_current_time_for_next_uuid_COUNT;
    short Use_directory_lists_for_bootstrapping_qm_COUNT;
    short Use_interpreter_debug_format_COUNT;
    short Use_jit_p_COUNT;
    short Use_minimal_time_slice_for_continue_current_kb_save_p_COUNT;
    short Use_new_message_group_for_send_icp_enlarge_index_space_p_COUNT;
    short Use_scaleable_set_widths_qm_COUNT;
    short Use_telewindows_clogging_mechanism_p_COUNT;
    short Use_type_info_COUNT;
    short Used_positional_command_line_argument_default_COUNT;
    short Used_remote_spawn_indices_qm_COUNT;
    short Useful_machine_authorization_info_COUNT;
    short User_defined_default_error_handling_procedure_fsn_COUNT;
    short User_defined_default_error_handling_procedure_qm_COUNT;
    short User_defined_logbook_handling_procedure_fsn_COUNT;
    short User_defined_logbook_handling_procedure_qm_COUNT;
    short User_defined_message_board_handling_procedure_fsn_COUNT;
    short User_defined_message_board_handling_procedure_qm_COUNT;
    short User_menu_choice_class_description_COUNT;
    short User_mode_alias_count_COUNT;
    short User_mouse_tracking_state_count_COUNT;
    short User_notified_of_uuid_uniqueness_problem_p_COUNT;
    short User_overridable_connection_slots_COUNT;
    short User_overridable_g2_array_slots_COUNT;
    short User_overridable_g2_list_slots_COUNT;
    short User_overridable_message_slots_COUNT;
    short User_overridable_object_slots_COUNT;
    short User_overridable_parameter_slots_COUNT;
    short User_overridable_variable_slots_COUNT;
    short User_package_in_this_lisp_COUNT;
    short User_random_seed_qm_COUNT;
    short Using_pending_write_reference_list_COUNT;
    short Using_temporary_g2binary_file_symbol_indices_p_COUNT;
    short Utf_7_transcoder_count_COUNT;
    short Utf_8_transcoder_count_COUNT;
    short Utf_g_ascii_as_much_as_possible_conversion_style_COUNT;
    short Utf_g_ascii_as_much_as_possible_transcoder_count_COUNT;
    short Utf_g_transcoder_count_COUNT;
    short Uuid_block_count_COUNT;
    short Uuid_block_hash_table_COUNT;
    short Uuid_for_next_frame_qm_COUNT;
    short Uuid_hash_block_table_for_merge_kb_COUNT;
    short Uuid_time_b0_COUNT;
    short Uuid_time_b1_COUNT;
    short Uuid_time_b2_COUNT;
    short Uuid_time_b3_COUNT;
    short Uuid_xml_checksum_COUNT;
    short Valid_token_actions_COUNT;
    short Value_array_class_description_COUNT;
    short Value_at_type_failure_COUNT;
    short Value_list_class_description_COUNT;
    short Value_xml_checksum_COUNT;
    short Var_vector_caching_backpatch_locations_COUNT;
    short Var_vector_decaching_backpatch_locations_COUNT;
    short Variable_class_description_COUNT;
    short Variable_group_update_structure_count_COUNT;
    short Variable_is_at_bottom_of_stack_qm_COUNT;
    short Variable_or_parameter_class_description_COUNT;
    short Variable_simulation_runtime_structure_count_COUNT;
    short Variables_that_did_not_have_values_COUNT;
    short Vars_settable_at_runtime_COUNT;
    short Vector_of_oversized_simple_float_array_pools_COUNT;
    short Vector_of_oversized_simple_vector_pools_COUNT;
    short Vector_of_simple_float_array_pools_COUNT;
    short Vector_of_simple_long_array_pools_COUNT;
    short Vector_of_simple_vector_pools_COUNT;
    short Vector_pool_cons_counter_COUNT;
    short Verbosity_level_COUNT;
    short Version_control_parameters_COUNT;
    short Vertical_axis_range_COUNT;
    short Vertical_grid_line_color_qm_COUNT;
    short Vertical_grid_line_spacing_COUNT;
    short Vertical_grid_line_width_COUNT;
    short Virtual_attribute_class_instance_header_type_of_slot_COUNT;
    short Virtual_attribute_count_COUNT;
    short Virtual_attributes_not_local_to_a_class_COUNT;
    short Vms_directory_filenames_can_dangle_p_COUNT;
    short Wait_interval_before_killing_foreign_process_COUNT;
    short Walking_menus_state_count_COUNT;
    short Warmboot_cons_counter_COUNT;
    short Warmboot_current_time_COUNT;
    short Warmboot_simulated_time_COUNT;
    short Warmbooting_qm_COUNT;
    short Warmbooting_with_catch_up_qm_COUNT;
    short Warning_message_level_COUNT;
    short Weighting_factors_for_thrashing_ratio_ring_buffers_COUNT;
    short Whitespace_characters_COUNT;
    short Whitespace_wide_characters_COUNT;
    short Wide_string_text_sequence_count_COUNT;
    short Wide_twrite_fixnum_buffer_COUNT;
    short Widget_pending_state_count_COUNT;
    short Width_for_change_size_qm_COUNT;
    short Window_for_bitmap_for_gsi_COUNT;
    short Window_instigating_this_rule_instance_qm_COUNT;
    short With_extreme_edges_COUNT;
    short With_icp_buffer_coelescing_scope_qm_COUNT;
    short Within_activate_for_kb_workspace_COUNT;
    short Within_backward_chaining_task_COUNT;
    short Within_delete_frame_scope_qm_COUNT;
    short Within_managed_object_scope_COUNT;
    short Within_simulate_until_consistent_with_gensym_time_COUNT;
    short Within_simulator_for_stack_error_qm_COUNT;
    short Within_writing_procedure_invocation_p_COUNT;
    short Word_spacing_for_line_of_text_of_graphic_element_COUNT;
    short Working_on_annotated_frame_COUNT;
    short Working_on_chart_COUNT;
    short Working_on_drawing_COUNT;
    short Working_on_drawing_image_plane_COUNT;
    short Working_on_drawing_pane_COUNT;
    short Working_on_drawing_schedule_COUNT;
    short Working_on_drawing_workspace_COUNT;
    short Working_on_lexical_computation_of_frame_COUNT;
    short Working_on_new_table_COUNT;
    short Working_on_variables_that_need_simulated_values_stack_qm_COUNT;
    short Workspace_background_spot_count_COUNT;
    short Workspace_class_description_COUNT;
    short Workspace_dock_spot_count_COUNT;
    short Workspace_for_current_draw_document_qm_COUNT;
    short Workspace_image_plane_per_window_COUNT;
    short Workspace_invalidation_handling_event_type_queue_COUNT;
    short Workspace_invalidation_handling_fsn_queue_COUNT;
    short Workspace_invalidation_handling_procedure_fsn_qm_COUNT;
    short Workspace_invalidation_handling_procedure_qm_COUNT;
    short Workspace_invalidation_handling_window_queue_COUNT;
    short Workspace_invalidation_handling_workspace_queue_COUNT;
    short Workspace_menu_choices_COUNT;
    short Workspace_name_box_class_description_COUNT;
    short Workspace_region_count_COUNT;
    short Workspace_view_count_COUNT;
    short Workstation_context_count_COUNT;
    short Workstation_context_frame_count_COUNT;
    short Workstation_context_with_selection_focus_count_COUNT;
    short Workstation_count_COUNT;
    short Workstation_event_count_COUNT;
    short Workstation_in_which_to_launch_recompilation_qm_COUNT;
    short Workstation_with_image_plane_being_refreshed_COUNT;
    short Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing_COUNT;
    short Workstations_with_their_stacks_for_timeout_of_source_code_control_COUNT;
    short Wrap_conservatively_COUNT;
    short Wrapper_references_for_left_side_of_formula_qm_COUNT;
    short Write_all_byte_code_bodies_for_kb_p_COUNT;
    short Write_annotations_indent_COUNT;
    short Write_annotations_part_pattern_stack_COUNT;
    short Write_annotations_suppress_the_p_COUNT;
    short Write_checksums_in_xml_file_p_COUNT;
    short Write_compound_slots_parseably_qm_COUNT;
    short Write_console_p_COUNT;
    short Write_diffs_after_saving_clear_text_p_COUNT;
    short Write_floats_accurately_p_COUNT;
    short Write_initial_icp_version_info_p_COUNT;
    short Write_proprietary_package_while_saving_xml_kb_COUNT;
    short Write_remote_value_items_kind_COUNT;
    short Write_strings_parsably_qm_COUNT;
    short Write_symbols_in_lower_case_qm_COUNT;
    short Write_symbols_parsably_qm_COUNT;
    short Write_value_of_gsi_item_p_COUNT;
    short Write_xml_attribute_change_old_value_p_COUNT;
    short Write_xml_object_items_collected_COUNT;
    short Writing_annotations_COUNT;
    short Writing_g2_rdf_file_p_COUNT;
    short Writing_icp_message_group_COUNT;
    short Writing_resumable_icp_messages_p_COUNT;
    short Writing_xml_cdata_p_COUNT;
    short Writing_xml_p_COUNT;
    short Wrote_first_annotation_flag_COUNT;
    short Ws_representation_slots_to_update_COUNT;
    short Ws_representation_type_count_COUNT;
    short X11_preinitialized_p_COUNT;
    short X_data_min_set_qm_COUNT;
    short X_debugging_on_COUNT;
    short X_in_window_for_finding_object_near_mouse_COUNT;
    short X_in_window_of_graphic_element_COUNT;
    short X_scale_of_graphic_element_COUNT;
    short X_value_on_graph_COUNT;
    short Xml_checksums_enabled_p_COUNT;
    short Xml_namespace_count_COUNT;
    short Xml_namespace_list_count_COUNT;
    short Xml_nil_COUNT;
    short Xml_node_count_COUNT;
    short Xml_node_list_count_COUNT;
    short Xml_object_changes_COUNT;
    short Xml_output_buffer_COUNT;
    short Xml_output_position_COUNT;
    short Xml_output_stream_COUNT;
    short Xml_structure_count_COUNT;
    short Xml_structures_extent_COUNT;
    short Xsd_datatypes_xml_namespace_prefix_COUNT;
    short Y_in_window_for_finding_object_near_mouse_COUNT;
    short Y_in_window_of_graphic_element_COUNT;
    short Y_scale_of_graphic_element_COUNT;
    short Year_at_compilation_time_COUNT;
    short ab_Dummy_var_COUNT;
};

#define A_list_of_classes_with_instances_in_modules_that_do_not_require_them SPECIAL_VALUE(A_list_of_classes_with_instances_in_modules_that_do_not_require_them)
#define A_list_of_relations_with_related_items_in_modules_that_do_not_require_them SPECIAL_VALUE(A_list_of_relations_with_related_items_in_modules_that_do_not_require_them)
#define Ab_package_1 SPECIAL_VALUE(Ab_package_1)
#define Ab_system_pathname SPECIAL_VALUE(Ab_system_pathname)
#define Abbreviate_frame_notes_p SPECIAL_VALUE(Abbreviate_frame_notes_p)
#define Abbreviate_wide_strings_for_legibility SPECIAL_VALUE(Abbreviate_wide_strings_for_legibility)
#define Abort_file_written_p SPECIAL_VALUE(Abort_file_written_p)
#define Abort_for_icp_catcher_qm SPECIAL_VALUE(Abort_for_icp_catcher_qm)
#define Abort_level_0_tag SPECIAL_VALUE(Abort_level_0_tag)
#define Absolutely_prohibited_restriction_set SPECIAL_VALUE(Absolutely_prohibited_restriction_set)
#define Absolutely_selected_choice_qm SPECIAL_VALUE(Absolutely_selected_choice_qm)
#define Accept_any_version_component_p SPECIAL_VALUE(Accept_any_version_component_p)
#define Access_direction_slot_description SPECIAL_VALUE(Access_direction_slot_description)
#define Access_error_count SPECIAL_VALUE(Access_error_count)
#define Action_button_class_description SPECIAL_VALUE(Action_button_class_description)
#define Action_templates SPECIAL_VALUE(Action_templates)
#define Active_icp_sockets SPECIAL_VALUE(Active_icp_sockets)
#define Activities_currently_being_converted_to_xml SPECIAL_VALUE(Activities_currently_being_converted_to_xml)
#define Activities_currently_being_laid_out SPECIAL_VALUE(Activities_currently_being_laid_out)
#define Activity_class_code_vector SPECIAL_VALUE(Activity_class_code_vector)
#define Actual_arg SPECIAL_VALUE(Actual_arg)
#define Add_as_item_referring_to_name_qm SPECIAL_VALUE(Add_as_item_referring_to_name_qm)
#define Adding_from_graph_rendering_p SPECIAL_VALUE(Adding_from_graph_rendering_p)
#define Additional_related_blocks SPECIAL_VALUE(Additional_related_blocks)
#define Adjustable_gensym_string_byte_use_counter SPECIAL_VALUE(Adjustable_gensym_string_byte_use_counter)
#define Adjustable_gensym_string_counter SPECIAL_VALUE(Adjustable_gensym_string_counter)
#define Adjustable_gensym_string_counts SPECIAL_VALUE(Adjustable_gensym_string_counts)
#define Adjustable_gensym_strings SPECIAL_VALUE(Adjustable_gensym_strings)
#define Align_selection_command_operations SPECIAL_VALUE(Align_selection_command_operations)
#define Alist_of_dialog_mappings SPECIAL_VALUE(Alist_of_dialog_mappings)
#define Alist_of_local_names_and_role_names SPECIAL_VALUE(Alist_of_local_names_and_role_names)
#define All_ab_font_names SPECIAL_VALUE(All_ab_font_names)
#define All_branch_destinations_possible SPECIAL_VALUE(All_branch_destinations_possible)
#define All_classes_for_cached_class_description_node_attributes SPECIAL_VALUE(All_classes_for_cached_class_description_node_attributes)
#define All_classes_for_cached_class_description_node_attributes_for_external_definition SPECIAL_VALUE(All_classes_for_cached_class_description_node_attributes_for_external_definition)
#define All_classes_for_indirectly_referenced_class SPECIAL_VALUE(All_classes_for_indirectly_referenced_class)
#define All_colors SPECIAL_VALUE(All_colors)
#define All_command_line_keyword_arguments SPECIAL_VALUE(All_command_line_keyword_arguments)
#define All_computation_instances_above_breakpoint SPECIAL_VALUE(All_computation_instances_above_breakpoint)
#define All_cons_pools SPECIAL_VALUE(All_cons_pools)
#define All_cycles_found_so_far_in_module_hierarchy SPECIAL_VALUE(All_cycles_found_so_far_in_module_hierarchy)
#define All_directory_namestrings_in_directory_of_names SPECIAL_VALUE(All_directory_namestrings_in_directory_of_names)
#define All_external_foreign_function_images_qm SPECIAL_VALUE(All_external_foreign_function_images_qm)
#define All_file_namestrings_in_directory_of_names SPECIAL_VALUE(All_file_namestrings_in_directory_of_names)
#define All_foreign_function_images_qm SPECIAL_VALUE(All_foreign_function_images_qm)
#define All_formats_in_module SPECIAL_VALUE(All_formats_in_module)
#define All_frames_with_simple_debugging_names SPECIAL_VALUE(All_frames_with_simple_debugging_names)
#define All_g2gl_operators SPECIAL_VALUE(All_g2gl_operators)
#define All_gensym_pathnames_containing_open_streams SPECIAL_VALUE(All_gensym_pathnames_containing_open_streams)
#define All_gesture_instruction_names SPECIAL_VALUE(All_gesture_instruction_names)
#define All_image_data_structures SPECIAL_VALUE(All_image_data_structures)
#define All_index_space_names SPECIAL_VALUE(All_index_space_names)
#define All_known_command_line_plist_elements SPECIAL_VALUE(All_known_command_line_plist_elements)
#define All_known_file_systems SPECIAL_VALUE(All_known_file_systems)
#define All_menu_heading_format_names SPECIAL_VALUE(All_menu_heading_format_names)
#define All_module_frame_notes_for_workspaces SPECIAL_VALUE(All_module_frame_notes_for_workspaces)
#define All_permanently_changed_things_are_marked SPECIAL_VALUE(All_permanently_changed_things_are_marked)
#define All_region_info SPECIAL_VALUE(All_region_info)
#define All_signal_handlers_registered_p SPECIAL_VALUE(All_signal_handlers_registered_p)
#define All_supported_2022_escape_sequences SPECIAL_VALUE(All_supported_2022_escape_sequences)
#define All_systems SPECIAL_VALUE(All_systems)
#define All_unicode_block_names SPECIAL_VALUE(All_unicode_block_names)
#define All_valid_superior_test_functions SPECIAL_VALUE(All_valid_superior_test_functions)
#define All_virtual_attributes SPECIAL_VALUE(All_virtual_attributes)
#define All_write_locks SPECIAL_VALUE(All_write_locks)
#define All_xml_checksums SPECIAL_VALUE(All_xml_checksums)
#define Allocated_byte_vector_16_vectors SPECIAL_VALUE(Allocated_byte_vector_16_vectors)
#define Allocated_strings_reported SPECIAL_VALUE(Allocated_strings_reported)
#define Allow_activation_of_name_boxes_p SPECIAL_VALUE(Allow_activation_of_name_boxes_p)
#define Allow_activation_of_table_items_p SPECIAL_VALUE(Allow_activation_of_table_items_p)
#define Allow_comparison_of_slot_value_to_parse_result SPECIAL_VALUE(Allow_comparison_of_slot_value_to_parse_result)
#define Allow_debugger_pause SPECIAL_VALUE(Allow_debugger_pause)
#define Allow_extensionless_dos_filenames_p SPECIAL_VALUE(Allow_extensionless_dos_filenames_p)
#define Allow_in_line_designations_qm SPECIAL_VALUE(Allow_in_line_designations_qm)
#define Allow_inline_evaluate_role_instructions_p SPECIAL_VALUE(Allow_inline_evaluate_role_instructions_p)
#define Allow_internal_procedure_environment_printing_qm SPECIAL_VALUE(Allow_internal_procedure_environment_printing_qm)
#define Allow_invalidate_on_printing_window_p SPECIAL_VALUE(Allow_invalidate_on_printing_window_p)
#define Allow_name_box_creation SPECIAL_VALUE(Allow_name_box_creation)
#define Allow_name_box_creation_without_workspace SPECIAL_VALUE(Allow_name_box_creation_without_workspace)
#define Allow_no_value_p SPECIAL_VALUE(Allow_no_value_p)
#define Allow_user_defined_logbook_handlers_p SPECIAL_VALUE(Allow_user_defined_logbook_handlers_p)
#define Alphabet_canonical_element_st_test SPECIAL_VALUE(Alphabet_canonical_element_st_test)
#define Alphabet_character_class_st_test SPECIAL_VALUE(Alphabet_character_class_st_test)
#define Alphabet_count_of_standard_state_transition_tests SPECIAL_VALUE(Alphabet_count_of_standard_state_transition_tests)
#define Alphabet_equality_st_test SPECIAL_VALUE(Alphabet_equality_st_test)
#define Alphabet_members SPECIAL_VALUE(Alphabet_members)
#define Alphabet_standard_state_transition_tests SPECIAL_VALUE(Alphabet_standard_state_transition_tests)
#define Alphabet_subset_function SPECIAL_VALUE(Alphabet_subset_function)
#define Already_mutated_evaluators SPECIAL_VALUE(Already_mutated_evaluators)
#define Alternate_chaining_queue SPECIAL_VALUE(Alternate_chaining_queue)
#define Alternate_symbols_for_translation SPECIAL_VALUE(Alternate_symbols_for_translation)
#define Always_impose_device_set_widths_qm SPECIAL_VALUE(Always_impose_device_set_widths_qm)
#define Always_make_runtime_nil_checks SPECIAL_VALUE(Always_make_runtime_nil_checks)
#define Always_recompile_on_load SPECIAL_VALUE(Always_recompile_on_load)
#define Always_use_current_time_for_uuid SPECIAL_VALUE(Always_use_current_time_for_uuid)
#define Analyze_for_consistency_in_progress SPECIAL_VALUE(Analyze_for_consistency_in_progress)
#define Analyzing_export_definition_for_consistency_p SPECIAL_VALUE(Analyzing_export_definition_for_consistency_p)
#define Annotation_count SPECIAL_VALUE(Annotation_count)
#define Any_cached_evaluator_slot_info_p SPECIAL_VALUE(Any_cached_evaluator_slot_info_p)
#define Append_into_arrays_and_lists SPECIAL_VALUE(Append_into_arrays_and_lists)
#define Archtypal_stripped_text SPECIAL_VALUE(Archtypal_stripped_text)
#define Args_for_g2gl_object_class_icon_description_override SPECIAL_VALUE(Args_for_g2gl_object_class_icon_description_override)
#define Arithmetic_errors_are_stack_errors_p SPECIAL_VALUE(Arithmetic_errors_are_stack_errors_p)
#define Array_initialization_evaluation_values_use_designations_p SPECIAL_VALUE(Array_initialization_evaluation_values_use_designations_p)
#define Arrow_button_class_description SPECIAL_VALUE(Arrow_button_class_description)
#define As_fast_as_possible_model_queue SPECIAL_VALUE(As_fast_as_possible_model_queue)
#define Ascii_to_kana_map SPECIAL_VALUE(Ascii_to_kana_map)
#define Asian_double_byte_count SPECIAL_VALUE(Asian_double_byte_count)
#define Assignment_section_forms SPECIAL_VALUE(Assignment_section_forms)
#define At_end_of_icp_message_block_qm SPECIAL_VALUE(At_end_of_icp_message_block_qm)
#define At_end_of_icp_message_group_qm SPECIAL_VALUE(At_end_of_icp_message_group_qm)
#define Attempting_save_via_system_procedure_qm SPECIAL_VALUE(Attempting_save_via_system_procedure_qm)
#define Attr_not_found SPECIAL_VALUE(Attr_not_found)
#define Attribute_display_spot_count SPECIAL_VALUE(Attribute_display_spot_count)
#define Attribute_file_input_frame SPECIAL_VALUE(Attribute_file_input_frame)
#define Attribute_items SPECIAL_VALUE(Attribute_items)
#define Attribute_mimic_count SPECIAL_VALUE(Attribute_mimic_count)
#define Attribute_name_errors SPECIAL_VALUE(Attribute_name_errors)
#define Attribute_name_represented_by_table_spot_count SPECIAL_VALUE(Attribute_name_represented_by_table_spot_count)
#define Attribute_name_xml_checksum SPECIAL_VALUE(Attribute_name_xml_checksum)
#define Attribute_nesting_depth SPECIAL_VALUE(Attribute_nesting_depth)
#define Attribute_represented_by_table_spot_count SPECIAL_VALUE(Attribute_represented_by_table_spot_count)
#define Attribute_table_spot_count SPECIAL_VALUE(Attribute_table_spot_count)
#define Attribute_value_represented_by_table_spot_count SPECIAL_VALUE(Attribute_value_represented_by_table_spot_count)
#define Attributes_collector SPECIAL_VALUE(Attributes_collector)
#define Attributes_collector_tail SPECIAL_VALUE(Attributes_collector_tail)
#define Attributes_of_history_element_structure_as_interned_list SPECIAL_VALUE(Attributes_of_history_element_structure_as_interned_list)
#define Attributes_of_history_specification_structure_as_interned_list SPECIAL_VALUE(Attributes_of_history_specification_structure_as_interned_list)
#define Authorized_products_of_this_machine SPECIAL_VALUE(Authorized_products_of_this_machine)
#define Authorized_user_class_description SPECIAL_VALUE(Authorized_user_class_description)
#define Authorized_user_records_of_g2_ok_file SPECIAL_VALUE(Authorized_user_records_of_g2_ok_file)
#define Authorized_users_list SPECIAL_VALUE(Authorized_users_list)
#define Authorizing_ok_pathname SPECIAL_VALUE(Authorizing_ok_pathname)
#define Automatic_deadlock_detection_frequency SPECIAL_VALUE(Automatic_deadlock_detection_frequency)
#define Automatic_deadlock_detection_task SPECIAL_VALUE(Automatic_deadlock_detection_task)
#define Automatically_resolve_conflicts_by_default SPECIAL_VALUE(Automatically_resolve_conflicts_by_default)
#define Autostart_after_doing_init_file_qm SPECIAL_VALUE(Autostart_after_doing_init_file_qm)
#define Autostart_reason_in_init_file_qm SPECIAL_VALUE(Autostart_reason_in_init_file_qm)
#define Available_8859_reverse_unicode_map_hash_vector_43_vectors SPECIAL_VALUE(Available_8859_reverse_unicode_map_hash_vector_43_vectors)
#define Available_backtrace_conses SPECIAL_VALUE(Available_backtrace_conses)
#define Available_backtrace_conses_tail SPECIAL_VALUE(Available_backtrace_conses_tail)
#define Available_blocks_hash_hash_vector_43_vectors SPECIAL_VALUE(Available_blocks_hash_hash_vector_43_vectors)
#define Available_byte_vector_conses SPECIAL_VALUE(Available_byte_vector_conses)
#define Available_byte_vector_conses_tail SPECIAL_VALUE(Available_byte_vector_conses_tail)
#define Available_call_hash_hash_vector_43_vectors SPECIAL_VALUE(Available_call_hash_hash_vector_43_vectors)
#define Available_class_description_conses SPECIAL_VALUE(Available_class_description_conses)
#define Available_class_description_conses_tail SPECIAL_VALUE(Available_class_description_conses_tail)
#define Available_compiler_conses SPECIAL_VALUE(Available_compiler_conses)
#define Available_compiler_conses_tail SPECIAL_VALUE(Available_compiler_conses_tail)
#define Available_connection_conses SPECIAL_VALUE(Available_connection_conses)
#define Available_connection_conses_tail SPECIAL_VALUE(Available_connection_conses_tail)
#define Available_custom_dialog_conses SPECIAL_VALUE(Available_custom_dialog_conses)
#define Available_custom_dialog_conses_tail SPECIAL_VALUE(Available_custom_dialog_conses_tail)
#define Available_dragging_conses SPECIAL_VALUE(Available_dragging_conses)
#define Available_dragging_conses_tail SPECIAL_VALUE(Available_dragging_conses_tail)
#define Available_duplicates_check_hash_table_hash_vector_50021_vectors SPECIAL_VALUE(Available_duplicates_check_hash_table_hash_vector_50021_vectors)
#define Available_dynamic_rule_displays_hash_vector_43_vectors SPECIAL_VALUE(Available_dynamic_rule_displays_hash_vector_43_vectors)
#define Available_entity_conses SPECIAL_VALUE(Available_entity_conses)
#define Available_entity_conses_tail SPECIAL_VALUE(Available_entity_conses_tail)
#define Available_eval_conses SPECIAL_VALUE(Available_eval_conses)
#define Available_eval_conses_tail SPECIAL_VALUE(Available_eval_conses_tail)
#define Available_filter_conses SPECIAL_VALUE(Available_filter_conses)
#define Available_filter_conses_tail SPECIAL_VALUE(Available_filter_conses_tail)
#define Available_float_array_conses SPECIAL_VALUE(Available_float_array_conses)
#define Available_float_array_conses_tail SPECIAL_VALUE(Available_float_array_conses_tail)
#define Available_fonts_conses SPECIAL_VALUE(Available_fonts_conses)
#define Available_fonts_conses_tail SPECIAL_VALUE(Available_fonts_conses_tail)
#define Available_foreign_function_registry_internal_hash_vector_131_vectors SPECIAL_VALUE(Available_foreign_function_registry_internal_hash_vector_131_vectors)
#define Available_frame_conses SPECIAL_VALUE(Available_frame_conses)
#define Available_frame_conses_tail SPECIAL_VALUE(Available_frame_conses_tail)
#define Available_frame_display_conses SPECIAL_VALUE(Available_frame_display_conses)
#define Available_frame_display_conses_tail SPECIAL_VALUE(Available_frame_display_conses_tail)
#define Available_frame_serial_conses SPECIAL_VALUE(Available_frame_serial_conses)
#define Available_frame_serial_conses_tail SPECIAL_VALUE(Available_frame_serial_conses_tail)
#define Available_frame_serial_number_to_item_table_hash_vector_67_vectors SPECIAL_VALUE(Available_frame_serial_number_to_item_table_hash_vector_67_vectors)
#define Available_g2_list_conses SPECIAL_VALUE(Available_g2_list_conses)
#define Available_g2_list_conses_tail SPECIAL_VALUE(Available_g2_list_conses_tail)
#define Available_g2ds_conses SPECIAL_VALUE(Available_g2ds_conses)
#define Available_g2ds_conses_tail SPECIAL_VALUE(Available_g2ds_conses_tail)
#define Available_generic_rule_instance_displays_hash_vector_43_vectors SPECIAL_VALUE(Available_generic_rule_instance_displays_hash_vector_43_vectors)
#define Available_gensym_conses SPECIAL_VALUE(Available_gensym_conses)
#define Available_gensym_conses_tail SPECIAL_VALUE(Available_gensym_conses_tail)
#define Available_gfi_conses SPECIAL_VALUE(Available_gfi_conses)
#define Available_gfi_conses_tail SPECIAL_VALUE(Available_gfi_conses_tail)
#define Available_gfi_spreadsheet_field_index_hash_vector_131_vectors SPECIAL_VALUE(Available_gfi_spreadsheet_field_index_hash_vector_131_vectors)
#define Available_grammar_conses SPECIAL_VALUE(Available_grammar_conses)
#define Available_grammar_conses_tail SPECIAL_VALUE(Available_grammar_conses_tail)
#define Available_graph_conses SPECIAL_VALUE(Available_graph_conses)
#define Available_graph_conses_tail SPECIAL_VALUE(Available_graph_conses_tail)
#define Available_graph_layout_conses SPECIAL_VALUE(Available_graph_layout_conses)
#define Available_graph_layout_conses_tail SPECIAL_VALUE(Available_graph_layout_conses_tail)
#define Available_graph_node_of_graphed_thing_hash_vector_43_vectors SPECIAL_VALUE(Available_graph_node_of_graphed_thing_hash_vector_43_vectors)
#define Available_graphics_conses SPECIAL_VALUE(Available_graphics_conses)
#define Available_graphics_conses_tail SPECIAL_VALUE(Available_graphics_conses_tail)
#define Available_gsi_conses SPECIAL_VALUE(Available_gsi_conses)
#define Available_gsi_conses_tail SPECIAL_VALUE(Available_gsi_conses_tail)
#define Available_hashed_rule_instance_hash_vector_43_vectors SPECIAL_VALUE(Available_hashed_rule_instance_hash_vector_43_vectors)
#define Available_history_conses SPECIAL_VALUE(Available_history_conses)
#define Available_history_conses_tail SPECIAL_VALUE(Available_history_conses_tail)
#define Available_icon_editor_conses SPECIAL_VALUE(Available_icon_editor_conses)
#define Available_icon_editor_conses_tail SPECIAL_VALUE(Available_icon_editor_conses_tail)
#define Available_icp_buffer_ref_count_conses SPECIAL_VALUE(Available_icp_buffer_ref_count_conses)
#define Available_icp_buffer_ref_count_conses_tail SPECIAL_VALUE(Available_icp_buffer_ref_count_conses_tail)
#define Available_icp_callback_conses SPECIAL_VALUE(Available_icp_callback_conses)
#define Available_icp_callback_conses_tail SPECIAL_VALUE(Available_icp_callback_conses_tail)
#define Available_icp_conses SPECIAL_VALUE(Available_icp_conses)
#define Available_icp_conses_tail SPECIAL_VALUE(Available_icp_conses_tail)
#define Available_indexed_attribute_parent_objects_hash_vector_43_vectors SPECIAL_VALUE(Available_indexed_attribute_parent_objects_hash_vector_43_vectors)
#define Available_installation_conses SPECIAL_VALUE(Available_installation_conses)
#define Available_installation_conses_tail SPECIAL_VALUE(Available_installation_conses_tail)
#define Available_item_or_name_hash_hash_vector_43_vectors SPECIAL_VALUE(Available_item_or_name_hash_hash_vector_43_vectors)
#define Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors SPECIAL_VALUE(Available_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors)
#define Available_java_conses SPECIAL_VALUE(Available_java_conses)
#define Available_java_conses_tail SPECIAL_VALUE(Available_java_conses_tail)
#define Available_jis_map_hash_vector_307_vectors SPECIAL_VALUE(Available_jis_map_hash_vector_307_vectors)
#define Available_journal_conses SPECIAL_VALUE(Available_journal_conses)
#define Available_journal_conses_tail SPECIAL_VALUE(Available_journal_conses_tail)
#define Available_kanji_font_cache_vector_137_vectors SPECIAL_VALUE(Available_kanji_font_cache_vector_137_vectors)
#define Available_kb_fsn_hash_table_hash_vector_131_vectors SPECIAL_VALUE(Available_kb_fsn_hash_table_hash_vector_131_vectors)
#define Available_kb_property_conses SPECIAL_VALUE(Available_kb_property_conses)
#define Available_kb_property_conses_tail SPECIAL_VALUE(Available_kb_property_conses_tail)
#define Available_long_array_conses SPECIAL_VALUE(Available_long_array_conses)
#define Available_long_array_conses_tail SPECIAL_VALUE(Available_long_array_conses_tail)
#define Available_lookup_conses SPECIAL_VALUE(Available_lookup_conses)
#define Available_lookup_conses_tail SPECIAL_VALUE(Available_lookup_conses_tail)
#define Available_module_required_by_relationships_hash_vector_43_vectors SPECIAL_VALUE(Available_module_required_by_relationships_hash_vector_43_vectors)
#define Available_native_font_set_width_equivalence_table_256_vectors SPECIAL_VALUE(Available_native_font_set_width_equivalence_table_256_vectors)
#define Available_native_icon_handle_hash_vector_43_vectors SPECIAL_VALUE(Available_native_icon_handle_hash_vector_43_vectors)
#define Available_nms_menu_for_hmenu_hash_vector_43_vectors SPECIAL_VALUE(Available_nms_menu_for_hmenu_hash_vector_43_vectors)
#define Available_non_kanji_font_vector_257_vectors SPECIAL_VALUE(Available_non_kanji_font_vector_257_vectors)
#define Available_object_circularity_hashtable_hash_vector_131_vectors SPECIAL_VALUE(Available_object_circularity_hashtable_hash_vector_131_vectors)
#define Available_ok_file_token_conses SPECIAL_VALUE(Available_ok_file_token_conses)
#define Available_ok_file_token_conses_tail SPECIAL_VALUE(Available_ok_file_token_conses_tail)
#define Available_part_stack_conses SPECIAL_VALUE(Available_part_stack_conses)
#define Available_part_stack_conses_tail SPECIAL_VALUE(Available_part_stack_conses_tail)
#define Available_path_conses SPECIAL_VALUE(Available_path_conses)
#define Available_path_conses_tail SPECIAL_VALUE(Available_path_conses_tail)
#define Available_phrase_pool_conses SPECIAL_VALUE(Available_phrase_pool_conses)
#define Available_phrase_pool_conses_tail SPECIAL_VALUE(Available_phrase_pool_conses_tail)
#define Available_player_conses SPECIAL_VALUE(Available_player_conses)
#define Available_player_conses_tail SPECIAL_VALUE(Available_player_conses_tail)
#define Available_printing_conses SPECIAL_VALUE(Available_printing_conses)
#define Available_printing_conses_tail SPECIAL_VALUE(Available_printing_conses_tail)
#define Available_proc_conses SPECIAL_VALUE(Available_proc_conses)
#define Available_proc_conses_tail SPECIAL_VALUE(Available_proc_conses_tail)
#define Available_procedure_invocations_hash_vector_43_vectors SPECIAL_VALUE(Available_procedure_invocations_hash_vector_43_vectors)
#define Available_queue_item_conses SPECIAL_VALUE(Available_queue_item_conses)
#define Available_queue_item_conses_tail SPECIAL_VALUE(Available_queue_item_conses_tail)
#define Available_regexp_conses SPECIAL_VALUE(Available_regexp_conses)
#define Available_regexp_conses_tail SPECIAL_VALUE(Available_regexp_conses_tail)
#define Available_region_conses SPECIAL_VALUE(Available_region_conses)
#define Available_region_conses_tail SPECIAL_VALUE(Available_region_conses_tail)
#define Available_representation_handle_hash_vector_109_vectors SPECIAL_VALUE(Available_representation_handle_hash_vector_109_vectors)
#define Available_reusable_gensyms SPECIAL_VALUE(Available_reusable_gensyms)
#define Available_role_conses SPECIAL_VALUE(Available_role_conses)
#define Available_role_conses_tail SPECIAL_VALUE(Available_role_conses_tail)
#define Available_scaled_font_kanji_font_cache_vector_1096_vectors SPECIAL_VALUE(Available_scaled_font_kanji_font_cache_vector_1096_vectors)
#define Available_scaled_font_non_kanji_font_vector_2049_vectors SPECIAL_VALUE(Available_scaled_font_non_kanji_font_vector_2049_vectors)
#define Available_sequence_conses SPECIAL_VALUE(Available_sequence_conses)
#define Available_sequence_conses_tail SPECIAL_VALUE(Available_sequence_conses_tail)
#define Available_sexp_annotation_hash_vector_43_vectors SPECIAL_VALUE(Available_sexp_annotation_hash_vector_43_vectors)
#define Available_simulate_conses SPECIAL_VALUE(Available_simulate_conses)
#define Available_simulate_conses_tail SPECIAL_VALUE(Available_simulate_conses_tail)
#define Available_slot_value_conses SPECIAL_VALUE(Available_slot_value_conses)
#define Available_slot_value_conses_tail SPECIAL_VALUE(Available_slot_value_conses_tail)
#define Available_stack_change_conses SPECIAL_VALUE(Available_stack_change_conses)
#define Available_stack_change_conses_tail SPECIAL_VALUE(Available_stack_change_conses_tail)
#define Available_stack_conses SPECIAL_VALUE(Available_stack_conses)
#define Available_stack_conses_tail SPECIAL_VALUE(Available_stack_conses_tail)
#define Available_streams_conses SPECIAL_VALUE(Available_streams_conses)
#define Available_streams_conses_tail SPECIAL_VALUE(Available_streams_conses_tail)
#define Available_string_pool_conses SPECIAL_VALUE(Available_string_pool_conses)
#define Available_string_pool_conses_tail SPECIAL_VALUE(Available_string_pool_conses_tail)
#define Available_sub_call_hash_hash_vector_43_vectors SPECIAL_VALUE(Available_sub_call_hash_hash_vector_43_vectors)
#define Available_subseries_of_values_64_vectors SPECIAL_VALUE(Available_subseries_of_values_64_vectors)
#define Available_sysproc_conses SPECIAL_VALUE(Available_sysproc_conses)
#define Available_sysproc_conses_tail SPECIAL_VALUE(Available_sysproc_conses_tail)
#define Available_sysproc_continuation_hashtable_hash_vector_131_vectors SPECIAL_VALUE(Available_sysproc_continuation_hashtable_hash_vector_131_vectors)
#define Available_tiling_patterns SPECIAL_VALUE(Available_tiling_patterns)
#define Available_timestamp_conses SPECIAL_VALUE(Available_timestamp_conses)
#define Available_timestamp_conses_tail SPECIAL_VALUE(Available_timestamp_conses_tail)
#define Available_token_conses SPECIAL_VALUE(Available_token_conses)
#define Available_token_conses_tail SPECIAL_VALUE(Available_token_conses_tail)
#define Available_token_stack_conses SPECIAL_VALUE(Available_token_stack_conses)
#define Available_token_stack_conses_tail SPECIAL_VALUE(Available_token_stack_conses_tail)
#define Available_tracked_items_call_vector_table_hash_vector_43_vectors SPECIAL_VALUE(Available_tracked_items_call_vector_table_hash_vector_43_vectors)
#define Available_tree_ordering_conses SPECIAL_VALUE(Available_tree_ordering_conses)
#define Available_tree_ordering_conses_tail SPECIAL_VALUE(Available_tree_ordering_conses_tail)
#define Available_ui_callback_table_hash_vector_43_vectors SPECIAL_VALUE(Available_ui_callback_table_hash_vector_43_vectors)
#define Available_uo_memory_usage_information_hash_vector_43_vectors SPECIAL_VALUE(Available_uo_memory_usage_information_hash_vector_43_vectors)
#define Available_user_hash_table_internal_hash_vector_43_vectors SPECIAL_VALUE(Available_user_hash_table_internal_hash_vector_43_vectors)
#define Available_variable_fill_icp_buffer_4096_vectors SPECIAL_VALUE(Available_variable_fill_icp_buffer_4096_vectors)
#define Available_vector_pool_conses SPECIAL_VALUE(Available_vector_pool_conses)
#define Available_vector_pool_conses_tail SPECIAL_VALUE(Available_vector_pool_conses_tail)
#define Available_warmboot_conses SPECIAL_VALUE(Available_warmboot_conses)
#define Available_warmboot_conses_tail SPECIAL_VALUE(Available_warmboot_conses_tail)
#define Available_workstation_contexts SPECIAL_VALUE(Available_workstation_contexts)
#define Axis SPECIAL_VALUE(Axis)
#define Axis_automatic SPECIAL_VALUE(Axis_automatic)
#define Axis_crossover SPECIAL_VALUE(Axis_crossover)
#define Axis_heading SPECIAL_VALUE(Axis_heading)
#define Axis_index SPECIAL_VALUE(Axis_index)
#define Axis_is_discrete_p SPECIAL_VALUE(Axis_is_discrete_p)
#define Axis_maximum SPECIAL_VALUE(Axis_maximum)
#define Axis_minimum SPECIAL_VALUE(Axis_minimum)
#define Axis_pane_count SPECIAL_VALUE(Axis_pane_count)
#define Axis_tickmark_count SPECIAL_VALUE(Axis_tickmark_count)
#define Axis_tickmark_count_as_fixnum SPECIAL_VALUE(Axis_tickmark_count_as_fixnum)
#define Axis_tickmark_label_frequency SPECIAL_VALUE(Axis_tickmark_label_frequency)
#define Axis_tickmark_label_max_digits_after_point SPECIAL_VALUE(Axis_tickmark_label_max_digits_after_point)
#define Axis_tickmark_label_max_digits_before_point SPECIAL_VALUE(Axis_tickmark_label_max_digits_before_point)
#define Axis_tickmark_label_max_digits_in_exponent SPECIAL_VALUE(Axis_tickmark_label_max_digits_in_exponent)
#define Axis_tickmark_step SPECIAL_VALUE(Axis_tickmark_step)
#define Background_color_value_from_postponed_erase SPECIAL_VALUE(Background_color_value_from_postponed_erase)
#define Background_color_value_of_graphic_element SPECIAL_VALUE(Background_color_value_of_graphic_element)
#define Background_print_workspace_process_state_block_count SPECIAL_VALUE(Background_print_workspace_process_state_block_count)
#define Background_processes SPECIAL_VALUE(Background_processes)
#define Background_processes_task SPECIAL_VALUE(Background_processes_task)
#define Backoff_limit SPECIAL_VALUE(Backoff_limit)
#define Backtrace_cons_counter SPECIAL_VALUE(Backtrace_cons_counter)
#define Backtrace_stack_for_internal_error SPECIAL_VALUE(Backtrace_stack_for_internal_error)
#define Backtrace_text_buffer_for_internal_error SPECIAL_VALUE(Backtrace_text_buffer_for_internal_error)
#define Backtrace_text_buffer_for_string_metering SPECIAL_VALUE(Backtrace_text_buffer_for_string_metering)
#define Backup_case_qm SPECIAL_VALUE(Backup_case_qm)
#define Backward_chaining_display_count SPECIAL_VALUE(Backward_chaining_display_count)
#define Backward_chaining_displays SPECIAL_VALUE(Backward_chaining_displays)
#define Backward_chaining_link_class_description SPECIAL_VALUE(Backward_chaining_link_class_description)
#define Bad_rule SPECIAL_VALUE(Bad_rule)
#define Base_36_digits_string SPECIAL_VALUE(Base_36_digits_string)
#define Base_code_body_return_tag SPECIAL_VALUE(Base_code_body_return_tag)
#define Base_reference SPECIAL_VALUE(Base_reference)
#define Baseline_in_window_for_line_of_text_of_graphic_element SPECIAL_VALUE(Baseline_in_window_for_line_of_text_of_graphic_element)
#define Basic_part SPECIAL_VALUE(Basic_part)
#define Basic_profiling_structure_count SPECIAL_VALUE(Basic_profiling_structure_count)
#define Basis_kb_frame_serial_number SPECIAL_VALUE(Basis_kb_frame_serial_number)
#define Best_text_matched_by_player SPECIAL_VALUE(Best_text_matched_by_player)
#define Bignum_overflow_count SPECIAL_VALUE(Bignum_overflow_count)
#define Binary_tree_element_count SPECIAL_VALUE(Binary_tree_element_count)
#define Binary_xml_checksum SPECIAL_VALUE(Binary_xml_checksum)
#define Bindable_keysyms SPECIAL_VALUE(Bindable_keysyms)
#define Bitmap_array_count SPECIAL_VALUE(Bitmap_array_count)
#define Bitmap_for_printing_qm SPECIAL_VALUE(Bitmap_for_printing_qm)
#define Block_change_count SPECIAL_VALUE(Block_change_count)
#define Block_class_description SPECIAL_VALUE(Block_class_description)
#define Block_near_mouse_cache_count SPECIAL_VALUE(Block_near_mouse_cache_count)
#define Block_of_frame SPECIAL_VALUE(Block_of_frame)
#define Blocking_socket_count SPECIAL_VALUE(Blocking_socket_count)
#define Blocks_to_delete_after_reading_kb SPECIAL_VALUE(Blocks_to_delete_after_reading_kb)
#define Blocks_to_delete_after_unsquirreling SPECIAL_VALUE(Blocks_to_delete_after_unsquirreling)
#define Blocks_with_bad_connections SPECIAL_VALUE(Blocks_with_bad_connections)
#define Blocks_with_connections_from_kb_read SPECIAL_VALUE(Blocks_with_connections_from_kb_read)
#define Blocks_with_relation_instances_from_kb_read SPECIAL_VALUE(Blocks_with_relation_instances_from_kb_read)
#define Blocks_with_specialized_method_qm SPECIAL_VALUE(Blocks_with_specialized_method_qm)
#define Blocks_with_subblocks_from_kb_read SPECIAL_VALUE(Blocks_with_subblocks_from_kb_read)
#define Bogus_preflight_from_printing_to_graphs SPECIAL_VALUE(Bogus_preflight_from_printing_to_graphs)
#define Bombout_clean_up_functions SPECIAL_VALUE(Bombout_clean_up_functions)
#define Boolean_composition_over_symbols_allows_top_level_symbols_p SPECIAL_VALUE(Boolean_composition_over_symbols_allows_top_level_symbols_p)
#define Bootstrap_information SPECIAL_VALUE(Bootstrap_information)
#define Bottom_edge_in_window_of_graphic_element SPECIAL_VALUE(Bottom_edge_in_window_of_graphic_element)
#define Bottom_edge_of_draw_area SPECIAL_VALUE(Bottom_edge_of_draw_area)
#define Bottom_edge_of_frame SPECIAL_VALUE(Bottom_edge_of_frame)
#define Bottom_scroll_arrow_rubber_stamp_widget SPECIAL_VALUE(Bottom_scroll_arrow_rubber_stamp_widget)
#define Bounding_box_class_description SPECIAL_VALUE(Bounding_box_class_description)
#define Bounding_box_spot_count SPECIAL_VALUE(Bounding_box_spot_count)
#define Bounding_box_state_count SPECIAL_VALUE(Bounding_box_state_count)
#define Bounding_state_count SPECIAL_VALUE(Bounding_state_count)
#define Bpel_xml_namespace SPECIAL_VALUE(Bpel_xml_namespace)
#define Break_if_name_inconsistency_qm SPECIAL_VALUE(Break_if_name_inconsistency_qm)
#define Breakpoint_level SPECIAL_VALUE(Breakpoint_level)
#define Breakpoints_enabled_p SPECIAL_VALUE(Breakpoints_enabled_p)
#define Buffer_for_internal_error_on_console SPECIAL_VALUE(Buffer_for_internal_error_on_console)
#define Buffer_for_internal_error_on_logbook SPECIAL_VALUE(Buffer_for_internal_error_on_logbook)
#define Buffer_for_read_file_into_string SPECIAL_VALUE(Buffer_for_read_file_into_string)
#define Buffer_for_string_metering SPECIAL_VALUE(Buffer_for_string_metering)
#define Buffer_for_write_internal_error SPECIAL_VALUE(Buffer_for_write_internal_error)
#define Buffer_index_of_ok_file_reader SPECIAL_VALUE(Buffer_index_of_ok_file_reader)
#define Buffer_length_of_ok_file_reader SPECIAL_VALUE(Buffer_length_of_ok_file_reader)
#define Buffer_of_ok_file_reader SPECIAL_VALUE(Buffer_of_ok_file_reader)
#define Buffer_of_resumable_p SPECIAL_VALUE(Buffer_of_resumable_p)
#define Buffered_plot_painting_color SPECIAL_VALUE(Buffered_plot_painting_color)
#define Buffered_plot_painting_line_style SPECIAL_VALUE(Buffered_plot_painting_line_style)
#define Buffered_plot_painting_one_pixel_in_seconds SPECIAL_VALUE(Buffered_plot_painting_one_pixel_in_seconds)
#define Buffered_plot_painting_plot SPECIAL_VALUE(Buffered_plot_painting_plot)
#define Buffered_plot_painting_style_arg SPECIAL_VALUE(Buffered_plot_painting_style_arg)
#define Buffered_plot_painting_value_axis SPECIAL_VALUE(Buffered_plot_painting_value_axis)
#define Buggy_polyline_p SPECIAL_VALUE(Buggy_polyline_p)
#define Built_in_character_codes SPECIAL_VALUE(Built_in_character_codes)
#define Button_class_description SPECIAL_VALUE(Button_class_description)
#define Button_down_state_count SPECIAL_VALUE(Button_down_state_count)
#define Button_label_class_description SPECIAL_VALUE(Button_label_class_description)
#define Button_menu_spot_count SPECIAL_VALUE(Button_menu_spot_count)
#define Button_spot_count SPECIAL_VALUE(Button_spot_count)
#define Buttons_in_button_down_state SPECIAL_VALUE(Buttons_in_button_down_state)
#define Bypass_add_class_export_info_attributes_p SPECIAL_VALUE(Bypass_add_class_export_info_attributes_p)
#define Bypass_fix_for_exported_method_overloading_p SPECIAL_VALUE(Bypass_fix_for_exported_method_overloading_p)
#define Byte_code_body_count SPECIAL_VALUE(Byte_code_body_count)
#define Byte_code_stream_count SPECIAL_VALUE(Byte_code_stream_count)
#define Byte_vector_16_pool_counts SPECIAL_VALUE(Byte_vector_16_pool_counts)
#define Byte_vector_16_pool_number_to_malloc SPECIAL_VALUE(Byte_vector_16_pool_number_to_malloc)
#define Byte_vector_16_pools SPECIAL_VALUE(Byte_vector_16_pools)
#define Byte_vector_cons_counter SPECIAL_VALUE(Byte_vector_cons_counter)
#define Bytes_allocated_for_image_tiles SPECIAL_VALUE(Bytes_allocated_for_image_tiles)
#define Bytes_consumed_by_one_undefaulted_lookup_slot SPECIAL_VALUE(Bytes_consumed_by_one_undefaulted_lookup_slot)
#define Bytes_in_allocated_byte_vector_16_vectors SPECIAL_VALUE(Bytes_in_allocated_byte_vector_16_vectors)
#define Bytes_per_double_float_simple_array_cached SPECIAL_VALUE(Bytes_per_double_float_simple_array_cached)
#define Bytes_per_long_simple_array_cached SPECIAL_VALUE(Bytes_per_long_simple_array_cached)
#define C_byte_code_body_result_1 SPECIAL_VALUE(C_byte_code_body_result_1)
#define C_byte_code_body_result_2 SPECIAL_VALUE(C_byte_code_body_result_2)
#define C_byte_code_body_result_3 SPECIAL_VALUE(C_byte_code_body_result_3)
#define C_byte_code_body_result_4 SPECIAL_VALUE(C_byte_code_body_result_4)
#define C_byte_code_body_result_5 SPECIAL_VALUE(C_byte_code_body_result_5)
#define C_byte_code_body_result_6 SPECIAL_VALUE(C_byte_code_body_result_6)
#define C_byte_code_body_result_7 SPECIAL_VALUE(C_byte_code_body_result_7)
#define C_byte_code_body_result_8 SPECIAL_VALUE(C_byte_code_body_result_8)
#define Cache_al_semantics_graph SPECIAL_VALUE(Cache_al_semantics_graph)
#define Cache_chinese_semantics_graph SPECIAL_VALUE(Cache_chinese_semantics_graph)
#define Cache_embedded_option_semantics_graph SPECIAL_VALUE(Cache_embedded_option_semantics_graph)
#define Cache_ent_semantics_graph SPECIAL_VALUE(Cache_ent_semantics_graph)
#define Cache_g1_semantics_graph SPECIAL_VALUE(Cache_g1_semantics_graph)
#define Cache_gfi_semantics_graph SPECIAL_VALUE(Cache_gfi_semantics_graph)
#define Cache_gsi_semantics_graph SPECIAL_VALUE(Cache_gsi_semantics_graph)
#define Cache_gspan_semantics_graph SPECIAL_VALUE(Cache_gspan_semantics_graph)
#define Cache_icp_semantics_graph SPECIAL_VALUE(Cache_icp_semantics_graph)
#define Cache_japanese_semantics_graph SPECIAL_VALUE(Cache_japanese_semantics_graph)
#define Cache_jl_semantics_graph SPECIAL_VALUE(Cache_jl_semantics_graph)
#define Cache_jp_semantics_graph SPECIAL_VALUE(Cache_jp_semantics_graph)
#define Cache_kfep_semantics_graph SPECIAL_VALUE(Cache_kfep_semantics_graph)
#define Cache_korean_semantics_graph SPECIAL_VALUE(Cache_korean_semantics_graph)
#define Cache_nupec_semantics_graph SPECIAL_VALUE(Cache_nupec_semantics_graph)
#define Cache_restricted_use_option_semantics_graph SPECIAL_VALUE(Cache_restricted_use_option_semantics_graph)
#define Cache_runtime_option_semantics_graph SPECIAL_VALUE(Cache_runtime_option_semantics_graph)
#define Cache_stack_and_locals SPECIAL_VALUE(Cache_stack_and_locals)
#define Cached_byte_code_body SPECIAL_VALUE(Cached_byte_code_body)
#define Cached_classes_for_backward_chaining SPECIAL_VALUE(Cached_classes_for_backward_chaining)
#define Cached_classes_for_forward_chaining SPECIAL_VALUE(Cached_classes_for_forward_chaining)
#define Cached_compareoperator SPECIAL_VALUE(Cached_compareoperator)
#define Cached_event_bit SPECIAL_VALUE(Cached_event_bit)
#define Cached_eventflag SPECIAL_VALUE(Cached_eventflag)
#define Cached_explanation_from_data_server_or_initial_value_count SPECIAL_VALUE(Cached_explanation_from_data_server_or_initial_value_count)
#define Cached_explanation_from_frame_count SPECIAL_VALUE(Cached_explanation_from_frame_count)
#define Cached_explanation_from_generic_formula_count SPECIAL_VALUE(Cached_explanation_from_generic_formula_count)
#define Cached_explanation_from_rule_count SPECIAL_VALUE(Cached_explanation_from_rule_count)
#define Cached_explanation_from_specific_formula_count SPECIAL_VALUE(Cached_explanation_from_specific_formula_count)
#define Cached_fellow_val SPECIAL_VALUE(Cached_fellow_val)
#define Cached_fixnum_start_time SPECIAL_VALUE(Cached_fixnum_start_time)
#define Cached_fixnum_time_limit_qm SPECIAL_VALUE(Cached_fixnum_time_limit_qm)
#define Cached_fixnum_time_qm SPECIAL_VALUE(Cached_fixnum_time_qm)
#define Cached_gensym_user_home_directory SPECIAL_VALUE(Cached_gensym_user_home_directory)
#define Cached_local_gensym_x11_display SPECIAL_VALUE(Cached_local_gensym_x11_display)
#define Cached_local_icp_version_info SPECIAL_VALUE(Cached_local_icp_version_info)
#define Cached_long_code_constant_form SPECIAL_VALUE(Cached_long_code_constant_form)
#define Cached_machine_id_qm SPECIAL_VALUE(Cached_machine_id_qm)
#define Cached_matching_machine_id_qm SPECIAL_VALUE(Cached_matching_machine_id_qm)
#define Cached_n SPECIAL_VALUE(Cached_n)
#define Cached_name_for_local_home SPECIAL_VALUE(Cached_name_for_local_home)
#define Cached_nstart SPECIAL_VALUE(Cached_nstart)
#define Cached_requiredgoodsize SPECIAL_VALUE(Cached_requiredgoodsize)
#define Cached_restrictions_alist SPECIAL_VALUE(Cached_restrictions_alist)
#define Cached_result SPECIAL_VALUE(Cached_result)
#define Cached_stack_frame_base SPECIAL_VALUE(Cached_stack_frame_base)
#define Cached_stack_program_counter SPECIAL_VALUE(Cached_stack_program_counter)
#define Cached_stack_program_counter_form SPECIAL_VALUE(Cached_stack_program_counter_form)
#define Cached_subj SPECIAL_VALUE(Cached_subj)
#define Cached_tcpip_listener_address_qm SPECIAL_VALUE(Cached_tcpip_listener_address_qm)
#define Cached_timed_out_foreign_function_name_qm SPECIAL_VALUE(Cached_timed_out_foreign_function_name_qm)
#define Cached_top_of_stack SPECIAL_VALUE(Cached_top_of_stack)
#define Cached_top_of_stack_form SPECIAL_VALUE(Cached_top_of_stack_form)
#define Cached_unknown_error_string_with_code_qm SPECIAL_VALUE(Cached_unknown_error_string_with_code_qm)
#define Calendar_cv_count SPECIAL_VALUE(Calendar_cv_count)
#define Call_check_node_attribute_value_p SPECIAL_VALUE(Call_check_node_attribute_value_p)
#define Call_statement_processed_qm SPECIAL_VALUE(Call_statement_processed_qm)
#define Called_within_clear_text_loading SPECIAL_VALUE(Called_within_clear_text_loading)
#define Called_within_locate_or_create_junction_block_definition SPECIAL_VALUE(Called_within_locate_or_create_junction_block_definition)
#define Calling_float_function_cleverly_p SPECIAL_VALUE(Calling_float_function_cleverly_p)
#define Calling_tformat_for_give_warning_qm SPECIAL_VALUE(Calling_tformat_for_give_warning_qm)
#define Cascaded_ring_buffer_count SPECIAL_VALUE(Cascaded_ring_buffer_count)
#define Catch_for_let_in_expression_context SPECIAL_VALUE(Catch_for_let_in_expression_context)
#define Category_evaluator_interface_count SPECIAL_VALUE(Category_evaluator_interface_count)
#define Category_for_category_symbol_count SPECIAL_VALUE(Category_for_category_symbol_count)
#define Category_for_token_count SPECIAL_VALUE(Category_for_token_count)
#define Category_instance_menu_workspace_class_description SPECIAL_VALUE(Category_instance_menu_workspace_class_description)
#define Category_menu_button_spot_count SPECIAL_VALUE(Category_menu_button_spot_count)
#define Category_menu_class_description SPECIAL_VALUE(Category_menu_class_description)
#define Category_set_count SPECIAL_VALUE(Category_set_count)
#define Category_symbols_for_non_contributing_categories SPECIAL_VALUE(Category_symbols_for_non_contributing_categories)
#define Category_visit_vector_qm SPECIAL_VALUE(Category_visit_vector_qm)
#define Cell SPECIAL_VALUE(Cell)
#define Cell_contents SPECIAL_VALUE(Cell_contents)
#define Cell_index_currently_being_registered SPECIAL_VALUE(Cell_index_currently_being_registered)
#define Chain_of_available_access_errors SPECIAL_VALUE(Chain_of_available_access_errors)
#define Chain_of_available_annotations SPECIAL_VALUE(Chain_of_available_annotations)
#define Chain_of_available_asian_double_bytes SPECIAL_VALUE(Chain_of_available_asian_double_bytes)
#define Chain_of_available_attribute_display_spots SPECIAL_VALUE(Chain_of_available_attribute_display_spots)
#define Chain_of_available_attribute_mimics SPECIAL_VALUE(Chain_of_available_attribute_mimics)
#define Chain_of_available_attribute_name_represented_by_table_spots SPECIAL_VALUE(Chain_of_available_attribute_name_represented_by_table_spots)
#define Chain_of_available_attribute_represented_by_table_spots SPECIAL_VALUE(Chain_of_available_attribute_represented_by_table_spots)
#define Chain_of_available_attribute_table_spots SPECIAL_VALUE(Chain_of_available_attribute_table_spots)
#define Chain_of_available_attribute_value_represented_by_table_spots SPECIAL_VALUE(Chain_of_available_attribute_value_represented_by_table_spots)
#define Chain_of_available_axis_panes SPECIAL_VALUE(Chain_of_available_axis_panes)
#define Chain_of_available_background_print_workspace_process_state_blocks SPECIAL_VALUE(Chain_of_available_background_print_workspace_process_state_blocks)
#define Chain_of_available_backward_chaining_displays SPECIAL_VALUE(Chain_of_available_backward_chaining_displays)
#define Chain_of_available_basic_profiling_structures SPECIAL_VALUE(Chain_of_available_basic_profiling_structures)
#define Chain_of_available_binary_tree_elements SPECIAL_VALUE(Chain_of_available_binary_tree_elements)
#define Chain_of_available_bitmap_arrays SPECIAL_VALUE(Chain_of_available_bitmap_arrays)
#define Chain_of_available_block_changes SPECIAL_VALUE(Chain_of_available_block_changes)
#define Chain_of_available_block_near_mouse_caches SPECIAL_VALUE(Chain_of_available_block_near_mouse_caches)
#define Chain_of_available_blocking_sockets SPECIAL_VALUE(Chain_of_available_blocking_sockets)
#define Chain_of_available_bounding_box_spots SPECIAL_VALUE(Chain_of_available_bounding_box_spots)
#define Chain_of_available_bounding_box_states SPECIAL_VALUE(Chain_of_available_bounding_box_states)
#define Chain_of_available_bounding_states SPECIAL_VALUE(Chain_of_available_bounding_states)
#define Chain_of_available_button_down_states SPECIAL_VALUE(Chain_of_available_button_down_states)
#define Chain_of_available_button_menu_spots SPECIAL_VALUE(Chain_of_available_button_menu_spots)
#define Chain_of_available_button_spots SPECIAL_VALUE(Chain_of_available_button_spots)
#define Chain_of_available_byte_code_bodys SPECIAL_VALUE(Chain_of_available_byte_code_bodys)
#define Chain_of_available_byte_code_streams SPECIAL_VALUE(Chain_of_available_byte_code_streams)
#define Chain_of_available_cached_explanation_from_data_server_or_initial_values SPECIAL_VALUE(Chain_of_available_cached_explanation_from_data_server_or_initial_values)
#define Chain_of_available_cached_explanation_from_frames SPECIAL_VALUE(Chain_of_available_cached_explanation_from_frames)
#define Chain_of_available_cached_explanation_from_generic_formulas SPECIAL_VALUE(Chain_of_available_cached_explanation_from_generic_formulas)
#define Chain_of_available_cached_explanation_from_rules SPECIAL_VALUE(Chain_of_available_cached_explanation_from_rules)
#define Chain_of_available_cached_explanation_from_specific_formulas SPECIAL_VALUE(Chain_of_available_cached_explanation_from_specific_formulas)
#define Chain_of_available_calendar_cvs SPECIAL_VALUE(Chain_of_available_calendar_cvs)
#define Chain_of_available_cascaded_ring_buffers SPECIAL_VALUE(Chain_of_available_cascaded_ring_buffers)
#define Chain_of_available_category_evaluator_interfaces SPECIAL_VALUE(Chain_of_available_category_evaluator_interfaces)
#define Chain_of_available_category_for_category_symbols SPECIAL_VALUE(Chain_of_available_category_for_category_symbols)
#define Chain_of_available_category_for_tokens SPECIAL_VALUE(Chain_of_available_category_for_tokens)
#define Chain_of_available_category_menu_button_spots SPECIAL_VALUE(Chain_of_available_category_menu_button_spots)
#define Chain_of_available_category_sets SPECIAL_VALUE(Chain_of_available_category_sets)
#define Chain_of_available_character_descriptions SPECIAL_VALUE(Chain_of_available_character_descriptions)
#define Chain_of_available_character_images SPECIAL_VALUE(Chain_of_available_character_images)
#define Chain_of_available_character_sequence_token_menu_button_spots SPECIAL_VALUE(Chain_of_available_character_sequence_token_menu_button_spots)
#define Chain_of_available_chart_spots SPECIAL_VALUE(Chain_of_available_chart_spots)
#define Chain_of_available_chart_views SPECIAL_VALUE(Chain_of_available_chart_views)
#define Chain_of_available_check_box_cvs SPECIAL_VALUE(Chain_of_available_check_box_cvs)
#define Chain_of_available_checkable_list_box_cvs SPECIAL_VALUE(Chain_of_available_checkable_list_box_cvs)
#define Chain_of_available_class_descriptions SPECIAL_VALUE(Chain_of_available_class_descriptions)
#define Chain_of_available_class_file_streams SPECIAL_VALUE(Chain_of_available_class_file_streams)
#define Chain_of_available_class_instances_memory_infos SPECIAL_VALUE(Chain_of_available_class_instances_memory_infos)
#define Chain_of_available_class_subscriptions SPECIAL_VALUE(Chain_of_available_class_subscriptions)
#define Chain_of_available_class_subscriptionss SPECIAL_VALUE(Chain_of_available_class_subscriptionss)
#define Chain_of_available_close_box_spots SPECIAL_VALUE(Chain_of_available_close_box_spots)
#define Chain_of_available_code_body_continuations SPECIAL_VALUE(Chain_of_available_code_body_continuations)
#define Chain_of_available_code_body_invocations SPECIAL_VALUE(Chain_of_available_code_body_invocations)
#define Chain_of_available_color_maps SPECIAL_VALUE(Chain_of_available_color_maps)
#define Chain_of_available_compiled_resources SPECIAL_VALUE(Chain_of_available_compiled_resources)
#define Chain_of_available_compiler_code_body_entrys SPECIAL_VALUE(Chain_of_available_compiler_code_body_entrys)
#define Chain_of_available_component_change_reports SPECIAL_VALUE(Chain_of_available_component_change_reports)
#define Chain_of_available_compound_fixnum_simulation_times SPECIAL_VALUE(Chain_of_available_compound_fixnum_simulation_times)
#define Chain_of_available_compound_slot_descriptors SPECIAL_VALUE(Chain_of_available_compound_slot_descriptors)
#define Chain_of_available_compound_type_descriptors SPECIAL_VALUE(Chain_of_available_compound_type_descriptors)
#define Chain_of_available_computation_instances SPECIAL_VALUE(Chain_of_available_computation_instances)
#define Chain_of_available_connection_items SPECIAL_VALUE(Chain_of_available_connection_items)
#define Chain_of_available_connection_spots SPECIAL_VALUE(Chain_of_available_connection_spots)
#define Chain_of_available_connection_subrectangle_structures SPECIAL_VALUE(Chain_of_available_connection_subrectangle_structures)
#define Chain_of_available_connections SPECIAL_VALUE(Chain_of_available_connections)
#define Chain_of_available_credits_table_spots SPECIAL_VALUE(Chain_of_available_credits_table_spots)
#define Chain_of_available_data_servers SPECIAL_VALUE(Chain_of_available_data_servers)
#define Chain_of_available_date_formats SPECIAL_VALUE(Chain_of_available_date_formats)
#define Chain_of_available_deferred_updates SPECIAL_VALUE(Chain_of_available_deferred_updates)
#define Chain_of_available_detail_pane_spots SPECIAL_VALUE(Chain_of_available_detail_pane_spots)
#define Chain_of_available_dial_spots SPECIAL_VALUE(Chain_of_available_dial_spots)
#define Chain_of_available_dialog_components SPECIAL_VALUE(Chain_of_available_dialog_components)
#define Chain_of_available_dialog_errors_structures SPECIAL_VALUE(Chain_of_available_dialog_errors_structures)
#define Chain_of_available_dialog_states SPECIAL_VALUE(Chain_of_available_dialog_states)
#define Chain_of_available_dialog_views SPECIAL_VALUE(Chain_of_available_dialog_views)
#define Chain_of_available_display_panes SPECIAL_VALUE(Chain_of_available_display_panes)
#define Chain_of_available_drag_handle_states SPECIAL_VALUE(Chain_of_available_drag_handle_states)
#define Chain_of_available_dragging_states SPECIAL_VALUE(Chain_of_available_dragging_states)
#define Chain_of_available_drawing_tasks SPECIAL_VALUE(Chain_of_available_drawing_tasks)
#define Chain_of_available_duration_cvs SPECIAL_VALUE(Chain_of_available_duration_cvs)
#define Chain_of_available_dynamic_dialogs SPECIAL_VALUE(Chain_of_available_dynamic_dialogs)
#define Chain_of_available_dynamic_workspace_associated_structures SPECIAL_VALUE(Chain_of_available_dynamic_workspace_associated_structures)
#define Chain_of_available_edit_box_changes SPECIAL_VALUE(Chain_of_available_edit_box_changes)
#define Chain_of_available_edit_box_spots SPECIAL_VALUE(Chain_of_available_edit_box_spots)
#define Chain_of_available_edit_caches SPECIAL_VALUE(Chain_of_available_edit_caches)
#define Chain_of_available_edit_menu_states SPECIAL_VALUE(Chain_of_available_edit_menu_states)
#define Chain_of_available_edit_states SPECIAL_VALUE(Chain_of_available_edit_states)
#define Chain_of_available_element_of_foreign_linking_infos SPECIAL_VALUE(Chain_of_available_element_of_foreign_linking_infos)
#define Chain_of_available_elevator_of_scroll_bar_spots SPECIAL_VALUE(Chain_of_available_elevator_of_scroll_bar_spots)
#define Chain_of_available_elevator_shaft_spots SPECIAL_VALUE(Chain_of_available_elevator_shaft_spots)
#define Chain_of_available_elevator_states SPECIAL_VALUE(Chain_of_available_elevator_states)
#define Chain_of_available_entire_focus_menu_spots SPECIAL_VALUE(Chain_of_available_entire_focus_menu_spots)
#define Chain_of_available_entire_g2_window_spots SPECIAL_VALUE(Chain_of_available_entire_g2_window_spots)
#define Chain_of_available_entire_menu_spots SPECIAL_VALUE(Chain_of_available_entire_menu_spots)
#define Chain_of_available_eq_hash_tables SPECIAL_VALUE(Chain_of_available_eq_hash_tables)
#define Chain_of_available_error_codes SPECIAL_VALUE(Chain_of_available_error_codes)
#define Chain_of_available_evaluator_slot_infos SPECIAL_VALUE(Chain_of_available_evaluator_slot_infos)
#define Chain_of_available_event_detectors SPECIAL_VALUE(Chain_of_available_event_detectors)
#define Chain_of_available_expression_for_compilations SPECIAL_VALUE(Chain_of_available_expression_for_compilations)
#define Chain_of_available_external_class_infos SPECIAL_VALUE(Chain_of_available_external_class_infos)
#define Chain_of_available_external_method_infos SPECIAL_VALUE(Chain_of_available_external_method_infos)
#define Chain_of_available_external_set_pointerss SPECIAL_VALUE(Chain_of_available_external_set_pointerss)
#define Chain_of_available_external_simulation_objects SPECIAL_VALUE(Chain_of_available_external_simulation_objects)
#define Chain_of_available_extremum_caches SPECIAL_VALUE(Chain_of_available_extremum_caches)
#define Chain_of_available_filename_parser_informations SPECIAL_VALUE(Chain_of_available_filename_parser_informations)
#define Chain_of_available_for_structures SPECIAL_VALUE(Chain_of_available_for_structures)
#define Chain_of_available_foreign_function_call_infos SPECIAL_VALUE(Chain_of_available_foreign_function_call_infos)
#define Chain_of_available_foreign_function_entrys SPECIAL_VALUE(Chain_of_available_foreign_function_entrys)
#define Chain_of_available_foreign_function_image_infos SPECIAL_VALUE(Chain_of_available_foreign_function_image_infos)
#define Chain_of_available_foreign_struct_infos SPECIAL_VALUE(Chain_of_available_foreign_struct_infos)
#define Chain_of_available_formula_invocations SPECIAL_VALUE(Chain_of_available_formula_invocations)
#define Chain_of_available_frame_component_spots SPECIAL_VALUE(Chain_of_available_frame_component_spots)
#define Chain_of_available_frame_description_references SPECIAL_VALUE(Chain_of_available_frame_description_references)
#define Chain_of_available_frame_displays SPECIAL_VALUE(Chain_of_available_frame_displays)
#define Chain_of_available_frame_transforms SPECIAL_VALUE(Chain_of_available_frame_transforms)
#define Chain_of_available_fsm_states SPECIAL_VALUE(Chain_of_available_fsm_states)
#define Chain_of_available_function_infos SPECIAL_VALUE(Chain_of_available_function_infos)
#define Chain_of_available_function_invocations SPECIAL_VALUE(Chain_of_available_function_invocations)
#define Chain_of_available_future_task_queue_holders SPECIAL_VALUE(Chain_of_available_future_task_queue_holders)
#define Chain_of_available_g2_list_elements SPECIAL_VALUE(Chain_of_available_g2_list_elements)
#define Chain_of_available_g2_login_states SPECIAL_VALUE(Chain_of_available_g2_login_states)
#define Chain_of_available_g2_stream_structures SPECIAL_VALUE(Chain_of_available_g2_stream_structures)
#define Chain_of_available_g2_tokens SPECIAL_VALUE(Chain_of_available_g2_tokens)
#define Chain_of_available_g2ds_interfaces SPECIAL_VALUE(Chain_of_available_g2ds_interfaces)
#define Chain_of_available_g2ds_server_connections SPECIAL_VALUE(Chain_of_available_g2ds_server_connections)
#define Chain_of_available_g2ds_variables SPECIAL_VALUE(Chain_of_available_g2ds_variables)
#define Chain_of_available_g2gl_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_activity_compilations)
#define Chain_of_available_g2gl_activity_optionss SPECIAL_VALUE(Chain_of_available_g2gl_activity_optionss)
#define Chain_of_available_g2gl_alarm_event_handler_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_alarm_event_handler_activity_compilations)
#define Chain_of_available_g2gl_assign_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_assign_activity_compilations)
#define Chain_of_available_g2gl_attribute_display_compilations SPECIAL_VALUE(Chain_of_available_g2gl_attribute_display_compilations)
#define Chain_of_available_g2gl_body_compilations SPECIAL_VALUE(Chain_of_available_g2gl_body_compilations)
#define Chain_of_available_g2gl_break_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_break_activity_compilations)
#define Chain_of_available_g2gl_call_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_call_activity_compilations)
#define Chain_of_available_g2gl_call_invocations SPECIAL_VALUE(Chain_of_available_g2gl_call_invocations)
#define Chain_of_available_g2gl_compensate_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_compensate_activity_compilations)
#define Chain_of_available_g2gl_compensation_handler_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_compensation_handler_activity_compilations)
#define Chain_of_available_g2gl_compilation_versions SPECIAL_VALUE(Chain_of_available_g2gl_compilation_versions)
#define Chain_of_available_g2gl_do_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_do_activity_compilations)
#define Chain_of_available_g2gl_empty_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_empty_activity_compilations)
#define Chain_of_available_g2gl_execution_faults SPECIAL_VALUE(Chain_of_available_g2gl_execution_faults)
#define Chain_of_available_g2gl_execution_frames SPECIAL_VALUE(Chain_of_available_g2gl_execution_frames)
#define Chain_of_available_g2gl_execution_threads SPECIAL_VALUE(Chain_of_available_g2gl_execution_threads)
#define Chain_of_available_g2gl_exit_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_exit_activity_compilations)
#define Chain_of_available_g2gl_fault_handler_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_fault_handler_activity_compilations)
#define Chain_of_available_g2gl_flow_discriminator_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_flow_discriminator_activity_compilations)
#define Chain_of_available_g2gl_flow_gate_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_flow_gate_activity_compilations)
#define Chain_of_available_g2gl_flow_signal_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_flow_signal_activity_compilations)
#define Chain_of_available_g2gl_flow_split_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_flow_split_activity_compilations)
#define Chain_of_available_g2gl_flow_sync_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_flow_sync_activity_compilations)
#define Chain_of_available_g2gl_flow_terminator_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_flow_terminator_activity_compilations)
#define Chain_of_available_g2gl_invoke_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_invoke_activity_compilations)
#define Chain_of_available_g2gl_message_event_handler_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_message_event_handler_activity_compilations)
#define Chain_of_available_g2gl_message_transmissions SPECIAL_VALUE(Chain_of_available_g2gl_message_transmissions)
#define Chain_of_available_g2gl_n_out_of_m_flow_join_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_n_out_of_m_flow_join_activity_compilations)
#define Chain_of_available_g2gl_pick_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_pick_activity_compilations)
#define Chain_of_available_g2gl_pick_join_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_pick_join_activity_compilations)
#define Chain_of_available_g2gl_process_invocation_threads SPECIAL_VALUE(Chain_of_available_g2gl_process_invocation_threads)
#define Chain_of_available_g2gl_receive_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_receive_activity_compilations)
#define Chain_of_available_g2gl_reply_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_reply_activity_compilations)
#define Chain_of_available_g2gl_return_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_return_activity_compilations)
#define Chain_of_available_g2gl_scope_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_scope_activity_compilations)
#define Chain_of_available_g2gl_service_ports SPECIAL_VALUE(Chain_of_available_g2gl_service_ports)
#define Chain_of_available_g2gl_switch_fork_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_switch_fork_activity_compilations)
#define Chain_of_available_g2gl_switch_join_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_switch_join_activity_compilations)
#define Chain_of_available_g2gl_text_box_compilations SPECIAL_VALUE(Chain_of_available_g2gl_text_box_compilations)
#define Chain_of_available_g2gl_throw_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_throw_activity_compilations)
#define Chain_of_available_g2gl_wait_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_wait_activity_compilations)
#define Chain_of_available_g2gl_while_activity_compilations SPECIAL_VALUE(Chain_of_available_g2gl_while_activity_compilations)
#define Chain_of_available_gb_2312s SPECIAL_VALUE(Chain_of_available_gb_2312s)
#define Chain_of_available_gensym_grammars SPECIAL_VALUE(Chain_of_available_gensym_grammars)
#define Chain_of_available_gensym_pathnames SPECIAL_VALUE(Chain_of_available_gensym_pathnames)
#define Chain_of_available_gensym_string_streams SPECIAL_VALUE(Chain_of_available_gensym_string_streams)
#define Chain_of_available_gensym_string_text_sequences SPECIAL_VALUE(Chain_of_available_gensym_string_text_sequences)
#define Chain_of_available_gensym_windows SPECIAL_VALUE(Chain_of_available_gensym_windows)
#define Chain_of_available_geometrys SPECIAL_VALUE(Chain_of_available_geometrys)
#define Chain_of_available_gesture_functions SPECIAL_VALUE(Chain_of_available_gesture_functions)
#define Chain_of_available_gesture_locals SPECIAL_VALUE(Chain_of_available_gesture_locals)
#define Chain_of_available_gesture_threads SPECIAL_VALUE(Chain_of_available_gesture_threads)
#define Chain_of_available_gfi_queue_items SPECIAL_VALUE(Chain_of_available_gfi_queue_items)
#define Chain_of_available_global_profiling_structures SPECIAL_VALUE(Chain_of_available_global_profiling_structures)
#define Chain_of_available_goto_tag_entrys SPECIAL_VALUE(Chain_of_available_goto_tag_entrys)
#define Chain_of_available_graph_displays SPECIAL_VALUE(Chain_of_available_graph_displays)
#define Chain_of_available_graph_nodes SPECIAL_VALUE(Chain_of_available_graph_nodes)
#define Chain_of_available_graph_renderings SPECIAL_VALUE(Chain_of_available_graph_renderings)
#define Chain_of_available_graph_table_spots SPECIAL_VALUE(Chain_of_available_graph_table_spots)
#define Chain_of_available_graphic_character_sets SPECIAL_VALUE(Chain_of_available_graphic_character_sets)
#define Chain_of_available_grid_panes SPECIAL_VALUE(Chain_of_available_grid_panes)
#define Chain_of_available_grid_view_cells SPECIAL_VALUE(Chain_of_available_grid_view_cells)
#define Chain_of_available_group_index_structures SPECIAL_VALUE(Chain_of_available_group_index_structures)
#define Chain_of_available_gsi_array_wrappers SPECIAL_VALUE(Chain_of_available_gsi_array_wrappers)
#define Chain_of_available_gsi_attributes SPECIAL_VALUE(Chain_of_available_gsi_attributes)
#define Chain_of_available_gsi_extension_datas SPECIAL_VALUE(Chain_of_available_gsi_extension_datas)
#define Chain_of_available_gsi_historys SPECIAL_VALUE(Chain_of_available_gsi_historys)
#define Chain_of_available_gsi_icp_interfaces SPECIAL_VALUE(Chain_of_available_gsi_icp_interfaces)
#define Chain_of_available_gsi_instance_extensions SPECIAL_VALUE(Chain_of_available_gsi_instance_extensions)
#define Chain_of_available_gsi_instances SPECIAL_VALUE(Chain_of_available_gsi_instances)
#define Chain_of_available_gsi_local_functions SPECIAL_VALUE(Chain_of_available_gsi_local_functions)
#define Chain_of_available_gsi_remote_procedures SPECIAL_VALUE(Chain_of_available_gsi_remote_procedures)
#define Chain_of_available_gsi_transfer_wrappers SPECIAL_VALUE(Chain_of_available_gsi_transfer_wrappers)
#define Chain_of_available_halt_infos SPECIAL_VALUE(Chain_of_available_halt_infos)
#define Chain_of_available_hfep_hanc_types SPECIAL_VALUE(Chain_of_available_hfep_hanc_types)
#define Chain_of_available_history_ring_buffers SPECIAL_VALUE(Chain_of_available_history_ring_buffers)
#define Chain_of_available_hot_spot_states SPECIAL_VALUE(Chain_of_available_hot_spot_states)
#define Chain_of_available_html_views SPECIAL_VALUE(Chain_of_available_html_views)
#define Chain_of_available_i_am_alive_infos SPECIAL_VALUE(Chain_of_available_i_am_alive_infos)
#define Chain_of_available_icmp_sockets SPECIAL_VALUE(Chain_of_available_icmp_sockets)
#define Chain_of_available_icon_descriptions SPECIAL_VALUE(Chain_of_available_icon_descriptions)
#define Chain_of_available_icon_editor_buttons SPECIAL_VALUE(Chain_of_available_icon_editor_buttons)
#define Chain_of_available_icon_editor_engines SPECIAL_VALUE(Chain_of_available_icon_editor_engines)
#define Chain_of_available_icon_editor_layers_pads SPECIAL_VALUE(Chain_of_available_icon_editor_layers_pads)
#define Chain_of_available_icon_editor_tables SPECIAL_VALUE(Chain_of_available_icon_editor_tables)
#define Chain_of_available_icon_editor_translators SPECIAL_VALUE(Chain_of_available_icon_editor_translators)
#define Chain_of_available_icon_editor_view_pads SPECIAL_VALUE(Chain_of_available_icon_editor_view_pads)
#define Chain_of_available_icon_editors SPECIAL_VALUE(Chain_of_available_icon_editors)
#define Chain_of_available_icon_renderings SPECIAL_VALUE(Chain_of_available_icon_renderings)
#define Chain_of_available_icon_slot_groups SPECIAL_VALUE(Chain_of_available_icon_slot_groups)
#define Chain_of_available_icp_buffers SPECIAL_VALUE(Chain_of_available_icp_buffers)
#define Chain_of_available_icp_ports SPECIAL_VALUE(Chain_of_available_icp_ports)
#define Chain_of_available_icp_read_tasks SPECIAL_VALUE(Chain_of_available_icp_read_tasks)
#define Chain_of_available_icp_sockets SPECIAL_VALUE(Chain_of_available_icp_sockets)
#define Chain_of_available_icp_write_tasks SPECIAL_VALUE(Chain_of_available_icp_write_tasks)
#define Chain_of_available_identified_drawing_activitys SPECIAL_VALUE(Chain_of_available_identified_drawing_activitys)
#define Chain_of_available_image_cvs SPECIAL_VALUE(Chain_of_available_image_cvs)
#define Chain_of_available_image_datas SPECIAL_VALUE(Chain_of_available_image_datas)
#define Chain_of_available_image_plane_spots SPECIAL_VALUE(Chain_of_available_image_plane_spots)
#define Chain_of_available_image_planes SPECIAL_VALUE(Chain_of_available_image_planes)
#define Chain_of_available_image_renderings SPECIAL_VALUE(Chain_of_available_image_renderings)
#define Chain_of_available_image_tiles SPECIAL_VALUE(Chain_of_available_image_tiles)
#define Chain_of_available_incomplete_painting_actions SPECIAL_VALUE(Chain_of_available_incomplete_painting_actions)
#define Chain_of_available_incomplete_phrases SPECIAL_VALUE(Chain_of_available_incomplete_phrases)
#define Chain_of_available_index_spaces SPECIAL_VALUE(Chain_of_available_index_spaces)
#define Chain_of_available_inference_background_collections SPECIAL_VALUE(Chain_of_available_inference_background_collections)
#define Chain_of_available_inform_message_informations SPECIAL_VALUE(Chain_of_available_inform_message_informations)
#define Chain_of_available_inlining_data_holders SPECIAL_VALUE(Chain_of_available_inlining_data_holders)
#define Chain_of_available_input_table_spots SPECIAL_VALUE(Chain_of_available_input_table_spots)
#define Chain_of_available_inspect_command_spots SPECIAL_VALUE(Chain_of_available_inspect_command_spots)
#define Chain_of_available_integer_cvs SPECIAL_VALUE(Chain_of_available_integer_cvs)
#define Chain_of_available_inter_g2_data_request_queues SPECIAL_VALUE(Chain_of_available_inter_g2_data_request_queues)
#define Chain_of_available_internal_tokens SPECIAL_VALUE(Chain_of_available_internal_tokens)
#define Chain_of_available_interned_lists SPECIAL_VALUE(Chain_of_available_interned_lists)
#define Chain_of_available_interned_remote_procedure_item_passing_infos SPECIAL_VALUE(Chain_of_available_interned_remote_procedure_item_passing_infos)
#define Chain_of_available_invalid_spots SPECIAL_VALUE(Chain_of_available_invalid_spots)
#define Chain_of_available_iso_2022_transcoders SPECIAL_VALUE(Chain_of_available_iso_2022_transcoders)
#define Chain_of_available_iso_646s SPECIAL_VALUE(Chain_of_available_iso_646s)
#define Chain_of_available_iso_8859_10s SPECIAL_VALUE(Chain_of_available_iso_8859_10s)
#define Chain_of_available_iso_8859_1s SPECIAL_VALUE(Chain_of_available_iso_8859_1s)
#define Chain_of_available_iso_8859_2s SPECIAL_VALUE(Chain_of_available_iso_8859_2s)
#define Chain_of_available_iso_8859_3s SPECIAL_VALUE(Chain_of_available_iso_8859_3s)
#define Chain_of_available_iso_8859_4s SPECIAL_VALUE(Chain_of_available_iso_8859_4s)
#define Chain_of_available_iso_8859_5s SPECIAL_VALUE(Chain_of_available_iso_8859_5s)
#define Chain_of_available_iso_8859_6s SPECIAL_VALUE(Chain_of_available_iso_8859_6s)
#define Chain_of_available_iso_8859_7s SPECIAL_VALUE(Chain_of_available_iso_8859_7s)
#define Chain_of_available_iso_8859_8s SPECIAL_VALUE(Chain_of_available_iso_8859_8s)
#define Chain_of_available_iso_8859_9s SPECIAL_VALUE(Chain_of_available_iso_8859_9s)
#define Chain_of_available_iso_8859_abstracts SPECIAL_VALUE(Chain_of_available_iso_8859_abstracts)
#define Chain_of_available_iso_8859_transcoders SPECIAL_VALUE(Chain_of_available_iso_8859_transcoders)
#define Chain_of_available_item_access_caches SPECIAL_VALUE(Chain_of_available_item_access_caches)
#define Chain_of_available_item_represented_by_table_spots SPECIAL_VALUE(Chain_of_available_item_represented_by_table_spots)
#define Chain_of_available_java_classs SPECIAL_VALUE(Chain_of_available_java_classs)
#define Chain_of_available_java_code_exceptions SPECIAL_VALUE(Chain_of_available_java_code_exceptions)
#define Chain_of_available_java_codes SPECIAL_VALUE(Chain_of_available_java_codes)
#define Chain_of_available_java_descriptors SPECIAL_VALUE(Chain_of_available_java_descriptors)
#define Chain_of_available_java_fields SPECIAL_VALUE(Chain_of_available_java_fields)
#define Chain_of_available_java_methods SPECIAL_VALUE(Chain_of_available_java_methods)
#define Chain_of_available_java_symbols SPECIAL_VALUE(Chain_of_available_java_symbols)
#define Chain_of_available_javalink_versioned_call_datas SPECIAL_VALUE(Chain_of_available_javalink_versioned_call_datas)
#define Chain_of_available_jis_x_0208s SPECIAL_VALUE(Chain_of_available_jis_x_0208s)
#define Chain_of_available_kb_saves SPECIAL_VALUE(Chain_of_available_kb_saves)
#define Chain_of_available_kb_transfers SPECIAL_VALUE(Chain_of_available_kb_transfers)
#define Chain_of_available_kb_workspace_image_plane_spots SPECIAL_VALUE(Chain_of_available_kb_workspace_image_plane_spots)
#define Chain_of_available_kfep_batchs SPECIAL_VALUE(Chain_of_available_kfep_batchs)
#define Chain_of_available_kfep_conversion_choice_menu_button_spots SPECIAL_VALUE(Chain_of_available_kfep_conversion_choice_menu_button_spots)
#define Chain_of_available_kfep_masters SPECIAL_VALUE(Chain_of_available_kfep_masters)
#define Chain_of_available_ks_c_5601s SPECIAL_VALUE(Chain_of_available_ks_c_5601s)
#define Chain_of_available_label_box_spots SPECIAL_VALUE(Chain_of_available_label_box_spots)
#define Chain_of_available_large_scaled_font_buckets SPECIAL_VALUE(Chain_of_available_large_scaled_font_buckets)
#define Chain_of_available_layer_boxs SPECIAL_VALUE(Chain_of_available_layer_boxs)
#define Chain_of_available_legend_panes SPECIAL_VALUE(Chain_of_available_legend_panes)
#define Chain_of_available_lexing_tables SPECIAL_VALUE(Chain_of_available_lexing_tables)
#define Chain_of_available_line_drawing_for_printings SPECIAL_VALUE(Chain_of_available_line_drawing_for_printings)
#define Chain_of_available_lisp_grid_views SPECIAL_VALUE(Chain_of_available_lisp_grid_views)
#define Chain_of_available_list_box_cvs SPECIAL_VALUE(Chain_of_available_list_box_cvs)
#define Chain_of_available_local_events SPECIAL_VALUE(Chain_of_available_local_events)
#define Chain_of_available_local_nupec_variables SPECIAL_VALUE(Chain_of_available_local_nupec_variables)
#define Chain_of_available_logbook_views SPECIAL_VALUE(Chain_of_available_logbook_views)
#define Chain_of_available_loose_end_spots SPECIAL_VALUE(Chain_of_available_loose_end_spots)
#define Chain_of_available_lru_elements SPECIAL_VALUE(Chain_of_available_lru_elements)
#define Chain_of_available_media_streams SPECIAL_VALUE(Chain_of_available_media_streams)
#define Chain_of_available_memory_limit_infos SPECIAL_VALUE(Chain_of_available_memory_limit_infos)
#define Chain_of_available_menu_button_spots SPECIAL_VALUE(Chain_of_available_menu_button_spots)
#define Chain_of_available_menu_choose_states SPECIAL_VALUE(Chain_of_available_menu_choose_states)
#define Chain_of_available_menu_item_spots SPECIAL_VALUE(Chain_of_available_menu_item_spots)
#define Chain_of_available_menu_pane_spots SPECIAL_VALUE(Chain_of_available_menu_pane_spots)
#define Chain_of_available_menu_title_spots SPECIAL_VALUE(Chain_of_available_menu_title_spots)
#define Chain_of_available_meter_or_dial_spots SPECIAL_VALUE(Chain_of_available_meter_or_dial_spots)
#define Chain_of_available_meter_spots SPECIAL_VALUE(Chain_of_available_meter_spots)
#define Chain_of_available_minimal_character_descriptions SPECIAL_VALUE(Chain_of_available_minimal_character_descriptions)
#define Chain_of_available_modal_menu_states SPECIAL_VALUE(Chain_of_available_modal_menu_states)
#define Chain_of_available_model_queues SPECIAL_VALUE(Chain_of_available_model_queues)
#define Chain_of_available_model_runtime_infos SPECIAL_VALUE(Chain_of_available_model_runtime_infos)
#define Chain_of_available_modify_control_action_types SPECIAL_VALUE(Chain_of_available_modify_control_action_types)
#define Chain_of_available_modify_control_structures SPECIAL_VALUE(Chain_of_available_modify_control_structures)
#define Chain_of_available_modify_dialog_structures SPECIAL_VALUE(Chain_of_available_modify_dialog_structures)
#define Chain_of_available_mouse_drag_detector_states SPECIAL_VALUE(Chain_of_available_mouse_drag_detector_states)
#define Chain_of_available_mouse_pointers SPECIAL_VALUE(Chain_of_available_mouse_pointers)
#define Chain_of_available_mouse_watch_states SPECIAL_VALUE(Chain_of_available_mouse_watch_states)
#define Chain_of_available_move_dragging_states SPECIAL_VALUE(Chain_of_available_move_dragging_states)
#define Chain_of_available_multiframe_table_spots SPECIAL_VALUE(Chain_of_available_multiframe_table_spots)
#define Chain_of_available_multiply_wild_regular_expression_nodes SPECIAL_VALUE(Chain_of_available_multiply_wild_regular_expression_nodes)
#define Chain_of_available_name_box_spots SPECIAL_VALUE(Chain_of_available_name_box_spots)
#define Chain_of_available_named_gensym_structures SPECIAL_VALUE(Chain_of_available_named_gensym_structures)
#define Chain_of_available_native_dialogs SPECIAL_VALUE(Chain_of_available_native_dialogs)
#define Chain_of_available_native_fonts SPECIAL_VALUE(Chain_of_available_native_fonts)
#define Chain_of_available_native_simple_dialog_states SPECIAL_VALUE(Chain_of_available_native_simple_dialog_states)
#define Chain_of_available_native_windows SPECIAL_VALUE(Chain_of_available_native_windows)
#define Chain_of_available_new_table_background_spots SPECIAL_VALUE(Chain_of_available_new_table_background_spots)
#define Chain_of_available_new_table_cell_spots SPECIAL_VALUE(Chain_of_available_new_table_cell_spots)
#define Chain_of_available_new_table_spots SPECIAL_VALUE(Chain_of_available_new_table_spots)
#define Chain_of_available_nms_menu_items SPECIAL_VALUE(Chain_of_available_nms_menu_items)
#define Chain_of_available_nms_menus SPECIAL_VALUE(Chain_of_available_nms_menus)
#define Chain_of_available_non_kb_workspace_image_plane_spots SPECIAL_VALUE(Chain_of_available_non_kb_workspace_image_plane_spots)
#define Chain_of_available_normal_completions SPECIAL_VALUE(Chain_of_available_normal_completions)
#define Chain_of_available_nupec_synchronize_variable_or_parameters SPECIAL_VALUE(Chain_of_available_nupec_synchronize_variable_or_parameters)
#define Chain_of_available_object_building_problems SPECIAL_VALUE(Chain_of_available_object_building_problems)
#define Chain_of_available_object_passing_infos SPECIAL_VALUE(Chain_of_available_object_passing_infos)
#define Chain_of_available_ok_file_tokens SPECIAL_VALUE(Chain_of_available_ok_file_tokens)
#define Chain_of_available_output_only_table_spots SPECIAL_VALUE(Chain_of_available_output_only_table_spots)
#define Chain_of_available_outside_window_spots SPECIAL_VALUE(Chain_of_available_outside_window_spots)
#define Chain_of_available_overview_pane_spots SPECIAL_VALUE(Chain_of_available_overview_pane_spots)
#define Chain_of_available_pane_background_spots SPECIAL_VALUE(Chain_of_available_pane_background_spots)
#define Chain_of_available_pane_border_spots SPECIAL_VALUE(Chain_of_available_pane_border_spots)
#define Chain_of_available_pane_component_spots SPECIAL_VALUE(Chain_of_available_pane_component_spots)
#define Chain_of_available_pane_spots SPECIAL_VALUE(Chain_of_available_pane_spots)
#define Chain_of_available_panes SPECIAL_VALUE(Chain_of_available_panes)
#define Chain_of_available_parse_objects SPECIAL_VALUE(Chain_of_available_parse_objects)
#define Chain_of_available_parse_tables SPECIAL_VALUE(Chain_of_available_parse_tables)
#define Chain_of_available_parsing_contexts SPECIAL_VALUE(Chain_of_available_parsing_contexts)
#define Chain_of_available_parsing_tokens SPECIAL_VALUE(Chain_of_available_parsing_tokens)
#define Chain_of_available_partial_commands SPECIAL_VALUE(Chain_of_available_partial_commands)
#define Chain_of_available_pathname_component_token_menu_button_spots SPECIAL_VALUE(Chain_of_available_pathname_component_token_menu_button_spots)
#define Chain_of_available_pending_activitys SPECIAL_VALUE(Chain_of_available_pending_activitys)
#define Chain_of_available_phrase_rule_completions SPECIAL_VALUE(Chain_of_available_phrase_rule_completions)
#define Chain_of_available_pixmaps SPECIAL_VALUE(Chain_of_available_pixmaps)
#define Chain_of_available_place_reference_internalss SPECIAL_VALUE(Chain_of_available_place_reference_internalss)
#define Chain_of_available_plot_data_ring_buffers SPECIAL_VALUE(Chain_of_available_plot_data_ring_buffers)
#define Chain_of_available_possible_phrases SPECIAL_VALUE(Chain_of_available_possible_phrases)
#define Chain_of_available_procedure_invocations SPECIAL_VALUE(Chain_of_available_procedure_invocations)
#define Chain_of_available_processs SPECIAL_VALUE(Chain_of_available_processs)
#define Chain_of_available_productions SPECIAL_VALUE(Chain_of_available_productions)
#define Chain_of_available_prop_grid_verbs SPECIAL_VALUE(Chain_of_available_prop_grid_verbs)
#define Chain_of_available_property_grid_nodes SPECIAL_VALUE(Chain_of_available_property_grid_nodes)
#define Chain_of_available_property_grids SPECIAL_VALUE(Chain_of_available_property_grids)
#define Chain_of_available_pseudo_attributes SPECIAL_VALUE(Chain_of_available_pseudo_attributes)
#define Chain_of_available_pseudo_frames SPECIAL_VALUE(Chain_of_available_pseudo_frames)
#define Chain_of_available_pseudo_instruction_streams SPECIAL_VALUE(Chain_of_available_pseudo_instruction_streams)
#define Chain_of_available_push_button_cvs SPECIAL_VALUE(Chain_of_available_push_button_cvs)
#define Chain_of_available_quantity_cvs SPECIAL_VALUE(Chain_of_available_quantity_cvs)
#define Chain_of_available_query_cell_streams SPECIAL_VALUE(Chain_of_available_query_cell_streams)
#define Chain_of_available_queue_elements SPECIAL_VALUE(Chain_of_available_queue_elements)
#define Chain_of_available_queues SPECIAL_VALUE(Chain_of_available_queues)
#define Chain_of_available_readout_table_spots SPECIAL_VALUE(Chain_of_available_readout_table_spots)
#define Chain_of_available_receiving_resumable_objects SPECIAL_VALUE(Chain_of_available_receiving_resumable_objects)
#define Chain_of_available_receiving_rpc_arglist_structures SPECIAL_VALUE(Chain_of_available_receiving_rpc_arglist_structures)
#define Chain_of_available_reference_structures SPECIAL_VALUE(Chain_of_available_reference_structures)
#define Chain_of_available_region_bounds_and_rasters SPECIAL_VALUE(Chain_of_available_region_bounds_and_rasters)
#define Chain_of_available_regular_expression_node_for_set_of_characterss SPECIAL_VALUE(Chain_of_available_regular_expression_node_for_set_of_characterss)
#define Chain_of_available_regular_expression_node_for_single_characters SPECIAL_VALUE(Chain_of_available_regular_expression_node_for_single_characters)
#define Chain_of_available_regular_expression_node_for_single_wild_characters SPECIAL_VALUE(Chain_of_available_regular_expression_node_for_single_wild_characters)
#define Chain_of_available_regular_expression_node_for_subexpressions SPECIAL_VALUE(Chain_of_available_regular_expression_node_for_subexpressions)
#define Chain_of_available_regular_expression_node_for_wild_characterss SPECIAL_VALUE(Chain_of_available_regular_expression_node_for_wild_characterss)
#define Chain_of_available_regular_expression_nodes SPECIAL_VALUE(Chain_of_available_regular_expression_nodes)
#define Chain_of_available_relation_instances SPECIAL_VALUE(Chain_of_available_relation_instances)
#define Chain_of_available_relative_time_panes SPECIAL_VALUE(Chain_of_available_relative_time_panes)
#define Chain_of_available_remote_procedure_calls SPECIAL_VALUE(Chain_of_available_remote_procedure_calls)
#define Chain_of_available_remote_procedure_identifiers SPECIAL_VALUE(Chain_of_available_remote_procedure_identifiers)
#define Chain_of_available_remote_procedure_item_passing_infos SPECIAL_VALUE(Chain_of_available_remote_procedure_item_passing_infos)
#define Chain_of_available_remote_procedure_names SPECIAL_VALUE(Chain_of_available_remote_procedure_names)
#define Chain_of_available_replacement_token_menu_button_spots SPECIAL_VALUE(Chain_of_available_replacement_token_menu_button_spots)
#define Chain_of_available_resize_box_spots SPECIAL_VALUE(Chain_of_available_resize_box_spots)
#define Chain_of_available_resumable_circular_nodes SPECIAL_VALUE(Chain_of_available_resumable_circular_nodes)
#define Chain_of_available_resumable_evaluation_sequence_node_mixins SPECIAL_VALUE(Chain_of_available_resumable_evaluation_sequence_node_mixins)
#define Chain_of_available_resumable_evaluation_sequence_nodes SPECIAL_VALUE(Chain_of_available_resumable_evaluation_sequence_nodes)
#define Chain_of_available_resumable_evaluation_structure_nodes SPECIAL_VALUE(Chain_of_available_resumable_evaluation_structure_nodes)
#define Chain_of_available_resumable_history_nodes SPECIAL_VALUE(Chain_of_available_resumable_history_nodes)
#define Chain_of_available_resumable_icp_node_mixins SPECIAL_VALUE(Chain_of_available_resumable_icp_node_mixins)
#define Chain_of_available_resumable_icp_object_mixins SPECIAL_VALUE(Chain_of_available_resumable_icp_object_mixins)
#define Chain_of_available_resumable_instance_node_mixins SPECIAL_VALUE(Chain_of_available_resumable_instance_node_mixins)
#define Chain_of_available_resumable_instance_or_complex_value_node_mixins SPECIAL_VALUE(Chain_of_available_resumable_instance_or_complex_value_node_mixins)
#define Chain_of_available_resumable_list_node_mixins SPECIAL_VALUE(Chain_of_available_resumable_list_node_mixins)
#define Chain_of_available_resumable_node_mixins SPECIAL_VALUE(Chain_of_available_resumable_node_mixins)
#define Chain_of_available_resumable_object_list_nodes SPECIAL_VALUE(Chain_of_available_resumable_object_list_nodes)
#define Chain_of_available_resumable_object_mixins SPECIAL_VALUE(Chain_of_available_resumable_object_mixins)
#define Chain_of_available_resumable_object_nodes SPECIAL_VALUE(Chain_of_available_resumable_object_nodes)
#define Chain_of_available_resumable_object_vector_nodes SPECIAL_VALUE(Chain_of_available_resumable_object_vector_nodes)
#define Chain_of_available_resumable_sequence_node_mixins SPECIAL_VALUE(Chain_of_available_resumable_sequence_node_mixins)
#define Chain_of_available_resumable_value_list_nodes SPECIAL_VALUE(Chain_of_available_resumable_value_list_nodes)
#define Chain_of_available_resumable_value_nodes SPECIAL_VALUE(Chain_of_available_resumable_value_nodes)
#define Chain_of_available_resumable_value_vector_nodes SPECIAL_VALUE(Chain_of_available_resumable_value_vector_nodes)
#define Chain_of_available_resumable_vector_node_mixins SPECIAL_VALUE(Chain_of_available_resumable_vector_node_mixins)
#define Chain_of_available_ring_buffer_states SPECIAL_VALUE(Chain_of_available_ring_buffer_states)
#define Chain_of_available_ring_raster_for_graphs SPECIAL_VALUE(Chain_of_available_ring_raster_for_graphs)
#define Chain_of_available_rule_instances SPECIAL_VALUE(Chain_of_available_rule_instances)
#define Chain_of_available_saving_contexts SPECIAL_VALUE(Chain_of_available_saving_contexts)
#define Chain_of_available_scaled_fonts SPECIAL_VALUE(Chain_of_available_scaled_fonts)
#define Chain_of_available_schedule_tasks SPECIAL_VALUE(Chain_of_available_schedule_tasks)
#define Chain_of_available_scheduled_remote_procedure_starts SPECIAL_VALUE(Chain_of_available_scheduled_remote_procedure_starts)
#define Chain_of_available_search_state_table_spots SPECIAL_VALUE(Chain_of_available_search_state_table_spots)
#define Chain_of_available_selection_handle_spots SPECIAL_VALUE(Chain_of_available_selection_handle_spots)
#define Chain_of_available_selection_rectangle_states SPECIAL_VALUE(Chain_of_available_selection_rectangle_states)
#define Chain_of_available_selections SPECIAL_VALUE(Chain_of_available_selections)
#define Chain_of_available_sending_resumable_objects SPECIAL_VALUE(Chain_of_available_sending_resumable_objects)
#define Chain_of_available_sensor_groups SPECIAL_VALUE(Chain_of_available_sensor_groups)
#define Chain_of_available_sensor_groups_headers SPECIAL_VALUE(Chain_of_available_sensor_groups_headers)
#define Chain_of_available_set_of_possible_phrasess SPECIAL_VALUE(Chain_of_available_set_of_possible_phrasess)
#define Chain_of_available_shift_jis_transcoders SPECIAL_VALUE(Chain_of_available_shift_jis_transcoders)
#define Chain_of_available_short_duration_cvs SPECIAL_VALUE(Chain_of_available_short_duration_cvs)
#define Chain_of_available_short_representation_table_spots SPECIAL_VALUE(Chain_of_available_short_representation_table_spots)
#define Chain_of_available_shortcut_bars SPECIAL_VALUE(Chain_of_available_shortcut_bars)
#define Chain_of_available_show_parameters_decoders SPECIAL_VALUE(Chain_of_available_show_parameters_decoders)
#define Chain_of_available_shredded_rasters SPECIAL_VALUE(Chain_of_available_shredded_rasters)
#define Chain_of_available_simple_item_spots SPECIAL_VALUE(Chain_of_available_simple_item_spots)
#define Chain_of_available_simulation_infos SPECIAL_VALUE(Chain_of_available_simulation_infos)
#define Chain_of_available_skip_list_elements SPECIAL_VALUE(Chain_of_available_skip_list_elements)
#define Chain_of_available_slider_spots SPECIAL_VALUE(Chain_of_available_slider_spots)
#define Chain_of_available_slot_component_descriptors SPECIAL_VALUE(Chain_of_available_slot_component_descriptors)
#define Chain_of_available_slot_descriptions SPECIAL_VALUE(Chain_of_available_slot_descriptions)
#define Chain_of_available_snapshot_invocation_infos SPECIAL_VALUE(Chain_of_available_snapshot_invocation_infos)
#define Chain_of_available_snapshot_of_blocks SPECIAL_VALUE(Chain_of_available_snapshot_of_blocks)
#define Chain_of_available_socket_output_buffers SPECIAL_VALUE(Chain_of_available_socket_output_buffers)
#define Chain_of_available_sockets SPECIAL_VALUE(Chain_of_available_sockets)
#define Chain_of_available_source_nupec_synchronizations SPECIAL_VALUE(Chain_of_available_source_nupec_synchronizations)
#define Chain_of_available_sparse_arrays SPECIAL_VALUE(Chain_of_available_sparse_arrays)
#define Chain_of_available_spinner_cvs SPECIAL_VALUE(Chain_of_available_spinner_cvs)
#define Chain_of_available_spots SPECIAL_VALUE(Chain_of_available_spots)
#define Chain_of_available_stack_node_instructions SPECIAL_VALUE(Chain_of_available_stack_node_instructions)
#define Chain_of_available_stack_nodes SPECIAL_VALUE(Chain_of_available_stack_nodes)
#define Chain_of_available_state_transitions SPECIAL_VALUE(Chain_of_available_state_transitions)
#define Chain_of_available_status_bar_panes SPECIAL_VALUE(Chain_of_available_status_bar_panes)
#define Chain_of_available_status_bars SPECIAL_VALUE(Chain_of_available_status_bars)
#define Chain_of_available_status_pane_spots SPECIAL_VALUE(Chain_of_available_status_pane_spots)
#define Chain_of_available_stepper_of_scroll_bar_spots SPECIAL_VALUE(Chain_of_available_stepper_of_scroll_bar_spots)
#define Chain_of_available_strict_subcategory_infos SPECIAL_VALUE(Chain_of_available_strict_subcategory_infos)
#define Chain_of_available_sub_profiling_structures SPECIAL_VALUE(Chain_of_available_sub_profiling_structures)
#define Chain_of_available_subcommand_menu_button_spots SPECIAL_VALUE(Chain_of_available_subcommand_menu_button_spots)
#define Chain_of_available_subcommand_states SPECIAL_VALUE(Chain_of_available_subcommand_states)
#define Chain_of_available_symbol_trees SPECIAL_VALUE(Chain_of_available_symbol_trees)
#define Chain_of_available_system_rpc_instances SPECIAL_VALUE(Chain_of_available_system_rpc_instances)
#define Chain_of_available_system_rpcs SPECIAL_VALUE(Chain_of_available_system_rpcs)
#define Chain_of_available_t2_nonce_datas SPECIAL_VALUE(Chain_of_available_t2_nonce_datas)
#define Chain_of_available_table_background_spots SPECIAL_VALUE(Chain_of_available_table_background_spots)
#define Chain_of_available_table_header_spots SPECIAL_VALUE(Chain_of_available_table_header_spots)
#define Chain_of_available_table_spots SPECIAL_VALUE(Chain_of_available_table_spots)
#define Chain_of_available_tabular_views SPECIAL_VALUE(Chain_of_available_tabular_views)
#define Chain_of_available_target_nupec_synchronizations SPECIAL_VALUE(Chain_of_available_target_nupec_synchronizations)
#define Chain_of_available_tcp_sockets SPECIAL_VALUE(Chain_of_available_tcp_sockets)
#define Chain_of_available_temporary_constants SPECIAL_VALUE(Chain_of_available_temporary_constants)
#define Chain_of_available_text_box_cvs SPECIAL_VALUE(Chain_of_available_text_box_cvs)
#define Chain_of_available_text_box_spots SPECIAL_VALUE(Chain_of_available_text_box_spots)
#define Chain_of_available_text_inserter_spots SPECIAL_VALUE(Chain_of_available_text_inserter_spots)
#define Chain_of_available_text_marking_states SPECIAL_VALUE(Chain_of_available_text_marking_states)
#define Chain_of_available_text_sequences SPECIAL_VALUE(Chain_of_available_text_sequences)
#define Chain_of_available_text_spots SPECIAL_VALUE(Chain_of_available_text_spots)
#define Chain_of_available_text_tokenization_states SPECIAL_VALUE(Chain_of_available_text_tokenization_states)
#define Chain_of_available_thrashing_ratio_ring_buffers SPECIAL_VALUE(Chain_of_available_thrashing_ratio_ring_buffers)
#define Chain_of_available_tiled_rasters SPECIAL_VALUE(Chain_of_available_tiled_rasters)
#define Chain_of_available_tiling_patterns SPECIAL_VALUE(Chain_of_available_tiling_patterns)
#define Chain_of_available_time_of_day_cvs SPECIAL_VALUE(Chain_of_available_time_of_day_cvs)
#define Chain_of_available_title_bar_spots SPECIAL_VALUE(Chain_of_available_title_bar_spots)
#define Chain_of_available_token_menu_button_spots SPECIAL_VALUE(Chain_of_available_token_menu_button_spots)
#define Chain_of_available_top_level_states SPECIAL_VALUE(Chain_of_available_top_level_states)
#define Chain_of_available_transcode_text_conversion_styles SPECIAL_VALUE(Chain_of_available_transcode_text_conversion_styles)
#define Chain_of_available_transcoders SPECIAL_VALUE(Chain_of_available_transcoders)
#define Chain_of_available_transfer_dragging_states SPECIAL_VALUE(Chain_of_available_transfer_dragging_states)
#define Chain_of_available_tree_view_nodes SPECIAL_VALUE(Chain_of_available_tree_view_nodes)
#define Chain_of_available_tree_views SPECIAL_VALUE(Chain_of_available_tree_views)
#define Chain_of_available_trend_chart_panes SPECIAL_VALUE(Chain_of_available_trend_chart_panes)
#define Chain_of_available_trend_chart_spots SPECIAL_VALUE(Chain_of_available_trend_chart_spots)
#define Chain_of_available_type_descriptions SPECIAL_VALUE(Chain_of_available_type_descriptions)
#define Chain_of_available_type_in_box_spots SPECIAL_VALUE(Chain_of_available_type_in_box_spots)
#define Chain_of_available_ui_callbacks SPECIAL_VALUE(Chain_of_available_ui_callbacks)
#define Chain_of_available_unicode_blocks SPECIAL_VALUE(Chain_of_available_unicode_blocks)
#define Chain_of_available_unicode_byte_swapped_transcoders SPECIAL_VALUE(Chain_of_available_unicode_byte_swapped_transcoders)
#define Chain_of_available_unicode_transcoders SPECIAL_VALUE(Chain_of_available_unicode_transcoders)
#define Chain_of_available_unicode_ucs_2_transcoders SPECIAL_VALUE(Chain_of_available_unicode_ucs_2_transcoders)
#define Chain_of_available_uninteresting_block_spots SPECIAL_VALUE(Chain_of_available_uninteresting_block_spots)
#define Chain_of_available_uri_references SPECIAL_VALUE(Chain_of_available_uri_references)
#define Chain_of_available_user_mode_aliass SPECIAL_VALUE(Chain_of_available_user_mode_aliass)
#define Chain_of_available_user_mouse_tracking_states SPECIAL_VALUE(Chain_of_available_user_mouse_tracking_states)
#define Chain_of_available_utf_7_transcoders SPECIAL_VALUE(Chain_of_available_utf_7_transcoders)
#define Chain_of_available_utf_8_transcoders SPECIAL_VALUE(Chain_of_available_utf_8_transcoders)
#define Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders SPECIAL_VALUE(Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders)
#define Chain_of_available_utf_g_transcoders SPECIAL_VALUE(Chain_of_available_utf_g_transcoders)
#define Chain_of_available_uuid_blocks SPECIAL_VALUE(Chain_of_available_uuid_blocks)
#define Chain_of_available_variable_group_update_structures SPECIAL_VALUE(Chain_of_available_variable_group_update_structures)
#define Chain_of_available_variable_simulation_runtime_structures SPECIAL_VALUE(Chain_of_available_variable_simulation_runtime_structures)
#define Chain_of_available_virtual_attributes SPECIAL_VALUE(Chain_of_available_virtual_attributes)
#define Chain_of_available_walking_menus_states SPECIAL_VALUE(Chain_of_available_walking_menus_states)
#define Chain_of_available_wide_string_text_sequences SPECIAL_VALUE(Chain_of_available_wide_string_text_sequences)
#define Chain_of_available_widget_pending_states SPECIAL_VALUE(Chain_of_available_widget_pending_states)
#define Chain_of_available_workspace_background_spots SPECIAL_VALUE(Chain_of_available_workspace_background_spots)
#define Chain_of_available_workspace_dock_spots SPECIAL_VALUE(Chain_of_available_workspace_dock_spots)
#define Chain_of_available_workspace_regions SPECIAL_VALUE(Chain_of_available_workspace_regions)
#define Chain_of_available_workspace_views SPECIAL_VALUE(Chain_of_available_workspace_views)
#define Chain_of_available_workstation_context_frames SPECIAL_VALUE(Chain_of_available_workstation_context_frames)
#define Chain_of_available_workstation_context_with_selection_focuss SPECIAL_VALUE(Chain_of_available_workstation_context_with_selection_focuss)
#define Chain_of_available_workstation_contexts SPECIAL_VALUE(Chain_of_available_workstation_contexts)
#define Chain_of_available_workstation_events SPECIAL_VALUE(Chain_of_available_workstation_events)
#define Chain_of_available_workstations SPECIAL_VALUE(Chain_of_available_workstations)
#define Chain_of_available_ws_representation_types SPECIAL_VALUE(Chain_of_available_ws_representation_types)
#define Chain_of_available_xml_namespace_lists SPECIAL_VALUE(Chain_of_available_xml_namespace_lists)
#define Chain_of_available_xml_namespaces SPECIAL_VALUE(Chain_of_available_xml_namespaces)
#define Chain_of_available_xml_node_lists SPECIAL_VALUE(Chain_of_available_xml_node_lists)
#define Chain_of_available_xml_nodes SPECIAL_VALUE(Chain_of_available_xml_nodes)
#define Chain_of_available_xml_structures SPECIAL_VALUE(Chain_of_available_xml_structures)
#define Chain_of_recycled_edit_states SPECIAL_VALUE(Chain_of_recycled_edit_states)
#define Chaining_refresh_list SPECIAL_VALUE(Chaining_refresh_list)
#define Chaining_refresh_version SPECIAL_VALUE(Chaining_refresh_version)
#define Change_the_text_of_attributes_without_category_evaluator_interfaces_p SPECIAL_VALUE(Change_the_text_of_attributes_without_category_evaluator_interfaces_p)
#define Changing_colors_of_graphic_elements_qm SPECIAL_VALUE(Changing_colors_of_graphic_elements_qm)
#define Changing_graph_margins_qm SPECIAL_VALUE(Changing_graph_margins_qm)
#define Changing_validity_interval_invalidates_current_value_p SPECIAL_VALUE(Changing_validity_interval_invalidates_current_value_p)
#define Character_bitmap_scratch_list SPECIAL_VALUE(Character_bitmap_scratch_list)
#define Character_case_mode_for_generalized_dos SPECIAL_VALUE(Character_case_mode_for_generalized_dos)
#define Character_description_count SPECIAL_VALUE(Character_description_count)
#define Character_image_count SPECIAL_VALUE(Character_image_count)
#define Character_sequence_token_menu_button_spot_count SPECIAL_VALUE(Character_sequence_token_menu_button_spot_count)
#define Characters_in_buffer_of_ok_file_reader_qm SPECIAL_VALUE(Characters_in_buffer_of_ok_file_reader_qm)
#define Chart SPECIAL_VALUE(Chart)
#define Chart_bottom SPECIAL_VALUE(Chart_bottom)
#define Chart_bottom_margin SPECIAL_VALUE(Chart_bottom_margin)
#define Chart_class_description SPECIAL_VALUE(Chart_class_description)
#define Chart_color_value_for_this_raster SPECIAL_VALUE(Chart_color_value_for_this_raster)
#define Chart_current_raster_is_monochrome_raster_list_p SPECIAL_VALUE(Chart_current_raster_is_monochrome_raster_list_p)
#define Chart_current_raster_is_polychrome_p SPECIAL_VALUE(Chart_current_raster_is_polychrome_p)
#define Chart_data_point SPECIAL_VALUE(Chart_data_point)
#define Chart_drawing SPECIAL_VALUE(Chart_drawing)
#define Chart_left SPECIAL_VALUE(Chart_left)
#define Chart_left_margin SPECIAL_VALUE(Chart_left_margin)
#define Chart_origin_x SPECIAL_VALUE(Chart_origin_x)
#define Chart_origin_y SPECIAL_VALUE(Chart_origin_y)
#define Chart_pen_color SPECIAL_VALUE(Chart_pen_color)
#define Chart_pen_color_value SPECIAL_VALUE(Chart_pen_color_value)
#define Chart_pen_x SPECIAL_VALUE(Chart_pen_x)
#define Chart_pen_y SPECIAL_VALUE(Chart_pen_y)
#define Chart_really_drawing SPECIAL_VALUE(Chart_really_drawing)
#define Chart_right SPECIAL_VALUE(Chart_right)
#define Chart_right_margin SPECIAL_VALUE(Chart_right_margin)
#define Chart_spot_count SPECIAL_VALUE(Chart_spot_count)
#define Chart_top SPECIAL_VALUE(Chart_top)
#define Chart_top_margin SPECIAL_VALUE(Chart_top_margin)
#define Chart_tuple_1_maximum SPECIAL_VALUE(Chart_tuple_1_maximum)
#define Chart_tuple_1_minimum SPECIAL_VALUE(Chart_tuple_1_minimum)
#define Chart_tuple_2_maximum SPECIAL_VALUE(Chart_tuple_2_maximum)
#define Chart_tuple_2_minimum SPECIAL_VALUE(Chart_tuple_2_minimum)
#define Chart_view_count SPECIAL_VALUE(Chart_view_count)
#define Charting_library_version_qm SPECIAL_VALUE(Charting_library_version_qm)
#define Check_box_cv_count SPECIAL_VALUE(Check_box_cv_count)
#define Check_for_circular_formula_paths_qm SPECIAL_VALUE(Check_for_circular_formula_paths_qm)
#define Check_icp_handshaking_p SPECIAL_VALUE(Check_icp_handshaking_p)
#define Check_time_on_next_uuid SPECIAL_VALUE(Check_time_on_next_uuid)
#define Checkable_list_box_cv_count SPECIAL_VALUE(Checkable_list_box_cv_count)
#define Choice_conflict SPECIAL_VALUE(Choice_conflict)
#define Class_and_foundation_class_directory_categories SPECIAL_VALUE(Class_and_foundation_class_directory_categories)
#define Class_bit_numbers_pool SPECIAL_VALUE(Class_bit_numbers_pool)
#define Class_change_timestamp SPECIAL_VALUE(Class_change_timestamp)
#define Class_definition_class_description SPECIAL_VALUE(Class_definition_class_description)
#define Class_description_cons_counter SPECIAL_VALUE(Class_description_cons_counter)
#define Class_description_count SPECIAL_VALUE(Class_description_count)
#define Class_description_for_next_frame_qm SPECIAL_VALUE(Class_description_for_next_frame_qm)
#define Class_file_stream_count SPECIAL_VALUE(Class_file_stream_count)
#define Class_info_attributes SPECIAL_VALUE(Class_info_attributes)
#define Class_instance_header_type_of_slot SPECIAL_VALUE(Class_instance_header_type_of_slot)
#define Class_instances_memory_info_count SPECIAL_VALUE(Class_instances_memory_info_count)
#define Class_is_undergoing_inheritance_change_qm SPECIAL_VALUE(Class_is_undergoing_inheritance_change_qm)
#define Class_name_conflicts SPECIAL_VALUE(Class_name_conflicts)
#define Class_name_max_length SPECIAL_VALUE(Class_name_max_length)
#define Class_name_read_while_reading_current_ghost_definition SPECIAL_VALUE(Class_name_read_while_reading_current_ghost_definition)
#define Class_specific_instances_lock SPECIAL_VALUE(Class_specific_instances_lock)
#define Class_subscription_count SPECIAL_VALUE(Class_subscription_count)
#define Class_subscriptions_count SPECIAL_VALUE(Class_subscriptions_count)
#define Classes_and_directory_categories_for_classes SPECIAL_VALUE(Classes_and_directory_categories_for_classes)
#define Classes_needing_data_interface_initialization SPECIAL_VALUE(Classes_needing_data_interface_initialization)
#define Classes_not_defined_in_any_module SPECIAL_VALUE(Classes_not_defined_in_any_module)
#define Classes_of_objects_to_not_consider_qm SPECIAL_VALUE(Classes_of_objects_to_not_consider_qm)
#define Classes_remaining_to_sort SPECIAL_VALUE(Classes_remaining_to_sort)
#define Classes_sorted_so_far SPECIAL_VALUE(Classes_sorted_so_far)
#define Classes_visited_byte_vector SPECIAL_VALUE(Classes_visited_byte_vector)
#define Classes_whose_superiors_are_not_defined_in_required_modules SPECIAL_VALUE(Classes_whose_superiors_are_not_defined_in_required_modules)
#define Clear_text_grammar_rules_added_p SPECIAL_VALUE(Clear_text_grammar_rules_added_p)
#define Clear_text_item_layering_info SPECIAL_VALUE(Clear_text_item_layering_info)
#define Clear_text_primitive_value_style SPECIAL_VALUE(Clear_text_primitive_value_style)
#define Clear_text_saving_problems_were_encountered_p SPECIAL_VALUE(Clear_text_saving_problems_were_encountered_p)
#define Clipping_rectangles_for_new_data_qm SPECIAL_VALUE(Clipping_rectangles_for_new_data_qm)
#define Clock_sequence_for_uuid SPECIAL_VALUE(Clock_sequence_for_uuid)
#define Clogged_count SPECIAL_VALUE(Clogged_count)
#define Close_box_rubber_stamp_widget SPECIAL_VALUE(Close_box_rubber_stamp_widget)
#define Close_box_spot_count SPECIAL_VALUE(Close_box_spot_count)
#define Closing_procedure_invocation SPECIAL_VALUE(Closing_procedure_invocation)
#define Code_body SPECIAL_VALUE(Code_body)
#define Code_body_continuation_count SPECIAL_VALUE(Code_body_continuation_count)
#define Code_body_entries_in_compilation SPECIAL_VALUE(Code_body_entries_in_compilation)
#define Code_body_invocation_count SPECIAL_VALUE(Code_body_invocation_count)
#define Collected_frame_notes_for_class_export_qm SPECIAL_VALUE(Collected_frame_notes_for_class_export_qm)
#define Collected_items_with_warnings_alist SPECIAL_VALUE(Collected_items_with_warnings_alist)
#define Collected_menu_content_structure SPECIAL_VALUE(Collected_menu_content_structure)
#define Collected_updates_to_sensor_attributes SPECIAL_VALUE(Collected_updates_to_sensor_attributes)
#define Collecting_denotation_errors_p SPECIAL_VALUE(Collecting_denotation_errors_p)
#define Collecting_exported_method_text_p SPECIAL_VALUE(Collecting_exported_method_text_p)
#define Collecting_frame_notes_for_class_export_p SPECIAL_VALUE(Collecting_frame_notes_for_class_export_p)
#define Collecting_free_references SPECIAL_VALUE(Collecting_free_references)
#define Collecting_procedures_to_warn_about_p SPECIAL_VALUE(Collecting_procedures_to_warn_about_p)
#define Collecting_updates_to_sensor_attributes_p SPECIAL_VALUE(Collecting_updates_to_sensor_attributes_p)
#define Collecting_warnings_p SPECIAL_VALUE(Collecting_warnings_p)
#define Color_change_indicator SPECIAL_VALUE(Color_change_indicator)
#define Color_changes_indicator SPECIAL_VALUE(Color_changes_indicator)
#define Color_code_differences SPECIAL_VALUE(Color_code_differences)
#define Color_difference_for_line_of_text_of_graphic_element SPECIAL_VALUE(Color_difference_for_line_of_text_of_graphic_element)
#define Color_hierarchy SPECIAL_VALUE(Color_hierarchy)
#define Color_map_count SPECIAL_VALUE(Color_map_count)
#define Color_parameters SPECIAL_VALUE(Color_parameters)
#define Color_values_of_graph_rasters_of_graphic_element SPECIAL_VALUE(Color_values_of_graph_rasters_of_graphic_element)
#define Column SPECIAL_VALUE(Column)
#define Column_maximum SPECIAL_VALUE(Column_maximum)
#define Column_width SPECIAL_VALUE(Column_width)
#define Combiners_for_defun_incremental SPECIAL_VALUE(Combiners_for_defun_incremental)
#define Command_line_qm SPECIAL_VALUE(Command_line_qm)
#define Comp_trace_level SPECIAL_VALUE(Comp_trace_level)
#define Compare_xml_collect_diffs_p SPECIAL_VALUE(Compare_xml_collect_diffs_p)
#define Compilation_local_name_listed_next_symbol SPECIAL_VALUE(Compilation_local_name_listed_next_symbol)
#define Compilation_local_name_symbol_counter SPECIAL_VALUE(Compilation_local_name_symbol_counter)
#define Compilation_local_name_symbol_supply SPECIAL_VALUE(Compilation_local_name_symbol_supply)
#define Compilations_were_removed_in_this_kb_module_qm SPECIAL_VALUE(Compilations_were_removed_in_this_kb_module_qm)
#define Compile_reference_to_system_slot SPECIAL_VALUE(Compile_reference_to_system_slot)
#define Compiled_antecedent_1 SPECIAL_VALUE(Compiled_antecedent_1)
#define Compiled_cell_expression SPECIAL_VALUE(Compiled_cell_expression)
#define Compiled_code_grammar_rules_added_p SPECIAL_VALUE(Compiled_code_grammar_rules_added_p)
#define Compiled_consequent_1 SPECIAL_VALUE(Compiled_consequent_1)
#define Compiled_consequent_2 SPECIAL_VALUE(Compiled_consequent_2)
#define Compiled_item_being_analyzed SPECIAL_VALUE(Compiled_item_being_analyzed)
#define Compiled_item_being_analyzed_started_out_incomplete_qm SPECIAL_VALUE(Compiled_item_being_analyzed_started_out_incomplete_qm)
#define Compiled_items_deferred_for_analysis SPECIAL_VALUE(Compiled_items_deferred_for_analysis)
#define Compiled_kb_indent SPECIAL_VALUE(Compiled_kb_indent)
#define Compiled_kb_initialization_array_initialized_p SPECIAL_VALUE(Compiled_kb_initialization_array_initialized_p)
#define Compiled_resource_count SPECIAL_VALUE(Compiled_resource_count)
#define Compiler_code_body_entry_count SPECIAL_VALUE(Compiler_code_body_entry_count)
#define Compiler_cons_counter SPECIAL_VALUE(Compiler_cons_counter)
#define Compiler_errors SPECIAL_VALUE(Compiler_errors)
#define Compiler_free_references SPECIAL_VALUE(Compiler_free_references)
#define Compiler_warnings SPECIAL_VALUE(Compiler_warnings)
#define Compiling_antecedent_p SPECIAL_VALUE(Compiling_antecedent_p)
#define Compiling_expression_p SPECIAL_VALUE(Compiling_expression_p)
#define Compiling_incomplete_items_after_analyze_p SPECIAL_VALUE(Compiling_incomplete_items_after_analyze_p)
#define Compiling_rule_p SPECIAL_VALUE(Compiling_rule_p)
#define Complete_kb_name_qm SPECIAL_VALUE(Complete_kb_name_qm)
#define Component_change_report_count SPECIAL_VALUE(Component_change_report_count)
#define Compound_fixnum_simulation_time_count SPECIAL_VALUE(Compound_fixnum_simulation_time_count)
#define Compound_slot_descriptor_count SPECIAL_VALUE(Compound_slot_descriptor_count)
#define Compound_type_descriptor_count SPECIAL_VALUE(Compound_type_descriptor_count)
#define Computation_frame_at_breakpoint SPECIAL_VALUE(Computation_frame_at_breakpoint)
#define Computation_instance_at_breakpoint SPECIAL_VALUE(Computation_instance_at_breakpoint)
#define Computation_instance_count SPECIAL_VALUE(Computation_instance_count)
#define Computation_style_description SPECIAL_VALUE(Computation_style_description)
#define Compute_menu_items_list SPECIAL_VALUE(Compute_menu_items_list)
#define Conclude_attribute_binding_listed_next_symbol SPECIAL_VALUE(Conclude_attribute_binding_listed_next_symbol)
#define Conclude_attribute_binding_symbol_counter SPECIAL_VALUE(Conclude_attribute_binding_symbol_counter)
#define Conclude_attribute_binding_symbol_supply SPECIAL_VALUE(Conclude_attribute_binding_symbol_supply)
#define Conclude_parent_attribute_bindings SPECIAL_VALUE(Conclude_parent_attribute_bindings)
#define Conditional_selected_choice_qm SPECIAL_VALUE(Conditional_selected_choice_qm)
#define Conditional_termination_state_qm SPECIAL_VALUE(Conditional_termination_state_qm)
#define Connected_subnet SPECIAL_VALUE(Connected_subnet)
#define Connection_class_description SPECIAL_VALUE(Connection_class_description)
#define Connection_classes_warned_about_for_this_kb SPECIAL_VALUE(Connection_classes_warned_about_for_this_kb)
#define Connection_cons_counter SPECIAL_VALUE(Connection_cons_counter)
#define Connection_count SPECIAL_VALUE(Connection_count)
#define Connection_definition_class_description SPECIAL_VALUE(Connection_definition_class_description)
#define Connection_handling_block_queue SPECIAL_VALUE(Connection_handling_block_queue)
#define Connection_handling_connection_queue SPECIAL_VALUE(Connection_handling_connection_queue)
#define Connection_handling_connection_type_queue SPECIAL_VALUE(Connection_handling_connection_type_queue)
#define Connection_handling_fsn_queue SPECIAL_VALUE(Connection_handling_fsn_queue)
#define Connection_handling_procedure_fsn_qm SPECIAL_VALUE(Connection_handling_procedure_fsn_qm)
#define Connection_handling_procedure_qm SPECIAL_VALUE(Connection_handling_procedure_qm)
#define Connection_handling_window_queue SPECIAL_VALUE(Connection_handling_window_queue)
#define Connection_item_count SPECIAL_VALUE(Connection_item_count)
#define Connection_post_class_description SPECIAL_VALUE(Connection_post_class_description)
#define Connection_spot_count SPECIAL_VALUE(Connection_spot_count)
#define Connection_subrectangle_structure_count SPECIAL_VALUE(Connection_subrectangle_structure_count)
#define Connections_in_connection_paths SPECIAL_VALUE(Connections_in_connection_paths)
#define Connections_in_modules_a_list SPECIAL_VALUE(Connections_in_modules_a_list)
#define Connections_to_be_excluded_qm SPECIAL_VALUE(Connections_to_be_excluded_qm)
#define Connections_to_delete_after_reading_kb SPECIAL_VALUE(Connections_to_delete_after_reading_kb)
#define Consider_asian_language_initializations_qm SPECIAL_VALUE(Consider_asian_language_initializations_qm)
#define Consistency_tree_focus_shifts SPECIAL_VALUE(Consistency_tree_focus_shifts)
#define Contains_either_really_transient_or_proprietary_p_1 SPECIAL_VALUE(Contains_either_really_transient_or_proprietary_p_1)
#define Contains_proprietary_p_1 SPECIAL_VALUE(Contains_proprietary_p_1)
#define Context_iteration_forms SPECIAL_VALUE(Context_iteration_forms)
#define Context_of_type_failure SPECIAL_VALUE(Context_of_type_failure)
#define Continuation_task_for_current_backup SPECIAL_VALUE(Continuation_task_for_current_backup)
#define Continue_current_kb_save_failure SPECIAL_VALUE(Continue_current_kb_save_failure)
#define Contour_of_ok_file_tokens SPECIAL_VALUE(Contour_of_ok_file_tokens)
#define Control_sequence_record SPECIAL_VALUE(Control_sequence_record)
#define Control_stack_of_frame_projecting SPECIAL_VALUE(Control_stack_of_frame_projecting)
#define Convert_file_strings_to_uppercase_p SPECIAL_VALUE(Convert_file_strings_to_uppercase_p)
#define Copyright_boilerplate_lines_of_text_1 SPECIAL_VALUE(Copyright_boilerplate_lines_of_text_1)
#define Copyright_boilerplate_lines_of_text_2 SPECIAL_VALUE(Copyright_boilerplate_lines_of_text_2)
#define Corresponding_icp_object_index_for_item_new_copy SPECIAL_VALUE(Corresponding_icp_object_index_for_item_new_copy)
#define Corresponding_icp_object_index_for_item_reference SPECIAL_VALUE(Corresponding_icp_object_index_for_item_reference)
#define Count_of_8859_reverse_unicode_map_hash_vector_43_vectors SPECIAL_VALUE(Count_of_8859_reverse_unicode_map_hash_vector_43_vectors)
#define Count_of_blocks_hash_hash_vector_43_vectors SPECIAL_VALUE(Count_of_blocks_hash_hash_vector_43_vectors)
#define Count_of_call_hash_hash_vector_43_vectors SPECIAL_VALUE(Count_of_call_hash_hash_vector_43_vectors)
#define Count_of_duplicates_check_hash_table_hash_vector_50021_vectors SPECIAL_VALUE(Count_of_duplicates_check_hash_table_hash_vector_50021_vectors)
#define Count_of_dynamic_rule_displays_hash_vector_43_vectors SPECIAL_VALUE(Count_of_dynamic_rule_displays_hash_vector_43_vectors)
#define Count_of_foreign_function_registry_internal_hash_vector_131_vectors SPECIAL_VALUE(Count_of_foreign_function_registry_internal_hash_vector_131_vectors)
#define Count_of_frame_serial_number_to_item_table_hash_vector_67_vectors SPECIAL_VALUE(Count_of_frame_serial_number_to_item_table_hash_vector_67_vectors)
#define Count_of_generic_rule_instance_displays_hash_vector_43_vectors SPECIAL_VALUE(Count_of_generic_rule_instance_displays_hash_vector_43_vectors)
#define Count_of_gfi_spreadsheet_field_index_hash_vector_131_vectors SPECIAL_VALUE(Count_of_gfi_spreadsheet_field_index_hash_vector_131_vectors)
#define Count_of_graph_node_of_graphed_thing_hash_vector_43_vectors SPECIAL_VALUE(Count_of_graph_node_of_graphed_thing_hash_vector_43_vectors)
#define Count_of_hashed_rule_instance_hash_vector_43_vectors SPECIAL_VALUE(Count_of_hashed_rule_instance_hash_vector_43_vectors)
#define Count_of_indexed_attribute_parent_objects_hash_vector_43_vectors SPECIAL_VALUE(Count_of_indexed_attribute_parent_objects_hash_vector_43_vectors)
#define Count_of_interned_gensym_strings SPECIAL_VALUE(Count_of_interned_gensym_strings)
#define Count_of_interned_text_strings SPECIAL_VALUE(Count_of_interned_text_strings)
#define Count_of_item_or_name_hash_hash_vector_43_vectors SPECIAL_VALUE(Count_of_item_or_name_hash_hash_vector_43_vectors)
#define Count_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors SPECIAL_VALUE(Count_of_items_encountered_in_memory_walk_hash_table_hash_vector_131_vectors)
#define Count_of_jis_map_hash_vector_307_vectors SPECIAL_VALUE(Count_of_jis_map_hash_vector_307_vectors)
#define Count_of_kanji_font_cache_vector_137_vectors SPECIAL_VALUE(Count_of_kanji_font_cache_vector_137_vectors)
#define Count_of_kb_fsn_hash_table_hash_vector_131_vectors SPECIAL_VALUE(Count_of_kb_fsn_hash_table_hash_vector_131_vectors)
#define Count_of_module_required_by_relationships_hash_vector_43_vectors SPECIAL_VALUE(Count_of_module_required_by_relationships_hash_vector_43_vectors)
#define Count_of_native_font_set_width_equivalence_table_256_vectors SPECIAL_VALUE(Count_of_native_font_set_width_equivalence_table_256_vectors)
#define Count_of_native_icon_handle_hash_vector_43_vectors SPECIAL_VALUE(Count_of_native_icon_handle_hash_vector_43_vectors)
#define Count_of_nms_menu_for_hmenu_hash_vector_43_vectors SPECIAL_VALUE(Count_of_nms_menu_for_hmenu_hash_vector_43_vectors)
#define Count_of_non_kanji_font_vector_257_vectors SPECIAL_VALUE(Count_of_non_kanji_font_vector_257_vectors)
#define Count_of_object_circularity_hashtable_hash_vector_131_vectors SPECIAL_VALUE(Count_of_object_circularity_hashtable_hash_vector_131_vectors)
#define Count_of_pending_workspace_drawing SPECIAL_VALUE(Count_of_pending_workspace_drawing)
#define Count_of_procedure_invocations_hash_vector_43_vectors SPECIAL_VALUE(Count_of_procedure_invocations_hash_vector_43_vectors)
#define Count_of_representation_handle_hash_vector_109_vectors SPECIAL_VALUE(Count_of_representation_handle_hash_vector_109_vectors)
#define Count_of_scaled_font_kanji_font_cache_vector_1096_vectors SPECIAL_VALUE(Count_of_scaled_font_kanji_font_cache_vector_1096_vectors)
#define Count_of_scaled_font_non_kanji_font_vector_2049_vectors SPECIAL_VALUE(Count_of_scaled_font_non_kanji_font_vector_2049_vectors)
#define Count_of_sexp_annotation_hash_vector_43_vectors SPECIAL_VALUE(Count_of_sexp_annotation_hash_vector_43_vectors)
#define Count_of_sub_call_hash_hash_vector_43_vectors SPECIAL_VALUE(Count_of_sub_call_hash_hash_vector_43_vectors)
#define Count_of_subseries_of_values_64_vectors SPECIAL_VALUE(Count_of_subseries_of_values_64_vectors)
#define Count_of_sysproc_continuation_hashtable_hash_vector_131_vectors SPECIAL_VALUE(Count_of_sysproc_continuation_hashtable_hash_vector_131_vectors)
#define Count_of_tracked_items_call_vector_table_hash_vector_43_vectors SPECIAL_VALUE(Count_of_tracked_items_call_vector_table_hash_vector_43_vectors)
#define Count_of_ui_callback_table_hash_vector_43_vectors SPECIAL_VALUE(Count_of_ui_callback_table_hash_vector_43_vectors)
#define Count_of_uo_memory_usage_information_hash_vector_43_vectors SPECIAL_VALUE(Count_of_uo_memory_usage_information_hash_vector_43_vectors)
#define Count_of_user_hash_table_internal_hash_vector_43_vectors SPECIAL_VALUE(Count_of_user_hash_table_internal_hash_vector_43_vectors)
#define Count_of_variable_fill_icp_buffer_4096_vectors SPECIAL_VALUE(Count_of_variable_fill_icp_buffer_4096_vectors)
#define Countdown_for_checking SPECIAL_VALUE(Countdown_for_checking)
#define Create_frames_and_connections_reading_past_qm SPECIAL_VALUE(Create_frames_and_connections_reading_past_qm)
#define Create_process_instance_for_current_process_p SPECIAL_VALUE(Create_process_instance_for_current_process_p)
#define Create_subpart_upon_tracking_p SPECIAL_VALUE(Create_subpart_upon_tracking_p)
#define Created_oversized_simple_float_array_pool_arrays SPECIAL_VALUE(Created_oversized_simple_float_array_pool_arrays)
#define Created_simple_float_array_pool_arrays SPECIAL_VALUE(Created_simple_float_array_pool_arrays)
#define Created_simple_long_array_pool_arrays SPECIAL_VALUE(Created_simple_long_array_pool_arrays)
#define Created_simple_vector_pool_vectors SPECIAL_VALUE(Created_simple_vector_pool_vectors)
#define Credits_table_spot_count SPECIAL_VALUE(Credits_table_spot_count)
#define Ctlc_cons_count SPECIAL_VALUE(Ctlc_cons_count)
#define Cumulative_x_scaled_connection_stripe_half_width SPECIAL_VALUE(Cumulative_x_scaled_connection_stripe_half_width)
#define Cumulative_x_scaled_connection_stripe_width SPECIAL_VALUE(Cumulative_x_scaled_connection_stripe_width)
#define Cumulative_y_scaled_connection_stripe_half_width SPECIAL_VALUE(Cumulative_y_scaled_connection_stripe_half_width)
#define Cumulative_y_scaled_connection_stripe_width SPECIAL_VALUE(Cumulative_y_scaled_connection_stripe_width)
#define Current_2d_rendering SPECIAL_VALUE(Current_2d_rendering)
#define Current_2d_state SPECIAL_VALUE(Current_2d_state)
#define Current_a_matrix SPECIAL_VALUE(Current_a_matrix)
#define Current_ab_font_qm SPECIAL_VALUE(Current_ab_font_qm)
#define Current_agenda_accumulating SPECIAL_VALUE(Current_agenda_accumulating)
#define Current_anchor_p SPECIAL_VALUE(Current_anchor_p)
#define Current_annotated_frame SPECIAL_VALUE(Current_annotated_frame)
#define Current_attribute_description_class SPECIAL_VALUE(Current_attribute_description_class)
#define Current_attribute_description_index SPECIAL_VALUE(Current_attribute_description_index)
#define Current_attribute_file_pathname_qm SPECIAL_VALUE(Current_attribute_file_pathname_qm)
#define Current_axis SPECIAL_VALUE(Current_axis)
#define Current_axis_pane SPECIAL_VALUE(Current_axis_pane)
#define Current_b_vector SPECIAL_VALUE(Current_b_vector)
#define Current_background_color_value SPECIAL_VALUE(Current_background_color_value)
#define Current_background_process SPECIAL_VALUE(Current_background_process)
#define Current_backup_definition_workspace_qm SPECIAL_VALUE(Current_backup_definition_workspace_qm)
#define Current_backup_definition_workspace_serial_number_qm SPECIAL_VALUE(Current_backup_definition_workspace_serial_number_qm)
#define Current_basic_part SPECIAL_VALUE(Current_basic_part)
#define Current_best_match_for_eyes SPECIAL_VALUE(Current_best_match_for_eyes)
#define Current_block_of_dependent_frame SPECIAL_VALUE(Current_block_of_dependent_frame)
#define Current_callback_representation_subscription_handle SPECIAL_VALUE(Current_callback_representation_subscription_handle)
#define Current_cascaded_ring_buffer SPECIAL_VALUE(Current_cascaded_ring_buffer)
#define Current_category_name_for_type_specification_type_p SPECIAL_VALUE(Current_category_name_for_type_specification_type_p)
#define Current_category_visit_stamp SPECIAL_VALUE(Current_category_visit_stamp)
#define Current_cell SPECIAL_VALUE(Current_cell)
#define Current_character SPECIAL_VALUE(Current_character)
#define Current_character_index_after_token SPECIAL_VALUE(Current_character_index_after_token)
#define Current_character_syntax_table SPECIAL_VALUE(Current_character_syntax_table)
#define Current_chart SPECIAL_VALUE(Current_chart)
#define Current_chart_data_point SPECIAL_VALUE(Current_chart_data_point)
#define Current_chart_frame SPECIAL_VALUE(Current_chart_frame)
#define Current_chart_raster_color_value SPECIAL_VALUE(Current_chart_raster_color_value)
#define Current_code_body_entry SPECIAL_VALUE(Current_code_body_entry)
#define Current_color_map SPECIAL_VALUE(Current_color_map)
#define Current_column SPECIAL_VALUE(Current_column)
#define Current_compiled_cell_expression SPECIAL_VALUE(Current_compiled_cell_expression)
#define Current_component_type_for_sorting SPECIAL_VALUE(Current_component_type_for_sorting)
#define Current_computation_activity SPECIAL_VALUE(Current_computation_activity)
#define Current_computation_component_particulars SPECIAL_VALUE(Current_computation_component_particulars)
#define Current_computation_flags SPECIAL_VALUE(Current_computation_flags)
#define Current_computation_frame SPECIAL_VALUE(Current_computation_frame)
#define Current_computation_instance SPECIAL_VALUE(Current_computation_instance)
#define Current_computation_slot_component_group SPECIAL_VALUE(Current_computation_slot_component_group)
#define Current_computation_style SPECIAL_VALUE(Current_computation_style)
#define Current_computation_style_description SPECIAL_VALUE(Current_computation_style_description)
#define Current_conclude_frame_list SPECIAL_VALUE(Current_conclude_frame_list)
#define Current_conclude_innermost_attribute_description SPECIAL_VALUE(Current_conclude_innermost_attribute_description)
#define Current_conclude_innermost_frame SPECIAL_VALUE(Current_conclude_innermost_frame)
#define Current_conclude_innermost_item_index SPECIAL_VALUE(Current_conclude_innermost_item_index)
#define Current_connection_path SPECIAL_VALUE(Current_connection_path)
#define Current_create_frame_description_reference_1 SPECIAL_VALUE(Current_create_frame_description_reference_1)
#define Current_custom_reclamation_stamp_qm SPECIAL_VALUE(Current_custom_reclamation_stamp_qm)
#define Current_cvs_command SPECIAL_VALUE(Current_cvs_command)
#define Current_data_buffer_for_plot SPECIAL_VALUE(Current_data_buffer_for_plot)
#define Current_data_series SPECIAL_VALUE(Current_data_series)
#define Current_ddd_dot_dddd_format_qm SPECIAL_VALUE(Current_ddd_dot_dddd_format_qm)
#define Current_default_line_color SPECIAL_VALUE(Current_default_line_color)
#define Current_delta SPECIAL_VALUE(Current_delta)
#define Current_description_of_new_table SPECIAL_VALUE(Current_description_of_new_table)
#define Current_dialog_errors_structure SPECIAL_VALUE(Current_dialog_errors_structure)
#define Current_directory_of_binary_truenames SPECIAL_VALUE(Current_directory_of_binary_truenames)
#define Current_directory_of_source_truenames_qm SPECIAL_VALUE(Current_directory_of_source_truenames_qm)
#define Current_display_pane_bottom SPECIAL_VALUE(Current_display_pane_bottom)
#define Current_display_pane_height SPECIAL_VALUE(Current_display_pane_height)
#define Current_display_pane_left SPECIAL_VALUE(Current_display_pane_left)
#define Current_display_pane_right SPECIAL_VALUE(Current_display_pane_right)
#define Current_display_pane_top SPECIAL_VALUE(Current_display_pane_top)
#define Current_display_pane_width SPECIAL_VALUE(Current_display_pane_width)
#define Current_dragging_states SPECIAL_VALUE(Current_dragging_states)
#define Current_draw_document_p SPECIAL_VALUE(Current_draw_document_p)
#define Current_draw_paper_p SPECIAL_VALUE(Current_draw_paper_p)
#define Current_drawing_priority SPECIAL_VALUE(Current_drawing_priority)
#define Current_drawing_transfer_mode SPECIAL_VALUE(Current_drawing_transfer_mode)
#define Current_edit_state SPECIAL_VALUE(Current_edit_state)
#define Current_edit_workspace SPECIAL_VALUE(Current_edit_workspace)
#define Current_environment SPECIAL_VALUE(Current_environment)
#define Current_extended_utf_g_low_half_character_qm SPECIAL_VALUE(Current_extended_utf_g_low_half_character_qm)
#define Current_filters_search_result SPECIAL_VALUE(Current_filters_search_result)
#define Current_foreground_color_value SPECIAL_VALUE(Current_foreground_color_value)
#define Current_foreign_function_call_info SPECIAL_VALUE(Current_foreign_function_call_info)
#define Current_foreign_image_pathname_qm SPECIAL_VALUE(Current_foreign_image_pathname_qm)
#define Current_formatted_part SPECIAL_VALUE(Current_formatted_part)
#define Current_frame_serial_number SPECIAL_VALUE(Current_frame_serial_number)
#define Current_frame_serial_number_before_reading SPECIAL_VALUE(Current_frame_serial_number_before_reading)
#define Current_frame_transform_qm SPECIAL_VALUE(Current_frame_transform_qm)
#define Current_g2_rdf_module SPECIAL_VALUE(Current_g2_rdf_module)
#define Current_g2_time SPECIAL_VALUE(Current_g2_time)
#define Current_g2_user_mode_qm SPECIAL_VALUE(Current_g2_user_mode_qm)
#define Current_g2_window_for_this_workstation_qm SPECIAL_VALUE(Current_g2_window_for_this_workstation_qm)
#define Current_g2binary_file_symbol_index SPECIAL_VALUE(Current_g2binary_file_symbol_index)
#define Current_g2gl_definition SPECIAL_VALUE(Current_g2gl_definition)
#define Current_gensym_string SPECIAL_VALUE(Current_gensym_string)
#define Current_gensym_window_serial_number SPECIAL_VALUE(Current_gensym_window_serial_number)
#define Current_gesture_code_sequence SPECIAL_VALUE(Current_gesture_code_sequence)
#define Current_gesture_code_sequences SPECIAL_VALUE(Current_gesture_code_sequences)
#define Current_gesture_frame_pointer SPECIAL_VALUE(Current_gesture_frame_pointer)
#define Current_gesture_label_index SPECIAL_VALUE(Current_gesture_label_index)
#define Current_gesture_sequence_index SPECIAL_VALUE(Current_gesture_sequence_index)
#define Current_gesture_stack_pointer SPECIAL_VALUE(Current_gesture_stack_pointer)
#define Current_grammar SPECIAL_VALUE(Current_grammar)
#define Current_graph_grid SPECIAL_VALUE(Current_graph_grid)
#define Current_graph_grid_in_minimal_update SPECIAL_VALUE(Current_graph_grid_in_minimal_update)
#define Current_graph_layout_hashing_function SPECIAL_VALUE(Current_graph_layout_hashing_function)
#define Current_graph_rendering SPECIAL_VALUE(Current_graph_rendering)
#define Current_graph_rendering_embedded_icons SPECIAL_VALUE(Current_graph_rendering_embedded_icons)
#define Current_graph_rendering_structure SPECIAL_VALUE(Current_graph_rendering_structure)
#define Current_grid SPECIAL_VALUE(Current_grid)
#define Current_grid_painting_actions_to_delete SPECIAL_VALUE(Current_grid_painting_actions_to_delete)
#define Current_grid_painting_background_color_value SPECIAL_VALUE(Current_grid_painting_background_color_value)
#define Current_grid_painting_color_mode SPECIAL_VALUE(Current_grid_painting_color_mode)
#define Current_grid_painting_earliest_time SPECIAL_VALUE(Current_grid_painting_earliest_time)
#define Current_grid_painting_foreground_color_value SPECIAL_VALUE(Current_grid_painting_foreground_color_value)
#define Current_grid_painting_is_full_qm SPECIAL_VALUE(Current_grid_painting_is_full_qm)
#define Current_grid_painting_latest_time SPECIAL_VALUE(Current_grid_painting_latest_time)
#define Current_grid_painting_mode SPECIAL_VALUE(Current_grid_painting_mode)
#define Current_grid_painting_queue SPECIAL_VALUE(Current_grid_painting_queue)
#define Current_grid_painting_queue_tail SPECIAL_VALUE(Current_grid_painting_queue_tail)
#define Current_grid_painting_x_scale SPECIAL_VALUE(Current_grid_painting_x_scale)
#define Current_grid_painting_y_scale SPECIAL_VALUE(Current_grid_painting_y_scale)
#define Current_height_of_formatted_part SPECIAL_VALUE(Current_height_of_formatted_part)
#define Current_hfep_c_act SPECIAL_VALUE(Current_hfep_c_act)
#define Current_hfep_c_state SPECIAL_VALUE(Current_hfep_c_state)
#define Current_hfep_cchar SPECIAL_VALUE(Current_hfep_cchar)
#define Current_hfep_nchar SPECIAL_VALUE(Current_hfep_nchar)
#define Current_icon_editor SPECIAL_VALUE(Current_icon_editor)
#define Current_icon_editor_event SPECIAL_VALUE(Current_icon_editor_event)
#define Current_icon_editor_workspace SPECIAL_VALUE(Current_icon_editor_workspace)
#define Current_icon_substitution_list SPECIAL_VALUE(Current_icon_substitution_list)
#define Current_icon_untransformed_height SPECIAL_VALUE(Current_icon_untransformed_height)
#define Current_icon_untransformed_width SPECIAL_VALUE(Current_icon_untransformed_width)
#define Current_icon_variables_override_plist SPECIAL_VALUE(Current_icon_variables_override_plist)
#define Current_icon_variables_plist SPECIAL_VALUE(Current_icon_variables_plist)
#define Current_icp_buffer SPECIAL_VALUE(Current_icp_buffer)
#define Current_icp_port SPECIAL_VALUE(Current_icp_port)
#define Current_icp_read_trace_level SPECIAL_VALUE(Current_icp_read_trace_level)
#define Current_icp_socket SPECIAL_VALUE(Current_icp_socket)
#define Current_icp_write_trace_level SPECIAL_VALUE(Current_icp_write_trace_level)
#define Current_image_plane SPECIAL_VALUE(Current_image_plane)
#define Current_image_plane_for_button SPECIAL_VALUE(Current_image_plane_for_button)
#define Current_image_plane_qm SPECIAL_VALUE(Current_image_plane_qm)
#define Current_image_x_scale SPECIAL_VALUE(Current_image_x_scale)
#define Current_image_y_scale SPECIAL_VALUE(Current_image_y_scale)
#define Current_include_denotation_for_block_flag SPECIAL_VALUE(Current_include_denotation_for_block_flag)
#define Current_index SPECIAL_VALUE(Current_index)
#define Current_index_array SPECIAL_VALUE(Current_index_array)
#define Current_indicator_for_category_of_symbol_token SPECIAL_VALUE(Current_indicator_for_category_of_symbol_token)
#define Current_indicator_for_category_of_this_name SPECIAL_VALUE(Current_indicator_for_category_of_this_name)
#define Current_input_stack SPECIAL_VALUE(Current_input_stack)
#define Current_invocation_remotely_started_p SPECIAL_VALUE(Current_invocation_remotely_started_p)
#define Current_jemit_args SPECIAL_VALUE(Current_jemit_args)
#define Current_jemit_class_description SPECIAL_VALUE(Current_jemit_class_description)
#define Current_jemit_class_object_table SPECIAL_VALUE(Current_jemit_class_object_table)
#define Current_jemit_compound_statement_list SPECIAL_VALUE(Current_jemit_compound_statement_list)
#define Current_jemit_indent SPECIAL_VALUE(Current_jemit_indent)
#define Current_jemit_locals SPECIAL_VALUE(Current_jemit_locals)
#define Current_jemit_node_stack SPECIAL_VALUE(Current_jemit_node_stack)
#define Current_jemit_return_type_specification_qm SPECIAL_VALUE(Current_jemit_return_type_specification_qm)
#define Current_jemit_self_name SPECIAL_VALUE(Current_jemit_self_name)
#define Current_jemit_stream SPECIAL_VALUE(Current_jemit_stream)
#define Current_jemit_text_style_qm SPECIAL_VALUE(Current_jemit_text_style_qm)
#define Current_kb_file_progress_for_modules_qm SPECIAL_VALUE(Current_kb_file_progress_for_modules_qm)
#define Current_kb_pathname_qm SPECIAL_VALUE(Current_kb_pathname_qm)
#define Current_kb_save SPECIAL_VALUE(Current_kb_save)
#define Current_kb_serial_number SPECIAL_VALUE(Current_kb_serial_number)
#define Current_kb_specific_property_list_property_name SPECIAL_VALUE(Current_kb_specific_property_list_property_name)
#define Current_kind_of_change SPECIAL_VALUE(Current_kind_of_change)
#define Current_let_action_bindings SPECIAL_VALUE(Current_let_action_bindings)
#define Current_lexing_patterns SPECIAL_VALUE(Current_lexing_patterns)
#define Current_lexing_rule_number SPECIAL_VALUE(Current_lexing_rule_number)
#define Current_lexing_strings SPECIAL_VALUE(Current_lexing_strings)
#define Current_line_index_for_end_of_token SPECIAL_VALUE(Current_line_index_for_end_of_token)
#define Current_linearized_kb_required_modules SPECIAL_VALUE(Current_linearized_kb_required_modules)
#define Current_localization_domains_qm SPECIAL_VALUE(Current_localization_domains_qm)
#define Current_localization_purpose_qm SPECIAL_VALUE(Current_localization_purpose_qm)
#define Current_logbook_qm SPECIAL_VALUE(Current_logbook_qm)
#define Current_logbook_serial_number_qm SPECIAL_VALUE(Current_logbook_serial_number_qm)
#define Current_long_operation_notification_workspace SPECIAL_VALUE(Current_long_operation_notification_workspace)
#define Current_lookup_data SPECIAL_VALUE(Current_lookup_data)
#define Current_lr_states SPECIAL_VALUE(Current_lr_states)
#define Current_lu_matrix SPECIAL_VALUE(Current_lu_matrix)
#define Current_machine_ids_of_g2_ok_file_qm SPECIAL_VALUE(Current_machine_ids_of_g2_ok_file_qm)
#define Current_message_board_qm SPECIAL_VALUE(Current_message_board_qm)
#define Current_message_serial_number SPECIAL_VALUE(Current_message_serial_number)
#define Current_message_unix_time_qm SPECIAL_VALUE(Current_message_unix_time_qm)
#define Current_minimal_grid_draw_has_seen_one_image_plane_p SPECIAL_VALUE(Current_minimal_grid_draw_has_seen_one_image_plane_p)
#define Current_model_definition_qm SPECIAL_VALUE(Current_model_definition_qm)
#define Current_model_queue_qm SPECIAL_VALUE(Current_model_queue_qm)
#define Current_model_runtime_info_qm SPECIAL_VALUE(Current_model_runtime_info_qm)
#define Current_modularity_problems SPECIAL_VALUE(Current_modularity_problems)
#define Current_modularity_problems_fatal_qm SPECIAL_VALUE(Current_modularity_problems_fatal_qm)
#define Current_module_being_saved SPECIAL_VALUE(Current_module_being_saved)
#define Current_module_data SPECIAL_VALUE(Current_module_data)
#define Current_module_directory_binding_alist SPECIAL_VALUE(Current_module_directory_binding_alist)
#define Current_module_lisp_binary_filename SPECIAL_VALUE(Current_module_lisp_binary_filename)
#define Current_module_pathname_override_binding_alist SPECIAL_VALUE(Current_module_pathname_override_binding_alist)
#define Current_module_qm SPECIAL_VALUE(Current_module_qm)
#define Current_module_source_filename SPECIAL_VALUE(Current_module_source_filename)
#define Current_native_image_plane SPECIAL_VALUE(Current_native_image_plane)
#define Current_native_simple_dialog_handle SPECIAL_VALUE(Current_native_simple_dialog_handle)
#define Current_native_window_qm SPECIAL_VALUE(Current_native_window_qm)
#define Current_network_interface SPECIAL_VALUE(Current_network_interface)
#define Current_new_table SPECIAL_VALUE(Current_new_table)
#define Current_nonterminals SPECIAL_VALUE(Current_nonterminals)
#define Current_painting_action SPECIAL_VALUE(Current_painting_action)
#define Current_pane SPECIAL_VALUE(Current_pane)
#define Current_parse_table SPECIAL_VALUE(Current_parse_table)
#define Current_parsing_context_character SPECIAL_VALUE(Current_parsing_context_character)
#define Current_parsing_context_line SPECIAL_VALUE(Current_parsing_context_line)
#define Current_parsing_context_qm SPECIAL_VALUE(Current_parsing_context_qm)
#define Current_parsing_context_text SPECIAL_VALUE(Current_parsing_context_text)
#define Current_parsing_context_text_length SPECIAL_VALUE(Current_parsing_context_text_length)
#define Current_parsing_contexts SPECIAL_VALUE(Current_parsing_contexts)
#define Current_part_description SPECIAL_VALUE(Current_part_description)
#define Current_plot SPECIAL_VALUE(Current_plot)
#define Current_plot_number SPECIAL_VALUE(Current_plot_number)
#define Current_post_mortem_ring_buffer SPECIAL_VALUE(Current_post_mortem_ring_buffer)
#define Current_post_mortem_ring_buffer_length SPECIAL_VALUE(Current_post_mortem_ring_buffer_length)
#define Current_process_handle SPECIAL_VALUE(Current_process_handle)
#define Current_productions SPECIAL_VALUE(Current_productions)
#define Current_profile_structure_qm SPECIAL_VALUE(Current_profile_structure_qm)
#define Current_projection_function_for_funcall SPECIAL_VALUE(Current_projection_function_for_funcall)
#define Current_read_icp_byte_position SPECIAL_VALUE(Current_read_icp_byte_position)
#define Current_real_time SPECIAL_VALUE(Current_real_time)
#define Current_receiving_resumable_object SPECIAL_VALUE(Current_receiving_resumable_object)
#define Current_region_maximum_x SPECIAL_VALUE(Current_region_maximum_x)
#define Current_region_maximum_y SPECIAL_VALUE(Current_region_maximum_y)
#define Current_region_minimum_x SPECIAL_VALUE(Current_region_minimum_x)
#define Current_region_minimum_y SPECIAL_VALUE(Current_region_minimum_y)
#define Current_remote_procedure_identifier SPECIAL_VALUE(Current_remote_procedure_identifier)
#define Current_remote_search_representation_qm SPECIAL_VALUE(Current_remote_search_representation_qm)
#define Current_resumable_icp_read_task SPECIAL_VALUE(Current_resumable_icp_read_task)
#define Current_return_values_position SPECIAL_VALUE(Current_return_values_position)
#define Current_ri_completion_notification_collection_qm SPECIAL_VALUE(Current_ri_completion_notification_collection_qm)
#define Current_row SPECIAL_VALUE(Current_row)
#define Current_rule_local_name_reference_info SPECIAL_VALUE(Current_rule_local_name_reference_info)
#define Current_saving_context SPECIAL_VALUE(Current_saving_context)
#define Current_saving_context_qm SPECIAL_VALUE(Current_saving_context_qm)
#define Current_schedule_task SPECIAL_VALUE(Current_schedule_task)
#define Current_score_of_best_match_for_eyes SPECIAL_VALUE(Current_score_of_best_match_for_eyes)
#define Current_scratchpad_color_value_list SPECIAL_VALUE(Current_scratchpad_color_value_list)
#define Current_scratchpad_raster SPECIAL_VALUE(Current_scratchpad_raster)
#define Current_scratchpad_raster_depth SPECIAL_VALUE(Current_scratchpad_raster_depth)
#define Current_scratchpad_raster_height SPECIAL_VALUE(Current_scratchpad_raster_height)
#define Current_scratchpad_raster_list SPECIAL_VALUE(Current_scratchpad_raster_list)
#define Current_scratchpad_raster_tiled_p SPECIAL_VALUE(Current_scratchpad_raster_tiled_p)
#define Current_scratchpad_raster_type SPECIAL_VALUE(Current_scratchpad_raster_type)
#define Current_scratchpad_raster_width SPECIAL_VALUE(Current_scratchpad_raster_width)
#define Current_simulation_category SPECIAL_VALUE(Current_simulation_category)
#define Current_simulation_runtime_structure SPECIAL_VALUE(Current_simulation_runtime_structure)
#define Current_slice_size_qm SPECIAL_VALUE(Current_slice_size_qm)
#define Current_slot_value_of_user_slot SPECIAL_VALUE(Current_slot_value_of_user_slot)
#define Current_source_line SPECIAL_VALUE(Current_source_line)
#define Current_source_nupec_synchronization SPECIAL_VALUE(Current_source_nupec_synchronization)
#define Current_standard_icp_object_index_space SPECIAL_VALUE(Current_standard_icp_object_index_space)
#define Current_start_state SPECIAL_VALUE(Current_start_state)
#define Current_state_stack SPECIAL_VALUE(Current_state_stack)
#define Current_statistics_file_pathname_qm SPECIAL_VALUE(Current_statistics_file_pathname_qm)
#define Current_style_if_other_than_default SPECIAL_VALUE(Current_style_if_other_than_default)
#define Current_subcategory_path SPECIAL_VALUE(Current_subcategory_path)
#define Current_subscribe_innermost_class SPECIAL_VALUE(Current_subscribe_innermost_class)
#define Current_subscribe_innermost_item_index SPECIAL_VALUE(Current_subscribe_innermost_item_index)
#define Current_system_being_loaded SPECIAL_VALUE(Current_system_being_loaded)
#define Current_system_dummy_workstation_qm SPECIAL_VALUE(Current_system_dummy_workstation_qm)
#define Current_system_name SPECIAL_VALUE(Current_system_name)
#define Current_system_rpc_icp_socket_qm SPECIAL_VALUE(Current_system_rpc_icp_socket_qm)
#define Current_system_version SPECIAL_VALUE(Current_system_version)
#define Current_t2_dialog_sequence_number SPECIAL_VALUE(Current_t2_dialog_sequence_number)
#define Current_table_updates_task_qm SPECIAL_VALUE(Current_table_updates_task_qm)
#define Current_target_nupec_synchronization SPECIAL_VALUE(Current_target_nupec_synchronization)
#define Current_task_to_run_propagate_all_workspace_changes_to_image_planes SPECIAL_VALUE(Current_task_to_run_propagate_all_workspace_changes_to_image_planes)
#define Current_telewindows_workstation SPECIAL_VALUE(Current_telewindows_workstation)
#define Current_temporary_g2gl_values SPECIAL_VALUE(Current_temporary_g2gl_values)
#define Current_temporary_icp_object_index_space SPECIAL_VALUE(Current_temporary_icp_object_index_space)
#define Current_terminals SPECIAL_VALUE(Current_terminals)
#define Current_text_box_format SPECIAL_VALUE(Current_text_box_format)
#define Current_text_cell_plist SPECIAL_VALUE(Current_text_cell_plist)
#define Current_text_focus_for_eyes_qm SPECIAL_VALUE(Current_text_focus_for_eyes_qm)
#define Current_text_tokenization_state SPECIAL_VALUE(Current_text_tokenization_state)
#define Current_thing_changed SPECIAL_VALUE(Current_thing_changed)
#define Current_thread_index SPECIAL_VALUE(Current_thread_index)
#define Current_token_stack SPECIAL_VALUE(Current_token_stack)
#define Current_tokenizer SPECIAL_VALUE(Current_tokenizer)
#define Current_tracking_subcomponent SPECIAL_VALUE(Current_tracking_subcomponent)
#define Current_tracking_x_in_window SPECIAL_VALUE(Current_tracking_x_in_window)
#define Current_tracking_y_in_window SPECIAL_VALUE(Current_tracking_y_in_window)
#define Current_transform_constituent_array SPECIAL_VALUE(Current_transform_constituent_array)
#define Current_transform_constituent_count SPECIAL_VALUE(Current_transform_constituent_count)
#define Current_trend_chart SPECIAL_VALUE(Current_trend_chart)
#define Current_trend_chart_has_remote_representation_p SPECIAL_VALUE(Current_trend_chart_has_remote_representation_p)
#define Current_twriting_output_type SPECIAL_VALUE(Current_twriting_output_type)
#define Current_ui_client_session SPECIAL_VALUE(Current_ui_client_session)
#define Current_wide_string SPECIAL_VALUE(Current_wide_string)
#define Current_wide_string_list SPECIAL_VALUE(Current_wide_string_list)
#define Current_width_of_formatted_part SPECIAL_VALUE(Current_width_of_formatted_part)
#define Current_window SPECIAL_VALUE(Current_window)
#define Current_workspace_on_image_plane_qm SPECIAL_VALUE(Current_workspace_on_image_plane_qm)
#define Current_workstation SPECIAL_VALUE(Current_workstation)
#define Current_workstation_context SPECIAL_VALUE(Current_workstation_context)
#define Current_workstation_detail_pane SPECIAL_VALUE(Current_workstation_detail_pane)
#define Current_workstation_event SPECIAL_VALUE(Current_workstation_event)
#define Current_workstation_native_window_qm SPECIAL_VALUE(Current_workstation_native_window_qm)
#define Current_workstation_window SPECIAL_VALUE(Current_workstation_window)
#define Current_write_icp_byte_position SPECIAL_VALUE(Current_write_icp_byte_position)
#define Current_x_for_eyes_qm SPECIAL_VALUE(Current_x_for_eyes_qm)
#define Current_x_max_for_stored_raster_qm SPECIAL_VALUE(Current_x_max_for_stored_raster_qm)
#define Current_x_offset_for_stored_raster_qm SPECIAL_VALUE(Current_x_offset_for_stored_raster_qm)
#define Current_x_origin_of_drawing SPECIAL_VALUE(Current_x_origin_of_drawing)
#define Current_x_vector SPECIAL_VALUE(Current_x_vector)
#define Current_xml_structures SPECIAL_VALUE(Current_xml_structures)
#define Current_y_for_eyes_qm SPECIAL_VALUE(Current_y_for_eyes_qm)
#define Current_y_max_for_stored_raster_qm SPECIAL_VALUE(Current_y_max_for_stored_raster_qm)
#define Current_y_offset_for_stored_raster_qm SPECIAL_VALUE(Current_y_offset_for_stored_raster_qm)
#define Current_y_origin_of_drawing SPECIAL_VALUE(Current_y_origin_of_drawing)
#define Currently_active_event_handlers_via_object_configuration SPECIAL_VALUE(Currently_active_event_handlers_via_object_configuration)
#define Currently_automatically_resolving_class_name_conflicts_qm SPECIAL_VALUE(Currently_automatically_resolving_class_name_conflicts_qm)
#define Currently_exposed_workspaces SPECIAL_VALUE(Currently_exposed_workspaces)
#define Currently_jump_out_of_drawing_image_plane_when_empty_rectangle_p SPECIAL_VALUE(Currently_jump_out_of_drawing_image_plane_when_empty_rectangle_p)
#define Currently_loading_modules_qm SPECIAL_VALUE(Currently_loading_modules_qm)
#define Currently_posting_message_on_logbook_p SPECIAL_VALUE(Currently_posting_message_on_logbook_p)
#define Currently_supressing_part_highlighting SPECIAL_VALUE(Currently_supressing_part_highlighting)
#define Currently_tracking_subcategory_path_max SPECIAL_VALUE(Currently_tracking_subcategory_path_max)
#define Currently_within_make_transient_instruction_p SPECIAL_VALUE(Currently_within_make_transient_instruction_p)
#define Currently_working_on_drawing_p SPECIAL_VALUE(Currently_working_on_drawing_p)
#define Currently_working_on_drawing_workspace SPECIAL_VALUE(Currently_working_on_drawing_workspace)
#define Custom_dialog_cons_counter SPECIAL_VALUE(Custom_dialog_cons_counter)
#define Cvs_command_initial_timeout SPECIAL_VALUE(Cvs_command_initial_timeout)
#define Cvs_command_timed_out_p SPECIAL_VALUE(Cvs_command_timed_out_p)
#define Daily_countdown SPECIAL_VALUE(Daily_countdown)
#define Data_point_first_x SPECIAL_VALUE(Data_point_first_x)
#define Data_point_first_y SPECIAL_VALUE(Data_point_first_y)
#define Data_point_index SPECIAL_VALUE(Data_point_index)
#define Data_point_indicator SPECIAL_VALUE(Data_point_indicator)
#define Data_point_indicator_projection_function SPECIAL_VALUE(Data_point_indicator_projection_function)
#define Data_point_last_x SPECIAL_VALUE(Data_point_last_x)
#define Data_point_last_y SPECIAL_VALUE(Data_point_last_y)
#define Data_point_show_connecting_line SPECIAL_VALUE(Data_point_show_connecting_line)
#define Data_point_show_indicator SPECIAL_VALUE(Data_point_show_indicator)
#define Data_point_tuple_1 SPECIAL_VALUE(Data_point_tuple_1)
#define Data_point_tuple_2 SPECIAL_VALUE(Data_point_tuple_2)
#define Data_point_tuple_valid_qm SPECIAL_VALUE(Data_point_tuple_valid_qm)
#define Data_point_value SPECIAL_VALUE(Data_point_value)
#define Data_point_value_and_collection_time_interned_list SPECIAL_VALUE(Data_point_value_and_collection_time_interned_list)
#define Data_point_value_interned_list SPECIAL_VALUE(Data_point_value_interned_list)
#define Data_point_x SPECIAL_VALUE(Data_point_x)
#define Data_point_y SPECIAL_VALUE(Data_point_y)
#define Data_series SPECIAL_VALUE(Data_series)
#define Data_series_connect_first_and_last_point SPECIAL_VALUE(Data_series_connect_first_and_last_point)
#define Data_series_data_cache_1_qm SPECIAL_VALUE(Data_series_data_cache_1_qm)
#define Data_series_data_cache_2_qm SPECIAL_VALUE(Data_series_data_cache_2_qm)
#define Data_series_failed_to_compile SPECIAL_VALUE(Data_series_failed_to_compile)
#define Data_series_generator_info_1 SPECIAL_VALUE(Data_series_generator_info_1)
#define Data_series_generator_info_2 SPECIAL_VALUE(Data_series_generator_info_2)
#define Data_series_illustration_kind SPECIAL_VALUE(Data_series_illustration_kind)
#define Data_series_index SPECIAL_VALUE(Data_series_index)
#define Data_series_info_1 SPECIAL_VALUE(Data_series_info_1)
#define Data_series_info_2 SPECIAL_VALUE(Data_series_info_2)
#define Data_series_source_kind SPECIAL_VALUE(Data_series_source_kind)
#define Data_series_subparts SPECIAL_VALUE(Data_series_subparts)
#define Data_server_count SPECIAL_VALUE(Data_server_count)
#define Data_server_error_code_alist SPECIAL_VALUE(Data_server_error_code_alist)
#define Data_server_parameters SPECIAL_VALUE(Data_server_parameters)
#define Data_server_pretty_name_alist SPECIAL_VALUE(Data_server_pretty_name_alist)
#define Date_format_count SPECIAL_VALUE(Date_format_count)
#define Datum_type SPECIAL_VALUE(Datum_type)
#define Day_of_the_week_names SPECIAL_VALUE(Day_of_the_week_names)
#define Deadman_switch_time_interval SPECIAL_VALUE(Deadman_switch_time_interval)
#define Debug_1 SPECIAL_VALUE(Debug_1)
#define Debug_10 SPECIAL_VALUE(Debug_10)
#define Debug_11 SPECIAL_VALUE(Debug_11)
#define Debug_12 SPECIAL_VALUE(Debug_12)
#define Debug_2 SPECIAL_VALUE(Debug_2)
#define Debug_3 SPECIAL_VALUE(Debug_3)
#define Debug_4 SPECIAL_VALUE(Debug_4)
#define Debug_5 SPECIAL_VALUE(Debug_5)
#define Debug_6 SPECIAL_VALUE(Debug_6)
#define Debug_7 SPECIAL_VALUE(Debug_7)
#define Debug_8 SPECIAL_VALUE(Debug_8)
#define Debug_9 SPECIAL_VALUE(Debug_9)
#define Debug_out_of_synch SPECIAL_VALUE(Debug_out_of_synch)
#define Debug_print_byte_code_pc_p SPECIAL_VALUE(Debug_print_byte_code_pc_p)
#define Debugging_consing SPECIAL_VALUE(Debugging_consing)
#define Debugging_name_index SPECIAL_VALUE(Debugging_name_index)
#define Debugging_parameters SPECIAL_VALUE(Debugging_parameters)
#define Debugging_reset SPECIAL_VALUE(Debugging_reset)
#define Decache_attribute_description_lists_of_interned_lists_function SPECIAL_VALUE(Decache_attribute_description_lists_of_interned_lists_function)
#define Decache_occurred_since_last_update_qm SPECIAL_VALUE(Decache_occurred_since_last_update_qm)
#define Default_accept_timeout SPECIAL_VALUE(Default_accept_timeout)
#define Default_axis_data_series_instance SPECIAL_VALUE(Default_axis_data_series_instance)
#define Default_duration_for_data_point SPECIAL_VALUE(Default_duration_for_data_point)
#define Default_entity_line_drawing_description_template SPECIAL_VALUE(Default_entity_line_drawing_description_template)
#define Default_fin_length SPECIAL_VALUE(Default_fin_length)
#define Default_float_to_text_format SPECIAL_VALUE(Default_float_to_text_format)
#define Default_format_structure SPECIAL_VALUE(Default_format_structure)
#define Default_g2_hangul_star_pathname SPECIAL_VALUE(Default_g2_hangul_star_pathname)
#define Default_g2_init_pathname SPECIAL_VALUE(Default_g2_init_pathname)
#define Default_g2_kanji_star_pathname SPECIAL_VALUE(Default_g2_kanji_star_pathname)
#define Default_g2_kb_pathname SPECIAL_VALUE(Default_g2_kb_pathname)
#define Default_g2_minm_star_pathname SPECIAL_VALUE(Default_g2_minm_star_pathname)
#define Default_g2_module_map_pathname SPECIAL_VALUE(Default_g2_module_map_pathname)
#define Default_g2_ok_pathname SPECIAL_VALUE(Default_g2_ok_pathname)
#define Default_g2v11_ok_pathname SPECIAL_VALUE(Default_g2v11_ok_pathname)
#define Default_g2v12_ok_pathname SPECIAL_VALUE(Default_g2v12_ok_pathname)
#define Default_g2v51_ok_pathname SPECIAL_VALUE(Default_g2v51_ok_pathname)
#define Default_g2v5_ok_pathname SPECIAL_VALUE(Default_g2v5_ok_pathname)
#define Default_g2v6_ok_pathname SPECIAL_VALUE(Default_g2v6_ok_pathname)
#define Default_g2v7_ok_pathname SPECIAL_VALUE(Default_g2v7_ok_pathname)
#define Default_g2v83_ok_pathname SPECIAL_VALUE(Default_g2v83_ok_pathname)
#define Default_g2v8_ok_pathname SPECIAL_VALUE(Default_g2v8_ok_pathname)
#define Default_g2v9_ok_pathname SPECIAL_VALUE(Default_g2v9_ok_pathname)
#define Default_graph_line_color_value SPECIAL_VALUE(Default_graph_line_color_value)
#define Default_icon_slot_group SPECIAL_VALUE(Default_icon_slot_group)
#define Default_junction_class_description SPECIAL_VALUE(Default_junction_class_description)
#define Default_kb_pathname_qm SPECIAL_VALUE(Default_kb_pathname_qm)
#define Default_language SPECIAL_VALUE(Default_language)
#define Default_maximum_icon_bitmap_memory SPECIAL_VALUE(Default_maximum_icon_bitmap_memory)
#define Default_maximum_icon_bitmaps SPECIAL_VALUE(Default_maximum_icon_bitmaps)
#define Default_most_recent_bandwidth_per_timeslice SPECIAL_VALUE(Default_most_recent_bandwidth_per_timeslice)
#define Default_size_of_spacial_index SPECIAL_VALUE(Default_size_of_spacial_index)
#define Default_stub_length SPECIAL_VALUE(Default_stub_length)
#define Default_text_conversion_style SPECIAL_VALUE(Default_text_conversion_style)
#define Default_tw_hangul_star_pathname SPECIAL_VALUE(Default_tw_hangul_star_pathname)
#define Default_tw_kanji_star_pathname SPECIAL_VALUE(Default_tw_kanji_star_pathname)
#define Default_tw_minm_star_pathname SPECIAL_VALUE(Default_tw_minm_star_pathname)
#define Default_tw_ok_pathname SPECIAL_VALUE(Default_tw_ok_pathname)
#define Default_twv11_ok_pathname SPECIAL_VALUE(Default_twv11_ok_pathname)
#define Default_twv12_ok_pathname SPECIAL_VALUE(Default_twv12_ok_pathname)
#define Default_twv5_ok_pathname SPECIAL_VALUE(Default_twv5_ok_pathname)
#define Default_twv6_ok_pathname SPECIAL_VALUE(Default_twv6_ok_pathname)
#define Default_twv7_ok_pathname SPECIAL_VALUE(Default_twv7_ok_pathname)
#define Default_twv8_ok_pathname SPECIAL_VALUE(Default_twv8_ok_pathname)
#define Default_twv9_ok_pathname SPECIAL_VALUE(Default_twv9_ok_pathname)
#define Defaults_namestring_for_directory_of_names_qm SPECIAL_VALUE(Defaults_namestring_for_directory_of_names_qm)
#define Defer_consistency_analysis_qm SPECIAL_VALUE(Defer_consistency_analysis_qm)
#define Defer_notifications_qm SPECIAL_VALUE(Defer_notifications_qm)
#define Deferred_class_definitions_alist SPECIAL_VALUE(Deferred_class_definitions_alist)
#define Deferred_errors_for_class_export_qm SPECIAL_VALUE(Deferred_errors_for_class_export_qm)
#define Deferred_update_count SPECIAL_VALUE(Deferred_update_count)
#define Deferring_errors_for_class_export_p SPECIAL_VALUE(Deferring_errors_for_class_export_p)
#define Defined_evaluation_datum_types SPECIAL_VALUE(Defined_evaluation_datum_types)
#define Defined_evaluation_value_types SPECIAL_VALUE(Defined_evaluation_value_types)
#define Definition_being_analyzed_for_savability SPECIAL_VALUE(Definition_being_analyzed_for_savability)
#define Definition_class_description SPECIAL_VALUE(Definition_class_description)
#define Definition_with_subclass_or_instance_in_kb_hierarchy SPECIAL_VALUE(Definition_with_subclass_or_instance_in_kb_hierarchy)
#define Definitions_for_saving SPECIAL_VALUE(Definitions_for_saving)
#define Definitions_in_module SPECIAL_VALUE(Definitions_in_module)
#define Definitions_in_module_to_go SPECIAL_VALUE(Definitions_in_module_to_go)
#define Definitions_not_required SPECIAL_VALUE(Definitions_not_required)
#define Definitions_read_in_this_module SPECIAL_VALUE(Definitions_read_in_this_module)
#define Definitions_that_have_been_visited SPECIAL_VALUE(Definitions_that_have_been_visited)
#define Defun_incremental_compile_time_registry SPECIAL_VALUE(Defun_incremental_compile_time_registry)
#define Defun_incremental_runtime_registry SPECIAL_VALUE(Defun_incremental_runtime_registry)
#define Defvar_for_informational_tests_for_mhd SPECIAL_VALUE(Defvar_for_informational_tests_for_mhd)
#define Delay_item_array_initializations_p SPECIAL_VALUE(Delay_item_array_initializations_p)
#define Delayed_item_array_initializations SPECIAL_VALUE(Delayed_item_array_initializations)
#define Delete_as_item_referring_to_name_qm SPECIAL_VALUE(Delete_as_item_referring_to_name_qm)
#define Delete_compiled_kb_source_p SPECIAL_VALUE(Delete_compiled_kb_source_p)
#define Delete_connections_without_leaving_stubs_qm SPECIAL_VALUE(Delete_connections_without_leaving_stubs_qm)
#define Delete_corresponding_object_qm SPECIAL_VALUE(Delete_corresponding_object_qm)
#define Delete_files_after_external_diff_p SPECIAL_VALUE(Delete_files_after_external_diff_p)
#define Delete_old_elements_from_arrays_and_lists SPECIAL_VALUE(Delete_old_elements_from_arrays_and_lists)
#define Deleting_ui_client_interfaces_for_clear_kb SPECIAL_VALUE(Deleting_ui_client_interfaces_for_clear_kb)
#define Denotation_error_list SPECIAL_VALUE(Denotation_error_list)
#define Denotation_size_vector SPECIAL_VALUE(Denotation_size_vector)
#define Dependent_frame_class_description SPECIAL_VALUE(Dependent_frame_class_description)
#define Depth_of_post_mortem_checkpoint_reporting SPECIAL_VALUE(Depth_of_post_mortem_checkpoint_reporting)
#define Deregister_and_register_item_p SPECIAL_VALUE(Deregister_and_register_item_p)
#define Deregister_but_do_not_remove_from_table_p SPECIAL_VALUE(Deregister_but_do_not_remove_from_table_p)
#define Deregister_corresponding_object_qm SPECIAL_VALUE(Deregister_corresponding_object_qm)
#define Derived_icp_input_port SPECIAL_VALUE(Derived_icp_input_port)
#define Derived_icp_output_port SPECIAL_VALUE(Derived_icp_output_port)
#define Designation_marker SPECIAL_VALUE(Designation_marker)
#define Designations_from_explicit_iteration_forms SPECIAL_VALUE(Designations_from_explicit_iteration_forms)
#define Designations_in_rule SPECIAL_VALUE(Designations_in_rule)
#define Desired_distance_between_fins SPECIAL_VALUE(Desired_distance_between_fins)
#define Desired_distance_between_fins_on_link SPECIAL_VALUE(Desired_distance_between_fins_on_link)
#define Desired_high_value_for_horizontal_axis SPECIAL_VALUE(Desired_high_value_for_horizontal_axis)
#define Desired_high_value_for_vertical_axis SPECIAL_VALUE(Desired_high_value_for_vertical_axis)
#define Desired_low_value_for_horizontal_axis SPECIAL_VALUE(Desired_low_value_for_horizontal_axis)
#define Desired_low_value_for_vertical_axis SPECIAL_VALUE(Desired_low_value_for_vertical_axis)
#define Desired_parent_of_native_window_qm SPECIAL_VALUE(Desired_parent_of_native_window_qm)
#define Destination_for_symbol_with_preserved_cells SPECIAL_VALUE(Destination_for_symbol_with_preserved_cells)
#define Detail_pane_spot_count SPECIAL_VALUE(Detail_pane_spot_count)
#define Development_world_save_p SPECIAL_VALUE(Development_world_save_p)
#define Dial_class_description SPECIAL_VALUE(Dial_class_description)
#define Dial_spot_count SPECIAL_VALUE(Dial_spot_count)
#define Dialog_button_class_description SPECIAL_VALUE(Dialog_button_class_description)
#define Dialog_component_count SPECIAL_VALUE(Dialog_component_count)
#define Dialog_errors_structure_count SPECIAL_VALUE(Dialog_errors_structure_count)
#define Dialog_state_count SPECIAL_VALUE(Dialog_state_count)
#define Dialog_view_count SPECIAL_VALUE(Dialog_view_count)
#define Dialogs_error_handling SPECIAL_VALUE(Dialogs_error_handling)
#define Digital_clock_class_description SPECIAL_VALUE(Digital_clock_class_description)
#define Digits_of_extremal_fixnum_as_string SPECIAL_VALUE(Digits_of_extremal_fixnum_as_string)
#define Digits_of_largest_float_as_string SPECIAL_VALUE(Digits_of_largest_float_as_string)
#define Digits_of_most_negative_fixnum_as_string SPECIAL_VALUE(Digits_of_most_negative_fixnum_as_string)
#define Digits_of_most_positive_fixnum_as_string SPECIAL_VALUE(Digits_of_most_positive_fixnum_as_string)
#define Digits_of_smallest_normalized_float_as_string SPECIAL_VALUE(Digits_of_smallest_normalized_float_as_string)
#define Directory_nil SPECIAL_VALUE(Directory_nil)
#define Directory_of_built_in_menu_choices SPECIAL_VALUE(Directory_of_built_in_menu_choices)
#define Disable_parameter_strings_for_internal_proprietary_procedures SPECIAL_VALUE(Disable_parameter_strings_for_internal_proprietary_procedures)
#define Disable_resumability SPECIAL_VALUE(Disable_resumability)
#define Disable_stack_error SPECIAL_VALUE(Disable_stack_error)
#define Disable_subworkspace_connection_posts SPECIAL_VALUE(Disable_subworkspace_connection_posts)
#define Disable_tracing_and_breakpoints_warning SPECIAL_VALUE(Disable_tracing_and_breakpoints_warning)
#define Disable_update_button SPECIAL_VALUE(Disable_update_button)
#define Disassemble_enabled_qm SPECIAL_VALUE(Disassemble_enabled_qm)
#define Display_pane_count SPECIAL_VALUE(Display_pane_count)
#define Distance_to_snap_points_together_in_view_pad SPECIAL_VALUE(Distance_to_snap_points_together_in_view_pad)
#define Distribute_selection_command_operations SPECIAL_VALUE(Distribute_selection_command_operations)
#define Do_backpatching SPECIAL_VALUE(Do_backpatching)
#define Do_circularity_check_walking_through_conses_p SPECIAL_VALUE(Do_circularity_check_walking_through_conses_p)
#define Do_circularity_check_walking_through_simple_vectors_p SPECIAL_VALUE(Do_circularity_check_walking_through_simple_vectors_p)
#define Do_g2_init_file_qm SPECIAL_VALUE(Do_g2_init_file_qm)
#define Do_icp_flow_control_qm SPECIAL_VALUE(Do_icp_flow_control_qm)
#define Do_not_allow_user_interactions_during_kb_load_qm SPECIAL_VALUE(Do_not_allow_user_interactions_during_kb_load_qm)
#define Do_not_error_in_x11_create_pixmap_on_failed_allocation SPECIAL_VALUE(Do_not_error_in_x11_create_pixmap_on_failed_allocation)
#define Do_not_initialize_g2_array_elements_p SPECIAL_VALUE(Do_not_initialize_g2_array_elements_p)
#define Do_not_initialize_specializations SPECIAL_VALUE(Do_not_initialize_specializations)
#define Do_not_invoke_rules_for_user_icon_movement_qm SPECIAL_VALUE(Do_not_invoke_rules_for_user_icon_movement_qm)
#define Do_not_load_modules_p SPECIAL_VALUE(Do_not_load_modules_p)
#define Do_not_note_permanent_changes_p SPECIAL_VALUE(Do_not_note_permanent_changes_p)
#define Do_not_notify_user_during_kb_load_qm SPECIAL_VALUE(Do_not_notify_user_during_kb_load_qm)
#define Do_not_reclaim_runs_while_inactive_entries SPECIAL_VALUE(Do_not_reclaim_runs_while_inactive_entries)
#define Do_not_restore_image_planes_qm SPECIAL_VALUE(Do_not_restore_image_planes_qm)
#define Do_not_show_conflicts_during_kb_load_qm SPECIAL_VALUE(Do_not_show_conflicts_during_kb_load_qm)
#define Do_not_stop_search_once_found_qm SPECIAL_VALUE(Do_not_stop_search_once_found_qm)
#define Do_not_update_file_progress_display_qm SPECIAL_VALUE(Do_not_update_file_progress_display_qm)
#define Do_not_update_frame_authors_qm SPECIAL_VALUE(Do_not_update_frame_authors_qm)
#define Do_not_update_selection_highlights SPECIAL_VALUE(Do_not_update_selection_highlights)
#define Do_not_update_simulated_value_qm SPECIAL_VALUE(Do_not_update_simulated_value_qm)
#define Doing_g2_init_file_p SPECIAL_VALUE(Doing_g2_init_file_p)
#define Doing_g2_init_kb_p SPECIAL_VALUE(Doing_g2_init_kb_p)
#define Doing_long_operation_with_notification_qm SPECIAL_VALUE(Doing_long_operation_with_notification_qm)
#define Doing_password_change_p SPECIAL_VALUE(Doing_password_change_p)
#define Dont_backward_chain_in_sim_eval_qm SPECIAL_VALUE(Dont_backward_chain_in_sim_eval_qm)
#define Dont_cerror_for_slot_changes_while_on_window_qm SPECIAL_VALUE(Dont_cerror_for_slot_changes_while_on_window_qm)
#define Dont_include_offset_for_end_position_qm SPECIAL_VALUE(Dont_include_offset_for_end_position_qm)
#define Dont_load_if_definitions_have_changed_p SPECIAL_VALUE(Dont_load_if_definitions_have_changed_p)
#define Dont_proceed_to_next_variable_qm SPECIAL_VALUE(Dont_proceed_to_next_variable_qm)
#define Drag_handle_state_count SPECIAL_VALUE(Drag_handle_state_count)
#define Dragging_cons_counter SPECIAL_VALUE(Dragging_cons_counter)
#define Dragging_state_count SPECIAL_VALUE(Dragging_state_count)
#define Drawing_is_locked_qm SPECIAL_VALUE(Drawing_is_locked_qm)
#define Drawing_on_window SPECIAL_VALUE(Drawing_on_window)
#define Drawing_parameters SPECIAL_VALUE(Drawing_parameters)
#define Drawing_state_for_project_paper SPECIAL_VALUE(Drawing_state_for_project_paper)
#define Drawing_task_count SPECIAL_VALUE(Drawing_task_count)
#define Drawing_to_printer_p SPECIAL_VALUE(Drawing_to_printer_p)
#define Dummy_evaluators_list SPECIAL_VALUE(Dummy_evaluators_list)
#define Dummy_place_for_chestnut_internals SPECIAL_VALUE(Dummy_place_for_chestnut_internals)
#define Duplicate_local_names_already_reported SPECIAL_VALUE(Duplicate_local_names_already_reported)
#define Duplicates_check_hash SPECIAL_VALUE(Duplicates_check_hash)
#define Duration_cv_count SPECIAL_VALUE(Duration_cv_count)
#define During_ffi_call_qm SPECIAL_VALUE(During_ffi_call_qm)
#define Dynamic_dialog_count SPECIAL_VALUE(Dynamic_dialog_count)
#define Dynamic_menus_modification_tick SPECIAL_VALUE(Dynamic_menus_modification_tick)
#define Dynamic_rule_display_hash_table SPECIAL_VALUE(Dynamic_rule_display_hash_table)
#define Dynamic_workspace_associated_structure_count SPECIAL_VALUE(Dynamic_workspace_associated_structure_count)
#define Echo_dialog_spec_p SPECIAL_VALUE(Echo_dialog_spec_p)
#define Edit_box_change_count SPECIAL_VALUE(Edit_box_change_count)
#define Edit_box_class_description SPECIAL_VALUE(Edit_box_class_description)
#define Edit_box_spot_count SPECIAL_VALUE(Edit_box_spot_count)
#define Edit_cache_count SPECIAL_VALUE(Edit_cache_count)
#define Edit_menu_state_count SPECIAL_VALUE(Edit_menu_state_count)
#define Edit_state_count SPECIAL_VALUE(Edit_state_count)
#define Edit_states SPECIAL_VALUE(Edit_states)
#define Edit_type_alias_mapping SPECIAL_VALUE(Edit_type_alias_mapping)
#define Editing_context SPECIAL_VALUE(Editing_context)
#define Editing_new_table SPECIAL_VALUE(Editing_new_table)
#define Editor_background_color_override_qm SPECIAL_VALUE(Editor_background_color_override_qm)
#define Editor_caption_text_override_qm SPECIAL_VALUE(Editor_caption_text_override_qm)
#define Editor_font_size_override_qm SPECIAL_VALUE(Editor_font_size_override_qm)
#define Editor_frame_style_override_qm SPECIAL_VALUE(Editor_frame_style_override_qm)
#define Editor_initial_editor_height_override_qm SPECIAL_VALUE(Editor_initial_editor_height_override_qm)
#define Editor_parameters SPECIAL_VALUE(Editor_parameters)
#define Editor_prompt_filter_qm SPECIAL_VALUE(Editor_prompt_filter_qm)
#define Editor_scroll_decision_override_qm SPECIAL_VALUE(Editor_scroll_decision_override_qm)
#define Editor_specific_natural_language_override_qm SPECIAL_VALUE(Editor_specific_natural_language_override_qm)
#define Editor_text_color_override_qm SPECIAL_VALUE(Editor_text_color_override_qm)
#define Editor_toolbar_user_callback SPECIAL_VALUE(Editor_toolbar_user_callback)
#define Editor_window_handle SPECIAL_VALUE(Editor_window_handle)
#define Effectively_infinite_region SPECIAL_VALUE(Effectively_infinite_region)
#define Element_of_foreign_linking_info_count SPECIAL_VALUE(Element_of_foreign_linking_info_count)
#define Elevator_of_scroll_bar_spot_count SPECIAL_VALUE(Elevator_of_scroll_bar_spot_count)
#define Elevator_shaft_spot_count SPECIAL_VALUE(Elevator_shaft_spot_count)
#define Elevator_state_count SPECIAL_VALUE(Elevator_state_count)
#define Email_abort_message_sent_p SPECIAL_VALUE(Email_abort_message_sent_p)
#define Embedded_fuzzy_conditionals_list SPECIAL_VALUE(Embedded_fuzzy_conditionals_list)
#define Emit_postscript_line_length SPECIAL_VALUE(Emit_postscript_line_length)
#define Enable_click_to_edit_kludge SPECIAL_VALUE(Enable_click_to_edit_kludge)
#define Enable_loading_compiled_kbs_p SPECIAL_VALUE(Enable_loading_compiled_kbs_p)
#define Enable_native_fonts_qm SPECIAL_VALUE(Enable_native_fonts_qm)
#define Enable_running_compiled_code_p SPECIAL_VALUE(Enable_running_compiled_code_p)
#define Enable_saving_compiled_kbs_p SPECIAL_VALUE(Enable_saving_compiled_kbs_p)
#define Enclosing_form_will_wrap SPECIAL_VALUE(Enclosing_form_will_wrap)
#define Ensure_expanded_instruction_macros_has_run_p SPECIAL_VALUE(Ensure_expanded_instruction_macros_has_run_p)
#define Entire_focus_menu_spot_count SPECIAL_VALUE(Entire_focus_menu_spot_count)
#define Entire_g2_window_spot_count SPECIAL_VALUE(Entire_g2_window_spot_count)
#define Entire_menu_spot_count SPECIAL_VALUE(Entire_menu_spot_count)
#define Entities_or_triples_found_in_search SPECIAL_VALUE(Entities_or_triples_found_in_search)
#define Entities_to_be_excluded_qm SPECIAL_VALUE(Entities_to_be_excluded_qm)
#define Entity_class_description SPECIAL_VALUE(Entity_class_description)
#define Entity_cons_counter SPECIAL_VALUE(Entity_cons_counter)
#define Entity_height_in_ws SPECIAL_VALUE(Entity_height_in_ws)
#define Entity_width_in_ws SPECIAL_VALUE(Entity_width_in_ws)
#define Eq_hash_table_count SPECIAL_VALUE(Eq_hash_table_count)
#define Erase_dateline SPECIAL_VALUE(Erase_dateline)
#define Erase_instead_qm SPECIAL_VALUE(Erase_instead_qm)
#define Error_code_count SPECIAL_VALUE(Error_code_count)
#define Error_of_ok_file_reader_qm SPECIAL_VALUE(Error_of_ok_file_reader_qm)
#define Error_within_error_p SPECIAL_VALUE(Error_within_error_p)
#define Eval_cons_counter SPECIAL_VALUE(Eval_cons_counter)
#define Evaluating_simulator_procedure_qm SPECIAL_VALUE(Evaluating_simulator_procedure_qm)
#define Evaluation_value_indentation_depth SPECIAL_VALUE(Evaluation_value_indentation_depth)
#define Evaluation_value_writing_target_length_qm SPECIAL_VALUE(Evaluation_value_writing_target_length_qm)
#define Evaluator_slot_info_count SPECIAL_VALUE(Evaluator_slot_info_count)
#define Event_detector_count SPECIAL_VALUE(Event_detector_count)
#define Event_handler_args SPECIAL_VALUE(Event_handler_args)
#define Exact_class_names_for_menu_restrictions SPECIAL_VALUE(Exact_class_names_for_menu_restrictions)
#define Exclude_secondary_attributes SPECIAL_VALUE(Exclude_secondary_attributes)
#define Executing_change_item_color_instruction_p SPECIAL_VALUE(Executing_change_item_color_instruction_p)
#define Execution_time_stack SPECIAL_VALUE(Execution_time_stack)
#define Existence_classes_already_checked SPECIAL_VALUE(Existence_classes_already_checked)
#define Expanded_bindings_forms SPECIAL_VALUE(Expanded_bindings_forms)
#define Expanded_check_timeout_form SPECIAL_VALUE(Expanded_check_timeout_form)
#define Expanded_default_clause_form SPECIAL_VALUE(Expanded_default_clause_form)
#define Expanded_exit_form SPECIAL_VALUE(Expanded_exit_form)
#define Expanded_exit_stack_eval_major_form SPECIAL_VALUE(Expanded_exit_stack_eval_major_form)
#define Expanded_exit_stack_eval_minor_form SPECIAL_VALUE(Expanded_exit_stack_eval_minor_form)
#define Expanded_return_values_form SPECIAL_VALUE(Expanded_return_values_form)
#define Explanation_table_class_description SPECIAL_VALUE(Explanation_table_class_description)
#define Explanation_variables SPECIAL_VALUE(Explanation_variables)
#define Explicit_branch_destination SPECIAL_VALUE(Explicit_branch_destination)
#define Explicit_dragger_x_in_window_qm SPECIAL_VALUE(Explicit_dragger_x_in_window_qm)
#define Explicit_dragger_y_in_window_qm SPECIAL_VALUE(Explicit_dragger_y_in_window_qm)
#define Expression_bound_local_names SPECIAL_VALUE(Expression_bound_local_names)
#define Expression_cell_index SPECIAL_VALUE(Expression_cell_index)
#define Expression_for_compilation_count SPECIAL_VALUE(Expression_for_compilation_count)
#define Expression_list_indicator SPECIAL_VALUE(Expression_list_indicator)
#define Expression_source_text SPECIAL_VALUE(Expression_source_text)
#define Expressions_to_display_slot_description SPECIAL_VALUE(Expressions_to_display_slot_description)
#define External_class_info_count SPECIAL_VALUE(External_class_info_count)
#define External_diff_options_qm SPECIAL_VALUE(External_diff_options_qm)
#define External_diff_program_qm SPECIAL_VALUE(External_diff_program_qm)
#define External_method_info_count SPECIAL_VALUE(External_method_info_count)
#define External_set_pointers_count SPECIAL_VALUE(External_set_pointers_count)
#define External_simulation_definition_class_description SPECIAL_VALUE(External_simulation_definition_class_description)
#define External_simulation_object_count SPECIAL_VALUE(External_simulation_object_count)
#define Externaldefinitions_fixups SPECIAL_VALUE(Externaldefinitions_fixups)
#define Extra_time_for_drawing SPECIAL_VALUE(Extra_time_for_drawing)
#define Extreme_bottom_edge_so_far SPECIAL_VALUE(Extreme_bottom_edge_so_far)
#define Extreme_left_edge_so_far SPECIAL_VALUE(Extreme_left_edge_so_far)
#define Extreme_right_edge_so_far SPECIAL_VALUE(Extreme_right_edge_so_far)
#define Extreme_top_edge_so_far SPECIAL_VALUE(Extreme_top_edge_so_far)
#define Extremum_cache_count SPECIAL_VALUE(Extremum_cache_count)
#define Failure_marker SPECIAL_VALUE(Failure_marker)
#define Fake_attribute SPECIAL_VALUE(Fake_attribute)
#define Fasl_extension SPECIAL_VALUE(Fasl_extension)
#define Fatal_focus_error_info_for_all_compilations SPECIAL_VALUE(Fatal_focus_error_info_for_all_compilations)
#define Fatal_focus_error_info_qm SPECIAL_VALUE(Fatal_focus_error_info_qm)
#define Feature_blt SPECIAL_VALUE(Feature_blt)
#define Ff_connect_finalized SPECIAL_VALUE(Ff_connect_finalized)
#define File_format_version_of_g2_ok_file_qm SPECIAL_VALUE(File_format_version_of_g2_ok_file_qm)
#define File_punctuation_mark_grammar_rules SPECIAL_VALUE(File_punctuation_mark_grammar_rules)
#define File_system_directory_search_cache SPECIAL_VALUE(File_system_directory_search_cache)
#define File_system_directory_search_cache_active_p SPECIAL_VALUE(File_system_directory_search_cache_active_p)
#define File_system_directory_search_cache_wildcard_string SPECIAL_VALUE(File_system_directory_search_cache_wildcard_string)
#define File_system_for_interception_qm SPECIAL_VALUE(File_system_for_interception_qm)
#define File_system_slot_description SPECIAL_VALUE(File_system_slot_description)
#define File_template_instance_counter SPECIAL_VALUE(File_template_instance_counter)
#define Filename_of_module_being_loaded_qm SPECIAL_VALUE(Filename_of_module_being_loaded_qm)
#define Filename_parser_information_count SPECIAL_VALUE(Filename_parser_information_count)
#define Filename_special_character_registry SPECIAL_VALUE(Filename_special_character_registry)
#define Fill_pointer_for_current_gensym_string SPECIAL_VALUE(Fill_pointer_for_current_gensym_string)
#define Fill_pointer_for_current_wide_string SPECIAL_VALUE(Fill_pointer_for_current_wide_string)
#define Fill_pointer_for_match_pattern_for_inspect_binding_vector SPECIAL_VALUE(Fill_pointer_for_match_pattern_for_inspect_binding_vector)
#define Filter_cons_counter SPECIAL_VALUE(Filter_cons_counter)
#define Finding_object_near_mouse SPECIAL_VALUE(Finding_object_near_mouse)
#define Finish_current_kb_save_failure SPECIAL_VALUE(Finish_current_kb_save_failure)
#define Finished_storing_in_plot_data_1_qm SPECIAL_VALUE(Finished_storing_in_plot_data_1_qm)
#define First_kb_in_group_read_in_yet_qm SPECIAL_VALUE(First_kb_in_group_read_in_yet_qm)
#define First_string_in_pool_group SPECIAL_VALUE(First_string_in_pool_group)
#define First_subexpression_node_for_reclaiming_qm SPECIAL_VALUE(First_subexpression_node_for_reclaiming_qm)
#define Fixnum_maximum_y_value SPECIAL_VALUE(Fixnum_maximum_y_value)
#define Fixnum_minimum_y_value SPECIAL_VALUE(Fixnum_minimum_y_value)
#define Fixnum_time_at_start_of_current_long_notification SPECIAL_VALUE(Fixnum_time_at_start_of_current_long_notification)
#define Fixnum_time_interval_for_one_second SPECIAL_VALUE(Fixnum_time_interval_for_one_second)
#define Fixnum_time_of_last_g2_tick SPECIAL_VALUE(Fixnum_time_of_last_g2_tick)
#define Fixnum_time_of_last_real_time_tick SPECIAL_VALUE(Fixnum_time_of_last_real_time_tick)
#define Fixnum_time_of_last_xsync SPECIAL_VALUE(Fixnum_time_of_last_xsync)
#define Fixnum_time_units_of_sleep_this_clock_tick SPECIAL_VALUE(Fixnum_time_units_of_sleep_this_clock_tick)
#define Fixnum_time_until_g2_time_tick SPECIAL_VALUE(Fixnum_time_until_g2_time_tick)
#define Fixup_authors_to_skip SPECIAL_VALUE(Fixup_authors_to_skip)
#define Flattened_menu_maximum_remaining_elements SPECIAL_VALUE(Flattened_menu_maximum_remaining_elements)
#define Flattened_menu_reverse SPECIAL_VALUE(Flattened_menu_reverse)
#define Float_array_class_description SPECIAL_VALUE(Float_array_class_description)
#define Float_array_cons_counter SPECIAL_VALUE(Float_array_cons_counter)
#define Float_contagion_stack_operators SPECIAL_VALUE(Float_contagion_stack_operators)
#define Float_errors_are_possible SPECIAL_VALUE(Float_errors_are_possible)
#define Float_list_class_description SPECIAL_VALUE(Float_list_class_description)
#define Float_parameter_class_description SPECIAL_VALUE(Float_parameter_class_description)
#define Float_variable_class_description SPECIAL_VALUE(Float_variable_class_description)
#define Floating_telewindows_limit SPECIAL_VALUE(Floating_telewindows_limit)
#define Floating_tw2_limit SPECIAL_VALUE(Floating_tw2_limit)
#define Flush_graphics_immediately_qm SPECIAL_VALUE(Flush_graphics_immediately_qm)
#define Focal_entity_for_simulation_formula SPECIAL_VALUE(Focal_entity_for_simulation_formula)
#define Focus_for_graph_detailed_procedures SPECIAL_VALUE(Focus_for_graph_detailed_procedures)
#define Focus_local_name_for_rule_compilation_qm SPECIAL_VALUE(Focus_local_name_for_rule_compilation_qm)
#define Focus_local_names_for_focus_role_name SPECIAL_VALUE(Focus_local_names_for_focus_role_name)
#define Focus_name_for_rule_or_formula_compilation SPECIAL_VALUE(Focus_name_for_rule_or_formula_compilation)
#define Focus_range SPECIAL_VALUE(Focus_range)
#define Focus_too_narrow_qm SPECIAL_VALUE(Focus_too_narrow_qm)
#define Font_feature_list SPECIAL_VALUE(Font_feature_list)
#define Font_map_for_line_of_text_of_graphic_element SPECIAL_VALUE(Font_map_for_line_of_text_of_graphic_element)
#define Fonts SPECIAL_VALUE(Fonts)
#define Fonts_cons_counter SPECIAL_VALUE(Fonts_cons_counter)
#define Fonts_needing_corresponding_kanji_font SPECIAL_VALUE(Fonts_needing_corresponding_kanji_font)
#define Fonts_used_in_print_job SPECIAL_VALUE(Fonts_used_in_print_job)
#define For_image_plane SPECIAL_VALUE(For_image_plane)
#define For_structure_count SPECIAL_VALUE(For_structure_count)
#define For_workstation SPECIAL_VALUE(For_workstation)
#define For_workstation_context SPECIAL_VALUE(For_workstation_context)
#define For_workstation_polling SPECIAL_VALUE(For_workstation_polling)
#define Force_change_to_minimum_size_p SPECIAL_VALUE(Force_change_to_minimum_size_p)
#define Force_clock_tick SPECIAL_VALUE(Force_clock_tick)
#define Foreground_color_difference_of_graphic_element SPECIAL_VALUE(Foreground_color_difference_of_graphic_element)
#define Foreground_color_difference_or_differences_of_graphic_element SPECIAL_VALUE(Foreground_color_difference_or_differences_of_graphic_element)
#define Foreground_color_value_of_graphic_element SPECIAL_VALUE(Foreground_color_value_of_graphic_element)
#define Foreign_function_call_info_count SPECIAL_VALUE(Foreign_function_call_info_count)
#define Foreign_function_declaration_class_description SPECIAL_VALUE(Foreign_function_declaration_class_description)
#define Foreign_function_entry_count SPECIAL_VALUE(Foreign_function_entry_count)
#define Foreign_function_image_info_count SPECIAL_VALUE(Foreign_function_image_info_count)
#define Foreign_function_registry SPECIAL_VALUE(Foreign_function_registry)
#define Foreign_image_connection_checkup_interval_in_ms SPECIAL_VALUE(Foreign_image_connection_checkup_interval_in_ms)
#define Foreign_image_connection_mode SPECIAL_VALUE(Foreign_image_connection_mode)
#define Foreign_struct_info_count SPECIAL_VALUE(Foreign_struct_info_count)
#define Foremost_attribute_for_multiplexed_chaining_qm SPECIAL_VALUE(Foremost_attribute_for_multiplexed_chaining_qm)
#define Forgive_long_procedure_instruction_qm SPECIAL_VALUE(Forgive_long_procedure_instruction_qm)
#define Format_frame_class_description SPECIAL_VALUE(Format_frame_class_description)
#define Formatted_part SPECIAL_VALUE(Formatted_part)
#define Formatted_part_highlight_flag SPECIAL_VALUE(Formatted_part_highlight_flag)
#define Formatted_part_true_line_color SPECIAL_VALUE(Formatted_part_true_line_color)
#define Formula_invocation_count SPECIAL_VALUE(Formula_invocation_count)
#define Forward_chaining_link_class_description SPECIAL_VALUE(Forward_chaining_link_class_description)
#define Forward_compiled_antecedent SPECIAL_VALUE(Forward_compiled_antecedent)
#define Forward_compiled_consequent_qm SPECIAL_VALUE(Forward_compiled_consequent_qm)
#define Forward_referenced_format_frames SPECIAL_VALUE(Forward_referenced_format_frames)
#define Frame_being_made SPECIAL_VALUE(Frame_being_made)
#define Frame_being_read_qm SPECIAL_VALUE(Frame_being_read_qm)
#define Frame_component_spot_count SPECIAL_VALUE(Frame_component_spot_count)
#define Frame_cons_counter SPECIAL_VALUE(Frame_cons_counter)
#define Frame_description_reference_count SPECIAL_VALUE(Frame_description_reference_count)
#define Frame_display_cons_counter SPECIAL_VALUE(Frame_display_cons_counter)
#define Frame_display_count SPECIAL_VALUE(Frame_display_count)
#define Frame_for_write_frame_for_kb SPECIAL_VALUE(Frame_for_write_frame_for_kb)
#define Frame_note_count SPECIAL_VALUE(Frame_note_count)
#define Frame_note_index SPECIAL_VALUE(Frame_note_index)
#define Frame_note_index_has_been_written_qm SPECIAL_VALUE(Frame_note_index_has_been_written_qm)
#define Frame_note_index_skip SPECIAL_VALUE(Frame_note_index_skip)
#define Frame_projecting SPECIAL_VALUE(Frame_projecting)
#define Frame_serial_cons_counter SPECIAL_VALUE(Frame_serial_cons_counter)
#define Frame_serial_number_map SPECIAL_VALUE(Frame_serial_number_map)
#define Frame_serial_number_of_current_message_board SPECIAL_VALUE(Frame_serial_number_of_current_message_board)
#define Frame_transform_count SPECIAL_VALUE(Frame_transform_count)
#define Frame_transform_of_frame SPECIAL_VALUE(Frame_transform_of_frame)
#define Frame_vector_count SPECIAL_VALUE(Frame_vector_count)
#define Frame_vector_memory_used SPECIAL_VALUE(Frame_vector_memory_used)
#define Frame_vector_pool_vector SPECIAL_VALUE(Frame_vector_pool_vector)
#define Frames_for_rendezvous_in_aggregate_values_qm SPECIAL_VALUE(Frames_for_rendezvous_in_aggregate_values_qm)
#define Frames_with_substitute_classes SPECIAL_VALUE(Frames_with_substitute_classes)
#define Free_floater_allowed_qm SPECIAL_VALUE(Free_floater_allowed_qm)
#define Free_global_stacks SPECIAL_VALUE(Free_global_stacks)
#define Free_malloced_arrays SPECIAL_VALUE(Free_malloced_arrays)
#define Fsm_state_count SPECIAL_VALUE(Fsm_state_count)
#define Funcalled_evaluator_array SPECIAL_VALUE(Funcalled_evaluator_array)
#define Funcalled_evaluator_dispatch_type SPECIAL_VALUE(Funcalled_evaluator_dispatch_type)
#define Funcalled_evaluator_functions SPECIAL_VALUE(Funcalled_evaluator_functions)
#define Funcalled_instruction_functions SPECIAL_VALUE(Funcalled_instruction_functions)
#define Funcalled_instructions SPECIAL_VALUE(Funcalled_instructions)
#define Function_definition_class_description SPECIAL_VALUE(Function_definition_class_description)
#define Function_info_count SPECIAL_VALUE(Function_info_count)
#define Function_invocation_count SPECIAL_VALUE(Function_invocation_count)
#define Function_templates SPECIAL_VALUE(Function_templates)
#define Future_task_queue_holder_count SPECIAL_VALUE(Future_task_queue_holder_count)
#define Future_task_to_run_propagate_all_workspace_changes_to_image_planes SPECIAL_VALUE(Future_task_to_run_propagate_all_workspace_changes_to_image_planes)
#define G2_array_class_description SPECIAL_VALUE(G2_array_class_description)
#define G2_cell_array_cell_class_description SPECIAL_VALUE(G2_cell_array_cell_class_description)
#define G2_cell_array_class_description SPECIAL_VALUE(G2_cell_array_class_description)
#define G2_comment_tokenizer SPECIAL_VALUE(G2_comment_tokenizer)
#define G2_datatypes_xml_namespace_prefix SPECIAL_VALUE(G2_datatypes_xml_namespace_prefix)
#define G2_designation_cell_class_description SPECIAL_VALUE(G2_designation_cell_class_description)
#define G2_element_types_that_can_contain_datum SPECIAL_VALUE(G2_element_types_that_can_contain_datum)
#define G2_expression_cell_class_description SPECIAL_VALUE(G2_expression_cell_class_description)
#define G2_has_been_started_qm SPECIAL_VALUE(G2_has_been_started_qm)
#define G2_has_v5_mode_windows_p SPECIAL_VALUE(G2_has_v5_mode_windows_p)
#define G2_identification_for_write_locks SPECIAL_VALUE(G2_identification_for_write_locks)
#define G2_list_class_description SPECIAL_VALUE(G2_list_class_description)
#define G2_list_cons_counter SPECIAL_VALUE(G2_list_cons_counter)
#define G2_list_element_count SPECIAL_VALUE(G2_list_element_count)
#define G2_load_kb_tokenizer SPECIAL_VALUE(G2_load_kb_tokenizer)
#define G2_login_class_description SPECIAL_VALUE(G2_login_class_description)
#define G2_login_state_count SPECIAL_VALUE(G2_login_state_count)
#define G2_machine_type SPECIAL_VALUE(G2_machine_type)
#define G2_meter_names_and_forms SPECIAL_VALUE(G2_meter_names_and_forms)
#define G2_meter_task_count SPECIAL_VALUE(G2_meter_task_count)
#define G2_module_file_name_map SPECIAL_VALUE(G2_module_file_name_map)
#define G2_module_search_path SPECIAL_VALUE(G2_module_search_path)
#define G2_operating_system SPECIAL_VALUE(G2_operating_system)
#define G2_query_cell_class_description SPECIAL_VALUE(G2_query_cell_class_description)
#define G2_save_module_flag SPECIAL_VALUE(G2_save_module_flag)
#define G2_save_module_list SPECIAL_VALUE(G2_save_module_list)
#define G2_simple_tokenizer SPECIAL_VALUE(G2_simple_tokenizer)
#define G2_standard_tokenizer SPECIAL_VALUE(G2_standard_tokenizer)
#define G2_stream_all_open_streams SPECIAL_VALUE(G2_stream_all_open_streams)
#define G2_stream_device_buffer SPECIAL_VALUE(G2_stream_device_buffer)
#define G2_stream_directory_buffer SPECIAL_VALUE(G2_stream_directory_buffer)
#define G2_stream_error_string_table SPECIAL_VALUE(G2_stream_error_string_table)
#define G2_stream_of_ok_file_reader SPECIAL_VALUE(G2_stream_of_ok_file_reader)
#define G2_stream_status_slot_description SPECIAL_VALUE(G2_stream_status_slot_description)
#define G2_stream_structure_count SPECIAL_VALUE(G2_stream_structure_count)
#define G2_symbol_tokenizer SPECIAL_VALUE(G2_symbol_tokenizer)
#define G2_time_at_start SPECIAL_VALUE(G2_time_at_start)
#define G2_time_at_start_as_text_string SPECIAL_VALUE(G2_time_at_start_as_text_string)
#define G2_time_to_tick_p_base SPECIAL_VALUE(G2_time_to_tick_p_base)
#define G2_to_g2_uses_references_p SPECIAL_VALUE(G2_to_g2_uses_references_p)
#define G2_token_count SPECIAL_VALUE(G2_token_count)
#define G2_tokenizer_tokenizer SPECIAL_VALUE(G2_tokenizer_tokenizer)
#define G2_window_class_description SPECIAL_VALUE(G2_window_class_description)
#define G2_window_for_save_via_system_procedure_qm SPECIAL_VALUE(G2_window_for_save_via_system_procedure_qm)
#define G2binary_file_name SPECIAL_VALUE(G2binary_file_name)
#define G2binary_file_position SPECIAL_VALUE(G2binary_file_position)
#define G2binary_file_stream SPECIAL_VALUE(G2binary_file_stream)
#define G2binary_file_symbol_index_space SPECIAL_VALUE(G2binary_file_symbol_index_space)
#define G2binary_file_symbol_list SPECIAL_VALUE(G2binary_file_symbol_list)
#define G2ds_cons_counter SPECIAL_VALUE(G2ds_cons_counter)
#define G2ds_data_value_write_truth_value_as_integer_p SPECIAL_VALUE(G2ds_data_value_write_truth_value_as_integer_p)
#define G2ds_interface_count SPECIAL_VALUE(G2ds_interface_count)
#define G2ds_interface_status_changed_p SPECIAL_VALUE(G2ds_interface_status_changed_p)
#define G2ds_interface_transition_table SPECIAL_VALUE(G2ds_interface_transition_table)
#define G2ds_server_connection_count SPECIAL_VALUE(G2ds_server_connection_count)
#define G2ds_server_connections SPECIAL_VALUE(G2ds_server_connections)
#define G2ds_variable_count SPECIAL_VALUE(G2ds_variable_count)
#define G2ds_variable_list SPECIAL_VALUE(G2ds_variable_list)
#define G2gl_activity_compilation_count SPECIAL_VALUE(G2gl_activity_compilation_count)
#define G2gl_activity_implementations_alist SPECIAL_VALUE(G2gl_activity_implementations_alist)
#define G2gl_activity_options_count SPECIAL_VALUE(G2gl_activity_options_count)
#define G2gl_alarm_event_handler SPECIAL_VALUE(G2gl_alarm_event_handler)
#define G2gl_alarm_event_handler_activity_compilation_count SPECIAL_VALUE(G2gl_alarm_event_handler_activity_compilation_count)
#define G2gl_arg_variable SPECIAL_VALUE(G2gl_arg_variable)
#define G2gl_assign SPECIAL_VALUE(G2gl_assign)
#define G2gl_assign_activity_compilation_count SPECIAL_VALUE(G2gl_assign_activity_compilation_count)
#define G2gl_attribute_display_compilation_count SPECIAL_VALUE(G2gl_attribute_display_compilation_count)
#define G2gl_body_being_laid_out SPECIAL_VALUE(G2gl_body_being_laid_out)
#define G2gl_body_compilation_count SPECIAL_VALUE(G2gl_body_compilation_count)
#define G2gl_break SPECIAL_VALUE(G2gl_break)
#define G2gl_break_activity_compilation_count SPECIAL_VALUE(G2gl_break_activity_compilation_count)
#define G2gl_call SPECIAL_VALUE(G2gl_call)
#define G2gl_call_activity_compilation_count SPECIAL_VALUE(G2gl_call_activity_compilation_count)
#define G2gl_call_invocation_count SPECIAL_VALUE(G2gl_call_invocation_count)
#define G2gl_compensate SPECIAL_VALUE(G2gl_compensate)
#define G2gl_compensate_activity_compilation_count SPECIAL_VALUE(G2gl_compensate_activity_compilation_count)
#define G2gl_compensation_handler SPECIAL_VALUE(G2gl_compensation_handler)
#define G2gl_compensation_handler_activity_compilation_count SPECIAL_VALUE(G2gl_compensation_handler_activity_compilation_count)
#define G2gl_compilation_version_count SPECIAL_VALUE(G2gl_compilation_version_count)
#define G2gl_correlation_variable SPECIAL_VALUE(G2gl_correlation_variable)
#define G2gl_do SPECIAL_VALUE(G2gl_do)
#define G2gl_do_activity_compilation_count SPECIAL_VALUE(G2gl_do_activity_compilation_count)
#define G2gl_empty SPECIAL_VALUE(G2gl_empty)
#define G2gl_empty_activity_compilation_count SPECIAL_VALUE(G2gl_empty_activity_compilation_count)
#define G2gl_eval_error SPECIAL_VALUE(G2gl_eval_error)
#define G2gl_execution_fault_count SPECIAL_VALUE(G2gl_execution_fault_count)
#define G2gl_execution_frame_count SPECIAL_VALUE(G2gl_execution_frame_count)
#define G2gl_execution_thread_count SPECIAL_VALUE(G2gl_execution_thread_count)
#define G2gl_exit SPECIAL_VALUE(G2gl_exit)
#define G2gl_exit_activity_compilation_count SPECIAL_VALUE(G2gl_exit_activity_compilation_count)
#define G2gl_expression_compilation_error SPECIAL_VALUE(G2gl_expression_compilation_error)
#define G2gl_expression_language_symbol SPECIAL_VALUE(G2gl_expression_language_symbol)
#define G2gl_failed_activity_name SPECIAL_VALUE(G2gl_failed_activity_name)
#define G2gl_false SPECIAL_VALUE(G2gl_false)
#define G2gl_fault_handler SPECIAL_VALUE(G2gl_fault_handler)
#define G2gl_fault_handler_activity_compilation_count SPECIAL_VALUE(G2gl_fault_handler_activity_compilation_count)
#define G2gl_flow_discriminator SPECIAL_VALUE(G2gl_flow_discriminator)
#define G2gl_flow_discriminator_activity_compilation_count SPECIAL_VALUE(G2gl_flow_discriminator_activity_compilation_count)
#define G2gl_flow_gate SPECIAL_VALUE(G2gl_flow_gate)
#define G2gl_flow_gate_activity_compilation_count SPECIAL_VALUE(G2gl_flow_gate_activity_compilation_count)
#define G2gl_flow_signal SPECIAL_VALUE(G2gl_flow_signal)
#define G2gl_flow_signal_activity_compilation_count SPECIAL_VALUE(G2gl_flow_signal_activity_compilation_count)
#define G2gl_flow_split SPECIAL_VALUE(G2gl_flow_split)
#define G2gl_flow_split_activity_compilation_count SPECIAL_VALUE(G2gl_flow_split_activity_compilation_count)
#define G2gl_flow_sync SPECIAL_VALUE(G2gl_flow_sync)
#define G2gl_flow_sync_activity_compilation_count SPECIAL_VALUE(G2gl_flow_sync_activity_compilation_count)
#define G2gl_flow_terminator SPECIAL_VALUE(G2gl_flow_terminator)
#define G2gl_flow_terminator_activity_compilation_count SPECIAL_VALUE(G2gl_flow_terminator_activity_compilation_count)
#define G2gl_import_added_start_activity_p SPECIAL_VALUE(G2gl_import_added_start_activity_p)
#define G2gl_import_errors SPECIAL_VALUE(G2gl_import_errors)
#define G2gl_import_flow_link_p_list SPECIAL_VALUE(G2gl_import_flow_link_p_list)
#define G2gl_invoke SPECIAL_VALUE(G2gl_invoke)
#define G2gl_invoke_activity_compilation_count SPECIAL_VALUE(G2gl_invoke_activity_compilation_count)
#define G2gl_link_connection_arrows SPECIAL_VALUE(G2gl_link_connection_arrows)
#define G2gl_link_connection_line_pattern SPECIAL_VALUE(G2gl_link_connection_line_pattern)
#define G2gl_local_variable SPECIAL_VALUE(G2gl_local_variable)
#define G2gl_message_event_handler SPECIAL_VALUE(G2gl_message_event_handler)
#define G2gl_message_event_handler_activity_compilation_count SPECIAL_VALUE(G2gl_message_event_handler_activity_compilation_count)
#define G2gl_message_transmission_count SPECIAL_VALUE(G2gl_message_transmission_count)
#define G2gl_n_out_of_m_flow_join SPECIAL_VALUE(G2gl_n_out_of_m_flow_join)
#define G2gl_n_out_of_m_flow_join_activity_compilation_count SPECIAL_VALUE(G2gl_n_out_of_m_flow_join_activity_compilation_count)
#define G2gl_object_icon_descriptions_info SPECIAL_VALUE(G2gl_object_icon_descriptions_info)
#define G2gl_object_icon_substitutions_may_be_in_use_p SPECIAL_VALUE(G2gl_object_icon_substitutions_may_be_in_use_p)
#define G2gl_operators SPECIAL_VALUE(G2gl_operators)
#define G2gl_parameters SPECIAL_VALUE(G2gl_parameters)
#define G2gl_partner_link_variable SPECIAL_VALUE(G2gl_partner_link_variable)
#define G2gl_pick SPECIAL_VALUE(G2gl_pick)
#define G2gl_pick_activity_compilation_count SPECIAL_VALUE(G2gl_pick_activity_compilation_count)
#define G2gl_pick_join SPECIAL_VALUE(G2gl_pick_join)
#define G2gl_pick_join_activity_compilation_count SPECIAL_VALUE(G2gl_pick_join_activity_compilation_count)
#define G2gl_process_invocation_thread_count SPECIAL_VALUE(G2gl_process_invocation_thread_count)
#define G2gl_query_language_symbol SPECIAL_VALUE(G2gl_query_language_symbol)
#define G2gl_receive SPECIAL_VALUE(G2gl_receive)
#define G2gl_receive_activity_compilation_count SPECIAL_VALUE(G2gl_receive_activity_compilation_count)
#define G2gl_reply SPECIAL_VALUE(G2gl_reply)
#define G2gl_reply_activity_compilation_count SPECIAL_VALUE(G2gl_reply_activity_compilation_count)
#define G2gl_return SPECIAL_VALUE(G2gl_return)
#define G2gl_return_activity_compilation_count SPECIAL_VALUE(G2gl_return_activity_compilation_count)
#define G2gl_scope SPECIAL_VALUE(G2gl_scope)
#define G2gl_scope_activity_compilation_count SPECIAL_VALUE(G2gl_scope_activity_compilation_count)
#define G2gl_service_port_count SPECIAL_VALUE(G2gl_service_port_count)
#define G2gl_standard_connection_arrows SPECIAL_VALUE(G2gl_standard_connection_arrows)
#define G2gl_standard_connection_line_pattern SPECIAL_VALUE(G2gl_standard_connection_line_pattern)
#define G2gl_standard_service_switch SPECIAL_VALUE(G2gl_standard_service_switch)
#define G2gl_switch_fork SPECIAL_VALUE(G2gl_switch_fork)
#define G2gl_switch_fork_activity_compilation_count SPECIAL_VALUE(G2gl_switch_fork_activity_compilation_count)
#define G2gl_switch_join SPECIAL_VALUE(G2gl_switch_join)
#define G2gl_switch_join_activity_compilation_count SPECIAL_VALUE(G2gl_switch_join_activity_compilation_count)
#define G2gl_text_box_compilation_count SPECIAL_VALUE(G2gl_text_box_compilation_count)
#define G2gl_throw SPECIAL_VALUE(G2gl_throw)
#define G2gl_throw_activity_compilation_count SPECIAL_VALUE(G2gl_throw_activity_compilation_count)
#define G2gl_true SPECIAL_VALUE(G2gl_true)
#define G2gl_variable SPECIAL_VALUE(G2gl_variable)
#define G2gl_wait SPECIAL_VALUE(G2gl_wait)
#define G2gl_wait_activity_compilation_count SPECIAL_VALUE(G2gl_wait_activity_compilation_count)
#define G2gl_while SPECIAL_VALUE(G2gl_while)
#define G2gl_while_activity_compilation_count SPECIAL_VALUE(G2gl_while_activity_compilation_count)
#define G2gl_xml_namespace SPECIAL_VALUE(G2gl_xml_namespace)
#define G2gl_xml_namespace_prefix SPECIAL_VALUE(G2gl_xml_namespace_prefix)
#define G2passwdexe SPECIAL_VALUE(G2passwdexe)
#define G2passwdexe_is_executable_p SPECIAL_VALUE(G2passwdexe_is_executable_p)
#define Gathering_normally_editable_slots_for_search_qm SPECIAL_VALUE(Gathering_normally_editable_slots_for_search_qm)
#define Gb_2312_count SPECIAL_VALUE(Gb_2312_count)
#define Generate_source_annotation_info SPECIAL_VALUE(Generate_source_annotation_info)
#define Generated_var_spots_for_base_code_body_return SPECIAL_VALUE(Generated_var_spots_for_base_code_body_return)
#define Generic_action_button_class_description SPECIAL_VALUE(Generic_action_button_class_description)
#define Generic_formula_class_description SPECIAL_VALUE(Generic_formula_class_description)
#define Generic_listener_initialized_qm SPECIAL_VALUE(Generic_listener_initialized_qm)
#define Generic_rule_instance_display_hash_table SPECIAL_VALUE(Generic_rule_instance_display_hash_table)
#define Generic_simulation_formula_class_description SPECIAL_VALUE(Generic_simulation_formula_class_description)
#define Generic_simulation_formulas_used_p SPECIAL_VALUE(Generic_simulation_formulas_used_p)
#define Gensym_base_time_as_managed_float SPECIAL_VALUE(Gensym_base_time_as_managed_float)
#define Gensym_char_or_code_for_bullet SPECIAL_VALUE(Gensym_char_or_code_for_bullet)
#define Gensym_char_or_code_for_capital_ligature_oe SPECIAL_VALUE(Gensym_char_or_code_for_capital_ligature_oe)
#define Gensym_char_or_code_for_linebreak SPECIAL_VALUE(Gensym_char_or_code_for_linebreak)
#define Gensym_char_or_code_for_paragraph_break SPECIAL_VALUE(Gensym_char_or_code_for_paragraph_break)
#define Gensym_char_or_code_for_small_letter_f_with_hook SPECIAL_VALUE(Gensym_char_or_code_for_small_letter_f_with_hook)
#define Gensym_char_or_code_for_small_ligature_oe SPECIAL_VALUE(Gensym_char_or_code_for_small_ligature_oe)
#define Gensym_char_or_code_for_trade_mark_sign SPECIAL_VALUE(Gensym_char_or_code_for_trade_mark_sign)
#define Gensym_code_for_bullet SPECIAL_VALUE(Gensym_code_for_bullet)
#define Gensym_code_for_capital_ligature_oe SPECIAL_VALUE(Gensym_code_for_capital_ligature_oe)
#define Gensym_code_for_linebreak SPECIAL_VALUE(Gensym_code_for_linebreak)
#define Gensym_code_for_paragraph_break SPECIAL_VALUE(Gensym_code_for_paragraph_break)
#define Gensym_code_for_small_letter_f_with_hook SPECIAL_VALUE(Gensym_code_for_small_letter_f_with_hook)
#define Gensym_code_for_small_ligature_oe SPECIAL_VALUE(Gensym_code_for_small_ligature_oe)
#define Gensym_code_for_trade_mark_sign SPECIAL_VALUE(Gensym_code_for_trade_mark_sign)
#define Gensym_cons_counter SPECIAL_VALUE(Gensym_cons_counter)
#define Gensym_default_pathname_defaults SPECIAL_VALUE(Gensym_default_pathname_defaults)
#define Gensym_environment_variable_buffer SPECIAL_VALUE(Gensym_environment_variable_buffer)
#define Gensym_error_argument_list SPECIAL_VALUE(Gensym_error_argument_list)
#define Gensym_error_format_string SPECIAL_VALUE(Gensym_error_format_string)
#define Gensym_error_sure_of_format_info_p SPECIAL_VALUE(Gensym_error_sure_of_format_info_p)
#define Gensym_esc_for_bullet_qm SPECIAL_VALUE(Gensym_esc_for_bullet_qm)
#define Gensym_esc_for_capital_ligature_oe_qm SPECIAL_VALUE(Gensym_esc_for_capital_ligature_oe_qm)
#define Gensym_esc_for_linebreak_qm SPECIAL_VALUE(Gensym_esc_for_linebreak_qm)
#define Gensym_esc_for_paragraph_break_qm SPECIAL_VALUE(Gensym_esc_for_paragraph_break_qm)
#define Gensym_esc_for_small_letter_f_with_hook_qm SPECIAL_VALUE(Gensym_esc_for_small_letter_f_with_hook_qm)
#define Gensym_esc_for_small_ligature_oe_qm SPECIAL_VALUE(Gensym_esc_for_small_ligature_oe_qm)
#define Gensym_esc_for_trade_mark_sign_qm SPECIAL_VALUE(Gensym_esc_for_trade_mark_sign_qm)
#define Gensym_file_error_occurred_p SPECIAL_VALUE(Gensym_file_error_occurred_p)
#define Gensym_grammar_count SPECIAL_VALUE(Gensym_grammar_count)
#define Gensym_logo_style SPECIAL_VALUE(Gensym_logo_style)
#define Gensym_pathname_count SPECIAL_VALUE(Gensym_pathname_count)
#define Gensym_string_stream_count SPECIAL_VALUE(Gensym_string_stream_count)
#define Gensym_string_text_sequence_count SPECIAL_VALUE(Gensym_string_text_sequence_count)
#define Gensym_time SPECIAL_VALUE(Gensym_time)
#define Gensym_time_array SPECIAL_VALUE(Gensym_time_array)
#define Gensym_time_at_start SPECIAL_VALUE(Gensym_time_at_start)
#define Gensym_window_count SPECIAL_VALUE(Gensym_window_count)
#define Gensym_window_for_printing SPECIAL_VALUE(Gensym_window_for_printing)
#define Geometric_change_to_connection_is_temporary_p SPECIAL_VALUE(Geometric_change_to_connection_is_temporary_p)
#define Geometry_count SPECIAL_VALUE(Geometry_count)
#define Gesture_function_count SPECIAL_VALUE(Gesture_function_count)
#define Gesture_local_count SPECIAL_VALUE(Gesture_local_count)
#define Gesture_source_recording_p SPECIAL_VALUE(Gesture_source_recording_p)
#define Gesture_source_stack SPECIAL_VALUE(Gesture_source_stack)
#define Gesture_thread_count SPECIAL_VALUE(Gesture_thread_count)
#define Gesture_unbound_value SPECIAL_VALUE(Gesture_unbound_value)
#define Get_focal_entity_for_simulation_formula_qm SPECIAL_VALUE(Get_focal_entity_for_simulation_formula_qm)
#define Get_object_on_kb_workspace_for_item SPECIAL_VALUE(Get_object_on_kb_workspace_for_item)
#define Gfi_cons_counter SPECIAL_VALUE(Gfi_cons_counter)
#define Gfi_list_of_converters SPECIAL_VALUE(Gfi_list_of_converters)
#define Gfi_queue_item_count SPECIAL_VALUE(Gfi_queue_item_count)
#define Global_desired_thrashing_setpoint SPECIAL_VALUE(Global_desired_thrashing_setpoint)
#define Global_domain SPECIAL_VALUE(Global_domain)
#define Global_draw_diagonally_qm SPECIAL_VALUE(Global_draw_diagonally_qm)
#define Global_keyboard_command_choices SPECIAL_VALUE(Global_keyboard_command_choices)
#define Global_list_of_all_data_servers SPECIAL_VALUE(Global_list_of_all_data_servers)
#define Global_nms_menu_choiced_item_id SPECIAL_VALUE(Global_nms_menu_choiced_item_id)
#define Global_nmsci_id_for_attributes_pane SPECIAL_VALUE(Global_nmsci_id_for_attributes_pane)
#define Global_nmsci_id_for_hidden_attributes_pane SPECIAL_VALUE(Global_nmsci_id_for_hidden_attributes_pane)
#define Global_output_stream_for_expand_syntax_template SPECIAL_VALUE(Global_output_stream_for_expand_syntax_template)
#define Global_profiling_structure_count SPECIAL_VALUE(Global_profiling_structure_count)
#define Global_stack SPECIAL_VALUE(Global_stack)
#define Global_table_of_attributes_pane SPECIAL_VALUE(Global_table_of_attributes_pane)
#define Global_table_of_attributes_pane_pointer SPECIAL_VALUE(Global_table_of_attributes_pane_pointer)
#define Global_table_of_hidden_attributes_pane SPECIAL_VALUE(Global_table_of_hidden_attributes_pane)
#define Global_table_of_hidden_attributes_pane_pointer SPECIAL_VALUE(Global_table_of_hidden_attributes_pane_pointer)
#define Global_temp_1 SPECIAL_VALUE(Global_temp_1)
#define Global_temp_2 SPECIAL_VALUE(Global_temp_2)
#define Global_temp_3 SPECIAL_VALUE(Global_temp_3)
#define Goto_tag_entry_count SPECIAL_VALUE(Goto_tag_entry_count)
#define Goto_tags_in_compilation SPECIAL_VALUE(Goto_tags_in_compilation)
#define Grammar_categories_getting_choose_existing_class_feature SPECIAL_VALUE(Grammar_categories_getting_choose_existing_class_feature)
#define Grammar_categories_getting_yes_no_feature SPECIAL_VALUE(Grammar_categories_getting_yes_no_feature)
#define Grammar_cons_counter SPECIAL_VALUE(Grammar_cons_counter)
#define Grammar_rules_to_add_for_nupec_after_authorization SPECIAL_VALUE(Grammar_rules_to_add_for_nupec_after_authorization)
#define Graph_allocation_factor SPECIAL_VALUE(Graph_allocation_factor)
#define Graph_background_color_value SPECIAL_VALUE(Graph_background_color_value)
#define Graph_class_description SPECIAL_VALUE(Graph_class_description)
#define Graph_cons_counter SPECIAL_VALUE(Graph_cons_counter)
#define Graph_display_changed_during_update_qm SPECIAL_VALUE(Graph_display_changed_during_update_qm)
#define Graph_display_count SPECIAL_VALUE(Graph_display_count)
#define Graph_expression_uses_local_name_qm SPECIAL_VALUE(Graph_expression_uses_local_name_qm)
#define Graph_grid_class_description SPECIAL_VALUE(Graph_grid_class_description)
#define Graph_grid_for_data SPECIAL_VALUE(Graph_grid_for_data)
#define Graph_layout_cons_counter SPECIAL_VALUE(Graph_layout_cons_counter)
#define Graph_month_strings SPECIAL_VALUE(Graph_month_strings)
#define Graph_node_count SPECIAL_VALUE(Graph_node_count)
#define Graph_nodes_needing_children_connections SPECIAL_VALUE(Graph_nodes_needing_children_connections)
#define Graph_nodes_to_add_as_subblocks SPECIAL_VALUE(Graph_nodes_to_add_as_subblocks)
#define Graph_or_icon_rendering_of_graphic_element SPECIAL_VALUE(Graph_or_icon_rendering_of_graphic_element)
#define Graph_rendering_count SPECIAL_VALUE(Graph_rendering_count)
#define Graph_table_spot_count SPECIAL_VALUE(Graph_table_spot_count)
#define Graphed_block_groups_to_move SPECIAL_VALUE(Graphed_block_groups_to_move)
#define Graphic_character_set_count SPECIAL_VALUE(Graphic_character_set_count)
#define Graphic_element_projection SPECIAL_VALUE(Graphic_element_projection)
#define Graphics_cons_counter SPECIAL_VALUE(Graphics_cons_counter)
#define Grid SPECIAL_VALUE(Grid)
#define Grid_color SPECIAL_VALUE(Grid_color)
#define Grid_height SPECIAL_VALUE(Grid_height)
#define Grid_painting SPECIAL_VALUE(Grid_painting)
#define Grid_pane_count SPECIAL_VALUE(Grid_pane_count)
#define Grid_view_cell_count SPECIAL_VALUE(Grid_view_cell_count)
#define Grid_visible SPECIAL_VALUE(Grid_visible)
#define Grid_width SPECIAL_VALUE(Grid_width)
#define Group_index_structure_count SPECIAL_VALUE(Group_index_structure_count)
#define Gsi_application_name SPECIAL_VALUE(Gsi_application_name)
#define Gsi_array_wrapper_count SPECIAL_VALUE(Gsi_array_wrapper_count)
#define Gsi_attribute_count SPECIAL_VALUE(Gsi_attribute_count)
#define Gsi_connection_checkup_interval_in_ms SPECIAL_VALUE(Gsi_connection_checkup_interval_in_ms)
#define Gsi_cons_counter SPECIAL_VALUE(Gsi_cons_counter)
#define Gsi_context_to_socket_map SPECIAL_VALUE(Gsi_context_to_socket_map)
#define Gsi_extension_data_count SPECIAL_VALUE(Gsi_extension_data_count)
#define Gsi_history_count SPECIAL_VALUE(Gsi_history_count)
#define Gsi_icp_interface_count SPECIAL_VALUE(Gsi_icp_interface_count)
#define Gsi_instance_count SPECIAL_VALUE(Gsi_instance_count)
#define Gsi_instance_extension_count SPECIAL_VALUE(Gsi_instance_extension_count)
#define Gsi_interface_status_changed_p SPECIAL_VALUE(Gsi_interface_status_changed_p)
#define Gsi_interfaces_to_process_head SPECIAL_VALUE(Gsi_interfaces_to_process_head)
#define Gsi_interfaces_to_process_tail SPECIAL_VALUE(Gsi_interfaces_to_process_tail)
#define Gsi_local_function_count SPECIAL_VALUE(Gsi_local_function_count)
#define Gsi_local_home SPECIAL_VALUE(Gsi_local_home)
#define Gsi_magic_number SPECIAL_VALUE(Gsi_magic_number)
#define Gsi_maximum_contexts_exceeded SPECIAL_VALUE(Gsi_maximum_contexts_exceeded)
#define Gsi_maximum_idle_interval SPECIAL_VALUE(Gsi_maximum_idle_interval)
#define Gsi_maximum_number_of_contexts SPECIAL_VALUE(Gsi_maximum_number_of_contexts)
#define Gsi_protect_inner_calls_p SPECIAL_VALUE(Gsi_protect_inner_calls_p)
#define Gsi_reclaim_list_level SPECIAL_VALUE(Gsi_reclaim_list_level)
#define Gsi_reclaim_list_qm SPECIAL_VALUE(Gsi_reclaim_list_qm)
#define Gsi_remote_procedure_count SPECIAL_VALUE(Gsi_remote_procedure_count)
#define Gsi_remote_value_conses_logical_p SPECIAL_VALUE(Gsi_remote_value_conses_logical_p)
#define Gsi_remote_value_creates_instance_p SPECIAL_VALUE(Gsi_remote_value_creates_instance_p)
#define Gsi_throw_to_run_loop_may_be_harmful_p SPECIAL_VALUE(Gsi_throw_to_run_loop_may_be_harmful_p)
#define Gsi_transfer_wrapper_count SPECIAL_VALUE(Gsi_transfer_wrapper_count)
#define Gsi_vector_length SPECIAL_VALUE(Gsi_vector_length)
#define Halt_info_count SPECIAL_VALUE(Halt_info_count)
#define Han_interpretation_mode SPECIAL_VALUE(Han_interpretation_mode)
#define Handle_to_socket_mapping SPECIAL_VALUE(Handle_to_socket_mapping)
#define Handle_ui_client_interface_messages_immediately_p SPECIAL_VALUE(Handle_ui_client_interface_messages_immediately_p)
#define Handling_solitary_i_am_alive_qm SPECIAL_VALUE(Handling_solitary_i_am_alive_qm)
#define Handy_float_1 SPECIAL_VALUE(Handy_float_1)
#define Height_for_change_size_qm SPECIAL_VALUE(Height_for_change_size_qm)
#define Hfep_action SPECIAL_VALUE(Hfep_action)
#define Hfep_capability_qm SPECIAL_VALUE(Hfep_capability_qm)
#define Hfep_cho_ksc2c SPECIAL_VALUE(Hfep_cho_ksc2c)
#define Hfep_hanc_type_count SPECIAL_VALUE(Hfep_hanc_type_count)
#define Hfep_jong_ksc2c SPECIAL_VALUE(Hfep_jong_ksc2c)
#define Hfep_jung_ksc2c SPECIAL_VALUE(Hfep_jung_ksc2c)
#define Hfep_ksc2cs SPECIAL_VALUE(Hfep_ksc2cs)
#define Hfep_state SPECIAL_VALUE(Hfep_state)
#define High_bound_system_variable_for_get_current_bounds_for_plot SPECIAL_VALUE(High_bound_system_variable_for_get_current_bounds_for_plot)
#define High_bound_system_variable_for_get_current_min_and_max_for_plot_from_history SPECIAL_VALUE(High_bound_system_variable_for_get_current_min_and_max_for_plot_from_history)
#define High_value_for_horizontal_grid_lines SPECIAL_VALUE(High_value_for_horizontal_grid_lines)
#define High_value_for_vertical_grid_lines SPECIAL_VALUE(High_value_for_vertical_grid_lines)
#define Highest_foreign_image_index SPECIAL_VALUE(Highest_foreign_image_index)
#define Highest_icp_socket_session_id SPECIAL_VALUE(Highest_icp_socket_session_id)
#define Highest_inspect_session_id SPECIAL_VALUE(Highest_inspect_session_id)
#define Highest_parsing_context_handle SPECIAL_VALUE(Highest_parsing_context_handle)
#define Highest_remote_spawn_index SPECIAL_VALUE(Highest_remote_spawn_index)
#define Highest_state_index SPECIAL_VALUE(Highest_state_index)
#define History_cons_counter SPECIAL_VALUE(History_cons_counter)
#define History_ring_buffer_count SPECIAL_VALUE(History_ring_buffer_count)
#define History_time_per_pixel SPECIAL_VALUE(History_time_per_pixel)
#define History_time_to_evaluate_display_expression_with SPECIAL_VALUE(History_time_to_evaluate_display_expression_with)
#define Home_name_separator SPECIAL_VALUE(Home_name_separator)
#define Horizontal_grid_line_color_qm SPECIAL_VALUE(Horizontal_grid_line_color_qm)
#define Horizontal_grid_line_spacing SPECIAL_VALUE(Horizontal_grid_line_spacing)
#define Horizontal_grid_line_width SPECIAL_VALUE(Horizontal_grid_line_width)
#define Hot_spot_state_count SPECIAL_VALUE(Hot_spot_state_count)
#define Hour_of_last_message SPECIAL_VALUE(Hour_of_last_message)
#define Hourly_countdown SPECIAL_VALUE(Hourly_countdown)
#define Html_view_count SPECIAL_VALUE(Html_view_count)
#define I_am_alive_info_count SPECIAL_VALUE(I_am_alive_info_count)
#define I_am_alive_send_time_interval SPECIAL_VALUE(I_am_alive_send_time_interval)
#define I_am_alive_send_time_interval_in_seconds SPECIAL_VALUE(I_am_alive_send_time_interval_in_seconds)
#define I_am_alive_send_time_interval_in_seconds_as_float SPECIAL_VALUE(I_am_alive_send_time_interval_in_seconds_as_float)
#define Icmp_socket_count SPECIAL_VALUE(Icmp_socket_count)
#define Icon_cell_class_description SPECIAL_VALUE(Icon_cell_class_description)
#define Icon_description_count SPECIAL_VALUE(Icon_description_count)
#define Icon_editor_button_count SPECIAL_VALUE(Icon_editor_button_count)
#define Icon_editor_cons_counter SPECIAL_VALUE(Icon_editor_cons_counter)
#define Icon_editor_count SPECIAL_VALUE(Icon_editor_count)
#define Icon_editor_engine_count SPECIAL_VALUE(Icon_editor_engine_count)
#define Icon_editor_layers_pad_count SPECIAL_VALUE(Icon_editor_layers_pad_count)
#define Icon_editor_table_count SPECIAL_VALUE(Icon_editor_table_count)
#define Icon_editor_table_info_frame_class_description SPECIAL_VALUE(Icon_editor_table_info_frame_class_description)
#define Icon_editor_translator_count SPECIAL_VALUE(Icon_editor_translator_count)
#define Icon_editor_view_pad_count SPECIAL_VALUE(Icon_editor_view_pad_count)
#define Icon_editor_workspace_class_description SPECIAL_VALUE(Icon_editor_workspace_class_description)
#define Icon_list_notes SPECIAL_VALUE(Icon_list_notes)
#define Icon_offset_clip_bottom SPECIAL_VALUE(Icon_offset_clip_bottom)
#define Icon_offset_clip_left SPECIAL_VALUE(Icon_offset_clip_left)
#define Icon_offset_clip_right SPECIAL_VALUE(Icon_offset_clip_right)
#define Icon_offset_clip_top SPECIAL_VALUE(Icon_offset_clip_top)
#define Icon_offset_left SPECIAL_VALUE(Icon_offset_left)
#define Icon_offset_top SPECIAL_VALUE(Icon_offset_top)
#define Icon_rendering_count SPECIAL_VALUE(Icon_rendering_count)
#define Icon_renderings_being_bulk_decached SPECIAL_VALUE(Icon_renderings_being_bulk_decached)
#define Icon_slot_group_count SPECIAL_VALUE(Icon_slot_group_count)
#define Icp_bits_current_bits SPECIAL_VALUE(Icp_bits_current_bits)
#define Icp_bits_current_value SPECIAL_VALUE(Icp_bits_current_value)
#define Icp_buffer_count SPECIAL_VALUE(Icp_buffer_count)
#define Icp_buffer_of_start_of_message_series_qm SPECIAL_VALUE(Icp_buffer_of_start_of_message_series_qm)
#define Icp_buffer_ref_count_cons_counter SPECIAL_VALUE(Icp_buffer_ref_count_cons_counter)
#define Icp_buffers_for_message_group SPECIAL_VALUE(Icp_buffers_for_message_group)
#define Icp_byte_position_of_start_of_message_series_qm SPECIAL_VALUE(Icp_byte_position_of_start_of_message_series_qm)
#define Icp_callback_cons_counter SPECIAL_VALUE(Icp_callback_cons_counter)
#define Icp_cons_counter SPECIAL_VALUE(Icp_cons_counter)
#define Icp_error_suspend_p SPECIAL_VALUE(Icp_error_suspend_p)
#define Icp_message_handler_array SPECIAL_VALUE(Icp_message_handler_array)
#define Icp_message_handler_name_array SPECIAL_VALUE(Icp_message_handler_name_array)
#define Icp_message_trace_stream_qm SPECIAL_VALUE(Icp_message_trace_stream_qm)
#define Icp_output_ports_to_flush SPECIAL_VALUE(Icp_output_ports_to_flush)
#define Icp_player_message_handler_array SPECIAL_VALUE(Icp_player_message_handler_array)
#define Icp_port_count SPECIAL_VALUE(Icp_port_count)
#define Icp_port_for_reclaim SPECIAL_VALUE(Icp_port_for_reclaim)
#define Icp_printing_message_handler_array SPECIAL_VALUE(Icp_printing_message_handler_array)
#define Icp_priority_categories_for_gsi SPECIAL_VALUE(Icp_priority_categories_for_gsi)
#define Icp_protocol_version SPECIAL_VALUE(Icp_protocol_version)
#define Icp_read_task_count SPECIAL_VALUE(Icp_read_task_count)
#define Icp_read_trace_cutoff_level_qm SPECIAL_VALUE(Icp_read_trace_cutoff_level_qm)
#define Icp_socket_connect_negotiation_timeout_default SPECIAL_VALUE(Icp_socket_connect_negotiation_timeout_default)
#define Icp_socket_count SPECIAL_VALUE(Icp_socket_count)
#define Icp_socket_for_handle_icp_messages SPECIAL_VALUE(Icp_socket_for_handle_icp_messages)
#define Icp_socket_for_reclaim_qm SPECIAL_VALUE(Icp_socket_for_reclaim_qm)
#define Icp_socket_index SPECIAL_VALUE(Icp_socket_index)
#define Icp_socket_transacting_message_group SPECIAL_VALUE(Icp_socket_transacting_message_group)
#define Icp_sockets_now_initializing_g2ds SPECIAL_VALUE(Icp_sockets_now_initializing_g2ds)
#define Icp_sockets_now_initializing_gsi SPECIAL_VALUE(Icp_sockets_now_initializing_gsi)
#define Icp_sockets_to_be_reclaimed SPECIAL_VALUE(Icp_sockets_to_be_reclaimed)
#define Icp_sockets_waiting_for_icp_message_processing SPECIAL_VALUE(Icp_sockets_waiting_for_icp_message_processing)
#define Icp_suspend SPECIAL_VALUE(Icp_suspend)
#define Icp_trace_level_descriptions SPECIAL_VALUE(Icp_trace_level_descriptions)
#define Icp_trace_print_message_series_p SPECIAL_VALUE(Icp_trace_print_message_series_p)
#define Icp_write_task_count SPECIAL_VALUE(Icp_write_task_count)
#define Icp_write_trace_cutoff_level_qm SPECIAL_VALUE(Icp_write_trace_cutoff_level_qm)
#define Identified_drawing_activity_count SPECIAL_VALUE(Identified_drawing_activity_count)
#define Identifying_attribute_count_for_item_new_copy SPECIAL_VALUE(Identifying_attribute_count_for_item_new_copy)
#define Idling_wait_state_string SPECIAL_VALUE(Idling_wait_state_string)
#define Ignore_kb_flags_in_kbs_qm SPECIAL_VALUE(Ignore_kb_flags_in_kbs_qm)
#define Ignore_kb_state_changes_p SPECIAL_VALUE(Ignore_kb_state_changes_p)
#define Image_cv_count SPECIAL_VALUE(Image_cv_count)
#define Image_data_count SPECIAL_VALUE(Image_data_count)
#define Image_data_of_graphic_element SPECIAL_VALUE(Image_data_of_graphic_element)
#define Image_left_offset_in_ws SPECIAL_VALUE(Image_left_offset_in_ws)
#define Image_plane_count SPECIAL_VALUE(Image_plane_count)
#define Image_plane_for_finding_object_near_mouse SPECIAL_VALUE(Image_plane_for_finding_object_near_mouse)
#define Image_plane_is_obscured_p SPECIAL_VALUE(Image_plane_is_obscured_p)
#define Image_plane_spot_count SPECIAL_VALUE(Image_plane_spot_count)
#define Image_rendering_count SPECIAL_VALUE(Image_rendering_count)
#define Image_tile_count SPECIAL_VALUE(Image_tile_count)
#define Image_tile_lru_queue SPECIAL_VALUE(Image_tile_lru_queue)
#define Image_top_offset_in_ws SPECIAL_VALUE(Image_top_offset_in_ws)
#define Image_x_scale_for_finding_object_near_mouse SPECIAL_VALUE(Image_x_scale_for_finding_object_near_mouse)
#define Image_y_scale_for_finding_object_near_mouse SPECIAL_VALUE(Image_y_scale_for_finding_object_near_mouse)
#define In_clear_kb_p SPECIAL_VALUE(In_clear_kb_p)
#define In_edit_warning_context_p SPECIAL_VALUE(In_edit_warning_context_p)
#define In_external_definitions_for_module_p SPECIAL_VALUE(In_external_definitions_for_module_p)
#define In_find_stripped_text_slot_p SPECIAL_VALUE(In_find_stripped_text_slot_p)
#define In_line_evaluator_array SPECIAL_VALUE(In_line_evaluator_array)
#define In_local_source_code_control_scope_p SPECIAL_VALUE(In_local_source_code_control_scope_p)
#define In_non_top_level_context_qm SPECIAL_VALUE(In_non_top_level_context_qm)
#define In_recompile_item_p SPECIAL_VALUE(In_recompile_item_p)
#define In_recursive_gsi_context SPECIAL_VALUE(In_recursive_gsi_context)
#define In_suspend_resume_p SPECIAL_VALUE(In_suspend_resume_p)
#define In_text_for_item_or_value_p SPECIAL_VALUE(In_text_for_item_or_value_p)
#define In_unprotected_gsi_api_call_p SPECIAL_VALUE(In_unprotected_gsi_api_call_p)
#define In_write_module_as_clear_text_p SPECIAL_VALUE(In_write_module_as_clear_text_p)
#define Include_slots_visible_only_to_roles_p SPECIAL_VALUE(Include_slots_visible_only_to_roles_p)
#define Incomplete_painting_action_count SPECIAL_VALUE(Incomplete_painting_action_count)
#define Incomplete_phrase_count SPECIAL_VALUE(Incomplete_phrase_count)
#define Incomplete_phrases_at_frontier SPECIAL_VALUE(Incomplete_phrases_at_frontier)
#define Indent_sequences_and_structures_p SPECIAL_VALUE(Indent_sequences_and_structures_p)
#define Index_for_stop_time SPECIAL_VALUE(Index_for_stop_time)
#define Index_of_open_windows SPECIAL_VALUE(Index_of_open_windows)
#define Index_of_resumable_p_in_icp_buffer SPECIAL_VALUE(Index_of_resumable_p_in_icp_buffer)
#define Index_of_top_of_backtrace_stack SPECIAL_VALUE(Index_of_top_of_backtrace_stack)
#define Index_space_count SPECIAL_VALUE(Index_space_count)
#define Index_to_array_of_transfer_wrappers SPECIAL_VALUE(Index_to_array_of_transfer_wrappers)
#define Indexed_attributes SPECIAL_VALUE(Indexed_attributes)
#define Inference_background_collection_count SPECIAL_VALUE(Inference_background_collection_count)
#define Inference_engine_parameters SPECIAL_VALUE(Inference_engine_parameters)
#define Inform_message_information_count SPECIAL_VALUE(Inform_message_information_count)
#define Information_from_caught_signal SPECIAL_VALUE(Information_from_caught_signal)
#define Information_from_trapped_error SPECIAL_VALUE(Information_from_trapped_error)
#define Inhibit_corresponding_icp_object_making SPECIAL_VALUE(Inhibit_corresponding_icp_object_making)
#define Inhibit_free_reference_recording SPECIAL_VALUE(Inhibit_free_reference_recording)
#define Inhibit_icp_message_processing SPECIAL_VALUE(Inhibit_icp_message_processing)
#define Inhibit_icp_message_processing_enabled SPECIAL_VALUE(Inhibit_icp_message_processing_enabled)
#define Inhibit_icp_socket_reclamation SPECIAL_VALUE(Inhibit_icp_socket_reclamation)
#define Inhibit_model_install_qm SPECIAL_VALUE(Inhibit_model_install_qm)
#define Inhibit_modularity_consistency_checking_qm SPECIAL_VALUE(Inhibit_modularity_consistency_checking_qm)
#define Inhibit_non_real_time_clock_ticks_qm SPECIAL_VALUE(Inhibit_non_real_time_clock_ticks_qm)
#define Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm SPECIAL_VALUE(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm)
#define Init_orientation_horizontal_p SPECIAL_VALUE(Init_orientation_horizontal_p)
#define Initial_icp_version_info_enabled_p SPECIAL_VALUE(Initial_icp_version_info_enabled_p)
#define Initial_java_class SPECIAL_VALUE(Initial_java_class)
#define Initial_stack_offsets SPECIAL_VALUE(Initial_stack_offsets)
#define Initialization_inhibit SPECIAL_VALUE(Initialization_inhibit)
#define Initialize_gensym_window_after_connection_done SPECIAL_VALUE(Initialize_gensym_window_after_connection_done)
#define Initialize_items_count SPECIAL_VALUE(Initialize_items_count)
#define Initializing_clear_text_p SPECIAL_VALUE(Initializing_clear_text_p)
#define Initializing_compound_slot_qm SPECIAL_VALUE(Initializing_compound_slot_qm)
#define Initializing_items_needing_initialization SPECIAL_VALUE(Initializing_items_needing_initialization)
#define Initializing_simulator_qm SPECIAL_VALUE(Initializing_simulator_qm)
#define Initializing_state_variables_qm SPECIAL_VALUE(Initializing_state_variables_qm)
#define Inline_timeout_checks SPECIAL_VALUE(Inline_timeout_checks)
#define Inlining_data SPECIAL_VALUE(Inlining_data)
#define Inlining_data_holder_count SPECIAL_VALUE(Inlining_data_holder_count)
#define Inner_abort_level_tag SPECIAL_VALUE(Inner_abort_level_tag)
#define Inner_paint_loop_counter SPECIAL_VALUE(Inner_paint_loop_counter)
#define Input_gensym_string_for_buffer_for_internal_error_on_console SPECIAL_VALUE(Input_gensym_string_for_buffer_for_internal_error_on_console)
#define Input_gensym_string_for_buffer_for_string_metering SPECIAL_VALUE(Input_gensym_string_for_buffer_for_string_metering)
#define Input_gensym_string_for_gensym_error_message_buffer SPECIAL_VALUE(Input_gensym_string_for_gensym_error_message_buffer)
#define Input_string_for_backtrace_text_buffer_for_internal_error SPECIAL_VALUE(Input_string_for_backtrace_text_buffer_for_internal_error)
#define Input_string_for_backtrace_text_buffer_for_string_metering SPECIAL_VALUE(Input_string_for_backtrace_text_buffer_for_string_metering)
#define Input_string_for_buffer_for_internal_error_on_logbook SPECIAL_VALUE(Input_string_for_buffer_for_internal_error_on_logbook)
#define Input_string_for_buffer_for_write_internal_error SPECIAL_VALUE(Input_string_for_buffer_for_write_internal_error)
#define Input_table_spot_count SPECIAL_VALUE(Input_table_spot_count)
#define Insertion_location_for_embedded_expressions_qm SPECIAL_VALUE(Insertion_location_for_embedded_expressions_qm)
#define Inside_action_iteration_p SPECIAL_VALUE(Inside_action_iteration_p)
#define Inside_avoid_arithmetic_errors_p SPECIAL_VALUE(Inside_avoid_arithmetic_errors_p)
#define Inside_breakpoint_p SPECIAL_VALUE(Inside_breakpoint_p)
#define Inside_handle_event SPECIAL_VALUE(Inside_handle_event)
#define Inside_handling_gensym_file_errors_scope_p SPECIAL_VALUE(Inside_handling_gensym_file_errors_scope_p)
#define Inspect_command_class_description SPECIAL_VALUE(Inspect_command_class_description)
#define Inspect_command_for_modularity_problems_qm SPECIAL_VALUE(Inspect_command_for_modularity_problems_qm)
#define Inspect_command_history_list SPECIAL_VALUE(Inspect_command_history_list)
#define Inspect_command_spot_count SPECIAL_VALUE(Inspect_command_spot_count)
#define Inspection_instance_counter SPECIAL_VALUE(Inspection_instance_counter)
#define Install_item_in_model_if_appropriate SPECIAL_VALUE(Install_item_in_model_if_appropriate)
#define Installation_code_in_ok_file SPECIAL_VALUE(Installation_code_in_ok_file)
#define Installation_cons_counter SPECIAL_VALUE(Installation_cons_counter)
#define Integer_array_class_description SPECIAL_VALUE(Integer_array_class_description)
#define Integer_cv_count SPECIAL_VALUE(Integer_cv_count)
#define Integer_list_class_description SPECIAL_VALUE(Integer_list_class_description)
#define Integer_parameter_class_description SPECIAL_VALUE(Integer_parameter_class_description)
#define Integer_variable_class_description SPECIAL_VALUE(Integer_variable_class_description)
#define Intentionally_bogus_vector_for_g2_cause_asynchronous_abort SPECIAL_VALUE(Intentionally_bogus_vector_for_g2_cause_asynchronous_abort)
#define Inter_g2_data_request_queue_count SPECIAL_VALUE(Inter_g2_data_request_queue_count)
#define Interesting_blocks_found_in_search SPECIAL_VALUE(Interesting_blocks_found_in_search)
#define Intern_string_buffer SPECIAL_VALUE(Intern_string_buffer)
#define Internal_error_trapped_format_string SPECIAL_VALUE(Internal_error_trapped_format_string)
#define Internal_g2_element_types_that_can_contain_datum SPECIAL_VALUE(Internal_g2_element_types_that_can_contain_datum)
#define Internal_signal_caught_format_string SPECIAL_VALUE(Internal_signal_caught_format_string)
#define Internal_status_of_most_recent_file_operation SPECIAL_VALUE(Internal_status_of_most_recent_file_operation)
#define Internal_token_count SPECIAL_VALUE(Internal_token_count)
#define Interned_list_conses SPECIAL_VALUE(Interned_list_conses)
#define Interned_list_conses_in_use SPECIAL_VALUE(Interned_list_conses_in_use)
#define Interned_list_count SPECIAL_VALUE(Interned_list_count)
#define Interned_list_nil SPECIAL_VALUE(Interned_list_nil)
#define Interned_list_non_symbol_root SPECIAL_VALUE(Interned_list_non_symbol_root)
#define Interned_list_symbols SPECIAL_VALUE(Interned_list_symbols)
#define Interned_remote_procedure_item_passing_info_count SPECIAL_VALUE(Interned_remote_procedure_item_passing_info_count)
#define Interval_between_horizontal_grid_lines SPECIAL_VALUE(Interval_between_horizontal_grid_lines)
#define Interval_between_plot_markers SPECIAL_VALUE(Interval_between_plot_markers)
#define Interval_between_vertical_grid_lines SPECIAL_VALUE(Interval_between_vertical_grid_lines)
#define Interval_for_telewindows_modernization SPECIAL_VALUE(Interval_for_telewindows_modernization)
#define Invalid_address SPECIAL_VALUE(Invalid_address)
#define Invalid_spot_count SPECIAL_VALUE(Invalid_spot_count)
#define Invisible_entity_class_description SPECIAL_VALUE(Invisible_entity_class_description)
#define Is_g2_enterprise_qm SPECIAL_VALUE(Is_g2_enterprise_qm)
#define Is_icon_mask_drawing SPECIAL_VALUE(Is_icon_mask_drawing)
#define Iso_2022_transcoder_count SPECIAL_VALUE(Iso_2022_transcoder_count)
#define Iso_646_count SPECIAL_VALUE(Iso_646_count)
#define Iso_8859_10_count SPECIAL_VALUE(Iso_8859_10_count)
#define Iso_8859_1_count SPECIAL_VALUE(Iso_8859_1_count)
#define Iso_8859_2_count SPECIAL_VALUE(Iso_8859_2_count)
#define Iso_8859_3_count SPECIAL_VALUE(Iso_8859_3_count)
#define Iso_8859_4_count SPECIAL_VALUE(Iso_8859_4_count)
#define Iso_8859_5_count SPECIAL_VALUE(Iso_8859_5_count)
#define Iso_8859_6_count SPECIAL_VALUE(Iso_8859_6_count)
#define Iso_8859_7_count SPECIAL_VALUE(Iso_8859_7_count)
#define Iso_8859_8_count SPECIAL_VALUE(Iso_8859_8_count)
#define Iso_8859_9_count SPECIAL_VALUE(Iso_8859_9_count)
#define Iso_8859_abstract_count SPECIAL_VALUE(Iso_8859_abstract_count)
#define Iso_8859_transcoder_count SPECIAL_VALUE(Iso_8859_transcoder_count)
#define Iso_latin1_special_character_code_map SPECIAL_VALUE(Iso_latin1_special_character_code_map)
#define Item_access_cache_count SPECIAL_VALUE(Item_access_cache_count)
#define Item_array_class_description SPECIAL_VALUE(Item_array_class_description)
#define Item_being_read_for_new_reference SPECIAL_VALUE(Item_being_read_for_new_reference)
#define Item_class_description SPECIAL_VALUE(Item_class_description)
#define Item_color_pattern_returns_overrides_only_p SPECIAL_VALUE(Item_color_pattern_returns_overrides_only_p)
#define Item_copy_handle_for_root_item SPECIAL_VALUE(Item_copy_handle_for_root_item)
#define Item_copy_index_space SPECIAL_VALUE(Item_copy_index_space)
#define Item_copy_root_item SPECIAL_VALUE(Item_copy_root_item)
#define Item_copy_rpc_item_info SPECIAL_VALUE(Item_copy_rpc_item_info)
#define Item_list_class_description SPECIAL_VALUE(Item_list_class_description)
#define Item_represented_by_table_spot_count SPECIAL_VALUE(Item_represented_by_table_spot_count)
#define Items_deleted_since_load_or_save SPECIAL_VALUE(Items_deleted_since_load_or_save)
#define Items_deleted_since_load_or_save_tail SPECIAL_VALUE(Items_deleted_since_load_or_save_tail)
#define Items_encountered_in_memory_walk SPECIAL_VALUE(Items_encountered_in_memory_walk)
#define Items_made_incomplete SPECIAL_VALUE(Items_made_incomplete)
#define Items_made_incomplete_were_recorded_qm SPECIAL_VALUE(Items_made_incomplete_were_recorded_qm)
#define Items_needing_initialization SPECIAL_VALUE(Items_needing_initialization)
#define Items_needing_initialization_tree SPECIAL_VALUE(Items_needing_initialization_tree)
#define Items_to_traverse SPECIAL_VALUE(Items_to_traverse)
#define Items_warned_in_edit_warning_context SPECIAL_VALUE(Items_warned_in_edit_warning_context)
#define Iteration_forms_for_embedded_expressions_qm SPECIAL_VALUE(Iteration_forms_for_embedded_expressions_qm)
#define Java_class_count SPECIAL_VALUE(Java_class_count)
#define Java_code_count SPECIAL_VALUE(Java_code_count)
#define Java_code_exception_count SPECIAL_VALUE(Java_code_exception_count)
#define Java_cons_counter SPECIAL_VALUE(Java_cons_counter)
#define Java_descriptor_count SPECIAL_VALUE(Java_descriptor_count)
#define Java_editing_categories SPECIAL_VALUE(Java_editing_categories)
#define Java_field_count SPECIAL_VALUE(Java_field_count)
#define Java_grammar_stream_qm SPECIAL_VALUE(Java_grammar_stream_qm)
#define Java_method_count SPECIAL_VALUE(Java_method_count)
#define Java_symbol_count SPECIAL_VALUE(Java_symbol_count)
#define Java_tokenizer SPECIAL_VALUE(Java_tokenizer)
#define Javalink_notification_versions SPECIAL_VALUE(Javalink_notification_versions)
#define Javalink_versioned_call_data_count SPECIAL_VALUE(Javalink_versioned_call_data_count)
#define Jis_x_0208_count SPECIAL_VALUE(Jis_x_0208_count)
#define Joes_graph_hax_p SPECIAL_VALUE(Joes_graph_hax_p)
#define Joes_graph_hax_trace_p SPECIAL_VALUE(Joes_graph_hax_trace_p)
#define Journal_cons_counter SPECIAL_VALUE(Journal_cons_counter)
#define Journal_shutout_scan_p SPECIAL_VALUE(Journal_shutout_scan_p)
#define Junction_blocks_not_to_be_deleted SPECIAL_VALUE(Junction_blocks_not_to_be_deleted)
#define Just_update_representations_of_slot_value SPECIAL_VALUE(Just_update_representations_of_slot_value)
#define Kana_to_ascii_map SPECIAL_VALUE(Kana_to_ascii_map)
#define Kanji_fonts_used_in_print_job SPECIAL_VALUE(Kanji_fonts_used_in_print_job)
#define Kanji_row_to_font_file_name_mapping_vector SPECIAL_VALUE(Kanji_row_to_font_file_name_mapping_vector)
#define Kb_configuration SPECIAL_VALUE(Kb_configuration)
#define Kb_file_progress SPECIAL_VALUE(Kb_file_progress)
#define Kb_file_progress_is_currently_for_modules_p SPECIAL_VALUE(Kb_file_progress_is_currently_for_modules_p)
#define Kb_flags SPECIAL_VALUE(Kb_flags)
#define Kb_flags_for_saving SPECIAL_VALUE(Kb_flags_for_saving)
#define Kb_flags_from_last_kb_read SPECIAL_VALUE(Kb_flags_from_last_kb_read)
#define Kb_format_identifier_read_qm SPECIAL_VALUE(Kb_format_identifier_read_qm)
#define Kb_format_write_integer_buffer SPECIAL_VALUE(Kb_format_write_integer_buffer)
#define Kb_frame_class_description SPECIAL_VALUE(Kb_frame_class_description)
#define Kb_load_case_qm SPECIAL_VALUE(Kb_load_case_qm)
#define Kb_module_currently_to_save_qm SPECIAL_VALUE(Kb_module_currently_to_save_qm)
#define Kb_object_index_property_name_pool SPECIAL_VALUE(Kb_object_index_property_name_pool)
#define Kb_object_index_space SPECIAL_VALUE(Kb_object_index_space)
#define Kb_procedure_completion_form_qm SPECIAL_VALUE(Kb_procedure_completion_form_qm)
#define Kb_property_cons_counter SPECIAL_VALUE(Kb_property_cons_counter)
#define Kb_restrictions SPECIAL_VALUE(Kb_restrictions)
#define Kb_restrictions_names SPECIAL_VALUE(Kb_restrictions_names)
#define Kb_save_count SPECIAL_VALUE(Kb_save_count)
#define Kb_save_termination_reason_qm SPECIAL_VALUE(Kb_save_termination_reason_qm)
#define Kb_serial_number_before_loading_this_group SPECIAL_VALUE(Kb_serial_number_before_loading_this_group)
#define Kb_state_changes SPECIAL_VALUE(Kb_state_changes)
#define Kb_transfer_count SPECIAL_VALUE(Kb_transfer_count)
#define Kb_uses_crlf_p SPECIAL_VALUE(Kb_uses_crlf_p)
#define Kb_window_for_initializing_definitions SPECIAL_VALUE(Kb_window_for_initializing_definitions)
#define Kb_workspace_class_description SPECIAL_VALUE(Kb_workspace_class_description)
#define Kb_workspace_image_plane_spot_count SPECIAL_VALUE(Kb_workspace_image_plane_spot_count)
#define Keep_edit_workspace_hidden_no_matter_what_qm SPECIAL_VALUE(Keep_edit_workspace_hidden_no_matter_what_qm)
#define Key_cap_to_gensym_cyrillic_character_code_map SPECIAL_VALUE(Key_cap_to_gensym_cyrillic_character_code_map)
#define Key_index_to_key_symbol_array SPECIAL_VALUE(Key_index_to_key_symbol_array)
#define Key_index_to_lisp_character_array SPECIAL_VALUE(Key_index_to_lisp_character_array)
#define Keytab1 SPECIAL_VALUE(Keytab1)
#define Keyword_package_1 SPECIAL_VALUE(Keyword_package_1)
#define Kfep_batch_count SPECIAL_VALUE(Kfep_batch_count)
#define Kfep_batchyomi SPECIAL_VALUE(Kfep_batchyomi)
#define Kfep_batchyomilen SPECIAL_VALUE(Kfep_batchyomilen)
#define Kfep_battable SPECIAL_VALUE(Kfep_battable)
#define Kfep_capability_qm SPECIAL_VALUE(Kfep_capability_qm)
#define Kfep_conversion_choice_menu_button_spot_count SPECIAL_VALUE(Kfep_conversion_choice_menu_button_spot_count)
#define Kfep_conversion_choice_menu_class_description SPECIAL_VALUE(Kfep_conversion_choice_menu_class_description)
#define Kfep_converters_have_been_initialized_qm SPECIAL_VALUE(Kfep_converters_have_been_initialized_qm)
#define Kfep_ghyoki_hptr SPECIAL_VALUE(Kfep_ghyoki_hptr)
#define Kfep_ghyoki_idxbuf SPECIAL_VALUE(Kfep_ghyoki_idxbuf)
#define Kfep_ghyoki_idxbuf_cache_alist SPECIAL_VALUE(Kfep_ghyoki_idxbuf_cache_alist)
#define Kfep_ghyoki_savtblnum SPECIAL_VALUE(Kfep_ghyoki_savtblnum)
#define Kfep_hensaisyo_getpos SPECIAL_VALUE(Kfep_hensaisyo_getpos)
#define Kfep_hensaisyo_gonum SPECIAL_VALUE(Kfep_hensaisyo_gonum)
#define Kfep_hensaisyo_saventry SPECIAL_VALUE(Kfep_hensaisyo_saventry)
#define Kfep_hensaisyo_tno SPECIAL_VALUE(Kfep_hensaisyo_tno)
#define Kfep_index_file_stream SPECIAL_VALUE(Kfep_index_file_stream)
#define Kfep_kka_p_batkanakan_position SPECIAL_VALUE(Kfep_kka_p_batkanakan_position)
#define Kfep_kka_usetblnum SPECIAL_VALUE(Kfep_kka_usetblnum)
#define Kfep_kojin_bunpobits SPECIAL_VALUE(Kfep_kojin_bunpobits)
#define Kfep_kojin_file_stream SPECIAL_VALUE(Kfep_kojin_file_stream)
#define Kfep_kojin_header SPECIAL_VALUE(Kfep_kojin_header)
#define Kfep_kojin_hyolen SPECIAL_VALUE(Kfep_kojin_hyolen)
#define Kfep_kojin_index SPECIAL_VALUE(Kfep_kojin_index)
#define Kfep_kojin_usedbits SPECIAL_VALUE(Kfep_kojin_usedbits)
#define Kfep_m_table SPECIAL_VALUE(Kfep_m_table)
#define Kfep_main_file_stream SPECIAL_VALUE(Kfep_main_file_stream)
#define Kfep_master_count SPECIAL_VALUE(Kfep_master_count)
#define Kfep_master_header SPECIAL_VALUE(Kfep_master_header)
#define Kfep_master_header_in_characters SPECIAL_VALUE(Kfep_master_header_in_characters)
#define Kfep_search_limit_1 SPECIAL_VALUE(Kfep_search_limit_1)
#define Kfep_search_limit_2 SPECIAL_VALUE(Kfep_search_limit_2)
#define Kfep_tablemax SPECIAL_VALUE(Kfep_tablemax)
#define Known_gensym_acronyms SPECIAL_VALUE(Known_gensym_acronyms)
#define Known_localizations SPECIAL_VALUE(Known_localizations)
#define Known_process_ids_qm SPECIAL_VALUE(Known_process_ids_qm)
#define Known_regexp_functions SPECIAL_VALUE(Known_regexp_functions)
#define Ks_c_5601_count SPECIAL_VALUE(Ks_c_5601_count)
#define Ksc_contiguous_character_group_lengths SPECIAL_VALUE(Ksc_contiguous_character_group_lengths)
#define Label_box_spot_count SPECIAL_VALUE(Label_box_spot_count)
#define Label_scale_for_vertical_grid_lines SPECIAL_VALUE(Label_scale_for_vertical_grid_lines)
#define Language_parameters SPECIAL_VALUE(Language_parameters)
#define Language_translation_class_description SPECIAL_VALUE(Language_translation_class_description)
#define Large_byte_vector SPECIAL_VALUE(Large_byte_vector)
#define Large_scaled_font_bucket_count SPECIAL_VALUE(Large_scaled_font_bucket_count)
#define Largest_non_malloced_byte_vector_16_pool_index SPECIAL_VALUE(Largest_non_malloced_byte_vector_16_pool_index)
#define Largest_non_malloced_string_pool_index SPECIAL_VALUE(Largest_non_malloced_string_pool_index)
#define Last_assigned_category_index SPECIAL_VALUE(Last_assigned_category_index)
#define Last_assigned_global_kb_number SPECIAL_VALUE(Last_assigned_global_kb_number)
#define Last_assigned_grammar_number SPECIAL_VALUE(Last_assigned_grammar_number)
#define Last_assigned_kb_serial_number SPECIAL_VALUE(Last_assigned_kb_serial_number)
#define Last_bootstrap_mode_qm SPECIAL_VALUE(Last_bootstrap_mode_qm)
#define Last_deletable_token_in_namestring SPECIAL_VALUE(Last_deletable_token_in_namestring)
#define Last_event_socket_handle SPECIAL_VALUE(Last_event_socket_handle)
#define Last_event_socket_handle_holder SPECIAL_VALUE(Last_event_socket_handle_holder)
#define Last_event_status_code SPECIAL_VALUE(Last_event_status_code)
#define Last_event_status_code_0 SPECIAL_VALUE(Last_event_status_code_0)
#define Last_event_status_code_1 SPECIAL_VALUE(Last_event_status_code_1)
#define Last_event_status_code_holder SPECIAL_VALUE(Last_event_status_code_holder)
#define Last_gsi_timestamp_day SPECIAL_VALUE(Last_gsi_timestamp_day)
#define Last_gsi_timestamp_hour SPECIAL_VALUE(Last_gsi_timestamp_hour)
#define Last_gsi_timestamp_month SPECIAL_VALUE(Last_gsi_timestamp_month)
#define Last_gsi_timestamp_unix_time SPECIAL_VALUE(Last_gsi_timestamp_unix_time)
#define Last_gsi_timestamp_year SPECIAL_VALUE(Last_gsi_timestamp_year)
#define Last_history_time_for_data_point_on_pixel SPECIAL_VALUE(Last_history_time_for_data_point_on_pixel)
#define Last_image_plane_serial_number SPECIAL_VALUE(Last_image_plane_serial_number)
#define Last_memory_stats_snapshot SPECIAL_VALUE(Last_memory_stats_snapshot)
#define Last_part_features_index_allocated SPECIAL_VALUE(Last_part_features_index_allocated)
#define Last_player_event_time SPECIAL_VALUE(Last_player_event_time)
#define Last_player_mouse_x SPECIAL_VALUE(Last_player_mouse_x)
#define Last_player_mouse_y SPECIAL_VALUE(Last_player_mouse_y)
#define Last_postscript_composite_object_index SPECIAL_VALUE(Last_postscript_composite_object_index)
#define Last_reason_for_complex_type_rejection SPECIAL_VALUE(Last_reason_for_complex_type_rejection)
#define Last_roman_kana_g2_length SPECIAL_VALUE(Last_roman_kana_g2_length)
#define Last_roman_kata_g2_length SPECIAL_VALUE(Last_roman_kata_g2_length)
#define Last_semantic_check_error_string SPECIAL_VALUE(Last_semantic_check_error_string)
#define Last_slot_checked_of_type_failure SPECIAL_VALUE(Last_slot_checked_of_type_failure)
#define Last_source_line SPECIAL_VALUE(Last_source_line)
#define Last_system_class_bit_number SPECIAL_VALUE(Last_system_class_bit_number)
#define Last_ui_callback_handle SPECIAL_VALUE(Last_ui_callback_handle)
#define Last_workstation_serviced SPECIAL_VALUE(Last_workstation_serviced)
#define Launch_recompile_for_compilations_removed_in_this_kb_qm SPECIAL_VALUE(Launch_recompile_for_compilations_removed_in_this_kb_qm)
#define Layer_box_count SPECIAL_VALUE(Layer_box_count)
#define Lazy_assignment_of_uuids SPECIAL_VALUE(Lazy_assignment_of_uuids)
#define Leak_list SPECIAL_VALUE(Leak_list)
#define Learned_list_to_expedite_ui SPECIAL_VALUE(Learned_list_to_expedite_ui)
#define Leave_text_representation_as_a_single_line_qm SPECIAL_VALUE(Leave_text_representation_as_a_single_line_qm)
#define Left_braket_written_qm SPECIAL_VALUE(Left_braket_written_qm)
#define Left_edge_in_window_of_graphic_element SPECIAL_VALUE(Left_edge_in_window_of_graphic_element)
#define Left_edge_of_draw_area SPECIAL_VALUE(Left_edge_of_draw_area)
#define Left_edge_of_frame SPECIAL_VALUE(Left_edge_of_frame)
#define Left_edge_of_line_of_text_in_window_of_graphic_element SPECIAL_VALUE(Left_edge_of_line_of_text_in_window_of_graphic_element)
#define Left_marker_for_cascading_menu_rubber_stamp_widget SPECIAL_VALUE(Left_marker_for_cascading_menu_rubber_stamp_widget)
#define Left_scroll_arrow_rubber_stamp_widget SPECIAL_VALUE(Left_scroll_arrow_rubber_stamp_widget)
#define Legacy_subsecond_heartbeat_adjustment_interval SPECIAL_VALUE(Legacy_subsecond_heartbeat_adjustment_interval)
#define Legend_pane_count SPECIAL_VALUE(Legend_pane_count)
#define Length_of_most_negative_fixnum_as_string SPECIAL_VALUE(Length_of_most_negative_fixnum_as_string)
#define Length_of_xml_output_line SPECIAL_VALUE(Length_of_xml_output_line)
#define Level_of_group_kb_read SPECIAL_VALUE(Level_of_group_kb_read)
#define Lexically_visible_code_bodies SPECIAL_VALUE(Lexically_visible_code_bodies)
#define Lexically_visible_goto_tags SPECIAL_VALUE(Lexically_visible_goto_tags)
#define Lexing_table_count SPECIAL_VALUE(Lexing_table_count)
#define Lfsi_bound_marker SPECIAL_VALUE(Lfsi_bound_marker)
#define Lfsi_label_index_space SPECIAL_VALUE(Lfsi_label_index_space)
#define Lfsi_local_var_index_space SPECIAL_VALUE(Lfsi_local_var_index_space)
#define Lfsi_stack_var_index_space SPECIAL_VALUE(Lfsi_stack_var_index_space)
#define Lfsi_unbound_marker SPECIAL_VALUE(Lfsi_unbound_marker)
#define Limit_dos_filename_component_lengths_p SPECIAL_VALUE(Limit_dos_filename_component_lengths_p)
#define Limit_profiling_based_on_licence_level_p SPECIAL_VALUE(Limit_profiling_based_on_licence_level_p)
#define Line_drawing_for_printing_count SPECIAL_VALUE(Line_drawing_for_printing_count)
#define Line_number_of_ok_file_reader SPECIAL_VALUE(Line_number_of_ok_file_reader)
#define Links_and_objects SPECIAL_VALUE(Links_and_objects)
#define Lisp_character_to_key_index_alist SPECIAL_VALUE(Lisp_character_to_key_index_alist)
#define Lisp_grid_view_count SPECIAL_VALUE(Lisp_grid_view_count)
#define Lisp_highest_printable_character_code SPECIAL_VALUE(Lisp_highest_printable_character_code)
#define Lisp_int_character_to_key_index_array SPECIAL_VALUE(Lisp_int_character_to_key_index_array)
#define Lisp_memory_expanded_qm SPECIAL_VALUE(Lisp_memory_expanded_qm)
#define Lisp_package_1 SPECIAL_VALUE(Lisp_package_1)
#define List_box_cv_count SPECIAL_VALUE(List_box_cv_count)
#define List_for_import SPECIAL_VALUE(List_for_import)
#define List_of_all_data_servers SPECIAL_VALUE(List_of_all_data_servers)
#define List_of_all_g2ds_interfaces SPECIAL_VALUE(List_of_all_g2ds_interfaces)
#define List_of_all_gsi_interfaces SPECIAL_VALUE(List_of_all_gsi_interfaces)
#define List_of_already_defined_tokenizer_matching_tests SPECIAL_VALUE(List_of_already_defined_tokenizer_matching_tests)
#define List_of_argument_lists_to_add_menu_items_for_category SPECIAL_VALUE(List_of_argument_lists_to_add_menu_items_for_category)
#define List_of_bad_status_compiler_frame_note_types SPECIAL_VALUE(List_of_bad_status_compiler_frame_note_types)
#define List_of_compiler_frame_note_types SPECIAL_VALUE(List_of_compiler_frame_note_types)
#define List_of_connection_roles SPECIAL_VALUE(List_of_connection_roles)
#define List_of_exported_method_texts SPECIAL_VALUE(List_of_exported_method_texts)
#define List_of_expressions_for_compilation SPECIAL_VALUE(List_of_expressions_for_compilation)
#define List_of_for_structures SPECIAL_VALUE(List_of_for_structures)
#define List_of_funcalled_functions SPECIAL_VALUE(List_of_funcalled_functions)
#define List_of_g2ds_values_to_process_head SPECIAL_VALUE(List_of_g2ds_values_to_process_head)
#define List_of_g2ds_values_to_process_tail SPECIAL_VALUE(List_of_g2ds_values_to_process_tail)
#define List_of_generated_contexts SPECIAL_VALUE(List_of_generated_contexts)
#define List_of_generated_contexts_tail SPECIAL_VALUE(List_of_generated_contexts_tail)
#define List_of_grid_attributes SPECIAL_VALUE(List_of_grid_attributes)
#define List_of_grid_tokens SPECIAL_VALUE(List_of_grid_tokens)
#define List_of_gsi_values_to_process_head SPECIAL_VALUE(List_of_gsi_values_to_process_head)
#define List_of_gsi_values_to_process_tail SPECIAL_VALUE(List_of_gsi_values_to_process_tail)
#define List_of_known_names SPECIAL_VALUE(List_of_known_names)
#define List_of_module_pre_conflict_resolution_post_loading_functions SPECIAL_VALUE(List_of_module_pre_conflict_resolution_post_loading_functions)
#define List_of_once_only_post_conflict_resolution_post_loading_functions SPECIAL_VALUE(List_of_once_only_post_conflict_resolution_post_loading_functions)
#define List_of_once_only_pre_conflict_resolution_post_loading_functions SPECIAL_VALUE(List_of_once_only_pre_conflict_resolution_post_loading_functions)
#define List_of_once_only_switched_post_loading_functions SPECIAL_VALUE(List_of_once_only_switched_post_loading_functions)
#define List_of_previously_optimized_procedures SPECIAL_VALUE(List_of_previously_optimized_procedures)
#define List_of_reference_structures SPECIAL_VALUE(List_of_reference_structures)
#define List_of_switched_and_module_post_loading_functions SPECIAL_VALUE(List_of_switched_and_module_post_loading_functions)
#define List_of_symbols_for_symbol_value SPECIAL_VALUE(List_of_symbols_for_symbol_value)
#define List_of_types_to_be_analyzed SPECIAL_VALUE(List_of_types_to_be_analyzed)
#define List_of_user_overridable_system_slots SPECIAL_VALUE(List_of_user_overridable_system_slots)
#define Listed_continuation_servers SPECIAL_VALUE(Listed_continuation_servers)
#define Listed_print_to_server_command SPECIAL_VALUE(Listed_print_to_server_command)
#define Loading_compiled_kb_p SPECIAL_VALUE(Loading_compiled_kb_p)
#define Loading_kb_p SPECIAL_VALUE(Loading_kb_p)
#define Local_event_count SPECIAL_VALUE(Local_event_count)
#define Local_file_system SPECIAL_VALUE(Local_file_system)
#define Local_filename_parser SPECIAL_VALUE(Local_filename_parser)
#define Local_host_name SPECIAL_VALUE(Local_host_name)
#define Local_insertion_location SPECIAL_VALUE(Local_insertion_location)
#define Local_iteration_forms SPECIAL_VALUE(Local_iteration_forms)
#define Local_name_errors SPECIAL_VALUE(Local_name_errors)
#define Local_name_to_cached_designation_alist SPECIAL_VALUE(Local_name_to_cached_designation_alist)
#define Local_names_not_associated_with_roles SPECIAL_VALUE(Local_names_not_associated_with_roles)
#define Local_namestring_generator SPECIAL_VALUE(Local_namestring_generator)
#define Local_nupec_variable_count SPECIAL_VALUE(Local_nupec_variable_count)
#define Local_paste_event_queue SPECIAL_VALUE(Local_paste_event_queue)
#define Local_source_code_control_buffer SPECIAL_VALUE(Local_source_code_control_buffer)
#define Local_source_code_control_number_of_characters SPECIAL_VALUE(Local_source_code_control_number_of_characters)
#define Local_ui_client_test_mode_p SPECIAL_VALUE(Local_ui_client_test_mode_p)
#define Localization_context SPECIAL_VALUE(Localization_context)
#define Locked_to_kb_qm SPECIAL_VALUE(Locked_to_kb_qm)
#define Log_file_count SPECIAL_VALUE(Log_file_count)
#define Log_file_default_pathname_qm SPECIAL_VALUE(Log_file_default_pathname_qm)
#define Log_file_message_count SPECIAL_VALUE(Log_file_message_count)
#define Log_file_message_count_at_last_update SPECIAL_VALUE(Log_file_message_count_at_last_update)
#define Log_file_outputting_qm SPECIAL_VALUE(Log_file_outputting_qm)
#define Log_file_parameters SPECIAL_VALUE(Log_file_parameters)
#define Log_file_pathnames SPECIAL_VALUE(Log_file_pathnames)
#define Log_file_stream SPECIAL_VALUE(Log_file_stream)
#define Log_file_string SPECIAL_VALUE(Log_file_string)
#define Log_file_time_at_last_update SPECIAL_VALUE(Log_file_time_at_last_update)
#define Log_file_time_at_open SPECIAL_VALUE(Log_file_time_at_open)
#define Log_file_writing_message_qm SPECIAL_VALUE(Log_file_writing_message_qm)
#define Log_post_mortem_ring_buffer_to_file_p SPECIAL_VALUE(Log_post_mortem_ring_buffer_to_file_p)
#define Log_simple_string_data SPECIAL_VALUE(Log_simple_string_data)
#define Log_simple_string_reclaims SPECIAL_VALUE(Log_simple_string_reclaims)
#define Logbook_page_class_description SPECIAL_VALUE(Logbook_page_class_description)
#define Logbook_parameters SPECIAL_VALUE(Logbook_parameters)
#define Logbook_view_count SPECIAL_VALUE(Logbook_view_count)
#define Logical_parameter_class_description SPECIAL_VALUE(Logical_parameter_class_description)
#define Logical_variable_class_description SPECIAL_VALUE(Logical_variable_class_description)
#define Login_handler SPECIAL_VALUE(Login_handler)
#define Login_handler_fsn SPECIAL_VALUE(Login_handler_fsn)
#define Long_array_cons_counter SPECIAL_VALUE(Long_array_cons_counter)
#define Long_operation_notification_has_been_put_up_qm SPECIAL_VALUE(Long_operation_notification_has_been_put_up_qm)
#define Long_simple_gensym_string_counts SPECIAL_VALUE(Long_simple_gensym_string_counts)
#define Long_simple_gensym_strings SPECIAL_VALUE(Long_simple_gensym_strings)
#define Long_thrashing_cost_update_interval SPECIAL_VALUE(Long_thrashing_cost_update_interval)
#define Long_variable_class_description SPECIAL_VALUE(Long_variable_class_description)
#define Lookup_cons_counter SPECIAL_VALUE(Lookup_cons_counter)
#define Loose_bottom_edge_of_visible_workspace_area SPECIAL_VALUE(Loose_bottom_edge_of_visible_workspace_area)
#define Loose_end_class_description SPECIAL_VALUE(Loose_end_class_description)
#define Loose_end_spot_count SPECIAL_VALUE(Loose_end_spot_count)
#define Loose_left_edge_of_visible_workspace_area SPECIAL_VALUE(Loose_left_edge_of_visible_workspace_area)
#define Loose_right_edge_of_visible_workspace_area SPECIAL_VALUE(Loose_right_edge_of_visible_workspace_area)
#define Loose_top_edge_of_visible_workspace_area SPECIAL_VALUE(Loose_top_edge_of_visible_workspace_area)
#define Low_and_high_values_specified_for_vertical_axis_qm SPECIAL_VALUE(Low_and_high_values_specified_for_vertical_axis_qm)
#define Low_bound_system_variable_for_get_current_bounds_for_plot SPECIAL_VALUE(Low_bound_system_variable_for_get_current_bounds_for_plot)
#define Low_bound_system_variable_for_get_current_min_and_max_for_plot_from_history SPECIAL_VALUE(Low_bound_system_variable_for_get_current_min_and_max_for_plot_from_history)
#define Low_value_for_horizontal_axis SPECIAL_VALUE(Low_value_for_horizontal_axis)
#define Low_value_for_horizontal_grid_lines SPECIAL_VALUE(Low_value_for_horizontal_grid_lines)
#define Low_value_for_vertical_axis SPECIAL_VALUE(Low_value_for_vertical_axis)
#define Low_value_for_vertical_grid_lines SPECIAL_VALUE(Low_value_for_vertical_grid_lines)
#define Lower_match_rank_for_player_eyes_p SPECIAL_VALUE(Lower_match_rank_for_player_eyes_p)
#define Lr0_follow SPECIAL_VALUE(Lr0_follow)
#define Lru_element_count SPECIAL_VALUE(Lru_element_count)
#define Lt_asterisk_gt SPECIAL_VALUE(Lt_asterisk_gt)
#define Lt_backslash_gt SPECIAL_VALUE(Lt_backslash_gt)
#define Lt_colon_gt SPECIAL_VALUE(Lt_colon_gt)
#define Lt_comma_gt SPECIAL_VALUE(Lt_comma_gt)
#define Lt_dot_gt SPECIAL_VALUE(Lt_dot_gt)
#define Lt_double_quote_gt SPECIAL_VALUE(Lt_double_quote_gt)
#define Lt_end_of_sequence_gt SPECIAL_VALUE(Lt_end_of_sequence_gt)
#define Lt_exclamation_gt SPECIAL_VALUE(Lt_exclamation_gt)
#define Lt_hyphen_gt SPECIAL_VALUE(Lt_hyphen_gt)
#define Lt_left_angle_bracket_gt SPECIAL_VALUE(Lt_left_angle_bracket_gt)
#define Lt_left_bracket_gt SPECIAL_VALUE(Lt_left_bracket_gt)
#define Lt_right_angle_bracket_gt SPECIAL_VALUE(Lt_right_angle_bracket_gt)
#define Lt_right_bracket_gt SPECIAL_VALUE(Lt_right_bracket_gt)
#define Lt_semicolon_gt SPECIAL_VALUE(Lt_semicolon_gt)
#define Lt_sharp_sign_gt SPECIAL_VALUE(Lt_sharp_sign_gt)
#define Lt_slash_gt SPECIAL_VALUE(Lt_slash_gt)
#define Lt_space_gt SPECIAL_VALUE(Lt_space_gt)
#define Lt_tilde_gt SPECIAL_VALUE(Lt_tilde_gt)
#define Machine_model_var SPECIAL_VALUE(Machine_model_var)
#define Macroexpanding_for_instruction_expander SPECIAL_VALUE(Macroexpanding_for_instruction_expander)
#define Main_kb_being_read_qm SPECIAL_VALUE(Main_kb_being_read_qm)
#define Main_menu_choices SPECIAL_VALUE(Main_menu_choices)
#define Main_model_runtime_info SPECIAL_VALUE(Main_model_runtime_info)
#define Maintain_stack_of_current_part_descriptions_p SPECIAL_VALUE(Maintain_stack_of_current_part_descriptions_p)
#define Maintaining_g2ds_interface_status_changed_p SPECIAL_VALUE(Maintaining_g2ds_interface_status_changed_p)
#define Maintaining_gsi_interface_status_changed_p SPECIAL_VALUE(Maintaining_gsi_interface_status_changed_p)
#define Make_gsi_instance_existing_instance SPECIAL_VALUE(Make_gsi_instance_existing_instance)
#define Making_distribution_system_qm SPECIAL_VALUE(Making_distribution_system_qm)
#define Managed_bignum_pool SPECIAL_VALUE(Managed_bignum_pool)
#define Many_more_data_points_than_pixels_qm SPECIAL_VALUE(Many_more_data_points_than_pixels_qm)
#define Mark_for_modules_with_unsaved_changes SPECIAL_VALUE(Mark_for_modules_with_unsaved_changes)
#define Marker_for_meter_class_description SPECIAL_VALUE(Marker_for_meter_class_description)
#define Master_hierarchy_reconciliation_switches SPECIAL_VALUE(Master_hierarchy_reconciliation_switches)
#define Match_pattern_for_inspect_binding_vector SPECIAL_VALUE(Match_pattern_for_inspect_binding_vector)
#define Match_regular_expression_for_g2_stream_directory_hook SPECIAL_VALUE(Match_regular_expression_for_g2_stream_directory_hook)
#define Max_gsi_sensors_in_a_group SPECIAL_VALUE(Max_gsi_sensors_in_a_group)
#define Max_stack_index SPECIAL_VALUE(Max_stack_index)
#define Max_var_index SPECIAL_VALUE(Max_var_index)
#define Maximum_clock_tick_length SPECIAL_VALUE(Maximum_clock_tick_length)
#define Maximum_file_name_length_qm SPECIAL_VALUE(Maximum_file_name_length_qm)
#define Maximum_height SPECIAL_VALUE(Maximum_height)
#define Maximum_length_for_sax_strings SPECIAL_VALUE(Maximum_length_for_sax_strings)
#define Maximum_length_of_ascii_string SPECIAL_VALUE(Maximum_length_of_ascii_string)
#define Maximum_length_of_kana_string SPECIAL_VALUE(Maximum_length_of_kana_string)
#define Maximum_log_file_name_prefix_length_qm SPECIAL_VALUE(Maximum_log_file_name_prefix_length_qm)
#define Maximum_number_of_array_or_list_elements_to_describe SPECIAL_VALUE(Maximum_number_of_array_or_list_elements_to_describe)
#define Maximum_number_of_slots_in_structure_type SPECIAL_VALUE(Maximum_number_of_slots_in_structure_type)
#define Maximum_number_of_tries_to_create_temp_file SPECIAL_VALUE(Maximum_number_of_tries_to_create_temp_file)
#define Maximum_object_passing_bandwidth SPECIAL_VALUE(Maximum_object_passing_bandwidth)
#define Maximum_region_complexity SPECIAL_VALUE(Maximum_region_complexity)
#define Maximum_retries_for_foreign_image_connection SPECIAL_VALUE(Maximum_retries_for_foreign_image_connection)
#define Maximum_significant_decimal_digits_in_gensym_float SPECIAL_VALUE(Maximum_significant_decimal_digits_in_gensym_float)
#define Maximum_time_slice_size SPECIAL_VALUE(Maximum_time_slice_size)
#define Maximum_width SPECIAL_VALUE(Maximum_width)
#define Maximum_x_value_for_new_data SPECIAL_VALUE(Maximum_x_value_for_new_data)
#define Maximum_y_value SPECIAL_VALUE(Maximum_y_value)
#define Maximum_y_value_for_new_data SPECIAL_VALUE(Maximum_y_value_for_new_data)
#define Maximum_y_value_for_pixel SPECIAL_VALUE(Maximum_y_value_for_pixel)
#define May_create_simulation_subtable_from_module_data_p SPECIAL_VALUE(May_create_simulation_subtable_from_module_data_p)
#define May_return_from_breakpoint SPECIAL_VALUE(May_return_from_breakpoint)
#define Media_stream_count SPECIAL_VALUE(Media_stream_count)
#define Memory_category_count SPECIAL_VALUE(Memory_category_count)
#define Memory_limit_info_count SPECIAL_VALUE(Memory_limit_info_count)
#define Memory_limit_variable_names_for_decacheable_structures SPECIAL_VALUE(Memory_limit_variable_names_for_decacheable_structures)
#define Memory_used_for_interned_gensym_strings SPECIAL_VALUE(Memory_used_for_interned_gensym_strings)
#define Memory_used_for_interned_text_strings SPECIAL_VALUE(Memory_used_for_interned_text_strings)
#define Memory_walk_verbose_p SPECIAL_VALUE(Memory_walk_verbose_p)
#define Menu_button_spot_count SPECIAL_VALUE(Menu_button_spot_count)
#define Menu_choose_state_count SPECIAL_VALUE(Menu_choose_state_count)
#define Menu_class_description SPECIAL_VALUE(Menu_class_description)
#define Menu_clean_up_menu_to_keep SPECIAL_VALUE(Menu_clean_up_menu_to_keep)
#define Menu_colors SPECIAL_VALUE(Menu_colors)
#define Menu_colors_sorted_alphabetically SPECIAL_VALUE(Menu_colors_sorted_alphabetically)
#define Menu_colors_sorted_by_hue SPECIAL_VALUE(Menu_colors_sorted_by_hue)
#define Menu_item_spot_count SPECIAL_VALUE(Menu_item_spot_count)
#define Menu_items_for_parsing SPECIAL_VALUE(Menu_items_for_parsing)
#define Menu_pane_spot_count SPECIAL_VALUE(Menu_pane_spot_count)
#define Menu_parameters SPECIAL_VALUE(Menu_parameters)
#define Menu_title_spot_count SPECIAL_VALUE(Menu_title_spot_count)
#define Menu_workspace_class_description SPECIAL_VALUE(Menu_workspace_class_description)
#define Merge_pathnames_rules SPECIAL_VALUE(Merge_pathnames_rules)
#define Merge_pathnames_rules_sorted_p SPECIAL_VALUE(Merge_pathnames_rules_sorted_p)
#define Message_board_class_description SPECIAL_VALUE(Message_board_class_description)
#define Message_board_parameters SPECIAL_VALUE(Message_board_parameters)
#define Message_class_description SPECIAL_VALUE(Message_class_description)
#define Message_completion_interval SPECIAL_VALUE(Message_completion_interval)
#define Message_definition_class_description SPECIAL_VALUE(Message_definition_class_description)
#define Message_illegal_symbol_text_string_contains_a_newline SPECIAL_VALUE(Message_illegal_symbol_text_string_contains_a_newline)
#define Message_illegal_symbol_text_string_contains_fffe SPECIAL_VALUE(Message_illegal_symbol_text_string_contains_fffe)
#define Message_illegal_symbol_text_string_contains_ffff SPECIAL_VALUE(Message_illegal_symbol_text_string_contains_ffff)
#define Message_illegal_symbol_text_string_empty SPECIAL_VALUE(Message_illegal_symbol_text_string_empty)
#define Message_illegal_symbol_text_string_too_long SPECIAL_VALUE(Message_illegal_symbol_text_string_too_long)
#define Meter_class_description SPECIAL_VALUE(Meter_class_description)
#define Meter_lag_time_variables SPECIAL_VALUE(Meter_lag_time_variables)
#define Meter_or_dial_spot_count SPECIAL_VALUE(Meter_or_dial_spot_count)
#define Meter_spot_count SPECIAL_VALUE(Meter_spot_count)
#define Metered_clock_tick_length SPECIAL_VALUE(Metered_clock_tick_length)
#define Method_class_description SPECIAL_VALUE(Method_class_description)
#define Method_declaration_class_description SPECIAL_VALUE(Method_declaration_class_description)
#define Milliseconds_between_retries_for_foreign_image_connection SPECIAL_VALUE(Milliseconds_between_retries_for_foreign_image_connection)
#define Milliseconds_to_sleep_after_connection_on_pc_platforms SPECIAL_VALUE(Milliseconds_to_sleep_after_connection_on_pc_platforms)
#define Milliseconds_to_sleep_before_connecting_to_foreign_image SPECIAL_VALUE(Milliseconds_to_sleep_before_connecting_to_foreign_image)
#define Min_string_length_to_report SPECIAL_VALUE(Min_string_length_to_report)
#define Minimal_character_description_count SPECIAL_VALUE(Minimal_character_description_count)
#define Minimal_fragmentation_seeds SPECIAL_VALUE(Minimal_fragmentation_seeds)
#define Minimnal_bandwidth_for_resumable_sequence_range SPECIAL_VALUE(Minimnal_bandwidth_for_resumable_sequence_range)
#define Minimum_and_maximum_y_value_set_qm SPECIAL_VALUE(Minimum_and_maximum_y_value_set_qm)
#define Minimum_bandwidth_per_timeslice SPECIAL_VALUE(Minimum_bandwidth_per_timeslice)
#define Minimum_distance_between_fins SPECIAL_VALUE(Minimum_distance_between_fins)
#define Minimum_distance_for_data_points SPECIAL_VALUE(Minimum_distance_for_data_points)
#define Minimum_grid_height SPECIAL_VALUE(Minimum_grid_height)
#define Minimum_grid_width SPECIAL_VALUE(Minimum_grid_width)
#define Minimum_number_of_blocks_for_spacial_index SPECIAL_VALUE(Minimum_number_of_blocks_for_spacial_index)
#define Minimum_number_of_blocks_to_retain_spacial_index SPECIAL_VALUE(Minimum_number_of_blocks_to_retain_spacial_index)
#define Minimum_simulation_time_increment SPECIAL_VALUE(Minimum_simulation_time_increment)
#define Minimum_x_value_for_new_data SPECIAL_VALUE(Minimum_x_value_for_new_data)
#define Minimum_y_value SPECIAL_VALUE(Minimum_y_value)
#define Minimum_y_value_for_new_data SPECIAL_VALUE(Minimum_y_value_for_new_data)
#define Minimum_y_value_for_pixel SPECIAL_VALUE(Minimum_y_value_for_pixel)
#define Minus_one_integer SPECIAL_VALUE(Minus_one_integer)
#define Miscellaneous_parameters SPECIAL_VALUE(Miscellaneous_parameters)
#define Missing_local_names_already_reported SPECIAL_VALUE(Missing_local_names_already_reported)
#define Modal_menu_state_count SPECIAL_VALUE(Modal_menu_state_count)
#define Model_definition_class_description SPECIAL_VALUE(Model_definition_class_description)
#define Model_queue_count SPECIAL_VALUE(Model_queue_count)
#define Model_runtime_info_count SPECIAL_VALUE(Model_runtime_info_count)
#define Models_used_p SPECIAL_VALUE(Models_used_p)
#define Modify_control_action_type_count SPECIAL_VALUE(Modify_control_action_type_count)
#define Modify_control_structure_count SPECIAL_VALUE(Modify_control_structure_count)
#define Modify_dialog_structure_count SPECIAL_VALUE(Modify_dialog_structure_count)
#define Modularity_checking SPECIAL_VALUE(Modularity_checking)
#define Module_information SPECIAL_VALUE(Module_information)
#define Module_required_by_relationships SPECIAL_VALUE(Module_required_by_relationships)
#define Module_search_path_tokenizer SPECIAL_VALUE(Module_search_path_tokenizer)
#define Modules_and_system_tables_a_list SPECIAL_VALUE(Modules_and_system_tables_a_list)
#define Modules_considered_in_loading_schedule_so_far SPECIAL_VALUE(Modules_considered_in_loading_schedule_so_far)
#define Modules_listed_so_far SPECIAL_VALUE(Modules_listed_so_far)
#define Modules_loaded_in_this_group SPECIAL_VALUE(Modules_loaded_in_this_group)
#define Modules_scheduled_so_far SPECIAL_VALUE(Modules_scheduled_so_far)
#define Modules_scheduled_so_far_by_save_all_modules_of_kb SPECIAL_VALUE(Modules_scheduled_so_far_by_save_all_modules_of_kb)
#define Modules_that_have_already_been_loaded SPECIAL_VALUE(Modules_that_have_already_been_loaded)
#define Modules_to_translate_verbosely SPECIAL_VALUE(Modules_to_translate_verbosely)
#define Most_fixnum_digits SPECIAL_VALUE(Most_fixnum_digits)
#define Most_lefthand_float_digits SPECIAL_VALUE(Most_lefthand_float_digits)
#define Most_negative_fixnum_as_string SPECIAL_VALUE(Most_negative_fixnum_as_string)
#define Most_recent_bandwidth_per_timeslice_qm SPECIAL_VALUE(Most_recent_bandwidth_per_timeslice_qm)
#define Most_recent_defun_warned_for_catch_qm SPECIAL_VALUE(Most_recent_defun_warned_for_catch_qm)
#define Most_recent_defun_warned_for_unwind_protect_qm SPECIAL_VALUE(Most_recent_defun_warned_for_unwind_protect_qm)
#define Most_recent_extremum_maximum_for_pixel_p SPECIAL_VALUE(Most_recent_extremum_maximum_for_pixel_p)
#define Most_recent_extremum_maximum_p SPECIAL_VALUE(Most_recent_extremum_maximum_p)
#define Most_recent_g2_time SPECIAL_VALUE(Most_recent_g2_time)
#define Most_recent_trend_chart_checked SPECIAL_VALUE(Most_recent_trend_chart_checked)
#define Most_recent_xml_checksum_differences SPECIAL_VALUE(Most_recent_xml_checksum_differences)
#define Most_righthand_float_zeros SPECIAL_VALUE(Most_righthand_float_zeros)
#define Mouse_drag_detector_state_count SPECIAL_VALUE(Mouse_drag_detector_state_count)
#define Mouse_pointer_count SPECIAL_VALUE(Mouse_pointer_count)
#define Mouse_pointer_of_frame SPECIAL_VALUE(Mouse_pointer_of_frame)
#define Mouse_watch_state_count SPECIAL_VALUE(Mouse_watch_state_count)
#define Mouse_x_in_workspace SPECIAL_VALUE(Mouse_x_in_workspace)
#define Mouse_y_in_workspace SPECIAL_VALUE(Mouse_y_in_workspace)
#define Move_dragging_state_count SPECIAL_VALUE(Move_dragging_state_count)
#define Ms_to_wait_for_cvs SPECIAL_VALUE(Ms_to_wait_for_cvs)
#define Msw_cyrillic_code_map SPECIAL_VALUE(Msw_cyrillic_code_map)
#define Multiframe_table_spot_count SPECIAL_VALUE(Multiframe_table_spot_count)
#define Multiplicative_counter_for_evaluation SPECIAL_VALUE(Multiplicative_counter_for_evaluation)
#define Multiplier_for_turning_off_data_collection SPECIAL_VALUE(Multiplier_for_turning_off_data_collection)
#define Multiply_wild_regular_expression_node_count SPECIAL_VALUE(Multiply_wild_regular_expression_node_count)
#define Mutable_slot_description_list_head SPECIAL_VALUE(Mutable_slot_description_list_head)
#define N_32bit_constants SPECIAL_VALUE(N_32bit_constants)
#define Name_box_class_description SPECIAL_VALUE(Name_box_class_description)
#define Name_box_spot_count SPECIAL_VALUE(Name_box_spot_count)
#define Name_for_find_menu_item SPECIAL_VALUE(Name_for_find_menu_item)
#define Name_for_local_home SPECIAL_VALUE(Name_for_local_home)
#define Name_of_current_editor_command_qm SPECIAL_VALUE(Name_of_current_editor_command_qm)
#define Name_of_customer_in_ok_file SPECIAL_VALUE(Name_of_customer_in_ok_file)
#define Name_of_file_slot_description SPECIAL_VALUE(Name_of_file_slot_description)
#define Name_of_kb_being_read SPECIAL_VALUE(Name_of_kb_being_read)
#define Name_of_module_being_read_qm SPECIAL_VALUE(Name_of_module_being_read_qm)
#define Name_text_string_for_kb_being_read SPECIAL_VALUE(Name_text_string_for_kb_being_read)
#define Named_gensym_structure_count SPECIAL_VALUE(Named_gensym_structure_count)
#define Names_and_info_for_chaining SPECIAL_VALUE(Names_and_info_for_chaining)
#define Names_and_sizes_for_decacheable_structures SPECIAL_VALUE(Names_and_sizes_for_decacheable_structures)
#define Names_of_grammars_to_add_rules_to SPECIAL_VALUE(Names_of_grammars_to_add_rules_to)
#define Names_used_for_more_than_one_item SPECIAL_VALUE(Names_used_for_more_than_one_item)
#define Namestring_for_kb_being_read SPECIAL_VALUE(Namestring_for_kb_being_read)
#define Native_alias_creation_dialog SPECIAL_VALUE(Native_alias_creation_dialog)
#define Native_dialog_count SPECIAL_VALUE(Native_dialog_count)
#define Native_dialog_handle_parity SPECIAL_VALUE(Native_dialog_handle_parity)
#define Native_editor_already_updated SPECIAL_VALUE(Native_editor_already_updated)
#define Native_font_count SPECIAL_VALUE(Native_font_count)
#define Native_image_plane_options SPECIAL_VALUE(Native_image_plane_options)
#define Native_image_plane_updated_by_client SPECIAL_VALUE(Native_image_plane_updated_by_client)
#define Native_login_dialog SPECIAL_VALUE(Native_login_dialog)
#define Native_menu_counter SPECIAL_VALUE(Native_menu_counter)
#define Native_menu_id_to_handle_and_item_number_table SPECIAL_VALUE(Native_menu_id_to_handle_and_item_number_table)
#define Native_menu_table SPECIAL_VALUE(Native_menu_table)
#define Native_menu_unique_id_counter SPECIAL_VALUE(Native_menu_unique_id_counter)
#define Native_printer_information SPECIAL_VALUE(Native_printer_information)
#define Native_printing_color_differences SPECIAL_VALUE(Native_printing_color_differences)
#define Native_printing_icon_x_in_window SPECIAL_VALUE(Native_printing_icon_x_in_window)
#define Native_printing_icon_y_in_window SPECIAL_VALUE(Native_printing_icon_y_in_window)
#define Native_simple_dialog_state_count SPECIAL_VALUE(Native_simple_dialog_state_count)
#define Native_window_client_operation SPECIAL_VALUE(Native_window_client_operation)
#define Native_window_count SPECIAL_VALUE(Native_window_count)
#define Native_window_heartbeat_task SPECIAL_VALUE(Native_window_heartbeat_task)
#define Native_window_notices_enter_and_leave_events_p SPECIAL_VALUE(Native_window_notices_enter_and_leave_events_p)
#define Native_window_updated_by_client SPECIAL_VALUE(Native_window_updated_by_client)
#define Need_to_check_plist_p SPECIAL_VALUE(Need_to_check_plist_p)
#define Needed_domain SPECIAL_VALUE(Needed_domain)
#define Negative_shutdown_interval_for_disallowed_icp_connection SPECIAL_VALUE(Negative_shutdown_interval_for_disallowed_icp_connection)
#define Network_octet_buffer_length SPECIAL_VALUE(Network_octet_buffer_length)
#define New_byte_code_body_list SPECIAL_VALUE(New_byte_code_body_list)
#define New_compiled_byte_code_body_list SPECIAL_VALUE(New_compiled_byte_code_body_list)
#define New_dateline_qm SPECIAL_VALUE(New_dateline_qm)
#define New_descriptions SPECIAL_VALUE(New_descriptions)
#define New_g2_classic_ui_p SPECIAL_VALUE(New_g2_classic_ui_p)
#define New_goto_tag_counter SPECIAL_VALUE(New_goto_tag_counter)
#define New_position_of_horizontal_elevator_of_frame SPECIAL_VALUE(New_position_of_horizontal_elevator_of_frame)
#define New_position_of_vertical_elevator_of_frame SPECIAL_VALUE(New_position_of_vertical_elevator_of_frame)
#define New_saved_kb_format_p SPECIAL_VALUE(New_saved_kb_format_p)
#define New_table SPECIAL_VALUE(New_table)
#define New_table_background_spot_count SPECIAL_VALUE(New_table_background_spot_count)
#define New_table_cell_spot_count SPECIAL_VALUE(New_table_cell_spot_count)
#define New_table_spot_count SPECIAL_VALUE(New_table_spot_count)
#define New_value_computed_in_formula_qm SPECIAL_VALUE(New_value_computed_in_formula_qm)
#define Newline_characters SPECIAL_VALUE(Newline_characters)
#define Next_character_for_kb_qm SPECIAL_VALUE(Next_character_for_kb_qm)
#define Next_class_bit_number SPECIAL_VALUE(Next_class_bit_number)
#define Next_continuation_function_qm SPECIAL_VALUE(Next_continuation_function_qm)
#define Next_element_to_be_sorted_qm SPECIAL_VALUE(Next_element_to_be_sorted_qm)
#define Next_eq_hash_value SPECIAL_VALUE(Next_eq_hash_value)
#define Next_info SPECIAL_VALUE(Next_info)
#define Next_info_reclaimer_qm SPECIAL_VALUE(Next_info_reclaimer_qm)
#define Next_native_eq_dialog_handle SPECIAL_VALUE(Next_native_eq_dialog_handle)
#define Next_object_index_property_number SPECIAL_VALUE(Next_object_index_property_number)
#define Next_old_style_return_function_qm SPECIAL_VALUE(Next_old_style_return_function_qm)
#define Next_serial_number_to_be_generated SPECIAL_VALUE(Next_serial_number_to_be_generated)
#define Next_stack_frame_var_location SPECIAL_VALUE(Next_stack_frame_var_location)
#define Nil_indicator SPECIAL_VALUE(Nil_indicator)
#define Nil_interned SPECIAL_VALUE(Nil_interned)
#define Nms_constructing_built_in_menus_p SPECIAL_VALUE(Nms_constructing_built_in_menus_p)
#define Nms_menu_count SPECIAL_VALUE(Nms_menu_count)
#define Nms_menu_hash_table SPECIAL_VALUE(Nms_menu_hash_table)
#define Nms_menu_item_count SPECIAL_VALUE(Nms_menu_item_count)
#define Nms_reclaim_hook SPECIAL_VALUE(Nms_reclaim_hook)
#define No_arg SPECIAL_VALUE(No_arg)
#define No_data_server_error SPECIAL_VALUE(No_data_server_error)
#define No_grouping_tag_for_grouping_specification SPECIAL_VALUE(No_grouping_tag_for_grouping_specification)
#define No_saved_initial_value SPECIAL_VALUE(No_saved_initial_value)
#define No_value SPECIAL_VALUE(No_value)
#define Node_id_for_uuid SPECIAL_VALUE(Node_id_for_uuid)
#define Node_id_for_uuid_uses_ethernet_address_p SPECIAL_VALUE(Node_id_for_uuid_uses_ethernet_address_p)
#define Nodes_for_generalized_dos_filename_parser SPECIAL_VALUE(Nodes_for_generalized_dos_filename_parser)
#define Nodes_for_unix_filename_parser SPECIAL_VALUE(Nodes_for_unix_filename_parser)
#define Nodes_for_vms_filename_parser SPECIAL_VALUE(Nodes_for_vms_filename_parser)
#define Non_context_top_level_binding_forms SPECIAL_VALUE(Non_context_top_level_binding_forms)
#define Non_kb_workspace_class_description SPECIAL_VALUE(Non_kb_workspace_class_description)
#define Non_kb_workspace_image_plane_spot_count SPECIAL_VALUE(Non_kb_workspace_image_plane_spot_count)
#define Non_menu_choices SPECIAL_VALUE(Non_menu_choices)
#define Non_procedure_root_invocations SPECIAL_VALUE(Non_procedure_root_invocations)
#define Normal_completion_count SPECIAL_VALUE(Normal_completion_count)
#define Note_as_kb_state_change_qm SPECIAL_VALUE(Note_as_kb_state_change_qm)
#define Note_blocks_in_tformat SPECIAL_VALUE(Note_blocks_in_tformat)
#define Note_kb_state_changes_via_system_procedures_qm SPECIAL_VALUE(Note_kb_state_changes_via_system_procedures_qm)
#define Note_things_encountered_during_role_service_qm SPECIAL_VALUE(Note_things_encountered_during_role_service_qm)
#define Notification_data_version_map SPECIAL_VALUE(Notification_data_version_map)
#define Noting_changes_to_kb_p SPECIAL_VALUE(Noting_changes_to_kb_p)
#define Null_char SPECIAL_VALUE(Null_char)
#define Number_of_contexts_allocated SPECIAL_VALUE(Number_of_contexts_allocated)
#define Number_of_horizontal_grid_lines SPECIAL_VALUE(Number_of_horizontal_grid_lines)
#define Number_of_icp_bytes_for_message_series SPECIAL_VALUE(Number_of_icp_bytes_for_message_series)
#define Number_of_icp_bytes_in_message_group SPECIAL_VALUE(Number_of_icp_bytes_in_message_group)
#define Number_of_icp_bytes_left_in_current_buffer SPECIAL_VALUE(Number_of_icp_bytes_left_in_current_buffer)
#define Number_of_icp_bytes_left_in_message_series SPECIAL_VALUE(Number_of_icp_bytes_left_in_message_series)
#define Number_of_icp_bytes_ready_to_read SPECIAL_VALUE(Number_of_icp_bytes_ready_to_read)
#define Number_of_icp_bytes_to_fill_buffer SPECIAL_VALUE(Number_of_icp_bytes_to_fill_buffer)
#define Number_of_kb_characters_so_far_qm SPECIAL_VALUE(Number_of_kb_characters_so_far_qm)
#define Number_of_kb_lines_so_far SPECIAL_VALUE(Number_of_kb_lines_so_far)
#define Number_of_ksc_codes SPECIAL_VALUE(Number_of_ksc_codes)
#define Number_of_lexing_tables_in_cache SPECIAL_VALUE(Number_of_lexing_tables_in_cache)
#define Number_of_memory_regions SPECIAL_VALUE(Number_of_memory_regions)
#define Number_of_no_binds SPECIAL_VALUE(Number_of_no_binds)
#define Number_of_raster_oddspaces SPECIAL_VALUE(Number_of_raster_oddspaces)
#define Number_of_significant_digits SPECIAL_VALUE(Number_of_significant_digits)
#define Number_of_simulated_variables_processed SPECIAL_VALUE(Number_of_simulated_variables_processed)
#define Number_of_variables_to_process_at_a_time SPECIAL_VALUE(Number_of_variables_to_process_at_a_time)
#define Number_of_vertical_grid_lines SPECIAL_VALUE(Number_of_vertical_grid_lines)
#define Nupec_catch_up_mode_caught_up_qm SPECIAL_VALUE(Nupec_catch_up_mode_caught_up_qm)
#define Nupec_synchronize_variable_or_parameter_count SPECIAL_VALUE(Nupec_synchronize_variable_or_parameter_count)
#define Object_building_problem_count SPECIAL_VALUE(Object_building_problem_count)
#define Object_class_description SPECIAL_VALUE(Object_class_description)
#define Object_definition_class_description SPECIAL_VALUE(Object_definition_class_description)
#define Object_file_pathname_for_machine SPECIAL_VALUE(Object_file_pathname_for_machine)
#define Object_map_plist_for_icp_tree SPECIAL_VALUE(Object_map_plist_for_icp_tree)
#define Object_passing_info_count SPECIAL_VALUE(Object_passing_info_count)
#define Object_pool_meters SPECIAL_VALUE(Object_pool_meters)
#define Objects_to_not_consider_qm SPECIAL_VALUE(Objects_to_not_consider_qm)
#define Obsolete_frame_note_types_from_modularity_development SPECIAL_VALUE(Obsolete_frame_note_types_from_modularity_development)
#define Off_window_color_map SPECIAL_VALUE(Off_window_color_map)
#define Ok_authorized_packages SPECIAL_VALUE(Ok_authorized_packages)
#define Ok_authorized_products SPECIAL_VALUE(Ok_authorized_products)
#define Ok_class_description SPECIAL_VALUE(Ok_class_description)
#define Ok_expiration_date_qm SPECIAL_VALUE(Ok_expiration_date_qm)
#define Ok_file_saving_mode_qm SPECIAL_VALUE(Ok_file_saving_mode_qm)
#define Ok_file_token_cons_counter SPECIAL_VALUE(Ok_file_token_cons_counter)
#define Ok_file_token_count SPECIAL_VALUE(Ok_file_token_count)
#define Ok_make_g2_secure_qm SPECIAL_VALUE(Ok_make_g2_secure_qm)
#define Ok_maximum_number_of_concurrent_floating_telewindows_allowed SPECIAL_VALUE(Ok_maximum_number_of_concurrent_floating_telewindows_allowed)
#define Ok_maximum_number_of_concurrent_floating_tw2_allowed SPECIAL_VALUE(Ok_maximum_number_of_concurrent_floating_tw2_allowed)
#define Ok_modified SPECIAL_VALUE(Ok_modified)
#define Ok_number_of_processes_authorized SPECIAL_VALUE(Ok_number_of_processes_authorized)
#define Old_exposed_region SPECIAL_VALUE(Old_exposed_region)
#define Old_timespan_system_variable_for_compute_trend_chart_time_bounds SPECIAL_VALUE(Old_timespan_system_variable_for_compute_trend_chart_time_bounds)
#define On_monochrome_raster_list_p SPECIAL_VALUE(On_monochrome_raster_list_p)
#define On_window_with_drawing SPECIAL_VALUE(On_window_with_drawing)
#define On_window_without_drawing SPECIAL_VALUE(On_window_without_drawing)
#define One_integer SPECIAL_VALUE(One_integer)
#define One_sequence_of_following_tokens_only_p SPECIAL_VALUE(One_sequence_of_following_tokens_only_p)
#define Only_impose_device_set_widths_to_squeeze_qm SPECIAL_VALUE(Only_impose_device_set_widths_to_squeeze_qm)
#define Operation_around_record_of_items_made_incomplete SPECIAL_VALUE(Operation_around_record_of_items_made_incomplete)
#define Operation_of_graphic_element SPECIAL_VALUE(Operation_of_graphic_element)
#define Operative_task_list SPECIAL_VALUE(Operative_task_list)
#define Optimized_constant_op_codes SPECIAL_VALUE(Optimized_constant_op_codes)
#define Optimized_constant_pc SPECIAL_VALUE(Optimized_constant_pc)
#define Optimized_constant_vector SPECIAL_VALUE(Optimized_constant_vector)
#define Optimized_constant_vector_index SPECIAL_VALUE(Optimized_constant_vector_index)
#define Optional_modules_map SPECIAL_VALUE(Optional_modules_map)
#define Orientation_horizontal_p SPECIAL_VALUE(Orientation_horizontal_p)
#define Orientation_of_frame SPECIAL_VALUE(Orientation_of_frame)
#define Original_kb_state_plist_written_qm SPECIAL_VALUE(Original_kb_state_plist_written_qm)
#define Out_of_memory_handler SPECIAL_VALUE(Out_of_memory_handler)
#define Outer_native_image_plane SPECIAL_VALUE(Outer_native_image_plane)
#define Outermost_stack_frame_var_binding_qm SPECIAL_VALUE(Outermost_stack_frame_var_binding_qm)
#define Output_only_table_spot_count SPECIAL_VALUE(Output_only_table_spot_count)
#define Output_vector_for_object SPECIAL_VALUE(Output_vector_for_object)
#define Output_window_for_printing_qm SPECIAL_VALUE(Output_window_for_printing_qm)
#define Outputting_to_gensym_string SPECIAL_VALUE(Outputting_to_gensym_string)
#define Outputting_to_wide_string SPECIAL_VALUE(Outputting_to_wide_string)
#define Outside_window_spot_count SPECIAL_VALUE(Outside_window_spot_count)
#define Outstanding_float_function_floats SPECIAL_VALUE(Outstanding_float_function_floats)
#define Outstanding_frame_vector_count SPECIAL_VALUE(Outstanding_frame_vector_count)
#define Overflow_byte_count SPECIAL_VALUE(Overflow_byte_count)
#define Override_eliminate_for_gsi_no_utf_g_p SPECIAL_VALUE(Override_eliminate_for_gsi_no_utf_g_p)
#define Override_eliminate_for_gsi_p SPECIAL_VALUE(Override_eliminate_for_gsi_p)
#define Override_preferred_editor SPECIAL_VALUE(Override_preferred_editor)
#define Overriding_alignment SPECIAL_VALUE(Overriding_alignment)
#define Oversized_simple_float_array_pool_memory_usage SPECIAL_VALUE(Oversized_simple_float_array_pool_memory_usage)
#define Oversized_simple_vector_pool_counts SPECIAL_VALUE(Oversized_simple_vector_pool_counts)
#define Overview_pane_spot_count SPECIAL_VALUE(Overview_pane_spot_count)
#define Package_preparation_mode SPECIAL_VALUE(Package_preparation_mode)
#define Pad_for_ok_file_reader SPECIAL_VALUE(Pad_for_ok_file_reader)
#define Page_class_description SPECIAL_VALUE(Page_class_description)
#define Paint_only_target_monochrome_raster_p SPECIAL_VALUE(Paint_only_target_monochrome_raster_p)
#define Painting_for_graph_activation_p SPECIAL_VALUE(Painting_for_graph_activation_p)
#define Pane_background_spot_count SPECIAL_VALUE(Pane_background_spot_count)
#define Pane_border_spot_count SPECIAL_VALUE(Pane_border_spot_count)
#define Pane_component_spot_count SPECIAL_VALUE(Pane_component_spot_count)
#define Pane_count SPECIAL_VALUE(Pane_count)
#define Pane_for_debugger_pause SPECIAL_VALUE(Pane_for_debugger_pause)
#define Pane_spot_count SPECIAL_VALUE(Pane_spot_count)
#define Parameter_class_description SPECIAL_VALUE(Parameter_class_description)
#define Parent_trend_chart SPECIAL_VALUE(Parent_trend_chart)
#define Parse_object_count SPECIAL_VALUE(Parse_object_count)
#define Parse_table_count SPECIAL_VALUE(Parse_table_count)
#define Parsing_context_count SPECIAL_VALUE(Parsing_context_count)
#define Parsing_token_count SPECIAL_VALUE(Parsing_token_count)
#define Part_exceptions_from_parents SPECIAL_VALUE(Part_exceptions_from_parents)
#define Part_feature_enter_methods SPECIAL_VALUE(Part_feature_enter_methods)
#define Part_feature_exit_methods SPECIAL_VALUE(Part_feature_exit_methods)
#define Part_feature_indexes SPECIAL_VALUE(Part_feature_indexes)
#define Part_feature_recall_stack SPECIAL_VALUE(Part_feature_recall_stack)
#define Part_features_to_write SPECIAL_VALUE(Part_features_to_write)
#define Part_index SPECIAL_VALUE(Part_index)
#define Part_stack_cons_counter SPECIAL_VALUE(Part_stack_cons_counter)
#define Part_text_size_parameters SPECIAL_VALUE(Part_text_size_parameters)
#define Partial_command_count SPECIAL_VALUE(Partial_command_count)
#define Partition_details_of_current_branch_of_frame SPECIAL_VALUE(Partition_details_of_current_branch_of_frame)
#define Partition_float_union SPECIAL_VALUE(Partition_float_union)
#define Partition_long_union SPECIAL_VALUE(Partition_long_union)
#define Parts_of_annotated_frames_currently_erased SPECIAL_VALUE(Parts_of_annotated_frames_currently_erased)
#define Path_cons_counter SPECIAL_VALUE(Path_cons_counter)
#define Pathname_component_token_menu_button_spot_count SPECIAL_VALUE(Pathname_component_token_menu_button_spot_count)
#define Pathname_for_disabling_g2_hangul_star_command_line SPECIAL_VALUE(Pathname_for_disabling_g2_hangul_star_command_line)
#define Pathname_for_disabling_g2_init_command_line SPECIAL_VALUE(Pathname_for_disabling_g2_init_command_line)
#define Pathname_for_disabling_g2_kanji_star_command_line SPECIAL_VALUE(Pathname_for_disabling_g2_kanji_star_command_line)
#define Pathname_for_disabling_g2_kb_command_line SPECIAL_VALUE(Pathname_for_disabling_g2_kb_command_line)
#define Pathname_for_disabling_g2_minm_star_command_line SPECIAL_VALUE(Pathname_for_disabling_g2_minm_star_command_line)
#define Pathname_for_disabling_g2_module_map_command_line SPECIAL_VALUE(Pathname_for_disabling_g2_module_map_command_line)
#define Pathname_for_disabling_g2_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_g2_ok_command_line)
#define Pathname_for_disabling_g2v11_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_g2v11_ok_command_line)
#define Pathname_for_disabling_g2v12_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_g2v12_ok_command_line)
#define Pathname_for_disabling_g2v51_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_g2v51_ok_command_line)
#define Pathname_for_disabling_g2v5_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_g2v5_ok_command_line)
#define Pathname_for_disabling_g2v6_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_g2v6_ok_command_line)
#define Pathname_for_disabling_g2v7_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_g2v7_ok_command_line)
#define Pathname_for_disabling_g2v83_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_g2v83_ok_command_line)
#define Pathname_for_disabling_g2v8_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_g2v8_ok_command_line)
#define Pathname_for_disabling_g2v9_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_g2v9_ok_command_line)
#define Pathname_for_disabling_tw_hangul_star_command_line SPECIAL_VALUE(Pathname_for_disabling_tw_hangul_star_command_line)
#define Pathname_for_disabling_tw_kanji_star_command_line SPECIAL_VALUE(Pathname_for_disabling_tw_kanji_star_command_line)
#define Pathname_for_disabling_tw_minm_star_command_line SPECIAL_VALUE(Pathname_for_disabling_tw_minm_star_command_line)
#define Pathname_for_disabling_tw_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_tw_ok_command_line)
#define Pathname_for_disabling_twv11_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_twv11_ok_command_line)
#define Pathname_for_disabling_twv12_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_twv12_ok_command_line)
#define Pathname_for_disabling_twv5_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_twv5_ok_command_line)
#define Pathname_for_disabling_twv6_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_twv6_ok_command_line)
#define Pathname_for_disabling_twv7_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_twv7_ok_command_line)
#define Pathname_for_disabling_twv8_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_twv8_ok_command_line)
#define Pathname_for_disabling_twv9_ok_command_line SPECIAL_VALUE(Pathname_for_disabling_twv9_ok_command_line)
#define Pathname_for_distribution_binaries_qm SPECIAL_VALUE(Pathname_for_distribution_binaries_qm)
#define Pathname_with_default_type_if_required_for_module_pathnames_qm SPECIAL_VALUE(Pathname_with_default_type_if_required_for_module_pathnames_qm)
#define Pattern_checking_inverse_references SPECIAL_VALUE(Pattern_checking_inverse_references)
#define Pending_activity_count SPECIAL_VALUE(Pending_activity_count)
#define Pending_native_dialogs SPECIAL_VALUE(Pending_native_dialogs)
#define Pending_write_reference_list SPECIAL_VALUE(Pending_write_reference_list)
#define Percent_running SPECIAL_VALUE(Percent_running)
#define Permanent_mutable_list SPECIAL_VALUE(Permanent_mutable_list)
#define Permit_cvs_timeout_dialog_p SPECIAL_VALUE(Permit_cvs_timeout_dialog_p)
#define Permit_spacial_index_p SPECIAL_VALUE(Permit_spacial_index_p)
#define Permit_transfer_of_permanent_items_p SPECIAL_VALUE(Permit_transfer_of_permanent_items_p)
#define Permitted_restriction_set SPECIAL_VALUE(Permitted_restriction_set)
#define Phrase_copying_needs_annotation_rehashing SPECIAL_VALUE(Phrase_copying_needs_annotation_rehashing)
#define Phrase_pool_cons_counter SPECIAL_VALUE(Phrase_pool_cons_counter)
#define Phrase_rule_completion_count SPECIAL_VALUE(Phrase_rule_completion_count)
#define Ping_seq_id_array SPECIAL_VALUE(Ping_seq_id_array)
#define Pixmap_count SPECIAL_VALUE(Pixmap_count)
#define Place_for_for_telewindows_modernization SPECIAL_VALUE(Place_for_for_telewindows_modernization)
#define Place_reference_internals_count SPECIAL_VALUE(Place_reference_internals_count)
#define Platform_independent_print_spool_command_file_name SPECIAL_VALUE(Platform_independent_print_spool_command_file_name)
#define Player_cons_counter SPECIAL_VALUE(Player_cons_counter)
#define Player_control_stack SPECIAL_VALUE(Player_control_stack)
#define Player_current_instruction SPECIAL_VALUE(Player_current_instruction)
#define Player_definition_stack SPECIAL_VALUE(Player_definition_stack)
#define Player_icp_connection SPECIAL_VALUE(Player_icp_connection)
#define Player_lexical_binding_stack SPECIAL_VALUE(Player_lexical_binding_stack)
#define Player_location_stack SPECIAL_VALUE(Player_location_stack)
#define Player_mouse_x SPECIAL_VALUE(Player_mouse_x)
#define Player_mouse_y SPECIAL_VALUE(Player_mouse_y)
#define Player_named_locations SPECIAL_VALUE(Player_named_locations)
#define Player_pace SPECIAL_VALUE(Player_pace)
#define Player_require_modules_already_sent SPECIAL_VALUE(Player_require_modules_already_sent)
#define Player_state SPECIAL_VALUE(Player_state)
#define Player_target_gensym_window_g2_struct_qm SPECIAL_VALUE(Player_target_gensym_window_g2_struct_qm)
#define Player_value_stack SPECIAL_VALUE(Player_value_stack)
#define Plist_from_end_element_qm SPECIAL_VALUE(Plist_from_end_element_qm)
#define Plist_has_been_checked_p SPECIAL_VALUE(Plist_has_been_checked_p)
#define Plist_of_corresponding_icp_object_maps_for_font_maps SPECIAL_VALUE(Plist_of_corresponding_icp_object_maps_for_font_maps)
#define Plot_class_description SPECIAL_VALUE(Plot_class_description)
#define Plot_connector_painting_buffer_head SPECIAL_VALUE(Plot_connector_painting_buffer_head)
#define Plot_connector_painting_buffer_limit SPECIAL_VALUE(Plot_connector_painting_buffer_limit)
#define Plot_connector_painting_buffer_size SPECIAL_VALUE(Plot_connector_painting_buffer_size)
#define Plot_connector_painting_buffer_tail SPECIAL_VALUE(Plot_connector_painting_buffer_tail)
#define Plot_data_ring_buffer_count SPECIAL_VALUE(Plot_data_ring_buffer_count)
#define Plot_marker_qm SPECIAL_VALUE(Plot_marker_qm)
#define Plot_max_qm SPECIAL_VALUE(Plot_max_qm)
#define Plot_min_and_max_qm SPECIAL_VALUE(Plot_min_and_max_qm)
#define Plot_min_qm SPECIAL_VALUE(Plot_min_qm)
#define Pm_max_length SPECIAL_VALUE(Pm_max_length)
#define Pm_slot_names SPECIAL_VALUE(Pm_slot_names)
#define Pm_temp_string SPECIAL_VALUE(Pm_temp_string)
#define Pointer_for_dial_class_description SPECIAL_VALUE(Pointer_for_dial_class_description)
#define Poly_line_pattern SPECIAL_VALUE(Poly_line_pattern)
#define Poly_line_style SPECIAL_VALUE(Poly_line_style)
#define Poly_line_width SPECIAL_VALUE(Poly_line_width)
#define Poly_vertices SPECIAL_VALUE(Poly_vertices)
#define Polygon_fill_color_difference SPECIAL_VALUE(Polygon_fill_color_difference)
#define Polygon_fill_pattern SPECIAL_VALUE(Polygon_fill_pattern)
#define Pop_fonts_stack SPECIAL_VALUE(Pop_fonts_stack)
#define Popup_frames_available SPECIAL_VALUE(Popup_frames_available)
#define Position_in_file_slot_description SPECIAL_VALUE(Position_in_file_slot_description)
#define Possible_label_dispatch_destination SPECIAL_VALUE(Possible_label_dispatch_destination)
#define Possible_phrase_count SPECIAL_VALUE(Possible_phrase_count)
#define Post_analyzer_warning_note_qm SPECIAL_VALUE(Post_analyzer_warning_note_qm)
#define Post_analyzer_warning_notes_for_generic_simulation_formulas_qm SPECIAL_VALUE(Post_analyzer_warning_notes_for_generic_simulation_formulas_qm)
#define Post_compiler_warning_note_qm SPECIAL_VALUE(Post_compiler_warning_note_qm)
#define Post_draw_methods_for_text_box_formats SPECIAL_VALUE(Post_draw_methods_for_text_box_formats)
#define Post_kb_loading_consistency_analysis SPECIAL_VALUE(Post_kb_loading_consistency_analysis)
#define Post_loading_functions_will_be_executed_again_later_qm SPECIAL_VALUE(Post_loading_functions_will_be_executed_again_later_qm)
#define Post_mortem_internal_buffer SPECIAL_VALUE(Post_mortem_internal_buffer)
#define Post_mortem_report_buffer SPECIAL_VALUE(Post_mortem_report_buffer)
#define Post_mortem_ring_buffer_logfile_line_count SPECIAL_VALUE(Post_mortem_ring_buffer_logfile_line_count)
#define Post_mortem_ring_buffer_logfile_namestring SPECIAL_VALUE(Post_mortem_ring_buffer_logfile_namestring)
#define Post_mortem_ring_buffer_logfile_stream SPECIAL_VALUE(Post_mortem_ring_buffer_logfile_stream)
#define Postpone_cell_erase_until_redraw_p SPECIAL_VALUE(Postpone_cell_erase_until_redraw_p)
#define Postscript_composite_object_mapping SPECIAL_VALUE(Postscript_composite_object_mapping)
#define Postscript_computed_variables_mapping SPECIAL_VALUE(Postscript_computed_variables_mapping)
#define Postscript_current_graph_line_drawing_index SPECIAL_VALUE(Postscript_current_graph_line_drawing_index)
#define Postscript_definition_operation_counter SPECIAL_VALUE(Postscript_definition_operation_counter)
#define Postscript_emit_composite_object_without_name SPECIAL_VALUE(Postscript_emit_composite_object_without_name)
#define Postscript_emit_integers_as_color_differences SPECIAL_VALUE(Postscript_emit_integers_as_color_differences)
#define Postscript_emitting_definition SPECIAL_VALUE(Postscript_emitting_definition)
#define Postscript_object_mapping_for_graph_renderings SPECIAL_VALUE(Postscript_object_mapping_for_graph_renderings)
#define Postscript_object_mapping_for_icon_renderings SPECIAL_VALUE(Postscript_object_mapping_for_icon_renderings)
#define Postscript_printing_icon_renderings SPECIAL_VALUE(Postscript_printing_icon_renderings)
#define Preexisting_frames SPECIAL_VALUE(Preexisting_frames)
#define Prefer_bitmap_to_scaled_outline_font_at_full_scale_qm SPECIAL_VALUE(Prefer_bitmap_to_scaled_outline_font_at_full_scale_qm)
#define Prefer_bitmap_to_scaled_outline_font_qm SPECIAL_VALUE(Prefer_bitmap_to_scaled_outline_font_qm)
#define Prefer_bitmap_to_scaled_outline_if_matched_at_any_scale_qm SPECIAL_VALUE(Prefer_bitmap_to_scaled_outline_if_matched_at_any_scale_qm)
#define Prefer_kb_procedures_to_system_defined_p SPECIAL_VALUE(Prefer_kb_procedures_to_system_defined_p)
#define Preprocessing_tokenizer SPECIAL_VALUE(Preprocessing_tokenizer)
#define Preprocessor_errors_qm SPECIAL_VALUE(Preprocessor_errors_qm)
#define Presentation_mode SPECIAL_VALUE(Presentation_mode)
#define Preserve_non_default_icon_colors_or_variables_qm SPECIAL_VALUE(Preserve_non_default_icon_colors_or_variables_qm)
#define Previous_cascaded_ring_buffer_accessed SPECIAL_VALUE(Previous_cascaded_ring_buffer_accessed)
#define Previous_index_for_ring_buffer SPECIAL_VALUE(Previous_index_for_ring_buffer)
#define Previous_modulus_counter_for_evaluation SPECIAL_VALUE(Previous_modulus_counter_for_evaluation)
#define Previous_timestamp_qm SPECIAL_VALUE(Previous_timestamp_qm)
#define Print_spooling SPECIAL_VALUE(Print_spooling)
#define Print_wide_string_max_length SPECIAL_VALUE(Print_wide_string_max_length)
#define Printer_setup SPECIAL_VALUE(Printer_setup)
#define Printing_cons_counter SPECIAL_VALUE(Printing_cons_counter)
#define Printing_format SPECIAL_VALUE(Printing_format)
#define Printing_graph_rendering_color_list_qm SPECIAL_VALUE(Printing_graph_rendering_color_list_qm)
#define Printing_icon_current_region_index_qm SPECIAL_VALUE(Printing_icon_current_region_index_qm)
#define Printing_in_progress_p SPECIAL_VALUE(Printing_in_progress_p)
#define Printing_pass_number SPECIAL_VALUE(Printing_pass_number)
#define Printing_stream SPECIAL_VALUE(Printing_stream)
#define Priority_10_last_gensym_time SPECIAL_VALUE(Priority_10_last_gensym_time)
#define Priority_1_last_gensym_time SPECIAL_VALUE(Priority_1_last_gensym_time)
#define Priority_2_last_gensym_time SPECIAL_VALUE(Priority_2_last_gensym_time)
#define Priority_3_last_gensym_time SPECIAL_VALUE(Priority_3_last_gensym_time)
#define Priority_4_last_gensym_time SPECIAL_VALUE(Priority_4_last_gensym_time)
#define Priority_5_last_gensym_time SPECIAL_VALUE(Priority_5_last_gensym_time)
#define Priority_6_last_gensym_time SPECIAL_VALUE(Priority_6_last_gensym_time)
#define Priority_7_last_gensym_time SPECIAL_VALUE(Priority_7_last_gensym_time)
#define Priority_8_last_gensym_time SPECIAL_VALUE(Priority_8_last_gensym_time)
#define Priority_9_last_gensym_time SPECIAL_VALUE(Priority_9_last_gensym_time)
#define Priority_of_current_task SPECIAL_VALUE(Priority_of_current_task)
#define Priority_of_icp_control_messages SPECIAL_VALUE(Priority_of_icp_control_messages)
#define Priority_of_icp_message_service SPECIAL_VALUE(Priority_of_icp_message_service)
#define Priority_of_next_task SPECIAL_VALUE(Priority_of_next_task)
#define Priority_of_rpc_service SPECIAL_VALUE(Priority_of_rpc_service)
#define Problems_reformatting_graph_qm SPECIAL_VALUE(Problems_reformatting_graph_qm)
#define Proc_cons_counter SPECIAL_VALUE(Proc_cons_counter)
#define Procedure_alist SPECIAL_VALUE(Procedure_alist)
#define Procedure_branch_short_cuts SPECIAL_VALUE(Procedure_branch_short_cuts)
#define Procedure_class_description SPECIAL_VALUE(Procedure_class_description)
#define Procedure_current_time SPECIAL_VALUE(Procedure_current_time)
#define Procedure_end_time SPECIAL_VALUE(Procedure_end_time)
#define Procedure_function_template_alist SPECIAL_VALUE(Procedure_function_template_alist)
#define Procedure_invocation_class_description SPECIAL_VALUE(Procedure_invocation_class_description)
#define Procedure_invocation_count SPECIAL_VALUE(Procedure_invocation_count)
#define Procedure_start_time SPECIAL_VALUE(Procedure_start_time)
#define Procedures_to_warn_about_p SPECIAL_VALUE(Procedures_to_warn_about_p)
#define Proceed_with_edit SPECIAL_VALUE(Proceed_with_edit)
#define Process_checksum_for_image_data_p SPECIAL_VALUE(Process_checksum_for_image_data_p)
#define Process_count SPECIAL_VALUE(Process_count)
#define Process_initializations_alist SPECIAL_VALUE(Process_initializations_alist)
#define Process_instance_created_for_current_process_qm SPECIAL_VALUE(Process_instance_created_for_current_process_qm)
#define Process_specific_system_pathname SPECIAL_VALUE(Process_specific_system_pathname)
#define Processing_as_fast_as_possible_models_qm SPECIAL_VALUE(Processing_as_fast_as_possible_models_qm)
#define Production_count SPECIAL_VALUE(Production_count)
#define Profiling_enabled_qm SPECIAL_VALUE(Profiling_enabled_qm)
#define Profiling_structure SPECIAL_VALUE(Profiling_structure)
#define Prohibited_restriction_set SPECIAL_VALUE(Prohibited_restriction_set)
#define Projecting_to_collect_description_for_new_table SPECIAL_VALUE(Projecting_to_collect_description_for_new_table)
#define Projection SPECIAL_VALUE(Projection)
#define Projection_computing_path_of_focus SPECIAL_VALUE(Projection_computing_path_of_focus)
#define Projection_drawing SPECIAL_VALUE(Projection_drawing)
#define Projection_focus_annotation SPECIAL_VALUE(Projection_focus_annotation)
#define Projection_focus_cell_index SPECIAL_VALUE(Projection_focus_cell_index)
#define Projection_focus_cell_new_cached_value SPECIAL_VALUE(Projection_focus_cell_new_cached_value)
#define Projection_focus_method SPECIAL_VALUE(Projection_focus_method)
#define Projection_focus_path SPECIAL_VALUE(Projection_focus_path)
#define Projection_funcall_on_focus SPECIAL_VALUE(Projection_funcall_on_focus)
#define Projection_mode SPECIAL_VALUE(Projection_mode)
#define Projection_of_new_table_accumulating_size SPECIAL_VALUE(Projection_of_new_table_accumulating_size)
#define Projection_tracking SPECIAL_VALUE(Projection_tracking)
#define Projection_update_dependencies SPECIAL_VALUE(Projection_update_dependencies)
#define Prop_grid_contents SPECIAL_VALUE(Prop_grid_contents)
#define Prop_grid_verb_count SPECIAL_VALUE(Prop_grid_verb_count)
#define Property_grid_count SPECIAL_VALUE(Property_grid_count)
#define Property_grid_node_count SPECIAL_VALUE(Property_grid_node_count)
#define Prune_token_categories_visited_more_than_once_p SPECIAL_VALUE(Prune_token_categories_visited_more_than_once_p)
#define Pseudo_attribute_count SPECIAL_VALUE(Pseudo_attribute_count)
#define Pseudo_class_slot_description SPECIAL_VALUE(Pseudo_class_slot_description)
#define Pseudo_frame_count SPECIAL_VALUE(Pseudo_frame_count)
#define Pseudo_instruction_stream_count SPECIAL_VALUE(Pseudo_instruction_stream_count)
#define Pseudo_keysyms SPECIAL_VALUE(Pseudo_keysyms)
#define Pulse_rate_multiplier SPECIAL_VALUE(Pulse_rate_multiplier)
#define Pulse_rate_options SPECIAL_VALUE(Pulse_rate_options)
#define Purpose_of_extreme_edges SPECIAL_VALUE(Purpose_of_extreme_edges)
#define Purpose_of_frame_projecting SPECIAL_VALUE(Purpose_of_frame_projecting)
#define Push_button_cv_count SPECIAL_VALUE(Push_button_cv_count)
#define Put_current_evaluation_value_old_value_qm SPECIAL_VALUE(Put_current_evaluation_value_old_value_qm)
#define Put_current_evaluation_value_return_value SPECIAL_VALUE(Put_current_evaluation_value_return_value)
#define Put_current_value_called_from_simulator_p SPECIAL_VALUE(Put_current_value_called_from_simulator_p)
#define Quality_of_graphic_element SPECIAL_VALUE(Quality_of_graphic_element)
#define Quantitative_parameter_class_description SPECIAL_VALUE(Quantitative_parameter_class_description)
#define Quantitative_variable_class_description SPECIAL_VALUE(Quantitative_variable_class_description)
#define Quantity_array_class_description SPECIAL_VALUE(Quantity_array_class_description)
#define Quantity_cv_count SPECIAL_VALUE(Quantity_cv_count)
#define Quantity_list_class_description SPECIAL_VALUE(Quantity_list_class_description)
#define Query_cell_stream_count SPECIAL_VALUE(Query_cell_stream_count)
#define Question_mark_box_class_description SPECIAL_VALUE(Question_mark_box_class_description)
#define Queue_count SPECIAL_VALUE(Queue_count)
#define Queue_element_count SPECIAL_VALUE(Queue_element_count)
#define Queue_existential_rules SPECIAL_VALUE(Queue_existential_rules)
#define Queue_existential_rules_tail SPECIAL_VALUE(Queue_existential_rules_tail)
#define Queue_item_cons_counter SPECIAL_VALUE(Queue_item_cons_counter)
#define Queue_of_active_gfi_input_interface_objects SPECIAL_VALUE(Queue_of_active_gfi_input_interface_objects)
#define Queue_of_active_gfi_output_interface_objects SPECIAL_VALUE(Queue_of_active_gfi_output_interface_objects)
#define Queue_of_active_uninterruptable_gfi_input_interface_objects SPECIAL_VALUE(Queue_of_active_uninterruptable_gfi_input_interface_objects)
#define Queue_of_active_uninterruptable_gfi_output_interface_objects SPECIAL_VALUE(Queue_of_active_uninterruptable_gfi_output_interface_objects)
#define Queue_of_classes_to_be_undefined SPECIAL_VALUE(Queue_of_classes_to_be_undefined)
#define Radio_button_status_flags SPECIAL_VALUE(Radio_button_status_flags)
#define Radio_button_status_flags_1 SPECIAL_VALUE(Radio_button_status_flags_1)
#define Ran_out_of_time_qm SPECIAL_VALUE(Ran_out_of_time_qm)
#define Random_real_0_result SPECIAL_VALUE(Random_real_0_result)
#define Random_state_array SPECIAL_VALUE(Random_state_array)
#define Random_state_array_24_pointer SPECIAL_VALUE(Random_state_array_24_pointer)
#define Random_state_array_current_pointer SPECIAL_VALUE(Random_state_array_current_pointer)
#define Random_variation SPECIAL_VALUE(Random_variation)
#define Random_variation_2 SPECIAL_VALUE(Random_variation_2)
#define Range_too_small_qm SPECIAL_VALUE(Range_too_small_qm)
#define Read_kb_buffer SPECIAL_VALUE(Read_kb_buffer)
#define Read_kb_buffer_index SPECIAL_VALUE(Read_kb_buffer_index)
#define Read_kb_buffer_length SPECIAL_VALUE(Read_kb_buffer_length)
#define Read_kb_next_character SPECIAL_VALUE(Read_kb_next_character)
#define Read_kb_stream SPECIAL_VALUE(Read_kb_stream)
#define Read_ok_file_buffer_1 SPECIAL_VALUE(Read_ok_file_buffer_1)
#define Read_xml_line SPECIAL_VALUE(Read_xml_line)
#define Reading_ghost_definitions_p SPECIAL_VALUE(Reading_ghost_definitions_p)
#define Reading_initial_plist_for_clear_text_kb SPECIAL_VALUE(Reading_initial_plist_for_clear_text_kb)
#define Reading_kb_p SPECIAL_VALUE(Reading_kb_p)
#define Reading_ok_file SPECIAL_VALUE(Reading_ok_file)
#define Readout_table_class_description SPECIAL_VALUE(Readout_table_class_description)
#define Readout_table_spot_count SPECIAL_VALUE(Readout_table_spot_count)
#define Real_time_of_last_g2_tick SPECIAL_VALUE(Real_time_of_last_g2_tick)
#define Real_time_to_tick_p_base SPECIAL_VALUE(Real_time_to_tick_p_base)
#define Really_large_byte_vector SPECIAL_VALUE(Really_large_byte_vector)
#define Reason_for_type_failure SPECIAL_VALUE(Reason_for_type_failure)
#define Receiving_resumable_object_count SPECIAL_VALUE(Receiving_resumable_object_count)
#define Receiving_rpc_arglist_structure_count SPECIAL_VALUE(Receiving_rpc_arglist_structure_count)
#define Recent_enough_g2_revision_for_trend_charts SPECIAL_VALUE(Recent_enough_g2_revision_for_trend_charts)
#define Recent_loaded_kbs SPECIAL_VALUE(Recent_loaded_kbs)
#define Reclaim_fonts_stack SPECIAL_VALUE(Reclaim_fonts_stack)
#define Reclaim_text_value_from_postponed_erase_p SPECIAL_VALUE(Reclaim_text_value_from_postponed_erase_p)
#define Reclaimed_strings_reported SPECIAL_VALUE(Reclaimed_strings_reported)
#define Reclaimed_telewindows_boxes SPECIAL_VALUE(Reclaimed_telewindows_boxes)
#define Reclaimed_temporary_character_bitmaps SPECIAL_VALUE(Reclaimed_temporary_character_bitmaps)
#define Reclaimed_things SPECIAL_VALUE(Reclaimed_things)
#define Recompile_from_inspect SPECIAL_VALUE(Recompile_from_inspect)
#define Recompile_on_next_load SPECIAL_VALUE(Recompile_on_next_load)
#define Record_class_name_conflicts_qm SPECIAL_VALUE(Record_class_name_conflicts_qm)
#define Record_definitional_name_conflicts_qm SPECIAL_VALUE(Record_definitional_name_conflicts_qm)
#define Record_fixnum_time_units_of_sleep_this_clock_tick_qm SPECIAL_VALUE(Record_fixnum_time_units_of_sleep_this_clock_tick_qm)
#define Record_of_class_name_conflicts_qm SPECIAL_VALUE(Record_of_class_name_conflicts_qm)
#define Record_of_definitional_name_conflicts_qm SPECIAL_VALUE(Record_of_definitional_name_conflicts_qm)
#define Recording_items_made_incomplete_qm SPECIAL_VALUE(Recording_items_made_incomplete_qm)
#define Recursive_depth SPECIAL_VALUE(Recursive_depth)
#define Recycled_icp_buffers SPECIAL_VALUE(Recycled_icp_buffers)
#define Recycled_resumption_conses SPECIAL_VALUE(Recycled_resumption_conses)
#define Recycled_variable_fill_icp_buffers SPECIAL_VALUE(Recycled_variable_fill_icp_buffers)
#define Redef_class_instance SPECIAL_VALUE(Redef_class_instance)
#define Redo_saved_changes SPECIAL_VALUE(Redo_saved_changes)
#define Redraw_as_well_as_reformat_p SPECIAL_VALUE(Redraw_as_well_as_reformat_p)
#define Reference_class_info_p SPECIAL_VALUE(Reference_class_info_p)
#define Reference_date_for_interval_encoding SPECIAL_VALUE(Reference_date_for_interval_encoding)
#define Reference_serial_number_for_saved_detail_pane_description SPECIAL_VALUE(Reference_serial_number_for_saved_detail_pane_description)
#define Reference_structure_count SPECIAL_VALUE(Reference_structure_count)
#define Reference_structures_originating_from_within_existence_predicate SPECIAL_VALUE(Reference_structures_originating_from_within_existence_predicate)
#define Reformat_as_appropriate_qm SPECIAL_VALUE(Reformat_as_appropriate_qm)
#define Refresh_all_windows_after_merging_qm SPECIAL_VALUE(Refresh_all_windows_after_merging_qm)
#define Refused_icp_listener_connections SPECIAL_VALUE(Refused_icp_listener_connections)
#define Regexp_cons_counter SPECIAL_VALUE(Regexp_cons_counter)
#define Regexp_preprocessing_parser SPECIAL_VALUE(Regexp_preprocessing_parser)
#define Region_1_info SPECIAL_VALUE(Region_1_info)
#define Region_2_info SPECIAL_VALUE(Region_2_info)
#define Region_3_info SPECIAL_VALUE(Region_3_info)
#define Region_and_tile_x_offset SPECIAL_VALUE(Region_and_tile_x_offset)
#define Region_and_tile_y_offset SPECIAL_VALUE(Region_and_tile_y_offset)
#define Region_bounds_and_raster_count SPECIAL_VALUE(Region_bounds_and_raster_count)
#define Region_cons_counter SPECIAL_VALUE(Region_cons_counter)
#define Region_invalidation_is_preferred SPECIAL_VALUE(Region_invalidation_is_preferred)
#define Region_x_max_qm SPECIAL_VALUE(Region_x_max_qm)
#define Region_x_offset_qm SPECIAL_VALUE(Region_x_offset_qm)
#define Region_y_max_qm SPECIAL_VALUE(Region_y_max_qm)
#define Region_y_offset_qm SPECIAL_VALUE(Region_y_offset_qm)
#define Registered_activities_symbol_array SPECIAL_VALUE(Registered_activities_symbol_array)
#define Regular_expression_node_count SPECIAL_VALUE(Regular_expression_node_count)
#define Regular_expression_node_for_set_of_characters_count SPECIAL_VALUE(Regular_expression_node_for_set_of_characters_count)
#define Regular_expression_node_for_single_character_count SPECIAL_VALUE(Regular_expression_node_for_single_character_count)
#define Regular_expression_node_for_single_wild_character_count SPECIAL_VALUE(Regular_expression_node_for_single_wild_character_count)
#define Regular_expression_node_for_subexpression_count SPECIAL_VALUE(Regular_expression_node_for_subexpression_count)
#define Regular_expression_node_for_wild_characters_count SPECIAL_VALUE(Regular_expression_node_for_wild_characters_count)
#define Regular_expression_parser SPECIAL_VALUE(Regular_expression_parser)
#define Regular_expression_tokenizer SPECIAL_VALUE(Regular_expression_tokenizer)
#define Relation_class_description SPECIAL_VALUE(Relation_class_description)
#define Relation_instance_count SPECIAL_VALUE(Relation_instance_count)
#define Relations_tag_list SPECIAL_VALUE(Relations_tag_list)
#define Relative_time_pane_count SPECIAL_VALUE(Relative_time_pane_count)
#define Releasing_kb_qm SPECIAL_VALUE(Releasing_kb_qm)
#define Remaining_bytes_in_g2binary_data SPECIAL_VALUE(Remaining_bytes_in_g2binary_data)
#define Remaining_number_of_size_pieces_of_frame SPECIAL_VALUE(Remaining_number_of_size_pieces_of_frame)
#define Remaining_space_for_variable_size_pieces_of_frame SPECIAL_VALUE(Remaining_space_for_variable_size_pieces_of_frame)
#define Remote_gsi_interface_list SPECIAL_VALUE(Remote_gsi_interface_list)
#define Remote_procedure_call_count SPECIAL_VALUE(Remote_procedure_call_count)
#define Remote_procedure_declaration_class_description SPECIAL_VALUE(Remote_procedure_declaration_class_description)
#define Remote_procedure_identifier_array SPECIAL_VALUE(Remote_procedure_identifier_array)
#define Remote_procedure_identifier_count SPECIAL_VALUE(Remote_procedure_identifier_count)
#define Remote_procedure_item_passing_info_count SPECIAL_VALUE(Remote_procedure_item_passing_info_count)
#define Remote_procedure_name_count SPECIAL_VALUE(Remote_procedure_name_count)
#define Remote_query_id_for_kb_recompile SPECIAL_VALUE(Remote_query_id_for_kb_recompile)
#define Remote_value_is_binary_p SPECIAL_VALUE(Remote_value_is_binary_p)
#define Remote_value_known_typetag SPECIAL_VALUE(Remote_value_known_typetag)
#define Remove_as_inferior_block_1 SPECIAL_VALUE(Remove_as_inferior_block_1)
#define Remove_unused_labels SPECIAL_VALUE(Remove_unused_labels)
#define Rendezvous_successful_blocks_qm SPECIAL_VALUE(Rendezvous_successful_blocks_qm)
#define Replacement_token_menu_button_spot_count SPECIAL_VALUE(Replacement_token_menu_button_spot_count)
#define Report_filename_parsing_errors_in_development_p SPECIAL_VALUE(Report_filename_parsing_errors_in_development_p)
#define Represented_frames_in_limbo SPECIAL_VALUE(Represented_frames_in_limbo)
#define Required_definitions SPECIAL_VALUE(Required_definitions)
#define Required_token_types SPECIAL_VALUE(Required_token_types)
#define Resize_box_rubber_stamp_widget SPECIAL_VALUE(Resize_box_rubber_stamp_widget)
#define Resize_box_spot_count SPECIAL_VALUE(Resize_box_spot_count)
#define Resolving_definitional_name_conflicts_qm SPECIAL_VALUE(Resolving_definitional_name_conflicts_qm)
#define Restrict_edits_to_modules_having_read_only_files_p SPECIAL_VALUE(Restrict_edits_to_modules_having_read_only_files_p)
#define Result_end_time_system_variable_for_compute_trend_chart_time_bounds SPECIAL_VALUE(Result_end_time_system_variable_for_compute_trend_chart_time_bounds)
#define Result_index SPECIAL_VALUE(Result_index)
#define Result_of_ask_user_about_checking_pathname_out_for_editing SPECIAL_VALUE(Result_of_ask_user_about_checking_pathname_out_for_editing)
#define Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug SPECIAL_VALUE(Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug)
#define Result_timespan_system_variable_for_compute_trend_chart_time_bounds SPECIAL_VALUE(Result_timespan_system_variable_for_compute_trend_chart_time_bounds)
#define Resumable_circular_node_count SPECIAL_VALUE(Resumable_circular_node_count)
#define Resumable_evaluation_sequence_node_count SPECIAL_VALUE(Resumable_evaluation_sequence_node_count)
#define Resumable_evaluation_sequence_node_mixin_count SPECIAL_VALUE(Resumable_evaluation_sequence_node_mixin_count)
#define Resumable_evaluation_structure_node_count SPECIAL_VALUE(Resumable_evaluation_structure_node_count)
#define Resumable_history_node_count SPECIAL_VALUE(Resumable_history_node_count)
#define Resumable_icp_node_mixin_count SPECIAL_VALUE(Resumable_icp_node_mixin_count)
#define Resumable_icp_object_mixin_count SPECIAL_VALUE(Resumable_icp_object_mixin_count)
#define Resumable_icp_read_ignore_p SPECIAL_VALUE(Resumable_icp_read_ignore_p)
#define Resumable_icp_state SPECIAL_VALUE(Resumable_icp_state)
#define Resumable_instance_node_mixin_count SPECIAL_VALUE(Resumable_instance_node_mixin_count)
#define Resumable_instance_or_complex_value_node_mixin_count SPECIAL_VALUE(Resumable_instance_or_complex_value_node_mixin_count)
#define Resumable_list_node_mixin_count SPECIAL_VALUE(Resumable_list_node_mixin_count)
#define Resumable_node_mixin_count SPECIAL_VALUE(Resumable_node_mixin_count)
#define Resumable_object_list_node_count SPECIAL_VALUE(Resumable_object_list_node_count)
#define Resumable_object_mixin_count SPECIAL_VALUE(Resumable_object_mixin_count)
#define Resumable_object_node_count SPECIAL_VALUE(Resumable_object_node_count)
#define Resumable_object_vector_node_count SPECIAL_VALUE(Resumable_object_vector_node_count)
#define Resumable_priority_of_gsi_data_service SPECIAL_VALUE(Resumable_priority_of_gsi_data_service)
#define Resumable_priority_of_gsi_rpc_service SPECIAL_VALUE(Resumable_priority_of_gsi_rpc_service)
#define Resumable_sequence_node_mixin_count SPECIAL_VALUE(Resumable_sequence_node_mixin_count)
#define Resumable_value_list_node_count SPECIAL_VALUE(Resumable_value_list_node_count)
#define Resumable_value_node_count SPECIAL_VALUE(Resumable_value_node_count)
#define Resumable_value_vector_node_count SPECIAL_VALUE(Resumable_value_vector_node_count)
#define Resumable_vector_node_mixin_count SPECIAL_VALUE(Resumable_vector_node_mixin_count)
#define Return_from_ask_user_about_checking_pathname_out_for_editing_p SPECIAL_VALUE(Return_from_ask_user_about_checking_pathname_out_for_editing_p)
#define Return_from_breakpoint_task SPECIAL_VALUE(Return_from_breakpoint_task)
#define Return_from_save_to_caller_for_continuation_qm SPECIAL_VALUE(Return_from_save_to_caller_for_continuation_qm)
#define Return_statement_processed_qm SPECIAL_VALUE(Return_statement_processed_qm)
#define Return_to_waiting_for_cvs_p SPECIAL_VALUE(Return_to_waiting_for_cvs_p)
#define Returned_values_description SPECIAL_VALUE(Returned_values_description)
#define Reusable_gensyms SPECIAL_VALUE(Reusable_gensyms)
#define Reverse_iso_latin1_special_character_code_map SPECIAL_VALUE(Reverse_iso_latin1_special_character_code_map)
#define Revert_marker SPECIAL_VALUE(Revert_marker)
#define Revert_to_fuzzy_cache_p SPECIAL_VALUE(Revert_to_fuzzy_cache_p)
#define Right_edge_in_window_of_graphic_element SPECIAL_VALUE(Right_edge_in_window_of_graphic_element)
#define Right_edge_of_draw_area SPECIAL_VALUE(Right_edge_of_draw_area)
#define Right_edge_of_frame SPECIAL_VALUE(Right_edge_of_frame)
#define Right_marker_for_cascading_menu_rubber_stamp_widget SPECIAL_VALUE(Right_marker_for_cascading_menu_rubber_stamp_widget)
#define Right_recursion_limit_list SPECIAL_VALUE(Right_recursion_limit_list)
#define Right_scroll_arrow_rubber_stamp_widget SPECIAL_VALUE(Right_scroll_arrow_rubber_stamp_widget)
#define Ring_buffer_for_history_time SPECIAL_VALUE(Ring_buffer_for_history_time)
#define Ring_buffer_queue_for_kfep SPECIAL_VALUE(Ring_buffer_queue_for_kfep)
#define Ring_buffer_state_count SPECIAL_VALUE(Ring_buffer_state_count)
#define Ring_raster_for_graph_count SPECIAL_VALUE(Ring_raster_for_graph_count)
#define Role_and_domains_for_nth_element_expression SPECIAL_VALUE(Role_and_domains_for_nth_element_expression)
#define Role_caching_enabled_qm SPECIAL_VALUE(Role_caching_enabled_qm)
#define Role_cons_counter SPECIAL_VALUE(Role_cons_counter)
#define Role_names_and_local_names_for_runtime_items SPECIAL_VALUE(Role_names_and_local_names_for_runtime_items)
#define Roman_character_map SPECIAL_VALUE(Roman_character_map)
#define Roman_font_special_character_code_map SPECIAL_VALUE(Roman_font_special_character_code_map)
#define Root_name_for_temp_file SPECIAL_VALUE(Root_name_for_temp_file)
#define Rotation_of_graphic_element SPECIAL_VALUE(Rotation_of_graphic_element)
#define Row SPECIAL_VALUE(Row)
#define Row_height SPECIAL_VALUE(Row_height)
#define Row_maximum SPECIAL_VALUE(Row_maximum)
#define Rpc_argument_count_override_qm SPECIAL_VALUE(Rpc_argument_count_override_qm)
#define Rpc_argument_list_error SPECIAL_VALUE(Rpc_argument_list_error)
#define Rpc_object_arguments_to_run_or_schedule_qm SPECIAL_VALUE(Rpc_object_arguments_to_run_or_schedule_qm)
#define Rpc_throw_tag SPECIAL_VALUE(Rpc_throw_tag)
#define Rule_certainty_var SPECIAL_VALUE(Rule_certainty_var)
#define Rule_class_description SPECIAL_VALUE(Rule_class_description)
#define Rule_expiration_var SPECIAL_VALUE(Rule_expiration_var)
#define Rule_instance_count SPECIAL_VALUE(Rule_instance_count)
#define Rule_local_name_references SPECIAL_VALUE(Rule_local_name_references)
#define Ruling_for_dial_class_description SPECIAL_VALUE(Ruling_for_dial_class_description)
#define Ruling_for_meter_class_description SPECIAL_VALUE(Ruling_for_meter_class_description)
#define Run_traverse_kb_xml_object_type SPECIAL_VALUE(Run_traverse_kb_xml_object_type)
#define Running_trace_function_p SPECIAL_VALUE(Running_trace_function_p)
#define Safe_to_access_attribute_display_update_interval_p SPECIAL_VALUE(Safe_to_access_attribute_display_update_interval_p)
#define Sample_and_hold_plot_in_representation_update_p SPECIAL_VALUE(Sample_and_hold_plot_in_representation_update_p)
#define Save_kb_state_for_system_procedure_save SPECIAL_VALUE(Save_kb_state_for_system_procedure_save)
#define Save_only_if_interrupting_qm SPECIAL_VALUE(Save_only_if_interrupting_qm)
#define Saved_breakpoint_level SPECIAL_VALUE(Saved_breakpoint_level)
#define Saved_detail_pane_description SPECIAL_VALUE(Saved_detail_pane_description)
#define Saved_directories_for_module_truename_search SPECIAL_VALUE(Saved_directories_for_module_truename_search)
#define Saved_initial_status SPECIAL_VALUE(Saved_initial_status)
#define Saved_local_var_vector SPECIAL_VALUE(Saved_local_var_vector)
#define Saved_position_or_next_lower_thing SPECIAL_VALUE(Saved_position_or_next_lower_thing)
#define Saved_source_stepping_level SPECIAL_VALUE(Saved_source_stepping_level)
#define Saved_tracing_level SPECIAL_VALUE(Saved_tracing_level)
#define Saved_warning_level SPECIAL_VALUE(Saved_warning_level)
#define Saving_context_count SPECIAL_VALUE(Saving_context_count)
#define Saving_kb_p SPECIAL_VALUE(Saving_kb_p)
#define Saving_parameters SPECIAL_VALUE(Saving_parameters)
#define Saw_more_than_one_machine_authorization_qm SPECIAL_VALUE(Saw_more_than_one_machine_authorization_qm)
#define Scale_y_data_points_qm SPECIAL_VALUE(Scale_y_data_points_qm)
#define Scaled_font_count SPECIAL_VALUE(Scaled_font_count)
#define Scanning_subparts_of_block SPECIAL_VALUE(Scanning_subparts_of_block)
#define Schedule_task_count SPECIAL_VALUE(Schedule_task_count)
#define Scheduled_remote_procedure_start_count SPECIAL_VALUE(Scheduled_remote_procedure_start_count)
#define Scheduler_enabled_qm SPECIAL_VALUE(Scheduler_enabled_qm)
#define Scheduler_has_been_initialized_p SPECIAL_VALUE(Scheduler_has_been_initialized_p)
#define Scope_conses SPECIAL_VALUE(Scope_conses)
#define Scrap_class_description SPECIAL_VALUE(Scrap_class_description)
#define Scratch_add_item_to_workspace SPECIAL_VALUE(Scratch_add_item_to_workspace)
#define Scratch_attribute_denotation SPECIAL_VALUE(Scratch_attribute_denotation)
#define Scratch_character_rectangle_array SPECIAL_VALUE(Scratch_character_rectangle_array)
#define Scratch_custom_event_denotation SPECIAL_VALUE(Scratch_custom_event_denotation)
#define Scratch_incomplete_painting_action SPECIAL_VALUE(Scratch_incomplete_painting_action)
#define Scratch_item_color_pattern_change_denotation SPECIAL_VALUE(Scratch_item_color_pattern_change_denotation)
#define Scratch_item_event_denotation SPECIAL_VALUE(Scratch_item_event_denotation)
#define Scratch_rectangle_region SPECIAL_VALUE(Scratch_rectangle_region)
#define Scratch_remove_item_from_workspace SPECIAL_VALUE(Scratch_remove_item_from_workspace)
#define Scratch_variable_value_denotation SPECIAL_VALUE(Scratch_variable_value_denotation)
#define Scratch_virtual_attribute_denotation SPECIAL_VALUE(Scratch_virtual_attribute_denotation)
#define Scratchpad_raster SPECIAL_VALUE(Scratchpad_raster)
#define Scroll_bar_elevator_rubber_stamp_widget SPECIAL_VALUE(Scroll_bar_elevator_rubber_stamp_widget)
#define Search_state_table_spot_count SPECIAL_VALUE(Search_state_table_spot_count)
#define Secret_return_value SPECIAL_VALUE(Secret_return_value)
#define See_also_for_warn_about_editing_item SPECIAL_VALUE(See_also_for_warn_about_editing_item)
#define Selected_file_progress_attributes_to_show_subsets_plist SPECIAL_VALUE(Selected_file_progress_attributes_to_show_subsets_plist)
#define Selected_module_load_request_attributes_to_show_subsets_plist SPECIAL_VALUE(Selected_module_load_request_attributes_to_show_subsets_plist)
#define Selection_count SPECIAL_VALUE(Selection_count)
#define Selection_handle_icon SPECIAL_VALUE(Selection_handle_icon)
#define Selection_handle_spot_count SPECIAL_VALUE(Selection_handle_spot_count)
#define Selection_rectangle_state_count SPECIAL_VALUE(Selection_rectangle_state_count)
#define Semi_open_category_map SPECIAL_VALUE(Semi_open_category_map)
#define Send_image_data_immediately_qm SPECIAL_VALUE(Send_image_data_immediately_qm)
#define Send_logbook_messages_to_console_p SPECIAL_VALUE(Send_logbook_messages_to_console_p)
#define Send_messages_to_console_p SPECIAL_VALUE(Send_messages_to_console_p)
#define Send_messages_to_logbook_p SPECIAL_VALUE(Send_messages_to_logbook_p)
#define Sending_i_am_alive_qm SPECIAL_VALUE(Sending_i_am_alive_qm)
#define Sending_resumable_object_count SPECIAL_VALUE(Sending_resumable_object_count)
#define Sensor_group_count SPECIAL_VALUE(Sensor_group_count)
#define Sensor_groups_header_count SPECIAL_VALUE(Sensor_groups_header_count)
#define Separate_imminent_actions_p SPECIAL_VALUE(Separate_imminent_actions_p)
#define Sequence_cons_counter SPECIAL_VALUE(Sequence_cons_counter)
#define Serial_number_in_ok_file SPECIAL_VALUE(Serial_number_in_ok_file)
#define Server_parameters SPECIAL_VALUE(Server_parameters)
#define Service_workstations SPECIAL_VALUE(Service_workstations)
#define Servicing_workstation_event SPECIAL_VALUE(Servicing_workstation_event)
#define Servicing_workstation_qm SPECIAL_VALUE(Servicing_workstation_qm)
#define Set_of_all_component_kinds SPECIAL_VALUE(Set_of_all_component_kinds)
#define Set_of_all_permanent_computation_style SPECIAL_VALUE(Set_of_all_permanent_computation_style)
#define Set_of_possible_phrases_count SPECIAL_VALUE(Set_of_possible_phrases_count)
#define Set_of_variables_to_simulation_evaluate SPECIAL_VALUE(Set_of_variables_to_simulation_evaluate)
#define Shift_jis_transcoder_count SPECIAL_VALUE(Shift_jis_transcoder_count)
#define Shift_variant_for_cursor_movement_p SPECIAL_VALUE(Shift_variant_for_cursor_movement_p)
#define Short_duration_cv_count SPECIAL_VALUE(Short_duration_cv_count)
#define Short_menus_qm SPECIAL_VALUE(Short_menus_qm)
#define Short_representation_table_spot_count SPECIAL_VALUE(Short_representation_table_spot_count)
#define Short_simple_gensym_string_counts SPECIAL_VALUE(Short_simple_gensym_string_counts)
#define Short_simple_gensym_strings SPECIAL_VALUE(Short_simple_gensym_strings)
#define Shortcut_bar_count SPECIAL_VALUE(Shortcut_bar_count)
#define Show_deletions_in_xml_changes_p SPECIAL_VALUE(Show_deletions_in_xml_changes_p)
#define Show_parameters_decoder_count SPECIAL_VALUE(Show_parameters_decoder_count)
#define Show_procedure_invocation_hierarchy_on_debugger_pause_p SPECIAL_VALUE(Show_procedure_invocation_hierarchy_on_debugger_pause_p)
#define Show_stack_bytes_qm SPECIAL_VALUE(Show_stack_bytes_qm)
#define Shredded_raster_count SPECIAL_VALUE(Shredded_raster_count)
#define Shunned_machine_ids_list SPECIAL_VALUE(Shunned_machine_ids_list)
#define Shutdown_catch_tag SPECIAL_VALUE(Shutdown_catch_tag)
#define Shutdown_interval_for_disallowed_icp_connection SPECIAL_VALUE(Shutdown_interval_for_disallowed_icp_connection)
#define Shutdown_interval_for_disallowed_icp_connection_in_seconds SPECIAL_VALUE(Shutdown_interval_for_disallowed_icp_connection_in_seconds)
#define Sigfpe SPECIAL_VALUE(Sigfpe)
#define Signal_code_registry SPECIAL_VALUE(Signal_code_registry)
#define Simple_dialog_fill_text_p SPECIAL_VALUE(Simple_dialog_fill_text_p)
#define Simple_dialog_plist_qm SPECIAL_VALUE(Simple_dialog_plist_qm)
#define Simple_dialog_title_qm SPECIAL_VALUE(Simple_dialog_title_qm)
#define Simple_float_array_pool_memory_usage SPECIAL_VALUE(Simple_float_array_pool_memory_usage)
#define Simple_for_image_plane SPECIAL_VALUE(Simple_for_image_plane)
#define Simple_gensym_string_byte_use_counter SPECIAL_VALUE(Simple_gensym_string_byte_use_counter)
#define Simple_gensym_string_counter SPECIAL_VALUE(Simple_gensym_string_counter)
#define Simple_item_spot_count SPECIAL_VALUE(Simple_item_spot_count)
#define Simple_long_array_pool_memory_usage SPECIAL_VALUE(Simple_long_array_pool_memory_usage)
#define Simple_string_stats_header_needed SPECIAL_VALUE(Simple_string_stats_header_needed)
#define Simple_string_stats_namestring SPECIAL_VALUE(Simple_string_stats_namestring)
#define Simple_vector_pool_counts SPECIAL_VALUE(Simple_vector_pool_counts)
#define Simple_vector_pool_memory_usage SPECIAL_VALUE(Simple_vector_pool_memory_usage)
#define Simulate_cons_counter SPECIAL_VALUE(Simulate_cons_counter)
#define Simulate_proprietary_qm SPECIAL_VALUE(Simulate_proprietary_qm)
#define Simulation_info_count SPECIAL_VALUE(Simulation_info_count)
#define Simulation_no_value SPECIAL_VALUE(Simulation_no_value)
#define Simulation_parameters SPECIAL_VALUE(Simulation_parameters)
#define Simulation_procedure_completion_form SPECIAL_VALUE(Simulation_procedure_completion_form)
#define Simulation_subtable_class_description SPECIAL_VALUE(Simulation_subtable_class_description)
#define Simulation_time_accumulator SPECIAL_VALUE(Simulation_time_accumulator)
#define Simulation_time_managed_float SPECIAL_VALUE(Simulation_time_managed_float)
#define Simulator_initialized_as_data_server_qm SPECIAL_VALUE(Simulator_initialized_as_data_server_qm)
#define Single_element_string SPECIAL_VALUE(Single_element_string)
#define Single_escape_character_for_gensym_filenames SPECIAL_VALUE(Single_escape_character_for_gensym_filenames)
#define Size_of_cached_subsequence_for_resumable_history SPECIAL_VALUE(Size_of_cached_subsequence_for_resumable_history)
#define Size_of_icon_slot_group SPECIAL_VALUE(Size_of_icon_slot_group)
#define Skip_list_element_count SPECIAL_VALUE(Skip_list_element_count)
#define Skip_list_find_preds SPECIAL_VALUE(Skip_list_find_preds)
#define Skip_list_find_succs SPECIAL_VALUE(Skip_list_find_succs)
#define Slider_minimum_value_label_class_description SPECIAL_VALUE(Slider_minimum_value_label_class_description)
#define Slider_needle_class_description SPECIAL_VALUE(Slider_needle_class_description)
#define Slider_readout_class_description SPECIAL_VALUE(Slider_readout_class_description)
#define Slider_spot_count SPECIAL_VALUE(Slider_spot_count)
#define Slot_alias_for_restrictions SPECIAL_VALUE(Slot_alias_for_restrictions)
#define Slot_component_descriptor_count SPECIAL_VALUE(Slot_component_descriptor_count)
#define Slot_description_count SPECIAL_VALUE(Slot_description_count)
#define Slot_description_for_restrictions SPECIAL_VALUE(Slot_description_for_restrictions)
#define Slot_description_for_slot_value_being_read_qm SPECIAL_VALUE(Slot_description_for_slot_value_being_read_qm)
#define Slot_name_for_write_frame_for_kb SPECIAL_VALUE(Slot_name_for_write_frame_for_kb)
#define Slot_pad_of_ok_file_reader SPECIAL_VALUE(Slot_pad_of_ok_file_reader)
#define Slot_value_cons_counter SPECIAL_VALUE(Slot_value_cons_counter)
#define Slot_value_for_write_frame_for_kb SPECIAL_VALUE(Slot_value_for_write_frame_for_kb)
#define Slots_containing_circular_unnamed_simple_vectors SPECIAL_VALUE(Slots_containing_circular_unnamed_simple_vectors)
#define Slots_to_skip_saving_in_ok_files SPECIAL_VALUE(Slots_to_skip_saving_in_ok_files)
#define Smoothed_subsecond_adjustment SPECIAL_VALUE(Smoothed_subsecond_adjustment)
#define Snapshot_invocation_info_count SPECIAL_VALUE(Snapshot_invocation_info_count)
#define Snapshot_of_block_count SPECIAL_VALUE(Snapshot_of_block_count)
#define Snapshots_of_related_blocks SPECIAL_VALUE(Snapshots_of_related_blocks)
#define Socket_count SPECIAL_VALUE(Socket_count)
#define Socket_output_buffer_count SPECIAL_VALUE(Socket_output_buffer_count)
#define Some_module_is_clear_text_p SPECIAL_VALUE(Some_module_is_clear_text_p)
#define Sorted_static_evaluate_role_dispatchers SPECIAL_VALUE(Sorted_static_evaluate_role_dispatchers)
#define Source_code_control_grammar_is_present_p SPECIAL_VALUE(Source_code_control_grammar_is_present_p)
#define Source_code_control_is_enabled_by_default SPECIAL_VALUE(Source_code_control_is_enabled_by_default)
#define Source_code_control_support_enabled_p SPECIAL_VALUE(Source_code_control_support_enabled_p)
#define Source_designations_from_explicit_iteration_forms SPECIAL_VALUE(Source_designations_from_explicit_iteration_forms)
#define Source_nupec_synchronization_count SPECIAL_VALUE(Source_nupec_synchronization_count)
#define Source_stepping_level SPECIAL_VALUE(Source_stepping_level)
#define Sparse_array_count SPECIAL_VALUE(Sparse_array_count)
#define Sparse_known_pathnames_list SPECIAL_VALUE(Sparse_known_pathnames_list)
#define Spawn_command_line_process_failure SPECIAL_VALUE(Spawn_command_line_process_failure)
#define Special_globally_known_references SPECIAL_VALUE(Special_globally_known_references)
#define Special_slot_names_for_memory_walk SPECIAL_VALUE(Special_slot_names_for_memory_walk)
#define Special_variable_for_use_value_macro SPECIAL_VALUE(Special_variable_for_use_value_macro)
#define Specific_structure_for_current_workstation_context SPECIAL_VALUE(Specific_structure_for_current_workstation_context)
#define Specified_kfep_index_filename_qm SPECIAL_VALUE(Specified_kfep_index_filename_qm)
#define Specified_kfep_kojin_filename_qm SPECIAL_VALUE(Specified_kfep_kojin_filename_qm)
#define Specified_kfep_main_filename_qm SPECIAL_VALUE(Specified_kfep_main_filename_qm)
#define Speedup_tagname_string SPECIAL_VALUE(Speedup_tagname_string)
#define Speedup_tagname_string_index SPECIAL_VALUE(Speedup_tagname_string_index)
#define Spinner_cv_count SPECIAL_VALUE(Spinner_cv_count)
#define Spot_count SPECIAL_VALUE(Spot_count)
#define Stack_change_cons_counter SPECIAL_VALUE(Stack_change_cons_counter)
#define Stack_cons_counter SPECIAL_VALUE(Stack_cons_counter)
#define Stack_eval_qm SPECIAL_VALUE(Stack_eval_qm)
#define Stack_expiration SPECIAL_VALUE(Stack_expiration)
#define Stack_frame_vars_ok_in_procedure_qm SPECIAL_VALUE(Stack_frame_vars_ok_in_procedure_qm)
#define Stack_instructions SPECIAL_VALUE(Stack_instructions)
#define Stack_node_count SPECIAL_VALUE(Stack_node_count)
#define Stack_node_instruction_count SPECIAL_VALUE(Stack_node_instruction_count)
#define Stack_nodes_to_reclaim SPECIAL_VALUE(Stack_nodes_to_reclaim)
#define Stack_of_current_part_descriptions SPECIAL_VALUE(Stack_of_current_part_descriptions)
#define Stack_of_deferred_notification_strings SPECIAL_VALUE(Stack_of_deferred_notification_strings)
#define Stack_of_slot_value_changes SPECIAL_VALUE(Stack_of_slot_value_changes)
#define Standard_8_bit_non_graphic_characters_skip_spec SPECIAL_VALUE(Standard_8_bit_non_graphic_characters_skip_spec)
#define Standard_gensym_color_alist SPECIAL_VALUE(Standard_gensym_color_alist)
#define Star_character_index SPECIAL_VALUE(Star_character_index)
#define Star_character_index_in_string_to_insert_qm SPECIAL_VALUE(Star_character_index_in_string_to_insert_qm)
#define Star_character_index_of_change_qm SPECIAL_VALUE(Star_character_index_of_change_qm)
#define Star_character_index_past_deletion_qm SPECIAL_VALUE(Star_character_index_past_deletion_qm)
#define Star_current_indentation SPECIAL_VALUE(Star_current_indentation)
#define Star_explicit_paragraph_or_newline_qm SPECIAL_VALUE(Star_explicit_paragraph_or_newline_qm)
#define Star_line_buffer SPECIAL_VALUE(Star_line_buffer)
#define Star_line_buffer_fill_pointer SPECIAL_VALUE(Star_line_buffer_fill_pointer)
#define Star_line_buffer_limit SPECIAL_VALUE(Star_line_buffer_limit)
#define Star_line_index SPECIAL_VALUE(Star_line_index)
#define Star_line_index_of_change_qm SPECIAL_VALUE(Star_line_index_of_change_qm)
#define Star_line_index_past_deletion_qm SPECIAL_VALUE(Star_line_index_past_deletion_qm)
#define Star_line_length SPECIAL_VALUE(Star_line_length)
#define Star_lost_space_at_end_of_line SPECIAL_VALUE(Star_lost_space_at_end_of_line)
#define Star_next_text_tail_qm SPECIAL_VALUE(Star_next_text_tail_qm)
#define Star_string_to_insert_qm SPECIAL_VALUE(Star_string_to_insert_qm)
#define Star_text_line SPECIAL_VALUE(Star_text_line)
#define Star_text_line_is_simple_qm SPECIAL_VALUE(Star_text_line_is_simple_qm)
#define Star_text_string_to_insert_is_simple_qm SPECIAL_VALUE(Star_text_string_to_insert_is_simple_qm)
#define Star_this_text_tail_qm SPECIAL_VALUE(Star_this_text_tail_qm)
#define State_transition_count SPECIAL_VALUE(State_transition_count)
#define Statement_class_description SPECIAL_VALUE(Statement_class_description)
#define Static_attributes SPECIAL_VALUE(Static_attributes)
#define Status_bar_count SPECIAL_VALUE(Status_bar_count)
#define Status_bar_pane_count SPECIAL_VALUE(Status_bar_pane_count)
#define Status_pane_spot_count SPECIAL_VALUE(Status_pane_spot_count)
#define Stepper_of_scroll_bar_spot_count SPECIAL_VALUE(Stepper_of_scroll_bar_spot_count)
#define Strange_cons SPECIAL_VALUE(Strange_cons)
#define Streams_cons_counter SPECIAL_VALUE(Streams_cons_counter)
#define Strict_subcategory_info_count SPECIAL_VALUE(Strict_subcategory_info_count)
#define Strict_subcategory_info_last_category_1 SPECIAL_VALUE(Strict_subcategory_info_last_category_1)
#define Strict_subcategory_info_last_category_2 SPECIAL_VALUE(Strict_subcategory_info_last_category_2)
#define Strict_subcategory_info_last_result SPECIAL_VALUE(Strict_subcategory_info_last_result)
#define Strict_subcategory_infos_exist_p SPECIAL_VALUE(Strict_subcategory_infos_exist_p)
#define String_allocations_until_next_report SPECIAL_VALUE(String_allocations_until_next_report)
#define String_chars_to_print SPECIAL_VALUE(String_chars_to_print)
#define String_for_returning_floats SPECIAL_VALUE(String_for_returning_floats)
#define String_pool_cons_counter SPECIAL_VALUE(String_pool_cons_counter)
#define String_pool_number_to_malloc SPECIAL_VALUE(String_pool_number_to_malloc)
#define String_reclaims_until_next_report SPECIAL_VALUE(String_reclaims_until_next_report)
#define String_report_frequency SPECIAL_VALUE(String_report_frequency)
#define Stringw_should_not_cons_p SPECIAL_VALUE(Stringw_should_not_cons_p)
#define Structure_being_reclaimed SPECIAL_VALUE(Structure_being_reclaimed)
#define Structure_slot_not_bound SPECIAL_VALUE(Structure_slot_not_bound)
#define Structure_specs_allow_unknown_slots_p SPECIAL_VALUE(Structure_specs_allow_unknown_slots_p)
#define Stub_length_to_use_qm SPECIAL_VALUE(Stub_length_to_use_qm)
#define Sub_profiling_structure_count SPECIAL_VALUE(Sub_profiling_structure_count)
#define Subcommand_menu_button_spot_count SPECIAL_VALUE(Subcommand_menu_button_spot_count)
#define Subcommand_state_count SPECIAL_VALUE(Subcommand_state_count)
#define Subframe_depth SPECIAL_VALUE(Subframe_depth)
#define Subordinate_text_box_class_description SPECIAL_VALUE(Subordinate_text_box_class_description)
#define Subpart_defaults SPECIAL_VALUE(Subpart_defaults)
#define Subpart_exceptions SPECIAL_VALUE(Subpart_exceptions)
#define Subparts SPECIAL_VALUE(Subparts)
#define Subtract_arrays_instead_qm SPECIAL_VALUE(Subtract_arrays_instead_qm)
#define Subworkspace_currently_being_deleted_qm SPECIAL_VALUE(Subworkspace_currently_being_deleted_qm)
#define Success_of_ok_file_reader_qm SPECIAL_VALUE(Success_of_ok_file_reader_qm)
#define Superior_frame_being_cloned_qm SPECIAL_VALUE(Superior_frame_being_cloned_qm)
#define Superior_frame_for_restrictions_frame_qm SPECIAL_VALUE(Superior_frame_for_restrictions_frame_qm)
#define Superior_frame_for_restrictions_superior_qm SPECIAL_VALUE(Superior_frame_for_restrictions_superior_qm)
#define Supported_combining_classes SPECIAL_VALUE(Supported_combining_classes)
#define Supported_control_actions_by_id SPECIAL_VALUE(Supported_control_actions_by_id)
#define Supported_control_actions_by_symbol SPECIAL_VALUE(Supported_control_actions_by_symbol)
#define Supported_dialog_component_types SPECIAL_VALUE(Supported_dialog_component_types)
#define Supported_ok_file_format_version SPECIAL_VALUE(Supported_ok_file_format_version)
#define Supports_dialog_component_with_font SPECIAL_VALUE(Supports_dialog_component_with_font)
#define Supports_font_in_grid_view SPECIAL_VALUE(Supports_font_in_grid_view)
#define Supports_transparent_color_index SPECIAL_VALUE(Supports_transparent_color_index)
#define Suppress_consistency_analysis_warnings_notes_qm SPECIAL_VALUE(Suppress_consistency_analysis_warnings_notes_qm)
#define Suppress_notification_for_kb_save_qm SPECIAL_VALUE(Suppress_notification_for_kb_save_qm)
#define Suppress_scrolling_into_view_global_flag_qm SPECIAL_VALUE(Suppress_scrolling_into_view_global_flag_qm)
#define Suppress_updates_to_name_boxes SPECIAL_VALUE(Suppress_updates_to_name_boxes)
#define Suppress_updating_of_self_representations_qm SPECIAL_VALUE(Suppress_updating_of_self_representations_qm)
#define Suppress_updating_of_slot_value_representations_qm SPECIAL_VALUE(Suppress_updating_of_slot_value_representations_qm)
#define Suppress_use_of_stack_of_slot_value_changes_p SPECIAL_VALUE(Suppress_use_of_stack_of_slot_value_changes_p)
#define Suppress_warning_message_header_qm SPECIAL_VALUE(Suppress_warning_message_header_qm)
#define Symbol_array_class_description SPECIAL_VALUE(Symbol_array_class_description)
#define Symbol_list_class_description SPECIAL_VALUE(Symbol_list_class_description)
#define Symbol_tree_count SPECIAL_VALUE(Symbol_tree_count)
#define Symbolic_parameter_class_description SPECIAL_VALUE(Symbolic_parameter_class_description)
#define Symbolic_variable_class_description SPECIAL_VALUE(Symbolic_variable_class_description)
#define Symbols_not_to_add_to_semi_open_category_directories SPECIAL_VALUE(Symbols_not_to_add_to_semi_open_category_directories)
#define Synchronous_model_queue SPECIAL_VALUE(Synchronous_model_queue)
#define Sysproc_cons_counter SPECIAL_VALUE(Sysproc_cons_counter)
#define Sysproc_continuation_table SPECIAL_VALUE(Sysproc_continuation_table)
#define System_class_method_tables_processed_qm SPECIAL_VALUE(System_class_method_tables_processed_qm)
#define System_defined_rpcs SPECIAL_VALUE(System_defined_rpcs)
#define System_has_aborted SPECIAL_VALUE(System_has_aborted)
#define System_has_paused SPECIAL_VALUE(System_has_paused)
#define System_is_running SPECIAL_VALUE(System_is_running)
#define System_item_class_description SPECIAL_VALUE(System_item_class_description)
#define System_quality_from_last_kb_read SPECIAL_VALUE(System_quality_from_last_kb_read)
#define System_revision_from_last_kb_read SPECIAL_VALUE(System_revision_from_last_kb_read)
#define System_rpc_count SPECIAL_VALUE(System_rpc_count)
#define System_rpc_instance_count SPECIAL_VALUE(System_rpc_instance_count)
#define System_slot_accessor SPECIAL_VALUE(System_slot_accessor)
#define System_statistics_writers SPECIAL_VALUE(System_statistics_writers)
#define System_tables_read_for_this_module SPECIAL_VALUE(System_tables_read_for_this_module)
#define System_version_from_kb_being_read SPECIAL_VALUE(System_version_from_kb_being_read)
#define System_version_from_last_kb_read SPECIAL_VALUE(System_version_from_last_kb_read)
#define System_version_of_current_gensym_product_line SPECIAL_VALUE(System_version_of_current_gensym_product_line)
#define System_window SPECIAL_VALUE(System_window)
#define System_window_title_and_info_text_string_qm SPECIAL_VALUE(System_window_title_and_info_text_string_qm)
#define Systems_in_gensym_product_line SPECIAL_VALUE(Systems_in_gensym_product_line)
#define Systemtables_are_initialized_p SPECIAL_VALUE(Systemtables_are_initialized_p)
#define Systemtables_fixups SPECIAL_VALUE(Systemtables_fixups)
#define T2_dialog_result_alist SPECIAL_VALUE(T2_dialog_result_alist)
#define T2_nonce_data_count SPECIAL_VALUE(T2_nonce_data_count)
#define T2_nonce_table SPECIAL_VALUE(T2_nonce_table)
#define Tab_length_for_counter_report SPECIAL_VALUE(Tab_length_for_counter_report)
#define Table_background_spot_count SPECIAL_VALUE(Table_background_spot_count)
#define Table_class_description SPECIAL_VALUE(Table_class_description)
#define Table_header_spot_count SPECIAL_VALUE(Table_header_spot_count)
#define Table_menu_choices SPECIAL_VALUE(Table_menu_choices)
#define Table_representation_update_schedule SPECIAL_VALUE(Table_representation_update_schedule)
#define Table_spot_count SPECIAL_VALUE(Table_spot_count)
#define Table_to_map_generic_method_id_to_generic_method_name SPECIAL_VALUE(Table_to_map_generic_method_id_to_generic_method_name)
#define Table_to_map_structure_id_to_method_name SPECIAL_VALUE(Table_to_map_structure_id_to_method_name)
#define Tabular_function_class_description SPECIAL_VALUE(Tabular_function_class_description)
#define Tabular_function_of_1_arg_class_description SPECIAL_VALUE(Tabular_function_of_1_arg_class_description)
#define Tabular_view_action SPECIAL_VALUE(Tabular_view_action)
#define Tabular_view_count SPECIAL_VALUE(Tabular_view_count)
#define Target_nupec_synchronization_count SPECIAL_VALUE(Target_nupec_synchronization_count)
#define Task_for_display_of_simulation_time SPECIAL_VALUE(Task_for_display_of_simulation_time)
#define Task_scheduled_to_process_gsi_values_qm SPECIAL_VALUE(Task_scheduled_to_process_gsi_values_qm)
#define Task_to_process_g2ds_values SPECIAL_VALUE(Task_to_process_g2ds_values)
#define Task_to_process_gsi_interfaces SPECIAL_VALUE(Task_to_process_gsi_interfaces)
#define Task_to_process_gsi_values SPECIAL_VALUE(Task_to_process_gsi_values)
#define Task_to_run_service_workstations_final SPECIAL_VALUE(Task_to_run_service_workstations_final)
#define Task_to_warn_user_of_previously_aborted_g2 SPECIAL_VALUE(Task_to_warn_user_of_previously_aborted_g2)
#define Tcp_ip_port_offset_for_foreign_images SPECIAL_VALUE(Tcp_ip_port_offset_for_foreign_images)
#define Tcp_listener_port_number SPECIAL_VALUE(Tcp_listener_port_number)
#define Tcp_socket_count SPECIAL_VALUE(Tcp_socket_count)
#define Tcpip_external_foreign_image_prologue SPECIAL_VALUE(Tcpip_external_foreign_image_prologue)
#define Telewindows_authorized_products SPECIAL_VALUE(Telewindows_authorized_products)
#define Telewindows_license_level SPECIAL_VALUE(Telewindows_license_level)
#define Telewindows_screen_utilization SPECIAL_VALUE(Telewindows_screen_utilization)
#define Temporary_constant_count SPECIAL_VALUE(Temporary_constant_count)
#define Temporary_file_count SPECIAL_VALUE(Temporary_file_count)
#define Temporary_g2binary_file_symbol_indices SPECIAL_VALUE(Temporary_g2binary_file_symbol_indices)
#define Temporary_name_number_1 SPECIAL_VALUE(Temporary_name_number_1)
#define Temporary_name_number_2 SPECIAL_VALUE(Temporary_name_number_2)
#define Temporary_string_buffer SPECIAL_VALUE(Temporary_string_buffer)
#define Temporary_workspace_class_description SPECIAL_VALUE(Temporary_workspace_class_description)
#define Terminate_kb_save_stream_error_message_qm SPECIAL_VALUE(Terminate_kb_save_stream_error_message_qm)
#define Test_removal_of_unsigned_vector_16 SPECIAL_VALUE(Test_removal_of_unsigned_vector_16)
#define Testing_parsing_context_locally_p SPECIAL_VALUE(Testing_parsing_context_locally_p)
#define Text_array_class_description SPECIAL_VALUE(Text_array_class_description)
#define Text_box_class_description SPECIAL_VALUE(Text_box_class_description)
#define Text_box_cv_count SPECIAL_VALUE(Text_box_cv_count)
#define Text_box_spot_count SPECIAL_VALUE(Text_box_spot_count)
#define Text_conversion_style_for_transcoder_being_created SPECIAL_VALUE(Text_conversion_style_for_transcoder_being_created)
#define Text_inserter_spot_count SPECIAL_VALUE(Text_inserter_spot_count)
#define Text_line_for_line_of_text_of_graphic_element SPECIAL_VALUE(Text_line_for_line_of_text_of_graphic_element)
#define Text_list_class_description SPECIAL_VALUE(Text_list_class_description)
#define Text_marking_state_count SPECIAL_VALUE(Text_marking_state_count)
#define Text_of_definition_being_compiled SPECIAL_VALUE(Text_of_definition_being_compiled)
#define Text_parameter_class_description SPECIAL_VALUE(Text_parameter_class_description)
#define Text_region_class_description SPECIAL_VALUE(Text_region_class_description)
#define Text_representation_of_our_ok_object SPECIAL_VALUE(Text_representation_of_our_ok_object)
#define Text_sequence_count SPECIAL_VALUE(Text_sequence_count)
#define Text_spot_count SPECIAL_VALUE(Text_spot_count)
#define Text_time_stamp_seconds SPECIAL_VALUE(Text_time_stamp_seconds)
#define Text_tokenization_state_count SPECIAL_VALUE(Text_tokenization_state_count)
#define Text_value SPECIAL_VALUE(Text_value)
#define Text_value_from_postponed_erase SPECIAL_VALUE(Text_value_from_postponed_erase)
#define Text_variable_class_description SPECIAL_VALUE(Text_variable_class_description)
#define Text_xml_checksum SPECIAL_VALUE(Text_xml_checksum)
#define Tformat_fresh_line_is_newline_p SPECIAL_VALUE(Tformat_fresh_line_is_newline_p)
#define The_denotation_conversion_buffer SPECIAL_VALUE(The_denotation_conversion_buffer)
#define The_g2_defstruct_package SPECIAL_VALUE(The_g2_defstruct_package)
#define The_java_symbol_table SPECIAL_VALUE(The_java_symbol_table)
#define The_only_dynamic_computation_style SPECIAL_VALUE(The_only_dynamic_computation_style)
#define The_polygon_data_buffer SPECIAL_VALUE(The_polygon_data_buffer)
#define The_representation_handle_hashtable SPECIAL_VALUE(The_representation_handle_hashtable)
#define The_transform SPECIAL_VALUE(The_transform)
#define The_type_description_of_t SPECIAL_VALUE(The_type_description_of_t)
#define There_exists_p SPECIAL_VALUE(There_exists_p)
#define There_is_a_current_kb_qm SPECIAL_VALUE(There_is_a_current_kb_qm)
#define Things_that_affect_this_formula SPECIAL_VALUE(Things_that_affect_this_formula)
#define Thrashing_cost_update_interval SPECIAL_VALUE(Thrashing_cost_update_interval)
#define Thrashing_ratio_ring_buffer_count SPECIAL_VALUE(Thrashing_ratio_ring_buffer_count)
#define Throws_from_breakpoints_are_possible SPECIAL_VALUE(Throws_from_breakpoints_are_possible)
#define Tick_mark_part_to_draw SPECIAL_VALUE(Tick_mark_part_to_draw)
#define Tickmark_label_char_width SPECIAL_VALUE(Tickmark_label_char_width)
#define Tickmark_label_min_height SPECIAL_VALUE(Tickmark_label_min_height)
#define Tickmark_label_min_width SPECIAL_VALUE(Tickmark_label_min_width)
#define Tightest_end_of_loop_tag SPECIAL_VALUE(Tightest_end_of_loop_tag)
#define Tightness_of_text_spot_for_click_to_edit SPECIAL_VALUE(Tightness_of_text_spot_for_click_to_edit)
#define Tiled_raster_count SPECIAL_VALUE(Tiled_raster_count)
#define Tiling_pattern_count SPECIAL_VALUE(Tiling_pattern_count)
#define Time_of_day_cv_count SPECIAL_VALUE(Time_of_day_cv_count)
#define Time_of_frame_edit_base_time SPECIAL_VALUE(Time_of_frame_edit_base_time)
#define Time_of_last_call_to_set_user_password SPECIAL_VALUE(Time_of_last_call_to_set_user_password)
#define Time_of_last_expiration_check SPECIAL_VALUE(Time_of_last_expiration_check)
#define Time_of_last_synthetic_motion_event_qm SPECIAL_VALUE(Time_of_last_synthetic_motion_event_qm)
#define Time_of_last_thrashing_cost_update SPECIAL_VALUE(Time_of_last_thrashing_cost_update)
#define Time_of_last_uuid SPECIAL_VALUE(Time_of_last_uuid)
#define Time_slice_expired_p SPECIAL_VALUE(Time_slice_expired_p)
#define Time_slice_start_time SPECIAL_VALUE(Time_slice_start_time)
#define Time_to_check_network_events SPECIAL_VALUE(Time_to_check_network_events)
#define Time_used_to_adjust_histories_qm SPECIAL_VALUE(Time_used_to_adjust_histories_qm)
#define Timestamp_cons_counter SPECIAL_VALUE(Timestamp_cons_counter)
#define Timing_parameters SPECIAL_VALUE(Timing_parameters)
#define Title_bar_spot_count SPECIAL_VALUE(Title_bar_spot_count)
#define Token_cons_counter SPECIAL_VALUE(Token_cons_counter)
#define Token_menu_button_spot_count SPECIAL_VALUE(Token_menu_button_spot_count)
#define Token_sequence_location_plist SPECIAL_VALUE(Token_sequence_location_plist)
#define Token_stack_cons_counter SPECIAL_VALUE(Token_stack_cons_counter)
#define Tokenize_with_editing_context_p SPECIAL_VALUE(Tokenize_with_editing_context_p)
#define Top_edge_in_window_of_graphic_element SPECIAL_VALUE(Top_edge_in_window_of_graphic_element)
#define Top_edge_of_draw_area SPECIAL_VALUE(Top_edge_of_draw_area)
#define Top_edge_of_frame SPECIAL_VALUE(Top_edge_of_frame)
#define Top_level_error_catcher_tag SPECIAL_VALUE(Top_level_error_catcher_tag)
#define Top_level_error_seen SPECIAL_VALUE(Top_level_error_seen)
#define Top_level_reference_tree SPECIAL_VALUE(Top_level_reference_tree)
#define Top_level_state_count SPECIAL_VALUE(Top_level_state_count)
#define Top_scroll_arrow_rubber_stamp_widget SPECIAL_VALUE(Top_scroll_arrow_rubber_stamp_widget)
#define Total_foreign_image_connection_checkup_interval_in_ms SPECIAL_VALUE(Total_foreign_image_connection_checkup_interval_in_ms)
#define Total_items_in_file SPECIAL_VALUE(Total_items_in_file)
#define Total_length_of_current_gensym_string SPECIAL_VALUE(Total_length_of_current_gensym_string)
#define Total_length_of_current_wide_string SPECIAL_VALUE(Total_length_of_current_wide_string)
#define Trace_compiled_function_execution SPECIAL_VALUE(Trace_compiled_function_execution)
#define Trace_drawing_for_build SPECIAL_VALUE(Trace_drawing_for_build)
#define Trace_filename_parsing_p SPECIAL_VALUE(Trace_filename_parsing_p)
#define Trace_image_planes_p SPECIAL_VALUE(Trace_image_planes_p)
#define Trace_images SPECIAL_VALUE(Trace_images)
#define Trace_instruction_execution SPECIAL_VALUE(Trace_instruction_execution)
#define Trace_messages_within_extent_of_rule SPECIAL_VALUE(Trace_messages_within_extent_of_rule)
#define Trace_parsing_context_p SPECIAL_VALUE(Trace_parsing_context_p)
#define Trace_parsing_context_tokenizing_p SPECIAL_VALUE(Trace_parsing_context_tokenizing_p)
#define Trace_reshape_events SPECIAL_VALUE(Trace_reshape_events)
#define Trace_skip_data_service_i_am_alive_messages_p SPECIAL_VALUE(Trace_skip_data_service_i_am_alive_messages_p)
#define Trace_system_calls_p SPECIAL_VALUE(Trace_system_calls_p)
#define Trace_validate_p SPECIAL_VALUE(Trace_validate_p)
#define Trace_workstation_events SPECIAL_VALUE(Trace_workstation_events)
#define Tracing_in_events_modules_p SPECIAL_VALUE(Tracing_in_events_modules_p)
#define Tracing_message_level SPECIAL_VALUE(Tracing_message_level)
#define Tracked_items_call_depth SPECIAL_VALUE(Tracked_items_call_depth)
#define Tracked_items_call_vector_table SPECIAL_VALUE(Tracked_items_call_vector_table)
#define Tracking_items_grammar_installed_p SPECIAL_VALUE(Tracking_items_grammar_installed_p)
#define Tracking_items_p SPECIAL_VALUE(Tracking_items_p)
#define Transcode_text_conversion_style_count SPECIAL_VALUE(Transcode_text_conversion_style_count)
#define Transcoder_count SPECIAL_VALUE(Transcoder_count)
#define Transfer_dragging_state_count SPECIAL_VALUE(Transfer_dragging_state_count)
#define Transfer_in_progress SPECIAL_VALUE(Transfer_in_progress)
#define Transform_image_operation_hint SPECIAL_VALUE(Transform_image_operation_hint)
#define Transient_connection_error_qm SPECIAL_VALUE(Transient_connection_error_qm)
#define Transients_to_delete SPECIAL_VALUE(Transients_to_delete)
#define Transmitted_variable_fill_icp_buffers SPECIAL_VALUE(Transmitted_variable_fill_icp_buffers)
#define Traverse_kb_queued_nodes SPECIAL_VALUE(Traverse_kb_queued_nodes)
#define Traverse_kb_queued_nodes_tail SPECIAL_VALUE(Traverse_kb_queued_nodes_tail)
#define Traversing_kb_attribute SPECIAL_VALUE(Traversing_kb_attribute)
#define Traversing_xml_object_p SPECIAL_VALUE(Traversing_xml_object_p)
#define Tree_ordering_cons_counter SPECIAL_VALUE(Tree_ordering_cons_counter)
#define Tree_view_count SPECIAL_VALUE(Tree_view_count)
#define Tree_view_node_count SPECIAL_VALUE(Tree_view_node_count)
#define Trend_chart_layout_bottom SPECIAL_VALUE(Trend_chart_layout_bottom)
#define Trend_chart_layout_grid SPECIAL_VALUE(Trend_chart_layout_grid)
#define Trend_chart_layout_left SPECIAL_VALUE(Trend_chart_layout_left)
#define Trend_chart_layout_parent SPECIAL_VALUE(Trend_chart_layout_parent)
#define Trend_chart_layout_relative_time_pane SPECIAL_VALUE(Trend_chart_layout_relative_time_pane)
#define Trend_chart_layout_right SPECIAL_VALUE(Trend_chart_layout_right)
#define Trend_chart_layout_top SPECIAL_VALUE(Trend_chart_layout_top)
#define Trend_chart_pane_count SPECIAL_VALUE(Trend_chart_pane_count)
#define Trend_chart_spot_count SPECIAL_VALUE(Trend_chart_spot_count)
#define Trif_block_value_alist SPECIAL_VALUE(Trif_block_value_alist)
#define True_value_update_recipient_class_description SPECIAL_VALUE(True_value_update_recipient_class_description)
#define Truth_value_array_class_description SPECIAL_VALUE(Truth_value_array_class_description)
#define Truth_value_list_class_description SPECIAL_VALUE(Truth_value_list_class_description)
#define Tw_deferred_actions SPECIAL_VALUE(Tw_deferred_actions)
#define Tw_evaluate_trace_level SPECIAL_VALUE(Tw_evaluate_trace_level)
#define Tw_expiration_check_interval SPECIAL_VALUE(Tw_expiration_check_interval)
#define Tw_source_debug_p SPECIAL_VALUE(Tw_source_debug_p)
#define Twrite_control_as_ctrl SPECIAL_VALUE(Twrite_control_as_ctrl)
#define Twrite_fixnum_buffer SPECIAL_VALUE(Twrite_fixnum_buffer)
#define Type_at_type_failure SPECIAL_VALUE(Type_at_type_failure)
#define Type_description_count SPECIAL_VALUE(Type_description_count)
#define Type_in_box_class_description SPECIAL_VALUE(Type_in_box_class_description)
#define Type_in_box_spot_count SPECIAL_VALUE(Type_in_box_spot_count)
#define Type_in_text_box_class_description SPECIAL_VALUE(Type_in_text_box_class_description)
#define Type_of_current_window SPECIAL_VALUE(Type_of_current_window)
#define Type_of_current_workstation_context SPECIAL_VALUE(Type_of_current_workstation_context)
#define Type_of_current_workstation_window SPECIAL_VALUE(Type_of_current_workstation_window)
#define Type_of_file_being_read SPECIAL_VALUE(Type_of_file_being_read)
#define Ucs_4_to_utf_8_1st_octet_table SPECIAL_VALUE(Ucs_4_to_utf_8_1st_octet_table)
#define Ui_callback_count SPECIAL_VALUE(Ui_callback_count)
#define Ui_callbacks SPECIAL_VALUE(Ui_callbacks)
#define Ui_client_interface_in_which_to_launch_recompilation_qm SPECIAL_VALUE(Ui_client_interface_in_which_to_launch_recompilation_qm)
#define Ui_client_interface_saved_icp_socket_list SPECIAL_VALUE(Ui_client_interface_saved_icp_socket_list)
#define Ui_client_interface_saved_session_list SPECIAL_VALUE(Ui_client_interface_saved_session_list)
#define Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing SPECIAL_VALUE(Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing)
#define Ui_client_interfaces_for_timeout_of_source_code_control SPECIAL_VALUE(Ui_client_interfaces_for_timeout_of_source_code_control)
#define Ui_command_context SPECIAL_VALUE(Ui_command_context)
#define Unbound_value_for_ok_reader SPECIAL_VALUE(Unbound_value_for_ok_reader)
#define Unevaluated_expression SPECIAL_VALUE(Unevaluated_expression)
#define Unicode_block_count SPECIAL_VALUE(Unicode_block_count)
#define Unicode_byte_swapped_transcoder_count SPECIAL_VALUE(Unicode_byte_swapped_transcoder_count)
#define Unicode_index_to_slavic_font_direct_index_map SPECIAL_VALUE(Unicode_index_to_slavic_font_direct_index_map)
#define Unicode_offset_for_gensym_cyrillic SPECIAL_VALUE(Unicode_offset_for_gensym_cyrillic)
#define Unicode_offset_for_gensym_general_punctuation SPECIAL_VALUE(Unicode_offset_for_gensym_general_punctuation)
#define Unicode_offset_for_gensym_letterlike_symbol SPECIAL_VALUE(Unicode_offset_for_gensym_letterlike_symbol)
#define Unicode_to_gb_2312_map SPECIAL_VALUE(Unicode_to_gb_2312_map)
#define Unicode_to_jis_x_0208_map SPECIAL_VALUE(Unicode_to_jis_x_0208_map)
#define Unicode_to_ks_c_5601_map SPECIAL_VALUE(Unicode_to_ks_c_5601_map)
#define Unicode_transcoder_count SPECIAL_VALUE(Unicode_transcoder_count)
#define Unicode_ucs_2_transcoder_count SPECIAL_VALUE(Unicode_ucs_2_transcoder_count)
#define Uninteresting_block_spot_count SPECIAL_VALUE(Uninteresting_block_spot_count)
#define Unique_temp_filename SPECIAL_VALUE(Unique_temp_filename)
#define Unique_value_roles SPECIAL_VALUE(Unique_value_roles)
#define Units_of_measure_declaration_class_description SPECIAL_VALUE(Units_of_measure_declaration_class_description)
#define Unix_command_callback_function SPECIAL_VALUE(Unix_command_callback_function)
#define Unix_command_line_argument_count SPECIAL_VALUE(Unix_command_line_argument_count)
#define Unix_command_line_arguments SPECIAL_VALUE(Unix_command_line_arguments)
#define Unix_command_line_arguments_as_text_strings SPECIAL_VALUE(Unix_command_line_arguments_as_text_strings)
#define Unix_time_offset_for_encoding SPECIAL_VALUE(Unix_time_offset_for_encoding)
#define Unix_time_offset_was_computed_qm SPECIAL_VALUE(Unix_time_offset_was_computed_qm)
#define Unknown_references SPECIAL_VALUE(Unknown_references)
#define Unread_char_of_ok_file_reader_qm SPECIAL_VALUE(Unread_char_of_ok_file_reader_qm)
#define Unrecoverable_error_p SPECIAL_VALUE(Unrecoverable_error_p)
#define Unused_foreign_image_indices SPECIAL_VALUE(Unused_foreign_image_indices)
#define Unused_known_offsets SPECIAL_VALUE(Unused_known_offsets)
#define Uo_memory_usage_information_hash_table SPECIAL_VALUE(Uo_memory_usage_information_hash_table)
#define Update_before_loading_by_default SPECIAL_VALUE(Update_before_loading_by_default)
#define Update_images_in_xor_overlay_p SPECIAL_VALUE(Update_images_in_xor_overlay_p)
#define Update_menu_values SPECIAL_VALUE(Update_menu_values)
#define Updated_only_qm SPECIAL_VALUE(Updated_only_qm)
#define Updated_users_list SPECIAL_VALUE(Updated_users_list)
#define Uri_reference_count SPECIAL_VALUE(Uri_reference_count)
#define Use_current_time_for_next_uuid SPECIAL_VALUE(Use_current_time_for_next_uuid)
#define Use_directory_lists_for_bootstrapping_qm SPECIAL_VALUE(Use_directory_lists_for_bootstrapping_qm)
#define Use_interpreter_debug_format SPECIAL_VALUE(Use_interpreter_debug_format)
#define Use_jit_p SPECIAL_VALUE(Use_jit_p)
#define Use_minimal_time_slice_for_continue_current_kb_save_p SPECIAL_VALUE(Use_minimal_time_slice_for_continue_current_kb_save_p)
#define Use_new_message_group_for_send_icp_enlarge_index_space_p SPECIAL_VALUE(Use_new_message_group_for_send_icp_enlarge_index_space_p)
#define Use_scaleable_set_widths_qm SPECIAL_VALUE(Use_scaleable_set_widths_qm)
#define Use_telewindows_clogging_mechanism_p SPECIAL_VALUE(Use_telewindows_clogging_mechanism_p)
#define Use_type_info SPECIAL_VALUE(Use_type_info)
#define Used_positional_command_line_argument_default SPECIAL_VALUE(Used_positional_command_line_argument_default)
#define Used_remote_spawn_indices_qm SPECIAL_VALUE(Used_remote_spawn_indices_qm)
#define Useful_machine_authorization_info SPECIAL_VALUE(Useful_machine_authorization_info)
#define User_defined_default_error_handling_procedure_fsn SPECIAL_VALUE(User_defined_default_error_handling_procedure_fsn)
#define User_defined_default_error_handling_procedure_qm SPECIAL_VALUE(User_defined_default_error_handling_procedure_qm)
#define User_defined_logbook_handling_procedure_fsn SPECIAL_VALUE(User_defined_logbook_handling_procedure_fsn)
#define User_defined_logbook_handling_procedure_qm SPECIAL_VALUE(User_defined_logbook_handling_procedure_qm)
#define User_defined_message_board_handling_procedure_fsn SPECIAL_VALUE(User_defined_message_board_handling_procedure_fsn)
#define User_defined_message_board_handling_procedure_qm SPECIAL_VALUE(User_defined_message_board_handling_procedure_qm)
#define User_menu_choice_class_description SPECIAL_VALUE(User_menu_choice_class_description)
#define User_mode_alias_count SPECIAL_VALUE(User_mode_alias_count)
#define User_mouse_tracking_state_count SPECIAL_VALUE(User_mouse_tracking_state_count)
#define User_notified_of_uuid_uniqueness_problem_p SPECIAL_VALUE(User_notified_of_uuid_uniqueness_problem_p)
#define User_overridable_connection_slots SPECIAL_VALUE(User_overridable_connection_slots)
#define User_overridable_g2_array_slots SPECIAL_VALUE(User_overridable_g2_array_slots)
#define User_overridable_g2_list_slots SPECIAL_VALUE(User_overridable_g2_list_slots)
#define User_overridable_message_slots SPECIAL_VALUE(User_overridable_message_slots)
#define User_overridable_object_slots SPECIAL_VALUE(User_overridable_object_slots)
#define User_overridable_parameter_slots SPECIAL_VALUE(User_overridable_parameter_slots)
#define User_overridable_variable_slots SPECIAL_VALUE(User_overridable_variable_slots)
#define User_package_in_this_lisp SPECIAL_VALUE(User_package_in_this_lisp)
#define User_random_seed_qm SPECIAL_VALUE(User_random_seed_qm)
#define Using_pending_write_reference_list SPECIAL_VALUE(Using_pending_write_reference_list)
#define Using_temporary_g2binary_file_symbol_indices_p SPECIAL_VALUE(Using_temporary_g2binary_file_symbol_indices_p)
#define Utf_7_transcoder_count SPECIAL_VALUE(Utf_7_transcoder_count)
#define Utf_8_transcoder_count SPECIAL_VALUE(Utf_8_transcoder_count)
#define Utf_g_ascii_as_much_as_possible_conversion_style SPECIAL_VALUE(Utf_g_ascii_as_much_as_possible_conversion_style)
#define Utf_g_ascii_as_much_as_possible_transcoder_count SPECIAL_VALUE(Utf_g_ascii_as_much_as_possible_transcoder_count)
#define Utf_g_transcoder_count SPECIAL_VALUE(Utf_g_transcoder_count)
#define Uuid_block_count SPECIAL_VALUE(Uuid_block_count)
#define Uuid_block_hash_table SPECIAL_VALUE(Uuid_block_hash_table)
#define Uuid_for_next_frame_qm SPECIAL_VALUE(Uuid_for_next_frame_qm)
#define Uuid_hash_block_table_for_merge_kb SPECIAL_VALUE(Uuid_hash_block_table_for_merge_kb)
#define Uuid_time_b0 SPECIAL_VALUE(Uuid_time_b0)
#define Uuid_time_b1 SPECIAL_VALUE(Uuid_time_b1)
#define Uuid_time_b2 SPECIAL_VALUE(Uuid_time_b2)
#define Uuid_time_b3 SPECIAL_VALUE(Uuid_time_b3)
#define Uuid_xml_checksum SPECIAL_VALUE(Uuid_xml_checksum)
#define Valid_token_actions SPECIAL_VALUE(Valid_token_actions)
#define Value_array_class_description SPECIAL_VALUE(Value_array_class_description)
#define Value_at_type_failure SPECIAL_VALUE(Value_at_type_failure)
#define Value_list_class_description SPECIAL_VALUE(Value_list_class_description)
#define Value_xml_checksum SPECIAL_VALUE(Value_xml_checksum)
#define Var_vector_caching_backpatch_locations SPECIAL_VALUE(Var_vector_caching_backpatch_locations)
#define Var_vector_decaching_backpatch_locations SPECIAL_VALUE(Var_vector_decaching_backpatch_locations)
#define Variable_class_description SPECIAL_VALUE(Variable_class_description)
#define Variable_group_update_structure_count SPECIAL_VALUE(Variable_group_update_structure_count)
#define Variable_is_at_bottom_of_stack_qm SPECIAL_VALUE(Variable_is_at_bottom_of_stack_qm)
#define Variable_or_parameter_class_description SPECIAL_VALUE(Variable_or_parameter_class_description)
#define Variable_simulation_runtime_structure_count SPECIAL_VALUE(Variable_simulation_runtime_structure_count)
#define Variables_that_did_not_have_values SPECIAL_VALUE(Variables_that_did_not_have_values)
#define Vars_settable_at_runtime SPECIAL_VALUE(Vars_settable_at_runtime)
#define Vector_of_oversized_simple_float_array_pools SPECIAL_VALUE(Vector_of_oversized_simple_float_array_pools)
#define Vector_of_oversized_simple_vector_pools SPECIAL_VALUE(Vector_of_oversized_simple_vector_pools)
#define Vector_of_simple_float_array_pools SPECIAL_VALUE(Vector_of_simple_float_array_pools)
#define Vector_of_simple_long_array_pools SPECIAL_VALUE(Vector_of_simple_long_array_pools)
#define Vector_of_simple_vector_pools SPECIAL_VALUE(Vector_of_simple_vector_pools)
#define Vector_pool_cons_counter SPECIAL_VALUE(Vector_pool_cons_counter)
#define Verbosity_level SPECIAL_VALUE(Verbosity_level)
#define Version_control_parameters SPECIAL_VALUE(Version_control_parameters)
#define Vertical_axis_range SPECIAL_VALUE(Vertical_axis_range)
#define Vertical_grid_line_color_qm SPECIAL_VALUE(Vertical_grid_line_color_qm)
#define Vertical_grid_line_spacing SPECIAL_VALUE(Vertical_grid_line_spacing)
#define Vertical_grid_line_width SPECIAL_VALUE(Vertical_grid_line_width)
#define Virtual_attribute_class_instance_header_type_of_slot SPECIAL_VALUE(Virtual_attribute_class_instance_header_type_of_slot)
#define Virtual_attribute_count SPECIAL_VALUE(Virtual_attribute_count)
#define Virtual_attributes_not_local_to_a_class SPECIAL_VALUE(Virtual_attributes_not_local_to_a_class)
#define Vms_directory_filenames_can_dangle_p SPECIAL_VALUE(Vms_directory_filenames_can_dangle_p)
#define Wait_interval_before_killing_foreign_process SPECIAL_VALUE(Wait_interval_before_killing_foreign_process)
#define Walking_menus_state_count SPECIAL_VALUE(Walking_menus_state_count)
#define Warmboot_cons_counter SPECIAL_VALUE(Warmboot_cons_counter)
#define Warmboot_current_time SPECIAL_VALUE(Warmboot_current_time)
#define Warmboot_simulated_time SPECIAL_VALUE(Warmboot_simulated_time)
#define Warmbooting_qm SPECIAL_VALUE(Warmbooting_qm)
#define Warmbooting_with_catch_up_qm SPECIAL_VALUE(Warmbooting_with_catch_up_qm)
#define Warning_message_level SPECIAL_VALUE(Warning_message_level)
#define Weighting_factors_for_thrashing_ratio_ring_buffers SPECIAL_VALUE(Weighting_factors_for_thrashing_ratio_ring_buffers)
#define Whitespace_characters SPECIAL_VALUE(Whitespace_characters)
#define Whitespace_wide_characters SPECIAL_VALUE(Whitespace_wide_characters)
#define Wide_string_text_sequence_count SPECIAL_VALUE(Wide_string_text_sequence_count)
#define Wide_twrite_fixnum_buffer SPECIAL_VALUE(Wide_twrite_fixnum_buffer)
#define Widget_pending_state_count SPECIAL_VALUE(Widget_pending_state_count)
#define Width_for_change_size_qm SPECIAL_VALUE(Width_for_change_size_qm)
#define Window_for_bitmap_for_gsi SPECIAL_VALUE(Window_for_bitmap_for_gsi)
#define Window_instigating_this_rule_instance_qm SPECIAL_VALUE(Window_instigating_this_rule_instance_qm)
#define With_extreme_edges SPECIAL_VALUE(With_extreme_edges)
#define With_icp_buffer_coelescing_scope_qm SPECIAL_VALUE(With_icp_buffer_coelescing_scope_qm)
#define Within_activate_for_kb_workspace SPECIAL_VALUE(Within_activate_for_kb_workspace)
#define Within_backward_chaining_task SPECIAL_VALUE(Within_backward_chaining_task)
#define Within_delete_frame_scope_qm SPECIAL_VALUE(Within_delete_frame_scope_qm)
#define Within_managed_object_scope SPECIAL_VALUE(Within_managed_object_scope)
#define Within_simulate_until_consistent_with_gensym_time SPECIAL_VALUE(Within_simulate_until_consistent_with_gensym_time)
#define Within_simulator_for_stack_error_qm SPECIAL_VALUE(Within_simulator_for_stack_error_qm)
#define Within_writing_procedure_invocation_p SPECIAL_VALUE(Within_writing_procedure_invocation_p)
#define Word_spacing_for_line_of_text_of_graphic_element SPECIAL_VALUE(Word_spacing_for_line_of_text_of_graphic_element)
#define Working_on_annotated_frame SPECIAL_VALUE(Working_on_annotated_frame)
#define Working_on_chart SPECIAL_VALUE(Working_on_chart)
#define Working_on_drawing SPECIAL_VALUE(Working_on_drawing)
#define Working_on_drawing_image_plane SPECIAL_VALUE(Working_on_drawing_image_plane)
#define Working_on_drawing_pane SPECIAL_VALUE(Working_on_drawing_pane)
#define Working_on_drawing_schedule SPECIAL_VALUE(Working_on_drawing_schedule)
#define Working_on_drawing_workspace SPECIAL_VALUE(Working_on_drawing_workspace)
#define Working_on_lexical_computation_of_frame SPECIAL_VALUE(Working_on_lexical_computation_of_frame)
#define Working_on_new_table SPECIAL_VALUE(Working_on_new_table)
#define Working_on_variables_that_need_simulated_values_stack_qm SPECIAL_VALUE(Working_on_variables_that_need_simulated_values_stack_qm)
#define Workspace_background_spot_count SPECIAL_VALUE(Workspace_background_spot_count)
#define Workspace_class_description SPECIAL_VALUE(Workspace_class_description)
#define Workspace_dock_spot_count SPECIAL_VALUE(Workspace_dock_spot_count)
#define Workspace_for_current_draw_document_qm SPECIAL_VALUE(Workspace_for_current_draw_document_qm)
#define Workspace_image_plane_per_window SPECIAL_VALUE(Workspace_image_plane_per_window)
#define Workspace_invalidation_handling_event_type_queue SPECIAL_VALUE(Workspace_invalidation_handling_event_type_queue)
#define Workspace_invalidation_handling_fsn_queue SPECIAL_VALUE(Workspace_invalidation_handling_fsn_queue)
#define Workspace_invalidation_handling_procedure_fsn_qm SPECIAL_VALUE(Workspace_invalidation_handling_procedure_fsn_qm)
#define Workspace_invalidation_handling_procedure_qm SPECIAL_VALUE(Workspace_invalidation_handling_procedure_qm)
#define Workspace_invalidation_handling_window_queue SPECIAL_VALUE(Workspace_invalidation_handling_window_queue)
#define Workspace_invalidation_handling_workspace_queue SPECIAL_VALUE(Workspace_invalidation_handling_workspace_queue)
#define Workspace_menu_choices SPECIAL_VALUE(Workspace_menu_choices)
#define Workspace_name_box_class_description SPECIAL_VALUE(Workspace_name_box_class_description)
#define Workspace_region_count SPECIAL_VALUE(Workspace_region_count)
#define Workspace_view_count SPECIAL_VALUE(Workspace_view_count)
#define Workstation_context_count SPECIAL_VALUE(Workstation_context_count)
#define Workstation_context_frame_count SPECIAL_VALUE(Workstation_context_frame_count)
#define Workstation_context_with_selection_focus_count SPECIAL_VALUE(Workstation_context_with_selection_focus_count)
#define Workstation_count SPECIAL_VALUE(Workstation_count)
#define Workstation_event_count SPECIAL_VALUE(Workstation_event_count)
#define Workstation_in_which_to_launch_recompilation_qm SPECIAL_VALUE(Workstation_in_which_to_launch_recompilation_qm)
#define Workstation_with_image_plane_being_refreshed SPECIAL_VALUE(Workstation_with_image_plane_being_refreshed)
#define Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing SPECIAL_VALUE(Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing)
#define Workstations_with_their_stacks_for_timeout_of_source_code_control SPECIAL_VALUE(Workstations_with_their_stacks_for_timeout_of_source_code_control)
#define Wrap_conservatively SPECIAL_VALUE(Wrap_conservatively)
#define Wrapper_references_for_left_side_of_formula_qm SPECIAL_VALUE(Wrapper_references_for_left_side_of_formula_qm)
#define Write_all_byte_code_bodies_for_kb_p SPECIAL_VALUE(Write_all_byte_code_bodies_for_kb_p)
#define Write_annotations_indent SPECIAL_VALUE(Write_annotations_indent)
#define Write_annotations_part_pattern_stack SPECIAL_VALUE(Write_annotations_part_pattern_stack)
#define Write_annotations_suppress_the_p SPECIAL_VALUE(Write_annotations_suppress_the_p)
#define Write_checksums_in_xml_file_p SPECIAL_VALUE(Write_checksums_in_xml_file_p)
#define Write_compound_slots_parseably_qm SPECIAL_VALUE(Write_compound_slots_parseably_qm)
#define Write_console_p SPECIAL_VALUE(Write_console_p)
#define Write_diffs_after_saving_clear_text_p SPECIAL_VALUE(Write_diffs_after_saving_clear_text_p)
#define Write_floats_accurately_p SPECIAL_VALUE(Write_floats_accurately_p)
#define Write_initial_icp_version_info_p SPECIAL_VALUE(Write_initial_icp_version_info_p)
#define Write_proprietary_package_while_saving_xml_kb SPECIAL_VALUE(Write_proprietary_package_while_saving_xml_kb)
#define Write_remote_value_items_kind SPECIAL_VALUE(Write_remote_value_items_kind)
#define Write_strings_parsably_qm SPECIAL_VALUE(Write_strings_parsably_qm)
#define Write_symbols_in_lower_case_qm SPECIAL_VALUE(Write_symbols_in_lower_case_qm)
#define Write_symbols_parsably_qm SPECIAL_VALUE(Write_symbols_parsably_qm)
#define Write_value_of_gsi_item_p SPECIAL_VALUE(Write_value_of_gsi_item_p)
#define Write_xml_attribute_change_old_value_p SPECIAL_VALUE(Write_xml_attribute_change_old_value_p)
#define Write_xml_object_items_collected SPECIAL_VALUE(Write_xml_object_items_collected)
#define Writing_annotations SPECIAL_VALUE(Writing_annotations)
#define Writing_g2_rdf_file_p SPECIAL_VALUE(Writing_g2_rdf_file_p)
#define Writing_icp_message_group SPECIAL_VALUE(Writing_icp_message_group)
#define Writing_resumable_icp_messages_p SPECIAL_VALUE(Writing_resumable_icp_messages_p)
#define Writing_xml_cdata_p SPECIAL_VALUE(Writing_xml_cdata_p)
#define Writing_xml_p SPECIAL_VALUE(Writing_xml_p)
#define Wrote_first_annotation_flag SPECIAL_VALUE(Wrote_first_annotation_flag)
#define Ws_representation_slots_to_update SPECIAL_VALUE(Ws_representation_slots_to_update)
#define Ws_representation_type_count SPECIAL_VALUE(Ws_representation_type_count)
#define X11_preinitialized_p SPECIAL_VALUE(X11_preinitialized_p)
#define X_data_min_set_qm SPECIAL_VALUE(X_data_min_set_qm)
#define X_debugging_on SPECIAL_VALUE(X_debugging_on)
#define X_in_window_for_finding_object_near_mouse SPECIAL_VALUE(X_in_window_for_finding_object_near_mouse)
#define X_in_window_of_graphic_element SPECIAL_VALUE(X_in_window_of_graphic_element)
#define X_scale_of_graphic_element SPECIAL_VALUE(X_scale_of_graphic_element)
#define X_value_on_graph SPECIAL_VALUE(X_value_on_graph)
#define Xml_checksums_enabled_p SPECIAL_VALUE(Xml_checksums_enabled_p)
#define Xml_namespace_count SPECIAL_VALUE(Xml_namespace_count)
#define Xml_namespace_list_count SPECIAL_VALUE(Xml_namespace_list_count)
#define Xml_nil SPECIAL_VALUE(Xml_nil)
#define Xml_node_count SPECIAL_VALUE(Xml_node_count)
#define Xml_node_list_count SPECIAL_VALUE(Xml_node_list_count)
#define Xml_object_changes SPECIAL_VALUE(Xml_object_changes)
#define Xml_output_buffer SPECIAL_VALUE(Xml_output_buffer)
#define Xml_output_position SPECIAL_VALUE(Xml_output_position)
#define Xml_output_stream SPECIAL_VALUE(Xml_output_stream)
#define Xml_structure_count SPECIAL_VALUE(Xml_structure_count)
#define Xml_structures_extent SPECIAL_VALUE(Xml_structures_extent)
#define Xsd_datatypes_xml_namespace_prefix SPECIAL_VALUE(Xsd_datatypes_xml_namespace_prefix)
#define Y_in_window_for_finding_object_near_mouse SPECIAL_VALUE(Y_in_window_for_finding_object_near_mouse)
#define Y_in_window_of_graphic_element SPECIAL_VALUE(Y_in_window_of_graphic_element)
#define Y_scale_of_graphic_element SPECIAL_VALUE(Y_scale_of_graphic_element)
#define Year_at_compilation_time SPECIAL_VALUE(Year_at_compilation_time)
#define ab_Dummy_var SPECIAL_VALUE(ab_Dummy_var)

#endif /* SI_SUPPORT_THREAD */
