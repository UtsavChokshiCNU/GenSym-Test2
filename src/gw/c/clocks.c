/* clocks.c
 * Input file:  clocks.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "clocks.h"


Object G2int_g2_time_at_start = UNBOUND;

Object G2int_g2_time_at_start_as_text_string = UNBOUND;

Object G2int_fixnum_time_of_last_real_time_tick = UNBOUND;

Object G2int_most_recent_g2_time = UNBOUND;

Object G2int_real_time_of_last_g2_tick = UNBOUND;

Object G2int_fixnum_time_of_last_g2_tick = UNBOUND;

Object G2int_fixnum_time_until_g2_time_tick = UNBOUND;

Object G2int_g2_time_to_tick_p_base = UNBOUND;

Object G2int_real_time_to_tick_p_base = UNBOUND;

Object G2int_gensym_time = UNBOUND;

Object G2int_gensym_base_time_as_managed_float = UNBOUND;

Object G2int_gensym_time_at_start = UNBOUND;

static Object Qg2int_gensym;       /* gensym */

/* INITIALIZE-GENSYM-TIME */
Object g2int_initialize_gensym_time()
{
    Object current_fixnum_time, amf_available_array_cons_qm, amf_array, temp;
    Object svref_new_value, amf_result, incff_1_arg, new_float;
    Object wide_string_bv16, b1, b2, b3, b4;
    SI_Long bv16_length, aref_arg_2, aref_new_value;
    double current_unix_time, temp_1, aref_new_value_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(36,0);
    if ( !TRUEP(G2int_gensym_base_time_as_managed_float)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    current_unix_time = inline_ffloor_1(g2ext_unix_time_as_float());
	    current_fixnum_time = g2int_c_native_clock_ticks_or_cache(T,Nil);
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,current_unix_time);
	    G2int_current_real_time = new_float;
	    G2int_fixnum_time_of_last_real_time_tick = current_fixnum_time;
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,current_unix_time);
	    G2int_current_g2_time = new_float;
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,current_unix_time);
	    G2int_most_recent_g2_time = new_float;
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,current_unix_time);
	    G2int_real_time_of_last_g2_tick = new_float;
	    G2int_fixnum_time_of_last_g2_tick = current_fixnum_time;
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,current_unix_time);
	    G2int_g2_time_at_start = new_float;
	    wide_string_bv16 = 
		    g2int_allocate_byte_vector_16(FIX((SI_Long)4L + 
		    (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    aref_arg_2 = bv16_length - (SI_Long)2L;
	    aref_new_value = (SI_Long)4L & (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    aref_arg_2 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)4L,(SI_Long)0L);
	    G2int_g2_time_at_start_as_text_string = wide_string_bv16;
	    result = g2int_partition_managed_float(G2int_g2_time_at_start);
	    MVS_4(result,b1,b2,b3,b4);
	    temp = G2int_g2_time_at_start_as_text_string;
	    UBYTE_16_ISASET_1(temp,(SI_Long)0L,IFIX(b1));
	    temp = G2int_g2_time_at_start_as_text_string;
	    UBYTE_16_ISASET_1(temp,(SI_Long)1L,IFIX(b2));
	    temp = G2int_g2_time_at_start_as_text_string;
	    UBYTE_16_ISASET_1(temp,(SI_Long)2L,IFIX(b3));
	    temp = G2int_g2_time_at_start_as_text_string;
	    UBYTE_16_ISASET_1(temp,(SI_Long)3L,IFIX(b4));
	    G2int_g2_time_to_tick_p_base = current_fixnum_time;
	    G2int_real_time_to_tick_p_base = current_fixnum_time;
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(G2int_seconds_from_1900_to_1970);
	    aref_new_value_1 = current_unix_time + temp_1;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    G2int_gensym_base_time_as_managed_float = new_float;
	    G2int_gensym_time = FIX((SI_Long)0L);
	    G2int_gensym_time_at_start = FIX((SI_Long)0L);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    return VALUES_1(Nil);
}

static Object Qg2int_real_time;    /* real-time */

/* PRESET-GENSYM-TIME-FOR-INITIALIZATION */
Object g2int_preset_gensym_time_for_initialization()
{
    Object aref_arg_1, current_fixnum_time;
    double temp, aref_new_value, current_time, floored_current_time;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(36,1);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (G2int_warmbootingqm) {
	    if (G2int_warmbooting_with_catch_upqm) {
		G2int_gensym_time = G2int_warmboot_current_time;
		aref_arg_1 = G2int_current_g2_time;
		temp = DOUBLE_FLOAT_TO_DOUBLE(G2int_seconds_from_1900_to_1970);
		aref_new_value = 
			DFLOAT_ISAREF_1(G2int_gensym_base_time_as_managed_float,
			(SI_Long)0L) - temp + 
			(double)IFIX(G2int_warmboot_current_time);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = G2int_most_recent_g2_time;
		aref_new_value = DFLOAT_ISAREF_1(G2int_current_g2_time,
			(SI_Long)0L);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = G2int_real_time_of_last_g2_tick;
		aref_new_value = g2ext_unix_time_as_float();
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		G2int_fixnum_time_of_last_g2_tick = 
			g2int_c_native_clock_ticks_or_cache(Nil,Nil);
		aref_arg_1 = G2int_g2_time_at_start;
		aref_new_value = DFLOAT_ISAREF_1(G2int_current_g2_time,
			(SI_Long)0L) - 
			(double)IFIX(FIXNUM_MINUS(G2int_gensym_time,
			G2int_gensym_time_at_start));
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else if ( !EQ(Qg2int_real_time,Qg2int_real_time)) {
		G2int_gensym_time = G2int_warmboot_simulated_time;
		aref_arg_1 = G2int_current_g2_time;
		temp = DOUBLE_FLOAT_TO_DOUBLE(G2int_seconds_from_1900_to_1970);
		aref_new_value = 
			DFLOAT_ISAREF_1(G2int_gensym_base_time_as_managed_float,
			(SI_Long)0L) - temp + 
			(double)IFIX(G2int_warmboot_simulated_time);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = G2int_most_recent_g2_time;
		aref_new_value = DFLOAT_ISAREF_1(G2int_current_g2_time,
			(SI_Long)0L);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = G2int_real_time_of_last_g2_tick;
		aref_new_value = g2ext_unix_time_as_float();
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		G2int_fixnum_time_of_last_g2_tick = 
			g2int_c_native_clock_ticks_or_cache(Nil,Nil);
		aref_arg_1 = G2int_g2_time_at_start;
		aref_new_value = DFLOAT_ISAREF_1(G2int_current_g2_time,
			(SI_Long)0L) - 
			(double)IFIX(FIXNUM_MINUS(G2int_gensym_time,
			G2int_gensym_time_at_start));
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		G2int_gensym_time = G2int_gensym_time_at_start;
		aref_arg_1 = G2int_current_g2_time;
		temp = DOUBLE_FLOAT_TO_DOUBLE(G2int_seconds_from_1900_to_1970);
		aref_new_value = 
			DFLOAT_ISAREF_1(G2int_gensym_base_time_as_managed_float,
			(SI_Long)0L) - temp + 
			(double)IFIX(G2int_gensym_time_at_start);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = G2int_most_recent_g2_time;
		aref_new_value = DFLOAT_ISAREF_1(G2int_current_g2_time,
			(SI_Long)0L);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = G2int_real_time_of_last_g2_tick;
		aref_new_value = g2ext_unix_time_as_float();
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		G2int_fixnum_time_of_last_g2_tick = 
			g2int_c_native_clock_ticks_or_cache(Nil,Nil);
		aref_arg_1 = G2int_g2_time_at_start;
		aref_new_value = DFLOAT_ISAREF_1(G2int_current_g2_time,
			(SI_Long)0L);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	}
	else {
	    current_time = g2ext_unix_time_as_float();
	    current_fixnum_time = g2int_c_native_clock_ticks_or_cache(T,Nil);
	    floored_current_time = inline_ffloor_1(current_time);
	    aref_arg_1 = G2int_gensym_base_time_as_managed_float;
	    temp = DOUBLE_FLOAT_TO_DOUBLE(G2int_seconds_from_1900_to_1970);
	    aref_new_value = floored_current_time + temp - 
		    (double)IFIX(G2int_gensym_time);
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    G2int_gensym_time_at_start = G2int_gensym_time;
	    aref_arg_1 = G2int_current_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_current_time);
	    aref_arg_1 = G2int_most_recent_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_current_time);
	    aref_arg_1 = G2int_real_time_of_last_g2_tick;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,current_time);
	    G2int_fixnum_time_of_last_g2_tick = current_fixnum_time;
	    aref_arg_1 = G2int_g2_time_at_start;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_current_time);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

Object G2int_force_clock_tick = UNBOUND;

/* TICK-THE-REAL-TIME-CLOCK */
Object g2int_tick_the_real_time_clock(current_fixnum_time)
    Object current_fixnum_time;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_3;
    Object svref_new_value, amf_result, incff_1_arg, new_float, discontinuity;
    SI_Long gensymed_symbol, temp_1;
    char temp_2;
    double current_unix_time, most_recent_real_time, unix_time_delta;
    double fixnum_time_delta, clock_difference, absolute_difference, arg;
    double arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(36,2);
    if (FIXNUM_GE(current_fixnum_time,G2int_real_time_to_tick_p_base))
	temp = FIXNUM_MINUS(current_fixnum_time,
		G2int_real_time_to_tick_p_base);
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(current_fixnum_time,
		G2int_real_time_to_tick_p_base));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	temp = FIX(gensymed_symbol + (SI_Long)1L);
    }
    if (FIXNUM_GE(temp,G2int_fixnum_time_until_real_time_tick)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    current_unix_time = g2ext_unix_time_as_float();
	    most_recent_real_time = 
		    DFLOAT_ISAREF_1(G2int_current_real_time,(SI_Long)0L);
	    unix_time_delta = current_unix_time - most_recent_real_time;
	    if (FIXNUM_GE(current_fixnum_time,
		    G2int_fixnum_time_of_last_real_time_tick))
		temp_1 = IFIX(FIXNUM_MINUS(current_fixnum_time,
			G2int_fixnum_time_of_last_real_time_tick));
	    else {
		gensymed_symbol = IFIX(FIXNUM_MINUS(current_fixnum_time,
			G2int_fixnum_time_of_last_real_time_tick));
		gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
		temp_1 = gensymed_symbol + (SI_Long)1L;
	    }
	    fixnum_time_delta = (double)temp_1 / 
		    (double)IFIX(G2int_fixnum_time_units_per_second);
	    clock_difference = unix_time_delta - fixnum_time_delta;
	    absolute_difference = ABS(clock_difference);
	    arg = absolute_difference;
	    arg_1 = 2.0;
	    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		arg = unix_time_delta;
		arg_1 = 0.0;
		temp_2 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?
			  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		if (temp_2);
		else {
		    arg = absolute_difference;
		    arg_1 = fixnum_time_delta * 0.1;
		    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1)) {
			arg = fixnum_time_delta;
			arg_1 = 86400.0;
			temp_2 = arg < arg_1 &&  
				!inline_nanp_for_comparison(arg) ?  
				!inline_nanp_for_comparison(arg_1) : 
				TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		}
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		amf_available_array_cons_qm = 
			ISVREF(G2int_vector_of_simple_float_array_pools,
			(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_3 = G2int_vector_of_simple_float_array_pools;
		    svref_new_value = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_3,FIX((SI_Long)1L)) = svref_new_value;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qg2int_gensym);
		    temp_3 = G2int_available_gensym_conses;
		    M_CDR(amf_available_array_cons_qm) = temp_3;
		    G2int_available_gensym_conses = 
			    amf_available_array_cons_qm;
		    amf_result = amf_array;
		}
		else {
		    temp_3 = 
			    FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		    G2int_created_simple_float_array_pool_arrays = temp_3;
		    incff_1_arg = 
			    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		    temp_3 = 
			    FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			    incff_1_arg);
		    G2int_simple_float_array_pool_memory_usage = temp_3;
		    amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
		}
		new_float = amf_result;
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,clock_difference);
		discontinuity = new_float;
		g2int_real_time_clock_discontinuity(discontinuity);
		g2int_reclaim_managed_simple_float_array_of_length_1(discontinuity);
	    }
	    arg = current_unix_time;
	    arg_1 = most_recent_real_time;
	    if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))) {
		temp_3 = G2int_current_real_time;
		DFLOAT_ISASET_1(temp_3,(SI_Long)0L,current_unix_time);
		G2int_fixnum_time_of_last_real_time_tick = current_fixnum_time;
		G2int_real_time_to_tick_p_base = current_fixnum_time;
		temp = T;
	    }
	    else
		temp = Nil;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TICK-THE-CLOCK-FOR-TW-OR-GSI */
