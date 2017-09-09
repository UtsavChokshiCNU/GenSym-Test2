/* times.c
 * Input file:  times.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "times.h"


Object G2int_seconds_from_1900_to_1970 = UNBOUND;

/* DECODE-UNIX-TIME-AS-MANAGED-FLOAT */
Object g2int_decode_unix_time_as_managed_float(managed_float)
    Object managed_float;
{
    Object seconds, minutes, hours, date, months, years, weekday, dstp;
    Object time_zone;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(29,0);
    seconds = Nil;
    minutes = Nil;
    hours = Nil;
    date = Nil;
    months = Nil;
    years = Nil;
    weekday = Nil;
    dstp = Nil;
    time_zone = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	result = g2int_gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_float,
		(SI_Long)0L)));
	MVS_9(result,seconds,minutes,hours,date,months,years,weekday,dstp,
		time_zone);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_9(seconds,minutes,hours,date,months,years,weekday,dstp,
	    time_zone);
}

static Object Qg2int_gensym;       /* gensym */

/* GET-UNIX-TIME-TO-THE-SECOND-AS-MANAGED-FLOAT */
Object g2int_get_unix_time_to_the_second_as_managed_float()
{
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float, temp_1;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(29,1);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	amf_available_array_cons_qm = 
		ISVREF(G2int_vector_of_simple_float_array_pools,(SI_Long)1L);
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
	    temp = FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
	    G2int_created_simple_float_array_pool_arrays = temp;
	    incff_1_arg = 
		    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    G2int_simple_float_array_pool_memory_usage = temp;
	    amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value = inline_ffloor_1(g2ext_unix_time_as_float());
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_1 = new_float;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_1);
}

/* LEAP-YEAR-P */
Object g2int_leap_year_p(year)
    Object year;
{
    Object temp_1;
    SI_Long temp;

    x_note_fn_call(29,2);
    temp = IFIX(year) % (SI_Long)4L;
    if ((SI_Long)0L == temp) {
	temp = IFIX(year) % (SI_Long)100L;
	temp_1 = (SI_Long)0L != temp ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    temp = IFIX(year) % (SI_Long)400L;
	    return VALUES_1((SI_Long)0L == temp ? T : Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

Object G2int_days_before_this_month = UNBOUND;

/* VALID-DATE-FOR-MONTH-P */
Object g2int_valid_date_for_month_p(day,month,year)
    Object day, month, year;
{
    Object temp;

    x_note_fn_call(29,3);
    temp = month;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L)))) {
	if ((SI_Long)1L <= IFIX(day))
	    return VALUES_1(IFIX(day) <= (SI_Long)31L ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 2:
	    if (g2int_leap_year_p(year)) {
		if ((SI_Long)1L <= IFIX(day))
		    return VALUES_1(IFIX(day) <= (SI_Long)29L ? T : Nil);
		else
		    return VALUES_1(Nil);
	    }
	    else if ((SI_Long)1L <= IFIX(day))
		return VALUES_1(IFIX(day) <= (SI_Long)28L ? T : Nil);
	    else
		return VALUES_1(Nil);
	  case 4:
	  case 6:
	  case 9:
	  case 11:
	    if ((SI_Long)1L <= IFIX(day))
		return VALUES_1(IFIX(day) <= (SI_Long)30L ? T : Nil);
	    else
		return VALUES_1(Nil);
	  default:
	    if ((SI_Long)1L <= IFIX(day))
		return VALUES_1(IFIX(day) <= (SI_Long)31L ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
}

/* ENCODE-UNIVERSAL-DATE */
Object g2int_encode_universal_date(day,month,year)
    Object day, month, year;
{
    SI_Long normalized_year, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long gensymed_symbol_5, gensymed_symbol_6;

    x_note_fn_call(29,4);
    normalized_year = IFIX(year) - (SI_Long)1900L;
    gensymed_symbol = normalized_year * (SI_Long)365L;
    gensymed_symbol_1 = 
	    IFIX(g2int_chestnut_floorf_function(FIX(normalized_year + 
	    (SI_Long)3L),FIX((SI_Long)4L)));
    gensymed_symbol_2 = 
	    IFIX(FIXNUM_NEGATE(g2int_chestnut_floorf_function(FIX(normalized_year 
	    + (SI_Long)99L),FIX((SI_Long)100L))));
    gensymed_symbol_3 = 
	    IFIX(g2int_chestnut_floorf_function(FIX(normalized_year + 
	    (SI_Long)299L),FIX((SI_Long)400L)));
    gensymed_symbol_4 = IFIX(nth(FIXNUM_SUB1(month),
	    G2int_days_before_this_month));
    gensymed_symbol_5 = IFIX(FIXNUM_SUB1(day));
    gensymed_symbol_6 = g2int_leap_year_p(year) && IFIX(month) > 
	    (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L;
    return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1 + 
	    gensymed_symbol_2 + gensymed_symbol_3 + gensymed_symbol_4 + 
	    gensymed_symbol_5 + gensymed_symbol_6));
}

/* GET-UNIVERSAL-DATE */
Object g2int_get_universal_date()
{
    Object temp, day, month, year;
    Object result;

    x_note_fn_call(29,5);
    result = g2int_get_decoded_real_time();
    MVS_6(result,temp,temp,temp,day,month,year);
    return g2int_encode_universal_date(day,month,year);
}

/* GET-CURRENT-YEAR */
Object g2int_get_current_year()
{
    Object year;
    Object result;

    x_note_fn_call(29,6);
    result = g2int_get_decoded_real_time();
    year = NTH_VALUE((SI_Long)5L, result);
    return VALUES_1(year);
}

Object G2int_unix_time_offset_was_computedqm = UNBOUND;

Object G2int_unix_time_offset_for_encoding = UNBOUND;

/* ENCODE-UNIX-DATE */
Object g2int_encode_unix_date(day,month,year)
    Object day, month, year;
{
    SI_Long normalized_year, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long gensymed_symbol_5, gensymed_symbol_6, gensymed_symbol_7;

    x_note_fn_call(29,7);
    normalized_year = IFIX(year) - (SI_Long)1900L;
    gensymed_symbol =  - (SI_Long)25567L;
    gensymed_symbol_1 = normalized_year * (SI_Long)365L;
    gensymed_symbol_2 = 
	    IFIX(g2int_chestnut_floorf_function(FIX(normalized_year + 
	    (SI_Long)3L),FIX((SI_Long)4L)));
    gensymed_symbol_3 = 
	    IFIX(FIXNUM_NEGATE(g2int_chestnut_floorf_function(FIX(normalized_year 
	    + (SI_Long)99L),FIX((SI_Long)100L))));
    gensymed_symbol_4 = 
	    IFIX(g2int_chestnut_floorf_function(FIX(normalized_year + 
	    (SI_Long)299L),FIX((SI_Long)400L)));
    gensymed_symbol_5 = IFIX(nth(FIXNUM_SUB1(month),
	    G2int_days_before_this_month));
    gensymed_symbol_6 = IFIX(FIXNUM_SUB1(day));
    gensymed_symbol_7 = g2int_leap_year_p(year) && IFIX(month) > 
	    (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L;
    return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1 + 
	    gensymed_symbol_2 + gensymed_symbol_3 + gensymed_symbol_4 + 
	    gensymed_symbol_5 + gensymed_symbol_6 + gensymed_symbol_7));
}

