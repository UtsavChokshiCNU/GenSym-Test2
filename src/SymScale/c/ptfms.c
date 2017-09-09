/* ptfms.c
 * Input file:  platforms.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "ptfms.h"


DEFINE_VARIABLE_WITH_SYMBOL(Service_workstations, Qservice_workstations);

Object Workstations_in_service = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Last_workstation_serviced, Qlast_workstation_serviced);

Object Last_session_id_for_g2 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Standard_gensym_color_alist, Qstandard_gensym_color_alist);

/* RGB2GRAY */
Object rgb2gray(r,g,b)
    Object r, g, b;
{
    Object temp;

    x_note_fn_call(37,0);
    temp = l_round(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(r) * 0.299 + 
	    (double)IFIX(g) * 0.587 + (double)IFIX(b) * 0.114),_);
    return VALUES_1(temp);
}

Object Gray_gensym_color_alist = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Color_hierarchy, Qcolor_hierarchy);

Object Standard_gensym_color_subset = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Native_window_notices_enter_and_leave_events_p, Qnative_window_notices_enter_and_leave_events_p);

static Object array_constant;      /* # */

/* X11-DISPLAY-SPECIFIED-P */
Object x11_display_specified_p()
{
    x_note_fn_call(37,1);
    return VALUES_1(windows_platform_p() || 
	    get_command_line_keyword_argument(1,array_constant) ? T : Nil);
}

Object No_local_window_p_cached = UNBOUND;

Object No_local_window_p = UNBOUND;

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

/* NO-LOCAL-WINDOW-P */
Object no_local_window_p()
{
    Object temp;

    x_note_fn_call(37,2);
    if (No_local_window_p_cached)
	temp = No_local_window_p;
    else {
	temp = get_command_line_flag_argument(1,array_constant_1);
	if (temp);
	else
	    temp = get_command_line_flag_argument(1,array_constant_2);
	No_local_window_p = temp;
	temp = No_local_window_p;
	No_local_window_p_cached = T;
    }
    return VALUES_1(temp);
}

Object Maximum_x11_cut_buffer_length = UNBOUND;

static Object Qx_cut_buffer;       /* x-cut-buffer */

/* READ-X-WINDOW-CUT-BUFFER */
Object read_x_window_cut_buffer(gensym_x_window)
    Object gensym_x_window;
{
    Object cut_buffer_string, length_1, temp;

    x_note_fn_call(37,3);
    cut_buffer_string = 
	    obtain_simple_gensym_string(Maximum_x11_cut_buffer_length);
    length_1 = c_x11_read_cut_buffer(gensym_x_window,cut_buffer_string,
	    FIXNUM_SUB1(Maximum_x11_cut_buffer_length));
    temp = IFIX(length_1) > (SI_Long)0L ? import_text_string(4,
	    cut_buffer_string,Qx_cut_buffer,FIX((SI_Long)0L),length_1) : 
	    obtain_text_string(FIX((SI_Long)0L));
    reclaim_gensym_string(cut_buffer_string);
    return VALUES_1(temp);
}

/* C-X11-READ-CUT-BUFFER */
Object c_x11_read_cut_buffer(gensym_x_window,string_1,max_size)
    Object gensym_x_window, string_1, max_size;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,4);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(string_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = string_1;
    temp = FIX(g2ext_x11_read_cut_buffer(IFIX(gensym_x_window),
	    ISTRING(temp),IFIX(max_size)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* WRITE-X-WINDOW-CUT-BUFFER */
Object write_x_window_cut_buffer(gensym_x_window,text_string)
    Object gensym_x_window, text_string;
{
    Object string_1;

    x_note_fn_call(37,5);
    string_1 = export_text_string(2,text_string,Qx_cut_buffer);
    c_x11_write_cut_buffer(gensym_x_window,string_1,length(string_1));
    return reclaim_gensym_string(string_1);
}

/* C-X11-WRITE-CUT-BUFFER */
Object c_x11_write_cut_buffer(gensym_x_window,string_1,length_1)
    Object gensym_x_window, string_1, length_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,6);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(string_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = string_1;
    temp = FIX(g2ext_x11_write_cut_buffer(IFIX(gensym_x_window),
	    ISTRING(temp),IFIX(length_1)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

static Object Qx_string;           /* x-string */

static Object Qcf_text;            /* cf-text */

static Object Qx_compound_text_string;  /* x-compound-text-string */

static Object Qunicode;            /* unicode */

static Object Qcf_unicode_text;    /* cf-unicode-text */

/* WRITE-CLIPBOARD */
Object write_clipboard(gensym_x_window,text_string)
    Object gensym_x_window, text_string;
{
    Object latin_1_string, latin_1_string_length, x_compound_text_string;
    Object x_compound_text_string_length, unicode_text_string, temp;
    SI_Long x_targets_p, length_1, unicode_text_string_length;

    x_note_fn_call(37,7);
    x_targets_p = g2ext_x11_clipboard_x_targets_p(IFIX(gensym_x_window));
    latin_1_string = export_text_string(2,text_string,FIX(x_targets_p) ? 
	    Qx_string : Qcf_text);
    latin_1_string_length = gensym_string_length(latin_1_string);
    x_compound_text_string = FIX(x_targets_p) ? export_text_string(2,
	    text_string,Qx_compound_text_string) : (SI_Long)0L > 
	    IFIX(Maximum_suggested_length_for_simple_gensym_strings) ? 
	    obtain_long_enough_adjustable_gensym_string(FIX((SI_Long)0L)) :
	     obtain_simple_gensym_string(FIX((SI_Long)0L));
    x_compound_text_string_length = 
	    gensym_string_length(x_compound_text_string);
    unicode_text_string = export_text_string(2,text_string,
	    FIX(x_targets_p) ? Qunicode : Qcf_unicode_text);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(unicode_text_string));
    unicode_text_string_length = UBYTE_16_ISAREF_1(unicode_text_string,
	    length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(unicode_text_string,length_1 - 
	    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    temp = c_write_clipboard(gensym_x_window,latin_1_string,
	    latin_1_string_length,x_compound_text_string,
	    x_compound_text_string_length,unicode_text_string,
	    FIX(unicode_text_string_length));
    reclaim_gensym_string(latin_1_string);
    reclaim_gensym_string(x_compound_text_string);
    reclaim_wide_string(unicode_text_string);
    return VALUES_1(temp);
}

/* C-WRITE-CLIPBOARD */
Object c_write_clipboard(gensym_x_window,latin_1_string,
	    latin_1_string_length,x_compound_text_string,
	    x_compound_text_string_length,unicode_text_string,
	    unicode_text_string_length)
    Object gensym_x_window, latin_1_string, latin_1_string_length;
    Object x_compound_text_string, x_compound_text_string_length;
    Object unicode_text_string, unicode_text_string_length;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(37,8);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(latin_1_string);
    gensymed_symbol_1 = 
	    copy_foreign_string_arg_if_appropriate(x_compound_text_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = latin_1_string;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = x_compound_text_string;
    temp = FIX(g2ext_write_clipboards(IFIX(gensym_x_window),temp_1,
	    IFIX(latin_1_string_length),ISTRING(temp),
	    IFIX(x_compound_text_string_length),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(unicode_text_string),
	    IFIX(unicode_text_string_length)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

static Object Qiso_8859_1_gensym_string;  /* iso-8859-1-gensym-string */

static Object array_constant_3;    /* # */

/* READ-CLIPBOARD */
Object read_clipboard(gensym_x_window)
    Object gensym_x_window;
{
    Object latin_1_string, x_compound_text_string, unicode_text_string;
    Object wide_string_bv16, clipboard_reading_results_vector, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, latin_1_result;
    SI_Long x_compound_text_result, unicode_text_result;

    x_note_fn_call(37,9);
    latin_1_string = 
	    obtain_simple_gensym_string(Allocated_clipboard_text_length);
    x_compound_text_string = 
	    obtain_simple_gensym_string(Allocated_clipboard_text_length);
    unicode_text_string = obtain_text_string(Allocated_clipboard_text_length);
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Clipboard_reading_results_vector_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Clipboard_reading_results_vector_length) & 
	    (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,
	    IFIX(Clipboard_reading_results_vector_length),(SI_Long)0L);
    clipboard_reading_results_vector = wide_string_bv16;
    c_read_clipboard(gensym_x_window,latin_1_string,
	    Specified_max_clipboard_text_length,FIX((SI_Long)1L),
	    x_compound_text_string,Specified_max_clipboard_text_length,
	    FIX((SI_Long)1L),unicode_text_string,
	    Specified_max_clipboard_text_length,FIX((SI_Long)1L),
	    clipboard_reading_results_vector);
    latin_1_result = UBYTE_16_ISAREF_1(clipboard_reading_results_vector,
	    IFIX(Latin_1_clipboard_read_results_entry));
    x_compound_text_result = 
	    UBYTE_16_ISAREF_1(clipboard_reading_results_vector,
	    IFIX(X_compound_text_clipboard_read_results_entry));
    unicode_text_result = 
	    UBYTE_16_ISAREF_1(clipboard_reading_results_vector,
	    IFIX(Unicode_text_clipboard_read_results_entry));
    if (unicode_text_result != IFIX(Clipboard_read_results_failure_code))
	temp = import_text_string(4,unicode_text_string,Qunicode,
		FIX((SI_Long)0L),FIX(unicode_text_result));
    else if (x_compound_text_result != 
	    IFIX(Clipboard_read_results_failure_code))
	temp = import_text_string(4,x_compound_text_string,
		Qx_compound_text_string,FIX((SI_Long)0L),
		FIX(x_compound_text_result));
    else if (latin_1_result != IFIX(Clipboard_read_results_failure_code))
	temp = import_text_string(4,latin_1_string,
		Qiso_8859_1_gensym_string,FIX((SI_Long)0L),
		FIX(latin_1_result));
    else
	temp = copy_constant_wide_string_given_length(array_constant_3,
		FIX((SI_Long)0L));
    reclaim_wide_string(clipboard_reading_results_vector);
    reclaim_gensym_string(latin_1_string);
    reclaim_gensym_string(x_compound_text_string);
    reclaim_text_string(unicode_text_string);
    return VALUES_1(temp);
}

/* C-READ-CLIPBOARD */
Object c_read_clipboard(gensym_x_window,latin_1_string,
	    latin_1_string_max_length,latin_1_string_desired_p,
	    x_compound_text_string,x_compound_text_string_max_length,
	    x_compound_text_string_desired_p,unicode_text_string,
	    unicode_text_string_max_length,unicode_text_string_desired_p,
	    result_vector)
    Object gensym_x_window, latin_1_string, latin_1_string_max_length;
    Object latin_1_string_desired_p, x_compound_text_string;
    Object x_compound_text_string_max_length, x_compound_text_string_desired_p;
    Object unicode_text_string, unicode_text_string_max_length;
    Object unicode_text_string_desired_p, result_vector;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(37,10);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(latin_1_string);
    gensymed_symbol_1 = 
	    copy_foreign_string_arg_if_appropriate(x_compound_text_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = latin_1_string;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = x_compound_text_string;
    temp = FIX(g2ext_read_clipboards(IFIX(gensym_x_window),temp_1,
	    IFIX(latin_1_string_max_length),IFIX(latin_1_string_desired_p),
	    ISTRING(temp),IFIX(x_compound_text_string_max_length),
	    IFIX(x_compound_text_string_desired_p),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(unicode_text_string),
	    IFIX(unicode_text_string_max_length),
	    IFIX(unicode_text_string_desired_p),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(result_vector)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* FILE-DESCRIPTOR-FOR-NATIVE-WINDOW */
Object file_descriptor_for_native_window(gensym_x_window)
    Object gensym_x_window;
{
    x_note_fn_call(37,11);
    return VALUES_1(FIX(g2ext_x11_file_descriptor_for_window(IFIX(gensym_x_window))));
}

DEFINE_VARIABLE_WITH_SYMBOL(X11_preinitialized_p, Qx11_preinitialized_p);

/* PRINT-DISPLAY-ERROR */
Object print_display_error()
{
    x_note_fn_call(37,12);
    format((SI_Long)2L,T,
	    "~&The X11 window display has not been specified in either");
    format((SI_Long)2L,T,
	    "~%the command line or the environment variable DISPLAY.");
    format((SI_Long)2L,T,"~%Aborting ");
    format((SI_Long)2L,T,"G2 ");
    return format((SI_Long)2L,T,"startup.~%");
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_local_gensym_x11_display, Qcached_local_gensym_x11_display);

static Object string_constant;     /* "DISPLAY" */

/* LOCAL-GENSYM-X11-DISPLAY */
Object local_gensym_x11_display()
{
    Object temp;

    x_note_fn_call(37,13);
    temp = Cached_local_gensym_x11_display;
    if (temp)
	return VALUES_1(temp);
    else {
	Cached_local_gensym_x11_display = 
		get_gensym_environment_variable(string_constant);
	return VALUES_1(Cached_local_gensym_x11_display);
    }
}

static Object string_constant_1;   /* ":0" */

/* GET-DEFAULT-X11-DISPLAY */
Object get_default_x11_display()
{
    Object temp, x11_display_qm;

    x_note_fn_call(37,14);
    if (X11_preinitialized_p && IFIX(X11_preinitialized_p) == (SI_Long)1L 
	    || windows_platform_p())
	temp = string_constant_1;
    else {
	x11_display_qm = get_command_line_keyword_argument(1,array_constant);
	temp = x11_display_qm;
	if (temp);
	else
	    temp = local_gensym_x11_display();
	if (temp);
	else {
	    print_display_error();
	    temp = exit_lisp_process(0);
	}
    }
    return VALUES_1(temp);
}

static Object array_constant_4;    /* # */

/* GET-WINDOW-NAME-FROM-COMMAND-LINE-IF-ANY */
Object get_window_name_from_command_line_if_any()
{
    x_note_fn_call(37,15);
    return get_command_line_keyword_argument(3,array_constant_4,
	    FIX((SI_Long)1L),T);
}

static Object array_constant_5;    /* # */

/* GET-ICON-NAME-FROM-COMMAND-LINE-IF-ANY */
Object get_icon_name_from_command_line_if_any()
{
    x_note_fn_call(37,16);
    return get_command_line_keyword_argument(3,array_constant_5,
	    FIX((SI_Long)1L),T);
}

static Object Qx;                  /* x */

static Object Qy;                  /* y */

/* GET-DEFAULT-X-AND-Y-SCALE-FROM-COMMAND-LINE-IF-ANY */
Object get_default_x_and_y_scale_from_command_line_if_any varargs_1(int, n)
{
    Object silent_qm, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(37,17);
    INIT_ARGS_nonrelocating();
    silent_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = get_default_scale_from_command_line_1(Qx,silent_qm);
    temp_1 = get_default_scale_from_command_line_1(Qy,silent_qm);
    return VALUES_2(temp,temp_1);
}

static Object list_constant;       /* # */

static Object string_constant_2;   /* "res" */

/* GET-DEFAULT-SCALE-FROM-COMMAND-LINE-1 */
Object get_default_scale_from_command_line_1(goal_dimension,silent_qm)
    Object goal_dimension, silent_qm;
{
    Object command_string, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(37,18);
    command_string = Nil;
    ab_loop_list_ = getf(list_constant,goal_dimension,_);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    command_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = search(2,string_constant_2,command_string) ? 
	    process_command_line_resolution_arg(2,command_string,
	    silent_qm) : process_command_line_scale_arg(2,command_string,
	    silent_qm);
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_3;   /* "(none)" */

static Object string_constant_4;   /* "~%Illegal ~a arg: ~a; it must be an integer ~
				    *                          between ~a and ~a (expressing dots per inch).~%"
				    */

/* PROCESS-COMMAND-LINE-RESOLUTION-ARG */
Object process_command_line_resolution_arg varargs_1(int, n)
{
    Object name;
    Object silent_qm, resolution_spec_qm, resolution_in_dpi_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(37,19);
    INIT_ARGS_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    silent_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    resolution_spec_qm = get_command_line_keyword_argument(1,name);
    resolution_in_dpi_qm = resolution_spec_qm ? read_fixnum_from_string(3,
	    resolution_spec_qm,FIX((SI_Long)0L),
	    lengthw(resolution_spec_qm)) : Nil;
    temp = resolution_in_dpi_qm ? (num_len(3,
	    Gensym_windows_minimum_supported_dpi,resolution_in_dpi_qm,
	    Gensym_windows_maximum_supported_dpi) ? 
	    scale_scale(FIX((SI_Long)4096L),resolution_in_dpi_qm,
	    Gensym_windows_standard_dpi) : Nil) : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (resolution_spec_qm) {
	if ( !TRUEP(silent_qm)) {
	    temp = resolution_spec_qm;
	    if (temp);
	    else
		temp = string_constant_3;
	    return notify_user_at_console(5,string_constant_4,name,temp,
		    Gensym_windows_minimum_supported_dpi,
		    Gensym_windows_maximum_supported_dpi);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_5;   /* "~%Illegal ~a arg: ~a; it must be a number ~
				    *                          between ~f and ~f (expressing a magnification factor).~%"
				    */

/* PROCESS-COMMAND-LINE-SCALE-ARG */
Object process_command_line_scale_arg varargs_1(int, n)
{
    Object name;
    Object silent_qm, scale_spec_qm, scale_qm, scale_as_number, temp;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(37,20);
    INIT_ARGS_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    silent_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	scale_spec_qm = get_command_line_keyword_argument(1,name);
	scale_qm = scale_spec_qm ? read_number_from_string(scale_spec_qm,
		FIX((SI_Long)0L),lengthw(scale_spec_qm)) : Nil;
	if (scale_qm) {
	    scale_as_number = INLINE_DOUBLE_FLOAT_VECTOR_P(scale_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(scale_qm)) == 
		    (SI_Long)1L ? 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(scale_qm,
		    (SI_Long)0L)) : scale_qm;
	    temp = num_len(3,Gensym_windows_minimum_supported_scale,
		    scale_as_number,
		    Gensym_windows_maximum_supported_scale) ? 
		    l_round(ltimes(FIX((SI_Long)4096L),scale_as_number),_) 
		    : Nil;
	}
	else
	    temp = Nil;
	if (temp)
	    result = VALUES_1(temp);
	else if (scale_spec_qm) {
	    if ( !TRUEP(silent_qm)) {
		temp = scale_spec_qm;
		if (temp);
		else
		    temp = string_constant_3;
		result = notify_user_at_console(5,string_constant_5,name,
			temp,Gensym_windows_minimum_supported_scale,
			Gensym_windows_maximum_supported_scale);
	    }
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* C-X11-PREINITIALIZE */
Object c_x11_preinitialize(run_without_local_window_p,windowhandle)
    Object run_without_local_window_p, windowhandle;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,21);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(windowhandle);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = windowhandle;
    g2ext_x11_preinitialize(IFIX(run_without_local_window_p),ISTRING(temp));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* X11-PREINITIALIZE-IF-NECESSARY */
Object x11_preinitialize_if_necessary()
{
    SI_Long preinitialization_option;

    x_note_fn_call(37,22);
    if ( !TRUEP(X11_preinitialized_p)) {
	preinitialization_option = no_local_window_p() ? (SI_Long)1L : 
		(SI_Long)0L;
	c_x11_preinitialize(FIX(preinitialization_option),
		get_parent_windowhandle());
	X11_preinitialized_p = FIX(preinitialization_option);
	return VALUES_1(X11_preinitialized_p);
    }
    else
	return VALUES_1(Nil);
}

/* C-X11-INITIALIZE */
Object c_x11_initialize(display_spec,window_name,icon_name,window_width_1,
	    window_height_1,x_offset,y_offset,backing_store_p,
	    private_colormap_p,frame_type)
    Object display_spec, window_name, icon_name, window_width_1;
    Object window_height_1, x_offset, y_offset, backing_store_p;
    Object private_colormap_p, frame_type;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(37,23);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(display_spec);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(window_name);
    gensymed_symbol_2 = copy_foreign_string_arg_if_appropriate(icon_name);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = display_spec;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = window_name;
    temp_2 = ISTRING(temp);
    temp = gensymed_symbol_2;
    if (temp);
    else
	temp = icon_name;
    temp = LONG_TO_FIXNUM(g2ext_x11_initialize(temp_1,temp_2,ISTRING(temp),
	    IFIX(window_width_1),IFIX(window_height_1),IFIX(x_offset),
	    IFIX(y_offset),IFIX(backing_store_p),IFIX(private_colormap_p),
	    IFIX(frame_type)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(temp);
}

/* C-X11-GET-PIXEL-VALUE */
Object c_x11_get_pixel_value(gensym_x_window,gensym_color_string,
	    extended_color_p)
    Object gensym_x_window, gensym_color_string, extended_color_p;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,24);
    gensymed_symbol = 
	    copy_foreign_string_arg_if_appropriate(gensym_color_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = gensym_color_string;
    temp = FIX(g2ext_get_pixel(IFIX(gensym_x_window),ISTRING(temp),
	    IFIX(extended_color_p)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* GET-PIXEL-VALUE */
Object get_pixel_value(native_window,string_1,extended_color_p)
    Object native_window, string_1, extended_color_p;
{
    Object raw_pixel_value;

    x_note_fn_call(37,25);
    raw_pixel_value = c_x11_get_pixel_value(native_window,string_1,
	    extended_color_p ? FIX((SI_Long)1L) : FIX((SI_Long)0L));
    if (IFIX(raw_pixel_value) >= (SI_Long)0L)
	return VALUES_1(raw_pixel_value);
    else
	return VALUES_1(Nil);
}

/* C-X11-LAST-EVENT-VALUE */
Object c_x11_last_event_value(gensym_x_window,buffer,buffer_size)
    Object gensym_x_window, buffer, buffer_size;
{
    Object temp;

    x_note_fn_call(37,26);
    temp = FIX(g2ext_x11_last_event_value(IFIX(gensym_x_window),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(buffer),IFIX(buffer_size)));
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_error_in_x11_create_pixmap_on_failed_allocation, Qdo_not_error_in_x11_create_pixmap_on_failed_allocation);

/* HANDLE-NO-SOLUTION-TO-RASTER-ALLOCATION-FAILURE */
Object handle_no_solution_to_raster_allocation_failure(gensym_window,width,
	    height)
    Object gensym_window, width, height;
{
    x_note_fn_call(37,27);
    return error((SI_Long)3L,"Unable to allocate a ~dx~d pixmap!",width,
	    height);
}

Object Maximum_polygon_coordinates = UNBOUND;

/* C-X11-PFILL-CLIPPED-POLYGON */
Object c_x11_pfill_clipped_polygon(pixmap_structure_pointer,point_data,
	    number_points,left,top,right,bottom,xcolor)
    Object pixmap_structure_pointer, point_data, number_points, left, top;
    Object right, bottom, xcolor;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,28);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(point_data);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = point_data;
    g2ext_p_fill_clipped_polygon(IFIX(pixmap_structure_pointer),
	    ISTRING(temp),IFIX(number_points),IFIX(left),IFIX(top),
	    IFIX(right),IFIX(bottom),IFIX(xcolor));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* C-X11-DRAW-STRING */
Object c_x11_draw_string(window,left,top,right,bottom,x,y,color,point_size,
	    angle,flags,x_scale,y_scale,word_spacing,string_1,length_1)
    Object window, left, top, right, bottom, x, y, color, point_size, angle;
    Object flags, x_scale, y_scale, word_spacing, string_1, length_1;
{
    x_note_fn_call(37,29);
    g2ext_w_draw_string(IFIX(window),IFIX(left),IFIX(top),IFIX(right),
	    IFIX(bottom),IFIX(x),IFIX(y),IFIX(color),IFIX(point_size),
	    IFIX(angle),IFIX(flags),IFIX(x_scale),IFIX(y_scale),
	    IFIX(word_spacing),UBYTE_16_SARRAY_TO_USHORT_PTR(string_1),
	    IFIX(length_1));
    return VALUES_1(Nil);
}

/* C-X11-DRAW-STRING-WITH-CLIPPING */
Object c_x11_draw_string_with_clipping(gensym_x_window,x,y,left_edge,
	    top_edge,right_edge,bottom_edge,xcolor,function_index,
	    font_name,ascii_text,length_1)
    Object gensym_x_window, x, y, left_edge, top_edge, right_edge, bottom_edge;
    Object xcolor, function_index, font_name, ascii_text, length_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(37,30);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(font_name);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(ascii_text);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = font_name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = ascii_text;
    temp = FIX(g2ext_w_draw_string_with_clipping(IFIX(gensym_x_window),
	    IFIX(x),IFIX(y),IFIX(left_edge),IFIX(top_edge),
	    IFIX(right_edge),IFIX(bottom_edge),IFIX(xcolor),
	    IFIX(function_index),temp_1,ISTRING(temp),IFIX(length_1)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* C-X11-DRAW-STRING-IN-FONT */
Object c_x11_draw_string_in_font(gensym_x_window,x,y,xcolor,function_index,
	    font,ascii_text,length_1)
    Object gensym_x_window, x, y, xcolor, function_index, font, ascii_text;
    Object length_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,31);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(ascii_text);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = ascii_text;
    temp = FIX(g2ext_draw_string_in_font(IFIX(gensym_x_window),IFIX(x),
	    IFIX(y),IFIX(xcolor),IFIX(function_index),IFIX(font),
	    ISTRING(temp),IFIX(length_1)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-X11-DRAW-STRING-IN-FONT-WITH-CLIPPING */
Object c_x11_draw_string_in_font_with_clipping(gensym_x_window,x,y,
	    left_edge,top_edge,right_edge,bottom_edge,xcolor,
	    function_index,font,ascii_text,length_1)
    Object gensym_x_window, x, y, left_edge, top_edge, right_edge, bottom_edge;
    Object xcolor, function_index, font, ascii_text, length_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,32);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(ascii_text);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = ascii_text;
    temp = 
	    FIX(g2ext_draw_string_in_font_with_clipping(IFIX(gensym_x_window),
	    IFIX(x),IFIX(y),IFIX(left_edge),IFIX(top_edge),
	    IFIX(right_edge),IFIX(bottom_edge),IFIX(xcolor),
	    IFIX(function_index),IFIX(font),ISTRING(temp),IFIX(length_1)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-X11-ALLOCATE-X-FONT */
Object c_x11_allocate_x_font(gensym_x_window,font_name)
    Object gensym_x_window, font_name;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,33);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(font_name);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = font_name;
    temp = LONG_TO_FIXNUM(g2ext_allocate_x_font(IFIX(gensym_x_window),
	    ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-X11-DRAW-WIDE-POLYLINE */
Object c_x11_draw_wide_polyline(gensym_x_window,points,npoints,left_edge,
	    top_edge,right_edge,bottom_edge,color,width,style,dashes,
	    ndashes,function_index)
    Object gensym_x_window, points, npoints, left_edge, top_edge, right_edge;
    Object bottom_edge, color, width, style, dashes, ndashes, function_index;
{
    x_note_fn_call(37,34);
    g2ext_w_draw_wide_polyline(IFIX(gensym_x_window),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(points),IFIX(npoints),
	    IFIX(left_edge),IFIX(top_edge),IFIX(right_edge),
	    IFIX(bottom_edge),IFIX(color),IFIX(width),IFIX(style),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(dashes),IFIX(ndashes),
	    IFIX(function_index));
    return VALUES_1(Nil);
}

/* C-X11-DRAW-POLYGON */
Object c_x11_draw_polygon(gensym_x_window,left_edge,top_edge,right_edge,
	    bottom_edge,line_color,line_width,fill_color,fill_pattern,
	    function_index,points,npoints)
    Object gensym_x_window, left_edge, top_edge, right_edge, bottom_edge;
    Object line_color, line_width, fill_color, fill_pattern, function_index;
    Object points, npoints;
{
    x_note_fn_call(37,35);
    g2ext_w_draw_polygon(IFIX(gensym_x_window),IFIX(left_edge),
	    IFIX(top_edge),IFIX(right_edge),IFIX(bottom_edge),
	    IFIX(line_color),IFIX(line_width),IFIX(fill_color),
	    IFIX(fill_pattern),IFIX(function_index),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(points),IFIX(npoints));
    return VALUES_1(Nil);
}

/* GET-VALUES-FROM-X11-PARSE-GEOMETRY */
Object get_values_from_x11_parse_geometry(parsestring)
    Object parsestring;
{
    Object temp, temp_1, temp_2, temp_3;

    x_note_fn_call(37,36);
    c_x11_parse_geometry(parsestring);
    temp = FIX(g2ext_x11_parse_geometry_x());
    temp_1 = FIX(g2ext_x11_parse_geometry_y());
    temp_2 = FIX(g2ext_x11_parse_geometry_width());
    temp_3 = FIX(g2ext_x11_parse_geometry_height());
    return VALUES_4(temp,temp_1,temp_2,temp_3);
}

/* C-X11-PARSE-GEOMETRY */
Object c_x11_parse_geometry(parsestring)
    Object parsestring;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,37);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(parsestring);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = parsestring;
    g2ext_x11_parse_geometry(ISTRING(temp));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* MAKE-BLOCK-NEAR-MOUSE-CACHE */
Object make_block_near_mouse_cache()
{
    x_note_fn_call(37,38);
    return make_block_near_mouse_cache_internal_1();
}

/* RECLAIM-BLOCK-NEAR-MOUSE-CACHE-FUNCTION */
Object reclaim_block_near_mouse_cache_function(cache)
    Object cache;
{
    x_note_fn_call(37,39);
    reclaim_block_near_mouse_cache_1(cache);
    return VALUES_1(Nil);
}

Object The_type_description_of_workstation = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_workstations, Qchain_of_available_workstations);

DEFINE_VARIABLE_WITH_SYMBOL(Workstation_count, Qworkstation_count);

Object Chain_of_available_workstations_vector = UNBOUND;

/* WORKSTATION-STRUCTURE-MEMORY-USAGE */
Object workstation_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(37,40);
    temp = Workstation_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)56L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-WORKSTATION-COUNT */
Object outstanding_workstation_count()
{
    Object def_structure_workstation_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(37,41);
    gensymed_symbol = IFIX(Workstation_count);
    def_structure_workstation_variable = Chain_of_available_workstations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_workstation_variable))
	goto end_loop;
    def_structure_workstation_variable = 
	    ISVREF(def_structure_workstation_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-WORKSTATION-INTERNAL-1 */
Object reclaim_workstation_internal_1(workstation)
    Object workstation;
{
    Object structure_being_reclaimed, thing, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(37,42);
    inline_note_reclaim_cons(workstation,Nil);
    structure_being_reclaimed = workstation;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_window_for_workstation(ISVREF(workstation,(SI_Long)1L));
      SVREF(workstation,FIX((SI_Long)1L)) = Nil;
      reclaim_workstation_event_queue_if_g2(ISVREF(workstation,(SI_Long)2L));
      SVREF(workstation,FIX((SI_Long)2L)) = Nil;
      reclaim_mouse_pointers_if_g2(ISVREF(workstation,(SI_Long)14L));
      SVREF(workstation,FIX((SI_Long)14L)) = Nil;
      reclaim_mouse_pointers_if_g2(ISVREF(workstation,(SI_Long)15L));
      SVREF(workstation,FIX((SI_Long)15L)) = Nil;
      reclaim_workstation_context_stack_if_g2(ISVREF(workstation,
	      (SI_Long)17L));
      SVREF(workstation,FIX((SI_Long)17L)) = Nil;
      reclaim_if_managed_float(ISVREF(workstation,(SI_Long)24L));
      SVREF(workstation,FIX((SI_Long)24L)) = Nil;
      thing = ISVREF(workstation,(SI_Long)26L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(workstation,FIX((SI_Long)26L)) = Nil;
      reclaim_non_kb_workspaces_for_this_workstation_only_if_g2(ISVREF(workstation,
	      (SI_Long)32L));
      SVREF(workstation,FIX((SI_Long)32L)) = Nil;
      reclaim_gensym_tree_with_text_strings(ISVREF(workstation,(SI_Long)33L));
      SVREF(workstation,FIX((SI_Long)33L)) = Nil;
      reclaim_gensym_tree_with_text_strings(ISVREF(workstation,(SI_Long)34L));
      SVREF(workstation,FIX((SI_Long)34L)) = Nil;
      reclaim_gensym_tree_with_text_strings(ISVREF(workstation,(SI_Long)35L));
      SVREF(workstation,FIX((SI_Long)35L)) = Nil;
      thing = ISVREF(workstation,(SI_Long)38L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(workstation,FIX((SI_Long)38L)) = Nil;
      thing = ISVREF(workstation,(SI_Long)39L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(workstation,FIX((SI_Long)39L)) = Nil;
      reclaim_block_near_mouse_cache_function(ISVREF(workstation,
	      (SI_Long)42L));
      SVREF(workstation,FIX((SI_Long)42L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_workstations_vector,
	    IFIX(Current_thread_index));
    SVREF(workstation,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_workstations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = workstation;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-WORKSTATION */
Object reclaim_structure_for_workstation(workstation)
    Object workstation;
{
    x_note_fn_call(37,43);
    return reclaim_workstation_internal_1(workstation);
}

static Object Qg2_defstruct_structure_name_workstation_g2_struct;  /* g2-defstruct-structure-name::workstation-g2-struct */

/* MAKE-PERMANENT-WORKSTATION-STRUCTURE-INTERNAL */
Object make_permanent_workstation_structure_internal()
{
    Object def_structure_workstation_variable;
    Object defstruct_g2_workstation_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(37,44);
    def_structure_workstation_variable = Nil;
    atomic_incff_symval(Qworkstation_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_workstation_variable = Nil;
	gensymed_symbol = (SI_Long)56L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_workstation_variable = the_array;
	SVREF(defstruct_g2_workstation_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_workstation_g2_struct;
	def_structure_workstation_variable = defstruct_g2_workstation_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_workstation_variable);
}

static Object Qnone;               /* none */

static Object Qg2_window;          /* g2-window */

static Object Qlogged_out;         /* logged-out */

/* MAKE-WORKSTATION-1 */
Object make_workstation_1(window_for_workstation)
    Object window_for_workstation;
{
    Object def_structure_workstation_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(37,45);
    def_structure_workstation_variable = 
	    ISVREF(Chain_of_available_workstations_vector,
	    IFIX(Current_thread_index));
    if (def_structure_workstation_variable) {
	temp = Chain_of_available_workstations_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_workstation_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_workstation_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_workstation_g2_struct;
    }
    else
	def_structure_workstation_variable = 
		make_permanent_workstation_structure_internal();
    inline_note_allocate_cons(def_structure_workstation_variable,Nil);
    SVREF(def_structure_workstation_variable,FIX((SI_Long)1L)) = 
	    window_for_workstation;
    temp = make_queue();
    SVREF(def_structure_workstation_variable,FIX((SI_Long)2L)) = temp;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)4L)) = Nil;
    ISVREF(def_structure_workstation_variable,(SI_Long)5L) = FIX((SI_Long)0L);
    ISVREF(def_structure_workstation_variable,(SI_Long)6L) = FIX((SI_Long)0L);
    ISVREF(def_structure_workstation_variable,(SI_Long)9L) = FIX((SI_Long)0L);
    SVREF(def_structure_workstation_variable,FIX((SI_Long)10L)) = Qnone;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)15L)) = Nil;
    ISVREF(def_structure_workstation_variable,(SI_Long)16L) = FIX((SI_Long)2L);
    SVREF(def_structure_workstation_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)22L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)23L)) = Qg2_window;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)24L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)25L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)26L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)27L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)28L)) = Qlogged_out;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)29L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)30L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)31L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)32L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)33L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)34L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)35L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)36L)) = Nil;
    temp = add1(Last_session_id_for_g2);
    Last_session_id_for_g2 = temp;
    temp = Last_session_id_for_g2;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)37L)) = temp;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)38L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)39L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)40L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)41L)) = Nil;
    temp = make_block_near_mouse_cache();
    SVREF(def_structure_workstation_variable,FIX((SI_Long)42L)) = temp;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)43L)) = Nil;
    ISVREF(def_structure_workstation_variable,(SI_Long)44L) = FIX((SI_Long)0L);
    SVREF(def_structure_workstation_variable,FIX((SI_Long)45L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)46L)) = T;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)47L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)48L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)49L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)50L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)51L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)52L)) = Nil;
    SVREF(def_structure_workstation_variable,FIX((SI_Long)53L)) = Nil;
    return VALUES_1(def_structure_workstation_variable);
}