Object g2int_tick_the_clock_for_tw_or_gsi()
{
    Object local_fixnum_time, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(36,3);
    local_fixnum_time = g2int_c_native_clock_ticks_or_cache(T,Nil);
    if (FIXNUM_GE(local_fixnum_time,G2int_real_time_to_tick_p_base))
	temp = FIXNUM_MINUS(local_fixnum_time,G2int_real_time_to_tick_p_base);
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(local_fixnum_time,
		G2int_real_time_to_tick_p_base));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	temp = FIX(gensymed_symbol + (SI_Long)1L);
    }
    if (FIXNUM_GE(temp,G2int_fixnum_time_until_real_time_tick)) {
	if (g2int_tick_the_real_time_clock(local_fixnum_time))
	    g2int_unpack_future_tasks_into_current_task_queues(Nil);
    }
    return VALUES_1(Nil);
}

/* REAL-TIME-CLOCK-DISCONTINUITY */
Object g2int_real_time_clock_discontinuity(managed_float)
    Object managed_float;
{
    x_note_fn_call(36,4);
    g2int_adjust_task_times_after_clock_discontinuity(managed_float,
	    G2int_future_real_time_tasks);
    return VALUES_1(Nil);
}

/* G2-TIME-CLOCK-DISCONTINUITY */
Object g2int_g2_time_clock_discontinuity(managed_float)
    Object managed_float;
{
    x_note_fn_call(36,5);
    g2int_adjust_g2_clock_times_after_discontinuity_1(managed_float);
    g2int_adjust_task_times_after_clock_discontinuity(managed_float,
	    G2int_future_g2_time_tasks);
    return VALUES_1(Nil);
}

