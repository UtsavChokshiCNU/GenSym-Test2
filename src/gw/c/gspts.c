/* gspts.c
 * Input file:  gsi-patches.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gspts.h"


/* GET-GENSYM-WINDOW-PARAMETER */
Object g2int_get_gensym_window_parameter(gensym_window,parameter_name)
    Object gensym_window, parameter_name;
{
    x_note_fn_call(5,0);
    return VALUES_1(Nil);
}

/* GET-FRAME-WINDOW-TYPE */
Object g2int_get_frame_window_type(system_1)
    Object system_1;
{
    x_note_fn_call(5,1);
    return VALUES_1(Nil);
}

/* LOCAL-GENSYM-X11-DISPLAY */
Object g2int_local_gensym_x11_display()
{
    x_note_fn_call(5,2);
    return VALUES_1(Nil);
}

Object G2int_bytes_allocated_for_image_tiles = UNBOUND;

/* BYTES-ALLOCATED-FOR-IMAGE-TILES */
Object g2int_bytes_allocated_for_image_tiles()
{
    x_note_fn_call(5,3);
    return VALUES_1(Nil);
}

/* MAXIMUM-BYTES-FOR-IMAGE-TILES */
Object g2int_maximum_bytes_for_image_tiles()
{
    x_note_fn_call(5,4);
    return VALUES_1(Nil);
}

/* INSTALL-SYSTEM-TABLE */
Object g2int_install_system_table(system_table)
    Object system_table;
{
    x_note_fn_call(5,5);
    return VALUES_1(Nil);
}

/* WRITE-ERROR-TEXT */
Object g2int_write_error_text(error_text)
    Object error_text;
{
    x_note_fn_call(5,6);
    return VALUES_1(Nil);
}

/* NOTIFY-USER */
Object g2int_notify_user varargs_1(int, n)
{
    Object notification_as_format_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,7);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

Object G2int_x11_window = UNBOUND;

Object G2int_workstations_in_service = UNBOUND;

/* X11-DISPLAY-SPECIFIED-P */
Object g2int_x11_display_specified_p()
{
    x_note_fn_call(5,8);
    return VALUES_1(Nil);
}

/* NO-LOCAL-WINDOW-P */
Object g2int_no_local_window_p()
{
    x_note_fn_call(5,9);
    return VALUES_1(Nil);
}

/* X11-PREINITIALIZE-IF-NECESSARY */
Object g2int_x11_preinitialize_if_necessary()
{
    x_note_fn_call(5,10);
    return VALUES_1(Nil);
}

/* C-X11-INITIALIZE */
Object g2int_c_x11_initialize(a,b,c,d,e,f,g,h,i,j)
    Object a, b, c, d, e, f, g, h, i, j;
{
    x_note_fn_call(5,11);
    return VALUES_1(Nil);
}

/* GET-DEFAULT-X11-DISPLAY */
Object g2int_get_default_x11_display()
{
    x_note_fn_call(5,12);
    return VALUES_1(Nil);
}

/* GET-WINDOW-NAME-FROM-COMMAND-LINE-IF-ANY */
Object g2int_get_window_name_from_command_line_if_any()
{
    x_note_fn_call(5,13);
    return VALUES_1(Nil);
}

/* GET-ICON-NAME-FROM-COMMAND-LINE-IF-ANY */
Object g2int_get_icon_name_from_command_line_if_any()
{
    x_note_fn_call(5,14);
    return VALUES_1(Nil);
}

/* C-X11-CLOSE */
Object g2int_c_x11_close(gensym_x_window_index)
    Object gensym_x_window_index;
{
    x_note_fn_call(5,15);
    return VALUES_1(Nil);
}

/* X-EVENTS-PENDING? */
Object g2int_x_events_pendingqm()
{
    x_note_fn_call(5,16);
    return VALUES_1(FIX((SI_Long)0L));
}

