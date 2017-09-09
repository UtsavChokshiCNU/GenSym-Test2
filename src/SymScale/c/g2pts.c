/* g2pts.c
 * Input file:  g2-patches.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2pts.h"


DEFINE_VARIABLE_WITH_SYMBOL(Compilations_were_removed_in_this_kb_module_qm, Qcompilations_were_removed_in_this_kb_module_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_telewindows_workstation, Qcurrent_telewindows_workstation);

/* RUN-ONE-TW-SCHEDULER-CYCLE */
Object run_one_tw_scheduler_cycle()
{
    x_note_fn_call(5,0);
    return VALUES_1(Nil);
}

/* GET-TELEWINDOWS-COMMAND-LINE-ARGS-IF-VALID */
Object get_telewindows_command_line_args_if_valid()
{
    x_note_fn_call(5,1);
    return VALUES_1(Nil);
}

/* SEND-TELEWINDOWS-WORKSTATION-EVENT */
Object send_telewindows_workstation_event(workstation,event)
    Object workstation, event;
{
    x_note_fn_call(5,2);
    return VALUES_1(Nil);
}

/* ACCEPT-TELEWINDOWS-CONNECTION-LICENSE-LEVEL */
Object accept_telewindows_connection_license_level(gensym_window,
	    license_level_1)
    Object gensym_window, license_level_1;
{
    x_note_fn_call(5,3);
    return VALUES_1(Nil);
}

/* ACCEPT-TELEWINDOWS-CONNECTION-LICENSE-INFO */
Object accept_telewindows_connection_license_info(gensym_window,info)
    Object gensym_window, info;
{
    x_note_fn_call(5,4);
    return VALUES_1(Nil);
}

/* ACCEPT-SAVED-USER-SETTINGS-FOR-TELEWINDOWS */
Object accept_saved_user_settings_for_telewindows(gensym_window,
	    user_settings_plist)
    Object gensym_window, user_settings_plist;
{
    x_note_fn_call(5,5);
    return VALUES_1(Nil);
}

/* REROUTE-TELEWINDOWS-CONNECTION */
Object reroute_telewindows_connection(gensym_window,protocol,host,port,
	    init_string)
    Object gensym_window, protocol, host, port, init_string;
{
    x_note_fn_call(5,6);
    return VALUES_1(Nil);
}

/* WRITE-LIST-OF-TEXT-LINES-TO-GENSYM-WINDOW */
Object write_list_of_text_lines_to_gensym_window(gensym_window,
	    list_of_text_lines,font_size,clear_window_qm,new_paragraph_qm)
    Object gensym_window, list_of_text_lines, font_size, clear_window_qm;
    Object new_paragraph_qm;
{
    x_note_fn_call(5,7);
    return VALUES_1(Nil);
}

/* PASTE-FOR-TELEWINDOWS */
Object paste_for_telewindows(gensym_window,text_string,request_id)
    Object gensym_window, text_string, request_id;
{
    x_note_fn_call(5,8);
    return VALUES_1(Nil);
}

/* UPDATE-PASTE-AVAILABILITY-STATUS-FOR-TELEWINDOWS */
Object update_paste_availability_status_for_telewindows(gensym_window,status)
    Object gensym_window, status;
{
    x_note_fn_call(5,9);
    return VALUES_1(Nil);
}

/* REFRESH-TELEWINDOW */
Object refresh_telewindow varargs_1(int, n)
{
    Object gensym_window, native_window;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,10);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    native_window = REQUIRED_ARG_nonrelocating();
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

/* RESHAPE-TELEWINDOW */
Object reshape_telewindow(gensym_window,native_window)
    Object gensym_window, native_window;
{
    x_note_fn_call(5,11);
    return VALUES_1(Nil);
}

/* TELEWINDOWS-CHECK-VERSION-OF-REMOTE-G2 */
Object telewindows_check_version_of_remote_g2(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(5,12);
    return VALUES_1(Nil);
}