/* ADJUST-G2-CLOCK-TIMES-AFTER-DISCONTINUITY-1 */
Object g2int_adjust_g2_clock_times_after_discontinuity_1(managed_float)
    Object managed_float;
{
    Object aref_arg_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    double gensymed_symbol, arg, arg_1, integral_seconds_of_difference;
    double aref_new_value;

    x_note_fn_call(36,6);
    gensymed_symbol = DFLOAT_ISAREF_1(G2int_current_g2_time,(SI_Long)0L) + 
	    DFLOAT_ISAREF_1(managed_float,(SI_Long)0L) - 
	    DFLOAT_ISAREF_1(G2int_g2_time_at_start,(SI_Long)0L) + 
	    (double)IFIX(G2int_gensym_time_at_start);
    arg = gensymed_symbol;
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(G2int_most_positive_fixnum_as_float);
    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
	    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    if (temp);
    else {
	arg = gensymed_symbol;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(G2int_most_negative_fixnum_as_float);
	temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    gensymed_symbol_1 = temp ? IFIX(Most_negative_fixnum) : 
	    inline_floor_1(gensymed_symbol);
    gensymed_symbol_2 = IFIX(G2int_gensym_time);
    integral_seconds_of_difference = (double)(gensymed_symbol_1 - 
	    gensymed_symbol_2);
    aref_arg_1 = G2int_gensym_base_time_as_managed_float;
    aref_new_value = 
	    DFLOAT_ISAREF_1(G2int_gensym_base_time_as_managed_float,
	    (SI_Long)0L) + integral_seconds_of_difference;
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    aref_arg_1 = G2int_g2_time_at_start;
    aref_new_value = DFLOAT_ISAREF_1(G2int_g2_time_at_start,(SI_Long)0L) + 
	    integral_seconds_of_difference;
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    return VALUES_1(Nil);
}

static Object float_constant;      /* 0.0 */

/* TICK-THE-G2-REAL-TIME-CLOCK */
Object g2int_tick_the_g2_real_time_clock(current_fixnum_time)
    Object current_fixnum_time;
{
    Object millisecond_minimum_scheduling_interval_qm, minimum_in_milliseconds;
    Object amf_available_array_cons_qm, amf_array, temp_2, svref_new_value;
    Object amf_result, incff_1_arg, new_float, discontinuity;
    Object gensymed_symbol_2, temp_4;
    SI_Long temp_1, gensymed_symbol;
    char temp;
    double current_unix_time, cached_g2_time;
    double float_minimum_scheduling_interval, arg, arg_1, time_1;
    double minimum_float, floored_tick_time, tick_time, unix_time_delta;
    double fixnum_time_delta, clock_difference, absolute_difference;
    double aref_new_value, gensymed_symbol_1, gensymed_symbol_3, temp_3;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(36,7);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_unix_time = g2ext_unix_time_as_float();
	cached_g2_time = DFLOAT_ISAREF_1(G2int_current_g2_time,(SI_Long)0L);
	millisecond_minimum_scheduling_interval_qm = Nil;
	float_minimum_scheduling_interval = 
		millisecond_minimum_scheduling_interval_qm ? 
		(double)IFIX(millisecond_minimum_scheduling_interval_qm) / 
		1000.0 : 0.0;
	G2int_force_clock_tick = Nil;
	if (millisecond_minimum_scheduling_interval_qm) {
	    arg = current_unix_time;
	    arg_1 = cached_g2_time + float_minimum_scheduling_interval;
	    temp = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = current_unix_time;
		arg_1 = cached_g2_time - float_minimum_scheduling_interval;
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	}
	else {
	    arg = current_unix_time;
	    arg_1 = cached_g2_time;
	    temp =  !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) && 
		     !inline_nanp_for_comparison(arg_1));
	}
	if (temp) {
	    time_1 = current_unix_time;
	    minimum_in_milliseconds = 
		    millisecond_minimum_scheduling_interval_qm;
	    minimum_float = float_minimum_scheduling_interval;
	    if (minimum_in_milliseconds) {
		if (IFIX(minimum_in_milliseconds) < (SI_Long)1000L) {
		    floored_tick_time = inline_ffloor_1(time_1);
		    tick_time = floored_tick_time + 
			    inline_ffloor_1((time_1 - floored_tick_time + 
			    1.0E-6) / minimum_float) * minimum_float;
		}
		else
		    tick_time = inline_ffloor_1(time_1 / minimum_float) * 
			    minimum_float;
	    }
	    else
		tick_time = time_1;
	    unix_time_delta = tick_time - cached_g2_time;
	    if (FIXNUM_GE(current_fixnum_time,
		    G2int_fixnum_time_of_last_g2_tick))
		temp_1 = IFIX(FIXNUM_MINUS(current_fixnum_time,
			G2int_fixnum_time_of_last_g2_tick));
	    else {
		gensymed_symbol = IFIX(FIXNUM_MINUS(current_fixnum_time,
			G2int_fixnum_time_of_last_g2_tick));
		gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
		temp_1 = gensymed_symbol + (SI_Long)1L;
	    }
	    fixnum_time_delta = (double)temp_1 / 
		    (double)IFIX(G2int_fixnum_time_units_per_second);
	    clock_difference = unix_time_delta - fixnum_time_delta;
	    absolute_difference = ABS(clock_difference);
	    arg = absolute_difference;
	    arg_1 = 2.0;
	    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		arg = unix_time_delta;
		arg_1 = millisecond_minimum_scheduling_interval_qm ?  - 
			float_minimum_scheduling_interval : 0.0;
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		if (temp);
		else {
		    arg = absolute_difference;
		    arg_1 = fixnum_time_delta * 0.1;
		    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1)) {
			arg = fixnum_time_delta;
			arg_1 = 8.64E+7;
			temp = arg < arg_1 &&  
				!inline_nanp_for_comparison(arg) ?  
				!inline_nanp_for_comparison(arg_1) : 
				TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		amf_available_array_cons_qm = 
			ISVREF(G2int_vector_of_simple_float_array_pools,
			(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = G2int_vector_of_simple_float_array_pools;
		    svref_new_value = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = svref_new_value;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qg2int_gensym);
		    temp_2 = G2int_available_gensym_conses;
		    M_CDR(amf_available_array_cons_qm) = temp_2;
		    G2int_available_gensym_conses = 
			    amf_available_array_cons_qm;
		    amf_result = amf_array;
		}
		else {
		    temp_2 = 
			    FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		    G2int_created_simple_float_array_pool_arrays = temp_2;
		    incff_1_arg = 
			    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		    temp_2 = 
			    FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			    incff_1_arg);
		    G2int_simple_float_array_pool_memory_usage = temp_2;
		    amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
		}
		new_float = amf_result;
		aref_new_value = tick_time - cached_g2_time;
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		discontinuity = new_float;
		g2int_g2_time_clock_discontinuity(discontinuity);
		g2int_reclaim_managed_simple_float_array_of_length_1(discontinuity);
	    }
	    temp_2 = G2int_current_g2_time;
	    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,tick_time);
	    temp_2 = G2int_most_recent_g2_time;
	    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,cached_g2_time);
	    temp_2 = G2int_real_time_of_last_g2_tick;
	    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,current_unix_time);
	    G2int_fixnum_time_of_last_g2_tick = current_fixnum_time;
	    gensymed_symbol_1 = tick_time - 
		    DFLOAT_ISAREF_1(G2int_g2_time_at_start,(SI_Long)0L) + 
		    (double)IFIX(G2int_gensym_time_at_start);
	    arg = gensymed_symbol_1;
	    arg_1 = 
		    DOUBLE_FLOAT_TO_DOUBLE(G2int_most_positive_fixnum_as_float);
	    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = gensymed_symbol_1;
		arg_1 = 
			DOUBLE_FLOAT_TO_DOUBLE(G2int_most_negative_fixnum_as_float);
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    G2int_gensym_time = temp ? Most_negative_fixnum : 
		    LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol_1));
	    if (millisecond_minimum_scheduling_interval_qm) {
		gensymed_symbol_1 = 
			(double)IFIX(G2int_fixnum_time_units_per_second);
		gensymed_symbol_2 = float_constant;
		gensymed_symbol_3 = tick_time + 
			float_minimum_scheduling_interval - current_unix_time;
		temp_3 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_2);
		gensymed_symbol_3 = MAX(temp_3,gensymed_symbol_3);
		G2int_fixnum_time_until_g2_time_tick = 
			LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol_1 * 
			gensymed_symbol_3));
		G2int_g2_time_to_tick_p_base = current_fixnum_time;
	    }
	    else {
		G2int_fixnum_time_until_g2_time_tick = FIX((SI_Long)1L);
		G2int_g2_time_to_tick_p_base = current_fixnum_time;
	    }
	    temp_4 = T;
	}
	else
	    temp_4 = Nil;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_4);
}