/* COMPUTE-UNIX-TIME-OFFSET */
Object g2int_compute_unix_time_offset()
{
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float, second_1, minute, hour, day;
    Object month, year, temp_2;
    double unix_time, old_unix_time_offset, temp_1, internally_encoded_time;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(29,8);
    if ( !TRUEP(G2int_unix_time_offset_was_computedqm)) {
	amf_available_array_cons_qm = 
		ISVREF(G2int_vector_of_simple_float_array_pools,(SI_Long)1L);
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
	    temp = FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
	    G2int_created_simple_float_array_pool_arrays = temp;
	    incff_1_arg = 
		    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    G2int_simple_float_array_pool_memory_usage = temp;
	    amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	G2int_unix_time_offset_for_encoding = new_float;
    }
    G2int_unix_time_offset_was_computedqm = T;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	unix_time = inline_ffloor_1(g2ext_unix_time_as_float());
	old_unix_time_offset = 
		DFLOAT_ISAREF_1(G2int_unix_time_offset_for_encoding,
		(SI_Long)0L);
	result = g2int_gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(unix_time));
	MVS_6(result,second_1,minute,hour,day,month,year);
	if ( !TRUEP(G2int_unix_time_offset_was_computedqm))
	    g2int_compute_unix_time_offset();
	temp_1 = (double)(IFIX(second_1) + IFIX(minute) * (SI_Long)60L + 
		IFIX(hour) * (SI_Long)3600L);
	temp_1 = temp_1 + 86400.0 * 
		(double)IFIX(g2int_encode_unix_date(day,month,year));
	internally_encoded_time = inline_ffloor_1(temp_1 + 
		DFLOAT_ISAREF_1(G2int_unix_time_offset_for_encoding,
		(SI_Long)0L));
	temp = G2int_unix_time_offset_for_encoding;
	aref_new_value = old_unix_time_offset + (unix_time - 
		internally_encoded_time);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp_2 = Nil;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_2);
}

/* GENSYM-ENCODE-UNIX-TIME-AS-GENSYM-FLOAT */
Object g2int_gensym_encode_unix_time_as_gensym_float(second_1,minute,hour,
	    day,month,year)
    Object second_1, minute, hour, day, month, year;
{
    Object temp;
    double unix_time, arg, arg_1, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(29,9);
    unix_time = g2ext_get_encoded_unix_time(IFIX(second_1),IFIX(minute),
	    IFIX(hour),IFIX(day),IFIX(month),IFIX(year));
    arg = unix_time;
    arg_1 = -1.0;
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	temp = g2int_encode_unix_time_after_failure(second_1,minute,hour,
		day,month,year);
	gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
    }
    else
	gensymed_symbol = unix_time;
    gensymed_symbol_1 = (double)((SI_Long)60L * 
	    IFIX(G2int_global_daylight_saving_time_adjustment));
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(gensymed_symbol - 
	    gensymed_symbol_1));
}

/* ENCODE-UNIX-TIME-AFTER-FAILURE */
Object g2int_encode_unix_time_after_failure(second_1,minute,hour,day,month,
	    year)
    Object second_1, minute, hour, day, month, year;
{
    double temp, time_since_1970_without_consulting_os;
    double time_since_1970_inferred_by_os, arg, arg_1;

    x_note_fn_call(29,10);
    if ( !TRUEP(G2int_unix_time_offset_was_computedqm))
	g2int_compute_unix_time_offset();
    temp = (double)(IFIX(second_1) + IFIX(minute) * (SI_Long)60L + 
	    IFIX(hour) * (SI_Long)3600L);
    temp = temp + 86400.0 * (double)IFIX(g2int_encode_unix_date(day,month,
	    year));
    time_since_1970_without_consulting_os = temp + 
	    DFLOAT_ISAREF_1(G2int_unix_time_offset_for_encoding,(SI_Long)0L);
    time_since_1970_inferred_by_os = 
	    g2ext_infer_encoded_unix_time(time_since_1970_without_consulting_os);
    arg = time_since_1970_inferred_by_os;
    arg_1 = -1.0;
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(time_since_1970_without_consulting_os));
    else
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(time_since_1970_inferred_by_os));
}

/* GENSYM-ENCODE-UNIX-TIME-AS-MANAGED-FLOAT */
Object g2int_gensym_encode_unix_time_as_managed_float(second_1,minute,hour,
	    day,month,year)
    Object second_1, minute, hour, day, month, year;
{
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float, temp_1;
    double unix_time, arg, arg_1, gensymed_symbol, gensymed_symbol_1;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(29,11);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	amf_available_array_cons_qm = 
		ISVREF(G2int_vector_of_simple_float_array_pools,(SI_Long)1L);
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
	    temp = FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
	    G2int_created_simple_float_array_pool_arrays = temp;
	    incff_1_arg = 
		    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    G2int_simple_float_array_pool_memory_usage = temp;
	    amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	unix_time = g2ext_get_encoded_unix_time(IFIX(second_1),
		IFIX(minute),IFIX(hour),IFIX(day),IFIX(month),IFIX(year));
	arg = unix_time;
	arg_1 = -1.0;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp_1 = g2int_encode_unix_time_after_failure(second_1,minute,
		    hour,day,month,year);
	    gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	}
	else
	    gensymed_symbol = unix_time;
	gensymed_symbol_1 = (double)((SI_Long)60L * 
		IFIX(G2int_global_daylight_saving_time_adjustment));
	aref_new_value = gensymed_symbol - gensymed_symbol_1;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_1 = new_float;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_1);
}

