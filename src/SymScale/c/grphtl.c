/* grphtl.c
 * Input file:  graph-util.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "grphtl.h"


Object Enumeration_grammar_category_members_prop = UNBOUND;

/* CHECK-FRAME-LIKE-VALUE-RANGE */
Object check_frame_like_value_range(value,low_qm,high_qm)
    Object value, low_qm, high_qm;
{
    char temp;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(174,0);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (FIXNUMP(high_qm))
	    high_qm = DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(high_qm));
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(high_qm) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(high_qm)) == (SI_Long)1L)
	    high_qm = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(high_qm,
		    (SI_Long)0L));
	else;
	if (FIXNUMP(low_qm))
	    low_qm = DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(low_qm));
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(low_qm) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(low_qm)) == (SI_Long)1L)
	    low_qm = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(low_qm,
		    (SI_Long)0L));
	else;
	if (FIXNUMP(value))
	    value = DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(value));
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L));
	else;
	if (low_qm) {
	    arg = DOUBLE_FLOAT_TO_DOUBLE(low_qm);
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(T);
	if (temp) {
	    if (high_qm) {
		arg = DOUBLE_FLOAT_TO_DOUBLE(high_qm);
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
		if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg))
		    result = VALUES_1( !inline_nanp_for_comparison(arg_1) ?
			     T : Nil);
		else
		    result = VALUES_1(Nil);
	    }
	    else
		result = VALUES_1(T);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

Object Frame_like_category_cases_prop = UNBOUND;

Object Recent_defaults_made = UNBOUND;

static Object Qphrase;             /* phrase */

/* MAKE-FRAME-LIKE-CATEGORY-PARSE-RESULT */
Object make_frame_like_category_parse_result(category_name,key_symbol_1,plist)
    Object category_name, key_symbol_1, plist;
{
    Object parse_result, case_number, cadr_new_value;

    x_note_fn_call(174,1);
    parse_result = make_frame_like_category_default(4,category_name,
	    key_symbol_1,plist,Qphrase);
    case_number = CADR(parse_result);
    cadr_new_value = CODE_CHAR(FIX(IFIX(case_number) + (SI_Long)65L));
    M_CADR(parse_result) = cadr_new_value;
    return VALUES_1(parse_result);
}

static Object Qab_slot_value;      /* slot-value */

static Object Qframe_like_category_cases;  /* frame-like-category-cases */

/* MAKE-FRAME-LIKE-CATEGORY-DEFAULT */
Object make_frame_like_category_default varargs_1(int, n)
{
    Object category_name, key_symbol_1, plist;
    Object pool, cases, best_case_qm, best_case_key_matches;
    Object best_case_value_matches, maximum_matches, case_1, ab_loop_list_;
    Object case_plist, temp, current_case_key_matches;
    Object current_case_value_matches, key, value, ab_loop_list__1;
    Object matching_key_qm, value_in_case_qm, result_1, tail, temp_1;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, gensymed_symbol;
    Object modify_macro_for_phrase_push_arg;
    Declare_varargs_nonrelocating;

    x_note_fn_call(174,2);
    INIT_ARGS_nonrelocating();
    category_name = REQUIRED_ARG_nonrelocating();
    key_symbol_1 = REQUIRED_ARG_nonrelocating();
    plist = REQUIRED_ARG_nonrelocating();
    pool = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    Qab_slot_value;
    END_ARGS_nonrelocating();
    cases = getfq_function_no_default(INLINE_SYMBOL_PLIST(category_name),
	    Qframe_like_category_cases);
    best_case_qm = Nil;
    best_case_key_matches = FIX((SI_Long)0L);
    best_case_value_matches = FIX((SI_Long)0L);
    maximum_matches = chestnut_floorf_function(length(plist),FIX((SI_Long)2L));
    case_1 = Nil;
    ab_loop_list_ = cases;
    case_plist = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    case_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    case_plist = CDDR(case_1);
    if (EQ(CAR(case_1),key_symbol_1)) {
	temp = FIX((SI_Long)0L);
	if (NUM_EQ(temp,maximum_matches)) {
	    if (EQ(pool,Qab_slot_value))
		return copy_for_slot_value(case_1);
	    else
		return copy_for_phrase(case_1);
	}
	else {
	    current_case_key_matches = FIX((SI_Long)0L);
	    current_case_value_matches = FIX((SI_Long)0L);
	    key = Nil;
	    value = Nil;
	    ab_loop_list__1 = plist;
	    matching_key_qm = Nil;
	    value_in_case_qm = Nil;
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	  next_loop_1:
	    key = CAR(ab_loop_list__1);
	    temp = CDR(ab_loop_list__1);
	    value = CAR(temp);
	    matching_key_qm = memq_function(key,case_plist);
	    value_in_case_qm = matching_key_qm ? getf(case_plist,key,_) : Qnil;
	    if (matching_key_qm) {
		current_case_key_matches = 
			FIXNUM_ADD1(current_case_key_matches);
		if (EQUAL(value_in_case_qm,value))
		    current_case_value_matches = 
			    add1(current_case_value_matches);
	    }
	    ab_loop_list__1 = CDDR(ab_loop_list__1);
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    goto next_loop_1;
	  end_loop_1:
	    if ( !TRUEP(best_case_qm) || 
		    FIXNUM_GT(current_case_key_matches,
		    best_case_key_matches) || 
		    FIXNUM_EQ(current_case_key_matches,
		    best_case_key_matches) && 
		    FIXNUM_GT(current_case_value_matches,
		    best_case_value_matches)) {
		best_case_qm = case_1;
		best_case_key_matches = current_case_key_matches;
		best_case_value_matches = current_case_value_matches;
	    }
	}
    }
    goto next_loop;
  end_loop:
    if (best_case_qm) {
	result_1 = EQ(pool,Qab_slot_value) ? 
		copy_for_slot_value(best_case_qm) : 
		copy_for_phrase(best_case_qm);
	key = Nil;
	value = Nil;
	ab_loop_list_ = plist;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
      next_loop_2:
	key = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	value = CAR(temp);
	if (memq_function(key,CDDR(result_1))) {
	    temp = memq_function(key,CDDR(result_1));
	    tail = CDR(temp);
	    temp_1 = EQ(pool,Qab_slot_value) ? copy_for_slot_value(value) :
		     copy_for_phrase(value);
	    M_CAR(tail) = temp_1;
	}
	else {
	    if (EQ(pool,Qab_slot_value)) {
		slot_value_push_modify_macro_arg = EQ(pool,Qab_slot_value) 
			? copy_for_slot_value(value) : copy_for_phrase(value);
		car_1 = slot_value_push_modify_macro_arg;
		cdr_1 = CDDR(result_1);
		temp_1 = slot_value_cons_1(car_1,cdr_1);
		M_CDDR(result_1) = temp_1;
	    }
	    else {
		gensymed_symbol = EQ(pool,Qab_slot_value) ? 
			copy_for_slot_value(value) : copy_for_phrase(value);
		modify_macro_for_phrase_push_arg = gensymed_symbol;
		temp_1 = phrase_cons_with_args_reversed(CDDR(result_1),
			modify_macro_for_phrase_push_arg);
		M_CDDR(result_1) = temp_1;
	    }
	    if (EQ(pool,Qab_slot_value)) {
		slot_value_push_modify_macro_arg = key;
		car_1 = slot_value_push_modify_macro_arg;
		cdr_1 = CDDR(result_1);
		temp_1 = slot_value_cons_1(car_1,cdr_1);
		M_CDDR(result_1) = temp_1;
	    }
	    else {
		modify_macro_for_phrase_push_arg = key;
		temp_1 = phrase_cons_with_args_reversed(CDDR(result_1),
			modify_macro_for_phrase_push_arg);
		M_CDDR(result_1) = temp_1;
	    }
	}
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(result_1);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Calling_float_function_cleverly_p, Qcalling_float_function_cleverly_p);

DEFINE_VARIABLE_WITH_SYMBOL(Outstanding_float_function_floats, Qoutstanding_float_function_floats);

static Object Qfloat_array;        /* float-array */

/* INIT-EZ-FLOAT */
Object init_ez_float()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;

    x_note_fn_call(174,3);
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,3.1415926);
    return VALUES_1(new_float);
}

/* CLEANUP-FLOAT-FUNCTION-FLOATS */
Object cleanup_float_function_floats()
{
    Object managed_float, ab_loop_list_;

    x_note_fn_call(174,4);
    managed_float = Nil;
    ab_loop_list_ = Outstanding_float_function_floats;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    managed_float = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    goto next_loop;
  end_loop:
    reclaim_slot_value_list_1(Outstanding_float_function_floats);
    Outstanding_float_function_floats = Nil;
    return VALUES_1(Qnil);
}

/* MAKE-2D-DISPLAY-TIME */
Object make_2d_display_time()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;

    x_note_fn_call(174,5);
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
    return VALUES_1(new_float);
}

/* MAKE-2D-DISPLAY-VALUE */
Object make_2d_display_value()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;

    x_note_fn_call(174,6);
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
    return VALUES_1(new_float);
}

/* FIXNUM-TO-TIME-FUNCTION */
Object fixnum_to_time_function(x)
    Object x;
{
    x_note_fn_call(174,7);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(x)));
}

Object Max_timespan = UNBOUND;

static Object Qvms;                /* vms */

static Object Qpositive_infinity;  /* positive-infinity */

static Object Qnegative_infinity;  /* negative-infinity */

static Object Qnan;                /* nan */

/* EXCEPTIONAL-FLOAT-FLAVOR? */
Object exceptional_float_flavor_qm(thing)
    Object thing;
{
    Object temp, byte0, byte1, byte2, byte3;
    SI_Long b0, b1, b2, b3;
    double temp_1;
    Object result;

    x_note_fn_call(174,8);
    if (FLOATP(thing)) {
	if (EQ(G2_machine_type,Qvms))
	    temp = Nil;
	else {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(thing);
	    g2ext_foreign_partition_float(temp_1,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	    b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	    b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	    b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	    b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	    result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	    MVS_4(result,byte0,byte1,byte2,byte3);
	    if (FIXNUM_EQ(FIXNUM_LOGAND(byte0,Mask_for_ieee_exponent),
		    Mask_for_ieee_exponent)) {
		if (FIXNUM_EQ(byte0,Mask_for_ieee_exponent) && IFIX(byte1) 
			== (SI_Long)0L && IFIX(byte2) == (SI_Long)0L && 
			IFIX(byte3) == (SI_Long)0L)
		    temp = Qpositive_infinity;
		else if (IFIX(byte0) == (SI_Long)65520L && IFIX(byte1) == 
			(SI_Long)0L && IFIX(byte2) == (SI_Long)0L && 
			IFIX(byte3) == (SI_Long)0L)
		    temp = Qnegative_infinity;
		else if (FIXNUM_PLUSP(byte1) || FIXNUM_PLUSP(byte2) || 
			FIXNUM_PLUSP(byte3) || (SI_Long)0L < (IFIX(byte0) 
			& (SI_Long)15L))
		    temp = Qnan;
		else
		    temp = Nil;
	    }
	    else
		temp = Nil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object The_type_description_of_extremum_cache = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_extremum_caches, Qchain_of_available_extremum_caches);

DEFINE_VARIABLE_WITH_SYMBOL(Extremum_cache_count, Qextremum_cache_count);

Object Chain_of_available_extremum_caches_vector = UNBOUND;

/* EXTREMUM-CACHE-STRUCTURE-MEMORY-USAGE */
Object extremum_cache_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(174,9);
    temp = Extremum_cache_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)15L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EXTREMUM-CACHE-COUNT */
Object outstanding_extremum_cache_count()
{
    Object def_structure_extremum_cache_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(174,10);
    gensymed_symbol = IFIX(Extremum_cache_count);
    def_structure_extremum_cache_variable = Chain_of_available_extremum_caches;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_extremum_cache_variable))
	goto end_loop;
    def_structure_extremum_cache_variable = 
	    ISVREF(def_structure_extremum_cache_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EXTREMUM-CACHE-1 */
Object reclaim_extremum_cache_1(extremum_cache)
    Object extremum_cache;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(174,11);
    inline_note_reclaim_cons(extremum_cache,Nil);
    structure_being_reclaimed = extremum_cache;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_if_managed_array(ISVREF(extremum_cache,(SI_Long)3L));
      SVREF(extremum_cache,FIX((SI_Long)3L)) = Nil;
      reclaim_if_managed_array(ISVREF(extremum_cache,(SI_Long)5L));
      SVREF(extremum_cache,FIX((SI_Long)5L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_extremum_caches_vector,
	    IFIX(Current_thread_index));
    SVREF(extremum_cache,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_extremum_caches_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = extremum_cache;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EXTREMUM-CACHE */
Object reclaim_structure_for_extremum_cache(extremum_cache)
    Object extremum_cache;
{
    x_note_fn_call(174,12);
    return reclaim_extremum_cache_1(extremum_cache);
}

static Object Qg2_defstruct_structure_name_extremum_cache_g2_struct;  /* g2-defstruct-structure-name::extremum-cache-g2-struct */

/* MAKE-PERMANENT-EXTREMUM-CACHE-STRUCTURE-INTERNAL */
Object make_permanent_extremum_cache_structure_internal()
{
    Object def_structure_extremum_cache_variable;
    Object defstruct_g2_extremum_cache_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(174,13);
    def_structure_extremum_cache_variable = Nil;
    atomic_incff_symval(Qextremum_cache_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_extremum_cache_variable = Nil;
	gensymed_symbol = (SI_Long)15L;
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
	defstruct_g2_extremum_cache_variable = the_array;
	SVREF(defstruct_g2_extremum_cache_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_extremum_cache_g2_struct;
	def_structure_extremum_cache_variable = 
		defstruct_g2_extremum_cache_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_extremum_cache_variable);
}

/* MAKE-EXTREMUM-CACHE-1 */
Object make_extremum_cache_1()
{
    Object def_structure_extremum_cache_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(174,14);
    def_structure_extremum_cache_variable = 
	    ISVREF(Chain_of_available_extremum_caches_vector,
	    IFIX(Current_thread_index));
    if (def_structure_extremum_cache_variable) {
	svref_arg_1 = Chain_of_available_extremum_caches_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_extremum_cache_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_extremum_cache_g2_struct;
    }
    else
	def_structure_extremum_cache_variable = 
		make_permanent_extremum_cache_structure_internal();
    inline_note_allocate_cons(def_structure_extremum_cache_variable,Nil);
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_extremum_cache_variable,FIX((SI_Long)14L)) = Nil;
    return VALUES_1(def_structure_extremum_cache_variable);
}

/* RECLAIM-GENERIC-HISTORY-DATA-SERIAL-NUMBER-VALUE */
Object reclaim_generic_history_data_serial_number_value(serial_number,
	    generic_history)
    Object serial_number, generic_history;
{
    x_note_fn_call(174,15);
    reclaim_frame_serial_number(serial_number);
    ISVREF(generic_history,(SI_Long)7L) = Nil;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Trace_validate_p, Qtrace_validate_p);

/* COPY-FRAME-FOR-GENERIC-HISTORY */
Object copy_frame_for_generic_history(generic_history)
    Object generic_history;
{
    Object old, current_block_of_dependent_frame, new_1, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(174,16);
    old = generic_history;
    current_block_of_dependent_frame = 
	    BOUNDP(Qcurrent_block_of_dependent_frame) && 
	    Current_block_of_dependent_frame ? 
	    Current_block_of_dependent_frame : Superior_frame_being_cloned_qm;
    new_1 = clone_frame(1,generic_history);
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      svref_new_value = copy_extremum_cache(ISVREF(old,(SI_Long)3L),new_1);
      ISVREF(new_1,(SI_Long)3L) = svref_new_value;
      svref_new_value = copy_extremum_cache(ISVREF(old,(SI_Long)2L),new_1);
      ISVREF(new_1,(SI_Long)2L) = svref_new_value;
      svref_new_value = copy_generic_history_data(ISVREF(old,(SI_Long)5L),
	      ISVREF(old,(SI_Long)4L));
      ISVREF(new_1,(SI_Long)5L) = svref_new_value;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      svref_new_value = copy_for_slot_value(ISVREF(old,(SI_Long)8L));
      SVREF(new_1,FIX((SI_Long)8L)) = svref_new_value;
      result = VALUES_1(new_1);
    POP_SPECIAL();
    return result;
}

static Object Qgeneric_history;    /* generic-history */

/* CLEANUP-FOR-GENERIC-HISTORY */
Object cleanup_for_generic_history(generic_history)
    Object generic_history;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(174,17);
    frame = generic_history;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgeneric_history)) {
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
    return reclaim_generic_history(2,generic_history,Nil);
}

static Object Qconstant;           /* constant */

static Object Qcascaded;           /* cascaded */

/* COPY-GENERIC-HISTORY-DATA */
Object copy_generic_history_data(data,type)
    Object data, type;
{
    x_note_fn_call(174,18);
    if (EQ(type,Qconstant))
	return copy_managed_float(data);
    else if (EQ(type,Qcascaded))
	return copy_cascaded_ring_buffer(data);
    else if (EQ(type,Qvariable))
	return VALUES_1(Nil);
    else
	return VALUES_1(Qnil);
}

/* VALIDATE-GENERIC-HISTORY */
Object validate_generic_history(history)
    Object history;
{
    Object temp, res;

    x_note_fn_call(174,19);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qcascaded) || EQ(temp,Qconstant))
	return VALUES_1(Nil);
    else if (EQ(temp,Qvariable)) {
	res = validate_variable_history(history);
	if (Trace_validate_p)
	    format((SI_Long)3L,T,"gross changes to ~s~%",history);
	return VALUES_1(res);
    }
    else
	return VALUES_1(Qnil);
}

