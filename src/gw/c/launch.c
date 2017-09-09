/* launch.c
 * Input file:  launch.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "launch.h"


Object G2int_system_top_level_function_prop = UNBOUND;

Object G2int_system_run_function_prop = UNBOUND;

Object G2int_system_window_title_string_prop = UNBOUND;

Object G2int_system_icon_title_string_prop = UNBOUND;

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object Qg2int_system_window_title_string;  /* system-window-title-string */

static Object Qg2int_system_icon_title_string;  /* system-icon-title-string */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

/* MAKE-NATIVE-WINDOW */
Object g2int_make_native_window varargs_1(int, n)
{
    Object system_1;
    Object geometry_qm, fullscreen_qm, name_qm, icon_name_qm;
    Object user_wants_full_screen_p, geometry_command_line_option_string;
    Object x_offset, y_offset, width, height, temp, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6, temp_7, temp_8;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(31,0);
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
	user_wants_full_screen_p = g2int_get_command_line_flag_argument(1,
		array_constant);
    geometry_command_line_option_string = geometry_qm;
    if (geometry_command_line_option_string);
    else
	geometry_command_line_option_string = 
		g2int_get_command_line_keyword_argument(1,array_constant_1);
    x_offset = FIX((SI_Long)-1L);
    y_offset = FIX((SI_Long)-1L);
    width = FIX((SI_Long)-1L);
    height = FIX((SI_Long)-1L);
    if (geometry_command_line_option_string) {
	result = g2int_get_values_from_x11_parse_geometry(geometry_command_line_option_string);
	MVS_4(result,x_offset,y_offset,width,height);
    }
    g2int_clear_fixnum_time_alarm();
    temp = g2int_get_default_x11_display();
    temp_1 = name_qm;
    if (temp_1);
    else
	temp_1 = g2int_get_window_name_from_command_line_if_any();
    if (temp_1);
    else
	temp_1 = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(system_1),
		Qg2int_system_window_title_string);
    temp_2 = g2int_mutate_global_property(system_1,temp_1,
	    Qg2int_system_window_title_string);
    temp_3 = icon_name_qm;
    if (temp_3);
    else
	temp_3 = g2int_get_icon_name_from_command_line_if_any();
    if (temp_3);
    else
	temp_3 = g2int_get_window_name_from_command_line_if_any();
    if (temp_3);
    else
	temp_3 = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(system_1),
		Qg2int_system_icon_title_string);
    if (user_wants_full_screen_p)
	temp_4 = FIX((SI_Long)-2L);
    else {
	temp_4 = g2int_get_command_line_keyword_argument_as_integer(1,
		array_constant_2);
	if (temp_4);
	else
	    temp_4 = width;
    }
    if (user_wants_full_screen_p)
	temp_5 = FIX((SI_Long)-2L);
    else {
	temp_5 = g2int_get_command_line_keyword_argument_as_integer(1,
		array_constant_3);
	if (temp_5);
	else
	    temp_5 = height;
    }
    temp_6 = x_offset;
    temp_7 = y_offset;
    temp_8 = g2int_get_command_line_flag_argument(1,array_constant_4) ? 
	    FIX((SI_Long)0L) : FIX((SI_Long)1L);
    temp_1 = g2int_get_command_line_flag_argument(1,array_constant_5) ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L);
    return g2int_c_x11_initialize(temp,temp_2,temp_3,temp_4,temp_5,temp_6,
	    temp_7,temp_8,temp_1,g2int_get_frame_window_type(system_1));
}

static Object string_constant;     /* "0" */

static Object string_constant_1;   /* "" */

static Object Qg2int_system_alias;  /* system-alias */

static Object Qg2int_system_version;  /* system-version */

