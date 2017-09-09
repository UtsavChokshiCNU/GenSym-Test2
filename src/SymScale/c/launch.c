/* launch.c
 * Input file:  launch.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "launch.h"


Object System_top_level_function_prop = UNBOUND;

Object System_run_function_prop = UNBOUND;

Object System_window_title_string_prop = UNBOUND;

Object System_icon_title_string_prop = UNBOUND;

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object Qsystem_window_title_string;  /* system-window-title-string */

static Object Qsystem_icon_title_string;  /* system-icon-title-string */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

/* MAKE-NATIVE-WINDOW */
Object make_native_window varargs_1(int, n)
{
    Object system_1;
    Object geometry_qm, fullscreen_qm, name_qm, icon_name_qm;
    Object user_wants_full_screen_p, geometry_command_line_option_string;
    Object x_offset, y_offset, width, height, temp, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6, temp_7, temp_8;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(38,0);
    INIT_ARGS_nonrelocating();
    system_1 = REQUIRED_ARG_nonrelocating();
    geometry_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    fullscreen_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    icon_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    user_wants_full_screen_p = fullscreen_qm;
    if (user_wants_full_screen_p);
    else
	user_wants_full_screen_p = get_command_line_flag_argument(1,
		array_constant);
    geometry_command_line_option_string = geometry_qm;
    if (geometry_command_line_option_string);
    else
	geometry_command_line_option_string = 
		get_command_line_keyword_argument(1,array_constant_1);
    x_offset = FIX((SI_Long)-1L);
    y_offset = FIX((SI_Long)-1L);
    width = FIX((SI_Long)-1L);
    height = FIX((SI_Long)-1L);
    if (geometry_command_line_option_string) {
	result = get_values_from_x11_parse_geometry(geometry_command_line_option_string);
	MVS_4(result,x_offset,y_offset,width,height);
    }
    clear_fixnum_time_alarm();
    temp = get_default_x11_display();
    temp_1 = name_qm;
    if (temp_1);
    else
	temp_1 = get_window_name_from_command_line_if_any();
    if (temp_1);
    else
	temp_1 = format((SI_Long)3L,Nil,"~A (multicore)",
		getfq_function_no_default(INLINE_SYMBOL_PLIST(system_1),
		Qsystem_window_title_string));
    temp_2 = mutate_global_property(system_1,temp_1,
	    Qsystem_window_title_string);
    temp_3 = icon_name_qm;
    if (temp_3);
    else
	temp_3 = get_icon_name_from_command_line_if_any();
    if (temp_3);
    else
	temp_3 = get_window_name_from_command_line_if_any();
    if (temp_3);
    else
	temp_3 = getfq_function_no_default(INLINE_SYMBOL_PLIST(system_1),
		Qsystem_icon_title_string);
    if (user_wants_full_screen_p)
	temp_4 = FIX((SI_Long)-2L);
    else {
	temp_4 = get_command_line_keyword_argument_as_integer(1,
		array_constant_2);
	if (temp_4);
	else
	    temp_4 = width;
    }
    if (user_wants_full_screen_p)
	temp_5 = FIX((SI_Long)-2L);
    else {
	temp_5 = get_command_line_keyword_argument_as_integer(1,
		array_constant_3);
	if (temp_5);
	else
	    temp_5 = height;
    }
    temp_6 = x_offset;
    temp_7 = y_offset;
    temp_8 = get_command_line_flag_argument(1,array_constant_4) ? 
	    FIX((SI_Long)0L) : FIX((SI_Long)1L);
    temp_1 = get_command_line_flag_argument(1,array_constant_5) ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L);
    return c_x11_initialize(temp,temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,
	    temp_8,temp_1,get_frame_window_type(system_1));
}

static Object string_constant;     /* "0" */

static Object string_constant_1;   /* "" */

static Object Qsystem_alias;       /* system-alias */

static Object Qsystem_version;     /* system-version */

