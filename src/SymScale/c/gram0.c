/* gram0.c
 * Input file:  grammar0.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram0.h"


static Object Qneutral_unit_of_measure;  /* neutral-unit-of-measure */

static Object Qsingular_unit_of_measure;  /* singular-unit-of-measure */

static Object Qplural_unit_of_measure;  /* plural-unit-of-measure */

/* ADD-UNITS-OF-MEASURE */
Object add_units_of_measure(list_of_symbols)
    Object list_of_symbols;
{
    Object symbol_or_pair, ab_loop_list_;

    x_note_fn_call(192,0);
    symbol_or_pair = Nil;
    ab_loop_list_ = list_of_symbols;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    symbol_or_pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SYMBOLP(symbol_or_pair)) {
	def_numeric_subtype(1,symbol_or_pair);
	add_kb_specific_symbol_token(symbol_or_pair,Qneutral_unit_of_measure);
    }
    else {
	def_numeric_subtype(2,CAR(symbol_or_pair),CDR(symbol_or_pair));
	def_numeric_subtype(1,CDR(symbol_or_pair));
	add_kb_specific_symbol_token(CAR(symbol_or_pair),
		Qsingular_unit_of_measure);
	add_kb_specific_symbol_token(CDR(symbol_or_pair),
		Qplural_unit_of_measure);
	mutate_kb_specific_property_value(CDR(symbol_or_pair),
		CAR(symbol_or_pair),
		Star_singular_of_numeric_data_type_star_kbprop);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qlong;               /* long */

/* CONVERT-SINGULAR-CONSTANT */
Object convert_singular_constant(pair)
    Object pair;
{
    Object symbol, cdr_new_value;

    x_note_fn_call(192,1);
    symbol = CDR(pair);
    cdr_new_value = EQ(symbol,Qnumber) ? T : Nil;
    if (cdr_new_value);
    else
	cdr_new_value = EQ(symbol,Qinteger) ? T : Nil;
    if (cdr_new_value);
    else
	cdr_new_value = EQ(symbol,Qfloat) ? T : Nil;
    if (cdr_new_value);
    else
	cdr_new_value = EQ(symbol,Qlong) ? T : Nil;
    if (cdr_new_value);
    else
	cdr_new_value = lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop);
    M_CDR(pair) = cdr_new_value;
    return VALUES_1(pair);
}

static Object Qseconds;            /* seconds */

static Object Qminute;             /* minute */

static Object Qminutes;            /* minutes */

static Object Qhour;               /* hour */

static Object Qhours;              /* hours */

static Object Qday;                /* day */

static Object Qdays;               /* days */

static Object Qweek;               /* week */

static Object Qweeks;              /* weeks */

static Object Qinterval_too_long;  /* interval-too-long */

/* CONVERT-INTERVAL-PHRASE */
Object convert_interval_phrase(phrase)
    Object phrase;
{
    Object number, unit, temp, interval_in_seconds;

    x_note_fn_call(192,2);
    number = CAR(phrase);
    unit = CDR(phrase);
    if (EQ(unit,Qsecond) || EQ(unit,Qseconds))
	temp = FIX((SI_Long)1L);
    else if (EQ(unit,Qminute) || EQ(unit,Qminutes))
	temp = FIX((SI_Long)60L);
    else if (EQ(unit,Qhour) || EQ(unit,Qhours))
	temp = FIX((SI_Long)3600L);
    else if (EQ(unit,Qday) || EQ(unit,Qdays))
	temp = FIX((SI_Long)86400L);
    else if (EQ(unit,Qweek) || EQ(unit,Qweeks))
	temp = FIX((SI_Long)604800L);
    else
	temp = Qnil;
    interval_in_seconds = star_f_safe(number,temp);
    if ( !TRUEP(interval_in_seconds) || FIXNUM_GT(interval_in_seconds,
	    Ten_years))
	return VALUES_2(Bad_phrase,Qinterval_too_long);
    else
	return phrase_cons(interval_in_seconds,Qseconds);
}

static Object Qfloat_array;        /* float-array */

/* CONVERT-QUANTITY-INTERVAL-PHRASE */
Object convert_quantity_interval_phrase(phrase)
    Object phrase;
{
    Object number, unit, conversion, interval_in_seconds_qm;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(192,3);
    number = CAR(phrase);
    unit = CDR(phrase);
    if (EQ(unit,Qsecond) || EQ(unit,Qseconds))
	conversion = FIX((SI_Long)1L);
    else if (EQ(unit,Qminute) || EQ(unit,Qminutes))
	conversion = FIX((SI_Long)60L);
    else if (EQ(unit,Qhour) || EQ(unit,Qhours))
	conversion = FIX((SI_Long)3600L);
    else if (EQ(unit,Qday) || EQ(unit,Qdays))
	conversion = FIX((SI_Long)86400L);
    else if (EQ(unit,Qweek) || EQ(unit,Qweeks))
	conversion = FIX((SI_Long)604800L);
    else
	conversion = Qnil;
    interval_in_seconds_qm = Nil;
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
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
	    aref_new_value = DFLOAT_ISAREF_1(number,(SI_Long)0L) * 
		    (double)IFIX(conversion);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    interval_in_seconds_qm = 
		    note_use_of_managed_float_in_phrase(new_float);
	    arg = DFLOAT_ISAREF_1(interval_in_seconds_qm,(SI_Long)0L);
	    arg_1 = 3.1536E+8;
	    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		interval_in_seconds_qm = Nil;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	interval_in_seconds_qm = star_f_safe(number,conversion);
	if (interval_in_seconds_qm && FIXNUM_GT(interval_in_seconds_qm,
		Ten_years))
	    interval_in_seconds_qm = Nil;
    }
    if (interval_in_seconds_qm)
	return phrase_cons(interval_in_seconds_qm,Qseconds);
    else
	return VALUES_2(Bad_phrase,Qinterval_too_long);
}