/* ANNOUNCE-SYSTEM-PRESENCE */
Object g2int_announce_system_presence(system_1)
    Object system_1;
{
    Object second_1, minute, hour, date, month, year, print_case;
    Object gensymed_symbol, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(31,1);
    format((SI_Long)2L,T,"~%");
    result = g2int_get_decoded_real_time();
    MVS_6(result,second_1,minute,hour,date,month,year);
    format((SI_Long)12L,T,"~%[~d-~a~d-~a~d ~d:~a~d:~a~d]",year,IFIX(month) 
	    < (SI_Long)10L ? string_constant : string_constant_1,month,
	    IFIX(date) < (SI_Long)10L ? string_constant : 
	    string_constant_1,date,hour,IFIX(minute) < (SI_Long)10L ? 
	    string_constant : string_constant_1,minute,IFIX(second_1) < 
	    (SI_Long)10L ? string_constant : string_constant_1,second_1);
    print_case = Kupcase;
    PUSH_SPECIAL(Print_case,print_case,0);
      gensymed_symbol = system_1;
      temp = get(gensymed_symbol,Qg2int_system_alias,_);
      if (temp);
      else
	  temp = gensymed_symbol;
      format((SI_Long)3L,T,"~%~a ",temp);
    POP_SPECIAL();
    g2int_write_system_version(get(system_1,Qg2int_system_version,_));
    format((SI_Long)3L,T," (~a)",G2int_build_identification_string);
    if (G2int_build_comment_string)
	format((SI_Long)3L,T," (~a)",G2int_build_comment_string);
    return format((SI_Long)2L,T," ~%");
}

static Object Qg2int_requested;    /* requested */

/* MAYBE-WAIT-FOR-RETURN-KEY */
Object g2int_maybe_wait_for_return_key varargs_1(int, n)
{
    Object exit_requested_by_user_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(31,2);
    INIT_ARGS_nonrelocating();
    exit_requested_by_user_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !EQ(exit_requested_by_user_qm,Qg2int_requested))
	g2ext_maybe_wait_for_return_key();
    return VALUES_1(T);
}

Object G2int_current_process_handle = UNBOUND;

Object G2int_current_system_version = UNBOUND;

static Object Qg2int_system_top_level_function;  /* system-top-level-function */

/* LAUNCH-SYSTEM-PROCESS */
Object g2int_launch_system_process(system_1)
    Object system_1;
{
    Object temp;

    x_note_fn_call(31,3);
    G2int_current_system_name = system_1;
    g2ext_initialize_g2pointers();
    g2ext_initialize_locales();
    ne_initialize_event_handling();
    temp = g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(system_1),
	    Qg2int_system_top_level_function);
    return FUNCALL_1(temp,Nil);
}

Object G2int_generic_listener_initializedqm = UNBOUND;

Object G2int_g2_stream_all_open_streams = UNBOUND;

static Object Qg2int_shutdown;     /* shutdown */

static Object Qg2int_abort_level_0;  /* abort-level-0 */

static Object string_constant_2;   /* "AB" */

static Object string_constant_3;   /* "CURRENT-PROCESS" */

static Object Qg2int_gsi;          /* gsi */