/* ANNOUNCE-SYSTEM-PRESENCE */
Object announce_system_presence(system_1)
    Object system_1;
{
    Object second_1, minute, hour, date, month, year, print_case;
    Object gensymed_symbol, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(38,1);
    format((SI_Long)2L,T,"~%");
    result = get_decoded_real_time();
    MVS_6(result,second_1,minute,hour,date,month,year);
    format((SI_Long)12L,T,"~%[~d-~a~d-~a~d ~d:~a~d:~a~d]",year,IFIX(month) 
	    < (SI_Long)10L ? string_constant : string_constant_1,month,
	    IFIX(date) < (SI_Long)10L ? string_constant : 
	    string_constant_1,date,hour,IFIX(minute) < (SI_Long)10L ? 
	    string_constant : string_constant_1,minute,IFIX(second_1) < 
	    (SI_Long)10L ? string_constant : string_constant_1,second_1);
    print_case = Kupcase;
    PUSH_SPECIAL_WITH_SYMBOL(Print_case,Qprint_case,print_case,0);
      gensymed_symbol = system_1;
      temp = get(gensymed_symbol,Qsystem_alias,_);
      if (temp);
      else
	  temp = gensymed_symbol;
      format((SI_Long)3L,T,"~%~a ",temp);
    POP_SPECIAL();
    write_system_version(get(system_1,Qsystem_version,_));
    format((SI_Long)3L,T," (~a)",Build_identification_string);
    if (Build_comment_string)
	format((SI_Long)3L,T," (~a)",Build_comment_string);
    return format((SI_Long)2L,T," ~%");
}

static Object Qrequested;          /* requested */

/* MAYBE-WAIT-FOR-RETURN-KEY */
Object maybe_wait_for_return_key varargs_1(int, n)
{
    Object exit_requested_by_user_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(38,2);
    INIT_ARGS_nonrelocating();
    exit_requested_by_user_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !EQ(exit_requested_by_user_qm,Qrequested))
	g2ext_maybe_wait_for_return_key();
    return VALUES_1(T);
}

DEFINE_VARIABLE_WITH_SYMBOL(System_window, Qsystem_window);

DEFINE_VARIABLE_WITH_SYMBOL(Current_process_handle, Qcurrent_process_handle);

DEFINE_VARIABLE_WITH_SYMBOL(Current_system_version, Qcurrent_system_version);

DEFINE_VARIABLE_WITH_SYMBOL(Send_messages_to_logbook_p, Qsend_messages_to_logbook_p);

DEFINE_VARIABLE_WITH_SYMBOL(Send_messages_to_console_p, Qsend_messages_to_console_p);

DEFINE_VARIABLE_WITH_SYMBOL(Send_logbook_messages_to_console_p, Qsend_logbook_messages_to_console_p);

Object Debug_frame_reference_balance_qm = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Trace_system_calls_p, Qtrace_system_calls_p);

DEFINE_VARIABLE_WITH_SYMBOL(Echo_dialog_spec_p, Qecho_dialog_spec_p);

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

static Object Qsystem_is_windowless_p;  /* system-is-windowless-p */

static Object Qsystem_top_level_function;  /* system-top-level-function */