/* ABORT-TELEWINDOWS-FOR-PROTOCOL-OUT-OF-SYNCH-CASE-6 */
Object abort_telewindows_for_protocol_out_of_synch_case_6()
{
    x_note_fn_call(5,13);
    return VALUES_1(Nil);
}

/* ABORT-TELEWINDOWS-TOP-LEVEL */
Object abort_telewindows_top_level(reason)
    Object reason;
{
    x_note_fn_call(5,14);
    return VALUES_1(Nil);
}

/* TELEWINDOWS-AUTHORIZED-FOR-JAPANESE-P */
Object telewindows_authorized_for_japanese_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(5,15);
    return VALUES_1(Nil);
}

/* TELEWINDOWS-AUTHORIZED-FOR-KOREAN-P */
Object telewindows_authorized_for_korean_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(5,16);
    return VALUES_1(Nil);
}

/* TELEWINDOWS-AUTHORIZED-FOR-CHINESE-P */
Object telewindows_authorized_for_chinese_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(5,17);
    return VALUES_1(Nil);
}

/* TELEWINDOWS-ICP-SOCKET?-FUNCTION */
Object telewindows_icp_socket_qm_function(telewindows_workstation)
    Object telewindows_workstation;
{
    x_note_fn_call(5,18);
    return VALUES_1(Nil);
}

/* GSI-PRIORITY-OF-DATA-SERVICE-FUNCTION */
Object gsi_priority_of_data_service_function()
{
    x_note_fn_call(5,19);
    return VALUES_1(Nil);
}

/* TW-PRIORITY-OF-DATA-SERVICE-FUNCTION */
Object tw_priority_of_data_service_function()
{
    x_note_fn_call(5,20);
    return VALUES_1(Nil);
}

/* ENTERING-SIGNAL-HANDLER-FUNCTION */
Object entering_signal_handler_function()
{
    x_note_fn_call(5,21);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Derived_icp_input_port, Qderived_icp_input_port);

DEFINE_VARIABLE_WITH_SYMBOL(Derived_icp_output_port, Qderived_icp_output_port);

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_maximum_contexts_exceeded, Qgsi_maximum_contexts_exceeded);

/* RUN-ONE-GSI-SCHEDULER-CYCLE */
Object run_one_gsi_scheduler_cycle()
{
    x_note_fn_call(5,22);
    return VALUES_1(Nil);
}

/* SIGNAL-GSI-NETWORK-ERROR */
Object signal_gsi_network_error(x,y)
    Object x, y;
{
    x_note_fn_call(5,23);
    return VALUES_1(Nil);
}

/* GSI-CHECK-IF-ALL-ITEMS-ARE-BUILT */
Object gsi_check_if_all_items_are_built(x)
    Object x;
{
    x_note_fn_call(5,24);
    return VALUES_1(Nil);
}

/* GET-ICP-SOCKET-FROM-CONTEXT */
Object get_icp_socket_from_context(x,y)
    Object x, y;
{
    x_note_fn_call(5,25);
    return VALUES_1(Nil);
}

/* GSI-WARNING */
Object gsi_warning varargs_1(int, n)
{
    Object x, y;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,26);
    INIT_ARGS_nonrelocating();
    x = REQUIRED_ARG_nonrelocating();
    y = REQUIRED_ARG_nonrelocating();
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

/* GSI-ERROR */
Object gsi_error varargs_1(int, n)
{
    Object x, y;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,27);
    INIT_ARGS_nonrelocating();
    x = REQUIRED_ARG_nonrelocating();
    y = REQUIRED_ARG_nonrelocating();
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

/* GSI-CONNECTION-ERROR */
Object gsi_connection_error varargs_1(int, n)
{
    Object x, y;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,28);
    INIT_ARGS_nonrelocating();
    x = REQUIRED_ARG_nonrelocating();
    y = REQUIRED_ARG_nonrelocating();
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