/* RUN-SYSTEM-PROCESS */
Object g2int_run_system_process(system_name,initial_native_window_qm,
	    system_specific_run_function)
    Object system_name, initial_native_window_qm, system_specific_run_function;
{
    Object shutdown_catch_tag, inner_abort_level_tag, gensymed_symbol;
    Object copy_of_g2_stream_all_open_streams, stream_qm, ab_loop_list_;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(2);
    Object result;

    x_note_fn_call(31,4);
    SAVE_STACK();
    shutdown_catch_tag = Qg2int_shutdown;
    PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,1);
      if (PUSH_CATCH(G2int_shutdown_catch_tag,3)) {
	next_loop:
	  if (PUSH_CATCH(Qg2int_abort_level_0,2)) {
	      inner_abort_level_tag = Qg2int_abort_level_0;
	      PUSH_SPECIAL(G2int_inner_abort_level_tag,inner_abort_level_tag,
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
		G2int_system_window = Nil;
		G2int_current_system_name = system_name;
		G2int_current_process_handle = make_symbol(string_constant_3);
		G2int_current_system_version = get(system_name,
			Qg2int_system_version,_);
		if ( !EQ(G2int_current_system_name,Qg2int_gsi))
		    g2int_register_all_signal_handlers_for_launch();
		G2int_within_managed_object_scope = T;
		gensymed_symbol = system_name;
		g2int_initialize_system_variables(gensymed_symbol,
			G2int_current_process_handle);
		G2int_generic_listener_initializedqm = 
			g2int_establish_g2_network_listeners();
		if (PUSH_UNWIND_PROTECT(1)) {
		    G2int_g2_stream_all_open_streams = Nil;
		    if (PUSH_UNWIND_PROTECT(0)) {
			G2int_system_window = initial_native_window_qm ? 
				g2int_make_or_revise_window_per_native_window(Nil,
				initial_native_window_qm) : Qnil;
			FUNCALL_1(system_specific_run_function,
				G2int_system_window);
		    }
		    POP_UNWIND_PROTECT(0);
		    copy_of_g2_stream_all_open_streams = 
			    g2int_copy_list_using_streams_conses_function(G2int_g2_stream_all_open_streams);
		    stream_qm = Nil;
		    ab_loop_list_ = copy_of_g2_stream_all_open_streams;
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    stream_qm = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (stream_qm)
			g2int_g2_stream_close(stream_qm);
		    goto next_loop_1;
		  end_loop:;
		    g2int_reclaim_streams_list_function(copy_of_g2_stream_all_open_streams);
		    CONTINUE_UNWINDING(0);
		}
		POP_UNWIND_PROTECT(1);
		CONTINUE_UNWINDING(1);
	      POP_SPECIAL();
	  }
	  POP_CATCH(2);
	  goto next_loop;
	end_loop_1:
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
Object g2int_shut_down_ab_process varargs_1(int, n)
{
    Object status;
    Declare_varargs_nonrelocating;

    x_note_fn_call(31,5);
    INIT_ARGS_nonrelocating();
    status = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    return g2int_shutdown_or_exit(1,status);
}

void launch_INIT()
{
    Object Qg2int_shut_down_ab_process, AB_package, list_constant;
    Object Qg2int_system_run_function;

    x_note_fn_call(31,6);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_system_top_level_function = 
	    STATIC_SYMBOL("SYSTEM-TOP-LEVEL-FUNCTION",AB_package);
    G2int_system_top_level_function_prop = Qg2int_system_top_level_function;
    Qg2int_system_run_function = STATIC_SYMBOL("SYSTEM-RUN-FUNCTION",
	    AB_package);
    G2int_system_run_function_prop = Qg2int_system_run_function;
    Qg2int_system_window_title_string = 
	    STATIC_SYMBOL("SYSTEM-WINDOW-TITLE-STRING",AB_package);
    G2int_system_window_title_string_prop = Qg2int_system_window_title_string;
    Qg2int_system_icon_title_string = 
	    STATIC_SYMBOL("SYSTEM-ICON-TITLE-STRING",AB_package);
    G2int_system_icon_title_string_prop = Qg2int_system_icon_title_string;
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
    Qg2int_system_alias = STATIC_SYMBOL("SYSTEM-ALIAS",AB_package);
    Qg2int_system_version = STATIC_SYMBOL("SYSTEM-VERSION",AB_package);
    Qg2int_requested = STATIC_SYMBOL("REQUESTED",AB_package);
    if (G2int_current_system_name == UNBOUND)
	G2int_current_system_name = Nil;
    Qg2int_shutdown = STATIC_SYMBOL("SHUTDOWN",AB_package);
    Qg2int_abort_level_0 = STATIC_SYMBOL("ABORT-LEVEL-0",AB_package);
    string_constant_2 = STATIC_STRING("AB");
    string_constant_3 = STATIC_STRING("CURRENT-PROCESS");
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    Qg2int_shut_down_ab_process = STATIC_SYMBOL("SHUT-DOWN-AB-PROCESS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_shut_down_ab_process,
	    STATIC_FUNCTION(g2int_shut_down_ab_process,NIL,TRUE,0,1));
}
