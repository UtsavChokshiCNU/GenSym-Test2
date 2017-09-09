/* prntng.c
 * Input file:  printing.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "prntng.h"


/* UPDATE-FRAME-STATUS-AND-NOTES-FOR-BLOCK */
Object update_frame_status_and_notes_for_block(block)
    Object block;
{
    x_note_fn_call(96,0);
    return VALUES_1(Nil);
}

static Object list_constant;       /* # */

static Object Qtruth_value;        /* truth-value */

/* YES-OR-NO-EVALUATION-SETTER */
Object yes_or_no_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,1);
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
			      Qtruth_value,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_yes_or_no_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = evaluation_truth_value_is_true_p(evaluation_value);
  end_yes_or_no_evaluation_setter:
    return result;
}

/* YES-OR-NO-EVALUATION-GETTER */
Object yes_or_no_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(96,2);
    GENSYM_RETURN_ONE(slot_value ? Evaluation_true_value : 
	    Evaluation_false_value);
    return VALUES_1(Nil);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

/* LINEAR-UNIT-OF-LENGTH-EVALUATION-SETTER */
Object linear_unit_of_length_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,3);
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
		      goto end_linear_unit_of_length_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_linear_unit_of_length_evaluation_setter:
    return result;
}

/* LINEAR-UNIT-OF-LENGTH-EVALUATION-GETTER */
Object linear_unit_of_length_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(96,4);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object Qfloat_array;        /* float-array */

static Object Qunits;              /* units */

/* LINEAR-DISTANCE-EVALUATION-SETTER */
Object linear_distance_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, value, new_long;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,5);
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
			  list_constant_3))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_4,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_linear_distance_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    value = evaluation_value_value(estructure_slot(gensymed_symbol,Qnumber,
	    Nil));
    if (FIXNUMP(value))
	temp_1 = value;
    else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	new_long = allocate_managed_long_box();
	aref_new_value = INTEGER_TO_INT64(value);
	set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
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
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_float_array_conses_tail_vector,
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
    result = phrase_list_2(temp_1,estructure_slot(gensymed_symbol,Qunits,Nil));
  end_linear_distance_evaluation_setter:
    return result;
}

/* LINEAR-DISTANCE-EVALUATION-GETTER */
Object linear_distance_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, x, temp, amf_available_array_cons_qm, amf_array;
    Object temp_1, temp_2, amf_result, new_float;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(96,6);
    if (slot_value) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	x = CAR(slot_value);
	if (FIXNUMP(x))
	    temp = x;
	else if (INLINE_LONG_P(x) != (SI_Long)0L) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		temp = make_evaluation_long(aref1(x,FIX((SI_Long)0L)));
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
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
		aref_new_value = DFLOAT_ISAREF_1(x,(SI_Long)0L);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp = new_float;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	set_evaluation_structure_slot(gensymed_symbol,Qnumber,temp);
	set_evaluation_structure_slot(gensymed_symbol,Qunits,CADR(slot_value));
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object Qlinear_distance;    /* linear-distance */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qwidth;              /* width */

static Object Qheight;             /* height */

static Object Qcustom;             /* custom */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "~NT " */

static Object string_constant_1;   /* "~NV must be one of the following types: ~a" */

/* PAPER-SIZE-KIND-EVALUATION-SETTER */
Object paper_size_kind_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,7);
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
			  list_constant_5))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_6,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_paper_size_kind_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7)) {
	gensymed_symbol = evaluation_value;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = estructure_slot(gensymed_symbol,Qwidth,Nil);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp = parse_result_or_bad_phrase;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,Qheight,Nil);
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	result = phrase_list_3(Qcustom,temp,temp_1);
    }
    else if (type_specification_type_p(gensymed_symbol,Qsymbol))
	result = VALUES_1(evaluation_value);
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
		  tformat(2,string_constant,list_constant_7);
		  tformat(2,string_constant,Qsymbol);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_1,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_paper_size_kind_evaluation_setter:
    return result;
}

/* PAPER-SIZE-KIND-EVALUATION-GETTER */
Object paper_size_kind_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4;

    x_note_fn_call(96,8);
    if (SYMBOLP(slot_value))
	temp = slot_value;
    else {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CADR(slot_value);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qwidth,temp);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CADDR(slot_value);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qheight,temp);
	temp = gensymed_symbol;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

static Object Qpaper_size_kind;    /* paper-size-kind */

static Object Qpaper_size;         /* paper-size */

static Object Qpaper_orientation;  /* paper-orientation */

static Object Qleft_margin;        /* left-margin */

static Object Qtop_margin;         /* top-margin */

static Object Qright_margin;       /* right-margin */

static Object Qbottom_margin;      /* bottom-margin */

/* PRINTER-PAGE-LAYOUT-EVALUATION-SETTER */
Object printer_page_layout_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, gensymed_symbol_1;
    Object gensymed_symbol_2, category_evaluator_interface, function;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object gensymed_symbol_6, gensymed_symbol_7, parse_result_or_bad_phrase;
    Object error_string_qm, car_new_value, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,9);
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
		      goto end_printer_page_layout_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7)) {
	gensymed_symbol = evaluation_value;
	gensymed_symbol_1 = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_2 = gensymed_symbol_1;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpaper_size_kind),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_3 = function;
	    gensymed_symbol_4 = estructure_slot(gensymed_symbol,
		    Qpaper_size,Nil);
	    gensymed_symbol_5 = Nil;
	    gensymed_symbol_6 = Nil;
	    gensymed_symbol_7 = Nil;
	    result = inline_funcall_4(gensymed_symbol_3,gensymed_symbol_4,
		    gensymed_symbol_5,gensymed_symbol_6,gensymed_symbol_7);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	car_new_value = phrase_cons(Qpaper_size,temp_1);
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	car_new_value = phrase_cons(Qpaper_orientation,
		estructure_slot(gensymed_symbol,Qpaper_orientation,Nil));
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_3 = function;
	    gensymed_symbol_4 = estructure_slot(gensymed_symbol,
		    Qleft_margin,Nil);
	    gensymed_symbol_5 = Nil;
	    gensymed_symbol_6 = Nil;
	    gensymed_symbol_7 = Nil;
	    result = inline_funcall_4(gensymed_symbol_3,gensymed_symbol_4,
		    gensymed_symbol_5,gensymed_symbol_6,gensymed_symbol_7);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	car_new_value = phrase_cons(Qleft_margin,temp_1);
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_3 = function;
	    gensymed_symbol_4 = estructure_slot(gensymed_symbol,
		    Qtop_margin,Nil);
	    gensymed_symbol_5 = Nil;
	    gensymed_symbol_6 = Nil;
	    gensymed_symbol_7 = Nil;
	    result = inline_funcall_4(gensymed_symbol_3,gensymed_symbol_4,
		    gensymed_symbol_5,gensymed_symbol_6,gensymed_symbol_7);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	car_new_value = phrase_cons(Qtop_margin,temp_1);
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_3 = function;
	    gensymed_symbol_4 = estructure_slot(gensymed_symbol,
		    Qright_margin,Nil);
	    gensymed_symbol_5 = Nil;
	    gensymed_symbol_6 = Nil;
	    gensymed_symbol_7 = Nil;
	    result = inline_funcall_4(gensymed_symbol_3,gensymed_symbol_4,
		    gensymed_symbol_5,gensymed_symbol_6,gensymed_symbol_7);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	car_new_value = phrase_cons(Qright_margin,temp_1);
	M_CAR(gensymed_symbol_2) = car_new_value;
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_3 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,
		    Qbottom_margin,Nil);
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    gensymed_symbol_6 = Nil;
	    result = inline_funcall_4(gensymed_symbol_3,gensymed_symbol,
		    gensymed_symbol_4,gensymed_symbol_5,gensymed_symbol_6);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	car_new_value = phrase_cons(Qbottom_margin,temp_1);
	M_CAR(gensymed_symbol_2) = car_new_value;
	result = VALUES_1(gensymed_symbol_1);
      end_safe_category_setter_calling_block:;
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
		  tformat(2,string_constant,list_constant_7);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_1,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_printer_page_layout_evaluation_setter:
    return result;
}

/* PRINTER-PAGE-LAYOUT-EVALUATION-GETTER */
Object printer_page_layout_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, temp, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4;

    x_note_fn_call(96,10);
    if (slot_value) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpaper_size_kind),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    temp = assq_function(Qpaper_size,slot_value);
	    gensymed_symbol_2 = CDR(temp);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qpaper_size,temp);
	temp = assq_function(Qpaper_orientation,slot_value);
	set_evaluation_structure_slot(gensymed_symbol,Qpaper_orientation,
		CDR(temp));
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    temp = assq_function(Qleft_margin,slot_value);
	    gensymed_symbol_2 = CDR(temp);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qleft_margin,temp);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    temp = assq_function(Qtop_margin,slot_value);
	    gensymed_symbol_2 = CDR(temp);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qtop_margin,temp);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    temp = assq_function(Qright_margin,slot_value);
	    gensymed_symbol_2 = CDR(temp);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qright_margin,temp);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    temp = assq_function(Qbottom_margin,slot_value);
	    gensymed_symbol_2 = CDR(temp);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qbottom_margin,temp);
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

/* KIND-OF-SCALING-EVALUATION-SETTER */
Object kind_of_scaling_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,11);
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
		      goto end_kind_of_scaling_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7)) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    result = VALUES_1(parse_result_or_bad_phrase);
    }
    else if (type_specification_type_p(gensymed_symbol,Qsymbol))
	result = VALUES_1(evaluation_value);
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
		  tformat(2,string_constant,list_constant_7);
		  tformat(2,string_constant,Qsymbol);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_1,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_kind_of_scaling_evaluation_setter:
    return result;
}

/* KIND-OF-SCALING-EVALUATION-GETTER */
Object kind_of_scaling_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(96,12);
    if (SYMBOLP(slot_value))
	temp = slot_value;
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlinear_distance),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

static Object Qkind_of_scaling;    /* kind-of-scaling */

static Object Qworkspace_scaling;  /* workspace-scaling */

static Object Qcolor_conversion;   /* color-conversion */

/* PRINTER-TRANSLATION-DETAILS-EVALUATION-SETTER */
Object printer_translation_details_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,13);
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
		      goto end_printer_translation_details_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7)) {
	gensymed_symbol = evaluation_value;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qkind_of_scaling),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = estructure_slot(gensymed_symbol,
		    Qworkspace_scaling,Nil);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	temp_1 = phrase_cons(Qworkspace_scaling,temp_1);
	result = phrase_list_2(temp_1,phrase_cons(Qcolor_conversion,
		estructure_slot(gensymed_symbol,Qcolor_conversion,Nil)));
      end_safe_category_setter_calling_block:;
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
		  tformat(2,string_constant,list_constant_7);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_1,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_printer_translation_details_evaluation_setter:
    return result;
}

/* PRINTER-TRANSLATION-DETAILS-EVALUATION-GETTER */
Object printer_translation_details_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, temp, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4;

    x_note_fn_call(96,14);
    if (slot_value) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qkind_of_scaling),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    temp = assq_function(Qworkspace_scaling,slot_value);
	    gensymed_symbol_2 = CDR(temp);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qworkspace_scaling,temp);
	temp = assq_function(Qcolor_conversion,slot_value);
	set_evaluation_structure_slot(gensymed_symbol,Qcolor_conversion,
		CDR(temp));
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_14;    /* # */

static Object list_constant_15;    /* # */

static Object Qspooled_filename_template;  /* spooled-filename-template */

static Object Qyes_or_no;          /* yes-or-no */

static Object Qspool_file_to_printer;  /* spool-file-to-printer */

static Object Qprinter_identification;  /* printer-identification */

/* PRINTER-SPOOLING-DETAILS-EVALUATION-SETTER */
Object printer_spooling_details_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,15);
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
		      goto end_printer_spooling_details_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7)) {
	gensymed_symbol = evaluation_value;
	temp = phrase_cons(Qspooled_filename_template,
		copy_for_phrase(estructure_slot(gensymed_symbol,
		Qspooled_filename_template,Nil)));
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qyes_or_no),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = estructure_slot(gensymed_symbol,
		    Qspool_file_to_printer,Nil);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	temp_1 = phrase_cons(Qspool_file_to_printer,temp_1);
	result = phrase_list_3(temp,temp_1,
		phrase_cons(Qprinter_identification,
		copy_for_phrase(estructure_slot(gensymed_symbol,
		Qprinter_identification,Nil))));
      end_safe_category_setter_calling_block:;
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
		  tformat(2,string_constant,list_constant_7);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_1,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_printer_spooling_details_evaluation_setter:
    return result;
}

/* PRINTER-SPOOLING-DETAILS-EVALUATION-GETTER */
Object printer_spooling_details_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, temp, evaluation_value;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(96,16);
    if (slot_value) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	temp = assq_function(Qspooled_filename_template,slot_value);
	evaluation_value = CDR(temp);
	set_evaluation_structure_slot(gensymed_symbol,
		Qspooled_filename_template,FIXNUMP(evaluation_value) || 
		evaluation_value && SYMBOLP(evaluation_value) ? 
		evaluation_value : copy_evaluation_value_1(evaluation_value));
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qyes_or_no),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    temp = assq_function(Qspool_file_to_printer,slot_value);
	    gensymed_symbol_2 = CDR(temp);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,
		Qspool_file_to_printer,temp);
	temp = assq_function(Qprinter_identification,slot_value);
	evaluation_value = CDR(temp);
	set_evaluation_structure_slot(gensymed_symbol,
		Qprinter_identification,FIXNUMP(evaluation_value) || 
		evaluation_value && SYMBOLP(evaluation_value) ? 
		evaluation_value : copy_evaluation_value_1(evaluation_value));
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_16;    /* # */

static Object list_constant_17;    /* # */

static Object Qencapsulated_postscript;  /* encapsulated-postscript */

static Object Qeps;                /* eps */

/* PRINTING-FILE-FORMAT-EVALUATION-SETTER */
Object printing_file_format_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,17);
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
		      goto end_printing_file_format_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qencapsulated_postscript))
	result = VALUES_1(Qeps);
    else
	result = VALUES_1(evaluation_value);
  end_printing_file_format_evaluation_setter:
    return result;
}

/* PRINTING-FILE-FORMAT-EVALUATION-GETTER */
Object printing_file_format_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(96,18);
    GENSYM_RETURN_ONE(EQ(slot_value,Qeps) ? Qencapsulated_postscript : 
	    slot_value);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Printer_setup, Qprinter_setup);

/* INITIALIZE-FOR-PRINTER-SETUP */
Object initialize_for_printer_setup(printer_setup)
    Object printer_setup;
{
    Object frame, sub_vector_qm, method_function_qm, function_qm;
    SI_Long index_1, ab_loop_bind_, method_index;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,19);
    PUSH_SPECIAL_WITH_SYMBOL(Printer_setup,Qprinter_setup,printer_setup,0);
      frame = Printer_setup;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)2L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qprinter_setup)) {
	  method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	  goto end_1;
      }
      index_1 = index_1 + (SI_Long)2L;
      goto next_loop;
    end_loop:
      method_function_qm = Qnil;
    end_1:;
      if (method_function_qm)
	  inline_funcall_1(method_function_qm,frame);
      method_index = (SI_Long)19L;
      frame = Printer_setup;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),method_index);
      function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
      if (function_qm)
	  result = inline_funcall_1(function_qm,frame);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qprinting_details;   /* printing-details */

/* PUT-PRINTING-DETAILS */
Object put_printing_details(printer_setup_instance,new_value,gensymed_symbol)
    Object printer_setup_instance, new_value, gensymed_symbol;
{
    Object frame, sub_vector_qm, function_qm;
    SI_Long method_index;

    x_note_fn_call(96,20);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(printer_setup_instance,Qprinting_details);
    SVREF(printer_setup_instance,FIX((SI_Long)22L)) = new_value;
    if (system_table_installed_p(printer_setup_instance)) {
	method_index = (SI_Long)19L;
	frame = printer_setup_instance;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),method_index);
	function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
	if (function_qm)
	    inline_funcall_1(function_qm,frame);
    }
    return VALUES_1(new_value);
}

static Object Qpage_layout;        /* page-layout */

/* PUT-PAGE-LAYOUT */
Object put_page_layout(printer_setup_instance,new_value,gensymed_symbol)
    Object printer_setup_instance, new_value, gensymed_symbol;
{
    Object frame, sub_vector_qm, function_qm;
    SI_Long method_index;

    x_note_fn_call(96,21);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(printer_setup_instance,Qpage_layout);
    SVREF(printer_setup_instance,FIX((SI_Long)23L)) = new_value;
    if (system_table_installed_p(printer_setup_instance)) {
	method_index = (SI_Long)19L;
	frame = printer_setup_instance;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),method_index);
	function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
	if (function_qm)
	    inline_funcall_1(function_qm,frame);
    }
    return VALUES_1(new_value);
}

/* PUT-PRINT-SPOOLING */
Object put_print_spooling(printer_setup_instance,new_value,gensymed_symbol)
    Object printer_setup_instance, new_value, gensymed_symbol;
{
    Object frame, sub_vector_qm, function_qm;
    SI_Long method_index;

    x_note_fn_call(96,22);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(printer_setup_instance,Qprint_spooling);
    SVREF(printer_setup_instance,FIX((SI_Long)24L)) = new_value;
    if (system_table_installed_p(printer_setup_instance)) {
	method_index = (SI_Long)19L;
	frame = printer_setup_instance;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),method_index);
	function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
	if (function_qm)
	    inline_funcall_1(function_qm,frame);
    }
    return VALUES_1(new_value);
}

/* INSTALL-SYSTEM-TABLE-FOR-PRINTER-SETUP */
Object install_system_table_for_printer_setup(printer_setup)
    Object printer_setup;
{
    Object frame, sub_vector_qm, function_qm;
    SI_Long method_index;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,23);
    PUSH_SPECIAL_WITH_SYMBOL(Printer_setup,Qprinter_setup,printer_setup,0);
      if (system_table_installed_p(Printer_setup)) {
	  method_index = (SI_Long)19L;
	  frame = Printer_setup;
	  sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		  (SI_Long)11L),method_index);
	  function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) :
		   Nil;
	  if (function_qm)
	      result = inline_funcall_1(function_qm,frame);
	  else
	      result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-PRINTER-SETUP */
Object deinstall_system_table_for_printer_setup(printer_setup)
    Object printer_setup;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(96,24);
    PUSH_SPECIAL_WITH_SYMBOL(Printer_setup,Qprinter_setup,printer_setup,0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Native_printer_information, Qnative_printer_information);

/* PRINTER-SETUP-PARTICULAR */
Object printer_setup_particular(key)
    Object key;
{
    Object temp;

    x_note_fn_call(96,25);
    temp = assq_function(key,ISVREF(Printer_setup,(SI_Long)22L));
    if (temp);
    else
	temp = assq_function(key,Native_printer_information);
    if (temp);
    else
	temp = assq_function(key,ISVREF(Printer_setup,(SI_Long)23L));
    if (temp);
    else
	temp = assq_function(key,ISVREF(Printer_setup,(SI_Long)24L));
    return VALUES_1(CDR(temp));
}

static Object Qx_dpi;              /* x-dpi */

static Object float_constant;      /* 0.0 */

static Object Qy_dpi;              /* y-dpi */

static Object Qphysical_width;     /* physical-width */

static Object Qphysical_height;    /* physical-height */

static Object Qx_offset;           /* x-offset */

static Object Qy_offset;           /* y-offset */

static Object Qprinter;            /* printer */

static Object Qquality;            /* quality */

static Object Qfrom_page;          /* from-page */

static Object Qto_page;            /* to-page */

static Object list_constant_18;    /* # */

static Object Qab_pathname;        /* pathname */

static Object Qportrait;           /* portrait */

static Object Qfull_color;         /* full-color */

static Object Qinch;               /* inch */

static Object Qpaper_margins;      /* paper-margins */

/* COMPUTE-NATIVE-PRINTER-INFORMATION */
Object compute_native_printer_information(plist)
    Object plist;
{
    Object x_dpi, y_dpi, physical_width, physical_height, width, height;
    Object x_offset, y_offset, printer, quality, from_page, to_page, margin;
    Object ab_loop_list_, value_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object requested_margins, pathname_qm, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1, amf_available_array_cons_qm, amf_array, temp_4;
    Object amf_result, new_float, lm, tm, rm, bm;
    double temp_2, temp_3, physical_width_inches, physical_height_inches;
    double aref_new_value;

    x_note_fn_call(96,26);
    x_dpi = lfloat(getf(plist,Qx_dpi,_),float_constant);
    y_dpi = lfloat(getf(plist,Qy_dpi,_),float_constant);
    physical_width = getf(plist,Qphysical_width,_);
    physical_height = getf(plist,Qphysical_height,_);
    width = getf(plist,Qwidth,_);
    height = getf(plist,Qheight,_);
    x_offset = getf(plist,Qx_offset,_);
    y_offset = getf(plist,Qy_offset,_);
    printer = getf(plist,Qprinter,_);
    quality = getf(plist,Qquality,_);
    from_page = getf(plist,Qfrom_page,_);
    to_page = getf(plist,Qto_page,_);
    margin = Nil;
    ab_loop_list_ = list_constant_18;
    value_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    margin = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    value_qm = getf(plist,margin,_);
    if (value_qm) {
	ab_loopvar__2 = slot_value_cons_1(slot_value_cons_1(margin,
		copy_list_using_slot_value_conses_1(value_qm)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    requested_margins = ab_loopvar_;
    goto end_1;
    requested_margins = Qnil;
  end_1:;
    pathname_qm = getf(plist,Qab_pathname,_);
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)8L));
    gensymed_symbol_1 = gensymed_symbol;
    temp = slot_value_cons_1(Qpaper_orientation,Qportrait);
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = slot_value_cons_1(Qcolor_conversion,Qfull_color);
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = slot_value_cons_1(Qquality,quality);
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = slot_value_cons_1(Qprinter_identification,
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(printer) != (SI_Long)0L ? 
	    copy_text_string(printer) : printer);
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = slot_value_cons_1(Qfrom_page,from_page);
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = slot_value_cons_1(Qto_page,to_page);
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp_1 = lfloat(physical_width,float_constant);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(x_dpi);
    physical_width_inches = temp_2 / temp_3;
    temp_1 = lfloat(physical_height,float_constant);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(y_dpi);
    physical_height_inches = temp_2 / temp_3;
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_4 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_4;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,physical_width_inches);
    temp_1 = slot_value_list_2(new_float,Qinch);
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_4 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_4;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,physical_height_inches);
    temp = slot_value_cons_1(Qpaper_size,slot_value_list_3(Qcustom,temp_1,
	    slot_value_list_2(new_float,Qinch)));
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_4 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_4;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
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
    temp_1 = lfloat(x_offset,float_constant);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(x_dpi);
    aref_new_value = temp_2 / temp_3;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    lm = new_float;
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_4 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_4;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
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
    temp_1 = lfloat(y_offset,float_constant);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(y_dpi);
    aref_new_value = temp_2 / temp_3;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    tm = new_float;
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_4 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_4;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
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
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(x_dpi);
    aref_new_value = (double)IFIX(FIXNUM_MINUS(FIXNUM_MINUS(physical_width,
	    width),x_offset)) / temp_3;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    rm = new_float;
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_4 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_4;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp,temp_4) = amf_available_array_cons_qm;
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
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(y_dpi);
    aref_new_value = 
	    (double)IFIX(FIXNUM_MINUS(FIXNUM_MINUS(physical_height,height),
	    y_offset)) / temp_3;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    bm = new_float;
    temp = slot_value_cons_1(Qpaper_margins,
	    slot_value_list_4(slot_value_list_2(lm,Qinch),
	    slot_value_list_2(tm,Qinch),slot_value_list_2(rm,Qinch),
	    slot_value_list_2(bm,Qinch)));
    M_CAR(gensymed_symbol_1) = temp;
    return VALUES_1(nconc2(gensymed_symbol,nconc2(pathname_qm ? 
	    slot_value_cons_1(slot_value_cons_1(Qab_pathname,
	    copy_text_string(pathname_qm)),Nil) : Nil,requested_margins)));
}

/* GENERATE-EPS-P */
Object generate_eps_p()
{
    x_note_fn_call(96,27);
    return VALUES_1(EQ(ISVREF(Printer_setup,(SI_Long)26L),Qeps) ? T : Nil);
}

static Object Qjpeg;               /* jpeg */

/* GENERATE-BITMAP-P */
Object generate_bitmap_p varargs_1(int, n)
{
    Object plist;
    Declare_varargs_nonrelocating;

    x_note_fn_call(96,28);
    INIT_ARGS_nonrelocating();
    plist = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if (plist)
	return VALUES_1(EQ(getf(plist,Qprinter,_),Qjpeg) ? T : Nil);
    else
	return VALUES_1(EQ(ISVREF(Printer_setup,(SI_Long)26L),Qjpeg) ? T : 
		Nil);
}

/* PRINTER-WORKSPACE-SCALING */
Object printer_workspace_scaling()
{
    x_note_fn_call(96,29);
    return printer_setup_particular(Qworkspace_scaling);
}

static Object string_constant_2;   /* "the filename template for the spooled file is not in a valid format" */

/* WRITE-PRINTER-FILE-TEMPLATE-IS-MISFORMED-NOTE */
Object write_printer_file_template_is_misformed_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(96,30);
    GENSYM_RETURN_ONE(tformat(1,string_constant_2));
    return VALUES_1(Nil);
}

static Object string_constant_3;   /* "the requested printer is not the default printer for this machine" */

/* WRITE-PRINTER-IS-NOT-DEFAULT-PRINTER-NOTE */
Object write_printer_is_not_default_printer_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(96,31);
    GENSYM_RETURN_ONE(tformat(1,string_constant_3));
    return VALUES_1(Nil);
}

static Object string_constant_4;   /* "since the printer identification is unknown, printed output will be left in the spooled output file" */

/* WRITE-PRINTER-NO-PRINTER-SPECIFIED-NOTE */
Object write_printer_no_printer_specified_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(96,32);
    GENSYM_RETURN_ONE(tformat(1,string_constant_4));
    return VALUES_1(Nil);
}

static Object string_constant_5;   /* "the requested printer is not one of the known printers for this host" */

/* WRITE-PRINTER-IS-UNKNOWN-NOTE */
Object write_printer_is_unknown_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(96,33);
    GENSYM_RETURN_ONE(tformat(1,string_constant_5));
    return VALUES_1(Nil);
}

static Object string_constant_6;   /* "small margins are often not supported by printers" */

/* WRITE-PRINTER-SMALL-MARGIN-ARE-IGNORED-NOTE */
Object write_printer_small_margin_are_ignored_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(96,34);
    GENSYM_RETURN_ONE(tformat(1,string_constant_6));
    return VALUES_1(Nil);
}

static Object string_constant_7;   /* "the requested paper size is out of range or otherwise unattainable e.g. due to too wide margins" */

/* WRITE-PRINTER-PAPER-SIZE-IS-UNREASONABLE-NOTE */
Object write_printer_paper_size_is_unreasonable_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(96,35);
    GENSYM_RETURN_ONE(tformat(1,string_constant_7));
    return VALUES_1(Nil);
}

static Object string_constant_8;   /* "" */

/* WRITE-PRINTER-ONLY-BLACK-AND-WHITE-IS-SUPPORTED-NOTE */
Object write_printer_only_black_and_white_is_supported_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(96,36);
    GENSYM_RETURN_ONE(tformat(1,string_constant_8));
    return VALUES_1(Nil);
}

/* WRITE-PRINTER-UNIMPLEMENTED-PAGE-LAYOUT-SETTINGS-NOTE */
Object write_printer_unimplemented_page_layout_settings_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(96,37);
    GENSYM_RETURN_ONE(tformat(1,string_constant_8));
    return VALUES_1(Nil);
}

static Object string_constant_9;   /* "unable to spool output directly to the printer on this machine, ~
				    *             you will have to transmit the file to the printer by some means outside of G2"
				    */

/* WRITE-PRINTER-G2-CAN-NOT-SPOOL-OUTPUT-ON-THIS-PLATFORM-NOTE */
Object write_printer_g2_can_not_spool_output_on_this_platform_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(96,38);
    GENSYM_RETURN_ONE(tformat(1,string_constant_9));
    return VALUES_1(Nil);
}

static Object list_constant_19;    /* # */

static Object list_constant_20;    /* # */

static Object Qprinter_small_margin_are_ignored;  /* printer-small-margin-are-ignored */

static Object list_constant_21;    /* # */

static Object list_constant_22;    /* # */

static Object Qprinter_paper_size_is_unreasonable;  /* printer-paper-size-is-unreasonable */

/* UPDATE-FRAME-STATUS-AND-NOTES-FOR-PRINTER-SETUP */
Object update_frame_status_and_notes_for_printer_setup(printer_setup)
    Object printer_setup;
{
    Object frame_note_kind, ab_loop_list_, small_margin_mf;
    Object particular_margin_name, particular_margin_value_mf, flag, result_1;
    Object paper_size, small_mf, large_mf, slot_value_number, temp_1;
    Object dimension_1_mf, dimension_2_mf, paper_size_info;
    Object actual_paper_width_mf, actual_paper_height_mf, paper_width_mf;
    Object paper_height_mf, left_margin_mf, top_margin_mf, right_margin_mf;
    Object bottom_margin_mf, page_width_mf, page_height_mf, one_inch_mf;
    char temp, paper_orientation_is_portrait;
    double arg, arg_1, arg_2;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(96,39);
    PUSH_SPECIAL_WITH_SYMBOL(Printer_setup,Qprinter_setup,printer_setup,0);
      frame_note_kind = Nil;
      ab_loop_list_ = list_constant_19;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      frame_note_kind = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      delete_frame_note_if_any(frame_note_kind,Printer_setup);
      goto next_loop;
    end_loop:;
      if (ISVREF(Printer_setup,(SI_Long)23L)) {
	  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	      small_margin_mf = 
		      postscript_convert_linear_distance_to_postscript_units_mf(1,
		      list_constant_20);
	      particular_margin_name = Nil;
	      ab_loop_list_ = list_constant_18;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      particular_margin_name = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      particular_margin_value_mf = 
		      postscript_convert_linear_distance_to_postscript_units_mf(1,
		      printer_setup_particular(particular_margin_name));
	      arg = DFLOAT_ISAREF_1(particular_margin_value_mf,(SI_Long)0L);
	      arg_1 = DFLOAT_ISAREF_1(small_margin_mf,(SI_Long)0L);
	      flag = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		      !inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
	      reclaim_managed_simple_float_array_of_length_1(particular_margin_value_mf);
	      if (flag) {
		  result_1 = T;
		  goto end_1;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      result_1 = Qnil;
	    end_1:;
	      reclaim_managed_simple_float_array_of_length_1(small_margin_mf);
	      temp = TRUEP(result_1);
	  }
	  POP_LOCAL_ALLOCATION(0,0);
	  if (temp)
	      add_frame_note(5,Qprinter_small_margin_are_ignored,
		      Printer_setup,T,T,Nil);
	  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	      paper_size = printer_setup_particular(Qpaper_size);
	      if (CONSP(paper_size)) {
		  small_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  list_constant_21);
		  large_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  list_constant_22);
		  slot_value_number = SECOND(paper_size);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			  == (SI_Long)1L)
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			  == (SI_Long)1L)
		      temp_1 = aref1(slot_value_number,FIX((SI_Long)0L));
		  else
		      temp_1 = slot_value_number;
		  dimension_1_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  temp_1);
		  slot_value_number = THIRD(paper_size);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			  == (SI_Long)1L)
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			  == (SI_Long)1L)
		      temp_1 = aref1(slot_value_number,FIX((SI_Long)0L));
		  else
		      temp_1 = slot_value_number;
		  dimension_2_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  temp_1);
		  arg = DFLOAT_ISAREF_1(small_mf,(SI_Long)0L);
		  arg_1 = DFLOAT_ISAREF_1(dimension_1_mf,(SI_Long)0L);
		  arg_2 = DFLOAT_ISAREF_1(large_mf,(SI_Long)0L);
		  if (arg < arg_1 && arg_1 < arg_2 &&  
			  !inline_nanp_for_comparison(arg) &&  
			  !inline_nanp_for_comparison(arg_1) &&  
			  !inline_nanp_for_comparison(arg_2)) {
		      arg = DFLOAT_ISAREF_1(small_mf,(SI_Long)0L);
		      arg_1 = DFLOAT_ISAREF_1(dimension_2_mf,(SI_Long)0L);
		      arg_2 = DFLOAT_ISAREF_1(large_mf,(SI_Long)0L);
		      temp = arg < arg_1 && arg_1 < arg_2 &&  
			      !inline_nanp_for_comparison(arg) &&  
			      !inline_nanp_for_comparison(arg_1) ?  
			      !inline_nanp_for_comparison(arg_2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  temp_1 =  !temp ? T : Nil;
		  reclaim_managed_simple_float_array_of_length_1(small_mf);
		  reclaim_managed_simple_float_array_of_length_1(large_mf);
		  reclaim_managed_simple_float_array_of_length_1(dimension_1_mf);
		  reclaim_managed_simple_float_array_of_length_1(dimension_2_mf);
		  temp = TRUEP(temp_1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp);
	      else {
		  paper_orientation_is_portrait = 
			  EQ(printer_setup_particular(Qpaper_orientation),
			  Qportrait);
		  paper_size_info = postscript_paper_size_info(paper_size);
		  actual_paper_width_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  FIRST(paper_size_info));
		  actual_paper_height_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  SECOND(paper_size_info));
		  paper_width_mf = paper_orientation_is_portrait ? 
			  actual_paper_width_mf : actual_paper_height_mf;
		  paper_height_mf = paper_orientation_is_portrait ? 
			  actual_paper_height_mf : actual_paper_width_mf;
		  left_margin_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  printer_setup_particular(Qleft_margin));
		  top_margin_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  printer_setup_particular(Qtop_margin));
		  right_margin_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  printer_setup_particular(Qright_margin));
		  bottom_margin_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  printer_setup_particular(Qbottom_margin));
		  page_width_mf = 
			  postscript_remove_margins_from_dimension(paper_width_mf,
			  left_margin_mf,right_margin_mf);
		  page_height_mf = 
			  postscript_remove_margins_from_dimension(paper_height_mf,
			  top_margin_mf,bottom_margin_mf);
		  one_inch_mf = 
			  postscript_convert_linear_distance_to_postscript_units_mf(1,
			  list_constant_21);
		  arg = DFLOAT_ISAREF_1(page_width_mf,(SI_Long)0L);
		  arg_1 = DFLOAT_ISAREF_1(one_inch_mf,(SI_Long)0L);
		  temp_1 = arg < arg_1 &&  
			  !inline_nanp_for_comparison(arg) ? ( 
			  !inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
		  if (temp_1);
		  else {
		      arg = DFLOAT_ISAREF_1(page_height_mf,(SI_Long)0L);
		      arg_1 = DFLOAT_ISAREF_1(one_inch_mf,(SI_Long)0L);
		      temp_1 = arg < arg_1 &&  
			      !inline_nanp_for_comparison(arg) ? ( 
			      !inline_nanp_for_comparison(arg_1) ? T : 
			      Nil) : Qnil;
		  }
		  reclaim_managed_simple_float_array_of_length_1(actual_paper_width_mf);
		  reclaim_managed_simple_float_array_of_length_1(actual_paper_height_mf);
		  reclaim_managed_simple_float_array_of_length_1(left_margin_mf);
		  reclaim_managed_simple_float_array_of_length_1(top_margin_mf);
		  reclaim_managed_simple_float_array_of_length_1(right_margin_mf);
		  reclaim_managed_simple_float_array_of_length_1(bottom_margin_mf);
		  reclaim_managed_simple_float_array_of_length_1(page_width_mf);
		  reclaim_managed_simple_float_array_of_length_1(page_height_mf);
		  reclaim_managed_simple_float_array_of_length_1(one_inch_mf);
		  temp = TRUEP(temp_1);
	      }
	  }
	  POP_LOCAL_ALLOCATION(0,0);
	  if (temp)
	      add_frame_note(5,Qprinter_paper_size_is_unreasonable,
		      Printer_setup,T,T,Nil);
      }
      if (ISVREF(Printer_setup,(SI_Long)24L))
	  result = semantic_check_spooling_parameters();
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* POSTSCRIPT-PAPER-SIZE-NAME */
Object postscript_paper_size_name(paper_size)
    Object paper_size;
{
    x_note_fn_call(96,40);
    if (ATOM(paper_size))
	return VALUES_1(paper_size);
    else
	return VALUES_1(FIRST(paper_size));
}

/* POSTSCRIPT-PAPER-SIZE-INFO */
Object postscript_paper_size_info(paper_size)
    Object paper_size;
{
    Object temp;

    x_note_fn_call(96,41);
    if (SYMBOLP(paper_size)) {
	temp = assq_function(paper_size,Postscript_paper_sizes);
	temp = CDR(temp);
    }
    else if (CONSP(paper_size))
	temp = CDR(paper_size);
    else
	temp = Qnil;
    if (temp)
	return VALUES_1(temp);
    else {
	temp = FIRST(Postscript_paper_sizes);
	return VALUES_1(CDR(temp));
    }
}

Object Postscript_paper_margins = UNBOUND;

/* POSTSCRIPT-PAPER-MARGINS-INFO */
Object postscript_paper_margins_info(paper_size)
    Object paper_size;
{
    Object temp;

    x_note_fn_call(96,42);
    temp = assq_function(Qpaper_margins,Native_printer_information);
    temp = CDR(temp);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(Postscript_paper_margins);
}

static Object list_constant_23;    /* # */

/* POSTSCRIPT-CORRECT-GRAMMAR-OF-LINEAR-DISTANCE */
Object postscript_correct_grammar_of_linear_distance(value,units)
    Object value, units;
{
    Object names, temp, singular, plural, ab_loop_list_, ab_loop_desetq_;
    char singular_p;

    x_note_fn_call(96,43);
    names = list_constant_23;
    temp = FIX((SI_Long)1L);
    singular_p = NUM_EQ(temp,value);
    singular = Nil;
    plural = Nil;
    ab_loop_list_ = names;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    singular = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    plural = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(units,singular) || EQ(units,plural)) {
	if (singular_p)
	    return VALUES_1(singular);
	else
	    return VALUES_1(plural);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(units);
    return VALUES_1(Qnil);
}

static Object string_constant_10;  /* "Workspace scale must be between 5 and 25000." */

/* COMPILE-PRINTER-TRANSLATION-DETAILS-FOR-SLOT */
Object compile_printer_translation_details_for_slot varargs_1(int, n)
{
    Object parse, gensymed_symbol, gensymed_symbol_1;
    Object workspace_scaling, temp, scale_as_phrase_number_qm;
    Object error_message_qm, scale_as_lisp_number;
    char temp_1;
    double arg, arg_1, arg_2;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(96,44);
    INIT_ARGS_nonrelocating();
    parse = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    workspace_scaling = assq_function(Qworkspace_scaling,parse);
    temp = CDR(workspace_scaling);
    scale_as_phrase_number_qm = CONSP(temp) ? SECOND(workspace_scaling) : Nil;
    error_message_qm = Nil;
    if (scale_as_phrase_number_qm) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(scale_as_phrase_number_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(scale_as_phrase_number_qm)) 
		    == (SI_Long)1L)
		scale_as_lisp_number = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(scale_as_phrase_number_qm,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(scale_as_phrase_number_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(scale_as_phrase_number_qm)) 
		    == (SI_Long)1L)
		scale_as_lisp_number = aref1(scale_as_phrase_number_qm,
			FIX((SI_Long)0L));
	    else
		scale_as_lisp_number = scale_as_phrase_number_qm;
	    temp_1 = INTEGERP(scale_as_lisp_number) ? (SI_Long)5L <= 
		    IFIX(scale_as_lisp_number) && 
		    IFIX(scale_as_lisp_number) <= (SI_Long)25000L : 
		    TRUEP(Qnil);
	    if (temp_1);
	    else if (FLOATP(scale_as_lisp_number)) {
		arg = 5.0;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(scale_as_lisp_number);
		arg_2 = 25000.0;
		temp_1 = arg <= arg_1 && arg_1 <= arg_2 &&  
			!inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1) ?  
			!inline_nanp_for_comparison(arg_2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1)
		error_message_qm = copy_text_string(string_constant_10);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    if (error_message_qm)
	return VALUES_2(Bad_phrase,error_message_qm);
    else
	return VALUES_1(parse);
}

static Object string_constant_11;  /* ";~%" */

static Object Kfirst;              /* :first */

static Object string_constant_12;  /* "~A:" */

static Object list_constant_24;    /* # */

static Object string_constant_13;  /* "~( ~S~)" */

static Object string_constant_14;  /* "~( ~d ~s by ~d ~s~)" */

static Object string_constant_15;  /* " ~S" */

static Object string_constant_16;  /* " yes" */

static Object string_constant_17;  /* " no" */

static Object Qlinear_measure;     /* linear-measure */

static Object string_constant_18;  /* " ~(~S ~S~)" */

static Object string_constant_19;  /* "~( ~S workspace units per ~S~)" */

/* WRITE-PRINTER-SETUP-SLOT */
Object write_printer_setup_slot(slot_value_alist)
    Object slot_value_alist;
{
    Object key, value, ab_loop_list_, wrote_initial_statement;
    Object ab_loop_iter_flag_, ab_loop_desetq_, key_string, temp;
    Object gensymed_symbol, gensymed_symbol_1, n1, d1, n2, d2;
    Object slot_value_number;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(96,45);
    key = Nil;
    value = Nil;
    ab_loop_list_ = slot_value_alist;
    wrote_initial_statement = Nil;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    key = CAR(ab_loop_desetq_);
    value = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	wrote_initial_statement = T;
    if (wrote_initial_statement)
	tformat(1,string_constant_11);
    key_string = copy_symbol_name(3,key,Kfirst,T);
    tformat(2,string_constant_12,key_string);
    reclaim_text_string(key_string);
    temp = getf(list_constant_24,key,_);
    if (EQ(temp,Qsymbol))
	tformat(2,string_constant_13,value);
    else if (EQ(temp,Qpaper_size)) {
	if (SYMBOLP(value))
	    tformat(2,string_constant_13,value);
	else {
	    gensymed_symbol = value;
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol_1 = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    n1 = CAR(gensymed_symbol_1);
	    gensymed_symbol_1 = CDR(gensymed_symbol_1);
	    d1 = CAR(gensymed_symbol_1);
	    gensymed_symbol = CAR(gensymed_symbol);
	    n2 = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    d2 = CAR(gensymed_symbol);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(n1) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(n1)) == (SI_Long)1L)
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(n1,(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(n1) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(n1)) == (SI_Long)1L)
		temp = aref1(n1,FIX((SI_Long)0L));
	    else
		temp = n1;
	    d1 = postscript_correct_grammar_of_linear_distance(temp,d1);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(n2) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(n2)) == (SI_Long)1L)
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(n2,(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(n2) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(n2)) == (SI_Long)1L)
		temp = aref1(n2,FIX((SI_Long)0L));
	    else
		temp = n2;
	    d2 = postscript_correct_grammar_of_linear_distance(temp,d2);
	    tformat(5,string_constant_14,n1,d1,n2,d2);
	}
    }
    else if (EQ(temp,Qstring))
	tformat(2,string_constant_15,value);
    else if (EQ(temp,Qyes_or_no))
	tformat(1,value ? string_constant_16 : string_constant_17);
    else if (EQ(temp,Qlinear_measure)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    slot_value_number = FIRST(value);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		temp = aref1(slot_value_number,FIX((SI_Long)0L));
	    else
		temp = slot_value_number;
	    tformat(3,string_constant_18,temp,SECOND(value));
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else if (EQ(temp,Qworkspace_scaling)) {
	if (SYMBOLP(value))
	    tformat(2,string_constant_13,value);
	else if (LISTP(value)) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		slot_value_number = FIRST(value);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			== (SI_Long)1L)
		    temp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			== (SI_Long)1L)
		    temp = aref1(slot_value_number,FIX((SI_Long)0L));
		else
		    temp = slot_value_number;
		tformat(3,string_constant_19,temp,SECOND(value));
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qinches;             /* inches */

static Object Qin;                 /* in */

static Object float_constant_1;    /* 1.0 */

static Object Qfoot;               /* foot */

static Object Qfeet;               /* feet */

static Object Qft;                 /* ft */

static Object float_constant_2;    /* 12.0 */

static Object Qmeter;              /* meter */

static Object Qmeters;             /* meters */

static Object float_constant_3;    /* 39.37 */

static Object Qcentimeter;         /* centimeter */

static Object Qcentimeters;        /* centimeters */

static Object Qab_cm;              /* cm */

static Object float_constant_4;    /* 0.3937 */

static Object Qmillimeter;         /* millimeter */

static Object Qmillimeters;        /* millimeters */

static Object Qmm;                 /* mm */

static Object float_constant_5;    /* 0.03937 */

/* POSTSCRIPT-CONVERT-LINEAR-DISTANCE-TO-POSTSCRIPT-UNITS-MF */
Object postscript_convert_linear_distance_to_postscript_units_mf varargs_1(int, n)
{
    Object linear_distance;
    Object inverse, gensymed_symbol, x, units, temp, units_multiplier;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float;
    double temp_3, temp_4, aref_new_value;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(96,46);
    INIT_ARGS_nonrelocating();
    linear_distance = REQUIRED_ARG_nonrelocating();
    inverse = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = linear_distance;
	x = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	units = CAR(gensymed_symbol);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,(SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
	    temp = aref1(x,FIX((SI_Long)0L));
	else
	    temp = x;
	x = lfloat(temp,float_constant);
	if (EQ(units,Qinch) || EQ(units,Qinches) || EQ(units,Qin))
	    units_multiplier = float_constant_1;
	else if (EQ(units,Qfoot) || EQ(units,Qfeet) || EQ(units,Qft))
	    units_multiplier = float_constant_2;
	else if (EQ(units,Qmeter) || EQ(units,Qmeters))
	    units_multiplier = float_constant_3;
	else if (EQ(units,Qcentimeter) || EQ(units,Qcentimeters) || 
		EQ(units,Qab_cm))
	    units_multiplier = float_constant_4;
	else if (EQ(units,Qmillimeter) || EQ(units,Qmillimeters) || 
		EQ(units,Qmm))
	    units_multiplier = float_constant_5;
	else
	    units_multiplier = float_constant_1;
	if (inverse) {
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
	    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(x);
	    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(units_multiplier);
	    aref_new_value = 72.0 * (1.0 / temp_3) * temp_4;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    result = VALUES_1(new_float);
	}
	else {
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
	    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(x);
	    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(units_multiplier);
	    aref_new_value = 72.0 * temp_3 * temp_4;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    result = VALUES_1(new_float);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-PRINTER-TRANSLATION-DETAILS-FROM-SLOT */
Object write_printer_translation_details_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(96,47);
    return write_printer_setup_slot(slot_value);
}

/* WRITE-PRINTER-PAGE-LAYOUT-FROM-SLOT */
Object write_printer_page_layout_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(96,48);
    return write_printer_setup_slot(slot_value);
}

/* WRITE-PRINTER-SPOOLING-DETAILS-FROM-SLOT */
Object write_printer_spooling_details_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(96,49);
    return write_printer_setup_slot(slot_value);
}

static Object Qpostscript;         /* postscript */

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

/* WRITE-PRINTING-FILE-FORMAT-FROM-SLOT */
Object write_printing_file_format_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(96,50);
    if (EQ(slot_value,Qpostscript))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)10L));
    else if (EQ(slot_value,Qeps))
	return twrite_beginning_of_wide_string(array_constant_1,
		FIX((SI_Long)23L));
    else if (EQ(slot_value,Qjpeg))
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)4L));
    else
	return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Print_spooling, Qprint_spooling);

DEFINE_VARIABLE_WITH_SYMBOL(Printing_in_progress_p, Qprinting_in_progress_p);

DEFINE_VARIABLE_WITH_SYMBOL(Printing_format, Qprinting_format);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_window_for_printing, Qgensym_window_for_printing);

DEFINE_VARIABLE_WITH_SYMBOL(Output_window_for_printing_qm, Qoutput_window_for_printing_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Bitmap_for_printing_qm, Qbitmap_for_printing_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Printing_pass_number, Qprinting_pass_number);

DEFINE_VARIABLE_WITH_SYMBOL(Last_postscript_composite_object_index, Qlast_postscript_composite_object_index);

DEFINE_VARIABLE_WITH_SYMBOL(Postscript_composite_object_mapping, Qpostscript_composite_object_mapping);

DEFINE_VARIABLE_WITH_SYMBOL(Fonts_used_in_print_job, Qfonts_used_in_print_job);

DEFINE_VARIABLE_WITH_SYMBOL(Kanji_fonts_used_in_print_job, Qkanji_fonts_used_in_print_job);

DEFINE_VARIABLE_WITH_SYMBOL(Fonts_needing_corresponding_kanji_font, Qfonts_needing_corresponding_kanji_font);

DEFINE_VARIABLE_WITH_SYMBOL(Postscript_object_mapping_for_graph_renderings, Qpostscript_object_mapping_for_graph_renderings);

DEFINE_VARIABLE_WITH_SYMBOL(Postscript_object_mapping_for_icon_renderings, Qpostscript_object_mapping_for_icon_renderings);

DEFINE_VARIABLE_WITH_SYMBOL(Postscript_computed_variables_mapping, Qpostscript_computed_variables_mapping);

DEFINE_VARIABLE_WITH_SYMBOL(Postscript_printing_icon_renderings, Qpostscript_printing_icon_renderings);

DEFINE_VARIABLE_WITH_SYMBOL(Postscript_current_graph_line_drawing_index, Qpostscript_current_graph_line_drawing_index);

DEFINE_VARIABLE_WITH_SYMBOL(Postscript_emitting_definition, Qpostscript_emitting_definition);

DEFINE_VARIABLE_WITH_SYMBOL(Postscript_definition_operation_counter, Qpostscript_definition_operation_counter);

DEFINE_VARIABLE_WITH_SYMBOL(Printing_graph_rendering_color_list_qm, Qprinting_graph_rendering_color_list_qm);

/* PRINTING-P */
Object printing_p()
{
    x_note_fn_call(96,51);
    return VALUES_1(Printing_in_progress_p);
}

static Object Qbitmap;             /* bitmap */

/* POLYCHROME-RASTERS-FOR-GRAPHS-P */
Object polychrome_rasters_for_graphs_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(96,52);
    if (printing_p() && printing_window_p(gensym_window))
	return VALUES_1( !EQ(Printing_format,Qbitmap) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qpformat;            /* pformat */

/* PFORMAT */
Object pformat varargs_1(int, n)
{
    Object format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, text_string;
    Object ascii_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(96,53);
    INIT_ARGS_nonrelocating();
    format_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    text_string = tformat_text_string(10,format_string,arg1,arg2,arg3,arg4,
	    arg5,arg6,arg7,arg8,arg9);
    ascii_string = export_text_string(2,text_string,Qpformat);
    g2_stream_write_string(ascii_string,Printing_stream);
    reclaim_text_string(text_string);
    reclaim_text_string(ascii_string);
    return VALUES_1(Nil);
}

/* EMIT-POSTSCRIPT-RESERVE-SPACE */
Object emit_postscript_reserve_space(length_1,stream)
    Object length_1, stream;
{
    x_note_fn_call(96,54);
    if ((SI_Long)80L < IFIX(FIXNUM_ADD(Emit_postscript_line_length,
		length_1))) {
	g2_stream_terpri(stream);
	Emit_postscript_line_length = FIX((SI_Long)0L);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_20;  /* " ~a" */

static Object string_constant_21;  /* "~%g~D}def /g~D {~%" */

/* POSTSCRIPT-EMIT-OPERATOR-1 */
Object postscript_emit_operator_1(operator_name)
    Object operator_name;
{
    Object temp, subfunction_index;

    x_note_fn_call(96,55);
    pformat(2,string_constant_20,operator_name);
    postscript_emit_line_break();
    temp = add1(Postscript_definition_operation_counter);
    Postscript_definition_operation_counter = temp;
    if (Postscript_emitting_definition && (SI_Long)32L < 
	    IFIX(Postscript_definition_operation_counter)) {
	Postscript_definition_operation_counter = FIX((SI_Long)0L);
	temp = FIXNUM_ADD1(Last_postscript_composite_object_index);
	Last_postscript_composite_object_index = temp;
	subfunction_index = Last_postscript_composite_object_index;
	return pformat(3,string_constant_21,subfunction_index,
		subfunction_index);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_printing_conses, Qavailable_printing_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_printing_conses_tail, Qavailable_printing_conses_tail);

Object Available_printing_conses_vector = UNBOUND;

Object Available_printing_conses_tail_vector = UNBOUND;

Object Printing_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Printing_cons_counter, Qprinting_cons_counter);

/* OUTSTANDING-PRINTING-CONSES */
Object outstanding_printing_conses()
{
    Object temp;

    x_note_fn_call(96,56);
    temp = FIXNUM_MINUS(Printing_cons_counter,
	    length(Available_printing_conses));
    return VALUES_1(temp);
}

/* PRINTING-CONS-MEMORY-USAGE */
Object printing_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(96,57);
    temp = FIXNUM_TIMES(Printing_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-PRINTING-CONS-POOL */
Object replenish_printing_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(96,58);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qprinting_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_printing_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_printing_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_printing_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_printing_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Printing_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qprinting;           /* printing */

/* PRINTING-CONS-1 */
Object printing_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(96,59);
    new_cons = ISVREF(Available_printing_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_printing_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_printing_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_printing_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qprinting);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-PRINTING-LIST-POOL */
Object replenish_printing_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(96,60);
    conses_needed = IFIX(FIXNUM_ADD1(conses_needed_minus_one));
    temp = (conses_needed + 
	    IFIX(FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time))) / 
	    IFIX(Cons_pool_conses_to_make_at_a_time);
    new_conses_count = temp;
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,FIX(new_conses_count));
    POP_AREA(0);
    new_conses = gensymed_symbol;
    if (ISVREF(Available_printing_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_printing_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_printing_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_printing_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qprinting_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-PRINTING-LIST-1 */
Object make_printing_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(96,61);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end_1;
	gensymed_symbol_1 = Qnil;
      end_1:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	replenish_printing_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_printing_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qprinting);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_printing_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_printing_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	M_CDR(gensymed_symbol_1) = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* PRINTING-LIST-2 */
Object printing_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(96,62);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_printing_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_printing_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qprinting);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_printing_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_printing_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_printing_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_printing_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* PRINTING-LIST-3 */
Object printing_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(96,63);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_printing_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_printing_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qprinting);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_printing_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_printing_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_printing_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_printing_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* PRINTING-LIST-4 */
Object printing_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(96,64);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_printing_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_printing_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qprinting);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_printing_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_printing_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_printing_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_printing_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = fourth_1;
    return VALUES_1(gensymed_symbol);
}

/* PRINTING-LIST-TRACE-HOOK */
Object printing_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(96,65);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-PRINTING-CONSES-1 */
Object copy_tree_using_printing_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(96,66);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_printing_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_printing_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_printing_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_printing_cons_pool();
	temp_1 = copy_tree_using_printing_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qprinting);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_printing_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_printing_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_printing_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_printing_cons_pool();
	temp_1 = copy_tree_using_printing_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qprinting);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* COPY-LIST-USING-PRINTING-CONSES-1 */
Object copy_list_using_printing_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(96,67);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_printing_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_printing_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_printing_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_printing_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qprinting);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_printing_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_printing_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_printing_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_printing_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_printing_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qprinting);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-PRINTING-CONS-1 */
Object reclaim_printing_cons_1(printing_cons)
    Object printing_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(96,68);
    inline_note_reclaim_cons(printing_cons,Qprinting);
    if (ISVREF(Available_printing_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_printing_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = printing_cons;
	temp = Available_printing_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = printing_cons;
    }
    else {
	temp = Available_printing_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = printing_cons;
	temp = Available_printing_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = printing_cons;
    }
    M_CDR(printing_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-PRINTING-LIST-1 */
Object reclaim_printing_list_1(printing_list)
    Object printing_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(96,69);
    if (printing_list) {
	last_1 = printing_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qprinting);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qprinting);
	if (ISVREF(Available_printing_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_printing_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = printing_list;
	    temp = Available_printing_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_printing_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = printing_list;
	    temp = Available_printing_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-PRINTING-LIST*-1 */
Object reclaim_printing_list_star_1(printing_list)
    Object printing_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(96,70);
    if (CONSP(printing_list)) {
	temp = last(printing_list,_);
	M_CDR(temp) = Nil;
	if (printing_list) {
	    last_1 = printing_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qprinting);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qprinting);
	    if (ISVREF(Available_printing_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_printing_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = printing_list;
		temp = Available_printing_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_printing_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = printing_list;
		temp = Available_printing_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-PRINTING-TREE-1 */
Object reclaim_printing_tree_1(tree)
    Object tree;
{
    Object e, e2, printing_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(96,71);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_printing_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		printing_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(printing_cons,Qprinting);
		if (EQ(printing_cons,e))
		    goto end_1;
		else if ( !TRUEP(printing_cons))
		    goto end_1;
		else
		    printing_cons = CDR(printing_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_printing_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_printing_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_printing_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_printing_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_printing_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    M_CDR(e) = Nil;
	    goto end_loop_1;
	}
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* DELETE-PRINTING-ELEMENT-1 */
Object delete_printing_element_1(element,printing_list)
    Object element, printing_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(96,72);
    if (printing_list) {
	if (EQ(element,M_CAR(printing_list))) {
	    temp = CDR(printing_list);
	    inline_note_reclaim_cons(printing_list,Qprinting);
	    if (ISVREF(Available_printing_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_printing_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = printing_list;
		temp_1 = Available_printing_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = printing_list;
	    }
	    else {
		temp_1 = Available_printing_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = printing_list;
		temp_1 = Available_printing_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = printing_list;
	    }
	    M_CDR(printing_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = printing_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qprinting);
		if (ISVREF(Available_printing_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_printing_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_printing_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_printing_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_printing_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		M_CDR(l) = Nil;
		goto end_loop;
	    }
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp = printing_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-PRINTING-CONS-1 */
Object delete_printing_cons_1(printing_cons,printing_list)
    Object printing_cons, printing_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(96,73);
    if (EQ(printing_cons,printing_list))
	temp = CDR(printing_list);
    else {
	l_trailer_qm = Nil;
	l = printing_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,printing_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = printing_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_printing_cons_1(printing_cons);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Postscript_emit_integers_as_color_differences, Qpostscript_emit_integers_as_color_differences);

DEFINE_VARIABLE_WITH_SYMBOL(Postscript_emit_composite_object_without_name, Qpostscript_emit_composite_object_without_name);

/* POSTSCRIPT-EMIT-COMPOSITE-OBJECT */
Object postscript_emit_composite_object(object)
    Object object;
{
    Object element, ab_loop_list_;

    x_note_fn_call(96,74);
    if (LISTP(object)) {
	element = Nil;
	ab_loop_list_ = object;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SYMBOLP(element))
	    postscript_emit_symbol(element);
	else if (FIXNUMP(element)) {
	    if (Postscript_emit_integers_as_color_differences)
		postscript_emit_color_difference(element);
	    else
		postscript_emit_atom(element);
	}
	else if (LISTP(element))
	    postscript_emit_composite_object(element);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else if (SYMBOLP(object))
	return postscript_emit_symbol(object);
    else if (FIXNUMP(object)) {
	if (Postscript_emit_integers_as_color_differences)
	    return postscript_emit_color_difference(object);
	else
	    return postscript_emit_atom(object);
    }
    else
	return VALUES_1(Qnil);
}

/* RESERVE-COMPOSITE-OBJECT-INDEX */
Object reserve_composite_object_index()
{
    Object last_postscript_composite_object_index_new_value;

    x_note_fn_call(96,75);
    last_postscript_composite_object_index_new_value = 
	    FIXNUM_ADD1(Last_postscript_composite_object_index);
    Last_postscript_composite_object_index = 
	    last_postscript_composite_object_index_new_value;
    return VALUES_1(Last_postscript_composite_object_index);
}

static Object string_constant_22;  /* " /g~D" */

static Object string_constant_23;  /* "~C" */

static Object string_constant_24;  /* "def" */

static Object Qpostscript_emit_icon_rendering_inner;  /* postscript-emit-icon-rendering-inner */

/* POSTSCRIPT-EMIT-COMPOSITE-OBJECT-DEFINITION */
Object postscript_emit_composite_object_definition varargs_1(int, n)
{
    Object object, brackets, body_function;
    Object previously_reserved_index_qm, postscript_emitting_definition;
    Object postscript_definition_operation_counter, object_index, temp;
    Object computed_values_plist_copy, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(96,76);
    INIT_ARGS_nonrelocating();
    object = REQUIRED_ARG_nonrelocating();
    brackets = REQUIRED_ARG_nonrelocating();
    body_function = REQUIRED_ARG_nonrelocating();
    previously_reserved_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    postscript_emitting_definition = T;
    postscript_definition_operation_counter = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Postscript_definition_operation_counter,Qpostscript_definition_operation_counter,postscript_definition_operation_counter,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Postscript_emitting_definition,Qpostscript_emitting_definition,postscript_emitting_definition,
	      0);
	object_index = previously_reserved_index_qm;
	if (object_index);
	else if ( !TRUEP(Postscript_emit_composite_object_without_name)) {
	    temp = FIXNUM_ADD1(Last_postscript_composite_object_index);
	    Last_postscript_composite_object_index = temp;
	    object_index = Last_postscript_composite_object_index;
	}
	else
	    object_index = Nil;
	postscript_emit_line_break();
	if ( !TRUEP(Postscript_emit_composite_object_without_name))
	    pformat(2,string_constant_22,object_index);
	pformat(2,string_constant_23,FIX(UBYTE_16_ISAREF_1(brackets,
		(SI_Long)0L)));
	FUNCALL_1(body_function,object);
	pformat(2,string_constant_23,FIX(UBYTE_16_ISAREF_1(brackets,
		(SI_Long)1L)));
	if ( !TRUEP(Postscript_emit_composite_object_without_name))
	    pformat(1,string_constant_24);
	if (EQ(body_function,Qpostscript_emit_icon_rendering_inner)) {
	    Postscript_object_mapping_for_icon_renderings = 
		    printing_cons_1(object_index,
		    Postscript_object_mapping_for_icon_renderings);
	    computed_values_plist_copy = 
		    copy_tree_including_leaves_using_printing_conses(ISVREF(object,
		    (SI_Long)9L));
	    if (computed_values_plist_copy)
		Postscript_computed_variables_mapping = 
			printing_cons_1(computed_values_plist_copy,
			Postscript_computed_variables_mapping);
	    gensymed_symbol = make_printing_list_1(FIX((SI_Long)7L));
	    gensymed_symbol_1 = gensymed_symbol;
	    temp = ISVREF(object,(SI_Long)3L);
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = ISVREF(object,(SI_Long)4L);
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = ISVREF(object,(SI_Long)5L);
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = ISVREF(object,(SI_Long)8L);
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = ISVREF(object,(SI_Long)13L);
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = ISVREF(object,(SI_Long)14L);
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = computed_values_plist_copy;
	    Postscript_object_mapping_for_icon_renderings = 
		    printing_cons_1(gensymed_symbol,
		    Postscript_object_mapping_for_icon_renderings);
	}
	else {
	    Postscript_composite_object_mapping = 
		    printing_cons_1(object_index,
		    Postscript_composite_object_mapping);
	    Postscript_composite_object_mapping = printing_cons_1(object,
		    Postscript_composite_object_mapping);
	}
	result = VALUES_1(object_index);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object array_constant_3;    /* # */

static Object Qpostscript_emit_composite_object;  /* postscript-emit-composite-object */

static Object string_constant_25;  /* " g~D" */

/* POSTSCRIPT-EMIT-COMPOSITE-OBJECT-OR-LOOKUP */
Object postscript_emit_composite_object_or_lookup(object)
    Object object;
{
    Object temp;

    x_note_fn_call(96,77);
    temp = getf(Postscript_composite_object_mapping,object,_);
    if (temp);
    else
	temp = postscript_emit_composite_object_definition(3,object,
		array_constant_3,Qpostscript_emit_composite_object);
    return pformat(2,string_constant_25,temp);
}

/* RECLAIM-POSTSCRIPT-OBJECT-MAPPING-FOR-ICON-RENDERINGS */
Object reclaim_postscript_object_mapping_for_icon_renderings(object_mapping)
    Object object_mapping;
{
    Object key, ab_loop_list_;

    x_note_fn_call(96,78);
    key = Nil;
    ab_loop_list_ = object_mapping;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    key = CAR(ab_loop_list_);
    reclaim_printing_list_1(key);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    reclaim_printing_list_1(object_mapping);
    return VALUES_1(Nil);
}

/* RECLAIM-POSTSCRIPT-COMPUTED-VARIABLES-MAPPING */
Object reclaim_postscript_computed_variables_mapping(mapping)
    Object mapping;
{
    x_note_fn_call(96,79);
    reclaim_tree_including_leaves_for_printing_conses(mapping);
    return VALUES_1(Nil);
}

/* LOOKUP-POSTSCRIPT-ICON-RENDERING-INDEX */
Object lookup_postscript_icon_rendering_index(icon_rendering)
    Object icon_rendering;
{
    Object x_scale_of_rendering, y_scale_of_rendering;
    Object reflection_and_rotation_of_rendering;
    Object line_drawing_description_for_rendering_qm, width_of_rendered_icon;
    Object height_of_rendered_icon, variable_overrides, a, b, c, d, e, f, g;
    Object index_1, ab_loop_list_, temp;

    x_note_fn_call(96,80);
    x_scale_of_rendering = ISVREF(icon_rendering,(SI_Long)3L);
    y_scale_of_rendering = ISVREF(icon_rendering,(SI_Long)4L);
    reflection_and_rotation_of_rendering = ISVREF(icon_rendering,(SI_Long)5L);
    line_drawing_description_for_rendering_qm = ISVREF(icon_rendering,
	    (SI_Long)8L);
    width_of_rendered_icon = ISVREF(icon_rendering,(SI_Long)13L);
    height_of_rendered_icon = ISVREF(icon_rendering,(SI_Long)14L);
    variable_overrides = ISVREF(icon_rendering,(SI_Long)9L);
    a = Nil;
    b = Nil;
    c = Nil;
    d = Nil;
    e = Nil;
    f = Nil;
    g = Nil;
    index_1 = Nil;
    ab_loop_list_ = Postscript_object_mapping_for_icon_renderings;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    temp = CAR(ab_loop_list_);
    a = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    b = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    temp = CDR(temp);
    c = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    d = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    e = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    f = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    g = CAR(temp);
    temp = CDR(ab_loop_list_);
    index_1 = CAR(temp);
    if (EQL(a,x_scale_of_rendering) && EQL(b,y_scale_of_rendering) && 
	    EQL(c,reflection_and_rotation_of_rendering) && EQL(d,
	    line_drawing_description_for_rendering_qm) && EQL(e,
	    width_of_rendered_icon) && EQL(f,height_of_rendered_icon) && 
	    sorted_plist_match_p(g,variable_overrides))
	return VALUES_1(index_1);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

Object The_type_description_of_line_drawing_for_printing = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_line_drawing_for_printings, Qchain_of_available_line_drawing_for_printings);

DEFINE_VARIABLE_WITH_SYMBOL(Line_drawing_for_printing_count, Qline_drawing_for_printing_count);

Object Chain_of_available_line_drawing_for_printings_vector = UNBOUND;

/* LINE-DRAWING-FOR-PRINTING-STRUCTURE-MEMORY-USAGE */
Object line_drawing_for_printing_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(96,81);
    temp = Line_drawing_for_printing_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-LINE-DRAWING-FOR-PRINTING-COUNT */
Object outstanding_line_drawing_for_printing_count()
{
    Object def_structure_line_drawing_for_printing_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(96,82);
    gensymed_symbol = IFIX(Line_drawing_for_printing_count);
    def_structure_line_drawing_for_printing_variable = 
	    Chain_of_available_line_drawing_for_printings;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_line_drawing_for_printing_variable))
	goto end_loop;
    def_structure_line_drawing_for_printing_variable = 
	    ISVREF(def_structure_line_drawing_for_printing_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-LINE-DRAWING-FOR-PRINTING-1 */
Object reclaim_line_drawing_for_printing_1(line_drawing_for_printing)
    Object line_drawing_for_printing;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(96,83);
    inline_note_reclaim_cons(line_drawing_for_printing,Nil);
    structure_being_reclaimed = line_drawing_for_printing;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_computed_values_plist_for_printing(ISVREF(line_drawing_for_printing,
	      (SI_Long)4L));
      SVREF(line_drawing_for_printing,FIX((SI_Long)4L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_line_drawing_for_printings_vector,
	    IFIX(Current_thread_index));
    SVREF(line_drawing_for_printing,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_line_drawing_for_printings_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = line_drawing_for_printing;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LINE-DRAWING-FOR-PRINTING */
Object reclaim_structure_for_line_drawing_for_printing(line_drawing_for_printing)
    Object line_drawing_for_printing;
{
    x_note_fn_call(96,84);
    return reclaim_line_drawing_for_printing_1(line_drawing_for_printing);
}

static Object Qg2_defstruct_structure_name_line_drawing_for_printing_g2_struct;  /* g2-defstruct-structure-name::line-drawing-for-printing-g2-struct */

/* MAKE-PERMANENT-LINE-DRAWING-FOR-PRINTING-STRUCTURE-INTERNAL */
Object make_permanent_line_drawing_for_printing_structure_internal()
{
    Object def_structure_line_drawing_for_printing_variable;
    Object defstruct_g2_line_drawing_for_printing_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(96,85);
    def_structure_line_drawing_for_printing_variable = Nil;
    atomic_incff_symval(Qline_drawing_for_printing_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_line_drawing_for_printing_variable = Nil;
	gensymed_symbol = (SI_Long)5L;
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
	defstruct_g2_line_drawing_for_printing_variable = the_array;
	SVREF(defstruct_g2_line_drawing_for_printing_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_line_drawing_for_printing_g2_struct;
	def_structure_line_drawing_for_printing_variable = 
		defstruct_g2_line_drawing_for_printing_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_line_drawing_for_printing_variable);
}

/* MAKE-LINE-DRAWING-FOR-PRINTING-1 */
Object make_line_drawing_for_printing_1(line_drawing_description_for_printing,
	    width_of_line_drawing_for_printing,
	    height_of_line_drawing_for_printing,
	    computed_values_plist_for_printing)
    Object line_drawing_description_for_printing;
    Object width_of_line_drawing_for_printing;
    Object height_of_line_drawing_for_printing;
    Object computed_values_plist_for_printing;
{
    Object def_structure_line_drawing_for_printing_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(96,86);
    def_structure_line_drawing_for_printing_variable = 
	    ISVREF(Chain_of_available_line_drawing_for_printings_vector,
	    IFIX(Current_thread_index));
    if (def_structure_line_drawing_for_printing_variable) {
	svref_arg_1 = Chain_of_available_line_drawing_for_printings_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_line_drawing_for_printing_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_line_drawing_for_printing_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_line_drawing_for_printing_g2_struct;
    }
    else
	def_structure_line_drawing_for_printing_variable = 
		make_permanent_line_drawing_for_printing_structure_internal();
    inline_note_allocate_cons(def_structure_line_drawing_for_printing_variable,
	    Nil);
    SVREF(def_structure_line_drawing_for_printing_variable,
	    FIX((SI_Long)1L)) = line_drawing_description_for_printing;
    SVREF(def_structure_line_drawing_for_printing_variable,
	    FIX((SI_Long)2L)) = width_of_line_drawing_for_printing;
    SVREF(def_structure_line_drawing_for_printing_variable,
	    FIX((SI_Long)3L)) = height_of_line_drawing_for_printing;
    SVREF(def_structure_line_drawing_for_printing_variable,
	    FIX((SI_Long)4L)) = computed_values_plist_for_printing;
    return VALUES_1(def_structure_line_drawing_for_printing_variable);
}

/* COPY-TREE-INCLUDING-LEAVES-USING-PRINTING-CONSES */
Object copy_tree_including_leaves_using_printing_conses(tree_qm)
    Object tree_qm;
{
    Object temp, new_list, last_new_cons, current_copy_position, cdr_new_value;

    x_note_fn_call(96,87);
    if (text_string_p(tree_qm))
	temp = copy_text_string(tree_qm);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(tree_qm) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(tree_qm)) == (SI_Long)1L)
	temp = copy_managed_float(tree_qm);
    else if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	temp = copy_tree_including_leaves_using_printing_conses(CAR(tree_qm));
	new_list = printing_cons_1(temp,CDR(tree_qm));
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	temp = 
		copy_tree_including_leaves_using_printing_conses(CAR(current_copy_position));
	cdr_new_value = printing_cons_1(temp,CDR(current_copy_position));
	M_CDR(last_new_cons) = cdr_new_value;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-TREE-INCLUDING-LEAVES-FOR-PRINTING-CONSES */
Object reclaim_tree_including_leaves_for_printing_conses(tree_qm)
    Object tree_qm;
{
    Object temp;

    x_note_fn_call(96,88);
    if (text_string_p(tree_qm))
	temp = reclaim_text_string(tree_qm);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(tree_qm) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(tree_qm)) == (SI_Long)1L) {
	reclaim_managed_simple_float_array_of_length_1(tree_qm);
	temp = Nil;
    }
    else if (ATOM(tree_qm))
	temp = Nil;
    else {
	reclaim_tree_including_leaves_for_printing_conses(CAR(tree_qm));
	reclaim_tree_including_leaves_for_printing_conses(CDR(tree_qm));
	temp = reclaim_printing_cons_1(tree_qm);
    }
    return VALUES_1(temp);
}

/* RECLAIM-COMPUTED-VALUES-PLIST-FOR-PRINTING */
Object reclaim_computed_values_plist_for_printing(computed_values_plist)
    Object computed_values_plist;
{
    x_note_fn_call(96,89);
    return reclaim_tree_including_leaves_for_printing_conses(computed_values_plist);
}

/* RECLAIM-POSTSCRIPT-PRINTING-ICON-RENDERINGS */
Object reclaim_postscript_printing_icon_renderings(renderings)
    Object renderings;
{
    Object line_drawing_for_printing, ab_loop_list_;

    x_note_fn_call(96,90);
    line_drawing_for_printing = Nil;
    ab_loop_list_ = renderings;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    line_drawing_for_printing = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_line_drawing_for_printing_1(line_drawing_for_printing);
    goto next_loop;
  end_loop:;
    reclaim_printing_list_1(renderings);
    Postscript_printing_icon_renderings = Nil;
    return VALUES_1(Postscript_printing_icon_renderings);
}

/* LOOK-UP-LINE-DRAWING-FOR-PRINTING */
Object look_up_line_drawing_for_printing(line_drawing,width,height,
	    computed_values_plist)
    Object line_drawing, width, height, computed_values_plist;
{
    Object line_drawing_for_printing, ab_loop_list_;

    x_note_fn_call(96,91);
    line_drawing_for_printing = Nil;
    ab_loop_list_ = Postscript_printing_icon_renderings;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    line_drawing_for_printing = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(line_drawing_for_printing,(SI_Long)1L),line_drawing) && 
	    FIXNUM_EQ(ISVREF(line_drawing_for_printing,(SI_Long)2L),width) 
	    && FIXNUM_EQ(ISVREF(line_drawing_for_printing,(SI_Long)3L),
	    height) && 
	    sorted_plist_match_p(ISVREF(line_drawing_for_printing,
	    (SI_Long)4L),computed_values_plist))
	return VALUES_1(line_drawing_for_printing);
    goto next_loop;
  end_loop:
    line_drawing_for_printing = 
	    make_line_drawing_for_printing_1(line_drawing,width,height,
	    copy_tree_including_leaves_using_printing_conses(computed_values_plist));
    Postscript_printing_icon_renderings = 
	    printing_cons_1(line_drawing_for_printing,
	    Postscript_printing_icon_renderings);
    return VALUES_1(line_drawing_for_printing);
    return VALUES_1(Qnil);
}

static Object array_constant_4;    /* # */

static Object Qpostscript_emit_line_drawing;  /* postscript-emit-line-drawing */

/* POSTSCRIPT-EMIT-ICON-RENDERING */
Object postscript_emit_icon_rendering(icon_rendering)
    Object icon_rendering;
{
    Object temp, line_drawing_for_printing;

    x_note_fn_call(96,92);
    temp = lookup_postscript_icon_rendering_index(icon_rendering);
    if (temp);
    else {
	line_drawing_for_printing = 
		look_up_line_drawing_for_printing(ISVREF(icon_rendering,
		(SI_Long)8L),ISVREF(icon_rendering,(SI_Long)13L),
		ISVREF(icon_rendering,(SI_Long)14L),ISVREF(icon_rendering,
		(SI_Long)9L));
	if ( !TRUEP(getf(Postscript_composite_object_mapping,
		line_drawing_for_printing,_)))
	    postscript_emit_composite_object_definition(3,
		    line_drawing_for_printing,array_constant_4,
		    Qpostscript_emit_line_drawing);
	temp = postscript_emit_composite_object_definition(3,
		icon_rendering,array_constant_4,
		Qpostscript_emit_icon_rendering_inner);
    }
    return pformat(2,string_constant_22,temp);
}

static Object list_constant_25;    /* # */

static Object list_constant_26;    /* # */

static Object string_constant_26;  /* "~% ~D ~D " */

static Object string_constant_27;  /* "~D ~D " */

static Object string_constant_28;  /* "~D ~D" */

static Object string_constant_29;  /* "$ed" */

static Object string_constant_30;  /* "~% g~D" */

/* POSTSCRIPT-EMIT-ICON-RENDERING-INNER */
Object postscript_emit_icon_rendering_inner(icon_rendering)
    Object icon_rendering;
{
    Object x_scale_of_rendering, y_scale_of_rendering, width, height;
    Object rotation_info, temp;

    x_note_fn_call(96,93);
    x_scale_of_rendering = ISVREF(icon_rendering,(SI_Long)3L);
    y_scale_of_rendering = ISVREF(icon_rendering,(SI_Long)4L);
    width = ISVREF(icon_rendering,(SI_Long)13L);
    height = ISVREF(icon_rendering,(SI_Long)14L);
    rotation_info = assq_function(ISVREF(icon_rendering,(SI_Long)5L),
	    list_constant_25);
    if (rotation_info);
    else
	rotation_info = list_constant_26;
    postscript_emit_line_break();
    if (IFIX(x_scale_of_rendering) != (SI_Long)4096L || 
	    IFIX(y_scale_of_rendering) != (SI_Long)4096L || 
	    FIRST(rotation_info)) {
	pformat(3,string_constant_26,width,height);
	pformat(3,string_constant_27,x_scale_of_rendering,
		y_scale_of_rendering);
	pformat(3,string_constant_28,SECOND(rotation_info),
		THIRD(rotation_info));
	postscript_emit_operator_1(string_constant_29);
    }
    temp = Postscript_composite_object_mapping;
    return pformat(2,string_constant_30,getf(temp,
	    look_up_line_drawing_for_printing(ISVREF(icon_rendering,
	    (SI_Long)8L),ISVREF(icon_rendering,(SI_Long)13L),
	    ISVREF(icon_rendering,(SI_Long)14L),ISVREF(icon_rendering,
	    (SI_Long)9L)),_));
}

static Object Qpolychrome;         /* polychrome */

static Object list_constant_27;    /* # */

static Object Qforeground;         /* foreground */

static Object Qbackground;         /* background */

static Object Qworkspace_foreground;  /* workspace-foreground */

static Object Qtransparent;        /* transparent */

/* POSTSCRIPT-EMIT-LINE-DRAWING */
Object postscript_emit_line_drawing(line_drawing_for_printing)
    Object line_drawing_for_printing;
{
    Object line_drawing, width, height, variable_overrides, first_element;
    Object polychrome_header_qm, icon_color_pattern_1;
    Object printing_icon_current_region_index_qm;
    Object line_drawing_description_following_header, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,94);
    line_drawing = ISVREF(line_drawing_for_printing,(SI_Long)1L);
    width = ISVREF(line_drawing_for_printing,(SI_Long)2L);
    height = ISVREF(line_drawing_for_printing,(SI_Long)3L);
    variable_overrides = ISVREF(line_drawing_for_printing,(SI_Long)4L);
    first_element = CAR(line_drawing);
    polychrome_header_qm = CONSP(first_element) && EQ(CAR(first_element),
	    Qpolychrome) ? first_element : Nil;
    icon_color_pattern_1 = REST(polychrome_header_qm);
    if (icon_color_pattern_1);
    else
	icon_color_pattern_1 = list_constant_27;
    printing_icon_current_region_index_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Printing_icon_current_region_index_qm,Qprinting_icon_current_region_index_qm,printing_icon_current_region_index_qm,
	    0);
      line_drawing_description_following_header = polychrome_header_qm ? 
	      CDR(line_drawing) : line_drawing;
      if (EQ(Qforeground,Qbackground))
	  temp = Current_background_color_value;
      else if (EQ(Qforeground,Qforeground) || EQ(Qforeground,
	      Qworkspace_foreground))
	  temp = Current_foreground_color_value;
      else if (EQ(Qforeground,Qtransparent))
	  temp = Current_background_color_value;
      else
	  temp = map_to_color_value(Qforeground);
      result = paint_one_bitmap_for_icon_on_scratchpad_raster(icon_color_pattern_1,
	      line_drawing_description_following_header,width,height,
	      FIX((SI_Long)4096L),FIX((SI_Long)4096L),temp,Nil,
	      variable_overrides,width,height,Nil);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_graph_rendering_embedded_icons, Qcurrent_graph_rendering_embedded_icons);

static Object Qpostscript_emit_graph_line_drawing;  /* postscript-emit-graph-line-drawing */

static Object Qpostscript_emit_graph_rendering_inner;  /* postscript-emit-graph-rendering-inner */

static Object string_constant_31;  /* " /g~Da{g~D" */

static Object string_constant_32;  /* "cleanup-after-graph-rendering" */

static Object string_constant_33;  /* "} def /g~Da" */

/* POSTSCRIPT-EMIT-GRAPH-RENDERING */
Object postscript_emit_graph_rendering(graph_rendering)
    Object graph_rendering;
{
    Object graph_rendering_index, current_graph_rendering_embedded_icons, temp;
    Object postscript_current_graph_line_drawing_index, index_1;
    Declare_special(2);

    x_note_fn_call(96,95);
    graph_rendering_index = 
	    getf(Postscript_object_mapping_for_graph_renderings,
	    ISVREF(graph_rendering,(SI_Long)16L),_);
    if (graph_rendering_index);
    else {
	current_graph_rendering_embedded_icons = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_graph_rendering_embedded_icons,Qcurrent_graph_rendering_embedded_icons,current_graph_rendering_embedded_icons,
		1);
	  temp = postscript_emit_composite_object_definition(3,
		  ISVREF(graph_rendering,(SI_Long)8L),array_constant_4,
		  Qpostscript_emit_graph_line_drawing);
	  postscript_emit_graph_rendering_embedded_icons();
	  postscript_current_graph_line_drawing_index = temp;
	  PUSH_SPECIAL_WITH_SYMBOL(Postscript_current_graph_line_drawing_index,Qpostscript_current_graph_line_drawing_index,postscript_current_graph_line_drawing_index,
		  0);
	    index_1 = postscript_emit_composite_object_definition(3,
		    graph_rendering,array_constant_4,
		    Qpostscript_emit_graph_rendering_inner);
	    Postscript_object_mapping_for_graph_renderings = 
		    printing_cons_1(index_1,
		    Postscript_object_mapping_for_graph_renderings);
	    Postscript_object_mapping_for_graph_renderings = 
		    printing_cons_1(ISVREF(graph_rendering,(SI_Long)16L),
		    Postscript_object_mapping_for_graph_renderings);
	    graph_rendering_index = index_1;
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    pformat(3,string_constant_31,graph_rendering_index,graph_rendering_index);
    postscript_emit_operator_1(string_constant_32);
    return pformat(2,string_constant_33,graph_rendering_index);
}

/* POSTSCRIPT-EMIT-GRAPH-LINE-DRAWING */
Object postscript_emit_graph_line_drawing(graph_line_drawing)
    Object graph_line_drawing;
{
    x_note_fn_call(96,96);
    return paint_graph_on_scratchpad_raster(T,FIX((SI_Long)1L),
	    graph_line_drawing,FIX((SI_Long)10000L),FIX((SI_Long)10000L),
	    FIX((SI_Long)4096L),FIX((SI_Long)4096L));
}

/* POSTSCRIPT-EMIT-GRAPH-RENDERING-EMBEDDED-ICONS */
Object postscript_emit_graph_rendering_embedded_icons()
{
    Object triple, ab_loop_list_, index_1;
    Object color_value_and_line_drawing_description;

    x_note_fn_call(96,97);
    triple = Nil;
    ab_loop_list_ = Current_graph_rendering_embedded_icons;
    index_1 = Nil;
    color_value_and_line_drawing_description = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    triple = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    index_1 = CAR(triple);
    color_value_and_line_drawing_description = CDR(triple);
    emit_embedded_icon_layer_definition(index_1,
	    color_value_and_line_drawing_description);
    reclaim_printing_list_1(triple);
    goto next_loop;
  end_loop:
    reclaim_printing_list_1(Current_graph_rendering_embedded_icons);
    return VALUES_1(Qnil);
}

/* POSTSCRIPT-EMIT-GRAPH-RENDERING-INNER */
Object postscript_emit_graph_rendering_inner(graph_rendering)
    Object graph_rendering;
{
    x_note_fn_call(96,98);
    return pformat(2,string_constant_30,
	    Postscript_current_graph_line_drawing_index);
}

Object Number_of_kanji_characters_per_microfont = UNBOUND;

Object Use_substitute_for_non_latin_text_p = UNBOUND;

Object Substitute_character_for_non_latin_text = UNBOUND;

static Object list_constant_28;    /* # */

static Object Qnon_graphic;        /* non-graphic */

static Object Qordinary_space;     /* ordinary-space */

static Object Qzero_width_space;   /* zero-width-space */

static Object Qnon_spacing_mark;   /* non-spacing-mark */

static Object Qmark;               /* mark */

/* PRINTING-PASS-1-DEFINE-FOR-TEXT */
Object printing_pass_1_define_for_text(font_map,text_line)
    Object font_map, text_line;
{
    Object font_used, non_latin_used_so_far_qm, character_index, length_1;
    Object character_1, code, temp, printing_modify_macro_using_test_arg_1;
    Object car_1, cdr_1, key_result, x_element, ab_loop_list_, ab_loop_it_;
    Object fonts_needing_corresponding_kanji_font_new_value;
    SI_Long arg, arg_1, arg_2;
    char temp_1;

    x_note_fn_call(96,99);
    font_used = FIRST(font_map);
    if ( !TRUEP(memq_function(font_used,Fonts_used_in_print_job)))
	Fonts_used_in_print_job = printing_cons_1(font_used,
		Fonts_used_in_print_job);
    if ( !TRUEP(Use_substitute_for_non_latin_text_p)) {
	non_latin_used_so_far_qm = Nil;
	character_index = FIX((SI_Long)0L);
	length_1 = lengthw(text_line);
	character_1 = Nil;
	code = Nil;
      next_loop:
	if ( !FIXNUM_LT(character_index,length_1))
	    goto end_loop;
	temp = FIX(UBYTE_16_ISAREF_1(text_line,IFIX(character_index)));
	character_index = FIXNUM_ADD1(character_index);
	character_1 = temp;
	code = character_1;
	if ((SI_Long)0L == 
		IFIX(map_unicode_to_ab_latin_font_code_or_zero(code)) || 
		assoc_eql(code,list_constant_28)) {
	    if (newline_p(character_1))
		temp = Qnon_graphic;
	    else if (IFIX(character_1) == (SI_Long)32L || 
		    IFIX(character_1) == (SI_Long)160L)
		temp = Qordinary_space;
	    else if (IFIX(character_1) == (SI_Long)8203L)
		temp = Qzero_width_space;
	    else {
		arg = (SI_Long)746L;
		arg_1 = IFIX(character_1);
		arg_2 = (SI_Long)883L;
		temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		if (temp_1);
		else {
		    arg = (SI_Long)1456L;
		    arg_1 = IFIX(character_1);
		    arg_2 = (SI_Long)1474L;
		    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		}
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(character_1,FIX((SI_Long)3633L));
		if (temp_1);
		else {
		    arg = (SI_Long)3636L;
		    arg_1 = IFIX(character_1);
		    arg_2 = (SI_Long)3642L;
		    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		}
		if (temp_1);
		else {
		    arg = (SI_Long)3655L;
		    arg_1 = IFIX(character_1);
		    arg_2 = (SI_Long)3662L;
		    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		}
		if (temp_1)
		    temp = Qnon_spacing_mark;
		else
		    temp = Qmark;
	    }
	    temp_1 = EQ(temp,Qmark);
	    if (temp_1);
	    else {
		if (newline_p(character_1))
		    temp = Qnon_graphic;
		else if (IFIX(character_1) == (SI_Long)32L || 
			IFIX(character_1) == (SI_Long)160L)
		    temp = Qordinary_space;
		else if (IFIX(character_1) == (SI_Long)8203L)
		    temp = Qzero_width_space;
		else {
		    arg = (SI_Long)746L;
		    arg_1 = IFIX(character_1);
		    arg_2 = (SI_Long)883L;
		    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		    if (temp_1);
		    else {
			arg = (SI_Long)1456L;
			arg_1 = IFIX(character_1);
			arg_2 = (SI_Long)1474L;
			temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		    }
		    if (temp_1);
		    else
			temp_1 = FIXNUM_EQ(character_1,FIX((SI_Long)3633L));
		    if (temp_1);
		    else {
			arg = (SI_Long)3636L;
			arg_1 = IFIX(character_1);
			arg_2 = (SI_Long)3642L;
			temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		    }
		    if (temp_1);
		    else {
			arg = (SI_Long)3655L;
			arg_1 = IFIX(character_1);
			arg_2 = (SI_Long)3662L;
			temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		    }
		    if (temp_1)
			temp = Qnon_spacing_mark;
		    else
			temp = Qmark;
		}
		temp_1 = EQ(temp,Qnon_spacing_mark);
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    non_latin_used_so_far_qm = T;
	    note_use_of_kanji_character(font_used,character_1);
	}
	goto next_loop;
      end_loop:
	if (non_latin_used_so_far_qm) {
	    printing_modify_macro_using_test_arg_1 = font_used;
	    car_1 = printing_modify_macro_using_test_arg_1;
	    cdr_1 = Fonts_needing_corresponding_kanji_font;
	    key_result = car_1;
	    x_element = Nil;
	    ab_loop_list_ = cdr_1;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    x_element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	    fonts_needing_corresponding_kanji_font_new_value = temp_1 ? 
		    cdr_1 : printing_cons_1(car_1,cdr_1);
	    Fonts_needing_corresponding_kanji_font = 
		    fonts_needing_corresponding_kanji_font_new_value;
	}
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* NOTE-USE-OF-KANJI-CHARACTER */
Object note_use_of_kanji_character(base_font,non_latin_wide_character)
    Object base_font, non_latin_wide_character;
{
    Object kanji_code, code, tail_of_font_list;
    Object code_and_assignment_used_in_kanji_font_tail;
    Object code_and_assignment_used_in_kanji_font, temp, printing_font_code_qm;
    Object microfont_number, char_code_1, temp_1, tail;
    Object result;

    x_note_fn_call(96,100);
    kanji_code = non_latin_wide_character;
    if ( !TRUEP(getf(Kanji_fonts_used_in_print_job,base_font,_)))
	Kanji_fonts_used_in_print_job = printing_cons_1(base_font,
		printing_cons_1(Nil,Kanji_fonts_used_in_print_job));
    code = FIX((SI_Long)0L);
    tail_of_font_list = Nil;
    code_and_assignment_used_in_kanji_font_tail = 
	    getf(Kanji_fonts_used_in_print_job,base_font,_);
    code_and_assignment_used_in_kanji_font = Nil;
  next_loop:
    if ( !TRUEP(code_and_assignment_used_in_kanji_font_tail))
	goto end_loop;
    code_and_assignment_used_in_kanji_font = 
	    CAR(code_and_assignment_used_in_kanji_font_tail);
    temp = CAR(code_and_assignment_used_in_kanji_font);
    if (EQL(temp,kanji_code)) {
	printing_font_code_qm = code;
	goto end_1;
    }
    else {
	tail_of_font_list = code_and_assignment_used_in_kanji_font_tail;
	code = FIXNUM_ADD1(code);
    }
    code_and_assignment_used_in_kanji_font_tail = 
	    M_CDR(code_and_assignment_used_in_kanji_font_tail);
    goto next_loop;
  end_loop:
    printing_font_code_qm = Qnil;
  end_1:;
    if (printing_font_code_qm)
	return VALUES_1(printing_font_code_qm);
    else if (tail_of_font_list) {
	result = chestnut_floorf_function(code,
		Number_of_kanji_characters_per_microfont);
	MVS_2(result,microfont_number,char_code_1);
	code = FIX(IFIX(microfont_number) << (SI_Long)10L | IFIX(char_code_1));
	temp_1 = printing_cons_1(printing_cons_1(kanji_code,code),Nil);
	M_CDR(tail_of_font_list) = temp_1;
	return VALUES_1(code);
    }
    else {
	tail = memq_function(base_font,Kanji_fonts_used_in_print_job);
	temp_1 = printing_cons_1(printing_cons_1(kanji_code,
		FIX((SI_Long)0L)),Nil);
	M_CADR(tail) = temp_1;
	return VALUES_1(FIX((SI_Long)0L));
    }
}

/* CONVERT-TEXT-WIDTH-TO-POSTSCRIPT-SCALEABLE-POINTS */
Object convert_text_width_to_postscript_scaleable_points(text_width,point_size)
    Object text_width, point_size;
{
    Object temp;
    double temp_1, temp_2;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(96,101);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = lfloat(text_width,float_constant);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = lfloat(point_size,float_constant);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	result = l_round(DOUBLE_TO_DOUBLE_FLOAT(1000.0 * temp_1),
		DOUBLE_TO_DOUBLE_FLOAT(temp_2 * 256.0));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* G2-CHARACTER-CODE-FOR-POSTSCRIPT-CHARACTER-CODE */
Object g2_character_code_for_postscript_character_code(ps_code)
    Object ps_code;
{
    x_note_fn_call(96,102);
    return VALUES_1(ps_code);
}

static Object Qab_font;            /* ab-font */

static Object string_constant_34;  /* "[" */

static Object string_constant_35;  /* "~d" */

static Object string_constant_36;  /* "~%" */

static Object string_constant_37;  /* " " */

static Object string_constant_38;  /* "]" */

/* POSTSCRIPT-EMIT-AB-FONT-CHARACTER-WIDTHS */
Object postscript_emit_ab_font_character_widths(font_name)
    Object font_name;
{
    Object font, character_description_table, font_size, g2_character_code;
    Object character_description_qm, width, points, temp, temp_1;
    SI_Long i;
    char temp_2;

    x_note_fn_call(96,103);
    font = getfq_function_no_default(INLINE_SYMBOL_PLIST(font_name),Qab_font);
    character_description_table = ISVREF(font,(SI_Long)10L);
    font_size = ISVREF(font,(SI_Long)6L);
    pformat(1,string_constant_34);
    i = (SI_Long)0L;
    g2_character_code = Nil;
    character_description_qm = Nil;
    width = Nil;
    points = Nil;
  next_loop:
    if (i >= (SI_Long)256L)
	goto end_loop;
    g2_character_code = 
	    g2_character_code_for_postscript_character_code(FIX(i));
    character_description_qm = IFIX(g2_character_code) <= (SI_Long)256L ? 
	    ISVREF(character_description_table,IFIX(g2_character_code)) : Nil;
    temp = ISVREF(font,(SI_Long)15L);
    if (temp);
    else if (character_description_qm) {
	temp = Use_scaleable_set_widths_qm ? 
		ISVREF(character_description_qm,(SI_Long)1L) : Nil;
	if (temp);
	else
	    temp = FIX(IFIX(ISVREF(character_description_qm,(SI_Long)0L)) 
		    << (SI_Long)8L);
    }
    else
	temp = FIX(IFIX(ISVREF(font,(SI_Long)4L)) << (SI_Long)8L);
    width = temp;
    points = convert_text_width_to_postscript_scaleable_points(width,
	    font_size);
    pformat(2,string_constant_35,points);
    if (i > (SI_Long)0L) {
	temp_1 = chestnut_modf_function(FIX(i),FIX((SI_Long)16L));
	temp = FIX((SI_Long)0L);
	temp_2 = NUM_EQ(temp_1,temp);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	pformat(1,string_constant_36);
    else if (i < (SI_Long)255L)
	pformat(1,string_constant_37);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return pformat(1,string_constant_38);
}

static Object string_constant_39;  /* "~%% Define Fonts.~%" */

static Object Qblob18;             /* blob18 */

static Object string_constant_40;  /* "$br" */

static Object Qroman;              /* roman */

static Object string_constant_41;  /* "$bs" */

static Object string_constant_42;  /* "$bu" */

static Object string_constant_43;  /* "~%/microfont-encoding-vector[" */

static Object string_constant_44;  /* "/c~D" */

static Object string_constant_45;  /* "]def" */

static Object string_constant_46;  /* "~%/kanji-dictionary ~D dict def" */

static Object string_constant_47;  /* "~%% Setup Kanji Fonts" */

static Object string_constant_48;  /* "~%kanji-dictionary begin" */

static Object string_constant_49;  /* "EXTRA~a" */

static Object string_constant_50;  /* "~%~(/~A~) begin-kanji-font" */

static Object string_constant_51;  /* "~%~(  /k~D ~D begin-kanji-microfont" */

static Object string_constant_52;  /* "  % ~D" */

static Object string_constant_53;  /* "~%  /k~D ~D end-kanji-microfont" */

static Object string_constant_54;  /* "~%  /k~D ~D begin-kanji-microfont" */

static Object string_constant_55;  /* "~%~(  /k~D ~D end-kanji-microfont" */

static Object string_constant_56;  /* "~%~(/~A~) end-kanji-font" */

static Object string_constant_57;  /* "~%end" */

static Object string_constant_58;  /* "~%/corresponding-kanji-font ~D dict def" */

static Object string_constant_59;  /* "~%~(/~S /~A~)" */

static Object Qcorresponding_kanji_font_name_and_magnification;  /* corresponding-kanji-font-name-and-magnification */

static Object string_constant_60;  /* " ~D ~D def-kanji-correspondence" */

/* EMIT-PRINT-JOB-SPECIFIC-FONT-DEFINITIONS */
Object emit_print_job_specific_font_definitions()
{
    Object font, ab_loop_list_, ab_font, ab_font_size, ab_font_type, temp;
    Object temp_1, kanji_codes, ab_loopvar_, base_font, kanji_codes_etc_used;
    Object corresponding_font_name, microfont_number;
    Object code_and_assignment_used_in_kanji_font, ab_loop_list__1, kanji_code;
    Object microfont_character_code, ab_loop_iter_flag_;
    SI_Long character_code, ab_loop_bind_, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, kanji_dictionary_size;
    SI_Long count_1;

    x_note_fn_call(96,104);
    font = Nil;
    ab_loop_list_ = Fonts_used_in_print_job;
    ab_font = Nil;
    ab_font_size = Nil;
    ab_font_type = Nil;
    pformat(1,string_constant_39);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    font = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_font = getfq_function_no_default(INLINE_SYMBOL_PLIST(font),Qab_font);
    ab_font_size = ISVREF(ab_font,(SI_Long)6L);
    ab_font_type = ISVREF(ab_font,(SI_Long)12L);
    postscript_emit_symbol(font);
    postscript_emit_integer(ab_font_size);
    if (EQ(font,Qblob18))
	postscript_emit_operator_1(string_constant_40);
    else if (EQ(Qroman,ab_font_type)) {
	postscript_emit_ab_font_character_widths(font);
	postscript_emit_operator_1(string_constant_41);
    }
    else
	postscript_emit_operator_1(string_constant_42);
    goto next_loop;
  end_loop:;
    if (Kanji_fonts_used_in_print_job) {
	character_code = (SI_Long)0L;
	ab_loop_bind_ = IFIX(Number_of_kanji_characters_per_microfont);
	pformat(1,string_constant_43);
      next_loop_1:
	if (character_code >= ab_loop_bind_)
	    goto end_loop_1;
	temp = chestnut_modf_function(FIX(character_code),FIX((SI_Long)24L));
	temp_1 = FIX((SI_Long)0L);
	if (NUM_EQ(temp,temp_1))
	    pformat(1,string_constant_36);
	pformat(2,string_constant_44,FIX(character_code));
	character_code = character_code + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	pformat(1,string_constant_45);
	gensymed_symbol = (SI_Long)30L;
	gensymed_symbol_1 = 
		IFIX(ltruncate(length(Kanji_fonts_used_in_print_job),
		FIX((SI_Long)2L)));
	kanji_codes = Nil;
	ab_loop_list_ = Kanji_fonts_used_in_print_job;
	ab_loopvar_ = FIX((SI_Long)0L);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
      next_loop_2:
	temp = CDR(ab_loop_list_);
	kanji_codes = CAR(temp);
	ab_loopvar_ = add(ceiling(length(kanji_codes),
		Number_of_kanji_characters_per_microfont),ab_loopvar_);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:
	gensymed_symbol_2 = IFIX(ab_loopvar_);
	goto end_1;
	gensymed_symbol_2 = IFIX(Qnil);
      end_1:;
	gensymed_symbol_3 = 
		IFIX(length(Fonts_needing_corresponding_kanji_font));
	kanji_dictionary_size = gensymed_symbol + gensymed_symbol_1 + 
		gensymed_symbol_2 + gensymed_symbol_3;
	pformat(2,string_constant_46,FIX(kanji_dictionary_size));
	base_font = Nil;
	kanji_codes_etc_used = Nil;
	ab_loop_list_ = Kanji_fonts_used_in_print_job;
	ab_font = Nil;
	corresponding_font_name = Nil;
	pformat(1,string_constant_47);
	pformat(1,string_constant_48);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
      next_loop_3:
	base_font = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	kanji_codes_etc_used = CAR(temp);
	ab_font = getfq_function_no_default(INLINE_SYMBOL_PLIST(base_font),
		Qab_font);
	corresponding_font_name = tformat_text_string(2,string_constant_49,
		base_font);
	microfont_number = FIX((SI_Long)0L);
	code_and_assignment_used_in_kanji_font = Nil;
	ab_loop_list__1 = kanji_codes_etc_used;
	kanji_code = Nil;
	count_1 = (SI_Long)0L;
	microfont_character_code = Nil;
	ab_loop_iter_flag_ = T;
	pformat(2,string_constant_50,corresponding_font_name);
	pformat(3,string_constant_51,microfont_number,microfont_number);
      next_loop_4:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_4;
	code_and_assignment_used_in_kanji_font = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	kanji_code = CAR(code_and_assignment_used_in_kanji_font);
	if ( !TRUEP(ab_loop_iter_flag_))
	    count_1 = count_1 + (SI_Long)1L;
	microfont_character_code = chestnut_modf_function(FIX(count_1),
		Number_of_kanji_characters_per_microfont);
	postscript_emit_kanji_character_description(kanji_code,ab_font,
		microfont_character_code);
	pformat(2,string_constant_52,kanji_code);
	if (FIXNUM_EQ(microfont_character_code,
		FIXNUM_SUB1(Number_of_kanji_characters_per_microfont))) {
	    pformat(3,string_constant_53,microfont_number,microfont_number);
	    microfont_number = FIXNUM_ADD1(microfont_number);
	    pformat(3,string_constant_54,microfont_number,microfont_number);
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_4;
      end_loop_4:
	pformat(3,string_constant_55,microfont_number,microfont_number);
	pformat(2,string_constant_56,corresponding_font_name);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	goto next_loop_3;
      end_loop_3:
	pformat(1,string_constant_57);
	font = Nil;
	ab_loop_list_ = Fonts_needing_corresponding_kanji_font;
	corresponding_font_name = Nil;
	pformat(2,string_constant_58,
		length(Fonts_needing_corresponding_kanji_font));
      next_loop_5:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_5;
	font = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	corresponding_font_name = tformat_text_string(2,string_constant_49,
		font);
	pformat(3,string_constant_59,font,corresponding_font_name);
	temp = ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(font),
		Qab_font),(SI_Long)6L);
	temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(font),
		Qcorresponding_kanji_font_name_and_magnification);
	temp_1 = CDR(temp_1);
	if (temp_1);
	else
	    temp_1 = FIX((SI_Long)256L);
	pformat(3,string_constant_60,temp,temp_1);
	goto next_loop_5;
      end_loop_5:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qcorresponding_cyrillic_font_name_and_magnification;  /* corresponding-cyrillic-font-name-and-magnification */

static Object list_constant_29;    /* # */

static Object Qcorresponding_hebrew_font_name_and_magnification;  /* corresponding-hebrew-font-name-and-magnification */

static Object list_constant_30;    /* # */

static Object Qcorresponding_thai_font_name_and_magnification;  /* corresponding-thai-font-name-and-magnification */

static Object list_constant_31;    /* # */

static Object list_constant_32;    /* # */

static Object string_constant_61;  /* "~%   /c~D" */

static Object string_constant_62;  /* " ~D" */

static Object string_constant_63;  /* " ~D ~D" */

static Object string_constant_64;  /* "~a" */

static Object string_constant_65;  /* " def-kanji-character" */

/* POSTSCRIPT-EMIT-KANJI-CHARACTER-DESCRIPTION */
Object postscript_emit_kanji_character_description(kanji_code,base_ab_font,
	    micro_font_character_code)
    Object kanji_code, base_ab_font, micro_font_character_code;
{
    Object ab_font_name, corresponding_font_name_and_magnification_qm, unicode;
    Object gensymed_symbol, ab_font, character_bitmap, temporary_p;
    Object bounding_box_x_offset, bounding_box_y_offset, bounding_box_width;
    Object bounding_box_height, character_set_width, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object postscript_bitmap_encoding_string;
    SI_Long arg, arg_1, arg_2, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,105);
    ab_font_name = ISVREF(base_ab_font,(SI_Long)9L);
    if (IFIX(map_unicode_to_ab_latin_font_code_or_zero(kanji_code)) != 
	    (SI_Long)0L)
	corresponding_font_name_and_magnification_qm = Nil;
    else {
	arg = (SI_Long)8192L;
	arg_1 = IFIX(FIXNUM_ADD(kanji_code,
		Unicode_offset_for_gensym_cyrillic));
	arg_2 = (SI_Long)8447L;
	if (arg <= arg_1 && arg_1 <= arg_2) {
	    corresponding_font_name_and_magnification_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(ab_font_name),
		    Qcorresponding_cyrillic_font_name_and_magnification);
	    if (corresponding_font_name_and_magnification_qm);
	    else
		corresponding_font_name_and_magnification_qm = 
			list_constant_29;
	}
	else {
	    unicode = kanji_code;
	    if (IFIX(unicode) <= (SI_Long)8364L ? (IFIX(unicode) <= 
		    (SI_Long)487L ? (IFIX(unicode) <= (SI_Long)304L ? 
		    (IFIX(unicode) <= (SI_Long)287L ? IFIX(unicode) >= 
		    (SI_Long)286L : IFIX(unicode) == (SI_Long)304L) : 
		    IFIX(unicode) <= (SI_Long)351L ? IFIX(unicode) >= 
		    (SI_Long)348L : IFIX(unicode) >= (SI_Long)486L) : 
		    IFIX(unicode) <= (SI_Long)8355L ? (IFIX(unicode) <= 
		    (SI_Long)1524L ? IFIX(unicode) >= (SI_Long)1456L : 
		    IFIX(unicode) == (SI_Long)8355L) : IFIX(unicode) <= 
		    (SI_Long)8362L ? IFIX(unicode) == (SI_Long)8362L : 
		    IFIX(unicode) == (SI_Long)8364L) : IFIX(unicode) <= 
		    (SI_Long)64335L ? IFIX(unicode) >= (SI_Long)64285L : 
		    TRUEP(Nil)) {
		corresponding_font_name_and_magnification_qm = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(ab_font_name),
			Qcorresponding_hebrew_font_name_and_magnification);
		if (corresponding_font_name_and_magnification_qm);
		else
		    corresponding_font_name_and_magnification_qm = 
			    list_constant_30;
	    }
	    else {
		unicode = kanji_code;
		if (IFIX(unicode) <= (SI_Long)3711L ? IFIX(unicode) >= 
			(SI_Long)3584L : IFIX(unicode) <= (SI_Long)63247L ?
			 IFIX(unicode) >= (SI_Long)63232L : TRUEP(Nil)) {
		    corresponding_font_name_and_magnification_qm = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(ab_font_name),
			    Qcorresponding_thai_font_name_and_magnification);
		    if (corresponding_font_name_and_magnification_qm);
		    else
			corresponding_font_name_and_magnification_qm = 
				list_constant_31;
		}
		else {
		    corresponding_font_name_and_magnification_qm = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(ab_font_name),
			    Qcorresponding_kanji_font_name_and_magnification);
		    if (corresponding_font_name_and_magnification_qm);
		    else
			corresponding_font_name_and_magnification_qm = 
				list_constant_32;
		}
	    }
	}
    }
    if (corresponding_font_name_and_magnification_qm) {
	gensymed_symbol = FIRST(corresponding_font_name_and_magnification_qm);
	ab_font = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qab_font);
    }
    else
	ab_font = Nil;
    if (ab_font);
    else
	ab_font = base_ab_font;
    result = get_character_bitmap_of_font_character(kanji_code,ab_font);
    MVS_7(result,character_bitmap,temporary_p,bounding_box_x_offset,
	    bounding_box_y_offset,bounding_box_width,bounding_box_height,
	    character_set_width);
    pformat(2,string_constant_61,micro_font_character_code);
    pformat(2,string_constant_62,character_set_width);
    pformat(3,string_constant_63,FIX(IFIX(bounding_box_width) + 
	    (SI_Long)7L &  ~(SI_Long)7L),FIX(IFIX(bounding_box_height) + 
	    (SI_Long)7L &  ~(SI_Long)7L));
    pformat(3,string_constant_63,bounding_box_x_offset,
	    FIXNUM_ADD(bounding_box_height,bounding_box_y_offset));
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
	      twrite_postscript_bitmap_encoding(character_bitmap,
		      bounding_box_width,bounding_box_height);
	      postscript_bitmap_encoding_string = 
		      copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    pformat(2,string_constant_64,postscript_bitmap_encoding_string);
    reclaim_text_string(postscript_bitmap_encoding_string);
    pformat(1,string_constant_65);
    if (temporary_p)
	return reclaim_temporary_character_bitmap(character_bitmap);
    else
	return VALUES_1(Nil);
}

static Object array_constant_5;    /* # */

static Object string_constant_66;  /* "<" */

static Object string_constant_67;  /* ">" */

/* TWRITE-POSTSCRIPT-BITMAP-ENCODING */
Object twrite_postscript_bitmap_encoding(character_bitmap,
	    bounding_box_width,bounding_box_height)
    Object character_bitmap, bounding_box_width, bounding_box_height;
{
    Object characters_per_row, character_in_hex, character_index, row, column;
    Object i;
    SI_Long width, height, ab_loop_bind_, ab_loop_bind__1, aref_new_value;
    SI_Long ab_loop_repeat_, j;
    Declare_special(2);
    Object result;

    x_note_fn_call(96,106);
    width = IFIX(bounding_box_width) + (SI_Long)7L &  ~(SI_Long)7L;
    height = IFIX(bounding_box_height) + (SI_Long)7L &  ~(SI_Long)7L;
    characters_per_row = ltruncate(FIX((SI_Long)8L * 
	    IFIX(ceiling(FIX(width),FIX((SI_Long)8L)))),FIX((SI_Long)4L));
    character_in_hex = 
	    obtain_simple_text_string(FIX(IFIX(characters_per_row) * height));
    character_index = FIX((SI_Long)-1L);
    row = FIX((SI_Long)0L);
    ab_loop_bind_ = height;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,1);
    next_loop:
      if (IFIX(Row) >= ab_loop_bind_)
	  goto end_loop;
      column = FIX((SI_Long)0L);
      ab_loop_bind__1 = width;
      PUSH_SPECIAL_WITH_SYMBOL(Column,Qcolumn,column,0);
      next_loop_1:
	if (IFIX(Column) >= ab_loop_bind__1)
	    goto end_loop_1;
	character_index = add1(character_index);
	aref_new_value = UBYTE_16_ISAREF_1(array_constant_5,((IFIX(Column) 
		+ (SI_Long)0L < IFIX(bounding_box_width) && FIXNUM_LT(Row,
		bounding_box_height) ? IFIX(aref2(character_bitmap,
		FIX(IFIX(Column) + (SI_Long)0L),Row)) : (SI_Long)0L) << 
		(SI_Long)3L) + ((FIXNUM_LT(FIXNUM_ADD1(Column),
		bounding_box_width) && FIXNUM_LT(Row,bounding_box_height) ?
		 IFIX(aref2(character_bitmap,FIXNUM_ADD1(Column),Row)) : 
		(SI_Long)0L) << (SI_Long)2L) + ((IFIX(Column) + 
		(SI_Long)2L < IFIX(bounding_box_width) && FIXNUM_LT(Row,
		bounding_box_height) ? IFIX(aref2(character_bitmap,
		FIX(IFIX(Column) + (SI_Long)2L),Row)) : (SI_Long)0L) << 
		(SI_Long)1L) + (IFIX(Column) + (SI_Long)3L < 
		IFIX(bounding_box_width) && FIXNUM_LT(Row,
		bounding_box_height) ? IFIX(aref2(character_bitmap,
		FIX(IFIX(Column) + (SI_Long)3L),Row)) : (SI_Long)0L));
	UBYTE_16_ISASET_1(character_in_hex,IFIX(character_index),
		aref_new_value);
	Column = FIX(IFIX(Column) + (SI_Long)4L);
	goto next_loop_1;
      end_loop_1:;
      POP_SPECIAL();
      Row = FIXNUM_ADD1(Row);
      goto next_loop;
    end_loop:
      i = FIX((SI_Long)-1L);
      ab_loop_repeat_ = height;
      tformat(1,string_constant_66);
    next_loop_2:
      if ( !((SI_Long)0L < ab_loop_repeat_))
	  goto end_loop_2;
      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
      j = (SI_Long)0L;
      ab_loop_bind_ = IFIX(characters_per_row);
      if ( !TRUEP(minusp(i)))
	  tformat(1,string_constant_8);
    next_loop_3:
      if (j >= ab_loop_bind_)
	  goto end_loop_3;
      i = add1(i);
      tformat(2,string_constant_23,FIX(UBYTE_16_ISAREF_1(character_in_hex,
	      IFIX(i))));
      j = j + (SI_Long)1L;
      goto next_loop_3;
    end_loop_3:;
      goto next_loop_2;
    end_loop_2:
      tformat(1,string_constant_67);
      reclaim_simple_text_string(character_in_hex);
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

Object Postscript_encoding_for_tilde_escape_characters = UNBOUND;

static Object string_constant_68;  /* " ~A" */

/* POSTSCRIPT-EMIT-ATOM */
Object postscript_emit_atom(atom_1)
    Object atom_1;
{
    x_note_fn_call(96,107);
    return pformat(2,string_constant_68,atom_1);
}

/* POSTSCRIPT-EMIT-LINE-BREAK */
Object postscript_emit_line_break()
{
    x_note_fn_call(96,108);
    return pformat(1,string_constant_36);
}

/* LOOKUP-CURRENT-POSTSCRIPT-ENCODING-FOR-KANJI */
Object lookup_current_postscript_encoding_for_kanji(kanji_font,kanji_code)
    Object kanji_font, kanji_code;
{
    Object cantidate_kanji_code, kanji_microfont_encoding, ab_loop_list_;
    Object ab_loop_desetq_;

    x_note_fn_call(96,109);
    cantidate_kanji_code = Nil;
    kanji_microfont_encoding = Nil;
    ab_loop_list_ = getf(Kanji_fonts_used_in_print_job,kanji_font,_);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    cantidate_kanji_code = CAR(ab_loop_desetq_);
    kanji_microfont_encoding = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQL(cantidate_kanji_code,kanji_code))
	return VALUES_2(FIX(IFIX(kanji_microfont_encoding) >>  -  - 
		(SI_Long)10L),FIX((SI_Long)511L & 
		IFIX(kanji_microfont_encoding)));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_69;  /* "~%(" */

static Object string_constant_70;  /* ")" */

/* POSTSCRIPT-EMIT-TEXT-STRING */
Object postscript_emit_text_string(font,text_string)
    Object font, text_string;
{
    Object non_latin_used_so_far_qm, wide_character, wide_character_code;
    Object character_or_character_code, escape_character_qm, font_code;
    Object character_index, length_1, non_adobe_latin_p;
    Object kanji_postscript_font_number, kanji_postscript_character_code;
    Object unicode, code, extended_code, unicode_1, code_1, temp_2, row;
    Object gensym_character_code_qm, character_code, char_1;
    Object simple_gensym_character_code;
    SI_Long temp, character_1, gensym_full_row, gensymed_symbol;
    SI_Long gensymed_symbol_1;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,110);
    non_latin_used_so_far_qm = Nil;
    wide_character = Nil;
    wide_character_code = Nil;
    character_or_character_code = Nil;
    escape_character_qm = Nil;
    font_code = Nil;
    character_index = FIX((SI_Long)0L);
    length_1 = text_string_length(text_string);
    non_adobe_latin_p = Nil;
    pformat(1,string_constant_69);
  next_loop:
    non_adobe_latin_p = Nil;
    if ( !FIXNUM_LT(character_index,length_1))
	goto end_loop;
    temp = UBYTE_16_ISAREF_1(text_string,IFIX(character_index));
    character_index = FIXNUM_ADD1(character_index);
    character_1 = temp;
    wide_character = EQ(FIX(character_1),FIX((SI_Long)10L)) || 
	    EQ(FIX(character_1),FIX((SI_Long)13L)) ? FIX((SI_Long)8232L) : 
	    FIX(character_1);
    wide_character_code = wide_character;
    font_code = map_unicode_to_ab_latin_font_code_or_zero(wide_character_code);
    if (IFIX(font_code) != (SI_Long)0L) {
	non_adobe_latin_p = assoc_eql(wide_character_code,list_constant_28);
	temp_1 =  !TRUEP(non_adobe_latin_p);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1);
    else if (Use_substitute_for_non_latin_text_p) {
	font_code = 
		map_unicode_to_ab_latin_font_code_or_zero(Substitute_character_for_non_latin_text);
	temp_1 = TRUEP(font_code);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	postscript_emit_string_character_code(font_code);
    else if (non_adobe_latin_p) {
	non_latin_used_so_far_qm = T;
	result = lookup_current_postscript_encoding_for_kanji(font,
		wide_character_code);
	MVS_2(result,kanji_postscript_font_number,
		kanji_postscript_character_code);
	postscript_emit_string_character_code(FIX((SI_Long)27L));
	postscript_emit_string_character_code(kanji_postscript_font_number);
	postscript_emit_string_character_code(kanji_postscript_character_code);
    }
    else {
	unicode = wide_character;
	code = Nil;
	extended_code = Nil;
	unicode_1 = unicode;
	extended_code = Nil;
	code_1 = unicode_1;
	if (IFIX(code_1) < (SI_Long)127L &&  !((SI_Long)64L == 
		IFIX(code_1) || (SI_Long)126L == IFIX(code_1) || 
		(SI_Long)92L == IFIX(code_1))) {
	    code = unicode_1;
	    temp_2 = code;
	}
	else {
	    row = FIX(IFIX(unicode_1) >>  -  - (SI_Long)8L);
	    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	      gensym_full_row = 
		      UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
		      IFIX(Row));
	      if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
		  gensymed_symbol = gensym_full_row << (SI_Long)8L;
		  gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
		  gensym_character_code_qm = FIX(gensymed_symbol + 
			  gensymed_symbol_1);
	      }
	      else
		  gensym_character_code_qm = Nil;
	    POP_SPECIAL();
	    if (gensym_character_code_qm) {
		temp_1 = IFIX(gensym_character_code_qm) < (SI_Long)256L ? 
			TRUEP(ISVREF(Iso_latin1_special_character_code_map,
			IFIX(gensym_character_code_qm))) : TRUEP(Nil);
		if (temp_1);
		else if (FIXNUM_EQ(gensym_character_code_qm,
			Gensym_code_for_capital_ligature_oe))
		    temp_1 = 'W';
		else if (FIXNUM_EQ(gensym_character_code_qm,
			Gensym_code_for_small_ligature_oe))
		    temp_1 = 'w';
		else if (FIXNUM_EQ(gensym_character_code_qm,
			Gensym_code_for_bullet))
		    temp_1 = '*';
		else if (FIXNUM_EQ(gensym_character_code_qm,
			Gensym_code_for_small_letter_f_with_hook))
		    temp_1 = '&';
		else if (FIXNUM_EQ(gensym_character_code_qm,
			Gensym_code_for_trade_mark_sign))
		    temp_1 = ':';
		else
		    temp_1 = TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = (SI_Long)8192L <= 
			    IFIX(gensym_character_code_qm) ? 
			    IFIX(gensym_character_code_qm) <= 
			    (SI_Long)8447L : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		code = gensym_character_code_qm;
		temp_2 = code;
	    }
	    else
		temp_2 = Nil;
	    if (temp_2);
	    else {
		code = map_unicode_to_gensym_han_character_code(unicode_1);
		temp_2 = code;
		if (temp_2);
		else {
		    row = FIX(IFIX(unicode_1) >>  -  - (SI_Long)8L);
		    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		      gensym_full_row = 
			      UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
			      IFIX(Row));
		      if ( !(gensym_full_row == 
				  IFIX(Invalid_gensym_full_row))) {
			  gensymed_symbol = gensym_full_row << (SI_Long)8L;
			  gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
			  code = FIX(gensymed_symbol + gensymed_symbol_1);
		      }
		      else
			  code = Nil;
		    POP_SPECIAL();
		    temp_2 = code;
		    if (temp_2);
		    else {
			gensymed_symbol = (SI_Long)63488L;
			gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
			extended_code = FIX(gensymed_symbol + 
				gensymed_symbol_1);
			code = FIX((SI_Long)63232L + (IFIX(unicode_1) >>  
				-  - (SI_Long)8L));
			temp_2 = code;
		    }
		}
	    }
	}
	character_code = temp_2;
	if (character_code);
	else
	    character_code = Gensym_noncharacter_code;
	char_1 = Nil;
	if (FIXNUM_EQ(character_code,Gensym_code_for_linebreak))
	    result = VALUES_2(Gensym_char_or_code_for_linebreak,
		    Gensym_esc_for_linebreak_qm);
	else if (FIXNUM_EQ(character_code,Gensym_code_for_paragraph_break))
	    result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
		    Gensym_esc_for_paragraph_break_qm);
	else {
	    if ((SI_Long)32L <= IFIX(character_code) && 
		    IFIX(character_code) <= (SI_Long)126L) {
		simple_gensym_character_code = character_code;
		temp_1 =  !(FIXNUM_EQ(simple_gensym_character_code,
			FIX((SI_Long)64L)) || 
			FIXNUM_EQ(simple_gensym_character_code,
			FIX((SI_Long)126L)) || 
			FIXNUM_EQ(simple_gensym_character_code,
			FIX((SI_Long)92L)));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp_2 = CODE_CHAR(character_code);
		result = VALUES_2(temp_2,Nil);
	    }
	    else {
		temp_2 = IFIX(character_code) < (SI_Long)256L ? 
			ISVREF(Iso_latin1_special_character_code_map,
			IFIX(character_code)) : Nil;
		if (temp_2);
		else if (FIXNUM_EQ(character_code,
			Gensym_code_for_capital_ligature_oe))
		    temp_2 = CHR('W');
		else if (FIXNUM_EQ(character_code,
			Gensym_code_for_small_ligature_oe))
		    temp_2 = CHR('w');
		else if (FIXNUM_EQ(character_code,Gensym_code_for_bullet))
		    temp_2 = CHR('*');
		else if (FIXNUM_EQ(character_code,
			Gensym_code_for_small_letter_f_with_hook))
		    temp_2 = CHR('&');
		else if (FIXNUM_EQ(character_code,
			Gensym_code_for_trade_mark_sign))
		    temp_2 = CHR(':');
		else
		    temp_2 = Qnil;
		char_1 = temp_2;
		if (char_1)
		    result = VALUES_2(char_1,CHR('~'));
		else
		    result = VALUES_2(character_code,CHR('\\'));
	    }
	}
	MVS_2(result,character_or_character_code,escape_character_qm);
	if ( !CHARACTERP(escape_character_qm))
	    postscript_emit_string_character(character_or_character_code);
	else
	    switch (ICHAR_CODE(escape_character_qm)) {
	      case '~':
		postscript_emit_string_character_code(ISVREF(Postscript_encoding_for_tilde_escape_characters,
			IFIX(CHAR_CODE(character_or_character_code))));
		break;
	      case '\\':
		non_latin_used_so_far_qm = T;
		result = lookup_current_postscript_encoding_for_kanji(font,
			wide_character_code);
		MVS_2(result,kanji_postscript_font_number,
			kanji_postscript_character_code);
		postscript_emit_string_character_code(FIX((SI_Long)27L));
		postscript_emit_string_character_code(kanji_postscript_font_number);
		postscript_emit_string_character_code(kanji_postscript_character_code);
		break;
	      case '@':
		break;
	      default:
		postscript_emit_string_character(character_or_character_code);
		break;
	    }
    }
    goto next_loop;
  end_loop:
    pformat(1,string_constant_70);
    return VALUES_1(non_latin_used_so_far_qm);
    return VALUES_1(Qnil);
}

static Object list_constant_33;    /* # */

/* POSTSCRIPT-EMIT-STRING-CHARACTER */
Object postscript_emit_string_character(c)
    Object c;
{
    Object char_code_1, c2;

    x_note_fn_call(96,111);
    char_code_1 = CHAR_CODE(c);
    c2 = Nil;
    if (EQ(c,CHR('(')) || EQ(c,CHR(')')) || EQ(c,CHR('\\'))) {
	g2_stream_write_char(CHR('\\'),Printing_stream);
	return g2_stream_write_char(c,Printing_stream);
    }
    else {
	c2 = getf(list_constant_33,c,_);
	if (c2) {
	    g2_stream_write_char(CHR('\\'),Printing_stream);
	    return g2_stream_write_char(c2,Printing_stream);
	}
	else if ((SI_Long)32L <= IFIX(char_code_1) && IFIX(char_code_1) <= 
		(SI_Long)126L)
	    return g2_stream_write_char(c,Printing_stream);
	else {
	    g2_stream_write_char(CHR('\\'),Printing_stream);
	    return postscript_emit_octal_digit(char_code_1,FIX((SI_Long)64L));
	}
    }
}

/* POSTSCRIPT-EMIT-STRING-CHARACTER-CODE */
Object postscript_emit_string_character_code(char_code_1)
    Object char_code_1;
{
    Object temp;

    x_note_fn_call(96,112);
    temp = EQ(char_code_1,Nil) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if ((SI_Long)32L <= IFIX(char_code_1) && IFIX(char_code_1) <= 
	    (SI_Long)126L)
	return postscript_emit_string_character(CODE_CHAR(char_code_1));
    else if ((SI_Long)0L <= IFIX(char_code_1) && IFIX(char_code_1) <= 
	    (SI_Long)255L) {
	g2_stream_write_char(CHR('\\'),Printing_stream);
	return postscript_emit_octal_digit(char_code_1,FIX((SI_Long)64L));
    }
    else
	return g2_stream_write_char(CHR('\?'),Printing_stream);
}

static Object string_constant_71;  /* "0" */

/* POSTSCRIPT-EMIT-OCTAL-DIGIT */
Object postscript_emit_octal_digit(small_octal_number,octal_decade)
    Object small_octal_number, octal_decade;
{
    Object temp, quotient, remainder_1;
    SI_Long gensymed_symbol;
    Object result;

    x_note_fn_call(96,113);
    temp = IFIX(octal_decade) == (SI_Long)0L ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (FIXNUM_LT(small_octal_number,octal_decade)) {
	g2_stream_write_string(string_constant_71,Printing_stream);
	return postscript_emit_octal_digit(small_octal_number,
		ltruncate(octal_decade,FIX((SI_Long)8L)));
    }
    else {
	result = chestnut_floorf_function(small_octal_number,FIX((SI_Long)8L));
	MVS_2(result,quotient,remainder_1);
	postscript_emit_octal_digit(quotient,ltruncate(octal_decade,
		FIX((SI_Long)8L)));
	gensymed_symbol = IFIX(remainder_1);
	return pformat(2,string_constant_23,gensymed_symbol >= (SI_Long)0L 
		&& gensymed_symbol < (SI_Long)8L ? FIX((SI_Long)48L + 
		gensymed_symbol) : Nil);
    }
}

Object Write_hex_table = UNBOUND;

Object Postscript_emit_hex_byte_string = UNBOUND;

Object Postscript_emit_rgb_string = UNBOUND;

/* POSTSCRIPT-EMIT-MANAGED-FLOAT */
Object postscript_emit_managed_float(managed_float)
    Object managed_float;
{
    x_note_fn_call(96,114);
    return pformat(2,string_constant_62,
	    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_float,
	    (SI_Long)0L)));
}

static Object string_constant_72;  /* "~( /~a~)" */

/* POSTSCRIPT-EMIT-SYMBOL */
Object postscript_emit_symbol(symbol)
    Object symbol;
{
    x_note_fn_call(96,115);
    return pformat(2,string_constant_72,symbol);
}

/* POSTSCRIPT-EMIT-RECTANGLE */
Object postscript_emit_rectangle(left,top,right,bottom)
    Object left, top, right, bottom;
{
    x_note_fn_call(96,116);
    postscript_emit_atom(left);
    postscript_emit_atom(top);
    postscript_emit_atom(right);
    return postscript_emit_atom(bottom);
}

/* POSTSCRIPT-EMIT-COLOR-VALUE */
Object postscript_emit_color_value(color_value)
    Object color_value;
{
    x_note_fn_call(96,117);
    return postscript_emit_atom(color_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Adding_from_graph_rendering_p, Qadding_from_graph_rendering_p);

static Object string_constant_73;  /* "$bw" */

static Object string_constant_74;  /* "$bm" */

/* POSTSCRIPT-EMIT-SCRATCHPAD-COLOR */
Object postscript_emit_scratchpad_color(color_value)
    Object color_value;
{
    x_note_fn_call(96,118);
    if (Printing_icon_current_region_index_qm) {
	postscript_emit_atom(Printing_icon_current_region_index_qm);
	return postscript_emit_operator_1(string_constant_73);
    }
    else if (Adding_from_graph_rendering_p)
	return postscript_emit_atom(color_value);
    else
	return postscript_emit_operator_1(string_constant_74);
}

/* POSTSCRIPT-EMIT-INTEGER */
Object postscript_emit_integer(integer)
    Object integer;
{
    x_note_fn_call(96,119);
    return postscript_emit_atom(integer);
}

static Object Kpaint_infered_from_xor;  /* :paint-infered-from-xor */

/* POSTSCRIPT-EMIT-COLOR-DIFFERENCE */
Object postscript_emit_color_difference(color_difference)
    Object color_difference;
{
    x_note_fn_call(96,120);
    return postscript_emit_atom((EQ(Current_drawing_transfer_mode,
	    Kpaint_infered_from_xor) ? FIXNUM_EQ(color_difference,
	    Transparent_color_value) : IFIX(color_difference) == 
	    (SI_Long)0L || FIXNUM_EQ(color_difference,
	    Transparent_color_value)) ? Postscript_transparent_color_value 
	    : FIXNUM_LOGXOR(color_difference,Current_background_color_value));
}

/* POSTSCRIPT-EMIT-SCALLING */
Object postscript_emit_scalling(x_scale,y_scale)
    Object x_scale, y_scale;
{
    x_note_fn_call(96,121);
    postscript_emit_atom(x_scale);
    return postscript_emit_atom(y_scale);
}

/* POSTSCRIPT-EMIT-POINT */
Object postscript_emit_point(x,y)
    Object x, y;
{
    x_note_fn_call(96,122);
    postscript_emit_atom(x);
    return postscript_emit_atom(y);
}

/* POSTSCRIPT-EMIT-BOOLEAN */
Object postscript_emit_boolean(boolean_1)
    Object boolean_1;
{
    x_note_fn_call(96,123);
    return postscript_emit_atom(boolean_1 ? FIX((SI_Long)1L) : 
	    FIX((SI_Long)0L));
}

/* POSTSCRIPT-EMIT-UNSIGNED-INTEGER */
Object postscript_emit_unsigned_integer(unsigned_integer)
    Object unsigned_integer;
{
    x_note_fn_call(96,124);
    return postscript_emit_atom(unsigned_integer);
}

/* POSTSCRIPT-EMIT-FONT-MAP */
Object postscript_emit_font_map(font_map)
    Object font_map;
{
    Object postscript_emit_composite_object_without_name;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,125);
    postscript_emit_composite_object_without_name = T;
    PUSH_SPECIAL_WITH_SYMBOL(Postscript_emit_composite_object_without_name,Qpostscript_emit_composite_object_without_name,postscript_emit_composite_object_without_name,
	    0);
      result = postscript_emit_composite_object_definition(3,font_map,
	      array_constant_3,Qpostscript_emit_composite_object);
    POP_SPECIAL();
    return result;
}

/* POSTSCRIPT-EMIT-LIST-OF-COLORS */
Object postscript_emit_list_of_colors(list_of_colors,use_differences_p)
    Object list_of_colors, use_differences_p;
{
    Object postscript_emit_composite_object_without_name;
    Object postscript_emit_integers_as_color_differences;
    Declare_special(2);
    Object result;

    x_note_fn_call(96,126);
    postscript_emit_composite_object_without_name = T;
    postscript_emit_integers_as_color_differences = use_differences_p;
    PUSH_SPECIAL_WITH_SYMBOL(Postscript_emit_integers_as_color_differences,Qpostscript_emit_integers_as_color_differences,postscript_emit_integers_as_color_differences,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Postscript_emit_composite_object_without_name,Qpostscript_emit_composite_object_without_name,postscript_emit_composite_object_without_name,
	      0);
	result = postscript_emit_composite_object_definition(3,
		list_of_colors,array_constant_3,
		Qpostscript_emit_composite_object);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* POSTSCRIPT-EMIT-COLOR-MAP */
Object postscript_emit_color_map(color_map)
    Object color_map;
{
    x_note_fn_call(96,127);
    return error((SI_Long)1L,"Unimplemented");
}

/* POSTSCRIPT-EMIT-GENSYM-WINDOW */
Object postscript_emit_gensym_window(window)
    Object window;
{
    x_note_fn_call(96,128);
    return error((SI_Long)1L,"Unimplemented");
}

static Object Qblack;              /* black */

static Object Qwhite;              /* white */

static Object list_constant_34;    /* # */

/* MAKE-PRINTING-COLOR-DESCRIPTION-PLIST */
Object make_printing_color_description_plist()
{
    Object temp, last_color_number, color, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp_1;

    x_note_fn_call(96,129);
    temp = gensym_list_4(Qblack,gensym_cons_1(FIX((SI_Long)0L),Nil),Qwhite,
	    gensym_cons_1(FIX((SI_Long)1L),Nil));
    last_color_number = FIX((SI_Long)1L);
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
    if ( !TRUEP(memq_function(color,list_constant_34))) {
	ab_loopvar__2 = gensym_cons_1(color,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	last_color_number = FIXNUM_ADD1(last_color_number);
	ab_loopvar__2 = gensym_cons_1(gensym_cons_1(last_color_number,Nil),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(nconc2(temp,temp_1));
}

/* MAKE-TRUE-COLOR-DESCRIPTION-PLIST */
Object make_true_color_description_plist()
{
    Object color, r, g, b, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(96,130);
    color = Nil;
    r = Nil;
    g = Nil;
    b = Nil;
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
    ab_loopvar__2 = gensym_cons_1(color,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    gensymed_symbol = IFIX(b) & (SI_Long)255L;
    gensymed_symbol_1 = (SI_Long)16L;
    gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
    gensymed_symbol_2 = IFIX(g) & (SI_Long)255L;
    gensymed_symbol = (SI_Long)8L;
    gensymed_symbol = gensymed_symbol_2 << gensymed_symbol;
    gensymed_symbol_2 = IFIX(r) & (SI_Long)255L;
    ab_loopvar__2 = gensym_cons_1(gensym_cons_1(FIX(gensymed_symbol_1 | 
	    gensymed_symbol | gensymed_symbol_2),Nil),Nil);
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

/* MAKE-GRAY-TRUE-COLOR-DESCRIPTION-PLIST */
Object make_gray_true_color_description_plist()
{
    Object color, r, g, b, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp, r_1, g_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(96,131);
    color = Nil;
    r = Nil;
    g = Nil;
    b = Nil;
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
    ab_loopvar__2 = gensym_cons_1(color,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    r_1 = rgb2gray(r,g,b);
    g_1 = rgb2gray(r,g,b);
    b = rgb2gray(r,g,b);
    gensymed_symbol = IFIX(b) & (SI_Long)255L;
    gensymed_symbol_1 = (SI_Long)16L;
    gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
    gensymed_symbol_2 = IFIX(g_1) & (SI_Long)255L;
    gensymed_symbol = (SI_Long)8L;
    gensymed_symbol = gensymed_symbol_2 << gensymed_symbol;
    gensymed_symbol_2 = IFIX(r_1) & (SI_Long)255L;
    ab_loopvar__2 = gensym_cons_1(gensym_cons_1(FIX(gensymed_symbol_1 | 
	    gensymed_symbol | gensymed_symbol_2),Nil),Nil);
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

static Object string_constant_75;  /* "~%/full-color-map[" */

static Object string_constant_76;  /* "~%]def" */

static Object string_constant_77;  /* "~%/gray-color-map[" */

/* EMIT-PRINTING-COLOR-MAP */
Object emit_printing_color_map()
{
    Object color_qm, alist_entry_qm, standard_gensym_color_alist;
    SI_Long color_value, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,132);
    color_value = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(Standard_gensym_color_alist));
    color_qm = Nil;
    alist_entry_qm = Nil;
    pformat(1,string_constant_75);
  next_loop:
    if (color_value >= ab_loop_bind_)
	goto end_loop;
    color_qm = map_to_color(FIX(color_value));
    alist_entry_qm = assq_function(color_qm,Standard_gensym_color_alist);
    emit_printing_color_map_1(FIX(color_value),alist_entry_qm);
    color_value = color_value + (SI_Long)1L;
    goto next_loop;
  end_loop:
    pformat(1,string_constant_76);
    standard_gensym_color_alist = Gray_gensym_color_alist;
    PUSH_SPECIAL_WITH_SYMBOL(Standard_gensym_color_alist,Qstandard_gensym_color_alist,standard_gensym_color_alist,
	    0);
      color_value = (SI_Long)0L;
      ab_loop_bind_ = IFIX(length(Standard_gensym_color_alist));
      color_qm = Nil;
      alist_entry_qm = Nil;
      pformat(1,string_constant_77);
    next_loop_1:
      if (color_value >= ab_loop_bind_)
	  goto end_loop_1;
      color_qm = map_to_color(FIX(color_value));
      alist_entry_qm = assq_function(color_qm,Standard_gensym_color_alist);
      emit_printing_color_map_1(FIX(color_value),alist_entry_qm);
      color_value = color_value + (SI_Long)1L;
      goto next_loop_1;
    end_loop_1:
      pformat(1,string_constant_76);
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_78;  /* "~%[" */

static Object string_constant_79;  /* "~D" */

static Object string_constant_80;  /* "]% ~D ~(~S~)" */

static Object string_constant_81;  /* "~%[255 255 255]% ~D none" */

/* EMIT-PRINTING-COLOR-MAP-1 */
Object emit_printing_color_map_1(index_1,alist_entry_qm)
    Object index_1, alist_entry_qm;
{
    Object gensymed_symbol, color, red, green, blue;

    x_note_fn_call(96,133);
    if (alist_entry_qm) {
	gensymed_symbol = alist_entry_qm;
	color = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	red = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	green = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	blue = CAR(gensymed_symbol);
	pformat(1,string_constant_78);
	pformat(2,string_constant_79,red);
	pformat(2,string_constant_62,green);
	pformat(2,string_constant_62,blue);
	return pformat(3,string_constant_80,index_1,color);
    }
    else
	return pformat(2,string_constant_81,index_1);
}

/* DEFAULT-PRINT-HANDLER-FOR-ICP-MESSAGES */
Object default_print_handler_for_icp_messages varargs_1(int, n)
{
    Declare_varargs_nonrelocating;

    x_note_fn_call(96,134);
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

/* HANDLER-FOR-PRINTING-I-AM-ALIVE */
Object handler_for_printing_i_am_alive(message_group_id)
    Object message_group_id;
{
    x_note_fn_call(96,135);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE */
Object handler_for_printing_enlarge_corresponding_icp_object_index_space(name_of_corresponding_icp_object_index_space,
	    new_index_limit_plus_one)
    Object name_of_corresponding_icp_object_index_space;
    Object new_index_limit_plus_one;
{
    x_note_fn_call(96,136);
    if (IFIX(Printing_pass_number) == (SI_Long)2L)
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-NOP */
Object handler_for_printing_nop(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    x_note_fn_call(96,137);
    if (IFIX(Printing_pass_number) == (SI_Long)2L)
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-DEFINE-DUMMY-OBJECT */
Object handler_for_printing_define_dummy_object(corresponding_icp_object_index)
    Object corresponding_icp_object_index;
{
    x_note_fn_call(96,138);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-INITIALIZE-TELEWINDOWS-WORKSTATION */
Object handler_for_printing_initialize_telewindows_workstation(workstation,
	    gensym_window)
    Object workstation, gensym_window;
{
    x_note_fn_call(96,139);
    return VALUES_1(Nil);
}

static Object string_constant_82;  /* "$bf" */

/* HANDLER-FOR-PRINTING-BEGIN-WINDOW-UPDATE */
Object handler_for_printing_begin_window_update(gensym_window,
	    left_edge_of_update_area,top_edge_of_update_area,
	    right_edge_of_update_area,bottom_edge_of_update_area)
    Object gensym_window, left_edge_of_update_area, top_edge_of_update_area;
    Object right_edge_of_update_area, bottom_edge_of_update_area;
{
    x_note_fn_call(96,140);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_gensym_window(gensym_window);
	postscript_emit_rectangle(left_edge_of_update_area,
		top_edge_of_update_area,right_edge_of_update_area,
		bottom_edge_of_update_area);
	return postscript_emit_operator_1(string_constant_82);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SCROLL-RECTANGLE-IN-CURRENT-WINDOW */
Object handler_for_printing_scroll_rectangle_in_current_window(source_left,
	    source_top,width,height,destination_left,destination_top)
    Object source_left, source_top, width, height, destination_left;
    Object destination_top;
{
    x_note_fn_call(96,141);
    return VALUES_1(Nil);
}

static Object string_constant_83;  /* "$ef" */

/* HANDLER-FOR-PRINTING-SET-UP-PALETTE */
Object handler_for_printing_set_up_palette(gensym_window,color_map)
    Object gensym_window, color_map;
{
    x_note_fn_call(96,142);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_gensym_window(gensym_window);
	postscript_emit_color_map(color_map);
	return postscript_emit_operator_1(string_constant_83);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-TELEWINDOWS-WORKSTATION-EVENT */
Object handler_for_printing_telewindows_workstation_event(workstation,
	    event_code,x,y,timestamp)
    Object workstation, event_code, x, y, timestamp;
{
    x_note_fn_call(96,143);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-EXTENDED-TELEWINDOWS-WORKSTATION-EVENT */
Object handler_for_printing_extended_telewindows_workstation_event(workstation,
	    event_code,x,y,timestamp,plist)
    Object workstation, event_code, x, y, timestamp, plist;
{
    x_note_fn_call(96,144);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-DEFINE-TELEWINDOWS-WORKSTATION */
Object handler_for_printing_define_telewindows_workstation(corresponding_icp_object_index)
    Object corresponding_icp_object_index;
{
    x_note_fn_call(96,145);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SET-POSITION-OF-MOUSE */
Object handler_for_printing_set_position_of_mouse(x,y)
    Object x, y;
{
    x_note_fn_call(96,146);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-DEFINE-GENSYM-WINDOW */
Object handler_for_printing_define_gensym_window(corresponding_icp_object_index,
	    left_edge_in_window,top_edge_in_window,right_edge_in_window,
	    bottom_edge_in_window,window_parameters_plist,
	    corresponding_icp_object_index_on_other_side_qm)
    Object corresponding_icp_object_index, left_edge_in_window;
    Object top_edge_in_window, right_edge_in_window, bottom_edge_in_window;
    Object window_parameters_plist;
    Object corresponding_icp_object_index_on_other_side_qm;
{
    x_note_fn_call(96,147);
    return VALUES_1(Nil);
}

static Object string_constant_84;  /* "$co" */

/* HANDLER-FOR-PRINTING-INITIALIZE-SCRATCHPAD-RASTER */
Object handler_for_printing_initialize_scratchpad_raster(gensym_window,
	    minimum_width,minimum_height,bits_per_pixel,make_exact_size_p)
    Object gensym_window, minimum_width, minimum_height, bits_per_pixel;
    Object make_exact_size_p;
{
    x_note_fn_call(96,148);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_gensym_window(gensym_window);
	postscript_emit_unsigned_integer(minimum_width);
	postscript_emit_unsigned_integer(minimum_height);
	postscript_emit_unsigned_integer(bits_per_pixel);
	postscript_emit_boolean(make_exact_size_p);
	return postscript_emit_operator_1(string_constant_84);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_85;  /* "$dk" */

/* HANDLER-FOR-PRINTING-PAINT-SOLID-RECTANGLE-IN-CURRENT-SCRATCHPAD-RASTER */
Object handler_for_printing_paint_solid_rectangle_in_current_scratchpad_raster(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    color_value)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, color_value;
{
    x_note_fn_call(96,149);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_rectangle(clipped_left_edge,clipped_top_edge,
		clipped_right_edge,clipped_bottom_edge);
	postscript_emit_scratchpad_color(color_value);
	return postscript_emit_operator_1(string_constant_85);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_86;  /* "$di" */

/* HANDLER-FOR-PRINTING-PAINT-LINE-IN-CURRENT-SCRATCHPAD-RASTER */
Object handler_for_printing_paint_line_in_current_scratchpad_raster(x1,
	    y1_1,x2,y2,color_value,paint_last_point_qm)
    Object x1, y1_1, x2, y2, color_value, paint_last_point_qm;
{
    x_note_fn_call(96,150);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_point(x1,y1_1);
	postscript_emit_point(x2,y2);
	postscript_emit_scratchpad_color(color_value);
	postscript_emit_boolean(paint_last_point_qm);
	return postscript_emit_operator_1(string_constant_86);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_87;  /* "$db" */

/* HANDLER-FOR-PRINTING-PAINT-ARC-OR-CIRCLE-IN-CURRENT-SCRATCHPAD-RASTER */
Object handler_for_printing_paint_arc_or_circle_in_current_scratchpad_raster(x1,
	    y1_1,x2,y2,x3,y3,x_scale,y_scale,color_value,circle_qm,filled_qm)
    Object x1, y1_1, x2, y2, x3, y3, x_scale, y_scale, color_value, circle_qm;
    Object filled_qm;
{
    x_note_fn_call(96,151);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_point(x3,y3);
	postscript_emit_point(x2,y2);
	postscript_emit_point(x1,y1_1);
	postscript_emit_scalling(x_scale,y_scale);
	postscript_emit_scratchpad_color(color_value);
	postscript_emit_boolean(circle_qm);
	postscript_emit_boolean(filled_qm);
	return postscript_emit_operator_1(string_constant_87);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_88;  /* "$dc" */

/* HANDLER-FOR-PRINTING-PAINT-FILLED-TRIANGLE-IN-CURRENT-SCRATCHPAD-RASTER */
Object handler_for_printing_paint_filled_triangle_in_current_scratchpad_raster(x1,
	    y1_1,x2,y2,x3,y3,color_value)
    Object x1, y1_1, x2, y2, x3, y3, color_value;
{
    x_note_fn_call(96,152);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_point(x1,y1_1);
	postscript_emit_point(x2,y2);
	postscript_emit_point(x3,y3);
	postscript_emit_scratchpad_color(color_value);
	return postscript_emit_operator_1(string_constant_88);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-PAINT-FILLED-POLYGON-IN-CURRENT-SCRATCHPAD-RASTER */
Object handler_for_printing_paint_filled_polygon_in_current_scratchpad_raster(unsigned_polygon_point_list,
	    color_value)
    Object unsigned_polygon_point_list, color_value;
{
    x_note_fn_call(96,153);
    if (IFIX(Printing_pass_number) == (SI_Long)2L)
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_89;  /* "$dm" */

/* HANDLER-FOR-PRINTING-PAINT-WIDE-LINE-IN-CURRENT-SCRATCHPAD-RASTER */
Object handler_for_printing_paint_wide_line_in_current_scratchpad_raster(x1,
	    y1_1,x2,y2,color_value,paint_last_point_qm,line_width)
    Object x1, y1_1, x2, y2, color_value, paint_last_point_qm, line_width;
{
    x_note_fn_call(96,154);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_point(x1,y1_1);
	postscript_emit_point(x2,y2);
	postscript_emit_scratchpad_color(color_value);
	postscript_emit_boolean(paint_last_point_qm);
	postscript_emit_unsigned_integer(line_width);
	return postscript_emit_operator_1(string_constant_89);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_90;  /* "$dj" */

/* HANDLER-FOR-PRINTING-PAINT-POINT-IN-CURRENT-SCRATCHPAD-RASTER */
Object handler_for_printing_paint_point_in_current_scratchpad_raster(x,y,
	    color_value)
    Object x, y, color_value;
{
    x_note_fn_call(96,155);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_point(x,y);
	postscript_emit_scratchpad_color(color_value);
	return postscript_emit_operator_1(string_constant_90);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_91;  /* "gsave" */

static Object string_constant_92;  /* "savectm" */

static Object string_constant_93;  /* "clip-to-rectangle" */

static Object string_constant_94;  /* "translate" */

static Object string_constant_95;  /* "g~D" */

static Object string_constant_96;  /* "restorectm" */

static Object string_constant_97;  /* "grestore" */

/* HANDLER-FOR-PRINTING-PAINT-ICON-ONTO-GRAPH-RASTER */
Object handler_for_printing_paint_icon_onto_graph_raster(icon_rendering,
	    clip_left,clip_top,clip_right,clip_bottom,origin_left,
	    origin_top,color_value)
    Object icon_rendering, clip_left, clip_top, clip_right, clip_bottom;
    Object origin_left, origin_top, color_value;
{
    Object line_drawing, first_element, polychrome_header_qm;
    Object printing_icon_current_region_index_qm;
    Object line_drawing_description_following_header;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,156);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	line_drawing = ISVREF(icon_rendering,(SI_Long)8L);
	first_element = CAR(line_drawing);
	polychrome_header_qm = CONSP(first_element) && 
		EQ(CAR(first_element),Qpolychrome) ? first_element : Nil;
	printing_icon_current_region_index_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Printing_icon_current_region_index_qm,Qprinting_icon_current_region_index_qm,printing_icon_current_region_index_qm,
		0);
	  line_drawing_description_following_header = polychrome_header_qm 
		  ? CDR(line_drawing) : line_drawing;
	  postscript_emit_operator_1(string_constant_91);
	  postscript_emit_operator_1(string_constant_92);
	  postscript_emit_atom(clip_left);
	  postscript_emit_atom(clip_top);
	  postscript_emit_atom(clip_right);
	  postscript_emit_atom(clip_bottom);
	  postscript_emit_operator_1(string_constant_93);
	  postscript_emit_atom(origin_left);
	  postscript_emit_atom(origin_top);
	  postscript_emit_operator_1(string_constant_94);
	  pformat(2,string_constant_95,
		  get_embedded_icon_layer_index(color_value,
		  line_drawing_description_following_header));
	  postscript_emit_operator_1(string_constant_96);
	  result = postscript_emit_operator_1(string_constant_97);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* GET-EMBEDDED-ICON-LAYER-INDEX */
Object get_embedded_icon_layer_index(color_value,line_drawing_description)
    Object color_value, line_drawing_description;
{
    Object index_1, indexed_color_value, indexed_line_drawing_description;
    Object ab_loop_list_, ab_loop_desetq_, temp, triple;

    x_note_fn_call(96,157);
    index_1 = Nil;
    indexed_color_value = Nil;
    indexed_line_drawing_description = Nil;
    ab_loop_list_ = Current_graph_rendering_embedded_icons;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    index_1 = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    indexed_color_value = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    indexed_line_drawing_description = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQL(color_value,indexed_color_value) && 
	    EQ(line_drawing_description,indexed_line_drawing_description))
	return VALUES_1(index_1);
    goto next_loop;
  end_loop:
    triple = printing_list_3(reserve_composite_object_index(),color_value,
	    line_drawing_description);
    Current_graph_rendering_embedded_icons = printing_cons_1(triple,
	    Current_graph_rendering_embedded_icons);
    return VALUES_1(CAR(triple));
    return VALUES_1(Qnil);
}

static Object Qemit_embedded_icon_layer_definition_1;  /* emit-embedded-icon-layer-definition-1 */

/* EMIT-EMBEDDED-ICON-LAYER-DEFINITION */
Object emit_embedded_icon_layer_definition(index_1,
	    color_and_line_drawing_description)
    Object index_1, color_and_line_drawing_description;
{
    x_note_fn_call(96,158);
    return postscript_emit_composite_object_definition(4,
	    color_and_line_drawing_description,array_constant_4,
	    Qemit_embedded_icon_layer_definition_1,index_1);
}

/* EMIT-EMBEDDED-ICON-LAYER-DEFINITION-1 */
Object emit_embedded_icon_layer_definition_1(color_and_line_drawing_description)
    Object color_and_line_drawing_description;
{
    Object color_value, line_drawing_description;
    SI_Long width, height;

    x_note_fn_call(96,159);
    color_value = CAR(color_and_line_drawing_description);
    line_drawing_description = CADR(color_and_line_drawing_description);
    width = (SI_Long)10000L;
    height = (SI_Long)10000L;
    return paint_one_bitmap_for_icon_on_scratchpad_raster(Qforeground,
	    line_drawing_description,FIX(width),FIX(height),
	    FIX((SI_Long)4096L),FIX((SI_Long)4096L),color_value,Nil,Nil,
	    FIX(width),FIX(height),Nil);
}

/* HANDLER-FOR-PRINTING-PAINT-MARKER-ONTO-GRAPH-RASTER */
Object handler_for_printing_paint_marker_onto_graph_raster(icon_rendering,
	    x_in_graph_raster,y_in_graph_raster,color_value)
    Object icon_rendering, x_in_graph_raster, y_in_graph_raster, color_value;
{
    x_note_fn_call(96,160);
    if (IFIX(Printing_pass_number) == (SI_Long)2L)
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

static Object Qnormal;             /* normal */

static Object Qclockwise_90;       /* clockwise-90 */

static Object Qclockwise_180;      /* clockwise-180 */

static Object Qclockwise_270;      /* clockwise-270 */

static Object Qreflected;          /* reflected */

static Object Qreflected_clockwise_90;  /* reflected-clockwise-90 */

static Object Qreflected_clockwise_180;  /* reflected-clockwise-180 */

static Object Qreflected_clockwise_270;  /* reflected-clockwise-270 */

/* CONVERT-ROTATION-TO-DEGREES */
Object convert_rotation_to_degrees(rotation_and_reflection)
    Object rotation_and_reflection;
{
    x_note_fn_call(96,161);
    if (EQ(rotation_and_reflection,Qnormal))
	return VALUES_1(FIX((SI_Long)0L));
    else if (EQ(rotation_and_reflection,Qclockwise_90))
	return VALUES_1(FIX((SI_Long)90L));
    else if (EQ(rotation_and_reflection,Qclockwise_180))
	return VALUES_1(FIX((SI_Long)180L));
    else if (EQ(rotation_and_reflection,Qclockwise_270))
	return VALUES_1(FIX((SI_Long)270L));
    else if (EQ(rotation_and_reflection,Qreflected))
	return VALUES_1(FIX((SI_Long)0L));
    else if (EQ(rotation_and_reflection,Qreflected_clockwise_90))
	return VALUES_1(FIX((SI_Long)90L));
    else if (EQ(rotation_and_reflection,Qreflected_clockwise_180))
	return VALUES_1(FIX((SI_Long)180L));
    else if (EQ(rotation_and_reflection,Qreflected_clockwise_270))
	return VALUES_1(FIX((SI_Long)280L));
    else
	return VALUES_1(FIX((SI_Long)0L));
}

/* HANDLER-FOR-PRINTING-PAINT-ICON-BACKGROUND-IMAGE-IN-CURRENT-WINDOW */
Object handler_for_printing_paint_icon_background_image_in_current_window(image_data,
	    x_in_window,y_in_window,left,top,right,bottom,x_scale,y_scale,
	    rotation,quality,foreground_color,background_color,
	    image_left_offset_in_ws,image_top_offset_in_ws,
	    rotated_width_in_ws,rotated_height_in_ws)
    Object image_data, x_in_window, y_in_window, left, top, right, bottom;
    Object x_scale, y_scale, rotation, quality, foreground_color;
    Object background_color, image_left_offset_in_ws, image_top_offset_in_ws;
    Object rotated_width_in_ws, rotated_height_in_ws;
{
    Object temp, scaled_image_left_offset_in_ws, scaled_image_top_offset_in_ws;
    double temp_1, ps_x_scale, ps_y_scale;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(96,162);
    PUSH_SPECIAL_WITH_SYMBOL(Image_top_offset_in_ws,Qimage_top_offset_in_ws,image_top_offset_in_ws,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Image_left_offset_in_ws,Qimage_left_offset_in_ws,image_left_offset_in_ws,
	      0);
	if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	    if ( !TRUEP(rotation) || EQ(rotation,Qnormal)) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    temp = lfloat(x_scale,float_constant);
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
		    ps_x_scale = temp_1 / 4096.0;
		    temp = lfloat(y_scale,float_constant);
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
		    ps_y_scale = temp_1 / 4096.0;
		    scaled_image_left_offset_in_ws = 
			    l_round(ltimes(DOUBLE_TO_DOUBLE_FLOAT(ps_x_scale),
			    Image_left_offset_in_ws),_);
		    scaled_image_top_offset_in_ws = 
			    l_round(ltimes(DOUBLE_TO_DOUBLE_FLOAT(ps_y_scale),
			    Image_top_offset_in_ws),_);
		    result = paint_image_in_postscript(image_data,
			    FIXNUM_ADD(x_in_window,
			    scaled_image_left_offset_in_ws),
			    FIXNUM_ADD(y_in_window,
			    scaled_image_top_offset_in_ws),left,top,right,
			    bottom,x_scale,y_scale,rotation,quality,
			    foreground_color,background_color);
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* HANDLER-FOR-PRINTING-PAINT-IMAGE-IN-CURRENT-WINDOW */
Object handler_for_printing_paint_image_in_current_window(image_data,
	    x_in_window,y_in_window,left,top,right,bottom,x_scale,y_scale,
	    rotation,quality,foreground_color,background_color)
    Object image_data, x_in_window, y_in_window, left, top, right, bottom;
    Object x_scale, y_scale, rotation, quality, foreground_color;
    Object background_color;
{
    x_note_fn_call(96,163);
    if (IFIX(Printing_pass_number) == (SI_Long)2L)
	return paint_image_in_postscript(image_data,x_in_window,
		y_in_window,left,top,right,bottom,x_scale,y_scale,rotation,
		quality,foreground_color,background_color);
    else
	return VALUES_1(Nil);
}

static Object string_constant_98;  /* "/imagestring ~d string def~%" */

static Object string_constant_99;  /* "div" */

static Object string_constant_100;  /* "mul" */

static Object string_constant_101;  /* "scale" */

static Object string_constant_102;  /* " [~d 0 0 ~d 0 0]~%" */

static Object string_constant_103;  /* " {currentfile imagestring readhexstring pop}~%" */

static Object string_constant_104;  /* "false" */

static Object string_constant_105;  /* "colorimage" */

static Object string_constant_106;  /* "~%~%" */

static Object string_constant_107;  /* "image" */

/* PAINT-IMAGE-IN-POSTSCRIPT */
Object paint_image_in_postscript(image_data,x_in_window,y_in_window,left,
	    top,right,bottom,x_scale,y_scale,rotation,quality,
	    foreground_color,background_color)
    Object image_data, x_in_window, y_in_window, left, top, right, bottom;
    Object x_scale, y_scale, rotation, quality, foreground_color;
    Object background_color;
{
    Object width, height, depth, color_map, gray_map, raster_qm, in_color_p;
    Object flipped_one_bit_image_p, bits_per_component, characters_per_line;
    Object output_buffer, color_map_1, buffer, pixel, rgb, index_1, byte_1;
    Object temp, ab_loop_iter_flag_;
    SI_Long bytes_per_line_1, depth_1, left_star, right_star, index_start, y;
    SI_Long ab_loop_bind_, i, x, ab_loop_bind__1, gensymed_symbol;
    SI_Long gensymed_symbol_1, aref_arg_2, aref_new_value, red, green, blue;

    x_note_fn_call(96,164);
    if (ensure_image_data_pixels(image_data)) {
	width = ISVREF(image_data,(SI_Long)5L);
	height = ISVREF(image_data,(SI_Long)6L);
	depth = ISVREF(image_data,(SI_Long)7L);
	bytes_per_line_1 = IFIX(FIXNUM_TIMES(width,depth)) + (SI_Long)7L 
		>>  -  - (SI_Long)3L;
	color_map = ISVREF(image_data,(SI_Long)9L);
	gray_map = create_gray_map_from_color_map(color_map);
	raster_qm = ISVREF(image_data,(SI_Long)10L);
	in_color_p = EQ(printer_setup_particular(Qcolor_conversion),
		Qfull_color) ? ( 
		!TRUEP(image_data_is_gray_scale_p(image_data)) ? T : Nil) :
		 Qnil;
	flipped_one_bit_image_p = IFIX(depth) == (SI_Long)1L && 
		IFIX(ISVREF(gray_map,(SI_Long)1L)) == (SI_Long)2L ? 
		(FIXNUM_GT(FIXNUM_LE(ISVREF(gray_map,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(gray_map,(SI_Long)0L 
		+ IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gray_map,(SI_Long)2L),(SI_Long)0L),
		FIXNUM_LE(ISVREF(gray_map,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(gray_map,
		IFIX(FIXNUM_ADD1(Managed_array_index_offset))) : 
		ISVREF(ISVREF(gray_map,(SI_Long)2L),(SI_Long)1L)) ? T : 
		Nil) : Qnil;
	if (in_color_p)
	    bits_per_component = FIX((SI_Long)8L);
	else if (IFIX(depth) > (SI_Long)8L)
	    bits_per_component = FIX((SI_Long)8L);
	else
	    bits_per_component = depth;
	if (in_color_p)
	    characters_per_line = FIX(IFIX(width) * (SI_Long)6L);
	else if (IFIX(depth) < (SI_Long)8L)
	    characters_per_line = FIX(bytes_per_line_1 * (SI_Long)2L);
	else
	    characters_per_line = FIX(IFIX(width) * (SI_Long)2L);
	output_buffer = obtain_simple_text_string(characters_per_line);
	if (raster_qm) {
	    pformat(2,string_constant_98,FIX(IFIX(characters_per_line) >>  
		    -  - (SI_Long)1L));
	    postscript_emit_operator_1(string_constant_91);
	    postscript_emit_atom(left);
	    postscript_emit_atom(top);
	    postscript_emit_atom(right);
	    postscript_emit_atom(bottom);
	    postscript_emit_operator_1(string_constant_93);
	    postscript_emit_atom(x_in_window);
	    postscript_emit_atom(y_in_window);
	    postscript_emit_operator_1(string_constant_94);
	    postscript_emit_atom(x_scale);
	    postscript_emit_atom(FIX((SI_Long)4096L));
	    postscript_emit_operator_1(string_constant_99);
	    postscript_emit_atom(width);
	    postscript_emit_operator_1(string_constant_100);
	    postscript_emit_atom(y_scale);
	    postscript_emit_atom(FIX((SI_Long)4096L));
	    postscript_emit_operator_1(string_constant_99);
	    postscript_emit_atom(height);
	    postscript_emit_operator_1(string_constant_100);
	    postscript_emit_operator_1(string_constant_101);
	    postscript_emit_atom(width);
	    postscript_emit_atom(height);
	    postscript_emit_atom(bits_per_component);
	    pformat(3,string_constant_102,width,height);
	    pformat(1,string_constant_103);
	    if (in_color_p) {
		postscript_emit_operator_1(string_constant_104);
		postscript_emit_atom(FIX((SI_Long)3L));
		postscript_emit_operator_1(string_constant_105);
		depth_1 = IFIX(ISVREF(raster_qm,(SI_Long)4L));
		color_map_1 = ISVREF(raster_qm,(SI_Long)6L);
		left_star = (SI_Long)0L;
		right_star = IFIX(ISVREF(raster_qm,(SI_Long)1L));
		index_start = depth_1 == (SI_Long)24L ? (SI_Long)3L * 
			left_star : (SI_Long)0L;
		y = (SI_Long)0L;
		ab_loop_bind_ = IFIX(ISVREF(raster_qm,(SI_Long)2L));
		buffer = Nil;
	      next_loop:
		if (y >= ab_loop_bind_)
		    goto end_loop;
		buffer = FIXNUM_LE(ISVREF(ISVREF(raster_qm,(SI_Long)7L),
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(ISVREF(raster_qm,(SI_Long)7L),y + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(ISVREF(raster_qm,(SI_Long)7L),(y >>  
			-  - (SI_Long)10L) + (SI_Long)2L),y & (SI_Long)1023L);
		i = (SI_Long)0L;
		pixel = Nil;
		rgb = Nil;
		index_1 = FIX(index_start);
		x = left_star;
		ab_loop_bind__1 = right_star;
	      next_loop_1:
		if (x >= ab_loop_bind__1)
		    goto end_loop_1;
		if (! !((SI_Long)-128L <= depth_1 && depth_1 <= (SI_Long)127L))
		    switch ((char)depth_1) {
		      case 24:
			pixel = FIX(UBYTE_8_ISAREF_1(buffer,IFIX(index_1)) 
				<< (SI_Long)16L | UBYTE_8_ISAREF_1(buffer,
				IFIX(FIXNUM_ADD1(index_1))) << (SI_Long)8L 
				| UBYTE_8_ISAREF_1(buffer,IFIX(index_1) + 
				(SI_Long)2L));
			rgb = pixel;
			index_1 = FIX(IFIX(index_1) + (SI_Long)3L);
			break;
		      case 8:
			pixel = FIX(UBYTE_8_ISAREF_1(buffer,x));
			rgb = FIXNUM_LE(ISVREF(color_map_1,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(color_map_1,IFIX(FIXNUM_ADD(pixel,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(color_map_1,(IFIX(pixel) >>  
				-  - (SI_Long)10L) + (SI_Long)2L),
				IFIX(pixel) & (SI_Long)1023L);
			break;
		      case 1:
			gensymed_symbol = (SI_Long)1L;
			gensymed_symbol_1 = x & (SI_Long)7L;
			gensymed_symbol = IFIX(ash(FIX(gensymed_symbol),
				FIX(gensymed_symbol_1)));
			gensymed_symbol_1 = UBYTE_8_ISAREF_1(buffer,x >>  
				-  - (SI_Long)3L);
			pixel = (gensymed_symbol & gensymed_symbol_1) != 
				(SI_Long)0L ? FIX((SI_Long)1L) : 
				FIX((SI_Long)0L);
			rgb = FIXNUM_LE(ISVREF(color_map_1,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(color_map_1,IFIX(FIXNUM_ADD(pixel,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(color_map_1,(IFIX(pixel) >>  
				-  - (SI_Long)10L) + (SI_Long)2L),
				IFIX(pixel) & (SI_Long)1023L);
			break;
		      default:
			break;
		    }
		aref_arg_2 = i + (SI_Long)5L;
		aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
			IFIX(rgb) & (SI_Long)15L);
		UBYTE_16_ISASET_1(output_buffer,aref_arg_2,aref_new_value);
		rgb = ash(rgb,FIX((SI_Long)-4L));
		aref_arg_2 = i + (SI_Long)4L;
		aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
			IFIX(rgb) & (SI_Long)15L);
		UBYTE_16_ISASET_1(output_buffer,aref_arg_2,aref_new_value);
		rgb = ash(rgb,FIX((SI_Long)-4L));
		aref_arg_2 = i + (SI_Long)3L;
		aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
			IFIX(rgb) & (SI_Long)15L);
		UBYTE_16_ISASET_1(output_buffer,aref_arg_2,aref_new_value);
		rgb = ash(rgb,FIX((SI_Long)-4L));
		aref_arg_2 = i + (SI_Long)2L;
		aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
			IFIX(rgb) & (SI_Long)15L);
		UBYTE_16_ISASET_1(output_buffer,aref_arg_2,aref_new_value);
		rgb = ash(rgb,FIX((SI_Long)-4L));
		aref_arg_2 = i + (SI_Long)1L;
		aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
			IFIX(rgb) & (SI_Long)15L);
		UBYTE_16_ISASET_1(output_buffer,aref_arg_2,aref_new_value);
		rgb = ash(rgb,FIX((SI_Long)-4L));
		aref_arg_2 = i + (SI_Long)0L;
		aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
			IFIX(rgb) & (SI_Long)15L);
		UBYTE_16_ISASET_1(output_buffer,aref_arg_2,aref_new_value);
		i = i + (SI_Long)6L;
		x = x + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
		g2_stream_write_string(output_buffer,Printing_stream);
		pformat(1,string_constant_106);
		y = y + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	    else {
		postscript_emit_operator_1(string_constant_107);
		if ( !(FIXNUMP(depth) && FIXNUM_LE(FIX((SI_Long)-128L),
			depth) && FIXNUM_LE(depth,FIX((SI_Long)127L)))) {
		    depth_1 = IFIX(ISVREF(raster_qm,(SI_Long)4L));
		    color_map_1 = ISVREF(raster_qm,(SI_Long)6L);
		    left_star = (SI_Long)0L;
		    right_star = IFIX(ISVREF(raster_qm,(SI_Long)1L));
		    index_start = depth_1 == (SI_Long)24L ? (SI_Long)3L * 
			    left_star : (SI_Long)0L;
		    y = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(ISVREF(raster_qm,(SI_Long)2L));
		    buffer = Nil;
		  next_loop_2:
		    if (y >= ab_loop_bind_)
			goto end_loop_2;
		    buffer = FIXNUM_LE(ISVREF(ISVREF(raster_qm,
			    (SI_Long)7L),(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(ISVREF(raster_qm,(SI_Long)7L),y + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(ISVREF(raster_qm,(SI_Long)7L),(y 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L),y & 
			    (SI_Long)1023L);
		    i = (SI_Long)0L;
		    pixel = Nil;
		    rgb = Nil;
		    index_1 = FIX(index_start);
		    x = left_star;
		    ab_loop_bind__1 = right_star;
		  next_loop_3:
		    if (x >= ab_loop_bind__1)
			goto end_loop_3;
		    if (! !((SI_Long)-128L <= depth_1 && depth_1 <= 
			    (SI_Long)127L))
			switch ((char)depth_1) {
			  case 24:
			    pixel = FIX(UBYTE_8_ISAREF_1(buffer,
				    IFIX(index_1)) << (SI_Long)16L | 
				    UBYTE_8_ISAREF_1(buffer,
				    IFIX(FIXNUM_ADD1(index_1))) << 
				    (SI_Long)8L | UBYTE_8_ISAREF_1(buffer,
				    IFIX(index_1) + (SI_Long)2L));
			    rgb = pixel;
			    index_1 = FIX(IFIX(index_1) + (SI_Long)3L);
			    break;
			  case 8:
			    pixel = FIX(UBYTE_8_ISAREF_1(buffer,x));
			    rgb = FIXNUM_LE(ISVREF(color_map_1,
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(color_map_1,
				    IFIX(FIXNUM_ADD(pixel,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(color_map_1,(IFIX(pixel) 
				    >>  -  - (SI_Long)10L) + (SI_Long)2L),
				    IFIX(pixel) & (SI_Long)1023L);
			    break;
			  case 1:
			    gensymed_symbol = (SI_Long)1L;
			    gensymed_symbol_1 = x & (SI_Long)7L;
			    gensymed_symbol = 
				    IFIX(ash(FIX(gensymed_symbol),
				    FIX(gensymed_symbol_1)));
			    gensymed_symbol_1 = UBYTE_8_ISAREF_1(buffer,x 
				    >>  -  - (SI_Long)3L);
			    pixel = (gensymed_symbol & gensymed_symbol_1) 
				    != (SI_Long)0L ? FIX((SI_Long)1L) : 
				    FIX((SI_Long)0L);
			    rgb = FIXNUM_LE(ISVREF(color_map_1,
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(color_map_1,
				    IFIX(FIXNUM_ADD(pixel,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(color_map_1,(IFIX(pixel) 
				    >>  -  - (SI_Long)10L) + (SI_Long)2L),
				    IFIX(pixel) & (SI_Long)1023L);
			    break;
			  default:
			    break;
			}
		    if (IFIX(depth) == (SI_Long)8L)
			byte_1 = FIXNUM_LE(ISVREF(gray_map,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(gray_map,IFIX(FIXNUM_ADD(pixel,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(gray_map,(IFIX(pixel) >>  -  
				- (SI_Long)10L) + (SI_Long)2L),IFIX(pixel) 
				& (SI_Long)1023L);
		    else {
			gensymed_symbol = (SI_Long)255L & IFIX(rgb) >>  -  
				- (SI_Long)16L;
			red = gensymed_symbol;
			gensymed_symbol = (SI_Long)255L & IFIX(rgb) >>  -  
				- (SI_Long)8L;
			green = gensymed_symbol;
			gensymed_symbol = (SI_Long)255L & IFIX(rgb);
			blue = gensymed_symbol;
			temp = FIX(((SI_Long)30L * red + (SI_Long)59L * 
				green + (SI_Long)11L * blue) / (SI_Long)100L);
			byte_1 = temp;
		    }
		    aref_arg_2 = i + (SI_Long)1L;
		    aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
			    IFIX(byte_1) & (SI_Long)15L);
		    UBYTE_16_ISASET_1(output_buffer,aref_arg_2,aref_new_value);
		    byte_1 = ash(byte_1,FIX((SI_Long)-4L));
		    aref_arg_2 = i + (SI_Long)0L;
		    aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
			    IFIX(byte_1) & (SI_Long)15L);
		    UBYTE_16_ISASET_1(output_buffer,aref_arg_2,aref_new_value);
		    i = i + (SI_Long)2L;
		    x = x + (SI_Long)1L;
		    goto next_loop_3;
		  end_loop_3:;
		    g2_stream_write_string(output_buffer,Printing_stream);
		    pformat(1,string_constant_106);
		    y = y + (SI_Long)1L;
		    goto next_loop_2;
		  end_loop_2:;
		}
		else
		    switch (INTEGER_TO_CHAR(depth)) {
		      case 1:
		      case 2:
		      case 4:
			depth_1 = IFIX(ISVREF(raster_qm,(SI_Long)4L));
			color_map_1 = ISVREF(raster_qm,(SI_Long)6L);
			left_star = (SI_Long)0L;
			right_star = IFIX(ISVREF(raster_qm,(SI_Long)1L));
			index_start = depth_1 == (SI_Long)24L ? 
				(SI_Long)3L * left_star : (SI_Long)0L;
			y = (SI_Long)0L;
			ab_loop_bind_ = IFIX(ISVREF(raster_qm,(SI_Long)2L));
			buffer = Nil;
		      next_loop_4:
			if (y >= ab_loop_bind_)
			    goto end_loop_4;
			buffer = FIXNUM_LE(ISVREF(ISVREF(raster_qm,
				(SI_Long)7L),(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(ISVREF(raster_qm,(SI_Long)7L),y + 
				IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(ISVREF(raster_qm,
				(SI_Long)7L),(y >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),y & (SI_Long)1023L);
			ab_loop_bind__1 = bytes_per_line_1;
			x = (SI_Long)0L;
			i = (SI_Long)0L;
			byte_1 = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_5:
			if (x >= ab_loop_bind__1)
			    goto end_loop_5;
			if ( !TRUEP(ab_loop_iter_flag_))
			    i = i + (SI_Long)2L;
			byte_1 = 
				FIX(g2ext_reverse_bits_in_byte(flipped_one_bit_image_p 
				? (SI_Long)255L - UBYTE_8_ISAREF_1(buffer,
				x) : UBYTE_8_ISAREF_1(buffer,x)));
			aref_arg_2 = i + (SI_Long)1L;
			aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
				IFIX(byte_1) & (SI_Long)15L);
			UBYTE_16_ISASET_1(output_buffer,aref_arg_2,
				aref_new_value);
			byte_1 = ash(byte_1,FIX((SI_Long)-4L));
			aref_arg_2 = i + (SI_Long)0L;
			aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
				IFIX(byte_1) & (SI_Long)15L);
			UBYTE_16_ISASET_1(output_buffer,aref_arg_2,
				aref_new_value);
			ab_loop_iter_flag_ = Nil;
			x = x + (SI_Long)1L;
			goto next_loop_5;
		      end_loop_5:;
			g2_stream_write_string(output_buffer,Printing_stream);
			pformat(1,string_constant_106);
			y = y + (SI_Long)1L;
			goto next_loop_4;
		      end_loop_4:;
			break;
		      default:
			depth_1 = IFIX(ISVREF(raster_qm,(SI_Long)4L));
			color_map_1 = ISVREF(raster_qm,(SI_Long)6L);
			left_star = (SI_Long)0L;
			right_star = IFIX(ISVREF(raster_qm,(SI_Long)1L));
			index_start = depth_1 == (SI_Long)24L ? 
				(SI_Long)3L * left_star : (SI_Long)0L;
			y = (SI_Long)0L;
			ab_loop_bind_ = IFIX(ISVREF(raster_qm,(SI_Long)2L));
			buffer = Nil;
		      next_loop_6:
			if (y >= ab_loop_bind_)
			    goto end_loop_6;
			buffer = FIXNUM_LE(ISVREF(ISVREF(raster_qm,
				(SI_Long)7L),(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(ISVREF(raster_qm,(SI_Long)7L),y + 
				IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(ISVREF(raster_qm,
				(SI_Long)7L),(y >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),y & (SI_Long)1023L);
			i = (SI_Long)0L;
			pixel = Nil;
			rgb = Nil;
			index_1 = FIX(index_start);
			x = left_star;
			ab_loop_bind__1 = right_star;
		      next_loop_7:
			if (x >= ab_loop_bind__1)
			    goto end_loop_7;
			if (! !((SI_Long)-128L <= depth_1 && depth_1 <= 
				(SI_Long)127L))
			    switch ((char)depth_1) {
			      case 24:
				pixel = FIX(UBYTE_8_ISAREF_1(buffer,
					IFIX(index_1)) << (SI_Long)16L | 
					UBYTE_8_ISAREF_1(buffer,
					IFIX(FIXNUM_ADD1(index_1))) << 
					(SI_Long)8L | 
					UBYTE_8_ISAREF_1(buffer,
					IFIX(index_1) + (SI_Long)2L));
				rgb = pixel;
				index_1 = FIX(IFIX(index_1) + (SI_Long)3L);
				break;
			      case 8:
				pixel = FIX(UBYTE_8_ISAREF_1(buffer,x));
				rgb = FIXNUM_LE(ISVREF(color_map_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(color_map_1,
					IFIX(FIXNUM_ADD(pixel,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(color_map_1,
					(IFIX(pixel) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(pixel) & (SI_Long)1023L);
				break;
			      case 1:
				gensymed_symbol = (SI_Long)1L;
				gensymed_symbol_1 = x & (SI_Long)7L;
				gensymed_symbol = 
					IFIX(ash(FIX(gensymed_symbol),
					FIX(gensymed_symbol_1)));
				gensymed_symbol_1 = 
					UBYTE_8_ISAREF_1(buffer,x >>  -  - 
					(SI_Long)3L);
				pixel = (gensymed_symbol & 
					gensymed_symbol_1) != (SI_Long)0L ?
					 FIX((SI_Long)1L) : FIX((SI_Long)0L);
				rgb = FIXNUM_LE(ISVREF(color_map_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(color_map_1,
					IFIX(FIXNUM_ADD(pixel,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(color_map_1,
					(IFIX(pixel) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(pixel) & (SI_Long)1023L);
				break;
			      default:
				break;
			    }
			if (IFIX(depth) == (SI_Long)8L)
			    byte_1 = FIXNUM_LE(ISVREF(gray_map,
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(gray_map,IFIX(FIXNUM_ADD(pixel,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(gray_map,(IFIX(pixel) >> 
				     -  - (SI_Long)10L) + (SI_Long)2L),
				    IFIX(pixel) & (SI_Long)1023L);
			else {
			    gensymed_symbol = (SI_Long)255L & IFIX(rgb) >> 
				     -  - (SI_Long)16L;
			    red = gensymed_symbol;
			    gensymed_symbol = (SI_Long)255L & IFIX(rgb) >> 
				     -  - (SI_Long)8L;
			    green = gensymed_symbol;
			    gensymed_symbol = (SI_Long)255L & IFIX(rgb);
			    blue = gensymed_symbol;
			    temp = FIX(((SI_Long)30L * red + (SI_Long)59L 
				    * green + (SI_Long)11L * blue) / 
				    (SI_Long)100L);
			    byte_1 = temp;
			}
			aref_arg_2 = i + (SI_Long)1L;
			aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
				IFIX(byte_1) & (SI_Long)15L);
			UBYTE_16_ISASET_1(output_buffer,aref_arg_2,
				aref_new_value);
			byte_1 = ash(byte_1,FIX((SI_Long)-4L));
			aref_arg_2 = i + (SI_Long)0L;
			aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
				IFIX(byte_1) & (SI_Long)15L);
			UBYTE_16_ISASET_1(output_buffer,aref_arg_2,
				aref_new_value);
			i = i + (SI_Long)2L;
			x = x + (SI_Long)1L;
			goto next_loop_7;
		      end_loop_7:;
			g2_stream_write_string(output_buffer,Printing_stream);
			pformat(1,string_constant_106);
			y = y + (SI_Long)1L;
			goto next_loop_6;
		      end_loop_6:;
			break;
		    }
	    }
	    postscript_emit_operator_1(string_constant_97);
	}
	reclaim_managed_array(gray_map);
	return reclaim_simple_text_string(output_buffer);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_108;  /* "{<" */

static Object string_constant_109;  /* ">}~%" */

static Object string_constant_110;  /* "$df" */

/* HANDLER-FOR-PRINTING-PAINT-IMAGE-IN-CURRENT-SCRATCHPAD-RASTER */
Object handler_for_printing_paint_image_in_current_scratchpad_raster(image_data,
	    x_in_icon,y_in_icon,x_scale,y_scale,width,height,rotation,
	    quality,color_value)
    Object image_data, x_in_icon, y_in_icon, x_scale, y_scale, width, height;
    Object rotation, quality, color_value;
{
    Object image_width, image_height, depth, color_map, gray_map;
    Object output_buffer, raster_qm, buffer, byte_1, ab_loop_iter_flag_, mask;
    Object index_1, aref_arg_2, buffer_1, byte_vector;
    SI_Long bytes_per_line_1, ab_loop_bind_, y, ab_loop_bind__1, x, i, temp;
    SI_Long aref_new_value, gensymed_symbol, index_2, rgb, red, green, blue;
    SI_Long temp_1;

    x_note_fn_call(96,165);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	if (ensure_image_data_pixels(image_data)) {
	    image_width = ISVREF(image_data,(SI_Long)5L);
	    image_height = ISVREF(image_data,(SI_Long)6L);
	    depth = ISVREF(image_data,(SI_Long)7L);
	    bytes_per_line_1 = IFIX(image_width) * (SI_Long)1L + 
		    (SI_Long)7L >>  -  - (SI_Long)3L;
	    color_map = ISVREF(image_data,(SI_Long)9L);
	    gray_map = create_gray_map_from_color_map(color_map);
	    output_buffer = obtain_simple_text_string(FIX(bytes_per_line_1 
		    * (SI_Long)2L));
	    raster_qm = ISVREF(image_data,(SI_Long)10L);
	    if ( !TRUEP(raster_qm));
	    else if ( !(IFIX(depth) == (SI_Long)1L || IFIX(depth) == 
		    (SI_Long)8L || IFIX(depth) == (SI_Long)24L));
	    else {
		postscript_emit_atom(x_in_icon);
		postscript_emit_atom(y_in_icon);
		postscript_emit_atom(width);
		postscript_emit_atom(height);
		postscript_emit_atom(image_width);
		postscript_emit_atom(image_height);
		postscript_emit_atom(x_scale);
		postscript_emit_atom(y_scale);
		postscript_emit_scratchpad_color(color_value);
		pformat(1,string_constant_108);
		if (! !(FIXNUMP(depth) && FIXNUM_LE(FIX((SI_Long)-128L),
			depth) && FIXNUM_LE(depth,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(depth)) {
		      case 1:
			ab_loop_bind_ = IFIX(image_height);
			y = (SI_Long)0L;
			buffer = Nil;
		      next_loop:
			if (y >= ab_loop_bind_)
			    goto end_loop;
			buffer = FIXNUM_LE(ISVREF(ISVREF(raster_qm,
				(SI_Long)7L),(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(ISVREF(raster_qm,(SI_Long)7L),y + 
				IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(ISVREF(raster_qm,
				(SI_Long)7L),(y >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),y & (SI_Long)1023L);
			ab_loop_bind__1 = bytes_per_line_1;
			x = (SI_Long)0L;
			i = (SI_Long)0L;
			byte_1 = Nil;
			ab_loop_iter_flag_ = T;
		      next_loop_1:
			if (x >= ab_loop_bind__1)
			    goto end_loop_1;
			if ( !TRUEP(ab_loop_iter_flag_))
			    i = i + (SI_Long)2L;
			byte_1 = 
				FIX(g2ext_reverse_bits_in_byte(UBYTE_8_ISAREF_1(buffer,
				x)));
			temp = i + (SI_Long)1L;
			aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
				IFIX(byte_1) & (SI_Long)15L);
			UBYTE_16_ISASET_1(output_buffer,temp,aref_new_value);
			byte_1 = ash(byte_1,FIX((SI_Long)-4L));
			temp = i + (SI_Long)0L;
			aref_new_value = UBYTE_16_ISAREF_1(Write_hex_table,
				IFIX(byte_1) & (SI_Long)15L);
			UBYTE_16_ISASET_1(output_buffer,temp,aref_new_value);
			ab_loop_iter_flag_ = Nil;
			x = x + (SI_Long)1L;
			goto next_loop_1;
		      end_loop_1:;
			g2_stream_write_string(output_buffer,Printing_stream);
			pformat(1,string_constant_36);
			y = y + (SI_Long)1L;
			goto next_loop;
		      end_loop:;
			break;
		      case 8:
			ab_loop_bind_ = IFIX(image_height);
			y = (SI_Long)0L;
			mask = Nil;
			byte_1 = Nil;
			index_1 = Nil;
		      next_loop_2:
			if (y >= ab_loop_bind_)
			    goto end_loop_2;
			mask = FIX((SI_Long)1L);
			byte_1 = FIX((SI_Long)0L);
			index_1 = FIX((SI_Long)0L);
			ab_loop_bind__1 = IFIX(image_width);
			x = (SI_Long)0L;
		      next_loop_3:
			if (x >= ab_loop_bind__1)
			    goto end_loop_3;
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(FIXNUM_LE(ISVREF(ISVREF(raster_qm,
				(SI_Long)7L),(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(ISVREF(raster_qm,(SI_Long)7L),y + 
				IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(ISVREF(raster_qm,
				(SI_Long)7L),(y >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),y & (SI_Long)1023L),x);
			if (FIXNUM_LT(FIXNUM_LE(ISVREF(gray_map,
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(gray_map,gensymed_symbol + 
				IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(gray_map,(gensymed_symbol >> 
				 -  - (SI_Long)10L) + (SI_Long)2L),
				gensymed_symbol & (SI_Long)1023L),
				ISVREF(Ordered_dither_16,(x & 
				(SI_Long)15L) + ((y & (SI_Long)15L) << 
				(SI_Long)4L))))
			    byte_1 = FIXNUM_LOGIOR(byte_1,mask);
			mask = FIX(IFIX(mask) << (SI_Long)1L);
			if (IFIX(mask) >= (SI_Long)256L) {
			    byte_1 = 
				    FIX(g2ext_reverse_bits_in_byte(IFIX(byte_1)));
			    aref_arg_2 = FIXNUM_ADD1(index_1);
			    temp = UBYTE_16_ISAREF_1(Write_hex_table,
				    IFIX(byte_1) & (SI_Long)15L);
			    UBYTE_16_ISASET_1(output_buffer,
				    IFIX(aref_arg_2),temp);
			    byte_1 = ash(byte_1,FIX((SI_Long)-4L));
			    temp = IFIX(index_1) + (SI_Long)0L;
			    aref_new_value = 
				    UBYTE_16_ISAREF_1(Write_hex_table,
				    IFIX(byte_1) & (SI_Long)15L);
			    UBYTE_16_ISASET_1(output_buffer,temp,
				    aref_new_value);
			    byte_1 = FIX((SI_Long)0L);
			    mask = FIX((SI_Long)1L);
			    temp = IFIX(index_1) + (SI_Long)2L;
			    index_1 = FIX(temp);
			}
			x = x + (SI_Long)1L;
			goto next_loop_3;
		      end_loop_3:;
			if (IFIX(mask) > (SI_Long)1L) {
			    byte_1 = 
				    FIX(g2ext_reverse_bits_in_byte(IFIX(byte_1)));
			    aref_arg_2 = FIXNUM_ADD1(index_1);
			    temp = UBYTE_16_ISAREF_1(Write_hex_table,
				    IFIX(byte_1) & (SI_Long)15L);
			    UBYTE_16_ISASET_1(output_buffer,
				    IFIX(aref_arg_2),temp);
			    byte_1 = ash(byte_1,FIX((SI_Long)-4L));
			    temp = IFIX(index_1) + (SI_Long)0L;
			    aref_new_value = 
				    UBYTE_16_ISAREF_1(Write_hex_table,
				    IFIX(byte_1) & (SI_Long)15L);
			    UBYTE_16_ISASET_1(output_buffer,temp,
				    aref_new_value);
			    index_1 = FIXNUM_ADD1(index_1);
			}
			g2_stream_write_string(output_buffer,Printing_stream);
			pformat(1,string_constant_36);
			y = y + (SI_Long)1L;
			goto next_loop_2;
		      end_loop_2:;
			break;
		      case 24:
			ab_loop_bind_ = IFIX(image_height);
			y = (SI_Long)0L;
			mask = Nil;
			byte_1 = Nil;
			index_1 = Nil;
		      next_loop_4:
			if (y >= ab_loop_bind_)
			    goto end_loop_4;
			mask = FIX((SI_Long)1L);
			byte_1 = FIX((SI_Long)0L);
			index_1 = FIX((SI_Long)0L);
			ab_loop_bind__1 = IFIX(image_width);
			x = (SI_Long)0L;
		      next_loop_5:
			if (x >= ab_loop_bind__1)
			    goto end_loop_5;
			buffer_1 = FIXNUM_LE(ISVREF(ISVREF(raster_qm,
				(SI_Long)7L),(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(ISVREF(raster_qm,(SI_Long)7L),y + 
				IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(ISVREF(raster_qm,
				(SI_Long)7L),(y >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),y & (SI_Long)1023L);
			byte_vector = buffer_1;
			index_2 = (SI_Long)3L * x;
			rgb = UBYTE_8_ISAREF_1(byte_vector,index_2) << 
				(SI_Long)16L | 
				UBYTE_8_ISAREF_1(byte_vector,index_2 + 
				(SI_Long)1L) << (SI_Long)8L | 
				UBYTE_8_ISAREF_1(byte_vector,index_2 + 
				(SI_Long)2L);
			gensymed_symbol = (SI_Long)255L & rgb >>  -  - 
				(SI_Long)16L;
			red = gensymed_symbol;
			gensymed_symbol = (SI_Long)255L & rgb >>  -  - 
				(SI_Long)8L;
			green = gensymed_symbol;
			gensymed_symbol = (SI_Long)255L & rgb;
			blue = gensymed_symbol;
			temp_1 = ((SI_Long)30L * red + (SI_Long)59L * 
				green + (SI_Long)11L * blue) / (SI_Long)100L;
			if (FIXNUM_LT(FIX(temp_1),ISVREF(Ordered_dither_16,
				(x & (SI_Long)15L) + ((y & (SI_Long)15L) 
				<< (SI_Long)4L))))
			    byte_1 = FIXNUM_LOGIOR(byte_1,mask);
			mask = FIX(IFIX(mask) << (SI_Long)1L);
			if (IFIX(mask) >= (SI_Long)256L) {
			    byte_1 = 
				    FIX(g2ext_reverse_bits_in_byte(IFIX(byte_1)));
			    aref_arg_2 = FIXNUM_ADD1(index_1);
			    temp = UBYTE_16_ISAREF_1(Write_hex_table,
				    IFIX(byte_1) & (SI_Long)15L);
			    UBYTE_16_ISASET_1(output_buffer,
				    IFIX(aref_arg_2),temp);
			    byte_1 = ash(byte_1,FIX((SI_Long)-4L));
			    temp = IFIX(index_1) + (SI_Long)0L;
			    aref_new_value = 
				    UBYTE_16_ISAREF_1(Write_hex_table,
				    IFIX(byte_1) & (SI_Long)15L);
			    UBYTE_16_ISASET_1(output_buffer,temp,
				    aref_new_value);
			    byte_1 = FIX((SI_Long)0L);
			    mask = FIX((SI_Long)1L);
			    temp = IFIX(index_1) + (SI_Long)2L;
			    index_1 = FIX(temp);
			}
			x = x + (SI_Long)1L;
			goto next_loop_5;
		      end_loop_5:;
			if (IFIX(mask) > (SI_Long)1L) {
			    byte_1 = 
				    FIX(g2ext_reverse_bits_in_byte(IFIX(byte_1)));
			    aref_arg_2 = FIXNUM_ADD1(index_1);
			    temp = UBYTE_16_ISAREF_1(Write_hex_table,
				    IFIX(byte_1) & (SI_Long)15L);
			    UBYTE_16_ISASET_1(output_buffer,
				    IFIX(aref_arg_2),temp);
			    byte_1 = ash(byte_1,FIX((SI_Long)-4L));
			    temp = IFIX(index_1) + (SI_Long)0L;
			    aref_new_value = 
				    UBYTE_16_ISAREF_1(Write_hex_table,
				    IFIX(byte_1) & (SI_Long)15L);
			    UBYTE_16_ISASET_1(output_buffer,temp,
				    aref_new_value);
			    index_1 = FIXNUM_ADD1(index_1);
			}
			g2_stream_write_string(output_buffer,Printing_stream);
			pformat(1,string_constant_36);
			y = y + (SI_Long)1L;
			goto next_loop_4;
		      end_loop_4:;
			break;
		      default:
			break;
		    }
		pformat(1,string_constant_109);
		postscript_emit_operator_1(string_constant_110);
	    }
	    reclaim_managed_array(gray_map);
	    return reclaim_simple_text_string(output_buffer);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-CHANGE-IMAGE-PALETTE-OF-WINDOW */
Object handler_for_printing_change_image_palette_of_window(window,
	    palette_name,color_map_qm)
    Object window, palette_name, color_map_qm;
{
    x_note_fn_call(96,166);
    if (IFIX(Printing_pass_number) == (SI_Long)2L)
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_111;  /* "$dl" */

/* HANDLER-FOR-PRINTING-PAINT-SOLID-RECTANGLE-IN-CURRENT-WINDOW */
Object handler_for_printing_paint_solid_rectangle_in_current_window(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    color_value)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, color_value;
{
    x_note_fn_call(96,167);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_rectangle(clipped_left_edge,clipped_top_edge,
		clipped_right_edge,clipped_bottom_edge);
	postscript_emit_color_value(color_value);
	return postscript_emit_operator_1(string_constant_111);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_112;  /* "$w" */

/* HANDLER-FOR-PRINTING-ADD-SOLID-RECTANGLE-TO-CURRENT-WINDOW */
Object handler_for_printing_add_solid_rectangle_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,color_difference)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, color_difference;
{
    x_note_fn_call(96,168);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	if ( !(EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) ? 
		FIXNUM_EQ(color_difference,Transparent_color_value) : 
		IFIX(color_difference) == (SI_Long)0L || 
		FIXNUM_EQ(color_difference,Transparent_color_value))) {
	    postscript_emit_rectangle(clipped_left_edge,clipped_top_edge,
		    clipped_right_edge,clipped_bottom_edge);
	    postscript_emit_color_difference(color_difference);
	    return postscript_emit_operator_1(string_constant_112);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_113;  /* "pop" */

static Object string_constant_114;  /* "$u" */

/* HANDLER-FOR-PRINTING-ADD-FROM-ICON-RENDERING-TO-CURRENT-WINDOW */
Object handler_for_printing_add_from_icon_rendering_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,color_difference,icon_rendering,
	    left_edge_in_icon_rendering,top_edge_in_icon_rendering,
	    list_of_color_differences)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, color_difference;
    Object icon_rendering, left_edge_in_icon_rendering;
    Object top_edge_in_icon_rendering, list_of_color_differences;
{
    Object printing_pass_number;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,169);
    if (IFIX(Printing_pass_number) == (SI_Long)1L) {
	printing_pass_number = FIX((SI_Long)2L);
	PUSH_SPECIAL_WITH_SYMBOL(Printing_pass_number,Qprinting_pass_number,printing_pass_number,
		0);
	  if ( 
		      !TRUEP(lookup_postscript_icon_rendering_index(icon_rendering))) {
	      postscript_emit_icon_rendering(icon_rendering);
	      result = postscript_emit_operator_1(string_constant_113);
	  }
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	return result;
    }
    else if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	if ( !( !TRUEP(list_of_color_differences) && 
		(EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) 
		? FIXNUM_EQ(color_difference,Transparent_color_value) : 
		IFIX(color_difference) == (SI_Long)0L || 
		FIXNUM_EQ(color_difference,Transparent_color_value)))) {
	    postscript_emit_rectangle(clipped_left_edge,clipped_top_edge,
		    clipped_right_edge,clipped_bottom_edge);
	    postscript_emit_color_difference(CONSP(list_of_color_differences) 
		    ? FIRST(list_of_color_differences) : color_difference);
	    postscript_emit_icon_rendering(icon_rendering);
	    postscript_emit_point(left_edge_in_icon_rendering,
		    top_edge_in_icon_rendering);
	    postscript_emit_list_of_colors(list_of_color_differences,T);
	    return postscript_emit_operator_1(string_constant_114);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_115;  /* "$x" */

/* HANDLER-FOR-PRINTING-ADD-UPWARD-SLOPING-LINE-TO-CURRENT-WINDOW */
Object handler_for_printing_add_upward_sloping_line_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,color_difference,left_end_x,right_end_y,
	    right_end_x,left_end_y)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, color_difference;
    Object left_end_x, right_end_y, right_end_x, left_end_y;
{
    x_note_fn_call(96,170);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	if ( !(EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) ? 
		FIXNUM_EQ(color_difference,Transparent_color_value) : 
		IFIX(color_difference) == (SI_Long)0L || 
		FIXNUM_EQ(color_difference,Transparent_color_value))) {
	    postscript_emit_color_difference(color_difference);
	    postscript_emit_rectangle(left_end_x,right_end_y,right_end_x,
		    left_end_y);
	    return postscript_emit_operator_1(string_constant_115);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_116;  /* "$s" */

/* HANDLER-FOR-PRINTING-ADD-DOWNWARD-SLOPING-LINE-TO-CURRENT-WINDOW */
Object handler_for_printing_add_downward_sloping_line_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,color_difference,left_end_x,left_end_y,
	    right_end_x,right_end_y)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, color_difference;
    Object left_end_x, left_end_y, right_end_x, right_end_y;
{
    x_note_fn_call(96,171);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	if ( !(EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) ? 
		FIXNUM_EQ(color_difference,Transparent_color_value) : 
		IFIX(color_difference) == (SI_Long)0L || 
		FIXNUM_EQ(color_difference,Transparent_color_value))) {
	    postscript_emit_color_difference(color_difference);
	    postscript_emit_rectangle(left_end_x,left_end_y,right_end_x,
		    right_end_y);
	    return postscript_emit_operator_1(string_constant_116);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_117;  /* "[]" */

static Object string_constant_118;  /* "[~a ~a]" */

static Object string_constant_119;  /* "[~a ~a ~a ~a]" */

static Object string_constant_120;  /* "[~a ~a ~a ~a ~a ~a]" */

static Object string_constant_121;  /* "$y" */

/* HANDLER-FOR-PRINTING-ADD-WIDE-POLYLINE-TO-CURRENT-WINDOW */
Object handler_for_printing_add_wide_polyline_to_current_window(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    color_difference,width,style,dashes,vertices)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, color_difference, width, style, dashes;
    Object vertices;
{
    Object temp_1, dash_1, ab_loop_list_, xy;
    SI_Long temp, dot, dash;

    x_note_fn_call(96,172);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	if ( !(EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) ? 
		FIXNUM_EQ(color_difference,Transparent_color_value) : 
		IFIX(color_difference) == (SI_Long)0L || 
		FIXNUM_EQ(color_difference,Transparent_color_value))) {
	    postscript_emit_color_difference(color_difference);
	    postscript_emit_atom(width);
	    temp = IFIX(style) & (SI_Long)3840L;
	    if ( !((SI_Long)-32768L <= temp && temp <= (SI_Long)32767L))
		temp_1 = FIX((SI_Long)0L);
	    else
		switch ((short)temp) {
		  case 0:
		    temp_1 = FIX((SI_Long)1L);
		    break;
		  case 256:
		    temp_1 = FIX((SI_Long)2L);
		    break;
		  case 512:
		    temp_1 = FIX((SI_Long)0L);
		    break;
		  default:
		    temp_1 = FIX((SI_Long)0L);
		    break;
		}
	    postscript_emit_atom(temp_1);
	    temp = IFIX(style) & (SI_Long)61440L;
	    if ( !((SI_Long)-32768L <= temp && temp <= (SI_Long)32767L))
		temp_1 = FIX((SI_Long)0L);
	    else
		switch ((short)temp) {
		  case 0:
		    temp_1 = FIX((SI_Long)1L);
		    break;
		  case 4096:
		    temp_1 = FIX((SI_Long)2L);
		    break;
		  case 8192:
		    temp_1 = FIX((SI_Long)0L);
		    break;
		  default:
		    temp_1 = FIX((SI_Long)0L);
		    break;
		}
	    postscript_emit_atom(temp_1);
	    dot = IFIX(width) * (SI_Long)1L;
	    dash = IFIX(width) * (SI_Long)3L;
	    temp = IFIX(style) & (SI_Long)15L;
	    if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L))
		postscript_emit_atom(string_constant_117);
	    else
		switch ((char)temp) {
		  case 0:
		    pformat(1,string_constant_117);
		    break;
		  case 1:
		    pformat(3,string_constant_118,FIX(dash),FIX(dot));
		    break;
		  case 2:
		    pformat(3,string_constant_118,FIX(dot),FIX(dot));
		    break;
		  case 3:
		    pformat(5,string_constant_119,FIX(dash),FIX(dot),
			    FIX(dot),FIX(dot));
		    break;
		  case 4:
		    pformat(7,string_constant_120,FIX(dash),FIX(dot),
			    FIX(dot),FIX(dot),FIX(dot),FIX(dot));
		    break;
		  case 7:
		    postscript_emit_atom(string_constant_34);
		    dash_1 = Nil;
		    ab_loop_list_ = dashes;
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    dash_1 = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    postscript_emit_atom(dash_1);
		    goto next_loop;
		  end_loop:;
		    postscript_emit_atom(string_constant_38);
		    break;
		  default:
		    postscript_emit_atom(string_constant_117);
		    break;
		}
	    postscript_emit_atom(string_constant_34);
	    xy = Nil;
	    ab_loop_list_ = vertices;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    xy = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    postscript_emit_atom(xy);
	    goto next_loop_1;
	  end_loop_1:;
	    postscript_emit_atom(string_constant_38);
	    return postscript_emit_operator_1(string_constant_121);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-ADD-POLYGON-TO-CURRENT-WINDOW */
Object handler_for_printing_add_polygon_to_current_window(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    line_color_difference,line_width,fill_color_difference,
	    fill_pattern,vertices)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, line_color_difference, line_width;
    Object fill_color_difference, fill_pattern, vertices;
{
    x_note_fn_call(96,173);
    if (IFIX(Printing_pass_number) == (SI_Long)2L)
	return VALUES_1(vertices);
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-ADD-ELLIPSE-TO-CURRENT-WINDOW */
Object handler_for_printing_add_ellipse_to_current_window(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    line_color_difference,line_width,fill_color_difference,
	    fill_pattern,x1,y1_1,x2,y2)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, line_color_difference, line_width;
    Object fill_color_difference, fill_pattern, x1, y1_1, x2, y2;
{
    x_note_fn_call(96,174);
    if (IFIX(Printing_pass_number) == (SI_Long)2L)
	return VALUES_1(y2);
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-COPY-FROM-TILING-PATTERN-TO-CURRENT-WINDOW */
Object handler_for_printing_copy_from_tiling_pattern_to_current_window(left_edge,
	    top_edge,right_edge,bottom_edge,tiling_pattern)
    Object left_edge, top_edge, right_edge, bottom_edge, tiling_pattern;
{
    x_note_fn_call(96,175);
    if (IFIX(Printing_pass_number) == (SI_Long)2L)
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_122;  /* "$cp" */

static Object string_constant_123;  /* "$v" */

/* HANDLER-FOR-PRINTING-ADD-FROM-LINE-OF-TEXT-TO-CURRENT-WINDOW */
Object handler_for_printing_add_from_line_of_text_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,text_line,word_spacing,font_map,
	    color_difference,x_scale,y_scale,
	    left_edge_of_line_of_text_in_window,baseline_in_window)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, text_line, word_spacing;
    Object font_map, color_difference, x_scale, y_scale;
    Object left_edge_of_line_of_text_in_window, baseline_in_window;
{
    Object kanji_appeared_in_text;

    x_note_fn_call(96,176);
    if (EQ(Printing_pass_number,FIX((SI_Long)1L)))
	return printing_pass_1_define_for_text(font_map,text_line);
    else if (EQ(Printing_pass_number,FIX((SI_Long)2L))) {
	kanji_appeared_in_text = Nil;
	postscript_emit_rectangle(clipped_left_edge,clipped_top_edge,
		clipped_right_edge,clipped_bottom_edge);
	kanji_appeared_in_text = postscript_emit_text_string(CAR(font_map),
		text_line);
	postscript_emit_unsigned_integer(word_spacing);
	postscript_emit_font_map(font_map);
	postscript_emit_color_difference(color_difference);
	postscript_emit_atom(x_scale);
	postscript_emit_atom(FIX((SI_Long)4096L));
	postscript_emit_operator_1(string_constant_99);
	postscript_emit_atom(y_scale);
	postscript_emit_atom(FIX((SI_Long)4096L));
	postscript_emit_operator_1(string_constant_99);
	postscript_emit_atom(FIX((SI_Long)-1L));
	postscript_emit_operator_1(string_constant_100);
	postscript_emit_unsigned_integer(left_edge_of_line_of_text_in_window);
	postscript_emit_unsigned_integer(baseline_in_window);
	if (kanji_appeared_in_text)
	    return postscript_emit_operator_1(string_constant_122);
	else
	    return postscript_emit_operator_1(string_constant_123);
    }
    else
	return VALUES_1(Qnil);
}

/* HANDLER-FOR-PRINTING-BEEP-IN-WINDOW */
Object handler_for_printing_beep_in_window(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(96,177);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-MODIFY-GSI-SENSOR-DEFINITION */
Object handler_for_printing_modify_gsi_sensor_definition(corresponding_icp_object_index,
	    update_interval,value_type,reserve_1,reserve_2)
    Object corresponding_icp_object_index, update_interval, value_type;
    Object reserve_1, reserve_2;
{
    x_note_fn_call(96,178);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-LOAD-SENSOR-LIST-ELEMENT */
Object handler_for_printing_load_sensor_list_element(gsi_sensor,
	    collection_interval_qm,value_to_set_qm)
    Object gsi_sensor, collection_interval_qm, value_to_set_qm;
{
    x_note_fn_call(96,179);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-WRITE-USER-MESSAGE-STRING */
Object handler_for_printing_write_user_message_string(user_message,
	    urgency_qm,duration_qm)
    Object user_message, urgency_qm, duration_qm;
{
    x_note_fn_call(96,180);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RETURN-GSI-EXTENSION-VERSION */
Object handler_for_printing_return_gsi_extension_version(major_version_number,
	    minor_version_number)
    Object major_version_number, minor_version_number;
{
    x_note_fn_call(96,181);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RECEIVE-VALUE-FOR-PING-REQUEST */
Object handler_for_printing_receive_value_for_ping_request(gsi_interface,
	    year,month,day,hour,minute,second_1,status)
    Object gsi_interface, year, month, day, hour, minute, second_1, status;
{
    x_note_fn_call(96,182);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RECEIVE-VALUE-FOR-GSI-SENSOR */
Object handler_for_printing_receive_value_for_gsi_sensor(gsi_sensor,
	    error_code,value)
    Object gsi_sensor, error_code, value;
{
    x_note_fn_call(96,183);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-INITIALIZE-GSI-INTERFACE */
Object handler_for_printing_initialize_gsi_interface(interface_name,
	    class_name,listener_network_type,listener_host_name,
	    listener_port_name,remote_process_initialization_string)
    Object interface_name, class_name, listener_network_type;
    Object listener_host_name, listener_port_name;
    Object remote_process_initialization_string;
{
    x_note_fn_call(96,184);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RETURN-INITIALIZE-GSI-INTERFACE-STATUS */
Object handler_for_printing_return_initialize_gsi_interface_status(error_information)
    Object error_information;
{
    x_note_fn_call(96,185);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-INITIALIZE-DATA-SERVER */
Object handler_for_printing_initialize_data_server(text_string)
    Object text_string;
{
    x_note_fn_call(96,186);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SEND-DATA-VALUES-IF-ANY */
Object handler_for_printing_send_data_values_if_any(gsi_interface,year,
	    month,day,hour,minute,second_1)
    Object gsi_interface, year, month, day, hour, minute, second_1;
{
    x_note_fn_call(96,187);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-DEFINE-GSI-SENSOR */
Object handler_for_printing_define_gsi_sensor(corresponding_icp_object_index,
	    parameter1,parameter2,parameter3,parameter4,parameter5,parameter6)
    Object corresponding_icp_object_index, parameter1, parameter2, parameter3;
    Object parameter4, parameter5, parameter6;
{
    x_note_fn_call(96,188);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP */
Object handler_for_printing_receive_value_for_gsi_sensor_with_timestamp(gsi_sensor,
	    error_code,value,year,month,day,hour,minute,second_1)
    Object gsi_sensor, error_code, value, year, month, day, hour, minute;
    Object second_1;
{
    x_note_fn_call(96,189);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-DEFINE-GSI-INTERFACE */
Object handler_for_printing_define_gsi_interface(corresponding_icp_object_index)
    Object corresponding_icp_object_index;
{
    x_note_fn_call(96,190);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RECEIVE-GSI-SENSOR-VALUE-VECTOR */
Object handler_for_printing_receive_gsi_sensor_value_vector(gsi_sensor,
	    error_code,value,vector_1)
    Object gsi_sensor, error_code, value, vector_1;
{
    x_note_fn_call(96,191);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RECEIVE-TIMESTAMPED-GSI-SENSOR-VALUE-VECTOR */
Object handler_for_printing_receive_timestamped_gsi_sensor_value_vector(gsi_sensor,
	    error_code,value,year,month,day,hour,minute,second_1,
	    timestamped_vector)
    Object gsi_sensor, error_code, value, year, month, day, hour, minute;
    Object second_1, timestamped_vector;
{
    x_note_fn_call(96,192);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-INTERN */
Object handler_for_printing_intern(corresponding_icp_object_index,text_string)
    Object corresponding_icp_object_index, text_string;
{
    x_note_fn_call(96,193);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-ADD-TO-LIST-OF-SYMBOLS */
Object handler_for_printing_add_to_list_of_symbols(corresponding_icp_object_index,
	    symbol,first_element_qm)
    Object corresponding_icp_object_index, symbol, first_element_qm;
{
    x_note_fn_call(96,194);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-MAKE-TILING-PATTERN */
Object handler_for_printing_make_tiling_pattern(corresponding_icp_object_index,
	    gensym_window,tiling_pattern_rows_with_color_values)
    Object corresponding_icp_object_index, gensym_window;
    Object tiling_pattern_rows_with_color_values;
{
    x_note_fn_call(96,195);
    return VALUES_1(Nil);
}

static Object string_constant_124;  /* "$be" */

/* HANDLER-FOR-PRINTING-BEGIN-MAKING-ICON-RENDERING */
Object handler_for_printing_begin_making_icon_rendering(corresponding_icp_object_index,
	    x_scale_of_rendering,y_scale_of_rendering,
	    reflection_and_rotation_of_rendering,
	    width_of_rendering_structure,height_of_rendering_structure,
	    width_of_rendered_icon,height_of_rendered_icon,
	    number_of_rendering_structure_elements)
    Object corresponding_icp_object_index, x_scale_of_rendering;
    Object y_scale_of_rendering, reflection_and_rotation_of_rendering;
    Object width_of_rendering_structure, height_of_rendering_structure;
    Object width_of_rendered_icon, height_of_rendered_icon;
    Object number_of_rendering_structure_elements;
{
    x_note_fn_call(96,196);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_unsigned_integer(corresponding_icp_object_index);
	postscript_emit_scalling(x_scale_of_rendering,y_scale_of_rendering);
	postscript_emit_symbol(reflection_and_rotation_of_rendering);
	postscript_emit_unsigned_integer(width_of_rendering_structure);
	postscript_emit_unsigned_integer(height_of_rendering_structure);
	postscript_emit_unsigned_integer(width_of_rendered_icon);
	postscript_emit_unsigned_integer(height_of_rendered_icon);
	postscript_emit_unsigned_integer(number_of_rendering_structure_elements);
	return postscript_emit_operator_1(string_constant_124);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_125;  /* "$dz" */

/* HANDLER-FOR-PRINTING-REGION-EXTREMA-FOR-STORED-RASTER */
Object handler_for_printing_region_extrema_for_stored_raster(x_offset,
	    y_offset,x_max,y_max)
    Object x_offset, y_offset, x_max, y_max;
{
    x_note_fn_call(96,197);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_unsigned_integer(x_offset);
	postscript_emit_unsigned_integer(y_offset);
	postscript_emit_unsigned_integer(x_max);
	postscript_emit_unsigned_integer(y_max);
	return postscript_emit_operator_1(string_constant_125);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-REQUEST-TO-REFRESH-WINDOW */
Object handler_for_printing_request_to_refresh_window(gensym_window,
	    refresh_graphic_element_memory_too_qm,edges_supplied_qm,
	    left_edge_of_update_area_or_or_arbitrary_coordinate,
	    top_edge_of_update_area_or_or_arbitrary_coordinate,
	    right_edge_of_update_area_or_or_arbitrary_coordinate,
	    bottom_edge_of_update_area_or_or_arbitrary_coordinate)
    Object gensym_window, refresh_graphic_element_memory_too_qm;
    Object edges_supplied_qm;
    Object left_edge_of_update_area_or_or_arbitrary_coordinate;
    Object top_edge_of_update_area_or_or_arbitrary_coordinate;
    Object right_edge_of_update_area_or_or_arbitrary_coordinate;
    Object bottom_edge_of_update_area_or_or_arbitrary_coordinate;
{
    x_note_fn_call(96,198);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-REQUEST-TO-RESHAPE-WINDOW */
Object handler_for_printing_request_to_reshape_window(gensym_window,
	    new_left_edge,new_top_edge,new_right_edge,new_bottom_edge)
    Object gensym_window, new_left_edge, new_top_edge, new_right_edge;
    Object new_bottom_edge;
{
    x_note_fn_call(96,199);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-REQUEST-TO-RESHAPE-NATIVE-WINDOW */
Object handler_for_printing_request_to_reshape_native_window(gensym_window,
	    new_left_edge,new_top_edge,new_right_edge,new_bottom_edge)
    Object gensym_window, new_left_edge, new_top_edge, new_right_edge;
    Object new_bottom_edge;
{
    x_note_fn_call(96,200);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SHIFT-POSITION-OF-MOUSE */
Object handler_for_printing_shift_position_of_mouse(delta_x,delta_y)
    Object delta_x, delta_y;
{
    x_note_fn_call(96,201);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-REQUEST-TO-CLOSE-TELEWINDOWS-CONNECTION */
Object handler_for_printing_request_to_close_telewindows_connection(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(96,202);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-G2DS-LOAD-VARIABLE-LIST-ELEMENT */
Object handler_for_printing_g2ds_load_variable_list_element(g2ds_variable,
	    collection_interval,data_type,data_value)
    Object g2ds_variable, collection_interval, data_type, data_value;
{
    x_note_fn_call(96,203);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-G2DS-USER-MESSAGE-STRING */
Object handler_for_printing_g2ds_user_message_string(user_message,
	    urgency_qm,duration_qm)
    Object user_message, urgency_qm, duration_qm;
{
    x_note_fn_call(96,204);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-G2DS-VARIABLE-VALUE */
Object handler_for_printing_g2ds_variable_value(g2ds_variable_structure,
	    error_code,data_type,value)
    Object g2ds_variable_structure, error_code, data_type, value;
{
    x_note_fn_call(96,205);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-G2DS-DEFINE-VARIABLE */
Object handler_for_printing_g2ds_define_variable(corresponding_icp_object_index,
	    data_request_expression)
    Object corresponding_icp_object_index, data_request_expression;
{
    x_note_fn_call(96,206);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-NEW-EXTERNALLY-SIMULATED-OBJECT */
Object handler_for_printing_new_externally_simulated_object(external_simulation_object)
    Object external_simulation_object;
{
    x_note_fn_call(96,207);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-DEFINE-EXTERNAL-SIMULATION-OBJECT */
Object handler_for_printing_define_external_simulation_object(icp_object_index,
	    object_class)
    Object icp_object_index, object_class;
{
    x_note_fn_call(96,208);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SIMULATION-INITIALIZATION-VALUE */
Object handler_for_printing_simulation_initialization_value(initialization_value)
    Object initialization_value;
{
    x_note_fn_call(96,209);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-BEGIN-SIMULATION-INPUT-VECTOR-FOR-OBJECT */
Object handler_for_printing_begin_simulation_input_vector_for_object(external_simulation_object)
    Object external_simulation_object;
{
    x_note_fn_call(96,210);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-G2DS-CONFIGURE-VARIABLE */
Object handler_for_printing_g2ds_configure_variable(g2ds_variable,
	    data_request_expression)
    Object g2ds_variable, data_request_expression;
{
    x_note_fn_call(96,211);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SIMULATION-KEYWORD */
Object handler_for_printing_simulation_keyword(keyword)
    Object keyword;
{
    x_note_fn_call(96,212);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SIMULATION-INPUT-VALUE */
Object handler_for_printing_simulation_input_value(input_value)
    Object input_value;
{
    x_note_fn_call(96,213);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-G2DS-SERVER-STATUS */
Object handler_for_printing_g2ds_server_status(g2ds_server_status)
    Object g2ds_server_status;
{
    x_note_fn_call(96,214);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-BEGIN-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT */
Object handler_for_printing_begin_simulation_output_vector_for_object(external_simulation_object)
    Object external_simulation_object;
{
    x_note_fn_call(96,215);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SIMULATION-OUTPUT-VALUE */
Object handler_for_printing_simulation_output_value(output_value)
    Object output_value;
{
    x_note_fn_call(96,216);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-CONNECTION-INFO */
Object handler_for_printing_connection_info(input_end_object,
	    output_end_object,directional_qm,
	    port_name_for_input_end_object,port_name_for_output_end_object,
	    externally_simulated_connection,number_of_connections_left_in_path)
    Object input_end_object, output_end_object, directional_qm;
    Object port_name_for_input_end_object, port_name_for_output_end_object;
    Object externally_simulated_connection, number_of_connections_left_in_path;
{
    x_note_fn_call(96,217);
    return VALUES_1(Nil);
}

static Object string_constant_126;  /* "$bd" */

/* HANDLER-FOR-PRINTING-BEGIN-MAKING-GRAPH-RENDERING */
Object handler_for_printing_begin_making_graph_rendering(corresponding_icp_object_index,
	    format_of_graph_rendering_structure,x_scale_of_graph_rendering,
	    y_scale_of_graph_rendering,grid_border_width,
	    width_of_graph_rendering_structure,
	    height_of_graph_rendering_structure,width_of_rendered_graph,
	    height_of_rendered_graph)
    Object corresponding_icp_object_index, format_of_graph_rendering_structure;
    Object x_scale_of_graph_rendering, y_scale_of_graph_rendering;
    Object grid_border_width, width_of_graph_rendering_structure;
    Object height_of_graph_rendering_structure, width_of_rendered_graph;
    Object height_of_rendered_graph;
{
    x_note_fn_call(96,218);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_unsigned_integer(corresponding_icp_object_index);
	postscript_emit_symbol(format_of_graph_rendering_structure);
	postscript_emit_scalling(x_scale_of_graph_rendering,
		y_scale_of_graph_rendering);
	postscript_emit_unsigned_integer(grid_border_width);
	postscript_emit_unsigned_integer(width_of_graph_rendering_structure);
	postscript_emit_unsigned_integer(height_of_graph_rendering_structure);
	postscript_emit_unsigned_integer(width_of_rendered_graph);
	postscript_emit_unsigned_integer(height_of_rendered_graph);
	return postscript_emit_operator_1(string_constant_126);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_127;  /* "$t" */

/* HANDLER-FOR-PRINTING-ADD-FROM-GRAPH-RENDERING-TO-CURRENT-WINDOW */
Object handler_for_printing_add_from_graph_rendering_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,grid_background_color_value,
	    graph_rendering,left_edge_in_graph_rendering,
	    top_edge_in_graph_rendering,color_value,
	    color_values_for_rasters_qm)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge;
    Object grid_background_color_value, graph_rendering;
    Object left_edge_in_graph_rendering, top_edge_in_graph_rendering;
    Object color_value, color_values_for_rasters_qm;
{
    Object printing_pass_number, printing_graph_rendering_color_list_qm;
    Object adding_from_graph_rendering_p;
    Declare_special(3);
    Object result;

    x_note_fn_call(96,219);
    if (IFIX(Printing_pass_number) == (SI_Long)1L) {
	printing_pass_number = FIX((SI_Long)2L);
	printing_graph_rendering_color_list_qm = color_values_for_rasters_qm;
	adding_from_graph_rendering_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Adding_from_graph_rendering_p,Qadding_from_graph_rendering_p,adding_from_graph_rendering_p,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Printing_graph_rendering_color_list_qm,Qprinting_graph_rendering_color_list_qm,printing_graph_rendering_color_list_qm,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Printing_pass_number,Qprinting_pass_number,printing_pass_number,
		    0);
	      if ( 
		      !TRUEP(getf(Postscript_object_mapping_for_graph_renderings,
		      ISVREF(graph_rendering,(SI_Long)16L),_))) {
		  postscript_emit_graph_rendering(graph_rendering);
		  result = postscript_emit_operator_1(string_constant_113);
	      }
	      else
		  result = VALUES_1(Nil);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_rectangle(clipped_left_edge,clipped_top_edge,
		clipped_right_edge,clipped_bottom_edge);
	postscript_emit_unsigned_integer(grid_background_color_value);
	postscript_emit_graph_rendering(graph_rendering);
	postscript_emit_unsigned_integer(left_edge_in_graph_rendering);
	postscript_emit_unsigned_integer(top_edge_in_graph_rendering);
	postscript_emit_color_value(color_value);
	postscript_emit_list_of_colors(color_values_for_rasters_qm,Nil);
	return postscript_emit_operator_1(string_constant_127);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_128;  /* "$em" */

/* HANDLER-FOR-PRINTING-UPDATE-GRAPH-DATELINE */
Object handler_for_printing_update_graph_dateline(dateline,erase_dateline,
	    graph_rendering)
    Object dateline, erase_dateline, graph_rendering;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(96,220);
    PUSH_SPECIAL_WITH_SYMBOL(Erase_dateline,Qerase_dateline,erase_dateline,0);
      if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	  postscript_emit_integer(dateline);
	  postscript_emit_integer(Erase_dateline);
	  result = postscript_emit_operator_1(string_constant_128);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_129;  /* "$el" */

/* HANDLER-FOR-PRINTING-UPDATE-GRAPH-DATA-EXTREMA */
Object handler_for_printing_update_graph_data_extrema(left_edge,top_edge,
	    right_edge,bottom_edge)
    Object left_edge, top_edge, right_edge, bottom_edge;
{
    x_note_fn_call(96,221);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_rectangle(left_edge,top_edge,right_edge,bottom_edge);
	return postscript_emit_operator_1(string_constant_129);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_130;  /* "$en" */

/* HANDLER-FOR-PRINTING-UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES */
Object handler_for_printing_update_ring_raster_for_graph_given_color_values(graph_rendering,
	    number_of_rasters_needed)
    Object graph_rendering, number_of_rasters_needed;
{
    x_note_fn_call(96,222);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_graph_rendering(graph_rendering);
	postscript_emit_unsigned_integer(number_of_rasters_needed);
	return postscript_emit_operator_1(string_constant_130);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_131;  /* "$dt" */

/* HANDLER-FOR-PRINTING-PREPARE-FOR-PAINTING-GRAPH */
Object handler_for_printing_prepare_for_painting_graph(graph_rendering)
    Object graph_rendering;
{
    x_note_fn_call(96,223);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_graph_rendering(graph_rendering);
	return postscript_emit_operator_1(string_constant_131);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-CLEAR-DATA-CLIPPING-RECTANGLES */
Object handler_for_printing_clear_data_clipping_rectangles()
{
    x_note_fn_call(96,224);
    if (IFIX(Printing_pass_number) == (SI_Long)2L)
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-DELETE-ICP-OBJECT-FOR-PROCESS */
Object handler_for_printing_delete_icp_object_for_process(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(96,225);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RETURN-G2DS-VERSION */
Object handler_for_printing_return_g2ds_version(major_version_number,
	    minor_version_number)
    Object major_version_number, minor_version_number;
{
    x_note_fn_call(96,226);
    return VALUES_1(Nil);
}

static Object string_constant_132;  /* "$cy" */

/* HANDLER-FOR-PRINTING-MESSAGE-GROUP-ID */
Object handler_for_printing_message_group_id(message_group_id,
	    number_of_icp_bytes)
    Object message_group_id, number_of_icp_bytes;
{
    x_note_fn_call(96,227);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	postscript_emit_unsigned_integer(message_group_id);
	postscript_emit_unsigned_integer(number_of_icp_bytes);
	return postscript_emit_operator_1(string_constant_132);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-DEFINE-REMOTE-PROCEDURE-NAME */
Object handler_for_printing_define_remote_procedure_name(corresponding_icp_object_index,
	    remote_procedure_name_symbol)
    Object corresponding_icp_object_index, remote_procedure_name_symbol;
{
    x_note_fn_call(96,228);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-DEFINE-REMOTE-PROCEDURE-IDENTIFIER */
Object handler_for_printing_define_remote_procedure_identifier(corresponding_icp_object_index,
	    remote_procedure_identifier_tag,
	    list_of_included_return_attributes,
	    list_of_excluded_return_attributes)
    Object corresponding_icp_object_index, remote_procedure_identifier_tag;
    Object list_of_included_return_attributes;
    Object list_of_excluded_return_attributes;
{
    x_note_fn_call(96,229);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RPC-START */
Object handler_for_printing_rpc_start(remote_procedure_name,remote_values_list)
    Object remote_procedure_name, remote_values_list;
{
    x_note_fn_call(96,230);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RPC-CALL */
Object handler_for_printing_rpc_call(remote_procedure_name,
	    remote_procedure_identifier,remote_values_list)
    Object remote_procedure_name, remote_procedure_identifier;
    Object remote_values_list;
{
    x_note_fn_call(96,231);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RPC-ERROR */
Object handler_for_printing_rpc_error(error_name,error_level,
	    error_description,error_argument_list)
    Object error_name, error_level, error_description, error_argument_list;
{
    x_note_fn_call(96,232);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RPC-ERROR-TO-CALLER */
Object handler_for_printing_rpc_error_to_caller(remote_caller_index,
	    signaller_qm,error_name,error_level,error_description,
	    error_argument_list)
    Object remote_caller_index, signaller_qm, error_name, error_level;
    Object error_description, error_argument_list;
{
    x_note_fn_call(96,233);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RPC-ASYNCHRONOUS-ABORT */
Object handler_for_printing_rpc_asynchronous_abort(procedure_to_abort)
    Object procedure_to_abort;
{
    x_note_fn_call(96,234);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RPC-RETURN-VALUES */
Object handler_for_printing_rpc_return_values(calling_procedure_index,
	    return_values_list)
    Object calling_procedure_index, return_values_list;
{
    x_note_fn_call(96,235);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-RPC-ACKNOWLEDGE-ABORT */
Object handler_for_printing_rpc_acknowledge_abort(aborted_procedure_index)
    Object aborted_procedure_index;
{
    x_note_fn_call(96,236);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SPEEDUP-INPUT-OR-OUTPUT-TAGNAMES */
Object handler_for_printing_speedup_input_or_output_tagnames(input_or_output_tagnames)
    Object input_or_output_tagnames;
{
    x_note_fn_call(96,237);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SPEEDUP-TAGNAME */
Object handler_for_printing_speedup_tagname(tagname)
    Object tagname;
{
    x_note_fn_call(96,238);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-SPEEDUP-VALUE */
Object handler_for_printing_speedup_value(value)
    Object value;
{
    x_note_fn_call(96,239);
    return VALUES_1(Nil);
}

static Object string_constant_133;  /* "$cq" */

static Object string_constant_134;  /* "$dd" */

/* HANDLER-FOR-PRINTING-PAINT-FROM-LINE-OF-TEXT-TO-CURRENT-SCRATCHPAD-RASTER */
Object handler_for_printing_paint_from_line_of_text_to_current_scratchpad_raster(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    text_line,word_spacing,font_map,color_value,x_scale,y_scale,
	    left_edge_of_line_of_text_in_window,baseline_in_window)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, text_line, word_spacing, font_map, color_value;
    Object x_scale, y_scale, left_edge_of_line_of_text_in_window;
    Object baseline_in_window;
{
    Object kanji_appeared_in_text;

    x_note_fn_call(96,240);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	printing_pass_1_define_for_text(font_map,text_line);
	kanji_appeared_in_text = Nil;
	postscript_emit_rectangle(clipped_left_edge,clipped_top_edge,
		clipped_right_edge,clipped_bottom_edge);
	kanji_appeared_in_text = postscript_emit_text_string(CAR(font_map),
		text_line);
	postscript_emit_unsigned_integer(word_spacing);
	postscript_emit_font_map(font_map);
	postscript_emit_scratchpad_color(color_value);
	postscript_emit_scalling(x_scale,y_scale);
	postscript_emit_unsigned_integer(left_edge_of_line_of_text_in_window);
	postscript_emit_unsigned_integer(baseline_in_window);
	if (kanji_appeared_in_text)
	    return postscript_emit_operator_1(string_constant_133);
	else
	    return postscript_emit_operator_1(string_constant_134);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-ORIENT-AND-PAINT-LINE-OF-TEXT-TO-CURRENT-SCRATCHPAD-RASTER */
Object handler_for_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,width,
	    height,text_line,text_orientation,icon_orientation,
	    word_spacing,font_map,color_value,x_scale,y_scale,
	    left_edge_of_line_of_text_in_window,baseline_in_window)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, width, height, text_line, text_orientation;
    Object icon_orientation, word_spacing, font_map, color_value, x_scale;
    Object y_scale, left_edge_of_line_of_text_in_window, baseline_in_window;
{
    Object kanji_appeared_in_text;

    x_note_fn_call(96,241);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	printing_pass_1_define_for_text(font_map,text_line);
	kanji_appeared_in_text = Nil;
	postscript_emit_rectangle(clipped_left_edge,clipped_top_edge,
		clipped_right_edge,clipped_bottom_edge);
	kanji_appeared_in_text = postscript_emit_text_string(CAR(font_map),
		text_line);
	postscript_emit_unsigned_integer(word_spacing);
	postscript_emit_font_map(font_map);
	postscript_emit_scratchpad_color(color_value);
	postscript_emit_scalling(x_scale,y_scale);
	postscript_emit_unsigned_integer(left_edge_of_line_of_text_in_window);
	postscript_emit_unsigned_integer(baseline_in_window);
	if (kanji_appeared_in_text)
	    return postscript_emit_operator_1(string_constant_133);
	else
	    return postscript_emit_operator_1(string_constant_134);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-REMOTE-EVAL */
Object handler_for_printing_remote_eval(s_expression_for_remote_eval)
    Object s_expression_for_remote_eval;
{
    x_note_fn_call(96,242);
    return VALUES_1(Nil);
}

/* HANDLER-FOR-PRINTING-CONNECTION-SHUTDOWN-IMMINENT */
Object handler_for_printing_connection_shutdown_imminent(time_until_shutdown)
    Object time_until_shutdown;
{
    x_note_fn_call(96,243);
    return VALUES_1(Nil);
}

/* SEMANTIC-CHECK-FILE-TEMPLATE */
Object semantic_check_file_template(file_template)
    Object file_template;
{
    Object number_of_star, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, temp, schar_arg_2, schar_new_value, thing_1;
    Object example_instance_as_text, example_instance, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_, thing;
    Declare_special(5);

    x_note_fn_call(96,244);
    number_of_star = FIX((SI_Long)0L);
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
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(lengthw(file_template));
	      c = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      c = FIX(UBYTE_16_ISAREF_1(file_template,i));
	      if ((SI_Long)42L == IFIX(c)) {
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = (SI_Long)49L;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = (SI_Long)49L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  number_of_star = add1(number_of_star);
	      }
	      else if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing_1 = c;
		  twrite_wide_character(CHARACTERP(thing_1) ? 
			  CHAR_CODE(thing_1) : thing_1);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing_1 = c;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
			  CHAR_CODE(thing_1) : thing_1);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      example_instance_as_text = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    example_instance = 
	    convert_text_string_to_ascii_filename_as_much_as_possible(example_instance_as_text);
    temp_1 = (SI_Long)0L <= IFIX(number_of_star) && IFIX(number_of_star) 
	    <= (SI_Long)1L ? valid_pathname_p(example_instance) : Qnil;
    reclaim_text_string(example_instance_as_text);
    reclaim_text_string(example_instance);
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(File_template_instance_counter, Qfile_template_instance_counter);

static Object list_constant_35;    /* # */

static Object Qstring_equalw;      /* string-equalw */

/* NORMALIZE-PRINTING-PATHNAME-TYPE */
Object normalize_printing_pathname_type(pathname_1,format_1)
    Object pathname_1, format_1;
{
    Object gp, old_type, canonical_type, new_type, temp;

    x_note_fn_call(96,245);
    gp = gensym_pathname(pathname_1);
    old_type = ISVREF(gp,(SI_Long)5L);
    canonical_type = filetype_for_print_format(format_1);
    new_type = old_type && member(4,old_type,list_constant_35,Ktest,
	    SYMBOL_FUNCTION(Qstring_equalw)) ? canonical_type : old_type;
    temp = gensym_make_pathname_with_copied_components(ISVREF(gp,
	    (SI_Long)1L),ISVREF(gp,(SI_Long)2L),ISVREF(gp,(SI_Long)3L),
	    ISVREF(gp,(SI_Long)4L),new_type,Nil,Nil);
    reclaim_gensym_pathname(gp);
    return VALUES_1(temp);
}

static Object Qinstantiate_file_template_for_printing;  /* instantiate-file-template-for-printing */

/* INSTANTIATE-FILE-TEMPLATE */
Object instantiate_file_template(file_template,format_1)
    Object file_template, format_1;
{
    Object candidate_filename_as_text, candidate_filename, pathname_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, temp, thing, schar_arg_2, schar_new_value, temp_1;
    SI_Long i, bv16_length, aref_arg_2, aref_new_value, length_1, i_1;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(96,246);
    i = (SI_Long)0L;
    candidate_filename_as_text = Nil;
    candidate_filename = Nil;
    pathname_qm = Nil;
  next_loop:
    if (i > (SI_Long)10L)
	goto end_loop;
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
	      i_1 = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(text_string_length(file_template));
	      c = Nil;
	    next_loop_1:
	      if (i_1 >= ab_loop_bind_)
		  goto end_loop_1;
	      c = FIX(UBYTE_16_ISAREF_1(file_template,i_1));
	      if (EQ(FIX((SI_Long)42L),c)) {
		  temp = add1(File_template_instance_counter);
		  File_template_instance_counter = temp;
		  tformat(2,string_constant_79,File_template_instance_counter);
	      }
	      else if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = c;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = c;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      i_1 = i_1 + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:;
	      candidate_filename_as_text = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp_1 = export_text_string(2,candidate_filename_as_text,
	    Qinstantiate_file_template_for_printing);
    reclaim_text_string(candidate_filename_as_text);
    candidate_filename = temp_1;
    pathname_qm = valid_pathname_p(candidate_filename) ? 
	    normalize_printing_pathname_type(candidate_filename,format_1) :
	     Qnil;
    reclaim_text_string(candidate_filename);
    if (pathname_qm &&  !TRUEP(gensym_probe_file(pathname_qm))) {
	temp_1 = gensym_namestring_as_text_string(1,pathname_qm);
	reclaim_gensym_pathname(pathname_qm);
	return VALUES_1(temp_1);
    }
    else if (pathname_qm)
	reclaim_gensym_pathname(pathname_qm);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_135;  /* "print-*" */

static Object string_constant_136;  /* "ps" */

static Object array_constant_6;    /* # */

/* GET-HOST-PRINTING-PARTICULARS */
Object get_host_printing_particulars()
{
    Object spooled_filename_template_pathname, spooled_filename_template, temp;

    x_note_fn_call(96,247);
    spooled_filename_template_pathname = 
	    gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    string_constant_135,string_constant_136,Knewest,
	    Process_specific_system_pathname);
    spooled_filename_template = gensym_namestring_as_text_string(1,
	    spooled_filename_template_pathname);
    reclaim_gensym_pathname(spooled_filename_template_pathname);
    temp = copy_constant_wide_string_given_length(array_constant_6,
	    FIX((SI_Long)7L));
    return VALUES_3(spooled_filename_template,Nil,temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Platform_independent_print_spool_command_file_name, Qplatform_independent_print_spool_command_file_name);

/* SPOOL-FILE-TO-PRINTER-FOR-THIS-PLATFORM */
Object spool_file_to_printer_for_this_platform(pathname_of_actual_spooled_file)
    Object pathname_of_actual_spooled_file;
{
    Object namestring_1;

    x_note_fn_call(96,248);
    namestring_1 = gensym_namestring_as_text_string(1,
	    pathname_of_actual_spooled_file);
    return reclaim_text_string(namestring_1);
}

static Object Qprinter_file_template_is_misformed;  /* printer-file-template-is-misformed */

static Object Qprinter_g2_can_not_spool_output_on_this_platform;  /* printer-g2-can-not-spool-output-on-this-platform */

/* SEMANTIC-CHECK-SPOOLING-PARAMETERS */
Object semantic_check_spooling_parameters()
{
    Object printer_identification, spool_file_to_printer;
    Object spooled_filename_template;
    char we_really_have_a_printer_identification_p;

    x_note_fn_call(96,249);
    printer_identification = printer_setup_particular(Qprinter_identification);
    spool_file_to_printer = printer_setup_particular(Qspool_file_to_printer);
    we_really_have_a_printer_identification_p =  
	    !TRUEP(string_equalw(array_constant_6,printer_identification));
    spooled_filename_template = 
	    printer_setup_particular(Qspooled_filename_template);
    if ( !TRUEP(semantic_check_file_template(spooled_filename_template)))
	add_frame_note(5,Qprinter_file_template_is_misformed,Printer_setup,
		T,T,Nil);
    if (spool_file_to_printer && we_really_have_a_printer_identification_p)
	return add_frame_note(5,
		Qprinter_g2_can_not_spool_output_on_this_platform,
		Printer_setup,T,T,Nil);
    else
	return VALUES_1(Nil);
}

Object Postscript_enable_multipage_legends = UNBOUND;

static Object string_constant_137;  /* "%!PS-Adobe-3.0~a" */

static Object string_constant_138;  /* " EPSF-3.0" */

static Object string_constant_139;  /* "~%%%Pages: ~d" */

static Object string_constant_140;  /* "~%%%Title: Workspace ~a" */

static Object string_constant_141;  /* "~%%%Creator: G2 ~a" */

static Object string_constant_142;  /* "~%%%For: ~a" */

static Object string_constant_143;  /* "~%%%CreationDate: ~a" */

static Object string_constant_144;  /* "~%%%Orientation: ~(~a~)" */

static Object string_constant_145;  /* "~%%%DocumentPaperSizes: ~(~a~)" */

static Object Qlandscape;          /* landscape */

static Object string_constant_146;  /* "~%%%BoundingBox: ~a ~a ~a ~a" */

static Object string_constant_147;  /* "~%%%EndComments" */

/* EMIT-POSTSCRIPT-JOB-HEADER */
Object emit_postscript_job_header(workspace,paper_size,npages,eps_qm,
	    workspace_width,workspace_height,
	    postscript_units_per_workspace_unit_mf,paper_orientation,
	    paper_width_mf,paper_height_mf,left_margin_mf,top_margin_mf,
	    right_margin_mf,bottom_margin_mf,paper_left_margin_mf,
	    paper_top_margin_mf,paper_right_margin_mf,paper_bottom_margin_mf)
    Object workspace, paper_size, npages, eps_qm, workspace_width;
    Object workspace_height, postscript_units_per_workspace_unit_mf;
    Object paper_orientation, paper_width_mf, paper_height_mf, left_margin_mf;
    Object top_margin_mf, right_margin_mf, bottom_margin_mf;
    Object paper_left_margin_mf, paper_top_margin_mf, paper_right_margin_mf;
    Object paper_bottom_margin_mf;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object version, seconds, minutes, hours, day, month, year, date;
    Object bottom_margin_mf_old_value, temp, xmin, ymin, xmax, ymax, temp_2;
    Object temp_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    double gensymed_symbol, gensymed_symbol_1, left_margin, top_margin;
    double right_margin, bottom_margin, paper_height, paper_width, scale;
    double temp_1, image_width, image_height;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(96,250);
    pformat(2,string_constant_137,eps_qm ? string_constant_138 : 
	    string_constant_8);
    pformat(2,string_constant_139,npages);
    pformat(2,string_constant_140,
	    get_or_make_up_designation_for_block(workspace));
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
	      twrite_system_version(1,Current_system_version);
	      version = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    pformat(2,string_constant_141,version);
    reclaim_text_string(version);
    pformat(2,string_constant_142,get_current_user_name());
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
	      result = get_decoded_real_time();
	      MVS_6(result,seconds,minutes,hours,day,month,year);
	      print_decoded_time(seconds,minutes,hours,day,month,year);
	      date = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    pformat(2,string_constant_143,date);
    reclaim_text_string(date);
    pformat(2,string_constant_144,paper_orientation);
    if ( !TRUEP(eps_qm))
	pformat(2,string_constant_145,paper_size);
    if (eps_qm) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (EQ(paper_orientation,Qlandscape)) {
		bottom_margin_mf_old_value = bottom_margin_mf;
		bottom_margin_mf = right_margin_mf;
		right_margin_mf = top_margin_mf;
		top_margin_mf = left_margin_mf;
		temp = bottom_margin_mf_old_value;
		left_margin_mf = temp;
	    }
	    gensymed_symbol = DFLOAT_ISAREF_1(left_margin_mf,(SI_Long)0L);
	    gensymed_symbol_1 = DFLOAT_ISAREF_1(paper_left_margin_mf,
		    (SI_Long)0L);
	    left_margin = MAX(gensymed_symbol,gensymed_symbol_1);
	    gensymed_symbol = DFLOAT_ISAREF_1(top_margin_mf,(SI_Long)0L);
	    gensymed_symbol_1 = DFLOAT_ISAREF_1(paper_top_margin_mf,
		    (SI_Long)0L);
	    top_margin = MAX(gensymed_symbol,gensymed_symbol_1);
	    gensymed_symbol = DFLOAT_ISAREF_1(right_margin_mf,(SI_Long)0L);
	    gensymed_symbol_1 = DFLOAT_ISAREF_1(paper_right_margin_mf,
		    (SI_Long)0L);
	    right_margin = MAX(gensymed_symbol,gensymed_symbol_1);
	    gensymed_symbol = DFLOAT_ISAREF_1(bottom_margin_mf,(SI_Long)0L);
	    gensymed_symbol_1 = DFLOAT_ISAREF_1(paper_bottom_margin_mf,
		    (SI_Long)0L);
	    bottom_margin = MAX(gensymed_symbol,gensymed_symbol_1);
	    paper_height = DFLOAT_ISAREF_1(paper_height_mf,(SI_Long)0L);
	    paper_width = DFLOAT_ISAREF_1(paper_width_mf,(SI_Long)0L);
	    scale = DFLOAT_ISAREF_1(postscript_units_per_workspace_unit_mf,
		    (SI_Long)0L);
	    temp = lfloat(workspace_width,float_constant);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    image_width = scale * temp_1;
	    temp = lfloat(workspace_height,float_constant);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    image_height = scale * temp_1;
	    if (IFIX(npages) > (SI_Long)1L)
		result = VALUES_4(DOUBLE_TO_DOUBLE_FLOAT(left_margin),
			DOUBLE_TO_DOUBLE_FLOAT(bottom_margin),
			DOUBLE_TO_DOUBLE_FLOAT(paper_width - right_margin),
			DOUBLE_TO_DOUBLE_FLOAT(paper_height - top_margin));
	    else if (EQ(paper_orientation,Qportrait))
		result = VALUES_4(DOUBLE_TO_DOUBLE_FLOAT(left_margin),
			DOUBLE_TO_DOUBLE_FLOAT(paper_height - top_margin - 
			image_height),DOUBLE_TO_DOUBLE_FLOAT(left_margin + 
			image_width),DOUBLE_TO_DOUBLE_FLOAT(paper_height - 
			top_margin));
	    else
		result = VALUES_4(DOUBLE_TO_DOUBLE_FLOAT(paper_width - 
			right_margin - image_width),
			DOUBLE_TO_DOUBLE_FLOAT(paper_height - top_margin - 
			image_height),DOUBLE_TO_DOUBLE_FLOAT(paper_width - 
			right_margin),DOUBLE_TO_DOUBLE_FLOAT(paper_height 
			- top_margin));
	    MVS_4(result,xmin,ymin,xmax,ymax);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(xmin);
	    temp = LONG_TO_FIXNUM(inline_floor_1(temp_1));
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(ymin);
	    temp_2 = LONG_TO_FIXNUM(inline_floor_1(temp_1));
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(xmax);
	    temp_3 = LONG_TO_FIXNUM(inline_ceiling_1(temp_1));
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(ymax);
	    pformat(5,string_constant_146,temp,temp_2,temp_3,
		    LONG_TO_FIXNUM(inline_ceiling_1(temp_1)));
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    return pformat(1,string_constant_147);
}

static Object string_constant_148;  /* "~%% Define paper size.~%" */

static Object string_constant_149;  /* "$bt" */

static Object string_constant_150;  /* "$cb" */

static Object string_constant_151;  /* "~%%%EndSetup" */

/* EMIT-POSTSCRIPT-PAGE-LAYOUT */
Object emit_postscript_page_layout(paper_size_name,
	    postscript_units_per_workspace_unit_mf,paper_orientation,
	    actual_paper_width_mf,actual_paper_height_mf,left_margin_mf,
	    top_margin_mf,right_margin_mf,bottom_margin_mf,
	    paper_left_margin_mf,paper_top_margin_mf,paper_right_margin_mf,
	    paper_bottom_margin_mf)
    Object paper_size_name, postscript_units_per_workspace_unit_mf;
    Object paper_orientation, actual_paper_width_mf, actual_paper_height_mf;
    Object left_margin_mf, top_margin_mf, right_margin_mf, bottom_margin_mf;
    Object paper_left_margin_mf, paper_top_margin_mf, paper_right_margin_mf;
    Object paper_bottom_margin_mf;
{
    x_note_fn_call(96,251);
    pformat(1,string_constant_148);
    postscript_emit_symbol(paper_size_name);
    postscript_emit_symbol(paper_orientation);
    postscript_emit_managed_float(actual_paper_width_mf);
    postscript_emit_managed_float(actual_paper_height_mf);
    postscript_emit_managed_float(paper_left_margin_mf);
    postscript_emit_managed_float(paper_top_margin_mf);
    postscript_emit_managed_float(paper_right_margin_mf);
    postscript_emit_managed_float(paper_bottom_margin_mf);
    postscript_emit_operator_1(string_constant_149);
    postscript_emit_managed_float(postscript_units_per_workspace_unit_mf);
    postscript_emit_managed_float(left_margin_mf);
    postscript_emit_managed_float(top_margin_mf);
    postscript_emit_managed_float(right_margin_mf);
    postscript_emit_managed_float(bottom_margin_mf);
    postscript_emit_symbol(printer_setup_particular(Qcolor_conversion));
    postscript_emit_operator_1(string_constant_150);
    return pformat(1,string_constant_151);
}

static Object string_constant_152;  /* "~%~%%%Page: ~D ~D~%" */

static Object string_constant_153;  /* "set-up-page" */

static Object string_constant_154;  /* " ~d ~d ~d draw-multipage-legend~%" */

static Object string_constant_155;  /* "$ee" */

/* POSTSCRIPT-START-PAGE */
Object postscript_start_page(page_number,nrows,ncolumns,x_tile_offset,
	    y_tile_offset,x_tile_step,y_tile_step,multipage_legends_p,
	    blank_page_p)
    Object page_number, nrows, ncolumns, x_tile_offset, y_tile_offset;
    Object x_tile_step, y_tile_step, multipage_legends_p, blank_page_p;
{
    x_note_fn_call(96,252);
    pformat(3,string_constant_152,page_number,page_number);
    postscript_emit_operator_1(string_constant_153);
    if (multipage_legends_p && ( !TRUEP(ISVREF(Printer_setup,
	    (SI_Long)27L)) ||  !TRUEP(blank_page_p)))
	pformat(4,string_constant_154,nrows,ncolumns,page_number);
    postscript_emit_unsigned_integer(x_tile_offset);
    postscript_emit_unsigned_integer(y_tile_offset);
    postscript_emit_unsigned_integer(x_tile_step);
    postscript_emit_unsigned_integer(y_tile_step);
    return postscript_emit_operator_1(string_constant_155);
}

static Object string_constant_156;  /* "~%end~%" */

static Object string_constant_157;  /* "~%~%%%Trailer" */

static Object string_constant_158;  /* "~%~%%%Pages: ~D" */

static Object string_constant_159;  /* "~%~%%%EOF" */

/* POSTSCRIPT-END-DOCUMENT */
Object postscript_end_document(last_page_number)
    Object last_page_number;
{
    x_note_fn_call(96,253);
    pformat(1,string_constant_156);
    pformat(1,string_constant_157);
    pformat(2,string_constant_158,FIXNUM_SUB1(last_page_number));
    pformat(1,string_constant_159);
    return pformat(1,string_constant_106);
}

/* POSTSCRIPT-REMOVE-MARGINS-FROM-DIMENSION */
Object postscript_remove_margins_from_dimension(width,margin1,margin2)
    Object width, margin1, margin2;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value;

    x_note_fn_call(96,254);
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
    aref_new_value = DFLOAT_ISAREF_1(width,(SI_Long)0L) - 
	    DFLOAT_ISAREF_1(margin1,(SI_Long)0L) - DFLOAT_ISAREF_1(margin2,
	    (SI_Long)0L);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* POSTSCRIPT-COMPUTE-SCALING-TO-FIT */
Object postscript_compute_scaling_to_fit(top,bottom,left,right,
	    page_width_mf,page_height_mf)
    Object top, bottom, left, right, page_width_mf, page_height_mf;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    SI_Long fudge;
    double workspace_height_e, workspace_width_e, gensymed_symbol;
    double gensymed_symbol_1, aref_new_value;

    x_note_fn_call(96,255);
    fudge = Native_printer_information ? (SI_Long)0L : (SI_Long)-15L;
    workspace_height_e = (double)(IFIX(FIXNUM_MINUS(bottom,top)) - fudge);
    workspace_width_e = (double)(IFIX(FIXNUM_MINUS(right,left)) - fudge);
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
    gensymed_symbol = DFLOAT_ISAREF_1(page_width_mf,(SI_Long)0L) / 
	    workspace_width_e;
    gensymed_symbol_1 = DFLOAT_ISAREF_1(page_height_mf,(SI_Long)0L) / 
	    workspace_height_e;
    aref_new_value = MIN(gensymed_symbol,gensymed_symbol_1);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* POSTSCRIPT-COMPUTE-PAGE-COUNT */
Object postscript_compute_page_count(scale_mf,page_width_mf,page_height_mf,
	    workspace_width,workspace_height,window_frame_width)
    Object scale_mf, page_width_mf, page_height_mf, workspace_width;
    Object workspace_height, window_frame_width;
{
    Object x_tile_step, y_tile_step, initial_tile_offset, ncolumns, nrows;

    x_note_fn_call(96,256);
    x_tile_step = 
	    ltruncate(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(page_width_mf,
	    (SI_Long)0L)),DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(scale_mf,
	    (SI_Long)0L)));
    y_tile_step = 
	    ltruncate(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(page_height_mf,
	    (SI_Long)0L)),DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(scale_mf,
	    (SI_Long)0L)));
    initial_tile_offset = FIXNUM_NEGATE(window_frame_width);
    ncolumns = IFIX(x_tile_step) != (SI_Long)0L ? 
	    ceiling(minus(workspace_width,initial_tile_offset),
	    x_tile_step) : FIX((SI_Long)0L);
    nrows = IFIX(y_tile_step) != (SI_Long)0L ? 
	    ceiling(minus(workspace_height,initial_tile_offset),
	    y_tile_step) : FIX((SI_Long)0L);
    return VALUES_1(FIXNUM_TIMES(nrows,ncolumns));
}

static Object Qscale_to_fit_single_page;  /* scale-to-fit-single-page */

/* POSTSCRIPT-COMPUTE-WORKSPACE-SCALING */
Object postscript_compute_workspace_scaling(top,bottom,left,right,
	    page_width_mf,page_height_mf,workspace_width,workspace_height,
	    window_frame_width)
    Object top, bottom, left, right, page_width_mf, page_height_mf;
    Object workspace_width, workspace_height, window_frame_width;
{
    Object temp, scale_mf;

    x_note_fn_call(96,257);
    temp = printer_workspace_scaling();
    scale_mf = EQ(temp,Qscale_to_fit_single_page) ? 
	    postscript_compute_scaling_to_fit(top,bottom,left,right,
	    page_width_mf,page_height_mf) : 
	    postscript_convert_linear_distance_to_postscript_units_mf(2,
	    printer_workspace_scaling(),T);
    if ( !TRUEP(generate_eps_p()))
	return VALUES_1(scale_mf);
    else if ((SI_Long)1L == IFIX(postscript_compute_page_count(scale_mf,
	    page_width_mf,page_height_mf,workspace_width,workspace_height,
	    window_frame_width)))
	return VALUES_1(scale_mf);
    else {
	reclaim_managed_simple_float_array_of_length_1(scale_mf);
	return postscript_compute_scaling_to_fit(top,bottom,left,right,
		page_width_mf,page_height_mf);
    }
}

/* SUPPRESS-PRINTING-BORDER-P */
Object suppress_printing_border_p(image_plane)
    Object image_plane;
{
    x_note_fn_call(96,258);
    if (ISVREF(Printer_setup,(SI_Long)27L))
	return image_plane_has_default_frame_p(image_plane);
    else
	return VALUES_1(Nil);
}

static Object Qnative;             /* native */

/* START-DOCUMENT */
Object start_document(workspace,left,top,right,bottom)
    Object workspace, left, top, right, bottom;
{
    x_note_fn_call(96,259);
    if (EQ(Printing_format,Qbitmap))
	return VALUES_1(Nil);
    else if (EQ(Printing_format,Qnative))
	return VALUES_1(Nil);
    else if (EQ(Printing_format,Qpostscript))
	return VALUES_1(Nil);
    else
	return VALUES_1(Qnil);
}

/* START-PAGE */
Object start_page(page_number,nrows,ncolumns,left_margin_mf,top_margin_mf,
	    right_margin_mf,bottom_margin_mf,paper_left_margin_mf,
	    paper_top_margin_mf,paper_right_margin_mf,
	    paper_bottom_margin_mf,postscript_units_per_workspace_unit_mf,
	    x_tile_offset,y_tile_offset,x_tile_step,y_tile_step,
	    multipage_legends_p,blank_page_p)
    Object page_number, nrows, ncolumns, left_margin_mf, top_margin_mf;
    Object right_margin_mf, bottom_margin_mf, paper_left_margin_mf;
    Object paper_top_margin_mf, paper_right_margin_mf, paper_bottom_margin_mf;
    Object postscript_units_per_workspace_unit_mf, x_tile_offset;
    Object y_tile_offset, x_tile_step, y_tile_step, multipage_legends_p;
    Object blank_page_p;
{
    x_note_fn_call(96,260);
    if (EQ(Printing_format,Qbitmap))
	return VALUES_1(Nil);
    else if (EQ(Printing_format,Qnative))
	return native_start_page(page_number,nrows,ncolumns,left_margin_mf,
		top_margin_mf,right_margin_mf,bottom_margin_mf,
		paper_left_margin_mf,paper_top_margin_mf,
		paper_right_margin_mf,paper_bottom_margin_mf,
		postscript_units_per_workspace_unit_mf,multipage_legends_p);
    else if (EQ(Printing_format,Qpostscript))
	return postscript_start_page(page_number,nrows,ncolumns,
		x_tile_offset,y_tile_offset,x_tile_step,y_tile_step,
		multipage_legends_p,blank_page_p);
    else
	return VALUES_1(Qnil);
}

static Object string_constant_160;  /* "showpage~%" */

/* END-PAGE */
Object end_page()
{
    x_note_fn_call(96,261);
    if (EQ(Printing_format,Qbitmap))
	return VALUES_1(Nil);
    else if (EQ(Printing_format,Qnative))
	return native_printing_end_page(Output_window_for_printing_qm);
    else if (EQ(Printing_format,Qpostscript))
	return pformat(1,string_constant_160);
    else
	return VALUES_1(Qnil);
}

/* END-DOCUMENT */
Object end_document(last_page_number)
    Object last_page_number;
{
    Object temp_4;
    SI_Long temp, temp_1, temp_2, temp_3;

    x_note_fn_call(96,262);
    if (EQ(Printing_format,Qbitmap)) {
	if (Bitmap_for_printing_qm) {
	    temp = IFIX(ISVREF(Printing_stream,(SI_Long)1L));
	    temp_1 = IFIX(ISVREF(Bitmap_for_printing_qm,(SI_Long)4L));
	    temp_2 = IFIX(ISVREF(Bitmap_for_printing_qm,(SI_Long)1L));
	    temp_3 = IFIX(ISVREF(Bitmap_for_printing_qm,(SI_Long)2L));
	    temp_4 = printer_setup_particular(Qquality);
	    if (temp_4);
	    else
		temp_4 = FIX((SI_Long)-1L);
	    g2ext_compress_image(temp,temp_1,temp_2,temp_3,IFIX(temp_4));
	    return reclaim_pixmap(Bitmap_for_printing_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(Printing_format,Qnative))
	return native_printing_end_doc(Output_window_for_printing_qm);
    else if (EQ(Printing_format,Qpostscript))
	return postscript_end_document(last_page_number);
    else
	return VALUES_1(Qnil);
}

static Object float_constant_6;    /* 7.2 */

static Object float_constant_7;    /* 720.0 */

/* NATIVE-START-PAGE */
Object native_start_page(page_number,nrows,ncolumns,left_margin_mf,
	    top_margin_mf,right_margin_mf,bottom_margin_mf,
	    paper_left_margin_mf,paper_top_margin_mf,paper_right_margin_mf,
	    paper_bottom_margin_mf,postscript_units_per_workspace_unit_mf,
	    multipage_legends_p)
    Object page_number, nrows, ncolumns, left_margin_mf, top_margin_mf;
    Object right_margin_mf, bottom_margin_mf, paper_left_margin_mf;
    Object paper_top_margin_mf, paper_right_margin_mf, paper_bottom_margin_mf;
    Object postscript_units_per_workspace_unit_mf, multipage_legends_p;
{
    Object scale, left_margin, top_margin, right_margin, bottom_margin;
    double gensymed_symbol, gensymed_symbol_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(96,263);
    scale = Nil;
    left_margin = Nil;
    top_margin = Nil;
    right_margin = Nil;
    bottom_margin = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = DFLOAT_ISAREF_1(left_margin_mf,(SI_Long)0L);
	gensymed_symbol_1 = DFLOAT_ISAREF_1(paper_left_margin_mf,(SI_Long)0L);
	left_margin = l_round(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,
		gensymed_symbol_1)),float_constant_6);
	gensymed_symbol = DFLOAT_ISAREF_1(top_margin_mf,(SI_Long)0L);
	gensymed_symbol_1 = DFLOAT_ISAREF_1(paper_top_margin_mf,(SI_Long)0L);
	top_margin = l_round(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,
		gensymed_symbol_1)),float_constant_6);
	gensymed_symbol = DFLOAT_ISAREF_1(right_margin_mf,(SI_Long)0L);
	gensymed_symbol_1 = DFLOAT_ISAREF_1(paper_right_margin_mf,(SI_Long)0L);
	right_margin = l_round(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,
		gensymed_symbol_1)),float_constant_6);
	gensymed_symbol = DFLOAT_ISAREF_1(bottom_margin_mf,(SI_Long)0L);
	gensymed_symbol_1 = DFLOAT_ISAREF_1(paper_bottom_margin_mf,
		(SI_Long)0L);
	bottom_margin = l_round(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,
		gensymed_symbol_1)),float_constant_6);
	scale = l_round(float_constant_7,
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(postscript_units_per_workspace_unit_mf,
		(SI_Long)0L)));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return native_printing_start_page(Output_window_for_printing_qm,
	    page_number,nrows,ncolumns,left_margin,top_margin,right_margin,
	    bottom_margin,scale,multipage_legends_p);
}

DEFINE_VARIABLE_WITH_SYMBOL(Background_processes, Qbackground_processes);

DEFINE_VARIABLE_WITH_SYMBOL(Background_processes_task, Qbackground_processes_task);

DEFINE_VARIABLE_WITH_SYMBOL(Current_background_process, Qcurrent_background_process);

Object Description_of_process_prop = UNBOUND;

static Object Qg2_defstruct_structure_name_process_description_g2_struct;  /* g2-defstruct-structure-name::process-description-g2-struct */

static Object Qdescription_of_process;  /* description-of-process */

/* MAKE-PROCESS-DESCRIPTION */
Object make_process_description(name,function,initializer,reclaimer)
    Object name, function, initializer, reclaimer;
{
    Object defstruct_g2_process_description_variable, the_array;
    Object process_description;
    SI_Long gensymed_symbol, i, ab_loop_bind_;

    x_note_fn_call(96,264);
    defstruct_g2_process_description_variable = Nil;
    gensymed_symbol = (SI_Long)5L;
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
    defstruct_g2_process_description_variable = the_array;
    SVREF(defstruct_g2_process_description_variable,FIX((SI_Long)0L)) = 
	    Qg2_defstruct_structure_name_process_description_g2_struct;
    process_description = defstruct_g2_process_description_variable;
    SVREF(process_description,FIX((SI_Long)1L)) = name;
    SVREF(process_description,FIX((SI_Long)2L)) = function;
    SVREF(process_description,FIX((SI_Long)3L)) = initializer;
    SVREF(process_description,FIX((SI_Long)4L)) = reclaimer;
    mutate_global_property(name,process_description,Qdescription_of_process);
    return VALUES_1(process_description);
}

Object The_type_description_of_process = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_processs, Qchain_of_available_processs);

DEFINE_VARIABLE_WITH_SYMBOL(Process_count, Qprocess_count);

Object Chain_of_available_processs_vector = UNBOUND;

/* PROCESS-STRUCTURE-MEMORY-USAGE */
Object process_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(96,265);
    temp = Process_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PROCESS-COUNT */
Object outstanding_process_count()
{
    Object def_structure_process_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(96,266);
    gensymed_symbol = IFIX(Process_count);
    def_structure_process_variable = Chain_of_available_processs;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_process_variable))
	goto end_loop;
    def_structure_process_variable = ISVREF(def_structure_process_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PROCESS-1 */
Object reclaim_process_1(process)
    Object process;
{
    Object temp, svref_arg_2;

    x_note_fn_call(96,267);
    inline_note_reclaim_cons(process,Nil);
    temp = ISVREF(Chain_of_available_processs_vector,
	    IFIX(Current_thread_index));
    SVREF(process,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_processs_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = process;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PROCESS */
Object reclaim_structure_for_process(process)
    Object process;
{
    x_note_fn_call(96,268);
    return reclaim_process_1(process);
}

static Object Qg2_defstruct_structure_name_process_g2_struct;  /* g2-defstruct-structure-name::process-g2-struct */

/* MAKE-PERMANENT-PROCESS-STRUCTURE-INTERNAL */
Object make_permanent_process_structure_internal()
{
    Object def_structure_process_variable, defstruct_g2_process_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(96,269);
    def_structure_process_variable = Nil;
    atomic_incff_symval(Qprocess_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_process_variable = Nil;
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
	defstruct_g2_process_variable = the_array;
	SVREF(defstruct_g2_process_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_process_g2_struct;
	def_structure_process_variable = defstruct_g2_process_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_process_variable);
}

/* MAKE-PROCESS-1-1 */
Object make_process_1_1()
{
    Object def_structure_process_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(96,270);
    def_structure_process_variable = 
	    ISVREF(Chain_of_available_processs_vector,
	    IFIX(Current_thread_index));
    if (def_structure_process_variable) {
	svref_arg_1 = Chain_of_available_processs_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_process_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_process_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_process_g2_struct;
    }
    else
	def_structure_process_variable = 
		make_permanent_process_structure_internal();
    inline_note_allocate_cons(def_structure_process_variable,Nil);
    ISVREF(def_structure_process_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    ISVREF(def_structure_process_variable,(SI_Long)5L) = FIX((SI_Long)0L);
    ISVREF(def_structure_process_variable,(SI_Long)6L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_process_variable);
}

static Object Qwaiting;            /* waiting */

/* MAKE-BACKGROUND-PROCESS */
Object make_background_process varargs_1(int, n)
{
    Object name;
    Object arg_1, arg_2, arg_3, process_description_qm, function, initializer;
    Object state_block, process;
    Declare_varargs_nonrelocating;

    x_note_fn_call(96,271);
    INIT_ARGS_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    arg_1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     No_arg;
    arg_2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     No_arg;
    arg_3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     No_arg;
    END_ARGS_nonrelocating();
    process_description_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
	    Qdescription_of_process);
    if (process_description_qm) {
	function = ISVREF(process_description_qm,(SI_Long)2L);
	initializer = ISVREF(process_description_qm,(SI_Long)3L);
	if (EQ(arg_1,No_arg))
	    state_block = FUNCALL_0(initializer);
	else if (EQ(arg_2,No_arg))
	    state_block = FUNCALL_1(initializer,arg_1);
	else if (EQ(arg_3,No_arg))
	    state_block = FUNCALL_2(initializer,arg_1,arg_2);
	else
	    state_block = FUNCALL_3(initializer,arg_1,arg_2,arg_3);
	process = make_process_1_1();
	SVREF(process,FIX((SI_Long)1L)) = name;
	SVREF(process,FIX((SI_Long)2L)) = function;
	SVREF(process,FIX((SI_Long)3L)) = Qwaiting;
	SVREF(process,FIX((SI_Long)7L)) = state_block;
	Background_processes = nconc2(Background_processes,
		gensym_cons_1(process,Nil));
	maybe_schedule_service_workstations_final();
	return VALUES_1(process);
    }
    else
	return VALUES_1(Qt);
}

static Object Qrunning;            /* running */

static Object Qdone;               /* done */

/* CALL-BACKGROUND-PROCESS */
Object call_background_process(process)
    Object process;
{
    Object naughty_process, current_background_process, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,272);
    SAVE_STACK();
    if (EQ(ISVREF(process,(SI_Long)3L),Qwaiting)) {
	SVREF(process,FIX((SI_Long)3L)) = Qrunning;
	naughty_process = T;
	current_background_process = process;
	PUSH_SPECIAL_WITH_SYMBOL(Current_background_process,Qcurrent_background_process,current_background_process,
		0);
	  gensymed_symbol = ISVREF(process,(SI_Long)2L);
	  gensymed_symbol_1 = process;
	  gensymed_symbol_2 = ISVREF(process,(SI_Long)7L);
	  inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2);
	  naughty_process = Nil;
	  temp = ISVREF(process,(SI_Long)3L);
	  if (EQ(temp,Qrunning))
	      SAVE_VALUES(VALUES_1(SVREF(process,FIX((SI_Long)3L)) = 
		      Qwaiting));
	  else if (EQ(temp,Qdone))
	      SAVE_VALUES(kill_background_process(process));
	  else
	      SAVE_VALUES(VALUES_1(Qnil));
	POP_SPECIAL();
	if (naughty_process)
	    kill_background_process(process);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qservice_background_processes;  /* service-background-processes */

/* SCHEDULE-TASK-FOR-BACKGROUND-PROCESSES */
Object schedule_task_for_background_processes()
{
    Object task_priority, old, new_1, def_structure_schedule_task_variable;
    Object temp, svref_arg_2, svref_new_value, task, structure_being_reclaimed;
    char svref_new_value_1;
    double task_start_time, aref_new_value;
    Declare_special(1);

    x_note_fn_call(96,273);
    if (Background_processes &&  !TRUEP(Background_processes_task)) {
	task_priority = ISVREF(Printer_setup,(SI_Long)25L);
	task_start_time = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) + 0.0;
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = Background_processes_task;
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,task_start_time);
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	SVREF(task,FIX((SI_Long)4L)) = task_priority;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qservice_background_processes;
	temp = SYMBOL_FUNCTION(Qservice_background_processes);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
	new_1 = task;
	if (CAS_SYMBOL(Qbackground_processes_task,old,new_1)) {
	    if (old) {
		if (EQ(old,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(old,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(old);
		inline_note_reclaim_cons(old,Nil);
		structure_being_reclaimed = old;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(old,(SI_Long)9L));
		  SVREF(old,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(old,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = old;
	    }
	    future_task_schedule_2(new_1);
	    return VALUES_1(new_1);
	}
	else {
	    inline_note_reclaim_cons(new_1,Nil);
	    structure_being_reclaimed = new_1;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
	      SVREF(new_1,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = new_1;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* SERVICE-BACKGROUND-PROCESSES */
Object service_background_processes()
{
    Object process, ab_loop_list_, gensymed_symbol, structure_being_reclaimed;
    Object temp, svref_arg_2, temp_1;
    Declare_special(1);

    x_note_fn_call(96,274);
    process = Nil;
    ab_loop_list_ = Background_processes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    process = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    call_background_process(process);
    if (time_slice_expired_p())
	goto end_loop;
    goto next_loop;
  end_loop:;
    if (Background_processes_task) {
	gensymed_symbol = Nil;
      next_loop_1:
	gensymed_symbol = Background_processes_task;
	if (CAS_SYMBOL(Qbackground_processes_task,gensymed_symbol,Nil)) {
	    if (gensymed_symbol) {
		if (EQ(gensymed_symbol,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(gensymed_symbol,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
		inline_note_reclaim_cons(gensymed_symbol,Nil);
		structure_being_reclaimed = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			  (SI_Long)9L));
		  SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol;
	    }
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
      end_1:;
	Background_processes_task = Nil;
    }
    temp_1 = Background_processes ? 
	    schedule_task_for_background_processes() : Nil;
    return VALUES_1(temp_1);
}

static Object Qdead;               /* dead */

/* KILL-BACKGROUND-PROCESS */
Object kill_background_process(process)
    Object process;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(96,275);
    SVREF(process,FIX((SI_Long)3L)) = Qdead;
    Background_processes = delete_gensym_element_1(process,
	    Background_processes);
    gensymed_symbol = ISVREF(process,(SI_Long)1L);
    gensymed_symbol = 
	    ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qdescription_of_process),(SI_Long)4L);
    gensymed_symbol_1 = ISVREF(process,(SI_Long)7L);
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    reclaim_process_1(process);
    return VALUES_1(Nil);
}

static Object string_constant_161;  /* "Unable to print because opening the output file (~S) failed." */

/* MAKE-PRINTING-STREAM */
Object make_printing_stream(format_1)
    Object format_1;
{
    Object requested_filename_qm, filename_qm, printing_stream_qm;

    x_note_fn_call(96,276);
    if ( !EQ(format_1,Qnative)) {
	requested_filename_qm = printer_setup_particular(Qab_pathname);
	filename_qm = requested_filename_qm ? 
		copy_text_string(requested_filename_qm) : 
		generate_output_filename_for_printing(format_1);
	if (filename_qm) {
	    if (EQ(format_1,Qpostscript))
		printing_stream_qm = g2_stream_open_for_output(filename_qm);
	    else if (EQ(format_1,Qbitmap))
		printing_stream_qm = 
			g2_stream_open_for_binary_output(filename_qm);
	    else
		printing_stream_qm = Qnil;
	}
	else
	    printing_stream_qm = Nil;
	if (filename_qm &&  !TRUEP(printing_stream_qm))
	    notify_user(2,string_constant_161,filename_qm);
	if (filename_qm)
	    reclaim_text_string(filename_qm);
	return VALUES_1(printing_stream_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_162;  /* "Unable to print because the print file template was bad." */

static Object string_constant_163;  /* "Unable to print because the paper size in the printer-setup system table is invalid." */

static Object string_constant_164;  /* "Unable to print.  ~
				     *                 No available file name was found after trying ten variations ~
				     *                    of the filename suggested in the printer-setup system table.  ~
				     *                 You may need to delete old print files.  ~
				     *                 If you try again ten more names will be tried."
				     */

/* GENERATE-OUTPUT-FILENAME-FOR-PRINTING */
Object generate_output_filename_for_printing(format_1)
    Object format_1;
{
    Object spooled_filename_template, filename_qm, temp_1;
    char temp;

    x_note_fn_call(96,277);
    spooled_filename_template = 
	    printer_setup_particular(Qspooled_filename_template);
    filename_qm = Nil;
    if (Current_computation_component_particulars)
	temp = 
		TRUEP(get_particulars_of_frame_note_from_component_particulars(Qprinter_file_template_is_misformed,
		Printer_setup,Current_computation_component_particulars));
    else {
	temp_1 = ISVREF(Printer_setup,(SI_Long)8L);
	temp = TRUEP(getfq_function_no_default(CDR(temp_1),
		Qprinter_file_template_is_misformed));
    }
    if (temp)
	notify_user(1,string_constant_162);
    else {
	if (Current_computation_component_particulars)
	    temp = 
		    TRUEP(get_particulars_of_frame_note_from_component_particulars(Qprinter_paper_size_is_unreasonable,
		    Printer_setup,Current_computation_component_particulars));
	else {
	    temp_1 = ISVREF(Printer_setup,(SI_Long)8L);
	    temp = TRUEP(getfq_function_no_default(CDR(temp_1),
		    Qprinter_paper_size_is_unreasonable));
	}
	if (temp)
	    notify_user(1,string_constant_163);
	else {
	    filename_qm = 
		    instantiate_file_template(spooled_filename_template,
		    format_1);
	    if ( !TRUEP(filename_qm))
		notify_user(1,string_constant_164);
	}
    }
    return VALUES_1(filename_qm);
}

/* CLOSE-PRINTING-STREAM */
Object close_printing_stream(printing_stream)
    Object printing_stream;
{
    Object true_pathname_of_spooled_file;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,278);
    PUSH_SPECIAL_WITH_SYMBOL(Printing_stream,Qprinting_stream,printing_stream,
	    0);
      true_pathname_of_spooled_file = gensym_truename(Printing_stream);
      g2_stream_close(Printing_stream);
      if (EQ(Printing_format,Qpostscript))
	  spool_file_to_printer_for_this_platform(true_pathname_of_spooled_file);
      result = reclaim_gensym_pathname(true_pathname_of_spooled_file);
    POP_SPECIAL();
    return result;
}

static Object Qstored_raster_type_for_window;  /* stored-raster-type-for-window */

static Object Qscratchpad_raster_type_for_window;  /* scratchpad-raster-type-for-window */

static Object Qtype_of_gensym_window;  /* type-of-gensym-window */

static Object Qwidth_of_window_border;  /* width-of-window-border */

static Object Qpane_layout;        /* pane-layout */

static Object Qcolor_description_plist_qm;  /* color-description-plist? */

static Object Qblack_and_white;    /* black-and-white */

static Object Qgrays;              /* grays */

/* MAKE-GENSYM-WINDOW-FOR-PRINTING */
Object make_gensym_window_for_printing(window_width_1,window_height_1)
    Object window_width_1, window_height_1;
{
    Object window_parameters_plist, list_1, pane_layout;
    Object color_description_plist_qm, temp, color_conv, temp_1;
    Object gensym_window_for_printing, svref_new_value;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(96,279);
    window_parameters_plist = make_window_parameters_plist(Nil);
    mutate_gensym_plist(window_parameters_plist,
	    Qstored_raster_type_for_window,Qprinter);
    mutate_gensym_plist(window_parameters_plist,
	    Qscratchpad_raster_type_for_window,Qprinter);
    mutate_gensym_plist(window_parameters_plist,Qtype_of_gensym_window,
	    Qprinter);
    mutate_gensym_plist(window_parameters_plist,Qwidth_of_window_border,
	    FIX((SI_Long)0L));
    list_1 = window_parameters_plist;
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qpane_layout))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    pane_layout = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    list_1 = window_parameters_plist;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qcolor_description_plist_qm))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    color_description_plist_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (CONSP(pane_layout)) {
	temp = gensym_list_2(FIX((SI_Long)0L),FIX((SI_Long)0L));
	M_CDR(pane_layout) = temp;
    }
    if (color_description_plist_qm)
	reclaim_gensym_tree_1(color_description_plist_qm);
    color_conv = printer_setup_particular(Qcolor_conversion);
    if (EQ(Printing_format,Qnative) || EQ(Printing_format,Qbitmap)) {
	if (EQ(Qblack_and_white,color_conv)) {
	    gensymed_symbol = (SI_Long)255L & (SI_Long)255L;
	    gensymed_symbol_1 = (SI_Long)16L;
	    gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
	    gensymed_symbol_2 = (SI_Long)255L & (SI_Long)255L;
	    gensymed_symbol = (SI_Long)8L;
	    gensymed_symbol = gensymed_symbol_2 << gensymed_symbol;
	    gensymed_symbol_2 = (SI_Long)255L & (SI_Long)255L;
	    temp_1 = 
		    make_monochrome_color_description_plist(FIX((SI_Long)0L),
		    FIX(gensymed_symbol_1 | gensymed_symbol | 
		    gensymed_symbol_2));
	}
	else if (EQ(Qgrays,color_conv))
	    temp_1 = make_gray_true_color_description_plist();
	else
	    temp_1 = make_true_color_description_plist();
    }
    else if (EQ(Qblack_and_white,color_conv))
	temp_1 = make_monochrome_color_description_plist(FIX((SI_Long)1L),
		FIX((SI_Long)0L));
    else
	temp_1 = make_printing_color_description_plist();
    mutate_gensym_plist(window_parameters_plist,
	    Qcolor_description_plist_qm,temp_1);
    gensym_window_for_printing = make_or_revise_window(Nil,
	    FIX((SI_Long)0L),FIX((SI_Long)0L),window_width_1,
	    window_height_1,Nil,Nil,window_parameters_plist);
    PUSH_SPECIAL_WITH_SYMBOL(Gensym_window_for_printing,Qgensym_window_for_printing,gensym_window_for_printing,
	    0);
      temp = Gensym_window_for_printing;
      svref_new_value = Servicing_workstation_qm ? Current_workstation : 
	      CAR(Workstations_in_service);
      SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
      lay_out_window(Gensym_window_for_printing);
      temp = Gensym_window_for_printing;
      SVREF(temp,FIX((SI_Long)30L)) = Kpaint_infered_from_xor;
      result = VALUES_1(Gensym_window_for_printing);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-GENSYM-WINDOW-FOR-PRINTING */
Object reclaim_gensym_window_for_printing(printing_window)
    Object printing_window;
{
    x_note_fn_call(96,280);
    SVREF(printing_window,FIX((SI_Long)2L)) = Nil;
    return reclaim_window_for_workstation(printing_window);
}

/* SETUP-IMAGE-PLANE-FOR-PRINTING */
Object setup_image_plane_for_printing(workspace,x_offset,y_offset)
    Object workspace, x_offset, y_offset;
{
    Object pane, current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, image_plane;
    Object gensymed_symbol_1, allow_invalidate_on_printing_window_p;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(96,281);
    SAVE_STACK();
    pane = detail_pane(Gensym_window_for_printing);
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = ISVREF(Gensym_window_for_printing,(SI_Long)2L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		11);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  10);
	    current_g2_window_for_this_workstation_qm = 
		    ISVREF(Current_workstation,(SI_Long)25L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		    9);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		      8);
		current_workstation_native_window_qm = 
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			7);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			  6);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    5);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      4);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				3);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  2);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    1);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      0);
				temp = get_available_image_plane(pane,
					lookup_frame_description_reference_of_block_qm(workspace),
					Nil);
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(For_workstation);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    image_plane = result;
    associate_workspace_and_image_plane(workspace,image_plane);
    ISVREF(image_plane,(SI_Long)11L) = FIX((SI_Long)4096L);
    ISVREF(image_plane,(SI_Long)12L) = FIX((SI_Long)4096L);
    gensymed_symbol = IFIX(ISVREF(Gensym_window_for_printing,(SI_Long)7L));
    gensymed_symbol_1 = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    gensymed_symbol_3 = IFIX(x_offset);
    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    svref_new_value = gensymed_symbol - gensymed_symbol_2;
    ISVREF(image_plane,(SI_Long)13L) = FIX(svref_new_value);
    gensymed_symbol = IFIX(ISVREF(Gensym_window_for_printing,(SI_Long)8L));
    gensymed_symbol_1 = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    gensymed_symbol_3 = IFIX(y_offset);
    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    svref_new_value = gensymed_symbol - gensymed_symbol_2;
    ISVREF(image_plane,(SI_Long)14L) = FIX(svref_new_value);
    set_up_edges_for_image_plane(image_plane);
    recompute_visible_regions_for_pane(ISVREF(image_plane,(SI_Long)2L));
    if (native_printing_p())
	decache_all_graph_renderings_on_window(Gensym_window_for_printing);
    allow_invalidate_on_printing_window_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Allow_invalidate_on_printing_window_p,Qallow_invalidate_on_printing_window_p,allow_invalidate_on_printing_window_p,
	    0);
      invalidate_image_plane(image_plane);
    POP_SPECIAL();
    RESTORE_STACK();
    return VALUES_1(image_plane);
}

DEFINE_VARIABLE_WITH_SYMBOL(Native_printing_icon_x_in_window, Qnative_printing_icon_x_in_window);

DEFINE_VARIABLE_WITH_SYMBOL(Native_printing_icon_y_in_window, Qnative_printing_icon_y_in_window);

DEFINE_VARIABLE_WITH_SYMBOL(Native_printing_color_differences, Qnative_printing_color_differences);

Object Native_printing_icp_message_handler_array = UNBOUND;

/* NATIVE-PRINTING-DEFAULT-ICP-HANDLER */
Object native_printing_default_icp_handler varargs_1(int, n)
{
    Declare_varargs_nonrelocating;

    x_note_fn_call(96,282);
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

/* NATIVE-PRINTING-P */
Object native_printing_p()
{
    x_note_fn_call(96,283);
    if (printing_p())
	return VALUES_1(EQ(Printing_format,Qnative) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* POSTSCRIPT-PRINTING-P */
Object postscript_printing_p()
{
    x_note_fn_call(96,284);
    if (printing_p())
	return VALUES_1(EQ(Printing_format,Qpostscript) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* BITMAP-PRINTING-P */
Object bitmap_printing_p()
{
    x_note_fn_call(96,285);
    if (printing_p())
	return VALUES_1(EQ(Printing_format,Qbitmap) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-SOLID-RECTANGLE-IN-CURRENT-SCRATCHPAD-RASTER */
Object native_printing_paint_solid_rectangle_in_current_scratchpad_raster(left,
	    top,right,bottom,color_value)
    Object left, top, right, bottom, color_value;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type, color_difference;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,286);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		if (Printing_icon_current_region_index_qm && 
			IFIX(Printing_icon_current_region_index_qm) >= 
			(SI_Long)0L && 
			FIXNUM_LT(Printing_icon_current_region_index_qm,
			length(Native_printing_color_differences))) {
		    color_difference = 
			    nth(Printing_icon_current_region_index_qm,
			    Native_printing_color_differences);
		    color_value = (EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value) : 
			    IFIX(color_difference) == (SI_Long)0L || 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value)) ? color_difference : 
			    FIXNUM_LOGXOR(color_difference,
			    Current_background_color_value);
		}
		if ( !(EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? FIXNUM_EQ(color_value,
			Transparent_color_value) : IFIX(color_value) == 
			(SI_Long)0L || FIXNUM_EQ(color_value,
			Transparent_color_value)))
		    result = paint_solid_rectangle_in_current_scratchpad_raster(left,
			    top,right,bottom,color_value);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-LINE-IN-CURRENT-SCRATCHPAD-RASTER */
Object native_printing_paint_line_in_current_scratchpad_raster(x1,y1_1,x2,
	    y2,color_value,paint_last_point_qm)
    Object x1, y1_1, x2, y2, color_value, paint_last_point_qm;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type, color_difference;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,287);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		if (Printing_icon_current_region_index_qm && 
			IFIX(Printing_icon_current_region_index_qm) >= 
			(SI_Long)0L && 
			FIXNUM_LT(Printing_icon_current_region_index_qm,
			length(Native_printing_color_differences))) {
		    color_difference = 
			    nth(Printing_icon_current_region_index_qm,
			    Native_printing_color_differences);
		    color_value = (EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value) : 
			    IFIX(color_difference) == (SI_Long)0L || 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value)) ? color_difference : 
			    FIXNUM_LOGXOR(color_difference,
			    Current_background_color_value);
		}
		if ( !(EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? FIXNUM_EQ(color_value,
			Transparent_color_value) : IFIX(color_value) == 
			(SI_Long)0L || FIXNUM_EQ(color_value,
			Transparent_color_value)))
		    result = paint_line_in_current_scratchpad_raster(x1,
			    y1_1,x2,y2,color_value,paint_last_point_qm);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-ARC-OR-CIRCLE-IN-CURRENT-SCRATCHPAD-RASTER */
Object native_printing_paint_arc_or_circle_in_current_scratchpad_raster(x1,
	    y1_1,x2,y2,x3,y3,x_scale,y_scale,color_value,circle_qm,filled_qm)
    Object x1, y1_1, x2, y2, x3, y3, x_scale, y_scale, color_value, circle_qm;
    Object filled_qm;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type, color_difference;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,288);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		if (Printing_icon_current_region_index_qm && 
			IFIX(Printing_icon_current_region_index_qm) >= 
			(SI_Long)0L && 
			FIXNUM_LT(Printing_icon_current_region_index_qm,
			length(Native_printing_color_differences))) {
		    color_difference = 
			    nth(Printing_icon_current_region_index_qm,
			    Native_printing_color_differences);
		    color_value = (EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value) : 
			    IFIX(color_difference) == (SI_Long)0L || 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value)) ? color_difference : 
			    FIXNUM_LOGXOR(color_difference,
			    Current_background_color_value);
		}
		if ( !(EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? FIXNUM_EQ(color_value,
			Transparent_color_value) : IFIX(color_value) == 
			(SI_Long)0L || FIXNUM_EQ(color_value,
			Transparent_color_value)))
		    result = paint_arc_or_circle_in_current_scratchpad_raster(x1,
			    y1_1,x2,y2,x3,y3,x_scale,y_scale,color_value,
			    circle_qm,filled_qm);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-FILLED-TRIANGLE-IN-CURRENT-SCRATCHPAD-RASTER */
Object native_printing_paint_filled_triangle_in_current_scratchpad_raster(x1,
	    y1_1,x2,y2,x3,y3,color_value)
    Object x1, y1_1, x2, y2, x3, y3, color_value;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type, color_difference;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,289);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		if (Printing_icon_current_region_index_qm && 
			IFIX(Printing_icon_current_region_index_qm) >= 
			(SI_Long)0L && 
			FIXNUM_LT(Printing_icon_current_region_index_qm,
			length(Native_printing_color_differences))) {
		    color_difference = 
			    nth(Printing_icon_current_region_index_qm,
			    Native_printing_color_differences);
		    color_value = (EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value) : 
			    IFIX(color_difference) == (SI_Long)0L || 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value)) ? color_difference : 
			    FIXNUM_LOGXOR(color_difference,
			    Current_background_color_value);
		}
		if ( !(EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? FIXNUM_EQ(color_value,
			Transparent_color_value) : IFIX(color_value) == 
			(SI_Long)0L || FIXNUM_EQ(color_value,
			Transparent_color_value)))
		    result = paint_filled_triangle_in_current_scratchpad_raster(x1,
			    y1_1,x2,y2,x3,y3,color_value);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-FILLED-POLYGON-IN-CURRENT-SCRATCHPAD-RASTER */
Object native_printing_paint_filled_polygon_in_current_scratchpad_raster(unsigned_polygon_point_list,
	    color_value)
    Object unsigned_polygon_point_list, color_value;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type, color_difference;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,290);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		if (Printing_icon_current_region_index_qm && 
			IFIX(Printing_icon_current_region_index_qm) >= 
			(SI_Long)0L && 
			FIXNUM_LT(Printing_icon_current_region_index_qm,
			length(Native_printing_color_differences))) {
		    color_difference = 
			    nth(Printing_icon_current_region_index_qm,
			    Native_printing_color_differences);
		    color_value = (EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value) : 
			    IFIX(color_difference) == (SI_Long)0L || 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value)) ? color_difference : 
			    FIXNUM_LOGXOR(color_difference,
			    Current_background_color_value);
		}
		if ( !(EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? FIXNUM_EQ(color_value,
			Transparent_color_value) : IFIX(color_value) == 
			(SI_Long)0L || FIXNUM_EQ(color_value,
			Transparent_color_value)))
		    result = paint_filled_polygon_in_current_scratchpad_raster(unsigned_polygon_point_list,
			    color_value);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-WIDE-LINE-IN-CURRENT-SCRATCHPAD-RASTER */
Object native_printing_paint_wide_line_in_current_scratchpad_raster(x1,
	    y1_1,x2,y2,color_value,paint_last_point_qm,line_width)
    Object x1, y1_1, x2, y2, color_value, paint_last_point_qm, line_width;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type, color_difference;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,291);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		if (Printing_icon_current_region_index_qm && 
			IFIX(Printing_icon_current_region_index_qm) >= 
			(SI_Long)0L && 
			FIXNUM_LT(Printing_icon_current_region_index_qm,
			length(Native_printing_color_differences))) {
		    color_difference = 
			    nth(Printing_icon_current_region_index_qm,
			    Native_printing_color_differences);
		    color_value = (EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value) : 
			    IFIX(color_difference) == (SI_Long)0L || 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value)) ? color_difference : 
			    FIXNUM_LOGXOR(color_difference,
			    Current_background_color_value);
		}
		if ( !(EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? FIXNUM_EQ(color_value,
			Transparent_color_value) : IFIX(color_value) == 
			(SI_Long)0L || FIXNUM_EQ(color_value,
			Transparent_color_value)))
		    result = paint_wide_line_in_current_scratchpad_raster(x1,
			    y1_1,x2,y2,color_value,paint_last_point_qm,
			    line_width);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-POINT-IN-CURRENT-SCRATCHPAD-RASTER */
Object native_printing_paint_point_in_current_scratchpad_raster(x,y,
	    color_value)
    Object x, y, color_value;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type, color_difference;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,292);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		if (Printing_icon_current_region_index_qm && 
			IFIX(Printing_icon_current_region_index_qm) >= 
			(SI_Long)0L && 
			FIXNUM_LT(Printing_icon_current_region_index_qm,
			length(Native_printing_color_differences))) {
		    color_difference = 
			    nth(Printing_icon_current_region_index_qm,
			    Native_printing_color_differences);
		    color_value = (EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value) : 
			    IFIX(color_difference) == (SI_Long)0L || 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value)) ? color_difference : 
			    FIXNUM_LOGXOR(color_difference,
			    Current_background_color_value);
		}
		if ( !(EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? FIXNUM_EQ(color_value,
			Transparent_color_value) : IFIX(color_value) == 
			(SI_Long)0L || FIXNUM_EQ(color_value,
			Transparent_color_value)))
		    result = paint_point_in_current_scratchpad_raster(x,y,
			    color_value);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-IMAGE-IN-CURRENT-SCRATCHPAD-RASTER */
Object native_printing_paint_image_in_current_scratchpad_raster(image_data,
	    x_in_icon,y_in_icon,x_scale,y_scale,width,height,rotation,
	    quality,draw_or_burn)
    Object image_data, x_in_icon, y_in_icon, x_scale, y_scale, width, height;
    Object rotation, quality, draw_or_burn;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type, color_difference;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,293);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		if (Printing_icon_current_region_index_qm && 
			IFIX(Printing_icon_current_region_index_qm) >= 
			(SI_Long)0L && 
			FIXNUM_LT(Printing_icon_current_region_index_qm,
			length(Native_printing_color_differences))) {
		    color_difference = 
			    nth(Printing_icon_current_region_index_qm,
			    Native_printing_color_differences);
		    draw_or_burn = (EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value) : 
			    IFIX(color_difference) == (SI_Long)0L || 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value)) ? color_difference : 
			    FIXNUM_LOGXOR(color_difference,
			    Current_background_color_value);
		}
		if ( !(EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? FIXNUM_EQ(draw_or_burn,
			Transparent_color_value) : IFIX(draw_or_burn) == 
			(SI_Long)0L || FIXNUM_EQ(draw_or_burn,
			Transparent_color_value)))
		    result = paint_image_in_current_scratchpad_raster(image_data,
			    x_in_icon,y_in_icon,x_scale,y_scale,width,
			    height,rotation,quality,draw_or_burn);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-ORIENT-AND-PAINT-LINE-OF-TEXT-TO-CURRENT-SCRATCHPAD-RASTER */
Object native_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    normalized_width,normalized_height,text_line,text_orientation,
	    icon_orientation,word_spacing,font_map,color_value,
	    normalized_x_scale,normalized_y_scale,
	    left_edge_of_line_of_text_in_scratchpad_raster,
	    baseline_in_scratchpad_raster)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, normalized_width, normalized_height, text_line;
    Object text_orientation, icon_orientation, word_spacing, font_map;
    Object color_value, normalized_x_scale, normalized_y_scale;
    Object left_edge_of_line_of_text_in_scratchpad_raster;
    Object baseline_in_scratchpad_raster;
{
    Object reflection_and_rotation_qm, width, height, clipped_left_edge_temp;
    Object clipped_right_edge_temp;
    Object left_edge_of_line_of_text_in_scratchpad_raster_temp;
    Object clipped_top_edge_temp, angle, reflect, current_window_1;
    Object type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type, color_difference;
    SI_Long unshifted_result;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,294);
    if (EQ(Printing_format,Qnative)) {
	if ( !EQ(icon_orientation,Qnormal)) {
	    reflection_and_rotation_qm = icon_orientation;
	    if (IFIX(normalized_x_scale) == (SI_Long)4096L)
		width = normalized_width;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    normalized_x_scale) && FIXNUM_LT(normalized_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    normalized_width) && FIXNUM_LT(normalized_width,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(normalized_x_scale,
			normalized_width)) + (SI_Long)2048L;
		width = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		width = scalef_function(normalized_x_scale,normalized_width);
	    if (IFIX(normalized_y_scale) == (SI_Long)4096L)
		height = normalized_height;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    normalized_y_scale) && FIXNUM_LT(normalized_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    normalized_height) && FIXNUM_LT(normalized_height,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(normalized_y_scale,
			normalized_height)) + (SI_Long)2048L;
		height = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		height = scalef_function(normalized_y_scale,normalized_height);
	    if (reflection_and_rotation_qm) {
		if (EQ(reflection_and_rotation_qm,Qnormal));
		else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
		    clipped_left_edge_temp = FIXNUM_MINUS(height,
			    clipped_top_edge);
		    clipped_top_edge = clipped_left_edge;
		    clipped_left_edge = clipped_left_edge_temp;
		    clipped_right_edge_temp = FIXNUM_MINUS(height,
			    clipped_bottom_edge);
		    clipped_bottom_edge = clipped_right_edge;
		    clipped_right_edge = clipped_right_edge_temp;
		    left_edge_of_line_of_text_in_scratchpad_raster_temp = 
			    FIXNUM_MINUS(height,baseline_in_scratchpad_raster);
		    baseline_in_scratchpad_raster = 
			    left_edge_of_line_of_text_in_scratchpad_raster;
		    left_edge_of_line_of_text_in_scratchpad_raster = 
			    left_edge_of_line_of_text_in_scratchpad_raster_temp;
		}
		else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
		    clipped_left_edge_temp = clipped_top_edge;
		    clipped_top_edge = FIXNUM_MINUS(width,clipped_left_edge);
		    clipped_left_edge = clipped_left_edge_temp;
		    clipped_right_edge_temp = clipped_bottom_edge;
		    clipped_bottom_edge = FIXNUM_MINUS(width,
			    clipped_right_edge);
		    clipped_right_edge = clipped_right_edge_temp;
		    left_edge_of_line_of_text_in_scratchpad_raster_temp = 
			    baseline_in_scratchpad_raster;
		    baseline_in_scratchpad_raster = FIXNUM_MINUS(width,
			    left_edge_of_line_of_text_in_scratchpad_raster);
		    left_edge_of_line_of_text_in_scratchpad_raster = 
			    left_edge_of_line_of_text_in_scratchpad_raster_temp;
		}
		else if (EQ(reflection_and_rotation_qm,
			Qreflected_clockwise_270)) {
		    clipped_left_edge_temp = clipped_top_edge;
		    clipped_top_edge = clipped_left_edge;
		    clipped_left_edge = clipped_left_edge_temp;
		    clipped_right_edge_temp = clipped_bottom_edge;
		    clipped_bottom_edge = clipped_right_edge;
		    clipped_right_edge = clipped_right_edge_temp;
		    left_edge_of_line_of_text_in_scratchpad_raster_temp = 
			    baseline_in_scratchpad_raster;
		    baseline_in_scratchpad_raster = 
			    left_edge_of_line_of_text_in_scratchpad_raster;
		    left_edge_of_line_of_text_in_scratchpad_raster = 
			    left_edge_of_line_of_text_in_scratchpad_raster_temp;
		}
		else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
		    clipped_left_edge = FIXNUM_MINUS(width,clipped_left_edge);
		    clipped_top_edge = FIXNUM_MINUS(height,clipped_top_edge);
		    clipped_right_edge = FIXNUM_MINUS(width,
			    clipped_right_edge);
		    clipped_bottom_edge = FIXNUM_MINUS(height,
			    clipped_bottom_edge);
		    left_edge_of_line_of_text_in_scratchpad_raster = 
			    FIXNUM_MINUS(width,
			    left_edge_of_line_of_text_in_scratchpad_raster);
		    baseline_in_scratchpad_raster = FIXNUM_MINUS(height,
			    baseline_in_scratchpad_raster);
		}
		else if (EQ(reflection_and_rotation_qm,
			Qreflected_clockwise_90)) {
		    clipped_left_edge_temp = FIXNUM_MINUS(height,
			    clipped_top_edge);
		    clipped_top_edge = FIXNUM_MINUS(width,clipped_left_edge);
		    clipped_left_edge = clipped_left_edge_temp;
		    clipped_right_edge_temp = FIXNUM_MINUS(height,
			    clipped_bottom_edge);
		    clipped_bottom_edge = FIXNUM_MINUS(width,
			    clipped_right_edge);
		    clipped_right_edge = clipped_right_edge_temp;
		    left_edge_of_line_of_text_in_scratchpad_raster_temp = 
			    FIXNUM_MINUS(height,baseline_in_scratchpad_raster);
		    baseline_in_scratchpad_raster = FIXNUM_MINUS(width,
			    left_edge_of_line_of_text_in_scratchpad_raster);
		    left_edge_of_line_of_text_in_scratchpad_raster = 
			    left_edge_of_line_of_text_in_scratchpad_raster_temp;
		}
		else if (EQ(reflection_and_rotation_qm,Qreflected)) {
		    clipped_left_edge = FIXNUM_MINUS(width,clipped_left_edge);
		    clipped_right_edge = FIXNUM_MINUS(width,
			    clipped_right_edge);
		    left_edge_of_line_of_text_in_scratchpad_raster = 
			    FIXNUM_MINUS(width,
			    left_edge_of_line_of_text_in_scratchpad_raster);
		}
		else if (EQ(reflection_and_rotation_qm,
			Qreflected_clockwise_180)) {
		    clipped_top_edge = FIXNUM_MINUS(height,clipped_top_edge);
		    clipped_bottom_edge = FIXNUM_MINUS(height,
			    clipped_bottom_edge);
		    baseline_in_scratchpad_raster = FIXNUM_MINUS(height,
			    baseline_in_scratchpad_raster);
		}
	    }
	    clipped_top_edge_temp = FIXNUM_MIN(clipped_top_edge,
		    clipped_bottom_edge);
	    clipped_left_edge_temp = FIXNUM_MIN(clipped_left_edge,
		    clipped_right_edge);
	    clipped_right_edge_temp = FIXNUM_MAX(clipped_left_edge,
		    clipped_right_edge);
	    clipped_bottom_edge = FIXNUM_MAX(clipped_top_edge,
		    clipped_bottom_edge);
	    clipped_top_edge = clipped_top_edge_temp;
	    clipped_right_edge = clipped_right_edge_temp;
	    clipped_left_edge = clipped_left_edge_temp;
	}
	if (EQ(icon_orientation,Qnil) || EQ(icon_orientation,Qnormal))
	    result = VALUES_2(FIX((SI_Long)0L),FIX((SI_Long)0L));
	else if (EQ(icon_orientation,Qclockwise_90))
	    result = VALUES_2(FIX((SI_Long)-90L),FIX((SI_Long)0L));
	else if (EQ(icon_orientation,Qclockwise_180))
	    result = VALUES_2(FIX((SI_Long)180L),FIX((SI_Long)0L));
	else if (EQ(icon_orientation,Qclockwise_270))
	    result = VALUES_2(FIX((SI_Long)90L),FIX((SI_Long)0L));
	else if (EQ(icon_orientation,Qreflected))
	    result = VALUES_2(FIX((SI_Long)0L),FIX((SI_Long)1L));
	else if (EQ(icon_orientation,Qreflected_clockwise_90))
	    result = VALUES_2(FIX((SI_Long)-90L),FIX((SI_Long)1L));
	else if (EQ(icon_orientation,Qreflected_clockwise_180))
	    result = VALUES_2(FIX((SI_Long)180L),FIX((SI_Long)1L));
	else if (EQ(icon_orientation,Qreflected_clockwise_270))
	    result = VALUES_2(FIX((SI_Long)90L),FIX((SI_Long)1L));
	else
	    result = VALUES_2(FIX((SI_Long)0L),FIX((SI_Long)0L));
	MVS_2(result,angle,reflect);
	if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	    current_window_1 = Output_window_for_printing_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		    3);
	      type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		      2);
		current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
			1);
		  current_scratchpad_raster_type = ISVREF(Current_window,
			  (SI_Long)23L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			  0);
		    synchronize_background_color_value();
		    if (Printing_icon_current_region_index_qm && 
			    IFIX(Printing_icon_current_region_index_qm) >= 
			    (SI_Long)0L && 
			    FIXNUM_LT(Printing_icon_current_region_index_qm,
			    length(Native_printing_color_differences))) {
			color_difference = 
				nth(Printing_icon_current_region_index_qm,
				Native_printing_color_differences);
			color_value = (EQ(Current_drawing_transfer_mode,
				Kpaint_infered_from_xor) ? 
				FIXNUM_EQ(color_difference,
				Transparent_color_value) : 
				IFIX(color_difference) == (SI_Long)0L || 
				FIXNUM_EQ(color_difference,
				Transparent_color_value)) ? 
				color_difference : 
				FIXNUM_LOGXOR(color_difference,
				Current_background_color_value);
		    }
		    if ( !(EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    FIXNUM_EQ(color_value,Transparent_color_value) 
			    : IFIX(color_value) == (SI_Long)0L || 
			    FIXNUM_EQ(color_value,Transparent_color_value)))
			result = paint_line_of_text_in_current_window(FIXNUM_ADD(Native_printing_icon_x_in_window,
				clipped_left_edge),
				FIXNUM_ADD(Native_printing_icon_y_in_window,
				clipped_top_edge),
				FIXNUM_ADD(Native_printing_icon_x_in_window,
				clipped_right_edge),
				FIXNUM_ADD(Native_printing_icon_y_in_window,
				clipped_bottom_edge),text_line,
				word_spacing,CAR(font_map),color_value,
				FIX(IFIX(angle) * (SI_Long)10L),reflect,
				normalized_x_scale,normalized_y_scale,
				FIXNUM_ADD(Native_printing_icon_x_in_window,
				left_edge_of_line_of_text_in_scratchpad_raster),
				FIXNUM_ADD(Native_printing_icon_y_in_window,
				baseline_in_scratchpad_raster));
		    else
			result = VALUES_1(Nil);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		if (Printing_icon_current_region_index_qm && 
			IFIX(Printing_icon_current_region_index_qm) >= 
			(SI_Long)0L && 
			FIXNUM_LT(Printing_icon_current_region_index_qm,
			length(Native_printing_color_differences))) {
		    color_difference = 
			    nth(Printing_icon_current_region_index_qm,
			    Native_printing_color_differences);
		    color_value = (EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value) : 
			    IFIX(color_difference) == (SI_Long)0L || 
			    FIXNUM_EQ(color_difference,
			    Transparent_color_value)) ? color_difference : 
			    FIXNUM_LOGXOR(color_difference,
			    Current_background_color_value);
		}
		if ( !(EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? FIXNUM_EQ(color_value,
			Transparent_color_value) : IFIX(color_value) == 
			(SI_Long)0L || FIXNUM_EQ(color_value,
			Transparent_color_value)))
		    result = orient_and_paint_line_of_text_to_current_scratchpad_raster(clipped_left_edge,
			    clipped_top_edge,clipped_right_edge,
			    clipped_bottom_edge,normalized_width,
			    normalized_height,text_line,text_orientation,
			    icon_orientation,word_spacing,font_map,
			    color_value,normalized_x_scale,
			    normalized_y_scale,
			    left_edge_of_line_of_text_in_scratchpad_raster,
			    baseline_in_scratchpad_raster);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-FROM-LINE-OF-TEXT-TO-CURRENT-SCRATCHPAD-RASTER */
Object native_printing_paint_from_line_of_text_to_current_scratchpad_raster(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    text_line,word_spacing,font_map,color_value,x_scale,y_scale,
	    left_edge_of_line_of_text_in_window,baseline_in_window)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, text_line, word_spacing, font_map, color_value;
    Object x_scale, y_scale, left_edge_of_line_of_text_in_window;
    Object baseline_in_window;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,295);
    if (EQ(Printing_format,Qnative)) {
	if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	    current_window_1 = Output_window_for_printing_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		    3);
	      type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		      2);
		current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
			1);
		  current_scratchpad_raster_type = ISVREF(Current_window,
			  (SI_Long)23L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			  0);
		    synchronize_background_color_value();
		    result = paint_line_of_text_in_current_window(FIXNUM_ADD(Native_printing_icon_x_in_window,
			    clipped_left_edge),
			    FIXNUM_ADD(Native_printing_icon_y_in_window,
			    clipped_top_edge),
			    FIXNUM_ADD(Native_printing_icon_x_in_window,
			    clipped_right_edge),
			    FIXNUM_ADD(Native_printing_icon_y_in_window,
			    clipped_bottom_edge),text_line,word_spacing,
			    CAR(font_map),color_value,FIX((SI_Long)0L),
			    FIX((SI_Long)0L),x_scale,y_scale,
			    FIXNUM_ADD(Native_printing_icon_x_in_window,
			    left_edge_of_line_of_text_in_window),
			    FIXNUM_ADD(Native_printing_icon_y_in_window,
			    baseline_in_window));
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = paint_from_line_of_text_to_current_scratchpad_raster(clipped_left_edge,
			clipped_top_edge,clipped_right_edge,
			clipped_bottom_edge,text_line,word_spacing,
			font_map,color_value,x_scale,y_scale,
			left_edge_of_line_of_text_in_window,
			baseline_in_window);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-ADD-FROM-ICON-RENDERING-TO-CURRENT-WINDOW */
Object native_printing_add_from_icon_rendering_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,color_difference,icon_rendering,
	    left_edge_in_icon_rendering,top_edge_in_icon_rendering,
	    list_of_color_differences)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, color_difference;
    Object icon_rendering, left_edge_in_icon_rendering;
    Object top_edge_in_icon_rendering, list_of_color_differences;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,296);
    if (EQ(Printing_format,Qnative))
	return add_from_icon_rendering_to_current_window_2(subtract_instead_qm,
		clipped_left_edge,clipped_top_edge,clipped_right_edge,
		clipped_bottom_edge,color_difference,icon_rendering,
		left_edge_in_icon_rendering,top_edge_in_icon_rendering,
		list_of_color_differences);
    else if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = add_from_icon_rendering_to_current_window(subtract_instead_qm,
			clipped_left_edge,clipped_top_edge,
			clipped_right_edge,clipped_bottom_edge,
			color_difference,icon_rendering,
			left_edge_in_icon_rendering,
			top_edge_in_icon_rendering,list_of_color_differences);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* ADD-FROM-ICON-RENDERING-TO-CURRENT-WINDOW-2 */
Object add_from_icon_rendering_to_current_window_2(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,color_difference,icon_rendering,
	    left_edge_in_icon_rendering,top_edge_in_icon_rendering,
	    list_of_color_differences)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, color_difference;
    Object icon_rendering, left_edge_in_icon_rendering;
    Object top_edge_in_icon_rendering, list_of_color_differences;
{
    Object line_drawing, width, height, variable_overrides, first_element;
    Object polychrome_header_qm, icon_color_pattern_1;
    Object line_drawing_description_following_header;
    Object native_printing_icon_x_in_window, native_printing_icon_y_in_window;
    Object native_printing_color_differences;
    Object printing_icon_current_region_index_qm, current_window_1;
    Object type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(8);
    Object result;

    x_note_fn_call(96,297);
    line_drawing = ISVREF(icon_rendering,(SI_Long)8L);
    width = ISVREF(icon_rendering,(SI_Long)13L);
    height = ISVREF(icon_rendering,(SI_Long)14L);
    variable_overrides = ISVREF(icon_rendering,(SI_Long)9L);
    first_element = CAR(line_drawing);
    polychrome_header_qm = CONSP(first_element) && EQ(CAR(first_element),
	    Qpolychrome) ? first_element : Nil;
    icon_color_pattern_1 = REST(polychrome_header_qm);
    if (icon_color_pattern_1);
    else
	icon_color_pattern_1 = list_constant_27;
    line_drawing_description_following_header = polychrome_header_qm ? 
	    CDR(line_drawing) : line_drawing;
    native_printing_icon_x_in_window = FIXNUM_MINUS(clipped_left_edge,
	    left_edge_in_icon_rendering);
    PUSH_SPECIAL_WITH_SYMBOL(Native_printing_icon_x_in_window,Qnative_printing_icon_x_in_window,native_printing_icon_x_in_window,
	    7);
      native_printing_icon_y_in_window = FIXNUM_MINUS(clipped_top_edge,
	      top_edge_in_icon_rendering);
      PUSH_SPECIAL_WITH_SYMBOL(Native_printing_icon_y_in_window,Qnative_printing_icon_y_in_window,native_printing_icon_y_in_window,
	      6);
	native_printing_color_differences = list_of_color_differences;
	PUSH_SPECIAL_WITH_SYMBOL(Native_printing_color_differences,Qnative_printing_color_differences,native_printing_color_differences,
		5);
	  printing_icon_current_region_index_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Printing_icon_current_region_index_qm,Qprinting_icon_current_region_index_qm,printing_icon_current_region_index_qm,
		  4);
	    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
		current_window_1 = Output_window_for_printing_qm;
		PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
			3);
		  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
			  2);
		    current_native_window_qm = ISVREF(Current_window,
			    (SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
			    1);
		      current_scratchpad_raster_type = 
			      ISVREF(Current_window,(SI_Long)23L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			      0);
			synchronize_background_color_value();
			paint_icon_in_current_window(Native_printing_icon_x_in_window,
				Native_printing_icon_y_in_window,
				clipped_left_edge,clipped_top_edge,
				clipped_right_edge,clipped_bottom_edge,
				FIX((SI_Long)1L));
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    paint_one_bitmap_for_icon_on_scratchpad_raster(icon_color_pattern_1,
		    line_drawing_description_following_header,width,height,
		    ISVREF(icon_rendering,(SI_Long)3L),
		    ISVREF(icon_rendering,(SI_Long)4L),
		    FIXNUM_LOGXOR(color_difference,
		    Current_background_color_value),ISVREF(icon_rendering,
		    (SI_Long)5L),variable_overrides,width,height,Nil);
	    result = send_icp_end_message_block();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* NATIVE-PRINTING-ADD-FROM-LINE-OF-TEXT-TO-CURRENT-WINDOW */
Object native_printing_add_from_line_of_text_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,text_line,word_spacing,font_map,
	    color_difference,x_scale,y_scale,
	    left_edge_of_line_of_text_in_window,baseline_in_window)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, text_line, word_spacing;
    Object font_map, color_difference, x_scale, y_scale;
    Object left_edge_of_line_of_text_in_window, baseline_in_window;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,298);
    if (EQ(Printing_format,Qnative)) {
	if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	    current_window_1 = Output_window_for_printing_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		    3);
	      type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		      2);
		current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
			1);
		  current_scratchpad_raster_type = ISVREF(Current_window,
			  (SI_Long)23L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			  0);
		    synchronize_background_color_value();
		    result = paint_line_of_text_in_current_window(clipped_left_edge,
			    clipped_top_edge,clipped_right_edge,
			    clipped_bottom_edge,text_line,word_spacing,
			    CAR(font_map),FIXNUM_LOGXOR(color_difference,
			    Current_background_color_value),
			    FIX((SI_Long)0L),FIX((SI_Long)0L),x_scale,
			    y_scale,left_edge_of_line_of_text_in_window,
			    baseline_in_window);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = add_from_line_of_text_to_current_window(subtract_instead_qm,
			clipped_left_edge,clipped_top_edge,
			clipped_right_edge,clipped_bottom_edge,text_line,
			word_spacing,font_map,color_difference,x_scale,
			y_scale,left_edge_of_line_of_text_in_window,
			baseline_in_window);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-SOLID-RECTANGLE-IN-CURRENT-WINDOW */
Object native_printing_paint_solid_rectangle_in_current_window(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    color_value)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, color_value;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,299);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = paint_solid_rectangle_in_current_window(clipped_left_edge,
			clipped_top_edge,clipped_right_edge,
			clipped_bottom_edge,color_value);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-ADD-SOLID-RECTANGLE-TO-CURRENT-WINDOW */
Object native_printing_add_solid_rectangle_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,color_difference)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, color_difference;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,300);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = add_solid_rectangle_to_current_window(subtract_instead_qm,
			clipped_left_edge,clipped_top_edge,
			clipped_right_edge,clipped_bottom_edge,
			color_difference);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-ADD-UPWARD-SLOPING-LINE-TO-CURRENT-WINDOW */
Object native_printing_add_upward_sloping_line_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,color_difference,left_end_x,right_end_y,
	    right_end_x,left_end_y)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, color_difference;
    Object left_end_x, right_end_y, right_end_x, left_end_y;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,301);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = add_upward_sloping_line_to_current_window(subtract_instead_qm,
			clipped_left_edge,clipped_top_edge,
			clipped_right_edge,clipped_bottom_edge,
			color_difference,left_end_x,right_end_y,
			right_end_x,left_end_y);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-ADD-DOWNWARD-SLOPING-LINE-TO-CURRENT-WINDOW */
Object native_printing_add_downward_sloping_line_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,color_difference,left_end_x,left_end_y,
	    right_end_x,right_end_y)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, color_difference;
    Object left_end_x, left_end_y, right_end_x, right_end_y;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,302);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = add_downward_sloping_line_to_current_window(subtract_instead_qm,
			clipped_left_edge,clipped_top_edge,
			clipped_right_edge,clipped_bottom_edge,
			color_difference,left_end_x,left_end_y,right_end_x,
			right_end_y);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-ADD-WIDE-POLYLINE-TO-CURRENT-WINDOW */
Object native_printing_add_wide_polyline_to_current_window(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    color_difference,width,style,dashes,vertices)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, color_difference, width, style, dashes;
    Object vertices;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,303);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = add_wide_polyline_to_current_window(clipped_left_edge,
			clipped_top_edge,clipped_right_edge,
			clipped_bottom_edge,color_difference,width,style,
			dashes,vertices);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-ADD-POLYGON-TO-CURRENT-WINDOW */
Object native_printing_add_polygon_to_current_window(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    line_color_difference,line_width,fill_color_difference,
	    fill_pattern,vertices)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, line_color_difference, line_width;
    Object fill_color_difference, fill_pattern, vertices;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,304);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = add_polygon_to_current_window(clipped_left_edge,
			clipped_top_edge,clipped_right_edge,
			clipped_bottom_edge,line_color_difference,
			line_width,fill_color_difference,fill_pattern,
			vertices);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-ADD-ELLIPSE-TO-CURRENT-WINDOW */
Object native_printing_add_ellipse_to_current_window(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    line_color_difference,line_width,fill_color_difference,
	    fill_pattern,x1,y1_1,x2,y2)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, line_color_difference, line_width;
    Object fill_color_difference, fill_pattern, x1, y1_1, x2, y2;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,305);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = add_ellipse_to_current_window(clipped_left_edge,
			clipped_top_edge,clipped_right_edge,
			clipped_bottom_edge,line_color_difference,
			line_width,fill_color_difference,fill_pattern,x1,
			y1_1,x2,y2);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-COPY-FROM-TILING-PATTERN-TO-CURRENT-WINDOW */
Object native_printing_copy_from_tiling_pattern_to_current_window(left_edge,
	    top_edge,right_edge,bottom_edge,tiling_pattern)
    Object left_edge, top_edge, right_edge, bottom_edge, tiling_pattern;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,306);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = copy_from_tiling_pattern_to_current_window(left_edge,
			top_edge,right_edge,bottom_edge,tiling_pattern);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-IMAGE-IN-CURRENT-WINDOW */
Object native_printing_paint_image_in_current_window(image_data,
	    x_in_window,y_in_window,left,top,right,bottom,x_scale,y_scale,
	    rotation,quality,foreground_color,background_color)
    Object image_data, x_in_window, y_in_window, left, top, right, bottom;
    Object x_scale, y_scale, rotation, quality, foreground_color;
    Object background_color;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,307);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = paint_image_in_current_window(image_data,
			x_in_window,y_in_window,left,top,right,bottom,
			x_scale,y_scale,rotation,quality,foreground_color,
			background_color);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-ICON-BACKGROUND-IMAGE-IN-CURRENT-WINDOW */
Object native_printing_paint_icon_background_image_in_current_window(image_data,
	    x_in_window,y_in_window,draw_area_left,draw_area_top,
	    draw_area_right,draw_area_bottom,x_scale,y_scale,rotation,
	    quality,foreground_color,background_color,
	    image_left_offset_in_ws,image_top_offset_in_ws,
	    rotated_width_in_ws,rotated_height_in_ws)
    Object image_data, x_in_window, y_in_window, draw_area_left, draw_area_top;
    Object draw_area_right, draw_area_bottom, x_scale, y_scale, rotation;
    Object quality, foreground_color, background_color;
    Object image_left_offset_in_ws, image_top_offset_in_ws;
    Object rotated_width_in_ws, rotated_height_in_ws;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(6);
    Object result;

    x_note_fn_call(96,308);
    PUSH_SPECIAL_WITH_SYMBOL(Image_top_offset_in_ws,Qimage_top_offset_in_ws,image_top_offset_in_ws,
	    5);
      PUSH_SPECIAL_WITH_SYMBOL(Image_left_offset_in_ws,Qimage_left_offset_in_ws,image_left_offset_in_ws,
	      4);
	if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	    current_window_1 = Output_window_for_printing_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		    3);
	      type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		      2);
		current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
			1);
		  current_scratchpad_raster_type = ISVREF(Current_window,
			  (SI_Long)23L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			  0);
		    synchronize_background_color_value();
		    result = paint_icon_background_image_in_current_window(image_data,
			    x_in_window,y_in_window,draw_area_left,
			    draw_area_top,draw_area_right,draw_area_bottom,
			    x_scale,y_scale,rotation,quality,
			    foreground_color,background_color,
			    Image_left_offset_in_ws,Image_top_offset_in_ws,
			    rotated_width_in_ws,rotated_height_in_ws);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* NATIVE-PRINTING-UPDATE-GRAPH-DATELINE */
Object native_printing_update_graph_dateline(dateline,erase_dateline,
	    graph_rendering)
    Object dateline, erase_dateline, graph_rendering;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(5);
    Object result;

    x_note_fn_call(96,309);
    PUSH_SPECIAL_WITH_SYMBOL(Erase_dateline,Qerase_dateline,erase_dateline,4);
      if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	  current_window_1 = Output_window_for_printing_qm;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		  3);
	    type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		    2);
	      current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		      1);
		current_scratchpad_raster_type = ISVREF(Current_window,
			(SI_Long)23L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			0);
		  synchronize_background_color_value();
		  result = update_graph_dateline(dateline,Erase_dateline,
			  graph_rendering);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* NATIVE-PRINTING-CLEAR-DATA-CLIPPING-RECTANGLES */
Object native_printing_clear_data_clipping_rectangles()
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,310);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = clear_data_clipping_rectangles();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-UPDATE-GRAPH-DATA-EXTREMA */
Object native_printing_update_graph_data_extrema(left_edge,top_edge,
	    right_edge,bottom_edge)
    Object left_edge, top_edge, right_edge, bottom_edge;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,311);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = update_graph_data_extrema(left_edge,top_edge,
			right_edge,bottom_edge);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES */
Object native_printing_update_ring_raster_for_graph_given_color_values(graph_rendering,
	    number_of_rasters_needed)
    Object graph_rendering, number_of_rasters_needed;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,312);
    if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	current_window_1 = Output_window_for_printing_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		3);
	  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		  2);
	    current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
		    1);
	      current_scratchpad_raster_type = ISVREF(Current_window,
		      (SI_Long)23L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		      0);
		synchronize_background_color_value();
		result = update_ring_raster_for_graph_given_color_values(graph_rendering,
			number_of_rasters_needed);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-ADD-FROM-GRAPH-RENDERING-TO-CURRENT-WINDOW */
Object native_printing_add_from_graph_rendering_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,grid_background_color_value,
	    graph_rendering,left_edge_in_graph_rendering,
	    top_edge_in_graph_rendering,color_value,
	    color_values_for_rasters_qm)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge;
    Object grid_background_color_value, graph_rendering;
    Object left_edge_in_graph_rendering, top_edge_in_graph_rendering;
    Object color_value, color_values_for_rasters_qm;
{
    Object current_window_1, type_of_current_window, current_native_window_qm;
    Object current_scratchpad_raster_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(96,313);
    if (bitmap_printing_p()) {
	if (IFIX(Printing_pass_number) == (SI_Long)2L) {
	    current_window_1 = Output_window_for_printing_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		    3);
	      type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		      2);
		current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
			1);
		  current_scratchpad_raster_type = ISVREF(Current_window,
			  (SI_Long)23L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			  0);
		    synchronize_background_color_value();
		    result = add_from_graph_rendering_to_current_window(subtract_instead_qm,
			    clipped_left_edge,clipped_top_edge,
			    clipped_right_edge,clipped_bottom_edge,
			    grid_background_color_value,graph_rendering,
			    left_edge_in_graph_rendering,
			    top_edge_in_graph_rendering,color_value,
			    color_values_for_rasters_qm);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* NATIVE-PRINTING-PAINT-ICON-ONTO-GRAPH-RASTER */
Object native_printing_paint_icon_onto_graph_raster(icon_rendering,
	    clip_left,clip_top,clip_right,clip_bottom,origin_left,
	    origin_top,color_value)
    Object icon_rendering, clip_left, clip_top, clip_right, clip_bottom;
    Object origin_left, origin_top, color_value;
{
    Object current_background_color_value, native_printing_color_differences;
    Declare_special(2);
    Object result;

    x_note_fn_call(96,314);
    current_background_color_value = FIX((SI_Long)0L);
    native_printing_color_differences = gensym_cons_1(color_value,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Native_printing_color_differences,Qnative_printing_color_differences,native_printing_color_differences,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
	      0);
	add_from_icon_rendering_to_current_window(Nil,FIXNUM_ADD(clip_left,
		Native_printing_icon_x_in_window),FIXNUM_ADD(clip_top,
		Native_printing_icon_y_in_window),FIXNUM_ADD(clip_right,
		Native_printing_icon_x_in_window),FIXNUM_ADD(clip_bottom,
		Native_printing_icon_y_in_window),color_value,
		icon_rendering,FIXNUM_MINUS(clip_left,origin_left),
		FIXNUM_MINUS(clip_top,origin_top),
		Native_printing_color_differences);
	result = reclaim_gensym_list_1(Native_printing_color_differences);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object float_constant_8;    /* 25.4 */

static Object float_constant_9;    /* 2.54 */

static Object float_constant_10;   /* 0.083 */

/* GET-DPI-VALUE-FROM-USER-SETTINGS */
Object get_dpi_value_from_user_settings()
{
    Object scaling, temp, k;
    double dpi, temp_1;

    x_note_fn_call(96,315);
    scaling = printer_workspace_scaling();
    dpi = (double)IFIX(CAR(scaling));
    temp = SECOND(scaling);
    if (EQ(temp,Qinch))
	k = float_constant_1;
    else if (EQ(temp,Qinches))
	k = float_constant_1;
    else if (EQ(temp,Qmillimeter))
	k = float_constant_8;
    else if (EQ(temp,Qmillimeters))
	k = float_constant_8;
    else if (EQ(temp,Qmm))
	k = float_constant_8;
    else if (EQ(temp,Qcentimeter))
	k = float_constant_9;
    else if (EQ(temp,Qcentimeters))
	k = float_constant_9;
    else if (EQ(temp,Qab_cm))
	k = float_constant_9;
    else if (EQ(temp,Qfeet))
	k = float_constant_10;
    else if (EQ(temp,Qfoot))
	k = float_constant_10;
    else
	k = float_constant_1;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(k);
    return l_round(DOUBLE_TO_DOUBLE_FLOAT(dpi * temp_1),_);
}

static Object Qborder;             /* border */

static Object Qframe;              /* frame */

static Object Qframe_style;        /* frame-style */

static Object Qborder_width;       /* border-width */

/* GET-PROPERTY-FOR-PRINTING */
Object get_property_for_printing(workspace,property_1)
    Object workspace, property_1;
{
    Object frame_description_reference, frame_border_width, instruction;
    Object ab_loop_list_, kind, size, ab_loop_list__1, ab_loop_desetq_, temp;
    Object incff_1_arg, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(96,316);
    frame_description_reference = 
	    lookup_frame_description_reference_of_block_qm(workspace);
    frame_border_width = FIX((SI_Long)0L);
    instruction = Nil;
    ab_loop_list_ = ISVREF(frame_description_reference,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    instruction = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(Qborder,FIRST(instruction))) {
	kind = Nil;
	size = Nil;
	ab_loop_list__1 = REST(instruction);
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	kind = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	size = CAR(temp);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (EQ(kind,Qframe)) {
	    incff_1_arg = size;
	    frame_border_width = FIXNUM_ADD(frame_border_width,incff_1_arg);
	}
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    if (ISVREF(Printer_setup,(SI_Long)27L) && ( 
	    !TRUEP(get_lookup_slot_value(workspace,Qframe_style)) || 
	    EQ(frame_description_reference,
	    get_default_workspace_frame_description_reference()))) {
	if (EQ(property_1,Qborder_width))
	    temp = frame_border_width;
	else if (EQ(property_1,Qwidth)) {
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	}
	else if (EQ(property_1,Qheight)) {
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	}
	else
	    temp = Qnil;
    }
    else if (EQ(property_1,Qborder_width))
	temp = frame_border_width;
    else if (EQ(property_1,Qwidth)) {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(frame_border_width);
	gensymed_symbol_3 = IFIX(frame_border_width);
	temp = FIX(gensymed_symbol_1 + gensymed_symbol_2 + gensymed_symbol_3);
    }
    else if (EQ(property_1,Qheight)) {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(frame_border_width);
	gensymed_symbol_3 = IFIX(frame_border_width);
	temp = FIX(gensymed_symbol_1 + gensymed_symbol_2 + gensymed_symbol_3);
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* PRINT-WORKSPACE-AS-IMAGE */
Object print_workspace_as_image(workspace,pathname_qm,format_1,quality)
    Object workspace, pathname_qm, format_1, quality;
{
    Object gensym_window, width, height, dpi, gensymed_symbol;
    Object gensymed_symbol_1, car_new_value, plist;

    x_note_fn_call(96,317);
    gensym_window = System_window;
    width = get_property_for_printing(workspace,Qwidth);
    height = get_property_for_printing(workspace,Qheight);
    dpi = get_dpi_value_from_user_settings();
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)32L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qx_dpi;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = dpi;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qy_dpi;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = dpi;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qphysical_width;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = width;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qphysical_height;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = height;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qwidth;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = width;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qheight;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = height;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qx_offset;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qy_offset;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qleft_margin;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = gensym_list_2(FIX((SI_Long)0L),Qinch);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qtop_margin;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = gensym_list_2(FIX((SI_Long)0L),Qinch);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qright_margin;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = gensym_list_2(FIX((SI_Long)0L),Qinch);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qbottom_margin;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = gensym_list_2(FIX((SI_Long)0L),Qinch);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qprinter;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = format_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qquality;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = quality;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qfrom_page;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = FIX((SI_Long)1L);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qto_page;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = FIX((SI_Long)1L);
    plist = nconc2(gensymed_symbol,pathname_qm ? 
	    gensym_list_2(Qab_pathname,copy_text_string(pathname_qm)) : Nil);
    print_workspace(3,workspace,gensym_window,plist);
    return reclaim_gensym_tree_with_text_strings(plist);
}

static Object Kxor;                /* :xor */

static Object Qx11_window;         /* x11-window */

static Object Qadd_solid_rectangle;  /* add-solid-rectangle */

static Object Qicp;                /* icp */

static Object Qtelewindows;        /* telewindows */

static Object string_constant_165;  /* "Unable to allocate ~dx~dx~d bitmap." */

/* CREATE-BITMAP-FOR-PRINTING */
Object create_bitmap_for_printing(gensym_window,width,height)
    Object gensym_window, width, height;
{
    Object pixmap_qm, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_window_1, drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object temp, current_background_color_value;
    Object current_foreground_color_value, defer_notifications_qm, temp_1;
    Object temp_2, icp_output_port_qm, icp_socket_qm, i_am_alive_info_qm;
    Object icp_output_port_qm_1, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    SI_Long depth;
    SI_Long raster;
    char temp_3;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(30);
    Object result;

    x_note_fn_call(96,318);
    SAVE_STACK();
    depth = win32_window_p(gensym_window) || IFIX(ISVREF(gensym_window,
	    (SI_Long)35L)) > (SI_Long)8L ? (SI_Long)24L : (SI_Long)8L;
    raster = g2ext_create_bigmap(IFIX(ISVREF(gensym_window,(SI_Long)17L)),
	    IFIX(width),IFIX(height),depth);
    if (raster >= (SI_Long)0L) {
	pixmap_qm = make_pixmap_1(width,height,FIX(depth),
		LONG_TO_FIXNUM(raster));
	if (pixmap_qm) {
	    left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
	    top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
	    right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
	    bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
	    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		    29);
	      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		      28);
		PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
			27);
		  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
			  26);
		    current_image_x_scale = FIX((SI_Long)4096L);
		    current_image_y_scale = FIX((SI_Long)4096L);
		    current_x_origin_of_drawing = FIX((SI_Long)0L);
		    current_y_origin_of_drawing = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			    25);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			      24);
			PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				23);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				  22);
			    LOCK(On_window_without_drawing);
			    if (PUSH_UNWIND_PROTECT(1)) {
				current_window_1 = gensym_window;
				PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
					21);
				  drawing_on_window = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
					  20);
				    current_drawing_transfer_mode = 
					    EQ(Current_drawing_transfer_mode,
					    Kxor) ? 
					    Current_drawing_transfer_mode :
					     ISVREF(Current_window,
					    (SI_Long)30L);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
					    19);
				      type_of_current_window = 
					      ISVREF(Current_window,
					      (SI_Long)1L);
				      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
					      18);
					current_native_window_qm = 
						ISVREF(Current_window,
						(SI_Long)17L);
					PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
						17);
					  current_color_map = 
						  ISVREF(Current_window,
						  (SI_Long)20L);
					  PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
						  16);
					    temp = 
						    ISVREF(Current_color_map,
						    (SI_Long)5L);
					    if (temp);
					    else
						temp = 
							map_to_color_value_1(Qwhite);
					    current_background_color_value 
						    = temp;
					    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
						    15);
					      temp = 
						      ISVREF(Current_color_map,
						      (SI_Long)4L);
					      if (temp);
					      else
						  temp = 
							  map_to_color_value_1(Qblack);
					      current_foreground_color_value 
						      = temp;
					      PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
						      14);
						temp = 
							ISVREF(Current_color_map,
							(SI_Long)4L);
						if (temp);
						else
						    temp = 
							    map_to_color_value_1(Qblack);
						Current_background_color_value 
							= temp;
						Current_drawing_transfer_mode 
							= 
							Kpaint_infered_from_xor;
						defer_notifications_qm = T;
						PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
							13);
						  LOCK(On_window_with_drawing);
						  if (PUSH_UNWIND_PROTECT(0)) {
						      drawing_on_window = T;
						      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
							      12);
							if (EQ(Type_of_current_window,
								Qx11_window)) {
							    g2ext_offscreen(IFIX(Current_native_window_qm),
								    IFIX(ISVREF(pixmap_qm,
								    (SI_Long)4L)),
								    (SI_Long)1L);
							    temp = 
								    ISVREF(pixmap_qm,
								    (SI_Long)1L);
							    temp_1 = 
								    ISVREF(pixmap_qm,
								    (SI_Long)2L);
							    temp_2 = 
								    ISVREF(Current_color_map,
								    (SI_Long)5L);
							    if (temp_2);
							    else
								temp_2 = 
									map_to_color_value_1(Qwhite);
							    draw_graphic_element(6,
								    Qadd_solid_rectangle,
								    FIX((SI_Long)0L),
								    FIX((SI_Long)0L),
								    temp,
								    temp_1,
								    temp_2);
							    g2ext_offscreen(IFIX(Current_native_window_qm),
								    (SI_Long)0L,
								    (SI_Long)0L);
							    if (Flush_graphics_immediately_qm)
								sync_graphics_on_current_window();
							}
							else if (EQ(Type_of_current_window,
								Qicp)) {
							    icp_output_port_qm 
								    = 
								    ISVREF(Current_window,
								    (SI_Long)12L);
							    icp_socket_qm 
								    = 
								    icp_output_port_qm 
								    ? 
								    ISVREF(icp_output_port_qm,
								    (SI_Long)2L) 
								    : Qnil;
							    if (icp_socket_qm) 
									{
								i_am_alive_info_qm 
									= 
									ISVREF(icp_socket_qm,
									(SI_Long)24L);
								temp_3 =  
									!TRUEP(i_am_alive_info_qm);
								if (temp_3);
								else
								    temp_3 
									    = 
									     
									    !TRUEP(Do_icp_flow_control_qm);
								if (temp_3);
								else
								    temp_3 
									    = 
									     
									    !TRUEP(ISVREF(i_am_alive_info_qm,
									    (SI_Long)2L));
							    }
							    else
								temp_3 = 
									TRUEP(Nil);
							    if (temp_3) {
								icp_output_port_qm_1 
									= 
									ISVREF(Current_window,
									(SI_Long)12L);
								if (icp_output_port_qm_1 
									&& 
									icp_connection_open_p(ISVREF(icp_output_port_qm_1,
									(SI_Long)2L))) 
									    {
								    current_icp_port 
									    = 
									    icp_output_port_qm_1;
								    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
									    11);
								      current_icp_socket 
									      = 
									      ISVREF(Current_icp_port,
									      (SI_Long)2L);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
									      10);
									temp 
										= 
										IFIX(ISVREF(Current_icp_socket,
										(SI_Long)22L)) 
										>= 
										(SI_Long)17L 
										?
										 
										ISVREF(Current_icp_socket,
										(SI_Long)53L) 
										:
										 
										Nil;
									if (temp);
									else
									    temp 
										    = 
										    EQ(ISVREF(Current_icp_socket,
										    (SI_Long)25L),
										    Qtelewindows) 
										    ?
										     T : Nil;
									disable_resumability 
										= 
										temp;
									PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
										9);
									  number_of_icp_bytes_for_message_series 
										  = 
										  FIX((SI_Long)0L);
									  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
										  8);
									    icp_buffers_for_message_group 
										    = 
										    Nil;
									    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
										    7);
									      icp_buffer_of_start_of_message_series_qm 
										      = 
										      Nil;
									      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
										      6);
										icp_byte_position_of_start_of_message_series_qm 
											= 
											Nil;
										PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
											5);
										  number_of_icp_bytes_to_fill_buffer 
											  = 
											  FIX((SI_Long)0L);
										  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
											  4);
										    current_icp_buffer 
											    = 
											    Nil;
										    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
											    3);
										      current_write_icp_byte_position 
											      = 
											      Nil;
										      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
											      2);
											number_of_icp_bytes_in_message_group 
												= 
												FIX((SI_Long)0L);
											PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
												1);
											  writing_icp_message_group 
												  = 
												  FIXNUM_ADD1(Writing_icp_message_group);
											  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
												  0);
											    gensymed_symbol 
												    = 
												    Nil;
											    gensymed_symbol_1 
												    = 
												    0.0;
											    gensymed_symbol_2 
												    = 
												    0.0;
											    if (Profiling_enabled_qm) 
													{
												gensymed_symbol 
													= 
													T;
												gensymed_symbol_1 
													= 
													DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
													(SI_Long)2L),
													(SI_Long)0L);
												gensymed_symbol_2 
													= 
													g2ext_unix_time_as_float();
												aref_arg_1 
													= 
													ISVREF(Profiling_enabled_qm,
													(SI_Long)2L);
												DFLOAT_ISASET_1(aref_arg_1,
													(SI_Long)0L,
													gensymed_symbol_2);
											    }
											    if (icp_connection_open_p(Current_icp_socket) 
												    && 
												     
												    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
													{
												synchronize_icp_on_window_with_drawing(Current_window,
													Left_edge_of_draw_area,
													Top_edge_of_draw_area,
													Right_edge_of_draw_area,
													Bottom_edge_of_draw_area);
												g2ext_offscreen(IFIX(Current_native_window_qm),
													IFIX(ISVREF(pixmap_qm,
													(SI_Long)4L)),
													(SI_Long)1L);
												temp 
													= 
													ISVREF(pixmap_qm,
													(SI_Long)1L);
												temp_1 
													= 
													ISVREF(pixmap_qm,
													(SI_Long)2L);
												temp_2 
													= 
													ISVREF(Current_color_map,
													(SI_Long)5L);
												if (temp_2);
												else
												    temp_2 
													    = 
													    map_to_color_value_1(Qwhite);
												draw_graphic_element(6,
													Qadd_solid_rectangle,
													FIX((SI_Long)0L),
													FIX((SI_Long)0L),
													temp,
													temp_1,
													temp_2);
												g2ext_offscreen(IFIX(Current_native_window_qm),
													(SI_Long)0L,
													(SI_Long)0L);
												if (Flush_graphics_immediately_qm 
													&& 
													FIXNUM_NE(ISVREF(Current_icp_socket,
													(SI_Long)15L),
													Icp_connection_closed))
												    sync_graphics_on_current_window();
												end_icp_message_group();
											    }
											    if (Profiling_enabled_qm) 
													{
												gensymed_symbol_3 
													= 
													g2ext_unix_time_as_float();
												gensymed_symbol_4 
													= 
													DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
													(SI_Long)2L),
													(SI_Long)0L);
												gensymed_symbol_5 
													= 
													gensymed_symbol_3 
													- 
													gensymed_symbol_4;
												aref_arg_1 
													= 
													ISVREF(Profiling_enabled_qm,
													(SI_Long)6L);
												aref_new_value 
													= 
													gensymed_symbol_5 
													+ 
													DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
													(SI_Long)6L),
													(SI_Long)0L);
												DFLOAT_ISASET_1(aref_arg_1,
													(SI_Long)0L,
													aref_new_value);
												aref_arg_1 
													= 
													ISVREF(Profiling_enabled_qm,
													(SI_Long)2L);
												aref_new_value 
													= 
													gensymed_symbol 
													?
													 
													gensymed_symbol_1 
													+ 
													gensymed_symbol_5 
													+ 
													(gensymed_symbol_4 
													- 
													gensymed_symbol_2) 
													:
													 
													gensymed_symbol_3;
												DFLOAT_ISASET_1(aref_arg_1,
													(SI_Long)0L,
													aref_new_value);
											    }
											  POP_SPECIAL();
											POP_SPECIAL();
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
										POP_SPECIAL();
									      POP_SPECIAL();
									    POP_SPECIAL();
									  POP_SPECIAL();
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								}
							    }
							}
							else if (EQ(Type_of_current_window,
								Qprinter)) {
							    g2ext_offscreen(IFIX(Current_native_window_qm),
								    IFIX(ISVREF(pixmap_qm,
								    (SI_Long)4L)),
								    (SI_Long)1L);
							    temp = 
								    ISVREF(pixmap_qm,
								    (SI_Long)1L);
							    temp_1 = 
								    ISVREF(pixmap_qm,
								    (SI_Long)2L);
							    temp_2 = 
								    ISVREF(Current_color_map,
								    (SI_Long)5L);
							    if (temp_2);
							    else
								temp_2 = 
									map_to_color_value_1(Qwhite);
							    draw_graphic_element(6,
								    Qadd_solid_rectangle,
								    FIX((SI_Long)0L),
								    FIX((SI_Long)0L),
								    temp,
								    temp_1,
								    temp_2);
							    g2ext_offscreen(IFIX(Current_native_window_qm),
								    (SI_Long)0L,
								    (SI_Long)0L);
							}
						      POP_SPECIAL();
						  }
						  POP_UNWIND_PROTECT(0);
						  UNLOCK(On_window_with_drawing);
						  CONTINUE_UNWINDING(0);
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			    }
			    POP_UNWIND_PROTECT(1);
			    UNLOCK(On_window_without_drawing);
			    CONTINUE_UNWINDING(1);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	RESTORE_STACK();
	return VALUES_1(pixmap_qm);
    }
    else {
	notify_user_at_console(4,string_constant_165,width,height,FIX(depth));
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

/* FILETYPE-FOR-PRINT-FORMAT */
Object filetype_for_print_format(format_1)
    Object format_1;
{
    x_note_fn_call(96,319);
    if (EQ(format_1,Qpostscript))
	return VALUES_1(array_constant_7);
    else if (EQ(format_1,Qbitmap))
	return VALUES_1(array_constant_8);
    else
	return VALUES_1(Qnil);
}

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

/* DRAW-IMAGE-PLANE-FOR-PRINTING-A-LITTLE */
Object draw_image_plane_for_printing_a_little(image_plane)
    Object image_plane;
{
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_window_1, drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object temp, current_background_color_value;
    Object current_foreground_color_value, current_drawing_priority;
    Object current_scratchpad_raster_type, current_draw_paper_p;
    Object icp_printing_message_handler_array, icp_output_port_qm;
    Object current_icp_port, current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(35);
    Object result;

    x_note_fn_call(96,320);
    SAVE_STACK();
    left_edge_of_draw_area = ISVREF(Gensym_window_for_printing,(SI_Long)7L);
    top_edge_of_draw_area = ISVREF(Gensym_window_for_printing,(SI_Long)8L);
    right_edge_of_draw_area = ISVREF(Gensym_window_for_printing,(SI_Long)9L);
    bottom_edge_of_draw_area = ISVREF(Gensym_window_for_printing,(SI_Long)10L);
    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
	    34);
      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
	      33);
	PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		32);
	  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		  31);
	    current_image_x_scale = FIX((SI_Long)4096L);
	    current_image_y_scale = FIX((SI_Long)4096L);
	    current_x_origin_of_drawing = FIX((SI_Long)0L);
	    current_y_origin_of_drawing = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		    30);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		      29);
		PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			28);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			  27);
		    LOCK(On_window_without_drawing);
		    if (PUSH_UNWIND_PROTECT(1)) {
			current_window_1 = Gensym_window_for_printing;
			PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
				26);
			  drawing_on_window = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
				  25);
			    current_drawing_transfer_mode = 
				    EQ(Current_drawing_transfer_mode,Kxor) 
				    ? Current_drawing_transfer_mode : 
				    ISVREF(Current_window,(SI_Long)30L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
				    24);
			      type_of_current_window = 
				      ISVREF(Current_window,(SI_Long)1L);
			      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
				      23);
				current_native_window_qm = 
					ISVREF(Current_window,(SI_Long)17L);
				PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
					22);
				  current_color_map = 
					  ISVREF(Current_window,(SI_Long)20L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
					  21);
				    temp = ISVREF(Current_color_map,
					    (SI_Long)5L);
				    if (temp);
				    else
					temp = map_to_color_value_1(Qwhite);
				    current_background_color_value = temp;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
					    20);
				      temp = ISVREF(Current_color_map,
					      (SI_Long)4L);
				      if (temp);
				      else
					  temp = map_to_color_value_1(Qblack);
				      current_foreground_color_value = temp;
				      PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					      19);
					current_drawing_transfer_mode = 
						Kpaint_infered_from_xor;
					PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
						18);
					  current_drawing_priority = 
						  Kdraw_as_late_as_possible;
					  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
						  17);
					    current_scratchpad_raster_type 
						    = Qprinter;
					    current_draw_paper_p = Nil;
					    PUSH_SPECIAL_WITH_SYMBOL(Current_draw_paper_p,Qcurrent_draw_paper_p,current_draw_paper_p,
						    16);
					      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
						      15);
						LOCK(On_window_with_drawing);
						if (PUSH_UNWIND_PROTECT(0)) {
						    drawing_on_window = T;
						    PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
							    14);
						      if (EQ(Printing_format,
							      Qnative) || 
							      EQ(Printing_format,
							      Qbitmap)) {
							  icp_printing_message_handler_array 
								  = 
								  Native_printing_icp_message_handler_array;
							  PUSH_SPECIAL_WITH_SYMBOL(Icp_printing_message_handler_array,Qicp_printing_message_handler_array,icp_printing_message_handler_array,
								  13);
							    temp = 
								    ISVREF(Output_window_for_printing_qm,
								    (SI_Long)1L);
							    if (EQ(temp,
								    Qx11_window)) 
									{
								g2ext_offscreen(IFIX(ISVREF(Output_window_for_printing_qm,
									(SI_Long)17L)),
									IFIX(ISVREF(Bitmap_for_printing_qm,
									(SI_Long)4L)),
									(SI_Long)1L);
								work_on_drawing_current_window();
								g2ext_offscreen(IFIX(ISVREF(Output_window_for_printing_qm,
									(SI_Long)17L)),
									(SI_Long)-1L,
									(SI_Long)0L);
							    }
							    else if (EQ(temp,
								    Qicp)) {
								icp_output_port_qm 
									= 
									ISVREF(Output_window_for_printing_qm,
									(SI_Long)12L);
								if (icp_output_port_qm 
									&& 
									icp_connection_open_p(ISVREF(icp_output_port_qm,
									(SI_Long)2L))) 
									    {
								    current_icp_port 
									    = 
									    icp_output_port_qm;
								    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
									    12);
								      current_icp_socket 
									      = 
									      ISVREF(Current_icp_port,
									      (SI_Long)2L);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
									      11);
									temp 
										= 
										IFIX(ISVREF(Current_icp_socket,
										(SI_Long)22L)) 
										>= 
										(SI_Long)17L 
										?
										 
										ISVREF(Current_icp_socket,
										(SI_Long)53L) 
										:
										 
										Nil;
									if (temp);
									else
									    temp 
										    = 
										    EQ(ISVREF(Current_icp_socket,
										    (SI_Long)25L),
										    Qtelewindows) 
										    ?
										     T : Nil;
									disable_resumability 
										= 
										temp;
									PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
										10);
									  number_of_icp_bytes_for_message_series 
										  = 
										  FIX((SI_Long)0L);
									  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
										  9);
									    icp_buffers_for_message_group 
										    = 
										    Nil;
									    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
										    8);
									      icp_buffer_of_start_of_message_series_qm 
										      = 
										      Nil;
									      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
										      7);
										icp_byte_position_of_start_of_message_series_qm 
											= 
											Nil;
										PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
											6);
										  number_of_icp_bytes_to_fill_buffer 
											  = 
											  FIX((SI_Long)0L);
										  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
											  5);
										    current_icp_buffer 
											    = 
											    Nil;
										    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
											    4);
										      current_write_icp_byte_position 
											      = 
											      Nil;
										      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
											      3);
											number_of_icp_bytes_in_message_group 
												= 
												FIX((SI_Long)0L);
											PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
												2);
											  writing_icp_message_group 
												  = 
												  FIXNUM_ADD1(Writing_icp_message_group);
											  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
												  1);
											    gensymed_symbol 
												    = 
												    Nil;
											    gensymed_symbol_1 
												    = 
												    0.0;
											    gensymed_symbol_2 
												    = 
												    0.0;
											    if (Profiling_enabled_qm) 
													{
												gensymed_symbol 
													= 
													T;
												gensymed_symbol_1 
													= 
													DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
													(SI_Long)2L),
													(SI_Long)0L);
												gensymed_symbol_2 
													= 
													g2ext_unix_time_as_float();
												aref_arg_1 
													= 
													ISVREF(Profiling_enabled_qm,
													(SI_Long)2L);
												DFLOAT_ISASET_1(aref_arg_1,
													(SI_Long)0L,
													gensymed_symbol_2);
											    }
											    if (icp_connection_open_p(Current_icp_socket) 
												    && 
												     
												    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
													{
												current_window_1 
													= 
													Output_window_for_printing_qm;
												PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
													0);
												  synchronize_icp_on_window_with_drawing(Current_window,
													  Left_edge_of_draw_area,
													  Top_edge_of_draw_area,
													  Right_edge_of_draw_area,
													  Bottom_edge_of_draw_area);
												POP_SPECIAL();
												native_printing_begin(Output_window_for_printing_qm);
												work_on_drawing_current_window();
												native_printing_end(Output_window_for_printing_qm);
												end_icp_message_group();
											    }
											    if (Profiling_enabled_qm) 
													{
												gensymed_symbol_3 
													= 
													g2ext_unix_time_as_float();
												gensymed_symbol_4 
													= 
													DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
													(SI_Long)2L),
													(SI_Long)0L);
												gensymed_symbol_5 
													= 
													gensymed_symbol_3 
													- 
													gensymed_symbol_4;
												aref_arg_1 
													= 
													ISVREF(Profiling_enabled_qm,
													(SI_Long)6L);
												aref_new_value 
													= 
													gensymed_symbol_5 
													+ 
													DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
													(SI_Long)6L),
													(SI_Long)0L);
												DFLOAT_ISASET_1(aref_arg_1,
													(SI_Long)0L,
													aref_new_value);
												aref_arg_1 
													= 
													ISVREF(Profiling_enabled_qm,
													(SI_Long)2L);
												aref_new_value 
													= 
													gensymed_symbol 
													?
													 
													gensymed_symbol_1 
													+ 
													gensymed_symbol_5 
													+ 
													(gensymed_symbol_4 
													- 
													gensymed_symbol_2) 
													:
													 
													gensymed_symbol_3;
												DFLOAT_ISASET_1(aref_arg_1,
													(SI_Long)0L,
													aref_new_value);
											    }
											  POP_SPECIAL();
											POP_SPECIAL();
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
										POP_SPECIAL();
									      POP_SPECIAL();
									    POP_SPECIAL();
									  POP_SPECIAL();
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								}
							    }
							  POP_SPECIAL();
						      }
						      else
							  work_on_drawing_current_window();
						    POP_SPECIAL();
						}
						POP_UNWIND_PROTECT(0);
						UNLOCK(On_window_with_drawing);
						CONTINUE_UNWINDING(0);
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		    POP_UNWIND_PROTECT(1);
		    UNLOCK(On_window_without_drawing);
		    CONTINUE_UNWINDING(1);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    result = image_plane_drawing_is_completely_finished_qm(image_plane);
    RESTORE_STACK();
    return result;
}

static Object Qbackground_print_workspace;  /* background-print-workspace */

/* PRINT-WORKSPACE */
Object print_workspace varargs_1(int, n)
{
    Object workspace;
    Object output_window_qm, plist, process_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(96,321);
    INIT_ARGS_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    output_window_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    plist = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    process_qm = make_background_process(4,Qbackground_print_workspace,
	    workspace,output_window_qm,plist);
    if (process_qm) {
	call_background_process(process_qm);
	return schedule_task_for_background_processes();
    }
    else
	return VALUES_1(Nil);
}

/* ARE-THERE-GRAPHS-ON-THIS-WORKSPACE? */
Object are_there_graphs_on_this_workspace_qm(workspace)
    Object workspace;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, frame;
    Object ab_loop_it_, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(96,322);
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    frame = Nil;
    ab_loop_it_ = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    frame = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	ab_loop_it_ = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
    }
    else
	ab_loop_it_ = Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-TRUE-PATHNAME-NAMESTRING-FOR-PRINTING-STREAM */
Object get_true_pathname_namestring_for_printing_stream(printing_stream_qm)
    Object printing_stream_qm;
{
    Object truename_1, temp;

    x_note_fn_call(96,323);
    if (printing_stream_qm) {
	truename_1 = gensym_truename(Printing_stream);
	temp = gensym_namestring_as_text_string(1,truename_1);
	reclaim_gensym_pathname(truename_1);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_background_print_workspace_process_state_block = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_background_print_workspace_process_state_blocks, Qchain_of_available_background_print_workspace_process_state_blocks);

DEFINE_VARIABLE_WITH_SYMBOL(Background_print_workspace_process_state_block_count, Qbackground_print_workspace_process_state_block_count);

Object Chain_of_available_background_print_workspace_process_state_blocks_vector = UNBOUND;

/* BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK-STRUCTURE-MEMORY-USAGE */
Object background_print_workspace_process_state_block_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(96,324);
    temp = Background_print_workspace_process_state_block_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)68L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK-COUNT */
Object outstanding_background_print_workspace_process_state_block_count()
{
    Object def_structure_background_print_workspace_process_state_block_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(96,325);
    gensymed_symbol = 
	    IFIX(Background_print_workspace_process_state_block_count);
    def_structure_background_print_workspace_process_state_block_variable 
	    = 
	    Chain_of_available_background_print_workspace_process_state_blocks;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( 
	    !TRUEP(def_structure_background_print_workspace_process_state_block_variable))
	goto end_loop;
    def_structure_background_print_workspace_process_state_block_variable 
	    = 
	    ISVREF(def_structure_background_print_workspace_process_state_block_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK-1-1 */
Object reclaim_background_print_workspace_process_state_block_1_1(background_print_workspace_process_state_block)
    Object background_print_workspace_process_state_block;
{
    Object temp, svref_arg_2;

    x_note_fn_call(96,326);
    inline_note_reclaim_cons(background_print_workspace_process_state_block,
	    Nil);
    temp = 
	    ISVREF(Chain_of_available_background_print_workspace_process_state_blocks_vector,
	    IFIX(Current_thread_index));
    SVREF(background_print_workspace_process_state_block,FIX((SI_Long)0L)) 
	    = temp;
    temp = 
	    Chain_of_available_background_print_workspace_process_state_blocks_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = background_print_workspace_process_state_block;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK */
Object reclaim_structure_for_background_print_workspace_process_state_block(background_print_workspace_process_state_block)
    Object background_print_workspace_process_state_block;
{
    x_note_fn_call(96,327);
    return reclaim_background_print_workspace_process_state_block_1_1(background_print_workspace_process_state_block);
}

static Object Qg2_defstruct_structure_name_background_print_workspace_process_state_block_g2_struct;  /* g2-defstruct-structure-name::background-print-workspace-process-state-block-g2-struct */

/* MAKE-PERMANENT-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK-STRUCTURE-INTERNAL */
Object make_permanent_background_print_workspace_process_state_block_structure_internal()
{
    Object def_structure_background_print_workspace_process_state_block_variable;
    Object defstruct_g2_background_print_workspace_process_state_block_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(96,328);
    def_structure_background_print_workspace_process_state_block_variable 
	    = Nil;
    atomic_incff_symval(Qbackground_print_workspace_process_state_block_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_background_print_workspace_process_state_block_variable 
		= Nil;
	gensymed_symbol = (SI_Long)68L;
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
	defstruct_g2_background_print_workspace_process_state_block_variable 
		= the_array;
	SVREF(defstruct_g2_background_print_workspace_process_state_block_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_background_print_workspace_process_state_block_g2_struct;
	def_structure_background_print_workspace_process_state_block_variable 
		= 
		defstruct_g2_background_print_workspace_process_state_block_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_background_print_workspace_process_state_block_variable);
}

/* MAKE-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK-1 */
Object make_background_print_workspace_process_state_block_1()
{
    Object def_structure_background_print_workspace_process_state_block_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(96,329);
    def_structure_background_print_workspace_process_state_block_variable 
	    = 
	    ISVREF(Chain_of_available_background_print_workspace_process_state_blocks_vector,
	    IFIX(Current_thread_index));
    if (def_structure_background_print_workspace_process_state_block_variable) 
		{
	svref_arg_1 = 
		Chain_of_available_background_print_workspace_process_state_blocks_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_background_print_workspace_process_state_block_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_background_print_workspace_process_state_block_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_background_print_workspace_process_state_block_g2_struct;
    }
    else
	def_structure_background_print_workspace_process_state_block_variable 
		= 
		make_permanent_background_print_workspace_process_state_block_structure_internal();
    inline_note_allocate_cons(def_structure_background_print_workspace_process_state_block_variable,
	    Nil);
    return VALUES_1(def_structure_background_print_workspace_process_state_block_variable);
}

/* INITIALIZE-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK */
Object initialize_background_print_workspace_process_state_block(workspace,
	    output_window_qm,plist)
    Object workspace, output_window_qm, plist;
{
    Object state_block, workspace_serial_number, temp;
    Object output_window_for_printing_qm, native_printer_information;
    Object paper_size, paper_orientation, paper_size_name, paper_size_info;
    Object paper_margins, actual_paper_width_mf, actual_paper_height_mf;
    Object paper_width_mf, paper_height_mf, paper_left_margin_mf;
    Object paper_top_margin_mf, paper_right_margin_mf, paper_bottom_margin_mf;
    Object left_margin_mf, top_margin_mf, right_margin_mf, bottom_margin_mf;
    Object gensymed_symbol, left, top, right, bottom, window_frame_width;
    Object page_width_mf, page_height_mf;
    Object postscript_units_per_workspace_unit_mf, x_tile_step, y_tile_step;
    Object printing_format, gensym_window_for_printing, printing_stream;
    Object image_plane, blank_page_p, pathname_1, temp_1;
    Object bitmap_for_printing_qm, last_postscript_composite_object_index;
    Object postscript_composite_object_mapping;
    Object postscript_object_mapping_for_icon_renderings;
    Object postscript_computed_variables_mapping;
    Object postscript_printing_icon_renderings;
    Object postscript_object_mapping_for_graph_renderings;
    Object fonts_used_in_print_job, kanji_fonts_used_in_print_job;
    Object fonts_needing_corresponding_kanji_font;
    Object postscript_emitting_definition;
    Object postscript_definition_operation_counter;
    Object printing_icon_current_region_index_qm, printing_pass_number;
    Object printing_pass_is_for_header, emit_postscript_line_length;
    Object initial_tile_offset, number, divisor, ncolumns, nrows, npages;
    Object eps_qm, multipage_legends_p, x_tile_offset, y_tile_offset;
    Object svref_new_value;
    SI_Long workspace_width, workspace_height, page_number, state_1, substate;
    char paper_orientation_is_portrait;
    double arg, arg_1;
    Declare_special(20);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(96,330);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	state_block = make_background_print_workspace_process_state_block_1();
	workspace_serial_number = 
		copy_frame_serial_number(ISVREF(workspace,(SI_Long)3L));
	temp = output_window_qm;
	if (temp);
	else
	    temp = System_window;
	output_window_for_printing_qm = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Output_window_for_printing_qm,Qoutput_window_for_printing_qm,output_window_for_printing_qm,
		19);
	  native_printer_information = output_window_qm && plist ? 
		  compute_native_printer_information(plist) : Qnil;
	  PUSH_SPECIAL_WITH_SYMBOL(Native_printer_information,Qnative_printer_information,native_printer_information,
		  18);
	    paper_size = printer_setup_particular(Qpaper_size);
	    paper_orientation = printer_setup_particular(Qpaper_orientation);
	    paper_orientation_is_portrait = EQ(paper_orientation,Qportrait);
	    paper_size_name = postscript_paper_size_name(paper_size);
	    paper_size_info = postscript_paper_size_info(paper_size);
	    paper_margins = postscript_paper_margins_info(paper_size);
	    actual_paper_width_mf = 
		    postscript_convert_linear_distance_to_postscript_units_mf(1,
		    FIRST(paper_size_info));
	    actual_paper_height_mf = 
		    postscript_convert_linear_distance_to_postscript_units_mf(1,
		    SECOND(paper_size_info));
	    paper_width_mf = paper_orientation_is_portrait ? 
		    actual_paper_width_mf : actual_paper_height_mf;
	    paper_height_mf = paper_orientation_is_portrait ? 
		    actual_paper_height_mf : actual_paper_width_mf;
	    paper_left_margin_mf = 
		    postscript_convert_linear_distance_to_postscript_units_mf(1,
		    FIRST(paper_margins));
	    paper_top_margin_mf = 
		    postscript_convert_linear_distance_to_postscript_units_mf(1,
		    SECOND(paper_margins));
	    paper_right_margin_mf = 
		    postscript_convert_linear_distance_to_postscript_units_mf(1,
		    THIRD(paper_margins));
	    paper_bottom_margin_mf = 
		    postscript_convert_linear_distance_to_postscript_units_mf(1,
		    FOURTH(paper_margins));
	    left_margin_mf = 
		    postscript_convert_linear_distance_to_postscript_units_mf(1,
		    printer_setup_particular(Qleft_margin));
	    top_margin_mf = 
		    postscript_convert_linear_distance_to_postscript_units_mf(1,
		    printer_setup_particular(Qtop_margin));
	    right_margin_mf = 
		    postscript_convert_linear_distance_to_postscript_units_mf(1,
		    printer_setup_particular(Qright_margin));
	    bottom_margin_mf = 
		    postscript_convert_linear_distance_to_postscript_units_mf(1,
		    printer_setup_particular(Qbottom_margin));
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    left = gensymed_symbol;
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    top = gensymed_symbol;
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    right = gensymed_symbol;
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    bottom = gensymed_symbol;
	    workspace_width = IFIX(FIXNUM_MINUS(right,left)) - (SI_Long)6L;
	    workspace_height = IFIX(FIXNUM_MINUS(bottom,top)) - (SI_Long)6L;
	    window_frame_width = get_property_for_printing(workspace,
		    Qborder_width);
	    page_width_mf = 
		    postscript_remove_margins_from_dimension(paper_width_mf,
		    left_margin_mf,right_margin_mf);
	    page_height_mf = 
		    postscript_remove_margins_from_dimension(paper_height_mf,
		    top_margin_mf,bottom_margin_mf);
	    postscript_units_per_workspace_unit_mf = 
		    postscript_compute_workspace_scaling(top,bottom,left,
		    right,page_width_mf,page_height_mf,
		    FIX(workspace_width),FIX(workspace_height),
		    window_frame_width);
	    arg = DFLOAT_ISAREF_1(postscript_units_per_workspace_unit_mf,
		    (SI_Long)0L);
	    arg_1 = 0.0;
	    x_tile_step =  !(arg == arg_1 &&  
		    !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) ? 
		    ltruncate(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(page_width_mf,
		    (SI_Long)0L)),
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(postscript_units_per_workspace_unit_mf,
		    (SI_Long)0L))) : FIX((SI_Long)0L);
	    arg = DFLOAT_ISAREF_1(postscript_units_per_workspace_unit_mf,
		    (SI_Long)0L);
	    arg_1 = 0.0;
	    y_tile_step =  !(arg == arg_1 &&  
		    !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) ? 
		    ltruncate(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(page_height_mf,
		    (SI_Long)0L)),
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(postscript_units_per_workspace_unit_mf,
		    (SI_Long)0L))) : FIX((SI_Long)0L);
	    if (EQ(ISVREF(Output_window_for_printing_qm,(SI_Long)1L),Qicp))
		printing_format = Qnative;
	    else if (generate_bitmap_p(1,plist))
		printing_format = Qbitmap;
	    else
		printing_format = Qpostscript;
	    PUSH_SPECIAL_WITH_SYMBOL(Printing_format,Qprinting_format,printing_format,
		    17);
	      gensym_window_for_printing = 
		      make_gensym_window_for_printing(FIXNUM_ADD(FIXNUM_ADD(x_tile_step,
		      window_frame_width),window_frame_width),
		      FIXNUM_ADD(FIXNUM_ADD(y_tile_step,
		      window_frame_width),window_frame_width));
	      PUSH_SPECIAL_WITH_SYMBOL(Gensym_window_for_printing,Qgensym_window_for_printing,gensym_window_for_printing,
		      16);
		printing_stream = make_printing_stream(Printing_format);
		PUSH_SPECIAL_WITH_SYMBOL(Printing_stream,Qprinting_stream,printing_stream,
			15);
		  image_plane = Nil;
		  blank_page_p = Nil;
		  pathname_1 = 
			  get_true_pathname_namestring_for_printing_stream(Printing_stream);
		  if (EQ(Printing_format,Qbitmap)) {
		      temp_1 = System_window;
		      temp = get_property_for_printing(workspace,Qwidth);
		      bitmap_for_printing_qm = 
			      create_bitmap_for_printing(temp_1,temp,
			      get_property_for_printing(workspace,Qheight));
		  }
		  else
		      bitmap_for_printing_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Bitmap_for_printing_qm,Qbitmap_for_printing_qm,bitmap_for_printing_qm,
			  14);
		    last_postscript_composite_object_index = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Last_postscript_composite_object_index,Qlast_postscript_composite_object_index,last_postscript_composite_object_index,
			    13);
		      postscript_composite_object_mapping = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Postscript_composite_object_mapping,Qpostscript_composite_object_mapping,postscript_composite_object_mapping,
			      12);
			postscript_object_mapping_for_icon_renderings = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Postscript_object_mapping_for_icon_renderings,Qpostscript_object_mapping_for_icon_renderings,postscript_object_mapping_for_icon_renderings,
				11);
			  postscript_computed_variables_mapping = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Postscript_computed_variables_mapping,Qpostscript_computed_variables_mapping,postscript_computed_variables_mapping,
				  10);
			    postscript_printing_icon_renderings = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Postscript_printing_icon_renderings,Qpostscript_printing_icon_renderings,postscript_printing_icon_renderings,
				    9);
			      postscript_object_mapping_for_graph_renderings 
				      = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Postscript_object_mapping_for_graph_renderings,Qpostscript_object_mapping_for_graph_renderings,postscript_object_mapping_for_graph_renderings,
				      8);
				fonts_used_in_print_job = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Fonts_used_in_print_job,Qfonts_used_in_print_job,fonts_used_in_print_job,
					7);
				  kanji_fonts_used_in_print_job = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Kanji_fonts_used_in_print_job,Qkanji_fonts_used_in_print_job,kanji_fonts_used_in_print_job,
					  6);
				    fonts_needing_corresponding_kanji_font 
					    = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Fonts_needing_corresponding_kanji_font,Qfonts_needing_corresponding_kanji_font,fonts_needing_corresponding_kanji_font,
					    5);
				      postscript_emitting_definition = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Postscript_emitting_definition,Qpostscript_emitting_definition,postscript_emitting_definition,
					      4);
					postscript_definition_operation_counter 
						= FIX((SI_Long)0L);
					PUSH_SPECIAL_WITH_SYMBOL(Postscript_definition_operation_counter,Qpostscript_definition_operation_counter,postscript_definition_operation_counter,
						3);
					  printing_icon_current_region_index_qm 
						  = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Printing_icon_current_region_index_qm,Qprinting_icon_current_region_index_qm,printing_icon_current_region_index_qm,
						  2);
					    printing_pass_number = 
						    FIX((SI_Long)1L);
					    PUSH_SPECIAL_WITH_SYMBOL(Printing_pass_number,Qprinting_pass_number,printing_pass_number,
						    1);
					      printing_pass_is_for_header 
						      = Nil;
					      emit_postscript_line_length 
						      = FIX((SI_Long)0L);
					      PUSH_SPECIAL_WITH_SYMBOL(Emit_postscript_line_length,Qemit_postscript_line_length,emit_postscript_line_length,
						      0);
						initial_tile_offset = 
							FIXNUM_NEGATE(window_frame_width);
						number = 
							minus(FIX(workspace_width),
							initial_tile_offset);
						divisor = x_tile_step;
						ncolumns = IFIX(divisor) 
							== (SI_Long)0L ? 
							FIX((SI_Long)0L) : 
							ceiling(number,
							divisor);
						number = 
							minus(FIX(workspace_height),
							initial_tile_offset);
						divisor = y_tile_step;
						nrows = IFIX(divisor) == 
							(SI_Long)0L ? 
							FIX((SI_Long)0L) : 
							ceiling(number,
							divisor);
						npages = 
							FIXNUM_TIMES(nrows,
							ncolumns);
						eps_qm = IFIX(npages) == 
							(SI_Long)1L ? 
							generate_eps_p() : 
							Qnil;
						multipage_legends_p = 
							Postscript_enable_multipage_legends 
							&& IFIX(npages) > 
							(SI_Long)1L ? ( 
							!TRUEP(eps_qm) ? T 
							: Nil) : Qnil;
						page_number = (SI_Long)1L;
						x_tile_offset = 
							initial_tile_offset;
						y_tile_offset = 
							initial_tile_offset;
						state_1 = (SI_Long)0L;
						substate = (SI_Long)0L;
						SVREF(state_block,
							FIX((SI_Long)1L)) 
							= workspace;
						SVREF(state_block,
							FIX((SI_Long)2L)) 
							= 
							workspace_serial_number;
						svref_new_value = 
							Output_window_for_printing_qm;
						SVREF(state_block,
							FIX((SI_Long)3L)) 
							= svref_new_value;
						svref_new_value = 
							Native_printer_information;
						SVREF(state_block,
							FIX((SI_Long)4L)) 
							= svref_new_value;
						SVREF(state_block,
							FIX((SI_Long)5L)) 
							= paper_size;
						SVREF(state_block,
							FIX((SI_Long)6L)) 
							= paper_orientation;
						SVREF(state_block,
							FIX((SI_Long)7L)) 
							= 
							paper_orientation_is_portrait 
							? T : Nil;
						SVREF(state_block,
							FIX((SI_Long)8L)) 
							= paper_size_name;
						SVREF(state_block,
							FIX((SI_Long)9L)) 
							= paper_size_info;
						SVREF(state_block,
							FIX((SI_Long)10L)) 
							= paper_margins;
						SVREF(state_block,
							FIX((SI_Long)11L)) 
							= 
							actual_paper_width_mf;
						SVREF(state_block,
							FIX((SI_Long)12L)) 
							= 
							actual_paper_height_mf;
						SVREF(state_block,
							FIX((SI_Long)13L)) 
							= paper_width_mf;
						SVREF(state_block,
							FIX((SI_Long)14L)) 
							= paper_height_mf;
						SVREF(state_block,
							FIX((SI_Long)15L)) 
							= paper_left_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)16L)) 
							= paper_top_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)17L)) 
							= 
							paper_right_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)18L)) 
							= 
							paper_bottom_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)19L)) 
							= left_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)20L)) 
							= top_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)21L)) 
							= right_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)22L)) 
							= bottom_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)23L)) 
							= left;
						SVREF(state_block,
							FIX((SI_Long)24L)) 
							= top;
						SVREF(state_block,
							FIX((SI_Long)25L)) 
							= right;
						SVREF(state_block,
							FIX((SI_Long)26L)) 
							= bottom;
						ISVREF(state_block,
							(SI_Long)27L) = 
							FIX(workspace_width);
						ISVREF(state_block,
							(SI_Long)28L) = 
							FIX(workspace_height);
						SVREF(state_block,
							FIX((SI_Long)29L)) 
							= window_frame_width;
						SVREF(state_block,
							FIX((SI_Long)30L)) 
							= page_width_mf;
						SVREF(state_block,
							FIX((SI_Long)31L)) 
							= page_height_mf;
						SVREF(state_block,
							FIX((SI_Long)32L)) 
							= 
							postscript_units_per_workspace_unit_mf;
						SVREF(state_block,
							FIX((SI_Long)33L)) 
							= x_tile_step;
						SVREF(state_block,
							FIX((SI_Long)34L)) 
							= y_tile_step;
						svref_new_value = 
							Printing_format;
						SVREF(state_block,
							FIX((SI_Long)35L)) 
							= svref_new_value;
						svref_new_value = 
							Gensym_window_for_printing;
						SVREF(state_block,
							FIX((SI_Long)36L)) 
							= svref_new_value;
						svref_new_value = 
							Printing_stream;
						SVREF(state_block,
							FIX((SI_Long)37L)) 
							= svref_new_value;
						SVREF(state_block,
							FIX((SI_Long)38L)) 
							= image_plane;
						SVREF(state_block,
							FIX((SI_Long)39L)) 
							= blank_page_p;
						SVREF(state_block,
							FIX((SI_Long)40L)) 
							= pathname_1;
						svref_new_value = 
							Bitmap_for_printing_qm;
						SVREF(state_block,
							FIX((SI_Long)41L)) 
							= svref_new_value;
						svref_new_value = 
							Last_postscript_composite_object_index;
						SVREF(state_block,
							FIX((SI_Long)42L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_composite_object_mapping;
						SVREF(state_block,
							FIX((SI_Long)43L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_object_mapping_for_icon_renderings;
						SVREF(state_block,
							FIX((SI_Long)44L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_computed_variables_mapping;
						SVREF(state_block,
							FIX((SI_Long)45L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_printing_icon_renderings;
						SVREF(state_block,
							FIX((SI_Long)46L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_object_mapping_for_graph_renderings;
						SVREF(state_block,
							FIX((SI_Long)47L)) 
							= svref_new_value;
						svref_new_value = 
							Fonts_used_in_print_job;
						SVREF(state_block,
							FIX((SI_Long)48L)) 
							= svref_new_value;
						svref_new_value = 
							Kanji_fonts_used_in_print_job;
						SVREF(state_block,
							FIX((SI_Long)49L)) 
							= svref_new_value;
						svref_new_value = 
							Fonts_needing_corresponding_kanji_font;
						SVREF(state_block,
							FIX((SI_Long)50L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_emitting_definition;
						SVREF(state_block,
							FIX((SI_Long)51L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_definition_operation_counter;
						SVREF(state_block,
							FIX((SI_Long)52L)) 
							= svref_new_value;
						svref_new_value = 
							Printing_icon_current_region_index_qm;
						SVREF(state_block,
							FIX((SI_Long)53L)) 
							= svref_new_value;
						svref_new_value = 
							Printing_pass_number;
						SVREF(state_block,
							FIX((SI_Long)54L)) 
							= svref_new_value;
						SVREF(state_block,
							FIX((SI_Long)55L)) 
							= 
							printing_pass_is_for_header;
						svref_new_value = 
							Emit_postscript_line_length;
						SVREF(state_block,
							FIX((SI_Long)56L)) 
							= svref_new_value;
						SVREF(state_block,
							FIX((SI_Long)57L)) 
							= initial_tile_offset;
						SVREF(state_block,
							FIX((SI_Long)58L)) 
							= ncolumns;
						SVREF(state_block,
							FIX((SI_Long)59L)) 
							= nrows;
						SVREF(state_block,
							FIX((SI_Long)60L)) 
							= npages;
						SVREF(state_block,
							FIX((SI_Long)61L)) 
							= eps_qm;
						SVREF(state_block,
							FIX((SI_Long)62L)) 
							= multipage_legends_p;
						ISVREF(state_block,
							(SI_Long)63L) = 
							FIX(page_number);
						SVREF(state_block,
							FIX((SI_Long)64L)) 
							= x_tile_offset;
						SVREF(state_block,
							FIX((SI_Long)65L)) 
							= y_tile_offset;
						ISVREF(state_block,
							(SI_Long)66L) = 
							FIX(state_1);
						ISVREF(state_block,
							(SI_Long)67L) = 
							FIX(substate);
						temp = state_block;
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

/* RECLAIM-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK */
Object reclaim_background_print_workspace_process_state_block(state_block)
    Object state_block;
{
    Object managed_float, thing, temp;

    x_note_fn_call(96,331);
    reclaim_frame_serial_number(ISVREF(state_block,(SI_Long)2L));
    reclaim_slot_value(ISVREF(state_block,(SI_Long)4L));
    managed_float = ISVREF(state_block,(SI_Long)11L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)12L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)15L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)16L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)17L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)18L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)19L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)20L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)21L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)22L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)30L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)31L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = ISVREF(state_block,(SI_Long)32L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    reclaim_gensym_window_for_printing(ISVREF(state_block,(SI_Long)36L));
    thing = ISVREF(state_block,(SI_Long)40L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	reclaim_wide_string(thing);
    reclaim_printing_list_1(ISVREF(state_block,(SI_Long)43L));
    reclaim_postscript_object_mapping_for_icon_renderings(ISVREF(state_block,
	    (SI_Long)44L));
    reclaim_postscript_computed_variables_mapping(ISVREF(state_block,
	    (SI_Long)45L));
    reclaim_postscript_printing_icon_renderings(ISVREF(state_block,
	    (SI_Long)46L));
    reclaim_printing_list_1(ISVREF(state_block,(SI_Long)47L));
    reclaim_printing_list_1(ISVREF(state_block,(SI_Long)48L));
    reclaim_printing_list_1(ISVREF(state_block,(SI_Long)49L));
    reclaim_printing_list_1(ISVREF(state_block,(SI_Long)50L));
    temp = 
	    reclaim_background_print_workspace_process_state_block_1_1(state_block);
    return VALUES_1(temp);
}

static Object Qexit;               /* exit */

static Object Qinvalid_blocks;     /* invalid-blocks */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qdeleted;            /* deleted */

static Object Qbegin;              /* begin */

static Object Qend;                /* end */

/* WORK-ON-BACKGROUND-PRINT-WORKSPACE */
Object work_on_background_print_workspace(process,state_block)
    Object process, state_block;
{
    volatile Object workspace;
    Object workspace_serial_number, output_window_for_printing_qm;
    Object native_printer_information, paper_size, paper_orientation;
    Object paper_orientation_is_portrait, paper_size_name, paper_size_info;
    Object paper_margins, actual_paper_width_mf, actual_paper_height_mf;
    Object paper_width_mf, paper_height_mf, paper_left_margin_mf;
    Object paper_top_margin_mf, paper_right_margin_mf, paper_bottom_margin_mf;
    Object left_margin_mf, top_margin_mf, right_margin_mf, bottom_margin_mf;
    Object left, top, right, bottom, workspace_width, workspace_height;
    Object window_frame_width, page_width_mf, page_height_mf;
    Object postscript_units_per_workspace_unit_mf, x_tile_step, y_tile_step;
    Object printing_format, gensym_window_for_printing, printing_stream;
    volatile Object image_plane;
    volatile Object blank_page_p;
    Object pathname_1, bitmap_for_printing_qm;
    Object last_postscript_composite_object_index;
    Object postscript_composite_object_mapping;
    Object postscript_object_mapping_for_icon_renderings;
    Object postscript_computed_variables_mapping;
    Object postscript_printing_icon_renderings;
    Object postscript_object_mapping_for_graph_renderings;
    Object fonts_used_in_print_job, kanji_fonts_used_in_print_job;
    Object fonts_needing_corresponding_kanji_font;
    Object postscript_emitting_definition;
    Object postscript_definition_operation_counter;
    Object printing_icon_current_region_index_qm, printing_pass_number;
    Object printing_pass_is_for_header, emit_postscript_line_length;
    Object initial_tile_offset, ncolumns, nrows, npages, eps_qm;
    Object multipage_legends_p;
    volatile Object page_number;
    volatile Object x_tile_offset;
    volatile Object y_tile_offset;
    volatile Object state_1;
    volatile Object substate;
    volatile Object background_process_return_status;
    Object printing_in_progress_p, temp, gensymed_symbol, xa, ya;
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_window_1, drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object current_background_color_value, current_foreground_color_value;
    Object current_drawing_priority, current_scratchpad_raster_type;
    Object current_draw_paper_p, maximum_time_slice_size;
    Object priority_of_next_task, incff_1_arg, svref_new_value;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(41);
    Object result;

    x_note_fn_call(96,332);
    SAVE_STACK();
    workspace = ISVREF(state_block,(SI_Long)1L);
    workspace_serial_number = ISVREF(state_block,(SI_Long)2L);
    output_window_for_printing_qm = ISVREF(state_block,(SI_Long)3L);
    native_printer_information = ISVREF(state_block,(SI_Long)4L);
    paper_size = ISVREF(state_block,(SI_Long)5L);
    paper_orientation = ISVREF(state_block,(SI_Long)6L);
    paper_orientation_is_portrait = ISVREF(state_block,(SI_Long)7L);
    paper_size_name = ISVREF(state_block,(SI_Long)8L);
    paper_size_info = ISVREF(state_block,(SI_Long)9L);
    paper_margins = ISVREF(state_block,(SI_Long)10L);
    actual_paper_width_mf = ISVREF(state_block,(SI_Long)11L);
    actual_paper_height_mf = ISVREF(state_block,(SI_Long)12L);
    paper_width_mf = ISVREF(state_block,(SI_Long)13L);
    paper_height_mf = ISVREF(state_block,(SI_Long)14L);
    paper_left_margin_mf = ISVREF(state_block,(SI_Long)15L);
    paper_top_margin_mf = ISVREF(state_block,(SI_Long)16L);
    paper_right_margin_mf = ISVREF(state_block,(SI_Long)17L);
    paper_bottom_margin_mf = ISVREF(state_block,(SI_Long)18L);
    left_margin_mf = ISVREF(state_block,(SI_Long)19L);
    top_margin_mf = ISVREF(state_block,(SI_Long)20L);
    right_margin_mf = ISVREF(state_block,(SI_Long)21L);
    bottom_margin_mf = ISVREF(state_block,(SI_Long)22L);
    left = ISVREF(state_block,(SI_Long)23L);
    top = ISVREF(state_block,(SI_Long)24L);
    right = ISVREF(state_block,(SI_Long)25L);
    bottom = ISVREF(state_block,(SI_Long)26L);
    workspace_width = ISVREF(state_block,(SI_Long)27L);
    workspace_height = ISVREF(state_block,(SI_Long)28L);
    window_frame_width = ISVREF(state_block,(SI_Long)29L);
    page_width_mf = ISVREF(state_block,(SI_Long)30L);
    page_height_mf = ISVREF(state_block,(SI_Long)31L);
    postscript_units_per_workspace_unit_mf = ISVREF(state_block,(SI_Long)32L);
    x_tile_step = ISVREF(state_block,(SI_Long)33L);
    y_tile_step = ISVREF(state_block,(SI_Long)34L);
    printing_format = ISVREF(state_block,(SI_Long)35L);
    gensym_window_for_printing = ISVREF(state_block,(SI_Long)36L);
    printing_stream = ISVREF(state_block,(SI_Long)37L);
    image_plane = ISVREF(state_block,(SI_Long)38L);
    blank_page_p = ISVREF(state_block,(SI_Long)39L);
    pathname_1 = ISVREF(state_block,(SI_Long)40L);
    bitmap_for_printing_qm = ISVREF(state_block,(SI_Long)41L);
    last_postscript_composite_object_index = ISVREF(state_block,(SI_Long)42L);
    postscript_composite_object_mapping = ISVREF(state_block,(SI_Long)43L);
    postscript_object_mapping_for_icon_renderings = ISVREF(state_block,
	    (SI_Long)44L);
    postscript_computed_variables_mapping = ISVREF(state_block,(SI_Long)45L);
    postscript_printing_icon_renderings = ISVREF(state_block,(SI_Long)46L);
    postscript_object_mapping_for_graph_renderings = ISVREF(state_block,
	    (SI_Long)47L);
    fonts_used_in_print_job = ISVREF(state_block,(SI_Long)48L);
    kanji_fonts_used_in_print_job = ISVREF(state_block,(SI_Long)49L);
    fonts_needing_corresponding_kanji_font = ISVREF(state_block,(SI_Long)50L);
    postscript_emitting_definition = ISVREF(state_block,(SI_Long)51L);
    postscript_definition_operation_counter = ISVREF(state_block,(SI_Long)52L);
    printing_icon_current_region_index_qm = ISVREF(state_block,(SI_Long)53L);
    printing_pass_number = ISVREF(state_block,(SI_Long)54L);
    printing_pass_is_for_header = ISVREF(state_block,(SI_Long)55L);
    emit_postscript_line_length = ISVREF(state_block,(SI_Long)56L);
    initial_tile_offset = ISVREF(state_block,(SI_Long)57L);
    ncolumns = ISVREF(state_block,(SI_Long)58L);
    nrows = ISVREF(state_block,(SI_Long)59L);
    npages = ISVREF(state_block,(SI_Long)60L);
    eps_qm = ISVREF(state_block,(SI_Long)61L);
    multipage_legends_p = ISVREF(state_block,(SI_Long)62L);
    page_number = ISVREF(state_block,(SI_Long)63L);
    x_tile_offset = ISVREF(state_block,(SI_Long)64L);
    y_tile_offset = ISVREF(state_block,(SI_Long)65L);
    state_1 = ISVREF(state_block,(SI_Long)66L);
    substate = ISVREF(state_block,(SI_Long)67L);
    background_process_return_status = Qexit;
    PUSH_SPECIAL_WITH_SYMBOL(Emit_postscript_line_length,Qemit_postscript_line_length,emit_postscript_line_length,
	    40);
      PUSH_SPECIAL_WITH_SYMBOL(Printing_pass_number,Qprinting_pass_number,printing_pass_number,
	      39);
	PUSH_SPECIAL_WITH_SYMBOL(Printing_icon_current_region_index_qm,Qprinting_icon_current_region_index_qm,printing_icon_current_region_index_qm,
		38);
	  PUSH_SPECIAL_WITH_SYMBOL(Postscript_definition_operation_counter,Qpostscript_definition_operation_counter,postscript_definition_operation_counter,
		  37);
	    PUSH_SPECIAL_WITH_SYMBOL(Postscript_emitting_definition,Qpostscript_emitting_definition,postscript_emitting_definition,
		    36);
	      PUSH_SPECIAL_WITH_SYMBOL(Fonts_needing_corresponding_kanji_font,Qfonts_needing_corresponding_kanji_font,fonts_needing_corresponding_kanji_font,
		      35);
		PUSH_SPECIAL_WITH_SYMBOL(Kanji_fonts_used_in_print_job,Qkanji_fonts_used_in_print_job,kanji_fonts_used_in_print_job,
			34);
		  PUSH_SPECIAL_WITH_SYMBOL(Fonts_used_in_print_job,Qfonts_used_in_print_job,fonts_used_in_print_job,
			  33);
		    PUSH_SPECIAL_WITH_SYMBOL(Postscript_object_mapping_for_graph_renderings,Qpostscript_object_mapping_for_graph_renderings,postscript_object_mapping_for_graph_renderings,
			    32);
		      PUSH_SPECIAL_WITH_SYMBOL(Postscript_printing_icon_renderings,Qpostscript_printing_icon_renderings,postscript_printing_icon_renderings,
			      31);
			PUSH_SPECIAL_WITH_SYMBOL(Postscript_computed_variables_mapping,Qpostscript_computed_variables_mapping,postscript_computed_variables_mapping,
				30);
			  PUSH_SPECIAL_WITH_SYMBOL(Postscript_object_mapping_for_icon_renderings,Qpostscript_object_mapping_for_icon_renderings,postscript_object_mapping_for_icon_renderings,
				  29);
			    PUSH_SPECIAL_WITH_SYMBOL(Postscript_composite_object_mapping,Qpostscript_composite_object_mapping,postscript_composite_object_mapping,
				    28);
			      PUSH_SPECIAL_WITH_SYMBOL(Last_postscript_composite_object_index,Qlast_postscript_composite_object_index,last_postscript_composite_object_index,
				      27);
				PUSH_SPECIAL_WITH_SYMBOL(Bitmap_for_printing_qm,Qbitmap_for_printing_qm,bitmap_for_printing_qm,
					26);
				  PUSH_SPECIAL_WITH_SYMBOL(Printing_stream,Qprinting_stream,printing_stream,
					  25);
				    PUSH_SPECIAL_WITH_SYMBOL(Gensym_window_for_printing,Qgensym_window_for_printing,gensym_window_for_printing,
					    24);
				      PUSH_SPECIAL_WITH_SYMBOL(Printing_format,Qprinting_format,printing_format,
					      23);
					PUSH_SPECIAL_WITH_SYMBOL(Native_printer_information,Qnative_printer_information,native_printer_information,
						22);
					  PUSH_SPECIAL_WITH_SYMBOL(Output_window_for_printing_qm,Qoutput_window_for_printing_qm,output_window_for_printing_qm,
						  21);
					    if ( !TRUEP(T))
						background_process_return_status 
							= Qinvalid_blocks;
					    else {
						printing_in_progress_p = T;
						PUSH_SPECIAL_WITH_SYMBOL(Printing_in_progress_p,Qprinting_in_progress_p,printing_in_progress_p,
							20);
						  LOCK(Print_spooling);
						  if (PUSH_UNWIND_PROTECT(1)) {
						      if (EQ(Printing_format,
							      Qpostscript))
							  temp =  
								  !TRUEP(Printing_stream) 
								  ? T : Nil;
						      else if (EQ(Printing_format,
							      Qbitmap)) {
							  temp =  
								  !TRUEP(Printing_stream) 
								  ? T : Nil;
							  if (temp);
							  else
							      temp =  
								      !TRUEP(Bitmap_for_printing_qm) 
								      ? T :
								       Nil;
						      }
						      else
							  temp = Qnil;
						      if (temp) {
							  printing_notification(Qerror,
								  workspace,
								  pathname_1);
							  background_process_return_status 
								  = Qexit;
							  goto end_background_process;
						      }
						      gensymed_symbol = 
							      ISVREF(workspace,
							      (SI_Long)3L);
						      temp_1 = 
							      SIMPLE_VECTOR_P(workspace) 
							      ? 
							      EQ(ISVREF(workspace,
							      (SI_Long)1L),
							      Qavailable_frame_vector) 
							      : TRUEP(Qnil);
						      if (temp_1);
						      else
							  temp_1 = 
								  FIXNUMP(gensymed_symbol) 
								  ? 
								  IFIX(gensymed_symbol) 
								  == 
								  (SI_Long)-1L 
								  : TRUEP(Nil);
						      if (temp_1);
						      else if (FIXNUMP(workspace_serial_number))
							  temp_1 = 
								  FIXNUMP(gensymed_symbol) 
								  ? 
								  FIXNUM_LT(workspace_serial_number,
								  gensymed_symbol) 
								  : TRUEP(T);
						      else if (FIXNUMP(gensymed_symbol))
							  temp_1 = TRUEP(Nil);
						      else {
							  xa = 
								  M_CAR(workspace_serial_number);
							  ya = 
								  M_CAR(gensymed_symbol);
							  temp_1 = 
								  FIXNUM_LT(xa,
								  ya);
							  if (temp_1);
							  else
							      temp_1 = 
								      FIXNUM_EQ(xa,
								      ya) ?
								       
								      FIXNUM_LT(M_CDR(workspace_serial_number),
								      M_CDR(gensymed_symbol)) 
								      : 
								      TRUEP(Qnil);
						      }
						      if (temp_1) {
							  printing_notification(Qdeleted,
								  workspace,
								  pathname_1);
							  workspace = Nil;
							  if (Printing_stream)
							      state_1 = 
								      FIX((SI_Long)5L);
							  else {
							      background_process_return_status 
								      = Qexit;
							      goto end_background_process;
							  }
						      }
						      if (IFIX(state_1) == 
							      (SI_Long)0L) {
							  printing_notification(Qbegin,
								  workspace,
								  pathname_1);
							  left_edge_of_draw_area 
								  = 
								  ISVREF(Gensym_window_for_printing,
								  (SI_Long)7L);
							  top_edge_of_draw_area 
								  = 
								  ISVREF(Gensym_window_for_printing,
								  (SI_Long)8L);
							  right_edge_of_draw_area 
								  = 
								  ISVREF(Gensym_window_for_printing,
								  (SI_Long)9L);
							  bottom_edge_of_draw_area 
								  = 
								  ISVREF(Gensym_window_for_printing,
								  (SI_Long)10L);
							  PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
								  19);
							    PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
								    18);
							      PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
								      17);
								PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
									16);
								  current_image_x_scale 
									  = 
									  FIX((SI_Long)4096L);
								  current_image_y_scale 
									  = 
									  FIX((SI_Long)4096L);
								  current_x_origin_of_drawing 
									  = 
									  FIX((SI_Long)0L);
								  current_y_origin_of_drawing 
									  = 
									  FIX((SI_Long)0L);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
									  15);
								    PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
									    14);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
									      13);
									PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
										12);
									  LOCK(On_window_without_drawing);
									  if (PUSH_UNWIND_PROTECT(0)) 
										      {
									      current_window_1 
										      = 
										      Gensym_window_for_printing;
									      PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
										      11);
										drawing_on_window 
											= 
											Nil;
										PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
											10);
										  current_drawing_transfer_mode 
											  = 
											  EQ(Current_drawing_transfer_mode,
											  Kxor) 
											  ?
											   
											  Current_drawing_transfer_mode 
											  :
											   
											  ISVREF(Current_window,
											  (SI_Long)30L);
										  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
											  9);
										    type_of_current_window 
											    = 
											    ISVREF(Current_window,
											    (SI_Long)1L);
										    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
											    8);
										      current_native_window_qm 
											      = 
											      ISVREF(Current_window,
											      (SI_Long)17L);
										      PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
											      7);
											current_color_map 
												= 
												ISVREF(Current_window,
												(SI_Long)20L);
											PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
												6);
											  temp 
												  = 
												  ISVREF(Current_color_map,
												  (SI_Long)5L);
											  if (temp);
											  else
											      temp 
												      = 
												      map_to_color_value_1(Qwhite);
											  current_background_color_value 
												  = 
												  temp;
											  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
												  5);
											    temp 
												    = 
												    ISVREF(Current_color_map,
												    (SI_Long)4L);
											    if (temp);
											    else
												temp 
													= 
													map_to_color_value_1(Qblack);
											    current_foreground_color_value 
												    = 
												    temp;
											    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
												    4);
											      current_drawing_transfer_mode 
												      = 
												      Kpaint_infered_from_xor;
											      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
												      3);
												current_drawing_priority 
													= 
													Kdraw_as_late_as_possible;
												PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
													2);
												  current_scratchpad_raster_type 
													  = 
													  Qprinter;
												  current_draw_paper_p 
													  = 
													  Nil;
												  PUSH_SPECIAL_WITH_SYMBOL(Current_draw_paper_p,Qcurrent_draw_paper_p,current_draw_paper_p,
													  1);
												    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
													    0);
												      if (EQ(Printing_format,
													      Qpostscript)) 
														  {
													  emit_postscript_job_header(workspace,
														  paper_size_name,
														  npages,
														  eps_qm,
														  FIX(IFIX(FIXNUM_MINUS(right,
														  left)) 
														  - 
														  (SI_Long)-15L),
														  FIX(IFIX(FIXNUM_MINUS(bottom,
														  top)) 
														  - 
														  (SI_Long)-15L),
														  postscript_units_per_workspace_unit_mf,
														  paper_orientation,
														  actual_paper_width_mf,
														  actual_paper_height_mf,
														  left_margin_mf,
														  top_margin_mf,
														  right_margin_mf,
														  bottom_margin_mf,
														  paper_left_margin_mf,
														  paper_top_margin_mf,
														  paper_right_margin_mf,
														  paper_bottom_margin_mf);
													  emit_postscript_prolog(paper_size,
														  eps_qm);
												      }
												      make_or_revise_window(Gensym_window_for_printing,
													      FIX((SI_Long)0L),
													      FIX((SI_Long)0L),
													      FIXNUM_ADD(FIXNUM_ADD(workspace_width,
													      window_frame_width),
													      window_frame_width),
													      FIXNUM_ADD(FIXNUM_ADD(workspace_height,
													      window_frame_width),
													      window_frame_width),
													      Nil,
													      Nil,
													      Nil);
												      lay_out_window(Gensym_window_for_printing);
												    POP_SPECIAL();
												  POP_SPECIAL();
												POP_SPECIAL();
											      POP_SPECIAL();
											    POP_SPECIAL();
											  POP_SPECIAL();
											POP_SPECIAL();
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
										POP_SPECIAL();
									      POP_SPECIAL();
									  }
									  POP_UNWIND_PROTECT(0);
									  UNLOCK(On_window_without_drawing);
									  CONTINUE_UNWINDING(0);
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							    POP_SPECIAL();
							  POP_SPECIAL();
							  state_1 = 
								  FIXNUM_ADD1(state_1);
							  if (time_slice_expired_p()) 
								      {
							      background_process_return_status 
								      = 
								      Qreturn;
							      goto end_background_process;
							  }
						      }
						      if (IFIX(state_1) == 
							      (SI_Long)1L) {
							  if (EQ(Printing_format,
								  Qpostscript)) 
								      {
							      left_edge_of_draw_area 
								      = 
								      ISVREF(Gensym_window_for_printing,
								      (SI_Long)7L);
							      top_edge_of_draw_area 
								      = 
								      ISVREF(Gensym_window_for_printing,
								      (SI_Long)8L);
							      right_edge_of_draw_area 
								      = 
								      ISVREF(Gensym_window_for_printing,
								      (SI_Long)9L);
							      bottom_edge_of_draw_area 
								      = 
								      ISVREF(Gensym_window_for_printing,
								      (SI_Long)10L);
							      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
								      19);
								PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
									18);
								  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
									  17);
								    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
									    16);
								      current_image_x_scale 
									      = 
									      FIX((SI_Long)4096L);
								      current_image_y_scale 
									      = 
									      FIX((SI_Long)4096L);
								      current_x_origin_of_drawing 
									      = 
									      FIX((SI_Long)0L);
								      current_y_origin_of_drawing 
									      = 
									      FIX((SI_Long)0L);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
									      15);
									PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
										14);
									  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
										  13);
									    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
										    12);
									      LOCK(On_window_without_drawing);
									      if (PUSH_UNWIND_PROTECT(0)) 
											  {
										  current_window_1 
											  = 
											  Gensym_window_for_printing;
										  PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
											  11);
										    drawing_on_window 
											    = 
											    Nil;
										    PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
											    10);
										      current_drawing_transfer_mode 
											      = 
											      EQ(Current_drawing_transfer_mode,
											      Kxor) 
											      ?
											       
											      Current_drawing_transfer_mode 
											      :
											       
											      ISVREF(Current_window,
											      (SI_Long)30L);
										      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
											      9);
											type_of_current_window 
												= 
												ISVREF(Current_window,
												(SI_Long)1L);
											PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
												8);
											  current_native_window_qm 
												  = 
												  ISVREF(Current_window,
												  (SI_Long)17L);
											  PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
												  7);
											    current_color_map 
												    = 
												    ISVREF(Current_window,
												    (SI_Long)20L);
											    PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
												    6);
											      temp 
												      = 
												      ISVREF(Current_color_map,
												      (SI_Long)5L);
											      if (temp);
											      else
												  temp 
													  = 
													  map_to_color_value_1(Qwhite);
											      current_background_color_value 
												      = 
												      temp;
											      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
												      5);
												temp 
													= 
													ISVREF(Current_color_map,
													(SI_Long)4L);
												if (temp);
												else
												    temp 
													    = 
													    map_to_color_value_1(Qblack);
												current_foreground_color_value 
													= 
													temp;
												PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
													4);
												  current_drawing_transfer_mode 
													  = 
													  Kpaint_infered_from_xor;
												  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
													  3);
												    current_drawing_priority 
													    = 
													    Kdraw_as_late_as_possible;
												    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
													    2);
												      current_scratchpad_raster_type 
													      = 
													      Qprinter;
												      current_draw_paper_p 
													      = 
													      Nil;
												      PUSH_SPECIAL_WITH_SYMBOL(Current_draw_paper_p,Qcurrent_draw_paper_p,current_draw_paper_p,
													      1);
													PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
														0);
													  image_plane 
														  = 
														  setup_image_plane_for_printing(workspace,
														  x_tile_offset,
														  y_tile_offset);
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												  POP_SPECIAL();
												POP_SPECIAL();
											      POP_SPECIAL();
											    POP_SPECIAL();
											  POP_SPECIAL();
											POP_SPECIAL();
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
									      }
									      POP_UNWIND_PROTECT(0);
									      UNLOCK(On_window_without_drawing);
									      CONTINUE_UNWINDING(0);
									    POP_SPECIAL();
									  POP_SPECIAL();
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							  }
							  state_1 = 
								  FIXNUM_ADD1(state_1);
							  if (time_slice_expired_p()) 
								      {
							      background_process_return_status 
								      = 
								      Qreturn;
							      goto end_background_process;
							  }
						      }
						      if (IFIX(state_1) == 
							      (SI_Long)2L) {
							  if ( 
								  !EQ(Printing_format,
								  Qpostscript)) 
								      {
							      if (are_there_graphs_on_this_workspace_qm(workspace))
								  bogus_preflight_from_printing_to_graphs(workspace);
							      state_1 = 
								      FIXNUM_ADD1(state_1);
							  }
							  else if (are_there_graphs_on_this_workspace_qm(workspace)) 
								      {
							      bogus_preflight_from_printing_to_graphs(workspace);
							      maximum_time_slice_size 
								      = 
								      Most_positive_fixnum;
							      priority_of_next_task 
								      = 
								      Most_positive_fixnum;
							      PUSH_SPECIAL_WITH_SYMBOL(Priority_of_next_task,Qpriority_of_next_task,priority_of_next_task,
								      1);
								PUSH_SPECIAL_WITH_SYMBOL(Maximum_time_slice_size,Qmaximum_time_slice_size,maximum_time_slice_size,
									0);
								  draw_image_plane_for_printing_a_little(image_plane);
								  state_1 
									  = 
									  FIXNUM_ADD1(state_1);
								POP_SPECIAL();
							      POP_SPECIAL();
							  }
							  else {
							    next_loop:
							      if ( 
								      !(IFIX(state_1) 
								      == 
								      (SI_Long)2L))
								  goto end_loop;
							      if (draw_image_plane_for_printing_a_little(image_plane))
								  state_1 
									  = 
									  FIXNUM_ADD1(state_1);
							      if (time_slice_expired_p()) 
									  {
								  background_process_return_status 
									  = 
									  Qreturn;
								  goto end_background_process;
							      }
							      goto next_loop;
							    end_loop:;
							  }
						      }
						      if (IFIX(state_1) == 
							      (SI_Long)3L) {
							  left_edge_of_draw_area 
								  = 
								  ISVREF(Gensym_window_for_printing,
								  (SI_Long)7L);
							  top_edge_of_draw_area 
								  = 
								  ISVREF(Gensym_window_for_printing,
								  (SI_Long)8L);
							  right_edge_of_draw_area 
								  = 
								  ISVREF(Gensym_window_for_printing,
								  (SI_Long)9L);
							  bottom_edge_of_draw_area 
								  = 
								  ISVREF(Gensym_window_for_printing,
								  (SI_Long)10L);
							  PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
								  19);
							    PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
								    18);
							      PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
								      17);
								PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
									16);
								  current_image_x_scale 
									  = 
									  FIX((SI_Long)4096L);
								  current_image_y_scale 
									  = 
									  FIX((SI_Long)4096L);
								  current_x_origin_of_drawing 
									  = 
									  FIX((SI_Long)0L);
								  current_y_origin_of_drawing 
									  = 
									  FIX((SI_Long)0L);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
									  15);
								    PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
									    14);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
									      13);
									PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
										12);
									  LOCK(On_window_without_drawing);
									  if (PUSH_UNWIND_PROTECT(0)) 
										      {
									      current_window_1 
										      = 
										      Gensym_window_for_printing;
									      PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
										      11);
										drawing_on_window 
											= 
											Nil;
										PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
											10);
										  current_drawing_transfer_mode 
											  = 
											  EQ(Current_drawing_transfer_mode,
											  Kxor) 
											  ?
											   
											  Current_drawing_transfer_mode 
											  :
											   
											  ISVREF(Current_window,
											  (SI_Long)30L);
										  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
											  9);
										    type_of_current_window 
											    = 
											    ISVREF(Current_window,
											    (SI_Long)1L);
										    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
											    8);
										      current_native_window_qm 
											      = 
											      ISVREF(Current_window,
											      (SI_Long)17L);
										      PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
											      7);
											current_color_map 
												= 
												ISVREF(Current_window,
												(SI_Long)20L);
											PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
												6);
											  temp 
												  = 
												  ISVREF(Current_color_map,
												  (SI_Long)5L);
											  if (temp);
											  else
											      temp 
												      = 
												      map_to_color_value_1(Qwhite);
											  current_background_color_value 
												  = 
												  temp;
											  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
												  5);
											    temp 
												    = 
												    ISVREF(Current_color_map,
												    (SI_Long)4L);
											    if (temp);
											    else
												temp 
													= 
													map_to_color_value_1(Qblack);
											    current_foreground_color_value 
												    = 
												    temp;
											    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
												    4);
											      current_drawing_transfer_mode 
												      = 
												      Kpaint_infered_from_xor;
											      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
												      3);
												current_drawing_priority 
													= 
													Kdraw_as_late_as_possible;
												PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
													2);
												  current_scratchpad_raster_type 
													  = 
													  Qprinter;
												  current_draw_paper_p 
													  = 
													  Nil;
												  PUSH_SPECIAL_WITH_SYMBOL(Current_draw_paper_p,Qcurrent_draw_paper_p,current_draw_paper_p,
													  1);
												    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
													    0);
												      make_or_revise_window(Gensym_window_for_printing,
													      FIX((SI_Long)0L),
													      FIX((SI_Long)0L),
													      FIXNUM_ADD(FIXNUM_ADD(x_tile_step,
													      window_frame_width),
													      window_frame_width),
													      FIXNUM_ADD(FIXNUM_ADD(y_tile_step,
													      window_frame_width),
													      window_frame_width),
													      Nil,
													      Nil,
													      Nil);
												      lay_out_window(Gensym_window_for_printing);
												    POP_SPECIAL();
												  POP_SPECIAL();
												POP_SPECIAL();
											      POP_SPECIAL();
											    POP_SPECIAL();
											  POP_SPECIAL();
											POP_SPECIAL();
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
										POP_SPECIAL();
									      POP_SPECIAL();
									  }
									  POP_UNWIND_PROTECT(0);
									  UNLOCK(On_window_without_drawing);
									  CONTINUE_UNWINDING(0);
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							    POP_SPECIAL();
							  POP_SPECIAL();
							  start_document(workspace,
								  left,top,
								  right,
								  bottom);
							  if (EQ(Printing_format,
								  Qpostscript)) 
								      {
							      emit_print_job_specific_font_definitions();
							      emit_postscript_page_layout(paper_size_name,
								      postscript_units_per_workspace_unit_mf,
								      paper_orientation,
								      actual_paper_width_mf,
								      actual_paper_height_mf,
								      left_margin_mf,
								      top_margin_mf,
								      right_margin_mf,
								      bottom_margin_mf,
								      paper_left_margin_mf,
								      paper_top_margin_mf,
								      paper_right_margin_mf,
								      paper_bottom_margin_mf);
							  }
							  Printing_pass_number 
								  = 
								  FIX((SI_Long)2L);
							  state_1 = 
								  FIXNUM_ADD1(state_1);
							  if (time_slice_expired_p()) 
								      {
							      background_process_return_status 
								      = 
								      Qreturn;
							      goto end_background_process;
							  }
						      }
						      if (IFIX(state_1) == 
							      (SI_Long)4L) {
							next_loop_1:
							  if ( 
								  !(IFIX(state_1) 
								  == 
								  (SI_Long)4L))
							      goto end_loop_1;
							  if (IFIX(substate) 
								  == 
								  (SI_Long)0L) 
								      {
							      left_edge_of_draw_area 
								      = 
								      ISVREF(Gensym_window_for_printing,
								      (SI_Long)7L);
							      top_edge_of_draw_area 
								      = 
								      ISVREF(Gensym_window_for_printing,
								      (SI_Long)8L);
							      right_edge_of_draw_area 
								      = 
								      ISVREF(Gensym_window_for_printing,
								      (SI_Long)9L);
							      bottom_edge_of_draw_area 
								      = 
								      ISVREF(Gensym_window_for_printing,
								      (SI_Long)10L);
							      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
								      19);
								PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
									18);
								  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
									  17);
								    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
									    16);
								      current_image_x_scale 
									      = 
									      FIX((SI_Long)4096L);
								      current_image_y_scale 
									      = 
									      FIX((SI_Long)4096L);
								      current_x_origin_of_drawing 
									      = 
									      FIX((SI_Long)0L);
								      current_y_origin_of_drawing 
									      = 
									      FIX((SI_Long)0L);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
									      15);
									PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
										14);
									  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
										  13);
									    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
										    12);
									      LOCK(On_window_without_drawing);
									      if (PUSH_UNWIND_PROTECT(0)) 
											  {
										  current_window_1 
											  = 
											  Gensym_window_for_printing;
										  PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
											  11);
										    drawing_on_window 
											    = 
											    Nil;
										    PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
											    10);
										      current_drawing_transfer_mode 
											      = 
											      EQ(Current_drawing_transfer_mode,
											      Kxor) 
											      ?
											       
											      Current_drawing_transfer_mode 
											      :
											       
											      ISVREF(Current_window,
											      (SI_Long)30L);
										      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
											      9);
											type_of_current_window 
												= 
												ISVREF(Current_window,
												(SI_Long)1L);
											PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
												8);
											  current_native_window_qm 
												  = 
												  ISVREF(Current_window,
												  (SI_Long)17L);
											  PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
												  7);
											    current_color_map 
												    = 
												    ISVREF(Current_window,
												    (SI_Long)20L);
											    PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
												    6);
											      temp 
												      = 
												      ISVREF(Current_color_map,
												      (SI_Long)5L);
											      if (temp);
											      else
												  temp 
													  = 
													  map_to_color_value_1(Qwhite);
											      current_background_color_value 
												      = 
												      temp;
											      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
												      5);
												temp 
													= 
													ISVREF(Current_color_map,
													(SI_Long)4L);
												if (temp);
												else
												    temp 
													    = 
													    map_to_color_value_1(Qblack);
												current_foreground_color_value 
													= 
													temp;
												PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
													4);
												  current_drawing_transfer_mode 
													  = 
													  Kpaint_infered_from_xor;
												  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
													  3);
												    current_drawing_priority 
													    = 
													    Kdraw_as_late_as_possible;
												    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
													    2);
												      current_scratchpad_raster_type 
													      = 
													      Qprinter;
												      current_draw_paper_p 
													      = 
													      Nil;
												      PUSH_SPECIAL_WITH_SYMBOL(Current_draw_paper_p,Qcurrent_draw_paper_p,current_draw_paper_p,
													      1);
													PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
														0);
													  image_plane 
														  = 
														  setup_image_plane_for_printing(workspace,
														  x_tile_offset,
														  y_tile_offset);
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												  POP_SPECIAL();
												POP_SPECIAL();
											      POP_SPECIAL();
											    POP_SPECIAL();
											  POP_SPECIAL();
											POP_SPECIAL();
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
									      }
									      POP_UNWIND_PROTECT(0);
									      UNLOCK(On_window_without_drawing);
									      CONTINUE_UNWINDING(0);
									    POP_SPECIAL();
									  POP_SPECIAL();
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							      if (ISVREF(Printer_setup,
								      (SI_Long)27L)) 
									  {
								  blank_page_p 
									  = 
									   
									  !TRUEP(image_plane_has_drawing_in_window_p(image_plane)) 
									  ?
									   T : Nil;
								  temp_1 = 
									  TRUEP(blank_page_p);
							      }
							      else
								  temp_1 = 
									  TRUEP(Nil);
							      if (temp_1)
								  substate 
									  = 
									  FIX((SI_Long)3L);
							      else
								  substate 
									  = 
									  FIXNUM_ADD1(substate);
							  }
							  if (IFIX(substate) 
								  == 
								  (SI_Long)1L) 
								      {
							      start_page(page_number,
								      nrows,
								      ncolumns,
								      left_margin_mf,
								      top_margin_mf,
								      right_margin_mf,
								      bottom_margin_mf,
								      paper_left_margin_mf,
								      paper_top_margin_mf,
								      paper_right_margin_mf,
								      paper_bottom_margin_mf,
								      postscript_units_per_workspace_unit_mf,
								      x_tile_offset,
								      y_tile_offset,
								      x_tile_step,
								      y_tile_step,
								      multipage_legends_p,
								      blank_page_p);
							      substate = 
								      FIXNUM_ADD1(substate);
							      if (time_slice_expired_p()) 
									  {
								  background_process_return_status 
									  = 
									  Qreturn;
								  goto end_background_process;
							      }
							  }
							  if (IFIX(substate) 
								  == 
								  (SI_Long)2L) 
								      {
							    next_loop_2:
							      if ( 
								      !(IFIX(substate) 
								      == 
								      (SI_Long)2L))
								  goto end_loop_2;
							      if (draw_image_plane_for_printing_a_little(image_plane)) 
									  {
								  end_page();
								  substate 
									  = 
									  FIXNUM_ADD1(substate);
							      }
							      if (time_slice_expired_p()) 
									  {
								  background_process_return_status 
									  = 
									  Qreturn;
								  goto end_background_process;
							      }
							      goto next_loop_2;
							    end_loop_2:;
							  }
							  if (IFIX(substate) 
								  == 
								  (SI_Long)3L) 
								      {
							      page_number 
								      = 
								      FIXNUM_ADD1(page_number);
							      incff_1_arg 
								      = 
								      x_tile_step;
							      x_tile_offset 
								      = 
								      FIXNUM_ADD(x_tile_offset,
								      incff_1_arg);
							      if (FIXNUM_LT(workspace_width,
								      x_tile_offset)) 
									  {
								  x_tile_offset 
									  = 
									  initial_tile_offset;
								  y_tile_offset 
									  = 
									  FIXNUM_ADD(y_tile_offset,
									  y_tile_step);
							      }
							      if (FIXNUM_GT(y_tile_offset,
								      workspace_height))
								  state_1 
									  = 
									  FIXNUM_ADD1(state_1);
							      substate = 
								      FIX((SI_Long)0L);
							      if (time_slice_expired_p()) 
									  {
								  background_process_return_status 
									  = 
									  Qreturn;
								  goto end_background_process;
							      }
							  }
							  goto next_loop_1;
							end_loop_1:;
						      }
						      if (IFIX(state_1) == 
							      (SI_Long)5L) {
							  end_document(page_number);
							  if (Printing_stream)
							      close_printing_stream(Printing_stream);
							  printing_notification(Qend,
								  workspace,
								  pathname_1);
						      }
						    end_background_process:;
						  }
						  POP_UNWIND_PROTECT(1);
						  UNLOCK(Print_spooling);
						  CONTINUE_UNWINDING(1);
						POP_SPECIAL();
					    }
					    if (EQ(background_process_return_status,
						    Qreturn)) {
						SVREF(state_block,
							FIX((SI_Long)1L)) 
							= workspace;
						SVREF(state_block,
							FIX((SI_Long)2L)) 
							= 
							workspace_serial_number;
						svref_new_value = 
							Output_window_for_printing_qm;
						SVREF(state_block,
							FIX((SI_Long)3L)) 
							= svref_new_value;
						svref_new_value = 
							Native_printer_information;
						SVREF(state_block,
							FIX((SI_Long)4L)) 
							= svref_new_value;
						SVREF(state_block,
							FIX((SI_Long)5L)) 
							= paper_size;
						SVREF(state_block,
							FIX((SI_Long)6L)) 
							= paper_orientation;
						SVREF(state_block,
							FIX((SI_Long)7L)) 
							= 
							paper_orientation_is_portrait;
						SVREF(state_block,
							FIX((SI_Long)8L)) 
							= paper_size_name;
						SVREF(state_block,
							FIX((SI_Long)9L)) 
							= paper_size_info;
						SVREF(state_block,
							FIX((SI_Long)10L)) 
							= paper_margins;
						SVREF(state_block,
							FIX((SI_Long)11L)) 
							= 
							actual_paper_width_mf;
						SVREF(state_block,
							FIX((SI_Long)12L)) 
							= 
							actual_paper_height_mf;
						SVREF(state_block,
							FIX((SI_Long)13L)) 
							= paper_width_mf;
						SVREF(state_block,
							FIX((SI_Long)14L)) 
							= paper_height_mf;
						SVREF(state_block,
							FIX((SI_Long)15L)) 
							= paper_left_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)16L)) 
							= paper_top_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)17L)) 
							= 
							paper_right_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)18L)) 
							= 
							paper_bottom_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)19L)) 
							= left_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)20L)) 
							= top_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)21L)) 
							= right_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)22L)) 
							= bottom_margin_mf;
						SVREF(state_block,
							FIX((SI_Long)23L)) 
							= left;
						SVREF(state_block,
							FIX((SI_Long)24L)) 
							= top;
						SVREF(state_block,
							FIX((SI_Long)25L)) 
							= right;
						SVREF(state_block,
							FIX((SI_Long)26L)) 
							= bottom;
						SVREF(state_block,
							FIX((SI_Long)27L)) 
							= workspace_width;
						SVREF(state_block,
							FIX((SI_Long)28L)) 
							= workspace_height;
						SVREF(state_block,
							FIX((SI_Long)29L)) 
							= window_frame_width;
						SVREF(state_block,
							FIX((SI_Long)30L)) 
							= page_width_mf;
						SVREF(state_block,
							FIX((SI_Long)31L)) 
							= page_height_mf;
						SVREF(state_block,
							FIX((SI_Long)32L)) 
							= 
							postscript_units_per_workspace_unit_mf;
						SVREF(state_block,
							FIX((SI_Long)33L)) 
							= x_tile_step;
						SVREF(state_block,
							FIX((SI_Long)34L)) 
							= y_tile_step;
						svref_new_value = 
							Printing_format;
						SVREF(state_block,
							FIX((SI_Long)35L)) 
							= svref_new_value;
						svref_new_value = 
							Gensym_window_for_printing;
						SVREF(state_block,
							FIX((SI_Long)36L)) 
							= svref_new_value;
						svref_new_value = 
							Printing_stream;
						SVREF(state_block,
							FIX((SI_Long)37L)) 
							= svref_new_value;
						SVREF(state_block,
							FIX((SI_Long)38L)) 
							= image_plane;
						SVREF(state_block,
							FIX((SI_Long)39L)) 
							= blank_page_p;
						SVREF(state_block,
							FIX((SI_Long)40L)) 
							= pathname_1;
						svref_new_value = 
							Bitmap_for_printing_qm;
						SVREF(state_block,
							FIX((SI_Long)41L)) 
							= svref_new_value;
						svref_new_value = 
							Last_postscript_composite_object_index;
						SVREF(state_block,
							FIX((SI_Long)42L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_composite_object_mapping;
						SVREF(state_block,
							FIX((SI_Long)43L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_object_mapping_for_icon_renderings;
						SVREF(state_block,
							FIX((SI_Long)44L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_computed_variables_mapping;
						SVREF(state_block,
							FIX((SI_Long)45L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_printing_icon_renderings;
						SVREF(state_block,
							FIX((SI_Long)46L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_object_mapping_for_graph_renderings;
						SVREF(state_block,
							FIX((SI_Long)47L)) 
							= svref_new_value;
						svref_new_value = 
							Fonts_used_in_print_job;
						SVREF(state_block,
							FIX((SI_Long)48L)) 
							= svref_new_value;
						svref_new_value = 
							Kanji_fonts_used_in_print_job;
						SVREF(state_block,
							FIX((SI_Long)49L)) 
							= svref_new_value;
						svref_new_value = 
							Fonts_needing_corresponding_kanji_font;
						SVREF(state_block,
							FIX((SI_Long)50L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_emitting_definition;
						SVREF(state_block,
							FIX((SI_Long)51L)) 
							= svref_new_value;
						svref_new_value = 
							Postscript_definition_operation_counter;
						SVREF(state_block,
							FIX((SI_Long)52L)) 
							= svref_new_value;
						svref_new_value = 
							Printing_icon_current_region_index_qm;
						SVREF(state_block,
							FIX((SI_Long)53L)) 
							= svref_new_value;
						svref_new_value = 
							Printing_pass_number;
						SVREF(state_block,
							FIX((SI_Long)54L)) 
							= svref_new_value;
						SVREF(state_block,
							FIX((SI_Long)55L)) 
							= 
							printing_pass_is_for_header;
						svref_new_value = 
							Emit_postscript_line_length;
						SVREF(state_block,
							FIX((SI_Long)56L)) 
							= svref_new_value;
						SVREF(state_block,
							FIX((SI_Long)57L)) 
							= initial_tile_offset;
						SVREF(state_block,
							FIX((SI_Long)58L)) 
							= ncolumns;
						SVREF(state_block,
							FIX((SI_Long)59L)) 
							= nrows;
						SVREF(state_block,
							FIX((SI_Long)60L)) 
							= npages;
						SVREF(state_block,
							FIX((SI_Long)61L)) 
							= eps_qm;
						SVREF(state_block,
							FIX((SI_Long)62L)) 
							= multipage_legends_p;
						SVREF(state_block,
							FIX((SI_Long)63L)) 
							= page_number;
						SVREF(state_block,
							FIX((SI_Long)64L)) 
							= x_tile_offset;
						SVREF(state_block,
							FIX((SI_Long)65L)) 
							= y_tile_offset;
						SVREF(state_block,
							FIX((SI_Long)66L)) 
							= state_1;
						result = VALUES_1(SVREF(state_block,
							FIX((SI_Long)67L)) 
							= substate);
					    }
					    else if (EQ(background_process_return_status,
						    Qinvalid_blocks) || 
						    EQ(background_process_return_status,
						    Qexit))
						result = VALUES_1(SVREF(process,
							FIX((SI_Long)3L)) 
							= Qdone);
					    else
						result = VALUES_1(Qnil);
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_166;  /* "~a on ~a" */

static Object string_constant_167;  /* "~s" */

static Object string_constant_168;  /* "Begin printing ~NF to ~a at priority ~d." */

static Object string_constant_169;  /* "Begin printing ~NF to ~a at priority ~d.  ~a ~a ahead in queue." */

static Object string_constant_170;  /* "jobs" */

static Object string_constant_171;  /* "job" */

static Object string_constant_172;  /* "Printing workspace ~NF failed." */

static Object string_constant_173;  /* "The workspace being printed to ~a has been deleted." */

static Object string_constant_174;  /* "Finished printing ~NF to ~a." */

static Object string_constant_175;  /* "Finished printing ~NF to ~a.   ~a ~a remaining." */

/* PRINTING-NOTIFICATION */
Object printing_notification(which,workspace,pathname_qm)
    Object which, workspace, pathname_qm;
{
    Object priority, njobs, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, destination;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(96,333);
    priority = ISVREF(Printer_setup,(SI_Long)25L);
    njobs = length(Background_processes);
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
	      if (EQ(Printing_format,Qnative)) {
		  temp = printer_setup_particular(Qprinter_identification);
		  tformat(3,string_constant_166,temp,
			  gensym_window_host_name(Output_window_for_printing_qm));
	      }
	      else
		  tformat(2,string_constant_167,pathname_qm);
	      destination = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (EQ(which,Qbegin)) {
	if (IFIX(njobs) == (SI_Long)1L)
	    notify_user(4,string_constant_168,workspace,destination,priority);
	else
	    notify_user(6,string_constant_169,workspace,destination,
		    priority,FIXNUM_SUB1(njobs),IFIX(njobs) > (SI_Long)2L ?
		     string_constant_170 : string_constant_171);
    }
    else if (EQ(which,Qerror))
	notify_user(2,string_constant_172,workspace);
    else if (EQ(which,Qdeleted))
	notify_user(2,string_constant_173,destination);
    else if (EQ(which,Qend)) {
	if ( !TRUEP(workspace));
	else if (IFIX(njobs) == (SI_Long)1L)
	    notify_user(3,string_constant_174,workspace,destination);
	else
	    notify_user(5,string_constant_175,workspace,destination,
		    FIXNUM_SUB1(njobs),IFIX(njobs) > (SI_Long)2L ? 
		    string_constant_170 : string_constant_171);
    }
    return reclaim_text_string(destination);
}

/* PRINT-WORKSPACE-FROM-ACTION */
Object print_workspace_from_action(workspace)
    Object workspace;
{
    x_note_fn_call(96,334);
    return print_workspace(1,workspace);
}

/* WORKSPACE-OF-PRINTING-PROCESS */
Object workspace_of_printing_process(process)
    Object process;
{
    x_note_fn_call(96,335);
    if (EQ(ISVREF(process,(SI_Long)1L),Qbackground_print_workspace) && 
	    ISVREF(process,(SI_Long)7L))
	return VALUES_1(ISVREF(ISVREF(process,(SI_Long)7L),(SI_Long)1L));
    else
	return VALUES_1(Nil);
}

/* SERVICE-PRINT-JOBS */
Object service_print_jobs(workspace_qm)
    Object workspace_qm;
{
    Object process, ab_loop_list_, printing_workspace_qm;

    x_note_fn_call(96,336);
    process = Nil;
    ab_loop_list_ = Background_processes;
    printing_workspace_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    process = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    printing_workspace_qm = workspace_of_printing_process(process);
    if (printing_workspace_qm && ( !TRUEP(workspace_qm) || EQ(workspace_qm,
	    printing_workspace_qm)))
	call_background_process(process);
    if (time_slice_expired_p())
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PENDING-PRINT-JOBS-P */
Object pending_print_jobs_p(workspace_qm)
    Object workspace_qm;
{
    Object process, ab_loop_list_, printing_workspace_qm, ab_loop_it_, temp;

    x_note_fn_call(96,337);
    process = Nil;
    ab_loop_list_ = Background_processes;
    printing_workspace_qm = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    process = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    printing_workspace_qm = workspace_of_printing_process(process);
    if (printing_workspace_qm) {
	temp =  !TRUEP(workspace_qm) ? T : Nil;
	if (temp);
	else
	    temp = EQ(workspace_qm,printing_workspace_qm) ? T : Nil;
	ab_loop_it_ = temp;
    }
    else
	ab_loop_it_ = Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* G2-UI-PRINT-WINDOW */
Object g2_ui_print_window(g2_window,is_print_dlg_showed)
    Object g2_window, is_print_dlg_showed;
{
    Object gensym_window, is_print_dlg_showed_p, icp_output_port_qm;
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(96,338);
    gensym_window = map_g2_window_to_gensym_window(g2_window);
    is_print_dlg_showed_p = 
	    evaluation_truth_value_is_true_p(is_print_dlg_showed);
    icp_output_port_qm = ISVREF(gensym_window,(SI_Long)12L);
    if (icp_output_port_qm && 
	    icp_connection_open_p(ISVREF(icp_output_port_qm,(SI_Long)2L))) {
	current_icp_port = icp_output_port_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_1 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_2 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    temp = 
					    send_icp_print_native_window(gensym_window,
					    is_print_dlg_showed_p);
				    end_icp_message_group();
				}
				else
				    temp = Nil;
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				}
				result = VALUES_1(temp);
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

void printing_INIT()
{
    Object temp, temp_1, yes_or_no_evaluation_setter_1;
    Object yes_or_no_evaluation_getter_1;
    Object linear_unit_of_length_evaluation_setter_1;
    Object linear_unit_of_length_evaluation_getter_1;
    Object linear_distance_evaluation_setter_1;
    Object linear_distance_evaluation_getter_1;
    Object paper_size_kind_evaluation_setter_1;
    Object paper_size_kind_evaluation_getter_1;
    Object printer_page_layout_evaluation_setter_1;
    Object printer_page_layout_evaluation_getter_1;
    Object kind_of_scaling_evaluation_setter_1;
    Object kind_of_scaling_evaluation_getter_1;
    Object printer_translation_details_evaluation_setter_1;
    Object printer_translation_details_evaluation_getter_1;
    Object printer_spooling_details_evaluation_setter_1;
    Object printer_spooling_details_evaluation_getter_1;
    Object printing_file_format_evaluation_setter_1;
    Object printing_file_format_evaluation_getter_1, temp_2;
    Object write_printer_file_template_is_misformed_note_1;
    Object write_printer_is_not_default_printer_note_1;
    Object write_printer_no_printer_specified_note_1;
    Object write_printer_is_unknown_note_1;
    Object write_printer_small_margin_are_ignored_note_1;
    Object write_printer_paper_size_is_unreasonable_note_1;
    Object write_printer_only_black_and_white_is_supported_note_1;
    Object write_printer_unimplemented_page_layout_settings_note_1;
    Object write_printer_g2_can_not_spool_output_on_this_platform_note_1;
    Object named_dynamic_extent_description;
    Object reclaim_structure_for_line_drawing_for_printing_1;
    Object reclaim_structure_for_process_1;
    Object reclaim_structure_for_background_print_workspace_process_state_block_1;
    Object gensymed_symbol;
    Object Qg2_ui_print_window, Qfunction_keeps_procedure_environment_valid_qm;
    Object AB_package, Qreclaim_background_print_workspace_process_state_block;
    Object Qinitialize_background_print_workspace_process_state_block;
    Object Qwork_on_background_print_workspace;
    Object Qbackground_print_workspace_process_state_block, Qreclaim_structure;
    Object Qoutstanding_background_print_workspace_process_state_block_count;
    Object Qbackground_print_workspace_process_state_block_structure_memory_usage;
    Object Qutilities2, string_constant_210, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_209, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qnative_printing_paint_icon_onto_graph_raster;
    Object Qnative_printing_add_from_graph_rendering_to_current_window;
    Object Qnative_printing_update_ring_raster_for_graph_given_color_values;
    Object Qnative_printing_update_graph_data_extrema;
    Object Qnative_printing_clear_data_clipping_rectangles;
    Object Qnative_printing_update_graph_dateline;
    Object Qnative_printing_paint_icon_background_image_in_current_window;
    Object Qnative_printing_paint_image_in_current_window;
    Object Qnative_printing_copy_from_tiling_pattern_to_current_window;
    Object Qnative_printing_add_ellipse_to_current_window;
    Object Qnative_printing_add_polygon_to_current_window;
    Object Qnative_printing_add_wide_polyline_to_current_window;
    Object Qnative_printing_add_downward_sloping_line_to_current_window;
    Object Qnative_printing_add_upward_sloping_line_to_current_window;
    Object Qnative_printing_add_solid_rectangle_to_current_window;
    Object Qnative_printing_paint_solid_rectangle_in_current_window;
    Object Qnative_printing_add_from_line_of_text_to_current_window;
    Object Qnative_printing_add_from_icon_rendering_to_current_window;
    Object Qnative_printing_paint_from_line_of_text_to_current_scratchpad_raster;
    Object Qnative_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster;
    Object Qnative_printing_paint_image_in_current_scratchpad_raster;
    Object Qnative_printing_paint_point_in_current_scratchpad_raster;
    Object Qnative_printing_paint_wide_line_in_current_scratchpad_raster;
    Object Qnative_printing_paint_filled_polygon_in_current_scratchpad_raster;
    Object Qnative_printing_paint_filled_triangle_in_current_scratchpad_raster;
    Object Qnative_printing_paint_arc_or_circle_in_current_scratchpad_raster;
    Object Qnative_printing_paint_line_in_current_scratchpad_raster;
    Object Qnative_printing_paint_solid_rectangle_in_current_scratchpad_raster;
    Object Qnative_printing_default_icp_handler, Qprocess;
    Object Qoutstanding_process_count, Qprocess_structure_memory_usage;
    Object string_constant_208, string_constant_207, Qprocess_description;
    Object string_constant_206, list_constant_82;
    Object Qhandler_for_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster;
    Object Qhandler_for_printing_paint_from_line_of_text_to_current_scratchpad_raster;
    Object Qhandler_for_printing_clear_data_clipping_rectangles;
    Object Qhandler_for_printing_update_ring_raster_for_graph_given_color_values;
    Object Qhandler_for_printing_update_graph_data_extrema;
    Object Qhandler_for_printing_update_graph_dateline;
    Object Qhandler_for_printing_add_from_graph_rendering_to_current_window;
    Object Qhandler_for_printing_add_from_line_of_text_to_current_window;
    Object Qhandler_for_printing_copy_from_tiling_pattern_to_current_window;
    Object Qhandler_for_printing_add_ellipse_to_current_window;
    Object Qhandler_for_printing_add_polygon_to_current_window;
    Object Qhandler_for_printing_add_wide_polyline_to_current_window;
    Object Qhandler_for_printing_add_downward_sloping_line_to_current_window;
    Object Qhandler_for_printing_add_upward_sloping_line_to_current_window;
    Object Qhandler_for_printing_add_from_icon_rendering_to_current_window;
    Object Qhandler_for_printing_add_solid_rectangle_to_current_window;
    Object Qhandler_for_printing_paint_solid_rectangle_in_current_window;
    Object Qhandler_for_printing_change_image_palette_of_window;
    Object Qhandler_for_printing_paint_image_in_current_scratchpad_raster;
    Object Qhandler_for_printing_paint_image_in_current_window;
    Object Qhandler_for_printing_paint_icon_background_image_in_current_window;
    Object Qhandler_for_printing_paint_marker_onto_graph_raster;
    Object Qhandler_for_printing_paint_icon_onto_graph_raster;
    Object Qhandler_for_printing_paint_point_in_current_scratchpad_raster;
    Object Qhandler_for_printing_paint_wide_line_in_current_scratchpad_raster;
    Object Qhandler_for_printing_paint_filled_polygon_in_current_scratchpad_raster;
    Object Qhandler_for_printing_paint_filled_triangle_in_current_scratchpad_raster;
    Object Qhandler_for_printing_paint_arc_or_circle_in_current_scratchpad_raster;
    Object Qhandler_for_printing_paint_line_in_current_scratchpad_raster;
    Object Qhandler_for_printing_paint_solid_rectangle_in_current_scratchpad_raster;
    Object Qhandler_for_printing_initialize_scratchpad_raster;
    Object Qhandler_for_printing_set_up_palette;
    Object Qhandler_for_printing_scroll_rectangle_in_current_window;
    Object Qdefault_print_handler_for_icp_messages, Qwrite_hex_table;
    Object list_constant_125, list_constant_124, list_constant_123;
    Object list_constant_122, list_constant_121, list_constant_120;
    Object list_constant_119, list_constant_118, list_constant_117, Qkanji16;
    Object Qthai16, Qhebrew16, Qslavic16, list_constant_116, list_constant_115;
    Object list_constant_114, list_constant_113, list_constant_112;
    Object list_constant_111, list_constant_110, list_constant_109;
    Object list_constant_108, list_constant_107, list_constant_106;
    Object list_constant_105, list_constant_104, list_constant_103;
    Object list_constant_102, list_constant_101, list_constant_100;
    Object list_constant_99, list_constant_98, list_constant_97;
    Object list_constant_96, list_constant_95, list_constant_94;
    Object list_constant_93, list_constant_92, list_constant_91;
    Object list_constant_90, list_constant_89, list_constant_88;
    Object list_constant_86, list_constant_87, Qline_drawing_for_printing;
    Object Qoutstanding_line_drawing_for_printing_count;
    Object Qline_drawing_for_printing_structure_memory_usage;
    Object string_constant_205, string_constant_204, string_constant_203;
    Object Qprinting_cons_memory_usage, Qoutstanding_printing_conses;
    Object list_constant_85, Qprinting_cons_counter_vector, Qmake_thread_array;
    Object Kfuncall, list_constant_84, Qavailable_printing_conses_tail_vector;
    Object Qavailable_printing_conses_vector, list_constant_83;
    Object Qnamed_dynamic_extent_description, string_constant_202;
    Object Qslot_value_writer, Qwrite_printing_file_format_from_slot;
    Object Qprinting_file_format, Qwrite_printer_spooling_details_from_slot;
    Object Qprinter_spooling_details, Qwrite_printer_page_layout_from_slot;
    Object Qprinter_page_layout, Qwrite_printer_translation_details_from_slot;
    Object Qprinter_translation_details, string_constant_201;
    Object string_constant_200, string_constant_199, string_constant_198;
    Object string_constant_197, string_constant_196, string_constant_195;
    Object string_constant_194, string_constant_193;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_printer_translation_details_for_slot;
    Object string_constant_192, string_constant_191, string_constant_190;
    Object string_constant_189, string_constant_188, string_constant_187;
    Object list_constant_81, list_constant_80, list_constant_79;
    Object list_constant_78, list_constant_77, list_constant_76;
    Object string_constant_186, string_constant_185, list_constant_75;
    Object list_constant_74, list_constant_73, list_constant_72;
    Object float_constant_14, float_constant_13, Qclasses_which_define;
    Object Qupdate_frame_status_and_notes;
    Object Qupdate_frame_status_and_notes_for_printer_setup, float_constant_12;
    Object Qprinter_unimplemented, Qprinter_unimplemented_page_layout_settings;
    Object Qprinter_only_black_and_white_is_supported, Qprinter_is_unknown;
    Object Qprinter_no_printer_specified, Qprinter_is_not_default_printer;
    Object Qframe_note_writer_1, Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_printer_setup, Qinstall_system_table;
    Object Qinstall_system_table_for_printer_setup, Qslot_putter;
    Object Qput_print_spooling, Qput_page_layout, Qput_printing_details;
    Object Qinitialize, Qinitialize_for_printer_setup, Qprinting_parameters;
    Object Qpriority_for_printing, Qprinting_priority, Ksystem_frame;
    Object string_constant_184, string_constant_183, string_constant_182;
    Object list_constant_71, float_constant_11, string_constant_181;
    Object string_constant_180, string_constant_179, string_constant_178;
    Object string_constant_177, array_constant_9, string_constant_176;
    Object Qsystem_table, Qnamed, Qtype_specification_simple_expansion;
    Object list_constant_70, list_constant_69, Qab_structure, list_constant_68;
    Object list_constant_67, list_constant_66, list_constant_65, Qtext;
    Object list_constant_64, list_constant_63, list_constant_62;
    Object list_constant_61, list_constant_60, list_constant_42;
    Object list_constant_59, Qab_or, list_constant_58, list_constant_57;
    Object list_constant_56, list_constant_55, list_constant_54;
    Object list_constant_53, list_constant_52, list_constant_51;
    Object list_constant_50, list_constant_49, list_constant_48;
    Object list_constant_47, list_constant_46, list_constant_45;
    Object list_constant_44, list_constant_43, Qb5, Qb4, Qb3, Qb2, Qb1, Qb0;
    Object Qa5, Qa4, Qa3, Qa2, Qa1, Qa0, Qledger, Qlegal, Qletter;
    Object list_constant_41, list_constant_40, list_constant_39;
    Object list_constant_38, list_constant_37, Qlinear_unit_of_length;
    Object Qgeneric_method_lambda_list, list_constant_36, Qretract_frame_notes;
    Object Qassert_frame_notes, Qupdate_frame_status_and_notes_for_block;

    x_note_fn_call(96,339);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qupdate_frame_status_and_notes = 
	    STATIC_SYMBOL("UPDATE-FRAME-STATUS-AND-NOTES",AB_package);
    list_constant_36 = STATIC_CONS(Qblock,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qupdate_frame_status_and_notes,list_constant_36,
	    Qgeneric_method_lambda_list);
    Qupdate_frame_status_and_notes_for_block = 
	    STATIC_SYMBOL("UPDATE-FRAME-STATUS-AND-NOTES-FOR-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_frame_status_and_notes_for_block,
	    STATIC_FUNCTION(update_frame_status_and_notes_for_block,NIL,
	    FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qupdate_frame_status_and_notes_for_block);
    set_get(Qblock,Qupdate_frame_status_and_notes,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_frame_status_and_notes),
	    Qclasses_which_define);
    temp = CONS(Qblock,temp_1);
    mutate_global_property(Qupdate_frame_status_and_notes,temp,
	    Qclasses_which_define);
    Qassert_frame_notes = STATIC_SYMBOL("ASSERT-FRAME-NOTES",AB_package);
    mutate_global_property(Qassert_frame_notes,list_constant_36,
	    Qgeneric_method_lambda_list);
    Qretract_frame_notes = STATIC_SYMBOL("RETRACT-FRAME-NOTES",AB_package);
    mutate_global_property(Qretract_frame_notes,list_constant_36,
	    Qgeneric_method_lambda_list);
    Qyes_or_no = STATIC_SYMBOL("YES-OR-NO",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qyes_or_no),
	    Qtype_specification_simple_expansion,Qtruth_value);
    define_type_specification_explicit_complex_type(Qyes_or_no,Qtruth_value);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qyes_or_no);
    yes_or_no_evaluation_setter_1 = 
	    STATIC_FUNCTION(yes_or_no_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qyes_or_no,
	    yes_or_no_evaluation_setter_1);
    yes_or_no_evaluation_getter_1 = 
	    STATIC_FUNCTION(yes_or_no_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qyes_or_no,
	    yes_or_no_evaluation_getter_1);
    Qlinear_unit_of_length = STATIC_SYMBOL("LINEAR-UNIT-OF-LENGTH",AB_package);
    set_property_value_function(get_symbol_properties_function(Qlinear_unit_of_length),
	    Qtype_specification_simple_expansion,Qnil);
    Qinch = STATIC_SYMBOL("INCH",AB_package);
    Qinches = STATIC_SYMBOL("INCHES",AB_package);
    Qcentimeter = STATIC_SYMBOL("CENTIMETER",AB_package);
    Qcentimeters = STATIC_SYMBOL("CENTIMETERS",AB_package);
    Qab_cm = STATIC_SYMBOL("CM",AB_package);
    Qfoot = STATIC_SYMBOL("FOOT",AB_package);
    Qfeet = STATIC_SYMBOL("FEET",AB_package);
    Qmillimeter = STATIC_SYMBOL("MILLIMETER",AB_package);
    Qmillimeters = STATIC_SYMBOL("MILLIMETERS",AB_package);
    Qmm = STATIC_SYMBOL("MM",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)11L,Qmember,Qinch,Qinches,
	    Qcentimeter,Qcentimeters,Qab_cm,Qfoot,Qfeet,Qmillimeter,
	    Qmillimeters,Qmm);
    define_type_specification_explicit_complex_type(Qlinear_unit_of_length,
	    list_constant_2);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnamed,Qlinear_unit_of_length);
    linear_unit_of_length_evaluation_setter_1 = 
	    STATIC_FUNCTION(linear_unit_of_length_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qlinear_unit_of_length,
	    linear_unit_of_length_evaluation_setter_1);
    linear_unit_of_length_evaluation_getter_1 = 
	    STATIC_FUNCTION(linear_unit_of_length_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlinear_unit_of_length,
	    linear_unit_of_length_evaluation_getter_1);
    Qlinear_distance = STATIC_SYMBOL("LINEAR-DISTANCE",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_7 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Qlinear_distance),
	    Qtype_specification_simple_expansion,list_constant_7);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qnumber,Qnumber);
    Qunits = STATIC_SYMBOL("UNITS",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qunits,list_constant_1);
    list_constant_39 = STATIC_LIST((SI_Long)2L,list_constant_37,
	    list_constant_38);
    list_constant_40 = STATIC_LIST((SI_Long)3L,Qand,Qnumber,Qunits);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_39,list_constant_40);
    define_type_specification_explicit_complex_type(Qlinear_distance,
	    list_constant_4);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnamed,Qlinear_distance);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    linear_distance_evaluation_setter_1 = 
	    STATIC_FUNCTION(linear_distance_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlinear_distance,
	    linear_distance_evaluation_setter_1);
    linear_distance_evaluation_getter_1 = 
	    STATIC_FUNCTION(linear_distance_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlinear_distance,
	    linear_distance_evaluation_getter_1);
    Qpaper_size_kind = STATIC_SYMBOL("PAPER-SIZE-KIND",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)3L,Qab_or,Qnil,list_constant_7);
    set_property_value_function(get_symbol_properties_function(Qpaper_size_kind),
	    Qtype_specification_simple_expansion,list_constant_41);
    Qletter = STATIC_SYMBOL("LETTER",AB_package);
    Qlegal = STATIC_SYMBOL("LEGAL",AB_package);
    Qledger = STATIC_SYMBOL("LEDGER",AB_package);
    Qa0 = STATIC_SYMBOL("A0",AB_package);
    Qa1 = STATIC_SYMBOL("A1",AB_package);
    Qa2 = STATIC_SYMBOL("A2",AB_package);
    Qa3 = STATIC_SYMBOL("A3",AB_package);
    Qa4 = STATIC_SYMBOL("A4",AB_package);
    Qa5 = STATIC_SYMBOL("A5",AB_package);
    Qb0 = STATIC_SYMBOL("B0",AB_package);
    Qb1 = STATIC_SYMBOL("B1",AB_package);
    Qb2 = STATIC_SYMBOL("B2",AB_package);
    Qb3 = STATIC_SYMBOL("B3",AB_package);
    Qb4 = STATIC_SYMBOL("B4",AB_package);
    Qb5 = STATIC_SYMBOL("B5",AB_package);
    list_constant_47 = STATIC_LIST((SI_Long)16L,Qmember,Qletter,Qlegal,
	    Qledger,Qa0,Qa1,Qa2,Qa3,Qa4,Qa5,Qb0,Qb1,Qb2,Qb3,Qb4,Qb5);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    list_constant_42 = STATIC_CONS(list_constant_3,Qnil);
    list_constant_43 = STATIC_CONS(Qwidth,list_constant_42);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    list_constant_44 = STATIC_CONS(Qheight,list_constant_42);
    list_constant_45 = STATIC_LIST((SI_Long)2L,list_constant_43,
	    list_constant_44);
    list_constant_46 = STATIC_LIST((SI_Long)3L,Qand,Qwidth,Qheight);
    list_constant_48 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_45,list_constant_46);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_47,
	    list_constant_48);
    define_type_specification_explicit_complex_type(Qpaper_size_kind,
	    list_constant_6);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnamed,Qpaper_size_kind);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qcustom = STATIC_SYMBOL("CUSTOM",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = STATIC_STRING("~NT ");
    string_constant_1 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    paper_size_kind_evaluation_setter_1 = 
	    STATIC_FUNCTION(paper_size_kind_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qpaper_size_kind,
	    paper_size_kind_evaluation_setter_1);
    paper_size_kind_evaluation_getter_1 = 
	    STATIC_FUNCTION(paper_size_kind_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpaper_size_kind,
	    paper_size_kind_evaluation_getter_1);
    Qprinter_page_layout = STATIC_SYMBOL("PRINTER-PAGE-LAYOUT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qprinter_page_layout),
	    Qtype_specification_simple_expansion,list_constant_7);
    Qpaper_size = STATIC_SYMBOL("PAPER-SIZE",AB_package);
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qpaper_size,list_constant_5);
    Qpaper_orientation = STATIC_SYMBOL("PAPER-ORIENTATION",AB_package);
    Qportrait = STATIC_SYMBOL("PORTRAIT",AB_package);
    Qlandscape = STATIC_SYMBOL("LANDSCAPE",AB_package);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Qmember,Qportrait,Qlandscape);
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qpaper_orientation,
	    list_constant_49);
    Qleft_margin = STATIC_SYMBOL("LEFT-MARGIN",AB_package);
    list_constant_52 = STATIC_CONS(Qleft_margin,list_constant_42);
    Qtop_margin = STATIC_SYMBOL("TOP-MARGIN",AB_package);
    list_constant_53 = STATIC_CONS(Qtop_margin,list_constant_42);
    Qright_margin = STATIC_SYMBOL("RIGHT-MARGIN",AB_package);
    list_constant_54 = STATIC_CONS(Qright_margin,list_constant_42);
    Qbottom_margin = STATIC_SYMBOL("BOTTOM-MARGIN",AB_package);
    list_constant_55 = STATIC_CONS(Qbottom_margin,list_constant_42);
    list_constant_56 = STATIC_LIST((SI_Long)6L,list_constant_50,
	    list_constant_51,list_constant_52,list_constant_53,
	    list_constant_54,list_constant_55);
    list_constant_57 = STATIC_LIST((SI_Long)7L,Qand,Qpaper_size,
	    Qpaper_orientation,Qleft_margin,Qtop_margin,Qright_margin,
	    Qbottom_margin);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_56,list_constant_57);
    define_type_specification_explicit_complex_type(Qprinter_page_layout,
	    list_constant_9);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qnamed,Qprinter_page_layout);
    printer_page_layout_evaluation_setter_1 = 
	    STATIC_FUNCTION(printer_page_layout_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qprinter_page_layout,
	    printer_page_layout_evaluation_setter_1);
    printer_page_layout_evaluation_getter_1 = 
	    STATIC_FUNCTION(printer_page_layout_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qprinter_page_layout,
	    printer_page_layout_evaluation_getter_1);
    Qkind_of_scaling = STATIC_SYMBOL("KIND-OF-SCALING",AB_package);
    list_constant_58 = STATIC_LIST((SI_Long)3L,Qab_or,Qnil,Qnil);
    set_property_value_function(get_symbol_properties_function(Qkind_of_scaling),
	    Qtype_specification_simple_expansion,list_constant_58);
    Qscale_to_fit_single_page = STATIC_SYMBOL("SCALE-TO-FIT-SINGLE-PAGE",
	    AB_package);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qmember,
	    Qscale_to_fit_single_page);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_59,list_constant_42);
    define_type_specification_explicit_complex_type(Qkind_of_scaling,
	    list_constant_11);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qnamed,Qkind_of_scaling);
    kind_of_scaling_evaluation_setter_1 = 
	    STATIC_FUNCTION(kind_of_scaling_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qkind_of_scaling,
	    kind_of_scaling_evaluation_setter_1);
    kind_of_scaling_evaluation_getter_1 = 
	    STATIC_FUNCTION(kind_of_scaling_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qkind_of_scaling,
	    kind_of_scaling_evaluation_getter_1);
    Qprinter_translation_details = 
	    STATIC_SYMBOL("PRINTER-TRANSLATION-DETAILS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qprinter_translation_details),
	    Qtype_specification_simple_expansion,list_constant_7);
    Qworkspace_scaling = STATIC_SYMBOL("WORKSPACE-SCALING",AB_package);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qworkspace_scaling,
	    list_constant_10);
    Qcolor_conversion = STATIC_SYMBOL("COLOR-CONVERSION",AB_package);
    Qblack_and_white = STATIC_SYMBOL("BLACK-AND-WHITE",AB_package);
    Qgrays = STATIC_SYMBOL("GRAYS",AB_package);
    Qfull_color = STATIC_SYMBOL("FULL-COLOR",AB_package);
    list_constant_60 = STATIC_LIST((SI_Long)4L,Qmember,Qblack_and_white,
	    Qgrays,Qfull_color);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qcolor_conversion,
	    list_constant_60);
    list_constant_63 = STATIC_LIST((SI_Long)2L,list_constant_61,
	    list_constant_62);
    list_constant_64 = STATIC_LIST((SI_Long)3L,Qand,Qworkspace_scaling,
	    Qcolor_conversion);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_63,list_constant_64);
    define_type_specification_explicit_complex_type(Qprinter_translation_details,
	    list_constant_13);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qprinter_translation_details);
    printer_translation_details_evaluation_setter_1 = 
	    STATIC_FUNCTION(printer_translation_details_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qprinter_translation_details,
	    printer_translation_details_evaluation_setter_1);
    printer_translation_details_evaluation_getter_1 = 
	    STATIC_FUNCTION(printer_translation_details_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qprinter_translation_details,
	    printer_translation_details_evaluation_getter_1);
    Qprinter_spooling_details = STATIC_SYMBOL("PRINTER-SPOOLING-DETAILS",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qprinter_spooling_details),
	    Qtype_specification_simple_expansion,list_constant_7);
    Qspooled_filename_template = STATIC_SYMBOL("SPOOLED-FILENAME-TEMPLATE",
	    AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_65 = STATIC_CONS(Qtext,Qnil);
    list_constant_66 = STATIC_CONS(Qspooled_filename_template,
	    list_constant_65);
    Qspool_file_to_printer = STATIC_SYMBOL("SPOOL-FILE-TO-PRINTER",AB_package);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qspool_file_to_printer,
	    list_constant);
    Qprinter_identification = STATIC_SYMBOL("PRINTER-IDENTIFICATION",
	    AB_package);
    list_constant_68 = STATIC_CONS(Qprinter_identification,list_constant_65);
    list_constant_69 = STATIC_LIST((SI_Long)3L,list_constant_66,
	    list_constant_67,list_constant_68);
    list_constant_70 = STATIC_LIST((SI_Long)4L,Qand,
	    Qspooled_filename_template,Qspool_file_to_printer,
	    Qprinter_identification);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_69,list_constant_70);
    define_type_specification_explicit_complex_type(Qprinter_spooling_details,
	    list_constant_15);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qprinter_spooling_details);
    printer_spooling_details_evaluation_setter_1 = 
	    STATIC_FUNCTION(printer_spooling_details_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qprinter_spooling_details,
	    printer_spooling_details_evaluation_setter_1);
    printer_spooling_details_evaluation_getter_1 = 
	    STATIC_FUNCTION(printer_spooling_details_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qprinter_spooling_details,
	    printer_spooling_details_evaluation_getter_1);
    Qprinting_file_format = STATIC_SYMBOL("PRINTING-FILE-FORMAT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qprinting_file_format),
	    Qtype_specification_simple_expansion,Qnil);
    Qencapsulated_postscript = STATIC_SYMBOL("ENCAPSULATED-POSTSCRIPT",
	    AB_package);
    Qpostscript = STATIC_SYMBOL("POSTSCRIPT",AB_package);
    Qjpeg = STATIC_SYMBOL("JPEG",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)4L,Qmember,
	    Qencapsulated_postscript,Qpostscript,Qjpeg);
    define_type_specification_explicit_complex_type(Qprinting_file_format,
	    list_constant_17);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qnamed,Qprinting_file_format);
    Qeps = STATIC_SYMBOL("EPS",AB_package);
    printing_file_format_evaluation_setter_1 = 
	    STATIC_FUNCTION(printing_file_format_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qprinting_file_format,
	    printing_file_format_evaluation_setter_1);
    printing_file_format_evaluation_getter_1 = 
	    STATIC_FUNCTION(printing_file_format_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qprinting_file_format,
	    printing_file_format_evaluation_getter_1);
    Qprinter_setup = STATIC_SYMBOL("PRINTER-SETUP",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_71 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qprinter_setup,list_constant_71);
    string_constant_176 = STATIC_STRING("1l1l83ey");
    array_constant_9 = STATIC_ARRAY(Qdouble_float,(SI_Long)1L,
	    FIX((SI_Long)1L));
    DFLOAT_ISASET_1(array_constant_9,(SI_Long)0L,0.5);
    string_constant_177 = 
	    STATIC_STRING("1q4z8r83Y6y83Y6y83ETy83ETy01m1n83AWy3-Wy83Csy2l838+y837ny001n1l8o1l8l1m8p83EVy000004z8r83XVy83XVy83ETy83ETy01q2l83EGy83DPy2l83EF");
    string_constant_178 = 
	    STATIC_STRING("y83EOy1n83DOy9k83Csy1n83FTy9l83Csy1n83Eoy9m83Csy1n83B*y9n83Csy001n1l8o1l8l1m8p83ESy000004z8r83Y4y83Y4y83ETy83ETy01n2l83F9y+3Cy3-");
    string_constant_179 = 
	    STATIC_STRING("iy3-ky3-by3-gy3-my3fy3cy3gy3-iy3-lykkkku3A++y1l83F8y2l83ERy+3Cy3-ny3-gy3-dy3-gy3-hy3-py3-gykkkkkkkr3A++y001n1l8o1l8l1m8p83EUy000");
    string_constant_180 = 
	    STATIC_STRING("004z8r83Y7y83Y7y83ETy83ETy0s001n1l8o1l8l1m8p83-Yy000004z8r83EWy83EWy83ETy83ETy083EPy001n1l8o1l8l1m8p83EWy000004z8r83XUy83XUy83ET");
    string_constant_181 = STATIC_STRING("y83ETy00001n1l8o1l8l1m8p83Ky00000");
    float_constant_11 = STATIC_FLOAT(0.5);
    string_constant_182 = 
	    STATIC_STRING("1s8q1n83ETy1l83-sy83ey1p83Y6y1m1n83AWy3-Wy83Csy2l838+y837ny8o8l1m8p83EVy1p83XVy1q2l83EGy83DPy2l83EFy83EOy1n83DOy9k83Csy1n83FTy9k");
    string_constant_183 = 
	    STATIC_STRING("83Csy1n83Eoy9k83Csy1n83B*y9k83Csy8o8l1m8p83ESy1p83Y4y1n2l83F9y5uprint-*.ps1l83F8y2l83ERy5runknown8o8l1m8p83EUy1p83Y7ys8o8l1m8p83");
    string_constant_184 = 
	    STATIC_STRING("-Yy1p83EWy83EPy8o8l1m8p83EWy1p83XUy08o8l1m8p83Ky");
    temp_1 = regenerate_optimized_constant(string_constant_176);
    clear_optimized_constants();
    push_optimized_constant(array_constant_9);
    push_optimized_constant(array_constant_9);
    push_optimized_constant(array_constant_9);
    push_optimized_constant(array_constant_9);
    temp_2 = regenerate_optimized_constant(LIST_5(string_constant_177,
	    string_constant_178,string_constant_179,string_constant_180,
	    string_constant_181));
    clear_optimized_constants();
    push_optimized_constant(float_constant_11);
    add_class_to_environment(9,Qprinter_setup,list_constant_71,Nil,temp_1,
	    Nil,temp_2,list_constant_71,
	    regenerate_optimized_constant(LIST_3(string_constant_182,
	    string_constant_183,string_constant_184)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qprinter_setup,Printer_setup);
    Qprinting = STATIC_SYMBOL("PRINTING",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qprinter_setup,Qprinting,Ksystem_frame,Qnil,
	    Qnil,Qnil,Qt);
    Qprinting_priority = STATIC_SYMBOL("PRINTING-PRIORITY",AB_package);
    Qpriority_for_printing = STATIC_SYMBOL("PRIORITY-FOR-PRINTING",AB_package);
    Qprinting_parameters = STATIC_SYMBOL("PRINTING-PARAMETERS",AB_package);
    alias_slot_name(3,Qprinting_priority,Qpriority_for_printing,
	    Qprinting_parameters);
    Qinitialize_for_printer_setup = 
	    STATIC_SYMBOL("INITIALIZE-FOR-PRINTER-SETUP",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_printer_setup,
	    STATIC_FUNCTION(initialize_for_printer_setup,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp = SYMBOL_FUNCTION(Qinitialize_for_printer_setup);
    set_get(Qprinter_setup,Qinitialize,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp = CONS(Qprinter_setup,temp_1);
    mutate_global_property(Qinitialize,temp,Qclasses_which_define);
    Qprinting_details = STATIC_SYMBOL("PRINTING-DETAILS",AB_package);
    Qput_printing_details = STATIC_SYMBOL("PUT-PRINTING-DETAILS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_printing_details,
	    STATIC_FUNCTION(put_printing_details,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qprinting_details,
	    SYMBOL_FUNCTION(Qput_printing_details),Qslot_putter);
    Qpage_layout = STATIC_SYMBOL("PAGE-LAYOUT",AB_package);
    Qput_page_layout = STATIC_SYMBOL("PUT-PAGE-LAYOUT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_page_layout,STATIC_FUNCTION(put_page_layout,
	    NIL,FALSE,3,3));
    mutate_global_property(Qpage_layout,SYMBOL_FUNCTION(Qput_page_layout),
	    Qslot_putter);
    Qprint_spooling = STATIC_SYMBOL("PRINT-SPOOLING",AB_package);
    Qput_print_spooling = STATIC_SYMBOL("PUT-PRINT-SPOOLING",AB_package);
    SET_SYMBOL_FUNCTION(Qput_print_spooling,
	    STATIC_FUNCTION(put_print_spooling,NIL,FALSE,3,3));
    mutate_global_property(Qprint_spooling,
	    SYMBOL_FUNCTION(Qput_print_spooling),Qslot_putter);
    Qinstall_system_table_for_printer_setup = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-PRINTER-SETUP",AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_printer_setup,
	    STATIC_FUNCTION(install_system_table_for_printer_setup,NIL,
	    FALSE,1,1));
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    temp = SYMBOL_FUNCTION(Qinstall_system_table_for_printer_setup);
    set_get(Qprinter_setup,Qinstall_system_table,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp = CONS(Qprinter_setup,temp_1);
    mutate_global_property(Qinstall_system_table,temp,Qclasses_which_define);
    Qdeinstall_system_table_for_printer_setup = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-PRINTER-SETUP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_printer_setup,
	    STATIC_FUNCTION(deinstall_system_table_for_printer_setup,NIL,
	    FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    temp = SYMBOL_FUNCTION(Qdeinstall_system_table_for_printer_setup);
    set_get(Qprinter_setup,Qdeinstall_system_table,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp = CONS(Qprinter_setup,temp_1);
    mutate_global_property(Qdeinstall_system_table,temp,Qclasses_which_define);
    Qx_dpi = STATIC_SYMBOL("X-DPI",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Qy_dpi = STATIC_SYMBOL("Y-DPI",AB_package);
    Qphysical_width = STATIC_SYMBOL("PHYSICAL-WIDTH",AB_package);
    Qphysical_height = STATIC_SYMBOL("PHYSICAL-HEIGHT",AB_package);
    Qx_offset = STATIC_SYMBOL("X-OFFSET",AB_package);
    Qy_offset = STATIC_SYMBOL("Y-OFFSET",AB_package);
    Qprinter = STATIC_SYMBOL("PRINTER",AB_package);
    Qquality = STATIC_SYMBOL("QUALITY",AB_package);
    Qfrom_page = STATIC_SYMBOL("FROM-PAGE",AB_package);
    Qto_page = STATIC_SYMBOL("TO-PAGE",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)4L,Qleft_margin,Qtop_margin,
	    Qright_margin,Qbottom_margin);
    Qab_pathname = STATIC_SYMBOL("PATHNAME",AB_package);
    Qpaper_margins = STATIC_SYMBOL("PAPER-MARGINS",AB_package);
    Qprinter_file_template_is_misformed = 
	    STATIC_SYMBOL("PRINTER-FILE-TEMPLATE-IS-MISFORMED",AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant_2 = 
	    STATIC_STRING("the filename template for the spooled file is not in a valid format");
    write_printer_file_template_is_misformed_note_1 = 
	    STATIC_FUNCTION(write_printer_file_template_is_misformed_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qprinter_file_template_is_misformed,
	    write_printer_file_template_is_misformed_note_1,
	    Qframe_note_writer_1);
    Qprinter_is_not_default_printer = 
	    STATIC_SYMBOL("PRINTER-IS-NOT-DEFAULT-PRINTER",AB_package);
    string_constant_3 = 
	    STATIC_STRING("the requested printer is not the default printer for this machine");
    write_printer_is_not_default_printer_note_1 = 
	    STATIC_FUNCTION(write_printer_is_not_default_printer_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qprinter_is_not_default_printer,
	    write_printer_is_not_default_printer_note_1,Qframe_note_writer_1);
    Qprinter_no_printer_specified = 
	    STATIC_SYMBOL("PRINTER-NO-PRINTER-SPECIFIED",AB_package);
    string_constant_4 = 
	    STATIC_STRING("since the printer identification is unknown, printed output will be left in the spooled output file");
    write_printer_no_printer_specified_note_1 = 
	    STATIC_FUNCTION(write_printer_no_printer_specified_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qprinter_no_printer_specified,
	    write_printer_no_printer_specified_note_1,Qframe_note_writer_1);
    Qprinter_is_unknown = STATIC_SYMBOL("PRINTER-IS-UNKNOWN",AB_package);
    string_constant_5 = 
	    STATIC_STRING("the requested printer is not one of the known printers for this host");
    write_printer_is_unknown_note_1 = 
	    STATIC_FUNCTION(write_printer_is_unknown_note,NIL,FALSE,2,2);
    mutate_global_property(Qprinter_is_unknown,
	    write_printer_is_unknown_note_1,Qframe_note_writer_1);
    Qprinter_small_margin_are_ignored = 
	    STATIC_SYMBOL("PRINTER-SMALL-MARGIN-ARE-IGNORED",AB_package);
    string_constant_6 = 
	    STATIC_STRING("small margins are often not supported by printers");
    write_printer_small_margin_are_ignored_note_1 = 
	    STATIC_FUNCTION(write_printer_small_margin_are_ignored_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qprinter_small_margin_are_ignored,
	    write_printer_small_margin_are_ignored_note_1,
	    Qframe_note_writer_1);
    Qprinter_paper_size_is_unreasonable = 
	    STATIC_SYMBOL("PRINTER-PAPER-SIZE-IS-UNREASONABLE",AB_package);
    string_constant_7 = 
	    STATIC_STRING("the requested paper size is out of range or otherwise unattainable e.g. due to too wide margins");
    write_printer_paper_size_is_unreasonable_note_1 = 
	    STATIC_FUNCTION(write_printer_paper_size_is_unreasonable_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qprinter_paper_size_is_unreasonable,
	    write_printer_paper_size_is_unreasonable_note_1,
	    Qframe_note_writer_1);
    Qprinter_only_black_and_white_is_supported = 
	    STATIC_SYMBOL("PRINTER-ONLY-BLACK-AND-WHITE-IS-SUPPORTED",
	    AB_package);
    string_constant_8 = STATIC_STRING("");
    write_printer_only_black_and_white_is_supported_note_1 = 
	    STATIC_FUNCTION(write_printer_only_black_and_white_is_supported_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qprinter_only_black_and_white_is_supported,
	    write_printer_only_black_and_white_is_supported_note_1,
	    Qframe_note_writer_1);
    Qprinter_unimplemented_page_layout_settings = 
	    STATIC_SYMBOL("PRINTER-UNIMPLEMENTED-PAGE-LAYOUT-SETTINGS",
	    AB_package);
    write_printer_unimplemented_page_layout_settings_note_1 = 
	    STATIC_FUNCTION(write_printer_unimplemented_page_layout_settings_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qprinter_unimplemented_page_layout_settings,
	    write_printer_unimplemented_page_layout_settings_note_1,
	    Qframe_note_writer_1);
    Qprinter_g2_can_not_spool_output_on_this_platform = 
	    STATIC_SYMBOL("PRINTER-G2-CAN-NOT-SPOOL-OUTPUT-ON-THIS-PLATFORM",
	    AB_package);
    string_constant_9 = 
	    STATIC_STRING("unable to spool output directly to the printer on this machine, ~\n            you will have to transmit the file to the printer by some means outside of G2");
    write_printer_g2_can_not_spool_output_on_this_platform_note_1 = 
	    STATIC_FUNCTION(write_printer_g2_can_not_spool_output_on_this_platform_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qprinter_g2_can_not_spool_output_on_this_platform,
	    write_printer_g2_can_not_spool_output_on_this_platform_note_1,
	    Qframe_note_writer_1);
    Qprinter_unimplemented = STATIC_SYMBOL("PRINTER-UNIMPLEMENTED",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)10L,
	    Qprinter_file_template_is_misformed,
	    Qprinter_is_not_default_printer,Qprinter_no_printer_specified,
	    Qprinter_is_unknown,Qprinter_only_black_and_white_is_supported,
	    Qprinter_unimplemented_page_layout_settings,
	    Qprinter_small_margin_are_ignored,
	    Qprinter_paper_size_is_unreasonable,Qprinter_unimplemented,
	    Qprinter_g2_can_not_spool_output_on_this_platform);
    float_constant_12 = STATIC_FLOAT(0.25);
    list_constant_72 = STATIC_CONS(Qinch,Qnil);
    list_constant_20 = STATIC_CONS(float_constant_12,list_constant_72);
    float_constant_1 = STATIC_FLOAT(1.0);
    list_constant_21 = STATIC_CONS(float_constant_1,list_constant_72);
    list_constant_22 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)50L),Qfeet);
    Qupdate_frame_status_and_notes_for_printer_setup = 
	    STATIC_SYMBOL("UPDATE-FRAME-STATUS-AND-NOTES-FOR-PRINTER-SETUP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_frame_status_and_notes_for_printer_setup,
	    STATIC_FUNCTION(update_frame_status_and_notes_for_printer_setup,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qupdate_frame_status_and_notes_for_printer_setup);
    set_get(Qprinter_setup,Qupdate_frame_status_and_notes,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_frame_status_and_notes),
	    Qclasses_which_define);
    temp = CONS(Qprinter_setup,temp_1);
    mutate_global_property(Qupdate_frame_status_and_notes,temp,
	    Qclasses_which_define);
    float_constant_13 = STATIC_FLOAT(0.1875);
    list_constant_73 = STATIC_CONS(float_constant_13,list_constant_72);
    float_constant_14 = STATIC_FLOAT(0.1876);
    list_constant_74 = STATIC_CONS(float_constant_14,list_constant_72);
    list_constant_75 = STATIC_LIST((SI_Long)4L,list_constant_20,
	    list_constant_73,list_constant_20,list_constant_74);
    Postscript_paper_margins = list_constant_75;
    string_constant_185 = 
	    STATIC_STRING("1v1m83-2Cy1m83-Hy83-2Dy1m83-2Dy1m9k83Csy1m83-2Dy1m9k83-ZLy1m83-2Dy1m9k83-Lpy1m83-2Dy1m9k83-Lqy1m83-2Dy1m9k83-Mny1m83-2Dy1m9k83-U");
    string_constant_186 = 
	    STATIC_STRING("Py1m83-2Dy1m9k83-Tpy1m83-2Dy1m9k83-eiy1m83-2Dy1m9k83-ejy1m83-2Dy1m9k83-ery");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_185,
	    string_constant_186)));
    list_constant_77 = STATIC_LIST((SI_Long)2L,Qinch,Qinches);
    list_constant_78 = STATIC_LIST((SI_Long)2L,Qcentimeter,Qcentimeters);
    list_constant_76 = STATIC_CONS(Qfeet,Qnil);
    list_constant_79 = STATIC_CONS(Qfoot,list_constant_76);
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    Qmeters = STATIC_SYMBOL("METERS",AB_package);
    list_constant_80 = STATIC_LIST((SI_Long)2L,Qmeter,Qmeters);
    list_constant_81 = STATIC_LIST((SI_Long)2L,Qmillimeter,Qmillimeters);
    list_constant_23 = STATIC_LIST((SI_Long)5L,list_constant_77,
	    list_constant_78,list_constant_79,list_constant_80,
	    list_constant_81);
    string_constant_187 = STATIC_STRING("1l1n83EVy1n83AWy1m9k83-Zy838+y1mln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_187));
    string_constant_188 = 
	    STATIC_STRING("1l1n83AWy1o1m9k83*qy1m9k83-ncy1m9k83-Py83-1iy2l83AWyo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_188));
    string_constant_189 = 
	    STATIC_STRING("1l1n838+y1o1m9k83*xy1m9k83t4y1m9k83-Py83-1gy2l838+yo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_189));
    string_constant_190 = 
	    STATIC_STRING("1m1m83-1iy1m9k83-nXy1n83-1iy1p83-Hy1m9k83*qy1m9k83Fgy1m9k83Xiy83-2Dy1mlp");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_190));
    string_constant_191 = 
	    STATIC_STRING("1n1m83-1gy1m9k837ny1m83-1gy1m9k83--Xy1m83-1gy1m9k83-VAy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_191));
    string_constant_192 = 
	    STATIC_STRING("1n1n83EWy1m9k83EPy83EPy1n83EWy1m1m9k83-Sey1m9k83EPy83-Svy1n83EWy1m9k83-bey83-bey");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_192));
    string_constant_10 = 
	    STATIC_STRING("Workspace scale must be between 5 and 25000.");
    Qcompile_printer_translation_details_for_slot = 
	    STATIC_SYMBOL("COMPILE-PRINTER-TRANSLATION-DETAILS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_printer_translation_details_for_slot,
	    STATIC_FUNCTION(compile_printer_translation_details_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qprinter_translation_details,
	    SYMBOL_FUNCTION(Qcompile_printer_translation_details_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qprinter_translation_details,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_193 = 
	    STATIC_STRING("1v1n83ESy1v83EGy1m9k83-Zy83EFy1m9k83-Zy83DOy1m9k83-Zy83FTy1m9k83-Zy83Eoy1m9k83-Zy83B*y1qlnprtv1n83EGy1o1m9k83-iHy1m9k83nBy1m9k83");
    string_constant_194 = 
	    STATIC_STRING("-Py83-8ey2l83EGyo1n83-8ey1n83-2Cy1m9k83*ty83-2Cy1n83J2yln1n83EFy1o1m9k83-iHy1m9k83-hwy1m9k83-Py83-iIy2l83EFyo1m83-iIy1m9k83EOy1m");
    string_constant_195 = 
	    STATIC_STRING("83-iIy1m9k83-cDy1n83DOy1m1m9k83*hy83-djy2l83DOym1n83FTy1m1m9k83hy83-djy2l83FTym1n83Eoy1m1m9k83-by83-djy2l83Eoym1n83B*y1m1m9k83gy");
    string_constant_196 = 
	    STATIC_STRING("83-djy2l83B*ym1n83-djy1n1m9k83-diy1m9k83-Py83-2Cyn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_193,
	    string_constant_194,string_constant_195,string_constant_196)));
    string_constant_197 = 
	    STATIC_STRING("1z1m83-8ey1m9k83DPy1m83-8ey1m9k83-cSy1m83-8ey1m9k83-cJy1m83-8ey1m9k83-Isy1m83-8ey1m9k83-Ity1m83-8ey1m9k83-Iuy1m83-8ey1m9k83-Ivy1");
    string_constant_198 = 
	    STATIC_STRING("m83-8ey1m9k83-Iwy1m83-8ey1m9k83-Ixy1m83-8ey1m9k83-KMy1m83-8ey1m9k83-KNy1m83-8ey1m9k83-KOy1m83-8ey1m9k83-KPy1m83-8ey1m9k83-KQy1m8");
    string_constant_199 = STATIC_STRING("3-8ey1m9k83-KRy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_197,
	    string_constant_198,string_constant_199)));
    string_constant_200 = 
	    STATIC_STRING("1o1n83EUy1p83F9y1m9k83-Zy83F8y1m9k83-Zy83ERy1nlnp1n83F9y1p1m9k83-qSy1m9k83-Tuy1m9k83-sJy1m9k83-Py83-Uy2l83F9yp1n83F8y1q1m9k83-qR");
    string_constant_201 = 
	    STATIC_STRING("y1m9k83LLy1m9k83=3y1m9k83-jcy1m9k83-Py83Ky2l83F8yq1n83ERy1o1m9k83-jcy1m9k83-Yuy1m9k83-Py83-Uy2l83ERyo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_200,
	    string_constant_201)));
    string_constant_11 = STATIC_STRING(";~%");
    Kfirst = STATIC_SYMBOL("FIRST",Pkeyword);
    string_constant_12 = STATIC_STRING("~A:");
    Qlinear_measure = STATIC_SYMBOL("LINEAR-MEASURE",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)22L,Qworkspace_scaling,
	    Qworkspace_scaling,Qcolor_conversion,Qsymbol,Qpaper_size,
	    Qpaper_size,Qpaper_orientation,Qsymbol,Qleft_margin,
	    Qlinear_measure,Qtop_margin,Qlinear_measure,Qright_margin,
	    Qlinear_measure,Qbottom_margin,Qlinear_measure,
	    Qspooled_filename_template,Qstring,Qspool_file_to_printer,
	    Qyes_or_no,Qprinter_identification,Qstring);
    string_constant_13 = STATIC_STRING("~( ~S~)");
    string_constant_14 = STATIC_STRING("~( ~d ~s by ~d ~s~)");
    string_constant_15 = STATIC_STRING(" ~S");
    string_constant_16 = STATIC_STRING(" yes");
    string_constant_17 = STATIC_STRING(" no");
    string_constant_18 = STATIC_STRING(" ~(~S ~S~)");
    string_constant_19 = STATIC_STRING("~( ~S workspace units per ~S~)");
    Qin = STATIC_SYMBOL("IN",AB_package);
    Qft = STATIC_SYMBOL("FT",AB_package);
    float_constant_2 = STATIC_FLOAT(12.0);
    float_constant_3 = STATIC_FLOAT(39.37);
    float_constant_4 = STATIC_FLOAT(0.3937);
    float_constant_5 = STATIC_FLOAT(0.03937);
    Qwrite_printer_translation_details_from_slot = 
	    STATIC_SYMBOL("WRITE-PRINTER-TRANSLATION-DETAILS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_printer_translation_details_from_slot,
	    STATIC_FUNCTION(write_printer_translation_details_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qprinter_translation_details,
	    SYMBOL_FUNCTION(Qwrite_printer_translation_details_from_slot),
	    Qslot_value_writer);
    Qwrite_printer_page_layout_from_slot = 
	    STATIC_SYMBOL("WRITE-PRINTER-PAGE-LAYOUT-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_printer_page_layout_from_slot,
	    STATIC_FUNCTION(write_printer_page_layout_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qprinter_page_layout,
	    SYMBOL_FUNCTION(Qwrite_printer_page_layout_from_slot),
	    Qslot_value_writer);
    Qwrite_printer_spooling_details_from_slot = 
	    STATIC_SYMBOL("WRITE-PRINTER-SPOOLING-DETAILS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_printer_spooling_details_from_slot,
	    STATIC_FUNCTION(write_printer_spooling_details_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qprinter_spooling_details,
	    SYMBOL_FUNCTION(Qwrite_printer_spooling_details_from_slot),
	    Qslot_value_writer);
    list_constant_82 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_82,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_82,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_82,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_printing_file_format_from_slot = 
	    STATIC_SYMBOL("WRITE-PRINTING-FILE-FORMAT-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_printing_file_format_from_slot,
	    STATIC_FUNCTION(write_printing_file_format_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qprinting_file_format,
	    SYMBOL_FUNCTION(Qwrite_printing_file_format_from_slot),
	    Qslot_value_writer);
    SET_SYMBOL_VALUE_LOCATION(Qprint_spooling,Print_spooling);
    string_constant_202 = STATIC_STRING("PRINT-SPOOLING");
    if (Print_spooling == UNBOUND)
	Print_spooling = make_recursive_lock(2,Kname,string_constant_202);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qprint_spooling,
	    Qprinting,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qprint_spooling,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Printing_in_progress_p == UNBOUND)
	Printing_in_progress_p = Nil;
    if (Native_printer_information == UNBOUND)
	Native_printer_information = Nil;
    if (Printing_icon_current_region_index_qm == UNBOUND)
	Printing_icon_current_region_index_qm = Nil;
    if (Printing_graph_rendering_color_list_qm == UNBOUND)
	Printing_graph_rendering_color_list_qm = Nil;
    Qbitmap = STATIC_SYMBOL("BITMAP",AB_package);
    Qpformat = STATIC_SYMBOL("PFORMAT",AB_package);
    SET_SYMBOL_FUNCTION(Qpformat,STATIC_FUNCTION(pformat,NIL,TRUE,1,10));
    string_constant_20 = STATIC_STRING(" ~a");
    string_constant_21 = STATIC_STRING("~%g~D}def /g~D {~%");
    Qavailable_printing_conses = STATIC_SYMBOL("AVAILABLE-PRINTING-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_printing_conses,
	    Available_printing_conses);
    record_system_variable(Qavailable_printing_conses,Qprinting,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_printing_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-PRINTING-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_printing_conses_tail,
	    Available_printing_conses_tail);
    record_system_variable(Qavailable_printing_conses_tail,Qprinting,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_printing_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-PRINTING-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_printing_conses_vector,
	    Available_printing_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_83 = STATIC_CONS(Qnil,Qnil);
    list_constant_84 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qmake_thread_array,list_constant_83);
    record_system_variable(Qavailable_printing_conses_vector,Qprinting,
	    list_constant_84,Qnil,Qt,Qnil,Qnil);
    Qavailable_printing_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-PRINTING-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_printing_conses_tail_vector,
	    Available_printing_conses_tail_vector);
    record_system_variable(Qavailable_printing_conses_tail_vector,
	    Qprinting,list_constant_84,Qnil,Qt,Qnil,Qnil);
    Qprinting_cons_counter_vector = 
	    STATIC_SYMBOL("PRINTING-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprinting_cons_counter_vector,
	    Printing_cons_counter_vector);
    list_constant_85 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qprinting_cons_counter_vector,Qprinting,
	    list_constant_85,Qnil,Qt,Qnil,Qnil);
    Qprinting_cons_counter = STATIC_SYMBOL("PRINTING-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprinting_cons_counter,Printing_cons_counter);
    record_system_variable(Qprinting_cons_counter,Qprinting,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_printing_conses = 
	    STATIC_SYMBOL("OUTSTANDING-PRINTING-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_printing_conses,
	    STATIC_FUNCTION(outstanding_printing_conses,NIL,FALSE,0,0));
    Qprinting_cons_memory_usage = 
	    STATIC_SYMBOL("PRINTING-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qprinting_cons_memory_usage,
	    STATIC_FUNCTION(printing_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_203 = STATIC_STRING("1q83-jey9k83-jdy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_printing_conses);
    push_optimized_constant(Qprinting_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_203));
    if (Postscript_emit_integers_as_color_differences == UNBOUND)
	Postscript_emit_integers_as_color_differences = Nil;
    if (Postscript_emit_composite_object_without_name == UNBOUND)
	Postscript_emit_composite_object_without_name = Nil;
    string_constant_22 = STATIC_STRING(" /g~D");
    string_constant_23 = STATIC_STRING("~C");
    string_constant_24 = STATIC_STRING("def");
    Qpostscript_emit_icon_rendering_inner = 
	    STATIC_SYMBOL("POSTSCRIPT-EMIT-ICON-RENDERING-INNER",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_82,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)91L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qpostscript_emit_composite_object = 
	    STATIC_SYMBOL("POSTSCRIPT-EMIT-COMPOSITE-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qpostscript_emit_composite_object,
	    STATIC_FUNCTION(postscript_emit_composite_object,NIL,FALSE,1,1));
    string_constant_25 = STATIC_STRING(" g~D");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_line_drawing_for_printing_g2_struct = 
	    STATIC_SYMBOL("LINE-DRAWING-FOR-PRINTING-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qline_drawing_for_printing = STATIC_SYMBOL("LINE-DRAWING-FOR-PRINTING",
	    AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_line_drawing_for_printing_g2_struct,
	    Qline_drawing_for_printing,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qline_drawing_for_printing,
	    Qg2_defstruct_structure_name_line_drawing_for_printing_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_line_drawing_for_printing == UNBOUND)
	The_type_description_of_line_drawing_for_printing = Nil;
    string_constant_204 = 
	    STATIC_STRING("43Dy8m83kVy1n83kVy8n8k1l8n0000001l1n8y83-4ky1o83-26y83-Gny83-*4y83siykpk0k0");
    temp_1 = The_type_description_of_line_drawing_for_printing;
    The_type_description_of_line_drawing_for_printing = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_204));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_line_drawing_for_printing_g2_struct,
	    The_type_description_of_line_drawing_for_printing,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qline_drawing_for_printing,
	    The_type_description_of_line_drawing_for_printing,
	    Qtype_description_of_type);
    Qoutstanding_line_drawing_for_printing_count = 
	    STATIC_SYMBOL("OUTSTANDING-LINE-DRAWING-FOR-PRINTING-COUNT",
	    AB_package);
    Qline_drawing_for_printing_structure_memory_usage = 
	    STATIC_SYMBOL("LINE-DRAWING-FOR-PRINTING-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_205 = STATIC_STRING("1q83kVy8s83-cgy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_line_drawing_for_printing_count);
    push_optimized_constant(Qline_drawing_for_printing_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_205));
    Qchain_of_available_line_drawing_for_printings = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LINE-DRAWING-FOR-PRINTINGS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_line_drawing_for_printings,
	    Chain_of_available_line_drawing_for_printings);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_line_drawing_for_printings,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qline_drawing_for_printing_count = 
	    STATIC_SYMBOL("LINE-DRAWING-FOR-PRINTING-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qline_drawing_for_printing_count,
	    Line_drawing_for_printing_count);
    record_system_variable(Qline_drawing_for_printing_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_line_drawing_for_printings_vector == UNBOUND)
	Chain_of_available_line_drawing_for_printings_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qline_drawing_for_printing_structure_memory_usage,
	    STATIC_FUNCTION(line_drawing_for_printing_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_line_drawing_for_printing_count,
	    STATIC_FUNCTION(outstanding_line_drawing_for_printing_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_line_drawing_for_printing_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_line_drawing_for_printing,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qline_drawing_for_printing,
	    reclaim_structure_for_line_drawing_for_printing_1);
    array_constant_4 = STATIC_ARRAY(list_constant_82,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    Qpostscript_emit_line_drawing = 
	    STATIC_SYMBOL("POSTSCRIPT-EMIT-LINE-DRAWING",AB_package);
    list_constant_86 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_87 = STATIC_CONS(FIX((SI_Long)0L),list_constant_86);
    list_constant_26 = STATIC_CONS(Qnil,list_constant_87);
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    list_constant_88 = STATIC_CONS(Qnormal,list_constant_87);
    Qclockwise_90 = STATIC_SYMBOL("CLOCKWISE-90",AB_package);
    list_constant_89 = STATIC_LIST((SI_Long)3L,Qclockwise_90,
	    FIX((SI_Long)0L),FIX((SI_Long)90L));
    Qclockwise_180 = STATIC_SYMBOL("CLOCKWISE-180",AB_package);
    list_constant_90 = STATIC_LIST((SI_Long)3L,Qclockwise_180,
	    FIX((SI_Long)0L),FIX((SI_Long)180L));
    Qclockwise_270 = STATIC_SYMBOL("CLOCKWISE-270",AB_package);
    list_constant_91 = STATIC_LIST((SI_Long)3L,Qclockwise_270,
	    FIX((SI_Long)0L),FIX((SI_Long)270L));
    Qreflected = STATIC_SYMBOL("REFLECTED",AB_package);
    list_constant_92 = STATIC_LIST_STAR((SI_Long)3L,Qreflected,
	    FIX((SI_Long)1L),list_constant_86);
    Qreflected_clockwise_90 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-90",
	    AB_package);
    list_constant_93 = STATIC_LIST((SI_Long)3L,Qreflected_clockwise_90,
	    FIX((SI_Long)1L),FIX((SI_Long)-90L));
    Qreflected_clockwise_180 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-180",
	    AB_package);
    list_constant_94 = STATIC_LIST((SI_Long)3L,Qreflected_clockwise_180,
	    FIX((SI_Long)1L),FIX((SI_Long)-180L));
    Qreflected_clockwise_270 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-270",
	    AB_package);
    list_constant_95 = STATIC_LIST((SI_Long)3L,Qreflected_clockwise_270,
	    FIX((SI_Long)1L),FIX((SI_Long)-270L));
    list_constant_25 = STATIC_LIST((SI_Long)9L,list_constant_26,
	    list_constant_88,list_constant_89,list_constant_90,
	    list_constant_91,list_constant_92,list_constant_93,
	    list_constant_94,list_constant_95);
    string_constant_26 = STATIC_STRING("~% ~D ~D ");
    string_constant_27 = STATIC_STRING("~D ~D ");
    string_constant_28 = STATIC_STRING("~D ~D");
    string_constant_29 = STATIC_STRING("$ed");
    string_constant_30 = STATIC_STRING("~% g~D");
    SET_SYMBOL_FUNCTION(Qpostscript_emit_icon_rendering_inner,
	    STATIC_FUNCTION(postscript_emit_icon_rendering_inner,NIL,FALSE,
	    1,1));
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    list_constant_96 = STATIC_CONS(Qforeground,Qforeground);
    list_constant_27 = STATIC_CONS(list_constant_96,Qnil);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    SET_SYMBOL_FUNCTION(Qpostscript_emit_line_drawing,
	    STATIC_FUNCTION(postscript_emit_line_drawing,NIL,FALSE,1,1));
    Qpostscript_emit_graph_line_drawing = 
	    STATIC_SYMBOL("POSTSCRIPT-EMIT-GRAPH-LINE-DRAWING",AB_package);
    Qpostscript_emit_graph_rendering_inner = 
	    STATIC_SYMBOL("POSTSCRIPT-EMIT-GRAPH-RENDERING-INNER",AB_package);
    string_constant_31 = STATIC_STRING(" /g~Da{g~D");
    string_constant_32 = STATIC_STRING("cleanup-after-graph-rendering");
    string_constant_33 = STATIC_STRING("} def /g~Da");
    SET_SYMBOL_FUNCTION(Qpostscript_emit_graph_line_drawing,
	    STATIC_FUNCTION(postscript_emit_graph_line_drawing,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qpostscript_emit_graph_rendering_inner,
	    STATIC_FUNCTION(postscript_emit_graph_rendering_inner,NIL,
	    FALSE,1,1));
    Number_of_kanji_characters_per_microfont = FIX((SI_Long)256L);
    Use_substitute_for_non_latin_text_p = Nil;
    Substitute_character_for_non_latin_text = FIX((SI_Long)35L);
    list_constant_98 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)260L),
	    FIX((SI_Long)5L));
    list_constant_99 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)261L),
	    FIX((SI_Long)6L));
    list_constant_100 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)262L),
	    FIX((SI_Long)7L));
    list_constant_101 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)263L),
	    FIX((SI_Long)8L));
    list_constant_102 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)280L),
	    FIX((SI_Long)9L));
    list_constant_103 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)281L),
	    FIX((SI_Long)10L));
    list_constant_104 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)323L),
	    FIX((SI_Long)11L));
    list_constant_105 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)324L),
	    FIX((SI_Long)12L));
    list_constant_106 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)346L),
	    FIX((SI_Long)13L));
    list_constant_107 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)347L),
	    FIX((SI_Long)14L));
    list_constant_108 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)377L),
	    FIX((SI_Long)15L));
    list_constant_97 = STATIC_CONS(FIX((SI_Long)16L),Qnil);
    list_constant_109 = STATIC_CONS(FIX((SI_Long)378L),list_constant_97);
    list_constant_110 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)379L),
	    FIX((SI_Long)17L));
    list_constant_111 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)380L),
	    FIX((SI_Long)18L));
    list_constant_112 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)779L),
	    FIX((SI_Long)19L));
    list_constant_113 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)368L),
	    FIX((SI_Long)20L));
    list_constant_114 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)369L),
	    FIX((SI_Long)21L));
    list_constant_115 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)336L),
	    FIX((SI_Long)22L));
    list_constant_116 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)337L),
	    FIX((SI_Long)23L));
    list_constant_28 = STATIC_LIST((SI_Long)19L,list_constant_98,
	    list_constant_99,list_constant_100,list_constant_101,
	    list_constant_102,list_constant_103,list_constant_104,
	    list_constant_105,list_constant_106,list_constant_107,
	    list_constant_108,list_constant_109,list_constant_110,
	    list_constant_111,list_constant_112,list_constant_113,
	    list_constant_114,list_constant_115,list_constant_116);
    Qnon_graphic = STATIC_SYMBOL("NON-GRAPHIC",AB_package);
    Qordinary_space = STATIC_SYMBOL("ORDINARY-SPACE",AB_package);
    Qzero_width_space = STATIC_SYMBOL("ZERO-WIDTH-SPACE",AB_package);
    Qnon_spacing_mark = STATIC_SYMBOL("NON-SPACING-MARK",AB_package);
    Qmark = STATIC_SYMBOL("MARK",AB_package);
    Qab_font = STATIC_SYMBOL("AB-FONT",AB_package);
    string_constant_34 = STATIC_STRING("[");
    string_constant_35 = STATIC_STRING("~d");
    string_constant_36 = STATIC_STRING("~%");
    string_constant_37 = STATIC_STRING(" ");
    string_constant_38 = STATIC_STRING("]");
    string_constant_39 = STATIC_STRING("~%% Define Fonts.~%");
    Qblob18 = STATIC_SYMBOL("BLOB18",AB_package);
    string_constant_40 = STATIC_STRING("$br");
    Qroman = STATIC_SYMBOL("ROMAN",AB_package);
    string_constant_41 = STATIC_STRING("$bs");
    string_constant_42 = STATIC_STRING("$bu");
    string_constant_43 = STATIC_STRING("~%/microfont-encoding-vector[");
    string_constant_44 = STATIC_STRING("/c~D");
    string_constant_45 = STATIC_STRING("]def");
    string_constant_46 = STATIC_STRING("~%/kanji-dictionary ~D dict def");
    string_constant_47 = STATIC_STRING("~%% Setup Kanji Fonts");
    string_constant_48 = STATIC_STRING("~%kanji-dictionary begin");
    string_constant_49 = STATIC_STRING("EXTRA~a");
    string_constant_50 = STATIC_STRING("~%~(/~A~) begin-kanji-font");
    string_constant_51 = STATIC_STRING("~%~(  /k~D ~D begin-kanji-microfont");
    string_constant_52 = STATIC_STRING("  % ~D");
    string_constant_53 = STATIC_STRING("~%  /k~D ~D end-kanji-microfont");
    string_constant_54 = STATIC_STRING("~%  /k~D ~D begin-kanji-microfont");
    string_constant_55 = STATIC_STRING("~%~(  /k~D ~D end-kanji-microfont");
    string_constant_56 = STATIC_STRING("~%~(/~A~) end-kanji-font");
    string_constant_57 = STATIC_STRING("~%end");
    string_constant_58 = 
	    STATIC_STRING("~%/corresponding-kanji-font ~D dict def");
    string_constant_59 = STATIC_STRING("~%~(/~S /~A~)");
    Qcorresponding_kanji_font_name_and_magnification = 
	    STATIC_SYMBOL("CORRESPONDING-KANJI-FONT-NAME-AND-MAGNIFICATION",
	    AB_package);
    string_constant_60 = STATIC_STRING(" ~D ~D def-kanji-correspondence");
    Qcorresponding_cyrillic_font_name_and_magnification = 
	    STATIC_SYMBOL("CORRESPONDING-CYRILLIC-FONT-NAME-AND-MAGNIFICATION",
	    AB_package);
    Qslavic16 = STATIC_SYMBOL("SLAVIC16",AB_package);
    list_constant_29 = STATIC_CONS(Qslavic16,Qnil);
    Qcorresponding_hebrew_font_name_and_magnification = 
	    STATIC_SYMBOL("CORRESPONDING-HEBREW-FONT-NAME-AND-MAGNIFICATION",
	    AB_package);
    Qhebrew16 = STATIC_SYMBOL("HEBREW16",AB_package);
    list_constant_30 = STATIC_CONS(Qhebrew16,Qnil);
    Qcorresponding_thai_font_name_and_magnification = 
	    STATIC_SYMBOL("CORRESPONDING-THAI-FONT-NAME-AND-MAGNIFICATION",
	    AB_package);
    Qthai16 = STATIC_SYMBOL("THAI16",AB_package);
    list_constant_31 = STATIC_CONS(Qthai16,Qnil);
    Qkanji16 = STATIC_SYMBOL("KANJI16",AB_package);
    list_constant_32 = STATIC_CONS(Qkanji16,Qnil);
    string_constant_61 = STATIC_STRING("~%   /c~D");
    string_constant_62 = STATIC_STRING(" ~D");
    string_constant_63 = STATIC_STRING(" ~D ~D");
    string_constant_64 = STATIC_STRING("~a");
    string_constant_65 = STATIC_STRING(" def-kanji-character");
    array_constant_5 = STATIC_ARRAY(list_constant_82,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)57344L);
    string_constant_66 = STATIC_STRING("<");
    string_constant_67 = STATIC_STRING(">");
    list_constant_117 = STATIC_LIST((SI_Long)8L,FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L));
    list_constant_118 = STATIC_LIST_STAR((SI_Long)32L,FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    list_constant_117);
    list_constant_119 = STATIC_LIST_STAR((SI_Long)32L,FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    list_constant_118);
    list_constant_120 = STATIC_LIST_STAR((SI_Long)32L,FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    list_constant_119);
    list_constant_121 = STATIC_LIST_STAR((SI_Long)32L,FIX((SI_Long)169L),
	    FIX((SI_Long)144L),FIX((SI_Long)126L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    list_constant_120);
    list_constant_122 = STATIC_LIST_STAR((SI_Long)32L,FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)228L),FIX((SI_Long)225L),FIX((SI_Long)231L),
	    FIX((SI_Long)226L),FIX((SI_Long)233L),FIX((SI_Long)234L),
	    FIX((SI_Long)232L),FIX((SI_Long)236L),FIX((SI_Long)237L),
	    FIX((SI_Long)238L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)224L),FIX((SI_Long)241L),FIX((SI_Long)246L),
	    FIX((SI_Long)243L),FIX((SI_Long)244L),FIX((SI_Long)229L),
	    FIX((SI_Long)223L),FIX((SI_Long)248L),FIX((SI_Long)252L),
	    FIX((SI_Long)250L),FIX((SI_Long)156L),FIX((SI_Long)230L),
	    FIX((SI_Long)242L),FIX((SI_Long)249L),FIX((SI_Long)144L),
	    list_constant_121);
    list_constant_123 = STATIC_LIST_STAR((SI_Long)32L,FIX((SI_Long)187L),
	    FIX((SI_Long)191L),FIX((SI_Long)64L),FIX((SI_Long)196L),
	    FIX((SI_Long)193L),FIX((SI_Long)199L),FIX((SI_Long)194L),
	    FIX((SI_Long)201L),FIX((SI_Long)202L),FIX((SI_Long)200L),
	    FIX((SI_Long)204L),FIX((SI_Long)205L),FIX((SI_Long)206L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)192L),
	    FIX((SI_Long)209L),FIX((SI_Long)214L),FIX((SI_Long)211L),
	    FIX((SI_Long)212L),FIX((SI_Long)197L),FIX((SI_Long)144L),
	    FIX((SI_Long)216L),FIX((SI_Long)220L),FIX((SI_Long)218L),
	    FIX((SI_Long)150L),FIX((SI_Long)198L),FIX((SI_Long)210L),
	    FIX((SI_Long)217L),FIX((SI_Long)144L),FIX((SI_Long)92L),
	    list_constant_122);
    list_constant_124 = STATIC_LIST_STAR((SI_Long)32L,FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)161L),FIX((SI_Long)144L),
	    FIX((SI_Long)163L),FIX((SI_Long)165L),FIX((SI_Long)162L),
	    FIX((SI_Long)134L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)128L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)235L),FIX((SI_Long)203L),
	    FIX((SI_Long)239L),FIX((SI_Long)207L),FIX((SI_Long)227L),
	    FIX((SI_Long)195L),FIX((SI_Long)245L),FIX((SI_Long)213L),
	    FIX((SI_Long)251L),FIX((SI_Long)219L),FIX((SI_Long)146L),
	    FIX((SI_Long)174L),FIX((SI_Long)171L),FIX((SI_Long)144L),
	    list_constant_123);
    list_constant_125 = STATIC_LIST_STAR((SI_Long)32L,FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    FIX((SI_Long)144L),FIX((SI_Long)144L),FIX((SI_Long)144L),
	    list_constant_124);
    Postscript_encoding_for_tilde_escape_characters = make_array(3,
	    add1(FIX((SI_Long)255L)),Kinitial_contents,list_constant_125);
    string_constant_68 = STATIC_STRING(" ~A");
    string_constant_69 = STATIC_STRING("~%(");
    string_constant_70 = STATIC_STRING(")");
    list_constant_33 = STATIC_LIST((SI_Long)10L,CHR('\n'),CHR('n'),
	    CHR('\r'),CHR('r'),CHR('\t'),CHR('t'),CHR('\b'),CHR('b'),
	    CHR('\f'),CHR('f'));
    string_constant_71 = STATIC_STRING("0");
    Qwrite_hex_table = STATIC_SYMBOL("WRITE-HEX-TABLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwrite_hex_table,Write_hex_table);
    SET_SYMBOL_VALUE(Qwrite_hex_table,array_constant_5);
    Postscript_emit_hex_byte_string = make_string(1,FIX((SI_Long)2L));
    Postscript_emit_rgb_string = make_string(1,FIX((SI_Long)6L));
    string_constant_72 = STATIC_STRING("~( /~a~)");
    if (Adding_from_graph_rendering_p == UNBOUND)
	Adding_from_graph_rendering_p = Nil;
    string_constant_73 = STATIC_STRING("$bw");
    string_constant_74 = STATIC_STRING("$bm");
    Kpaint_infered_from_xor = STATIC_SYMBOL("PAINT-INFERED-FROM-XOR",Pkeyword);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qblack,Qwhite);
    string_constant_75 = STATIC_STRING("~%/full-color-map[");
    string_constant_76 = STATIC_STRING("~%]def");
    string_constant_77 = STATIC_STRING("~%/gray-color-map[");
    string_constant_78 = STATIC_STRING("~%[");
    string_constant_79 = STATIC_STRING("~D");
    string_constant_80 = STATIC_STRING("]% ~D ~(~S~)");
    string_constant_81 = STATIC_STRING("~%[255 255 255]% ~D none");
    Qdefault_print_handler_for_icp_messages = 
	    STATIC_SYMBOL("DEFAULT-PRINT-HANDLER-FOR-ICP-MESSAGES",AB_package);
    SET_SYMBOL_FUNCTION(Qdefault_print_handler_for_icp_messages,
	    STATIC_FUNCTION(default_print_handler_for_icp_messages,NIL,
	    TRUE,0,16));
    string_constant_82 = STATIC_STRING("$bf");
    Qhandler_for_printing_scroll_rectangle_in_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-SCROLL-RECTANGLE-IN-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_scroll_rectangle_in_current_window,
	    STATIC_FUNCTION(handler_for_printing_scroll_rectangle_in_current_window,
	    NIL,FALSE,6,6));
    string_constant_83 = STATIC_STRING("$ef");
    Qhandler_for_printing_set_up_palette = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-SET-UP-PALETTE",AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_set_up_palette,
	    STATIC_FUNCTION(handler_for_printing_set_up_palette,NIL,FALSE,
	    2,2));
    string_constant_84 = STATIC_STRING("$co");
    Qhandler_for_printing_initialize_scratchpad_raster = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-INITIALIZE-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_initialize_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_initialize_scratchpad_raster,
	    NIL,FALSE,5,5));
    string_constant_85 = STATIC_STRING("$dk");
    Qhandler_for_printing_paint_solid_rectangle_in_current_scratchpad_raster 
	    = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-SOLID-RECTANGLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_solid_rectangle_in_current_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_solid_rectangle_in_current_scratchpad_raster,
	    NIL,FALSE,5,5));
    string_constant_86 = STATIC_STRING("$di");
    Qhandler_for_printing_paint_line_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-LINE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_line_in_current_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_line_in_current_scratchpad_raster,
	    NIL,FALSE,6,6));
    string_constant_87 = STATIC_STRING("$db");
    Qhandler_for_printing_paint_arc_or_circle_in_current_scratchpad_raster 
	    = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-ARC-OR-CIRCLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_arc_or_circle_in_current_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_arc_or_circle_in_current_scratchpad_raster,
	    NIL,FALSE,11,11));
    string_constant_88 = STATIC_STRING("$dc");
    Qhandler_for_printing_paint_filled_triangle_in_current_scratchpad_raster 
	    = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-FILLED-TRIANGLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_filled_triangle_in_current_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_filled_triangle_in_current_scratchpad_raster,
	    NIL,FALSE,7,7));
    Qhandler_for_printing_paint_filled_polygon_in_current_scratchpad_raster 
	    = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-FILLED-POLYGON-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_filled_polygon_in_current_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_filled_polygon_in_current_scratchpad_raster,
	    NIL,FALSE,2,2));
    string_constant_89 = STATIC_STRING("$dm");
    Qhandler_for_printing_paint_wide_line_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-WIDE-LINE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_wide_line_in_current_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_wide_line_in_current_scratchpad_raster,
	    NIL,FALSE,7,7));
    string_constant_90 = STATIC_STRING("$dj");
    Qhandler_for_printing_paint_point_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-POINT-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_point_in_current_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_point_in_current_scratchpad_raster,
	    NIL,FALSE,3,3));
    string_constant_91 = STATIC_STRING("gsave");
    string_constant_92 = STATIC_STRING("savectm");
    string_constant_93 = STATIC_STRING("clip-to-rectangle");
    string_constant_94 = STATIC_STRING("translate");
    string_constant_95 = STATIC_STRING("g~D");
    string_constant_96 = STATIC_STRING("restorectm");
    string_constant_97 = STATIC_STRING("grestore");
    Qhandler_for_printing_paint_icon_onto_graph_raster = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-ICON-ONTO-GRAPH-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_icon_onto_graph_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_icon_onto_graph_raster,
	    NIL,FALSE,8,8));
    Qemit_embedded_icon_layer_definition_1 = 
	    STATIC_SYMBOL("EMIT-EMBEDDED-ICON-LAYER-DEFINITION-1",AB_package);
    SET_SYMBOL_FUNCTION(Qemit_embedded_icon_layer_definition_1,
	    STATIC_FUNCTION(emit_embedded_icon_layer_definition_1,NIL,
	    FALSE,1,1));
    Qhandler_for_printing_paint_marker_onto_graph_raster = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-MARKER-ONTO-GRAPH-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_marker_onto_graph_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_marker_onto_graph_raster,
	    NIL,FALSE,4,4));
    Qhandler_for_printing_paint_icon_background_image_in_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-ICON-BACKGROUND-IMAGE-IN-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_icon_background_image_in_current_window,
	    STATIC_FUNCTION(handler_for_printing_paint_icon_background_image_in_current_window,
	    NIL,FALSE,17,17));
    Qhandler_for_printing_paint_image_in_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-IMAGE-IN-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_image_in_current_window,
	    STATIC_FUNCTION(handler_for_printing_paint_image_in_current_window,
	    NIL,FALSE,13,13));
    string_constant_98 = STATIC_STRING("/imagestring ~d string def~%");
    string_constant_99 = STATIC_STRING("div");
    string_constant_100 = STATIC_STRING("mul");
    string_constant_101 = STATIC_STRING("scale");
    string_constant_102 = STATIC_STRING(" [~d 0 0 ~d 0 0]~%");
    string_constant_103 = 
	    STATIC_STRING(" {currentfile imagestring readhexstring pop}~%");
    string_constant_104 = STATIC_STRING("false");
    string_constant_105 = STATIC_STRING("colorimage");
    string_constant_106 = STATIC_STRING("~%~%");
    string_constant_107 = STATIC_STRING("image");
    string_constant_108 = STATIC_STRING("{<");
    string_constant_109 = STATIC_STRING(">}~%");
    string_constant_110 = STATIC_STRING("$df");
    Qhandler_for_printing_paint_image_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-IMAGE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_image_in_current_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_image_in_current_scratchpad_raster,
	    NIL,FALSE,10,10));
    Qhandler_for_printing_change_image_palette_of_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-CHANGE-IMAGE-PALETTE-OF-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_change_image_palette_of_window,
	    STATIC_FUNCTION(handler_for_printing_change_image_palette_of_window,
	    NIL,FALSE,3,3));
    string_constant_111 = STATIC_STRING("$dl");
    Qhandler_for_printing_paint_solid_rectangle_in_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-SOLID-RECTANGLE-IN-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_solid_rectangle_in_current_window,
	    STATIC_FUNCTION(handler_for_printing_paint_solid_rectangle_in_current_window,
	    NIL,FALSE,5,5));
    string_constant_112 = STATIC_STRING("$w");
    Qhandler_for_printing_add_solid_rectangle_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ADD-SOLID-RECTANGLE-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_add_solid_rectangle_to_current_window,
	    STATIC_FUNCTION(handler_for_printing_add_solid_rectangle_to_current_window,
	    NIL,FALSE,6,6));
    string_constant_113 = STATIC_STRING("pop");
    string_constant_114 = STATIC_STRING("$u");
    Qhandler_for_printing_add_from_icon_rendering_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ADD-FROM-ICON-RENDERING-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_add_from_icon_rendering_to_current_window,
	    STATIC_FUNCTION(handler_for_printing_add_from_icon_rendering_to_current_window,
	    NIL,FALSE,10,10));
    string_constant_115 = STATIC_STRING("$x");
    Qhandler_for_printing_add_upward_sloping_line_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ADD-UPWARD-SLOPING-LINE-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_add_upward_sloping_line_to_current_window,
	    STATIC_FUNCTION(handler_for_printing_add_upward_sloping_line_to_current_window,
	    NIL,FALSE,10,10));
    string_constant_116 = STATIC_STRING("$s");
    Qhandler_for_printing_add_downward_sloping_line_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ADD-DOWNWARD-SLOPING-LINE-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_add_downward_sloping_line_to_current_window,
	    STATIC_FUNCTION(handler_for_printing_add_downward_sloping_line_to_current_window,
	    NIL,FALSE,10,10));
    string_constant_117 = STATIC_STRING("[]");
    string_constant_118 = STATIC_STRING("[~a ~a]");
    string_constant_119 = STATIC_STRING("[~a ~a ~a ~a]");
    string_constant_120 = STATIC_STRING("[~a ~a ~a ~a ~a ~a]");
    string_constant_121 = STATIC_STRING("$y");
    Qhandler_for_printing_add_wide_polyline_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ADD-WIDE-POLYLINE-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_add_wide_polyline_to_current_window,
	    STATIC_FUNCTION(handler_for_printing_add_wide_polyline_to_current_window,
	    NIL,FALSE,9,9));
    Qhandler_for_printing_add_polygon_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ADD-POLYGON-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_add_polygon_to_current_window,
	    STATIC_FUNCTION(handler_for_printing_add_polygon_to_current_window,
	    NIL,FALSE,9,9));
    Qhandler_for_printing_add_ellipse_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ADD-ELLIPSE-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_add_ellipse_to_current_window,
	    STATIC_FUNCTION(handler_for_printing_add_ellipse_to_current_window,
	    NIL,FALSE,12,12));
    Qhandler_for_printing_copy_from_tiling_pattern_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-COPY-FROM-TILING-PATTERN-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_copy_from_tiling_pattern_to_current_window,
	    STATIC_FUNCTION(handler_for_printing_copy_from_tiling_pattern_to_current_window,
	    NIL,FALSE,5,5));
    string_constant_122 = STATIC_STRING("$cp");
    string_constant_123 = STATIC_STRING("$v");
    Qhandler_for_printing_add_from_line_of_text_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ADD-FROM-LINE-OF-TEXT-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_add_from_line_of_text_to_current_window,
	    STATIC_FUNCTION(handler_for_printing_add_from_line_of_text_to_current_window,
	    NIL,FALSE,13,13));
    string_constant_124 = STATIC_STRING("$be");
    string_constant_125 = STATIC_STRING("$dz");
    string_constant_126 = STATIC_STRING("$bd");
    string_constant_127 = STATIC_STRING("$t");
    Qhandler_for_printing_add_from_graph_rendering_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ADD-FROM-GRAPH-RENDERING-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_add_from_graph_rendering_to_current_window,
	    STATIC_FUNCTION(handler_for_printing_add_from_graph_rendering_to_current_window,
	    NIL,FALSE,11,11));
    string_constant_128 = STATIC_STRING("$em");
    Qhandler_for_printing_update_graph_dateline = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-UPDATE-GRAPH-DATELINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_update_graph_dateline,
	    STATIC_FUNCTION(handler_for_printing_update_graph_dateline,NIL,
	    FALSE,3,3));
    string_constant_129 = STATIC_STRING("$el");
    Qhandler_for_printing_update_graph_data_extrema = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-UPDATE-GRAPH-DATA-EXTREMA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_update_graph_data_extrema,
	    STATIC_FUNCTION(handler_for_printing_update_graph_data_extrema,
	    NIL,FALSE,4,4));
    string_constant_130 = STATIC_STRING("$en");
    Qhandler_for_printing_update_ring_raster_for_graph_given_color_values 
	    = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_update_ring_raster_for_graph_given_color_values,
	    STATIC_FUNCTION(handler_for_printing_update_ring_raster_for_graph_given_color_values,
	    NIL,FALSE,2,2));
    string_constant_131 = STATIC_STRING("$dt");
    Qhandler_for_printing_clear_data_clipping_rectangles = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-CLEAR-DATA-CLIPPING-RECTANGLES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_clear_data_clipping_rectangles,
	    STATIC_FUNCTION(handler_for_printing_clear_data_clipping_rectangles,
	    NIL,FALSE,0,0));
    string_constant_132 = STATIC_STRING("$cy");
    string_constant_133 = STATIC_STRING("$cq");
    string_constant_134 = STATIC_STRING("$dd");
    Qhandler_for_printing_paint_from_line_of_text_to_current_scratchpad_raster 
	    = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PAINT-FROM-LINE-OF-TEXT-TO-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_paint_from_line_of_text_to_current_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_paint_from_line_of_text_to_current_scratchpad_raster,
	    NIL,FALSE,12,12));
    Qhandler_for_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster 
	    = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ORIENT-AND-PAINT-LINE-OF-TEXT-TO-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandler_for_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster,
	    STATIC_FUNCTION(handler_for_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster,
	    NIL,FALSE,16,16));
    Qfile_template_instance_counter = 
	    STATIC_SYMBOL("FILE-TEMPLATE-INSTANCE-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfile_template_instance_counter,
	    File_template_instance_counter);
    record_system_variable(Qfile_template_instance_counter,Qprinting,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qt);
    array_constant_7 = STATIC_ARRAY(list_constant_82,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_82,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    list_constant_35 = STATIC_LIST((SI_Long)2L,array_constant_7,
	    array_constant_8);
    Qstring_equalw = STATIC_SYMBOL("STRING-EQUALW",AB_package);
    SET_SYMBOL_FUNCTION(Qstring_equalw,STATIC_FUNCTION(string_equalw,NIL,
	    FALSE,2,2));
    Qinstantiate_file_template_for_printing = 
	    STATIC_SYMBOL("INSTANTIATE-FILE-TEMPLATE-FOR-PRINTING",AB_package);
    string_constant_135 = STATIC_STRING("print-*");
    string_constant_136 = STATIC_STRING("ps");
    array_constant_6 = STATIC_ARRAY(list_constant_82,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    string_constant_206 = STATIC_STRING("g2print");
    if (Platform_independent_print_spool_command_file_name == UNBOUND)
	Platform_independent_print_spool_command_file_name = 
		string_constant_206;
    Postscript_enable_multipage_legends = T;
    string_constant_137 = STATIC_STRING("%!PS-Adobe-3.0~a");
    string_constant_138 = STATIC_STRING(" EPSF-3.0");
    string_constant_139 = STATIC_STRING("~%%%Pages: ~d");
    string_constant_140 = STATIC_STRING("~%%%Title: Workspace ~a");
    string_constant_141 = STATIC_STRING("~%%%Creator: G2 ~a");
    string_constant_142 = STATIC_STRING("~%%%For: ~a");
    string_constant_143 = STATIC_STRING("~%%%CreationDate: ~a");
    string_constant_144 = STATIC_STRING("~%%%Orientation: ~(~a~)");
    string_constant_145 = STATIC_STRING("~%%%DocumentPaperSizes: ~(~a~)");
    string_constant_146 = STATIC_STRING("~%%%BoundingBox: ~a ~a ~a ~a");
    string_constant_147 = STATIC_STRING("~%%%EndComments");
    string_constant_148 = STATIC_STRING("~%% Define paper size.~%");
    string_constant_149 = STATIC_STRING("$bt");
    string_constant_150 = STATIC_STRING("$cb");
    string_constant_151 = STATIC_STRING("~%%%EndSetup");
    string_constant_152 = STATIC_STRING("~%~%%%Page: ~D ~D~%");
    string_constant_153 = STATIC_STRING("set-up-page");
    string_constant_154 = STATIC_STRING(" ~d ~d ~d draw-multipage-legend~%");
    string_constant_155 = STATIC_STRING("$ee");
    string_constant_156 = STATIC_STRING("~%end~%");
    string_constant_157 = STATIC_STRING("~%~%%%Trailer");
    string_constant_158 = STATIC_STRING("~%~%%%Pages: ~D");
    string_constant_159 = STATIC_STRING("~%~%%%EOF");
    Qnative = STATIC_SYMBOL("NATIVE",AB_package);
    string_constant_160 = STATIC_STRING("showpage~%");
    float_constant_6 = STATIC_FLOAT(7.2);
    float_constant_7 = STATIC_FLOAT(720.0);
    Qbackground_processes = STATIC_SYMBOL("BACKGROUND-PROCESSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbackground_processes,Background_processes);
    record_system_variable(Qbackground_processes,Qprinting,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qbackground_processes_task = STATIC_SYMBOL("BACKGROUND-PROCESSES-TASK",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbackground_processes_task,
	    Background_processes_task);
    record_system_variable(Qbackground_processes_task,Qprinting,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    if (Current_background_process == UNBOUND)
	Current_background_process = Nil;
    Qdescription_of_process = STATIC_SYMBOL("DESCRIPTION-OF-PROCESS",
	    AB_package);
    Description_of_process_prop = Qdescription_of_process;
    Qg2_defstruct_structure_name_process_description_g2_struct = 
	    STATIC_SYMBOL("PROCESS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qprocess_description = STATIC_SYMBOL("PROCESS-DESCRIPTION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_process_description_g2_struct,
	    Qprocess_description,Qab_name_of_unique_structure_type);
    mutate_global_property(Qprocess_description,
	    Qg2_defstruct_structure_name_process_description_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    Qg2_defstruct_structure_name_process_g2_struct = 
	    STATIC_SYMBOL("PROCESS-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qprocess = STATIC_SYMBOL("PROCESS",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_process_g2_struct,
	    Qprocess,Qab_name_of_unique_structure_type);
    mutate_global_property(Qprocess,
	    Qg2_defstruct_structure_name_process_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_process == UNBOUND)
	The_type_description_of_process = Nil;
    string_constant_207 = 
	    STATIC_STRING("43Dy8m839ny1n839ny8n8k1l8n0000001l1n8y83-57y0ksk0k0");
    temp_1 = The_type_description_of_process;
    The_type_description_of_process = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_207));
    mutate_global_property(Qg2_defstruct_structure_name_process_g2_struct,
	    The_type_description_of_process,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qprocess,The_type_description_of_process,
	    Qtype_description_of_type);
    Qoutstanding_process_count = STATIC_SYMBOL("OUTSTANDING-PROCESS-COUNT",
	    AB_package);
    Qprocess_structure_memory_usage = 
	    STATIC_SYMBOL("PROCESS-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_208 = STATIC_STRING("1q839ny8s83-kTy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_process_count);
    push_optimized_constant(Qprocess_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_208));
    Qchain_of_available_processs = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PROCESSS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_processs,
	    Chain_of_available_processs);
    record_system_variable(Qchain_of_available_processs,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qprocess_count = STATIC_SYMBOL("PROCESS-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprocess_count,Process_count);
    record_system_variable(Qprocess_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_processs_vector == UNBOUND)
	Chain_of_available_processs_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qprocess_structure_memory_usage,
	    STATIC_FUNCTION(process_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_process_count,
	    STATIC_FUNCTION(outstanding_process_count,NIL,FALSE,0,0));
    reclaim_structure_for_process_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_process,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qprocess,
	    reclaim_structure_for_process_1);
    Qwaiting = STATIC_SYMBOL("WAITING",AB_package);
    Qrunning = STATIC_SYMBOL("RUNNING",AB_package);
    Qdone = STATIC_SYMBOL("DONE",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qservice_background_processes = 
	    STATIC_SYMBOL("SERVICE-BACKGROUND-PROCESSES",AB_package);
    SET_SYMBOL_FUNCTION(Qservice_background_processes,
	    STATIC_FUNCTION(service_background_processes,NIL,FALSE,0,0));
    Qdead = STATIC_SYMBOL("DEAD",AB_package);
    string_constant_161 = 
	    STATIC_STRING("Unable to print because opening the output file (~S) failed.");
    string_constant_162 = 
	    STATIC_STRING("Unable to print because the print file template was bad.");
    string_constant_163 = 
	    STATIC_STRING("Unable to print because the paper size in the printer-setup system table is invalid.");
    string_constant_164 = 
	    string_append2(STATIC_STRING("Unable to print.  ~\n                No available file name was found after trying ten variations ~\n                   of the filename suggested in the printer-setup system tab"),
	    STATIC_STRING("le.  ~\n                You may need to delete old print files.  ~\n                If you try again ten more names will be tried."));
    Qstored_raster_type_for_window = 
	    STATIC_SYMBOL("STORED-RASTER-TYPE-FOR-WINDOW",AB_package);
    Qscratchpad_raster_type_for_window = 
	    STATIC_SYMBOL("SCRATCHPAD-RASTER-TYPE-FOR-WINDOW",AB_package);
    Qtype_of_gensym_window = STATIC_SYMBOL("TYPE-OF-GENSYM-WINDOW",AB_package);
    Qwidth_of_window_border = STATIC_SYMBOL("WIDTH-OF-WINDOW-BORDER",
	    AB_package);
    Qpane_layout = STATIC_SYMBOL("PANE-LAYOUT",AB_package);
    Qcolor_description_plist_qm = 
	    STATIC_SYMBOL("COLOR-DESCRIPTION-PLIST\?",AB_package);
    if (Native_printing_icon_x_in_window == UNBOUND)
	Native_printing_icon_x_in_window = Nil;
    if (Native_printing_icon_y_in_window == UNBOUND)
	Native_printing_icon_y_in_window = Nil;
    Qnative_printing_default_icp_handler = 
	    STATIC_SYMBOL("NATIVE-PRINTING-DEFAULT-ICP-HANDLER",AB_package);
    Native_printing_icp_message_handler_array = make_array(3,
	    FIX((SI_Long)750L),Kinitial_element,
	    Qnative_printing_default_icp_handler);
    SET_SYMBOL_FUNCTION(Qnative_printing_default_icp_handler,
	    STATIC_FUNCTION(native_printing_default_icp_handler,NIL,TRUE,0,
	    16));
    Qnative_printing_paint_solid_rectangle_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-SOLID-RECTANGLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_solid_rectangle_in_current_scratchpad_raster,
	    STATIC_FUNCTION(native_printing_paint_solid_rectangle_in_current_scratchpad_raster,
	    NIL,FALSE,5,5));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)32L)) = 
	    Qnative_printing_paint_solid_rectangle_in_current_scratchpad_raster;
    Qnative_printing_paint_line_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-LINE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_line_in_current_scratchpad_raster,
	    STATIC_FUNCTION(native_printing_paint_line_in_current_scratchpad_raster,
	    NIL,FALSE,6,6));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)33L)) = 
	    Qnative_printing_paint_line_in_current_scratchpad_raster;
    Qnative_printing_paint_arc_or_circle_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-ARC-OR-CIRCLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_arc_or_circle_in_current_scratchpad_raster,
	    STATIC_FUNCTION(native_printing_paint_arc_or_circle_in_current_scratchpad_raster,
	    NIL,FALSE,11,11));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)34L)) = 
	    Qnative_printing_paint_arc_or_circle_in_current_scratchpad_raster;
    Qnative_printing_paint_filled_triangle_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-FILLED-TRIANGLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_filled_triangle_in_current_scratchpad_raster,
	    STATIC_FUNCTION(native_printing_paint_filled_triangle_in_current_scratchpad_raster,
	    NIL,FALSE,7,7));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)35L)) = 
	    Qnative_printing_paint_filled_triangle_in_current_scratchpad_raster;
    Qnative_printing_paint_filled_polygon_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-FILLED-POLYGON-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_filled_polygon_in_current_scratchpad_raster,
	    STATIC_FUNCTION(native_printing_paint_filled_polygon_in_current_scratchpad_raster,
	    NIL,FALSE,2,2));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)58L)) = 
	    Qnative_printing_paint_filled_polygon_in_current_scratchpad_raster;
    Qnative_printing_paint_wide_line_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-WIDE-LINE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_wide_line_in_current_scratchpad_raster,
	    STATIC_FUNCTION(native_printing_paint_wide_line_in_current_scratchpad_raster,
	    NIL,FALSE,7,7));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)36L)) = 
	    Qnative_printing_paint_wide_line_in_current_scratchpad_raster;
    Qnative_printing_paint_point_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-POINT-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_point_in_current_scratchpad_raster,
	    STATIC_FUNCTION(native_printing_paint_point_in_current_scratchpad_raster,
	    NIL,FALSE,3,3));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)37L)) = 
	    Qnative_printing_paint_point_in_current_scratchpad_raster;
    Qnative_printing_paint_image_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-IMAGE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_image_in_current_scratchpad_raster,
	    STATIC_FUNCTION(native_printing_paint_image_in_current_scratchpad_raster,
	    NIL,FALSE,10,10));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)186L)) = 
	    Qnative_printing_paint_image_in_current_scratchpad_raster;
    Qnative_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster 
	    = 
	    STATIC_SYMBOL("NATIVE-PRINTING-ORIENT-AND-PAINT-LINE-OF-TEXT-TO-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster,
	    STATIC_FUNCTION(native_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster,
	    NIL,FALSE,16,16));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)56L)) = 
	    Qnative_printing_orient_and_paint_line_of_text_to_current_scratchpad_raster;
    Qnative_printing_paint_from_line_of_text_to_current_scratchpad_raster 
	    = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-FROM-LINE-OF-TEXT-TO-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_from_line_of_text_to_current_scratchpad_raster,
	    STATIC_FUNCTION(native_printing_paint_from_line_of_text_to_current_scratchpad_raster,
	    NIL,FALSE,12,12));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)271L)) = 
	    Qnative_printing_paint_from_line_of_text_to_current_scratchpad_raster;
    Qnative_printing_add_from_icon_rendering_to_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-ADD-FROM-ICON-RENDERING-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_add_from_icon_rendering_to_current_window,
	    STATIC_FUNCTION(native_printing_add_from_icon_rendering_to_current_window,
	    NIL,FALSE,10,10));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)43L)) = 
	    Qnative_printing_add_from_icon_rendering_to_current_window;
    Qnative_printing_add_from_line_of_text_to_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-ADD-FROM-LINE-OF-TEXT-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_add_from_line_of_text_to_current_window,
	    STATIC_FUNCTION(native_printing_add_from_line_of_text_to_current_window,
	    NIL,FALSE,13,13));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)47L)) = 
	    Qnative_printing_add_from_line_of_text_to_current_window;
    Qnative_printing_paint_solid_rectangle_in_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-SOLID-RECTANGLE-IN-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_solid_rectangle_in_current_window,
	    STATIC_FUNCTION(native_printing_paint_solid_rectangle_in_current_window,
	    NIL,FALSE,5,5));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)41L)) = 
	    Qnative_printing_paint_solid_rectangle_in_current_window;
    Qnative_printing_add_solid_rectangle_to_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-ADD-SOLID-RECTANGLE-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_add_solid_rectangle_to_current_window,
	    STATIC_FUNCTION(native_printing_add_solid_rectangle_to_current_window,
	    NIL,FALSE,6,6));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)42L)) = 
	    Qnative_printing_add_solid_rectangle_to_current_window;
    Qnative_printing_add_upward_sloping_line_to_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-ADD-UPWARD-SLOPING-LINE-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_add_upward_sloping_line_to_current_window,
	    STATIC_FUNCTION(native_printing_add_upward_sloping_line_to_current_window,
	    NIL,FALSE,10,10));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)44L)) = 
	    Qnative_printing_add_upward_sloping_line_to_current_window;
    Qnative_printing_add_downward_sloping_line_to_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-ADD-DOWNWARD-SLOPING-LINE-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_add_downward_sloping_line_to_current_window,
	    STATIC_FUNCTION(native_printing_add_downward_sloping_line_to_current_window,
	    NIL,FALSE,10,10));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)45L)) = 
	    Qnative_printing_add_downward_sloping_line_to_current_window;
    Qnative_printing_add_wide_polyline_to_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-ADD-WIDE-POLYLINE-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_add_wide_polyline_to_current_window,
	    STATIC_FUNCTION(native_printing_add_wide_polyline_to_current_window,
	    NIL,FALSE,9,9));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)366L)) = 
	    Qnative_printing_add_wide_polyline_to_current_window;
    Qnative_printing_add_polygon_to_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-ADD-POLYGON-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_add_polygon_to_current_window,
	    STATIC_FUNCTION(native_printing_add_polygon_to_current_window,
	    NIL,FALSE,9,9));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)571L)) = 
	    Qnative_printing_add_polygon_to_current_window;
    Qnative_printing_add_ellipse_to_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-ADD-ELLIPSE-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_add_ellipse_to_current_window,
	    STATIC_FUNCTION(native_printing_add_ellipse_to_current_window,
	    NIL,FALSE,12,12));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)572L)) = 
	    Qnative_printing_add_ellipse_to_current_window;
    Qnative_printing_copy_from_tiling_pattern_to_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-COPY-FROM-TILING-PATTERN-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_copy_from_tiling_pattern_to_current_window,
	    STATIC_FUNCTION(native_printing_copy_from_tiling_pattern_to_current_window,
	    NIL,FALSE,5,5));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)46L)) = 
	    Qnative_printing_copy_from_tiling_pattern_to_current_window;
    Qnative_printing_paint_image_in_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-IMAGE-IN-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_image_in_current_window,
	    STATIC_FUNCTION(native_printing_paint_image_in_current_window,
	    NIL,FALSE,13,13));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)185L)) = 
	    Qnative_printing_paint_image_in_current_window;
    Qnative_printing_paint_icon_background_image_in_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-ICON-BACKGROUND-IMAGE-IN-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_icon_background_image_in_current_window,
	    STATIC_FUNCTION(native_printing_paint_icon_background_image_in_current_window,
	    NIL,FALSE,17,17));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)191L)) = 
	    Qnative_printing_paint_icon_background_image_in_current_window;
    Qnative_printing_update_graph_dateline = 
	    STATIC_SYMBOL("NATIVE-PRINTING-UPDATE-GRAPH-DATELINE",AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_update_graph_dateline,
	    STATIC_FUNCTION(native_printing_update_graph_dateline,NIL,
	    FALSE,3,3));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)153L)) = Qnative_printing_update_graph_dateline;
    Qnative_printing_clear_data_clipping_rectangles = 
	    STATIC_SYMBOL("NATIVE-PRINTING-CLEAR-DATA-CLIPPING-RECTANGLES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_clear_data_clipping_rectangles,
	    STATIC_FUNCTION(native_printing_clear_data_clipping_rectangles,
	    NIL,FALSE,0,0));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)162L)) = 
	    Qnative_printing_clear_data_clipping_rectangles;
    Qnative_printing_update_graph_data_extrema = 
	    STATIC_SYMBOL("NATIVE-PRINTING-UPDATE-GRAPH-DATA-EXTREMA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_update_graph_data_extrema,
	    STATIC_FUNCTION(native_printing_update_graph_data_extrema,NIL,
	    FALSE,4,4));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)154L)) = 
	    Qnative_printing_update_graph_data_extrema;
    Qnative_printing_update_ring_raster_for_graph_given_color_values = 
	    STATIC_SYMBOL("NATIVE-PRINTING-UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_update_ring_raster_for_graph_given_color_values,
	    STATIC_FUNCTION(native_printing_update_ring_raster_for_graph_given_color_values,
	    NIL,FALSE,2,2));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)157L)) = 
	    Qnative_printing_update_ring_raster_for_graph_given_color_values;
    Qnative_printing_add_from_graph_rendering_to_current_window = 
	    STATIC_SYMBOL("NATIVE-PRINTING-ADD-FROM-GRAPH-RENDERING-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_add_from_graph_rendering_to_current_window,
	    STATIC_FUNCTION(native_printing_add_from_graph_rendering_to_current_window,
	    NIL,FALSE,11,11));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)151L)) = 
	    Qnative_printing_add_from_graph_rendering_to_current_window;
    Qnative_printing_paint_icon_onto_graph_raster = 
	    STATIC_SYMBOL("NATIVE-PRINTING-PAINT-ICON-ONTO-GRAPH-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_printing_paint_icon_onto_graph_raster,
	    STATIC_FUNCTION(native_printing_paint_icon_onto_graph_raster,
	    NIL,FALSE,8,8));
    temp = Native_printing_icp_message_handler_array;
    SVREF(temp,FIX((SI_Long)165L)) = 
	    Qnative_printing_paint_icon_onto_graph_raster;
    float_constant_8 = STATIC_FLOAT(25.4);
    float_constant_9 = STATIC_FLOAT(2.54);
    float_constant_10 = STATIC_FLOAT(0.083);
    Qborder = STATIC_SYMBOL("BORDER",AB_package);
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    Qframe_style = STATIC_SYMBOL("FRAME-STYLE",AB_package);
    Qborder_width = STATIC_SYMBOL("BORDER-WIDTH",AB_package);
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qx11_window = STATIC_SYMBOL("X11-WINDOW",AB_package);
    Qadd_solid_rectangle = STATIC_SYMBOL("ADD-SOLID-RECTANGLE",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    string_constant_165 = STATIC_STRING("Unable to allocate ~dx~dx~d bitmap.");
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Qbackground_print_workspace = 
	    STATIC_SYMBOL("BACKGROUND-PRINT-WORKSPACE",AB_package);
    Qg2_defstruct_structure_name_background_print_workspace_process_state_block_g2_struct 
	    = 
	    STATIC_SYMBOL("BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qbackground_print_workspace_process_state_block = 
	    STATIC_SYMBOL("BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_background_print_workspace_process_state_block_g2_struct,
	    Qbackground_print_workspace_process_state_block,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qbackground_print_workspace_process_state_block,
	    Qg2_defstruct_structure_name_background_print_workspace_process_state_block_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_background_print_workspace_process_state_block 
	    == UNBOUND)
	The_type_description_of_background_print_workspace_process_state_block 
		= Nil;
    string_constant_209 = 
	    STATIC_STRING("43Dy8m83fHy1n83fHy8n8k1l8n0000001m1n8y83-2oy01m83My83-A3yk3-0yk0k0");
    temp_1 = 
	    The_type_description_of_background_print_workspace_process_state_block;
    The_type_description_of_background_print_workspace_process_state_block 
	    = load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_209));
    mutate_global_property(Qg2_defstruct_structure_name_background_print_workspace_process_state_block_g2_struct,
	    The_type_description_of_background_print_workspace_process_state_block,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qbackground_print_workspace_process_state_block,
	    The_type_description_of_background_print_workspace_process_state_block,
	    Qtype_description_of_type);
    Qoutstanding_background_print_workspace_process_state_block_count = 
	    STATIC_SYMBOL("OUTSTANDING-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK-COUNT",
	    AB_package);
    Qbackground_print_workspace_process_state_block_structure_memory_usage 
	    = 
	    STATIC_SYMBOL("BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_210 = STATIC_STRING("1q83fHy8s83-KUy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_background_print_workspace_process_state_block_count);
    push_optimized_constant(Qbackground_print_workspace_process_state_block_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_210));
    Qchain_of_available_background_print_workspace_process_state_blocks = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCKS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_background_print_workspace_process_state_blocks,
	    Chain_of_available_background_print_workspace_process_state_blocks);
    record_system_variable(Qchain_of_available_background_print_workspace_process_state_blocks,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qbackground_print_workspace_process_state_block_count = 
	    STATIC_SYMBOL("BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbackground_print_workspace_process_state_block_count,
	    Background_print_workspace_process_state_block_count);
    record_system_variable(Qbackground_print_workspace_process_state_block_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_background_print_workspace_process_state_blocks_vector 
	    == UNBOUND)
	Chain_of_available_background_print_workspace_process_state_blocks_vector 
		= make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qbackground_print_workspace_process_state_block_structure_memory_usage,
	    STATIC_FUNCTION(background_print_workspace_process_state_block_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_background_print_workspace_process_state_block_count,
	    STATIC_FUNCTION(outstanding_background_print_workspace_process_state_block_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_background_print_workspace_process_state_block_1 
	    = 
	    STATIC_FUNCTION(reclaim_structure_for_background_print_workspace_process_state_block,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qbackground_print_workspace_process_state_block,
	    reclaim_structure_for_background_print_workspace_process_state_block_1);
    Qexit = STATIC_SYMBOL("EXIT",AB_package);
    Qinvalid_blocks = STATIC_SYMBOL("INVALID-BLOCKS",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qdeleted = STATIC_SYMBOL("DELETED",AB_package);
    Qbegin = STATIC_SYMBOL("BEGIN",AB_package);
    Qend = STATIC_SYMBOL("END",AB_package);
    Qwork_on_background_print_workspace = 
	    STATIC_SYMBOL("WORK-ON-BACKGROUND-PRINT-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qwork_on_background_print_workspace,
	    STATIC_FUNCTION(work_on_background_print_workspace,NIL,FALSE,2,2));
    Qinitialize_background_print_workspace_process_state_block = 
	    STATIC_SYMBOL("INITIALIZE-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_background_print_workspace_process_state_block,
	    STATIC_FUNCTION(initialize_background_print_workspace_process_state_block,
	    NIL,FALSE,3,3));
    Qreclaim_background_print_workspace_process_state_block = 
	    STATIC_SYMBOL("RECLAIM-BACKGROUND-PRINT-WORKSPACE-PROCESS-STATE-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_background_print_workspace_process_state_block,
	    STATIC_FUNCTION(reclaim_background_print_workspace_process_state_block,
	    NIL,FALSE,1,1));
    make_process_description(Qbackground_print_workspace,
	    SYMBOL_FUNCTION(Qwork_on_background_print_workspace),
	    SYMBOL_FUNCTION(Qinitialize_background_print_workspace_process_state_block),
	    SYMBOL_FUNCTION(Qreclaim_background_print_workspace_process_state_block));
    string_constant_166 = STATIC_STRING("~a on ~a");
    string_constant_167 = STATIC_STRING("~s");
    string_constant_168 = 
	    STATIC_STRING("Begin printing ~NF to ~a at priority ~d.");
    string_constant_169 = 
	    STATIC_STRING("Begin printing ~NF to ~a at priority ~d.  ~a ~a ahead in queue.");
    string_constant_170 = STATIC_STRING("jobs");
    string_constant_171 = STATIC_STRING("job");
    string_constant_172 = STATIC_STRING("Printing workspace ~NF failed.");
    string_constant_173 = 
	    STATIC_STRING("The workspace being printed to ~a has been deleted.");
    string_constant_174 = STATIC_STRING("Finished printing ~NF to ~a.");
    string_constant_175 = 
	    STATIC_STRING("Finished printing ~NF to ~a.   ~a ~a remaining.");
    Qg2_ui_print_window = STATIC_SYMBOL("G2-UI-PRINT-WINDOW",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_print_window,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_ui_print_window,
	    STATIC_FUNCTION(g2_ui_print_window,NIL,FALSE,2,2));
}