/* GSI-FATAL-ERROR */
Object gsi_fatal_error varargs_1(int, n)
{
    Object x, y;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,29);
    INIT_ARGS_nonrelocating();
    x = REQUIRED_ARG_nonrelocating();
    y = REQUIRED_ARG_nonrelocating();
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

/* RESOLVE-GSI-CONTEXT */
Object resolve_gsi_context(context,function_name)
    Object context, function_name;
{
    x_note_fn_call(5,30);
    return VALUES_1(Nil);
}

/* GSI-MAYBE-INITIATE-DELAYED-CONNECTION */
Object gsi_maybe_initiate_delayed_connection(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(5,31);
    return VALUES_1(Nil);
}

/* GSI-FAILURE-P */
Object gsi_failure_p(value)
    Object value;
{
    x_note_fn_call(5,32);
    return VALUES_1(Nil);
}

/* FIND-NEW-GSI-CONTEXT */
Object find_new_gsi_context()
{
    x_note_fn_call(5,33);
    return VALUES_1(Nil);
}

/* GSI-MESSAGE */
Object gsi_message varargs_1(int, n)
{
    Object message_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,34);
    INIT_ARGS_nonrelocating();
    message_1 = REQUIRED_ARG_nonrelocating();
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

/* RECLAIM-GSI-REMOTE-PROCEDURES */
Object reclaim_gsi_remote_procedures(list_1)
    Object list_1;
{
    x_note_fn_call(5,35);
    return VALUES_1(Nil);
}

/* RECLAIM-GSI-TRANSFER-WRAPPER-ARRAY */
Object reclaim_gsi_transfer_wrapper_array(transfer_wrapper_array)
    Object transfer_wrapper_array;
{
    x_note_fn_call(5,36);
    return VALUES_1(Nil);
}

/* RECLAIM-GSI-SENSOR-ATTRIBUTE-LIST */
Object reclaim_gsi_sensor_attribute_list(sensor_attribute_list)
    Object sensor_attribute_list;
{
    x_note_fn_call(5,37);
    return VALUES_1(Nil);
}

/* FILTER-TEXT-FOR-GSI-P */
Object filter_text_for_gsi_p()
{
    x_note_fn_call(5,38);
    return VALUES_1(Nil);
}

/* MAYBE-CALL-GSI-SHUTDOWN-CONTEXT-CALLBACK */
Object maybe_call_gsi_shutdown_context_callback(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(5,39);
    return VALUES_1(Nil);
}

/* CONVERT-VALUE-TO-GSI-VALUE */
Object convert_value_to_gsi_value(value)
    Object value;
{
    x_note_fn_call(5,40);
    return VALUES_1(Nil);
}

/* CONVERT-GSI-VALUE-TO-VALUE */
Object convert_gsi_value_to_value(value)
    Object value;
{
    x_note_fn_call(5,41);
    return VALUES_1(Nil);
}

/* RECLAIM-GSI-INSTANCE */
Object reclaim_gsi_instance(x,user_or_gsi)
    Object x, user_or_gsi;
{
    x_note_fn_call(5,42);
    return VALUES_1(Nil);
}

/* WRITE-ICP-GSI-VALUE-VECTOR */
Object write_icp_gsi_value_vector(x)
    Object x;
{
    x_note_fn_call(5,43);
    return VALUES_1(Nil);
}

/* WRITE-ICP-GSI-VALUES */
Object write_icp_gsi_values(x)
    Object x;
{
    x_note_fn_call(5,44);
    return VALUES_1(Nil);
}

/* CURRENT-GSI-STRING-CONVERSION-STYLE */
Object current_gsi_string_conversion_style()
{
    x_note_fn_call(5,45);
    return VALUES_1(Nil);
}

/* GSI-MAKE-APPROPRIATE-ARRAY */
Object gsi_make_appropriate_array varargs_1(int, n)
{
    Object gsi_type_tag, element_count;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,46);
    INIT_ARGS_nonrelocating();
    gsi_type_tag = REQUIRED_ARG_nonrelocating();
    element_count = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* GSI-PUSH-ONTO-APPROPRIATE-LIST */
