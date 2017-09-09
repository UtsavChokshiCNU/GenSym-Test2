/* sqncs2.c
 * Input file:  sequences2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "sqncs2.h"


static Object string_constant;     /* "An attempt has been made to use GSI.  GSI has not been authorized to run on this machine." */

/* RUN-GSI-FOR-RECURSIVE-DESCENT */
Object run_gsi_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,0);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_1;   /* "An attempt has been made to use GSPAN.  GSPAN has not been authorized to run on this machine." */

/* RUN-GSPAN-FOR-RECURSIVE-DESCENT */
Object run_gspan_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,1);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_1);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_2;   /* "An attempt has been made to use ICP.  ICP has not been authorized to run on this machine." */

/* RUN-ICP-FOR-RECURSIVE-DESCENT */
Object run_icp_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,2);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_2);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_3;   /* "An attempt has been made to use GFI.  GFI has not been authorized to run on this machine." */

/* RUN-GFI-FOR-RECURSIVE-DESCENT */
Object run_gfi_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,3);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_3);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_4;   /* "An attempt has been made to use KFEP.  KFEP has not been authorized to run on this machine." */

/* RUN-KFEP-FOR-RECURSIVE-DESCENT */
Object run_kfep_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,4);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_4);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_5;   /* "An attempt has been made to use CHINESE.  CHINESE has not been authorized to run on this machine." */

/* RUN-CHINESE-FOR-RECURSIVE-DESCENT */
Object run_chinese_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,5);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_5);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_6;   /* "An attempt has been made to use RUNTIME-OPTION.  RUNTIME-OPTION has not been authorized to run on this machine." */

/* RUN-RUNTIME-OPTION-FOR-RECURSIVE-DESCENT */
Object run_runtime_option_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,6);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_6);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_7;   /* "An attempt has been made to use JAPANESE.  JAPANESE has not been authorized to run on this machine." */

/* RUN-JAPANESE-FOR-RECURSIVE-DESCENT */
Object run_japanese_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,7);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_7);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_8;   /* "An attempt has been made to use NUPEC.  NUPEC has not been authorized to run on this machine." */

/* RUN-NUPEC-FOR-RECURSIVE-DESCENT */
Object run_nupec_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,8);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_8);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_9;   /* "An attempt has been made to use RESTRICTED-USE-OPTION.  RESTRICTED-USE-OPTION has not been authorized to run on this machine." */

/* RUN-RESTRICTED-USE-OPTION-FOR-RECURSIVE-DESCENT */
Object run_restricted_use_option_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,9);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_9);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_10;  /* "An attempt has been made to use EMBEDDED-OPTION.  EMBEDDED-OPTION has not been authorized to run on this machine." */

/* RUN-EMBEDDED-OPTION-FOR-RECURSIVE-DESCENT */
Object run_embedded_option_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,10);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_10);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_11;  /* "An attempt has been made to use KOREAN.  KOREAN has not been authorized to run on this machine." */

/* RUN-KOREAN-FOR-RECURSIVE-DESCENT */
Object run_korean_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,11);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_11);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_12;  /* "An attempt has been made to use G1.  G1 has not been authorized to run on this machine." */

/* RUN-G1-FOR-RECURSIVE-DESCENT */
Object run_g1_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,12);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_12);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_13;  /* "An attempt has been made to use JL.  JL has not been authorized to run on this machine." */

/* RUN-JL-FOR-RECURSIVE-DESCENT */
Object run_jl_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,13);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_13);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_14;  /* "An attempt has been made to use JP.  JP has not been authorized to run on this machine." */

/* RUN-JP-FOR-RECURSIVE-DESCENT */
Object run_jp_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,14);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_14);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_15;  /* "An attempt has been made to use AL.  AL has not been authorized to run on this machine." */

/* RUN-AL-FOR-RECURSIVE-DESCENT */
Object run_al_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,15);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_15);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

static Object string_constant_16;  /* "An attempt has been made to use ENT.  ENT has not been authorized to run on this machine." */

/* RUN-ENT-FOR-RECURSIVE-DESCENT */
Object run_ent_for_recursive_descent(x,y)
    Object x, y;
{
    x_note_fn_call(107,16);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_16);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(FIXNUM_ADD(x,y));
}

DEFINE_VARIABLE_WITH_SYMBOL(Pulse_rate_multiplier, Qpulse_rate_multiplier);

static Object array_constant;      /* # */

/* CHOOSE-PULSE-RATE-MULTIPLIER */
Object choose_pulse_rate_multiplier()
{
    x_note_fn_call(107,17);
    if ( !(FIXNUMP(Pulse_rate_multiplier) && FIXNUM_LE(FIX((SI_Long)-128L),
	    Pulse_rate_multiplier) && FIXNUM_LE(Pulse_rate_multiplier,
	    FIX((SI_Long)127L))))
	return error((SI_Long)2L,"unknown version: ~d",Pulse_rate_multiplier);
    else
	switch (INTEGER_TO_CHAR(Pulse_rate_multiplier)) {
	  case 1:
	    return VALUES_1(array_constant);
	  default:
	    return error((SI_Long)2L,"unknown version: ~d",
		    Pulse_rate_multiplier);
	}
}

DEFINE_VARIABLE_WITH_SYMBOL(Pulse_rate_options, Qpulse_rate_options);

/* COMPACT-RPC-SCRATCH-SPACE-IF-NECESSARY */
Object compact_rpc_scratch_space_if_necessary(machine_id,start_day_qm,
	    start_month_qm,start_year_qm,expiration_day_qm,
	    expiration_month_qm,expiration_year_qm,license_level_1)
    Object machine_id, start_day_qm, start_month_qm, start_year_qm;
    Object expiration_day_qm, expiration_month_qm, expiration_year_qm;
    Object license_level_1;
{
    Object start_date, end_date;
    Object result;

    x_note_fn_call(107,18);
    if (start_day_qm || start_month_qm || start_year_qm || 
	    expiration_day_qm || expiration_month_qm || expiration_year_qm) {
	result = convert_valid_date_expressions_to_universal_dates(start_day_qm,
		start_month_qm,start_year_qm,expiration_day_qm,
		expiration_month_qm,expiration_year_qm);
	MVS_2(result,start_date,end_date);
	return compact_rpc_scratch_space(machine_id,start_date,end_date,
		license_level_1);
    }
    else
	return compact_rpc_scratch_space(machine_id,Nil,Nil,license_level_1);
}

/* COMPACT-RPC-SCRATCH-SPACE */
Object compact_rpc_scratch_space(machine_id,start_date_qm,
	    expiration_date_qm,license_level_1)
    Object machine_id, start_date_qm, expiration_date_qm, license_level_1;
{
    Object code1, code2, code3, code4, temp;
    Object result;

    x_note_fn_call(107,19);
    result = scan_rpc_scratch_space(machine_id,start_date_qm,
	    expiration_date_qm,license_level_1);
    MVS_4(result,code1,code2,code3,code4);
    temp = revert_rpc_bounds_now(machine_id,code1,code2,code3,code4,
	    start_date_qm,expiration_date_qm,license_level_1);
    return VALUES_5(code1,code2,code3,code4,temp);
}

/* SCAN-RPC-SCRATCH-SPACE */
Object scan_rpc_scratch_space(machine_id,start_date,end_date,
	    authorization_level)
    Object machine_id, start_date, end_date, authorization_level;
{
    Object temp, temp_1, temp_2, temp_3;
    SI_Long i;

    x_note_fn_call(107,20);
    map_scratch_space_blocks(machine_id,start_date,end_date,
	    authorization_level);
    Random_state_array_current_pointer = FIX((SI_Long)54L);
    Random_state_array_24_pointer = FIX((SI_Long)30L);
    i = (SI_Long)1L;
  next_loop:
    if (i > (SI_Long)500L)
	goto end_loop;
    generate_large_random();
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = aref1(Random_state_array,FIX((SI_Long)0L));
    temp_1 = aref1(Random_state_array,FIX((SI_Long)1L));
    temp_2 = aref1(Random_state_array,FIX((SI_Long)2L));
    temp_3 = aref1(Random_state_array,FIX((SI_Long)3L));
    return VALUES_4(temp,temp_1,temp_2,temp_3);
}

static Object Qdevelopment;        /* development */

static Object Qdeployment;         /* deployment */

static Object Qrestricted_use_option;  /* restricted-use-option */

/* MAP-SCRATCH-SPACE-BLOCKS */
Object map_scratch_space_blocks(machine_id,start_date_qm,
	    expiration_date_qm,authorization_level)
    Object machine_id, start_date_qm, expiration_date_qm, authorization_level;
{
    Object aref_arg_1, aref_new_value, state_array_index_1, weight_qm, list_1;
    Object products_bitmask;
    SI_Long state_array_index, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(107,21);
    if ( !TRUEP(Random_state_array)) {
	if (PUSH_AREA(Dynamic_area,0))
	    Random_state_array = make_array(3,FIX((SI_Long)55L),
		    Kelement_type,Qfixnum);
	POP_AREA(0);
    }
    state_array_index = (SI_Long)0L;
  next_loop:
    if (state_array_index > (SI_Long)54L)
	goto end_loop;
    aref_arg_1 = Random_state_array;
    if ( !(FIXNUMP(Pulse_rate_multiplier) && FIXNUM_LE(FIX((SI_Long)-128L),
	    Pulse_rate_multiplier) && FIXNUM_LE(Pulse_rate_multiplier,
	    FIX((SI_Long)127L))))
	aref_new_value = Nil;
    else
	switch (INTEGER_TO_CHAR(Pulse_rate_multiplier)) {
	  case 1:
	    aref_new_value = FIX((SI_Long)87975L);
	    break;
	  default:
	    aref_new_value = Nil;
	    break;
	}
    set_aref1(aref_arg_1,FIX(state_array_index),aref_new_value);
    state_array_index = state_array_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    state_array_index_1 = FIX((SI_Long)0L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(text_string_length(machine_id));
    weight_qm = Nil;
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    weight_qm = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(machine_id,
	    i)),FIX((SI_Long)36L));
    if (weight_qm) {
	aref_arg_1 = Random_state_array;
	set_aref1(aref_arg_1,state_array_index_1,weight_qm);
	state_array_index_1 = FIXNUM_ADD1(state_array_index_1);
    }
    if (IFIX(state_array_index_1) == (SI_Long)55L)
	goto end_loop_1;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    aref_arg_1 = Random_state_array;
    set_aref1(aref_arg_1,FIX((SI_Long)54L),FIX((SI_Long)1L));
    if (start_date_qm) {
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)3L)),start_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)3L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)4L)),start_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)4L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)5L)),start_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)5L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)6L)),start_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)6L),aref_new_value);
    }
    if (expiration_date_qm) {
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)7L)),expiration_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)7L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)8L)),expiration_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)8L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)9L)),expiration_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)9L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)10L)),expiration_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)10L),aref_new_value);
    }
    if (authorization_level) {
	if ( !EQ(authorization_level,Qdevelopment)) {
	    list_1 = gensym_cons_1(EQ(authorization_level,Qdeployment) ? 
		    Qrestricted_use_option : error((SI_Long)2L,
		    "Unknown license level for a tw2: ~a",
		    authorization_level),Nil);
	    products_bitmask = sort_scheduled_priorities(list_1);
	    if (FIXNUMP(products_bitmask) && (IFIX(products_bitmask) & 
		    (SI_Long)64L) != (SI_Long)0L || 
		    FIXNUMP(products_bitmask) && (IFIX(products_bitmask) & 
		    (SI_Long)512L) != (SI_Long)0L || 
		    FIXNUMP(products_bitmask) && (IFIX(products_bitmask) & 
		    (SI_Long)1024L) != (SI_Long)0L) {
		aref_arg_1 = Random_state_array;
		aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
			FIX((SI_Long)11L)),products_bitmask);
		set_aref1(aref_arg_1,FIX((SI_Long)11L),aref_new_value);
	    }
	    return reclaim_gensym_list_1(list_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qbad_date_format;    /* bad-date-format */

/* CONVERT-VALID-DATE-EXPRESSIONS-TO-UNIVERSAL-DATES */
Object convert_valid_date_expressions_to_universal_dates(start_day_qm,
	    start_month_qm,start_year_qm,expiration_day_qm,
	    expiration_month_qm,expiration_year_qm)
    Object start_day_qm, start_month_qm, start_year_qm, expiration_day_qm;
    Object expiration_month_qm, expiration_year_qm;
{
    Object start_date_qm, expiration_date_qm;
    volatile Object start_date_list_qm;
    volatile Object end_date_list_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(107,22);
    SAVE_STACK();
    start_date_qm = Qunbound_in_protected_let;
    expiration_date_qm = Qunbound_in_protected_let;
    start_date_list_qm = Qunbound_in_protected_let;
    end_date_list_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	start_date_qm = Nil;
	expiration_date_qm = Nil;
	start_date_list_qm = gensym_list_3(start_day_qm,start_month_qm,
		start_year_qm);
	end_date_list_qm = gensym_list_3(expiration_day_qm,
		expiration_month_qm,expiration_year_qm);
	if (valid_universal_date_elements_p(start_day_qm,start_month_qm,
		start_year_qm))
	    start_date_qm = 
		    convert_input_to_universal_date(start_date_list_qm);
	if (valid_universal_date_elements_p(expiration_day_qm,
		expiration_month_qm,expiration_year_qm))
	    expiration_date_qm = 
		    convert_input_to_universal_date(end_date_list_qm);
	if ( !TRUEP(start_date_qm) ||  !TRUEP(expiration_date_qm))
	    SAVE_VALUES(VALUES_3(Nil,Nil,Qbad_date_format));
	else
	    SAVE_VALUES(VALUES_2(start_date_qm,expiration_date_qm));
    }
    POP_UNWIND_PROTECT(0);
    if (end_date_list_qm) {
	if ( !EQ(end_date_list_qm,Qunbound_in_protected_let))
	    reclaim_gensym_list_1(end_date_list_qm);
    }
    if (start_date_list_qm) {
	if ( !EQ(start_date_list_qm,Qunbound_in_protected_let))
	    reclaim_gensym_list_1(start_date_list_qm);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_17;  /* "~a~a" */

static Object Qruntime;            /* runtime */

static Object Qrestricted;         /* restricted */

static Object Qembedded;           /* embedded */

/* REVERT-RPC-BOUNDS-NOW */
Object revert_rpc_bounds_now(machine_id,code1,code2,code3,code4,
	    start_date_qm,expiration_date_qm,license_level_1)
    Object machine_id, code1, code2, code3, code4, start_date_qm;
    Object expiration_date_qm, license_level_1;
{
    Object keystring, gensymed_symbol, gensymed_symbol_1, expt_1, value;
    Object weight_qm, temp, modularized_key, t1, t2, license_multiplier, t3;
    Object t4;
    SI_Long i, ab_loop_bind_, temp_1;

    x_note_fn_call(107,23);
    keystring = tformat_text_string(3,string_constant_17,machine_id,
	    Pulse_rate_options);
    gensymed_symbol = keystring;
    gensymed_symbol_1 = New_modulus;
    expt_1 = FIX((SI_Long)1L);
    value = FIX((SI_Long)0L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_SUB1(lengthw(gensymed_symbol)));
    weight_qm = Nil;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    weight_qm = 
	    digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(gensymed_symbol,
	    i)),FIX((SI_Long)36L));
    if (weight_qm) {
	temp = value;
	temp_1 = IFIX(FIXNUM_TIMES(weight_qm,expt_1)) % 
		IFIX(gensymed_symbol_1);
	temp_1 = IFIX(FIXNUM_ADD(temp,FIX(temp_1))) % IFIX(gensymed_symbol_1);
	value = FIX(temp_1);
	temp_1 = IFIX(expt_1) * (SI_Long)36L % IFIX(gensymed_symbol_1);
	expt_1 = FIX(temp_1);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = value;
    goto end_1;
    temp = Qnil;
  end_1:;
    reclaim_text_string(keystring);
    modularized_key = temp;
    if (IFIX(code1) < (SI_Long)100L)
	code1 = FIX((SI_Long)173L + (SI_Long)477L * IFIX(code1));
    if (IFIX(code2) < (SI_Long)100L)
	code2 = FIX((SI_Long)931L + (SI_Long)73L * IFIX(code2));
    if (IFIX(code3) < (SI_Long)100L)
	code3 = FIX((SI_Long)575L + (SI_Long)637L * IFIX(code3));
    if (IFIX(code4) < (SI_Long)100L)
	code4 = FIX((SI_Long)347L + ((SI_Long)782L + IFIX(code4)));
    t1 = start_date_qm;
    if (t1);
    else
	t1 = FIX((SI_Long)0L);
    t2 = expiration_date_qm;
    if (t2);
    else
	t2 = FIX((SI_Long)0L);
    if (EQ(license_level_1,Qruntime))
	license_multiplier = code1;
    else if (EQ(license_level_1,Qrestricted))
	license_multiplier = code2;
    else if (EQ(license_level_1,Qembedded))
	license_multiplier = code3;
    else
	license_multiplier = FIX((SI_Long)0L);
    t3 = inner_multiply(license_multiplier,code1);
    t4 = inner_multiply(license_multiplier,code4);
    temp = inner_multiply(modularized_key,code1);
    temp = FIXNUM_LOGXOR(temp,inner_multiply(code2,code3));
    temp = FIXNUM_LOGXOR(temp,inner_multiply(code4,code4));
    temp = FIXNUM_LOGXOR(temp,inner_multiply(t1,t2));
    temp = FIXNUM_LOGXOR(temp,inner_multiply(t3,t4));
    return mod(temp,New_modulus);
}

static Object list_constant;       /* # */

static Object Qall_is_well;        /* all-is-well */

/* CHECK-CODE-SPACE-2 */
Object check_code_space_2()
{
    Object code1, code2, code3, code4, code5, id, s_day, s_month, s_year;
    Object e_day, e_month, e_year, level, c1, c2, c3, c4, c5, ab_loop_list_;
    Object ab_loop_desetq_, temp;
    Object result;

    x_note_fn_call(107,24);
    code1 = Nil;
    code2 = Nil;
    code3 = Nil;
    code4 = Nil;
    code5 = Nil;
    id = Nil;
    s_day = Nil;
    s_month = Nil;
    s_year = Nil;
    e_day = Nil;
    e_month = Nil;
    e_year = Nil;
    level = Nil;
    c1 = Nil;
    c2 = Nil;
    c3 = Nil;
    c4 = Nil;
    c5 = Nil;
    ab_loop_list_ = list_constant;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    temp = CAR(ab_loop_desetq_);
    id = CAR(temp);
    temp = CAR(ab_loop_desetq_);
    temp = CDR(temp);
    s_day = CAR(temp);
    temp = CAR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    s_month = CAR(temp);
    temp = CAR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    s_year = CAR(temp);
    temp = CAR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    e_day = CAR(temp);
    temp = CAR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    e_month = CAR(temp);
    temp = CAR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    e_year = CAR(temp);
    temp = CAR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    level = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CAR(temp);
    c1 = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CAR(temp);
    temp = CDR(temp);
    c2 = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CAR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    c3 = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CAR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    c4 = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CAR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    c5 = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    result = compact_rpc_scratch_space_if_necessary(id,s_day,s_month,
	    s_year,e_day,e_month,e_year,level);
    MVS_5(result,code1,code2,code3,code4,code5);
    if ( !(FIXNUM_EQ(code1,c1) && FIXNUM_EQ(code2,c2) && FIXNUM_EQ(code3,
	    c3) && FIXNUM_EQ(code4,c4)))
	error((SI_Long)1L,"failed the inner check");
    if ( !FIXNUM_EQ(code5,c5))
	error((SI_Long)1L,"falled the outer check");
    goto next_loop;
  end_loop:
    return VALUES_1(Qall_is_well);
    return VALUES_1(Qnil);
}

static Object Qno_end_date_supplied_with_start_date;  /* no-end-date-supplied-with-start-date */

static Object Qwrong_data_structure_for_temporary_interval_information;  /* wrong-data-structure-for-temporary-interval-information */

static Object Qmissing_date_information;  /* missing-date-information */

static Object Qtemp_codes_end_before_they_start;  /* temp-codes-end-before-they-start */

static Object Qtemp_codes_interval_has_ended;  /* temp-codes-interval-has-ended */

static Object Qtemp_codes_interval_not_started;  /* temp-codes-interval-not-started */

static Object Qbad_codes;          /* bad-codes */

/* DEFRAGMENT-RPC-MAPPING-TABLE */
Object defragment_rpc_mapping_table(machine_id,ok_code1,ok_code2,ok_code3,
	    ok_code4,ok_code5,start_date_sequence_qm,end_date_sequence_qm,
	    desired_authorization_level)
    Object machine_id, ok_code1, ok_code2, ok_code3, ok_code4, ok_code5;
    Object start_date_sequence_qm, end_date_sequence_qm;
    Object desired_authorization_level;
{
    Object start_date_qm, end_date_qm, error_symbol_qm, bad_date_format_qm;
    Object start_day, start_month, start_year, expiration_day;
    Object expiration_month, expiration_year, today, checksum;
    Object result;

    x_note_fn_call(107,25);
    start_date_qm = Nil;
    end_date_qm = Nil;
    error_symbol_qm = Nil;
    bad_date_format_qm = Nil;
    if (start_date_sequence_qm) {
	if ( !TRUEP(end_date_sequence_qm))
	    error_symbol_qm = Qno_end_date_supplied_with_start_date;
	if ( !TRUEP(error_symbol_qm)) {
	    if ( !(CONSP(start_date_sequence_qm) && 
		    EQ(M_CDR(start_date_sequence_qm),Qsequence) && 
		    CONSP(end_date_sequence_qm) && 
		    EQ(M_CDR(end_date_sequence_qm),Qsequence)))
		error_symbol_qm = 
			Qwrong_data_structure_for_temporary_interval_information;
	}
	if ( !TRUEP(error_symbol_qm)) {
	    start_day = evaluation_sequence_aref(start_date_sequence_qm,
		    FIX((SI_Long)0L));
	    start_month = evaluation_sequence_aref(start_date_sequence_qm,
		    FIX((SI_Long)1L));
	    start_year = evaluation_sequence_aref(start_date_sequence_qm,
		    FIX((SI_Long)2L));
	    expiration_day = evaluation_sequence_aref(end_date_sequence_qm,
		    FIX((SI_Long)0L));
	    expiration_month = 
		    evaluation_sequence_aref(end_date_sequence_qm,
		    FIX((SI_Long)1L));
	    expiration_year = 
		    evaluation_sequence_aref(end_date_sequence_qm,
		    FIX((SI_Long)2L));
	    if ( !(start_day && start_month && start_year && 
		    expiration_day && expiration_month && expiration_year))
		error_symbol_qm = Qmissing_date_information;
	    if ( !TRUEP(error_symbol_qm)) {
		result = convert_valid_date_expressions_to_universal_dates(start_day,
			start_month,start_year,expiration_day,
			expiration_month,expiration_year);
		MVS_3(result,start_date_qm,end_date_qm,bad_date_format_qm);
		if (bad_date_format_qm)
		    error_symbol_qm = bad_date_format_qm;
	    }
	    if ( !TRUEP(error_symbol_qm)) {
		today = get_universal_date();
		if (FIXNUM_LT(end_date_qm,start_date_qm))
		    error_symbol_qm = Qtemp_codes_end_before_they_start;
		else if (FIXNUM_LT(end_date_qm,today))
		    error_symbol_qm = Qtemp_codes_interval_has_ended;
		else if (FIXNUM_LT(today,start_date_qm))
		    error_symbol_qm = Qtemp_codes_interval_not_started;
	    }
	}
    }
    if (error_symbol_qm)
	return VALUES_2(Nil,error_symbol_qm);
    else {
	checksum = revert_rpc_bounds_now(machine_id,ok_code1,ok_code2,
		ok_code3,ok_code4,start_date_qm,end_date_qm,
		desired_authorization_level);
	if (FIXNUM_EQ(checksum,ok_code5))
	    return VALUES_1(T);
	else
	    return VALUES_2(Nil,Qbad_codes);
    }
}

/* PRINT-UNIVERSAL-DATE-AS-DECODED-DATE */
Object print_universal_date_as_decoded_date(universal_date_fixnum)
    Object universal_date_fixnum;
{
    Object day, month, year;
    Object result;

    x_note_fn_call(107,26);
    result = decode_universal_date(universal_date_fixnum);
    MVS_3(result,day,month,year);
    return print_decoded_date(day,month,year);
}

static Object Qnone;               /* none */

static Object array_constant_1;    /* # */

/* COMPILE-NON-NEGATIVE-INTEGER-OR-NONE-FOR-SLOT */
Object compile_non_negative_integer_or_none_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(107,27);
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
	return VALUES_1(FIX((SI_Long)0L));
    else if (IFIX(parse_result) < (SI_Long)0L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_1,
		FIX((SI_Long)42L));
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(parse_result);
}

static Object array_constant_2;    /* # */

/* WRITE-NON-NEGATIVE-INTEGER-OR-NONE-FROM-SLOT */
Object write_non_negative_integer_or_none_from_slot(non_negative_integer_or_none,
	    gensymed_symbol)
    Object non_negative_integer_or_none, gensymed_symbol;
{
    x_note_fn_call(107,28);
    if (IFIX(non_negative_integer_or_none) == (SI_Long)0L)
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)4L));
    else
	return twrite_fixnum(non_negative_integer_or_none);
}

/* PUT-EXPIRATION-DATE-WHERE-SLOT-IS-ABSENT */
Object put_expiration_date_where_slot_is_absent(frame,value)
    Object frame, value;
{
    x_note_fn_call(107,29);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Ok_modified, Qok_modified);

DEFINE_VARIABLE_WITH_SYMBOL(Ok_authorized_products, Qok_authorized_products);

DEFINE_VARIABLE_WITH_SYMBOL(Ok_expiration_date_qm, Qok_expiration_date_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Ok_authorized_packages, Qok_authorized_packages);

DEFINE_VARIABLE_WITH_SYMBOL(Ok_make_g2_secure_qm, Qok_make_g2_secure_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Ok_number_of_processes_authorized, Qok_number_of_processes_authorized);

DEFINE_VARIABLE_WITH_SYMBOL(Ok_maximum_number_of_concurrent_floating_telewindows_allowed, Qok_maximum_number_of_concurrent_floating_telewindows_allowed);

DEFINE_VARIABLE_WITH_SYMBOL(Ok_maximum_number_of_concurrent_floating_tw2_allowed, Qok_maximum_number_of_concurrent_floating_tw2_allowed);

/* WRITE-ID-OR-WHOLE-STRING?-FROM-SLOT */
Object write_id_or_whole_string_qm_from_slot(id_or_whole_string_qm,
	    gensymed_symbol)
    Object id_or_whole_string_qm, gensymed_symbol;
{
    x_note_fn_call(107,30);
    if (id_or_whole_string_qm)
	return tprin(id_or_whole_string_qm,T);
    else
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)4L));
}

static Object Qauthorized_kb_packages;  /* authorized-kb-packages */

/* COMPILE-ID-OR-WHOLE-STRING?-FOR-SLOT */
Object compile_id_or_whole_string_qm_for_slot varargs_1(int, n)
{
    Object parse_result, ok, gensymed_symbol;
    Object transformed_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(107,31);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    ok = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (text_string_p(parse_result))
	transformed_value = parse_result;
    else if (EQ(parse_result,Qnone))
	transformed_value = Nil;
    else
	transformed_value = pointer_to_first_string_in_pool_group();
    analyze_authorized_packages(get_lookup_slot_value_given_default(ok,
	    Qauthorized_kb_packages,Nil),transformed_value,ok);
    return VALUES_1(transformed_value);
}

static Object Qmachine_id;         /* machine-id */

/* PUT-MACHINE-ID */
Object put_machine_id(frame,value,gensymed_symbol)
    Object frame, value, gensymed_symbol;
{
    x_note_fn_call(107,32);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qmachine_id);
    set_lookup_slot_value_1(frame,Qmachine_id,value);
    reformat_line_from_left(frame);
    return VALUES_1(value);
}

static Object Qcode_1;             /* code-1 */

/* PUT-CODE-1 */
Object put_code_1(frame,value,gensymed_symbol)
    Object frame, value, gensymed_symbol;
{
    x_note_fn_call(107,33);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qcode_1);
    set_lookup_slot_value_1(frame,Qcode_1,value);
    reformat_line_from_left(frame);
    return VALUES_1(value);
}

static Object Qcode_2;             /* code-2 */

/* PUT-CODE-2 */
Object put_code_2(frame,value,gensymed_symbol)
    Object frame, value, gensymed_symbol;
{
    x_note_fn_call(107,34);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qcode_2);
    set_lookup_slot_value_1(frame,Qcode_2,value);
    reformat_line_from_left(frame);
    return VALUES_1(value);
}

static Object Qcode_3;             /* code-3 */

/* PUT-CODE-3 */
Object put_code_3(frame,value,gensymed_symbol)
    Object frame, value, gensymed_symbol;
{
    x_note_fn_call(107,35);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qcode_3);
    set_lookup_slot_value_1(frame,Qcode_3,value);
    reformat_line_from_left(frame);
    return VALUES_1(value);
}

static Object Qcode_4;             /* code-4 */

/* PUT-CODE-4 */
Object put_code_4(frame,value,gensymed_symbol)
    Object frame, value, gensymed_symbol;
{
    x_note_fn_call(107,36);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qcode_4);
    set_lookup_slot_value_1(frame,Qcode_4,value);
    reformat_line_from_left(frame);
    return VALUES_1(value);
}

static Object Qcode_5;             /* code-5 */

static Object Qok_slot_coordinator;  /* ok-slot-coordinator */

/* PUT-CODE-5 */
Object put_code_5(frame,value,gensymed_symbol)
    Object frame, value, gensymed_symbol;
{
    SI_Long ok_slot_coordinator_new_value;

    x_note_fn_call(107,37);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qcode_5);
    set_lookup_slot_value_1(frame,Qcode_5,value);
    if ( !TRUEP(Loading_kb_p)) {
	ok_slot_coordinator_new_value = 
		IFIX(get_lookup_slot_value_given_default(frame,
		Qok_slot_coordinator,FIX((SI_Long)0L))) | (SI_Long)1L;
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(frame,Qok_slot_coordinator);
	set_lookup_slot_value_1(frame,Qok_slot_coordinator,
		FIX(ok_slot_coordinator_new_value));
    }
    reformat_line_from_left(frame);
    return VALUES_1(value);
}

static Object Qauthorized_products;  /* authorized-products */

/* PUT-AUTHORIZED-PRODUCTS */
Object put_authorized_products(frame,value,gensymed_symbol)
    Object frame, value, gensymed_symbol;
{
    SI_Long ok_slot_coordinator_new_value, temp;

    x_note_fn_call(107,38);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qauthorized_products);
    set_lookup_slot_value_1(frame,Qauthorized_products,value);
    if ( !TRUEP(Loading_kb_p)) {
	if (value) {
	    ok_slot_coordinator_new_value = 
		    IFIX(get_lookup_slot_value_given_default(frame,
		    Qok_slot_coordinator,FIX((SI_Long)0L))) | (SI_Long)2L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qok_slot_coordinator);
	    set_lookup_slot_value_1(frame,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
	else {
	    temp = IFIX(get_lookup_slot_value_given_default(frame,
		    Qok_slot_coordinator,FIX((SI_Long)0L)));
	    ok_slot_coordinator_new_value = temp &  ~(SI_Long)2L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qok_slot_coordinator);
	    set_lookup_slot_value_1(frame,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
    }
    reformat_line_from_left(frame);
    return VALUES_1(value);
}

static Object Qexpiration_date_qm;  /* expiration-date? */

/* PUT-EXPIRATION-DATE? */
Object put_expiration_date_qm(frame,value,gensymed_symbol)
    Object frame, value, gensymed_symbol;
{
    SI_Long ok_slot_coordinator_new_value, temp;

    x_note_fn_call(107,39);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qexpiration_date_qm);
    set_lookup_slot_value_1(frame,Qexpiration_date_qm,value);
    if ( !TRUEP(Loading_kb_p)) {
	if (value) {
	    ok_slot_coordinator_new_value = 
		    IFIX(get_lookup_slot_value_given_default(frame,
		    Qok_slot_coordinator,FIX((SI_Long)0L))) | (SI_Long)4L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qok_slot_coordinator);
	    set_lookup_slot_value_1(frame,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
	else {
	    temp = IFIX(get_lookup_slot_value_given_default(frame,
		    Qok_slot_coordinator,FIX((SI_Long)0L)));
	    ok_slot_coordinator_new_value = temp &  ~(SI_Long)4L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qok_slot_coordinator);
	    set_lookup_slot_value_1(frame,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
    }
    reformat_line_from_left(frame);
    return VALUES_1(value);
}

static Object Qmake_g2_secure_qm;  /* make-g2-secure? */

/* PUT-MAKE-G2-SECURE? */
Object put_make_g2_secure_qm(frame,value,gensymed_symbol)
    Object frame, value, gensymed_symbol;
{
    SI_Long ok_slot_coordinator_new_value, temp;

    x_note_fn_call(107,40);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qmake_g2_secure_qm);
    set_lookup_slot_value_1(frame,Qmake_g2_secure_qm,value);
    if ( !TRUEP(Loading_kb_p)) {
	if (value) {
	    ok_slot_coordinator_new_value = 
		    IFIX(get_lookup_slot_value_given_default(frame,
		    Qok_slot_coordinator,FIX((SI_Long)0L))) | (SI_Long)16L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qok_slot_coordinator);
	    set_lookup_slot_value_1(frame,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
	else {
	    temp = IFIX(get_lookup_slot_value_given_default(frame,
		    Qok_slot_coordinator,FIX((SI_Long)0L)));
	    ok_slot_coordinator_new_value = temp &  ~(SI_Long)16L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qok_slot_coordinator);
	    set_lookup_slot_value_1(frame,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
    }
    reformat_line_from_left(frame);
    return VALUES_1(value);
}

/* PUT-OK-SLOT-COORDINATOR */
Object put_ok_slot_coordinator(frame,value,gensymed_symbol)
    Object frame, value, gensymed_symbol;
{
    x_note_fn_call(107,41);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qok_slot_coordinator);
    set_lookup_slot_value_1(frame,Qok_slot_coordinator,value);
    reformat_line_from_left(frame);
    return VALUES_1(value);
}

/* COMPILE-PRODUCTS?-FOR-SLOT */
Object compile_products_qm_for_slot varargs_1(int, n)
{
    Object translation, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(107,42);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_symbol_list(translation);
}

/* WRITE-PRODUCTS?-FROM-SLOT */
Object write_products_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(107,43);
    return write_symbol_list(1,value);
}

/* WRITE-NUMBER-OR-UNLIMITED-FROM-SLOT */
Object write_number_or_unlimited_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(107,44);
    return twrite(value);
}

Object N_1_2_version = UNBOUND;

Object N_4_0_version = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Reference_date_for_interval_encoding, Qreference_date_for_interval_encoding);

static Object string_constant_18;  /* "none" */

static Object string_constant_19;  /* "from " */

static Object string_constant_20;  /* " to " */

/* WRITE-AUTHORIZATION-INTERVAL?-FROM-SLOT */
Object write_authorization_interval_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object start_date_1, end_date_1, day, month, year;
    SI_Long start_date, end_date;
    Object result;

    x_note_fn_call(107,45);
    if ( !TRUEP(value))
	return twrite(string_constant_18);
    else if (value && IFIX(value) >= (SI_Long)8388608L) {
	start_date = IFIX(Reference_date_for_interval_encoding) + 
		(IFIX(value) & (SI_Long)4095L);
	end_date = start_date + (IFIX(value) >>  -  - (SI_Long)12L & 
		(SI_Long)2047L);
	result = VALUES_2(FIX(start_date),FIX(end_date));
	MVS_2(result,start_date_1,end_date_1);
	twrite(string_constant_19);
	result = decode_universal_date(start_date_1);
	MVS_3(result,day,month,year);
	print_decoded_date(day,month,year);
	twrite(string_constant_20);
	result = decode_universal_date(end_date_1);
	MVS_3(result,day,month,year);
	return print_decoded_date(day,month,year);
    }
    else {
	result = decode_universal_date(value);
	MVS_3(result,day,month,year);
	return print_decoded_date(day,month,year);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Floating_telewindows_limit, Qfloating_telewindows_limit);

DEFINE_VARIABLE_WITH_SYMBOL(Floating_tw2_limit, Qfloating_tw2_limit);

static Object Qfloating;           /* floating */

/* COUNT-FLOATING-TELEWINDOWS-IN-SERVICE */
Object count_floating_telewindows_in_service()
{
    Object floating_license_level, workstation, ab_loop_list_;
    Object telewindows_count;
    SI_Long ab_loopvar_;

    x_note_fn_call(107,46);
    floating_license_level = telewindows_license_level_from_product(Qfloating);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    ab_loopvar_ = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_EQ(ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)16L),
	    floating_license_level))
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    goto next_loop;
  end_loop:
    telewindows_count = FIX(ab_loopvar_);
    goto end_1;
    telewindows_count = Qnil;
  end_1:;
    return VALUES_1(telewindows_count);
}

static Object Qui_client_session;  /* ui-client-session */

/* COUNT-FLOATING-TW2-IN-SERVICE */
Object count_floating_tw2_in_service()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, session, ui_session_count;
    SI_Long ab_loopvar__2;
    char temp;
    Declare_special(1);

    x_note_fn_call(107,47);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    session = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__2 = (SI_Long)0L;
      ab_loopvar_ = collect_subclasses(Qui_client_session);
    next_loop:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_1:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_1;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      session = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ( !(IFIX(ui_client_session_license_level_qm_function(session)) == 
	      (SI_Long)-2L) && 
	      IFIX(ui_client_session_license_level_qm_function(session)) 
	      == (SI_Long)-1L && ui_client_session_valid_p(session))
	  ab_loopvar__2 = ab_loopvar__2 + (SI_Long)1L;
      goto next_loop;
    end_loop_1:
      ui_session_count = FIX(ab_loopvar__2);
      goto end_1;
      ui_session_count = Qnil;
    end_1:;
    POP_SPECIAL();
    return VALUES_1(ui_session_count);
}

DEFINE_VARIABLE_WITH_SYMBOL(Free_floater_allowed_qm, Qfree_floater_allowed_qm);

/* SET-FLAG-PERMITTING-FREE-FLOATING-AUTHORIZATION */
Object set_flag_permitting_free_floating_authorization()
{
    x_note_fn_call(107,48);
    if ( !EQ(get_g2_license_level(),FIX((SI_Long)0L))) {
	Free_floater_allowed_qm = T;
	return VALUES_1(Free_floater_allowed_qm);
    }
    else
	return VALUES_1(Nil);
}

/* COUNT-AVAILABLE-FLOATING-TELEWINDOWS */
Object count_available_floating_telewindows()
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(107,49);
    gensymed_symbol = (SI_Long)0L;
    gensymed_symbol_1 = IFIX(Floating_telewindows_limit);
    if (Free_floater_allowed_qm) {
	temp = count_floating_tw2_in_service();
	temp_1 = FIXNUM_LE(temp,FIXNUM_ADD1(Floating_tw2_limit));
    }
    else
	temp_1 = TRUEP(Nil);
    gensymed_symbol_2 = temp_1 ? (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = IFIX(count_floating_telewindows_in_service());
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    return VALUES_1(FIX(MAX(gensymed_symbol,gensymed_symbol_1)));
}

/* COUNT-AVAILABLE-FLOATING-TW2S */
Object count_available_floating_tw2s()
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(107,50);
    gensymed_symbol = (SI_Long)0L;
    gensymed_symbol_1 = IFIX(Floating_tw2_limit);
    if (Free_floater_allowed_qm) {
	temp = count_floating_telewindows_in_service();
	temp_1 = FIXNUM_LE(temp,FIXNUM_ADD1(Floating_telewindows_limit));
    }
    else
	temp_1 = TRUEP(Nil);
    gensymed_symbol_2 = temp_1 ? (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = IFIX(count_floating_tw2_in_service());
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    return VALUES_1(FIX(MAX(gensymed_symbol,gensymed_symbol_1)));
}

/* SOME-FLOATING-TELEWINDOWS-AVAILABLE-P */
Object some_floating_telewindows_available_p()
{
    x_note_fn_call(107,51);
    return VALUES_1(IFIX(count_available_floating_telewindows()) > 
	    (SI_Long)0L ? T : Nil);
}

/* SOME-FLOATING-TW2-AVAILABLE-P */
Object some_floating_tw2_available_p()
{
    x_note_fn_call(107,52);
    return VALUES_1(IFIX(count_available_floating_tw2s()) > (SI_Long)0L ? 
	    T : Nil);
}

/* OBTAIN-FLOATING-TELEWINDOWS-FOR-WORKSTATION-IF-POSSIBLE */
Object obtain_floating_telewindows_for_workstation_if_possible(gensym_window)
    Object gensym_window;
{
    Object svref_new_value;

    x_note_fn_call(107,53);
    if (some_floating_telewindows_available_p()) {
	svref_new_value = telewindows_license_level_from_product(Qfloating);
	SVREF(gensym_window,FIX((SI_Long)16L)) = svref_new_value;
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* GET-FLOATER-LICENSE-IF-AVAILABLE-FOR-WINDOW */
Object get_floater_license_if_available_for_window(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(107,54);
    return obtain_floating_telewindows_for_workstation_if_possible(gensym_window);
}

/* NEGOTIATE-TELEWINDOWS-LICENSING */
Object negotiate_telewindows_licensing(gensym_window)
    Object gensym_window;
{
    Object telewindows_license_level_of_gensym_window, g2_license_level;
    Object license_level_1;

    x_note_fn_call(107,55);
    telewindows_license_level_of_gensym_window = 
	    get_telewindows_license_level(gensym_window);
    g2_license_level = get_g2_license_level();
    if (FIXNUM_GE(telewindows_license_level_of_gensym_window,g2_license_level))
	license_level_1 = telewindows_license_level_of_gensym_window;
    else if ( !TRUEP(T))
	license_level_1 = FIX((SI_Long)-2L);
    else if (get_floater_license_if_available_for_window(gensym_window))
	license_level_1 = FIX((SI_Long)-1L);
    else
	license_level_1 = FIX((SI_Long)-2L);
    SVREF(gensym_window,FIX((SI_Long)16L)) = license_level_1;
    schedule_tw_modernization_tasks_if_necessary();
    return VALUES_1(license_level_1);
}

/* SESSION-LICENSING-LEVEL-COMPATIBLE-WITH-G2-LEVEL */
Object session_licensing_level_compatible_with_g2_level(session_symbolic_level)
    Object session_symbolic_level;
{
    Object temp, temp_1;

    x_note_fn_call(107,56);
    temp = telewindows_license_level_from_product(session_symbolic_level);
    temp_1 = get_g2_license_level();
    return VALUES_1(NUM_GE(temp,temp_1) ? T : Nil);
}

static Object Qunauthorized;       /* unauthorized */

static Object Qno_available_floating_licenses;  /* no-available-floating-licenses */

/* DISALLOW-UI-CLIENT-SESSION */
Object disallow_ui_client_session(ui_client_session)
    Object ui_client_session;
{
    x_note_fn_call(107,57);
    set_ui_client_session_license_level(ui_client_session,
	    telewindows_license_level_from_product(Qunauthorized));
    return VALUES_1(Qno_available_floating_licenses);
}

/* GET-TELEWINDOWS-LICENSE-LEVEL */
Object get_telewindows_license_level(gensym_window)
    Object gensym_window;
{
    Object temp;

    x_note_fn_call(107,58);
    temp = get_gensym_window_parameter(gensym_window,
	    Qtelewindows_license_level);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIX((SI_Long)3L));
}

/* START-ADAPTIVE-FONT-FALLBACK */
Object start_adaptive_font_fallback()
{
    Object temp, count_1, workstation, ab_loop_list_, workstations;
    Object ab_loopvar_, ab_loopvar__1;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(107,59);
    gensymed_symbol = IFIX(count_floating_telewindows_in_service());
    gensymed_symbol_1 = IFIX(Floating_telewindows_limit);
    if (Free_floater_allowed_qm) {
	temp = count_floating_tw2_in_service();
	temp_1 = FIXNUM_LE(temp,FIXNUM_ADD1(Floating_tw2_limit));
    }
    else
	temp_1 = TRUEP(Nil);
    gensymed_symbol_2 = temp_1 ? (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    count_1 = FIX(gensymed_symbol - gensymed_symbol_1);
    if (IFIX(count_1) > (SI_Long)0L) {
	notify_user(1,
		number_of_floating_telewindows_limit_exceeded_ok_message());
	workstation = Nil;
	ab_loop_list_ = Workstations_in_service;
	workstations = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)16L);
	if (FIXNUM_EQ(temp,
		    telewindows_license_level_from_product(Qfloating))) {
	    ab_loopvar__1 = gensym_cons_1(workstation,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		workstations = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    count_1 = FIXNUM_SUB1(count_1);
	}
	if ( !(IFIX(count_1) > (SI_Long)0L))
	    goto end_loop;
	goto next_loop;
      end_loop:
	workstation = Nil;
	ab_loop_list_ = workstations;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (memq_function(workstation,Workstations_in_service))
	    close_telewindows_connection(ISVREF(workstation,(SI_Long)1L));
	goto next_loop_1;
      end_loop_1:;
	reclaim_gensym_list_1(workstations);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* INVOKE-INTERLACE-ABSTRACTION-IF-OFFERED */
Object invoke_interlace_abstraction_if_offered()
{
    Object workstation, ab_loop_list_, workstations, ab_loopvar_;
    Object ab_loopvar__1, temp;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(107,60);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    workstations = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    arg = IFIX(telewindows_license_level_from_product(Qfloating));
    arg_1 = IFIX(ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)16L));
    arg_2 = IFIX(get_g2_license_level());
    if (arg < arg_1 && arg_1 < arg_2) {
	ab_loopvar__1 = gensym_cons_1(workstation,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    workstations = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    if (workstations) {
	workstation = Nil;
	ab_loop_list_ = workstations;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = not_permitted_to_connect_to_development_g2_ok_message();
	notify_user(2,temp,
		get_telewindows_product_name_from_level(ISVREF(ISVREF(workstation,
		(SI_Long)1L),(SI_Long)16L)));
	goto next_loop_1;
      end_loop_1:;
	workstation = Nil;
	ab_loop_list_ = workstations;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (memq_function(workstation,Workstations_in_service))
	    close_telewindows_connection(ISVREF(workstation,(SI_Long)1L));
	goto next_loop_2;
      end_loop_2:;
	reclaim_gensym_list_1(workstations);
    }
    return VALUES_1(Qnil);
}

/* OPTIMIZE-TELEWINDOWS-Z-LAYER-MODEL */
Object optimize_telewindows_z_layer_model()
{
    Object workstation, ab_loop_list_, gensym_window, telewindows_window_p_1;
    Object workstations, ab_loopvar_, ab_loopvar__1, temp;
    char temp_1;

    x_note_fn_call(107,61);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
    telewindows_window_p_1 = Nil;
    workstations = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    telewindows_window_p_1 = ISVREF(gensym_window,(SI_Long)12L);
    if (telewindows_window_p_1) {
	temp = ISVREF(gensym_window,(SI_Long)16L);
	temp_1 = FIXNUM_LE(temp,
		telewindows_license_level_from_product(Qunauthorized));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	ab_loopvar__1 = gensym_cons_1(workstation,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    workstations = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    workstation = Nil;
    ab_loop_list_ = workstations;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(workstation,Workstations_in_service))
	close_telewindows_connection(ISVREF(workstation,(SI_Long)1L));
    goto next_loop_1;
  end_loop_1:;
    reclaim_gensym_list_1(workstations);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Ctlc_cons_count, Qctlc_cons_count);

Object The_type_description_of_t2_nonce_data = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_t2_nonce_datas, Qchain_of_available_t2_nonce_datas);

DEFINE_VARIABLE_WITH_SYMBOL(T2_nonce_data_count, Qt2_nonce_data_count);

Object Chain_of_available_t2_nonce_datas_vector = UNBOUND;

/* T2-NONCE-DATA-STRUCTURE-MEMORY-USAGE */
Object t2_nonce_data_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(107,62);
    temp = T2_nonce_data_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-T2-NONCE-DATA-COUNT */
Object outstanding_t2_nonce_data_count()
{
    Object def_structure_t2_nonce_data_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(107,63);
    gensymed_symbol = IFIX(T2_nonce_data_count);
    def_structure_t2_nonce_data_variable = Chain_of_available_t2_nonce_datas;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_t2_nonce_data_variable))
	goto end_loop;
    def_structure_t2_nonce_data_variable = 
	    ISVREF(def_structure_t2_nonce_data_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-T2-NONCE-DATA-1 */
Object reclaim_t2_nonce_data_1(t2_nonce_data)
    Object t2_nonce_data;
{
    Object temp, svref_arg_2;

    x_note_fn_call(107,64);
    inline_note_reclaim_cons(t2_nonce_data,Nil);
    temp = ISVREF(Chain_of_available_t2_nonce_datas_vector,
	    IFIX(Current_thread_index));
    SVREF(t2_nonce_data,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_t2_nonce_datas_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = t2_nonce_data;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-T2-NONCE-DATA */
Object reclaim_structure_for_t2_nonce_data(t2_nonce_data)
    Object t2_nonce_data;
{
    x_note_fn_call(107,65);
    return reclaim_t2_nonce_data_1(t2_nonce_data);
}

static Object Qg2_defstruct_structure_name_t2_nonce_data_g2_struct;  /* g2-defstruct-structure-name::t2-nonce-data-g2-struct */

/* MAKE-PERMANENT-T2-NONCE-DATA-STRUCTURE-INTERNAL */
Object make_permanent_t2_nonce_data_structure_internal()
{
    Object def_structure_t2_nonce_data_variable;
    Object defstruct_g2_t2_nonce_data_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(107,66);
    def_structure_t2_nonce_data_variable = Nil;
    atomic_incff_symval(Qt2_nonce_data_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_t2_nonce_data_variable = Nil;
	gensymed_symbol = (SI_Long)6L;
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
	defstruct_g2_t2_nonce_data_variable = the_array;
	SVREF(defstruct_g2_t2_nonce_data_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_t2_nonce_data_g2_struct;
	def_structure_t2_nonce_data_variable = 
		defstruct_g2_t2_nonce_data_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_t2_nonce_data_variable);
}

static Object Qnot_allocated;      /* not-allocated */

/* MAKE-T2-NONCE-DATA-1 */
Object make_t2_nonce_data_1()
{
    Object def_structure_t2_nonce_data_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(107,67);
    def_structure_t2_nonce_data_variable = 
	    ISVREF(Chain_of_available_t2_nonce_datas_vector,
	    IFIX(Current_thread_index));
    if (def_structure_t2_nonce_data_variable) {
	svref_arg_1 = Chain_of_available_t2_nonce_datas_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_t2_nonce_data_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_t2_nonce_data_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_t2_nonce_data_g2_struct;
    }
    else
	def_structure_t2_nonce_data_variable = 
		make_permanent_t2_nonce_data_structure_internal();
    inline_note_allocate_cons(def_structure_t2_nonce_data_variable,Nil);
    SVREF(def_structure_t2_nonce_data_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_t2_nonce_data_variable,FIX((SI_Long)2L)) = 
	    Qnot_allocated;
    SVREF(def_structure_t2_nonce_data_variable,FIX((SI_Long)3L)) = Nil;
    ISVREF(def_structure_t2_nonce_data_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_t2_nonce_data_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_t2_nonce_data_variable);
}

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* MUTATE-T2-NONCE-HASH-TREE-ENTRY */
Object mutate_t2_nonce_hash_tree_entry(entry_cons,new_key,new_entry)
    Object entry_cons, new_key, new_entry;
{
    Object structure, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(107,68);
    reclaim_text_string(M_CAR(entry_cons));
    structure = M_CDR(entry_cons);
    gensymed_symbol = ISVREF(structure,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = structure;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    M_CAR(entry_cons) = new_key;
    M_CDR(entry_cons) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_t2_nonce_hash_tree_entry = UNBOUND;

static Object Qstring_eq_w;        /* string=w */

/* CLEAR-T2-NONCE-HASH-TREE */
Object clear_t2_nonce_hash_tree(t2_nonce_hash_binary_tree)
    Object t2_nonce_hash_binary_tree;
{
    Object element_qm, temp, gensymed_symbol, old_key, old_entry;
    Object gensymed_symbol_1;
    Object result;

    x_note_fn_call(107,69);
    element_qm = Nil;
  next_loop:
    element_qm = CDR(t2_nonce_hash_binary_tree);
    if ( !TRUEP(element_qm))
	goto end_loop;
    temp = ISVREF(element_qm,(SI_Long)3L);
    gensymed_symbol = CAAR(temp);
    result = delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qstring_eq_w),
	    gensymed_symbol,t2_nonce_hash_binary_tree,
	    sxhashw(gensymed_symbol));
    MVS_2(result,old_key,old_entry);
    reclaim_text_string(old_key);
    gensymed_symbol = ISVREF(old_entry,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = old_entry;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    goto next_loop;
  end_loop:;
    return VALUES_1(t2_nonce_hash_binary_tree);
}

DEFINE_VARIABLE_WITH_SYMBOL(T2_nonce_table, Qt2_nonce_table);

/* RECLAIM-NONCE */
Object reclaim_nonce(t2_nonce_data)
    Object t2_nonce_data;
{
    Object nonce, temp, old_key, old_entry, gensymed_symbol, gensymed_symbol_1;
    Object result;

    x_note_fn_call(107,70);
    if (t2_nonce_data) {
	nonce = ISVREF(t2_nonce_data,(SI_Long)1L);
	temp = T2_nonce_table;
	result = delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qstring_eq_w),
		nonce,temp,sxhashw(nonce));
	MVS_2(result,old_key,old_entry);
	reclaim_text_string(old_key);
	gensymed_symbol = ISVREF(old_entry,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)3L);
	gensymed_symbol_1 = old_entry;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qlogin_not_yet_attempted;  /* login-not-yet-attempted */

/* ALLOCATE-NEW-NONCE */
Object allocate_new_nonce()
{
    Object uuid, string_1, nonce, gensymed_symbol, temp, temp_1;

    x_note_fn_call(107,71);
    uuid = allocate_new_nonce_internal();
    string_1 = convert_uuid_string_to_hex_string(uuid,lengthw(uuid));
    nonce = make_t2_nonce_data_1();
    SVREF(nonce,FIX((SI_Long)1L)) = string_1;
    SVREF(nonce,FIX((SI_Long)2L)) = Qlogin_not_yet_attempted;
    gensymed_symbol = string_1;
    temp = T2_nonce_table;
    temp_1 = Fp_mutate_t2_nonce_hash_tree_entry;
    set_balanced_binary_tree_entry(temp,Qstring_eq_w,temp_1,T,
	    gensymed_symbol,sxhashw(gensymed_symbol),nonce);
    return VALUES_1(nonce);
}

static Object Qlogged_in;          /* logged-in */

static Object Qui_client_session_nonce;  /* ui-client-session-nonce */

/* NOTE-THAT-SESSION-HAS-BEEN-SUCCESSFULLY-LOGGED-IN */
Object note_that_session_has_been_successfully_logged_in(ui_client_session)
    Object ui_client_session;
{
    Object struct_1;

    x_note_fn_call(107,72);
    set_ui_client_session_status(ui_client_session,Qlogged_in);
    struct_1 = 
	    data_for_valid_nonce(get_slot_value_function(ui_client_session,
	    Qui_client_session_nonce,Nil));
    if (struct_1)
	return VALUES_1(SVREF(struct_1,FIX((SI_Long)2L)) = Qlogged_in);
    else
	return VALUES_1(Nil);
}

/* SESSION-HAS-SUCCESSFULLY-LOGGED-IN-P */
Object session_has_successfully_logged_in_p(ui_client_session)
    Object ui_client_session;
{
    Object struct_1, temp;

    x_note_fn_call(107,73);
    struct_1 = 
	    data_for_valid_nonce(get_slot_value_function(ui_client_session,
	    Qui_client_session_nonce,Nil));
    temp = struct_1 ? (EQ(ISVREF(struct_1,(SI_Long)2L),Qlogged_in) ? T : 
	    Nil) : Nil;
    return VALUES_1(temp);
}

static Object Qno_entry_for_this_nonce;  /* no-entry-for-this-nonce */

static Object Qlogged_out;         /* logged-out */

/* NOTE-THAT-SESSION-HAS-LOGGED-OUT */
Object note_that_session_has_logged_out(ui_client_session)
    Object ui_client_session;
{
    Object struct_1, error_symbol_qm, temp;
    Object result;

    x_note_fn_call(107,74);
    result = data_for_valid_nonce(get_slot_value_function(ui_client_session,
	    Qui_client_session_nonce,Nil));
    MVS_2(result,struct_1,error_symbol_qm);
    if ( !(error_symbol_qm && EQ(error_symbol_qm,Qno_entry_for_this_nonce) 
	    && EQ(ui_client_session_status_function(ui_client_session),
	    Qno_available_floating_licenses))) {
	if (struct_1)
	    reclaim_nonce(struct_1);
    }
    temp = set_ui_client_session_status(ui_client_session,Qlogged_out);
    return VALUES_1(temp);
}

static Object Qtoo_many_login_attempts;  /* too-many-login-attempts */

/* NONCE-IS-NOT-IN-A-VALID-STATE */
Object nonce_is_not_in_a_valid_state(nonce_data)
    Object nonce_data;
{
    Object state_1;

    x_note_fn_call(107,75);
    state_1 = ISVREF(nonce_data,(SI_Long)2L);
    return VALUES_1(EQ(state_1,Qtoo_many_login_attempts) ? 
	    Qtoo_many_login_attempts : Nil);
}

static Object Qnonce_is_not_a_string;  /* nonce-is-not-a-string */

/* DATA-FOR-VALID-NONCE */
Object data_for_valid_nonce(string_1)
    Object string_1;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, nonce_data;
    Object temp;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(107,76);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L) {
	gensymed_symbol = CDR(T2_nonce_table);
	gensymed_symbol_1 = string_1;
	gensymed_symbol_2 = IFIX(sxhashw(string_1));
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (string_eq_w(gensymed_symbol_1,gensymed_symbol_4)) {
		nonce_data = M_CDR(M_CAR(gensymed_symbol));
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:
	    nonce_data = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	nonce_data = Qnil;
      end_2:;
	if (nonce_data) {
	    temp = nonce_is_not_in_a_valid_state(nonce_data);
	    return VALUES_2(nonce_data,temp);
	}
	else
	    return VALUES_2(Nil,Qno_entry_for_this_nonce);
    }
    else
	return VALUES_2(Nil,Qnonce_is_not_a_string);
}

/* UI-CLIENT-SESSION-FOR-NONCE */
Object ui_client_session_for_nonce(uuid)
    Object uuid;
{
    Object nonce_data_qm, error_symbol_qm, temp;
    Object result;

    x_note_fn_call(107,77);
    result = data_for_valid_nonce(uuid);
    MVS_2(result,nonce_data_qm,error_symbol_qm);
    if (nonce_data_qm) {
	temp = ISVREF(nonce_data_qm,(SI_Long)3L);
	return VALUES_3(temp,error_symbol_qm,nonce_data_qm);
    }
    else
	return VALUES_2(Nil,error_symbol_qm);
}

static Object array_constant_3;    /* # */

/* HASH-NONCE-WITH-PASSWORD-HASH */
Object hash_nonce_with_password_hash(nonce,password_hash)
    Object nonce, password_hash;
{
    Object string_1, temp;

    x_note_fn_call(107,78);
    string_1 = obtain_simple_gensym_string(FIX((SI_Long)16L));
    g2ext_init_g2_MD5_context((SI_Long)0L);
    update_indexed_md5_context(FIX((SI_Long)0L),password_hash);
    update_indexed_md5_context(FIX((SI_Long)0L),array_constant_3);
    update_indexed_md5_context(FIX((SI_Long)0L),nonce);
    finalize_indexed_md5_context(FIX((SI_Long)0L),string_1);
    temp = convert_md5_result_string_to_hex_string(string_1,FIX((SI_Long)16L));
    reclaim_simple_gensym_string(string_1);
    return VALUES_1(temp);
}

/* UI-CLIENT-SESSION-IS-NOT-UNAUTHORIZED-P */
Object ui_client_session_is_not_unauthorized_p(session)
    Object session;
{
    x_note_fn_call(107,79);
    return VALUES_1( 
	    !(IFIX(ui_client_session_license_level_qm_function(session)) 
	    == (SI_Long)-2L) ? T : Nil);
}

/* UI-CLIENT-SESSION-IS-SELF-AUTHORIZED-P */
Object ui_client_session_is_self_authorized_p(session)
    Object session;
{
    Object level;

    x_note_fn_call(107,80);
    level = ui_client_session_license_level_qm_function(session);
    if ( !(IFIX(level) == (SI_Long)-2L))
	return VALUES_1( !(IFIX(level) == (SI_Long)-1L) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qonly_one_named_connection_per_client;  /* only-one-named-connection-per-client */

static Object Qalready_failed_self_authorization;  /* already-failed-self-authorization */

/* COMPACT-CONS-POOLS-NOW-IF-NECESSARY */
Object compact_cons_pools_now_if_necessary(gsi_interface,nonce,machine_id,
	    ok_code1,ok_code2,ok_code3,ok_code4,ok_code5,start_date_qm,
	    expiration_date_qm,desired_authorization_level)
    Object gsi_interface, nonce, machine_id, ok_code1, ok_code2, ok_code3;
    Object ok_code4, ok_code5, start_date_qm, expiration_date_qm;
    Object desired_authorization_level;
{
    Object session_qm, error_symbol_qm, nonce_data;
    Object result;

    x_note_fn_call(107,81);
    if (already_is_a_named_ui_session_from_this_client(gsi_interface,
	    machine_id))
	return VALUES_2(Nil,Qonly_one_named_connection_per_client);
    result = ui_client_session_for_nonce(nonce);
    MVS_3(result,session_qm,error_symbol_qm,nonce_data);
    if (error_symbol_qm) {
	if (session_qm)
	    g2_release_ui_client_session(session_qm);
	return VALUES_2(Nil,error_symbol_qm);
    }
    if (session_qm && reposition_cons_pool_fragments(session_qm,machine_id,
	    ok_code1,ok_code2,ok_code3,ok_code4,ok_code5,start_date_qm,
	    expiration_date_qm,desired_authorization_level)) {
	if (ui_client_session_is_not_unauthorized_p(session_qm))
	    return VALUES_1(T);
	else {
	    g2_release_ui_client_session(session_qm);
	    return VALUES_2(Nil,Qalready_failed_self_authorization);
	}
    }
    else
	return compact_cons_pools_now(nonce_data,machine_id,ok_code1,
		ok_code2,ok_code3,ok_code4,ok_code5,start_date_qm,
		expiration_date_qm,desired_authorization_level);
}

static Object Qundefined_license_level_requested;  /* undefined-license-level-requested */

static Object Qincompatible_license_level_no_floaters;  /* incompatible-license-level-no-floaters */

static Object Qincompatible_license_level;  /* incompatible-license-level */

/* COMPACT-CONS-POOLS-NOW */
Object compact_cons_pools_now(nonce_data,machine_id,ok_code1,ok_code2,
	    ok_code3,ok_code4,ok_code5,start_date_qm,expiration_date_qm,
	    desired_license_level)
    Object nonce_data, machine_id, ok_code1, ok_code2, ok_code3, ok_code4;
    Object ok_code5, start_date_qm, expiration_date_qm, desired_license_level;
{
    Object level_to_authorize, error_symbol_qm, ok_qm, internal_desired_level;
    Object numerical_desired_level, session;
    Object result;

    x_note_fn_call(107,82);
    level_to_authorize = FIX((SI_Long)-2L);
    error_symbol_qm = Nil;
    ok_qm = Nil;
    if (EQ(desired_license_level,Qdevelopment))
	internal_desired_level = Qdevelopment;
    else if (EQ(desired_license_level,Qdeployment))
	internal_desired_level = Qrestricted_use_option;
    else {
	error_symbol_qm = Qundefined_license_level_requested;
	internal_desired_level = Nil;
    }
    numerical_desired_level =  !TRUEP(error_symbol_qm) ? 
	    telewindows_license_level_from_product(internal_desired_level) 
	    : Qnil;
    if ( !TRUEP(error_symbol_qm)) {
	result = defragment_rpc_mapping_table(machine_id,ok_code1,ok_code2,
		ok_code3,ok_code4,ok_code5,start_date_qm,
		expiration_date_qm,internal_desired_level);
	MVS_2(result,ok_qm,error_symbol_qm);
	if (ok_qm) {
	    if (session_licensing_level_compatible_with_g2_level(internal_desired_level))
		level_to_authorize = numerical_desired_level;
	    else if (T) {
		if (some_floating_tw2_available_p())
		    level_to_authorize = FIX((SI_Long)-1L);
		else {
		    error_symbol_qm = Qincompatible_license_level_no_floaters;
		    ok_qm = Nil;
		}
	    }
	    else
		error_symbol_qm = Qincompatible_license_level;
	    if ( !TRUEP(error_symbol_qm)) {
		session = make_ui_client_session_internal();
		SVREF(nonce_data,FIX((SI_Long)3L)) = session;
		set_ui_client_session_license_level(session,
			level_to_authorize);
		remove_gaps_from_cons_pool(nonce_data,machine_id,ok_code1,
			ok_code2,ok_code3,ok_code4,ok_code5,start_date_qm,
			expiration_date_qm,internal_desired_level,
			level_to_authorize);
	    }
	}
    }
    return VALUES_2(ok_qm,error_symbol_qm);
}

/* REMOVE-GAPS-FROM-CONS-POOL */
Object remove_gaps_from_cons_pool(nonce_data,machine_id,ok_code1,ok_code2,
	    ok_code3,ok_code4,ok_code5,start_date_qm,expiration_date_qm,
	    desired_license_level,level_to_authorize)
    Object nonce_data, machine_id, ok_code1, ok_code2, ok_code3, ok_code4;
    Object ok_code5, start_date_qm, expiration_date_qm, desired_license_level;
    Object level_to_authorize;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(107,83);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)10L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = level_to_authorize;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = desired_license_level;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = start_date_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = expiration_date_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = ok_code1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = ok_code2;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = ok_code3;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = ok_code4;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = ok_code5;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = machine_id;
    return VALUES_1(SVREF(nonce_data,FIX((SI_Long)5L)) = gensymed_symbol);
}

/* CHECK-PULSE-RATE-LIMIT */
Object check_pulse_rate_limit(session)
    Object session;
{
    Object nonce_data;

    x_note_fn_call(107,84);
    nonce_data = 
	    data_for_valid_nonce(ui_client_session_nonce_function(session));
    if (nonce_data)
	return VALUES_1(ISVREF(nonce_data,(SI_Long)5L));
    else
	return VALUES_1(Nil);
}

/* REPOSITION-CONS-POOL-FRAGMENTS */
Object reposition_cons_pool_fragments(session,machine_id,ok_code1,ok_code2,
	    ok_code3,ok_code4,ok_code5,start_date_qm,expiration_date_qm,
	    desired_license_level)
    Object session, machine_id, ok_code1, ok_code2, ok_code3, ok_code4;
    Object ok_code5, start_date_qm, expiration_date_qm, desired_license_level;
{
    volatile Object current_list;
    Object reference_list, gensymed_symbol, gensymed_symbol_1, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(107,85);
    SAVE_STACK();
    current_list = Qunbound_in_protected_let;
    reference_list = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)9L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = desired_license_level;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = start_date_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = expiration_date_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = ok_code1;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = ok_code2;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = ok_code3;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = ok_code4;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = ok_code5;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = machine_id;
	current_list = gensymed_symbol;
	reference_list = check_pulse_rate_limit(session);
	if (reference_list) {
	    temp = CDR(reference_list);
	    SAVE_VALUES(VALUES_1(EQUAL(current_list,temp) ? T : Nil));
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(0);
    if (current_list) {
	if ( !EQ(current_list,Qunbound_in_protected_let))
	    reclaim_gensym_list_1(current_list);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Relations_tag_list, Qrelations_tag_list);

/* INITIAL-G2-IS-SECURE */
Object initial_g2_is_secure(class_1)
    Object class_1;
{
    x_note_fn_call(107,86);
    return VALUES_1(Nil);
}

/* GET-G2-IS-SECURE */
Object get_g2_is_secure(server_parameters)
    Object server_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(107,87);
    PUSH_SPECIAL_WITH_SYMBOL(Server_parameters,Qserver_parameters,server_parameters,
	    0);
      result = VALUES_1(Relations_tag_list ? Evaluation_true_value : 
	      Evaluation_false_value);
    POP_SPECIAL();
    return result;
}

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

/* COMPILE-NUMBER-OF-PROCESSES-FOR-SLOT */
Object compile_number_of_processes_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(107,88);
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
    if ( !NUMBERP(parse_result))
	return VALUES_1(Nil);
    else if (IFIX(parse_result) < (SI_Long)1L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_4,
		FIX((SI_Long)21L));
	return VALUES_2(temp,temp_1);
    }
    else if (IFIX(parse_result) > (SI_Long)200L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_5,
		FIX((SI_Long)27L));
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(parse_result);
}

static Object string_constant_21;  /* "no limit" */

/* WRITE-NUMBER-OF-PROCESSES-FROM-SLOT */
Object write_number_of_processes_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(107,89);
    if (NUMBERP(value))
	return twrite(value);
    else
	return twrite(string_constant_21);
}

static Object Qnumber_of_processes_authorized;  /* number-of-processes-authorized */

/* PUT-NUMBER-OF-PROCESSES-AUTHORIZED */
Object put_number_of_processes_authorized(ok,value,gensymed_symbol)
    Object ok, value, gensymed_symbol;
{
    SI_Long ok_slot_coordinator_new_value, temp;

    x_note_fn_call(107,90);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(ok,Qnumber_of_processes_authorized);
    set_lookup_slot_value_1(ok,Qnumber_of_processes_authorized,value);
    if ( !TRUEP(Loading_kb_p)) {
	if (value) {
	    ok_slot_coordinator_new_value = 
		    IFIX(get_lookup_slot_value_given_default(ok,
		    Qok_slot_coordinator,FIX((SI_Long)0L))) | (SI_Long)32L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(ok,Qok_slot_coordinator);
	    set_lookup_slot_value_1(ok,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
	else {
	    temp = IFIX(get_lookup_slot_value_given_default(ok,
		    Qok_slot_coordinator,FIX((SI_Long)0L)));
	    ok_slot_coordinator_new_value = temp &  ~(SI_Long)32L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(ok,Qok_slot_coordinator);
	    set_lookup_slot_value_1(ok,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
    }
    reformat_line_from_left(ok);
    return VALUES_1(value);
}

static Object Qmaximum_number_of_concurrent_floating_telewindows_allowed;  /* maximum-number-of-concurrent-floating-telewindows-allowed */

static Object Qok;                 /* ok */

/* PUT-MAXIMUM-NUMBER-OF-CONCURRENT-FLOATING-TELEWINDOWS-ALLOWED */
Object put_maximum_number_of_concurrent_floating_telewindows_allowed(ok,
	    value,gensymed_symbol)
    Object ok, value, gensymed_symbol;
{
    Object temp_1;
    SI_Long temp, ok_slot_coordinator_new_value;

    x_note_fn_call(107,91);
    temp = MIN((SI_Long)8000L,IFIX(value));
    value = FIX(MAX((SI_Long)0L,temp));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(ok,
		Qmaximum_number_of_concurrent_floating_telewindows_allowed);
    set_lookup_slot_value_1(ok,
	    Qmaximum_number_of_concurrent_floating_telewindows_allowed,value);
    if ( !TRUEP(Loading_kb_p)) {
	temp_1 = value;
	if ( !EQ(temp_1,get_slot_init_form(2,Qok,
		Qmaximum_number_of_concurrent_floating_telewindows_allowed))) {
	    ok_slot_coordinator_new_value = 
		    IFIX(get_lookup_slot_value_given_default(ok,
		    Qok_slot_coordinator,FIX((SI_Long)0L))) | (SI_Long)64L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(ok,Qok_slot_coordinator);
	    set_lookup_slot_value_1(ok,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
	else {
	    temp = IFIX(get_lookup_slot_value_given_default(ok,
		    Qok_slot_coordinator,FIX((SI_Long)0L)));
	    ok_slot_coordinator_new_value = temp &  ~(SI_Long)64L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(ok,Qok_slot_coordinator);
	    set_lookup_slot_value_1(ok,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
    }
    reformat_line_from_left(ok);
    return VALUES_1(value);
}

static Object string_constant_22;  /* "~(~a~) " */

static Object string_constant_23;  /* "," */

static Object string_constant_24;  /* " ~d ~d ~d" */

static Object string_constant_25;  /* ";~%" */

/* WRITE-AUTHORIZED-PACKAGES-FROM-SLOT */
Object write_authorized_packages_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object authorization, rest_1, ab_loop_list_, dates_qm, day, month, year;
    Object result;

    x_note_fn_call(107,92);
    if (value) {
	authorization = Nil;
	rest_1 = Nil;
	ab_loop_list_ = value;
	dates_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	authorization = CAR(ab_loop_list_);
	rest_1 = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	dates_qm = CDDDDR(authorization);
	tformat(2,string_constant_22,FIRST(authorization));
	if (dates_qm) {
	    twrite(string_constant_19);
	    result = decode_universal_date(FIRST(dates_qm));
	    MVS_3(result,day,month,year);
	    print_decoded_date(day,month,year);
	    twrite(string_constant_20);
	    result = decode_universal_date(SECOND(dates_qm));
	    MVS_3(result,day,month,year);
	    print_decoded_date(day,month,year);
	    twrite(string_constant_23);
	}
	tformat(4,string_constant_24,SECOND(authorization),
		THIRD(authorization),FOURTH(authorization));
	if (rest_1)
	    tformat(1,string_constant_25);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return twrite(string_constant_18);
}

static Object array_constant_6;    /* # */

/* COMPILE-AUTHORIZED-PACKAGES-FOR-SLOT */
Object compile_authorized_packages_for_slot varargs_1(int, n)
{
    Object parse_result, ok, gensymed_symbol;
    Object pkg, ab_loop_list_, start_date_qm, end_date_qm, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(107,93);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    ok = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else {
	pkg = Nil;
	ab_loop_list_ = parse_result;
	start_date_qm = Nil;
	end_date_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	pkg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	start_date_qm = FIFTH(pkg);
	end_date_qm = SIXTH(pkg);
	if (start_date_qm && (FIXNUM_GE(start_date_qm,end_date_qm) || 
		IFIX(start_date_qm) == (SI_Long)0L)) {
	    temp = Bad_phrase;
	    temp_1 = 
		    copy_constant_wide_string_given_length(array_constant_6,
		    FIX((SI_Long)43L));
	    return VALUES_2(temp,temp_1);
	}
	goto next_loop;
      end_loop:
	analyze_authorized_packages(parse_result,
		get_lookup_slot_value_given_default(ok,Qmachine_id,Nil),ok);
	return VALUES_1(parse_result);
	return VALUES_1(Qnil);
    }
}

static Object Qbad_package_authorization;  /* bad-package-authorization */

/* ANALYZE-AUTHORIZED-PACKAGES */
Object analyze_authorized_packages(package_authorizations,machine_id,ok)
    Object package_authorizations, machine_id, ok;
{
    Object q3, q4, q5, q6, c3, authorization, ab_loop_list_, package_name_1;
    Object code_1, code_2, code_3, start_date, end_date, temp;
    Object result;

    x_note_fn_call(107,94);
    delete_frame_note_if_any(Qbad_package_authorization,ok);
    if (machine_id) {
	q3 = Nil;
	q4 = Nil;
	q5 = Nil;
	q6 = Nil;
	c3 = Nil;
	authorization = Nil;
	ab_loop_list_ = package_authorizations;
	package_name_1 = Nil;
	code_1 = Nil;
	code_2 = Nil;
	code_3 = Nil;
	start_date = Nil;
	end_date = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	authorization = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	package_name_1 = FIRST(authorization);
	code_1 = SECOND(authorization);
	code_2 = THIRD(authorization);
	code_3 = FOURTH(authorization);
	temp = fifth(authorization);
	if (temp);
	else
	    temp = FIX((SI_Long)0L);
	start_date = temp;
	temp = SIXTH(authorization);
	if (temp);
	else
	    temp = FIX((SI_Long)0L);
	end_date = temp;
	result = eval_sequence_2(symbol_name_text_string(package_name_1));
	MVS_2(result,q3,q4);
	result = button_down_handler(machine_id);
	MVS_2(result,q5,q6);
	c3 = reverse_list_search(q3,q4,q5,q6,code_1,code_2,start_date,
		end_date);
	if ( !FIXNUM_EQ(c3,code_3))
	    add_to_frame_note_particulars_list_if_necessary(package_name_1,
		    Qbad_package_authorization,ok);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* NEW-ANALYZE-AUTHORIZED-PACKAGES */
Object new_analyze_authorized_packages(package_authorizations,machine_id)
    Object package_authorizations, machine_id;
{
    Object q3, q4, q5, q6, c3, authorization, ab_loop_list_, package_name_1;
    Object code_1, code_2, code_3, start_date, end_date, temp;
    Object result;

    x_note_fn_call(107,95);
    q3 = Nil;
    q4 = Nil;
    q5 = Nil;
    q6 = Nil;
    c3 = Nil;
    authorization = Nil;
    ab_loop_list_ = package_authorizations;
    package_name_1 = Nil;
    code_1 = Nil;
    code_2 = Nil;
    code_3 = Nil;
    start_date = Nil;
    end_date = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    authorization = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    package_name_1 = FIRST(authorization);
    code_1 = SECOND(authorization);
    code_2 = THIRD(authorization);
    code_3 = FOURTH(authorization);
    temp = fifth(authorization);
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start_date = temp;
    temp = SIXTH(authorization);
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    end_date = temp;
    result = eval_sequence_2(symbol_name_text_string(package_name_1));
    MVS_2(result,q3,q4);
    result = button_down_handler(machine_id);
    MVS_2(result,q5,q6);
    c3 = reverse_list_search(q3,q4,q5,q6,code_1,code_2,start_date,end_date);
    if ( !FIXNUM_EQ(c3,code_3)) {
	error_broke_rule_reading_ok_file(1,
		incorrect_authorization_for_package_ok_message());
	return VALUES_1(Nil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

static Object string_constant_26;  /* "the following packages have invalid authorization codes: " */

static Object string_constant_27;  /* "~(~a~)" */

static Object string_constant_28;  /* ", " */

/* WRITE-BAD-PACKAGE-AUTHORIZATION-NOTE */
Object write_bad_package_authorization_note(packages,gensymed_symbol)
    Object packages, gensymed_symbol;
{
    Object kb_package, rest_1, ab_loop_list_;

    x_note_fn_call(107,96);
    twrite(string_constant_26);
    kb_package = Nil;
    rest_1 = Nil;
    ab_loop_list_ = packages;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    kb_package = CAR(ab_loop_list_);
    rest_1 = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(2,string_constant_27,kb_package);
    if (rest_1)
	twrite(string_constant_28);
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

/* PUT-AUTHORIZED-KB-PACKAGES */
Object put_authorized_kb_packages(ok,value,gensymed_symbol)
    Object ok, value, gensymed_symbol;
{
    SI_Long ok_slot_coordinator_new_value, temp;

    x_note_fn_call(107,97);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(ok,Qauthorized_kb_packages);
    set_lookup_slot_value_1(ok,Qauthorized_kb_packages,value);
    if ( !TRUEP(Loading_kb_p)) {
	if (value) {
	    ok_slot_coordinator_new_value = 
		    IFIX(get_lookup_slot_value_given_default(ok,
		    Qok_slot_coordinator,FIX((SI_Long)0L))) | (SI_Long)8L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(ok,Qok_slot_coordinator);
	    set_lookup_slot_value_1(ok,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
	else {
	    temp = IFIX(get_lookup_slot_value_given_default(ok,
		    Qok_slot_coordinator,FIX((SI_Long)0L)));
	    ok_slot_coordinator_new_value = temp &  ~(SI_Long)8L;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(ok,Qok_slot_coordinator);
	    set_lookup_slot_value_1(ok,Qok_slot_coordinator,
		    FIX(ok_slot_coordinator_new_value));
	}
    }
    reformat_line_from_left(ok);
    return VALUES_1(value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Consider_asian_language_initializations_qm, Qconsider_asian_language_initializations_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Text_representation_of_our_ok_object, Qtext_representation_of_our_ok_object);

DEFINE_VARIABLE_WITH_SYMBOL(Authorized_products_of_this_machine, Qauthorized_products_of_this_machine);

Object Using_g2_ok_file_message = UNBOUND;

Object Ok_to_run_g2_message = UNBOUND;

Object Should_save_ok_file_message = UNBOUND;

Object Should_create_users_and_then_save_ok_file_message_format_control_string = UNBOUND;

Object Should_create_users_and_then_save_ok_file_message_1 = UNBOUND;

Object Should_create_users_and_then_save_ok_file_message_2 = UNBOUND;

Object Should_create_users_and_then_save_ok_file_message_3 = UNBOUND;

Object Can_create_additional_users_and_then_save_ok_file_message_format_control_string = UNBOUND;

Object Can_create_additional_users_and_then_save_ok_file_message_1 = UNBOUND;

Object Can_create_additional_users_and_then_save_ok_file_message_2 = UNBOUND;

Object G2_not_authorized_because_fails_process_count_message = UNBOUND;

Object G2_not_authorized_because_cannot_register_process_license_message = UNBOUND;

Object Keytab_backbone = UNBOUND;

Object Keytab_interface_linkage = UNBOUND;

Object Keytab_interface_inset = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Default_format_structure, Qdefault_format_structure);

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qcompletely_shut_down_g2;  /* completely-shut-down-g2 */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_29;  /* "~a" */

static Object array_constant_7;    /* # */

static Object string_constant_30;  /* "has not been valid since " */

static Object string_constant_31;  /* "will not be valid until " */

static Object array_constant_8;    /* # */

static Object Qrestricted_use;     /* restricted-use */

static Object Qinitialize_for_asian_languages;  /* initialize-for-asian-languages */

static Object string_constant_32;  /* "Your machine has already been authorized but there is ~
				    *               now an OK for this machine which is incorrect. ~
				    *               You are still authorized."
				    */

static Object string_constant_33;  /* "The authorization is not correct.  ~
				    *                   Please check it and try again."
				    */

/* REFORMAT-LINE-FROM-LEFT */
Object reformat_line_from_left(ok)
    Object ok;
{
    Object coordinator, modulus, machine_id, code_1, code_2, code_3, code_4;
    Object code_5, authorized_products, expiration_date_qm;
    Object authorized_kb_packages, number_of_processes_authorized;
    Object maximum_number_of_concurrent_floating_telewindows_allowed;
    Object make_g2_secure_qm, temp, machine_id_string, machine_id_qm;
    Object structure_being_reclaimed, temp_2, temp_3;
    Object def_structure_schedule_task_variable, svref_new_value, new_task;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object keystring, modularized_key, authorized_products_code, code_1x;
    Object code_2x, code_3x, code_4x, temp_4, checksum, date, start_date_qm;
    Object end_date_1, day, month, year, notification_text_string, system_1;
    Object option, gensymed_symbol_8, cons_1, frame_note_qm, pkg;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object visible_product, code;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    SI_Long gensymed_symbol_7, start_date, end_date;
    char temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(107,98);
    if (Loading_kb_p && system_version_greater_p(N_1_2_version,
	    System_version_from_kb_being_read)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(ok,Qok_slot_coordinator);
	set_lookup_slot_value_1(ok,Qok_slot_coordinator,FIX((SI_Long)1L));
    }
    coordinator = get_lookup_slot_value_given_default(ok,
	    Qok_slot_coordinator,FIX((SI_Long)0L));
    modulus = New_modulus;
    machine_id = get_lookup_slot_value_given_default(ok,Qmachine_id,Nil);
    code_1 = get_lookup_slot_value_given_default(ok,Qcode_1,Nil);
    code_2 = get_lookup_slot_value_given_default(ok,Qcode_2,Nil);
    code_3 = get_lookup_slot_value_given_default(ok,Qcode_3,Nil);
    code_4 = get_lookup_slot_value_given_default(ok,Qcode_4,Nil);
    code_5 = get_lookup_slot_value_given_default(ok,Qcode_5,Nil);
    authorized_products = get_lookup_slot_value_given_default(ok,
	    Qauthorized_products,Nil);
    expiration_date_qm = get_lookup_slot_value_given_default(ok,
	    Qexpiration_date_qm,Nil);
    authorized_kb_packages = get_lookup_slot_value_given_default(ok,
	    Qauthorized_kb_packages,Nil);
    number_of_processes_authorized = 
	    get_lookup_slot_value_given_default(ok,
	    Qnumber_of_processes_authorized,Nil);
    maximum_number_of_concurrent_floating_telewindows_allowed = 
	    get_lookup_slot_value_given_default(ok,
	    Qmaximum_number_of_concurrent_floating_telewindows_allowed,
	    FIX((SI_Long)0L));
    make_g2_secure_qm = get_lookup_slot_value_given_default(ok,
	    Qmake_g2_secure_qm,Nil);
    if (machine_id &&  !TRUEP(shunned_machine_id_string_p(machine_id)) && 
	    code_1 && code_2 && code_3 && code_4 && code_5 && 
	    IFIX(coordinator) > (SI_Long)0L && g2_equiv((SI_Long)0L != 
	    (IFIX(coordinator) & (SI_Long)2L) ? T : Nil,
	    authorized_products) && g2_equiv((SI_Long)0L != 
	    (IFIX(coordinator) & (SI_Long)4L) ? T : Nil,
	    expiration_date_qm) && g2_equiv((SI_Long)0L != 
	    (IFIX(coordinator) & (SI_Long)8L) ? T : Nil,
	    authorized_kb_packages) && g2_equiv((SI_Long)0L != 
	    (IFIX(coordinator) & (SI_Long)16L) ? T : Nil,
	    make_g2_secure_qm) && g2_equiv((SI_Long)0L != 
	    (IFIX(coordinator) & (SI_Long)32L) ? T : Nil,
	    number_of_processes_authorized)) {
	temp = (SI_Long)0L != (IFIX(coordinator) & (SI_Long)64L) ? T : Nil;
	temp_1 = TRUEP(g2_equiv(temp,
		FIXNUM_EQ(maximum_number_of_concurrent_floating_telewindows_allowed,
		get_slot_init_form(2,Qok,
		Qmaximum_number_of_concurrent_floating_telewindows_allowed)) 
		? Nil : 
		maximum_number_of_concurrent_floating_telewindows_allowed));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	if (expiration_date_qm) {
	    machine_id_string = get_lookup_slot_value_given_default(ok,
		    Qmachine_id,Nil);
	    temp_1 = IFIX(lengthw(machine_id_string)) > (SI_Long)5L && 
		    UBYTE_16_ISAREF_1(machine_id_string,(SI_Long)4L) == 
		    (SI_Long)58L && 
		    wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id_string,
		    (SI_Long)2L)),list_constant_1) && 
		    wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id_string,
		    (SI_Long)1L)),list_constant_2) && 
		    (UBYTE_16_ISAREF_1(machine_id_string,(SI_Long)3L) == 
		    (SI_Long)101L || UBYTE_16_ISAREF_1(machine_id_string,
		    (SI_Long)3L) == (SI_Long)69L) ? 
		    UBYTE_16_ISAREF_1(machine_id_string,(SI_Long)0L) == 
		    (SI_Long)83L || UBYTE_16_ISAREF_1(machine_id_string,
		    (SI_Long)0L) == (SI_Long)115L : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1);
	else {
	    machine_id_qm = pointer_to_first_string_in_pool_group();
	    temp = normalized_string_equal(2,machine_id_qm,
		    get_lookup_slot_value_given_default(ok,Qmachine_id,Nil));
	    reclaim_text_string(machine_id_qm);
	    temp_1 = TRUEP(temp);
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	if ((SI_Long)18L <= IFIX(THIRD(Keytab_interface_inset))) {
	    if (Nil) {
		if (EQ(Nil,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(Nil,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(Nil);
		inline_note_reclaim_cons(Nil,Nil);
		structure_being_reclaimed = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(Nil,(SI_Long)9L));
		  SVREF(Nil,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_2 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(Nil,FIX((SI_Long)0L)) = temp_2;
		temp_2 = Chain_of_available_schedule_tasks_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = Nil;
	    }
	    def_structure_schedule_task_variable = 
		    ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    if (def_structure_schedule_task_variable) {
		temp_2 = Chain_of_available_schedule_tasks_vector;
		temp_3 = Current_thread_index;
		svref_new_value = 
			ISVREF(def_structure_schedule_task_variable,
			(SI_Long)0L);
		SVREF(temp_2,temp_3) = svref_new_value;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)0L)) = 
			Qg2_defstruct_structure_name_schedule_task_g2_struct;
	    }
	    else
		def_structure_schedule_task_variable = 
			make_permanent_schedule_task_structure_internal();
	    inline_note_allocate_cons(def_structure_schedule_task_variable,
		    Nil);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = T;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    new_task = def_structure_schedule_task_variable;
	    SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
	    SVREF(new_task,FIX((SI_Long)9L)) = Nil;
	    SVREF(new_task,FIX((SI_Long)10L)) = Nil;
	    SVREF(new_task,FIX((SI_Long)7L)) = Qcompletely_shut_down_g2;
	    temp_2 = SYMBOL_FUNCTION(Qcompletely_shut_down_g2);
	    SVREF(new_task,FIX((SI_Long)8L)) = temp_2;
	    ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)0L);
	    temp_2 = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
	    SVREF(new_task,FIX((SI_Long)11L)) = temp_2;
	    temp_2 = 
		    constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
		    (SI_Long)0L),new_task);
	    SVREF(new_task,FIX((SI_Long)6L)) = temp_2;
	}
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
		  tformat(2,string_constant_29,
			  get_lookup_slot_value_given_default(ok,
			  Qmachine_id,Nil));
		  temp = FIX((SI_Long)3L);
		  if (NUM_GT(Chaining_refresh_version,temp))
		      tformat(2,string_constant_29,Chaining_refresh_list);
		  keystring = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	modularized_key = modulo_string_hash(keystring,modulus);
	authorized_products_code = 
		sort_scheduled_priorities(authorized_products);
	code_1x = IFIX(code_1) >= (SI_Long)100L ? code_1 : 
		FIX((SI_Long)394L + (SI_Long)185L * IFIX(code_1));
	code_2x = IFIX(code_2) >= (SI_Long)100L ? code_2 : 
		FIX((SI_Long)260L + (SI_Long)165L * IFIX(code_2));
	code_3x = IFIX(code_3) >= (SI_Long)100L ? code_3 : 
		FIX((SI_Long)111L + (SI_Long)64L * IFIX(code_3));
	code_4x = IFIX(code_4) >= (SI_Long)100L ? code_4 : 
		FIX((SI_Long)973L + (SI_Long)469L * IFIX(code_4));
	gensymed_symbol = IFIX(inner_multiply(modularized_key,code_3x));
	gensymed_symbol_1 = IFIX(inner_multiply(code_1x,
		authorized_products_code));
	gensymed_symbol_2 = IFIX(inner_multiply(code_2x,code_4x));
	temp_4 = expiration_date_qm;
	if (temp_4);
	else
	    temp_4 = FIX((SI_Long)0L);
	temp = expiration_date_qm;
	if (temp);
	else
	    temp = FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(inner_multiply(temp_4,temp));
	gensymed_symbol_4 = number_of_processes_authorized ? 
		IFIX(inner_multiply(code_3x,
		number_of_processes_authorized)) : (SI_Long)0L;
	gensymed_symbol_5 = number_of_processes_authorized ? 
		IFIX(inner_multiply(code_4x,
		FIX(IFIX(number_of_processes_authorized) << (SI_Long)8L))) 
		: (SI_Long)0L;
	gensymed_symbol_6 = IFIX(inner_multiply(code_1x,
		maximum_number_of_concurrent_floating_telewindows_allowed));
	gensymed_symbol_7 = IFIX(inner_multiply(code_2x,
		FIX(IFIX(maximum_number_of_concurrent_floating_telewindows_allowed) 
		<< (SI_Long)8L)));
	checksum = mod(FIX(gensymed_symbol ^ gensymed_symbol_1 ^ 
		gensymed_symbol_2 ^ gensymed_symbol_3 ^ gensymed_symbol_4 
		^ gensymed_symbol_5 ^ gensymed_symbol_6 ^ 
		gensymed_symbol_7),modulus);
	if (FIXNUM_EQ(checksum,code_5) && expiration_date_qm) {
	    date = get_universal_date();
	    if (expiration_date_qm && IFIX(expiration_date_qm) >= 
		    (SI_Long)8388608L) {
		start_date = IFIX(Reference_date_for_interval_encoding) + 
			(IFIX(expiration_date_qm) & (SI_Long)4095L);
		end_date = start_date + (IFIX(expiration_date_qm) >>  -  - 
			(SI_Long)12L & (SI_Long)2047L);
		result = VALUES_2(FIX(start_date),FIX(end_date));
	    }
	    else
		result = VALUES_2(Nil,expiration_date_qm);
	    MVS_2(result,start_date_qm,end_date_1);
	    if ((start_date_qm ? FIXNUM_LT(date,start_date_qm) : 
		    TRUEP(Nil)) || FIXNUM_GT(date,end_date_1)) {
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
		  current_wide_string = wide_string_bv16;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
			  3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  twrite_beginning_of_wide_string(array_constant_7,
				  FIX((SI_Long)35L));
			  twrite_general_string(FIXNUM_GT(date,end_date_1) 
				  ? string_constant_30 : string_constant_31);
			  result = decode_universal_date(FIXNUM_GT(date,
				  end_date_1) ? end_date_1 : start_date_qm);
			  MVS_3(result,day,month,year);
			  print_decoded_date(day,month,year);
			  twrite_beginning_of_wide_string(array_constant_8,
				  FIX((SI_Long)1L));
			  notification_text_string = 
				  copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		notify_user(2,string_constant_29,notification_text_string);
		reclaim_text_string(notification_text_string);
		temp_1 = TRUEP(T);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1);
	else {
	    if (FIXNUM_EQ(checksum,code_5) &&  ! 
		    !TRUEP(number_of_processes_authorized)) {
		if ( 
			!TRUEP(Unlimited_backtracking_in_internal_truth_maintenance_p)) 
			    {
		    system_1 = G2_product;
		    if (memq_function(Qruntime,authorized_products))
			option = G2_runtime_option;
		    else if (memq_function(Qrestricted_use,
			    authorized_products))
			option = G2_restricted_use_option;
		    else if (memq_function(Qembedded,authorized_products))
			option = G2_embedded_option;
		    else
			option = G2_development_option;
		    temp_2 = 
			    (IFIX(update_frames_needing_icp_callback(system_1,
			    option)) == (SI_Long)1L ? TRUEP(T) : 
			    TRUEP(Nil)) ? (g2ext_reduce_sleep_tolerance() 
			    != (SI_Long)-1L ? T : Nil) : Nil;
		    Unlimited_backtracking_in_internal_truth_maintenance_p 
			    = temp_2;
		}
		if ( 
			!TRUEP(Unlimited_backtracking_in_internal_truth_maintenance_p)) 
			    {
		    notify_user(1,
			    G2_not_authorized_because_cannot_register_process_license_message);
		    temp_1 = TRUEP(T);
		}
		else {
		    temp_1 =  !TRUEP(number_of_processes_authorized);
		    if (temp_1);
		    else {
			system_1 = G2_product;
			if (memq_function(Qruntime,authorized_products))
			    option = G2_runtime_option;
			else if (memq_function(Qrestricted_use,
				authorized_products))
			    option = G2_restricted_use_option;
			else if (memq_function(Qembedded,authorized_products))
			    option = G2_embedded_option;
			else
			    option = G2_development_option;
			temp = frequently_typed_characters(system_1,option);
			temp_1 = NUM_LT(temp,number_of_processes_authorized);
		    }
		    if (temp_1)
			temp_1 = TRUEP(Nil);
		    else {
			notify_user(1,
				G2_not_authorized_because_fails_process_count_message);
			temp_1 = TRUEP(T);
		    }
		}
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUM_EQ(checksum,code_5)) {
		gensymed_symbol_8 = Format_structure_description;
		M_CAR(gensymed_symbol_8) = code_5;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		temp_2 = Chaining_refresh_list;
		M_CAR(gensymed_symbol_8) = temp_2;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		temp_2 = FIXNUM_MINUS(code_4,code_5);
		M_CAR(gensymed_symbol_8) = temp_2;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		temp = get_lookup_slot_value_given_default(ok,Qmachine_id,Nil);
		temp_2 = make_array_from_strings(temp,Chaining_refresh_list);
		M_CAR(gensymed_symbol_8) = temp_2;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		temp_2 = make_array(1,FIX((SI_Long)8L));
		M_CAR(gensymed_symbol_8) = temp_2;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		temp_2 = copy_text_string(machine_id);
		M_CAR(gensymed_symbol_8) = temp_2;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		M_CAR(gensymed_symbol_8) = code_1;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		M_CAR(gensymed_symbol_8) = code_2;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		M_CAR(gensymed_symbol_8) = code_3;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		M_CAR(gensymed_symbol_8) = code_4;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		cons_1 = nth(FIX((SI_Long)10L),Format_structure_description);
		M_CAR(cons_1) = authorized_products_code;
		M_CAR(gensymed_symbol_8) = cons_1;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		M_CAR(gensymed_symbol_8) = expiration_date_qm;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		if (Current_computation_component_particulars)
		    frame_note_qm = 
			    get_particulars_of_frame_note_from_component_particulars(Qbad_package_authorization,
			    ok,Current_computation_component_particulars);
		else {
		    temp = ISVREF(ok,(SI_Long)8L);
		    frame_note_qm = getfq_function_no_default(CDR(temp),
			    Qbad_package_authorization);
		}
		pkg = Nil;
		ab_loop_list_ = authorized_kb_packages;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		pkg = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(memq_function(FIRST(pkg),frame_note_qm))) {
		    ab_loopvar__2 = LIST_1(copy_list(pkg));
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		}
		goto next_loop;
	      end_loop:
		goto end_1;
		ab_loopvar_ = Qnil;
	      end_1:;
		M_CAR(gensymed_symbol_8) = ab_loopvar_;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		M_CAR(gensymed_symbol_8) = number_of_processes_authorized;
		gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
		M_CAR(gensymed_symbol_8) = 
			maximum_number_of_concurrent_floating_telewindows_allowed;
		if ( ! !EQ(Unevaluated_expression,Within_side_limits)) {
		    if (expiration_date_qm) {
			machine_id_string = 
				get_lookup_slot_value_given_default(ok,
				Qmachine_id,Nil);
			temp_1 = IFIX(lengthw(machine_id_string)) > 
				(SI_Long)5L && 
				UBYTE_16_ISAREF_1(machine_id_string,
				(SI_Long)4L) == (SI_Long)58L && 
				wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id_string,
				(SI_Long)2L)),list_constant_1) && 
				wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id_string,
				(SI_Long)1L)),list_constant_2) && 
				(UBYTE_16_ISAREF_1(machine_id_string,
				(SI_Long)3L) == (SI_Long)101L || 
				UBYTE_16_ISAREF_1(machine_id_string,
				(SI_Long)3L) == (SI_Long)69L) ? 
				UBYTE_16_ISAREF_1(machine_id_string,
				(SI_Long)0L) == (SI_Long)83L || 
				UBYTE_16_ISAREF_1(machine_id_string,
				(SI_Long)0L) == (SI_Long)115L : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			c_nsleep(get_lookup_slot_value_given_default(ok,
				Qmachine_id,Nil));
		}
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
		  current_wide_string = wide_string_bv16;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
			  3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  print_frame(1,ok);
			  Text_representation_of_our_ok_object = 
				  copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		visible_product = Nil;
		ab_loop_list_ = authorized_products;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		visible_product = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loopvar__2 = LIST_1(visible_product);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_1;
	      end_loop_1:
		Authorized_products_of_this_machine = ab_loopvar_;
		goto end_2;
		Authorized_products_of_this_machine = Qnil;
	      end_2:;
		Floating_telewindows_limit = 
			maximum_number_of_concurrent_floating_telewindows_allowed;
		schedule_tw_modernization_tasks_if_necessary();
		temp_2 = Keytab_backbone;
		M_FOURTH(temp_2) = FIX((SI_Long)0L);
		notify_user(1,Ok_to_run_g2_message);
		code = M_CAR(M_CDR(Journal_shutout_scan_p));
		if (FIXNUMP(code) && (IFIX(code) & (SI_Long)256L) != 
			(SI_Long)0L)
		    authorize_nupec();
		Consider_asian_language_initializations_qm = T;
		if (Nil) {
		    if (EQ(Nil,Current_schedule_task))
			Current_schedule_task = Nil;
		    if (ISVREF(Nil,(SI_Long)6L))
			cancel_and_reclaim_scheduled_queue_element_1(Nil);
		    inline_note_reclaim_cons(Nil,Nil);
		    structure_being_reclaimed = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			    0);
		      reclaim_schedule_task_args(ISVREF(Nil,(SI_Long)9L));
		      SVREF(Nil,FIX((SI_Long)9L)) = Nil;
		    POP_SPECIAL();
		    temp_2 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(Nil,FIX((SI_Long)0L)) = temp_2;
		    temp_2 = Chain_of_available_schedule_tasks_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = Nil;
		}
		def_structure_schedule_task_variable = 
			ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		if (def_structure_schedule_task_variable) {
		    temp_2 = Chain_of_available_schedule_tasks_vector;
		    temp_3 = Current_thread_index;
		    svref_new_value = 
			    ISVREF(def_structure_schedule_task_variable,
			    (SI_Long)0L);
		    SVREF(temp_2,temp_3) = svref_new_value;
		    SVREF(def_structure_schedule_task_variable,
			    FIX((SI_Long)0L)) = 
			    Qg2_defstruct_structure_name_schedule_task_g2_struct;
		}
		else
		    def_structure_schedule_task_variable = 
			    make_permanent_schedule_task_structure_internal();
		inline_note_allocate_cons(def_structure_schedule_task_variable,
			Nil);
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)2L)) = T;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)9L)) = Nil;
		new_task = def_structure_schedule_task_variable;
		SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
		SVREF(new_task,FIX((SI_Long)9L)) = Nil;
		SVREF(new_task,FIX((SI_Long)10L)) = Nil;
		SVREF(new_task,FIX((SI_Long)7L)) = 
			Qinitialize_for_asian_languages;
		temp_2 = SYMBOL_FUNCTION(Qinitialize_for_asian_languages);
		SVREF(new_task,FIX((SI_Long)8L)) = temp_2;
		ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)0L);
		temp_2 = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
		SVREF(new_task,FIX((SI_Long)11L)) = temp_2;
		temp_2 = 
			constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
			(SI_Long)0L),new_task);
		SVREF(new_task,FIX((SI_Long)6L)) = temp_2;
		if ( ! !EQ(Unevaluated_expression,Within_side_limits) && 
			make_g2_secure_qm)
		    Relations_tag_list = T;
		if ( !TRUEP(Loading_kb_p)) {
		    if (make_g2_secure_qm)
			issue_mgs_notifications();
		    else
			notify_user(1,Should_save_ok_file_message);
		}
		temp_2 = Default_format_structure;
		M_THIRD(temp_2) = Nil;
		Unevaluated_expression = T;
	    }
	    else if ( !EQ(Unevaluated_expression,Within_side_limits)) {
		temp_2 = Keytab_interface_linkage;
		temp_3 = FIXNUM_ADD1(SECOND(temp_2));
		M_SECOND(temp_2) = temp_3;
		notify_user(1,string_constant_32);
	    }
	    else {
		temp_2 = Keytab_interface_linkage;
		temp_3 = FIXNUM_ADD1(SECOND(temp_2));
		M_SECOND(temp_2) = temp_3;
		notify_user(1,string_constant_33);
	    }
	}
	return reclaim_text_string(keystring);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_34;  /* "430+yw3-Ay3*Wy3=by3-8y3-Wy3=xy3=Ey3Vy3gy3ry3*8y3=Ly3-Qy3*Ny3=fy3*5y3-Sy3=-y3*cy3Hy3*Fy3*+y3*wy3=*y3=vy3=3y3-My3=Qy3=0y3*ny3-ey3-" */

static Object string_constant_35;  /* "fy3-Gyq3-Py3ay3*Sy3*Yy3*Oy3*hy3=wy3=Ny3=ly3=dy3*4y3Wy3=hy3*my3=1y3*ay3wy3-By3*Py3Dy3=6y3=qy3=Zy3=2y3-hy3*Ty3=ay3Ly3=Cy3*0y3=oy3-" */

static Object string_constant_36;  /* "+y3-by3-py3=8y3*Ly3*7y3=Hy3-ry3ky3-Ty3*ry3*-y3-Eyy3-Fy3=uyu3=4y3=Fy3Ky3*Jy3Zyr3-sy3*gy3*Ry3ey3-=y3=My3*py3-cy3Oy3Py3Qy3Iy3dynk3=" */

static Object string_constant_37;  /* "Ry3*ty3*Uy3*ey3sy3-Iy3-7y3*Ky3My3my3*vy3=Ky3*jy3-wy3=ky3Jy3cy3hy3*oy3=Dy3*Vy3xy3-Uy3Ty3=Oy3=sy3*dy3*Hyp3iy3-Ry3=Yy3=ty3=Gy3-6y3S" */

static Object string_constant_38;  /* "y3=5y3-gy3-Yy3Ey3**y3fy3*Gy3*Iy3-9ys3=ry3Gy3=Wy3=jy3*Eym3=Xy3*Ay3*ly3=Sy3*Dy3-Ly3-myt3vy3ly3-1y3qy3-Ny3*qy3*1y3-ky3=Py3=my3ty3=T" */

static Object string_constant_39;  /* "y3=9y3Ry3*Cy3*xy3*=y3*6y3Yyv3=7y3Cy3-3y3-xy3=py3=ny3==y3=gy3*uy3-Dy3*kylo3-Jy3--y3-ny3-Hy3-jy3*3y3=Vy3Fy3-uy3-oy3-5y3*9y3by3-ty3" */

static Object string_constant_40;  /* "=ey3*by3-Vy3*sy3-Cy3-vy3-ly3*2y3*Qy3oy3Xy3=Ay3=iy3-2yx3jy3=cy3*iy3-Xy3-Zy3-dy3*By3=Iy3-Ky3*fy3-qy3*My3-iy3-Oy3-0y3*Zyz3py3Ny3ny3" */

static Object string_constant_41;  /* "=By3=Uy3Uy3-*y3=Jy3-4y3-ay3uy3=+y3*Xy" */

static Object string_constant_42;  /* "Ry3*ty3*Uy3*ey3sy3-Iy3-7y3*Ky3My3my3*vy3=Ky3*jy3-wy3=ky3Jy3cy3hy3*oy3=Dy3*Vy3xy3-Uy3Ty3=Oy3=sy3*dy3*Hyp3iy3-Ry3=Yy3=ty3=Gy3=5y3-" */

static Object string_constant_43;  /* "gy3-Yy3Ey3**y3fy3*Gy3*Iy3-9ys3=ry3Gy3=Wy3=jy3*Eym3=Xy3*Ay3*ly3=Sy3*Dy3-Ly3-myt3vy3ly3-1y3qy3-Ny3*qy3*1y3-ky3=Py3=my3ty3=Ty3=9y3R" */

static Object string_constant_44;  /* "y3*Cy3*xy3*=y3*6y3Yyv3=7y3Cy3-3y3-6y3Sy3-xy3=py3=ny3==y3=gy3*uy3-Dy3*kylo3-Jy3--y3-ny3-Hy3-jy3*3y3=Vy3Fy3-uy3-oy3-5y3*9y3by3-ty3" */

static Object string_constant_45;  /* "+y3-by3-py3=8y3*Ly3*7y3=Hy3-ry3ky3-Ty3*ry3*-y3-Eyy3-Fy3=uyu3=4y3=Fy3Ky3*Jy3Zyr3*gy3-sy3*Ry3ey3-=y3=My3*py3-cy3Oy3Py3Qy3Iy3dynk3=" */

static Object string_constant_46;  /* "Ry3*ty3*Uy3*ey3sy3-Iy3-7y3*Ky3My3my3*vy3=Ky3*jy3-wy3=ky3Jy3cy3hy3*oy3=Dy3*Vy3xy3-Uy3Ty3=Oy3=sy3iy3-Ry3=Yy3=ty3=Gy3=5y3-gy3-Yy3Ey" */

static Object string_constant_47;  /* "3**y3fy3*Gy3*Iy3-9ys3=ry3Gy3=Wy3=jy3*Eym3=Xy3*Ay3*ly3=Sy3*Dy3-Ly3-myt3vy3ly3-1y3qy3-Ny3*qy3*1y3-ky3=Py3=my3ty3=Ty3=9y3Ry3*Cy3*xy" */

static Object string_constant_48;  /* "3*=y3*6y3Yyv3=7y3Cy3-3y3-6y3Sy3*dy3*Hyp3-xy3=py3=ny3==y3=gy3*uy3-Dy3*kylo3-Jy3--y3-ny3-Hy3-jy3*3y3=Vy3Fy3-uy3-oy3-5y3*9y3by3-ty3" */

static Object string_constant_49;  /* "Ry3*ty3*ey3*Uy3sy3-Iy3-7y3*Ky3My3my3*vy3=Ky3*jy3-wy3=ky3Jy3cy3hy3*oy3=Dy3*Vy3xy3-Uy3Ty3=Oy3=sy3iy3-Ry3=Yy3=ty3=Gy3=5y3-gy3-Yy3Ey" */

static Object string_constant_50;  /* "3*=y3*6y3Yyv3=7y3Cy3-3y3-6y3Sy3*dy3*Hyp3-xy3=py3=ny3==y3=gy3*uy3-Dy3*kylo3-Jy3--y3-ny3-Hy3-jy3*3y3=Vy3Fy3-uy3-oy3-5y3*9y3-ly3*2y" */

static Object string_constant_51;  /* "3*Qy3by3-ty3=ey3*by3-Vy3*sy3-Cy3-vy3oy3Xy3=Ay3=iy3-2yx3jy3=cy3*iy3-Xy3-Zy3-dy3*By3=Iy3-Ky3*fy3-qy3*My3-iy3-Oy3-0y3*Zyz3py3Ny3ny3" */

/* CHOOSE-KEYTAB */
Object choose_keytab()
{
    x_note_fn_call(107,99);
    if ( !(FIXNUMP(Chaining_refresh_version) && 
	    FIXNUM_LE(FIX((SI_Long)-128L),Chaining_refresh_version) && 
	    FIXNUM_LE(Chaining_refresh_version,FIX((SI_Long)127L))))
	return error((SI_Long)2L,"unknown version: ~d",
		Chaining_refresh_version);
    else
	switch (INTEGER_TO_CHAR(Chaining_refresh_version)) {
	  case 3:
	    return regenerate_optimized_constant(list(8,string_constant_34,
		    string_constant_35,string_constant_36,
		    string_constant_37,string_constant_38,
		    string_constant_39,string_constant_40,string_constant_41));
	  case 4:
	    return regenerate_optimized_constant(list(8,string_constant_34,
		    string_constant_35,string_constant_36,
		    string_constant_42,string_constant_43,
		    string_constant_44,string_constant_40,string_constant_41));
	  case 5:
	    return regenerate_optimized_constant(list(8,string_constant_34,
		    string_constant_35,string_constant_45,
		    string_constant_42,string_constant_43,
		    string_constant_44,string_constant_40,string_constant_41));
	  case 6:
	    return regenerate_optimized_constant(list(8,string_constant_34,
		    string_constant_35,string_constant_45,
		    string_constant_42,string_constant_43,
		    string_constant_44,string_constant_40,string_constant_41));
	  case 8:
	    return regenerate_optimized_constant(list(8,string_constant_34,
		    string_constant_35,string_constant_45,
		    string_constant_46,string_constant_47,
		    string_constant_48,string_constant_40,string_constant_41));
	  case 9:
	  case 12:
	    return regenerate_optimized_constant(list(8,string_constant_34,
		    string_constant_35,string_constant_45,
		    string_constant_49,string_constant_47,
		    string_constant_48,string_constant_40,string_constant_41));
	  case 11:
	    return regenerate_optimized_constant(list(8,string_constant_34,
		    string_constant_35,string_constant_45,
		    string_constant_46,string_constant_47,
		    string_constant_50,string_constant_51,string_constant_41));
	  default:
	    return error((SI_Long)2L,"unknown version: ~d",
		    Chaining_refresh_version);
	}
}

DEFINE_VARIABLE_WITH_SYMBOL(Keytab1, Qkeytab1);

/* LIMITED-TRUE-LIST-P */
Object limited_true_list_p(x,n_1)
    Object x, n_1;
{
    Object y;
    SI_Long i;

    x_note_fn_call(107,100);
    y = x;
    i = (SI_Long)0L;
  next_loop:
    if (i > IFIX(n_1))
	return VALUES_1(Nil);
    else if ( !TRUEP(y))
	return VALUES_1(T);
    else if (ATOM(y))
	return VALUES_1(Nil);
    y = CDR(y);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Redef_class_instance, Qredef_class_instance);

DEFINE_VARIABLE_WITH_SYMBOL(System_slot_accessor, Qsystem_slot_accessor);

DEFINE_VARIABLE_WITH_SYMBOL(Color_code_differences, Qcolor_code_differences);

DEFINE_VARIABLE_WITH_SYMBOL(Alternate_chaining_queue, Qalternate_chaining_queue);

DEFINE_VARIABLE_WITH_SYMBOL(Revert_to_fuzzy_cache_p, Qrevert_to_fuzzy_cache_p);

/* CALL-POST-PROMINENT-NOTIFICATION */
Object call_post_prominent_notification(a,b,c,d)
    Object a, b, c, d;
{
    Object temp;

    x_note_fn_call(107,101);
    temp = post_prominent_notification(4,a,b,c,d);
    return VALUES_1(temp);
}

/* REDRAW-SOLID-RECTANGLES-WITHOUT-OVERLAP */
Object redraw_solid_rectangles_without_overlap(class_1)
    Object class_1;
{
    Object class_description, cdr_arg, temp;

    x_note_fn_call(107,102);
    if (SECOND(Workspace_image_plane_per_window)) {
	class_description = 
		lookup_global_or_kb_specific_property_value(Qvariable,
		Class_description_gkbprop);
	redraw_solid_rectangles_without_overlap_1(ISVREF(class_description,
		(SI_Long)6L));
	Available_gensym_conses = make_permanent_list(FIX((SI_Long)5L));
	cdr_arg = last(Available_gensym_conses,_);
	temp = Available_gensym_conses;
	M_CDR(cdr_arg) = temp;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qcall_post_prominent_notification;  /* call-post-prominent-notification */

static Object Qredraw_solid_rectangles_without_overlap;  /* redraw-solid-rectangles-without-overlap */

/* REPLACE-FORMAT-USING-EQUIVALENT-FONT */
Object replace_format_using_equivalent_font(class_1)
    Object class_1;
{
    Object cons_1, ab_loop_iter_flag_, temp, old, new_1;
    Object def_structure_schedule_task_variable, svref_arg_2, svref_new_value;
    Object task, structure_being_reclaimed;
    SI_Long i;
    char svref_new_value_1;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(107,103);
    if ( !TRUEP(System_is_running)) {
	Unevaluated_expression = Within_side_limits;
	cons_1 = Format_structure_description;
	i = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(cons_1))
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    i = i + (SI_Long)1L;
	if (i == (SI_Long)10L) {
	    temp = CAR(cons_1);
	    M_CAR(temp) = FIX((SI_Long)0L);
	}
	else
	    M_CAR(cons_1) = Nil;
	ab_loop_iter_flag_ = Nil;
	cons_1 = M_CDR(cons_1);
	goto next_loop;
      end_loop:;
    }
    if (System_is_running || System_has_paused) {
	temp = Workspace_image_plane_per_window;
	M_SECOND(temp) = T;
	old = Nil;
	new_1 = Nil;
      next_loop_1:
	old = Alternate_chaining_queue;
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
	aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) + 2.0;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qcall_post_prominent_notification;
	temp = SYMBOL_FUNCTION(Qcall_post_prominent_notification);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)4L);
	temp = copy_text_string(SECOND(Color_code_differences));
	SVREF(task,FIX((SI_Long)13L)) = temp;
	ISVREF(task,(SI_Long)14L) = FIX((SI_Long)900L);
	ISVREF(task,(SI_Long)15L) = FIX((SI_Long)700L);
	SVREF(task,FIX((SI_Long)16L)) = T;
	new_1 = task;
	if (CAS_SYMBOL(Qalternate_chaining_queue,old,new_1)) {
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
	    goto end_1;
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
	goto next_loop_1;
      end_loop_1:
      end_1:;
	old = Nil;
	new_1 = Nil;
      next_loop_2:
	old = Revert_to_fuzzy_cache_p;
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
	aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) + 4.0;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = 
		Qredraw_solid_rectangles_without_overlap;
	temp = SYMBOL_FUNCTION(Qredraw_solid_rectangles_without_overlap);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = Nil;
	new_1 = task;
	if (CAS_SYMBOL(Qrevert_to_fuzzy_cache_p,old,new_1)) {
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
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* REDRAW-SOLID-RECTANGLES-WITHOUT-OVERLAP-1 */
Object redraw_solid_rectangles_without_overlap_1(x)
    Object x;
{
    Object temp;

    x_note_fn_call(107,104);
    temp = CAR(x);
    if (ATOM(temp))
	M_CAR(x) = Nil;
    else
	redraw_solid_rectangles_without_overlap_1(CAR(x));
    temp = CDR(x);
    if (ATOM(temp))
	return VALUES_1(M_CDR(x) = Nil);
    else
	return redraw_solid_rectangles_without_overlap_1(CDR(x));
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_matching_machine_id_qm, Qcached_matching_machine_id_qm);

/* MATCH-MACHINE-ID-FOR-THIS-MACHINE-ONLINE */
Object match_machine_id_for_this_machine_online(finger,array)
    Object finger, array;
{
    Object length1, length2, nlength1, nlength2, w1, w2, i1, i2, temp, temp_1;
    volatile Object ids;
    Object id, ab_loop_list_;
    SI_Long length_1, i, ab_loop_bind_, ab_loopvar_;
    char temp_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(107,105);
    SAVE_STACK();
    if (Cached_matching_machine_id_qm) {
	length1 = lengthw(Cached_matching_machine_id_qm);
	length2 = lengthw(finger);
	length_1 = IFIX(lengthw(Cached_matching_machine_id_qm));
	i = (SI_Long)0L;
	ab_loop_bind_ = length_1;
	ab_loopvar_ = (SI_Long)0L;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if (digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(Cached_matching_machine_id_qm,
		i)),FIX((SI_Long)36L)))
	    ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	nlength1 = FIX(ab_loopvar_);
	goto end_1;
	nlength1 = Qnil;
      end_1:;
	length_1 = IFIX(lengthw(finger));
	i = (SI_Long)0L;
	ab_loop_bind_ = length_1;
	ab_loopvar_ = (SI_Long)0L;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	if (digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(finger,i)),
		FIX((SI_Long)36L)))
	    ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	nlength2 = FIX(ab_loopvar_);
	goto end_2;
	nlength2 = Qnil;
      end_2:;
	w1 = Nil;
	w2 = Nil;
	i1 = FIX((SI_Long)0L);
	i2 = FIX((SI_Long)0L);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(nlength1);
	if (FIXNUM_NE(length(array),FIXNUM_ADD(nlength1,nlength2))) {
	    RESTORE_STACK();
	    return VALUES_1(Nil);
	}
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
      next_loop_3:
	if (FIXNUM_GE(i1,length1))
	    goto end_loop_3;
	w1 = 
		digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(Cached_matching_machine_id_qm,
		IFIX(i1))),FIX((SI_Long)36L));
	if (w1) {
	    i1 = FIXNUM_ADD1(i1);
	    goto end_3;
	}
	i1 = FIXNUM_ADD1(i1);
	goto next_loop_3;
      end_loop_3:
	w1 = Nil;
      end_3:
	if (FIXNUM_NE(aref1(array,FIX(i)),i == (SI_Long)0L ? w1 : 
		chestnut_modf_function(FIX((SI_Long)3769L * 
		IFIX(aref1(array,FIX(i - (SI_Long)1L))) + (SI_Long)6237L * 
		IFIX(w1)),FIX((SI_Long)256L)))) {
	    RESTORE_STACK();
	    return VALUES_1(Nil);
	}
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	i = IFIX(nlength1);
	ab_loop_bind_ = IFIX(nlength2);
      next_loop_4:
	if (i >= ab_loop_bind_)
	    goto end_loop_4;
      next_loop_5:
	if (FIXNUM_GE(i2,length2))
	    goto end_loop_5;
	w2 = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(finger,
		IFIX(i2))),FIX((SI_Long)36L));
	if (w2) {
	    i2 = FIXNUM_ADD1(i2);
	    goto end_4;
	}
	i2 = FIXNUM_ADD1(i2);
	goto next_loop_5;
      end_loop_5:
	w2 = Nil;
      end_4:
	temp = aref1(array,FIX(i));
	temp_1 = chestnut_modf_function(FIX((SI_Long)3769L * 
		IFIX(aref1(array,FIX(i - (SI_Long)1L))) + (SI_Long)6237L * 
		IFIX(w2)),FIX((SI_Long)256L));
	if (NUM_NE(temp,temp_1)) {
	    RESTORE_STACK();
	    return VALUES_1(Nil);
	}
	i = i + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:
	RESTORE_STACK();
	return VALUES_1(T);
	RESTORE_STACK();
	return VALUES_1(Qnil);
	RESTORE_STACK();
	return VALUES_1(Qnil);
    }
    else {
	ids = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    ids = get_local_machine_ids_as_gensym_list();
	    id = Nil;
	    ab_loop_list_ = ids;
	  next_loop_6:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_6;
	    id = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    length1 = lengthw(id);
	    length2 = lengthw(finger);
	    length_1 = IFIX(lengthw(id));
	    i = (SI_Long)0L;
	    ab_loop_bind_ = length_1;
	    ab_loopvar_ = (SI_Long)0L;
	  next_loop_7:
	    if (i >= ab_loop_bind_)
		goto end_loop_7;
	    if (digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(id,i)),
		    FIX((SI_Long)36L)))
		ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	    i = i + (SI_Long)1L;
	    goto next_loop_7;
	  end_loop_7:
	    nlength1 = FIX(ab_loopvar_);
	    goto end_5;
	    nlength1 = Qnil;
	  end_5:;
	    length_1 = IFIX(lengthw(finger));
	    i = (SI_Long)0L;
	    ab_loop_bind_ = length_1;
	    ab_loopvar_ = (SI_Long)0L;
	  next_loop_8:
	    if (i >= ab_loop_bind_)
		goto end_loop_8;
	    if (digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(finger,i)),
		    FIX((SI_Long)36L)))
		ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	    i = i + (SI_Long)1L;
	    goto next_loop_8;
	  end_loop_8:
	    nlength2 = FIX(ab_loopvar_);
	    goto end_6;
	    nlength2 = Qnil;
	  end_6:;
	    w1 = Nil;
	    w2 = Nil;
	    i1 = FIX((SI_Long)0L);
	    i2 = FIX((SI_Long)0L);
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(nlength1);
	    if (FIXNUM_NE(length(array),FIXNUM_ADD(nlength1,nlength2))) {
		temp_2 = TRUEP(Nil);
		goto end_7;
	    }
	  next_loop_9:
	    if (i >= ab_loop_bind_)
		goto end_loop_9;
	  next_loop_10:
	    if (FIXNUM_GE(i1,length1))
		goto end_loop_10;
	    w1 = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(id,
		    IFIX(i1))),FIX((SI_Long)36L));
	    if (w1) {
		i1 = FIXNUM_ADD1(i1);
		goto end_8;
	    }
	    i1 = FIXNUM_ADD1(i1);
	    goto next_loop_10;
	  end_loop_10:
	    w1 = Nil;
	  end_8:
	    if (FIXNUM_NE(aref1(array,FIX(i)),i == (SI_Long)0L ? w1 : 
		    chestnut_modf_function(FIX((SI_Long)3769L * 
		    IFIX(aref1(array,FIX(i - (SI_Long)1L))) + 
		    (SI_Long)6237L * IFIX(w1)),FIX((SI_Long)256L)))) {
		temp_2 = TRUEP(Nil);
		goto end_7;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_9;
	  end_loop_9:
	    i = IFIX(nlength1);
	    ab_loop_bind_ = IFIX(nlength2);
	  next_loop_11:
	    if (i >= ab_loop_bind_)
		goto end_loop_11;
	  next_loop_12:
	    if (FIXNUM_GE(i2,length2))
		goto end_loop_12;
	    w2 = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(finger,
		    IFIX(i2))),FIX((SI_Long)36L));
	    if (w2) {
		i2 = FIXNUM_ADD1(i2);
		goto end_9;
	    }
	    i2 = FIXNUM_ADD1(i2);
	    goto next_loop_12;
	  end_loop_12:
	    w2 = Nil;
	  end_9:
	    temp = aref1(array,FIX(i));
	    temp_1 = chestnut_modf_function(FIX((SI_Long)3769L * 
		    IFIX(aref1(array,FIX(i - (SI_Long)1L))) + 
		    (SI_Long)6237L * IFIX(w2)),FIX((SI_Long)256L));
	    if (NUM_NE(temp,temp_1)) {
		temp_2 = TRUEP(Nil);
		goto end_10;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_11;
	  end_loop_11:
	    temp_2 = TRUEP(T);
	    goto end_10;
	    temp_2 = TRUEP(Qnil);
	  end_10:;
	    goto end_7;
	    temp_2 = TRUEP(Qnil);
	  end_7:;
	    if (temp_2) {
		Cached_matching_machine_id_qm = copy_text_string(id);
		SAVE_VALUES(VALUES_1(T));
		goto end_11;
	    }
	    goto next_loop_6;
	  end_loop_6:
	    SAVE_VALUES(VALUES_1(Qnil));
	  end_11:;
	}
	POP_UNWIND_PROTECT(0);
	if (ids) {
	    if ( !EQ(ids,Qunbound_in_protected_let))
		reclaim_gensym_tree_with_text_strings(ids);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Grammar_rules_to_add_for_nupec_after_authorization, Qgrammar_rules_to_add_for_nupec_after_authorization);

/* ADD-GRAMMAR-RULES-FOR-NUPEC-AFTER-AUTHORIZATION */
Object add_grammar_rules_for_nupec_after_authorization(grammar_rules)
    Object grammar_rules;
{
    Object new_rule, ab_loop_list_, l, old_rule, temp, temp_1;
    char temp_2;

    x_note_fn_call(107,106);
    new_rule = Nil;
    ab_loop_list_ = grammar_rules;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    new_rule = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    l = Grammar_rules_to_add_for_nupec_after_authorization;
    old_rule = Nil;
  next_loop_1:
    if ( !TRUEP(l))
	goto end_loop_1;
    old_rule = CAR(l);
    if (EQ(FIRST(new_rule),FIRST(old_rule))) {
	temp = SECOND(new_rule);
	temp_1 = SECOND(old_rule);
	temp_2 = EQUAL(temp,temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	M_CAR(l) = new_rule;
	goto end_1;
    }
    l = M_CDR(l);
    goto next_loop_1;
  end_loop_1:
    Grammar_rules_to_add_for_nupec_after_authorization = 
	    nconc2(Grammar_rules_to_add_for_nupec_after_authorization,
	    LIST_1(new_rule));
  end_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_52;  /* "NUPEC" */

/* AUTHORIZE-NUPEC */
Object authorize_nupec()
{
    x_note_fn_call(107,107);
    add_grammar_rules_function(Grammar_rules_to_add_for_nupec_after_authorization);
    if ( !TRUEP(search(2,string_constant_52,machine_model()))) {
	Machine_model_var = format((SI_Long)3L,Nil,"~a NUPEC",machine_model());
	return VALUES_1(Machine_model_var);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Daily_countdown, Qdaily_countdown);

DEFINE_VARIABLE_WITH_SYMBOL(Hourly_countdown, Qhourly_countdown);

DEFINE_VARIABLE_WITH_SYMBOL(Hour_of_last_message, Qhour_of_last_message);

DEFINE_VARIABLE_WITH_SYMBOL(Operative_task_list, Qoperative_task_list);

DEFINE_VARIABLE_WITH_SYMBOL(Smoothed_subsecond_adjustment, Qsmoothed_subsecond_adjustment);

/* PRINT-MESSAGE-WITH-LIST */
Object print_message_with_list(list_1,text)
    Object list_1, text;
{
    x_note_fn_call(107,108);
    twrite(text);
    return print_list_without_message(list_1);
}

static Object string_constant_53;  /* "~(~a~)      " */

static Object string_constant_54;  /* "Start date: " */

static Object string_constant_55;  /* "      End date: " */

static Object string_constant_56;  /* "~%~%" */

/* PRINT-LIST-WITHOUT-MESSAGE */
Object print_list_without_message(list_1)
    Object list_1;
{
    Object authorizations, package_name_1, ab_loop_list_, authorization_qm;
    Object start_date_qm, end_date_qm, d, m, y;
    Object result;

    x_note_fn_call(107,109);
    authorizations = THIRD(Local_recovery_list);
    package_name_1 = Nil;
    ab_loop_list_ = list_1;
    authorization_qm = Nil;
    start_date_qm = Nil;
    end_date_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    package_name_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    authorization_qm = assq_function(package_name_1,authorizations);
    start_date_qm = FIFTH(authorization_qm);
    end_date_qm = SIXTH(authorization_qm);
    tformat(2,string_constant_53,package_name_1);
    if (start_date_qm) {
	twrite(string_constant_54);
	result = decode_universal_date(start_date_qm);
	MVS_3(result,d,m,y);
	print_decoded_date(d,m,y);
	tformat(1,string_constant_55);
	result = decode_universal_date(end_date_qm);
	MVS_3(result,d,m,y);
	print_decoded_date(d,m,y);
    }
    tformat(1,string_constant_56);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_57;  /* "The license to use G2 on this machine has expired.~%" */

static Object string_constant_58;  /* "G2 is not licensed to run with the package ~(~a~).~%" */

static Object string_constant_59;  /* "The license to use the package ~(~a~) has expired.~%" */

static Object string_constant_60;  /* "The license to use the package ~(~a~) has not yet begun.~%" */

static Object string_constant_61;  /* "G2 cannot be started or resumed." */

/* WARN-UPON-START-OR-RESUME */
Object warn_upon_start_or_resume()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object expiration_qm, today, license_expiration_qm, gensymed_symbol;
    Object days_left_qm, authorized_package_list, existing_package;
    Object ab_loop_list_, package_name_1, start_date_qm, end_date_qm;
    Object ab_loop_desetq_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, start_date;
    SI_Long end_date;
    Declare_special(5);
    Object result;

    x_note_fn_call(107,110);
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
	      expiration_qm = FOURTH(End_of_recovery_list);
	      today = get_universal_date();
	      if ( !TRUEP(expiration_qm))
		  license_expiration_qm = Nil;
	      else if (expiration_qm && IFIX(expiration_qm) >= 
		      (SI_Long)8388608L) {
		  start_date = IFIX(Reference_date_for_interval_encoding) 
			  + (IFIX(expiration_qm) & (SI_Long)4095L);
		  end_date = start_date + (IFIX(expiration_qm) >>  -  - 
			  (SI_Long)12L & (SI_Long)2047L);
		  result = VALUES_2(FIX(start_date),FIX(end_date));
		  gensymed_symbol = NTH_VALUE((SI_Long)1L, result);
		  license_expiration_qm = gensymed_symbol;
	      }
	      else
		  license_expiration_qm = expiration_qm;
	      days_left_qm = license_expiration_qm && 
		      FIXNUMP(license_expiration_qm) ? 
		      FIXNUM_MINUS(license_expiration_qm,today) : Nil;
	      authorized_package_list = THIRD(Local_recovery_list);
	      existing_package = Nil;
	      ab_loop_list_ = Control_sequence_record;
	      package_name_1 = Nil;
	      start_date_qm = Nil;
	      end_date_qm = Nil;
	      ab_loop_desetq_ = Nil;
	      if (days_left_qm && IFIX(days_left_qm) < (SI_Long)0L)
		  tformat(1,string_constant_57);
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      ab_loop_desetq_ = M_CAR(ab_loop_list_);
	      existing_package = CAR(ab_loop_desetq_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      ab_loop_desetq_ = assq_function(existing_package,
		      authorized_package_list);
	      package_name_1 = CAR(ab_loop_desetq_);
	      temp = CDR(ab_loop_desetq_);
	      temp = CDR(temp);
	      temp = CDR(temp);
	      temp = CDR(temp);
	      start_date_qm = CAR(temp);
	      temp = CDR(ab_loop_desetq_);
	      temp = CDR(temp);
	      temp = CDR(temp);
	      temp = CDR(temp);
	      temp = CDR(temp);
	      end_date_qm = CAR(temp);
	      if ( !TRUEP(package_name_1))
		  tformat(2,string_constant_58,existing_package);
	      if (package_name_1 && end_date_qm && FIXNUM_LT(end_date_qm,
		      today))
		  tformat(2,string_constant_59,existing_package);
	      if (package_name_1 && start_date_qm && 
		      FIXNUM_GT(start_date_qm,today))
		  tformat(2,string_constant_60,existing_package);
	      goto next_loop;
	    end_loop:
	      twrite(string_constant_61);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return post_prominent_notification(1,temp);
}

/* COMPILE-USER-PASSWORD-FOR-SLOT */
Object compile_user_password_for_slot varargs_1(int, n)
{
    Object translation, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(107,111);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(translation,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(translation);
}

/* WRITE-USER-PASSWORD-FROM-SLOT */
Object write_user_password_from_slot(translation,gensymed_symbol)
    Object translation, gensymed_symbol;
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long ab_loop_repeat_, thing;

    x_note_fn_call(107,112);
    if ( ! !TRUEP(translation)) {
	ab_loop_repeat_ = IFIX(lengthw(stringw(translation)));
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)42L;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)42L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COMPILE-PERMITTED-MODE-LIST-FOR-SLOT */
Object compile_permitted_mode_list_for_slot varargs_1(int, n)
{
    Object translation, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(107,113);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_symbol_list(translation);
}

/* WRITE-PERMITTED-MODE-LIST-FROM-SLOT */
Object write_permitted_mode_list_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(107,114);
    return write_symbol_list(1,value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Time_of_last_call_to_set_user_password, Qtime_of_last_call_to_set_user_password);

Object Required_delay_between_calls_to_set_password = UNBOUND;

static Object Qattempting_to_set_user_password_too_fast;  /* attempting-to-set-user-password-too-fast */

/* SET-USER-PASSWORD */
Object set_user_password(user,clear_old_password,clear_new_password)
    Object user, clear_old_password, clear_new_password;
{
    Object aref_arg_1;
    double now, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(107,115);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	now = g2ext_unix_time_as_float();
	arg = now;
	arg_1 = DFLOAT_ISAREF_1(Time_of_last_call_to_set_user_password,
		(SI_Long)0L) + 
		DFLOAT_ISAREF_1(Required_delay_between_calls_to_set_password,
		(SI_Long)0L);
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    aref_arg_1 = Time_of_last_call_to_set_user_password;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,now);
	    result = encode_and_check_password_change_information(3,user,
		    clear_old_password,clear_new_password);
	}
	else
	    result = VALUES_2(Nil,Qattempting_to_set_user_password_too_fast);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* VALID-USER-AND-PASSWORD-P */
Object valid_user_and_password_p(user_name,clear_password)
    Object user_name, clear_password;
{
    Object aref_arg_1, encoded_password;
    double now, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(107,116);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	now = g2ext_unix_time_as_float();
	arg = now;
	arg_1 = DFLOAT_ISAREF_1(Time_of_last_call_to_set_user_password,
		(SI_Long)0L) + 
		DFLOAT_ISAREF_1(Required_delay_between_calls_to_set_password,
		(SI_Long)0L);
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    aref_arg_1 = Time_of_last_call_to_set_user_password;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,now);
	    encoded_password = encode_password_via_md5(user_name,
		    clear_password,Nil);
	    result = validate_user_and_password(2,user_name,encoded_password);
	}
	else
	    result = VALUES_1(Qattempting_to_set_user_password_too_fast);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Authorized_users_list, Qauthorized_users_list);

DEFINE_VARIABLE_WITH_SYMBOL(Updated_users_list, Qupdated_users_list);

/* AUTHORIZED-USER-P */
Object authorized_user_p(user_name)
    Object user_name;
{
    x_note_fn_call(107,117);
    return assq_function(user_name,Authorized_users_list);
}

/* MAKE-USER-OK-ENTRY */
Object make_user_ok_entry(user_entry_user_name,user_entry_encoded_password,
	    user_entry_password_validity,user_entry_user_modes)
    Object user_entry_user_name, user_entry_encoded_password;
    Object user_entry_password_validity, user_entry_user_modes;
{
    x_note_fn_call(107,118);
    return gensym_cons_1(user_entry_user_name,
	    gensym_cons_1(user_entry_encoded_password,
	    gensym_cons_1(user_entry_password_validity,
	    user_entry_user_modes)));
}

/* USERS-AUTHORIZED-PASSWORD */
Object users_authorized_password(user_name)
    Object user_name;
{
    Object authorization_entry_qm, temp;

    x_note_fn_call(107,119);
    authorization_entry_qm = assq_function(user_name,Authorized_users_list);
    if (authorization_entry_qm) {
	temp = CDR(authorization_entry_qm);
	return VALUES_1(CAR(temp));
    }
    else
	return VALUES_1(Nil);
}

/* ENTER-AUTHORIZED-USER */
Object enter_authorized_user(name,encoded_password,user_modes,
	    password_validity,original_p)
    Object name, encoded_password, user_modes, password_validity, original_p;
{
    Object entry_qm, temp, password_string, earlier_user_modes, car_arg;
    Object new_user_entry;

    x_note_fn_call(107,120);
    entry_qm = original_p ? assq_function(name,Authorized_users_list) : 
	    assq_function(name,Updated_users_list);
    if (password_validity && IFIX(password_validity) == (SI_Long)0L)
	password_validity = Nil;
    if (entry_qm) {
	temp = CDR(entry_qm);
	password_string = CAR(temp);
	earlier_user_modes = CDDDR(entry_qm);
	temp = CDDR(entry_qm);
	password_validity = CAR(temp);
	car_arg = CDR(entry_qm);
	M_CAR(car_arg) = encoded_password;
	M_CDDDR(entry_qm) = user_modes;
	car_arg = CDDR(entry_qm);
	M_CAR(car_arg) = password_validity;
	reclaim_wide_string(password_string);
	return reclaim_gensym_list_1(earlier_user_modes);
    }
    else {
	new_user_entry = make_user_ok_entry(name,encoded_password,
		password_validity,user_modes);
	if (original_p) {
	    Authorized_users_list = gensym_cons_1(new_user_entry,
		    Authorized_users_list);
	    return VALUES_1(Authorized_users_list);
	}
	else {
	    Updated_users_list = gensym_cons_1(new_user_entry,
		    Updated_users_list);
	    return VALUES_1(Updated_users_list);
	}
    }
}

/* REMOVE-AUTHORIZED-USER */
Object remove_authorized_user(user_name)
    Object user_name;
{
    Object entry_qm;

    x_note_fn_call(107,121);
    entry_qm = assq_function(user_name,Authorized_users_list);
    if (entry_qm) {
	Authorized_users_list = delete_gensym_element_1(entry_qm,
		Authorized_users_list);
	reclaim_gensym_list_1(entry_qm);
	return propagate_changes_in_authorization_to_logged_in_users(Nil,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-OK-USER-DATA */
Object update_ok_user_data()
{
    Object users_added, users_with_additional_modes, old_entry, entry;
    Object ab_loop_list_, old_modes, mode, ab_loop_list__1, old_user_data;
    Object password_string, mode_list, temp;

    x_note_fn_call(107,122);
    users_added = Nil;
    users_with_additional_modes = Nil;
    old_entry = Nil;
    entry = Nil;
    ab_loop_list_ = Updated_users_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    old_entry = assq_function(CAR(entry),Authorized_users_list);
    if ( !TRUEP(old_entry))
	users_added = gensym_cons_1(CAR(entry),users_added);
    else {
	old_modes = CDDDR(old_entry);
	mode = Nil;
	ab_loop_list__1 = CDDDR(entry);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	mode = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(memq_function(mode,old_modes)))
	    users_with_additional_modes = gensym_cons_1(CAR(entry),
		    users_with_additional_modes);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    old_user_data = Authorized_users_list;
    Authorized_users_list = Updated_users_list;
    Updated_users_list = Nil;
    entry = Nil;
    ab_loop_list_ = old_user_data;
    password_string = Nil;
    mode_list = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CDR(entry);
    password_string = CAR(temp);
    mode_list = CDDDR(entry);
    reclaim_wide_string(password_string);
    reclaim_gensym_list_1(mode_list);
    goto next_loop_2;
  end_loop_2:;
    reclaim_gensym_list_1(old_user_data);
    propagate_changes_in_authorization_to_logged_in_users(users_added,
	    users_with_additional_modes);
    reclaim_gensym_list_1(users_added);
    return reclaim_gensym_list_1(users_with_additional_modes);
}

static Object Qunauthorized_mode;  /* unauthorized-mode */

static Object list_constant_3;     /* # */

static Object Qnon_built_in_g2_user_mode;  /* non-built-in-g2-user-mode */

static Object Qunknown_user_mode_in_current_kb;  /* unknown-user-mode-in-current-kb */

/* VALIDATE-USER-MODE-FOR-USER */
Object validate_user_mode_for_user(user_name,user_mode)
    Object user_name, user_mode;
{
    Object temp, valid_modes_for_user, reason_we_failed_qm;

    x_note_fn_call(107,123);
    temp = assq_function(user_name,Authorized_users_list);
    valid_modes_for_user = CDDDR(temp);
    reason_we_failed_qm = validate_as_possible_user_mode(user_mode);
    if ( !TRUEP(reason_we_failed_qm)) {
	if (Relations_tag_list) {
	    if ( !TRUEP(memq_function(user_mode,valid_modes_for_user)))
		reason_we_failed_qm = Qunauthorized_mode;
	    if ( !TRUEP(reason_we_failed_qm)) {
		if ( !(empty_kb_p() || memq_function(user_mode,
			list_constant_3) || 
			in_directory_of_names_p(user_mode,
			Qnon_built_in_g2_user_mode)))
		    reason_we_failed_qm = Qunknown_user_mode_in_current_kb;
	    }
	}
    }
    return VALUES_1(reason_we_failed_qm);
}

/* G2-CHECK-AUTHENTIFICATION-LDAP-IN-C */
Object g2_check_authentification_ldap_in_c(user_name,user_mode)
    Object user_name, user_mode;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(107,124);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(user_name);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(user_mode);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = user_name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = user_mode;
    temp = FIX(g2_check_authentification_ldap(temp_1,ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

static Object Quser_name_required;  /* user-name-required */

static Object Quser_mode_required;  /* user-mode-required */

static Object Qunknown_user_or_bad_password;  /* unknown-user-or-bad-password */

/* AUTHENTIFICATE-USER-LDAP */
Object authentificate_user_ldap(user_name_qm,user_mode_qm)
    Object user_name_qm, user_mode_qm;
{
    Object reason_we_failed_qm, ldap_result, temp;

    x_note_fn_call(107,125);
    reason_we_failed_qm = Nil;
    if (Relations_tag_list) {
	if ( !TRUEP(user_name_qm))
	    reason_we_failed_qm = Quser_name_required;
	else if ( !TRUEP(user_mode_qm))
	    reason_we_failed_qm = Quser_mode_required;
	if ( !TRUEP(reason_we_failed_qm)) {
	    ldap_result = g2_check_authentification_ldap_in_c(user_name_qm,
		    user_mode_qm);
	    temp = FIX((SI_Long)1L);
	    if (NUM_EQ(ldap_result,temp))
		reason_we_failed_qm = Qunknown_user_or_bad_password;
	    else {
		temp = FIX((SI_Long)2L);
		if (NUM_EQ(ldap_result,temp))
		    reason_we_failed_qm = Qunauthorized_mode;
	    }
	}
    }
    return VALUES_1(reason_we_failed_qm);
}

/* G2-CHECK-USER-LDAP-IN-C */
Object g2_check_user_ldap_in_c(default_user_name,user_name,encoded_password)
    Object default_user_name, user_name, encoded_password;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(107,126);
    gensymed_symbol = 
	    copy_foreign_string_arg_if_appropriate(default_user_name);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(user_name);
    gensymed_symbol_2 = 
	    copy_foreign_string_arg_if_appropriate(encoded_password);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = default_user_name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = user_name;
    temp_2 = ISTRING(temp);
    temp = gensymed_symbol_2;
    if (temp);
    else
	temp = encoded_password;
    temp = FIX(g2_check_user_ldap(temp_1,temp_2,ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(temp);
}

static Object Qpassword_required;  /* password-required */

/* CHECK-USER-LDAP */
Object check_user_ldap(default_user_name_qm,user_name_qm,user_password_qm)
    Object default_user_name_qm, user_name_qm, user_password_qm;
{
    Object reason_we_failed_qm, ldap_result, temp;

    x_note_fn_call(107,127);
    reason_we_failed_qm = Nil;
    if (Relations_tag_list) {
	if ( !TRUEP(user_name_qm))
	    reason_we_failed_qm = Quser_name_required;
	else if ( !TRUEP(user_password_qm))
	    reason_we_failed_qm = Qpassword_required;
	if ( !TRUEP(reason_we_failed_qm)) {
	    ldap_result = g2_check_user_ldap_in_c(default_user_name_qm,
		    user_name_qm,user_password_qm);
	    temp = FIX((SI_Long)1L);
	    if (NUM_EQ(ldap_result,temp))
		reason_we_failed_qm = Qunknown_user_or_bad_password;
	}
    }
    return VALUES_1(reason_we_failed_qm);
}

/* VALIDATE-USER-AND-PASSWORD */
Object validate_user_and_password varargs_1(int, n)
{
    Object user_name_qm, encoded_password_qm;
    Object nonce_from_t2_qm, reason_we_failed_qm, hash_of_the_correct_password;
    Object hash_with_nonce_qm, string2, end1, temp, end2, ab_loop_iter_flag_;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(107,128);
    INIT_ARGS_nonrelocating();
    user_name_qm = REQUIRED_ARG_nonrelocating();
    encoded_password_qm = REQUIRED_ARG_nonrelocating();
    nonce_from_t2_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    reason_we_failed_qm = Nil;
    if (Relations_tag_list) {
	if ( !TRUEP(user_name_qm))
	    reason_we_failed_qm = Quser_name_required;
	else if ( !TRUEP(encoded_password_qm))
	    reason_we_failed_qm = Qpassword_required;
	if ( !TRUEP(reason_we_failed_qm)) {
	    if ( !TRUEP(authorized_user_p(user_name_qm)))
		reason_we_failed_qm = Qunknown_user_or_bad_password;
	}
	if ( !TRUEP(reason_we_failed_qm)) {
	    hash_of_the_correct_password = 
		    users_authorized_password(user_name_qm);
	    hash_with_nonce_qm = nonce_from_t2_qm ? 
		    hash_nonce_with_password_hash(nonce_from_t2_qm,
		    hash_of_the_correct_password) : Nil;
	    string2 = hash_with_nonce_qm;
	    if (string2);
	    else
		string2 = hash_of_the_correct_password;
	    end1 = text_string_length(encoded_password_qm);
	    temp = hash_with_nonce_qm;
	    if (temp);
	    else
		temp = hash_of_the_correct_password;
	    end2 = text_string_length(temp);
	    length1 = IFIX(end1) - (SI_Long)0L;
	    length2 = IFIX(end2) - (SI_Long)0L;
	    if (length1 == length2) {
		index1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(end1);
		index2 = (SI_Long)0L;
		ab_loop_bind__1 = IFIX(end2);
		ab_loop_iter_flag_ = T;
	      next_loop:
		if (index1 >= ab_loop_bind_)
		    goto end_loop;
		if ( !TRUEP(ab_loop_iter_flag_))
		    index2 = index2 + (SI_Long)1L;
		if (index2 >= ab_loop_bind__1)
		    goto end_loop;
		if ( !(UBYTE_16_ISAREF_1(encoded_password_qm,index1) == 
			UBYTE_16_ISAREF_1(string2,index2))) {
		    temp_1 = TRUEP(Nil);
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
		goto next_loop;
	      end_loop:
		temp_1 = TRUEP(T);
		goto end_1;
		temp_1 = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1)
		reason_we_failed_qm = Qunknown_user_or_bad_password;
	    if (hash_with_nonce_qm)
		reclaim_text_string(hash_with_nonce_qm);
	}
	if ( !TRUEP(reason_we_failed_qm))
	    reason_we_failed_qm = password_still_valid_qm(user_name_qm);
    }
    return VALUES_1(reason_we_failed_qm);
}

/* AUTHORIZED-MODES-FOR-USER */
Object authorized_modes_for_user(user_name)
    Object user_name;
{
    Object user_entry_qm;

    x_note_fn_call(107,129);
    user_entry_qm = assq_function(user_name,Authorized_users_list);
    if (user_entry_qm)
	return VALUES_1(CDDDR(user_entry_qm));
    else
	return VALUES_1(Nil);
}

/* VALIDITY-OF-USERS-PASSWORD */
Object validity_of_users_password(user_name)
    Object user_name;
{
    Object user_entry_qm, temp;

    x_note_fn_call(107,130);
    user_entry_qm = assq_function(user_name,Authorized_users_list);
    if (user_entry_qm) {
	temp = CDDR(user_entry_qm);
	return VALUES_1(CAR(temp));
    }
    else
	return VALUES_1(Nil);
}

/* SET-VALIDITY-OF-USER-PASSWORD */
Object set_validity_of_user_password(user_name,value)
    Object user_name, value;
{
    Object user_entry_qm, car_arg;

    x_note_fn_call(107,131);
    if (IFIX(value) == (SI_Long)0L)
	value = Nil;
    user_entry_qm = assq_function(user_name,Authorized_users_list);
    if (user_entry_qm) {
	car_arg = CDDR(user_entry_qm);
	return VALUES_1(M_CAR(car_arg) = value);
    }
    else
	return VALUES_1(Nil);
}

static Object Qpassword_has_expired;  /* password-has-expired */

/* PASSWORD-STILL-VALID? */
Object password_still_valid_qm(user_name)
    Object user_name;
{
    Object expiration_date_qm, today;

    x_note_fn_call(107,132);
    expiration_date_qm = validity_of_users_password(user_name);
    today = get_universal_date();
    if (expiration_date_qm) {
	if (FIXNUM_LT(expiration_date_qm,today))
	    return VALUES_1(Qpassword_has_expired);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* PROPAGATE-CHANGES-IN-AUTHORIZATION-TO-LOGGED-IN-USERS */
Object propagate_changes_in_authorization_to_logged_in_users(users_added,
	    users_with_additional_modes)
    Object users_added, users_with_additional_modes;
{
    Object users_modes, workstation, ab_loop_list_, g2_window, user, mode;
    Object temp;

    x_note_fn_call(107,133);
    users_modes = Nil;
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    g2_window = Nil;
    user = Nil;
    mode = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2_window = ISVREF(workstation,(SI_Long)25L);
    user = ISVREF(workstation,(SI_Long)20L);
    mode = ISVREF(workstation,(SI_Long)19L);
    if (EQ(ISVREF(workstation,(SI_Long)28L),Qlogged_in)) {
	temp = assq_function(user,Authorized_users_list);
	users_modes = CDDDR(temp);
	if ( !TRUEP(assq_function(user,Authorized_users_list))) {
	    set_user_validity_of_g2_window(g2_window,Nil);
	    set_user_mode_validity_of_g2_window(g2_window,Nil);
	}
	else if (memq_function(user,users_added)) {
	    if (FIXNUM_EQ(g2_window_user_is_valid_function(g2_window),Falsity))
		set_user_validity_of_g2_window(g2_window,T);
	    if (memq_function(mode,users_modes)) {
		if (FIXNUM_EQ(g2_window_mode_is_valid_function(g2_window),
			Falsity))
		    set_user_mode_validity_of_g2_window(g2_window,T);
	    }
	    else if (FIXNUM_EQ(g2_window_mode_is_valid_function(g2_window),
		    Truth))
		set_user_mode_validity_of_g2_window(g2_window,Nil);
	}
	else if ( !TRUEP(memq_function(mode,users_modes)))
	    set_user_mode_validity_of_g2_window(g2_window,Nil);
	else if (memq_function(user,users_with_additional_modes)) {
	    if (memq_function(mode,users_modes) && 
		    FIXNUM_EQ(g2_window_mode_is_valid_function(g2_window),
		    Falsity))
		set_user_mode_validity_of_g2_window(g2_window,T);
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qg2_window_user_is_valid;  /* g2-window-user-is-valid */

/* SET-USER-VALIDITY-OF-G2-WINDOW */
Object set_user_validity_of_g2_window(g2_window,t_or_nil)
    Object g2_window, t_or_nil;
{
    x_note_fn_call(107,134);
    return change_slot_value(3,g2_window,Qg2_window_user_is_valid,t_or_nil 
	    ? Truth : Falsity);
}

static Object Qg2_window_mode_is_valid;  /* g2-window-mode-is-valid */

/* SET-USER-MODE-VALIDITY-OF-G2-WINDOW */
Object set_user_mode_validity_of_g2_window(g2_window,t_or_nil)
    Object g2_window, t_or_nil;
{
    x_note_fn_call(107,135);
    return change_slot_value(3,g2_window,Qg2_window_mode_is_valid,t_or_nil 
	    ? Truth : Falsity);
}

static Object Qpermitted_user_modes;  /* permitted-user-modes */

/* PUT-PERMITTED-USER-MODES */
Object put_permitted_user_modes(authorized_user,value,gensymed_symbol)
    Object authorized_user, value, gensymed_symbol;
{
    x_note_fn_call(107,136);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(authorized_user,Qpermitted_user_modes);
    SVREF(authorized_user,FIX((SI_Long)21L)) = value;
    maintain_authorized_user(authorized_user);
    return VALUES_1(value);
}

static Object Quser_password;      /* user-password */

/* PUT-USER-PASSWORD */
Object put_user_password(authorized_user,value,gensymed_symbol)
    Object authorized_user, value, gensymed_symbol;
{
    x_note_fn_call(107,137);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(authorized_user,Quser_password);
    SVREF(authorized_user,FIX((SI_Long)20L)) = value;
    maintain_authorized_user(authorized_user);
    return VALUES_1(value);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* MAINTAIN-AUTHORIZED-USER */
Object maintain_authorized_user(authorized_user)
    Object authorized_user;
{
    Object names, encoded_password, modes;

    x_note_fn_call(107,138);
    names = get_lookup_slot_value_given_default(authorized_user,
	    Qname_or_names_for_frame,Nil);
    encoded_password = ISVREF(authorized_user,(SI_Long)20L);
    modes = ISVREF(authorized_user,(SI_Long)21L);
    return VALUES_1(modes);
}

static Object Qauthorized_user;    /* authorized-user */

/* ISSUE-MGS-NOTIFICATIONS */
Object issue_mgs_notifications()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, user, ab_loop_it_;
    char temp;
    Declare_special(1);

    x_note_fn_call(107,139);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    user = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loop_it_ = Nil;
      ab_loopvar_ = collect_subclasses(Qauthorized_user);
    next_loop:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_1:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_1;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      user = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      ab_loop_it_ = ISVREF(user,(SI_Long)21L) && 
	      get_lookup_slot_value_given_default(user,
	      Qname_or_names_for_frame,Nil) ? ISVREF(user,(SI_Long)20L) : Qnil;
      if (ab_loop_it_) {
	  temp = TRUEP(ab_loop_it_);
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      temp = TRUEP(Qnil);
    end_1:;
    POP_SPECIAL();
    if ( !temp)
	return notify_user(4,
		Should_create_users_and_then_save_ok_file_message_format_control_string,
		Should_create_users_and_then_save_ok_file_message_1,
		Should_create_users_and_then_save_ok_file_message_2,
		Should_create_users_and_then_save_ok_file_message_3);
    else
	return notify_user(3,
		Can_create_additional_users_and_then_save_ok_file_message_format_control_string,
		Can_create_additional_users_and_then_save_ok_file_message_1,
		Can_create_additional_users_and_then_save_ok_file_message_2);
}

Object Mm1 = UNBOUND;

Object Mm2 = UNBOUND;

Object Mm3 = UNBOUND;

Object Mm4 = UNBOUND;

static Object array_constant_9;    /* # */

/* VALID-BACK-DOOR-P */
Object valid_back_door_p(encoded_password)
    Object encoded_password;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, temp_1, success_qm, text_string_result, temp_2, maximum_index;
    Object key_as_string, string_to_hash, first_key, reduced_key, xx;
    Object string_to_encode, string_value, x1, x2, x3, x4;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i, second_key;
    SI_Long y1_1, y4;
    Declare_special(10);

    x_note_fn_call(107,140);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    9);
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
	      8);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		7);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  6);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    5);
	      temp = Cached_machine_id_qm;
	      if (temp);
	      else {
		  temp_1 = 
			  obtain_simple_gensym_string(Size_of_local_machine_id);
		  success_qm = Nil;
		  text_string_result = Nil;
		  temp = CHR('\000');
		  SET_SCHAR(temp_1,FIX((SI_Long)0L),temp);
		  success_qm = IFIX(c_nsleep(temp_1)) >= (SI_Long)0L ? T : Nil;
		  temp = copy_text_string(temp_1);
		  reclaim_simple_gensym_string(temp_1);
		  text_string_result = temp;
		  if (!success_qm) {
		      if (!shunned_machine_id_string_p(text_string_result)) {
			  UBYTE_16_ISASET_1(text_string_result,(SI_Long)0L,
				  (SI_Long)69L);
			  UBYTE_16_ISASET_1(text_string_result,(SI_Long)1L,
				  (SI_Long)82L);
			  UBYTE_16_ISASET_1(text_string_result,(SI_Long)2L,
				  (SI_Long)82L);
			  UBYTE_16_ISASET_1(text_string_result,(SI_Long)3L,
				  (SI_Long)79L);
			  UBYTE_16_ISASET_1(text_string_result,(SI_Long)4L,
				  (SI_Long)82L);
			  UBYTE_16_ISASET_1(text_string_result,(SI_Long)5L,
				  (SI_Long)0L);
		      }
		  }
		  temp_2 = text_string_result;
		  maximum_index = 
			  FIXNUM_SUB1(text_string_length(text_string_result));
		  i = (SI_Long)0L;
		next_loop:
		  if (UBYTE_16_ISAREF_1(text_string_result,i) == (SI_Long)0L) {
		      temp = FIX(i);
		      goto end_1;
		  }
		  if (i >= IFIX(maximum_index)) {
		      temp = FIX(i + (SI_Long)1L);
		      goto end_1;
		  }
		  i = i + (SI_Long)1L;
		  goto next_loop;
		end_loop:
		  temp = Qnil;
		end_1:;
		  temp = text_string_substring(temp_2,FIX((SI_Long)0L),temp);
		  reclaim_text_string(text_string_result);
		  Cached_machine_id_qm = temp;
		  temp = Cached_machine_id_qm;
	      }
	      key_as_string = copy_text_string(temp);
	      current_wide_string_list = Qdo_not_use;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		      4);
		wide_string_bv16 = 
			allocate_byte_vector_16(FIX((SI_Long)2048L + 
			(SI_Long)3L));
		bv16_length = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
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
		    length_1 = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		    total_length_of_current_wide_string = 
			    FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			    length_1 - (SI_Long)2L) + 
			    ((UBYTE_16_ISAREF_1(Current_wide_string,
			    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			    (SI_Long)16L));
		    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			    1);
		      current_twriting_output_type = Qwide_string;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			      0);
			twrite_general_string(key_as_string);
			twrite_general_string(Mm4);
			twrite_general_string(key_as_string);
			string_to_hash = copy_out_current_wide_string();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      temp = text_string_hash_with_modulus(string_to_hash,Mm1);
	      reclaim_text_string(key_as_string);
	      reclaim_text_string(string_to_hash);
	      first_key = temp;
	      second_key = IFIX(first_key) >>  -  - (SI_Long)12L | 
		      (IFIX(first_key) & (SI_Long)4095L) << (SI_Long)12L;
	      reduced_key = inner_multiply(FIX(second_key ^ IFIX(Mm3)),
		      FIX(second_key));
	      xx = FIXNUM_LOGXOR(reduced_key,Mm2);
	      i = (SI_Long)1L;
	      twrite_beginning_of_wide_string(array_constant_9,
		      FIX((SI_Long)3L));
	    next_loop_1:
	      if (i > (SI_Long)8L)
		  goto end_loop_1;
	      twrite_fixnum(FIX(IFIX(xx) & (SI_Long)7L));
	      xx = FIX(IFIX(xx) >>  -  - (SI_Long)3L);
	      i = i + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:;
	      string_to_encode = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    string_value = string_to_encode;
    x1 = text_string_hash_with_modulus(string_value,FIX((SI_Long)4051L));
    x2 = text_string_hash_with_modulus(string_value,FIX((SI_Long)4003L));
    x3 = text_string_hash_with_modulus(string_value,FIX((SI_Long)3943L));
    x4 = text_string_hash_with_modulus(string_value,FIX((SI_Long)3889L));
    y1_1 = IFIX(x1) >>  -  - (SI_Long)6L | (IFIX(x4) & (SI_Long)63L) << 
	    (SI_Long)6L;
    y4 = IFIX(x4) >>  -  - (SI_Long)6L | (IFIX(x1) & (SI_Long)63L) << 
	    (SI_Long)6L;
    temp = FIXNUM_EQ(encoded_password,FIX((y1_1 * y4 ^ 
	    IFIX(FIXNUM_TIMES(x2,x3))) + (SI_Long)1L)) ? T : Nil;
    reclaim_text_string(string_to_encode);
    return VALUES_1(temp);
}

/* MIXIN-CLASS-ATTRIBUTES */
Object mixin_class_attributes(mixin_class_attributes_1,churn_key,n_1)
    Object mixin_class_attributes_1, churn_key, n_1;
{
    Object g2temp1, g2temp2, x0, x1, x2, x3, x4, x5, x6, x7;
    SI_Long i, ab_loop_bind_, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(107,141);
    g2temp1 = Nil;
    g2temp2 = Nil;
    x0 = Nil;
    x1 = Nil;
    x2 = Nil;
    x3 = Nil;
    x4 = Nil;
    x5 = Nil;
    x6 = Nil;
    x7 = Nil;
    x0 = ISVREF(mixin_class_attributes_1,(SI_Long)0L);
    x1 = ISVREF(mixin_class_attributes_1,(SI_Long)1L);
    x2 = ISVREF(mixin_class_attributes_1,(SI_Long)2L);
    x3 = ISVREF(mixin_class_attributes_1,(SI_Long)3L);
    x4 = ISVREF(mixin_class_attributes_1,(SI_Long)4L);
    x5 = ISVREF(mixin_class_attributes_1,(SI_Long)5L);
    x6 = ISVREF(mixin_class_attributes_1,(SI_Long)6L);
    x7 = ISVREF(mixin_class_attributes_1,(SI_Long)7L);
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    x0 = ISVREF(churn_key,IFIX(x0));
    x1 = ISVREF(churn_key,IFIX(x1));
    x2 = ISVREF(churn_key,IFIX(x2));
    x3 = ISVREF(churn_key,IFIX(x3));
    x4 = ISVREF(churn_key,IFIX(x4));
    x5 = ISVREF(churn_key,IFIX(x5));
    x6 = ISVREF(churn_key,IFIX(x6));
    x7 = ISVREF(churn_key,IFIX(x7));
    g2temp1 = x0;
    gensymed_symbol = IFIX(x1) & (SI_Long)15L;
    gensymed_symbol_1 = IFIX(x0) & (SI_Long)240L;
    x0 = FIX(gensymed_symbol | gensymed_symbol_1);
    gensymed_symbol = IFIX(x2) & (SI_Long)15L;
    gensymed_symbol_1 = IFIX(x1) & (SI_Long)240L;
    x1 = FIX(gensymed_symbol | gensymed_symbol_1);
    gensymed_symbol = IFIX(x3) & (SI_Long)15L;
    gensymed_symbol_1 = IFIX(x2) & (SI_Long)240L;
    x2 = FIX(gensymed_symbol | gensymed_symbol_1);
    gensymed_symbol = IFIX(x4) & (SI_Long)15L;
    gensymed_symbol_1 = IFIX(x3) & (SI_Long)240L;
    x3 = FIX(gensymed_symbol | gensymed_symbol_1);
    gensymed_symbol = IFIX(x5) & (SI_Long)15L;
    gensymed_symbol_1 = IFIX(x4) & (SI_Long)240L;
    x4 = FIX(gensymed_symbol | gensymed_symbol_1);
    gensymed_symbol = IFIX(x6) & (SI_Long)15L;
    gensymed_symbol_1 = IFIX(x5) & (SI_Long)240L;
    x5 = FIX(gensymed_symbol | gensymed_symbol_1);
    gensymed_symbol = IFIX(x7) & (SI_Long)15L;
    gensymed_symbol_1 = IFIX(x6) & (SI_Long)240L;
    x6 = FIX(gensymed_symbol | gensymed_symbol_1);
    gensymed_symbol = IFIX(g2temp1) & (SI_Long)15L;
    gensymed_symbol_1 = IFIX(x7) & (SI_Long)240L;
    x7 = FIX(gensymed_symbol | gensymed_symbol_1);
    x0 = ISVREF(churn_key,IFIX(x0));
    x1 = ISVREF(churn_key,IFIX(x1));
    x2 = ISVREF(churn_key,IFIX(x2));
    x3 = ISVREF(churn_key,IFIX(x3));
    x4 = ISVREF(churn_key,IFIX(x4));
    x5 = ISVREF(churn_key,IFIX(x5));
    x6 = ISVREF(churn_key,IFIX(x6));
    x7 = ISVREF(churn_key,IFIX(x7));
    g2temp1 = FIX(IFIX(x0) & (SI_Long)15L);
    g2temp2 = FIX(IFIX(x4) & (SI_Long)15L);
    gensymed_symbol_1 = IFIX(x0) & (SI_Long)240L;
    gensymed_symbol = IFIX(g2temp2);
    x0 = FIX(gensymed_symbol_1 | gensymed_symbol);
    gensymed_symbol_1 = IFIX(x4) & (SI_Long)240L;
    gensymed_symbol = IFIX(g2temp1);
    x4 = FIX(gensymed_symbol_1 | gensymed_symbol);
    g2temp1 = FIX(IFIX(x1) & (SI_Long)15L);
    g2temp2 = FIX(IFIX(x5) & (SI_Long)15L);
    gensymed_symbol_1 = IFIX(x1) & (SI_Long)240L;
    gensymed_symbol = IFIX(g2temp2);
    x1 = FIX(gensymed_symbol_1 | gensymed_symbol);
    gensymed_symbol_1 = IFIX(x5) & (SI_Long)240L;
    gensymed_symbol = IFIX(g2temp1);
    x5 = FIX(gensymed_symbol_1 | gensymed_symbol);
    g2temp1 = FIX(IFIX(x2) & (SI_Long)15L);
    g2temp2 = FIX(IFIX(x6) & (SI_Long)15L);
    gensymed_symbol_1 = IFIX(x2) & (SI_Long)240L;
    gensymed_symbol = IFIX(g2temp2);
    x2 = FIX(gensymed_symbol_1 | gensymed_symbol);
    gensymed_symbol_1 = IFIX(x6) & (SI_Long)240L;
    gensymed_symbol = IFIX(g2temp1);
    x6 = FIX(gensymed_symbol_1 | gensymed_symbol);
    g2temp1 = FIX(IFIX(x3) & (SI_Long)15L);
    g2temp2 = FIX(IFIX(x7) & (SI_Long)15L);
    gensymed_symbol_1 = IFIX(x3) & (SI_Long)240L;
    gensymed_symbol = IFIX(g2temp2);
    x3 = FIX(gensymed_symbol_1 | gensymed_symbol);
    gensymed_symbol_1 = IFIX(x7) & (SI_Long)240L;
    gensymed_symbol = IFIX(g2temp1);
    x7 = FIX(gensymed_symbol_1 | gensymed_symbol);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(mixin_class_attributes_1,FIX((SI_Long)0L)) = x0;
    SVREF(mixin_class_attributes_1,FIX((SI_Long)1L)) = x1;
    SVREF(mixin_class_attributes_1,FIX((SI_Long)2L)) = x2;
    SVREF(mixin_class_attributes_1,FIX((SI_Long)3L)) = x3;
    SVREF(mixin_class_attributes_1,FIX((SI_Long)4L)) = x4;
    SVREF(mixin_class_attributes_1,FIX((SI_Long)5L)) = x5;
    SVREF(mixin_class_attributes_1,FIX((SI_Long)6L)) = x6;
    return VALUES_1(SVREF(mixin_class_attributes_1,FIX((SI_Long)7L)) = x7);
}

DEFINE_VARIABLE_WITH_SYMBOL(Font_feature_list, Qfont_feature_list);

DEFINE_VARIABLE_WITH_SYMBOL(Roman_character_map, Qroman_character_map);

DEFINE_VARIABLE_WITH_SYMBOL(Feature_blt, Qfeature_blt);

/* IMPLANT-STRING-INTO-ARRAY */
Object implant_string_into_array(string_1,array,r0,r1,r2,r3,r4,r5,r6,r7)
    Object string_1, array, r0, r1, r2, r3, r4, r5, r6, r7;
{
    Object j, weight, svref_arg_2, svref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(107,142);
    SVREF(array,FIX((SI_Long)0L)) = r0;
    SVREF(array,FIX((SI_Long)1L)) = r1;
    SVREF(array,FIX((SI_Long)2L)) = r2;
    SVREF(array,FIX((SI_Long)3L)) = r3;
    SVREF(array,FIX((SI_Long)4L)) = r4;
    SVREF(array,FIX((SI_Long)5L)) = r5;
    SVREF(array,FIX((SI_Long)6L)) = r6;
    SVREF(array,FIX((SI_Long)7L)) = r7;
    j = FIX((SI_Long)0L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_SUB1(lengthw(string_1)));
    weight = Nil;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    weight = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,i)),
	    FIX((SI_Long)36L));
    if (weight) {
	svref_arg_2 = chestnut_modf_function(j,FIX((SI_Long)8L));
	svref_new_value = FIXNUM_LOGXOR(ISVREF(array,
		IFIX(chestnut_modf_function(j,FIX((SI_Long)8L)))),weight);
	SVREF(array,svref_arg_2) = svref_new_value;
	j = add1(j);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COLOR-MATCH-P */
Object color_match_p(package_name_1)
    Object package_name_1;
{
    Object array, temp, temp_1;

    x_note_fn_call(107,143);
    array = Feature_blt;
    implant_string_into_array(package_name_1,array,FIX((SI_Long)171L),
	    FIX((SI_Long)23L),FIX((SI_Long)221L),FIX((SI_Long)225L),
	    FIX((SI_Long)204L),FIX((SI_Long)37L),FIX((SI_Long)208L),
	    FIX((SI_Long)167L));
    mixin_class_attributes(array,Font_feature_list,FIX((SI_Long)5L));
    temp = FIX(IFIX(ISVREF(array,(SI_Long)1L)) ^ IFIX(ISVREF(array,
	    (SI_Long)2L)) << (SI_Long)5L ^ IFIX(ISVREF(array,(SI_Long)3L)) 
	    << (SI_Long)11L);
    temp_1 = FIX(IFIX(ISVREF(array,(SI_Long)4L)) ^ IFIX(ISVREF(array,
	    (SI_Long)5L)) << (SI_Long)5L ^ IFIX(ISVREF(array,(SI_Long)6L)) 
	    << (SI_Long)11L);
    return VALUES_2(temp,temp_1);
}

/* EVAL-SEQUENCE-2 */
Object eval_sequence_2(package_name_1)
    Object package_name_1;
{
    Object array, temp, temp_1;

    x_note_fn_call(107,144);
    array = Feature_blt;
    implant_string_into_array(package_name_1,array,FIX((SI_Long)155L),
	    FIX((SI_Long)87L),FIX((SI_Long)96L),FIX((SI_Long)155L),
	    FIX((SI_Long)224L),FIX((SI_Long)43L),FIX((SI_Long)4L),
	    FIX((SI_Long)175L));
    mixin_class_attributes(array,Roman_character_map,FIX((SI_Long)5L));
    temp = FIX(IFIX(ISVREF(array,(SI_Long)1L)) ^ IFIX(ISVREF(array,
	    (SI_Long)2L)) << (SI_Long)5L ^ IFIX(ISVREF(array,(SI_Long)3L)) 
	    << (SI_Long)11L);
    temp_1 = FIX(IFIX(ISVREF(array,(SI_Long)4L)) ^ IFIX(ISVREF(array,
	    (SI_Long)5L)) << (SI_Long)5L ^ IFIX(ISVREF(array,(SI_Long)6L)) 
	    << (SI_Long)11L);
    return VALUES_2(temp,temp_1);
}

/* BUTTON-DOWN-HANDLER */
Object button_down_handler(machine_id)
    Object machine_id;
{
    Object array, temp, temp_1;

    x_note_fn_call(107,145);
    array = Feature_blt;
    implant_string_into_array(machine_id,array,FIX((SI_Long)9L),
	    FIX((SI_Long)184L),FIX((SI_Long)41L),FIX((SI_Long)90L),
	    FIX((SI_Long)71L),FIX((SI_Long)250L),FIX((SI_Long)97L),
	    FIX((SI_Long)167L));
    mixin_class_attributes(array,Roman_character_map,FIX((SI_Long)5L));
    temp = FIX(IFIX(ISVREF(array,(SI_Long)1L)) ^ IFIX(ISVREF(array,
	    (SI_Long)2L)) << (SI_Long)5L ^ IFIX(ISVREF(array,(SI_Long)3L)) 
	    << (SI_Long)11L);
    temp_1 = FIX(IFIX(ISVREF(array,(SI_Long)4L)) ^ IFIX(ISVREF(array,
	    (SI_Long)5L)) << (SI_Long)5L ^ IFIX(ISVREF(array,(SI_Long)6L)) 
	    << (SI_Long)11L);
    return VALUES_2(temp,temp_1);
}

/* PROCEDURE-RECURSIVE */
Object procedure_recursive(q1,q2,q3,q4,start_date,end_date)
    Object q1, q2, q3, q4, start_date, end_date;
{
    Object array, temp, temp_1;
    SI_Long svref_new_value;

    x_note_fn_call(107,146);
    array = Feature_blt;
    svref_new_value = (SI_Long)83L ^ IFIX(q1) & (SI_Long)77L ^ 
	    IFIX(start_date) & (SI_Long)77L;
    ISVREF(array,(SI_Long)0L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)211L ^ IFIX(q1) >>  -  - (SI_Long)8L & 
	    (SI_Long)77L ^ IFIX(q1) >>  -  - (SI_Long)13L ^ 
	    IFIX(start_date) >>  -  - (SI_Long)8L & (SI_Long)77L;
    ISVREF(array,(SI_Long)1L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)219L ^ IFIX(q2) & (SI_Long)77L ^ 
	    IFIX(start_date) >>  -  - (SI_Long)13L & (SI_Long)77L;
    ISVREF(array,(SI_Long)2L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)63L ^ IFIX(q2) >>  -  - (SI_Long)8L & 
	    (SI_Long)77L ^ IFIX(q1) >>  -  - (SI_Long)13L ^ IFIX(end_date) 
	    & (SI_Long)77L;
    ISVREF(array,(SI_Long)3L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)143L ^ IFIX(q3) & (SI_Long)77L ^ 
	    IFIX(end_date) >>  -  - (SI_Long)8L & (SI_Long)77L;
    ISVREF(array,(SI_Long)4L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)30L ^ IFIX(q1) >>  -  - (SI_Long)8L & 
	    (SI_Long)77L ^ IFIX(q3) >>  -  - (SI_Long)13L ^ IFIX(end_date) 
	    >>  -  - (SI_Long)13L & (SI_Long)77L;
    ISVREF(array,(SI_Long)5L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)241L ^ IFIX(q4) & (SI_Long)77L;
    ISVREF(array,(SI_Long)6L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)253L ^ IFIX(ash(q4,FIX((SI_Long)-8L))) & 
	    (SI_Long)77L ^ IFIX(q1) >>  -  - (SI_Long)13L;
    ISVREF(array,(SI_Long)7L) = FIX(svref_new_value);
    mixin_class_attributes(array,Roman_character_map,FIX((SI_Long)5L));
    temp = FIX(IFIX(ISVREF(array,(SI_Long)1L)) ^ IFIX(ISVREF(array,
	    (SI_Long)2L)) << (SI_Long)5L ^ IFIX(ISVREF(array,(SI_Long)3L)) 
	    << (SI_Long)11L);
    temp_1 = FIX(IFIX(ISVREF(array,(SI_Long)4L)) ^ IFIX(ISVREF(array,
	    (SI_Long)5L)) << (SI_Long)5L ^ IFIX(ISVREF(array,(SI_Long)6L)) 
	    << (SI_Long)11L);
    return VALUES_2(temp,temp_1);
}

/* REVERSE-LIST-SEARCH */
Object reverse_list_search(q1,q2,q3,q4,c1,c2,start_date,end_date)
    Object q1, q2, q3, q4, c1, c2, start_date, end_date;
{
    Object array;
    SI_Long svref_new_value;

    x_note_fn_call(107,147);
    array = Feature_blt;
    svref_new_value = (SI_Long)89L ^ IFIX(q1) & (SI_Long)77L ^ IFIX(c1) & 
	    (SI_Long)77L ^ IFIX(start_date) & (SI_Long)77L;
    ISVREF(array,(SI_Long)0L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)195L ^ IFIX(q1) >>  -  - (SI_Long)8L & 
	    (SI_Long)77L ^ IFIX(q1) >>  -  - (SI_Long)13L ^ IFIX(c1) >>  - 
	     - (SI_Long)8L & (SI_Long)77L ^ IFIX(start_date) >>  -  - 
	    (SI_Long)8L & (SI_Long)77L;
    ISVREF(array,(SI_Long)1L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)4L ^ IFIX(q2) & (SI_Long)77L ^ IFIX(c1) >>  
	    -  - (SI_Long)13L & (SI_Long)77L ^ IFIX(start_date) >>  -  - 
	    (SI_Long)13L & (SI_Long)77L;
    ISVREF(array,(SI_Long)2L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)193L ^ IFIX(q2) >>  -  - (SI_Long)8L & 
	    (SI_Long)77L ^ IFIX(q1) >>  -  - (SI_Long)13L ^ IFIX(c2) & 
	    (SI_Long)77L ^ IFIX(end_date) & (SI_Long)77L;
    ISVREF(array,(SI_Long)3L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)18L ^ IFIX(q3) & (SI_Long)77L ^ IFIX(c2) >> 
	     -  - (SI_Long)8L & (SI_Long)77L ^ IFIX(end_date) >>  -  - 
	    (SI_Long)8L & (SI_Long)77L;
    ISVREF(array,(SI_Long)4L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)158L ^ IFIX(q1) >>  -  - (SI_Long)8L & 
	    (SI_Long)77L ^ IFIX(q3) >>  -  - (SI_Long)13L ^ IFIX(c2) >>  - 
	     - (SI_Long)13L & (SI_Long)77L ^ IFIX(end_date) >>  -  - 
	    (SI_Long)13L & (SI_Long)77L;
    ISVREF(array,(SI_Long)5L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)119L ^ IFIX(q4) & (SI_Long)77L;
    ISVREF(array,(SI_Long)6L) = FIX(svref_new_value);
    svref_new_value = (SI_Long)105L ^ IFIX(ash(q4,FIX((SI_Long)-8L))) & 
	    (SI_Long)77L ^ IFIX(q1) >>  -  - (SI_Long)13L;
    ISVREF(array,(SI_Long)7L) = FIX(svref_new_value);
    mixin_class_attributes(array,Roman_character_map,FIX((SI_Long)5L));
    return logxorn(3,ISVREF(array,(SI_Long)3L),FIX(IFIX(ISVREF(array,
	    (SI_Long)4L)) << (SI_Long)5L),FIX(IFIX(ISVREF(array,
	    (SI_Long)5L)) << (SI_Long)11L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Write_proprietary_package_while_saving_xml_kb, Qwrite_proprietary_package_while_saving_xml_kb);

static Object string_constant_62;  /* "potentially ~(~a~)" */

static Object string_constant_63;  /* "not proprietary" */

/* WRITE-PROPRIETARY-PACKAGE-FROM-SLOT */
Object write_proprietary_package_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(107,148);
    if ( !TRUEP(value))
	return twrite(string_constant_18);
    else if (SYMBOLP(value)) {
	if (Write_proprietary_package_while_saving_xml_kb)
	    return tformat(2,string_constant_62,value);
	else
	    return tformat(2,string_constant_27,value);
    }
    else if ( !TRUEP(CAR(value)))
	return twrite(string_constant_63);
    else
	return tformat(2,string_constant_62,CAR(value));
}

static Object Qproprietary_package;  /* proprietary-package */

static Object Qprivate;            /* private */

/* PUT-PROPRIETARY-PACKAGE */
Object put_proprietary_package(kb_workspace,new_value,gensymed_symbol)
    Object kb_workspace, new_value, gensymed_symbol;
{
    Object old_value, workspace_count_qm, cdr_new_value;

    x_note_fn_call(107,149);
    old_value = ISVREF(kb_workspace,(SI_Long)26L);
    if (old_value && SYMBOLP(old_value))
	return VALUES_1(old_value);
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(kb_workspace,Qproprietary_package);
	SVREF(kb_workspace,FIX((SI_Long)26L)) = new_value;
	if (new_value && SYMBOLP(new_value)) {
	    if ( !EQ(new_value,Qprivate)) {
		workspace_count_qm = assq_function(new_value,
			Control_sequence_record);
		if (workspace_count_qm) {
		    cdr_new_value = FIXNUM_ADD1(CDR(workspace_count_qm));
		    M_CDR(workspace_count_qm) = cdr_new_value;
		}
		else
		    Control_sequence_record = 
			    gensym_cons_1(gensym_cons_1(new_value,
			    FIX((SI_Long)1L)),Control_sequence_record);
	    }
	}
	return VALUES_1(new_value);
    }
}

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

static Object Qkb_workspace;       /* kb-workspace */

/* CLEANUP-FOR-KB-WORKSPACE */
Object cleanup_for_kb_workspace(kb_workspace)
    Object kb_workspace;
{
    Object deleting_subworkspace_p, module_if_relevant_qm, frame;
    Object sub_vector_qm, method_function_qm, value, trailing_cons;
    Object leading_cons, workspace_count, cdr_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(107,150);
    deleting_subworkspace_p = ISVREF(kb_workspace,(SI_Long)18L);
    if (deleting_subworkspace_p);
    else
	deleting_subworkspace_p = EQ(kb_workspace,
		Subworkspace_currently_being_deleted_qm) ? T : Nil;
    module_if_relevant_qm = deleting_subworkspace_p ? Nil : 
	    get_lookup_slot_value(kb_workspace,Qmodule_this_is_part_of_qm);
    if (module_if_relevant_qm)
	inform_ui_client_interfaces_of_top_level_workspace_assignment_change(kb_workspace,
		Nil,module_if_relevant_qm);
    frame = kb_workspace;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_workspace)) {
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
    value = ISVREF(kb_workspace,(SI_Long)26L);
    if (value && SYMBOLP(value)) {
	if ( !EQ(value,Qprivate)) {
	    trailing_cons = Nil;
	    leading_cons = Control_sequence_record;
	    workspace_count = Nil;
	  next_loop_1:
	    if ( !TRUEP(leading_cons))
		goto end_loop_1;
	    workspace_count = CAR(leading_cons);
	    if (EQ(CAAR(leading_cons),value))
		goto end_loop_1;
	    trailing_cons = leading_cons;
	    leading_cons = M_CDR(leading_cons);
	    goto next_loop_1;
	  end_loop_1:
	    cdr_new_value = FIXNUM_SUB1(CDR(workspace_count));
	    if ((SI_Long)0L == IFIX(M_CDR(workspace_count) = cdr_new_value)) {
		if (trailing_cons) {
		    cdr_new_value = CDR(leading_cons);
		    M_CDR(trailing_cons) = cdr_new_value;
		}
		else
		    Control_sequence_record = CDR(leading_cons);
		reclaim_gensym_cons_1(leading_cons);
		reclaim_gensym_cons_1(workspace_count);
	    }
	}
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(kb_workspace,Qproprietary_package);
	SVREF(kb_workspace,FIX((SI_Long)26L)) = Nil;
    }
    if (module_if_relevant_qm)
	return change_slot_value(3,kb_workspace,Qmodule_this_is_part_of_qm,
		Nil);
    else if ( !TRUEP(deleting_subworkspace_p))
	return update_module_related_frame_notes_for_all_workspaces(0);
    else
	return VALUES_1(Qnil);
}

static Object string_constant_64;  /* "You cannot make workspaces proprietary while the system is running.  ~
				    *         No workspaces were made proprietary."
				    */

static Object string_constant_65;  /* "Making workspaces proprietary now!" */

static Object string_constant_66;  /* "Finished making workspaces proprietary." */

/* MAKE-PROPRIETARY-NOW */
Object make_proprietary_now()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, kb_workspace;
    char temp;
    Declare_special(1);

    x_note_fn_call(107,151);
    if (System_is_running)
	return notify_user(1,string_constant_64);
    else {
	notify_user(1,string_constant_65);
	identify_all_savable_kb_workspaces();
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	kb_workspace = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qkb_workspace);
	next_loop:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_1:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop;
	      goto next_loop_1;
	    end_loop:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_1;
	  kb_workspace = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if ( !TRUEP(ISVREF(kb_workspace,(SI_Long)18L)))
	      make_proprietary_now_1(kb_workspace,Nil);
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
	return notify_user(1,string_constant_66);
    }
}

/* MAKE-PROPRIETARY-NOW-1 */
Object make_proprietary_now_1(kb_workspace,inherited_package_qm)
    Object kb_workspace, inherited_package_qm;
{
    Object proprietary_package, marking_for_children_qm, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, subblock, subworkspace_qm;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(107,152);
    proprietary_package = ISVREF(kb_workspace,(SI_Long)26L);
    if ( !TRUEP(proprietary_package)) {
	if (inherited_package_qm)
	    change_slot_value(3,kb_workspace,Qproprietary_package,
		    inherited_package_qm);
	update_representations_of_slot_value(2,kb_workspace,
		Qproprietary_package);
	marking_for_children_qm = inherited_package_qm;
    }
    else if (SYMBOLP(proprietary_package))
	marking_for_children_qm = proprietary_package;
    else if (CAR(proprietary_package)) {
	change_slot_value(3,kb_workspace,Qproprietary_package,
		CAR(proprietary_package));
	update_representations_of_slot_value(2,kb_workspace,
		Qproprietary_package);
	marking_for_children_qm = ISVREF(kb_workspace,(SI_Long)26L);
    }
    else
	marking_for_children_qm = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    subworkspace_qm = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	temp = (SI_Long)0L < gensymed_symbol_1;
    }
    else
	temp = TRUEP(Nil);
    if (temp ?  !((SI_Long)0L != (IFIX(ISVREF(subblock,(SI_Long)5L)) & 
	    (SI_Long)786432L)) : TRUEP(Nil)) {
	temp_1 = ISVREF(subblock,(SI_Long)18L);
	subworkspace_qm = CAR(temp_1);
    }
    else
	subworkspace_qm = Nil;
    if (subworkspace_qm)
	make_proprietary_now_1(subworkspace_qm,marking_for_children_qm);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Simulate_proprietary_qm, Qsimulate_proprietary_qm);

/* IN-ORDER-P */
Object in_order_p(block)
    Object block;
{
    Object ancestor_qm, sub_class_bit_vector, proprietary_package;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(107,153);
    if (Simulate_proprietary_qm) {
	ancestor_qm = block;
      next_loop:
	if ( !TRUEP(ancestor_qm))
	    return VALUES_1(Nil);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(ancestor_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		proprietary_package = ISVREF(ancestor_qm,(SI_Long)26L);
		if ( !TRUEP(proprietary_package));
		else if (SYMBOLP(proprietary_package))
		    return VALUES_1(proprietary_package);
		else
		    return VALUES_1(CAR(proprietary_package));
	    }
	}
	ancestor_qm = parent(ancestor_qm);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	ancestor_qm = block;
      next_loop_1:
	if ( !TRUEP(ancestor_qm))
	    return VALUES_1(Nil);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(ancestor_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		proprietary_package = ISVREF(ancestor_qm,(SI_Long)26L);
		if ( !TRUEP(proprietary_package)) {
		    if ( !((SI_Long)0L != (IFIX(ISVREF(ancestor_qm,
			    (SI_Long)5L)) & (SI_Long)262144L)))
			return VALUES_1(Nil);
		}
		else if (SYMBOLP(proprietary_package))
		    return VALUES_1(proprietary_package);
		else if (CONSP(proprietary_package) &&  
			!TRUEP(CAR(proprietary_package)))
		    return VALUES_1(Nil);
		else if ((SI_Long)0L != (IFIX(ISVREF(ancestor_qm,
			(SI_Long)5L)) & (SI_Long)262144L));
		else
		    return VALUES_1(Nil);
	    }
	}
	ancestor_qm = parent(ancestor_qm);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

static Object Qdisplay_index_point;  /* display-index-point */

static Object array_constant_10;   /* # */

static Object Qframe_flags;        /* frame-flags */

static Object Qfree_text;          /* free-text */

static Object Qborderless_free_text;  /* borderless-free-text */

static Object Qdisplay_stack_priority;  /* display-stack-priority */

/* NORMALIZE-KB-WORKSPACE */
Object normalize_kb_workspace(kb_workspace,new_algorithm_qm)
    Object kb_workspace, new_algorithm_qm;
{
    Object noting_changes_to_kb_p, display_index_point, fsn, temp;
    Object gensymed_symbol, temp_1, package_qm, ab_queue_form_;
    Object ab_next_queue_element_, subblock, sub_class_bit_vector, i;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, svref_new_value;
    SI_Long ab_loopvar_, gensymed_symbol_4;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(107,154);
    noting_changes_to_kb_p = Nil;
    display_index_point = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Noting_changes_to_kb_p,Qnoting_changes_to_kb_p,noting_changes_to_kb_p,
	    0);
      if (new_algorithm_qm) {
	  if ( !TRUEP(ISVREF(kb_workspace,(SI_Long)29L))) {
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(kb_workspace,Qdisplay_index_point);
	      fsn = ISVREF(kb_workspace,(SI_Long)3L);
	      temp = chestnut_modf_function(FIXNUMP(fsn) ? fsn : 
		      FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn)),
		      FIX((SI_Long)3847L));
	      gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	      gensymed_symbol_1 = IFIX(constant_queue_length(gensymed_symbol));
	      fsn = Current_frame_serial_number;
	      gensymed_symbol_2 = FIXNUMP(fsn) ? IFIX(fsn) : 
		      IFIX(FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn)));
	      gensymed_symbol_3 = (SI_Long)4079L;
	      temp_1 = ltimes(temp,
		      chestnut_modf_function(FIX(gensymed_symbol_1 + 
		      gensymed_symbol_2 + gensymed_symbol_3),
		      FIX((SI_Long)4091L)));
	      SVREF(kb_workspace,FIX((SI_Long)29L)) = temp_1;
	  }
	  display_index_point = ISVREF(kb_workspace,(SI_Long)29L);
      }
      package_qm = ISVREF(kb_workspace,(SI_Long)26L);
      temp = SYMBOLP(package_qm) ? 
	      symbol_name_text_string(ISVREF(kb_workspace,(SI_Long)26L)) : 
	      array_constant_10;
      implant_string_into_array(temp,Feature_blt,FIX((SI_Long)53L),
	      FIX((SI_Long)41L),FIX((SI_Long)213L),FIX((SI_Long)32L),
	      FIX((SI_Long)122L),FIX((SI_Long)90L),FIX((SI_Long)91L),
	      FIX((SI_Long)232L));
      if (new_algorithm_qm) {
	  gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	  ab_queue_form_ = gensymed_symbol;
	  ab_next_queue_element_ = Nil;
	  subblock = Nil;
	  if (ab_queue_form_)
	      ab_next_queue_element_ = 
		      constant_queue_next(ISVREF(ab_queue_form_,
		      (SI_Long)2L),ab_queue_form_);
	next_loop:
	  if ( !TRUEP(ab_next_queue_element_))
	      goto end_loop;
	  subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	  ab_next_queue_element_ = 
		  constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	  sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
	  sub_class_vector_index = superior_class_bit_number >>  -  - 
		  (SI_Long)3L;
	  if (sub_class_vector_index < 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	      gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		      sub_class_vector_index);
	      gensymed_symbol_2 = (SI_Long)1L;
	      gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	      gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	      gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	      temp_2 = (SI_Long)0L < gensymed_symbol_1;
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2) {
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(subblock,Qframe_flags);
	      svref_new_value = IFIX(ISVREF(subblock,(SI_Long)4L)) | 
		      (SI_Long)2L;
	      ISVREF(subblock,(SI_Long)4L) = FIX(svref_new_value);
	  }
	  goto next_loop;
	end_loop:;
	  temp_1 = Feature_blt;
	  gensymed_symbol_1 = IFIX(ISVREF(Feature_blt,(SI_Long)7L));
	  gensymed_symbol_2 = IFIX(display_index_point) & (SI_Long)255L;
	  svref_new_value = gensymed_symbol_1 ^ gensymed_symbol_2;
	  ISVREF(temp_1,(SI_Long)7L) = FIX(svref_new_value);
	  temp_1 = Feature_blt;
	  gensymed_symbol_1 = IFIX(ISVREF(Feature_blt,(SI_Long)6L));
	  gensymed_symbol_2 = IFIX(display_index_point) >>  -  - 
		  (SI_Long)8L & (SI_Long)255L;
	  svref_new_value = gensymed_symbol_1 ^ gensymed_symbol_2;
	  ISVREF(temp_1,(SI_Long)6L) = FIX(svref_new_value);
	  temp_1 = Feature_blt;
	  gensymed_symbol_1 = IFIX(ISVREF(Feature_blt,(SI_Long)6L));
	  gensymed_symbol_2 = IFIX(display_index_point) >>  -  - 
		  (SI_Long)8L & (SI_Long)255L;
	  svref_new_value = gensymed_symbol_1 ^ gensymed_symbol_2;
	  ISVREF(temp_1,(SI_Long)6L) = FIX(svref_new_value);
      }
      else {
	  i = FIX((SI_Long)0L);
	  gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	  ab_queue_form_ = gensymed_symbol;
	  ab_next_queue_element_ = Nil;
	  subblock = Nil;
	  if (ab_queue_form_)
	      ab_next_queue_element_ = 
		      constant_queue_next(ISVREF(ab_queue_form_,
		      (SI_Long)2L),ab_queue_form_);
	next_loop_1:
	  if ( !TRUEP(ab_next_queue_element_))
	      goto end_loop_1;
	  subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	  ab_next_queue_element_ = 
		  constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	  if ( !((SI_Long)0L != (IFIX(ISVREF(subblock,(SI_Long)5L)) & 
		  (SI_Long)786432L))) {
	      sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Statement_class_description,(SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_2 = (SI_Long)1L;
		  gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		  gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		  temp_2 = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2);
	      else {
		  sub_class_bit_vector = ISVREF(ISVREF(subblock,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Procedure_class_description,
			  (SI_Long)18L));
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp_2 = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2) {
	      sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_2 = (SI_Long)1L;
		  gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		  gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		  temp_2 = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  if (Noting_changes_to_kb_p)
		      note_change_to_block_1(subblock,Qframe_flags);
		  svref_new_value = IFIX(ISVREF(subblock,(SI_Long)4L)) | 
			  (SI_Long)2L;
		  ISVREF(subblock,(SI_Long)4L) = FIX(svref_new_value);
	      }
	      temp_1 = Feature_blt;
	      gensymed_symbol_1 = IFIX(ISVREF(Feature_blt,IFIX(i)));
	      gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)0L) : FIX((SI_Long)0L);
	      gensymed_symbol_2 = IFIX(gensymed_symbol);
	      gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)1L) : FIX((SI_Long)0L);
	      gensymed_symbol_3 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = gensymed_symbol_2 ^ gensymed_symbol_3;
	      gensymed_symbol_3 = (SI_Long)255L;
	      gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	      svref_new_value = gensymed_symbol_1 ^ gensymed_symbol_2;
	      SVREF(temp_1,i) = FIX(svref_new_value);
	      i = chestnut_modf_function(FIXNUM_ADD1(i),FIX((SI_Long)8L));
	  }
	  goto next_loop_1;
	end_loop_1:;
	  temp_1 = Feature_blt;
	  gensymed_symbol_1 = IFIX(ISVREF(Feature_blt,(SI_Long)1L));
	  gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	  ab_queue_form_ = gensymed_symbol;
	  ab_next_queue_element_ = Nil;
	  subblock = Nil;
	  ab_loopvar_ = (SI_Long)0L;
	  if (ab_queue_form_)
	      ab_next_queue_element_ = 
		      constant_queue_next(ISVREF(ab_queue_form_,
		      (SI_Long)2L),ab_queue_form_);
	next_loop_2:
	  if ( !TRUEP(ab_next_queue_element_))
	      goto end_loop_2;
	  subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	  ab_next_queue_element_ = 
		  constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	  if ( !((SI_Long)0L != (IFIX(ISVREF(subblock,(SI_Long)5L)) & 
		  (SI_Long)786432L))) {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(Qfree_text,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(subblock,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
			  (SI_Long)18L));
		  sub_class_vector_index = superior_class_bit_number >>  - 
			   - (SI_Long)3L;
		  if (sub_class_vector_index < 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			      {
		      gensymed_symbol_2 = 
			      UBYTE_8_ISAREF_1(sub_class_bit_vector,
			      sub_class_vector_index);
		      gensymed_symbol_3 = (SI_Long)1L;
		      gensymed_symbol_4 = superior_class_bit_number & 
			      (SI_Long)7L;
		      gensymed_symbol_3 = gensymed_symbol_3 << 
			      gensymed_symbol_4;
		      gensymed_symbol_2 = gensymed_symbol_2 & 
			      gensymed_symbol_3;
		      temp_2 = (SI_Long)0L < gensymed_symbol_2;
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2);
	      else {
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(Qborderless_free_text,
			  Class_description_gkbprop);
		  if (gensymed_symbol) {
		      sub_class_bit_vector = ISVREF(ISVREF(subblock,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
		      if (sub_class_vector_index < 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				  {
			  gensymed_symbol_2 = 
				  UBYTE_8_ISAREF_1(sub_class_bit_vector,
				  sub_class_vector_index);
			  gensymed_symbol_3 = (SI_Long)1L;
			  gensymed_symbol_4 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_3 = gensymed_symbol_3 << 
				  gensymed_symbol_4;
			  gensymed_symbol_2 = gensymed_symbol_2 & 
				  gensymed_symbol_3;
			  temp_2 = (SI_Long)0L < gensymed_symbol_2;
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	      if (temp_2);
	      else {
		  sub_class_bit_vector = ISVREF(ISVREF(subblock,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Object_class_description,(SI_Long)18L));
		  sub_class_vector_index = superior_class_bit_number >>  - 
			   - (SI_Long)3L;
		  if (sub_class_vector_index < 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			      {
		      gensymed_symbol_2 = 
			      UBYTE_8_ISAREF_1(sub_class_bit_vector,
			      sub_class_vector_index);
		      gensymed_symbol_3 = (SI_Long)1L;
		      gensymed_symbol_4 = superior_class_bit_number & 
			      (SI_Long)7L;
		      gensymed_symbol_3 = gensymed_symbol_3 << 
			      gensymed_symbol_4;
		      gensymed_symbol_2 = gensymed_symbol_2 & 
			      gensymed_symbol_3;
		      temp_2 = (SI_Long)0L < gensymed_symbol_2;
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	  goto next_loop_2;
	end_loop_2:
	  gensymed_symbol_2 = ab_loopvar_;
	  goto end_1;
	  gensymed_symbol_2 = IFIX(Qnil);
	end_1:;
	  gensymed_symbol_3 = (SI_Long)255L;
	  gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	  svref_new_value = gensymed_symbol_1 ^ gensymed_symbol_2;
	  ISVREF(temp_1,(SI_Long)1L) = FIX(svref_new_value);
      }
      mixin_class_attributes(Feature_blt,Roman_character_map,FIX((SI_Long)5L));
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(kb_workspace,Qdisplay_stack_priority);
      svref_new_value = IFIX(ISVREF(Feature_blt,(SI_Long)0L)) + 
	      (IFIX(ISVREF(Feature_blt,(SI_Long)1L)) << (SI_Long)8L) + 
	      (IFIX(ISVREF(Feature_blt,(SI_Long)2L)) << (SI_Long)13L);
      result = VALUES_1(ISVREF(kb_workspace,(SI_Long)27L) = 
	      FIX(svref_new_value));
    POP_SPECIAL();
    return result;
}

/* MODULO-STRING-HASH */
Object modulo_string_hash(text_string,modulus)
    Object text_string, modulus;
{
    Object length_1, w, i, result_1;

    x_note_fn_call(107,155);
    length_1 = lengthw(text_string);
    w = Nil;
    i = FIX((SI_Long)0L);
    result_1 = FIX((SI_Long)0L);
  next_loop:
  next_loop_1:
    if (FIXNUM_GE(i,length_1))
	goto end_loop;
    w = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(text_string,IFIX(i))),
	    FIX((SI_Long)36L));
    if (w) {
	i = FIXNUM_ADD1(i);
	goto end_1;
    }
    i = FIXNUM_ADD1(i);
    goto next_loop_1;
  end_loop:
    w = Nil;
  end_1:
    if ( !TRUEP(w))
	return VALUES_1(result_1);
    result_1 = chestnut_modf_function(FIX(IFIX(result_1) ^ IFIX(w) * 
	    (SI_Long)354673L),modulus);
    goto next_loop;
  end_loop_1:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Supported_ok_file_format_version, Qsupported_ok_file_format_version);

static Object Kincompatible_ok_file;  /* :incompatible-ok-file */

/* OK-FILE-IS-INCOMPATIBLE-WITH-IMAGE */
Object ok_file_is_incompatible_with_image(version_number)
    Object version_number;
{
    x_note_fn_call(107,156);
    return VALUES_1(FIXNUM_GT(version_number,
	    Supported_ok_file_format_version) ? ( !(IFIX(version_number) 
	    == (SI_Long)3L) ? Kincompatible_ok_file : Nil) : Nil);
}

static Object string_constant_67;  /* "~(begin ~S~%~)" */

static Object string_constant_68;  /* "~(  ~NN:" */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object string_constant_69;  /* ";~&" */

static Object string_constant_70;  /* "~(end ~S~%~)" */

/* WRITE-PART-DESCRIPTION-TO-STREAM */
Object write_part_description_to_stream(s,part_description)
    Object s, part_description;
{
    Object type, key, value, ab_loop_list_, result_string, temp;

    x_note_fn_call(107,157);
    type = FIRST(part_description);
    key = Nil;
    value = Nil;
    ab_loop_list_ = REST(part_description);
    result_string = tformat_text_string(2,string_constant_67,type);
    write_text_string_to_stream(result_string,s);
    reclaim_text_string(result_string);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    key = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    result_string = tformat_text_string(2,string_constant_68,key);
    write_text_string_to_stream(result_string,s);
    reclaim_text_string(result_string);
    write_part_description_value_to_stream(s,value,memq_function(key,
	    list_constant_4) ? list_constant_5 : Nil);
    result_string = tformat_text_string(1,string_constant_69);
    write_text_string_to_stream(result_string,s);
    reclaim_text_string(result_string);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    result_string = tformat_text_string(2,string_constant_70,type);
    write_text_string_to_stream(result_string,s);
    reclaim_text_string(result_string);
    return VALUES_1(Qnil);
}

static Object string_constant_71;  /* " none" */

static Object string_constant_72;  /* " false" */

static Object string_constant_73;  /* " ~S" */

static Object string_constant_74;  /* " ~D" */

static Object string_constant_75;  /* " ~NN" */

static Object string_constant_76;  /* " (" */

static Object string_constant_77;  /* "~%                " */

static Object string_constant_78;  /* " )" */

/* WRITE-PART-DESCRIPTION-VALUE-TO-STREAM */
Object write_part_description_value_to_stream(s,v,advice)
    Object s, v, advice;
{
    Object result_string, e, ab_loop_list_;
    char long_qm;

    x_note_fn_call(107,158);
    if (EQ(Nil,v)) {
	result_string = tformat_text_string(1,memq_function(Qlist,advice) ?
		 string_constant_71 : string_constant_72);
	write_text_string_to_stream(result_string,s);
	return reclaim_text_string(result_string);
    }
    else if (STRINGP(v)) {
	result_string = tformat_text_string(2,string_constant_73,v);
	write_text_string_to_stream(result_string,s);
	return reclaim_text_string(result_string);
    }
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(v) != (SI_Long)0L) {
	result_string = tformat_text_string(2,string_constant_73,v);
	write_text_string_to_stream(result_string,s);
	return reclaim_text_string(result_string);
    }
    else if (FIXNUMP(v)) {
	result_string = tformat_text_string(2,string_constant_74,v);
	write_text_string_to_stream(result_string,s);
	return reclaim_text_string(result_string);
    }
    else if (SYMBOLP(v)) {
	result_string = tformat_text_string(2,string_constant_75,v);
	write_text_string_to_stream(result_string,s);
	return reclaim_text_string(result_string);
    }
    else if (LISTP(v)) {
	result_string = tformat_text_string(1,string_constant_76);
	write_text_string_to_stream(result_string,s);
	reclaim_text_string(result_string);
	long_qm = (SI_Long)5L < IFIX(length(v));
	e = Nil;
	ab_loop_list_ = v;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	e = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (long_qm) {
	    result_string = tformat_text_string(1,string_constant_77);
	    write_text_string_to_stream(result_string,s);
	    reclaim_text_string(result_string);
	}
	write_part_description_value_to_stream(s,e,Nil);
	goto next_loop;
      end_loop:;
	result_string = tformat_text_string(1,string_constant_78);
	write_text_string_to_stream(result_string,s);
	return reclaim_text_string(result_string);
    }
    else
	return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Reading_ok_file, Qreading_ok_file);

DEFINE_VARIABLE_WITH_SYMBOL(G2_stream_of_ok_file_reader, Qg2_stream_of_ok_file_reader);

DEFINE_VARIABLE_WITH_SYMBOL(Buffer_of_ok_file_reader, Qbuffer_of_ok_file_reader);

DEFINE_VARIABLE_WITH_SYMBOL(Buffer_index_of_ok_file_reader, Qbuffer_index_of_ok_file_reader);

DEFINE_VARIABLE_WITH_SYMBOL(Characters_in_buffer_of_ok_file_reader_qm, Qcharacters_in_buffer_of_ok_file_reader_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Buffer_length_of_ok_file_reader, Qbuffer_length_of_ok_file_reader);

DEFINE_VARIABLE_WITH_SYMBOL(Unread_char_of_ok_file_reader_qm, Qunread_char_of_ok_file_reader_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Line_number_of_ok_file_reader, Qline_number_of_ok_file_reader);

/* COMPUTE-PROCESS-INITIAL-VALUE-FOR-PAD-FOR-OK-FILE-READER */
Object compute_process_initial_value_for_pad_for_ok_file_reader()
{
    Object temp;

    x_note_fn_call(107,159);
    temp = make_string(1,FIX((SI_Long)100L));
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pad_for_ok_file_reader, Qpad_for_ok_file_reader);

DEFINE_VARIABLE_WITH_SYMBOL(Error_of_ok_file_reader_qm, Qerror_of_ok_file_reader_qm);

DEFINE_VARIABLE_WITH_SYMBOL(File_format_version_of_g2_ok_file_qm, Qfile_format_version_of_g2_ok_file_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Authorized_user_records_of_g2_ok_file, Qauthorized_user_records_of_g2_ok_file);

DEFINE_VARIABLE_WITH_SYMBOL(Useful_machine_authorization_info, Quseful_machine_authorization_info);

DEFINE_VARIABLE_WITH_SYMBOL(Slot_pad_of_ok_file_reader, Qslot_pad_of_ok_file_reader);

DEFINE_VARIABLE_WITH_SYMBOL(Success_of_ok_file_reader_qm, Qsuccess_of_ok_file_reader_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Saw_more_than_one_machine_authorization_qm, Qsaw_more_than_one_machine_authorization_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_machine_ids_of_g2_ok_file_qm, Qcurrent_machine_ids_of_g2_ok_file_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Read_ok_file_buffer_1, Qread_ok_file_buffer_1);

static Object string_constant_79;  /* "~%OK file error ~a" */

/* ERROR-BROKE-RULE-READING-OK-FILE */
Object error_broke_rule_reading_ok_file varargs_1(int, n)
{
    Object constant_text_of_rule_broken;
    Object do_not_report_the_line_number_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(107,160);
    INIT_ARGS_nonrelocating();
    constant_text_of_rule_broken = REQUIRED_ARG_nonrelocating();
    do_not_report_the_line_number_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(Error_of_ok_file_reader_qm)) {
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
		  tformat(2,string_constant_79,
			  formulate_ok_error_message(2,
			  constant_text_of_rule_broken,
			  do_not_report_the_line_number_qm));
		  Error_of_ok_file_reader_qm = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return VALUES_1(Error_of_ok_file_reader_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_80;  /* "OK file warning. Possible problem~a" */

static Object string_constant_81;  /* "~%~a~%" */

/* WARNING-WHILE-READING-OK-FILE */
Object warning_while_reading_ok_file varargs_1(int, n)
{
    Object constant_text_of_rule_broken;
    Object do_not_report_the_line_number_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1, write_console_p;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(107,161);
    INIT_ARGS_nonrelocating();
    constant_text_of_rule_broken = REQUIRED_ARG_nonrelocating();
    do_not_report_the_line_number_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	      tformat(2,string_constant_80,formulate_ok_error_message(2,
		      constant_text_of_rule_broken,
		      do_not_report_the_line_number_qm));
	      message_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    write_console_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Write_console_p,Qwrite_console_p,write_console_p,
	    0);
      notify_user_at_console(2,string_constant_81,message_1);
    POP_SPECIAL();
    return reclaim_text_string(message_1);
}

static Object string_constant_82;  /* " on or near line ~D" */

static Object string_constant_83;  /* "~%Rule broken: ~A" */

/* FORMULATE-OK-ERROR-MESSAGE */
Object formulate_ok_error_message varargs_1(int, n)
{
    Object constant_text_of_rule_broken;
    Object do_not_report_the_line_number_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(107,162);
    INIT_ARGS_nonrelocating();
    constant_text_of_rule_broken = REQUIRED_ARG_nonrelocating();
    do_not_report_the_line_number_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	      if ( !TRUEP(do_not_report_the_line_number_qm)) {
		  if ((SI_Long)0L < IFIX(Line_number_of_ok_file_reader))
		      tformat(2,string_constant_82,
			      Line_number_of_ok_file_reader);
	      }
	      tformat(2,string_constant_83,constant_text_of_rule_broken);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object Character_table_for_g2_ok_file = UNBOUND;

static Object Keof;                /* :eof */

/* READ-CHAR-FROM-OK-FILE */
Object read_char_from_ok_file()
{
    Object temp, buffer_index_of_ok_file_reader_new_value;

    x_note_fn_call(107,163);
    if (Unread_char_of_ok_file_reader_qm) {
	temp = Unread_char_of_ok_file_reader_qm;
	Unread_char_of_ok_file_reader_qm = Nil;
	return VALUES_1(temp);
    }
    else if (EQ(FIX((SI_Long)0L),Characters_in_buffer_of_ok_file_reader_qm))
	return VALUES_1(Keof);
    else if (FIXNUM_LT(Buffer_index_of_ok_file_reader,
	    Characters_in_buffer_of_ok_file_reader_qm)) {
	temp = SCHAR(Buffer_of_ok_file_reader,Buffer_index_of_ok_file_reader);
	buffer_index_of_ok_file_reader_new_value = 
		FIXNUM_ADD1(Buffer_index_of_ok_file_reader);
	Buffer_index_of_ok_file_reader = 
		buffer_index_of_ok_file_reader_new_value;
	return VALUES_1(temp);
    }
    else {
	Characters_in_buffer_of_ok_file_reader_qm = 
		g2_stream_read_into_buffer(Buffer_of_ok_file_reader,
		Buffer_length_of_ok_file_reader,G2_stream_of_ok_file_reader);
	if (EQ(FIX((SI_Long)0L),Characters_in_buffer_of_ok_file_reader_qm))
	    return VALUES_1(Keof);
	else {
	    Buffer_index_of_ok_file_reader = FIX((SI_Long)1L);
	    return VALUES_1(SCHAR(Buffer_of_ok_file_reader,FIX((SI_Long)0L)));
	}
    }
}

/* UNREAD-CHAR-FROM-OK-FILE */
Object unread_char_from_ok_file(c)
    Object c;
{
    x_note_fn_call(107,164);
    Unread_char_of_ok_file_reader_qm = c;
    return VALUES_1(Unread_char_of_ok_file_reader_qm);
}

/* OK-FILE-SANITY-CHECK */
Object ok_file_sanity_check(prefix_string)
    Object prefix_string;
{
    Object temp, temporary_wide_string_copy;

    x_note_fn_call(107,165);
    temp = Buffer_of_ok_file_reader;
    temporary_wide_string_copy = text_string_substring(temp,
	    FIX((SI_Long)0L),lengthw(prefix_string));
    temp = Symbol_token_match_should_be_case_sensitive_p ? 
	    string_eq_w(prefix_string,temporary_wide_string_copy) : 
	    string_equalw(prefix_string,temporary_wide_string_copy);
    reclaim_wide_string(temporary_wide_string_copy);
    return VALUES_1(temp);
}

Object The_type_description_of_ok_file_token = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_ok_file_tokens, Qchain_of_available_ok_file_tokens);

DEFINE_VARIABLE_WITH_SYMBOL(Ok_file_token_count, Qok_file_token_count);

Object Chain_of_available_ok_file_tokens_vector = UNBOUND;

/* OK-FILE-TOKEN-STRUCTURE-MEMORY-USAGE */
Object ok_file_token_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(107,166);
    temp = Ok_file_token_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-OK-FILE-TOKEN-COUNT */
Object outstanding_ok_file_token_count()
{
    Object def_structure_ok_file_token_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(107,167);
    gensymed_symbol = IFIX(Ok_file_token_count);
    def_structure_ok_file_token_variable = Chain_of_available_ok_file_tokens;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_ok_file_token_variable))
	goto end_loop;
    def_structure_ok_file_token_variable = 
	    ISVREF(def_structure_ok_file_token_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-OK-FILE-TOKEN-1 */
Object reclaim_ok_file_token_1(ok_file_token)
    Object ok_file_token;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(107,168);
    inline_note_reclaim_cons(ok_file_token,Nil);
    structure_being_reclaimed = ok_file_token;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_text_string(ISVREF(ok_file_token,(SI_Long)3L));
      SVREF(ok_file_token,FIX((SI_Long)3L)) = Nil;
      reclaim_ok_file_value(ISVREF(ok_file_token,(SI_Long)4L));
      SVREF(ok_file_token,FIX((SI_Long)4L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_ok_file_tokens_vector,
	    IFIX(Current_thread_index));
    SVREF(ok_file_token,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_ok_file_tokens_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = ok_file_token;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-OK-FILE-TOKEN */
Object reclaim_structure_for_ok_file_token(ok_file_token)
    Object ok_file_token;
{
    x_note_fn_call(107,169);
    return reclaim_ok_file_token_1(ok_file_token);
}

static Object Qg2_defstruct_structure_name_ok_file_token_g2_struct;  /* g2-defstruct-structure-name::ok-file-token-g2-struct */

/* MAKE-PERMANENT-OK-FILE-TOKEN-STRUCTURE-INTERNAL */
Object make_permanent_ok_file_token_structure_internal()
{
    Object def_structure_ok_file_token_variable;
    Object defstruct_g2_ok_file_token_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(107,170);
    def_structure_ok_file_token_variable = Nil;
    atomic_incff_symval(Qok_file_token_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_ok_file_token_variable = Nil;
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
	defstruct_g2_ok_file_token_variable = the_array;
	SVREF(defstruct_g2_ok_file_token_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ok_file_token_g2_struct;
	def_structure_ok_file_token_variable = 
		defstruct_g2_ok_file_token_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_ok_file_token_variable);
}

/* MAKE-OK-FILE-TOKEN-1-1 */
Object make_ok_file_token_1_1(kind_of_ok_file_token,text_of_ok_file_token)
    Object kind_of_ok_file_token, text_of_ok_file_token;
{
    Object def_structure_ok_file_token_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(107,171);
    def_structure_ok_file_token_variable = 
	    ISVREF(Chain_of_available_ok_file_tokens_vector,
	    IFIX(Current_thread_index));
    if (def_structure_ok_file_token_variable) {
	temp = Chain_of_available_ok_file_tokens_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_ok_file_token_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_ok_file_token_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ok_file_token_g2_struct;
    }
    else
	def_structure_ok_file_token_variable = 
		make_permanent_ok_file_token_structure_internal();
    inline_note_allocate_cons(def_structure_ok_file_token_variable,Nil);
    SVREF(def_structure_ok_file_token_variable,FIX((SI_Long)1L)) = 
	    kind_of_ok_file_token;
    SVREF(def_structure_ok_file_token_variable,FIX((SI_Long)3L)) = 
	    text_of_ok_file_token;
    temp = Line_number_of_ok_file_reader;
    SVREF(def_structure_ok_file_token_variable,FIX((SI_Long)2L)) = temp;
    SVREF(def_structure_ok_file_token_variable,FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_ok_file_token_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Contour_of_ok_file_tokens, Qcontour_of_ok_file_tokens);

DEFINE_VARIABLE_WITH_SYMBOL(Available_ok_file_token_conses, Qavailable_ok_file_token_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_ok_file_token_conses_tail, Qavailable_ok_file_token_conses_tail);

Object Available_ok_file_token_conses_vector = UNBOUND;

Object Available_ok_file_token_conses_tail_vector = UNBOUND;

Object Ok_file_token_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Ok_file_token_cons_counter, Qok_file_token_cons_counter);

/* OUTSTANDING-OK-FILE-TOKEN-CONSES */
Object outstanding_ok_file_token_conses()
{
    Object temp;

    x_note_fn_call(107,172);
    temp = FIXNUM_MINUS(Ok_file_token_cons_counter,
	    length(Available_ok_file_token_conses));
    return VALUES_1(temp);
}

/* OK-FILE-TOKEN-CONS-MEMORY-USAGE */
Object ok_file_token_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(107,173);
    temp = FIXNUM_TIMES(Ok_file_token_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-OK-FILE-TOKEN-CONS-POOL */
Object replenish_ok_file_token_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(107,174);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qok_file_token_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_ok_file_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_ok_file_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_ok_file_token_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Ok_file_token_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qok_file_token;      /* ok-file-token */

/* OK-FILE-TOKEN-CONS-1 */
Object ok_file_token_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(107,175);
    new_cons = ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_ok_file_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_ok_file_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_ok_file_token_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qok_file_token);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-OK-FILE-TOKEN-LIST-POOL */
Object replenish_ok_file_token_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(107,176);
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
    if (ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_ok_file_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_ok_file_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_ok_file_token_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qok_file_token_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-OK-FILE-TOKEN-LIST-1 */
Object make_ok_file_token_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(107,177);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_ok_file_token_conses_vector,
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
	replenish_ok_file_token_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_ok_file_token_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qok_file_token);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_ok_file_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_ok_file_token_conses_tail_vector;
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

/* OK-FILE-TOKEN-LIST-2 */
Object ok_file_token_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(107,178);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_ok_file_token_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qok_file_token);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_ok_file_token_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_ok_file_token_conses_tail_vector;
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

/* OK-FILE-TOKEN-LIST-3 */
Object ok_file_token_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(107,179);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_ok_file_token_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qok_file_token);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_ok_file_token_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_ok_file_token_conses_tail_vector;
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

/* OK-FILE-TOKEN-LIST-4 */
Object ok_file_token_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(107,180);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_ok_file_token_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qok_file_token);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_ok_file_token_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_ok_file_token_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_ok_file_token_conses_tail_vector;
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

/* OK-FILE-TOKEN-LIST-TRACE-HOOK */
Object ok_file_token_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(107,181);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-OK-FILE-TOKEN-CONSES-1 */
Object copy_tree_using_ok_file_token_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(107,182);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_ok_file_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_ok_file_token_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_ok_file_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_ok_file_token_cons_pool();
	temp_1 = copy_tree_using_ok_file_token_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qok_file_token);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_ok_file_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_ok_file_token_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_ok_file_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_ok_file_token_cons_pool();
	temp_1 = 
		copy_tree_using_ok_file_token_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qok_file_token);
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

/* COPY-LIST-USING-OK-FILE-TOKEN-CONSES-1 */
Object copy_list_using_ok_file_token_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(107,183);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_ok_file_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_ok_file_token_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_ok_file_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_ok_file_token_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qok_file_token);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_ok_file_token_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_ok_file_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_ok_file_token_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_ok_file_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_ok_file_token_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qok_file_token);
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

/* RECLAIM-OK-FILE-TOKEN-CONS-1 */
Object reclaim_ok_file_token_cons_1(ok_file_token_cons)
    Object ok_file_token_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(107,184);
    inline_note_reclaim_cons(ok_file_token_cons,Qok_file_token);
    if (ISVREF(Available_ok_file_token_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_ok_file_token_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = ok_file_token_cons;
	temp = Available_ok_file_token_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = ok_file_token_cons;
    }
    else {
	temp = Available_ok_file_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = ok_file_token_cons;
	temp = Available_ok_file_token_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = ok_file_token_cons;
    }
    M_CDR(ok_file_token_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-OK-FILE-TOKEN-LIST-1 */
Object reclaim_ok_file_token_list_1(ok_file_token_list)
    Object ok_file_token_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(107,185);
    if (ok_file_token_list) {
	last_1 = ok_file_token_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qok_file_token);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qok_file_token);
	if (ISVREF(Available_ok_file_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_ok_file_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = ok_file_token_list;
	    temp = Available_ok_file_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_ok_file_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = ok_file_token_list;
	    temp = Available_ok_file_token_conses_tail_vector;
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

/* RECLAIM-OK-FILE-TOKEN-LIST*-1 */
Object reclaim_ok_file_token_list_star_1(ok_file_token_list)
    Object ok_file_token_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(107,186);
    if (CONSP(ok_file_token_list)) {
	temp = last(ok_file_token_list,_);
	M_CDR(temp) = Nil;
	if (ok_file_token_list) {
	    last_1 = ok_file_token_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qok_file_token);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qok_file_token);
	    if (ISVREF(Available_ok_file_token_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_ok_file_token_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = ok_file_token_list;
		temp = Available_ok_file_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_ok_file_token_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = ok_file_token_list;
		temp = Available_ok_file_token_conses_tail_vector;
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

/* RECLAIM-OK-FILE-TOKEN-TREE-1 */
Object reclaim_ok_file_token_tree_1(tree)
    Object tree;
{
    Object e, e2, ok_file_token_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(107,187);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_ok_file_token_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		ok_file_token_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(ok_file_token_cons,Qok_file_token);
		if (EQ(ok_file_token_cons,e))
		    goto end_1;
		else if ( !TRUEP(ok_file_token_cons))
		    goto end_1;
		else
		    ok_file_token_cons = CDR(ok_file_token_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_ok_file_token_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_ok_file_token_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_ok_file_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_ok_file_token_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_ok_file_token_conses_tail_vector;
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

/* DELETE-OK-FILE-TOKEN-ELEMENT-1 */
Object delete_ok_file_token_element_1(element,ok_file_token_list)
    Object element, ok_file_token_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(107,188);
    if (ok_file_token_list) {
	if (EQ(element,M_CAR(ok_file_token_list))) {
	    temp = CDR(ok_file_token_list);
	    inline_note_reclaim_cons(ok_file_token_list,Qok_file_token);
	    if (ISVREF(Available_ok_file_token_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_ok_file_token_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = ok_file_token_list;
		temp_1 = Available_ok_file_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = ok_file_token_list;
	    }
	    else {
		temp_1 = Available_ok_file_token_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = ok_file_token_list;
		temp_1 = Available_ok_file_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = ok_file_token_list;
	    }
	    M_CDR(ok_file_token_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = ok_file_token_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qok_file_token);
		if (ISVREF(Available_ok_file_token_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_ok_file_token_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_ok_file_token_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_ok_file_token_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_ok_file_token_conses_tail_vector;
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
	    temp = ok_file_token_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-OK-FILE-TOKEN-CONS-1 */
Object delete_ok_file_token_cons_1(ok_file_token_cons,ok_file_token_list)
    Object ok_file_token_cons, ok_file_token_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(107,189);
    if (EQ(ok_file_token_cons,ok_file_token_list))
	temp = CDR(ok_file_token_list);
    else {
	l_trailer_qm = Nil;
	l = ok_file_token_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,ok_file_token_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = ok_file_token_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_ok_file_token_cons_1(ok_file_token_cons);
    return VALUES_1(temp);
}

/* MAKE-OK-FILE-TOKEN */
Object make_ok_file_token(kind,text)
    Object kind, text;
{
    Object result_1;

    x_note_fn_call(107,190);
    result_1 = make_ok_file_token_1_1(kind,text);
    Contour_of_ok_file_tokens = ok_file_token_cons_1(result_1,
	    Contour_of_ok_file_tokens);
    return VALUES_1(result_1);
}

/* RECLAIM-CONTOUR-OF-OK-FILE-TOKENS */
Object reclaim_contour_of_ok_file_tokens()
{
    Object ok_file_token, ab_loop_list_;

    x_note_fn_call(107,191);
    ok_file_token = Nil;
    ab_loop_list_ = Contour_of_ok_file_tokens;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ok_file_token = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_ok_file_token_1(ok_file_token);
    goto next_loop;
  end_loop:;
    reclaim_ok_file_token_list_1(Contour_of_ok_file_tokens);
    Contour_of_ok_file_tokens = Nil;
    return VALUES_1(Nil);
}

static Object array_constant_11;   /* # */

/* MAKE-CONSTANT-TOKEN */
Object make_constant_token(constant)
    Object constant;
{
    x_note_fn_call(107,192);
    return make_ok_file_token(constant,
	    copy_constant_wide_string_given_length(array_constant_11,
	    FIX((SI_Long)0L)));
}

static Object Klist;               /* :list */

/* MAKE-LIST-TOKEN */
Object make_list_token(list_1)
    Object list_1;
{
    Object result_1;

    x_note_fn_call(107,193);
    result_1 = make_constant_token(Klist);
    SVREF(result_1,FIX((SI_Long)4L)) = list_1;
    return VALUES_1(result_1);
}

static Object Killegal;            /* :illegal */

/* MAKE-ILLEGAL-TOKEN */
Object make_illegal_token(constant_text_of_rule_broken)
    Object constant_text_of_rule_broken;
{
    x_note_fn_call(107,194);
    error_broke_rule_reading_ok_file(1,constant_text_of_rule_broken);
    return make_constant_token(Killegal);
}

/* TOKEN-KIND-IS */
Object token_kind_is(kind,token)
    Object kind, token;
{
    x_note_fn_call(107,195);
    return VALUES_1(EQ(kind,ISVREF(token,(SI_Long)1L)) ? T : Nil);
}

static Object Ksymbol;             /* :symbol */

/* SYMBOL-TOKEN-MATCH */
Object symbol_token_match(string_1,token)
    Object string_1, token;
{
    x_note_fn_call(107,196);
    if (EQ(Ksymbol,ISVREF(token,(SI_Long)1L))) {
	if (Symbol_token_match_should_be_case_sensitive_p)
	    return string_eq_w(string_1,ISVREF(token,(SI_Long)3L));
	else
	    return string_equalw(string_1,ISVREF(token,(SI_Long)3L));
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-OK-FILE-VALUE */
Object reclaim_ok_file_value(value)
    Object value;
{
    Object temp;

    x_note_fn_call(107,197);
    temp = SYMBOLP(value) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (CONSP(value)) {
	reclaim_ok_file_value(CAR(value));
	reclaim_ok_file_value(CDR(value));
	return reclaim_ok_file_token_cons_1(value);
    }
    else {
	temp = SIMPLE_VECTOR_P(value) ? (EQ(ISVREF(value,(SI_Long)0L),
		Qg2_defstruct_structure_name_ok_file_token_g2_struct) ? T :
		 Nil) : Qnil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return reclaim_slot_value(value);
    }
}

/* COERCE-TOKEN-TO-LISP */
Object coerce_token_to_lisp(token_or_value)
    Object token_or_value;
{
    Object i, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object svref_new_value;

    x_note_fn_call(107,198);
    if (CONSP(token_or_value)) {
	i = Nil;
	ab_loop_list_ = token_or_value;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	i = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = ok_file_token_cons_1(coerce_token_to_lisp(i),Nil);
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
    else if (SIMPLE_VECTOR_P(token_or_value) && EQ(ISVREF(token_or_value,
	    (SI_Long)0L),
		Qg2_defstruct_structure_name_ok_file_token_g2_struct)) {
	temp = ISVREF(token_or_value,(SI_Long)1L);
	if (EQ(temp,Ksymbol)) {
	    svref_new_value = intern_wide_string(1,
		    copy_wide_string(nstring_upcasew(ISVREF(token_or_value,
		    (SI_Long)3L))));
	    return VALUES_1(SVREF(token_or_value,FIX((SI_Long)4L)) = 
		    svref_new_value);
	}
	else if (EQ(temp,Klist))
	    return coerce_token_to_lisp(ISVREF(token_or_value,(SI_Long)4L));
	else
	    return VALUES_1(ISVREF(token_or_value,(SI_Long)4L));
    }
    else
	return VALUES_1(Qnil);
}

static Object Kclose_paren;        /* :close-paren */

static Object Kcolon;              /* :colon */

static Object Ksemicolon;          /* :semicolon */

/* READ-TOKEN-FROM-OK-FILE */
Object read_token_from_ok_file()
{
    Object char_1, temp, line_number_of_ok_file_reader_new_value;

    x_note_fn_call(107,199);
    if ( !TRUEP(Characters_in_buffer_of_ok_file_reader_qm))
	return VALUES_1(Keof);
    char_1 = Nil;
  next_loop:
    char_1 = read_char_from_ok_file();
    if (EQ(char_1,Keof))
	return make_constant_token(Keof);
    temp = ISVREF(Character_table_for_g2_ok_file,IFIX(CHAR_CODE(char_1)));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	return make_constant_token(make_illegal_token(character_cannot_start_token_ok_message()));
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 10:
	    if ( !EQ(CHR('\n'),read_char_from_ok_file()))
		unread_char_from_ok_file(char_1);
	    line_number_of_ok_file_reader_new_value = 
		    FIXNUM_ADD1(Line_number_of_ok_file_reader);
	    Line_number_of_ok_file_reader = 
		    line_number_of_ok_file_reader_new_value;
	    break;
	  case 11:
	    line_number_of_ok_file_reader_new_value = 
		    FIXNUM_ADD1(Line_number_of_ok_file_reader);
	    Line_number_of_ok_file_reader = 
		    line_number_of_ok_file_reader_new_value;
	    break;
	  case 7:
	    if ( !EQ(CHR('-'),read_char_from_ok_file()))
		return make_illegal_token(hyphen_not_followed_by_another_hyphen_ok_message());
	    char_1 = Nil;
	  next_loop_1:
	    char_1 = read_char_from_ok_file();
	    if (EQ(Keof,char_1))
		return make_constant_token(Keof);
	    if (EQ(CHR('\n'),char_1)) {
		line_number_of_ok_file_reader_new_value = 
			FIXNUM_ADD1(Line_number_of_ok_file_reader);
		Line_number_of_ok_file_reader = 
			line_number_of_ok_file_reader_new_value;
		goto end_1;
	    }
	    if (EQ(CHR('\r'),char_1)) {
		if ( !EQ(CHR('\n'),read_char_from_ok_file()))
		    unread_char_from_ok_file(char_1);
		line_number_of_ok_file_reader_new_value = 
			FIXNUM_ADD1(Line_number_of_ok_file_reader);
		Line_number_of_ok_file_reader = 
			line_number_of_ok_file_reader_new_value;
	    }
	    goto next_loop_1;
	  end_loop:
	  end_1:;
	    break;
	  case 1:
	    break;
	  case 2:
	    return read_string_from_ok_file();
	    break;
	  case 3:
	    return read_list_from_ok_file();
	    break;
	  case 4:
	    return make_constant_token(Kclose_paren);
	    break;
	  case 5:
	    return make_constant_token(Kcolon);
	    break;
	  case 6:
	    return make_constant_token(Ksemicolon);
	    break;
	  case 8:
	    return read_integer_from_ok_file(char_1);
	    break;
	  case 9:
	    return read_symbol_from_ok_file(char_1);
	    break;
	  case 12:
	    return read_symbol_from_ok_file(char_1);
	    break;
	  case 14:
	    return read_symbol_from_ok_file(char_1);
	    break;
	  case 13:
	    return read_symbol_from_ok_file(char_1);
	    break;
	  default:
	    return make_constant_token(make_illegal_token(character_cannot_start_token_ok_message()));
	    break;
	}
    goto next_loop;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* TEXT-STRING-OF-PAD-FOR-OK-FILE-READER */
Object text_string_of_pad_for_ok_file_reader(length_1)
    Object length_1;
{
    Object result_1, aref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(107,200);
    result_1 = obtain_text_string(length_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    aref_new_value = CHAR_CODE(CHR(ISCHAR(Pad_for_ok_file_reader,i)));
    UBYTE_16_ISASET_1(result_1,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

static Object Kstring;             /* :string */

static Object list_constant_6;     /* # */

/* READ-STRING-FROM-OK-FILE */
Object read_string_from_ok_file()
{
    Object c, schar_arg_1;
    SI_Long i;

    x_note_fn_call(107,201);
    i = (SI_Long)0L;
    c = Nil;
  next_loop:
    if (i >= (SI_Long)60L)
	goto end_loop;
    c = read_char_from_ok_file();
    if (EQ(c,CHR('\"')))
	return make_ok_file_token(Kstring,
		text_string_of_pad_for_ok_file_reader(FIX(i)));
    if (memq_function(c,list_constant_6))
	return make_illegal_token(illegal_character_in_string_ok_message());
    schar_arg_1 = Pad_for_ok_file_reader;
    SET_ISCHAR(schar_arg_1,i,ICHAR_CODE(c));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return make_illegal_token(string_too_long_ok_message());
    return VALUES_1(Qnil);
}

static Object array_constant_12;   /* # */

/* READ-SYMBOL-FROM-OK-FILE */
Object read_symbol_from_ok_file(first_char)
    Object first_char;
{
    Object schar_arg_1, c, op, temp, result_1;
    SI_Long i;

    x_note_fn_call(107,202);
    schar_arg_1 = Pad_for_ok_file_reader;
    SET_SCHAR(schar_arg_1,FIX((SI_Long)0L),first_char);
    i = (SI_Long)1L;
    c = Nil;
    op = Nil;
  next_loop:
    if (i >= (SI_Long)60L)
	goto end_loop;
    c = read_char_from_ok_file();
    op = EQ(c,Keof) ? Eof_character_for_g2_ok_file : 
	    ISVREF(Character_table_for_g2_ok_file,IFIX(CHAR_CODE(c)));
    temp = op;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L)))) {
	unread_char_from_ok_file(c);
	result_1 = make_ok_file_token(Ksymbol,
		text_string_of_pad_for_ok_file_reader(FIX(i)));
	goto end_1;
    }
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 9:
	  case 8:
	  case 7:
	  case 13:
	  case 12:
	  case 14:
	    schar_arg_1 = Pad_for_ok_file_reader;
	    SET_ISCHAR(schar_arg_1,i,ICHAR_CODE(c));
	    break;
	  case 1:
	    result_1 = make_ok_file_token(Ksymbol,
		    text_string_of_pad_for_ok_file_reader(FIX(i)));
	    goto end_1;
	    break;
	  default:
	    unread_char_from_ok_file(c);
	    result_1 = make_ok_file_token(Ksymbol,
		    text_string_of_pad_for_ok_file_reader(FIX(i)));
	    goto end_1;
	    break;
	}
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    result_1 = make_illegal_token(symbol_too_long_ok_message());
    goto end_1;
    result_1 = Qnil;
  end_1:;
    if (symbol_token_match(array_constant_2,result_1)) {
	SVREF(result_1,FIX((SI_Long)1L)) = Klist;
	SVREF(result_1,FIX((SI_Long)4L)) = Nil;
    }
    else if (symbol_token_match(array_constant_12,result_1))
	SVREF(result_1,FIX((SI_Long)4L)) = T;
    return VALUES_1(result_1);
}

/* READ-INTEGER-FROM-OK-FILE */
Object read_integer_from_ok_file(first_char)
    Object first_char;
{
    Object schar_arg_1, c, op, temp;
    SI_Long i;

    x_note_fn_call(107,203);
    schar_arg_1 = Pad_for_ok_file_reader;
    SET_SCHAR(schar_arg_1,FIX((SI_Long)0L),first_char);
    i = (SI_Long)1L;
    c = Nil;
    op = Nil;
  next_loop:
    if (i >= (SI_Long)40L)
	goto end_loop;
    c = read_char_from_ok_file();
    op = EQ(c,Keof) ? Eof_character_for_g2_ok_file : 
	    ISVREF(Character_table_for_g2_ok_file,IFIX(CHAR_CODE(c)));
    temp = op;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L)))) {
	unread_char_from_ok_file(c);
	return make_integer_ok_file_token_from_text(text_string_of_pad_for_ok_file_reader(FIX(i)));
    }
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 8:
	    schar_arg_1 = Pad_for_ok_file_reader;
	    SET_ISCHAR(schar_arg_1,i,ICHAR_CODE(c));
	    break;
	  case 9:
	  case 12:
	  case 13:
	  case 14:
	    return make_illegal_token(integer_contains_non_digit_character_ok_message());
	    break;
	  case 1:
	    return make_integer_ok_file_token_from_text(text_string_of_pad_for_ok_file_reader(FIX(i)));
	    break;
	  default:
	    unread_char_from_ok_file(c);
	    return make_integer_ok_file_token_from_text(text_string_of_pad_for_ok_file_reader(FIX(i)));
	    break;
	}
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return make_illegal_token(integer_too_long_ok_message());
    return VALUES_1(Qnil);
}

/* MAKE-INTEGER-OK-FILE-TOKEN-FROM-TEXT */
Object make_integer_ok_file_token_from_text(stringw_1)
    Object stringw_1;
{
    Object result_1, digit, temp;
    SI_Long i, length_1, ab_loop_bind_, gensymed_symbol;

    x_note_fn_call(107,204);
    result_1 = FIX((SI_Long)0L);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stringw_1));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(stringw_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(stringw_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    digit = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = UBYTE_16_ISAREF_1(stringw_1,i);
    digit = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
    result_1 = FIX((SI_Long)10L * IFIX(result_1) + IFIX(digit));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = result_1;
    goto end_1;
    temp = Qnil;
  end_1:;
    return make_integer_ok_file_token(stringw_1,temp);
}

static Object Kinteger;            /* :integer */

/* MAKE-INTEGER-OK-FILE-TOKEN */
Object make_integer_ok_file_token(stringw_1,value)
    Object stringw_1, value;
{
    Object token;

    x_note_fn_call(107,205);
    token = make_ok_file_token(Kinteger,stringw_1);
    SVREF(token,FIX((SI_Long)4L)) = value;
    return VALUES_1(token);
}

/* READ-LIST-FROM-OK-FILE */
Object read_list_from_ok_file()
{
    Object element, list_1, ab_loopvar_, ab_loopvar__1, ab_loop_iter_flag_;
    SI_Long i;

    x_note_fn_call(107,206);
    element = Nil;
    i = (SI_Long)0L;
    list_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    element = read_token_from_ok_file();
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    if ((SI_Long)60L <= i)
	return make_illegal_token(too_many_elements_in_list_ok_message());
    if (token_kind_is(Kclose_paren,element))
	goto end_loop;
    ab_loopvar__1 = ok_file_token_cons_1(element,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	list_1 = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return make_list_token(list_1);
    return VALUES_1(Qnil);
}

Object Slot_pad_descriptions_of_machine_authorization = UNBOUND;

Object Slot_pad_descriptions_of_user = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Unbound_value_for_ok_reader, Qunbound_value_for_ok_reader);

/* CLEAR-SLOT-PAD */
Object clear_slot_pad()
{
    Object svref_arg_1, svref_new_value;
    SI_Long i;

    x_note_fn_call(107,207);
    i = (SI_Long)0L;
  next_loop:
    if (i >= (SI_Long)20L)
	goto end_loop;
    svref_arg_1 = Slot_pad_of_ok_file_reader;
    svref_new_value = Unbound_value_for_ok_reader;
    ISVREF(svref_arg_1,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object array_constant_13;   /* # */

static Object Kbegin_entity;       /* :begin-entity */

static Object array_constant_14;   /* # */

static Object Kend_entity;         /* :end-entity */

static Object Kattribute;          /* :attribute */

/* READ-STATEMENT-FROM-OK-FILE */
Object read_statement_from_ok_file()
{
    Object first_token, second_token, third_token, fourth_token, temp_1;
    char temp;

    x_note_fn_call(107,208);
    first_token = read_token_from_ok_file();
    second_token = read_token_from_ok_file();
    third_token = Nil;
    fourth_token = Nil;
    if (token_kind_is(Keof,first_token))
	return VALUES_3(Keof,Nil,Nil);
    else if (symbol_token_match(array_constant_13,first_token) && 
	    token_kind_is(Ksymbol,second_token))
	return VALUES_3(Kbegin_entity,second_token,Nil);
    else if (symbol_token_match(array_constant_14,first_token) && 
	    token_kind_is(Ksymbol,second_token))
	return VALUES_3(Kend_entity,second_token,Nil);
    else {
	if (token_kind_is(Ksymbol,first_token) && token_kind_is(Kcolon,
		second_token)) {
	    third_token = read_token_from_ok_file();
	    temp = TRUEP(third_token);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? token_kind_is(Klist,third_token) || 
		token_kind_is(Kinteger,third_token) || 
		token_kind_is(Kstring,third_token) || 
		token_kind_is(Ksymbol,third_token) : TRUEP(Nil)) {
	    fourth_token = read_token_from_ok_file();
	    temp = TRUEP(token_kind_is(Ksemicolon,fourth_token));
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_3(Kattribute,first_token,third_token);
	else {
	    if (token_kind_is(Keof,second_token))
		temp_1 = eof_in_middle_of_statement_ok_message();
	    else if (fourth_token)
		temp_1 = 
			fourth_element_of_statement_not_a_semicolon_ok_message();
	    else if (third_token)
		temp_1 = illegal_attribute_value_ok_message_1(first_token,
			third_token);
	    else
		temp_1 = unknown_problem_parsing_statement_ok_message();
	    error_broke_rule_reading_ok_file(1,temp_1);
	    return VALUES_3(Killegal,first_token,Nil);
	}
    }
}

static Object string_constant_84;  /* "/home/bhyde/junk/test.ok" */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

/* READ-OK-FILE */
Object read_ok_file varargs_1(int, n)
{
    Object namestring_1, error_of_ok_file_reader_qm;
    Object line_number_of_ok_file_reader;
    volatile Object pathname_used_p;
    volatile Object namestring_2;
    volatile Object stream;
    Object g2_stream_of_ok_file_reader, buffer_of_ok_file_reader;
    Object buffer_length_of_ok_file_reader, unread_char_of_ok_file_reader_qm;
    Object characters_in_buffer_of_ok_file_reader_qm;
    Object buffer_index_of_ok_file_reader;
    Object file_format_version_of_g2_ok_file_qm;
    Object authorized_user_records_of_g2_ok_file;
    Object useful_machine_authorization_info, success_of_ok_file_reader_qm;
    Object saw_more_than_one_machine_authorization_qm;
    Object slot_pad_of_ok_file_reader, contour_of_ok_file_tokens, s, v1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(16);
    Object result;

    x_note_fn_call(107,209);
    INIT_ARGS_nonrelocating();
    SAVE_STACK();
    namestring_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : string_constant_84;
    END_ARGS_nonrelocating();
    LOCK(Reading_ok_file);
    if (PUSH_UNWIND_PROTECT(1)) {
	error_of_ok_file_reader_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Error_of_ok_file_reader_qm,Qerror_of_ok_file_reader_qm,error_of_ok_file_reader_qm,
		15);
	  line_number_of_ok_file_reader = FIX((SI_Long)-1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Line_number_of_ok_file_reader,Qline_number_of_ok_file_reader,line_number_of_ok_file_reader,
		  14);
	    pathname_used_p = Qunbound_in_protected_let;
	    namestring_2 = Qunbound_in_protected_let;
	    stream = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(0)) {
		pathname_used_p = SIMPLE_VECTOR_P(namestring_1) ? 
			(EQ(ISVREF(namestring_1,(SI_Long)0L),
			Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			? T : Nil) : Qnil;
		namestring_2 = SIMPLE_VECTOR_P(namestring_1) && 
			EQ(ISVREF(namestring_1,(SI_Long)0L),
			Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			? gensym_namestring(1,namestring_1) : namestring_1;
		stream = g2_stream_open_for_input(namestring_2);
		if ( !TRUEP(stream))
		    error_broke_rule_reading_ok_file(1,
			    could_not_open_stream_ok_message());
		else if ( !TRUEP(ISVREF(namestring_1,(SI_Long)4L)))
		    error_broke_rule_reading_ok_file(1,
			    no_filename_provided_ok_message());
		else {
		    g2_stream_of_ok_file_reader = stream;
		    PUSH_SPECIAL_WITH_SYMBOL(G2_stream_of_ok_file_reader,Qg2_stream_of_ok_file_reader,g2_stream_of_ok_file_reader,
			    13);
		      buffer_of_ok_file_reader = Read_ok_file_buffer_1;
		      PUSH_SPECIAL_WITH_SYMBOL(Buffer_of_ok_file_reader,Qbuffer_of_ok_file_reader,buffer_of_ok_file_reader,
			      12);
			buffer_length_of_ok_file_reader = 
				length(Buffer_of_ok_file_reader);
			PUSH_SPECIAL_WITH_SYMBOL(Buffer_length_of_ok_file_reader,Qbuffer_length_of_ok_file_reader,buffer_length_of_ok_file_reader,
				11);
			  unread_char_of_ok_file_reader_qm = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Unread_char_of_ok_file_reader_qm,Qunread_char_of_ok_file_reader_qm,unread_char_of_ok_file_reader_qm,
				  10);
			    characters_in_buffer_of_ok_file_reader_qm = 
				    g2_stream_read_into_buffer(Buffer_of_ok_file_reader,
				    Buffer_length_of_ok_file_reader,
				    G2_stream_of_ok_file_reader);
			    PUSH_SPECIAL_WITH_SYMBOL(Characters_in_buffer_of_ok_file_reader_qm,Qcharacters_in_buffer_of_ok_file_reader_qm,characters_in_buffer_of_ok_file_reader_qm,
				    9);
			      buffer_index_of_ok_file_reader = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL_WITH_SYMBOL(Buffer_index_of_ok_file_reader,Qbuffer_index_of_ok_file_reader,buffer_index_of_ok_file_reader,
				      8);
				line_number_of_ok_file_reader = 
					FIX((SI_Long)1L);
				PUSH_SPECIAL_WITH_SYMBOL(Line_number_of_ok_file_reader,Qline_number_of_ok_file_reader,line_number_of_ok_file_reader,
					7);
				  file_format_version_of_g2_ok_file_qm = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(File_format_version_of_g2_ok_file_qm,Qfile_format_version_of_g2_ok_file_qm,file_format_version_of_g2_ok_file_qm,
					  6);
				    authorized_user_records_of_g2_ok_file 
					    = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Authorized_user_records_of_g2_ok_file,Qauthorized_user_records_of_g2_ok_file,authorized_user_records_of_g2_ok_file,
					    5);
				      useful_machine_authorization_info = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Useful_machine_authorization_info,Quseful_machine_authorization_info,useful_machine_authorization_info,
					      4);
					success_of_ok_file_reader_qm = Nil;
					PUSH_SPECIAL_WITH_SYMBOL(Success_of_ok_file_reader_qm,Qsuccess_of_ok_file_reader_qm,success_of_ok_file_reader_qm,
						3);
					  saw_more_than_one_machine_authorization_qm 
						  = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Saw_more_than_one_machine_authorization_qm,Qsaw_more_than_one_machine_authorization_qm,saw_more_than_one_machine_authorization_qm,
						  2);
					    slot_pad_of_ok_file_reader = 
						    allocate_managed_simple_vector(FIX((SI_Long)20L));
					    PUSH_SPECIAL_WITH_SYMBOL(Slot_pad_of_ok_file_reader,Qslot_pad_of_ok_file_reader,slot_pad_of_ok_file_reader,
						    1);
					      if ( 
						      !TRUEP(ok_file_sanity_check(array_constant_15))) 
							  {
						  error_broke_rule_reading_ok_file(2,
							  sanity_check_on_initial_characters_of_file_ok_message(),
							  Nil);
						  clear_slot_pad();
						  goto end_reading;
					      }
					      contour_of_ok_file_tokens = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Contour_of_ok_file_tokens,Qcontour_of_ok_file_tokens,contour_of_ok_file_tokens,
						      0);
						result = read_statement_from_ok_file();
						MVS_2(result,s,v1);
						if (EQ(Kerror,s)) {
						    clear_slot_pad();
						    POP_SPECIAL();
						    goto end_reading;
						}
						if ( !(EQ(Kbegin_entity,s) 
							&& 
							symbol_token_match(array_constant_16,
							v1))) {
						    error_broke_rule_reading_ok_file(2,
							    header_for_file_entry_missing_ok_message(),
							    Nil);
						    clear_slot_pad();
						    POP_SPECIAL();
						    goto end_reading;
						}
						read_g2_ok_file_entity();
						reclaim_contour_of_ok_file_tokens();
					      POP_SPECIAL();
					      if ( 
						      !TRUEP(Success_of_ok_file_reader_qm)) 
							  {
						  if (Saw_more_than_one_machine_authorization_qm) 
							      {
						      error_broke_rule_reading_ok_file(2,
							      no_authorization_found_for_this_machine_multiple_entries_ok_message(),
							      T);
						      clear_slot_pad();
						      goto end_reading;
						  }
						  else {
						      error_broke_rule_reading_ok_file(2,
							      no_authorization_found_for_this_machine_one_entry_ok_message(),
							      T);
						      clear_slot_pad();
						      goto end_reading;
						  }
					      }
					    end_reading:
					      reclaim_managed_simple_vector(Slot_pad_of_ok_file_reader);
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
		SAVE_VALUES(VALUES_1(Error_of_ok_file_reader_qm));
	    }
	    POP_UNWIND_PROTECT(0);
	    if (stream) {
		if ( !EQ(stream,Qunbound_in_protected_let))
		    g2_stream_close(stream);
	    }
	    if (namestring_2) {
		if ( !EQ(namestring_2,Qunbound_in_protected_let)) {
		    if (pathname_used_p)
			reclaim_text_string(namestring_2);
		}
	    }
	    CONTINUE_UNWINDING(0);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Reading_ok_file);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

/* READ-G2-OK-FILE-ENTITY */
Object read_g2_ok_file_entity()
{
    Object saw_at_least_one_machine_authorization_qm;
    Object contour_of_ok_file_tokens, have_seen_subentities_qm, s, v1, v2;
    Declare_special(1);
    Object result;

    x_note_fn_call(107,210);
    saw_at_least_one_machine_authorization_qm = Nil;
    contour_of_ok_file_tokens = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Contour_of_ok_file_tokens,Qcontour_of_ok_file_tokens,contour_of_ok_file_tokens,
	    0);
      have_seen_subentities_qm = Nil;
    next_loop:
      reclaim_contour_of_ok_file_tokens();
      result = read_statement_from_ok_file();
      MVS_3(result,s,v1,v2);
      if (EQ(s,Keof))
	  goto end_1;
      else if (EQ(s,Kbegin_entity)) {
	  if (symbol_token_match(array_constant_17,v1)) {
	      if (saw_at_least_one_machine_authorization_qm)
		  Saw_more_than_one_machine_authorization_qm = T;
	      else
		  saw_at_least_one_machine_authorization_qm = T;
	      read_machine_ok_file_entry();
	  }
	  else if (symbol_token_match(array_constant_18,v1))
	      read_user_ok_file_entry();
	  else {
	      error_broke_rule_reading_ok_file(2,
		      undefined_entry_type_ok_message(),Nil);
	      goto end_1;
	  }
      }
      else if (EQ(s,Kattribute)) {
	  if (have_seen_subentities_qm) {
	      error_broke_rule_reading_ok_file(2,
		      file_attribute_not_initial_ok_message(),Nil);
	      goto end_1;
	  }
	  else if ( !TRUEP(symbol_token_match(array_constant_19,v1))) {
	      error_broke_rule_reading_ok_file(2,
		      undefined_file_attribute_ok_message(),Nil);
	      goto end_1;
	  }
	  else if (File_format_version_of_g2_ok_file_qm) {
	      error_broke_rule_reading_ok_file(2,
		      file_format_attribute_duplicated_ok_message(),Nil);
	      goto end_1;
	  }
	  else if ( !TRUEP(token_kind_is(Kinteger,v2))) {
	      error_broke_rule_reading_ok_file(2,
		      file_format_value_not_an_integer_ok_message(),Nil);
	      goto end_1;
	  }
	  else if (ok_file_is_incompatible_with_image(ISVREF(v2,
		      (SI_Long)4L))) {
	      error_broke_rule_reading_ok_file(2,
		      file_version_higher_than_image_version_ok_message_1(Supported_ok_file_format_version,
		      ISVREF(v2,(SI_Long)4L)),Nil);
	      goto end_1;
	  }
	  else
	      File_format_version_of_g2_ok_file_qm = ISVREF(v2,(SI_Long)4L);
      }
      else if (EQ(s,Kend_entity)) {
	  if ( !TRUEP(symbol_token_match(array_constant_16,v1))) {
	      error_broke_rule_reading_ok_file(2,
		      wrong_label_on_file_level_end_statement_ok_message(),
		      Nil);
	      goto end_1;
	  }
      }
      else {
	  error_broke_rule_reading_ok_file(2,
		  unknown_problem_parsing_file_ok_message(),Nil);
	  goto end_1;
      }
      goto next_loop;
    end_loop:
    end_1:;
      reclaim_contour_of_ok_file_tokens();
    POP_SPECIAL();
    if ( !TRUEP(saw_at_least_one_machine_authorization_qm))
	error_broke_rule_reading_ok_file(2,
		no_machine_authorization_in_file_ok_message(),T);
    return VALUES_1(Nil);
}

static Object string_constant_85;  /* "" */

static Object Qproprietary;        /* proprietary */

/* READ-USER-OK-FILE-ENTRY */
Object read_user_ok_file_entry()
{
    Object contour_of_ok_file_tokens, s, v1, v2, permitted_user_modes, temp;
    Object temp_1, temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(107,211);
    contour_of_ok_file_tokens = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Contour_of_ok_file_tokens,Qcontour_of_ok_file_tokens,contour_of_ok_file_tokens,
	    0);
      clear_slot_pad();
    next_loop:
      result = read_statement_from_ok_file();
      MVS_3(result,s,v1,v2);
      if (EQ(s,Kend_entity)) {
	  if ( !TRUEP(symbol_token_match(array_constant_18,v1))) {
	      error_broke_rule_reading_ok_file(1,
		      wrong_label_on_end_statement_ok_message());
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_read_user_ok_file_entry;
	  }
	  goto end_1;
      }
      else if (EQ(s,Kattribute)) {
	  if ( 
		  !TRUEP(process_attribute_of_entity(Slot_pad_descriptions_of_user,
		  v1,v2))) {
	      error_broke_rule_reading_ok_file(1,string_constant_85);
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_read_user_ok_file_entry;
	  }
      }
      else {
	  error_broke_rule_reading_ok_file(1,
		  unknown_problem_parsing_entry_ok_message());
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_user_ok_file_entry;
      }
      goto next_loop;
    end_loop:
    end_1:
      permitted_user_modes = 
	      coerce_token_to_lisp(ISVREF(Slot_pad_of_ok_file_reader,
	      (SI_Long)3L));
      if ( !TRUEP(permitted_user_modes)) {
	  error_broke_rule_reading_ok_file(1,
		  no_user_modes_specified_ok_message());
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_user_ok_file_entry;
      }
      if (memq_function(Qproprietary,permitted_user_modes)) {
	  error_broke_rule_reading_ok_file(1,
		  proprietary_mode_specified_ok_message());
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_user_ok_file_entry;
      }
      temp = coerce_token_to_lisp(ISVREF(Slot_pad_of_ok_file_reader,
	      (SI_Long)0L));
      temp_1 = copy_text_string(ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
	      (SI_Long)1L),(SI_Long)3L));
      temp_2 = copy_list_using_gensym_conses_1(permitted_user_modes);
      enter_authorized_user(temp,temp_1,temp_2,
	      coerce_token_to_lisp(ISVREF(Slot_pad_of_ok_file_reader,
	      (SI_Long)2L)),T);
      temp = reclaim_gensym_list_1(permitted_user_modes);
      reclaim_contour_of_ok_file_tokens();
      result = VALUES_1(temp);
    POP_SPECIAL();
  end_read_user_ok_file_entry:
    return result;
}

static Object array_constant_20;   /* # */

static Object array_constant_21;   /* # */

/* READ-MACHINE-OK-FILE-ENTRY */
Object read_machine_ok_file_entry()
{
    Object contour_of_ok_file_tokens, s, v1, v2, svref_arg_1, svref_new_value;
    Object id, ab_loop_list_, ab_loop_it_, machine_id_string, codes;
    Object authorized_products, authorized_kb_packages_parse;
    Object expiration_date_parse, expiration_date_qm, authorized_kb_packages;
    Object from_date_qm, temp_1, to_date_qm, element, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;
    char temp;
    Declare_special(1);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(107,212);
    contour_of_ok_file_tokens = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Contour_of_ok_file_tokens,Qcontour_of_ok_file_tokens,contour_of_ok_file_tokens,
	    0);
      clear_slot_pad();
    next_loop:
      result = read_statement_from_ok_file();
      MVS_3(result,s,v1,v2);
      if (EQ(s,Kend_entity)) {
	  if ( !TRUEP(symbol_token_match(array_constant_17,v1))) {
	      error_broke_rule_reading_ok_file(1,
		      wrong_label_on_end_statement_ok_message());
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_read_machine_ok_file_entry;
	  }
	  goto end_1;
      }
      else if (EQ(s,Kattribute))
	  process_attribute_of_entity(Slot_pad_descriptions_of_machine_authorization,
		  v1,v2);
      else {
	  error_broke_rule_reading_ok_file(1,
		  unknown_problem_parsing_entry_ok_message());
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_machine_ok_file_entry;
      }
      goto next_loop;
    end_loop:
    end_1:
      if (EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)1L),
	      Unbound_value_for_ok_reader)) {
	  error_broke_rule_reading_ok_file(1,machine_id_missing_ok_message());
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_machine_ok_file_entry;
      }
      if (EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)4L),
	      Unbound_value_for_ok_reader)) {
	  error_broke_rule_reading_ok_file(1,
		  authorization_missing_ok_message());
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_machine_ok_file_entry;
      }
      if (EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)0L),
	      Unbound_value_for_ok_reader)) {
	  svref_arg_1 = Slot_pad_of_ok_file_reader;
	  svref_new_value = make_list_token(Nil);
	  SVREF(svref_arg_1,FIX((SI_Long)0L)) = svref_new_value;
      }
      if (EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)2L),
	      Unbound_value_for_ok_reader)) {
	  svref_arg_1 = Slot_pad_of_ok_file_reader;
	  svref_new_value = make_list_token(Nil);
	  SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value;
      }
      if (EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)3L),
	      Unbound_value_for_ok_reader)) {
	  svref_arg_1 = Slot_pad_of_ok_file_reader;
	  svref_new_value = make_list_token(Nil);
	  SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value;
      }
      if (EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)5L),
	      Unbound_value_for_ok_reader)) {
	  svref_arg_1 = Slot_pad_of_ok_file_reader;
	  svref_new_value = make_list_token(Nil);
	  SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value;
      }
      if (EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)6L),
	      Unbound_value_for_ok_reader)) {
	  svref_arg_1 = Slot_pad_of_ok_file_reader;
	  svref_new_value = make_list_token(Nil);
	  SVREF(svref_arg_1,FIX((SI_Long)6L)) = svref_new_value;
      }
      if (EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)7L),
	      Unbound_value_for_ok_reader)) {
	  svref_arg_1 = Slot_pad_of_ok_file_reader;
	  svref_new_value = 
		  make_integer_ok_file_token(copy_wide_string(array_constant_20),
		  FIX((SI_Long)1L));
	  SVREF(svref_arg_1,FIX((SI_Long)7L)) = svref_new_value;
      }
      if (EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)8L),
	      Unbound_value_for_ok_reader)) {
	  svref_arg_1 = Slot_pad_of_ok_file_reader;
	  svref_new_value = 
		  make_integer_ok_file_token(copy_wide_string(array_constant_21),
		  FIX((SI_Long)0L));
	  SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
      }
      if (EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)9L),
	      Unbound_value_for_ok_reader)) {
	  svref_arg_1 = Slot_pad_of_ok_file_reader;
	  svref_new_value = 
		  make_integer_ok_file_token(copy_wide_string(array_constant_21),
		  FIX((SI_Long)0L));
	  SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
      }
      if (shunned_machine_id_string_p(ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
	      (SI_Long)1L),(SI_Long)3L))) {
	  error_broke_rule_reading_ok_file(1,shunned_machine_id_ok_message());
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_machine_ok_file_entry;
      }
      id = Nil;
      ab_loop_list_ = Current_machine_ids_of_g2_ok_file_qm;
      ab_loop_it_ = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      id = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      ab_loop_it_ = normalized_string_equal(2,
	      ISVREF(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)1L),
	      (SI_Long)3L),id);
      if (ab_loop_it_) {
	  temp = TRUEP(ab_loop_it_);
	  goto end_2;
      }
      goto next_loop_1;
    end_loop_1:
      temp = TRUEP(Qnil);
    end_2:;
      if (temp);
      else {
	  machine_id_string = ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		  (SI_Long)1L),(SI_Long)3L);
	  temp = IFIX(lengthw(machine_id_string)) > (SI_Long)5L && 
		  UBYTE_16_ISAREF_1(machine_id_string,(SI_Long)4L) == 
		  (SI_Long)58L && 
		  wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id_string,
		  (SI_Long)2L)),list_constant_1) && 
		  wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id_string,
		  (SI_Long)1L)),list_constant_2) && 
		  (UBYTE_16_ISAREF_1(machine_id_string,(SI_Long)3L) == 
		  (SI_Long)101L || UBYTE_16_ISAREF_1(machine_id_string,
		  (SI_Long)3L) == (SI_Long)69L) ? 
		  UBYTE_16_ISAREF_1(machine_id_string,(SI_Long)0L) == 
		  (SI_Long)83L || UBYTE_16_ISAREF_1(machine_id_string,
		  (SI_Long)0L) == (SI_Long)115L : TRUEP(Qnil);
      }
      if (temp) {
	  codes = ISVREF(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)4L),
		  (SI_Long)4L);
	  authorized_products = 
		  coerce_token_to_lisp(ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		  (SI_Long)2L),(SI_Long)4L));
	  authorized_kb_packages_parse = 
		  coerce_token_to_lisp(ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		  (SI_Long)6L),(SI_Long)4L));
	  expiration_date_parse = 
		  coerce_token_to_lisp(ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		  (SI_Long)3L),(SI_Long)4L));
	  expiration_date_qm = Nil;
	  authorized_kb_packages = Nil;
	  if ( !EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)10L),
		  Unbound_value_for_ok_reader))
	      Name_of_customer_in_ok_file = 
		      process_slot_text_for_customer(ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		      (SI_Long)10L),(SI_Long)3L));
	  if ( !EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)11L),
		  Unbound_value_for_ok_reader))
	      Serial_number_in_ok_file = 
		      copy_text_string(ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		      (SI_Long)11L),(SI_Long)3L));
	  if ( !EQ(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)12L),
		  Unbound_value_for_ok_reader))
	      Installation_code_in_ok_file = 
		      copy_text_string(ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		      (SI_Long)12L),(SI_Long)3L));
	  if ( !((SI_Long)5L == IFIX(length(codes)))) {
	      error_broke_rule_reading_ok_file(1,
		      wrong_number_of_authorization_codes_ok_message());
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_read_machine_ok_file_entry;
	  }
	  if (expiration_date_parse) {
	      if (Expiration_date_for_display_in_title)
		  reclaim_gensym_tree_1(Expiration_date_for_display_in_title);
	      Expiration_date_for_display_in_title = 
		      copy_tree_using_gensym_conses_1(expiration_date_parse);
	      from_date_qm = 
		      convert_input_to_universal_date(CDR(expiration_date_parse));
	      temp_1 = CDR(expiration_date_parse);
	      to_date_qm = convert_input_to_universal_date(CDDDDR(temp_1));
	      if ( !(from_date_qm && to_date_qm && FIXNUM_LT(from_date_qm,
		      to_date_qm))) {
		  error_broke_rule_reading_ok_file(1,
			  from_date_earlier_than_to_date_ok_message());
		  result = VALUES_1(Nil);
		  POP_SPECIAL();
		  goto end_read_machine_ok_file_entry;
	      }
	      expiration_date_qm = FIX((SI_Long)8388608L + 
		      IFIX(FIXNUM_MINUS(from_date_qm,
		      Reference_date_for_interval_encoding)) + 
		      (IFIX(FIXNUM_MINUS(to_date_qm,from_date_qm)) << 
		      (SI_Long)12L));
	  }
	  element = Nil;
	  ab_loop_list_ = authorized_kb_packages_parse;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  element = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ((SI_Long)4L < IFIX(length(element))) {
	      from_date_qm = convert_input_to_universal_date(CDDR(element));
	      temp_1 = CDDR(element);
	      to_date_qm = convert_input_to_universal_date(CDDDDR(temp_1));
	      if ( !(from_date_qm && to_date_qm && FIXNUM_LT(from_date_qm,
		      to_date_qm))) {
		  error_broke_rule_reading_ok_file(1,
			  from_date_earlier_than_to_date_ok_message());
		  result = VALUES_1(Nil);
		  POP_SPECIAL();
		  goto end_read_machine_ok_file_entry;
	      }
	      temp_1 = FIRST(element);
	      temp_1 = ok_file_token_cons_1(temp_1,
		      nconc2(copy_list_using_ok_file_token_conses_1(nthcdr(FIX((SI_Long)9L),
		      element)),ok_file_token_list_2(from_date_qm,
		      to_date_qm)));
	  }
	  else
	      temp_1 = copy_list_using_ok_file_token_conses_1(element);
	  ab_loopvar__2 = ok_file_token_cons_1(temp_1,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop_2;
	end_loop_2:
	  authorized_kb_packages = ab_loopvar_;
	  goto end_3;
	  authorized_kb_packages = Qnil;
	end_3:;
	  if ( 
		  !TRUEP(new_analyze_authorized_packages(authorized_kb_packages,
		  ISVREF(ISVREF(Slot_pad_of_ok_file_reader,(SI_Long)1L),
		  (SI_Long)3L)))) {
	      error_broke_rule_reading_ok_file(1,string_constant_85);
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_read_machine_ok_file_entry;
	  }
	  if (PUSH_AREA(Dynamic_area,0)) {
	      new_reformat_line_from_left(ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		      (SI_Long)1L),(SI_Long)3L),ISVREF(FIRST(codes),
		      (SI_Long)4L),ISVREF(SECOND(codes),(SI_Long)4L),
		      ISVREF(THIRD(codes),(SI_Long)4L),
		      ISVREF(FOURTH(codes),(SI_Long)4L),
		      ISVREF(FIFTH(codes),(SI_Long)4L),authorized_products,
		      authorized_kb_packages,expiration_date_qm,
		      ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		      (SI_Long)7L),(SI_Long)4L),
		      ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		      (SI_Long)8L),(SI_Long)4L),
		      ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		      (SI_Long)9L),(SI_Long)4L),
		      ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
		      (SI_Long)5L),(SI_Long)4L));
	      reclaim_ok_file_token_tree_1(authorized_products);
	      reclaim_ok_file_token_tree_1(authorized_kb_packages_parse);
	      reclaim_ok_file_token_tree_1(authorized_kb_packages);
	      temp_1 = reclaim_ok_file_token_tree_1(expiration_date_parse);
	  }
	  POP_AREA(0);
      }
      else
	  temp_1 = Nil;
      reclaim_contour_of_ok_file_tokens();
      result = VALUES_1(temp_1);
    POP_SPECIAL();
  end_read_machine_ok_file_entry:
    return result;
}

static Object array_constant_22;   /* # */

static Object list_constant_7;     /* # */

/* PROCESS-SLOT-TEXT-FOR-CUSTOMER */
Object process_slot_text_for_customer(slot_text)
    Object slot_text;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object just_wrote_space_p, char_1, temp_string, trimmed_temp_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(107,213);
    if (string_eq_w(slot_text,array_constant_22))
	return VALUES_1(Nil);
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
		  just_wrote_space_p = Nil;
		  i = (SI_Long)0L;
		  ab_loop_bind_ = IFIX(lengthw(slot_text));
		  char_1 = Nil;
		next_loop:
		  if (i >= ab_loop_bind_)
		      goto end_loop;
		  char_1 = FIX(UBYTE_16_ISAREF_1(slot_text,i));
		  char_1 = EQ(char_1,FIX((SI_Long)45L)) || EQ(char_1,
			  FIX((SI_Long)95L)) ? FIX((SI_Long)32L) : char_1;
		  if ( !(just_wrote_space_p && IFIX(char_1) == (SI_Long)32L))
		      twrite_character(char_1);
		  just_wrote_space_p = IFIX(char_1) == (SI_Long)32L ? T : Nil;
		  i = i + (SI_Long)1L;
		  goto next_loop;
		end_loop:;
		  temp_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	trimmed_temp_string = text_string_trim(list_constant_7,temp_string);
	reclaim_text_string(temp_string);
	if (string_eq_w(trimmed_temp_string,array_constant_11)) {
	    reclaim_text_string(trimmed_temp_string);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(trimmed_temp_string);
    }
}

/* PROCESS-ATTRIBUTE-OF-ENTITY */
Object process_attribute_of_entity(slot_descriptions,attribute_name,
	    attribute_value)
    Object slot_descriptions, attribute_name, attribute_value;
{
    Object slot_spelling, slot_symbol, slot_type, ab_loop_list_;
    Object ab_loop_iter_flag_, ab_loop_desetq_, temp, svref_arg_1;
    SI_Long i;

    x_note_fn_call(107,214);
    slot_spelling = Nil;
    slot_symbol = Nil;
    slot_type = Nil;
    ab_loop_list_ = slot_descriptions;
    i = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    slot_spelling = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    slot_symbol = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    slot_type = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    if (symbol_token_match(slot_spelling,attribute_name)) {
	if ( !TRUEP(check_ok_token_against_type(attribute_value,slot_type))) {
	    warning_while_reading_ok_file(1,
		    syntax_error_in_attribute_value_ok_message_1(attribute_name,
		    attribute_value,slot_type));
	    return VALUES_1(Nil);
	}
	if ( !EQ(Unbound_value_for_ok_reader,
		ISVREF(Slot_pad_of_ok_file_reader,i))) {
	    warning_while_reading_ok_file(1,
		    attribute_appears_more_than_once_ok_message_1(attribute_name));
	    return VALUES_1(Nil);
	}
	svref_arg_1 = Slot_pad_of_ok_file_reader;
	ISVREF(svref_arg_1,i) = attribute_value;
	return VALUES_1(T);
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    warning_while_reading_ok_file(1,
	    unrecognized_attribute_ok_message_1(attribute_name));
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

static Object Qboolean;            /* boolean */

static Object array_constant_23;   /* # */

static Object Qab_or;              /* or */

static Object Qlist_of;            /* list-of */

static Object Qlist_structure;     /* list-structure */

/* CHECK-OK-TOKEN-AGAINST-TYPE */
Object check_ok_token_against_type(token,type)
    Object token, type;
{
    Object temp, cantidate_type, ab_loop_list_, element, element_type, value;
    Object element_types, ab_loop_list__1;

    x_note_fn_call(107,215);
    if (SYMBOLP(type)) {
	if (EQ(type,Qinteger))
	    return token_kind_is(Kinteger,token);
	else if (EQ(type,Qsymbol))
	    return token_kind_is(Ksymbol,token);
	else if (EQ(type,Qstring))
	    return token_kind_is(Kstring,token);
	else if (EQ(type,Qnull)) {
	    if (EQ(Nil,ISVREF(token,(SI_Long)4L)))
		return token_kind_is(Klist,token);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(type,Qboolean)) {
	    if (token_kind_is(Ksymbol,token)) {
		temp = symbol_token_match(array_constant_23,token);
		if (temp)
		    return VALUES_1(temp);
		else
		    return symbol_token_match(array_constant_12,token);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else if (LISTP(type)) {
	temp = FIRST(type);
	if (EQ(temp,Qab_or)) {
	    cantidate_type = Nil;
	    ab_loop_list_ = REST(type);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    cantidate_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (check_ok_token_against_type(token,cantidate_type))
		return VALUES_1(T);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Nil);
	    return VALUES_1(Qnil);
	}
	else if (EQ(temp,Qmember)) {
	    element = Nil;
	    ab_loop_list_ = REST(type);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (symbol_token_match(element,token))
		return VALUES_1(T);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Nil);
	    return VALUES_1(Qnil);
	}
	else if (EQ(temp,Qlist_of)) {
	    if (token_kind_is(Klist,token)) {
		element_type = SECOND(type);
		element = Nil;
		ab_loop_list_ = ISVREF(token,(SI_Long)4L);
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(check_ok_token_against_type(element,element_type)))
		    return VALUES_1(Nil);
		goto next_loop_2;
	      end_loop_2:
		return VALUES_1(T);
		return VALUES_1(Qnil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(temp,Qlist_structure)) {
	    value = ISVREF(token,(SI_Long)4L);
	    element_types = REST(type);
	    if (token_kind_is(Klist,token) && FIXNUM_EQ(length(value),
		    length(element_types))) {
		element = Nil;
		ab_loop_list_ = ISVREF(token,(SI_Long)4L);
		element_type = Nil;
		ab_loop_list__1 = element_types;
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_3;
		element_type = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if ( !TRUEP(check_ok_token_against_type(element,element_type)))
		    return VALUES_1(Nil);
		goto next_loop_3;
	      end_loop_3:
		return VALUES_1(T);
		return VALUES_1(Qnil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Authorizing_ok_pathname, Qauthorizing_ok_pathname);

/* SET-AUTHORIZING-OK-PATHNAME */
Object set_authorizing_ok_pathname(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(107,216);
    if (ISVREF(pathname_1,(SI_Long)6L))
	SVREF(pathname_1,FIX((SI_Long)6L)) = Knewest;
    Authorizing_ok_pathname = pathname_1;
    return VALUES_1(Authorizing_ok_pathname);
}

/* G2-OK-FILE-PROBE-FOR-WRITE */
Object g2_ok_file_probe_for_write()
{
    Object pathname_qm;

    x_note_fn_call(107,217);
    pathname_qm = Authorizing_ok_pathname;
    if (pathname_qm)
	return gensym_probe_file_for_write(pathname_qm);
    else
	return VALUES_1(Nil);
}

/* G2-OK-FILE-WRITEABLE-P */
Object g2_ok_file_writeable_p()
{
    volatile Object pathname_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(107,218);
    SAVE_STACK();
    pathname_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	pathname_qm = Authorizing_ok_pathname ? 
		gensym_probe_file_for_write(Authorizing_ok_pathname) : Nil;
	if (pathname_qm)
	    SAVE_VALUES(VALUES_1(T));
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(0);
    if (pathname_qm) {
	if ( !EQ(pathname_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_qm);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-OK-FILE-PROBE */
Object g2_ok_file_probe()
{
    Object pathname_qm;

    x_note_fn_call(107,219);
    pathname_qm = Authorizing_ok_pathname;
    if (pathname_qm)
	return gensym_probe_file(pathname_qm);
    else
	return VALUES_1(Nil);
}

/* G2-OK-FILE-READABLE-P */
Object g2_ok_file_readable_p()
{
    volatile Object pathname_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(107,220);
    SAVE_STACK();
    pathname_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	pathname_qm = Authorizing_ok_pathname ? 
		gensym_probe_file(Authorizing_ok_pathname) : Nil;
	if (pathname_qm)
	    SAVE_VALUES(VALUES_1(T));
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(0);
    if (pathname_qm) {
	if ( !EQ(pathname_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_qm);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(G2passwdexe, Qg2passwdexe);

/* INITIALIZE-G2PASSWDEXE */
Object initialize_g2passwdexe()
{
    x_note_fn_call(107,221);
    return getf(Command_line_arguments,Qg2passwdexe,_);
}

static Object Qunix;               /* unix */

static Object array_constant_24;   /* # */

/* G2PASSWD-PROBE-FILE */
Object g2passwd_probe_file()
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object g2passwd_pathname;
    volatile Object g2passwd_exe_pathname;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(107,222);
    SAVE_STACK();
    if (G2passwdexe) {
	current_local_filename_parser = Local_filename_parser;
	current_local_namestring_generator = Local_namestring_generator;
	convert_file_strings_to_uppercase_p = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
		Qconvert_file_strings_to_uppercase_p);
	PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		0);
	  g2passwd_pathname = Qunbound_in_protected_let;
	  if (PUSH_UNWIND_PROTECT(1)) {
	      g2passwd_pathname = convert_to_gensym_pathname(G2passwdexe,
		      current_local_filename_parser,
		      current_local_namestring_generator);
	      if (EQ(ISVREF(g2passwd_pathname,(SI_Long)8L),Qunix))
		  SAVE_VALUES(gensym_probe_file_for_truth_value(g2passwd_pathname));
	      else {
		  g2passwd_exe_pathname = Qunbound_in_protected_let;
		  if (PUSH_UNWIND_PROTECT(0)) {
		      g2passwd_exe_pathname = 
			      gensym_merge_pathnames_function(g2passwd_pathname,
			      array_constant_24,Nil);
		      SAVE_VALUES(gensym_probe_file_for_truth_value(g2passwd_exe_pathname));
		  }
		  POP_UNWIND_PROTECT(0);
		  if (g2passwd_exe_pathname) {
		      if ( !EQ(g2passwd_exe_pathname,
			      Qunbound_in_protected_let))
			  reclaim_gensym_pathname(g2passwd_exe_pathname);
		  }
		  CONTINUE_UNWINDING(0);
	      }
	  }
	  POP_UNWIND_PROTECT(1);
	  if (g2passwd_pathname) {
	      if ( !EQ(g2passwd_pathname,Qunbound_in_protected_let)) {
		  if (g2passwd_pathname)
		      reclaim_gensym_pathname(g2passwd_pathname);
	      }
	  }
	  CONTINUE_UNWINDING(1);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(G2passwdexe_is_executable_p, Qg2passwdexe_is_executable_p);

Object G2passwdexe_areyouthere_arg = UNBOUND;

static Object string_constant_86;  /* "~a ~a" */

/* INITIALIZE-G2PASSWDEXE-IS-EXECUTABLE-P */
Object initialize_g2passwdexe_is_executable_p()
{
    volatile Object command_line;
    Object result_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(107,223);
    SAVE_STACK();
    command_line = Qunbound_in_protected_let;
    result_1 = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	command_line = tformat_text_string(3,string_constant_86,
		G2passwdexe,G2passwdexe_areyouthere_arg);
	result_1 = c_substatus_run_command_line(command_line);
	SAVE_VALUES(VALUES_1(FIXNUM_EQ(result_1,
		G2passwdexe_areyouthere_good_result) ? T : Nil));
    }
    POP_UNWIND_PROTECT(0);
    if (command_line) {
	if ( !EQ(command_line,Qunbound_in_protected_let))
	    reclaim_text_string(command_line);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qunknown;            /* unknown */

static Object string_constant_87;  /* "Warning: Cannot execute ~s from G2; password changing will be disabled for the entire G2 session!" */

/* CHECK-PASSWORD-SETUP-AND-NOTIFY-USER-IF-NECESSARY */
Object check_password_setup_and_notify_user_if_necessary()
{
    volatile Object message_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object write_console_p;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(107,224);
    SAVE_STACK();
    if (EQ(G2passwdexe_is_executable_p,Qunknown))
	G2passwdexe_is_executable_p = initialize_g2passwdexe_is_executable_p();
    if ( !TRUEP(G2passwdexe_is_executable_p)) {
	message_1 = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      twrite_standard_secure_g2_notification_header();
		      tformat(2,string_constant_87,G2passwdexe);
		      message_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    write_console_p = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_console_p,Qwrite_console_p,write_console_p,
		    0);
	      SAVE_VALUES(notify_user_at_console(2,string_constant_81,
		      message_1));
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(0);
	if (message_1) {
	    if ( !EQ(message_1,Qunbound_in_protected_let))
		reclaim_text_string(message_1);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* READ-OK-FILE-JUST-FOR-UPDATING-USER-DATA */
Object read_ok_file_just_for_updating_user_data(namestring_1)
    Object namestring_1;
{
    volatile Object error_in_ok_file_qm;
    Object error_of_ok_file_reader_qm, line_number_of_ok_file_reader;
    volatile Object pathname_used_p;
    volatile Object namestring_2;
    volatile Object stream;
    Object g2_stream_of_ok_file_reader, buffer_of_ok_file_reader;
    Object buffer_length_of_ok_file_reader, unread_char_of_ok_file_reader_qm;
    Object characters_in_buffer_of_ok_file_reader_qm;
    Object buffer_index_of_ok_file_reader;
    Object file_format_version_of_g2_ok_file_qm;
    Object authorized_user_records_of_g2_ok_file;
    Object useful_machine_authorization_info, success_of_ok_file_reader_qm;
    Object saw_more_than_one_machine_authorization_qm;
    Object slot_pad_of_ok_file_reader, contour_of_ok_file_tokens, s, v1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(16);
    Object result;

    x_note_fn_call(107,225);
    SAVE_STACK();
    error_in_ok_file_qm = Nil;
    LOCK(Reading_ok_file);
    if (PUSH_UNWIND_PROTECT(1)) {
	error_of_ok_file_reader_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Error_of_ok_file_reader_qm,Qerror_of_ok_file_reader_qm,error_of_ok_file_reader_qm,
		15);
	  line_number_of_ok_file_reader = FIX((SI_Long)-1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Line_number_of_ok_file_reader,Qline_number_of_ok_file_reader,line_number_of_ok_file_reader,
		  14);
	    pathname_used_p = Qunbound_in_protected_let;
	    namestring_2 = Qunbound_in_protected_let;
	    stream = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(0)) {
		pathname_used_p = SIMPLE_VECTOR_P(namestring_1) ? 
			(EQ(ISVREF(namestring_1,(SI_Long)0L),
			Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			? T : Nil) : Qnil;
		namestring_2 = SIMPLE_VECTOR_P(namestring_1) && 
			EQ(ISVREF(namestring_1,(SI_Long)0L),
			Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			? gensym_namestring(1,namestring_1) : namestring_1;
		stream = g2_stream_open_for_input(namestring_2);
		if ( !TRUEP(stream))
		    error_broke_rule_reading_ok_file(1,
			    could_not_open_stream_ok_message());
		else if ( !TRUEP(ISVREF(namestring_1,(SI_Long)4L)))
		    error_broke_rule_reading_ok_file(1,
			    no_filename_provided_ok_message());
		else {
		    g2_stream_of_ok_file_reader = stream;
		    PUSH_SPECIAL_WITH_SYMBOL(G2_stream_of_ok_file_reader,Qg2_stream_of_ok_file_reader,g2_stream_of_ok_file_reader,
			    13);
		      buffer_of_ok_file_reader = Read_ok_file_buffer_1;
		      PUSH_SPECIAL_WITH_SYMBOL(Buffer_of_ok_file_reader,Qbuffer_of_ok_file_reader,buffer_of_ok_file_reader,
			      12);
			buffer_length_of_ok_file_reader = 
				length(Buffer_of_ok_file_reader);
			PUSH_SPECIAL_WITH_SYMBOL(Buffer_length_of_ok_file_reader,Qbuffer_length_of_ok_file_reader,buffer_length_of_ok_file_reader,
				11);
			  unread_char_of_ok_file_reader_qm = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Unread_char_of_ok_file_reader_qm,Qunread_char_of_ok_file_reader_qm,unread_char_of_ok_file_reader_qm,
				  10);
			    characters_in_buffer_of_ok_file_reader_qm = 
				    g2_stream_read_into_buffer(Buffer_of_ok_file_reader,
				    Buffer_length_of_ok_file_reader,
				    G2_stream_of_ok_file_reader);
			    PUSH_SPECIAL_WITH_SYMBOL(Characters_in_buffer_of_ok_file_reader_qm,Qcharacters_in_buffer_of_ok_file_reader_qm,characters_in_buffer_of_ok_file_reader_qm,
				    9);
			      buffer_index_of_ok_file_reader = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL_WITH_SYMBOL(Buffer_index_of_ok_file_reader,Qbuffer_index_of_ok_file_reader,buffer_index_of_ok_file_reader,
				      8);
				line_number_of_ok_file_reader = 
					FIX((SI_Long)1L);
				PUSH_SPECIAL_WITH_SYMBOL(Line_number_of_ok_file_reader,Qline_number_of_ok_file_reader,line_number_of_ok_file_reader,
					7);
				  file_format_version_of_g2_ok_file_qm = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(File_format_version_of_g2_ok_file_qm,Qfile_format_version_of_g2_ok_file_qm,file_format_version_of_g2_ok_file_qm,
					  6);
				    authorized_user_records_of_g2_ok_file 
					    = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Authorized_user_records_of_g2_ok_file,Qauthorized_user_records_of_g2_ok_file,authorized_user_records_of_g2_ok_file,
					    5);
				      useful_machine_authorization_info = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Useful_machine_authorization_info,Quseful_machine_authorization_info,useful_machine_authorization_info,
					      4);
					success_of_ok_file_reader_qm = Nil;
					PUSH_SPECIAL_WITH_SYMBOL(Success_of_ok_file_reader_qm,Qsuccess_of_ok_file_reader_qm,success_of_ok_file_reader_qm,
						3);
					  saw_more_than_one_machine_authorization_qm 
						  = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Saw_more_than_one_machine_authorization_qm,Qsaw_more_than_one_machine_authorization_qm,saw_more_than_one_machine_authorization_qm,
						  2);
					    slot_pad_of_ok_file_reader = 
						    allocate_managed_simple_vector(FIX((SI_Long)20L));
					    PUSH_SPECIAL_WITH_SYMBOL(Slot_pad_of_ok_file_reader,Qslot_pad_of_ok_file_reader,slot_pad_of_ok_file_reader,
						    1);
					      if ( 
						      !TRUEP(ok_file_sanity_check(array_constant_15))) 
							  {
						  error_broke_rule_reading_ok_file(2,
							  sanity_check_on_initial_characters_of_file_ok_message(),
							  Nil);
						  clear_slot_pad();
						  goto end_reading;
					      }
					      contour_of_ok_file_tokens = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Contour_of_ok_file_tokens,Qcontour_of_ok_file_tokens,contour_of_ok_file_tokens,
						      0);
						result = read_statement_from_ok_file();
						MVS_2(result,s,v1);
						if ( !(EQ(Kbegin_entity,s) 
							&& 
							symbol_token_match(array_constant_16,
							v1))) {
						    error_broke_rule_reading_ok_file(2,
							    header_for_file_entry_missing_ok_message(),
							    Nil);
						    clear_slot_pad();
						    POP_SPECIAL();
						    goto end_reading;
						}
						read_g2_ok_file_entity_just_for_users();
						reclaim_contour_of_ok_file_tokens();
					      POP_SPECIAL();
					      error_in_ok_file_qm = 
						      Error_of_ok_file_reader_qm;
					      if ( !TRUEP(error_in_ok_file_qm))
						  update_ok_user_data();
					    end_reading:
					      reclaim_managed_simple_vector(Slot_pad_of_ok_file_reader);
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
	    }
	    POP_UNWIND_PROTECT(0);
	    if (stream) {
		if ( !EQ(stream,Qunbound_in_protected_let))
		    g2_stream_close(stream);
	    }
	    if (namestring_2) {
		if ( !EQ(namestring_2,Qunbound_in_protected_let)) {
		    if (pathname_used_p)
			reclaim_text_string(namestring_2);
		}
	    }
	    CONTINUE_UNWINDING(0);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Reading_ok_file);
    CONTINUE_UNWINDING(1);
    RESTORE_STACK();
    return VALUES_1(error_in_ok_file_qm);
}

/* READ-G2-OK-FILE-ENTITY-JUST-FOR-USERS */
Object read_g2_ok_file_entity_just_for_users()
{
    Object contour_of_ok_file_tokens, s, v1, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(107,226);
    contour_of_ok_file_tokens = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Contour_of_ok_file_tokens,Qcontour_of_ok_file_tokens,contour_of_ok_file_tokens,
	    0);
    next_loop:
      reclaim_contour_of_ok_file_tokens();
      result = read_statement_from_ok_file();
      MVS_2(result,s,v1);
      if (EQ(s,Keof)) {
	  temp = Nil;
	  goto end_1;
      }
      else if (EQ(s,Kbegin_entity)) {
	  if (symbol_token_match(array_constant_17,v1))
	      skip_ok_statements_until_end_of_entry(array_constant_17);
	  else if (symbol_token_match(array_constant_18,v1))
	      read_user_ok_file_entry_for_updates();
	  else {
	      error_broke_rule_reading_ok_file(2,
		      undefined_entry_type_ok_message(),Nil);
	      clear_slot_pad();
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_read_g2_ok_file_entity_just_for_users;
	  }
      }
      else if (EQ(s,Kend_entity)) {
	  if ( !TRUEP(symbol_token_match(array_constant_16,v1))) {
	      error_broke_rule_reading_ok_file(2,
		      wrong_label_on_file_level_end_statement_ok_message(),
		      Nil);
	      clear_slot_pad();
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_read_g2_ok_file_entity_just_for_users;
	  }
      }
      else if (EQ(s,Kattribute));
      else {
	  error_broke_rule_reading_ok_file(2,
		  unknown_problem_parsing_file_ok_message(),Nil);
	  clear_slot_pad();
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_g2_ok_file_entity_just_for_users;
      }
      goto next_loop;
    end_loop:
      temp = Qnil;
    end_1:
      reclaim_contour_of_ok_file_tokens();
      result = VALUES_1(temp);
    POP_SPECIAL();
  end_read_g2_ok_file_entity_just_for_users:
    return result;
}

/* SKIP-OK-STATEMENTS-UNTIL-END-OF-ENTRY */
Object skip_ok_statements_until_end_of_entry(string_for_entry_type)
    Object string_for_entry_type;
{
    Object contour_of_ok_file_tokens, s, v1, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(107,227);
    contour_of_ok_file_tokens = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Contour_of_ok_file_tokens,Qcontour_of_ok_file_tokens,contour_of_ok_file_tokens,
	    0);
    next_loop:
      reclaim_contour_of_ok_file_tokens();
      result = read_statement_from_ok_file();
      MVS_2(result,s,v1);
      if (EQ(s,Keof)) {
	  error_broke_rule_reading_ok_file(2,
		  reached_eof_while_inside_an_entry_ok_message(),Nil);
	  clear_slot_pad();
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_skip_ok_statements_until_end_of_entry;
      }
      else if (EQ(s,Kbegin_entity)) {
	  error_broke_rule_reading_ok_file(2,
		  entry_started_while_still_inside_entry_ok_message(),Nil);
	  clear_slot_pad();
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_skip_ok_statements_until_end_of_entry;
      }
      else if (EQ(s,Kend_entity)) {
	  if (symbol_token_match(string_for_entry_type,v1)) {
	      temp = Nil;
	      goto end_1;
	  }
	  else {
	      error_broke_rule_reading_ok_file(2,
		      wrong_label_on_file_level_end_statement_ok_message(),
		      Nil);
	      clear_slot_pad();
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_skip_ok_statements_until_end_of_entry;
	  }
      }
      else if (EQ(s,Kattribute));
      else if (EQ(s,Killegal)) {
	  error_broke_rule_reading_ok_file(2,
		  syntax_error_in_attribute_value_ok_message(),Nil);
	  clear_slot_pad();
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_skip_ok_statements_until_end_of_entry;
      }
      else {
	  error_broke_rule_reading_ok_file(2,
		  unknown_problem_parsing_file_ok_message(),Nil);
	  clear_slot_pad();
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_skip_ok_statements_until_end_of_entry;
      }
      goto next_loop;
    end_loop:
      temp = Qnil;
    end_1:
      reclaim_contour_of_ok_file_tokens();
      result = VALUES_1(temp);
    POP_SPECIAL();
  end_skip_ok_statements_until_end_of_entry:
    return result;
}

/* READ-USER-OK-FILE-ENTRY-FOR-UPDATES */
Object read_user_ok_file_entry_for_updates()
{
    Object contour_of_ok_file_tokens, s, v1, v2, permitted_user_modes, temp;
    Object temp_1, temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(107,228);
    contour_of_ok_file_tokens = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Contour_of_ok_file_tokens,Qcontour_of_ok_file_tokens,contour_of_ok_file_tokens,
	    0);
      clear_slot_pad();
    next_loop:
      result = read_statement_from_ok_file();
      MVS_3(result,s,v1,v2);
      if (EQ(s,Kend_entity)) {
	  if ( !TRUEP(symbol_token_match(array_constant_18,v1))) {
	      error_broke_rule_reading_ok_file(2,
		      wrong_label_on_end_statement_ok_message(),Nil);
	      clear_slot_pad();
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_read_user_ok_file_entry_for_updates;
	  }
	  goto end_1;
      }
      else if (EQ(s,Kattribute)) {
	  if ( 
		  !TRUEP(process_attribute_of_entity(Slot_pad_descriptions_of_user,
		  v1,v2))) {
	      error_broke_rule_reading_ok_file(2,string_constant_85,Nil);
	      clear_slot_pad();
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_read_user_ok_file_entry_for_updates;
	  }
      }
      else {
	  error_broke_rule_reading_ok_file(2,
		  unknown_problem_parsing_entry_ok_message(),Nil);
	  clear_slot_pad();
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_user_ok_file_entry_for_updates;
      }
      goto next_loop;
    end_loop:
    end_1:
      permitted_user_modes = 
	      coerce_token_to_lisp(ISVREF(Slot_pad_of_ok_file_reader,
	      (SI_Long)3L));
      if ( !TRUEP(permitted_user_modes)) {
	  error_broke_rule_reading_ok_file(2,
		  no_user_modes_specified_ok_message(),Nil);
	  clear_slot_pad();
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_user_ok_file_entry_for_updates;
      }
      if (memq_function(Qproprietary,permitted_user_modes)) {
	  error_broke_rule_reading_ok_file(2,
		  proprietary_mode_specified_ok_message(),Nil);
	  clear_slot_pad();
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_user_ok_file_entry_for_updates;
      }
      temp = coerce_token_to_lisp(ISVREF(Slot_pad_of_ok_file_reader,
	      (SI_Long)0L));
      temp_1 = copy_text_string(ISVREF(ISVREF(Slot_pad_of_ok_file_reader,
	      (SI_Long)1L),(SI_Long)3L));
      temp_2 = copy_list_using_gensym_conses_1(permitted_user_modes);
      enter_authorized_user(temp,temp_1,temp_2,
	      coerce_token_to_lisp(ISVREF(Slot_pad_of_ok_file_reader,
	      (SI_Long)2L)),Nil);
      temp = reclaim_gensym_list_1(permitted_user_modes);
      reclaim_contour_of_ok_file_tokens();
      result = VALUES_1(temp);
    POP_SPECIAL();
  end_read_user_ok_file_entry_for_updates:
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Locked_to_kb_qm, Qlocked_to_kb_qm);

static Object Qg1;                 /* g1 */

static Object Qent;                /* ent */

static Object array_constant_25;   /* # */

static Object array_constant_26;   /* # */

/* NEW-REFORMAT-LINE-FROM-LEFT */
Object new_reformat_line_from_left(machine_id,code_1,code_2,code_3,code_4,
	    code_5,authorized_products,authorized_kb_packages,
	    expiration_date_qm,number_of_processes_authorized,
	    maximum_number_of_concurrent_floating_telewindows_allowed,
	    maximum_number_of_concurrent_floating_tw2_allowed,
	    make_g2_secure_qm)
    Object machine_id, code_1, code_2, code_3, code_4, code_5;
    Object authorized_products, authorized_kb_packages, expiration_date_qm;
    Object number_of_processes_authorized;
    Object maximum_number_of_concurrent_floating_telewindows_allowed;
    Object maximum_number_of_concurrent_floating_tw2_allowed;
    Object make_g2_secure_qm;
{
    Object modulus, machine_ids, id, ab_loop_list_, ab_loop_it_, temp_1;
    Object structure_being_reclaimed, temp_2, temp_3;
    Object def_structure_schedule_task_variable, svref_new_value, new_task;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object keystring, modularized_key, authorized_products_code, code_1x;
    Object code_2x, code_3x, code_4x, temp_4, checksum, date, start_date_qm;
    Object end_date_1, day, month, year, notification_text_string, system_1;
    Object option, gensymed_symbol_10, cons_1, visible_product, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, code;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    SI_Long gensymed_symbol_7, gensymed_symbol_8, gensymed_symbol_9;
    SI_Long start_date, end_date;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(107,229);
    modulus = New_modulus;
    if (machine_id &&  !TRUEP(shunned_machine_id_string_p(machine_id)) && 
	    code_1 && code_2 && code_3 && code_4 && code_5) {
	temp = IFIX(lengthw(machine_id)) > (SI_Long)5L && 
		UBYTE_16_ISAREF_1(machine_id,(SI_Long)4L) == (SI_Long)58L 
		&& wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id,
		(SI_Long)2L)),list_constant_1) && 
		wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id,
		(SI_Long)1L)),list_constant_2) && 
		(UBYTE_16_ISAREF_1(machine_id,(SI_Long)3L) == 
		(SI_Long)101L || UBYTE_16_ISAREF_1(machine_id,(SI_Long)3L) 
		== (SI_Long)69L) ? UBYTE_16_ISAREF_1(machine_id,
		(SI_Long)0L) == (SI_Long)83L || 
		UBYTE_16_ISAREF_1(machine_id,(SI_Long)0L) == (SI_Long)115L 
		: TRUEP(Qnil);
	if (temp);
	else {
	    machine_ids = get_local_machine_ids_as_gensym_list();
	    id = Nil;
	    ab_loop_list_ = machine_ids;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    id = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = normalized_string_equal(2,id,machine_id);
	    if (ab_loop_it_) {
		temp_1 = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp_1 = Qnil;
	  end_1:;
	    reclaim_gensym_tree_with_text_strings(machine_ids);
	    temp = TRUEP(temp_1);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Locked_to_kb_qm)
	    authorized_products = CONS(Qg1,authorized_products);
	if ((SI_Long)18L <= IFIX(THIRD(Keytab_interface_inset))) {
	    if (Nil) {
		if (EQ(Nil,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(Nil,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(Nil);
		inline_note_reclaim_cons(Nil,Nil);
		structure_being_reclaimed = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(Nil,(SI_Long)9L));
		  SVREF(Nil,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_2 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(Nil,FIX((SI_Long)0L)) = temp_2;
		temp_2 = Chain_of_available_schedule_tasks_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = Nil;
	    }
	    def_structure_schedule_task_variable = 
		    ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    if (def_structure_schedule_task_variable) {
		temp_2 = Chain_of_available_schedule_tasks_vector;
		temp_3 = Current_thread_index;
		svref_new_value = 
			ISVREF(def_structure_schedule_task_variable,
			(SI_Long)0L);
		SVREF(temp_2,temp_3) = svref_new_value;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)0L)) = 
			Qg2_defstruct_structure_name_schedule_task_g2_struct;
	    }
	    else
		def_structure_schedule_task_variable = 
			make_permanent_schedule_task_structure_internal();
	    inline_note_allocate_cons(def_structure_schedule_task_variable,
		    Nil);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = T;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    new_task = def_structure_schedule_task_variable;
	    SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
	    SVREF(new_task,FIX((SI_Long)9L)) = Nil;
	    SVREF(new_task,FIX((SI_Long)10L)) = Nil;
	    SVREF(new_task,FIX((SI_Long)7L)) = Qcompletely_shut_down_g2;
	    temp_2 = SYMBOL_FUNCTION(Qcompletely_shut_down_g2);
	    SVREF(new_task,FIX((SI_Long)8L)) = temp_2;
	    ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)0L);
	    temp_2 = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
	    SVREF(new_task,FIX((SI_Long)11L)) = temp_2;
	    temp_2 = 
		    constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
		    (SI_Long)0L),new_task);
	    SVREF(new_task,FIX((SI_Long)6L)) = temp_2;
	}
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
		  tformat(2,string_constant_29,machine_id);
		  temp_1 = FIX((SI_Long)3L);
		  if (NUM_GT(Chaining_refresh_version,temp_1))
		      tformat(2,string_constant_29,Chaining_refresh_list);
		  keystring = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	modularized_key = modulo_string_hash(keystring,modulus);
	authorized_products_code = 
		sort_scheduled_priorities(authorized_products);
	code_1x = IFIX(code_1) >= (SI_Long)100L ? code_1 : 
		FIX((SI_Long)394L + (SI_Long)185L * IFIX(code_1));
	code_2x = IFIX(code_2) >= (SI_Long)100L ? code_2 : 
		FIX((SI_Long)260L + (SI_Long)165L * IFIX(code_2));
	code_3x = IFIX(code_3) >= (SI_Long)100L ? code_3 : 
		FIX((SI_Long)111L + (SI_Long)64L * IFIX(code_3));
	code_4x = IFIX(code_4) >= (SI_Long)100L ? code_4 : 
		FIX((SI_Long)973L + (SI_Long)469L * IFIX(code_4));
	gensymed_symbol = IFIX(inner_multiply(modularized_key,code_3x));
	gensymed_symbol_1 = IFIX(inner_multiply(code_1x,
		authorized_products_code));
	gensymed_symbol_2 = IFIX(inner_multiply(code_2x,code_4x));
	temp_4 = expiration_date_qm;
	if (temp_4);
	else
	    temp_4 = FIX((SI_Long)0L);
	temp_1 = expiration_date_qm;
	if (temp_1);
	else
	    temp_1 = FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(inner_multiply(temp_4,temp_1));
	gensymed_symbol_4 = number_of_processes_authorized ? 
		IFIX(inner_multiply(code_3x,
		number_of_processes_authorized)) : (SI_Long)0L;
	gensymed_symbol_5 = number_of_processes_authorized ? 
		IFIX(inner_multiply(code_4x,
		FIX(IFIX(number_of_processes_authorized) << (SI_Long)8L))) 
		: (SI_Long)0L;
	gensymed_symbol_6 = IFIX(inner_multiply(code_1x,
		maximum_number_of_concurrent_floating_telewindows_allowed));
	gensymed_symbol_7 = IFIX(inner_multiply(code_2x,
		FIX(IFIX(maximum_number_of_concurrent_floating_telewindows_allowed) 
		<< (SI_Long)8L)));
	gensymed_symbol_8 = IFIX(inner_multiply(code_3x,
		maximum_number_of_concurrent_floating_tw2_allowed));
	gensymed_symbol_9 = IFIX(inner_multiply(code_4x,
		ash(maximum_number_of_concurrent_floating_tw2_allowed,
		FIX((SI_Long)12L))));
	checksum = mod(FIX(gensymed_symbol ^ gensymed_symbol_1 ^ 
		gensymed_symbol_2 ^ gensymed_symbol_3 ^ gensymed_symbol_4 
		^ gensymed_symbol_5 ^ gensymed_symbol_6 ^ 
		gensymed_symbol_7 ^ gensymed_symbol_8 ^ gensymed_symbol_9),
		modulus);
	if (FIXNUM_EQ(checksum,code_5) && expiration_date_qm) {
	    date = get_universal_date();
	    if (expiration_date_qm && IFIX(expiration_date_qm) >= 
		    (SI_Long)8388608L) {
		start_date = IFIX(Reference_date_for_interval_encoding) + 
			(IFIX(expiration_date_qm) & (SI_Long)4095L);
		end_date = start_date + (IFIX(expiration_date_qm) >>  -  - 
			(SI_Long)12L & (SI_Long)2047L);
		result = VALUES_2(FIX(start_date),FIX(end_date));
	    }
	    else
		result = VALUES_2(Nil,expiration_date_qm);
	    MVS_2(result,start_date_qm,end_date_1);
	    if ((start_date_qm ? FIXNUM_LT(date,start_date_qm) : 
		    TRUEP(Nil)) || FIXNUM_GT(date,end_date_1)) {
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
		  current_wide_string = wide_string_bv16;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
			  3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  twrite_beginning_of_wide_string(array_constant_7,
				  FIX((SI_Long)35L));
			  twrite_general_string(FIXNUM_GT(date,end_date_1) 
				  ? string_constant_30 : string_constant_31);
			  result = decode_universal_date(FIXNUM_GT(date,
				  end_date_1) ? end_date_1 : start_date_qm);
			  MVS_3(result,day,month,year);
			  print_decoded_date(day,month,year);
			  twrite_beginning_of_wide_string(array_constant_8,
				  FIX((SI_Long)1L));
			  notification_text_string = 
				  copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		Error_of_ok_file_reader_qm = notification_text_string;
		temp = TRUEP(T);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else {
	    if (FIXNUM_EQ(checksum,code_5) &&  ! 
		    !TRUEP(number_of_processes_authorized)) {
		if ( 
			!TRUEP(Unlimited_backtracking_in_internal_truth_maintenance_p)) 
			    {
		    system_1 = G2_product;
		    if (memq_function(Qruntime,authorized_products))
			option = G2_runtime_option;
		    else if (memq_function(Qrestricted_use,
			    authorized_products))
			option = G2_restricted_use_option;
		    else if (memq_function(Qembedded,authorized_products))
			option = G2_embedded_option;
		    else
			option = G2_development_option;
		    temp_2 = 
			    (IFIX(update_frames_needing_icp_callback(system_1,
			    option)) == (SI_Long)1L ? TRUEP(T) : 
			    TRUEP(Nil)) ? (g2ext_reduce_sleep_tolerance() 
			    != (SI_Long)-1L ? T : Nil) : Nil;
		    Unlimited_backtracking_in_internal_truth_maintenance_p 
			    = temp_2;
		}
		if ( 
			!TRUEP(Unlimited_backtracking_in_internal_truth_maintenance_p)) 
			    {
		    current_wide_string_list = Qdo_not_use;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			    4);
		      wide_string_bv16 = 
			      allocate_byte_vector_16(FIX((SI_Long)2048L + 
			      (SI_Long)3L));
		      bv16_length = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		      aref_arg_2 = bv16_length - (SI_Long)2L;
		      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			      (SI_Long)0L);
		      current_wide_string = wide_string_bv16;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
			      3);
			fill_pointer_for_current_wide_string = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				2);
			  length_1 = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			  total_length_of_current_wide_string = 
				  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)2L) + 
				  ((UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)1L) & 
				  (SI_Long)8191L) << (SI_Long)16L));
			  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				  1);
			    current_twriting_output_type = Qwide_string;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				    0);
			      tformat(1,
				      G2_not_authorized_because_cannot_register_process_license_message);
			      Error_of_ok_file_reader_qm = 
				      copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    temp = TRUEP(T);
		}
		else {
		    temp =  !TRUEP(number_of_processes_authorized);
		    if (temp);
		    else {
			system_1 = G2_product;
			if (memq_function(Qruntime,authorized_products))
			    option = G2_runtime_option;
			else if (memq_function(Qrestricted_use,
				authorized_products))
			    option = G2_restricted_use_option;
			else if (memq_function(Qembedded,authorized_products))
			    option = G2_embedded_option;
			else
			    option = G2_development_option;
			temp_1 = frequently_typed_characters(system_1,option);
			temp = NUM_LT(temp_1,number_of_processes_authorized);
		    }
		    if (temp)
			temp = TRUEP(Nil);
		    else {
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
			  bv16_length = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			  aref_arg_2 = bv16_length - (SI_Long)2L;
			  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  aref_arg_2 = bv16_length - (SI_Long)1L;
			  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  tformat(1,
					  G2_not_authorized_because_fails_process_count_message);
				  Error_of_ok_file_reader_qm = 
					  copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			temp = TRUEP(T);
		    }
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp);
	    else {
		if (g2_enterprise_p() &&  !TRUEP(memq_function(Qent,
			authorized_products))) {
		    current_wide_string_list = Qdo_not_use;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			    4);
		      wide_string_bv16 = 
			      allocate_byte_vector_16(FIX((SI_Long)2048L + 
			      (SI_Long)3L));
		      bv16_length = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		      aref_arg_2 = bv16_length - (SI_Long)2L;
		      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			      (SI_Long)0L);
		      current_wide_string = wide_string_bv16;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
			      3);
			fill_pointer_for_current_wide_string = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				2);
			  length_1 = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			  total_length_of_current_wide_string = 
				  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)2L) + 
				  ((UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)1L) & 
				  (SI_Long)8191L) << (SI_Long)16L));
			  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				  1);
			    current_twriting_output_type = Qwide_string;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				    0);
			      twrite_beginning_of_wide_string(array_constant_25,
				      FIX((SI_Long)64L));
			      notification_text_string = 
				      copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    Error_of_ok_file_reader_qm = notification_text_string;
		    temp = TRUEP(T);
		}
		else
		    temp = TRUEP(Nil);
		if (temp);
		else {
		    if ( !TRUEP(g2_enterprise_p()) && memq_function(Qent,
			    authorized_products)) {
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
			  bv16_length = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			  aref_arg_2 = bv16_length - (SI_Long)2L;
			  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  aref_arg_2 = bv16_length - (SI_Long)1L;
			  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  twrite_beginning_of_wide_string(array_constant_26,
					  FIX((SI_Long)62L));
				  notification_text_string = 
					  copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			Error_of_ok_file_reader_qm = notification_text_string;
			temp = TRUEP(T);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp);
		    else if (FIXNUM_EQ(checksum,code_5)) {
			gensymed_symbol_10 = Format_structure_description;
			M_CAR(gensymed_symbol_10) = code_5;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			temp_2 = Chaining_refresh_list;
			M_CAR(gensymed_symbol_10) = temp_2;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			temp_2 = FIXNUM_MINUS(code_4,code_5);
			M_CAR(gensymed_symbol_10) = temp_2;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			temp_2 = make_array_from_strings(machine_id,
				Chaining_refresh_list);
			M_CAR(gensymed_symbol_10) = temp_2;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			temp_2 = make_array(1,FIX((SI_Long)8L));
			M_CAR(gensymed_symbol_10) = temp_2;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			temp_2 = copy_text_string(machine_id);
			M_CAR(gensymed_symbol_10) = temp_2;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			M_CAR(gensymed_symbol_10) = code_1;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			M_CAR(gensymed_symbol_10) = code_2;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			M_CAR(gensymed_symbol_10) = code_3;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			M_CAR(gensymed_symbol_10) = code_4;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			cons_1 = nth(FIX((SI_Long)10L),
				Format_structure_description);
			M_CAR(cons_1) = authorized_products_code;
			M_CAR(gensymed_symbol_10) = cons_1;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			M_CAR(gensymed_symbol_10) = expiration_date_qm;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			temp_2 = copy_tree(authorized_kb_packages);
			M_CAR(gensymed_symbol_10) = temp_2;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			M_CAR(gensymed_symbol_10) = 
				number_of_processes_authorized;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			M_CAR(gensymed_symbol_10) = 
				maximum_number_of_concurrent_floating_telewindows_allowed;
			gensymed_symbol_10 = M_CDR(gensymed_symbol_10);
			M_CAR(gensymed_symbol_10) = 
				maximum_number_of_concurrent_floating_tw2_allowed;
			if ( ! !EQ(Unevaluated_expression,
				    Within_side_limits)) {
			    if (IFIX(lengthw(machine_id)) > (SI_Long)5L && 
				    UBYTE_16_ISAREF_1(machine_id,
				    (SI_Long)4L) == (SI_Long)58L && 
				    wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id,
				    (SI_Long)2L)),list_constant_1) && 
				    wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id,
				    (SI_Long)1L)),list_constant_2) && 
				    (UBYTE_16_ISAREF_1(machine_id,
				    (SI_Long)3L) == (SI_Long)101L || 
				    UBYTE_16_ISAREF_1(machine_id,
				    (SI_Long)3L) == (SI_Long)69L) && 
				    (UBYTE_16_ISAREF_1(machine_id,
				    (SI_Long)0L) == (SI_Long)83L || 
				    UBYTE_16_ISAREF_1(machine_id,
				    (SI_Long)0L) == (SI_Long)115L))
				c_nsleep(machine_id);
			}
			set_first_string_in_pool_group(machine_id);
			Text_representation_of_our_ok_object = 
				generate_simulation_of_printing_ok_frame();
			visible_product = Nil;
			ab_loop_list_ = authorized_products;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_1:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_1;
			visible_product = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			ab_loopvar__2 = LIST_1(visible_product);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_1;
		      end_loop_1:
			Authorized_products_of_this_machine = ab_loopvar_;
			goto end_2;
			Authorized_products_of_this_machine = Qnil;
		      end_2:;
			Floating_telewindows_limit = 
				maximum_number_of_concurrent_floating_telewindows_allowed;
			schedule_tw_modernization_tasks_if_necessary();
			Floating_tw2_limit = 
				maximum_number_of_concurrent_floating_tw2_allowed;
			temp_2 = Keytab_backbone;
			M_FOURTH(temp_2) = FIX((SI_Long)0L);
			Success_of_ok_file_reader_qm = T;
			code = M_CAR(M_CDR(Journal_shutout_scan_p));
			if (FIXNUMP(code) && (IFIX(code) & (SI_Long)256L) 
				!= (SI_Long)0L)
			    authorize_nupec();
			Consider_asian_language_initializations_qm = T;
			if (Nil) {
			    if (EQ(Nil,Current_schedule_task))
				Current_schedule_task = Nil;
			    if (ISVREF(Nil,(SI_Long)6L))
				cancel_and_reclaim_scheduled_queue_element_1(Nil);
			    inline_note_reclaim_cons(Nil,Nil);
			    structure_being_reclaimed = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				    0);
			      reclaim_schedule_task_args(ISVREF(Nil,
				      (SI_Long)9L));
			      SVREF(Nil,FIX((SI_Long)9L)) = Nil;
			    POP_SPECIAL();
			    temp_2 = 
				    ISVREF(Chain_of_available_schedule_tasks_vector,
				    IFIX(Current_thread_index));
			    SVREF(Nil,FIX((SI_Long)0L)) = temp_2;
			    temp_2 = Chain_of_available_schedule_tasks_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = Nil;
			}
			def_structure_schedule_task_variable = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			if (def_structure_schedule_task_variable) {
			    temp_2 = Chain_of_available_schedule_tasks_vector;
			    temp_3 = Current_thread_index;
			    svref_new_value = 
				    ISVREF(def_structure_schedule_task_variable,
				    (SI_Long)0L);
			    SVREF(temp_2,temp_3) = svref_new_value;
			    SVREF(def_structure_schedule_task_variable,
				    FIX((SI_Long)0L)) = 
				    Qg2_defstruct_structure_name_schedule_task_g2_struct;
			}
			else
			    def_structure_schedule_task_variable = 
				    make_permanent_schedule_task_structure_internal();
			inline_note_allocate_cons(def_structure_schedule_task_variable,
				Nil);
			SVREF(def_structure_schedule_task_variable,
				FIX((SI_Long)2L)) = T;
			SVREF(def_structure_schedule_task_variable,
				FIX((SI_Long)9L)) = Nil;
			new_task = def_structure_schedule_task_variable;
			SVREF(new_task,FIX((SI_Long)4L)) = 
				Higher_than_any_priority;
			SVREF(new_task,FIX((SI_Long)9L)) = Nil;
			SVREF(new_task,FIX((SI_Long)10L)) = Nil;
			SVREF(new_task,FIX((SI_Long)7L)) = 
				Qinitialize_for_asian_languages;
			temp_2 = 
				SYMBOL_FUNCTION(Qinitialize_for_asian_languages);
			SVREF(new_task,FIX((SI_Long)8L)) = temp_2;
			ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)0L);
			temp_2 = ISVREF(Immediate_task_queue_vector,
				(SI_Long)0L);
			SVREF(new_task,FIX((SI_Long)11L)) = temp_2;
			temp_2 = 
				constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
				(SI_Long)0L),new_task);
			SVREF(new_task,FIX((SI_Long)6L)) = temp_2;
			if (make_g2_secure_qm) {
			    if ( ! !EQ(Unevaluated_expression,
				    Within_side_limits))
				Relations_tag_list = T;
			}
			temp_2 = Default_format_structure;
			M_THIRD(temp_2) = Nil;
			Unevaluated_expression = T;
		    }
		    else if ( !EQ(Unevaluated_expression,Within_side_limits)) {
			temp_2 = Keytab_interface_linkage;
			temp_3 = FIXNUM_ADD1(SECOND(temp_2));
			M_SECOND(temp_2) = temp_3;
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
			  bv16_length = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			  aref_arg_2 = bv16_length - (SI_Long)2L;
			  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  aref_arg_2 = bv16_length - (SI_Long)1L;
			  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  tformat(1,
					  authorization_incorrect_when_already_authorized_ok_message());
				  Error_of_ok_file_reader_qm = 
					  copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		    else {
			temp_2 = Keytab_interface_linkage;
			temp_3 = FIXNUM_ADD1(SECOND(temp_2));
			M_SECOND(temp_2) = temp_3;
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
			  bv16_length = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			  aref_arg_2 = bv16_length - (SI_Long)2L;
			  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  aref_arg_2 = bv16_length - (SI_Long)1L;
			  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  tformat(1,
					  authorization_incorrect_ok_message());
				  Error_of_ok_file_reader_qm = 
					  copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		}
	    }
	}
	return reclaim_text_string(keystring);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_27;   /* # */

static Object string_constant_88;  /* "~%~%---~%~A~%~A~%" */

static Object Qverbose;            /* verbose */

static Object string_constant_89;  /* "~%[~A ~s]~%" */

static Object string_constant_90;  /* "~%~A~%" */

/* AUTHORIZE-AB */
Object authorize_ab()
{
    Object pathname_1, current_machine_ids_of_g2_ok_file_qm, trouble_qm;
    Object message_qm, write_console_p, ok_file_namestring;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(107,230);
    SAVE_STACK();
    pathname_1 = Qunbound_in_protected_let;
    current_machine_ids_of_g2_ok_file_qm = Qunbound_in_protected_let;
    trouble_qm = Qunbound_in_protected_let;
    message_qm = Qunbound_in_protected_let;
    PUSH_SPECIAL_WITH_SYMBOL(Current_machine_ids_of_g2_ok_file_qm,Qcurrent_machine_ids_of_g2_ok_file_qm,current_machine_ids_of_g2_ok_file_qm,
	    1);
      if (PUSH_UNWIND_PROTECT(0)) {
	  pathname_1 = get_appropriate_ok_pathname(0);
	  Current_machine_ids_of_g2_ok_file_qm = 
		  get_local_machine_ids_as_gensym_list();
	  trouble_qm =  !EQ(Unevaluated_expression,Within_side_limits) ? 
		  Nil : pathname_1 ? read_ok_file(1,pathname_1) : 
		  array_constant_27;
	  message_qm = trouble_qm ? 
		  make_authorization_file_status_string(pathname_1,
		  Current_machine_ids_of_g2_ok_file_qm) : Nil;
	  if (trouble_qm) {
	      write_console_p = T;
	      PUSH_SPECIAL_WITH_SYMBOL(Write_console_p,Qwrite_console_p,write_console_p,
		      0);
		notify_user_at_console(3,string_constant_88,trouble_qm,
			message_qm);
	      POP_SPECIAL();
	      reclaim_text_string(message_qm);
	      SAVE_VALUES(VALUES_1(Nil));
	  }
	  else if ( !EQ(Unevaluated_expression,Within_side_limits)) {
	      set_authorizing_ok_pathname(pathname_1);
	      if (EQ(Verbosity_level,Qverbose)) {
		  ok_file_namestring = gensym_namestring(1,pathname_1);
		  write_console_p = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_console_p,Qwrite_console_p,write_console_p,
			  0);
		    notify_user_at_console(3,string_constant_89,
			    Using_g2_ok_file_message,ok_file_namestring);
		  POP_SPECIAL();
		  reclaim_text_string(ok_file_namestring);
	      }
	      write_console_p = T;
	      PUSH_SPECIAL_WITH_SYMBOL(Write_console_p,Qwrite_console_p,write_console_p,
		      0);
		notify_user_at_console(2,string_constant_90,
			Ok_to_run_g2_message);
	      POP_SPECIAL();
	      if (Relations_tag_list)
		  check_password_setup_and_notify_user_if_necessary();
	      SAVE_VALUES(VALUES_1(T));
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
      }
      POP_UNWIND_PROTECT(0);
      if (Current_machine_ids_of_g2_ok_file_qm) {
	  if ( !EQ(Current_machine_ids_of_g2_ok_file_qm,
		  Qunbound_in_protected_let))
	      reclaim_gensym_tree_with_text_strings(Current_machine_ids_of_g2_ok_file_qm);
      }
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object array_constant_28;   /* # */

static Object array_constant_29;   /* # */

static Object array_constant_30;   /* # */

static Object array_constant_31;   /* # */

static Object array_constant_32;   /* # */

static Object array_constant_33;   /* # */

static Object array_constant_34;   /* # */

static Object array_constant_35;   /* # */

static Object array_constant_36;   /* # */

/* GENERATE-SIMULATION-OF-PRINTING-OK-FRAME */
Object generate_simulation_of_printing_ok_frame()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(107,231);
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
	      write_pad_slot(array_constant_28);
	      write_pad_slot(array_constant_29);
	      write_pad_slot(array_constant_30);
	      write_pad_slot(array_constant_31);
	      write_pad_slot(array_constant_32);
	      write_pad_slot(array_constant_33);
	      write_pad_slot(array_constant_34);
	      write_pad_slot(array_constant_35);
	      write_pad_slot(array_constant_36);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qstring_equalw;      /* string-equalw */

static Object string_constant_91;  /* "  ~A:" */

/* WRITE-PAD-SLOT */
Object write_pad_slot(slot_name)
    Object slot_name;
{
    Object index_of_slot, type_description;

    x_note_fn_call(107,232);
    index_of_slot = position(6,slot_name,
	    Slot_pad_descriptions_of_machine_authorization,Kkey,
	    SYMBOL_FUNCTION(Qfirst),Ktest,
	    Symbol_token_match_should_be_case_sensitive_p ? 
	    SYMBOL_FUNCTION(Qstring_eq_w) : SYMBOL_FUNCTION(Qstring_equalw));
    type_description = nth(index_of_slot,
	    Slot_pad_descriptions_of_machine_authorization);
    tformat(2,string_constant_91,slot_name);
    twrite_ok_token(ISVREF(Slot_pad_of_ok_file_reader,IFIX(index_of_slot)),
	    ATOM(type_description) ? T : Nil);
    return tformat(1,string_constant_25);
}

static Object string_constant_92;  /* "~%          " */

/* TWRITE-OK-TOKEN */
Object twrite_ok_token(token,simple_qm)
    Object token, simple_qm;
{
    Object value, temp, element, ab_loop_list_;
    char long_qm;

    x_note_fn_call(107,233);
    value = ISVREF(token,(SI_Long)4L);
    temp = ISVREF(token,(SI_Long)1L);
    if (EQ(temp,Kinteger))
	return tformat(2,string_constant_74,value);
    else if (EQ(temp,Kstring))
	return tformat(2,string_constant_73,ISVREF(token,(SI_Long)3L));
    else if (EQ(temp,Ksymbol)) {
	if ( !TRUEP(value))
	    return tformat(1,string_constant_71);
	else
	    return tformat(2,string_constant_73,value);
    }
    else if (EQ(temp,Klist)) {
	if ( !TRUEP(value))
	    return tformat(1,string_constant_71);
	else {
	    tformat(1,string_constant_76);
	    long_qm = (SI_Long)5L < IFIX(length(value));
	    element = Nil;
	    ab_loop_list_ = value;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (long_qm)
		tformat(1,string_constant_92);
	    twrite_ok_token(element,simple_qm);
	    goto next_loop;
	  end_loop:;
	    return tformat(1,string_constant_78);
	}
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_93;  /* "OK file must exist and be readable." */

/* COULD-NOT-OPEN-STREAM-OK-MESSAGE */
Object could_not_open_stream_ok_message()
{
    x_note_fn_call(107,234);
    return VALUES_1(string_constant_93);
}

static Object string_constant_94;  /* "OK-file-path must specify a valid file name" */

/* NO-FILENAME-PROVIDED-OK-MESSAGE */
Object no_filename_provided_ok_message()
{
    x_note_fn_call(107,235);
    return VALUES_1(string_constant_94);
}

static Object string_constant_95;  /* "A minus sign can only introduce a comment." */

/* HYPHEN-NOT-FOLLOWED-BY-ANOTHER-HYPHEN-OK-MESSAGE */
Object hyphen_not_followed_by_another_hyphen_ok_message()
{
    x_note_fn_call(107,236);
    return VALUES_1(string_constant_95);
}

static Object string_constant_96;  /* "Only certain characters may start a new token." */

/* CHARACTER-CANNOT-START-TOKEN-OK-MESSAGE */
Object character_cannot_start_token_ok_message()
{
    x_note_fn_call(107,237);
    return VALUES_1(string_constant_96);
}

static Object string_constant_97;  /* "Strings must be less than 60 characters." */

/* STRING-TOO-LONG-OK-MESSAGE */
Object string_too_long_ok_message()
{
    x_note_fn_call(107,238);
    return VALUES_1(string_constant_97);
}

static Object string_constant_98;  /* "Strings may not contain atsign, tilde, backslash or line terminators." */

/* ILLEGAL-CHARACTER-IN-STRING-OK-MESSAGE */
Object illegal_character_in_string_ok_message()
{
    x_note_fn_call(107,239);
    return VALUES_1(string_constant_98);
}

static Object string_constant_99;  /* "Symbols must be less than 60 characters." */

/* SYMBOL-TOO-LONG-OK-MESSAGE */
Object symbol_too_long_ok_message()
{
    x_note_fn_call(107,240);
    return VALUES_1(string_constant_99);
}

static Object string_constant_100;  /* "Integers must be less than 40 digits." */

/* INTEGER-TOO-LONG-OK-MESSAGE */
Object integer_too_long_ok_message()
{
    x_note_fn_call(107,241);
    return VALUES_1(string_constant_100);
}

static Object string_constant_101;  /* "Integers contain only digits." */

/* INTEGER-CONTAINS-NON-DIGIT-CHARACTER-OK-MESSAGE */
Object integer_contains_non_digit_character_ok_message()
{
    x_note_fn_call(107,242);
    return VALUES_1(string_constant_101);
}

static Object string_constant_102;  /* "Lists must contain less than 60 elements" */

/* TOO-MANY-ELEMENTS-IN-LIST-OK-MESSAGE */
Object too_many_elements_in_list_ok_message()
{
    x_note_fn_call(107,243);
    return VALUES_1(string_constant_102);
}

static Object string_constant_103;  /* "Premature end of file." */

/* EOF-IN-MIDDLE-OF-STATEMENT-OK-MESSAGE */
Object eof_in_middle_of_statement_ok_message()
{
    x_note_fn_call(107,244);
    return VALUES_1(string_constant_103);
}

static Object string_constant_104;  /* "Attribute value pairs must end with a semicolon" */

/* FOURTH-ELEMENT-OF-STATEMENT-NOT-A-SEMICOLON-OK-MESSAGE */
Object fourth_element_of_statement_not_a_semicolon_ok_message()
{
    x_note_fn_call(107,245);
    return VALUES_1(string_constant_104);
}

static Object string_constant_105;  /* "Attribute values must be integers, lists, or symbols." */

/* ILLEGAL-ATTRIBUTE-VALUE-OK-MESSAGE */
Object illegal_attribute_value_ok_message()
{
    x_note_fn_call(107,246);
    return VALUES_1(string_constant_105);
}

static Object string_constant_106;  /* "Bad type for the value of the attribute ~a: ~a~
				     *            ~%Attribute values must be integers, lists, or symbols."
				     */

/* ILLEGAL-ATTRIBUTE-VALUE-OK-MESSAGE-1 */
Object illegal_attribute_value_ok_message_1(attribute_token,bad_token)
    Object attribute_token, bad_token;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(107,247);
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
	      tformat(3,string_constant_106,ISVREF(attribute_token,
		      (SI_Long)3L),ISVREF(bad_token,(SI_Long)1L));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_107;  /* "Cannot parse statement." */

/* UNKNOWN-PROBLEM-PARSING-STATEMENT-OK-MESSAGE */
Object unknown_problem_parsing_statement_ok_message()
{
    x_note_fn_call(107,248);
    return VALUES_1(string_constant_107);
}

static Object string_constant_108;  /* "The first N characters of file must be \"begin g2-ok-file\"." */

/* SANITY-CHECK-ON-INITIAL-CHARACTERS-OF-FILE-OK-MESSAGE */
Object sanity_check_on_initial_characters_of_file_ok_message()
{
    x_note_fn_call(107,249);
    return VALUES_1(string_constant_108);
}

static Object string_constant_109;  /* "The file must contain one g2-ok-file entity" */

/* HEADER-FOR-FILE-ENTRY-MISSING-OK-MESSAGE */
Object header_for_file_entry_missing_ok_message()
{
    x_note_fn_call(107,250);
    return VALUES_1(string_constant_109);
}

static Object string_constant_110;  /* "None of the entries in this authorization file has a machine id that matched this machine" */

/* NO-AUTHORIZATION-FOUND-FOR-THIS-MACHINE-MULTIPLE-ENTRIES-OK-MESSAGE */
Object no_authorization_found_for_this_machine_multiple_entries_ok_message()
{
    x_note_fn_call(107,251);
    return VALUES_1(string_constant_110);
}

static Object string_constant_111;  /* "The machine id in the authorization file does not match the id for this machine." */

/* NO-AUTHORIZATION-FOUND-FOR-THIS-MACHINE-ONE-ENTRY-OK-MESSAGE */
Object no_authorization_found_for_this_machine_one_entry_ok_message()
{
    x_note_fn_call(107,252);
    return VALUES_1(string_constant_111);
}

static Object string_constant_112;  /* "Unexpected element found inside of g2-ok-file-entity." */

/* UNDEFINED-ENTRY-TYPE-OK-MESSAGE */
Object undefined_entry_type_ok_message()
{
    x_note_fn_call(107,253);
    return VALUES_1(string_constant_112);
}

static Object string_constant_113;  /* "Entity attributes must appear before subentities." */

/* FILE-ATTRIBUTE-NOT-INITIAL-OK-MESSAGE */
Object file_attribute_not_initial_ok_message()
{
    x_note_fn_call(107,254);
    return VALUES_1(string_constant_113);
}

static Object string_constant_114;  /* "Only file-format-version attributes may appear in g2-ok-files." */

/* UNDEFINED-FILE-ATTRIBUTE-OK-MESSAGE */
Object undefined_file_attribute_ok_message()
{
    x_note_fn_call(107,255);
    return VALUES_1(string_constant_114);
}

static Object string_constant_115;  /* "Attributes may only appear once." */

/* FILE-FORMAT-ATTRIBUTE-DUPLICATED-OK-MESSAGE */
Object file_format_attribute_duplicated_ok_message()
{
    x_note_fn_call(107,256);
    return VALUES_1(string_constant_115);
}

static Object string_constant_116;  /* "Attribute must be an integer." */

/* FILE-FORMAT-VALUE-NOT-AN-INTEGER-OK-MESSAGE */
Object file_format_value_not_an_integer_ok_message()
{
    x_note_fn_call(107,257);
    return VALUES_1(string_constant_116);
}

static Object string_constant_117;  /* "This G2 can only read OK files in version ~a format.~
				     *             ~%The OK file being loaded is in version ~a format and is incompatible~
				     *             ~%because it contains attributes or codes that your G2 will not understand."
				     */

/* FILE-VERSION-HIGHER-THAN-IMAGE-VERSION-OK-MESSAGE-1 */
Object file_version_higher_than_image_version_ok_message_1(image_version,
	    ok_version)
    Object image_version, ok_version;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(107,258);
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
	      tformat(3,string_constant_117,image_version,ok_version);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_118;  /* "The type given on begin and end must match." */

/* WRONG-LABEL-ON-FILE-LEVEL-END-STATEMENT-OK-MESSAGE */
Object wrong_label_on_file_level_end_statement_ok_message()
{
    x_note_fn_call(107,259);
    return VALUES_1(string_constant_118);
}

static Object string_constant_119;  /* "File must be parsable." */

/* UNKNOWN-PROBLEM-PARSING-FILE-OK-MESSAGE */
Object unknown_problem_parsing_file_ok_message()
{
    x_note_fn_call(107,260);
    return VALUES_1(string_constant_119);
}

static Object string_constant_120;  /* "OK file must contain at least one machine authorization." */

/* NO-MACHINE-AUTHORIZATION-IN-FILE-OK-MESSAGE */
Object no_machine_authorization_in_file_ok_message()
{
    x_note_fn_call(107,261);
    return VALUES_1(string_constant_120);
}

/* WRONG-LABEL-ON-END-STATEMENT-OK-MESSAGE */
Object wrong_label_on_end_statement_ok_message()
{
    x_note_fn_call(107,262);
    return VALUES_1(string_constant_118);
}

static Object string_constant_121;  /* "File syntax must be correct." */

/* UNKNOWN-PROBLEM-PARSING-ENTRY-OK-MESSAGE */
Object unknown_problem_parsing_entry_ok_message()
{
    x_note_fn_call(107,263);
    return VALUES_1(string_constant_121);
}

static Object string_constant_122;  /* "Users must have some permitted user-modes." */

/* NO-USER-MODES-SPECIFIED-OK-MESSAGE */
Object no_user_modes_specified_ok_message()
{
    x_note_fn_call(107,264);
    return VALUES_1(string_constant_122);
}

static Object string_constant_123;  /* "Proprietary is not a user-mode." */

/* PROPRIETARY-MODE-SPECIFIED-OK-MESSAGE */
Object proprietary_mode_specified_ok_message()
{
    x_note_fn_call(107,265);
    return VALUES_1(string_constant_123);
}

static Object string_constant_124;  /* "A machine-id attribute is required." */

/* MACHINE-ID-MISSING-OK-MESSAGE */
Object machine_id_missing_ok_message()
{
    x_note_fn_call(107,266);
    return VALUES_1(string_constant_124);
}

static Object string_constant_125;  /* "A authorization attribute is required." */

/* AUTHORIZATION-MISSING-OK-MESSAGE */
Object authorization_missing_ok_message()
{
    x_note_fn_call(107,267);
    return VALUES_1(string_constant_125);
}

static Object string_constant_126;  /* "The machine ID must meet certain rules." */

/* SHUNNED-MACHINE-ID-OK-MESSAGE */
Object shunned_machine_id_ok_message()
{
    x_note_fn_call(107,268);
    return VALUES_1(string_constant_126);
}

static Object string_constant_127;  /* "The date range must be reasonable." */

/* FROM-DATE-EARLIER-THAN-TO-DATE-OK-MESSAGE */
Object from_date_earlier_than_to_date_ok_message()
{
    x_note_fn_call(107,269);
    return VALUES_1(string_constant_127);
}

static Object string_constant_128;  /* "Illegal attribute name." */

/* UNRECOGNIZED-ATTRIBUTE-OK-MESSAGE */
Object unrecognized_attribute_ok_message()
{
    x_note_fn_call(107,270);
    return VALUES_1(string_constant_128);
}

static Object string_constant_129;  /* "Unknown attribute: \"~a\"" */

/* UNRECOGNIZED-ATTRIBUTE-OK-MESSAGE-1 */
Object unrecognized_attribute_ok_message_1(name)
    Object name;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(107,271);
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
	      tformat(2,string_constant_129,ISVREF(name,(SI_Long)3L));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_130;  /* "Attribute value is not right." */

/* SYNTAX-ERROR-IN-ATTRIBUTE-VALUE-OK-MESSAGE */
Object syntax_error_in_attribute_value_ok_message()
{
    x_note_fn_call(107,272);
    return VALUES_1(string_constant_130);
}

static Object string_constant_131;  /* "The value ~a is the wrong type for the attribute ~a.~
				     *             ~%It should be of type ~a"
				     */

/* SYNTAX-ERROR-IN-ATTRIBUTE-VALUE-OK-MESSAGE-1 */
Object syntax_error_in_attribute_value_ok_message_1(name,value,correct_type)
    Object name, value, correct_type;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(107,273);
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
	      tformat(4,string_constant_131,ISVREF(value,(SI_Long)4L),
		      ISVREF(name,(SI_Long)3L),correct_type);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_132;  /* "Duplicate attributes are illegal." */

/* ATTRIBUTE-APPEARS-MORE-THAN-ONCE-OK-MESSAGE */
Object attribute_appears_more_than_once_ok_message()
{
    x_note_fn_call(107,274);
    return VALUES_1(string_constant_132);
}

static Object string_constant_133;  /* "This instance of attribute ~a is a duplicate" */

/* ATTRIBUTE-APPEARS-MORE-THAN-ONCE-OK-MESSAGE-1 */
Object attribute_appears_more_than_once_ok_message_1(name)
    Object name;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(107,275);
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
	      tformat(2,string_constant_133,ISVREF(name,(SI_Long)3L));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_134;  /* "You were already authorized.~%You are still authorized.~%Meanwhile the authorization found in the OK file was wrong." */

/* AUTHORIZATION-INCORRECT-WHEN-ALREADY-AUTHORIZED-OK-MESSAGE */
Object authorization_incorrect_when_already_authorized_ok_message()
{
    x_note_fn_call(107,276);
    return VALUES_1(string_constant_134);
}

static Object string_constant_135;  /* "The authorization is not correct. Please check it and try again." */

/* AUTHORIZATION-INCORRECT-OK-MESSAGE */
Object authorization_incorrect_ok_message()
{
    x_note_fn_call(107,277);
    return VALUES_1(string_constant_135);
}

static Object string_constant_136;  /* "Limit on number of Floating Telewindows licenses ~
				     *      exceeded.  Closing unauthorized connection(s) immediately."
				     */

/* NUMBER-OF-FLOATING-TELEWINDOWS-LIMIT-EXCEEDED-OK-MESSAGE */
Object number_of_floating_telewindows_limit_exceeded_ok_message()
{
    x_note_fn_call(107,278);
    return VALUES_1(string_constant_136);
}

static Object string_constant_137;  /* "A connection to ~a Telewindows is being closed immediately ~
				     *     because it is not permitted to connect to a Development version of G2."
				     */

/* NOT-PERMITTED-TO-CONNECT-TO-DEVELOPMENT-G2-OK-MESSAGE */
Object not_permitted_to_connect_to_development_g2_ok_message()
{
    x_note_fn_call(107,279);
    return VALUES_1(string_constant_137);
}

static Object string_constant_138;  /* "Bad package authorization." */

/* INCORRECT-AUTHORIZATION-FOR-PACKAGE-OK-MESSAGE */
Object incorrect_authorization_for_package_ok_message()
{
    x_note_fn_call(107,280);
    return VALUES_1(string_constant_138);
}

static Object string_constant_139;  /* "Wrong number of codes in authorization field. There should be five." */

/* WRONG-NUMBER-OF-AUTHORIZATION-CODES-OK-MESSAGE */
Object wrong_number_of_authorization_codes_ok_message()
{
    x_note_fn_call(107,281);
    return VALUES_1(string_constant_139);
}

static Object string_constant_140;  /* "Premature end of file: some entry was not terminated" */

/* REACHED-EOF-WHILE-INSIDE-AN-ENTRY-OK-MESSAGE */
Object reached_eof_while_inside_an_entry_ok_message()
{
    x_note_fn_call(107,282);
    return VALUES_1(string_constant_140);
}

static Object string_constant_141;  /* "Unexpected start of an entry: previous entry was not terminated" */

/* ENTRY-STARTED-WHILE-STILL-INSIDE-ENTRY-OK-MESSAGE */
Object entry_started_while_still_inside_entry_ok_message()
{
    x_note_fn_call(107,283);
    return VALUES_1(string_constant_141);
}

static Object string_constant_142;  /* "The license to run G2 on this machine has expired.~%" */

/* LICENSE-ON-THIS-MACHINE-HAS-EXPIRED-OK-MESSAGE */
Object license_on_this_machine_has_expired_ok_message()
{
    x_note_fn_call(107,284);
    return VALUES_1(string_constant_142);
}

static Object string_constant_143;  /* "The license to use G2 on this machine expires today.~% G2 will not run after today.~%~%" */

/* LICENCE-ON-THIS-MACHINE-EXPIRES-TODAY-OK-MESSAGE */
Object licence_on_this_machine_expires_today_ok_message()
{
    x_note_fn_call(107,285);
    return VALUES_1(string_constant_143);
}

void sequences2_INIT()
{
    Object module_name, invisible_module_p, ab_loop_list_, ab_loop_desetq_;
    Object temp, temp_1, reclaim_structure_for_t2_nonce_data_1, new_cons;
    Object temp_2, temp_3, svref_new_value, gensymed_symbol;
    Object write_bad_package_authorization_note_1, temp_4;
    Object amf_available_array_cons_qm, amf_array, amf_result, new_float;
    Object named_dynamic_extent_description;
    Object reclaim_structure_for_ok_file_token_1;
    Object AB_package, list_constant_8, Qg2passwdexe_areyouthere_good_result;
    Object string_constant_228, Qg2passwdexe_areyouthere_arg;
    Object list_constant_134, Qsequences2, Qinitialize_g2passwdexe;
    Object list_constant_133, Kfuncall, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qunbound_value_for_ok_reader_1, list_constant_132;
    Object list_constant_131, list_constant_130, list_constant_129;
    Object list_constant_114, list_constant_128, array_constant_98;
    Object list_constant_98, list_constant_105, Qpassword_validity;
    Object array_constant_97, list_constant_99, Qpassword, array_constant_96;
    Object list_constant_127, list_constant_126, list_constant_125;
    Object list_constant_124, list_constant_123, list_constant_122;
    Object list_constant_121, list_constant_120, list_constant_119;
    Object list_constant_118, list_constant_117, list_constant_116;
    Object list_constant_115, Qinstallation_code, array_constant_95;
    Object Qserial_number, array_constant_94, Qcustomer, array_constant_93;
    Object Qmaximum_number_of_concurrent_floating_tw2_allowed;
    Object list_constant_113, list_constant_112, list_constant_111;
    Object list_constant_110, list_constant_109, list_constant_103;
    Object list_constant_104, list_constant_102, array_constant_92;
    Object list_constant_108, Qauthorization, list_constant_107;
    Object list_constant_106, array_constant_91, array_constant_90;
    Object array_constant_89, array_constant_88, array_constant_87;
    Object array_constant_86, array_constant_85, array_constant_84;
    Object array_constant_83, array_constant_82, array_constant_81;
    Object array_constant_80, array_constant_79, array_constant_78;
    Object list_constant_101, list_constant_100, array_constant_77;
    Object array_constant_76, array_constant_75, array_constant_74;
    Object array_constant_73, array_constant_72, array_constant_71;
    Object array_constant_70, array_constant_69, array_constant_68;
    Object array_constant_67, array_constant_66, array_constant_65;
    Object array_constant_64, array_constant_63, array_constant_62;
    Object array_constant_61, array_constant_60, array_constant_59, Qname;
    Object string_constant_227, Qok_file_token_cons_memory_usage;
    Object Qoutstanding_ok_file_token_conses, Qutilities1, list_constant_97;
    Object Qok_file_token_cons_counter_vector, Qmake_thread_array;
    Object list_constant_96, Qavailable_ok_file_token_conses_tail_vector;
    Object Qavailable_ok_file_token_conses_vector, list_constant_95;
    Object Qreclaim_structure, Qoutstanding_ok_file_token_count;
    Object Qok_file_token_structure_memory_usage, Qutilities2;
    Object string_constant_226, Qtype_description_of_type, string_constant_225;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, array_constant_58;
    Object Qsymbol_token_match_should_be_case_sensitive_p;
    Object Qperiod_character_for_g2_ok_file;
    Object Qquestion_mark_character_for_g2_ok_file;
    Object Qunderscore_character_for_g2_ok_file, Qlf_character_for_g2_ok_file;
    Object Qcr_character_for_g2_ok_file, Qalphabetic_character_for_g2_ok_file;
    Object Qdigit_character_for_g2_ok_file, Qdash_character_for_g2_ok_file;
    Object Qsemicolon_character_for_g2_ok_file;
    Object Qcolon_character_for_g2_ok_file;
    Object Qclose_paren_character_for_g2_ok_file;
    Object Qopen_paren_character_for_g2_ok_file;
    Object Qopen_string_character_for_g2_ok_file;
    Object Qwhitespace_character_for_g2_ok_file;
    Object Qillegal_character_for_g2_ok_file, Qeof_character_for_g2_ok_file;
    Object list_constant_94, list_constant_93;
    Object Qcompute_process_initial_value_for_pad_for_ok_file_reader;
    Object Qnamed_dynamic_extent_description, string_constant_224;
    Object Qclasses_which_define, Qcleanup, Qcleanup_for_kb_workspace;
    Object Qslot_putter, Qput_proprietary_package, Qslot_value_writer;
    Object Qwrite_proprietary_package_from_slot, string_constant_223;
    Object Qnil_function, string_constant_222, string_constant_221;
    Object string_constant_220, string_constant_219, string_constant_218;
    Object string_constant_217, string_constant_216, string_constant_215;
    Object string_constant_214, string_constant_213, string_constant_212;
    Object string_constant_211, string_constant_210, string_constant_209;
    Object string_constant_208, string_constant_207, string_constant_206;
    Object Qput_user_password, Qput_permitted_user_modes, Qadministrator;
    Object Qfloat_array, Qwrite_permitted_mode_list_from_slot;
    Object Qpermitted_mode_list;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_permitted_mode_list_for_slot;
    Object Qwrite_user_password_from_slot, Qcompile_user_password_for_slot;
    Object string_constant_205, Qsimplify_associative_operation;
    Object string_constant_204, string_constant_203, string_constant_202;
    Object list_constant_50, Qcreate_icon_description, string_constant_201;
    Object string_constant_200, string_constant_199, string_constant_144;
    Object list_constant_92, list_constant_91, list_constant_90;
    Object list_constant_89, list_constant_88, list_constant_87;
    Object list_constant_86, list_constant_85, list_constant_84;
    Object list_constant_83, list_constant_82, Qnupec_extra_action_list;
    Object Qaction, list_constant_81, list_constant_80, list_constant_76;
    Object Qaction_list_3, list_constant_79, Qfix_nupec_synchronize;
    Object list_constant_78, list_constant_77, Qnupec_synchronize;
    Object Qunique_designation, list_constant_75, Qsynchronize_reference_list;
    Object list_constant_74, list_constant_54, Qacross, Qsynchronize;
    Object list_constant_73, list_constant_72, Qevent_literal;
    Object Qnupec_synchronization_occurs, list_constant_71, list_constant_70;
    Object Qoccurs, Qsynchronization, list_constant_69, list_constant_68;
    Object Qplot_marker_phrase, list_constant_67, list_constant_66, Qab_class;
    Object list_constant_65, Qmarker, Qplot, Qusing, Qnupec_catch_up;
    Object list_constant_64, Qtiming_scheduler_mode, list_constant_63;
    Object list_constant_62, list_constant_61, Qmode, Qup, Qab_catch;
    Object Qnupec_snapshot_with_restart_time, list_constant_60;
    Object Qgfi_file_format, list_constant_59, list_constant_58;
    Object list_constant_57, list_constant_55, Qab_restart, Qwith;
    Object Qnupec_snapshot, list_constant_56, Qsnapshot, Qnupec;
    Object string_constant_198, list_constant_53, Qchoose_keytab;
    Object list_constant_52, string_constant_197, string_constant_196;
    Object string_constant_195, array_constant_57;
    Object Qg2_not_authorized_because_cannot_register_process_license_message;
    Object string_constant_194, string_constant_193, string_constant_192;
    Object string_constant_191, array_constant_56;
    Object Qg2_not_authorized_because_fails_process_count_message;
    Object string_constant_190, string_constant_189, string_constant_188;
    Object string_constant_187, string_constant_186, string_constant_185;
    Object array_constant_55;
    Object Qcan_create_additional_users_and_then_save_ok_file_message_2;
    Object string_constant_184, string_constant_183, array_constant_54;
    Object Qcan_create_additional_users_and_then_save_ok_file_message_1;
    Object string_constant_182, array_constant_53;
    Object Qcan_create_additional_users_and_then_save_ok_file_message_format_control_string;
    Object string_constant_181, string_constant_180, string_constant_179;
    Object string_constant_178, string_constant_177, string_constant_176;
    Object array_constant_52;
    Object Qshould_create_users_and_then_save_ok_file_message_3;
    Object string_constant_175, string_constant_174, array_constant_51;
    Object Qshould_create_users_and_then_save_ok_file_message_2;
    Object string_constant_173, string_constant_172, string_constant_171;
    Object string_constant_170, array_constant_50;
    Object Qshould_create_users_and_then_save_ok_file_message_1;
    Object string_constant_169, array_constant_49;
    Object Qshould_create_users_and_then_save_ok_file_message_format_control_string;
    Object string_constant_168, string_constant_167, string_constant_166;
    Object array_constant_48, Qshould_save_ok_file_message;
    Object string_constant_165, array_constant_47, Qok_to_run_g2_message;
    Object string_constant_164, array_constant_46, Qusing_g2_ok_file_message;
    Object Qput_authorized_kb_packages, Qframe_note_writer_1;
    Object Qauthorized_packages, Qcompile_authorized_packages_for_slot;
    Object Qwrite_authorized_packages_from_slot, string_constant_163;
    Object string_constant_162, string_constant_161;
    Object Qput_maximum_number_of_concurrent_floating_telewindows_allowed;
    Object Qput_number_of_processes_authorized;
    Object Qwrite_number_of_processes_from_slot, Qnumber_of_processes;
    Object Qcompile_number_of_processes_for_slot, string_constant_160;
    Object Qget_g2_is_secure, Qinitial_g2_is_secure, Qtruth_value;
    Object list_constant_51, Qg2_is_secure, Qvirtual_attributes_local_to_class;
    Object Qlookup, Qt2_nonce_hash, Qmutate_t2_nonce_hash_tree_entry;
    Object Qt2_nonce_data, Qoutstanding_t2_nonce_data_count;
    Object Qt2_nonce_data_structure_memory_usage, string_constant_159;
    Object string_constant_158, Qwrite_authorization_interval_qm_from_slot;
    Object Qauthorization_interval_qm, string_constant_157, Qjan_1_2015;
    Object Qjan_1_2009, Qjan_1_2006, Qjan_1_1999, Qjan_1_1998, Qjan_1_1990;
    Object Qwrite_number_or_unlimited_from_slot, Qnumber_or_unlimited;
    Object Qwrite_products_qm_from_slot, Qproducts_qm;
    Object Qcompile_products_qm_for_slot, string_constant_156;
    Object Qput_ok_slot_coordinator, Qput_make_g2_secure_qm;
    Object Qput_expiration_date_qm, Qput_authorized_products, Qput_code_5;
    Object Qput_code_4, Qput_code_3, Qput_code_2, Qput_code_1, Qput_machine_id;
    Object Qid_or_whole_string_qm, Qcompile_id_or_whole_string_qm_for_slot;
    Object Qwrite_id_or_whole_string_qm_from_slot, string_constant_155;
    Object Qabsent_slot_putter, Qput_expiration_date_where_slot_is_absent;
    Object Qexpiration_date, Qauthorized_optional_modules, string_constant_154;
    Object Qwrite_non_negative_integer_or_none_from_slot;
    Object Qnon_negative_integer_or_none;
    Object Qcompile_non_negative_integer_or_none_for_slot, string_constant_153;
    Object string_constant_152, string_constant_151, string_constant_150;
    Object string_constant_149, string_constant_148, string_constant_147;
    Object string_constant_146, string_constant_145, Qentity, list_constant_49;
    Object list_constant_48, list_constant_47, list_constant_46;
    Object list_constant_45, list_constant_44, list_constant_43;
    Object list_constant_42, list_constant_41, list_constant_40;
    Object list_constant_39, list_constant_38, list_constant_37;
    Object list_constant_36, list_constant_14, array_constant_45;
    Object list_constant_35, list_constant_34, array_constant_44;
    Object list_constant_33, list_constant_32, array_constant_43;
    Object list_constant_31, list_constant_30, array_constant_42;
    Object list_constant_29, list_constant_28, array_constant_41;
    Object list_constant_27, list_constant_26, array_constant_40;
    Object list_constant_25, list_constant_24, array_constant_39;
    Object list_constant_23, list_constant_22, list_constant_13;
    Object list_constant_21, Qoct, array_constant_38, Qnov, list_constant_20;
    Object list_constant_19, list_constant_18, list_constant_17;
    Object list_constant_10, list_constant_16, list_constant_15;
    Object array_constant_37, list_constant_12, list_constant_11;
    Object list_constant_9, Qchoose_pulse_rate_multiplier, Qproduct;
    Object Qdevelopment_lic_level, Qrestricted_use_lic_level;
    Object Qruntime_lic_level, Qembedded_lic_level, Qfloating_lic_level;
    Object Qunauthorized_lic_level;

    x_note_fn_call(107,286);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qunauthorized_lic_level = STATIC_SYMBOL("UNAUTHORIZED-LIC-LEVEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qunauthorized_lic_level,FIX((SI_Long)-2L));
    Qfloating_lic_level = STATIC_SYMBOL("FLOATING-LIC-LEVEL",AB_package);
    SET_SYMBOL_VALUE(Qfloating_lic_level,FIX((SI_Long)-1L));
    Qembedded_lic_level = STATIC_SYMBOL("EMBEDDED-LIC-LEVEL",AB_package);
    SET_SYMBOL_VALUE(Qembedded_lic_level,FIX((SI_Long)0L));
    Qruntime_lic_level = STATIC_SYMBOL("RUNTIME-LIC-LEVEL",AB_package);
    SET_SYMBOL_VALUE(Qruntime_lic_level,FIX((SI_Long)1L));
    Qrestricted_use_lic_level = STATIC_SYMBOL("RESTRICTED-USE-LIC-LEVEL",
	    AB_package);
    SET_SYMBOL_VALUE(Qrestricted_use_lic_level,FIX((SI_Long)2L));
    Qdevelopment_lic_level = STATIC_SYMBOL("DEVELOPMENT-LIC-LEVEL",AB_package);
    SET_SYMBOL_VALUE(Qdevelopment_lic_level,FIX((SI_Long)3L));
    Optional_modules_map = nreverse(Optional_modules_map);
    Qproduct = STATIC_SYMBOL("PRODUCT",AB_package);
    module_name = Nil;
    invisible_module_p = Nil;
    ab_loop_list_ = Optional_modules_map;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    module_name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    invisible_module_p = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(invisible_module_p))
	add_grammar_rules_function(LIST_1(LIST_2(Qproduct,LIST_2(Qquote,
		module_name))));
    goto next_loop;
  end_loop:;
    string_constant = 
	    STATIC_STRING("An attempt has been made to use GSI.  GSI has not been authorized to run on this machine.");
    string_constant_1 = 
	    STATIC_STRING("An attempt has been made to use GSPAN.  GSPAN has not been authorized to run on this machine.");
    string_constant_2 = 
	    STATIC_STRING("An attempt has been made to use ICP.  ICP has not been authorized to run on this machine.");
    string_constant_3 = 
	    STATIC_STRING("An attempt has been made to use GFI.  GFI has not been authorized to run on this machine.");
    string_constant_4 = 
	    STATIC_STRING("An attempt has been made to use KFEP.  KFEP has not been authorized to run on this machine.");
    string_constant_5 = 
	    STATIC_STRING("An attempt has been made to use CHINESE.  CHINESE has not been authorized to run on this machine.");
    string_constant_6 = 
	    STATIC_STRING("An attempt has been made to use RUNTIME-OPTION.  RUNTIME-OPTION has not been authorized to run on this machine.");
    string_constant_7 = 
	    STATIC_STRING("An attempt has been made to use JAPANESE.  JAPANESE has not been authorized to run on this machine.");
    string_constant_8 = 
	    STATIC_STRING("An attempt has been made to use NUPEC.  NUPEC has not been authorized to run on this machine.");
    string_constant_9 = 
	    STATIC_STRING("An attempt has been made to use RESTRICTED-USE-OPTION.  RESTRICTED-USE-OPTION has not been authorized to run on this machine.");
    string_constant_10 = 
	    STATIC_STRING("An attempt has been made to use EMBEDDED-OPTION.  EMBEDDED-OPTION has not been authorized to run on this machine.");
    string_constant_11 = 
	    STATIC_STRING("An attempt has been made to use KOREAN.  KOREAN has not been authorized to run on this machine.");
    string_constant_12 = 
	    STATIC_STRING("An attempt has been made to use G1.  G1 has not been authorized to run on this machine.");
    string_constant_13 = 
	    STATIC_STRING("An attempt has been made to use JL.  JL has not been authorized to run on this machine.");
    string_constant_14 = 
	    STATIC_STRING("An attempt has been made to use JP.  JP has not been authorized to run on this machine.");
    string_constant_15 = 
	    STATIC_STRING("An attempt has been made to use AL.  AL has not been authorized to run on this machine.");
    string_constant_16 = 
	    STATIC_STRING("An attempt has been made to use ENT.  ENT has not been authorized to run on this machine.");
    if (Pulse_rate_multiplier == UNBOUND)
	Pulse_rate_multiplier = FIX((SI_Long)1L);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    Qpulse_rate_options = STATIC_SYMBOL("PULSE-RATE-OPTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpulse_rate_options,Pulse_rate_options);
    Qsequences2 = STATIC_SYMBOL("SEQUENCES2",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qchoose_pulse_rate_multiplier = 
	    STATIC_SYMBOL("CHOOSE-PULSE-RATE-MULTIPLIER",AB_package);
    SET_SYMBOL_FUNCTION(Qchoose_pulse_rate_multiplier,
	    STATIC_FUNCTION(choose_pulse_rate_multiplier,NIL,FALSE,0,0));
    list_constant_9 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qchoose_pulse_rate_multiplier);
    record_system_variable(Qpulse_rate_options,Qsequences2,list_constant_9,
	    Qnil,Qnil,Qnil,Qnil);
    Qdevelopment = STATIC_SYMBOL("DEVELOPMENT",AB_package);
    Qdeployment = STATIC_SYMBOL("DEPLOYMENT",AB_package);
    Qrestricted_use_option = STATIC_SYMBOL("RESTRICTED-USE-OPTION",AB_package);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qbad_date_format = STATIC_SYMBOL("BAD-DATE-FORMAT",AB_package);
    string_constant_17 = STATIC_STRING("~a~a");
    Qruntime = STATIC_SYMBOL("RUNTIME",AB_package);
    Qrestricted = STATIC_SYMBOL("RESTRICTED",AB_package);
    Qembedded = STATIC_SYMBOL("EMBEDDED",AB_package);
    array_constant_37 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)4L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)5L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)15L,(SI_Long)57344L);
    list_constant_10 = STATIC_LIST((SI_Long)7L,Qnil,Qnil,Qnil,Qnil,Qnil,
	    Qnil,Qdeployment);
    list_constant_11 = STATIC_CONS(array_constant_37,list_constant_10);
    list_constant_12 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)2133228L),
	    FIX((SI_Long)6794277L),FIX((SI_Long)6819064L),
	    FIX((SI_Long)6805666L),FIX((SI_Long)764797L));
    list_constant_38 = STATIC_LIST((SI_Long)2L,list_constant_11,
	    list_constant_12);
    list_constant_13 = STATIC_CONS(Qdevelopment,Qnil);
    list_constant_14 = STATIC_LIST_STAR((SI_Long)7L,Qnil,Qnil,Qnil,Qnil,
	    Qnil,Qnil,list_constant_13);
    list_constant_15 = STATIC_CONS(array_constant_37,list_constant_14);
    list_constant_16 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)2832108L),
	    FIX((SI_Long)6794277L),FIX((SI_Long)6819064L),
	    FIX((SI_Long)6815394L),FIX((SI_Long)365801L));
    list_constant_39 = STATIC_LIST((SI_Long)2L,list_constant_15,
	    list_constant_16);
    array_constant_38 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)4L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)5L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)8L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)9L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)10L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)15L,(SI_Long)57344L);
    list_constant_17 = STATIC_CONS(array_constant_38,list_constant_10);
    list_constant_18 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)7631149L),
	    FIX((SI_Long)1167989L),FIX((SI_Long)1194458L),
	    FIX((SI_Long)1180380L),FIX((SI_Long)554244L));
    list_constant_40 = STATIC_LIST((SI_Long)2L,list_constant_17,
	    list_constant_18);
    list_constant_19 = STATIC_CONS(array_constant_38,list_constant_14);
    list_constant_20 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)6932269L),
	    FIX((SI_Long)1167989L),FIX((SI_Long)1194458L),
	    FIX((SI_Long)1170652L),FIX((SI_Long)657026L));
    list_constant_41 = STATIC_LIST((SI_Long)2L,list_constant_19,
	    list_constant_20);
    Qoct = STATIC_SYMBOL("OCT",AB_package);
    Qnov = STATIC_SYMBOL("NOV",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qquote,Qnov);
    list_constant_22 = STATIC_LIST_STAR((SI_Long)8L,array_constant_38,
	    FIX((SI_Long)1L),Qoct,FIX((SI_Long)1998L),FIX((SI_Long)24L),
	    list_constant_21,FIX((SI_Long)1998L),list_constant_13);
    list_constant_23 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)5947951L),
	    FIX((SI_Long)176383L),FIX((SI_Long)5729073L),
	    FIX((SI_Long)5134757L),FIX((SI_Long)653127L));
    list_constant_42 = STATIC_LIST((SI_Long)2L,list_constant_22,
	    list_constant_23);
    array_constant_39 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)7L,(SI_Long)57344L);
    list_constant_24 = STATIC_CONS(array_constant_39,list_constant_14);
    list_constant_25 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)6748523L),
	    FIX((SI_Long)6748523L),FIX((SI_Long)6780083L),
	    FIX((SI_Long)3433045L),FIX((SI_Long)128953L));
    list_constant_43 = STATIC_LIST((SI_Long)2L,list_constant_24,
	    list_constant_25);
    array_constant_40 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)2L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)3L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)57344L);
    list_constant_26 = STATIC_CONS(array_constant_40,list_constant_14);
    list_constant_27 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)6748523L),
	    FIX((SI_Long)6748523L),FIX((SI_Long)6779930L),
	    FIX((SI_Long)3433044L),FIX((SI_Long)837304L));
    list_constant_44 = STATIC_LIST((SI_Long)2L,list_constant_26,
	    list_constant_27);
    array_constant_41 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)57344L);
    list_constant_28 = STATIC_CONS(array_constant_41,list_constant_14);
    list_constant_29 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)6748522L),
	    FIX((SI_Long)6748523L),FIX((SI_Long)6780083L),
	    FIX((SI_Long)3431329L),FIX((SI_Long)608298L));
    list_constant_45 = STATIC_LIST((SI_Long)2L,list_constant_28,
	    list_constant_29);
    array_constant_42 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)7L,(SI_Long)57344L);
    list_constant_30 = STATIC_CONS(array_constant_42,list_constant_14);
    list_constant_31 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)6748369L),
	    FIX((SI_Long)6748369L),FIX((SI_Long)6779929L),
	    FIX((SI_Long)3431328L),FIX((SI_Long)113545L));
    list_constant_46 = STATIC_LIST((SI_Long)2L,list_constant_30,
	    list_constant_31);
    array_constant_43 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)2L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)7L,(SI_Long)57344L);
    list_constant_32 = STATIC_CONS(array_constant_43,list_constant_14);
    list_constant_33 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)6748369L),
	    FIX((SI_Long)6748369L),FIX((SI_Long)6780082L),
	    FIX((SI_Long)3431329L),FIX((SI_Long)312781L));
    list_constant_47 = STATIC_LIST((SI_Long)2L,list_constant_32,
	    list_constant_33);
    array_constant_44 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)2L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)3L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)4L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)5L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)7L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)8L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)10L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)11L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)15L,(SI_Long)57344L);
    list_constant_34 = STATIC_CONS(array_constant_44,list_constant_14);
    list_constant_35 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)6921994L),
	    FIX((SI_Long)1165169L),FIX((SI_Long)1185082L),
	    FIX((SI_Long)1168833L),FIX((SI_Long)200502L));
    list_constant_48 = STATIC_LIST((SI_Long)2L,list_constant_34,
	    list_constant_35);
    array_constant_45 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)2L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)3L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)4L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)5L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)7L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)8L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)9L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)10L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)11L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)15L,(SI_Long)57344L);
    list_constant_36 = STATIC_CONS(array_constant_45,list_constant_14);
    list_constant_37 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)6916610L),
	    FIX((SI_Long)1165444L),FIX((SI_Long)1185098L),
	    FIX((SI_Long)1168262L),FIX((SI_Long)805320L));
    list_constant_49 = STATIC_LIST((SI_Long)2L,list_constant_36,
	    list_constant_37);
    list_constant = STATIC_LIST((SI_Long)12L,list_constant_38,
	    list_constant_39,list_constant_40,list_constant_41,
	    list_constant_42,list_constant_43,list_constant_44,
	    list_constant_45,list_constant_46,list_constant_47,
	    list_constant_48,list_constant_49);
    Qall_is_well = STATIC_SYMBOL("ALL-IS-WELL",AB_package);
    Qno_end_date_supplied_with_start_date = 
	    STATIC_SYMBOL("NO-END-DATE-SUPPLIED-WITH-START-DATE",AB_package);
    Qwrong_data_structure_for_temporary_interval_information = 
	    STATIC_SYMBOL("WRONG-DATA-STRUCTURE-FOR-TEMPORARY-INTERVAL-INFORMATION",
	    AB_package);
    Qmissing_date_information = STATIC_SYMBOL("MISSING-DATE-INFORMATION",
	    AB_package);
    Qtemp_codes_end_before_they_start = 
	    STATIC_SYMBOL("TEMP-CODES-END-BEFORE-THEY-START",AB_package);
    Qtemp_codes_interval_has_ended = 
	    STATIC_SYMBOL("TEMP-CODES-INTERVAL-HAS-ENDED",AB_package);
    Qtemp_codes_interval_not_started = 
	    STATIC_SYMBOL("TEMP-CODES-INTERVAL-NOT-STARTED",AB_package);
    Qbad_codes = STATIC_SYMBOL("BAD-CODES",AB_package);
    Qok = STATIC_SYMBOL("OK",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_50 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qok,list_constant_50);
    string_constant_144 = STATIC_STRING("0");
    string_constant_145 = 
	    STATIC_STRING("1y4z8r83Ucy83Ucy839Xy839Xy00001m1l8l1m8p83Cky000004z8r83Gxy83Gxy839Xy839Xy00001m1l8l1m8p839py000004z8r83Kpy83Kpy839Xy839Xy00001m");
    string_constant_146 = 
	    STATIC_STRING("1l8l1m8p83Apy000004z8r83I3y83I3y839Xy839Xy00001m1l8l1m8p830iy000004z8r83I4y83I4y839Xy839Xy00001m1l8l1m8p830iy000004z8r83I5y83I5y");
    string_constant_147 = 
	    STATIC_STRING("839Xy839Xy00001m1l8l1m8p830iy000004z8r83I6y83I6y839Xy839Xy00001m1l8l1m8p830iy000004z8r83I7y83I7y839Xy839Xy00001m1l8l1m8p830iy000");
    string_constant_148 = 
	    STATIC_STRING("004z8r83X7y83X7y839Xy839Xy0k001m1l8l1l83Cy000004z8r83Ugy83Ugy839Xy839Xy00001m1l8l1m8p83Ky000004z8r83Gvy83Gvy839Xy839Xy00001m1l8l");
    string_constant_149 = 
	    STATIC_STRING("1m8p83Aqy000004z8r83Wty83Wty839Xy839Xy00001m1l8l1m8p83E4y000004z8r83Ury83Ury839Xy839Xy0k001m1l8l1m8p83*7y000004z8r83Usy83Usy839X");
    string_constant_150 = STATIC_STRING("y839Xy0k001m1l8l1m8p83*7y00000");
    string_constant_151 = 
	    STATIC_STRING("13Cy8q1m839Xy1l83-+y1o83Ucy08l1m8p83Cky1o83Gxy08l1m8p839py1o83Kpy08l1m8p83Apy1o83I3y08l1m8p830iy1o83I4y08l1m8p830iy1o83I5y08l1m8");
    string_constant_152 = 
	    STATIC_STRING("p830iy1o83I6y08l1m8p830iy1o83I7y08l1m8p830iy1o83X7yk8l83Cy1n83Ugy01m8p83Ky1o83Gvy08l1m8p83Aqy1o83Wty08l1m8p83E4y1o83Uryk8l1m8p83");
    string_constant_153 = STATIC_STRING("*7y1o83Usyk8l1m8p83*7y");
    temp = regenerate_optimized_constant(string_constant_144);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_145,
	    string_constant_146,string_constant_147,string_constant_148,
	    string_constant_149,string_constant_150));
    add_class_to_environment(9,Qok,list_constant_50,Nil,temp,Nil,temp_1,
	    list_constant_50,
	    regenerate_optimized_constant(LIST_3(string_constant_151,
	    string_constant_152,string_constant_153)),Nil);
    Ok_class_description = lookup_global_or_kb_specific_property_value(Qok,
	    Class_description_gkbprop);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)40L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)41L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)46L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)47L,(SI_Long)57344L);
    Qnon_negative_integer_or_none = 
	    STATIC_SYMBOL("NON-NEGATIVE-INTEGER-OR-NONE",AB_package);
    Qcompile_non_negative_integer_or_none_for_slot = 
	    STATIC_SYMBOL("COMPILE-NON-NEGATIVE-INTEGER-OR-NONE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_non_negative_integer_or_none_for_slot,
	    STATIC_FUNCTION(compile_non_negative_integer_or_none_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qnon_negative_integer_or_none,
	    SYMBOL_FUNCTION(Qcompile_non_negative_integer_or_none_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qnon_negative_integer_or_none,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_2 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_non_negative_integer_or_none_from_slot = 
	    STATIC_SYMBOL("WRITE-NON-NEGATIVE-INTEGER-OR-NONE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_non_negative_integer_or_none_from_slot,
	    STATIC_FUNCTION(write_non_negative_integer_or_none_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qnon_negative_integer_or_none,
	    SYMBOL_FUNCTION(Qwrite_non_negative_integer_or_none_from_slot),
	    Qslot_value_writer);
    string_constant_154 = STATIC_STRING("1m1m83-gxy83*7y1m83-gxy1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_154));
    Qauthorized_products = STATIC_SYMBOL("AUTHORIZED-PRODUCTS",AB_package);
    Qauthorized_optional_modules = 
	    STATIC_SYMBOL("AUTHORIZED-OPTIONAL-MODULES",AB_package);
    alias_slot_name(3,Qauthorized_products,Qauthorized_optional_modules,Qok);
    Qexpiration_date = STATIC_SYMBOL("EXPIRATION-DATE",AB_package);
    Qput_expiration_date_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-EXPIRATION-DATE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_expiration_date_where_slot_is_absent,
	    STATIC_FUNCTION(put_expiration_date_where_slot_is_absent,NIL,
	    FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qexpiration_date,
	    SYMBOL_FUNCTION(Qput_expiration_date_where_slot_is_absent),
	    Qabsent_slot_putter);
    if (Ok_modified == UNBOUND)
	Ok_modified = FIX((SI_Long)1L);
    if (Ok_authorized_products == UNBOUND)
	Ok_authorized_products = FIX((SI_Long)2L);
    if (Ok_expiration_date_qm == UNBOUND)
	Ok_expiration_date_qm = FIX((SI_Long)4L);
    if (Ok_authorized_packages == UNBOUND)
	Ok_authorized_packages = FIX((SI_Long)8L);
    if (Ok_make_g2_secure_qm == UNBOUND)
	Ok_make_g2_secure_qm = FIX((SI_Long)16L);
    if (Ok_number_of_processes_authorized == UNBOUND)
	Ok_number_of_processes_authorized = FIX((SI_Long)32L);
    if (Ok_maximum_number_of_concurrent_floating_telewindows_allowed == 
	    UNBOUND)
	Ok_maximum_number_of_concurrent_floating_telewindows_allowed = 
		FIX((SI_Long)64L);
    if (Ok_maximum_number_of_concurrent_floating_tw2_allowed == UNBOUND)
	Ok_maximum_number_of_concurrent_floating_tw2_allowed = 
		FIX((SI_Long)128L);
    string_constant_155 = 
	    STATIC_STRING("1m1m83Cky83-xy1m83Cky1o1m9k83-Yty1m9k83=Iy1m9k837Zy1m9k83-dPy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_155));
    Qid_or_whole_string_qm = STATIC_SYMBOL("ID-OR-WHOLE-STRING\?",AB_package);
    Qwrite_id_or_whole_string_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-ID-OR-WHOLE-STRING\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_id_or_whole_string_qm_from_slot,
	    STATIC_FUNCTION(write_id_or_whole_string_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qid_or_whole_string_qm,
	    SYMBOL_FUNCTION(Qwrite_id_or_whole_string_qm_from_slot),
	    Qslot_value_writer);
    Qauthorized_kb_packages = STATIC_SYMBOL("AUTHORIZED-KB-PACKAGES",
	    AB_package);
    Qcompile_id_or_whole_string_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-ID-OR-WHOLE-STRING\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_id_or_whole_string_qm_for_slot,
	    STATIC_FUNCTION(compile_id_or_whole_string_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qid_or_whole_string_qm,
	    SYMBOL_FUNCTION(Qcompile_id_or_whole_string_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qid_or_whole_string_qm,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qmachine_id = STATIC_SYMBOL("MACHINE-ID",AB_package);
    Qput_machine_id = STATIC_SYMBOL("PUT-MACHINE-ID",AB_package);
    SET_SYMBOL_FUNCTION(Qput_machine_id,STATIC_FUNCTION(put_machine_id,NIL,
	    FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qmachine_id,SYMBOL_FUNCTION(Qput_machine_id),
	    Qslot_putter);
    Qcode_1 = STATIC_SYMBOL("CODE-1",AB_package);
    Qput_code_1 = STATIC_SYMBOL("PUT-CODE-1",AB_package);
    SET_SYMBOL_FUNCTION(Qput_code_1,STATIC_FUNCTION(put_code_1,NIL,FALSE,3,3));
    mutate_global_property(Qcode_1,SYMBOL_FUNCTION(Qput_code_1),Qslot_putter);
    Qcode_2 = STATIC_SYMBOL("CODE-2",AB_package);
    Qput_code_2 = STATIC_SYMBOL("PUT-CODE-2",AB_package);
    SET_SYMBOL_FUNCTION(Qput_code_2,STATIC_FUNCTION(put_code_2,NIL,FALSE,3,3));
    mutate_global_property(Qcode_2,SYMBOL_FUNCTION(Qput_code_2),Qslot_putter);
    Qcode_3 = STATIC_SYMBOL("CODE-3",AB_package);
    Qput_code_3 = STATIC_SYMBOL("PUT-CODE-3",AB_package);
    SET_SYMBOL_FUNCTION(Qput_code_3,STATIC_FUNCTION(put_code_3,NIL,FALSE,3,3));
    mutate_global_property(Qcode_3,SYMBOL_FUNCTION(Qput_code_3),Qslot_putter);
    Qcode_4 = STATIC_SYMBOL("CODE-4",AB_package);
    Qput_code_4 = STATIC_SYMBOL("PUT-CODE-4",AB_package);
    SET_SYMBOL_FUNCTION(Qput_code_4,STATIC_FUNCTION(put_code_4,NIL,FALSE,3,3));
    mutate_global_property(Qcode_4,SYMBOL_FUNCTION(Qput_code_4),Qslot_putter);
    Qcode_5 = STATIC_SYMBOL("CODE-5",AB_package);
    Qok_slot_coordinator = STATIC_SYMBOL("OK-SLOT-COORDINATOR",AB_package);
    Qput_code_5 = STATIC_SYMBOL("PUT-CODE-5",AB_package);
    SET_SYMBOL_FUNCTION(Qput_code_5,STATIC_FUNCTION(put_code_5,NIL,FALSE,3,3));
    mutate_global_property(Qcode_5,SYMBOL_FUNCTION(Qput_code_5),Qslot_putter);
    Qput_authorized_products = STATIC_SYMBOL("PUT-AUTHORIZED-PRODUCTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_authorized_products,
	    STATIC_FUNCTION(put_authorized_products,NIL,FALSE,3,3));
    mutate_global_property(Qauthorized_products,
	    SYMBOL_FUNCTION(Qput_authorized_products),Qslot_putter);
    Qexpiration_date_qm = STATIC_SYMBOL("EXPIRATION-DATE\?",AB_package);
    Qput_expiration_date_qm = STATIC_SYMBOL("PUT-EXPIRATION-DATE\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_expiration_date_qm,
	    STATIC_FUNCTION(put_expiration_date_qm,NIL,FALSE,3,3));
    mutate_global_property(Qexpiration_date_qm,
	    SYMBOL_FUNCTION(Qput_expiration_date_qm),Qslot_putter);
    Qmake_g2_secure_qm = STATIC_SYMBOL("MAKE-G2-SECURE\?",AB_package);
    Qput_make_g2_secure_qm = STATIC_SYMBOL("PUT-MAKE-G2-SECURE\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_make_g2_secure_qm,
	    STATIC_FUNCTION(put_make_g2_secure_qm,NIL,FALSE,3,3));
    mutate_global_property(Qmake_g2_secure_qm,
	    SYMBOL_FUNCTION(Qput_make_g2_secure_qm),Qslot_putter);
    Qput_ok_slot_coordinator = STATIC_SYMBOL("PUT-OK-SLOT-COORDINATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_ok_slot_coordinator,
	    STATIC_FUNCTION(put_ok_slot_coordinator,NIL,FALSE,3,3));
    mutate_global_property(Qok_slot_coordinator,
	    SYMBOL_FUNCTION(Qput_ok_slot_coordinator),Qslot_putter);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_156 = 
	    STATIC_STRING("1q1m839py83-kWy1m839py1m9k83Zy1m83-kWy83-9Sy1o83-kWy1n83-9Sy1m9k83vy83-kWy1nmln9l1m83-hEy1m9k83-Foy1m83-hEy83-ey");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_156));
    Qproducts_qm = STATIC_SYMBOL("PRODUCTS\?",AB_package);
    Qcompile_products_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-PRODUCTS\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_products_qm_for_slot,
	    STATIC_FUNCTION(compile_products_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qproducts_qm,
	    SYMBOL_FUNCTION(Qcompile_products_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qproducts_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_products_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-PRODUCTS\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_products_qm_from_slot,
	    STATIC_FUNCTION(write_products_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qproducts_qm,
	    SYMBOL_FUNCTION(Qwrite_products_qm_from_slot),Qslot_value_writer);
    Qnumber_or_unlimited = STATIC_SYMBOL("NUMBER-OR-UNLIMITED",AB_package);
    Qwrite_number_or_unlimited_from_slot = 
	    STATIC_SYMBOL("WRITE-NUMBER-OR-UNLIMITED-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_number_or_unlimited_from_slot,
	    STATIC_FUNCTION(write_number_or_unlimited_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qnumber_or_unlimited,
	    SYMBOL_FUNCTION(Qwrite_number_or_unlimited_from_slot),
	    Qslot_value_writer);
    N_1_2_version = LIST_2(FIX((SI_Long)1L),FIX((SI_Long)2L));
    N_4_0_version = LIST_2(FIX((SI_Long)4L),FIX((SI_Long)0L));
    Qjan_1_1990 = STATIC_SYMBOL("JAN-1-1990",AB_package);
    SET_SYMBOL_VALUE(Qjan_1_1990,FIX((SI_Long)32872L));
    Qjan_1_1998 = STATIC_SYMBOL("JAN-1-1998",AB_package);
    SET_SYMBOL_VALUE(Qjan_1_1998,FIX((SI_Long)35794L));
    Qjan_1_1999 = STATIC_SYMBOL("JAN-1-1999",AB_package);
    SET_SYMBOL_VALUE(Qjan_1_1999,FIX((SI_Long)36159L));
    Qjan_1_2006 = STATIC_SYMBOL("JAN-1-2006",AB_package);
    SET_SYMBOL_VALUE(Qjan_1_2006,FIX((SI_Long)38716L));
    Qjan_1_2009 = STATIC_SYMBOL("JAN-1-2009",AB_package);
    SET_SYMBOL_VALUE(Qjan_1_2009,FIX((SI_Long)39812L));
    Qjan_1_2015 = STATIC_SYMBOL("JAN-1-2015",AB_package);
    SET_SYMBOL_VALUE(Qjan_1_2015,FIX((SI_Long)42003L));
    if (Reference_date_for_interval_encoding == UNBOUND)
	Reference_date_for_interval_encoding = Jan_1_2015;
    Qnil_function = STATIC_SYMBOL("NIL-FUNCTION",AB_package);
    string_constant_157 = 
	    STATIC_STRING("1n1m83Apy8355y1o83Apy1m9k83Zy09l1n83Apy1o1m9k832+y8355y1m9k83=3y8355y2lmo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnil_function);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_157));
    string_constant_18 = STATIC_STRING("none");
    string_constant_19 = STATIC_STRING("from ");
    string_constant_20 = STATIC_STRING(" to ");
    Qauthorization_interval_qm = STATIC_SYMBOL("AUTHORIZATION-INTERVAL\?",
	    AB_package);
    Qwrite_authorization_interval_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-AUTHORIZATION-INTERVAL\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_authorization_interval_qm_from_slot,
	    STATIC_FUNCTION(write_authorization_interval_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qauthorization_interval_qm,
	    SYMBOL_FUNCTION(Qwrite_authorization_interval_qm_from_slot),
	    Qslot_value_writer);
    if (Floating_telewindows_limit == UNBOUND)
	Floating_telewindows_limit = FIX((SI_Long)0L);
    if (Floating_tw2_limit == UNBOUND)
	Floating_tw2_limit = FIX((SI_Long)0L);
    Qfloating = STATIC_SYMBOL("FLOATING",AB_package);
    Qui_client_session = STATIC_SYMBOL("UI-CLIENT-SESSION",AB_package);
    if (Free_floater_allowed_qm == UNBOUND)
	Free_floater_allowed_qm = Nil;
    Qunauthorized = STATIC_SYMBOL("UNAUTHORIZED",AB_package);
    Qno_available_floating_licenses = 
	    STATIC_SYMBOL("NO-AVAILABLE-FLOATING-LICENSES",AB_package);
    Qtelewindows_license_level = STATIC_SYMBOL("TELEWINDOWS-LICENSE-LEVEL",
	    AB_package);
    Qctlc_cons_count = STATIC_SYMBOL("CTLC-CONS-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qctlc_cons_count,Ctlc_cons_count);
    record_system_variable(Qctlc_cons_count,Qsequences2,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_t2_nonce_data_g2_struct = 
	    STATIC_SYMBOL("T2-NONCE-DATA-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qt2_nonce_data = STATIC_SYMBOL("T2-NONCE-DATA",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_t2_nonce_data_g2_struct,
	    Qt2_nonce_data,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qt2_nonce_data,
	    Qg2_defstruct_structure_name_t2_nonce_data_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_t2_nonce_data == UNBOUND)
	The_type_description_of_t2_nonce_data = Nil;
    string_constant_158 = 
	    STATIC_STRING("43Dy8m83ndy1n83ndy8n8k1l8n0000000kqk0k0");
    temp = The_type_description_of_t2_nonce_data;
    The_type_description_of_t2_nonce_data = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_158));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_t2_nonce_data_g2_struct,
	    The_type_description_of_t2_nonce_data,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qt2_nonce_data,
	    The_type_description_of_t2_nonce_data,Qtype_description_of_type);
    Qoutstanding_t2_nonce_data_count = 
	    STATIC_SYMBOL("OUTSTANDING-T2-NONCE-DATA-COUNT",AB_package);
    Qt2_nonce_data_structure_memory_usage = 
	    STATIC_SYMBOL("T2-NONCE-DATA-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_159 = STATIC_STRING("1q83ndy8s83-rty09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_t2_nonce_data_count);
    push_optimized_constant(Qt2_nonce_data_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_159));
    Qchain_of_available_t2_nonce_datas = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-T2-NONCE-DATAS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_t2_nonce_datas,
	    Chain_of_available_t2_nonce_datas);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_t2_nonce_datas,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qt2_nonce_data_count = STATIC_SYMBOL("T2-NONCE-DATA-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qt2_nonce_data_count,T2_nonce_data_count);
    record_system_variable(Qt2_nonce_data_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_t2_nonce_datas_vector == UNBOUND)
	Chain_of_available_t2_nonce_datas_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qt2_nonce_data_structure_memory_usage,
	    STATIC_FUNCTION(t2_nonce_data_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_t2_nonce_data_count,
	    STATIC_FUNCTION(outstanding_t2_nonce_data_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_t2_nonce_data_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_t2_nonce_data,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qt2_nonce_data,
	    reclaim_structure_for_t2_nonce_data_1);
    Qnot_allocated = STATIC_SYMBOL("NOT-ALLOCATED",AB_package);
    Qmutate_t2_nonce_hash_tree_entry = 
	    STATIC_SYMBOL("MUTATE-T2-NONCE-HASH-TREE-ENTRY",AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_t2_nonce_hash_tree_entry,
	    STATIC_FUNCTION(mutate_t2_nonce_hash_tree_entry,NIL,FALSE,3,3));
    Fp_mutate_t2_nonce_hash_tree_entry = 
	    SYMBOL_FUNCTION(Qmutate_t2_nonce_hash_tree_entry);
    Qstring_eq_w = STATIC_SYMBOL("STRING=W",AB_package);
    SET_SYMBOL_FUNCTION(Qstring_eq_w,STATIC_FUNCTION(string_eq_w,NIL,FALSE,
	    2,2));
    Qt2_nonce_hash = STATIC_SYMBOL("T2-NONCE-HASH",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    if (T2_nonce_table == UNBOUND) {
	new_cons = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_2 = Available_lookup_conses_vector;
	    temp_3 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_2,temp_3) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_lookup_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol) = Qt2_nonce_hash;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qlookup);
	T2_nonce_table = gensymed_symbol;
    }
    Qlogin_not_yet_attempted = STATIC_SYMBOL("LOGIN-NOT-YET-ATTEMPTED",
	    AB_package);
    Qlogged_in = STATIC_SYMBOL("LOGGED-IN",AB_package);
    Qui_client_session_nonce = STATIC_SYMBOL("UI-CLIENT-SESSION-NONCE",
	    AB_package);
    Qno_entry_for_this_nonce = STATIC_SYMBOL("NO-ENTRY-FOR-THIS-NONCE",
	    AB_package);
    Qlogged_out = STATIC_SYMBOL("LOGGED-OUT",AB_package);
    Qtoo_many_login_attempts = STATIC_SYMBOL("TOO-MANY-LOGIN-ATTEMPTS",
	    AB_package);
    Qnonce_is_not_a_string = STATIC_SYMBOL("NONCE-IS-NOT-A-STRING",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    Qonly_one_named_connection_per_client = 
	    STATIC_SYMBOL("ONLY-ONE-NAMED-CONNECTION-PER-CLIENT",AB_package);
    Qalready_failed_self_authorization = 
	    STATIC_SYMBOL("ALREADY-FAILED-SELF-AUTHORIZATION",AB_package);
    Qundefined_license_level_requested = 
	    STATIC_SYMBOL("UNDEFINED-LICENSE-LEVEL-REQUESTED",AB_package);
    Qincompatible_license_level_no_floaters = 
	    STATIC_SYMBOL("INCOMPATIBLE-LICENSE-LEVEL-NO-FLOATERS",AB_package);
    Qincompatible_license_level = 
	    STATIC_SYMBOL("INCOMPATIBLE-LICENSE-LEVEL",AB_package);
    if (Relations_tag_list == UNBOUND)
	Relations_tag_list = Nil;
    Qg2_is_secure = STATIC_SYMBOL("G2-IS-SECURE",AB_package);
    temp_2 = CONS(Qg2_is_secure,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    Qserver_parameters = STATIC_SYMBOL("SERVER-PARAMETERS",AB_package);
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qserver_parameters),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qg2_is_secure,temp);
    set_property_value_function(get_symbol_properties_function(Qserver_parameters),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qab_class,Qserver_parameters);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qinitial_g2_is_secure = STATIC_SYMBOL("INITIAL-G2-IS-SECURE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_g2_is_secure,
	    STATIC_FUNCTION(initial_g2_is_secure,NIL,FALSE,1,1));
    Qget_g2_is_secure = STATIC_SYMBOL("GET-G2-IS-SECURE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_g2_is_secure,STATIC_FUNCTION(get_g2_is_secure,
	    NIL,FALSE,1,1));
    add_virtual_attribute(Qg2_is_secure,list_constant_51,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qinitial_g2_is_secure),
	    SYMBOL_FUNCTION(Qget_g2_is_secure),Nil);
    string_constant_160 = 
	    STATIC_STRING("1m1m83E4y83-ey1o83E4y1m1m9k83=Ty1m9k83-cey09l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnil_function);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_160));
    array_constant_4 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)57344L);
    Qnumber_of_processes = STATIC_SYMBOL("NUMBER-OF-PROCESSES",AB_package);
    Qcompile_number_of_processes_for_slot = 
	    STATIC_SYMBOL("COMPILE-NUMBER-OF-PROCESSES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_number_of_processes_for_slot,
	    STATIC_FUNCTION(compile_number_of_processes_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qnumber_of_processes,
	    SYMBOL_FUNCTION(Qcompile_number_of_processes_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qnumber_of_processes,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_21 = STATIC_STRING("no limit");
    Qwrite_number_of_processes_from_slot = 
	    STATIC_SYMBOL("WRITE-NUMBER-OF-PROCESSES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_number_of_processes_from_slot,
	    STATIC_FUNCTION(write_number_of_processes_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qnumber_of_processes,
	    SYMBOL_FUNCTION(Qwrite_number_of_processes_from_slot),
	    Qslot_value_writer);
    Qnumber_of_processes_authorized = 
	    STATIC_SYMBOL("NUMBER-OF-PROCESSES-AUTHORIZED",AB_package);
    Qput_number_of_processes_authorized = 
	    STATIC_SYMBOL("PUT-NUMBER-OF-PROCESSES-AUTHORIZED",AB_package);
    SET_SYMBOL_FUNCTION(Qput_number_of_processes_authorized,
	    STATIC_FUNCTION(put_number_of_processes_authorized,NIL,FALSE,3,3));
    mutate_global_property(Qnumber_of_processes_authorized,
	    SYMBOL_FUNCTION(Qput_number_of_processes_authorized),Qslot_putter);
    Qmaximum_number_of_concurrent_floating_telewindows_allowed = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-CONCURRENT-FLOATING-TELEWINDOWS-ALLOWED",
	    AB_package);
    Qput_maximum_number_of_concurrent_floating_telewindows_allowed = 
	    STATIC_SYMBOL("PUT-MAXIMUM-NUMBER-OF-CONCURRENT-FLOATING-TELEWINDOWS-ALLOWED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_maximum_number_of_concurrent_floating_telewindows_allowed,
	    STATIC_FUNCTION(put_maximum_number_of_concurrent_floating_telewindows_allowed,
	    NIL,FALSE,3,3));
    mutate_global_property(Qmaximum_number_of_concurrent_floating_telewindows_allowed,
	    SYMBOL_FUNCTION(Qput_maximum_number_of_concurrent_floating_telewindows_allowed),
	    Qslot_putter);
    string_constant_161 = 
	    STATIC_STRING("1n1n83Aqy83q0y1ll1n83Aqy1n83q0y1m9k83-Zy83Aqy2lln1o83Aqy1m9k83Zyl9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnil_function);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_161));
    string_constant_162 = 
	    STATIC_STRING("1m1n83q0y1o839cy83-iAy83-iAy83-iAy1olmno1n83q0y1t839cy1m9k832+y8355y1m9k83=3y8355y1m9k83vy83-iAy83-iAy83-iAy1qlrstnp");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_162));
    string_constant_163 = STATIC_STRING("1l1m839cy83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_163));
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_163));
    string_constant_22 = STATIC_STRING("~(~a~) ");
    string_constant_23 = STATIC_STRING(",");
    string_constant_24 = STATIC_STRING(" ~d ~d ~d");
    string_constant_25 = STATIC_STRING(";~%");
    Qauthorized_packages = STATIC_SYMBOL("AUTHORIZED-PACKAGES",AB_package);
    Qwrite_authorized_packages_from_slot = 
	    STATIC_SYMBOL("WRITE-AUTHORIZED-PACKAGES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_authorized_packages_from_slot,
	    STATIC_FUNCTION(write_authorized_packages_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qauthorized_packages,
	    SYMBOL_FUNCTION(Qwrite_authorized_packages_from_slot),
	    Qslot_value_writer);
    array_constant_6 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)36L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)42L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)46L,(SI_Long)43L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)47L,(SI_Long)57344L);
    Qcompile_authorized_packages_for_slot = 
	    STATIC_SYMBOL("COMPILE-AUTHORIZED-PACKAGES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_authorized_packages_for_slot,
	    STATIC_FUNCTION(compile_authorized_packages_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qauthorized_packages,
	    SYMBOL_FUNCTION(Qcompile_authorized_packages_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qauthorized_packages,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qbad_package_authorization = STATIC_SYMBOL("BAD-PACKAGE-AUTHORIZATION",
	    AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant_26 = 
	    STATIC_STRING("the following packages have invalid authorization codes: ");
    string_constant_27 = STATIC_STRING("~(~a~)");
    string_constant_28 = STATIC_STRING(", ");
    write_bad_package_authorization_note_1 = 
	    STATIC_FUNCTION(write_bad_package_authorization_note,NIL,FALSE,
	    2,2);
    mutate_global_property(Qbad_package_authorization,
	    write_bad_package_authorization_note_1,Qframe_note_writer_1);
    Qput_authorized_kb_packages = 
	    STATIC_SYMBOL("PUT-AUTHORIZED-KB-PACKAGES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_authorized_kb_packages,
	    STATIC_FUNCTION(put_authorized_kb_packages,NIL,FALSE,3,3));
    mutate_global_property(Qauthorized_kb_packages,
	    SYMBOL_FUNCTION(Qput_authorized_kb_packages),Qslot_putter);
    Qconsider_asian_language_initializations_qm = 
	    STATIC_SYMBOL("CONSIDER-ASIAN-LANGUAGE-INITIALIZATIONS\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconsider_asian_language_initializations_qm,
	    Consider_asian_language_initializations_qm);
    record_system_variable(Qconsider_asian_language_initializations_qm,
	    Qsequences2,T,Qnil,Qnil,Qnil,Qnil);
    array_constant_11 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    if (Text_representation_of_our_ok_object == UNBOUND)
	Text_representation_of_our_ok_object = array_constant_11;
    if (Authorized_products_of_this_machine == UNBOUND)
	Authorized_products_of_this_machine = Nil;
    Qusing_g2_ok_file_message = STATIC_SYMBOL("USING-G2-OK-FILE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qusing_g2_ok_file_message,
	    Using_g2_ok_file_message);
    array_constant_46 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)2L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)3L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)4L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)5L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)6L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)8L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)9L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)10L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)14L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)15L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)22L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)23L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)24L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)31L,(SI_Long)57344L);
    string_constant_164 = 
	    STATIC_STRING("43Ly4npsv4k4lr4k4k4k4l3Cy4lq4lu4lt4lk4k4k4lz4lw4lo4k4mmx4ly4ln4ll4k4k4k4k");
    SET_SYMBOL_VALUE(Qusing_g2_ok_file_message,
	    transform_type_specification_2(FIX((SI_Long)17L),
	    array_constant_46,
	    regenerate_optimized_constant(string_constant_164)));
    Qok_to_run_g2_message = STATIC_SYMBOL("OK-TO-RUN-G2-MESSAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qok_to_run_g2_message,Ok_to_run_g2_message);
    array_constant_47 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)1L,(SI_Long)33L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)2L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)3L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)4L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)5L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)6L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)8L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)9L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)10L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)14L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)22L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)23L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)24L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)25L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)31L,(SI_Long)57344L);
    string_constant_165 = 
	    STATIC_STRING("43My4qmptwz3Fy4l3Iy4k4l3Hy4k4k4k4l3Gy4lk4lv4lu4k4k4k4k4ln4mq3Ey4mry4l3Cy4lo4mlx4l3Dy4k4ls4k4k");
    SET_SYMBOL_VALUE(Qok_to_run_g2_message,
	    transform_type_specification_2(FIX((SI_Long)23L),
	    array_constant_47,
	    regenerate_optimized_constant(string_constant_165)));
    Qshould_save_ok_file_message = 
	    STATIC_SYMBOL("SHOULD-SAVE-OK-FILE-MESSAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qshould_save_ok_file_message,
	    Should_save_ok_file_message);
    array_constant_48 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)2L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)5L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)6L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)7L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)8L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)9L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)10L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)11L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)12L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)20L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)22L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)25L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)27L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)29L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)30L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)31L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)32L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)33L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)34L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)35L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)39L,(SI_Long)57344L);
    string_constant_166 = 
	    STATIC_STRING("43Wy4l3hy43Eynuy3Fy3Jy3Ny3Qy3ay3fy3iy3jy3ky3ny3vy3-+y3-0y3-8y3-By4m3oy3uy4m3ry3-Ly4k4m3qy3-Ay4k4k4k4l3-9y4l3Py4l3Oy4lk4o3Cy3cy3l");
    string_constant_167 = 
	    STATIC_STRING("y3-4y4l3-Gy4ot3Xy3-1y3-Cy4l3by4s3Ey3My3Wy3Zy3ey3-=y3-2y3-Fy4l3-3y4m3Yy3py4np3Ly3-*y4rlqw3Gy3Ty3sy3-Iy4m3Ry3ty4m3wy3-Dy4nv3Sy3xy4");
    string_constant_168 = 
	    STATIC_STRING("ns3Vy3-6y4m3-Ey3-Jy4ooz3dy3my4p3Iy3Ky3--y3-7y3-Hy4omr3Hy3-5y4mx3Uy4l3Dy4l3-Ky4k4k4l3gy");
    SET_SYMBOL_VALUE(Qshould_save_ok_file_message,
	    transform_type_specification_2(FIX((SI_Long)90L),
	    array_constant_48,
	    regenerate_optimized_constant(LIST_3(string_constant_166,
	    string_constant_167,string_constant_168))));
    Qshould_create_users_and_then_save_ok_file_message_format_control_string 
	    = 
	    STATIC_SYMBOL("SHOULD-CREATE-USERS-AND-THEN-SAVE-OK-FILE-MESSAGE-FORMAT-CONTROL-STRING",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qshould_create_users_and_then_save_ok_file_message_format_control_string,
	    Should_create_users_and_then_save_ok_file_message_format_control_string);
    array_constant_49 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)1L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)2L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)3L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)9L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)11L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)12L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)13L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)23L,(SI_Long)57344L);
    string_constant_169 = 
	    STATIC_STRING("4y4k4k4k4k4nlnp4k4k4k4k4nkmo4k4k4k4k");
    SET_SYMBOL_VALUE(Qshould_create_users_and_then_save_ok_file_message_format_control_string,
	    transform_type_specification_2(FIX((SI_Long)6L),
	    array_constant_49,
	    regenerate_optimized_constant(string_constant_169)));
    Qshould_create_users_and_then_save_ok_file_message_1 = 
	    STATIC_SYMBOL("SHOULD-CREATE-USERS-AND-THEN-SAVE-OK-FILE-MESSAGE-1",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qshould_create_users_and_then_save_ok_file_message_1,
	    Should_create_users_and_then_save_ok_file_message_1);
    array_constant_50 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)1L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)2L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)5L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)6L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)7L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)8L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)9L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)10L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)11L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)12L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)13L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)14L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)16L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)17L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)18L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)20L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)22L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)24L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)26L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)27L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)28L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)31L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)32L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)35L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)36L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)37L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)38L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)39L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)46L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)47L,(SI_Long)57344L);
    string_constant_170 = 
	    STATIC_STRING("43ay43Gysx3Jy3My3Ty3Zy3cy3ky3oy3ty3wy3-*y3-1y3-Cy3-Iy3-Ny3-Uy3-fy3-jy3-oy4l3Hy4n3jy3-Ty3-ey4l3-uy4k4l3by4k4k4k4lr4mq3ay4l3vy4lo4");
    string_constant_171 = 
	    STATIC_STRING("ll4m3Ly3uy4mnp4l3Ky4lm4lk4rz3Vy3-+y3-2y3-Py3-Wy3-gy4m3Oy3ly4n3Cy3Ry3fy4o3-By3-cy3-iy3-ry4u3Gy3Qy3Xy3ey3iy3-Ay3-Fy3-Ry3-my3-sy4qu");
    string_constant_172 = 
	    STATIC_STRING("3Dy3qy3xy3-5y3-My4pv3Ey3ry3-8y3-Ky4l3Py4l3Wy4oy3Uy3-Qy3-py4o3Fy3-=y3-Oy3-hy4p3Ny3-0y3-6y3-ay3-qy4l3-Vy4p3hy3-7y3-Gy3-by3-ny4yw3I");
    string_constant_173 = 
	    STATIC_STRING("y3Yy3dy3sy3--y3-Ey3-Hy3-Sy3-Xy3-Yy3-dy3-ly3-ty4qt3Sy3ny3py3-4y3-Ly4p3gy3my3-3y3-Dy3-ky4k4m3-Jy3-Zy4l3-9y4k");
    SET_SYMBOL_VALUE(Qshould_create_users_and_then_save_ok_file_message_1,
	    transform_type_specification_2(FIX((SI_Long)125L),
	    array_constant_50,
	    regenerate_optimized_constant(LIST_4(string_constant_170,
	    string_constant_171,string_constant_172,string_constant_173))));
    Qshould_create_users_and_then_save_ok_file_message_2 = 
	    STATIC_SYMBOL("SHOULD-CREATE-USERS-AND-THEN-SAVE-OK-FILE-MESSAGE-2",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qshould_create_users_and_then_save_ok_file_message_2,
	    Should_create_users_and_then_save_ok_file_message_2);
    array_constant_51 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)2L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)3L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)4L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)5L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)6L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)8L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)9L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)10L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)12L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)16L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)25L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)26L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)27L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)28L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)29L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)30L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)39L,(SI_Long)57344L);
    string_constant_174 = 
	    STATIC_STRING("43Ry4xkmpty3Fy3Iy3Ny3Ty3Xy3ay3hy3ky4l3ry4k4lo4k4k4k4ll4ln4l3Hy4l3Gy4m3dy3ly4n3Yy3ey3iy4k4l3Sy4o3My3Zy3gy3qy4l3Jy4mx3Cy4nv3Dy3Ky4");
    string_constant_175 = 
	    STATIC_STRING("n3Ly3Ry3fy4os3Uy3my3py4n3Py3Vy3oy4lq4m3Ey3cy4nwz3Wy4nr3Qy3by4k4mu3Oy4k4m3jy3ny4k");
    SET_SYMBOL_VALUE(Qshould_create_users_and_then_save_ok_file_message_2,
	    transform_type_specification_2(FIX((SI_Long)58L),
	    array_constant_51,
	    regenerate_optimized_constant(LIST_2(string_constant_174,
	    string_constant_175))));
    Qshould_create_users_and_then_save_ok_file_message_3 = 
	    STATIC_SYMBOL("SHOULD-CREATE-USERS-AND-THEN-SAVE-OK-FILE-MESSAGE-3",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qshould_create_users_and_then_save_ok_file_message_3,
	    Should_create_users_and_then_save_ok_file_message_3);
    array_constant_52 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)1L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)2L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)5L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)6L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)8L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)9L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)10L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)11L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)12L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)13L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)15L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)17L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)24L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)25L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)26L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)29L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)30L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)33L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)34L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)35L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)36L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)37L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)38L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)47L,(SI_Long)57344L);
    string_constant_176 = 
	    STATIC_STRING("43Zy43Pykry3Ly3Ry3Uy3cy3iy3my3ry3-1y3-Ay3-Jy3-My3-Uy3-Yy3-dy3-iy3-my3-qy3-ty3*1y3*6y3*9y3*Hy3*Ky3*Oy3*Wy3*Zy4m3*Ay3*Gy4m3by3-Ty4");
    string_constant_177 = 
	    STATIC_STRING("m3*Dy3*jy4k4m3*Cy3*Yy4k4m3-Ny3*Xy4k4k4l3-sy4l3sy4l3-ry4ml3-2y4wovz3Sy3ty3--y3-3y3-Vy3-fy3*3y3*7y3*Sy4l3ny4m3-Ky3*2y4ns3-=y3*ey4t");
    string_constant_178 = 
	    STATIC_STRING("3Ky3Yy3ay3-9y3-Iy3-Xy3**y3*Py3*ay43Kynqux3Jy3Oy3Wy3Xy3Zy3ly3qy3xy3-0y3-Hy3-Oy3-by3-hy3-py3*-y3*0y3*5y3*Ny3*Qy3*dy4l3*Ry4n3hy3*=y");
    string_constant_179 = 
	    STATIC_STRING("3*By4p3Ey3ky3-ay3-oy3*My4r3Hy3fy3oy3uy3-Gy3*Iy3*by4m3-uy3*Fy4om3-Fy3*+y3*Uy4l3-Sy4u3Vy3gy3vy3-+y3-*y3-Py3-Wy3-cy3-vy3*Jy4q3Fy3-7");
    string_constant_180 = 
	    STATIC_STRING("y3-jy3-wy3*Ey3*gy4m3-Dy3-Ey4qt3Gy3Py3-8y3*cy3*hy4wp3Ny3Qy3Ty3ey3-4y3-5y3-By3-Qy3-ey3*4y3*8y4vw3Dy3jy3py3wy3-Zy3-ly3-ny3*Ly3*Vy3*");
    string_constant_181 = 
	    STATIC_STRING("fy4q3Cy3My3dy3-Cy3-ky3*Ty4l3-gy4m3-6y3-xy4k4n3-Ly3-Ry3*iy4l3Iy");
    SET_SYMBOL_VALUE(Qshould_create_users_and_then_save_ok_file_message_3,
	    transform_type_specification_2(FIX((SI_Long)178L),
	    array_constant_52,regenerate_optimized_constant(list(6,
	    string_constant_176,string_constant_177,string_constant_178,
	    string_constant_179,string_constant_180,string_constant_181))));
    Qcan_create_additional_users_and_then_save_ok_file_message_format_control_string 
	    = 
	    STATIC_SYMBOL("CAN-CREATE-ADDITIONAL-USERS-AND-THEN-SAVE-OK-FILE-MESSAGE-FORMAT-CONTROL-STRING",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcan_create_additional_users_and_then_save_ok_file_message_format_control_string,
	    Can_create_additional_users_and_then_save_ok_file_message_format_control_string);
    array_constant_53 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)1L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)2L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)3L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)10L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)11L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)12L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)13L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)23L,(SI_Long)57344L);
    string_constant_182 = STATIC_STRING("4y4k4k4k4k4mln4k4k4k4k4k4mkm4k4k4k");
    SET_SYMBOL_VALUE(Qcan_create_additional_users_and_then_save_ok_file_message_format_control_string,
	    transform_type_specification_2(FIX((SI_Long)4L),
	    array_constant_53,
	    regenerate_optimized_constant(string_constant_182)));
    Qcan_create_additional_users_and_then_save_ok_file_message_1 = 
	    STATIC_SYMBOL("CAN-CREATE-ADDITIONAL-USERS-AND-THEN-SAVE-OK-FILE-MESSAGE-1",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcan_create_additional_users_and_then_save_ok_file_message_1,
	    Can_create_additional_users_and_then_save_ok_file_message_1);
    array_constant_54 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)1L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)4L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)5L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)8L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)9L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)10L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)12L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)13L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)14L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)15L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)19L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)20L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)21L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)28L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)29L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)30L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)39L,(SI_Long)57344L);
    string_constant_183 = 
	    STATIC_STRING("43Ry4rpu3Gy3Jy3Qy3Wy3Zy4l3Ey4l3gy4k4l3Yy4k4mw3Sy4nx3Oy3cy4l3Xy4lk4k4l3Ly4k4lo4l3Hy4l3Iy4qn3Dy3Ny3Uy3by3fy4mry4msz4l3My4l3Ty4mv3R");
    string_constant_184 = 
	    STATIC_STRING("y4ml3Ky4l3Cy4l3ey4ot3Fy3Vy3ay4nmq3Py4l3dy4k4k4k");
    SET_SYMBOL_VALUE(Qcan_create_additional_users_and_then_save_ok_file_message_1,
	    transform_type_specification_2(FIX((SI_Long)47L),
	    array_constant_54,
	    regenerate_optimized_constant(LIST_2(string_constant_183,
	    string_constant_184))));
    Qcan_create_additional_users_and_then_save_ok_file_message_2 = 
	    STATIC_SYMBOL("CAN-CREATE-ADDITIONAL-USERS-AND-THEN-SAVE-OK-FILE-MESSAGE-2",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcan_create_additional_users_and_then_save_ok_file_message_2,
	    Can_create_additional_users_and_then_save_ok_file_message_2);
    array_constant_55 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)1L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)2L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)5L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)6L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)7L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)8L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)9L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)10L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)11L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)12L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)13L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)14L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)18L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)24L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)25L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)26L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)29L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)30L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)33L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)34L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)35L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)36L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)37L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)38L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)47L,(SI_Long)57344L);
    string_constant_185 = 
	    STATIC_STRING("43Zy43Qykry3Ly3Wy3cy3fy3ny3ty3xy3-0y3-Cy3-Ly3-Uy3-Xy3-fy3-jy3-oy3-ty3-xy3*=y3*2y3*Cy3*Hy3*Ky3*Sy3*Vy3*Zy3*hy3*ky4m3*Ly3*Ry4m3my3");
    string_constant_186 = 
	    STATIC_STRING("-ey4m3*Oy3*uy4k4m3*Ny3*jy4k4k4k4m3-Yy3*iy4l3*1y4l3-1y4l3*0y4ml3-Dy4l3-+y4yovz3Jy3My3dy3-2y3-8y3-Ey3-gy3-qy3*Ey3*Iy3*dy4m3-Vy3*Dy");
    string_constant_187 = 
	    STATIC_STRING("4v3Cy3Dy3Vy3jy3ly3-Ky3-Ty3-iy3*9y3*ay3*ly4ns3-Ay3*py43Kynqux3Uy3Zy3hy3iy3ky3wy3-=y3-6y3-By3-Sy3-Zy3-my3-sy3**y3*8y3*By3*Gy3*Yy3*");
    string_constant_188 = 
	    STATIC_STRING("by3*oy4l3*cy4n3sy3*Ay3*My4p3Py3vy3-ly3*-y3*Xy4t3Ey3Gy3Sy3qy3--y3-3y3-Ry3*Ty3*my4m3*3y3*Qy4pm3Ky3-Qy3*7y3*fy4l3-dy4v3Iy3gy3ry3-4y");
    string_constant_189 = 
	    STATIC_STRING("3-7y3-9y3-ay3-hy3-ny3*4y3*Uy4r3Hy3Qy3-Iy3-uy3*5y3*Py3*ry4m3-Oy3-Py4qt3Ry3ay3-Jy3*ny3*sy4wp3Yy3by3ey3py3-Fy3-Gy3-My3-by3-py3*Fy3*");
    string_constant_190 = 
	    STATIC_STRING("Jy4ww3Fy3Oy3uy3-*y3-5y3-ky3-wy3*+y3*Wy3*gy3*qy4q3Ny3Xy3oy3-Ny3-vy3*ey4l3-ry4m3-Hy3*6y4k4n3-Wy3-cy3*ty4l3Ty");
    SET_SYMBOL_VALUE(Qcan_create_additional_users_and_then_save_ok_file_message_2,
	    transform_type_specification_2(FIX((SI_Long)189L),
	    array_constant_55,regenerate_optimized_constant(list(6,
	    string_constant_185,string_constant_186,string_constant_187,
	    string_constant_188,string_constant_189,string_constant_190))));
    Qg2_not_authorized_because_fails_process_count_message = 
	    STATIC_SYMBOL("G2-NOT-AUTHORIZED-BECAUSE-FAILS-PROCESS-COUNT-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_not_authorized_because_fails_process_count_message,
	    G2_not_authorized_because_fails_process_count_message);
    array_constant_56 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)4L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)5L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)6L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)7L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)8L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)9L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)20L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)23L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)28L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)29L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)30L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)31L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)32L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)33L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)38L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)39L,(SI_Long)57344L);
    string_constant_191 = 
	    STATIC_STRING("43Uy4m3gy3-Ly43Mynv3Ey3Hy3Ry3Uy3ey3hy3iy3jy3ny3vy3-1y3-4y3-9y3-Iy3-Jy3-My3-Ny3-Oy3-Ty3-Xy3-ay3-iy3-ly3-py4m3-Hy3**y4k4m3Ty3-Zy4k");
    string_constant_192 = 
	    STATIC_STRING("4k4k4m3Sy3-Yy4mk3-Py4qp3ky3oy3sy3-By3-qy4lz4n3Yy3-Cy3-ey4n3Qy3ty3*-y4wm3Cy3Jy3Py3Zy3cy3my3ry3-Gy3-Vy3-fy3*+y4l3Gy4l3-0y4pl3-6y3-");
    string_constant_193 = 
	    STATIC_STRING("Dy3-Qy3-ty4sr3My3-*y3-7y3-Ey3-Ry3-jy3-wy4l3py4qosuy3Ly3-Ay4sw3-+y3--y3-=y3-3y3-Fy3-Uy3-my4q3Fy3Xy3-2y3-dy3-ny3-uy4n3Iy3Vy3-by4s3");
    string_constant_194 = 
	    STATIC_STRING("Dy3Ky3Wy3ly3qy3wy3-cy3-vy4s3ay3by3dy3-8y3-Sy3-gy3-hy3-ky4p3Ny3Oy3-5y3-oy3-sy4otx3xy3-ry4k4l3-Wy4lq4l3uy4l3-xy4m3fy3-Ky");
    SET_SYMBOL_VALUE(Qg2_not_authorized_because_fails_process_count_message,
	    transform_type_specification_2(FIX((SI_Long)131L),
	    array_constant_56,
	    regenerate_optimized_constant(LIST_4(string_constant_191,
	    string_constant_192,string_constant_193,string_constant_194))));
    Qg2_not_authorized_because_cannot_register_process_license_message = 
	    STATIC_SYMBOL("G2-NOT-AUTHORIZED-BECAUSE-CANNOT-REGISTER-PROCESS-LICENSE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_not_authorized_because_cannot_register_process_license_message,
	    G2_not_authorized_because_cannot_register_process_license_message);
    array_constant_57 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)4L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)5L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)6L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)7L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)8L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)9L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)15L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)18L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)21L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)23L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)28L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)29L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)30L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)31L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)32L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)38L,(SI_Long)33L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)39L,(SI_Long)57344L);
    string_constant_195 = 
	    STATIC_STRING("43Ty4l3jy4wr3Fy3Ny3Vy3Yy3hy3ky3ly3my3py3sy3wy4m3gy3-5y4k4l3oy4k4k4k4l3ny4lk4l3xy4ln4m3Jy3Qy4l3-4y4spty3Ky3Ry3Uy3ay3-3y4mu3Ey4l3-");
    string_constant_196 = 
	    STATIC_STRING("*y4pv3Cy3Py3qy3-1y4l3fy4mo3Oy4p3Dy3Sy3Xy3Zy3ty4lq4qm3Iy3Wy3dy3uy3-=y4l3Gy4qlsz3Hy3ey3-0y4pw3Ly3My3Ty3ry4ox3by3vy3--y4l3-+y4k4l3c");
    string_constant_197 = STATIC_STRING("y4l3-2y4k4l3iy");
    SET_SYMBOL_VALUE(Qg2_not_authorized_because_cannot_register_process_license_message,
	    transform_type_specification_2(FIX((SI_Long)74L),
	    array_constant_57,
	    regenerate_optimized_constant(LIST_3(string_constant_195,
	    string_constant_196,string_constant_197))));
    list_constant_52 = STATIC_LIST((SI_Long)6L,FIX((SI_Long)3L),
	    FIX((SI_Long)2L),FIX((SI_Long)1L),FIX((SI_Long)0L),
	    FIX((SI_Long)-1L),FIX((SI_Long)-2L));
    Keytab_backbone = list_constant_52;
    Keytab_interface_linkage = CDDR(Keytab_backbone);
    Keytab_interface_inset = CDR(Keytab_backbone);
    if (Default_format_structure == UNBOUND)
	Default_format_structure = LIST_5(Nil,Nil,Nil,Nil,Nil);
    list_constant_1 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)116L),
	    FIX((SI_Long)84L));
    list_constant_2 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)73L),
	    FIX((SI_Long)105L));
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcompletely_shut_down_g2 = STATIC_SYMBOL("COMPLETELY-SHUT-DOWN-G2",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_29 = STATIC_STRING("~a");
    array_constant_7 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)39L,(SI_Long)57344L);
    string_constant_30 = STATIC_STRING("has not been valid since ");
    string_constant_31 = STATIC_STRING("will not be valid until ");
    array_constant_8 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    Qrestricted_use = STATIC_SYMBOL("RESTRICTED-USE",AB_package);
    Qinitialize_for_asian_languages = 
	    STATIC_SYMBOL("INITIALIZE-FOR-ASIAN-LANGUAGES",AB_package);
    string_constant_32 = 
	    STATIC_STRING("Your machine has already been authorized but there is ~\n              now an OK for this machine which is incorrect. ~\n              You are still authorized.");
    string_constant_33 = 
	    STATIC_STRING("The authorization is not correct.  ~\n                  Please check it and try again.");
    string_constant_34 = 
	    STATIC_STRING("430+yw3-Ay3*Wy3=by3-8y3-Wy3=xy3=Ey3Vy3gy3ry3*8y3=Ly3-Qy3*Ny3=fy3*5y3-Sy3=-y3*cy3Hy3*Fy3*+y3*wy3=*y3=vy3=3y3-My3=Qy3=0y3*ny3-ey3-");
    string_constant_35 = 
	    STATIC_STRING("fy3-Gyq3-Py3ay3*Sy3*Yy3*Oy3*hy3=wy3=Ny3=ly3=dy3*4y3Wy3=hy3*my3=1y3*ay3wy3-By3*Py3Dy3=6y3=qy3=Zy3=2y3-hy3*Ty3=ay3Ly3=Cy3*0y3=oy3-");
    string_constant_36 = 
	    STATIC_STRING("+y3-by3-py3=8y3*Ly3*7y3=Hy3-ry3ky3-Ty3*ry3*-y3-Eyy3-Fy3=uyu3=4y3=Fy3Ky3*Jy3Zyr3-sy3*gy3*Ry3ey3-=y3=My3*py3-cy3Oy3Py3Qy3Iy3dynk3=");
    string_constant_37 = 
	    STATIC_STRING("Ry3*ty3*Uy3*ey3sy3-Iy3-7y3*Ky3My3my3*vy3=Ky3*jy3-wy3=ky3Jy3cy3hy3*oy3=Dy3*Vy3xy3-Uy3Ty3=Oy3=sy3*dy3*Hyp3iy3-Ry3=Yy3=ty3=Gy3-6y3S");
    string_constant_38 = 
	    STATIC_STRING("y3=5y3-gy3-Yy3Ey3**y3fy3*Gy3*Iy3-9ys3=ry3Gy3=Wy3=jy3*Eym3=Xy3*Ay3*ly3=Sy3*Dy3-Ly3-myt3vy3ly3-1y3qy3-Ny3*qy3*1y3-ky3=Py3=my3ty3=T");
    string_constant_39 = 
	    STATIC_STRING("y3=9y3Ry3*Cy3*xy3*=y3*6y3Yyv3=7y3Cy3-3y3-xy3=py3=ny3==y3=gy3*uy3-Dy3*kylo3-Jy3--y3-ny3-Hy3-jy3*3y3=Vy3Fy3-uy3-oy3-5y3*9y3by3-ty3");
    string_constant_40 = 
	    STATIC_STRING("=ey3*by3-Vy3*sy3-Cy3-vy3-ly3*2y3*Qy3oy3Xy3=Ay3=iy3-2yx3jy3=cy3*iy3-Xy3-Zy3-dy3*By3=Iy3-Ky3*fy3-qy3*My3-iy3-Oy3-0y3*Zyz3py3Ny3ny3");
    string_constant_41 = 
	    STATIC_STRING("=By3=Uy3Uy3-*y3=Jy3-4y3-ay3uy3=+y3*Xy");
    string_constant_42 = 
	    STATIC_STRING("Ry3*ty3*Uy3*ey3sy3-Iy3-7y3*Ky3My3my3*vy3=Ky3*jy3-wy3=ky3Jy3cy3hy3*oy3=Dy3*Vy3xy3-Uy3Ty3=Oy3=sy3*dy3*Hyp3iy3-Ry3=Yy3=ty3=Gy3=5y3-");
    string_constant_43 = 
	    STATIC_STRING("gy3-Yy3Ey3**y3fy3*Gy3*Iy3-9ys3=ry3Gy3=Wy3=jy3*Eym3=Xy3*Ay3*ly3=Sy3*Dy3-Ly3-myt3vy3ly3-1y3qy3-Ny3*qy3*1y3-ky3=Py3=my3ty3=Ty3=9y3R");
    string_constant_44 = 
	    STATIC_STRING("y3*Cy3*xy3*=y3*6y3Yyv3=7y3Cy3-3y3-6y3Sy3-xy3=py3=ny3==y3=gy3*uy3-Dy3*kylo3-Jy3--y3-ny3-Hy3-jy3*3y3=Vy3Fy3-uy3-oy3-5y3*9y3by3-ty3");
    string_constant_45 = 
	    STATIC_STRING("+y3-by3-py3=8y3*Ly3*7y3=Hy3-ry3ky3-Ty3*ry3*-y3-Eyy3-Fy3=uyu3=4y3=Fy3Ky3*Jy3Zyr3*gy3-sy3*Ry3ey3-=y3=My3*py3-cy3Oy3Py3Qy3Iy3dynk3=");
    string_constant_46 = 
	    STATIC_STRING("Ry3*ty3*Uy3*ey3sy3-Iy3-7y3*Ky3My3my3*vy3=Ky3*jy3-wy3=ky3Jy3cy3hy3*oy3=Dy3*Vy3xy3-Uy3Ty3=Oy3=sy3iy3-Ry3=Yy3=ty3=Gy3=5y3-gy3-Yy3Ey");
    string_constant_47 = 
	    STATIC_STRING("3**y3fy3*Gy3*Iy3-9ys3=ry3Gy3=Wy3=jy3*Eym3=Xy3*Ay3*ly3=Sy3*Dy3-Ly3-myt3vy3ly3-1y3qy3-Ny3*qy3*1y3-ky3=Py3=my3ty3=Ty3=9y3Ry3*Cy3*xy");
    string_constant_48 = 
	    STATIC_STRING("3*=y3*6y3Yyv3=7y3Cy3-3y3-6y3Sy3*dy3*Hyp3-xy3=py3=ny3==y3=gy3*uy3-Dy3*kylo3-Jy3--y3-ny3-Hy3-jy3*3y3=Vy3Fy3-uy3-oy3-5y3*9y3by3-ty3");
    string_constant_49 = 
	    STATIC_STRING("Ry3*ty3*ey3*Uy3sy3-Iy3-7y3*Ky3My3my3*vy3=Ky3*jy3-wy3=ky3Jy3cy3hy3*oy3=Dy3*Vy3xy3-Uy3Ty3=Oy3=sy3iy3-Ry3=Yy3=ty3=Gy3=5y3-gy3-Yy3Ey");
    string_constant_50 = 
	    STATIC_STRING("3*=y3*6y3Yyv3=7y3Cy3-3y3-6y3Sy3*dy3*Hyp3-xy3=py3=ny3==y3=gy3*uy3-Dy3*kylo3-Jy3--y3-ny3-Hy3-jy3*3y3=Vy3Fy3-uy3-oy3-5y3*9y3-ly3*2y");
    string_constant_51 = 
	    STATIC_STRING("3*Qy3by3-ty3=ey3*by3-Vy3*sy3-Cy3-vy3oy3Xy3=Ay3=iy3-2yx3jy3=cy3*iy3-Xy3-Zy3-dy3*By3=Iy3-Ky3*fy3-qy3*My3-iy3-Oy3-0y3*Zyz3py3Ny3ny3");
    Qkeytab1 = STATIC_SYMBOL("KEYTAB1",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkeytab1,Keytab1);
    Qchoose_keytab = STATIC_SYMBOL("CHOOSE-KEYTAB",AB_package);
    SET_SYMBOL_FUNCTION(Qchoose_keytab,STATIC_FUNCTION(choose_keytab,NIL,
	    FALSE,0,0));
    list_constant_53 = STATIC_LIST((SI_Long)2L,Kfuncall,Qchoose_keytab);
    record_system_variable(Qkeytab1,Qsequences2,list_constant_53,Qnil,Qnil,
	    Qnil,Qnil);
    if (Redef_class_instance == UNBOUND) {
	temp_1 = make_array(1,FIX((SI_Long)4L));
	temp = CDR(Default_format_structure);
	temp = CONS(Nil,temp);
	Redef_class_instance = CONS(temp_1,temp);
    }
    temp_2 = CAR(Redef_class_instance);
    temp_3 = Redef_class_instance;
    set_aref1(temp_2,FIX((SI_Long)1L),temp_3);
    if (Saved_initial_status == UNBOUND)
	Saved_initial_status = CAR(Redef_class_instance);
    string_constant_198 = 
	    STATIC_STRING("This G2 is not authorized. Please shut it down and call Gensym for proper authorization.");
    if (System_slot_accessor == UNBOUND)
	System_slot_accessor = LIST_2(FIX((SI_Long)34L),string_constant_198);
    if (Color_code_differences == UNBOUND)
	Color_code_differences = LIST_2(Nil,SECOND(System_slot_accessor));
    Qalternate_chaining_queue = STATIC_SYMBOL("ALTERNATE-CHAINING-QUEUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qalternate_chaining_queue,
	    Alternate_chaining_queue);
    record_system_variable(Qalternate_chaining_queue,Qsequences2,Nil,Qnil,
	    Qnil,Qnil,Qt);
    Qrevert_to_fuzzy_cache_p = STATIC_SYMBOL("REVERT-TO-FUZZY-CACHE-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrevert_to_fuzzy_cache_p,
	    Revert_to_fuzzy_cache_p);
    record_system_variable(Qrevert_to_fuzzy_cache_p,Qsequences2,Nil,Qnil,
	    Qnil,Qnil,Qt);
    Qcall_post_prominent_notification = 
	    STATIC_SYMBOL("CALL-POST-PROMINENT-NOTIFICATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcall_post_prominent_notification,
	    STATIC_FUNCTION(call_post_prominent_notification,NIL,FALSE,4,4));
    Qredraw_solid_rectangles_without_overlap = 
	    STATIC_SYMBOL("REDRAW-SOLID-RECTANGLES-WITHOUT-OVERLAP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qredraw_solid_rectangles_without_overlap,
	    STATIC_FUNCTION(redraw_solid_rectangles_without_overlap,NIL,
	    FALSE,1,1));
    if (Cached_matching_machine_id_qm == UNBOUND)
	Cached_matching_machine_id_qm = Nil;
    if (Grammar_rules_to_add_for_nupec_after_authorization == UNBOUND)
	Grammar_rules_to_add_for_nupec_after_authorization = Nil;
    Qgfi_file_format = STATIC_SYMBOL("GFI-FILE-FORMAT",AB_package);
    Qnupec = STATIC_SYMBOL("NUPEC",AB_package);
    list_constant_54 = STATIC_LIST((SI_Long)2L,Qquote,Qnupec);
    Qsnapshot = STATIC_SYMBOL("SNAPSHOT",AB_package);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qquote,Qsnapshot);
    list_constant_56 = STATIC_LIST((SI_Long)2L,list_constant_54,
	    list_constant_55);
    Qnupec_snapshot = STATIC_SYMBOL("NUPEC-SNAPSHOT",AB_package);
    list_constant_83 = STATIC_LIST((SI_Long)3L,Qgfi_file_format,
	    list_constant_56,Qnupec_snapshot);
    Qwith = STATIC_SYMBOL("WITH",AB_package);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qquote,Qwith);
    Qab_restart = STATIC_SYMBOL("RESTART",AB_package);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qquote,Qab_restart);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qquote,Qtime);
    list_constant_60 = STATIC_LIST((SI_Long)5L,list_constant_54,
	    list_constant_55,list_constant_57,list_constant_58,
	    list_constant_59);
    Qnupec_snapshot_with_restart_time = 
	    STATIC_SYMBOL("NUPEC-SNAPSHOT-WITH-RESTART-TIME",AB_package);
    list_constant_84 = STATIC_LIST((SI_Long)3L,Qgfi_file_format,
	    list_constant_60,Qnupec_snapshot_with_restart_time);
    Qtiming_scheduler_mode = STATIC_SYMBOL("TIMING-SCHEDULER-MODE",AB_package);
    Qab_catch = STATIC_SYMBOL("CATCH",AB_package);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qquote,Qab_catch);
    Qup = STATIC_SYMBOL("UP",AB_package);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qquote,Qup);
    Qmode = STATIC_SYMBOL("MODE",AB_package);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qquote,Qmode);
    list_constant_64 = STATIC_LIST((SI_Long)4L,list_constant_54,
	    list_constant_61,list_constant_62,list_constant_63);
    Qnupec_catch_up = STATIC_SYMBOL("NUPEC-CATCH-UP",AB_package);
    list_constant_85 = STATIC_LIST((SI_Long)3L,Qtiming_scheduler_mode,
	    list_constant_64,Qnupec_catch_up);
    Qplot_marker_phrase = STATIC_SYMBOL("PLOT-MARKER-PHRASE",AB_package);
    Qusing = STATIC_SYMBOL("USING",AB_package);
    list_constant_65 = STATIC_LIST((SI_Long)2L,Qquote,Qusing);
    Qplot = STATIC_SYMBOL("PLOT",AB_package);
    list_constant_66 = STATIC_LIST((SI_Long)2L,Qquote,Qplot);
    Qmarker = STATIC_SYMBOL("MARKER",AB_package);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qquote,Qmarker);
    list_constant_68 = STATIC_LIST((SI_Long)5L,list_constant_65,Qab_class,
	    list_constant_54,list_constant_66,list_constant_67);
    list_constant_69 = STATIC_CONS(FIX((SI_Long)3L),FIX((SI_Long)2L));
    list_constant_86 = STATIC_LIST((SI_Long)3L,Qplot_marker_phrase,
	    list_constant_68,list_constant_69);
    Qevent_literal = STATIC_SYMBOL("EVENT-LITERAL",AB_package);
    Qsynchronization = STATIC_SYMBOL("SYNCHRONIZATION",AB_package);
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qquote,Qsynchronization);
    Qoccurs = STATIC_SYMBOL("OCCURS",AB_package);
    list_constant_71 = STATIC_LIST((SI_Long)2L,Qquote,Qoccurs);
    list_constant_72 = STATIC_LIST((SI_Long)3L,list_constant_54,
	    list_constant_70,list_constant_71);
    Qnupec_synchronization_occurs = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZATION-OCCURS",AB_package);
    list_constant_73 = STATIC_CONS(Qnupec_synchronization_occurs,Qnil);
    list_constant_87 = STATIC_LIST((SI_Long)3L,Qevent_literal,
	    list_constant_72,list_constant_73);
    Qaction = STATIC_SYMBOL("ACTION",AB_package);
    Qsynchronize = STATIC_SYMBOL("SYNCHRONIZE",AB_package);
    list_constant_74 = STATIC_LIST((SI_Long)2L,Qquote,Qsynchronize);
    Qsynchronize_reference_list = 
	    STATIC_SYMBOL("SYNCHRONIZE-REFERENCE-LIST",AB_package);
    Qacross = STATIC_SYMBOL("ACROSS",AB_package);
    list_constant_75 = STATIC_LIST((SI_Long)2L,Qquote,Qacross);
    Qunique_designation = STATIC_SYMBOL("UNIQUE-DESIGNATION",AB_package);
    list_constant_77 = STATIC_LIST((SI_Long)5L,list_constant_54,
	    list_constant_74,Qsynchronize_reference_list,list_constant_75,
	    Qunique_designation);
    Qnupec_synchronize = STATIC_SYMBOL("NUPEC-SYNCHRONIZE",AB_package);
    list_constant_76 = STATIC_CONS(FIX((SI_Long)3L),Qnil);
    list_constant_78 = STATIC_LIST_STAR((SI_Long)3L,Qnupec_synchronize,
	    FIX((SI_Long)5L),list_constant_76);
    Qfix_nupec_synchronize = STATIC_SYMBOL("FIX-NUPEC-SYNCHRONIZE",AB_package);
    list_constant_88 = STATIC_LIST((SI_Long)4L,Qaction,list_constant_77,
	    list_constant_78,Qfix_nupec_synchronize);
    Qnupec_extra_action_list = STATIC_SYMBOL("NUPEC-EXTRA-ACTION-LIST",
	    AB_package);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qquote,Qand);
    Qaction_list_3 = STATIC_SYMBOL("ACTION-LIST-3",AB_package);
    list_constant_80 = STATIC_LIST((SI_Long)3L,Qaction,list_constant_79,
	    Qaction_list_3);
    list_constant_81 = STATIC_LIST_STAR((SI_Long)3L,Qand,FIX((SI_Long)1L),
	    list_constant_76);
    list_constant_89 = STATIC_LIST((SI_Long)4L,Qnupec_extra_action_list,
	    list_constant_80,list_constant_81,Qsimplify_associative_operation);
    list_constant_90 = STATIC_LIST((SI_Long)2L,Qnupec_extra_action_list,
	    Qaction);
    list_constant_82 = STATIC_LIST((SI_Long)2L,Qquote,Qnone);
    list_constant_91 = STATIC_LIST((SI_Long)3L,Qnupec_extra_action_list,
	    list_constant_82,Qnil);
    list_constant_92 = STATIC_LIST((SI_Long)9L,list_constant_83,
	    list_constant_84,list_constant_85,list_constant_86,
	    list_constant_87,list_constant_88,list_constant_89,
	    list_constant_90,list_constant_91);
    add_grammar_rules_for_nupec_after_authorization(list_constant_92);
    string_constant_52 = STATIC_STRING("NUPEC");
    if (Daily_countdown == UNBOUND)
	Daily_countdown = FIX((SI_Long)7L);
    if (Hourly_countdown == UNBOUND)
	Hourly_countdown = FIX((SI_Long)24L);
    if (Hour_of_last_message == UNBOUND)
	Hour_of_last_message = FIX((SI_Long)-1L);
    if (Operative_task_list == UNBOUND)
	Operative_task_list = LIST_3(FIX((SI_Long)3L),FIX((SI_Long)7L),
		FIX((SI_Long)12L));
    if (Smoothed_subsecond_adjustment == UNBOUND) {
	temp_1 = FIX((SI_Long)4L);
	temp_4 = FIX((SI_Long)5L);
	temp = CDDR(Operative_task_list);
	temp = CONS(temp_4,temp);
	Smoothed_subsecond_adjustment = CONS(temp_1,temp);
    }
    string_constant_53 = STATIC_STRING("~(~a~)      ");
    string_constant_54 = STATIC_STRING("Start date: ");
    string_constant_55 = STATIC_STRING("      End date: ");
    string_constant_56 = STATIC_STRING("~%~%");
    string_constant_57 = 
	    STATIC_STRING("The license to use G2 on this machine has expired.~%");
    string_constant_58 = 
	    STATIC_STRING("G2 is not licensed to run with the package ~(~a~).~%");
    string_constant_59 = 
	    STATIC_STRING("The license to use the package ~(~a~) has expired.~%");
    string_constant_60 = 
	    STATIC_STRING("The license to use the package ~(~a~) has not yet begun.~%");
    string_constant_61 = STATIC_STRING("G2 cannot be started or resumed.");
    Qauthorized_user = STATIC_SYMBOL("AUTHORIZED-USER",AB_package);
    check_if_superior_classes_are_defined(Qauthorized_user,list_constant_50);
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_199 = 
	    STATIC_STRING("1n4z8r831ny831ny83H+y83H+y0k001n1l8o1l8l1m8p831ny000004z8r83Xky83Xky83H+y83H+y00001n1l8o1l8l1m8p83EMy000004z8r8u8u83H+y83H+y01p8");
    string_constant_200 = 
	    STATIC_STRING("w9k3Gy3cy1o1o83*fy1muk1m3Cyq1muw1n83Oy1muw1mu3Qy1n83Oy1mk3Ey1m3Gy3Ey1o83Oy1mk3cy1mu3Qy1m3Gy3cy001o1l8l1l8o1l8z1m83Dy53YySee comm");
    string_constant_201 = STATIC_STRING("ent on ENTITY class definition00000");
    string_constant_202 = 
	    STATIC_STRING("1p8q1m83H+y1l83-+y1p831nyk8o8l1m8p831ny1p83Xky08o8l1m8p83EMy1m8u1p8w9k3Gy3cy1o1o83*fy1muk1m3Cyq1muw1n83Oy1muw1mu3Qy1n83Oy1mk3Ey1");
    string_constant_203 = STATIC_STRING("m3Gy3Ey1o83Oy1mk3cy1mu3Qy1m3Gy3cy");
    temp = regenerate_optimized_constant(string_constant_144);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_199,
	    string_constant_200,string_constant_201));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qauthorized_user,list_constant_50,Nil,temp,
	    Nil,temp_1,list_constant_50,
	    regenerate_optimized_constant(LIST_2(string_constant_202,
	    string_constant_203)),Nil);
    Authorized_user_class_description = 
	    lookup_global_or_kb_specific_property_value(Qauthorized_user,
	    Class_description_gkbprop);
    string_constant_204 = STATIC_STRING("1l1m831ny83-2y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_204));
    string_constant_205 = 
	    STATIC_STRING("1m1m83EMy83-6y1o83EMy1n83-6y1m9k83vy83EMy1nmln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_205));
    Quser_password = STATIC_SYMBOL("USER-PASSWORD",AB_package);
    Qcompile_user_password_for_slot = 
	    STATIC_SYMBOL("COMPILE-USER-PASSWORD-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_user_password_for_slot,
	    STATIC_FUNCTION(compile_user_password_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Quser_password,
	    SYMBOL_FUNCTION(Qcompile_user_password_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Quser_password,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_user_password_from_slot = 
	    STATIC_SYMBOL("WRITE-USER-PASSWORD-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_user_password_from_slot,
	    STATIC_FUNCTION(write_user_password_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Quser_password,
	    SYMBOL_FUNCTION(Qwrite_user_password_from_slot),
	    Qslot_value_writer);
    Qpermitted_mode_list = STATIC_SYMBOL("PERMITTED-MODE-LIST",AB_package);
    Qcompile_permitted_mode_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-PERMITTED-MODE-LIST-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_permitted_mode_list_for_slot,
	    STATIC_FUNCTION(compile_permitted_mode_list_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qpermitted_mode_list,
	    SYMBOL_FUNCTION(Qcompile_permitted_mode_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qpermitted_mode_list,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_permitted_mode_list_from_slot = 
	    STATIC_SYMBOL("WRITE-PERMITTED-MODE-LIST-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_permitted_mode_list_from_slot,
	    STATIC_FUNCTION(write_permitted_mode_list_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qpermitted_mode_list,
	    SYMBOL_FUNCTION(Qwrite_permitted_mode_list_from_slot),
	    Qslot_value_writer);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    if (Time_of_last_call_to_set_user_password == UNBOUND) {
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	Time_of_last_call_to_set_user_password = new_float;
    }
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,1.0);
    Required_delay_between_calls_to_set_password = new_float;
    Qattempting_to_set_user_password_too_fast = 
	    STATIC_SYMBOL("ATTEMPTING-TO-SET-USER-PASSWORD-TOO-FAST",
	    AB_package);
    if (Authorized_users_list == UNBOUND)
	Authorized_users_list = Nil;
    if (Updated_users_list == UNBOUND)
	Updated_users_list = Nil;
    Qunauthorized_mode = STATIC_SYMBOL("UNAUTHORIZED-MODE",AB_package);
    Qadministrator = STATIC_SYMBOL("ADMINISTRATOR",AB_package);
    list_constant_3 = STATIC_CONS(Qadministrator,Qnil);
    Qnon_built_in_g2_user_mode = STATIC_SYMBOL("NON-BUILT-IN-G2-USER-MODE",
	    AB_package);
    Qunknown_user_mode_in_current_kb = 
	    STATIC_SYMBOL("UNKNOWN-USER-MODE-IN-CURRENT-KB",AB_package);
    Quser_name_required = STATIC_SYMBOL("USER-NAME-REQUIRED",AB_package);
    Quser_mode_required = STATIC_SYMBOL("USER-MODE-REQUIRED",AB_package);
    Qunknown_user_or_bad_password = 
	    STATIC_SYMBOL("UNKNOWN-USER-OR-BAD-PASSWORD",AB_package);
    Qpassword_required = STATIC_SYMBOL("PASSWORD-REQUIRED",AB_package);
    Qpassword_has_expired = STATIC_SYMBOL("PASSWORD-HAS-EXPIRED",AB_package);
    Qg2_window_user_is_valid = STATIC_SYMBOL("G2-WINDOW-USER-IS-VALID",
	    AB_package);
    Qg2_window_mode_is_valid = STATIC_SYMBOL("G2-WINDOW-MODE-IS-VALID",
	    AB_package);
    Qpermitted_user_modes = STATIC_SYMBOL("PERMITTED-USER-MODES",AB_package);
    Qput_permitted_user_modes = STATIC_SYMBOL("PUT-PERMITTED-USER-MODES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_permitted_user_modes,
	    STATIC_FUNCTION(put_permitted_user_modes,NIL,FALSE,3,3));
    mutate_global_property(Qpermitted_user_modes,
	    SYMBOL_FUNCTION(Qput_permitted_user_modes),Qslot_putter);
    Qput_user_password = STATIC_SYMBOL("PUT-USER-PASSWORD",AB_package);
    SET_SYMBOL_FUNCTION(Qput_user_password,
	    STATIC_FUNCTION(put_user_password,NIL,FALSE,3,3));
    mutate_global_property(Quser_password,
	    SYMBOL_FUNCTION(Qput_user_password),Qslot_putter);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Mm1 = FIX((SI_Long)16776379L);
    Mm2 = FIX((SI_Long)12184771L);
    Mm3 = FIX((SI_Long)3720484L);
    string_constant_206 = STATIC_STRING("g0934sd");
    Mm4 = string_constant_206;
    array_constant_9 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    string_constant_207 = 
	    STATIC_STRING("430+y3*Xy3=+y3uy3-ay3-4y3=Jy3-*y3Uy3=Uy3=By3ny3Ny3pyz3*Zy3-0y3-Oy3-iy3*My3-qy3*fy3-Ky3=Iy3*By3-dy3-Zy3-Xy3*iy3=cy3jyx3-2y3=iy3=A");
    string_constant_208 = 
	    STATIC_STRING("y3Xy3oy3*Qy3*2y3-ly3-vy3-Cy3*sy3-Vy3*by3=ey3-ty3by3*9y3-5y3-oy3-uy3Fy3=Vy3*3y3-jy3-Hy3-ny3--y3-Jyol3*ky3-Dy3*uy3=gy3==y3=ny3=py3");
    string_constant_209 = 
	    STATIC_STRING("-xy3-3y3Cy3=7yv3Yy3*6y3*=y3*xy3*Cy3Ry3=9y3=Ty3ty3=my3=Py3-ky3*1y3*qy3-Ny3qy3-1y3ly3vyt3-my3-Ly3*Dy3=Sy3*ly3*Ay3=Xym3*Ey3=jy3=Wy3");
    string_constant_210 = 
	    STATIC_STRING("Gy3=rys3-9y3*Iy3*Gy3fy3**y3Ey3-Yy3-gy3=5y3Sy3-6y3=Gy3=ty3=Yy3-Ry3iyp3*Hy3*dy3=sy3=Oy3Ty3-Uy3xy3*Vy3=Dy3*oy3hy3cy3Jy3=ky3-wy3*jy3");
    string_constant_211 = 
	    STATIC_STRING("=Ky3*vy3my3My3*Ky3-7y3-Iy3sy3*ey3*Uy3*ty3=Rykn3dy3Iy3Qy3Py3Oy3-cy3*py3=My3-=y3ey3*Ry3*gy3-syr3Zy3*Jy3Ky3=Fy3=4yu3=uy3-Fyy3-Ey3*-");
    string_constant_212 = 
	    STATIC_STRING("y3*ry3-Ty3ky3-ry3=Hy3*7y3*Ly3=8y3-py3-by3-+y3=oy3*0y3=Cy3Ly3=ay3*Ty3-hy3=2y3=Zy3=qy3=6y3Dy3*Py3-By3wy3*ay3=1y3*my3=hy3Wy3*4y3=dy");
    string_constant_213 = 
	    STATIC_STRING("3=ly3=Ny3=wy3*hy3*Oy3*Yy3*Sy3ay3-Pyq3-Gy3-fy3-ey3*ny3=0y3=Qy3-My3=3y3=vy3=*y3*wy3*+y3*Fy3Hy3*cy3=-y3-Sy3*5y3=fy3*Ny3-Qy3=Ly3*8y3");
    string_constant_214 = 
	    STATIC_STRING("ry3gy3Vy3=Ey3=xy3-Wy3-8y3=by3*Wy3-Ayw");
    if (Font_feature_list == UNBOUND)
	Font_feature_list = regenerate_optimized_constant(list(8,
		string_constant_207,string_constant_208,
		string_constant_209,string_constant_210,
		string_constant_211,string_constant_212,
		string_constant_213,string_constant_214));
    string_constant_215 = 
	    STATIC_STRING("430+y3=Qy3-My3=3y3=vy3=*y3*wy3*+y3*Fy3Hy3*cy3=-y3-Sy3*5y3=fy3*Ny3-Qy3=Ly3=+y3uy3-ay3-4y3=Jy3-*y3Uy3=Uy3=By3ny3Ny3pyz3*Zy3-0y3-Oy");
    string_constant_216 = 
	    STATIC_STRING("3-iy3*My3-qy3*fy3-Ky3=Iy3*By3-dy3-Zy3-Xy3*iy3=cy3jyx3-2y3=iy3=Ay3Xy3oy3*3y3-jy3-Hy3-ny3--y3-Jyol3*ky3-Dy3*uy3=gy3==y3=ny3=py3-xy");
    string_constant_217 = 
	    STATIC_STRING("3-3y3Cy3=7yv3Yy3*6y3*=y3*xy3*Cy3Ry3=9y3=Ty3ty3=my3=Py3-ky3*1y3*qy3-Ny3qy3-1y3ly3vyt3-my3-Ly3*Dy3=Sy3*ly3*Ay3=Xym3*Ey3=jy3=Wy3Gy3");
    string_constant_218 = 
	    STATIC_STRING("=rys3-9y3*Iy3*Gy3fy3**y3Ey3-Yy3-gy3=5y3Sy3-6y3=Gy3=ty3=Yy3-Ry3iyp3*Hy3*dy3=sy3=Oy3Ty3-Uy3xy3*Vy3=Dy3*oy3hy3cy3Jy3=ky3-wy3*jy3=Ky");
    string_constant_219 = 
	    STATIC_STRING("3*vy3my3My3*Ky3-7y3-Iy3sy3*ey3*Uy3*ty3=Rykn3dy3Iy3Qy3Py3Oy3-cy3*py3=My3-=y3ey3*Ry3*gy3-syr3Zy3*Jy3Ky3=Fy3=4yu3=uy3-Fyy3-Ey3*Qy3*");
    string_constant_220 = 
	    STATIC_STRING("2y3-ly3-vy3-Cy3*sy3-Vy3*by3=ey3-ty3by3*9y3-5y3-oy3-uy3Fy3=Vy3*-y3*ry3-Ty3ky3-ry3=Hy3*7y3*Ly3=8y3-py3-by3-+y3=oy3*0y3=Cy3Ly3=ay3*");
    string_constant_221 = 
	    STATIC_STRING("Ty3-hy3=2y3=Zy3=qy3=6y3Dy3*Py3-By3wy3*ay3=1y3*my3=hy3Wy3*4y3=dy3=ly3=Ny3=wy3*hy3*Oy3*Yy3*Sy3ay3-Pyq3-Gy3-fy3-ey3*ny3=0y3*8y3ry3g");
    string_constant_222 = 
	    STATIC_STRING("y3Vy3=Ey3=xy3-Wy3-8y3=by3*Wy3-Ayw3*Xy");
    if (Roman_character_map == UNBOUND)
	Roman_character_map = regenerate_optimized_constant(list(8,
		string_constant_215,string_constant_216,
		string_constant_217,string_constant_218,
		string_constant_219,string_constant_220,
		string_constant_221,string_constant_222));
    if (Feature_blt == UNBOUND)
	Feature_blt = make_array(1,FIX((SI_Long)8L));
    string_constant_223 = 
	    STATIC_STRING("1n1o834Sy1m9k83Zyl9l1n834Sy1m1m9k9m1m9k839qy1l01n834Sy1m1m9k83-jWy839cy1lm");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnil_function);
    push_optimized_constant(Qnot);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_223));
    if (Write_proprietary_package_while_saving_xml_kb == UNBOUND)
	Write_proprietary_package_while_saving_xml_kb = Nil;
    string_constant_62 = STATIC_STRING("potentially ~(~a~)");
    string_constant_63 = STATIC_STRING("not proprietary");
    Qproprietary_package = STATIC_SYMBOL("PROPRIETARY-PACKAGE",AB_package);
    Qwrite_proprietary_package_from_slot = 
	    STATIC_SYMBOL("WRITE-PROPRIETARY-PACKAGE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_proprietary_package_from_slot,
	    STATIC_FUNCTION(write_proprietary_package_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qproprietary_package,
	    SYMBOL_FUNCTION(Qwrite_proprietary_package_from_slot),
	    Qslot_value_writer);
    Qprivate = STATIC_SYMBOL("PRIVATE",AB_package);
    Qput_proprietary_package = STATIC_SYMBOL("PUT-PROPRIETARY-PACKAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_proprietary_package,
	    STATIC_FUNCTION(put_proprietary_package,NIL,FALSE,3,3));
    mutate_global_property(Qproprietary_package,
	    SYMBOL_FUNCTION(Qput_proprietary_package),Qslot_putter);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qcleanup_for_kb_workspace = STATIC_SYMBOL("CLEANUP-FOR-KB-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_kb_workspace,
	    STATIC_FUNCTION(cleanup_for_kb_workspace,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_kb_workspace);
    set_get(Qkb_workspace,Qcleanup,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_workspace,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    string_constant_64 = 
	    STATIC_STRING("You cannot make workspaces proprietary while the system is running.  ~\n        No workspaces were made proprietary.");
    string_constant_65 = STATIC_STRING("Making workspaces proprietary now!");
    string_constant_66 = 
	    STATIC_STRING("Finished making workspaces proprietary.");
    Qsimulate_proprietary_qm = STATIC_SYMBOL("SIMULATE-PROPRIETARY\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimulate_proprietary_qm,
	    Simulate_proprietary_qm);
    record_system_variable(Qsimulate_proprietary_qm,Qsequences2,Nil,Qnil,
	    Qnil,Qnil,Qt);
    Qdisplay_index_point = STATIC_SYMBOL("DISPLAY-INDEX-POINT",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qfree_text = STATIC_SYMBOL("FREE-TEXT",AB_package);
    Qborderless_free_text = STATIC_SYMBOL("BORDERLESS-FREE-TEXT",AB_package);
    Qdisplay_stack_priority = STATIC_SYMBOL("DISPLAY-STACK-PRIORITY",
	    AB_package);
    if (Supported_ok_file_format_version == UNBOUND)
	Supported_ok_file_format_version = FIX((SI_Long)3L);
    Kincompatible_ok_file = STATIC_SYMBOL("INCOMPATIBLE-OK-FILE",Pkeyword);
    string_constant_67 = STATIC_STRING("~(begin ~S~%~)");
    string_constant_68 = STATIC_STRING("~(  ~NN:");
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qexpiration_date_qm,
	    Qauthorized_kb_packages);
    list_constant_5 = STATIC_CONS(Qlist,Qnil);
    string_constant_69 = STATIC_STRING(";~&");
    string_constant_70 = STATIC_STRING("~(end ~S~%~)");
    string_constant_71 = STATIC_STRING(" none");
    string_constant_72 = STATIC_STRING(" false");
    string_constant_73 = STATIC_STRING(" ~S");
    string_constant_74 = STATIC_STRING(" ~D");
    string_constant_75 = STATIC_STRING(" ~NN");
    string_constant_76 = STATIC_STRING(" (");
    string_constant_77 = STATIC_STRING("~%                ");
    string_constant_78 = STATIC_STRING(" )");
    string_constant_224 = STATIC_STRING("READING-OK-FILE");
    if (Reading_ok_file == UNBOUND)
	Reading_ok_file = make_recursive_lock(2,Kname,string_constant_224);
    Qreading_ok_file = STATIC_SYMBOL("READING-OK-FILE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreading_ok_file,Reading_ok_file);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qreading_ok_file,
	    Qsequences2,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qreading_ok_file,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qpad_for_ok_file_reader = STATIC_SYMBOL("PAD-FOR-OK-FILE-READER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpad_for_ok_file_reader,Pad_for_ok_file_reader);
    Qcompute_process_initial_value_for_pad_for_ok_file_reader = 
	    STATIC_SYMBOL("COMPUTE-PROCESS-INITIAL-VALUE-FOR-PAD-FOR-OK-FILE-READER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_process_initial_value_for_pad_for_ok_file_reader,
	    STATIC_FUNCTION(compute_process_initial_value_for_pad_for_ok_file_reader,
	    NIL,FALSE,0,0));
    list_constant_93 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qcompute_process_initial_value_for_pad_for_ok_file_reader);
    record_system_variable(Qpad_for_ok_file_reader,Qsequences2,
	    list_constant_93,Qnil,Qnil,Qnil,Qnil);
    if (Current_machine_ids_of_g2_ok_file_qm == UNBOUND)
	Current_machine_ids_of_g2_ok_file_qm = Nil;
    Qread_ok_file_buffer_1 = STATIC_SYMBOL("READ-OK-FILE-BUFFER-1",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qread_ok_file_buffer_1,Read_ok_file_buffer_1);
    list_constant_94 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_string,
	    FIX((SI_Long)2048L));
    record_system_variable(Qread_ok_file_buffer_1,Qsequences2,
	    list_constant_94,Qnil,Qnil,Qnil,Qnil);
    string_constant_79 = STATIC_STRING("~%OK file error ~a");
    string_constant_80 = STATIC_STRING("OK file warning. Possible problem~a");
    string_constant_81 = STATIC_STRING("~%~a~%");
    string_constant_82 = STATIC_STRING(" on or near line ~D");
    string_constant_83 = STATIC_STRING("~%Rule broken: ~A");
    Qeof_character_for_g2_ok_file = 
	    STATIC_SYMBOL("EOF-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qeof_character_for_g2_ok_file,FIX((SI_Long)-1L));
    Qillegal_character_for_g2_ok_file = 
	    STATIC_SYMBOL("ILLEGAL-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qillegal_character_for_g2_ok_file,FIX((SI_Long)0L));
    Qwhitespace_character_for_g2_ok_file = 
	    STATIC_SYMBOL("WHITESPACE-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qwhitespace_character_for_g2_ok_file,FIX((SI_Long)1L));
    Qopen_string_character_for_g2_ok_file = 
	    STATIC_SYMBOL("OPEN-STRING-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qopen_string_character_for_g2_ok_file,FIX((SI_Long)2L));
    Qopen_paren_character_for_g2_ok_file = 
	    STATIC_SYMBOL("OPEN-PAREN-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qopen_paren_character_for_g2_ok_file,FIX((SI_Long)3L));
    Qclose_paren_character_for_g2_ok_file = 
	    STATIC_SYMBOL("CLOSE-PAREN-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qclose_paren_character_for_g2_ok_file,FIX((SI_Long)4L));
    Qcolon_character_for_g2_ok_file = 
	    STATIC_SYMBOL("COLON-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qcolon_character_for_g2_ok_file,FIX((SI_Long)5L));
    Qsemicolon_character_for_g2_ok_file = 
	    STATIC_SYMBOL("SEMICOLON-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qsemicolon_character_for_g2_ok_file,FIX((SI_Long)6L));
    Qdash_character_for_g2_ok_file = 
	    STATIC_SYMBOL("DASH-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qdash_character_for_g2_ok_file,FIX((SI_Long)7L));
    Qdigit_character_for_g2_ok_file = 
	    STATIC_SYMBOL("DIGIT-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qdigit_character_for_g2_ok_file,FIX((SI_Long)8L));
    Qalphabetic_character_for_g2_ok_file = 
	    STATIC_SYMBOL("ALPHABETIC-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qalphabetic_character_for_g2_ok_file,FIX((SI_Long)9L));
    Qcr_character_for_g2_ok_file = 
	    STATIC_SYMBOL("CR-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qcr_character_for_g2_ok_file,FIX((SI_Long)10L));
    Qlf_character_for_g2_ok_file = 
	    STATIC_SYMBOL("LF-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qlf_character_for_g2_ok_file,FIX((SI_Long)11L));
    Qunderscore_character_for_g2_ok_file = 
	    STATIC_SYMBOL("UNDERSCORE-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qunderscore_character_for_g2_ok_file,FIX((SI_Long)12L));
    Qquestion_mark_character_for_g2_ok_file = 
	    STATIC_SYMBOL("QUESTION-MARK-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qquestion_mark_character_for_g2_ok_file,
	    FIX((SI_Long)13L));
    Qperiod_character_for_g2_ok_file = 
	    STATIC_SYMBOL("PERIOD-CHARACTER-FOR-G2-OK-FILE",AB_package);
    SET_SYMBOL_VALUE(Qperiod_character_for_g2_ok_file,FIX((SI_Long)14L));
    Qsymbol_token_match_should_be_case_sensitive_p = 
	    STATIC_SYMBOL("SYMBOL-TOKEN-MATCH-SHOULD-BE-CASE-SENSITIVE-P",
	    AB_package);
    SET_SYMBOL_VALUE(Qsymbol_token_match_should_be_case_sensitive_p,Nil);
    array_constant_58 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)256L));
    ISASET_1(array_constant_58,(SI_Long)0L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)1L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)2L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)3L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)4L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)5L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)6L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)7L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)8L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)9L,FIX((SI_Long)1L));
    ISASET_1(array_constant_58,(SI_Long)10L,FIX((SI_Long)11L));
    ISASET_1(array_constant_58,(SI_Long)11L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)12L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)13L,FIX((SI_Long)10L));
    ISASET_1(array_constant_58,(SI_Long)14L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)15L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)16L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)17L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)18L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)19L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)20L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)21L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)22L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)23L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)24L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)25L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)26L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)27L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)28L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)29L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)30L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)31L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)32L,FIX((SI_Long)1L));
    ISASET_1(array_constant_58,(SI_Long)33L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)34L,FIX((SI_Long)2L));
    ISASET_1(array_constant_58,(SI_Long)35L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)36L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)37L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)38L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)39L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)40L,FIX((SI_Long)3L));
    ISASET_1(array_constant_58,(SI_Long)41L,FIX((SI_Long)4L));
    ISASET_1(array_constant_58,(SI_Long)42L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)43L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)44L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)45L,FIX((SI_Long)7L));
    ISASET_1(array_constant_58,(SI_Long)46L,FIX((SI_Long)14L));
    ISASET_1(array_constant_58,(SI_Long)47L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)48L,FIX((SI_Long)8L));
    ISASET_1(array_constant_58,(SI_Long)49L,FIX((SI_Long)8L));
    ISASET_1(array_constant_58,(SI_Long)50L,FIX((SI_Long)8L));
    ISASET_1(array_constant_58,(SI_Long)51L,FIX((SI_Long)8L));
    ISASET_1(array_constant_58,(SI_Long)52L,FIX((SI_Long)8L));
    ISASET_1(array_constant_58,(SI_Long)53L,FIX((SI_Long)8L));
    ISASET_1(array_constant_58,(SI_Long)54L,FIX((SI_Long)8L));
    ISASET_1(array_constant_58,(SI_Long)55L,FIX((SI_Long)8L));
    ISASET_1(array_constant_58,(SI_Long)56L,FIX((SI_Long)8L));
    ISASET_1(array_constant_58,(SI_Long)57L,FIX((SI_Long)8L));
    ISASET_1(array_constant_58,(SI_Long)58L,FIX((SI_Long)5L));
    ISASET_1(array_constant_58,(SI_Long)59L,FIX((SI_Long)6L));
    ISASET_1(array_constant_58,(SI_Long)60L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)61L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)62L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)63L,FIX((SI_Long)13L));
    ISASET_1(array_constant_58,(SI_Long)64L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)65L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)66L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)67L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)68L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)69L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)70L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)71L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)72L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)73L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)74L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)75L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)76L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)77L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)78L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)79L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)80L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)81L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)82L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)83L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)84L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)85L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)86L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)87L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)88L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)89L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)90L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)91L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)92L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)93L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)94L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)95L,FIX((SI_Long)12L));
    ISASET_1(array_constant_58,(SI_Long)96L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)97L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)98L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)99L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)100L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)101L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)102L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)103L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)104L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)105L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)106L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)107L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)108L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)109L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)110L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)111L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)112L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)113L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)114L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)115L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)116L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)117L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)118L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)119L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)120L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)121L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)122L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)123L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)124L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)125L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)126L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)127L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)128L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)129L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)130L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)131L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)132L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)133L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)134L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)135L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)136L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)137L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)138L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)139L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)140L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)141L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)142L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)143L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)144L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)145L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)146L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)147L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)148L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)149L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)150L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)151L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)152L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)153L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)154L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)155L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)156L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)157L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)158L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)159L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)160L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)161L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)162L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)163L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)164L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)165L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)166L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)167L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)168L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)169L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)170L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)171L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)172L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)173L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)174L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)175L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)176L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)177L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)178L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)179L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)180L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)181L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)182L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)183L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)184L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)185L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)186L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)187L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)188L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)189L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)190L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)191L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)192L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)193L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)194L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)195L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)196L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)197L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)198L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)199L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)200L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)201L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)202L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)203L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)204L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)205L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)206L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)207L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)208L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)209L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)210L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)211L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)212L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)213L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)214L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)215L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)216L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)217L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)218L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)219L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)220L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)221L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)222L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)223L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)224L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)225L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)226L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)227L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)228L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)229L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)230L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)231L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)232L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)233L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)234L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)235L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)236L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)237L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)238L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)239L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)240L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)241L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)242L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)243L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)244L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)245L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)246L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)247L,FIX((SI_Long)0L));
    ISASET_1(array_constant_58,(SI_Long)248L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)249L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)250L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)251L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)252L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)253L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)254L,FIX((SI_Long)9L));
    ISASET_1(array_constant_58,(SI_Long)255L,FIX((SI_Long)9L));
    Character_table_for_g2_ok_file = array_constant_58;
    Keof = STATIC_SYMBOL("EOF",Pkeyword);
    Qg2_defstruct_structure_name_ok_file_token_g2_struct = 
	    STATIC_SYMBOL("OK-FILE-TOKEN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qok_file_token = STATIC_SYMBOL("OK-FILE-TOKEN",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_ok_file_token_g2_struct,
	    Qok_file_token,Qab_name_of_unique_structure_type);
    mutate_global_property(Qok_file_token,
	    Qg2_defstruct_structure_name_ok_file_token_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_ok_file_token == UNBOUND)
	The_type_description_of_ok_file_token = Nil;
    string_constant_225 = 
	    STATIC_STRING("43Dy8m83lCy1n83lCy8n8k1l8n0000001l1n8y83-5=y1m83-1hy83-Eeykpk0k0");
    temp = The_type_description_of_ok_file_token;
    The_type_description_of_ok_file_token = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_225));
    mutate_global_property(Qg2_defstruct_structure_name_ok_file_token_g2_struct,
	    The_type_description_of_ok_file_token,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qok_file_token,
	    The_type_description_of_ok_file_token,Qtype_description_of_type);
    Qoutstanding_ok_file_token_count = 
	    STATIC_SYMBOL("OUTSTANDING-OK-FILE-TOKEN-COUNT",AB_package);
    Qok_file_token_structure_memory_usage = 
	    STATIC_SYMBOL("OK-FILE-TOKEN-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_226 = STATIC_STRING("1q83lCy8s83-hXy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_ok_file_token_count);
    push_optimized_constant(Qok_file_token_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_226));
    Qchain_of_available_ok_file_tokens = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-OK-FILE-TOKENS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_ok_file_tokens,
	    Chain_of_available_ok_file_tokens);
    record_system_variable(Qchain_of_available_ok_file_tokens,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qok_file_token_count = STATIC_SYMBOL("OK-FILE-TOKEN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qok_file_token_count,Ok_file_token_count);
    record_system_variable(Qok_file_token_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_ok_file_tokens_vector == UNBOUND)
	Chain_of_available_ok_file_tokens_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qok_file_token_structure_memory_usage,
	    STATIC_FUNCTION(ok_file_token_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_ok_file_token_count,
	    STATIC_FUNCTION(outstanding_ok_file_token_count,NIL,FALSE,0,0));
    reclaim_structure_for_ok_file_token_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_ok_file_token,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qok_file_token,
	    reclaim_structure_for_ok_file_token_1);
    Qavailable_ok_file_token_conses = 
	    STATIC_SYMBOL("AVAILABLE-OK-FILE-TOKEN-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_ok_file_token_conses,
	    Available_ok_file_token_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_ok_file_token_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_ok_file_token_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-OK-FILE-TOKEN-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_ok_file_token_conses_tail,
	    Available_ok_file_token_conses_tail);
    record_system_variable(Qavailable_ok_file_token_conses_tail,
	    Qutilities1,Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_ok_file_token_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-OK-FILE-TOKEN-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_ok_file_token_conses_vector,
	    Available_ok_file_token_conses_vector);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_95 = STATIC_CONS(Qnil,Qnil);
    list_constant_96 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qmake_thread_array,list_constant_95);
    record_system_variable(Qavailable_ok_file_token_conses_vector,
	    Qutilities1,list_constant_96,Qnil,Qt,Qnil,Qnil);
    Qavailable_ok_file_token_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-OK-FILE-TOKEN-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_ok_file_token_conses_tail_vector,
	    Available_ok_file_token_conses_tail_vector);
    record_system_variable(Qavailable_ok_file_token_conses_tail_vector,
	    Qutilities1,list_constant_96,Qnil,Qt,Qnil,Qnil);
    Qok_file_token_cons_counter_vector = 
	    STATIC_SYMBOL("OK-FILE-TOKEN-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qok_file_token_cons_counter_vector,
	    Ok_file_token_cons_counter_vector);
    list_constant_97 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qok_file_token_cons_counter_vector,Qutilities1,
	    list_constant_97,Qnil,Qt,Qnil,Qnil);
    Qok_file_token_cons_counter = 
	    STATIC_SYMBOL("OK-FILE-TOKEN-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qok_file_token_cons_counter,
	    Ok_file_token_cons_counter);
    record_system_variable(Qok_file_token_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_ok_file_token_conses = 
	    STATIC_SYMBOL("OUTSTANDING-OK-FILE-TOKEN-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_ok_file_token_conses,
	    STATIC_FUNCTION(outstanding_ok_file_token_conses,NIL,FALSE,0,0));
    Qok_file_token_cons_memory_usage = 
	    STATIC_SYMBOL("OK-FILE-TOKEN-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qok_file_token_cons_memory_usage,
	    STATIC_FUNCTION(ok_file_token_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_227 = STATIC_STRING("1q83-hWy9k83-hVy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_ok_file_token_conses);
    push_optimized_constant(Qok_file_token_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_227));
    Klist = STATIC_SYMBOL("LIST",Pkeyword);
    Killegal = STATIC_SYMBOL("ILLEGAL",Pkeyword);
    Ksymbol = STATIC_SYMBOL("SYMBOL",Pkeyword);
    Kclose_paren = STATIC_SYMBOL("CLOSE-PAREN",Pkeyword);
    Kcolon = STATIC_SYMBOL("COLON",Pkeyword);
    Ksemicolon = STATIC_SYMBOL("SEMICOLON",Pkeyword);
    Kstring = STATIC_SYMBOL("STRING",Pkeyword);
    list_constant_6 = STATIC_LIST((SI_Long)5L,CHR('@'),CHR('~'),CHR('\\'),
	    CHR('\n'),CHR('\r'));
    array_constant_12 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    Kinteger = STATIC_SYMBOL("INTEGER",Pkeyword);
    array_constant_28 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)57344L);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    list_constant_98 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_114 = STATIC_LIST_STAR((SI_Long)3L,array_constant_28,
	    Qname,list_constant_98);
    array_constant_29 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)57344L);
    list_constant_99 = STATIC_CONS(Qstring,Qnil);
    list_constant_115 = STATIC_LIST_STAR((SI_Long)3L,array_constant_29,
	    Qmachine_id,list_constant_99);
    array_constant_30 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)10L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)23L,(SI_Long)57344L);
    Qlist_of = STATIC_SYMBOL("LIST-OF",AB_package);
    array_constant_59 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)0L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)15L,(SI_Long)57344L);
    array_constant_60 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)0L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)10L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)23L,(SI_Long)57344L);
    array_constant_61 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)15L,(SI_Long)57344L);
    array_constant_62 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)15L,(SI_Long)57344L);
    array_constant_63 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)15L,(SI_Long)57344L);
    array_constant_64 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)7L,(SI_Long)57344L);
    array_constant_65 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)7L,(SI_Long)57344L);
    array_constant_66 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)7L,(SI_Long)57344L);
    array_constant_67 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)0L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)15L,(SI_Long)57344L);
    array_constant_68 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)0L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)15L,(SI_Long)57344L);
    array_constant_69 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)15L,(SI_Long)57344L);
    array_constant_70 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)7L,(SI_Long)57344L);
    array_constant_71 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)7L,(SI_Long)57344L);
    array_constant_72 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)7L,(SI_Long)57344L);
    array_constant_73 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)15L,(SI_Long)57344L);
    array_constant_74 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)0L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)7L,(SI_Long)57344L);
    array_constant_75 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)0L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)7L,(SI_Long)57344L);
    array_constant_76 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)7L,(SI_Long)57344L);
    array_constant_77 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)7L,(SI_Long)57344L);
    list_constant_100 = STATIC_LIST((SI_Long)20L,Qmember,array_constant_59,
	    array_constant_60,array_constant_61,array_constant_62,
	    array_constant_63,array_constant_64,array_constant_65,
	    array_constant_66,array_constant_67,array_constant_68,
	    array_constant_69,array_constant_70,array_constant_71,
	    array_constant_72,array_constant_73,array_constant_74,
	    array_constant_75,array_constant_76,array_constant_77);
    list_constant_101 = STATIC_LIST((SI_Long)2L,Qlist_of,list_constant_100);
    list_constant_116 = STATIC_LIST((SI_Long)3L,array_constant_30,
	    Qauthorized_products,list_constant_101);
    array_constant_31 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)10L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)15L,(SI_Long)63L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)23L,(SI_Long)57344L);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qlist_structure = STATIC_SYMBOL("LIST-STRUCTURE",AB_package);
    array_constant_78 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)7L,(SI_Long)57344L);
    list_constant_102 = STATIC_LIST((SI_Long)2L,Qmember,array_constant_78);
    array_constant_79 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)0L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)7L,(SI_Long)57344L);
    array_constant_80 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)7L,(SI_Long)57344L);
    array_constant_81 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)7L,(SI_Long)57344L);
    array_constant_82 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)7L,(SI_Long)57344L);
    array_constant_83 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)2L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)7L,(SI_Long)57344L);
    array_constant_84 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)0L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)7L,(SI_Long)57344L);
    array_constant_85 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)0L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)7L,(SI_Long)57344L);
    array_constant_86 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)7L,(SI_Long)57344L);
    array_constant_87 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)7L,(SI_Long)57344L);
    array_constant_88 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)7L,(SI_Long)57344L);
    array_constant_89 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)7L,(SI_Long)57344L);
    array_constant_90 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)7L,(SI_Long)57344L);
    list_constant_103 = STATIC_LIST((SI_Long)13L,Qmember,array_constant_79,
	    array_constant_80,array_constant_81,array_constant_82,
	    array_constant_83,array_constant_84,array_constant_85,
	    array_constant_86,array_constant_87,array_constant_88,
	    array_constant_89,array_constant_90);
    array_constant_91 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_91,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_91,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_91,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_91,(SI_Long)7L,(SI_Long)57344L);
    list_constant_104 = STATIC_LIST((SI_Long)2L,Qmember,array_constant_91);
    list_constant_105 = STATIC_CONS(Qinteger,Qnil);
    list_constant_106 = STATIC_LIST_STAR((SI_Long)9L,Qlist_structure,
	    list_constant_102,Qinteger,list_constant_103,Qinteger,
	    list_constant_104,Qinteger,list_constant_103,list_constant_105);
    list_constant_107 = STATIC_LIST((SI_Long)3L,Qab_or,Qnull,
	    list_constant_106);
    list_constant_117 = STATIC_LIST((SI_Long)3L,array_constant_31,
	    Qexpiration_date_qm,list_constant_107);
    array_constant_32 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)15L,(SI_Long)57344L);
    Qauthorization = STATIC_SYMBOL("AUTHORIZATION",AB_package);
    list_constant_108 = STATIC_CONS(Qlist_of,list_constant_105);
    list_constant_118 = STATIC_LIST((SI_Long)3L,array_constant_32,
	    Qauthorization,list_constant_108);
    array_constant_92 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)6L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)14L,(SI_Long)63L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_92,(SI_Long)23L,(SI_Long)57344L);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    list_constant_119 = STATIC_LIST((SI_Long)3L,array_constant_92,
	    Qmake_g2_secure_qm,Qboolean);
    array_constant_33 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)10L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)11L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)12L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)13L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)17L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)31L,(SI_Long)57344L);
    list_constant_109 = STATIC_LIST_STAR((SI_Long)3L,Qinteger,Qinteger,
	    list_constant_105);
    list_constant_110 = STATIC_LIST_STAR((SI_Long)3L,Qlist_structure,
	    Qsymbol,list_constant_109);
    list_constant_111 = STATIC_LIST_STAR((SI_Long)11L,Qlist_structure,
	    Qsymbol,list_constant_102,Qinteger,list_constant_103,Qinteger,
	    list_constant_104,Qinteger,list_constant_103,Qinteger,
	    list_constant_109);
    list_constant_112 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_110,
	    list_constant_111);
    list_constant_113 = STATIC_LIST((SI_Long)2L,Qlist_of,list_constant_112);
    list_constant_120 = STATIC_LIST((SI_Long)3L,array_constant_33,
	    Qauthorized_kb_packages,list_constant_113);
    array_constant_34 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)8L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)19L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)24L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)27L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)29L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)39L,(SI_Long)57344L);
    list_constant_121 = STATIC_LIST_STAR((SI_Long)3L,array_constant_34,
	    Qnumber_of_processes_authorized,list_constant_105);
    array_constant_35 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)10L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)14L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)16L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)17L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)18L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)28L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)31L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)36L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)37L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)40L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)42L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)43L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)44L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)45L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)46L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)47L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)48L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)49L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)50L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)51L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)52L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)53L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)54L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)56L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)62L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)63L,(SI_Long)57344L);
    list_constant_122 = STATIC_LIST_STAR((SI_Long)3L,array_constant_35,
	    Qmaximum_number_of_concurrent_floating_telewindows_allowed,
	    list_constant_105);
    array_constant_36 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)10L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)14L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)16L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)17L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)18L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)28L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)31L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)36L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)37L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)39L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)40L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)41L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)42L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)43L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)44L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)45L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)46L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)47L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)48L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)54L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)55L,(SI_Long)57344L);
    Qmaximum_number_of_concurrent_floating_tw2_allowed = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-CONCURRENT-FLOATING-TW2-ALLOWED",
	    AB_package);
    list_constant_123 = STATIC_LIST_STAR((SI_Long)3L,array_constant_36,
	    Qmaximum_number_of_concurrent_floating_tw2_allowed,
	    list_constant_105);
    array_constant_93 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_93,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_93,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_93,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_93,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_93,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_93,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_93,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_93,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_93,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_93,(SI_Long)15L,(SI_Long)57344L);
    Qcustomer = STATIC_SYMBOL("CUSTOMER",AB_package);
    list_constant_124 = STATIC_LIST_STAR((SI_Long)3L,array_constant_93,
	    Qcustomer,list_constant_98);
    array_constant_94 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)6L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_94,(SI_Long)15L,(SI_Long)57344L);
    Qserial_number = STATIC_SYMBOL("SERIAL-NUMBER",AB_package);
    list_constant_125 = STATIC_LIST_STAR((SI_Long)3L,array_constant_94,
	    Qserial_number,list_constant_99);
    array_constant_95 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)12L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_95,(SI_Long)23L,(SI_Long)57344L);
    Qinstallation_code = STATIC_SYMBOL("INSTALLATION-CODE",AB_package);
    list_constant_126 = STATIC_LIST_STAR((SI_Long)3L,array_constant_95,
	    Qinstallation_code,list_constant_99);
    list_constant_127 = STATIC_LIST((SI_Long)13L,list_constant_114,
	    list_constant_115,list_constant_116,list_constant_117,
	    list_constant_118,list_constant_119,list_constant_120,
	    list_constant_121,list_constant_122,list_constant_123,
	    list_constant_124,list_constant_125,list_constant_126);
    Slot_pad_descriptions_of_machine_authorization = list_constant_127;
    array_constant_96 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_96,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_96,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_96,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_96,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_96,(SI_Long)4L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_96,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_96,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_96,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_96,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_96,(SI_Long)15L,(SI_Long)57344L);
    Qpassword = STATIC_SYMBOL("PASSWORD",AB_package);
    list_constant_129 = STATIC_LIST_STAR((SI_Long)3L,array_constant_96,
	    Qpassword,list_constant_99);
    array_constant_97 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)4L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)8L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)9L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)16L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_97,(SI_Long)23L,(SI_Long)57344L);
    Qpassword_validity = STATIC_SYMBOL("PASSWORD-VALIDITY",AB_package);
    list_constant_130 = STATIC_LIST_STAR((SI_Long)3L,array_constant_97,
	    Qpassword_validity,list_constant_105);
    array_constant_98 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)14L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_98,(SI_Long)23L,(SI_Long)57344L);
    list_constant_128 = STATIC_CONS(Qlist_of,list_constant_98);
    list_constant_131 = STATIC_LIST((SI_Long)3L,array_constant_98,
	    Qpermitted_user_modes,list_constant_128);
    list_constant_132 = STATIC_LIST((SI_Long)4L,list_constant_114,
	    list_constant_129,list_constant_130,list_constant_131);
    Slot_pad_descriptions_of_user = list_constant_132;
    Qunbound_value_for_ok_reader_1 = 
	    STATIC_SYMBOL("UNBOUND-VALUE-FOR-OK-READER",Qnil);
    if (Unbound_value_for_ok_reader == UNBOUND)
	Unbound_value_for_ok_reader = Qunbound_value_for_ok_reader_1;
    array_constant_13 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    Kbegin_entity = STATIC_SYMBOL("BEGIN-ENTITY",Pkeyword);
    array_constant_14 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    Kend_entity = STATIC_SYMBOL("END-ENTITY",Pkeyword);
    Kattribute = STATIC_SYMBOL("ATTRIBUTE",Pkeyword);
    string_constant_84 = STATIC_STRING("/home/bhyde/junk/test.ok");
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    array_constant_15 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)57344L);
    string_constant_85 = STATIC_STRING("");
    Qproprietary = STATIC_SYMBOL("PROPRIETARY",AB_package);
    array_constant_20 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)57344L);
    array_constant_21 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)57344L);
    list_constant_7 = STATIC_CONS(FIX((SI_Long)32L),Qnil);
    array_constant_23 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)57344L);
    if (Authorizing_ok_pathname == UNBOUND)
	Authorizing_ok_pathname = Nil;
    Qg2passwdexe = STATIC_SYMBOL("G2PASSWDEXE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2passwdexe,G2passwdexe);
    Qinitialize_g2passwdexe = STATIC_SYMBOL("INITIALIZE-G2PASSWDEXE",
	    AB_package);
    list_constant_133 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_g2passwdexe);
    record_system_variable(Qg2passwdexe,Qsequences2,list_constant_133,Qnil,
	    Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_g2passwdexe,
	    STATIC_FUNCTION(initialize_g2passwdexe,NIL,FALSE,0,0));
    Qconvert_file_strings_to_uppercase_p = 
	    STATIC_SYMBOL("CONVERT-FILE-STRINGS-TO-UPPERCASE-P",AB_package);
    Qunix = STATIC_SYMBOL("UNIX",AB_package);
    array_constant_24 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)57344L);
    Qg2passwdexe_is_executable_p = 
	    STATIC_SYMBOL("G2PASSWDEXE-IS-EXECUTABLE-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2passwdexe_is_executable_p,
	    G2passwdexe_is_executable_p);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    list_constant_134 = STATIC_LIST((SI_Long)2L,Qquote,Qunknown);
    record_system_variable(Qg2passwdexe_is_executable_p,Qsequences2,
	    list_constant_134,Qnil,Qnil,Qnil,Qnil);
    Qg2passwdexe_areyouthere_arg = 
	    STATIC_SYMBOL("G2PASSWDEXE-AREYOUTHERE-ARG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2passwdexe_areyouthere_arg,
	    G2passwdexe_areyouthere_arg);
    string_constant_228 = STATIC_STRING("-areyouthere");
    SET_SYMBOL_VALUE(Qg2passwdexe_areyouthere_arg,string_constant_228);
    Qg2passwdexe_areyouthere_good_result = 
	    STATIC_SYMBOL("G2PASSWDEXE-AREYOUTHERE-GOOD-RESULT",AB_package);
    SET_SYMBOL_VALUE(Qg2passwdexe_areyouthere_good_result,FIX((SI_Long)111L));
    string_constant_86 = STATIC_STRING("~a ~a");
    string_constant_87 = 
	    STATIC_STRING("Warning: Cannot execute ~s from G2; password changing will be disabled for the entire G2 session!");
    Qg1 = STATIC_SYMBOL("G1",AB_package);
    Qent = STATIC_SYMBOL("ENT",AB_package);
    array_constant_25 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)26L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)30L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)31L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)32L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)33L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)37L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)38L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)39L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)40L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)41L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)42L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)43L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)45L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)46L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)47L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)49L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)51L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)52L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)53L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)54L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)56L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)57L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)58L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)59L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)60L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)61L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)62L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)63L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)78L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)79L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)11L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)26L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)30L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)32L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)35L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)37L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)39L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)40L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)41L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)43L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)44L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)45L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)46L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)47L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)48L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)49L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)50L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)51L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)52L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)53L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)54L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)55L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)56L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)57L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)58L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)59L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)60L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)61L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)78L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)79L,(SI_Long)57344L);
    array_constant_27 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)17L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)20L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)23L,(SI_Long)57344L);
    string_constant_88 = STATIC_STRING("~%~%---~%~A~%~A~%");
    Qverbose = STATIC_SYMBOL("VERBOSE",AB_package);
    string_constant_89 = STATIC_STRING("~%[~A ~s]~%");
    string_constant_90 = STATIC_STRING("~%~A~%");
    Qstring_equalw = STATIC_SYMBOL("STRING-EQUALW",AB_package);
    string_constant_91 = STATIC_STRING("  ~A:");
    string_constant_92 = STATIC_STRING("~%          ");
    string_constant_93 = STATIC_STRING("OK file must exist and be readable.");
    string_constant_94 = 
	    STATIC_STRING("OK-file-path must specify a valid file name");
    string_constant_95 = 
	    STATIC_STRING("A minus sign can only introduce a comment.");
    string_constant_96 = 
	    STATIC_STRING("Only certain characters may start a new token.");
    string_constant_97 = 
	    STATIC_STRING("Strings must be less than 60 characters.");
    string_constant_98 = 
	    STATIC_STRING("Strings may not contain atsign, tilde, backslash or line terminators.");
    string_constant_99 = 
	    STATIC_STRING("Symbols must be less than 60 characters.");
    string_constant_100 = 
	    STATIC_STRING("Integers must be less than 40 digits.");
    string_constant_101 = STATIC_STRING("Integers contain only digits.");
    string_constant_102 = 
	    STATIC_STRING("Lists must contain less than 60 elements");
    string_constant_103 = STATIC_STRING("Premature end of file.");
    string_constant_104 = 
	    STATIC_STRING("Attribute value pairs must end with a semicolon");
    string_constant_105 = 
	    STATIC_STRING("Attribute values must be integers, lists, or symbols.");
    string_constant_106 = 
	    STATIC_STRING("Bad type for the value of the attribute ~a: ~a~\n           ~%Attribute values must be integers, lists, or symbols.");
    string_constant_107 = STATIC_STRING("Cannot parse statement.");
    string_constant_108 = 
	    STATIC_STRING("The first N characters of file must be \"begin g2-ok-file\".");
    string_constant_109 = 
	    STATIC_STRING("The file must contain one g2-ok-file entity");
    string_constant_110 = 
	    STATIC_STRING("None of the entries in this authorization file has a machine id that matched this machine");
    string_constant_111 = 
	    STATIC_STRING("The machine id in the authorization file does not match the id for this machine.");
    string_constant_112 = 
	    STATIC_STRING("Unexpected element found inside of g2-ok-file-entity.");
    string_constant_113 = 
	    STATIC_STRING("Entity attributes must appear before subentities.");
    string_constant_114 = 
	    STATIC_STRING("Only file-format-version attributes may appear in g2-ok-files.");
    string_constant_115 = STATIC_STRING("Attributes may only appear once.");
    string_constant_116 = STATIC_STRING("Attribute must be an integer.");
    string_constant_117 = 
	    string_append2(STATIC_STRING("This G2 can only read OK files in version ~a format.~\n            ~%The OK file being loaded is in version ~a format and is incompatible~\n            ~%because it contains att"),
	    STATIC_STRING("ributes or codes that your G2 will not understand."));
    string_constant_118 = 
	    STATIC_STRING("The type given on begin and end must match.");
    string_constant_119 = STATIC_STRING("File must be parsable.");
    string_constant_120 = 
	    STATIC_STRING("OK file must contain at least one machine authorization.");
    string_constant_121 = STATIC_STRING("File syntax must be correct.");
    string_constant_122 = 
	    STATIC_STRING("Users must have some permitted user-modes.");
    string_constant_123 = STATIC_STRING("Proprietary is not a user-mode.");
    string_constant_124 = STATIC_STRING("A machine-id attribute is required.");
    string_constant_125 = 
	    STATIC_STRING("A authorization attribute is required.");
    string_constant_126 = 
	    STATIC_STRING("The machine ID must meet certain rules.");
    string_constant_127 = STATIC_STRING("The date range must be reasonable.");
    string_constant_128 = STATIC_STRING("Illegal attribute name.");
    string_constant_129 = STATIC_STRING("Unknown attribute: \"~a\"");
    string_constant_130 = STATIC_STRING("Attribute value is not right.");
    string_constant_131 = 
	    STATIC_STRING("The value ~a is the wrong type for the attribute ~a.~\n            ~%It should be of type ~a");
    string_constant_132 = STATIC_STRING("Duplicate attributes are illegal.");
    string_constant_133 = 
	    STATIC_STRING("This instance of attribute ~a is a duplicate");
    string_constant_134 = 
	    STATIC_STRING("You were already authorized.~%You are still authorized.~%Meanwhile the authorization found in the OK file was wrong.");
    string_constant_135 = 
	    STATIC_STRING("The authorization is not correct. Please check it and try again.");
    string_constant_136 = 
	    STATIC_STRING("Limit on number of Floating Telewindows licenses ~\n     exceeded.  Closing unauthorized connection(s) immediately.");
    string_constant_137 = 
	    STATIC_STRING("A connection to ~a Telewindows is being closed immediately ~\n    because it is not permitted to connect to a Development version of G2.");
    string_constant_138 = STATIC_STRING("Bad package authorization.");
    string_constant_139 = 
	    STATIC_STRING("Wrong number of codes in authorization field. There should be five.");
    string_constant_140 = 
	    STATIC_STRING("Premature end of file: some entry was not terminated");
    string_constant_141 = 
	    STATIC_STRING("Unexpected start of an entry: previous entry was not terminated");
    string_constant_142 = 
	    STATIC_STRING("The license to run G2 on this machine has expired.~%");
    string_constant_143 = 
	    STATIC_STRING("The license to use G2 on this machine expires today.~% G2 will not run after today.~%~%");
}