/* TICK-THE-G2-FAST-TIME-CLOCK */
Object g2int_tick_the_g2_fast_time_clock(current_fixnum_time)
    Object current_fixnum_time;
{
    Object future_g2_tasks_exist_qm;
    Object millisecond_minimum_scheduling_interval_qm, minimum_in_milliseconds;
    Object aref_arg_1, temp_1;
    char temp;
    double next_scheduled_task_time, float_minimum_scheduling_interval, time_1;
    double minimum_float, floored_tick_time, tick_time, aref_new_value;
    double gensymed_symbol, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(36,8);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	future_g2_tasks_exist_qm = ISVREF(G2int_future_g2_time_tasks,
		(SI_Long)0L);
	next_scheduled_task_time = future_g2_tasks_exist_qm ? 
		DFLOAT_ISAREF_1(ISVREF(future_g2_tasks_exist_qm,
		(SI_Long)1L),(SI_Long)0L) : 0.0;
	millisecond_minimum_scheduling_interval_qm = Nil;
	float_minimum_scheduling_interval = 
		millisecond_minimum_scheduling_interval_qm ? 
		(double)IFIX(millisecond_minimum_scheduling_interval_qm) / 
		1000.0 : 0.0;
	G2int_force_clock_tick = Nil;
	if (future_g2_tasks_exist_qm) {
	    time_1 = next_scheduled_task_time;
	    minimum_in_milliseconds = 
		    millisecond_minimum_scheduling_interval_qm;
	    minimum_float = float_minimum_scheduling_interval;
	    if (minimum_in_milliseconds) {
		if (IFIX(minimum_in_milliseconds) < (SI_Long)1000L) {
		    floored_tick_time = inline_ffloor_1(time_1);
		    tick_time = floored_tick_time + 
			    inline_fceiling_1((time_1 - floored_tick_time 
			    - 1.0E-6) / minimum_float) * minimum_float;
		}
		else
		    tick_time = inline_fceiling_1(time_1 / minimum_float) 
			    * minimum_float;
	    }
	    else
		tick_time = time_1;
	    aref_arg_1 = G2int_most_recent_g2_time;
	    aref_new_value = DFLOAT_ISAREF_1(G2int_current_g2_time,
		    (SI_Long)0L);
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    aref_arg_1 = G2int_current_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,tick_time);
	    aref_arg_1 = G2int_real_time_of_last_g2_tick;
	    aref_new_value = g2ext_unix_time_as_float();
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    G2int_fixnum_time_of_last_g2_tick = current_fixnum_time;
	    gensymed_symbol = tick_time - 
		    DFLOAT_ISAREF_1(G2int_g2_time_at_start,(SI_Long)0L) + 
		    (double)IFIX(G2int_gensym_time_at_start);
	    arg = gensymed_symbol;
	    arg_1 = 
		    DOUBLE_FLOAT_TO_DOUBLE(G2int_most_positive_fixnum_as_float);
	    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = gensymed_symbol;
		arg_1 = 
			DOUBLE_FLOAT_TO_DOUBLE(G2int_most_negative_fixnum_as_float);
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    G2int_gensym_time = temp ? Most_negative_fixnum : 
		    LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol));
	    G2int_fixnum_time_until_g2_time_tick = FIX((SI_Long)0L);
	    G2int_g2_time_to_tick_p_base = current_fixnum_time;
	    temp_1 = T;
	}
	else
	    temp_1 = Nil;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_1);
}

