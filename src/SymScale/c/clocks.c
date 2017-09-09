/* clocks.c
 * Input file:  clocks.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "clocks.h"


DEFINE_VARIABLE_WITH_SYMBOL(G2_time_at_start, Qg2_time_at_start);

DEFINE_VARIABLE_WITH_SYMBOL(G2_time_at_start_as_text_string, Qg2_time_at_start_as_text_string);

DEFINE_VARIABLE_WITH_SYMBOL(Fixnum_time_of_last_real_time_tick, Qfixnum_time_of_last_real_time_tick);

DEFINE_VARIABLE_WITH_SYMBOL(Most_recent_g2_time, Qmost_recent_g2_time);

DEFINE_VARIABLE_WITH_SYMBOL(Real_time_of_last_g2_tick, Qreal_time_of_last_g2_tick);

DEFINE_VARIABLE_WITH_SYMBOL(Fixnum_time_of_last_g2_tick, Qfixnum_time_of_last_g2_tick);

DEFINE_VARIABLE_WITH_SYMBOL(Fixnum_time_until_g2_time_tick, Qfixnum_time_until_g2_time_tick);

DEFINE_VARIABLE_WITH_SYMBOL(G2_time_to_tick_p_base, Qg2_time_to_tick_p_base);

DEFINE_VARIABLE_WITH_SYMBOL(Real_time_to_tick_p_base, Qreal_time_to_tick_p_base);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_time_at_start, Qgensym_time_at_start);

static Object Qfloat_array;        /* float-array */

/* INITIALIZE-GENSYM-TIME */
Object initialize_gensym_time()
{
    Object current_fixnum_time, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float, wide_string_bv16, b1, b2, b3, b4;
    SI_Long bv16_length, aref_arg_2, aref_new_value;
    double current_unix_time, temp_2, aref_new_value_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(44,0);
    if ( !TRUEP(Gensym_base_time_as_managed_float)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    current_unix_time = inline_ffloor_1(g2ext_unix_time_as_float());
	    current_fixnum_time = c_native_clock_ticks_or_cache(T,Nil);
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,current_unix_time);
	    Current_real_time = new_float;
	    Fixnum_time_of_last_real_time_tick = current_fixnum_time;
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,current_unix_time);
	    Current_g2_time = new_float;
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,current_unix_time);
	    Most_recent_g2_time = new_float;
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,current_unix_time);
	    Real_time_of_last_g2_tick = new_float;
	    Fixnum_time_of_last_g2_tick = current_fixnum_time;
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,current_unix_time);
	    G2_time_at_start = new_float;
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)4L + 
		    (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    aref_arg_2 = bv16_length - (SI_Long)2L;
	    aref_new_value = (SI_Long)4L & (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    aref_arg_2 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)4L,(SI_Long)0L);
	    G2_time_at_start_as_text_string = wide_string_bv16;
	    result = partition_managed_float(G2_time_at_start);
	    MVS_4(result,b1,b2,b3,b4);
	    temp = G2_time_at_start_as_text_string;
	    UBYTE_16_ISASET_1(temp,(SI_Long)0L,IFIX(b1));
	    temp = G2_time_at_start_as_text_string;
	    UBYTE_16_ISASET_1(temp,(SI_Long)1L,IFIX(b2));
	    temp = G2_time_at_start_as_text_string;
	    UBYTE_16_ISASET_1(temp,(SI_Long)2L,IFIX(b3));
	    temp = G2_time_at_start_as_text_string;
	    UBYTE_16_ISASET_1(temp,(SI_Long)3L,IFIX(b4));
	    G2_time_to_tick_p_base = current_fixnum_time;
	    Real_time_to_tick_p_base = current_fixnum_time;
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
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
	    aref_new_value_1 = current_unix_time + temp_2;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    Gensym_base_time_as_managed_float = new_float;
	    Gensym_time = FIX((SI_Long)0L);
	    Gensym_time_at_start = FIX((SI_Long)0L);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Warmbooting_qm, Qwarmbooting_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Warmbooting_with_catch_up_qm, Qwarmbooting_with_catch_up_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Warmboot_current_time, Qwarmboot_current_time);

DEFINE_VARIABLE_WITH_SYMBOL(Warmboot_simulated_time, Qwarmboot_simulated_time);

static Object Qreal_time;          /* real-time */

