/* ostme.c
 * Input file:  os-time.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "ostme.h"


/* TIME-ZONE-IN-HOURS */
Object time_zone_in_hours()
{
    Object quotient, remainder_1;
    SI_Long local_time_zone;
    Object result;

    x_note_fn_call(10,0);
    local_time_zone = g2ext_time_zone((SI_Long)0L);
    result = chestnut_floorf_function(FIX(local_time_zone),FIX((SI_Long)60L));
    MVS_2(result,quotient,remainder_1);
    if (IFIX(remainder_1) >= (SI_Long)30L)
	return VALUES_1(FIXNUM_ADD1(quotient));
    else
	return VALUES_1(quotient);
}

/* C-GET-CURRENT-TIME-ZONE */
Object c_get_current_time_zone(buffer,buflen)
    Object buffer, buflen;
{
    Object temp;

    x_note_fn_call(10,1);
    temp = 
	    FIX(g2ext_get_current_time_zone(UBYTE_16_SARRAY_TO_USHORT_PTR(buffer),
	    IFIX(buflen)));
    return VALUES_1(temp);
}

static Object string_constant;     /* "" */

/* GET-CURRENT-TIME-ZONE */
Object get_current_time_zone()
{
    Object buffer_qm, new_length, time_zone_information_qm, temp;
    SI_Long buffer_size;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(10,2);
    SAVE_STACK();
    buffer_size = (SI_Long)64L;
    buffer_qm = make_wide_string_function(FIX(buffer_size));
    new_length = c_get_current_time_zone(buffer_qm,FIX(buffer_size));
    time_zone_information_qm = IFIX(new_length) > (SI_Long)0L ? 
	    copy_wide_string_given_length(buffer_qm,new_length) : 
	    copy_text_string(string_constant);
    temp = FIX(g2ext_time_zone((SI_Long)0L));
    SAVE_VALUES(VALUES_2(time_zone_information_qm,temp));
    reclaim_wide_string(buffer_qm);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

Object Seconds_from_1900_to_1990 = UNBOUND;

Object Global_daylight_saving_time_adjustment = UNBOUND;

static Object list_constant;       /* # */

/* MAKE-GENSYM-TIME-ARRAY */
Object make_gensym_time_array()
{
    Object temp;

    x_note_fn_call(10,3);
    temp = make_array(3,FIX((SI_Long)9L),Kelement_type,list_constant);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_time_array, Qgensym_time_array);

Object N_68_years_in_seconds = UNBOUND;

Object N_2_to_31_plus_62_years = UNBOUND;

/* GENSYM-DECODE-UNIX-TIME */
Object gensym_decode_unix_time(gensym_float_unix_time)
    Object gensym_float_unix_time;
{
    Object temp_1, temp_2, temp_3, temp_4, temp_5, temp_6, temp_7, temp_8;
    Object temp_9, seconds, minutes, hours, date, month, year, day_of_week;
    Object daylight_savings_time_p, time_zone;
    double temp, adjusted_unix_time, arg, arg_1;
    Object result;

    x_note_fn_call(10,4);
    temp = DOUBLE_FLOAT_TO_DOUBLE(gensym_float_unix_time);
    adjusted_unix_time = temp + (double)((SI_Long)60L * 
	    IFIX(Global_daylight_saving_time_adjustment));
    arg = adjusted_unix_time;
    arg_1 = 2.147483648E+9;
    if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	arg = adjusted_unix_time;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(N_2_to_31_plus_62_years);
	if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    temp = 2.147483648E+9;
	else {
	    temp = DOUBLE_FLOAT_TO_DOUBLE(N_68_years_in_seconds);
	    temp = adjusted_unix_time - temp;
	}
	g2ext_decode_unix_time(temp,
		UBYTE_16_SARRAY_TO_USHORT_PTR(Gensym_time_array));
	temp_1 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)0L));
	temp_2 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)1L));
	temp_3 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)2L));
	temp_4 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)3L));
	temp_5 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)4L));
	temp_6 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)5L) + 
		(SI_Long)1900L);
	temp_7 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)6L));
	temp_8 = UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)7L) != 
		(SI_Long)0L ? T : Nil;
	temp_9 = time_zone_in_hours();
	result = VALUES_9(temp_1,temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,
		temp_8,temp_9);
	MVS_9(result,seconds,minutes,hours,date,month,year,day_of_week,
		daylight_savings_time_p,time_zone);
	arg = adjusted_unix_time;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(N_2_to_31_plus_62_years);
	temp_8 = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) ? FIX(IFIX(year) + 
		(SI_Long)62L) : FIX(IFIX(year) + (SI_Long)68L);
	arg = adjusted_unix_time;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(N_2_to_31_plus_62_years);
	temp_9 = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) ? day_of_week : 
		chestnut_modf_function(FIXNUM_ADD1(day_of_week),
		FIX((SI_Long)7L));
	return VALUES_9(seconds,minutes,hours,date,month,temp_8,temp_9,
		daylight_savings_time_p,time_zone);
    }
    else {
	g2ext_decode_unix_time(adjusted_unix_time,
		UBYTE_16_SARRAY_TO_USHORT_PTR(Gensym_time_array));
	temp_1 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)0L));
	temp_2 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)1L));
	temp_3 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)2L));
	temp_4 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)3L));
	temp_5 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)4L));
	temp_6 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)5L) + 
		(SI_Long)1900L);
	temp_7 = FIX(UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)6L));
	temp_8 = UBYTE_16_ISAREF_1(Gensym_time_array,(SI_Long)7L) != 
		(SI_Long)0L ? T : Nil;
	temp_9 = time_zone_in_hours();
	return VALUES_9(temp_1,temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,
		temp_8,temp_9);
    }
}

void os_time_INIT()
{
    Object float_constant_1, Q2_to_31_plus_62_years, AB_package;
    Object float_constant, Q68_years_in_seconds, Qseconds_from_1900_to_1990;

    x_note_fn_call(10,5);
    SET_PACKAGE("AB");
    string_constant = STATIC_STRING("");
    AB_package = STATIC_PACKAGE("AB");
    Qseconds_from_1900_to_1990 = STATIC_SYMBOL("SECONDS-FROM-1900-TO-1990",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qseconds_from_1900_to_1990,
	    Seconds_from_1900_to_1990);
    SET_SYMBOL_VALUE(Qseconds_from_1900_to_1990,
	    ltimes(FIX((SI_Long)4838400L),FIX((SI_Long)587L)));
    Global_daylight_saving_time_adjustment = FIX((SI_Long)0L);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    if (Gensym_time_array == UNBOUND)
	Gensym_time_array = make_gensym_time_array();
    Q68_years_in_seconds = STATIC_SYMBOL("68-YEARS-IN-SECONDS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Q68_years_in_seconds,N_68_years_in_seconds);
    float_constant = STATIC_FLOAT(2.1459168E+9);
    SET_SYMBOL_VALUE(Q68_years_in_seconds,float_constant);
    Q2_to_31_plus_62_years = STATIC_SYMBOL("2-TO-31-PLUS-62-YEARS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Q2_to_31_plus_62_years,N_2_to_31_plus_62_years);
    float_constant_1 = STATIC_FLOAT(4.104011648E+9);
    SET_SYMBOL_VALUE(Q2_to_31_plus_62_years,float_constant_1);
}
