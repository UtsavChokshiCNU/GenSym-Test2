/* gfi-sb.c
 * Input file:  gfi-stubs.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gfi-sb.h"


static Object Qnone;               /* none */

/* COMPILE-GFI-FILE-FORMAT-FOR-SLOT */
Object compile_gfi_file_format_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(215,0);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* COMPILE-GFI-FILE-PATHNAME-FOR-SLOT */
Object compile_gfi_file_pathname_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(215,1);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

static Object string_constant;     /* "yes" */

static Object string_constant_1;   /* "no" */

/* WRITE-GFI-YES-OR-NO?-FROM-SLOT */
Object write_gfi_yes_or_no_qm_from_slot(value_qm,gensymed_symbol)
    Object value_qm, gensymed_symbol;
{
    x_note_fn_call(215,2);
    return twrite_general_string(value_qm ? string_constant : 
	    string_constant_1);
}

static Object Qrelative;           /* relative */

static Object array_constant;      /* # */

static Object Qexplicit;           /* explicit */

static Object array_constant_1;    /* # */

static Object string_constant_2;   /* "The slot value writer for gfi-time-stamp-format ~
				    *               received an illegal value: ~a."
				    */

/* WRITE-GFI-TIME-STAMP-FORMAT-FROM-SLOT */
Object write_gfi_time_stamp_format_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(215,3);
    if (EQ(value,Qrelative))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)19L));
    else if (EQ(value,Qexplicit))
	return twrite_beginning_of_wide_string(array_constant_1,
		FIX((SI_Long)19L));
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)2L),string_constant_2,value);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
}

static Object Qevent_log;          /* event-log */

static Object array_constant_2;    /* # */

static Object Qspreadsheet;        /* spreadsheet */

static Object array_constant_3;    /* # */

static Object Qnupec_snapshot;     /* nupec-snapshot */

static Object array_constant_4;    /* # */

static Object Qnupec_snapshot_with_restart_time;  /* nupec-snapshot-with-restart-time */

static Object array_constant_5;    /* # */

static Object string_constant_3;   /* "The slot value writer for gfi-file-format ~
				    *               received an illegal value: ~a."
				    */

/* WRITE-GFI-FILE-FORMAT-FROM-SLOT */
Object write_gfi_file_format_from_slot(format_1,gensymed_symbol)
    Object format_1, gensymed_symbol;
{
    x_note_fn_call(215,4);
    if (EQ(format_1,Qevent_log))
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)9L));
    else if (EQ(format_1,Qspreadsheet))
	return twrite_beginning_of_wide_string(array_constant_3,
		FIX((SI_Long)11L));
    else if (EQ(format_1,Qnupec_snapshot))
	return twrite_beginning_of_wide_string(array_constant_4,
		FIX((SI_Long)14L));
    else if (EQ(format_1,Qnupec_snapshot_with_restart_time))
	return twrite_beginning_of_wide_string(array_constant_5,
		FIX((SI_Long)32L));
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)2L),string_constant_3,format_1);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
}

static Object string_constant_4;   /* "The slot value writer for gfi-file-pathname ~
				    *               received an illegal value ~a."
				    */

/* WRITE-GFI-FILE-PATHNAME-FROM-SLOT */
Object write_gfi_file_pathname_from_slot(file_pathname,gensymed_symbol)
    Object file_pathname, gensymed_symbol;
{
    x_note_fn_call(215,5);
    if (text_string_p(file_pathname))
	return tprin(file_pathname,T);
    else if (ATOM(file_pathname) ? file_pathname && SYMBOLP(file_pathname) 
	    : 
	    TRUEP(designation_operator_or_giver_of_value_p(CAR(file_pathname))))
	return print_designation(file_pathname);
    else if ( !TRUEP(file_pathname))
	return twrite(Qnone);
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)2L),string_constant_4,file_pathname);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
}

static Object array_constant_6;    /* # */

/* WRITE-NO-GFI-OUTPUT-VALUES-NOTE */
Object write_no_gfi_output_values_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(215,6);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_6,
	    FIX((SI_Long)34L)));
    return VALUES_1(Nil);
}

static Object array_constant_7;    /* # */

/* WRITE-NO-GFI-OUTPUT-UPDATE-FREQUENCY-NOTE */
Object write_no_gfi_output_update_frequency_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(215,7);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_7,
	    FIX((SI_Long)43L)));
    return VALUES_1(Nil);
}

static Object array_constant_8;    /* # */

/* WRITE-NO-GFI-OUTPUT-FILE-PATHNAME-NOTE */
Object write_no_gfi_output_file_pathname_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(215,8);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_8,
	    FIX((SI_Long)40L)));
    return VALUES_1(Nil);
}

static Object array_constant_9;    /* # */

/* WRITE-NO-GFI-INPUT-FILE-PATHNAME-NOTE */
Object write_no_gfi_input_file_pathname_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(215,9);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_9,
	    FIX((SI_Long)39L)));
    return VALUES_1(Nil);
}

static Object array_constant_10;   /* # */

/* WRITE-NO-GFI-INPUT-VARIABLES-UPDATE-MODE-NOTE */
Object write_no_gfi_input_variables_update_mode_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(215,10);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_10,
	    FIX((SI_Long)47L)));
    return VALUES_1(Nil);
}

static Object Qcm;                 /* \, */

/* COMPILE-GFI-OUTPUT-VALUES-FOR-SLOT */
Object compile_gfi_output_values_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(215,11);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    simplify_associative_list_operation_all_at_once(parse_result);
    if ( !TRUEP(parse_result))
	return VALUES_1(Nil);
    else if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else if (SYMBOLP(parse_result))
	return phrase_cons(parse_result,Nil);
    else if (EQ(CAR(parse_result),Qcm))
	return VALUES_1(CDR(parse_result));
    else
	return phrase_cons(parse_result,Nil);
}

/* COMPILE-GFI-OUTPUT-FILE-UPDATE-FREQUENCY-FOR-SLOT */
Object compile_gfi_output_file_update_frequency_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(215,12);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(parse_result))
	return VALUES_1(Nil);
    else if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* WRITE-RENAMED-GFI-OUTPUT-FILE-PATHNAME-FROM-SLOT */
Object write_renamed_gfi_output_file_pathname_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(215,13);
    if (text_string_p(value))
	return tprin(value,T);
    else if (ATOM(value) ? value && SYMBOLP(value) : 
	    TRUEP(designation_operator_or_giver_of_value_p(CAR(value))))
	return print_designation(value);
    else if ( !TRUEP(value))
	return twrite(Qnone);
    else
	return VALUES_1(Qnil);
}

/* WRITE-GFI-OUTPUT-VALUES-FROM-SLOT */
Object write_gfi_output_values_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(215,14);
    if ( !TRUEP(value))
	return twrite(Qnone);
    else if (LISTP(value)) {
	if ( !TRUEP(FIRST(value)))
	    return twrite(Qnone);
	else {
	    temp = FIRST(value);
	    if (LISTP(temp))
		return print_designation_list(FIRST(value));
	    else
		return VALUES_1(Qt);
	}
    }
    else
	return VALUES_1(Qt);
}