/* PRINT-DISPLAY-ERROR */
Object g2int_print_display_error()
{
    x_note_fn_call(5,17);
    return VALUES_1(Nil);
}

/* GET-VALUES-FROM-X11-PARSE-GEOMETRY */
Object g2int_get_values_from_x11_parse_geometry(parsestring)
    Object parsestring;
{
    x_note_fn_call(5,18);
    return VALUES_1(Nil);
}

/* MAKE-OR-REVISE-WINDOW-PER-NATIVE-WINDOW */
Object g2int_make_or_revise_window_per_native_window(gensym_window_qm,
	    native_window)
    Object gensym_window_qm, native_window;
{
    x_note_fn_call(5,19);
    return VALUES_1(Nil);
}

Object G2int_do_not_initialize_g2_array_elements_p = UNBOUND;

/* WRITE-TYPE-SPECIFICATION */
Object g2int_write_type_specification(type_specification)
    Object type_specification;
{
    x_note_fn_call(5,20);
    return VALUES_1(Nil);
}

/* SIGNAL-FLOATING-POINT-EXCEPTION-STACK-ERROR */
Object g2int_signal_floating_point_exception_stack_error()
{
    x_note_fn_call(5,21);
    return VALUES_1(Nil);
}

/* EXIT-CURRENT-PROFILING-CONTEXT */
Object g2int_exit_current_profiling_context(current_time)
    Object current_time;
{
    x_note_fn_call(5,22);
    return VALUES_1(Nil);
}

/* POSIT-PROFILING-STRUCTURE */
Object g2int_posit_profiling_structure(current_task)
    Object current_task;
{
    x_note_fn_call(5,23);
    return VALUES_1(Nil);
}

/* MAKE-EVALUATION-TRUTH-VALUE-FUNCTION */
Object g2int_make_evaluation_truth_value_function(fixnum_truth_value)
    Object fixnum_truth_value;
{
    x_note_fn_call(5,24);
    return VALUES_1(Nil);
}

/* RECLAIM-EVALUATION-VALUE */
Object g2int_reclaim_evaluation_value(evaluation_value)
    Object evaluation_value;
{
    x_note_fn_call(5,25);
    return VALUES_1(Nil);
}

/* COPY-EVALUATION-VALUE-1 */
Object g2int_copy_evaluation_value_1(x)
    Object x;
{
    x_note_fn_call(5,26);
    return VALUES_1(Nil);
}

/* WRITE-BLOCK-OR-EVALUATION-VALUE */
Object g2int_write_block_or_evaluation_value(block_or_evaluation_value)
    Object block_or_evaluation_value;
{
    x_note_fn_call(5,27);
    return VALUES_1(Nil);
}

/* WRITE-EVALUATION-VALUE */
Object g2int_write_evaluation_value varargs_1(int, n)
{
    Object evaluation_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,28);
    INIT_ARGS_nonrelocating();
    evaluation_value = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* SHIFT-RULE-ORDERING-HEURISTICS */
Object g2int_shift_rule_ordering_heuristics()
{
    x_note_fn_call(5,29);
    return VALUES_1(Nil);
}

/* ENCODE-USER-PASSWORD-STRING-FUNCTION */
Object g2int_encode_user_password_string_function(string_1)
    Object string_1;
{
    x_note_fn_call(5,30);
    return VALUES_1(Nil);
}

/* CACHE-DEFERRED-RULE-INVOCATION-INDICES */
Object g2int_cache_deferred_rule_invocation_indices()
{
    x_note_fn_call(5,31);
    return VALUES_1(Nil);
}

/* RULE-INVOCATION-UPDATES-NEEDED-P */
Object g2int_rule_invocation_updates_needed_p()
{
    x_note_fn_call(5,32);
    return VALUES_1(Nil);
}

Object G2int_saved_initial_status = UNBOUND;

/* REPLACE-FORMAT-USING-EQUIVALENT-FONT */
Object g2int_replace_format_using_equivalent_font(class_1)
    Object class_1;
{
    x_note_fn_call(5,33);
    return VALUES_1(Nil);
}

