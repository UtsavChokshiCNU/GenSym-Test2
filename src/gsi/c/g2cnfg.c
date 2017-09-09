/* g2cnfg.c
 * Input file:  g2-config.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2cnfg.h"


Object G2int_maximum_key_index = UNBOUND;

Object G2int_key_index_bits = UNBOUND;

Object G2int_unicode_character_bits = UNBOUND;

Object G2int_unicode_mask = UNBOUND;

Object G2int_control_mask = UNBOUND;

Object G2int_meta_mask = UNBOUND;

Object G2int_extend_char_mask = UNBOUND;

Object G2int_compose_char_mask = UNBOUND;

Object G2int_alternate_mask = UNBOUND;

Object G2int_shift_mask = UNBOUND;

Object G2int_caps_lock_mask = UNBOUND;

Object G2int_double_mask = UNBOUND;

Object G2int_key_code_bits = UNBOUND;

Object G2int_key_modifier_bits = UNBOUND;

Object G2int_illegal_key_index = UNBOUND;

Object G2int_sparse_array_max_depth = UNBOUND;

Object G2int_maximum_index_in_backtrace_stack_for_internal_error = UNBOUND;

Object G2int_x11_event_codes_mask = UNBOUND;

Object G2int_x11_key_code_shift = UNBOUND;

Object G2int_gensym_windows_minimum_supported_scale = UNBOUND;

Object G2int_gensym_windows_maximum_supported_scale = UNBOUND;

Object G2int_icp_window_protocol_70_prerelease = UNBOUND;

Object G2int_maximum_interval_between_new_time_for_uuid = UNBOUND;

Object G2int_codejock_reserved_command_ids = UNBOUND;

Object G2int_nms_handle_gap_low = UNBOUND;

Object G2int_nms_handle_gap_high = UNBOUND;

Object G2int_obs_default_style = UNBOUND;

Object G2int_least_common_multiple_of_stock_line_pattern_lengths = UNBOUND;

Object G2int_minimum_minimum_float_scheduling_interval = UNBOUND;

Object G2int_date_month_and_year_of_frame_edit_base_time = UNBOUND;

Object G2int_g2_array_length_maximum = UNBOUND;

Object G2int_history_timestamp_epsilon = UNBOUND;

void g2_config_INIT()
{
    SI_Long temp;
    Object Qg2int_java_constant_unicode, AB_package, Qg2int_java_constant_utf8;
    Object Qg2int_java_constant_nameandtype, Qg2int_java_constant_double;
    Object Qg2int_java_constant_long, Qg2int_java_constant_float;
    Object Qg2int_java_constant_integer, Qg2int_java_constant_string;
    Object Qg2int_java_constant_interfacemethodref;
    Object Qg2int_java_constant_methodref, Qg2int_java_constant_fieldref;
    Object Qg2int_java_constant_class, Qg2int_java_access_flag_abstract;
    Object Qg2int_java_access_flag_interface, Qg2int_java_access_flag_native;
    Object Qg2int_java_access_flag_transient, Qg2int_java_access_flag_volatile;
    Object Qg2int_java_access_flag_synchronized, Qg2int_java_access_flag_super;
    Object Qg2int_java_access_flag_final, Qg2int_java_access_flag_static;
    Object Qg2int_java_access_flag_protected, Qg2int_java_access_flag_private;
    Object Qg2int_java_access_flag_public, Qg2int_econnaborted;
    Object Qg2int_enetreset, Qg2int_errno_again, Qg2int_errno_would_block;
    Object Qg2int_call_site_minimum_size, Qg2int_tcpip_protocol;
    Object Qg2int_number_of_protocols, Qg2int_number_of_gsi_subtests;
    Object Qg2int_mdi_tab_layout, Qg2int_mdi_tab_position;
    Object Qg2int_mdi_show_icons, Qg2int_mdi_grouped_mode;
    Object Qg2int_mdi_tabbed_mode, Qg2int_mdi_normal_mode;
    Object Qg2int_hh_alink_lookup, Qg2int_hh_close_all, Qg2int_hh_help_context;
    Object Qg2int_hh_display_text_popup, Qg2int_hh_keyword_lookup;
    Object Qg2int_hh_sync, Qg2int_hh_display_search, Qg2int_hh_display_index;
    Object Qg2int_hh_display_toc, Qg2int_hh_display_topic;
    Object Qg2int_ld_request_refresh, Qg2int_ld_request_children;
    Object Qg2int_ld_request_full_listing, Qg2int_large_native_icon_size;
    Object Qg2int_small_native_icon_size;
    Object Qg2int_logbook_set_include_date_in_title;
    Object Qg2int_logbook_set_line_wrap, Qg2int_logbook_highlight_message;
    Object Qg2int_logbook_fade_message, Qg2int_logbook_normal_message;
    Object Qg2int_logbook_delete_message, Qg2int_logbook_append_message;
    Object Qg2int_logbook_destroy, Qg2int_status_bar_maximum_pane_count;
    Object Qg2int_nupec_designation_cons_type_tag;
    Object Qg2int_nupec_designation_symbol_type_tag;
    Object Qg2int_nupec_designation_null_type_tag;
    Object Qg2int_nupec_synchronize_datum_text_type;
    Object Qg2int_nupec_synchronize_datum_float_type;
    Object Qg2int_nupec_synchronize_datum_integer_type;
    Object Qg2int_nupec_synchronize_datum_symbol_type;
    Object Qg2int_nupec_synchronize_datum_null_type;
    Object Qg2int_iterations_for_g2ds_temporary_float_processing;
    Object Qg2int_g2ds_write_expression_cell_index;
    Object Qg2int_g2ds_read_expression_cell_index;
    Object Qg2int_g2ds_server_max_count_in_return_queue;
    Object Qg2int_default_g2ds_interface_countdown_timer_limit;
    Object Qg2int_g2ds_no_error, Qg2int_g2ds_logical_type_tag;
    Object Qg2int_g2ds_evaluation_structure_type_tag;
    Object Qg2int_g2ds_evaluation_sequence_type_tag;
    Object Qg2int_g2ds_dotted_list_type_tag, Qg2int_g2ds_64bit_float_type_tag;
    Object Qg2int_g2ds_list_type_tag, Qg2int_g2ds_string_type_tag;
    Object Qg2int_g2ds_symbol_type_tag, Qg2int_g2ds_float_type_tag;
    Object Qg2int_g2ds_integer_type_tag, Qg2int_g2ds_null_type_tag;
    Object Qg2int_iterations_for_gsi_temporary_float_processing;
    Object Qg2int_maximum_gfi_output_queue_count;
    Object Qg2int_ffs_unknown_return_type, Qg2int_ffs_unknown_function;
    Object Qg2int_ffs_signal_caught_during_call;
    Object Qg2int_ffs_connection_open_already, Qg2int_ffs_unspecified_error;
    Object Qg2int_shutdown_context_only_flag_set;
    Object Qg2int_shutdown_context_only_flag_clear;
    Object Qg2int_largest_known_fixnum_time_units_per_second;
    Object Qg2int_foreign_function_text_type_tag;
    Object Qg2int_foreign_function_symbol_type_tag;
    Object Qg2int_foreign_function_real_type_tag;
    Object Qg2int_foreign_function_integer_type_tag;
    Object Qg2int_frame_display_reformat_after_count_deleted;
    Object Qg2int_frame_display_vertical_spacing;
    Object Qg2int_frame_display_workspace_margin;
    Object Qg2int_float_format_precision_limit, Qg2int_max_icon_area;
    Object Qg2int_max_icon_size, Qg2int_attribute_nesting_limit;
    Object Qg2int_maximum_connection_dash_count;
    Object Qg2int_maximum_connection_dash_length, Qg2int_ten_years;
    Object Qg2int_variable_value_particular_code;
    Object Qg2int_virtual_attribute_particular_code;
    Object Qg2int_element_particular_code;
    Object Qg2int_aliased_attribute_particular_code;
    Object Qg2int_attribute_particular_code;
    Object Qg2int_maximum_denotation_sequence_elements;
    Object Qg2int_maximum_denotation_types;
    Object Qg2int_denotation_element_overhead_slot_count;
    Object Qg2int_attribute_value_cache_entry_size;
    Object Qg2int_slot_description_cache_entry_size;
    Object Qg2int_maximum_length_for_dom_strings, Qg2int_xml_notation_node;
    Object Qg2int_xml_document_fragment_node, Qg2int_xml_document_type_node;
    Object Qg2int_xml_document_node, Qg2int_xml_comment_node;
    Object Qg2int_xml_processing_instruction_node, Qg2int_xml_entity_node;
    Object Qg2int_xml_entity_reference_node, Qg2int_xml_cdata_section_node;
    Object Qg2int_xml_text_node, Qg2int_xml_attribute_node;
    Object Qg2int_xml_element_node, Qg2int_xml_encoding_length;
    Object Qg2int_xml_callback_fatal_error, Qg2int_xml_callback_error;
    Object Qg2int_xml_callback_warning, Qg2int_xml_callback_comment;
    Object Qg2int_xml_callback_characters, Qg2int_xml_callback_end_element;
    Object Qg2int_xml_callback_start_element, Qg2int_xml_callback_end_document;
    Object Qg2int_xml_callback_start_document, Qg2int_xml_callback_none;
    Object Qg2int_fraction_modulus_of_compound_fixnum_simulation_time;
    Object Qg2int_buffered_plot_painting_minimum_ratio;
    Object Qg2int_maximum_painting_action_args;
    Object Qg2int_initial_change_log_revision_number;
    Object Qg2int_maximum_number_of_lisp_call_return_values;
    Object Qg2int_maximum_number_of_lisp_call_arguments;
    Object Qg2int_maximum_length_for_writing_evaluation_values;
    Object Qg2int_procedure_invalidates_environment_union_mask;
    Object Qg2int_procedure_call_without_validated_environment_mask;
    Object Qg2int_procedure_contains_indirect_procedure_call_mask;
    Object Qg2int_procedure_contains_wait_state_mask;
    Object Qg2int_procedure_can_invalidate_environment_mask;
    Object Qg2int_default_procedure_evaluation_priority;
    Object Qg2int_no_resumable_object_index, Qg2int_no_history_spec_value;
    Object float_constant_4, Qg2int_history_timestamp_epsilon;
    Object Qg2int_g2_array_length_maximum, Qg2int_default_error_source_column;
    Object Qg2int_default_error_source_line;
    Object Qg2int_default_telewindows_upper_margin;
    Object Qg2int_most_negative_window_coordinate;
    Object Qg2int_most_positive_window_coordinate;
    Object Qg2int_additional_time_for_synthetic_paste_event_timestamps;
    Object Qg2int_frame_edit_base_timestamp, list_constant_1;
    Object Qg2int_date_month_and_year_of_frame_edit_base_time;
    Object Qg2int_hfep_null_code, Qg2int_hfep_error, Qg2int_hfep_wrong;
    Object Qg2int_hfep_done, Qg2int_hfep_go_on, Qg2int_hfep_none;
    Object Qg2int_hfep_ks_size, Qg2int_jis_m_dash_character_code;
    Object Qg2int_jis_letter_a_character_code;
    Object Qg2int_jis_0_digit_character_code, Qg2int_jis_colon_character_code;
    Object Qg2int_jis_space_character_code, Qg2int_tmask_kka_ishouki;
    Object Qg2int_tmask_kka_kofind, Qg2int_tmask_kka_g_taigen;
    Object Qg2int_tmask_chkattr, Qg2int_tmask_chkbunpo;
    Object Qg2int_tmask_kka_find_bunpo, Qg2int_tmask_kka_evalbun;
    Object Qg2int_tmask_kka_gtnum, Qg2int_tmask_kka_ghyoki;
    Object Qg2int_tmask_kka_gtango, Qg2int_tmask_kka_hensaisyo;
    Object Qg2int_tmask_kka_p_batkanakan, float_constant_3;
    Object Qg2int_minimum_minimum_float_scheduling_interval;
    Object Qg2int_minimum_minimum_fixnum_scheduling_interval;
    Object Qg2int_least_common_multiple_of_stock_line_pattern_lengths;
    Object Qg2int_event_time_mask, Qg2int_lvscw_autosize_useheader;
    Object Qg2int_lvscw_autosize, Qg2int_lvcfmt_center, Qg2int_lvcfmt_right;
    Object Qg2int_lvcfmt_left, Qg2int_chart_no_window, Qg2int_chart_success;
    Object Qg2int_chart_format_svg, Qg2int_chart_format_wmf;
    Object Qg2int_chart_format_bmp, Qg2int_chart_format_png;
    Object Qg2int_chart_format_jpeg, Qg2int_chart_export, Qg2int_chart_copy;
    Object Qg2int_chart_partial_update, Qg2int_chart_update;
    Object Qg2int_chart_print, Qg2int_chart_destroy, Qg2int_chart_create;
    Object Qg2int_dlgm_sndmsg, Qg2int_dlgm_check, Qg2int_dlgm_seticon;
    Object Qg2int_dlgm_addstrings, Qg2int_dlgm_settext;
    Object Qg2int_obs_default_style, Qg2int_obs_xt_selhighlight;
    Object Qg2int_obs_xt_animation, Qg2int_obs_xt_dragitems;
    Object Qg2int_obs_xt_addgroups, Qg2int_obs_xt_removeitems;
    Object Qg2int_obs_xt_removegroups, Qg2int_obs_xt_edititems;
    Object Qg2int_obs_xt_editgroups, Qg2int_obs_xt_largeicon;
    Object Qg2int_obs_xt_smallicon, Qg2int_shortcut_bar_foreground_color;
    Object Qg2int_shortcut_bar_background_color;
    Object Qg2int_shortcut_bar_large_icons, Qg2int_shortcut_bar_small_icons;
    Object Qg2int_shortcut_bar_disable_item, Qg2int_shortcut_bar_enable_item;
    Object Qg2int_shortcut_bar_select_item, Qg2int_shortcut_bar_disable_folder;
    Object Qg2int_shortcut_bar_enable_folder;
    Object Qg2int_shortcut_bar_select_folder, Qg2int_shortcut_bar_clear;
    Object Qg2int_shortcut_bar_add_item, Qg2int_shortcut_bar_add_folder;
    Object Qg2int_shortcut_bar_destroy, Qg2int_shortcut_bar_style_outlook_2003;
    Object Qg2int_shortcut_bar_style_outlook, Qg2int_html_view_print;
    Object Qg2int_html_view_goto, Qg2int_html_view_refresh;
    Object Qg2int_html_view_stop, Qg2int_html_view_home;
    Object Qg2int_html_view_forward, Qg2int_html_view_back;
    Object Qg2int_html_view_destroy, Qg2int_tvf_reclaim_label;
    Object Qg2int_tvf_insert_mark, Qg2int_tvf_after, Qg2int_tvf_first;
    Object Qg2int_tvf_check, Qg2int_tvf_expand, Qg2int_tvf_bold;
    Object Qg2int_tvf_children, Qg2int_tree_view_redraw;
    Object Qg2int_tree_view_collapse_all, Qg2int_tree_view_expand_all;
    Object Qg2int_tree_view_set_right_click_selects_node;
    Object Qg2int_tree_view_toggle_item, Qg2int_tree_view_delete_item;
    Object Qg2int_tree_view_set_item_check, Qg2int_tree_view_set_item_icons;
    Object Qg2int_tree_view_set_item_label, Qg2int_tree_view_set_item_bold;
    Object Qg2int_tree_view_set_item_tooltip, Qg2int_tree_view_select_item;
    Object Qg2int_tree_view_collapse_item, Qg2int_tree_view_expand_item;
    Object Qg2int_tree_view_edit_item, Qg2int_tree_view_set_insert_mark;
    Object Qg2int_tree_view_scroll_to, Qg2int_tree_view_ensure_visible;
    Object Qg2int_tree_view_select_item_by_name;
    Object Qg2int_tree_view_set_insert_mark_color;
    Object Qg2int_tree_view_set_text_color, Qg2int_tree_view_set_bgcolor;
    Object Qg2int_tree_view_set_item_height, Qg2int_tree_view_set_indent;
    Object Qg2int_tree_view_clear, Qg2int_tree_view_insert_item;
    Object Qg2int_tree_view_destroy, Qg2int_pane_set_close_action;
    Object Qg2int_pane_set_visible_caption, Qg2int_pane_set_draggable;
    Object Qg2int_pane_set_floatable, Qg2int_pane_set_autohideable;
    Object Qg2int_pane_set_closeable, Qg2int_pane_fill;
    Object Qg2int_pane_toggle_docking, Qg2int_pane_redock, Qg2int_pane_close;
    Object Qg2int_pane_set_icon, Qg2int_pane_set_title, Qg2int_pane_show;
    Object Qg2int_pane_dock, Qg2int_pane_float, Qg2int_pane_select;
    Object Qg2int_pane_hide, Qg2int_pane_destroy, Qg2int_sb_pane_borders;
    Object Qg2int_sb_pane_enabled, Qg2int_sb_pane_tooltip;
    Object Qg2int_sb_pane_alignment, Qg2int_sb_pane_icon;
    Object Qg2int_sb_pane_background, Qg2int_sb_pane_foreground;
    Object Qg2int_sb_pane_visible, Qg2int_sb_pane_width, Qg2int_sb_pane_text;
    Object Qg2int_sb_remove_pane, Qg2int_sb_add_pane, Qg2int_sb_update;
    Object Qg2int_sb_minheight, Qg2int_sb_reset, Qg2int_sb_text;
    Object Qg2int_sb_show, Qg2int_sb_hide, Qg2int_nmsc_deletetext;
    Object Qg2int_nmsc_addtext, Qg2int_nmsc_settext, Qg2int_nmsc_setcursel;
    Object Qg2int_nmsc_hide, Qg2int_nmsc_show, Qg2int_nms_handle_gap_high;
    Object Qg2int_nms_handle_gap_low, list_constant;
    Object Qg2int_codejock_reserved_command_ids, Qg2int_nms_no_choice;
    Object Qg2int_nms_stock_command_min_id;
    Object Qg2int_logbook_message_type_warning;
    Object Qg2int_logbook_message_type_error, Qg2int_hh_display_envar_topic;
    Object Qg2int_handle_for_unsuccessful_query, Qg2int_dock_code_embedded;
    Object Qg2int_dock_code_top_level, Qg2int_dock_code_mdi_child;
    Object Qg2int_dock_code_within, Qg2int_dock_code_float;
    Object Qg2int_dock_code_right, Qg2int_dock_code_left;
    Object Qg2int_dock_code_bottom, Qg2int_dock_code_top;
    Object Qg2int_dialog_is_mdi_child, Qg2int_dialog_is_modeless;
    Object Qg2int_dialog_is_modal, Qg2int_dialog_response_client_side_problem;
    Object Qg2int_dialog_response_cancel_without_callback;
    Object Qg2int_dialog_response_respond_all_and_ok;
    Object Qg2int_dialog_response_respond_all;
    Object Qg2int_dialog_response_respond_and_ok;
    Object Qg2int_dialog_response_just_respond, Qg2int_dialog_response_ok;
    Object Qg2int_dialog_response_cancel;
    Object Qg2int_dialog_response_dont_invoke_callback;
    Object Qg2int_dialog_response_send_all_data;
    Object Qg2int_dialog_response_respond, Qg2int_dialog_response_apply;
    Object Qg2int_dialog_response_close, Qg2int_dialog_response_no_action;
    Object Qg2int_dialog_response_unspecified, Qg2int_g2_send_wsv_address;
    Object Qg2int_g2_dialog_user_gesture, Qg2int_g2_multi_update_finish;
    Object Qg2int_g2_multi_update_continue, Qg2int_g2_multi_update_begin;
    Object Qg2int_tw_multi_update_finish, Qg2int_tw_multi_update_continue;
    Object Qg2int_tw_multi_update_begin, Qg2int_focus_changed_update;
    Object Qg2int_multi_update_finish, Qg2int_multi_update_continue;
    Object Qg2int_multi_update_begin, Qg2int_g2_initiated_update;
    Object Qg2int_tw_initiated_update, Qg2int_debugger_source_stepping_flag;
    Object Qg2int_debugger_dialog_cancel, Qg2int_cd_refresh;
    Object Qg2int_cd_add_children;
    Object Qg2int_maximum_number_of_characters_in_pathname;
    Object Qg2int_dlg_icon_error, Qg2int_dlg_icon_warning;
    Object Qg2int_dlg_icon_information, Qg2int_dlg_icon_question;
    Object Qg2int_mb_help, Qg2int_mb_retrycancel, Qg2int_mb_yesno;
    Object Qg2int_mb_yesnocancel, Qg2int_mb_abortretryignore;
    Object Qg2int_mb_okcancel, Qg2int_mb_ok;
    Object Qg2int_max_subblock_count_with_pop_up_virtual_attributes_table;
    Object Qg2int_default_maximum_renderings_for_class;
    Object Qg2int_default_number_of_renderings_for_bulk_delete;
    Object Qg2int_message_field_mask, Qg2int_source_stepping_shift;
    Object Qg2int_breakpoint_shift, Qg2int_tracing_shift, Qg2int_warning_shift;
    Object Qg2int_assumed_standard_image_plane_border_width;
    Object Qg2int_maximum_image_plane_serial_number;
    Object Qg2int_minimum_image_plane_serial_number;
    Object Qg2int_maximum_length_of_menu_of_names;
    Object Qg2int_use_full_size_of_with_output_wide_string_cutoff;
    Object Qg2int_old_mask_for_saved_frame_flags;
    Object Qg2int_maximum_number_of_generic_methods;
    Object Qg2int_max_number_of_lexing_tables_to_cache;
    Object Qg2int_max_number_of_regexps_to_cache, Qg2int_default_reduction;
    Object Qg2int_max_instance_rule_chaining;
    Object Qg2int_maximum_size_of_category_set_as_list;
    Object Qg2int_maximum_background_tile_area, Qg2int_free_bits_per_icp_byte;
    Object Qg2int_number_of_bits_of_gray_in_the_extended_gray_palette;
    Object Qg2int_black_threshold_in_color_intensity;
    Object Qg2int_editor_options_query_on_close;
    Object Qg2int_editor_options_single_line_editor;
    Object Qg2int_editor_options_single_line_comments;
    Object Qg2int_editor_style_completion, Qg2int_editor_style_category;
    Object Qg2int_editor_style_normal, Qg2int_editor_grammar_procedureslrule;
    Object Qg2int_editor_grammar_free_text;
    Object Qg2int_editor_maximum_number_of_undos_to_remember;
    Object Qg2int_editor_undo, Qg2int_editor_custom_toolbar;
    Object Qg2int_editor_beep, Qg2int_editor_goto_item;
    Object Qg2int_editor_text_saved, Qg2int_editor_delete_text;
    Object Qg2int_editor_replace_text, Qg2int_editor_hotspot_clicked;
    Object Qg2int_editor_append_output, Qg2int_editor_clear_output;
    Object Qg2int_editor_completions_new, Qg2int_editor_apply_new;
    Object Qg2int_editor_exit_new, Qg2int_editor_incremental_updates;
    Object Qg2int_editor_text_deleted, Qg2int_editor_text_inserted;
    Object Qg2int_editor_cursor_moved, Qg2int_editor_set_tabs;
    Object Qg2int_editor_set_options, Qg2int_editor_set_grammar;
    Object Qg2int_editor_enable, Qg2int_editor_disable, Qg2int_editor_apply;
    Object Qg2int_editor_notes, Qg2int_editor_exit, Qg2int_editor_arglist;
    Object Qg2int_editor_completions, Qg2int_editor_syntax;
    Object Qg2int_editor_insert_text, Qg2int_editor_set_text;
    Object Qg2int_editor_reset, Qg2int_editor_syntax_repair;
    Object Qg2int_editor_clear_breakpoints, Qg2int_editor_set_breakpoint;
    Object Qg2int_editor_disable_breakpoint, Qg2int_editor_clear_breakpoint;
    Object Qg2int_editor_cancel, Qg2int_editor_add_toolbar_button;
    Object Qg2int_editor_modal, Qg2int_editor_show, Qg2int_editor_print;
    Object Qg2int_editor_destroy, Qg2int_editor_create, Qg2int_dt_end_ellipsis;
    Object Qg2int_dt_path_ellipsis, Qg2int_dt_editcontrol;
    Object Qg2int_dt_expandtabs, Qg2int_dt_singleline, Qg2int_dt_wordbreak;
    Object Qg2int_dt_bottom, Qg2int_dt_vcenter, Qg2int_dt_right;
    Object Qg2int_dt_center, Qg2int_dt_left, Qg2int_swp_hwnd_notopmost;
    Object Qg2int_swp_hwnd_topmost, Qg2int_swp_hwnd_bottom;
    Object Qg2int_swp_hwnd_top, Qg2int_sorting_order_default;
    Object Qg2int_sort_column_default, Qg2int_cw_usedefault;
    Object Qg2int_status_hidden, Qg2int_status_docked_bottom;
    Object Qg2int_status_docked_right, Qg2int_status_docked_top;
    Object Qg2int_status_docked_left, Qg2int_status_attached;
    Object Qg2int_status_closed, Qg2int_status_collapsed;
    Object Qg2int_status_expanded, Qg2int_status_unknown;
    Object Qg2int_status_autohidden, Qg2int_status_docked;
    Object Qg2int_status_floated, Qg2int_size_maxhide, Qg2int_size_maxshow;
    Object Qg2int_size_maximized, Qg2int_size_minimized, Qg2int_size_restored;
    Object Qg2int_ws_ex_appwindow, Qg2int_ws_ex_staticedge;
    Object Qg2int_ws_ex_controlparent, Qg2int_ws_ex_rightscrollbar;
    Object Qg2int_ws_ex_leftscrollbar, Qg2int_ws_ex_ltrreading;
    Object Qg2int_ws_ex_rtlreading, Qg2int_ws_ex_left, Qg2int_ws_ex_right;
    Object Qg2int_ws_ex_contexthelp, Qg2int_ws_ex_clientedge;
    Object Qg2int_ws_ex_windowedge, Qg2int_ws_ex_toolwindow;
    Object Qg2int_ws_ex_mdichild, Qg2int_ws_ex_transparent;
    Object Qg2int_ws_ex_acceptfiles, Qg2int_ws_ex_topmost;
    Object Qg2int_ws_ex_noparentnotify, Qg2int_ws_ex_dlgmodalframe;
    Object Qg2int_ws_maximizebox, Qg2int_ws_minimizebox, Qg2int_ws_tabstop;
    Object Qg2int_ws_group, Qg2int_ws_thickframe, Qg2int_ws_sysmenu;
    Object Qg2int_ws_hscroll, Qg2int_ws_vscroll, Qg2int_ws_dlgframe;
    Object Qg2int_ws_border, Qg2int_ws_caption, Qg2int_ws_maximize;
    Object Qg2int_ws_clipchildren, Qg2int_ws_clipsiblings, Qg2int_ws_disabled;
    Object Qg2int_ws_visible, Qg2int_ws_minimize, Qg2int_ws_child;
    Object Qg2int_ws_popup, Qg2int_ws_overlapped, Qg2int_sw_showdefault;
    Object Qg2int_sw_restore, Qg2int_sw_showna, Qg2int_sw_showminnoactive;
    Object Qg2int_sw_minimize, Qg2int_sw_show, Qg2int_sw_shownoactivate;
    Object Qg2int_sw_maximize, Qg2int_sw_showminimized, Qg2int_sw_shownormal;
    Object Qg2int_sw_hide, Qg2int_nip_size_window;
    Object Qg2int_nip_set_background_color, Qg2int_nip_rescale_window;
    Object Qg2int_nip_set_closeable, Qg2int_nip_set_icon;
    Object Qg2int_nip_zorder_window, Qg2int_nip_restyle_window;
    Object Qg2int_nip_set_max_size, Qg2int_nip_cerase_window;
    Object Qg2int_nip_scroll_window, Qg2int_nip_inflate_window;
    Object Qg2int_nip_caption_window, Qg2int_nip_destroy_window;
    Object Qg2int_nip_lower_window, Qg2int_nip_raise_window;
    Object Qg2int_nip_reshape_window, Qg2int_nip_move_window;
    Object Qg2int_nip_show_window, Qg2int_nip_wintype_mask;
    Object Qg2int_nip_wintype_classic, Qg2int_frame_type_mdi;
    Object Qg2int_frame_type_sdi, Qg2int_frame_type_child;
    Object Qg2int_frame_type_classic, Qg2int_frame_type_none;
    Object Qg2int_reclaim_offscreen_pixmap, Qg2int_bitblt_offscreen_pixmap;
    Object Qg2int_disable_offscreen_drawing, Qg2int_enable_offscreen_drawing;
    Object Qg2int_ps_join_miter, Qg2int_ps_join_bevel, Qg2int_ps_join_round;
    Object Qg2int_ps_endcap_flat, Qg2int_ps_endcap_square;
    Object Qg2int_ps_endcap_round, Qg2int_ps_userstyle, Qg2int_ps_dashdotdot;
    Object Qg2int_ps_dashdot, Qg2int_ps_dot, Qg2int_ps_dash, Qg2int_ps_solid;
    Object Qg2int_no_stipple_value, Qg2int_transparent_color_value;
    Object Qg2int_minimum_intensity_for_white, Qg2int_gsi_product_tag;
    Object Qg2int_g2_product_tag, Qg2int_use_no_network_protocols;
    Object Qg2int_use_tcpip_protocol_only, Qg2int_use_all_network_protocols;
    Object Qg2int_minimum_message_series_size_before_beginning_new_series;
    Object Qg2int_minimum_message_series_size_before_suspending;
    Object Qg2int_ne_error_value, Qg2int_ne_eof_value, Qg2int_ne_blocked_value;
    Object Qg2int_uuid_offset_mask, float_constant_2;
    Object Qg2int_maximum_interval_between_new_time_for_uuid;
    Object Qg2int_number_of_system_metrics, Qg2int_sm_cydialog;
    Object Qg2int_sm_cxdialog, Qg2int_sm_samedisplayformat;
    Object Qg2int_sm_cmonitors, Qg2int_sm_cyvirtualscreen;
    Object Qg2int_sm_cxvirtualscreen, Qg2int_sm_yvirtualscreen;
    Object Qg2int_sm_xvirtualscreen, Qg2int_sm_mousewheelpresent;
    Object Qg2int_sm_mideastenabled, Qg2int_sm_slowmachine;
    Object Qg2int_sm_cymenucheck, Qg2int_sm_cxmenucheck, Qg2int_sm_showsounds;
    Object Qg2int_sm_cydrag, Qg2int_sm_cxdrag, Qg2int_sm_cleanboot;
    Object Qg2int_sm_network, Qg2int_sm_cymaximized, Qg2int_sm_cxmaximized;
    Object Qg2int_sm_cymaxtrack, Qg2int_sm_cxmaxtrack, Qg2int_sm_cyminimized;
    Object Qg2int_sm_cxminimized, Qg2int_sm_arrange, Qg2int_sm_cymenusize;
    Object Qg2int_sm_cxmenusize, Qg2int_sm_cysmsize, Qg2int_sm_cxsmsize;
    Object Qg2int_sm_cysmcaption, Qg2int_sm_cysmicon, Qg2int_sm_cxsmicon;
    Object Qg2int_sm_cyminspacing, Qg2int_sm_cxminspacing, Qg2int_sm_cyedge;
    Object Qg2int_sm_cxedge, Qg2int_sm_secure, Qg2int_sm_cmousebuttons;
    Object Qg2int_sm_dbcsenabled, Qg2int_sm_penwindows;
    Object Qg2int_sm_menudropalignment, Qg2int_sm_cyiconspacing;
    Object Qg2int_sm_cxiconspacing, Qg2int_sm_cydoubleclk;
    Object Qg2int_sm_cxdoubleclk, Qg2int_sm_cymintrack, Qg2int_sm_cxmintrack;
    Object Qg2int_sm_cyframe, Qg2int_sm_cxframe, Qg2int_sm_cysize;
    Object Qg2int_sm_cxsize, Qg2int_sm_cymin, Qg2int_sm_cxmin;
    Object Qg2int_sm_swapbutton, Qg2int_sm_debug, Qg2int_sm_cxhscroll;
    Object Qg2int_sm_cyvscroll, Qg2int_sm_mousepresent;
    Object Qg2int_sm_cykanjiwindow, Qg2int_sm_cyfullscreen;
    Object Qg2int_sm_cxfullscreen, Qg2int_sm_cymenu, Qg2int_sm_cycursor;
    Object Qg2int_sm_cxcursor, Qg2int_sm_cyicon, Qg2int_sm_cxicon;
    Object Qg2int_sm_cxhthumb, Qg2int_sm_cyvthumb, Qg2int_sm_cydlgframe;
    Object Qg2int_sm_cxdlgframe, Qg2int_sm_cyborder, Qg2int_sm_cxborder;
    Object Qg2int_sm_cycaption, Qg2int_sm_cyhscroll, Qg2int_sm_cxvscroll;
    Object Qg2int_sm_cyscreen, Qg2int_sm_cxscreen;
    Object Qg2int_icp_window_protocol_supports_basic_dialogs;
    Object Qg2int_icp_window_protocol_supports_native_progress_bar;
    Object Qg2int_icp_window_protocol_supports_move_telewindow;
    Object Qg2int_icp_window_protocol_supports_native_icons;
    Object Qg2int_icp_window_protocol_supports_nms_posting_callbacks;
    Object Qg2int_icp_window_protocol_supports_native_printing;
    Object Qg2int_icp_window_protocol_70_prerelease;
    Object Qg2int_icp_window_protocol_70r0;
    Object Qg2int_icp_window_protocol_supports_nms_menus;
    Object Qg2int_icp_window_protocol_supports_image_tiling;
    Object Qg2int_icp_window_protocol_supports_native_widgets;
    Object Qg2int_icp_window_protocol_supports_event_plists;
    Object Qg2int_icp_window_protocol_supports_offscreen_drawing;
    Object Qg2int_icp_window_protocol_supports_wide_polyline;
    Object Qg2int_icp_window_protocol_supports_24bit_image_painting;
    Object Qg2int_icp_window_protocol_supports_raster_stipples;
    Object Qg2int_icp_window_protocol_supports_unicode_character_events;
    Object Qg2int_icp_window_protocol_supports_request_for_paste_availability;
    Object Qg2int_icp_window_protocol_supports_native_cut_and_paste;
    Object Qg2int_icp_window_protocol_supports_polychrome_icon_images;
    Object Qg2int_icp_window_protocol_supports_un_decomposed_polygons;
    Object Qg2int_icp_window_protocol_supports_saving_user_settings;
    Object Qg2int_icp_window_protocol_supports_md5_password_encryption;
    Object Qg2int_icp_window_protocol_supports_text_strings_as_wide_strings;
    Object Qg2int_icp_window_protocol_supports_oriented_text_in_scratchpad_rasters;
    Object Qg2int_icp_window_protocol_supports_remote_executables;
    Object Qg2int_icp_window_protocol_supports_remote_processes;
    Object Qg2int_icp_window_protocol_supports_slavic_font;
    Object Qg2int_icp_window_protocol_supports_telewindows_connection_license_info;
    Object Qg2int_icp_window_protocol_supports_ping_drawing;
    Object Qg2int_icp_window_protocol_supports_force_graphics;
    Object Qg2int_icp_window_protocol_supports_floating_telewindows;
    Object Qg2int_icp_window_protocol_supports_v4_mouse_messages;
    Object Qg2int_icp_window_protocol_supports_scrolling;
    Object Qg2int_icp_window_protocol_supports_setting_protocol_level;
    Object Qg2int_icp_window_protocol_supports_transparent_copy;
    Object Qg2int_icp_window_protocol_supports_monochrome_raster_lists;
    Object Qg2int_original_icp_window_protocol_version;
    Object Qg2int_maximum_polygon_points, float_constant_1;
    Object Qg2int_gensym_windows_maximum_supported_scale, float_constant;
    Object Qg2int_gensym_windows_minimum_supported_scale;
    Object Qg2int_gensym_windows_standard_dpi;
    Object Qg2int_gensym_windows_maximum_supported_dpi;
    Object Qg2int_gensym_windows_minimum_supported_dpi;
    Object Qg2int_clipboard_read_results_failure_code;
    Object Qg2int_unicode_text_clipboard_read_results_entry;
    Object Qg2int_x_compound_text_clipboard_read_results_entry;
    Object Qg2int_latin_1_clipboard_read_results_entry;
    Object Qg2int_clipboard_reading_results_vector_length;
    Object Qg2int_allocated_clipboard_text_length;
    Object Qg2int_specified_max_clipboard_text_length, Qg2int_x11_control;
    Object Qg2int_x11_focus_out, Qg2int_x11_focus_in, Qg2int_x11_leave;
    Object Qg2int_x11_enter, Qg2int_x11_reshape, Qg2int_x11_exposure;
    Object Qg2int_x11_pointer_motion, Qg2int_x11_button_release;
    Object Qg2int_x11_button_press, Qg2int_x11_keypress, Qg2int_x11_nullevent;
    Object Qg2int_x11_no_more_events, Qg2int_x11_key_code_shift;
    Object Qg2int_x11_event_codes_mask;
    Object Qg2int_x11_number_of_bits_in_event_codes;
    Object Qg2int_x11_transparent_copy, Qg2int_x11_stippled, Qg2int_x11_and;
    Object Qg2int_x11_xor, Qg2int_x11_copy, Qg2int_x11_or;
    Object Qg2int_gensym_error_buffer_initial_size;
    Object Qg2int_size_of_basic_backtrace_information;
    Object Qg2int_maximum_index_in_backtrace_stack_for_internal_error;
    Object Qg2int_size_of_backtrace_stack_for_internal_error;
    Object Qg2int_post_mortem_ring_buffer_default_length;
    Object Qg2int_no_tokenizer_match_end_index;
    Object Qg2int_no_tokenizer_match_start_index;
    Object Qg2int_state_transition_user_defined_transition_test_sentinel;
    Object Qg2int_maximum_state_transition_args, Qg2int_last_8859_part_number;
    Object Qg2int_first_8859_part_number, Qg2int_8859_code_mask;
    Object Qg2int_8859_part_size, Qg2int_intern_string_buffer_length;
    Object Qg2int_sparse_array_max_depth, Qg2int_sparse_array_layer_order;
    Object Qg2int_maximum_length_for_user_symbols;
    Object Qg2int_maximum_length_for_user_text_strings;
    Object Qg2int_maximum_length_for_user_gensym_strings;
    Object Qg2int_extra_wide_string_bv16_elements;
    Object Qg2int_managed_array_index_offset;
    Object Qg2int_maximum_managed_array_buffer_size;
    Object Qg2int_maximum_oversized_managed_simple_vector_size;
    Object Qg2int_illegal_key_index, Qg2int_illegal_key_code;
    Object Qg2int_key_modifier_bits, Qg2int_key_code_bits, Qg2int_double_mask;
    Object Qg2int_caps_lock_mask, Qg2int_shift_mask, Qg2int_alternate_mask;
    Object Qg2int_compose_char_mask, Qg2int_extend_char_mask, Qg2int_meta_mask;
    Object Qg2int_control_mask, Qg2int_unicode_mask, Qg2int_double_bit;
    Object Qg2int_caps_lock_bit, Qg2int_shift_bit, Qg2int_alternate_bit;
    Object Qg2int_compose_char_bit, Qg2int_extend_char_bit, Qg2int_meta_bit;
    Object Qg2int_control_bit, Qg2int_unicode_bit, Qg2int_menu_bit;
    Object Qg2int_unicode_character_bits;
    Object Qg2int_number_of_unicode_character_bits, Qg2int_key_index_bits;
    Object Qg2int_maximum_key_index, Qg2int_maximum_number_of_key_indexes;
    Object Qg2int_number_of_key_index_bits;
    Object Qg2int_c_environment_var_strlen_failure;
    Object Qg2int_c_argv_n_strlen_failure;

    x_note_fn_call(4,0);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_c_argv_n_strlen_failure = 
	    STATIC_SYMBOL("C-ARGV-N-STRLEN-FAILURE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_c_argv_n_strlen_failure,FIX((SI_Long)-1L));
    Qg2int_c_environment_var_strlen_failure = 
	    STATIC_SYMBOL("C-ENVIRONMENT-VAR-STRLEN-FAILURE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_c_environment_var_strlen_failure,
	    FIX((SI_Long)-1L));
    Qg2int_number_of_key_index_bits = 
	    STATIC_SYMBOL("NUMBER-OF-KEY-INDEX-BITS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_number_of_key_index_bits,FIX((SI_Long)11L));
    Qg2int_maximum_number_of_key_indexes = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-KEY-INDEXES",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_number_of_key_indexes,FIX((SI_Long)2048L));
    Qg2int_maximum_key_index = STATIC_SYMBOL("MAXIMUM-KEY-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_maximum_key_index,
	    G2int_maximum_key_index);
    SET_SYMBOL_VALUE(Qg2int_maximum_key_index,
	    FIXNUM_SUB1(FIX((SI_Long)2048L)));
    Qg2int_key_index_bits = STATIC_SYMBOL("KEY-INDEX-BITS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_key_index_bits,G2int_key_index_bits);
    SET_SYMBOL_VALUE(Qg2int_key_index_bits,FIXNUM_SUB1(FIX((SI_Long)2048L)));
    Qg2int_number_of_unicode_character_bits = 
	    STATIC_SYMBOL("NUMBER-OF-UNICODE-CHARACTER-BITS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_number_of_unicode_character_bits,
	    FIX((SI_Long)16L));
    Qg2int_unicode_character_bits = STATIC_SYMBOL("UNICODE-CHARACTER-BITS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_unicode_character_bits,
	    G2int_unicode_character_bits);
    SET_SYMBOL_VALUE(Qg2int_unicode_character_bits,
	    FIXNUM_SUB1(FIX((SI_Long)65536L)));
    Qg2int_menu_bit = STATIC_SYMBOL("MENU-BIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_menu_bit,FIX((SI_Long)33554432L));
    Qg2int_unicode_bit = STATIC_SYMBOL("UNICODE-BIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_bit,FIX((SI_Long)16777216L));
    Qg2int_control_bit = STATIC_SYMBOL("CONTROL-BIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_control_bit,FIX((SI_Long)8388608L));
    Qg2int_meta_bit = STATIC_SYMBOL("META-BIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_meta_bit,FIX((SI_Long)4194304L));
    Qg2int_extend_char_bit = STATIC_SYMBOL("EXTEND-CHAR-BIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_extend_char_bit,FIX((SI_Long)2097152L));
    Qg2int_compose_char_bit = STATIC_SYMBOL("COMPOSE-CHAR-BIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_compose_char_bit,FIX((SI_Long)1048576L));
    Qg2int_alternate_bit = STATIC_SYMBOL("ALTERNATE-BIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_alternate_bit,FIX((SI_Long)524288L));
    Qg2int_shift_bit = STATIC_SYMBOL("SHIFT-BIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shift_bit,FIX((SI_Long)262144L));
    Qg2int_caps_lock_bit = STATIC_SYMBOL("CAPS-LOCK-BIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_caps_lock_bit,FIX((SI_Long)131072L));
    Qg2int_double_bit = STATIC_SYMBOL("DOUBLE-BIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_double_bit,FIX((SI_Long)65536L));
    Qg2int_unicode_mask = STATIC_SYMBOL("UNICODE-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_unicode_mask,G2int_unicode_mask);
    SET_SYMBOL_VALUE(Qg2int_unicode_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),G2int_unicode_bit));
    Qg2int_control_mask = STATIC_SYMBOL("CONTROL-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_control_mask,G2int_control_mask);
    SET_SYMBOL_VALUE(Qg2int_control_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),G2int_control_bit));
    Qg2int_meta_mask = STATIC_SYMBOL("META-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_meta_mask,G2int_meta_mask);
    SET_SYMBOL_VALUE(Qg2int_meta_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),G2int_meta_bit));
    Qg2int_extend_char_mask = STATIC_SYMBOL("EXTEND-CHAR-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_extend_char_mask,G2int_extend_char_mask);
    SET_SYMBOL_VALUE(Qg2int_extend_char_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),
	    G2int_extend_char_bit));
    Qg2int_compose_char_mask = STATIC_SYMBOL("COMPOSE-CHAR-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_compose_char_mask,
	    G2int_compose_char_mask);
    SET_SYMBOL_VALUE(Qg2int_compose_char_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),
	    G2int_compose_char_bit));
    Qg2int_alternate_mask = STATIC_SYMBOL("ALTERNATE-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_alternate_mask,G2int_alternate_mask);
    SET_SYMBOL_VALUE(Qg2int_alternate_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),
	    G2int_alternate_bit));
    Qg2int_shift_mask = STATIC_SYMBOL("SHIFT-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_shift_mask,G2int_shift_mask);
    SET_SYMBOL_VALUE(Qg2int_shift_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),G2int_shift_bit));
    Qg2int_caps_lock_mask = STATIC_SYMBOL("CAPS-LOCK-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_caps_lock_mask,G2int_caps_lock_mask);
    SET_SYMBOL_VALUE(Qg2int_caps_lock_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),
	    G2int_caps_lock_bit));
    Qg2int_double_mask = STATIC_SYMBOL("DOUBLE-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_double_mask,G2int_double_mask);
    SET_SYMBOL_VALUE(Qg2int_double_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),G2int_double_bit));
    Qg2int_key_code_bits = STATIC_SYMBOL("KEY-CODE-BITS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_key_code_bits,G2int_key_code_bits);
    temp = IFIX(FIXNUM_SUB1(FIX((SI_Long)33554432L)));
    SET_SYMBOL_VALUE(Qg2int_key_code_bits,FIX(temp));
    Qg2int_key_modifier_bits = STATIC_SYMBOL("KEY-MODIFIER-BITS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_key_modifier_bits,
	    G2int_key_modifier_bits);
    SET_SYMBOL_VALUE(Qg2int_key_modifier_bits,logiorn(9,G2int_unicode_bit,
	    G2int_control_bit,G2int_meta_bit,G2int_extend_char_bit,
	    G2int_compose_char_bit,G2int_alternate_bit,G2int_shift_bit,
	    G2int_caps_lock_bit,G2int_double_bit));
    Qg2int_illegal_key_code = STATIC_SYMBOL("ILLEGAL-KEY-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_illegal_key_code,FIX((SI_Long)-1L));
    Qg2int_illegal_key_index = STATIC_SYMBOL("ILLEGAL-KEY-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_illegal_key_index,
	    G2int_illegal_key_index);
    SET_SYMBOL_VALUE(Qg2int_illegal_key_index,
	    logand(G2int_illegal_key_code,G2int_key_index_bits));
    Qg2int_maximum_oversized_managed_simple_vector_size = 
	    STATIC_SYMBOL("MAXIMUM-OVERSIZED-MANAGED-SIMPLE-VECTOR-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_oversized_managed_simple_vector_size,
	    FIX((SI_Long)1048576L));
    Qg2int_maximum_managed_array_buffer_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-ARRAY-BUFFER-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_managed_array_buffer_size,
	    FIX((SI_Long)1024L));
    Qg2int_managed_array_index_offset = 
	    STATIC_SYMBOL("MANAGED-ARRAY-INDEX-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_managed_array_index_offset,FIX((SI_Long)2L));
    Qg2int_extra_wide_string_bv16_elements = 
	    STATIC_SYMBOL("EXTRA-WIDE-STRING-BV16-ELEMENTS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_extra_wide_string_bv16_elements,FIX((SI_Long)3L));
    Qg2int_maximum_length_for_user_gensym_strings = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-FOR-USER-GENSYM-STRINGS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_length_for_user_gensym_strings,
	    FIX((SI_Long)400000000L));
    Qg2int_maximum_length_for_user_text_strings = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-FOR-USER-TEXT-STRINGS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_length_for_user_text_strings,
	    FIX((SI_Long)100000000L));
    Qg2int_maximum_length_for_user_symbols = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-FOR-USER-SYMBOLS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_length_for_user_symbols,
	    FIX((SI_Long)65533L));
    Qg2int_sparse_array_layer_order = 
	    STATIC_SYMBOL("SPARSE-ARRAY-LAYER-ORDER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sparse_array_layer_order,FIX((SI_Long)5L));
    Qg2int_sparse_array_max_depth = STATIC_SYMBOL("SPARSE-ARRAY-MAX-DEPTH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_sparse_array_max_depth,
	    G2int_sparse_array_max_depth);
    SET_SYMBOL_VALUE(Qg2int_sparse_array_max_depth,
	    lfloor(llog(Most_positive_fixnum,FIX((SI_Long)2L)),
	    G2int_sparse_array_layer_order));
    Qg2int_intern_string_buffer_length = 
	    STATIC_SYMBOL("INTERN-STRING-BUFFER-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_intern_string_buffer_length,FIX((SI_Long)32L));
    Qg2int_8859_part_size = STATIC_SYMBOL("8859-PART-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_8859_part_size,FIX((SI_Long)128L));
    Qg2int_8859_code_mask = STATIC_SYMBOL("8859-CODE-MASK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_8859_code_mask,FIX((SI_Long)127L));
    Qg2int_first_8859_part_number = STATIC_SYMBOL("FIRST-8859-PART-NUMBER",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_first_8859_part_number,FIX((SI_Long)1L));
    Qg2int_last_8859_part_number = STATIC_SYMBOL("LAST-8859-PART-NUMBER",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_last_8859_part_number,FIX((SI_Long)10L));
    Qg2int_maximum_state_transition_args = 
	    STATIC_SYMBOL("MAXIMUM-STATE-TRANSITION-ARGS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_state_transition_args,FIX((SI_Long)4L));
    Qg2int_state_transition_user_defined_transition_test_sentinel = 
	    STATIC_SYMBOL("STATE-TRANSITION-USER-DEFINED-TRANSITION-TEST-SENTINEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_state_transition_user_defined_transition_test_sentinel,
	    FIX((SI_Long)-1L));
    Qg2int_no_tokenizer_match_start_index = 
	    STATIC_SYMBOL("NO-TOKENIZER-MATCH-START-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_no_tokenizer_match_start_index,FIX((SI_Long)-1L));
    Qg2int_no_tokenizer_match_end_index = 
	    STATIC_SYMBOL("NO-TOKENIZER-MATCH-END-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_no_tokenizer_match_end_index,FIX((SI_Long)0L));
    Qg2int_post_mortem_ring_buffer_default_length = 
	    STATIC_SYMBOL("POST-MORTEM-RING-BUFFER-DEFAULT-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_post_mortem_ring_buffer_default_length,
	    FIX((SI_Long)50L));
    Qg2int_size_of_backtrace_stack_for_internal_error = 
	    STATIC_SYMBOL("SIZE-OF-BACKTRACE-STACK-FOR-INTERNAL-ERROR",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_size_of_backtrace_stack_for_internal_error,
	    FIX((SI_Long)1000L));
    Qg2int_maximum_index_in_backtrace_stack_for_internal_error = 
	    STATIC_SYMBOL("MAXIMUM-INDEX-IN-BACKTRACE-STACK-FOR-INTERNAL-ERROR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_maximum_index_in_backtrace_stack_for_internal_error,
	    G2int_maximum_index_in_backtrace_stack_for_internal_error);
    SET_SYMBOL_VALUE(Qg2int_maximum_index_in_backtrace_stack_for_internal_error,
	    FIXNUM_SUB1(G2int_size_of_backtrace_stack_for_internal_error));
    Qg2int_size_of_basic_backtrace_information = 
	    STATIC_SYMBOL("SIZE-OF-BASIC-BACKTRACE-INFORMATION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_size_of_basic_backtrace_information,
	    FIX((SI_Long)3L));
    Qg2int_gensym_error_buffer_initial_size = 
	    STATIC_SYMBOL("GENSYM-ERROR-BUFFER-INITIAL-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gensym_error_buffer_initial_size,
	    FIX((SI_Long)1000L));
    Qg2int_x11_or = STATIC_SYMBOL("X11-OR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_or,FIX((SI_Long)0L));
    Qg2int_x11_copy = STATIC_SYMBOL("X11-COPY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_copy,FIX((SI_Long)1L));
    Qg2int_x11_xor = STATIC_SYMBOL("X11-XOR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_xor,FIX((SI_Long)2L));
    Qg2int_x11_and = STATIC_SYMBOL("X11-AND",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_and,FIX((SI_Long)3L));
    Qg2int_x11_stippled = STATIC_SYMBOL("X11-STIPPLED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_stippled,FIX((SI_Long)4L));
    Qg2int_x11_transparent_copy = STATIC_SYMBOL("X11-TRANSPARENT-COPY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_transparent_copy,FIX((SI_Long)5L));
    Qg2int_x11_number_of_bits_in_event_codes = 
	    STATIC_SYMBOL("X11-NUMBER-OF-BITS-IN-EVENT-CODES",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_number_of_bits_in_event_codes,
	    FIX((SI_Long)4L));
    Qg2int_x11_event_codes_mask = STATIC_SYMBOL("X11-EVENT-CODES-MASK",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_x11_event_codes_mask,
	    G2int_x11_event_codes_mask);
    SET_SYMBOL_VALUE(Qg2int_x11_event_codes_mask,
	    FIXNUM_SUB1(FIX((SI_Long)16L)));
    Qg2int_x11_key_code_shift = STATIC_SYMBOL("X11-KEY-CODE-SHIFT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_x11_key_code_shift,
	    G2int_x11_key_code_shift);
    SET_SYMBOL_VALUE(Qg2int_x11_key_code_shift,
	    FIXNUM_NEGATE(G2int_x11_number_of_bits_in_event_codes));
    Qg2int_x11_no_more_events = STATIC_SYMBOL("X11-NO-MORE-EVENTS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_no_more_events,FIX((SI_Long)-1L));
    Qg2int_x11_nullevent = STATIC_SYMBOL("X11-NULLEVENT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_nullevent,FIX((SI_Long)0L));
    Qg2int_x11_keypress = STATIC_SYMBOL("X11-KEYPRESS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_keypress,FIX((SI_Long)1L));
    Qg2int_x11_button_press = STATIC_SYMBOL("X11-BUTTON-PRESS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_button_press,FIX((SI_Long)2L));
    Qg2int_x11_button_release = STATIC_SYMBOL("X11-BUTTON-RELEASE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_button_release,FIX((SI_Long)3L));
    Qg2int_x11_pointer_motion = STATIC_SYMBOL("X11-POINTER-MOTION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_pointer_motion,FIX((SI_Long)4L));
    Qg2int_x11_exposure = STATIC_SYMBOL("X11-EXPOSURE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_exposure,FIX((SI_Long)5L));
    Qg2int_x11_reshape = STATIC_SYMBOL("X11-RESHAPE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_reshape,FIX((SI_Long)6L));
    Qg2int_x11_enter = STATIC_SYMBOL("X11-ENTER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_enter,FIX((SI_Long)7L));
    Qg2int_x11_leave = STATIC_SYMBOL("X11-LEAVE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_leave,FIX((SI_Long)8L));
    Qg2int_x11_focus_in = STATIC_SYMBOL("X11-FOCUS-IN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_focus_in,FIX((SI_Long)9L));
    Qg2int_x11_focus_out = STATIC_SYMBOL("X11-FOCUS-OUT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_focus_out,FIX((SI_Long)10L));
    Qg2int_x11_control = STATIC_SYMBOL("X11-CONTROL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_x11_control,FIX((SI_Long)11L));
    Qg2int_specified_max_clipboard_text_length = 
	    STATIC_SYMBOL("SPECIFIED-MAX-CLIPBOARD-TEXT-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_specified_max_clipboard_text_length,
	    FIX((SI_Long)65535L));
    Qg2int_allocated_clipboard_text_length = 
	    STATIC_SYMBOL("ALLOCATED-CLIPBOARD-TEXT-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_allocated_clipboard_text_length,
	    FIX((SI_Long)65536L));
    Qg2int_clipboard_reading_results_vector_length = 
	    STATIC_SYMBOL("CLIPBOARD-READING-RESULTS-VECTOR-LENGTH",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_clipboard_reading_results_vector_length,
	    FIX((SI_Long)3L));
    Qg2int_latin_1_clipboard_read_results_entry = 
	    STATIC_SYMBOL("LATIN-1-CLIPBOARD-READ-RESULTS-ENTRY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_latin_1_clipboard_read_results_entry,
	    FIX((SI_Long)0L));
    Qg2int_x_compound_text_clipboard_read_results_entry = 
	    STATIC_SYMBOL("X-COMPOUND-TEXT-CLIPBOARD-READ-RESULTS-ENTRY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_x_compound_text_clipboard_read_results_entry,
	    FIX((SI_Long)1L));
    Qg2int_unicode_text_clipboard_read_results_entry = 
	    STATIC_SYMBOL("UNICODE-TEXT-CLIPBOARD-READ-RESULTS-ENTRY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_text_clipboard_read_results_entry,
	    FIX((SI_Long)2L));
    Qg2int_clipboard_read_results_failure_code = 
	    STATIC_SYMBOL("CLIPBOARD-READ-RESULTS-FAILURE-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_clipboard_read_results_failure_code,
	    FIX((SI_Long)65535L));
    Qg2int_gensym_windows_minimum_supported_dpi = 
	    STATIC_SYMBOL("GENSYM-WINDOWS-MINIMUM-SUPPORTED-DPI",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gensym_windows_minimum_supported_dpi,
	    FIX((SI_Long)36L));
    Qg2int_gensym_windows_maximum_supported_dpi = 
	    STATIC_SYMBOL("GENSYM-WINDOWS-MAXIMUM-SUPPORTED-DPI",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gensym_windows_maximum_supported_dpi,
	    FIX((SI_Long)200L));
    Qg2int_gensym_windows_standard_dpi = 
	    STATIC_SYMBOL("GENSYM-WINDOWS-STANDARD-DPI",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gensym_windows_standard_dpi,FIX((SI_Long)75L));
    Qg2int_gensym_windows_minimum_supported_scale = 
	    STATIC_SYMBOL("GENSYM-WINDOWS-MINIMUM-SUPPORTED-SCALE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gensym_windows_minimum_supported_scale,
	    G2int_gensym_windows_minimum_supported_scale);
    float_constant = STATIC_FLOAT(0.5);
    SET_SYMBOL_VALUE(Qg2int_gensym_windows_minimum_supported_scale,
	    float_constant);
    Qg2int_gensym_windows_maximum_supported_scale = 
	    STATIC_SYMBOL("GENSYM-WINDOWS-MAXIMUM-SUPPORTED-SCALE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gensym_windows_maximum_supported_scale,
	    G2int_gensym_windows_maximum_supported_scale);
    float_constant_1 = STATIC_FLOAT(2.66);
    SET_SYMBOL_VALUE(Qg2int_gensym_windows_maximum_supported_scale,
	    float_constant_1);
    Qg2int_maximum_polygon_points = STATIC_SYMBOL("MAXIMUM-POLYGON-POINTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_polygon_points,FIX((SI_Long)500L));
    Qg2int_original_icp_window_protocol_version = 
	    STATIC_SYMBOL("ORIGINAL-ICP-WINDOW-PROTOCOL-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_original_icp_window_protocol_version,
	    FIX((SI_Long)0L));
    Qg2int_icp_window_protocol_supports_monochrome_raster_lists = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MONOCHROME-RASTER-LISTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_monochrome_raster_lists,
	    FIX((SI_Long)2L));
    Qg2int_icp_window_protocol_supports_transparent_copy = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TRANSPARENT-COPY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_transparent_copy,
	    FIX((SI_Long)3L));
    Qg2int_icp_window_protocol_supports_setting_protocol_level = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SETTING-PROTOCOL-LEVEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_setting_protocol_level,
	    FIX((SI_Long)4L));
    Qg2int_icp_window_protocol_supports_scrolling = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SCROLLING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_scrolling,
	    FIX((SI_Long)4L));
    Qg2int_icp_window_protocol_supports_v4_mouse_messages = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-V4-MOUSE-MESSAGES",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_v4_mouse_messages,
	    FIX((SI_Long)5L));
    Qg2int_icp_window_protocol_supports_floating_telewindows = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-FLOATING-TELEWINDOWS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_floating_telewindows,
	    FIX((SI_Long)6L));
    Qg2int_icp_window_protocol_supports_force_graphics = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-FORCE-GRAPHICS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_force_graphics,
	    FIX((SI_Long)7L));
    Qg2int_icp_window_protocol_supports_ping_drawing = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-PING-DRAWING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_ping_drawing,
	    FIX((SI_Long)8L));
    Qg2int_icp_window_protocol_supports_telewindows_connection_license_info 
	    = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TELEWINDOWS-CONNECTION-LICENSE-INFO",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_telewindows_connection_license_info,
	    FIX((SI_Long)9L));
    Qg2int_icp_window_protocol_supports_slavic_font = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SLAVIC-FONT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_slavic_font,
	    FIX((SI_Long)10L));
    Qg2int_icp_window_protocol_supports_remote_processes = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-REMOTE-PROCESSES",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_remote_processes,
	    FIX((SI_Long)11L));
    Qg2int_icp_window_protocol_supports_remote_executables = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-REMOTE-EXECUTABLES",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_remote_executables,
	    FIX((SI_Long)12L));
    Qg2int_icp_window_protocol_supports_oriented_text_in_scratchpad_rasters 
	    = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-ORIENTED-TEXT-IN-SCRATCHPAD-RASTERS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_oriented_text_in_scratchpad_rasters,
	    FIX((SI_Long)13L));
    Qg2int_icp_window_protocol_supports_text_strings_as_wide_strings = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TEXT-STRINGS-AS-WIDE-STRINGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_text_strings_as_wide_strings,
	    FIX((SI_Long)14L));
    Qg2int_icp_window_protocol_supports_md5_password_encryption = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MD5-PASSWORD-ENCRYPTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_md5_password_encryption,
	    FIX((SI_Long)15L));
    Qg2int_icp_window_protocol_supports_saving_user_settings = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SAVING-USER-SETTINGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_saving_user_settings,
	    FIX((SI_Long)16L));
    Qg2int_icp_window_protocol_supports_un_decomposed_polygons = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-UN-DECOMPOSED-POLYGONS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_un_decomposed_polygons,
	    FIX((SI_Long)18L));
    Qg2int_icp_window_protocol_supports_polychrome_icon_images = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-POLYCHROME-ICON-IMAGES",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_polychrome_icon_images,
	    FIX((SI_Long)17L));
    Qg2int_icp_window_protocol_supports_native_cut_and_paste = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-CUT-AND-PASTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_native_cut_and_paste,
	    FIX((SI_Long)19L));
    Qg2int_icp_window_protocol_supports_request_for_paste_availability = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-REQUEST-FOR-PASTE-AVAILABILITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_request_for_paste_availability,
	    FIX((SI_Long)20L));
    Qg2int_icp_window_protocol_supports_unicode_character_events = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-UNICODE-CHARACTER-EVENTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_unicode_character_events,
	    FIX((SI_Long)21L));
    Qg2int_icp_window_protocol_supports_raster_stipples = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-RASTER-STIPPLES",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_raster_stipples,
	    FIX((SI_Long)22L));
    Qg2int_icp_window_protocol_supports_24bit_image_painting = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-24BIT-IMAGE-PAINTING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_24bit_image_painting,
	    FIX((SI_Long)23L));
    Qg2int_icp_window_protocol_supports_wide_polyline = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-WIDE-POLYLINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_wide_polyline,
	    FIX((SI_Long)24L));
    Qg2int_icp_window_protocol_supports_offscreen_drawing = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-OFFSCREEN-DRAWING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_offscreen_drawing,
	    FIX((SI_Long)25L));
    Qg2int_icp_window_protocol_supports_event_plists = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-EVENT-PLISTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_event_plists,
	    FIX((SI_Long)26L));
    Qg2int_icp_window_protocol_supports_native_widgets = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-WIDGETS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_native_widgets,
	    FIX((SI_Long)27L));
    Qg2int_icp_window_protocol_supports_image_tiling = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-IMAGE-TILING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_image_tiling,
	    FIX((SI_Long)28L));
    Qg2int_icp_window_protocol_supports_nms_menus = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NMS-MENUS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_nms_menus,
	    FIX((SI_Long)29L));
    Qg2int_icp_window_protocol_70r0 = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-70R0",AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_70r0,FIX((SI_Long)30L));
    Qg2int_icp_window_protocol_70_prerelease = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-70-PRERELEASE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_icp_window_protocol_70_prerelease,
	    G2int_icp_window_protocol_70_prerelease);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_70_prerelease,
	    add1(G2int_icp_window_protocol_supports_offscreen_drawing));
    Qg2int_icp_window_protocol_supports_native_printing = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-PRINTING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_native_printing,
	    FIX((SI_Long)31L));
    Qg2int_icp_window_protocol_supports_nms_posting_callbacks = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NMS-POSTING-CALLBACKS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_nms_posting_callbacks,
	    FIX((SI_Long)32L));
    Qg2int_icp_window_protocol_supports_native_icons = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-ICONS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_native_icons,
	    FIX((SI_Long)33L));
    Qg2int_icp_window_protocol_supports_move_telewindow = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MOVE-TELEWINDOW",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_move_telewindow,
	    FIX((SI_Long)34L));
    Qg2int_icp_window_protocol_supports_native_progress_bar = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-PROGRESS-BAR",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_native_progress_bar,
	    FIX((SI_Long)35L));
    Qg2int_icp_window_protocol_supports_basic_dialogs = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-BASIC-DIALOGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_icp_window_protocol_supports_basic_dialogs,
	    FIX((SI_Long)36L));
    Qg2int_sm_cxscreen = STATIC_SYMBOL("SM-CXSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxscreen,FIX((SI_Long)0L));
    Qg2int_sm_cyscreen = STATIC_SYMBOL("SM-CYSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyscreen,FIX((SI_Long)1L));
    Qg2int_sm_cxvscroll = STATIC_SYMBOL("SM-CXVSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxvscroll,FIX((SI_Long)2L));
    Qg2int_sm_cyhscroll = STATIC_SYMBOL("SM-CYHSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyhscroll,FIX((SI_Long)3L));
    Qg2int_sm_cycaption = STATIC_SYMBOL("SM-CYCAPTION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cycaption,FIX((SI_Long)4L));
    Qg2int_sm_cxborder = STATIC_SYMBOL("SM-CXBORDER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxborder,FIX((SI_Long)5L));
    Qg2int_sm_cyborder = STATIC_SYMBOL("SM-CYBORDER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyborder,FIX((SI_Long)6L));
    Qg2int_sm_cxdlgframe = STATIC_SYMBOL("SM-CXDLGFRAME",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxdlgframe,FIX((SI_Long)7L));
    Qg2int_sm_cydlgframe = STATIC_SYMBOL("SM-CYDLGFRAME",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cydlgframe,FIX((SI_Long)8L));
    Qg2int_sm_cyvthumb = STATIC_SYMBOL("SM-CYVTHUMB",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyvthumb,FIX((SI_Long)9L));
    Qg2int_sm_cxhthumb = STATIC_SYMBOL("SM-CXHTHUMB",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxhthumb,FIX((SI_Long)10L));
    Qg2int_sm_cxicon = STATIC_SYMBOL("SM-CXICON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxicon,FIX((SI_Long)11L));
    Qg2int_sm_cyicon = STATIC_SYMBOL("SM-CYICON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyicon,FIX((SI_Long)12L));
    Qg2int_sm_cxcursor = STATIC_SYMBOL("SM-CXCURSOR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxcursor,FIX((SI_Long)13L));
    Qg2int_sm_cycursor = STATIC_SYMBOL("SM-CYCURSOR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cycursor,FIX((SI_Long)14L));
    Qg2int_sm_cymenu = STATIC_SYMBOL("SM-CYMENU",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cymenu,FIX((SI_Long)15L));
    Qg2int_sm_cxfullscreen = STATIC_SYMBOL("SM-CXFULLSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxfullscreen,FIX((SI_Long)16L));
    Qg2int_sm_cyfullscreen = STATIC_SYMBOL("SM-CYFULLSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyfullscreen,FIX((SI_Long)17L));
    Qg2int_sm_cykanjiwindow = STATIC_SYMBOL("SM-CYKANJIWINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cykanjiwindow,FIX((SI_Long)18L));
    Qg2int_sm_mousepresent = STATIC_SYMBOL("SM-MOUSEPRESENT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_mousepresent,FIX((SI_Long)19L));
    Qg2int_sm_cyvscroll = STATIC_SYMBOL("SM-CYVSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyvscroll,FIX((SI_Long)20L));
    Qg2int_sm_cxhscroll = STATIC_SYMBOL("SM-CXHSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxhscroll,FIX((SI_Long)21L));
    Qg2int_sm_debug = STATIC_SYMBOL("SM-DEBUG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_debug,FIX((SI_Long)22L));
    Qg2int_sm_swapbutton = STATIC_SYMBOL("SM-SWAPBUTTON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_swapbutton,FIX((SI_Long)23L));
    Qg2int_sm_cxmin = STATIC_SYMBOL("SM-CXMIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxmin,FIX((SI_Long)28L));
    Qg2int_sm_cymin = STATIC_SYMBOL("SM-CYMIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cymin,FIX((SI_Long)29L));
    Qg2int_sm_cxsize = STATIC_SYMBOL("SM-CXSIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxsize,FIX((SI_Long)30L));
    Qg2int_sm_cysize = STATIC_SYMBOL("SM-CYSIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cysize,FIX((SI_Long)31L));
    Qg2int_sm_cxframe = STATIC_SYMBOL("SM-CXFRAME",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxframe,FIX((SI_Long)32L));
    Qg2int_sm_cyframe = STATIC_SYMBOL("SM-CYFRAME",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyframe,FIX((SI_Long)33L));
    Qg2int_sm_cxmintrack = STATIC_SYMBOL("SM-CXMINTRACK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxmintrack,FIX((SI_Long)34L));
    Qg2int_sm_cymintrack = STATIC_SYMBOL("SM-CYMINTRACK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cymintrack,FIX((SI_Long)35L));
    Qg2int_sm_cxdoubleclk = STATIC_SYMBOL("SM-CXDOUBLECLK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxdoubleclk,FIX((SI_Long)36L));
    Qg2int_sm_cydoubleclk = STATIC_SYMBOL("SM-CYDOUBLECLK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cydoubleclk,FIX((SI_Long)37L));
    Qg2int_sm_cxiconspacing = STATIC_SYMBOL("SM-CXICONSPACING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxiconspacing,FIX((SI_Long)38L));
    Qg2int_sm_cyiconspacing = STATIC_SYMBOL("SM-CYICONSPACING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyiconspacing,FIX((SI_Long)39L));
    Qg2int_sm_menudropalignment = STATIC_SYMBOL("SM-MENUDROPALIGNMENT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_menudropalignment,FIX((SI_Long)40L));
    Qg2int_sm_penwindows = STATIC_SYMBOL("SM-PENWINDOWS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_penwindows,FIX((SI_Long)41L));
    Qg2int_sm_dbcsenabled = STATIC_SYMBOL("SM-DBCSENABLED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_dbcsenabled,FIX((SI_Long)42L));
    Qg2int_sm_cmousebuttons = STATIC_SYMBOL("SM-CMOUSEBUTTONS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cmousebuttons,FIX((SI_Long)43L));
    Qg2int_sm_secure = STATIC_SYMBOL("SM-SECURE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_secure,FIX((SI_Long)44L));
    Qg2int_sm_cxedge = STATIC_SYMBOL("SM-CXEDGE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxedge,FIX((SI_Long)45L));
    Qg2int_sm_cyedge = STATIC_SYMBOL("SM-CYEDGE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyedge,FIX((SI_Long)46L));
    Qg2int_sm_cxminspacing = STATIC_SYMBOL("SM-CXMINSPACING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxminspacing,FIX((SI_Long)47L));
    Qg2int_sm_cyminspacing = STATIC_SYMBOL("SM-CYMINSPACING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyminspacing,FIX((SI_Long)48L));
    Qg2int_sm_cxsmicon = STATIC_SYMBOL("SM-CXSMICON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxsmicon,FIX((SI_Long)49L));
    Qg2int_sm_cysmicon = STATIC_SYMBOL("SM-CYSMICON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cysmicon,FIX((SI_Long)50L));
    Qg2int_sm_cysmcaption = STATIC_SYMBOL("SM-CYSMCAPTION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cysmcaption,FIX((SI_Long)51L));
    Qg2int_sm_cxsmsize = STATIC_SYMBOL("SM-CXSMSIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxsmsize,FIX((SI_Long)52L));
    Qg2int_sm_cysmsize = STATIC_SYMBOL("SM-CYSMSIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cysmsize,FIX((SI_Long)53L));
    Qg2int_sm_cxmenusize = STATIC_SYMBOL("SM-CXMENUSIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxmenusize,FIX((SI_Long)54L));
    Qg2int_sm_cymenusize = STATIC_SYMBOL("SM-CYMENUSIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cymenusize,FIX((SI_Long)55L));
    Qg2int_sm_arrange = STATIC_SYMBOL("SM-ARRANGE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_arrange,FIX((SI_Long)56L));
    Qg2int_sm_cxminimized = STATIC_SYMBOL("SM-CXMINIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxminimized,FIX((SI_Long)57L));
    Qg2int_sm_cyminimized = STATIC_SYMBOL("SM-CYMINIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyminimized,FIX((SI_Long)58L));
    Qg2int_sm_cxmaxtrack = STATIC_SYMBOL("SM-CXMAXTRACK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxmaxtrack,FIX((SI_Long)59L));
    Qg2int_sm_cymaxtrack = STATIC_SYMBOL("SM-CYMAXTRACK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cymaxtrack,FIX((SI_Long)60L));
    Qg2int_sm_cxmaximized = STATIC_SYMBOL("SM-CXMAXIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxmaximized,FIX((SI_Long)61L));
    Qg2int_sm_cymaximized = STATIC_SYMBOL("SM-CYMAXIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cymaximized,FIX((SI_Long)62L));
    Qg2int_sm_network = STATIC_SYMBOL("SM-NETWORK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_network,FIX((SI_Long)63L));
    Qg2int_sm_cleanboot = STATIC_SYMBOL("SM-CLEANBOOT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cleanboot,FIX((SI_Long)67L));
    Qg2int_sm_cxdrag = STATIC_SYMBOL("SM-CXDRAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxdrag,FIX((SI_Long)68L));
    Qg2int_sm_cydrag = STATIC_SYMBOL("SM-CYDRAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cydrag,FIX((SI_Long)69L));
    Qg2int_sm_showsounds = STATIC_SYMBOL("SM-SHOWSOUNDS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_showsounds,FIX((SI_Long)70L));
    Qg2int_sm_cxmenucheck = STATIC_SYMBOL("SM-CXMENUCHECK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxmenucheck,FIX((SI_Long)71L));
    Qg2int_sm_cymenucheck = STATIC_SYMBOL("SM-CYMENUCHECK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cymenucheck,FIX((SI_Long)72L));
    Qg2int_sm_slowmachine = STATIC_SYMBOL("SM-SLOWMACHINE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_slowmachine,FIX((SI_Long)73L));
    Qg2int_sm_mideastenabled = STATIC_SYMBOL("SM-MIDEASTENABLED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_mideastenabled,FIX((SI_Long)74L));
    Qg2int_sm_mousewheelpresent = STATIC_SYMBOL("SM-MOUSEWHEELPRESENT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_mousewheelpresent,FIX((SI_Long)75L));
    Qg2int_sm_xvirtualscreen = STATIC_SYMBOL("SM-XVIRTUALSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_xvirtualscreen,FIX((SI_Long)76L));
    Qg2int_sm_yvirtualscreen = STATIC_SYMBOL("SM-YVIRTUALSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_yvirtualscreen,FIX((SI_Long)77L));
    Qg2int_sm_cxvirtualscreen = STATIC_SYMBOL("SM-CXVIRTUALSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxvirtualscreen,FIX((SI_Long)78L));
    Qg2int_sm_cyvirtualscreen = STATIC_SYMBOL("SM-CYVIRTUALSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cyvirtualscreen,FIX((SI_Long)79L));
    Qg2int_sm_cmonitors = STATIC_SYMBOL("SM-CMONITORS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cmonitors,FIX((SI_Long)80L));
    Qg2int_sm_samedisplayformat = STATIC_SYMBOL("SM-SAMEDISPLAYFORMAT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_samedisplayformat,FIX((SI_Long)81L));
    Qg2int_sm_cxdialog = STATIC_SYMBOL("SM-CXDIALOG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cxdialog,FIX((SI_Long)82L));
    Qg2int_sm_cydialog = STATIC_SYMBOL("SM-CYDIALOG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sm_cydialog,FIX((SI_Long)83L));
    Qg2int_number_of_system_metrics = 
	    STATIC_SYMBOL("NUMBER-OF-SYSTEM-METRICS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_number_of_system_metrics,FIX((SI_Long)84L));
    Qg2int_maximum_interval_between_new_time_for_uuid = 
	    STATIC_SYMBOL("MAXIMUM-INTERVAL-BETWEEN-NEW-TIME-FOR-UUID",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_maximum_interval_between_new_time_for_uuid,
	    G2int_maximum_interval_between_new_time_for_uuid);
    float_constant_2 = STATIC_FLOAT(600.0);
    SET_SYMBOL_VALUE(Qg2int_maximum_interval_between_new_time_for_uuid,
	    float_constant_2);
    Qg2int_uuid_offset_mask = STATIC_SYMBOL("UUID-OFFSET-MASK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_uuid_offset_mask,FIX((SI_Long)255L));
    Qg2int_ne_blocked_value = STATIC_SYMBOL("NE-BLOCKED-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ne_blocked_value,FIX((SI_Long)0L));
    Qg2int_ne_eof_value = STATIC_SYMBOL("NE-EOF-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ne_eof_value,FIX((SI_Long)-1L));
    Qg2int_ne_error_value = STATIC_SYMBOL("NE-ERROR-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ne_error_value,FIX((SI_Long)-2L));
    Qg2int_minimum_message_series_size_before_suspending = 
	    STATIC_SYMBOL("MINIMUM-MESSAGE-SERIES-SIZE-BEFORE-SUSPENDING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_minimum_message_series_size_before_suspending,
	    FIX((SI_Long)8000L));
    Qg2int_minimum_message_series_size_before_beginning_new_series = 
	    STATIC_SYMBOL("MINIMUM-MESSAGE-SERIES-SIZE-BEFORE-BEGINNING-NEW-SERIES",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_minimum_message_series_size_before_beginning_new_series,
	    FIX((SI_Long)20000L));
    Qg2int_use_all_network_protocols = 
	    STATIC_SYMBOL("USE-ALL-NETWORK-PROTOCOLS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_use_all_network_protocols,FIX((SI_Long)14L));
    Qg2int_use_tcpip_protocol_only = 
	    STATIC_SYMBOL("USE-TCPIP-PROTOCOL-ONLY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_use_tcpip_protocol_only,FIX((SI_Long)13L));
    Qg2int_use_no_network_protocols = 
	    STATIC_SYMBOL("USE-NO-NETWORK-PROTOCOLS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_use_no_network_protocols,FIX((SI_Long)-1L));
    Qg2int_g2_product_tag = STATIC_SYMBOL("G2-PRODUCT-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_product_tag,FIX((SI_Long)1L));
    Qg2int_gsi_product_tag = STATIC_SYMBOL("GSI-PRODUCT-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_product_tag,FIX((SI_Long)2L));
    Qg2int_minimum_intensity_for_white = 
	    STATIC_SYMBOL("MINIMUM-INTENSITY-FOR-WHITE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_minimum_intensity_for_white,FIX((SI_Long)192L));
    Qg2int_transparent_color_value = 
	    STATIC_SYMBOL("TRANSPARENT-COLOR-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_transparent_color_value,FIX((SI_Long)16777216L));
    Qg2int_no_stipple_value = STATIC_SYMBOL("NO-STIPPLE-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_no_stipple_value,FIX((SI_Long)0L));
    Qg2int_ps_solid = STATIC_SYMBOL("PS-SOLID",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_solid,FIX((SI_Long)0L));
    Qg2int_ps_dash = STATIC_SYMBOL("PS-DASH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_dash,FIX((SI_Long)1L));
    Qg2int_ps_dot = STATIC_SYMBOL("PS-DOT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_dot,FIX((SI_Long)2L));
    Qg2int_ps_dashdot = STATIC_SYMBOL("PS-DASHDOT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_dashdot,FIX((SI_Long)3L));
    Qg2int_ps_dashdotdot = STATIC_SYMBOL("PS-DASHDOTDOT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_dashdotdot,FIX((SI_Long)4L));
    Qg2int_ps_userstyle = STATIC_SYMBOL("PS-USERSTYLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_userstyle,FIX((SI_Long)7L));
    Qg2int_ps_endcap_round = STATIC_SYMBOL("PS-ENDCAP-ROUND",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_endcap_round,FIX((SI_Long)0L));
    Qg2int_ps_endcap_square = STATIC_SYMBOL("PS-ENDCAP-SQUARE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_endcap_square,FIX((SI_Long)256L));
    Qg2int_ps_endcap_flat = STATIC_SYMBOL("PS-ENDCAP-FLAT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_endcap_flat,FIX((SI_Long)512L));
    Qg2int_ps_join_round = STATIC_SYMBOL("PS-JOIN-ROUND",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_join_round,FIX((SI_Long)0L));
    Qg2int_ps_join_bevel = STATIC_SYMBOL("PS-JOIN-BEVEL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_join_bevel,FIX((SI_Long)4096L));
    Qg2int_ps_join_miter = STATIC_SYMBOL("PS-JOIN-MITER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ps_join_miter,FIX((SI_Long)8192L));
    Qg2int_enable_offscreen_drawing = 
	    STATIC_SYMBOL("ENABLE-OFFSCREEN-DRAWING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_enable_offscreen_drawing,FIX((SI_Long)1L));
    Qg2int_disable_offscreen_drawing = 
	    STATIC_SYMBOL("DISABLE-OFFSCREEN-DRAWING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_disable_offscreen_drawing,FIX((SI_Long)2L));
    Qg2int_bitblt_offscreen_pixmap = 
	    STATIC_SYMBOL("BITBLT-OFFSCREEN-PIXMAP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_bitblt_offscreen_pixmap,FIX((SI_Long)3L));
    Qg2int_reclaim_offscreen_pixmap = 
	    STATIC_SYMBOL("RECLAIM-OFFSCREEN-PIXMAP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_reclaim_offscreen_pixmap,FIX((SI_Long)4L));
    Qg2int_frame_type_none = STATIC_SYMBOL("FRAME-TYPE-NONE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_frame_type_none,FIX((SI_Long)0L));
    Qg2int_frame_type_classic = STATIC_SYMBOL("FRAME-TYPE-CLASSIC",AB_package);
    SET_SYMBOL_VALUE(Qg2int_frame_type_classic,FIX((SI_Long)1L));
    Qg2int_frame_type_child = STATIC_SYMBOL("FRAME-TYPE-CHILD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_frame_type_child,FIX((SI_Long)2L));
    Qg2int_frame_type_sdi = STATIC_SYMBOL("FRAME-TYPE-SDI",AB_package);
    SET_SYMBOL_VALUE(Qg2int_frame_type_sdi,FIX((SI_Long)3L));
    Qg2int_frame_type_mdi = STATIC_SYMBOL("FRAME-TYPE-MDI",AB_package);
    SET_SYMBOL_VALUE(Qg2int_frame_type_mdi,FIX((SI_Long)4L));
    Qg2int_nip_wintype_classic = STATIC_SYMBOL("NIP-WINTYPE-CLASSIC",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_wintype_classic,FIX((SI_Long)0L));
    Qg2int_nip_wintype_mask = STATIC_SYMBOL("NIP-WINTYPE-MASK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_wintype_mask,FIX((SI_Long)15L));
    Qg2int_nip_show_window = STATIC_SYMBOL("NIP-SHOW-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_show_window,FIX((SI_Long)1L));
    Qg2int_nip_move_window = STATIC_SYMBOL("NIP-MOVE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_move_window,FIX((SI_Long)2L));
    Qg2int_nip_reshape_window = STATIC_SYMBOL("NIP-RESHAPE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_reshape_window,FIX((SI_Long)3L));
    Qg2int_nip_raise_window = STATIC_SYMBOL("NIP-RAISE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_raise_window,FIX((SI_Long)4L));
    Qg2int_nip_lower_window = STATIC_SYMBOL("NIP-LOWER-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_lower_window,FIX((SI_Long)5L));
    Qg2int_nip_destroy_window = STATIC_SYMBOL("NIP-DESTROY-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_destroy_window,FIX((SI_Long)6L));
    Qg2int_nip_caption_window = STATIC_SYMBOL("NIP-CAPTION-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_caption_window,FIX((SI_Long)7L));
    Qg2int_nip_inflate_window = STATIC_SYMBOL("NIP-INFLATE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_inflate_window,FIX((SI_Long)8L));
    Qg2int_nip_scroll_window = STATIC_SYMBOL("NIP-SCROLL-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_scroll_window,FIX((SI_Long)9L));
    Qg2int_nip_cerase_window = STATIC_SYMBOL("NIP-CERASE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_cerase_window,FIX((SI_Long)10L));
    Qg2int_nip_set_max_size = STATIC_SYMBOL("NIP-SET-MAX-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_set_max_size,FIX((SI_Long)11L));
    Qg2int_nip_restyle_window = STATIC_SYMBOL("NIP-RESTYLE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_restyle_window,FIX((SI_Long)12L));
    Qg2int_nip_zorder_window = STATIC_SYMBOL("NIP-ZORDER-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_zorder_window,FIX((SI_Long)13L));
    Qg2int_nip_set_icon = STATIC_SYMBOL("NIP-SET-ICON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_set_icon,FIX((SI_Long)14L));
    Qg2int_nip_set_closeable = STATIC_SYMBOL("NIP-SET-CLOSEABLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_set_closeable,FIX((SI_Long)15L));
    Qg2int_nip_rescale_window = STATIC_SYMBOL("NIP-RESCALE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_rescale_window,FIX((SI_Long)16L));
    Qg2int_nip_set_background_color = 
	    STATIC_SYMBOL("NIP-SET-BACKGROUND-COLOR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_set_background_color,FIX((SI_Long)17L));
    Qg2int_nip_size_window = STATIC_SYMBOL("NIP-SIZE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nip_size_window,FIX((SI_Long)18L));
    Qg2int_sw_hide = STATIC_SYMBOL("SW-HIDE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_hide,FIX((SI_Long)0L));
    Qg2int_sw_shownormal = STATIC_SYMBOL("SW-SHOWNORMAL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_shownormal,FIX((SI_Long)1L));
    Qg2int_sw_showminimized = STATIC_SYMBOL("SW-SHOWMINIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_showminimized,FIX((SI_Long)2L));
    Qg2int_sw_maximize = STATIC_SYMBOL("SW-MAXIMIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_maximize,FIX((SI_Long)3L));
    Qg2int_sw_shownoactivate = STATIC_SYMBOL("SW-SHOWNOACTIVATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_shownoactivate,FIX((SI_Long)4L));
    Qg2int_sw_show = STATIC_SYMBOL("SW-SHOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_show,FIX((SI_Long)5L));
    Qg2int_sw_minimize = STATIC_SYMBOL("SW-MINIMIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_minimize,FIX((SI_Long)6L));
    Qg2int_sw_showminnoactive = STATIC_SYMBOL("SW-SHOWMINNOACTIVE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_showminnoactive,FIX((SI_Long)7L));
    Qg2int_sw_showna = STATIC_SYMBOL("SW-SHOWNA",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_showna,FIX((SI_Long)8L));
    Qg2int_sw_restore = STATIC_SYMBOL("SW-RESTORE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_restore,FIX((SI_Long)9L));
    Qg2int_sw_showdefault = STATIC_SYMBOL("SW-SHOWDEFAULT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sw_showdefault,FIX((SI_Long)10L));
    Qg2int_ws_overlapped = STATIC_SYMBOL("WS-OVERLAPPED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_overlapped,FIX((SI_Long)0L));
    Qg2int_ws_popup = STATIC_SYMBOL("WS-POPUP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_popup,FIX((SI_Long)32768L));
    Qg2int_ws_child = STATIC_SYMBOL("WS-CHILD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_child,FIX((SI_Long)16384L));
    Qg2int_ws_minimize = STATIC_SYMBOL("WS-MINIMIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_minimize,FIX((SI_Long)8192L));
    Qg2int_ws_visible = STATIC_SYMBOL("WS-VISIBLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_visible,FIX((SI_Long)4096L));
    Qg2int_ws_disabled = STATIC_SYMBOL("WS-DISABLED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_disabled,FIX((SI_Long)2048L));
    Qg2int_ws_clipsiblings = STATIC_SYMBOL("WS-CLIPSIBLINGS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_clipsiblings,FIX((SI_Long)1024L));
    Qg2int_ws_clipchildren = STATIC_SYMBOL("WS-CLIPCHILDREN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_clipchildren,FIX((SI_Long)512L));
    Qg2int_ws_maximize = STATIC_SYMBOL("WS-MAXIMIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_maximize,FIX((SI_Long)256L));
    Qg2int_ws_caption = STATIC_SYMBOL("WS-CAPTION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_caption,FIX((SI_Long)192L));
    Qg2int_ws_border = STATIC_SYMBOL("WS-BORDER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_border,FIX((SI_Long)128L));
    Qg2int_ws_dlgframe = STATIC_SYMBOL("WS-DLGFRAME",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_dlgframe,FIX((SI_Long)64L));
    Qg2int_ws_vscroll = STATIC_SYMBOL("WS-VSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_vscroll,FIX((SI_Long)32L));
    Qg2int_ws_hscroll = STATIC_SYMBOL("WS-HSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_hscroll,FIX((SI_Long)16L));
    Qg2int_ws_sysmenu = STATIC_SYMBOL("WS-SYSMENU",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_sysmenu,FIX((SI_Long)8L));
    Qg2int_ws_thickframe = STATIC_SYMBOL("WS-THICKFRAME",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_thickframe,FIX((SI_Long)4L));
    Qg2int_ws_group = STATIC_SYMBOL("WS-GROUP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_group,FIX((SI_Long)2L));
    Qg2int_ws_tabstop = STATIC_SYMBOL("WS-TABSTOP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_tabstop,FIX((SI_Long)1L));
    Qg2int_ws_minimizebox = STATIC_SYMBOL("WS-MINIMIZEBOX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_minimizebox,FIX((SI_Long)2L));
    Qg2int_ws_maximizebox = STATIC_SYMBOL("WS-MAXIMIZEBOX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_maximizebox,FIX((SI_Long)1L));
    Qg2int_ws_ex_dlgmodalframe = STATIC_SYMBOL("WS-EX-DLGMODALFRAME",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_dlgmodalframe,FIX((SI_Long)1L));
    Qg2int_ws_ex_noparentnotify = STATIC_SYMBOL("WS-EX-NOPARENTNOTIFY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_noparentnotify,FIX((SI_Long)4L));
    Qg2int_ws_ex_topmost = STATIC_SYMBOL("WS-EX-TOPMOST",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_topmost,FIX((SI_Long)8L));
    Qg2int_ws_ex_acceptfiles = STATIC_SYMBOL("WS-EX-ACCEPTFILES",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_acceptfiles,FIX((SI_Long)16L));
    Qg2int_ws_ex_transparent = STATIC_SYMBOL("WS-EX-TRANSPARENT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_transparent,FIX((SI_Long)32L));
    Qg2int_ws_ex_mdichild = STATIC_SYMBOL("WS-EX-MDICHILD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_mdichild,FIX((SI_Long)64L));
    Qg2int_ws_ex_toolwindow = STATIC_SYMBOL("WS-EX-TOOLWINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_toolwindow,FIX((SI_Long)128L));
    Qg2int_ws_ex_windowedge = STATIC_SYMBOL("WS-EX-WINDOWEDGE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_windowedge,FIX((SI_Long)256L));
    Qg2int_ws_ex_clientedge = STATIC_SYMBOL("WS-EX-CLIENTEDGE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_clientedge,FIX((SI_Long)512L));
    Qg2int_ws_ex_contexthelp = STATIC_SYMBOL("WS-EX-CONTEXTHELP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_contexthelp,FIX((SI_Long)1024L));
    Qg2int_ws_ex_right = STATIC_SYMBOL("WS-EX-RIGHT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_right,FIX((SI_Long)4096L));
    Qg2int_ws_ex_left = STATIC_SYMBOL("WS-EX-LEFT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_left,FIX((SI_Long)0L));
    Qg2int_ws_ex_rtlreading = STATIC_SYMBOL("WS-EX-RTLREADING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_rtlreading,FIX((SI_Long)8192L));
    Qg2int_ws_ex_ltrreading = STATIC_SYMBOL("WS-EX-LTRREADING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_ltrreading,FIX((SI_Long)0L));
    Qg2int_ws_ex_leftscrollbar = STATIC_SYMBOL("WS-EX-LEFTSCROLLBAR",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_leftscrollbar,FIX((SI_Long)16384L));
    Qg2int_ws_ex_rightscrollbar = STATIC_SYMBOL("WS-EX-RIGHTSCROLLBAR",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_rightscrollbar,FIX((SI_Long)0L));
    Qg2int_ws_ex_controlparent = STATIC_SYMBOL("WS-EX-CONTROLPARENT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_controlparent,FIX((SI_Long)65536L));
    Qg2int_ws_ex_staticedge = STATIC_SYMBOL("WS-EX-STATICEDGE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_staticedge,FIX((SI_Long)131072L));
    Qg2int_ws_ex_appwindow = STATIC_SYMBOL("WS-EX-APPWINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ws_ex_appwindow,FIX((SI_Long)262144L));
    Qg2int_size_restored = STATIC_SYMBOL("SIZE-RESTORED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_size_restored,FIX((SI_Long)0L));
    Qg2int_size_minimized = STATIC_SYMBOL("SIZE-MINIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_size_minimized,FIX((SI_Long)1L));
    Qg2int_size_maximized = STATIC_SYMBOL("SIZE-MAXIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_size_maximized,FIX((SI_Long)2L));
    Qg2int_size_maxshow = STATIC_SYMBOL("SIZE-MAXSHOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_size_maxshow,FIX((SI_Long)3L));
    Qg2int_size_maxhide = STATIC_SYMBOL("SIZE-MAXHIDE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_size_maxhide,FIX((SI_Long)4L));
    Qg2int_status_floated = STATIC_SYMBOL("STATUS-FLOATED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_floated,FIX((SI_Long)8L));
    Qg2int_status_docked = STATIC_SYMBOL("STATUS-DOCKED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_docked,FIX((SI_Long)9L));
    Qg2int_status_autohidden = STATIC_SYMBOL("STATUS-AUTOHIDDEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_autohidden,FIX((SI_Long)10L));
    Qg2int_status_unknown = STATIC_SYMBOL("STATUS-UNKNOWN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_unknown,FIX((SI_Long)11L));
    Qg2int_status_expanded = STATIC_SYMBOL("STATUS-EXPANDED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_expanded,FIX((SI_Long)12L));
    Qg2int_status_collapsed = STATIC_SYMBOL("STATUS-COLLAPSED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_collapsed,FIX((SI_Long)13L));
    Qg2int_status_closed = STATIC_SYMBOL("STATUS-CLOSED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_closed,FIX((SI_Long)14L));
    Qg2int_status_attached = STATIC_SYMBOL("STATUS-ATTACHED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_attached,FIX((SI_Long)15L));
    Qg2int_status_docked_left = STATIC_SYMBOL("STATUS-DOCKED-LEFT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_docked_left,FIX((SI_Long)16L));
    Qg2int_status_docked_top = STATIC_SYMBOL("STATUS-DOCKED-TOP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_docked_top,FIX((SI_Long)17L));
    Qg2int_status_docked_right = STATIC_SYMBOL("STATUS-DOCKED-RIGHT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_docked_right,FIX((SI_Long)18L));
    Qg2int_status_docked_bottom = STATIC_SYMBOL("STATUS-DOCKED-BOTTOM",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_docked_bottom,FIX((SI_Long)19L));
    Qg2int_status_hidden = STATIC_SYMBOL("STATUS-HIDDEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_hidden,FIX((SI_Long)20L));
    Qg2int_cw_usedefault = STATIC_SYMBOL("CW-USEDEFAULT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_cw_usedefault,FIX((SI_Long)-30000L));
    Qg2int_sort_column_default = STATIC_SYMBOL("SORT-COLUMN-DEFAULT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_sort_column_default,FIX((SI_Long)-1L));
    Qg2int_sorting_order_default = STATIC_SYMBOL("SORTING-ORDER-DEFAULT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_sorting_order_default,FIX((SI_Long)1L));
    Qg2int_swp_hwnd_top = STATIC_SYMBOL("SWP-HWND-TOP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_swp_hwnd_top,FIX((SI_Long)-1L));
    Qg2int_swp_hwnd_bottom = STATIC_SYMBOL("SWP-HWND-BOTTOM",AB_package);
    SET_SYMBOL_VALUE(Qg2int_swp_hwnd_bottom,FIX((SI_Long)-2L));
    Qg2int_swp_hwnd_topmost = STATIC_SYMBOL("SWP-HWND-TOPMOST",AB_package);
    SET_SYMBOL_VALUE(Qg2int_swp_hwnd_topmost,FIX((SI_Long)-3L));
    Qg2int_swp_hwnd_notopmost = STATIC_SYMBOL("SWP-HWND-NOTOPMOST",AB_package);
    SET_SYMBOL_VALUE(Qg2int_swp_hwnd_notopmost,FIX((SI_Long)-4L));
    Qg2int_dt_left = STATIC_SYMBOL("DT-LEFT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_left,FIX((SI_Long)0L));
    Qg2int_dt_center = STATIC_SYMBOL("DT-CENTER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_center,FIX((SI_Long)1L));
    Qg2int_dt_right = STATIC_SYMBOL("DT-RIGHT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_right,FIX((SI_Long)2L));
    Qg2int_dt_vcenter = STATIC_SYMBOL("DT-VCENTER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_vcenter,FIX((SI_Long)4L));
    Qg2int_dt_bottom = STATIC_SYMBOL("DT-BOTTOM",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_bottom,FIX((SI_Long)8L));
    Qg2int_dt_wordbreak = STATIC_SYMBOL("DT-WORDBREAK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_wordbreak,FIX((SI_Long)16L));
    Qg2int_dt_singleline = STATIC_SYMBOL("DT-SINGLELINE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_singleline,FIX((SI_Long)32L));
    Qg2int_dt_expandtabs = STATIC_SYMBOL("DT-EXPANDTABS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_expandtabs,FIX((SI_Long)64L));
    Qg2int_dt_editcontrol = STATIC_SYMBOL("DT-EDITCONTROL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_editcontrol,FIX((SI_Long)8192L));
    Qg2int_dt_path_ellipsis = STATIC_SYMBOL("DT-PATH-ELLIPSIS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_path_ellipsis,FIX((SI_Long)16384L));
    Qg2int_dt_end_ellipsis = STATIC_SYMBOL("DT-END-ELLIPSIS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dt_end_ellipsis,FIX((SI_Long)32768L));
    Qg2int_editor_create = STATIC_SYMBOL("EDITOR-CREATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_create,FIX((SI_Long)1L));
    Qg2int_editor_destroy = STATIC_SYMBOL("EDITOR-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_destroy,FIX((SI_Long)2L));
    Qg2int_editor_print = STATIC_SYMBOL("EDITOR-PRINT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_print,FIX((SI_Long)3L));
    Qg2int_editor_show = STATIC_SYMBOL("EDITOR-SHOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_show,FIX((SI_Long)4L));
    Qg2int_editor_modal = STATIC_SYMBOL("EDITOR-MODAL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_modal,FIX((SI_Long)5L));
    Qg2int_editor_add_toolbar_button = 
	    STATIC_SYMBOL("EDITOR-ADD-TOOLBAR-BUTTON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_add_toolbar_button,FIX((SI_Long)6L));
    Qg2int_editor_cancel = STATIC_SYMBOL("EDITOR-CANCEL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_cancel,FIX((SI_Long)7L));
    Qg2int_editor_clear_breakpoint = 
	    STATIC_SYMBOL("EDITOR-CLEAR-BREAKPOINT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_clear_breakpoint,FIX((SI_Long)20L));
    Qg2int_editor_disable_breakpoint = 
	    STATIC_SYMBOL("EDITOR-DISABLE-BREAKPOINT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_disable_breakpoint,FIX((SI_Long)21L));
    Qg2int_editor_set_breakpoint = STATIC_SYMBOL("EDITOR-SET-BREAKPOINT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_set_breakpoint,FIX((SI_Long)22L));
    Qg2int_editor_clear_breakpoints = 
	    STATIC_SYMBOL("EDITOR-CLEAR-BREAKPOINTS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_clear_breakpoints,FIX((SI_Long)24L));
    Qg2int_editor_syntax_repair = STATIC_SYMBOL("EDITOR-SYNTAX-REPAIR",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_syntax_repair,FIX((SI_Long)28L));
    Qg2int_editor_reset = STATIC_SYMBOL("EDITOR-RESET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_reset,FIX((SI_Long)30L));
    Qg2int_editor_set_text = STATIC_SYMBOL("EDITOR-SET-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_set_text,FIX((SI_Long)31L));
    Qg2int_editor_insert_text = STATIC_SYMBOL("EDITOR-INSERT-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_insert_text,FIX((SI_Long)32L));
    Qg2int_editor_syntax = STATIC_SYMBOL("EDITOR-SYNTAX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_syntax,FIX((SI_Long)33L));
    Qg2int_editor_completions = STATIC_SYMBOL("EDITOR-COMPLETIONS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_completions,FIX((SI_Long)34L));
    Qg2int_editor_arglist = STATIC_SYMBOL("EDITOR-ARGLIST",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_arglist,FIX((SI_Long)35L));
    Qg2int_editor_exit = STATIC_SYMBOL("EDITOR-EXIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_exit,FIX((SI_Long)36L));
    Qg2int_editor_notes = STATIC_SYMBOL("EDITOR-NOTES",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_notes,FIX((SI_Long)37L));
    Qg2int_editor_apply = STATIC_SYMBOL("EDITOR-APPLY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_apply,FIX((SI_Long)38L));
    Qg2int_editor_disable = STATIC_SYMBOL("EDITOR-DISABLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_disable,FIX((SI_Long)39L));
    Qg2int_editor_enable = STATIC_SYMBOL("EDITOR-ENABLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_enable,FIX((SI_Long)40L));
    Qg2int_editor_set_grammar = STATIC_SYMBOL("EDITOR-SET-GRAMMAR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_set_grammar,FIX((SI_Long)41L));
    Qg2int_editor_set_options = STATIC_SYMBOL("EDITOR-SET-OPTIONS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_set_options,FIX((SI_Long)42L));
    Qg2int_editor_set_tabs = STATIC_SYMBOL("EDITOR-SET-TABS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_set_tabs,FIX((SI_Long)43L));
    Qg2int_editor_cursor_moved = STATIC_SYMBOL("EDITOR-CURSOR-MOVED",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_cursor_moved,FIX((SI_Long)44L));
    Qg2int_editor_text_inserted = STATIC_SYMBOL("EDITOR-TEXT-INSERTED",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_text_inserted,FIX((SI_Long)45L));
    Qg2int_editor_text_deleted = STATIC_SYMBOL("EDITOR-TEXT-DELETED",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_text_deleted,FIX((SI_Long)46L));
    Qg2int_editor_incremental_updates = 
	    STATIC_SYMBOL("EDITOR-INCREMENTAL-UPDATES",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_incremental_updates,FIX((SI_Long)47L));
    Qg2int_editor_exit_new = STATIC_SYMBOL("EDITOR-EXIT-NEW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_exit_new,FIX((SI_Long)48L));
    Qg2int_editor_apply_new = STATIC_SYMBOL("EDITOR-APPLY-NEW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_apply_new,FIX((SI_Long)49L));
    Qg2int_editor_completions_new = STATIC_SYMBOL("EDITOR-COMPLETIONS-NEW",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_completions_new,FIX((SI_Long)50L));
    Qg2int_editor_clear_output = STATIC_SYMBOL("EDITOR-CLEAR-OUTPUT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_clear_output,FIX((SI_Long)51L));
    Qg2int_editor_append_output = STATIC_SYMBOL("EDITOR-APPEND-OUTPUT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_append_output,FIX((SI_Long)52L));
    Qg2int_editor_hotspot_clicked = STATIC_SYMBOL("EDITOR-HOTSPOT-CLICKED",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_hotspot_clicked,FIX((SI_Long)53L));
    Qg2int_editor_replace_text = STATIC_SYMBOL("EDITOR-REPLACE-TEXT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_replace_text,FIX((SI_Long)54L));
    Qg2int_editor_delete_text = STATIC_SYMBOL("EDITOR-DELETE-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_delete_text,FIX((SI_Long)55L));
    Qg2int_editor_text_saved = STATIC_SYMBOL("EDITOR-TEXT-SAVED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_text_saved,FIX((SI_Long)56L));
    Qg2int_editor_goto_item = STATIC_SYMBOL("EDITOR-GOTO-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_goto_item,FIX((SI_Long)58L));
    Qg2int_editor_beep = STATIC_SYMBOL("EDITOR-BEEP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_beep,FIX((SI_Long)59L));
    Qg2int_editor_custom_toolbar = STATIC_SYMBOL("EDITOR-CUSTOM-TOOLBAR",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_custom_toolbar,FIX((SI_Long)60L));
    Qg2int_editor_undo = STATIC_SYMBOL("EDITOR-UNDO",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_undo,FIX((SI_Long)61L));
    Qg2int_editor_maximum_number_of_undos_to_remember = 
	    STATIC_SYMBOL("EDITOR-MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_maximum_number_of_undos_to_remember,
	    FIX((SI_Long)62L));
    Qg2int_editor_grammar_free_text = 
	    STATIC_SYMBOL("EDITOR-GRAMMAR-FREE-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_grammar_free_text,FIX((SI_Long)0L));
    Qg2int_editor_grammar_procedureslrule = 
	    STATIC_SYMBOL("EDITOR-GRAMMAR-PROCEDURE/RULE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_grammar_procedureslrule,FIX((SI_Long)1L));
    Qg2int_editor_style_normal = STATIC_SYMBOL("EDITOR-STYLE-NORMAL",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_style_normal,FIX((SI_Long)0L));
    Qg2int_editor_style_category = STATIC_SYMBOL("EDITOR-STYLE-CATEGORY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_style_category,FIX((SI_Long)1L));
    Qg2int_editor_style_completion = 
	    STATIC_SYMBOL("EDITOR-STYLE-COMPLETION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_style_completion,FIX((SI_Long)2L));
    Qg2int_editor_options_single_line_comments = 
	    STATIC_SYMBOL("EDITOR-OPTIONS-SINGLE-LINE-COMMENTS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_options_single_line_comments,
	    FIX((SI_Long)1L));
    Qg2int_editor_options_single_line_editor = 
	    STATIC_SYMBOL("EDITOR-OPTIONS-SINGLE-LINE-EDITOR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_options_single_line_editor,
	    FIX((SI_Long)2L));
    Qg2int_editor_options_query_on_close = 
	    STATIC_SYMBOL("EDITOR-OPTIONS-QUERY-ON-CLOSE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_editor_options_query_on_close,FIX((SI_Long)4L));
    Qg2int_black_threshold_in_color_intensity = 
	    STATIC_SYMBOL("BLACK-THRESHOLD-IN-COLOR-INTENSITY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_black_threshold_in_color_intensity,
	    FIX((SI_Long)128L));
    Qg2int_number_of_bits_of_gray_in_the_extended_gray_palette = 
	    STATIC_SYMBOL("NUMBER-OF-BITS-OF-GRAY-IN-THE-EXTENDED-GRAY-PALETTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_number_of_bits_of_gray_in_the_extended_gray_palette,
	    FIX((SI_Long)6L));
    Qg2int_free_bits_per_icp_byte = STATIC_SYMBOL("FREE-BITS-PER-ICP-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_free_bits_per_icp_byte,FIX((SI_Long)15L));
    Qg2int_maximum_background_tile_area = 
	    STATIC_SYMBOL("MAXIMUM-BACKGROUND-TILE-AREA",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_background_tile_area,FIX((SI_Long)16384L));
    Qg2int_maximum_size_of_category_set_as_list = 
	    STATIC_SYMBOL("MAXIMUM-SIZE-OF-CATEGORY-SET-AS-LIST",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_size_of_category_set_as_list,
	    FIX((SI_Long)8L));
    Qg2int_max_instance_rule_chaining = 
	    STATIC_SYMBOL("MAX-INSTANCE-RULE-CHAINING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_max_instance_rule_chaining,FIX((SI_Long)512L));
    Qg2int_default_reduction = STATIC_SYMBOL("DEFAULT-REDUCTION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_default_reduction,FIX((SI_Long)1L));
    Qg2int_max_number_of_regexps_to_cache = 
	    STATIC_SYMBOL("MAX-NUMBER-OF-REGEXPS-TO-CACHE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_max_number_of_regexps_to_cache,FIX((SI_Long)25L));
    Qg2int_max_number_of_lexing_tables_to_cache = 
	    STATIC_SYMBOL("MAX-NUMBER-OF-LEXING-TABLES-TO-CACHE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_max_number_of_lexing_tables_to_cache,
	    FIX((SI_Long)100L));
    Qg2int_maximum_number_of_generic_methods = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-GENERIC-METHODS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_number_of_generic_methods,
	    FIX((SI_Long)57L));
    Qg2int_old_mask_for_saved_frame_flags = 
	    STATIC_SYMBOL("OLD-MASK-FOR-SAVED-FRAME-FLAGS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_old_mask_for_saved_frame_flags,
	    FIX((SI_Long)7531546L));
    Qg2int_use_full_size_of_with_output_wide_string_cutoff = 
	    STATIC_SYMBOL("USE-FULL-SIZE-OF-WITH-OUTPUT-WIDE-STRING-CUTOFF",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_use_full_size_of_with_output_wide_string_cutoff,
	    FIX((SI_Long)256L));
    Qg2int_maximum_length_of_menu_of_names = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-OF-MENU-OF-NAMES",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_length_of_menu_of_names,
	    FIX((SI_Long)10000L));
    Qg2int_minimum_image_plane_serial_number = 
	    STATIC_SYMBOL("MINIMUM-IMAGE-PLANE-SERIAL-NUMBER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_minimum_image_plane_serial_number,
	    FIX((SI_Long)-8388608L));
    Qg2int_maximum_image_plane_serial_number = 
	    STATIC_SYMBOL("MAXIMUM-IMAGE-PLANE-SERIAL-NUMBER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_image_plane_serial_number,
	    FIX((SI_Long)8388608L));
    Qg2int_assumed_standard_image_plane_border_width = 
	    STATIC_SYMBOL("ASSUMED-STANDARD-IMAGE-PLANE-BORDER-WIDTH",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_assumed_standard_image_plane_border_width,
	    FIX((SI_Long)2L));
    Qg2int_warning_shift = STATIC_SYMBOL("WARNING-SHIFT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_warning_shift,FIX((SI_Long)0L));
    Qg2int_tracing_shift = STATIC_SYMBOL("TRACING-SHIFT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tracing_shift,FIX((SI_Long)4L));
    Qg2int_breakpoint_shift = STATIC_SYMBOL("BREAKPOINT-SHIFT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_breakpoint_shift,FIX((SI_Long)8L));
    Qg2int_source_stepping_shift = STATIC_SYMBOL("SOURCE-STEPPING-SHIFT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_source_stepping_shift,FIX((SI_Long)12L));
    Qg2int_message_field_mask = STATIC_SYMBOL("MESSAGE-FIELD-MASK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_message_field_mask,FIX((SI_Long)15L));
    Qg2int_default_number_of_renderings_for_bulk_delete = 
	    STATIC_SYMBOL("DEFAULT-NUMBER-OF-RENDERINGS-FOR-BULK-DELETE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_default_number_of_renderings_for_bulk_delete,
	    FIX((SI_Long)10L));
    Qg2int_default_maximum_renderings_for_class = 
	    STATIC_SYMBOL("DEFAULT-MAXIMUM-RENDERINGS-FOR-CLASS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_default_maximum_renderings_for_class,
	    FIX((SI_Long)200L));
    Qg2int_max_subblock_count_with_pop_up_virtual_attributes_table = 
	    STATIC_SYMBOL("MAX-SUBBLOCK-COUNT-WITH-POP-UP-VIRTUAL-ATTRIBUTES-TABLE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_max_subblock_count_with_pop_up_virtual_attributes_table,
	    FIX((SI_Long)3L));
    Qg2int_mb_ok = STATIC_SYMBOL("MB-OK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mb_ok,FIX((SI_Long)0L));
    Qg2int_mb_okcancel = STATIC_SYMBOL("MB-OKCANCEL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mb_okcancel,FIX((SI_Long)1L));
    Qg2int_mb_abortretryignore = STATIC_SYMBOL("MB-ABORTRETRYIGNORE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_mb_abortretryignore,FIX((SI_Long)2L));
    Qg2int_mb_yesnocancel = STATIC_SYMBOL("MB-YESNOCANCEL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mb_yesnocancel,FIX((SI_Long)3L));
    Qg2int_mb_yesno = STATIC_SYMBOL("MB-YESNO",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mb_yesno,FIX((SI_Long)4L));
    Qg2int_mb_retrycancel = STATIC_SYMBOL("MB-RETRYCANCEL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mb_retrycancel,FIX((SI_Long)5L));
    Qg2int_mb_help = STATIC_SYMBOL("MB-HELP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mb_help,FIX((SI_Long)16384L));
    Qg2int_dlg_icon_question = STATIC_SYMBOL("DLG-ICON-QUESTION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dlg_icon_question,FIX((SI_Long)0L));
    Qg2int_dlg_icon_information = STATIC_SYMBOL("DLG-ICON-INFORMATION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_dlg_icon_information,FIX((SI_Long)1L));
    Qg2int_dlg_icon_warning = STATIC_SYMBOL("DLG-ICON-WARNING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dlg_icon_warning,FIX((SI_Long)2L));
    Qg2int_dlg_icon_error = STATIC_SYMBOL("DLG-ICON-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dlg_icon_error,FIX((SI_Long)3L));
    Qg2int_maximum_number_of_characters_in_pathname = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-CHARACTERS-IN-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_number_of_characters_in_pathname,
	    FIX((SI_Long)512L));
    Qg2int_cd_add_children = STATIC_SYMBOL("CD-ADD-CHILDREN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_cd_add_children,FIX((SI_Long)1L));
    Qg2int_cd_refresh = STATIC_SYMBOL("CD-REFRESH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_cd_refresh,FIX((SI_Long)3L));
    Qg2int_debugger_dialog_cancel = STATIC_SYMBOL("DEBUGGER-DIALOG-CANCEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_debugger_dialog_cancel,FIX((SI_Long)2L));
    Qg2int_debugger_source_stepping_flag = 
	    STATIC_SYMBOL("DEBUGGER-SOURCE-STEPPING-FLAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_debugger_source_stepping_flag,FIX((SI_Long)256L));
    Qg2int_tw_initiated_update = STATIC_SYMBOL("TW-INITIATED-UPDATE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tw_initiated_update,FIX((SI_Long)1L));
    Qg2int_g2_initiated_update = STATIC_SYMBOL("G2-INITIATED-UPDATE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_initiated_update,FIX((SI_Long)2L));
    Qg2int_multi_update_begin = STATIC_SYMBOL("MULTI-UPDATE-BEGIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_multi_update_begin,FIX((SI_Long)4L));
    Qg2int_multi_update_continue = STATIC_SYMBOL("MULTI-UPDATE-CONTINUE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_multi_update_continue,FIX((SI_Long)8L));
    Qg2int_multi_update_finish = STATIC_SYMBOL("MULTI-UPDATE-FINISH",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_multi_update_finish,FIX((SI_Long)16L));
    Qg2int_focus_changed_update = STATIC_SYMBOL("FOCUS-CHANGED-UPDATE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_focus_changed_update,FIX((SI_Long)32L));
    Qg2int_tw_multi_update_begin = STATIC_SYMBOL("TW-MULTI-UPDATE-BEGIN",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tw_multi_update_begin,FIX((SI_Long)5L));
    Qg2int_tw_multi_update_continue = 
	    STATIC_SYMBOL("TW-MULTI-UPDATE-CONTINUE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tw_multi_update_continue,FIX((SI_Long)9L));
    Qg2int_tw_multi_update_finish = STATIC_SYMBOL("TW-MULTI-UPDATE-FINISH",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tw_multi_update_finish,FIX((SI_Long)17L));
    Qg2int_g2_multi_update_begin = STATIC_SYMBOL("G2-MULTI-UPDATE-BEGIN",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_multi_update_begin,FIX((SI_Long)6L));
    Qg2int_g2_multi_update_continue = 
	    STATIC_SYMBOL("G2-MULTI-UPDATE-CONTINUE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_multi_update_continue,FIX((SI_Long)10L));
    Qg2int_g2_multi_update_finish = STATIC_SYMBOL("G2-MULTI-UPDATE-FINISH",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_multi_update_finish,FIX((SI_Long)18L));
    Qg2int_g2_dialog_user_gesture = STATIC_SYMBOL("G2-DIALOG-USER-GESTURE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_dialog_user_gesture,FIX((SI_Long)1L));
    Qg2int_g2_send_wsv_address = STATIC_SYMBOL("G2-SEND-WSV-ADDRESS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_send_wsv_address,FIX((SI_Long)8L));
    Qg2int_dialog_response_unspecified = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-UNSPECIFIED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_unspecified,FIX((SI_Long)-1L));
    Qg2int_dialog_response_no_action = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-NO-ACTION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_no_action,FIX((SI_Long)0L));
    Qg2int_dialog_response_close = STATIC_SYMBOL("DIALOG-RESPONSE-CLOSE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_close,FIX((SI_Long)1L));
    Qg2int_dialog_response_apply = STATIC_SYMBOL("DIALOG-RESPONSE-APPLY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_apply,FIX((SI_Long)2L));
    Qg2int_dialog_response_respond = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-RESPOND",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_respond,FIX((SI_Long)4L));
    Qg2int_dialog_response_send_all_data = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-SEND-ALL-DATA",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_send_all_data,FIX((SI_Long)8L));
    Qg2int_dialog_response_dont_invoke_callback = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-DONT-INVOKE-CALLBACK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_dont_invoke_callback,
	    FIX((SI_Long)16L));
    Qg2int_dialog_response_cancel = STATIC_SYMBOL("DIALOG-RESPONSE-CANCEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_cancel,FIX((SI_Long)1L));
    Qg2int_dialog_response_ok = STATIC_SYMBOL("DIALOG-RESPONSE-OK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_ok,FIX((SI_Long)3L));
    Qg2int_dialog_response_just_respond = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-JUST-RESPOND",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_just_respond,FIX((SI_Long)4L));
    Qg2int_dialog_response_respond_and_ok = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-RESPOND-AND-OK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_respond_and_ok,FIX((SI_Long)7L));
    Qg2int_dialog_response_respond_all = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-RESPOND-ALL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_respond_all,FIX((SI_Long)12L));
    Qg2int_dialog_response_respond_all_and_ok = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-RESPOND-ALL-AND-OK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_respond_all_and_ok,
	    FIX((SI_Long)15L));
    Qg2int_dialog_response_cancel_without_callback = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-CANCEL-WITHOUT-CALLBACK",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_cancel_without_callback,
	    FIX((SI_Long)17L));
    Qg2int_dialog_response_client_side_problem = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-CLIENT-SIDE-PROBLEM",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_response_client_side_problem,
	    FIX((SI_Long)32L));
    Qg2int_dialog_is_modal = STATIC_SYMBOL("DIALOG-IS-MODAL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_is_modal,FIX((SI_Long)1L));
    Qg2int_dialog_is_modeless = STATIC_SYMBOL("DIALOG-IS-MODELESS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_is_modeless,FIX((SI_Long)2L));
    Qg2int_dialog_is_mdi_child = STATIC_SYMBOL("DIALOG-IS-MDI-CHILD",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_is_mdi_child,FIX((SI_Long)4L));
    Qg2int_dock_code_top = STATIC_SYMBOL("DOCK-CODE-TOP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dock_code_top,FIX((SI_Long)1L));
    Qg2int_dock_code_bottom = STATIC_SYMBOL("DOCK-CODE-BOTTOM",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dock_code_bottom,FIX((SI_Long)2L));
    Qg2int_dock_code_left = STATIC_SYMBOL("DOCK-CODE-LEFT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dock_code_left,FIX((SI_Long)3L));
    Qg2int_dock_code_right = STATIC_SYMBOL("DOCK-CODE-RIGHT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dock_code_right,FIX((SI_Long)4L));
    Qg2int_dock_code_float = STATIC_SYMBOL("DOCK-CODE-FLOAT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dock_code_float,FIX((SI_Long)5L));
    Qg2int_dock_code_within = STATIC_SYMBOL("DOCK-CODE-WITHIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dock_code_within,FIX((SI_Long)6L));
    Qg2int_dock_code_mdi_child = STATIC_SYMBOL("DOCK-CODE-MDI-CHILD",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_dock_code_mdi_child,FIX((SI_Long)7L));
    Qg2int_dock_code_top_level = STATIC_SYMBOL("DOCK-CODE-TOP-LEVEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_dock_code_top_level,FIX((SI_Long)8L));
    Qg2int_dock_code_embedded = STATIC_SYMBOL("DOCK-CODE-EMBEDDED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dock_code_embedded,FIX((SI_Long)9L));
    Qg2int_handle_for_unsuccessful_query = 
	    STATIC_SYMBOL("HANDLE-FOR-UNSUCCESSFUL-QUERY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_handle_for_unsuccessful_query,FIX((SI_Long)-1L));
    Qg2int_hh_display_envar_topic = STATIC_SYMBOL("HH-DISPLAY-ENVAR-TOPIC",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_display_envar_topic,FIX((SI_Long)128L));
    Qg2int_logbook_message_type_error = 
	    STATIC_SYMBOL("LOGBOOK-MESSAGE-TYPE-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_logbook_message_type_error,FIX((SI_Long)1L));
    Qg2int_logbook_message_type_warning = 
	    STATIC_SYMBOL("LOGBOOK-MESSAGE-TYPE-WARNING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_logbook_message_type_warning,FIX((SI_Long)2L));
    Qg2int_nms_stock_command_min_id = 
	    STATIC_SYMBOL("NMS-STOCK-COMMAND-MIN-ID",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nms_stock_command_min_id,FIX((SI_Long)1001L));
    Qg2int_nms_no_choice = STATIC_SYMBOL("NMS-NO-CHOICE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nms_no_choice,FIX((SI_Long)1500L));
    Qg2int_codejock_reserved_command_ids = 
	    STATIC_SYMBOL("CODEJOCK-RESERVED-COMMAND-IDS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_codejock_reserved_command_ids,
	    G2int_codejock_reserved_command_ids);
    list_constant = STATIC_CONS(FIX((SI_Long)9300L),FIX((SI_Long)9599L));
    SET_SYMBOL_VALUE(Qg2int_codejock_reserved_command_ids,list_constant);
    Qg2int_nms_handle_gap_low = STATIC_SYMBOL("NMS-HANDLE-GAP-LOW",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_nms_handle_gap_low,
	    G2int_nms_handle_gap_low);
    SET_SYMBOL_VALUE(Qg2int_nms_handle_gap_low,
	    minus(CAR(G2int_codejock_reserved_command_ids),
	    G2int_nms_no_choice));
    Qg2int_nms_handle_gap_high = STATIC_SYMBOL("NMS-HANDLE-GAP-HIGH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_nms_handle_gap_high,
	    G2int_nms_handle_gap_high);
    SET_SYMBOL_VALUE(Qg2int_nms_handle_gap_high,
	    minus(CDR(G2int_codejock_reserved_command_ids),
	    G2int_nms_no_choice));
    Qg2int_nmsc_show = STATIC_SYMBOL("NMSC-SHOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nmsc_show,FIX((SI_Long)1L));
    Qg2int_nmsc_hide = STATIC_SYMBOL("NMSC-HIDE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nmsc_hide,FIX((SI_Long)2L));
    Qg2int_nmsc_setcursel = STATIC_SYMBOL("NMSC-SETCURSEL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nmsc_setcursel,FIX((SI_Long)3L));
    Qg2int_nmsc_settext = STATIC_SYMBOL("NMSC-SETTEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nmsc_settext,FIX((SI_Long)4L));
    Qg2int_nmsc_addtext = STATIC_SYMBOL("NMSC-ADDTEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nmsc_addtext,FIX((SI_Long)5L));
    Qg2int_nmsc_deletetext = STATIC_SYMBOL("NMSC-DELETETEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nmsc_deletetext,FIX((SI_Long)6L));
    Qg2int_sb_hide = STATIC_SYMBOL("SB-HIDE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_hide,FIX((SI_Long)0L));
    Qg2int_sb_show = STATIC_SYMBOL("SB-SHOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_show,FIX((SI_Long)1L));
    Qg2int_sb_text = STATIC_SYMBOL("SB-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_text,FIX((SI_Long)2L));
    Qg2int_sb_reset = STATIC_SYMBOL("SB-RESET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_reset,FIX((SI_Long)3L));
    Qg2int_sb_minheight = STATIC_SYMBOL("SB-MINHEIGHT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_minheight,FIX((SI_Long)4L));
    Qg2int_sb_update = STATIC_SYMBOL("SB-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_update,FIX((SI_Long)5L));
    Qg2int_sb_add_pane = STATIC_SYMBOL("SB-ADD-PANE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_add_pane,FIX((SI_Long)6L));
    Qg2int_sb_remove_pane = STATIC_SYMBOL("SB-REMOVE-PANE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_remove_pane,FIX((SI_Long)7L));
    Qg2int_sb_pane_text = STATIC_SYMBOL("SB-PANE-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_pane_text,FIX((SI_Long)8L));
    Qg2int_sb_pane_width = STATIC_SYMBOL("SB-PANE-WIDTH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_pane_width,FIX((SI_Long)9L));
    Qg2int_sb_pane_visible = STATIC_SYMBOL("SB-PANE-VISIBLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_pane_visible,FIX((SI_Long)10L));
    Qg2int_sb_pane_foreground = STATIC_SYMBOL("SB-PANE-FOREGROUND",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_pane_foreground,FIX((SI_Long)11L));
    Qg2int_sb_pane_background = STATIC_SYMBOL("SB-PANE-BACKGROUND",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_pane_background,FIX((SI_Long)12L));
    Qg2int_sb_pane_icon = STATIC_SYMBOL("SB-PANE-ICON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_pane_icon,FIX((SI_Long)13L));
    Qg2int_sb_pane_alignment = STATIC_SYMBOL("SB-PANE-ALIGNMENT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_pane_alignment,FIX((SI_Long)14L));
    Qg2int_sb_pane_tooltip = STATIC_SYMBOL("SB-PANE-TOOLTIP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_pane_tooltip,FIX((SI_Long)15L));
    Qg2int_sb_pane_enabled = STATIC_SYMBOL("SB-PANE-ENABLED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_pane_enabled,FIX((SI_Long)16L));
    Qg2int_sb_pane_borders = STATIC_SYMBOL("SB-PANE-BORDERS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sb_pane_borders,FIX((SI_Long)17L));
    Qg2int_pane_destroy = STATIC_SYMBOL("PANE-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_destroy,FIX((SI_Long)2L));
    Qg2int_pane_hide = STATIC_SYMBOL("PANE-HIDE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_hide,FIX((SI_Long)3L));
    Qg2int_pane_select = STATIC_SYMBOL("PANE-SELECT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_select,FIX((SI_Long)4L));
    Qg2int_pane_float = STATIC_SYMBOL("PANE-FLOAT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_float,FIX((SI_Long)5L));
    Qg2int_pane_dock = STATIC_SYMBOL("PANE-DOCK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_dock,FIX((SI_Long)6L));
    Qg2int_pane_show = STATIC_SYMBOL("PANE-SHOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_show,FIX((SI_Long)7L));
    Qg2int_pane_set_title = STATIC_SYMBOL("PANE-SET-TITLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_set_title,FIX((SI_Long)8L));
    Qg2int_pane_set_icon = STATIC_SYMBOL("PANE-SET-ICON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_set_icon,FIX((SI_Long)9L));
    Qg2int_pane_close = STATIC_SYMBOL("PANE-CLOSE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_close,FIX((SI_Long)10L));
    Qg2int_pane_redock = STATIC_SYMBOL("PANE-REDOCK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_redock,FIX((SI_Long)11L));
    Qg2int_pane_toggle_docking = STATIC_SYMBOL("PANE-TOGGLE-DOCKING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_toggle_docking,FIX((SI_Long)12L));
    Qg2int_pane_fill = STATIC_SYMBOL("PANE-FILL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_fill,FIX((SI_Long)13L));
    Qg2int_pane_set_closeable = STATIC_SYMBOL("PANE-SET-CLOSEABLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_set_closeable,FIX((SI_Long)101L));
    Qg2int_pane_set_autohideable = STATIC_SYMBOL("PANE-SET-AUTOHIDEABLE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_set_autohideable,FIX((SI_Long)102L));
    Qg2int_pane_set_floatable = STATIC_SYMBOL("PANE-SET-FLOATABLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_set_floatable,FIX((SI_Long)103L));
    Qg2int_pane_set_draggable = STATIC_SYMBOL("PANE-SET-DRAGGABLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_set_draggable,FIX((SI_Long)104L));
    Qg2int_pane_set_visible_caption = 
	    STATIC_SYMBOL("PANE-SET-VISIBLE-CAPTION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_set_visible_caption,FIX((SI_Long)105L));
    Qg2int_pane_set_close_action = STATIC_SYMBOL("PANE-SET-CLOSE-ACTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_pane_set_close_action,FIX((SI_Long)106L));
    Qg2int_tree_view_destroy = STATIC_SYMBOL("TREE-VIEW-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_destroy,FIX((SI_Long)6L));
    Qg2int_tree_view_insert_item = STATIC_SYMBOL("TREE-VIEW-INSERT-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_insert_item,FIX((SI_Long)10L));
    Qg2int_tree_view_clear = STATIC_SYMBOL("TREE-VIEW-CLEAR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_clear,FIX((SI_Long)11L));
    Qg2int_tree_view_set_indent = STATIC_SYMBOL("TREE-VIEW-SET-INDENT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_indent,FIX((SI_Long)12L));
    Qg2int_tree_view_set_item_height = 
	    STATIC_SYMBOL("TREE-VIEW-SET-ITEM-HEIGHT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_item_height,FIX((SI_Long)13L));
    Qg2int_tree_view_set_bgcolor = STATIC_SYMBOL("TREE-VIEW-SET-BGCOLOR",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_bgcolor,FIX((SI_Long)14L));
    Qg2int_tree_view_set_text_color = 
	    STATIC_SYMBOL("TREE-VIEW-SET-TEXT-COLOR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_text_color,FIX((SI_Long)15L));
    Qg2int_tree_view_set_insert_mark_color = 
	    STATIC_SYMBOL("TREE-VIEW-SET-INSERT-MARK-COLOR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_insert_mark_color,FIX((SI_Long)16L));
    Qg2int_tree_view_select_item_by_name = 
	    STATIC_SYMBOL("TREE-VIEW-SELECT-ITEM-BY-NAME",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_select_item_by_name,FIX((SI_Long)17L));
    Qg2int_tree_view_ensure_visible = 
	    STATIC_SYMBOL("TREE-VIEW-ENSURE-VISIBLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_ensure_visible,FIX((SI_Long)18L));
    Qg2int_tree_view_scroll_to = STATIC_SYMBOL("TREE-VIEW-SCROLL-TO",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_scroll_to,FIX((SI_Long)19L));
    Qg2int_tree_view_set_insert_mark = 
	    STATIC_SYMBOL("TREE-VIEW-SET-INSERT-MARK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_insert_mark,FIX((SI_Long)20L));
    Qg2int_tree_view_edit_item = STATIC_SYMBOL("TREE-VIEW-EDIT-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_edit_item,FIX((SI_Long)21L));
    Qg2int_tree_view_expand_item = STATIC_SYMBOL("TREE-VIEW-EXPAND-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_expand_item,FIX((SI_Long)22L));
    Qg2int_tree_view_collapse_item = 
	    STATIC_SYMBOL("TREE-VIEW-COLLAPSE-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_collapse_item,FIX((SI_Long)23L));
    Qg2int_tree_view_select_item = STATIC_SYMBOL("TREE-VIEW-SELECT-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_select_item,FIX((SI_Long)24L));
    Qg2int_tree_view_set_item_tooltip = 
	    STATIC_SYMBOL("TREE-VIEW-SET-ITEM-TOOLTIP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_item_tooltip,FIX((SI_Long)25L));
    Qg2int_tree_view_set_item_bold = 
	    STATIC_SYMBOL("TREE-VIEW-SET-ITEM-BOLD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_item_bold,FIX((SI_Long)26L));
    Qg2int_tree_view_set_item_label = 
	    STATIC_SYMBOL("TREE-VIEW-SET-ITEM-LABEL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_item_label,FIX((SI_Long)27L));
    Qg2int_tree_view_set_item_icons = 
	    STATIC_SYMBOL("TREE-VIEW-SET-ITEM-ICONS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_item_icons,FIX((SI_Long)28L));
    Qg2int_tree_view_set_item_check = 
	    STATIC_SYMBOL("TREE-VIEW-SET-ITEM-CHECK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_item_check,FIX((SI_Long)29L));
    Qg2int_tree_view_delete_item = STATIC_SYMBOL("TREE-VIEW-DELETE-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_delete_item,FIX((SI_Long)30L));
    Qg2int_tree_view_toggle_item = STATIC_SYMBOL("TREE-VIEW-TOGGLE-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_toggle_item,FIX((SI_Long)31L));
    Qg2int_tree_view_set_right_click_selects_node = 
	    STATIC_SYMBOL("TREE-VIEW-SET-RIGHT-CLICK-SELECTS-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_set_right_click_selects_node,
	    FIX((SI_Long)32L));
    Qg2int_tree_view_expand_all = STATIC_SYMBOL("TREE-VIEW-EXPAND-ALL",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_expand_all,FIX((SI_Long)33L));
    Qg2int_tree_view_collapse_all = STATIC_SYMBOL("TREE-VIEW-COLLAPSE-ALL",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_collapse_all,FIX((SI_Long)34L));
    Qg2int_tree_view_redraw = STATIC_SYMBOL("TREE-VIEW-REDRAW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tree_view_redraw,FIX((SI_Long)35L));
    Qg2int_tvf_children = STATIC_SYMBOL("TVF-CHILDREN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tvf_children,FIX((SI_Long)1L));
    Qg2int_tvf_bold = STATIC_SYMBOL("TVF-BOLD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tvf_bold,FIX((SI_Long)2L));
    Qg2int_tvf_expand = STATIC_SYMBOL("TVF-EXPAND",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tvf_expand,FIX((SI_Long)4L));
    Qg2int_tvf_check = STATIC_SYMBOL("TVF-CHECK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tvf_check,FIX((SI_Long)8L));
    Qg2int_tvf_first = STATIC_SYMBOL("TVF-FIRST",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tvf_first,FIX((SI_Long)16L));
    Qg2int_tvf_after = STATIC_SYMBOL("TVF-AFTER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tvf_after,FIX((SI_Long)32L));
    Qg2int_tvf_insert_mark = STATIC_SYMBOL("TVF-INSERT-MARK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tvf_insert_mark,FIX((SI_Long)64L));
    Qg2int_tvf_reclaim_label = STATIC_SYMBOL("TVF-RECLAIM-LABEL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tvf_reclaim_label,FIX((SI_Long)128L));
    Qg2int_html_view_destroy = STATIC_SYMBOL("HTML-VIEW-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_html_view_destroy,FIX((SI_Long)2L));
    Qg2int_html_view_back = STATIC_SYMBOL("HTML-VIEW-BACK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_html_view_back,FIX((SI_Long)3L));
    Qg2int_html_view_forward = STATIC_SYMBOL("HTML-VIEW-FORWARD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_html_view_forward,FIX((SI_Long)4L));
    Qg2int_html_view_home = STATIC_SYMBOL("HTML-VIEW-HOME",AB_package);
    SET_SYMBOL_VALUE(Qg2int_html_view_home,FIX((SI_Long)5L));
    Qg2int_html_view_stop = STATIC_SYMBOL("HTML-VIEW-STOP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_html_view_stop,FIX((SI_Long)6L));
    Qg2int_html_view_refresh = STATIC_SYMBOL("HTML-VIEW-REFRESH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_html_view_refresh,FIX((SI_Long)7L));
    Qg2int_html_view_goto = STATIC_SYMBOL("HTML-VIEW-GOTO",AB_package);
    SET_SYMBOL_VALUE(Qg2int_html_view_goto,FIX((SI_Long)8L));
    Qg2int_html_view_print = STATIC_SYMBOL("HTML-VIEW-PRINT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_html_view_print,FIX((SI_Long)9L));
    Qg2int_shortcut_bar_style_outlook = 
	    STATIC_SYMBOL("SHORTCUT-BAR-STYLE-OUTLOOK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_style_outlook,FIX((SI_Long)1L));
    Qg2int_shortcut_bar_style_outlook_2003 = 
	    STATIC_SYMBOL("SHORTCUT-BAR-STYLE-OUTLOOK-2003",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_style_outlook_2003,FIX((SI_Long)2L));
    Qg2int_shortcut_bar_destroy = STATIC_SYMBOL("SHORTCUT-BAR-DESTROY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_destroy,FIX((SI_Long)6L));
    Qg2int_shortcut_bar_add_folder = 
	    STATIC_SYMBOL("SHORTCUT-BAR-ADD-FOLDER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_add_folder,FIX((SI_Long)10L));
    Qg2int_shortcut_bar_add_item = STATIC_SYMBOL("SHORTCUT-BAR-ADD-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_add_item,FIX((SI_Long)11L));
    Qg2int_shortcut_bar_clear = STATIC_SYMBOL("SHORTCUT-BAR-CLEAR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_clear,FIX((SI_Long)12L));
    Qg2int_shortcut_bar_select_folder = 
	    STATIC_SYMBOL("SHORTCUT-BAR-SELECT-FOLDER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_select_folder,FIX((SI_Long)13L));
    Qg2int_shortcut_bar_enable_folder = 
	    STATIC_SYMBOL("SHORTCUT-BAR-ENABLE-FOLDER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_enable_folder,FIX((SI_Long)14L));
    Qg2int_shortcut_bar_disable_folder = 
	    STATIC_SYMBOL("SHORTCUT-BAR-DISABLE-FOLDER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_disable_folder,FIX((SI_Long)15L));
    Qg2int_shortcut_bar_select_item = 
	    STATIC_SYMBOL("SHORTCUT-BAR-SELECT-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_select_item,FIX((SI_Long)16L));
    Qg2int_shortcut_bar_enable_item = 
	    STATIC_SYMBOL("SHORTCUT-BAR-ENABLE-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_enable_item,FIX((SI_Long)17L));
    Qg2int_shortcut_bar_disable_item = 
	    STATIC_SYMBOL("SHORTCUT-BAR-DISABLE-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_disable_item,FIX((SI_Long)18L));
    Qg2int_shortcut_bar_small_icons = 
	    STATIC_SYMBOL("SHORTCUT-BAR-SMALL-ICONS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_small_icons,FIX((SI_Long)19L));
    Qg2int_shortcut_bar_large_icons = 
	    STATIC_SYMBOL("SHORTCUT-BAR-LARGE-ICONS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_large_icons,FIX((SI_Long)20L));
    Qg2int_shortcut_bar_background_color = 
	    STATIC_SYMBOL("SHORTCUT-BAR-BACKGROUND-COLOR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_background_color,FIX((SI_Long)21L));
    Qg2int_shortcut_bar_foreground_color = 
	    STATIC_SYMBOL("SHORTCUT-BAR-FOREGROUND-COLOR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shortcut_bar_foreground_color,FIX((SI_Long)22L));
    Qg2int_obs_xt_smallicon = STATIC_SYMBOL("OBS-XT-SMALLICON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_obs_xt_smallicon,FIX((SI_Long)1L));
    Qg2int_obs_xt_largeicon = STATIC_SYMBOL("OBS-XT-LARGEICON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_obs_xt_largeicon,FIX((SI_Long)2L));
    Qg2int_obs_xt_editgroups = STATIC_SYMBOL("OBS-XT-EDITGROUPS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_obs_xt_editgroups,FIX((SI_Long)4L));
    Qg2int_obs_xt_edititems = STATIC_SYMBOL("OBS-XT-EDITITEMS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_obs_xt_edititems,FIX((SI_Long)8L));
    Qg2int_obs_xt_removegroups = STATIC_SYMBOL("OBS-XT-REMOVEGROUPS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_obs_xt_removegroups,FIX((SI_Long)16L));
    Qg2int_obs_xt_removeitems = STATIC_SYMBOL("OBS-XT-REMOVEITEMS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_obs_xt_removeitems,FIX((SI_Long)32L));
    Qg2int_obs_xt_addgroups = STATIC_SYMBOL("OBS-XT-ADDGROUPS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_obs_xt_addgroups,FIX((SI_Long)64L));
    Qg2int_obs_xt_dragitems = STATIC_SYMBOL("OBS-XT-DRAGITEMS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_obs_xt_dragitems,FIX((SI_Long)128L));
    Qg2int_obs_xt_animation = STATIC_SYMBOL("OBS-XT-ANIMATION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_obs_xt_animation,FIX((SI_Long)256L));
    Qg2int_obs_xt_selhighlight = STATIC_SYMBOL("OBS-XT-SELHIGHLIGHT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_obs_xt_selhighlight,FIX((SI_Long)512L));
    Qg2int_obs_default_style = STATIC_SYMBOL("OBS-DEFAULT-STYLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_obs_default_style,
	    G2int_obs_default_style);
    SET_SYMBOL_VALUE(Qg2int_obs_default_style,logiorn(3,
	    G2int_obs_xt_selhighlight,G2int_obs_xt_animation,
	    G2int_obs_xt_largeicon));
    Qg2int_dlgm_settext = STATIC_SYMBOL("DLGM-SETTEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dlgm_settext,FIX((SI_Long)1L));
    Qg2int_dlgm_addstrings = STATIC_SYMBOL("DLGM-ADDSTRINGS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dlgm_addstrings,FIX((SI_Long)2L));
    Qg2int_dlgm_seticon = STATIC_SYMBOL("DLGM-SETICON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dlgm_seticon,FIX((SI_Long)3L));
    Qg2int_dlgm_check = STATIC_SYMBOL("DLGM-CHECK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dlgm_check,FIX((SI_Long)4L));
    Qg2int_dlgm_sndmsg = STATIC_SYMBOL("DLGM-SNDMSG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dlgm_sndmsg,FIX((SI_Long)5L));
    Qg2int_chart_create = STATIC_SYMBOL("CHART-CREATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_create,FIX((SI_Long)1L));
    Qg2int_chart_destroy = STATIC_SYMBOL("CHART-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_destroy,FIX((SI_Long)2L));
    Qg2int_chart_print = STATIC_SYMBOL("CHART-PRINT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_print,FIX((SI_Long)3L));
    Qg2int_chart_update = STATIC_SYMBOL("CHART-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_update,FIX((SI_Long)4L));
    Qg2int_chart_partial_update = STATIC_SYMBOL("CHART-PARTIAL-UPDATE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_partial_update,FIX((SI_Long)5L));
    Qg2int_chart_copy = STATIC_SYMBOL("CHART-COPY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_copy,FIX((SI_Long)6L));
    Qg2int_chart_export = STATIC_SYMBOL("CHART-EXPORT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_export,FIX((SI_Long)7L));
    Qg2int_chart_format_jpeg = STATIC_SYMBOL("CHART-FORMAT-JPEG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_format_jpeg,FIX((SI_Long)1L));
    Qg2int_chart_format_png = STATIC_SYMBOL("CHART-FORMAT-PNG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_format_png,FIX((SI_Long)2L));
    Qg2int_chart_format_bmp = STATIC_SYMBOL("CHART-FORMAT-BMP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_format_bmp,FIX((SI_Long)3L));
    Qg2int_chart_format_wmf = STATIC_SYMBOL("CHART-FORMAT-WMF",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_format_wmf,FIX((SI_Long)4L));
    Qg2int_chart_format_svg = STATIC_SYMBOL("CHART-FORMAT-SVG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_format_svg,FIX((SI_Long)5L));
    Qg2int_chart_success = STATIC_SYMBOL("CHART-SUCCESS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_success,FIX((SI_Long)0L));
    Qg2int_chart_no_window = STATIC_SYMBOL("CHART-NO-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_chart_no_window,FIX((SI_Long)1L));
    Qg2int_lvcfmt_left = STATIC_SYMBOL("LVCFMT-LEFT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_lvcfmt_left,FIX((SI_Long)0L));
    Qg2int_lvcfmt_right = STATIC_SYMBOL("LVCFMT-RIGHT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_lvcfmt_right,FIX((SI_Long)1L));
    Qg2int_lvcfmt_center = STATIC_SYMBOL("LVCFMT-CENTER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_lvcfmt_center,FIX((SI_Long)2L));
    Qg2int_lvscw_autosize = STATIC_SYMBOL("LVSCW-AUTOSIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_lvscw_autosize,FIX((SI_Long)-1L));
    Qg2int_lvscw_autosize_useheader = 
	    STATIC_SYMBOL("LVSCW-AUTOSIZE-USEHEADER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_lvscw_autosize_useheader,FIX((SI_Long)-2L));
    Qg2int_event_time_mask = STATIC_SYMBOL("EVENT-TIME-MASK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_event_time_mask,FIX((SI_Long)268435455L));
    Qg2int_least_common_multiple_of_stock_line_pattern_lengths = 
	    STATIC_SYMBOL("LEAST-COMMON-MULTIPLE-OF-STOCK-LINE-PATTERN-LENGTHS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_least_common_multiple_of_stock_line_pattern_lengths,
	    G2int_least_common_multiple_of_stock_line_pattern_lengths);
    SET_SYMBOL_VALUE(Qg2int_least_common_multiple_of_stock_line_pattern_lengths,
	    timesn(4,FIX((SI_Long)3L),FIX((SI_Long)4L),FIX((SI_Long)5L),
	    FIX((SI_Long)7L)));
    Qg2int_minimum_minimum_fixnum_scheduling_interval = 
	    STATIC_SYMBOL("MINIMUM-MINIMUM-FIXNUM-SCHEDULING-INTERVAL",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_minimum_minimum_fixnum_scheduling_interval,
	    FIX((SI_Long)2L));
    Qg2int_minimum_minimum_float_scheduling_interval = 
	    STATIC_SYMBOL("MINIMUM-MINIMUM-FLOAT-SCHEDULING-INTERVAL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_minimum_minimum_float_scheduling_interval,
	    G2int_minimum_minimum_float_scheduling_interval);
    float_constant_3 = STATIC_FLOAT(0.002);
    SET_SYMBOL_VALUE(Qg2int_minimum_minimum_float_scheduling_interval,
	    float_constant_3);
    Qg2int_tmask_kka_p_batkanakan = STATIC_SYMBOL("TMASK_KKA_P_BATKANAKAN",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_kka_p_batkanakan,FIX((SI_Long)1L));
    Qg2int_tmask_kka_hensaisyo = STATIC_SYMBOL("TMASK_KKA_HENSAISYO",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_kka_hensaisyo,FIX((SI_Long)2L));
    Qg2int_tmask_kka_gtango = STATIC_SYMBOL("TMASK_KKA_GTANGO",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_kka_gtango,FIX((SI_Long)4L));
    Qg2int_tmask_kka_ghyoki = STATIC_SYMBOL("TMASK_KKA_GHYOKI",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_kka_ghyoki,FIX((SI_Long)8L));
    Qg2int_tmask_kka_gtnum = STATIC_SYMBOL("TMASK_KKA_GTNUM",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_kka_gtnum,FIX((SI_Long)16L));
    Qg2int_tmask_kka_evalbun = STATIC_SYMBOL("TMASK_KKA_EVALBUN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_kka_evalbun,FIX((SI_Long)32L));
    Qg2int_tmask_kka_find_bunpo = STATIC_SYMBOL("TMASK_KKA_FIND_BUNPO",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_kka_find_bunpo,FIX((SI_Long)64L));
    Qg2int_tmask_chkbunpo = STATIC_SYMBOL("TMASK_CHKBUNPO",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_chkbunpo,FIX((SI_Long)128L));
    Qg2int_tmask_chkattr = STATIC_SYMBOL("TMASK_CHKATTR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_chkattr,FIX((SI_Long)256L));
    Qg2int_tmask_kka_g_taigen = STATIC_SYMBOL("TMASK_KKA_G_TAIGEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_kka_g_taigen,FIX((SI_Long)512L));
    Qg2int_tmask_kka_kofind = STATIC_SYMBOL("TMASK_KKA_KOFIND",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_kka_kofind,FIX((SI_Long)1024L));
    Qg2int_tmask_kka_ishouki = STATIC_SYMBOL("TMASK_KKA_ISHOUKI",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tmask_kka_ishouki,FIX((SI_Long)2048L));
    Qg2int_jis_space_character_code = 
	    STATIC_SYMBOL("JIS-SPACE-CHARACTER-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_space_character_code,FIX((SI_Long)8481L));
    Qg2int_jis_colon_character_code = 
	    STATIC_SYMBOL("JIS-COLON-CHARACTER-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_colon_character_code,FIX((SI_Long)8487L));
    Qg2int_jis_0_digit_character_code = 
	    STATIC_SYMBOL("JIS-0-DIGIT-CHARACTER-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_0_digit_character_code,FIX((SI_Long)9008L));
    Qg2int_jis_letter_a_character_code = 
	    STATIC_SYMBOL("JIS-LETTER-A-CHARACTER-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_letter_a_character_code,FIX((SI_Long)9025L));
    Qg2int_jis_m_dash_character_code = 
	    STATIC_SYMBOL("JIS-M-DASH-CHARACTER-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_jis_m_dash_character_code,FIX((SI_Long)9005L));
    Qg2int_hfep_ks_size = STATIC_SYMBOL("HFEP-KS-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hfep_ks_size,FIX((SI_Long)2390L));
    Qg2int_hfep_none = STATIC_SYMBOL("HFEP-NONE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hfep_none,FIX((SI_Long)0L));
    Qg2int_hfep_go_on = STATIC_SYMBOL("HFEP-GO-ON",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hfep_go_on,FIX((SI_Long)1L));
    Qg2int_hfep_done = STATIC_SYMBOL("HFEP-DONE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hfep_done,FIX((SI_Long)2L));
    Qg2int_hfep_wrong = STATIC_SYMBOL("HFEP-WRONG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hfep_wrong,FIX((SI_Long)3L));
    Qg2int_hfep_error = STATIC_SYMBOL("HFEP-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hfep_error,FIX((SI_Long)4L));
    Qg2int_hfep_null_code = STATIC_SYMBOL("HFEP-NULL-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hfep_null_code,FIX((SI_Long)0L));
    Qg2int_date_month_and_year_of_frame_edit_base_time = 
	    STATIC_SYMBOL("DATE-MONTH-AND-YEAR-OF-FRAME-EDIT-BASE-TIME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_date_month_and_year_of_frame_edit_base_time,
	    G2int_date_month_and_year_of_frame_edit_base_time);
    list_constant_1 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)1L),
	    FIX((SI_Long)9L),FIX((SI_Long)1993L));
    SET_SYMBOL_VALUE(Qg2int_date_month_and_year_of_frame_edit_base_time,
	    list_constant_1);
    Qg2int_frame_edit_base_timestamp = 
	    STATIC_SYMBOL("FRAME-EDIT-BASE-TIMESTAMP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_frame_edit_base_timestamp,FIX((SI_Long)0L));
    Qg2int_additional_time_for_synthetic_paste_event_timestamps = 
	    STATIC_SYMBOL("ADDITIONAL-TIME-FOR-SYNTHETIC-PASTE-EVENT-TIMESTAMPS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_additional_time_for_synthetic_paste_event_timestamps,
	    FIX((SI_Long)13L));
    Qg2int_most_positive_window_coordinate = 
	    STATIC_SYMBOL("MOST-POSITIVE-WINDOW-COORDINATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_most_positive_window_coordinate,
	    FIX((SI_Long)65535L));
    Qg2int_most_negative_window_coordinate = 
	    STATIC_SYMBOL("MOST-NEGATIVE-WINDOW-COORDINATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_most_negative_window_coordinate,
	    FIX((SI_Long)-65535L));
    Qg2int_default_telewindows_upper_margin = 
	    STATIC_SYMBOL("DEFAULT-TELEWINDOWS-UPPER-MARGIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_default_telewindows_upper_margin,
	    FIX((SI_Long)50L));
    Qg2int_default_error_source_line = 
	    STATIC_SYMBOL("DEFAULT-ERROR-SOURCE-LINE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_default_error_source_line,FIX((SI_Long)-1L));
    Qg2int_default_error_source_column = 
	    STATIC_SYMBOL("DEFAULT-ERROR-SOURCE-COLUMN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_default_error_source_column,FIX((SI_Long)-1L));
    Qg2int_g2_array_length_maximum = 
	    STATIC_SYMBOL("G2-ARRAY-LENGTH-MAXIMUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_g2_array_length_maximum,
	    G2int_g2_array_length_maximum);
    SET_SYMBOL_VALUE(Qg2int_g2_array_length_maximum,
	    FIXNUM_MINUS(FIX((SI_Long)524288L),FIX((SI_Long)1024L)));
    Qg2int_history_timestamp_epsilon = 
	    STATIC_SYMBOL("HISTORY-TIMESTAMP-EPSILON",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_history_timestamp_epsilon,
	    G2int_history_timestamp_epsilon);
    float_constant_4 = STATIC_FLOAT(9.0E-7);
    SET_SYMBOL_VALUE(Qg2int_history_timestamp_epsilon,float_constant_4);
    Qg2int_no_history_spec_value = STATIC_SYMBOL("NO-HISTORY-SPEC-VALUE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_no_history_spec_value,FIX((SI_Long)-1L));
    Qg2int_no_resumable_object_index = 
	    STATIC_SYMBOL("NO-RESUMABLE-OBJECT-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_no_resumable_object_index,FIX((SI_Long)-1L));
    Qg2int_default_procedure_evaluation_priority = 
	    STATIC_SYMBOL("DEFAULT-PROCEDURE-EVALUATION-PRIORITY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_default_procedure_evaluation_priority,
	    FIX((SI_Long)6L));
    Qg2int_procedure_can_invalidate_environment_mask = 
	    STATIC_SYMBOL("PROCEDURE-CAN-INVALIDATE-ENVIRONMENT-MASK",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_procedure_can_invalidate_environment_mask,
	    FIX((SI_Long)1L));
    Qg2int_procedure_contains_wait_state_mask = 
	    STATIC_SYMBOL("PROCEDURE-CONTAINS-WAIT-STATE-MASK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_procedure_contains_wait_state_mask,
	    FIX((SI_Long)2L));
    Qg2int_procedure_contains_indirect_procedure_call_mask = 
	    STATIC_SYMBOL("PROCEDURE-CONTAINS-INDIRECT-PROCEDURE-CALL-MASK",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_procedure_contains_indirect_procedure_call_mask,
	    FIX((SI_Long)4L));
    Qg2int_procedure_call_without_validated_environment_mask = 
	    STATIC_SYMBOL("PROCEDURE-CALL-WITHOUT-VALIDATED-ENVIRONMENT-MASK",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_procedure_call_without_validated_environment_mask,
	    FIX((SI_Long)8L));
    Qg2int_procedure_invalidates_environment_union_mask = 
	    STATIC_SYMBOL("PROCEDURE-INVALIDATES-ENVIRONMENT-UNION-MASK",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_procedure_invalidates_environment_union_mask,
	    FIX((SI_Long)15L));
    Qg2int_maximum_length_for_writing_evaluation_values = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-FOR-WRITING-EVALUATION-VALUES",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_length_for_writing_evaluation_values,
	    FIX((SI_Long)300L));
    Qg2int_maximum_number_of_lisp_call_arguments = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-LISP-CALL-ARGUMENTS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_number_of_lisp_call_arguments,
	    FIX((SI_Long)8L));
    Qg2int_maximum_number_of_lisp_call_return_values = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-LISP-CALL-RETURN-VALUES",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_number_of_lisp_call_return_values,
	    FIX((SI_Long)8L));
    Qg2int_initial_change_log_revision_number = 
	    STATIC_SYMBOL("INITIAL-CHANGE-LOG-REVISION-NUMBER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_initial_change_log_revision_number,
	    FIX((SI_Long)0L));
    Qg2int_maximum_painting_action_args = 
	    STATIC_SYMBOL("MAXIMUM-PAINTING-ACTION-ARGS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_painting_action_args,FIX((SI_Long)10L));
    Qg2int_buffered_plot_painting_minimum_ratio = 
	    STATIC_SYMBOL("BUFFERED-PLOT-PAINTING-MINIMUM-RATIO",AB_package);
    SET_SYMBOL_VALUE(Qg2int_buffered_plot_painting_minimum_ratio,
	    FIX((SI_Long)5L));
    Qg2int_fraction_modulus_of_compound_fixnum_simulation_time = 
	    STATIC_SYMBOL("FRACTION-MODULUS-OF-COMPOUND-FIXNUM-SIMULATION-TIME",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_fraction_modulus_of_compound_fixnum_simulation_time,
	    FIX((SI_Long)100000L));
    Qg2int_xml_callback_none = STATIC_SYMBOL("XML-CALLBACK-NONE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_callback_none,FIX((SI_Long)-1L));
    Qg2int_xml_callback_start_document = 
	    STATIC_SYMBOL("XML-CALLBACK-START-DOCUMENT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_callback_start_document,FIX((SI_Long)12L));
    Qg2int_xml_callback_end_document = 
	    STATIC_SYMBOL("XML-CALLBACK-END-DOCUMENT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_callback_end_document,FIX((SI_Long)13L));
    Qg2int_xml_callback_start_element = 
	    STATIC_SYMBOL("XML-CALLBACK-START-ELEMENT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_callback_start_element,FIX((SI_Long)14L));
    Qg2int_xml_callback_end_element = 
	    STATIC_SYMBOL("XML-CALLBACK-END-ELEMENT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_callback_end_element,FIX((SI_Long)15L));
    Qg2int_xml_callback_characters = 
	    STATIC_SYMBOL("XML-CALLBACK-CHARACTERS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_callback_characters,FIX((SI_Long)17L));
    Qg2int_xml_callback_comment = STATIC_SYMBOL("XML-CALLBACK-COMMENT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_callback_comment,FIX((SI_Long)20L));
    Qg2int_xml_callback_warning = STATIC_SYMBOL("XML-CALLBACK-WARNING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_callback_warning,FIX((SI_Long)21L));
    Qg2int_xml_callback_error = STATIC_SYMBOL("XML-CALLBACK-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_callback_error,FIX((SI_Long)22L));
    Qg2int_xml_callback_fatal_error = 
	    STATIC_SYMBOL("XML-CALLBACK-FATAL-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_callback_fatal_error,FIX((SI_Long)23L));
    Qg2int_xml_encoding_length = STATIC_SYMBOL("XML-ENCODING-LENGTH",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_encoding_length,FIX((SI_Long)4L));
    Qg2int_xml_element_node = STATIC_SYMBOL("XML-ELEMENT-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_element_node,FIX((SI_Long)1L));
    Qg2int_xml_attribute_node = STATIC_SYMBOL("XML-ATTRIBUTE-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_attribute_node,FIX((SI_Long)2L));
    Qg2int_xml_text_node = STATIC_SYMBOL("XML-TEXT-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_text_node,FIX((SI_Long)3L));
    Qg2int_xml_cdata_section_node = STATIC_SYMBOL("XML-CDATA-SECTION-NODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_cdata_section_node,FIX((SI_Long)4L));
    Qg2int_xml_entity_reference_node = 
	    STATIC_SYMBOL("XML-ENTITY-REFERENCE-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_entity_reference_node,FIX((SI_Long)5L));
    Qg2int_xml_entity_node = STATIC_SYMBOL("XML-ENTITY-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_entity_node,FIX((SI_Long)6L));
    Qg2int_xml_processing_instruction_node = 
	    STATIC_SYMBOL("XML-PROCESSING-INSTRUCTION-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_processing_instruction_node,FIX((SI_Long)7L));
    Qg2int_xml_comment_node = STATIC_SYMBOL("XML-COMMENT-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_comment_node,FIX((SI_Long)8L));
    Qg2int_xml_document_node = STATIC_SYMBOL("XML-DOCUMENT-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_document_node,FIX((SI_Long)9L));
    Qg2int_xml_document_type_node = STATIC_SYMBOL("XML-DOCUMENT-TYPE-NODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_document_type_node,FIX((SI_Long)10L));
    Qg2int_xml_document_fragment_node = 
	    STATIC_SYMBOL("XML-DOCUMENT-FRAGMENT-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_document_fragment_node,FIX((SI_Long)11L));
    Qg2int_xml_notation_node = STATIC_SYMBOL("XML-NOTATION-NODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_xml_notation_node,FIX((SI_Long)12L));
    Qg2int_maximum_length_for_dom_strings = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-FOR-DOM-STRINGS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_length_for_dom_strings,
	    G2int_maximum_length_for_user_text_strings);
    Qg2int_slot_description_cache_entry_size = 
	    STATIC_SYMBOL("SLOT-DESCRIPTION-CACHE-ENTRY-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_slot_description_cache_entry_size,
	    FIX((SI_Long)4L));
    Qg2int_attribute_value_cache_entry_size = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-CACHE-ENTRY-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_value_cache_entry_size,FIX((SI_Long)3L));
    Qg2int_denotation_element_overhead_slot_count = 
	    STATIC_SYMBOL("DENOTATION-ELEMENT-OVERHEAD-SLOT-COUNT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_denotation_element_overhead_slot_count,
	    FIX((SI_Long)2L));
    Qg2int_maximum_denotation_types = 
	    STATIC_SYMBOL("MAXIMUM-DENOTATION-TYPES",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_denotation_types,FIX((SI_Long)50L));
    Qg2int_maximum_denotation_sequence_elements = 
	    STATIC_SYMBOL("MAXIMUM-DENOTATION-SEQUENCE-ELEMENTS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_denotation_sequence_elements,
	    FIX((SI_Long)50L));
    Qg2int_attribute_particular_code = 
	    STATIC_SYMBOL("ATTRIBUTE-PARTICULAR-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_particular_code,FIX((SI_Long)1L));
    Qg2int_aliased_attribute_particular_code = 
	    STATIC_SYMBOL("ALIASED-ATTRIBUTE-PARTICULAR-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_aliased_attribute_particular_code,
	    FIX((SI_Long)2L));
    Qg2int_element_particular_code = 
	    STATIC_SYMBOL("ELEMENT-PARTICULAR-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_element_particular_code,FIX((SI_Long)3L));
    Qg2int_virtual_attribute_particular_code = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-PARTICULAR-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_virtual_attribute_particular_code,
	    FIX((SI_Long)4L));
    Qg2int_variable_value_particular_code = 
	    STATIC_SYMBOL("VARIABLE-VALUE-PARTICULAR-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_variable_value_particular_code,FIX((SI_Long)5L));
    Qg2int_ten_years = STATIC_SYMBOL("TEN-YEARS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ten_years,FIX((SI_Long)315360000L));
    Qg2int_maximum_connection_dash_length = 
	    STATIC_SYMBOL("MAXIMUM-CONNECTION-DASH-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_connection_dash_length,FIX((SI_Long)127L));
    Qg2int_maximum_connection_dash_count = 
	    STATIC_SYMBOL("MAXIMUM-CONNECTION-DASH-COUNT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_connection_dash_count,FIX((SI_Long)256L));
    Qg2int_attribute_nesting_limit = 
	    STATIC_SYMBOL("ATTRIBUTE-NESTING-LIMIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_nesting_limit,FIX((SI_Long)20L));
    Qg2int_max_icon_size = STATIC_SYMBOL("MAX-ICON-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_max_icon_size,FIX((SI_Long)100000L));
    Qg2int_max_icon_area = STATIC_SYMBOL("MAX-ICON-AREA",AB_package);
    SET_SYMBOL_VALUE(Qg2int_max_icon_area,FIX((SI_Long)2500000L));
    Qg2int_float_format_precision_limit = 
	    STATIC_SYMBOL("FLOAT-FORMAT-PRECISION-LIMIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_float_format_precision_limit,FIX((SI_Long)40L));
    Qg2int_frame_display_workspace_margin = 
	    STATIC_SYMBOL("FRAME-DISPLAY-WORKSPACE-MARGIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_frame_display_workspace_margin,FIX((SI_Long)30L));
    Qg2int_frame_display_vertical_spacing = 
	    STATIC_SYMBOL("FRAME-DISPLAY-VERTICAL-SPACING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_frame_display_vertical_spacing,FIX((SI_Long)10L));
    Qg2int_frame_display_reformat_after_count_deleted = 
	    STATIC_SYMBOL("FRAME-DISPLAY-REFORMAT-AFTER-COUNT-DELETED",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_frame_display_reformat_after_count_deleted,
	    FIX((SI_Long)3L));
    Qg2int_foreign_function_integer_type_tag = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-INTEGER-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_foreign_function_integer_type_tag,
	    FIX((SI_Long)1L));
    Qg2int_foreign_function_real_type_tag = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-REAL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_foreign_function_real_type_tag,FIX((SI_Long)6L));
    Qg2int_foreign_function_symbol_type_tag = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-SYMBOL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_foreign_function_symbol_type_tag,FIX((SI_Long)3L));
    Qg2int_foreign_function_text_type_tag = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-TEXT-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_foreign_function_text_type_tag,FIX((SI_Long)4L));
    Qg2int_largest_known_fixnum_time_units_per_second = 
	    STATIC_SYMBOL("LARGEST-KNOWN-FIXNUM-TIME-UNITS-PER-SECOND",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_largest_known_fixnum_time_units_per_second,
	    FIX((SI_Long)1000L));
    Qg2int_shutdown_context_only_flag_clear = 
	    STATIC_SYMBOL("SHUTDOWN-CONTEXT-ONLY-FLAG-CLEAR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shutdown_context_only_flag_clear,FIX((SI_Long)0L));
    Qg2int_shutdown_context_only_flag_set = 
	    STATIC_SYMBOL("SHUTDOWN-CONTEXT-ONLY-FLAG-SET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shutdown_context_only_flag_set,FIX((SI_Long)1L));
    Qg2int_ffs_unspecified_error = STATIC_SYMBOL("FFS_UNSPECIFIED_ERROR",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ffs_unspecified_error,FIX((SI_Long)1L));
    Qg2int_ffs_connection_open_already = 
	    STATIC_SYMBOL("FFS_CONNECTION_OPEN_ALREADY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ffs_connection_open_already,FIX((SI_Long)2L));
    Qg2int_ffs_signal_caught_during_call = 
	    STATIC_SYMBOL("FFS_SIGNAL_CAUGHT_DURING_CALL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ffs_signal_caught_during_call,FIX((SI_Long)3L));
    Qg2int_ffs_unknown_function = STATIC_SYMBOL("FFS_UNKNOWN_FUNCTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ffs_unknown_function,FIX((SI_Long)4L));
    Qg2int_ffs_unknown_return_type = 
	    STATIC_SYMBOL("FFS_UNKNOWN_RETURN_TYPE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ffs_unknown_return_type,FIX((SI_Long)5L));
    Qg2int_maximum_gfi_output_queue_count = 
	    STATIC_SYMBOL("MAXIMUM-GFI-OUTPUT-QUEUE-COUNT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_gfi_output_queue_count,FIX((SI_Long)100L));
    Qg2int_iterations_for_gsi_temporary_float_processing = 
	    STATIC_SYMBOL("ITERATIONS-FOR-GSI-TEMPORARY-FLOAT-PROCESSING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_iterations_for_gsi_temporary_float_processing,
	    FIX((SI_Long)100L));
    Qg2int_g2ds_null_type_tag = STATIC_SYMBOL("G2DS-NULL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_null_type_tag,FIX((SI_Long)0L));
    Qg2int_g2ds_integer_type_tag = STATIC_SYMBOL("G2DS-INTEGER-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_integer_type_tag,FIX((SI_Long)1L));
    Qg2int_g2ds_float_type_tag = STATIC_SYMBOL("G2DS-FLOAT-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_float_type_tag,FIX((SI_Long)2L));
    Qg2int_g2ds_symbol_type_tag = STATIC_SYMBOL("G2DS-SYMBOL-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_symbol_type_tag,FIX((SI_Long)3L));
    Qg2int_g2ds_string_type_tag = STATIC_SYMBOL("G2DS-STRING-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_string_type_tag,FIX((SI_Long)4L));
    Qg2int_g2ds_list_type_tag = STATIC_SYMBOL("G2DS-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_list_type_tag,FIX((SI_Long)5L));
    Qg2int_g2ds_64bit_float_type_tag = 
	    STATIC_SYMBOL("G2DS-64BIT-FLOAT-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_64bit_float_type_tag,FIX((SI_Long)6L));
    Qg2int_g2ds_dotted_list_type_tag = 
	    STATIC_SYMBOL("G2DS-DOTTED-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_dotted_list_type_tag,FIX((SI_Long)7L));
    Qg2int_g2ds_evaluation_sequence_type_tag = 
	    STATIC_SYMBOL("G2DS-EVALUATION-SEQUENCE-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_evaluation_sequence_type_tag,
	    FIX((SI_Long)8L));
    Qg2int_g2ds_evaluation_structure_type_tag = 
	    STATIC_SYMBOL("G2DS-EVALUATION-STRUCTURE-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_evaluation_structure_type_tag,
	    FIX((SI_Long)9L));
    Qg2int_g2ds_logical_type_tag = STATIC_SYMBOL("G2DS-LOGICAL-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_logical_type_tag,FIX((SI_Long)10L));
    Qg2int_g2ds_no_error = STATIC_SYMBOL("G2DS-NO-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_no_error,FIX((SI_Long)0L));
    Qg2int_default_g2ds_interface_countdown_timer_limit = 
	    STATIC_SYMBOL("DEFAULT-G2DS-INTERFACE-COUNTDOWN-TIMER-LIMIT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_default_g2ds_interface_countdown_timer_limit,
	    FIX((SI_Long)10L));
    Qg2int_g2ds_server_max_count_in_return_queue = 
	    STATIC_SYMBOL("G2DS-SERVER-MAX-COUNT-IN-RETURN-QUEUE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_server_max_count_in_return_queue,
	    FIX((SI_Long)20L));
    Qg2int_g2ds_read_expression_cell_index = 
	    STATIC_SYMBOL("G2DS-READ-EXPRESSION-CELL-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_read_expression_cell_index,FIX((SI_Long)0L));
    Qg2int_g2ds_write_expression_cell_index = 
	    STATIC_SYMBOL("G2DS-WRITE-EXPRESSION-CELL-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2ds_write_expression_cell_index,FIX((SI_Long)1L));
    Qg2int_iterations_for_g2ds_temporary_float_processing = 
	    STATIC_SYMBOL("ITERATIONS-FOR-G2DS-TEMPORARY-FLOAT-PROCESSING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_iterations_for_g2ds_temporary_float_processing,
	    FIX((SI_Long)100L));
    Qg2int_nupec_synchronize_datum_null_type = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM-NULL-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nupec_synchronize_datum_null_type,
	    FIX((SI_Long)0L));
    Qg2int_nupec_synchronize_datum_symbol_type = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM-SYMBOL-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nupec_synchronize_datum_symbol_type,
	    FIX((SI_Long)1L));
    Qg2int_nupec_synchronize_datum_integer_type = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM-INTEGER-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nupec_synchronize_datum_integer_type,
	    FIX((SI_Long)2L));
    Qg2int_nupec_synchronize_datum_float_type = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM-FLOAT-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nupec_synchronize_datum_float_type,
	    FIX((SI_Long)3L));
    Qg2int_nupec_synchronize_datum_text_type = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM-TEXT-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nupec_synchronize_datum_text_type,
	    FIX((SI_Long)4L));
    Qg2int_nupec_designation_null_type_tag = 
	    STATIC_SYMBOL("NUPEC-DESIGNATION-NULL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nupec_designation_null_type_tag,FIX((SI_Long)0L));
    Qg2int_nupec_designation_symbol_type_tag = 
	    STATIC_SYMBOL("NUPEC-DESIGNATION-SYMBOL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nupec_designation_symbol_type_tag,
	    FIX((SI_Long)1L));
    Qg2int_nupec_designation_cons_type_tag = 
	    STATIC_SYMBOL("NUPEC-DESIGNATION-CONS-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nupec_designation_cons_type_tag,FIX((SI_Long)2L));
    Qg2int_status_bar_maximum_pane_count = 
	    STATIC_SYMBOL("STATUS-BAR-MAXIMUM-PANE-COUNT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_status_bar_maximum_pane_count,FIX((SI_Long)250L));
    Qg2int_logbook_destroy = STATIC_SYMBOL("LOGBOOK-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_logbook_destroy,FIX((SI_Long)2L));
    Qg2int_logbook_append_message = STATIC_SYMBOL("LOGBOOK-APPEND-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_logbook_append_message,FIX((SI_Long)10L));
    Qg2int_logbook_delete_message = STATIC_SYMBOL("LOGBOOK-DELETE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_logbook_delete_message,FIX((SI_Long)11L));
    Qg2int_logbook_normal_message = STATIC_SYMBOL("LOGBOOK-NORMAL-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_logbook_normal_message,FIX((SI_Long)12L));
    Qg2int_logbook_fade_message = STATIC_SYMBOL("LOGBOOK-FADE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_logbook_fade_message,FIX((SI_Long)13L));
    Qg2int_logbook_highlight_message = 
	    STATIC_SYMBOL("LOGBOOK-HIGHLIGHT-MESSAGE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_logbook_highlight_message,FIX((SI_Long)14L));
    Qg2int_logbook_set_line_wrap = STATIC_SYMBOL("LOGBOOK-SET-LINE-WRAP",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_logbook_set_line_wrap,FIX((SI_Long)15L));
    Qg2int_logbook_set_include_date_in_title = 
	    STATIC_SYMBOL("LOGBOOK-SET-INCLUDE-DATE-IN-TITLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_logbook_set_include_date_in_title,
	    FIX((SI_Long)16L));
    Qg2int_small_native_icon_size = STATIC_SYMBOL("SMALL-NATIVE-ICON-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_small_native_icon_size,FIX((SI_Long)16L));
    Qg2int_large_native_icon_size = STATIC_SYMBOL("LARGE-NATIVE-ICON-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_large_native_icon_size,FIX((SI_Long)32L));
    Qg2int_ld_request_full_listing = 
	    STATIC_SYMBOL("LD-REQUEST-FULL-LISTING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ld_request_full_listing,FIX((SI_Long)0L));
    Qg2int_ld_request_children = STATIC_SYMBOL("LD-REQUEST-CHILDREN",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ld_request_children,FIX((SI_Long)1L));
    Qg2int_ld_request_refresh = STATIC_SYMBOL("LD-REQUEST-REFRESH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ld_request_refresh,FIX((SI_Long)2L));
    Qg2int_hh_display_topic = STATIC_SYMBOL("HH-DISPLAY-TOPIC",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_display_topic,FIX((SI_Long)0L));
    Qg2int_hh_display_toc = STATIC_SYMBOL("HH-DISPLAY-TOC",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_display_toc,FIX((SI_Long)1L));
    Qg2int_hh_display_index = STATIC_SYMBOL("HH-DISPLAY-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_display_index,FIX((SI_Long)2L));
    Qg2int_hh_display_search = STATIC_SYMBOL("HH-DISPLAY-SEARCH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_display_search,FIX((SI_Long)3L));
    Qg2int_hh_sync = STATIC_SYMBOL("HH-SYNC",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_sync,FIX((SI_Long)9L));
    Qg2int_hh_keyword_lookup = STATIC_SYMBOL("HH-KEYWORD-LOOKUP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_keyword_lookup,FIX((SI_Long)13L));
    Qg2int_hh_display_text_popup = STATIC_SYMBOL("HH-DISPLAY-TEXT-POPUP",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_display_text_popup,FIX((SI_Long)14L));
    Qg2int_hh_help_context = STATIC_SYMBOL("HH-HELP-CONTEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_help_context,FIX((SI_Long)15L));
    Qg2int_hh_close_all = STATIC_SYMBOL("HH-CLOSE-ALL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_close_all,FIX((SI_Long)18L));
    Qg2int_hh_alink_lookup = STATIC_SYMBOL("HH-ALINK-LOOKUP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hh_alink_lookup,FIX((SI_Long)19L));
    Qg2int_mdi_normal_mode = STATIC_SYMBOL("MDI-NORMAL-MODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mdi_normal_mode,FIX((SI_Long)1L));
    Qg2int_mdi_tabbed_mode = STATIC_SYMBOL("MDI-TABBED-MODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mdi_tabbed_mode,FIX((SI_Long)2L));
    Qg2int_mdi_grouped_mode = STATIC_SYMBOL("MDI-GROUPED-MODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mdi_grouped_mode,FIX((SI_Long)3L));
    Qg2int_mdi_show_icons = STATIC_SYMBOL("MDI-SHOW-ICONS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mdi_show_icons,FIX((SI_Long)4L));
    Qg2int_mdi_tab_position = STATIC_SYMBOL("MDI-TAB-POSITION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mdi_tab_position,FIX((SI_Long)5L));
    Qg2int_mdi_tab_layout = STATIC_SYMBOL("MDI-TAB-LAYOUT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mdi_tab_layout,FIX((SI_Long)6L));
    Qg2int_number_of_gsi_subtests = STATIC_SYMBOL("NUMBER-OF-GSI-SUBTESTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_number_of_gsi_subtests,FIX((SI_Long)7L));
    Qg2int_number_of_protocols = STATIC_SYMBOL("NUMBER-OF-PROTOCOLS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_number_of_protocols,FIX((SI_Long)1L));
    Qg2int_tcpip_protocol = STATIC_SYMBOL("TCPIP-PROTOCOL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_tcpip_protocol,FIX((SI_Long)0L));
    Qg2int_call_site_minimum_size = STATIC_SYMBOL("CALL-SITE-MINIMUM-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_call_site_minimum_size,FIX((SI_Long)5L));
    Qg2int_errno_would_block = STATIC_SYMBOL("ERRNO-WOULD-BLOCK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_errno_would_block,FIX((SI_Long)35L));
    Qg2int_errno_again = STATIC_SYMBOL("ERRNO-AGAIN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_errno_again,FIX((SI_Long)11L));
    Qg2int_enetreset = STATIC_SYMBOL("ENETRESET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_enetreset,FIX((SI_Long)52L));
    Qg2int_econnaborted = STATIC_SYMBOL("ECONNABORTED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_econnaborted,FIX((SI_Long)53L));
    Qg2int_java_access_flag_public = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-PUBLIC",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_public,FIX((SI_Long)1L));
    Qg2int_java_access_flag_private = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-PRIVATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_private,FIX((SI_Long)2L));
    Qg2int_java_access_flag_protected = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-PROTECTED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_protected,FIX((SI_Long)4L));
    Qg2int_java_access_flag_static = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-STATIC",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_static,FIX((SI_Long)8L));
    Qg2int_java_access_flag_final = STATIC_SYMBOL("JAVA-ACCESS-FLAG-FINAL",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_final,FIX((SI_Long)16L));
    Qg2int_java_access_flag_super = STATIC_SYMBOL("JAVA-ACCESS-FLAG-SUPER",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_super,FIX((SI_Long)32L));
    Qg2int_java_access_flag_synchronized = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-SYNCHRONIZED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_synchronized,FIX((SI_Long)32L));
    Qg2int_java_access_flag_volatile = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-VOLATILE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_volatile,FIX((SI_Long)64L));
    Qg2int_java_access_flag_transient = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-TRANSIENT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_transient,FIX((SI_Long)128L));
    Qg2int_java_access_flag_native = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-NATIVE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_native,FIX((SI_Long)256L));
    Qg2int_java_access_flag_interface = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-INTERFACE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_interface,FIX((SI_Long)512L));
    Qg2int_java_access_flag_abstract = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-ABSTRACT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_access_flag_abstract,FIX((SI_Long)1024L));
    Qg2int_java_constant_class = STATIC_SYMBOL("JAVA-CONSTANT-CLASS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_class,FIX((SI_Long)7L));
    Qg2int_java_constant_fieldref = STATIC_SYMBOL("JAVA-CONSTANT-FIELDREF",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_fieldref,FIX((SI_Long)9L));
    Qg2int_java_constant_methodref = 
	    STATIC_SYMBOL("JAVA-CONSTANT-METHODREF",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_methodref,FIX((SI_Long)10L));
    Qg2int_java_constant_interfacemethodref = 
	    STATIC_SYMBOL("JAVA-CONSTANT-INTERFACEMETHODREF",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_interfacemethodref,
	    FIX((SI_Long)11L));
    Qg2int_java_constant_string = STATIC_SYMBOL("JAVA-CONSTANT-STRING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_string,FIX((SI_Long)8L));
    Qg2int_java_constant_integer = STATIC_SYMBOL("JAVA-CONSTANT-INTEGER",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_integer,FIX((SI_Long)3L));
    Qg2int_java_constant_float = STATIC_SYMBOL("JAVA-CONSTANT-FLOAT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_float,FIX((SI_Long)4L));
    Qg2int_java_constant_long = STATIC_SYMBOL("JAVA-CONSTANT-LONG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_long,FIX((SI_Long)5L));
    Qg2int_java_constant_double = STATIC_SYMBOL("JAVA-CONSTANT-DOUBLE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_double,FIX((SI_Long)6L));
    Qg2int_java_constant_nameandtype = 
	    STATIC_SYMBOL("JAVA-CONSTANT-NAMEANDTYPE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_nameandtype,FIX((SI_Long)12L));
    Qg2int_java_constant_utf8 = STATIC_SYMBOL("JAVA-CONSTANT-UTF8",AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_utf8,FIX((SI_Long)1L));
    Qg2int_java_constant_unicode = STATIC_SYMBOL("JAVA-CONSTANT-UNICODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_java_constant_unicode,FIX((SI_Long)2L));
}