/* GENERIC-HISTORY-VALID-P */
Object generic_history_valid_p(history)
    Object history;
{
    Object temp;

    x_note_fn_call(174,20);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qcascaded) || EQ(temp,Qconstant))
	return VALUES_1(T);
    else if (EQ(temp,Qvariable))
	return VALUES_1(ISVREF(history,(SI_Long)5L));
    else
	return VALUES_1(Qnil);
}

/* RESET-GENERIC-HISTORY */
Object reset_generic_history(history)
    Object history;
{
    Object temp;

    x_note_fn_call(174,21);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	return reset_constant_history(history);
    else if (EQ(temp,Qcascaded))
	return reset_cascaded_history(history);
    else if (EQ(temp,Qvariable))
	return reset_variable_history(history);
    else
	return VALUES_1(Qnil);
}

/* RECLAIM-GENERIC-HISTORY */
Object reclaim_generic_history varargs_1(int, n)
{
    Object history;
    Object delete_p, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(174,22);
    INIT_ARGS_nonrelocating();
    history = REQUIRED_ARG_nonrelocating();
    delete_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	return reclaim_constant_history(1,history);
    else if (EQ(temp,Qcascaded))
	return reclaim_cascaded_history(2,history,delete_p);
    else if (EQ(temp,Qvariable))
	return reclaim_variable_history(2,history,delete_p);
    else
	return VALUES_1(Qnil);
}

/* NEW-CONSTANT-HISTORY */
Object new_constant_history(fix_or_float)
    Object fix_or_float;
{
    Object history, amf_available_array_cons_qm, amf_array, temp, temp_1;
    Object amf_result, new_float;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(174,23);
    history = make_frame(Qgeneric_history);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (FIXNUMP(fix_or_float)) {
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
	    aref_new_value = (double)IFIX(fix_or_float);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	}
	else if (CONSP(fix_or_float) && EQ(CAR(fix_or_float),Qminus)) {
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
	    aref_new_value = (double)IFIX(ltimes(FIX((SI_Long)-1L),
		    CADR(fix_or_float)));
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	}
	else
	    new_float = copy_managed_float(fix_or_float);
    }
    POP_LOCAL_ALLOCATION(0,0);
    ISVREF(history,(SI_Long)5L) = new_float;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    SVREF(history,FIX((SI_Long)4L)) = Qconstant;
    initialize_generic_history(history,FIX((SI_Long)100L));
    return VALUES_1(history);
}

static Object float_constant;      /* 1.0 */

/* COMPUTE-UPDATE-INTERVAL-SPEC */
Object compute_update_interval_spec(update_interval_in_seconds)
    Object update_interval_in_seconds;
{
    Object temp, update_interval_float;
    double temp_1;

    x_note_fn_call(174,24);
    temp = update_interval_in_seconds;
    if (temp);
    else
	temp = FIX((SI_Long)1L);
    update_interval_float = normalize_to_gensym_float(temp);
    update_interval_float = DOUBLE_FLOAT_MIN(float_constant,
	    update_interval_float);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(update_interval_float);
    temp = fround(DOUBLE_TO_DOUBLE_FLOAT(temp_1 * 1000.0),_);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    return VALUES_1(LONG_TO_FIXNUM(inline_floor_1(temp_1)));
}

/* NEW-CASCADED-HISTORY */
Object new_cascaded_history varargs_1(int, n)
{
    Object expiration_interval_qm;
    Object granularity_interval_in_seconds, history, granularity;
    Object svref_new_value;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(174,25);
    INIT_ARGS_nonrelocating();
    expiration_interval_qm = REQUIRED_ARG_nonrelocating();
    granularity_interval_in_seconds = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    history = make_frame(Qgeneric_history);
    granularity = 
	    compute_update_interval_spec(granularity_interval_in_seconds);
    svref_new_value = make_or_reformat_cascaded_ring_buffer(Nil,Nil,
	    expiration_interval_qm,granularity);
    ISVREF(history,(SI_Long)5L) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    SVREF(history,FIX((SI_Long)4L)) = Qcascaded;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_dependent_frame_1();
	svref_new_value = slot_value_list_4(Nil,Nil,expiration_interval_qm,
		granularity);
	SVREF(history,FIX((SI_Long)8L)) = svref_new_value;
    }
    POP_LOCAL_ALLOCATION(0,0);
    initialize_generic_history(history,FIX((SI_Long)500L));
    return VALUES_1(history);
}

/* UPDATE-CASCADED-HISTORY-EXPIRATION */
Object update_cascaded_history_expiration(history,expiration,
	    granularity_interval_qm)
    Object history, expiration, granularity_interval_qm;
{
    Object cascaded_ring_buffer_qm, granularity, temp;

    x_note_fn_call(174,26);
    cascaded_ring_buffer_qm = ISVREF(history,(SI_Long)5L);
    granularity = compute_update_interval_spec(granularity_interval_qm);
    temp = ISVREF(history,(SI_Long)8L);
    M_CADDR(temp) = expiration;
    temp = ISVREF(history,(SI_Long)8L);
    M_CADDDR(temp) = granularity;
    if (cascaded_ring_buffer_qm)
	return make_or_reformat_cascaded_ring_buffer(cascaded_ring_buffer_qm,
		Nil,expiration,granularity);
    else
	return VALUES_1(Nil);
}

/* NEW-VARIABLE-HISTORY */
Object new_variable_history(frame,cell_index,use_simulator_p)
    Object frame, cell_index, use_simulator_p;
{
    Object history, svref_new_value;

    x_note_fn_call(174,27);
    history = make_frame(Qgeneric_history);
    ISVREF(history,(SI_Long)5L) = Nil;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    svref_new_value = slot_value_list_3(frame,cell_index,use_simulator_p);
    SVREF(history,FIX((SI_Long)6L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    SVREF(history,FIX((SI_Long)4L)) = Qvariable;
    initialize_generic_history(history,FIX((SI_Long)500L));
    return VALUES_1(history);
}

/* UPDATE-HISTORY-FOR-CELL-ARRAY-CHANGE */
Object update_history_for_cell_array_change(history,frame,cell_index,
	    use_simulator_p)
    Object history, frame, cell_index, use_simulator_p;
{
    Object designation, svref_new_value;

    x_note_fn_call(174,28);
    if (EQ(ISVREF(history,(SI_Long)4L),Qvariable)) {
	if (ISVREF(history,(SI_Long)6L)) {
	    designation = ISVREF(history,(SI_Long)6L);
	    M_CAR(designation) = frame;
	    M_CADR(designation) = cell_index;
	    if ( !EQ(CADDR(designation),use_simulator_p))
		ISVREF(history,(SI_Long)5L) = Nil;
	    return VALUES_1(M_CADDR(designation) = use_simulator_p);
	}
	else {
	    if (Noting_changes_to_kb_p)
		note_change_to_dependent_frame_1();
	    svref_new_value = slot_value_list_3(frame,cell_index,
		    use_simulator_p);
	    return VALUES_1(SVREF(history,FIX((SI_Long)6L)) = svref_new_value);
	}
    }
    else
	return VALUES_1(Nil);
}

/* ADD-TO-CASCADED-HISTORY */
Object add_to_cascaded_history(history,value)
    Object history, value;
{
    Object temp, temp_1, temp_2;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(174,29);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = ISVREF(history,(SI_Long)5L);
	temp_1 = ISVREF(history,(SI_Long)8L);
	temp_2 = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	result = store_history_value(temp,temp_1,temp_2,
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		(SI_Long)0L)),Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* UPDATE-GENERIC-HISTORY-FOR-CHANGE-TO-CASCADED-RING-BUFFER */
Object update_generic_history_for_change_to_cascaded_ring_buffer(history)
    Object history;
{
    x_note_fn_call(174,30);
    if (EQ(ISVREF(history,(SI_Long)4L),Qvariable)) {
	if (Trace_validate_p)
	    format((SI_Long)5L,T,"invalidating gh=~s for ~s from ~S~%",
		    history,ISVREF(history,(SI_Long)5L),ISVREF(history,
		    (SI_Long)5L) ? Nil : Qnil);
	invalidate_extrema_caches(history);
	remove_generic_history_as_client_to_history_of_variable(history);
	return VALUES_1(ISVREF(history,(SI_Long)5L) = Nil);
    }
    else
	return VALUES_1(Nil);
}

/* ADD-GENERIC-HISTORY-AS-CLIENT-TO-HISTORY-OF-VARIABLE */
Object add_generic_history_as_client_to_history_of_variable(history)
    Object history;
{
    Object cascaded_ring_buffer_qm;

    x_note_fn_call(174,31);
    cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,history);
    if (cascaded_ring_buffer_qm)
	return add_cascaded_ring_buffer_client(history,
		cascaded_ring_buffer_qm);
    else
	return VALUES_1(Nil);
}

/* REMOVE-GENERIC-HISTORY-AS-CLIENT-TO-HISTORY-OF-VARIABLE */
Object remove_generic_history_as_client_to_history_of_variable(history)
    Object history;
{
    Object cascaded_ring_buffer_qm;

    x_note_fn_call(174,32);
    cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,history);
    if (cascaded_ring_buffer_qm)
	return remove_cascaded_ring_buffer_client(history,
		cascaded_ring_buffer_qm);
    else if (Trace_validate_p)
	return format((SI_Long)4L,T,"failed remove gh=~s client from ~s~%",
		history,Nil);
    else
	return VALUES_1(Qnil);
}

static Object Qcell_array;         /* cell-array */

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* VALIDATE-VARIABLE-HISTORY */
Object validate_variable_history(history)
    Object history;
{
    Object temp, frame, cell_array_qm, cell_array_index_qm;
    Object variable_in_history_qm, cached_variable_qm, var_change_p;
    Object gensymed_symbol, x, y, xa, ya, frame_serial_number_setf_arg, old;
    Object new_1, svref_new_value;
    char temp_1;

    x_note_fn_call(174,33);
    remove_generic_history_as_client_to_history_of_variable(history);
    temp = ISVREF(history,(SI_Long)6L);
    frame = CAR(temp);
    cell_array_qm = get_lookup_slot_value_given_default(frame,Qcell_array,Nil);
    temp = ISVREF(history,(SI_Long)6L);
    cell_array_index_qm = CADR(temp);
    variable_in_history_qm = ISVREF(history,(SI_Long)5L);
    cached_variable_qm = cell_array_index_qm && cell_array_qm ? 
	    ISVREF(FIXNUM_LE(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
	    IFIX(FIXNUM_ADD(cell_array_index_qm,
	    Managed_array_index_offset))) : 
	    ISVREF(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
	    (IFIX(cell_array_index_qm) >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),IFIX(cell_array_index_qm) & (SI_Long)1023L),
	    (SI_Long)6L) : Qnil;
    var_change_p = Nil;
    temp_1 =  !TRUEP(cached_variable_qm);
    if (temp_1);
    else
	temp_1 = FIXNUMP(cached_variable_qm);
    if (temp_1);
    else {
	gensymed_symbol = ISVREF(cached_variable_qm,(SI_Long)3L);
	temp_1 =  ! !(FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil));
    }
    if (temp_1);
    else if (variable_in_history_qm && EQ(variable_in_history_qm,
	    cached_variable_qm)) {
	gensymed_symbol = ISVREF(cached_variable_qm,(SI_Long)3L);
	temp_1 = SIMPLE_VECTOR_P(cached_variable_qm) ? 
		EQ(ISVREF(cached_variable_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp_1);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(history,(SI_Long)7L);
	    if (FIXNUMP(y))
		temp_1 = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
			    M_CDR(x)) : TRUEP(Qnil);
	    }
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	if (Trace_validate_p)
	    format((SI_Long)4L,T,
		    "validate case 1 cachvar=~s var-in-h=~s~%",
		    cached_variable_qm,variable_in_history_qm);
	if (variable_in_history_qm) {
	    ISVREF(history,(SI_Long)5L) = Nil;
	    invalidate_extrema_caches(history);
	    var_change_p = T;
	}
    }
    else if (EQ(variable_in_history_qm,cached_variable_qm)) {
	if (Trace_validate_p)
	    format((SI_Long)2L,T,"validate case 2~%");
    }
    else {
	if (Trace_validate_p) {
	    format((SI_Long)2L,T,"validate case 3~%");
	    format((SI_Long)4L,T,
		    "setting new variable for gh old ~S new ~s~%",
		    variable_in_history_qm,cached_variable_qm);
	}
	ISVREF(history,(SI_Long)5L) = cached_variable_qm;
	frame_serial_number_setf_arg = ISVREF(cached_variable_qm,(SI_Long)3L);
	old = ISVREF(history,(SI_Long)7L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	ISVREF(history,(SI_Long)7L) = svref_new_value;
	invalidate_extrema_caches(history);
	var_change_p = T;
    }
    add_generic_history_as_client_to_history_of_variable(history);
    return VALUES_1(var_change_p);
}

/* RESET-CONSTANT-HISTORY */
Object reset_constant_history(history)
    Object history;
{
    x_note_fn_call(174,34);
    return reset_generic_history_internal(history);
}

/* RESET-CASCADED-HISTORY */
Object reset_cascaded_history(history)
    Object history;
{
    x_note_fn_call(174,35);
    reset_generic_history_internal(history);
    return clear_history_buffer(ISVREF(history,(SI_Long)5L));
}

/* RESET-VARIABLE-HISTORY */
Object reset_variable_history(history)
    Object history;
{
    x_note_fn_call(174,36);
    validate_variable_history(history);
    if (Trace_validate_p)
	format((SI_Long)2L,T,"in reset~%");
    remove_generic_history_as_client_to_history_of_variable(history);
    reset_generic_history_internal(history);
    return VALUES_1(ISVREF(history,(SI_Long)5L) = Nil);
}

