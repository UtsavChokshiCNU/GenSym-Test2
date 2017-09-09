/* grphdf.c
 * Input file:  graph-def.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "grphdf.h"


static Object Qfloat_array;        /* float-array */

static Object Qtext;               /* text */

static Object Qinterval;           /* interval */

static Object Qseconds;            /* seconds */

/* EVALUATION-VALUE-TO-FRAME-LIKE-VALUE-PROPERTY */
Object evaluation_value_to_frame_like_value_property(evaluation_value,
	    type_specification,style)
    Object evaluation_value, type_specification, style;
{
    Object value, new_long, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float;
    SI_int64 aref_new_value;
    double aref_new_value_1;

    x_note_fn_call(175,0);
    if (type_specification_subtype_p(type_specification,Qnumber)) {
	value = evaluation_value_value(evaluation_value);
	if (FIXNUMP(value));
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    value = note_use_of_managed_long_in_phrase(new_long);
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
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
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    value = note_use_of_managed_float_in_phrase(new_float);
	}
    }
    else if (type_specification_subtype_p(type_specification,Qsymbol))
	value = evaluation_value;
    else if (type_specification_subtype_p(type_specification,Qtext))
	value = copy_text_string(evaluation_value);
    else
	value = error((SI_Long)1L,
		"unsupported frame-like-value-property type-specification");
    if (EQ(style,Qinterval))
	return phrase_cons(value,Qseconds);
    else
	return VALUES_1(value);
}

static Object Qtruth_value;        /* truth-value */

/* FRAME-LIKE-VALUE-PROPERTY-TO-EVALUATION-VALUE */
Object frame_like_value_property_to_evaluation_value(slot_value,
	    type_specification,style)
    Object slot_value, type_specification, style;
{
    Object value, amf_available_array_cons_qm, amf_array, temp, temp_1;
    Object amf_result, new_float, gensymed_symbol;
    double aref_new_value;

    x_note_fn_call(175,1);
    value = EQ(style,Qinterval) ? CAR(slot_value) : slot_value;
    if (FIXNUMP(value))
	return VALUES_1(value);
    else if ( !TRUEP(value))
	return VALUES_1(Evaluation_false_value);
    else if (EQ(value,T))
	return VALUES_1(Evaluation_true_value);
    else if (SYMBOLP(value))
	return VALUES_1(value);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	return copy_managed_float(value);
    else if (FLOATP(value)) {
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return VALUES_1(new_float);
    }
    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	return copy_managed_long(value);
    else if (INLINE_LONG_P(value) != (SI_Long)0L)
	return make_evaluation_long(value);
    else if (text_string_p(value))
	return copy_as_wide_string(value);
    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	gensymed_symbol = M_CAR(value);
	if (FIXNUM_EQ(gensymed_symbol,Truth))
	    return VALUES_1(Evaluation_true_value);
	else if (FIXNUM_EQ(gensymed_symbol,Falsity))
	    return VALUES_1(Evaluation_false_value);
	else
	    return eval_cons_1(gensymed_symbol,Qtruth_value);
    }
    else
	return error((SI_Long)2L,
		"Bad type ~a for make-evaluation-value-based-on-type.",
		type_of(value));
}

static Object string_constant;     /* "Unknown color requested: ~NV" */

/* COMPILE-EXTANT-COLOR-OR-METACOLOR-FOR-SLOT */
Object compile_extant_color_or_metacolor_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,2);
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
    if (color_or_metacolor_p(parse_result))
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant,parse_result);
	return VALUES_2(temp,temp_1);
    }
}

static Object list_constant;       /* # */

static Object Qnone;               /* none */

/* EXTANT-COLOR-OR-METACOLOR-EVALUATION-SETTER */
Object extant_color_or_metacolor_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,3);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qsymbol,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_extant_color_or_metacolor_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qnone))
	result = VALUES_1(Nil);
    else
	result = VALUES_1(evaluation_value);
  end_extant_color_or_metacolor_evaluation_setter:
    return result;
}

/* EXTANT-COLOR-OR-METACOLOR-EVALUATION-GETTER */
Object extant_color_or_metacolor_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(175,4);
    temp = slot_value;
    if (temp);
    else
	temp = Qnone;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-EXTANT-COLOR-OR-METACOLOR-FROM-SLOT */
Object write_extant_color_or_metacolor_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(175,5);
    return twrite_color(slot_value);
}

static Object string_constant_1;   /* "~a" */

/* COMPILE-2D-SHADING-TARGET-SPEC-FOR-SLOT */
Object compile_2d_shading_target_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,6);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    if (T)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_1,
		reason_for_bad_phrase);
	return VALUES_2(temp,temp_1);
    }
}

static Object Qconstant;           /* constant */

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

/* WRITE-2D-SHADING-TARGET-SPEC-FROM-SLOT */
Object write_2d_shading_target_spec_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist;

    x_note_fn_call(175,7);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qconstant) && EQ(sub_key,FIX((SI_Long)1L)))
	return twrite(array_constant);
    else if (EQ(key_symbol_1,Qconstant) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(array_constant_1);
    else if (EQ(key_symbol_1,Qnone) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(array_constant_2);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object Q2d_shading_target_spec;  /* 2d-shading-target-spec */

static Object Qtop;                /* top */

static Object Qbottom;             /* bottom */

static Object Qtarget;             /* target */

static Object string_constant_2;   /* "shading target, ~a, must be TOP, or BOTTOM" */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_3;   /* "~NT " */

static Object string_constant_4;   /* "~NV must be one of the following types: ~a" */

/* 2D-SHADING-TARGET-SPEC-EVALUATION-SETTER */
Object n_2d_shading_target_spec_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, symbol;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,8);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_1))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_2,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_shading_target_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_3))
	result = make_frame_like_category_parse_result(Q2d_shading_target_spec,
		Qnone,Nil);
    else if (type_specification_type_p(gensymed_symbol,Qsymbol)) {
	symbol = evaluation_value;
	if (EQ(symbol,Qtop) || EQ(symbol,Qbottom))
	    result = make_frame_like_category_parse_result(Q2d_shading_target_spec,
		    Qconstant,phrase_list_2(Qtarget,symbol));
	else if (EQ(symbol,Qnone))
	    result = make_frame_like_category_parse_result(Q2d_shading_target_spec,
		    Qnone,Nil);
	else {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(1,string_constant_2);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else {
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
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_3,list_constant_3);
		  tformat(2,string_constant_3,Qsymbol);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_4,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_2d_shading_target_spec_evaluation_setter:
    return result;
}

/* 2D-SHADING-TARGET-SPEC-EVALUATION-GETTER */
Object n_2d_shading_target_spec_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(175,9);
    temp = CAR(slot_value);
    if (EQ(temp,Qnone))
	temp = Qnone;
    else if (EQ(temp,Qconstant))
	temp = getf(CDDR(slot_value),Qtarget,_);
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMPILE-2D-PLOT-MARKER-SHAPE-FOR-SLOT */
Object compile_2d_plot_marker_shape_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,10);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    if (T)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_1,
		reason_for_bad_phrase);
	return VALUES_2(temp,temp_1);
    }
}

static Object Qcustom;             /* custom */

static Object array_constant_3;    /* # */

static Object string_constant_5;   /* " " */

static Object array_constant_4;    /* # */

static Object Qicon_class;         /* icon-class */

static Object Qab_standard;        /* standard */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

/* WRITE-2D-PLOT-MARKER-SHAPE-FROM-SLOT */
Object write_2d_plot_marker_shape_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist;

    x_note_fn_call(175,11);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qcustom) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_3);
	twrite(string_constant_5);
	twrite(array_constant_4);
	twrite(string_constant_5);
	return twrite(getf(plist,Qicon_class,_));
    }
    else if (EQ(key_symbol_1,Qab_standard) && EQ(sub_key,FIX((SI_Long)3L))) {
	twrite(array_constant_5);
	twrite(string_constant_5);
	return twrite(array_constant_6);
    }
    else if (EQ(key_symbol_1,Qab_standard) && EQ(sub_key,FIX((SI_Long)2L)))
	return twrite(array_constant_7);
    else if (EQ(key_symbol_1,Qab_standard) && EQ(sub_key,FIX((SI_Long)1L)))
	return twrite(array_constant_8);
    else if (EQ(key_symbol_1,Qab_standard) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(array_constant_9);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object Qstandard_shape;     /* standard-shape */

static Object Q2d_plot_marker_shape;  /* 2d-plot-marker-shape */

static Object Qshape;              /* shape */

static Object Qicon_of_class;      /* icon-of-class */

/* 2D-PLOT-MARKER-SHAPE-EVALUATION-SETTER */
Object n_2d_plot_marker_shape_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, standard_shape_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,12);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_4))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_5,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_plot_marker_shape_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    standard_shape_qm = estructure_slot(evaluation_value,Qstandard_shape,Nil);
    if (standard_shape_qm)
	result = make_frame_like_category_parse_result(Q2d_plot_marker_shape,
		Qab_standard,phrase_list_2(Qshape,standard_shape_qm));
    else
	result = make_frame_like_category_parse_result(Q2d_plot_marker_shape,
		Qcustom,phrase_list_2(Qicon_class,
		estructure_slot(evaluation_value,Qicon_of_class,Nil)));
  end_2d_plot_marker_shape_evaluation_setter:
    return result;
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qab_structure;       /* structure */

/* 2D-PLOT-MARKER-SHAPE-EVALUATION-GETTER */
Object n_2d_plot_marker_shape_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(175,13);
    temp = CAR(slot_value);
    if (EQ(temp,Qab_standard)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qstandard_shape;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qstandard_shape;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = getf(CDDR(slot_value),Qshape,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = getf(CDDR(slot_value),Qshape,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qcustom)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qicon_of_class;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qicon_of_class;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = getf(CDDR(slot_value),Qicon_class,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = getf(CDDR(slot_value),Qicon_class,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMPILE-2D-LOCATION-SPEC-FOR-SLOT */
Object compile_2d_location_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,14);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    if (T)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_1,
		reason_for_bad_phrase);
	return VALUES_2(temp,temp_1);
    }
}

static Object Qrelative_to_window;  /* relative-to-window */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

/* WRITE-2D-LOCATION-SPEC-FROM-SLOT */
Object write_2d_location_spec_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist;

    x_note_fn_call(175,15);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qrelative_to_window) && EQ(sub_key,FIX((SI_Long)1L))) {
	twrite(array_constant_10);
	twrite(string_constant_5);
	twrite(array_constant_11);
	twrite(string_constant_5);
	return twrite(array_constant_12);
    }
    else if (EQ(key_symbol_1,Qrelative_to_window) && EQ(sub_key,
	    FIX((SI_Long)0L))) {
	twrite(array_constant_13);
	twrite(string_constant_5);
	twrite(array_constant_11);
	twrite(string_constant_5);
	return twrite(array_constant_12);
    }
    else if (EQ(key_symbol_1,Qnone) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(array_constant_2);
    else
	return VALUES_1(Qnil);
}

static Object Qabsolute;           /* absolute */

static Object Qcolor;              /* color */

static Object string_constant_6;   /* "Unknown color requested" */

/* COMPILE-2D-TICKMARK-LABEL-COLOR-FOR-SLOT */
Object compile_2d_tickmark_label_color_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp_1, temp_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,16);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    gensymed_symbol_1 = EQ(CAR(parse_result),Qabsolute) ? 
	    getf(CDDR(parse_result),Qcolor,_) : Qnil;
    if (gensymed_symbol_1) {
	if (color_or_metacolor_p(gensymed_symbol_1))
	    temp = TRUEP(T);
	else {
	    reason_for_bad_phrase = copy_text_string(string_constant_6);
	    temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(T);
    if (temp)
	return VALUES_1(parse_result);
    else {
	temp_1 = Bad_phrase;
	temp_2 = tformat_text_string(2,string_constant_1,
		reason_for_bad_phrase);
	return VALUES_2(temp_1,temp_2);
    }
}

static Object Qmatching;           /* matching */

static Object array_constant_14;   /* # */

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

/* WRITE-2D-TICKMARK-LABEL-COLOR-FROM-SLOT */
Object write_2d_tickmark_label_color_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist;

    x_note_fn_call(175,17);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qmatching) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_14);
	twrite(string_constant_5);
	twrite(array_constant_15);
	twrite(string_constant_5);
	return twrite(array_constant_16);
    }
    else if (EQ(key_symbol_1,Qabsolute) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(getf(plist,Qcolor,_));
    else
	return VALUES_1(Qnil);
}

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object Qlabel_color_type;   /* label-color-type */

static Object Qmatching_plot_color;  /* matching-plot-color */

static Object Q2d_tickmark_label_color;  /* 2d-tickmark-label-color */

static Object Qplot_color;         /* plot-color */

/* 2D-TICKMARK-LABEL-COLOR-EVALUATION-SETTER */
Object n_2d_tickmark_label_color_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, label_color_type;
    Object color;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,18);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_6))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_7,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_tickmark_label_color_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    label_color_type = estructure_slot(evaluation_value,Qlabel_color_type,Nil);
    if (EQ(label_color_type,Qmatching_plot_color))
	result = make_frame_like_category_parse_result(Q2d_tickmark_label_color,
		Qmatching,phrase_list_2(Qtarget,Qplot_color));
    else if (EQ(label_color_type,Qabsolute)) {
	color = estructure_slot(evaluation_value,Qcolor,Nil);
	if (color)
	    result = make_frame_like_category_parse_result(Q2d_tickmark_label_color,
		    Qabsolute,phrase_list_2(Qcolor,color));
	else {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(2,string_constant,color);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else
	result = VALUES_1(Qnil);
  end_2d_tickmark_label_color_evaluation_setter:
    return result;
}

/* 2D-TICKMARK-LABEL-COLOR-EVALUATION-GETTER */
Object n_2d_tickmark_label_color_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(175,19);
    temp = CAR(slot_value);
    if (EQ(temp,Qabsolute)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel_color_type;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlabel_color_type;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qabsolute;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qabsolute;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qcolor;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qcolor;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = getf(CDDR(slot_value),Qcolor,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = getf(CDDR(slot_value),Qcolor,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qmatching)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel_color_type;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlabel_color_type;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qmatching_plot_color;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qmatching_plot_color;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object array_constant_17;   /* # */

/* COMPILE-2D-TIME-SPAN-SPEC-FOR-SLOT */
Object compile_2d_time_span_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp, prop_value_qm, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,20);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    if (EQ(CAR(parse_result),Qinterval)) {
	temp = getf(CDDR(parse_result),Qlength,_);
	prop_value_qm = CAR(temp);
    }
    else
	prop_value_qm = Nil;
    if (prop_value_qm) {
	if (check_frame_like_value_range(prop_value_qm,FIX((SI_Long)1L),Nil))
	    temp_1 = TRUEP(T);
	else {
	    reason_for_bad_phrase = 
		    copy_constant_wide_string_given_length(array_constant_17,
		    FIX((SI_Long)42L));
	    temp_1 = TRUEP(Nil);
	}
    }
    else
	temp_1 = TRUEP(T);
    if (temp_1)
	return VALUES_1(parse_result);
    else {
	temp_2 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_1,reason_for_bad_phrase);
	return VALUES_2(temp_2,temp);
    }
}

static Object Qall_history;        /* all-history */

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

static Object array_constant_20;   /* # */

/* WRITE-2D-TIME-SPAN-SPEC-FROM-SLOT */
Object write_2d_time_span_spec_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist, temp;

    x_note_fn_call(175,21);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qinterval) && EQ(sub_key,FIX((SI_Long)0L))) {
	temp = getf(plist,Qlength,_);
	return print_constant(2,CAR(temp),Qseconds);
    }
    else if (EQ(key_symbol_1,Qall_history) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_18);
	twrite(string_constant_5);
	twrite(array_constant_19);
	twrite(string_constant_5);
	return twrite(array_constant_20);
    }
    else
	return VALUES_1(Qnil);
}

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

static Object Qdata_window_time_span_mode;  /* data-window-time-span-mode */

static Object Qshow_all_history;   /* show-all-history */

static Object Q2d_time_span_spec;  /* 2d-time-span-spec */

static Object Qnumber_of_seconds;  /* number-of-seconds */

static Object string_constant_7;   /* "must specify all of (NUMBER-OF-SECONDS)" */

/* 2D-TIME-SPAN-SPEC-EVALUATION-SETTER */
Object n_2d_time_span_spec_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object data_window_time_span_mode, number_of_seconds;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,22);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_8))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_9,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_time_span_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    data_window_time_span_mode = estructure_slot(evaluation_value,
	    Qdata_window_time_span_mode,Nil);
    if (EQ(data_window_time_span_mode,Qshow_all_history))
	result = make_frame_like_category_parse_result(Q2d_time_span_spec,
		Qall_history,Nil);
    else if (EQ(data_window_time_span_mode,Qinterval)) {
	number_of_seconds = estructure_slot(evaluation_value,
		Qnumber_of_seconds,Nil);
	if (number_of_seconds)
	    result = make_frame_like_category_parse_result(Q2d_time_span_spec,
		    Qinterval,phrase_list_2(Qlength,
		    evaluation_value_to_frame_like_value_property(number_of_seconds,
		    Qinteger,Qinterval)));
	else {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(string_constant_7);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else
	result = VALUES_1(Qnil);
  end_2d_time_span_spec_evaluation_setter:
    return result;
}

/* 2D-TIME-SPAN-SPEC-EVALUATION-GETTER */
Object n_2d_time_span_spec_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(175,23);
    temp = CAR(slot_value);
    if (EQ(temp,Qall_history)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
		    Qdata_window_time_span_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qdata_window_time_span_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qshow_all_history;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qshow_all_history;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qinterval)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
		    Qdata_window_time_span_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qdata_window_time_span_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qinterval;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qinterval;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qnumber_of_seconds;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qnumber_of_seconds;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    frame_like_value_property_to_evaluation_value(getf(CDDR(slot_value),
		    Qlength,_),Qinteger,Qinterval);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = 
		    frame_like_value_property_to_evaluation_value(getf(CDDR(slot_value),
		    Qlength,_),Qinteger,Qinterval);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMPILE-2D-TOTAL-TIME-SPAN-SPEC-FOR-SLOT */
Object compile_2d_total_time_span_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp, prop_value_qm, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,24);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    if (EQ(CAR(parse_result),Qinterval)) {
	temp = getf(CDDR(parse_result),Qlength,_);
	prop_value_qm = CAR(temp);
    }
    else
	prop_value_qm = Nil;
    if (prop_value_qm) {
	if (check_frame_like_value_range(prop_value_qm,FIX((SI_Long)1L),Nil))
	    temp_1 = TRUEP(T);
	else {
	    reason_for_bad_phrase = 
		    copy_constant_wide_string_given_length(array_constant_17,
		    FIX((SI_Long)42L));
	    temp_1 = TRUEP(Nil);
	}
    }
    else
	temp_1 = TRUEP(T);
    if (temp_1)
	return VALUES_1(parse_result);
    else {
	temp_2 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_1,reason_for_bad_phrase);
	return VALUES_2(temp_2,temp);
    }
}

static Object Qdata_window;        /* data-window */

static Object array_constant_21;   /* # */

static Object array_constant_22;   /* # */

/* WRITE-2D-TOTAL-TIME-SPAN-SPEC-FROM-SLOT */
Object write_2d_total_time_span_spec_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist, temp;

    x_note_fn_call(175,25);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qinterval) && EQ(sub_key,FIX((SI_Long)0L))) {
	temp = getf(plist,Qlength,_);
	return print_constant(2,CAR(temp),Qseconds);
    }
    else if (EQ(key_symbol_1,Qdata_window) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_21);
	twrite(string_constant_5);
	twrite(array_constant_22);
	twrite(string_constant_5);
	twrite(array_constant_11);
	twrite(string_constant_5);
	return twrite(array_constant_12);
    }
    else
	return VALUES_1(Qnil);
}

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

static Object Qtotal_time_span_mode;  /* total-time-span-mode */

static Object Qsame_as_data_window;  /* same-as-data-window */

static Object Q2d_total_time_span_spec;  /* 2d-total-time-span-spec */

/* 2D-TOTAL-TIME-SPAN-SPEC-EVALUATION-SETTER */
Object n_2d_total_time_span_spec_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object total_time_span_mode, number_of_seconds;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,26);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_10))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_11,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_total_time_span_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    total_time_span_mode = estructure_slot(evaluation_value,
	    Qtotal_time_span_mode,Nil);
    if (EQ(total_time_span_mode,Qsame_as_data_window))
	result = make_frame_like_category_parse_result(Q2d_total_time_span_spec,
		Qdata_window,Nil);
    else if (EQ(total_time_span_mode,Qinterval)) {
	number_of_seconds = estructure_slot(evaluation_value,
		Qnumber_of_seconds,Nil);
	if (number_of_seconds)
	    result = make_frame_like_category_parse_result(Q2d_total_time_span_spec,
		    Qinterval,phrase_list_2(Qlength,
		    evaluation_value_to_frame_like_value_property(number_of_seconds,
		    Qinteger,Qinterval)));
	else {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(string_constant_7);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else
	result = VALUES_1(Qnil);
  end_2d_total_time_span_spec_evaluation_setter:
    return result;
}

/* 2D-TOTAL-TIME-SPAN-SPEC-EVALUATION-GETTER */
Object n_2d_total_time_span_spec_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(175,27);
    temp = CAR(slot_value);
    if (EQ(temp,Qdata_window)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtotal_time_span_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qtotal_time_span_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qsame_as_data_window;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qsame_as_data_window;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qinterval)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtotal_time_span_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qtotal_time_span_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qinterval;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qinterval;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qnumber_of_seconds;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qnumber_of_seconds;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    frame_like_value_property_to_evaluation_value(getf(CDDR(slot_value),
		    Qlength,_),Qinteger,Qinterval);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = 
		    frame_like_value_property_to_evaluation_value(getf(CDDR(slot_value),
		    Qlength,_),Qinteger,Qinterval);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMPILE-2D-END-TIME-SPEC-FOR-SLOT */
Object compile_2d_end_time_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,28);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    if (T)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_1,
		reason_for_bad_phrase);
	return VALUES_2(temp,temp_1);
    }
}

static Object Qstart_relative;     /* start-relative */

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

static Object Qlast_sample;        /* last-sample */

static Object array_constant_25;   /* # */

static Object array_constant_26;   /* # */

static Object Qcurrent_time;       /* current-time */

static Object array_constant_27;   /* # */

/* WRITE-2D-END-TIME-SPEC-FROM-SLOT */
Object write_2d_end_time_spec_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist, temp;

    x_note_fn_call(175,29);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qstart_relative) && EQ(sub_key,FIX((SI_Long)0L))) {
	temp = getf(plist,Qinterval,_);
	print_constant(2,CAR(temp),Qseconds);
	twrite(string_constant_5);
	twrite(array_constant_23);
	twrite(string_constant_5);
	return twrite(array_constant_24);
    }
    else if (EQ(key_symbol_1,Qlast_sample) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_25);
	twrite(string_constant_5);
	return twrite(array_constant_26);
    }
    else if (EQ(key_symbol_1,Qcurrent_time) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_5);
	twrite(string_constant_5);
	return twrite(array_constant_27);
    }
    else
	return VALUES_1(Qnil);
}

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

static Object Qend_time_mode;      /* end-time-mode */

static Object Q2d_end_time_spec;   /* 2d-end-time-spec */

/* 2D-END-TIME-SPEC-EVALUATION-SETTER */
Object n_2d_end_time_spec_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, end_time_mode;
    Object number_of_seconds;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,30);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_12))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_13,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_end_time_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    end_time_mode = estructure_slot(evaluation_value,Qend_time_mode,Nil);
    if (EQ(end_time_mode,Qcurrent_time))
	result = make_frame_like_category_parse_result(Q2d_end_time_spec,
		Qcurrent_time,Nil);
    else if (EQ(end_time_mode,Qlast_sample))
	result = make_frame_like_category_parse_result(Q2d_end_time_spec,
		Qlast_sample,Nil);
    else if (EQ(end_time_mode,Qstart_relative)) {
	number_of_seconds = estructure_slot(evaluation_value,
		Qnumber_of_seconds,Nil);
	if (number_of_seconds)
	    result = make_frame_like_category_parse_result(Q2d_end_time_spec,
		    Qstart_relative,phrase_list_2(Qinterval,
		    evaluation_value_to_frame_like_value_property(number_of_seconds,
		    Qinteger,Qinterval)));
	else {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(string_constant_7);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else
	result = VALUES_1(Qnil);
  end_2d_end_time_spec_evaluation_setter:
    return result;
}

/* 2D-END-TIME-SPEC-EVALUATION-GETTER */
Object n_2d_end_time_spec_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(175,31);
    temp = CAR(slot_value);
    if (EQ(temp,Qcurrent_time)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qend_time_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qend_time_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qcurrent_time;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qcurrent_time;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qlast_sample)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qend_time_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qend_time_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qlast_sample;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qlast_sample;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qstart_relative)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qend_time_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qend_time_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qstart_relative;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qstart_relative;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qnumber_of_seconds;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qnumber_of_seconds;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    frame_like_value_property_to_evaluation_value(getf(CDDR(slot_value),
		    Qinterval,_),Qinteger,Qinterval);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = 
		    frame_like_value_property_to_evaluation_value(getf(CDDR(slot_value),
		    Qinterval,_),Qinteger,Qinterval);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_8;   /* "Must use an interval between 1 seconds and one-day" */

/* COMPILE-2D-SCROLLING-ALIGNMENT-SPEC-FOR-SLOT */
Object compile_2d_scrolling_alignment_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp, prop_value_qm, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,32);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    if (EQ(CAR(parse_result),Qinterval)) {
	temp = getf(CDDR(parse_result),Qlength,_);
	prop_value_qm = CAR(temp);
    }
    else
	prop_value_qm = Nil;
    if (prop_value_qm) {
	if (check_frame_like_value_range(prop_value_qm,FIX((SI_Long)1L),
		FIX((SI_Long)86400L)))
	    temp_1 = TRUEP(T);
	else {
	    reason_for_bad_phrase = copy_text_string(string_constant_8);
	    temp_1 = TRUEP(Nil);
	}
    }
    else
	temp_1 = TRUEP(T);
    if (temp_1)
	return VALUES_1(parse_result);
    else {
	temp_2 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_1,reason_for_bad_phrase);
	return VALUES_2(temp_2,temp);
    }
}

/* WRITE-2D-SCROLLING-ALIGNMENT-SPEC-FROM-SLOT */
Object write_2d_scrolling_alignment_spec_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist, temp;

    x_note_fn_call(175,33);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qinterval) && EQ(sub_key,FIX((SI_Long)0L))) {
	temp = getf(plist,Qlength,_);
	return print_constant(2,CAR(temp),Qseconds);
    }
    else if (EQ(key_symbol_1,Qnone) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(array_constant_2);
    else
	return VALUES_1(Qnil);
}

static Object string_constant_9;   /* "Must use an interval between 1 second and one-day" */

/* COMPILE-2D-TIME-AXIS-TICKMARK-FREQUENCY-SPEC-FOR-SLOT */
Object compile_2d_time_axis_tickmark_frequency_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp, prop_value_qm, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,34);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    if (EQ(CAR(parse_result),Qinterval)) {
	temp = getf(CDDR(parse_result),Qlength,_);
	prop_value_qm = CAR(temp);
    }
    else
	prop_value_qm = Nil;
    if (prop_value_qm) {
	if (check_frame_like_value_range(prop_value_qm,FIX((SI_Long)1L),
		FIX((SI_Long)86400L)))
	    temp_1 = TRUEP(T);
	else {
	    reason_for_bad_phrase = copy_text_string(string_constant_9);
	    temp_1 = TRUEP(Nil);
	}
    }
    else
	temp_1 = TRUEP(T);
    if (temp_1)
	return VALUES_1(parse_result);
    else {
	temp_2 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_1,reason_for_bad_phrase);
	return VALUES_2(temp_2,temp);
    }
}

static Object array_constant_28;   /* # */

static Object Qsynchronized;       /* synchronized */

static Object array_constant_29;   /* # */

/* WRITE-2D-TIME-AXIS-TICKMARK-FREQUENCY-SPEC-FROM-SLOT */
Object write_2d_time_axis_tickmark_frequency_spec_from_slot(slot_value,
	    gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist, temp;

    x_note_fn_call(175,35);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qinterval) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_28);
	twrite(string_constant_5);
	temp = getf(plist,Qlength,_);
	return print_constant(2,CAR(temp),Qseconds);
    }
    else if (EQ(key_symbol_1,Qsynchronized) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(array_constant_29);
    else if (EQ(key_symbol_1,Qnone) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(array_constant_2);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_14;    /* # */

static Object list_constant_15;    /* # */

static Object Qlabel_frequency_mode;  /* label-frequency-mode */

static Object Qno_labels;          /* no-labels */

static Object Q2d_time_axis_tickmark_frequency_spec;  /* 2d-time-axis-tickmark-frequency-spec */

/* 2D-TIME-AXIS-TICKMARK-FREQUENCY-SPEC-EVALUATION-SETTER */
Object n_2d_time_axis_tickmark_frequency_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object label_frequency_mode, number_of_seconds;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,36);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_14))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_15,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_time_axis_tickmark_frequency_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    label_frequency_mode = estructure_slot(evaluation_value,
	    Qlabel_frequency_mode,Nil);
    if (EQ(label_frequency_mode,Qno_labels))
	result = make_frame_like_category_parse_result(Q2d_time_axis_tickmark_frequency_spec,
		Qnone,Nil);
    else if (EQ(label_frequency_mode,Qsynchronized))
	result = make_frame_like_category_parse_result(Q2d_time_axis_tickmark_frequency_spec,
		Qsynchronized,Nil);
    else if (EQ(label_frequency_mode,Qinterval)) {
	number_of_seconds = estructure_slot(evaluation_value,
		Qnumber_of_seconds,Nil);
	if (number_of_seconds)
	    result = make_frame_like_category_parse_result(Q2d_time_axis_tickmark_frequency_spec,
		    Qinterval,phrase_list_2(Qlength,
		    evaluation_value_to_frame_like_value_property(number_of_seconds,
		    Qinteger,Qinterval)));
	else {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(string_constant_7);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else
	result = VALUES_1(Qnil);
  end_2d_time_axis_tickmark_frequency_spec_evaluation_setter:
    return result;
}

/* 2D-TIME-AXIS-TICKMARK-FREQUENCY-SPEC-EVALUATION-GETTER */
Object n_2d_time_axis_tickmark_frequency_spec_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(175,37);
    temp = CAR(slot_value);
    if (EQ(temp,Qnone)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel_frequency_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlabel_frequency_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qno_labels;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qno_labels;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qsynchronized)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel_frequency_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlabel_frequency_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qsynchronized;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qsynchronized;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qinterval)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel_frequency_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlabel_frequency_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qinterval;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qinterval;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qnumber_of_seconds;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qnumber_of_seconds;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    frame_like_value_property_to_evaluation_value(getf(CDDR(slot_value),
		    Qlength,_),Qinteger,Qinterval);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = 
		    frame_like_value_property_to_evaluation_value(getf(CDDR(slot_value),
		    Qlength,_),Qinteger,Qinterval);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_10;  /* "Must specify a ratio between 1 and 1000" */

/* COMPILE-2D-PLOT-MARKER-FREQUENCY-FOR-SLOT */
Object compile_2d_plot_marker_frequency_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, prop_value_qm, temp_1;
    Object temp_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,38);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    prop_value_qm = EQ(CAR(parse_result),Qratio) ? getf(CDDR(parse_result),
	    Qnumber,_) : Qnil;
    if (prop_value_qm) {
	if (check_frame_like_value_range(prop_value_qm,FIX((SI_Long)1L),
		FIX((SI_Long)1000L)))
	    temp = TRUEP(T);
	else {
	    reason_for_bad_phrase = copy_text_string(string_constant_10);
	    temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(T);
    if (temp)
	return VALUES_1(parse_result);
    else {
	temp_1 = Bad_phrase;
	temp_2 = tformat_text_string(2,string_constant_1,
		reason_for_bad_phrase);
	return VALUES_2(temp_1,temp_2);
    }
}

static Object array_constant_30;   /* # */

/* WRITE-2D-PLOT-MARKER-FREQUENCY-FROM-SLOT */
Object write_2d_plot_marker_frequency_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist;

    x_note_fn_call(175,39);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qratio) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_28);
	twrite(string_constant_5);
	twrite(getf(plist,Qnumber,_));
	twrite(string_constant_5);
	return twrite(array_constant_30);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_16;    /* # */

static Object list_constant_17;    /* # */

static Object Qpoints_per_marker;  /* points-per-marker */

static Object Q2d_plot_marker_frequency;  /* 2d-plot-marker-frequency */

static Object string_constant_11;  /* "Must specify a ratio of between 1 and 1000 points per marker" */

/* 2D-PLOT-MARKER-FREQUENCY-EVALUATION-SETTER */
Object n_2d_plot_marker_frequency_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object points_per_marker_qm, points_per_marker;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,40);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_16))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_17,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_plot_marker_frequency_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    points_per_marker_qm = estructure_slot(evaluation_value,
	    Qpoints_per_marker,Nil);
    if (points_per_marker_qm) {
	points_per_marker = points_per_marker_qm;
	if ((SI_Long)1L <= IFIX(points_per_marker) && 
		IFIX(points_per_marker) <= (SI_Long)1000L)
	    result = make_frame_like_category_parse_result(Q2d_plot_marker_frequency,
		    Qratio,phrase_list_2(Qnumber,points_per_marker));
	else {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(string_constant_11);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else
	result = VALUES_1(Qt);
  end_2d_plot_marker_frequency_evaluation_setter:
    return result;
}

/* 2D-PLOT-MARKER-FREQUENCY-EVALUATION-GETTER */
Object n_2d_plot_marker_frequency_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(175,41);
    temp = CAR(slot_value);
    if (EQ(temp,Qratio)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qpoints_per_marker;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qpoints_per_marker;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = getf(CDDR(slot_value),Qnumber,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = getf(CDDR(slot_value),Qnumber,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* POSITIVE-VALUE-P */
Object positive_value_p(number)
    Object number;
{
    Object temp;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(175,42);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    arg = DFLOAT_ISAREF_1(number,(SI_Long)0L);
	    arg_1 = 0.0;
	    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		    !inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	temp = IFIX(number) > (SI_Long)0L ? T : Nil;
    return VALUES_1(temp);
}

static Object Qwidth;              /* width */

static Object string_constant_12;  /* "Must specify a positive label interval" */

static Object Qfraction;           /* fraction */

static Object string_constant_13;  /* "Must specify between 1 and 1000 labels" */

/* COMPILE-2D-VALUE-AXIS-TICKMARK-FREQUENCY-SPEC-FOR-SLOT */
Object compile_2d_value_axis_tickmark_frequency_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, prop_value_qm, temp_1;
    Object temp_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,43);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    gensymed_symbol_1 = EQ(CAR(parse_result),Qinterval) ? 
	    getf(CDDR(parse_result),Qwidth,_) : Qnil;
    if (gensymed_symbol_1) {
	if (positive_value_p(gensymed_symbol_1))
	    temp = TRUEP(T);
	else {
	    reason_for_bad_phrase = copy_text_string(string_constant_12);
	    temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(T);
    if (temp) {
	prop_value_qm = EQ(CAR(parse_result),Qfraction) ? 
		getf(CDDR(parse_result),Qcount,_) : Qnil;
	if (prop_value_qm) {
	    if (check_frame_like_value_range(prop_value_qm,
		    FIX((SI_Long)1L),FIX((SI_Long)1000L)))
		temp = TRUEP(T);
	    else {
		reason_for_bad_phrase = copy_text_string(string_constant_13);
		temp = TRUEP(Nil);
	    }
	}
	else
	    temp = TRUEP(T);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(parse_result);
    else {
	temp_1 = Bad_phrase;
	temp_2 = tformat_text_string(2,string_constant_1,
		reason_for_bad_phrase);
	return VALUES_2(temp_1,temp_2);
    }
}

static Object array_constant_31;   /* # */

static Object array_constant_32;   /* # */

static Object Qorigin;             /* origin */

static Object array_constant_33;   /* # */

static Object Qautomatic;          /* automatic */

/* WRITE-2D-VALUE-AXIS-TICKMARK-FREQUENCY-SPEC-FROM-SLOT */
Object write_2d_value_axis_tickmark_frequency_spec_from_slot(slot_value,
	    gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist;

    x_note_fn_call(175,44);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qinterval) && EQ(sub_key,FIX((SI_Long)1L))) {
	twrite(array_constant_28);
	twrite(string_constant_5);
	twrite(getf(plist,Qwidth,_));
	twrite(string_constant_5);
	twrite(array_constant_31);
	twrite(string_constant_5);
	twrite(array_constant_32);
	twrite(string_constant_5);
	return twrite(getf(plist,Qorigin,_));
    }
    else if (EQ(key_symbol_1,Qinterval) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_28);
	twrite(string_constant_5);
	return twrite(getf(plist,Qwidth,_));
    }
    else if (EQ(key_symbol_1,Qfraction) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(getf(plist,Qcount,_));
	twrite(string_constant_5);
	return twrite(array_constant_33);
    }
    else if (EQ(key_symbol_1,Qautomatic) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(array_constant_29);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_18;    /* # */

static Object list_constant_19;    /* # */

static Object Qlabel_layout_mode;  /* label-layout-mode */

static Object Q2d_value_axis_tickmark_frequency_spec;  /* 2d-value-axis-tickmark-frequency-spec */

static Object Qgrid_division;      /* grid-division */

static Object Qnumber_of_grid_divisions;  /* number-of-grid-divisions */

static Object string_constant_14;  /* "must specify number-of-grid-divisions" */

static Object Qinterval_width;     /* interval-width */

static Object Qinterval_origin;    /* interval-origin */

static Object string_constant_15;  /* "must specify interval-width" */

/* 2D-VALUE-AXIS-TICKMARK-FREQUENCY-SPEC-EVALUATION-SETTER */
Object n_2d_value_axis_tickmark_frequency_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, label_layout_mode;
    Object number_of_grid_divisions, value, new_long;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float, interval_width, interval_origin_qm;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,45);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_18))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_19,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_value_axis_tickmark_frequency_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    label_layout_mode = estructure_slot(evaluation_value,
	    Qlabel_layout_mode,Nil);
    if (EQ(label_layout_mode,Qautomatic))
	result = make_frame_like_category_parse_result(Q2d_value_axis_tickmark_frequency_spec,
		Qautomatic,Nil);
    else if (EQ(label_layout_mode,Qgrid_division)) {
	number_of_grid_divisions = estructure_slot(evaluation_value,
		Qnumber_of_grid_divisions,Nil);
	if (number_of_grid_divisions) {
	    value = evaluation_value_value(number_of_grid_divisions);
	    if (FIXNUMP(value))
		temp_1 = value;
	    else if (INLINE_LONG_P(value) != (SI_Long)0L) {
		new_long = allocate_managed_long_box();
		aref_new_value = INTEGER_TO_INT64(value);
		set_aref1(new_long,FIX((SI_Long)0L),
			INT64_TO_INTEGER(aref_new_value));
		temp_1 = note_use_of_managed_long_in_phrase(new_long);
	    }
	    else {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
		temp_1 = note_use_of_managed_float_in_phrase(new_float);
	    }
	    result = make_frame_like_category_parse_result(Q2d_value_axis_tickmark_frequency_spec,
		    Qfraction,phrase_list_2(Qcount,temp_1));
	}
	else {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(string_constant_14);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else if (EQ(label_layout_mode,Qinterval)) {
	interval_width = estructure_slot(evaluation_value,Qinterval_width,Nil);
	interval_origin_qm = estructure_slot(evaluation_value,
		Qinterval_origin,Nil);
	if (interval_width) {
	    value = evaluation_value_value(interval_width);
	    if (FIXNUMP(value))
		temp = value;
	    else if (INLINE_LONG_P(value) != (SI_Long)0L) {
		new_long = allocate_managed_long_box();
		aref_new_value = INTEGER_TO_INT64(value);
		set_aref1(new_long,FIX((SI_Long)0L),
			INT64_TO_INTEGER(aref_new_value));
		temp = note_use_of_managed_long_in_phrase(new_long);
	    }
	    else {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
		temp = note_use_of_managed_float_in_phrase(new_float);
	    }
	    if (interval_origin_qm) {
		value = evaluation_value_value(interval_origin_qm);
		if (FIXNUMP(value))
		    temp_1 = value;
		else if (INLINE_LONG_P(value) != (SI_Long)0L) {
		    new_long = allocate_managed_long_box();
		    aref_new_value = INTEGER_TO_INT64(value);
		    set_aref1(new_long,FIX((SI_Long)0L),
			    INT64_TO_INTEGER(aref_new_value));
		    temp_1 = note_use_of_managed_long_in_phrase(new_long);
		}
		else {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
		    temp_1 = note_use_of_managed_float_in_phrase(new_float);
		}
	    }
	    else {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		temp_1 = note_use_of_managed_float_in_phrase(new_float);
	    }
	    result = make_frame_like_category_parse_result(Q2d_value_axis_tickmark_frequency_spec,
		    Qinterval,phrase_list_4(Qwidth,temp,Qorigin,temp_1));
	}
	else {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(string_constant_15);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else
	result = VALUES_1(Qnil);
  end_2d_value_axis_tickmark_frequency_spec_evaluation_setter:
    return result;
}

/* 2D-VALUE-AXIS-TICKMARK-FREQUENCY-SPEC-EVALUATION-GETTER */
Object n_2d_value_axis_tickmark_frequency_spec_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, temp_3, value;
    Object amf_available_array_cons_qm, amf_array, amf_result, new_float;
    Object gensymed_symbol_2, temp_4;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(175,46);
    temp = CAR(slot_value);
    if (EQ(temp,Qautomatic)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel_layout_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlabel_layout_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qautomatic;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qautomatic;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = temp_3;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qfraction)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel_layout_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlabel_layout_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qgrid_division;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qgrid_division;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = temp_3;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = 
		    Qnumber_of_grid_divisions;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qnumber_of_grid_divisions;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = getf(CDDR(slot_value),Qcount,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = getf(CDDR(slot_value),Qcount,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = temp_3;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qinterval)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel_layout_mode;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlabel_layout_mode;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qinterval;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qinterval;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = temp_3;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qinterval_width;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qinterval_width;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    value = getf(CDDR(slot_value),Qwidth,_);
	    if (FIXNUMP(value))
		item_or_value = value;
	    else if ( !TRUEP(value))
		item_or_value = Evaluation_false_value;
	    else if (EQ(value,T))
		item_or_value = Evaluation_true_value;
	    else if (SYMBOLP(value))
		item_or_value = value;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_float(value);
	    else if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_1 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		item_or_value = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_long(value);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L)
		item_or_value = make_evaluation_long(value);
	    else if (text_string_p(value))
		item_or_value = copy_as_wide_string(value);
	    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		gensymed_symbol_2 = M_CAR(value);
		if (FIXNUM_EQ(gensymed_symbol_2,Truth))
		    item_or_value = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
		    item_or_value = Evaluation_false_value;
		else
		    item_or_value = eval_cons_1(gensymed_symbol_2,
			    Qtruth_value);
	    }
	    else
		item_or_value = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(value));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    value = getf(CDDR(slot_value),Qwidth,_);
	    if (FIXNUMP(value))
		item_or_value = value;
	    else if ( !TRUEP(value))
		item_or_value = Evaluation_false_value;
	    else if (EQ(value,T))
		item_or_value = Evaluation_true_value;
	    else if (SYMBOLP(value))
		item_or_value = value;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_float(value);
	    else if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_3 = Vector_of_simple_float_array_pools;
		    temp_4 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_3 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_3) = amf_available_array_cons_qm;
			temp_3 = Available_float_array_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
		    }
		    else {
			temp_3 = Available_float_array_conses_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
			temp_3 = Available_float_array_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		item_or_value = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_long(value);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L)
		item_or_value = make_evaluation_long(value);
	    else if (text_string_p(value))
		item_or_value = copy_as_wide_string(value);
	    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		gensymed_symbol_2 = M_CAR(value);
		if (FIXNUM_EQ(gensymed_symbol_2,Truth))
		    item_or_value = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
		    item_or_value = Evaluation_false_value;
		else
		    item_or_value = eval_cons_1(gensymed_symbol_2,
			    Qtruth_value);
	    }
	    else
		item_or_value = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(value));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = temp_3;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qinterval_origin;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)5L)) = Qinterval_origin;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    if (getf(CDDR(slot_value),Qorigin,_)) {
		value = getf(CDDR(slot_value),Qorigin,_);
		if (FIXNUMP(value))
		    item_or_value = value;
		else if ( !TRUEP(value))
		    item_or_value = Evaluation_false_value;
		else if (EQ(value,T))
		    item_or_value = Evaluation_true_value;
		else if (SYMBOLP(value))
		    item_or_value = value;
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    item_or_value = copy_managed_float(value);
		else if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = amf_available_array_cons_qm;
			    temp_1 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_1 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
			    temp_1 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    item_or_value = new_float;
		}
		else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    item_or_value = copy_managed_long(value);
		else if (INLINE_LONG_P(value) != (SI_Long)0L)
		    item_or_value = make_evaluation_long(value);
		else if (text_string_p(value))
		    item_or_value = copy_as_wide_string(value);
		else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		    gensymed_symbol_2 = M_CAR(value);
		    if (FIXNUM_EQ(gensymed_symbol_2,Truth))
			item_or_value = Evaluation_true_value;
		    else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
			item_or_value = Evaluation_false_value;
		    else
			item_or_value = eval_cons_1(gensymed_symbol_2,
				Qtruth_value);
		}
		else
		    item_or_value = error((SI_Long)2L,
			    "Bad type ~a for make-evaluation-value-based-on-type.",
			    type_of(value));
	    }
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = amf_available_array_cons_qm;
			    temp_1 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_1 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
			    temp_1 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
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
		    item_or_value = new_float;
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (getf(CDDR(slot_value),Qorigin,_)) {
		value = getf(CDDR(slot_value),Qorigin,_);
		if (FIXNUMP(value))
		    item_or_value = value;
		else if ( !TRUEP(value))
		    item_or_value = Evaluation_false_value;
		else if (EQ(value,T))
		    item_or_value = Evaluation_true_value;
		else if (SYMBOLP(value))
		    item_or_value = value;
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    item_or_value = copy_managed_float(value);
		else if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_3 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_3 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_3) = amf_available_array_cons_qm;
			    temp_3 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_3 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
			    temp_3 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    item_or_value = new_float;
		}
		else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    item_or_value = copy_managed_long(value);
		else if (INLINE_LONG_P(value) != (SI_Long)0L)
		    item_or_value = make_evaluation_long(value);
		else if (text_string_p(value))
		    item_or_value = copy_as_wide_string(value);
		else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		    gensymed_symbol_2 = M_CAR(value);
		    if (FIXNUM_EQ(gensymed_symbol_2,Truth))
			item_or_value = Evaluation_true_value;
		    else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
			item_or_value = Evaluation_false_value;
		    else
			item_or_value = eval_cons_1(gensymed_symbol_2,
				Qtruth_value);
		}
		else
		    item_or_value = error((SI_Long)2L,
			    "Bad type ~a for make-evaluation-value-based-on-type.",
			    type_of(value));
	    }
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_3 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_3 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_3) = amf_available_array_cons_qm;
			    temp_3 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_3 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
			    temp_3 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
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
		    item_or_value = new_float;
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)6L)) = temp_3;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qspecified;          /* specified */

static Object Qlower;              /* lower */

static Object Qupper;              /* upper */

static Object string_constant_16;  /* "Lower bound must be less than upper bound and greater than ~%~a. Upper bound must be less than ~a" */

static Object float_constant;      /* -1.7976931348623158E+# */

static Object float_constant_1;    /* 1.7976931348623158E+# */

/* COMPILE-2D-VALUE-AXIS-BOUNDS-SPEC-FOR-SLOT */
Object compile_2d_value_axis_bounds_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp_1, temp_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,47);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    gensymed_symbol_1 = EQ(CAR(parse_result),Qspecified) ? 
	    getf(CDDR(parse_result),Qlower,_) : Qnil;
    gensymed_symbol = EQ(CAR(parse_result),Qspecified) ? 
	    getf(CDDR(parse_result),Qupper,_) : Qnil;
    if (gensymed_symbol_1 && gensymed_symbol) {
	if (value_axis_bounds_check(gensymed_symbol_1,gensymed_symbol))
	    temp = TRUEP(T);
	else {
	    reason_for_bad_phrase = tformat_text_string(3,
		    string_constant_16,float_constant,float_constant_1);
	    temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(T);
    if (temp)
	return VALUES_1(parse_result);
    else {
	temp_1 = Bad_phrase;
	temp_2 = tformat_text_string(2,string_constant_1,
		reason_for_bad_phrase);
	return VALUES_2(temp_1,temp_2);
    }
}

static Object array_constant_34;   /* # */

static Object array_constant_35;   /* # */

/* WRITE-2D-VALUE-AXIS-BOUNDS-SPEC-FROM-SLOT */
Object write_2d_value_axis_bounds_spec_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist;

    x_note_fn_call(175,48);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qspecified) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_34);
	twrite(string_constant_5);
	twrite(getf(plist,Qlower,_));
	twrite(string_constant_5);
	twrite(array_constant_35);
	twrite(string_constant_5);
	return twrite(getf(plist,Qupper,_));
    }
    else if (EQ(key_symbol_1,Qnone) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(array_constant_2);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_20;    /* # */

static Object list_constant_21;    /* # */

static Object Q2d_value_axis_bounds_spec;  /* 2d-value-axis-bounds-spec */

static Object list_constant_22;    /* # */

static Object Qlower_bound;        /* lower-bound */

static Object Qupper_bound;        /* upper-bound */

/* 2D-VALUE-AXIS-BOUNDS-SPEC-EVALUATION-SETTER */
Object n_2d_value_axis_bounds_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, value, new_long;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value_2, length_1;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,49);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_20))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_21,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_value_axis_bounds_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_3))
	result = make_frame_like_category_parse_result(Q2d_value_axis_bounds_spec,
		Qnone,Nil);
    else if (type_specification_type_p(gensymed_symbol,list_constant_22)) {
	value = evaluation_value_value(estructure_slot(evaluation_value,
		Qlower_bound,Nil));
	if (FIXNUMP(value))
	    temp_1 = value;
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    temp_1 = note_use_of_managed_long_in_phrase(new_long);
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_2 = Vector_of_simple_float_array_pools;
		temp_3 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		}
		else {
		    temp_2 = Available_float_array_conses_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    temp_1 = note_use_of_managed_float_in_phrase(new_float);
	}
	value = evaluation_value_value(estructure_slot(evaluation_value,
		Qupper_bound,Nil));
	if (FIXNUMP(value))
	    temp = value;
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    temp = note_use_of_managed_long_in_phrase(new_long);
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_2 = Vector_of_simple_float_array_pools;
		temp_3 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		}
		else {
		    temp_2 = Available_float_array_conses_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    temp = note_use_of_managed_float_in_phrase(new_float);
	}
	result = make_frame_like_category_parse_result(Q2d_value_axis_bounds_spec,
		Qspecified,phrase_list_4(Qlower,temp_1,Qupper,temp));
    }
    else {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  aref_arg_2 = bv16_length - (SI_Long)2L;
	  aref_new_value_2 = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value_2);
	  aref_arg_2 = bv16_length - (SI_Long)1L;
	  aref_new_value_2 = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value_2);
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
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_3,list_constant_3);
		  tformat(2,string_constant_3,list_constant_22);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_4,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_2d_value_axis_bounds_spec_evaluation_setter:
    return result;
}

/* 2D-VALUE-AXIS-BOUNDS-SPEC-EVALUATION-GETTER */
Object n_2d_value_axis_bounds_spec_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, value, item_or_value;
    Object amf_available_array_cons_qm, amf_array, temp_2, amf_result;
    Object new_float, gensymed_symbol_2, x2, temp_4;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_3;
    double aref_new_value;

    x_note_fn_call(175,50);
    temp = CAR(slot_value);
    if (EQ(temp,Qnone))
	temp = Nil;
    else if (EQ(temp,Qspecified)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlower_bound;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlower_bound;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    value = getf(CDDR(slot_value),Qlower,_);
	    if (FIXNUMP(value))
		item_or_value = value;
	    else if ( !TRUEP(value))
		item_or_value = Evaluation_false_value;
	    else if (EQ(value,T))
		item_or_value = Evaluation_true_value;
	    else if (SYMBOLP(value))
		item_or_value = value;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_float(value);
	    else if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = Vector_of_simple_float_array_pools;
		    temp_2 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    }
		    else {
			temp_1 = Available_float_array_conses_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		item_or_value = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_long(value);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L)
		item_or_value = make_evaluation_long(value);
	    else if (text_string_p(value))
		item_or_value = copy_as_wide_string(value);
	    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		gensymed_symbol_2 = M_CAR(value);
		if (FIXNUM_EQ(gensymed_symbol_2,Truth))
		    item_or_value = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
		    item_or_value = Evaluation_false_value;
		else
		    item_or_value = eval_cons_1(gensymed_symbol_2,
			    Qtruth_value);
	    }
	    else
		item_or_value = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(value));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_1 = temp_3 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    value = getf(CDDR(slot_value),Qlower,_);
	    if (FIXNUMP(value))
		item_or_value = value;
	    else if ( !TRUEP(value))
		item_or_value = Evaluation_false_value;
	    else if (EQ(value,T))
		item_or_value = Evaluation_true_value;
	    else if (SYMBOLP(value))
		item_or_value = value;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_float(value);
	    else if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_4 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		item_or_value = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_long(value);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L)
		item_or_value = make_evaluation_long(value);
	    else if (text_string_p(value))
		item_or_value = copy_as_wide_string(value);
	    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		gensymed_symbol_2 = M_CAR(value);
		if (FIXNUM_EQ(gensymed_symbol_2,Truth))
		    item_or_value = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
		    item_or_value = Evaluation_false_value;
		else
		    item_or_value = eval_cons_1(gensymed_symbol_2,
			    Qtruth_value);
	    }
	    else
		item_or_value = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(value));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_2 = temp_3 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = temp_2;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qupper_bound;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qupper_bound;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    value = getf(CDDR(slot_value),Qupper,_);
	    if (FIXNUMP(value))
		item_or_value = value;
	    else if ( !TRUEP(value))
		item_or_value = Evaluation_false_value;
	    else if (EQ(value,T))
		item_or_value = Evaluation_true_value;
	    else if (SYMBOLP(value))
		item_or_value = value;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_float(value);
	    else if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = Vector_of_simple_float_array_pools;
		    temp_2 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    }
		    else {
			temp_1 = Available_float_array_conses_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		item_or_value = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_long(value);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L)
		item_or_value = make_evaluation_long(value);
	    else if (text_string_p(value))
		item_or_value = copy_as_wide_string(value);
	    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		gensymed_symbol_2 = M_CAR(value);
		if (FIXNUM_EQ(gensymed_symbol_2,Truth))
		    item_or_value = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
		    item_or_value = Evaluation_false_value;
		else
		    item_or_value = eval_cons_1(gensymed_symbol_2,
			    Qtruth_value);
	    }
	    else
		item_or_value = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(value));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_1 = temp_3 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    value = getf(CDDR(slot_value),Qupper,_);
	    if (FIXNUMP(value))
		item_or_value = value;
	    else if ( !TRUEP(value))
		item_or_value = Evaluation_false_value;
	    else if (EQ(value,T))
		item_or_value = Evaluation_true_value;
	    else if (SYMBOLP(value))
		item_or_value = value;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_float(value);
	    else if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_4 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		item_or_value = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_long(value);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L)
		item_or_value = make_evaluation_long(value);
	    else if (text_string_p(value))
		item_or_value = copy_as_wide_string(value);
	    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		gensymed_symbol_2 = M_CAR(value);
		if (FIXNUM_EQ(gensymed_symbol_2,Truth))
		    item_or_value = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
		    item_or_value = Evaluation_false_value;
		else
		    item_or_value = eval_cons_1(gensymed_symbol_2,
			    Qtruth_value);
	    }
	    else
		item_or_value = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(value));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_2 = temp_3 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = temp_2;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* VALUE-AXIS-BOUNDS-CHECK */
Object value_axis_bounds_check(low,high)
    Object low, high;
{
    char temp;
    double low_float, high_float, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(175,51);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	low_float = INLINE_DOUBLE_FLOAT_VECTOR_P(low) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(low)) == (SI_Long)1L ? 
		DFLOAT_ISAREF_1(low,(SI_Long)0L) : (double)IFIX(low);
	high_float = INLINE_DOUBLE_FLOAT_VECTOR_P(high) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(high)) == (SI_Long)1L ? 
		DFLOAT_ISAREF_1(high,(SI_Long)0L) : (double)IFIX(high);
	arg = low_float;
	arg_1 = high_float;
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    arg = high_float;
	    arg_1 = 1.7976931348623158E+304;
	    temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    arg = low_float;
	    arg_1 = -1.7976931348623158E+304;
	    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg))
		result = VALUES_1( !inline_nanp_for_comparison(arg_1) ? T :
			 Nil);
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* COMPILE-TREND-CHART-LEGEND-COLOR-SPEC-FOR-SLOT */
Object compile_trend_chart_legend_color_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cadr_new_value, reason_for_bad_phrase, temp_1, temp_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,52);
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
    if ( !FIXNUMP(CADR(parse_result))) {
	cadr_new_value = FIXNUM_MINUS(CHAR_CODE(CADR(parse_result)),
		CHAR_CODE(CHR('A')));
	M_CADR(parse_result) = cadr_new_value;
    }
    reason_for_bad_phrase = Nil;
    gensymed_symbol_1 = EQ(CAR(parse_result),Qabsolute) ? 
	    getf(CDDR(parse_result),Qcolor,_) : Qnil;
    if (gensymed_symbol_1) {
	if (color_or_metacolor_p(gensymed_symbol_1))
	    temp = TRUEP(T);
	else {
	    reason_for_bad_phrase = copy_text_string(string_constant_6);
	    temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(T);
    if (temp)
	return VALUES_1(parse_result);
    else {
	temp_1 = Bad_phrase;
	temp_2 = tformat_text_string(2,string_constant_1,
		reason_for_bad_phrase);
	return VALUES_2(temp_1,temp_2);
    }
}

static Object array_constant_36;   /* # */

/* WRITE-TREND-CHART-LEGEND-COLOR-SPEC-FROM-SLOT */
Object write_trend_chart_legend_color_spec_from_slot(slot_value,
	    gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object key_symbol_1, sub_key, plist;

    x_note_fn_call(175,53);
    key_symbol_1 = CAR(slot_value);
    sub_key = CADR(slot_value);
    plist = CDDR(slot_value);
    if (EQ(key_symbol_1,Qabsolute) && EQ(sub_key,FIX((SI_Long)0L)))
	return twrite(getf(plist,Qcolor,_));
    else if (EQ(key_symbol_1,Qmatching) && EQ(sub_key,FIX((SI_Long)0L))) {
	twrite(array_constant_14);
	twrite(string_constant_5);
	twrite(array_constant_15);
	twrite(string_constant_5);
	return twrite(array_constant_36);
    }
    else
	return VALUES_1(Qnil);
}

static Object list_constant_23;    /* # */

static Object list_constant_24;    /* # */

static Object Qlegend_color_type;  /* legend-color-type */

static Object Qtrend_chart_legend_color_spec;  /* trend-chart-legend-color-spec */

/* TREND-CHART-LEGEND-COLOR-SPEC-EVALUATION-SETTER */
Object trend_chart_legend_color_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, legend_color_type;
    Object color;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,54);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_23))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_24,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_trend_chart_legend_color_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    legend_color_type = estructure_slot(evaluation_value,
	    Qlegend_color_type,Nil);
    if (EQ(legend_color_type,Qmatching_plot_color))
	result = make_frame_like_category_parse_result(Qtrend_chart_legend_color_spec,
		Qmatching,Nil);
    else if (EQ(legend_color_type,Qabsolute)) {
	color = estructure_slot(evaluation_value,Qcolor,Nil);
	if (color)
	    result = make_frame_like_category_parse_result(Qtrend_chart_legend_color_spec,
		    Qabsolute,phrase_list_2(Qcolor,color));
	else {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(2,string_constant,color);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else
	result = VALUES_1(Qnil);
  end_trend_chart_legend_color_spec_evaluation_setter:
    return result;
}

/* TREND-CHART-LEGEND-COLOR-SPEC-EVALUATION-GETTER */
Object trend_chart_legend_color_spec_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(175,55);
    temp = CAR(slot_value);
    if (EQ(temp,Qabsolute)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlegend_color_type;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlegend_color_type;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qabsolute;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qabsolute;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qcolor;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qcolor;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = getf(CDDR(slot_value),Qcolor,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = getf(CDDR(slot_value),Qcolor,_);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (EQ(temp,Qmatching)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlegend_color_type;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qlegend_color_type;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qmatching_plot_color;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qmatching_plot_color;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_25;    /* # */

static Object list_constant_26;    /* # */

static Object Qright;              /* right */

static Object Qleft;               /* left */

/* VALUE-AXIS-POSITION-EVALUATION-SETTER */
Object value_axis_position_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, symbol;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,56);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_25))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_26,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_value_axis_position_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    symbol = evaluation_value;
    if (EQ(symbol,Qright))
	result = VALUES_1(Qright);
    else if (EQ(symbol,Qleft))
	result = VALUES_1(Qleft);
    else
	result = VALUES_1(Qnil);
  end_value_axis_position_evaluation_setter:
    return result;
}

/* VALUE-AXIS-POSITION-EVALUATION-GETTER */
Object value_axis_position_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(175,57);
    if (EQ(slot_value,Qright))
	temp = Qright;
    else if (EQ(slot_value,Qleft))
	temp = Qleft;
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_17;  /* "left" */

static Object string_constant_18;  /* "right" */

/* WRITE-VALUE-AXIS-POSITION-FROM-SLOT */
Object write_value_axis_position_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(175,58);
    if (EQ(value,Qleft))
	return twrite(string_constant_17);
    else if (EQ(value,Qright))
	return twrite(string_constant_18);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_27;    /* # */

static Object list_constant_28;    /* # */

static Object Qabove;              /* above */

static Object Qbelow;              /* below */

/* TREND-CHART-LEGEND-POSITION-EVALUATION-SETTER */
Object trend_chart_legend_position_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, symbol;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,59);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_27))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_28,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_trend_chart_legend_position_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    symbol = evaluation_value;
    if (EQ(symbol,Qabove))
	result = VALUES_1(Qabove);
    else if (EQ(symbol,Qbelow))
	result = VALUES_1(Qbelow);
    else
	result = VALUES_1(Qnil);
  end_trend_chart_legend_position_evaluation_setter:
    return result;
}

/* TREND-CHART-LEGEND-POSITION-EVALUATION-GETTER */
Object trend_chart_legend_position_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(175,60);
    if (EQ(slot_value,Qabove))
	temp = Qabove;
    else if (EQ(slot_value,Qbelow))
	temp = Qbelow;
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_19;  /* "below" */

static Object string_constant_20;  /* "above" */

/* WRITE-TREND-CHART-LEGEND-POSITION-FROM-SLOT */
Object write_trend_chart_legend_position_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(175,61);
    if (EQ(value,Qbelow))
	return twrite(string_constant_19);
    else if (EQ(value,Qabove))
	return twrite(string_constant_20);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_29;    /* # */

static Object list_constant_30;    /* # */

static Object Qsample_and_hold_cm_without_risers;  /* SAMPLE-AND-HOLD-\,-WITHOUT-RISERS */

static Object Qsample_and_hold;    /* sample-and-hold */

static Object Qsample_and_hold_with_risers;  /* sample-and-hold-with-risers */

static Object Qlinear;             /* linear */

static Object Qinterpolated;       /* interpolated */

/* 2D-LINE-STYLE-EVALUATION-SETTER */
Object n_2d_line_style_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, symbol;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,62);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_29))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_30,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_line_style_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    symbol = evaluation_value;
    if (EQ(symbol,Qsample_and_hold_cm_without_risers))
	result = VALUES_1(Qsample_and_hold);
    else if (EQ(symbol,Qsample_and_hold))
	result = VALUES_1(Qsample_and_hold_with_risers);
    else if (EQ(symbol,Qlinear))
	result = VALUES_1(Qinterpolated);
    else
	result = VALUES_1(Qnil);
  end_2d_line_style_evaluation_setter:
    return result;
}

/* 2D-LINE-STYLE-EVALUATION-GETTER */
Object n_2d_line_style_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(175,63);
    if (EQ(slot_value,Qsample_and_hold))
	temp = Qsample_and_hold_cm_without_risers;
    else if (EQ(slot_value,Qsample_and_hold_with_risers))
	temp = Qsample_and_hold;
    else if (EQ(slot_value,Qinterpolated))
	temp = Qlinear;
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_21;  /* "linear" */

static Object string_constant_22;  /* "sample and hold" */

static Object string_constant_23;  /* "sample and hold , without risers" */

/* WRITE-2D-LINE-STYLE-FROM-SLOT */
Object write_2d_line_style_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(175,64);
    if (EQ(value,Qinterpolated))
	return twrite(string_constant_21);
    else if (EQ(value,Qsample_and_hold_with_risers))
	return twrite(string_constant_22);
    else if (EQ(value,Qsample_and_hold))
	return twrite(string_constant_23);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_31;    /* # */

static Object list_constant_32;    /* # */

static Object Qcenter;             /* center */

/* TIME-AXIS-LABEL-ALIGNMENT-EVALUATION-SETTER */
Object time_axis_label_alignment_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, symbol;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,65);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_31))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_32,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_time_axis_label_alignment_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    symbol = evaluation_value;
    if (EQ(symbol,Qleft))
	result = VALUES_1(Qleft);
    else if (EQ(symbol,Qright))
	result = VALUES_1(Qright);
    else if (EQ(symbol,Qcenter))
	result = VALUES_1(Qcenter);
    else
	result = VALUES_1(Qnil);
  end_time_axis_label_alignment_evaluation_setter:
    return result;
}

/* TIME-AXIS-LABEL-ALIGNMENT-EVALUATION-GETTER */
Object time_axis_label_alignment_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(175,66);
    if (EQ(slot_value,Qleft))
	temp = Qleft;
    else if (EQ(slot_value,Qright))
	temp = Qright;
    else if (EQ(slot_value,Qcenter))
	temp = Qcenter;
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_24;  /* "center" */

/* WRITE-TIME-AXIS-LABEL-ALIGNMENT-FROM-SLOT */
Object write_time_axis_label_alignment_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(175,67);
    if (EQ(value,Qcenter))
	return twrite(string_constant_24);
    else if (EQ(value,Qright))
	return twrite(string_constant_18);
    else if (EQ(value,Qleft))
	return twrite(string_constant_17);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_33;    /* # */

static Object list_constant_34;    /* # */

static Object Qhh_mm;              /* hh-mm */

static Object Qhh_mm_as_an_interval;  /* hh-mm-as-an-interval */

static Object Qhh_mm_interval;     /* hh-mm-interval */

static Object Qhh_mm_am_pm;        /* hh-mm-am-pm */

static Object Qhh_mm_ss;           /* hh-mm-ss */

static Object Qhh_mm_ss_as_an_interval;  /* hh-mm-ss-as-an-interval */

static Object Qhh_mm_ss_interval;  /* hh-mm-ss-interval */

static Object Qhh_mm_ss_am_pm;     /* hh-mm-ss-am-pm */

static Object Qmm_ss;              /* mm-ss */

static Object Qmm_ss_as_an_interval;  /* mm-ss-as-an-interval */

static Object Qmm_ss_interval;     /* mm-ss-interval */

static Object Qdd_hh_mm_as_an_interval;  /* dd-hh-mm-as-an-interval */

static Object Qdd_hh_mm_interval;  /* dd-hh-mm-interval */

static Object Qmmm_dd_hh_mm;       /* mmm-dd-hh-mm */

static Object Qmm_dd_hh_mm;        /* mm-dd-hh-mm */

static Object Qmm_sl_dd_hh_mm;     /* mm/dd-hh-mm */

static Object Qmm_yy;              /* mm-yy */

static Object Qmm_dd_yy;           /* mm-dd-yy */

static Object Qyy_mm_dd;           /* yy-mm-dd */

static Object Qdd_mm_yy;           /* dd-mm-yy */

static Object Qdd_mmm_yyyy;        /* dd-mmm-yyyy */

static Object Qmmm_dd_yyyy;        /* mmm-dd-yyyy */

static Object Qmmm_yyyy;           /* mmm-yyyy */

static Object Qhh_dot_hh_as_an_interval;  /* hh.hh-as-an-interval */

static Object Qhh_dot_hh_interval;  /* hh.hh-interval */

/* TIME-AXIS-LABEL-FORMAT-SPEC-EVALUATION-SETTER */
Object time_axis_label_format_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, symbol;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,68);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_33))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_34,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_time_axis_label_format_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    symbol = evaluation_value;
    if (EQ(symbol,Qhh_mm))
	result = VALUES_1(Qhh_mm);
    else if (EQ(symbol,Qhh_mm_as_an_interval))
	result = VALUES_1(Qhh_mm_interval);
    else if (EQ(symbol,Qhh_mm_am_pm))
	result = VALUES_1(Qhh_mm_am_pm);
    else if (EQ(symbol,Qhh_mm_ss))
	result = VALUES_1(Qhh_mm_ss);
    else if (EQ(symbol,Qhh_mm_ss_as_an_interval))
	result = VALUES_1(Qhh_mm_ss_interval);
    else if (EQ(symbol,Qhh_mm_ss_am_pm))
	result = VALUES_1(Qhh_mm_ss_am_pm);
    else if (EQ(symbol,Qmm_ss))
	result = VALUES_1(Qmm_ss);
    else if (EQ(symbol,Qmm_ss_as_an_interval))
	result = VALUES_1(Qmm_ss_interval);
    else if (EQ(symbol,Qdd_hh_mm_as_an_interval))
	result = VALUES_1(Qdd_hh_mm_interval);
    else if (EQ(symbol,Qmmm_dd_hh_mm))
	result = VALUES_1(Qmmm_dd_hh_mm);
    else if (EQ(symbol,Qmm_dd_hh_mm))
	result = VALUES_1(Qmm_sl_dd_hh_mm);
    else if (EQ(symbol,Qmm_yy))
	result = VALUES_1(Qmm_yy);
    else if (EQ(symbol,Qmm_dd_yy))
	result = VALUES_1(Qmm_dd_yy);
    else if (EQ(symbol,Qyy_mm_dd))
	result = VALUES_1(Qyy_mm_dd);
    else if (EQ(symbol,Qdd_mm_yy))
	result = VALUES_1(Qdd_mm_yy);
    else if (EQ(symbol,Qdd_mmm_yyyy))
	result = VALUES_1(Qdd_mmm_yyyy);
    else if (EQ(symbol,Qmmm_dd_yyyy))
	result = VALUES_1(Qmmm_dd_yyyy);
    else if (EQ(symbol,Qmmm_yyyy))
	result = VALUES_1(Qmmm_yyyy);
    else if (EQ(symbol,Qhh_dot_hh_as_an_interval))
	result = VALUES_1(Qhh_dot_hh_interval);
    else
	result = VALUES_1(Qnil);
  end_time_axis_label_format_spec_evaluation_setter:
    return result;
}

/* TIME-AXIS-LABEL-FORMAT-SPEC-EVALUATION-GETTER */
Object time_axis_label_format_spec_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(175,69);
    if (EQ(slot_value,Qhh_mm))
	temp = Qhh_mm;
    else if (EQ(slot_value,Qhh_mm_interval))
	temp = Qhh_mm_as_an_interval;
    else if (EQ(slot_value,Qhh_mm_am_pm))
	temp = Qhh_mm_am_pm;
    else if (EQ(slot_value,Qhh_mm_ss))
	temp = Qhh_mm_ss;
    else if (EQ(slot_value,Qhh_mm_ss_interval))
	temp = Qhh_mm_ss_as_an_interval;
    else if (EQ(slot_value,Qhh_mm_ss_am_pm))
	temp = Qhh_mm_ss_am_pm;
    else if (EQ(slot_value,Qmm_ss))
	temp = Qmm_ss;
    else if (EQ(slot_value,Qmm_ss_interval))
	temp = Qmm_ss_as_an_interval;
    else if (EQ(slot_value,Qdd_hh_mm_interval))
	temp = Qdd_hh_mm_as_an_interval;
    else if (EQ(slot_value,Qmmm_dd_hh_mm))
	temp = Qmmm_dd_hh_mm;
    else if (EQ(slot_value,Qmm_sl_dd_hh_mm))
	temp = Qmm_dd_hh_mm;
    else if (EQ(slot_value,Qmm_yy))
	temp = Qmm_yy;
    else if (EQ(slot_value,Qmm_dd_yy))
	temp = Qmm_dd_yy;
    else if (EQ(slot_value,Qyy_mm_dd))
	temp = Qyy_mm_dd;
    else if (EQ(slot_value,Qdd_mm_yy))
	temp = Qdd_mm_yy;
    else if (EQ(slot_value,Qdd_mmm_yyyy))
	temp = Qdd_mmm_yyyy;
    else if (EQ(slot_value,Qmmm_dd_yyyy))
	temp = Qmmm_dd_yyyy;
    else if (EQ(slot_value,Qmmm_yyyy))
	temp = Qmmm_yyyy;
    else if (EQ(slot_value,Qhh_dot_hh_interval))
	temp = Qhh_dot_hh_as_an_interval;
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_25;  /* "hh.hh as an interval" */

static Object string_constant_26;  /* "mmm-yyyy" */

static Object string_constant_27;  /* "mmm-dd-yyyy" */

static Object string_constant_28;  /* "dd-mmm-yyyy" */

static Object string_constant_29;  /* "dd-mm-yy" */

static Object string_constant_30;  /* "yy-mm-dd" */

static Object string_constant_31;  /* "mm-dd-yy" */

static Object string_constant_32;  /* "mm-yy" */

static Object string_constant_33;  /* "mm-dd-hh-mm" */

static Object string_constant_34;  /* "mmm-dd-hh-mm" */

static Object string_constant_35;  /* "dd-hh-mm as an interval" */

static Object string_constant_36;  /* "mm-ss as an interval" */

static Object string_constant_37;  /* "mm-ss" */

static Object string_constant_38;  /* "hh-mm-ss-am-pm" */

static Object string_constant_39;  /* "hh-mm-ss as an interval" */

static Object string_constant_40;  /* "hh-mm-ss" */

static Object string_constant_41;  /* "hh-mm-am-pm" */

static Object string_constant_42;  /* "hh-mm as an interval" */

static Object string_constant_43;  /* "hh-mm" */

/* WRITE-TIME-AXIS-LABEL-FORMAT-SPEC-FROM-SLOT */
Object write_time_axis_label_format_spec_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(175,70);
    if (EQ(value,Qhh_dot_hh_interval))
	return twrite(string_constant_25);
    else if (EQ(value,Qmmm_yyyy))
	return twrite(string_constant_26);
    else if (EQ(value,Qmmm_dd_yyyy))
	return twrite(string_constant_27);
    else if (EQ(value,Qdd_mmm_yyyy))
	return twrite(string_constant_28);
    else if (EQ(value,Qdd_mm_yy))
	return twrite(string_constant_29);
    else if (EQ(value,Qyy_mm_dd))
	return twrite(string_constant_30);
    else if (EQ(value,Qmm_dd_yy))
	return twrite(string_constant_31);
    else if (EQ(value,Qmm_yy))
	return twrite(string_constant_32);
    else if (EQ(value,Qmm_sl_dd_hh_mm))
	return twrite(string_constant_33);
    else if (EQ(value,Qmmm_dd_hh_mm))
	return twrite(string_constant_34);
    else if (EQ(value,Qdd_hh_mm_interval))
	return twrite(string_constant_35);
    else if (EQ(value,Qmm_ss_interval))
	return twrite(string_constant_36);
    else if (EQ(value,Qmm_ss))
	return twrite(string_constant_37);
    else if (EQ(value,Qhh_mm_ss_am_pm))
	return twrite(string_constant_38);
    else if (EQ(value,Qhh_mm_ss_interval))
	return twrite(string_constant_39);
    else if (EQ(value,Qhh_mm_ss))
	return twrite(string_constant_40);
    else if (EQ(value,Qhh_mm_am_pm))
	return twrite(string_constant_41);
    else if (EQ(value,Qhh_mm_interval))
	return twrite(string_constant_42);
    else if (EQ(value,Qhh_mm))
	return twrite(string_constant_43);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_35;    /* # */

static Object list_constant_36;    /* # */

static Object Qfixed;              /* fixed */

static Object Qautoranging_on_data_window;  /* autoranging-on-data-window */

static Object Qautoranging_on_all_past_values;  /* autoranging-on-all-past-values */

static Object Qhigh_water_marking;  /* high-water-marking */

/* 2D-RANGE-MODE-EVALUATION-SETTER */
Object n_2d_range_mode_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, symbol;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,71);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_35))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_36,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_2d_range_mode_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    symbol = evaluation_value;
    if (EQ(symbol,Qfixed))
	result = VALUES_1(Qfixed);
    else if (EQ(symbol,Qautoranging_on_data_window))
	result = VALUES_1(Qautomatic);
    else if (EQ(symbol,Qautoranging_on_all_past_values))
	result = VALUES_1(Qhigh_water_marking);
    else
	result = VALUES_1(Qnil);
  end_2d_range_mode_evaluation_setter:
    return result;
}

/* 2D-RANGE-MODE-EVALUATION-GETTER */
Object n_2d_range_mode_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(175,72);
    if (EQ(slot_value,Qfixed))
	temp = Qfixed;
    else if (EQ(slot_value,Qautomatic))
	temp = Qautoranging_on_data_window;
    else if (EQ(slot_value,Qhigh_water_marking))
	temp = Qautoranging_on_all_past_values;
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_44;  /* "autoranging on all past values" */

static Object string_constant_45;  /* "autoranging on data window" */

static Object string_constant_46;  /* "fixed" */

/* WRITE-2D-RANGE-MODE-FROM-SLOT */
Object write_2d_range_mode_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(175,73);
    if (EQ(value,Qhigh_water_marking))
	return twrite(string_constant_44);
    else if (EQ(value,Qautomatic))
	return twrite(string_constant_45);
    else if (EQ(value,Qfixed))
	return twrite(string_constant_46);
    else
	return VALUES_1(Qnil);
}

static Object Qdefault;            /* default */

static Object string_constant_47;  /* "unknown color specified" */

/* COMPILE-EXTRA-VALUE-GRID-LINES-FOR-SLOT */
Object compile_extra_value_grid_lines_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object number, color_spec, ab_loop_list_, ab_loop_desetq_, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,74);
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
    number = Nil;
    color_spec = Nil;
    ab_loop_list_ = CDR(parse_result);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    number = CAR(ab_loop_desetq_);
    color_spec = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(EQ(color_spec,Qdefault) || color_or_metacolor_p(color_spec))) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_47);
	return VALUES_2(temp,temp_1);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(parse_result);
    return VALUES_1(Qnil);
}

static Object list_constant_37;    /* # */

static Object list_constant_38;    /* # */

static Object list_constant_39;    /* # */

static Object Qvalue;              /* value */

static Object Qcm;                 /* \, */

/* EXTRA-VALUE-GRID-LINES-EVALUATION-SETTER */
Object extra_value_grid_lines_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object extra_grid_line, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, value, new_long, amf_available_array_cons_qm;
    Object amf_array, temp_2, temp_3, amf_result, new_float;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value_2;
    SI_Long length_2;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,75);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_37))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_38,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_extra_value_grid_lines_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_3))
	result = VALUES_1(Nil);
    else if (type_specification_type_p(gensymed_symbol,list_constant_39)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	extra_grid_line = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	extra_grid_line = validated_elt;
	value = evaluation_value_value(estructure_slot(extra_grid_line,
		Qvalue,Nil));
	if (FIXNUMP(value))
	    temp = value;
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    temp = note_use_of_managed_long_in_phrase(new_long);
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_2 = Vector_of_simple_float_array_pools;
		temp_3 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		}
		else {
		    temp_2 = Available_float_array_conses_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    temp = note_use_of_managed_float_in_phrase(new_float);
	}
	temp_1 = estructure_slot(extra_grid_line,Qcolor,Nil);
	if (temp_1);
	else
	    temp_1 = Qdefault;
	ab_loopvar__2 = phrase_cons(phrase_cons(temp,temp_1),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	result = phrase_cons(Qcm,temp_1);
    }
    else {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  aref_arg_2 = bv16_length - (SI_Long)2L;
	  aref_new_value_2 = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value_2);
	  aref_arg_2 = bv16_length - (SI_Long)1L;
	  aref_new_value_2 = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value_2);
	  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	  current_wide_string = wide_string_bv16;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		  3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_3,list_constant_3);
		  tformat(2,string_constant_3,list_constant_39);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_4,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_extra_value_grid_lines_evaluation_setter:
    return result;
}

/* EXTRA-VALUE-GRID-LINES-EVALUATION-GETTER */
Object extra_value_grid_lines_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object value_color_pair, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, gensymed_symbol_1, temp, value, item_or_value;
    Object amf_available_array_cons_qm, amf_array, temp_1, amf_result;
    Object new_float, gensymed_symbol_3, x2, temp_3, temp_4;
    SI_Long gensymed_symbol_2, svref_arg_2;
    char temp_2;
    double aref_new_value;

    x_note_fn_call(175,76);
    if (slot_value) {
	value_color_pair = Nil;
	ab_loop_list_ = CDR(slot_value);
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	value_color_pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_1 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_2 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_2 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol_1,(gensymed_symbol_2 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_1,FIX((SI_Long)3L)) = Qvalue;
	else {
	    temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qvalue;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    value = CAR(value_color_pair);
	    if (FIXNUMP(value))
		item_or_value = value;
	    else if ( !TRUEP(value))
		item_or_value = Evaluation_false_value;
	    else if (EQ(value,T))
		item_or_value = Evaluation_true_value;
	    else if (SYMBOLP(value))
		item_or_value = value;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_float(value);
	    else if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp = Vector_of_simple_float_array_pools;
		    temp_1 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp = 
				ISVREF(Available_float_array_conses_tail_vector,
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		item_or_value = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_long(value);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L)
		item_or_value = make_evaluation_long(value);
	    else if (text_string_p(value))
		item_or_value = copy_as_wide_string(value);
	    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		gensymed_symbol_3 = M_CAR(value);
		if (FIXNUM_EQ(gensymed_symbol_3,Truth))
		    item_or_value = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_3,Falsity))
		    item_or_value = Evaluation_false_value;
		else
		    item_or_value = eval_cons_1(gensymed_symbol_3,
			    Qtruth_value);
	    }
	    else
		item_or_value = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(value));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_1,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    value = CAR(value_color_pair);
	    if (FIXNUMP(value))
		item_or_value = value;
	    else if ( !TRUEP(value))
		item_or_value = Evaluation_false_value;
	    else if (EQ(value,T))
		item_or_value = Evaluation_true_value;
	    else if (SYMBOLP(value))
		item_or_value = value;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_float(value);
	    else if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_1 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		item_or_value = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		item_or_value = copy_managed_long(value);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L)
		item_or_value = make_evaluation_long(value);
	    else if (text_string_p(value))
		item_or_value = copy_as_wide_string(value);
	    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		gensymed_symbol_3 = M_CAR(value);
		if (FIXNUM_EQ(gensymed_symbol_3,Truth))
		    item_or_value = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_3,Falsity))
		    item_or_value = Evaluation_false_value;
		else
		    item_or_value = eval_cons_1(gensymed_symbol_3,
			    Qtruth_value);
	    }
	    else
		item_or_value = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(value));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = temp_1;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_1,FIX((SI_Long)5L)) = Qcolor;
	else {
	    temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qcolor;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = CDR(value_color_pair);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_1,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    item_or_value = CDR(value_color_pair);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = temp_1;
	}
	ab_loopvar__1 = eval_cons_1(eval_cons_1(gensymed_symbol_1,
		Qab_structure),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp_4 = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp_4 = Qnil;
      end_1:;
    }
    else
	temp_4 = Nil;
    GENSYM_RETURN_ONE(temp_4);
    return VALUES_1(Nil);
}

static Object string_constant_48;  /* ", " */

static Object string_constant_49;  /* "at " */

static Object string_constant_50;  /* " in " */

/* WRITE-EXTRA-VALUE-GRID-LINES-FROM-SLOT */
Object write_extra_value_grid_lines_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object number, color_spec, ab_loop_list_, first_p, ab_loop_iter_flag_;
    Object ab_loop_desetq_;

    x_note_fn_call(175,77);
    if (slot_value) {
	number = Nil;
	color_spec = Nil;
	ab_loop_list_ = CDR(slot_value);
	first_p = T;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	number = CAR(ab_loop_desetq_);
	color_spec = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    first_p = Nil;
	if ( !TRUEP(first_p))
	    twrite(string_constant_48);
	twrite(string_constant_49);
	twrite(number);
	if ( !EQ(color_spec,Qdefault)) {
	    twrite(string_constant_50);
	    twrite(color_spec);
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)4L));
}

static Object string_constant_51;  /* "Must specify between 1 and 15 significant digits" */

/* COMPILE-SIGNIFICANT-DIGIT-SPEC-FOR-SLOT */
Object compile_significant_digit_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,78);
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
    if ((SI_Long)1L <= IFIX(parse_result) && IFIX(parse_result) <= 
	    (SI_Long)15L)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_51);
	return VALUES_2(temp,temp_1);
    }
}

static Object list_constant_40;    /* # */

/* SIGNIFICANT-DIGIT-SPEC-EVALUATION-SETTER */
Object significant_digit_spec_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,79);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_40))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qinteger,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_significant_digit_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_significant_digit_spec_evaluation_setter:
    return result;
}

/* SIGNIFICANT-DIGIT-SPEC-EVALUATION-GETTER */
Object significant_digit_spec_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(175,80);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* WRITE-SIGNIFICANT-DIGIT-SPEC-FROM-SLOT */
Object write_significant_digit_spec_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(175,81);
    return twrite(slot_value);
}

static Object string_constant_52;  /* "Must specify a range slack of 0 to 100 percent" */

/* COMPILE-RANGE-SLACK-SPEC-FOR-SLOT */
Object compile_range_slack_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,82);
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
    if ((SI_Long)0L <= IFIX(parse_result) && IFIX(parse_result) <= 
	    (SI_Long)100L)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_52);
	return VALUES_2(temp,temp_1);
    }
}

static Object list_constant_41;    /* # */

/* RANGE-SLACK-SPEC-EVALUATION-SETTER */
Object range_slack_spec_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,83);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_41))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qinteger,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_range_slack_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_range_slack_spec_evaluation_setter:
    return result;
}

/* RANGE-SLACK-SPEC-EVALUATION-GETTER */
Object range_slack_spec_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(175,84);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* WRITE-RANGE-SLACK-SPEC-FROM-SLOT */
Object write_range_slack_spec_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(175,85);
    return twrite(slot_value);
}

static Object string_constant_53;  /* "Must specify between 0 and 50 grid lines per label" */

/* COMPILE-GRID-LINE-RATIO-FOR-SLOT */
Object compile_grid_line_ratio_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,86);
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
    if ((SI_Long)0L <= IFIX(parse_result) && IFIX(parse_result) <= 
	    (SI_Long)50L)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_53);
	return VALUES_2(temp,temp_1);
    }
}

static Object list_constant_42;    /* # */

/* GRID-LINE-RATIO-EVALUATION-SETTER */
Object grid_line_ratio_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,87);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_42))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qinteger,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_grid_line_ratio_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_grid_line_ratio_evaluation_setter:
    return result;
}

/* GRID-LINE-RATIO-EVALUATION-GETTER */
Object grid_line_ratio_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(175,88);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* WRITE-GRID-LINE-RATIO-FROM-SLOT */
Object write_grid_line_ratio_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(175,89);
    return twrite(slot_value);
}

static Object Qinterval_with_granularity;  /* interval-with-granularity */

static Object Qdisplay_interval;   /* display-interval */

static Object Qslot_value_compiler;  /* slot-value-compiler */

static Object Qquantity_interval;  /* quantity-interval */

/* COMPILE-PLOT-UPDATE-INTERVAL-SPEC-FOR-SLOT */
Object compile_plot_update_interval_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, display_interval_parse_result, error_qm;
    Object quantity_interval_parse_result;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(175,90);
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
    if (CONSP(parse_result) && EQ(CAR(parse_result),
	    Qinterval_with_granularity)) {
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_interval),
		Qslot_value_compiler);
	result = funcall(7,temp,CADR(parse_result),Nil,Nil,Nil,Nil,Nil);
	MVS_2(result,display_interval_parse_result,error_qm);
	if (EQ(display_interval_parse_result,Bad_phrase))
	    return VALUES_2(Bad_phrase,error_qm);
	else {
	    temp = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qquantity_interval),
		    Qslot_value_compiler);
	    result = funcall(7,temp,CADDR(parse_result),Nil,Nil,Nil,Nil,Nil);
	    MVS_2(result,quantity_interval_parse_result,error_qm);
	    if (EQ(quantity_interval_parse_result,Bad_phrase))
		return VALUES_2(Bad_phrase,error_qm);
	    else
		return slot_value_list_3(Qinterval_with_granularity,
			display_interval_parse_result,
			quantity_interval_parse_result);
	}
    }
    else
	return funcall(7,
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_interval),
		Qslot_value_compiler),parse_result,Nil,Nil,Nil,Nil,Nil);
}

static Object Qslot_value_writer;  /* slot-value-writer */

static Object array_constant_37;   /* # */

/* WRITE-PLOT-UPDATE-INTERVAL-SPEC-FROM-SLOT */
Object write_plot_update_interval_spec_from_slot(slot_value,frame)
    Object slot_value, frame;
{
    Object temp;

    x_note_fn_call(175,91);
    if (CONSP(slot_value) && EQ(CAR(slot_value),Qinterval_with_granularity)) {
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_interval),
		Qslot_value_writer);
	FUNCALL_2(temp,CADR(slot_value),frame);
	twrite_beginning_of_wide_string(array_constant_37,FIX((SI_Long)46L));
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qquantity_interval),
		Qslot_value_writer);
	return FUNCALL_2(temp,CADDR(slot_value),frame);
    }
    else {
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_interval),
		Qslot_value_writer);
	return FUNCALL_2(temp,slot_value,frame);
    }
}

/* PLOT-UPDATE-INTERVAL-PERIOD */
Object plot_update_interval_period(plot_update_interval)
    Object plot_update_interval;
{
    x_note_fn_call(175,92);
    if (CONSP(plot_update_interval) && EQ(CAR(plot_update_interval),
	    Qinterval_with_granularity))
	return VALUES_1(CADR(plot_update_interval));
    else
	return VALUES_1(plot_update_interval);
}

/* PLOT-UPDATE-INTERVAL-GRANULARITY? */
Object plot_update_interval_granularity_qm(plot_update_interval)
    Object plot_update_interval;
{
    x_note_fn_call(175,93);
    if (CONSP(plot_update_interval) && EQ(CAR(plot_update_interval),
	    Qinterval_with_granularity))
	return VALUES_1(CADDR(plot_update_interval));
    else
	return VALUES_1(Nil);
}

static Object Qcompute_automatically;  /* compute-automatically */

static Object string_constant_54;  /* "Must specify interval of at least 1 second." */

/* COMPILE-TREND-CHART-SCROLL-INTERVAL-FOR-SLOT */
Object compile_trend_chart_scroll_interval_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object thing, temp_1, temp_2;
    char temp;
    double arg, arg_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(175,94);
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
    if (EQ(parse_result,Qcompute_automatically))
	return VALUES_1(Nil);
    else {
	thing = CAR(parse_result);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		arg = DFLOAT_ISAREF_1(CAR(parse_result),(SI_Long)0L);
		arg_1 = 1.0;
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else
	    temp = IFIX(CAR(parse_result)) < (SI_Long)1L;
	if (temp) {
	    temp_1 = Bad_phrase;
	    temp_2 = copy_text_string(string_constant_54);
	    return VALUES_2(temp_1,temp_2);
	}
	else
	    return VALUES_1(parse_result);
    }
}

static Object list_constant_43;    /* # */

static Object list_constant_44;    /* # */

static Object Qscroll_interval_type;  /* scroll-interval-type */

static Object array_constant_38;   /* # */

/* TREND-CHART-SCROLL-INTERVAL-EVALUATION-SETTER */
Object trend_chart_scroll_interval_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object scroll_interval_type, seconds_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(175,95);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_43))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_trend_chart_scroll_interval_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    scroll_interval_type = estructure_slot(evaluation_value,
	    Qscroll_interval_type,Nil);
    if (EQ(scroll_interval_type,Qautomatic))
	result = VALUES_1(Qcompute_automatically);
    else if (EQ(scroll_interval_type,Qinterval)) {
	seconds_qm = estructure_slot(evaluation_value,Qinterval,Nil);
	if (seconds_qm)
	    result = phrase_cons(seconds_qm,Qseconds);
	else {
	    temp = Bad_phrase;
	    temp_1 = 
		    copy_constant_wide_string_given_length(array_constant_38,
		    FIX((SI_Long)21L));
	    result = VALUES_2(temp,temp_1);
	}
    }
    else
	result = VALUES_1(Qnil);
  end_trend_chart_scroll_interval_evaluation_setter:
    return result;
}

/* TREND-CHART-SCROLL-INTERVAL-EVALUATION-GETTER */
Object trend_chart_scroll_interval_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(175,96);
    if (slot_value) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qscroll_interval_type;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qscroll_interval_type;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qinterval;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qinterval;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qinterval;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qinterval;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = CAR(slot_value);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = CAR(slot_value);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp_2 = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qscroll_interval_type;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qscroll_interval_type;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qautomatic;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qautomatic;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp_2 = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    GENSYM_RETURN_ONE(temp_2);
    return VALUES_1(Nil);
}

/* WRITE-TREND-CHART-SCROLL-INTERVAL-FROM-SLOT */
Object write_trend_chart_scroll_interval_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(175,97);
    if (EQ(slot_value,Nil))
	return twrite_beginning_of_wide_string(array_constant_29,
		FIX((SI_Long)9L));
    else
	return print_constant(2,CAR(slot_value),Qseconds);
}

/* RECLAIM-2D-INCOMPLETE-PAINTING-ACTIONS-VALUE */
Object reclaim_2d_incomplete_painting_actions_value(value,frame)
    Object value, frame;
{
    x_note_fn_call(175,98);
    clear_incomplete_painting_actions(frame);
    return VALUES_1(Nil);
}

Object The_type_description_of_display_pane = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_display_panes, Qchain_of_available_display_panes);

DEFINE_VARIABLE_WITH_SYMBOL(Display_pane_count, Qdisplay_pane_count);

Object Chain_of_available_display_panes_vector = UNBOUND;

/* DISPLAY-PANE-STRUCTURE-MEMORY-USAGE */
Object display_pane_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(175,99);
    temp = Display_pane_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)12L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-DISPLAY-PANE-COUNT */
Object outstanding_display_pane_count()
{
    Object def_structure_display_pane_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(175,100);
    gensymed_symbol = IFIX(Display_pane_count);
    def_structure_display_pane_variable = Chain_of_available_display_panes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_display_pane_variable))
	goto end_loop;
    def_structure_display_pane_variable = 
	    ISVREF(def_structure_display_pane_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-DISPLAY-PANE-1 */
Object reclaim_display_pane_1(display_pane)
    Object display_pane;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(175,101);
    inline_note_reclaim_cons(display_pane,Nil);
    structure_being_reclaimed = display_pane;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_slot_value_list_1(ISVREF(display_pane,(SI_Long)11L));
      SVREF(display_pane,FIX((SI_Long)11L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_display_panes_vector,
	    IFIX(Current_thread_index));
    SVREF(display_pane,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_display_panes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = display_pane;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-DISPLAY-PANE */
Object reclaim_structure_for_display_pane(display_pane)
    Object display_pane;
{
    x_note_fn_call(175,102);
    return reclaim_display_pane_1(display_pane);
}

static Object Qg2_defstruct_structure_name_display_pane_g2_struct;  /* g2-defstruct-structure-name::display-pane-g2-struct */

/* MAKE-PERMANENT-DISPLAY-PANE-STRUCTURE-INTERNAL */
Object make_permanent_display_pane_structure_internal()
{
    Object def_structure_display_pane_variable;
    Object defstruct_g2_display_pane_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(175,103);
    def_structure_display_pane_variable = Nil;
    atomic_incff_symval(Qdisplay_pane_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_display_pane_variable = Nil;
	gensymed_symbol = (SI_Long)12L;
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
	defstruct_g2_display_pane_variable = the_array;
	SVREF(defstruct_g2_display_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_display_pane_g2_struct;
	def_structure_display_pane_variable = 
		defstruct_g2_display_pane_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_display_pane_variable);
}

static Object Qwhite;              /* white */

static Object Qblack;              /* black */

/* MAKE-DISPLAY-PANE-1 */
Object make_display_pane_1()
{
    Object def_structure_display_pane_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(175,104);
    def_structure_display_pane_variable = 
	    ISVREF(Chain_of_available_display_panes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_display_pane_variable) {
	svref_arg_1 = Chain_of_available_display_panes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_display_pane_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_display_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_display_pane_g2_struct;
    }
    else
	def_structure_display_pane_variable = 
		make_permanent_display_pane_structure_internal();
    inline_note_allocate_cons(def_structure_display_pane_variable,Nil);
    SVREF(def_structure_display_pane_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_display_pane_variable,(SI_Long)2L) = FIX((SI_Long)0L);
    ISVREF(def_structure_display_pane_variable,(SI_Long)3L) = FIX((SI_Long)0L);
    ISVREF(def_structure_display_pane_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    ISVREF(def_structure_display_pane_variable,(SI_Long)5L) = FIX((SI_Long)0L);
    SVREF(def_structure_display_pane_variable,FIX((SI_Long)6L)) = Qwhite;
    SVREF(def_structure_display_pane_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_display_pane_variable,FIX((SI_Long)8L)) = Qblack;
    SVREF(def_structure_display_pane_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_display_pane_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_display_pane_variable,FIX((SI_Long)11L)) = Nil;
    return VALUES_1(def_structure_display_pane_variable);
}

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* RECLAIM-PANE-TREE */
Object reclaim_pane_tree(display_pane)
    Object display_pane;
{
    Object sub_pane, ab_loop_list_, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(175,105);
    sub_pane = Nil;
    ab_loop_list_ = ISVREF(display_pane,(SI_Long)11L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_pane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_pane_tree(sub_pane);
    goto next_loop;
  end_loop:
    gensymed_symbol = ISVREF(display_pane,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = display_pane;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(Qnil);
}

Object The_type_description_of_axis_pane = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_axis_panes, Qchain_of_available_axis_panes);

DEFINE_VARIABLE_WITH_SYMBOL(Axis_pane_count, Qaxis_pane_count);

Object Chain_of_available_axis_panes_vector = UNBOUND;

/* AXIS-PANE-STRUCTURE-MEMORY-USAGE */
Object axis_pane_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(175,106);
    temp = Axis_pane_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)27L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-AXIS-PANE-COUNT */
Object outstanding_axis_pane_count()
{
    Object def_structure_axis_pane_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(175,107);
    gensymed_symbol = IFIX(Axis_pane_count);
    def_structure_axis_pane_variable = Chain_of_available_axis_panes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_axis_pane_variable))
	goto end_loop;
    def_structure_axis_pane_variable = 
	    ISVREF(def_structure_axis_pane_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-AXIS-PANE-1 */
Object reclaim_axis_pane_1(axis_pane)
    Object axis_pane;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(175,108);
    inline_note_reclaim_cons(axis_pane,Nil);
    structure_being_reclaimed = axis_pane;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_slot_value_list_1(ISVREF(axis_pane,(SI_Long)11L));
      SVREF(axis_pane,FIX((SI_Long)11L)) = Nil;
      reclaim_slot_value(ISVREF(axis_pane,(SI_Long)12L));
      SVREF(axis_pane,FIX((SI_Long)12L)) = Nil;
      reclaim_slot_value(ISVREF(axis_pane,(SI_Long)23L));
      SVREF(axis_pane,FIX((SI_Long)23L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_axis_panes_vector,
	    IFIX(Current_thread_index));
    SVREF(axis_pane,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_axis_panes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = axis_pane;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-AXIS-PANE */
Object reclaim_structure_for_axis_pane(axis_pane)
    Object axis_pane;
{
    x_note_fn_call(175,109);
    return reclaim_axis_pane_1(axis_pane);
}

static Object Qg2_defstruct_structure_name_axis_pane_g2_struct;  /* g2-defstruct-structure-name::axis-pane-g2-struct */

/* MAKE-PERMANENT-AXIS-PANE-STRUCTURE-INTERNAL */
Object make_permanent_axis_pane_structure_internal()
{
    Object def_structure_axis_pane_variable, defstruct_g2_axis_pane_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(175,110);
    def_structure_axis_pane_variable = Nil;
    atomic_incff_symval(Qaxis_pane_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_axis_pane_variable = Nil;
	gensymed_symbol = (SI_Long)27L;
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
	defstruct_g2_axis_pane_variable = the_array;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_axis_pane_g2_struct;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_axis_pane_variable,FIX((SI_Long)11L)) = Nil;
	def_structure_axis_pane_variable = defstruct_g2_axis_pane_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_axis_pane_variable);
}

/* MAKE-AXIS-PANE-1 */
Object make_axis_pane_1()
{
    Object def_structure_axis_pane_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(175,111);
    def_structure_axis_pane_variable = 
	    ISVREF(Chain_of_available_axis_panes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_axis_pane_variable) {
	svref_arg_1 = Chain_of_available_axis_panes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_axis_pane_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_axis_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_axis_pane_g2_struct;
    }
    else
	def_structure_axis_pane_variable = 
		make_permanent_axis_pane_structure_internal();
    inline_note_allocate_cons(def_structure_axis_pane_variable,Nil);
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_axis_pane_variable,(SI_Long)2L) = FIX((SI_Long)0L);
    ISVREF(def_structure_axis_pane_variable,(SI_Long)3L) = FIX((SI_Long)0L);
    ISVREF(def_structure_axis_pane_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    ISVREF(def_structure_axis_pane_variable,(SI_Long)5L) = FIX((SI_Long)0L);
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)6L)) = Qwhite;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)8L)) = Qblack;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)13L)) = Qblack;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)14L)) = Qleft;
    ISVREF(def_structure_axis_pane_variable,(SI_Long)15L) = FIX((SI_Long)0L);
    ISVREF(def_structure_axis_pane_variable,(SI_Long)16L) = FIX((SI_Long)0L);
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)17L)) = Nil;
    ISVREF(def_structure_axis_pane_variable,(SI_Long)18L) = FIX((SI_Long)0L);
    ISVREF(def_structure_axis_pane_variable,(SI_Long)19L) = FIX((SI_Long)0L);
    ISVREF(def_structure_axis_pane_variable,(SI_Long)20L) = FIX((SI_Long)0L);
    ISVREF(def_structure_axis_pane_variable,(SI_Long)21L) = FIX((SI_Long)0L);
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)22L)) = Nil;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)23L)) = Nil;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)24L)) = Nil;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)25L)) = Nil;
    SVREF(def_structure_axis_pane_variable,FIX((SI_Long)26L)) = Nil;
    return VALUES_1(def_structure_axis_pane_variable);
}

Object The_type_description_of_trend_chart_pane = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_trend_chart_panes, Qchain_of_available_trend_chart_panes);

DEFINE_VARIABLE_WITH_SYMBOL(Trend_chart_pane_count, Qtrend_chart_pane_count);

Object Chain_of_available_trend_chart_panes_vector = UNBOUND;

/* TREND-CHART-PANE-STRUCTURE-MEMORY-USAGE */
Object trend_chart_pane_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(175,112);
    temp = Trend_chart_pane_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TREND-CHART-PANE-COUNT */
Object outstanding_trend_chart_pane_count()
{
    Object def_structure_trend_chart_pane_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(175,113);
    gensymed_symbol = IFIX(Trend_chart_pane_count);
    def_structure_trend_chart_pane_variable = 
	    Chain_of_available_trend_chart_panes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_trend_chart_pane_variable))
	goto end_loop;
    def_structure_trend_chart_pane_variable = 
	    ISVREF(def_structure_trend_chart_pane_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TREND-CHART-PANE-1 */
Object reclaim_trend_chart_pane_1(trend_chart_pane)
    Object trend_chart_pane;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(175,114);
    inline_note_reclaim_cons(trend_chart_pane,Nil);
    structure_being_reclaimed = trend_chart_pane;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_slot_value_list_1(ISVREF(trend_chart_pane,(SI_Long)11L));
      SVREF(trend_chart_pane,FIX((SI_Long)11L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_trend_chart_panes_vector,
	    IFIX(Current_thread_index));
    SVREF(trend_chart_pane,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_trend_chart_panes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = trend_chart_pane;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TREND-CHART-PANE */
Object reclaim_structure_for_trend_chart_pane(trend_chart_pane)
    Object trend_chart_pane;
{
    x_note_fn_call(175,115);
    return reclaim_trend_chart_pane_1(trend_chart_pane);
}

static Object Qg2_defstruct_structure_name_trend_chart_pane_g2_struct;  /* g2-defstruct-structure-name::trend-chart-pane-g2-struct */

/* MAKE-PERMANENT-TREND-CHART-PANE-STRUCTURE-INTERNAL */
Object make_permanent_trend_chart_pane_structure_internal()
{
    Object def_structure_trend_chart_pane_variable;
    Object defstruct_g2_trend_chart_pane_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(175,116);
    def_structure_trend_chart_pane_variable = Nil;
    atomic_incff_symval(Qtrend_chart_pane_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_trend_chart_pane_variable = Nil;
	gensymed_symbol = (SI_Long)13L;
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
	defstruct_g2_trend_chart_pane_variable = the_array;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_trend_chart_pane_g2_struct;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_trend_chart_pane_variable,FIX((SI_Long)11L)) = Nil;
	def_structure_trend_chart_pane_variable = 
		defstruct_g2_trend_chart_pane_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_trend_chart_pane_variable);
}

/* MAKE-TREND-CHART-PANE-1 */
Object make_trend_chart_pane_1()
{
    Object def_structure_trend_chart_pane_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(175,117);
    def_structure_trend_chart_pane_variable = 
	    ISVREF(Chain_of_available_trend_chart_panes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_trend_chart_pane_variable) {
	svref_arg_1 = Chain_of_available_trend_chart_panes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_trend_chart_pane_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_trend_chart_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_trend_chart_pane_g2_struct;
    }
    else
	def_structure_trend_chart_pane_variable = 
		make_permanent_trend_chart_pane_structure_internal();
    inline_note_allocate_cons(def_structure_trend_chart_pane_variable,Nil);
    SVREF(def_structure_trend_chart_pane_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_trend_chart_pane_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_trend_chart_pane_variable,(SI_Long)3L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_trend_chart_pane_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_trend_chart_pane_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_trend_chart_pane_variable,FIX((SI_Long)6L)) = Qwhite;
    SVREF(def_structure_trend_chart_pane_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_trend_chart_pane_variable,FIX((SI_Long)8L)) = Qblack;
    SVREF(def_structure_trend_chart_pane_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_trend_chart_pane_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_trend_chart_pane_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_trend_chart_pane_variable,FIX((SI_Long)12L)) = T;
    return VALUES_1(def_structure_trend_chart_pane_variable);
}

Object The_type_description_of_legend_pane = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_legend_panes, Qchain_of_available_legend_panes);

DEFINE_VARIABLE_WITH_SYMBOL(Legend_pane_count, Qlegend_pane_count);

Object Chain_of_available_legend_panes_vector = UNBOUND;

/* LEGEND-PANE-STRUCTURE-MEMORY-USAGE */
Object legend_pane_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(175,118);
    temp = Legend_pane_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)14L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-LEGEND-PANE-COUNT */
Object outstanding_legend_pane_count()
{
    Object def_structure_legend_pane_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(175,119);
    gensymed_symbol = IFIX(Legend_pane_count);
    def_structure_legend_pane_variable = Chain_of_available_legend_panes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_legend_pane_variable))
	goto end_loop;
    def_structure_legend_pane_variable = 
	    ISVREF(def_structure_legend_pane_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-LEGEND-PANE-1 */
Object reclaim_legend_pane_1(legend_pane)
    Object legend_pane;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(175,120);
    inline_note_reclaim_cons(legend_pane,Nil);
    structure_being_reclaimed = legend_pane;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_slot_value_list_1(ISVREF(legend_pane,(SI_Long)11L));
      SVREF(legend_pane,FIX((SI_Long)11L)) = Nil;
      reclaim_slot_value(ISVREF(legend_pane,(SI_Long)12L));
      SVREF(legend_pane,FIX((SI_Long)12L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_legend_panes_vector,
	    IFIX(Current_thread_index));
    SVREF(legend_pane,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_legend_panes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = legend_pane;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LEGEND-PANE */
Object reclaim_structure_for_legend_pane(legend_pane)
    Object legend_pane;
{
    x_note_fn_call(175,121);
    return reclaim_legend_pane_1(legend_pane);
}

static Object Qg2_defstruct_structure_name_legend_pane_g2_struct;  /* g2-defstruct-structure-name::legend-pane-g2-struct */

/* MAKE-PERMANENT-LEGEND-PANE-STRUCTURE-INTERNAL */
Object make_permanent_legend_pane_structure_internal()
{
    Object def_structure_legend_pane_variable;
    Object defstruct_g2_legend_pane_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(175,122);
    def_structure_legend_pane_variable = Nil;
    atomic_incff_symval(Qlegend_pane_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_legend_pane_variable = Nil;
	gensymed_symbol = (SI_Long)14L;
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
	defstruct_g2_legend_pane_variable = the_array;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_legend_pane_g2_struct;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_legend_pane_variable,FIX((SI_Long)11L)) = Nil;
	def_structure_legend_pane_variable = defstruct_g2_legend_pane_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_legend_pane_variable);
}

/* MAKE-LEGEND-PANE-1 */
Object make_legend_pane_1()
{
    Object def_structure_legend_pane_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(175,123);
    def_structure_legend_pane_variable = 
	    ISVREF(Chain_of_available_legend_panes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_legend_pane_variable) {
	svref_arg_1 = Chain_of_available_legend_panes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_legend_pane_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_legend_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_legend_pane_g2_struct;
    }
    else
	def_structure_legend_pane_variable = 
		make_permanent_legend_pane_structure_internal();
    inline_note_allocate_cons(def_structure_legend_pane_variable,Nil);
    SVREF(def_structure_legend_pane_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_legend_pane_variable,(SI_Long)2L) = FIX((SI_Long)0L);
    ISVREF(def_structure_legend_pane_variable,(SI_Long)3L) = FIX((SI_Long)0L);
    ISVREF(def_structure_legend_pane_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    ISVREF(def_structure_legend_pane_variable,(SI_Long)5L) = FIX((SI_Long)0L);
    SVREF(def_structure_legend_pane_variable,FIX((SI_Long)6L)) = Qwhite;
    SVREF(def_structure_legend_pane_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_legend_pane_variable,FIX((SI_Long)8L)) = Qblack;
    SVREF(def_structure_legend_pane_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_legend_pane_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_legend_pane_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_legend_pane_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_legend_pane_variable,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(def_structure_legend_pane_variable);
}

Object The_type_description_of_relative_time_pane = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_relative_time_panes, Qchain_of_available_relative_time_panes);

DEFINE_VARIABLE_WITH_SYMBOL(Relative_time_pane_count, Qrelative_time_pane_count);

Object Chain_of_available_relative_time_panes_vector = UNBOUND;

/* RELATIVE-TIME-PANE-STRUCTURE-MEMORY-USAGE */
Object relative_time_pane_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(175,124);
    temp = Relative_time_pane_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)14L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RELATIVE-TIME-PANE-COUNT */
Object outstanding_relative_time_pane_count()
{
    Object def_structure_relative_time_pane_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(175,125);
    gensymed_symbol = IFIX(Relative_time_pane_count);
    def_structure_relative_time_pane_variable = 
	    Chain_of_available_relative_time_panes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_relative_time_pane_variable))
	goto end_loop;
    def_structure_relative_time_pane_variable = 
	    ISVREF(def_structure_relative_time_pane_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RELATIVE-TIME-PANE-1 */
Object reclaim_relative_time_pane_1(relative_time_pane)
    Object relative_time_pane;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(175,126);
    inline_note_reclaim_cons(relative_time_pane,Nil);
    structure_being_reclaimed = relative_time_pane;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_slot_value_list_1(ISVREF(relative_time_pane,(SI_Long)11L));
      SVREF(relative_time_pane,FIX((SI_Long)11L)) = Nil;
      reclaim_slot_value(ISVREF(relative_time_pane,(SI_Long)13L));
      SVREF(relative_time_pane,FIX((SI_Long)13L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_relative_time_panes_vector,
	    IFIX(Current_thread_index));
    SVREF(relative_time_pane,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_relative_time_panes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = relative_time_pane;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RELATIVE-TIME-PANE */
Object reclaim_structure_for_relative_time_pane(relative_time_pane)
    Object relative_time_pane;
{
    x_note_fn_call(175,127);
    return reclaim_relative_time_pane_1(relative_time_pane);
}

static Object Qg2_defstruct_structure_name_relative_time_pane_g2_struct;  /* g2-defstruct-structure-name::relative-time-pane-g2-struct */

/* MAKE-PERMANENT-RELATIVE-TIME-PANE-STRUCTURE-INTERNAL */
Object make_permanent_relative_time_pane_structure_internal()
{
    Object def_structure_relative_time_pane_variable;
    Object defstruct_g2_relative_time_pane_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(175,128);
    def_structure_relative_time_pane_variable = Nil;
    atomic_incff_symval(Qrelative_time_pane_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_relative_time_pane_variable = Nil;
	gensymed_symbol = (SI_Long)14L;
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
	defstruct_g2_relative_time_pane_variable = the_array;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_relative_time_pane_g2_struct;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)10L)) 
		= Nil;
	SVREF(defstruct_g2_relative_time_pane_variable,FIX((SI_Long)11L)) 
		= Nil;
	def_structure_relative_time_pane_variable = 
		defstruct_g2_relative_time_pane_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_relative_time_pane_variable);
}

/* MAKE-RELATIVE-TIME-PANE-1 */
Object make_relative_time_pane_1()
{
    Object def_structure_relative_time_pane_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(175,129);
    def_structure_relative_time_pane_variable = 
	    ISVREF(Chain_of_available_relative_time_panes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_relative_time_pane_variable) {
	svref_arg_1 = Chain_of_available_relative_time_panes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_relative_time_pane_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_relative_time_pane_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_relative_time_pane_g2_struct;
    }
    else
	def_structure_relative_time_pane_variable = 
		make_permanent_relative_time_pane_structure_internal();
    inline_note_allocate_cons(def_structure_relative_time_pane_variable,Nil);
    SVREF(def_structure_relative_time_pane_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_relative_time_pane_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_relative_time_pane_variable,(SI_Long)3L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_relative_time_pane_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_relative_time_pane_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_relative_time_pane_variable,FIX((SI_Long)6L)) = Qwhite;
    SVREF(def_structure_relative_time_pane_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_relative_time_pane_variable,FIX((SI_Long)8L)) = Qblack;
    SVREF(def_structure_relative_time_pane_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_relative_time_pane_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_relative_time_pane_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_relative_time_pane_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_relative_time_pane_variable,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(def_structure_relative_time_pane_variable);
}

Object The_type_description_of_grid_pane = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_grid_panes, Qchain_of_available_grid_panes);

DEFINE_VARIABLE_WITH_SYMBOL(Grid_pane_count, Qgrid_pane_count);

Object Chain_of_available_grid_panes_vector = UNBOUND;

/* GRID-PANE-STRUCTURE-MEMORY-USAGE */
Object grid_pane_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(175,130);
    temp = Grid_pane_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)25L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GRID-PANE-COUNT */
Object outstanding_grid_pane_count()
{
    Object def_structure_grid_pane_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(175,131);
    gensymed_symbol = IFIX(Grid_pane_count);
    def_structure_grid_pane_variable = Chain_of_available_grid_panes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_grid_pane_variable))
	goto end_loop;
    def_structure_grid_pane_variable = 
	    ISVREF(def_structure_grid_pane_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GRID-PANE-1 */
Object reclaim_grid_pane_1(grid_pane)
    Object grid_pane;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(175,132);
    inline_note_reclaim_cons(grid_pane,Nil);
    structure_being_reclaimed = grid_pane;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_slot_value_list_1(ISVREF(grid_pane,(SI_Long)11L));
      SVREF(grid_pane,FIX((SI_Long)11L)) = Nil;
      reclaim_slot_value(ISVREF(grid_pane,(SI_Long)17L));
      SVREF(grid_pane,FIX((SI_Long)17L)) = Nil;
      reclaim_slot_value(ISVREF(grid_pane,(SI_Long)18L));
      SVREF(grid_pane,FIX((SI_Long)18L)) = Nil;
      reclaim_slot_value(ISVREF(grid_pane,(SI_Long)19L));
      SVREF(grid_pane,FIX((SI_Long)19L)) = Nil;
      reclaim_slot_value(ISVREF(grid_pane,(SI_Long)20L));
      SVREF(grid_pane,FIX((SI_Long)20L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_grid_panes_vector,
	    IFIX(Current_thread_index));
    SVREF(grid_pane,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_grid_panes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = grid_pane;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GRID-PANE */
Object reclaim_structure_for_grid_pane(grid_pane)
    Object grid_pane;
{
    x_note_fn_call(175,133);
    return reclaim_grid_pane_1(grid_pane);
}

static Object Qg2_defstruct_structure_name_grid_pane_g2_struct;  /* g2-defstruct-structure-name::grid-pane-g2-struct */

/* MAKE-PERMANENT-GRID-PANE-STRUCTURE-INTERNAL */
Object make_permanent_grid_pane_structure_internal()
{
    Object def_structure_grid_pane_variable, defstruct_g2_grid_pane_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(175,134);
    def_structure_grid_pane_variable = Nil;
    atomic_incff_symval(Qgrid_pane_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_grid_pane_variable = Nil;
	gensymed_symbol = (SI_Long)25L;
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
	defstruct_g2_grid_pane_variable = the_array;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_grid_pane_g2_struct;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_grid_pane_variable,FIX((SI_Long)11L)) = Nil;
	def_structure_grid_pane_variable = defstruct_g2_grid_pane_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_grid_pane_variable);
}

/* MAKE-GRID-PANE-1 */
Object make_grid_pane_1()
{
    Object def_structure_grid_pane_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(175,135);
    def_structure_grid_pane_variable = 
	    ISVREF(Chain_of_available_grid_panes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_grid_pane_variable) {
	svref_arg_1 = Chain_of_available_grid_panes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_grid_pane_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_grid_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_grid_pane_g2_struct;
    }
    else
	def_structure_grid_pane_variable = 
		make_permanent_grid_pane_structure_internal();
    inline_note_allocate_cons(def_structure_grid_pane_variable,Nil);
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_grid_pane_variable,(SI_Long)2L) = FIX((SI_Long)0L);
    ISVREF(def_structure_grid_pane_variable,(SI_Long)3L) = FIX((SI_Long)0L);
    ISVREF(def_structure_grid_pane_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    ISVREF(def_structure_grid_pane_variable,(SI_Long)5L) = FIX((SI_Long)0L);
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)6L)) = Qwhite;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)8L)) = Qblack;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)22L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)23L)) = Nil;
    SVREF(def_structure_grid_pane_variable,FIX((SI_Long)24L)) = Nil;
    return VALUES_1(def_structure_grid_pane_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_display_pane_left, Qcurrent_display_pane_left);

DEFINE_VARIABLE_WITH_SYMBOL(Current_display_pane_top, Qcurrent_display_pane_top);

DEFINE_VARIABLE_WITH_SYMBOL(Current_display_pane_right, Qcurrent_display_pane_right);

DEFINE_VARIABLE_WITH_SYMBOL(Current_display_pane_bottom, Qcurrent_display_pane_bottom);

DEFINE_VARIABLE_WITH_SYMBOL(Current_display_pane_height, Qcurrent_display_pane_height);

DEFINE_VARIABLE_WITH_SYMBOL(Current_display_pane_width, Qcurrent_display_pane_width);

static Object Qhairline;           /* hairline */

/* FOCUS-ON-DISPLAY-PANE */
Object focus_on_display_pane(display,display_pane)
    Object display, display_pane;
{
    Object display_pane_list, pane, gensymed_symbol, left, top, right, bottom;
    Object ab_loop_list_, border_style_qm, incff_1_arg, border_width;
    Object decff_1_arg, temp, temp_1;

    x_note_fn_call(175,136);
    display_pane_list = Qnil;
    pane = display_pane;
  next_loop:
    if ( !TRUEP(pane))
	goto end_loop;
    display_pane_list = slot_value_cons_1(pane,display_pane_list);
    pane = ISVREF(pane,(SI_Long)10L);
    goto next_loop;
  end_loop:;
    gensymed_symbol = ISVREF(display,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left = gensymed_symbol;
    gensymed_symbol = ISVREF(display,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top = gensymed_symbol;
    gensymed_symbol = ISVREF(display,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    right = gensymed_symbol;
    gensymed_symbol = ISVREF(display,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom = gensymed_symbol;
    pane = Nil;
    ab_loop_list_ = display_pane_list;
    border_style_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    pane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    border_style_qm = ISVREF(pane,(SI_Long)7L);
    incff_1_arg = ISVREF(pane,(SI_Long)2L);
    left = FIXNUM_ADD(left,incff_1_arg);
    incff_1_arg = ISVREF(pane,(SI_Long)3L);
    top = FIXNUM_ADD(top,incff_1_arg);
    right = FIXNUM_ADD(left,ISVREF(pane,(SI_Long)4L));
    bottom = FIXNUM_ADD(top,ISVREF(pane,(SI_Long)5L));
    if (border_style_qm) {
	border_width = EQ(border_style_qm,Qhairline) ? FIX((SI_Long)1L) : 
		border_style_qm;
	incff_1_arg = border_width;
	left = FIXNUM_ADD(left,incff_1_arg);
	incff_1_arg = border_width;
	top = FIXNUM_ADD(top,incff_1_arg);
	decff_1_arg = border_width;
	right = FIXNUM_MINUS(right,decff_1_arg);
	decff_1_arg = border_width;
	bottom = FIXNUM_MINUS(bottom,decff_1_arg);
    }
    goto next_loop_1;
  end_loop_1:
    reclaim_slot_value_list_1(display_pane_list);
    temp = FIXNUM_MINUS(bottom,top);
    temp_1 = FIXNUM_MINUS(right,left);
    return VALUES_6(left,top,right,bottom,temp,temp_1);
    return VALUES_1(Qnil);
}

Object Minimum_data_window_size = UNBOUND;

Object Minimum_data_window_margin = UNBOUND;

Object Maximum_plots_per_trend_chart = UNBOUND;

Object Trend_chart_plot_slot_increment = UNBOUND;

static Object Qplot;               /* plot */

/* COMPILE-TREND-CHART-PLOTS-GRAMMAR-SPEC-FOR-SLOT */
Object compile_trend_chart_plots_grammar_spec_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,137);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_compound_slot_value(parse_result,frame,slot_name,Qplot,Qt);
}

static Object Qvalue_axis;         /* value-axis */

/* COMPILE-TREND-CHART-VALUE-AXES-GRAMMAR-SPEC-FOR-SLOT */
Object compile_trend_chart_value_axes_grammar_spec_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,138);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_compound_slot_value(parse_result,frame,slot_name,
	    Qvalue_axis,Qt);
}

static Object Qtime_axis;          /* time-axis */

/* COMPILE-TREND-CHART-TIME-AXIS-GRAMMAR-SPEC-FOR-SLOT */
Object compile_trend_chart_time_axis_grammar_spec_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,139);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_compound_slot_value(parse_result,frame,slot_name,
	    Qtime_axis,Qnil);
}

static Object Qpoint_format;       /* point-format */

/* COMPILE-TREND-CHART-POINT-FORMATS-GRAMMAR-SPEC-FOR-SLOT */
Object compile_trend_chart_point_formats_grammar_spec_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,140);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_compound_slot_value(parse_result,frame,slot_name,
	    Qpoint_format,Qt);
}

static Object Qconnector_format;   /* connector-format */

/* COMPILE-TREND-CHART-CONNECTOR-FORMATS-GRAMMAR-SPEC-FOR-SLOT */
Object compile_trend_chart_connector_formats_grammar_spec_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,141);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_compound_slot_value(parse_result,frame,slot_name,
	    Qconnector_format,Qt);
}

static Object Qtrend_chart_format;  /* trend-chart-format */

/* COMPILE-TREND-CHART-FORMAT-GRAMMAR-SPEC-FOR-SLOT */
Object compile_trend_chart_format_grammar_spec_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(175,142);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_compound_slot_value(parse_result,frame,slot_name,
	    Qtrend_chart_format,Qnil);
}

/* WRITE-TREND-CHART-PLOTS-GRAMMAR-SPEC-FROM-SLOT */
Object write_trend_chart_plots_grammar_spec_from_slot(slot_value,frame)
    Object slot_value, frame;
{
    x_note_fn_call(175,143);
    if (Write_compound_slots_parseably_qm)
	return write_multiple_compound_slot_value(frame,slot_value,Qplot);
    else
	return write_component_group_count(slot_value,Qplot);
}

/* WRITE-TREND-CHART-VALUE-AXES-GRAMMAR-SPEC-FROM-SLOT */
Object write_trend_chart_value_axes_grammar_spec_from_slot(slot_value,frame)
    Object slot_value, frame;
{
    x_note_fn_call(175,144);
    if (Write_compound_slots_parseably_qm)
	return write_multiple_compound_slot_value(frame,slot_value,
		Qvalue_axis);
    else
	return write_component_group_count(slot_value,Qvalue_axis);
}

/* WRITE-TREND-CHART-TIME-AXIS-GRAMMAR-SPEC-FROM-SLOT */
Object write_trend_chart_time_axis_grammar_spec_from_slot(slot_value,frame)
    Object slot_value, frame;
{
    x_note_fn_call(175,145);
    if (Write_compound_slots_parseably_qm)
	return write_single_compound_slot_value(frame,slot_value,Qtime_axis);
    else
	return write_component_group_count(slot_value,Qtime_axis);
}

/* WRITE-TREND-CHART-POINT-FORMATS-GRAMMAR-SPEC-FROM-SLOT */
Object write_trend_chart_point_formats_grammar_spec_from_slot(slot_value,frame)
    Object slot_value, frame;
{
    x_note_fn_call(175,146);
    if (Write_compound_slots_parseably_qm)
	return write_multiple_compound_slot_value(frame,slot_value,
		Qpoint_format);
    else
	return write_component_group_count(slot_value,Qpoint_format);
}

/* WRITE-TREND-CHART-CONNECTOR-FORMATS-GRAMMAR-SPEC-FROM-SLOT */
Object write_trend_chart_connector_formats_grammar_spec_from_slot(slot_value,
	    frame)
    Object slot_value, frame;
{
    x_note_fn_call(175,147);
    if (Write_compound_slots_parseably_qm)
	return write_multiple_compound_slot_value(frame,slot_value,
		Qconnector_format);
    else
	return write_component_group_count(slot_value,Qconnector_format);
}

/* WRITE-TREND-CHART-FORMAT-GRAMMAR-SPEC-FROM-SLOT */
Object write_trend_chart_format_grammar_spec_from_slot(slot_value,frame)
    Object slot_value, frame;
{
    x_note_fn_call(175,148);
    if (Write_compound_slots_parseably_qm)
	return write_single_compound_slot_value(frame,slot_value,
		Qtrend_chart_format);
    else
	return write_component_group_count(slot_value,Qtrend_chart_format);
}

static Object list_constant_45;    /* # */

static Object Qtrend_chart_plots;  /* trend-chart-plots */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

/* PUT-TREND-CHART-PLOTS */
Object put_trend_chart_plots(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(175,149);
    if (memq_function(CAR(new_value),list_constant_45))
	return put_compound_slot_value(3,frame,Qtrend_chart_plots,new_value);
    else {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(frame,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(frame,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = frame;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(frame,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(frame,Qtrend_chart_plots);
	  result_1 = SVREF(frame,FIX((SI_Long)17L)) = new_value;
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_1);
	  else if (M_CDR(Stack_of_slot_value_changes)) {
	      frame_and_slot_or_atom = Nil;
	      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	      ab_loop_it_ = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (ATOM(frame_and_slot_or_atom))
		  goto end_loop;
	      temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_1);
	      else {
		  temp_2 = M_CDR(frame_and_slot_or_atom);
		  temp_1 = CONSP(temp_2) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_1 ? (EQ(frame,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_1 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if ( !temp_1)
	      update_all_representations_of_slot(frame,slot_description,
		      Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(frame);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      else {
		  temp = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp_2 = M_CAR(Stack_of_slot_value_changes);
	      temp_1 = ATOM(temp_2);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	return VALUES_2(result_1,T);
    }
}

static Object Qtrend_chart_value_axes;  /* trend-chart-value-axes */

/* PUT-TREND-CHART-VALUE-AXES */
Object put_trend_chart_value_axes(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(175,150);
    if (memq_function(CAR(new_value),list_constant_45))
	return put_compound_slot_value(3,frame,Qtrend_chart_value_axes,
		new_value);
    else {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(frame,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(frame,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = frame;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(frame,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(frame,Qtrend_chart_value_axes);
	  result_1 = SVREF(frame,FIX((SI_Long)18L)) = new_value;
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_1);
	  else if (M_CDR(Stack_of_slot_value_changes)) {
	      frame_and_slot_or_atom = Nil;
	      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	      ab_loop_it_ = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (ATOM(frame_and_slot_or_atom))
		  goto end_loop;
	      temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_1);
	      else {
		  temp_2 = M_CDR(frame_and_slot_or_atom);
		  temp_1 = CONSP(temp_2) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_1 ? (EQ(frame,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_1 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if ( !temp_1)
	      update_all_representations_of_slot(frame,slot_description,
		      Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(frame);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      else {
		  temp = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp_2 = M_CAR(Stack_of_slot_value_changes);
	      temp_1 = ATOM(temp_2);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	return VALUES_2(result_1,T);
    }
}

static Object Qtrend_chart_time_axis;  /* trend-chart-time-axis */

/* PUT-TREND-CHART-TIME-AXIS */
Object put_trend_chart_time_axis(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(175,151);
    if (memq_function(CAR(new_value),list_constant_45))
	return put_compound_slot_value(3,frame,Qtrend_chart_time_axis,
		new_value);
    else {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(frame,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(frame,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = frame;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(frame,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(frame,Qtrend_chart_time_axis);
	  result_1 = SVREF(frame,FIX((SI_Long)19L)) = new_value;
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_1);
	  else if (M_CDR(Stack_of_slot_value_changes)) {
	      frame_and_slot_or_atom = Nil;
	      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	      ab_loop_it_ = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (ATOM(frame_and_slot_or_atom))
		  goto end_loop;
	      temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_1);
	      else {
		  temp_2 = M_CDR(frame_and_slot_or_atom);
		  temp_1 = CONSP(temp_2) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_1 ? (EQ(frame,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_1 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if ( !temp_1)
	      update_all_representations_of_slot(frame,slot_description,
		      Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(frame);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      else {
		  temp = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp_2 = M_CAR(Stack_of_slot_value_changes);
	      temp_1 = ATOM(temp_2);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	return VALUES_2(result_1,T);
    }
}

static Object Qtrend_chart_point_formats;  /* trend-chart-point-formats */

/* PUT-TREND-CHART-POINT-FORMATS */
Object put_trend_chart_point_formats(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(175,152);
    if (memq_function(CAR(new_value),list_constant_45))
	return put_compound_slot_value(3,frame,Qtrend_chart_point_formats,
		new_value);
    else {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(frame,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(frame,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = frame;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(frame,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(frame,Qtrend_chart_point_formats);
	  result_1 = SVREF(frame,FIX((SI_Long)20L)) = new_value;
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_1);
	  else if (M_CDR(Stack_of_slot_value_changes)) {
	      frame_and_slot_or_atom = Nil;
	      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	      ab_loop_it_ = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (ATOM(frame_and_slot_or_atom))
		  goto end_loop;
	      temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_1);
	      else {
		  temp_2 = M_CDR(frame_and_slot_or_atom);
		  temp_1 = CONSP(temp_2) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_1 ? (EQ(frame,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_1 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if ( !temp_1)
	      update_all_representations_of_slot(frame,slot_description,
		      Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(frame);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      else {
		  temp = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp_2 = M_CAR(Stack_of_slot_value_changes);
	      temp_1 = ATOM(temp_2);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	return VALUES_2(result_1,T);
    }
}

static Object Qtrend_chart_connector_formats;  /* trend-chart-connector-formats */

/* PUT-TREND-CHART-CONNECTOR-FORMATS */
Object put_trend_chart_connector_formats(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(175,153);
    if (memq_function(CAR(new_value),list_constant_45))
	return put_compound_slot_value(3,frame,
		Qtrend_chart_connector_formats,new_value);
    else {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(frame,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(frame,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = frame;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(frame,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(frame,Qtrend_chart_connector_formats);
	  result_1 = SVREF(frame,FIX((SI_Long)21L)) = new_value;
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_1);
	  else if (M_CDR(Stack_of_slot_value_changes)) {
	      frame_and_slot_or_atom = Nil;
	      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	      ab_loop_it_ = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (ATOM(frame_and_slot_or_atom))
		  goto end_loop;
	      temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_1);
	      else {
		  temp_2 = M_CDR(frame_and_slot_or_atom);
		  temp_1 = CONSP(temp_2) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_1 ? (EQ(frame,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_1 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if ( !temp_1)
	      update_all_representations_of_slot(frame,slot_description,
		      Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(frame);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      else {
		  temp = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp_2 = M_CAR(Stack_of_slot_value_changes);
	      temp_1 = ATOM(temp_2);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	return VALUES_2(result_1,T);
    }
}

/* PUT-TREND-CHART-FORMAT */
Object put_trend_chart_format(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(175,154);
    if (memq_function(CAR(new_value),list_constant_45))
	return put_compound_slot_value(3,frame,Qtrend_chart_format,new_value);
    else {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(frame,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(frame,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = frame;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(frame,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(frame,Qtrend_chart_format);
	  result_1 = SVREF(frame,FIX((SI_Long)22L)) = new_value;
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(frame,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_1);
	  else if (M_CDR(Stack_of_slot_value_changes)) {
	      frame_and_slot_or_atom = Nil;
	      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	      ab_loop_it_ = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (ATOM(frame_and_slot_or_atom))
		  goto end_loop;
	      temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_1);
	      else {
		  temp_2 = M_CDR(frame_and_slot_or_atom);
		  temp_1 = CONSP(temp_2) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_1 ? (EQ(frame,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_1 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if ( !temp_1)
	      update_all_representations_of_slot(frame,slot_description,
		      Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(frame);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      else {
		  temp = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp_2 = M_CAR(Stack_of_slot_value_changes);
	      temp_1 = ATOM(temp_2);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	return VALUES_2(result_1,T);
    }
}

/* RECLAIM-TREND-CHART-PANE-TREE-VALUE */
Object reclaim_trend_chart_pane_tree_value(pane_tree,trend_chart)
    Object pane_tree, trend_chart;
{
    x_note_fn_call(175,155);
    reclaim_pane_tree(pane_tree);
    return VALUES_1(Nil);
}

static Object Qcomponent_type;     /* component-type */

/* TREND-CHART-COMPONENT-NAME */
Object trend_chart_component_name(slot_component_group)
    Object slot_component_group;
{
    Object value_in_instance, name_or_names;

    x_note_fn_call(175,156);
    value_in_instance = getfq_function(CDDR(slot_component_group),
	    Qcomponent_type,Compound_type_slot_not_present);
    name_or_names = 
	    slot_component_group_name_or_names(slot_component_group,
	    EQ(value_in_instance,Compound_type_slot_not_present) ? 
	    get_default_slot_component_value_from_master_slot(slot_component_group,
	    Qcomponent_type) : value_in_instance);
    if (CONSP(name_or_names))
	return VALUES_1(CAR(name_or_names));
    else
	return VALUES_1(name_or_names);
}

Object Trend_chart_component_type_slot_name_map = UNBOUND;

static Object Qslot_component;     /* slot-component */

/* ADD-OR-DELETE-TREND-CHART-NOTE */
Object add_or_delete_trend_chart_note(trend_chart,
	    slot_component_group_or_name,note_type,add_p)
    Object trend_chart, slot_component_group_or_name, note_type, add_p;
{
    Object value_in_instance, component_type, indicator, temp, slot_name;
    Object current_computation_component_particulars;
    Declare_special(1);
    Object result;

    x_note_fn_call(175,157);
    if ( !TRUEP(slot_component_group_or_name) || 
	    SYMBOLP(slot_component_group_or_name)) {
	if (add_p)
	    return add_frame_note(2,note_type,trend_chart);
	else
	    return delete_frame_note_if_any(note_type,trend_chart);
    }
    else {
	value_in_instance = 
		getfq_function(CDDR(slot_component_group_or_name),
		Qcomponent_type,Compound_type_slot_not_present);
	component_type = EQ(value_in_instance,
		Compound_type_slot_not_present) ? 
		get_default_slot_component_value_from_master_slot(slot_component_group_or_name,
		Qcomponent_type) : value_in_instance;
	indicator = CAR(slot_component_group_or_name);
	temp = assoc_eql(component_type,
		Trend_chart_component_type_slot_name_map);
	slot_name = CDR(temp);
	current_computation_component_particulars = 
		slot_value_list_4(Qslot_component,slot_name,Nil,indicator);
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		0);
	  if (add_p)
	      add_frame_note(2,note_type,trend_chart);
	  else
	      delete_frame_note_if_any(note_type,trend_chart);
	  result = reclaim_slot_value_list_1(Current_computation_component_particulars);
	POP_SPECIAL();
	return result;
    }
}

/* DELETE-ALL-FRAME-NOTES-OF-TYPE-FROM-TREND-CHART */
Object delete_all_frame_notes_of_type_from_trend_chart(trend_chart,
	    type_of_note,components_p)
    Object trend_chart, type_of_note, components_p;
{
    x_note_fn_call(175,158);
    if (components_p)
	return delete_frame_note_from_all_component_particulars_of_frame(type_of_note,
		trend_chart);
    else
	return delete_frame_note_if_any(type_of_note,trend_chart);
}

/* DELETE-ALL-FRAME-NOTES-OF-TREND-CHART-COMPONENT-GROUP */
Object delete_all_frame_notes_of_trend_chart_component_group(trend_chart,
	    slot_component_group)
    Object trend_chart, slot_component_group;
{
    Object value_in_instance, component_type, indicator, temp, slot_name;
    Object current_computation_component_particulars;
    Declare_special(1);
    Object result;

    x_note_fn_call(175,159);
    value_in_instance = getfq_function(CDDR(slot_component_group),
	    Qcomponent_type,Compound_type_slot_not_present);
    component_type = EQ(value_in_instance,Compound_type_slot_not_present) ?
	     
	    get_default_slot_component_value_from_master_slot(slot_component_group,
	    Qcomponent_type) : value_in_instance;
    indicator = CAR(slot_component_group);
    temp = assoc_eql(component_type,Trend_chart_component_type_slot_name_map);
    slot_name = CDR(temp);
    current_computation_component_particulars = 
	    slot_value_list_4(Qslot_component,slot_name,Nil,indicator);
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	    0);
      delete_all_frame_notes_for_component_particular(Current_computation_component_particulars,
	      trend_chart);
      result = reclaim_slot_value_list_1(Current_computation_component_particulars);
    POP_SPECIAL();
    return result;
}

static Object array_constant_39;   /* # */

/* WRITE-DEFAULTING-TOTAL-TIMESPAN-NOTE */
Object write_defaulting_total_timespan_note(ignore_me,gensymed_symbol)
    Object ignore_me, gensymed_symbol;
{
    x_note_fn_call(175,160);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_39,
	    FIX((SI_Long)58L)));
    return VALUES_1(Nil);
}

static Object Qnames;              /* names */

static Object Qreserved_word_p;    /* reserved-word-p */

static Object string_constant_55;  /* "~a is a reserved symbol" */

/* GET-MULTIPLE-COMPOUND-SLOT-PARSE-RESULT-HEADER */
Object get_multiple_compound_slot_parse_result_header(sequence)
    Object sequence;
{
    Object res, gensymed_symbol, held_vector, struct_1, names_slot_value_qm;
    Object ab_loop_iter_flag_, elt_1, validated_elt, primary_name, temp;
    Object temp_1;
    SI_Long next_index, length_1, i;

    x_note_fn_call(175,161);
    res = Qnil;
    gensymed_symbol = sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    struct_1 = Nil;
    i = (SI_Long)1L;
    names_slot_value_qm = Nil;
    ab_loop_iter_flag_ = T;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    struct_1 = validated_elt;
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    names_slot_value_qm = estructure_slot(struct_1,Qnames,Nil);
    if (names_slot_value_qm) {
	primary_name = SYMBOLP(names_slot_value_qm) ? names_slot_value_qm :
		 evaluation_sequence_aref(names_slot_value_qm,
		FIX((SI_Long)0L));
	if ( !TRUEP(primary_name));
	else if (EQ(primary_name,Qdefault))
	    i = i - (SI_Long)1L;
	else if (getfq_function_no_default(INLINE_SYMBOL_PLIST(primary_name),
		Qreserved_word_p)) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(2,string_constant_55,primary_name);
	    return VALUES_2(temp,temp_1);
	}
	else
	    res = phrase_cons(phrase_list_2(FIX(i),primary_name),res);
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    if (res)
	return phrase_cons(Qcm,nreverse(res));
    else
	return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* GET-COMPONENT-GROUP-ID-FROM-STRUCTURE */
Object get_component_group_id_from_structure(struct_1)
    Object struct_1;
{
    Object name_or_names_qm, id, temp;

    x_note_fn_call(175,162);
    name_or_names_qm = estructure_slot(struct_1,Qnames,Nil);
    id = Nil;
    if (SYMBOLP(name_or_names_qm)) {
	id = name_or_names_qm;
	temp = id;
    }
    else if (CONSP(name_or_names_qm) && EQ(M_CDR(name_or_names_qm),Qsequence))
	temp = evaluation_sequence_aref(name_or_names_qm,FIX((SI_Long)0L));
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qchart_element_uid;  /* chart-element-uid */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qany;                /* any */

static Object Qnamed;              /* named */

static Object Qsingle;             /* single */

static Object Qnumbered;           /* numbered */

/* ADD-TRIPLES-FOR-COMPOUND-SLOT-STRUCTURE-PARSE-RESULT */
Object add_triples_for_compound_slot_structure_parse_result(frame,struct_1,
	    compound_type_descriptor,component_group_id,multiple_p)
    Object frame, struct_1, compound_type_descriptor, component_group_id;
    Object multiple_p;
{
    Object class_1, compound_type_name, parse_result, triples, gensymed_symbol;
    Object held_vector, name, attribute_value, value, slot_component_name;
    Object slot_component_descriptor, type_of_slot_component_qm, category;
    Object temp, category_evaluator_interface, function, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, temp_1;
    Object temp_2;
    SI_Long next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(175,163);
    class_1 = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
    compound_type_name = ISVREF(compound_type_descriptor,(SI_Long)1L);
    parse_result = Nil;
    triples = Qnil;
    gensymed_symbol = struct_1;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    name = Nil;
    attribute_value = Nil;
    value = Nil;
    slot_component_name = Nil;
    slot_component_descriptor = Nil;
    type_of_slot_component_qm = Nil;
    category = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    gensymed_symbol_1 = next_index + (SI_Long)1L;
    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,
	    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & (SI_Long)1023L);
    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
    next_index = next_index + (SI_Long)2L;
    temp = get_slot_component_name_for_alias_if_any(name,class_1,
	    compound_type_name);
    if (temp);
    else
	temp = name;
    slot_component_name = temp;
    slot_component_descriptor = 
	    compound_type_slot_if_any(compound_type_descriptor,
	    slot_component_name);
    type_of_slot_component_qm = assq_function(Qtype,
	    ISVREF(slot_component_descriptor,(SI_Long)3L));
    category = type_of_slot_component_qm ? 
	    SECOND(type_of_slot_component_qm) : Qnil;
    if (type_of_slot_component_qm &&  !(EQ(name,Qnames) || EQ(name,
	    Qchart_element_uid))) {
	if (memq_function(Qtext,CDDR(type_of_slot_component_qm)))
	    parse_result = parse_text_string(2,value,category);
	else {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(category),
		    Qcategory_evaluator_interface);
	    if ( !(category_evaluator_interface && 
		    ISVREF(category_evaluator_interface,(SI_Long)3L)))
		parse_result = Bad_phrase;
	    else {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(category),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)3L) : 
			Qnil;
		if (function) {
		    gensymed_symbol = function;
		    gensymed_symbol_2 = value;
		    gensymed_symbol_3 = frame;
		    gensymed_symbol_4 = Nil;
		    gensymed_symbol_5 = Nil;
		    parse_result = inline_funcall_4(gensymed_symbol,
			    gensymed_symbol_2,gensymed_symbol_3,
			    gensymed_symbol_4,gensymed_symbol_5);
		}
		else
		    parse_result = Nil;
	    }
	}
	temp_1 = slot_component_name;
	temp = parse_result;
	if (EQ(component_group_id,Qdefault))
	    temp_2 = phrase_cons(Qany,Nil);
	else if (SYMBOLP(component_group_id))
	    temp_2 = multiple_p ? phrase_list_2(Qnamed,component_group_id) 
		    : phrase_cons(Qsingle,Nil);
	else
	    temp_2 = phrase_list_2(Qnumbered,component_group_id);
	triples = phrase_cons(phrase_list_3(temp_1,temp,temp_2),triples);
    }
    goto next_loop;
  end_loop:
    return nreverse(triples);
    return VALUES_1(Qnil);
}

/* MAKE-EVALUATION-SEQUENCE-FROM-MULTIPLE-COMPOUND-SLOT */
Object make_evaluation_sequence_from_multiple_compound_slot(frame,
	    slot_value,compound_type_descriptor,expand_inherited_slots_p)
    Object frame, slot_value, compound_type_descriptor;
    Object expand_inherited_slots_p;
{
    Object res, slot_component_group, ab_loop_list_, temp;

    x_note_fn_call(175,164);
    res = Qnil;
    slot_component_group = Nil;
    ab_loop_list_ = CDR(slot_value);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_component_group = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = make_evaluation_structure_from_slot_component(frame,
	    slot_component_group,compound_type_descriptor,
	    expand_inherited_slots_p,T);
    res = eval_cons_1(temp,res);
    goto next_loop;
  end_loop:
    return allocate_evaluation_sequence(nreverse(res));
    return VALUES_1(Qnil);
}

static Object Qslot_component_alias;  /* slot-component-alias */

static Object Qnot_editable_in_default;  /* not-editable-in-default */

static Object Qname_or_names;      /* name-or-names */

/* MAKE-EVALUATION-STRUCTURE-FROM-SLOT-COMPONENT */
Object make_evaluation_structure_from_slot_component(frame,
	    slot_component_group,compound_type_descriptor,
	    expand_inherited_slots_p,multiple_p)
    Object frame, slot_component_group, compound_type_descriptor;
    Object expand_inherited_slots_p, multiple_p;
{
    Object indicator, slot_component_name_for_names, reversed_plist;
    Object slot_component_descriptor, ab_loop_list_, slot_component_name;
    Object slot_component_features, best_slot_component_name;
    Object type_of_slot_component, category, slot_component_indicator_qm, temp;
    Object non_default_value_qm, add_attribute_to_struct_p;
    Object slot_component_value, evaluation_value, value_in_instance;
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(175,165);
    indicator = CAR(slot_component_group);
    slot_component_name_for_names = ISVREF(compound_type_descriptor,
	    (SI_Long)4L);
    reversed_plist = multiple_p ? eval_list_2(indicator,
	    Qchart_element_uid) : Qnil;
    slot_component_descriptor = Nil;
    ab_loop_list_ = ISVREF(compound_type_descriptor,(SI_Long)3L);
    slot_component_name = Nil;
    slot_component_features = Nil;
    best_slot_component_name = Nil;
    type_of_slot_component = Nil;
    category = Nil;
    slot_component_indicator_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_component_descriptor = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_component_name = ISVREF(slot_component_descriptor,(SI_Long)1L);
    slot_component_features = ISVREF(slot_component_descriptor,(SI_Long)3L);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(slot_component_name),
	    Qslot_component_alias);
    if (temp);
    else
	temp = slot_component_name;
    best_slot_component_name = temp;
    type_of_slot_component = assq_function(Qtype,slot_component_features);
    category = SECOND(type_of_slot_component);
    slot_component_indicator_qm = CAR(slot_component_group);
    if (type_of_slot_component &&  !EQ(slot_component_name,
	    Qcomponent_type) && category && (EQ(slot_component_name,
	    slot_component_name_for_names) ||  
	    !TRUEP(assq_function(Qnot_editable_in_default,
	    slot_component_features)) ||  !EQ(slot_component_indicator_qm,
	    Qdefault))) {
	non_default_value_qm = getf(CDDR(slot_component_group),
		slot_component_name,Compound_type_slot_not_present);
	add_attribute_to_struct_p = T;
	slot_component_value = Nil;
	evaluation_value = Nil;
	if (EQ(non_default_value_qm,Compound_type_slot_not_present)) {
	    if (EQ(indicator,Qdefault) || expand_inherited_slots_p) {
		value_in_instance = 
			getfq_function(CDDR(slot_component_group),
			slot_component_name,Compound_type_slot_not_present);
		slot_component_value = EQ(value_in_instance,
			Compound_type_slot_not_present) ? 
			get_default_slot_component_value_from_master_slot(slot_component_group,
			slot_component_name) : value_in_instance;
	    }
	    else
		add_attribute_to_struct_p = Nil;
	}
	else
	    slot_component_value = non_default_value_qm;
	if (add_attribute_to_struct_p) {
	    if (EQ(category,Qname_or_names)) {
		if (slot_component_value)
		    evaluation_value = CONSP(slot_component_value) ? 
			    allocate_evaluation_sequence(copy_list_using_eval_conses_1(slot_component_value)) 
			    : slot_component_value;
		else
		    add_attribute_to_struct_p = Nil;
	    }
	    else if (memq_function(Qtext,CDDR(type_of_slot_component)))
		evaluation_value = 
			text_slot_value_to_evaluation_text(frame,
			slot_component_value,type_of_slot_component);
	    else {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(category),
			Qcategory_evaluator_interface);
		if ( !(category_evaluator_interface && 
			ISVREF(category_evaluator_interface,(SI_Long)2L)))
		    evaluation_value = Evaluation_false_value;
		else {
		    category_evaluator_interface = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(category),
			    Qcategory_evaluator_interface);
		    function = category_evaluator_interface ? 
			    ISVREF(category_evaluator_interface,
			    (SI_Long)2L) : Qnil;
		    if (function) {
			gensymed_symbol = function;
			gensymed_symbol_1 = slot_component_value;
			gensymed_symbol_2 = Nil;
			gensymed_symbol_3 = Nil;
			evaluation_value = 
				inline_funcall_3(gensymed_symbol,
				gensymed_symbol_1,gensymed_symbol_2,
				gensymed_symbol_3);
		    }
		    else
			evaluation_value = Nil;
		    if ( !TRUEP(evaluation_value))
			add_attribute_to_struct_p = Nil;
		}
	    }
	    if (add_attribute_to_struct_p) {
		reversed_plist = eval_cons_1(best_slot_component_name,
			reversed_plist);
		reversed_plist = eval_cons_1(evaluation_value,reversed_plist);
	    }
	}
    }
    goto next_loop;
  end_loop:
    return allocate_evaluation_structure(nreverse(reversed_plist));
    return VALUES_1(Qnil);
}

static Object Qplot_tracing_and_breakpoints;  /* plot-tracing-and-breakpoints */

/* SET-TRACING-AND-BREAKPOINTS-FOR-TREND-CHART */
Object set_tracing_and_breakpoints_for_trend_chart(block,new_value)
    Object block, new_value;
{
    Object slot_component_group, temp, ab_loop_list_, indicator;

    x_note_fn_call(175,166);
    slot_component_group = Nil;
    temp = ISVREF(block,(SI_Long)17L);
    ab_loop_list_ = CDDR(temp);
    indicator = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_component_group = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    indicator = CAR(slot_component_group);
    if ( !EQ(get_slot_component_value_if_any(block,Qtrend_chart_plots,Nil,
	    Qplot_tracing_and_breakpoints,indicator),new_value))
	change_slot_value(6,block,Qtrend_chart_plots,new_value,Nil,
		Qplot_tracing_and_breakpoints,indicator);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

void graph_def_INIT()
{
    Object extant_color_or_metacolor_evaluation_setter_1;
    Object extant_color_or_metacolor_evaluation_getter_1;
    Object n_2d_shading_target_spec_evaluation_setter_1;
    Object n_2d_shading_target_spec_evaluation_getter_1;
    Object n_2d_plot_marker_shape_evaluation_setter_1;
    Object n_2d_plot_marker_shape_evaluation_getter_1;
    Object n_2d_tickmark_label_color_evaluation_setter_1;
    Object n_2d_tickmark_label_color_evaluation_getter_1;
    Object n_2d_time_span_spec_evaluation_setter_1;
    Object n_2d_time_span_spec_evaluation_getter_1;
    Object n_2d_total_time_span_spec_evaluation_setter_1;
    Object n_2d_total_time_span_spec_evaluation_getter_1;
    Object n_2d_end_time_spec_evaluation_setter_1;
    Object n_2d_end_time_spec_evaluation_getter_1;
    Object n_2d_time_axis_tickmark_frequency_spec_evaluation_setter_1;
    Object n_2d_time_axis_tickmark_frequency_spec_evaluation_getter_1;
    Object n_2d_plot_marker_frequency_evaluation_setter_1;
    Object n_2d_plot_marker_frequency_evaluation_getter_1;
    Object n_2d_value_axis_tickmark_frequency_spec_evaluation_setter_1;
    Object n_2d_value_axis_tickmark_frequency_spec_evaluation_getter_1;
    Object n_2d_value_axis_bounds_spec_evaluation_setter_1;
    Object n_2d_value_axis_bounds_spec_evaluation_getter_1;
    Object trend_chart_legend_color_spec_evaluation_setter_1;
    Object trend_chart_legend_color_spec_evaluation_getter_1;
    Object value_axis_position_evaluation_setter_1;
    Object value_axis_position_evaluation_getter_1;
    Object trend_chart_legend_position_evaluation_setter_1;
    Object trend_chart_legend_position_evaluation_getter_1;
    Object n_2d_line_style_evaluation_setter_1;
    Object n_2d_line_style_evaluation_getter_1;
    Object time_axis_label_alignment_evaluation_setter_1;
    Object time_axis_label_alignment_evaluation_getter_1;
    Object time_axis_label_format_spec_evaluation_setter_1;
    Object time_axis_label_format_spec_evaluation_getter_1;
    Object n_2d_range_mode_evaluation_setter_1;
    Object n_2d_range_mode_evaluation_getter_1;
    Object extra_value_grid_lines_evaluation_setter_1;
    Object extra_value_grid_lines_evaluation_getter_1;
    Object significant_digit_spec_evaluation_setter_1;
    Object significant_digit_spec_evaluation_getter_1;
    Object range_slack_spec_evaluation_setter_1;
    Object range_slack_spec_evaluation_getter_1;
    Object grid_line_ratio_evaluation_setter_1;
    Object grid_line_ratio_evaluation_getter_1;
    Object trend_chart_scroll_interval_evaluation_setter_1;
    Object trend_chart_scroll_interval_evaluation_getter_1;
    Object slot_component_pretty_name_new_value, temp, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6, temp_7, temp_8, temp_9, temp_10, temp_11;
    Object temp_12, temp_13, temp_14, temp_15, temp_16, temp_17, temp_18;
    Object temp_19, temp_20, temp_21, temp_22, temp_23;
    Object reclaim_structure_for_display_pane_1;
    Object reclaim_structure_for_axis_pane_1;
    Object reclaim_structure_for_trend_chart_pane_1;
    Object reclaim_structure_for_legend_pane_1;
    Object reclaim_structure_for_relative_time_pane_1;
    Object reclaim_structure_for_grid_pane_1;
    Object write_defaulting_total_timespan_note_1;
    Object AB_package, Qframe_note_writer_1, Qdefaulting_total_timespan;
    Object list_constant_46, list_constant_249, list_constant_248;
    Object list_constant_247, list_constant_246, list_constant_245;
    Object list_constant_244, list_constant_243, Qslot_value_reclaimer;
    Object Qreclaim_trend_chart_pane_tree_value, Qtrend_chart_pane_tree;
    Object Qslot_putter, Qput_trend_chart_format;
    Object Qput_trend_chart_connector_formats, Qput_trend_chart_point_formats;
    Object Qput_trend_chart_time_axis, Qput_trend_chart_value_axes;
    Object Qput_trend_chart_plots, Qmultiple;
    Object Qwrite_trend_chart_format_grammar_spec_from_slot;
    Object Qtrend_chart_format_grammar_spec;
    Object Qwrite_trend_chart_connector_formats_grammar_spec_from_slot;
    Object Qtrend_chart_connector_formats_grammar_spec;
    Object Qwrite_trend_chart_point_formats_grammar_spec_from_slot;
    Object Qtrend_chart_point_formats_grammar_spec;
    Object Qwrite_trend_chart_time_axis_grammar_spec_from_slot;
    Object Qtrend_chart_time_axis_grammar_spec;
    Object Qwrite_trend_chart_value_axes_grammar_spec_from_slot;
    Object Qtrend_chart_value_axes_grammar_spec;
    Object Qwrite_trend_chart_plots_grammar_spec_from_slot;
    Object Qtrend_chart_plots_grammar_spec;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qcompile_trend_chart_format_grammar_spec_for_slot;
    Object Qcompile_trend_chart_connector_formats_grammar_spec_for_slot;
    Object Qcompile_trend_chart_point_formats_grammar_spec_for_slot;
    Object Qcompile_trend_chart_time_axis_grammar_spec_for_slot;
    Object Qcompile_trend_chart_value_axes_grammar_spec_for_slot;
    Object Qcompile_trend_chart_plots_grammar_spec_for_slot;
    Object string_constant_228, string_constant_227, string_constant_226;
    Object string_constant_225, string_constant_224, string_constant_223;
    Object string_constant_222, string_constant_221, string_constant_220;
    Object string_constant_219, Qsimplify_associative_operation;
    Object string_constant_218, string_constant_217, string_constant_216;
    Object string_constant_215, string_constant_214, string_constant_213;
    Object string_constant_212, string_constant_211, string_constant_210;
    Object string_constant_209, string_constant_208, string_constant_207;
    Object string_constant_206, string_constant_205, string_constant_204;
    Object string_constant_203, string_constant_202, string_constant_201;
    Object string_constant_200, string_constant_199, string_constant_198;
    Object string_constant_197, string_constant_196, string_constant_195;
    Object string_constant_194, string_constant_193, string_constant_192;
    Object string_constant_191, string_constant_190, string_constant_189;
    Object string_constant_188, string_constant_187, string_constant_186;
    Object string_constant_185, string_constant_184, string_constant_183;
    Object string_constant_182, string_constant_181, string_constant_180;
    Object string_constant_179, string_constant_178, string_constant_177;
    Object string_constant_176, string_constant_175, string_constant_174;
    Object string_constant_173, string_constant_172, string_constant_171;
    Object string_constant_170, string_constant_169, string_constant_168;
    Object string_constant_167, string_constant_166, string_constant_165;
    Object string_constant_164, string_constant_163, string_constant_162;
    Object string_constant_161, string_constant_160, string_constant_159;
    Object string_constant_158, string_constant_157, string_constant_156;
    Object string_constant_155, string_constant_154, string_constant_153;
    Object string_constant_152, string_constant_151, string_constant_150;
    Object string_constant_149, Qcompound_slots_for_class, list_constant_242;
    Object Qtrend_chart, list_constant_241, Qcompound_slot_descriptor;
    Object string_constant_148, string_constant_147, string_constant_146;
    Object string_constant_145, list_constant_240, string_constant_144;
    Object string_constant_143, string_constant_142, string_constant_141;
    Object string_constant_140, string_constant_139, string_constant_138;
    Object string_constant_137, string_constant_136, string_constant_135;
    Object string_constant_134, string_constant_133, string_constant_132;
    Object string_constant_131, Qitem, string_constant_130;
    Object Qcompound_slot_value_writer_info, Qconnector_formats;
    Object Qpoint_formats, Qvalue_axes, Qtrend_chart_formats, Qtime_axes;
    Object Qplots, Qplotting_conditions, Qtrend_chart_plotting_conditions;
    Object Qtitle, Qtrend_chart_label_to_display, Qgrid_pane;
    Object Qreclaim_structure, Qoutstanding_grid_pane_count;
    Object Qgrid_pane_structure_memory_usage, Qutilities2, string_constant_129;
    Object Qtype_description_of_type, string_constant_128;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qrelative_time_pane;
    Object Qoutstanding_relative_time_pane_count;
    Object Qrelative_time_pane_structure_memory_usage, string_constant_127;
    Object string_constant_126, Qlegend_pane, Qoutstanding_legend_pane_count;
    Object Qlegend_pane_structure_memory_usage, string_constant_125;
    Object string_constant_124, Qtrend_chart_pane;
    Object Qoutstanding_trend_chart_pane_count;
    Object Qtrend_chart_pane_structure_memory_usage, string_constant_123;
    Object string_constant_122, Qaxis_pane, Qoutstanding_axis_pane_count;
    Object Qaxis_pane_structure_memory_usage, string_constant_121;
    Object string_constant_120, Qdisplay_pane, Qoutstanding_display_pane_count;
    Object Qdisplay_pane_structure_memory_usage, string_constant_119;
    Object string_constant_118, Qreclaim_2d_incomplete_painting_actions_value;
    Object Q2d_incomplete_painting_actions, string_constant_117;
    Object string_constant_116, list_constant_239, Q2d_image_plane_state;
    Object string_constant_115, string_constant_114, string_constant_113;
    Object string_constant_112, string_constant_111, string_constant_110;
    Object string_constant_109, Qdependent_frame, Qslot_component_pretty_name;
    Object Qconnector_format_name_or_number, Qplot_connector_format;
    Object Qpoint_format_name_or_number, Qplot_point_format;
    Object Qvalue_axis_name_or_number, Qplot_axis, Qexpression;
    Object Qplot_expression, Qtracing_and_breakpoints, Quse_local_history_qm;
    Object Qplot_use_local_history_qm, Quse_simulator_qm;
    Object Qplot_use_simulator_qm, Qmay_request_event_updates_qm;
    Object Qplot_request_event_updates_qm, Qmay_request_data_seeking_qm;
    Object Qplot_request_data_seeking_qm, Qupdate_priority;
    Object Qplot_update_priority, Qwait_interval, Qplot_wait_interval;
    Object Qupdate_interval, Qplot_update_interval, Qcompound_type_descriptor;
    Object Qplot_names, list_constant_190, Qplot_index;
    Object Qplot_v_or_p_cell_index, Qplot_number_cell_index;
    Object Qplot_variable_or_parameter_qm;
    Object Qplot_data_tc_representation_earliest_index_qm;
    Object Qplot_data_tc_representation_end_index_qm;
    Object Qplot_data_last_tc_representation_send_time_qm, Qplot_history;
    Object list_constant_238, list_constant_151, Qinclude_in_legend_qm;
    Object list_constant_237, list_constant_236, list_constant_150;
    Object list_constant_235, list_constant_234, list_constant_233;
    Object list_constant_232, string_constant_108, string_constant_107;
    Object list_constant_231, list_constant_230, list_constant_229;
    Object list_constant_125, list_constant_161, list_constant_228;
    Object list_constant_227, Qpriority, list_constant_226;
    Object Qplot_update_interval_spec, list_constant_223, list_constant_225;
    Object Qreference, Qsubtype, list_constant_224, list_constant_222;
    Object list_constant_221, Qcomponent_reference, list_constant_160;
    Object list_constant_220, list_constant_118, Qconnector_format_names;
    Object list_constant_219, Qconnector_shading_target, list_constant_218;
    Object Qconnector_line_width, list_constant_217, Qconnector_line_style;
    Object list_constant_156, Qconnector_line_color, Qconnector_visible_qm;
    Object string_constant_106, string_constant_105, list_constant_216;
    Object list_constant_215, list_constant_214, list_constant_213;
    Object list_constant_76, list_constant_212, list_constant_211;
    Object Q2d_line_style, list_constant_210, Qconnectors_visible_qm;
    Object Qconnector_interpolation, Qpoint_format_names, list_constant_209;
    Object list_constant_208, Qpoint_frequency, list_constant_207;
    Object list_constant_206, Qpoint_style, Qpoint_color, Qpoint_visible_qm;
    Object string_constant_104, string_constant_103, list_constant_205;
    Object list_constant_204, list_constant_203, list_constant_202;
    Object list_constant_201, list_constant_200, Qtriangle, list_constant_199;
    Object Qmarker_frequency, Qmarker_style, Qmarker_color;
    Object Qmarkers_visible_qm, Qtrend_chart_format_names, list_constant_198;
    Object Qtrend_chart_label_position, Qtrend_chart_label_color;
    Object Qtrend_chart_label_visible_qm, Qtrend_chart_legend_position;
    Object list_constant_197, Qtrend_chart_legend_color;
    Object Qtrend_chart_legend_visible_qm, Qsmoke;
    Object Qdata_window_background_color, Qdata_window_border_color;
    Object Qdata_window_border_visible_qm, Qouter_background_color;
    Object Qouter_border_color, Qouter_border_visible_qm, list_constant_196;
    Object list_constant_195, list_constant_194, list_constant_193;
    Object list_constant_192, list_constant_191, Qtitle_color, Qtitle_position;
    Object Qtitle_visible_qm, Qlegend_position, Qlegend_color;
    Object Qlegend_visible_qm, Qvalue_axis_names;
    Object Qvalue_axis_last_sent_low_value, Qvalue_axis_last_sent_high_value;
    Object Qvalue_axis_low_value, Qvalue_axis_high_value;
    Object Qvalue_axis_upper_bound_qm, Qvalue_axis_lower_bound_qm;
    Object Qcolor_for_value_axis_base_line, Qvalue_axis_base_line_visible_qm;
    Object list_constant_189, Qextra_value_grid_lines, list_constant_157;
    Object Qratio_of_grid_lines_to_value_axis_tickmarks, Qgray;
    Object Qcolor_for_value_grid_lines, Qvalue_grid_lines_visible_qm;
    Object list_constant_188, Qvalue_axis_label_significant_digits;
    Object Qshow_value_labels_as_percent_qm, list_constant_187;
    Object Qvalue_axis_tickmark_frequency, list_constant_186;
    Object list_constant_185, Qcolor_for_value_axis_tickmarks;
    Object Qvalue_axis_labels_visible_qm, list_constant_184;
    Object Qvalue_axis_range_slack, list_constant_183, Qvalue_axis_bounds;
    Object list_constant_182, Qvalue_axis_range_mode, list_constant_181;
    Object Qvalue_axis_position, list_constant_180, Qvalue_axis_visible_qm;
    Object string_constant_102, string_constant_101, list_constant_179;
    Object list_constant_158, list_constant_178, Qinternal, list_constant_177;
    Object list_constant_176, list_constant_175, list_constant_174;
    Object Qsignificant_digit_spec, list_constant_173, list_constant_172;
    Object list_constant_171, list_constant_170, list_constant_169;
    Object list_constant_168, Qrange_slack_spec, list_constant_167;
    Object list_constant_166, list_constant_165, list_constant_164;
    Object Q2d_range_mode, list_constant_163, list_constant_162;
    Object list_constant_132, list_constant_117, list_constant_159;
    Object list_constant_121, list_constant_120, list_constant_122;
    Object Qrange_slack_percentage, Qextra_grid_lines, Qgrid_lines_visible_qm;
    Object Qgrid_line_color, Qshow_labels_as_percent_qm, Qbaseline_visible_qm;
    Object Qlabels_visible_qm, Qbaseline_color, Qrange_mode, Qrange_bounds;
    Object Qgrid_lines_per_label, Qlabel_frequency, Qlabel_color;
    Object Qsignificant_digits_for_labels, Qtime_axis_names;
    Object Qcolor_for_time_axis_base_line, Qtime_axis_base_line_visible_qm;
    Object Qratio_of_grid_lines_to_time_axis_tickmarks;
    Object Qcolor_for_time_grid_lines, Qtime_grid_lines_visible_qm;
    Object Qcolor_for_time_tickmarks, list_constant_155;
    Object Qtime_axis_label_format, list_constant_154;
    Object Qtime_axis_label_alignment, list_constant_153;
    Object Qtime_axis_tickmark_frequency;
    Object Qtime_axis_relative_labels_visible_qm;
    Object Qtime_axis_absolute_labels_visible_qm, list_constant_152;
    Object Qtime_axis_scroll_interval, Qtime_axis_jump_scroll_qm;
    Object Qtime_axis_update_interval, list_constant_149, Qend_time;
    Object list_constant_148, Qtotal_time_span, list_constant_147;
    Object list_constant_146, Qdata_window_time_span, list_constant_145;
    Object list_constant_144, list_constant_143, Qgrid_line_ratio;
    Object list_constant_142, list_constant_141, Qextant_color_or_metacolor;
    Object list_constant_140, list_constant_139, Qtime_axis_label_format_spec;
    Object list_constant_138, list_constant_137, list_constant_136;
    Object list_constant_135, list_constant_134, list_constant_133;
    Object Qtrend_chart_scroll_interval, Qyes_or_no, list_constant_131;
    Object list_constant_130, list_constant_129, list_constant_128;
    Object list_constant_127, list_constant_126, list_constant_124;
    Object list_constant_123, list_constant_119, Qnot_user_editable;
    Object Qdo_not_identify_in_attribute_tables, Qcomponent_group_header;
    Object Qjump_scroll_interval, Qjump_scroll_qm, Qdisplay_update_interval;
    Object Qrelative_labels_visible_qm, Qabsolute_labels_visible_qm;
    Object Qlabel_alignment, Qtime_format;
    Object Qwrite_trend_chart_scroll_interval_from_slot, list_constant_116;
    Object list_constant_115, list_constant_114, list_constant_113;
    Object list_constant_112, list_constant_62;
    Object Qtype_specification_simple_expansion;
    Object Qcompile_trend_chart_scroll_interval_for_slot;
    Object Qwrite_plot_update_interval_spec_from_slot;
    Object Qcompile_plot_update_interval_spec_for_slot, string_constant_100;
    Object string_constant_99, Qwrite_grid_line_ratio_from_slot;
    Object Qcompile_grid_line_ratio_for_slot;
    Object Qwrite_range_slack_spec_from_slot;
    Object Qcompile_range_slack_spec_for_slot;
    Object Qwrite_significant_digit_spec_from_slot;
    Object Qcompile_significant_digit_spec_for_slot;
    Object Qwrite_extra_value_grid_lines_from_slot, list_constant_111, Qab_or;
    Object list_constant_110, list_constant_109, list_constant_108;
    Object list_constant_107, list_constant_106, list_constant_47;
    Object list_constant_81, list_constant_105;
    Object Qcompile_extra_value_grid_lines_for_slot;
    Object Qwrite_2d_range_mode_from_slot, list_constant_104;
    Object string_constant_98, string_constant_97;
    Object Qenumeration_grammar_category_members;
    Object Qwrite_time_axis_label_format_spec_from_slot, list_constant_103;
    Object string_constant_96, string_constant_95, string_constant_94;
    Object string_constant_93, string_constant_92;
    Object Qwrite_time_axis_label_alignment_from_slot, list_constant_102;
    Object string_constant_91, Qwrite_2d_line_style_from_slot;
    Object list_constant_101, string_constant_90, string_constant_89;
    Object Qwrite_trend_chart_legend_position_from_slot, list_constant_100;
    Object string_constant_88, Qwrite_value_axis_position_from_slot;
    Object list_constant_99, string_constant_87, list_constant_98;
    Object list_constant_97, list_constant_96, list_constant_95;
    Object list_constant_54, list_constant_94, list_constant_52;
    Object Qwrite_trend_chart_legend_color_spec_from_slot;
    Object Qcompile_trend_chart_legend_color_spec_for_slot;
    Object Qframe_like_category_cases, string_constant_86, string_constant_85;
    Object list_constant_93, list_constant_92, list_constant_91;
    Object list_constant_90, list_constant_89, list_constant_88;
    Object Qwrite_2d_value_axis_bounds_spec_from_slot;
    Object Qcompile_2d_value_axis_bounds_spec_for_slot, string_constant_84;
    Object string_constant_83, list_constant_87, list_constant_86;
    Object list_constant_85, list_constant_84, list_constant_83;
    Object list_constant_82, list_constant_80;
    Object Qwrite_2d_value_axis_tickmark_frequency_spec_from_slot;
    Object Qcompile_2d_value_axis_tickmark_frequency_spec_for_slot;
    Object string_constant_82, string_constant_81, string_constant_80;
    Object list_constant_79, list_constant_78, list_constant_77;
    Object Qwrite_2d_plot_marker_frequency_from_slot;
    Object Qcompile_2d_plot_marker_frequency_for_slot, string_constant_79;
    Object string_constant_78, list_constant_75, list_constant_74;
    Object list_constant_65, list_constant_73, list_constant_72;
    Object Qwrite_2d_time_axis_tickmark_frequency_spec_from_slot;
    Object Qcompile_2d_time_axis_tickmark_frequency_spec_for_slot;
    Object string_constant_77, string_constant_76;
    Object Qwrite_2d_scrolling_alignment_spec_from_slot;
    Object Q2d_scrolling_alignment_spec;
    Object Qcompile_2d_scrolling_alignment_spec_for_slot, string_constant_75;
    Object string_constant_74, list_constant_71, list_constant_70;
    Object list_constant_69, list_constant_68;
    Object Qwrite_2d_end_time_spec_from_slot;
    Object Qcompile_2d_end_time_spec_for_slot, string_constant_73;
    Object string_constant_72, list_constant_67, list_constant_66;
    Object list_constant_64, list_constant_59, list_constant_63;
    Object Qwrite_2d_total_time_span_spec_from_slot;
    Object Qcompile_2d_total_time_span_spec_for_slot, string_constant_71;
    Object string_constant_70, list_constant_61, list_constant_60;
    Object list_constant_58, list_constant_57;
    Object Qwrite_2d_time_span_spec_from_slot;
    Object Qcompile_2d_time_span_spec_for_slot, string_constant_69;
    Object string_constant_68, list_constant_56, list_constant_55;
    Object list_constant_53, Qwrite_2d_tickmark_label_color_from_slot;
    Object Qcompile_2d_tickmark_label_color_for_slot, string_constant_67;
    Object string_constant_66, Qwrite_2d_location_spec_from_slot;
    Object Q2d_location_spec, Qcompile_2d_location_spec_for_slot;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object list_constant_51, list_constant_50, list_constant_49;
    Object list_constant_48, Qwrite_2d_plot_marker_shape_from_slot;
    Object Qcompile_2d_plot_marker_shape_for_slot, string_constant_62;
    Object string_constant_61, string_constant_60, Qno_item;
    Object Qwrite_2d_shading_target_spec_from_slot;
    Object Qcompile_2d_shading_target_spec_for_slot, string_constant_59;
    Object string_constant_58, Qwrite_extant_color_or_metacolor_from_slot;
    Object Qcompile_extant_color_or_metacolor_for_slot, Qextra_value_grid_line;
    Object string_constant_57, string_constant_56;

    x_note_fn_call(175,167);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    string_constant_56 = 
	    STATIC_STRING("1s1m83-Coy83Sy1m83i9y83Sy1m83-J1y1n1m9k9l1m9k83-xqy1m9k83-ZEy1m83-9wy83Sy1m83-9*y83=xy1m832Yy83*uy1n83-Tey1o1m9k83=Gy83-Hy1m9k83");
    string_constant_57 = 
	    STATIC_STRING("*Xy83*xy2lmo1n83-Tey1m1m9k83=Gy83-Hy2lm83Py");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnot);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_56,
	    string_constant_57)));
    Qextra_value_grid_lines = STATIC_SYMBOL("EXTRA-VALUE-GRID-LINES",
	    AB_package);
    Qextra_value_grid_line = STATIC_SYMBOL("EXTRA-VALUE-GRID-LINE",AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    add_grammar_rules_for_list(5,Qextra_value_grid_lines,
	    Qextra_value_grid_line,Qcm,Nil,Qnone);
    string_constant = STATIC_STRING("Unknown color requested: ~NV");
    Qextant_color_or_metacolor = STATIC_SYMBOL("EXTANT-COLOR-OR-METACOLOR",
	    AB_package);
    Qcompile_extant_color_or_metacolor_for_slot = 
	    STATIC_SYMBOL("COMPILE-EXTANT-COLOR-OR-METACOLOR-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_extant_color_or_metacolor_for_slot,
	    STATIC_FUNCTION(compile_extant_color_or_metacolor_for_slot,NIL,
	    TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qextant_color_or_metacolor,
	    SYMBOL_FUNCTION(Qcompile_extant_color_or_metacolor_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qextant_color_or_metacolor,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qextant_color_or_metacolor),
	    Qtype_specification_simple_expansion,Qsymbol);
    define_type_specification_explicit_complex_type(Qextant_color_or_metacolor,
	    Qsymbol);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qextant_color_or_metacolor);
    extant_color_or_metacolor_evaluation_setter_1 = 
	    STATIC_FUNCTION(extant_color_or_metacolor_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qextant_color_or_metacolor,
	    extant_color_or_metacolor_evaluation_setter_1);
    extant_color_or_metacolor_evaluation_getter_1 = 
	    STATIC_FUNCTION(extant_color_or_metacolor_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qextant_color_or_metacolor,
	    extant_color_or_metacolor_evaluation_getter_1);
    Qwrite_extant_color_or_metacolor_from_slot = 
	    STATIC_SYMBOL("WRITE-EXTANT-COLOR-OR-METACOLOR-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_extant_color_or_metacolor_from_slot,
	    STATIC_FUNCTION(write_extant_color_or_metacolor_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qextant_color_or_metacolor,
	    SYMBOL_FUNCTION(Qwrite_extant_color_or_metacolor_from_slot),
	    Qslot_value_writer);
    string_constant_58 = 
	    STATIC_STRING("1n1n83p+y1m9k83gy1o8382y6B83bOy83gy1n83p+y1m9k83hy1o8382y6A83bOy83hy1n83p+y1m9k83Zy1m83Zy6A");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_58));
    Q2d_shading_target_spec = STATIC_SYMBOL("2D-SHADING-TARGET-SPEC",
	    AB_package);
    string_constant_59 = 
	    STATIC_STRING("1n1o8382yl83bOy83gy1o8382yk83bOy83hy1m83Zyk");
    Qframe_like_category_cases = STATIC_SYMBOL("FRAME-LIKE-CATEGORY-CASES",
	    AB_package);
    mutate_global_property(Q2d_shading_target_spec,
	    regenerate_optimized_constant(string_constant_59),
	    Qframe_like_category_cases);
    string_constant_1 = STATIC_STRING("~a");
    Qcompile_2d_shading_target_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-SHADING-TARGET-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_shading_target_spec_for_slot,
	    STATIC_FUNCTION(compile_2d_shading_target_spec_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Q2d_shading_target_spec,
	    SYMBOL_FUNCTION(Qcompile_2d_shading_target_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_shading_target_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qconstant = STATIC_SYMBOL("CONSTANT",AB_package);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_2d_shading_target_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-SHADING-TARGET-SPEC-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_shading_target_spec_from_slot,
	    STATIC_FUNCTION(write_2d_shading_target_spec_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Q2d_shading_target_spec,
	    SYMBOL_FUNCTION(Qwrite_2d_shading_target_spec_from_slot),
	    Qslot_value_writer);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_3 = STATIC_CONS(Qno_item,Qnil);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_3,Qsymbol);
    set_property_value_function(get_symbol_properties_function(Q2d_shading_target_spec),
	    Qtype_specification_simple_expansion,list_constant_2);
    define_type_specification_explicit_complex_type(Q2d_shading_target_spec,
	    list_constant_2);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_shading_target_spec);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qtarget = STATIC_SYMBOL("TARGET",AB_package);
    string_constant_2 = 
	    STATIC_STRING("shading target, ~a, must be TOP, or BOTTOM");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_3 = STATIC_STRING("~NT ");
    string_constant_4 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    n_2d_shading_target_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_shading_target_spec_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_shading_target_spec,
	    n_2d_shading_target_spec_evaluation_setter_1);
    n_2d_shading_target_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_shading_target_spec_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_shading_target_spec,
	    n_2d_shading_target_spec_evaluation_getter_1);
    string_constant_60 = 
	    STATIC_STRING("1p1n83owy1n1m9k83-*Ly1m9k83-Ty832Cy1o83J2y6A83-*Oyn1n83owy1m1m9k831Sy1m9k83*ly1o837Ry6D83-Cey83gRy1n83owy1m9k83amy1o837Ry6C83-Ce");
    string_constant_61 = 
	    STATIC_STRING("y83amy1n83owy1m9k83lZy1o837Ry6B83-Cey83lZy1n83owy1m9k83ly1o837Ry6A83-Cey83ly");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_60,
	    string_constant_61)));
    Q2d_plot_marker_shape = STATIC_SYMBOL("2D-PLOT-MARKER-SHAPE",AB_package);
    string_constant_62 = 
	    STATIC_STRING("1p1o83J2yk83-*Oyn1o837Ryn83-Cey83gRy1o837Rym83-Cey83amy1o837Ryl83-Cey83lZy1o837Ryk83-Cey83ly");
    mutate_global_property(Q2d_plot_marker_shape,
	    regenerate_optimized_constant(string_constant_62),
	    Qframe_like_category_cases);
    Qcompile_2d_plot_marker_shape_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-PLOT-MARKER-SHAPE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_plot_marker_shape_for_slot,
	    STATIC_FUNCTION(compile_2d_plot_marker_shape_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Q2d_plot_marker_shape,
	    SYMBOL_FUNCTION(Qcompile_2d_plot_marker_shape_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_plot_marker_shape,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcustom = STATIC_SYMBOL("CUSTOM",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    string_constant_5 = STATIC_STRING(" ");
    array_constant_4 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    Qicon_class = STATIC_SYMBOL("ICON-CLASS",AB_package);
    Qab_standard = STATIC_SYMBOL("STANDARD",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_2d_plot_marker_shape_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-PLOT-MARKER-SHAPE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_plot_marker_shape_from_slot,
	    STATIC_FUNCTION(write_2d_plot_marker_shape_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Q2d_plot_marker_shape,
	    SYMBOL_FUNCTION(Qwrite_2d_plot_marker_shape_from_slot),
	    Qslot_value_writer);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_22 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Q2d_plot_marker_shape),
	    Qtype_specification_simple_expansion,list_constant_22);
    Qstandard_shape = STATIC_SYMBOL("STANDARD-SHAPE",AB_package);
    list_constant_47 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_48 = STATIC_CONS(Qstandard_shape,list_constant_47);
    Qicon_of_class = STATIC_SYMBOL("ICON-OF-CLASS",AB_package);
    list_constant_49 = STATIC_CONS(Qicon_of_class,list_constant_47);
    list_constant_50 = STATIC_LIST((SI_Long)2L,list_constant_48,
	    list_constant_49);
    list_constant_51 = STATIC_LIST((SI_Long)3L,Qab_or,Qstandard_shape,
	    Qicon_of_class);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_50,list_constant_51);
    define_type_specification_explicit_complex_type(Q2d_plot_marker_shape,
	    list_constant_5);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_plot_marker_shape);
    Qshape = STATIC_SYMBOL("SHAPE",AB_package);
    n_2d_plot_marker_shape_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_plot_marker_shape_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_plot_marker_shape,
	    n_2d_plot_marker_shape_evaluation_setter_1);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    n_2d_plot_marker_shape_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_plot_marker_shape_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_plot_marker_shape,
	    n_2d_plot_marker_shape_evaluation_getter_1);
    string_constant_63 = 
	    STATIC_STRING("1n1n83-IXy1n1m9k83HCy1m9k831Dy1m9k834ry1o83-Bay6B9l83HCy1n83-IXy1n1m9k83GOy1m9k831Dy1m9k834ry1o83-Bay6A9l83GOy1n83-IXy1m9k83Zy1m");
    string_constant_64 = STATIC_STRING("83Zy6A");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qposition);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_63,
	    string_constant_64)));
    Q2d_location_spec = STATIC_SYMBOL("2D-LOCATION-SPEC",AB_package);
    string_constant_65 = 
	    STATIC_STRING("1n1o83-Bayl9k83HCy1o83-Bayk9k83GOy1m83Zyk");
    clear_optimized_constants();
    push_optimized_constant(Qposition);
    mutate_global_property(Q2d_location_spec,
	    regenerate_optimized_constant(string_constant_65),
	    Qframe_like_category_cases);
    Qcompile_2d_location_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-LOCATION-SPEC-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_location_spec_for_slot,
	    STATIC_FUNCTION(compile_2d_location_spec_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Q2d_location_spec,
	    SYMBOL_FUNCTION(Qcompile_2d_location_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_location_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qrelative_to_window = STATIC_SYMBOL("RELATIVE-TO-WINDOW",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_2d_location_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-LOCATION-SPEC-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_location_spec_from_slot,
	    STATIC_FUNCTION(write_2d_location_spec_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Q2d_location_spec,
	    SYMBOL_FUNCTION(Qwrite_2d_location_spec_from_slot),
	    Qslot_value_writer);
    string_constant_66 = 
	    STATIC_STRING("1m1n83p-y1n1m9k83-6Ry1m9k833Wy1m9k83*xy1o83Uny6A83bOy839gy1n83p-y83*uy1o83GPy6A83*xyl");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_66));
    Q2d_tickmark_label_color = STATIC_SYMBOL("2D-TICKMARK-LABEL-COLOR",
	    AB_package);
    string_constant_67 = STATIC_STRING("1m1o83Unyk83bOy839gy1o83GPyk83*xyl");
    mutate_global_property(Q2d_tickmark_label_color,
	    regenerate_optimized_constant(string_constant_67),
	    Qframe_like_category_cases);
    Qabsolute = STATIC_SYMBOL("ABSOLUTE",AB_package);
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    string_constant_6 = STATIC_STRING("Unknown color requested");
    Qcompile_2d_tickmark_label_color_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-TICKMARK-LABEL-COLOR-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_tickmark_label_color_for_slot,
	    STATIC_FUNCTION(compile_2d_tickmark_label_color_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Q2d_tickmark_label_color,
	    SYMBOL_FUNCTION(Qcompile_2d_tickmark_label_color_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_tickmark_label_color,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qmatching = STATIC_SYMBOL("MATCHING",AB_package);
    array_constant_14 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    array_constant_15 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_2d_tickmark_label_color_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-TICKMARK-LABEL-COLOR-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_tickmark_label_color_from_slot,
	    STATIC_FUNCTION(write_2d_tickmark_label_color_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Q2d_tickmark_label_color,
	    SYMBOL_FUNCTION(Qwrite_2d_tickmark_label_color_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Q2d_tickmark_label_color),
	    Qtype_specification_simple_expansion,list_constant_22);
    Qlabel_color_type = STATIC_SYMBOL("LABEL-COLOR-TYPE",AB_package);
    Qmatching_plot_color = STATIC_SYMBOL("MATCHING-PLOT-COLOR",AB_package);
    list_constant_52 = STATIC_LIST((SI_Long)3L,Qmember,Qabsolute,
	    Qmatching_plot_color);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qlabel_color_type,
	    list_constant_52);
    list_constant_54 = STATIC_LIST((SI_Long)2L,Qcolor,list_constant);
    list_constant_55 = STATIC_LIST((SI_Long)2L,list_constant_53,
	    list_constant_54);
    list_constant_56 = STATIC_LIST((SI_Long)2L,Qand,Qlabel_color_type);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_55,list_constant_56);
    define_type_specification_explicit_complex_type(Q2d_tickmark_label_color,
	    list_constant_7);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_tickmark_label_color);
    Qplot_color = STATIC_SYMBOL("PLOT-COLOR",AB_package);
    n_2d_tickmark_label_color_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_tickmark_label_color_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_tickmark_label_color,
	    n_2d_tickmark_label_color_evaluation_setter_1);
    n_2d_tickmark_label_color_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_tickmark_label_color_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_tickmark_label_color,
	    n_2d_tickmark_label_color_evaluation_getter_1);
    string_constant_68 = 
	    STATIC_STRING("1m1n83p=y83-oy1o83-oy6A9kl1n83p=y1n1m9l83n-y1m9l830*y1m9l836xy1m83pcy6A");
    clear_optimized_constants();
    push_optimized_constant(Qlength);
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_68));
    Q2d_time_span_spec = STATIC_SYMBOL("2D-TIME-SPAN-SPEC",AB_package);
    string_constant_69 = STATIC_STRING("1m1o83-oyk9kl1m83pcyk");
    clear_optimized_constants();
    push_optimized_constant(Qlength);
    mutate_global_property(Q2d_time_span_spec,
	    regenerate_optimized_constant(string_constant_69),
	    Qframe_like_category_cases);
    array_constant_17 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)18L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)28L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)30L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)34L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)38L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)39L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)40L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)41L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)46L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)47L,(SI_Long)57344L);
    Qcompile_2d_time_span_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-TIME-SPAN-SPEC-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_time_span_spec_for_slot,
	    STATIC_FUNCTION(compile_2d_time_span_spec_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Q2d_time_span_spec,
	    SYMBOL_FUNCTION(Qcompile_2d_time_span_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_time_span_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qall_history = STATIC_SYMBOL("ALL-HISTORY",AB_package);
    array_constant_18 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_2d_time_span_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-TIME-SPAN-SPEC-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_time_span_spec_from_slot,
	    STATIC_FUNCTION(write_2d_time_span_spec_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Q2d_time_span_spec,
	    SYMBOL_FUNCTION(Qwrite_2d_time_span_spec_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Q2d_time_span_spec),
	    Qtype_specification_simple_expansion,list_constant_22);
    Qdata_window_time_span_mode = 
	    STATIC_SYMBOL("DATA-WINDOW-TIME-SPAN-MODE",AB_package);
    Qshow_all_history = STATIC_SYMBOL("SHOW-ALL-HISTORY",AB_package);
    list_constant_57 = STATIC_LIST((SI_Long)3L,Qmember,Qshow_all_history,
	    Qinterval);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qdata_window_time_span_mode,
	    list_constant_57);
    Qnumber_of_seconds = STATIC_SYMBOL("NUMBER-OF-SECONDS",AB_package);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qnumber_of_seconds,Qinteger);
    list_constant_60 = STATIC_LIST((SI_Long)2L,list_constant_58,
	    list_constant_59);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qand,
	    Qdata_window_time_span_mode);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_60,list_constant_61);
    define_type_specification_explicit_complex_type(Q2d_time_span_spec,
	    list_constant_9);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_time_span_spec);
    string_constant_7 = 
	    STATIC_STRING("must specify all of (NUMBER-OF-SECONDS)");
    n_2d_time_span_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_time_span_spec_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_time_span_spec,
	    n_2d_time_span_spec_evaluation_setter_1);
    n_2d_time_span_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_time_span_spec_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_time_span_spec,
	    n_2d_time_span_spec_evaluation_getter_1);
    string_constant_70 = 
	    STATIC_STRING("1m1n83p0y83-oy1o83-oy6A9kl1n83p0y1o1m9l83Euy1m9l83*5y1m9l831Dy1m9l834ry1m83uWy6A");
    clear_optimized_constants();
    push_optimized_constant(Qlength);
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_70));
    Q2d_total_time_span_spec = STATIC_SYMBOL("2D-TOTAL-TIME-SPAN-SPEC",
	    AB_package);
    string_constant_71 = STATIC_STRING("1m1o83-oyk9kl1m83uWyk");
    clear_optimized_constants();
    push_optimized_constant(Qlength);
    mutate_global_property(Q2d_total_time_span_spec,
	    regenerate_optimized_constant(string_constant_71),
	    Qframe_like_category_cases);
    Qcompile_2d_total_time_span_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-TOTAL-TIME-SPAN-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_total_time_span_spec_for_slot,
	    STATIC_FUNCTION(compile_2d_total_time_span_spec_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Q2d_total_time_span_spec,
	    SYMBOL_FUNCTION(Qcompile_2d_total_time_span_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_total_time_span_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qdata_window = STATIC_SYMBOL("DATA-WINDOW",AB_package);
    array_constant_21 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_2d_total_time_span_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-TOTAL-TIME-SPAN-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_total_time_span_spec_from_slot,
	    STATIC_FUNCTION(write_2d_total_time_span_spec_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Q2d_total_time_span_spec,
	    SYMBOL_FUNCTION(Qwrite_2d_total_time_span_spec_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Q2d_total_time_span_spec),
	    Qtype_specification_simple_expansion,list_constant_22);
    Qtotal_time_span_mode = STATIC_SYMBOL("TOTAL-TIME-SPAN-MODE",AB_package);
    Qsame_as_data_window = STATIC_SYMBOL("SAME-AS-DATA-WINDOW",AB_package);
    list_constant_62 = STATIC_CONS(Qinterval,Qnil);
    list_constant_63 = STATIC_LIST_STAR((SI_Long)3L,Qmember,
	    Qsame_as_data_window,list_constant_62);
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qtotal_time_span_mode,
	    list_constant_63);
    list_constant_65 = STATIC_CONS(list_constant_59,Qnil);
    list_constant_66 = STATIC_CONS(list_constant_64,list_constant_65);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qand,Qtotal_time_span_mode);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_66,list_constant_67);
    define_type_specification_explicit_complex_type(Q2d_total_time_span_spec,
	    list_constant_11);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_total_time_span_spec);
    n_2d_total_time_span_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_total_time_span_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_total_time_span_spec,
	    n_2d_total_time_span_spec_evaluation_setter_1);
    n_2d_total_time_span_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_total_time_span_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_total_time_span_spec,
	    n_2d_total_time_span_spec_evaluation_getter_1);
    string_constant_72 = 
	    STATIC_STRING("1n1n83oty1n83-oy1m9k835+y1m9k836Gy1o83-Dey6A83-oyl1n83oty1m1m9k9l1m9k83-CAy1m83-1qy6A1n83oty1m1m9k831Sy1m9k831Ay1m83BTy6A");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qlast);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_72));
    Q2d_end_time_spec = STATIC_SYMBOL("2D-END-TIME-SPEC",AB_package);
    string_constant_73 = STATIC_STRING("1n1o83-Deyk83-oyl1m83-1qyk1m83BTyk");
    mutate_global_property(Q2d_end_time_spec,
	    regenerate_optimized_constant(string_constant_73),
	    Qframe_like_category_cases);
    Qcompile_2d_end_time_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-END-TIME-SPEC-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_end_time_spec_for_slot,
	    STATIC_FUNCTION(compile_2d_end_time_spec_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Q2d_end_time_spec,
	    SYMBOL_FUNCTION(Qcompile_2d_end_time_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_end_time_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qstart_relative = STATIC_SYMBOL("START-RELATIVE",AB_package);
    array_constant_23 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)57344L);
    Qlast_sample = STATIC_SYMBOL("LAST-SAMPLE",AB_package);
    array_constant_25 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)57344L);
    Qcurrent_time = STATIC_SYMBOL("CURRENT-TIME",AB_package);
    array_constant_27 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_2d_end_time_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-END-TIME-SPEC-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_end_time_spec_from_slot,
	    STATIC_FUNCTION(write_2d_end_time_spec_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Q2d_end_time_spec,
	    SYMBOL_FUNCTION(Qwrite_2d_end_time_spec_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Q2d_end_time_spec),
	    Qtype_specification_simple_expansion,list_constant_22);
    Qend_time_mode = STATIC_SYMBOL("END-TIME-MODE",AB_package);
    list_constant_68 = STATIC_LIST((SI_Long)4L,Qmember,Qcurrent_time,
	    Qlast_sample,Qstart_relative);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qend_time_mode,
	    list_constant_68);
    list_constant_70 = STATIC_CONS(list_constant_69,list_constant_65);
    list_constant_71 = STATIC_LIST((SI_Long)2L,Qand,Qend_time_mode);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_70,list_constant_71);
    define_type_specification_explicit_complex_type(Q2d_end_time_spec,
	    list_constant_13);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_end_time_spec);
    n_2d_end_time_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_end_time_spec_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Q2d_end_time_spec,
	    n_2d_end_time_spec_evaluation_setter_1);
    n_2d_end_time_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_end_time_spec_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Q2d_end_time_spec,
	    n_2d_end_time_spec_evaluation_getter_1);
    string_constant_74 = 
	    STATIC_STRING("1m1n83-IYy83-oy1o83-oy6A9kl1n83-IYy1m9l83Zy1m83Zy6A");
    clear_optimized_constants();
    push_optimized_constant(Qlength);
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_74));
    Q2d_scrolling_alignment_spec = 
	    STATIC_SYMBOL("2D-SCROLLING-ALIGNMENT-SPEC",AB_package);
    string_constant_75 = STATIC_STRING("1m1o83-oyk9kl1m83Zyk");
    clear_optimized_constants();
    push_optimized_constant(Qlength);
    mutate_global_property(Q2d_scrolling_alignment_spec,
	    regenerate_optimized_constant(string_constant_75),
	    Qframe_like_category_cases);
    string_constant_8 = 
	    STATIC_STRING("Must use an interval between 1 seconds and one-day");
    Qcompile_2d_scrolling_alignment_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-SCROLLING-ALIGNMENT-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_scrolling_alignment_spec_for_slot,
	    STATIC_FUNCTION(compile_2d_scrolling_alignment_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Q2d_scrolling_alignment_spec,
	    SYMBOL_FUNCTION(Qcompile_2d_scrolling_alignment_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_scrolling_alignment_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_2d_scrolling_alignment_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-SCROLLING-ALIGNMENT-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_scrolling_alignment_spec_from_slot,
	    STATIC_FUNCTION(write_2d_scrolling_alignment_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Q2d_scrolling_alignment_spec,
	    SYMBOL_FUNCTION(Qwrite_2d_scrolling_alignment_spec_from_slot),
	    Qslot_value_writer);
    string_constant_76 = 
	    STATIC_STRING("1n1n83p*y1m1m9k9l83-oy1o83-oy6A9mm1n83p*y1m9k83Ary1m83A5y6A1n83p*y1m9k83Zy1m83Zy6A");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qevery);
    push_optimized_constant(Qlength);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_76));
    Q2d_time_axis_tickmark_frequency_spec = 
	    STATIC_SYMBOL("2D-TIME-AXIS-TICKMARK-FREQUENCY-SPEC",AB_package);
    string_constant_77 = STATIC_STRING("1n1o83-oyk9km1m83A5yk1m83Zyk");
    clear_optimized_constants();
    push_optimized_constant(Qlength);
    mutate_global_property(Q2d_time_axis_tickmark_frequency_spec,
	    regenerate_optimized_constant(string_constant_77),
	    Qframe_like_category_cases);
    string_constant_9 = 
	    STATIC_STRING("Must use an interval between 1 second and one-day");
    Qcompile_2d_time_axis_tickmark_frequency_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-TIME-AXIS-TICKMARK-FREQUENCY-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_time_axis_tickmark_frequency_spec_for_slot,
	    STATIC_FUNCTION(compile_2d_time_axis_tickmark_frequency_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Q2d_time_axis_tickmark_frequency_spec,
	    SYMBOL_FUNCTION(Qcompile_2d_time_axis_tickmark_frequency_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_time_axis_tickmark_frequency_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_28 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)57344L);
    Qsynchronized = STATIC_SYMBOL("SYNCHRONIZED",AB_package);
    array_constant_29 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_2d_time_axis_tickmark_frequency_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-TIME-AXIS-TICKMARK-FREQUENCY-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_time_axis_tickmark_frequency_spec_from_slot,
	    STATIC_FUNCTION(write_2d_time_axis_tickmark_frequency_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Q2d_time_axis_tickmark_frequency_spec,
	    SYMBOL_FUNCTION(Qwrite_2d_time_axis_tickmark_frequency_spec_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Q2d_time_axis_tickmark_frequency_spec),
	    Qtype_specification_simple_expansion,list_constant_22);
    Qlabel_frequency_mode = STATIC_SYMBOL("LABEL-FREQUENCY-MODE",AB_package);
    Qno_labels = STATIC_SYMBOL("NO-LABELS",AB_package);
    list_constant_72 = STATIC_LIST_STAR((SI_Long)4L,Qmember,Qno_labels,
	    Qsynchronized,list_constant_62);
    list_constant_73 = STATIC_LIST((SI_Long)2L,Qlabel_frequency_mode,
	    list_constant_72);
    list_constant_74 = STATIC_CONS(list_constant_73,list_constant_65);
    list_constant_75 = STATIC_LIST((SI_Long)2L,Qand,Qlabel_frequency_mode);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_74,list_constant_75);
    define_type_specification_explicit_complex_type(Q2d_time_axis_tickmark_frequency_spec,
	    list_constant_15);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_time_axis_tickmark_frequency_spec);
    n_2d_time_axis_tickmark_frequency_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_time_axis_tickmark_frequency_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_time_axis_tickmark_frequency_spec,
	    n_2d_time_axis_tickmark_frequency_spec_evaluation_setter_1);
    n_2d_time_axis_tickmark_frequency_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_time_axis_tickmark_frequency_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_time_axis_tickmark_frequency_spec,
	    n_2d_time_axis_tickmark_frequency_spec_evaluation_getter_1);
    string_constant_78 = 
	    STATIC_STRING("1l1n83ovy1n1m9k9l83Sy1m9k839iy1o83-9xy6A83-Hym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qevery);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_78));
    Q2d_plot_marker_frequency = STATIC_SYMBOL("2D-PLOT-MARKER-FREQUENCY",
	    AB_package);
    string_constant_79 = STATIC_STRING("1l1o83-9xyk83-Hym");
    mutate_global_property(Q2d_plot_marker_frequency,
	    regenerate_optimized_constant(string_constant_79),
	    Qframe_like_category_cases);
    string_constant_10 = 
	    STATIC_STRING("Must specify a ratio between 1 and 1000");
    Qcompile_2d_plot_marker_frequency_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-PLOT-MARKER-FREQUENCY-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_plot_marker_frequency_for_slot,
	    STATIC_FUNCTION(compile_2d_plot_marker_frequency_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Q2d_plot_marker_frequency,
	    SYMBOL_FUNCTION(Qcompile_2d_plot_marker_frequency_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_plot_marker_frequency,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_30 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_2d_plot_marker_frequency_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-PLOT-MARKER-FREQUENCY-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_plot_marker_frequency_from_slot,
	    STATIC_FUNCTION(write_2d_plot_marker_frequency_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Q2d_plot_marker_frequency,
	    SYMBOL_FUNCTION(Qwrite_2d_plot_marker_frequency_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Q2d_plot_marker_frequency),
	    Qtype_specification_simple_expansion,list_constant_22);
    Qpoints_per_marker = STATIC_SYMBOL("POINTS-PER-MARKER",AB_package);
    list_constant_76 = STATIC_CONS(Qinteger,Qnil);
    list_constant_77 = STATIC_CONS(Qpoints_per_marker,list_constant_76);
    list_constant_78 = STATIC_CONS(list_constant_77,Qnil);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qand,Qpoints_per_marker);
    list_constant_17 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_78,list_constant_79);
    define_type_specification_explicit_complex_type(Q2d_plot_marker_frequency,
	    list_constant_17);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_plot_marker_frequency);
    string_constant_11 = 
	    STATIC_STRING("Must specify a ratio of between 1 and 1000 points per marker");
    n_2d_plot_marker_frequency_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_plot_marker_frequency_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_plot_marker_frequency,
	    n_2d_plot_marker_frequency_evaluation_setter_1);
    n_2d_plot_marker_frequency_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_plot_marker_frequency_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_plot_marker_frequency,
	    n_2d_plot_marker_frequency_evaluation_getter_1);
    string_constant_80 = 
	    STATIC_STRING("1o1n83p2y1p1m9k9l83-Hy1m9k83HBy1m9k83=Gy83-Hy1q83-oy6B83*4ym83-8Dyp1n83p2y1m1m9k9l83-Hy1q83-oy6A83*4ym83-8Dy01n83p2y1m83Sy1m9k9m");
    string_constant_81 = 
	    STATIC_STRING("1o83wpy6A9nl1n83p2y1m9k83Ary1m83Ary6A");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qevery);
    push_optimized_constant(Qlabels);
    push_optimized_constant(Qcount);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_80,
	    string_constant_81)));
    Q2d_value_axis_tickmark_frequency_spec = 
	    STATIC_SYMBOL("2D-VALUE-AXIS-TICKMARK-FREQUENCY-SPEC",AB_package);
    string_constant_82 = 
	    STATIC_STRING("1o1q83-oyl83*4ym83-8Dyp1q83-oyk83*4ym83-8Dy01o83wpyk9kl1m83Aryk");
    clear_optimized_constants();
    push_optimized_constant(Qcount);
    mutate_global_property(Q2d_value_axis_tickmark_frequency_spec,
	    regenerate_optimized_constant(string_constant_82),
	    Qframe_like_category_cases);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    string_constant_12 = 
	    STATIC_STRING("Must specify a positive label interval");
    Qfraction = STATIC_SYMBOL("FRACTION",AB_package);
    string_constant_13 = 
	    STATIC_STRING("Must specify between 1 and 1000 labels");
    Qcompile_2d_value_axis_tickmark_frequency_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-VALUE-AXIS-TICKMARK-FREQUENCY-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_value_axis_tickmark_frequency_spec_for_slot,
	    STATIC_FUNCTION(compile_2d_value_axis_tickmark_frequency_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Q2d_value_axis_tickmark_frequency_spec,
	    SYMBOL_FUNCTION(Qcompile_2d_value_axis_tickmark_frequency_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_value_axis_tickmark_frequency_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_31 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)15L,(SI_Long)57344L);
    array_constant_32 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)57344L);
    Qorigin = STATIC_SYMBOL("ORIGIN",AB_package);
    array_constant_33 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)15L,(SI_Long)57344L);
    Qautomatic = STATIC_SYMBOL("AUTOMATIC",AB_package);
    Qwrite_2d_value_axis_tickmark_frequency_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-VALUE-AXIS-TICKMARK-FREQUENCY-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_value_axis_tickmark_frequency_spec_from_slot,
	    STATIC_FUNCTION(write_2d_value_axis_tickmark_frequency_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Q2d_value_axis_tickmark_frequency_spec,
	    SYMBOL_FUNCTION(Qwrite_2d_value_axis_tickmark_frequency_spec_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Q2d_value_axis_tickmark_frequency_spec),
	    Qtype_specification_simple_expansion,list_constant_22);
    Qlabel_layout_mode = STATIC_SYMBOL("LABEL-LAYOUT-MODE",AB_package);
    Qgrid_division = STATIC_SYMBOL("GRID-DIVISION",AB_package);
    list_constant_80 = STATIC_LIST_STAR((SI_Long)4L,Qmember,Qautomatic,
	    Qgrid_division,list_constant_62);
    list_constant_82 = STATIC_LIST((SI_Long)2L,Qlabel_layout_mode,
	    list_constant_80);
    Qnumber_of_grid_divisions = STATIC_SYMBOL("NUMBER-OF-GRID-DIVISIONS",
	    AB_package);
    list_constant_83 = STATIC_CONS(Qnumber_of_grid_divisions,list_constant_76);
    Qinterval_width = STATIC_SYMBOL("INTERVAL-WIDTH",AB_package);
    list_constant_81 = STATIC_CONS(Qnumber,Qnil);
    list_constant_84 = STATIC_CONS(Qinterval_width,list_constant_81);
    Qinterval_origin = STATIC_SYMBOL("INTERVAL-ORIGIN",AB_package);
    list_constant_85 = STATIC_CONS(Qinterval_origin,list_constant_81);
    list_constant_86 = STATIC_LIST((SI_Long)4L,list_constant_82,
	    list_constant_83,list_constant_84,list_constant_85);
    list_constant_87 = STATIC_LIST((SI_Long)2L,Qand,Qlabel_layout_mode);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_86,list_constant_87);
    define_type_specification_explicit_complex_type(Q2d_value_axis_tickmark_frequency_spec,
	    list_constant_19);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_value_axis_tickmark_frequency_spec);
    string_constant_14 = 
	    STATIC_STRING("must specify number-of-grid-divisions");
    string_constant_15 = STATIC_STRING("must specify interval-width");
    n_2d_value_axis_tickmark_frequency_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_value_axis_tickmark_frequency_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_value_axis_tickmark_frequency_spec,
	    n_2d_value_axis_tickmark_frequency_spec_evaluation_setter_1);
    n_2d_value_axis_tickmark_frequency_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_value_axis_tickmark_frequency_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_value_axis_tickmark_frequency_spec,
	    n_2d_value_axis_tickmark_frequency_spec_evaluation_getter_1);
    string_constant_83 = 
	    STATIC_STRING("1m1n83p1y1o1m9k832+y83-Hy1m9k83=3y83-Hy1q83-DYy6A83-2eym83-Ftyo1n83p1y1m9k83Zy1m83Zy6A");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_83));
    Q2d_value_axis_bounds_spec = STATIC_SYMBOL("2D-VALUE-AXIS-BOUNDS-SPEC",
	    AB_package);
    string_constant_84 = STATIC_STRING("1m1q83-DYyk83-2eym83-Ftyo1m83Zyk");
    mutate_global_property(Q2d_value_axis_bounds_spec,
	    regenerate_optimized_constant(string_constant_84),
	    Qframe_like_category_cases);
    Qspecified = STATIC_SYMBOL("SPECIFIED",AB_package);
    Qlower = STATIC_SYMBOL("LOWER",AB_package);
    Qupper = STATIC_SYMBOL("UPPER",AB_package);
    string_constant_16 = 
	    STATIC_STRING("Lower bound must be less than upper bound and greater than ~%~a. Upper bound must be less than ~a");
    float_constant = STATIC_FLOAT(-1.7976931348623158E+304);
    float_constant_1 = STATIC_FLOAT(1.7976931348623158E+304);
    Qcompile_2d_value_axis_bounds_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-2D-VALUE-AXIS-BOUNDS-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_2d_value_axis_bounds_spec_for_slot,
	    STATIC_FUNCTION(compile_2d_value_axis_bounds_spec_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Q2d_value_axis_bounds_spec,
	    SYMBOL_FUNCTION(Qcompile_2d_value_axis_bounds_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Q2d_value_axis_bounds_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_34 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)57344L);
    array_constant_35 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_2d_value_axis_bounds_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-VALUE-AXIS-BOUNDS-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_value_axis_bounds_spec_from_slot,
	    STATIC_FUNCTION(write_2d_value_axis_bounds_spec_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Q2d_value_axis_bounds_spec,
	    SYMBOL_FUNCTION(Qwrite_2d_value_axis_bounds_spec_from_slot),
	    Qslot_value_writer);
    list_constant_88 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_3,
	    list_constant_22);
    set_property_value_function(get_symbol_properties_function(Q2d_value_axis_bounds_spec),
	    Qtype_specification_simple_expansion,list_constant_88);
    Qlower_bound = STATIC_SYMBOL("LOWER-BOUND",AB_package);
    list_constant_89 = STATIC_CONS(Qlower_bound,list_constant_81);
    Qupper_bound = STATIC_SYMBOL("UPPER-BOUND",AB_package);
    list_constant_90 = STATIC_CONS(Qupper_bound,list_constant_81);
    list_constant_91 = STATIC_LIST((SI_Long)2L,list_constant_89,
	    list_constant_90);
    list_constant_92 = STATIC_LIST((SI_Long)3L,Qand,Qlower_bound,Qupper_bound);
    list_constant_93 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_91,list_constant_92);
    list_constant_21 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_3,
	    list_constant_93);
    define_type_specification_explicit_complex_type(Q2d_value_axis_bounds_spec,
	    list_constant_21);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Q2d_value_axis_bounds_spec);
    n_2d_value_axis_bounds_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_value_axis_bounds_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_value_axis_bounds_spec,
	    n_2d_value_axis_bounds_spec_evaluation_setter_1);
    n_2d_value_axis_bounds_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_value_axis_bounds_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_value_axis_bounds_spec,
	    n_2d_value_axis_bounds_spec_evaluation_getter_1);
    string_constant_85 = 
	    STATIC_STRING("1m1n83-FGy83*uy1o83GPy6A83*xyl1n83-FGy1n1m9k83-6Ry1m9k833Wy1m9k83sKy1m83Uny6A");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_85));
    Qtrend_chart_legend_color_spec = 
	    STATIC_SYMBOL("TREND-CHART-LEGEND-COLOR-SPEC",AB_package);
    string_constant_86 = STATIC_STRING("1m1o83GPyk83*xyl1m83Unyk");
    mutate_global_property(Qtrend_chart_legend_color_spec,
	    regenerate_optimized_constant(string_constant_86),
	    Qframe_like_category_cases);
    Qcompile_trend_chart_legend_color_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-TREND-CHART-LEGEND-COLOR-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_trend_chart_legend_color_spec_for_slot,
	    STATIC_FUNCTION(compile_trend_chart_legend_color_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtrend_chart_legend_color_spec,
	    SYMBOL_FUNCTION(Qcompile_trend_chart_legend_color_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtrend_chart_legend_color_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_36 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_trend_chart_legend_color_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-TREND-CHART-LEGEND-COLOR-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_trend_chart_legend_color_spec_from_slot,
	    STATIC_FUNCTION(write_trend_chart_legend_color_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtrend_chart_legend_color_spec,
	    SYMBOL_FUNCTION(Qwrite_trend_chart_legend_color_spec_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qtrend_chart_legend_color_spec),
	    Qtype_specification_simple_expansion,list_constant_22);
    Qlegend_color_type = STATIC_SYMBOL("LEGEND-COLOR-TYPE",AB_package);
    list_constant_94 = STATIC_CONS(list_constant_52,Qnil);
    list_constant_95 = STATIC_CONS(Qlegend_color_type,list_constant_94);
    list_constant_96 = STATIC_CONS(list_constant_54,Qnil);
    list_constant_97 = STATIC_CONS(list_constant_95,list_constant_96);
    list_constant_98 = STATIC_LIST((SI_Long)2L,Qand,Qlegend_color_type);
    list_constant_24 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_97,list_constant_98);
    define_type_specification_explicit_complex_type(Qtrend_chart_legend_color_spec,
	    list_constant_24);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_legend_color_spec);
    trend_chart_legend_color_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(trend_chart_legend_color_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtrend_chart_legend_color_spec,
	    trend_chart_legend_color_spec_evaluation_setter_1);
    trend_chart_legend_color_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(trend_chart_legend_color_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtrend_chart_legend_color_spec,
	    trend_chart_legend_color_spec_evaluation_getter_1);
    Qvalue_axis_position = STATIC_SYMBOL("VALUE-AXIS-POSITION",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    list_constant_99 = STATIC_LIST((SI_Long)2L,Qright,Qleft);
    Qenumeration_grammar_category_members = 
	    STATIC_SYMBOL("ENUMERATION-GRAMMAR-CATEGORY-MEMBERS",AB_package);
    mutate_global_property(Qvalue_axis_position,list_constant_99,
	    Qenumeration_grammar_category_members);
    string_constant_87 = 
	    STATIC_STRING("1m1n83-GNy1m9k83*hy83*hy1n83-GNy1m9k83-by83-by");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_87));
    set_property_value_function(get_symbol_properties_function(Qvalue_axis_position),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_26 = STATIC_CONS(Qmember,list_constant_99);
    define_type_specification_explicit_complex_type(Qvalue_axis_position,
	    list_constant_26);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qnamed,Qvalue_axis_position);
    value_axis_position_evaluation_setter_1 = 
	    STATIC_FUNCTION(value_axis_position_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qvalue_axis_position,
	    value_axis_position_evaluation_setter_1);
    value_axis_position_evaluation_getter_1 = 
	    STATIC_FUNCTION(value_axis_position_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qvalue_axis_position,
	    value_axis_position_evaluation_getter_1);
    string_constant_17 = STATIC_STRING("left");
    string_constant_18 = STATIC_STRING("right");
    Qwrite_value_axis_position_from_slot = 
	    STATIC_SYMBOL("WRITE-VALUE-AXIS-POSITION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_value_axis_position_from_slot,
	    STATIC_FUNCTION(write_value_axis_position_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qvalue_axis_position,
	    SYMBOL_FUNCTION(Qwrite_value_axis_position_from_slot),
	    Qslot_value_writer);
    Qtrend_chart_legend_position = 
	    STATIC_SYMBOL("TREND-CHART-LEGEND-POSITION",AB_package);
    Qabove = STATIC_SYMBOL("ABOVE",AB_package);
    Qbelow = STATIC_SYMBOL("BELOW",AB_package);
    list_constant_100 = STATIC_LIST((SI_Long)2L,Qabove,Qbelow);
    mutate_global_property(Qtrend_chart_legend_position,list_constant_100,
	    Qenumeration_grammar_category_members);
    string_constant_88 = 
	    STATIC_STRING("1m1n83-FHy1m9k83HCy83HCy1n83-FHy1m9k83GOy83GOy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_88));
    set_property_value_function(get_symbol_properties_function(Qtrend_chart_legend_position),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_28 = STATIC_CONS(Qmember,list_constant_100);
    define_type_specification_explicit_complex_type(Qtrend_chart_legend_position,
	    list_constant_28);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_legend_position);
    trend_chart_legend_position_evaluation_setter_1 = 
	    STATIC_FUNCTION(trend_chart_legend_position_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtrend_chart_legend_position,
	    trend_chart_legend_position_evaluation_setter_1);
    trend_chart_legend_position_evaluation_getter_1 = 
	    STATIC_FUNCTION(trend_chart_legend_position_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtrend_chart_legend_position,
	    trend_chart_legend_position_evaluation_getter_1);
    string_constant_19 = STATIC_STRING("below");
    string_constant_20 = STATIC_STRING("above");
    Qwrite_trend_chart_legend_position_from_slot = 
	    STATIC_SYMBOL("WRITE-TREND-CHART-LEGEND-POSITION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_trend_chart_legend_position_from_slot,
	    STATIC_FUNCTION(write_trend_chart_legend_position_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtrend_chart_legend_position,
	    SYMBOL_FUNCTION(Qwrite_trend_chart_legend_position_from_slot),
	    Qslot_value_writer);
    Q2d_line_style = STATIC_SYMBOL("2D-LINE-STYLE",AB_package);
    Qsample_and_hold_cm_without_risers = 
	    STATIC_SYMBOL("SAMPLE-AND-HOLD-,-WITHOUT-RISERS",AB_package);
    Qsample_and_hold = STATIC_SYMBOL("SAMPLE-AND-HOLD",AB_package);
    Qlinear = STATIC_SYMBOL("LINEAR",AB_package);
    list_constant_101 = STATIC_LIST((SI_Long)3L,
	    Qsample_and_hold_cm_without_risers,Qsample_and_hold,Qlinear);
    mutate_global_property(Q2d_line_style,list_constant_101,
	    Qenumeration_grammar_category_members);
    string_constant_89 = 
	    STATIC_STRING("1n1n83ouy1m9k83-ciy83-=ly1n83ouy1n1m9k83-CAy1m9k83-ty1m9k83-YBy83-nRy1n83ouy1q1m9k83-CAy1m9k83-ty1m9k83-YBy1m9k83vy1m9k83AUy1m9k");
    string_constant_90 = STATIC_STRING("83-n8y83-CBy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_89,
	    string_constant_90)));
    set_property_value_function(get_symbol_properties_function(Q2d_line_style),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_30 = STATIC_CONS(Qmember,list_constant_101);
    define_type_specification_explicit_complex_type(Q2d_line_style,
	    list_constant_30);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_line_style);
    Qsample_and_hold_with_risers = 
	    STATIC_SYMBOL("SAMPLE-AND-HOLD-WITH-RISERS",AB_package);
    Qinterpolated = STATIC_SYMBOL("INTERPOLATED",AB_package);
    n_2d_line_style_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_line_style_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_line_style,
	    n_2d_line_style_evaluation_setter_1);
    n_2d_line_style_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_line_style_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_line_style,
	    n_2d_line_style_evaluation_getter_1);
    string_constant_21 = STATIC_STRING("linear");
    string_constant_22 = STATIC_STRING("sample and hold");
    string_constant_23 = STATIC_STRING("sample and hold , without risers");
    Qwrite_2d_line_style_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-LINE-STYLE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_line_style_from_slot,
	    STATIC_FUNCTION(write_2d_line_style_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Q2d_line_style,
	    SYMBOL_FUNCTION(Qwrite_2d_line_style_from_slot),
	    Qslot_value_writer);
    Qtime_axis_label_alignment = STATIC_SYMBOL("TIME-AXIS-LABEL-ALIGNMENT",
	    AB_package);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    list_constant_102 = STATIC_LIST((SI_Long)3L,Qleft,Qright,Qcenter);
    mutate_global_property(Qtime_axis_label_alignment,list_constant_102,
	    Qenumeration_grammar_category_members);
    string_constant_91 = 
	    STATIC_STRING("1n1n83-F-y1m9k83-cy83-cy1n83-F-y1m9k83-by83-by1n83-F-y1m9k83*hy83*hy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_91));
    set_property_value_function(get_symbol_properties_function(Qtime_axis_label_alignment),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_32 = STATIC_CONS(Qmember,list_constant_102);
    define_type_specification_explicit_complex_type(Qtime_axis_label_alignment,
	    list_constant_32);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtime_axis_label_alignment);
    time_axis_label_alignment_evaluation_setter_1 = 
	    STATIC_FUNCTION(time_axis_label_alignment_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtime_axis_label_alignment,
	    time_axis_label_alignment_evaluation_setter_1);
    time_axis_label_alignment_evaluation_getter_1 = 
	    STATIC_FUNCTION(time_axis_label_alignment_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtime_axis_label_alignment,
	    time_axis_label_alignment_evaluation_getter_1);
    string_constant_24 = STATIC_STRING("center");
    Qwrite_time_axis_label_alignment_from_slot = 
	    STATIC_SYMBOL("WRITE-TIME-AXIS-LABEL-ALIGNMENT-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_time_axis_label_alignment_from_slot,
	    STATIC_FUNCTION(write_time_axis_label_alignment_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qtime_axis_label_alignment,
	    SYMBOL_FUNCTION(Qwrite_time_axis_label_alignment_from_slot),
	    Qslot_value_writer);
    Qtime_axis_label_format_spec = 
	    STATIC_SYMBOL("TIME-AXIS-LABEL-FORMAT-SPEC",AB_package);
    Qhh_mm = STATIC_SYMBOL("HH-MM",AB_package);
    Qhh_mm_as_an_interval = STATIC_SYMBOL("HH-MM-AS-AN-INTERVAL",AB_package);
    Qhh_mm_am_pm = STATIC_SYMBOL("HH-MM-AM-PM",AB_package);
    Qhh_mm_ss = STATIC_SYMBOL("HH-MM-SS",AB_package);
    Qhh_mm_ss_as_an_interval = STATIC_SYMBOL("HH-MM-SS-AS-AN-INTERVAL",
	    AB_package);
    Qhh_mm_ss_am_pm = STATIC_SYMBOL("HH-MM-SS-AM-PM",AB_package);
    Qmm_ss = STATIC_SYMBOL("MM-SS",AB_package);
    Qmm_ss_as_an_interval = STATIC_SYMBOL("MM-SS-AS-AN-INTERVAL",AB_package);
    Qdd_hh_mm_as_an_interval = STATIC_SYMBOL("DD-HH-MM-AS-AN-INTERVAL",
	    AB_package);
    Qmmm_dd_hh_mm = STATIC_SYMBOL("MMM-DD-HH-MM",AB_package);
    Qmm_dd_hh_mm = STATIC_SYMBOL("MM-DD-HH-MM",AB_package);
    Qmm_yy = STATIC_SYMBOL("MM-YY",AB_package);
    Qmm_dd_yy = STATIC_SYMBOL("MM-DD-YY",AB_package);
    Qyy_mm_dd = STATIC_SYMBOL("YY-MM-DD",AB_package);
    Qdd_mm_yy = STATIC_SYMBOL("DD-MM-YY",AB_package);
    Qdd_mmm_yyyy = STATIC_SYMBOL("DD-MMM-YYYY",AB_package);
    Qmmm_dd_yyyy = STATIC_SYMBOL("MMM-DD-YYYY",AB_package);
    Qmmm_yyyy = STATIC_SYMBOL("MMM-YYYY",AB_package);
    Qhh_dot_hh_as_an_interval = STATIC_SYMBOL("HH.HH-AS-AN-INTERVAL",
	    AB_package);
    list_constant_103 = STATIC_LIST((SI_Long)19L,Qhh_mm,
	    Qhh_mm_as_an_interval,Qhh_mm_am_pm,Qhh_mm_ss,
	    Qhh_mm_ss_as_an_interval,Qhh_mm_ss_am_pm,Qmm_ss,
	    Qmm_ss_as_an_interval,Qdd_hh_mm_as_an_interval,Qmmm_dd_hh_mm,
	    Qmm_dd_hh_mm,Qmm_yy,Qmm_dd_yy,Qyy_mm_dd,Qdd_mm_yy,Qdd_mmm_yyyy,
	    Qmmm_dd_yyyy,Qmmm_yyyy,Qhh_dot_hh_as_an_interval);
    mutate_global_property(Qtime_axis_label_format_spec,list_constant_103,
	    Qenumeration_grammar_category_members);
    string_constant_92 = 
	    STATIC_STRING("13Fy1n83-F*y1o1m9k83-*Dy1m9k83*5y1m9k83=ay1m9k83-oy83-Xxy1n83-F*y1m9k83-fIy83-fIy1n83-F*y1m9k83-fHy83-fHy1n83-F*y1m9k83-QOy83-QO");
    string_constant_93 = 
	    STATIC_STRING("y1n83-F*y1m9k83-Q8y83-Q8y1n83-F*y1m9k83-xry83-xry1n83-F*y1m9k83-ety83-ety1n83-F*y1m9k83-fBy83-fBy1n83-F*y1m9k83-esy83-fFy1n83-F*");
    string_constant_94 = 
	    STATIC_STRING("y1m9k83-fGy83-fGy1n83-F*y1o1m9k83-Q2y1m9k83*5y1m9k83=ay1m9k83-oy83-Q3y1n83-F*y1o1m9k83-6sy1m9k83*5y1m9k83=ay1m9k83-oy83-fAy1n83-");
    string_constant_95 = 
	    STATIC_STRING("F*y1m9k83-6sy83-6sy1n83-F*y1m9k83-Xpy83-Xpy1n83-F*y1o1m9k83-*By1m9k83*5y1m9k83=ay1m9k83-oy83-Xty1n83-F*y1m9k83-*By83-*By1n83-F*y");
    string_constant_96 = 
	    STATIC_STRING("1m9k83-Xky83-Xky1n83-F*y1o1m9k83-*9y1m9k83*5y1m9k83=ay1m9k83-oy83-Xoy1n83-F*y1m9k83-*9y83-*9y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_5(string_constant_92,
	    string_constant_93,string_constant_94,string_constant_95,
	    string_constant_96)));
    set_property_value_function(get_symbol_properties_function(Qtime_axis_label_format_spec),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_34 = STATIC_CONS(Qmember,list_constant_103);
    define_type_specification_explicit_complex_type(Qtime_axis_label_format_spec,
	    list_constant_34);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtime_axis_label_format_spec);
    Qhh_mm_interval = STATIC_SYMBOL("HH-MM-INTERVAL",AB_package);
    Qhh_mm_ss_interval = STATIC_SYMBOL("HH-MM-SS-INTERVAL",AB_package);
    Qmm_ss_interval = STATIC_SYMBOL("MM-SS-INTERVAL",AB_package);
    Qdd_hh_mm_interval = STATIC_SYMBOL("DD-HH-MM-INTERVAL",AB_package);
    Qmm_sl_dd_hh_mm = STATIC_SYMBOL("MM/DD-HH-MM",AB_package);
    Qhh_dot_hh_interval = STATIC_SYMBOL("HH.HH-INTERVAL",AB_package);
    time_axis_label_format_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(time_axis_label_format_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtime_axis_label_format_spec,
	    time_axis_label_format_spec_evaluation_setter_1);
    time_axis_label_format_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(time_axis_label_format_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtime_axis_label_format_spec,
	    time_axis_label_format_spec_evaluation_getter_1);
    string_constant_25 = STATIC_STRING("hh.hh as an interval");
    string_constant_26 = STATIC_STRING("mmm-yyyy");
    string_constant_27 = STATIC_STRING("mmm-dd-yyyy");
    string_constant_28 = STATIC_STRING("dd-mmm-yyyy");
    string_constant_29 = STATIC_STRING("dd-mm-yy");
    string_constant_30 = STATIC_STRING("yy-mm-dd");
    string_constant_31 = STATIC_STRING("mm-dd-yy");
    string_constant_32 = STATIC_STRING("mm-yy");
    string_constant_33 = STATIC_STRING("mm-dd-hh-mm");
    string_constant_34 = STATIC_STRING("mmm-dd-hh-mm");
    string_constant_35 = STATIC_STRING("dd-hh-mm as an interval");
    string_constant_36 = STATIC_STRING("mm-ss as an interval");
    string_constant_37 = STATIC_STRING("mm-ss");
    string_constant_38 = STATIC_STRING("hh-mm-ss-am-pm");
    string_constant_39 = STATIC_STRING("hh-mm-ss as an interval");
    string_constant_40 = STATIC_STRING("hh-mm-ss");
    string_constant_41 = STATIC_STRING("hh-mm-am-pm");
    string_constant_42 = STATIC_STRING("hh-mm as an interval");
    string_constant_43 = STATIC_STRING("hh-mm");
    Qwrite_time_axis_label_format_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-TIME-AXIS-LABEL-FORMAT-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_time_axis_label_format_spec_from_slot,
	    STATIC_FUNCTION(write_time_axis_label_format_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtime_axis_label_format_spec,
	    SYMBOL_FUNCTION(Qwrite_time_axis_label_format_spec_from_slot),
	    Qslot_value_writer);
    Q2d_range_mode = STATIC_SYMBOL("2D-RANGE-MODE",AB_package);
    Qfixed = STATIC_SYMBOL("FIXED",AB_package);
    Qautoranging_on_data_window = 
	    STATIC_SYMBOL("AUTORANGING-ON-DATA-WINDOW",AB_package);
    Qautoranging_on_all_past_values = 
	    STATIC_SYMBOL("AUTORANGING-ON-ALL-PAST-VALUES",AB_package);
    list_constant_104 = STATIC_LIST((SI_Long)3L,Qfixed,
	    Qautoranging_on_data_window,Qautoranging_on_all_past_values);
    mutate_global_property(Q2d_range_mode,list_constant_104,
	    Qenumeration_grammar_category_members);
    string_constant_97 = 
	    STATIC_STRING("1n1n83oxy1p1m9k83-KFy1m9k830Py1m9k830*y1m9k83-iWy1m9k9l83-Y1y1n83oxy1o1m9k83-KFy1m9k830Py1m9k831Dy1m9k834ry83Ary1n83oxy1m9k83wJy");
    string_constant_98 = STATIC_STRING("83wJy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qvalues);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_97,
	    string_constant_98)));
    set_property_value_function(get_symbol_properties_function(Q2d_range_mode),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_36 = STATIC_CONS(Qmember,list_constant_104);
    define_type_specification_explicit_complex_type(Q2d_range_mode,
	    list_constant_36);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qnamed,Q2d_range_mode);
    Qhigh_water_marking = STATIC_SYMBOL("HIGH-WATER-MARKING",AB_package);
    n_2d_range_mode_evaluation_setter_1 = 
	    STATIC_FUNCTION(n_2d_range_mode_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Q2d_range_mode,
	    n_2d_range_mode_evaluation_setter_1);
    n_2d_range_mode_evaluation_getter_1 = 
	    STATIC_FUNCTION(n_2d_range_mode_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Q2d_range_mode,
	    n_2d_range_mode_evaluation_getter_1);
    string_constant_44 = STATIC_STRING("autoranging on all past values");
    string_constant_45 = STATIC_STRING("autoranging on data window");
    string_constant_46 = STATIC_STRING("fixed");
    Qwrite_2d_range_mode_from_slot = 
	    STATIC_SYMBOL("WRITE-2D-RANGE-MODE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_2d_range_mode_from_slot,
	    STATIC_FUNCTION(write_2d_range_mode_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Q2d_range_mode,
	    SYMBOL_FUNCTION(Qwrite_2d_range_mode_from_slot),
	    Qslot_value_writer);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    string_constant_47 = STATIC_STRING("unknown color specified");
    Qcompile_extra_value_grid_lines_for_slot = 
	    STATIC_SYMBOL("COMPILE-EXTRA-VALUE-GRID-LINES-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_extra_value_grid_lines_for_slot,
	    STATIC_FUNCTION(compile_extra_value_grid_lines_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qextra_value_grid_lines,
	    SYMBOL_FUNCTION(Qcompile_extra_value_grid_lines_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qextra_value_grid_lines,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_39 = STATIC_CONS(Qsequence,Qnil);
    list_constant_105 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_3,
	    list_constant_39);
    set_property_value_function(get_symbol_properties_function(Qextra_value_grid_lines),
	    Qtype_specification_simple_expansion,list_constant_105);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    list_constant_106 = STATIC_CONS(Qvalue,list_constant_81);
    list_constant_107 = STATIC_CONS(Qcolor,list_constant_47);
    list_constant_108 = STATIC_LIST((SI_Long)2L,list_constant_106,
	    list_constant_107);
    list_constant_109 = STATIC_LIST((SI_Long)2L,Qand,Qvalue);
    list_constant_110 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_108,list_constant_109);
    list_constant_111 = STATIC_LIST((SI_Long)3L,Qsequence,
	    list_constant_110,FIX((SI_Long)1L));
    list_constant_38 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_3,
	    list_constant_111);
    define_type_specification_explicit_complex_type(Qextra_value_grid_lines,
	    list_constant_38);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qnamed,Qextra_value_grid_lines);
    extra_value_grid_lines_evaluation_setter_1 = 
	    STATIC_FUNCTION(extra_value_grid_lines_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qextra_value_grid_lines,
	    extra_value_grid_lines_evaluation_setter_1);
    extra_value_grid_lines_evaluation_getter_1 = 
	    STATIC_FUNCTION(extra_value_grid_lines_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qextra_value_grid_lines,
	    extra_value_grid_lines_evaluation_getter_1);
    string_constant_48 = STATIC_STRING(", ");
    string_constant_49 = STATIC_STRING("at ");
    string_constant_50 = STATIC_STRING(" in ");
    Qwrite_extra_value_grid_lines_from_slot = 
	    STATIC_SYMBOL("WRITE-EXTRA-VALUE-GRID-LINES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_extra_value_grid_lines_from_slot,
	    STATIC_FUNCTION(write_extra_value_grid_lines_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qextra_value_grid_lines,
	    SYMBOL_FUNCTION(Qwrite_extra_value_grid_lines_from_slot),
	    Qslot_value_writer);
    string_constant_51 = 
	    STATIC_STRING("Must specify between 1 and 15 significant digits");
    Qsignificant_digit_spec = STATIC_SYMBOL("SIGNIFICANT-DIGIT-SPEC",
	    AB_package);
    Qcompile_significant_digit_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-SIGNIFICANT-DIGIT-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_significant_digit_spec_for_slot,
	    STATIC_FUNCTION(compile_significant_digit_spec_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qsignificant_digit_spec,
	    SYMBOL_FUNCTION(Qcompile_significant_digit_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qsignificant_digit_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qsignificant_digit_spec),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qsignificant_digit_spec,
	    Qinteger);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qnamed,Qsignificant_digit_spec);
    significant_digit_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(significant_digit_spec_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qsignificant_digit_spec,
	    significant_digit_spec_evaluation_setter_1);
    significant_digit_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(significant_digit_spec_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsignificant_digit_spec,
	    significant_digit_spec_evaluation_getter_1);
    Qwrite_significant_digit_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-SIGNIFICANT-DIGIT-SPEC-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_significant_digit_spec_from_slot,
	    STATIC_FUNCTION(write_significant_digit_spec_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qsignificant_digit_spec,
	    SYMBOL_FUNCTION(Qwrite_significant_digit_spec_from_slot),
	    Qslot_value_writer);
    string_constant_52 = 
	    STATIC_STRING("Must specify a range slack of 0 to 100 percent");
    Qrange_slack_spec = STATIC_SYMBOL("RANGE-SLACK-SPEC",AB_package);
    Qcompile_range_slack_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-RANGE-SLACK-SPEC-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_range_slack_spec_for_slot,
	    STATIC_FUNCTION(compile_range_slack_spec_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qrange_slack_spec,
	    SYMBOL_FUNCTION(Qcompile_range_slack_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qrange_slack_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qrange_slack_spec),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qrange_slack_spec,
	    Qinteger);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qnamed,Qrange_slack_spec);
    range_slack_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(range_slack_spec_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qrange_slack_spec,
	    range_slack_spec_evaluation_setter_1);
    range_slack_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(range_slack_spec_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qrange_slack_spec,
	    range_slack_spec_evaluation_getter_1);
    Qwrite_range_slack_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-RANGE-SLACK-SPEC-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_range_slack_spec_from_slot,
	    STATIC_FUNCTION(write_range_slack_spec_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qrange_slack_spec,
	    SYMBOL_FUNCTION(Qwrite_range_slack_spec_from_slot),
	    Qslot_value_writer);
    string_constant_53 = 
	    STATIC_STRING("Must specify between 0 and 50 grid lines per label");
    Qgrid_line_ratio = STATIC_SYMBOL("GRID-LINE-RATIO",AB_package);
    Qcompile_grid_line_ratio_for_slot = 
	    STATIC_SYMBOL("COMPILE-GRID-LINE-RATIO-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_grid_line_ratio_for_slot,
	    STATIC_FUNCTION(compile_grid_line_ratio_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qgrid_line_ratio,
	    SYMBOL_FUNCTION(Qcompile_grid_line_ratio_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgrid_line_ratio,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qgrid_line_ratio),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qgrid_line_ratio,Qinteger);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qnamed,Qgrid_line_ratio);
    grid_line_ratio_evaluation_setter_1 = 
	    STATIC_FUNCTION(grid_line_ratio_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgrid_line_ratio,
	    grid_line_ratio_evaluation_setter_1);
    grid_line_ratio_evaluation_getter_1 = 
	    STATIC_FUNCTION(grid_line_ratio_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgrid_line_ratio,
	    grid_line_ratio_evaluation_getter_1);
    Qwrite_grid_line_ratio_from_slot = 
	    STATIC_SYMBOL("WRITE-GRID-LINE-RATIO-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_grid_line_ratio_from_slot,
	    STATIC_FUNCTION(write_grid_line_ratio_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qgrid_line_ratio,
	    SYMBOL_FUNCTION(Qwrite_grid_line_ratio_from_slot),
	    Qslot_value_writer);
    string_constant_99 = 
	    STATIC_STRING("1o1m83-FIy83lcy1n83-FIy1m9k83Ary83-Nfy1m83-90y83=Qy1n83-90y1u83=Qy1m9k83vy1m9k83=Fy1m9k83Dmy1m9k83-oy1m9k837my1m9k831Dy1m9k839iy");
    string_constant_100 = STATIC_STRING("1m9k9l831Ny1n83-aXylu");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_99,
	    string_constant_100)));
    Qinterval_with_granularity = STATIC_SYMBOL("INTERVAL-WITH-GRANULARITY",
	    AB_package);
    Qdisplay_interval = STATIC_SYMBOL("DISPLAY-INTERVAL",AB_package);
    Qquantity_interval = STATIC_SYMBOL("QUANTITY-INTERVAL",AB_package);
    Qplot_update_interval_spec = STATIC_SYMBOL("PLOT-UPDATE-INTERVAL-SPEC",
	    AB_package);
    Qcompile_plot_update_interval_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-PLOT-UPDATE-INTERVAL-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_plot_update_interval_spec_for_slot,
	    STATIC_FUNCTION(compile_plot_update_interval_spec_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qplot_update_interval_spec,
	    SYMBOL_FUNCTION(Qcompile_plot_update_interval_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qplot_update_interval_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_37 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)20L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)24L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)27L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)32L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)33L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)37L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)39L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)40L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)41L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)42L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)44L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)54L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)55L,(SI_Long)57344L);
    Qwrite_plot_update_interval_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-PLOT-UPDATE-INTERVAL-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_plot_update_interval_spec_from_slot,
	    STATIC_FUNCTION(write_plot_update_interval_spec_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qplot_update_interval_spec,
	    SYMBOL_FUNCTION(Qwrite_plot_update_interval_spec_from_slot),
	    Qslot_value_writer);
    Qcompute_automatically = STATIC_SYMBOL("COMPUTE-AUTOMATICALLY",AB_package);
    string_constant_54 = 
	    STATIC_STRING("Must specify interval of at least 1 second.");
    Qtrend_chart_scroll_interval = 
	    STATIC_SYMBOL("TREND-CHART-SCROLL-INTERVAL",AB_package);
    Qcompile_trend_chart_scroll_interval_for_slot = 
	    STATIC_SYMBOL("COMPILE-TREND-CHART-SCROLL-INTERVAL-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_trend_chart_scroll_interval_for_slot,
	    STATIC_FUNCTION(compile_trend_chart_scroll_interval_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtrend_chart_scroll_interval,
	    SYMBOL_FUNCTION(Qcompile_trend_chart_scroll_interval_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtrend_chart_scroll_interval,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qtrend_chart_scroll_interval),
	    Qtype_specification_simple_expansion,list_constant_22);
    Qscroll_interval_type = STATIC_SYMBOL("SCROLL-INTERVAL-TYPE",AB_package);
    list_constant_112 = STATIC_LIST_STAR((SI_Long)3L,Qmember,Qautomatic,
	    list_constant_62);
    list_constant_113 = STATIC_LIST((SI_Long)2L,Qscroll_interval_type,
	    list_constant_112);
    list_constant_114 = STATIC_CONS(Qinterval,list_constant_76);
    list_constant_115 = STATIC_LIST((SI_Long)2L,list_constant_113,
	    list_constant_114);
    list_constant_116 = STATIC_LIST((SI_Long)2L,Qand,Qscroll_interval_type);
    list_constant_44 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_115,list_constant_116);
    define_type_specification_explicit_complex_type(Qtrend_chart_scroll_interval,
	    list_constant_44);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtrend_chart_scroll_interval);
    array_constant_38 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)11L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)18L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)23L,(SI_Long)57344L);
    trend_chart_scroll_interval_evaluation_setter_1 = 
	    STATIC_FUNCTION(trend_chart_scroll_interval_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtrend_chart_scroll_interval,
	    trend_chart_scroll_interval_evaluation_setter_1);
    trend_chart_scroll_interval_evaluation_getter_1 = 
	    STATIC_FUNCTION(trend_chart_scroll_interval_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtrend_chart_scroll_interval,
	    trend_chart_scroll_interval_evaluation_getter_1);
    Qwrite_trend_chart_scroll_interval_from_slot = 
	    STATIC_SYMBOL("WRITE-TREND-CHART-SCROLL-INTERVAL-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_trend_chart_scroll_interval_from_slot,
	    STATIC_FUNCTION(write_trend_chart_scroll_interval_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtrend_chart_scroll_interval,
	    SYMBOL_FUNCTION(Qwrite_trend_chart_scroll_interval_from_slot),
	    Qslot_value_writer);
    Qtime_axis_base_line_visible_qm = 
	    STATIC_SYMBOL("TIME-AXIS-BASE-LINE-VISIBLE\?",AB_package);
    Qbaseline_visible_qm = STATIC_SYMBOL("BASELINE-VISIBLE\?",AB_package);
    Qslot_component_alias = STATIC_SYMBOL("SLOT-COMPONENT-ALIAS",AB_package);
    mutate_global_property(Qtime_axis_base_line_visible_qm,
	    Qbaseline_visible_qm,Qslot_component_alias);
    Qslot_component_pretty_name = 
	    STATIC_SYMBOL("SLOT-COMPONENT-PRETTY-NAME",AB_package);
    Qtime_axis = STATIC_SYMBOL("TIME-AXIS",AB_package);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qbaseline_visible_qm),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qtime_axis_base_line_visible_qm);
    mutate_global_property(Qbaseline_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qcolor_for_time_axis_base_line = 
	    STATIC_SYMBOL("COLOR-FOR-TIME-AXIS-BASE-LINE",AB_package);
    Qbaseline_color = STATIC_SYMBOL("BASELINE-COLOR",AB_package);
    mutate_global_property(Qcolor_for_time_axis_base_line,Qbaseline_color,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qbaseline_color),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qcolor_for_time_axis_base_line);
    mutate_global_property(Qbaseline_color,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qcolor_for_time_grid_lines = STATIC_SYMBOL("COLOR-FOR-TIME-GRID-LINES",
	    AB_package);
    Qgrid_line_color = STATIC_SYMBOL("GRID-LINE-COLOR",AB_package);
    mutate_global_property(Qcolor_for_time_grid_lines,Qgrid_line_color,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgrid_line_color),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qcolor_for_time_grid_lines);
    mutate_global_property(Qgrid_line_color,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtime_axis_label_format = STATIC_SYMBOL("TIME-AXIS-LABEL-FORMAT",
	    AB_package);
    Qtime_format = STATIC_SYMBOL("TIME-FORMAT",AB_package);
    mutate_global_property(Qtime_axis_label_format,Qtime_format,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtime_format),
	    Qslot_component_pretty_name),Qtime_axis,Qtime_axis_label_format);
    mutate_global_property(Qtime_format,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qlabel_alignment = STATIC_SYMBOL("LABEL-ALIGNMENT",AB_package);
    mutate_global_property(Qtime_axis_label_alignment,Qlabel_alignment,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlabel_alignment),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qtime_axis_label_alignment);
    mutate_global_property(Qlabel_alignment,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtime_axis_absolute_labels_visible_qm = 
	    STATIC_SYMBOL("TIME-AXIS-ABSOLUTE-LABELS-VISIBLE\?",AB_package);
    Qabsolute_labels_visible_qm = 
	    STATIC_SYMBOL("ABSOLUTE-LABELS-VISIBLE\?",AB_package);
    mutate_global_property(Qtime_axis_absolute_labels_visible_qm,
	    Qabsolute_labels_visible_qm,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qabsolute_labels_visible_qm),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qtime_axis_absolute_labels_visible_qm);
    mutate_global_property(Qabsolute_labels_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtime_axis_relative_labels_visible_qm = 
	    STATIC_SYMBOL("TIME-AXIS-RELATIVE-LABELS-VISIBLE\?",AB_package);
    Qrelative_labels_visible_qm = 
	    STATIC_SYMBOL("RELATIVE-LABELS-VISIBLE\?",AB_package);
    mutate_global_property(Qtime_axis_relative_labels_visible_qm,
	    Qrelative_labels_visible_qm,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrelative_labels_visible_qm),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qtime_axis_relative_labels_visible_qm);
    mutate_global_property(Qrelative_labels_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtime_axis_tickmark_frequency = 
	    STATIC_SYMBOL("TIME-AXIS-TICKMARK-FREQUENCY",AB_package);
    Qlabel_frequency = STATIC_SYMBOL("LABEL-FREQUENCY",AB_package);
    mutate_global_property(Qtime_axis_tickmark_frequency,Qlabel_frequency,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlabel_frequency),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qtime_axis_tickmark_frequency);
    mutate_global_property(Qlabel_frequency,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qcolor_for_time_tickmarks = STATIC_SYMBOL("COLOR-FOR-TIME-TICKMARKS",
	    AB_package);
    Qlabel_color = STATIC_SYMBOL("LABEL-COLOR",AB_package);
    mutate_global_property(Qcolor_for_time_tickmarks,Qlabel_color,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlabel_color),
	    Qslot_component_pretty_name),Qtime_axis,Qcolor_for_time_tickmarks);
    mutate_global_property(Qlabel_color,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qratio_of_grid_lines_to_time_axis_tickmarks = 
	    STATIC_SYMBOL("RATIO-OF-GRID-LINES-TO-TIME-AXIS-TICKMARKS",
	    AB_package);
    Qgrid_lines_per_label = STATIC_SYMBOL("GRID-LINES-PER-LABEL",AB_package);
    mutate_global_property(Qratio_of_grid_lines_to_time_axis_tickmarks,
	    Qgrid_lines_per_label,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgrid_lines_per_label),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qratio_of_grid_lines_to_time_axis_tickmarks);
    mutate_global_property(Qgrid_lines_per_label,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtime_axis_update_interval = STATIC_SYMBOL("TIME-AXIS-UPDATE-INTERVAL",
	    AB_package);
    Qdisplay_update_interval = STATIC_SYMBOL("DISPLAY-UPDATE-INTERVAL",
	    AB_package);
    mutate_global_property(Qtime_axis_update_interval,
	    Qdisplay_update_interval,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdisplay_update_interval),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qtime_axis_update_interval);
    mutate_global_property(Qdisplay_update_interval,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtime_axis_jump_scroll_qm = STATIC_SYMBOL("TIME-AXIS-JUMP-SCROLL\?",
	    AB_package);
    Qjump_scroll_qm = STATIC_SYMBOL("JUMP-SCROLL\?",AB_package);
    mutate_global_property(Qtime_axis_jump_scroll_qm,Qjump_scroll_qm,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjump_scroll_qm),
	    Qslot_component_pretty_name),Qtime_axis,Qtime_axis_jump_scroll_qm);
    mutate_global_property(Qjump_scroll_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtime_axis_scroll_interval = STATIC_SYMBOL("TIME-AXIS-SCROLL-INTERVAL",
	    AB_package);
    Qjump_scroll_interval = STATIC_SYMBOL("JUMP-SCROLL-INTERVAL",AB_package);
    mutate_global_property(Qtime_axis_scroll_interval,
	    Qjump_scroll_interval,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjump_scroll_interval),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qtime_axis_scroll_interval);
    mutate_global_property(Qjump_scroll_interval,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtime_grid_lines_visible_qm = 
	    STATIC_SYMBOL("TIME-GRID-LINES-VISIBLE\?",AB_package);
    Qgrid_lines_visible_qm = STATIC_SYMBOL("GRID-LINES-VISIBLE\?",AB_package);
    mutate_global_property(Qtime_grid_lines_visible_qm,
	    Qgrid_lines_visible_qm,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgrid_lines_visible_qm),
	    Qslot_component_pretty_name),Qtime_axis,
	    Qtime_grid_lines_visible_qm);
    mutate_global_property(Qgrid_lines_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qcomponent_type = STATIC_SYMBOL("COMPONENT-TYPE",AB_package);
    Qsubtype = STATIC_SYMBOL("SUBTYPE",AB_package);
    list_constant_118 = STATIC_LIST((SI_Long)2L,Qsubtype,Qcomponent_type);
    list_constant_119 = STATIC_LIST((SI_Long)2L,Qcomponent_type,Qtime_axis);
    Qcomponent_group_header = STATIC_SYMBOL("COMPONENT-GROUP-HEADER",
	    AB_package);
    list_constant_120 = STATIC_LIST((SI_Long)2L,Qtype,Qcomponent_group_header);
    Qdo_not_identify_in_attribute_tables = 
	    STATIC_SYMBOL("DO-NOT-IDENTIFY-IN-ATTRIBUTE-TABLES",AB_package);
    list_constant_117 = STATIC_CONS(Qt,Qnil);
    list_constant_121 = STATIC_CONS(Qdo_not_identify_in_attribute_tables,
	    list_constant_117);
    Qnot_user_editable = STATIC_SYMBOL("NOT-USER-EDITABLE",AB_package);
    list_constant_122 = STATIC_CONS(Qnot_user_editable,list_constant_117);
    list_constant_145 = STATIC_LIST((SI_Long)5L,list_constant_118,
	    list_constant_119,list_constant_120,list_constant_121,
	    list_constant_122);
    Qdata_window_time_span = STATIC_SYMBOL("DATA-WINDOW-TIME-SPAN",AB_package);
    list_constant_123 = STATIC_CONS(FIX((SI_Long)300L),Qseconds);
    list_constant_146 = STATIC_LIST((SI_Long)2L,Qlength,list_constant_123);
    list_constant_125 = STATIC_LIST((SI_Long)2L,Qsubtype,Qtype);
    list_constant_124 = STATIC_CONS(Q2d_time_span_spec,Qnil);
    list_constant_126 = STATIC_CONS(Qtype,list_constant_124);
    list_constant_147 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_126);
    Qtotal_time_span = STATIC_SYMBOL("TOTAL-TIME-SPAN",AB_package);
    list_constant_127 = STATIC_CONS(Q2d_total_time_span_spec,Qnil);
    list_constant_128 = STATIC_CONS(Qtype,list_constant_127);
    list_constant_148 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_128);
    Qend_time = STATIC_SYMBOL("END-TIME",AB_package);
    list_constant_129 = STATIC_CONS(Q2d_end_time_spec,Qnil);
    list_constant_130 = STATIC_CONS(Qtype,list_constant_129);
    list_constant_149 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_130);
    list_constant_131 = STATIC_LIST((SI_Long)2L,Qtype,Qdisplay_interval);
    list_constant_150 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_131);
    Qyes_or_no = STATIC_SYMBOL("YES-OR-NO",AB_package);
    list_constant_132 = STATIC_LIST((SI_Long)2L,Qtype,Qyes_or_no);
    list_constant_151 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_132);
    list_constant_133 = STATIC_CONS(Qtrend_chart_scroll_interval,Qnil);
    list_constant_134 = STATIC_CONS(Qtype,list_constant_133);
    list_constant_152 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_134);
    list_constant_135 = STATIC_CONS(Q2d_time_axis_tickmark_frequency_spec,
	    Qnil);
    list_constant_136 = STATIC_CONS(Qtype,list_constant_135);
    list_constant_153 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_136);
    list_constant_137 = STATIC_CONS(Qtime_axis_label_alignment,Qnil);
    list_constant_138 = STATIC_CONS(Qtype,list_constant_137);
    list_constant_154 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_138);
    list_constant_139 = STATIC_CONS(Qtime_axis_label_format_spec,Qnil);
    list_constant_140 = STATIC_CONS(Qtype,list_constant_139);
    list_constant_155 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_140);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    list_constant_141 = STATIC_CONS(Qextant_color_or_metacolor,Qnil);
    list_constant_142 = STATIC_CONS(Qtype,list_constant_141);
    list_constant_156 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_142);
    Qgray = STATIC_SYMBOL("GRAY",AB_package);
    list_constant_143 = STATIC_CONS(Qgrid_line_ratio,Qnil);
    list_constant_144 = STATIC_CONS(Qtype,list_constant_143);
    list_constant_157 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_144);
    Qtime_axis_names = STATIC_SYMBOL("TIME-AXIS-NAMES",AB_package);
    Qcompound_type_descriptor = STATIC_SYMBOL("COMPOUND-TYPE-DESCRIPTOR",
	    AB_package);
    temp = make_slot_component_descriptor(Qcomponent_type,Nil,
	    list_constant_145);
    temp_1 = make_slot_component_descriptor(Qdata_window_time_span,
	    make_frame_like_category_default(3,Q2d_time_span_spec,
	    Qinterval,list_constant_146),list_constant_147);
    temp_2 = make_slot_component_descriptor(Qtotal_time_span,
	    make_frame_like_category_default(3,Q2d_total_time_span_spec,
	    Qdata_window,Qnil),list_constant_148);
    temp_3 = make_slot_component_descriptor(Qend_time,
	    make_frame_like_category_default(3,Q2d_end_time_spec,
	    Qlast_sample,Qnil),list_constant_149);
    temp_4 = make_slot_component_descriptor(Qtime_axis_update_interval,
	    FIX((SI_Long)2L),list_constant_150);
    temp_5 = make_slot_component_descriptor(Qtime_axis_jump_scroll_qm,Qt,
	    list_constant_151);
    temp_6 = make_slot_component_descriptor(Qtime_axis_scroll_interval,
	    Qnil,list_constant_152);
    temp_7 = 
	    make_slot_component_descriptor(Qtime_axis_absolute_labels_visible_qm,
	    Qt,list_constant_151);
    temp_8 = 
	    make_slot_component_descriptor(Qtime_axis_relative_labels_visible_qm,
	    Qnil,list_constant_151);
    temp_9 = make_slot_component_descriptor(Qtime_axis_tickmark_frequency,
	    make_frame_like_category_default(3,
	    Q2d_time_axis_tickmark_frequency_spec,Qsynchronized,Qnil),
	    list_constant_153);
    temp_10 = make_slot_component_descriptor(Qtime_axis_label_alignment,
	    Qright,list_constant_154);
    temp_11 = make_slot_component_descriptor(Qtime_axis_label_format,
	    Qhh_mm_ss_am_pm,list_constant_155);
    temp_12 = make_slot_component_descriptor(Qcolor_for_time_tickmarks,
	    Qblack,list_constant_156);
    temp_13 = make_slot_component_descriptor(Qtime_grid_lines_visible_qm,
	    Qt,list_constant_151);
    temp_14 = make_slot_component_descriptor(Qcolor_for_time_grid_lines,
	    Qgray,list_constant_156);
    temp_15 = 
	    make_slot_component_descriptor(Qratio_of_grid_lines_to_time_axis_tickmarks,
	    FIX((SI_Long)1L),list_constant_157);
    temp_16 = 
	    make_slot_component_descriptor(Qtime_axis_base_line_visible_qm,
	    Qt,list_constant_151);
    mutate_global_property(Qtime_axis,
	    make_compound_type_descriptor(Qtime_axis,Nil,list(18,temp,
	    temp_1,temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,temp_9,
	    temp_10,temp_11,temp_12,temp_13,temp_14,temp_15,temp_16,
	    make_slot_component_descriptor(Qcolor_for_time_axis_base_line,
	    Qblack,list_constant_156)),Qtime_axis_names),
	    Qcompound_type_descriptor);
    Qvalue_axis_label_significant_digits = 
	    STATIC_SYMBOL("VALUE-AXIS-LABEL-SIGNIFICANT-DIGITS",AB_package);
    Qsignificant_digits_for_labels = 
	    STATIC_SYMBOL("SIGNIFICANT-DIGITS-FOR-LABELS",AB_package);
    mutate_global_property(Qvalue_axis_label_significant_digits,
	    Qsignificant_digits_for_labels,Qslot_component_alias);
    Qvalue_axis = STATIC_SYMBOL("VALUE-AXIS",AB_package);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsignificant_digits_for_labels),
	    Qslot_component_pretty_name),Qvalue_axis,
	    Qvalue_axis_label_significant_digits);
    mutate_global_property(Qsignificant_digits_for_labels,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qcolor_for_value_axis_tickmarks = 
	    STATIC_SYMBOL("COLOR-FOR-VALUE-AXIS-TICKMARKS",AB_package);
    mutate_global_property(Qcolor_for_value_axis_tickmarks,Qlabel_color,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlabel_color),
	    Qslot_component_pretty_name),Qvalue_axis,
	    Qcolor_for_value_axis_tickmarks);
    mutate_global_property(Qlabel_color,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qvalue_axis_tickmark_frequency = 
	    STATIC_SYMBOL("VALUE-AXIS-TICKMARK-FREQUENCY",AB_package);
    mutate_global_property(Qvalue_axis_tickmark_frequency,Qlabel_frequency,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlabel_frequency),
	    Qslot_component_pretty_name),Qvalue_axis,
	    Qvalue_axis_tickmark_frequency);
    mutate_global_property(Qlabel_frequency,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qratio_of_grid_lines_to_value_axis_tickmarks = 
	    STATIC_SYMBOL("RATIO-OF-GRID-LINES-TO-VALUE-AXIS-TICKMARKS",
	    AB_package);
    mutate_global_property(Qratio_of_grid_lines_to_value_axis_tickmarks,
	    Qgrid_lines_per_label,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgrid_lines_per_label),
	    Qslot_component_pretty_name),Qvalue_axis,
	    Qratio_of_grid_lines_to_value_axis_tickmarks);
    mutate_global_property(Qgrid_lines_per_label,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qvalue_axis_bounds = STATIC_SYMBOL("VALUE-AXIS-BOUNDS",AB_package);
    Qrange_bounds = STATIC_SYMBOL("RANGE-BOUNDS",AB_package);
    mutate_global_property(Qvalue_axis_bounds,Qrange_bounds,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrange_bounds),
	    Qslot_component_pretty_name),Qvalue_axis,Qvalue_axis_bounds);
    mutate_global_property(Qrange_bounds,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qvalue_axis_range_mode = STATIC_SYMBOL("VALUE-AXIS-RANGE-MODE",AB_package);
    Qrange_mode = STATIC_SYMBOL("RANGE-MODE",AB_package);
    mutate_global_property(Qvalue_axis_range_mode,Qrange_mode,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrange_mode),
	    Qslot_component_pretty_name),Qvalue_axis,Qvalue_axis_range_mode);
    mutate_global_property(Qrange_mode,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qcolor_for_value_axis_base_line = 
	    STATIC_SYMBOL("COLOR-FOR-VALUE-AXIS-BASE-LINE",AB_package);
    mutate_global_property(Qcolor_for_value_axis_base_line,Qbaseline_color,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qbaseline_color),
	    Qslot_component_pretty_name),Qvalue_axis,
	    Qcolor_for_value_axis_base_line);
    mutate_global_property(Qbaseline_color,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qvalue_axis_labels_visible_qm = 
	    STATIC_SYMBOL("VALUE-AXIS-LABELS-VISIBLE\?",AB_package);
    Qlabels_visible_qm = STATIC_SYMBOL("LABELS-VISIBLE\?",AB_package);
    mutate_global_property(Qvalue_axis_labels_visible_qm,
	    Qlabels_visible_qm,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlabels_visible_qm),
	    Qslot_component_pretty_name),Qvalue_axis,
	    Qvalue_axis_labels_visible_qm);
    mutate_global_property(Qlabels_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qvalue_axis_base_line_visible_qm = 
	    STATIC_SYMBOL("VALUE-AXIS-BASE-LINE-VISIBLE\?",AB_package);
    mutate_global_property(Qvalue_axis_base_line_visible_qm,
	    Qbaseline_visible_qm,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qbaseline_visible_qm),
	    Qslot_component_pretty_name),Qvalue_axis,
	    Qvalue_axis_base_line_visible_qm);
    mutate_global_property(Qbaseline_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qshow_value_labels_as_percent_qm = 
	    STATIC_SYMBOL("SHOW-VALUE-LABELS-AS-PERCENT\?",AB_package);
    Qshow_labels_as_percent_qm = STATIC_SYMBOL("SHOW-LABELS-AS-PERCENT\?",
	    AB_package);
    mutate_global_property(Qshow_value_labels_as_percent_qm,
	    Qshow_labels_as_percent_qm,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qshow_labels_as_percent_qm),
	    Qslot_component_pretty_name),Qvalue_axis,
	    Qshow_value_labels_as_percent_qm);
    mutate_global_property(Qshow_labels_as_percent_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qcolor_for_value_grid_lines = 
	    STATIC_SYMBOL("COLOR-FOR-VALUE-GRID-LINES",AB_package);
    mutate_global_property(Qcolor_for_value_grid_lines,Qgrid_line_color,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgrid_line_color),
	    Qslot_component_pretty_name),Qvalue_axis,
	    Qcolor_for_value_grid_lines);
    mutate_global_property(Qgrid_line_color,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qvalue_grid_lines_visible_qm = 
	    STATIC_SYMBOL("VALUE-GRID-LINES-VISIBLE\?",AB_package);
    mutate_global_property(Qvalue_grid_lines_visible_qm,
	    Qgrid_lines_visible_qm,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgrid_lines_visible_qm),
	    Qslot_component_pretty_name),Qvalue_axis,
	    Qvalue_grid_lines_visible_qm);
    mutate_global_property(Qgrid_lines_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qextra_grid_lines = STATIC_SYMBOL("EXTRA-GRID-LINES",AB_package);
    mutate_global_property(Qextra_value_grid_lines,Qextra_grid_lines,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qextra_grid_lines),
	    Qslot_component_pretty_name),Qvalue_axis,Qextra_value_grid_lines);
    mutate_global_property(Qextra_grid_lines,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qvalue_axis_names = STATIC_SYMBOL("VALUE-AXIS-NAMES",AB_package);
    Qnames = STATIC_SYMBOL("NAMES",AB_package);
    mutate_global_property(Qvalue_axis_names,Qnames,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnames),
	    Qslot_component_pretty_name),Qvalue_axis,Qvalue_axis_names);
    mutate_global_property(Qnames,slot_component_pretty_name_new_value,
	    Qslot_component_pretty_name);
    Qvalue_axis_range_slack = STATIC_SYMBOL("VALUE-AXIS-RANGE-SLACK",
	    AB_package);
    Qrange_slack_percentage = STATIC_SYMBOL("RANGE-SLACK-PERCENTAGE",
	    AB_package);
    mutate_global_property(Qvalue_axis_range_slack,Qrange_slack_percentage,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrange_slack_percentage),
	    Qslot_component_pretty_name),Qvalue_axis,Qvalue_axis_range_slack);
    mutate_global_property(Qrange_slack_percentage,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    list_constant_159 = STATIC_LIST((SI_Long)2L,Qcomponent_type,Qvalue_axis);
    list_constant_158 = STATIC_CONS(list_constant_122,Qnil);
    list_constant_160 = STATIC_LIST_STAR((SI_Long)3L,list_constant_120,
	    list_constant_121,list_constant_158);
    list_constant_179 = STATIC_LIST_STAR((SI_Long)3L,list_constant_118,
	    list_constant_159,list_constant_160);
    string_constant_101 = STATIC_STRING("83-GMy");
    string_constant_102 = 
	    STATIC_STRING("1n1n83b4y831Ty83-GLy1m8p83-ky1m83WXy8k");
    Qchart_element_uid = STATIC_SYMBOL("CHART-ELEMENT-UID",AB_package);
    Qvalue_axis_visible_qm = STATIC_SYMBOL("VALUE-AXIS-VISIBLE\?",AB_package);
    Qnot_editable_in_default = STATIC_SYMBOL("NOT-EDITABLE-IN-DEFAULT",
	    AB_package);
    list_constant_161 = STATIC_CONS(Qnot_editable_in_default,
	    list_constant_117);
    list_constant_180 = STATIC_LIST((SI_Long)3L,list_constant_125,
	    list_constant_132,list_constant_161);
    list_constant_162 = STATIC_CONS(Qvalue_axis_position,Qnil);
    list_constant_163 = STATIC_CONS(Qtype,list_constant_162);
    list_constant_181 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_163);
    list_constant_164 = STATIC_CONS(Q2d_range_mode,Qnil);
    list_constant_165 = STATIC_CONS(Qtype,list_constant_164);
    list_constant_182 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_165);
    list_constant_166 = STATIC_CONS(Q2d_value_axis_bounds_spec,Qnil);
    list_constant_167 = STATIC_CONS(Qtype,list_constant_166);
    list_constant_183 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_167);
    list_constant_168 = STATIC_CONS(Qrange_slack_spec,Qnil);
    list_constant_169 = STATIC_CONS(Qtype,list_constant_168);
    list_constant_184 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_169);
    list_constant_185 = STATIC_LIST((SI_Long)2L,Qcolor,Qblack);
    list_constant_170 = STATIC_CONS(Q2d_tickmark_label_color,Qnil);
    list_constant_171 = STATIC_CONS(Qtype,list_constant_170);
    list_constant_186 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_171);
    list_constant_172 = STATIC_CONS(Q2d_value_axis_tickmark_frequency_spec,
	    Qnil);
    list_constant_173 = STATIC_CONS(Qtype,list_constant_172);
    list_constant_187 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_173);
    list_constant_174 = STATIC_CONS(Qsignificant_digit_spec,Qnil);
    list_constant_175 = STATIC_CONS(Qtype,list_constant_174);
    list_constant_188 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_175);
    list_constant_176 = STATIC_CONS(Qextra_value_grid_lines,Qnil);
    list_constant_177 = STATIC_CONS(Qtype,list_constant_176);
    list_constant_189 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_177);
    Qvalue_axis_lower_bound_qm = STATIC_SYMBOL("VALUE-AXIS-LOWER-BOUND\?",
	    AB_package);
    Qinternal = STATIC_SYMBOL("INTERNAL",AB_package);
    list_constant_178 = STATIC_LIST((SI_Long)2L,Qsubtype,Qinternal);
    list_constant_190 = STATIC_CONS(list_constant_178,list_constant_158);
    Qvalue_axis_upper_bound_qm = STATIC_SYMBOL("VALUE-AXIS-UPPER-BOUND\?",
	    AB_package);
    Qvalue_axis_high_value = STATIC_SYMBOL("VALUE-AXIS-HIGH-VALUE",AB_package);
    Qvalue_axis_low_value = STATIC_SYMBOL("VALUE-AXIS-LOW-VALUE",AB_package);
    Qvalue_axis_last_sent_high_value = 
	    STATIC_SYMBOL("VALUE-AXIS-LAST-SENT-HIGH-VALUE",AB_package);
    Qvalue_axis_last_sent_low_value = 
	    STATIC_SYMBOL("VALUE-AXIS-LAST-SENT-LOW-VALUE",AB_package);
    temp = make_slot_component_descriptor(Qcomponent_type,Nil,
	    list_constant_179);
    temp_1 = regenerate_optimized_constant(string_constant_101);
    temp_1 = make_slot_component_descriptor(temp_1,Nil,
	    regenerate_optimized_constant(string_constant_102));
    temp_2 = make_slot_component_descriptor(Qchart_element_uid,Qnil,Qnil);
    temp_3 = make_slot_component_descriptor(Qvalue_axis_visible_qm,Qt,
	    list_constant_180);
    temp_4 = make_slot_component_descriptor(Qvalue_axis_position,Qright,
	    list_constant_181);
    temp_5 = make_slot_component_descriptor(Qvalue_axis_range_mode,
	    Qautomatic,list_constant_182);
    temp_6 = make_slot_component_descriptor(Qvalue_axis_bounds,
	    make_frame_like_category_default(3,Q2d_value_axis_bounds_spec,
	    Qnone,Qnil),list_constant_183);
    temp_7 = make_slot_component_descriptor(Qvalue_axis_range_slack,
	    FIX((SI_Long)10L),list_constant_184);
    temp_8 = make_slot_component_descriptor(Qvalue_axis_labels_visible_qm,
	    Qt,list_constant_151);
    temp_9 = 
	    make_slot_component_descriptor(Qcolor_for_value_axis_tickmarks,
	    make_frame_like_category_default(3,Q2d_tickmark_label_color,
	    Qabsolute,list_constant_185),list_constant_186);
    temp_10 = 
	    make_slot_component_descriptor(Qvalue_axis_tickmark_frequency,
	    make_frame_like_category_default(3,
	    Q2d_value_axis_tickmark_frequency_spec,Qautomatic,Qnil),
	    list_constant_187);
    temp_11 = 
	    make_slot_component_descriptor(Qshow_value_labels_as_percent_qm,
	    Qnil,list_constant_151);
    temp_12 = 
	    make_slot_component_descriptor(Qvalue_axis_label_significant_digits,
	    FIX((SI_Long)4L),list_constant_188);
    temp_13 = make_slot_component_descriptor(Qvalue_grid_lines_visible_qm,
	    Qt,list_constant_151);
    temp_14 = make_slot_component_descriptor(Qcolor_for_value_grid_lines,
	    Qgray,list_constant_156);
    temp_15 = 
	    make_slot_component_descriptor(Qratio_of_grid_lines_to_value_axis_tickmarks,
	    FIX((SI_Long)1L),list_constant_157);
    temp_16 = make_slot_component_descriptor(Qextra_value_grid_lines,Qnil,
	    list_constant_189);
    temp_17 = 
	    make_slot_component_descriptor(Qvalue_axis_base_line_visible_qm,
	    Qt,list_constant_151);
    temp_18 = 
	    make_slot_component_descriptor(Qcolor_for_value_axis_base_line,
	    Qblack,list_constant_156);
    temp_19 = make_slot_component_descriptor(Qvalue_axis_lower_bound_qm,
	    Qnil,list_constant_190);
    temp_20 = make_slot_component_descriptor(Qvalue_axis_upper_bound_qm,
	    Qnil,list_constant_190);
    temp_21 = make_slot_component_descriptor(Qvalue_axis_high_value,Qnil,
	    list_constant_190);
    temp_22 = make_slot_component_descriptor(Qvalue_axis_low_value,Qnil,
	    list_constant_190);
    temp_23 = 
	    make_slot_component_descriptor(Qvalue_axis_last_sent_high_value,
	    Qnil,list_constant_190);
    mutate_global_property(Qvalue_axis,
	    make_compound_type_descriptor(Qvalue_axis,T,list(25,temp,
	    temp_1,temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,temp_9,
	    temp_10,temp_11,temp_12,temp_13,temp_14,temp_15,temp_16,
	    temp_17,temp_18,temp_19,temp_20,temp_21,temp_22,temp_23,
	    make_slot_component_descriptor(Qvalue_axis_last_sent_low_value,
	    Qnil,list_constant_190)),Qvalue_axis_names),
	    Qcompound_type_descriptor);
    Qtrend_chart_legend_visible_qm = 
	    STATIC_SYMBOL("TREND-CHART-LEGEND-VISIBLE\?",AB_package);
    Qlegend_visible_qm = STATIC_SYMBOL("LEGEND-VISIBLE\?",AB_package);
    mutate_global_property(Qtrend_chart_legend_visible_qm,
	    Qlegend_visible_qm,Qslot_component_alias);
    Qtrend_chart_format = STATIC_SYMBOL("TREND-CHART-FORMAT",AB_package);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlegend_visible_qm),
	    Qslot_component_pretty_name),Qtrend_chart_format,
	    Qtrend_chart_legend_visible_qm);
    mutate_global_property(Qlegend_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtrend_chart_legend_color = STATIC_SYMBOL("TREND-CHART-LEGEND-COLOR",
	    AB_package);
    Qlegend_color = STATIC_SYMBOL("LEGEND-COLOR",AB_package);
    mutate_global_property(Qtrend_chart_legend_color,Qlegend_color,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlegend_color),
	    Qslot_component_pretty_name),Qtrend_chart_format,
	    Qtrend_chart_legend_color);
    mutate_global_property(Qlegend_color,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qlegend_position = STATIC_SYMBOL("LEGEND-POSITION",AB_package);
    mutate_global_property(Qtrend_chart_legend_position,Qlegend_position,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlegend_position),
	    Qslot_component_pretty_name),Qtrend_chart_format,
	    Qtrend_chart_legend_position);
    mutate_global_property(Qlegend_position,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtrend_chart_label_visible_qm = 
	    STATIC_SYMBOL("TREND-CHART-LABEL-VISIBLE\?",AB_package);
    Qtitle_visible_qm = STATIC_SYMBOL("TITLE-VISIBLE\?",AB_package);
    mutate_global_property(Qtrend_chart_label_visible_qm,Qtitle_visible_qm,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtitle_visible_qm),
	    Qslot_component_pretty_name),Qtrend_chart_format,
	    Qtrend_chart_label_visible_qm);
    mutate_global_property(Qtitle_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtrend_chart_label_position = 
	    STATIC_SYMBOL("TREND-CHART-LABEL-POSITION",AB_package);
    Qtitle_position = STATIC_SYMBOL("TITLE-POSITION",AB_package);
    mutate_global_property(Qtrend_chart_label_position,Qtitle_position,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtitle_position),
	    Qslot_component_pretty_name),Qtrend_chart_format,
	    Qtrend_chart_label_position);
    mutate_global_property(Qtitle_position,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qtrend_chart_label_color = STATIC_SYMBOL("TREND-CHART-LABEL-COLOR",
	    AB_package);
    Qtitle_color = STATIC_SYMBOL("TITLE-COLOR",AB_package);
    mutate_global_property(Qtrend_chart_label_color,Qtitle_color,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtitle_color),
	    Qslot_component_pretty_name),Qtrend_chart_format,
	    Qtrend_chart_label_color);
    mutate_global_property(Qtitle_color,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    list_constant_191 = STATIC_LIST((SI_Long)2L,Qcomponent_type,
	    Qtrend_chart_format);
    list_constant_196 = STATIC_LIST_STAR((SI_Long)3L,list_constant_118,
	    list_constant_191,list_constant_160);
    Qouter_border_visible_qm = STATIC_SYMBOL("OUTER-BORDER-VISIBLE\?",
	    AB_package);
    Qouter_border_color = STATIC_SYMBOL("OUTER-BORDER-COLOR",AB_package);
    Qouter_background_color = STATIC_SYMBOL("OUTER-BACKGROUND-COLOR",
	    AB_package);
    Qsmoke = STATIC_SYMBOL("SMOKE",AB_package);
    Qdata_window_border_visible_qm = 
	    STATIC_SYMBOL("DATA-WINDOW-BORDER-VISIBLE\?",AB_package);
    Qdata_window_border_color = STATIC_SYMBOL("DATA-WINDOW-BORDER-COLOR",
	    AB_package);
    Qdata_window_background_color = 
	    STATIC_SYMBOL("DATA-WINDOW-BACKGROUND-COLOR",AB_package);
    list_constant_192 = STATIC_CONS(Qtrend_chart_legend_color_spec,Qnil);
    list_constant_193 = STATIC_CONS(Qtype,list_constant_192);
    list_constant_197 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_193);
    list_constant_194 = STATIC_CONS(Qtrend_chart_legend_position,Qnil);
    list_constant_195 = STATIC_CONS(Qtype,list_constant_194);
    list_constant_198 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_195);
    Qtrend_chart_format_names = STATIC_SYMBOL("TREND-CHART-FORMAT-NAMES",
	    AB_package);
    temp = make_slot_component_descriptor(Qcomponent_type,Nil,
	    list_constant_196);
    temp_1 = make_slot_component_descriptor(Qouter_border_visible_qm,Qt,
	    list_constant_151);
    temp_2 = make_slot_component_descriptor(Qouter_border_color,Qblack,
	    list_constant_156);
    temp_3 = make_slot_component_descriptor(Qouter_background_color,Qsmoke,
	    list_constant_156);
    temp_4 = make_slot_component_descriptor(Qdata_window_border_visible_qm,
	    Qnil,list_constant_151);
    temp_5 = make_slot_component_descriptor(Qdata_window_border_color,
	    Qblack,list_constant_156);
    temp_6 = make_slot_component_descriptor(Qdata_window_background_color,
	    Qsmoke,list_constant_156);
    temp_7 = make_slot_component_descriptor(Qtrend_chart_legend_visible_qm,
	    Qt,list_constant_151);
    temp_8 = make_slot_component_descriptor(Qtrend_chart_legend_color,
	    make_frame_like_category_default(3,
	    Qtrend_chart_legend_color_spec,Qmatching,Qnil),list_constant_197);
    temp_9 = make_slot_component_descriptor(Qtrend_chart_legend_position,
	    Qbelow,list_constant_198);
    temp_10 = make_slot_component_descriptor(Qtrend_chart_label_visible_qm,
	    Qt,list_constant_151);
    temp_11 = make_slot_component_descriptor(Qtrend_chart_label_color,
	    Qblack,list_constant_156);
    mutate_global_property(Qtrend_chart_format,
	    make_compound_type_descriptor(Qtrend_chart_format,Nil,list(13,
	    temp,temp_1,temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,
	    temp_9,temp_10,temp_11,
	    make_slot_component_descriptor(Qtrend_chart_label_position,
	    Qabove,list_constant_198)),Qtrend_chart_format_names),
	    Qcompound_type_descriptor);
    Qpoint_visible_qm = STATIC_SYMBOL("POINT-VISIBLE\?",AB_package);
    Qmarkers_visible_qm = STATIC_SYMBOL("MARKERS-VISIBLE\?",AB_package);
    mutate_global_property(Qpoint_visible_qm,Qmarkers_visible_qm,
	    Qslot_component_alias);
    Qpoint_format = STATIC_SYMBOL("POINT-FORMAT",AB_package);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmarkers_visible_qm),
	    Qslot_component_pretty_name),Qpoint_format,Qpoint_visible_qm);
    mutate_global_property(Qmarkers_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qpoint_color = STATIC_SYMBOL("POINT-COLOR",AB_package);
    Qmarker_color = STATIC_SYMBOL("MARKER-COLOR",AB_package);
    mutate_global_property(Qpoint_color,Qmarker_color,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmarker_color),
	    Qslot_component_pretty_name),Qpoint_format,Qpoint_color);
    mutate_global_property(Qmarker_color,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qpoint_style = STATIC_SYMBOL("POINT-STYLE",AB_package);
    Qmarker_style = STATIC_SYMBOL("MARKER-STYLE",AB_package);
    mutate_global_property(Qpoint_style,Qmarker_style,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmarker_style),
	    Qslot_component_pretty_name),Qpoint_format,Qpoint_style);
    mutate_global_property(Qmarker_style,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qpoint_frequency = STATIC_SYMBOL("POINT-FREQUENCY",AB_package);
    Qmarker_frequency = STATIC_SYMBOL("MARKER-FREQUENCY",AB_package);
    mutate_global_property(Qpoint_frequency,Qmarker_frequency,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmarker_frequency),
	    Qslot_component_pretty_name),Qpoint_format,Qpoint_frequency);
    mutate_global_property(Qmarker_frequency,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qpoint_format_names = STATIC_SYMBOL("POINT-FORMAT-NAMES",AB_package);
    mutate_global_property(Qpoint_format_names,Qnames,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnames),
	    Qslot_component_pretty_name),Qpoint_format,Qpoint_format_names);
    mutate_global_property(Qnames,slot_component_pretty_name_new_value,
	    Qslot_component_pretty_name);
    list_constant_199 = STATIC_LIST((SI_Long)2L,Qcomponent_type,Qpoint_format);
    list_constant_205 = STATIC_LIST_STAR((SI_Long)3L,list_constant_118,
	    list_constant_199,list_constant_160);
    string_constant_103 = STATIC_STRING("83-94y");
    string_constant_104 = 
	    STATIC_STRING("1n1n83b4y831Ty83-93y1m8p83-ky1m83WXy8k");
    Qtriangle = STATIC_SYMBOL("TRIANGLE",AB_package);
    list_constant_206 = STATIC_LIST((SI_Long)2L,Qshape,Qtriangle);
    list_constant_200 = STATIC_CONS(Q2d_plot_marker_shape,Qnil);
    list_constant_201 = STATIC_CONS(Qtype,list_constant_200);
    list_constant_207 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_201);
    list_constant_202 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_208 = STATIC_CONS(Qnumber,list_constant_202);
    list_constant_203 = STATIC_CONS(Q2d_plot_marker_frequency,Qnil);
    list_constant_204 = STATIC_CONS(Qtype,list_constant_203);
    list_constant_209 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_204);
    temp = make_slot_component_descriptor(Qcomponent_type,Nil,
	    list_constant_205);
    temp_1 = regenerate_optimized_constant(string_constant_103);
    temp_1 = make_slot_component_descriptor(temp_1,Nil,
	    regenerate_optimized_constant(string_constant_104));
    temp_2 = make_slot_component_descriptor(Qchart_element_uid,Qnil,Qnil);
    temp_3 = make_slot_component_descriptor(Qpoint_visible_qm,Qnil,
	    list_constant_151);
    temp_4 = make_slot_component_descriptor(Qpoint_color,Qblack,
	    list_constant_156);
    temp_5 = make_slot_component_descriptor(Qpoint_style,
	    make_frame_like_category_default(3,Q2d_plot_marker_shape,
	    Qab_standard,list_constant_206),list_constant_207);
    mutate_global_property(Qpoint_format,
	    make_compound_type_descriptor(Qpoint_format,T,list(7,temp,
	    temp_1,temp_2,temp_3,temp_4,temp_5,
	    make_slot_component_descriptor(Qpoint_frequency,
	    make_frame_like_category_default(3,Q2d_plot_marker_frequency,
	    Qratio,list_constant_208),list_constant_209)),
	    Qpoint_format_names),Qcompound_type_descriptor);
    Qconnector_line_style = STATIC_SYMBOL("CONNECTOR-LINE-STYLE",AB_package);
    Qconnector_interpolation = STATIC_SYMBOL("CONNECTOR-INTERPOLATION",
	    AB_package);
    mutate_global_property(Qconnector_line_style,Qconnector_interpolation,
	    Qslot_component_alias);
    Qconnector_format = STATIC_SYMBOL("CONNECTOR-FORMAT",AB_package);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnector_interpolation),
	    Qslot_component_pretty_name),Qconnector_format,
	    Qconnector_line_style);
    mutate_global_property(Qconnector_interpolation,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qconnector_visible_qm = STATIC_SYMBOL("CONNECTOR-VISIBLE\?",AB_package);
    Qconnectors_visible_qm = STATIC_SYMBOL("CONNECTORS-VISIBLE\?",AB_package);
    mutate_global_property(Qconnector_visible_qm,Qconnectors_visible_qm,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnectors_visible_qm),
	    Qslot_component_pretty_name),Qconnector_format,
	    Qconnector_visible_qm);
    mutate_global_property(Qconnectors_visible_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qconnector_format_names = STATIC_SYMBOL("CONNECTOR-FORMAT-NAMES",
	    AB_package);
    mutate_global_property(Qconnector_format_names,Qnames,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnames),
	    Qslot_component_pretty_name),Qconnector_format,
	    Qconnector_format_names);
    mutate_global_property(Qnames,slot_component_pretty_name_new_value,
	    Qslot_component_pretty_name);
    list_constant_210 = STATIC_LIST((SI_Long)2L,Qcomponent_type,
	    Qconnector_format);
    list_constant_216 = STATIC_LIST_STAR((SI_Long)3L,list_constant_118,
	    list_constant_210,list_constant_160);
    string_constant_105 = STATIC_STRING("83t-y");
    string_constant_106 = 
	    STATIC_STRING("1n1n83b4y831Ty83t+y1m8p83-ky1m83WXy8k");
    Qconnector_line_color = STATIC_SYMBOL("CONNECTOR-LINE-COLOR",AB_package);
    list_constant_211 = STATIC_CONS(Q2d_line_style,Qnil);
    list_constant_212 = STATIC_CONS(Qtype,list_constant_211);
    list_constant_217 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_212);
    Qconnector_line_width = STATIC_SYMBOL("CONNECTOR-LINE-WIDTH",AB_package);
    list_constant_213 = STATIC_CONS(Qtype,list_constant_76);
    list_constant_218 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_213);
    Qconnector_shading_target = STATIC_SYMBOL("CONNECTOR-SHADING-TARGET",
	    AB_package);
    list_constant_214 = STATIC_CONS(Q2d_shading_target_spec,Qnil);
    list_constant_215 = STATIC_CONS(Qtype,list_constant_214);
    list_constant_219 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_215);
    temp = make_slot_component_descriptor(Qcomponent_type,Nil,
	    list_constant_216);
    temp_1 = regenerate_optimized_constant(string_constant_105);
    temp_1 = make_slot_component_descriptor(temp_1,Nil,
	    regenerate_optimized_constant(string_constant_106));
    temp_2 = make_slot_component_descriptor(Qchart_element_uid,Qnil,Qnil);
    temp_3 = make_slot_component_descriptor(Qconnector_visible_qm,Qt,
	    list_constant_151);
    temp_4 = make_slot_component_descriptor(Qconnector_line_color,Qblack,
	    list_constant_156);
    temp_5 = make_slot_component_descriptor(Qconnector_line_style,
	    Qinterpolated,list_constant_217);
    temp_6 = make_slot_component_descriptor(Qconnector_line_width,
	    FIX((SI_Long)1L),list_constant_218);
    mutate_global_property(Qconnector_format,
	    make_compound_type_descriptor(Qconnector_format,T,list(8,temp,
	    temp_1,temp_2,temp_3,temp_4,temp_5,temp_6,
	    make_slot_component_descriptor(Qconnector_shading_target,
	    make_frame_like_category_default(3,Q2d_shading_target_spec,
	    Qnone,Qnil),list_constant_219)),Qconnector_format_names),
	    Qcompound_type_descriptor);
    Qplot_names = STATIC_SYMBOL("PLOT-NAMES",AB_package);
    mutate_global_property(Qplot_names,Qnames,Qslot_component_alias);
    Qplot = STATIC_SYMBOL("PLOT",AB_package);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnames),
	    Qslot_component_pretty_name),Qplot,Qplot_names);
    mutate_global_property(Qnames,slot_component_pretty_name_new_value,
	    Qslot_component_pretty_name);
    list_constant_220 = STATIC_LIST((SI_Long)2L,Qcomponent_type,Qplot);
    list_constant_231 = STATIC_LIST_STAR((SI_Long)3L,list_constant_118,
	    list_constant_220,list_constant_160);
    string_constant_107 = STATIC_STRING("83-9=y");
    string_constant_108 = 
	    STATIC_STRING("1n1n83b4y831Ty833Wy1m8p83-ky1m83WXy8k");
    Qplot_use_local_history_qm = STATIC_SYMBOL("PLOT-USE-LOCAL-HISTORY\?",
	    AB_package);
    Qplot_axis = STATIC_SYMBOL("PLOT-AXIS",AB_package);
    Qreference = STATIC_SYMBOL("REFERENCE",AB_package);
    Qtrend_chart_value_axes = STATIC_SYMBOL("TREND-CHART-VALUE-AXES",
	    AB_package);
    list_constant_222 = STATIC_LIST((SI_Long)3L,Qsubtype,Qreference,
	    Qtrend_chart_value_axes);
    Qcomponent_reference = STATIC_SYMBOL("COMPONENT-REFERENCE",AB_package);
    list_constant_221 = STATIC_LIST((SI_Long)2L,Qtype,Qcomponent_reference);
    list_constant_223 = STATIC_CONS(list_constant_221,Qnil);
    list_constant_232 = STATIC_CONS(list_constant_222,list_constant_223);
    Qplot_point_format = STATIC_SYMBOL("PLOT-POINT-FORMAT",AB_package);
    Qtrend_chart_point_formats = STATIC_SYMBOL("TREND-CHART-POINT-FORMATS",
	    AB_package);
    list_constant_224 = STATIC_LIST((SI_Long)3L,Qsubtype,Qreference,
	    Qtrend_chart_point_formats);
    list_constant_233 = STATIC_CONS(list_constant_224,list_constant_223);
    Qplot_connector_format = STATIC_SYMBOL("PLOT-CONNECTOR-FORMAT",AB_package);
    Qtrend_chart_connector_formats = 
	    STATIC_SYMBOL("TREND-CHART-CONNECTOR-FORMATS",AB_package);
    list_constant_225 = STATIC_LIST((SI_Long)3L,Qsubtype,Qreference,
	    Qtrend_chart_connector_formats);
    list_constant_234 = STATIC_CONS(list_constant_225,list_constant_223);
    Qplot_update_interval = STATIC_SYMBOL("PLOT-UPDATE-INTERVAL",AB_package);
    list_constant_226 = STATIC_LIST((SI_Long)2L,Qtype,
	    Qplot_update_interval_spec);
    list_constant_235 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_226);
    Qplot_wait_interval = STATIC_SYMBOL("PLOT-WAIT-INTERVAL",AB_package);
    Qplot_update_priority = STATIC_SYMBOL("PLOT-UPDATE-PRIORITY",AB_package);
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    list_constant_227 = STATIC_LIST((SI_Long)2L,Qtype,Qpriority);
    list_constant_236 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_227);
    Qplot_request_data_seeking_qm = 
	    STATIC_SYMBOL("PLOT-REQUEST-DATA-SEEKING\?",AB_package);
    Qplot_request_event_updates_qm = 
	    STATIC_SYMBOL("PLOT-REQUEST-EVENT-UPDATES\?",AB_package);
    Qplot_use_simulator_qm = STATIC_SYMBOL("PLOT-USE-SIMULATOR\?",AB_package);
    Qplot_tracing_and_breakpoints = 
	    STATIC_SYMBOL("PLOT-TRACING-AND-BREAKPOINTS",AB_package);
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    list_constant_228 = STATIC_LIST((SI_Long)2L,Qtype,
	    Qtracing_and_breakpoints);
    list_constant_237 = STATIC_LIST((SI_Long)2L,list_constant_125,
	    list_constant_228);
    Qinclude_in_legend_qm = STATIC_SYMBOL("INCLUDE-IN-LEGEND\?",AB_package);
    Qplot_expression = STATIC_SYMBOL("PLOT-EXPRESSION",AB_package);
    list_constant_229 = STATIC_LIST((SI_Long)3L,Qtype,Qplot_expression,Qtext);
    list_constant_230 = STATIC_CONS(list_constant_161,Qnil);
    list_constant_238 = STATIC_LIST_STAR((SI_Long)3L,list_constant_125,
	    list_constant_229,list_constant_230);
    Qplot_history = STATIC_SYMBOL("PLOT-HISTORY",AB_package);
    Qplot_data_last_tc_representation_send_time_qm = 
	    STATIC_SYMBOL("PLOT-DATA-LAST-TC-REPRESENTATION-SEND-TIME\?",
	    AB_package);
    Qplot_data_tc_representation_end_index_qm = 
	    STATIC_SYMBOL("PLOT-DATA-TC-REPRESENTATION-END-INDEX\?",
	    AB_package);
    Qplot_data_tc_representation_earliest_index_qm = 
	    STATIC_SYMBOL("PLOT-DATA-TC-REPRESENTATION-EARLIEST-INDEX\?",
	    AB_package);
    Qplot_variable_or_parameter_qm = 
	    STATIC_SYMBOL("PLOT-VARIABLE-OR-PARAMETER\?",AB_package);
    Qplot_number_cell_index = STATIC_SYMBOL("PLOT-NUMBER-CELL-INDEX",
	    AB_package);
    Qplot_v_or_p_cell_index = STATIC_SYMBOL("PLOT-V-OR-P-CELL-INDEX",
	    AB_package);
    Qplot_index = STATIC_SYMBOL("PLOT-INDEX",AB_package);
    temp = make_slot_component_descriptor(Qcomponent_type,Nil,
	    list_constant_231);
    temp_1 = regenerate_optimized_constant(string_constant_107);
    temp_1 = make_slot_component_descriptor(temp_1,Nil,
	    regenerate_optimized_constant(string_constant_108));
    temp_2 = make_slot_component_descriptor(Qchart_element_uid,Qnil,Qnil);
    temp_3 = make_slot_component_descriptor(Qplot_use_local_history_qm,Qt,
	    list_constant_151);
    temp_4 = make_slot_component_descriptor(Qplot_axis,FIX((SI_Long)1L),
	    list_constant_232);
    temp_5 = make_slot_component_descriptor(Qplot_point_format,
	    FIX((SI_Long)1L),list_constant_233);
    temp_6 = make_slot_component_descriptor(Qplot_connector_format,
	    FIX((SI_Long)1L),list_constant_234);
    temp_7 = make_slot_component_descriptor(Qplot_update_interval,
	    FIX((SI_Long)5L),list_constant_235);
    temp_8 = make_slot_component_descriptor(Qplot_wait_interval,
	    FIX((SI_Long)2L),list_constant_150);
    temp_9 = make_slot_component_descriptor(Qplot_update_priority,
	    FIX((SI_Long)2L),list_constant_236);
    temp_10 = make_slot_component_descriptor(Qplot_request_data_seeking_qm,
	    Qt,list_constant_151);
    temp_11 = 
	    make_slot_component_descriptor(Qplot_request_event_updates_qm,
	    Qt,list_constant_151);
    temp_12 = make_slot_component_descriptor(Qplot_use_simulator_qm,Qnil,
	    list_constant_151);
    temp_13 = make_slot_component_descriptor(Qplot_tracing_and_breakpoints,
	    Qnil,list_constant_237);
    temp_14 = make_slot_component_descriptor(Qinclude_in_legend_qm,Qt,
	    list_constant_151);
    temp_15 = make_slot_component_descriptor(Qplot_expression,Qnil,
	    list_constant_238);
    temp_16 = make_slot_component_descriptor(Qplot_history,Qnil,
	    list_constant_190);
    temp_17 = 
	    make_slot_component_descriptor(Qplot_data_last_tc_representation_send_time_qm,
	    Qnil,list_constant_190);
    temp_18 = 
	    make_slot_component_descriptor(Qplot_data_tc_representation_end_index_qm,
	    Qnil,list_constant_190);
    temp_19 = 
	    make_slot_component_descriptor(Qplot_data_tc_representation_earliest_index_qm,
	    Qnil,list_constant_190);
    temp_20 = 
	    make_slot_component_descriptor(Qplot_variable_or_parameter_qm,
	    Qnil,list_constant_190);
    temp_21 = make_slot_component_descriptor(Qplot_number_cell_index,Qnil,
	    list_constant_190);
    temp_22 = make_slot_component_descriptor(Qplot_v_or_p_cell_index,Qnil,
	    list_constant_190);
    mutate_global_property(Qplot,make_compound_type_descriptor(Qplot,T,
	    list(24,temp,temp_1,temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,
	    temp_8,temp_9,temp_10,temp_11,temp_12,temp_13,temp_14,temp_15,
	    temp_16,temp_17,temp_18,temp_19,temp_20,temp_21,temp_22,
	    make_slot_component_descriptor(Qplot_index,Qnil,
	    list_constant_190)),Qplot_names),Qcompound_type_descriptor);
    Qupdate_interval = STATIC_SYMBOL("UPDATE-INTERVAL",AB_package);
    mutate_global_property(Qplot_update_interval,Qupdate_interval,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_interval),
	    Qslot_component_pretty_name),Qplot,Qplot_update_interval);
    mutate_global_property(Qupdate_interval,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qwait_interval = STATIC_SYMBOL("WAIT-INTERVAL",AB_package);
    mutate_global_property(Qplot_wait_interval,Qwait_interval,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwait_interval),
	    Qslot_component_pretty_name),Qplot,Qplot_wait_interval);
    mutate_global_property(Qwait_interval,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qupdate_priority = STATIC_SYMBOL("UPDATE-PRIORITY",AB_package);
    mutate_global_property(Qplot_update_priority,Qupdate_priority,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_priority),
	    Qslot_component_pretty_name),Qplot,Qplot_update_priority);
    mutate_global_property(Qupdate_priority,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qmay_request_data_seeking_qm = 
	    STATIC_SYMBOL("MAY-REQUEST-DATA-SEEKING\?",AB_package);
    mutate_global_property(Qplot_request_data_seeking_qm,
	    Qmay_request_data_seeking_qm,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmay_request_data_seeking_qm),
	    Qslot_component_pretty_name),Qplot,Qplot_request_data_seeking_qm);
    mutate_global_property(Qmay_request_data_seeking_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qmay_request_event_updates_qm = 
	    STATIC_SYMBOL("MAY-REQUEST-EVENT-UPDATES\?",AB_package);
    mutate_global_property(Qplot_request_event_updates_qm,
	    Qmay_request_event_updates_qm,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmay_request_event_updates_qm),
	    Qslot_component_pretty_name),Qplot,Qplot_request_event_updates_qm);
    mutate_global_property(Qmay_request_event_updates_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Quse_simulator_qm = STATIC_SYMBOL("USE-SIMULATOR\?",AB_package);
    mutate_global_property(Qplot_use_simulator_qm,Quse_simulator_qm,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Quse_simulator_qm),
	    Qslot_component_pretty_name),Qplot,Qplot_use_simulator_qm);
    mutate_global_property(Quse_simulator_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Quse_local_history_qm = STATIC_SYMBOL("USE-LOCAL-HISTORY\?",AB_package);
    mutate_global_property(Qplot_use_local_history_qm,
	    Quse_local_history_qm,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Quse_local_history_qm),
	    Qslot_component_pretty_name),Qplot,Qplot_use_local_history_qm);
    mutate_global_property(Quse_local_history_qm,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    mutate_global_property(Qplot_tracing_and_breakpoints,
	    Qtracing_and_breakpoints,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtracing_and_breakpoints),
	    Qslot_component_pretty_name),Qplot,Qplot_tracing_and_breakpoints);
    mutate_global_property(Qtracing_and_breakpoints,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    mutate_global_property(Qplot_expression,Qexpression,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexpression),
	    Qslot_component_pretty_name),Qplot,Qplot_expression);
    mutate_global_property(Qexpression,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qvalue_axis_name_or_number = STATIC_SYMBOL("VALUE-AXIS-NAME-OR-NUMBER",
	    AB_package);
    mutate_global_property(Qplot_axis,Qvalue_axis_name_or_number,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qvalue_axis_name_or_number),
	    Qslot_component_pretty_name),Qplot,Qplot_axis);
    mutate_global_property(Qvalue_axis_name_or_number,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qpoint_format_name_or_number = 
	    STATIC_SYMBOL("POINT-FORMAT-NAME-OR-NUMBER",AB_package);
    mutate_global_property(Qplot_point_format,Qpoint_format_name_or_number,
	    Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_format_name_or_number),
	    Qslot_component_pretty_name),Qplot,Qplot_point_format);
    mutate_global_property(Qpoint_format_name_or_number,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Qconnector_format_name_or_number = 
	    STATIC_SYMBOL("CONNECTOR-FORMAT-NAME-OR-NUMBER",AB_package);
    mutate_global_property(Qplot_connector_format,
	    Qconnector_format_name_or_number,Qslot_component_alias);
    slot_component_pretty_name_new_value = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnector_format_name_or_number),
	    Qslot_component_pretty_name),Qplot,Qplot_connector_format);
    mutate_global_property(Qconnector_format_name_or_number,
	    slot_component_pretty_name_new_value,Qslot_component_pretty_name);
    Q2d_image_plane_state = STATIC_SYMBOL("2D-IMAGE-PLANE-STATE",AB_package);
    Qdependent_frame = STATIC_SYMBOL("DEPENDENT-FRAME",AB_package);
    list_constant_239 = STATIC_CONS(Qdependent_frame,Qnil);
    check_if_superior_classes_are_defined(Q2d_image_plane_state,
	    list_constant_239);
    string_constant_109 = STATIC_STRING("1l1l8t");
    string_constant_110 = 
	    STATIC_STRING("13Dy4z8r83GJy83GJy83G2y83G2y00001m1l8o1l8l000004z8r83G5y83G5y83G2y83G2y00001m1l8o1l8l000004z8r83GAy83GAy83G2y83G2y00001m1l8o1l8l");
    string_constant_111 = 
	    STATIC_STRING("000004z8r83G8y83G8y83G2y83G2y00001m1l8o1l8l000004z8r83G9y83G9y83G2y83G2y00001m1l8o1l8l000004z8r83GHy83GHy83G2y83G2y00001m1l8o1l8");
    string_constant_112 = 
	    STATIC_STRING("l000004z8r83GFy83GFy83G2y83G2y00001m1l8o1l8l000004z8r83GGy83GGy83G2y83G2y00001m1l8o1l8l000004z8r83GKy83GKy83G2y83G2y00001m1l8o1l");
    string_constant_113 = 
	    STATIC_STRING("8l000004z8r83GIy83GIy83G2y83G2y00001m1l8o1l8l000004z8r83G7y83G7y83G2y83G2y00001m1l8o1l8l000004z8r83GEy83GEy83G2y83G2y00001m1l8o1");
    string_constant_114 = 
	    STATIC_STRING("l8l000004z8r83G6y83G6y83G2y83G2y00001m1l8o1l8l000004z8r83G4y83G4y83G2y83G2y00001m1l8o1l8l000004z8r83GDy83GDy83G2y83G2y00001m1l8o");
    string_constant_115 = 
	    STATIC_STRING("1l8l000004z8r83GBy83GBy83G2y83G2y00001m1l8o1l8l000004z8r83GCy83GCy83G2y83G2y00001m1l8o1l8l00000");
    string_constant_116 = 
	    STATIC_STRING("13Fy8q1n83G2y1l83=fy8t1o83GJy08o8l1o83G5y08o8l1o83GAy08o8l1o83G8y08o8l1o83G9y08o8l1o83GHy08o8l1o83GFy08o8l1o83GGy08o8l1o83GKy08o");
    string_constant_117 = 
	    STATIC_STRING("8l1o83GIy08o8l1o83G7y08o8l1o83GEy08o8l1o83G6y08o8l1o83G4y08o8l1o83GDy08o8l1o83GBy08o8l1o83GCy08o8l");
    temp = regenerate_optimized_constant(string_constant_109);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_110,
	    string_constant_111,string_constant_112,string_constant_113,
	    string_constant_114,string_constant_115));
    add_class_to_environment(9,Q2d_image_plane_state,list_constant_239,Nil,
	    temp,Nil,temp_1,list_constant_239,
	    regenerate_optimized_constant(LIST_2(string_constant_116,
	    string_constant_117)),Nil);
    Q2d_incomplete_painting_actions = 
	    STATIC_SYMBOL("2D-INCOMPLETE-PAINTING-ACTIONS",AB_package);
    Qreclaim_2d_incomplete_painting_actions_value = 
	    STATIC_SYMBOL("RECLAIM-2D-INCOMPLETE-PAINTING-ACTIONS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_2d_incomplete_painting_actions_value,
	    STATIC_FUNCTION(reclaim_2d_incomplete_painting_actions_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Q2d_incomplete_painting_actions,
	    SYMBOL_FUNCTION(Qreclaim_2d_incomplete_painting_actions_value),
	    Qslot_value_reclaimer);
    Qg2_defstruct_structure_name_display_pane_g2_struct = 
	    STATIC_SYMBOL("DISPLAY-PANE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdisplay_pane = STATIC_SYMBOL("DISPLAY-PANE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_display_pane_g2_struct,
	    Qdisplay_pane,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qdisplay_pane,
	    Qg2_defstruct_structure_name_display_pane_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_display_pane == UNBOUND)
	The_type_description_of_display_pane = Nil;
    string_constant_118 = 
	    STATIC_STRING("43Dy8m831Vy1n831Vy8n8k1l8n0000000kwk0k0");
    temp = The_type_description_of_display_pane;
    The_type_description_of_display_pane = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_118));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_display_pane_g2_struct,
	    The_type_description_of_display_pane,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qdisplay_pane,
	    The_type_description_of_display_pane,Qtype_description_of_type);
    Qoutstanding_display_pane_count = 
	    STATIC_SYMBOL("OUTSTANDING-DISPLAY-PANE-COUNT",AB_package);
    Qdisplay_pane_structure_memory_usage = 
	    STATIC_SYMBOL("DISPLAY-PANE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_119 = STATIC_STRING("1q831Vy8s83-RYy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_display_pane_count);
    push_optimized_constant(Qdisplay_pane_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_119));
    Qchain_of_available_display_panes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-DISPLAY-PANES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_display_panes,
	    Chain_of_available_display_panes);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_display_panes,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qdisplay_pane_count = STATIC_SYMBOL("DISPLAY-PANE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdisplay_pane_count,Display_pane_count);
    record_system_variable(Qdisplay_pane_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_display_panes_vector == UNBOUND)
	Chain_of_available_display_panes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qdisplay_pane_structure_memory_usage,
	    STATIC_FUNCTION(display_pane_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_display_pane_count,
	    STATIC_FUNCTION(outstanding_display_pane_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_display_pane_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_display_pane,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qdisplay_pane,
	    reclaim_structure_for_display_pane_1);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qg2_defstruct_structure_name_axis_pane_g2_struct = 
	    STATIC_SYMBOL("AXIS-PANE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qaxis_pane = STATIC_SYMBOL("AXIS-PANE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_axis_pane_g2_struct,
	    Qaxis_pane,Qab_name_of_unique_structure_type);
    mutate_global_property(Qaxis_pane,
	    Qg2_defstruct_structure_name_axis_pane_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_axis_pane == UNBOUND)
	The_type_description_of_axis_pane = Nil;
    string_constant_120 = 
	    STATIC_STRING("43Dy8m83fGy1o83fGy831Vy8n8k1l831Vy0000001l1m8x831Vyk3Nyk0k0");
    temp = The_type_description_of_axis_pane;
    The_type_description_of_axis_pane = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_120));
    mutate_global_property(Qg2_defstruct_structure_name_axis_pane_g2_struct,
	    The_type_description_of_axis_pane,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qaxis_pane,The_type_description_of_axis_pane,
	    Qtype_description_of_type);
    Qoutstanding_axis_pane_count = 
	    STATIC_SYMBOL("OUTSTANDING-AXIS-PANE-COUNT",AB_package);
    Qaxis_pane_structure_memory_usage = 
	    STATIC_SYMBOL("AXIS-PANE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_121 = STATIC_STRING("1q83fGy8s83-KLy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_axis_pane_count);
    push_optimized_constant(Qaxis_pane_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_121));
    Qchain_of_available_axis_panes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-AXIS-PANES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_axis_panes,
	    Chain_of_available_axis_panes);
    record_system_variable(Qchain_of_available_axis_panes,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qaxis_pane_count = STATIC_SYMBOL("AXIS-PANE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_pane_count,Axis_pane_count);
    record_system_variable(Qaxis_pane_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_axis_panes_vector == UNBOUND)
	Chain_of_available_axis_panes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qaxis_pane_structure_memory_usage,
	    STATIC_FUNCTION(axis_pane_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_axis_pane_count,
	    STATIC_FUNCTION(outstanding_axis_pane_count,NIL,FALSE,0,0));
    reclaim_structure_for_axis_pane_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_axis_pane,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qaxis_pane,
	    reclaim_structure_for_axis_pane_1);
    Qg2_defstruct_structure_name_trend_chart_pane_g2_struct = 
	    STATIC_SYMBOL("TREND-CHART-PANE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtrend_chart_pane = STATIC_SYMBOL("TREND-CHART-PANE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_trend_chart_pane_g2_struct,
	    Qtrend_chart_pane,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtrend_chart_pane,
	    Qg2_defstruct_structure_name_trend_chart_pane_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_trend_chart_pane == UNBOUND)
	The_type_description_of_trend_chart_pane = Nil;
    string_constant_122 = 
	    STATIC_STRING("43Dy8m83o-y1o83o-y831Vy8n8k1l831Vy0000001l1m8x831Vykxk0k0");
    temp = The_type_description_of_trend_chart_pane;
    The_type_description_of_trend_chart_pane = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_122));
    mutate_global_property(Qg2_defstruct_structure_name_trend_chart_pane_g2_struct,
	    The_type_description_of_trend_chart_pane,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtrend_chart_pane,
	    The_type_description_of_trend_chart_pane,
	    Qtype_description_of_type);
    Qoutstanding_trend_chart_pane_count = 
	    STATIC_SYMBOL("OUTSTANDING-TREND-CHART-PANE-COUNT",AB_package);
    Qtrend_chart_pane_structure_memory_usage = 
	    STATIC_SYMBOL("TREND-CHART-PANE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_123 = STATIC_STRING("1q83o-y8s83-u6y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_trend_chart_pane_count);
    push_optimized_constant(Qtrend_chart_pane_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_123));
    Qchain_of_available_trend_chart_panes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TREND-CHART-PANES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_trend_chart_panes,
	    Chain_of_available_trend_chart_panes);
    record_system_variable(Qchain_of_available_trend_chart_panes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qtrend_chart_pane_count = STATIC_SYMBOL("TREND-CHART-PANE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtrend_chart_pane_count,Trend_chart_pane_count);
    record_system_variable(Qtrend_chart_pane_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_trend_chart_panes_vector == UNBOUND)
	Chain_of_available_trend_chart_panes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtrend_chart_pane_structure_memory_usage,
	    STATIC_FUNCTION(trend_chart_pane_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_trend_chart_pane_count,
	    STATIC_FUNCTION(outstanding_trend_chart_pane_count,NIL,FALSE,0,0));
    reclaim_structure_for_trend_chart_pane_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_trend_chart_pane,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtrend_chart_pane,
	    reclaim_structure_for_trend_chart_pane_1);
    Qg2_defstruct_structure_name_legend_pane_g2_struct = 
	    STATIC_SYMBOL("LEGEND-PANE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlegend_pane = STATIC_SYMBOL("LEGEND-PANE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_legend_pane_g2_struct,
	    Qlegend_pane,Qab_name_of_unique_structure_type);
    mutate_global_property(Qlegend_pane,
	    Qg2_defstruct_structure_name_legend_pane_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_legend_pane == UNBOUND)
	The_type_description_of_legend_pane = Nil;
    string_constant_124 = 
	    STATIC_STRING("43Dy8m83kTy1o83kTy831Vy8n8k1l831Vy0000001l1m8x831Vykyk0k0");
    temp = The_type_description_of_legend_pane;
    The_type_description_of_legend_pane = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_124));
    mutate_global_property(Qg2_defstruct_structure_name_legend_pane_g2_struct,
	    The_type_description_of_legend_pane,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qlegend_pane,
	    The_type_description_of_legend_pane,Qtype_description_of_type);
    Qoutstanding_legend_pane_count = 
	    STATIC_SYMBOL("OUTSTANDING-LEGEND-PANE-COUNT",AB_package);
    Qlegend_pane_structure_memory_usage = 
	    STATIC_SYMBOL("LEGEND-PANE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_125 = STATIC_STRING("1q83kTy8s83-cUy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_legend_pane_count);
    push_optimized_constant(Qlegend_pane_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_125));
    Qchain_of_available_legend_panes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LEGEND-PANES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_legend_panes,
	    Chain_of_available_legend_panes);
    record_system_variable(Qchain_of_available_legend_panes,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qlegend_pane_count = STATIC_SYMBOL("LEGEND-PANE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlegend_pane_count,Legend_pane_count);
    record_system_variable(Qlegend_pane_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_legend_panes_vector == UNBOUND)
	Chain_of_available_legend_panes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qlegend_pane_structure_memory_usage,
	    STATIC_FUNCTION(legend_pane_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_legend_pane_count,
	    STATIC_FUNCTION(outstanding_legend_pane_count,NIL,FALSE,0,0));
    reclaim_structure_for_legend_pane_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_legend_pane,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qlegend_pane,
	    reclaim_structure_for_legend_pane_1);
    Qg2_defstruct_structure_name_relative_time_pane_g2_struct = 
	    STATIC_SYMBOL("RELATIVE-TIME-PANE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qrelative_time_pane = STATIC_SYMBOL("RELATIVE-TIME-PANE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_relative_time_pane_g2_struct,
	    Qrelative_time_pane,Qab_name_of_unique_structure_type);
    mutate_global_property(Qrelative_time_pane,
	    Qg2_defstruct_structure_name_relative_time_pane_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_relative_time_pane == UNBOUND)
	The_type_description_of_relative_time_pane = Nil;
    string_constant_126 = 
	    STATIC_STRING("43Dy8m83mEy1o83mEy831Vy8n8k1l831Vy0000001l1m8x831Vykyk0k0");
    temp = The_type_description_of_relative_time_pane;
    The_type_description_of_relative_time_pane = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_126));
    mutate_global_property(Qg2_defstruct_structure_name_relative_time_pane_g2_struct,
	    The_type_description_of_relative_time_pane,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qrelative_time_pane,
	    The_type_description_of_relative_time_pane,
	    Qtype_description_of_type);
    Qoutstanding_relative_time_pane_count = 
	    STATIC_SYMBOL("OUTSTANDING-RELATIVE-TIME-PANE-COUNT",AB_package);
    Qrelative_time_pane_structure_memory_usage = 
	    STATIC_SYMBOL("RELATIVE-TIME-PANE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_127 = STATIC_STRING("1q83mEy8s83-m0y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_relative_time_pane_count);
    push_optimized_constant(Qrelative_time_pane_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_127));
    Qchain_of_available_relative_time_panes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RELATIVE-TIME-PANES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_relative_time_panes,
	    Chain_of_available_relative_time_panes);
    record_system_variable(Qchain_of_available_relative_time_panes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qrelative_time_pane_count = STATIC_SYMBOL("RELATIVE-TIME-PANE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrelative_time_pane_count,
	    Relative_time_pane_count);
    record_system_variable(Qrelative_time_pane_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_relative_time_panes_vector == UNBOUND)
	Chain_of_available_relative_time_panes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qrelative_time_pane_structure_memory_usage,
	    STATIC_FUNCTION(relative_time_pane_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_relative_time_pane_count,
	    STATIC_FUNCTION(outstanding_relative_time_pane_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_relative_time_pane_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_relative_time_pane,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qrelative_time_pane,
	    reclaim_structure_for_relative_time_pane_1);
    Qg2_defstruct_structure_name_grid_pane_g2_struct = 
	    STATIC_SYMBOL("GRID-PANE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgrid_pane = STATIC_SYMBOL("GRID-PANE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_grid_pane_g2_struct,
	    Qgrid_pane,Qab_name_of_unique_structure_type);
    mutate_global_property(Qgrid_pane,
	    Qg2_defstruct_structure_name_grid_pane_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_grid_pane == UNBOUND)
	The_type_description_of_grid_pane = Nil;
    string_constant_128 = 
	    STATIC_STRING("43Dy8m83iAy1o83iAy831Vy8n8k1l831Vy0000001l1m8x831Vyk3Lyk0k0");
    temp = The_type_description_of_grid_pane;
    The_type_description_of_grid_pane = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_128));
    mutate_global_property(Qg2_defstruct_structure_name_grid_pane_g2_struct,
	    The_type_description_of_grid_pane,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qgrid_pane,The_type_description_of_grid_pane,
	    Qtype_description_of_type);
    Qoutstanding_grid_pane_count = 
	    STATIC_SYMBOL("OUTSTANDING-GRID-PANE-COUNT",AB_package);
    Qgrid_pane_structure_memory_usage = 
	    STATIC_SYMBOL("GRID-PANE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_129 = STATIC_STRING("1q83iAy8s83-XFy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_grid_pane_count);
    push_optimized_constant(Qgrid_pane_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_129));
    Qchain_of_available_grid_panes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GRID-PANES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_grid_panes,
	    Chain_of_available_grid_panes);
    record_system_variable(Qchain_of_available_grid_panes,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qgrid_pane_count = STATIC_SYMBOL("GRID-PANE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgrid_pane_count,Grid_pane_count);
    record_system_variable(Qgrid_pane_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_grid_panes_vector == UNBOUND)
	Chain_of_available_grid_panes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgrid_pane_structure_memory_usage,
	    STATIC_FUNCTION(grid_pane_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_grid_pane_count,
	    STATIC_FUNCTION(outstanding_grid_pane_count,NIL,FALSE,0,0));
    reclaim_structure_for_grid_pane_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_grid_pane,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgrid_pane,
	    reclaim_structure_for_grid_pane_1);
    Qhairline = STATIC_SYMBOL("HAIRLINE",AB_package);
    Qtrend_chart_label_to_display = 
	    STATIC_SYMBOL("TREND-CHART-LABEL-TO-DISPLAY",AB_package);
    Qtitle = STATIC_SYMBOL("TITLE",AB_package);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    alias_slot_name(3,Qtrend_chart_label_to_display,Qtitle,Qtrend_chart);
    Qtrend_chart_plots = STATIC_SYMBOL("TREND-CHART-PLOTS",AB_package);
    Qplots = STATIC_SYMBOL("PLOTS",AB_package);
    alias_slot_name(3,Qtrend_chart_plots,Qplots,Qtrend_chart);
    Qvalue_axes = STATIC_SYMBOL("VALUE-AXES",AB_package);
    alias_slot_name(3,Qtrend_chart_value_axes,Qvalue_axes,Qtrend_chart);
    Qtrend_chart_time_axis = STATIC_SYMBOL("TREND-CHART-TIME-AXIS",AB_package);
    alias_slot_name(3,Qtrend_chart_time_axis,Qtime_axis,Qtrend_chart);
    Qpoint_formats = STATIC_SYMBOL("POINT-FORMATS",AB_package);
    alias_slot_name(3,Qtrend_chart_point_formats,Qpoint_formats,Qtrend_chart);
    Qconnector_formats = STATIC_SYMBOL("CONNECTOR-FORMATS",AB_package);
    alias_slot_name(3,Qtrend_chart_connector_formats,Qconnector_formats,
	    Qtrend_chart);
    Qtrend_chart_plotting_conditions = 
	    STATIC_SYMBOL("TREND-CHART-PLOTTING-CONDITIONS",AB_package);
    Qplotting_conditions = STATIC_SYMBOL("PLOTTING-CONDITIONS",AB_package);
    alias_slot_name(3,Qtrend_chart_plotting_conditions,
	    Qplotting_conditions,Qtrend_chart);
    Qcompound_slot_value_writer_info = 
	    STATIC_SYMBOL("COMPOUND-SLOT-VALUE-WRITER-INFO",AB_package);
    mutate_global_property(Qplot,LIST_3(Qtrend_chart_plots,Qplot,Qplots),
	    Qcompound_slot_value_writer_info);
    Qtime_axes = STATIC_SYMBOL("TIME-AXES",AB_package);
    mutate_global_property(Qtime_axis,LIST_3(Qtrend_chart_time_axis,
	    Qtime_axis,Qtime_axes),Qcompound_slot_value_writer_info);
    Qtrend_chart_formats = STATIC_SYMBOL("TREND-CHART-FORMATS",AB_package);
    mutate_global_property(Qtrend_chart_format,LIST_3(Qtrend_chart_format,
	    Qtrend_chart_format,Qtrend_chart_formats),
	    Qcompound_slot_value_writer_info);
    mutate_global_property(Qvalue_axis,LIST_3(Qtrend_chart_value_axes,
	    Qvalue_axis,Qvalue_axes),Qcompound_slot_value_writer_info);
    mutate_global_property(Qpoint_format,LIST_3(Qtrend_chart_point_formats,
	    Qpoint_format,Qpoint_formats),Qcompound_slot_value_writer_info);
    mutate_global_property(Qconnector_format,
	    LIST_3(Qtrend_chart_connector_formats,Qconnector_format,
	    Qconnector_formats),Qcompound_slot_value_writer_info);
    Minimum_data_window_size = FIX((SI_Long)20L);
    Minimum_data_window_margin = FIX((SI_Long)10L);
    Default_trend_chart_height = FIX((SI_Long)200L);
    Default_trend_chart_width = FIX((SI_Long)300L);
    Maximum_plots_per_trend_chart = FIX((SI_Long)20L);
    Trend_chart_plot_slot_increment = FIX((SI_Long)10L);
    string_constant_130 = STATIC_STRING("1l1m83-Tly83Sy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_130));
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_240 = STATIC_LIST((SI_Long)2L,Qitem,Qblock);
    check_if_superior_classes_are_defined(Qtrend_chart,list_constant_240);
    string_constant_131 = STATIC_STRING("1m1m8v83AHy1l8t");
    string_constant_132 = 
	    STATIC_STRING("13Oy4z8r83-Ey83-Ey83AHy83AHy03C+y001q1l8l1l8o1m8p01l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I think");
    string_constant_133 = 
	    STATIC_STRING(" individual attribute-mimics should be created for ~\nparticular flags, and I don\'t know if options should continue to be support");
    string_constant_134 = 
	    STATIC_STRING("ed. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83cSy83cSy83AHy83AHy00001n1n8p83-dy8");
    string_constant_135 = 
	    STATIC_STRING("3Gy1l8o1l8l000004z8r83cdy83cdy83AHy83AHy00001n1m8p83FYy1l8o1l8l000004z8r83cjy83cjy83AHy83AHy00001n1m8p83Fby1l8o1l8l000004z8r83cg");
    string_constant_136 = 
	    STATIC_STRING("y83cgy83AHy83AHy00001n1m8p83Fay1l8o1l8l000004z8r83cey83cey83AHy83AHy00001n1m8p83FZy1l8o1l8l000004z8r83cPy83cPy83AHy83AHy00001n1m");
    string_constant_137 = 
	    STATIC_STRING("8p83FVy1l8o1l8l000004z8r83FWy83FWy83AHy83AHy00001n1m8p83FXy1l8o1l8l000004z8r83ciy83ciy83AHy83AHy00001m1l8o1l8l000004z8r83GLy83GL");
    string_constant_138 = 
	    STATIC_STRING("y83AHy83AHy0k001n1l8o1l8l1l83Cy000004z8r83G1y83G1y83AHy83AHy08k001m1l8o1l8l000004z8r83G3y83G3y83AHy83AHy00001m1l8o1l8l000004z8r8");
    string_constant_139 = 
	    STATIC_STRING("3cYy83cYy83AHy83AHy00001m1l8o1l8l000004z8r83cay83cay83AHy83AHy00001m1l8o1l8l000004z8r83cby83cby83AHy83AHy00001m1l8o1l8l000004z8r");
    string_constant_140 = 
	    STATIC_STRING("83cZy83cZy83AHy83AHy00001m1l8o1l8l000004z8r83cRy83cRy83AHy83AHy00001m1l8o1l8l000004z8r83cNy83cNy83AHy83AHy00001m1l8o1l8l000004z8");
    string_constant_141 = 
	    STATIC_STRING("r83cOy83cOy83AHy83AHy00001m1l8o1l8l000004z8r83chy83chy83AHy83AHy00001m1l8o1l8l000004z8r83cVy83cVy83AHy83AHy00001m1l8o1l8l000004z");
    string_constant_142 = 
	    STATIC_STRING("8r83cQy83cQy83AHy83AHy00001m1l8o1l8l000004z8r83cWy83cWy83AHy83AHy00001m1l8o1l8l000004z8r83cTy83cTy83AHy83AHy00001m1l8o1l8l000004");
    string_constant_143 = 
	    STATIC_STRING("z8r83cUy83cUy83AHy83AHy00001m1l8o1l8l000004z8r83ccy83ccy83AHy83AHy03Gy001n1l8o1l8l1l83Cy000004z8r83cXy83cXy83AHy83AHy00001n1l8o1");
    string_constant_144 = 
	    STATIC_STRING("l8l1l83Cy000004z8r83cfy83cfy83AHy83AHy00001m1l8o1l8l00000");
    string_constant_145 = 
	    STATIC_STRING("13Qy8q1o83AHy1m83Ry9k1m8v83AHy8t1m83-Ey3C+y1p83cSy01n8p83-dy83Gy8o8l1p83cdy01m8p83FYy8o8l1p83cjy01m8p83Fby8o8l1p83cgy01m8p83Fay8");
    string_constant_146 = 
	    STATIC_STRING("o8l1p83cey01m8p83FZy8o8l1p83cPy01m8p83FVy8o8l1p83FWy01m8p83FXy8o8l1o83ciy08o8l1p83GLyk8o8l83Cy1o83G1y8k8o8l1o83G3y08o8l1o83cYy08");
    string_constant_147 = 
	    STATIC_STRING("o8l1o83cay08o8l1o83cby08o8l1o83cZy08o8l1o83cRy08o8l1o83cNy08o8l1o83cOy08o8l1o83chy08o8l1o83cVy08o8l1o83cQy08o8l1o83cWy08o8l1o83c");
    string_constant_148 = 
	    STATIC_STRING("Ty08o8l1o83cUy08o8l1p83ccy3Gy8o8l83Cy1p83cXy08o8l83Cy1o83cfy08o8l");
    temp = regenerate_optimized_constant(string_constant_131);
    temp_1 = regenerate_optimized_constant(list(13,string_constant_132,
	    string_constant_133,string_constant_134,string_constant_135,
	    string_constant_136,string_constant_137,string_constant_138,
	    string_constant_139,string_constant_140,string_constant_141,
	    string_constant_142,string_constant_143,string_constant_144));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qtrend_chart,list_constant_240,Nil,temp,Nil,
	    temp_1,list_constant_240,
	    regenerate_optimized_constant(LIST_4(string_constant_145,
	    string_constant_146,string_constant_147,string_constant_148)),Nil);
    Qcompound_slot_descriptor = STATIC_SYMBOL("COMPOUND-SLOT-DESCRIPTOR",
	    AB_package);
    mutate_global_property(Qtrend_chart_plots,
	    make_compound_slot_descriptor(Qtrend_chart_plots,Qplot,
	    Qtrend_chart,Qt,Qt),Qcompound_slot_descriptor);
    mutate_global_property(Qtrend_chart_value_axes,
	    make_compound_slot_descriptor(Qtrend_chart_value_axes,
	    Qvalue_axis,Qtrend_chart,Qt,Qt),Qcompound_slot_descriptor);
    mutate_global_property(Qtrend_chart_time_axis,
	    make_compound_slot_descriptor(Qtrend_chart_time_axis,
	    Qtime_axis,Qtrend_chart,Qnil,Qnil),Qcompound_slot_descriptor);
    mutate_global_property(Qtrend_chart_point_formats,
	    make_compound_slot_descriptor(Qtrend_chart_point_formats,
	    Qpoint_format,Qtrend_chart,Qt,Qt),Qcompound_slot_descriptor);
    mutate_global_property(Qtrend_chart_connector_formats,
	    make_compound_slot_descriptor(Qtrend_chart_connector_formats,
	    Qconnector_format,Qtrend_chart,Qt,Qt),Qcompound_slot_descriptor);
    mutate_global_property(Qtrend_chart_format,
	    make_compound_slot_descriptor(Qtrend_chart_format,
	    Qtrend_chart_format,Qtrend_chart,Qnil,Qnil),
	    Qcompound_slot_descriptor);
    list_constant_241 = STATIC_CONS(Qtrend_chart_format,Qnil);
    list_constant_242 = STATIC_LIST_STAR((SI_Long)6L,Qtrend_chart_plots,
	    Qtrend_chart_value_axes,Qtrend_chart_time_axis,
	    Qtrend_chart_point_formats,Qtrend_chart_connector_formats,
	    list_constant_241);
    Qcompound_slots_for_class = STATIC_SYMBOL("COMPOUND-SLOTS-FOR-CLASS",
	    AB_package);
    mutate_global_property(Qtrend_chart,list_constant_242,
	    Qcompound_slots_for_class);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_149 = 
	    STATIC_STRING("13by1n83FYy83-uAy1ml01n83FYy1n83-uAy1m9k83-Zy83-u8y1mln1n83-uAy1m83Sy83-uDy1ml01n83-uAy1o83Sy83-uDy1m9k83-Py83-uBy1mlo1m83-uDy1m");
    string_constant_150 = 
	    STATIC_STRING("9k833Wy1m83-uDy1m9k83-jBy1m83-uBy83-uCy1o83-uBy1n83-uCy1m9k83vy83-uBy1nmln9l1n83-uCy1o1m9k833Wy83Sy1m9k832dy83-6y1mmo1m83-u8y83-");
    string_constant_151 = 
	    STATIC_STRING("u7y1o83-u8y1n83-u7y1m9k83-Zy83-u8y1nmln9l1n83-u9y1o1m9k9m1m9k833Wy1m9k832dy83-6y1m832dyo1n83-u9y1m1m9k833Wy83Sy1m83X*ym1n83-u9y1");
    string_constant_152 = 
	    STATIC_STRING("m1m9k83=by1m9k833Wy1l83=by1n83-u7y1q1m9k9m1m9k835oy1m9k83-Ty83-u9y1m9k83*Iy83-ky1n83-9=yqo1n83-u7y1q1m9k9m1m9k83-9=y1m9k83-Ty83-");
    string_constant_153 = 
	    STATIC_STRING("u9y1m9k83*Iy83-ky1n83-9=yqo1n83-u7y1q1m9k9m1m9k83=py1m9k83-Ty83-u9y1m9k83*Iy83-9*y1n83-9*yqo1n83-u7y1q1m9k9m1m9k83-9*y1m9k83-Ty8");
    string_constant_154 = 
	    STATIC_STRING("3-u9y1m9k83*Iy83-9*y1n83-9*yqo1n83-u7y1q1m9k9m1m9k83-ZQy1m9k83-Ty83-u9y1m9k83*Iy83Ky1n83-ZQyqo1n83-u7y1q1m9k9m1m9k83-py1m9k83-Ty");
    string_constant_155 = 
	    STATIC_STRING("83-u9y1m9k83*Iy83-py1n83-j5yqo1n83-u7y1q1m9k9m1m9k83-j5y1m9k83-Ty83-u9y1m9k83*Iy83-py1n83-j5yqo1n83-u7y1q1m9k9m1m9k83-vdy1m9k83-");
    string_constant_156 = 
	    STATIC_STRING("Ty83-u9y1m9k83*Iy83Ky1n83-j9yqo1n83-u7y1q1m9k9m1m9k83-j9y1m9k83-Ty83-u9y1m9k83*Iy83Ky1n83-j9yqo1n83-u7y1q1m9k9m1m9k83-e1y1m9k83-");
    string_constant_157 = 
	    STATIC_STRING("Ty83-u9y1m9k83*Iy83Ky1n83-j4yqo1n83-u7y1q1m9k9m1m9k83-j4y1m9k83-Ty83-u9y1m9k83*Iy83Ky1n83-j4yqo1n83-u7y1q1m9k9m1m9k83-e=y1m9k83-");
    string_constant_158 = 
	    STATIC_STRING("Ty83-u9y1m9k83*Iy83Ky1n83-j3yqo1n83-u7y1q1m9k9m1m9k83-j3y1m9k83-Ty83-u9y1m9k83*Iy83Ky1n83-j3yqo1n83-u7y1q1m9k9m1m9k83-vay1m9k83-");
    string_constant_159 = 
	    STATIC_STRING("Ty83-u9y1m9k83*Iy83-Yy1n83-j7yqo1n83-u7y1q1m9k9m1m9k83-j7y1m9k83-Ty83-u9y1m9k83*Iy83-Yy1n83-j7yqo1n83-u7y1q1m9k9m1m9k83-wiy1m9k8");
    string_constant_160 = 
	    STATIC_STRING("3-Ty83-u9y1m9k9n83=Qy1n83-jAyqo1n83-u7y1q1m9k9m1m9k83-jAy1m9k83-Ty83-u9y1m9k9n83=Qy1n83-jAyqo1n83-u7y1q1m9k9m1m9k83-vWy1m9k83-Ty");
    string_constant_161 = 
	    STATIC_STRING("83-u9y1m9k83*Iy83-90y1n83-j6yqo1n83-u7y1q1m9k9m1m9k83-j6y1m9k83-Ty83-u9y1m9k83*Iy83-90y1n83-j6yqo1n83-u7y1q1m9k9m1m9k83-OBy1m9k8");
    string_constant_162 = 
	    STATIC_STRING("3-Ty83-u9y1m9k83*Iy83sWy1n83-j+yqo1n83-u7y1q1m9k9m1m9k83-j+y1m9k83-Ty83-u9y1m9k83*Iy83sWy1n83-j+yqo1n83-u7y1q1m9k9m1m9k83-jEy1m9");
    string_constant_163 = 
	    STATIC_STRING("k83-Ty83-u9y1m9k83*Iy83sWy1n83-j1yqo1n83-u7y1q1m9k9m1m9k83-j1y1m9k83-Ty83-u9y1m9k83*Iy83sWy1n83-j1yqo1n83-u7y1q1m9k9m1m9k83-w2y1");
    string_constant_164 = 
	    STATIC_STRING("m9k83-Ty83-u9y1m9k83*Iy83sWy1n83-iwyqo1n83-u7y1q1m9k9m1m9k83-iwy1m9k83-Ty83-u9y1m9k83*Iy83sWy1n83-iwyqo1n83-u7y1q1m9k9m1m9k83-vc");
    string_constant_165 = 
	    STATIC_STRING("y1m9k83-Ty83-u9y1m9k83*Iy83Ky1n83-j8yqo1n83-u7y1q1m9k9m1m9k83-j8y1m9k83-Ty83-u9y1m9k83*Iy83Ky1n83-j8yqo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(list(17,
	    string_constant_149,string_constant_150,string_constant_151,
	    string_constant_152,string_constant_153,string_constant_154,
	    string_constant_155,string_constant_156,string_constant_157,
	    string_constant_158,string_constant_159,string_constant_160,
	    string_constant_161,string_constant_162,string_constant_163,
	    string_constant_164,string_constant_165)));
    string_constant_166 = 
	    STATIC_STRING("13gy1n83Fby83-uRy1ml01n83Fby1n83-uRy1m9k83-Zy83-uPy1mln1n83-uRy1m83Sy83-uUy1ml01n83-uRy1o83Sy83-uUy1m9k83-Py83-uSy1mlo1m83-uUy1m");
    string_constant_167 = 
	    STATIC_STRING("9k83-GLy1m83-uUy1m9k83-w-y1m83-uSy83-uTy1o83-uSy1n83-uTy1m9k83vy83-uSy1nmln9l1n83-uTy1o1m9k83-GLy83Sy1m9k832dy83-6y1mmo1m83-uPy8");
    string_constant_168 = 
	    STATIC_STRING("3-uOy1o83-uPy1n83-uOy1m9k83-Zy83-uPy1nmln9l1n83-uQy1o1m9k9m1m9k83-GLy1m9k832dy83-6y1m832dyo1n83-uQy1m1m9k83-GLy83Sy1m83X*ym1n83-");
    string_constant_169 = 
	    STATIC_STRING("uQy1m1m9k83=by1m9k83-GLy1l83=by1n83-uOy1q1m9k9m1m9k835oy1m9k83-Ty83-uQy1m9k83*Iy83-ky1n83-GMyqo1n83-uOy1q1m9k9m1m9k83-GMy1m9k83-");
    string_constant_170 = 
	    STATIC_STRING("Ty83-uQy1m9k83*Iy83-ky1n83-GMyqo1n83-uOy1q1m9k9m1m9k83qLy1m9k83-Ty83-uQy1m9k83*Iy832Yy1n83-N3yqo1n83-uOy1q1m9k9m1m9k83-N3y1m9k83");
    string_constant_171 = 
	    STATIC_STRING("-Ty83-uQy1m9k83*Iy832Yy1n83-N3yqo1n83-uOy1q1m9k9m1m9k83qMy1m9k83-Ty83-uQy1m9k83*Iy83Ky1n83-w*yqo1n83-uOy1q1m9k9m1m9k83-w*y1m9k83");
    string_constant_172 = 
	    STATIC_STRING("-Ty83-uQy1m9k83*Iy83Ky1n83-w*yqo1n83-uOy1q1m9k9m1m9k83-Tcy1m9k83-Ty83-uQy1m9k83*Iy83-Tfy1n83-Tfyqo1n83-uOy1q1m9k9m1m9k83-Tfy1m9k");
    string_constant_173 = 
	    STATIC_STRING("83-Ty83-uQy1m9k83*Iy83-Tfy1n83-Tfyqo1n83-uOy1q1m9k9m1m9k83--cy1m9k83-Ty83-uQy1m9k83*Iy83i9y1n83-lEyqo1n83-uOy1q1m9k9m1m9k83-lEy1");
    string_constant_174 = 
	    STATIC_STRING("m9k83-Ty83-uQy1m9k83*Iy83i9y1n83-lEyqo1n83-uOy1q1m9k9m1m9k83--by1m9k83-Ty83-uQy1m9k83*Iy832Yy1n83-N5yqo1n83-uOy1q1m9k9m1m9k83-N5");
    string_constant_175 = 
	    STATIC_STRING("y1m9k83-Ty83-uQy1m9k83*Iy832Yy1n83-N5yqo1n83-uOy1q1m9k9m1m9k83--dy1m9k83-Ty83-uQy1m9k83*Iy83Ky1n83-w8yqo1n83-uOy1q1m9k9m1m9k83-w");
    string_constant_176 = 
	    STATIC_STRING("8y1m9k83-Ty83-uQy1m9k83*Iy83Ky1n83-w8yqo1n83-uOy1q1m9k9m1m9k83-pMy1m9k83-Ty83-uQy1m9k83*Iy83-Coy1n83-w0yqo1n83-uOy1q1m9k9m1m9k83");
    string_constant_177 = 
	    STATIC_STRING("-w0y1m9k83-Ty83-uQy1m9k83*Iy83-Coy1n83-w0yqo1n83-uOy1q1m9k9m1m9k83-oky1m9k83-Ty83-uQy1m9k83*Iy83Ky1n83-p8yqo1n83-uOy1q1m9k9m1m9k");
    string_constant_178 = 
	    STATIC_STRING("83-p8y1m9k83-Ty83-uQy1m9k83*Iy83Ky1n83-p8yqo1n83-uOy1q1m9k9m1m9k83-1my1m9k83-Ty83-uQy1m9k83*Iy83p2y1n83-w5yqo1n83-uOy1q1m9k9m1m9");
    string_constant_179 = 
	    STATIC_STRING("k83-w5y1m9k83-Ty83-uQy1m9k83*Iy83p2y1n83-w5yqo1n83-uOy1q1m9k9m1m9k83-1ly1m9k83-Ty83-uQy1m9k83*Iy83p-y1n83-N4yqo1n83-uOy1q1m9k9m1");
    string_constant_180 = 
	    STATIC_STRING("m9k83-N4y1m9k83-Ty83-uQy1m9k83*Iy83p-y1n83-N4yqo1n83-uOy1q1m9k9m1m9k83-cCy1m9k83-Ty83-uQy1m9k83*Iy83Ky1n83-w1yqo1n83-uOy1q1m9k9m");
    string_constant_181 = 
	    STATIC_STRING("1m9k83-w1y1m9k83-Ty83-uQy1m9k83*Iy83Ky1n83-w1yqo1n83-uOy1q1m9k9m1m9k83-lAy1m9k83-Ty83-uQy1m9k83*Iy83-9wy1n83-w4yqo1n83-uOy1q1m9k");
    string_constant_182 = 
	    STATIC_STRING("9m1m9k83-w4y1m9k83-Ty83-uQy1m9k83*Iy83-9wy1n83-w4yqo1n83-uOy1q1m9k9m1m9k83-l7y1m9k83-Ty83-uQy1m9k83*Iy83p1y1n83-w=yqo1n83-uOy1q1");
    string_constant_183 = 
	    STATIC_STRING("m9k9m1m9k83-w=y1m9k83-Ty83-uQy1m9k83*Iy83p1y1n83-w=yqo1n83-uOy1q1m9k9m1m9k83-l9y1m9k83-Ty83-uQy1m9k83*Iy83oxy1n83-w3yqo1n83-uOy1");
    string_constant_184 = 
	    STATIC_STRING("q1m9k9m1m9k83-w3y1m9k83-Ty83-uQy1m9k83*Iy83oxy1n83-w3yqo1n83-uOy1q1m9k9m1m9k83-GNy1m9k83-Ty83-uQy1m9k83*Iy83-GNy1n83-GNyqo1n83-u");
    string_constant_185 = 
	    STATIC_STRING("Oy1q1m9k9m1m9k83-w6y1m9k83-Ty83-uQy1m9k83*Iy83Ky1n83-w6yqo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(list(20,
	    string_constant_166,string_constant_167,string_constant_168,
	    string_constant_169,string_constant_170,string_constant_171,
	    string_constant_172,string_constant_173,string_constant_174,
	    string_constant_175,string_constant_176,string_constant_177,
	    string_constant_178,string_constant_179,string_constant_180,
	    string_constant_181,string_constant_182,string_constant_183,
	    string_constant_184,string_constant_185)));
    string_constant_186 = 
	    STATIC_STRING("13Wy1n83Fay1m1m9k83=Yy1m9k83-t*y1m001n83Fay1o1m9k83=Yy1m9k83-t*y1m9k83-Zy83-uNy1m0o1m83-uNy83-uMy1o83-uNy1n83-uMy1m9k83-Zy83-uNy");
    string_constant_187 = 
	    STATIC_STRING("1nmln9l1n83-uMy1o1m9k9m1m9k83-t3y1m9k83*Iy83-ky1n83-t3yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83qLy1m9k83*Iy832Yy1n83-N0yo1l83-Cxy1n83-uMy");
    string_constant_188 = 
	    STATIC_STRING("1o1m9k9m1m9k83-N0y1m9k83*Iy832Yy1n83-N0yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83qMy1m9k83*Iy83Ky1n83-t0yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-t");
    string_constant_189 = 
	    STATIC_STRING("0y1m9k83*Iy83Ky1n83-t0yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83--cy1m9k83*Iy83i9y1n83-lDyo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-lDy1m9k83*Iy83i9");
    string_constant_190 = 
	    STATIC_STRING("y1n83-lDyo1l83-Cxy1n83-uMy1o1m9k9m1m9k83--by1m9k83*Iy832Yy1n83-N1yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-N1y1m9k83*Iy832Yy1n83-N1yo1l83");
    string_constant_191 = 
	    STATIC_STRING("-Cxy1n83-uMy1o1m9k9m1m9k83--dy1m9k83*Iy83Ky1n83-t9yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-t9y1m9k83*Iy83Ky1n83-t9yo1l83-Cxy1n83-uMy1o1m");
    string_constant_192 = 
	    STATIC_STRING("9k9m1m9k83-1ly1m9k83*Iy832Yy1n83-N2yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-N2y1m9k83*Iy832Yy1n83-N2yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-t8y");
    string_constant_193 = 
	    STATIC_STRING("1m9k83*Iy83-F*y1n83-t2yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-t2y1m9k83*Iy83-F*y1n83-t2yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-c9y1m9k83*Iy83-");
    string_constant_194 = 
	    STATIC_STRING("F-y1n83-F-yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-F-y1m9k83*Iy83-F-y1n83-F-yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-1my1m9k83*Iy83p*y1n83-t6yo1");
    string_constant_195 = 
	    STATIC_STRING("l83-Cxy1n83-uMy1o1m9k9m1m9k83-t6y1m9k83*Iy83p*y1n83-t6yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-m=y1m9k83*Iy83Ky1n83-t4yo1l83-Cxy1n83-uMy");
    string_constant_196 = 
	    STATIC_STRING("1o1m9k9m1m9k83-t4y1m9k83*Iy83Ky1n83-t4yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-J0y1m9k83*Iy83Ky1n83-t=yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-t");
    string_constant_197 = 
	    STATIC_STRING("=y1m9k83*Iy83Ky1n83-t=yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-bgy1m9k83*Iy83-FIy1n83-t5yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-t5y1m9k83*Iy83-");
    string_constant_198 = 
	    STATIC_STRING("FIy1n83-t5yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-bhy1m9k83*Iy83Ky1n83-t1yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-t1y1m9k83*Iy83Ky1n83-t1yo1l83");
    string_constant_199 = 
	    STATIC_STRING("-Cxy1n83-uMy1o1m9k9m1m9k8300y1m9k9n83=Qy1n83-t7yo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-t7y1m9k9n83=Qy1n83-t7yo1l83-Cxy1n83-uMy1o1m9k9m1");
    string_constant_200 = 
	    STATIC_STRING("m9k83-Shy1m9k83*Iy83oty1n83-Shyo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-tcy1m9k83*Iy83p0y1n83-tcyo1l83-Cxy1n83-uMy1o1m9k9m1m9k83-Pwy1m9k8");
    string_constant_201 = STATIC_STRING("3*Iy83p=y1n83-Pwyo1l83-Cxy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(list(16,
	    string_constant_186,string_constant_187,string_constant_188,
	    string_constant_189,string_constant_190,string_constant_191,
	    string_constant_192,string_constant_193,string_constant_194,
	    string_constant_195,string_constant_196,string_constant_197,
	    string_constant_198,string_constant_199,string_constant_200,
	    string_constant_201)));
    string_constant_202 = 
	    STATIC_STRING("13Ky1n83FZy83-uHy1ml01n83FZy1n83-uHy1m9k83-Zy83-uFy1mln1n83-uHy1m83Sy83-uKy1ml01n83-uHy1o83Sy83-uKy1m9k83-Py83-uIy1mlo1m83-uKy1m");
    string_constant_203 = 
	    STATIC_STRING("9k83-93y1m83-uKy1m9k83-jFy1m83-uIy83-uJy1o83-uIy1n83-uJy1m9k83vy83-uIy1nmln9l1n83-uJy1o1m9k83-93y83Sy1m9k832dy83-6y1mmo1m83-uFy8");
    string_constant_204 = 
	    STATIC_STRING("3-uEy1o83-uFy1n83-uEy1m9k83-Zy83-uFy1nmln9l1n83-uGy1o1m9k9m1m9k83-93y1m9k832dy83-6y1m832dyo1n83-uGy1m1m9k83-93y83Sy1m83X*ym1n83-");
    string_constant_205 = 
	    STATIC_STRING("uGy1m1m9k83=by1m9k83-93y1l83=by1n83-uEy1q1m9k9m1m9k835oy1m9k83-Ty83-uGy1m9k83*Iy83-ky1n83-94yqo1n83-uEy1q1m9k9m1m9k83-94y1m9k83-");
    string_constant_206 = 
	    STATIC_STRING("Ty83-uGy1m9k83*Iy83-ky1n83-94yqo1n83-uEy1q1m9k9m1m9k83-dqy1m9k83-Ty83-uGy1m9k83*Iy83ovy1n83-jGyqo1n83-uEy1q1m9k9m1m9k83-jGy1m9k8");
    string_constant_207 = 
	    STATIC_STRING("3-Ty83-uGy1m9k83*Iy83ovy1n83-jGyqo1n83-uEy1q1m9k9m1m9k83-dsy1m9k83-Ty83-uGy1m9k83*Iy83owy1n83-jHyqo1n83-uEy1q1m9k9m1m9k83-jHy1m9");
    string_constant_208 = 
	    STATIC_STRING("k83-Ty83-uGy1m9k83*Iy83owy1n83-jHyqo1n83-uEy1q1m9k9m1m9k83-dpy1m9k83-Ty83-uGy1m9k83*Iy832Yy1n83-jDyqo1n83-uEy1q1m9k9m1m9k83-jDy1");
    string_constant_209 = 
	    STATIC_STRING("m9k83-Ty83-uGy1m9k83*Iy832Yy1n83-jDyqo1n83-uEy1q1m9k9m1m9k83-dty1m9k83-Ty83-uGy1m9k83*Iy83Ky1n83-jLyqo1n83-uEy1q1m9k9m1m9k83-jLy");
    string_constant_210 = 
	    STATIC_STRING("1m9k83-Ty83-uGy1m9k83*Iy83Ky1n83-jLyqo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(list(9,
	    string_constant_202,string_constant_203,string_constant_204,
	    string_constant_205,string_constant_206,string_constant_207,
	    string_constant_208,string_constant_209,string_constant_210)));
    string_constant_211 = 
	    STATIC_STRING("13Jy1n83FVy83-twy1ml01n83FVy1n83-twy1m9k83-Zy83-tuy1mln1n83-twy1m83Sy83-u-y1ml01n83-twy1o83Sy83-u-y1m9k83-Py83-txy1mlo1m83-u-y1m");
    string_constant_212 = 
	    STATIC_STRING("9k83t+y1m83-u-y1m9k83-OCy1m83-txy83-u+y1o83-txy1n83-u+y1m9k83vy83-txy1nmln9l1n83-u+y1o1m9k83t+y83Sy1m9k832dy83-6y1mmo1m83-tuy83-");
    string_constant_213 = 
	    STATIC_STRING("tty1o83-tuy1n83-tty1m9k83-Zy83-tuy1nmln9l1n83-tvy1o1m9k9m1m9k83t+y1m9k832dy83-6y1m832dyo1n83-tvy1m1m9k83t+y83Sy1m83X*ym1n83-tvy1");
    string_constant_214 = 
	    STATIC_STRING("m1m9k83=by1m9k83t+y1l83=by1n83-tty1q1m9k9m1m9k835oy1m9k83-Ty83-tvy1m9k83*Iy83-ky1n83t-yqo1n83-tty1q1m9k9m1m9k83t-y1m9k83-Ty83-tv");
    string_constant_215 = 
	    STATIC_STRING("y1m9k83*Iy83-ky1n83t-yqo1n83-tty1q1m9k9m1m9k83-OHy1m9k83-Ty83-tvy1m9k83*Iy83p+y1n83-OHyqo1n83-tty1q1m9k9m1m9k83-OGy1m9k83-Ty83-t");
    string_constant_216 = 
	    STATIC_STRING("vy1m9k9n83Sy1n83-OGyqo1n83-tty1q1m9k9m1m9k83-ODy1m9k83-Ty83-tvy1m9k83*Iy83ouy1n83-OFyqo1n83-tty1q1m9k9m1m9k83-OFy1m9k83-Ty83-tvy");
    string_constant_217 = 
	    STATIC_STRING("1m9k83*Iy83ouy1n83-OFyqo1n83-tty1q1m9k9m1m9k83-OEy1m9k83-Ty83-tvy1m9k83*Iy832Yy1n83-OEyqo1n83-tty1q1m9k9m1m9k83-OJy1m9k83-Ty83-t");
    string_constant_218 = 
	    STATIC_STRING("vy1m9k83*Iy83Ky1n83-OIyqo1n83-tty1q1m9k9m1m9k83-OIy1m9k83-Ty83-tvy1m9k83*Iy83Ky1n83-OIyqo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(list(8,
	    string_constant_211,string_constant_212,string_constant_213,
	    string_constant_214,string_constant_215,string_constant_216,
	    string_constant_217,string_constant_218)));
    string_constant_219 = 
	    STATIC_STRING("13Jy1n83FXy1m1m9k83=Yy1m9k83FWy1m001n83FXy1o1m9k83=Yy1m9k83FWy1m9k83-Zy83-u=y1m0o1m83-u=y83-u*y1o83-u=y1n83-u*y1m9k83-Zy83-u=y1n");
    string_constant_220 = 
	    STATIC_STRING("mln9l1n83-u*y1o1m9k9m1m9k83-u0y1m9k83*Iy83-ky1n83-u0yo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-tQy1m9k83*Iy83-FHy1n83-u2yo1l83-Cxy1n83-u*y");
    string_constant_221 = 
	    STATIC_STRING("1o1m9k9m1m9k83-u2y1m9k83*Iy83-FHy1n83-u2yo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-tPy1m9k83*Iy832Yy1n83-u1yo1l83-Cxy1n83-u*y1o1m9k9m1m9k8");
    string_constant_222 = 
	    STATIC_STRING("3-u1y1m9k83*Iy832Yy1n83-u1yo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-tRy1m9k83*Iy83Ky1n83-u3yo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-u3y1m9k83*Iy8");
    string_constant_223 = 
	    STATIC_STRING("3Ky1n83-u3yo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-cVy1m9k83*Iy83-FHy1n83-FHyo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-FHy1m9k83*Iy83-FHy1n83-FHyo");
    string_constant_224 = 
	    STATIC_STRING("1l83-Cxy1n83-u*y1o1m9k9m1m9k83-cTy1m9k83*Iy83-FGy1n83-u4yo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-u4y1m9k83*Iy83-FGy1n83-u4yo1l83-Cxy1n83");
    string_constant_225 = 
	    STATIC_STRING("-u*y1o1m9k9m1m9k83-cWy1m9k83*Iy83Ky1n83-u5yo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-u5y1m9k83*Iy83Ky1n83-u5yo1l83-Cxy1n83-u*y1o1m9k9m1m9k");
    string_constant_226 = 
	    STATIC_STRING("83-Pty1m9k83*Iy832Yy1n83-Ptyo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-Puy1m9k83*Iy832Yy1n83-Puyo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-Pvy1m9k83*I");
    string_constant_227 = 
	    STATIC_STRING("y83Ky1n83-Pvyo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-i+y1m9k83*Iy832Yy1n83-i+yo1l83-Cxy1n83-u*y1o1m9k9m1m9k83-i-y1m9k83*Iy832Yy1n83-i-yo");
    string_constant_228 = 
	    STATIC_STRING("1l83-Cxy1n83-u*y1o1m9k9m1m9k83-i*y1m9k83*Iy83Ky1n83-i*yo1l83-Cxy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(list(10,
	    string_constant_219,string_constant_220,string_constant_221,
	    string_constant_222,string_constant_223,string_constant_224,
	    string_constant_225,string_constant_226,string_constant_227,
	    string_constant_228)));
    Qtrend_chart_plots_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-PLOTS-GRAMMAR-SPEC",AB_package);
    Qcompile_trend_chart_plots_grammar_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-TREND-CHART-PLOTS-GRAMMAR-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_trend_chart_plots_grammar_spec_for_slot,
	    STATIC_FUNCTION(compile_trend_chart_plots_grammar_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtrend_chart_plots_grammar_spec,
	    SYMBOL_FUNCTION(Qcompile_trend_chart_plots_grammar_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtrend_chart_plots_grammar_spec,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtrend_chart_value_axes_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-VALUE-AXES-GRAMMAR-SPEC",AB_package);
    Qcompile_trend_chart_value_axes_grammar_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-TREND-CHART-VALUE-AXES-GRAMMAR-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_trend_chart_value_axes_grammar_spec_for_slot,
	    STATIC_FUNCTION(compile_trend_chart_value_axes_grammar_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtrend_chart_value_axes_grammar_spec,
	    SYMBOL_FUNCTION(Qcompile_trend_chart_value_axes_grammar_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtrend_chart_value_axes_grammar_spec,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtrend_chart_time_axis_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-TIME-AXIS-GRAMMAR-SPEC",AB_package);
    Qcompile_trend_chart_time_axis_grammar_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-TREND-CHART-TIME-AXIS-GRAMMAR-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_trend_chart_time_axis_grammar_spec_for_slot,
	    STATIC_FUNCTION(compile_trend_chart_time_axis_grammar_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtrend_chart_time_axis_grammar_spec,
	    SYMBOL_FUNCTION(Qcompile_trend_chart_time_axis_grammar_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtrend_chart_time_axis_grammar_spec,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtrend_chart_point_formats_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-POINT-FORMATS-GRAMMAR-SPEC",AB_package);
    Qcompile_trend_chart_point_formats_grammar_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-TREND-CHART-POINT-FORMATS-GRAMMAR-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_trend_chart_point_formats_grammar_spec_for_slot,
	    STATIC_FUNCTION(compile_trend_chart_point_formats_grammar_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtrend_chart_point_formats_grammar_spec,
	    SYMBOL_FUNCTION(Qcompile_trend_chart_point_formats_grammar_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtrend_chart_point_formats_grammar_spec,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtrend_chart_connector_formats_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-CONNECTOR-FORMATS-GRAMMAR-SPEC",
	    AB_package);
    Qcompile_trend_chart_connector_formats_grammar_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-TREND-CHART-CONNECTOR-FORMATS-GRAMMAR-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_trend_chart_connector_formats_grammar_spec_for_slot,
	    STATIC_FUNCTION(compile_trend_chart_connector_formats_grammar_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtrend_chart_connector_formats_grammar_spec,
	    SYMBOL_FUNCTION(Qcompile_trend_chart_connector_formats_grammar_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtrend_chart_connector_formats_grammar_spec,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtrend_chart_format_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-FORMAT-GRAMMAR-SPEC",AB_package);
    Qcompile_trend_chart_format_grammar_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-TREND-CHART-FORMAT-GRAMMAR-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_trend_chart_format_grammar_spec_for_slot,
	    STATIC_FUNCTION(compile_trend_chart_format_grammar_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtrend_chart_format_grammar_spec,
	    SYMBOL_FUNCTION(Qcompile_trend_chart_format_grammar_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtrend_chart_format_grammar_spec,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_trend_chart_plots_grammar_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-TREND-CHART-PLOTS-GRAMMAR-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_trend_chart_plots_grammar_spec_from_slot,
	    STATIC_FUNCTION(write_trend_chart_plots_grammar_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtrend_chart_plots_grammar_spec,
	    SYMBOL_FUNCTION(Qwrite_trend_chart_plots_grammar_spec_from_slot),
	    Qslot_value_writer);
    Qwrite_trend_chart_value_axes_grammar_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-TREND-CHART-VALUE-AXES-GRAMMAR-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_trend_chart_value_axes_grammar_spec_from_slot,
	    STATIC_FUNCTION(write_trend_chart_value_axes_grammar_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtrend_chart_value_axes_grammar_spec,
	    SYMBOL_FUNCTION(Qwrite_trend_chart_value_axes_grammar_spec_from_slot),
	    Qslot_value_writer);
    Qwrite_trend_chart_time_axis_grammar_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-TREND-CHART-TIME-AXIS-GRAMMAR-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_trend_chart_time_axis_grammar_spec_from_slot,
	    STATIC_FUNCTION(write_trend_chart_time_axis_grammar_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtrend_chart_time_axis_grammar_spec,
	    SYMBOL_FUNCTION(Qwrite_trend_chart_time_axis_grammar_spec_from_slot),
	    Qslot_value_writer);
    Qwrite_trend_chart_point_formats_grammar_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-TREND-CHART-POINT-FORMATS-GRAMMAR-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_trend_chart_point_formats_grammar_spec_from_slot,
	    STATIC_FUNCTION(write_trend_chart_point_formats_grammar_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtrend_chart_point_formats_grammar_spec,
	    SYMBOL_FUNCTION(Qwrite_trend_chart_point_formats_grammar_spec_from_slot),
	    Qslot_value_writer);
    Qwrite_trend_chart_connector_formats_grammar_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-TREND-CHART-CONNECTOR-FORMATS-GRAMMAR-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_trend_chart_connector_formats_grammar_spec_from_slot,
	    STATIC_FUNCTION(write_trend_chart_connector_formats_grammar_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtrend_chart_connector_formats_grammar_spec,
	    SYMBOL_FUNCTION(Qwrite_trend_chart_connector_formats_grammar_spec_from_slot),
	    Qslot_value_writer);
    Qwrite_trend_chart_format_grammar_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-TREND-CHART-FORMAT-GRAMMAR-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_trend_chart_format_grammar_spec_from_slot,
	    STATIC_FUNCTION(write_trend_chart_format_grammar_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtrend_chart_format_grammar_spec,
	    SYMBOL_FUNCTION(Qwrite_trend_chart_format_grammar_spec_from_slot),
	    Qslot_value_writer);
    Qmultiple = STATIC_SYMBOL("MULTIPLE",AB_package);
    Qsingle = STATIC_SYMBOL("SINGLE",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qmultiple,Qsingle);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qput_trend_chart_plots = STATIC_SYMBOL("PUT-TREND-CHART-PLOTS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_trend_chart_plots,
	    STATIC_FUNCTION(put_trend_chart_plots,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qtrend_chart_plots,
	    SYMBOL_FUNCTION(Qput_trend_chart_plots),Qslot_putter);
    Qput_trend_chart_value_axes = 
	    STATIC_SYMBOL("PUT-TREND-CHART-VALUE-AXES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_trend_chart_value_axes,
	    STATIC_FUNCTION(put_trend_chart_value_axes,NIL,FALSE,3,3));
    mutate_global_property(Qtrend_chart_value_axes,
	    SYMBOL_FUNCTION(Qput_trend_chart_value_axes),Qslot_putter);
    Qput_trend_chart_time_axis = STATIC_SYMBOL("PUT-TREND-CHART-TIME-AXIS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_trend_chart_time_axis,
	    STATIC_FUNCTION(put_trend_chart_time_axis,NIL,FALSE,3,3));
    mutate_global_property(Qtrend_chart_time_axis,
	    SYMBOL_FUNCTION(Qput_trend_chart_time_axis),Qslot_putter);
    Qput_trend_chart_point_formats = 
	    STATIC_SYMBOL("PUT-TREND-CHART-POINT-FORMATS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_trend_chart_point_formats,
	    STATIC_FUNCTION(put_trend_chart_point_formats,NIL,FALSE,3,3));
    mutate_global_property(Qtrend_chart_point_formats,
	    SYMBOL_FUNCTION(Qput_trend_chart_point_formats),Qslot_putter);
    Qput_trend_chart_connector_formats = 
	    STATIC_SYMBOL("PUT-TREND-CHART-CONNECTOR-FORMATS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_trend_chart_connector_formats,
	    STATIC_FUNCTION(put_trend_chart_connector_formats,NIL,FALSE,3,3));
    mutate_global_property(Qtrend_chart_connector_formats,
	    SYMBOL_FUNCTION(Qput_trend_chart_connector_formats),Qslot_putter);
    Qput_trend_chart_format = STATIC_SYMBOL("PUT-TREND-CHART-FORMAT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_trend_chart_format,
	    STATIC_FUNCTION(put_trend_chart_format,NIL,FALSE,3,3));
    mutate_global_property(Qtrend_chart_format,
	    SYMBOL_FUNCTION(Qput_trend_chart_format),Qslot_putter);
    Qtrend_chart_pane_tree = STATIC_SYMBOL("TREND-CHART-PANE-TREE",AB_package);
    Qreclaim_trend_chart_pane_tree_value = 
	    STATIC_SYMBOL("RECLAIM-TREND-CHART-PANE-TREE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_trend_chart_pane_tree_value,
	    STATIC_FUNCTION(reclaim_trend_chart_pane_tree_value,NIL,FALSE,
	    2,2));
    mutate_global_property(Qtrend_chart_pane_tree,
	    SYMBOL_FUNCTION(Qreclaim_trend_chart_pane_tree_value),
	    Qslot_value_reclaimer);
    list_constant_243 = STATIC_CONS(Qplot,Qtrend_chart_plots);
    list_constant_244 = STATIC_CONS(Qvalue_axis,Qtrend_chart_value_axes);
    list_constant_245 = STATIC_CONS(Qtime_axis,Qtrend_chart_time_axis);
    list_constant_246 = STATIC_CONS(Qpoint_format,Qtrend_chart_point_formats);
    list_constant_247 = STATIC_CONS(Qconnector_format,
	    Qtrend_chart_connector_formats);
    list_constant_248 = STATIC_CONS(Qtrend_chart_format,Qtrend_chart_format);
    list_constant_249 = STATIC_LIST((SI_Long)6L,list_constant_243,
	    list_constant_244,list_constant_245,list_constant_246,
	    list_constant_247,list_constant_248);
    Trend_chart_component_type_slot_name_map = list_constant_249;
    Qslot_component = STATIC_SYMBOL("SLOT-COMPONENT",AB_package);
    Qdefaulting_total_timespan = STATIC_SYMBOL("DEFAULTING-TOTAL-TIMESPAN",
	    AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    array_constant_39 = STATIC_ARRAY(list_constant_46,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)20L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)22L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)24L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)27L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)29L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)30L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)32L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)36L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)38L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)39L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)40L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)41L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)42L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)43L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)44L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)46L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)47L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)51L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)52L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)53L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)54L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)55L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)56L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)57L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)62L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)63L,(SI_Long)57344L);
    write_defaulting_total_timespan_note_1 = 
	    STATIC_FUNCTION(write_defaulting_total_timespan_note,NIL,FALSE,
	    2,2);
    mutate_global_property(Qdefaulting_total_timespan,
	    write_defaulting_total_timespan_note_1,Qframe_note_writer_1);
    Qreserved_word_p = STATIC_SYMBOL("RESERVED-WORD-P",AB_package);
    string_constant_55 = STATIC_STRING("~a is a reserved symbol");
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qany = STATIC_SYMBOL("ANY",AB_package);
    Qnumbered = STATIC_SYMBOL("NUMBERED",AB_package);
    Qname_or_names = STATIC_SYMBOL("NAME-OR-NAMES",AB_package);
}