/* GET-DECODED-REAL-TIME */
Object g2int_get_decoded_real_time()
{
    Object second_1, minute, hour, date, month, year, day_of_week;
    Object daylight_savings_time_p, time_zone;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(29,12);
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
	result = g2int_gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(g2ext_unix_time_as_float()));
	MVS_9(result,second_1,minute,hour,date,month,year,day_of_week,
		daylight_savings_time_p,time_zone);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_9(second_1,minute,hour,date,month,year,day_of_week,
	    daylight_savings_time_p,time_zone);
}

Object G2int_year_at_compilation_time = UNBOUND;

/* NULL-OR-ZERO-P */
Object g2int_null_or_zero_p(x)
    Object x;
{
    Object temp;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(29,13);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp =  !TRUEP(x) ? T : Nil;
	if (temp);
	else
	    temp = FIXNUMP(x) ? (IFIX(x) == (SI_Long)0L ? T : Nil) : Qnil;
	if (temp);
	else if (FLOATP(x)) {
	    arg = DOUBLE_FLOAT_TO_DOUBLE(x);
	    arg_1 = 0.0;
	    temp = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		    !inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
	}
	else
	    temp = Nil;
	if (temp);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L) {
	    arg = DFLOAT_ISAREF_1(x,(SI_Long)0L);
	    arg_1 = 0.0;
	    temp = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		    !inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
	}
	else
	    temp = Nil;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

static Object string_constant;     /* "midnight" */

static Object string_constant_1;   /* "a.m." */

static Object string_constant_2;   /* "noon" */

static Object string_constant_3;   /* "p.m." */

/* SELECT-AM-OR-PM */
Object g2int_select_am_or_pm varargs_1(int, n)
{
    Object hour;
    Object minute_qm, second_qm, do_noon_or_midnight_if_applicable_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(29,14);
    INIT_ARGS_nonrelocating();
    hour = REQUIRED_ARG_nonrelocating();
    minute_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    second_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    do_noon_or_midnight_if_applicable_qm = OPTIONAL_ARG_P_nonrelocating() ?
	     OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (IFIX(hour) < (SI_Long)12L) {
	temp = do_noon_or_midnight_if_applicable_qm ? (IFIX(hour) == 
		(SI_Long)0L && g2int_null_or_zero_p(minute_qm) && 
		g2int_null_or_zero_p(second_qm) ? string_constant : Nil) : Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(string_constant_1);
    }
    else {
	temp = do_noon_or_midnight_if_applicable_qm ? (IFIX(hour) == 
		(SI_Long)12L && g2int_null_or_zero_p(minute_qm) && 
		g2int_null_or_zero_p(second_qm) ? string_constant_2 : Nil) 
		: Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(string_constant_3);
    }
}

static Object string_constant_4;   /* "Mon" */

static Object string_constant_5;   /* "Tue" */

static Object string_constant_6;   /* "Wed" */

static Object string_constant_7;   /* "Thu" */

static Object string_constant_8;   /* "Fri" */

static Object string_constant_9;   /* "Sat" */

static Object string_constant_10;  /* "Sun" */