/* KILL-FOREIGN-IMAGE-UNCONDITIONALLY */
Object g2int_kill_foreign_image_unconditionally(image_info)
    Object image_info;
{
    x_note_fn_call(5,34);
    return VALUES_1(Nil);
}

/* RECLAIM-SYSPROC-LIST-FUNCTION */
Object g2int_reclaim_sysproc_list_function(sysproc_list)
    Object sysproc_list;
{
    x_note_fn_call(5,35);
    return VALUES_1(Nil);
}

/* KILL-POSSIBLY-LEFTOVER-SPAWNED-PROCESS */
Object g2int_kill_possibly_leftover_spawned_process(process_id)
    Object process_id;
{
    x_note_fn_call(5,36);
    return VALUES_1(Nil);
}

/* MAKE-SYSTEM-FRAME */
Object g2int_make_system_frame(class_1)
    Object class_1;
{
    x_note_fn_call(5,37);
    return VALUES_1(Nil);
}

/* BLOCK-P-FUNCTION */
Object g2int_block_p_function(x)
    Object x;
{
    x_note_fn_call(5,38);
    return VALUES_1(Nil);
}

/* FRAMEP-FUNCTION */
Object g2int_framep_function(x)
    Object x;
{
    x_note_fn_call(5,39);
    return VALUES_1(Nil);
}

/* WRITE-NAME-DENOTATION */
Object g2int_write_name_denotation(name_denotation)
    Object name_denotation;
{
    x_note_fn_call(5,40);
    return VALUES_1(Nil);
}

/* RECLAIM-SLOT-VALUE-TREE-FUNCTION */
Object g2int_reclaim_slot_value_tree_function(tree)
    Object tree;
{
    x_note_fn_call(5,41);
    return VALUES_1(Nil);
}

/* WRITE-NAME-DENOTATION-COMPONENTS */
Object g2int_write_name_denotation_components(name,defining_class_qm)
    Object name, defining_class_qm;
{
    x_note_fn_call(5,42);
    return VALUES_1(Nil);
}

/* MAKE-WORKSPACE */
Object g2int_make_workspace varargs_1(int, n)
{
    Object class_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,43);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* WRITE-NAME-DENOTATION-FOR-SLOT */
Object g2int_write_name_denotation_for_slot(slot_description,class_description)
    Object slot_description, class_description;
{
    x_note_fn_call(5,44);
    return VALUES_1(Nil);
}

/* NAME-AND-CLASS-FOR-COMPUTATION-INSTANCE */
Object g2int_name_and_class_for_computation_instance(x)
    Object x;
{
    x_note_fn_call(5,45);
    return VALUES_1(Nil);
}

/* GET-OR-MAKE-UP-DESIGNATION-FOR-BLOCK */
Object g2int_get_or_make_up_designation_for_block(block)
    Object block;
{
    x_note_fn_call(5,46);
    return VALUES_1(Nil);
}

/* TWRITE-DESIGNATION-FOR-ITEM */
Object g2int_twrite_designation_for_item(block)
    Object block;
{
    x_note_fn_call(5,47);
    return VALUES_1(Nil);
}

/* PRINT-CONSTANT */
Object g2int_print_constant varargs_1(int, n)
{
    Object constant_value, constant_type;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,48);
    INIT_ARGS_nonrelocating();
    constant_value = REQUIRED_ARG_nonrelocating();
    constant_type = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* WRITE-EXPRESSION */
Object g2int_write_expression(exp_1)
    Object exp_1;
{
    x_note_fn_call(5,49);
    return VALUES_1(Nil);
}

/* PRINT-DESIGNATION */
Object g2int_print_designation(designation)
    Object designation;
{
    x_note_fn_call(5,50);
    return VALUES_1(Nil);
}