/* PRESET-GENSYM-TIME-FOR-INITIALIZATION */
Object preset_gensym_time_for_initialization()
{
    Object gensymed_symbol, gensymed_symbol_1, aref_arg_1, current_fixnum_time;
    double temp, aref_new_value, current_time, floored_current_time;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,1);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (Warmbooting_qm) {
	    if (Warmbooting_with_catch_up_qm) {
	      next_loop:
		gensymed_symbol = Gensym_time;
		gensymed_symbol_1 = Warmboot_current_time;
		if (CAS_SYMBOL(Qgensym_time,gensymed_symbol,gensymed_symbol_1))
		    goto end_1;
		goto next_loop;
	      end_loop:
	      end_1:
		aref_arg_1 = Current_g2_time;
		temp = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		aref_new_value = 
			DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
			(SI_Long)0L) - temp + 
			(double)IFIX(Warmboot_current_time);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = Most_recent_g2_time;
		aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = Real_time_of_last_g2_tick;
		aref_new_value = g2ext_unix_time_as_float();
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	      next_loop_1:
		gensymed_symbol = Fixnum_time_of_last_g2_tick;
		gensymed_symbol_1 = c_native_clock_ticks_or_cache(Nil,Nil);
		if (CAS_SYMBOL(Qfixnum_time_of_last_g2_tick,
			gensymed_symbol,gensymed_symbol_1))
		    goto end_2;
		goto next_loop_1;
	      end_loop_1:
	      end_2:
		aref_arg_1 = G2_time_at_start;
		aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - 
			(double)IFIX(FIXNUM_MINUS(Gensym_time,
			Gensym_time_at_start));
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else if ( !EQ(Qreal_time,
		    scheduler_mode_function(Timing_parameters))) {
	      next_loop_2:
		gensymed_symbol = Gensym_time;
		gensymed_symbol_1 = Warmboot_simulated_time;
		if (CAS_SYMBOL(Qgensym_time,gensymed_symbol,gensymed_symbol_1))
		    goto end_3;
		goto next_loop_2;
	      end_loop_2:
	      end_3:
		aref_arg_1 = Current_g2_time;
		temp = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		aref_new_value = 
			DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
			(SI_Long)0L) - temp + 
			(double)IFIX(Warmboot_simulated_time);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = Most_recent_g2_time;
		aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = Real_time_of_last_g2_tick;
		aref_new_value = g2ext_unix_time_as_float();
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	      next_loop_3:
		gensymed_symbol = Fixnum_time_of_last_g2_tick;
		gensymed_symbol_1 = c_native_clock_ticks_or_cache(Nil,Nil);
		if (CAS_SYMBOL(Qfixnum_time_of_last_g2_tick,
			gensymed_symbol,gensymed_symbol_1))
		    goto end_4;
		goto next_loop_3;
	      end_loop_3:
	      end_4:
		aref_arg_1 = G2_time_at_start;
		aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - 
			(double)IFIX(FIXNUM_MINUS(Gensym_time,
			Gensym_time_at_start));
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
	      next_loop_4:
		gensymed_symbol = Gensym_time;
		gensymed_symbol_1 = Gensym_time_at_start;
		if (CAS_SYMBOL(Qgensym_time,gensymed_symbol,gensymed_symbol_1))
		    goto end_5;
		goto next_loop_4;
	      end_loop_4:
	      end_5:
		aref_arg_1 = Current_g2_time;
		temp = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		aref_new_value = 
			DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
			(SI_Long)0L) - temp + 
			(double)IFIX(Gensym_time_at_start);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = Most_recent_g2_time;
		aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		aref_arg_1 = Real_time_of_last_g2_tick;
		aref_new_value = g2ext_unix_time_as_float();
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	      next_loop_5:
		gensymed_symbol = Fixnum_time_of_last_g2_tick;
		gensymed_symbol_1 = c_native_clock_ticks_or_cache(Nil,Nil);
		if (CAS_SYMBOL(Qfixnum_time_of_last_g2_tick,
			gensymed_symbol,gensymed_symbol_1))
		    goto end_6;
		goto next_loop_5;
	      end_loop_5:
	      end_6:
		aref_arg_1 = G2_time_at_start;
		aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	}
	else {
	    current_time = g2ext_unix_time_as_float();
	    current_fixnum_time = c_native_clock_ticks_or_cache(T,Nil);
	    floored_current_time = inline_ffloor_1(current_time);
	    aref_arg_1 = Gensym_base_time_as_managed_float;
	    temp = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
	    aref_new_value = floored_current_time + temp - 
		    (double)IFIX(Gensym_time);
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	  next_loop_6:
	    gensymed_symbol = Gensym_time_at_start;
	    gensymed_symbol_1 = Gensym_time;
	    if (CAS_SYMBOL(Qgensym_time_at_start,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_7;
	    goto next_loop_6;
	  end_loop_6:
	  end_7:
	    aref_arg_1 = Current_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_current_time);
	    aref_arg_1 = Most_recent_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_current_time);
	    aref_arg_1 = Real_time_of_last_g2_tick;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,current_time);
	  next_loop_7:
	    gensymed_symbol = Fixnum_time_of_last_g2_tick;
	    gensymed_symbol_1 = current_fixnum_time;
	    if (CAS_SYMBOL(Qfixnum_time_of_last_g2_tick,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_8;
	    goto next_loop_7;
	  end_loop_7:
	  end_8:
	    aref_arg_1 = G2_time_at_start;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_current_time);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Force_clock_tick, Qforce_clock_tick);

/* TICK-THE-REAL-TIME-CLOCK */
Object tick_the_real_time_clock(current_fixnum_time)
    Object current_fixnum_time;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_3, temp_4;
    Object amf_result, new_float, discontinuity, gensymed_symbol_1;
    Object gensymed_symbol_2;
    SI_Long gensymed_symbol, temp_1;
    char temp_2;
    double current_unix_time, most_recent_real_time, unix_time_delta;
    double fixnum_time_delta, clock_difference, absolute_difference, arg;
    double arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,2);
    if (FIXNUM_GE(current_fixnum_time,Real_time_to_tick_p_base))
	temp = FIXNUM_MINUS(current_fixnum_time,Real_time_to_tick_p_base);
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(current_fixnum_time,
		Real_time_to_tick_p_base));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	temp = FIX(gensymed_symbol + (SI_Long)1L);
    }
    if (FIXNUM_GE(temp,Fixnum_time_until_real_time_tick)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    current_unix_time = g2ext_unix_time_as_float();
	    most_recent_real_time = DFLOAT_ISAREF_1(Current_real_time,
		    (SI_Long)0L);
	    unix_time_delta = current_unix_time - most_recent_real_time;
	    if (FIXNUM_GE(current_fixnum_time,
		    Fixnum_time_of_last_real_time_tick))
		temp_1 = IFIX(FIXNUM_MINUS(current_fixnum_time,
			Fixnum_time_of_last_real_time_tick));
	    else {
		gensymed_symbol = IFIX(FIXNUM_MINUS(current_fixnum_time,
			Fixnum_time_of_last_real_time_tick));
		gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
		temp_1 = gensymed_symbol + (SI_Long)1L;
	    }
	    fixnum_time_delta = (double)temp_1 / 
		    (double)IFIX(Fixnum_time_units_per_second);
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
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,clock_difference);
		discontinuity = new_float;
		real_time_clock_discontinuity(discontinuity);
		reclaim_managed_simple_float_array_of_length_1(discontinuity);
	    }
	    arg = current_unix_time;
	    arg_1 = most_recent_real_time;
	    if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))) {
		temp_3 = Current_real_time;
		DFLOAT_ISASET_1(temp_3,(SI_Long)0L,current_unix_time);
	      next_loop:
		gensymed_symbol_1 = Fixnum_time_of_last_real_time_tick;
		gensymed_symbol_2 = current_fixnum_time;
		if (CAS_SYMBOL(Qfixnum_time_of_last_real_time_tick,
			gensymed_symbol_1,gensymed_symbol_2))
		    goto end_1;
		goto next_loop;
	      end_loop:
	      end_1:
	      next_loop_1:
		gensymed_symbol_1 = Real_time_to_tick_p_base;
		gensymed_symbol_2 = current_fixnum_time;
		if (CAS_SYMBOL(Qreal_time_to_tick_p_base,gensymed_symbol_1,
			gensymed_symbol_2))
		    goto end_2;
		goto next_loop_1;
	      end_loop_1:
	      end_2:
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
Object tick_the_clock_for_tw_or_gsi()
{
    Object local_fixnum_time, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(44,3);
    local_fixnum_time = c_native_clock_ticks_or_cache(T,Nil);
    if (FIXNUM_GE(local_fixnum_time,Real_time_to_tick_p_base))
	temp = FIXNUM_MINUS(local_fixnum_time,Real_time_to_tick_p_base);
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(local_fixnum_time,
		Real_time_to_tick_p_base));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	temp = FIX(gensymed_symbol + (SI_Long)1L);
    }
    if (FIXNUM_GE(temp,Fixnum_time_until_real_time_tick)) {
	if (tick_the_real_time_clock(local_fixnum_time))
	    unpack_future_tasks_into_current_task_queues(Nil);
    }
    return VALUES_1(Nil);
}

/* REAL-TIME-CLOCK-DISCONTINUITY */
Object real_time_clock_discontinuity(managed_float)
    Object managed_float;
{
    x_note_fn_call(44,4);
    adjust_task_times_after_clock_discontinuity(managed_float,
	    Future_real_time_tasks);
    return VALUES_1(Nil);
}

