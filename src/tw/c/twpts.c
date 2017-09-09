/* twpts.c
 * Input file:  tw-patches.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "twpts.h"


/* SIGNAL-ERROR-FOR-UNDEFINED-FUNCTION-CALLED-FROM-TELEWINDOWS */
Object signal_error_for_undefined_function_called_from_telewindows()
{
    x_note_fn_call(5,0);
    return error((SI_Long)1L,
	    "a function not defined for Telewindows has been called in Telewindows");
}

Object Value_undefined_in_telewindows = UNBOUND;

Object Timing_parameters = UNBOUND;

Object Warmboot_simulated_time = UNBOUND;

Object Dequeuing_time = UNBOUND;

Object Warmbooting_qm = UNBOUND;

Object Current_kb_pathname_qm = UNBOUND;

Object Warmbooting_with_catch_up_qm = UNBOUND;

Object Warmboot_current_time = UNBOUND;

Object All_foreign_function_images = UNBOUND;

Object Known_process_ids = UNBOUND;

Object Player_state = UNBOUND;

Object Saved_initial_status = UNBOUND;

Object Global_grammar = UNBOUND;

Object Bad_phrase = UNBOUND;

Object Log_file_outputting_qm = UNBOUND;

Object Noting_changes_to_kb_p = UNBOUND;

Object Gsi_suppress_output = UNBOUND;

Object Default_workspace_frame_description = UNBOUND;