/* SELECT-DAY-OF-WEEK-STRING */
Object g2int_select_day_of_week_string(day_of_week_index)
    Object day_of_week_index;
{
    x_note_fn_call(29,15);
    if ( !(FIXNUMP(day_of_week_index) && FIXNUM_LE(FIX((SI_Long)-128L),
	    day_of_week_index) && FIXNUM_LE(day_of_week_index,
	    FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(day_of_week_index)) {
	  case 0:
	    return VALUES_1(string_constant_4);
	  case 1:
	    return VALUES_1(string_constant_5);
	  case 2:
	    return VALUES_1(string_constant_6);
	  case 3:
	    return VALUES_1(string_constant_7);
	  case 4:
	    return VALUES_1(string_constant_8);
	  case 5:
	    return VALUES_1(string_constant_9);
	  case 6:
	    return VALUES_1(string_constant_10);
	  default:
	    return VALUES_1(Nil);
	}
}

static Object string_constant_11;  /* "Jan" */

static Object string_constant_12;  /* "Feb" */

static Object string_constant_13;  /* "Mar" */

static Object string_constant_14;  /* "Apr" */

static Object string_constant_15;  /* "May" */

static Object string_constant_16;  /* "Jun" */

static Object string_constant_17;  /* "Jul" */

static Object string_constant_18;  /* "Aug" */

static Object string_constant_19;  /* "Sep" */

static Object string_constant_20;  /* "Oct" */

static Object string_constant_21;  /* "Nov" */

static Object string_constant_22;  /* "Dec" */

/* SELECT-MONTH-STRING */
Object g2int_select_month_string(month_index)
    Object month_index;
{
    x_note_fn_call(29,16);
    if ( !(FIXNUMP(month_index) && FIXNUM_LE(FIX((SI_Long)-128L),
	    month_index) && FIXNUM_LE(month_index,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(month_index)) {
	  case 1:
	    return VALUES_1(string_constant_11);
	  case 2:
	    return VALUES_1(string_constant_12);
	  case 3:
	    return VALUES_1(string_constant_13);
	  case 4:
	    return VALUES_1(string_constant_14);
	  case 5:
	    return VALUES_1(string_constant_15);
	  case 6:
	    return VALUES_1(string_constant_16);
	  case 7:
	    return VALUES_1(string_constant_17);
	  case 8:
	    return VALUES_1(string_constant_18);
	  case 9:
	    return VALUES_1(string_constant_19);
	  case 10:
	    return VALUES_1(string_constant_20);
	  case 11:
	    return VALUES_1(string_constant_21);
	  case 12:
	    return VALUES_1(string_constant_22);
	  default:
	    return VALUES_1(Nil);
	}
}

static Object string_constant_23;  /* "~a~d:~a~d" */

static Object string_constant_24;  /* "0" */

static Object string_constant_25;  /* "" */

/* PRINT-MINUTE-AND-SECOND */
Object g2int_print_minute_and_second(minute,second_1)
    Object minute, second_1;
{
    x_note_fn_call(29,17);
    return g2int_tformat(5,string_constant_23,IFIX(minute) < (SI_Long)10L ?
	     string_constant_24 : string_constant_25,minute,IFIX(second_1) 
	    < (SI_Long)10L ? string_constant_24 : string_constant_25,second_1);
}

/* PRINT-HOUR-AND-MINUTE */
Object g2int_print_hour_and_minute(hour,minute)
    Object hour, minute;
{
    Object temp_1;
    SI_Long temp;

    x_note_fn_call(29,18);
    if (IFIX(hour) == (SI_Long)0L || IFIX(hour) > (SI_Long)12L) {
	temp = IFIX(hour) - (SI_Long)12L;
	temp_1 = FIX(ABS(temp));
    }
    else
	temp_1 = hour;
    return g2int_print_relative_hours_and_minutes(temp_1,minute);
}

static Object string_constant_26;  /* "~d:~a~d" */

/* PRINT-RELATIVE-HOURS-AND-MINUTES */
Object g2int_print_relative_hours_and_minutes(hours,minutes)
    Object hours, minutes;
{
    x_note_fn_call(29,19);
    return g2int_tformat(4,string_constant_26,hours,IFIX(minutes) < 
	    (SI_Long)10L ? string_constant_24 : string_constant_25,minutes);
}

static Object string_constant_27;  /* "~d~a,~a" */

/* PRINT-DAY-OF-WEEK-AND-HOUR */
Object g2int_print_day_of_week_and_hour(day_of_week,hour)
    Object day_of_week, hour;
{
    Object temp_1, temp_2;
    SI_Long temp;

    x_note_fn_call(29,20);
    if (IFIX(hour) == (SI_Long)0L || IFIX(hour) > (SI_Long)12L) {
	temp = IFIX(hour) - (SI_Long)12L;
	temp_1 = FIX(ABS(temp));
    }
    else
	temp_1 = hour;
    temp_2 = g2int_select_am_or_pm(1,hour);
    return g2int_tformat(4,string_constant_27,temp_1,temp_2,
	    g2int_select_day_of_week_string(day_of_week));
}

static Object string_constant_28;  /* "~d h." */

/* PRINT-RELATIVE-HOURS */
Object g2int_print_relative_hours(hours)
    Object hours;
{
    x_note_fn_call(29,21);
    return g2int_tformat(2,string_constant_28,hours);
}

static Object string_constant_29;  /* "~d ~a" */

/* PRINT-MONTH-AND-DATE */
Object g2int_print_month_and_date(month,date)
    Object month, date;
{
    x_note_fn_call(29,22);
    return g2int_tformat(3,string_constant_29,date,
	    g2int_select_month_string(month));
}

static Object string_constant_30;  /* "~d d." */

/* PRINT-RELATIVE-DAYS */
Object g2int_print_relative_days(days)
    Object days;
{
    x_note_fn_call(29,23);
    return g2int_tformat(2,string_constant_30,days);
}

static Object string_constant_31;  /* "~a ~a~d" */

/* PRINT-MONTH-AND-YEAR */
Object g2int_print_month_and_year(month,year)
    Object month, year;
{
    Object temp;

    x_note_fn_call(29,24);
    temp = g2int_select_month_string(month);
    return g2int_tformat(4,string_constant_31,temp,IFIX(year) < 
	    (SI_Long)10L ? string_constant_24 : string_constant_25,
	    mod(year,FIX((SI_Long)100L)));
}

static Object string_constant_32;  /* "~d w." */

/* PRINT-RELATIVE-WEEKS */
Object g2int_print_relative_weeks(weeks)
    Object weeks;
{
    x_note_fn_call(29,25);
    return g2int_tformat(2,string_constant_32,weeks);
}

static Object Qg2int_wide_string;  /* wide-string */

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object array_constant;      /* # */

static Object string_constant_33;  /* ", " */

static Object string_constant_34;  /* ", and " */

static Object string_constant_35;  /* " and " */

static Object array_constant_1;    /* # */

static Object list_constant_3;     /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

/* PRINT-RELATIVE-TIME */
Object g2int_print_relative_time(number_of_seconds)
    Object number_of_seconds;
{
    Object temp, schar_arg_2, schar_new_value, ab_loop_list_, singular_unit;
    Object ab_loop_list__1, plural_unit, ab_loop_list__2, ab_loop_list__3;
    Object temp_2;
    SI_Long thing, positive_number_of_seconds, remainder_1, quotient, how_many;
    SI_Long so_far, divisor, remainder_2, ab_loopvar_, temp_1;
    double float_number_of_seconds, arg, arg_1, positive_number_of_seconds_1;
    double remainder_3, float_divisor, remainder_4, float_quotient;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(29,26);
    if (FIXNUMP(number_of_seconds)) {
	if (IFIX(number_of_seconds) < (SI_Long)0L) {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = (SI_Long)45L;
		g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = (SI_Long)45L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	    positive_number_of_seconds = 
		    IFIX(FIXNUM_NEGATE(number_of_seconds));
	}
	else
	    positive_number_of_seconds = IFIX(number_of_seconds);
	remainder_1 = positive_number_of_seconds;
	quotient = (SI_Long)0L;
	how_many = (SI_Long)0L;
	so_far = (SI_Long)0L;
	divisor = (SI_Long)0L;
	ab_loop_list_ = list_constant;
	singular_unit = Nil;
	ab_loop_list__1 = list_constant_1;
	plural_unit = Nil;
	ab_loop_list__2 = list_constant_2;
	if (positive_number_of_seconds == (SI_Long)0L) {
	    g2int_twrite_beginning_of_wide_string(array_constant,
		    FIX((SI_Long)9L));
	    goto end_loop;
	}
	remainder_2 = positive_number_of_seconds;
	divisor = (SI_Long)0L;
	ab_loop_list__3 = list_constant;
	ab_loopvar_ = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(ab_loop_list__3))
	    goto end_loop_1;
	divisor = IFIX(M_CAR(ab_loop_list__3));
	ab_loop_list__3 = M_CDR(ab_loop_list__3);
	temp_1 = remainder_2 / divisor;
	quotient = temp_1;
	temp_1 = remainder_2 % divisor;
	remainder_2 = temp_1;
	if (quotient > (SI_Long)0L)
	    ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	goto next_loop;
      end_loop_1:
	how_many = ab_loopvar_;
	goto end;
	how_many = IFIX(Qnil);
      end:;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	divisor = IFIX(M_CAR(ab_loop_list_));
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	singular_unit = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop;
	plural_unit = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	temp_1 = remainder_1 / divisor;
	quotient = temp_1;
	temp_1 = remainder_1 % divisor;
	remainder_1 = temp_1;
	if (quotient > (SI_Long)0L) {
	    so_far = so_far + (SI_Long)1L;
	    g2int_twrite_positive_fixnum(FIX(quotient));
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = (SI_Long)32L;
		g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = (SI_Long)32L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	    g2int_twrite_symbol(1,quotient == (SI_Long)1L ? singular_unit :
		     plural_unit);
	    if ( !(so_far == how_many)) {
		if (how_many > (SI_Long)2L && how_many > so_far + (SI_Long)1L)
		    temp_2 = string_constant_33;
		else if (how_many > (SI_Long)2L)
		    temp_2 = string_constant_34;
		else
		    temp_2 = string_constant_35;
		g2int_twrite_general_string(temp_2);
	    }
	}
	goto next_loop_1;
      end_loop:;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(number_of_seconds) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_seconds)) == 
	    (SI_Long)1L && 
	    g2int_nanp(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(number_of_seconds,
	    (SI_Long)0L))) || FLOATP(number_of_seconds) && 
	    g2int_nanp(number_of_seconds))
	g2int_twrite_beginning_of_wide_string(array_constant_1,
		FIX((SI_Long)3L));
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(number_of_seconds) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_seconds)) == 
	    (SI_Long)1L || FLOATP(number_of_seconds)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number_of_seconds) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_seconds)) == 
		    (SI_Long)1L)
		float_number_of_seconds = 
			DFLOAT_ISAREF_1(number_of_seconds,(SI_Long)0L);
	    else
		float_number_of_seconds = 
			DOUBLE_FLOAT_TO_DOUBLE(number_of_seconds);
	    arg = float_number_of_seconds;
	    arg_1 = 0.0;
	    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
		    thing = (SI_Long)45L;
		    g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			    CHAR_CODE(FIX(thing)) : FIX(thing));
		}
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    thing = (SI_Long)45L;
		    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			    CHAR_CODE(FIX(thing)) : FIX(thing));
		    SET_SCHAR(temp,schar_arg_2,schar_new_value);
		    temp = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp;
		}
		positive_number_of_seconds_1 =  - float_number_of_seconds;
	    }
	    else
		positive_number_of_seconds_1 = float_number_of_seconds;
	    remainder_3 = positive_number_of_seconds_1;
	    quotient = (SI_Long)0L;
	    how_many = (SI_Long)0L;
	    so_far = (SI_Long)0L;
	    divisor = (SI_Long)0L;
	    ab_loop_list_ = list_constant_3;
	    float_divisor = 0.0;
	    singular_unit = Nil;
	    ab_loop_list__1 = list_constant_1;
	    plural_unit = Nil;
	    ab_loop_list__2 = list_constant_2;
	    arg = positive_number_of_seconds_1;
	    arg_1 = 0.0;
	    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		g2int_twrite_beginning_of_wide_string(array_constant_2,
			FIX((SI_Long)11L));
		goto end_1;
	    }
	    remainder_4 = positive_number_of_seconds_1;
	    float_quotient = 0.0;
	    divisor = (SI_Long)0L;
	    ab_loop_list__3 = list_constant;
	    float_divisor = 0.0;
	    ab_loopvar_ = (SI_Long)0L;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__3))
		goto end_loop_2;
	    divisor = IFIX(M_CAR(ab_loop_list__3));
	    ab_loop_list__3 = M_CDR(ab_loop_list__3);
	    float_divisor = (double)divisor;
	    if (divisor == (SI_Long)1L)
		float_quotient = remainder_4;
	    else
		float_quotient = inline_ffloor_1(remainder_4 / float_divisor);
	    remainder_4 = remainder_4 - float_quotient * float_divisor;
	    arg = float_quotient;
	    arg_1 = 0.0;
	    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	    goto next_loop_2;
	  end_loop_2:
	    how_many = ab_loopvar_;
	    goto end_2;
	    how_many = IFIX(Qnil);
	  end_2:;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    divisor = IFIX(M_CAR(ab_loop_list_));
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    float_divisor = (double)divisor;
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_3;
	    singular_unit = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_3;
	    plural_unit = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    quotient = inline_floor_1(remainder_3 / float_divisor);
	    remainder_3 = remainder_3 - (double)quotient * float_divisor;
	    if (quotient > (SI_Long)0L) {
		so_far = so_far + (SI_Long)1L;
		g2int_twrite_positive_fixnum(FIX(quotient));
		if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
		    thing = (SI_Long)32L;
		    g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			    CHAR_CODE(FIX(thing)) : FIX(thing));
		}
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    thing = (SI_Long)32L;
		    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			    CHAR_CODE(FIX(thing)) : FIX(thing));
		    SET_SCHAR(temp,schar_arg_2,schar_new_value);
		    temp = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp;
		}
		g2int_twrite_symbol(1,quotient == (SI_Long)1L ? 
			singular_unit : plural_unit);
		if ( !(so_far == how_many)) {
		    if (how_many > (SI_Long)2L && how_many > so_far + 
			    (SI_Long)1L)
			temp_2 = string_constant_33;
		    else if (how_many > (SI_Long)2L)
			temp_2 = string_constant_34;
		    else
			temp_2 = string_constant_35;
		    g2int_twrite_general_string(temp_2);
		}
	    }
	    goto next_loop_3;
	  end_loop_3:
	    arg = remainder_3;
	    arg_1 = 0.0;
	    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		g2int_write_floating_point_number_simple_c_format(1,
			DOUBLE_TO_DOUBLE_FLOAT(remainder_3));
		g2int_twrite_beginning_of_wide_string(array_constant_3,
			FIX((SI_Long)8L));
	    }
	  end_1:;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	g2int_twrite_beginning_of_wide_string(array_constant_4,
		FIX((SI_Long)22L));
    return VALUES_1(Nil);
}