/* WINDOW-FOR-WORKSTATION-FUNCTION */
Object window_for_workstation_function(workstation)
    Object workstation;
{
    x_note_fn_call(37,46);
    return VALUES_1(ISVREF(workstation,(SI_Long)1L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Delete_corresponding_object_qm, Qdelete_corresponding_object_qm);

/* RECLAIM-WORKSTATION */
Object reclaim_workstation(workstation)
    Object workstation;
{
    Object delete_corresponding_object_qm;
    Declare_special(1);

    x_note_fn_call(37,47);
    if (EQ(Last_workstation_serviced,workstation))
	Last_workstation_serviced = Nil;
    Workstations_in_service = delete_gensym_element_1(workstation,
	    Workstations_in_service);
    delete_corresponding_object_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Delete_corresponding_object_qm,Qdelete_corresponding_object_qm,delete_corresponding_object_qm,
	    0);
      reclaim_icp_object_map_for_workstation(workstation);
    POP_SPECIAL();
    reclaim_workstation_tasks(workstation);
    SVREF(workstation,FIX((SI_Long)55L)) = Nil;
    return reclaim_workstation_internal_1(workstation);
}

/* RECLAIM-EVENT-PLIST */
Object reclaim_event_plist(plist)
    Object plist;
{
    Object v, ab_loop_list_, temp;

    x_note_fn_call(37,48);
    if ( ! !TRUEP(plist)) {
	v = Nil;
	ab_loop_list_ = plist;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	temp = CDR(ab_loop_list_);
	v = CAR(temp);
	if (text_string_p(v))
	    reclaim_text_string(v);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:;
	return reclaim_gensym_list_1(plist);
    }
    else
	return VALUES_1(Nil);
}

/* COPY-EVENT-PLIST */
Object copy_event_plist(plist)
    Object plist;
{
    Object p, v, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp;

    x_note_fn_call(37,49);
    if ( ! !TRUEP(plist)) {
	p = Nil;
	v = Nil;
	ab_loop_list_ = plist;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	p = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	v = CAR(temp);
	temp = p;
	ab_loopvar__2 = gensym_list_2(temp,text_string_p(v) ? 
		copy_text_string(v) : v);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_local_event = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_local_events, Qchain_of_available_local_events);

DEFINE_VARIABLE_WITH_SYMBOL(Local_event_count, Qlocal_event_count);

Object Chain_of_available_local_events_vector = UNBOUND;

/* LOCAL-EVENT-STRUCTURE-MEMORY-USAGE */
Object local_event_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(37,50);
    temp = Local_event_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-LOCAL-EVENT-COUNT */
Object outstanding_local_event_count()
{
    Object def_structure_local_event_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(37,51);
    gensymed_symbol = IFIX(Local_event_count);
    def_structure_local_event_variable = Chain_of_available_local_events;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_local_event_variable))
	goto end_loop;
    def_structure_local_event_variable = 
	    ISVREF(def_structure_local_event_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-LOCAL-EVENT-1-1 */
Object reclaim_local_event_1_1(local_event)
    Object local_event;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(37,52);
    inline_note_reclaim_cons(local_event,Nil);
    structure_being_reclaimed = local_event;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_event_plist(ISVREF(local_event,(SI_Long)7L));
      SVREF(local_event,FIX((SI_Long)7L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_local_events_vector,
	    IFIX(Current_thread_index));
    SVREF(local_event,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_local_events_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = local_event;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LOCAL-EVENT */
Object reclaim_structure_for_local_event(local_event)
    Object local_event;
{
    x_note_fn_call(37,53);
    return reclaim_local_event_1_1(local_event);
}

static Object Qg2_defstruct_structure_name_local_event_g2_struct;  /* g2-defstruct-structure-name::local-event-g2-struct */

/* MAKE-PERMANENT-LOCAL-EVENT-STRUCTURE-INTERNAL */
Object make_permanent_local_event_structure_internal()
{
    Object def_structure_local_event_variable;
    Object defstruct_g2_local_event_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(37,54);
    def_structure_local_event_variable = Nil;
    atomic_incff_symval(Qlocal_event_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_local_event_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_local_event_variable = the_array;
	SVREF(defstruct_g2_local_event_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_local_event_g2_struct;
	def_structure_local_event_variable = defstruct_g2_local_event_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_local_event_variable);
}

/* MAKE-LOCAL-EVENT-1 */
Object make_local_event_1()
{
    Object def_structure_local_event_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(37,55);
    def_structure_local_event_variable = 
	    ISVREF(Chain_of_available_local_events_vector,
	    IFIX(Current_thread_index));
    if (def_structure_local_event_variable) {
	svref_arg_1 = Chain_of_available_local_events_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_local_event_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_local_event_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_local_event_g2_struct;
    }
    else
	def_structure_local_event_variable = 
		make_permanent_local_event_structure_internal();
    inline_note_allocate_cons(def_structure_local_event_variable,Nil);
    SVREF(def_structure_local_event_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_local_event_variable);
}

/* RECLAIM-LOCAL-EVENT */
Object reclaim_local_event(local_event)
    Object local_event;
{
    x_note_fn_call(37,56);
    return reclaim_local_event_1_1(local_event);
}

/* COPY-LOCAL-EVENT */
Object copy_local_event(event)
    Object event;
{
    Object new_event, svref_new_value;

    x_note_fn_call(37,57);
    new_event = make_local_event_1();
    svref_new_value = ISVREF(event,(SI_Long)1L);
    SVREF(new_event,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)2L);
    SVREF(new_event,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)3L);
    SVREF(new_event,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)4L);
    SVREF(new_event,FIX((SI_Long)4L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)5L);
    SVREF(new_event,FIX((SI_Long)5L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)6L);
    SVREF(new_event,FIX((SI_Long)6L)) = svref_new_value;
    svref_new_value = copy_event_plist(ISVREF(event,(SI_Long)7L));
    SVREF(new_event,FIX((SI_Long)7L)) = svref_new_value;
    return VALUES_1(new_event);
}

Object Local_event_queue = UNBOUND;

/* RECLAIM-LOCAL-EVENT-QUEUE */
Object reclaim_local_event_queue(queue)
    Object queue;
{
    x_note_fn_call(37,58);
  next_loop:
    if ( !TRUEP(queue_non_empty_p(queue)))
	goto end_loop;
    reclaim_local_event(queue_pop(queue));
    goto next_loop;
  end_loop:
    return reclaim_queue(queue);
}

/* ENQUEUE-LOCAL-EVENT */
Object enqueue_local_event varargs_1(int, n)
{
    Object native_window_qm, key_code, x, y, timestamp;
    Object plist_qm, event, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(37,59);
    INIT_ARGS_nonrelocating();
    native_window_qm = REQUIRED_ARG_nonrelocating();
    key_code = REQUIRED_ARG_nonrelocating();
    x = REQUIRED_ARG_nonrelocating();
    y = REQUIRED_ARG_nonrelocating();
    timestamp = REQUIRED_ARG_nonrelocating();
    plist_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    event = make_local_event_1();
    SVREF(event,FIX((SI_Long)1L)) = key_code;
    SVREF(event,FIX((SI_Long)2L)) = timestamp;
    SVREF(event,FIX((SI_Long)3L)) = x;
    SVREF(event,FIX((SI_Long)4L)) = y;
    SVREF(event,FIX((SI_Long)5L)) = x;
    SVREF(event,FIX((SI_Long)6L)) = y;
    SVREF(event,FIX((SI_Long)7L)) = plist_qm;
    temp = get_event_queue_of_native_window(native_window_qm);
    if (temp);
    else
	temp = Local_event_queue;
    queue_insert(temp,event);
    return VALUES_1(event);
}

/* GET-LAST-LOCAL-MOUSE-MOTION-EVENT */
Object get_last_local_mouse_motion_event(native_window_qm)
    Object native_window_qm;
{
    Object last_one_qm, local_event_qm, temp, key_code, unicode;
    SI_Long temp_1;
    char temp_2;

    x_note_fn_call(37,60);
    last_one_qm = Nil;
    local_event_qm = Nil;
  next_loop:
    temp = get_event_queue_of_native_window(native_window_qm);
    if (temp);
    else
	temp = Local_event_queue;
    local_event_qm = queue_peek(temp);
    if (local_event_qm) {
	key_code = ISVREF(local_event_qm,(SI_Long)1L);
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    temp_1 = num_len(3,FIX((SI_Long)0L),unicode,
		    FIX((SI_Long)127L)) ? IFIX(unicode) : 
		    IFIX(Illegal_key_index);
	}
	else
	    temp_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	temp_2 = temp_1 == (SI_Long)771L;
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2)
	goto end_loop;
    if (last_one_qm)
	reclaim_local_event(last_one_qm);
    temp = get_event_queue_of_native_window(native_window_qm);
    if (temp);
    else
	temp = Local_event_queue;
    last_one_qm = queue_pop(temp);
    goto next_loop;
  end_loop:
    return VALUES_1(last_one_qm);
    return VALUES_1(Qnil);
}

Object Local_reshape_event_queue = UNBOUND;

static Object Qwindow;             /* window */

/* ENQUEUE-WINDOW-RESHAPE-EVENT */
Object enqueue_window_reshape_event varargs_1(int, n)
{
    Object native_window, key_code, timestamp;
    Object left_edge_of_area_qm, top_edge_of_area_qm, right_edge_of_area_qm;
    Object bottom_edge_of_area_qm, window_handle_qm, local_event;
    Object svref_new_value, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(37,61);
    INIT_ARGS_nonrelocating();
    native_window = REQUIRED_ARG_nonrelocating();
    key_code = REQUIRED_ARG_nonrelocating();
    timestamp = REQUIRED_ARG_nonrelocating();
    left_edge_of_area_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    top_edge_of_area_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    right_edge_of_area_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    bottom_edge_of_area_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    window_handle_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    local_event = make_local_event_1();
    SVREF(local_event,FIX((SI_Long)1L)) = key_code;
    SVREF(local_event,FIX((SI_Long)2L)) = timestamp;
    SVREF(local_event,FIX((SI_Long)3L)) = left_edge_of_area_qm;
    SVREF(local_event,FIX((SI_Long)4L)) = top_edge_of_area_qm;
    SVREF(local_event,FIX((SI_Long)5L)) = right_edge_of_area_qm;
    SVREF(local_event,FIX((SI_Long)6L)) = bottom_edge_of_area_qm;
    if (window_handle_qm) {
	svref_new_value = gensym_list_2(Qwindow,window_handle_qm);
	SVREF(local_event,FIX((SI_Long)7L)) = svref_new_value;
    }
    temp = get_reshape_event_queue_of_native_window(native_window);
    if (temp);
    else
	temp = Local_reshape_event_queue;
    return queue_insert(temp,local_event);
}

static Object Qcheck_shape_of_window_without_lookahead;  /* check-shape-of-window-without-lookahead */

/* CHECK-SHAPE-OF-WINDOW-WITHOUT-LOOKAHEAD */
Object check_shape_of_window_without_lookahead(gensym_window,native_window)
    Object gensym_window, native_window;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object work_was_done_qm, queue, temp_1;
    SI_Long count_1;
    Declare_special(1);

    x_note_fn_call(37,62);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qcheck_shape_of_window_without_lookahead;
      }
      work_was_done_qm = Nil;
      queue = get_gensym_window_reshape_event_queue(gensym_window);
      count_1 = (SI_Long)1L;
    next_loop:
      if (count_1 > (SI_Long)20L)
	  goto end_loop;
      if ( !TRUEP(queue_peek(queue)))
	  goto end_loop;
      handle_reshape_event(gensym_window,native_window);
      work_was_done_qm = T;
      count_1 = count_1 + (SI_Long)1L;
      goto next_loop;
    end_loop:;
      temp_1 = work_was_done_qm;
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* RESHAPE-NATIVE-G2-WINDOW */
Object reshape_native_g2_window(gensym_window,native_window)
    Object gensym_window, native_window;
{
    x_note_fn_call(37,63);
    make_or_revise_window_per_native_window(gensym_window,native_window);
    lay_out_window(gensym_window);
    flush_window_reshape_local_event_queue(native_window);
    return refresh_window(gensym_window);
}