/* CONVERT-COMPOUND-INTERVAL */
Object convert_compound_interval(phrase)
    Object phrase;
{
    Object result_1;

    x_note_fn_call(192,4);
    result_1 = phrase_cons(FIXNUM_ADD(CAAR(phrase),CADR(phrase)),Qseconds);
    if (FIXNUM_GT(CAR(result_1),Ten_years))
	return VALUES_2(Bad_phrase,Qinterval_too_long);
    else
	return VALUES_1(result_1);
}

/* CONVERT-COMPOUND-QUANTITY-INTERVAL */
Object convert_compound_quantity_interval(phrase)
    Object phrase;
{
    Object value_1, value_2, result_qm, amf_available_array_cons_qm, amf_array;
    Object temp, temp_1, amf_result, new_float;
    char temp_2;
    double aref_new_value, gensymed_symbol, gensymed_symbol_1, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(192,5);
    value_1 = CAAR(phrase);
    value_2 = CADR(phrase);
    result_qm = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (FIXNUMP(value_1)) {
	    if (FIXNUMP(value_2))
		result_qm = FIXNUM_ADD(value_1,value_2);
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
		aref_new_value = (double)IFIX(value_1) + 
			DFLOAT_ISAREF_1(value_2,(SI_Long)0L);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		result_qm = note_use_of_managed_float_in_phrase(new_float);
	    }
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
	    gensymed_symbol = DFLOAT_ISAREF_1(value_1,(SI_Long)0L);
	    gensymed_symbol_1 = FIXNUMP(value_2) ? (double)IFIX(value_2) : 
		    DFLOAT_ISAREF_1(value_2,(SI_Long)0L);
	    aref_new_value = gensymed_symbol + gensymed_symbol_1;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    result_qm = note_use_of_managed_float_in_phrase(new_float);
	}
	temp_2 = FIXNUMP(result_qm) ? FIXNUM_LE(result_qm,Ten_years) : 
		TRUEP(Qnil);
	if (temp_2);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(result_qm) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(result_qm)) == (SI_Long)1L) {
	    arg = DFLOAT_ISAREF_1(result_qm,(SI_Long)0L);
	    arg_1 = 3.1536E+8;
	    temp_2 = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if ( !temp_2)
	    result_qm = Nil;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if (result_qm)
	return phrase_cons(result_qm,Qseconds);
    else
	return VALUES_2(Bad_phrase,Qinterval_too_long);
}

static Object array_constant;      /* # */