/* G2-TIME-CLOCK-DISCONTINUITY */
Object g2_time_clock_discontinuity(managed_float)
    Object managed_float;
{
    x_note_fn_call(44,5);
    adjust_g2_clock_times_after_discontinuity_1(managed_float);
    adjust_task_times_after_clock_discontinuity(managed_float,
	    Future_g2_time_tasks);
    add_delta_time_to_variables_and_parameters(managed_float);
    update_trend_charts_for_clock_discontinuity(managed_float);
    return VALUES_1(Nil);
}

/* ADJUST-G2-CLOCK-TIMES-AFTER-DISCONTINUITY-1 */
Object adjust_g2_clock_times_after_discontinuity_1(managed_float)
    Object managed_float;
{
    Object aref_arg_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    double gensymed_symbol, arg, arg_1, integral_seconds_of_difference;
    double aref_new_value;

    x_note_fn_call(44,6);
    gensymed_symbol = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) + 
	    DFLOAT_ISAREF_1(managed_float,(SI_Long)0L) - 
	    DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
	    (double)IFIX(Gensym_time_at_start);
    arg = gensymed_symbol;
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
	    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    if (temp);
    else {
	arg = gensymed_symbol;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
	temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    gensymed_symbol_1 = temp ? IFIX(Most_negative_fixnum) : 
	    inline_floor_1(gensymed_symbol);
    gensymed_symbol_2 = IFIX(Gensym_time);
    integral_seconds_of_difference = (double)(gensymed_symbol_1 - 
	    gensymed_symbol_2);
    aref_arg_1 = Gensym_base_time_as_managed_float;
    aref_new_value = DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
	    (SI_Long)0L) + integral_seconds_of_difference;
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    aref_arg_1 = G2_time_at_start;
    aref_new_value = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
	    integral_seconds_of_difference;
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    return VALUES_1(Nil);
}

static Object float_constant;      /* 0.0 */

/* TICK-THE-G2-REAL-TIME-CLOCK */
Object tick_the_g2_real_time_clock(current_fixnum_time)
    Object current_fixnum_time;
{
    Object millisecond_minimum_scheduling_interval_qm, gensymed_symbol;
    Object gensymed_symbol_1, minimum_in_milliseconds;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float, discontinuity, temp_5;
    SI_Long temp_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_5;
    char temp;
    double current_unix_time, cached_g2_time;
    double float_minimum_scheduling_interval, arg, arg_1, time_1;
    double minimum_float, floored_tick_time, tick_time, unix_time_delta;
    double fixnum_time_delta, clock_difference, absolute_difference;
    double aref_new_value, gensymed_symbol_3, gensymed_symbol_4, temp_4;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,7);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_unix_time = g2ext_unix_time_as_float();
	cached_g2_time = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	millisecond_minimum_scheduling_interval_qm = 
		minimum_scheduling_interval_function(Timing_parameters);
	float_minimum_scheduling_interval = 
		millisecond_minimum_scheduling_interval_qm ? 
		(double)IFIX(millisecond_minimum_scheduling_interval_qm) / 
		1000.0 : 0.0;
      next_loop:
	gensymed_symbol = Force_clock_tick;
	gensymed_symbol_1 = Nil;
	if (CAS_SYMBOL(Qforce_clock_tick,gensymed_symbol,gensymed_symbol_1))
	    goto end_1;
	goto next_loop;
      end_loop:
      end_1:
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
	    if (FIXNUM_GE(current_fixnum_time,Fixnum_time_of_last_g2_tick))
		temp_1 = IFIX(FIXNUM_MINUS(current_fixnum_time,
			Fixnum_time_of_last_g2_tick));
	    else {
		gensymed_symbol_2 = IFIX(FIXNUM_MINUS(current_fixnum_time,
			Fixnum_time_of_last_g2_tick));
		gensymed_symbol_2 = gensymed_symbol_2 + 
			IFIX(Most_positive_fixnum);
		temp_1 = gensymed_symbol_2 + (SI_Long)1L;
	    }
	    fixnum_time_delta = (double)temp_1 / 
		    (double)IFIX(Fixnum_time_units_per_second);
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
		aref_new_value = tick_time - cached_g2_time;
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		discontinuity = new_float;
		g2_time_clock_discontinuity(discontinuity);
		reclaim_managed_simple_float_array_of_length_1(discontinuity);
	    }
	    temp_2 = Current_g2_time;
	    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,tick_time);
	    temp_2 = Most_recent_g2_time;
	    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,cached_g2_time);
	    temp_2 = Real_time_of_last_g2_tick;
	    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,current_unix_time);
	  next_loop_1:
	    gensymed_symbol = Fixnum_time_of_last_g2_tick;
	    gensymed_symbol_1 = current_fixnum_time;
	    if (CAS_SYMBOL(Qfixnum_time_of_last_g2_tick,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_2;
	    goto next_loop_1;
	  end_loop_1:
	  end_2:
	  next_loop_2:
	    gensymed_symbol = Gensym_time;
	    gensymed_symbol_3 = tick_time - 
		    DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
		    (double)IFIX(Gensym_time_at_start);
	    arg = gensymed_symbol_3;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = gensymed_symbol_3;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    gensymed_symbol_2 = temp ? IFIX(Most_negative_fixnum) : 
		    inline_floor_1(gensymed_symbol_3);
	    if (CAS_SYMBOL(Qgensym_time,gensymed_symbol,
		    FIX(gensymed_symbol_2)))
		goto end_3;
	    goto next_loop_2;
	  end_loop_2:
	  end_3:
	    if (millisecond_minimum_scheduling_interval_qm) {
	      next_loop_3:
		gensymed_symbol = Fixnum_time_until_g2_time_tick;
		gensymed_symbol_3 = (double)IFIX(Fixnum_time_units_per_second);
		gensymed_symbol_1 = float_constant;
		gensymed_symbol_4 = tick_time + 
			float_minimum_scheduling_interval - current_unix_time;
		temp_4 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
		gensymed_symbol_4 = MAX(temp_4,gensymed_symbol_4);
		gensymed_symbol_5 = inline_floor_1(gensymed_symbol_3 * 
			gensymed_symbol_4);
		if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			gensymed_symbol,LONG_TO_FIXNUM(gensymed_symbol_5)))
		    goto end_4;
		goto next_loop_3;
	      end_loop_3:
	      end_4:
	      next_loop_4:
		gensymed_symbol = G2_time_to_tick_p_base;
		gensymed_symbol_1 = current_fixnum_time;
		if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			gensymed_symbol_1))
		    goto end_5;
		goto next_loop_4;
	      end_loop_4:
	      end_5:;
	    }
	    else {
	      next_loop_5:
		gensymed_symbol = Fixnum_time_until_g2_time_tick;
		gensymed_symbol_2 = (SI_Long)1L;
		if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			gensymed_symbol,FIX(gensymed_symbol_2)))
		    goto end_6;
		goto next_loop_5;
	      end_loop_5:
	      end_6:
	      next_loop_6:
		gensymed_symbol = G2_time_to_tick_p_base;
		gensymed_symbol_1 = current_fixnum_time;
		if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			gensymed_symbol_1))
		    goto end_7;
		goto next_loop_6;
	      end_loop_6:
	      end_7:;
	    }
	    temp_5 = T;
	}
	else
	    temp_5 = Nil;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_5);
}