/* LAUNCH-SYSTEM-PROCESS */
Object launch_system_process(system_1)
    Object system_1;
{
    Object timeout, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(38,3);
    SAVE_STACK();
    Current_system_name = system_1;
    cache_command_line_if_necessary();
    g2ext_initialize_g2pointers();
    g2ext_initialize_locales();
    ne_initialize_event_handling();
    timeout = get_command_line_keyword_argument(1,array_constant_6);
    if (timeout)
	c_set_file_operation_timeout(timeout);
    if (get_command_line_flag_argument(1,array_constant_7))
	Send_messages_to_logbook_p = T;
    if (get_command_line_flag_argument(1,array_constant_8))
	Send_messages_to_console_p = T;
    if (get_command_line_flag_argument(1,array_constant_9))
	Send_logbook_messages_to_console_p = T;
    if (get_command_line_flag_argument(1,array_constant_10))
	Debug_frame_reference_balance_qm = T;
    if (get_command_line_flag_argument(1,array_constant_11))
	Trace_system_calls_p = FIX((SI_Long)2000L);
    if (get_command_line_flag_argument(1,array_constant_12))
	Echo_dialog_spec_p = T;
    if (get(system_1,Qsystem_is_windowless_p,_)) {
	if (PUSH_UNWIND_PROTECT(0)) {
	    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(system_1),
		    Qsystem_top_level_function);
	    SAVE_VALUES(maybe_wait_for_return_key(1,FUNCALL_1(temp,Nil)));
	}
	POP_UNWIND_PROTECT(0);
	exit_lisp_process(0);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else if (local_gensym_x11_display() || x11_display_specified_p() || 
	    no_local_window_p()) {
	x11_preinitialize_if_necessary();
	if (PUSH_UNWIND_PROTECT(0)) {
	    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(system_1),
		    Qsystem_top_level_function);
	    SAVE_VALUES(maybe_wait_for_return_key(1,FUNCALL_1(temp,
		    make_native_window(1,system_1))));
	}
	POP_UNWIND_PROTECT(0);
	exit_lisp_process(0);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	print_display_error();
	maybe_wait_for_return_key(1,Nil);
	result = exit_lisp_process(0);
	RESTORE_STACK();
	return result;
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Generic_listener_initialized_qm, Qgeneric_listener_initialized_qm);

DEFINE_VARIABLE_WITH_SYMBOL(G2_stream_all_open_streams, Qg2_stream_all_open_streams);

static Object Qshutdown;           /* shutdown */

static Object Qabort_level_0;      /* abort-level-0 */

static Object string_constant_2;   /* "AB" */

static Object string_constant_3;   /* "CURRENT-PROCESS" */

static Object Qgsi;                /* gsi */