/* WRITE-NAME-DENOTATION-COMPONENTS */
Object write_name_denotation_components(name,defining_class_qm)
    Object name, defining_class_qm;
{
    x_note_fn_call(5,1);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* WRITE-NAME-DENOTATION */
Object write_name_denotation(name_denotation)
    Object name_denotation;
{
    x_note_fn_call(5,2);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* BLOCK-P-FUNCTION */
Object block_p_function(x)
    Object x;
{
    x_note_fn_call(5,3);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* TWRITE-DESIGNATION-FOR-ITEM */
Object twrite_designation_for_item(x)
    Object x;
{
    x_note_fn_call(5,4);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* FRAMEP-FUNCTION */
Object framep_function(x)
    Object x;
{
    x_note_fn_call(5,5);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* GET-OR-MAKE-UP-DESIGNATION-FOR-BLOCK */
Object get_or_make_up_designation_for_block(block)
    Object block;
{
    x_note_fn_call(5,6);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* PRINT-DESIGNATION */
Object print_designation(designation)
    Object designation;
{
    x_note_fn_call(5,7);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* WRITE-EXPRESSION */
Object write_expression(exp_1)
    Object exp_1;
{
    x_note_fn_call(5,8);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* WRITE-EVALUATION-VALUE */
Object write_evaluation_value(value)
    Object value;
{
    x_note_fn_call(5,9);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* PRINT-CONSTANT */
Object print_constant(constant_value,constant_type)
    Object constant_value, constant_type;
{
    x_note_fn_call(5,10);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* WARN-OF-BIG-BIGNUM */
Object warn_of_big_bignum(negative_qm)
    Object negative_qm;
{
    x_note_fn_call(5,11);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* MAKE-CALL-HASH-FUNCTION */
Object make_call_hash_function()
{
    x_note_fn_call(5,12);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* LAY-OUT-WINDOW */
Object lay_out_window(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(5,13);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* REFRESH-WINDOW */
Object refresh_window(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(5,14);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* G2-GLOBAL-PAINT-MODE-P */
Object g2_global_paint_mode_p()
{
    x_note_fn_call(5,15);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* NOTIFY-USER */
Object notify_user varargs_1(int, n)
{
    Object notification_as_format_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,16);
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
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-GSI-FOR-RECURSIVE-DESCENT */
Object run_gsi_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,17);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-GSPAN-FOR-RECURSIVE-DESCENT */
Object run_gspan_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,18);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-ICP-FOR-RECURSIVE-DESCENT */
Object run_icp_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,19);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-GFI-FOR-RECURSIVE-DESCENT */
Object run_gfi_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,20);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-KFEP-FOR-RECURSIVE-DESCENT */
Object run_kfep_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,21);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-RUNTIME-OPTION-FOR-RECURSIVE-DESCENT */
Object run_runtime_option_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,22);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-RESTRICTED-USE-OPTION-FOR-RECURSIVE-DESCENT */
Object run_restricted_use_option_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,23);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-EMBEDDED-OPTION-FOR-RECURSIVE-DESCENT */
Object run_embedded_option_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,24);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-CHINESE-FOR-RECURSIVE-DESCENT */
Object run_chinese_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,25);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-JAPANESE-FOR-RECURSIVE-DESCENT */
Object run_japanese_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,26);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-KOREAN-FOR-RECURSIVE-DESCENT */
Object run_korean_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,27);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-NUPEC-FOR-RECURSIVE-DESCENT */
Object run_nupec_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,28);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-G1-FOR-RECURSIVE-DESCENT */
Object run_g1_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,29);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-JL-FOR-RECURSIVE-DESCENT */
Object run_jl_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,30);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-JP-FOR-RECURSIVE-DESCENT */
Object run_jp_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,31);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-AL-FOR-RECURSIVE-DESCENT */
Object run_al_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,32);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RUN-ENT-FOR-RECURSIVE-DESCENT */
Object run_ent_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(5,33);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* KILL-POSSIBLY-LEFTOVER-SPAWNED-PROCESS */
Object kill_possibly_leftover_spawned_process(process_id)
    Object process_id;
{
    x_note_fn_call(5,34);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RECLAIM-SYSPROC-LIST-FUNCTION */
Object reclaim_sysproc_list_function(sysproc_list)
    Object sysproc_list;
{
    x_note_fn_call(5,35);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* REPLACE-FORMAT-USING-EQUIVALENT-FONT */
Object replace_format_using_equivalent_font(class_1)
    Object class_1;
{
    x_note_fn_call(5,36);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* REMOVE-GRAPH-RENDERING-FROM-GRAPH-GRID */
Object remove_graph_rendering_from_graph_grid(graph_rendering,
	    graph_grid_or_chart)
    Object graph_rendering, graph_grid_or_chart;
{
    x_note_fn_call(5,37);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* SIGNAL-FLOATING-POINT-EXCEPTION-STACK-ERROR */
Object signal_floating_point_exception_stack_error()
{
    x_note_fn_call(5,38);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* POLL-PLAYER */
Object poll_player()
{
    x_note_fn_call(5,39);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* WRITE-ERROR-TEXT */
Object write_error_text(x)
    Object x;
{
    x_note_fn_call(5,40);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* ABSORB-LOCAL-EVENT-AB-SIDE */
Object absorb_local_event_ab_side(local_event)
    Object local_event;
{
    x_note_fn_call(5,41);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* ABSORB-LOCAL-EVENT-AB-SIDE-1 */
Object absorb_local_event_ab_side_1(workstation,key_code,x,y,timestamp,plist)
    Object workstation, key_code, x, y, timestamp, plist;
{
    x_note_fn_call(5,42);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* GET-G2-WINDOW-GIVEN-ICP-SOCKET */
Object get_g2_window_given_icp_socket(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(5,43);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* GET-GENSYM-WINDOW-FOR-G2-WINDOW */
Object get_gensym_window_for_g2_window(window)
    Object window;
{
    x_note_fn_call(5,44);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* NOTIFY-ENGINEER */
Object notify_engineer varargs_1(int, n)
{
    Object notification_as_format_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,45);
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
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* COPY-GENSYM-WINDOW-ATTRIBUTES-INTO-G2-WINDOW */
Object copy_gensym_window_attributes_into_g2_window(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(5,46);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* G2-IDENTIFICATION-FOR-WRITE-LOCKS */
Object g2_identification_for_write_locks()
{
    x_note_fn_call(5,47);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* EQUAL-RULE-CONTEXT */
Object equal_rule_context(x,y)
    Object x, y;
{
    x_note_fn_call(5,48);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* GET-G2-LICENSE-LEVEL */
Object get_g2_license_level()
{
    x_note_fn_call(5,49);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* G2-HANDLE-SPAWN-REMOTE-PROCESS-REPLY */
Object g2_handle_spawn_remote_process_reply(index_of_result_parameter,
	    process_id)
    Object index_of_result_parameter, process_id;
{
    x_note_fn_call(5,50);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* G2-HANDLE-REMOTE-PROCESS-EXISTS-P-REPLY */
Object g2_handle_remote_process_exists_p_reply(index_of_result_parameter,
	    result_code)
    Object index_of_result_parameter, result_code;
{
    x_note_fn_call(5,51);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* G2-HANDLE-KILL-REMOTE-PROCESS-REPLY */
Object g2_handle_kill_remote_process_reply(index_of_result_parameter,
	    result_code)
    Object index_of_result_parameter, result_code;
{
    x_note_fn_call(5,52);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* HANDLE-PASTE-AVAILABILITY-EVENT-IN-G2 */
Object handle_paste_availability_event_in_g2(gensym_window,status,timestamp_qm)
    Object gensym_window, status, timestamp_qm;
{
    x_note_fn_call(5,53);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* HANDLE-PASTE-EVENT-IN-G2 */
Object handle_paste_event_in_g2(gensym_window,text_string,request_id,
	    timestamp_qm)
    Object gensym_window, text_string, request_id, timestamp_qm;
{
    x_note_fn_call(5,54);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* PAUSE-FOR-INTERNAL-ERROR */
Object pause_for_internal_error(message)
    Object message;
{
    x_note_fn_call(5,55);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* REPORT-SIMPLE-STRING-ALLOCATION */
Object report_simple_string_allocation(string_1)
    Object string_1;
{
    x_note_fn_call(5,56);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* REPORT-SIMPLE-STRING-RECLAMATION */
Object report_simple_string_reclamation(string_1,length_1)
    Object string_1, length_1;
{
    x_note_fn_call(5,57);
    return signal_error_for_undefined_function_called_from_telewindows();
}

/* RECLAIM-IF-EVALUATION-ITEM-REFERENCE */
Object reclaim_if_evaluation_item_reference(thing)
    Object thing;
{
    x_note_fn_call(5,58);
    return signal_error_for_undefined_function_called_from_telewindows();
}

void tw_patches_INIT()
{
    Object Qbogus_value, AB_package;

    x_note_fn_call(5,59);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qbogus_value = STATIC_SYMBOL("BOGUS-VALUE",AB_package);
    if (Value_undefined_in_telewindows == UNBOUND)
	Value_undefined_in_telewindows = Qbogus_value;
    if (Timing_parameters == UNBOUND)
	Timing_parameters = Value_undefined_in_telewindows;
    if (Warmboot_simulated_time == UNBOUND)
	Warmboot_simulated_time = Value_undefined_in_telewindows;
    if (Dequeuing_time == UNBOUND)
	Dequeuing_time = Value_undefined_in_telewindows;
    if (Warmbooting_qm == UNBOUND)
	Warmbooting_qm = Value_undefined_in_telewindows;
    if (Current_kb_pathname_qm == UNBOUND)
	Current_kb_pathname_qm = Value_undefined_in_telewindows;
    if (Warmbooting_with_catch_up_qm == UNBOUND)
	Warmbooting_with_catch_up_qm = Value_undefined_in_telewindows;
    if (Warmboot_current_time == UNBOUND)
	Warmboot_current_time = Value_undefined_in_telewindows;
    if (All_foreign_function_images == UNBOUND)
	All_foreign_function_images = Value_undefined_in_telewindows;
    if (Known_process_ids == UNBOUND)
	Known_process_ids = Value_undefined_in_telewindows;
    if (Player_state == UNBOUND)
	Player_state = Value_undefined_in_telewindows;
    if (Saved_initial_status == UNBOUND)
	Saved_initial_status = Value_undefined_in_telewindows;
    if (Global_grammar == UNBOUND)
	Global_grammar = Value_undefined_in_telewindows;
    if (Bad_phrase == UNBOUND)
	Bad_phrase = Value_undefined_in_telewindows;
    if (Log_file_outputting_qm == UNBOUND)
	Log_file_outputting_qm = Value_undefined_in_telewindows;
    if (Noting_changes_to_kb_p == UNBOUND)
	Noting_changes_to_kb_p = Value_undefined_in_telewindows;
    if (Gsi_suppress_output == UNBOUND)
	Gsi_suppress_output = Value_undefined_in_telewindows;
    Default_workspace_frame_description = Value_undefined_in_telewindows;
}
