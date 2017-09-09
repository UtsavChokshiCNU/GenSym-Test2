/* g2cnfg.c
 * Input file:  g2-config.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2cnfg.h"


Object Maximum_key_index = UNBOUND;

Object Key_index_bits = UNBOUND;

Object Unicode_character_bits = UNBOUND;

Object Unicode_mask = UNBOUND;

Object Control_mask = UNBOUND;

Object Meta_mask = UNBOUND;

Object Extend_char_mask = UNBOUND;

Object Compose_char_mask = UNBOUND;

Object Alternate_mask = UNBOUND;

Object Shift_mask = UNBOUND;

Object Caps_lock_mask = UNBOUND;

Object Double_mask = UNBOUND;

Object Key_code_bits = UNBOUND;

Object Key_modifier_bits = UNBOUND;

Object Illegal_key_index = UNBOUND;

Object Sparse_array_max_depth = UNBOUND;

Object Maximum_index_in_backtrace_stack_for_internal_error = UNBOUND;

Object X11_event_codes_mask = UNBOUND;

Object X11_key_code_shift = UNBOUND;

Object Gensym_windows_minimum_supported_scale = UNBOUND;

Object Gensym_windows_maximum_supported_scale = UNBOUND;

Object Icp_window_protocol_70_prerelease = UNBOUND;

Object Maximum_interval_between_new_time_for_uuid = UNBOUND;

Object Codejock_reserved_command_ids = UNBOUND;

Object Nms_handle_gap_low = UNBOUND;

Object Nms_handle_gap_high = UNBOUND;

Object Obs_default_style = UNBOUND;

Object Least_common_multiple_of_stock_line_pattern_lengths = UNBOUND;

Object Minimum_minimum_float_scheduling_interval = UNBOUND;

Object Date_month_and_year_of_frame_edit_base_time = UNBOUND;

Object G2_array_length_maximum = UNBOUND;

Object History_timestamp_epsilon = UNBOUND;

void g2_config_INIT()
{
    SI_Long temp;
    Object Qjava_constant_unicode, AB_package, Qjava_constant_utf8;
    Object Qjava_constant_nameandtype, Qjava_constant_double;
    Object Qjava_constant_long, Qjava_constant_float, Qjava_constant_integer;
    Object Qjava_constant_string, Qjava_constant_interfacemethodref;
    Object Qjava_constant_methodref, Qjava_constant_fieldref;
    Object Qjava_constant_class, Qjava_access_flag_abstract;
    Object Qjava_access_flag_interface, Qjava_access_flag_native;
    Object Qjava_access_flag_transient, Qjava_access_flag_volatile;
    Object Qjava_access_flag_synchronized, Qjava_access_flag_super;
    Object Qjava_access_flag_final, Qjava_access_flag_static;
    Object Qjava_access_flag_protected, Qjava_access_flag_private;
    Object Qjava_access_flag_public, Qeconnaborted, Qenetreset, Qerrno_again;
    Object Qerrno_would_block, Qcall_site_minimum_size, Qtcpip_protocol;
    Object Qnumber_of_protocols, Qnumber_of_gsi_subtests, Qmdi_tab_layout;
    Object Qmdi_tab_position, Qmdi_show_icons, Qmdi_grouped_mode;
    Object Qmdi_tabbed_mode, Qmdi_normal_mode, Qhh_alink_lookup, Qhh_close_all;
    Object Qhh_help_context, Qhh_display_text_popup, Qhh_keyword_lookup;
    Object Qhh_sync, Qhh_display_search, Qhh_display_index, Qhh_display_toc;
    Object Qhh_display_topic, Qld_request_refresh, Qld_request_children;
    Object Qld_request_full_listing, Qlarge_native_icon_size;
    Object Qsmall_native_icon_size, Qlogbook_set_include_date_in_title;
    Object Qlogbook_set_line_wrap, Qlogbook_highlight_message;
    Object Qlogbook_fade_message, Qlogbook_normal_message;
    Object Qlogbook_delete_message, Qlogbook_append_message, Qlogbook_destroy;
    Object Qstatus_bar_maximum_pane_count, Qnupec_designation_cons_type_tag;
    Object Qnupec_designation_symbol_type_tag;
    Object Qnupec_designation_null_type_tag;
    Object Qnupec_synchronize_datum_text_type;
    Object Qnupec_synchronize_datum_float_type;
    Object Qnupec_synchronize_datum_integer_type;
    Object Qnupec_synchronize_datum_symbol_type;
    Object Qnupec_synchronize_datum_null_type;
    Object Qiterations_for_g2ds_temporary_float_processing;
    Object Qg2ds_write_expression_cell_index, Qg2ds_read_expression_cell_index;
    Object Qg2ds_server_max_count_in_return_queue;
    Object Qdefault_g2ds_interface_countdown_timer_limit, Qg2ds_no_error;
    Object Qg2ds_logical_type_tag, Qg2ds_evaluation_structure_type_tag;
    Object Qg2ds_evaluation_sequence_type_tag, Qg2ds_dotted_list_type_tag;
    Object Qg2ds_64bit_float_type_tag, Qg2ds_list_type_tag;
    Object Qg2ds_string_type_tag, Qg2ds_symbol_type_tag, Qg2ds_float_type_tag;
    Object Qg2ds_integer_type_tag, Qg2ds_null_type_tag;
    Object Qiterations_for_gsi_temporary_float_processing;
    Object Qmaximum_gfi_output_queue_count, Qffs_unknown_return_type;
    Object Qffs_unknown_function, Qffs_signal_caught_during_call;
    Object Qffs_connection_open_already, Qffs_unspecified_error;
    Object Qshutdown_context_only_flag_set, Qshutdown_context_only_flag_clear;
    Object Qlargest_known_fixnum_time_units_per_second;
    Object Qforeign_function_text_type_tag, Qforeign_function_symbol_type_tag;
    Object Qforeign_function_real_type_tag, Qforeign_function_integer_type_tag;
    Object Qframe_display_reformat_after_count_deleted;
    Object Qframe_display_vertical_spacing, Qframe_display_workspace_margin;
    Object Qfloat_format_precision_limit, Qmax_icon_area, Qmax_icon_size;
    Object Qattribute_nesting_limit, Qmaximum_connection_dash_count;
    Object Qmaximum_connection_dash_length, Qten_years;
    Object Qvariable_value_particular_code, Qvirtual_attribute_particular_code;
    Object Qelement_particular_code, Qaliased_attribute_particular_code;
    Object Qattribute_particular_code, Qmaximum_denotation_sequence_elements;
    Object Qmaximum_denotation_types, Qdenotation_element_overhead_slot_count;
    Object Qattribute_value_cache_entry_size;
    Object Qslot_description_cache_entry_size, Qmaximum_length_for_dom_strings;
    Object Qxml_notation_node, Qxml_document_fragment_node;
    Object Qxml_document_type_node, Qxml_document_node, Qxml_comment_node;
    Object Qxml_processing_instruction_node, Qxml_entity_node;
    Object Qxml_entity_reference_node, Qxml_cdata_section_node, Qxml_text_node;
    Object Qxml_attribute_node, Qxml_element_node, Qxml_encoding_length;
    Object Qxml_callback_fatal_error, Qxml_callback_error;
    Object Qxml_callback_warning, Qxml_callback_comment;
    Object Qxml_callback_characters, Qxml_callback_end_element;
    Object Qxml_callback_start_element, Qxml_callback_end_document;
    Object Qxml_callback_start_document, Qxml_callback_none;
    Object Qfraction_modulus_of_compound_fixnum_simulation_time;
    Object Qbuffered_plot_painting_minimum_ratio;
    Object Qmaximum_painting_action_args, Qinitial_change_log_revision_number;
    Object Qmaximum_number_of_lisp_call_return_values;
    Object Qmaximum_number_of_lisp_call_arguments;
    Object Qmaximum_length_for_writing_evaluation_values;
    Object Qprocedure_invalidates_environment_union_mask;
    Object Qprocedure_call_without_validated_environment_mask;
    Object Qprocedure_contains_indirect_procedure_call_mask;
    Object Qprocedure_contains_wait_state_mask;
    Object Qprocedure_can_invalidate_environment_mask;
    Object Qdefault_procedure_evaluation_priority, Qno_resumable_object_index;
    Object Qno_history_spec_value, float_constant_4;
    Object Qhistory_timestamp_epsilon, Qg2_array_length_maximum;
    Object Qdefault_error_source_column, Qdefault_error_source_line;
    Object Qdefault_telewindows_upper_margin, Qmost_negative_window_coordinate;
    Object Qmost_positive_window_coordinate;
    Object Qadditional_time_for_synthetic_paste_event_timestamps;
    Object Qframe_edit_base_timestamp, list_constant_1;
    Object Qdate_month_and_year_of_frame_edit_base_time, Qhfep_null_code;
    Object Qhfep_error, Qhfep_wrong, Qhfep_done, Qhfep_go_on, Qhfep_none;
    Object Qhfep_ks_size, Qjis_m_dash_character_code;
    Object Qjis_letter_a_character_code, Qjis_0_digit_character_code;
    Object Qjis_colon_character_code, Qjis_space_character_code;
    Object Qtmask_kka_ishouki, Qtmask_kka_kofind, Qtmask_kka_g_taigen;
    Object Qtmask_chkattr, Qtmask_chkbunpo, Qtmask_kka_find_bunpo;
    Object Qtmask_kka_evalbun, Qtmask_kka_gtnum, Qtmask_kka_ghyoki;
    Object Qtmask_kka_gtango, Qtmask_kka_hensaisyo, Qtmask_kka_p_batkanakan;
    Object float_constant_3, Qminimum_minimum_float_scheduling_interval;
    Object Qminimum_minimum_fixnum_scheduling_interval;
    Object Qleast_common_multiple_of_stock_line_pattern_lengths;
    Object Qevent_time_mask, Qlvscw_autosize_useheader, Qlvscw_autosize;
    Object Qlvcfmt_center, Qlvcfmt_right, Qlvcfmt_left, Qchart_no_window;
    Object Qchart_success, Qchart_format_svg, Qchart_format_wmf;
    Object Qchart_format_bmp, Qchart_format_png, Qchart_format_jpeg;
    Object Qchart_export, Qchart_copy, Qchart_partial_update, Qchart_update;
    Object Qchart_print, Qchart_destroy, Qchart_create, Qdlgm_sndmsg;
    Object Qdlgm_check, Qdlgm_seticon, Qdlgm_addstrings, Qdlgm_settext;
    Object Qobs_default_style, Qobs_xt_selhighlight, Qobs_xt_animation;
    Object Qobs_xt_dragitems, Qobs_xt_addgroups, Qobs_xt_removeitems;
    Object Qobs_xt_removegroups, Qobs_xt_edititems, Qobs_xt_editgroups;
    Object Qobs_xt_largeicon, Qobs_xt_smallicon;
    Object Qshortcut_bar_foreground_color, Qshortcut_bar_background_color;
    Object Qshortcut_bar_large_icons, Qshortcut_bar_small_icons;
    Object Qshortcut_bar_disable_item, Qshortcut_bar_enable_item;
    Object Qshortcut_bar_select_item, Qshortcut_bar_disable_folder;
    Object Qshortcut_bar_enable_folder, Qshortcut_bar_select_folder;
    Object Qshortcut_bar_clear, Qshortcut_bar_add_item;
    Object Qshortcut_bar_add_folder, Qshortcut_bar_destroy;
    Object Qshortcut_bar_style_outlook_2003, Qshortcut_bar_style_outlook;
    Object Qhtml_view_print, Qhtml_view_goto, Qhtml_view_refresh;
    Object Qhtml_view_stop, Qhtml_view_home, Qhtml_view_forward;
    Object Qhtml_view_back, Qhtml_view_destroy, Qtvf_reclaim_label;
    Object Qtvf_insert_mark, Qtvf_after, Qtvf_first, Qtvf_check, Qtvf_expand;
    Object Qtvf_bold, Qtvf_children, Qtree_view_redraw;
    Object Qtree_view_collapse_all, Qtree_view_expand_all;
    Object Qtree_view_set_right_click_selects_node, Qtree_view_toggle_item;
    Object Qtree_view_delete_item, Qtree_view_set_item_check;
    Object Qtree_view_set_item_icons, Qtree_view_set_item_label;
    Object Qtree_view_set_item_bold, Qtree_view_set_item_tooltip;
    Object Qtree_view_select_item, Qtree_view_collapse_item;
    Object Qtree_view_expand_item, Qtree_view_edit_item;
    Object Qtree_view_set_insert_mark, Qtree_view_scroll_to;
    Object Qtree_view_ensure_visible, Qtree_view_select_item_by_name;
    Object Qtree_view_set_insert_mark_color, Qtree_view_set_text_color;
    Object Qtree_view_set_bgcolor, Qtree_view_set_item_height;
    Object Qtree_view_set_indent, Qtree_view_clear, Qtree_view_insert_item;
    Object Qtree_view_destroy, Qpane_set_close_action;
    Object Qpane_set_visible_caption, Qpane_set_draggable, Qpane_set_floatable;
    Object Qpane_set_autohideable, Qpane_set_closeable, Qpane_fill;
    Object Qpane_toggle_docking, Qpane_redock, Qpane_close, Qpane_set_icon;
    Object Qpane_set_title, Qpane_show, Qpane_dock, Qpane_float, Qpane_select;
    Object Qpane_hide, Qpane_destroy, Qsb_pane_borders, Qsb_pane_enabled;
    Object Qsb_pane_tooltip, Qsb_pane_alignment, Qsb_pane_icon;
    Object Qsb_pane_background, Qsb_pane_foreground, Qsb_pane_visible;
    Object Qsb_pane_width, Qsb_pane_text, Qsb_remove_pane, Qsb_add_pane;
    Object Qsb_update, Qsb_minheight, Qsb_reset, Qsb_text, Qsb_show, Qsb_hide;
    Object Qnmsc_deletetext, Qnmsc_addtext, Qnmsc_settext, Qnmsc_setcursel;
    Object Qnmsc_hide, Qnmsc_show, Qnms_handle_gap_high, Qnms_handle_gap_low;
    Object list_constant, Qcodejock_reserved_command_ids, Qnms_no_choice;
    Object Qnms_stock_command_min_id, Qlogbook_message_type_warning;
    Object Qlogbook_message_type_error, Qhh_display_envar_topic;
    Object Qhandle_for_unsuccessful_query, Qdock_code_embedded;
    Object Qdock_code_top_level, Qdock_code_mdi_child, Qdock_code_within;
    Object Qdock_code_float, Qdock_code_right, Qdock_code_left;
    Object Qdock_code_bottom, Qdock_code_top, Qdialog_is_mdi_child;
    Object Qdialog_is_modeless, Qdialog_is_modal;
    Object Qdialog_response_client_side_problem;
    Object Qdialog_response_cancel_without_callback;
    Object Qdialog_response_respond_all_and_ok, Qdialog_response_respond_all;
    Object Qdialog_response_respond_and_ok, Qdialog_response_just_respond;
    Object Qdialog_response_ok, Qdialog_response_cancel;
    Object Qdialog_response_dont_invoke_callback;
    Object Qdialog_response_send_all_data, Qdialog_response_respond;
    Object Qdialog_response_apply, Qdialog_response_close;
    Object Qdialog_response_no_action, Qdialog_response_unspecified;
    Object Qg2_send_wsv_address, Qg2_dialog_user_gesture;
    Object Qg2_multi_update_finish, Qg2_multi_update_continue;
    Object Qg2_multi_update_begin, Qtw_multi_update_finish;
    Object Qtw_multi_update_continue, Qtw_multi_update_begin;
    Object Qfocus_changed_update, Qmulti_update_finish, Qmulti_update_continue;
    Object Qmulti_update_begin, Qg2_initiated_update, Qtw_initiated_update;
    Object Qdebugger_source_stepping_flag, Qdebugger_dialog_cancel;
    Object Qcd_refresh, Qcd_add_children;
    Object Qmaximum_number_of_characters_in_pathname, Qdlg_icon_error;
    Object Qdlg_icon_warning, Qdlg_icon_information, Qdlg_icon_question;
    Object Qmb_help, Qmb_retrycancel, Qmb_yesno, Qmb_yesnocancel;
    Object Qmb_abortretryignore, Qmb_okcancel, Qmb_ok;
    Object Qmax_subblock_count_with_pop_up_virtual_attributes_table;
    Object Qdefault_maximum_renderings_for_class;
    Object Qdefault_number_of_renderings_for_bulk_delete, Qmessage_field_mask;
    Object Qsource_stepping_shift, Qbreakpoint_shift, Qtracing_shift;
    Object Qwarning_shift, Qassumed_standard_image_plane_border_width;
    Object Qmaximum_image_plane_serial_number;
    Object Qminimum_image_plane_serial_number;
    Object Qmaximum_length_of_menu_of_names;
    Object Quse_full_size_of_with_output_wide_string_cutoff;
    Object Qold_mask_for_saved_frame_flags, Qmaximum_number_of_generic_methods;
    Object Qmax_number_of_lexing_tables_to_cache;
    Object Qmax_number_of_regexps_to_cache, Qdefault_reduction;
    Object Qmax_instance_rule_chaining, Qmaximum_size_of_category_set_as_list;
    Object Qmaximum_background_tile_area, Qfree_bits_per_icp_byte;
    Object Qnumber_of_bits_of_gray_in_the_extended_gray_palette;
    Object Qblack_threshold_in_color_intensity, Qeditor_options_query_on_close;
    Object Qeditor_options_single_line_editor;
    Object Qeditor_options_single_line_comments, Qeditor_style_completion;
    Object Qeditor_style_category, Qeditor_style_normal;
    Object Qeditor_grammar_procedure_sl_rule, Qeditor_grammar_free_text;
    Object Qeditor_maximum_number_of_undos_to_remember, Qeditor_undo;
    Object Qeditor_custom_toolbar, Qeditor_beep, Qeditor_goto_item;
    Object Qeditor_text_saved, Qeditor_delete_text, Qeditor_replace_text;
    Object Qeditor_hotspot_clicked, Qeditor_append_output;
    Object Qeditor_clear_output, Qeditor_completions_new, Qeditor_apply_new;
    Object Qeditor_exit_new, Qeditor_incremental_updates, Qeditor_text_deleted;
    Object Qeditor_text_inserted, Qeditor_cursor_moved, Qeditor_set_tabs;
    Object Qeditor_set_options, Qeditor_set_grammar, Qeditor_enable;
    Object Qeditor_disable, Qeditor_apply, Qeditor_notes, Qeditor_exit;
    Object Qeditor_arglist, Qeditor_completions, Qeditor_syntax;
    Object Qeditor_insert_text, Qeditor_set_text, Qeditor_reset;
    Object Qeditor_syntax_repair, Qeditor_clear_breakpoints;
    Object Qeditor_set_breakpoint, Qeditor_disable_breakpoint;
    Object Qeditor_clear_breakpoint, Qeditor_cancel;
    Object Qeditor_add_toolbar_button, Qeditor_modal, Qeditor_show;
    Object Qeditor_print, Qeditor_destroy, Qeditor_create, Qdt_end_ellipsis;
    Object Qdt_path_ellipsis, Qdt_editcontrol, Qdt_expandtabs, Qdt_singleline;
    Object Qdt_wordbreak, Qdt_bottom, Qdt_vcenter, Qdt_right, Qdt_center;
    Object Qdt_left, Qswp_hwnd_notopmost, Qswp_hwnd_topmost, Qswp_hwnd_bottom;
    Object Qswp_hwnd_top, Qsorting_order_default, Qsort_column_default;
    Object Qcw_usedefault, Qstatus_hidden, Qstatus_docked_bottom;
    Object Qstatus_docked_right, Qstatus_docked_top, Qstatus_docked_left;
    Object Qstatus_attached, Qstatus_closed, Qstatus_collapsed;
    Object Qstatus_expanded, Qstatus_unknown, Qstatus_autohidden;
    Object Qstatus_docked, Qstatus_floated, Qsize_maxhide, Qsize_maxshow;
    Object Qsize_maximized, Qsize_minimized, Qsize_restored, Qws_ex_appwindow;
    Object Qws_ex_staticedge, Qws_ex_controlparent, Qws_ex_rightscrollbar;
    Object Qws_ex_leftscrollbar, Qws_ex_ltrreading, Qws_ex_rtlreading;
    Object Qws_ex_left, Qws_ex_right, Qws_ex_contexthelp, Qws_ex_clientedge;
    Object Qws_ex_windowedge, Qws_ex_toolwindow, Qws_ex_mdichild;
    Object Qws_ex_transparent, Qws_ex_acceptfiles, Qws_ex_topmost;
    Object Qws_ex_noparentnotify, Qws_ex_dlgmodalframe, Qws_maximizebox;
    Object Qws_minimizebox, Qws_tabstop, Qws_group, Qws_thickframe;
    Object Qws_sysmenu, Qws_hscroll, Qws_vscroll, Qws_dlgframe, Qws_border;
    Object Qws_caption, Qws_maximize, Qws_clipchildren, Qws_clipsiblings;
    Object Qws_disabled, Qws_visible, Qws_minimize, Qws_child, Qws_popup;
    Object Qws_overlapped, Qsw_showdefault, Qsw_restore, Qsw_showna;
    Object Qsw_showminnoactive, Qsw_minimize, Qsw_show, Qsw_shownoactivate;
    Object Qsw_maximize, Qsw_showminimized, Qsw_shownormal, Qsw_hide;
    Object Qnip_size_window, Qnip_set_background_color, Qnip_rescale_window;
    Object Qnip_set_closeable, Qnip_set_icon, Qnip_zorder_window;
    Object Qnip_restyle_window, Qnip_set_max_size, Qnip_cerase_window;
    Object Qnip_scroll_window, Qnip_inflate_window, Qnip_caption_window;
    Object Qnip_destroy_window, Qnip_lower_window, Qnip_raise_window;
    Object Qnip_reshape_window, Qnip_move_window, Qnip_show_window;
    Object Qnip_wintype_mask, Qnip_wintype_classic, Qframe_type_mdi;
    Object Qframe_type_sdi, Qframe_type_child, Qframe_type_classic;
    Object Qframe_type_none, Qreclaim_offscreen_pixmap;
    Object Qbitblt_offscreen_pixmap, Qdisable_offscreen_drawing;
    Object Qenable_offscreen_drawing, Qps_join_miter, Qps_join_bevel;
    Object Qps_join_round, Qps_endcap_flat, Qps_endcap_square;
    Object Qps_endcap_round, Qps_userstyle, Qps_dashdotdot, Qps_dashdot;
    Object Qps_dot, Qps_dash, Qps_solid, Qno_stipple_value;
    Object Qtransparent_color_value, Qminimum_intensity_for_white;
    Object Qgsi_product_tag, Qg2_product_tag, Quse_no_network_protocols;
    Object Quse_tcpip_protocol_only, Quse_all_network_protocols;
    Object Qminimum_message_series_size_before_beginning_new_series;
    Object Qminimum_message_series_size_before_suspending, Qne_error_value;
    Object Qne_eof_value, Qne_blocked_value, Quuid_offset_mask;
    Object float_constant_2, Qmaximum_interval_between_new_time_for_uuid;
    Object Qnumber_of_system_metrics, Qsm_cydialog, Qsm_cxdialog;
    Object Qsm_samedisplayformat, Qsm_cmonitors, Qsm_cyvirtualscreen;
    Object Qsm_cxvirtualscreen, Qsm_yvirtualscreen, Qsm_xvirtualscreen;
    Object Qsm_mousewheelpresent, Qsm_mideastenabled, Qsm_slowmachine;
    Object Qsm_cymenucheck, Qsm_cxmenucheck, Qsm_showsounds, Qsm_cydrag;
    Object Qsm_cxdrag, Qsm_cleanboot, Qsm_network, Qsm_cymaximized;
    Object Qsm_cxmaximized, Qsm_cymaxtrack, Qsm_cxmaxtrack, Qsm_cyminimized;
    Object Qsm_cxminimized, Qsm_arrange, Qsm_cymenusize, Qsm_cxmenusize;
    Object Qsm_cysmsize, Qsm_cxsmsize, Qsm_cysmcaption, Qsm_cysmicon;
    Object Qsm_cxsmicon, Qsm_cyminspacing, Qsm_cxminspacing, Qsm_cyedge;
    Object Qsm_cxedge, Qsm_secure, Qsm_cmousebuttons, Qsm_dbcsenabled;
    Object Qsm_penwindows, Qsm_menudropalignment, Qsm_cyiconspacing;
    Object Qsm_cxiconspacing, Qsm_cydoubleclk, Qsm_cxdoubleclk, Qsm_cymintrack;
    Object Qsm_cxmintrack, Qsm_cyframe, Qsm_cxframe, Qsm_cysize, Qsm_cxsize;
    Object Qsm_cymin, Qsm_cxmin, Qsm_swapbutton, Qsm_debug, Qsm_cxhscroll;
    Object Qsm_cyvscroll, Qsm_mousepresent, Qsm_cykanjiwindow;
    Object Qsm_cyfullscreen, Qsm_cxfullscreen, Qsm_cymenu, Qsm_cycursor;
    Object Qsm_cxcursor, Qsm_cyicon, Qsm_cxicon, Qsm_cxhthumb, Qsm_cyvthumb;
    Object Qsm_cydlgframe, Qsm_cxdlgframe, Qsm_cyborder, Qsm_cxborder;
    Object Qsm_cycaption, Qsm_cyhscroll, Qsm_cxvscroll, Qsm_cyscreen;
    Object Qsm_cxscreen, Qicp_window_protocol_supports_basic_dialogs;
    Object Qicp_window_protocol_supports_native_progress_bar;
    Object Qicp_window_protocol_supports_move_telewindow;
    Object Qicp_window_protocol_supports_native_icons;
    Object Qicp_window_protocol_supports_nms_posting_callbacks;
    Object Qicp_window_protocol_supports_native_printing;
    Object Qicp_window_protocol_70_prerelease, Qicp_window_protocol_70r0;
    Object Qicp_window_protocol_supports_nms_menus;
    Object Qicp_window_protocol_supports_image_tiling;
    Object Qicp_window_protocol_supports_native_widgets;
    Object Qicp_window_protocol_supports_event_plists;
    Object Qicp_window_protocol_supports_offscreen_drawing;
    Object Qicp_window_protocol_supports_wide_polyline;
    Object Qicp_window_protocol_supports_24bit_image_painting;
    Object Qicp_window_protocol_supports_raster_stipples;
    Object Qicp_window_protocol_supports_unicode_character_events;
    Object Qicp_window_protocol_supports_request_for_paste_availability;
    Object Qicp_window_protocol_supports_native_cut_and_paste;
    Object Qicp_window_protocol_supports_polychrome_icon_images;
    Object Qicp_window_protocol_supports_un_decomposed_polygons;
    Object Qicp_window_protocol_supports_saving_user_settings;
    Object Qicp_window_protocol_supports_md5_password_encryption;
    Object Qicp_window_protocol_supports_text_strings_as_wide_strings;
    Object Qicp_window_protocol_supports_oriented_text_in_scratchpad_rasters;
    Object Qicp_window_protocol_supports_remote_executables;
    Object Qicp_window_protocol_supports_remote_processes;
    Object Qicp_window_protocol_supports_slavic_font;
    Object Qicp_window_protocol_supports_telewindows_connection_license_info;
    Object Qicp_window_protocol_supports_ping_drawing;
    Object Qicp_window_protocol_supports_force_graphics;
    Object Qicp_window_protocol_supports_floating_telewindows;
    Object Qicp_window_protocol_supports_v4_mouse_messages;
    Object Qicp_window_protocol_supports_scrolling;
    Object Qicp_window_protocol_supports_setting_protocol_level;
    Object Qicp_window_protocol_supports_transparent_copy;
    Object Qicp_window_protocol_supports_monochrome_raster_lists;
    Object Qoriginal_icp_window_protocol_version, Qmaximum_polygon_points;
    Object float_constant_1, Qgensym_windows_maximum_supported_scale;
    Object float_constant, Qgensym_windows_minimum_supported_scale;
    Object Qgensym_windows_standard_dpi, Qgensym_windows_maximum_supported_dpi;
    Object Qgensym_windows_minimum_supported_dpi;
    Object Qclipboard_read_results_failure_code;
    Object Qunicode_text_clipboard_read_results_entry;
    Object Qx_compound_text_clipboard_read_results_entry;
    Object Qlatin_1_clipboard_read_results_entry;
    Object Qclipboard_reading_results_vector_length;
    Object Qallocated_clipboard_text_length;
    Object Qspecified_max_clipboard_text_length, Qx11_control, Qx11_focus_out;
    Object Qx11_focus_in, Qx11_leave, Qx11_enter, Qx11_reshape, Qx11_exposure;
    Object Qx11_pointer_motion, Qx11_button_release, Qx11_button_press;
    Object Qx11_keypress, Qx11_nullevent, Qx11_no_more_events;
    Object Qx11_key_code_shift, Qx11_event_codes_mask;
    Object Qx11_number_of_bits_in_event_codes, Qx11_transparent_copy;
    Object Qx11_stippled, Qx11_and, Qx11_xor, Qx11_copy, Qx11_or;
    Object Qgensym_error_buffer_initial_size;
    Object Qsize_of_basic_backtrace_information;
    Object Qmaximum_index_in_backtrace_stack_for_internal_error;
    Object Qsize_of_backtrace_stack_for_internal_error;
    Object Qpost_mortem_ring_buffer_default_length;
    Object Qno_tokenizer_match_end_index, Qno_tokenizer_match_start_index;
    Object Qstate_transition_user_defined_transition_test_sentinel;
    Object Qmaximum_state_transition_args, Qlast_8859_part_number;
    Object Qfirst_8859_part_number, Q8859_code_mask, Q8859_part_size;
    Object Qintern_string_buffer_length, Qsparse_array_max_depth;
    Object Qsparse_array_layer_order, Qmaximum_length_for_user_symbols;
    Object Qmaximum_length_for_user_text_strings;
    Object Qmaximum_length_for_user_gensym_strings;
    Object Qextra_wide_string_bv16_elements, Qmanaged_array_index_offset;
    Object Qmaximum_managed_array_buffer_size;
    Object Qmaximum_oversized_managed_simple_vector_size, Qillegal_key_index;
    Object Qillegal_key_code, Qkey_modifier_bits, Qkey_code_bits, Qdouble_mask;
    Object Qcaps_lock_mask, Qshift_mask, Qalternate_mask, Qcompose_char_mask;
    Object Qextend_char_mask, Qmeta_mask, Qcontrol_mask, Qunicode_mask;
    Object Qdouble_bit, Qcaps_lock_bit, Qshift_bit, Qalternate_bit;
    Object Qcompose_char_bit, Qextend_char_bit, Qmeta_bit, Qcontrol_bit;
    Object Qunicode_bit, Qmenu_bit, Qunicode_character_bits;
    Object Qnumber_of_unicode_character_bits, Qkey_index_bits;
    Object Qmaximum_key_index, Qmaximum_number_of_key_indexes;
    Object Qnumber_of_key_index_bits, Qc_environment_var_strlen_failure;
    Object Qc_argv_n_strlen_failure;

    x_note_fn_call(4,0);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qc_argv_n_strlen_failure = STATIC_SYMBOL("C-ARGV-N-STRLEN-FAILURE",
	    AB_package);
    SET_SYMBOL_VALUE(Qc_argv_n_strlen_failure,FIX((SI_Long)-1L));
    Qc_environment_var_strlen_failure = 
	    STATIC_SYMBOL("C-ENVIRONMENT-VAR-STRLEN-FAILURE",AB_package);
    SET_SYMBOL_VALUE(Qc_environment_var_strlen_failure,FIX((SI_Long)-1L));
    Qnumber_of_key_index_bits = STATIC_SYMBOL("NUMBER-OF-KEY-INDEX-BITS",
	    AB_package);
    SET_SYMBOL_VALUE(Qnumber_of_key_index_bits,FIX((SI_Long)11L));
    Qmaximum_number_of_key_indexes = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-KEY-INDEXES",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_number_of_key_indexes,FIX((SI_Long)2048L));
    Qmaximum_key_index = STATIC_SYMBOL("MAXIMUM-KEY-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_key_index,Maximum_key_index);
    SET_SYMBOL_VALUE(Qmaximum_key_index,FIXNUM_SUB1(FIX((SI_Long)2048L)));
    Qkey_index_bits = STATIC_SYMBOL("KEY-INDEX-BITS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkey_index_bits,Key_index_bits);
    SET_SYMBOL_VALUE(Qkey_index_bits,FIXNUM_SUB1(FIX((SI_Long)2048L)));
    Qnumber_of_unicode_character_bits = 
	    STATIC_SYMBOL("NUMBER-OF-UNICODE-CHARACTER-BITS",AB_package);
    SET_SYMBOL_VALUE(Qnumber_of_unicode_character_bits,FIX((SI_Long)16L));
    Qunicode_character_bits = STATIC_SYMBOL("UNICODE-CHARACTER-BITS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qunicode_character_bits,Unicode_character_bits);
    SET_SYMBOL_VALUE(Qunicode_character_bits,
	    FIXNUM_SUB1(FIX((SI_Long)65536L)));
    Qmenu_bit = STATIC_SYMBOL("MENU-BIT",AB_package);
    SET_SYMBOL_VALUE(Qmenu_bit,FIX((SI_Long)33554432L));
    Qunicode_bit = STATIC_SYMBOL("UNICODE-BIT",AB_package);
    SET_SYMBOL_VALUE(Qunicode_bit,FIX((SI_Long)16777216L));
    Qcontrol_bit = STATIC_SYMBOL("CONTROL-BIT",AB_package);
    SET_SYMBOL_VALUE(Qcontrol_bit,FIX((SI_Long)8388608L));
    Qmeta_bit = STATIC_SYMBOL("META-BIT",AB_package);
    SET_SYMBOL_VALUE(Qmeta_bit,FIX((SI_Long)4194304L));
    Qextend_char_bit = STATIC_SYMBOL("EXTEND-CHAR-BIT",AB_package);
    SET_SYMBOL_VALUE(Qextend_char_bit,FIX((SI_Long)2097152L));
    Qcompose_char_bit = STATIC_SYMBOL("COMPOSE-CHAR-BIT",AB_package);
    SET_SYMBOL_VALUE(Qcompose_char_bit,FIX((SI_Long)1048576L));
    Qalternate_bit = STATIC_SYMBOL("ALTERNATE-BIT",AB_package);
    SET_SYMBOL_VALUE(Qalternate_bit,FIX((SI_Long)524288L));
    Qshift_bit = STATIC_SYMBOL("SHIFT-BIT",AB_package);
    SET_SYMBOL_VALUE(Qshift_bit,FIX((SI_Long)262144L));
    Qcaps_lock_bit = STATIC_SYMBOL("CAPS-LOCK-BIT",AB_package);
    SET_SYMBOL_VALUE(Qcaps_lock_bit,FIX((SI_Long)131072L));
    Qdouble_bit = STATIC_SYMBOL("DOUBLE-BIT",AB_package);
    SET_SYMBOL_VALUE(Qdouble_bit,FIX((SI_Long)65536L));
    Qunicode_mask = STATIC_SYMBOL("UNICODE-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qunicode_mask,Unicode_mask);
    SET_SYMBOL_VALUE(Qunicode_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),Unicode_bit));
    Qcontrol_mask = STATIC_SYMBOL("CONTROL-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcontrol_mask,Control_mask);
    SET_SYMBOL_VALUE(Qcontrol_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),Control_bit));
    Qmeta_mask = STATIC_SYMBOL("META-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmeta_mask,Meta_mask);
    SET_SYMBOL_VALUE(Qmeta_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),Meta_bit));
    Qextend_char_mask = STATIC_SYMBOL("EXTEND-CHAR-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qextend_char_mask,Extend_char_mask);
    SET_SYMBOL_VALUE(Qextend_char_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),Extend_char_bit));
    Qcompose_char_mask = STATIC_SYMBOL("COMPOSE-CHAR-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompose_char_mask,Compose_char_mask);
    SET_SYMBOL_VALUE(Qcompose_char_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),Compose_char_bit));
    Qalternate_mask = STATIC_SYMBOL("ALTERNATE-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qalternate_mask,Alternate_mask);
    SET_SYMBOL_VALUE(Qalternate_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),Alternate_bit));
    Qshift_mask = STATIC_SYMBOL("SHIFT-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qshift_mask,Shift_mask);
    SET_SYMBOL_VALUE(Qshift_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),Shift_bit));
    Qcaps_lock_mask = STATIC_SYMBOL("CAPS-LOCK-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcaps_lock_mask,Caps_lock_mask);
    SET_SYMBOL_VALUE(Qcaps_lock_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),Caps_lock_bit));
    Qdouble_mask = STATIC_SYMBOL("DOUBLE-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdouble_mask,Double_mask);
    SET_SYMBOL_VALUE(Qdouble_mask,
	    FIXNUM_LOGXOR(FIXNUM_LOGNOT(FIX((SI_Long)0L)),Double_bit));
    Qkey_code_bits = STATIC_SYMBOL("KEY-CODE-BITS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkey_code_bits,Key_code_bits);
    temp = IFIX(FIXNUM_SUB1(FIX((SI_Long)33554432L)));
    SET_SYMBOL_VALUE(Qkey_code_bits,FIX(temp));
    Qkey_modifier_bits = STATIC_SYMBOL("KEY-MODIFIER-BITS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkey_modifier_bits,Key_modifier_bits);
    SET_SYMBOL_VALUE(Qkey_modifier_bits,logiorn(9,Unicode_bit,Control_bit,
	    Meta_bit,Extend_char_bit,Compose_char_bit,Alternate_bit,
	    Shift_bit,Caps_lock_bit,Double_bit));
    Qillegal_key_code = STATIC_SYMBOL("ILLEGAL-KEY-CODE",AB_package);
    SET_SYMBOL_VALUE(Qillegal_key_code,FIX((SI_Long)-1L));
    Qillegal_key_index = STATIC_SYMBOL("ILLEGAL-KEY-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qillegal_key_index,Illegal_key_index);
    SET_SYMBOL_VALUE(Qillegal_key_index,logand(Illegal_key_code,
	    Key_index_bits));
    Qmaximum_oversized_managed_simple_vector_size = 
	    STATIC_SYMBOL("MAXIMUM-OVERSIZED-MANAGED-SIMPLE-VECTOR-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_oversized_managed_simple_vector_size,
	    FIX((SI_Long)1048576L));
    Qmaximum_managed_array_buffer_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-ARRAY-BUFFER-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_managed_array_buffer_size,FIX((SI_Long)1024L));
    Qmanaged_array_index_offset = 
	    STATIC_SYMBOL("MANAGED-ARRAY-INDEX-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qmanaged_array_index_offset,FIX((SI_Long)2L));
    Qextra_wide_string_bv16_elements = 
	    STATIC_SYMBOL("EXTRA-WIDE-STRING-BV16-ELEMENTS",AB_package);
    SET_SYMBOL_VALUE(Qextra_wide_string_bv16_elements,FIX((SI_Long)3L));
    Qmaximum_length_for_user_gensym_strings = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-FOR-USER-GENSYM-STRINGS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_length_for_user_gensym_strings,
	    FIX((SI_Long)400000000L));
    Qmaximum_length_for_user_text_strings = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-FOR-USER-TEXT-STRINGS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_length_for_user_text_strings,
	    FIX((SI_Long)100000000L));
    Qmaximum_length_for_user_symbols = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-FOR-USER-SYMBOLS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_length_for_user_symbols,FIX((SI_Long)65533L));
    Qsparse_array_layer_order = STATIC_SYMBOL("SPARSE-ARRAY-LAYER-ORDER",
	    AB_package);
    SET_SYMBOL_VALUE(Qsparse_array_layer_order,FIX((SI_Long)5L));
    Qsparse_array_max_depth = STATIC_SYMBOL("SPARSE-ARRAY-MAX-DEPTH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsparse_array_max_depth,Sparse_array_max_depth);
    SET_SYMBOL_VALUE(Qsparse_array_max_depth,
	    lfloor(llog(Most_positive_fixnum,FIX((SI_Long)2L)),
	    Sparse_array_layer_order));
    Qintern_string_buffer_length = 
	    STATIC_SYMBOL("INTERN-STRING-BUFFER-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qintern_string_buffer_length,FIX((SI_Long)32L));
    Q8859_part_size = STATIC_SYMBOL("8859-PART-SIZE",AB_package);
    SET_SYMBOL_VALUE(Q8859_part_size,FIX((SI_Long)128L));
    Q8859_code_mask = STATIC_SYMBOL("8859-CODE-MASK",AB_package);
    SET_SYMBOL_VALUE(Q8859_code_mask,FIX((SI_Long)127L));
    Qfirst_8859_part_number = STATIC_SYMBOL("FIRST-8859-PART-NUMBER",
	    AB_package);
    SET_SYMBOL_VALUE(Qfirst_8859_part_number,FIX((SI_Long)1L));
    Qlast_8859_part_number = STATIC_SYMBOL("LAST-8859-PART-NUMBER",AB_package);
    SET_SYMBOL_VALUE(Qlast_8859_part_number,FIX((SI_Long)10L));
    Qmaximum_state_transition_args = 
	    STATIC_SYMBOL("MAXIMUM-STATE-TRANSITION-ARGS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_state_transition_args,FIX((SI_Long)4L));
    Qstate_transition_user_defined_transition_test_sentinel = 
	    STATIC_SYMBOL("STATE-TRANSITION-USER-DEFINED-TRANSITION-TEST-SENTINEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qstate_transition_user_defined_transition_test_sentinel,
	    FIX((SI_Long)-1L));
    Qno_tokenizer_match_start_index = 
	    STATIC_SYMBOL("NO-TOKENIZER-MATCH-START-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qno_tokenizer_match_start_index,FIX((SI_Long)-1L));
    Qno_tokenizer_match_end_index = 
	    STATIC_SYMBOL("NO-TOKENIZER-MATCH-END-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qno_tokenizer_match_end_index,FIX((SI_Long)0L));
    Qpost_mortem_ring_buffer_default_length = 
	    STATIC_SYMBOL("POST-MORTEM-RING-BUFFER-DEFAULT-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qpost_mortem_ring_buffer_default_length,
	    FIX((SI_Long)50L));
    Qsize_of_backtrace_stack_for_internal_error = 
	    STATIC_SYMBOL("SIZE-OF-BACKTRACE-STACK-FOR-INTERNAL-ERROR",
	    AB_package);
    SET_SYMBOL_VALUE(Qsize_of_backtrace_stack_for_internal_error,
	    FIX((SI_Long)1000L));
    Qmaximum_index_in_backtrace_stack_for_internal_error = 
	    STATIC_SYMBOL("MAXIMUM-INDEX-IN-BACKTRACE-STACK-FOR-INTERNAL-ERROR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_index_in_backtrace_stack_for_internal_error,
	    Maximum_index_in_backtrace_stack_for_internal_error);
    SET_SYMBOL_VALUE(Qmaximum_index_in_backtrace_stack_for_internal_error,
	    FIXNUM_SUB1(Size_of_backtrace_stack_for_internal_error));
    Qsize_of_basic_backtrace_information = 
	    STATIC_SYMBOL("SIZE-OF-BASIC-BACKTRACE-INFORMATION",AB_package);
    SET_SYMBOL_VALUE(Qsize_of_basic_backtrace_information,FIX((SI_Long)3L));
    Qgensym_error_buffer_initial_size = 
	    STATIC_SYMBOL("GENSYM-ERROR-BUFFER-INITIAL-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qgensym_error_buffer_initial_size,FIX((SI_Long)1000L));
    Qx11_or = STATIC_SYMBOL("X11-OR",AB_package);
    SET_SYMBOL_VALUE(Qx11_or,FIX((SI_Long)0L));
    Qx11_copy = STATIC_SYMBOL("X11-COPY",AB_package);
    SET_SYMBOL_VALUE(Qx11_copy,FIX((SI_Long)1L));
    Qx11_xor = STATIC_SYMBOL("X11-XOR",AB_package);
    SET_SYMBOL_VALUE(Qx11_xor,FIX((SI_Long)2L));
    Qx11_and = STATIC_SYMBOL("X11-AND",AB_package);
    SET_SYMBOL_VALUE(Qx11_and,FIX((SI_Long)3L));
    Qx11_stippled = STATIC_SYMBOL("X11-STIPPLED",AB_package);
    SET_SYMBOL_VALUE(Qx11_stippled,FIX((SI_Long)4L));
    Qx11_transparent_copy = STATIC_SYMBOL("X11-TRANSPARENT-COPY",AB_package);
    SET_SYMBOL_VALUE(Qx11_transparent_copy,FIX((SI_Long)5L));
    Qx11_number_of_bits_in_event_codes = 
	    STATIC_SYMBOL("X11-NUMBER-OF-BITS-IN-EVENT-CODES",AB_package);
    SET_SYMBOL_VALUE(Qx11_number_of_bits_in_event_codes,FIX((SI_Long)4L));
    Qx11_event_codes_mask = STATIC_SYMBOL("X11-EVENT-CODES-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qx11_event_codes_mask,X11_event_codes_mask);
    SET_SYMBOL_VALUE(Qx11_event_codes_mask,FIXNUM_SUB1(FIX((SI_Long)16L)));
    Qx11_key_code_shift = STATIC_SYMBOL("X11-KEY-CODE-SHIFT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qx11_key_code_shift,X11_key_code_shift);
    SET_SYMBOL_VALUE(Qx11_key_code_shift,
	    FIXNUM_NEGATE(X11_number_of_bits_in_event_codes));
    Qx11_no_more_events = STATIC_SYMBOL("X11-NO-MORE-EVENTS",AB_package);
    SET_SYMBOL_VALUE(Qx11_no_more_events,FIX((SI_Long)-1L));
    Qx11_nullevent = STATIC_SYMBOL("X11-NULLEVENT",AB_package);
    SET_SYMBOL_VALUE(Qx11_nullevent,FIX((SI_Long)0L));
    Qx11_keypress = STATIC_SYMBOL("X11-KEYPRESS",AB_package);
    SET_SYMBOL_VALUE(Qx11_keypress,FIX((SI_Long)1L));
    Qx11_button_press = STATIC_SYMBOL("X11-BUTTON-PRESS",AB_package);
    SET_SYMBOL_VALUE(Qx11_button_press,FIX((SI_Long)2L));
    Qx11_button_release = STATIC_SYMBOL("X11-BUTTON-RELEASE",AB_package);
    SET_SYMBOL_VALUE(Qx11_button_release,FIX((SI_Long)3L));
    Qx11_pointer_motion = STATIC_SYMBOL("X11-POINTER-MOTION",AB_package);
    SET_SYMBOL_VALUE(Qx11_pointer_motion,FIX((SI_Long)4L));
    Qx11_exposure = STATIC_SYMBOL("X11-EXPOSURE",AB_package);
    SET_SYMBOL_VALUE(Qx11_exposure,FIX((SI_Long)5L));
    Qx11_reshape = STATIC_SYMBOL("X11-RESHAPE",AB_package);
    SET_SYMBOL_VALUE(Qx11_reshape,FIX((SI_Long)6L));
    Qx11_enter = STATIC_SYMBOL("X11-ENTER",AB_package);
    SET_SYMBOL_VALUE(Qx11_enter,FIX((SI_Long)7L));
    Qx11_leave = STATIC_SYMBOL("X11-LEAVE",AB_package);
    SET_SYMBOL_VALUE(Qx11_leave,FIX((SI_Long)8L));
    Qx11_focus_in = STATIC_SYMBOL("X11-FOCUS-IN",AB_package);
    SET_SYMBOL_VALUE(Qx11_focus_in,FIX((SI_Long)9L));
    Qx11_focus_out = STATIC_SYMBOL("X11-FOCUS-OUT",AB_package);
    SET_SYMBOL_VALUE(Qx11_focus_out,FIX((SI_Long)10L));
    Qx11_control = STATIC_SYMBOL("X11-CONTROL",AB_package);
    SET_SYMBOL_VALUE(Qx11_control,FIX((SI_Long)11L));
    Qspecified_max_clipboard_text_length = 
	    STATIC_SYMBOL("SPECIFIED-MAX-CLIPBOARD-TEXT-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qspecified_max_clipboard_text_length,
	    FIX((SI_Long)65535L));
    Qallocated_clipboard_text_length = 
	    STATIC_SYMBOL("ALLOCATED-CLIPBOARD-TEXT-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qallocated_clipboard_text_length,FIX((SI_Long)65536L));
    Qclipboard_reading_results_vector_length = 
	    STATIC_SYMBOL("CLIPBOARD-READING-RESULTS-VECTOR-LENGTH",
	    AB_package);
    SET_SYMBOL_VALUE(Qclipboard_reading_results_vector_length,
	    FIX((SI_Long)3L));
    Qlatin_1_clipboard_read_results_entry = 
	    STATIC_SYMBOL("LATIN-1-CLIPBOARD-READ-RESULTS-ENTRY",AB_package);
    SET_SYMBOL_VALUE(Qlatin_1_clipboard_read_results_entry,FIX((SI_Long)0L));
    Qx_compound_text_clipboard_read_results_entry = 
	    STATIC_SYMBOL("X-COMPOUND-TEXT-CLIPBOARD-READ-RESULTS-ENTRY",
	    AB_package);
    SET_SYMBOL_VALUE(Qx_compound_text_clipboard_read_results_entry,
	    FIX((SI_Long)1L));
    Qunicode_text_clipboard_read_results_entry = 
	    STATIC_SYMBOL("UNICODE-TEXT-CLIPBOARD-READ-RESULTS-ENTRY",
	    AB_package);
    SET_SYMBOL_VALUE(Qunicode_text_clipboard_read_results_entry,
	    FIX((SI_Long)2L));
    Qclipboard_read_results_failure_code = 
	    STATIC_SYMBOL("CLIPBOARD-READ-RESULTS-FAILURE-CODE",AB_package);
    SET_SYMBOL_VALUE(Qclipboard_read_results_failure_code,
	    FIX((SI_Long)65535L));
    Qgensym_windows_minimum_supported_dpi = 
	    STATIC_SYMBOL("GENSYM-WINDOWS-MINIMUM-SUPPORTED-DPI",AB_package);
    SET_SYMBOL_VALUE(Qgensym_windows_minimum_supported_dpi,FIX((SI_Long)36L));
    Qgensym_windows_maximum_supported_dpi = 
	    STATIC_SYMBOL("GENSYM-WINDOWS-MAXIMUM-SUPPORTED-DPI",AB_package);
    SET_SYMBOL_VALUE(Qgensym_windows_maximum_supported_dpi,FIX((SI_Long)200L));
    Qgensym_windows_standard_dpi = 
	    STATIC_SYMBOL("GENSYM-WINDOWS-STANDARD-DPI",AB_package);
    SET_SYMBOL_VALUE(Qgensym_windows_standard_dpi,FIX((SI_Long)75L));
    Qgensym_windows_minimum_supported_scale = 
	    STATIC_SYMBOL("GENSYM-WINDOWS-MINIMUM-SUPPORTED-SCALE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_windows_minimum_supported_scale,
	    Gensym_windows_minimum_supported_scale);
    float_constant = STATIC_FLOAT(0.5);
    SET_SYMBOL_VALUE(Qgensym_windows_minimum_supported_scale,float_constant);
    Qgensym_windows_maximum_supported_scale = 
	    STATIC_SYMBOL("GENSYM-WINDOWS-MAXIMUM-SUPPORTED-SCALE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_windows_maximum_supported_scale,
	    Gensym_windows_maximum_supported_scale);
    float_constant_1 = STATIC_FLOAT(2.66);
    SET_SYMBOL_VALUE(Qgensym_windows_maximum_supported_scale,float_constant_1);
    Qmaximum_polygon_points = STATIC_SYMBOL("MAXIMUM-POLYGON-POINTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_polygon_points,FIX((SI_Long)500L));
    Qoriginal_icp_window_protocol_version = 
	    STATIC_SYMBOL("ORIGINAL-ICP-WINDOW-PROTOCOL-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qoriginal_icp_window_protocol_version,FIX((SI_Long)0L));
    Qicp_window_protocol_supports_monochrome_raster_lists = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MONOCHROME-RASTER-LISTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_monochrome_raster_lists,
	    FIX((SI_Long)2L));
    Qicp_window_protocol_supports_transparent_copy = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TRANSPARENT-COPY",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_transparent_copy,
	    FIX((SI_Long)3L));
    Qicp_window_protocol_supports_setting_protocol_level = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SETTING-PROTOCOL-LEVEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_setting_protocol_level,
	    FIX((SI_Long)4L));
    Qicp_window_protocol_supports_scrolling = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SCROLLING",AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_scrolling,FIX((SI_Long)4L));
    Qicp_window_protocol_supports_v4_mouse_messages = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-V4-MOUSE-MESSAGES",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_v4_mouse_messages,
	    FIX((SI_Long)5L));
    Qicp_window_protocol_supports_floating_telewindows = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-FLOATING-TELEWINDOWS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_floating_telewindows,
	    FIX((SI_Long)6L));
    Qicp_window_protocol_supports_force_graphics = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-FORCE-GRAPHICS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_force_graphics,
	    FIX((SI_Long)7L));
    Qicp_window_protocol_supports_ping_drawing = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-PING-DRAWING",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_ping_drawing,
	    FIX((SI_Long)8L));
    Qicp_window_protocol_supports_telewindows_connection_license_info = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TELEWINDOWS-CONNECTION-LICENSE-INFO",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_telewindows_connection_license_info,
	    FIX((SI_Long)9L));
    Qicp_window_protocol_supports_slavic_font = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SLAVIC-FONT",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_slavic_font,
	    FIX((SI_Long)10L));
    Qicp_window_protocol_supports_remote_processes = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-REMOTE-PROCESSES",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_remote_processes,
	    FIX((SI_Long)11L));
    Qicp_window_protocol_supports_remote_executables = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-REMOTE-EXECUTABLES",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_remote_executables,
	    FIX((SI_Long)12L));
    Qicp_window_protocol_supports_oriented_text_in_scratchpad_rasters = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-ORIENTED-TEXT-IN-SCRATCHPAD-RASTERS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_oriented_text_in_scratchpad_rasters,
	    FIX((SI_Long)13L));
    Qicp_window_protocol_supports_text_strings_as_wide_strings = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TEXT-STRINGS-AS-WIDE-STRINGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_text_strings_as_wide_strings,
	    FIX((SI_Long)14L));
    Qicp_window_protocol_supports_md5_password_encryption = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MD5-PASSWORD-ENCRYPTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_md5_password_encryption,
	    FIX((SI_Long)15L));
    Qicp_window_protocol_supports_saving_user_settings = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SAVING-USER-SETTINGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_saving_user_settings,
	    FIX((SI_Long)16L));
    Qicp_window_protocol_supports_un_decomposed_polygons = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-UN-DECOMPOSED-POLYGONS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_un_decomposed_polygons,
	    FIX((SI_Long)18L));
    Qicp_window_protocol_supports_polychrome_icon_images = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-POLYCHROME-ICON-IMAGES",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_polychrome_icon_images,
	    FIX((SI_Long)17L));
    Qicp_window_protocol_supports_native_cut_and_paste = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-CUT-AND-PASTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_native_cut_and_paste,
	    FIX((SI_Long)19L));
    Qicp_window_protocol_supports_request_for_paste_availability = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-REQUEST-FOR-PASTE-AVAILABILITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_request_for_paste_availability,
	    FIX((SI_Long)20L));
    Qicp_window_protocol_supports_unicode_character_events = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-UNICODE-CHARACTER-EVENTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_unicode_character_events,
	    FIX((SI_Long)21L));
    Qicp_window_protocol_supports_raster_stipples = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-RASTER-STIPPLES",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_raster_stipples,
	    FIX((SI_Long)22L));
    Qicp_window_protocol_supports_24bit_image_painting = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-24BIT-IMAGE-PAINTING",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_24bit_image_painting,
	    FIX((SI_Long)23L));
    Qicp_window_protocol_supports_wide_polyline = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-WIDE-POLYLINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_wide_polyline,
	    FIX((SI_Long)24L));
    Qicp_window_protocol_supports_offscreen_drawing = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-OFFSCREEN-DRAWING",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_offscreen_drawing,
	    FIX((SI_Long)25L));
    Qicp_window_protocol_supports_event_plists = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-EVENT-PLISTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_event_plists,
	    FIX((SI_Long)26L));
    Qicp_window_protocol_supports_native_widgets = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-WIDGETS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_native_widgets,
	    FIX((SI_Long)27L));
    Qicp_window_protocol_supports_image_tiling = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-IMAGE-TILING",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_image_tiling,
	    FIX((SI_Long)28L));
    Qicp_window_protocol_supports_nms_menus = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NMS-MENUS",AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_nms_menus,
	    FIX((SI_Long)29L));
    Qicp_window_protocol_70r0 = STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-70R0",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_70r0,FIX((SI_Long)30L));
    Qicp_window_protocol_70_prerelease = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-70-PRERELEASE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_window_protocol_70_prerelease,
	    Icp_window_protocol_70_prerelease);
    SET_SYMBOL_VALUE(Qicp_window_protocol_70_prerelease,
	    add1(Icp_window_protocol_supports_offscreen_drawing));
    Qicp_window_protocol_supports_native_printing = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-PRINTING",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_native_printing,
	    FIX((SI_Long)31L));
    Qicp_window_protocol_supports_nms_posting_callbacks = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NMS-POSTING-CALLBACKS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_nms_posting_callbacks,
	    FIX((SI_Long)32L));
    Qicp_window_protocol_supports_native_icons = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-ICONS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_native_icons,
	    FIX((SI_Long)33L));
    Qicp_window_protocol_supports_move_telewindow = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MOVE-TELEWINDOW",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_move_telewindow,
	    FIX((SI_Long)34L));
    Qicp_window_protocol_supports_native_progress_bar = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-PROGRESS-BAR",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_native_progress_bar,
	    FIX((SI_Long)35L));
    Qicp_window_protocol_supports_basic_dialogs = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-BASIC-DIALOGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_basic_dialogs,
	    FIX((SI_Long)36L));
    Qsm_cxscreen = STATIC_SYMBOL("SM-CXSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxscreen,FIX((SI_Long)0L));
    Qsm_cyscreen = STATIC_SYMBOL("SM-CYSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyscreen,FIX((SI_Long)1L));
    Qsm_cxvscroll = STATIC_SYMBOL("SM-CXVSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxvscroll,FIX((SI_Long)2L));
    Qsm_cyhscroll = STATIC_SYMBOL("SM-CYHSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyhscroll,FIX((SI_Long)3L));
    Qsm_cycaption = STATIC_SYMBOL("SM-CYCAPTION",AB_package);
    SET_SYMBOL_VALUE(Qsm_cycaption,FIX((SI_Long)4L));
    Qsm_cxborder = STATIC_SYMBOL("SM-CXBORDER",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxborder,FIX((SI_Long)5L));
    Qsm_cyborder = STATIC_SYMBOL("SM-CYBORDER",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyborder,FIX((SI_Long)6L));
    Qsm_cxdlgframe = STATIC_SYMBOL("SM-CXDLGFRAME",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxdlgframe,FIX((SI_Long)7L));
    Qsm_cydlgframe = STATIC_SYMBOL("SM-CYDLGFRAME",AB_package);
    SET_SYMBOL_VALUE(Qsm_cydlgframe,FIX((SI_Long)8L));
    Qsm_cyvthumb = STATIC_SYMBOL("SM-CYVTHUMB",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyvthumb,FIX((SI_Long)9L));
    Qsm_cxhthumb = STATIC_SYMBOL("SM-CXHTHUMB",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxhthumb,FIX((SI_Long)10L));
    Qsm_cxicon = STATIC_SYMBOL("SM-CXICON",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxicon,FIX((SI_Long)11L));
    Qsm_cyicon = STATIC_SYMBOL("SM-CYICON",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyicon,FIX((SI_Long)12L));
    Qsm_cxcursor = STATIC_SYMBOL("SM-CXCURSOR",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxcursor,FIX((SI_Long)13L));
    Qsm_cycursor = STATIC_SYMBOL("SM-CYCURSOR",AB_package);
    SET_SYMBOL_VALUE(Qsm_cycursor,FIX((SI_Long)14L));
    Qsm_cymenu = STATIC_SYMBOL("SM-CYMENU",AB_package);
    SET_SYMBOL_VALUE(Qsm_cymenu,FIX((SI_Long)15L));
    Qsm_cxfullscreen = STATIC_SYMBOL("SM-CXFULLSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxfullscreen,FIX((SI_Long)16L));
    Qsm_cyfullscreen = STATIC_SYMBOL("SM-CYFULLSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyfullscreen,FIX((SI_Long)17L));
    Qsm_cykanjiwindow = STATIC_SYMBOL("SM-CYKANJIWINDOW",AB_package);
    SET_SYMBOL_VALUE(Qsm_cykanjiwindow,FIX((SI_Long)18L));
    Qsm_mousepresent = STATIC_SYMBOL("SM-MOUSEPRESENT",AB_package);
    SET_SYMBOL_VALUE(Qsm_mousepresent,FIX((SI_Long)19L));
    Qsm_cyvscroll = STATIC_SYMBOL("SM-CYVSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyvscroll,FIX((SI_Long)20L));
    Qsm_cxhscroll = STATIC_SYMBOL("SM-CXHSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxhscroll,FIX((SI_Long)21L));
    Qsm_debug = STATIC_SYMBOL("SM-DEBUG",AB_package);
    SET_SYMBOL_VALUE(Qsm_debug,FIX((SI_Long)22L));
    Qsm_swapbutton = STATIC_SYMBOL("SM-SWAPBUTTON",AB_package);
    SET_SYMBOL_VALUE(Qsm_swapbutton,FIX((SI_Long)23L));
    Qsm_cxmin = STATIC_SYMBOL("SM-CXMIN",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxmin,FIX((SI_Long)28L));
    Qsm_cymin = STATIC_SYMBOL("SM-CYMIN",AB_package);
    SET_SYMBOL_VALUE(Qsm_cymin,FIX((SI_Long)29L));
    Qsm_cxsize = STATIC_SYMBOL("SM-CXSIZE",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxsize,FIX((SI_Long)30L));
    Qsm_cysize = STATIC_SYMBOL("SM-CYSIZE",AB_package);
    SET_SYMBOL_VALUE(Qsm_cysize,FIX((SI_Long)31L));
    Qsm_cxframe = STATIC_SYMBOL("SM-CXFRAME",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxframe,FIX((SI_Long)32L));
    Qsm_cyframe = STATIC_SYMBOL("SM-CYFRAME",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyframe,FIX((SI_Long)33L));
    Qsm_cxmintrack = STATIC_SYMBOL("SM-CXMINTRACK",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxmintrack,FIX((SI_Long)34L));
    Qsm_cymintrack = STATIC_SYMBOL("SM-CYMINTRACK",AB_package);
    SET_SYMBOL_VALUE(Qsm_cymintrack,FIX((SI_Long)35L));
    Qsm_cxdoubleclk = STATIC_SYMBOL("SM-CXDOUBLECLK",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxdoubleclk,FIX((SI_Long)36L));
    Qsm_cydoubleclk = STATIC_SYMBOL("SM-CYDOUBLECLK",AB_package);
    SET_SYMBOL_VALUE(Qsm_cydoubleclk,FIX((SI_Long)37L));
    Qsm_cxiconspacing = STATIC_SYMBOL("SM-CXICONSPACING",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxiconspacing,FIX((SI_Long)38L));
    Qsm_cyiconspacing = STATIC_SYMBOL("SM-CYICONSPACING",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyiconspacing,FIX((SI_Long)39L));
    Qsm_menudropalignment = STATIC_SYMBOL("SM-MENUDROPALIGNMENT",AB_package);
    SET_SYMBOL_VALUE(Qsm_menudropalignment,FIX((SI_Long)40L));
    Qsm_penwindows = STATIC_SYMBOL("SM-PENWINDOWS",AB_package);
    SET_SYMBOL_VALUE(Qsm_penwindows,FIX((SI_Long)41L));
    Qsm_dbcsenabled = STATIC_SYMBOL("SM-DBCSENABLED",AB_package);
    SET_SYMBOL_VALUE(Qsm_dbcsenabled,FIX((SI_Long)42L));
    Qsm_cmousebuttons = STATIC_SYMBOL("SM-CMOUSEBUTTONS",AB_package);
    SET_SYMBOL_VALUE(Qsm_cmousebuttons,FIX((SI_Long)43L));
    Qsm_secure = STATIC_SYMBOL("SM-SECURE",AB_package);
    SET_SYMBOL_VALUE(Qsm_secure,FIX((SI_Long)44L));
    Qsm_cxedge = STATIC_SYMBOL("SM-CXEDGE",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxedge,FIX((SI_Long)45L));
    Qsm_cyedge = STATIC_SYMBOL("SM-CYEDGE",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyedge,FIX((SI_Long)46L));
    Qsm_cxminspacing = STATIC_SYMBOL("SM-CXMINSPACING",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxminspacing,FIX((SI_Long)47L));
    Qsm_cyminspacing = STATIC_SYMBOL("SM-CYMINSPACING",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyminspacing,FIX((SI_Long)48L));
    Qsm_cxsmicon = STATIC_SYMBOL("SM-CXSMICON",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxsmicon,FIX((SI_Long)49L));
    Qsm_cysmicon = STATIC_SYMBOL("SM-CYSMICON",AB_package);
    SET_SYMBOL_VALUE(Qsm_cysmicon,FIX((SI_Long)50L));
    Qsm_cysmcaption = STATIC_SYMBOL("SM-CYSMCAPTION",AB_package);
    SET_SYMBOL_VALUE(Qsm_cysmcaption,FIX((SI_Long)51L));
    Qsm_cxsmsize = STATIC_SYMBOL("SM-CXSMSIZE",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxsmsize,FIX((SI_Long)52L));
    Qsm_cysmsize = STATIC_SYMBOL("SM-CYSMSIZE",AB_package);
    SET_SYMBOL_VALUE(Qsm_cysmsize,FIX((SI_Long)53L));
    Qsm_cxmenusize = STATIC_SYMBOL("SM-CXMENUSIZE",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxmenusize,FIX((SI_Long)54L));
    Qsm_cymenusize = STATIC_SYMBOL("SM-CYMENUSIZE",AB_package);
    SET_SYMBOL_VALUE(Qsm_cymenusize,FIX((SI_Long)55L));
    Qsm_arrange = STATIC_SYMBOL("SM-ARRANGE",AB_package);
    SET_SYMBOL_VALUE(Qsm_arrange,FIX((SI_Long)56L));
    Qsm_cxminimized = STATIC_SYMBOL("SM-CXMINIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxminimized,FIX((SI_Long)57L));
    Qsm_cyminimized = STATIC_SYMBOL("SM-CYMINIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyminimized,FIX((SI_Long)58L));
    Qsm_cxmaxtrack = STATIC_SYMBOL("SM-CXMAXTRACK",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxmaxtrack,FIX((SI_Long)59L));
    Qsm_cymaxtrack = STATIC_SYMBOL("SM-CYMAXTRACK",AB_package);
    SET_SYMBOL_VALUE(Qsm_cymaxtrack,FIX((SI_Long)60L));
    Qsm_cxmaximized = STATIC_SYMBOL("SM-CXMAXIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxmaximized,FIX((SI_Long)61L));
    Qsm_cymaximized = STATIC_SYMBOL("SM-CYMAXIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qsm_cymaximized,FIX((SI_Long)62L));
    Qsm_network = STATIC_SYMBOL("SM-NETWORK",AB_package);
    SET_SYMBOL_VALUE(Qsm_network,FIX((SI_Long)63L));
    Qsm_cleanboot = STATIC_SYMBOL("SM-CLEANBOOT",AB_package);
    SET_SYMBOL_VALUE(Qsm_cleanboot,FIX((SI_Long)67L));
    Qsm_cxdrag = STATIC_SYMBOL("SM-CXDRAG",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxdrag,FIX((SI_Long)68L));
    Qsm_cydrag = STATIC_SYMBOL("SM-CYDRAG",AB_package);
    SET_SYMBOL_VALUE(Qsm_cydrag,FIX((SI_Long)69L));
    Qsm_showsounds = STATIC_SYMBOL("SM-SHOWSOUNDS",AB_package);
    SET_SYMBOL_VALUE(Qsm_showsounds,FIX((SI_Long)70L));
    Qsm_cxmenucheck = STATIC_SYMBOL("SM-CXMENUCHECK",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxmenucheck,FIX((SI_Long)71L));
    Qsm_cymenucheck = STATIC_SYMBOL("SM-CYMENUCHECK",AB_package);
    SET_SYMBOL_VALUE(Qsm_cymenucheck,FIX((SI_Long)72L));
    Qsm_slowmachine = STATIC_SYMBOL("SM-SLOWMACHINE",AB_package);
    SET_SYMBOL_VALUE(Qsm_slowmachine,FIX((SI_Long)73L));
    Qsm_mideastenabled = STATIC_SYMBOL("SM-MIDEASTENABLED",AB_package);
    SET_SYMBOL_VALUE(Qsm_mideastenabled,FIX((SI_Long)74L));
    Qsm_mousewheelpresent = STATIC_SYMBOL("SM-MOUSEWHEELPRESENT",AB_package);
    SET_SYMBOL_VALUE(Qsm_mousewheelpresent,FIX((SI_Long)75L));
    Qsm_xvirtualscreen = STATIC_SYMBOL("SM-XVIRTUALSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qsm_xvirtualscreen,FIX((SI_Long)76L));
    Qsm_yvirtualscreen = STATIC_SYMBOL("SM-YVIRTUALSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qsm_yvirtualscreen,FIX((SI_Long)77L));
    Qsm_cxvirtualscreen = STATIC_SYMBOL("SM-CXVIRTUALSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxvirtualscreen,FIX((SI_Long)78L));
    Qsm_cyvirtualscreen = STATIC_SYMBOL("SM-CYVIRTUALSCREEN",AB_package);
    SET_SYMBOL_VALUE(Qsm_cyvirtualscreen,FIX((SI_Long)79L));
    Qsm_cmonitors = STATIC_SYMBOL("SM-CMONITORS",AB_package);
    SET_SYMBOL_VALUE(Qsm_cmonitors,FIX((SI_Long)80L));
    Qsm_samedisplayformat = STATIC_SYMBOL("SM-SAMEDISPLAYFORMAT",AB_package);
    SET_SYMBOL_VALUE(Qsm_samedisplayformat,FIX((SI_Long)81L));
    Qsm_cxdialog = STATIC_SYMBOL("SM-CXDIALOG",AB_package);
    SET_SYMBOL_VALUE(Qsm_cxdialog,FIX((SI_Long)82L));
    Qsm_cydialog = STATIC_SYMBOL("SM-CYDIALOG",AB_package);
    SET_SYMBOL_VALUE(Qsm_cydialog,FIX((SI_Long)83L));
    Qnumber_of_system_metrics = STATIC_SYMBOL("NUMBER-OF-SYSTEM-METRICS",
	    AB_package);
    SET_SYMBOL_VALUE(Qnumber_of_system_metrics,FIX((SI_Long)84L));
    Qmaximum_interval_between_new_time_for_uuid = 
	    STATIC_SYMBOL("MAXIMUM-INTERVAL-BETWEEN-NEW-TIME-FOR-UUID",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_interval_between_new_time_for_uuid,
	    Maximum_interval_between_new_time_for_uuid);
    float_constant_2 = STATIC_FLOAT(600.0);
    SET_SYMBOL_VALUE(Qmaximum_interval_between_new_time_for_uuid,
	    float_constant_2);
    Quuid_offset_mask = STATIC_SYMBOL("UUID-OFFSET-MASK",AB_package);
    SET_SYMBOL_VALUE(Quuid_offset_mask,FIX((SI_Long)255L));
    Qne_blocked_value = STATIC_SYMBOL("NE-BLOCKED-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qne_blocked_value,FIX((SI_Long)0L));
    Qne_eof_value = STATIC_SYMBOL("NE-EOF-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qne_eof_value,FIX((SI_Long)-1L));
    Qne_error_value = STATIC_SYMBOL("NE-ERROR-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qne_error_value,FIX((SI_Long)-2L));
    Qminimum_message_series_size_before_suspending = 
	    STATIC_SYMBOL("MINIMUM-MESSAGE-SERIES-SIZE-BEFORE-SUSPENDING",
	    AB_package);
    SET_SYMBOL_VALUE(Qminimum_message_series_size_before_suspending,
	    FIX((SI_Long)8000L));
    Qminimum_message_series_size_before_beginning_new_series = 
	    STATIC_SYMBOL("MINIMUM-MESSAGE-SERIES-SIZE-BEFORE-BEGINNING-NEW-SERIES",
	    AB_package);
    SET_SYMBOL_VALUE(Qminimum_message_series_size_before_beginning_new_series,
	    FIX((SI_Long)20000L));
    Quse_all_network_protocols = STATIC_SYMBOL("USE-ALL-NETWORK-PROTOCOLS",
	    AB_package);
    SET_SYMBOL_VALUE(Quse_all_network_protocols,FIX((SI_Long)14L));
    Quse_tcpip_protocol_only = STATIC_SYMBOL("USE-TCPIP-PROTOCOL-ONLY",
	    AB_package);
    SET_SYMBOL_VALUE(Quse_tcpip_protocol_only,FIX((SI_Long)13L));
    Quse_no_network_protocols = STATIC_SYMBOL("USE-NO-NETWORK-PROTOCOLS",
	    AB_package);
    SET_SYMBOL_VALUE(Quse_no_network_protocols,FIX((SI_Long)-1L));
    Qg2_product_tag = STATIC_SYMBOL("G2-PRODUCT-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2_product_tag,FIX((SI_Long)1L));
    Qgsi_product_tag = STATIC_SYMBOL("GSI-PRODUCT-TAG",AB_package);
    SET_SYMBOL_VALUE(Qgsi_product_tag,FIX((SI_Long)2L));
    Qminimum_intensity_for_white = 
	    STATIC_SYMBOL("MINIMUM-INTENSITY-FOR-WHITE",AB_package);
    SET_SYMBOL_VALUE(Qminimum_intensity_for_white,FIX((SI_Long)192L));
    Qtransparent_color_value = STATIC_SYMBOL("TRANSPARENT-COLOR-VALUE",
	    AB_package);
    SET_SYMBOL_VALUE(Qtransparent_color_value,FIX((SI_Long)16777216L));
    Qno_stipple_value = STATIC_SYMBOL("NO-STIPPLE-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qno_stipple_value,FIX((SI_Long)0L));
    Qps_solid = STATIC_SYMBOL("PS-SOLID",AB_package);
    SET_SYMBOL_VALUE(Qps_solid,FIX((SI_Long)0L));
    Qps_dash = STATIC_SYMBOL("PS-DASH",AB_package);
    SET_SYMBOL_VALUE(Qps_dash,FIX((SI_Long)1L));
    Qps_dot = STATIC_SYMBOL("PS-DOT",AB_package);
    SET_SYMBOL_VALUE(Qps_dot,FIX((SI_Long)2L));
    Qps_dashdot = STATIC_SYMBOL("PS-DASHDOT",AB_package);
    SET_SYMBOL_VALUE(Qps_dashdot,FIX((SI_Long)3L));
    Qps_dashdotdot = STATIC_SYMBOL("PS-DASHDOTDOT",AB_package);
    SET_SYMBOL_VALUE(Qps_dashdotdot,FIX((SI_Long)4L));
    Qps_userstyle = STATIC_SYMBOL("PS-USERSTYLE",AB_package);
    SET_SYMBOL_VALUE(Qps_userstyle,FIX((SI_Long)7L));
    Qps_endcap_round = STATIC_SYMBOL("PS-ENDCAP-ROUND",AB_package);
    SET_SYMBOL_VALUE(Qps_endcap_round,FIX((SI_Long)0L));
    Qps_endcap_square = STATIC_SYMBOL("PS-ENDCAP-SQUARE",AB_package);
    SET_SYMBOL_VALUE(Qps_endcap_square,FIX((SI_Long)256L));
    Qps_endcap_flat = STATIC_SYMBOL("PS-ENDCAP-FLAT",AB_package);
    SET_SYMBOL_VALUE(Qps_endcap_flat,FIX((SI_Long)512L));
    Qps_join_round = STATIC_SYMBOL("PS-JOIN-ROUND",AB_package);
    SET_SYMBOL_VALUE(Qps_join_round,FIX((SI_Long)0L));
    Qps_join_bevel = STATIC_SYMBOL("PS-JOIN-BEVEL",AB_package);
    SET_SYMBOL_VALUE(Qps_join_bevel,FIX((SI_Long)4096L));
    Qps_join_miter = STATIC_SYMBOL("PS-JOIN-MITER",AB_package);
    SET_SYMBOL_VALUE(Qps_join_miter,FIX((SI_Long)8192L));
    Qenable_offscreen_drawing = STATIC_SYMBOL("ENABLE-OFFSCREEN-DRAWING",
	    AB_package);
    SET_SYMBOL_VALUE(Qenable_offscreen_drawing,FIX((SI_Long)1L));
    Qdisable_offscreen_drawing = STATIC_SYMBOL("DISABLE-OFFSCREEN-DRAWING",
	    AB_package);
    SET_SYMBOL_VALUE(Qdisable_offscreen_drawing,FIX((SI_Long)2L));
    Qbitblt_offscreen_pixmap = STATIC_SYMBOL("BITBLT-OFFSCREEN-PIXMAP",
	    AB_package);
    SET_SYMBOL_VALUE(Qbitblt_offscreen_pixmap,FIX((SI_Long)3L));
    Qreclaim_offscreen_pixmap = STATIC_SYMBOL("RECLAIM-OFFSCREEN-PIXMAP",
	    AB_package);
    SET_SYMBOL_VALUE(Qreclaim_offscreen_pixmap,FIX((SI_Long)4L));
    Qframe_type_none = STATIC_SYMBOL("FRAME-TYPE-NONE",AB_package);
    SET_SYMBOL_VALUE(Qframe_type_none,FIX((SI_Long)0L));
    Qframe_type_classic = STATIC_SYMBOL("FRAME-TYPE-CLASSIC",AB_package);
    SET_SYMBOL_VALUE(Qframe_type_classic,FIX((SI_Long)1L));
    Qframe_type_child = STATIC_SYMBOL("FRAME-TYPE-CHILD",AB_package);
    SET_SYMBOL_VALUE(Qframe_type_child,FIX((SI_Long)2L));
    Qframe_type_sdi = STATIC_SYMBOL("FRAME-TYPE-SDI",AB_package);
    SET_SYMBOL_VALUE(Qframe_type_sdi,FIX((SI_Long)3L));
    Qframe_type_mdi = STATIC_SYMBOL("FRAME-TYPE-MDI",AB_package);
    SET_SYMBOL_VALUE(Qframe_type_mdi,FIX((SI_Long)4L));
    Qnip_wintype_classic = STATIC_SYMBOL("NIP-WINTYPE-CLASSIC",AB_package);
    SET_SYMBOL_VALUE(Qnip_wintype_classic,FIX((SI_Long)0L));
    Qnip_wintype_mask = STATIC_SYMBOL("NIP-WINTYPE-MASK",AB_package);
    SET_SYMBOL_VALUE(Qnip_wintype_mask,FIX((SI_Long)15L));
    Qnip_show_window = STATIC_SYMBOL("NIP-SHOW-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_show_window,FIX((SI_Long)1L));
    Qnip_move_window = STATIC_SYMBOL("NIP-MOVE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_move_window,FIX((SI_Long)2L));
    Qnip_reshape_window = STATIC_SYMBOL("NIP-RESHAPE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_reshape_window,FIX((SI_Long)3L));
    Qnip_raise_window = STATIC_SYMBOL("NIP-RAISE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_raise_window,FIX((SI_Long)4L));
    Qnip_lower_window = STATIC_SYMBOL("NIP-LOWER-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_lower_window,FIX((SI_Long)5L));
    Qnip_destroy_window = STATIC_SYMBOL("NIP-DESTROY-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_destroy_window,FIX((SI_Long)6L));
    Qnip_caption_window = STATIC_SYMBOL("NIP-CAPTION-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_caption_window,FIX((SI_Long)7L));
    Qnip_inflate_window = STATIC_SYMBOL("NIP-INFLATE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_inflate_window,FIX((SI_Long)8L));
    Qnip_scroll_window = STATIC_SYMBOL("NIP-SCROLL-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_scroll_window,FIX((SI_Long)9L));
    Qnip_cerase_window = STATIC_SYMBOL("NIP-CERASE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_cerase_window,FIX((SI_Long)10L));
    Qnip_set_max_size = STATIC_SYMBOL("NIP-SET-MAX-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qnip_set_max_size,FIX((SI_Long)11L));
    Qnip_restyle_window = STATIC_SYMBOL("NIP-RESTYLE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_restyle_window,FIX((SI_Long)12L));
    Qnip_zorder_window = STATIC_SYMBOL("NIP-ZORDER-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_zorder_window,FIX((SI_Long)13L));
    Qnip_set_icon = STATIC_SYMBOL("NIP-SET-ICON",AB_package);
    SET_SYMBOL_VALUE(Qnip_set_icon,FIX((SI_Long)14L));
    Qnip_set_closeable = STATIC_SYMBOL("NIP-SET-CLOSEABLE",AB_package);
    SET_SYMBOL_VALUE(Qnip_set_closeable,FIX((SI_Long)15L));
    Qnip_rescale_window = STATIC_SYMBOL("NIP-RESCALE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_rescale_window,FIX((SI_Long)16L));
    Qnip_set_background_color = STATIC_SYMBOL("NIP-SET-BACKGROUND-COLOR",
	    AB_package);
    SET_SYMBOL_VALUE(Qnip_set_background_color,FIX((SI_Long)17L));
    Qnip_size_window = STATIC_SYMBOL("NIP-SIZE-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qnip_size_window,FIX((SI_Long)18L));
    Qsw_hide = STATIC_SYMBOL("SW-HIDE",AB_package);
    SET_SYMBOL_VALUE(Qsw_hide,FIX((SI_Long)0L));
    Qsw_shownormal = STATIC_SYMBOL("SW-SHOWNORMAL",AB_package);
    SET_SYMBOL_VALUE(Qsw_shownormal,FIX((SI_Long)1L));
    Qsw_showminimized = STATIC_SYMBOL("SW-SHOWMINIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qsw_showminimized,FIX((SI_Long)2L));
    Qsw_maximize = STATIC_SYMBOL("SW-MAXIMIZE",AB_package);
    SET_SYMBOL_VALUE(Qsw_maximize,FIX((SI_Long)3L));
    Qsw_shownoactivate = STATIC_SYMBOL("SW-SHOWNOACTIVATE",AB_package);
    SET_SYMBOL_VALUE(Qsw_shownoactivate,FIX((SI_Long)4L));
    Qsw_show = STATIC_SYMBOL("SW-SHOW",AB_package);
    SET_SYMBOL_VALUE(Qsw_show,FIX((SI_Long)5L));
    Qsw_minimize = STATIC_SYMBOL("SW-MINIMIZE",AB_package);
    SET_SYMBOL_VALUE(Qsw_minimize,FIX((SI_Long)6L));
    Qsw_showminnoactive = STATIC_SYMBOL("SW-SHOWMINNOACTIVE",AB_package);
    SET_SYMBOL_VALUE(Qsw_showminnoactive,FIX((SI_Long)7L));
    Qsw_showna = STATIC_SYMBOL("SW-SHOWNA",AB_package);
    SET_SYMBOL_VALUE(Qsw_showna,FIX((SI_Long)8L));
    Qsw_restore = STATIC_SYMBOL("SW-RESTORE",AB_package);
    SET_SYMBOL_VALUE(Qsw_restore,FIX((SI_Long)9L));
    Qsw_showdefault = STATIC_SYMBOL("SW-SHOWDEFAULT",AB_package);
    SET_SYMBOL_VALUE(Qsw_showdefault,FIX((SI_Long)10L));
    Qws_overlapped = STATIC_SYMBOL("WS-OVERLAPPED",AB_package);
    SET_SYMBOL_VALUE(Qws_overlapped,FIX((SI_Long)0L));
    Qws_popup = STATIC_SYMBOL("WS-POPUP",AB_package);
    SET_SYMBOL_VALUE(Qws_popup,FIX((SI_Long)32768L));
    Qws_child = STATIC_SYMBOL("WS-CHILD",AB_package);
    SET_SYMBOL_VALUE(Qws_child,FIX((SI_Long)16384L));
    Qws_minimize = STATIC_SYMBOL("WS-MINIMIZE",AB_package);
    SET_SYMBOL_VALUE(Qws_minimize,FIX((SI_Long)8192L));
    Qws_visible = STATIC_SYMBOL("WS-VISIBLE",AB_package);
    SET_SYMBOL_VALUE(Qws_visible,FIX((SI_Long)4096L));
    Qws_disabled = STATIC_SYMBOL("WS-DISABLED",AB_package);
    SET_SYMBOL_VALUE(Qws_disabled,FIX((SI_Long)2048L));
    Qws_clipsiblings = STATIC_SYMBOL("WS-CLIPSIBLINGS",AB_package);
    SET_SYMBOL_VALUE(Qws_clipsiblings,FIX((SI_Long)1024L));
    Qws_clipchildren = STATIC_SYMBOL("WS-CLIPCHILDREN",AB_package);
    SET_SYMBOL_VALUE(Qws_clipchildren,FIX((SI_Long)512L));
    Qws_maximize = STATIC_SYMBOL("WS-MAXIMIZE",AB_package);
    SET_SYMBOL_VALUE(Qws_maximize,FIX((SI_Long)256L));
    Qws_caption = STATIC_SYMBOL("WS-CAPTION",AB_package);
    SET_SYMBOL_VALUE(Qws_caption,FIX((SI_Long)192L));
    Qws_border = STATIC_SYMBOL("WS-BORDER",AB_package);
    SET_SYMBOL_VALUE(Qws_border,FIX((SI_Long)128L));
    Qws_dlgframe = STATIC_SYMBOL("WS-DLGFRAME",AB_package);
    SET_SYMBOL_VALUE(Qws_dlgframe,FIX((SI_Long)64L));
    Qws_vscroll = STATIC_SYMBOL("WS-VSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qws_vscroll,FIX((SI_Long)32L));
    Qws_hscroll = STATIC_SYMBOL("WS-HSCROLL",AB_package);
    SET_SYMBOL_VALUE(Qws_hscroll,FIX((SI_Long)16L));
    Qws_sysmenu = STATIC_SYMBOL("WS-SYSMENU",AB_package);
    SET_SYMBOL_VALUE(Qws_sysmenu,FIX((SI_Long)8L));
    Qws_thickframe = STATIC_SYMBOL("WS-THICKFRAME",AB_package);
    SET_SYMBOL_VALUE(Qws_thickframe,FIX((SI_Long)4L));
    Qws_group = STATIC_SYMBOL("WS-GROUP",AB_package);
    SET_SYMBOL_VALUE(Qws_group,FIX((SI_Long)2L));
    Qws_tabstop = STATIC_SYMBOL("WS-TABSTOP",AB_package);
    SET_SYMBOL_VALUE(Qws_tabstop,FIX((SI_Long)1L));
    Qws_minimizebox = STATIC_SYMBOL("WS-MINIMIZEBOX",AB_package);
    SET_SYMBOL_VALUE(Qws_minimizebox,FIX((SI_Long)2L));
    Qws_maximizebox = STATIC_SYMBOL("WS-MAXIMIZEBOX",AB_package);
    SET_SYMBOL_VALUE(Qws_maximizebox,FIX((SI_Long)1L));
    Qws_ex_dlgmodalframe = STATIC_SYMBOL("WS-EX-DLGMODALFRAME",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_dlgmodalframe,FIX((SI_Long)1L));
    Qws_ex_noparentnotify = STATIC_SYMBOL("WS-EX-NOPARENTNOTIFY",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_noparentnotify,FIX((SI_Long)4L));
    Qws_ex_topmost = STATIC_SYMBOL("WS-EX-TOPMOST",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_topmost,FIX((SI_Long)8L));
    Qws_ex_acceptfiles = STATIC_SYMBOL("WS-EX-ACCEPTFILES",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_acceptfiles,FIX((SI_Long)16L));
    Qws_ex_transparent = STATIC_SYMBOL("WS-EX-TRANSPARENT",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_transparent,FIX((SI_Long)32L));
    Qws_ex_mdichild = STATIC_SYMBOL("WS-EX-MDICHILD",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_mdichild,FIX((SI_Long)64L));
    Qws_ex_toolwindow = STATIC_SYMBOL("WS-EX-TOOLWINDOW",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_toolwindow,FIX((SI_Long)128L));
    Qws_ex_windowedge = STATIC_SYMBOL("WS-EX-WINDOWEDGE",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_windowedge,FIX((SI_Long)256L));
    Qws_ex_clientedge = STATIC_SYMBOL("WS-EX-CLIENTEDGE",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_clientedge,FIX((SI_Long)512L));
    Qws_ex_contexthelp = STATIC_SYMBOL("WS-EX-CONTEXTHELP",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_contexthelp,FIX((SI_Long)1024L));
    Qws_ex_right = STATIC_SYMBOL("WS-EX-RIGHT",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_right,FIX((SI_Long)4096L));
    Qws_ex_left = STATIC_SYMBOL("WS-EX-LEFT",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_left,FIX((SI_Long)0L));
    Qws_ex_rtlreading = STATIC_SYMBOL("WS-EX-RTLREADING",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_rtlreading,FIX((SI_Long)8192L));
    Qws_ex_ltrreading = STATIC_SYMBOL("WS-EX-LTRREADING",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_ltrreading,FIX((SI_Long)0L));
    Qws_ex_leftscrollbar = STATIC_SYMBOL("WS-EX-LEFTSCROLLBAR",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_leftscrollbar,FIX((SI_Long)16384L));
    Qws_ex_rightscrollbar = STATIC_SYMBOL("WS-EX-RIGHTSCROLLBAR",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_rightscrollbar,FIX((SI_Long)0L));
    Qws_ex_controlparent = STATIC_SYMBOL("WS-EX-CONTROLPARENT",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_controlparent,FIX((SI_Long)65536L));
    Qws_ex_staticedge = STATIC_SYMBOL("WS-EX-STATICEDGE",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_staticedge,FIX((SI_Long)131072L));
    Qws_ex_appwindow = STATIC_SYMBOL("WS-EX-APPWINDOW",AB_package);
    SET_SYMBOL_VALUE(Qws_ex_appwindow,FIX((SI_Long)262144L));
    Qsize_restored = STATIC_SYMBOL("SIZE-RESTORED",AB_package);
    SET_SYMBOL_VALUE(Qsize_restored,FIX((SI_Long)0L));
    Qsize_minimized = STATIC_SYMBOL("SIZE-MINIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qsize_minimized,FIX((SI_Long)1L));
    Qsize_maximized = STATIC_SYMBOL("SIZE-MAXIMIZED",AB_package);
    SET_SYMBOL_VALUE(Qsize_maximized,FIX((SI_Long)2L));
    Qsize_maxshow = STATIC_SYMBOL("SIZE-MAXSHOW",AB_package);
    SET_SYMBOL_VALUE(Qsize_maxshow,FIX((SI_Long)3L));
    Qsize_maxhide = STATIC_SYMBOL("SIZE-MAXHIDE",AB_package);
    SET_SYMBOL_VALUE(Qsize_maxhide,FIX((SI_Long)4L));
    Qstatus_floated = STATIC_SYMBOL("STATUS-FLOATED",AB_package);
    SET_SYMBOL_VALUE(Qstatus_floated,FIX((SI_Long)8L));
    Qstatus_docked = STATIC_SYMBOL("STATUS-DOCKED",AB_package);
    SET_SYMBOL_VALUE(Qstatus_docked,FIX((SI_Long)9L));
    Qstatus_autohidden = STATIC_SYMBOL("STATUS-AUTOHIDDEN",AB_package);
    SET_SYMBOL_VALUE(Qstatus_autohidden,FIX((SI_Long)10L));
    Qstatus_unknown = STATIC_SYMBOL("STATUS-UNKNOWN",AB_package);
    SET_SYMBOL_VALUE(Qstatus_unknown,FIX((SI_Long)11L));
    Qstatus_expanded = STATIC_SYMBOL("STATUS-EXPANDED",AB_package);
    SET_SYMBOL_VALUE(Qstatus_expanded,FIX((SI_Long)12L));
    Qstatus_collapsed = STATIC_SYMBOL("STATUS-COLLAPSED",AB_package);
    SET_SYMBOL_VALUE(Qstatus_collapsed,FIX((SI_Long)13L));
    Qstatus_closed = STATIC_SYMBOL("STATUS-CLOSED",AB_package);
    SET_SYMBOL_VALUE(Qstatus_closed,FIX((SI_Long)14L));
    Qstatus_attached = STATIC_SYMBOL("STATUS-ATTACHED",AB_package);
    SET_SYMBOL_VALUE(Qstatus_attached,FIX((SI_Long)15L));
    Qstatus_docked_left = STATIC_SYMBOL("STATUS-DOCKED-LEFT",AB_package);
    SET_SYMBOL_VALUE(Qstatus_docked_left,FIX((SI_Long)16L));
    Qstatus_docked_top = STATIC_SYMBOL("STATUS-DOCKED-TOP",AB_package);
    SET_SYMBOL_VALUE(Qstatus_docked_top,FIX((SI_Long)17L));
    Qstatus_docked_right = STATIC_SYMBOL("STATUS-DOCKED-RIGHT",AB_package);
    SET_SYMBOL_VALUE(Qstatus_docked_right,FIX((SI_Long)18L));
    Qstatus_docked_bottom = STATIC_SYMBOL("STATUS-DOCKED-BOTTOM",AB_package);
    SET_SYMBOL_VALUE(Qstatus_docked_bottom,FIX((SI_Long)19L));
    Qstatus_hidden = STATIC_SYMBOL("STATUS-HIDDEN",AB_package);
    SET_SYMBOL_VALUE(Qstatus_hidden,FIX((SI_Long)20L));
    Qcw_usedefault = STATIC_SYMBOL("CW-USEDEFAULT",AB_package);
    SET_SYMBOL_VALUE(Qcw_usedefault,FIX((SI_Long)-30000L));
    Qsort_column_default = STATIC_SYMBOL("SORT-COLUMN-DEFAULT",AB_package);
    SET_SYMBOL_VALUE(Qsort_column_default,FIX((SI_Long)-1L));
    Qsorting_order_default = STATIC_SYMBOL("SORTING-ORDER-DEFAULT",AB_package);
    SET_SYMBOL_VALUE(Qsorting_order_default,FIX((SI_Long)1L));
    Qswp_hwnd_top = STATIC_SYMBOL("SWP-HWND-TOP",AB_package);
    SET_SYMBOL_VALUE(Qswp_hwnd_top,FIX((SI_Long)-1L));
    Qswp_hwnd_bottom = STATIC_SYMBOL("SWP-HWND-BOTTOM",AB_package);
    SET_SYMBOL_VALUE(Qswp_hwnd_bottom,FIX((SI_Long)-2L));
    Qswp_hwnd_topmost = STATIC_SYMBOL("SWP-HWND-TOPMOST",AB_package);
    SET_SYMBOL_VALUE(Qswp_hwnd_topmost,FIX((SI_Long)-3L));
    Qswp_hwnd_notopmost = STATIC_SYMBOL("SWP-HWND-NOTOPMOST",AB_package);
    SET_SYMBOL_VALUE(Qswp_hwnd_notopmost,FIX((SI_Long)-4L));
    Qdt_left = STATIC_SYMBOL("DT-LEFT",AB_package);
    SET_SYMBOL_VALUE(Qdt_left,FIX((SI_Long)0L));
    Qdt_center = STATIC_SYMBOL("DT-CENTER",AB_package);
    SET_SYMBOL_VALUE(Qdt_center,FIX((SI_Long)1L));
    Qdt_right = STATIC_SYMBOL("DT-RIGHT",AB_package);
    SET_SYMBOL_VALUE(Qdt_right,FIX((SI_Long)2L));
    Qdt_vcenter = STATIC_SYMBOL("DT-VCENTER",AB_package);
    SET_SYMBOL_VALUE(Qdt_vcenter,FIX((SI_Long)4L));
    Qdt_bottom = STATIC_SYMBOL("DT-BOTTOM",AB_package);
    SET_SYMBOL_VALUE(Qdt_bottom,FIX((SI_Long)8L));
    Qdt_wordbreak = STATIC_SYMBOL("DT-WORDBREAK",AB_package);
    SET_SYMBOL_VALUE(Qdt_wordbreak,FIX((SI_Long)16L));
    Qdt_singleline = STATIC_SYMBOL("DT-SINGLELINE",AB_package);
    SET_SYMBOL_VALUE(Qdt_singleline,FIX((SI_Long)32L));
    Qdt_expandtabs = STATIC_SYMBOL("DT-EXPANDTABS",AB_package);
    SET_SYMBOL_VALUE(Qdt_expandtabs,FIX((SI_Long)64L));
    Qdt_editcontrol = STATIC_SYMBOL("DT-EDITCONTROL",AB_package);
    SET_SYMBOL_VALUE(Qdt_editcontrol,FIX((SI_Long)8192L));
    Qdt_path_ellipsis = STATIC_SYMBOL("DT-PATH-ELLIPSIS",AB_package);
    SET_SYMBOL_VALUE(Qdt_path_ellipsis,FIX((SI_Long)16384L));
    Qdt_end_ellipsis = STATIC_SYMBOL("DT-END-ELLIPSIS",AB_package);
    SET_SYMBOL_VALUE(Qdt_end_ellipsis,FIX((SI_Long)32768L));
    Qeditor_create = STATIC_SYMBOL("EDITOR-CREATE",AB_package);
    SET_SYMBOL_VALUE(Qeditor_create,FIX((SI_Long)1L));
    Qeditor_destroy = STATIC_SYMBOL("EDITOR-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qeditor_destroy,FIX((SI_Long)2L));
    Qeditor_print = STATIC_SYMBOL("EDITOR-PRINT",AB_package);
    SET_SYMBOL_VALUE(Qeditor_print,FIX((SI_Long)3L));
    Qeditor_show = STATIC_SYMBOL("EDITOR-SHOW",AB_package);
    SET_SYMBOL_VALUE(Qeditor_show,FIX((SI_Long)4L));
    Qeditor_modal = STATIC_SYMBOL("EDITOR-MODAL",AB_package);
    SET_SYMBOL_VALUE(Qeditor_modal,FIX((SI_Long)5L));
    Qeditor_add_toolbar_button = STATIC_SYMBOL("EDITOR-ADD-TOOLBAR-BUTTON",
	    AB_package);
    SET_SYMBOL_VALUE(Qeditor_add_toolbar_button,FIX((SI_Long)6L));
    Qeditor_cancel = STATIC_SYMBOL("EDITOR-CANCEL",AB_package);
    SET_SYMBOL_VALUE(Qeditor_cancel,FIX((SI_Long)7L));
    Qeditor_clear_breakpoint = STATIC_SYMBOL("EDITOR-CLEAR-BREAKPOINT",
	    AB_package);
    SET_SYMBOL_VALUE(Qeditor_clear_breakpoint,FIX((SI_Long)20L));
    Qeditor_disable_breakpoint = STATIC_SYMBOL("EDITOR-DISABLE-BREAKPOINT",
	    AB_package);
    SET_SYMBOL_VALUE(Qeditor_disable_breakpoint,FIX((SI_Long)21L));
    Qeditor_set_breakpoint = STATIC_SYMBOL("EDITOR-SET-BREAKPOINT",AB_package);
    SET_SYMBOL_VALUE(Qeditor_set_breakpoint,FIX((SI_Long)22L));
    Qeditor_clear_breakpoints = STATIC_SYMBOL("EDITOR-CLEAR-BREAKPOINTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qeditor_clear_breakpoints,FIX((SI_Long)24L));
    Qeditor_syntax_repair = STATIC_SYMBOL("EDITOR-SYNTAX-REPAIR",AB_package);
    SET_SYMBOL_VALUE(Qeditor_syntax_repair,FIX((SI_Long)28L));
    Qeditor_reset = STATIC_SYMBOL("EDITOR-RESET",AB_package);
    SET_SYMBOL_VALUE(Qeditor_reset,FIX((SI_Long)30L));
    Qeditor_set_text = STATIC_SYMBOL("EDITOR-SET-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qeditor_set_text,FIX((SI_Long)31L));
    Qeditor_insert_text = STATIC_SYMBOL("EDITOR-INSERT-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qeditor_insert_text,FIX((SI_Long)32L));
    Qeditor_syntax = STATIC_SYMBOL("EDITOR-SYNTAX",AB_package);
    SET_SYMBOL_VALUE(Qeditor_syntax,FIX((SI_Long)33L));
    Qeditor_completions = STATIC_SYMBOL("EDITOR-COMPLETIONS",AB_package);
    SET_SYMBOL_VALUE(Qeditor_completions,FIX((SI_Long)34L));
    Qeditor_arglist = STATIC_SYMBOL("EDITOR-ARGLIST",AB_package);
    SET_SYMBOL_VALUE(Qeditor_arglist,FIX((SI_Long)35L));
    Qeditor_exit = STATIC_SYMBOL("EDITOR-EXIT",AB_package);
    SET_SYMBOL_VALUE(Qeditor_exit,FIX((SI_Long)36L));
    Qeditor_notes = STATIC_SYMBOL("EDITOR-NOTES",AB_package);
    SET_SYMBOL_VALUE(Qeditor_notes,FIX((SI_Long)37L));
    Qeditor_apply = STATIC_SYMBOL("EDITOR-APPLY",AB_package);
    SET_SYMBOL_VALUE(Qeditor_apply,FIX((SI_Long)38L));
    Qeditor_disable = STATIC_SYMBOL("EDITOR-DISABLE",AB_package);
    SET_SYMBOL_VALUE(Qeditor_disable,FIX((SI_Long)39L));
    Qeditor_enable = STATIC_SYMBOL("EDITOR-ENABLE",AB_package);
    SET_SYMBOL_VALUE(Qeditor_enable,FIX((SI_Long)40L));
    Qeditor_set_grammar = STATIC_SYMBOL("EDITOR-SET-GRAMMAR",AB_package);
    SET_SYMBOL_VALUE(Qeditor_set_grammar,FIX((SI_Long)41L));
    Qeditor_set_options = STATIC_SYMBOL("EDITOR-SET-OPTIONS",AB_package);
    SET_SYMBOL_VALUE(Qeditor_set_options,FIX((SI_Long)42L));
    Qeditor_set_tabs = STATIC_SYMBOL("EDITOR-SET-TABS",AB_package);
    SET_SYMBOL_VALUE(Qeditor_set_tabs,FIX((SI_Long)43L));
    Qeditor_cursor_moved = STATIC_SYMBOL("EDITOR-CURSOR-MOVED",AB_package);
    SET_SYMBOL_VALUE(Qeditor_cursor_moved,FIX((SI_Long)44L));
    Qeditor_text_inserted = STATIC_SYMBOL("EDITOR-TEXT-INSERTED",AB_package);
    SET_SYMBOL_VALUE(Qeditor_text_inserted,FIX((SI_Long)45L));
    Qeditor_text_deleted = STATIC_SYMBOL("EDITOR-TEXT-DELETED",AB_package);
    SET_SYMBOL_VALUE(Qeditor_text_deleted,FIX((SI_Long)46L));
    Qeditor_incremental_updates = 
	    STATIC_SYMBOL("EDITOR-INCREMENTAL-UPDATES",AB_package);
    SET_SYMBOL_VALUE(Qeditor_incremental_updates,FIX((SI_Long)47L));
    Qeditor_exit_new = STATIC_SYMBOL("EDITOR-EXIT-NEW",AB_package);
    SET_SYMBOL_VALUE(Qeditor_exit_new,FIX((SI_Long)48L));
    Qeditor_apply_new = STATIC_SYMBOL("EDITOR-APPLY-NEW",AB_package);
    SET_SYMBOL_VALUE(Qeditor_apply_new,FIX((SI_Long)49L));
    Qeditor_completions_new = STATIC_SYMBOL("EDITOR-COMPLETIONS-NEW",
	    AB_package);
    SET_SYMBOL_VALUE(Qeditor_completions_new,FIX((SI_Long)50L));
    Qeditor_clear_output = STATIC_SYMBOL("EDITOR-CLEAR-OUTPUT",AB_package);
    SET_SYMBOL_VALUE(Qeditor_clear_output,FIX((SI_Long)51L));
    Qeditor_append_output = STATIC_SYMBOL("EDITOR-APPEND-OUTPUT",AB_package);
    SET_SYMBOL_VALUE(Qeditor_append_output,FIX((SI_Long)52L));
    Qeditor_hotspot_clicked = STATIC_SYMBOL("EDITOR-HOTSPOT-CLICKED",
	    AB_package);
    SET_SYMBOL_VALUE(Qeditor_hotspot_clicked,FIX((SI_Long)53L));
    Qeditor_replace_text = STATIC_SYMBOL("EDITOR-REPLACE-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qeditor_replace_text,FIX((SI_Long)54L));
    Qeditor_delete_text = STATIC_SYMBOL("EDITOR-DELETE-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qeditor_delete_text,FIX((SI_Long)55L));
    Qeditor_text_saved = STATIC_SYMBOL("EDITOR-TEXT-SAVED",AB_package);
    SET_SYMBOL_VALUE(Qeditor_text_saved,FIX((SI_Long)56L));
    Qeditor_goto_item = STATIC_SYMBOL("EDITOR-GOTO-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qeditor_goto_item,FIX((SI_Long)58L));
    Qeditor_beep = STATIC_SYMBOL("EDITOR-BEEP",AB_package);
    SET_SYMBOL_VALUE(Qeditor_beep,FIX((SI_Long)59L));
    Qeditor_custom_toolbar = STATIC_SYMBOL("EDITOR-CUSTOM-TOOLBAR",AB_package);
    SET_SYMBOL_VALUE(Qeditor_custom_toolbar,FIX((SI_Long)60L));
    Qeditor_undo = STATIC_SYMBOL("EDITOR-UNDO",AB_package);
    SET_SYMBOL_VALUE(Qeditor_undo,FIX((SI_Long)61L));
    Qeditor_maximum_number_of_undos_to_remember = 
	    STATIC_SYMBOL("EDITOR-MAXIMUM-NUMBER-OF-UNDOS-TO-REMEMBER",
	    AB_package);
    SET_SYMBOL_VALUE(Qeditor_maximum_number_of_undos_to_remember,
	    FIX((SI_Long)62L));
    Qeditor_grammar_free_text = STATIC_SYMBOL("EDITOR-GRAMMAR-FREE-TEXT",
	    AB_package);
    SET_SYMBOL_VALUE(Qeditor_grammar_free_text,FIX((SI_Long)0L));
    Qeditor_grammar_procedure_sl_rule = 
	    STATIC_SYMBOL("EDITOR-GRAMMAR-PROCEDURE/RULE",AB_package);
    SET_SYMBOL_VALUE(Qeditor_grammar_procedure_sl_rule,FIX((SI_Long)1L));
    Qeditor_style_normal = STATIC_SYMBOL("EDITOR-STYLE-NORMAL",AB_package);
    SET_SYMBOL_VALUE(Qeditor_style_normal,FIX((SI_Long)0L));
    Qeditor_style_category = STATIC_SYMBOL("EDITOR-STYLE-CATEGORY",AB_package);
    SET_SYMBOL_VALUE(Qeditor_style_category,FIX((SI_Long)1L));
    Qeditor_style_completion = STATIC_SYMBOL("EDITOR-STYLE-COMPLETION",
	    AB_package);
    SET_SYMBOL_VALUE(Qeditor_style_completion,FIX((SI_Long)2L));
    Qeditor_options_single_line_comments = 
	    STATIC_SYMBOL("EDITOR-OPTIONS-SINGLE-LINE-COMMENTS",AB_package);
    SET_SYMBOL_VALUE(Qeditor_options_single_line_comments,FIX((SI_Long)1L));
    Qeditor_options_single_line_editor = 
	    STATIC_SYMBOL("EDITOR-OPTIONS-SINGLE-LINE-EDITOR",AB_package);
    SET_SYMBOL_VALUE(Qeditor_options_single_line_editor,FIX((SI_Long)2L));
    Qeditor_options_query_on_close = 
	    STATIC_SYMBOL("EDITOR-OPTIONS-QUERY-ON-CLOSE",AB_package);
    SET_SYMBOL_VALUE(Qeditor_options_query_on_close,FIX((SI_Long)4L));
    Qblack_threshold_in_color_intensity = 
	    STATIC_SYMBOL("BLACK-THRESHOLD-IN-COLOR-INTENSITY",AB_package);
    SET_SYMBOL_VALUE(Qblack_threshold_in_color_intensity,FIX((SI_Long)128L));
    Qnumber_of_bits_of_gray_in_the_extended_gray_palette = 
	    STATIC_SYMBOL("NUMBER-OF-BITS-OF-GRAY-IN-THE-EXTENDED-GRAY-PALETTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qnumber_of_bits_of_gray_in_the_extended_gray_palette,
	    FIX((SI_Long)6L));
    Qfree_bits_per_icp_byte = STATIC_SYMBOL("FREE-BITS-PER-ICP-BYTE",
	    AB_package);
    SET_SYMBOL_VALUE(Qfree_bits_per_icp_byte,FIX((SI_Long)15L));
    Qmaximum_background_tile_area = 
	    STATIC_SYMBOL("MAXIMUM-BACKGROUND-TILE-AREA",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_background_tile_area,FIX((SI_Long)16384L));
    Qmaximum_size_of_category_set_as_list = 
	    STATIC_SYMBOL("MAXIMUM-SIZE-OF-CATEGORY-SET-AS-LIST",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_size_of_category_set_as_list,FIX((SI_Long)8L));
    Qmax_instance_rule_chaining = 
	    STATIC_SYMBOL("MAX-INSTANCE-RULE-CHAINING",AB_package);
    SET_SYMBOL_VALUE(Qmax_instance_rule_chaining,FIX((SI_Long)512L));
    Qdefault_reduction = STATIC_SYMBOL("DEFAULT-REDUCTION",AB_package);
    SET_SYMBOL_VALUE(Qdefault_reduction,FIX((SI_Long)1L));
    Qmax_number_of_regexps_to_cache = 
	    STATIC_SYMBOL("MAX-NUMBER-OF-REGEXPS-TO-CACHE",AB_package);
    SET_SYMBOL_VALUE(Qmax_number_of_regexps_to_cache,FIX((SI_Long)25L));
    Qmax_number_of_lexing_tables_to_cache = 
	    STATIC_SYMBOL("MAX-NUMBER-OF-LEXING-TABLES-TO-CACHE",AB_package);
    SET_SYMBOL_VALUE(Qmax_number_of_lexing_tables_to_cache,FIX((SI_Long)100L));
    Qmaximum_number_of_generic_methods = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-GENERIC-METHODS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_number_of_generic_methods,FIX((SI_Long)57L));
    Qold_mask_for_saved_frame_flags = 
	    STATIC_SYMBOL("OLD-MASK-FOR-SAVED-FRAME-FLAGS",AB_package);
    SET_SYMBOL_VALUE(Qold_mask_for_saved_frame_flags,FIX((SI_Long)7531546L));
    Quse_full_size_of_with_output_wide_string_cutoff = 
	    STATIC_SYMBOL("USE-FULL-SIZE-OF-WITH-OUTPUT-WIDE-STRING-CUTOFF",
	    AB_package);
    SET_SYMBOL_VALUE(Quse_full_size_of_with_output_wide_string_cutoff,
	    FIX((SI_Long)256L));
    Qmaximum_length_of_menu_of_names = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-OF-MENU-OF-NAMES",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_length_of_menu_of_names,FIX((SI_Long)10000L));
    Qminimum_image_plane_serial_number = 
	    STATIC_SYMBOL("MINIMUM-IMAGE-PLANE-SERIAL-NUMBER",AB_package);
    SET_SYMBOL_VALUE(Qminimum_image_plane_serial_number,
	    FIX((SI_Long)-8388608L));
    Qmaximum_image_plane_serial_number = 
	    STATIC_SYMBOL("MAXIMUM-IMAGE-PLANE-SERIAL-NUMBER",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_image_plane_serial_number,
	    FIX((SI_Long)8388608L));
    Qassumed_standard_image_plane_border_width = 
	    STATIC_SYMBOL("ASSUMED-STANDARD-IMAGE-PLANE-BORDER-WIDTH",
	    AB_package);
    SET_SYMBOL_VALUE(Qassumed_standard_image_plane_border_width,
	    FIX((SI_Long)2L));
    Qwarning_shift = STATIC_SYMBOL("WARNING-SHIFT",AB_package);
    SET_SYMBOL_VALUE(Qwarning_shift,FIX((SI_Long)0L));
    Qtracing_shift = STATIC_SYMBOL("TRACING-SHIFT",AB_package);
    SET_SYMBOL_VALUE(Qtracing_shift,FIX((SI_Long)4L));
    Qbreakpoint_shift = STATIC_SYMBOL("BREAKPOINT-SHIFT",AB_package);
    SET_SYMBOL_VALUE(Qbreakpoint_shift,FIX((SI_Long)8L));
    Qsource_stepping_shift = STATIC_SYMBOL("SOURCE-STEPPING-SHIFT",AB_package);
    SET_SYMBOL_VALUE(Qsource_stepping_shift,FIX((SI_Long)12L));
    Qmessage_field_mask = STATIC_SYMBOL("MESSAGE-FIELD-MASK",AB_package);
    SET_SYMBOL_VALUE(Qmessage_field_mask,FIX((SI_Long)15L));
    Qdefault_number_of_renderings_for_bulk_delete = 
	    STATIC_SYMBOL("DEFAULT-NUMBER-OF-RENDERINGS-FOR-BULK-DELETE",
	    AB_package);
    SET_SYMBOL_VALUE(Qdefault_number_of_renderings_for_bulk_delete,
	    FIX((SI_Long)10L));
    Qdefault_maximum_renderings_for_class = 
	    STATIC_SYMBOL("DEFAULT-MAXIMUM-RENDERINGS-FOR-CLASS",AB_package);
    SET_SYMBOL_VALUE(Qdefault_maximum_renderings_for_class,FIX((SI_Long)200L));
    Qmax_subblock_count_with_pop_up_virtual_attributes_table = 
	    STATIC_SYMBOL("MAX-SUBBLOCK-COUNT-WITH-POP-UP-VIRTUAL-ATTRIBUTES-TABLE",
	    AB_package);
    SET_SYMBOL_VALUE(Qmax_subblock_count_with_pop_up_virtual_attributes_table,
	    FIX((SI_Long)3L));
    Qmb_ok = STATIC_SYMBOL("MB-OK",AB_package);
    SET_SYMBOL_VALUE(Qmb_ok,FIX((SI_Long)0L));
    Qmb_okcancel = STATIC_SYMBOL("MB-OKCANCEL",AB_package);
    SET_SYMBOL_VALUE(Qmb_okcancel,FIX((SI_Long)1L));
    Qmb_abortretryignore = STATIC_SYMBOL("MB-ABORTRETRYIGNORE",AB_package);
    SET_SYMBOL_VALUE(Qmb_abortretryignore,FIX((SI_Long)2L));
    Qmb_yesnocancel = STATIC_SYMBOL("MB-YESNOCANCEL",AB_package);
    SET_SYMBOL_VALUE(Qmb_yesnocancel,FIX((SI_Long)3L));
    Qmb_yesno = STATIC_SYMBOL("MB-YESNO",AB_package);
    SET_SYMBOL_VALUE(Qmb_yesno,FIX((SI_Long)4L));
    Qmb_retrycancel = STATIC_SYMBOL("MB-RETRYCANCEL",AB_package);
    SET_SYMBOL_VALUE(Qmb_retrycancel,FIX((SI_Long)5L));
    Qmb_help = STATIC_SYMBOL("MB-HELP",AB_package);
    SET_SYMBOL_VALUE(Qmb_help,FIX((SI_Long)16384L));
    Qdlg_icon_question = STATIC_SYMBOL("DLG-ICON-QUESTION",AB_package);
    SET_SYMBOL_VALUE(Qdlg_icon_question,FIX((SI_Long)0L));
    Qdlg_icon_information = STATIC_SYMBOL("DLG-ICON-INFORMATION",AB_package);
    SET_SYMBOL_VALUE(Qdlg_icon_information,FIX((SI_Long)1L));
    Qdlg_icon_warning = STATIC_SYMBOL("DLG-ICON-WARNING",AB_package);
    SET_SYMBOL_VALUE(Qdlg_icon_warning,FIX((SI_Long)2L));
    Qdlg_icon_error = STATIC_SYMBOL("DLG-ICON-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qdlg_icon_error,FIX((SI_Long)3L));
    Qmaximum_number_of_characters_in_pathname = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-CHARACTERS-IN-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_number_of_characters_in_pathname,
	    FIX((SI_Long)512L));
    Qcd_add_children = STATIC_SYMBOL("CD-ADD-CHILDREN",AB_package);
    SET_SYMBOL_VALUE(Qcd_add_children,FIX((SI_Long)1L));
    Qcd_refresh = STATIC_SYMBOL("CD-REFRESH",AB_package);
    SET_SYMBOL_VALUE(Qcd_refresh,FIX((SI_Long)3L));
    Qdebugger_dialog_cancel = STATIC_SYMBOL("DEBUGGER-DIALOG-CANCEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qdebugger_dialog_cancel,FIX((SI_Long)2L));
    Qdebugger_source_stepping_flag = 
	    STATIC_SYMBOL("DEBUGGER-SOURCE-STEPPING-FLAG",AB_package);
    SET_SYMBOL_VALUE(Qdebugger_source_stepping_flag,FIX((SI_Long)256L));
    Qtw_initiated_update = STATIC_SYMBOL("TW-INITIATED-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qtw_initiated_update,FIX((SI_Long)1L));
    Qg2_initiated_update = STATIC_SYMBOL("G2-INITIATED-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qg2_initiated_update,FIX((SI_Long)2L));
    Qmulti_update_begin = STATIC_SYMBOL("MULTI-UPDATE-BEGIN",AB_package);
    SET_SYMBOL_VALUE(Qmulti_update_begin,FIX((SI_Long)4L));
    Qmulti_update_continue = STATIC_SYMBOL("MULTI-UPDATE-CONTINUE",AB_package);
    SET_SYMBOL_VALUE(Qmulti_update_continue,FIX((SI_Long)8L));
    Qmulti_update_finish = STATIC_SYMBOL("MULTI-UPDATE-FINISH",AB_package);
    SET_SYMBOL_VALUE(Qmulti_update_finish,FIX((SI_Long)16L));
    Qfocus_changed_update = STATIC_SYMBOL("FOCUS-CHANGED-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qfocus_changed_update,FIX((SI_Long)32L));
    Qtw_multi_update_begin = STATIC_SYMBOL("TW-MULTI-UPDATE-BEGIN",AB_package);
    SET_SYMBOL_VALUE(Qtw_multi_update_begin,FIX((SI_Long)5L));
    Qtw_multi_update_continue = STATIC_SYMBOL("TW-MULTI-UPDATE-CONTINUE",
	    AB_package);
    SET_SYMBOL_VALUE(Qtw_multi_update_continue,FIX((SI_Long)9L));
    Qtw_multi_update_finish = STATIC_SYMBOL("TW-MULTI-UPDATE-FINISH",
	    AB_package);
    SET_SYMBOL_VALUE(Qtw_multi_update_finish,FIX((SI_Long)17L));
    Qg2_multi_update_begin = STATIC_SYMBOL("G2-MULTI-UPDATE-BEGIN",AB_package);
    SET_SYMBOL_VALUE(Qg2_multi_update_begin,FIX((SI_Long)6L));
    Qg2_multi_update_continue = STATIC_SYMBOL("G2-MULTI-UPDATE-CONTINUE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2_multi_update_continue,FIX((SI_Long)10L));
    Qg2_multi_update_finish = STATIC_SYMBOL("G2-MULTI-UPDATE-FINISH",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2_multi_update_finish,FIX((SI_Long)18L));
    Qg2_dialog_user_gesture = STATIC_SYMBOL("G2-DIALOG-USER-GESTURE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2_dialog_user_gesture,FIX((SI_Long)1L));
    Qg2_send_wsv_address = STATIC_SYMBOL("G2-SEND-WSV-ADDRESS",AB_package);
    SET_SYMBOL_VALUE(Qg2_send_wsv_address,FIX((SI_Long)8L));
    Qdialog_response_unspecified = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-UNSPECIFIED",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_unspecified,FIX((SI_Long)-1L));
    Qdialog_response_no_action = STATIC_SYMBOL("DIALOG-RESPONSE-NO-ACTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_no_action,FIX((SI_Long)0L));
    Qdialog_response_close = STATIC_SYMBOL("DIALOG-RESPONSE-CLOSE",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_close,FIX((SI_Long)1L));
    Qdialog_response_apply = STATIC_SYMBOL("DIALOG-RESPONSE-APPLY",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_apply,FIX((SI_Long)2L));
    Qdialog_response_respond = STATIC_SYMBOL("DIALOG-RESPONSE-RESPOND",
	    AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_respond,FIX((SI_Long)4L));
    Qdialog_response_send_all_data = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-SEND-ALL-DATA",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_send_all_data,FIX((SI_Long)8L));
    Qdialog_response_dont_invoke_callback = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-DONT-INVOKE-CALLBACK",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_dont_invoke_callback,FIX((SI_Long)16L));
    Qdialog_response_cancel = STATIC_SYMBOL("DIALOG-RESPONSE-CANCEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_cancel,FIX((SI_Long)1L));
    Qdialog_response_ok = STATIC_SYMBOL("DIALOG-RESPONSE-OK",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_ok,FIX((SI_Long)3L));
    Qdialog_response_just_respond = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-JUST-RESPOND",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_just_respond,FIX((SI_Long)4L));
    Qdialog_response_respond_and_ok = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-RESPOND-AND-OK",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_respond_and_ok,FIX((SI_Long)7L));
    Qdialog_response_respond_all = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-RESPOND-ALL",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_respond_all,FIX((SI_Long)12L));
    Qdialog_response_respond_all_and_ok = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-RESPOND-ALL-AND-OK",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_respond_all_and_ok,FIX((SI_Long)15L));
    Qdialog_response_cancel_without_callback = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-CANCEL-WITHOUT-CALLBACK",
	    AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_cancel_without_callback,
	    FIX((SI_Long)17L));
    Qdialog_response_client_side_problem = 
	    STATIC_SYMBOL("DIALOG-RESPONSE-CLIENT-SIDE-PROBLEM",AB_package);
    SET_SYMBOL_VALUE(Qdialog_response_client_side_problem,FIX((SI_Long)32L));
    Qdialog_is_modal = STATIC_SYMBOL("DIALOG-IS-MODAL",AB_package);
    SET_SYMBOL_VALUE(Qdialog_is_modal,FIX((SI_Long)1L));
    Qdialog_is_modeless = STATIC_SYMBOL("DIALOG-IS-MODELESS",AB_package);
    SET_SYMBOL_VALUE(Qdialog_is_modeless,FIX((SI_Long)2L));
    Qdialog_is_mdi_child = STATIC_SYMBOL("DIALOG-IS-MDI-CHILD",AB_package);
    SET_SYMBOL_VALUE(Qdialog_is_mdi_child,FIX((SI_Long)4L));
    Qdock_code_top = STATIC_SYMBOL("DOCK-CODE-TOP",AB_package);
    SET_SYMBOL_VALUE(Qdock_code_top,FIX((SI_Long)1L));
    Qdock_code_bottom = STATIC_SYMBOL("DOCK-CODE-BOTTOM",AB_package);
    SET_SYMBOL_VALUE(Qdock_code_bottom,FIX((SI_Long)2L));
    Qdock_code_left = STATIC_SYMBOL("DOCK-CODE-LEFT",AB_package);
    SET_SYMBOL_VALUE(Qdock_code_left,FIX((SI_Long)3L));
    Qdock_code_right = STATIC_SYMBOL("DOCK-CODE-RIGHT",AB_package);
    SET_SYMBOL_VALUE(Qdock_code_right,FIX((SI_Long)4L));
    Qdock_code_float = STATIC_SYMBOL("DOCK-CODE-FLOAT",AB_package);
    SET_SYMBOL_VALUE(Qdock_code_float,FIX((SI_Long)5L));
    Qdock_code_within = STATIC_SYMBOL("DOCK-CODE-WITHIN",AB_package);
    SET_SYMBOL_VALUE(Qdock_code_within,FIX((SI_Long)6L));
    Qdock_code_mdi_child = STATIC_SYMBOL("DOCK-CODE-MDI-CHILD",AB_package);
    SET_SYMBOL_VALUE(Qdock_code_mdi_child,FIX((SI_Long)7L));
    Qdock_code_top_level = STATIC_SYMBOL("DOCK-CODE-TOP-LEVEL",AB_package);
    SET_SYMBOL_VALUE(Qdock_code_top_level,FIX((SI_Long)8L));
    Qdock_code_embedded = STATIC_SYMBOL("DOCK-CODE-EMBEDDED",AB_package);
    SET_SYMBOL_VALUE(Qdock_code_embedded,FIX((SI_Long)9L));
    Qhandle_for_unsuccessful_query = 
	    STATIC_SYMBOL("HANDLE-FOR-UNSUCCESSFUL-QUERY",AB_package);
    SET_SYMBOL_VALUE(Qhandle_for_unsuccessful_query,FIX((SI_Long)-1L));
    Qhh_display_envar_topic = STATIC_SYMBOL("HH-DISPLAY-ENVAR-TOPIC",
	    AB_package);
    SET_SYMBOL_VALUE(Qhh_display_envar_topic,FIX((SI_Long)128L));
    Qlogbook_message_type_error = 
	    STATIC_SYMBOL("LOGBOOK-MESSAGE-TYPE-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qlogbook_message_type_error,FIX((SI_Long)1L));
    Qlogbook_message_type_warning = 
	    STATIC_SYMBOL("LOGBOOK-MESSAGE-TYPE-WARNING",AB_package);
    SET_SYMBOL_VALUE(Qlogbook_message_type_warning,FIX((SI_Long)2L));
    Qnms_stock_command_min_id = STATIC_SYMBOL("NMS-STOCK-COMMAND-MIN-ID",
	    AB_package);
    SET_SYMBOL_VALUE(Qnms_stock_command_min_id,FIX((SI_Long)1001L));
    Qnms_no_choice = STATIC_SYMBOL("NMS-NO-CHOICE",AB_package);
    SET_SYMBOL_VALUE(Qnms_no_choice,FIX((SI_Long)1500L));
    Qcodejock_reserved_command_ids = 
	    STATIC_SYMBOL("CODEJOCK-RESERVED-COMMAND-IDS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcodejock_reserved_command_ids,
	    Codejock_reserved_command_ids);
    list_constant = STATIC_CONS(FIX((SI_Long)9300L),FIX((SI_Long)9599L));
    SET_SYMBOL_VALUE(Qcodejock_reserved_command_ids,list_constant);
    Qnms_handle_gap_low = STATIC_SYMBOL("NMS-HANDLE-GAP-LOW",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnms_handle_gap_low,Nms_handle_gap_low);
    SET_SYMBOL_VALUE(Qnms_handle_gap_low,
	    minus(CAR(Codejock_reserved_command_ids),Nms_no_choice));
    Qnms_handle_gap_high = STATIC_SYMBOL("NMS-HANDLE-GAP-HIGH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnms_handle_gap_high,Nms_handle_gap_high);
    SET_SYMBOL_VALUE(Qnms_handle_gap_high,
	    minus(CDR(Codejock_reserved_command_ids),Nms_no_choice));
    Qnmsc_show = STATIC_SYMBOL("NMSC-SHOW",AB_package);
    SET_SYMBOL_VALUE(Qnmsc_show,FIX((SI_Long)1L));
    Qnmsc_hide = STATIC_SYMBOL("NMSC-HIDE",AB_package);
    SET_SYMBOL_VALUE(Qnmsc_hide,FIX((SI_Long)2L));
    Qnmsc_setcursel = STATIC_SYMBOL("NMSC-SETCURSEL",AB_package);
    SET_SYMBOL_VALUE(Qnmsc_setcursel,FIX((SI_Long)3L));
    Qnmsc_settext = STATIC_SYMBOL("NMSC-SETTEXT",AB_package);
    SET_SYMBOL_VALUE(Qnmsc_settext,FIX((SI_Long)4L));
    Qnmsc_addtext = STATIC_SYMBOL("NMSC-ADDTEXT",AB_package);
    SET_SYMBOL_VALUE(Qnmsc_addtext,FIX((SI_Long)5L));
    Qnmsc_deletetext = STATIC_SYMBOL("NMSC-DELETETEXT",AB_package);
    SET_SYMBOL_VALUE(Qnmsc_deletetext,FIX((SI_Long)6L));
    Qsb_hide = STATIC_SYMBOL("SB-HIDE",AB_package);
    SET_SYMBOL_VALUE(Qsb_hide,FIX((SI_Long)0L));
    Qsb_show = STATIC_SYMBOL("SB-SHOW",AB_package);
    SET_SYMBOL_VALUE(Qsb_show,FIX((SI_Long)1L));
    Qsb_text = STATIC_SYMBOL("SB-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qsb_text,FIX((SI_Long)2L));
    Qsb_reset = STATIC_SYMBOL("SB-RESET",AB_package);
    SET_SYMBOL_VALUE(Qsb_reset,FIX((SI_Long)3L));
    Qsb_minheight = STATIC_SYMBOL("SB-MINHEIGHT",AB_package);
    SET_SYMBOL_VALUE(Qsb_minheight,FIX((SI_Long)4L));
    Qsb_update = STATIC_SYMBOL("SB-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qsb_update,FIX((SI_Long)5L));
    Qsb_add_pane = STATIC_SYMBOL("SB-ADD-PANE",AB_package);
    SET_SYMBOL_VALUE(Qsb_add_pane,FIX((SI_Long)6L));
    Qsb_remove_pane = STATIC_SYMBOL("SB-REMOVE-PANE",AB_package);
    SET_SYMBOL_VALUE(Qsb_remove_pane,FIX((SI_Long)7L));
    Qsb_pane_text = STATIC_SYMBOL("SB-PANE-TEXT",AB_package);
    SET_SYMBOL_VALUE(Qsb_pane_text,FIX((SI_Long)8L));
    Qsb_pane_width = STATIC_SYMBOL("SB-PANE-WIDTH",AB_package);
    SET_SYMBOL_VALUE(Qsb_pane_width,FIX((SI_Long)9L));
    Qsb_pane_visible = STATIC_SYMBOL("SB-PANE-VISIBLE",AB_package);
    SET_SYMBOL_VALUE(Qsb_pane_visible,FIX((SI_Long)10L));
    Qsb_pane_foreground = STATIC_SYMBOL("SB-PANE-FOREGROUND",AB_package);
    SET_SYMBOL_VALUE(Qsb_pane_foreground,FIX((SI_Long)11L));
    Qsb_pane_background = STATIC_SYMBOL("SB-PANE-BACKGROUND",AB_package);
    SET_SYMBOL_VALUE(Qsb_pane_background,FIX((SI_Long)12L));
    Qsb_pane_icon = STATIC_SYMBOL("SB-PANE-ICON",AB_package);
    SET_SYMBOL_VALUE(Qsb_pane_icon,FIX((SI_Long)13L));
    Qsb_pane_alignment = STATIC_SYMBOL("SB-PANE-ALIGNMENT",AB_package);
    SET_SYMBOL_VALUE(Qsb_pane_alignment,FIX((SI_Long)14L));
    Qsb_pane_tooltip = STATIC_SYMBOL("SB-PANE-TOOLTIP",AB_package);
    SET_SYMBOL_VALUE(Qsb_pane_tooltip,FIX((SI_Long)15L));
    Qsb_pane_enabled = STATIC_SYMBOL("SB-PANE-ENABLED",AB_package);
    SET_SYMBOL_VALUE(Qsb_pane_enabled,FIX((SI_Long)16L));
    Qsb_pane_borders = STATIC_SYMBOL("SB-PANE-BORDERS",AB_package);
    SET_SYMBOL_VALUE(Qsb_pane_borders,FIX((SI_Long)17L));
    Qpane_destroy = STATIC_SYMBOL("PANE-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qpane_destroy,FIX((SI_Long)2L));
    Qpane_hide = STATIC_SYMBOL("PANE-HIDE",AB_package);
    SET_SYMBOL_VALUE(Qpane_hide,FIX((SI_Long)3L));
    Qpane_select = STATIC_SYMBOL("PANE-SELECT",AB_package);
    SET_SYMBOL_VALUE(Qpane_select,FIX((SI_Long)4L));
    Qpane_float = STATIC_SYMBOL("PANE-FLOAT",AB_package);
    SET_SYMBOL_VALUE(Qpane_float,FIX((SI_Long)5L));
    Qpane_dock = STATIC_SYMBOL("PANE-DOCK",AB_package);
    SET_SYMBOL_VALUE(Qpane_dock,FIX((SI_Long)6L));
    Qpane_show = STATIC_SYMBOL("PANE-SHOW",AB_package);
    SET_SYMBOL_VALUE(Qpane_show,FIX((SI_Long)7L));
    Qpane_set_title = STATIC_SYMBOL("PANE-SET-TITLE",AB_package);
    SET_SYMBOL_VALUE(Qpane_set_title,FIX((SI_Long)8L));
    Qpane_set_icon = STATIC_SYMBOL("PANE-SET-ICON",AB_package);
    SET_SYMBOL_VALUE(Qpane_set_icon,FIX((SI_Long)9L));
    Qpane_close = STATIC_SYMBOL("PANE-CLOSE",AB_package);
    SET_SYMBOL_VALUE(Qpane_close,FIX((SI_Long)10L));
    Qpane_redock = STATIC_SYMBOL("PANE-REDOCK",AB_package);
    SET_SYMBOL_VALUE(Qpane_redock,FIX((SI_Long)11L));
    Qpane_toggle_docking = STATIC_SYMBOL("PANE-TOGGLE-DOCKING",AB_package);
    SET_SYMBOL_VALUE(Qpane_toggle_docking,FIX((SI_Long)12L));
    Qpane_fill = STATIC_SYMBOL("PANE-FILL",AB_package);
    SET_SYMBOL_VALUE(Qpane_fill,FIX((SI_Long)13L));
    Qpane_set_closeable = STATIC_SYMBOL("PANE-SET-CLOSEABLE",AB_package);
    SET_SYMBOL_VALUE(Qpane_set_closeable,FIX((SI_Long)101L));
    Qpane_set_autohideable = STATIC_SYMBOL("PANE-SET-AUTOHIDEABLE",AB_package);
    SET_SYMBOL_VALUE(Qpane_set_autohideable,FIX((SI_Long)102L));
    Qpane_set_floatable = STATIC_SYMBOL("PANE-SET-FLOATABLE",AB_package);
    SET_SYMBOL_VALUE(Qpane_set_floatable,FIX((SI_Long)103L));
    Qpane_set_draggable = STATIC_SYMBOL("PANE-SET-DRAGGABLE",AB_package);
    SET_SYMBOL_VALUE(Qpane_set_draggable,FIX((SI_Long)104L));
    Qpane_set_visible_caption = STATIC_SYMBOL("PANE-SET-VISIBLE-CAPTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qpane_set_visible_caption,FIX((SI_Long)105L));
    Qpane_set_close_action = STATIC_SYMBOL("PANE-SET-CLOSE-ACTION",AB_package);
    SET_SYMBOL_VALUE(Qpane_set_close_action,FIX((SI_Long)106L));
    Qtree_view_destroy = STATIC_SYMBOL("TREE-VIEW-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_destroy,FIX((SI_Long)6L));
    Qtree_view_insert_item = STATIC_SYMBOL("TREE-VIEW-INSERT-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_insert_item,FIX((SI_Long)10L));
    Qtree_view_clear = STATIC_SYMBOL("TREE-VIEW-CLEAR",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_clear,FIX((SI_Long)11L));
    Qtree_view_set_indent = STATIC_SYMBOL("TREE-VIEW-SET-INDENT",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_indent,FIX((SI_Long)12L));
    Qtree_view_set_item_height = STATIC_SYMBOL("TREE-VIEW-SET-ITEM-HEIGHT",
	    AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_item_height,FIX((SI_Long)13L));
    Qtree_view_set_bgcolor = STATIC_SYMBOL("TREE-VIEW-SET-BGCOLOR",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_bgcolor,FIX((SI_Long)14L));
    Qtree_view_set_text_color = STATIC_SYMBOL("TREE-VIEW-SET-TEXT-COLOR",
	    AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_text_color,FIX((SI_Long)15L));
    Qtree_view_set_insert_mark_color = 
	    STATIC_SYMBOL("TREE-VIEW-SET-INSERT-MARK-COLOR",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_insert_mark_color,FIX((SI_Long)16L));
    Qtree_view_select_item_by_name = 
	    STATIC_SYMBOL("TREE-VIEW-SELECT-ITEM-BY-NAME",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_select_item_by_name,FIX((SI_Long)17L));
    Qtree_view_ensure_visible = STATIC_SYMBOL("TREE-VIEW-ENSURE-VISIBLE",
	    AB_package);
    SET_SYMBOL_VALUE(Qtree_view_ensure_visible,FIX((SI_Long)18L));
    Qtree_view_scroll_to = STATIC_SYMBOL("TREE-VIEW-SCROLL-TO",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_scroll_to,FIX((SI_Long)19L));
    Qtree_view_set_insert_mark = STATIC_SYMBOL("TREE-VIEW-SET-INSERT-MARK",
	    AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_insert_mark,FIX((SI_Long)20L));
    Qtree_view_edit_item = STATIC_SYMBOL("TREE-VIEW-EDIT-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_edit_item,FIX((SI_Long)21L));
    Qtree_view_expand_item = STATIC_SYMBOL("TREE-VIEW-EXPAND-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_expand_item,FIX((SI_Long)22L));
    Qtree_view_collapse_item = STATIC_SYMBOL("TREE-VIEW-COLLAPSE-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qtree_view_collapse_item,FIX((SI_Long)23L));
    Qtree_view_select_item = STATIC_SYMBOL("TREE-VIEW-SELECT-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_select_item,FIX((SI_Long)24L));
    Qtree_view_set_item_tooltip = 
	    STATIC_SYMBOL("TREE-VIEW-SET-ITEM-TOOLTIP",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_item_tooltip,FIX((SI_Long)25L));
    Qtree_view_set_item_bold = STATIC_SYMBOL("TREE-VIEW-SET-ITEM-BOLD",
	    AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_item_bold,FIX((SI_Long)26L));
    Qtree_view_set_item_label = STATIC_SYMBOL("TREE-VIEW-SET-ITEM-LABEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_item_label,FIX((SI_Long)27L));
    Qtree_view_set_item_icons = STATIC_SYMBOL("TREE-VIEW-SET-ITEM-ICONS",
	    AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_item_icons,FIX((SI_Long)28L));
    Qtree_view_set_item_check = STATIC_SYMBOL("TREE-VIEW-SET-ITEM-CHECK",
	    AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_item_check,FIX((SI_Long)29L));
    Qtree_view_delete_item = STATIC_SYMBOL("TREE-VIEW-DELETE-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_delete_item,FIX((SI_Long)30L));
    Qtree_view_toggle_item = STATIC_SYMBOL("TREE-VIEW-TOGGLE-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_toggle_item,FIX((SI_Long)31L));
    Qtree_view_set_right_click_selects_node = 
	    STATIC_SYMBOL("TREE-VIEW-SET-RIGHT-CLICK-SELECTS-NODE",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_set_right_click_selects_node,
	    FIX((SI_Long)32L));
    Qtree_view_expand_all = STATIC_SYMBOL("TREE-VIEW-EXPAND-ALL",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_expand_all,FIX((SI_Long)33L));
    Qtree_view_collapse_all = STATIC_SYMBOL("TREE-VIEW-COLLAPSE-ALL",
	    AB_package);
    SET_SYMBOL_VALUE(Qtree_view_collapse_all,FIX((SI_Long)34L));
    Qtree_view_redraw = STATIC_SYMBOL("TREE-VIEW-REDRAW",AB_package);
    SET_SYMBOL_VALUE(Qtree_view_redraw,FIX((SI_Long)35L));
    Qtvf_children = STATIC_SYMBOL("TVF-CHILDREN",AB_package);
    SET_SYMBOL_VALUE(Qtvf_children,FIX((SI_Long)1L));
    Qtvf_bold = STATIC_SYMBOL("TVF-BOLD",AB_package);
    SET_SYMBOL_VALUE(Qtvf_bold,FIX((SI_Long)2L));
    Qtvf_expand = STATIC_SYMBOL("TVF-EXPAND",AB_package);
    SET_SYMBOL_VALUE(Qtvf_expand,FIX((SI_Long)4L));
    Qtvf_check = STATIC_SYMBOL("TVF-CHECK",AB_package);
    SET_SYMBOL_VALUE(Qtvf_check,FIX((SI_Long)8L));
    Qtvf_first = STATIC_SYMBOL("TVF-FIRST",AB_package);
    SET_SYMBOL_VALUE(Qtvf_first,FIX((SI_Long)16L));
    Qtvf_after = STATIC_SYMBOL("TVF-AFTER",AB_package);
    SET_SYMBOL_VALUE(Qtvf_after,FIX((SI_Long)32L));
    Qtvf_insert_mark = STATIC_SYMBOL("TVF-INSERT-MARK",AB_package);
    SET_SYMBOL_VALUE(Qtvf_insert_mark,FIX((SI_Long)64L));
    Qtvf_reclaim_label = STATIC_SYMBOL("TVF-RECLAIM-LABEL",AB_package);
    SET_SYMBOL_VALUE(Qtvf_reclaim_label,FIX((SI_Long)128L));
    Qhtml_view_destroy = STATIC_SYMBOL("HTML-VIEW-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qhtml_view_destroy,FIX((SI_Long)2L));
    Qhtml_view_back = STATIC_SYMBOL("HTML-VIEW-BACK",AB_package);
    SET_SYMBOL_VALUE(Qhtml_view_back,FIX((SI_Long)3L));
    Qhtml_view_forward = STATIC_SYMBOL("HTML-VIEW-FORWARD",AB_package);
    SET_SYMBOL_VALUE(Qhtml_view_forward,FIX((SI_Long)4L));
    Qhtml_view_home = STATIC_SYMBOL("HTML-VIEW-HOME",AB_package);
    SET_SYMBOL_VALUE(Qhtml_view_home,FIX((SI_Long)5L));
    Qhtml_view_stop = STATIC_SYMBOL("HTML-VIEW-STOP",AB_package);
    SET_SYMBOL_VALUE(Qhtml_view_stop,FIX((SI_Long)6L));
    Qhtml_view_refresh = STATIC_SYMBOL("HTML-VIEW-REFRESH",AB_package);
    SET_SYMBOL_VALUE(Qhtml_view_refresh,FIX((SI_Long)7L));
    Qhtml_view_goto = STATIC_SYMBOL("HTML-VIEW-GOTO",AB_package);
    SET_SYMBOL_VALUE(Qhtml_view_goto,FIX((SI_Long)8L));
    Qhtml_view_print = STATIC_SYMBOL("HTML-VIEW-PRINT",AB_package);
    SET_SYMBOL_VALUE(Qhtml_view_print,FIX((SI_Long)9L));
    Qshortcut_bar_style_outlook = 
	    STATIC_SYMBOL("SHORTCUT-BAR-STYLE-OUTLOOK",AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_style_outlook,FIX((SI_Long)1L));
    Qshortcut_bar_style_outlook_2003 = 
	    STATIC_SYMBOL("SHORTCUT-BAR-STYLE-OUTLOOK-2003",AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_style_outlook_2003,FIX((SI_Long)2L));
    Qshortcut_bar_destroy = STATIC_SYMBOL("SHORTCUT-BAR-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_destroy,FIX((SI_Long)6L));
    Qshortcut_bar_add_folder = STATIC_SYMBOL("SHORTCUT-BAR-ADD-FOLDER",
	    AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_add_folder,FIX((SI_Long)10L));
    Qshortcut_bar_add_item = STATIC_SYMBOL("SHORTCUT-BAR-ADD-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_add_item,FIX((SI_Long)11L));
    Qshortcut_bar_clear = STATIC_SYMBOL("SHORTCUT-BAR-CLEAR",AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_clear,FIX((SI_Long)12L));
    Qshortcut_bar_select_folder = 
	    STATIC_SYMBOL("SHORTCUT-BAR-SELECT-FOLDER",AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_select_folder,FIX((SI_Long)13L));
    Qshortcut_bar_enable_folder = 
	    STATIC_SYMBOL("SHORTCUT-BAR-ENABLE-FOLDER",AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_enable_folder,FIX((SI_Long)14L));
    Qshortcut_bar_disable_folder = 
	    STATIC_SYMBOL("SHORTCUT-BAR-DISABLE-FOLDER",AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_disable_folder,FIX((SI_Long)15L));
    Qshortcut_bar_select_item = STATIC_SYMBOL("SHORTCUT-BAR-SELECT-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_select_item,FIX((SI_Long)16L));
    Qshortcut_bar_enable_item = STATIC_SYMBOL("SHORTCUT-BAR-ENABLE-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_enable_item,FIX((SI_Long)17L));
    Qshortcut_bar_disable_item = STATIC_SYMBOL("SHORTCUT-BAR-DISABLE-ITEM",
	    AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_disable_item,FIX((SI_Long)18L));
    Qshortcut_bar_small_icons = STATIC_SYMBOL("SHORTCUT-BAR-SMALL-ICONS",
	    AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_small_icons,FIX((SI_Long)19L));
    Qshortcut_bar_large_icons = STATIC_SYMBOL("SHORTCUT-BAR-LARGE-ICONS",
	    AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_large_icons,FIX((SI_Long)20L));
    Qshortcut_bar_background_color = 
	    STATIC_SYMBOL("SHORTCUT-BAR-BACKGROUND-COLOR",AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_background_color,FIX((SI_Long)21L));
    Qshortcut_bar_foreground_color = 
	    STATIC_SYMBOL("SHORTCUT-BAR-FOREGROUND-COLOR",AB_package);
    SET_SYMBOL_VALUE(Qshortcut_bar_foreground_color,FIX((SI_Long)22L));
    Qobs_xt_smallicon = STATIC_SYMBOL("OBS-XT-SMALLICON",AB_package);
    SET_SYMBOL_VALUE(Qobs_xt_smallicon,FIX((SI_Long)1L));
    Qobs_xt_largeicon = STATIC_SYMBOL("OBS-XT-LARGEICON",AB_package);
    SET_SYMBOL_VALUE(Qobs_xt_largeicon,FIX((SI_Long)2L));
    Qobs_xt_editgroups = STATIC_SYMBOL("OBS-XT-EDITGROUPS",AB_package);
    SET_SYMBOL_VALUE(Qobs_xt_editgroups,FIX((SI_Long)4L));
    Qobs_xt_edititems = STATIC_SYMBOL("OBS-XT-EDITITEMS",AB_package);
    SET_SYMBOL_VALUE(Qobs_xt_edititems,FIX((SI_Long)8L));
    Qobs_xt_removegroups = STATIC_SYMBOL("OBS-XT-REMOVEGROUPS",AB_package);
    SET_SYMBOL_VALUE(Qobs_xt_removegroups,FIX((SI_Long)16L));
    Qobs_xt_removeitems = STATIC_SYMBOL("OBS-XT-REMOVEITEMS",AB_package);
    SET_SYMBOL_VALUE(Qobs_xt_removeitems,FIX((SI_Long)32L));
    Qobs_xt_addgroups = STATIC_SYMBOL("OBS-XT-ADDGROUPS",AB_package);
    SET_SYMBOL_VALUE(Qobs_xt_addgroups,FIX((SI_Long)64L));
    Qobs_xt_dragitems = STATIC_SYMBOL("OBS-XT-DRAGITEMS",AB_package);
    SET_SYMBOL_VALUE(Qobs_xt_dragitems,FIX((SI_Long)128L));
    Qobs_xt_animation = STATIC_SYMBOL("OBS-XT-ANIMATION",AB_package);
    SET_SYMBOL_VALUE(Qobs_xt_animation,FIX((SI_Long)256L));
    Qobs_xt_selhighlight = STATIC_SYMBOL("OBS-XT-SELHIGHLIGHT",AB_package);
    SET_SYMBOL_VALUE(Qobs_xt_selhighlight,FIX((SI_Long)512L));
    Qobs_default_style = STATIC_SYMBOL("OBS-DEFAULT-STYLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qobs_default_style,Obs_default_style);
    SET_SYMBOL_VALUE(Qobs_default_style,logiorn(3,Obs_xt_selhighlight,
	    Obs_xt_animation,Obs_xt_largeicon));
    Qdlgm_settext = STATIC_SYMBOL("DLGM-SETTEXT",AB_package);
    SET_SYMBOL_VALUE(Qdlgm_settext,FIX((SI_Long)1L));
    Qdlgm_addstrings = STATIC_SYMBOL("DLGM-ADDSTRINGS",AB_package);
    SET_SYMBOL_VALUE(Qdlgm_addstrings,FIX((SI_Long)2L));
    Qdlgm_seticon = STATIC_SYMBOL("DLGM-SETICON",AB_package);
    SET_SYMBOL_VALUE(Qdlgm_seticon,FIX((SI_Long)3L));
    Qdlgm_check = STATIC_SYMBOL("DLGM-CHECK",AB_package);
    SET_SYMBOL_VALUE(Qdlgm_check,FIX((SI_Long)4L));
    Qdlgm_sndmsg = STATIC_SYMBOL("DLGM-SNDMSG",AB_package);
    SET_SYMBOL_VALUE(Qdlgm_sndmsg,FIX((SI_Long)5L));
    Qchart_create = STATIC_SYMBOL("CHART-CREATE",AB_package);
    SET_SYMBOL_VALUE(Qchart_create,FIX((SI_Long)1L));
    Qchart_destroy = STATIC_SYMBOL("CHART-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qchart_destroy,FIX((SI_Long)2L));
    Qchart_print = STATIC_SYMBOL("CHART-PRINT",AB_package);
    SET_SYMBOL_VALUE(Qchart_print,FIX((SI_Long)3L));
    Qchart_update = STATIC_SYMBOL("CHART-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qchart_update,FIX((SI_Long)4L));
    Qchart_partial_update = STATIC_SYMBOL("CHART-PARTIAL-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qchart_partial_update,FIX((SI_Long)5L));
    Qchart_copy = STATIC_SYMBOL("CHART-COPY",AB_package);
    SET_SYMBOL_VALUE(Qchart_copy,FIX((SI_Long)6L));
    Qchart_export = STATIC_SYMBOL("CHART-EXPORT",AB_package);
    SET_SYMBOL_VALUE(Qchart_export,FIX((SI_Long)7L));
    Qchart_format_jpeg = STATIC_SYMBOL("CHART-FORMAT-JPEG",AB_package);
    SET_SYMBOL_VALUE(Qchart_format_jpeg,FIX((SI_Long)1L));
    Qchart_format_png = STATIC_SYMBOL("CHART-FORMAT-PNG",AB_package);
    SET_SYMBOL_VALUE(Qchart_format_png,FIX((SI_Long)2L));
    Qchart_format_bmp = STATIC_SYMBOL("CHART-FORMAT-BMP",AB_package);
    SET_SYMBOL_VALUE(Qchart_format_bmp,FIX((SI_Long)3L));
    Qchart_format_wmf = STATIC_SYMBOL("CHART-FORMAT-WMF",AB_package);
    SET_SYMBOL_VALUE(Qchart_format_wmf,FIX((SI_Long)4L));
    Qchart_format_svg = STATIC_SYMBOL("CHART-FORMAT-SVG",AB_package);
    SET_SYMBOL_VALUE(Qchart_format_svg,FIX((SI_Long)5L));
    Qchart_success = STATIC_SYMBOL("CHART-SUCCESS",AB_package);
    SET_SYMBOL_VALUE(Qchart_success,FIX((SI_Long)0L));
    Qchart_no_window = STATIC_SYMBOL("CHART-NO-WINDOW",AB_package);
    SET_SYMBOL_VALUE(Qchart_no_window,FIX((SI_Long)1L));
    Qlvcfmt_left = STATIC_SYMBOL("LVCFMT-LEFT",AB_package);
    SET_SYMBOL_VALUE(Qlvcfmt_left,FIX((SI_Long)0L));
    Qlvcfmt_right = STATIC_SYMBOL("LVCFMT-RIGHT",AB_package);
    SET_SYMBOL_VALUE(Qlvcfmt_right,FIX((SI_Long)1L));
    Qlvcfmt_center = STATIC_SYMBOL("LVCFMT-CENTER",AB_package);
    SET_SYMBOL_VALUE(Qlvcfmt_center,FIX((SI_Long)2L));
    Qlvscw_autosize = STATIC_SYMBOL("LVSCW-AUTOSIZE",AB_package);
    SET_SYMBOL_VALUE(Qlvscw_autosize,FIX((SI_Long)-1L));
    Qlvscw_autosize_useheader = STATIC_SYMBOL("LVSCW-AUTOSIZE-USEHEADER",
	    AB_package);
    SET_SYMBOL_VALUE(Qlvscw_autosize_useheader,FIX((SI_Long)-2L));
    Qevent_time_mask = STATIC_SYMBOL("EVENT-TIME-MASK",AB_package);
    SET_SYMBOL_VALUE(Qevent_time_mask,FIX((SI_Long)268435455L));
    Qleast_common_multiple_of_stock_line_pattern_lengths = 
	    STATIC_SYMBOL("LEAST-COMMON-MULTIPLE-OF-STOCK-LINE-PATTERN-LENGTHS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qleast_common_multiple_of_stock_line_pattern_lengths,
	    Least_common_multiple_of_stock_line_pattern_lengths);
    SET_SYMBOL_VALUE(Qleast_common_multiple_of_stock_line_pattern_lengths,
	    timesn(4,FIX((SI_Long)3L),FIX((SI_Long)4L),FIX((SI_Long)5L),
	    FIX((SI_Long)7L)));
    Qminimum_minimum_fixnum_scheduling_interval = 
	    STATIC_SYMBOL("MINIMUM-MINIMUM-FIXNUM-SCHEDULING-INTERVAL",
	    AB_package);
    SET_SYMBOL_VALUE(Qminimum_minimum_fixnum_scheduling_interval,
	    FIX((SI_Long)2L));
    Qminimum_minimum_float_scheduling_interval = 
	    STATIC_SYMBOL("MINIMUM-MINIMUM-FLOAT-SCHEDULING-INTERVAL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminimum_minimum_float_scheduling_interval,
	    Minimum_minimum_float_scheduling_interval);
    float_constant_3 = STATIC_FLOAT(0.002);
    SET_SYMBOL_VALUE(Qminimum_minimum_float_scheduling_interval,
	    float_constant_3);
    Qtmask_kka_p_batkanakan = STATIC_SYMBOL("TMASK_KKA_P_BATKANAKAN",
	    AB_package);
    SET_SYMBOL_VALUE(Qtmask_kka_p_batkanakan,FIX((SI_Long)1L));
    Qtmask_kka_hensaisyo = STATIC_SYMBOL("TMASK_KKA_HENSAISYO",AB_package);
    SET_SYMBOL_VALUE(Qtmask_kka_hensaisyo,FIX((SI_Long)2L));
    Qtmask_kka_gtango = STATIC_SYMBOL("TMASK_KKA_GTANGO",AB_package);
    SET_SYMBOL_VALUE(Qtmask_kka_gtango,FIX((SI_Long)4L));
    Qtmask_kka_ghyoki = STATIC_SYMBOL("TMASK_KKA_GHYOKI",AB_package);
    SET_SYMBOL_VALUE(Qtmask_kka_ghyoki,FIX((SI_Long)8L));
    Qtmask_kka_gtnum = STATIC_SYMBOL("TMASK_KKA_GTNUM",AB_package);
    SET_SYMBOL_VALUE(Qtmask_kka_gtnum,FIX((SI_Long)16L));
    Qtmask_kka_evalbun = STATIC_SYMBOL("TMASK_KKA_EVALBUN",AB_package);
    SET_SYMBOL_VALUE(Qtmask_kka_evalbun,FIX((SI_Long)32L));
    Qtmask_kka_find_bunpo = STATIC_SYMBOL("TMASK_KKA_FIND_BUNPO",AB_package);
    SET_SYMBOL_VALUE(Qtmask_kka_find_bunpo,FIX((SI_Long)64L));
    Qtmask_chkbunpo = STATIC_SYMBOL("TMASK_CHKBUNPO",AB_package);
    SET_SYMBOL_VALUE(Qtmask_chkbunpo,FIX((SI_Long)128L));
    Qtmask_chkattr = STATIC_SYMBOL("TMASK_CHKATTR",AB_package);
    SET_SYMBOL_VALUE(Qtmask_chkattr,FIX((SI_Long)256L));
    Qtmask_kka_g_taigen = STATIC_SYMBOL("TMASK_KKA_G_TAIGEN",AB_package);
    SET_SYMBOL_VALUE(Qtmask_kka_g_taigen,FIX((SI_Long)512L));
    Qtmask_kka_kofind = STATIC_SYMBOL("TMASK_KKA_KOFIND",AB_package);
    SET_SYMBOL_VALUE(Qtmask_kka_kofind,FIX((SI_Long)1024L));
    Qtmask_kka_ishouki = STATIC_SYMBOL("TMASK_KKA_ISHOUKI",AB_package);
    SET_SYMBOL_VALUE(Qtmask_kka_ishouki,FIX((SI_Long)2048L));
    Qjis_space_character_code = STATIC_SYMBOL("JIS-SPACE-CHARACTER-CODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_space_character_code,FIX((SI_Long)8481L));
    Qjis_colon_character_code = STATIC_SYMBOL("JIS-COLON-CHARACTER-CODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_colon_character_code,FIX((SI_Long)8487L));
    Qjis_0_digit_character_code = 
	    STATIC_SYMBOL("JIS-0-DIGIT-CHARACTER-CODE",AB_package);
    SET_SYMBOL_VALUE(Qjis_0_digit_character_code,FIX((SI_Long)9008L));
    Qjis_letter_a_character_code = 
	    STATIC_SYMBOL("JIS-LETTER-A-CHARACTER-CODE",AB_package);
    SET_SYMBOL_VALUE(Qjis_letter_a_character_code,FIX((SI_Long)9025L));
    Qjis_m_dash_character_code = STATIC_SYMBOL("JIS-M-DASH-CHARACTER-CODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjis_m_dash_character_code,FIX((SI_Long)9005L));
    Qhfep_ks_size = STATIC_SYMBOL("HFEP-KS-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qhfep_ks_size,FIX((SI_Long)2390L));
    Qhfep_none = STATIC_SYMBOL("HFEP-NONE",AB_package);
    SET_SYMBOL_VALUE(Qhfep_none,FIX((SI_Long)0L));
    Qhfep_go_on = STATIC_SYMBOL("HFEP-GO-ON",AB_package);
    SET_SYMBOL_VALUE(Qhfep_go_on,FIX((SI_Long)1L));
    Qhfep_done = STATIC_SYMBOL("HFEP-DONE",AB_package);
    SET_SYMBOL_VALUE(Qhfep_done,FIX((SI_Long)2L));
    Qhfep_wrong = STATIC_SYMBOL("HFEP-WRONG",AB_package);
    SET_SYMBOL_VALUE(Qhfep_wrong,FIX((SI_Long)3L));
    Qhfep_error = STATIC_SYMBOL("HFEP-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qhfep_error,FIX((SI_Long)4L));
    Qhfep_null_code = STATIC_SYMBOL("HFEP-NULL-CODE",AB_package);
    SET_SYMBOL_VALUE(Qhfep_null_code,FIX((SI_Long)0L));
    Qdate_month_and_year_of_frame_edit_base_time = 
	    STATIC_SYMBOL("DATE-MONTH-AND-YEAR-OF-FRAME-EDIT-BASE-TIME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdate_month_and_year_of_frame_edit_base_time,
	    Date_month_and_year_of_frame_edit_base_time);
    list_constant_1 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)1L),
	    FIX((SI_Long)9L),FIX((SI_Long)1993L));
    SET_SYMBOL_VALUE(Qdate_month_and_year_of_frame_edit_base_time,
	    list_constant_1);
    Qframe_edit_base_timestamp = STATIC_SYMBOL("FRAME-EDIT-BASE-TIMESTAMP",
	    AB_package);
    SET_SYMBOL_VALUE(Qframe_edit_base_timestamp,FIX((SI_Long)0L));
    Qadditional_time_for_synthetic_paste_event_timestamps = 
	    STATIC_SYMBOL("ADDITIONAL-TIME-FOR-SYNTHETIC-PASTE-EVENT-TIMESTAMPS",
	    AB_package);
    SET_SYMBOL_VALUE(Qadditional_time_for_synthetic_paste_event_timestamps,
	    FIX((SI_Long)13L));
    Qmost_positive_window_coordinate = 
	    STATIC_SYMBOL("MOST-POSITIVE-WINDOW-COORDINATE",AB_package);
    SET_SYMBOL_VALUE(Qmost_positive_window_coordinate,FIX((SI_Long)65535L));
    Qmost_negative_window_coordinate = 
	    STATIC_SYMBOL("MOST-NEGATIVE-WINDOW-COORDINATE",AB_package);
    SET_SYMBOL_VALUE(Qmost_negative_window_coordinate,FIX((SI_Long)-65535L));
    Qdefault_telewindows_upper_margin = 
	    STATIC_SYMBOL("DEFAULT-TELEWINDOWS-UPPER-MARGIN",AB_package);
    SET_SYMBOL_VALUE(Qdefault_telewindows_upper_margin,FIX((SI_Long)50L));
    Qdefault_error_source_line = STATIC_SYMBOL("DEFAULT-ERROR-SOURCE-LINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qdefault_error_source_line,FIX((SI_Long)-1L));
    Qdefault_error_source_column = 
	    STATIC_SYMBOL("DEFAULT-ERROR-SOURCE-COLUMN",AB_package);
    SET_SYMBOL_VALUE(Qdefault_error_source_column,FIX((SI_Long)-1L));
    Qg2_array_length_maximum = STATIC_SYMBOL("G2-ARRAY-LENGTH-MAXIMUM",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_array_length_maximum,
	    G2_array_length_maximum);
    SET_SYMBOL_VALUE(Qg2_array_length_maximum,
	    FIXNUM_MINUS(FIX((SI_Long)524288L),FIX((SI_Long)1024L)));
    Qhistory_timestamp_epsilon = STATIC_SYMBOL("HISTORY-TIMESTAMP-EPSILON",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhistory_timestamp_epsilon,
	    History_timestamp_epsilon);
    float_constant_4 = STATIC_FLOAT(9.0E-7);
    SET_SYMBOL_VALUE(Qhistory_timestamp_epsilon,float_constant_4);
    Qno_history_spec_value = STATIC_SYMBOL("NO-HISTORY-SPEC-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qno_history_spec_value,FIX((SI_Long)-1L));
    Qno_resumable_object_index = STATIC_SYMBOL("NO-RESUMABLE-OBJECT-INDEX",
	    AB_package);
    SET_SYMBOL_VALUE(Qno_resumable_object_index,FIX((SI_Long)-1L));
    Qdefault_procedure_evaluation_priority = 
	    STATIC_SYMBOL("DEFAULT-PROCEDURE-EVALUATION-PRIORITY",AB_package);
    SET_SYMBOL_VALUE(Qdefault_procedure_evaluation_priority,FIX((SI_Long)6L));
    Qprocedure_can_invalidate_environment_mask = 
	    STATIC_SYMBOL("PROCEDURE-CAN-INVALIDATE-ENVIRONMENT-MASK",
	    AB_package);
    SET_SYMBOL_VALUE(Qprocedure_can_invalidate_environment_mask,
	    FIX((SI_Long)1L));
    Qprocedure_contains_wait_state_mask = 
	    STATIC_SYMBOL("PROCEDURE-CONTAINS-WAIT-STATE-MASK",AB_package);
    SET_SYMBOL_VALUE(Qprocedure_contains_wait_state_mask,FIX((SI_Long)2L));
    Qprocedure_contains_indirect_procedure_call_mask = 
	    STATIC_SYMBOL("PROCEDURE-CONTAINS-INDIRECT-PROCEDURE-CALL-MASK",
	    AB_package);
    SET_SYMBOL_VALUE(Qprocedure_contains_indirect_procedure_call_mask,
	    FIX((SI_Long)4L));
    Qprocedure_call_without_validated_environment_mask = 
	    STATIC_SYMBOL("PROCEDURE-CALL-WITHOUT-VALIDATED-ENVIRONMENT-MASK",
	    AB_package);
    SET_SYMBOL_VALUE(Qprocedure_call_without_validated_environment_mask,
	    FIX((SI_Long)8L));
    Qprocedure_invalidates_environment_union_mask = 
	    STATIC_SYMBOL("PROCEDURE-INVALIDATES-ENVIRONMENT-UNION-MASK",
	    AB_package);
    SET_SYMBOL_VALUE(Qprocedure_invalidates_environment_union_mask,
	    FIX((SI_Long)15L));
    Qmaximum_length_for_writing_evaluation_values = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-FOR-WRITING-EVALUATION-VALUES",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_length_for_writing_evaluation_values,
	    FIX((SI_Long)300L));
    Qmaximum_number_of_lisp_call_arguments = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-LISP-CALL-ARGUMENTS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_number_of_lisp_call_arguments,FIX((SI_Long)8L));
    Qmaximum_number_of_lisp_call_return_values = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-LISP-CALL-RETURN-VALUES",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_number_of_lisp_call_return_values,
	    FIX((SI_Long)8L));
    Qinitial_change_log_revision_number = 
	    STATIC_SYMBOL("INITIAL-CHANGE-LOG-REVISION-NUMBER",AB_package);
    SET_SYMBOL_VALUE(Qinitial_change_log_revision_number,FIX((SI_Long)0L));
    Qmaximum_painting_action_args = 
	    STATIC_SYMBOL("MAXIMUM-PAINTING-ACTION-ARGS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_painting_action_args,FIX((SI_Long)10L));
    Qbuffered_plot_painting_minimum_ratio = 
	    STATIC_SYMBOL("BUFFERED-PLOT-PAINTING-MINIMUM-RATIO",AB_package);
    SET_SYMBOL_VALUE(Qbuffered_plot_painting_minimum_ratio,FIX((SI_Long)5L));
    Qfraction_modulus_of_compound_fixnum_simulation_time = 
	    STATIC_SYMBOL("FRACTION-MODULUS-OF-COMPOUND-FIXNUM-SIMULATION-TIME",
	    AB_package);
    SET_SYMBOL_VALUE(Qfraction_modulus_of_compound_fixnum_simulation_time,
	    FIX((SI_Long)100000L));
    Qxml_callback_none = STATIC_SYMBOL("XML-CALLBACK-NONE",AB_package);
    SET_SYMBOL_VALUE(Qxml_callback_none,FIX((SI_Long)-1L));
    Qxml_callback_start_document = 
	    STATIC_SYMBOL("XML-CALLBACK-START-DOCUMENT",AB_package);
    SET_SYMBOL_VALUE(Qxml_callback_start_document,FIX((SI_Long)12L));
    Qxml_callback_end_document = STATIC_SYMBOL("XML-CALLBACK-END-DOCUMENT",
	    AB_package);
    SET_SYMBOL_VALUE(Qxml_callback_end_document,FIX((SI_Long)13L));
    Qxml_callback_start_element = 
	    STATIC_SYMBOL("XML-CALLBACK-START-ELEMENT",AB_package);
    SET_SYMBOL_VALUE(Qxml_callback_start_element,FIX((SI_Long)14L));
    Qxml_callback_end_element = STATIC_SYMBOL("XML-CALLBACK-END-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE(Qxml_callback_end_element,FIX((SI_Long)15L));
    Qxml_callback_characters = STATIC_SYMBOL("XML-CALLBACK-CHARACTERS",
	    AB_package);
    SET_SYMBOL_VALUE(Qxml_callback_characters,FIX((SI_Long)17L));
    Qxml_callback_comment = STATIC_SYMBOL("XML-CALLBACK-COMMENT",AB_package);
    SET_SYMBOL_VALUE(Qxml_callback_comment,FIX((SI_Long)20L));
    Qxml_callback_warning = STATIC_SYMBOL("XML-CALLBACK-WARNING",AB_package);
    SET_SYMBOL_VALUE(Qxml_callback_warning,FIX((SI_Long)21L));
    Qxml_callback_error = STATIC_SYMBOL("XML-CALLBACK-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qxml_callback_error,FIX((SI_Long)22L));
    Qxml_callback_fatal_error = STATIC_SYMBOL("XML-CALLBACK-FATAL-ERROR",
	    AB_package);
    SET_SYMBOL_VALUE(Qxml_callback_fatal_error,FIX((SI_Long)23L));
    Qxml_encoding_length = STATIC_SYMBOL("XML-ENCODING-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qxml_encoding_length,FIX((SI_Long)4L));
    Qxml_element_node = STATIC_SYMBOL("XML-ELEMENT-NODE",AB_package);
    SET_SYMBOL_VALUE(Qxml_element_node,FIX((SI_Long)1L));
    Qxml_attribute_node = STATIC_SYMBOL("XML-ATTRIBUTE-NODE",AB_package);
    SET_SYMBOL_VALUE(Qxml_attribute_node,FIX((SI_Long)2L));
    Qxml_text_node = STATIC_SYMBOL("XML-TEXT-NODE",AB_package);
    SET_SYMBOL_VALUE(Qxml_text_node,FIX((SI_Long)3L));
    Qxml_cdata_section_node = STATIC_SYMBOL("XML-CDATA-SECTION-NODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qxml_cdata_section_node,FIX((SI_Long)4L));
    Qxml_entity_reference_node = STATIC_SYMBOL("XML-ENTITY-REFERENCE-NODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qxml_entity_reference_node,FIX((SI_Long)5L));
    Qxml_entity_node = STATIC_SYMBOL("XML-ENTITY-NODE",AB_package);
    SET_SYMBOL_VALUE(Qxml_entity_node,FIX((SI_Long)6L));
    Qxml_processing_instruction_node = 
	    STATIC_SYMBOL("XML-PROCESSING-INSTRUCTION-NODE",AB_package);
    SET_SYMBOL_VALUE(Qxml_processing_instruction_node,FIX((SI_Long)7L));
    Qxml_comment_node = STATIC_SYMBOL("XML-COMMENT-NODE",AB_package);
    SET_SYMBOL_VALUE(Qxml_comment_node,FIX((SI_Long)8L));
    Qxml_document_node = STATIC_SYMBOL("XML-DOCUMENT-NODE",AB_package);
    SET_SYMBOL_VALUE(Qxml_document_node,FIX((SI_Long)9L));
    Qxml_document_type_node = STATIC_SYMBOL("XML-DOCUMENT-TYPE-NODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qxml_document_type_node,FIX((SI_Long)10L));
    Qxml_document_fragment_node = 
	    STATIC_SYMBOL("XML-DOCUMENT-FRAGMENT-NODE",AB_package);
    SET_SYMBOL_VALUE(Qxml_document_fragment_node,FIX((SI_Long)11L));
    Qxml_notation_node = STATIC_SYMBOL("XML-NOTATION-NODE",AB_package);
    SET_SYMBOL_VALUE(Qxml_notation_node,FIX((SI_Long)12L));
    Qmaximum_length_for_dom_strings = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-FOR-DOM-STRINGS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_length_for_dom_strings,
	    Maximum_length_for_user_text_strings);
    Qslot_description_cache_entry_size = 
	    STATIC_SYMBOL("SLOT-DESCRIPTION-CACHE-ENTRY-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qslot_description_cache_entry_size,FIX((SI_Long)4L));
    Qattribute_value_cache_entry_size = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-CACHE-ENTRY-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qattribute_value_cache_entry_size,FIX((SI_Long)3L));
    Qdenotation_element_overhead_slot_count = 
	    STATIC_SYMBOL("DENOTATION-ELEMENT-OVERHEAD-SLOT-COUNT",AB_package);
    SET_SYMBOL_VALUE(Qdenotation_element_overhead_slot_count,FIX((SI_Long)2L));
    Qmaximum_denotation_types = STATIC_SYMBOL("MAXIMUM-DENOTATION-TYPES",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_denotation_types,FIX((SI_Long)50L));
    Qmaximum_denotation_sequence_elements = 
	    STATIC_SYMBOL("MAXIMUM-DENOTATION-SEQUENCE-ELEMENTS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_denotation_sequence_elements,FIX((SI_Long)50L));
    Qattribute_particular_code = STATIC_SYMBOL("ATTRIBUTE-PARTICULAR-CODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qattribute_particular_code,FIX((SI_Long)1L));
    Qaliased_attribute_particular_code = 
	    STATIC_SYMBOL("ALIASED-ATTRIBUTE-PARTICULAR-CODE",AB_package);
    SET_SYMBOL_VALUE(Qaliased_attribute_particular_code,FIX((SI_Long)2L));
    Qelement_particular_code = STATIC_SYMBOL("ELEMENT-PARTICULAR-CODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qelement_particular_code,FIX((SI_Long)3L));
    Qvirtual_attribute_particular_code = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-PARTICULAR-CODE",AB_package);
    SET_SYMBOL_VALUE(Qvirtual_attribute_particular_code,FIX((SI_Long)4L));
    Qvariable_value_particular_code = 
	    STATIC_SYMBOL("VARIABLE-VALUE-PARTICULAR-CODE",AB_package);
    SET_SYMBOL_VALUE(Qvariable_value_particular_code,FIX((SI_Long)5L));
    Qten_years = STATIC_SYMBOL("TEN-YEARS",AB_package);
    SET_SYMBOL_VALUE(Qten_years,FIX((SI_Long)315360000L));
    Qmaximum_connection_dash_length = 
	    STATIC_SYMBOL("MAXIMUM-CONNECTION-DASH-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_connection_dash_length,FIX((SI_Long)127L));
    Qmaximum_connection_dash_count = 
	    STATIC_SYMBOL("MAXIMUM-CONNECTION-DASH-COUNT",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_connection_dash_count,FIX((SI_Long)256L));
    Qattribute_nesting_limit = STATIC_SYMBOL("ATTRIBUTE-NESTING-LIMIT",
	    AB_package);
    SET_SYMBOL_VALUE(Qattribute_nesting_limit,FIX((SI_Long)20L));
    Qmax_icon_size = STATIC_SYMBOL("MAX-ICON-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qmax_icon_size,FIX((SI_Long)100000L));
    Qmax_icon_area = STATIC_SYMBOL("MAX-ICON-AREA",AB_package);
    SET_SYMBOL_VALUE(Qmax_icon_area,FIX((SI_Long)2500000L));
    Qfloat_format_precision_limit = 
	    STATIC_SYMBOL("FLOAT-FORMAT-PRECISION-LIMIT",AB_package);
    SET_SYMBOL_VALUE(Qfloat_format_precision_limit,FIX((SI_Long)40L));
    Qframe_display_workspace_margin = 
	    STATIC_SYMBOL("FRAME-DISPLAY-WORKSPACE-MARGIN",AB_package);
    SET_SYMBOL_VALUE(Qframe_display_workspace_margin,FIX((SI_Long)30L));
    Qframe_display_vertical_spacing = 
	    STATIC_SYMBOL("FRAME-DISPLAY-VERTICAL-SPACING",AB_package);
    SET_SYMBOL_VALUE(Qframe_display_vertical_spacing,FIX((SI_Long)10L));
    Qframe_display_reformat_after_count_deleted = 
	    STATIC_SYMBOL("FRAME-DISPLAY-REFORMAT-AFTER-COUNT-DELETED",
	    AB_package);
    SET_SYMBOL_VALUE(Qframe_display_reformat_after_count_deleted,
	    FIX((SI_Long)3L));
    Qforeign_function_integer_type_tag = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-INTEGER-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qforeign_function_integer_type_tag,FIX((SI_Long)1L));
    Qforeign_function_real_type_tag = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-REAL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qforeign_function_real_type_tag,FIX((SI_Long)6L));
    Qforeign_function_symbol_type_tag = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-SYMBOL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qforeign_function_symbol_type_tag,FIX((SI_Long)3L));
    Qforeign_function_text_type_tag = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-TEXT-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qforeign_function_text_type_tag,FIX((SI_Long)4L));
    Qlargest_known_fixnum_time_units_per_second = 
	    STATIC_SYMBOL("LARGEST-KNOWN-FIXNUM-TIME-UNITS-PER-SECOND",
	    AB_package);
    SET_SYMBOL_VALUE(Qlargest_known_fixnum_time_units_per_second,
	    FIX((SI_Long)1000L));
    Qshutdown_context_only_flag_clear = 
	    STATIC_SYMBOL("SHUTDOWN-CONTEXT-ONLY-FLAG-CLEAR",AB_package);
    SET_SYMBOL_VALUE(Qshutdown_context_only_flag_clear,FIX((SI_Long)0L));
    Qshutdown_context_only_flag_set = 
	    STATIC_SYMBOL("SHUTDOWN-CONTEXT-ONLY-FLAG-SET",AB_package);
    SET_SYMBOL_VALUE(Qshutdown_context_only_flag_set,FIX((SI_Long)1L));
    Qffs_unspecified_error = STATIC_SYMBOL("FFS_UNSPECIFIED_ERROR",AB_package);
    SET_SYMBOL_VALUE(Qffs_unspecified_error,FIX((SI_Long)1L));
    Qffs_connection_open_already = 
	    STATIC_SYMBOL("FFS_CONNECTION_OPEN_ALREADY",AB_package);
    SET_SYMBOL_VALUE(Qffs_connection_open_already,FIX((SI_Long)2L));
    Qffs_signal_caught_during_call = 
	    STATIC_SYMBOL("FFS_SIGNAL_CAUGHT_DURING_CALL",AB_package);
    SET_SYMBOL_VALUE(Qffs_signal_caught_during_call,FIX((SI_Long)3L));
    Qffs_unknown_function = STATIC_SYMBOL("FFS_UNKNOWN_FUNCTION",AB_package);
    SET_SYMBOL_VALUE(Qffs_unknown_function,FIX((SI_Long)4L));
    Qffs_unknown_return_type = STATIC_SYMBOL("FFS_UNKNOWN_RETURN_TYPE",
	    AB_package);
    SET_SYMBOL_VALUE(Qffs_unknown_return_type,FIX((SI_Long)5L));
    Qmaximum_gfi_output_queue_count = 
	    STATIC_SYMBOL("MAXIMUM-GFI-OUTPUT-QUEUE-COUNT",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_gfi_output_queue_count,FIX((SI_Long)100L));
    Qiterations_for_gsi_temporary_float_processing = 
	    STATIC_SYMBOL("ITERATIONS-FOR-GSI-TEMPORARY-FLOAT-PROCESSING",
	    AB_package);
    SET_SYMBOL_VALUE(Qiterations_for_gsi_temporary_float_processing,
	    FIX((SI_Long)100L));
    Qg2ds_null_type_tag = STATIC_SYMBOL("G2DS-NULL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_null_type_tag,FIX((SI_Long)0L));
    Qg2ds_integer_type_tag = STATIC_SYMBOL("G2DS-INTEGER-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_integer_type_tag,FIX((SI_Long)1L));
    Qg2ds_float_type_tag = STATIC_SYMBOL("G2DS-FLOAT-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_float_type_tag,FIX((SI_Long)2L));
    Qg2ds_symbol_type_tag = STATIC_SYMBOL("G2DS-SYMBOL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_symbol_type_tag,FIX((SI_Long)3L));
    Qg2ds_string_type_tag = STATIC_SYMBOL("G2DS-STRING-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_string_type_tag,FIX((SI_Long)4L));
    Qg2ds_list_type_tag = STATIC_SYMBOL("G2DS-LIST-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_list_type_tag,FIX((SI_Long)5L));
    Qg2ds_64bit_float_type_tag = STATIC_SYMBOL("G2DS-64BIT-FLOAT-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2ds_64bit_float_type_tag,FIX((SI_Long)6L));
    Qg2ds_dotted_list_type_tag = STATIC_SYMBOL("G2DS-DOTTED-LIST-TYPE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2ds_dotted_list_type_tag,FIX((SI_Long)7L));
    Qg2ds_evaluation_sequence_type_tag = 
	    STATIC_SYMBOL("G2DS-EVALUATION-SEQUENCE-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_evaluation_sequence_type_tag,FIX((SI_Long)8L));
    Qg2ds_evaluation_structure_type_tag = 
	    STATIC_SYMBOL("G2DS-EVALUATION-STRUCTURE-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_evaluation_structure_type_tag,FIX((SI_Long)9L));
    Qg2ds_logical_type_tag = STATIC_SYMBOL("G2DS-LOGICAL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_logical_type_tag,FIX((SI_Long)10L));
    Qg2ds_no_error = STATIC_SYMBOL("G2DS-NO-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_no_error,FIX((SI_Long)0L));
    Qdefault_g2ds_interface_countdown_timer_limit = 
	    STATIC_SYMBOL("DEFAULT-G2DS-INTERFACE-COUNTDOWN-TIMER-LIMIT",
	    AB_package);
    SET_SYMBOL_VALUE(Qdefault_g2ds_interface_countdown_timer_limit,
	    FIX((SI_Long)10L));
    Qg2ds_server_max_count_in_return_queue = 
	    STATIC_SYMBOL("G2DS-SERVER-MAX-COUNT-IN-RETURN-QUEUE",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_server_max_count_in_return_queue,FIX((SI_Long)20L));
    Qg2ds_read_expression_cell_index = 
	    STATIC_SYMBOL("G2DS-READ-EXPRESSION-CELL-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_read_expression_cell_index,FIX((SI_Long)0L));
    Qg2ds_write_expression_cell_index = 
	    STATIC_SYMBOL("G2DS-WRITE-EXPRESSION-CELL-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qg2ds_write_expression_cell_index,FIX((SI_Long)1L));
    Qiterations_for_g2ds_temporary_float_processing = 
	    STATIC_SYMBOL("ITERATIONS-FOR-G2DS-TEMPORARY-FLOAT-PROCESSING",
	    AB_package);
    SET_SYMBOL_VALUE(Qiterations_for_g2ds_temporary_float_processing,
	    FIX((SI_Long)100L));
    Qnupec_synchronize_datum_null_type = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM-NULL-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qnupec_synchronize_datum_null_type,FIX((SI_Long)0L));
    Qnupec_synchronize_datum_symbol_type = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM-SYMBOL-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qnupec_synchronize_datum_symbol_type,FIX((SI_Long)1L));
    Qnupec_synchronize_datum_integer_type = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM-INTEGER-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qnupec_synchronize_datum_integer_type,FIX((SI_Long)2L));
    Qnupec_synchronize_datum_float_type = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM-FLOAT-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qnupec_synchronize_datum_float_type,FIX((SI_Long)3L));
    Qnupec_synchronize_datum_text_type = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM-TEXT-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qnupec_synchronize_datum_text_type,FIX((SI_Long)4L));
    Qnupec_designation_null_type_tag = 
	    STATIC_SYMBOL("NUPEC-DESIGNATION-NULL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qnupec_designation_null_type_tag,FIX((SI_Long)0L));
    Qnupec_designation_symbol_type_tag = 
	    STATIC_SYMBOL("NUPEC-DESIGNATION-SYMBOL-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qnupec_designation_symbol_type_tag,FIX((SI_Long)1L));
    Qnupec_designation_cons_type_tag = 
	    STATIC_SYMBOL("NUPEC-DESIGNATION-CONS-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qnupec_designation_cons_type_tag,FIX((SI_Long)2L));
    Qstatus_bar_maximum_pane_count = 
	    STATIC_SYMBOL("STATUS-BAR-MAXIMUM-PANE-COUNT",AB_package);
    SET_SYMBOL_VALUE(Qstatus_bar_maximum_pane_count,FIX((SI_Long)250L));
    Qlogbook_destroy = STATIC_SYMBOL("LOGBOOK-DESTROY",AB_package);
    SET_SYMBOL_VALUE(Qlogbook_destroy,FIX((SI_Long)2L));
    Qlogbook_append_message = STATIC_SYMBOL("LOGBOOK-APPEND-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE(Qlogbook_append_message,FIX((SI_Long)10L));
    Qlogbook_delete_message = STATIC_SYMBOL("LOGBOOK-DELETE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE(Qlogbook_delete_message,FIX((SI_Long)11L));
    Qlogbook_normal_message = STATIC_SYMBOL("LOGBOOK-NORMAL-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE(Qlogbook_normal_message,FIX((SI_Long)12L));
    Qlogbook_fade_message = STATIC_SYMBOL("LOGBOOK-FADE-MESSAGE",AB_package);
    SET_SYMBOL_VALUE(Qlogbook_fade_message,FIX((SI_Long)13L));
    Qlogbook_highlight_message = STATIC_SYMBOL("LOGBOOK-HIGHLIGHT-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE(Qlogbook_highlight_message,FIX((SI_Long)14L));
    Qlogbook_set_line_wrap = STATIC_SYMBOL("LOGBOOK-SET-LINE-WRAP",AB_package);
    SET_SYMBOL_VALUE(Qlogbook_set_line_wrap,FIX((SI_Long)15L));
    Qlogbook_set_include_date_in_title = 
	    STATIC_SYMBOL("LOGBOOK-SET-INCLUDE-DATE-IN-TITLE",AB_package);
    SET_SYMBOL_VALUE(Qlogbook_set_include_date_in_title,FIX((SI_Long)16L));
    Qsmall_native_icon_size = STATIC_SYMBOL("SMALL-NATIVE-ICON-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qsmall_native_icon_size,FIX((SI_Long)16L));
    Qlarge_native_icon_size = STATIC_SYMBOL("LARGE-NATIVE-ICON-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qlarge_native_icon_size,FIX((SI_Long)32L));
    Qld_request_full_listing = STATIC_SYMBOL("LD-REQUEST-FULL-LISTING",
	    AB_package);
    SET_SYMBOL_VALUE(Qld_request_full_listing,FIX((SI_Long)0L));
    Qld_request_children = STATIC_SYMBOL("LD-REQUEST-CHILDREN",AB_package);
    SET_SYMBOL_VALUE(Qld_request_children,FIX((SI_Long)1L));
    Qld_request_refresh = STATIC_SYMBOL("LD-REQUEST-REFRESH",AB_package);
    SET_SYMBOL_VALUE(Qld_request_refresh,FIX((SI_Long)2L));
    Qhh_display_topic = STATIC_SYMBOL("HH-DISPLAY-TOPIC",AB_package);
    SET_SYMBOL_VALUE(Qhh_display_topic,FIX((SI_Long)0L));
    Qhh_display_toc = STATIC_SYMBOL("HH-DISPLAY-TOC",AB_package);
    SET_SYMBOL_VALUE(Qhh_display_toc,FIX((SI_Long)1L));
    Qhh_display_index = STATIC_SYMBOL("HH-DISPLAY-INDEX",AB_package);
    SET_SYMBOL_VALUE(Qhh_display_index,FIX((SI_Long)2L));
    Qhh_display_search = STATIC_SYMBOL("HH-DISPLAY-SEARCH",AB_package);
    SET_SYMBOL_VALUE(Qhh_display_search,FIX((SI_Long)3L));
    Qhh_sync = STATIC_SYMBOL("HH-SYNC",AB_package);
    SET_SYMBOL_VALUE(Qhh_sync,FIX((SI_Long)9L));
    Qhh_keyword_lookup = STATIC_SYMBOL("HH-KEYWORD-LOOKUP",AB_package);
    SET_SYMBOL_VALUE(Qhh_keyword_lookup,FIX((SI_Long)13L));
    Qhh_display_text_popup = STATIC_SYMBOL("HH-DISPLAY-TEXT-POPUP",AB_package);
    SET_SYMBOL_VALUE(Qhh_display_text_popup,FIX((SI_Long)14L));
    Qhh_help_context = STATIC_SYMBOL("HH-HELP-CONTEXT",AB_package);
    SET_SYMBOL_VALUE(Qhh_help_context,FIX((SI_Long)15L));
    Qhh_close_all = STATIC_SYMBOL("HH-CLOSE-ALL",AB_package);
    SET_SYMBOL_VALUE(Qhh_close_all,FIX((SI_Long)18L));
    Qhh_alink_lookup = STATIC_SYMBOL("HH-ALINK-LOOKUP",AB_package);
    SET_SYMBOL_VALUE(Qhh_alink_lookup,FIX((SI_Long)19L));
    Qmdi_normal_mode = STATIC_SYMBOL("MDI-NORMAL-MODE",AB_package);
    SET_SYMBOL_VALUE(Qmdi_normal_mode,FIX((SI_Long)1L));
    Qmdi_tabbed_mode = STATIC_SYMBOL("MDI-TABBED-MODE",AB_package);
    SET_SYMBOL_VALUE(Qmdi_tabbed_mode,FIX((SI_Long)2L));
    Qmdi_grouped_mode = STATIC_SYMBOL("MDI-GROUPED-MODE",AB_package);
    SET_SYMBOL_VALUE(Qmdi_grouped_mode,FIX((SI_Long)3L));
    Qmdi_show_icons = STATIC_SYMBOL("MDI-SHOW-ICONS",AB_package);
    SET_SYMBOL_VALUE(Qmdi_show_icons,FIX((SI_Long)4L));
    Qmdi_tab_position = STATIC_SYMBOL("MDI-TAB-POSITION",AB_package);
    SET_SYMBOL_VALUE(Qmdi_tab_position,FIX((SI_Long)5L));
    Qmdi_tab_layout = STATIC_SYMBOL("MDI-TAB-LAYOUT",AB_package);
    SET_SYMBOL_VALUE(Qmdi_tab_layout,FIX((SI_Long)6L));
    Qnumber_of_gsi_subtests = STATIC_SYMBOL("NUMBER-OF-GSI-SUBTESTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qnumber_of_gsi_subtests,FIX((SI_Long)7L));
    Qnumber_of_protocols = STATIC_SYMBOL("NUMBER-OF-PROTOCOLS",AB_package);
    SET_SYMBOL_VALUE(Qnumber_of_protocols,FIX((SI_Long)1L));
    Qtcpip_protocol = STATIC_SYMBOL("TCPIP-PROTOCOL",AB_package);
    SET_SYMBOL_VALUE(Qtcpip_protocol,FIX((SI_Long)0L));
    Qcall_site_minimum_size = STATIC_SYMBOL("CALL-SITE-MINIMUM-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qcall_site_minimum_size,FIX((SI_Long)5L));
    Qerrno_would_block = STATIC_SYMBOL("ERRNO-WOULD-BLOCK",AB_package);
    SET_SYMBOL_VALUE(Qerrno_would_block,FIX((SI_Long)35L));
    Qerrno_again = STATIC_SYMBOL("ERRNO-AGAIN",AB_package);
    SET_SYMBOL_VALUE(Qerrno_again,FIX((SI_Long)11L));
    Qenetreset = STATIC_SYMBOL("ENETRESET",AB_package);
    SET_SYMBOL_VALUE(Qenetreset,FIX((SI_Long)52L));
    Qeconnaborted = STATIC_SYMBOL("ECONNABORTED",AB_package);
    SET_SYMBOL_VALUE(Qeconnaborted,FIX((SI_Long)53L));
    Qjava_access_flag_public = STATIC_SYMBOL("JAVA-ACCESS-FLAG-PUBLIC",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_public,FIX((SI_Long)1L));
    Qjava_access_flag_private = STATIC_SYMBOL("JAVA-ACCESS-FLAG-PRIVATE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_private,FIX((SI_Long)2L));
    Qjava_access_flag_protected = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-PROTECTED",AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_protected,FIX((SI_Long)4L));
    Qjava_access_flag_static = STATIC_SYMBOL("JAVA-ACCESS-FLAG-STATIC",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_static,FIX((SI_Long)8L));
    Qjava_access_flag_final = STATIC_SYMBOL("JAVA-ACCESS-FLAG-FINAL",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_final,FIX((SI_Long)16L));
    Qjava_access_flag_super = STATIC_SYMBOL("JAVA-ACCESS-FLAG-SUPER",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_super,FIX((SI_Long)32L));
    Qjava_access_flag_synchronized = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-SYNCHRONIZED",AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_synchronized,FIX((SI_Long)32L));
    Qjava_access_flag_volatile = STATIC_SYMBOL("JAVA-ACCESS-FLAG-VOLATILE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_volatile,FIX((SI_Long)64L));
    Qjava_access_flag_transient = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-TRANSIENT",AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_transient,FIX((SI_Long)128L));
    Qjava_access_flag_native = STATIC_SYMBOL("JAVA-ACCESS-FLAG-NATIVE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_native,FIX((SI_Long)256L));
    Qjava_access_flag_interface = 
	    STATIC_SYMBOL("JAVA-ACCESS-FLAG-INTERFACE",AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_interface,FIX((SI_Long)512L));
    Qjava_access_flag_abstract = STATIC_SYMBOL("JAVA-ACCESS-FLAG-ABSTRACT",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_access_flag_abstract,FIX((SI_Long)1024L));
    Qjava_constant_class = STATIC_SYMBOL("JAVA-CONSTANT-CLASS",AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_class,FIX((SI_Long)7L));
    Qjava_constant_fieldref = STATIC_SYMBOL("JAVA-CONSTANT-FIELDREF",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_fieldref,FIX((SI_Long)9L));
    Qjava_constant_methodref = STATIC_SYMBOL("JAVA-CONSTANT-METHODREF",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_methodref,FIX((SI_Long)10L));
    Qjava_constant_interfacemethodref = 
	    STATIC_SYMBOL("JAVA-CONSTANT-INTERFACEMETHODREF",AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_interfacemethodref,FIX((SI_Long)11L));
    Qjava_constant_string = STATIC_SYMBOL("JAVA-CONSTANT-STRING",AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_string,FIX((SI_Long)8L));
    Qjava_constant_integer = STATIC_SYMBOL("JAVA-CONSTANT-INTEGER",AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_integer,FIX((SI_Long)3L));
    Qjava_constant_float = STATIC_SYMBOL("JAVA-CONSTANT-FLOAT",AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_float,FIX((SI_Long)4L));
    Qjava_constant_long = STATIC_SYMBOL("JAVA-CONSTANT-LONG",AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_long,FIX((SI_Long)5L));
    Qjava_constant_double = STATIC_SYMBOL("JAVA-CONSTANT-DOUBLE",AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_double,FIX((SI_Long)6L));
    Qjava_constant_nameandtype = STATIC_SYMBOL("JAVA-CONSTANT-NAMEANDTYPE",
	    AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_nameandtype,FIX((SI_Long)12L));
    Qjava_constant_utf8 = STATIC_SYMBOL("JAVA-CONSTANT-UTF8",AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_utf8,FIX((SI_Long)1L));
    Qjava_constant_unicode = STATIC_SYMBOL("JAVA-CONSTANT-UNICODE",AB_package);
    SET_SYMBOL_VALUE(Qjava_constant_unicode,FIX((SI_Long)2L));
}