/* RUN-SYSTEM-PROCESS */
Object run_system_process(system_name,initial_native_window_qm,
	    system_specific_run_function)
    Object system_name, initial_native_window_qm, system_specific_run_function;
{
    Object shutdown_catch_tag, inner_abort_level_tag, gensymed_symbol;
    Object gensymed_symbol_1, copy_of_g2_stream_all_open_streams, stream_qm;
    Object ab_loop_list_;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(2);
    Object result;

    x_note_fn_call(38,4);
    SAVE_STACK();
    shutdown_catch_tag = Qshutdown;
    PUSH_SPECIAL_WITH_SYMBOL(Shutdown_catch_tag,Qshutdown_catch_tag,shutdown_catch_tag,
	    1);
      if (PUSH_CATCH(Shutdown_catch_tag,3)) {
	next_loop:
	  if (PUSH_CATCH(Qabort_level_0,2)) {
	      inner_abort_level_tag = Qabort_level_0;
	      PUSH_SPECIAL_WITH_SYMBOL(Inner_abort_level_tag,Qinner_abort_level_tag,inner_abort_level_tag,
		      0);
		Package = find_package(string_constant_2);
		Read_base = FIX((SI_Long)10L);
		Read_default_float_format = Qdouble_float;
		Print_base = FIX((SI_Long)10L);
		Print_array = Nil;
		Print_case = Kupcase;
		Standard_input = Terminal_io;
		Error_output = Terminal_io;
		Debug_io = Terminal_io;
		System_window = Nil;
		Current_system_name = system_name;
		Current_process_handle = make_symbol(string_constant_3);
		Current_system_version = get(system_name,Qsystem_version,_);
		if ( !EQ(Current_system_name,Qgsi))
		    register_all_signal_handlers_for_launch();
		Within_managed_object_scope = T;
		set_up_lisp_memory_management(system_name);
		gensymed_symbol = system_name;
		initialize_system_variables(gensymed_symbol,
			Current_process_handle);
		get_node_id_for_uuid_1();
		Generic_listener_initialized_qm = 
			establish_g2_network_listeners();
		if (PUSH_UNWIND_PROTECT(1)) {
		    G2_stream_all_open_streams = Nil;
		    if (PUSH_UNWIND_PROTECT(0)) {
		      next_loop_1:
			gensymed_symbol = System_window;
			gensymed_symbol_1 = initial_native_window_qm ? 
				make_or_revise_window_per_native_window(Nil,
				initial_native_window_qm) : Qnil;
			if (CAS_SYMBOL(Qsystem_window,gensymed_symbol,
				gensymed_symbol_1))
			    goto end_1;
			goto next_loop_1;
		      end_loop:
		      end_1:
			announce_system_presence(system_name);
			report_memory_usage(system_name);
			FUNCALL_1(system_specific_run_function,System_window);
		    }
		    POP_UNWIND_PROTECT(0);
		    copy_of_g2_stream_all_open_streams = 
			    copy_list_using_streams_conses_function(G2_stream_all_open_streams);
		    stream_qm = Nil;
		    ab_loop_list_ = copy_of_g2_stream_all_open_streams;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_1;
		    stream_qm = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (stream_qm)
			g2_stream_close(stream_qm);
		    goto next_loop_2;
		  end_loop_1:;
		    reclaim_streams_list_function(copy_of_g2_stream_all_open_streams);
		    CONTINUE_UNWINDING(0);
		}
		POP_UNWIND_PROTECT(1);
		shutdown_system_for_exit();
		CONTINUE_UNWINDING(1);
	      POP_SPECIAL();
	  }
	  POP_CATCH(2);
	  goto next_loop;
	end_loop_2:
	  result = VALUES_1(Qnil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(3);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* SHUT-DOWN-AB-PROCESS */
Object shut_down_ab_process varargs_1(int, n)
{
    Object status;
    Declare_varargs_nonrelocating;

    x_note_fn_call(38,5);
    INIT_ARGS_nonrelocating();
    status = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    close_log_file();
    release_all_kb_write_locks();
    return shutdown_or_exit(1,status);
}

void launch_INIT()
{
    Object Qshut_down_ab_process, AB_package, list_constant;
    Object Qsystem_run_function;

    x_note_fn_call(38,6);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsystem_top_level_function = STATIC_SYMBOL("SYSTEM-TOP-LEVEL-FUNCTION",
	    AB_package);
    System_top_level_function_prop = Qsystem_top_level_function;
    Qsystem_run_function = STATIC_SYMBOL("SYSTEM-RUN-FUNCTION",AB_package);
    System_run_function_prop = Qsystem_run_function;
    Qsystem_window_title_string = 
	    STATIC_SYMBOL("SYSTEM-WINDOW-TITLE-STRING",AB_package);
    System_window_title_string_prop = Qsystem_window_title_string;
    Qsystem_icon_title_string = STATIC_SYMBOL("SYSTEM-ICON-TITLE-STRING",
	    AB_package);
    System_icon_title_string_prop = Qsystem_icon_title_string;
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant,(SI_Long)1L,FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)57344L);
    string_constant = STATIC_STRING("0");
    string_constant_1 = STATIC_STRING("");
    Qsystem_alias = STATIC_SYMBOL("SYSTEM-ALIAS",AB_package);
    Qsystem_version = STATIC_SYMBOL("SYSTEM-VERSION",AB_package);
    Qrequested = STATIC_SYMBOL("REQUESTED",AB_package);
    if (Current_system_name == UNBOUND)
	Current_system_name = Nil;
    array_constant_6 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)27L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)57344L);
    Qsystem_is_windowless_p = STATIC_SYMBOL("SYSTEM-IS-WINDOWLESS-P",
	    AB_package);
    Qshutdown = STATIC_SYMBOL("SHUTDOWN",AB_package);
    Qabort_level_0 = STATIC_SYMBOL("ABORT-LEVEL-0",AB_package);
    string_constant_2 = STATIC_STRING("AB");
    string_constant_3 = STATIC_STRING("CURRENT-PROCESS");
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    Qsystem_window = STATIC_SYMBOL("SYSTEM-WINDOW",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsystem_window,System_window);
    Qshut_down_ab_process = STATIC_SYMBOL("SHUT-DOWN-AB-PROCESS",AB_package);
    SET_SYMBOL_FUNCTION(Qshut_down_ab_process,
	    STATIC_FUNCTION(shut_down_ab_process,NIL,TRUE,0,1));
}