/* TICK-THE-G2-FAST-TIME-CLOCK */
Object tick_the_g2_fast_time_clock(current_fixnum_time)
    Object current_fixnum_time;
{
    Object next_queue, future_g2_tasks_exist_qm;
    Object millisecond_minimum_scheduling_interval_qm, gensymed_symbol;
    Object gensymed_symbol_1, minimum_in_milliseconds, aref_arg_1, temp_1;
    SI_Long gensymed_symbol_3;
    char temp;
    double next_scheduled_task_time, float_minimum_scheduling_interval, time_1;
    double minimum_float, floored_tick_time, tick_time, aref_new_value;
    double gensymed_symbol_2, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,8);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	next_queue = 
		ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_g2_time_tasks),
		(SI_Long)0L),(SI_Long)0L));
	future_g2_tasks_exist_qm = EQ(next_queue,
		CDR(Future_g2_time_tasks)) ? Nil : next_queue;
	next_scheduled_task_time = future_g2_tasks_exist_qm ? 
		DFLOAT_ISAREF_1(ISVREF(future_g2_tasks_exist_qm,
		(SI_Long)1L),(SI_Long)0L) : 0.0;
	millisecond_minimum_scheduling_interval_qm = 
		minimum_scheduling_interval_function(Timing_parameters);
	float_minimum_scheduling_interval = 
		millisecond_minimum_scheduling_interval_qm ? 
		(double)IFIX(millisecond_minimum_scheduling_interval_qm) / 
		1000.0 : 0.0;
      next_loop:
	gensymed_symbol = Force_clock_tick;
	gensymed_symbol_1 = Nil;
	if (CAS_SYMBOL(Qforce_clock_tick,gensymed_symbol,gensymed_symbol_1))
	    goto end_1;
	goto next_loop;
      end_loop:
      end_1:
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
	    aref_arg_1 = Most_recent_g2_time;
	    aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    aref_arg_1 = Current_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,tick_time);
	    aref_arg_1 = Real_time_of_last_g2_tick;
	    aref_new_value = g2ext_unix_time_as_float();
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	  next_loop_1:
	    gensymed_symbol = Fixnum_time_of_last_g2_tick;
	    gensymed_symbol_1 = current_fixnum_time;
	    if (CAS_SYMBOL(Qfixnum_time_of_last_g2_tick,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_2;
	    goto next_loop_1;
	  end_loop_1:
	  end_2:
	  next_loop_2:
	    gensymed_symbol = Gensym_time;
	    gensymed_symbol_2 = tick_time - 
		    DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
		    (double)IFIX(Gensym_time_at_start);
	    arg = gensymed_symbol_2;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = gensymed_symbol_2;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    gensymed_symbol_3 = temp ? IFIX(Most_negative_fixnum) : 
		    inline_floor_1(gensymed_symbol_2);
	    if (CAS_SYMBOL(Qgensym_time,gensymed_symbol,
		    FIX(gensymed_symbol_3)))
		goto end_3;
	    goto next_loop_2;
	  end_loop_2:
	  end_3:
	  next_loop_3:
	    gensymed_symbol = Fixnum_time_until_g2_time_tick;
	    gensymed_symbol_3 = (SI_Long)0L;
	    if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,gensymed_symbol,
		    FIX(gensymed_symbol_3)))
		goto end_4;
	    goto next_loop_3;
	  end_loop_3:
	  end_4:
	  next_loop_4:
	    gensymed_symbol = G2_time_to_tick_p_base;
	    gensymed_symbol_1 = current_fixnum_time;
	    if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_5;
	    goto next_loop_4;
	  end_loop_4:
	  end_5:
	    temp_1 = T;
	}
	else
	    temp_1 = Nil;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_1);
}