Object gsi_push_onto_appropriate_list varargs_1(int, n)
{
    Object new_thing;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,47);
    INIT_ARGS_nonrelocating();
    new_thing = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* GSI-SIMPLE-CONTENT-COPY-INTERNAL */
Object gsi_simple_content_copy_internal(dst,src)
    Object dst, src;
{
    x_note_fn_call(5,48);
    return VALUES_1(Nil);
}

/* TEXT-CONVERSION-STYLE-FOR-GSI */
Object text_conversion_style_for_gsi(style_code,wide_string_p)
    Object style_code, wide_string_p;
{
    x_note_fn_call(5,49);
    return VALUES_1(Nil);
}

/* GSI-INTERN */
Object gsi_intern(string_1)
    Object string_1;
{
    x_note_fn_call(5,50);
    return VALUES_1(Nil);
}

/* GSI-MAKE-ATTRIBUTES-FOR-USER-OR-GSI */
Object gsi_make_attributes_for_user_or_gsi(count_1,user_or_gsi)
    Object count_1, user_or_gsi;
{
    x_note_fn_call(5,51);
    return VALUES_1(Nil);
}

/* MAKE-GSI-STRUCTURE */
Object make_gsi_structure(list_1)
    Object list_1;
{
    x_note_fn_call(5,52);
    return VALUES_1(Nil);
}

/* MAKE-GSI-SEQUENCE */
Object make_gsi_sequence(list_1)
    Object list_1;
{
    x_note_fn_call(5,53);
    return VALUES_1(Nil);
}

/* MAKE-GSI-HISTORY */
Object make_gsi_history varargs_1(int, n)
{
    Object gsi_instance, length_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,54);
    INIT_ARGS_nonrelocating();
    gsi_instance = REQUIRED_ARG_nonrelocating();
    length_1 = REQUIRED_ARG_nonrelocating();
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

/* ADD-VECTORS-TO-GSI-HISTORY */
Object add_vectors_to_gsi_history(length_1,history,gsi_instance_qm)
    Object length_1, history, gsi_instance_qm;
{
    x_note_fn_call(5,55);
    return VALUES_1(Nil);
}

/* GSI-GET-ITEM-OF-ATTRIBUTE-NAMED */
Object gsi_get_item_of_attribute_named(instance,symbol)
    Object instance, symbol;
{
    x_note_fn_call(5,56);
    return VALUES_1(Nil);
}

/* REGISTER-GSI-CONNECTION-CALLBACKS */
Object register_gsi_connection_callbacks(listener_socket_qm,nascent_socket)
    Object listener_socket_qm, nascent_socket;
{
    x_note_fn_call(5,57);
    return VALUES_1(Nil);
}

/* SET-GSI-ATTRIBUTE-NAME */
Object set_gsi_attribute_name(attribute,attribute_name)
    Object attribute, attribute_name;
{
    x_note_fn_call(5,58);
    return VALUES_1(Nil);
}

/* MAKE-GSI-ATTRIBUTE-FOR-USER-OR-GSI */
Object make_gsi_attribute_for_user_or_gsi(user_or_gsi)
    Object user_or_gsi;
{
    x_note_fn_call(5,59);
    return VALUES_1(Nil);
}

/* GSI-ATTRIBUTE-QUALIFIED-NAME */
Object gsi_attribute_qualified_name(gsi_attribute)
    Object gsi_attribute;
{
    x_note_fn_call(5,60);
    return VALUES_1(Nil);
}

/* GSI-MAKE-ARRAY-FOR-USER-OR-GSI */
Object gsi_make_array_for_user_or_gsi(count_1,user_or_gsi)
    Object count_1, user_or_gsi;
{
    x_note_fn_call(5,61);
    return VALUES_1(Nil);
}