/* RECLAIM-CONSTANT-HISTORY */
Object reclaim_constant_history varargs_1(int, n)
{
    Object history;
    Object delete_p, managed_float;
    Declare_varargs_nonrelocating;

    x_note_fn_call(174,37);
    INIT_ARGS_nonrelocating();
    history = REQUIRED_ARG_nonrelocating();
    delete_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    reclaim_generic_history_internal(history);
    if (ISVREF(history,(SI_Long)5L)) {
	managed_float = ISVREF(history,(SI_Long)5L);
	reclaim_managed_simple_float_array_of_length_1(managed_float);
    }
    ISVREF(history,(SI_Long)5L) = Nil;
    if (delete_p)
	return delete_frame(history);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-CASCADED-HISTORY */
Object reclaim_cascaded_history varargs_1(int, n)
{
    Object history;
    Object delete_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(174,38);
    INIT_ARGS_nonrelocating();
    history = REQUIRED_ARG_nonrelocating();
    delete_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    reclaim_generic_history_internal(history);
    if (ISVREF(history,(SI_Long)5L))
	reclaim_history_buffer(ISVREF(history,(SI_Long)5L));
    ISVREF(history,(SI_Long)5L) = Nil;
    if (delete_p)
	return delete_frame(history);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-VARIABLE-HISTORY */
Object reclaim_variable_history varargs_1(int, n)
{
    Object history;
    Object delete_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(174,39);
    INIT_ARGS_nonrelocating();
    history = REQUIRED_ARG_nonrelocating();
    delete_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Trace_validate_p)
	format((SI_Long)2L,T,"in reclaim~%");
    remove_generic_history_as_client_to_history_of_variable(history);
    reclaim_generic_history_internal(history);
    ISVREF(history,(SI_Long)5L) = Nil;
    if (delete_p)
	return delete_frame(history);
    else
	return VALUES_1(Nil);
}

static Object Qmaximum;            /* maximum */

static Object Qminimum;            /* minimum */

/* INITIALIZE-GENERIC-HISTORY */
Object initialize_generic_history(history,length_1)
    Object history, length_1;
{
    Object svref_new_value;

    x_note_fn_call(174,40);
    svref_new_value = allocate_extremum_cache(history,Qmaximum,
	    chestnut_floorf_function(length_1,FIX((SI_Long)32L)));
    ISVREF(history,(SI_Long)2L) = svref_new_value;
    svref_new_value = allocate_extremum_cache(history,Qminimum,
	    chestnut_floorf_function(length_1,FIX((SI_Long)32L)));
    return VALUES_1(ISVREF(history,(SI_Long)3L) = svref_new_value);
}

/* RESET-GENERIC-HISTORY-INTERNAL */
Object reset_generic_history_internal(history)
    Object history;
{
    x_note_fn_call(174,41);
    reset_extremum_cache(ISVREF(history,(SI_Long)2L),history);
    return reset_extremum_cache(ISVREF(history,(SI_Long)3L),history);
}

/* RECLAIM-GENERIC-HISTORY-INTERNAL */
Object reclaim_generic_history_internal(history)
    Object history;
{
    x_note_fn_call(174,42);
    if (ISVREF(history,(SI_Long)3L))
	delete_extremum_cache(ISVREF(history,(SI_Long)3L),history);
    ISVREF(history,(SI_Long)3L) = Nil;
    if (ISVREF(history,(SI_Long)2L))
	delete_extremum_cache(ISVREF(history,(SI_Long)2L),history);
    return VALUES_1(ISVREF(history,(SI_Long)2L) = Nil);
}

/* UPDATE-GENERIC-HISTORY-FOR-CLOCK-DISCONTINUITY */
Object update_generic_history_for_clock_discontinuity(history,time_delta)
    Object history, time_delta;
{
    x_note_fn_call(174,43);
    if (EQ(ISVREF(history,(SI_Long)4L),Qcascaded))
	return add_delta_to_history_buffer_base_time(ISVREF(history,
		(SI_Long)5L),time_delta);
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

/* GET-VARIABLE-FOR-DESIGNATION */
Object get_variable_for_designation(designation)
    Object designation;
{
    Object variables_that_did_not_have_values, current_computation_flags;
    Object variable_qm, x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(174,44);
    if (System_is_running || System_has_paused) {
	variables_that_did_not_have_values = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
		1);
	  current_computation_flags = Current_computation_flags;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    variable_qm = Nil;
	    Current_computation_flags = 
		    FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    variable_qm = evaluate_designation(designation,Nil);
	    if (SIMPLE_VECTOR_P(variable_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(variable_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(variable_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(variable_qm,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(variable_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_or_parameter_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		result = VALUES_1(variable_qm);
	    else {
		if (SIMPLE_VECTOR_P(variable_qm) && EQ(ISVREF(variable_qm,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_temporary_constant_g2_struct))
		    reclaim_temporary_constant_1(variable_qm);
		result = VALUES_1(Nil);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant;     /* "The plot expression \"~ND\" indicates variable or parameter without history." */

static Object string_constant_1;   /* "The plot expression \"~ND\" did not evaluate to a variable or parameter." */

/* GET-CASCADED-RING-BUFFER-FOR-DESIGNATION */
Object get_cascaded_ring_buffer_for_designation varargs_1(int, n)
{
    Object designation;
    Object give_operator_message_p, variable_qm, cascaded_ring_buffer_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(174,45);
    INIT_ARGS_nonrelocating();
    designation = REQUIRED_ARG_nonrelocating();
    give_operator_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    variable_qm = get_variable_for_designation(designation);
    cascaded_ring_buffer_qm = variable_qm ? ISVREF(variable_qm,
	    (SI_Long)24L) : Qnil;
    if (cascaded_ring_buffer_qm)
	return VALUES_1(cascaded_ring_buffer_qm);
    else if (variable_qm) {
	if (give_operator_message_p) {
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		return give_warning_1(3,FIX((SI_Long)1L),string_constant,
			designation);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (give_operator_message_p) {
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    return give_warning_1(3,FIX((SI_Long)1L),string_constant_1,
		    designation);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_details;  /* simulation-details */

static Object string_constant_2;   /* "The variable or parameter ~a does not have a history." */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object string_constant_3;   /* "No variable or parameter available" */

/* GET-CASCADED-RING-BUFFER-FOR-HISTORY */
Object get_cascaded_ring_buffer_for_history varargs_1(int, n)
{
    Object history;
    Object give_operator_message_p, temp, unchecked_variable_qm;
    Object gensymed_symbol, x, y, xa, ya, variable_qm, designation_qm;
    Object sub_class_bit_vector, simulation_details_qm;
    Object cascaded_ring_buffer_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(174,46);
    INIT_ARGS_nonrelocating();
    history = REQUIRED_ARG_nonrelocating();
    give_operator_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	return VALUES_1(Nil);
    else if (EQ(temp,Qcascaded))
	return VALUES_1(ISVREF(history,(SI_Long)5L));
    else if (EQ(temp,Qvariable)) {
	unchecked_variable_qm = ISVREF(history,(SI_Long)5L);
	if (unchecked_variable_qm) {
	    gensymed_symbol = ISVREF(unchecked_variable_qm,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(unchecked_variable_qm) ? 
		    EQ(ISVREF(unchecked_variable_qm,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else {
		x = gensymed_symbol;
		y = ISVREF(history,(SI_Long)7L);
		if (FIXNUMP(y))
		    temp_1 = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
		else if (FIXNUMP(x))
		    temp_1 = TRUEP(Nil);
		else {
		    xa = M_CAR(y);
		    ya = M_CAR(x);
		    temp_1 = FIXNUM_LT(xa,ya);
		    if (temp_1);
		    else
			temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
				M_CDR(x)) : TRUEP(Qnil);
		}
	    }
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	variable_qm = temp_1 ? unchecked_variable_qm : Nil;
	if (variable_qm) {
	    designation_qm = ISVREF(history,(SI_Long)6L);
	    if (designation_qm && CADDR(designation_qm)) {
		sub_class_bit_vector = ISVREF(ISVREF(variable_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    simulation_details_qm = 
			    get_lookup_slot_value(variable_qm,
			    Qsimulation_details);
		    cascaded_ring_buffer_qm = simulation_details_qm ? 
			    ISVREF(simulation_details_qm,(SI_Long)20L) : Qnil;
		}
		else
		    cascaded_ring_buffer_qm = Nil;
	    }
	    else
		cascaded_ring_buffer_qm = ISVREF(variable_qm,(SI_Long)24L);
	}
	else
	    cascaded_ring_buffer_qm = Nil;
	if (cascaded_ring_buffer_qm)
	    return VALUES_1(cascaded_ring_buffer_qm);
	else if (variable_qm) {
	    if (give_operator_message_p) {
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(3,FIX((SI_Long)1L),string_constant_2,
			    get_lookup_slot_value_given_default(variable_qm,
			    Qname_or_names_for_frame,Nil));
	    }
	    return VALUES_1(Nil);
	}
	else {
	    if (give_operator_message_p) {
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(2,FIX((SI_Long)1L),string_constant_3);
	    }
	    return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Qnil);
}

/* GENERIC-HISTORY-SUPPORTS-INDEXED-ACCESS-P */
Object generic_history_supports_indexed_access_p(history)
    Object history;
{
    Object temp;

    x_note_fn_call(174,47);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	return VALUES_1(Nil);
    else if (EQ(temp,Qcascaded) || EQ(temp,Qvariable))
	return VALUES_1(T);
    else
	return VALUES_1(Qnil);
}

static Object Qinclusive;          /* inclusive */

static Object Qexclusive;          /* exclusive */

static Object Qloose;              /* loose */

/* GENERIC-HISTORY-INDEX */
Object generic_history_index(history,timestamp,inclusion,low_bound_p)
    Object history, timestamp, inclusion, low_bound_p;
{
    Object history_type, cascaded_ring_buffer, cascaded_ring_buffer_qm, temp;
    Object ring_buffer, index_1, time_for_index, next_index_qm;
    Object time_for_next_index, prev_index_qm, time_for_prev_index;
    char temp_1;
    double arg, arg_1;

    x_note_fn_call(174,48);
    history_type = ISVREF(history,(SI_Long)4L);
    if (EQ(history_type,Qconstant))
	return VALUES_1(FIX((SI_Long)0L));
    else if (EQ(history_type,Qcascaded) || EQ(history_type,Qvariable)) {
	if (EQ(history_type,Qcascaded))
	    cascaded_ring_buffer = ISVREF(history,(SI_Long)5L);
	else {
	    cascaded_ring_buffer_qm = 
		    get_cascaded_ring_buffer_for_history(1,history);
	    cascaded_ring_buffer = cascaded_ring_buffer_qm;
	}
	temp = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
	ring_buffer = CAR(temp);
	index_1 = get_history_index_by_binary_search(cascaded_ring_buffer,
		timestamp,Nil);
	time_for_index = normalize_to_gensym_float(get_history_g2_time(2,
		cascaded_ring_buffer,index_1));
	if (EQ(inclusion,Qinclusive)) {
	    if (low_bound_p) {
		arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_index);
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		temp_1 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?
			  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		next_index_qm = FIXNUM_NE(ISVREF(ring_buffer,(SI_Long)1L),
			index_1) ? (FIXNUM_EQ(index_1,
			FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			FIX((SI_Long)0L) : FIXNUM_ADD1(index_1)) : Qnil;
		time_for_next_index = next_index_qm ? 
			normalize_to_gensym_float(get_history_g2_time(2,
			cascaded_ring_buffer,next_index_qm)) : Qnil;
		if (next_index_qm) {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_next_index);
		    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    temp_1 = arg >= arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    return VALUES_1(next_index_qm);
		else
		    return VALUES_1(index_1);
	    }
	    else {
		if ( !TRUEP(low_bound_p)) {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_index);
		    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    temp_1 = arg > arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    prev_index_qm = FIXNUM_NE(ISVREF(ring_buffer,
			    (SI_Long)2L),index_1) ? (IFIX(index_1) == 
			    (SI_Long)0L ? FIXNUM_SUB1(ISVREF(ring_buffer,
			    (SI_Long)4L)) : FIXNUM_SUB1(index_1)) : Qnil;
		    time_for_prev_index = prev_index_qm ? 
			    normalize_to_gensym_float(get_history_g2_time(2,
			    cascaded_ring_buffer,prev_index_qm)) : Qnil;
		    if (prev_index_qm) {
			arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_prev_index);
			arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			temp_1 = arg <= arg_1 &&  
				!inline_nanp_for_comparison(arg) ?  
				!inline_nanp_for_comparison(arg_1) : 
				TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			return VALUES_1(prev_index_qm);
		    else
			return VALUES_1(index_1);
		}
		else
		    return VALUES_1(index_1);
	    }
	}
	else if (EQ(inclusion,Qexclusive)) {
	    if (low_bound_p) {
		arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_index);
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		temp_1 = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) 
			?  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		next_index_qm = FIXNUM_NE(ISVREF(ring_buffer,(SI_Long)1L),
			index_1) ? (FIXNUM_EQ(index_1,
			FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			FIX((SI_Long)0L) : FIXNUM_ADD1(index_1)) : Qnil;
		time_for_next_index = next_index_qm ? 
			normalize_to_gensym_float(get_history_g2_time(2,
			cascaded_ring_buffer,next_index_qm)) : Qnil;
		if (next_index_qm) {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_next_index);
		    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    temp_1 = arg > arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    return VALUES_1(next_index_qm);
		else
		    return VALUES_1(index_1);
	    }
	    else {
		if ( !TRUEP(low_bound_p)) {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_index);
		    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    temp_1 = arg >= arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    prev_index_qm = FIXNUM_NE(ISVREF(ring_buffer,
			    (SI_Long)2L),index_1) ? (IFIX(index_1) == 
			    (SI_Long)0L ? FIXNUM_SUB1(ISVREF(ring_buffer,
			    (SI_Long)4L)) : FIXNUM_SUB1(index_1)) : Qnil;
		    time_for_prev_index = prev_index_qm ? 
			    normalize_to_gensym_float(get_history_g2_time(2,
			    cascaded_ring_buffer,prev_index_qm)) : Qnil;
		    if (prev_index_qm) {
			arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_prev_index);
			arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			temp_1 = arg < arg_1 &&  
				!inline_nanp_for_comparison(arg) ?  
				!inline_nanp_for_comparison(arg_1) : 
				TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			return VALUES_1(prev_index_qm);
		    else
			return VALUES_1(index_1);
		}
		else
		    return VALUES_1(index_1);
	    }
	}
	else if (EQ(inclusion,Qloose)) {
	    if (low_bound_p) {
		arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_index);
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?
			  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		prev_index_qm = FIXNUM_NE(ISVREF(ring_buffer,(SI_Long)2L),
			index_1) ? (IFIX(index_1) == (SI_Long)0L ? 
			FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L)) : 
			FIXNUM_SUB1(index_1)) : Qnil;
		time_for_prev_index = prev_index_qm ? 
			normalize_to_gensym_float(get_history_g2_time(2,
			cascaded_ring_buffer,prev_index_qm)) : Qnil;
		if (prev_index_qm) {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_prev_index);
		    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    temp_1 = arg <= arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    return VALUES_1(prev_index_qm);
		else
		    return VALUES_1(index_1);
	    }
	    else {
		if ( !TRUEP(low_bound_p)) {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_index);
		    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
		    temp_1 = arg < arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    next_index_qm = FIXNUM_NE(ISVREF(ring_buffer,
			    (SI_Long)1L),index_1) ? (FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     FIX((SI_Long)0L) : FIXNUM_ADD1(index_1)) : Qnil;
		    time_for_next_index = next_index_qm ? 
			    normalize_to_gensym_float(get_history_g2_time(2,
			    cascaded_ring_buffer,next_index_qm)) : Qnil;
		    if (next_index_qm) {
			arg = DOUBLE_FLOAT_TO_DOUBLE(time_for_next_index);
			arg_1 = DOUBLE_FLOAT_TO_DOUBLE(timestamp);
			temp_1 = arg >= arg_1 &&  
				!inline_nanp_for_comparison(arg) ?  
				!inline_nanp_for_comparison(arg_1) : 
				TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			return VALUES_1(next_index_qm);
		    else
			return VALUES_1(index_1);
		}
		else
		    return VALUES_1(index_1);
	    }
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

/* SMALLEST-LESSER-FACTOR */
Object smallest_lesser_factor(n_1)
    Object n_1;
{
    Object lim, temp, temp_1;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(174,49);
    if (oddp(n_1)) {
	lim = isqrt(n_1);
	i = (SI_Long)3L;
	ab_loop_bind_ = IFIX(lim);
      next_loop:
	if (i > ab_loop_bind_)
	    goto end_loop;
	temp = FIX((SI_Long)0L);
	temp_1 = chestnut_modf_function(n_1,FIX(i));
	if (NUM_EQ(temp,temp_1))
	    return VALUES_1(FIX(i));
	i = i + (SI_Long)2L;
	goto next_loop;
      end_loop:
	return VALUES_1(Nil);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(FIX((SI_Long)2L));
}

/* GET-NEXT-HIGHEST-PRIME */
Object get_next_highest_prime(n_1)
    Object n_1;
{
    SI_Long test;

    x_note_fn_call(174,50);
    if ( !TRUEP(oddp(n_1)))
	n_1 = FIXNUM_ADD1(n_1);
    test = IFIX(n_1);
  next_loop:
    if ( !TRUEP(smallest_lesser_factor(FIX(test))))
	return VALUES_1(FIX(test));
    test = test + (SI_Long)2L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ALLOCATE-EXTREMUM-CACHE */
Object allocate_extremum_cache(history,polarity,zone_count)
    Object history, polarity, zone_count;
{
    Object extremum_cache, zone_index_size, svref_new_value;

    x_note_fn_call(174,51);
    extremum_cache = make_extremum_cache_1();
    zone_index_size = get_next_highest_prime(zone_count);
    SVREF(extremum_cache,FIX((SI_Long)1L)) = polarity;
    SVREF(extremum_cache,FIX((SI_Long)2L)) = history;
    SVREF(extremum_cache,FIX((SI_Long)6L)) = zone_index_size;
    svref_new_value = allocate_managed_array(1,zone_index_size);
    SVREF(extremum_cache,FIX((SI_Long)5L)) = svref_new_value;
    SVREF(extremum_cache,FIX((SI_Long)4L)) = zone_count;
    svref_new_value = allocate_managed_array(1,zone_count);
    SVREF(extremum_cache,FIX((SI_Long)3L)) = svref_new_value;
    return reset_extremum_cache(extremum_cache,history);
}

/* COPY-EXTREMUM-CACHE */
Object copy_extremum_cache(extremum_cache,history)
    Object extremum_cache, history;
{
    Object new_extremum_cache, gensymed_symbol, gensymed_symbol_1;
    Object svref_new_value;

    x_note_fn_call(174,52);
    new_extremum_cache = make_extremum_cache_1();
    gensymed_symbol = extremum_cache;
    gensymed_symbol_1 = new_extremum_cache;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,(SI_Long)1L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,(SI_Long)3L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,(SI_Long)4L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)4L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,(SI_Long)5L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)5L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,(SI_Long)6L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)6L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,(SI_Long)7L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,(SI_Long)8L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,(SI_Long)9L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)9L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,
	    (SI_Long)10L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)10L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,
	    (SI_Long)11L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)11L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,
	    (SI_Long)12L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)12L)) = svref_new_value;
    svref_new_value = copy_for_slot_value(ISVREF(gensymed_symbol,
	    (SI_Long)13L));
    SVREF(gensymed_symbol_1,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(new_extremum_cache,FIX((SI_Long)2L)) = history;
    return VALUES_1(new_extremum_cache);
}

/* RESET-EXTREMUM-CACHE */
Object reset_extremum_cache(extremum_cache,history)
    Object extremum_cache, history;
{
    Object zone_count, temp, history_size_qm, ring_buffer_qm;
    Object cascaded_ring_buffer_qm, old_data_lost, zone_vector, svref_arg_1;
    Object zone_index;
    SI_Long zone_width, i, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(174,53);
    zone_count = ISVREF(extremum_cache,(SI_Long)4L);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	history_size_qm = FIX((SI_Long)1L);
    else if (EQ(temp,Qcascaded)) {
	temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	ring_buffer_qm = CAR(temp);
	history_size_qm = ring_buffer_qm ? ISVREF(ring_buffer_qm,
		(SI_Long)4L) : FIX((SI_Long)0L);
    }
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	if (cascaded_ring_buffer_qm) {
	    cascaded_ring_buffer_qm = 
		    get_cascaded_ring_buffer_for_history(1,history);
	    if (cascaded_ring_buffer_qm) {
		temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		ring_buffer_qm = CAR(temp);
	    }
	    else
		ring_buffer_qm = Nil;
	}
	else
	    ring_buffer_qm = Nil;
	history_size_qm = ring_buffer_qm ? ISVREF(ring_buffer_qm,
		(SI_Long)4L) : FIX((SI_Long)0L);
    }
    else
	history_size_qm = FIX((SI_Long)0L);
    zone_width = history_size_qm ? IFIX(ceiling(history_size_qm,
	    zone_count)) : (SI_Long)2L;
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	old_data_lost = FIX((SI_Long)0L);
    else if (EQ(temp,Qcascaded))
	old_data_lost = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)6L);
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	old_data_lost = cascaded_ring_buffer_qm ? 
		ISVREF(cascaded_ring_buffer_qm,(SI_Long)6L) : FIX((SI_Long)0L);
    }
    else
	old_data_lost = FIX((SI_Long)0L);
    SVREF(extremum_cache,FIX((SI_Long)12L)) = Nil;
    SVREF(extremum_cache,FIX((SI_Long)11L)) = Nil;
    ISVREF(extremum_cache,(SI_Long)7L) = FIX((SI_Long)0L);
    zone_vector = ISVREF(extremum_cache,(SI_Long)3L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(extremum_cache,(SI_Long)4L));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    reclaim_slot_value_list_1(FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(zone_vector,i + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(zone_vector,
	    (i >>  -  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L));
    if (FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(zone_vector,svref_arg_2) = Nil;
    }
    else {
	svref_arg_1 = ISVREF(zone_vector,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    zone_index = ISVREF(extremum_cache,(SI_Long)5L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(extremum_cache,(SI_Long)6L));
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    reclaim_slot_value_tree_1(FIXNUM_LE(ISVREF(zone_index,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(zone_index,i + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(zone_index,
	    (i >>  -  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L));
    if (FIXNUM_LE(ISVREF(zone_index,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(zone_index,svref_arg_2) = Nil;
    }
    else {
	svref_arg_1 = ISVREF(zone_index,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    reclaim_slot_value_list_1(ISVREF(extremum_cache,(SI_Long)8L));
    SVREF(extremum_cache,FIX((SI_Long)8L)) = Nil;
    ISVREF(extremum_cache,(SI_Long)9L) = FIX(zone_width);
    SVREF(extremum_cache,FIX((SI_Long)10L)) = old_data_lost;
    SVREF(extremum_cache,FIX((SI_Long)13L)) = T;
    return VALUES_1(extremum_cache);
}

/* DELETE-EXTREMUM-CACHE */
Object delete_extremum_cache(extremum_cache,history)
    Object extremum_cache, history;
{
    Object zone_vector, svref_arg_1, zone_index;
    SI_Long i, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(174,54);
    reclaim_slot_value_list_1(ISVREF(extremum_cache,(SI_Long)8L));
    SVREF(extremum_cache,FIX((SI_Long)8L)) = Nil;
    zone_vector = ISVREF(extremum_cache,(SI_Long)3L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(extremum_cache,(SI_Long)4L));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    reclaim_slot_value_list_1(FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(zone_vector,i + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(zone_vector,
	    (i >>  -  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L));
    if (FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(zone_vector,svref_arg_2) = Nil;
    }
    else {
	svref_arg_1 = ISVREF(zone_vector,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    zone_index = ISVREF(extremum_cache,(SI_Long)5L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(extremum_cache,(SI_Long)6L));
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    reclaim_slot_value_tree_1(FIXNUM_LE(ISVREF(zone_index,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(zone_index,i + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(zone_index,
	    (i >>  -  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L));
    if (FIXNUM_LE(ISVREF(zone_index,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(zone_index,svref_arg_2) = Nil;
    }
    else {
	svref_arg_1 = ISVREF(zone_index,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    SVREF(extremum_cache,FIX((SI_Long)2L)) = Nil;
    return reclaim_extremum_cache_1(extremum_cache);
}

/* GET-ZONE-START */
Object get_zone_start(history,extremum_cache,absolute_start)
    Object history, extremum_cache, absolute_start;
{
    x_note_fn_call(174,55);
    return minus(absolute_start,
	    chestnut_modf_function(FIXNUM_MINUS(absolute_start,
	    ISVREF(extremum_cache,(SI_Long)10L)),ISVREF(extremum_cache,
	    (SI_Long)9L)));
}

/* ADD-ZONE-CACHE-ELEMENT */
Object add_zone_cache_element(extremum_cache,start_index,value_index)
    Object extremum_cache, start_index, value_index;
{
    Object zone_vector, lru_element_index, temp, n_2nd_to_lru_element_index;
    Object temp_1, temp_2, vector_index, zones_in_use, svref_new_value;
    Object zone_cache_element;
    SI_Long svref_arg_2;

    x_note_fn_call(174,56);
    zone_vector = ISVREF(extremum_cache,(SI_Long)3L);
    if (FIXNUM_EQ(ISVREF(extremum_cache,(SI_Long)7L),ISVREF(extremum_cache,
	    (SI_Long)4L))) {
	lru_element_index = ISVREF(extremum_cache,(SI_Long)11L);
	temp = FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(zone_vector,
		IFIX(FIXNUM_ADD(lru_element_index,
		Managed_array_index_offset))) : ISVREF(ISVREF(zone_vector,
		(IFIX(lru_element_index) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(lru_element_index) & (SI_Long)1023L);
	n_2nd_to_lru_element_index = CADR(temp);
	temp_1 = FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(zone_vector,
		IFIX(FIXNUM_ADD(n_2nd_to_lru_element_index,
		Managed_array_index_offset))) : ISVREF(ISVREF(zone_vector,
		(IFIX(n_2nd_to_lru_element_index) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(n_2nd_to_lru_element_index) & 
		(SI_Long)1023L);
	M_CAR(temp_1) = Nil;
	SVREF(extremum_cache,FIX((SI_Long)11L)) = n_2nd_to_lru_element_index;
	remove_zone_cache_element_index(extremum_cache,start_index);
	temp = ISVREF(extremum_cache,(SI_Long)2L);
	temp_2 = FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(zone_vector,
		IFIX(FIXNUM_ADD(lru_element_index,
		Managed_array_index_offset))) : ISVREF(ISVREF(zone_vector,
		(IFIX(lru_element_index) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(lru_element_index) & (SI_Long)1023L);
	remove_zone_cache_element_index(extremum_cache,get_zone_start(temp,
		extremum_cache,CADDR(temp_2)));
	vector_index = lru_element_index;
    }
    else {
	zones_in_use = ISVREF(extremum_cache,(SI_Long)7L);
	if ( !(FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? TRUEP(ISVREF(zone_vector,
		IFIX(FIXNUM_ADD(zones_in_use,
		Managed_array_index_offset)))) : 
		TRUEP(ISVREF(ISVREF(zone_vector,(IFIX(zones_in_use) >>  -  
		- (SI_Long)10L) + (SI_Long)2L),IFIX(zones_in_use) & 
		(SI_Long)1023L)))) {
	    if (FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(zones_in_use,Managed_array_index_offset);
		svref_new_value = slot_value_list_3(Nil,Nil,Nil);
		SVREF(zone_vector,temp_1) = svref_new_value;
	    }
	    else {
		temp_1 = ISVREF(zone_vector,(IFIX(zones_in_use) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = IFIX(zones_in_use) & (SI_Long)1023L;
		svref_new_value = slot_value_list_3(Nil,Nil,Nil);
		ISVREF(temp_1,svref_arg_2) = svref_new_value;
	    }
	}
	temp_1 = add1(ISVREF(extremum_cache,(SI_Long)7L));
	SVREF(extremum_cache,FIX((SI_Long)7L)) = temp_1;
	vector_index = zones_in_use;
    }
    zone_cache_element = FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(zone_vector,
	    IFIX(FIXNUM_ADD(vector_index,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(zone_vector,(IFIX(vector_index) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(vector_index) & (SI_Long)1023L);
    M_CADDR(zone_cache_element) = value_index;
    add_zone_cache_element_index(extremum_cache,start_index,vector_index);
    return make_zone_cache_element_most_recent(extremum_cache,
	    zone_cache_element,vector_index);
}

/* ADD-ZONE-CACHE-ELEMENT-INDEX */
Object add_zone_cache_element_index(extremum_cache,start_index,vector_index)
    Object extremum_cache, start_index, vector_index;
{
    Object svref_arg_1, temp, slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value;
    SI_Long svref_arg_2;

    x_note_fn_call(174,57);
    svref_arg_1 = ISVREF(extremum_cache,(SI_Long)5L);
    temp = chestnut_modf_function(start_index,ISVREF(extremum_cache,
	    (SI_Long)6L));
    slot_value_push_modify_macro_arg = slot_value_cons_1(start_index,
	    vector_index);
    car_1 = slot_value_push_modify_macro_arg;
    cdr_1 = FIXNUM_LE(ISVREF(svref_arg_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(svref_arg_1,
	    IFIX(FIXNUM_ADD(temp,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(svref_arg_1,(IFIX(temp) >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),IFIX(temp) & (SI_Long)1023L);
    svref_new_value = slot_value_cons_1(car_1,cdr_1);
    if (FIXNUM_LE(ISVREF(svref_arg_1,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(temp,Managed_array_index_offset);
	return VALUES_1(SVREF(svref_arg_1,temp) = svref_new_value);
    }
    else {
	svref_arg_1 = ISVREF(svref_arg_1,(IFIX(temp) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(temp) & (SI_Long)1023L;
	return VALUES_1(ISVREF(svref_arg_1,svref_arg_2) = svref_new_value);
    }
}

/* REMOVE-ZONE-CACHE-ELEMENT-INDEX */
Object remove_zone_cache_element_index(extremum_cache,start_index)
    Object extremum_cache, start_index;
{
    Object chain_index, zone_index, chain, previous_tail, tail, bucket, temp;
    Object svref_new_value;
    SI_Long svref_arg_2;

    x_note_fn_call(174,58);
    chain_index = chestnut_modf_function(start_index,ISVREF(extremum_cache,
	    (SI_Long)6L));
    zone_index = ISVREF(extremum_cache,(SI_Long)5L);
    chain = FIXNUM_LE(ISVREF(zone_index,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(zone_index,
	    IFIX(FIXNUM_ADD(chain_index,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(zone_index,(IFIX(chain_index) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(chain_index) & (SI_Long)1023L);
    previous_tail = Nil;
    tail = chain;
    bucket = Nil;
  next_loop:
    if ( !TRUEP(tail))
	goto end_loop;
    bucket = CAR(tail);
    if (FIXNUM_EQ(M_CAR(bucket),start_index)) {
	if (previous_tail) {
	    temp = CDR(tail);
	    M_CDR(previous_tail) = temp;
	}
	else if (FIXNUM_LE(ISVREF(zone_index,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(chain_index,Managed_array_index_offset);
	    svref_new_value = CDR(tail);
	    SVREF(zone_index,temp) = svref_new_value;
	}
	else {
	    temp = ISVREF(zone_index,(IFIX(chain_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(chain_index) & (SI_Long)1023L;
	    svref_new_value = CDR(tail);
	    ISVREF(temp,svref_arg_2) = svref_new_value;
	}
	reclaim_slot_value_cons_1(bucket);
	reclaim_slot_value_cons_1(tail);
	return VALUES_1(Nil);
    }
    else
	previous_tail = tail;
    tail = M_CDR(tail);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MAKE-ZONE-CACHE-ELEMENT-MOST-RECENT */
Object make_zone_cache_element_most_recent(extremum_cache,
	    zone_cache_element,vector_index)
    Object extremum_cache, zone_cache_element, vector_index;
{
    Object former_most_recent_index, zone_vector;
    Object former_most_recent_zone_cache_element;

    x_note_fn_call(174,59);
    former_most_recent_index = ISVREF(extremum_cache,(SI_Long)12L);
    zone_vector = ISVREF(extremum_cache,(SI_Long)3L);
    if (former_most_recent_index) {
	former_most_recent_zone_cache_element = 
		FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(zone_vector,
		IFIX(FIXNUM_ADD(former_most_recent_index,
		Managed_array_index_offset))) : ISVREF(ISVREF(zone_vector,
		(IFIX(former_most_recent_index) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(former_most_recent_index) & (SI_Long)1023L);
	M_CADR(former_most_recent_zone_cache_element) = vector_index;
    }
    else
	SVREF(extremum_cache,FIX((SI_Long)11L)) = vector_index;
    M_CAR(zone_cache_element) = former_most_recent_index;
    M_CADR(zone_cache_element) = Nil;
    if ( !TRUEP(vector_index))
	error((SI_Long)1L,"Null vector index in make zce most recent ~%");
    return VALUES_1(SVREF(extremum_cache,FIX((SI_Long)12L)) = vector_index);
}

/* LOOKUP-ZONE-CACHE-ELEMENT */
Object lookup_zone_cache_element(extremum_cache,start_index)
    Object extremum_cache, start_index;
{
    Object gensymed_symbol, gensymed_symbol_1, chain, bucket, ab_loop_list_;
    Object vector_index, zone_vector, zone_cache_element, previous_index;
    Object next_index, temp, temp_1;

    x_note_fn_call(174,60);
    if (IFIX(ISVREF(extremum_cache,(SI_Long)7L)) > (SI_Long)0L) {
	gensymed_symbol = ISVREF(extremum_cache,(SI_Long)5L);
	gensymed_symbol_1 = chestnut_modf_function(start_index,
		ISVREF(extremum_cache,(SI_Long)6L));
	chain = FIXNUM_LE(ISVREF(ISVREF(extremum_cache,(SI_Long)5L),
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(extremum_cache,(SI_Long)5L),
		IFIX(FIXNUM_ADD(gensymed_symbol_1,
		Managed_array_index_offset))) : 
		ISVREF(ISVREF(gensymed_symbol,(IFIX(gensymed_symbol_1) >>  
		-  - (SI_Long)10L) + (SI_Long)2L),IFIX(gensymed_symbol_1) 
		& (SI_Long)1023L);
	if (chain) {
	    bucket = Nil;
	    ab_loop_list_ = chain;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    bucket = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (FIXNUM_EQ(M_CAR(bucket),start_index)) {
		vector_index = M_CDR(bucket);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    vector_index = Nil;
	    goto end_1;
	    vector_index = Qnil;
	  end_1:;
	}
	else
	    vector_index = Nil;
	zone_vector = ISVREF(extremum_cache,(SI_Long)3L);
	if (vector_index &&  !FIXNUM_EQ(vector_index,ISVREF(extremum_cache,
		(SI_Long)12L))) {
	    zone_cache_element = FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(zone_vector,
		    IFIX(FIXNUM_ADD(vector_index,
		    Managed_array_index_offset))) : 
		    ISVREF(ISVREF(zone_vector,(IFIX(vector_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(vector_index) & 
		    (SI_Long)1023L);
	    previous_index = CADR(zone_cache_element);
	    next_index = CAR(zone_cache_element);
	    temp = FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(zone_vector,
		    IFIX(FIXNUM_ADD(previous_index,
		    Managed_array_index_offset))) : 
		    ISVREF(ISVREF(zone_vector,(IFIX(previous_index) >>  -  
		    - (SI_Long)10L) + (SI_Long)2L),IFIX(previous_index) & 
		    (SI_Long)1023L);
	    M_CAR(temp) = next_index;
	    if (next_index) {
		temp = FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(zone_vector,
			IFIX(FIXNUM_ADD(next_index,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(zone_vector,(IFIX(next_index) >>  -  
			- (SI_Long)10L) + (SI_Long)2L),IFIX(next_index) & 
			(SI_Long)1023L);
		M_CADR(temp) = previous_index;
	    }
	    else
		SVREF(extremum_cache,FIX((SI_Long)11L)) = previous_index;
	    make_zone_cache_element_most_recent(extremum_cache,
		    zone_cache_element,vector_index);
	}
	if (vector_index) {
	    temp_1 = FIXNUM_LE(ISVREF(zone_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(zone_vector,
		    IFIX(FIXNUM_ADD(vector_index,
		    Managed_array_index_offset))) : 
		    ISVREF(ISVREF(zone_vector,(IFIX(vector_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(vector_index) & 
		    (SI_Long)1023L);
	    return VALUES_1(CADDR(temp_1));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-WHOLE-INTERVAL-EXTREMUM-CACHE */
Object update_whole_interval_extremum_cache(extremum_cache,start,end_1,
	    value_index)
    Object extremum_cache, start, end_1, value_index;
{
    Object triple, svref_new_value;

    x_note_fn_call(174,61);
    triple = ISVREF(extremum_cache,(SI_Long)8L);
    if (triple) {
	M_CAR(triple) = start;
	M_CADR(triple) = end_1;
	return VALUES_1(M_CADDR(triple) = value_index);
    }
    else {
	svref_new_value = slot_value_list_3(start,end_1,value_index);
	return VALUES_1(SVREF(extremum_cache,FIX((SI_Long)8L)) = 
		svref_new_value);
    }
}

/* HISTORY-SIZE-IS-CONSTANT? */
Object history_size_is_constant_qm(history,extremum_cache)
    Object history, extremum_cache;
{
    Object temp, new_size_qm, ring_buffer_qm, cascaded_ring_buffer_qm;

    x_note_fn_call(174,62);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	new_size_qm = FIX((SI_Long)1L);
    else if (EQ(temp,Qcascaded)) {
	temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	ring_buffer_qm = CAR(temp);
	new_size_qm = ring_buffer_qm ? ISVREF(ring_buffer_qm,(SI_Long)4L) :
		 FIX((SI_Long)0L);
    }
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	if (cascaded_ring_buffer_qm) {
	    cascaded_ring_buffer_qm = 
		    get_cascaded_ring_buffer_for_history(1,history);
	    if (cascaded_ring_buffer_qm) {
		temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		ring_buffer_qm = CAR(temp);
	    }
	    else
		ring_buffer_qm = Nil;
	}
	else
	    ring_buffer_qm = Nil;
	new_size_qm = ring_buffer_qm ? ISVREF(ring_buffer_qm,(SI_Long)4L) :
		 FIX((SI_Long)0L);
    }
    else
	new_size_qm = FIX((SI_Long)0L);
    temp = ISVREF(extremum_cache,(SI_Long)14L);
    if (EQL(temp,new_size_qm))
	return VALUES_1(T);
    else {
	SVREF(extremum_cache,FIX((SI_Long)14L)) = new_size_qm;
	return VALUES_1(Nil);
    }
}

static Object float_constant_1;    /* 1.7976931348623158E+# */

static Object float_constant_2;    /* -1.7976931348623158E+# */

static Object float_constant_3;    /* 0.0 */

/* COMPUTE-EXTREMUM-FOR-INTERVAL */
Object compute_extremum_for_interval(history,start,end_1,polarity)
    Object history, start, end_1, polarity;
{
    Object extremum_cache, temp, ring_buffer;
    Object oldest_active_element_index_for_ring_buffer;
    Object cascaded_ring_buffer_qm, triple, triple_old_value, first_zone_start;
    Object extremum_zone_width, interval_length, extreme_value_index;
    Object first_time_p, zone_end, gensymed_symbol_2, gensymed_symbol_3;
    Object history_start, history_end, history_size, ring_buffer_qm, index_1;
    Object vector_1, managed_number_or_value, value, current_value, new_value;
    SI_Long gensymed_symbol, position_in_history, gensymed_symbol_1;
    SI_Long absolute_start, absolute_end, temp_1, zone_start, ab_loop_step_by_;
    char temp_2;
    double arg, arg_1;

    x_note_fn_call(174,63);
    extremum_cache = EQ(polarity,Qminimum) ? ISVREF(history,(SI_Long)3L) : 
	    ISVREF(history,(SI_Long)2L);
    if ( !(ISVREF(extremum_cache,(SI_Long)13L) && 
	    history_size_is_constant_qm(history,extremum_cache)))
	reset_extremum_cache(extremum_cache,history);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	gensymed_symbol = (SI_Long)0L;
    else if (EQ(temp,Qcascaded)) {
	temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	ring_buffer = CAR(temp);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	gensymed_symbol = FIXNUM_GE(start,
		oldest_active_element_index_for_ring_buffer) ? 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(start,
		oldest_active_element_index_for_ring_buffer))) : 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(start,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)));
    }
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	if (cascaded_ring_buffer_qm) {
	    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
	    ring_buffer = CAR(temp);
	}
	else
	    ring_buffer = Nil;
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	gensymed_symbol = FIXNUM_GE(start,
		oldest_active_element_index_for_ring_buffer) ? 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(start,
		oldest_active_element_index_for_ring_buffer))) : 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(start,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)));
    }
    else
	gensymed_symbol = (SI_Long)0L;
    position_in_history = gensymed_symbol - (SI_Long)1L;
    gensymed_symbol = position_in_history;
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	gensymed_symbol_1 = (SI_Long)0L;
    else if (EQ(temp,Qcascaded))
	gensymed_symbol_1 = IFIX(ISVREF(ISVREF(history,(SI_Long)5L),
		(SI_Long)6L));
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	gensymed_symbol_1 = cascaded_ring_buffer_qm ? 
		IFIX(ISVREF(cascaded_ring_buffer_qm,(SI_Long)6L)) : 
		(SI_Long)0L;
    }
    else
	gensymed_symbol_1 = (SI_Long)0L;
    absolute_start = gensymed_symbol + gensymed_symbol_1;
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	gensymed_symbol = (SI_Long)0L;
    else if (EQ(temp,Qcascaded)) {
	temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	ring_buffer = CAR(temp);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	gensymed_symbol = FIXNUM_GE(end_1,
		oldest_active_element_index_for_ring_buffer) ? 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(end_1,
		oldest_active_element_index_for_ring_buffer))) : 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(end_1,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)));
    }
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	if (cascaded_ring_buffer_qm) {
	    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
	    ring_buffer = CAR(temp);
	}
	else
	    ring_buffer = Nil;
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	gensymed_symbol = FIXNUM_GE(end_1,
		oldest_active_element_index_for_ring_buffer) ? 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(end_1,
		oldest_active_element_index_for_ring_buffer))) : 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(end_1,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)));
    }
    else
	gensymed_symbol = (SI_Long)0L;
    position_in_history = gensymed_symbol - (SI_Long)1L;
    gensymed_symbol = position_in_history;
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	gensymed_symbol_1 = (SI_Long)0L;
    else if (EQ(temp,Qcascaded))
	gensymed_symbol_1 = IFIX(ISVREF(ISVREF(history,(SI_Long)5L),
		(SI_Long)6L));
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	gensymed_symbol_1 = cascaded_ring_buffer_qm ? 
		IFIX(ISVREF(cascaded_ring_buffer_qm,(SI_Long)6L)) : 
		(SI_Long)0L;
    }
    else
	gensymed_symbol_1 = (SI_Long)0L;
    absolute_end = gensymed_symbol + gensymed_symbol_1;
    triple = ISVREF(extremum_cache,(SI_Long)8L);
    if (triple) {
	triple_old_value = triple;
	temp_1 = IFIX(FIRST(triple_old_value));
	triple = REST(triple_old_value);
	temp_2 = temp_1 == absolute_start;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	triple_old_value = triple;
	temp_1 = IFIX(FIRST(triple_old_value));
	triple = REST(triple_old_value);
	temp_2 = temp_1 == absolute_end;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	triple_old_value = triple;
	triple = REST(triple_old_value);
    }
    if (Nil)
	return VALUES_1(Nil);
    else {
	first_zone_start = get_zone_start(history,extremum_cache,
		FIX(absolute_start));
	extremum_zone_width = ISVREF(extremum_cache,(SI_Long)9L);
	temp = ISVREF(history,(SI_Long)4L);
	if (EQ(temp,Qconstant))
	    interval_length = error((SI_Long)1L,
		    "indexed access not supported");
	else if (EQ(temp,Qcascaded)) {
	    temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	    ring_buffer = CAR(temp);
	    interval_length = ring_buffer ? (FIXNUM_GE(end_1,start) ? 
		    FIXNUM_ADD1(FIXNUM_MINUS(end_1,start)) : 
		    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(end_1,
		    ISVREF(ring_buffer,(SI_Long)4L)),start))) : 
		    FIX((SI_Long)0L);
	}
	else if (EQ(temp,Qvariable)) {
	    cascaded_ring_buffer_qm = 
		    get_cascaded_ring_buffer_for_history(1,history);
	    if (cascaded_ring_buffer_qm) {
		temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		ring_buffer = CAR(temp);
	    }
	    else
		ring_buffer = Nil;
	    interval_length = ring_buffer ? (FIXNUM_GE(end_1,start) ? 
		    FIXNUM_ADD1(FIXNUM_MINUS(end_1,start)) : 
		    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(end_1,
		    ISVREF(ring_buffer,(SI_Long)4L)),start))) : 
		    FIX((SI_Long)0L);
	}
	else
	    interval_length = FIX((SI_Long)0L);
	extreme_value_index = compute_extremum_for_zone(history,
		extremum_cache,polarity,FIX(absolute_start),
		FIXNUM_GT(interval_length,extremum_zone_width) ? 
		FIXNUM_ADD(first_zone_start,extremum_zone_width) : 
		FIX(absolute_start + IFIX(interval_length)));
	zone_start = IFIX(FIXNUM_ADD(first_zone_start,extremum_zone_width));
	ab_loop_step_by_ = IFIX(extremum_zone_width);
	first_time_p = T;
	zone_end = Nil;
      next_loop:
	zone_end = FIX(zone_start + IFIX(extremum_zone_width));
	if (IFIX(zone_end) > absolute_end) {
	    if ( !(zone_start > absolute_end)) {
		gensymed_symbol_2 = history;
		gensymed_symbol_3 = compute_extremum_for_zone(history,
			extremum_cache,polarity,FIX(zone_start),
			FIX(absolute_end + (SI_Long)1L));
		if (extreme_value_index) {
		    gensymed_symbol = IFIX(extreme_value_index);
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
		    if (EQ(temp,Qconstant))
			gensymed_symbol_1 = (SI_Long)0L;
		    else if (EQ(temp,Qcascaded))
			gensymed_symbol_1 = 
				IFIX(ISVREF(ISVREF(gensymed_symbol_2,
				(SI_Long)5L),(SI_Long)6L));
		    else if (EQ(temp,Qvariable)) {
			cascaded_ring_buffer_qm = 
				get_cascaded_ring_buffer_for_history(1,
				gensymed_symbol_2);
			gensymed_symbol_1 = cascaded_ring_buffer_qm ? 
				IFIX(ISVREF(cascaded_ring_buffer_qm,
				(SI_Long)6L)) : (SI_Long)0L;
		    }
		    else
			gensymed_symbol_1 = (SI_Long)0L;
		    position_in_history = gensymed_symbol - gensymed_symbol_1;
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
		    if (EQ(temp,Qconstant))
			history_start = error((SI_Long)1L,
				"indexed access not supported");
		    else if (EQ(temp,Qcascaded)) {
			temp = ISVREF(ISVREF(gensymed_symbol_2,
				(SI_Long)5L),(SI_Long)4L);
			ring_buffer = CAR(temp);
			history_start = ring_buffer ? ISVREF(ring_buffer,
				(SI_Long)2L) : FIX((SI_Long)0L);
		    }
		    else if (EQ(temp,Qvariable)) {
			cascaded_ring_buffer_qm = 
				get_cascaded_ring_buffer_for_history(1,
				gensymed_symbol_2);
			if (cascaded_ring_buffer_qm) {
			    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
			    ring_buffer = CAR(temp);
			}
			else
			    ring_buffer = Nil;
			history_start = ring_buffer ? ISVREF(ring_buffer,
				(SI_Long)2L) : FIX((SI_Long)0L);
		    }
		    else
			history_start = FIX((SI_Long)0L);
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
		    if (EQ(temp,Qconstant))
			history_end = error((SI_Long)1L,
				"indexed access not supported");
		    else if (EQ(temp,Qcascaded)) {
			temp = ISVREF(ISVREF(gensymed_symbol_2,
				(SI_Long)5L),(SI_Long)4L);
			ring_buffer = CAR(temp);
			history_end = ring_buffer ? ISVREF(ring_buffer,
				(SI_Long)1L) : FIX((SI_Long)0L);
		    }
		    else if (EQ(temp,Qvariable)) {
			cascaded_ring_buffer_qm = 
				get_cascaded_ring_buffer_for_history(1,
				gensymed_symbol_2);
			if (cascaded_ring_buffer_qm) {
			    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
			    ring_buffer = CAR(temp);
			}
			else
			    ring_buffer = Nil;
			history_end = ring_buffer ? ISVREF(ring_buffer,
				(SI_Long)1L) : FIX((SI_Long)0L);
		    }
		    else
			history_end = FIX((SI_Long)0L);
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
		    if (EQ(temp,Qconstant))
			history_size = FIX((SI_Long)1L);
		    else if (EQ(temp,Qcascaded)) {
			temp = ISVREF(ISVREF(gensymed_symbol_2,
				(SI_Long)5L),(SI_Long)4L);
			ring_buffer_qm = CAR(temp);
			history_size = ring_buffer_qm ? 
				ISVREF(ring_buffer_qm,(SI_Long)4L) : 
				FIX((SI_Long)0L);
		    }
		    else if (EQ(temp,Qvariable)) {
			cascaded_ring_buffer_qm = 
				get_cascaded_ring_buffer_for_history(1,
				gensymed_symbol_2);
			if (cascaded_ring_buffer_qm) {
			    cascaded_ring_buffer_qm = 
				    get_cascaded_ring_buffer_for_history(1,
				    gensymed_symbol_2);
			    if (cascaded_ring_buffer_qm) {
				temp = ISVREF(cascaded_ring_buffer_qm,
					(SI_Long)4L);
				ring_buffer_qm = CAR(temp);
			    }
			    else
				ring_buffer_qm = Nil;
			}
			else
			    ring_buffer_qm = Nil;
			history_size = ring_buffer_qm ? 
				ISVREF(ring_buffer_qm,(SI_Long)4L) : 
				FIX((SI_Long)0L);
		    }
		    else
			history_size = FIX((SI_Long)0L);
		    index_1 = NUM_LE(history_start,history_end) ? 
			    FIX(position_in_history + IFIX(history_start)) 
			    : 
			    chestnut_modf_function(FIX(position_in_history 
			    - IFIX(FIXNUM_MINUS(history_size,
			    history_start))),history_size);
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
		    if (EQ(temp,Qconstant))
			temp = ISVREF(gensymed_symbol_2,(SI_Long)5L);
		    else if (EQ(temp,Qcascaded)) {
			temp = ISVREF(ISVREF(gensymed_symbol_2,
				(SI_Long)5L),(SI_Long)4L);
			ring_buffer = CAR(temp);
			if (ring_buffer) {
			    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp = aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    temp = 
					    copy_text_string(managed_number_or_value);
				else
				    temp = managed_number_or_value;
			    }
			    else
				temp = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L));
			}
			else
			    temp = FIX((SI_Long)0L);
		    }
		    else if (EQ(temp,Qvariable)) {
			cascaded_ring_buffer_qm = 
				get_cascaded_ring_buffer_for_history(1,
				gensymed_symbol_2);
			if (cascaded_ring_buffer_qm) {
			    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
			    ring_buffer = CAR(temp);
			}
			else
			    ring_buffer = Nil;
			if (ring_buffer) {
			    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp = aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    temp = 
					    copy_text_string(managed_number_or_value);
				else
				    temp = managed_number_or_value;
			    }
			    else
				temp = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L));
			}
			else
			    temp = FIX((SI_Long)0L);
		    }
		    else
			temp = FIX((SI_Long)0L);
		    value = normalize_to_gensym_float(temp);
		    temp = exceptional_float_flavor_qm(value);
		    if (EQ(temp,Qpositive_infinity))
			current_value = float_constant_1;
		    else if (EQ(temp,Qnegative_infinity))
			current_value = float_constant_2;
		    else if (EQ(temp,Qnan))
			current_value = float_constant_3;
		    else {
			arg = DOUBLE_FLOAT_TO_DOUBLE(value);
			arg_1 = 1.7976931348623158E+304;
			if (arg >= arg_1 &&  
				!inline_nanp_for_comparison(arg) &&  
				!inline_nanp_for_comparison(arg_1))
			    current_value = float_constant_1;
			else {
			    arg = DOUBLE_FLOAT_TO_DOUBLE(value);
			    arg_1 = -1.7976931348623158E+304;
			    if (arg <= arg_1 &&  
				    !inline_nanp_for_comparison(arg) &&  
				    !inline_nanp_for_comparison(arg_1))
				current_value = float_constant_2;
			    else
				current_value = value;
			}
		    }
		    gensymed_symbol = IFIX(gensymed_symbol_3);
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
		    if (EQ(temp,Qconstant))
			gensymed_symbol_1 = (SI_Long)0L;
		    else if (EQ(temp,Qcascaded))
			gensymed_symbol_1 = 
				IFIX(ISVREF(ISVREF(gensymed_symbol_2,
				(SI_Long)5L),(SI_Long)6L));
		    else if (EQ(temp,Qvariable)) {
			cascaded_ring_buffer_qm = 
				get_cascaded_ring_buffer_for_history(1,
				gensymed_symbol_2);
			gensymed_symbol_1 = cascaded_ring_buffer_qm ? 
				IFIX(ISVREF(cascaded_ring_buffer_qm,
				(SI_Long)6L)) : (SI_Long)0L;
		    }
		    else
			gensymed_symbol_1 = (SI_Long)0L;
		    position_in_history = gensymed_symbol - gensymed_symbol_1;
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
		    if (EQ(temp,Qconstant))
			history_start = error((SI_Long)1L,
				"indexed access not supported");
		    else if (EQ(temp,Qcascaded)) {
			temp = ISVREF(ISVREF(gensymed_symbol_2,
				(SI_Long)5L),(SI_Long)4L);
			ring_buffer = CAR(temp);
			history_start = ring_buffer ? ISVREF(ring_buffer,
				(SI_Long)2L) : FIX((SI_Long)0L);
		    }
		    else if (EQ(temp,Qvariable)) {
			cascaded_ring_buffer_qm = 
				get_cascaded_ring_buffer_for_history(1,
				gensymed_symbol_2);
			if (cascaded_ring_buffer_qm) {
			    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
			    ring_buffer = CAR(temp);
			}
			else
			    ring_buffer = Nil;
			history_start = ring_buffer ? ISVREF(ring_buffer,
				(SI_Long)2L) : FIX((SI_Long)0L);
		    }
		    else
			history_start = FIX((SI_Long)0L);
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
		    if (EQ(temp,Qconstant))
			history_end = error((SI_Long)1L,
				"indexed access not supported");
		    else if (EQ(temp,Qcascaded)) {
			temp = ISVREF(ISVREF(gensymed_symbol_2,
				(SI_Long)5L),(SI_Long)4L);
			ring_buffer = CAR(temp);
			history_end = ring_buffer ? ISVREF(ring_buffer,
				(SI_Long)1L) : FIX((SI_Long)0L);
		    }
		    else if (EQ(temp,Qvariable)) {
			cascaded_ring_buffer_qm = 
				get_cascaded_ring_buffer_for_history(1,
				gensymed_symbol_2);
			if (cascaded_ring_buffer_qm) {
			    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
			    ring_buffer = CAR(temp);
			}
			else
			    ring_buffer = Nil;
			history_end = ring_buffer ? ISVREF(ring_buffer,
				(SI_Long)1L) : FIX((SI_Long)0L);
		    }
		    else
			history_end = FIX((SI_Long)0L);
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
		    if (EQ(temp,Qconstant))
			history_size = FIX((SI_Long)1L);
		    else if (EQ(temp,Qcascaded)) {
			temp = ISVREF(ISVREF(gensymed_symbol_2,
				(SI_Long)5L),(SI_Long)4L);
			ring_buffer_qm = CAR(temp);
			history_size = ring_buffer_qm ? 
				ISVREF(ring_buffer_qm,(SI_Long)4L) : 
				FIX((SI_Long)0L);
		    }
		    else if (EQ(temp,Qvariable)) {
			cascaded_ring_buffer_qm = 
				get_cascaded_ring_buffer_for_history(1,
				gensymed_symbol_2);
			if (cascaded_ring_buffer_qm) {
			    cascaded_ring_buffer_qm = 
				    get_cascaded_ring_buffer_for_history(1,
				    gensymed_symbol_2);
			    if (cascaded_ring_buffer_qm) {
				temp = ISVREF(cascaded_ring_buffer_qm,
					(SI_Long)4L);
				ring_buffer_qm = CAR(temp);
			    }
			    else
				ring_buffer_qm = Nil;
			}
			else
			    ring_buffer_qm = Nil;
			history_size = ring_buffer_qm ? 
				ISVREF(ring_buffer_qm,(SI_Long)4L) : 
				FIX((SI_Long)0L);
		    }
		    else
			history_size = FIX((SI_Long)0L);
		    index_1 = NUM_LE(history_start,history_end) ? 
			    FIX(position_in_history + IFIX(history_start)) 
			    : 
			    chestnut_modf_function(FIX(position_in_history 
			    - IFIX(FIXNUM_MINUS(history_size,
			    history_start))),history_size);
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
		    if (EQ(temp,Qconstant))
			temp = ISVREF(gensymed_symbol_2,(SI_Long)5L);
		    else if (EQ(temp,Qcascaded)) {
			temp = ISVREF(ISVREF(gensymed_symbol_2,
				(SI_Long)5L),(SI_Long)4L);
			ring_buffer = CAR(temp);
			if (ring_buffer) {
			    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp = aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    temp = 
					    copy_text_string(managed_number_or_value);
				else
				    temp = managed_number_or_value;
			    }
			    else
				temp = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L));
			}
			else
			    temp = FIX((SI_Long)0L);
		    }
		    else if (EQ(temp,Qvariable)) {
			cascaded_ring_buffer_qm = 
				get_cascaded_ring_buffer_for_history(1,
				gensymed_symbol_2);
			if (cascaded_ring_buffer_qm) {
			    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
			    ring_buffer = CAR(temp);
			}
			else
			    ring_buffer = Nil;
			if (ring_buffer) {
			    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp = aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    temp = 
					    copy_text_string(managed_number_or_value);
				else
				    temp = managed_number_or_value;
			    }
			    else
				temp = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L));
			}
			else
			    temp = FIX((SI_Long)0L);
		    }
		    else
			temp = FIX((SI_Long)0L);
		    value = normalize_to_gensym_float(temp);
		    temp = exceptional_float_flavor_qm(value);
		    if (EQ(temp,Qpositive_infinity))
			new_value = float_constant_1;
		    else if (EQ(temp,Qnegative_infinity))
			new_value = float_constant_2;
		    else if (EQ(temp,Qnan))
			new_value = float_constant_3;
		    else {
			arg = DOUBLE_FLOAT_TO_DOUBLE(value);
			arg_1 = 1.7976931348623158E+304;
			if (arg >= arg_1 &&  
				!inline_nanp_for_comparison(arg) &&  
				!inline_nanp_for_comparison(arg_1))
			    new_value = float_constant_1;
			else {
			    arg = DOUBLE_FLOAT_TO_DOUBLE(value);
			    arg_1 = -1.7976931348623158E+304;
			    if (arg <= arg_1 &&  
				    !inline_nanp_for_comparison(arg) &&  
				    !inline_nanp_for_comparison(arg_1))
				new_value = float_constant_2;
			    else
				new_value = value;
			}
		    }
		    if (EQ(polarity,Qminimum)) {
			arg = DOUBLE_FLOAT_TO_DOUBLE(new_value);
			arg_1 = DOUBLE_FLOAT_TO_DOUBLE(current_value);
			if (arg < arg_1 &&  
				!inline_nanp_for_comparison(arg) &&  
				!inline_nanp_for_comparison(arg_1))
			    extreme_value_index = gensymed_symbol_3;
		    }
		    else if (EQ(polarity,Qmaximum)) {
			arg = DOUBLE_FLOAT_TO_DOUBLE(new_value);
			arg_1 = DOUBLE_FLOAT_TO_DOUBLE(current_value);
			if (arg > arg_1 &&  
				!inline_nanp_for_comparison(arg) &&  
				!inline_nanp_for_comparison(arg_1))
			    extreme_value_index = gensymed_symbol_3;
		    }
		}
		else
		    extreme_value_index = gensymed_symbol_3;
	    }
	    update_whole_interval_extremum_cache(extremum_cache,
		    FIX(absolute_start),FIX(absolute_end),extreme_value_index);
	    return VALUES_1(extreme_value_index);
	}
	gensymed_symbol_2 = history;
	gensymed_symbol_3 = compute_extremum_for_zone(history,
		extremum_cache,polarity,FIX(zone_start),zone_end);
	if (extreme_value_index) {
	    gensymed_symbol = IFIX(extreme_value_index);
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		gensymed_symbol_1 = (SI_Long)0L;
	    else if (EQ(temp,Qcascaded))
		gensymed_symbol_1 = IFIX(ISVREF(ISVREF(gensymed_symbol_2,
			(SI_Long)5L),(SI_Long)6L));
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol_2);
		gensymed_symbol_1 = cascaded_ring_buffer_qm ? 
			IFIX(ISVREF(cascaded_ring_buffer_qm,(SI_Long)6L)) :
			 (SI_Long)0L;
	    }
	    else
		gensymed_symbol_1 = (SI_Long)0L;
	    position_in_history = gensymed_symbol - gensymed_symbol_1;
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_start = error((SI_Long)1L,
			"indexed access not supported");
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol_2,(SI_Long)5L),
			(SI_Long)4L);
		ring_buffer = CAR(temp);
		history_start = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)2L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol_2);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		history_start = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)2L) : FIX((SI_Long)0L);
	    }
	    else
		history_start = FIX((SI_Long)0L);
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_end = error((SI_Long)1L,
			"indexed access not supported");
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol_2,(SI_Long)5L),
			(SI_Long)4L);
		ring_buffer = CAR(temp);
		history_end = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)1L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol_2);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		history_end = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)1L) : FIX((SI_Long)0L);
	    }
	    else
		history_end = FIX((SI_Long)0L);
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_size = FIX((SI_Long)1L);
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol_2,(SI_Long)5L),
			(SI_Long)4L);
		ring_buffer_qm = CAR(temp);
		history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,
			(SI_Long)4L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol_2);
		if (cascaded_ring_buffer_qm) {
		    cascaded_ring_buffer_qm = 
			    get_cascaded_ring_buffer_for_history(1,
			    gensymed_symbol_2);
		    if (cascaded_ring_buffer_qm) {
			temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
			ring_buffer_qm = CAR(temp);
		    }
		    else
			ring_buffer_qm = Nil;
		}
		else
		    ring_buffer_qm = Nil;
		history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,
			(SI_Long)4L) : FIX((SI_Long)0L);
	    }
	    else
		history_size = FIX((SI_Long)0L);
	    index_1 = NUM_LE(history_start,history_end) ? 
		    FIX(position_in_history + IFIX(history_start)) : 
		    chestnut_modf_function(FIX(position_in_history - 
		    IFIX(FIXNUM_MINUS(history_size,history_start))),
		    history_size);
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		temp = ISVREF(gensymed_symbol_2,(SI_Long)5L);
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol_2,(SI_Long)5L),
			(SI_Long)4L);
		ring_buffer = CAR(temp);
		if (ring_buffer) {
		    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
		    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			managed_number_or_value = 
				FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(vector_1,(IFIX(index_1) >>  
				-  - (SI_Long)10L) + (SI_Long)2L),
				IFIX(index_1) & (SI_Long)1023L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp = copy_text_string(managed_number_or_value);
			else
			    temp = managed_number_or_value;
		    }
		    else
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(index_1) >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L));
		}
		else
		    temp = FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol_2);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		if (ring_buffer) {
		    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
		    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			managed_number_or_value = 
				FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(vector_1,(IFIX(index_1) >>  
				-  - (SI_Long)10L) + (SI_Long)2L),
				IFIX(index_1) & (SI_Long)1023L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp = copy_text_string(managed_number_or_value);
			else
			    temp = managed_number_or_value;
		    }
		    else
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(index_1) >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L));
		}
		else
		    temp = FIX((SI_Long)0L);
	    }
	    else
		temp = FIX((SI_Long)0L);
	    value = normalize_to_gensym_float(temp);
	    temp = exceptional_float_flavor_qm(value);
	    if (EQ(temp,Qpositive_infinity))
		current_value = float_constant_1;
	    else if (EQ(temp,Qnegative_infinity))
		current_value = float_constant_2;
	    else if (EQ(temp,Qnan))
		current_value = float_constant_3;
	    else {
		arg = DOUBLE_FLOAT_TO_DOUBLE(value);
		arg_1 = 1.7976931348623158E+304;
		if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    current_value = float_constant_1;
		else {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(value);
		    arg_1 = -1.7976931348623158E+304;
		    if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1))
			current_value = float_constant_2;
		    else
			current_value = value;
		}
	    }
	    gensymed_symbol = IFIX(gensymed_symbol_3);
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		gensymed_symbol_1 = (SI_Long)0L;
	    else if (EQ(temp,Qcascaded))
		gensymed_symbol_1 = IFIX(ISVREF(ISVREF(gensymed_symbol_2,
			(SI_Long)5L),(SI_Long)6L));
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol_2);
		gensymed_symbol_1 = cascaded_ring_buffer_qm ? 
			IFIX(ISVREF(cascaded_ring_buffer_qm,(SI_Long)6L)) :
			 (SI_Long)0L;
	    }
	    else
		gensymed_symbol_1 = (SI_Long)0L;
	    position_in_history = gensymed_symbol - gensymed_symbol_1;
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_start = error((SI_Long)1L,
			"indexed access not supported");
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol_2,(SI_Long)5L),
			(SI_Long)4L);
		ring_buffer = CAR(temp);
		history_start = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)2L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol_2);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		history_start = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)2L) : FIX((SI_Long)0L);
	    }
	    else
		history_start = FIX((SI_Long)0L);
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_end = error((SI_Long)1L,
			"indexed access not supported");
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol_2,(SI_Long)5L),
			(SI_Long)4L);
		ring_buffer = CAR(temp);
		history_end = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)1L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol_2);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		history_end = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)1L) : FIX((SI_Long)0L);
	    }
	    else
		history_end = FIX((SI_Long)0L);
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_size = FIX((SI_Long)1L);
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol_2,(SI_Long)5L),
			(SI_Long)4L);
		ring_buffer_qm = CAR(temp);
		history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,
			(SI_Long)4L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol_2);
		if (cascaded_ring_buffer_qm) {
		    cascaded_ring_buffer_qm = 
			    get_cascaded_ring_buffer_for_history(1,
			    gensymed_symbol_2);
		    if (cascaded_ring_buffer_qm) {
			temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
			ring_buffer_qm = CAR(temp);
		    }
		    else
			ring_buffer_qm = Nil;
		}
		else
		    ring_buffer_qm = Nil;
		history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,
			(SI_Long)4L) : FIX((SI_Long)0L);
	    }
	    else
		history_size = FIX((SI_Long)0L);
	    index_1 = NUM_LE(history_start,history_end) ? 
		    FIX(position_in_history + IFIX(history_start)) : 
		    chestnut_modf_function(FIX(position_in_history - 
		    IFIX(FIXNUM_MINUS(history_size,history_start))),
		    history_size);
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		temp = ISVREF(gensymed_symbol_2,(SI_Long)5L);
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol_2,(SI_Long)5L),
			(SI_Long)4L);
		ring_buffer = CAR(temp);
		if (ring_buffer) {
		    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
		    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			managed_number_or_value = 
				FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(vector_1,(IFIX(index_1) >>  
				-  - (SI_Long)10L) + (SI_Long)2L),
				IFIX(index_1) & (SI_Long)1023L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp = copy_text_string(managed_number_or_value);
			else
			    temp = managed_number_or_value;
		    }
		    else
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(index_1) >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L));
		}
		else
		    temp = FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol_2);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		if (ring_buffer) {
		    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
		    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			managed_number_or_value = 
				FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(vector_1,(IFIX(index_1) >>  
				-  - (SI_Long)10L) + (SI_Long)2L),
				IFIX(index_1) & (SI_Long)1023L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp = copy_text_string(managed_number_or_value);
			else
			    temp = managed_number_or_value;
		    }
		    else
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(index_1) >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L));
		}
		else
		    temp = FIX((SI_Long)0L);
	    }
	    else
		temp = FIX((SI_Long)0L);
	    value = normalize_to_gensym_float(temp);
	    temp = exceptional_float_flavor_qm(value);
	    if (EQ(temp,Qpositive_infinity))
		new_value = float_constant_1;
	    else if (EQ(temp,Qnegative_infinity))
		new_value = float_constant_2;
	    else if (EQ(temp,Qnan))
		new_value = float_constant_3;
	    else {
		arg = DOUBLE_FLOAT_TO_DOUBLE(value);
		arg_1 = 1.7976931348623158E+304;
		if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    new_value = float_constant_1;
		else {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(value);
		    arg_1 = -1.7976931348623158E+304;
		    if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1))
			new_value = float_constant_2;
		    else
			new_value = value;
		}
	    }
	    if (EQ(polarity,Qminimum)) {
		arg = DOUBLE_FLOAT_TO_DOUBLE(new_value);
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(current_value);
		if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    extreme_value_index = gensymed_symbol_3;
	    }
	    else if (EQ(polarity,Qmaximum)) {
		arg = DOUBLE_FLOAT_TO_DOUBLE(new_value);
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(current_value);
		if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    extreme_value_index = gensymed_symbol_3;
	    }
	}
	else
	    extreme_value_index = gensymed_symbol_3;
	zone_start = zone_start + ab_loop_step_by_;
	first_time_p = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* COMPUTE-EXTREMUM-FOR-ZONE */