/* TICK-THE-G2-SIMULATED-TIME-CLOCK */
Object tick_the_g2_simulated_time_clock(current_fixnum_time)
    Object current_fixnum_time;
{
    Object next_queue, future_g2_tasks_exist_qm;
    Object millisecond_minimum_scheduling_interval_qm, minimum_in_milliseconds;
    Object gensymed_symbol, gensymed_symbol_1, aref_arg_1, temp_2;
    SI_Long gensymed_symbol_3;
    SI_Long gensymed_symbol_5;
    char temp;
    double current_unix_time, elapsed_time_in_tick, g2_time, elapsed_g2_time;
    double next_scheduled_task_time, float_minimum_scheduling_interval, time_1;
    double minimum_float, floored_tick_time, potenial_elapsed_tick_time;
    double potential_schedule_tick_time, new_g2_time, arg, arg_1;
    double gensymed_symbol_2, gensymed_symbol_4, temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,9);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_unix_time = g2ext_unix_time_as_float();
	elapsed_time_in_tick = current_unix_time - 
		DFLOAT_ISAREF_1(Real_time_of_last_g2_tick,(SI_Long)0L);
	g2_time = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	elapsed_g2_time = g2_time + elapsed_time_in_tick;
	next_queue = 
		ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_g2_time_tasks),
		(SI_Long)0L),(SI_Long)0L));
	future_g2_tasks_exist_qm = EQ(next_queue,
		CDR(Future_g2_time_tasks)) ? Nil : next_queue;
	next_scheduled_task_time = future_g2_tasks_exist_qm ? 
		DFLOAT_ISAREF_1(ISVREF(future_g2_tasks_exist_qm,
		(SI_Long)1L),(SI_Long)0L) : 0.0;
	millisecond_minimum_scheduling_interval_qm = 
		minimum_scheduling_interval_function(Timing_parameters);
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
      next_loop:
	gensymed_symbol = Force_clock_tick;
	gensymed_symbol_1 = Nil;
	if (CAS_SYMBOL(Qforce_clock_tick,gensymed_symbol,gensymed_symbol_1))
	    goto end_1;
	goto next_loop;
      end_loop:
      end_1:
	arg = new_g2_time;
	arg_1 = g2_time;
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    aref_arg_1 = Most_recent_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,g2_time);
	    aref_arg_1 = Current_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,new_g2_time);
	    aref_arg_1 = Real_time_of_last_g2_tick;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,current_unix_time);
	  next_loop_1:
	    gensymed_symbol = Fixnum_time_of_last_g2_tick;
	    gensymed_symbol_1 = current_fixnum_time;
	    if (CAS_SYMBOL(Qfixnum_time_of_last_g2_tick,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_2;
	    goto next_loop_1;
	  end_loop_1:
	  end_2:
	  next_loop_2:
	    gensymed_symbol = Gensym_time;
	    gensymed_symbol_2 = new_g2_time - 
		    DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
		    (double)IFIX(Gensym_time_at_start);
	    arg = gensymed_symbol_2;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = gensymed_symbol_2;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    gensymed_symbol_3 = temp ? IFIX(Most_negative_fixnum) : 
		    inline_floor_1(gensymed_symbol_2);
	    if (CAS_SYMBOL(Qgensym_time,gensymed_symbol,
		    FIX(gensymed_symbol_3)))
		goto end_3;
	    goto next_loop_2;
	  end_loop_2:
	  end_3:
	    if (millisecond_minimum_scheduling_interval_qm) {
	      next_loop_3:
		gensymed_symbol = Fixnum_time_until_g2_time_tick;
		gensymed_symbol_2 = (double)IFIX(Fixnum_time_units_per_second);
		gensymed_symbol_1 = float_constant;
		gensymed_symbol_4 = current_unix_time + 
			float_minimum_scheduling_interval - current_unix_time;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
		gensymed_symbol_4 = MAX(temp_1,gensymed_symbol_4);
		gensymed_symbol_5 = inline_floor_1(gensymed_symbol_2 * 
			gensymed_symbol_4);
		if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			gensymed_symbol,LONG_TO_FIXNUM(gensymed_symbol_5)))
		    goto end_4;
		goto next_loop_3;
	      end_loop_3:
	      end_4:
	      next_loop_4:
		gensymed_symbol = G2_time_to_tick_p_base;
		gensymed_symbol_1 = current_fixnum_time;
		if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			gensymed_symbol_1))
		    goto end_5;
		goto next_loop_4;
	      end_loop_4:
	      end_5:;
	    }
	    else {
	      next_loop_5:
		gensymed_symbol = Fixnum_time_until_g2_time_tick;
		gensymed_symbol_3 = (SI_Long)1L;
		if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			gensymed_symbol,FIX(gensymed_symbol_3)))
		    goto end_6;
		goto next_loop_5;
	      end_loop_5:
	      end_6:
	      next_loop_6:
		gensymed_symbol = G2_time_to_tick_p_base;
		gensymed_symbol_1 = current_fixnum_time;
		if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			gensymed_symbol_1))
		    goto end_7;
		goto next_loop_6;
	      end_loop_6:
	      end_7:;
	    }
	    temp_2 = T;
	}
	else
	    temp_2 = Nil;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_2);
}

DEFINE_VARIABLE_WITH_SYMBOL(Nupec_catch_up_mode_caught_up_qm, Qnupec_catch_up_mode_caught_up_qm);

/* TICK-THE-NUPEC-CATCH-UP-CLOCK */
Object tick_the_nupec_catch_up_clock(fixnum_time_units_time_stamp)
    Object fixnum_time_units_time_stamp;
{
    Object temp;
    char temp_1;

    x_note_fn_call(44,10);
    if ( !TRUEP(Nupec_catch_up_mode_caught_up_qm)) {
	temp = Gensym_time;
	temp_1 = FIXNUM_GE(temp,get_real_gensym_time());
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	Nupec_catch_up_mode_caught_up_qm = T;
    temp = Nupec_catch_up_mode_caught_up_qm ? 
	    tick_the_g2_real_time_clock(fixnum_time_units_time_stamp) : 
	    tick_the_g2_fast_time_clock(fixnum_time_units_time_stamp);
    return VALUES_1(temp);
}

/* CHANGE-CURRENT-TIME-IN-NUPEC-CATCH-UP-MODE */
Object change_current_time_in_nupec_catch_up_mode(target_gensym_time)
    Object target_gensym_time;
{
    Object clock_adjustment, temp, amf_available_array_cons_qm, amf_array;
    Object temp_1, amf_result, new_float, managed_float_adjustment;
    Object gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    double float_adjustment, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,11);
    clock_adjustment = FIXNUM_MINUS(target_gensym_time,Gensym_time);
    if ( !(IFIX(clock_adjustment) == (SI_Long)0L)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    float_adjustment = (double)IFIX(clock_adjustment);
	    temp = Gensym_base_time_as_managed_float;
	    aref_new_value = 
		    DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
		    (SI_Long)0L) + float_adjustment;
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,float_adjustment);
	    managed_float_adjustment = new_float;
	    g2_time_clock_discontinuity(managed_float_adjustment);
	    reclaim_managed_simple_float_array_of_length_1(managed_float_adjustment);
	    temp = Current_g2_time;
	    aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) 
		    - float_adjustment;
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    temp = Most_recent_g2_time;
	    aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    temp = Real_time_of_last_g2_tick;
	    aref_new_value = g2ext_unix_time_as_float();
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	  next_loop:
	    gensymed_symbol = Fixnum_time_of_last_g2_tick;
	    gensymed_symbol_1 = c_native_clock_ticks_or_cache(T,Nil);
	    if (CAS_SYMBOL(Qfixnum_time_of_last_g2_tick,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_1;
	    goto next_loop;
	  end_loop:
	  end_1:
	  next_loop_1:
	    gensymed_symbol = Fixnum_time_until_g2_time_tick;
	    gensymed_symbol_2 = (SI_Long)0L;
	    if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,gensymed_symbol,
		    FIX(gensymed_symbol_2)))
		goto end_2;
	    goto next_loop_1;
	  end_loop_1:
	  end_2:
	  next_loop_2:
	    gensymed_symbol = G2_time_to_tick_p_base;
	    gensymed_symbol_1 = c_native_clock_ticks_or_cache(Nil,Nil);
	    if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_3;
	    goto next_loop_2;
	  end_loop_2:
	  end_3:;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    Nupec_catch_up_mode_caught_up_qm = Nil;
    return VALUES_1(Nil);
}

static Object Qfast_time;          /* fast-time */

static Object Qsimulated_time;     /* simulated-time */

static Object Qnupec_catch_up;     /* nupec-catch-up */