/* TICK-THE-G2-SIMULATED-TIME-CLOCK */
Object g2int_tick_the_g2_simulated_time_clock(current_fixnum_time)
    Object current_fixnum_time;
{
    Object future_g2_tasks_exist_qm;
    Object millisecond_minimum_scheduling_interval_qm, minimum_in_milliseconds;
    Object aref_arg_1, gensymed_symbol_1, temp_2;
    char temp;
    double current_unix_time, elapsed_time_in_tick, g2_time, elapsed_g2_time;
    double next_scheduled_task_time, float_minimum_scheduling_interval, time_1;
    double minimum_float, floored_tick_time, potenial_elapsed_tick_time;
    double potential_schedule_tick_time, new_g2_time, arg, arg_1;
    double gensymed_symbol, gensymed_symbol_2, temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(36,9);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_unix_time = g2ext_unix_time_as_float();
	elapsed_time_in_tick = current_unix_time - 
		DFLOAT_ISAREF_1(G2int_real_time_of_last_g2_tick,(SI_Long)0L);
	g2_time = DFLOAT_ISAREF_1(G2int_current_g2_time,(SI_Long)0L);
	elapsed_g2_time = g2_time + elapsed_time_in_tick;
	future_g2_tasks_exist_qm = ISVREF(G2int_future_g2_time_tasks,
		(SI_Long)0L);
	next_scheduled_task_time = future_g2_tasks_exist_qm ? 
		DFLOAT_ISAREF_1(ISVREF(future_g2_tasks_exist_qm,
		(SI_Long)1L),(SI_Long)0L) : 0.0;
	millisecond_minimum_scheduling_interval_qm = Nil;
	float_minimum_scheduling_interval = 
		millisecond_minimum_scheduling_interval_qm ? 
		(double)IFIX(millisecond_minimum_scheduling_interval_qm) / 
		1000.0 : 0.0;
	time_1 = elapsed_g2_time;
	minimum_in_milliseconds = millisecond_minimum_scheduling_interval_qm;
	minimum_float = float_minimum_scheduling_interval;
	if (minimum_in_milliseconds) {
	    if (IFIX(minimum_in_milliseconds) < (SI_Long)1000L) {
		floored_tick_time = inline_ffloor_1(time_1);
		potenial_elapsed_tick_time = floored_tick_time + 
			inline_ffloor_1((time_1 - floored_tick_time + 
			1.0E-6) / minimum_float) * minimum_float;
	    }
	    else
		potenial_elapsed_tick_time = inline_ffloor_1(time_1 / 
			minimum_float) * minimum_float;
	}
	else
	    potenial_elapsed_tick_time = time_1;
	time_1 = next_scheduled_task_time;
	minimum_in_milliseconds = millisecond_minimum_scheduling_interval_qm;
	minimum_float = float_minimum_scheduling_interval;
	if (minimum_in_milliseconds) {
	    if (IFIX(minimum_in_milliseconds) < (SI_Long)1000L) {
		floored_tick_time = inline_ffloor_1(time_1);
		potential_schedule_tick_time = floored_tick_time + 
			inline_fceiling_1((time_1 - floored_tick_time - 
			1.0E-6) / minimum_float) * minimum_float;
	    }
	    else
		potential_schedule_tick_time = inline_fceiling_1(time_1 / 
			minimum_float) * minimum_float;
	}
	else
	    potential_schedule_tick_time = time_1;
	new_g2_time = future_g2_tasks_exist_qm ? 
		MIN(potenial_elapsed_tick_time,
		potential_schedule_tick_time) : potenial_elapsed_tick_time;
	G2int_force_clock_tick = Nil;
	arg = new_g2_time;
	arg_1 = g2_time;
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    aref_arg_1 = G2int_most_recent_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,g2_time);
	    aref_arg_1 = G2int_current_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,new_g2_time);
	    aref_arg_1 = G2int_real_time_of_last_g2_tick;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,current_unix_time);
	    G2int_fixnum_time_of_last_g2_tick = current_fixnum_time;
	    gensymed_symbol = new_g2_time - 
		    DFLOAT_ISAREF_1(G2int_g2_time_at_start,(SI_Long)0L) + 
		    (double)IFIX(G2int_gensym_time_at_start);
	    arg = gensymed_symbol;
	    arg_1 = 
		    DOUBLE_FLOAT_TO_DOUBLE(G2int_most_positive_fixnum_as_float);
	    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = gensymed_symbol;
		arg_1 = 
			DOUBLE_FLOAT_TO_DOUBLE(G2int_most_negative_fixnum_as_float);
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    G2int_gensym_time = temp ? Most_negative_fixnum : 
		    LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol));
	    if (millisecond_minimum_scheduling_interval_qm) {
		gensymed_symbol = 
			(double)IFIX(G2int_fixnum_time_units_per_second);
		gensymed_symbol_1 = float_constant;
		gensymed_symbol_2 = current_unix_time + 
			float_minimum_scheduling_interval - current_unix_time;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
		gensymed_symbol_2 = MAX(temp_1,gensymed_symbol_2);
		G2int_fixnum_time_until_g2_time_tick = 
			LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol * 
			gensymed_symbol_2));
		G2int_g2_time_to_tick_p_base = current_fixnum_time;
	    }
	    else {
		G2int_fixnum_time_until_g2_time_tick = FIX((SI_Long)1L);
		G2int_g2_time_to_tick_p_base = current_fixnum_time;
	    }
	    temp_2 = T;
	}
	else
	    temp_2 = Nil;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_2);
}

Object G2int_nupec_catch_up_mode_caught_upqm = UNBOUND;