/* GET-X-POSITION-OF-NATIVE-WINDOW */
Object get_x_position_of_native_window(native_window)
    Object native_window;
{
    Object temp;

    x_note_fn_call(37,64);
    temp = FIX(g2ext_x11_last_window_x(IFIX(native_window)));
    return VALUES_1(temp);
}

/* GET-Y-POSITION-OF-NATIVE-WINDOW */
Object get_y_position_of_native_window(native_window)
    Object native_window;
{
    Object temp;

    x_note_fn_call(37,65);
    temp = FIX(g2ext_x11_last_window_y(IFIX(native_window)));
    return VALUES_1(temp);
}

/* GET-WIDTH-OF-NATIVE-WINDOW */
Object get_width_of_native_window(native_window)
    Object native_window;
{
    Object temp_1;
    SI_Long temp;

    x_note_fn_call(37,66);
    temp = g2ext_x11_last_window_width(IFIX(native_window));
    temp_1 = FIX(MAX(temp,(SI_Long)22L));
    return VALUES_1(temp_1);
}

/* GET-HEIGHT-OF-NATIVE-WINDOW */
Object get_height_of_native_window(native_window)
    Object native_window;
{
    Object temp_1;
    SI_Long temp;

    x_note_fn_call(37,67);
    temp = g2ext_x11_last_window_height(IFIX(native_window));
    temp_1 = FIX(MAX(temp,(SI_Long)22L));
    return VALUES_1(temp_1);
}

Object Latest_icp_window_protocol_version = UNBOUND;

/* MAKE-OR-REVISE-WINDOW-PER-NATIVE-WINDOW */
Object make_or_revise_window_per_native_window(gensym_window_qm,native_window)
    Object gensym_window_qm, native_window;
{
    Object temp, temp_1, gensym_window;

    x_note_fn_call(37,68);
    temp = get_width_of_native_window(native_window);
    temp_1 = get_height_of_native_window(native_window);
    gensym_window = make_or_revise_window(gensym_window_qm,
	    FIX((SI_Long)0L),FIX((SI_Long)0L),temp,temp_1,native_window,
	    Nil, !TRUEP(gensym_window_qm) ? 
	    make_window_parameters_plist(native_window) : Nil);
    note_change_in_gensym_window(gensym_window);
    if ( !TRUEP(gensym_window_qm))
	change_icp_window_protocol_version(gensym_window,
		slave_gensym_window_qm(gensym_window) ? 
		Original_icp_window_protocol_version : 
		Latest_icp_window_protocol_version);
    return VALUES_1(gensym_window);
}

Object Fixnum_time_interval_for_automatic_xsync = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Fixnum_time_of_last_xsync, Qfixnum_time_of_last_xsync);

Object Scrollbar_code_names = UNBOUND;

/* SCROLLBAR-CODE-NAME */
Object scrollbar_code_name(code)
    Object code;
{
    Object temp;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(37,69);
    arg = (SI_Long)-1L;
    arg_1 = IFIX(code);
    arg_2 = IFIX(length(Scrollbar_code_names));
    temp = arg < arg_1 && arg_1 < arg_2 ? ISVREF(Scrollbar_code_names,
	    IFIX(code)) : Nil;
    return VALUES_1(temp);
}

static Object Qroot;               /* root */

static Object Qab_directory;       /* directory */

/* UNPACK-LIST-DIRECTORY-REQUEST-VALUE */
Object unpack_list_directory_request_value(value)
    Object value;
{
    Object pos_qm, temp;

    x_note_fn_call(37,70);
    pos_qm = position_in_wide_string(FIX((SI_Long)1L),value);
    if (pos_qm) {
	temp = wide_string_substring(value,FIX((SI_Long)0L),pos_qm);
	temp = gensym_list_4(Qroot,temp,Qab_directory,
		wide_string_substring(value,FIXNUM_ADD1(pos_qm),Nil));
	reclaim_wide_string(value);
	return VALUES_1(temp);
    }
    else
	return gensym_list_2(Qab_directory,value);
}

static Object Qhscroll;            /* hscroll */

static Object Qvscroll;            /* vscroll */

static Object Qcode;               /* code */

static Object Qthumb;              /* thumb */

static Object Qid;                 /* id */

static Object Qmenu_choice;        /* menu-choice */

static Object Qchoice;             /* choice */

static Object Qmenu;               /* menu */

static Object Qmenu_bar;           /* menu-bar */

static Object Qdialog_update;      /* dialog-update */

static Object Qdialog_id;          /* dialog-id */

static Object Qcontrol_id;         /* control-id */

static Object Qinitiator;          /* initiator */

static Object Qnew_value;          /* new-value */

static Object Qdialog_dismissed;   /* dialog-dismissed */

static Object Qdialog_response_code;  /* dialog-response-code */

static Object Qdialog_miscellaneous_communication;  /* dialog-miscellaneous-communication */

static Object Qmessage_type;       /* message-type */

static Object Qinfo;               /* info */

static Object Qdialog_user_gesture;  /* dialog-user-gesture */

static Object Qkey;                /* key */

static Object Qvalue;              /* value */

static Object Qnms_menu_posted;    /* nms-menu-posted */

static Object Qnms_menu_handle;    /* nms-menu-handle */

static Object Qitem;               /* item */

static Object Qnms_menu_unposted;  /* nms-menu-unposted */

static Object Qnms_menu_item_selected;  /* nms-menu-item-selected */

static Object Qprevious_nms_menu_handle;  /* previous-nms-menu-handle */

static Object Qprevious_item;      /* previous-item */

static Object Qnms_control;        /* nms-control */

static Object Qselection;          /* selection */

static Object Qtree_view;          /* tree-view */

static Object Qhandle;             /* handle */

static Object Qevent;              /* event */

static Object Qprop_grid;          /* prop-grid */

static Object Qivalue;             /* ivalue */

static Object Qgrid_view;          /* grid-view */

static Object Qtabular_view;       /* tabular-view */

static Object Qchart_view;         /* chart-view */

static Object Qshortcut_bar;       /* shortcut-bar */

static Object Qdrag_to;            /* drag-to */

static Object Qfolder;             /* folder */

static Object Qhtml_view;          /* html-view */

static Object Qlogbook_view;       /* logbook-view */

static Object Qmsg;                /* msg */

static Object Qstatus_bar;         /* status-bar */

static Object Qpane;               /* pane */

static Object Qbits;               /* bits */

static Object Qdebugger_dialog;    /* debugger-dialog */

static Object Qopcode;             /* opcode */

static Object Qline;               /* line */

static Object Qeditor;             /* editor */

static Object Qcaret;              /* caret */

static Object Qend;                /* end */

static Object Qtext;               /* text */

static Object Qlist_directory;     /* list-directory */

static Object Qwindow_refresh;     /* window-refresh */

static Object Qwidth;              /* width */

static Object Qheight;             /* height */

static Object Qwindow_moved;       /* window-moved */

static Object Qstatus;             /* status */

static Object Qwindow_sized;       /* window-sized */

/* DECODE-NATIVE-CONTROL-EVENT */
Object decode_native_control_event(key_code,x,y,width,height,
	    window_handle_qm,value_qm)
    Object key_code, x, y, width, height, window_handle_qm, value_qm;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, car_new_value, temp_1;
    Object temp_2, temp_3;

    x_note_fn_call(37,71);
    temp = convert_key_code_to_key_symbol(key_code);
    if (EQ(temp,Qhscroll) || EQ(temp,Qvscroll)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qcode;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = scrollbar_code_name(x);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qthumb;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = y;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qid;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = width;
	temp = nconc2(gensymed_symbol,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Qnil);
    }
    else if (EQ(temp,Qmenu_choice))
	temp = gensym_list_4(Qchoice,x,Qmenu,y);
    else if (EQ(temp,Qmenu_bar))
	temp = Nil;
    else if (EQ(temp,Qdialog_update)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)8L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qdialog_id;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = map_client_dialog_id_to_global_dialog_id(x);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qcontrol_id;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = y;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qinitiator;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = width;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qnew_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = value_qm;
	temp = gensymed_symbol;
    }
    else if (EQ(temp,Qdialog_dismissed))
	temp = gensym_list_4(Qdialog_id,remove_dialog_given_client_id(x),
		Qdialog_response_code,y);
    else if (EQ(temp,Qdialog_miscellaneous_communication)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)8L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qdialog_id;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = map_client_dialog_id_to_global_dialog_id(x);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qcontrol_id;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = y;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qmessage_type;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = width;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qinfo;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = value_qm;
	temp = gensymed_symbol;
    }
    else if (EQ(temp,Qdialog_user_gesture)) {
	temp_1 = gensym_list_4(Qcontrol_id,width,Qkey,height);
	temp_2 = IFIX(x) >= (SI_Long)0L ? gensym_list_2(Qrow,x) : Nil;
	temp = IFIX(y) >= (SI_Long)0L ? gensym_list_2(Qcolumn,y) : Nil;
	temp = nconc2(temp_1,nconc2(temp_2,nconc2(temp,nconc2(value_qm ? 
		gensym_list_2(Qvalue,value_qm) : Nil,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Nil))));
    }
    else if (EQ(temp,Qnms_menu_posted))
	temp = gensym_list_4(Qnms_menu_handle,x,Qitem,y);
    else if (EQ(temp,Qnms_menu_unposted))
	temp = gensym_list_2(Qnms_menu_handle,x);
    else if (EQ(temp,Qnms_menu_item_selected)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)8L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qnms_menu_handle;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = x;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qitem;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = y;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qprevious_nms_menu_handle;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = width;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qprevious_item;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = height;
	temp = gensymed_symbol;
    }
    else if (EQ(temp,Qnms_control)) {
	temp = gensym_list_4(Qcontrol_id,x,Qselection,y);
	temp = nconc2(temp,nconc2(value_qm ? gensym_list_2(Qvalue,
		value_qm) : Nil,window_handle_qm ? gensym_list_2(Qwindow,
		window_handle_qm) : Nil));
    }
    else if (EQ(temp,Qtree_view)) {
	temp_3 = gensym_list_2(Qhandle,width);
	temp_1 = gensym_list_2(Qevent,height);
	temp_2 = gensym_list_2(Qitem,x);
	temp = IFIX(y) > (SI_Long)0L ? gensym_list_2(Qkey,y) : Nil;
	temp = nconc2(temp_3,nconc2(temp_1,nconc2(temp_2,nconc2(temp,
		nconc2(value_qm ? gensym_list_2(Qvalue,value_qm) : Nil,
		window_handle_qm ? gensym_list_2(Qwindow,window_handle_qm) 
		: Nil)))));
    }
    else if (EQ(temp,Qprop_grid)) {
	temp_1 = gensym_list_2(Qevent,x);
	temp_2 = gensym_list_2(Qitem,y);
	temp = FIXNUM_NE(width,Most_negative_fixnum) ? 
		gensym_list_2(Qivalue,width) : Nil;
	temp = nconc2(temp_1,nconc2(temp_2,nconc2(temp,nconc2(value_qm ? 
		gensym_list_2(Qvalue,value_qm) : Nil,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Nil))));
    }
    else if (EQ(temp,Qgrid_view)) {
	temp_3 = gensym_list_2(Qevent,x);
	temp_1 = gensym_list_2(Qcontrol_id,y);
	temp_2 = gensym_list_2(Qrow,width);
	temp = gensym_list_2(Qcolumn,height);
	temp = nconc2(temp_3,nconc2(temp_1,nconc2(temp_2,nconc2(temp,
		nconc2(value_qm ? gensym_list_2(Qvalue,value_qm) : Nil,
		window_handle_qm ? gensym_list_2(Qwindow,window_handle_qm) 
		: Nil)))));
    }
    else if (EQ(temp,Qtabular_view)) {
	temp_3 = gensym_list_2(Qevent,x);
	temp_1 = gensym_list_2(Qrow,y);
	temp_2 = IFIX(height) >= (SI_Long)0L ? gensym_list_2(Qcolumn,
		height) : Nil;
	temp = IFIX(width) > (SI_Long)0L ? gensym_list_2(Qkey,width) : Nil;
	temp = nconc2(temp_3,nconc2(temp_1,nconc2(temp_2,nconc2(temp,
		nconc2(value_qm ? gensym_list_2(Qvalue,value_qm) : Nil,
		window_handle_qm ? gensym_list_2(Qwindow,window_handle_qm) 
		: Nil)))));
    }
    else if (EQ(temp,Qchart_view)) {
	temp_1 = gensym_list_4(Qx,x,Qy,y);
	temp_2 = gensym_list_2(Qhandle,width);
	temp = gensym_list_2(Qevent,height);
	temp = nconc2(temp_1,nconc2(temp_2,nconc2(temp,nconc2(value_qm ? 
		gensym_list_2(Qvalue,value_qm) : Nil,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Nil))));
    }
    else if (EQ(temp,Qshortcut_bar)) {
	temp_3 = gensym_list_2(Qevent,x);
	temp_1 = gensym_list_2(Qdrag_to,y);
	temp_2 = gensym_list_2(Qfolder,width);
	temp = gensym_list_2(Qitem,height);
	temp = nconc2(temp_3,nconc2(temp_1,nconc2(temp_2,nconc2(temp,
		nconc2(value_qm ? gensym_list_2(Qvalue,value_qm) : Nil,
		window_handle_qm ? gensym_list_2(Qwindow,window_handle_qm) 
		: Nil)))));
    }
    else if (EQ(temp,Qhtml_view)) {
	temp_1 = gensym_list_4(Qx,x,Qy,y);
	temp_2 = gensym_list_2(Qhandle,width);
	temp = gensym_list_2(Qevent,height);
	temp = nconc2(temp_1,nconc2(temp_2,nconc2(temp,nconc2(value_qm ? 
		gensym_list_2(Qvalue,value_qm) : Nil,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Nil))));
    }
    else if (EQ(temp,Qlogbook_view)) {
	temp_1 = gensym_list_4(Qx,x,Qy,y);
	temp_2 = gensym_list_2(Qmsg,width);
	temp = gensym_list_2(Qevent,height);
	temp = nconc2(temp_1,nconc2(temp_2,nconc2(temp,nconc2(value_qm ? 
		gensym_list_2(Qvalue,value_qm) : Nil,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Nil))));
    }
    else if (EQ(temp,Qstatus_bar)) {
	temp_1 = gensym_list_2(Qevent,x);
	temp_2 = gensym_list_2(Qpane,y);
	temp = gensym_list_2(Qbits,width);
	temp = nconc2(temp_1,nconc2(temp_2,nconc2(temp,nconc2(value_qm ? 
		gensym_list_2(Qvalue,value_qm) : Nil,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Nil))));
    }
    else if (EQ(temp,Qdebugger_dialog))
	temp = nconc2(gensym_list_4(Qopcode,x,Qline,y),window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Nil);
    else if (EQ(temp,Qeditor)) {
	temp_1 = gensym_list_2(Qopcode,x);
	temp_2 = gensym_list_2(Qcaret,y);
	temp = IFIX(width) >= (SI_Long)0L ? gensym_list_2(Qend,width) : Nil;
	temp = nconc2(temp_1,nconc2(temp_2,nconc2(temp,nconc2(value_qm ? 
		gensym_list_2(Qtext,value_qm) : Nil,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Nil))));
    }
    else if (EQ(temp,Qlist_directory)) {
	temp_1 = gensym_list_2(Qhandle,x);
	temp_2 = IFIX(y) >= (SI_Long)0L ? gensym_list_2(Qopcode,y) : Nil;
	temp = value_qm ? unpack_list_directory_request_value(value_qm) : Nil;
	temp = nconc2(temp_1,nconc2(temp_2,nconc2(temp,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Nil)));
    }
    else if (EQ(temp,Qwindow_refresh)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)8L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qx;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = x;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qy;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = y;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qwidth;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = width;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qheight;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = height;
	temp = nconc2(gensymed_symbol,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Qnil);
    }
    else if (EQ(temp,Qwindow_moved)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qx;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = x;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qy;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = y;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qstatus;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = width;
	temp = nconc2(gensymed_symbol,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Qnil);
    }
    else if (EQ(temp,Qwindow_sized)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qwidth;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = width;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qheight;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = height;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qstatus;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = x;
	temp = nconc2(gensymed_symbol,window_handle_qm ? 
		gensym_list_2(Qwindow,window_handle_qm) : Qnil);
    }
    else
	temp = window_handle_qm ? gensym_list_2(Qwindow,window_handle_qm) :
		 Nil;
    return VALUES_1(temp);
}