/* PRINT-DECODED-TIME */
Object g2int_print_decoded_time(seconds_qm,minutes,hours,day,month,year)
    Object seconds_qm, minutes, hours, day, month, year;
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long thing;

    x_note_fn_call(29,27);
    g2int_print_decoded_date(day,month,year);
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = (SI_Long)32L;
	g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = (SI_Long)32L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp;
    }
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = (SI_Long)32L;
	g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = (SI_Long)32L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp;
    }
    return g2int_print_decoded_time_of_day(seconds_qm,minutes,hours);
}

/* PRINT-DECODED-DATE */
Object g2int_print_decoded_date(day,month,year)
    Object day, month, year;
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long thing;

    x_note_fn_call(29,28);
    g2int_twrite_positive_fixnum(day);
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = (SI_Long)32L;
	g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = (SI_Long)32L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp;
    }
    g2int_twrite_general_string(g2int_select_month_string(month));
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = (SI_Long)32L;
	g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = (SI_Long)32L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp;
    }
    return g2int_twrite_positive_fixnum(year);
}

/* PRINT-DECODED-TIME-OF-DAY */
Object g2int_print_decoded_time_of_day(seconds_qm,minutes,hours)
    Object seconds_qm, minutes, hours;
{
    Object temp_1, temp_2, schar_arg_2, schar_new_value;
    SI_Long temp, thing;
    double seconds, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(29,29);
    if (IFIX(hours) == (SI_Long)0L || IFIX(hours) > (SI_Long)12L) {
	temp = IFIX(hours) - (SI_Long)12L;
	temp_1 = FIX(ABS(temp));
    }
    else
	temp_1 = hours;
    g2int_twrite_positive_fixnum(temp_1);
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = (SI_Long)58L;
	g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_2 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = (SI_Long)58L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_2;
    }
    if (IFIX(minutes) < (SI_Long)10L) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = (SI_Long)48L;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)48L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    g2int_twrite_positive_fixnum(minutes);
    if (seconds_qm) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = (SI_Long)58L;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)58L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
	if (FIXNUMP(seconds_qm)) {
	    if (IFIX(seconds_qm) < (SI_Long)10L) {
		if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
		    thing = (SI_Long)48L;
		    g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			    CHAR_CODE(FIX(thing)) : FIX(thing));
		}
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp_2 = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    thing = (SI_Long)48L;
		    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			    CHAR_CODE(FIX(thing)) : FIX(thing));
		    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		    temp_2 = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp_2;
		}
	    }
	    g2int_twrite_positive_fixnum(seconds_qm);
	}
	else if (FLOATP(seconds_qm) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == (SI_Long)1L) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
			(SI_Long)1L)
		    seconds = DFLOAT_ISAREF_1(seconds_qm,(SI_Long)0L);
		else
		    seconds = DOUBLE_FLOAT_TO_DOUBLE(seconds_qm);
		arg = seconds;
		arg_1 = 10.0;
		if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing = (SI_Long)48L;
			g2int_twrite_wide_character(CHARACTERP(FIX(thing)) 
				? CHAR_CODE(FIX(thing)) : FIX(thing));
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp_2 = G2int_current_gensym_string;
			schar_arg_2 = 
				G2int_fill_pointer_for_current_gensym_string;
			thing = (SI_Long)48L;
			schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) 
				? CHAR_CODE(FIX(thing)) : FIX(thing));
			SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp_2;
		    }
		}
		g2int_write_floating_point_number(7,
			DOUBLE_TO_DOUBLE_FLOAT(seconds),FIX((SI_Long)2L),
			FIX((SI_Long)6L),FIX((SI_Long)8L),T,Nil,Nil);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
    }
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = (SI_Long)32L;
	g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_2 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = (SI_Long)32L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_2;
    }
    return g2int_twrite_general_string(g2int_select_am_or_pm(4,hours,
	    minutes,seconds_qm,Nil));
}