/* TICK-THE-NUPEC-CATCH-UP-CLOCK */
Object g2int_tick_the_nupec_catch_up_clock(fixnum_time_units_time_stamp)
    Object fixnum_time_units_time_stamp;
{
    Object temp;
    char temp_1;

    x_note_fn_call(36,10);
    if ( !TRUEP(G2int_nupec_catch_up_mode_caught_upqm)) {
	temp = G2int_gensym_time;
	temp_1 = FIXNUM_GE(temp,g2int_get_real_gensym_time());
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	G2int_nupec_catch_up_mode_caught_upqm = T;
    temp = G2int_nupec_catch_up_mode_caught_upqm ? 
	    g2int_tick_the_g2_real_time_clock(fixnum_time_units_time_stamp) 
	    : g2int_tick_the_g2_fast_time_clock(fixnum_time_units_time_stamp);
    return VALUES_1(temp);
}

/* CHANGE-CURRENT-TIME-IN-NUPEC-CATCH-UP-MODE */
Object g2int_change_current_time_in_nupec_catch_up_mode(target_gensym_time)
    Object target_gensym_time;
{
    Object clock_adjustment, temp, amf_available_array_cons_qm, amf_array;
    Object svref_new_value, amf_result, incff_1_arg, new_float;
    Object managed_float_adjustment;
    double float_adjustment, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(36,11);
    clock_adjustment = FIXNUM_MINUS(target_gensym_time,G2int_gensym_time);
    if ( !(IFIX(clock_adjustment) == (SI_Long)0L)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    float_adjustment = (double)IFIX(clock_adjustment);
	    temp = G2int_gensym_base_time_as_managed_float;
	    aref_new_value = 
		    DFLOAT_ISAREF_1(G2int_gensym_base_time_as_managed_float,
		    (SI_Long)0L) + float_adjustment;
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,float_adjustment);
	    managed_float_adjustment = new_float;
	    g2int_g2_time_clock_discontinuity(managed_float_adjustment);
	    g2int_reclaim_managed_simple_float_array_of_length_1(managed_float_adjustment);
	    temp = G2int_current_g2_time;
	    aref_new_value = DFLOAT_ISAREF_1(G2int_current_g2_time,
		    (SI_Long)0L) - float_adjustment;
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    temp = G2int_most_recent_g2_time;
	    aref_new_value = DFLOAT_ISAREF_1(G2int_current_g2_time,
		    (SI_Long)0L);
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    temp = G2int_real_time_of_last_g2_tick;
	    aref_new_value = g2ext_unix_time_as_float();
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    G2int_fixnum_time_of_last_g2_tick = 
		    g2int_c_native_clock_ticks_or_cache(T,Nil);
	    G2int_fixnum_time_until_g2_time_tick = FIX((SI_Long)0L);
	    G2int_g2_time_to_tick_p_base = 
		    g2int_c_native_clock_ticks_or_cache(Nil,Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    G2int_nupec_catch_up_mode_caught_upqm = Nil;
    return VALUES_1(Nil);
}

static Object Qg2int_fast_time;    /* fast-time */

static Object Qg2int_simulated_time;  /* simulated-time */

static Object Qg2int_nupec_catch_up;  /* nupec-catch-up */

/* UPDATE-G2-TIME-TO-TICK-AFTER-SCHEDULING-CHANGE */
Object g2int_update_g2_time_to_tick_after_scheduling_change()
{
    Object current_fixnum_time, millisecond_minimum_scheduling_interval_qm;
    Object mode, gensymed_symbol_1;
    double current_unix_time, g2_time, float_minimum_scheduling_interval, arg;
    double arg_1, gensymed_symbol, gensymed_symbol_2, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(36,12);
    if (G2int_system_is_running || G2int_system_has_paused) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    current_fixnum_time = g2int_c_native_clock_ticks_or_cache(Nil,Nil);
	    current_unix_time = g2ext_unix_time_as_float();
	    g2_time = DFLOAT_ISAREF_1(G2int_current_g2_time,(SI_Long)0L);
	    millisecond_minimum_scheduling_interval_qm = Nil;
	    float_minimum_scheduling_interval = 
		    millisecond_minimum_scheduling_interval_qm ? 
		    (double)IFIX(millisecond_minimum_scheduling_interval_qm) 
		    / 1000.0 : 0.0;
	    mode = Qg2int_real_time;
	    if (EQ(mode,Qg2int_real_time)) {
		arg = current_unix_time;
		arg_1 = g2_time;
		if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    G2int_fixnum_time_until_g2_time_tick = FIX((SI_Long)0L);
		    G2int_g2_time_to_tick_p_base = current_fixnum_time;
		}
		else {
		    G2int_fixnum_time_until_g2_time_tick = FIX((SI_Long)1L);
		    G2int_g2_time_to_tick_p_base = current_fixnum_time;
		}
	    }
	    else if (EQ(mode,Qg2int_fast_time)) {
		G2int_fixnum_time_until_g2_time_tick = FIX((SI_Long)0L);
		G2int_g2_time_to_tick_p_base = current_fixnum_time;
	    }
	    else if (EQ(mode,Qg2int_simulated_time)) {
		if (millisecond_minimum_scheduling_interval_qm) {
		    gensymed_symbol = 
			    (double)IFIX(G2int_fixnum_time_units_per_second);
		    gensymed_symbol_1 = float_constant;
		    gensymed_symbol_2 = 
			    DFLOAT_ISAREF_1(G2int_real_time_of_last_g2_tick,
			    (SI_Long)0L) + 
			    float_minimum_scheduling_interval - 
			    current_unix_time;
		    temp = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
		    gensymed_symbol_2 = MAX(temp,gensymed_symbol_2);
		    G2int_fixnum_time_until_g2_time_tick = 
			    LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol 
			    * gensymed_symbol_2));
		    G2int_g2_time_to_tick_p_base = current_fixnum_time;
		}
		else {
		    arg = current_unix_time;
		    arg_1 = 
			    DFLOAT_ISAREF_1(G2int_real_time_of_last_g2_tick,
			    (SI_Long)0L);
		    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1)) {
			G2int_fixnum_time_until_g2_time_tick = 
				FIX((SI_Long)0L);
			G2int_g2_time_to_tick_p_base = current_fixnum_time;
		    }
		    else {
			G2int_fixnum_time_until_g2_time_tick = 
				FIX((SI_Long)1L);
			G2int_g2_time_to_tick_p_base = current_fixnum_time;
		    }
		}
	    }
	    else if (EQ(mode,Qg2int_nupec_catch_up)) {
		if (G2int_nupec_catch_up_mode_caught_upqm) {
		    if (millisecond_minimum_scheduling_interval_qm) {
			gensymed_symbol = 
				(double)IFIX(G2int_fixnum_time_units_per_second);
			gensymed_symbol_1 = float_constant;
			gensymed_symbol_2 = g2_time + 
				float_minimum_scheduling_interval - 
				current_unix_time;
			temp = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
			gensymed_symbol_2 = MAX(temp,gensymed_symbol_2);
			G2int_fixnum_time_until_g2_time_tick = 
				LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol 
				* gensymed_symbol_2));
			G2int_g2_time_to_tick_p_base = current_fixnum_time;
		    }
		    else {
			arg = current_unix_time;
			arg_1 = g2_time;
			if (arg > arg_1 &&  
				!inline_nanp_for_comparison(arg) &&  
				!inline_nanp_for_comparison(arg_1)) {
			    G2int_fixnum_time_until_g2_time_tick = 
				    FIX((SI_Long)0L);
			    G2int_g2_time_to_tick_p_base = current_fixnum_time;
			}
			else {
			    G2int_fixnum_time_until_g2_time_tick = 
				    FIX((SI_Long)1L);
			    G2int_g2_time_to_tick_p_base = current_fixnum_time;
			}
		    }
		}
		else {
		    G2int_fixnum_time_until_g2_time_tick = FIX((SI_Long)0L);
		    G2int_g2_time_to_tick_p_base = current_fixnum_time;
		}
	    }
	    else
		error((SI_Long)2L,
			"Unknown scheduler mode in update-g2-time-to-tick ~a",
			mode);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    return VALUES_1(Nil);
}

Object G2int_inhibit_non_real_time_clock_ticksqm = UNBOUND;