/* NATIVE-WINDOW-HANDLE-FOR-LAST-EVENT? */
Object native_window_handle_for_last_event_qm(native_window)
    Object native_window;
{
    SI_Long handle;

    x_note_fn_call(37,72);
    handle = g2ext_x11_last_event_window_handle(IFIX(native_window));
    if (handle >= (SI_Long)0L)
	return VALUES_1(FIX(handle));
    else
	return VALUES_1(Nil);
}

/* STRING-VALUE-FOR-LAST-EVENT? */
Object string_value_for_last_event_qm(native_window)
    Object native_window;
{
    Object length_1, string_1;

    x_note_fn_call(37,73);
    length_1 = c_x11_last_event_value(native_window,array_constant_3,
	    FIX((SI_Long)0L));
    if (IFIX(length_1) >= (SI_Long)0L) {
	string_1 = obtain_text_string(length_1);
	c_x11_last_event_value(native_window,string_1,length_1);
	return VALUES_1(string_1);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_workstation, Qcurrent_workstation);

DEFINE_VARIABLE_WITH_SYMBOL(Current_workstation_window, Qcurrent_workstation_window);

/* GET-ALL-X11-EVENTS */
Object get_all_x11_events(native_window)
    Object native_window;
{
    Object fixnum_time, event_code, temp, event_type_1, key_code_1, temp_1;
    Object temp_2, temp_3, temp_4, plist;
    SI_Long gensymed_symbol, event_code_1, event_type, key_code, last_window_x;
    SI_Long last_window_y, last_window_width, last_window_height;
    SI_Long last_expose_x, last_expose_y, last_expose_width;
    SI_Long last_expose_height;
    Object result;

    x_note_fn_call(37,74);
    fixnum_time = c_native_clock_ticks_or_cache(Nil,Nil);
    event_code = FIX((SI_Long)0L);
  next_loop:
    if (FIXNUM_GE(fixnum_time,Fixnum_time_of_last_xsync))
	temp = FIXNUM_MINUS(fixnum_time,Fixnum_time_of_last_xsync);
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(fixnum_time,
		Fixnum_time_of_last_xsync));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	temp = FIX(gensymed_symbol + (SI_Long)1L);
    }
    if (FIXNUM_GT(temp,Fixnum_time_interval_for_automatic_xsync)) {
	Fixnum_time_of_last_xsync = fixnum_time;
	sync_graphics_on_native_window(native_window);
    }
    event_code = FIX(g2ext_get_event(IFIX(native_window)));
    event_code_1 = IFIX(event_code);
    event_type = event_code_1 & IFIX(X11_event_codes_mask);
    key_code = event_code_1 >>  -  - (SI_Long)4L;
    if (event_code_1 == IFIX(X11_no_more_events))
	result = VALUES_2(FIX(event_code_1),FIX((SI_Long)0L));
    else if (event_type == IFIX(X11_keypress)) {
	temp = canonicalize_gensym_key_code(FIX(key_code));
	result = VALUES_2(FIX(event_type),temp);
    }
    else if (event_type == IFIX(X11_button_press) || event_type == 
	    IFIX(X11_button_release) || event_type == 
		IFIX(X11_pointer_motion)) {
	temp = FIX(key_code & IFIX(FIXNUM_LOGNOT(Caps_lock_bit)));
	result = VALUES_2(FIX(event_type),temp);
    }
    else
	result = VALUES_2(FIX(event_type),FIX(key_code));
    MVS_2(result,event_type_1,key_code_1);
    if (IFIX(event_type_1) == (SI_Long)-1L)
	goto end_loop;
    else if (IFIX(event_type_1) == (SI_Long)0L);
    else if (IFIX(event_type_1) == (SI_Long)9L) {
	if (native_window_handle_for_last_event_qm(native_window)) {
	    temp = FIX(g2ext_x11_last_mouse_x_position(IFIX(native_window)));
	    temp_1 = FIX(g2ext_x11_last_mouse_y_position(IFIX(native_window)));
	    temp_2 = FIX(g2ext_x11_last_event_time(IFIX(native_window)));
	    enqueue_local_event(6,native_window,FIX((SI_Long)788L),temp,
		    temp_1,temp_2,gensym_list_2(Qwindow,
		    native_window_handle_for_last_event_qm(native_window)));
	}
	if (ISVREF(Current_workstation,(SI_Long)46L) && 
		window_supports_request_for_paste_availability_function(Current_workstation_window))
	    enqueue_local_paste_availability_event(native_window,
		    local_clipboard_has_text_p(Current_workstation_window),
		    FIX((SI_Long)1L));
    }
    else if (IFIX(event_type_1) == (SI_Long)7L) {
	if (Native_window_notices_enter_and_leave_events_p) {
	    temp = FIX(g2ext_x11_last_mouse_x_position(IFIX(native_window)));
	    temp_1 = FIX(g2ext_x11_last_mouse_y_position(IFIX(native_window)));
	    enqueue_local_event(5,native_window,FIX((SI_Long)790L),temp,
		    temp_1,
		    FIX(g2ext_x11_last_event_time(IFIX(native_window))));
	}
    }
    else if (IFIX(event_type_1) == (SI_Long)8L) {
	if (Native_window_notices_enter_and_leave_events_p) {
	    temp = FIX(g2ext_x11_last_mouse_x_position(IFIX(native_window)));
	    temp_1 = FIX(g2ext_x11_last_mouse_y_position(IFIX(native_window)));
	    enqueue_local_event(5,native_window,FIX((SI_Long)791L),temp,
		    temp_1,
		    FIX(g2ext_x11_last_event_time(IFIX(native_window))));
	}
    }
    else if (IFIX(event_type_1) == (SI_Long)6L) {
	last_window_x = g2ext_x11_last_window_x(IFIX(native_window));
	last_window_y = g2ext_x11_last_window_y(IFIX(native_window));
	last_window_width = g2ext_x11_last_window_width(IFIX(native_window));
	last_window_height = g2ext_x11_last_window_height(IFIX(native_window));
	temp = FIX(g2ext_x11_last_event_time(IFIX(native_window)));
	temp_1 = FIX(last_window_x + last_window_width);
	temp_2 = FIX(last_window_y + last_window_height);
	enqueue_window_reshape_event(8,native_window,FIX((SI_Long)785L),
		temp,FIX(last_window_x),FIX(last_window_y),temp_1,temp_2,
		native_window_handle_for_last_event_qm(native_window));
    }
    else if (IFIX(event_type_1) == (SI_Long)5L) {
	if ( !TRUEP(last_exposure_event_already_queued_p(native_window))) {
	    last_expose_x = 
		    g2ext_x11_last_expose_x_position(IFIX(native_window));
	    last_expose_y = 
		    g2ext_x11_last_expose_y_position(IFIX(native_window));
	    last_expose_width = 
		    g2ext_x11_last_expose_width(IFIX(native_window));
	    last_expose_height = 
		    g2ext_x11_last_expose_height(IFIX(native_window));
	    temp = FIX(g2ext_x11_last_event_time(IFIX(native_window)));
	    temp_1 = FIX(last_expose_x + last_expose_width);
	    temp_2 = FIX(last_expose_y + last_expose_height);
	    enqueue_window_reshape_event(8,native_window,
		    FIX((SI_Long)784L),temp,FIX(last_expose_x),
		    FIX(last_expose_y),temp_1,temp_2,
		    native_window_handle_for_last_event_qm(native_window));
	}
    }
    else if (IFIX(event_type_1) == (SI_Long)11L) {
	temp_3 = FIX(g2ext_x11_last_expose_x_position(IFIX(native_window)));
	temp_4 = FIX(g2ext_x11_last_expose_y_position(IFIX(native_window)));
	temp_2 = FIX(g2ext_x11_last_expose_width(IFIX(native_window)));
	temp_1 = FIX(g2ext_x11_last_expose_height(IFIX(native_window)));
	temp = native_window_handle_for_last_event_qm(native_window);
	plist = decode_native_control_event(key_code_1,temp_3,temp_4,
		temp_2,temp_1,temp,
		string_value_for_last_event_qm(native_window));
	temp = FIX(g2ext_x11_last_mouse_x_position(IFIX(native_window)));
	temp_1 = FIX(g2ext_x11_last_mouse_y_position(IFIX(native_window)));
	enqueue_local_event(6,native_window,key_code_1,temp,temp_1,
		FIX(g2ext_x11_last_event_time(IFIX(native_window))),plist);
    }
    else {
	temp = FIX(g2ext_x11_last_mouse_x_position(IFIX(native_window)));
	temp_1 = FIX(g2ext_x11_last_mouse_y_position(IFIX(native_window)));
	temp_2 = FIX(g2ext_x11_last_event_time(IFIX(native_window)));
	enqueue_local_event(6,native_window,key_code_1,temp,temp_1,temp_2,
		construct_local_event_plist(native_window));
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* LAST-EXPOSURE-EVENT-ALREADY-QUEUED-P */
Object last_exposure_event_already_queued_p(native_window)
    Object native_window;
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(37,75);
    temp = FIX(g2ext_x11_last_expose_x_position(IFIX(native_window)));
    temp_1 = FIX(g2ext_x11_last_expose_y_position(IFIX(native_window)));
    temp_2 = FIX(g2ext_x11_last_expose_width(IFIX(native_window)));
    return find_local_reshape_event(native_window,FIX((SI_Long)784L),temp,
	    temp_1,temp_2,
	    FIX(g2ext_x11_last_expose_height(IFIX(native_window))));
}

/* FLUSH-WINDOW-RESHAPE-LOCAL-EVENT-QUEUE */
Object flush_window_reshape_local_event_queue(native_window)
    Object native_window;
{
    Object e, temp;

    x_note_fn_call(37,76);
    e = Nil;
  next_loop:
    temp = get_reshape_event_queue_of_native_window(native_window);
    if (temp);
    else
	temp = Local_reshape_event_queue;
    e = queue_pop(temp);
    if ( !TRUEP(e))
	goto end_loop;
    reclaim_local_event(e);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FIND-LOCAL-RESHAPE-EVENT */
Object find_local_reshape_event(native_window,event_code,x,y,width,height)
    Object native_window, event_code, x, y, width, height;
{
    Object temp, queue_sublist, e;
    char temp_1;

    x_note_fn_call(37,77);
    temp = get_reshape_event_queue_of_native_window(native_window);
    if (temp);
    else
	temp = Local_reshape_event_queue;
    queue_sublist = ISVREF(temp,(SI_Long)1L);
    e = Nil;
  next_loop:
    if ( !TRUEP(queue_sublist))
	goto end_loop;
    e = M_CAR(queue_sublist);
    queue_sublist = M_CDR(queue_sublist);
    temp = ISVREF(e,(SI_Long)1L);
    if (EQL(temp,event_code)) {
	temp = ISVREF(e,(SI_Long)3L);
	temp_1 = EQL(temp,x);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = ISVREF(e,(SI_Long)4L);
	temp_1 = EQL(temp,y);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = ISVREF(e,(SI_Long)5L);
	temp_1 = EQL(temp,width);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = ISVREF(e,(SI_Long)6L);
	temp_1 = EQL(temp,height);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(e);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_workstation_native_window_qm, Qcurrent_workstation_native_window_qm);

/* SET-POSITION-OF-MOUSE-1 */
Object set_position_of_mouse_1(x,y)
    Object x, y;
{
    x_note_fn_call(37,78);
    g2ext_x11_move_pointer(IFIX(Current_workstation_native_window_qm),
	    IFIX(x),IFIX(y));
    return VALUES_2(x,y);
}

/* SHIFT-POSITION-OF-MOUSE-1 */
Object shift_position_of_mouse_1(delta_x,delta_y)
    Object delta_x, delta_y;
{
    Object mouse_x, mouse_y;
    Object result;

    x_note_fn_call(37,79);
    result = get_position_of_mouse();
    MVS_2(result,mouse_x,mouse_y);
    return set_position_of_mouse_1(add(mouse_x,delta_x),add(mouse_y,delta_y));
}

/* GET-POSITION-OF-MOUSE */
Object get_position_of_mouse()
{
    SI_Long mouse_x, mouse_y;

    x_note_fn_call(37,80);
    if ( !TRUEP(Current_workstation_native_window_qm))
	return VALUES_2(FIX((SI_Long)10L),FIX((SI_Long)10L));
    else {
	mouse_x = 
		g2ext_x11_get_mouse_x_position(IFIX(Current_workstation_native_window_qm));
	mouse_y = 
		g2ext_x11_last_mouse_y_position(IFIX(Current_workstation_native_window_qm));
	return VALUES_2(FIX(mouse_x),FIX(mouse_y));
    }
}

Object Native_window_polling_interval_default = UNBOUND;

Object Native_window_polling_interval_fast = UNBOUND;

Object Native_window_polling_interval = UNBOUND;

/* START-MOUSE-TRACKING */
Object start_mouse_tracking(native_window)
    Object native_window;
{
    x_note_fn_call(37,81);
    Native_window_polling_interval = Native_window_polling_interval_fast;
    g2ext_start_tracking_mouse(IFIX(native_window));
    return VALUES_1(T);
}

/* STOP-MOUSE-TRACKING */
Object stop_mouse_tracking(native_window)
    Object native_window;
{
    x_note_fn_call(37,82);
    Native_window_polling_interval = Native_window_polling_interval_default;
    g2ext_stop_tracking_mouse(IFIX(native_window));
    return VALUES_1(T);
}

DEFINE_VARIABLE_WITH_SYMBOL(For_workstation_context, Qfor_workstation_context);

DEFINE_VARIABLE_WITH_SYMBOL(Specific_structure_for_current_workstation_context, Qspecific_structure_for_current_workstation_context);

DEFINE_VARIABLE_WITH_SYMBOL(Type_of_current_workstation_context, Qtype_of_current_workstation_context);

DEFINE_VARIABLE_WITH_SYMBOL(Current_workstation_context, Qcurrent_workstation_context);

DEFINE_VARIABLE_WITH_SYMBOL(For_workstation_polling, Qfor_workstation_polling);

DEFINE_VARIABLE_WITH_SYMBOL(Type_of_current_workstation_window, Qtype_of_current_workstation_window);

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* GET-X11-PIXEL-VALUE-FROM-RGB */
Object get_x11_pixel_value_from_rgb(native_x11_window,red,green,blue,
	    extended_color_p)
    Object native_x11_window, red, green, blue, extended_color_p;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, string_1, pixel_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(37,83);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      twrite_beginning_of_wide_string(array_constant_6,
		      FIX((SI_Long)1L));
	      temp = FIX((SI_Long)16L);
	      if (NUM_LT(red,temp))
		  twrite_beginning_of_wide_string(array_constant_7,
			  FIX((SI_Long)1L));
	      twrite_positive_fixnum_in_radix(red,FIX((SI_Long)16L));
	      temp = FIX((SI_Long)16L);
	      if (NUM_LT(green,temp))
		  twrite_beginning_of_wide_string(array_constant_7,
			  FIX((SI_Long)1L));
	      twrite_positive_fixnum_in_radix(green,FIX((SI_Long)16L));
	      temp = FIX((SI_Long)16L);
	      if (NUM_LT(blue,temp))
		  twrite_beginning_of_wide_string(array_constant_7,
			  FIX((SI_Long)1L));
	      twrite_positive_fixnum_in_radix(blue,FIX((SI_Long)16L));
	      string_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    pixel_qm = get_pixel_value(native_x11_window,string_1,extended_color_p);
    reclaim_text_string(string_1);
    return VALUES_1(pixel_qm);
}

/* ALLOCATE-X11-PIXEL-VALUE */
Object allocate_x11_pixel_value(x11_window,color_symbol)
    Object x11_window, color_symbol;
{
    Object color_name_text_string, pixel_qm, color_r_g_b_qm;

    x_note_fn_call(37,84);
    color_name_text_string = copy_symbol_name(3,color_symbol,Nil,T);
    pixel_qm = get_pixel_value(x11_window,color_name_text_string,Nil);
    reclaim_text_string(color_name_text_string);
    if ( !TRUEP(pixel_qm)) {
	color_r_g_b_qm = assoc_eql(color_symbol,Standard_gensym_color_alist);
	if (color_r_g_b_qm)
	    pixel_qm = get_x11_pixel_value_from_rgb(x11_window,
		    SECOND(color_r_g_b_qm),THIRD(color_r_g_b_qm),
		    FOURTH(color_r_g_b_qm),Nil);
    }
    return VALUES_1(pixel_qm);
}

/* CREATE-X11-COLOR-PLIST-FROM-COLOR-HIERARCHY */
Object create_x11_color_plist_from_color_hierarchy varargs_1(int, n)
{
    Object x11_window, c_hierarchy;
    Object default_pixel_value, number_of_colors_left, queue, entry;
    Object entry_default_pixel, entry_name, pixel_value, plist, ab_loopvar_;
    Object ab_loopvar__1, temp_1, sub_entry, ab_loop_list_;
    SI_Long temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(37,85);
    INIT_ARGS_nonrelocating();
    x11_window = REQUIRED_ARG_nonrelocating();
    c_hierarchy = REQUIRED_ARG_nonrelocating();
    default_pixel_value = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)0L);
    number_of_colors_left = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(number_of_colors_left)) {
	temp = g2ext_x11_screen_depth(IFIX(x11_window));
	temp = expt_long((SI_Long)2L,MIN((SI_Long)24L,temp)) - (SI_Long)2L;
	number_of_colors_left = FIX(MAX(temp,(SI_Long)2L));
    }
    queue = make_queue();
    entry = gensym_cons_1(default_pixel_value,c_hierarchy);
    entry_default_pixel = Nil;
    entry_name = Nil;
    pixel_value = Nil;
    plist = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    entry_default_pixel = CAR(entry);
    temp_1 = CDR(entry);
    entry_name = SYMBOLP(temp_1) ? CDR(entry) : SECOND(entry);
    if (IFIX(number_of_colors_left) > (SI_Long)0L &&  !EQ(entry_name,Qroot)) {
	number_of_colors_left = FIXNUM_SUB1(number_of_colors_left);
	temp_1 = allocate_x11_pixel_value(x11_window,entry_name);
    }
    else
	temp_1 = Nil;
    if (temp_1);
    else
	temp_1 = entry_default_pixel;
    pixel_value = temp_1;
    if ( !EQ(entry_name,Qroot)) {
	ab_loopvar__1 = gensym_list_2(entry_name,gensym_cons_1(pixel_value,
		Nil));
	if (ab_loopvar__1) {
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		plist = ab_loopvar__1;
	    ab_loopvar_ = last(ab_loopvar__1,_);
	}
    }
    temp_1 = CDR(entry);
    if (CONSP(temp_1)) {
	sub_entry = Nil;
	ab_loop_list_ = CDDR(entry);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	sub_entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	queue_insert(queue,gensym_cons_1(pixel_value,sub_entry));
	goto next_loop_1;
      end_loop:;
    }
    reclaim_gensym_cons_1(entry);
    if ( !TRUEP(ISVREF(queue,(SI_Long)1L)))
	goto end_loop_1;
    entry = queue_pop(queue);
    goto next_loop;
  end_loop_1:
    reclaim_queue(queue);
    return VALUES_1(plist);
    return VALUES_1(Qnil);
}

static Object string_constant_6;   /* "#000000" */

static Object string_constant_7;   /* "#ffffff" */

/* ALLOCATE-X11-COLORS */
Object allocate_x11_colors(x11_window)
    Object x11_window;
{
    Object temp;
    SI_Long screen_depth;

    x_note_fn_call(37,86);
    screen_depth = g2ext_x11_screen_depth(IFIX(x11_window));
    if (screen_depth > (SI_Long)1L)
	return create_x11_color_plist_from_color_hierarchy(3,x11_window,
		Color_hierarchy,FIX((SI_Long)0L));
    else {
	temp = get_pixel_value(x11_window,string_constant_6,Nil);
	return make_monochrome_color_description_plist(temp,
		get_pixel_value(x11_window,string_constant_7,Nil));
    }
}

static Object Qwhite;              /* white */