/* UPDATE-G2-TIME-TO-TICK-AFTER-SCHEDULING-CHANGE */
Object update_g2_time_to_tick_after_scheduling_change()
{
    Object current_fixnum_time, millisecond_minimum_scheduling_interval_qm;
    Object mode, gensymed_symbol, gensymed_symbol_2;
    SI_Long gensymed_symbol_1;
    SI_Long gensymed_symbol_5;
    double current_unix_time, g2_time, float_minimum_scheduling_interval, arg;
    double arg_1, gensymed_symbol_3, gensymed_symbol_4, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,12);
    if (System_is_running || System_has_paused) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    current_fixnum_time = c_native_clock_ticks_or_cache(Nil,Nil);
	    current_unix_time = g2ext_unix_time_as_float();
	    g2_time = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	    millisecond_minimum_scheduling_interval_qm = 
		    minimum_scheduling_interval_function(Timing_parameters);
	    float_minimum_scheduling_interval = 
		    millisecond_minimum_scheduling_interval_qm ? 
		    (double)IFIX(millisecond_minimum_scheduling_interval_qm) 
		    / 1000.0 : 0.0;
	    mode = scheduler_mode_function(Timing_parameters);
	    if (EQ(mode,Qreal_time)) {
		arg = current_unix_time;
		arg_1 = g2_time;
		if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		  next_loop:
		    gensymed_symbol = Fixnum_time_until_g2_time_tick;
		    gensymed_symbol_1 = (SI_Long)0L;
		    if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			    gensymed_symbol,FIX(gensymed_symbol_1)))
			goto end_1;
		    goto next_loop;
		  end_loop:
		  end_1:
		  next_loop_1:
		    gensymed_symbol = G2_time_to_tick_p_base;
		    gensymed_symbol_2 = current_fixnum_time;
		    if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			    gensymed_symbol_2))
			goto end_2;
		    goto next_loop_1;
		  end_loop_1:
		  end_2:;
		}
		else {
		  next_loop_2:
		    gensymed_symbol = Fixnum_time_until_g2_time_tick;
		    gensymed_symbol_1 = (SI_Long)1L;
		    if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			    gensymed_symbol,FIX(gensymed_symbol_1)))
			goto end_3;
		    goto next_loop_2;
		  end_loop_2:
		  end_3:
		  next_loop_3:
		    gensymed_symbol = G2_time_to_tick_p_base;
		    gensymed_symbol_2 = current_fixnum_time;
		    if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			    gensymed_symbol_2))
			goto end_4;
		    goto next_loop_3;
		  end_loop_3:
		  end_4:;
		}
	    }
	    else if (EQ(mode,Qfast_time)) {
	      next_loop_4:
		gensymed_symbol = Fixnum_time_until_g2_time_tick;
		gensymed_symbol_1 = (SI_Long)0L;
		if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			gensymed_symbol,FIX(gensymed_symbol_1)))
		    goto end_5;
		goto next_loop_4;
	      end_loop_4:
	      end_5:
	      next_loop_5:
		gensymed_symbol = G2_time_to_tick_p_base;
		gensymed_symbol_2 = current_fixnum_time;
		if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			gensymed_symbol_2))
		    goto end_6;
		goto next_loop_5;
	      end_loop_5:
	      end_6:;
	    }
	    else if (EQ(mode,Qsimulated_time)) {
		if (millisecond_minimum_scheduling_interval_qm) {
		  next_loop_6:
		    gensymed_symbol = Fixnum_time_until_g2_time_tick;
		    gensymed_symbol_3 = 
			    (double)IFIX(Fixnum_time_units_per_second);
		    gensymed_symbol_2 = float_constant;
		    gensymed_symbol_4 = 
			    DFLOAT_ISAREF_1(Real_time_of_last_g2_tick,
			    (SI_Long)0L) + 
			    float_minimum_scheduling_interval - 
			    current_unix_time;
		    temp = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_2);
		    gensymed_symbol_4 = MAX(temp,gensymed_symbol_4);
		    gensymed_symbol_5 = inline_floor_1(gensymed_symbol_3 * 
			    gensymed_symbol_4);
		    if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			    gensymed_symbol,LONG_TO_FIXNUM(gensymed_symbol_5)))
			goto end_7;
		    goto next_loop_6;
		  end_loop_6:
		  end_7:
		  next_loop_7:
		    gensymed_symbol = G2_time_to_tick_p_base;
		    gensymed_symbol_2 = current_fixnum_time;
		    if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			    gensymed_symbol_2))
			goto end_8;
		    goto next_loop_7;
		  end_loop_7:
		  end_8:;
		}
		else {
		    arg = current_unix_time;
		    arg_1 = DFLOAT_ISAREF_1(Real_time_of_last_g2_tick,
			    (SI_Long)0L);
		    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1)) {
		      next_loop_8:
			gensymed_symbol = Fixnum_time_until_g2_time_tick;
			gensymed_symbol_1 = (SI_Long)0L;
			if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
				gensymed_symbol,FIX(gensymed_symbol_1)))
			    goto end_9;
			goto next_loop_8;
		      end_loop_8:
		      end_9:
		      next_loop_9:
			gensymed_symbol = G2_time_to_tick_p_base;
			gensymed_symbol_2 = current_fixnum_time;
			if (CAS_SYMBOL(Qg2_time_to_tick_p_base,
				gensymed_symbol,gensymed_symbol_2))
			    goto end_10;
			goto next_loop_9;
		      end_loop_9:
		      end_10:;
		    }
		    else {
		      next_loop_10:
			gensymed_symbol = Fixnum_time_until_g2_time_tick;
			gensymed_symbol_1 = (SI_Long)1L;
			if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
				gensymed_symbol,FIX(gensymed_symbol_1)))
			    goto end_11;
			goto next_loop_10;
		      end_loop_10:
		      end_11:
		      next_loop_11:
			gensymed_symbol = G2_time_to_tick_p_base;
			gensymed_symbol_2 = current_fixnum_time;
			if (CAS_SYMBOL(Qg2_time_to_tick_p_base,
				gensymed_symbol,gensymed_symbol_2))
			    goto end_12;
			goto next_loop_11;
		      end_loop_11:
		      end_12:;
		    }
		}
	    }
	    else if (EQ(mode,Qnupec_catch_up)) {
		if (Nupec_catch_up_mode_caught_up_qm) {
		    if (millisecond_minimum_scheduling_interval_qm) {
		      next_loop_12:
			gensymed_symbol = Fixnum_time_until_g2_time_tick;
			gensymed_symbol_3 = 
				(double)IFIX(Fixnum_time_units_per_second);
			gensymed_symbol_2 = float_constant;
			gensymed_symbol_4 = g2_time + 
				float_minimum_scheduling_interval - 
				current_unix_time;
			temp = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_2);
			gensymed_symbol_4 = MAX(temp,gensymed_symbol_4);
			gensymed_symbol_5 = 
				inline_floor_1(gensymed_symbol_3 * 
				gensymed_symbol_4);
			if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
				gensymed_symbol,
				LONG_TO_FIXNUM(gensymed_symbol_5)))
			    goto end_13;
			goto next_loop_12;
		      end_loop_12:
		      end_13:
		      next_loop_13:
			gensymed_symbol = G2_time_to_tick_p_base;
			gensymed_symbol_2 = current_fixnum_time;
			if (CAS_SYMBOL(Qg2_time_to_tick_p_base,
				gensymed_symbol,gensymed_symbol_2))
			    goto end_14;
			goto next_loop_13;
		      end_loop_13:
		      end_14:;
		    }
		    else {
			arg = current_unix_time;
			arg_1 = g2_time;
			if (arg > arg_1 &&  
				!inline_nanp_for_comparison(arg) &&  
				!inline_nanp_for_comparison(arg_1)) {
			  next_loop_14:
			    gensymed_symbol = Fixnum_time_until_g2_time_tick;
			    gensymed_symbol_1 = (SI_Long)0L;
			    if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
				    gensymed_symbol,FIX(gensymed_symbol_1)))
				goto end_15;
			    goto next_loop_14;
			  end_loop_14:
			  end_15:
			  next_loop_15:
			    gensymed_symbol = G2_time_to_tick_p_base;
			    gensymed_symbol_2 = current_fixnum_time;
			    if (CAS_SYMBOL(Qg2_time_to_tick_p_base,
				    gensymed_symbol,gensymed_symbol_2))
				goto end_16;
			    goto next_loop_15;
			  end_loop_15:
			  end_16:;
			}
			else {
			  next_loop_16:
			    gensymed_symbol = Fixnum_time_until_g2_time_tick;
			    gensymed_symbol_1 = (SI_Long)1L;
			    if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
				    gensymed_symbol,FIX(gensymed_symbol_1)))
				goto end_17;
			    goto next_loop_16;
			  end_loop_16:
			  end_17:
			  next_loop_17:
			    gensymed_symbol = G2_time_to_tick_p_base;
			    gensymed_symbol_2 = current_fixnum_time;
			    if (CAS_SYMBOL(Qg2_time_to_tick_p_base,
				    gensymed_symbol,gensymed_symbol_2))
				goto end_18;
			    goto next_loop_17;
			  end_loop_17:
			  end_18:;
			}
		    }
		}
		else {
		  next_loop_18:
		    gensymed_symbol = Fixnum_time_until_g2_time_tick;
		    gensymed_symbol_1 = (SI_Long)0L;
		    if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			    gensymed_symbol,FIX(gensymed_symbol_1)))
			goto end_19;
		    goto next_loop_18;
		  end_loop_18:
		  end_19:
		  next_loop_19:
		    gensymed_symbol = G2_time_to_tick_p_base;
		    gensymed_symbol_2 = current_fixnum_time;
		    if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			    gensymed_symbol_2))
			goto end_20;
		    goto next_loop_19;
		  end_loop_19:
		  end_20:;
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