/* MILLISECONDS-TO-NEXT-TASK */
Object g2int_milliseconds_to_next_task()
{
    Object scheduler_mode, future_g2_time_tasks_qm, future_real_time_tasks_qm;
    Object temp;
    double unix_time, max_sleep, gensymed_symbol, gensymed_symbol_1;
    double seconds_to_next_real_time_task, seconds_to_next_g2_task;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(36,13);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	scheduler_mode = Qg2int_real_time;
	future_g2_time_tasks_qm = ISVREF(G2int_future_g2_time_tasks,
		(SI_Long)0L);
	future_real_time_tasks_qm = ISVREF(G2int_future_real_time_tasks,
		(SI_Long)0L);
	if (G2int_system_is_running && (G2int_force_clock_tick || 
		EQ(scheduler_mode,Qg2int_fast_time) && 
		future_g2_time_tasks_qm &&  
		!TRUEP(G2int_inhibit_non_real_time_clock_ticksqm)))
	    temp = FIX((SI_Long)0L);
	else if (future_real_time_tasks_qm || future_g2_time_tasks_qm && 
		G2int_system_is_running) {
	    unix_time = g2ext_unix_time_as_float();
	    max_sleep = 3600.0;
	    if (future_real_time_tasks_qm) {
		gensymed_symbol = 
			DFLOAT_ISAREF_1(ISVREF(future_real_time_tasks_qm,
			(SI_Long)1L),(SI_Long)0L) - unix_time;
		gensymed_symbol_1 = max_sleep;
		seconds_to_next_real_time_task = MIN(gensymed_symbol,
			gensymed_symbol_1);
	    }
	    else
		seconds_to_next_real_time_task = max_sleep;
	    if (G2int_system_is_running) {
		seconds_to_next_g2_task = max_sleep;
		future_g2_time_tasks_qm = 
			ISVREF(G2int_future_g2_time_tasks,(SI_Long)0L);
		if (future_g2_time_tasks_qm) {
		    if (EQ(scheduler_mode,Qg2int_real_time) || 
			    EQ(scheduler_mode,Qg2int_nupec_catch_up))
			seconds_to_next_g2_task = 
				DFLOAT_ISAREF_1(ISVREF(future_g2_time_tasks_qm,
				(SI_Long)1L),(SI_Long)0L) - unix_time;
		    else if (EQ(scheduler_mode,Qg2int_simulated_time))
			seconds_to_next_g2_task = 
				DFLOAT_ISAREF_1(ISVREF(future_g2_time_tasks_qm,
				(SI_Long)1L),(SI_Long)0L) - 
				DFLOAT_ISAREF_1(G2int_current_g2_time,
				(SI_Long)0L) - (unix_time - 
				DFLOAT_ISAREF_1(G2int_real_time_of_last_g2_tick,
				(SI_Long)0L));
		}
		temp = LONG_TO_FIXNUM(inline_floor_1(1000.0 * 
			MIN(seconds_to_next_real_time_task,
			seconds_to_next_g2_task)));
	    }
	    else
		temp = LONG_TO_FIXNUM(inline_floor_1(1000.0 * 
			seconds_to_next_real_time_task));
	}
	else
	    temp = Nil;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

Object G2int_starsome_time_agostar = UNBOUND;

/* GET-REAL-GENSYM-TIME */
Object g2int_get_real_gensym_time()
{
    Object temp_2;
    char temp_1;
    double temp, gensymed_symbol, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(36,14);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = g2ext_unix_time_as_float();
	gensymed_symbol = temp - DFLOAT_ISAREF_1(G2int_g2_time_at_start,
		(SI_Long)0L) + (double)IFIX(G2int_gensym_time_at_start);
	arg = gensymed_symbol;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(G2int_most_positive_fixnum_as_float);
	temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	if (temp_1);
	else {
	    arg = gensymed_symbol;
	    arg_1 = 
		    DOUBLE_FLOAT_TO_DOUBLE(G2int_most_negative_fixnum_as_float);
	    temp_1 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	temp_2 = temp_1 ? Most_negative_fixnum : 
		LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_2);
}

/* DECODE-GENSYM-TIME */
Object g2int_decode_gensym_time(gensym_time)
    Object gensym_time;
{
    Object second_1, minute, hour, date, month, year, day_of_week;
    Object daylight_savings_time_p, time_zone;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(36,15);
    PUSH_SPECIAL(G2int_gensym_time,gensym_time,0);
      second_1 = Nil;
      minute = Nil;
      hour = Nil;
      date = Nil;
      month = Nil;
      year = Nil;
      day_of_week = Nil;
      daylight_savings_time_p = Nil;
      time_zone = Nil;
      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  result = g2int_gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_MINUS(G2int_gensym_time,
		  G2int_gensym_time_at_start)) + 
		  DFLOAT_ISAREF_1(G2int_g2_time_at_start,(SI_Long)0L)));
	  MVS_9(result,second_1,minute,hour,date,month,year,day_of_week,
		  daylight_savings_time_p,time_zone);
      }
      POP_LOCAL_ALLOCATION(0,0);
      result = VALUES_9(second_1,minute,hour,date,month,year,day_of_week,
	      daylight_savings_time_p,time_zone);
    POP_SPECIAL();
    return result;
}

/* SAME-GENSYM-DATE-P */
Object g2int_same_gensym_date_p(gensym_time_1,gensym_time_2)
    Object gensym_time_1, gensym_time_2;
{
    Object temp, temp_1, day_1, month_1, year_1, temp_2, day_2, month_2;
    Object year_2;
    Object result;

    x_note_fn_call(36,16);
    result = g2int_decode_gensym_time(gensym_time_1);
    MVS_6(result,temp_1,temp_1,temp_1,day_1,month_1,year_1);
    result = g2int_decode_gensym_time(gensym_time_2);
    MVS_6(result,temp_1,temp_1,temp_1,day_2,month_2,year_2);
    temp_1 = FIXNUM_EQ(month_1,month_2) && FIXNUM_EQ(day_1,day_2) ? 
	    (FIXNUM_EQ(year_1,year_2) ? T : Nil) : Qnil;
    return VALUES_1(temp_1);
}