/* WARN-OF-BIG-BIGNUM */
Object g2int_warn_of_big_bignum(negative_qm)
    Object negative_qm;
{
    x_note_fn_call(5,51);
    return VALUES_1(Nil);
}

/* COMPUTE-NEWEST-THRASHING-RATIO */
Object g2int_compute_newest_thrashing_ratio(limit_info,time_since_last_update)
    Object limit_info, time_since_last_update;
{
    x_note_fn_call(5,52);
    return VALUES_1(Nil);
}

/* EQUAL-RULE-CONTEXT */
Object g2int_equal_rule_context(rule_context_1,rule_context_2)
    Object rule_context_1, rule_context_2;
{
    x_note_fn_call(5,53);
    return VALUES_1(Nil);
}

/* ADD-TO-WORKSPACE */
Object g2int_add_to_workspace varargs_1(int, n)
{
    Object block, workspace, left_edge_for_block, top_edge_for_block;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,54);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    left_edge_for_block = REQUIRED_ARG_nonrelocating();
    top_edge_for_block = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* LOOKUP-FRAME-DESCRIPTION-REFERENCE-OF-FRAME-STYLE */
Object g2int_lookup_frame_description_reference_of_frame_style(frame_style,
	    default_frame_style)
    Object frame_style, default_frame_style;
{
    x_note_fn_call(5,55);
    return VALUES_1(Nil);
}

/* MAKE-DIALOG-MESSAGE */
Object g2int_make_dialog_message(constant_string)
    Object constant_string;
{
    x_note_fn_call(5,56);
    return VALUES_1(Nil);
}

/* RECLAIM-TEXT */
Object g2int_reclaim_text(text)
    Object text;
{
    x_note_fn_call(5,57);
    return VALUES_1(Nil);
}

/* MAKE-DIALOG-BUTTON */
Object g2int_make_dialog_button(constant_string,translation,
	    this_is_the_default_button_qm)
    Object constant_string, translation, this_is_the_default_button_qm;
{
    x_note_fn_call(5,58);
    return VALUES_1(Nil);
}

/* DETAIL-PANE */
Object g2int_detail_pane(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(5,59);
    return VALUES_1(Nil);
}

/* GET-AVAILABLE-IMAGE-PLANE */
Object g2int_get_available_image_plane(pane,frame_description_reference,
	    on_the_bottom_qm)
    Object pane, frame_description_reference, on_the_bottom_qm;
{
    x_note_fn_call(5,60);
    return VALUES_1(Nil);
}

/* PUT-IMAGE-ON-IMAGE-PLANE */
Object g2int_put_image_on_image_plane(image_plane,workspace,
	    new_image_x_scale_qm,new_image_y_scale_qm,
	    fraction_of_image_width_or_height_to_have_within_pane_qm,
	    block_to_position_on_qm,x_in_workspace_qm,y_in_workspace_qm,
	    x_in_window_qm,y_in_window_qm)
    Object image_plane, workspace, new_image_x_scale_qm, new_image_y_scale_qm;
    Object fraction_of_image_width_or_height_to_have_within_pane_qm;
    Object block_to_position_on_qm, x_in_workspace_qm, y_in_workspace_qm;
    Object x_in_window_qm, y_in_window_qm;
{
    x_note_fn_call(5,61);
    return VALUES_1(Nil);
}

Object G2int_log_file_outputtingqm = UNBOUND;

/* CLOSE-LOG-FILE */
Object g2int_close_log_file()
{
    x_note_fn_call(5,62);
    return VALUES_1(Nil);
}

/* NOTIFY-ENGINEER */
Object g2int_notify_engineer varargs_1(int, n)
{
    Object notification_as_format_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,63);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* POST-ON-MESSAGE-BOARD */
Object g2int_post_on_message_board varargs_1(int, n)
{
    Object text_line, urgency_qm, duration_qm, origin_frame_qm, destination_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,64);
    INIT_ARGS_nonrelocating();
    text_line = REQUIRED_ARG_nonrelocating();
    urgency_qm = REQUIRED_ARG_nonrelocating();
    duration_qm = REQUIRED_ARG_nonrelocating();
    origin_frame_qm = REQUIRED_ARG_nonrelocating();
    destination_qm = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* PAUSE-FOR-INTERNAL-ERROR */