/* MAKE-GSI-INSTANCE */
Object make_gsi_instance varargs_1(int, n)
{
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,62);
    INIT_ARGS_nonrelocating();
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

/* MAKE-GSI-HISTORY-FROM-SPECIFICATION */
Object make_gsi_history_from_specification(max_count_qm,max_age_qm,
	    granularity_qm)
    Object max_count_qm, max_age_qm, granularity_qm;
{
    x_note_fn_call(5,63);
    return VALUES_1(Nil);
}

/* SIGNAL-GSI-ICP-MESSAGE-TOO-LONG-ERROR */
Object signal_gsi_icp_message_too_long_error()
{
    x_note_fn_call(5,64);
    return VALUES_1(Nil);
}

/* SIGNAL-GSI-ICP-MESSAGE-OUT-OF-SYNCH-CASE-2-ERROR */
Object signal_gsi_icp_message_out_of_synch_case_2_error()
{
    x_note_fn_call(5,65);
    return VALUES_1(Nil);
}

/* SIGNAL-GSI-MAXIMUM-GENSYM-STRING-LENGTH-ERROR */
Object signal_gsi_maximum_gensym_string_length_error(length_1,maximum_length)
    Object length_1, maximum_length;
{
    x_note_fn_call(5,66);
    return VALUES_1(Nil);
}

/* SIGNAL-GSI-MAXIMUM-TEXT-STRING-LENGTH-ERROR */
Object signal_gsi_maximum_text_string_length_error(length_1,maximum_length)
    Object length_1, maximum_length;
{
    x_note_fn_call(5,67);
    return VALUES_1(Nil);
}

/* SIGNAL-GSI-EXTEND-CURRENT-GENSYM-STRING-ERROR */
Object signal_gsi_extend_current_gensym_string_error()
{
    x_note_fn_call(5,68);
    return VALUES_1(Nil);
}

/* SIGNAL-GSI-EXTEND-CURRENT-TEXT-STRING-ERROR */
Object signal_gsi_extend_current_text_string_error()
{
    x_note_fn_call(5,69);
    return VALUES_1(Nil);
}

/* SIGNAL-GSI-UNDEFINED-STRUCTURE-METHOD-ERROR */
Object signal_gsi_undefined_structure_method_error()
{
    x_note_fn_call(5,70);
    return VALUES_1(Nil);
}

/* SIGNAL-GSI-INDEX-SPACE-FULL-ERROR */
Object signal_gsi_index_space_full_error()
{
    x_note_fn_call(5,71);
    return VALUES_1(Nil);
}

/* GSI-START-OR-CALL-LOCAL-FUNCTION-OR-HANDLE-RETURN-VALUES */
Object gsi_start_or_call_local_function_or_handle_return_values(invocation_type,
	    remote_procedure_name,remote_procedure_identifier,
	    rpc_argument_list)
    Object invocation_type, remote_procedure_name, remote_procedure_identifier;
    Object rpc_argument_list;
{
    x_note_fn_call(5,72);
    return VALUES_1(Nil);
}

/* GSI-RECLAIM-CONTENTS */
Object gsi_reclaim_contents(reclaim_list_qm,user_or_gsi)
    Object reclaim_list_qm, user_or_gsi;
{
    x_note_fn_call(5,73);
    return VALUES_1(Nil);
}

/* GSI-PREPARE-FOR-RECURSIVE-DESCENT */
Object gsi_prepare_for_recursive_descent()
{
    x_note_fn_call(5,74);
    return VALUES_1(Nil);
}

/* GSI-TYPE-FROM-G2-ELEMENT-TYPE */
Object gsi_type_from_g2_element_type(g2_element_type)
    Object g2_element_type;
{
    x_note_fn_call(5,75);
    return VALUES_1(Nil);
}

/* GSI-TYPE-FROM-LEAF-TYPE */
Object gsi_type_from_leaf_type(leaf_type)
    Object leaf_type;
{
    x_note_fn_call(5,76);
    return VALUES_1(Nil);
}