static Object Qwhen_received_value;  /* when-received-value */

static Object string_constant_5;   /* "write to file when variables receive values" */

static Object Qoutput_one_shot_when_activated;  /* output-one-shot-when-activated */

static Object string_constant_6;   /* "write to file when activated" */

static Object Qoutput_one_shot_when_activated_without_interruption;  /* output-one-shot-when-activated-without-interruption */

static Object string_constant_7;   /* "write to file when activated, without interruption" */

static Object Qwrite_interval;     /* write-interval */

static Object string_constant_8;   /* "write to file every " */

static Object Qseconds;            /* seconds */

static Object string_constant_9;   /* "The slot value writer for gfi-output-file-update-frequency ~
				    *               received an illegal value: ~a."
				    */

/* WRITE-GFI-OUTPUT-FILE-UPDATE-FREQUENCY-FROM-SLOT */
Object write_gfi_output_file_update_frequency_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;
    char temp_1;

    x_note_fn_call(215,15);
    if ( !TRUEP(value))
	return twrite(Qnone);
    else if (EQ(value,Qnone))
	return twrite(Qnone);
    else if (EQ(value,Qwhen_received_value))
	return tformat(1,string_constant_5);
    else if (EQ(value,Qoutput_one_shot_when_activated))
	return tformat(1,string_constant_6);
    else if (EQ(value,Qoutput_one_shot_when_activated_without_interruption))
	return tformat(1,string_constant_7);
    else {
	if (LISTP(value) && EQ(CAR(value),Qwrite_interval)) {
	    temp = SECOND(value);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    tformat(1,string_constant_8);
	    temp = SECOND(value);
	    return print_constant(2,CAR(temp),Qseconds);
	}
	else {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)2L),string_constant_9,value);
	    Suppress_warning_message_header_qm = Nil;
	    return VALUES_1(Suppress_warning_message_header_qm);
	}
    }
}

/* RECLAIM-GFI-INPUT-FILE-BUFFER-VALUE */
Object reclaim_gfi_input_file_buffer_value(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(215,16);
    reclaim_simple_gensym_string(value);
    return VALUES_1(Nil);
}

/* WRITE-IGNORE-GFI-INPUT-BASE-TIME?-FROM-SLOT */
Object write_ignore_gfi_input_base_time_qm_from_slot(value_qm,gensymed_symbol)
    Object value_qm, gensymed_symbol;
{
    x_note_fn_call(215,17);
    return twrite_general_string(value_qm ? string_constant : 
	    string_constant_1);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qgfi_input_interface;  /* gfi-input-interface */

static Object list_constant;       /* # */

static Object Qgfi_input_ignore_data_server_qm;  /* gfi-input-ignore-data-server? */

static Object array_constant_11;   /* # */

static Object Qasynchronous;       /* asynchronous */

static Object array_constant_12;   /* # */

static Object Qasynchronous_ignoring_data_server;  /* asynchronous-ignoring-data-server */

static Object array_constant_13;   /* # */

static Object Qon_request;         /* on-request */

static Object array_constant_14;   /* # */

static Object Qon_request_sample_and_hold;  /* on-request-sample-and-hold */

static Object array_constant_15;   /* # */

static Object Qinput_one_shot_when_activated;  /* input-one-shot-when-activated */

static Object array_constant_16;   /* # */

static Object Qinput_one_shot_when_activated_without_interruption;  /* input-one-shot-when-activated-without-interruption */

static Object array_constant_17;   /* # */

static Object string_constant_10;  /* "The attribute gfi-input-variables-update-mode contains ~
				    *                 an illegal value ~a."
				    */

/* WRITE-GFI-INPUT-VARIABLES-UPDATE-MODE-FROM-SLOT */
Object write_gfi_input_variables_update_mode_from_slot(value,gfi_input_frame)
    Object value, gfi_input_frame;
{
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object result_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(215,18);
    if (SIMPLE_VECTOR_P(gfi_input_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gfi_input_frame)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(gfi_input_frame,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(gfi_input_frame,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qgfi_input_interface,
		Class_description_gkbprop);
	if (gensymed_symbol_1) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_3 = (SI_Long)1L;
		gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		temp = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	result_qm = memq_function(value,list_constant);
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_ignore_data_server_qm,result_qm ? T : Nil);
    }
    if ( !TRUEP(value))
	return twrite_beginning_of_wide_string(array_constant_11,
		FIX((SI_Long)4L));
    else if (EQ(value,Qasynchronous))
	return twrite_beginning_of_wide_string(array_constant_12,
		FIX((SI_Long)18L));
    else if (EQ(value,Qasynchronous_ignoring_data_server))
	return twrite_beginning_of_wide_string(array_constant_13,
		FIX((SI_Long)44L));
    else if (EQ(value,Qon_request))
	return twrite_beginning_of_wide_string(array_constant_14,
		FIX((SI_Long)39L));
    else if (EQ(value,Qon_request_sample_and_hold))
	return twrite_beginning_of_wide_string(array_constant_15,
		FIX((SI_Long)32L));
    else if (EQ(value,Qinput_one_shot_when_activated))
	return twrite_beginning_of_wide_string(array_constant_16,
		FIX((SI_Long)20L));
    else if (EQ(value,Qinput_one_shot_when_activated_without_interruption))
	return twrite_beginning_of_wide_string(array_constant_17,
		FIX((SI_Long)42L));
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)2L),string_constant_10,value);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
}

/* COMPILE-GFI-INPUT-VARIABLES-UPDATE-MODE-FOR-SLOT */
Object compile_gfi_input_variables_update_mode_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(215,19);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(parse_result))
	return VALUES_1(Nil);
    else if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

static Object Qgfi_input_interface_object;  /* gfi-input-interface-object */

/* PUT-GFI-INTERFACE-OBJECT-WHERE-SLOT-IS-ABSENT */
Object put_gfi_interface_object_where_slot_is_absent(frame_var,new_value)
    Object frame_var, new_value;
{
    x_note_fn_call(215,20);
    change_slot_value(3,frame_var,Qgfi_input_interface_object,new_value);
    return VALUES_1(Nil);
}

/* COMPILE-GFI-INTERFACE-OBJECT-FOR-SLOT */
Object compile_gfi_interface_object_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(215,21);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* WRITE-GFI-INTERFACE-OBJECT-FROM-SLOT */
Object write_gfi_interface_object_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(215,22);
    if ( !TRUEP(value))
	return twrite_beginning_of_wide_string(array_constant_11,
		FIX((SI_Long)4L));
    else
	return print_designation(value);
}