Object g2int_pause_for_internal_error(message)
    Object message;
{
    x_note_fn_call(5,65);
    return VALUES_1(Nil);
}

/* SYSTEM-PAUSE */
Object g2int_system_pause()
{
    x_note_fn_call(5,66);
    return VALUES_1(Nil);
}

/* RUN-EMBEDDED-OPTION-FOR-RECURSIVE-DESCENT */
Object g2int_run_embedded_option_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,67);
    return VALUES_1(Nil);
}

/* RUN-GFI-FOR-RECURSIVE-DESCENT */
Object g2int_run_gfi_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,68);
    return VALUES_1(Nil);
}

/* RUN-GSI-FOR-RECURSIVE-DESCENT */
Object g2int_run_gsi_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,69);
    return VALUES_1(Nil);
}

/* RUN-ICP-FOR-RECURSIVE-DESCENT */
Object g2int_run_icp_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,70);
    return VALUES_1(Nil);
}

/* RUN-CHINESE-FOR-RECURSIVE-DESCENT */
Object g2int_run_chinese_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,71);
    return VALUES_1(Nil);
}

/* RUN-JAPANESE-FOR-RECURSIVE-DESCENT */
Object g2int_run_japanese_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,72);
    return VALUES_1(Nil);
}

/* RUN-KFEP-FOR-RECURSIVE-DESCENT */
Object g2int_run_kfep_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,73);
    return VALUES_1(Nil);
}

/* RUN-KOREAN-FOR-RECURSIVE-DESCENT */
Object g2int_run_korean_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,74);
    return VALUES_1(Nil);
}

/* RUN-NUPEC-FOR-RECURSIVE-DESCENT */
Object g2int_run_nupec_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,75);
    return VALUES_1(Nil);
}

/* RUN-RUNTIME-OPTION-FOR-RECURSIVE-DESCENT */
Object g2int_run_runtime_option_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,76);
    return VALUES_1(Nil);
}

/* RUN-G1-FOR-RECURSIVE-DESCENT */
Object g2int_run_g1_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,77);
    return VALUES_1(Nil);
}

/* RUN-JL-FOR-RECURSIVE-DESCENT */
Object g2int_run_jl_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,78);
    return VALUES_1(Nil);
}

/* RUN-JP-FOR-RECURSIVE-DESCENT */
Object g2int_run_jp_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,79);
    return VALUES_1(Nil);
}

/* RUN-AL-FOR-RECURSIVE-DESCENT */
Object g2int_run_al_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,80);
    return VALUES_1(Nil);
}

/* RUN-ENT-FOR-RECURSIVE-DESCENT */
Object g2int_run_ent_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,81);
    return VALUES_1(Nil);
}

/* RUN-RESTRICTED-USE-OPTION-FOR-RECURSIVE-DESCENT */
Object g2int_run_restricted_use_option_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,82);
    return VALUES_1(Nil);
}

/* G2-CANCEL-FLUSH-OF-PARTIAL-ICP-BUFFER */
Object g2int_g2_cancel_flush_of_partial_icp_buffer()
{
    x_note_fn_call(5,83);
    return VALUES_1(Nil);
}

/* G2-PRIORITY-OF-DATA-SERVICE-FUNCTION */
Object g2int_g2_priority_of_data_service_function()
{
    x_note_fn_call(5,84);
    return VALUES_1(Nil);
}

/* ITEM-REFERENCES-ENABLED-P */
Object g2int_item_references_enabled_p(socket_1)
    Object socket_1;
{
    x_note_fn_call(5,85);
    return VALUES_1(Nil);
}