Object compute_extremum_for_zone(history,extremum_cache,polarity,
	    zone_start,zone_end)
    Object history, extremum_cache, polarity, zone_start, zone_end;
{
    Object zone_width, cached_value_index, extremum, gensymed_symbol, temp;
    Object cascaded_ring_buffer_qm, history_start, ring_buffer, history_end;
    Object history_size, ring_buffer_qm, index_1, vector_1;
    Object managed_number_or_value, value, current_value, new_value;
    SI_Long i, ab_loop_bind_, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, position_in_history;
    char cacheable_p;
    double arg, arg_1;

    x_note_fn_call(174,64);
    zone_width = ISVREF(extremum_cache,(SI_Long)9L);
    cacheable_p = FIXNUM_EQ(FIXNUM_MINUS(zone_end,zone_start),zone_width);
    cached_value_index = cacheable_p ? 
	    lookup_zone_cache_element(extremum_cache,zone_start) : Qnil;
    if (cached_value_index)
	return VALUES_1(cached_value_index);
    else if (FIXNUM_GE(zone_end,zone_start)) {
	extremum = zone_start;
	i = IFIX(FIXNUM_ADD1(zone_start));
	ab_loop_bind_ = IFIX(zone_end);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	gensymed_symbol = history;
	gensymed_symbol_1 = i;
	if (extremum) {
	    gensymed_symbol_2 = IFIX(extremum);
	    temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		gensymed_symbol_3 = (SI_Long)0L;
	    else if (EQ(temp,Qcascaded))
		gensymed_symbol_3 = IFIX(ISVREF(ISVREF(gensymed_symbol,
			(SI_Long)5L),(SI_Long)6L));
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol);
		gensymed_symbol_3 = cascaded_ring_buffer_qm ? 
			IFIX(ISVREF(cascaded_ring_buffer_qm,(SI_Long)6L)) :
			 (SI_Long)0L;
	    }
	    else
		gensymed_symbol_3 = (SI_Long)0L;
	    position_in_history = gensymed_symbol_2 - gensymed_symbol_3;
	    temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_start = error((SI_Long)1L,
			"indexed access not supported");
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol,(SI_Long)5L),(SI_Long)4L);
		ring_buffer = CAR(temp);
		history_start = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)2L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		history_start = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)2L) : FIX((SI_Long)0L);
	    }
	    else
		history_start = FIX((SI_Long)0L);
	    temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_end = error((SI_Long)1L,
			"indexed access not supported");
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol,(SI_Long)5L),(SI_Long)4L);
		ring_buffer = CAR(temp);
		history_end = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)1L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		history_end = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)1L) : FIX((SI_Long)0L);
	    }
	    else
		history_end = FIX((SI_Long)0L);
	    temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_size = FIX((SI_Long)1L);
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol,(SI_Long)5L),(SI_Long)4L);
		ring_buffer_qm = CAR(temp);
		history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,
			(SI_Long)4L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol);
		if (cascaded_ring_buffer_qm) {
		    cascaded_ring_buffer_qm = 
			    get_cascaded_ring_buffer_for_history(1,
			    gensymed_symbol);
		    if (cascaded_ring_buffer_qm) {
			temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
			ring_buffer_qm = CAR(temp);
		    }
		    else
			ring_buffer_qm = Nil;
		}
		else
		    ring_buffer_qm = Nil;
		history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,
			(SI_Long)4L) : FIX((SI_Long)0L);
	    }
	    else
		history_size = FIX((SI_Long)0L);
	    index_1 = NUM_LE(history_start,history_end) ? 
		    FIX(position_in_history + IFIX(history_start)) : 
		    chestnut_modf_function(FIX(position_in_history - 
		    IFIX(FIXNUM_MINUS(history_size,history_start))),
		    history_size);
	    temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		temp = ISVREF(gensymed_symbol,(SI_Long)5L);
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol,(SI_Long)5L),(SI_Long)4L);
		ring_buffer = CAR(temp);
		if (ring_buffer) {
		    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
		    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			managed_number_or_value = 
				FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(vector_1,(IFIX(index_1) >>  
				-  - (SI_Long)10L) + (SI_Long)2L),
				IFIX(index_1) & (SI_Long)1023L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp = copy_text_string(managed_number_or_value);
			else
			    temp = managed_number_or_value;
		    }
		    else
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(index_1) >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L));
		}
		else
		    temp = FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		if (ring_buffer) {
		    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
		    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			managed_number_or_value = 
				FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(vector_1,(IFIX(index_1) >>  
				-  - (SI_Long)10L) + (SI_Long)2L),
				IFIX(index_1) & (SI_Long)1023L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp = copy_text_string(managed_number_or_value);
			else
			    temp = managed_number_or_value;
		    }
		    else
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(index_1) >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L));
		}
		else
		    temp = FIX((SI_Long)0L);
	    }
	    else
		temp = FIX((SI_Long)0L);
	    value = normalize_to_gensym_float(temp);
	    temp = exceptional_float_flavor_qm(value);
	    if (EQ(temp,Qpositive_infinity))
		current_value = float_constant_1;
	    else if (EQ(temp,Qnegative_infinity))
		current_value = float_constant_2;
	    else if (EQ(temp,Qnan))
		current_value = float_constant_3;
	    else {
		arg = DOUBLE_FLOAT_TO_DOUBLE(value);
		arg_1 = 1.7976931348623158E+304;
		if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    current_value = float_constant_1;
		else {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(value);
		    arg_1 = -1.7976931348623158E+304;
		    if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1))
			current_value = float_constant_2;
		    else
			current_value = value;
		}
	    }
	    temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		gensymed_symbol_2 = (SI_Long)0L;
	    else if (EQ(temp,Qcascaded))
		gensymed_symbol_2 = IFIX(ISVREF(ISVREF(gensymed_symbol,
			(SI_Long)5L),(SI_Long)6L));
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol);
		gensymed_symbol_2 = cascaded_ring_buffer_qm ? 
			IFIX(ISVREF(cascaded_ring_buffer_qm,(SI_Long)6L)) :
			 (SI_Long)0L;
	    }
	    else
		gensymed_symbol_2 = (SI_Long)0L;
	    position_in_history = gensymed_symbol_1 - gensymed_symbol_2;
	    temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_start = error((SI_Long)1L,
			"indexed access not supported");
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol,(SI_Long)5L),(SI_Long)4L);
		ring_buffer = CAR(temp);
		history_start = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)2L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		history_start = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)2L) : FIX((SI_Long)0L);
	    }
	    else
		history_start = FIX((SI_Long)0L);
	    temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_end = error((SI_Long)1L,
			"indexed access not supported");
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol,(SI_Long)5L),(SI_Long)4L);
		ring_buffer = CAR(temp);
		history_end = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)1L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		history_end = ring_buffer ? ISVREF(ring_buffer,
			(SI_Long)1L) : FIX((SI_Long)0L);
	    }
	    else
		history_end = FIX((SI_Long)0L);
	    temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		history_size = FIX((SI_Long)1L);
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol,(SI_Long)5L),(SI_Long)4L);
		ring_buffer_qm = CAR(temp);
		history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,
			(SI_Long)4L) : FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol);
		if (cascaded_ring_buffer_qm) {
		    cascaded_ring_buffer_qm = 
			    get_cascaded_ring_buffer_for_history(1,
			    gensymed_symbol);
		    if (cascaded_ring_buffer_qm) {
			temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
			ring_buffer_qm = CAR(temp);
		    }
		    else
			ring_buffer_qm = Nil;
		}
		else
		    ring_buffer_qm = Nil;
		history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,
			(SI_Long)4L) : FIX((SI_Long)0L);
	    }
	    else
		history_size = FIX((SI_Long)0L);
	    index_1 = NUM_LE(history_start,history_end) ? 
		    FIX(position_in_history + IFIX(history_start)) : 
		    chestnut_modf_function(FIX(position_in_history - 
		    IFIX(FIXNUM_MINUS(history_size,history_start))),
		    history_size);
	    temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	    if (EQ(temp,Qconstant))
		temp = ISVREF(gensymed_symbol,(SI_Long)5L);
	    else if (EQ(temp,Qcascaded)) {
		temp = ISVREF(ISVREF(gensymed_symbol,(SI_Long)5L),(SI_Long)4L);
		ring_buffer = CAR(temp);
		if (ring_buffer) {
		    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
		    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			managed_number_or_value = 
				FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(vector_1,(IFIX(index_1) >>  
				-  - (SI_Long)10L) + (SI_Long)2L),
				IFIX(index_1) & (SI_Long)1023L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp = copy_text_string(managed_number_or_value);
			else
			    temp = managed_number_or_value;
		    }
		    else
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(index_1) >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L));
		}
		else
		    temp = FIX((SI_Long)0L);
	    }
	    else if (EQ(temp,Qvariable)) {
		cascaded_ring_buffer_qm = 
			get_cascaded_ring_buffer_for_history(1,
			gensymed_symbol);
		if (cascaded_ring_buffer_qm) {
		    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		    ring_buffer = CAR(temp);
		}
		else
		    ring_buffer = Nil;
		if (ring_buffer) {
		    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
		    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			managed_number_or_value = 
				FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				Maximum_in_place_array_size) ? 
				ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(vector_1,(IFIX(index_1) >>  
				-  - (SI_Long)10L) + (SI_Long)2L),
				IFIX(index_1) & (SI_Long)1023L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp = copy_text_string(managed_number_or_value);
			else
			    temp = managed_number_or_value;
		    }
		    else
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(index_1) >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L));
		}
		else
		    temp = FIX((SI_Long)0L);
	    }
	    else
		temp = FIX((SI_Long)0L);
	    value = normalize_to_gensym_float(temp);
	    temp = exceptional_float_flavor_qm(value);
	    if (EQ(temp,Qpositive_infinity))
		new_value = float_constant_1;
	    else if (EQ(temp,Qnegative_infinity))
		new_value = float_constant_2;
	    else if (EQ(temp,Qnan))
		new_value = float_constant_3;
	    else {
		arg = DOUBLE_FLOAT_TO_DOUBLE(value);
		arg_1 = 1.7976931348623158E+304;
		if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    new_value = float_constant_1;
		else {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(value);
		    arg_1 = -1.7976931348623158E+304;
		    if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1))
			new_value = float_constant_2;
		    else
			new_value = value;
		}
	    }
	    if (EQ(polarity,Qminimum)) {
		arg = DOUBLE_FLOAT_TO_DOUBLE(new_value);
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(current_value);
		if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    extremum = FIX(gensymed_symbol_1);
	    }
	    else if (EQ(polarity,Qmaximum)) {
		arg = DOUBLE_FLOAT_TO_DOUBLE(new_value);
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(current_value);
		if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    extremum = FIX(gensymed_symbol_1);
	    }
	}
	else
	    extremum = FIX(gensymed_symbol_1);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	if (cacheable_p)
	    add_zone_cache_element(extremum_cache,zone_start,extremum);
	return VALUES_1(extremum);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* INVALIDATE-EXTREMA-CACHES */