void gfi_stubs_INIT()
{
    Object grammar_categories_getting_yes_no_feature_new_value;
    Object write_no_gfi_output_values_note_1;
    Object write_no_gfi_output_update_frequency_note_1;
    Object write_no_gfi_output_file_pathname_note_1;
    Object write_no_gfi_input_file_pathname_note_1;
    Object write_no_gfi_input_variables_update_mode_note_1, temp, temp_1;
    Object string_constant_65, Qgfi_data_server, AB_package;
    Object Qslot_value_writer, Qwrite_gfi_interface_object_from_slot;
    Object Qgfi_interface_object;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_gfi_interface_object_for_slot;
    Object string_constant_64, Qabsent_slot_putter;
    Object Qput_gfi_interface_object_where_slot_is_absent, string_constant_63;
    Object string_constant_62, list_constant_36, Qgfi_data_service;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object Qgfi_input_variables_update_mode;
    Object Qcompile_gfi_input_variables_update_mode_for_slot;
    Object Qwrite_gfi_input_variables_update_mode_from_slot, list_constant_1;
    Object list_constant_35, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qwrite_ignore_gfi_input_base_time_qm_from_slot;
    Object Qignore_gfi_input_base_time_qm, list_constant_34, list_constant_33;
    Object list_constant_32, list_constant_31, list_constant_30;
    Object list_constant_29, list_constant_28, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object list_constant_8, list_constant_22, list_constant_21;
    Object list_constant_6, Qinterruption, Qwithout, list_constant_23;
    Object Qactivated, list_constant_20, list_constant_19, list_constant_15;
    Object list_constant_14, Qsample_and_hold, list_constant_18;
    Object list_constant_17, list_constant_16, Qtime_stamps, Qpreserving;
    Object Qrequest, Qon, list_constant_13, list_constant_12, list_constant_11;
    Object list_constant_10, list_constant_9, list_constant_5, Qserver, Qdata;
    Object Qignoring, list_constant_4, list_constant_7, Qinput;
    Object list_constant_3, Qignore_gfi_input_base_time, Qslot_value_reclaimer;
    Object Qreclaim_gfi_input_file_buffer_value, Qgfi_input_file_buffer;
    Object string_constant_58, string_constant_57, string_constant_56;
    Object string_constant_55, string_constant_54, string_constant_53;
    Object string_constant_52, list_constant_2, Qobtain_simple_gensym_string;
    Object string_constant_51, string_constant_50, string_constant_49;
    Object string_constant_48, string_constant_47, string_constant_46;
    Object string_constant_45, string_constant_44, string_constant_43;
    Object string_constant_42, string_constant_41, string_constant_40;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object Qwrite_gfi_output_file_update_frequency_from_slot;
    Object Qgfi_output_file_update_frequency;
    Object Qwrite_gfi_output_values_from_slot, Qgfi_output_values;
    Object Qwrite_renamed_gfi_output_file_pathname_from_slot;
    Object Qrenamed_gfi_output_file_pathname;
    Object Qcompile_gfi_output_file_update_frequency_for_slot;
    Object Qcompile_gfi_output_values_for_slot, string_constant_36;
    Object string_constant_35, string_constant_34, Qe_designation;
    Object Qgfi_output_value_list, Qrenamed_gfi_output_file_pathname_qm;
    Object string_constant_33, string_constant_32, string_constant_31;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object string_constant_27, Qgfi_output_interface, string_constant_26;
    Object string_constant_25, string_constant_24, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, Qobject, Qframe_note_writer_1;
    Object Qno_gfi_input_variables_update_mode, Qno_gfi_input_file_pathname;
    Object Qno_gfi_output_file_pathname, Qno_gfi_output_update_frequency;
    Object Qno_gfi_output_values, Qwrite_gfi_file_pathname_from_slot;
    Object Qgfi_file_pathname, Qwrite_gfi_file_format_from_slot;
    Object Qgfi_file_format, Qwrite_gfi_time_stamp_format_from_slot;
    Object Qgfi_time_stamp_format, Qwrite_gfi_yes_or_no_qm_from_slot;
    Object Qgfi_yes_or_no_qm, Qcompile_gfi_file_pathname_for_slot;
    Object Qcompile_gfi_file_format_for_slot, string_constant_12;
    Object string_constant_11;

    x_note_fn_call(215,23);
    SET_PACKAGE("AB");
    string_constant_11 = 
	    STATIC_STRING("1s1m833Ly83Ky1n833Ky1m1m9k83-TLy1m9k832ny83-TLy1n833Ky1m1m9k834Vy1m9k832ny834Vy1n833Iy1m1m9k83vgy1m9k9l833vy1m833Iy1m9k83-qUy1m8");
    string_constant_12 = STATIC_STRING("33Jy1m9k83Zy1m833Jy833ny1m833Jy83-Uy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qlog);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_11,
	    string_constant_12)));
    AB_package = STATIC_PACKAGE("AB");
    Qgfi_yes_or_no_qm = STATIC_SYMBOL("GFI-YES-OR-NO\?",AB_package);
    grammar_categories_getting_yes_no_feature_new_value = adjoin(2,
	    Qgfi_yes_or_no_qm,Grammar_categories_getting_yes_no_feature);
    Grammar_categories_getting_yes_no_feature = 
	    grammar_categories_getting_yes_no_feature_new_value;
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qgfi_file_format = STATIC_SYMBOL("GFI-FILE-FORMAT",AB_package);
    Qcompile_gfi_file_format_for_slot = 
	    STATIC_SYMBOL("COMPILE-GFI-FILE-FORMAT-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_gfi_file_format_for_slot,
	    STATIC_FUNCTION(compile_gfi_file_format_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qgfi_file_format,
	    SYMBOL_FUNCTION(Qcompile_gfi_file_format_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qgfi_file_format,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qgfi_file_pathname = STATIC_SYMBOL("GFI-FILE-PATHNAME",AB_package);
    Qcompile_gfi_file_pathname_for_slot = 
	    STATIC_SYMBOL("COMPILE-GFI-FILE-PATHNAME-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_gfi_file_pathname_for_slot,
	    STATIC_FUNCTION(compile_gfi_file_pathname_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qgfi_file_pathname,
	    SYMBOL_FUNCTION(Qcompile_gfi_file_pathname_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgfi_file_pathname,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant = STATIC_STRING("yes");
    string_constant_1 = STATIC_STRING("no");
    Qwrite_gfi_yes_or_no_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-GFI-YES-OR-NO\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gfi_yes_or_no_qm_from_slot,
	    STATIC_FUNCTION(write_gfi_yes_or_no_qm_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qgfi_yes_or_no_qm,
	    SYMBOL_FUNCTION(Qwrite_gfi_yes_or_no_qm_from_slot),
	    Qslot_value_writer);
    Qrelative = STATIC_SYMBOL("RELATIVE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    Qexplicit = STATIC_SYMBOL("EXPLICIT",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    string_constant_2 = 
	    STATIC_STRING("The slot value writer for gfi-time-stamp-format ~\n              received an illegal value: ~a.");
    Qgfi_time_stamp_format = STATIC_SYMBOL("GFI-TIME-STAMP-FORMAT",AB_package);
    Qwrite_gfi_time_stamp_format_from_slot = 
	    STATIC_SYMBOL("WRITE-GFI-TIME-STAMP-FORMAT-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gfi_time_stamp_format_from_slot,
	    STATIC_FUNCTION(write_gfi_time_stamp_format_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qgfi_time_stamp_format,
	    SYMBOL_FUNCTION(Qwrite_gfi_time_stamp_format_from_slot),
	    Qslot_value_writer);
    Qevent_log = STATIC_SYMBOL("EVENT-LOG",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Qspreadsheet = STATIC_SYMBOL("SPREADSHEET",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    Qnupec_snapshot = STATIC_SYMBOL("NUPEC-SNAPSHOT",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    Qnupec_snapshot_with_restart_time = 
	    STATIC_SYMBOL("NUPEC-SNAPSHOT-WITH-RESTART-TIME",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)57344L);
    string_constant_3 = 
	    STATIC_STRING("The slot value writer for gfi-file-format ~\n              received an illegal value: ~a.");
    Qwrite_gfi_file_format_from_slot = 
	    STATIC_SYMBOL("WRITE-GFI-FILE-FORMAT-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gfi_file_format_from_slot,
	    STATIC_FUNCTION(write_gfi_file_format_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qgfi_file_format,
	    SYMBOL_FUNCTION(Qwrite_gfi_file_format_from_slot),
	    Qslot_value_writer);
    string_constant_4 = 
	    STATIC_STRING("The slot value writer for gfi-file-pathname ~\n              received an illegal value ~a.");
    Qwrite_gfi_file_pathname_from_slot = 
	    STATIC_SYMBOL("WRITE-GFI-FILE-PATHNAME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gfi_file_pathname_from_slot,
	    STATIC_FUNCTION(write_gfi_file_pathname_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qgfi_file_pathname,
	    SYMBOL_FUNCTION(Qwrite_gfi_file_pathname_from_slot),
	    Qslot_value_writer);
    Qno_gfi_output_values = STATIC_SYMBOL("NO-GFI-OUTPUT-VALUES",AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)57344L);
    write_no_gfi_output_values_note_1 = 
	    STATIC_FUNCTION(write_no_gfi_output_values_note,NIL,FALSE,2,2);
    mutate_global_property(Qno_gfi_output_values,
	    write_no_gfi_output_values_note_1,Qframe_note_writer_1);
    Qno_gfi_output_update_frequency = 
	    STATIC_SYMBOL("NO-GFI-OUTPUT-UPDATE-FREQUENCY",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)35L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)37L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)39L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)40L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)42L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)46L,(SI_Long)43L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)47L,(SI_Long)57344L);
    write_no_gfi_output_update_frequency_note_1 = 
	    STATIC_FUNCTION(write_no_gfi_output_update_frequency_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qno_gfi_output_update_frequency,
	    write_no_gfi_output_update_frequency_note_1,Qframe_note_writer_1);
    Qno_gfi_output_file_pathname = 
	    STATIC_SYMBOL("NO-GFI-OUTPUT-FILE-PATHNAME",AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)29L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)32L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)34L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)36L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)37L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)38L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)39L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)46L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)47L,(SI_Long)57344L);
    write_no_gfi_output_file_pathname_note_1 = 
	    STATIC_FUNCTION(write_no_gfi_output_file_pathname_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qno_gfi_output_file_pathname,
	    write_no_gfi_output_file_pathname_note_1,Qframe_note_writer_1);
    Qno_gfi_input_file_pathname = 
	    STATIC_SYMBOL("NO-GFI-INPUT-FILE-PATHNAME",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)33L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)35L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)36L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)38L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)47L,(SI_Long)57344L);
    write_no_gfi_input_file_pathname_note_1 = 
	    STATIC_FUNCTION(write_no_gfi_input_file_pathname_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qno_gfi_input_file_pathname,
	    write_no_gfi_input_file_pathname_note_1,Qframe_note_writer_1);
    Qno_gfi_input_variables_update_mode = 
	    STATIC_SYMBOL("NO-GFI-INPUT-VARIABLES-UPDATE-MODE",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)25L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)32L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)39L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)41L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)42L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)43L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)44L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)45L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)46L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)54L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)55L,(SI_Long)57344L);
    write_no_gfi_input_variables_update_mode_note_1 = 
	    STATIC_FUNCTION(write_no_gfi_input_variables_update_mode_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qno_gfi_input_variables_update_mode,
	    write_no_gfi_input_variables_update_mode_note_1,
	    Qframe_note_writer_1);
    Qgfi_output_interface = STATIC_SYMBOL("GFI-OUTPUT-INTERFACE",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_2 = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qgfi_output_interface,
	    list_constant_2);
    string_constant_13 = 
	    STATIC_STRING("1n1m8v83-Oy1o830by83=8y8301y8304y1l8t");
    string_constant_14 = 
	    STATIC_STRING("13My4z8r831vy831vy8305y8305y00001q1l83Ey1m8p83*iy1l83Fy1l83Hy1l8l1l83-4y000004z8r835By835By8305y8305y08367y001q1l83Ey1m8p83*iy1l");
    string_constant_15 = 
	    STATIC_STRING("83Fy1l83Hy1l8l1l83-4y000004z8r83Dby83Dby8305y8305y00001p1l83Ey1m8p832fy1l8l1l8z1l83Cy000004z8r83CTy83CTy8305y8305y00001o1l83Ey1n");
    string_constant_16 = 
	    STATIC_STRING("8p83CTy83Gy1l8l1l83Cy000004z8r838wy838wy8305y8305y00001p1l83Ey1m8p838wy1l8z1l8l1l83Cy000004z8r83CSy83CSy8305y8305y0834Vy001p1l83");
    string_constant_17 = 
	    STATIC_STRING("Ey1m8p833Ky1l8l1l8z1l83Cy000004z8r83CQy83CQy8305y8305y0833vy001p1l83Ey1m8p833Iy1l8l1l8z1l83Cy000004z8r83Ely83Ely8305y8305y00001p");
    string_constant_18 = 
	    STATIC_STRING("1l83Ey1m8p833Jy1l8z1l8l1l83Cy000004z8r83CRy83CRy8305y8305y00001p1l83Ey1m8p833Jy1l8l1l8z1l83Cy000004z8r83QWy83QWy8305y8305y08k001");
    string_constant_19 = 
	    STATIC_STRING("p1l83Ey1m8p833Ly1l8l1l8z1l83Cy000004z8r83QYy83QYy8305y8305y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QPy83QPy8305y8305y00001o1l8l1l");
    string_constant_20 = 
	    STATIC_STRING("83Ey1l83Ny1l83Hy000004z8r83QOy83QOy8305y8305y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QSy83QSy8305y8305y00001o1l8l1l83Ey1l83Ny1l83");
    string_constant_21 = 
	    STATIC_STRING("Hy000004z8r83QTy83QTy8305y8305y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83Wmy83Wmy8305y8305y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83W");
    string_constant_22 = 
	    STATIC_STRING("Qy83WQy8305y8305y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QNy83QNy8305y8305y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QZy83QZy8305y83");
    string_constant_23 = 
	    STATIC_STRING("05y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83Wsy83Wsy8305y8305y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QXy83QXy8305y8305y00001o1l8l1");
    string_constant_24 = 
	    STATIC_STRING("l83Ey1l83Ny1l83Hy000004z8r83QRy83QRy8305y8305y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QUy83QUy8305y8305y00001o1l8l1l83Ey1l83Ny1l8");
    string_constant_25 = 
	    STATIC_STRING("3Hy000004z8r83QQy83QQy8305y8305y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QVy83QVy8305y8305y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83");
    string_constant_26 = 
	    STATIC_STRING("=ly83=ly8305y8305y00001p1m8p830Uy1l83-4y1l83Ey1l8l1l83Hy00000");
    string_constant_27 = 
	    STATIC_STRING("13Oy8q1p8305y1l83-Oy1m8v83-Oy1o830by83=8y8301y8304y8t1s831vy01l83Ey1m8p83*iy1l83Fy1l83Hy1l8l83-4y1s835By8367y1l83Ey1m8p83*iy1l83");
    string_constant_28 = 
	    STATIC_STRING("Fy1l83Hy1l8l83-4y1r83Dby01l83Ey1m8p832fy1l8l8z1l83Cy1q83CTy01l83Ey1n8p83CTy83Gy1l8l1l83Cy1r838wy01l83Ey1m8p838wy8z1l8l1l83Cy1r83");
    string_constant_29 = 
	    STATIC_STRING("CSy834Vy1l83Ey1m8p833Ky1l8l8z1l83Cy1r83CQy833vy1l83Ey1m8p833Iy1l8l8z1l83Cy1r83Ely01l83Ey1m8p833Jy8z1l8l1l83Cy1r83CRy01l83Ey1m8p8");
    string_constant_30 = 
	    STATIC_STRING("33Jy1l8l8z1l83Cy1r83QWy8k1l83Ey1m8p833Ly1l8l8z1l83Cy1p83QYy01l83Ey1l83Ny1l83Hy1p83QPy01l83Ey1l83Ny1l83Hy1p83QOy01l83Ey1l83Ny1l83");
    string_constant_31 = 
	    STATIC_STRING("Hy1p83QSy01l83Ey1l83Ny1l83Hy1p83QTy01l83Ey1l83Ny1l83Hy1p83Wmy01l83Ey1l83Ny1l83Hy1p83WQy01l83Ey1l83Ny1l83Hy1p83QNy01l83Ey1l83Ny1l");
    string_constant_32 = 
	    STATIC_STRING("83Hy1p83QZy01l83Ey1l83Ny1l83Hy1p83Wsy01l83Ey1l83Ny1l83Hy1p83QXy01l83Ey1l83Ny1l83Hy1p83QRy01l83Ey1l83Ny1l83Hy1p83QUy01l83Ey1l83Ny");
    string_constant_33 = 
	    STATIC_STRING("1l83Hy1p83QQy01l83Ey1l83Ny1l83Hy1p83QVy01l83Ey1l83Ny1l83Hy1r83=ly01m8p830Uy83-4y83Ey8l83Hy");
    temp = regenerate_optimized_constant(string_constant_13);
    temp_1 = regenerate_optimized_constant(list(13,string_constant_14,
	    string_constant_15,string_constant_16,string_constant_17,
	    string_constant_18,string_constant_19,string_constant_20,
	    string_constant_21,string_constant_22,string_constant_23,
	    string_constant_24,string_constant_25,string_constant_26));
    add_class_to_environment(9,Qgfi_output_interface,list_constant_2,Nil,
	    temp,Nil,temp_1,list_constant_2,
	    regenerate_optimized_constant(list(7,string_constant_27,
	    string_constant_28,string_constant_29,string_constant_30,
	    string_constant_31,string_constant_32,string_constant_33)),Nil);
    Qrenamed_gfi_output_file_pathname_qm = 
	    STATIC_SYMBOL("RENAMED-GFI-OUTPUT-FILE-PATHNAME\?",AB_package);
    Qrenamed_gfi_output_file_pathname = 
	    STATIC_SYMBOL("RENAMED-GFI-OUTPUT-FILE-PATHNAME",AB_package);
    alias_slot_name(3,Qrenamed_gfi_output_file_pathname_qm,
	    Qrenamed_gfi_output_file_pathname,Qnil);
    Qgfi_output_value_list = STATIC_SYMBOL("GFI-OUTPUT-VALUE-LIST",AB_package);
    Qe_designation = STATIC_SYMBOL("E-DESIGNATION",AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    add_grammar_rules_for_list(6,Qgfi_output_value_list,Qe_designation,Qcm,
	    Nil,Qnone,Nil);
    string_constant_34 = 
	    STATIC_STRING("1q1m83CTy83-WUy1m838wy1m9k83Zy1n838wy1p1m9k9l1m9k83=3y1m9k83LLy1m9k9m83-oy1m83-xfyp1n838wy1r1m9k9l1m9k83=3y1m9k83LLy1m9k837ey1m9");
    string_constant_35 = 
	    STATIC_STRING("k83-iy1m9k839ry1m9k9n83-wwy1n838wy1p1m9k9l1m9k83=3y1m9k83LLy1m9k837ey1m9k83GSy83-i1y1n838wy1s1m9k9l1m9k83=3y1m9k83LLy1m9k837ey1m");
    string_constant_36 = 
	    STATIC_STRING("9k83GSy1m9k83vy1m9k83AUy1m9k83-=my83-i2y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qwrite);
    push_optimized_constant(Qevery);
    push_optimized_constant(Qvalues);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_34,
	    string_constant_35,string_constant_36)));
    Qgfi_output_values = STATIC_SYMBOL("GFI-OUTPUT-VALUES",AB_package);
    Qcompile_gfi_output_values_for_slot = 
	    STATIC_SYMBOL("COMPILE-GFI-OUTPUT-VALUES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_gfi_output_values_for_slot,
	    STATIC_FUNCTION(compile_gfi_output_values_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qgfi_output_values,
	    SYMBOL_FUNCTION(Qcompile_gfi_output_values_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgfi_output_values,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qgfi_output_file_update_frequency = 
	    STATIC_SYMBOL("GFI-OUTPUT-FILE-UPDATE-FREQUENCY",AB_package);
    Qcompile_gfi_output_file_update_frequency_for_slot = 
	    STATIC_SYMBOL("COMPILE-GFI-OUTPUT-FILE-UPDATE-FREQUENCY-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_gfi_output_file_update_frequency_for_slot,
	    STATIC_FUNCTION(compile_gfi_output_file_update_frequency_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qgfi_output_file_update_frequency,
	    SYMBOL_FUNCTION(Qcompile_gfi_output_file_update_frequency_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgfi_output_file_update_frequency,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_renamed_gfi_output_file_pathname_from_slot = 
	    STATIC_SYMBOL("WRITE-RENAMED-GFI-OUTPUT-FILE-PATHNAME-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_renamed_gfi_output_file_pathname_from_slot,
	    STATIC_FUNCTION(write_renamed_gfi_output_file_pathname_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qrenamed_gfi_output_file_pathname,
	    SYMBOL_FUNCTION(Qwrite_renamed_gfi_output_file_pathname_from_slot),
	    Qslot_value_writer);
    Qwrite_gfi_output_values_from_slot = 
	    STATIC_SYMBOL("WRITE-GFI-OUTPUT-VALUES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gfi_output_values_from_slot,
	    STATIC_FUNCTION(write_gfi_output_values_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qgfi_output_values,
	    SYMBOL_FUNCTION(Qwrite_gfi_output_values_from_slot),
	    Qslot_value_writer);
    Qwhen_received_value = STATIC_SYMBOL("WHEN-RECEIVED-VALUE",AB_package);
    string_constant_5 = 
	    STATIC_STRING("write to file when variables receive values");
    Qoutput_one_shot_when_activated = 
	    STATIC_SYMBOL("OUTPUT-ONE-SHOT-WHEN-ACTIVATED",AB_package);
    string_constant_6 = STATIC_STRING("write to file when activated");
    Qoutput_one_shot_when_activated_without_interruption = 
	    STATIC_SYMBOL("OUTPUT-ONE-SHOT-WHEN-ACTIVATED-WITHOUT-INTERRUPTION",
	    AB_package);
    string_constant_7 = 
	    STATIC_STRING("write to file when activated, without interruption");
    Qwrite_interval = STATIC_SYMBOL("WRITE-INTERVAL",AB_package);
    string_constant_8 = STATIC_STRING("write to file every ");
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    string_constant_9 = 
	    STATIC_STRING("The slot value writer for gfi-output-file-update-frequency ~\n              received an illegal value: ~a.");
    Qwrite_gfi_output_file_update_frequency_from_slot = 
	    STATIC_SYMBOL("WRITE-GFI-OUTPUT-FILE-UPDATE-FREQUENCY-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gfi_output_file_update_frequency_from_slot,
	    STATIC_FUNCTION(write_gfi_output_file_update_frequency_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qgfi_output_file_update_frequency,
	    SYMBOL_FUNCTION(Qwrite_gfi_output_file_update_frequency_from_slot),
	    Qslot_value_writer);
    Qgfi_input_interface = STATIC_SYMBOL("GFI-INPUT-INTERFACE",AB_package);
    check_if_superior_classes_are_defined(Qgfi_input_interface,
	    list_constant_2);
    string_constant_37 = 
	    STATIC_STRING("1n1m8v83-Oy1o830by83=8y8301y8305y1l8t");
    Qobtain_simple_gensym_string = 
	    STATIC_SYMBOL("OBTAIN-SIMPLE-GENSYM-STRING",AB_package);
    string_constant_38 = 
	    STATIC_STRING("13Oy4z8r831vy831vy8304y8304y00001q1l83Ey1m8p83*iy1l83Fy1l83Hy1l8l1l83-4y000004z8r835By835By8304y8304y08367y001q1l83Ey1m8p83*iy1l");
    string_constant_39 = 
	    STATIC_STRING("83Fy1l83Hy1l8l1l83-4y000004z8r83Cly83Cly8304y8304y08k001p1l83Ey1m8p833Ly1l8l1l8z1l83Cy000004z8r838uy838uy8304y8304y00001p1l83Ey1");
    string_constant_40 = 
	    STATIC_STRING("m8p838uy1l8z1l8l1l83Cy000004z8r83CPy83CPy8304y8304y0834Vy001p1l83Ey1m8p833Ky1l8z1l8l1l83Cy000004z8r83CMy83CMy8304y8304y0833vy001");
    string_constant_41 = 
	    STATIC_STRING("p1l83Ey1m8p833Iy1l8z1l8l1l83Cy000004z8r83CNy83CNy8304y8304y00001p1l83Ey1m8p833Jy1l8z1l8l1l83Cy000004z8r83QJy83QJy8304y8304y08k00");
    string_constant_42 = 
	    STATIC_STRING("1p1l83Ey1m8p833Ly1l8l1l8z1l83Cy000004z8r83Q3y83Q3y8304y8304y00001p1l8l1l83Ey1m8p8330y1l83Ny1l83Hy000004z8r83QLy83QLy8304y8304y00");
    string_constant_43 = 
	    STATIC_STRING("001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83Q9y83Q9y8304y8304y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83Q4y83Q4y8304y8304y00001o1l8l1l83Ey");
    string_constant_44 = 
	    STATIC_STRING("1l83Ny1l83Hy000004z8r83QBy83QBy8304y8304y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QDy83QDy8304y8304y00001o1l8l1l83Ey1l83Ny1l83Hy00");
    string_constant_45 = 
	    STATIC_STRING("0004z8r83QFy83QFy8304y8304y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QGy83QGy8304y8304y0k001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QEy83");
    string_constant_46 = 
	    STATIC_STRING("QEy8304y8304y0k001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QIy83QIy8304y8304y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83Qay83Qay8304y8304y0");
    string_constant_47 = 
	    STATIC_STRING("0001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QAy83QAy8304y8304y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QKy83QKy8304y8304y00001o1l8l1l83E");
    string_constant_48 = 
	    STATIC_STRING("y1l83Ny1l83Hy000004z8r83QHy83QHy8304y8304y00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83QCy83QCy8304y8304y00001o1l8l1l83Ey1l83Ny1l83Hy0");
    string_constant_49 = 
	    STATIC_STRING("00004z8r83=ly83=ly8304y8304y00001o1m8p830Uy1l83-4y1l83Ey1l8l000004z8r83Q5y83Q5y8304y8304y01n83*Ay9k34+y001n1l8l1l83Ey1l83Hy00000");
    string_constant_50 = 
	    STATIC_STRING("4z8r83Q6y83Q6y8304y8304y0k001n1l8l1l83Ey1l83Hy000004z8r83Q8y83Q8y8304y8304y0k001n1l8l1l83Ey1l83Hy000004z8r83Q7y83Q7y8304y8304y0k");
    string_constant_51 = STATIC_STRING("001n1l8l1l83Ey1l83Hy00000");
    string_constant_52 = 
	    STATIC_STRING("13Qy8q1p8304y1l83-Oy1m8v83-Oy1o830by83=8y8301y8305y8t1s831vy01l83Ey1m8p83*iy1l83Fy1l83Hy1l8l83-4y1s835By8367y1l83Ey1m8p83*iy1l83");
    string_constant_53 = 
	    STATIC_STRING("Fy1l83Hy1l8l83-4y1r83Cly8k1l83Ey1m8p833Ly1l8l8z1l83Cy1r838uy01l83Ey1m8p838uy8z1l8l1l83Cy1r83CPy834Vy1l83Ey1m8p833Ky8z1l8l1l83Cy1");
    string_constant_54 = 
	    STATIC_STRING("r83CMy833vy1l83Ey1m8p833Iy8z1l8l1l83Cy1r83CNy01l83Ey1m8p833Jy8z1l8l1l83Cy1r83QJy8k1l83Ey1m8p833Ly1l8l8z1l83Cy1q83Q3y01l83Ey1m8p8");
    string_constant_55 = 
	    STATIC_STRING("330y1l83Ny1l83Hy1p83QLy01l83Ey1l83Ny1l83Hy1p83Q9y01l83Ey1l83Ny1l83Hy1p83Q4y01l83Ey1l83Ny1l83Hy1p83QBy01l83Ey1l83Ny1l83Hy1p83QDy0");
    string_constant_56 = 
	    STATIC_STRING("1l83Ey1l83Ny1l83Hy1p83QFy01l83Ey1l83Ny1l83Hy1p83QGyk1l83Ey1l83Ny1l83Hy1p83QEyk1l83Ey1l83Ny1l83Hy1p83QIy01l83Ey1l83Ny1l83Hy1p83Qa");
    string_constant_57 = 
	    STATIC_STRING("y01l83Ey1l83Ny1l83Hy1p83QAy01l83Ey1l83Ny1l83Hy1p83QKy01l83Ey1l83Ny1l83Hy1p83QHy01l83Ey1l83Ny1l83Hy1p83QCy01l83Ey1l83Ny1l83Hy1q83");
    string_constant_58 = 
	    STATIC_STRING("=ly01m8p830Uy83-4y83Ey8l1o83Q5y1n83*Ay9k34+y1l83Ey83Hy1o83Q6yk1l83Ey83Hy1o83Q8yk1l83Ey83Hy1o83Q7yk1l83Ey83Hy");
    temp = regenerate_optimized_constant(string_constant_37);
    clear_optimized_constants();
    push_optimized_constant(Qobtain_simple_gensym_string);
    temp_1 = regenerate_optimized_constant(list(14,string_constant_38,
	    string_constant_39,string_constant_40,string_constant_41,
	    string_constant_42,string_constant_43,string_constant_44,
	    string_constant_45,string_constant_46,string_constant_47,
	    string_constant_48,string_constant_49,string_constant_50,
	    string_constant_51));
    clear_optimized_constants();
    push_optimized_constant(Qobtain_simple_gensym_string);
    add_class_to_environment(9,Qgfi_input_interface,list_constant_2,Nil,
	    temp,Nil,temp_1,list_constant_2,
	    regenerate_optimized_constant(list(7,string_constant_52,
	    string_constant_53,string_constant_54,string_constant_55,
	    string_constant_56,string_constant_57,string_constant_58)),Nil);
    Qgfi_input_file_buffer = STATIC_SYMBOL("GFI-INPUT-FILE-BUFFER",AB_package);
    Qreclaim_gfi_input_file_buffer_value = 
	    STATIC_SYMBOL("RECLAIM-GFI-INPUT-FILE-BUFFER-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gfi_input_file_buffer_value,
	    STATIC_FUNCTION(reclaim_gfi_input_file_buffer_value,NIL,FALSE,
	    2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qgfi_input_file_buffer,
	    SYMBOL_FUNCTION(Qreclaim_gfi_input_file_buffer_value),
	    Qslot_value_reclaimer);
    Qignore_gfi_input_base_time_qm = 
	    STATIC_SYMBOL("IGNORE-GFI-INPUT-BASE-TIME\?",AB_package);
    Qignore_gfi_input_base_time = 
	    STATIC_SYMBOL("IGNORE-GFI-INPUT-BASE-TIME",AB_package);
    alias_slot_name(3,Qignore_gfi_input_base_time_qm,
	    Qignore_gfi_input_base_time,Qnil);
    Qgfi_input_variables_update_mode = 
	    STATIC_SYMBOL("GFI-INPUT-VARIABLES-UPDATE-MODE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qquote,Qnone);
    list_constant_27 = STATIC_LIST((SI_Long)2L,
	    Qgfi_input_variables_update_mode,list_constant_3);
    Qasynchronous = STATIC_SYMBOL("ASYNCHRONOUS",AB_package);
    list_constant_4 = STATIC_CONS(Qasynchronous,Qnil);
    list_constant_5 = STATIC_CONS(Qquote,list_constant_4);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qquote,Qinput);
    list_constant_7 = STATIC_LIST((SI_Long)2L,list_constant_5,list_constant_6);
    list_constant_28 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgfi_input_variables_update_mode,list_constant_7,list_constant_4);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qquote,Qcm);
    Qignoring = STATIC_SYMBOL("IGNORING",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qquote,Qignoring);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qquote,Qthe);
    Qdata = STATIC_SYMBOL("DATA",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qquote,Qdata);
    Qserver = STATIC_SYMBOL("SERVER",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qquote,Qserver);
    list_constant_13 = STATIC_LIST((SI_Long)7L,list_constant_5,
	    list_constant_6,list_constant_8,list_constant_9,
	    list_constant_10,list_constant_11,list_constant_12);
    Qasynchronous_ignoring_data_server = 
	    STATIC_SYMBOL("ASYNCHRONOUS-IGNORING-DATA-SERVER",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)3L,
	    Qgfi_input_variables_update_mode,list_constant_13,
	    Qasynchronous_ignoring_data_server);
    Qon = STATIC_SYMBOL("ON",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qquote,Qon);
    Qrequest = STATIC_SYMBOL("REQUEST",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qquote,Qrequest);
    Qpreserving = STATIC_SYMBOL("PRESERVING",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qquote,Qpreserving);
    Qtime_stamps = STATIC_SYMBOL("TIME-STAMPS",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qquote,Qtime_stamps);
    list_constant_18 = STATIC_LIST((SI_Long)5L,list_constant_6,
	    list_constant_14,list_constant_15,list_constant_16,
	    list_constant_17);
    Qon_request = STATIC_SYMBOL("ON-REQUEST",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)3L,
	    Qgfi_input_variables_update_mode,list_constant_18,Qon_request);
    Qsample_and_hold = STATIC_SYMBOL("SAMPLE-AND-HOLD",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qquote,Qsample_and_hold);
    list_constant_20 = STATIC_LIST((SI_Long)4L,list_constant_6,
	    list_constant_14,list_constant_15,list_constant_19);
    Qon_request_sample_and_hold = 
	    STATIC_SYMBOL("ON-REQUEST-SAMPLE-AND-HOLD",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)3L,
	    Qgfi_input_variables_update_mode,list_constant_20,
	    Qon_request_sample_and_hold);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qquote,Qwhen);
    Qactivated = STATIC_SYMBOL("ACTIVATED",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qquote,Qactivated);
    list_constant_23 = STATIC_LIST((SI_Long)3L,list_constant_6,
	    list_constant_21,list_constant_22);
    Qinput_one_shot_when_activated = 
	    STATIC_SYMBOL("INPUT-ONE-SHOT-WHEN-ACTIVATED",AB_package);
    list_constant_32 = STATIC_LIST((SI_Long)3L,
	    Qgfi_input_variables_update_mode,list_constant_23,
	    Qinput_one_shot_when_activated);
    Qwithout = STATIC_SYMBOL("WITHOUT",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qquote,Qwithout);
    Qinterruption = STATIC_SYMBOL("INTERRUPTION",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qquote,Qinterruption);
    list_constant_26 = STATIC_LIST((SI_Long)6L,list_constant_6,
	    list_constant_21,list_constant_22,list_constant_8,
	    list_constant_24,list_constant_25);
    Qinput_one_shot_when_activated_without_interruption = 
	    STATIC_SYMBOL("INPUT-ONE-SHOT-WHEN-ACTIVATED-WITHOUT-INTERRUPTION",
	    AB_package);
    list_constant_33 = STATIC_LIST((SI_Long)3L,
	    Qgfi_input_variables_update_mode,list_constant_26,
	    Qinput_one_shot_when_activated_without_interruption);
    list_constant_34 = STATIC_LIST((SI_Long)7L,list_constant_27,
	    list_constant_28,list_constant_29,list_constant_30,
	    list_constant_31,list_constant_32,list_constant_33);
    add_grammar_rules_function(list_constant_34);
    Qwrite_ignore_gfi_input_base_time_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-IGNORE-GFI-INPUT-BASE-TIME\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_ignore_gfi_input_base_time_qm_from_slot,
	    STATIC_FUNCTION(write_ignore_gfi_input_base_time_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qignore_gfi_input_base_time_qm,
	    SYMBOL_FUNCTION(Qwrite_ignore_gfi_input_base_time_qm_from_slot),
	    Qslot_value_writer);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    list_constant_35 = 
	    STATIC_CONS(Qinput_one_shot_when_activated_without_interruption,
	    Qnil);
    list_constant = STATIC_LIST_STAR((SI_Long)3L,
	    Qasynchronous_ignoring_data_server,
	    Qinput_one_shot_when_activated,list_constant_35);
    Qgfi_input_ignore_data_server_qm = 
	    STATIC_SYMBOL("GFI-INPUT-IGNORE-DATA-SERVER\?",AB_package);
    array_constant_11 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)18L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)27L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)30L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)34L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)35L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)36L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)40L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)41L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)42L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)43L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)46L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)47L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)17L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)26L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)32L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)36L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)37L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)47L,(SI_Long)57344L);
    array_constant_15 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)19L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)20L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)21L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)26L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)27L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)28L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)31L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)39L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)23L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)20L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)31L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)34L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)35L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)36L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)37L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)39L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)40L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)41L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)46L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)47L,(SI_Long)57344L);
    string_constant_10 = 
	    STATIC_STRING("The attribute gfi-input-variables-update-mode contains ~\n                an illegal value ~a.");
    Qwrite_gfi_input_variables_update_mode_from_slot = 
	    STATIC_SYMBOL("WRITE-GFI-INPUT-VARIABLES-UPDATE-MODE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gfi_input_variables_update_mode_from_slot,
	    STATIC_FUNCTION(write_gfi_input_variables_update_mode_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qgfi_input_variables_update_mode,
	    SYMBOL_FUNCTION(Qwrite_gfi_input_variables_update_mode_from_slot),
	    Qslot_value_writer);
    Qcompile_gfi_input_variables_update_mode_for_slot = 
	    STATIC_SYMBOL("COMPILE-GFI-INPUT-VARIABLES-UPDATE-MODE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_gfi_input_variables_update_mode_for_slot,
	    STATIC_FUNCTION(compile_gfi_input_variables_update_mode_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qgfi_input_variables_update_mode,
	    SYMBOL_FUNCTION(Qcompile_gfi_input_variables_update_mode_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgfi_input_variables_update_mode,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qgfi_data_service = STATIC_SYMBOL("GFI-DATA-SERVICE",AB_package);
    list_constant_36 = STATIC_CONS(Qvariable,Qnil);
    check_if_superior_classes_are_defined(Qgfi_data_service,list_constant_36);
    string_constant_59 = 
	    STATIC_STRING("1q1l8t1m830ky83*dy1m8v83*dy1l83-8y1l83Iy1l83Ly");
    string_constant_60 = 
	    STATIC_STRING("1o4z8r83*My83*My838ty838ty083CLy001o1l8o1l8l1m8p83*My1l8z000004z8r83COy83COy838ty838ty00001p1l83Ey1m8p838vy1l8z1l8l1l83Cy000004z");
    string_constant_61 = 
	    STATIC_STRING("8r83QMy83QMy838ty838ty00001o1l8l1l83Ey1l83Ny1l83Hy000004z8r83Qby83Qby838ty838ty00001o1l8l1l83Ey1l83Ny1l83Hy00000");
    string_constant_62 = 
	    STATIC_STRING("1q8q1s838ty1l83*dy8t1m830ky83*dy1m8v83*dy83-8y83Iy83Ly1p83*My83CLy1l8o1l8l1m8p83*My1r83COy01l83Ey1m8p838vy8z1l8l1l83Cy1p83QMy01l");
    string_constant_63 = 
	    STATIC_STRING("83Ey1l83Ny1l83Hy1p83Qby01l83Ey1l83Ny1l83Hy");
    temp = regenerate_optimized_constant(string_constant_59);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_60,
	    string_constant_61));
    add_class_to_environment(9,Qgfi_data_service,list_constant_36,Nil,temp,
	    Nil,temp_1,list_constant_36,
	    regenerate_optimized_constant(LIST_2(string_constant_62,
	    string_constant_63)),Nil);
    Qgfi_input_interface_object = 
	    STATIC_SYMBOL("GFI-INPUT-INTERFACE-OBJECT",AB_package);
    Qgfi_interface_object = STATIC_SYMBOL("GFI-INTERFACE-OBJECT",AB_package);
    Qput_gfi_interface_object_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-GFI-INTERFACE-OBJECT-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_interface_object_where_slot_is_absent,
	    STATIC_FUNCTION(put_gfi_interface_object_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qgfi_interface_object,
	    SYMBOL_FUNCTION(Qput_gfi_interface_object_where_slot_is_absent),
	    Qabsent_slot_putter);
    string_constant_64 = STATIC_STRING("1m1m838vy1m9k83Zy1m838vy833ny");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_64));
    Qcompile_gfi_interface_object_for_slot = 
	    STATIC_SYMBOL("COMPILE-GFI-INTERFACE-OBJECT-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_gfi_interface_object_for_slot,
	    STATIC_FUNCTION(compile_gfi_interface_object_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qgfi_interface_object,
	    SYMBOL_FUNCTION(Qcompile_gfi_interface_object_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgfi_interface_object,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_gfi_interface_object_from_slot = 
	    STATIC_SYMBOL("WRITE-GFI-INTERFACE-OBJECT-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gfi_interface_object_from_slot,
	    STATIC_FUNCTION(write_gfi_interface_object_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qgfi_interface_object,
	    SYMBOL_FUNCTION(Qwrite_gfi_interface_object_from_slot),
	    Qslot_value_writer);
    Qgfi_data_server = STATIC_SYMBOL("GFI-DATA-SERVER",AB_package);
    string_constant_65 = STATIC_STRING("GFI data server");
    def_data_server_pretty_printer(Qgfi_data_server,string_constant_65);
}