/* GSI-PREFLIGHT-ITEM */
Object gsi_preflight_item(item,junk)
    Object item, junk;
{
    x_note_fn_call(5,77);
    return VALUES_1(Nil);
}

/* GSI-SEND-ITEM */
Object gsi_send_item(item,attribute_spec_qm)
    Object item, attribute_spec_qm;
{
    x_note_fn_call(5,78);
    return VALUES_1(Nil);
}

/* GSI-BUILD-ITEM-INSTANCE */
Object gsi_build_item_instance(attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index,class_name,gsi_type_tag,vector_length,
	    symbolic_attribute_count)
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, gsi_type_tag, vector_length, symbolic_attribute_count;
{
    x_note_fn_call(5,79);
    return VALUES_1(Nil);
}

/* GSI-RECEIVE-ADD-HOMOGENEOUS-HISTORY-RANGE */
Object gsi_receive_add_homogeneous_history_range(timestamps_use_floats_qm,
	    element_type,number_of_elements)
    Object timestamps_use_floats_qm, element_type, number_of_elements;
{
    x_note_fn_call(5,80);
    return VALUES_1(Nil);
}

/* GSI-ADD-RESUMABLE-CIRCULARITY */
Object gsi_add_resumable_circularity(corresponding_index)
    Object corresponding_index;
{
    x_note_fn_call(5,81);
    return VALUES_1(Nil);
}

/* GSI-RECEIVE-ADD-HISTORY-RANGE */
Object gsi_receive_add_history_range(timestamps_use_float_array_p,
	    values_use_float_array_p,number_of_elements)
    Object timestamps_use_float_array_p, values_use_float_array_p;
    Object number_of_elements;
{
    x_note_fn_call(5,82);
    return VALUES_1(Nil);
}

/* GSI-ARRAY-TYPE-FROM-G2-ELEMENT-TYPE */
Object gsi_array_type_from_g2_element_type(g2_element_type)
    Object g2_element_type;
{
    x_note_fn_call(5,83);
    return VALUES_1(Nil);
}

/* SIMPLE-TEXT-STRING-COPY-FROM-ATTRIBUTE-NAME */
Object simple_text_string_copy_from_attribute_name(base_name,
	    class_qualifier_qm)
    Object base_name, class_qualifier_qm;
{
    x_note_fn_call(5,84);
    return VALUES_1(Nil);
}

/* GSI-LIST-TYPE-FROM-G2-ELEMENT-TYPE */
Object gsi_list_type_from_g2_element_type(g2_element_type)
    Object g2_element_type;
{
    x_note_fn_call(5,85);
    return VALUES_1(Nil);
}

/* GSI-ADD-LEAF-TO-ITEM-INSTANCE */
Object gsi_add_leaf_to_item_instance(current_subobject,attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,leaf_value,
	    leaf_type)
    Object current_subobject, attribute_type, attribute_qualifier_qm;
    Object attribute_name_or_index, leaf_value, leaf_type;
{
    x_note_fn_call(5,86);
    return VALUES_1(Nil);
}

/* GSI-HANDLE-DEFINE-REMOTE-PROCEDURE-NAME */
Object gsi_handle_define_remote_procedure_name(new_remote_procedure_name)
    Object new_remote_procedure_name;
{
    x_note_fn_call(5,87);
    return VALUES_1(Nil);
}

/* GSI-OPTION-IS-SET-P */
Object gsi_option_is_set_p(option_index)
    Object option_index;
{
    x_note_fn_call(5,88);
    return VALUES_1(Nil);
}

/* GSI-DEREGISTER-ITEMS-WRAPPER-FOR-KNOWN-SENSOR */
Object gsi_deregister_items_wrapper_for_known_sensor(gsi_sensor,index_1)
    Object gsi_sensor, index_1;
{
    x_note_fn_call(5,89);
    return VALUES_1(Nil);
}