Object invalidate_extrema_caches(history)
    Object history;
{
    Object svref_arg_1;

    x_note_fn_call(174,65);
    svref_arg_1 = ISVREF(history,(SI_Long)3L);
    SVREF(svref_arg_1,FIX((SI_Long)13L)) = Nil;
    svref_arg_1 = ISVREF(history,(SI_Long)2L);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)13L)) = Nil);
}

/* INVALIDATE-HISTORY-INDICES */
Object invalidate_history_indices(history)
    Object history;
{
    x_note_fn_call(174,66);
    return invalidate_extrema_caches(history);
}

/* GENERIC-HISTORY-MAXIMUM-VALUE-INDEX */
Object generic_history_maximum_value_index(history,start,end_1)
    Object history, start, end_1;
{
    Object index_1, temp, cascaded_ring_buffer_qm, history_start, ring_buffer;
    Object history_end, history_size, ring_buffer_qm;
    SI_Long gensymed_symbol, gensymed_symbol_1, position_in_history;

    x_note_fn_call(174,67);
    index_1 = compute_extremum_for_interval(history,start,end_1,Qmaximum);
    gensymed_symbol = IFIX(index_1);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	gensymed_symbol_1 = (SI_Long)0L;
    else if (EQ(temp,Qcascaded))
	gensymed_symbol_1 = IFIX(ISVREF(ISVREF(history,(SI_Long)5L),
		(SI_Long)6L));
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	gensymed_symbol_1 = cascaded_ring_buffer_qm ? 
		IFIX(ISVREF(cascaded_ring_buffer_qm,(SI_Long)6L)) : 
		(SI_Long)0L;
    }
    else
	gensymed_symbol_1 = (SI_Long)0L;
    position_in_history = gensymed_symbol - gensymed_symbol_1;
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	history_start = error((SI_Long)1L,"indexed access not supported");
    else if (EQ(temp,Qcascaded)) {
	temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	ring_buffer = CAR(temp);
	history_start = ring_buffer ? ISVREF(ring_buffer,(SI_Long)2L) : 
		FIX((SI_Long)0L);
    }
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	if (cascaded_ring_buffer_qm) {
	    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
	    ring_buffer = CAR(temp);
	}
	else
	    ring_buffer = Nil;
	history_start = ring_buffer ? ISVREF(ring_buffer,(SI_Long)2L) : 
		FIX((SI_Long)0L);
    }
    else
	history_start = FIX((SI_Long)0L);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	history_end = error((SI_Long)1L,"indexed access not supported");
    else if (EQ(temp,Qcascaded)) {
	temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	ring_buffer = CAR(temp);
	history_end = ring_buffer ? ISVREF(ring_buffer,(SI_Long)1L) : 
		FIX((SI_Long)0L);
    }
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	if (cascaded_ring_buffer_qm) {
	    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
	    ring_buffer = CAR(temp);
	}
	else
	    ring_buffer = Nil;
	history_end = ring_buffer ? ISVREF(ring_buffer,(SI_Long)1L) : 
		FIX((SI_Long)0L);
    }
    else
	history_end = FIX((SI_Long)0L);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	history_size = FIX((SI_Long)1L);
    else if (EQ(temp,Qcascaded)) {
	temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	ring_buffer_qm = CAR(temp);
	history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,(SI_Long)4L) 
		: FIX((SI_Long)0L);
    }
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	if (cascaded_ring_buffer_qm) {
	    cascaded_ring_buffer_qm = 
		    get_cascaded_ring_buffer_for_history(1,history);
	    if (cascaded_ring_buffer_qm) {
		temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		ring_buffer_qm = CAR(temp);
	    }
	    else
		ring_buffer_qm = Nil;
	}
	else
	    ring_buffer_qm = Nil;
	history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,(SI_Long)4L) 
		: FIX((SI_Long)0L);
    }
    else
	history_size = FIX((SI_Long)0L);
    if (NUM_LE(history_start,history_end))
	return VALUES_1(FIX(position_in_history + IFIX(history_start)));
    else
	return chestnut_modf_function(FIX(position_in_history - 
		IFIX(FIXNUM_MINUS(history_size,history_start))),history_size);
}