DEFINE_VARIABLE_WITH_SYMBOL(Inhibit_non_real_time_clock_ticks_qm, Qinhibit_non_real_time_clock_ticks_qm);

/* MILLISECONDS-TO-NEXT-TASK */
Object milliseconds_to_next_task()
{
    Object scheduler_mode, next_queue, future_g2_time_tasks_qm;
    Object future_real_time_tasks_qm, temp;
    double unix_time, max_sleep, gensymed_symbol, gensymed_symbol_1;
    double seconds_to_next_real_time_task, seconds_to_next_g2_task;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,13);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	scheduler_mode = scheduler_mode_function(Timing_parameters);
	next_queue = 
		ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_g2_time_tasks),
		(SI_Long)0L),(SI_Long)0L));
	future_g2_time_tasks_qm = EQ(next_queue,CDR(Future_g2_time_tasks)) 
		? Nil : next_queue;
	next_queue = 
		ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_real_time_tasks),
		(SI_Long)0L),(SI_Long)0L));
	future_real_time_tasks_qm = EQ(next_queue,
		CDR(Future_real_time_tasks)) ? Nil : next_queue;
	if (System_is_running && (Force_clock_tick || EQ(scheduler_mode,
		Qfast_time) && future_g2_time_tasks_qm &&  
		!TRUEP(Inhibit_non_real_time_clock_ticks_qm)))
	    temp = FIX((SI_Long)0L);
	else if (future_real_time_tasks_qm || future_g2_time_tasks_qm && 
		System_is_running) {
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
	    if (System_is_running) {
		seconds_to_next_g2_task = max_sleep;
		next_queue = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_g2_time_tasks),
			(SI_Long)0L),(SI_Long)0L));
		future_g2_time_tasks_qm = EQ(next_queue,
			CDR(Future_g2_time_tasks)) ? Nil : next_queue;
		if (future_g2_time_tasks_qm) {
		    if (EQ(scheduler_mode,Qreal_time) || EQ(scheduler_mode,
			    Qnupec_catch_up))
			seconds_to_next_g2_task = 
				DFLOAT_ISAREF_1(ISVREF(future_g2_time_tasks_qm,
				(SI_Long)1L),(SI_Long)0L) - unix_time;
		    else if (EQ(scheduler_mode,Qsimulated_time))
			seconds_to_next_g2_task = 
				DFLOAT_ISAREF_1(ISVREF(future_g2_time_tasks_qm,
				(SI_Long)1L),(SI_Long)0L) - 
				DFLOAT_ISAREF_1(Current_g2_time,
				(SI_Long)0L) - (unix_time - 
				DFLOAT_ISAREF_1(Real_time_of_last_g2_tick,
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

Object Some_time_ago = UNBOUND;

/* GET-REAL-GENSYM-TIME */
Object get_real_gensym_time()
{
    Object temp_2;
    char temp_1;
    double temp, gensymed_symbol, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,14);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = g2ext_unix_time_as_float();
	gensymed_symbol = temp - DFLOAT_ISAREF_1(G2_time_at_start,
		(SI_Long)0L) + (double)IFIX(Gensym_time_at_start);
	arg = gensymed_symbol;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	if (temp_1);
	else {
	    arg = gensymed_symbol;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
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
Object decode_gensym_time(gensym_time)
    Object gensym_time;
{
    Object second_1, minute, hour, date, month, year, day_of_week;
    Object daylight_savings_time_p, time_zone;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(44,15);
    PUSH_SPECIAL_WITH_SYMBOL(Gensym_time,Qgensym_time,gensym_time,0);
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
	  result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_MINUS(Gensym_time,
		  Gensym_time_at_start)) + 
		  DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L)));
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
Object same_gensym_date_p(gensym_time_1,gensym_time_2)
    Object gensym_time_1, gensym_time_2;
{
    Object temp, temp_1, day_1, month_1, year_1, temp_2, day_2, month_2;
    Object year_2;
    Object result;

    x_note_fn_call(44,16);
    result = decode_gensym_time(gensym_time_1);
    MVS_6(result,temp_1,temp_1,temp_1,day_1,month_1,year_1);
    result = decode_gensym_time(gensym_time_2);
    MVS_6(result,temp_1,temp_1,temp_1,day_2,month_2,year_2);
    temp_1 = FIXNUM_EQ(month_1,month_2) && FIXNUM_EQ(day_1,day_2) ? 
	    (FIXNUM_EQ(year_1,year_2) ? T : Nil) : Qnil;
    return VALUES_1(temp_1);
}

/* ENCODE-GENSYM-TIME */
Object encode_gensym_time(second_1,minute,hour,date,month,year)
    Object second_1, minute, hour, date, month, year;
{
    Object temp;
    char temp_1;
    double unix_time, arg, arg_1, gensymed_symbol, gensymed_symbol_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,17);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	unix_time = g2ext_get_encoded_unix_time(IFIX(second_1),
		IFIX(minute),IFIX(hour),IFIX(date),IFIX(month),IFIX(year));
	arg = unix_time;
	arg_1 = -1.0;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp = encode_unix_time_after_failure(second_1,minute,hour,
		    date,month,year);
	    gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    gensymed_symbol = unix_time;
	gensymed_symbol_1 = (double)((SI_Long)60L * 
		IFIX(Global_daylight_saving_time_adjustment));
	gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	gensymed_symbol_1 = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	gensymed_symbol_1 = (double)IFIX(Gensym_time_at_start);
	gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	arg = gensymed_symbol;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	if (temp_1);
	else {
	    arg = gensymed_symbol;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
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
    Object Qcycles, AB_package, Qclocks, Kno_initial_value;
    Object Qfixnum_time_until_real_time_tick;

    x_note_fn_call(44,18);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2_time_at_start = STATIC_SYMBOL("G2-TIME-AT-START",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_time_at_start,G2_time_at_start);
    Qclocks = STATIC_SYMBOL("CLOCKS",AB_package);
    Kno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",Pkeyword);
    record_system_variable(Qg2_time_at_start,Qclocks,Kno_initial_value,
	    Qnil,Qnil,Qnil,Qnil);
    Qg2_time_at_start_as_text_string = 
	    STATIC_SYMBOL("G2-TIME-AT-START-AS-TEXT-STRING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_time_at_start_as_text_string,
	    G2_time_at_start_as_text_string);
    record_system_variable(Qg2_time_at_start_as_text_string,Qclocks,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_real_time = STATIC_SYMBOL("CURRENT-REAL-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_real_time,Current_real_time);
    record_system_variable(Qcurrent_real_time,Qclocks,Kno_initial_value,
	    Qnil,Qnil,Qnil,Qnil);
    Qfixnum_time_of_last_real_time_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-OF-LAST-REAL-TIME-TICK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfixnum_time_of_last_real_time_tick,
	    Fixnum_time_of_last_real_time_tick);
    record_system_variable(Qfixnum_time_of_last_real_time_tick,Qclocks,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_g2_time = STATIC_SYMBOL("CURRENT-G2-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_g2_time,Current_g2_time);
    record_system_variable(Qcurrent_g2_time,Qclocks,Kno_initial_value,Qnil,
	    Qnil,Qnil,Qnil);
    Qmost_recent_g2_time = STATIC_SYMBOL("MOST-RECENT-G2-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_recent_g2_time,Most_recent_g2_time);
    record_system_variable(Qmost_recent_g2_time,Qclocks,Kno_initial_value,
	    Qnil,Qnil,Qnil,Qnil);
    Qreal_time_of_last_g2_tick = STATIC_SYMBOL("REAL-TIME-OF-LAST-G2-TICK",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreal_time_of_last_g2_tick,
	    Real_time_of_last_g2_tick);
    record_system_variable(Qreal_time_of_last_g2_tick,Qclocks,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qfixnum_time_of_last_g2_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-OF-LAST-G2-TICK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfixnum_time_of_last_g2_tick,
	    Fixnum_time_of_last_g2_tick);
    record_system_variable(Qfixnum_time_of_last_g2_tick,Qclocks,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qfixnum_time_until_real_time_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-UNTIL-REAL-TIME-TICK",AB_package);
    SET_SYMBOL_VALUE(Qfixnum_time_until_real_time_tick,FIX((SI_Long)1L));
    Qfixnum_time_until_g2_time_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-UNTIL-G2-TIME-TICK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfixnum_time_until_g2_time_tick,
	    Fixnum_time_until_g2_time_tick);
    record_system_variable(Qfixnum_time_until_g2_time_tick,Qclocks,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2_time_to_tick_p_base = STATIC_SYMBOL("G2-TIME-TO-TICK-P-BASE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_time_to_tick_p_base,G2_time_to_tick_p_base);
    record_system_variable(Qg2_time_to_tick_p_base,Qclocks,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qreal_time_to_tick_p_base = STATIC_SYMBOL("REAL-TIME-TO-TICK-P-BASE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreal_time_to_tick_p_base,
	    Real_time_to_tick_p_base);
    record_system_variable(Qreal_time_to_tick_p_base,Qclocks,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qgensym_time = STATIC_SYMBOL("GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_time,Gensym_time);
    record_system_variable(Qgensym_time,Qclocks,FIX((SI_Long)0L),Qnil,Qnil,
	    Qnil,Qnil);
    Qgensym_base_time_as_managed_float = 
	    STATIC_SYMBOL("GENSYM-BASE-TIME-AS-MANAGED-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_base_time_as_managed_float,
	    Gensym_base_time_as_managed_float);
    record_system_variable(Qgensym_base_time_as_managed_float,Qclocks,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qgensym_time_at_start = STATIC_SYMBOL("GENSYM-TIME-AT-START",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_time_at_start,Gensym_time_at_start);
    record_system_variable(Qgensym_time_at_start,Qclocks,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qreal_time = STATIC_SYMBOL("REAL-TIME",AB_package);
    if (Force_clock_tick == UNBOUND)
	Force_clock_tick = Nil;
    Qforce_clock_tick = STATIC_SYMBOL("FORCE-CLOCK-TICK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforce_clock_tick,Force_clock_tick);
    float_constant = STATIC_FLOAT(0.0);
    Qnupec_catch_up_mode_caught_up_qm = 
	    STATIC_SYMBOL("NUPEC-CATCH-UP-MODE-CAUGHT-UP\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnupec_catch_up_mode_caught_up_qm,
	    Nupec_catch_up_mode_caught_up_qm);
    record_system_variable(Qnupec_catch_up_mode_caught_up_qm,Qclocks,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qfast_time = STATIC_SYMBOL("FAST-TIME",AB_package);
    Qsimulated_time = STATIC_SYMBOL("SIMULATED-TIME",AB_package);
    Qnupec_catch_up = STATIC_SYMBOL("NUPEC-CATCH-UP",AB_package);
    Qinhibit_non_real_time_clock_ticks_qm = 
	    STATIC_SYMBOL("INHIBIT-NON-REAL-TIME-CLOCK-TICKS\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinhibit_non_real_time_clock_ticks_qm,
	    Inhibit_non_real_time_clock_ticks_qm);
    Qcycles = STATIC_SYMBOL("CYCLES",AB_package);
    record_system_variable(Qinhibit_non_real_time_clock_ticks_qm,Qcycles,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Some_time_ago = FIX(IFIX(Most_negative_fixnum32) + (SI_Long)2L * 
	    (SI_Long)7L * (SI_Long)24L * (SI_Long)60L * (SI_Long)60L);
}