/* TWRITE-UNIX-TIME */
Object twrite_unix_time varargs_1(int, n)
{
    Object unix_time;
    Object subsecond_qm, second_1, minute, hour, date, month, year;
    char temp;
    double gensym_float_unix_time, arg, arg_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(192,6);
    INIT_ARGS_nonrelocating();
    unix_time = REQUIRED_ARG_nonrelocating();
    subsecond_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensym_float_unix_time = DFLOAT_ISAREF_1(unix_time,(SI_Long)0L);
	arg = gensym_float_unix_time;
	arg_1 = -2.147483648E+9;
	temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	if (temp);
	else {
	    arg = gensym_float_unix_time;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(N_2_to_31_plus_62_years);
	    temp = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	if (temp)
	    result = twrite_beginning_of_wide_string(array_constant,
		    FIX((SI_Long)26L));
	else {
	    result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(gensym_float_unix_time));
	    MVS_6(result,second_1,minute,hour,date,month,year);
	    result = print_decoded_time(subsecond_qm ? 
		    DOUBLE_TO_DOUBLE_FLOAT(gensym_float_unix_time - 
		    inline_ffloor_1(gensym_float_unix_time)) : second_1,
		    minute,hour,date,month,year);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qtime_stamp;         /* time-stamp */

/* WRITE-DATE-AND-TIME */
Object write_date_and_time(gensym_time)
    Object gensym_time;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(192,7);
    PUSH_SPECIAL_WITH_SYMBOL(Gensym_time,Qgensym_time,gensym_time,0);
      result = print_constant(2,FIXNUM_MINUS(Gensym_time,
	      Gensym_time_at_start),Qtime_stamp);
    POP_SPECIAL();
    return result;
}

/* RESTRICT-IF-SLOT-EDIT-FEATURE */
Object restrict_if_slot_edit_feature(parse,slot_edit_feature,reason)
    Object parse, slot_edit_feature, reason;
{
    Object type_of_slot_qm, feature_is_present_qm;

    x_note_fn_call(192,8);
    type_of_slot_qm = Current_edit_state ? ISVREF(Current_edit_state,
	    (SI_Long)9L) : Nil;
    feature_is_present_qm = type_of_slot_qm ? 
	    memq_function(slot_edit_feature,CDDR(type_of_slot_qm)) : Nil;
    if (feature_is_present_qm)
	return VALUES_2(Bad_phrase,reason);
    else
	return VALUES_1(parse);
}

/* RESTRICT-IF-NOT-SLOT-EDIT-FEATURE */
Object restrict_if_not_slot_edit_feature(parse,slot_edit_feature,reason)
    Object parse, slot_edit_feature, reason;
{
    Object type_of_slot_qm, feature_is_present_qm;

    x_note_fn_call(192,9);
    type_of_slot_qm = Current_edit_state ? ISVREF(Current_edit_state,
	    (SI_Long)9L) : Nil;
    feature_is_present_qm = type_of_slot_qm ? 
	    memq_function(slot_edit_feature,CDDR(type_of_slot_qm)) : Nil;
    if (feature_is_present_qm)
	return VALUES_1(parse);
    else
	return VALUES_2(Bad_phrase,reason);
}

static Object Qthis_rule;          /* this-rule */

static Object string_constant;     /* "`This rule' is only permitted within rules." */

static Object Qthis_procedure;     /* this-procedure */

static Object string_constant_1;   /* "`This procedure' is only permitted within procedures." */

static Object Qthis_procedure_invocation;  /* this-procedure-invocation */

static Object string_constant_2;   /* "`This procedure-invocation' is only permitted within procedures." */

static Object Qhas_a_current_value;  /* has-a-current-value */

static Object string_constant_3;   /* "`Has a current value' and `Has no current value' may not be applied to composite expressions." */

static Object Qe_designation;      /* e-designation */

static Object string_constant_4;   /* "`Every' is not permitted within procedures." */

static Object Qconditional_expression;  /* conditional-expression */

static Object string_constant_5;   /* "Conditional expressions within procedures must terminate in an `else' clause." */

static Object Qregion_cannot_be_a_color_or_metacolor;  /* region-cannot-be-a-color-or-metacolor */

static Object string_constant_6;   /* "A region cannot be a color or metacolor." */

static Object Qregion_cannot_be_the_symbol_copy;  /* region-cannot-be-the-symbol-copy */

static Object string_constant_7;   /* "A region cannot be the symbol COPY." */

static Object Qregion_cannot_be_the_symbol_inherited;  /* region-cannot-be-the-symbol-inherited */

static Object string_constant_8;   /* "A region cannot be the symbol INHERITED." */

static Object Qcolor_cannot_be_the_symbol_copy;  /* color-cannot-be-the-symbol-copy */

static Object string_constant_9;   /* "A color cannot be the symbol INHERITED." */

static Object string_constant_10;  /* "you cannot enter an interval longer than 10 years" */

static Object Qtoo_few_arguments;  /* too-few-arguments */

static Object string_constant_11;  /* "too few arguments" */

static Object Qtoo_many_arguments;  /* too-many-arguments */

static Object string_constant_12;  /* "too many arguments" */

static Object Qwrong_number_of_arguments;  /* wrong-number-of-arguments */

static Object string_constant_13;  /* "wrong number of arguments" */

static Object string_constant_14;  /* "`Otherwise' may be used only after at least one other case choice and only as the last choice." */

static Object Qcannot_replace_in_runtime_or_embedded_g2;  /* cannot-replace-in-runtime-or-embedded-g2 */

static Object string_constant_15;  /* "The replace feature is not available in runtime or embedded G2." */

static Object Qnon_object_must_be_passed_as_handle;  /* non-object-must-be-passed-as-handle */

static Object string_constant_16;  /* "This class is not a subclass of object and so must be passed `as handle'" */

static Object Qchange_nth_element_no_array_or_list;  /* change-nth-element-no-array-or-list */

static Object string_constant_17;  /* "The change element action must refer to a g2-array or g2-list.  Note that the array or list expression may need to be within parentheses." */

static Object Qreserved_java_word;  /* reserved-java-word */

static Object string_constant_18;  /* "" */

static Object string_constant_19;  /* "[Internal error in bad parse explanation.]" */

/* REASON-FOR-BAD-PARSE-AS-STRING */
Object reason_for_bad_parse_as_string(reason)
    Object reason;
{
    x_note_fn_call(192,10);
    if (EQ(reason,Qthis_rule))
	return VALUES_1(string_constant);
    else if (EQ(reason,Qthis_procedure))
	return VALUES_1(string_constant_1);
    else if (EQ(reason,Qthis_procedure_invocation))
	return VALUES_1(string_constant_2);
    else if (EQ(reason,Qhas_a_current_value))
	return VALUES_1(string_constant_3);
    else if (EQ(reason,Qe_designation))
	return VALUES_1(string_constant_4);
    else if (EQ(reason,Qconditional_expression))
	return VALUES_1(string_constant_5);
    else if (EQ(reason,Qregion_cannot_be_a_color_or_metacolor))
	return VALUES_1(string_constant_6);
    else if (EQ(reason,Qregion_cannot_be_the_symbol_copy))
	return VALUES_1(string_constant_7);
    else if (EQ(reason,Qregion_cannot_be_the_symbol_inherited))
	return VALUES_1(string_constant_8);
    else if (EQ(reason,Qcolor_cannot_be_the_symbol_copy))
	return VALUES_1(string_constant_9);
    else if (EQ(reason,Qinterval_too_long))
	return VALUES_1(string_constant_10);
    else if (EQ(reason,Qtoo_few_arguments))
	return VALUES_1(string_constant_11);
    else if (EQ(reason,Qtoo_many_arguments))
	return VALUES_1(string_constant_12);
    else if (EQ(reason,Qwrong_number_of_arguments))
	return VALUES_1(string_constant_13);
    else if (EQ(reason,Qotherwise))
	return VALUES_1(string_constant_14);
    else if (EQ(reason,Qcannot_replace_in_runtime_or_embedded_g2))
	return VALUES_1(string_constant_15);
    else if (EQ(reason,Qnon_object_must_be_passed_as_handle))
	return VALUES_1(string_constant_16);
    else if (EQ(reason,Qchange_nth_element_no_array_or_list))
	return VALUES_1(string_constant_17);
    else if (EQ(reason,Qreserved_java_word))
	return VALUES_1(string_constant_18);
    else if (STRINGP(reason) || INLINE_UNSIGNED_BYTE_16_VECTOR_P(reason) 
	    != (SI_Long)0L)
	return VALUES_1(reason);
    else
	return VALUES_1(string_constant_19);
}

/* PHRASE-FOR-CONSTANT-P */
Object phrase_for_constant_p(phrase)
    Object phrase;
{
    Object temp;

    x_note_fn_call(192,11);
    temp = phrase_number_p(phrase);
    if (temp);
    else
	temp = text_string_p(phrase);
    if (temp);
    else
	temp = CONSP(phrase) ? (EQ(M_CDR(phrase),Phrase_sequence_marker) ? 
		T : Nil) : Qnil;
    if (temp);
    else
	temp = CONSP(phrase) ? (EQ(M_CDR(phrase),Phrase_structure_marker) ?
		 T : Nil) : Qnil;
    if (temp);
    else
	temp = truth_value_phrase_p(phrase);
    if (temp);
    else
	temp = phrase_for_unit_of_measure_constant_p(phrase);
    return VALUES_1(temp);
}

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

/* REJECT-TRUTH-VALUE-AS-SYMBOL */
Object reject_truth_value_as_symbol(symbol_phrase)
    Object symbol_phrase;
{
    x_note_fn_call(192,12);
    if (EQ(symbol_phrase,Qtrue) || EQ(symbol_phrase,Qfalse))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(symbol_phrase);
}

static Object Qtruth_value;        /* truth-value */

/* PHRASE-FOR-UNIT-OF-MEASURE-CONSTANT-P */
Object phrase_for_unit_of_measure_constant_p(phrase)
    Object phrase;
{
    Object temp, gensymed_symbol;
    char temp_1;

    x_note_fn_call(192,13);
    if (CONSP(phrase) && phrase_number_p(M_CAR(phrase))) {
	temp = M_CDR(phrase);
	temp_1 = SYMBOLP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !EQ(M_CDR(phrase),Qtruth_value) : TRUEP(Nil)) {
	gensymed_symbol = M_CDR(phrase);
	temp =  !(EQ(gensymed_symbol,Qsecond) || EQ(gensymed_symbol,
		Qseconds) || EQ(gensymed_symbol,Qminute) || 
		EQ(gensymed_symbol,Qminutes) || EQ(gensymed_symbol,Qhour) 
		|| EQ(gensymed_symbol,Qhours) || EQ(gensymed_symbol,Qday) 
		|| EQ(gensymed_symbol,Qdays) || EQ(gensymed_symbol,Qweek) 
		|| EQ(gensymed_symbol,Qweeks)) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REJECT-TRUTH-VALUE-AS-UNIT-OF-MEASURE-CONSTANT */
Object reject_truth_value_as_unit_of_measure_constant(unit_of_measure_expression_phrase)
    Object unit_of_measure_expression_phrase;
{
    x_note_fn_call(192,14);
    if (truth_value_phrase_p(unit_of_measure_expression_phrase))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(unit_of_measure_expression_phrase);
}

/* TRANSFORM-TRUTH-VALUE-PHRASE-INTO-SLOT-CONSTANT */
Object transform_truth_value_phrase_into_slot_constant(truth_value_phrase)
    Object truth_value_phrase;
{
    Object cdr_new_value;

    x_note_fn_call(192,15);
    cdr_new_value = phrase_cons(CDR(truth_value_phrase),Nil);
    M_CDR(truth_value_phrase) = cdr_new_value;
    return VALUES_1(truth_value_phrase);
}

static Object string_constant_20;  /* "~s is an invalid certainty factor; it must be a number between -1 and 1, inclusive" */

/* MAKE-MESSAGE-REJECTING-CERTAINTY-FACTOR */
Object make_message_rejecting_certainty_factor(wrong_certainty_factor)
    Object wrong_certainty_factor;
{
    x_note_fn_call(192,16);
    return tformat_text_string(2,string_constant_20,wrong_certainty_factor);
}

/* CHECK-AND-SCALE-CERTAINTY-FACTOR */
Object check_and_scale_certainty_factor(true_false_or_certainty_factor_cons)
    Object true_false_or_certainty_factor_cons;
{
    Object phrase_number, certainty_factor, car_new_value, temp, temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(192,17);
    if (EQ(true_false_or_certainty_factor_cons,Qtrue))
	return phrase_cons(Truth,Qtruth_value);
    else if (EQ(true_false_or_certainty_factor_cons,Qfalse))
	return phrase_cons(Falsity,Qtruth_value);
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    phrase_number = M_CAR(true_false_or_certainty_factor_cons);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		    (SI_Long)1L)
		certainty_factor = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(phrase_number) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		    (SI_Long)1L)
		certainty_factor = aref1(phrase_number,FIX((SI_Long)0L));
	    else
		certainty_factor = phrase_number;
	    if (num_len(3,FIX((SI_Long)-1L),certainty_factor,
			FIX((SI_Long)1L))) {
		car_new_value = l_round(ltimes(Truth,certainty_factor),_);
		M_CAR(true_false_or_certainty_factor_cons) = car_new_value;
		M_CDR(true_false_or_certainty_factor_cons) = Qtruth_value;
		result = VALUES_1(true_false_or_certainty_factor_cons);
	    }
	    else {
		temp = Bad_phrase;
		temp_1 = 
			make_message_rejecting_certainty_factor(certainty_factor);
		result = VALUES_2(temp,temp_1);
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
}

/* TRUTH-VALUE-PHRASE-P */
Object truth_value_phrase_p(phrase)
    Object phrase;
{
    Object temp;

    x_note_fn_call(192,18);
    temp = CONSP(phrase) ? (EQ(M_CDR(phrase),Qtruth_value) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* TRUTH-VALUE-PHRASE-VALUE */
Object truth_value_phrase_value(truth_value_phrase)
    Object truth_value_phrase;
{
    x_note_fn_call(192,19);
    return VALUES_1(M_CAR(truth_value_phrase));
}

void grammar0_INIT()
{
    Object string_constant_49, string_constant_48, string_constant_47;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42, string_constant_41;
    Object string_constant_40, string_constant_39, string_constant_38;
    Object string_constant_37, string_constant_36, string_constant_35;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, Qconvert_quantity_interval_phrase;
    Object Qconvert_compound_quantity_interval, Qconvert_interval_phrase;
    Object Qconvert_compound_interval, string_constant_30;
    Object Qcheck_and_scale_certainty_factor;
    Object Qtransform_truth_value_phrase_into_slot_constant;
    Object string_constant_29, AB_package, string_constant_28;
    Object string_constant_27, string_constant_26;
    Object Qreject_truth_value_as_unit_of_measure_constant, string_constant_25;
    Object Qconvert_singular_constant, string_constant_24;
    Object Qreject_truth_value_as_symbol, string_constant_23;
    Object string_constant_22, string_constant_21;
    Object Qrestrict_if_not_slot_edit_feature, Qrestrict_if_slot_edit_feature;
    Object list_constant, Qinterval, Qpure_number;

    x_note_fn_call(192,20);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qneutral_unit_of_measure = STATIC_SYMBOL("NEUTRAL-UNIT-OF-MEASURE",
	    AB_package);
    Qsingular_unit_of_measure = STATIC_SYMBOL("SINGULAR-UNIT-OF-MEASURE",
	    AB_package);
    Qplural_unit_of_measure = STATIC_SYMBOL("PLURAL-UNIT-OF-MEASURE",
	    AB_package);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    def_numeric_subtype(1,Qseconds);
    Qtime_stamp = STATIC_SYMBOL("TIME-STAMP",AB_package);
    def_numeric_subtype(1,Qtime_stamp);
    Qpure_number = STATIC_SYMBOL("PURE-NUMBER",AB_package);
    def_numeric_subtype(1,Qpure_number);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    def_numeric_subtype(1,Qinterval);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qminute = STATIC_SYMBOL("MINUTE",AB_package);
    Qminutes = STATIC_SYMBOL("MINUTES",AB_package);
    Qhour = STATIC_SYMBOL("HOUR",AB_package);
    Qhours = STATIC_SYMBOL("HOURS",AB_package);
    Qday = STATIC_SYMBOL("DAY",AB_package);
    Qdays = STATIC_SYMBOL("DAYS",AB_package);
    Qweek = STATIC_SYMBOL("WEEK",AB_package);
    Qweeks = STATIC_SYMBOL("WEEKS",AB_package);
    Qinterval_too_long = STATIC_SYMBOL("INTERVAL-TOO-LONG",AB_package);
    Qconvert_interval_phrase = STATIC_SYMBOL("CONVERT-INTERVAL-PHRASE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_interval_phrase,
	    STATIC_FUNCTION(convert_interval_phrase,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qconvert_interval_phrase);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qconvert_quantity_interval_phrase = 
	    STATIC_SYMBOL("CONVERT-QUANTITY-INTERVAL-PHRASE",AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_quantity_interval_phrase,
	    STATIC_FUNCTION(convert_quantity_interval_phrase,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qconvert_quantity_interval_phrase);
    Qconvert_compound_interval = STATIC_SYMBOL("CONVERT-COMPOUND-INTERVAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_compound_interval,
	    STATIC_FUNCTION(convert_compound_interval,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qconvert_compound_interval);
    Qconvert_compound_quantity_interval = 
	    STATIC_SYMBOL("CONVERT-COMPOUND-QUANTITY-INTERVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_compound_quantity_interval,
	    STATIC_FUNCTION(convert_compound_quantity_interval,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qconvert_compound_quantity_interval);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant,(SI_Long)1L,FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)57344L);
    Qrestrict_if_slot_edit_feature = 
	    STATIC_SYMBOL("RESTRICT-IF-SLOT-EDIT-FEATURE",AB_package);
    SET_SYMBOL_FUNCTION(Qrestrict_if_slot_edit_feature,
	    STATIC_FUNCTION(restrict_if_slot_edit_feature,NIL,FALSE,3,3));
    set_grammar_transform_can_return_bad_phrase_p(Qrestrict_if_slot_edit_feature);
    Qrestrict_if_not_slot_edit_feature = 
	    STATIC_SYMBOL("RESTRICT-IF-NOT-SLOT-EDIT-FEATURE",AB_package);
    SET_SYMBOL_FUNCTION(Qrestrict_if_not_slot_edit_feature,
	    STATIC_FUNCTION(restrict_if_not_slot_edit_feature,NIL,FALSE,3,3));
    set_grammar_transform_can_return_bad_phrase_p(Qrestrict_if_not_slot_edit_feature);
    Qthis_rule = STATIC_SYMBOL("THIS-RULE",AB_package);
    string_constant = 
	    STATIC_STRING("`This rule\' is only permitted within rules.");
    Qthis_procedure = STATIC_SYMBOL("THIS-PROCEDURE",AB_package);
    string_constant_1 = 
	    STATIC_STRING("`This procedure\' is only permitted within procedures.");
    Qthis_procedure_invocation = STATIC_SYMBOL("THIS-PROCEDURE-INVOCATION",
	    AB_package);
    string_constant_2 = 
	    STATIC_STRING("`This procedure-invocation\' is only permitted within procedures.");
    Qhas_a_current_value = STATIC_SYMBOL("HAS-A-CURRENT-VALUE",AB_package);
    string_constant_3 = 
	    STATIC_STRING("`Has a current value\' and `Has no current value\' may not be applied to composite expressions.");
    Qe_designation = STATIC_SYMBOL("E-DESIGNATION",AB_package);
    string_constant_4 = 
	    STATIC_STRING("`Every\' is not permitted within procedures.");
    Qconditional_expression = STATIC_SYMBOL("CONDITIONAL-EXPRESSION",
	    AB_package);
    string_constant_5 = 
	    STATIC_STRING("Conditional expressions within procedures must terminate in an `else\' clause.");
    Qregion_cannot_be_a_color_or_metacolor = 
	    STATIC_SYMBOL("REGION-CANNOT-BE-A-COLOR-OR-METACOLOR",AB_package);
    string_constant_6 = 
	    STATIC_STRING("A region cannot be a color or metacolor.");
    Qregion_cannot_be_the_symbol_copy = 
	    STATIC_SYMBOL("REGION-CANNOT-BE-THE-SYMBOL-COPY",AB_package);
    string_constant_7 = STATIC_STRING("A region cannot be the symbol COPY.");
    Qregion_cannot_be_the_symbol_inherited = 
	    STATIC_SYMBOL("REGION-CANNOT-BE-THE-SYMBOL-INHERITED",AB_package);
    string_constant_8 = 
	    STATIC_STRING("A region cannot be the symbol INHERITED.");
    Qcolor_cannot_be_the_symbol_copy = 
	    STATIC_SYMBOL("COLOR-CANNOT-BE-THE-SYMBOL-COPY",AB_package);
    string_constant_9 = 
	    STATIC_STRING("A color cannot be the symbol INHERITED.");
    string_constant_10 = 
	    STATIC_STRING("you cannot enter an interval longer than 10 years");
    Qtoo_few_arguments = STATIC_SYMBOL("TOO-FEW-ARGUMENTS",AB_package);
    string_constant_11 = STATIC_STRING("too few arguments");
    Qtoo_many_arguments = STATIC_SYMBOL("TOO-MANY-ARGUMENTS",AB_package);
    string_constant_12 = STATIC_STRING("too many arguments");
    Qwrong_number_of_arguments = STATIC_SYMBOL("WRONG-NUMBER-OF-ARGUMENTS",
	    AB_package);
    string_constant_13 = STATIC_STRING("wrong number of arguments");
    string_constant_14 = 
	    STATIC_STRING("`Otherwise\' may be used only after at least one other case choice and only as the last choice.");
    Qcannot_replace_in_runtime_or_embedded_g2 = 
	    STATIC_SYMBOL("CANNOT-REPLACE-IN-RUNTIME-OR-EMBEDDED-G2",
	    AB_package);
    string_constant_15 = 
	    STATIC_STRING("The replace feature is not available in runtime or embedded G2.");
    Qnon_object_must_be_passed_as_handle = 
	    STATIC_SYMBOL("NON-OBJECT-MUST-BE-PASSED-AS-HANDLE",AB_package);
    string_constant_16 = 
	    STATIC_STRING("This class is not a subclass of object and so must be passed `as handle\'");
    Qchange_nth_element_no_array_or_list = 
	    STATIC_SYMBOL("CHANGE-NTH-ELEMENT-NO-ARRAY-OR-LIST",AB_package);
    string_constant_17 = 
	    STATIC_STRING("The change element action must refer to a g2-array or g2-list.  Note that the array or list expression may need to be within parentheses.");
    Qreserved_java_word = STATIC_SYMBOL("RESERVED-JAVA-WORD",AB_package);
    string_constant_18 = STATIC_STRING("");
    string_constant_19 = 
	    STATIC_STRING("[Internal error in bad parse explanation.]");
    string_constant_21 = 
	    STATIC_STRING("1p1m83Kky83-Hy1m83Kky83-Uy1m83Kky834my1m83Kky830Sy1m83Kky8s");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_21));
    Qreject_truth_value_as_unit_of_measure_constant = 
	    STATIC_SYMBOL("REJECT-TRUTH-VALUE-AS-UNIT-OF-MEASURE-CONSTANT",
	    AB_package);
    string_constant_22 = 
	    STATIC_STRING("1n1o8382y83dQyl9k1m8382y831Ny1m8382y83Kky");
    clear_optimized_constants();
    push_optimized_constant(Qreject_truth_value_as_unit_of_measure_constant);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_22));
    Qreject_truth_value_as_symbol = 
	    STATIC_SYMBOL("REJECT-TRUTH-VALUE-AS-SYMBOL",AB_package);
    string_constant_23 = STATIC_STRING("1m1m837ky8382y1o837ky83-2yl9k");
    clear_optimized_constants();
    push_optimized_constant(Qreject_truth_value_as_symbol);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_23));
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qreject_truth_value_as_symbol,
	    STATIC_FUNCTION(reject_truth_value_as_symbol,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qreject_truth_value_as_symbol);
    Qconvert_singular_constant = STATIC_SYMBOL("CONVERT-SINGULAR-CONSTANT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_singular_constant,
	    STATIC_FUNCTION(convert_singular_constant,NIL,FALSE,1,1));
    string_constant_24 = 
	    STATIC_STRING("1q1m83-82y83-Hy1m83-82y831Ny1o83-82y1m83-Hy83aKy2llm9k1n83-82y1m83-Hy839hy2llm1n83-82y1m83-Hy839Ty2llm1m83-82y83-Uy");
    clear_optimized_constants();
    push_optimized_constant(Qconvert_singular_constant);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_24));
    string_constant_25 = 
	    STATIC_STRING("1n1o83dQy1m83-Hy83aKy2llm9k1n83dQy1m83-Hy839hy2llm1n83dQy1m83-Hy839Ty2llm");
    clear_optimized_constants();
    push_optimized_constant(Qconvert_singular_constant);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_25));
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreject_truth_value_as_unit_of_measure_constant,
	    STATIC_FUNCTION(reject_truth_value_as_unit_of_measure_constant,
	    NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qreject_truth_value_as_unit_of_measure_constant);
    string_constant_26 = 
	    STATIC_STRING("1m1m83f1y83Kky1n83f1y1n1m9k9l1m9k83-2y830Tyn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_26));
    Qcheck_and_scale_certainty_factor = 
	    STATIC_SYMBOL("CHECK-AND-SCALE-CERTAINTY-FACTOR",AB_package);
    string_constant_27 = 
	    STATIC_STRING("1n1o834my1m9k83=Oyl9l1o834my1m9k832Zyl9l1o834my1m83-Hy1m9k83=Oy2ll83=Oy9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qcheck_and_scale_certainty_factor);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_27));
    string_constant_28 = STATIC_STRING("1m1m83-uVy1m9k83Zy1m83-uVy834my");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_28));
    Qtransform_truth_value_phrase_into_slot_constant = 
	    STATIC_SYMBOL("TRANSFORM-TRUTH-VALUE-PHRASE-INTO-SLOT-CONSTANT",
	    AB_package);
    string_constant_29 = STATIC_STRING("1l1o83-uWy834myl9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_truth_value_phrase_into_slot_constant);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_29));
    SET_SYMBOL_FUNCTION(Qtransform_truth_value_phrase_into_slot_constant,
	    STATIC_FUNCTION(transform_truth_value_phrase_into_slot_constant,
	    NIL,FALSE,1,1));
    string_constant_20 = 
	    STATIC_STRING("~s is an invalid certainty factor; it must be a number between -1 and 1, inclusive");
    SET_SYMBOL_FUNCTION(Qcheck_and_scale_certainty_factor,
	    STATIC_FUNCTION(check_and_scale_certainty_factor,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qcheck_and_scale_certainty_factor);
    string_constant_30 = STATIC_STRING("1n1m83-Hy83Sy1m83-Hy9k1m83-Hy83=By");
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_30));
    string_constant_31 = 
	    STATIC_STRING("13-Ey1m83-oy83-wuy1o83-oy1n83-wuy1m9k83-ty83-Q1y2lln9l1o83-oy1n83-wuy1m9k83-ty83-YHy2lln9l1o83-oy1n83-wuy1m9k83-ty83-epy2lln9l1o");
    string_constant_32 = 
	    STATIC_STRING("83-oy1n83-wuy1m9k83-ty83-nty2lln9l1o83-oy1n83-wuy1m9k83vy83-OXy2lln9l1m83-oy83-Q=y1m83-Q=y83-Q1y1o83-Q=y1n83-Q1y1m9k83-ty83-YHy2");
    string_constant_33 = 
	    STATIC_STRING("lln9l1o83-Q=y1n83-Q1y1m9k83-ty83-epy2lln9l1o83-Q=y1n83-Q1y1m9k83-ty83-nty2lln9l1o83-Q=y1n83-Q1y1m9k83vy83-OYy2lln9l1m83-Q=y83-YF");
    string_constant_34 = 
	    STATIC_STRING("y1o83-OXy1n83-Q1y1m9k83vy83-OYy2lln9l1o83-OXy1o83-Q1y1m9k83vy1m9k83-ty83-YHy2llo9l1o83-OXy1o83-Q1y1m9k83vy1m9k83-ty83-epy2llo9l1");
    string_constant_35 = 
	    STATIC_STRING("o83-OXy1o83-Q1y1m9k83vy1m9k83-ty83-nty2llo9l1m83-OXy83-OYy1m83-YFy83-YHy1o83-YFy1n83-YHy1m9k83-ty83-epy2lln9l1o83-YFy1n83-YHy1m9");
    string_constant_36 = 
	    STATIC_STRING("k83-ty83-nty2lln9l1o83-YFy1n83-YHy1m9k83vy83-OZy2lln9l1m83-YFy83-eny1o83-OYy1n83-YHy1m9k83vy83-OZy2lln9l1o83-OYy1o83-YHy1m9k83vy");
    string_constant_37 = 
	    STATIC_STRING("1m9k83-ty83-epy2llo9l1o83-OYy1o83-YHy1m9k83vy1m9k83-ty83-nty2llo9l1m83-OYy83-OZy1m83-eny83-epy1o83-eny1n83-epy1m9k83-ty83-nty2ll");
    string_constant_38 = 
	    STATIC_STRING("n9l1m83-eny83-nty1o83-OZy1o83-epy1m9k83vy1m9k83-ty83-nty2llo9l1o83-wuy1m83*7y83-wty2llm9m1m83-wty1m9k83Fty1m83-wty1m9k83-Ggy1o83");
    string_constant_39 = 
	    STATIC_STRING("-Q1y1m83*7y83-Q0y2llm9m1m83-Q0y1m9k833+y1m83-Q0y1m9k83uey1o83-YHy1m83*7y83-YGy2llm9m1m83-YGy1m9k833Oy1m83-YGy1m9k83-*Ky1o83-epy1");
    string_constant_40 = 
	    STATIC_STRING("m83*7y83-eoy2llm9m1m83-eoy1m9k833Ty1m83-eoy1m9k83-6my1o83-nty1m83*7y83-CSy2llm9m1m83-CSy1m9k9n1m83-CSy1m9k832Ky1m831Ny83-kty1o83");
    string_constant_41 = 
	    STATIC_STRING("1Ny1n83-kty1m9k83-ty83-kny2lln9o1o831Ny1n83-kty1m9k83-ty83-kpy2lln9o1o831Ny1n83-kty1m9k83-ty83-kry2lln9o1o831Ny1n83-kty1m9k83-ty");
    string_constant_42 = 
	    STATIC_STRING("83-ksy2lln9o1o831Ny1n83-kty1m9k83vy83-Oay2lln9o1m831Ny83-kmy1m83-kmy83-kny1o83-kmy1n83-kny1m9k83-ty83-kpy2lln9o1o83-kmy1n83-kny1");
    string_constant_43 = 
	    STATIC_STRING("m9k83-ty83-kry2lln9o1o83-kmy1n83-kny1m9k83-ty83-ksy2lln9o1o83-kmy1n83-kny1m9k83vy83-Oby2lln9o1m83-kmy83-koy1o83-Oay1n83-kny1m9k8");
    string_constant_44 = 
	    STATIC_STRING("3vy83-Oby2lln9o1o83-Oay1o83-kny1m9k83vy1m9k83-ty83-kpy2llo9o1o83-Oay1o83-kny1m9k83vy1m9k83-ty83-kry2llo9o1o83-Oay1o83-kny1m9k83v");
    string_constant_45 = 
	    STATIC_STRING("y1m9k83-ty83-ksy2llo9o1m83-Oay83-Oby1m83-koy83-kpy1o83-koy1n83-kpy1m9k83-ty83-kry2lln9o1o83-koy1n83-kpy1m9k83-ty83-ksy2lln9o1o83");
    string_constant_46 = 
	    STATIC_STRING("-koy1n83-kpy1m9k83vy83-Ocy2lln9o1m83-koy83-kqy1o83-Oby1n83-kpy1m9k83vy83-Ocy2lln9o1o83-Oby1o83-kpy1m9k83vy1m9k83-ty83-kry2llo9o1");
    string_constant_47 = 
	    STATIC_STRING("o83-Oby1o83-kpy1m9k83vy1m9k83-ty83-ksy2llo9o1m83-Oby83-Ocy1m83-kqy83-kry1o83-kqy1n83-kry1m9k83-ty83-ksy2lln9o1m83-kqy83-ksy1o83-");
    string_constant_48 = 
	    STATIC_STRING("Ocy1o83-kry1m9k83vy1m9k83-ty83-ksy2llo9o1o83-kty1m83-7Wy83-wty2llm9p1o83-kny1m83-7Wy83-Q0y2llm9p1o83-kpy1m83-7Wy83-YGy2llm9p1o83");
    string_constant_49 = 
	    STATIC_STRING("-kry1m83-7Wy83-eoy2llm9p1o83-ksy1m83-7Wy83-CSy2llm9p");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qconvert_compound_interval);
    push_optimized_constant(Qconvert_interval_phrase);
    push_optimized_constant(Qsecond);
    push_optimized_constant(Qconvert_compound_quantity_interval);
    push_optimized_constant(Qconvert_quantity_interval_phrase);
    add_grammar_rules_function(regenerate_optimized_constant(list(19,
	    string_constant_31,string_constant_32,string_constant_33,
	    string_constant_34,string_constant_35,string_constant_36,
	    string_constant_37,string_constant_38,string_constant_39,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45,
	    string_constant_46,string_constant_47,string_constant_48,
	    string_constant_49)));
}