/* GENERIC-HISTORY-MINIMUM-VALUE-INDEX */
Object generic_history_minimum_value_index(history,start,end_1)
    Object history, start, end_1;
{
    Object index_1, temp, cascaded_ring_buffer_qm, history_start, ring_buffer;
    Object history_end, history_size, ring_buffer_qm;
    SI_Long gensymed_symbol, gensymed_symbol_1, position_in_history;

    x_note_fn_call(174,68);
    index_1 = compute_extremum_for_interval(history,start,end_1,Qminimum);
    gensymed_symbol = IFIX(index_1);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	gensymed_symbol_1 = (SI_Long)0L;
    else if (EQ(temp,Qcascaded))
	gensymed_symbol_1 = IFIX(ISVREF(ISVREF(history,(SI_Long)5L),
		(SI_Long)6L));
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	gensymed_symbol_1 = cascaded_ring_buffer_qm ? 
		IFIX(ISVREF(cascaded_ring_buffer_qm,(SI_Long)6L)) : 
		(SI_Long)0L;
    }
    else
	gensymed_symbol_1 = (SI_Long)0L;
    position_in_history = gensymed_symbol - gensymed_symbol_1;
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	history_start = error((SI_Long)1L,"indexed access not supported");
    else if (EQ(temp,Qcascaded)) {
	temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	ring_buffer = CAR(temp);
	history_start = ring_buffer ? ISVREF(ring_buffer,(SI_Long)2L) : 
		FIX((SI_Long)0L);
    }
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	if (cascaded_ring_buffer_qm) {
	    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
	    ring_buffer = CAR(temp);
	}
	else
	    ring_buffer = Nil;
	history_start = ring_buffer ? ISVREF(ring_buffer,(SI_Long)2L) : 
		FIX((SI_Long)0L);
    }
    else
	history_start = FIX((SI_Long)0L);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	history_end = error((SI_Long)1L,"indexed access not supported");
    else if (EQ(temp,Qcascaded)) {
	temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	ring_buffer = CAR(temp);
	history_end = ring_buffer ? ISVREF(ring_buffer,(SI_Long)1L) : 
		FIX((SI_Long)0L);
    }
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	if (cascaded_ring_buffer_qm) {
	    temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
	    ring_buffer = CAR(temp);
	}
	else
	    ring_buffer = Nil;
	history_end = ring_buffer ? ISVREF(ring_buffer,(SI_Long)1L) : 
		FIX((SI_Long)0L);
    }
    else
	history_end = FIX((SI_Long)0L);
    temp = ISVREF(history,(SI_Long)4L);
    if (EQ(temp,Qconstant))
	history_size = FIX((SI_Long)1L);
    else if (EQ(temp,Qcascaded)) {
	temp = ISVREF(ISVREF(history,(SI_Long)5L),(SI_Long)4L);
	ring_buffer_qm = CAR(temp);
	history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,(SI_Long)4L) 
		: FIX((SI_Long)0L);
    }
    else if (EQ(temp,Qvariable)) {
	cascaded_ring_buffer_qm = get_cascaded_ring_buffer_for_history(1,
		history);
	if (cascaded_ring_buffer_qm) {
	    cascaded_ring_buffer_qm = 
		    get_cascaded_ring_buffer_for_history(1,history);
	    if (cascaded_ring_buffer_qm) {
		temp = ISVREF(cascaded_ring_buffer_qm,(SI_Long)4L);
		ring_buffer_qm = CAR(temp);
	    }
	    else
		ring_buffer_qm = Nil;
	}
	else
	    ring_buffer_qm = Nil;
	history_size = ring_buffer_qm ? ISVREF(ring_buffer_qm,(SI_Long)4L) 
		: FIX((SI_Long)0L);
    }
    else
	history_size = FIX((SI_Long)0L);
    if (NUM_LE(history_start,history_end))
	return VALUES_1(FIX(position_in_history + IFIX(history_start)));
    else
	return chestnut_modf_function(FIX(position_in_history - 
		IFIX(FIXNUM_MINUS(history_size,history_start))),history_size);
}