/* NETWORK-ACCESS-ALLOWED-P */
Object g2int_network_access_allowed_p varargs_1(int, n)
{
    Object access_agent, access_type;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,86);
    INIT_ARGS_nonrelocating();
    access_agent = REQUIRED_ARG_nonrelocating();
    access_type = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* G2-IDENTIFICATION-FOR-WRITE-LOCKS */
Object g2int_g2_identification_for_write_locks()
{
    x_note_fn_call(5,87);
    return VALUES_1(Nil);
}

/* HANDLE-UNCLOGGED-CONNECTION-IF-NECESSARY */
Object g2int_handle_unclogged_connection_if_necessary(i_am_alive_info)
    Object i_am_alive_info;
{
    x_note_fn_call(5,88);
    return VALUES_1(Nil);
}

Object G2int_time_slice_expired_p = UNBOUND;

/* DEFINE-OR-CONFIGURE-GSI-SENSOR */
Object g2int_define_or_configure_gsi_sensor(sensor,
	    corresponding_icp_object_index,gsi_interface)
    Object sensor, corresponding_icp_object_index, gsi_interface;
{
    x_note_fn_call(5,89);
    return VALUES_1(Nil);
}

/* GET-GSI-INTERFACE-FOR-GSI-SENSOR-IF-ANY */
Object g2int_get_gsi_interface_for_gsi_sensor_if_any(gsi_sensor)
    Object gsi_sensor;
{
    x_note_fn_call(5,90);
    return VALUES_1(Nil);
}

/* GSI-RECEIVE-VALUE-FOR-GSI-SENSOR */
Object g2int_gsi_receive_value_for_gsi_sensor(gsi_sensor,error_code,
	    value_qm,collection_time_qm,value_vector_qm)
    Object gsi_sensor, error_code, value_qm, collection_time_qm;
    Object value_vector_qm;
{
    x_note_fn_call(5,91);
    return VALUES_1(Nil);
}

/* GSI-RECEIVE-VALUE-FOR-PING-REQUEST */
Object g2int_gsi_receive_value_for_ping_request(gsi_interface,year,month,
	    day,hour,minute,second_1,status)
    Object gsi_interface, year, month, day, hour, minute, second_1, status;
{
    x_note_fn_call(5,92);
    return VALUES_1(Nil);
}

/* ABORT-RPC-CALL-AND-RECLAIM-IDENTIFIER */
Object g2int_abort_rpc_call_and_reclaim_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    x_note_fn_call(5,93);
    return VALUES_1(Nil);
}

/* SIGNAL-ERROR-TO-RPC-CALLER-AND-RECLAIM-IDENTIFIER */
Object g2int_signal_error_to_rpc_caller_and_reclaim_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    x_note_fn_call(5,94);
    return VALUES_1(Nil);
}

/* G2-RECLAIM-SENDING-RESUMABLE-OBJECT */
Object g2int_g2_reclaim_sending_resumable_object(resumable_object)
    Object resumable_object;
{
    x_note_fn_call(5,95);
    return VALUES_1(Nil);
}

/* RECLAIM-EVALUATION-VALUE-IF-ANY-FUNCTION */
Object g2int_reclaim_evaluation_value_if_any_function(evaluation_value_qm)
    Object evaluation_value_qm;
{
    x_note_fn_call(5,96);
    return VALUES_1(Nil);
}

Object G2int_timing_parameters = UNBOUND;