/* CALL-GSI-CALLBACK */
Object call_gsi_callback varargs_1(int, n)
{
    Object callback_index;
    Declare_varargs_nonrelocating;

    x_note_fn_call(5,90);
    INIT_ARGS_nonrelocating();
    callback_index = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* CALL-GSI-CLOSE-FD-CALLBACK */
Object call_gsi_close_fd_callback(fd)
    Object fd;
{
    x_note_fn_call(5,91);
    return VALUES_1(Nil);
}

/* CALL-GSI-OPEN-FD-CALLBACK */
Object call_gsi_open_fd_callback(fd)
    Object fd;
{
    x_note_fn_call(5,92);
    return VALUES_1(Nil);
}

/* CALL-GSI-NOT-WRITING-FD-CALLBACK */
Object call_gsi_not_writing_fd_callback(fd)
    Object fd;
{
    x_note_fn_call(5,93);
    return VALUES_1(Nil);
}

/* CALL-GSI-WRITING-FD-CALLBACK */
Object call_gsi_writing_fd_callback(fd)
    Object fd;
{
    x_note_fn_call(5,94);
    return VALUES_1(Nil);
}

/* DEFAULT-OWNER-FOR-GSI-OBJECTS */
Object default_owner_for_gsi_objects()
{
    x_note_fn_call(5,95);
    return VALUES_1(Nil);
}

/* FIND-OR-LOAD-GSI-APPLICATION */
Object find_or_load_gsi_application(name)
    Object name;
{
    x_note_fn_call(5,96);
    return VALUES_1(Nil);
}

/* GSI-CURRENT-CONTEXT-NUMBER */
Object gsi_current_context_number()
{
    x_note_fn_call(5,97);
    return VALUES_1(Nil);
}

/* TW-HANDLE-SPAWN-REMOTE-COMMAND-LINE-PROCESS */
Object tw_handle_spawn_remote_command_line_process(index_of_result_parameter,
	    command_line)
    Object index_of_result_parameter, command_line;
{
    x_note_fn_call(5,98);
    return VALUES_1(Nil);
}

/* TW-HANDLE-SPAWN-REMOTE-EXECUTABLE-PROCESS */
Object tw_handle_spawn_remote_executable_process(index_of_result_parameter,
	    command_line)
    Object index_of_result_parameter, command_line;
{
    x_note_fn_call(5,99);
    return VALUES_1(Nil);
}

/* TW-HANDLE-REMOTE-PROCESS-EXISTS-P */
Object tw_handle_remote_process_exists_p(index_of_result_parameter,process_id)
    Object index_of_result_parameter, process_id;
{
    x_note_fn_call(5,100);
    return VALUES_1(Nil);
}

/* TW-HANDLE-KILL-REMOTE-PROCESS */
Object tw_handle_kill_remote_process(index_of_result_parameter,process_id)
    Object index_of_result_parameter, process_id;
{
    x_note_fn_call(5,101);
    return VALUES_1(Nil);
}

/* RECLAIM-TELEWINDOWS-WORKSTATION-FUNCTION */
Object reclaim_telewindows_workstation_function(workstation)
    Object workstation;
{
    x_note_fn_call(5,102);
    return VALUES_1(Nil);
}

void g2_patches_INIT()
{
    x_note_fn_call(5,103);
    SET_PACKAGE("AB");
    if (Compilations_were_removed_in_this_kb_module_qm == UNBOUND)
	Compilations_were_removed_in_this_kb_module_qm = Nil;
    if (Current_telewindows_workstation == UNBOUND)
	Current_telewindows_workstation = Nil;
    if (Derived_icp_input_port == UNBOUND)
	Derived_icp_input_port = Nil;
    if (Derived_icp_output_port == UNBOUND)
	Derived_icp_output_port = Nil;
    if (Gsi_maximum_contexts_exceeded == UNBOUND)
	Gsi_maximum_contexts_exceeded = Nil;
}