void graph_util_INIT()
{
    Object temp, reclaim_structure_for_extremum_cache_1, temp_1, temp_2;
    Object AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qclasses_which_define, Qcleanup, Qcleanup_for_generic_history;
    Object Qcopy_frame, Qcopy_frame_for_generic_history, Qslot_value_reclaimer;
    Object Qreclaim_generic_history_data_serial_number_value;
    Object Qgeneric_history_data_serial_number, string_constant_10;
    Object list_constant_1, string_constant_9, string_constant_8;
    Object string_constant_7, string_constant_6, Qdependent_frame;
    Object Qextremum_cache, Qreclaim_structure;
    Object Qoutstanding_extremum_cache_count;
    Object Qextremum_cache_structure_memory_usage, Qutilities2;
    Object string_constant_5, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_4, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, list_constant, Qgraph_util;
    Object Qenumeration_grammar_category_members;

    x_note_fn_call(174,69);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qenumeration_grammar_category_members = 
	    STATIC_SYMBOL("ENUMERATION-GRAMMAR-CATEGORY-MEMBERS",AB_package);
    Enumeration_grammar_category_members_prop = 
	    Qenumeration_grammar_category_members;
    Qframe_like_category_cases = STATIC_SYMBOL("FRAME-LIKE-CATEGORY-CASES",
	    AB_package);
    Frame_like_category_cases_prop = Qframe_like_category_cases;
    Recent_defaults_made = Qnil;
    Qphrase = STATIC_SYMBOL("PHRASE",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qcalling_float_function_cleverly_p = 
	    STATIC_SYMBOL("CALLING-FLOAT-FUNCTION-CLEVERLY-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcalling_float_function_cleverly_p,
	    Calling_float_function_cleverly_p);
    Qgraph_util = STATIC_SYMBOL("GRAPH-UTIL",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qquote,Qnil);
    record_system_variable(Qcalling_float_function_cleverly_p,Qgraph_util,
	    list_constant,Qnil,Qnil,Qnil,Qnil);
    Qoutstanding_float_function_floats = 
	    STATIC_SYMBOL("OUTSTANDING-FLOAT-FUNCTION-FLOATS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoutstanding_float_function_floats,
	    Outstanding_float_function_floats);
    record_system_variable(Qoutstanding_float_function_floats,Qgraph_util,
	    list_constant,Qnil,Qnil,Qnil,Qnil);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Max_timespan = fixnum_to_time_function(FIXNUM_SUB1(Most_positive_fixnum));
    Qvms = STATIC_SYMBOL("VMS",AB_package);
    Qpositive_infinity = STATIC_SYMBOL("POSITIVE-INFINITY",AB_package);
    Qnegative_infinity = STATIC_SYMBOL("NEGATIVE-INFINITY",AB_package);
    Qnan = STATIC_SYMBOL("NAN",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_extremum_cache_g2_struct = 
	    STATIC_SYMBOL("EXTREMUM-CACHE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qextremum_cache = STATIC_SYMBOL("EXTREMUM-CACHE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_extremum_cache_g2_struct,
	    Qextremum_cache,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qextremum_cache,
	    Qg2_defstruct_structure_name_extremum_cache_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_extremum_cache == UNBOUND)
	The_type_description_of_extremum_cache = Nil;
    string_constant_4 = 
	    STATIC_STRING("43Dy8m83hFy1n83hFy8n8k1l8n0000000kzk0k0");
    temp = The_type_description_of_extremum_cache;
    The_type_description_of_extremum_cache = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_4));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_extremum_cache_g2_struct,
	    The_type_description_of_extremum_cache,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qextremum_cache,
	    The_type_description_of_extremum_cache,Qtype_description_of_type);
    Qoutstanding_extremum_cache_count = 
	    STATIC_SYMBOL("OUTSTANDING-EXTREMUM-CACHE-COUNT",AB_package);
    Qextremum_cache_structure_memory_usage = 
	    STATIC_SYMBOL("EXTREMUM-CACHE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_5 = STATIC_STRING("1q83hFy8s83-Thy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_extremum_cache_count);
    push_optimized_constant(Qextremum_cache_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_5));
    Qchain_of_available_extremum_caches = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EXTREMUM-CACHES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_extremum_caches,
	    Chain_of_available_extremum_caches);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_extremum_caches,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qextremum_cache_count = STATIC_SYMBOL("EXTREMUM-CACHE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qextremum_cache_count,Extremum_cache_count);
    record_system_variable(Qextremum_cache_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_extremum_caches_vector == UNBOUND)
	Chain_of_available_extremum_caches_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qextremum_cache_structure_memory_usage,
	    STATIC_FUNCTION(extremum_cache_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_extremum_cache_count,
	    STATIC_FUNCTION(outstanding_extremum_cache_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_extremum_cache_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_extremum_cache,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qextremum_cache,
	    reclaim_structure_for_extremum_cache_1);
    Qgeneric_history = STATIC_SYMBOL("GENERIC-HISTORY",AB_package);
    Qdependent_frame = STATIC_SYMBOL("DEPENDENT-FRAME",AB_package);
    list_constant_1 = STATIC_CONS(Qdependent_frame,Qnil);
    check_if_superior_classes_are_defined(Qgeneric_history,list_constant_1);
    string_constant_6 = STATIC_STRING("1l1l8t");
    string_constant_7 = 
	    STATIC_STRING("1r4z8r83Pxy83Pxy83Pty83Pty00001m1l8o1l8l000004z8r83Q+y83Q+y83Pty83Pty00001m1l8o1l8l000004z8r83Q*y83Q*y83Pty83Pty00001n1l8o1l8l1l");
    string_constant_8 = 
	    STATIC_STRING("83Cy000004z8r83Puy83Puy83Pty83Pty00001m1l8o1l8l000004z8r83Pwy83Pwy83Pty83Pty00001n1l8o1l8l1l83Cy000004z8r83Pvy83Pvy83Pty83Pty000");
    string_constant_9 = 
	    STATIC_STRING("01m1l8o1l8l000004z8r83Q-y83Q-y83Pty83Pty00001n1l8o1l8l1l83Cy00000");
    string_constant_10 = 
	    STATIC_STRING("1t8q1n83Pty1l83=fy8t1o83Pxy08o8l1o83Q+y08o8l1p83Q*y08o8l83Cy1o83Puy08o8l1p83Pwy08o8l83Cy1o83Pvy08o8l1p83Q-y08o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_6);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_7,
	    string_constant_8,string_constant_9));
    add_class_to_environment(9,Qgeneric_history,list_constant_1,Nil,temp,
	    Nil,temp_1,list_constant_1,
	    regenerate_optimized_constant(string_constant_10),Nil);
    Qgeneric_history_data_serial_number = 
	    STATIC_SYMBOL("GENERIC-HISTORY-DATA-SERIAL-NUMBER",AB_package);
    Qreclaim_generic_history_data_serial_number_value = 
	    STATIC_SYMBOL("RECLAIM-GENERIC-HISTORY-DATA-SERIAL-NUMBER-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_generic_history_data_serial_number_value,
	    STATIC_FUNCTION(reclaim_generic_history_data_serial_number_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qgeneric_history_data_serial_number,
	    SYMBOL_FUNCTION(Qreclaim_generic_history_data_serial_number_value),
	    Qslot_value_reclaimer);
    if (Trace_validate_p == UNBOUND)
	Trace_validate_p = Nil;
    Qcurrent_block_of_dependent_frame = 
	    STATIC_SYMBOL("CURRENT-BLOCK-OF-DEPENDENT-FRAME",AB_package);
    Qcopy_frame_for_generic_history = 
	    STATIC_SYMBOL("COPY-FRAME-FOR-GENERIC-HISTORY",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_frame_for_generic_history,
	    STATIC_FUNCTION(copy_frame_for_generic_history,NIL,FALSE,1,1));
    Qcopy_frame = STATIC_SYMBOL("COPY-FRAME",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcopy_frame_for_generic_history);
    set_get(Qgeneric_history,Qcopy_frame,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcopy_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qgeneric_history,temp);
    mutate_global_property(Qcopy_frame,temp_2,Qclasses_which_define);
    Qcleanup_for_generic_history = 
	    STATIC_SYMBOL("CLEANUP-FOR-GENERIC-HISTORY",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_generic_history,
	    STATIC_FUNCTION(cleanup_for_generic_history,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_generic_history);
    set_get(Qgeneric_history,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qgeneric_history,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qconstant = STATIC_SYMBOL("CONSTANT",AB_package);
    Qcascaded = STATIC_SYMBOL("CASCADED",AB_package);
    float_constant = STATIC_FLOAT(1.0);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qmaximum = STATIC_SYMBOL("MAXIMUM",AB_package);
    Qminimum = STATIC_SYMBOL("MINIMUM",AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant = 
	    STATIC_STRING("The plot expression \"~ND\" indicates variable or parameter without history.");
    string_constant_1 = 
	    STATIC_STRING("The plot expression \"~ND\" did not evaluate to a variable or parameter.");
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    string_constant_2 = 
	    STATIC_STRING("The variable or parameter ~a does not have a history.");
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    string_constant_3 = STATIC_STRING("No variable or parameter available");
    Qinclusive = STATIC_SYMBOL("INCLUSIVE",AB_package);
    Qexclusive = STATIC_SYMBOL("EXCLUSIVE",AB_package);
    Qloose = STATIC_SYMBOL("LOOSE",AB_package);
    float_constant_1 = STATIC_FLOAT(1.7976931348623158E+304);
    float_constant_2 = STATIC_FLOAT(-1.7976931348623158E+304);
    float_constant_3 = STATIC_FLOAT(0.0);
}