/* MAKE-MONOCHROME-COLOR-DESCRIPTION-PLIST */
Object make_monochrome_color_description_plist(black_pixel_value,
	    white_pixel_value)
    Object black_pixel_value, white_pixel_value;
{
    Object color, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_;

    x_note_fn_call(37,87);
    color = Nil;
    ab_loop_list_ = Standard_gensym_color_alist;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = gensym_cons_1(color,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loopvar__2 = 
	    gensym_cons_1(gensym_cons_1(EQ(map_to_black_or_white(color),
	    Qwhite) ? white_pixel_value : black_pixel_value,Nil),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object Qsystem_metrics;     /* system-metrics */

/* GET-SYSTEM-METRICS-FOR-LOCAL-WINDOW */
Object get_system_metrics_for_local_window()
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    SI_Long i;

    x_note_fn_call(37,88);
    if (windows_platform_p()) {
	i = (SI_Long)0L;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (i >= IFIX(Number_of_system_metrics))
	    goto end_loop;
	ab_loopvar__2 = gensym_cons_1(FIX(g2ext_get_system_metric(i)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
	return gensym_list_2(Qsystem_metrics,temp);
    }
    else
	return VALUES_1(Nil);
}

Object Default_width_of_window_border = UNBOUND;

static Object list_constant_1;     /* # */

static Object Qwidth_of_window_border;  /* width-of-window-border */

static Object Qdefault_x_scale;    /* default-x-scale */

static Object Qdefault_y_scale;    /* default-y-scale */

static Object Qcolor_description_plist_qm;  /* color-description-plist? */

static Object Qwindow_x_in_parent;  /* window-x-in-parent */

static Object Qwindow_y_in_parent;  /* window-y-in-parent */

static Object Qdefault_pane_background_color_or_tiling_pattern_rows;  /* default-pane-background-color-or-tiling-pattern-rows */

static Object Qicp_window_protocol_version;  /* icp-window-protocol-version */

static Object Qwindow_screen_depth;  /* window-screen-depth */

/* MAKE-WINDOW-PARAMETERS-PLIST */
Object make_window_parameters_plist(native_window_qm)
    Object native_window_qm;
{
    Object constant_plist, gensymed_symbol, gensymed_symbol_1, car_new_value;
    Object gensymed_symbol_2, varying_plist, temp, temp_1, result_1;
    Object result;

    x_note_fn_call(37,89);
    constant_plist = list_constant_1;
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)16L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qwidth_of_window_border;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = Default_width_of_window_border;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qdefault_x_scale;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = get_default_x_and_y_scale_from_command_line_if_any(0);
    if (car_new_value);
    else
	car_new_value = FIX((SI_Long)4096L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qdefault_y_scale;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    result = get_default_x_and_y_scale_from_command_line_if_any(1,T);
    gensymed_symbol_2 = NTH_VALUE((SI_Long)1L, result);
    if (gensymed_symbol_2);
    else
	gensymed_symbol_2 = FIX((SI_Long)4096L);
    M_CAR(gensymed_symbol_1) = gensymed_symbol_2;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qcolor_description_plist_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = native_window_qm ? 
	    allocate_x11_colors(native_window_qm) : Nil;
    if (car_new_value);
    else
	car_new_value = 
		make_monochrome_color_description_plist(FIX((SI_Long)1L),
		FIX((SI_Long)0L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qwindow_x_in_parent;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = native_window_qm ? 
	    get_x_position_of_native_window(native_window_qm) : 
	    FIX((SI_Long)0L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qwindow_y_in_parent;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = native_window_qm ? 
	    get_y_position_of_native_window(native_window_qm) : 
	    FIX((SI_Long)0L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = 
	    Qdefault_pane_background_color_or_tiling_pattern_rows;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = get_background_color_or_tiling_pattern();
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qicp_window_protocol_version;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = Latest_icp_window_protocol_version;
    M_CAR(gensymed_symbol_1) = car_new_value;
    varying_plist = gensymed_symbol;
    temp = copy_tree_using_gensym_conses_1(constant_plist);
    if (native_window_qm) {
	temp_1 = FIX(g2ext_x11_screen_depth(IFIX(native_window_qm)));
	temp_1 = gensym_list_4(Qwindow_screen_depth,temp_1,
		Qcharting_library_version_qm,charting_library_version_qm());
    }
    else
	temp_1 = Nil;
    result_1 = nconc2(temp,nconc2(varying_plist,nconc2(temp_1,
	    native_window_qm ? get_system_metrics_for_local_window() : Qnil)));
    return VALUES_1(result_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Node_id_for_uuid, Qnode_id_for_uuid);

DEFINE_VARIABLE_WITH_SYMBOL(Node_id_for_uuid_uses_ethernet_address_p, Qnode_id_for_uuid_uses_ethernet_address_p);

Object Extract_ethernet_script = UNBOUND;

static Object Qunix;               /* unix */

static Object list_constant_2;     /* # */

/* GET-ETHERNET-ADDRESS-IF-POSSIBLE */
Object get_ethernet_address_if_possible(uuid_machine_id)
    Object uuid_machine_id;
{
    Object string_1, temp, buffer, start, end_1;
    Object result;

    x_note_fn_call(37,90);
    if (EQ(G2_operating_system,Qunix)) {
	if (memq_function(G2_machine_type,list_constant_2)) {
	    string_1 = 
		    wide_string_to_gensym_string(get_local_machine_id_function());
	    temp = length(string_1);
	    result = VALUES_3(string_1,FIX((SI_Long)0L),temp);
	}
	else
	    result = get_ethernet_address_if_possible_for_unix();
	MVS_3(result,buffer,start,end_1);
	if (buffer) {
	    temp = extract_ethernet_address_from_string(buffer,start,end_1,
		    uuid_machine_id);
	    reclaim_gensym_string(buffer);
	    return VALUES_1(temp);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qhp9000s700;         /* hp9000s700 */

static Object string_constant_8;   /* "lanscan -a" */

static Object Qskip_two_characters;  /* skip-two-characters */

static Object Qalphaosf;           /* alphaosf */

static Object string_constant_9;   /* "netstat -i -I ln0 | grep '<Link>'" */

static Object Qextract_ethernet;   /* extract-ethernet */

static Object Qsgi;                /* sgi */

static Object string_constant_10;  /* "netstat -ia" */

static Object Qsparcsol;           /* sparcsol */

static Object string_constant_11;  /* "ndd /dev/arp arp_cache_report | grep PUBLISH" */

static Object Qintelsol;           /* intelsol */

static Object string_constant_12;  /* "~A | ~A" */

/* GET-ETHERNET-ADDRESS-IF-POSSIBLE-FOR-UNIX */
Object get_ethernet_address_if_possible_for_unix()
{
    Object command, type, successful_command_output_qm, number_of_characters;
    Object temp;
    Object result;

    x_note_fn_call(37,91);
    if (EQ(G2_machine_type,Qhp9000s700))
	result = VALUES_2(string_constant_8,Qskip_two_characters);
    else if (EQ(G2_machine_type,Qalphaosf))
	result = VALUES_2(string_constant_9,Qextract_ethernet);
    else if (EQ(G2_machine_type,Qsgi))
	result = VALUES_2(string_constant_10,Qextract_ethernet);
    else if (EQ(G2_machine_type,Qsparcsol))
	result = VALUES_2(string_constant_11,Qextract_ethernet);
    else if (EQ(G2_machine_type,Qintelsol))
	result = VALUES_2(string_constant_11,Qextract_ethernet);
    else
	result = VALUES_1(Qnil);
    MVS_2(result,command,type);
    if ( !TRUEP(command))
	return VALUES_1(Nil);
    if (EQ(type,Qextract_ethernet))
	command = tformat_gensym_string(3,string_constant_12,command,
		Extract_ethernet_script);
    successful_command_output_qm = unix_command_output_as_string(command);
    reclaim_gensym_string(command);
    if (successful_command_output_qm) {
	number_of_characters = lengthw(successful_command_output_qm);
	if ((SI_Long)12L <= IFIX(number_of_characters)) {
	    temp = wide_string_to_gensym_string(successful_command_output_qm);
	    reclaim_text_string(successful_command_output_qm);
	    return VALUES_3(temp,EQ(type,Qskip_two_characters) ? 
		    FIX((SI_Long)2L) : FIX((SI_Long)0L),number_of_characters);
	}
	else {
	    reclaim_text_string(successful_command_output_qm);
	    return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Result_index, Qresult_index);

/* EXTRACT-ETHERNET-ADDRESS-FROM-STRING */
Object extract_ethernet_address_from_string(buffer,start,end_1,result_1)
    Object buffer, start, end_1, result_1;
{
    Object result_index, temp, all_zeros_p, current_bit_count, char_1, digit;
    Object ab_loop_iter_flag_, incff_1_arg;
    SI_Long index_1, ab_loop_bind_, temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(37,92);
    result_index = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Result_index,Qresult_index,result_index,0);
    next_loop:
      if (IFIX(Result_index) >= (SI_Long)3L)
	  goto end_loop;
      temp = Result_index;
      UBYTE_16_ISASET_1(result_1,IFIX(temp),(SI_Long)0L);
      Result_index = FIXNUM_ADD1(Result_index);
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    all_zeros_p = T;
    result_index = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Result_index,Qresult_index,result_index,0);
      current_bit_count = FIX((SI_Long)0L);
      index_1 = IFIX(start);
      ab_loop_bind_ = IFIX(end_1);
      char_1 = Nil;
      digit = Nil;
      ab_loop_iter_flag_ = T;
    next_loop_1:
      if ( !(IFIX(Result_index) < (SI_Long)3L))
	  goto end_loop_1;
      if ( !TRUEP(ab_loop_iter_flag_))
	  index_1 = index_1 + (SI_Long)1L;
      if (index_1 >= ab_loop_bind_)
	  goto end_loop_1;
      char_1 = CHR(ICHAR(buffer,index_1));
      digit = digit_char_p(char_1,FIX((SI_Long)16L));
      if (digit) {
	  temp = Result_index;
	  incff_1_arg = ash(digit,current_bit_count);
	  temp_1 = UBYTE_16_ISAREF_1(result_1,IFIX(temp)) + IFIX(incff_1_arg);
	  UBYTE_16_ISASET_1(result_1,IFIX(temp),temp_1);
	  temp_1 = IFIX(current_bit_count) + (SI_Long)4L;
	  current_bit_count = FIX(temp_1);
	  if (IFIX(current_bit_count) == (SI_Long)16L) {
	      current_bit_count = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Result_index);
	      Result_index = temp;
	  }
	  if ( !((SI_Long)0L == IFIX(digit)))
	      all_zeros_p = Nil;
      }
      ab_loop_iter_flag_ = Nil;
      goto next_loop_1;
    end_loop_1:
      if ((SI_Long)3L == IFIX(Result_index) &&  !TRUEP(all_zeros_p))
	  result = VALUES_1(result_1);
      else
	  result = VALUES_1(Nil);
      goto end_2;
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

/* GET-NODE-ID-FOR-UUID-1 */
Object get_node_id_for_uuid_1()
{
    Object wide_string_bv16, uuid_machine_id, ethernet_address;
    Object machine_id_string, start_char, limit, aref_new_value_1;
    SI_Long bv16_length, temp, aref_new_value, length_1, machine_id_length;
    SI_Long index_1, temp_1, clump_size;

    x_note_fn_call(37,93);
    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)3L + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    temp = bv16_length - (SI_Long)2L;
    aref_new_value = (SI_Long)3L & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
    temp = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)3L,(SI_Long)0L);
    uuid_machine_id = wide_string_bv16;
    ethernet_address = get_ethernet_address_if_possible(uuid_machine_id);
    machine_id_string = ethernet_address;
    if (machine_id_string);
    else
	machine_id_string = get_local_machine_id_function();
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(machine_id_string));
    machine_id_length = UBYTE_16_ISAREF_1(machine_id_string,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(machine_id_string,length_1 
	    - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    if (machine_id_length <= (SI_Long)3L) {
	index_1 = (SI_Long)0L;
      next_loop:
	if (index_1 >= (SI_Long)3L)
	    goto end_loop;
	temp = index_1 < machine_id_length ? 
		UBYTE_16_ISAREF_1(machine_id_string,index_1) : (SI_Long)0L;
	UBYTE_16_ISASET_1(uuid_machine_id,index_1,temp);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else {
	temp_1 = machine_id_length / (SI_Long)3L;
	clump_size = temp_1;
	index_1 = (SI_Long)0L;
	start_char = Nil;
	limit = Nil;
      next_loop_1:
	if (index_1 >= (SI_Long)3L)
	    goto end_loop_1;
	start_char = FIX(index_1 * clump_size);
	limit = index_1 == (SI_Long)2L ? FIX(machine_id_length) : 
		FIX(IFIX(start_char) + clump_size);
	aref_new_value_1 = hash_wide_string_portion(machine_id_string,
		start_char,limit);
	UBYTE_16_ISASET_1(uuid_machine_id,index_1,IFIX(aref_new_value_1));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    Node_id_for_uuid_uses_ethernet_address_p =  ! !TRUEP(ethernet_address) 
	    ? T : Nil;
    Node_id_for_uuid = uuid_machine_id;
    return VALUES_1(Node_id_for_uuid);
}

DEFINE_VARIABLE_WITH_SYMBOL(Time_of_last_uuid, Qtime_of_last_uuid);

DEFINE_VARIABLE_WITH_SYMBOL(Always_use_current_time_for_uuid, Qalways_use_current_time_for_uuid);

DEFINE_VARIABLE_WITH_SYMBOL(Use_current_time_for_next_uuid, Quse_current_time_for_next_uuid);

DEFINE_VARIABLE_WITH_SYMBOL(Clock_sequence_for_uuid, Qclock_sequence_for_uuid);

static Object float_constant;      /* 262143.0 */

/* GET-CLOCK-SEQUENCE-FOR-UUID-1 */
Object get_clock_sequence_for_uuid_1()
{
    Object pid_low_bits;
    SI_Long unique_bits_for_uuid_clock_sequence, i, ab_loop_bind_;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(37,94);
    pid_low_bits = 
	    lfloor(mod(DOUBLE_TO_DOUBLE_FLOAT(g2ext_get_process_identifier()),
	    float_constant),_);
    unique_bits_for_uuid_clock_sequence = (SI_Long)8191L & IFIX(pid_low_bits);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(pid_low_bits) >>  -  - (SI_Long)13L;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    l_random(FIX((SI_Long)8192L),_);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    gensymed_symbol = Node_id_for_uuid_uses_ethernet_address_p ? 
	    (SI_Long)32768L : (SI_Long)57344L;
    gensymed_symbol_1 = IFIX(l_random(FIX((SI_Long)8192L),_)) ^ 
	    unique_bits_for_uuid_clock_sequence;
    return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
}

/* RESET-CLOCK-SEQUENCE-FOR-UUID */
Object reset_clock_sequence_for_uuid()
{
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(37,95);
    gensymed_symbol = Node_id_for_uuid_uses_ethernet_address_p ? 
	    (SI_Long)32768L : (SI_Long)57344L;
    gensymed_symbol_1 = (SI_Long)8191L & IFIX(add1(Clock_sequence_for_uuid));
    Clock_sequence_for_uuid = FIX(gensymed_symbol + gensymed_symbol_1);
    return VALUES_1(Clock_sequence_for_uuid);
}

DEFINE_VARIABLE_WITH_SYMBOL(Uuid_time_b0, Quuid_time_b0);

DEFINE_VARIABLE_WITH_SYMBOL(Uuid_time_b1, Quuid_time_b1);

DEFINE_VARIABLE_WITH_SYMBOL(Uuid_time_b2, Quuid_time_b2);

DEFINE_VARIABLE_WITH_SYMBOL(Uuid_time_b3, Quuid_time_b3);

/* GET-TIME-FOR-UUID-INTERNAL */
Object get_time_for_uuid_internal(time_managed_float)
    Object time_managed_float;
{
    Object time_b3, remainder_b3, time_b2, remainder_b2, time_b1, remainder_b1;
    Object time_b0, temp_1, temp_2, temp_3, temp_4;
    SI_Long time_b3_new_value;
    double current_unix_time, temp;
    Object result;

    x_note_fn_call(37,96);
    current_unix_time = DFLOAT_ISAREF_1(time_managed_float,(SI_Long)0L);
    result = lfloor(DOUBLE_TO_DOUBLE_FLOAT(current_unix_time * 
	    3.552713678800501E-8 + 0.11648675828473642),_);
    MVS_2(result,time_b3,remainder_b3);
    time_b3_new_value = IFIX(time_b3) + (SI_Long)4530L;
    time_b3 = FIX(time_b3_new_value);
    temp = DOUBLE_FLOAT_TO_DOUBLE(remainder_b3);
    result = lfloor(DOUBLE_TO_DOUBLE_FLOAT(temp * 65536.0),_);
    MVS_2(result,time_b2,remainder_b2);
    temp = DOUBLE_FLOAT_TO_DOUBLE(remainder_b2);
    result = lfloor(DOUBLE_TO_DOUBLE_FLOAT(temp * 65536.0),_);
    MVS_2(result,time_b1,remainder_b1);
    temp = DOUBLE_FLOAT_TO_DOUBLE(remainder_b1);
    time_b0 = lfloor(DOUBLE_TO_DOUBLE_FLOAT(temp * 65536.0),_);
    time_b0 = FIX(IFIX(time_b0) & (SI_Long)65280L);
    if (FIXNUM_EQ(Uuid_time_b3,time_b3) && FIXNUM_EQ(Uuid_time_b2,time_b2) 
	    && FIXNUM_EQ(Uuid_time_b1,time_b1) && FIXNUM_EQ(Uuid_time_b0,
	    time_b0)) {
	temp_1 = FIXNUM_ADD1(Uuid_time_b0);
	Uuid_time_b0 = temp_1;
	if (IFIX(Uuid_time_b0) == (SI_Long)65536L) {
	    Uuid_time_b0 = FIX((SI_Long)0L);
	    temp_1 = FIXNUM_ADD1(Uuid_time_b1);
	    Uuid_time_b1 = temp_1;
	    if (IFIX(Uuid_time_b1) == (SI_Long)65536L) {
		Uuid_time_b1 = FIX((SI_Long)0L);
		temp_1 = FIXNUM_ADD1(Uuid_time_b2);
		Uuid_time_b2 = temp_1;
		if (IFIX(Uuid_time_b2) == (SI_Long)65536L) {
		    Uuid_time_b2 = FIX((SI_Long)0L);
		    temp_1 = FIXNUM_ADD1(Uuid_time_b3);
		    Uuid_time_b3 = temp_1;
		    if (IFIX(Uuid_time_b3) == (SI_Long)65536L)
			Uuid_time_b3 = FIX((SI_Long)0L);
		}
	    }
	}
	return VALUES_4(Uuid_time_b3,Uuid_time_b2,Uuid_time_b1,Uuid_time_b0);
    }
    else {
	Uuid_time_b3 = time_b3;
	temp_2 = Uuid_time_b3;
	Uuid_time_b2 = time_b2;
	temp_3 = Uuid_time_b2;
	Uuid_time_b1 = time_b1;
	temp_4 = Uuid_time_b1;
	Uuid_time_b0 = time_b0;
	return VALUES_4(temp_2,temp_3,temp_4,Uuid_time_b0);
    }
}

static Object Qfloat_array;        /* float-array */

/* GET-TIME-FOR-UUID */
Object get_time_for_uuid()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    char temp_2;
    double last_unix_time, current_unix_time, arg, arg_1, uuid_unix_time;

    x_note_fn_call(37,97);
    if ( !TRUEP(Time_of_last_uuid)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    else {
		temp = Available_float_array_conses_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	Time_of_last_uuid = new_float;
    }
    last_unix_time = DFLOAT_ISAREF_1(Time_of_last_uuid,(SI_Long)0L);
    current_unix_time = 0.0;
    arg = 0.0;
    arg_1 = last_unix_time;
    temp_2 = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ?  
	    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    if (temp_2);
    else
	temp_2 = TRUEP(Always_use_current_time_for_uuid);
    if (temp_2);
    else
	temp_2 = TRUEP(Use_current_time_for_next_uuid);
    if (temp_2);
    else if (Check_time_on_next_uuid) {
	Check_time_on_next_uuid = Nil;
	c_native_clock_ticks_or_cache(Nil,Nil);
	current_unix_time = g2ext_unix_time_as_float();
	arg = current_unix_time - last_unix_time;
	arg_1 = 
		DOUBLE_FLOAT_TO_DOUBLE(Maximum_interval_between_new_time_for_uuid);
	temp_2 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2);
    else
	temp_2 = FIXNUM_EQ(FIXNUM_LOGAND(Uuid_offset_mask,Uuid_time_b0),
		Uuid_offset_mask);
    if (temp_2) {
	arg = 0.0;
	arg_1 = current_unix_time;
	uuid_unix_time = arg == arg_1 &&  !inline_nanp_for_comparison(arg) 
		&&  !inline_nanp_for_comparison(arg_1) ? 
		g2ext_unix_time_as_float() : current_unix_time;
    }
    else
	uuid_unix_time = last_unix_time;
    Use_current_time_for_next_uuid = Nil;
    arg = uuid_unix_time;
    arg_1 = last_unix_time;
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	temp = FIXNUM_ADD1(Uuid_time_b0);
	Uuid_time_b0 = temp;
	if (IFIX(Uuid_time_b0) == (SI_Long)65536L) {
	    Uuid_time_b0 = FIX((SI_Long)0L);
	    temp = FIXNUM_ADD1(Uuid_time_b1);
	    Uuid_time_b1 = temp;
	    if (IFIX(Uuid_time_b1) == (SI_Long)65536L) {
		Uuid_time_b1 = FIX((SI_Long)0L);
		temp = FIXNUM_ADD1(Uuid_time_b2);
		Uuid_time_b2 = temp;
		if (IFIX(Uuid_time_b2) == (SI_Long)65536L) {
		    Uuid_time_b2 = FIX((SI_Long)0L);
		    temp = FIXNUM_ADD1(Uuid_time_b3);
		    Uuid_time_b3 = temp;
		    if (IFIX(Uuid_time_b3) == (SI_Long)65536L)
			Uuid_time_b3 = FIX((SI_Long)0L);
		}
	    }
	}
	return VALUES_4(Uuid_time_b3,Uuid_time_b2,Uuid_time_b1,Uuid_time_b0);
    }
    else {
	arg = uuid_unix_time;
	arg_1 = last_unix_time;
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    reset_clock_sequence_for_uuid();
	temp = Time_of_last_uuid;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,uuid_unix_time);
	return get_time_for_uuid_internal(Time_of_last_uuid);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(User_notified_of_uuid_uniqueness_problem_p, Quser_notified_of_uuid_uniqueness_problem_p);

static Object string_constant_13;  /* "Unrecognized error code: " */

static Object string_constant_14;  /* "~a~a" */

static Object string_constant_15;  /* "" */

static Object string_constant_16;  /* "This computer's operating system cannot generate a universal unique ID (UUID).~
				    *               ~%~a"
				    */

/* GET-WIN32-UUID */
Object get_win32_uuid(uuid_string)
    Object uuid_string;
{
    Object code, message_string_qm, temp, message_string;

    x_note_fn_call(37,98);
    code = c_uuid_create(uuid_string);
    if (IFIX(code) == (SI_Long)0L)
	return VALUES_1(T);
    else {
	if ( !TRUEP(User_notified_of_uuid_uniqueness_problem_p)) {
	    if (FIXNUM_EQ(code,Rpc_s_uuid_local_only))
		message_string_qm = Rpc_s_uuid_local_only_message;
	    else if (FIXNUM_EQ(code,Rpc_s_uuid_no_address))
		message_string_qm = Rpc_s_uuid_no_address_message;
	    else
		message_string_qm = Qnil;
	    temp = message_string_qm;
	    if (temp);
	    else
		temp = string_constant_13;
	    message_string = tformat_text_string(3,string_constant_14,temp,
		    message_string_qm ? string_constant_15 : code);
	    notify_user_at_console_and_on_logbook(2,string_constant_16,
		    message_string);
	    User_notified_of_uuid_uniqueness_problem_p = T;
	    reclaim_text_string(message_string);
	}
	return VALUES_1(Nil);
    }
}

static Object Qintelnt;            /* intelnt */

static Object Qalphant;            /* alphant */

/* MAKE-UUID */
Object make_uuid()
{
    Object wide_string_bv16, uuid_string, b3, b2, b1, b0, machine_id_string;
    Object aref_new_value_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, index_1, length_1;
    Object result;

    x_note_fn_call(37,99);
    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)8L + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = (SI_Long)8L & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)8L,(SI_Long)0L);
    uuid_string = wide_string_bv16;
    if (EQ(G2_machine_type,Qintelnt) || EQ(G2_machine_type,Qalphant))
	get_win32_uuid(uuid_string);
    else {
	result = get_time_for_uuid();
	MVS_4(result,b3,b2,b1,b0);
	machine_id_string = Node_id_for_uuid;
	if (machine_id_string);
	else
	    machine_id_string = get_node_id_for_uuid_1();
	UBYTE_16_ISASET_1(uuid_string,(SI_Long)0L,IFIX(b0));
	UBYTE_16_ISASET_1(uuid_string,(SI_Long)1L,IFIX(b1));
	UBYTE_16_ISASET_1(uuid_string,(SI_Long)2L,IFIX(b2));
	UBYTE_16_ISASET_1(uuid_string,(SI_Long)3L,IFIX(b3));
	aref_new_value_1 = Clock_sequence_for_uuid;
	if (aref_new_value_1);
	else {
	    Clock_sequence_for_uuid = get_clock_sequence_for_uuid_1();
	    aref_new_value_1 = Clock_sequence_for_uuid;
	}
	UBYTE_16_ISASET_1(uuid_string,(SI_Long)4L,IFIX(aref_new_value_1));
	index_1 = (SI_Long)0L;
      next_loop:
	if (index_1 >= (SI_Long)3L)
	    goto end_loop;
	aref_arg_2 = index_1 + (SI_Long)5L;
	aref_new_value = UBYTE_16_ISAREF_1(machine_id_string,index_1);
	UBYTE_16_ISASET_1(uuid_string,aref_arg_2,aref_new_value);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(uuid_string));
    length_1 = UBYTE_16_ISAREF_1(uuid_string,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(uuid_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    UBYTE_16_ISASET_1(uuid_string,length_1,(SI_Long)1L);
    return VALUES_1(uuid_string);
}

/* TWRITE-UUID-PRINTED-REPRESENTATION */
Object twrite_uuid_printed_representation(uuid)
    Object uuid;
{
    Object temp;

    x_note_fn_call(37,100);
    temp = twrite_binary_string_printed_representation(uuid);
    return VALUES_1(temp);
}

static Object string_constant_17;  /* "000" */

static Object string_constant_18;  /* "00" */

static Object string_constant_19;  /* "0" */

/* TWRITE-BINARY-STRING-PRINTED-REPRESENTATION */
Object twrite_binary_string_printed_representation(binary_string)
    Object binary_string;
{
    Object write_strings_parsably_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object character_code, string_1, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(6);

    x_note_fn_call(37,101);
    write_strings_parsably_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
	    5);
      current_wide_string_list = Qdo_not_use;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	      4);
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	current_wide_string = wide_string_bv16;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		3);
	  fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		  2);
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	    total_length_of_current_wide_string = 
		    FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		    (SI_Long)16L));
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		    1);
	      current_twriting_output_type = Qwide_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		i = (SI_Long)0L;
		ab_loop_bind_ = IFIX(lengthw(binary_string));
		character_code = Nil;
	      next_loop:
		if (i >= ab_loop_bind_)
		    goto end_loop;
		character_code = FIX(UBYTE_16_ISAREF_1(binary_string,i));
		twrite_general_string(IFIX(character_code) <= (SI_Long)15L 
			? string_constant_17 : IFIX(character_code) <= 
			(SI_Long)255L ? string_constant_18 : 
			IFIX(character_code) <= (SI_Long)4095L ? 
			string_constant_19 : string_constant_15);
		twrite_positive_fixnum_in_radix(character_code,
			FIX((SI_Long)16L));
		i = i + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
		string_1 = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      downcase_text_string_in_place(string_1);
      twrite_general_string(string_1);
      temp = reclaim_text_string(string_1);
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* HASH-WIDE-STRING-PORTION */
Object hash_wide_string_portion(wide_string,start_init,end_init)
    Object wide_string, start_init, end_init;
{
    Object temp;
    SI_Long start, end_1, hash, index_1, ab_loop_bind_, char_code_1;

    x_note_fn_call(37,102);
    start = IFIX(start_init);
    end_1 = IFIX(end_init);
    if (start == end_1)
	temp = FIX((SI_Long)0L);
    else if (start == end_1 - (SI_Long)1L)
	temp = FIX(UBYTE_16_ISAREF_1(wide_string,start));
    else {
	hash = UBYTE_16_ISAREF_1(wide_string,start);
	index_1 = start + (SI_Long)1L;
	ab_loop_bind_ = end_1;
	char_code_1 = (SI_Long)0L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	char_code_1 = UBYTE_16_ISAREF_1(wide_string,index_1);
	hash = (hash << (SI_Long)1L & (SI_Long)65535L) + (hash >>  -  - 
		(SI_Long)15L) ^ char_code_1;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = FIX(hash);
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    return VALUES_1(temp);
}

void platforms_INIT()
{
    Object named_dynamic_extent_description, color, r, g, b, ab_loop_list_, c;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp;
    Object reclaim_structure_for_workstation_1;
    Object reclaim_structure_for_local_event_1, cdddr_arg, cdddr_new_value;
    Object AB_package, Qplatforms, Qalphavms, Qvax, string_constant_52;
    Object list_constant_12, Qdefault_workspace_area_foreground_color;
    Object Qdefault_workspace_area_background_color, Quse_xor_for_addition_qm;
    Object Qmaximum_scale, Qminimum_scale, Qblack, Qdefault_image_border_color;
    Object Qdefault_image_border_width, Qpane_borders_color;
    Object Qdefault_minimum_height_for_pane, Qdefault_minimum_width_for_pane;
    Object Qwidth_of_space_between_panes, Qminimum_line_height_of_text_to_draw;
    Object Qbits_per_pixel, Qallow_panic_messages_qm;
    Object Qallow_user_notifications_qm, list_constant_11, Qpane_layout;
    Object list_constant_10, Qimage_plane_scroll_bar_rail_color;
    Object Qimage_plane_scroll_bar_rail_width;
    Object Qimage_plane_scroll_bar_background_color;
    Object Qimage_plane_scroll_bar_width, Qimage_plane_hide_button_position;
    Object Qimage_plane_hide_button_height, Qimage_plane_hide_button_width;
    Object Qimage_plane_hide_button_color;
    Object Qimage_plane_title_baseline_position, list_constant_9;
    Object Qimage_plane_title_font_map, Qimage_plane_title_color;
    Object Qimage_plane_top_bar_width, Qimage_plane_border_color;
    Object Qimage_plane_minimum_border_width;
    Object Qimage_plane_border_outline_width, Qx11_pixmap;
    Object Qstored_raster_type_for_window, Qscratchpad_raster_type_for_window;
    Object Qx11_window, Qtype_of_gensym_window;
    Object Qimage_plane_scroll_bar_thumb_color;
    Object Qimage_plane_scroll_bar_thumb_width, Qhm18, Qdetail_pane;
    Object Qicp_window_protocol_supports_set_background_color;
    Object Qicp_window_protocol_supports_grid_view_delimiter_fix;
    Object Qicp_window_protocol_supports_tabular_view_selection_changed_events;
    Object Qicp_window_protocol_supports_choose_directory_on_server;
    Object Qicp_window_protocol_supports_views_in_listbars;
    Object Qicp_window_protocol_supports_tabular_views;
    Object Qicp_window_protocol_supports_choose_directory;
    Object Qicp_window_protocol_supports_manage_status_bar_ex;
    Object Qicp_window_protocol_supports_nip_rescale_window;
    Object Qicp_window_protocol_supports_native_editor_ex;
    Object Qicp_window_protocol_supports_incremental_editor_updates;
    Object Qicp_window_protocol_supports_chart_views_in_panes;
    Object Qicp_window_protocol_supports_append_control_ex;
    Object Qicp_window_protocol_supports_property_grid;
    Object Qicp_window_protocol_supports_extended_dialog_text_boxes;
    Object Qicp_window_protocol_supports_hide_toolbar;
    Object Qicp_window_protocol_supports_views_in_dialogs;
    Object Qicp_window_protocol_supports_modify_node;
    Object Qicp_window_protocol_supports_manage_dialog;
    Object Qicp_window_protocol_supports_tabbed_mdi_mode;
    Object Qicp_window_protocol_supports_grid_view_small_chunks;
    Object Qicp_window_protocol_supports_manage_logbook;
    Object Qicp_window_protocol_supports_manage_ui_properties;
    Object Qicp_window_protocol_supports_html_help_ex;
    Object Qicp_window_protocol_supports_views_api;
    Object Qicp_window_protocol_supports_tree_views_ex;
    Object Qicp_window_protocol_supports_simple_dialog_ex;
    Object Qicp_window_protocol_supports_toolbar_docking;
    Object Qicp_window_protocol_supports_nms_set_theme;
    Object Qicp_window_protocol_supports_scroll_while_minimized_fix;
    Object Qicp_window_protocol_supports_manage_pane;
    Object Qicp_window_protocol_supports_new_grid_views;
    Object Qicp_window_protocol_supports_dialog_panes;
    Object Qicp_window_protocol_supports_zorder_native_window;
    Object Qicp_window_protocol_supports_tabular_view_selected_rows;
    Object Qicp_window_protocol_supports_grid_views;
    Object Qicp_window_protocol_supports_chart_views;
    Object Qicp_window_protocol_supports_polyarcs;
    Object Qicp_window_protocol_supports_shortcut_bars;
    Object Qicp_window_protocol_supports_nms_unposting_callbacks;
    Object Qicp_window_protocol_supports_native_printing_ex;
    Object Qicp_window_protocol_supports_native_editor;
    Object Qicp_window_protocol_supports_debugger_dialog;
    Object Qicp_window_protocol_supports_html_views;
    Object Qicp_window_protocol_supports_tree_views;
    Object Qicp_window_protocol_supports_file_dialog_ex;
    Object Qicp_window_protocol_supports_nms_selection_callbacks;
    Object Qicp_window_protocol_supports_manage_status_bar;
    Object Qicp_window_protocol_supports_nms_modify_control;
    Object Qicp_window_protocol_supports_set_window_title;
    Object Qicp_window_protocol_supports_list_directory;
    Object Qicp_window_protocol_supports_nms_controls;
    Object Qicp_window_protocol_supports_custom_dialogs;
    Object Qicp_window_protocol_supports_mdi, list_constant_4;
    Object Qnamed_dynamic_extent_description, Qunwind_qm, string_constant_51;
    Object Qtelestubs, string_constant_50, Qnative_window_polling_interval;
    Object Qnative_window_polling_interval_fast;
    Object Qnative_window_polling_interval_default, array_constant_8;
    Object Qendscroll, Qbottom, Qtop, Qthumbtrack, Qthumbposition, Qpagedown;
    Object Qpageup, Qlinedown, Qlineup, list_constant_8;
    Object Qlocal_reshape_event_queue, Qlocal_event_queue, Qmake_queue;
    Object Kfuncall, Qlocal_event, Qreclaim_structure;
    Object Qoutstanding_local_event_count, Qlocal_event_structure_memory_usage;
    Object Qutilities2, string_constant_49, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_48, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qworkstation;
    Object Qoutstanding_workstation_count, Qworkstation_structure_memory_usage;
    Object string_constant_47, string_constant_46;
    Object Qmaximum_polygon_coordinates, list_constant_7, list_constant_6;
    Object list_constant_5, string_constant_45, string_constant_44;
    Object string_constant_39, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_38;
    Object string_constant_37, string_constant_36, string_constant_35;
    Object list_constant_3, Qdark_gray, Qgray, Qlight_gray, Qbrown, Qpurple;
    Object Qblue, Qgreen, Qyellow, Qorange, Qred, string_constant_34;
    Object string_constant_33, string_constant_32, string_constant_31;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object string_constant_27, string_constant_26, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, Qlast_session_id_for_g2;
    Object Qworkstations_in_service, string_constant_20;

    x_note_fn_call(37,103);
    SET_PACKAGE("AB");
    string_constant_20 = STATIC_STRING("SERVICE-WORKSTATIONS");
    if (Service_workstations == UNBOUND)
	Service_workstations = make_recursive_lock(2,Kname,string_constant_20);
    AB_package = STATIC_PACKAGE("AB");
    Qservice_workstations = STATIC_SYMBOL("SERVICE-WORKSTATIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qservice_workstations,Service_workstations);
    Qplatforms = STATIC_SYMBOL("PLATFORMS",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qservice_workstations,
	    Qplatforms,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qservice_workstations,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qworkstations_in_service = STATIC_SYMBOL("WORKSTATIONS-IN-SERVICE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkstations_in_service,
	    Workstations_in_service);
    record_system_variable(Qworkstations_in_service,Qplatforms,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qlast_workstation_serviced = STATIC_SYMBOL("LAST-WORKSTATION-SERVICED",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_workstation_serviced,
	    Last_workstation_serviced);
    record_system_variable(Qlast_workstation_serviced,Qplatforms,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qlast_session_id_for_g2 = STATIC_SYMBOL("LAST-SESSION-ID-FOR-G2",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_session_id_for_g2,Last_session_id_for_g2);
    record_system_variable(Qlast_session_id_for_g2,Qplatforms,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    string_constant_21 = 
	    STATIC_STRING("13xy1o83piy3-xy3=xy3=Gy1o83fykkk1o83qeykk3=xy1o83r3y3*Xy3cy3cy1o83rUy3-Ry3*Qy3*Sy1o832xy3=xy3-xy3-Cy1o83tJyk3=xy3=xy1q83-Ry3*+y3");
    string_constant_22 = 
	    STATIC_STRING("*+y3*+y83-Piy8k1o832Vy3-4y3vy3*7y1p838Ay3-by3-by3-by83-RKy1o83wdy3Uy3*7y3Uy1o83--By3=xy3=Jyk1o83--Cy3=My3*Xy3Sy1p83*Gy3*by3*by3*");
    string_constant_23 = 
	    STATIC_STRING("by83-XDy1o839+yk3=xyk1o83--Zy3*fy3=xy3hy1o83-=Sy3=9y3-Oy3-Oy1o83-1ey3=iy3=Yy3*8y1o83-2=y3*fy3=Ky3=Yy1p83-Wy3=Fy3=Fy3=Fy83-ccy1o8");
    string_constant_24 = 
	    STATIC_STRING("3-24y3ky3=9y3ky1o83-2gy3=xyk3=xy1o83-6Qy3*+ykk1o83-6Yy3-Yy3=9y3*cy1o83-6Zykk3=9y1o83-6ay3=cy3=cy3*fy1o83-6by3*sy3-Hy3=Fy1o83-8Cy");
    string_constant_25 = 
	    STATIC_STRING("3=xy3*Xyk1o839ey3*Ky3=ty3*Ky1o83-8ry3=xy3=+y3=7y1o83-91y3=Py3*Sy3=Py1q83-9dy3*+yk3*+y08k1o83m3y3=xykk1o83-C9y3=sy3*+y3-ky1o83-Cm");
    string_constant_26 = 
	    STATIC_STRING("y3*Sy3-Ey3fy1o83-D5y3*3y3=Ay3=dy1o83-D6y3-cy3-My3=9y1o9k3=Ey3*my3*8y1o83-Ety3=Ky3*xy3=Ky1o83-FMy3-+y3=Sy3=Cy1o83-GUy3=gy3**y3=gy");
    string_constant_27 = 
	    STATIC_STRING("1o83-GVy3=8y3ky3*Ly1o83-Ghy3=ny3=Qy3*ly1o83*2y3=xy3=xy3=xy1o83AYy3=xy3=xyk1r83-gy3=ny3=ny3=ny83-x4y08k1r83wSy3=xy3=sy3=iy008k1r8");
    string_constant_28 = 
	    STATIC_STRING("3-2Ey3=sy3=iy3=Yy008k1r83phy3=sy3=dy3=Jy008k1r83-02y3=xy3=xy3=iy008k1r83q7y3=iy3=xy3=xy008k1r83-1sy3=Yy3=Yy3=sy008k1r839Hy3*iy3=");
    string_constant_29 = 
	    STATIC_STRING("0y3=Qy008k1r83-98y3*iy3=Sy3=Yy008k1r83-8ay3*hy3=gy3=gy008k1r83-20y3=Sy3=xy3=xy008k1r83-8Zy3=gy3=ay3*cy008k1r83-22y3=sy3=sy3=Ey00");
    string_constant_30 = 
	    STATIC_STRING("8k1r83-23y3=xy3=xy3=Sy008k1r83-21y3=gy3=Py3**y008k1r83qUy3=ny3=ny3=Oy008k1r839Gy3=xy3*oy3=-y008k1r8334y3=Xy3=Xy3=Xy83-Tdy08k");
    if (Standard_gensym_color_alist == UNBOUND) {
	clear_optimized_constants();
	push_optimized_constant(Qtan);
	Standard_gensym_color_alist = 
		regenerate_optimized_constant(list(10,string_constant_21,
		string_constant_22,string_constant_23,string_constant_24,
		string_constant_25,string_constant_26,string_constant_27,
		string_constant_28,string_constant_29,string_constant_30));
    }
    color = Nil;
    r = Nil;
    g = Nil;
    b = Nil;
    ab_loop_list_ = Standard_gensym_color_alist;
    c = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    r = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    g = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    b = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    c = rgb2gray(r,g,b);
    ab_loopvar__2 = LIST_1(LIST_4(color,c,c,c));
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    Gray_gensym_color_alist = ab_loopvar_;
    goto end_1;
    Gray_gensym_color_alist = Qnil;
  end_1:;
    string_constant_31 = 
	    STATIC_STRING("1n83Epy1n83fy1n83m3y1n83-8Cy1o83--By83-1ey83-Cmy9k832xy1n83r3y1o83-2gy83-Ety83-GVy83-8ry1n83-6Qy83-C9y83-=Sy1o83qey1o83-9dy1n83-");
    string_constant_32 = 
	    STATIC_STRING("2=y83-6Zy83-D5y1n83rUy83-D6y832Vy1n83-GUy83-6by83-91y83*Gy1m83-Ry838Ay13Fy83*2y1n83AYy1p83--Cy83-Ghy83-22y83-23y83-21y83-6ay1n83");
    string_constant_33 = 
	    STATIC_STRING("9+y1o839ey83-24y83--Zy83tJy1o83wdy83-6Yy83piy83-FMy83-Wy8334y83-gy83wSy83-2Ey83phy83-02y83q7y83-1sy839Hy83-98y83-8ay83-20y83-8Zy");
    string_constant_34 = STATIC_STRING("83qUy839Gy");
    if (Color_hierarchy == UNBOUND) {
	clear_optimized_constants();
	push_optimized_constant(Qtan);
	Color_hierarchy = 
		regenerate_optimized_constant(LIST_4(string_constant_31,
		string_constant_32,string_constant_33,string_constant_34));
    }
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qred = STATIC_SYMBOL("RED",AB_package);
    Qorange = STATIC_SYMBOL("ORANGE",AB_package);
    Qyellow = STATIC_SYMBOL("YELLOW",AB_package);
    Qgreen = STATIC_SYMBOL("GREEN",AB_package);
    Qblue = STATIC_SYMBOL("BLUE",AB_package);
    Qpurple = STATIC_SYMBOL("PURPLE",AB_package);
    Qbrown = STATIC_SYMBOL("BROWN",AB_package);
    Qlight_gray = STATIC_SYMBOL("LIGHT-GRAY",AB_package);
    Qgray = STATIC_SYMBOL("GRAY",AB_package);
    Qdark_gray = STATIC_SYMBOL("DARK-GRAY",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)12L,Qblack,Qwhite,Qred,Qorange,
	    Qyellow,Qgreen,Qblue,Qpurple,Qbrown,Qlight_gray,Qgray,Qdark_gray);
    Standard_gensym_color_subset = list_constant_3;
    if (Native_window_notices_enter_and_leave_events_p == UNBOUND)
	Native_window_notices_enter_and_leave_events_p = Nil;
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    No_local_window_p_cached = Nil;
    array_constant_1 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Maximum_x11_cut_buffer_length = FIX((SI_Long)32768L);
    Qx_cut_buffer = STATIC_SYMBOL("X-CUT-BUFFER",AB_package);
    Qx_string = STATIC_SYMBOL("X-STRING",AB_package);
    Qcf_text = STATIC_SYMBOL("CF-TEXT",AB_package);
    Qx_compound_text_string = STATIC_SYMBOL("X-COMPOUND-TEXT-STRING",
	    AB_package);
    Qunicode = STATIC_SYMBOL("UNICODE",AB_package);
    Qcf_unicode_text = STATIC_SYMBOL("CF-UNICODE-TEXT",AB_package);
    Qiso_8859_1_gensym_string = STATIC_SYMBOL("ISO-8859-1-GENSYM-STRING",
	    AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    if (X11_preinitialized_p == UNBOUND)
	X11_preinitialized_p = Nil;
    if (Cached_local_gensym_x11_display == UNBOUND)
	Cached_local_gensym_x11_display = Nil;
    string_constant = STATIC_STRING("DISPLAY");
    string_constant_1 = STATIC_STRING(":0");
    array_constant_4 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    Qx = STATIC_SYMBOL("X",AB_package);
    Qy = STATIC_SYMBOL("Y",AB_package);
    string_constant_37 = STATIC_STRING("x-res");
    string_constant_38 = STATIC_STRING("x-resolution");
    string_constant_2 = STATIC_STRING("res");
    string_constant_39 = STATIC_STRING("resolution");
    string_constant_40 = STATIC_STRING("x-mag");
    string_constant_41 = STATIC_STRING("x-magnification");
    string_constant_35 = STATIC_STRING("mag");
    string_constant_36 = STATIC_STRING("magnification");
    list_constant_5 = STATIC_LIST((SI_Long)2L,string_constant_35,
	    string_constant_36);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)7L,string_constant_37,
	    string_constant_38,string_constant_2,string_constant_39,
	    string_constant_40,string_constant_41,list_constant_5);
    string_constant_42 = STATIC_STRING("y-res");
    string_constant_43 = STATIC_STRING("y-resolution");
    string_constant_44 = STATIC_STRING("y-mag");
    string_constant_45 = STATIC_STRING("y-magnification");
    list_constant_7 = STATIC_LIST_STAR((SI_Long)7L,string_constant_42,
	    string_constant_43,string_constant_2,string_constant_39,
	    string_constant_44,string_constant_45,list_constant_5);
    list_constant = STATIC_LIST((SI_Long)4L,Qx,list_constant_6,Qy,
	    list_constant_7);
    string_constant_3 = STATIC_STRING("(none)");
    string_constant_4 = 
	    STATIC_STRING("~%Illegal ~a arg: ~a; it must be an integer ~\n                         between ~a and ~a (expressing dots per inch).~%");
    string_constant_5 = 
	    STATIC_STRING("~%Illegal ~a arg: ~a; it must be a number ~\n                         between ~f and ~f (expressing a magnification factor).~%");
    if (Do_not_error_in_x11_create_pixmap_on_failed_allocation == UNBOUND)
	Do_not_error_in_x11_create_pixmap_on_failed_allocation = Nil;
    Qmaximum_polygon_coordinates = 
	    STATIC_SYMBOL("MAXIMUM-POLYGON-COORDINATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_polygon_coordinates,
	    Maximum_polygon_coordinates);
    SET_SYMBOL_VALUE(Qmaximum_polygon_coordinates,
	    FIX(IFIX(Maximum_polygon_points) * (SI_Long)2L));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_workstation_g2_struct = 
	    STATIC_SYMBOL("WORKSTATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qworkstation = STATIC_SYMBOL("WORKSTATION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_workstation_g2_struct,
	    Qworkstation,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qworkstation,
	    Qg2_defstruct_structure_name_workstation_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_workstation == UNBOUND)
	The_type_description_of_workstation = Nil;
    string_constant_46 = 
	    STATIC_STRING("43Dy8m83oey1n83oey8n8k1l8n0000001n1m83My83-BKy1m83=0y83-9Ey1n8y83-6My1l83-Guyk3qyk0k0");
    temp = The_type_description_of_workstation;
    The_type_description_of_workstation = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_46));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_workstation_g2_struct,
	    The_type_description_of_workstation,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qworkstation,
	    The_type_description_of_workstation,Qtype_description_of_type);
    Qoutstanding_workstation_count = 
	    STATIC_SYMBOL("OUTSTANDING-WORKSTATION-COUNT",AB_package);
    Qworkstation_structure_memory_usage = 
	    STATIC_SYMBOL("WORKSTATION-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_47 = STATIC_STRING("1q83oey8s83-xdy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_workstation_count);
    push_optimized_constant(Qworkstation_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_47));
    Qchain_of_available_workstations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-WORKSTATIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_workstations,
	    Chain_of_available_workstations);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_workstations,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qworkstation_count = STATIC_SYMBOL("WORKSTATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkstation_count,Workstation_count);
    record_system_variable(Qworkstation_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_workstations_vector == UNBOUND)
	Chain_of_available_workstations_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qworkstation_structure_memory_usage,
	    STATIC_FUNCTION(workstation_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_workstation_count,
	    STATIC_FUNCTION(outstanding_workstation_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_workstation_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_workstation,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qworkstation,
	    reclaim_structure_for_workstation_1);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    Qlogged_out = STATIC_SYMBOL("LOGGED-OUT",AB_package);
    Qg2_defstruct_structure_name_local_event_g2_struct = 
	    STATIC_SYMBOL("LOCAL-EVENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlocal_event = STATIC_SYMBOL("LOCAL-EVENT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_local_event_g2_struct,
	    Qlocal_event,Qab_name_of_unique_structure_type);
    mutate_global_property(Qlocal_event,
	    Qg2_defstruct_structure_name_local_event_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_local_event == UNBOUND)
	The_type_description_of_local_event = Nil;
    string_constant_48 = 
	    STATIC_STRING("43Dy8m83kYy1n83kYy8n8k1l8n0000001m1m83My83-Aey1m83=0y83-9Byksk0k0");
    temp = The_type_description_of_local_event;
    The_type_description_of_local_event = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_48));
    mutate_global_property(Qg2_defstruct_structure_name_local_event_g2_struct,
	    The_type_description_of_local_event,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qlocal_event,
	    The_type_description_of_local_event,Qtype_description_of_type);
    Qoutstanding_local_event_count = 
	    STATIC_SYMBOL("OUTSTANDING-LOCAL-EVENT-COUNT",AB_package);
    Qlocal_event_structure_memory_usage = 
	    STATIC_SYMBOL("LOCAL-EVENT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_49 = STATIC_STRING("1q83kYy8s83-d3y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_local_event_count);
    push_optimized_constant(Qlocal_event_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_49));
    Qchain_of_available_local_events = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LOCAL-EVENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_local_events,
	    Chain_of_available_local_events);
    record_system_variable(Qchain_of_available_local_events,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qlocal_event_count = STATIC_SYMBOL("LOCAL-EVENT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlocal_event_count,Local_event_count);
    record_system_variable(Qlocal_event_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_local_events_vector == UNBOUND)
	Chain_of_available_local_events_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qlocal_event_structure_memory_usage,
	    STATIC_FUNCTION(local_event_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_local_event_count,
	    STATIC_FUNCTION(outstanding_local_event_count,NIL,FALSE,0,0));
    reclaim_structure_for_local_event_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_local_event,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qlocal_event,
	    reclaim_structure_for_local_event_1);
    Qlocal_event_queue = STATIC_SYMBOL("LOCAL-EVENT-QUEUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlocal_event_queue,Local_event_queue);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_queue = STATIC_SYMBOL("MAKE-QUEUE",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_queue,STATIC_FUNCTION(make_queue,NIL,FALSE,0,0));
    list_constant_8 = STATIC_LIST((SI_Long)2L,Kfuncall,Qmake_queue);
    record_system_variable(Qlocal_event_queue,Qplatforms,list_constant_8,
	    Qnil,Qt,Qnil,Qnil);
    Qlocal_reshape_event_queue = STATIC_SYMBOL("LOCAL-RESHAPE-EVENT-QUEUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlocal_reshape_event_queue,
	    Local_reshape_event_queue);
    record_system_variable(Qlocal_reshape_event_queue,Qplatforms,
	    list_constant_8,Qnil,Qnil,Qnil,Qnil);
    Qwindow = STATIC_SYMBOL("WINDOW",AB_package);
    Qcheck_shape_of_window_without_lookahead = 
	    STATIC_SYMBOL("CHECK-SHAPE-OF-WINDOW-WITHOUT-LOOKAHEAD",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcheck_shape_of_window_without_lookahead,
	    STATIC_FUNCTION(check_shape_of_window_without_lookahead,NIL,
	    FALSE,2,2));
    Fixnum_time_interval_for_automatic_xsync = FIX((SI_Long)1L * 
	    IFIX(Fixnum_time_units_per_second));
    if (Fixnum_time_of_last_xsync == UNBOUND)
	Fixnum_time_of_last_xsync = FIX((SI_Long)0L);
    array_constant_8 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)9L));
    Qlineup = STATIC_SYMBOL("LINEUP",AB_package);
    Qlinedown = STATIC_SYMBOL("LINEDOWN",AB_package);
    Qpageup = STATIC_SYMBOL("PAGEUP",AB_package);
    Qpagedown = STATIC_SYMBOL("PAGEDOWN",AB_package);
    Qthumbposition = STATIC_SYMBOL("THUMBPOSITION",AB_package);
    Qthumbtrack = STATIC_SYMBOL("THUMBTRACK",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qendscroll = STATIC_SYMBOL("ENDSCROLL",AB_package);
    ISASET_1(array_constant_8,(SI_Long)0L,Qlineup);
    ISASET_1(array_constant_8,(SI_Long)1L,Qlinedown);
    ISASET_1(array_constant_8,(SI_Long)2L,Qpageup);
    ISASET_1(array_constant_8,(SI_Long)3L,Qpagedown);
    ISASET_1(array_constant_8,(SI_Long)4L,Qthumbposition);
    ISASET_1(array_constant_8,(SI_Long)5L,Qthumbtrack);
    ISASET_1(array_constant_8,(SI_Long)6L,Qtop);
    ISASET_1(array_constant_8,(SI_Long)7L,Qbottom);
    ISASET_1(array_constant_8,(SI_Long)8L,Qendscroll);
    Scrollbar_code_names = array_constant_8;
    Qroot = STATIC_SYMBOL("ROOT",AB_package);
    Qab_directory = STATIC_SYMBOL("DIRECTORY",AB_package);
    Qhscroll = STATIC_SYMBOL("HSCROLL",AB_package);
    Qvscroll = STATIC_SYMBOL("VSCROLL",AB_package);
    Qcode = STATIC_SYMBOL("CODE",AB_package);
    Qthumb = STATIC_SYMBOL("THUMB",AB_package);
    Qid = STATIC_SYMBOL("ID",AB_package);
    Qmenu_choice = STATIC_SYMBOL("MENU-CHOICE",AB_package);
    Qchoice = STATIC_SYMBOL("CHOICE",AB_package);
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    Qmenu_bar = STATIC_SYMBOL("MENU-BAR",AB_package);
    Qdialog_update = STATIC_SYMBOL("DIALOG-UPDATE",AB_package);
    Qdialog_id = STATIC_SYMBOL("DIALOG-ID",AB_package);
    Qcontrol_id = STATIC_SYMBOL("CONTROL-ID",AB_package);
    Qinitiator = STATIC_SYMBOL("INITIATOR",AB_package);
    Qnew_value = STATIC_SYMBOL("NEW-VALUE",AB_package);
    Qdialog_dismissed = STATIC_SYMBOL("DIALOG-DISMISSED",AB_package);
    Qdialog_response_code = STATIC_SYMBOL("DIALOG-RESPONSE-CODE",AB_package);
    Qdialog_miscellaneous_communication = 
	    STATIC_SYMBOL("DIALOG-MISCELLANEOUS-COMMUNICATION",AB_package);
    Qmessage_type = STATIC_SYMBOL("MESSAGE-TYPE",AB_package);
    Qinfo = STATIC_SYMBOL("INFO",AB_package);
    Qdialog_user_gesture = STATIC_SYMBOL("DIALOG-USER-GESTURE",AB_package);
    Qkey = STATIC_SYMBOL("KEY",AB_package);
    Qrow = STATIC_SYMBOL("ROW",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrow,Row);
    Qcolumn = STATIC_SYMBOL("COLUMN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcolumn,Column);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qnms_menu_posted = STATIC_SYMBOL("NMS-MENU-POSTED",AB_package);
    Qnms_menu_handle = STATIC_SYMBOL("NMS-MENU-HANDLE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qnms_menu_unposted = STATIC_SYMBOL("NMS-MENU-UNPOSTED",AB_package);
    Qnms_menu_item_selected = STATIC_SYMBOL("NMS-MENU-ITEM-SELECTED",
	    AB_package);
    Qprevious_nms_menu_handle = STATIC_SYMBOL("PREVIOUS-NMS-MENU-HANDLE",
	    AB_package);
    Qprevious_item = STATIC_SYMBOL("PREVIOUS-ITEM",AB_package);
    Qnms_control = STATIC_SYMBOL("NMS-CONTROL",AB_package);
    Qselection = STATIC_SYMBOL("SELECTION",AB_package);
    Qtree_view = STATIC_SYMBOL("TREE-VIEW",AB_package);
    Qhandle = STATIC_SYMBOL("HANDLE",AB_package);
    Qevent = STATIC_SYMBOL("EVENT",AB_package);
    Qprop_grid = STATIC_SYMBOL("PROP-GRID",AB_package);
    Qivalue = STATIC_SYMBOL("IVALUE",AB_package);
    Qgrid_view = STATIC_SYMBOL("GRID-VIEW",AB_package);
    Qtabular_view = STATIC_SYMBOL("TABULAR-VIEW",AB_package);
    Qchart_view = STATIC_SYMBOL("CHART-VIEW",AB_package);
    Qshortcut_bar = STATIC_SYMBOL("SHORTCUT-BAR",AB_package);
    Qdrag_to = STATIC_SYMBOL("DRAG-TO",AB_package);
    Qfolder = STATIC_SYMBOL("FOLDER",AB_package);
    Qhtml_view = STATIC_SYMBOL("HTML-VIEW",AB_package);
    Qlogbook_view = STATIC_SYMBOL("LOGBOOK-VIEW",AB_package);
    Qmsg = STATIC_SYMBOL("MSG",AB_package);
    Qstatus_bar = STATIC_SYMBOL("STATUS-BAR",AB_package);
    Qpane = STATIC_SYMBOL("PANE",AB_package);
    Qbits = STATIC_SYMBOL("BITS",AB_package);
    Qdebugger_dialog = STATIC_SYMBOL("DEBUGGER-DIALOG",AB_package);
    Qopcode = STATIC_SYMBOL("OPCODE",AB_package);
    Qline = STATIC_SYMBOL("LINE",AB_package);
    Qeditor = STATIC_SYMBOL("EDITOR",AB_package);
    Qcaret = STATIC_SYMBOL("CARET",AB_package);
    Qend = STATIC_SYMBOL("END",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qlist_directory = STATIC_SYMBOL("LIST-DIRECTORY",AB_package);
    Qwindow_refresh = STATIC_SYMBOL("WINDOW-REFRESH",AB_package);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    Qwindow_moved = STATIC_SYMBOL("WINDOW-MOVED",AB_package);
    Qstatus = STATIC_SYMBOL("STATUS",AB_package);
    Qwindow_sized = STATIC_SYMBOL("WINDOW-SIZED",AB_package);
    Qnative_window_polling_interval_default = 
	    STATIC_SYMBOL("NATIVE-WINDOW-POLLING-INTERVAL-DEFAULT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnative_window_polling_interval_default,
	    Native_window_polling_interval_default);
    record_system_variable(Qnative_window_polling_interval_default,
	    Qplatforms,FIX((SI_Long)3600000L),Qnil,Qnil,Qnil,Qnil);
    Qnative_window_polling_interval_fast = 
	    STATIC_SYMBOL("NATIVE-WINDOW-POLLING-INTERVAL-FAST",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnative_window_polling_interval_fast,
	    Native_window_polling_interval_fast);
    record_system_variable(Qnative_window_polling_interval_fast,Qplatforms,
	    FIX((SI_Long)250L),Qnil,Qnil,Qnil,Qnil);
    Qnative_window_polling_interval = 
	    STATIC_SYMBOL("NATIVE-WINDOW-POLLING-INTERVAL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnative_window_polling_interval,
	    Native_window_polling_interval);
    record_system_variable(Qnative_window_polling_interval,Qplatforms,
	    FIX((SI_Long)3600000L),Qnil,Qnil,Qnil,Qnil);
    string_constant_50 = STATIC_STRING("FOR-WORKSTATION-CONTEXT");
    if (For_workstation_context == UNBOUND)
	For_workstation_context = make_recursive_lock(2,Kname,
		string_constant_50);
    Qfor_workstation_context = STATIC_SYMBOL("FOR-WORKSTATION-CONTEXT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfor_workstation_context,
	    For_workstation_context);
    Qtelestubs = STATIC_SYMBOL("TELESTUBS",AB_package);
    Qunwind_qm = STATIC_SYMBOL("UNWIND\?",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qfor_workstation_context,
	    Qtelestubs,Nil,Qnil,Qnil,Qnil,Nil);
    cdddr_arg = CDDDR(named_dynamic_extent_description);
    cdddr_new_value = set_getf(CDDDR(cdddr_arg),Qunwind_qm,T);
    M_CDDDR(cdddr_arg) = cdddr_new_value;
    mutate_global_property(Qfor_workstation_context,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    string_constant_51 = STATIC_STRING("FOR-WORKSTATION-POLLING");
    if (For_workstation_polling == UNBOUND)
	For_workstation_polling = make_recursive_lock(2,Kname,
		string_constant_51);
    Qfor_workstation_polling = STATIC_SYMBOL("FOR-WORKSTATION-POLLING",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfor_workstation_polling,
	    For_workstation_polling);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qfor_workstation_polling,
	    Qplatforms,Nil,Qnil,Qnil,Qnil,Nil);
    cdddr_arg = CDDDR(named_dynamic_extent_description);
    cdddr_new_value = set_getf(CDDDR(cdddr_arg),Qunwind_qm,T);
    M_CDDDR(cdddr_arg) = cdddr_new_value;
    mutate_global_property(Qfor_workstation_polling,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    string_constant_6 = STATIC_STRING("#000000");
    string_constant_7 = STATIC_STRING("#ffffff");
    Qicp_window_protocol_supports_mdi = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MDI",AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_mdi,FIX((SI_Long)37L));
    Qicp_window_protocol_supports_custom_dialogs = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-CUSTOM-DIALOGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_custom_dialogs,
	    FIX((SI_Long)38L));
    Qicp_window_protocol_supports_nms_controls = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NMS-CONTROLS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_nms_controls,
	    FIX((SI_Long)39L));
    Qicp_window_protocol_supports_list_directory = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-LIST-DIRECTORY",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_list_directory,
	    FIX((SI_Long)40L));
    Qicp_window_protocol_supports_set_window_title = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SET-WINDOW-TITLE",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_set_window_title,
	    FIX((SI_Long)41L));
    Qicp_window_protocol_supports_nms_modify_control = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NMS-MODIFY-CONTROL",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_nms_modify_control,
	    FIX((SI_Long)42L));
    Qicp_window_protocol_supports_manage_status_bar = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MANAGE-STATUS-BAR",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_manage_status_bar,
	    FIX((SI_Long)43L));
    Qicp_window_protocol_supports_nms_selection_callbacks = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NMS-SELECTION-CALLBACKS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_nms_selection_callbacks,
	    FIX((SI_Long)44L));
    Qicp_window_protocol_supports_file_dialog_ex = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-FILE-DIALOG-EX",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_file_dialog_ex,
	    FIX((SI_Long)45L));
    Qicp_window_protocol_supports_tree_views = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TREE-VIEWS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_tree_views,
	    FIX((SI_Long)46L));
    Qicp_window_protocol_supports_html_views = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-HTML-VIEWS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_html_views,
	    FIX((SI_Long)47L));
    Qicp_window_protocol_supports_debugger_dialog = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-DEBUGGER-DIALOG",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_debugger_dialog,
	    FIX((SI_Long)48L));
    Qicp_window_protocol_supports_native_editor = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-EDITOR",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_native_editor,
	    FIX((SI_Long)49L));
    Qicp_window_protocol_supports_native_printing_ex = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-PRINTING-EX",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_native_printing_ex,
	    FIX((SI_Long)50L));
    Qicp_window_protocol_supports_nms_unposting_callbacks = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NMS-UNPOSTING-CALLBACKS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_nms_unposting_callbacks,
	    FIX((SI_Long)51L));
    Qicp_window_protocol_supports_shortcut_bars = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SHORTCUT-BARS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_shortcut_bars,
	    FIX((SI_Long)52L));
    Qicp_window_protocol_supports_polyarcs = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-POLYARCS",AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_polyarcs,FIX((SI_Long)53L));
    Qicp_window_protocol_supports_chart_views = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-CHART-VIEWS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_chart_views,
	    FIX((SI_Long)54L));
    Qicp_window_protocol_supports_grid_views = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-GRID-VIEWS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_grid_views,
	    FIX((SI_Long)55L));
    Qicp_window_protocol_supports_tabular_view_selected_rows = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TABULAR-VIEW-SELECTED-ROWS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_tabular_view_selected_rows,
	    FIX((SI_Long)56L));
    Qicp_window_protocol_supports_zorder_native_window = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-ZORDER-NATIVE-WINDOW",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_zorder_native_window,
	    FIX((SI_Long)57L));
    Qicp_window_protocol_supports_dialog_panes = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-DIALOG-PANES",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_dialog_panes,
	    FIX((SI_Long)58L));
    Qicp_window_protocol_supports_new_grid_views = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NEW-GRID-VIEWS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_new_grid_views,
	    FIX((SI_Long)59L));
    Qicp_window_protocol_supports_manage_pane = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MANAGE-PANE",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_manage_pane,
	    FIX((SI_Long)60L));
    Qicp_window_protocol_supports_scroll_while_minimized_fix = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SCROLL-WHILE-MINIMIZED-FIX",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_scroll_while_minimized_fix,
	    FIX((SI_Long)61L));
    Qicp_window_protocol_supports_nms_set_theme = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NMS-SET-THEME",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_nms_set_theme,
	    FIX((SI_Long)62L));
    Qicp_window_protocol_supports_toolbar_docking = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TOOLBAR-DOCKING",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_toolbar_docking,
	    FIX((SI_Long)63L));
    Qicp_window_protocol_supports_simple_dialog_ex = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SIMPLE-DIALOG-EX",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_simple_dialog_ex,
	    FIX((SI_Long)64L));
    Qicp_window_protocol_supports_tree_views_ex = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TREE-VIEWS-EX",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_tree_views_ex,
	    FIX((SI_Long)65L));
    Qicp_window_protocol_supports_views_api = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-VIEWS-API",AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_views_api,
	    FIX((SI_Long)66L));
    Qicp_window_protocol_supports_html_help_ex = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-HTML-HELP-EX",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_html_help_ex,
	    FIX((SI_Long)67L));
    Qicp_window_protocol_supports_manage_ui_properties = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MANAGE-UI-PROPERTIES",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_manage_ui_properties,
	    FIX((SI_Long)68L));
    Qicp_window_protocol_supports_manage_logbook = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MANAGE-LOGBOOK",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_manage_logbook,
	    FIX((SI_Long)69L));
    Qicp_window_protocol_supports_grid_view_small_chunks = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-GRID-VIEW-SMALL-CHUNKS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_grid_view_small_chunks,
	    FIX((SI_Long)70L));
    Qicp_window_protocol_supports_tabbed_mdi_mode = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TABBED-MDI-MODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_tabbed_mdi_mode,
	    FIX((SI_Long)71L));
    Qicp_window_protocol_supports_manage_dialog = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MANAGE-DIALOG",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_manage_dialog,
	    FIX((SI_Long)72L));
    Qicp_window_protocol_supports_modify_node = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MODIFY-NODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_modify_node,
	    FIX((SI_Long)73L));
    Qicp_window_protocol_supports_views_in_dialogs = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-VIEWS-IN-DIALOGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_views_in_dialogs,
	    FIX((SI_Long)74L));
    Qicp_window_protocol_supports_hide_toolbar = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-HIDE-TOOLBAR",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_hide_toolbar,
	    FIX((SI_Long)75L));
    Qicp_window_protocol_supports_extended_dialog_text_boxes = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-EXTENDED-DIALOG-TEXT-BOXES",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_extended_dialog_text_boxes,
	    FIX((SI_Long)76L));
    Qicp_window_protocol_supports_property_grid = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-PROPERTY-GRID",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_property_grid,
	    FIX((SI_Long)77L));
    Qicp_window_protocol_supports_append_control_ex = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-APPEND-CONTROL-EX",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_append_control_ex,
	    FIX((SI_Long)78L));
    Qicp_window_protocol_supports_chart_views_in_panes = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-CHART-VIEWS-IN-PANES",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_chart_views_in_panes,
	    FIX((SI_Long)79L));
    Qicp_window_protocol_supports_incremental_editor_updates = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-INCREMENTAL-EDITOR-UPDATES",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_incremental_editor_updates,
	    FIX((SI_Long)80L));
    Qicp_window_protocol_supports_native_editor_ex = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NATIVE-EDITOR-EX",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_native_editor_ex,
	    FIX((SI_Long)81L));
    Qicp_window_protocol_supports_nip_rescale_window = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-NIP-RESCALE-WINDOW",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_nip_rescale_window,
	    FIX((SI_Long)82L));
    Qicp_window_protocol_supports_manage_status_bar_ex = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-MANAGE-STATUS-BAR-EX",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_manage_status_bar_ex,
	    FIX((SI_Long)83L));
    Qicp_window_protocol_supports_choose_directory = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-CHOOSE-DIRECTORY",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_choose_directory,
	    FIX((SI_Long)84L));
    Qicp_window_protocol_supports_tabular_views = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TABULAR-VIEWS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_tabular_views,
	    FIX((SI_Long)85L));
    Qicp_window_protocol_supports_views_in_listbars = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-VIEWS-IN-LISTBARS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_views_in_listbars,
	    FIX((SI_Long)86L));
    Qicp_window_protocol_supports_choose_directory_on_server = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-CHOOSE-DIRECTORY-ON-SERVER",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_choose_directory_on_server,
	    FIX((SI_Long)87L));
    Qicp_window_protocol_supports_tabular_view_selection_changed_events = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-TABULAR-VIEW-SELECTION-CHANGED-EVENTS",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_tabular_view_selection_changed_events,
	    FIX((SI_Long)88L));
    Qicp_window_protocol_supports_grid_view_delimiter_fix = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-GRID-VIEW-DELIMITER-FIX",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_grid_view_delimiter_fix,
	    FIX((SI_Long)89L));
    Qicp_window_protocol_supports_set_background_color = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-SUPPORTS-SET-BACKGROUND-COLOR",
	    AB_package);
    SET_SYMBOL_VALUE(Qicp_window_protocol_supports_set_background_color,
	    FIX((SI_Long)90L));
    Latest_icp_window_protocol_version = FIX((SI_Long)91L);
    Qsystem_metrics = STATIC_SYMBOL("SYSTEM-METRICS",AB_package);
    Default_width_of_window_border = FIX((SI_Long)6L);
    Qpane_layout = STATIC_SYMBOL("PANE-LAYOUT",AB_package);
    Qdetail_pane = STATIC_SYMBOL("DETAIL-PANE",AB_package);
    list_constant_11 = STATIC_CONS(Qdetail_pane,Qnil);
    Qallow_user_notifications_qm = 
	    STATIC_SYMBOL("ALLOW-USER-NOTIFICATIONS\?",AB_package);
    Qallow_panic_messages_qm = STATIC_SYMBOL("ALLOW-PANIC-MESSAGES\?",
	    AB_package);
    Qbits_per_pixel = STATIC_SYMBOL("BITS-PER-PIXEL",AB_package);
    Qminimum_line_height_of_text_to_draw = 
	    STATIC_SYMBOL("MINIMUM-LINE-HEIGHT-OF-TEXT-TO-DRAW",AB_package);
    Qwidth_of_space_between_panes = 
	    STATIC_SYMBOL("WIDTH-OF-SPACE-BETWEEN-PANES",AB_package);
    Qdefault_minimum_width_for_pane = 
	    STATIC_SYMBOL("DEFAULT-MINIMUM-WIDTH-FOR-PANE",AB_package);
    Qdefault_minimum_height_for_pane = 
	    STATIC_SYMBOL("DEFAULT-MINIMUM-HEIGHT-FOR-PANE",AB_package);
    Qpane_borders_color = STATIC_SYMBOL("PANE-BORDERS-COLOR",AB_package);
    Qdefault_image_border_width = 
	    STATIC_SYMBOL("DEFAULT-IMAGE-BORDER-WIDTH",AB_package);
    Qdefault_image_border_color = 
	    STATIC_SYMBOL("DEFAULT-IMAGE-BORDER-COLOR",AB_package);
    Qminimum_scale = STATIC_SYMBOL("MINIMUM-SCALE",AB_package);
    Qmaximum_scale = STATIC_SYMBOL("MAXIMUM-SCALE",AB_package);
    Quse_xor_for_addition_qm = STATIC_SYMBOL("USE-XOR-FOR-ADDITION\?",
	    AB_package);
    Qdefault_workspace_area_background_color = 
	    STATIC_SYMBOL("DEFAULT-WORKSPACE-AREA-BACKGROUND-COLOR",
	    AB_package);
    Qdefault_workspace_area_foreground_color = 
	    STATIC_SYMBOL("DEFAULT-WORKSPACE-AREA-FOREGROUND-COLOR",
	    AB_package);
    Qimage_plane_border_outline_width = 
	    STATIC_SYMBOL("IMAGE-PLANE-BORDER-OUTLINE-WIDTH",AB_package);
    Qimage_plane_minimum_border_width = 
	    STATIC_SYMBOL("IMAGE-PLANE-MINIMUM-BORDER-WIDTH",AB_package);
    Qimage_plane_border_color = STATIC_SYMBOL("IMAGE-PLANE-BORDER-COLOR",
	    AB_package);
    Qimage_plane_top_bar_width = STATIC_SYMBOL("IMAGE-PLANE-TOP-BAR-WIDTH",
	    AB_package);
    Qimage_plane_title_color = STATIC_SYMBOL("IMAGE-PLANE-TITLE-COLOR",
	    AB_package);
    Qimage_plane_title_font_map = 
	    STATIC_SYMBOL("IMAGE-PLANE-TITLE-FONT-MAP",AB_package);
    Qhm18 = STATIC_SYMBOL("HM18",AB_package);
    list_constant_9 = STATIC_CONS(Qhm18,Qnil);
    Qimage_plane_title_baseline_position = 
	    STATIC_SYMBOL("IMAGE-PLANE-TITLE-BASELINE-POSITION",AB_package);
    Qimage_plane_hide_button_color = 
	    STATIC_SYMBOL("IMAGE-PLANE-HIDE-BUTTON-COLOR",AB_package);
    Qimage_plane_hide_button_width = 
	    STATIC_SYMBOL("IMAGE-PLANE-HIDE-BUTTON-WIDTH",AB_package);
    Qimage_plane_hide_button_height = 
	    STATIC_SYMBOL("IMAGE-PLANE-HIDE-BUTTON-HEIGHT",AB_package);
    Qimage_plane_hide_button_position = 
	    STATIC_SYMBOL("IMAGE-PLANE-HIDE-BUTTON-POSITION",AB_package);
    Qimage_plane_scroll_bar_width = 
	    STATIC_SYMBOL("IMAGE-PLANE-SCROLL-BAR-WIDTH",AB_package);
    Qimage_plane_scroll_bar_background_color = 
	    STATIC_SYMBOL("IMAGE-PLANE-SCROLL-BAR-BACKGROUND-COLOR",
	    AB_package);
    Qimage_plane_scroll_bar_rail_width = 
	    STATIC_SYMBOL("IMAGE-PLANE-SCROLL-BAR-RAIL-WIDTH",AB_package);
    Qimage_plane_scroll_bar_rail_color = 
	    STATIC_SYMBOL("IMAGE-PLANE-SCROLL-BAR-RAIL-COLOR",AB_package);
    Qimage_plane_scroll_bar_thumb_width = 
	    STATIC_SYMBOL("IMAGE-PLANE-SCROLL-BAR-THUMB-WIDTH",AB_package);
    Qimage_plane_scroll_bar_thumb_color = 
	    STATIC_SYMBOL("IMAGE-PLANE-SCROLL-BAR-THUMB-COLOR",AB_package);
    Qtype_of_gensym_window = STATIC_SYMBOL("TYPE-OF-GENSYM-WINDOW",AB_package);
    Qx11_window = STATIC_SYMBOL("X11-WINDOW",AB_package);
    Qscratchpad_raster_type_for_window = 
	    STATIC_SYMBOL("SCRATCHPAD-RASTER-TYPE-FOR-WINDOW",AB_package);
    Qx11_pixmap = STATIC_SYMBOL("X11-PIXMAP",AB_package);
    Qstored_raster_type_for_window = 
	    STATIC_SYMBOL("STORED-RASTER-TYPE-FOR-WINDOW",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)10L,
	    Qimage_plane_scroll_bar_thumb_width,FIX((SI_Long)20L),
	    Qimage_plane_scroll_bar_thumb_color,Qblack,
	    Qtype_of_gensym_window,Qx11_window,
	    Qscratchpad_raster_type_for_window,Qx11_pixmap,
	    Qstored_raster_type_for_window,Qx11_pixmap);
    list_constant_12 = STATIC_LIST_STAR((SI_Long)32L,Qblack,
	    Qimage_plane_border_outline_width,FIX((SI_Long)2L),
	    Qimage_plane_minimum_border_width,FIX((SI_Long)3L),
	    Qimage_plane_border_color,Qblack,Qimage_plane_top_bar_width,
	    FIX((SI_Long)28L),Qimage_plane_title_color,Qwhite,
	    Qimage_plane_title_font_map,list_constant_9,
	    Qimage_plane_title_baseline_position,FIX((SI_Long)21L),
	    Qimage_plane_hide_button_color,Qwhite,
	    Qimage_plane_hide_button_width,FIX((SI_Long)18L),
	    Qimage_plane_hide_button_height,FIX((SI_Long)18L),
	    Qimage_plane_hide_button_position,FIX((SI_Long)12L),
	    Qimage_plane_scroll_bar_width,FIX((SI_Long)28L),
	    Qimage_plane_scroll_bar_background_color,Qwhite,
	    Qimage_plane_scroll_bar_rail_width,FIX((SI_Long)8L),
	    Qimage_plane_scroll_bar_rail_color,Qblack,list_constant_10);
    list_constant_1 = STATIC_LIST_STAR((SI_Long)32L,Qpane_layout,
	    list_constant_11,Qallow_user_notifications_qm,Qt,
	    Qallow_panic_messages_qm,Qt,Qbits_per_pixel,FIX((SI_Long)1L),
	    Qminimum_line_height_of_text_to_draw,FIX((SI_Long)6L),
	    Qwidth_of_space_between_panes,FIX((SI_Long)2L),
	    Qdefault_minimum_width_for_pane,FIX((SI_Long)10L),
	    Qdefault_minimum_height_for_pane,FIX((SI_Long)10L),
	    Qpane_borders_color,Qblack,Qdefault_image_border_width,
	    FIX((SI_Long)3L),Qdefault_image_border_color,Qblack,
	    Qminimum_scale,FIX((SI_Long)32L),Qmaximum_scale,
	    FIX((SI_Long)16384L),Quse_xor_for_addition_qm,Qt,
	    Qdefault_workspace_area_background_color,Qwhite,
	    Qdefault_workspace_area_foreground_color,list_constant_12);
    Qwidth_of_window_border = STATIC_SYMBOL("WIDTH-OF-WINDOW-BORDER",
	    AB_package);
    Qdefault_x_scale = STATIC_SYMBOL("DEFAULT-X-SCALE",AB_package);
    Qdefault_y_scale = STATIC_SYMBOL("DEFAULT-Y-SCALE",AB_package);
    Qcolor_description_plist_qm = 
	    STATIC_SYMBOL("COLOR-DESCRIPTION-PLIST\?",AB_package);
    Qwindow_x_in_parent = STATIC_SYMBOL("WINDOW-X-IN-PARENT",AB_package);
    Qwindow_y_in_parent = STATIC_SYMBOL("WINDOW-Y-IN-PARENT",AB_package);
    Qdefault_pane_background_color_or_tiling_pattern_rows = 
	    STATIC_SYMBOL("DEFAULT-PANE-BACKGROUND-COLOR-OR-TILING-PATTERN-ROWS",
	    AB_package);
    Qicp_window_protocol_version = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-VERSION",AB_package);
    Qwindow_screen_depth = STATIC_SYMBOL("WINDOW-SCREEN-DEPTH",AB_package);
    Qcharting_library_version_qm = 
	    STATIC_SYMBOL("CHARTING-LIBRARY-VERSION\?",AB_package);
    if (Node_id_for_uuid == UNBOUND)
	Node_id_for_uuid = Nil;
    if (Node_id_for_uuid_uses_ethernet_address_p == UNBOUND)
	Node_id_for_uuid_uses_ethernet_address_p = Nil;
    string_constant_52 = 
	    STATIC_STRING("/bin/grep \'[0-9a-z][0-9a-z]:..:..:..:..:..\' | /bin/sed -e \'s/^\\(.*\\)/\\1 /\' -e \'s/^.*[ \\t]\\([0-9a-z][0-9a-z]:[0-9a-z:]*\\) .*$/\\1/\'");
    Extract_ethernet_script = string_constant_52;
    Qunix = STATIC_SYMBOL("UNIX",AB_package);
    Qvax = STATIC_SYMBOL("VAX",AB_package);
    Qalphavms = STATIC_SYMBOL("ALPHAVMS",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qvax,Qalphavms);
    Qhp9000s700 = STATIC_SYMBOL("HP9000S700",AB_package);
    string_constant_8 = STATIC_STRING("lanscan -a");
    Qskip_two_characters = STATIC_SYMBOL("SKIP-TWO-CHARACTERS",AB_package);
    Qalphaosf = STATIC_SYMBOL("ALPHAOSF",AB_package);
    string_constant_9 = STATIC_STRING("netstat -i -I ln0 | grep \'<Link>\'");
    Qextract_ethernet = STATIC_SYMBOL("EXTRACT-ETHERNET",AB_package);
    Qsgi = STATIC_SYMBOL("SGI",AB_package);
    string_constant_10 = STATIC_STRING("netstat -ia");
    Qsparcsol = STATIC_SYMBOL("SPARCSOL",AB_package);
    string_constant_11 = 
	    STATIC_STRING("ndd /dev/arp arp_cache_report | grep PUBLISH");
    Qintelsol = STATIC_SYMBOL("INTELSOL",AB_package);
    string_constant_12 = STATIC_STRING("~A | ~A");
    Qtime_of_last_uuid = STATIC_SYMBOL("TIME-OF-LAST-UUID",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtime_of_last_uuid,Time_of_last_uuid);
    record_system_variable(Qtime_of_last_uuid,Qplatforms,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    if (Always_use_current_time_for_uuid == UNBOUND)
	Always_use_current_time_for_uuid = Nil;
    Quse_current_time_for_next_uuid = 
	    STATIC_SYMBOL("USE-CURRENT-TIME-FOR-NEXT-UUID",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quse_current_time_for_next_uuid,
	    Use_current_time_for_next_uuid);
    record_system_variable(Quse_current_time_for_next_uuid,Qplatforms,T,
	    Qnil,Qnil,Qnil,Qnil);
    Qclock_sequence_for_uuid = STATIC_SYMBOL("CLOCK-SEQUENCE-FOR-UUID",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclock_sequence_for_uuid,
	    Clock_sequence_for_uuid);
    record_system_variable(Qclock_sequence_for_uuid,Qplatforms,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    float_constant = STATIC_FLOAT(262143.0);
    Quuid_time_b0 = STATIC_SYMBOL("UUID-TIME-B0",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quuid_time_b0,Uuid_time_b0);
    record_system_variable(Quuid_time_b0,Qplatforms,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    Quuid_time_b1 = STATIC_SYMBOL("UUID-TIME-B1",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quuid_time_b1,Uuid_time_b1);
    record_system_variable(Quuid_time_b1,Qplatforms,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    Quuid_time_b2 = STATIC_SYMBOL("UUID-TIME-B2",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quuid_time_b2,Uuid_time_b2);
    record_system_variable(Quuid_time_b2,Qplatforms,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    Quuid_time_b3 = STATIC_SYMBOL("UUID-TIME-B3",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quuid_time_b3,Uuid_time_b3);
    record_system_variable(Quuid_time_b3,Qplatforms,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Quser_notified_of_uuid_uniqueness_problem_p = 
	    STATIC_SYMBOL("USER-NOTIFIED-OF-UUID-UNIQUENESS-PROBLEM-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_notified_of_uuid_uniqueness_problem_p,
	    User_notified_of_uuid_uniqueness_problem_p);
    record_system_variable(Quser_notified_of_uuid_uniqueness_problem_p,
	    Qplatforms,Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_13 = STATIC_STRING("Unrecognized error code: ");
    string_constant_14 = STATIC_STRING("~a~a");
    string_constant_15 = STATIC_STRING("");
    string_constant_16 = 
	    STATIC_STRING("This computer\'s operating system cannot generate a universal unique ID (UUID).~\n              ~%~a");
    Qintelnt = STATIC_SYMBOL("INTELNT",AB_package);
    Qalphant = STATIC_SYMBOL("ALPHANT",AB_package);
    string_constant_17 = STATIC_STRING("000");
    string_constant_18 = STATIC_STRING("00");
    string_constant_19 = STATIC_STRING("0");
}