/* ENCODE-GENSYM-TIME */
Object g2int_encode_gensym_time(second_1,minute,hour,date,month,year)
    Object second_1, minute, hour, date, month, year;
{
    Object temp;
    char temp_1;
    double unix_time, arg, arg_1, gensymed_symbol, gensymed_symbol_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(36,17);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	unix_time = g2ext_get_encoded_unix_time(IFIX(second_1),
		IFIX(minute),IFIX(hour),IFIX(date),IFIX(month),IFIX(year));
	arg = unix_time;
	arg_1 = -1.0;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp = g2int_encode_unix_time_after_failure(second_1,minute,
		    hour,date,month,year);
	    gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    gensymed_symbol = unix_time;
	gensymed_symbol_1 = (double)((SI_Long)60L * 
		IFIX(G2int_global_daylight_saving_time_adjustment));
	gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	gensymed_symbol_1 = DFLOAT_ISAREF_1(G2int_g2_time_at_start,
		(SI_Long)0L);
	gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	gensymed_symbol_1 = (double)IFIX(G2int_gensym_time_at_start);
	gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	arg = gensymed_symbol;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(G2int_most_positive_fixnum_as_float);
	temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	if (temp_1);
	else {
	    arg = gensymed_symbol;
	    arg_1 = 
		    DOUBLE_FLOAT_TO_DOUBLE(G2int_most_negative_fixnum_as_float);
	    temp_1 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	temp = temp_1 ? Most_negative_fixnum : 
		LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

void clocks_INIT()
{
    Object Qg2int_cycles, Qg2int_inhibit_non_real_time_clock_ticksqm;
    Object AB_package, Qg2int_clocks, Qg2int_nupec_catch_up_mode_caught_upqm;
    Object Qg2int_gensym_time_at_start;
    Object Qg2int_gensym_base_time_as_managed_float, Qg2int_gensym_time;
    Object Kno_initial_value, Qg2int_real_time_to_tick_p_base;
    Object Qg2int_g2_time_to_tick_p_base;
    Object Qg2int_fixnum_time_until_g2_time_tick;
    Object Qg2int_fixnum_time_until_real_time_tick;
    Object Qg2int_fixnum_time_of_last_g2_tick;
    Object Qg2int_real_time_of_last_g2_tick, Qg2int_most_recent_g2_time;
    Object Qg2int_current_g2_time, Qg2int_fixnum_time_of_last_real_time_tick;
    Object Qg2int_current_real_time, Qg2int_g2_time_at_start_as_text_string;
    Object Qg2int_g2_time_at_start;

    x_note_fn_call(36,18);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_g2_time_at_start = STATIC_SYMBOL("G2-TIME-AT-START",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_g2_time_at_start,G2int_g2_time_at_start);
    Qg2int_clocks = STATIC_SYMBOL("CLOCKS",AB_package);
    Kno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",Pkeyword);
    g2int_record_system_variable(Qg2int_g2_time_at_start,Qg2int_clocks,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qg2int_g2_time_at_start_as_text_string = 
	    STATIC_SYMBOL("G2-TIME-AT-START-AS-TEXT-STRING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_g2_time_at_start_as_text_string,
	    G2int_g2_time_at_start_as_text_string);
    g2int_record_system_variable(Qg2int_g2_time_at_start_as_text_string,
	    Qg2int_clocks,Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qg2int_current_real_time = STATIC_SYMBOL("CURRENT-REAL-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_real_time,
	    G2int_current_real_time);
    g2int_record_system_variable(Qg2int_current_real_time,Qg2int_clocks,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qg2int_fixnum_time_of_last_real_time_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-OF-LAST-REAL-TIME-TICK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_fixnum_time_of_last_real_time_tick,
	    G2int_fixnum_time_of_last_real_time_tick);
    g2int_record_system_variable(Qg2int_fixnum_time_of_last_real_time_tick,
	    Qg2int_clocks,Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qg2int_current_g2_time = STATIC_SYMBOL("CURRENT-G2-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_g2_time,G2int_current_g2_time);
    g2int_record_system_variable(Qg2int_current_g2_time,Qg2int_clocks,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qg2int_most_recent_g2_time = STATIC_SYMBOL("MOST-RECENT-G2-TIME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_most_recent_g2_time,
	    G2int_most_recent_g2_time);
    g2int_record_system_variable(Qg2int_most_recent_g2_time,Qg2int_clocks,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qg2int_real_time_of_last_g2_tick = 
	    STATIC_SYMBOL("REAL-TIME-OF-LAST-G2-TICK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_real_time_of_last_g2_tick,
	    G2int_real_time_of_last_g2_tick);
    g2int_record_system_variable(Qg2int_real_time_of_last_g2_tick,
	    Qg2int_clocks,Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qg2int_fixnum_time_of_last_g2_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-OF-LAST-G2-TICK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_fixnum_time_of_last_g2_tick,
	    G2int_fixnum_time_of_last_g2_tick);
    g2int_record_system_variable(Qg2int_fixnum_time_of_last_g2_tick,
	    Qg2int_clocks,Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qg2int_fixnum_time_until_real_time_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-UNTIL-REAL-TIME-TICK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_fixnum_time_until_real_time_tick,FIX((SI_Long)1L));
    Qg2int_fixnum_time_until_g2_time_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-UNTIL-G2-TIME-TICK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_fixnum_time_until_g2_time_tick,
	    G2int_fixnum_time_until_g2_time_tick);
    g2int_record_system_variable(Qg2int_fixnum_time_until_g2_time_tick,
	    Qg2int_clocks,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_g2_time_to_tick_p_base = STATIC_SYMBOL("G2-TIME-TO-TICK-P-BASE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_g2_time_to_tick_p_base,
	    G2int_g2_time_to_tick_p_base);
    g2int_record_system_variable(Qg2int_g2_time_to_tick_p_base,
	    Qg2int_clocks,Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qg2int_real_time_to_tick_p_base = 
	    STATIC_SYMBOL("REAL-TIME-TO-TICK-P-BASE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_real_time_to_tick_p_base,
	    G2int_real_time_to_tick_p_base);
    g2int_record_system_variable(Qg2int_real_time_to_tick_p_base,
	    Qg2int_clocks,Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qg2int_gensym_time = STATIC_SYMBOL("GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gensym_time,G2int_gensym_time);
    g2int_record_system_variable(Qg2int_gensym_time,Qg2int_clocks,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_gensym_base_time_as_managed_float = 
	    STATIC_SYMBOL("GENSYM-BASE-TIME-AS-MANAGED-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gensym_base_time_as_managed_float,
	    G2int_gensym_base_time_as_managed_float);
    g2int_record_system_variable(Qg2int_gensym_base_time_as_managed_float,
	    Qg2int_clocks,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_gensym_time_at_start = STATIC_SYMBOL("GENSYM-TIME-AT-START",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gensym_time_at_start,
	    G2int_gensym_time_at_start);
    g2int_record_system_variable(Qg2int_gensym_time_at_start,Qg2int_clocks,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_real_time = STATIC_SYMBOL("REAL-TIME",AB_package);
    if (G2int_force_clock_tick == UNBOUND)
	G2int_force_clock_tick = Nil;
    float_constant = STATIC_FLOAT(0.0);
    Qg2int_nupec_catch_up_mode_caught_upqm = 
	    STATIC_SYMBOL("NUPEC-CATCH-UP-MODE-CAUGHT-UP\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_nupec_catch_up_mode_caught_upqm,
	    G2int_nupec_catch_up_mode_caught_upqm);
    g2int_record_system_variable(Qg2int_nupec_catch_up_mode_caught_upqm,
	    Qg2int_clocks,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_fast_time = STATIC_SYMBOL("FAST-TIME",AB_package);
    Qg2int_simulated_time = STATIC_SYMBOL("SIMULATED-TIME",AB_package);
    Qg2int_nupec_catch_up = STATIC_SYMBOL("NUPEC-CATCH-UP",AB_package);
    Qg2int_inhibit_non_real_time_clock_ticksqm = 
	    STATIC_SYMBOL("INHIBIT-NON-REAL-TIME-CLOCK-TICKS\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_inhibit_non_real_time_clock_ticksqm,
	    G2int_inhibit_non_real_time_clock_ticksqm);
    Qg2int_cycles = STATIC_SYMBOL("CYCLES",AB_package);
    g2int_record_system_variable(Qg2int_inhibit_non_real_time_clock_ticksqm,
	    Qg2int_cycles,Nil,Qnil,Qnil,Qnil,Qnil);
    G2int_starsome_time_agostar = FIX(IFIX(G2int_most_negative_fixnum32) + 
	    (SI_Long)2L * (SI_Long)7L * (SI_Long)24L * (SI_Long)60L * 
	    (SI_Long)60L);
}