/* SCHEDULER-MODE-FUNCTION */
Object g2int_scheduler_mode_function(timing_parameters)
    Object timing_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(5,97);
    PUSH_SPECIAL(G2int_timing_parameters,timing_parameters,0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* MINIMUM-SCHEDULING-INTERVAL-FUNCTION */
Object g2int_minimum_scheduling_interval_function(timing_parameters)
    Object timing_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(5,98);
    PUSH_SPECIAL(G2int_timing_parameters,timing_parameters,0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

Object G2int_warmbootingqm = UNBOUND;

Object G2int_warmbooting_with_catch_upqm = UNBOUND;

Object G2int_warmboot_current_time = UNBOUND;

Object G2int_warmboot_simulated_time = UNBOUND;

/* TAKE-ACTIONS-AT-START-OF-CLOCK-TICK */
Object g2int_take_actions_at_start_of_clock_tick(fixnum_time_length_of_previous_tick)
    Object fixnum_time_length_of_previous_tick;
{
    x_note_fn_call(5,99);
    return VALUES_1(Nil);
}

/* ADD-DELTA-TIME-TO-VARIABLES-AND-PARAMETERS */
Object g2int_add_delta_time_to_variables_and_parameters(managed_float_delta)
    Object managed_float_delta;
{
    x_note_fn_call(5,100);
    return VALUES_1(Nil);
}

/* UPDATE-TREND-CHARTS-FOR-CLOCK-DISCONTINUITY */
Object g2int_update_trend_charts_for_clock_discontinuity(time_delta)
    Object time_delta;
{
    x_note_fn_call(5,101);
    return VALUES_1(Nil);
}

/* CACHE-MAIN-THREAD-ID */
Object g2int_cache_main_thread_id()
{
    x_note_fn_call(5,102);
    return VALUES_1(Nil);
}

Object G2int_system_window = UNBOUND;

/* DO-ALL-OLE-INITIALIZATION */
Object g2int_do_all_ole_initialization(system_window)
    Object system_window;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(5,103);
    PUSH_SPECIAL(G2int_system_window,system_window,0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* DO-ALL-OLE-CLEANUP */
Object g2int_do_all_ole_cleanup(system_window)
    Object system_window;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(5,104);
    PUSH_SPECIAL(G2int_system_window,system_window,0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* SCHEDULE-G2-LEGACY-HEARTBEAT-TASKS-IF-NECESSARY */
Object g2int_schedule_g2_legacy_heartbeat_tasks_if_necessary()
{
    x_note_fn_call(5,105);
    return VALUES_1(Nil);
}

/* REPORT-SIMPLE-STRING-ALLOCATION */
Object g2int_report_simple_string_allocation(string_1)
    Object string_1;
{
    x_note_fn_call(5,106);
    return VALUES_1(Nil);
}

/* REPORT-SIMPLE-STRING-RECLAMATION */
Object g2int_report_simple_string_reclamation(string_1,length_1)
    Object string_1, length_1;
{
    x_note_fn_call(5,107);
    return VALUES_1(Nil);
}

void gsi_patches_INIT()
{
    x_note_fn_call(5,108);
    SET_PACKAGE("AB");
    if (G2int_bytes_allocated_for_image_tiles == UNBOUND)
	G2int_bytes_allocated_for_image_tiles = Nil;
    if (G2int_x11_window == UNBOUND)
	G2int_x11_window = Nil;
    if (G2int_workstations_in_service == UNBOUND)
	G2int_workstations_in_service = Nil;
    if (G2int_do_not_initialize_g2_array_elements_p == UNBOUND)
	G2int_do_not_initialize_g2_array_elements_p = Nil;
    if (G2int_saved_initial_status == UNBOUND)
	G2int_saved_initial_status = Nil;
    if (G2int_log_file_outputtingqm == UNBOUND)
	G2int_log_file_outputtingqm = Nil;
    if (G2int_time_slice_expired_p == UNBOUND)
	G2int_time_slice_expired_p = Nil;
    if (G2int_timing_parameters == UNBOUND)
	G2int_timing_parameters = Nil;
    if (G2int_warmbootingqm == UNBOUND)
	G2int_warmbootingqm = Nil;
    if (G2int_warmbooting_with_catch_upqm == UNBOUND)
	G2int_warmbooting_with_catch_upqm = Nil;
    if (G2int_warmboot_current_time == UNBOUND)
	G2int_warmboot_current_time = Nil;
    if (G2int_warmboot_simulated_time == UNBOUND)
	G2int_warmboot_simulated_time = Nil;
}