static Object string_constant_36;  /* "Copyright ~c 1986 - ~d Gensym Corporation.~%" */

static Object array_constant_5;    /* # */

/* COPYRIGHT-BOILERPLATE-LINES-OF-TEXT-1 */
Object g2int_copyright_boilerplate_lines_of_text_1()
{
    x_note_fn_call(29,30);
    return g2int_gensym_list_2(g2int_tformat_text_string(3,
	    string_constant_36,FIX((SI_Long)169L),
	    G2int_year_at_compilation_time),array_constant_5);
}

Object G2int_copyright_boilerplate_lines_of_text_1 = UNBOUND;

Object G2int_disclaimer_for_release_quality_software = UNBOUND;

Object G2int_disclaimer_for_licensing_and_authorization = UNBOUND;

Object G2int_restricted_rights_legend = UNBOUND;

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

static Object array_constant_14;   /* # */

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

/* COPYRIGHT-BOILERPLATE-LINES-OF-TEXT-2 */
Object g2int_copyright_boilerplate_lines_of_text_2()
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(29,31);
    gensymed_symbol = g2int_make_gensym_list_1(FIX((SI_Long)17L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = array_constant_6;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_7;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_8;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_9;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_9;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_10;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_11;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_12;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_13;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_14;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_9;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_9;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_15;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_16;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_17;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_18;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = array_constant_19;
    return VALUES_1(gensymed_symbol);
}

Object G2int_copyright_boilerplate_lines_of_text_2 = UNBOUND;

/* MAKE-COPYRIGHT-BOILERPLATE-LINES-OF-TEXT-FOR-TW */
Object g2int_make_copyright_boilerplate_lines_of_text_for_tw()
{
    Object temp;

    x_note_fn_call(29,32);
    temp = 
	    g2int_copy_list_using_gensym_conses_1(G2int_copyright_boilerplate_lines_of_text_1);
    return VALUES_1(nconc2(temp,
	    nconc2(g2int_gensym_list_2(array_constant_9,array_constant_9),
	    G2int_copyright_boilerplate_lines_of_text_2)));
}

void times_INIT()
{
    Object list_constant_10, Qg2int_times;
    Object Qg2int_copyright_boilerplate_lines_of_text_2, Kfuncall, AB_package;
    Object list_constant_5, list_constant_9, list_constant_8, list_constant_7;
    Object list_constant_6, Qg2int_copyright_boilerplate_lines_of_text_1;
    Object Qg2int_seconds, Qg2int_minutes, Qg2int_hours, Qg2int_days;
    Object Qg2int_weeks, Qg2int_minute, Qg2int_hour, Qg2int_day, Qg2int_week;
    Object Qg2int_seconds_per_day, list_constant_4;
    Object Qg2int_days_before_this_month, float_constant;
    Object Qg2int_seconds_from_1900_to_1970;

    x_note_fn_call(29,33);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_seconds_from_1900_to_1970 = 
	    STATIC_SYMBOL("SECONDS-FROM-1900-TO-1970",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_seconds_from_1900_to_1970,
	    G2int_seconds_from_1900_to_1970);
    float_constant = STATIC_FLOAT(2.2089888E+9);
    SET_SYMBOL_VALUE(Qg2int_seconds_from_1900_to_1970,float_constant);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_days_before_this_month = STATIC_SYMBOL("DAYS-BEFORE-THIS-MONTH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_days_before_this_month,
	    G2int_days_before_this_month);
    list_constant_4 = STATIC_LIST((SI_Long)13L,FIX((SI_Long)0L),
	    FIX((SI_Long)31L),FIX((SI_Long)59L),FIX((SI_Long)90L),
	    FIX((SI_Long)120L),FIX((SI_Long)151L),FIX((SI_Long)181L),
	    FIX((SI_Long)212L),FIX((SI_Long)243L),FIX((SI_Long)273L),
	    FIX((SI_Long)304L),FIX((SI_Long)334L),FIX((SI_Long)365L));
    SET_SYMBOL_VALUE(Qg2int_days_before_this_month,list_constant_4);
    Qg2int_seconds_per_day = STATIC_SYMBOL("SECONDS-PER-DAY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_seconds_per_day,FIX((SI_Long)86400L));
    if (G2int_unix_time_offset_was_computedqm == UNBOUND)
	G2int_unix_time_offset_was_computedqm = Nil;
    if (G2int_unix_time_offset_for_encoding == UNBOUND)
	G2int_unix_time_offset_for_encoding = Nil;
    if (G2int_year_at_compilation_time == UNBOUND)
	G2int_year_at_compilation_time = FIX((SI_Long)2017L);
    string_constant = STATIC_STRING("midnight");
    string_constant_1 = STATIC_STRING("a.m.");
    string_constant_2 = STATIC_STRING("noon");
    string_constant_3 = STATIC_STRING("p.m.");
    string_constant_4 = STATIC_STRING("Mon");
    string_constant_5 = STATIC_STRING("Tue");
    string_constant_6 = STATIC_STRING("Wed");
    string_constant_7 = STATIC_STRING("Thu");
    string_constant_8 = STATIC_STRING("Fri");
    string_constant_9 = STATIC_STRING("Sat");
    string_constant_10 = STATIC_STRING("Sun");
    string_constant_11 = STATIC_STRING("Jan");
    string_constant_12 = STATIC_STRING("Feb");
    string_constant_13 = STATIC_STRING("Mar");
    string_constant_14 = STATIC_STRING("Apr");
    string_constant_15 = STATIC_STRING("May");
    string_constant_16 = STATIC_STRING("Jun");
    string_constant_17 = STATIC_STRING("Jul");
    string_constant_18 = STATIC_STRING("Aug");
    string_constant_19 = STATIC_STRING("Sep");
    string_constant_20 = STATIC_STRING("Oct");
    string_constant_21 = STATIC_STRING("Nov");
    string_constant_22 = STATIC_STRING("Dec");
    string_constant_23 = STATIC_STRING("~a~d:~a~d");
    string_constant_24 = STATIC_STRING("0");
    string_constant_25 = STATIC_STRING("");
    string_constant_26 = STATIC_STRING("~d:~a~d");
    string_constant_27 = STATIC_STRING("~d~a,~a");
    string_constant_28 = STATIC_STRING("~d h.");
    string_constant_29 = STATIC_STRING("~d ~a");
    string_constant_30 = STATIC_STRING("~d d.");
    string_constant_31 = STATIC_STRING("~a ~a~d");
    string_constant_32 = STATIC_STRING("~d w.");
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant = STATIC_LIST((SI_Long)5L,FIX((SI_Long)604800L),
	    FIX((SI_Long)86400L),FIX((SI_Long)3600L),FIX((SI_Long)60L),
	    FIX((SI_Long)1L));
    Qg2int_week = STATIC_SYMBOL("WEEK",AB_package);
    Qg2int_day = STATIC_SYMBOL("DAY",AB_package);
    Qg2int_hour = STATIC_SYMBOL("HOUR",AB_package);
    Qg2int_minute = STATIC_SYMBOL("MINUTE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)5L,Qg2int_week,Qg2int_day,
	    Qg2int_hour,Qg2int_minute,Qsecond);
    Qg2int_weeks = STATIC_SYMBOL("WEEKS",AB_package);
    Qg2int_days = STATIC_SYMBOL("DAYS",AB_package);
    Qg2int_hours = STATIC_SYMBOL("HOURS",AB_package);
    Qg2int_minutes = STATIC_SYMBOL("MINUTES",AB_package);
    Qg2int_seconds = STATIC_SYMBOL("SECONDS",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)5L,Qg2int_weeks,Qg2int_days,
	    Qg2int_hours,Qg2int_minutes,Qg2int_seconds);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    string_constant_33 = STATIC_STRING(", ");
    string_constant_34 = STATIC_STRING(", and ");
    string_constant_35 = STATIC_STRING(" and ");
    array_constant_1 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    list_constant_3 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)604800L),
	    FIX((SI_Long)86400L),FIX((SI_Long)3600L),FIX((SI_Long)60L));
    array_constant_2 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)57344L);
    string_constant_36 = 
	    STATIC_STRING("Copyright ~c 1986 - ~d Gensym Corporation.~%");
    array_constant_5 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)57344L);
    Qg2int_copyright_boilerplate_lines_of_text_1 = 
	    STATIC_SYMBOL("COPYRIGHT-BOILERPLATE-LINES-OF-TEXT-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_copyright_boilerplate_lines_of_text_1,
	    STATIC_FUNCTION(g2int_copyright_boilerplate_lines_of_text_1,
	    NIL,FALSE,0,0));
    SET_SYMBOL_VALUE_LOCATION(Qg2int_copyright_boilerplate_lines_of_text_1,
	    G2int_copyright_boilerplate_lines_of_text_1);
    Qg2int_times = STATIC_SYMBOL("TIMES",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_copyright_boilerplate_lines_of_text_1);
    g2int_record_system_variable(Qg2int_copyright_boilerplate_lines_of_text_1,
	    Qg2int_times,list_constant_6,Qnil,Qnil,Qnil,Qnil);
    array_constant_6 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)33L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)36L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)37L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)41L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)42L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)44L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)45L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)46L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)47L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)49L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)50L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)51L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)52L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)53L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)54L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)55L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)56L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)57L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)58L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)59L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)60L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)61L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)62L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)63L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)64L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)78L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)79L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)36L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)37L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)40L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)41L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)42L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)43L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)44L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)45L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)46L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)47L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)48L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)49L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)50L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)51L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)52L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)53L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)54L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)55L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)56L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)57L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)58L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)59L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)60L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)61L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)62L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)63L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)64L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)65L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)66L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)78L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)79L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)27L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)35L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)37L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)38L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)39L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)41L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)42L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)43L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)46L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)47L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)48L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)49L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)50L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)54L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)55L,(SI_Long)57344L);
    list_constant_7 = STATIC_LIST((SI_Long)3L,array_constant_6,
	    array_constant_7,array_constant_8);
    G2int_disclaimer_for_release_quality_software = list_constant_7;
    array_constant_10 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)27L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)29L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)35L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)37L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)39L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)40L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)41L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)42L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)43L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)44L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)45L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)46L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)47L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)48L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)49L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)50L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)51L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)52L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)53L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)54L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)56L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)57L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)58L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)59L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)60L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)61L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)62L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)63L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)64L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)65L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)66L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)67L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)68L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)69L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)78L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)79L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)29L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)33L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)34L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)37L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)38L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)39L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)41L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)44L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)45L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)46L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)47L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)49L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)51L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)52L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)53L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)54L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)55L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)56L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)57L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)58L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)59L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)60L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)61L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)62L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)63L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)64L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)65L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)66L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)67L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)68L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)69L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)78L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)79L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)25L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)29L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)32L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)33L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)38L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)40L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)41L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)42L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)43L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)46L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)47L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)48L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)49L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)50L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)51L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)52L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)53L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)54L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)55L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)56L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)57L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)58L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)59L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)60L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)61L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)62L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)63L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)64L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)65L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)66L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)67L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)68L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)69L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)70L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)78L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)79L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)24L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)26L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)28L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)31L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)34L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)37L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)39L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)40L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)42L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)44L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)45L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)46L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)47L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)48L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)49L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)50L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)51L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)52L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)53L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)54L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)56L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)57L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)58L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)59L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)60L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)61L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)62L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)63L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)64L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)65L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)66L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)67L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)68L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)69L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)70L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)78L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)79L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)20L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)24L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)31L,(SI_Long)57344L);
    list_constant_8 = STATIC_LIST((SI_Long)5L,array_constant_10,
	    array_constant_11,array_constant_12,array_constant_13,
	    array_constant_14);
    G2int_disclaimer_for_licensing_and_authorization = list_constant_8;
    array_constant_15 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)16L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)17L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)18L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)19L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)20L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)21L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)24L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)25L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)27L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)28L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)29L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)30L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)31L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)32L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)33L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)35L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)38L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)40L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)41L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)42L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)43L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)44L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)45L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)46L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)47L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)48L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)49L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)50L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)51L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)52L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)53L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)54L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)55L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)56L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)57L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)58L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)59L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)60L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)61L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)62L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)63L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)64L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)65L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)66L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)67L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)68L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)69L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)78L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)79L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)10L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)19L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)20L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)21L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)23L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)29L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)33L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)35L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)37L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)39L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)40L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)41L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)42L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)43L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)45L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)46L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)47L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)49L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)51L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)52L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)53L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)54L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)55L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)56L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)57L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)58L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)59L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)60L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)61L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)62L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)63L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)64L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)65L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)66L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)67L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)68L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)69L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)78L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)79L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)20L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)27L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)30L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)32L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)33L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)36L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)37L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)38L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)40L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)41L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)42L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)43L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)45L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)46L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)47L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)49L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)51L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)52L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)53L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)54L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)56L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)57L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)58L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)59L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)60L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)61L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)62L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)63L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)64L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)65L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)78L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)79L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)16L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)17L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)18L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)19L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)20L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)21L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)24L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)25L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)26L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)27L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)28L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)30L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)34L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)35L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)37L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)39L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)40L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)41L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)42L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)43L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)44L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)45L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)46L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)47L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)49L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)51L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)52L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)53L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)54L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)55L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)56L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)57L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)58L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)59L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)60L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)61L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)62L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)63L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)64L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)65L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)66L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)67L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)68L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)69L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)70L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)71L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)72L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)78L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)79L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)112L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)25L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)27L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)28L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)33L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)34L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)35L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)36L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)38L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)39L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)40L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)41L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)42L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)43L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)44L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)46L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)47L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)49L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)50L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)51L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)52L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)53L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)54L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)55L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)56L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)57L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)58L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)59L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)60L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)61L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)62L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)63L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)64L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)65L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)66L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)67L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)68L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)69L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)70L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)71L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)72L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)73L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)74L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)75L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)76L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)77L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)78L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)79L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)80L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)81L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)82L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)83L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)84L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)85L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)86L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)87L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)88L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)89L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)90L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)91L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)92L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)93L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)94L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)95L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)110L,(SI_Long)96L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)111L,(SI_Long)57344L);
    list_constant_9 = STATIC_LIST((SI_Long)5L,array_constant_15,
	    array_constant_16,array_constant_17,array_constant_18,
	    array_constant_19);
    G2int_restricted_rights_legend = list_constant_9;
    array_constant_9 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)8232L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    Qg2int_copyright_boilerplate_lines_of_text_2 = 
	    STATIC_SYMBOL("COPYRIGHT-BOILERPLATE-LINES-OF-TEXT-2",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_copyright_boilerplate_lines_of_text_2,
	    STATIC_FUNCTION(g2int_copyright_boilerplate_lines_of_text_2,
	    NIL,FALSE,0,0));
    SET_SYMBOL_VALUE_LOCATION(Qg2int_copyright_boilerplate_lines_of_text_2,
	    G2int_copyright_boilerplate_lines_of_text_2);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_copyright_boilerplate_lines_of_text_2);
    g2int_record_system_variable(Qg2int_copyright_boilerplate_lines_of_text_2,
	    Qg2int_times,list_constant_10,Qnil,Qnil,Qnil,Qnil);
}
