/* utlts3.c
 * Input file:  utilities3.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "utlts3.h"


DEFINE_VARIABLE_WITH_SYMBOL(No_arg, Qno_arg);

/* NOTIFY-USER-AT-CONSOLE-AND-ON-LOGBOOK */
Object notify_user_at_console_and_on_logbook varargs_1(int, n)
{
    Object notification_as_format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,0);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    END_ARGS_nonrelocating();
    if (EQ(arg1,No_arg))
	notify_user_at_console(1,notification_as_format_string);
    else if (EQ(arg2,No_arg))
	notify_user_at_console(2,notification_as_format_string,arg1);
    else if (EQ(arg3,No_arg))
	notify_user_at_console(3,notification_as_format_string,arg1,arg2);
    else if (EQ(arg4,No_arg))
	notify_user_at_console(4,notification_as_format_string,arg1,arg2,arg3);
    else if (EQ(arg5,No_arg))
	notify_user_at_console(5,notification_as_format_string,arg1,arg2,
		arg3,arg4);
    else if (EQ(arg6,No_arg))
	notify_user_at_console(6,notification_as_format_string,arg1,arg2,
		arg3,arg4,arg5);
    else if (EQ(arg7,No_arg))
	notify_user_at_console(7,notification_as_format_string,arg1,arg2,
		arg3,arg4,arg5,arg6);
    else if (EQ(arg8,No_arg))
	notify_user_at_console(8,notification_as_format_string,arg1,arg2,
		arg3,arg4,arg5,arg6,arg7);
    else if (EQ(arg9,No_arg))
	notify_user_at_console(9,notification_as_format_string,arg1,arg2,
		arg3,arg4,arg5,arg6,arg7,arg8);
    else
	notify_user_at_console(10,notification_as_format_string,arg1,arg2,
		arg3,arg4,arg5,arg6,arg7,arg8,arg9);
    if (EQ(arg1,No_arg))
	return notify_user(1,notification_as_format_string);
    else if (EQ(arg2,No_arg))
	return notify_user(2,notification_as_format_string,arg1);
    else if (EQ(arg3,No_arg))
	return notify_user(3,notification_as_format_string,arg1,arg2);
    else if (EQ(arg4,No_arg))
	return notify_user(4,notification_as_format_string,arg1,arg2,arg3);
    else if (EQ(arg5,No_arg))
	return notify_user(5,notification_as_format_string,arg1,arg2,arg3,
		arg4);
    else if (EQ(arg6,No_arg))
	return notify_user(6,notification_as_format_string,arg1,arg2,arg3,
		arg4,arg5);
    else if (EQ(arg7,No_arg))
	return notify_user(7,notification_as_format_string,arg1,arg2,arg3,
		arg4,arg5,arg6);
    else if (EQ(arg8,No_arg))
	return notify_user(8,notification_as_format_string,arg1,arg2,arg3,
		arg4,arg5,arg6,arg7);
    else if (EQ(arg9,No_arg))
	return notify_user(9,notification_as_format_string,arg1,arg2,arg3,
		arg4,arg5,arg6,arg7,arg8);
    else
	return notify_user(10,notification_as_format_string,arg1,arg2,arg3,
		arg4,arg5,arg6,arg7,arg8,arg9);
}

DEFINE_VARIABLE_WITH_SYMBOL(Write_console_p, Qwrite_console_p);

static Object Qiso_8859_1_gensym_string;  /* iso-8859-1-gensym-string */

/* NOTIFY-USER-AT-CONSOLE */
Object notify_user_at_console varargs_1(int, n)
{
    Object notification_as_format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Object formatted_text_string, gensym_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,1);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    END_ARGS_nonrelocating();
    formatted_text_string = tformat_text_string(10,
	    notification_as_format_string,arg1,arg2,arg3,arg4,arg5,arg6,
	    arg7,arg8,arg9);
    gensym_string = export_text_string(2,formatted_text_string,
	    Qiso_8859_1_gensym_string);
    c_write_string_to_console(gensym_string,Write_console_p ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L));
    reclaim_text_string(formatted_text_string);
    return reclaim_gensym_string(gensym_string);
}

/* NOTIFY-USER-IN-PARENT-WINDOW */
Object notify_user_in_parent_window varargs_1(int, n)
{
    Object notification_as_format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,2);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    END_ARGS_nonrelocating();
    return notify_user_at_console(10,notification_as_format_string,arg1,
	    arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9);
}

DEFINE_VARIABLE_WITH_SYMBOL(Actual_arg, Qactual_arg);

/* C-STRING-TO-GENSYM-STRING */
Object c_string_to_gensym_string(c_string)
    Object c_string;
{
    Object lisp_string, schar_new_value, temp;
    SI_Long length_1, i, ab_loop_bind_;

    x_note_fn_call(32,3);
    length_1 =  !TRUEP(c_string) ? (SI_Long)0L : 
	    IFIX(inline_get_length_of_c_string(c_string));
    lisp_string = obtain_simple_gensym_string(FIX(length_1));
    i = (SI_Long)0L;
    ab_loop_bind_ = length_1;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    schar_new_value = inline_get_c_string_element(c_string,FIX(i));
    SET_ISCHAR(lisp_string,i,ICHAR_CODE(schar_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = lisp_string;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object Floating_zero = UNBOUND;

static Object float_constant;      /* 0.0 */

/* GENERATE-FLOAT-VECTOR */
Object generate_float_vector(length_1)
    Object length_1;
{
    Object array;
    XDeclare_area(1);

    x_note_fn_call(32,4);
    if (PUSH_AREA(Dynamic_area,0))
	array = make_array(5,length_1,Kelement_type,Qdouble_float,
		Kinitial_element,float_constant);
    POP_AREA(0);
    return VALUES_1(array);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_float_array_conses, Qavailable_float_array_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_float_array_conses_tail, Qavailable_float_array_conses_tail);

Object Available_float_array_conses_vector = UNBOUND;

Object Available_float_array_conses_tail_vector = UNBOUND;

Object Float_array_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Float_array_cons_counter, Qfloat_array_cons_counter);

/* OUTSTANDING-FLOAT-ARRAY-CONSES */
Object outstanding_float_array_conses()
{
    Object temp;

    x_note_fn_call(32,5);
    temp = FIXNUM_MINUS(Float_array_cons_counter,
	    length(Available_float_array_conses));
    return VALUES_1(temp);
}

/* FLOAT-ARRAY-CONS-MEMORY-USAGE */
Object float_array_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(32,6);
    temp = FIXNUM_TIMES(Float_array_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-FLOAT-ARRAY-CONS-POOL */
Object replenish_float_array_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(32,7);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qfloat_array_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_float_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_float_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_float_array_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Float_array_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qfloat_array;        /* float-array */

/* FLOAT-ARRAY-CONS-1 */
Object float_array_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(32,8);
    new_cons = ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_float_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_float_array_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_float_array_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qfloat_array);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-FLOAT-ARRAY-LIST-POOL */
Object replenish_float_array_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(32,9);
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
    if (ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_float_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_float_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_float_array_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qfloat_array_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-FLOAT-ARRAY-LIST-1 */
Object make_float_array_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(32,10);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_float_array_conses_vector,
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
	replenish_float_array_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_float_array_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qfloat_array);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_float_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_float_array_conses_tail_vector;
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

/* FLOAT-ARRAY-LIST-2 */
Object float_array_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,11);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_float_array_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qfloat_array);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_float_array_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_float_array_conses_tail_vector;
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

/* FLOAT-ARRAY-LIST-3 */
Object float_array_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,12);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_float_array_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qfloat_array);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_float_array_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_float_array_conses_tail_vector;
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

/* FLOAT-ARRAY-LIST-4 */
Object float_array_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,13);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_float_array_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qfloat_array);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_float_array_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_float_array_conses_tail_vector;
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

/* FLOAT-ARRAY-LIST-TRACE-HOOK */
Object float_array_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(32,14);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-FLOAT-ARRAY-CONSES-1 */
Object copy_tree_using_float_array_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(32,15);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_float_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_float_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_float_array_cons_pool();
	temp_1 = copy_tree_using_float_array_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qfloat_array);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_float_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_float_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_float_array_cons_pool();
	temp_1 = 
		copy_tree_using_float_array_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qfloat_array);
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

/* COPY-LIST-USING-FLOAT-ARRAY-CONSES-1 */
Object copy_list_using_float_array_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(32,16);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_float_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_float_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_float_array_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qfloat_array);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_float_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_float_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_float_array_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qfloat_array);
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

/* RECLAIM-FLOAT-ARRAY-CONS-1 */
Object reclaim_float_array_cons_1(float_array_cons)
    Object float_array_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(32,17);
    inline_note_reclaim_cons(float_array_cons,Qfloat_array);
    if (ISVREF(Available_float_array_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = float_array_cons;
	temp = Available_float_array_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = float_array_cons;
    }
    else {
	temp = Available_float_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = float_array_cons;
	temp = Available_float_array_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = float_array_cons;
    }
    M_CDR(float_array_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-FLOAT-ARRAY-LIST-1 */
Object reclaim_float_array_list_1(float_array_list)
    Object float_array_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(32,18);
    if (float_array_list) {
	last_1 = float_array_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qfloat_array);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = float_array_list;
	    temp = Available_float_array_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = float_array_list;
	    temp = Available_float_array_conses_tail_vector;
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

/* RECLAIM-FLOAT-ARRAY-LIST*-1 */
Object reclaim_float_array_list_star_1(float_array_list)
    Object float_array_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(32,19);
    if (CONSP(float_array_list)) {
	temp = last(float_array_list,_);
	M_CDR(temp) = Nil;
	if (float_array_list) {
	    last_1 = float_array_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qfloat_array);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = float_array_list;
		temp = Available_float_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_float_array_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = float_array_list;
		temp = Available_float_array_conses_tail_vector;
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

/* RECLAIM-FLOAT-ARRAY-TREE-1 */
Object reclaim_float_array_tree_1(tree)
    Object tree;
{
    Object e, e2, float_array_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(32,20);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_float_array_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		float_array_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(float_array_cons,Qfloat_array);
		if (EQ(float_array_cons,e))
		    goto end_1;
		else if ( !TRUEP(float_array_cons))
		    goto end_1;
		else
		    float_array_cons = CDR(float_array_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_float_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_float_array_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_float_array_conses_tail_vector;
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

/* DELETE-FLOAT-ARRAY-ELEMENT-1 */
Object delete_float_array_element_1(element,float_array_list)
    Object element, float_array_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(32,21);
    if (float_array_list) {
	if (EQ(element,M_CAR(float_array_list))) {
	    temp = CDR(float_array_list);
	    inline_note_reclaim_cons(float_array_list,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = float_array_list;
		temp_1 = Available_float_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = float_array_list;
	    }
	    else {
		temp_1 = Available_float_array_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = float_array_list;
		temp_1 = Available_float_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = float_array_list;
	    }
	    M_CDR(float_array_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = float_array_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_float_array_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_float_array_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_float_array_conses_tail_vector;
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
	    temp = float_array_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-FLOAT-ARRAY-CONS-1 */
Object delete_float_array_cons_1(float_array_cons,float_array_list)
    Object float_array_cons, float_array_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(32,22);
    if (EQ(float_array_cons,float_array_list))
	temp = CDR(float_array_list);
    else {
	l_trailer_qm = Nil;
	l = float_array_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,float_array_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = float_array_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_float_array_cons_1(float_array_cons);
    return VALUES_1(temp);
}

/* ALLOCATE-INITIAL-VECTOR-OF-SIMPLE-FLOAT-ARRAY-POOLS */
Object allocate_initial_vector_of_simple_float_array_pools()
{
    x_note_fn_call(32,23);
    return make_array(3,
	    FIXNUM_ADD1(Maximum_managed_simple_float_array_size),
	    Kinitial_element,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);

DEFINE_VARIABLE_WITH_SYMBOL(Vector_of_oversized_simple_float_array_pools, Qvector_of_oversized_simple_float_array_pools);

DEFINE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);

DEFINE_VARIABLE_WITH_SYMBOL(Created_oversized_simple_float_array_pool_arrays, Qcreated_oversized_simple_float_array_pool_arrays);

/* OUTSTANDING-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS */
Object outstanding_simple_float_array_pool_arrays()
{
    Object incff_1_arg;
    SI_Long vectors_in_pools, index_1;

    x_note_fn_call(32,24);
    vectors_in_pools = (SI_Long)0L;
    index_1 = (SI_Long)1L;
  next_loop:
    if (index_1 > IFIX(Maximum_managed_simple_float_array_size))
	goto end_loop;
    incff_1_arg = length(ISVREF(Vector_of_simple_float_array_pools,index_1));
    vectors_in_pools = vectors_in_pools + IFIX(incff_1_arg);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(IFIX(Created_simple_float_array_pool_arrays) - 
	    vectors_in_pools));
    return VALUES_1(Qnil);
}

/* OUTSTANDING-OVERSIZED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS */
Object outstanding_oversized_simple_float_array_pool_arrays()
{
    Object incff_1_arg;
    SI_Long vectors_in_pools, index_1;

    x_note_fn_call(32,25);
    vectors_in_pools = (SI_Long)0L;
    index_1 = (SI_Long)1L;
  next_loop:
    if (index_1 > IFIX(Maximum_managed_simple_float_array_size))
	goto end_loop;
    incff_1_arg = 
	    length(ISVREF(Vector_of_oversized_simple_float_array_pools,
	    index_1));
    vectors_in_pools = vectors_in_pools + IFIX(incff_1_arg);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(IFIX(Created_oversized_simple_float_array_pool_arrays) 
	    - vectors_in_pools));
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);

DEFINE_VARIABLE_WITH_SYMBOL(Oversized_simple_float_array_pool_memory_usage, Qoversized_simple_float_array_pool_memory_usage);

/* SFLAP-MEMORY-USAGE */
Object sflap_memory_usage()
{
    x_note_fn_call(32,26);
    return VALUES_1(Simple_float_array_pool_memory_usage);
}

/* OVERSIZED-SFLAP-MEMORY-USAGE */
Object oversized_sflap_memory_usage()
{
    x_note_fn_call(32,27);
    return VALUES_1(Oversized_simple_float_array_pool_memory_usage);
}

Object Replenished_simple_float_array_size_limit = UNBOUND;

Object Replenished_simple_float_arrays_to_make_at_a_time = UNBOUND;

static Object Qmanaged_simple_float_array;  /* managed-simple-float-array */

/* ALLOCATE-MANAGED-SIMPLE-FLOAT-ARRAY */
Object allocate_managed_simple_float_array(requested_length_init)
    Object requested_length_init;
{
    Object vector_of_pools, available_array_cons_qm, array, temp, svref_arg_2;
    Object result_1, new_vector_list, new_vector_cons, temp_1;
    SI_Long requested_length, length_1, index_1;
    char oversized_qm;

    x_note_fn_call(32,28);
    requested_length = IFIX(requested_length_init);
    oversized_qm = requested_length > 
	    IFIX(Maximum_managed_simple_float_array_size);
    length_1 = oversized_qm && (requested_length & (SI_Long)1023L) != 
	    (SI_Long)0L ? (requested_length & (SI_Long)-1024L) + 
	    (SI_Long)1024L : requested_length;
    vector_of_pools = oversized_qm ? 
	    Vector_of_oversized_simple_float_array_pools : 
	    Vector_of_simple_float_array_pools;
    index_1 = oversized_qm ? length_1 >>  -  - (SI_Long)10L : length_1;
    available_array_cons_qm = ISVREF(vector_of_pools,index_1);
    if (available_array_cons_qm) {
	array = M_CAR(available_array_cons_qm);
	temp = M_CDR(available_array_cons_qm);
	ISVREF(vector_of_pools,index_1) = temp;
	inline_note_reclaim_cons(available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = available_array_cons_qm;
	}
	M_CDR(available_array_cons_qm) = Nil;
	result_1 = array;
    }
    else if (length_1 <= IFIX(Replenished_simple_float_array_size_limit) 
	    && length_1 <= IFIX(Maximum_managed_simple_float_array_size)) {
	new_vector_list = 
		make_float_array_list_1(FIXNUM_SUB1(Replenished_simple_vectors_to_make_at_a_time));
	new_vector_cons = new_vector_list;
      next_loop:
	if ( !TRUEP(new_vector_cons))
	    goto end_loop;
	temp = generate_float_vector(FIX(length_1));
	M_CAR(new_vector_cons) = temp;
	new_vector_cons = M_CDR(new_vector_cons);
	goto next_loop;
      end_loop:
	ISVREF(vector_of_pools,index_1) = new_vector_list;
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		Replenished_simple_float_arrays_to_make_at_a_time);
	temp_1 = Replenished_simple_float_arrays_to_make_at_a_time;
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		FIXNUM_TIMES(temp_1,
		bytes_per_double_float_simple_array(FIX(length_1))));
	result_1 = generate_float_vector(FIX(length_1));
    }
    else if ( !oversized_qm) {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX(length_1)));
	result_1 = generate_float_vector(FIX(length_1));
    }
    else {
	atomic_incff_symval(Qcreated_oversized_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qoversized_simple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX(length_1)));
	result_1 = generate_float_vector(FIX(length_1));
    }
    inline_note_allocate_cons(result_1,Qmanaged_simple_float_array);
    return VALUES_1(result_1);
}

/* ALLOCATE-MANAGED-SIMPLE-FLOAT-ARRAY-OF-LENGTH-1 */
Object allocate_managed_simple_float_array_of_length_1()
{
    Object available_array_cons_qm, array, temp, temp_1, result_1;
    Object new_vector_list, new_vector_cons;

    x_note_fn_call(32,29);
    available_array_cons_qm = ISVREF(Vector_of_simple_float_array_pools,
	    (SI_Long)1L);
    if (available_array_cons_qm) {
	array = M_CAR(available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = available_array_cons_qm;
	}
	M_CDR(available_array_cons_qm) = Nil;
	result_1 = array;
    }
    else {
	new_vector_list = make_float_array_list_1(FIX((SI_Long)9L));
	new_vector_cons = new_vector_list;
      next_loop:
	if ( !TRUEP(new_vector_cons))
	    goto end_loop;
	temp = generate_float_vector(FIX((SI_Long)1L));
	M_CAR(new_vector_cons) = temp;
	new_vector_cons = M_CDR(new_vector_cons);
	goto next_loop;
      end_loop:
	temp = Vector_of_simple_float_array_pools;
	SVREF(temp,FIX((SI_Long)1L)) = new_vector_list;
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)10L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		FIX((SI_Long)10L * 
		IFIX(bytes_per_double_float_simple_array(FIX((SI_Long)1L)))));
	result_1 = generate_float_vector(FIX((SI_Long)1L));
    }
    inline_note_allocate_cons(result_1,Qmanaged_simple_float_array);
    return VALUES_1(result_1);
}

/* RECLAIM-MANAGED-SIMPLE-FLOAT-ARRAY */
Object reclaim_managed_simple_float_array(managed_simple_float_array)
    Object managed_simple_float_array;
{
    Object vector_of_pools, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol;
    SI_Long length_1, index_1;
    char oversized_qm;

    x_note_fn_call(32,30);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_simple_float_array));
    oversized_qm = length_1 > IFIX(Maximum_managed_simple_float_array_size);
    vector_of_pools = oversized_qm ? 
	    Vector_of_oversized_simple_float_array_pools : 
	    Vector_of_simple_float_array_pools;
    index_1 = oversized_qm ? length_1 >>  -  - (SI_Long)10L : length_1;
    inline_note_reclaim_cons(managed_simple_float_array,
	    Qmanaged_simple_float_array);
    new_cons = ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_float_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_float_array_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_float_array_cons_pool();
    M_CAR(gensymed_symbol) = managed_simple_float_array;
    temp = ISVREF(vector_of_pools,index_1);
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qfloat_array);
    ISVREF(vector_of_pools,index_1) = gensymed_symbol;
    return VALUES_1(Nil);
}

/* RECLAIM-MANAGED-SIMPLE-FLOAT-ARRAY-OF-LENGTH-1 */
Object reclaim_managed_simple_float_array_of_length_1(managed_simple_float_array)
    Object managed_simple_float_array;
{
    Object svref_arg_1, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(32,31);
    inline_note_reclaim_cons(managed_simple_float_array,
	    Qmanaged_simple_float_array);
    svref_arg_1 = Vector_of_simple_float_array_pools;
    new_cons = ISVREF(Available_float_array_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_float_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_float_array_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_float_array_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_float_array_cons_pool();
    M_CAR(gensymed_symbol) = managed_simple_float_array;
    temp = ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qfloat_array);
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = gensymed_symbol;
    return VALUES_1(Nil);
}

Object Managed_float_array_unique_marker = UNBOUND;

/* ALLOCATE-MANAGED-FLOAT-ARRAY */
Object allocate_managed_float_array varargs_1(int, n)
{
    Object length_1;
    Object make_exactly, full_size_buffers, size_of_partial_buffer;
    Object spine_vector, svref_new_value;
    SI_Long gensymed_symbol, gensymed_symbol_1, total_buffers;
    SI_Long full_buffer_index, ab_loop_bind_, svref_arg_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(32,32);
    INIT_ARGS_nonrelocating();
    length_1 = REQUIRED_ARG_nonrelocating();
    make_exactly = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    result = chestnut_floorf_function(length_1,
	    Maximum_managed_float_array_buffer_size);
    MVS_2(result,full_size_buffers,size_of_partial_buffer);
    gensymed_symbol = IFIX(full_size_buffers);
    gensymed_symbol_1 = IFIX(size_of_partial_buffer) > (SI_Long)0L ? 
	    (SI_Long)1L : (SI_Long)0L;
    total_buffers = gensymed_symbol + gensymed_symbol_1;
    spine_vector = 
	    allocate_managed_simple_vector_for_float_array(make_exactly ? 
	    FIX(total_buffers + (SI_Long)2L) : 
	    buffer_size_for_partial_buffer(FIX(total_buffers + 
	    (SI_Long)2L),Managed_array_allocation_schemes));
    svref_new_value = Managed_float_array_unique_marker;
    SVREF(spine_vector,FIX((SI_Long)0L)) = svref_new_value;
    SVREF(spine_vector,FIX((SI_Long)1L)) = length_1;
    full_buffer_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(full_size_buffers);
  next_loop:
    if (full_buffer_index >= ab_loop_bind_)
	goto end_loop;
    svref_arg_2 = full_buffer_index + (SI_Long)2L;
    svref_new_value = 
	    allocate_managed_simple_float_array(Maximum_managed_float_array_buffer_size);
    ISVREF(spine_vector,svref_arg_2) = svref_new_value;
    full_buffer_index = full_buffer_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (IFIX(size_of_partial_buffer) > (SI_Long)0L) {
	svref_arg_2 = total_buffers - (SI_Long)1L + (SI_Long)2L;
	svref_new_value = allocate_managed_simple_float_array(make_exactly 
		? size_of_partial_buffer : 
		buffer_size_for_partial_buffer(size_of_partial_buffer,
		Managed_array_allocation_schemes));
	ISVREF(spine_vector,svref_arg_2) = svref_new_value;
    }
    return VALUES_1(spine_vector);
}

/* RECLAIM-MANAGED-FLOAT-ARRAY */
Object reclaim_managed_float_array(managed_float_array)
    Object managed_float_array;
{
    Object length_1, full_buffers, remainder_1, buffer;
    SI_Long buffer_count, buffer_index, ab_loop_bind_;
    Object result;

    x_note_fn_call(32,33);
    length_1 = ISVREF(managed_float_array,(SI_Long)1L);
    result = chestnut_floorf_function(length_1,
	    Maximum_managed_float_array_buffer_size);
    MVS_2(result,full_buffers,remainder_1);
    buffer_count = IFIX(remainder_1) > (SI_Long)0L ? 
	    IFIX(FIXNUM_ADD1(full_buffers)) : IFIX(full_buffers);
    buffer_index = (SI_Long)0L;
    ab_loop_bind_ = buffer_count;
    buffer = Nil;
  next_loop:
    if (buffer_index >= ab_loop_bind_)
	goto end_loop;
    buffer = ISVREF(managed_float_array,buffer_index + (SI_Long)2L);
    reclaim_managed_simple_float_array(buffer);
    buffer_index = buffer_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(managed_float_array,FIX((SI_Long)0L)) = Nil;
    reclaim_managed_simple_vector_for_float_array(managed_float_array);
    return VALUES_1(Nil);
}

/* COPY-SIMPLE-FLOAT-ARRAY-PORTION-FUNCTION */
Object copy_simple_float_array_portion_function(source_simple_float_array,
	    source_index,element_count,destination_simple_float_array,
	    destination_index)
    Object source_simple_float_array, source_index, element_count;
    Object destination_simple_float_array, destination_index;
{
    Object gensymed_symbol, gensymed_symbol_3;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(32,34);
    gensymed_symbol = source_simple_float_array;
    gensymed_symbol_1 = IFIX(source_index);
    gensymed_symbol_2 = gensymed_symbol_1 + IFIX(element_count);
    gensymed_symbol_3 = destination_simple_float_array;
    gensymed_symbol_4 = IFIX(destination_index);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop:
	if ( !(gensymed_symbol_1 < gensymed_symbol_2))
	    goto end_loop;
	aref_new_value = DFLOAT_ISAREF_1(gensymed_symbol,gensymed_symbol_1);
	DFLOAT_ISASET_1(gensymed_symbol_3,gensymed_symbol_4,aref_new_value);
	gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
	gensymed_symbol_4 = gensymed_symbol_4 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* ADJUST-MANAGED-FLOAT-ARRAY */
Object adjust_managed_float_array varargs_1(int, n)
{
    Object managed_float_array, new_length;
    Object dont_copy, old_length;
    SI_Long temp, old_full_buffers, old_remainder, new_full_buffers;
    SI_Long new_remainder, old_total_buffers, new_total_buffers;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,35);
    INIT_ARGS_nonrelocating();
    managed_float_array = REQUIRED_ARG_nonrelocating();
    new_length = REQUIRED_ARG_nonrelocating();
    dont_copy = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    old_length = ISVREF(managed_float_array,(SI_Long)1L);
    if (FIXNUM_EQ(new_length,old_length))
	return VALUES_1(managed_float_array);
    temp = IFIX(old_length) / IFIX(Maximum_managed_float_array_buffer_size);
    old_full_buffers = temp;
    temp = IFIX(old_length) % IFIX(Maximum_managed_float_array_buffer_size);
    old_remainder = temp;
    temp = IFIX(new_length) / IFIX(Maximum_managed_float_array_buffer_size);
    new_full_buffers = temp;
    temp = IFIX(new_length) % IFIX(Maximum_managed_float_array_buffer_size);
    new_remainder = temp;
    old_total_buffers = old_remainder > (SI_Long)0L ? old_full_buffers + 
	    (SI_Long)1L : old_full_buffers;
    new_total_buffers = new_remainder > (SI_Long)0L ? new_full_buffers + 
	    (SI_Long)1L : new_full_buffers;
    if (new_total_buffers == old_total_buffers) {
	adjust_final_buffer_of_managed_float_array(managed_float_array,
		dont_copy,FIX(new_total_buffers),old_remainder == 
		(SI_Long)0L ? Maximum_managed_float_array_buffer_size : 
		FIX(old_remainder),new_remainder == (SI_Long)0L ? 
		Maximum_managed_float_array_buffer_size : FIX(new_remainder));
	SVREF(managed_float_array,FIX((SI_Long)1L)) = new_length;
	return VALUES_1(managed_float_array);
    }
    else if (new_total_buffers > old_total_buffers)
	return grow_managed_float_array(managed_float_array,dont_copy,
		FIX(old_full_buffers),FIX(old_remainder),
		FIX(old_total_buffers),new_length,FIX(new_full_buffers),
		FIX(new_remainder),FIX(new_total_buffers));
    else
	return shrink_managed_float_array(managed_float_array,dont_copy,
		FIX(old_total_buffers),new_length,FIX(new_full_buffers),
		FIX(new_remainder),FIX(new_total_buffers));
}

/* ADJUST-FINAL-BUFFER-OF-MANAGED-FLOAT-ARRAY */
Object adjust_final_buffer_of_managed_float_array(managed_float_array,
	    dont_copy,total_buffers,old_final_buffer_size,
	    new_final_buffer_size)
    Object managed_float_array, dont_copy, total_buffers;
    Object old_final_buffer_size, new_final_buffer_size;
{
    Object old_buffer, old_actual_buffer_length, new_actual_buffer_length;
    Object new_buffer;
    SI_Long svref_arg_2;

    x_note_fn_call(32,36);
    old_buffer = ISVREF(managed_float_array,
	    IFIX(FIXNUM_SUB1(total_buffers)) + (SI_Long)2L);
    old_actual_buffer_length = length(old_buffer);
    new_actual_buffer_length = 
	    buffer_size_for_partial_buffer(new_final_buffer_size,
	    Managed_array_allocation_schemes);
    if (FIXNUM_NE(new_actual_buffer_length,old_actual_buffer_length)) {
	new_buffer = 
		allocate_managed_simple_float_array(new_actual_buffer_length);
	if ( !TRUEP(dont_copy))
	    copy_simple_float_array_portion_function(old_buffer,
		    FIX((SI_Long)0L),FIXNUM_MIN(new_final_buffer_size,
		    old_final_buffer_size),new_buffer,FIX((SI_Long)0L));
	svref_arg_2 = IFIX(FIXNUM_SUB1(total_buffers)) + (SI_Long)2L;
	ISVREF(managed_float_array,svref_arg_2) = new_buffer;
	return reclaim_managed_simple_float_array(old_buffer);
    }
    else
	return VALUES_1(Nil);
}

/* GROW-MANAGED-FLOAT-ARRAY */
Object grow_managed_float_array(managed_float_array,dont_copy,
	    old_full_buffers,old_remainder,old_total_buffers,new_length,
	    new_full_buffers,new_remainder,new_total_buffers)
    Object managed_float_array, dont_copy, old_full_buffers, old_remainder;
    Object old_total_buffers, new_length, new_full_buffers, new_remainder;
    Object new_total_buffers;
{
    Object new_spine_length, new_spine, svref_new_value;
    SI_Long spine_index, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(32,37);
    if (FIXNUM_NE(old_full_buffers,old_total_buffers))
	adjust_final_buffer_of_managed_float_array(managed_float_array,
		dont_copy,old_total_buffers,old_remainder,
		Maximum_managed_float_array_buffer_size);
    new_spine_length = 
	    buffer_size_for_partial_buffer(FIX(IFIX(new_total_buffers) + 
	    (SI_Long)2L),Managed_array_allocation_schemes);
    if (FIXNUM_NE(length(managed_float_array),new_spine_length)) {
	new_spine = 
		allocate_managed_simple_vector_for_float_array(new_spine_length);
	copy_simple_vector_portion_function(managed_float_array,
		FIX((SI_Long)2L),old_total_buffers,new_spine,FIX((SI_Long)2L));
	SVREF(managed_float_array,FIX((SI_Long)0L)) = Nil;
	reclaim_managed_simple_vector_for_float_array(managed_float_array);
	svref_new_value = Managed_float_array_unique_marker;
	SVREF(new_spine,FIX((SI_Long)0L)) = svref_new_value;
	managed_float_array = new_spine;
    }
    SVREF(managed_float_array,FIX((SI_Long)1L)) = new_length;
    spine_index = IFIX(old_total_buffers);
    ab_loop_bind_ = IFIX(new_full_buffers);
  next_loop:
    if (spine_index >= ab_loop_bind_)
	goto end_loop;
    svref_arg_2 = spine_index + (SI_Long)2L;
    svref_new_value = 
	    allocate_managed_simple_float_array(Maximum_managed_float_array_buffer_size);
    ISVREF(managed_float_array,svref_arg_2) = svref_new_value;
    spine_index = spine_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (FIXNUM_NE(new_full_buffers,new_total_buffers)) {
	svref_arg_2 = IFIX(FIXNUM_SUB1(new_total_buffers)) + (SI_Long)2L;
	svref_new_value = 
		allocate_managed_simple_float_array(buffer_size_for_partial_buffer(new_remainder,
		Managed_array_allocation_schemes));
	ISVREF(managed_float_array,svref_arg_2) = svref_new_value;
    }
    return VALUES_1(managed_float_array);
}

/* SHRINK-MANAGED-FLOAT-ARRAY */
Object shrink_managed_float_array(managed_float_array,dont_copy,
	    old_total_buffers,new_length,new_full_buffers,new_remainder,
	    new_total_buffers)
    Object managed_float_array, dont_copy, old_total_buffers, new_length;
    Object new_full_buffers, new_remainder, new_total_buffers;
{
    Object buffer, new_spine_length, new_spine, gensymed_symbol;
    Object gensymed_symbol_3, svref_new_value;
    SI_Long buffer_index, ab_loop_bind_, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_4;

    x_note_fn_call(32,38);
    buffer_index = IFIX(new_total_buffers);
    ab_loop_bind_ = IFIX(old_total_buffers);
    buffer = Nil;
  next_loop:
    if (buffer_index >= ab_loop_bind_)
	goto end_loop;
    buffer = ISVREF(managed_float_array,buffer_index + (SI_Long)2L);
    reclaim_managed_simple_float_array(buffer);
    buffer_index = buffer_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (FIXNUM_NE(new_full_buffers,new_total_buffers))
	adjust_final_buffer_of_managed_float_array(managed_float_array,
		dont_copy,new_total_buffers,
		Maximum_managed_float_array_buffer_size,new_remainder);
    new_spine_length = 
	    buffer_size_for_partial_buffer(FIX(IFIX(new_total_buffers) + 
	    (SI_Long)2L),Managed_array_allocation_schemes);
    if (FIXNUM_NE(new_spine_length,length(managed_float_array))) {
	new_spine = 
		allocate_managed_simple_vector_for_float_array(new_spine_length);
	gensymed_symbol = managed_float_array;
	gensymed_symbol_1 = (SI_Long)2L;
	gensymed_symbol_2 = gensymed_symbol_1 + IFIX(new_total_buffers);
	gensymed_symbol_3 = new_spine;
	gensymed_symbol_4 = (SI_Long)2L;
      next_loop_1:
	if ( !(gensymed_symbol_1 < gensymed_symbol_2))
	    goto end_loop_1;
	svref_new_value = ISVREF(gensymed_symbol,gensymed_symbol_1);
	ISVREF(gensymed_symbol_3,gensymed_symbol_4) = svref_new_value;
	gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
	gensymed_symbol_4 = gensymed_symbol_4 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	SVREF(managed_float_array,FIX((SI_Long)0L)) = Nil;
	reclaim_managed_simple_vector_for_float_array(managed_float_array);
	svref_new_value = Managed_float_array_unique_marker;
	SVREF(new_spine,FIX((SI_Long)0L)) = svref_new_value;
	managed_float_array = new_spine;
    }
    SVREF(managed_float_array,FIX((SI_Long)1L)) = new_length;
    return VALUES_1(managed_float_array);
}

/* COPY-FROM-SIMPLE-FLOAT-ARRAY-INTO-MANAGED-FLOAT-ARRAY */
Object copy_from_simple_float_array_into_managed_float_array(simple_float_array,
	    vector_index_init,count_init,managed_float_array,array_index_init)
    Object simple_float_array, vector_index_init, count_init;
    Object managed_float_array, array_index_init;
{
    Object temp, temp_1;
    SI_Long vector_index, count_1, array_index, buffer_index;
    SI_Long managed_buffer_number, elements_to_copy, temp_2, decff_1_arg;
    SI_Long incff_1_arg;
    Object result;

    x_note_fn_call(32,39);
    vector_index = IFIX(vector_index_init);
    count_1 = IFIX(count_init);
    array_index = IFIX(array_index_init);
    result = chestnut_floorf_function(FIX(array_index),
	    Maximum_managed_float_array_buffer_size);
    MVS_2(result,temp,temp_1);
    buffer_index = IFIX(temp_1);
    managed_buffer_number = IFIX(temp);
    elements_to_copy = (SI_Long)0L;
  next_loop:
    if ( !(count_1 > (SI_Long)0L))
	goto end_loop;
    temp_2 = IFIX(Maximum_managed_float_array_buffer_size) - buffer_index;
    elements_to_copy = MIN(temp_2,count_1);
    copy_simple_float_array_portion_function(simple_float_array,
	    FIX(vector_index),FIX(elements_to_copy),
	    ISVREF(managed_float_array,managed_buffer_number + 
	    (SI_Long)2L),FIX(buffer_index));
    decff_1_arg = elements_to_copy;
    count_1 = count_1 - decff_1_arg;
    incff_1_arg = elements_to_copy;
    vector_index = vector_index + incff_1_arg;
    managed_buffer_number = managed_buffer_number + (SI_Long)1L;
    buffer_index = (SI_Long)0L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COPY-FROM-MANAGED-FLOAT-ARRAY-INTO-SIMPLE-FLOAT-ARRAY */
Object copy_from_managed_float_array_into_simple_float_array(managed_float_array,
	    array_index_init,count_init,simple_float_array,vector_index_init)
    Object managed_float_array, array_index_init, count_init;
    Object simple_float_array, vector_index_init;
{
    Object temp, temp_1;
    SI_Long array_index, count_1, vector_index, buffer_index;
    SI_Long managed_buffer_number, elements_to_copy, temp_2, decff_1_arg;
    SI_Long incff_1_arg;
    Object result;

    x_note_fn_call(32,40);
    array_index = IFIX(array_index_init);
    count_1 = IFIX(count_init);
    vector_index = IFIX(vector_index_init);
    result = chestnut_floorf_function(FIX(array_index),
	    Maximum_managed_float_array_buffer_size);
    MVS_2(result,temp,temp_1);
    buffer_index = IFIX(temp_1);
    managed_buffer_number = IFIX(temp);
    elements_to_copy = (SI_Long)0L;
  next_loop:
    if ( !(count_1 > (SI_Long)0L))
	goto end_loop;
    temp_2 = IFIX(Maximum_managed_float_array_buffer_size) - buffer_index;
    elements_to_copy = MIN(temp_2,count_1);
    copy_simple_float_array_portion_function(ISVREF(managed_float_array,
	    managed_buffer_number + (SI_Long)2L),FIX(buffer_index),
	    FIX(elements_to_copy),simple_float_array,FIX(vector_index));
    decff_1_arg = elements_to_copy;
    count_1 = count_1 - decff_1_arg;
    incff_1_arg = elements_to_copy;
    vector_index = vector_index + incff_1_arg;
    managed_buffer_number = managed_buffer_number + (SI_Long)1L;
    buffer_index = (SI_Long)0L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COPY-MANAGED-FLOAT-ARRAY-PORTION */
Object copy_managed_float_array_portion(source_array,source_index_init,
	    element_count_init,destination_array,destination_index_init)
    Object source_array, source_index_init, element_count_init;
    Object destination_array, destination_index_init;
{
    Object temp, temp_1, ab_loop_iter_flag_;
    SI_Long source_index, element_count, destination_index;
    SI_Long source_buffer_index, source_buffer_number, temp_2;
    SI_Long elements_to_copy, decff_1_arg, incff_1_arg;
    Object result;

    x_note_fn_call(32,41);
    source_index = IFIX(source_index_init);
    element_count = IFIX(element_count_init);
    destination_index = IFIX(destination_index_init);
    if (element_count > (SI_Long)0L) {
	result = chestnut_floorf_function(FIX(source_index),
		Maximum_managed_float_array_buffer_size);
	MVS_2(result,temp,temp_1);
	source_buffer_index = IFIX(temp_1);
	source_buffer_number = IFIX(temp);
	temp_2 = IFIX(Maximum_managed_float_array_buffer_size) - 
		source_buffer_index;
	elements_to_copy = MIN(temp_2,element_count);
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !(element_count > (SI_Long)0L))
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_)) {
	    temp_2 = IFIX(Maximum_managed_float_array_buffer_size);
	    elements_to_copy = MIN(temp_2,element_count);
	}
	copy_from_simple_float_array_into_managed_float_array(ISVREF(source_array,
		source_buffer_number + (SI_Long)2L),
		FIX(source_buffer_index),FIX(elements_to_copy),
		destination_array,FIX(destination_index));
	decff_1_arg = elements_to_copy;
	element_count = element_count - decff_1_arg;
	incff_1_arg = elements_to_copy;
	destination_index = destination_index + incff_1_arg;
	source_buffer_number = source_buffer_number + (SI_Long)1L;
	source_buffer_index = (SI_Long)0L;
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* FILL-MANAGED-FLOAT-ARRAY */
Object fill_managed_float_array(managed_float_array,gensym_float)
    Object managed_float_array, gensym_float;
{
    Object temp, temp_1, full_buffer, last_buffer;
    SI_Long length_1, partial_buffer, full_buffers, buffer_index;
    SI_Long ab_loop_bind_, index_1;
    double cached_float;
    Object result;

    x_note_fn_call(32,42);
    length_1 = IFIX(SVREF(managed_float_array,FIX((SI_Long)1L)));
    cached_float = DOUBLE_FLOAT_TO_DOUBLE(gensym_float);
    result = chestnut_floorf_function(FIX(length_1),
	    Maximum_managed_float_array_buffer_size);
    MVS_2(result,temp,temp_1);
    partial_buffer = IFIX(temp_1);
    full_buffers = IFIX(temp);
    buffer_index = (SI_Long)0L;
    ab_loop_bind_ = full_buffers;
    full_buffer = Nil;
  next_loop:
    if (buffer_index >= ab_loop_bind_)
	goto end_loop;
    full_buffer = ISVREF(managed_float_array,buffer_index + (SI_Long)2L);
    index_1 = (SI_Long)0L;
  next_loop_1:
    if (index_1 >= IFIX(Maximum_managed_float_array_buffer_size))
	goto end_loop_1;
    DFLOAT_ISASET_1(full_buffer,index_1,cached_float);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    buffer_index = buffer_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (partial_buffer != (SI_Long)0L) {
	last_buffer = ISVREF(managed_float_array,full_buffers + (SI_Long)2L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = partial_buffer;
      next_loop_2:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_2;
	DFLOAT_ISASET_1(last_buffer,index_1,cached_float);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
    }
    return VALUES_1(managed_float_array);
}

/* ROTATE-MANAGED-FLOAT-ARRAY */
Object rotate_managed_float_array(managed_float_array,index_to_rotate)
    Object managed_float_array, index_to_rotate;
{
    Object new_array, buffer, svref_new_value;
    SI_Long length_1, high_shift_size, buffer_index, temp, ab_loop_bind_;
    SI_Long svref_arg_2;

    x_note_fn_call(32,43);
    if (IFIX(index_to_rotate) != (SI_Long)0L) {
	length_1 = IFIX(ISVREF(managed_float_array,(SI_Long)1L));
	new_array = allocate_managed_float_array(1,FIX(length_1));
	high_shift_size = length_1 - IFIX(index_to_rotate);
	copy_managed_float_array_portion(managed_float_array,
		index_to_rotate,FIX(high_shift_size),new_array,
		FIX((SI_Long)0L));
	copy_managed_float_array_portion(managed_float_array,
		FIX((SI_Long)0L),index_to_rotate,new_array,
		FIX(high_shift_size));
	buffer_index = (SI_Long)0L;
	temp = (length_1 + 
		IFIX(FIXNUM_SUB1(Maximum_managed_float_array_buffer_size))) 
		/ IFIX(Maximum_managed_float_array_buffer_size);
	ab_loop_bind_ = temp;
	buffer = Nil;
      next_loop:
	if (buffer_index >= ab_loop_bind_)
	    goto end_loop;
	buffer = ISVREF(managed_float_array,buffer_index + (SI_Long)2L);
	reclaim_managed_simple_float_array(buffer);
	svref_arg_2 = buffer_index + (SI_Long)2L;
	svref_new_value = ISVREF(new_array,buffer_index + (SI_Long)2L);
	ISVREF(managed_float_array,svref_arg_2) = svref_new_value;
	buffer_index = buffer_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	reclaim_managed_simple_vector(new_array);
	return VALUES_1(managed_float_array);
    }
    else
	return VALUES_1(Nil);
}

/* COPY-MANAGED-FLOAT-ARRAY */
Object copy_managed_float_array(managed_float_array)
    Object managed_float_array;
{
    Object length_1, new_array;

    x_note_fn_call(32,44);
    length_1 = ISVREF(managed_float_array,(SI_Long)1L);
    new_array = allocate_managed_float_array(1,length_1);
    copy_managed_float_array_portion(managed_float_array,FIX((SI_Long)0L),
	    length_1,new_array,FIX((SI_Long)0L));
    return VALUES_1(new_array);
}

/* MANAGED-FLOAT-P-FUNCTION */
Object managed_float_p_function(thing)
    Object thing;
{
    x_note_fn_call(32,45);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L)
	return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == 
		(SI_Long)1L ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* MANAGED-FLOAT-VALUE-FUNCTION */
Object managed_float_value_function(managed_float)
    Object managed_float;
{
    x_note_fn_call(32,46);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_float,
	    (SI_Long)0L)));
}

DEFINE_VARIABLE_WITH_SYMBOL(Bytes_per_double_float_simple_array_cached, Qbytes_per_double_float_simple_array_cached);

/* ALLOCATE-MANAGED-FLOAT-BOX */
Object allocate_managed_float_box()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;

    x_note_fn_call(32,47);
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
    return VALUES_1(amf_result);
}

/* COPY-MANAGED-FLOAT */
Object copy_managed_float(managed_float)
    Object managed_float;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value;

    x_note_fn_call(32,48);
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
    aref_new_value = DFLOAT_ISAREF_1(managed_float,(SI_Long)0L);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* RECLAIM-IF-MANAGED-FLOAT */
Object reclaim_if_managed_float(maybe_managed_float)
    Object maybe_managed_float;
{
    x_note_fn_call(32,49);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(maybe_managed_float) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(maybe_managed_float)) == 
	    (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(maybe_managed_float);
    return VALUES_1(Nil);
}

static Object list_constant;       /* # */

/* GENERATE-LONG-VECTOR */
Object generate_long_vector(length_1)
    Object length_1;
{
    Object vector_1;
    XDeclare_area(1);

    x_note_fn_call(32,50);
    if (PUSH_AREA(Dynamic_area,0))
	vector_1 = make_array(5,length_1,Kelement_type,list_constant,
		Kinitial_element,FIX((SI_Long)0L));
    POP_AREA(0);
    return VALUES_1(vector_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_long_array_conses, Qavailable_long_array_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_long_array_conses_tail, Qavailable_long_array_conses_tail);

Object Available_long_array_conses_vector = UNBOUND;

Object Available_long_array_conses_tail_vector = UNBOUND;

Object Long_array_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Long_array_cons_counter, Qlong_array_cons_counter);

/* OUTSTANDING-LONG-ARRAY-CONSES */
Object outstanding_long_array_conses()
{
    Object temp;

    x_note_fn_call(32,51);
    temp = FIXNUM_MINUS(Long_array_cons_counter,
	    length(Available_long_array_conses));
    return VALUES_1(temp);
}

/* LONG-ARRAY-CONS-MEMORY-USAGE */
Object long_array_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(32,52);
    temp = FIXNUM_TIMES(Long_array_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-LONG-ARRAY-CONS-POOL */
Object replenish_long_array_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(32,53);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qlong_array_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_long_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_long_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_long_array_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Long_array_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qlong_array;         /* long-array */

/* LONG-ARRAY-CONS-1 */
Object long_array_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(32,54);
    new_cons = ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_long_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_long_array_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_long_array_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qlong_array);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-LONG-ARRAY-LIST-POOL */
Object replenish_long_array_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(32,55);
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
    if (ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_long_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_long_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_long_array_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qlong_array_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-LONG-ARRAY-LIST-1 */
Object make_long_array_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(32,56);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_long_array_conses_vector,
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
	replenish_long_array_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_long_array_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qlong_array);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_long_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_long_array_conses_tail_vector;
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

/* LONG-ARRAY-LIST-2 */
Object long_array_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,57);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_long_array_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qlong_array);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_long_array_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_long_array_conses_tail_vector;
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

/* LONG-ARRAY-LIST-3 */
Object long_array_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,58);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_long_array_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qlong_array);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_long_array_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_long_array_conses_tail_vector;
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

/* LONG-ARRAY-LIST-4 */
Object long_array_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,59);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_long_array_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qlong_array);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_long_array_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_long_array_conses_tail_vector;
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

/* LONG-ARRAY-LIST-TRACE-HOOK */
Object long_array_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(32,60);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-LONG-ARRAY-CONSES-1 */
Object copy_tree_using_long_array_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(32,61);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_long_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_long_array_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_long_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_long_array_cons_pool();
	temp_1 = copy_tree_using_long_array_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qlong_array);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_long_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_long_array_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_long_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_long_array_cons_pool();
	temp_1 = 
		copy_tree_using_long_array_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qlong_array);
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

/* COPY-LIST-USING-LONG-ARRAY-CONSES-1 */
Object copy_list_using_long_array_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(32,62);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_long_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_long_array_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_long_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_long_array_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qlong_array);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_long_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_long_array_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_long_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_long_array_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qlong_array);
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

/* RECLAIM-LONG-ARRAY-CONS-1 */
Object reclaim_long_array_cons_1(long_array_cons)
    Object long_array_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(32,63);
    inline_note_reclaim_cons(long_array_cons,Qlong_array);
    if (ISVREF(Available_long_array_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_long_array_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = long_array_cons;
	temp = Available_long_array_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = long_array_cons;
    }
    else {
	temp = Available_long_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = long_array_cons;
	temp = Available_long_array_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = long_array_cons;
    }
    M_CDR(long_array_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-LONG-ARRAY-LIST-1 */
Object reclaim_long_array_list_1(long_array_list)
    Object long_array_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(32,64);
    if (long_array_list) {
	last_1 = long_array_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qlong_array);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qlong_array);
	if (ISVREF(Available_long_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_long_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = long_array_list;
	    temp = Available_long_array_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_long_array_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = long_array_list;
	    temp = Available_long_array_conses_tail_vector;
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

/* RECLAIM-LONG-ARRAY-LIST*-1 */
Object reclaim_long_array_list_star_1(long_array_list)
    Object long_array_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(32,65);
    if (CONSP(long_array_list)) {
	temp = last(long_array_list,_);
	M_CDR(temp) = Nil;
	if (long_array_list) {
	    last_1 = long_array_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qlong_array);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qlong_array);
	    if (ISVREF(Available_long_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_long_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = long_array_list;
		temp = Available_long_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_long_array_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = long_array_list;
		temp = Available_long_array_conses_tail_vector;
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

/* RECLAIM-LONG-ARRAY-TREE-1 */
Object reclaim_long_array_tree_1(tree)
    Object tree;
{
    Object e, e2, long_array_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(32,66);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_long_array_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		long_array_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(long_array_cons,Qlong_array);
		if (EQ(long_array_cons,e))
		    goto end_1;
		else if ( !TRUEP(long_array_cons))
		    goto end_1;
		else
		    long_array_cons = CDR(long_array_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_long_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_long_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_long_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_long_array_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_long_array_conses_tail_vector;
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

/* DELETE-LONG-ARRAY-ELEMENT-1 */
Object delete_long_array_element_1(element,long_array_list)
    Object element, long_array_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(32,67);
    if (long_array_list) {
	if (EQ(element,M_CAR(long_array_list))) {
	    temp = CDR(long_array_list);
	    inline_note_reclaim_cons(long_array_list,Qlong_array);
	    if (ISVREF(Available_long_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_long_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = long_array_list;
		temp_1 = Available_long_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = long_array_list;
	    }
	    else {
		temp_1 = Available_long_array_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = long_array_list;
		temp_1 = Available_long_array_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = long_array_list;
	    }
	    M_CDR(long_array_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = long_array_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qlong_array);
		if (ISVREF(Available_long_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_long_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_long_array_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_long_array_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_long_array_conses_tail_vector;
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
	    temp = long_array_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-LONG-ARRAY-CONS-1 */
Object delete_long_array_cons_1(long_array_cons,long_array_list)
    Object long_array_cons, long_array_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(32,68);
    if (EQ(long_array_cons,long_array_list))
	temp = CDR(long_array_list);
    else {
	l_trailer_qm = Nil;
	l = long_array_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,long_array_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = long_array_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_long_array_cons_1(long_array_cons);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Vector_of_simple_long_array_pools, Qvector_of_simple_long_array_pools);

DEFINE_VARIABLE_WITH_SYMBOL(Created_simple_long_array_pool_arrays, Qcreated_simple_long_array_pool_arrays);

/* OUTSTANDING-SIMPLE-LONG-ARRAY-POOL-ARRAYS */
Object outstanding_simple_long_array_pool_arrays()
{
    Object incff_1_arg;
    SI_Long vectors_in_pools, index_1;

    x_note_fn_call(32,69);
    vectors_in_pools = (SI_Long)0L;
    index_1 = (SI_Long)1L;
  next_loop:
    if (index_1 > IFIX(Maximum_managed_simple_long_array_size))
	goto end_loop;
    incff_1_arg = length(ISVREF(Vector_of_simple_long_array_pools,index_1));
    vectors_in_pools = vectors_in_pools + IFIX(incff_1_arg);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(IFIX(Created_simple_long_array_pool_arrays) - 
	    vectors_in_pools));
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Simple_long_array_pool_memory_usage, Qsimple_long_array_pool_memory_usage);

/* SIMPLE-LONG-ARRAY-POOL-MEMORY-USAGE */
Object simple_long_array_pool_memory_usage()
{
    x_note_fn_call(32,70);
    return VALUES_1(Simple_long_array_pool_memory_usage);
}

Object Replenished_simple_long_array_size_limit = UNBOUND;

Object Replenished_simple_long_arrays_to_make_at_a_time = UNBOUND;

static Object Qmanaged_simple_long_array;  /* managed-simple-long-array */

/* ALLOCATE-MANAGED-SIMPLE-LONG-ARRAY-OF-LENGTH-1 */
Object allocate_managed_simple_long_array_of_length_1()
{
    Object available_array_cons_qm, array, temp, temp_1, result_1;
    Object new_vector_list, new_vector_cons;

    x_note_fn_call(32,71);
    available_array_cons_qm = ISVREF(Vector_of_simple_long_array_pools,
	    (SI_Long)1L);
    if (available_array_cons_qm) {
	array = M_CAR(available_array_cons_qm);
	temp = Vector_of_simple_long_array_pools;
	temp_1 = M_CDR(available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(available_array_cons_qm,Qlong_array);
	if (ISVREF(Available_long_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_long_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = available_array_cons_qm;
	    temp = Available_long_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = available_array_cons_qm;
	}
	else {
	    temp = Available_long_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = available_array_cons_qm;
	    temp = Available_long_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = available_array_cons_qm;
	}
	M_CDR(available_array_cons_qm) = Nil;
	result_1 = array;
    }
    else {
	new_vector_list = make_long_array_list_1(FIX((SI_Long)9L));
	new_vector_cons = new_vector_list;
      next_loop:
	if ( !TRUEP(new_vector_cons))
	    goto end_loop;
	temp = generate_long_vector(FIX((SI_Long)1L));
	M_CAR(new_vector_cons) = temp;
	new_vector_cons = M_CDR(new_vector_cons);
	goto next_loop;
      end_loop:
	temp = Vector_of_simple_long_array_pools;
	SVREF(temp,FIX((SI_Long)1L)) = new_vector_list;
	atomic_incff_symval(Qcreated_simple_long_array_pool_arrays,
		FIX((SI_Long)10L));
	atomic_incff_symval(Qsimple_long_array_pool_memory_usage,
		FIX((SI_Long)10L * 
		IFIX(bytes_per_long_simple_array(FIX((SI_Long)1L)))));
	result_1 = generate_long_vector(FIX((SI_Long)1L));
    }
    inline_note_allocate_cons(result_1,Qmanaged_simple_long_array);
    return VALUES_1(result_1);
}

/* RECLAIM-MANAGED-SIMPLE-LONG-ARRAY-OF-LENGTH-1 */
Object reclaim_managed_simple_long_array_of_length_1(managed_simple_long_array)
    Object managed_simple_long_array;
{
    Object svref_arg_1, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(32,72);
    inline_note_reclaim_cons(managed_simple_long_array,
	    Qmanaged_simple_long_array);
    svref_arg_1 = Vector_of_simple_long_array_pools;
    new_cons = ISVREF(Available_long_array_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_long_array_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_long_array_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_long_array_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_long_array_cons_pool();
    M_CAR(gensymed_symbol) = managed_simple_long_array;
    temp = ISVREF(Vector_of_simple_long_array_pools,(SI_Long)1L);
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qlong_array);
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = gensymed_symbol;
    return VALUES_1(Nil);
}

/* MANAGED-LONG-P-FUNCTION */
Object managed_long_p_function(thing)
    Object thing;
{
    x_note_fn_call(32,73);
    if (INLINE_LONG_VECTOR_P(thing) != (SI_Long)0L)
	return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == 
		(SI_Long)1L ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* MANAGED-LONG-VALUE-FUNCTION */
Object managed_long_value_function(managed_long)
    Object managed_long;
{
    x_note_fn_call(32,74);
    return aref1(managed_long,FIX((SI_Long)0L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Bytes_per_long_simple_array_cached, Qbytes_per_long_simple_array_cached);

/* ALLOCATE-MANAGED-LONG-BOX */
Object allocate_managed_long_box()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;

    x_note_fn_call(32,75);
    amf_available_array_cons_qm = ISVREF(Vector_of_simple_long_array_pools,
	    (SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_long_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qlong_array);
	if (ISVREF(Available_long_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_long_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_long_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_long_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_long_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_long_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_long_array_pool_memory_usage,
		Bytes_per_long_simple_array_cached);
	amf_result = generate_long_vector(FIX((SI_Long)1L));
    }
    return VALUES_1(amf_result);
}

/* ALLOCATE-MANAGED-LONG-FUNCTION */
Object allocate_managed_long_function(gensym_long)
    Object gensym_long;
{
    Object new_long;
    SI_int64 aref_new_value;

    x_note_fn_call(32,76);
    new_long = allocate_managed_long_box();
    aref_new_value = INTEGER_TO_INT64(gensym_long);
    set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
    return VALUES_1(new_long);
}

/* COPY-MANAGED-LONG */
Object copy_managed_long(managed_long)
    Object managed_long;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_long, temp_2;
    SI_int64 aref_new_value;

    x_note_fn_call(32,77);
    amf_available_array_cons_qm = ISVREF(Vector_of_simple_long_array_pools,
	    (SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_long_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qlong_array);
	if (ISVREF(Available_long_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_long_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_long_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_long_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_long_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_long_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_long_array_pool_memory_usage,
		Bytes_per_long_simple_array_cached);
	amf_result = generate_long_vector(FIX((SI_Long)1L));
    }
    new_long = amf_result;
    temp_2 = aref1(managed_long,FIX((SI_Long)0L));
    aref_new_value = INTEGER_TO_INT64(temp_2);
    set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
    return VALUES_1(new_long);
}

/* RECLAIM-IF-MANAGED-LONG */
Object reclaim_if_managed_long(maybe_managed_long)
    Object maybe_managed_long;
{
    x_note_fn_call(32,78);
    if (INLINE_LONG_VECTOR_P(maybe_managed_long) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(maybe_managed_long)) == (SI_Long)1L)
	reclaim_managed_simple_long_array_of_length_1(maybe_managed_long);
    return VALUES_1(Nil);
}

/* RECLAIM-MANAGED-NUMBER-OR-VALUE-FUNCTION */
Object reclaim_managed_number_or_value_function(managed_number_or_value)
    Object managed_number_or_value;
{
    x_note_fn_call(32,79);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(managed_number_or_value);
    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	reclaim_managed_simple_long_array_of_length_1(managed_number_or_value);
    else if (text_string_p(managed_number_or_value))
	reclaim_text_string(managed_number_or_value);
    else if (FIXNUMP(managed_number_or_value) || 
	    SYMBOLP(managed_number_or_value));
    else
	reclaim_evaluation_value(managed_number_or_value);
    return VALUES_1(Nil);
}

/* RECLAIM-POSSIBLE-MANAGED-FLOAT */
Object reclaim_possible_managed_float(managed_float_qm)
    Object managed_float_qm;
{
    x_note_fn_call(32,80);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_qm) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_qm)) == (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(managed_float_qm);
    return VALUES_1(Nil);
}

/* STORE-MANAGED-NUMBER-FUNCTION */
Object store_managed_number_function(old_value,new_number)
    Object old_value, new_number;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_1, temp_2;
    Object amf_result, new_float, new_long;
    SI_int64 aref_new_value_1;
    double aref_new_value;

    x_note_fn_call(32,81);
    if (FLOATP(new_number) || INLINE_LONG_P(new_number) != (SI_Long)0L) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_number);
	    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    temp = old_value;
	}
	else if (INLINE_LONG_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value_1 = INTEGER_TO_INT64(new_number);
	    temp = set_aref1(old_value,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value_1));
	}
	else if (FLOATP(new_number)) {
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_number);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
	else {
	    new_long = allocate_managed_long_box();
	    aref_new_value_1 = INTEGER_TO_INT64(new_number);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value_1));
	    temp = new_long;
	}
    }
    else if (FIXNUMP(new_number)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L)
	    reclaim_managed_simple_float_array_of_length_1(old_value);
	temp = new_number;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_number)) == (SI_Long)1L) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L)
	    reclaim_managed_simple_float_array_of_length_1(old_value);
	else if (INLINE_LONG_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L)
	    reclaim_managed_simple_long_array_of_length_1(old_value);
	temp = new_number;
    }
    else if (INLINE_LONG_VECTOR_P(new_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_number)) == (SI_Long)1L) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L)
	    reclaim_managed_simple_float_array_of_length_1(old_value);
	else if (INLINE_LONG_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L)
	    reclaim_managed_simple_long_array_of_length_1(old_value);
	temp = new_number;
    }
    else if (BIGNUMP(new_number)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    temp_1 = coerce_bignum_to_gensym_float(new_number);
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    temp = old_value;
	}
	else if (FLOATP(old_value)) {
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
	    temp = coerce_bignum_to_gensym_float(new_number);
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value_1 = INTEGER_TO_INT64(new_number);
	    temp = set_aref1(old_value,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value_1));
	}
	else {
	    new_long = allocate_managed_long_box();
	    aref_new_value_1 = INTEGER_TO_INT64(new_number);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value_1));
	    temp = new_long;
	}
    }
    else
	temp = error((SI_Long)2L,
		"Non-number ~a given to store-managed-number.",new_number);
    return VALUES_1(temp);
}

/* COERCE-NUMBER-TO-FIXNUM */
Object coerce_number_to_fixnum(number)
    Object number;
{
    Object temp, long_value;
    XDeclare_area(1);

    x_note_fn_call(32,82);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number)) == (SI_Long)1L)
	temp = l_round(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(number,
		(SI_Long)0L)),_);
    else if (FLOATP(number))
	temp = l_round(number,_);
    else if (FIXNUMP(number))
	temp = number;
    else if (INLINE_LONG_VECTOR_P(number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number)) == (SI_Long)1L) {
	if (PUSH_AREA(Dynamic_area,0)) {
	    long_value = aref1(number,FIX((SI_Long)0L));
	    temp = coerce(long_value,Qfixnum);
	}
	POP_AREA(0);
    }
    else if (INLINE_LONG_P(number) != (SI_Long)0L) {
	if (PUSH_AREA(Dynamic_area,0))
	    temp = coerce(number,Qfixnum);
	POP_AREA(0);
    }
    else
	temp = FIX((SI_Long)0L);
    return VALUES_1(temp);
}

/* CONVERT-G2LONGINT-TO-DOUBLE */
Object convert_g2longint_to_double(gensym_long_init)
    Object gensym_long_init;
{
    Object temp;
    SI_int64 gensym_long;

    x_note_fn_call(32,83);
    gensym_long = INTEGER_TO_INT64(gensym_long_init);
    temp = lfloat(INT64_TO_INTEGER(gensym_long),float_constant);
    return VALUES_1(temp);
}

static Object Qgensym_float;       /* gensym-float */

/* NORMALIZE-TO-GENSYM-FLOAT */
Object normalize_to_gensym_float(x)
    Object x;
{
    Object gensymed_symbol, long_value;

    x_note_fn_call(32,84);
    gensymed_symbol = x;
    if (FIXNUMP(gensymed_symbol))
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(gensymed_symbol)));
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == (SI_Long)1L)
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gensymed_symbol,
		(SI_Long)0L)));
    else if (FLOATP(gensymed_symbol))
	return VALUES_1(gensymed_symbol);
    else if (INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == (SI_Long)1L) {
	long_value = aref1(gensymed_symbol,FIX((SI_Long)0L));
	return convert_g2longint_to_double(long_value);
    }
    else if (INLINE_LONG_P(gensymed_symbol) != (SI_Long)0L)
	return convert_g2longint_to_double(gensymed_symbol);
    else
	return coerce(gensymed_symbol,Qgensym_float);
}

/* STORE-MANAGED-NUMBER-OR-VALUE-FUNCTION */
Object store_managed_number_or_value_function(old_value,new_value)
    Object old_value, new_value;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, new_long;
    SI_int64 aref_new_value_1;
    double aref_new_value;

    x_note_fn_call(32,85);
    if (FIXNUMP(new_value) || SYMBOLP(new_value)) {
	if ( !(FIXNUMP(old_value) || SYMBOLP(old_value))) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L)
		reclaim_managed_simple_float_array_of_length_1(old_value);
	    else if (text_string_p(old_value))
		reclaim_text_string(old_value);
	}
	return VALUES_1(new_value);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value)) == (SI_Long)1L) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value = DFLOAT_ISAREF_1(new_value,(SI_Long)0L);
	    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    return VALUES_1(old_value);
	}
	else {
	    if (text_string_p(old_value))
		reclaim_text_string(old_value);
	    return copy_managed_float(new_value);
	}
    }
    else if (FLOATP(new_value)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    return VALUES_1(old_value);
	}
	else {
	    if (text_string_p(old_value))
		reclaim_text_string(old_value);
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    return VALUES_1(new_float);
	}
    }
    else if (text_string_p(new_value)) {
	if (text_string_p(old_value))
	    reclaim_text_string(old_value);
	return copy_text_string(new_value);
    }
    else if (INLINE_LONG_VECTOR_P(new_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value)) == (SI_Long)1L) {
	if (INLINE_LONG_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    temp = aref1(new_value,FIX((SI_Long)0L));
	    aref_new_value_1 = INTEGER_TO_INT64(temp);
	    set_aref1(old_value,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value_1));
	    return VALUES_1(old_value);
	}
	else {
	    if (text_string_p(old_value))
		reclaim_text_string(old_value);
	    return copy_managed_long(new_value);
	}
    }
    else if (INLINE_LONG_P(new_value) != (SI_Long)0L) {
	if (INLINE_LONG_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value_1 = INTEGER_TO_INT64(new_value);
	    set_aref1(old_value,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value_1));
	    return VALUES_1(old_value);
	}
	else {
	    if (text_string_p(old_value))
		reclaim_text_string(old_value);
	    new_long = allocate_managed_long_box();
	    aref_new_value_1 = INTEGER_TO_INT64(new_value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value_1));
	    return VALUES_1(new_long);
	}
    }
    else if (BIGNUMP(new_value)) {
	new_value = coerce_bignum_to_gensym_float(new_value);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    return VALUES_1(old_value);
	}
	else {
	    if (text_string_p(old_value))
		reclaim_text_string(old_value);
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    return VALUES_1(new_float);
	}
    }
    else
	return VALUES_1(new_value);
}

static Object float_constant_1;    /* -1.0 */

static Object float_constant_2;    /* 1.0 */

/* COERCE-BIGNUM-TO-GENSYM-FLOAT */
Object coerce_bignum_to_gensym_float(bignum)
    Object bignum;
{
    x_note_fn_call(32,86);
    if (NUM_LT(bignum,Most_negative_gensym_float)) {
	warn_of_big_bignum(T);
	return VALUES_1(float_constant_1);
    }
    else if (NUM_GT(bignum,Most_positive_gensym_float)) {
	warn_of_big_bignum(Nil);
	return VALUES_1(float_constant_2);
    }
    else
	return lfloat(bignum,float_constant);
}

static Object list_constant_1;     /* # */

/* MAKE-PARTITION-FLOAT-OR-LONG-UNION */
Object make_partition_float_or_long_union()
{
    Object temp;

    x_note_fn_call(32,87);
    temp = make_array(3,FIX((SI_Long)4L),Kelement_type,list_constant_1);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Partition_float_union, Qpartition_float_union);

DEFINE_VARIABLE_WITH_SYMBOL(Partition_long_union, Qpartition_long_union);

/* PARTITION-MANAGED-FLOAT */
Object partition_managed_float(managed_float)
    Object managed_float;
{
    SI_Long b0, b1, b2, b3;

    x_note_fn_call(32,88);
    g2ext_foreign_partition_float(DFLOAT_ISAREF_1(managed_float,
	    (SI_Long)0L),UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
    b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
    b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
    b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
    b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
    return VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
}

/* RECONSTRUCT-MANAGED-FLOAT */
Object reconstruct_managed_float(byte0,byte1,byte2,byte3)
    Object byte0, byte1, byte2, byte3;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, b0, b1, b2, b3;
    double aref_new_value;

    x_note_fn_call(32,89);
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
    b0 = byte0;
    b1 = byte1;
    b2 = byte2;
    b3 = byte3;
    aref_new_value = g2ext_foreign_reconstruct_float(IFIX(b0),IFIX(b1),
	    IFIX(b2),IFIX(b3));
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

static Object Qvms;                /* vms */

/* POSITIVE-INFINITY-P */
Object positive_infinity_p(thing)
    Object thing;
{
    Object temp, byte0, byte1, byte2, byte3;
    SI_Long b0, b1, b2, b3;
    double temp_1;
    Object result;

    x_note_fn_call(32,90);
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
	    temp = FIXNUM_EQ(byte0,Mask_for_ieee_exponent) && IFIX(byte1) 
		    == (SI_Long)0L && IFIX(byte2) == (SI_Long)0L ? 
		    (IFIX(byte3) == (SI_Long)0L ? T : Nil) : Qnil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* NEGATIVE-INFINITY-P */
Object negative_infinity_p(thing)
    Object thing;
{
    Object temp, byte0, byte1, byte2, byte3;
    SI_Long b0, b1, b2, b3;
    double temp_1;
    Object result;

    x_note_fn_call(32,91);
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
	    temp = IFIX(byte0) == (SI_Long)65520L && IFIX(byte1) == 
		    (SI_Long)0L && IFIX(byte2) == (SI_Long)0L ? 
		    (IFIX(byte3) == (SI_Long)0L ? T : Nil) : Qnil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* NANP */
Object nanp(thing)
    Object thing;
{
    Object temp, byte0, byte1, byte2, byte3;
    SI_Long b0, b1, b2, b3;
    double temp_1;
    Object result;

    x_note_fn_call(32,92);
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
		temp = FIXNUM_PLUSP(byte1) ? T : Nil;
		if (temp);
		else
		    temp = FIXNUM_PLUSP(byte2) ? T : Nil;
		if (temp);
		else
		    temp = FIXNUM_PLUSP(byte3) ? T : Nil;
		if (temp);
		else
		    temp = (SI_Long)0L < (IFIX(byte0) & (SI_Long)15L) ? T :
			     Nil;
	    }
	    else
		temp = Nil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EXCEPTIONAL-FLOAT-P */
Object exceptional_float_p(thing)
    Object thing;
{
    Object temp, byte0;
    SI_Long b0, b1, b2, b3;
    double temp_1;

    x_note_fn_call(32,93);
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
	    temp = FIX(b0);
	    byte0 = temp;
	    temp = FIXNUM_EQ(FIXNUM_LOGAND(byte0,Mask_for_ieee_exponent),
		    Mask_for_ieee_exponent) ? T : Nil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* FILL-MANAGED-FLOAT-ARRAY-WITH-MANAGED-FLOAT */
Object fill_managed_float_array_with_managed_float(managed_float_array,
	    managed_float)
    Object managed_float_array, managed_float;
{
    Object full_buffer, last_buffer;
    SI_Long length_1, temp, full_buffers, partial_buffer, buffer_index;
    SI_Long ab_loop_bind_, index_1;
    double float_1;

    x_note_fn_call(32,94);
    length_1 = IFIX(SVREF(managed_float_array,FIX((SI_Long)1L)));
    temp = length_1 / IFIX(Maximum_managed_float_array_buffer_size);
    full_buffers = temp;
    temp = length_1 % IFIX(Maximum_managed_float_array_buffer_size);
    partial_buffer = temp;
    float_1 = DFLOAT_ISAREF_1(managed_float,(SI_Long)0L);
    buffer_index = (SI_Long)0L;
    ab_loop_bind_ = full_buffers;
    full_buffer = Nil;
  next_loop:
    if (buffer_index >= ab_loop_bind_)
	goto end_loop;
    full_buffer = ISVREF(managed_float_array,buffer_index + (SI_Long)2L);
    index_1 = (SI_Long)0L;
  next_loop_1:
    if (index_1 >= IFIX(Maximum_managed_float_array_buffer_size))
	goto end_loop_1;
    DFLOAT_ISASET_1(full_buffer,index_1,float_1);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    buffer_index = buffer_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (partial_buffer != (SI_Long)0L) {
	last_buffer = ISVREF(managed_float_array,full_buffers + (SI_Long)2L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = partial_buffer;
      next_loop_2:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_2;
	DFLOAT_ISASET_1(last_buffer,index_1,float_1);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
    }
    return VALUES_1(managed_float_array);
}

DEFINE_VARIABLE_WITH_SYMBOL(Managed_bignum_pool, Qmanaged_bignum_pool);

static Object Qab_gensym;          /* gensym */

/* GET-MANAGED-BIGNUM */
Object get_managed_bignum(length_1,value)
    Object length_1, value;
{
    Object available, gensym_pop_store, svref_arg_1, cons_1, next_cons, temp;
    Object svref_arg_2;
    SI_Long svref_arg_2_1;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(32,95);
    if (FIXNUM_GE(length_1,ISVREF(Managed_bignum_pool,(SI_Long)1L)))
	Managed_bignum_pool = adjust_managed_array(2,Managed_bignum_pool,
		FIXNUM_ADD1(length_1));
    available = FIXNUM_LE(ISVREF(Managed_bignum_pool,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(Managed_bignum_pool,
	    IFIX(FIXNUM_ADD(length_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(Managed_bignum_pool,(IFIX(length_1) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(length_1) & (SI_Long)1023L);
    if (available) {
	gensym_pop_store = Nil;
	svref_arg_1 = Managed_bignum_pool;
	cons_1 = FIXNUM_LE(ISVREF(svref_arg_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(svref_arg_1,
		IFIX(FIXNUM_ADD(length_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(svref_arg_1,(IFIX(length_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(length_1) & (SI_Long)1023L);
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	if (FIXNUM_LE(ISVREF(svref_arg_1,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(length_1,Managed_array_index_offset);
	    SVREF(svref_arg_1,temp) = next_cons;
	}
	else {
	    temp = ISVREF(svref_arg_1,(IFIX(length_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2_1 = IFIX(length_1) & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2_1) = next_cons;
	}
	return VALUES_1(gensym_pop_store);
    }
    else {
	if (PUSH_AREA(Dynamic_area,0))
	    result = copy_of_bignum(value);
	POP_AREA(0);
	return result;
    }
}

Object The_type_description_of_temporary_constant = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_temporary_constants, Qchain_of_available_temporary_constants);

DEFINE_VARIABLE_WITH_SYMBOL(Temporary_constant_count, Qtemporary_constant_count);

Object Chain_of_available_temporary_constants_vector = UNBOUND;

/* TEMPORARY-CONSTANT-STRUCTURE-MEMORY-USAGE */
Object temporary_constant_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(32,96);
    temp = Temporary_constant_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TEMPORARY-CONSTANT-COUNT */
Object outstanding_temporary_constant_count()
{
    Object def_structure_temporary_constant_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(32,97);
    gensymed_symbol = IFIX(Temporary_constant_count);
    def_structure_temporary_constant_variable = 
	    Chain_of_available_temporary_constants;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_temporary_constant_variable))
	goto end_loop;
    def_structure_temporary_constant_variable = 
	    ISVREF(def_structure_temporary_constant_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TEMPORARY-CONSTANT-1 */
Object reclaim_temporary_constant_1(temporary_constant)
    Object temporary_constant;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(32,98);
    inline_note_reclaim_cons(temporary_constant,Nil);
    structure_being_reclaimed = temporary_constant;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      temp = 
	      reclaim_managed_number_or_value_function(ISVREF(temporary_constant,
	      (SI_Long)1L));
      SVREF(temporary_constant,FIX((SI_Long)1L)) = temp;
      SVREF(temporary_constant,FIX((SI_Long)1L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_temporary_constants_vector,
	    IFIX(Current_thread_index));
    SVREF(temporary_constant,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_temporary_constants_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = temporary_constant;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TEMPORARY-CONSTANT */
Object reclaim_structure_for_temporary_constant(temporary_constant)
    Object temporary_constant;
{
    x_note_fn_call(32,99);
    return reclaim_temporary_constant_1(temporary_constant);
}

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

/* MAKE-PERMANENT-TEMPORARY-CONSTANT-STRUCTURE-INTERNAL */
Object make_permanent_temporary_constant_structure_internal()
{
    Object def_structure_temporary_constant_variable;
    Object defstruct_g2_temporary_constant_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(32,100);
    def_structure_temporary_constant_variable = Nil;
    atomic_incff_symval(Qtemporary_constant_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_temporary_constant_variable = Nil;
	gensymed_symbol = (SI_Long)3L;
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
	defstruct_g2_temporary_constant_variable = the_array;
	SVREF(defstruct_g2_temporary_constant_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_temporary_constant_g2_struct;
	def_structure_temporary_constant_variable = 
		defstruct_g2_temporary_constant_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* MAKE-TEMPORARY-CONSTANT-1-1 */
Object make_temporary_constant_1_1(constant_value_internal,constant_type)
    Object constant_value_internal, constant_type;
{
    Object def_structure_temporary_constant_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,101);
    def_structure_temporary_constant_variable = 
	    ISVREF(Chain_of_available_temporary_constants_vector,
	    IFIX(Current_thread_index));
    if (def_structure_temporary_constant_variable) {
	svref_arg_1 = Chain_of_available_temporary_constants_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_temporary_constant_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_temporary_constant_g2_struct;
    }
    else
	def_structure_temporary_constant_variable = 
		make_permanent_temporary_constant_structure_internal();
    inline_note_allocate_cons(def_structure_temporary_constant_variable,Nil);
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)1L)) = 
	    constant_value_internal;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)2L)) = 
	    constant_type;
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* MAKE-TEMPORARY-CONSTANT-NO-EXPIRATION */
Object make_temporary_constant_no_expiration(value,type)
    Object value, type;
{
    Object def_structure_temporary_constant_variable, temp, temp_1;
    Object svref_new_value, new_float, amf_available_array_cons_qm, amf_array;
    Object amf_result, new_long, temp_2;
    SI_int64 aref_new_value_1;
    double aref_new_value;

    x_note_fn_call(32,102);
    def_structure_temporary_constant_variable = 
	    ISVREF(Chain_of_available_temporary_constants_vector,
	    IFIX(Current_thread_index));
    if (def_structure_temporary_constant_variable) {
	temp = Chain_of_available_temporary_constants_vector;
	temp_1 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_temporary_constant_variable,
		(SI_Long)0L);
	SVREF(temp,temp_1) = svref_new_value;
	SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_temporary_constant_g2_struct;
    }
    else
	def_structure_temporary_constant_variable = 
		make_permanent_temporary_constant_structure_internal();
    inline_note_allocate_cons(def_structure_temporary_constant_variable,Nil);
    if (FIXNUMP(value) || SYMBOLP(value))
	new_float = value;
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
    }
    else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	new_long = allocate_managed_long_box();
	aref_new_value_1 = INTEGER_TO_INT64(value);
	set_aref1(new_long,FIX((SI_Long)0L),
		INT64_TO_INTEGER(aref_new_value_1));
	new_float = new_long;
    }
    else if (text_string_p(value))
	new_float = copy_text_string(value);
    else if (BIGNUMP(value)) {
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
	temp_2 = coerce_bignum_to_gensym_float(value);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    }
    else
	new_float = value;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)1L)) = 
	    new_float;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)2L)) = type;
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* MAKE-TEMPORARY-CONSTANT-GIVEN-MANAGED-VALUE-NO-EXPIRATION */
Object make_temporary_constant_given_managed_value_no_expiration(managed_value,
	    type)
    Object managed_value, type;
{
    Object def_structure_temporary_constant_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,103);
    def_structure_temporary_constant_variable = 
	    ISVREF(Chain_of_available_temporary_constants_vector,
	    IFIX(Current_thread_index));
    if (def_structure_temporary_constant_variable) {
	svref_arg_1 = Chain_of_available_temporary_constants_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_temporary_constant_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_temporary_constant_g2_struct;
    }
    else
	def_structure_temporary_constant_variable = 
		make_permanent_temporary_constant_structure_internal();
    inline_note_allocate_cons(def_structure_temporary_constant_variable,Nil);
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)1L)) = 
	    managed_value;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)2L)) = type;
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* MAKE-TEMPORARY-CONSTANT-COPYING-MANAGED-VALUE-NO-EXPIRATION */
Object make_temporary_constant_copying_managed_value_no_expiration(managed_value,
	    type)
    Object managed_value, type;
{
    Object def_structure_temporary_constant_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,104);
    def_structure_temporary_constant_variable = 
	    ISVREF(Chain_of_available_temporary_constants_vector,
	    IFIX(Current_thread_index));
    if (def_structure_temporary_constant_variable) {
	temp = Chain_of_available_temporary_constants_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_temporary_constant_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_temporary_constant_g2_struct;
    }
    else
	def_structure_temporary_constant_variable = 
		make_permanent_temporary_constant_structure_internal();
    inline_note_allocate_cons(def_structure_temporary_constant_variable,Nil);
    temp = FIXNUMP(managed_value) || SYMBOLP(managed_value) ? 
	    managed_value : copy_evaluation_value_1(managed_value);
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)1L)) = temp;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)2L)) = type;
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* COPY-TEMPORARY-CONSTANT */
Object copy_temporary_constant(temporary_constant)
    Object temporary_constant;
{
    Object def_structure_temporary_constant_variable, temp, svref_arg_2;
    Object svref_new_value, managed_number_or_value;

    x_note_fn_call(32,105);
    def_structure_temporary_constant_variable = 
	    ISVREF(Chain_of_available_temporary_constants_vector,
	    IFIX(Current_thread_index));
    if (def_structure_temporary_constant_variable) {
	temp = Chain_of_available_temporary_constants_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_temporary_constant_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_temporary_constant_g2_struct;
    }
    else
	def_structure_temporary_constant_variable = 
		make_permanent_temporary_constant_structure_internal();
    inline_note_allocate_cons(def_structure_temporary_constant_variable,Nil);
    managed_number_or_value = ISVREF(temporary_constant,(SI_Long)1L);
    temp = FIXNUMP(managed_number_or_value) || 
	    SYMBOLP(managed_number_or_value) ? managed_number_or_value : 
	    copy_evaluation_value_1(managed_number_or_value);
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)1L)) = temp;
    temp = ISVREF(temporary_constant,(SI_Long)2L);
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)2L)) = temp;
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* RECLAIM-IF-TEMPORARY-CONSTANT-FUNCTION */
Object reclaim_if_temporary_constant_function(thing)
    Object thing;
{
    x_note_fn_call(32,106);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	return reclaim_temporary_constant_1(thing);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Recycled_resumption_conses, Qrecycled_resumption_conses);

/* WORK-ON-SUSPENDABLE-TASK */
Object work_on_suspendable_task(suspendable_function,objects,other_args,
	    resumption_qm,resumption_stack)
    Object suspendable_function, objects, other_args, resumption_qm;
    Object resumption_stack;
{
    Object temp, remaining_objects, suspendable_subfunction_qm, subobjects;
    Object other_args_for_suspendable_subfunction, cdddr_of_resumption_stack;
    Object temp_1, remaining_recycled_resumption_conses, new_top_of_stack;
    char temp_2;
    Object result;

    x_note_fn_call(32,107);
  next_loop:
    temp = SYMBOL_FUNCTION(suspendable_function);
    result = FUNCALL_3(temp,objects,other_args,resumption_qm);
    MVS_4(result,remaining_objects,suspendable_subfunction_qm,subobjects,
	    other_args_for_suspendable_subfunction);
    if ( !TRUEP(remaining_objects)) {
	if (resumption_qm) {
	    cdddr_of_resumption_stack = CDDDR(resumption_stack);
	    temp_1 = Recycled_resumption_conses;
	    M_CDDDR(resumption_stack) = temp_1;
	    Recycled_resumption_conses = nconc2(THIRD(resumption_stack),
		    resumption_stack);
	    resumption_stack = cdddr_of_resumption_stack;
	}
	if (resumption_stack) {
	    suspendable_function = FIRST(resumption_stack);
	    objects = SECOND(resumption_stack);
	    other_args = THIRD(resumption_stack);
	    resumption_qm = T;
	    temp_2 = TRUEP(resumption_qm);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else {
	if ( !TRUEP(resumption_qm)) {
	    remaining_recycled_resumption_conses = 
		    CDDDR(Recycled_resumption_conses);
	    if ( !TRUEP(remaining_recycled_resumption_conses)) {
		new_top_of_stack = gensym_list_3(suspendable_function,Nil,
			other_args);
		M_CDDDR(new_top_of_stack) = resumption_stack;
		resumption_stack = new_top_of_stack;
	    }
	    else {
		temp = Recycled_resumption_conses;
		temp_1 = Recycled_resumption_conses;
		M_FIRST(temp_1) = suspendable_function;
		temp_1 = Recycled_resumption_conses;
		M_THIRD(temp_1) = other_args;
		temp_1 = Recycled_resumption_conses;
		M_CDDDR(temp_1) = resumption_stack;
		Recycled_resumption_conses = 
			remaining_recycled_resumption_conses;
		resumption_stack = temp;
	    }
	}
	M_SECOND(resumption_stack) = remaining_objects;
	if (suspendable_subfunction_qm) {
	    suspendable_function = suspendable_subfunction_qm;
	    objects = subobjects;
	    other_args = other_args_for_suspendable_subfunction;
	    resumption_qm = Nil;
	    temp_2 = TRUEP(T);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    if ( !temp_2)
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(resumption_stack);
    return VALUES_1(Qnil);
}

/* RESUME-TASK */
Object resume_task(resumption_stack)
    Object resumption_stack;
{
    Object gensymed_symbol, function, objects, other_args;

    x_note_fn_call(32,108);
    gensymed_symbol = resumption_stack;
    function = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    objects = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    other_args = CAR(gensymed_symbol);
    return work_on_suspendable_task(function,objects,other_args,T,
	    resumption_stack);
}

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_interned_gensym_strings, Qcount_of_interned_gensym_strings);

DEFINE_VARIABLE_WITH_SYMBOL(Memory_used_for_interned_gensym_strings, Qmemory_used_for_interned_gensym_strings);

/* GENSYM-SYMBOL-NAME */
Object gensym_symbol_name(symbol)
    Object symbol;
{
    Object gensym_string;
    SI_Long ab_loop_bind_, i;
    char temp;
    char *name;
    int len;

    x_note_fn_call(32,109);
    name = isymbol_name(symbol);
    len = strlen(name);
    gensym_string = len > 
	    IFIX(Maximum_suggested_length_for_simple_gensym_strings) ? 
	    obtain_long_enough_adjustable_gensym_string(INT_TO_FIXNUM(len)) 
	    : obtain_simple_gensym_string(INT_TO_FIXNUM(len));
    if (SIMPLE_STRING_P(gensym_string)) {
	ab_loop_bind_ = len;
	i = (SI_Long)0L;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	temp = name[i];
	SET_ISCHAR(gensym_string,i,temp);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else {
	ab_loop_bind_ = len;
	i = (SI_Long)0L;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	temp = name[i];
	SET_ICHAR(gensym_string,i,temp);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(gensym_string);
}

DEFINE_VARIABLE_WITH_SYMBOL(Nil_interned, Qnil_interned);

/* INTERN-GENSYM-STRING */
Object intern_gensym_string varargs_1(int, n)
{
    Object gensym_string;
    Object package_qm, temp, symbol, pre_existing_symbol_p;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(32,110);
    INIT_ARGS_nonrelocating();
    gensym_string = REQUIRED_ARG_nonrelocating();
    package_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = package_qm;
    if (temp);
    else
	temp = Package;
    result = intern(gensym_string,temp);
    MVS_2(result,symbol,pre_existing_symbol_p);
    if ( !TRUEP(pre_existing_symbol_p)) {
	atomic_incff_symval(Qcount_of_interned_gensym_strings,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qmemory_used_for_interned_gensym_strings,
		FIX((SI_Long)25L + IFIX(length(gensym_string))));
    }
    if ( !EQ(INLINE_CACHED_SYMBOL_NAME(symbol),gensym_string))
	reclaim_gensym_string(gensym_string);
    if (EQ(symbol,Nil_interned))
	return VALUES_1(Nil);
    else
	return VALUES_1(symbol);
}

/* INTERN-USING-STRING-BUFFER */
Object intern_using_string_buffer(string_buffer,length_1,package_qm)
    Object string_buffer, length_1, package_qm;
{
    Object char_new_value, temp, symbol, pre_existing_symbol_p;
    Object result;

    x_note_fn_call(32,111);
    char_new_value = CODE_CHAR(FIX((SI_Long)0L));
    SET_CHAR(string_buffer,length_1,char_new_value);
    SET_FILL_POINTER(string_buffer,length_1);
    temp = package_qm;
    if (temp);
    else
	temp = Package;
    result = intern(string_buffer,temp);
    MVS_2(result,symbol,pre_existing_symbol_p);
    if ( !TRUEP(pre_existing_symbol_p)) {
	atomic_incff_symval(Qcount_of_interned_gensym_strings,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qmemory_used_for_interned_gensym_strings,length_1);
    }
    return VALUES_1(EQ(symbol,Nil_interned) ? Nil : symbol);
}

/* POSITION-OF-TWO-COLONS */
Object position_of_two_colons(string_1)
    Object string_1;
{
    Object length_1, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(32,112);
    if (text_string_p(string_1)) {
	length_1 = lengthw(string_1);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(FIXNUM_SUB1(length_1));
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if (UBYTE_16_ISAREF_1(string_1,i) == (SI_Long)58L && 
		UBYTE_16_ISAREF_1(string_1,i + (SI_Long)1L) == (SI_Long)58L) {
	    temp = FIX(i);
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    else {
	length_1 = length(string_1);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(FIXNUM_SUB1(length_1));
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	if (CHAR_EQ(CHR(ICHAR(string_1,i)),CHR(':')) && 
		CHAR_EQ(CHR(ICHAR(string_1,i + (SI_Long)1L)),CHR(':'))) {
	    temp = FIX(i);
	    goto end_2;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_2:;
    }
    return VALUES_1(temp);
}

/* GET-MEMORY-USED-FOR-INTERNED-TEXT-STRINGS */
Object get_memory_used_for_interned_text_strings()
{
    x_note_fn_call(32,113);
    return VALUES_1(Memory_used_for_interned_gensym_strings);
}

Object Most_positive_fixnum_floor_10 = UNBOUND;

Object Most_negative_fixnum_ceiling_10 = UNBOUND;

/* VALUE-TIMES-TEN-MINUS-WEIGHT->=-MOST-NEGATIVE-FIXNUM-P */
Object value_times_ten_minus_weight_gt_eq_most_negative_fixnum_p(value,weight)
    Object value, weight;
{
    x_note_fn_call(32,114);
    return VALUES_1(FIXNUM_GE(FIXNUM_NEGATE(value),
	    Most_negative_fixnum_ceiling_10) ? (IFIX(weight) <= 
	    IFIX(value) * (SI_Long)10L - IFIX(Most_negative_fixnum) ? T : 
	    Nil) : Qnil);
}

/* READ-NUMBER-WITHOUT-EXPONENT */
Object read_number_without_exponent(the_string,start_index,end_index,
	    allowed_non_fixnum_number_type_qm)
    Object the_string, start_index, end_index;
    Object allowed_non_fixnum_number_type_qm;
{
    Object non_fixnum_number_type_qm, value_so_far, character_1;
    Object number_of_ignored_digits, index_of_decimal_point_qm, initial_index;
    Object weight_qm, temp_2, temp_3;
    SI_Long gensymed_symbol;
    char negative_qm, positive_char_qm, temp;
    double arg, arg_1, arg_2, temp_1;

    x_note_fn_call(32,115);
    non_fixnum_number_type_qm = Nil;
    value_so_far = FIX((SI_Long)0L);
    character_1 = FIX(UBYTE_16_ISAREF_1(the_string,IFIX(start_index)));
    negative_qm = IFIX(character_1) == (SI_Long)45L;
    positive_char_qm = IFIX(character_1) == (SI_Long)43L;
    number_of_ignored_digits = FIX((SI_Long)0L);
    index_of_decimal_point_qm = Nil;
    initial_index = start_index;
    weight_qm = Nil;
    if (negative_qm || positive_char_qm) {
	start_index = FIXNUM_ADD1(start_index);
	if (FIXNUM_EQ(start_index,end_index))
	    goto end_loop;
	else
	    character_1 = FIX(UBYTE_16_ISAREF_1(the_string,IFIX(start_index)));
    }
  next_loop:
    gensymed_symbol = IFIX(character_1);
    weight_qm = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
    if (weight_qm) {
	if (negative_qm)
	    weight_qm = FIXNUM_NEGATE(weight_qm);
	temp = TRUEP(non_fixnum_number_type_qm);
	if (temp);
	else
	    temp = FIXNUM_LT(FIXNUM_ABS(value_so_far),
		    Most_positive_fixnum_floor_10);
	if (temp);
	else {
	    non_fixnum_number_type_qm = allowed_non_fixnum_number_type_qm;
	    if (non_fixnum_number_type_qm) {
		if (EQ(allowed_non_fixnum_number_type_qm,Qgensym_float))
		    value_so_far = lfloat(value_so_far,float_constant);
		temp = TRUEP(T);
	    }
	    else
		temp = TRUEP(Nil);
	}
	if (temp);
	else
	    temp = negative_qm ? FIXNUM_GE(FIXNUM_NEGATE(value_so_far),
		    Most_negative_fixnum_ceiling_10) && IFIX(weight_qm) >= 
		    IFIX(Most_negative_fixnum) - 
		    IFIX(FIXNUM_NEGATE(value_so_far)) * (SI_Long)10L : 
		    FIXNUM_LE(value_so_far,Most_positive_fixnum_floor_10) 
		    && IFIX(weight_qm) <= IFIX(Most_positive_fixnum) - 
		    IFIX(value_so_far) * (SI_Long)10L;
	if (temp) {
	    temp =  !EQ(non_fixnum_number_type_qm,Qgensym_float);
	    if (temp);
	    else {
		arg = -1.7976931348623158E+307;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(value_so_far);
		arg_2 = 1.7976931348623158E+307;
		temp = arg <= arg_1 && arg_1 <= arg_2 &&  
			!inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1) ?  
			!inline_nanp_for_comparison(arg_2) : TRUEP(Qnil);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if ( !TRUEP(non_fixnum_number_type_qm))
		value_so_far = FIX((SI_Long)10L * IFIX(value_so_far) + 
			IFIX(weight_qm));
	    else if (EQ(allowed_non_fixnum_number_type_qm,Qgensym_float)) {
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(value_so_far);
		value_so_far = add(DOUBLE_TO_DOUBLE_FLOAT(10.0 * temp_1),
			weight_qm);
	    }
	    else
		value_so_far = add(ltimes(FIX((SI_Long)10L),value_so_far),
			weight_qm);
	}
	else
	    number_of_ignored_digits = FIXNUM_ADD1(number_of_ignored_digits);
    }
    else if (IFIX(character_1) == (SI_Long)46L &&  
	    !TRUEP(index_of_decimal_point_qm))
	index_of_decimal_point_qm = start_index;
    else
	goto end_loop;
    start_index = FIXNUM_ADD1(start_index);
    if (FIXNUM_EQ(start_index,end_index))
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(the_string,IFIX(start_index)));
    goto next_loop;
  end_loop:
    temp_2 = value_so_far;
    temp_3 = index_of_decimal_point_qm ? 
	    FIXNUM_ADD(FIXNUM_ADD1(FIXNUM_MINUS(index_of_decimal_point_qm,
	    start_index)),number_of_ignored_digits) : number_of_ignored_digits;
    return VALUES_3(temp_2,temp_3,(negative_qm || positive_char_qm) && 
	    FIXNUM_LE(start_index,FIXNUM_ADD1(initial_index)) ? 
	    initial_index : start_index);
    return VALUES_1(Qnil);
}

static Object string_constant;     /* "number is too large" */

/* READ-POSITIVE-FIXNUM-FROM-STRING */
Object read_positive_fixnum_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object digit_character, digit_qm;
    SI_Long string_index, fixnum_so_far, gensymed_symbol;

    x_note_fn_call(32,116);
    string_index = IFIX(start_index);
    digit_character = FIX((SI_Long)97L);
    digit_qm = Nil;
    fixnum_so_far = (SI_Long)0L;
  next_loop:
    if ( !(string_index < IFIX(end_index)))
	goto end_loop;
    digit_character = FIX(UBYTE_16_ISAREF_1(string_1,string_index));
    gensymed_symbol = IFIX(digit_character);
    digit_qm = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
    if (digit_qm) {
	if (fixnum_so_far < IFIX(Most_positive_fixnum_floor_10) || 
		fixnum_so_far <= IFIX(Most_positive_fixnum_floor_10) && 
		IFIX(digit_qm) <= IFIX(Most_positive_fixnum) - 
		fixnum_so_far * (SI_Long)10L)
	    fixnum_so_far = fixnum_so_far * (SI_Long)10L + IFIX(digit_qm);
	else
	    return VALUES_3(Nil,FIX(string_index + (SI_Long)1L),
		    string_constant);
    }
    else
	goto end_loop;
    string_index = string_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_3( !(string_index == IFIX(start_index)) ? 
	    FIX(fixnum_so_far) : Nil,FIX(string_index),Nil);
    return VALUES_1(Qnil);
}

static Object string_constant_1;   /* "negative number is too large" */

/* READ-NEGATIVE-FIXNUM-FROM-STRING */
Object read_negative_fixnum_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object string_index, digit_character, digit_qm, fixnum_so_far, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(32,117);
    string_index = FIXNUM_ADD1(start_index);
    digit_character = Nil;
    digit_qm = Nil;
    fixnum_so_far = FIX((SI_Long)0L);
    if ( !(UBYTE_16_ISAREF_1(string_1,IFIX(start_index)) == (SI_Long)45L))
	return VALUES_3(Nil,start_index,Nil);
  next_loop:
    if ( !FIXNUM_LT(string_index,end_index))
	goto end_loop;
    digit_character = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(string_index)));
    gensymed_symbol = IFIX(digit_character);
    digit_qm = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
    if (digit_qm) {
	if (FIXNUM_GT(fixnum_so_far,Most_negative_fixnum_ceiling_10) || 
		value_times_ten_minus_weight_gt_eq_most_negative_fixnum_p(fixnum_so_far,
		digit_qm))
	    fixnum_so_far = FIX(IFIX(fixnum_so_far) * (SI_Long)10L - 
		    IFIX(digit_qm));
	else {
	    temp = FIXNUM_ADD1(string_index);
	    return VALUES_3(Nil,temp,string_constant_1);
	}
    }
    else
	goto end_loop;
    string_index = FIXNUM_ADD1(string_index);
    goto next_loop;
  end_loop:
    return VALUES_3( !FIXNUM_EQ(string_index,start_index) ? fixnum_so_far :
	     Nil,string_index,Nil);
    return VALUES_1(Qnil);
}

/* READ-FIXNUM-FROM-STRING */
Object read_fixnum_from_string varargs_1(int, n)
{
    Object string_1;
    Object start_index_qm, end_index_qm, start_index, end_index;
    SI_Long digit_character;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,118);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    start_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    start_index = start_index_qm;
    if (start_index);
    else
	start_index = FIX((SI_Long)0L);
    end_index = end_index_qm;
    if (end_index);
    else
	end_index = text_string_length(string_1);
    digit_character = UBYTE_16_ISAREF_1(string_1,IFIX(start_index));
    if (digit_character == (SI_Long)45L)
	return read_negative_fixnum_from_string(string_1,start_index,
		end_index);
    else if (digit_character == (SI_Long)43L)
	return read_positive_fixnum_from_string(string_1,
		FIXNUM_ADD1(start_index),end_index);
    else
	return read_positive_fixnum_from_string(string_1,start_index,
		end_index);
}

Object Most_positive_int64_floor_10 = UNBOUND;

/* VALUE-TIMES-TEN-PLUS-WEIGHT-<=-MOST-POSITIVE-INT64-P */
Object value_times_ten_plus_weight_lt_eq_most_positive_int64_p(value_init,
	    weight_init)
    Object value_init, weight_init;
{
    Object temp;
    SI_int64 value, weight;

    x_note_fn_call(32,119);
    value = INTEGER_TO_INT64(value_init);
    weight = INTEGER_TO_INT64(weight_init);
    if (NUM_LE(INT64_TO_INTEGER(value),Most_positive_int64_floor_10)) {
	temp = minus(Most_positive_int64,ltimes(INT64_TO_INTEGER(value),
		FIX((SI_Long)10L)));
	temp = NUM_LE(INT64_TO_INTEGER(weight),temp) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qoverflow;           /* overflow */

/* READ-POSITIVE-LONG-FROM-STRING */
Object read_positive_long_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object digit_character, digit_qm, temp;
    SI_Long string_index, gensymed_symbol;
    SI_int64 num_so_far;

    x_note_fn_call(32,120);
    string_index = IFIX(start_index);
    digit_character = FIX((SI_Long)97L);
    digit_qm = Nil;
    num_so_far = (SI_int64)(SI_Long)0L;
  next_loop:
    if ( !(string_index < IFIX(end_index)))
	goto end_loop;
    digit_character = FIX(UBYTE_16_ISAREF_1(string_1,string_index));
    gensymed_symbol = IFIX(digit_character);
    digit_qm = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
    if (digit_qm) {
	if (NUM_LT(INT64_TO_INTEGER(num_so_far),
		Most_positive_int64_floor_10) || 
		value_times_ten_plus_weight_lt_eq_most_positive_int64_p(INT64_TO_INTEGER(num_so_far),
		digit_qm)) {
	    temp = add(ltimes(INT64_TO_INTEGER(num_so_far),
		    FIX((SI_Long)10L)),digit_qm);
	    num_so_far = INTEGER_TO_INT64(temp);
	}
	else
	    return VALUES_3(Qoverflow,FIX(string_index + (SI_Long)1L),
		    string_constant);
    }
    else
	goto end_loop;
    string_index = string_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_3( !(string_index == IFIX(start_index)) ? 
	    INT64_TO_INTEGER(num_so_far) : Nil,FIX(string_index),Nil);
    return VALUES_1(Qnil);
}

Object Most_negative_int64_ceiling_10 = UNBOUND;

/* VALUE-TIMES-TEN-MINUS-WEIGHT->=-MOST-NEGATIVE-INT64-P */
Object value_times_ten_minus_weight_gt_eq_most_negative_int64_p(value_init,
	    weight_init)
    Object value_init, weight_init;
{
    Object temp;
    SI_int64 value, weight;

    x_note_fn_call(32,121);
    value = INTEGER_TO_INT64(value_init);
    weight = INTEGER_TO_INT64(weight_init);
    temp = negate(INT64_TO_INTEGER(value));
    if (NUM_GE(temp,Most_negative_int64_ceiling_10)) {
	temp = minus(ltimes(INT64_TO_INTEGER(value),FIX((SI_Long)10L)),
		Most_negative_int64);
	temp = NUM_LE(INT64_TO_INTEGER(weight),temp) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qunderflow;          /* underflow */

/* READ-NEGATIVE-LONG-FROM-STRING */
Object read_negative_long_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object digit_character, digit_qm, num_so_far;
    SI_Long string_index, gensymed_symbol;

    x_note_fn_call(32,122);
    string_index = IFIX(start_index);
    digit_character = FIX((SI_Long)97L);
    digit_qm = Nil;
    num_so_far = FIX((SI_Long)0L);
  next_loop:
    if ( !(string_index < IFIX(end_index)))
	goto end_loop;
    digit_character = FIX(UBYTE_16_ISAREF_1(string_1,string_index));
    gensymed_symbol = IFIX(digit_character);
    digit_qm = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
    if (digit_qm) {
	if (NUM_GT(num_so_far,Most_negative_int64_ceiling_10) || 
		value_times_ten_minus_weight_gt_eq_most_negative_int64_p(num_so_far,
		digit_qm))
	    num_so_far = minus(ltimes(num_so_far,FIX((SI_Long)10L)),digit_qm);
	else
	    return VALUES_3(Qunderflow,FIX(string_index + (SI_Long)1L),
		    string_constant_1);
    }
    else
	goto end_loop;
    string_index = string_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_3( !(string_index == IFIX(start_index)) ? num_so_far : 
	    Nil,FIX(string_index),Nil);
    return VALUES_1(Qnil);
}

/* READ-LONG-FROM-STRING */
Object read_long_from_string varargs_1(int, n)
{
    Object string_1;
    Object start_index_qm, end_index_qm, start_index, end_index;
    SI_Long digit_character;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,123);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    start_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    start_index = start_index_qm;
    if (start_index);
    else
	start_index = FIX((SI_Long)0L);
    end_index = end_index_qm;
    if (end_index);
    else
	end_index = text_string_length(string_1);
    digit_character = UBYTE_16_ISAREF_1(string_1,IFIX(start_index));
    if (digit_character == (SI_Long)45L)
	return read_negative_long_from_string(string_1,
		FIXNUM_ADD1(start_index),end_index);
    else if (digit_character == (SI_Long)43L)
	return read_positive_long_from_string(string_1,
		FIXNUM_ADD1(start_index),end_index);
    else
	return read_positive_long_from_string(string_1,start_index,end_index);
}

/* C-READ_FLOAT_FROM_STRING */
Object c_read_float_from_string(string_1)
    Object string_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(32,124);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(string_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = string_1;
    temp = DOUBLE_TO_DOUBLE_FLOAT(g2ext_read_float_from_string(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* READ-FLOAT-FROM-STRING */
Object read_float_from_string(string_1,inclusive_start_index,
	    exclusive_final_index)
    Object string_1, inclusive_start_index, exclusive_final_index;
{
    Object substring, temp;

    x_note_fn_call(32,125);
    substring = 
	    obtain_simple_gensym_string(FIXNUM_MINUS(exclusive_final_index,
	    inclusive_start_index));
    copy_portion_of_wide_string_octets_into_simple_gensym_string(string_1,
	    inclusive_start_index,exclusive_final_index,substring,
	    FIX((SI_Long)0L));
    temp = c_read_float_from_string(substring);
    reclaim_gensym_string(substring);
    return VALUES_1(temp);
}

Object Most_positive_fixnum_floor_2 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Current_index, Qcurrent_index);

static Object float_constant_3;    /* 308.25471127925886 */

static Object string_constant_2;   /* "exponent of number is out of range" */

/* READ-NUMBER-FROM-STRING */
Object read_number_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object current_index, managed_value_qm, number_exists_p, whole_number;
    Object exponent_qm, end_index_of_mantissa, whole_number_for_exponent;
    Object exponent_for_exponent, end_index_of_exponent;
    Object store_managed_number_or_value_arg;
    SI_Long start_index_for_exponent;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(32,126);
    current_index = FIX((SI_Long)0L);
    managed_value_qm = Nil;
    number_exists_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  result = read_number_without_exponent(string_1,start_index,
		  end_index,Qgensym_float);
	  MVS_3(result,whole_number,exponent_qm,end_index_of_mantissa);
	  if (FIXNUM_LE(end_index_of_mantissa,start_index))
	      number_exists_p = Nil;
	  else {
	      start_index_for_exponent = 
		      IFIX(FIXNUM_ADD1(end_index_of_mantissa));
	      Current_index = end_index_of_mantissa;
	      if (start_index_for_exponent < IFIX(end_index) && 
		      g2_exponent_marker_p(FIX(UBYTE_16_ISAREF_1(string_1,
		      IFIX(end_index_of_mantissa))))) {
		  result = read_number_without_exponent(string_1,
			  FIX(start_index_for_exponent),end_index,Nil);
		  MVS_3(result,whole_number_for_exponent,
			  exponent_for_exponent,end_index_of_exponent);
		  if (IFIX(end_index_of_exponent) == start_index_for_exponent);
		  else if (IFIX(exponent_for_exponent) == (SI_Long)0L && 
			  FIXNUM_LT(FIXNUM_ABS(whole_number_for_exponent),
			  Most_positive_fixnum_floor_2)) {
		      Current_index = end_index_of_exponent;
		      exponent_qm = FIXNUM_ADD(exponent_qm,
			      whole_number_for_exponent);
		  }
		  else
		      exponent_qm = Nil;
	      }
	      if ( !TRUEP(exponent_qm) ||  !(IFIX(exponent_qm) == 
		      (SI_Long)0L) && FIXNUM_GT(FIXNUM_ABS(exponent_qm),
		      lfloor(minus(float_constant_3,
		      llog(add1(l_abs(whole_number)),FIX((SI_Long)10L))),_)))
		  managed_value_qm = Nil;
	      else if (IFIX(exponent_qm) == (SI_Long)0L && 
		      NUM_LE(Most_negative_fixnum,whole_number) && 
		      NUM_LE(whole_number,Most_positive_fixnum)) {
		  store_managed_number_or_value_arg = whole_number;
		  managed_value_qm = 
			  store_managed_number_or_value_function(managed_value_qm,
			  store_managed_number_or_value_arg);
	      }
	      else {
		  store_managed_number_or_value_arg = 
			  lfloat(read_float_from_string(string_1,
			  start_index,end_index),float_constant);
		  managed_value_qm = 
			  store_managed_number_or_value_function(managed_value_qm,
			  store_managed_number_or_value_arg);
	      }
	  }
      }
      POP_LOCAL_ALLOCATION(0,0);
      if (managed_value_qm)
	  result = VALUES_3(managed_value_qm,Current_index,Nil);
      else
	  result = VALUES_3(Nil,start_index,number_exists_p ? 
		  string_constant_2 : Nil);
    POP_SPECIAL();
    return result;
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_3;   /* "symbol is too big" */

static Object Knil;                /* :nil */

/* READ-SYMBOL-FROM-STRING */
Object read_symbol_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object current_index, string_length_so_far, character_1, string_to_intern;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object code, simple_or_wide_character, thing, temp, schar_arg_2;
    Object schar_new_value, managed_symbol, store_managed_number_or_value_arg;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(32,127);
    current_index = start_index;
    string_length_so_far = FIX((SI_Long)0L);
    character_1 = Nil;
    string_to_intern = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,5);
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
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		    (SI_Long)16L));
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		    1);
	      current_twriting_output_type = Qwide_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		if (FIXNUM_LE(FIXNUM_MINUS(end_index,start_index),
			Maximum_length_of_g2_symbol_name)) {
		  next_loop:
		    if ( !FIXNUM_LT(Current_index,end_index))
			goto end_loop;
		    character_1 = FIX(UBYTE_16_ISAREF_1(string_1,
			    IFIX(Current_index)));
		    if (simple_symbol_character_p(character_1)) {
			code = character_1;
			if (IFIX(code) < (SI_Long)127L)
			    simple_or_wide_character = (SI_Long)97L <= 
				    IFIX(code) && IFIX(code) <= 
				    (SI_Long)122L ? FIX(IFIX(code) + 
				    (SI_Long)-32L) : code;
			else {
			    simple_or_wide_character = 
				    unicode_uppercase_if_lowercase(code);
			    if (simple_or_wide_character);
			    else
				simple_or_wide_character = code;
			}
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = simple_or_wide_character;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp = Current_gensym_string;
			    schar_arg_2 = 
				    Fill_pointer_for_current_gensym_string;
			    thing = simple_or_wide_character;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp,schar_arg_2,schar_new_value);
			    temp = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp;
			}
			temp = FIXNUM_ADD1(Current_index);
			Current_index = temp;
		    }
		    else
			goto end_1;
		    goto next_loop;
		  end_loop:
		  end_1:;
		}
		else {
		  next_loop_1:
		    if ( !(FIXNUM_LT(Current_index,end_index) && 
			    FIXNUM_LE(string_length_so_far,
			    Maximum_length_of_g2_symbol_name)))
			goto end_loop_1;
		    character_1 = FIX(UBYTE_16_ISAREF_1(string_1,
			    IFIX(Current_index)));
		    if (simple_symbol_character_p(character_1)) {
			code = character_1;
			if (IFIX(code) < (SI_Long)127L)
			    simple_or_wide_character = (SI_Long)97L <= 
				    IFIX(code) && IFIX(code) <= 
				    (SI_Long)122L ? FIX(IFIX(code) + 
				    (SI_Long)-32L) : code;
			else {
			    simple_or_wide_character = 
				    unicode_uppercase_if_lowercase(code);
			    if (simple_or_wide_character);
			    else
				simple_or_wide_character = code;
			}
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = simple_or_wide_character;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp = Current_gensym_string;
			    schar_arg_2 = 
				    Fill_pointer_for_current_gensym_string;
			    thing = simple_or_wide_character;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp,schar_arg_2,schar_new_value);
			    temp = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp;
			}
			string_length_so_far = 
				FIXNUM_ADD1(string_length_so_far);
			temp = FIXNUM_ADD1(Current_index);
			Current_index = temp;
		    }
		    else
			goto end_2;
		    goto next_loop_1;
		  end_loop_1:
		  end_2:;
		}
		string_to_intern = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      if (FIXNUM_GT(string_length_so_far,Maximum_length_of_g2_symbol_name)) {
	  reclaim_text_string(string_to_intern);
	  result = VALUES_3(Nil,Current_index,string_constant_3);
      }
      else if (FIXNUM_EQ(Current_index,start_index)) {
	  reclaim_text_string(string_to_intern);
	  result = VALUES_3(Nil,Current_index,Nil);
      }
      else {
	  managed_symbol = Nil;
	  store_managed_number_or_value_arg = intern_text_string(1,
		  string_to_intern);
	  if (store_managed_number_or_value_arg);
	  else
	      store_managed_number_or_value_arg = Knil;
	  managed_symbol = 
		  store_managed_number_or_value_function(managed_symbol,
		  store_managed_number_or_value_arg);
	  result = VALUES_3(managed_symbol,Current_index,Nil);
      }
    POP_SPECIAL();
    return result;
}

/* SUBSTRING-EQUAL */
Object substring_equal(string_1,start_index_1,end_index_1,string_2,
	    start_index_2,end_index_2)
    Object string_1, start_index_1, end_index_1, string_2, start_index_2;
    Object end_index_2;
{
    Object current_index_1, current_index_2, temp, temp_1;
    SI_Long wide_character, code;

    x_note_fn_call(32,128);
    if (FIXNUM_EQ(FIXNUM_MINUS(end_index_1,start_index_1),
	    FIXNUM_MINUS(end_index_2,start_index_2))) {
	current_index_1 = start_index_1;
	current_index_2 = start_index_2;
      next_loop:
	if ( !FIXNUM_LT(current_index_1,end_index_1))
	    goto end_loop;
	wide_character = UBYTE_16_ISAREF_1(string_1,IFIX(current_index_1));
	code = wide_character;
	if (code < (SI_Long)127L)
	    temp = (SI_Long)97L <= code && code <= (SI_Long)122L ? 
		    FIX(code + (SI_Long)-32L) : FIX(code);
	else {
	    temp = unicode_uppercase_if_lowercase(FIX(code));
	    if (temp);
	    else
		temp = FIX(code);
	}
	wide_character = UBYTE_16_ISAREF_1(string_2,IFIX(current_index_2));
	code = wide_character;
	if (code < (SI_Long)127L)
	    temp_1 = (SI_Long)97L <= code && code <= (SI_Long)122L ? 
		    FIX(code + (SI_Long)-32L) : FIX(code);
	else {
	    temp_1 = unicode_uppercase_if_lowercase(FIX(code));
	    if (temp_1);
	    else
		temp_1 = FIX(code);
	}
	if ( !NUM_EQ(temp,temp_1))
	    return VALUES_1(Nil);
	current_index_1 = FIXNUM_ADD1(current_index_1);
	current_index_2 = FIXNUM_ADD1(current_index_2);
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* SKIP-SPACES-IN-STRING */
Object skip_spaces_in_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object temp;

    x_note_fn_call(32,129);
  next_loop:
    if ( !(FIXNUM_LT(start_index,end_index) && UBYTE_16_ISAREF_1(string_1,
	    IFIX(start_index)) == (SI_Long)32L))
	goto end_loop;
    start_index = FIXNUM_ADD1(start_index);
    goto next_loop;
  end_loop:
    temp = start_index;
    goto end_1;
    temp = Qnil;
  end_1:
    return VALUES_1(temp);
}

/* SKIP-WHITESPACE-IN-STRING */
Object skip_whitespace_in_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object char_1;

    x_note_fn_call(32,130);
    char_1 = Nil;
  next_loop:
    if ( !FIXNUM_LT(start_index,end_index))
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(start_index)));
    if (blank_p(char_1))
	start_index = FIXNUM_ADD1(start_index);
    else
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(start_index);
    return VALUES_1(Qnil);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* READ-TRUTH-VALUE-FROM-STRING */
Object read_truth_value_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object length_of_rest_of_string, certainty, error_message;
    Object managed_certainty, certainty_qm, current_index, temp;
    Object store_managed_number_or_value_arg;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(32,131);
    length_of_rest_of_string = FIXNUM_MINUS(end_index,start_index);
    certainty = Nil;
    error_message = Nil;
    managed_certainty = Nil;
    if (IFIX(length_of_rest_of_string) < (SI_Long)4L)
	return VALUES_3(Nil,start_index,Nil);
    else if (substring_equal(string_1,start_index,FIX(IFIX(start_index) + 
	    (SI_Long)4L),array_constant,FIX((SI_Long)0L),FIX((SI_Long)4L))) {
	managed_certainty = 
		store_managed_number_or_value_function(managed_certainty,
		Truth);
	return VALUES_3(managed_certainty,FIX(IFIX(start_index) + 
		(SI_Long)4L),Nil);
    }
    else if (substring_equal(string_1,start_index,FIX(IFIX(start_index) + 
	    (SI_Long)5L),array_constant_1,FIX((SI_Long)0L),FIX((SI_Long)5L))) {
	managed_certainty = 
		store_managed_number_or_value_function(managed_certainty,
		Falsity);
	return VALUES_3(managed_certainty,FIX(IFIX(start_index) + 
		(SI_Long)5L),Nil);
    }
    else {
	result = read_number_from_string(string_1,start_index,end_index);
	MVS_2(result,certainty_qm,current_index);
	PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
	  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	      if (! !TRUEP(certainty_qm)) {
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(certainty_qm) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(certainty_qm)) == 
			  (SI_Long)1L)
		      temp = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(certainty_qm,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(certainty_qm) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(certainty_qm)) == 
			  (SI_Long)1L)
		      temp = aref1(certainty_qm,FIX((SI_Long)0L));
		  else if (text_string_p(certainty_qm))
		      temp = copy_text_string(certainty_qm);
		  else
		      temp = certainty_qm;
		  certainty = l_round(ltimes(FIX((SI_Long)1000L),temp),_);
		  certainty_qm = 
			  reclaim_managed_number_or_value_function(certainty_qm);
		  Current_index = skip_spaces_in_string(string_1,
			  Current_index,end_index);
		  if (IFIX(FIXNUM_MINUS(end_index,Current_index)) < 
			  (SI_Long)4L)
		      Current_index = start_index;
		  else if ( !TRUEP(substring_equal(string_1,Current_index,
			  FIX(IFIX(Current_index) + (SI_Long)4L),
			  array_constant,FIX((SI_Long)0L),FIX((SI_Long)4L))))
		      Current_index = start_index;
		  else if (NUM_GT(certainty,Truth))
		      error_message = array_constant_2;
		  else if (NUM_LT(certainty,Falsity))
		      error_message = array_constant_3;
		  else {
		      store_managed_number_or_value_arg = certainty;
		      managed_certainty = 
			      store_managed_number_or_value_function(managed_certainty,
			      store_managed_number_or_value_arg);
		      Current_index = FIX(IFIX(Current_index) + (SI_Long)4L);
		  }
	      }
	  }
	  POP_LOCAL_ALLOCATION(0,0);
	  result = VALUES_3(managed_certainty,Current_index,error_message);
	POP_SPECIAL();
	return result;
    }
}

/* READ-TEXT-STRING-ENDING-IN-A-DELIMITTER-FROM-STRING */
Object read_text_string_ending_in_a_delimitter_from_string(string_1,
	    start_index,end_index,delimitter)
    Object string_1, start_index, end_index, delimitter;
{
    Object current_index, string_ends_in_delimitter_p;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object character_1, temp, thing, schar_arg_2, schar_new_value, text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(32,132);
    current_index = start_index;
    PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,5);
      string_ends_in_delimitter_p = Nil;
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
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		    (SI_Long)16L));
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		    1);
	      current_twriting_output_type = Qwide_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		character_1 = Nil;
	      next_loop:
		if ( !FIXNUM_LT(Current_index,end_index))
		    goto end_loop;
		character_1 = FIX(UBYTE_16_ISAREF_1(string_1,
			IFIX(Current_index)));
		if (FIXNUM_EQ(character_1,delimitter)) {
		    string_ends_in_delimitter_p = T;
		    goto end_1;
		}
		temp = FIXNUM_ADD1(Current_index);
		Current_index = temp;
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing = character_1;
		    twrite_wide_character(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing = character_1;
		    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		    SET_SCHAR(temp,schar_arg_2,schar_new_value);
		    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp;
		}
		goto next_loop;
	      end_loop:
		string_ends_in_delimitter_p = Nil;
		goto end_1;
		string_ends_in_delimitter_p = Qnil;
	      end_1:;
		text_string = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      result = VALUES_3(text_string,Current_index,string_ends_in_delimitter_p);
    POP_SPECIAL();
    return result;
}

/* READ-TEXT-STRING-FROM-STRING */
Object read_text_string_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object current_index, string_in_string, string_is_ok_p, managed_string;
    Object store_managed_number_or_value_arg;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,133);
    if (UBYTE_16_ISAREF_1(string_1,IFIX(start_index)) == (SI_Long)34L) {
	current_index = FIXNUM_ADD1(start_index);
	string_in_string = Nil;
	string_is_ok_p = Nil;
	managed_string = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
	  result = read_text_string_ending_in_a_delimitter_from_string(string_1,
		  Current_index,end_index,FIX((SI_Long)34L));
	  MVS_3(result,string_in_string,Current_index,string_is_ok_p);
	  if (string_is_ok_p) {
	      store_managed_number_or_value_arg = string_in_string;
	      managed_string = 
		      store_managed_number_or_value_function(managed_string,
		      store_managed_number_or_value_arg);
	      reclaim_text_string(string_in_string);
	      result = VALUES_3(managed_string,Current_index,Nil);
	  }
	  else {
	      reclaim_text_string(string_in_string);
	      result = VALUES_3(Nil,start_index,Nil);
	  }
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_3(Nil,start_index,Nil);
}

static Object list_constant_2;     /* # */

/* READ-THREE-LETTER-MONTH-FROM-STRING */
Object read_three_letter_month_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object month, ab_loop_list_, ab_loop_iter_flag_;
    SI_Long limit, i;

    x_note_fn_call(32,134);
    limit = IFIX(start_index) + (SI_Long)3L;
    if (limit > IFIX(end_index))
	return VALUES_1(Nil);
    else {
	month = Nil;
	ab_loop_list_ = list_constant_2;
	i = (SI_Long)1L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	month = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    i = i + (SI_Long)1L;
	if (substring_equal(string_1,start_index,FIX(limit),month,
		FIX((SI_Long)0L),FIX((SI_Long)3L)))
	    return VALUES_1(FIX(i));
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* READ-DATE-FROM-STRING */
Object read_date_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object month, current_index, day, end_index_of_day, year;
    Object end_index_of_year;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,135);
    month = Nil;
    current_index = start_index;
    PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
    next_loop:
      if (IFIX(FIXNUM_MINUS(end_index,start_index)) >= (SI_Long)10L) {
	  result = read_positive_fixnum_from_string(string_1,Current_index,
		  FIX(IFIX(Current_index) + (SI_Long)2L));
	  MVS_2(result,day,end_index_of_day);
	  if (day) {
	      Current_index = skip_spaces_in_string(string_1,
		      end_index_of_day,end_index);
	      month = read_three_letter_month_from_string(string_1,
		      Current_index,end_index);
	      if (month) {
		  Current_index = skip_spaces_in_string(string_1,
			  FIX(IFIX(Current_index) + (SI_Long)3L),end_index);
		  result = read_positive_fixnum_from_string(string_1,
			  Current_index,FIX(IFIX(Current_index) + 
			  (SI_Long)4L));
		  MVS_2(result,year,end_index_of_year);
		  if (year && IFIX(end_index_of_year) == 
			  IFIX(Current_index) + (SI_Long)4L) {
		      result = VALUES_5(day,month,year,end_index_of_year,Nil);
		      goto end_1;
		  }
	      }
	  }
      }
      result = VALUES_5(Nil,Nil,Nil,start_index,Nil);
      goto end_1;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

/* READ-TIME-FROM-STRING */
Object read_time_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object current_index, hours, end_index_of_hours, minutes;
    Object end_index_of_minutes, seconds, end_index_of_seconds;
    Object valid_seconds_qm;
    double arg, arg_1;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(32,136);
    current_index = start_index;
    PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
    next_loop:
      if (IFIX(FIXNUM_MINUS(end_index,start_index)) >= (SI_Long)7L) {
	  result = read_positive_fixnum_from_string(string_1,Current_index,
		  FIX(IFIX(Current_index) + (SI_Long)2L));
	  MVS_2(result,hours,end_index_of_hours);
	  if (hours && IFIX(hours) <= (SI_Long)24L && 
		  UBYTE_16_ISAREF_1(string_1,IFIX(end_index_of_hours)) == 
		  (SI_Long)58L) {
	      Current_index = FIXNUM_ADD1(end_index_of_hours);
	      result = read_positive_fixnum_from_string(string_1,
		      Current_index,FIX(IFIX(Current_index) + (SI_Long)2L));
	      MVS_2(result,minutes,end_index_of_minutes);
	      if (minutes && IFIX(minutes) <= (SI_Long)59L && 
		      IFIX(FIXNUM_MINUS(end_index_of_minutes,
		      Current_index)) == (SI_Long)2L && 
		      UBYTE_16_ISAREF_1(string_1,
		      IFIX(end_index_of_minutes)) == (SI_Long)58L) {
		  Current_index = FIXNUM_ADD1(end_index_of_minutes);
		  result = read_number_from_string(string_1,Current_index,
			  end_index);
		  MVS_2(result,seconds,end_index_of_seconds);
		  if (seconds) {
		      if (FIXNUMP(seconds))
			  valid_seconds_qm = IFIX(seconds) <= (SI_Long)59L 
				  ? 
				  (IFIX(FIXNUM_MINUS(end_index_of_seconds,
				  Current_index)) == (SI_Long)2L ? T : 
				  Nil) : Qnil;
		      else if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds) != 
			      (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds)) == 
			      (SI_Long)1L) {
			  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			      arg = DFLOAT_ISAREF_1(seconds,(SI_Long)0L);
			      arg_1 = 60.0;
			      valid_seconds_qm = arg < arg_1 &&  
				      !inline_nanp_for_comparison(arg) &&  
				      !inline_nanp_for_comparison(arg_1) ? 
				      (IFIX(FIXNUM_MINUS(end_index_of_seconds,
				      Current_index)) >= (SI_Long)4L ? T : 
				      Nil) : Nil;
			  }
			  POP_LOCAL_ALLOCATION(0,0);
		      }
		      else
			  valid_seconds_qm = Nil;
		  }
		  else
		      valid_seconds_qm = Nil;
		  if (valid_seconds_qm) {
		      Current_index = skip_spaces_in_string(string_1,
			      end_index_of_seconds,end_index);
		      if (IFIX(hours) == (SI_Long)24L)
			  hours = FIX((SI_Long)0L);
		      if (IFIX(FIXNUM_MINUS(end_index,Current_index)) < 
			      (SI_Long)4L) {
			  result = VALUES_5(hours,minutes,seconds,
				  end_index_of_seconds,Nil);
			  goto end_1;
		      }
		      else if (substring_equal(string_1,Current_index,
			      FIX(IFIX(Current_index) + (SI_Long)4L),
			      array_constant_4,FIX((SI_Long)0L),
			      FIX((SI_Long)4L))) {
			  if (IFIX(hours) > (SI_Long)0L && IFIX(hours) <= 
				  (SI_Long)12L) {
			      if (IFIX(hours) == (SI_Long)12L)
				  hours = FIX((SI_Long)0L);
			      result = VALUES_5(hours,minutes,seconds,
				      FIX(IFIX(Current_index) + 
				      (SI_Long)4L),Nil);
			      goto end_1;
			  }
		      }
		      else if (substring_equal(string_1,Current_index,
			      FIX(IFIX(Current_index) + (SI_Long)4L),
			      array_constant_5,FIX((SI_Long)0L),
			      FIX((SI_Long)4L))) {
			  if (IFIX(hours) > (SI_Long)0L && IFIX(hours) <= 
				  (SI_Long)12L) {
			      if (IFIX(hours) != (SI_Long)12L)
				  hours = FIX(IFIX(hours) + (SI_Long)12L);
			      result = VALUES_5(hours,minutes,seconds,
				      FIX(IFIX(Current_index) + 
				      (SI_Long)4L),Nil);
			      goto end_1;
			  }
		      }
		      else {
			  result = VALUES_5(hours,minutes,seconds,
				  end_index_of_seconds,Nil);
			  goto end_1;
		      }
		  }
	      }
	  }
      }
      result = VALUES_5(Nil,Nil,Nil,start_index,Nil);
      goto end_1;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* READ-TIME-STAMP-FROM-STRING */
Object read_time_stamp_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object day, month, year, end_index_of_date, hours, minutes, seconds;
    Object end_index_of_time;
    Object result;

    x_note_fn_call(32,137);
    if (IFIX(FIXNUM_MINUS(end_index,start_index)) >= (SI_Long)18L) {
	result = read_date_from_string(string_1,start_index,end_index);
	MVS_4(result,day,month,year,end_index_of_date);
	if (day) {
	    end_index_of_date = skip_spaces_in_string(string_1,
		    end_index_of_date,end_index);
	    result = read_time_from_string(string_1,end_index_of_date,
		    end_index);
	    MVS_4(result,hours,minutes,seconds,end_index_of_time);
	    if (hours)
		return VALUES_8(seconds,minutes,hours,day,month,year,
			end_index_of_time,Nil);
	}
    }
    return VALUES_8(Nil,Nil,Nil,Nil,Nil,Nil,start_index,Nil);
}

Object Large_mask = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Random_state_array, Qrandom_state_array);

DEFINE_VARIABLE_WITH_SYMBOL(Random_state_array_current_pointer, Qrandom_state_array_current_pointer);

DEFINE_VARIABLE_WITH_SYMBOL(Random_state_array_24_pointer, Qrandom_state_array_24_pointer);

DEFINE_VARIABLE_WITH_SYMBOL(Random_variation, Qrandom_variation);

DEFINE_VARIABLE_WITH_SYMBOL(Random_variation_2, Qrandom_variation_2);

DEFINE_VARIABLE_WITH_SYMBOL(User_random_seed_qm, Quser_random_seed_qm);

/* RESET-G2-RANDOM-STATE */
Object reset_g2_random_state(non_deterministic_qm)
    Object non_deterministic_qm;
{
    Object aref_arg_1, temp, aref_new_value_1;
    SI_Long i, aref_new_value;
    XDeclare_area(1);

    x_note_fn_call(32,138);
    if ( !TRUEP(Random_state_array)) {
	if (PUSH_AREA(Dynamic_area,0))
	    Random_state_array = make_array(3,FIX((SI_Long)55L),
		    Kelement_type,Qfixnum);
	POP_AREA(0);
    }
    aref_arg_1 = Random_state_array;
    set_aref1(aref_arg_1,FIX((SI_Long)0L),Random_seed_0);
    aref_arg_1 = Random_state_array;
    set_aref1(aref_arg_1,FIX((SI_Long)1L),Random_seed_1);
    aref_arg_1 = Random_state_array;
    set_aref1(aref_arg_1,FIX((SI_Long)2L),Random_seed_2);
    aref_arg_1 = Random_state_array;
    set_aref1(aref_arg_1,FIX((SI_Long)3L),Random_seed_3);
    i = (SI_Long)4L;
  next_loop:
    if (i > (SI_Long)54L)
	goto end_loop;
    aref_arg_1 = Random_state_array;
    aref_new_value = i * (SI_Long)103L;
    set_aref1(aref_arg_1,FIX(i),FIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    Random_state_array_current_pointer = FIX((SI_Long)54L);
    Random_state_array_24_pointer = FIX((SI_Long)30L);
    if (non_deterministic_qm) {
	temp = User_random_seed_qm;
	if (temp);
	else
	    temp = c_native_clock_ticks_or_cache(Nil,Nil);
	Random_variation = temp;
	Random_variation_2 = FIXNUM_SUB1(Random_variation);
    }
    aref_arg_1 = Random_state_array;
    aref_new_value_1 = Random_variation;
    set_aref1(aref_arg_1,FIX((SI_Long)4L),aref_new_value_1);
    aref_arg_1 = Random_state_array;
    aref_new_value_1 = Random_variation_2;
    set_aref1(aref_arg_1,FIX((SI_Long)5L),aref_new_value_1);
    i = (SI_Long)0L;
  next_loop_1:
    if (i > (SI_Long)1000L)
	goto end_loop_1;
    generate_large_random();
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* GENERATE-LARGE-RANDOM */
Object generate_large_random()
{
    Object current_pointer, n_24_pointer, aref_arg_1, aref_new_value;

    x_note_fn_call(32,139);
    current_pointer = Random_state_array_current_pointer;
    n_24_pointer = Random_state_array_24_pointer;
    current_pointer = FIXNUM_ADD1(current_pointer);
    if (IFIX(current_pointer) == (SI_Long)55L)
	current_pointer = FIX((SI_Long)0L);
    Random_state_array_current_pointer = current_pointer;
    n_24_pointer = FIXNUM_ADD1(n_24_pointer);
    if (IFIX(n_24_pointer) == (SI_Long)55L)
	n_24_pointer = FIX((SI_Long)0L);
    Random_state_array_24_pointer = n_24_pointer;
    aref_arg_1 = Random_state_array;
    aref_new_value = FIXNUM_LOGAND(Large_mask,
	    FIXNUM_ADD(aref1(Random_state_array,current_pointer),
	    aref1(Random_state_array,n_24_pointer)));
    return set_aref1(aref_arg_1,current_pointer,aref_new_value);
}

/* G2-RANDOM */
Object g2_random(n_1)
    Object n_1;
{
    Object lim, rand_1, shift, new_mask, mask, temp, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long i, j;

    x_note_fn_call(32,140);
    if (FIXNUM_LE(n_1,Large_mask)) {
	lim = FIXNUM_TIMES(n_1,chestnut_floorf_function(Large_mask,n_1));
	i = (SI_Long)1L;
	rand_1 = Nil;
      next_loop:
	if (i > (SI_Long)30L)
	    goto end_loop;
	rand_1 = generate_large_random();
	if (FIXNUM_LE(rand_1,lim))
	    return chestnut_modf_function(rand_1,n_1);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return chestnut_modf_function(rand_1,n_1);
	return VALUES_1(Qnil);
    }
    else {
	shift = Nil;
	new_mask = Nil;
	lim = Nil;
	i = (SI_Long)1L;
	rand_1 = Nil;
	j = (SI_Long)0L;
	mask = Large_mask;
      next_loop_1:
	if (FIXNUM_GE(mask,n_1))
	    goto end_loop_1;
	j = j + (SI_Long)1L;
	mask = FIX((IFIX(mask) << (SI_Long)1L) + (SI_Long)1L);
	goto next_loop_1;
      end_loop_1:
	shift = FIX(j);
	new_mask = mask;
	lim = FIXNUM_TIMES(n_1,chestnut_floorf_function(new_mask,n_1));
      next_loop_2:
	if (i > (SI_Long)30L)
	    goto end_loop_2;
	temp = generate_large_random();
	gensymed_symbol = generate_large_random();
	gensymed_symbol_1 = shift;
	rand_1 = logxor(temp,ash(gensymed_symbol,gensymed_symbol_1));
	if (FIXNUM_LE(rand_1,lim))
	    return chestnut_modf_function(rand_1,n_1);
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	return chestnut_modf_function(rand_1,n_1);
	return VALUES_1(Qnil);
    }
}

/* GENSYM-SEARCH-SIMPLE */
Object gensym_search_simple(sequence1,sequence2)
    Object sequence1, sequence2;
{
    Object sequence1_length, sequence2_length, ab_loop_it_, temp, temp_1;
    SI_Long sequence2_index, ab_loop_bind_, sequence1_index, ab_loop_bind__1;
    char temp_2;

    x_note_fn_call(32,141);
    sequence1_length = lengthw(sequence1);
    sequence2_length = lengthw(sequence2);
    if (NUM_GT(sequence1_length,sequence2_length))
	return VALUES_1(Nil);
    else {
	sequence2_index = (SI_Long)0L;
	ab_loop_bind_ = IFIX(minus(sequence2_length,sequence1_length));
	ab_loop_it_ = Nil;
      next_loop:
	if (sequence2_index > ab_loop_bind_)
	    goto end_loop;
	sequence1_index = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(sequence1_length);
      next_loop_1:
	if (sequence1_index >= ab_loop_bind__1)
	    goto end_loop_1;
	temp = eltw(sequence1,FIX(sequence1_index));
	temp_1 = eltw(sequence2,add(FIX(sequence1_index),
		FIX(sequence2_index)));
	if ( !EQL(temp,temp_1)) {
	    temp_2 = TRUEP(Nil);
	    goto end_1;
	}
	sequence1_index = sequence1_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp_2 = TRUEP(T);
	goto end_1;
	temp_2 = TRUEP(Qnil);
      end_1:;
	ab_loop_it_ = temp_2 ? FIX(sequence2_index) : Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	sequence2_index = sequence2_index + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* GENSYM-SEARCH-COMPLEX */
Object gensym_search_complex(sequence1,sequence2,from_end,test,test_not,
	    key,start1,start2,end1,end2)
    Object sequence1, sequence2, from_end, test, test_not, key, start1, start2;
    Object end1, end2;
{
    Object span1, temp, ab_loop_it_, raw_element1, raw_element2, element1;
    Object element2;
    SI_Long sequence2_index, ab_loop_bind_, sequence1_index, ab_loop_bind__1;
    char temp_1;

    x_note_fn_call(32,142);
    if ( !TRUEP(end1))
	end1 = lengthw(sequence1);
    if ( !TRUEP(end2))
	end2 = lengthw(sequence2);
    span1 = minus(end1,start1);
    temp = minus(end2,start2);
    if (NUM_GT(span1,temp))
	return VALUES_1(Nil);
    else if (from_end) {
	sequence2_index = IFIX(minus(end2,span1));
	ab_loop_bind_ = IFIX(start2);
	ab_loop_it_ = Nil;
      next_loop:
	if (sequence2_index < ab_loop_bind_)
	    goto end_loop;
	sequence1_index = IFIX(start1);
	ab_loop_bind__1 = IFIX(end1);
	raw_element1 = Nil;
	raw_element2 = Nil;
	element1 = Nil;
	element2 = Nil;
      next_loop_1:
	if (sequence1_index >= ab_loop_bind__1)
	    goto end_loop_1;
	raw_element1 = eltw(sequence1,FIX(sequence1_index));
	raw_element2 = eltw(sequence2,add(FIX(sequence1_index),
		FIX(sequence2_index)));
	element1 = key ? FUNCALL_1(key,raw_element1) : raw_element1;
	element2 = key ? FUNCALL_1(key,raw_element2) : raw_element2;
	if ( !(test ? TRUEP(FUNCALL_2(test,element1,element2)) : TRUEP(T))) {
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	}
	if (test_not && FUNCALL_2(test_not,element1,element2)) {
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	}
	sequence1_index = sequence1_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp_1 = TRUEP(T);
	goto end_1;
	temp_1 = TRUEP(T);
	goto end_1;
	temp_1 = TRUEP(Qnil);
      end_1:;
	ab_loop_it_ = temp_1 ? FIX(sequence2_index) : Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	sequence2_index = sequence2_index - (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	sequence2_index = IFIX(start2);
	ab_loop_bind_ = IFIX(minus(end2,span1));
	ab_loop_it_ = Nil;
      next_loop_2:
	if (sequence2_index > ab_loop_bind_)
	    goto end_loop_2;
	sequence1_index = IFIX(start1);
	ab_loop_bind__1 = IFIX(end1);
	raw_element1 = Nil;
	raw_element2 = Nil;
	element1 = Nil;
	element2 = Nil;
      next_loop_3:
	if (sequence1_index >= ab_loop_bind__1)
	    goto end_loop_3;
	raw_element1 = eltw(sequence1,FIX(sequence1_index));
	raw_element2 = eltw(sequence2,add(FIX(sequence1_index),
		FIX(sequence2_index)));
	element1 = key ? FUNCALL_1(key,raw_element1) : raw_element1;
	element2 = key ? FUNCALL_1(key,raw_element2) : raw_element2;
	if ( !(test ? TRUEP(FUNCALL_2(test,element1,element2)) : TRUEP(T))) {
	    temp_1 = TRUEP(Nil);
	    goto end_2;
	}
	if (test_not && FUNCALL_2(test_not,element1,element2)) {
	    temp_1 = TRUEP(Nil);
	    goto end_2;
	}
	sequence1_index = sequence1_index + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:
	temp_1 = TRUEP(T);
	goto end_2;
	temp_1 = TRUEP(T);
	goto end_2;
	temp_1 = TRUEP(Qnil);
      end_2:;
	ab_loop_it_ = temp_1 ? FIX(sequence2_index) : Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	sequence2_index = sequence2_index + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
}

/* SIMPLE-EVAL */
Object simple_eval(form)
    Object form;
{
    Object head, result_1, statement, ab_loop_list_, temp, temp_1, temp_2;
    Object temp_3;

    x_note_fn_call(32,143);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(form) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(form)) == (SI_Long)1L)
	return copy_managed_float(form);
    else if (SYMBOLP(form))
	return VALUES_1(SYMBOL_VALUE(form));
    else if (ATOM(form))
	return VALUES_1(form);
    else if (LISTP(form)) {
	head = FIRST(form);
	if (EQ(head,Qprogn)) {
	    result_1 = Nil;
	    statement = Nil;
	    ab_loop_list_ = REST(form);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    statement = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    result_1 = simple_eval(statement);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(result_1);
	    return VALUES_1(Qnil);
	}
	else if (EQ(head,Qquote))
	    return VALUES_1(SECOND(form));
	else {
	    temp = length(form);
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		return error((SI_Long)1L,
			"simple eval suports only 5 argument calls or less.");
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    return FUNCALL_0(head);
		  case 2:
		    return FUNCALL_1(head,simple_eval(SECOND(form)));
		  case 3:
		    temp = simple_eval(SECOND(form));
		    return FUNCALL_2(head,temp,simple_eval(THIRD(form)));
		  case 4:
		    temp_1 = simple_eval(SECOND(form));
		    temp = simple_eval(THIRD(form));
		    return FUNCALL_3(head,temp_1,temp,
			    simple_eval(FOURTH(form)));
		  case 5:
		    temp_2 = simple_eval(SECOND(form));
		    temp_1 = simple_eval(THIRD(form));
		    temp = simple_eval(FOURTH(form));
		    return FUNCALL_4(head,temp_2,temp_1,temp,
			    simple_eval(FIFTH(form)));
		  case 6:
		    temp_3 = simple_eval(SECOND(form));
		    temp_2 = simple_eval(THIRD(form));
		    temp_1 = simple_eval(FOURTH(form));
		    temp = simple_eval(FIFTH(form));
		    return FUNCALL_5(head,temp_3,temp_2,temp_1,temp,
			    simple_eval(SIXTH(form)));
		  default:
		    return error((SI_Long)1L,
			    "simple eval suports only 5 argument calls or less.");
		}
	}
    }
    else
	return VALUES_1(Qnil);
}

Object Simple_type_specification_prop = UNBOUND;

static Object Qboolean;            /* boolean */

static Object Qmanaged_number;     /* managed-number */

static Object Qtemporary_constant;  /* temporary-constant */

static Object Qsimple_type_specification;  /* simple-type-specification */

static Object Qab_or;              /* or */

/* SIMPLE-TYPEP */
Object simple_typep(instance,type_spec)
    Object instance, type_spec;
{
    Object temp, simple_type_specification, spec, ab_loop_list_;

    x_note_fn_call(32,144);
    if (SYMBOLP(type_spec)) {
	if (EQ(type_spec,Qt))
	    return VALUES_1(T);
	else if (EQ(type_spec,Qnull))
	    return VALUES_1(Nil);
	else if (EQ(type_spec,Qfixnum))
	    return VALUES_1(FIXNUMP(instance) ? T : Nil);
	else if (EQ(type_spec,Qboolean)) {
	    temp =  !TRUEP(instance) ? T : Nil;
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1(EQ(instance,T) ? T : Nil);
	}
	else if (EQ(type_spec,Qgensym_float))
	    return VALUES_1(FLOATP(instance) ? T : Nil);
	else if (EQ(type_spec,Qmanaged_number)) {
	    temp = FIXNUMP(instance) ? T : Nil;
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(instance) != 
			(SI_Long)0L ? 
			(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(instance)) == 
			(SI_Long)1L ? T : Nil) : Qnil;
	    if (temp)
		return VALUES_1(temp);
	    else if (INLINE_LONG_VECTOR_P(instance) != (SI_Long)0L)
		return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(instance)) 
			== (SI_Long)1L ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(type_spec,Qtemporary_constant)) {
	    if (SIMPLE_VECTOR_P(instance))
		return VALUES_1(EQ(ISVREF(instance,(SI_Long)0L),
			Qg2_defstruct_structure_name_temporary_constant_g2_struct) 
			? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else {
	    simple_type_specification = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(type_spec),
		    Qsimple_type_specification);
	    if (simple_type_specification)
		return simple_typep(instance,simple_type_specification);
	    else
		return VALUES_1(Nil);
	}
    }
    else if (CONSP(type_spec)) {
	temp = FIRST(type_spec);
	if (EQ(temp,Qsatisfies)) {
	    temp = SECOND(type_spec);
	    return FUNCALL_1(temp,instance);
	}
	else if (EQ(temp,Qmember))
	    return memq_function(instance,REST(type_spec));
	else if (EQ(temp,Qab_or)) {
	    spec = Nil;
	    ab_loop_list_ = REST(type_spec);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    spec = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (simple_typep(instance,spec))
		return VALUES_1(T);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Nil);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

Object Type_error_printer_prop = UNBOUND;

static Object string_constant_4;   /* "~(~A is ~)" */

static Object Qmanaged_float;      /* managed-float */

static Object Qslot_value_float;   /* slot-value-float */

static Object string_constant_5;   /* " not a number." */

static Object Qtype_error_printer;  /* type-error-printer */

static Object string_constant_6;   /* "~A." */

static Object string_constant_7;   /* "~( not ~A~A~)." */

static Object string_constant_8;   /* "." */

static Object string_constant_9;   /* "~(not ~A~)." */

static Object string_constant_10;  /* "~( neither ~A nor ~A~)." */

static Object string_constant_11;  /* "not one of " */

static Object string_constant_12;  /* "~(~A~)" */

static Object string_constant_13;  /* ", or " */

static Object string_constant_14;  /* ", " */

static Object string_constant_15;  /* "~(not an appropriate value (e.g., ~A, ~A, etc.)~)" */

/* TFORMAT-TYPE-ERROR */
Object tformat_type_error(value,type_spec)
    Object value, type_spec;
{
    Object type_error_printer, temp, length_1, l, ab_loop_list_;

    x_note_fn_call(32,145);
    tformat(2,string_constant_4,value);
    if (SYMBOLP(type_spec)) {
	if (EQ(type_spec,Qgensym_float) || EQ(type_spec,Qmanaged_float) || 
		EQ(type_spec,Qslot_value_float))
	    return tformat(1,string_constant_5);
	else {
	    type_error_printer = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(type_spec),
		    Qtype_error_printer);
	    if (STRINGP(type_error_printer))
		return tformat(2,string_constant_6,type_error_printer);
	    else if ( !TRUEP(type_error_printer))
		return tformat(3,string_constant_7,
			supply_a_or_an(type_spec),type_spec);
	    else if (SYMBOLP(type_error_printer)) {
		FUNCALL_1(type_error_printer,value);
		return tformat(1,string_constant_8);
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
    else if (CONSP(type_spec)) {
	temp = FIRST(type_spec);
	if (EQ(temp,Qmember)) {
	    length_1 = length(type_spec);
	    if (IFIX(length_1) == (SI_Long)1L)
		return tformat(2,string_constant_9,SECOND(type_spec));
	    else if (IFIX(length_1) == (SI_Long)2L)
		return tformat(3,string_constant_10,SECOND(type_spec),
			THIRD(type_spec));
	    else if (IFIX(length_1) < (SI_Long)10L) {
		tformat(1,string_constant_11);
		l = Nil;
		ab_loop_list_ = CDR(type_spec);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		l = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		tformat(2,string_constant_12,CAR(l));
		tformat(1, !TRUEP(CDR(l)) ? string_constant_13 : 
			string_constant_14);
		goto next_loop;
	      end_loop:;
		return tformat(1,string_constant_8);
	    }
	    else
		return tformat(3,string_constant_15,SECOND(type_spec),
			THIRD(type_spec));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

Object Simple_type_writer_prop = UNBOUND;

static Object Qsimple_type_writer;  /* simple-type-writer */

static Object string_constant_16;  /* "~(~S~)" */

/* WRITE-INSTANCE-OF-SIMPLE-TYPE-1 */
Object write_instance_of_simple_type_1(simple_type_name,instance)
    Object simple_type_name, instance;
{
    Object type_writer, temp;

    x_note_fn_call(32,146);
    type_writer = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(simple_type_name),
	    Qsimple_type_writer);
    if (type_writer) {
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(simple_type_name),
		Qsimple_type_writer);
	return FUNCALL_1(temp,instance);
    }
    else
	return tformat(2,string_constant_16,instance);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_region_conses, Qavailable_region_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_region_conses_tail, Qavailable_region_conses_tail);

Object Available_region_conses_vector = UNBOUND;

Object Available_region_conses_tail_vector = UNBOUND;

Object Region_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Region_cons_counter, Qregion_cons_counter);

/* OUTSTANDING-REGION-CONSES */
Object outstanding_region_conses()
{
    Object temp;

    x_note_fn_call(32,147);
    temp = FIXNUM_MINUS(Region_cons_counter,length(Available_region_conses));
    return VALUES_1(temp);
}

/* REGION-CONS-MEMORY-USAGE */
Object region_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(32,148);
    temp = FIXNUM_TIMES(Region_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-REGION-CONS-POOL */
Object replenish_region_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(32,149);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qregion_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_region_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_region_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Region_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qregion;             /* region */

/* REGION-CONS-1 */
Object region_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(32,150);
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-REGION-LIST-POOL */
Object replenish_region_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(32,151);
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
    if (ISVREF(Available_region_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_region_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qregion_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-REGION-LIST-1 */
Object make_region_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(32,152);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_region_conses_vector,
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
	replenish_region_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
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

/* REGION-LIST-2 */
Object region_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,153);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_region_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_region_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qregion);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_region_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_region_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_region_conses_tail_vector;
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

/* REGION-LIST-3 */
Object region_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,154);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_region_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_region_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qregion);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_region_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_region_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_region_conses_tail_vector;
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

/* REGION-LIST-4 */
Object region_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,155);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_region_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_region_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qregion);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_region_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_region_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_region_conses_tail_vector;
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

/* REGION-LIST-TRACE-HOOK */
Object region_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(32,156);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-REGION-CONSES-1 */
Object copy_tree_using_region_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(32,157);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	temp_1 = copy_tree_using_region_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	temp_1 = copy_tree_using_region_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
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

/* COPY-LIST-USING-REGION-CONSES-1 */
Object copy_list_using_region_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(32,158);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
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

/* RECLAIM-REGION-CONS-1 */
Object reclaim_region_cons_1(region_cons)
    Object region_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(32,159);
    inline_note_reclaim_cons(region_cons,Qregion);
    if (ISVREF(Available_region_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_region_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = region_cons;
	temp = Available_region_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = region_cons;
    }
    else {
	temp = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = region_cons;
	temp = Available_region_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = region_cons;
    }
    M_CDR(region_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-REGION-LIST-1 */
Object reclaim_region_list_1(region_list)
    Object region_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(32,160);
    if (region_list) {
	last_1 = region_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qregion);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qregion);
	if (ISVREF(Available_region_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_region_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = region_list;
	    temp = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = region_list;
	    temp = Available_region_conses_tail_vector;
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

/* RECLAIM-REGION-LIST*-1 */
Object reclaim_region_list_star_1(region_list)
    Object region_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(32,161);
    if (CONSP(region_list)) {
	temp = last(region_list,_);
	M_CDR(temp) = Nil;
	if (region_list) {
	    last_1 = region_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qregion);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qregion);
	    if (ISVREF(Available_region_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_region_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = region_list;
		temp = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = region_list;
		temp = Available_region_conses_tail_vector;
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

/* RECLAIM-REGION-TREE-1 */
Object reclaim_region_tree_1(tree)
    Object tree;
{
    Object e, e2, region_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(32,162);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_region_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		region_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(region_cons,Qregion);
		if (EQ(region_cons,e))
		    goto end_1;
		else if ( !TRUEP(region_cons))
		    goto end_1;
		else
		    region_cons = CDR(region_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_region_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_region_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_region_conses_tail_vector;
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

/* DELETE-REGION-ELEMENT-1 */
Object delete_region_element_1(element,region_list)
    Object element, region_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(32,163);
    if (region_list) {
	if (EQ(element,M_CAR(region_list))) {
	    temp = CDR(region_list);
	    inline_note_reclaim_cons(region_list,Qregion);
	    if (ISVREF(Available_region_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_region_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = region_list;
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = region_list;
	    }
	    else {
		temp_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = region_list;
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = region_list;
	    }
	    M_CDR(region_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = region_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qregion);
		if (ISVREF(Available_region_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_region_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_region_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_region_conses_tail_vector;
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
	    temp = region_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-REGION-CONS-1 */
Object delete_region_cons_1(region_cons,region_list)
    Object region_cons, region_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(32,164);
    if (EQ(region_cons,region_list))
	temp = CDR(region_list);
    else {
	l_trailer_qm = Nil;
	l = region_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,region_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = region_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_region_cons_1(region_cons);
    return VALUES_1(temp);
}

/* RIGHT-OPEN-INTERVALS-INTERSECT-P */
Object right_open_intervals_intersect_p(interval_1,interval_2)
    Object interval_1, interval_2;
{
    Object left_1, right_1, left_2, right_2;

    x_note_fn_call(32,165);
    left_1 = M_CAR(interval_1);
    right_1 = M_CDR(interval_1);
    left_2 = M_CAR(interval_2);
    right_2 = M_CDR(interval_2);
    if (FIXNUM_LT(left_1,right_2))
	return VALUES_1(FIXNUM_LT(left_2,right_1) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* INTERSECT-INTERVALS */
Object intersect_intervals(a_intervals,b_intervals)
    Object a_intervals, b_intervals;
{
    Object result_1, a0, a1, b0, b1, min_qm, a_intervals_old_value, temp;
    Object b_intervals_old_value, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, max_qm;

    x_note_fn_call(32,166);
    result_1 = Nil;
    a0 = Nil;
    a1 = Nil;
    b0 = Nil;
    b1 = Nil;
    min_qm = Nil;
    if ( !TRUEP(a_intervals))
	goto end_1;
    a0 = M_CAR(FIRST(a_intervals));
    a_intervals_old_value = a_intervals;
    temp = FIRST(a_intervals_old_value);
    a_intervals = REST(a_intervals_old_value);
    a1 = M_CDR(temp);
    if ( !TRUEP(b_intervals))
	goto end_1;
    b0 = M_CAR(FIRST(b_intervals));
    b_intervals_old_value = b_intervals;
    temp = FIRST(b_intervals_old_value);
    b_intervals = REST(b_intervals_old_value);
    b1 = M_CDR(temp);
  next_loop:
    if (FIXNUM_LT(a0,b0)) {
	if (FIXNUM_LT(a1,b0))
	    goto adv_a;
	else if (FIXNUM_LE(b1,a1)) {
	    if ( !FIXNUM_EQ(b0,b1)) {
		if ( !TRUEP(min_qm))
		    min_qm = b0;
		if (EQ(CDDR(result_1),b0))
		    M_CDDR(result_1) = b1;
		else {
		    new_cons = ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			svref_arg_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index)))) {
			    svref_arg_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(svref_arg_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_region_cons_pool();
		    M_CAR(gensymed_symbol) = b0;
		    M_CDR(gensymed_symbol) = b1;
		    inline_note_allocate_cons(gensymed_symbol,Qregion);
		    result_1 = region_cons_1(gensymed_symbol,result_1);
		}
	    }
	    goto adv_b;
	}
	else if (FIXNUM_LT(a1,b1)) {
	    if ( !FIXNUM_EQ(b0,a1)) {
		if ( !TRUEP(min_qm))
		    min_qm = b0;
		if (EQ(CDDR(result_1),b0))
		    M_CDDR(result_1) = a1;
		else {
		    new_cons = ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			svref_arg_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index)))) {
			    svref_arg_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(svref_arg_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_region_cons_pool();
		    M_CAR(gensymed_symbol) = b0;
		    M_CDR(gensymed_symbol) = a1;
		    inline_note_allocate_cons(gensymed_symbol,Qregion);
		    result_1 = region_cons_1(gensymed_symbol,result_1);
		}
	    }
	    goto adv_a;
	}
    }
    else if (FIXNUM_LT(b1,a0))
	goto adv_b;
    else if (FIXNUM_LE(a1,b1)) {
	if ( !FIXNUM_EQ(a0,a1)) {
	    if ( !TRUEP(min_qm))
		min_qm = a0;
	    if (EQ(CDDR(result_1),a0))
		M_CDDR(result_1) = a1;
	    else {
		new_cons = ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_region_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_region_cons_pool();
		M_CAR(gensymed_symbol) = a0;
		M_CDR(gensymed_symbol) = a1;
		inline_note_allocate_cons(gensymed_symbol,Qregion);
		result_1 = region_cons_1(gensymed_symbol,result_1);
	    }
	}
	goto adv_a;
    }
    else if (FIXNUM_LT(b1,a1)) {
	if ( !FIXNUM_EQ(a0,b1)) {
	    if ( !TRUEP(min_qm))
		min_qm = a0;
	    if (EQ(CDDR(result_1),a0))
		M_CDDR(result_1) = b1;
	    else {
		new_cons = ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_region_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_region_cons_pool();
		M_CAR(gensymed_symbol) = a0;
		M_CDR(gensymed_symbol) = b1;
		inline_note_allocate_cons(gensymed_symbol,Qregion);
		result_1 = region_cons_1(gensymed_symbol,result_1);
	    }
	}
	goto adv_b;
    }
  adv_a:
    if ( !TRUEP(a_intervals))
	goto end_1;
    a0 = M_CAR(FIRST(a_intervals));
    a_intervals_old_value = a_intervals;
    temp = FIRST(a_intervals_old_value);
    a_intervals = REST(a_intervals_old_value);
    a1 = M_CDR(temp);
    goto next;
  adv_b:
    if ( !TRUEP(b_intervals))
	goto end_1;
    b0 = M_CAR(FIRST(b_intervals));
    b_intervals_old_value = b_intervals;
    temp = FIRST(b_intervals_old_value);
    b_intervals = REST(b_intervals_old_value);
    b1 = M_CDR(temp);
  next:
    goto next_loop;
  end_loop:
  end_1:
    max_qm = result_1 ? M_CDR(FIRST(result_1)) : Nil;
    temp = nreverse(result_1);
    return VALUES_3(temp,min_qm,max_qm);
}

/* SUBTRACT-INTERVALS */
Object subtract_intervals(a_intervals,b_intervals)
    Object a_intervals, b_intervals;
{
    Object left, right, ab_loop_list_, left_max, ab_loop_maxmin_fl_, right_max;
    Object ab_loop_maxmin_fl__1, result_1, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_desetq_, a0, a1, b0, b1, min_qm, max_qm;
    Object a_intervals_old_value, temp, b_intervals_old_value, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol;
    Object left_min, tail, temp_1, temp_2;

    x_note_fn_call(32,167);
    if ( !TRUEP(b_intervals)) {
	if (a_intervals) {
	    left = Nil;
	    right = Nil;
	    ab_loop_list_ = a_intervals;
	    left_max = FIX((SI_Long)0L);
	    ab_loop_maxmin_fl_ = T;
	    right_max = FIX((SI_Long)0L);
	    ab_loop_maxmin_fl__1 = T;
	    result_1 = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    left = CAR(ab_loop_desetq_);
	    right = CDR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (ab_loop_maxmin_fl_) {
		ab_loop_maxmin_fl_ = Nil;
		left_max = left;
	    }
	    else
		left_max = FIXNUM_MIN(left_max,left);
	    if (ab_loop_maxmin_fl__1) {
		ab_loop_maxmin_fl__1 = Nil;
		right_max = right;
	    }
	    else
		right_max = FIXNUM_MAX(right_max,right);
	    ab_loopvar__1 = region_cons_1(region_cons_1(left,right),Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		result_1 = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop;
	  end_loop:
	    return VALUES_3(result_1,left_max,right_max);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    if ( !TRUEP(a_intervals))
	return VALUES_1(Nil);
    result_1 = Nil;
    a0 = Nil;
    a1 = Nil;
    b0 = Nil;
    b1 = Nil;
    min_qm = Nil;
    max_qm = Nil;
    if ( !TRUEP(a_intervals))
	goto finished_a;
    a0 = M_CAR(FIRST(a_intervals));
    a_intervals_old_value = a_intervals;
    temp = FIRST(a_intervals_old_value);
    a_intervals = REST(a_intervals_old_value);
    a1 = M_CDR(temp);
    if ( !TRUEP(b_intervals))
	goto finished_b;
    b0 = M_CAR(FIRST(b_intervals));
    b_intervals_old_value = b_intervals;
    temp = FIRST(b_intervals_old_value);
    b_intervals = REST(b_intervals_old_value);
    b1 = M_CDR(temp);
  loop_head:
    if (FIXNUM_LT(a0,b0)) {
	if (FIXNUM_LT(a1,b0)) {
	    if ( !FIXNUM_EQ(a0,a1)) {
		if (EQ(CDDR(result_1),a0)) {
		    max_qm = a1;
		    M_CDDR(result_1) = a1;
		}
		else {
		    if (max_qm) {
			min_qm = FIXNUM_MIN(min_qm,a0);
			max_qm = FIXNUM_MAX(max_qm,a1);
		    }
		    else {
			min_qm = a0;
			max_qm = a1;
		    }
		    new_cons = ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			svref_arg_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index)))) {
			    svref_arg_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(svref_arg_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_region_cons_pool();
		    M_CAR(gensymed_symbol) = a0;
		    M_CDR(gensymed_symbol) = a1;
		    inline_note_allocate_cons(gensymed_symbol,Qregion);
		    result_1 = region_cons_1(gensymed_symbol,result_1);
		}
	    }
	    goto adv_a;
	}
	else if (FIXNUM_LE(b1,a1)) {
	    if ( !FIXNUM_EQ(a0,b0)) {
		if (EQ(CDDR(result_1),a0)) {
		    max_qm = b0;
		    M_CDDR(result_1) = b0;
		}
		else {
		    if (max_qm) {
			min_qm = FIXNUM_MIN(min_qm,a0);
			max_qm = FIXNUM_MAX(max_qm,b0);
		    }
		    else {
			min_qm = a0;
			max_qm = b0;
		    }
		    new_cons = ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			svref_arg_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index)))) {
			    svref_arg_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(svref_arg_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_region_cons_pool();
		    M_CAR(gensymed_symbol) = a0;
		    M_CDR(gensymed_symbol) = b0;
		    inline_note_allocate_cons(gensymed_symbol,Qregion);
		    result_1 = region_cons_1(gensymed_symbol,result_1);
		}
	    }
	    a0 = b1;
	    goto adv_b;
	}
	else if (FIXNUM_LT(a1,b1)) {
	    if ( !FIXNUM_EQ(a0,b0)) {
		if (EQ(CDDR(result_1),a0)) {
		    max_qm = b0;
		    M_CDDR(result_1) = b0;
		}
		else {
		    if (max_qm) {
			min_qm = FIXNUM_MIN(min_qm,a0);
			max_qm = FIXNUM_MAX(max_qm,b0);
		    }
		    else {
			min_qm = a0;
			max_qm = b0;
		    }
		    new_cons = ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			svref_arg_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index)))) {
			    svref_arg_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(svref_arg_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_region_cons_pool();
		    M_CAR(gensymed_symbol) = a0;
		    M_CDR(gensymed_symbol) = b0;
		    inline_note_allocate_cons(gensymed_symbol,Qregion);
		    result_1 = region_cons_1(gensymed_symbol,result_1);
		}
	    }
	    goto adv_a;
	}
    }
    else if (FIXNUM_LT(b1,a0))
	goto adv_b;
    else if (FIXNUM_LE(a1,b1))
	goto adv_a;
    else if (FIXNUM_LT(b1,a1)) {
	a0 = b1;
	goto adv_b;
    }
  adv_a:
    if ( !TRUEP(a_intervals))
	goto finished_a;
    a0 = M_CAR(FIRST(a_intervals));
    a_intervals_old_value = a_intervals;
    temp = FIRST(a_intervals_old_value);
    a_intervals = REST(a_intervals_old_value);
    a1 = M_CDR(temp);
    goto next;
  adv_b:
    if ( !TRUEP(b_intervals))
	goto finished_b;
    b0 = M_CAR(FIRST(b_intervals));
    b_intervals_old_value = b_intervals;
    temp = FIRST(b_intervals_old_value);
    b_intervals = REST(b_intervals_old_value);
    b1 = M_CDR(temp);
    goto next;
  finished_a:
    temp = nreverse(result_1);
    return VALUES_3(temp,min_qm,max_qm);
  finished_b:
    if ( !FIXNUM_EQ(a0,a1)) {
	if (EQ(CDDR(result_1),a0)) {
	    max_qm = a1;
	    M_CDDR(result_1) = a1;
	}
	else {
	    if (max_qm) {
		min_qm = FIXNUM_MIN(min_qm,a0);
		max_qm = FIXNUM_MAX(max_qm,a1);
	    }
	    else {
		min_qm = a0;
		max_qm = a1;
	    }
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = a0;
	    M_CDR(gensymed_symbol) = a1;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    result_1 = region_cons_1(gensymed_symbol,result_1);
	}
    }
    if (a_intervals) {
	left = Nil;
	right = Nil;
	ab_loop_list_ = a_intervals;
	left_min = FIX((SI_Long)0L);
	ab_loop_maxmin_fl_ = T;
	right_max = FIX((SI_Long)0L);
	ab_loop_maxmin_fl__1 = T;
	tail = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	left = CAR(ab_loop_desetq_);
	right = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (ab_loop_maxmin_fl_) {
	    ab_loop_maxmin_fl_ = Nil;
	    left_min = left;
	}
	else
	    left_min = FIXNUM_MIN(left_min,left);
	if (ab_loop_maxmin_fl__1) {
	    ab_loop_maxmin_fl__1 = Nil;
	    right_max = right;
	}
	else
	    right_max = FIXNUM_MAX(right_max,right);
	ab_loopvar__1 = region_cons_1(region_cons_1(left,right),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    tail = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_1;
      end_loop_1:
	temp_1 = nreconc(result_1,tail);
	temp_2 = FIXNUM_MIN(min_qm,left_min);
	temp = FIXNUM_MAX(max_qm,right_max);
	return VALUES_3(temp_1,temp_2,temp);
    }
    else {
	temp = nreverse(result_1);
	return VALUES_3(temp,min_qm,max_qm);
    }
  next:
    goto loop_head;
    return VALUES_1(Qnil);
}

/* UNION-INTERVALS */
Object union_intervals(a_intervals,b_intervals)
    Object a_intervals, b_intervals;
{
    Object union_intervals_1, a0, a1, b0, b1, temp, left, right, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_;
    Object new_cons, temp_1, svref_arg_2, svref_new_value, gensymed_symbol;
    Object gensymed_symbol_1, temp_2, a_intervals_old_value;
    Object b_intervals_old_value;

    x_note_fn_call(32,168);
    union_intervals_1 = Nil;
    a0 = Nil;
    a1 = Nil;
    b0 = Nil;
    b1 = Nil;
  next_loop:
    if ( !TRUEP(a_intervals) ||  !TRUEP(b_intervals)) {
	temp = union_intervals_1;
	left = Nil;
	right = Nil;
	ab_loop_list_ = a_intervals;
	if (ab_loop_list_);
	else
	    ab_loop_list_ = b_intervals;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	left = CAR(ab_loop_desetq_);
	right = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_region_cons_pool();
	M_CAR(gensymed_symbol_1) = left;
	M_CDR(gensymed_symbol_1) = right;
	inline_note_allocate_cons(gensymed_symbol_1,Qregion);
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	ab_loopvar__2 = gensymed_symbol;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop:
	temp_2 = ab_loopvar_;
	goto end_1;
	temp_2 = Qnil;
      end_1:;
	return nreconc(temp,temp_2);
    }
    a0 = M_CAR(FIRST(a_intervals));
    b0 = M_CAR(FIRST(b_intervals));
    if ( !FIXNUM_LE(a0,b0)) {
	temp_1 = a_intervals;
	a_intervals = b_intervals;
	b_intervals = temp_1;
	temp_1 = a0;
	a0 = b0;
	b0 = temp_1;
    }
    a_intervals_old_value = a_intervals;
    temp_2 = FIRST(a_intervals_old_value);
    a_intervals = REST(a_intervals_old_value);
    a1 = M_CDR(temp_2);
  next_loop_2:
    if ( !TRUEP(b_intervals) || FIXNUM_LT(a1,M_CAR(FIRST(b_intervals)))) {
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = a0;
	M_CDR(gensymed_symbol) = a1;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	union_intervals_1 = region_cons_1(gensymed_symbol,union_intervals_1);
	goto end_2;
    }
    else {
	b_intervals_old_value = b_intervals;
	temp_2 = FIRST(b_intervals_old_value);
	b_intervals = REST(b_intervals_old_value);
	b1 = M_CDR(temp_2);
	if (FIXNUM_LE(b1,a1));
	else {
	    a1 = b1;
	    temp_1 = a_intervals;
	    a_intervals = b_intervals;
	    b_intervals = temp_1;
	}
    }
    goto next_loop_2;
  end_loop_1:
  end_2:
    goto next_loop;
  end_loop_2:
    return VALUES_1(Qnil);
}

/* MAKE-REGION-STRIP-FUNCTION */
Object make_region_strip_function(region_strip_top,region_strip_intervals)
    Object region_strip_top, region_strip_intervals;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(32,169);
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = region_strip_top;
    M_CDR(gensymed_symbol) = region_strip_intervals;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    return VALUES_1(gensymed_symbol);
}

/* POINT-IN-REGION-BOUNDING-BOX-P */
Object point_in_region_bounding_box_p(box,x,y)
    Object box, x, y;
{
    Object interval, point;

    x_note_fn_call(32,170);
    interval = M_CAR(box);
    point = x;
    if (FIXNUM_GE(point,M_CAR(interval)) && FIXNUM_LT(point,M_CDR(interval))) {
	interval = M_CDR(box);
	point = y;
	if (FIXNUM_GE(point,M_CAR(interval)))
	    return VALUES_1(FIXNUM_LT(point,M_CDR(interval)) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REGION-BOUNDING-BOX-EMPTY-P */
Object region_bounding_box_empty_p(box)
    Object box;
{
    Object interval, temp;

    x_note_fn_call(32,171);
    interval = M_CAR(box);
    temp = FIXNUM_LE(M_CDR(interval),M_CAR(interval)) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	interval = M_CDR(box);
	return VALUES_1(FIXNUM_LE(M_CDR(interval),M_CAR(interval)) ? T : Nil);
    }
}

/* UNION-REGION-BOUNDING-BOX */
Object union_region_bounding_box(box1,box2)
    Object box1, box2;
{
    Object interval, interval_left, interval_right, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol;
    Object region_bounding_box_x_interval, region_bounding_box_y_interval;
    Object interval_1, interval_2, temp, temp_1;

    x_note_fn_call(32,172);
    if (box1 && box2) {
	if (region_bounding_box_empty_p(box1)) {
	    interval = M_CAR(box2);
	    interval_left = M_CAR(interval);
	    interval_right = M_CDR(interval);
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = interval_left;
	    M_CDR(gensymed_symbol) = interval_right;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    region_bounding_box_x_interval = gensymed_symbol;
	    interval = M_CDR(box2);
	    interval_left = M_CAR(interval);
	    interval_right = M_CDR(interval);
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = interval_left;
	    M_CDR(gensymed_symbol) = interval_right;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    region_bounding_box_y_interval = gensymed_symbol;
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = region_bounding_box_x_interval;
	    M_CDR(gensymed_symbol) = region_bounding_box_y_interval;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    return VALUES_1(gensymed_symbol);
	}
	else if (region_bounding_box_empty_p(box2)) {
	    interval = M_CAR(box1);
	    interval_left = M_CAR(interval);
	    interval_right = M_CDR(interval);
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = interval_left;
	    M_CDR(gensymed_symbol) = interval_right;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    region_bounding_box_x_interval = gensymed_symbol;
	    interval = M_CDR(box1);
	    interval_left = M_CAR(interval);
	    interval_right = M_CDR(interval);
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = interval_left;
	    M_CDR(gensymed_symbol) = interval_right;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    region_bounding_box_y_interval = gensymed_symbol;
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = region_bounding_box_x_interval;
	    M_CDR(gensymed_symbol) = region_bounding_box_y_interval;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    return VALUES_1(gensymed_symbol);
	}
	else {
	    interval_1 = M_CAR(box1);
	    interval_2 = M_CAR(box2);
	    temp = M_CAR(interval_1);
	    temp_1 = M_CAR(interval_2);
	    interval_left = FIXNUM_MIN(temp,temp_1);
	    temp = M_CDR(interval_1);
	    temp_1 = M_CDR(interval_2);
	    interval_right = FIXNUM_MAX(temp,temp_1);
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = interval_left;
	    M_CDR(gensymed_symbol) = interval_right;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    region_bounding_box_x_interval = gensymed_symbol;
	    interval_1 = M_CDR(box1);
	    interval_2 = M_CDR(box2);
	    temp = M_CAR(interval_1);
	    temp_1 = M_CAR(interval_2);
	    interval_left = FIXNUM_MIN(temp,temp_1);
	    temp = M_CDR(interval_1);
	    temp_1 = M_CDR(interval_2);
	    interval_right = FIXNUM_MAX(temp,temp_1);
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = interval_left;
	    M_CDR(gensymed_symbol) = interval_right;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    region_bounding_box_y_interval = gensymed_symbol;
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = region_bounding_box_x_interval;
	    M_CDR(gensymed_symbol) = region_bounding_box_y_interval;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    return VALUES_1(gensymed_symbol);
	}
    }
    else
	return VALUES_1(Nil);
}

/* REGION-BOUNDING-BOX-INTERSECT-P */
Object region_bounding_box_intersect_p(box1,box2)
    Object box1, box2;
{
    x_note_fn_call(32,173);
    if (right_open_intervals_intersect_p(M_CAR(box1),M_CAR(box2)))
	return right_open_intervals_intersect_p(M_CDR(box1),M_CDR(box2));
    else
	return VALUES_1(Nil);
}

/* RECLAIM-REGION */
Object reclaim_region(region_qm)
    Object region_qm;
{
    x_note_fn_call(32,174);
    return VALUES_1(Nil);
}

/* COPY-REGION */
Object copy_region(region)
    Object region;
{
    Object strips, strip, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, region_strip_top, left, right, ab_loop_list__1;
    Object ab_loopvar__3, ab_loopvar__4, ab_loop_desetq_, gensymed_symbol_1;
    Object gensymed_symbol_2, region_strip_intervals, region_strips, box;
    Object interval, interval_left, interval_right;
    Object region_bounding_box_x_interval, region_bounding_box_y_interval;
    Object region_bounding_box;

    x_note_fn_call(32,175);
    strips = M_CAR(region);
    strip = Nil;
    ab_loop_list_ = strips;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    strip = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    if (strip) {
	region_strip_top = CAR(strip);
	left = Nil;
	right = Nil;
	ab_loop_list__1 = CDR(strip);
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	left = CAR(ab_loop_desetq_);
	right = CDR(ab_loop_desetq_);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_region_cons_pool();
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_region_cons_pool();
	M_CAR(gensymed_symbol_2) = left;
	M_CDR(gensymed_symbol_2) = right;
	inline_note_allocate_cons(gensymed_symbol_2,Qregion);
	M_CAR(gensymed_symbol_1) = gensymed_symbol_2;
	M_CDR(gensymed_symbol_1) = Nil;
	inline_note_allocate_cons(gensymed_symbol_1,Qregion);
	ab_loopvar__4 = gensymed_symbol_1;
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
	goto next_loop_1;
      end_loop_1:
	region_strip_intervals = ab_loopvar__2;
	goto end_1;
	region_strip_intervals = Qnil;
      end_1:;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_region_cons_pool();
	M_CAR(gensymed_symbol_1) = region_strip_top;
	M_CDR(gensymed_symbol_1) = region_strip_intervals;
	inline_note_allocate_cons(gensymed_symbol_1,Qregion);
    }
    else
	gensymed_symbol_1 = Nil;
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    region_strips = ab_loopvar_;
    goto end_2;
    region_strips = Qnil;
  end_2:;
    box = M_CDR(region);
    interval = M_CAR(box);
    interval_left = M_CAR(interval);
    interval_right = M_CDR(interval);
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = interval_left;
    M_CDR(gensymed_symbol) = interval_right;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    region_bounding_box_x_interval = gensymed_symbol;
    interval = M_CDR(box);
    interval_left = M_CAR(interval);
    interval_right = M_CDR(interval);
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = interval_left;
    M_CDR(gensymed_symbol) = interval_right;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    region_bounding_box_y_interval = gensymed_symbol;
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = region_bounding_box_x_interval;
    M_CDR(gensymed_symbol) = region_bounding_box_y_interval;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    region_bounding_box = gensymed_symbol;
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = region_strips;
    M_CDR(gensymed_symbol) = region_bounding_box;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    return VALUES_1(gensymed_symbol);
}

/* MAKE-EMPTY-REGION */
Object make_empty_region()
{
    Object region_strips, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, region_bounding_box_x_interval;
    Object region_bounding_box_y_interval, region_bounding_box;

    x_note_fn_call(32,176);
    region_strips = Nil;
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = FIX((SI_Long)0L);
    M_CDR(gensymed_symbol) = FIX((SI_Long)0L);
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    region_bounding_box_x_interval = gensymed_symbol;
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = FIX((SI_Long)0L);
    M_CDR(gensymed_symbol) = FIX((SI_Long)0L);
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    region_bounding_box_y_interval = gensymed_symbol;
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = region_bounding_box_x_interval;
    M_CDR(gensymed_symbol) = region_bounding_box_y_interval;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    region_bounding_box = gensymed_symbol;
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = region_strips;
    M_CDR(gensymed_symbol) = region_bounding_box;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    return VALUES_1(gensymed_symbol);
}

/* MAKE-UNBOUNDED-REGION */
Object make_unbounded_region()
{
    Object infinity_1;

    x_note_fn_call(32,177);
    infinity_1 = ash(Most_positive_fixnum,FIX((SI_Long)-2L));
    return make_region_from_rectangle(FIXNUM_NEGATE(infinity_1),
	    FIXNUM_NEGATE(infinity_1),infinity_1,infinity_1);
}

/* REGION-BOUNDING-RECTANGLE */
Object region_bounding_rectangle(region)
    Object region;
{
    Object region_bounding_box, bounding_box_x, bounding_box_y;

    x_note_fn_call(32,178);
    region_bounding_box = M_CDR(region);
    bounding_box_x = M_CAR(region_bounding_box);
    bounding_box_y = M_CDR(region_bounding_box);
    return VALUES_4(M_CAR(bounding_box_x),M_CAR(bounding_box_y),
	    M_CDR(bounding_box_x),M_CDR(bounding_box_y));
}

/* MAKE-REGION-FROM-RECTANGLE */
Object make_region_from_rectangle(left,top,right,bottom)
    Object left, top, right, bottom;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value, region_strip_top, new_cons, gensymed_symbol_2;
    Object gensymed_symbol_3, region_strip_intervals, region_strips;
    Object region_bounding_box_x_interval, region_bounding_box_y_interval;
    Object region_bounding_box;

    x_note_fn_call(32,179);
    if (FIXNUM_LE(left,right) && FIXNUM_LE(top,bottom)) {
	gensymed_symbol = Nil;
      next_loop:
	temp = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	gensymed_symbol = CDR(temp);
	if (gensymed_symbol)
	    goto end_loop;
	replenish_region_list_pool(FIX((SI_Long)1L));
	goto next_loop;
      end_loop:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol_1 = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_1:
	    inline_note_allocate_cons(gensymed_symbol_1,Qregion);
	    if (EQ(gensymed_symbol_1,gensymed_symbol))
		goto end_loop_1;
	    gensymed_symbol_1 = CDR(gensymed_symbol_1);
	    goto next_loop_1;
	  end_loop_1:;
	}
	temp = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	M_CDR(gensymed_symbol) = Nil;
	gensymed_symbol = temp;
	goto end_1;
	gensymed_symbol = Qnil;
      end_1:;
	gensymed_symbol_1 = gensymed_symbol;
	region_strip_top = top;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_region_cons_pool();
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_3 = new_cons;
	}
	else
	    gensymed_symbol_3 = Nil;
	if ( !TRUEP(gensymed_symbol_3))
	    gensymed_symbol_3 = replenish_region_cons_pool();
	M_CAR(gensymed_symbol_3) = left;
	M_CDR(gensymed_symbol_3) = right;
	inline_note_allocate_cons(gensymed_symbol_3,Qregion);
	M_CAR(gensymed_symbol_2) = gensymed_symbol_3;
	M_CDR(gensymed_symbol_2) = Nil;
	inline_note_allocate_cons(gensymed_symbol_2,Qregion);
	region_strip_intervals = gensymed_symbol_2;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_region_cons_pool();
	M_CAR(gensymed_symbol_2) = region_strip_top;
	M_CDR(gensymed_symbol_2) = region_strip_intervals;
	inline_note_allocate_cons(gensymed_symbol_2,Qregion);
	M_CAR(gensymed_symbol_1) = gensymed_symbol_2;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	region_strip_top = bottom;
	region_strip_intervals = Nil;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_region_cons_pool();
	M_CAR(gensymed_symbol_2) = region_strip_top;
	M_CDR(gensymed_symbol_2) = region_strip_intervals;
	inline_note_allocate_cons(gensymed_symbol_2,Qregion);
	M_CAR(gensymed_symbol_1) = gensymed_symbol_2;
	region_strips = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = left;
	M_CDR(gensymed_symbol) = right;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box_x_interval = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = top;
	M_CDR(gensymed_symbol) = bottom;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box_y_interval = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = region_bounding_box_x_interval;
	M_CDR(gensymed_symbol) = region_bounding_box_y_interval;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = region_strips;
	M_CDR(gensymed_symbol) = region_bounding_box;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	return VALUES_1(gensymed_symbol);
    }
    else
	return make_empty_region();
}

/* SIMPLIFY-REGION */
Object simplify_region(region)
    Object region;
{
    Object left, top, right, bottom, temp;
    Object result;

    x_note_fn_call(32,180);
    result = region_bounding_rectangle(region);
    MVS_4(result,left,top,right,bottom);
    temp = make_region_from_rectangle(left,top,right,bottom);
    reclaim_region(region);
    return VALUES_1(temp);
}

/* REGION-COMPLEXITY */
Object region_complexity(region)
    Object region;
{
    SI_Long temp;

    x_note_fn_call(32,181);
    temp = IFIX(FIXNUM_SUB1(length(M_CAR(region))));
    return VALUES_1(FIX(MAX((SI_Long)0L,temp)));
}

/* REGIONS-POSSIBLY-INTERSECT-P */
Object regions_possibly_intersect_p(region_1,region_2)
    Object region_1, region_2;
{
    Object left_1, top_1, right_1, bottom_1, left_2, top_2, right_2, bottom_2;
    Object temp;
    Object result;

    x_note_fn_call(32,182);
    if ( ! !TRUEP(M_CAR(region_1)) &&  ! !TRUEP(M_CAR(region_2))) {
	result = region_bounding_rectangle(region_1);
	MVS_4(result,left_1,top_1,right_1,bottom_1);
	result = region_bounding_rectangle(region_2);
	MVS_4(result,left_2,top_2,right_2,bottom_2);
	if (FIXNUM_GE(bottom_2,bottom_1) && FIXNUM_GE(bottom_1,top_2) || 
		FIXNUM_GE(bottom_1,bottom_2) && FIXNUM_GE(bottom_2,top_1)) {
	    temp = FIXNUM_GE(right_2,right_1) ? (FIXNUM_GE(right_1,left_2) 
		    ? T : Nil) : Qnil;
	    if (temp)
		return VALUES_1(temp);
	    else if (FIXNUM_GE(right_1,right_2))
		return VALUES_1(FIXNUM_GE(right_2,left_1) ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REGION-EQUAL */
Object region_equal(region1,region2)
    Object region1, region2;
{
    Object box1, box2, temp, temp_1, s1_1, ab_loop_list_, s2_1;
    Object ab_loop_list__1, i1, ab_loop_list__2, i2, ab_loop_list__3;
    char temp_2;

    x_note_fn_call(32,183);
    box1 = M_CDR(region1);
    box2 = M_CDR(region2);
    temp = M_CAR(box1);
    temp_1 = M_CAR(box2);
    if (EQUAL(temp,temp_1)) {
	temp_1 = M_CDR(box1);
	temp = M_CDR(box2);
	temp_2 = EQUAL(temp_1,temp);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2 ? FIXNUM_EQ(length(M_CAR(region1)),length(M_CAR(region2))) :
	     TRUEP(Nil)) {
	s1_1 = Nil;
	ab_loop_list_ = M_CAR(region1);
	s2_1 = Nil;
	ab_loop_list__1 = M_CAR(region2);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	s1_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	s2_1 = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (FIXNUM_EQ(CAR(s1_1),CAR(s2_1)) && FIXNUM_EQ(length(CDR(s1_1)),
		length(CDR(s2_1)))) {
	    i1 = Nil;
	    ab_loop_list__2 = CDR(s1_1);
	    i2 = Nil;
	    ab_loop_list__3 = CDR(s2_1);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_1;
	    i1 = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    if ( !TRUEP(ab_loop_list__3))
		goto end_loop_1;
	    i2 = M_CAR(ab_loop_list__3);
	    ab_loop_list__3 = M_CDR(ab_loop_list__3);
	    if ( !EQUAL(i1,i2)) {
		temp_2 = TRUEP(Nil);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = TRUEP(T);
	    goto end_1;
	    temp_2 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_2 = TRUEP(Nil);
	if ( !temp_2)
	    return VALUES_1(Nil);
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scratch_rectangle_region, Qscratch_rectangle_region);

/* RECTANGLE-IN-REGION-P */
Object rectangle_in_region_p(left,top,right,bottom,region)
    Object left, top, right, bottom, region;
{
    Object strips, car_arg, temp, interval, box, rectangle, intersection_1;

    x_note_fn_call(32,184);
    strips = M_CAR(Scratch_rectangle_region);
    car_arg = FIRST(strips);
    M_CAR(car_arg) = top;
    car_arg = SECOND(strips);
    M_CAR(car_arg) = bottom;
    temp = FIRST(strips);
    temp = CDR(temp);
    interval = FIRST(temp);
    M_CAR(interval) = left;
    M_CDR(interval) = right;
    box = M_CDR(Scratch_rectangle_region);
    interval = M_CAR(box);
    M_CAR(interval) = left;
    M_CDR(interval) = right;
    interval = M_CDR(box);
    left = top;
    right = bottom;
    M_CAR(interval) = left;
    M_CDR(interval) = right;
    rectangle = Scratch_rectangle_region;
    if (regions_possibly_intersect_p(rectangle,region)) {
	intersection_1 = intersect_region(rectangle,region);
	temp = region_equal(rectangle,intersection_1);
	reclaim_region(intersection_1);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* ADD-RECTANGLE-TO-REGION */
Object add_rectangle_to_region(left,top,right,bottom,region)
    Object left, top, right, bottom, region;
{
    Object strips, car_arg, temp, interval, box, result_1;

    x_note_fn_call(32,185);
    if (FIXNUM_LE(left,right) && FIXNUM_LE(top,bottom)) {
	strips = M_CAR(Scratch_rectangle_region);
	car_arg = FIRST(strips);
	M_CAR(car_arg) = top;
	car_arg = SECOND(strips);
	M_CAR(car_arg) = bottom;
	temp = FIRST(strips);
	temp = CDR(temp);
	interval = FIRST(temp);
	M_CAR(interval) = left;
	M_CDR(interval) = right;
	box = M_CDR(Scratch_rectangle_region);
	interval = M_CAR(box);
	M_CAR(interval) = left;
	M_CDR(interval) = right;
	interval = M_CDR(box);
	left = top;
	right = bottom;
	M_CAR(interval) = left;
	M_CDR(interval) = right;
	result_1 = union_region(Scratch_rectangle_region,region);
	reclaim_region(region);
	temp = result_1;
    }
    else
	temp = region;
    return VALUES_1(temp);
}

/* REMOVE-RECTANGLE-FROM-REGION */
Object remove_rectangle_from_region(left,top,right,bottom,region)
    Object left, top, right, bottom, region;
{
    Object strips, car_arg, temp, interval, box;

    x_note_fn_call(32,186);
    if (FIXNUM_LE(left,right) && FIXNUM_LE(top,bottom)) {
	strips = M_CAR(Scratch_rectangle_region);
	car_arg = FIRST(strips);
	M_CAR(car_arg) = top;
	car_arg = SECOND(strips);
	M_CAR(car_arg) = bottom;
	temp = FIRST(strips);
	temp = CDR(temp);
	interval = FIRST(temp);
	M_CAR(interval) = left;
	M_CDR(interval) = right;
	box = M_CDR(Scratch_rectangle_region);
	interval = M_CAR(box);
	M_CAR(interval) = left;
	M_CDR(interval) = right;
	interval = M_CDR(box);
	left = top;
	right = bottom;
	M_CAR(interval) = left;
	M_CDR(interval) = right;
	temp = subtract_region(region,Scratch_rectangle_region);
	reclaim_region(region);
    }
    else
	temp = region;
    return VALUES_1(temp);
}

/* SHIFT-REGION */
Object shift_region(region,delta_x,delta_y)
    Object region, delta_x, delta_y;
{
    Object tail, strip, incff_1_arg, temp, tail_1, interval, box, delta;

    x_note_fn_call(32,187);
    tail = M_CAR(region);
    strip = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	strip = CAR(tail);
	incff_1_arg = delta_y;
	temp = FIXNUM_ADD(CAR(strip),incff_1_arg);
	M_CAR(strip) = temp;
	if ( !((SI_Long)0L == IFIX(delta_x))) {
	    tail_1 = CDR(strip);
	    interval = Nil;
	    for ( ; !ENDP(tail_1); tail_1 = CDR(tail_1)) {
		interval = CAR(tail_1);
		incff_1_arg = delta_x;
		temp = FIXNUM_ADD(M_CAR(interval),incff_1_arg);
		M_CAR(interval) = temp;
		incff_1_arg = delta_x;
		temp = FIXNUM_ADD(M_CDR(interval),incff_1_arg);
		M_CDR(interval) = temp;
	    }
	}
    }
    box = M_CDR(region);
    interval = M_CAR(box);
    delta = delta_x;
    incff_1_arg = delta;
    temp = FIXNUM_ADD(M_CAR(interval),incff_1_arg);
    M_CAR(interval) = temp;
    incff_1_arg = delta;
    temp = FIXNUM_ADD(M_CDR(interval),incff_1_arg);
    M_CDR(interval) = temp;
    interval = M_CDR(box);
    delta = delta_y;
    incff_1_arg = delta;
    temp = FIXNUM_ADD(M_CAR(interval),incff_1_arg);
    M_CAR(interval) = temp;
    incff_1_arg = delta;
    temp = FIXNUM_ADD(M_CDR(interval),incff_1_arg);
    M_CDR(interval) = temp;
    return VALUES_1(region);
}

/* UNION-REGION */
Object union_region(region1,region2)
    Object region1, region2;
{
    Object strips_union, strips2, prior_strip2, temp, top2, strips1;
    Object prior_strip1, top1, temp_1, strip_intervals, interval;
    Object ab_loop_list_, svref_arg_2, new_cons, svref_new_value;
    Object gensymed_symbol, temp_2, strip, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, region_strip_top, left, right, ab_loop_list__1;
    Object ab_loopvar__3, ab_loopvar__4, ab_loop_desetq_, gensymed_symbol_1;
    Object gensymed_symbol_2, region_strip_intervals, region_strips;
    Object region_bounding_box;

    x_note_fn_call(32,188);
    if ( !TRUEP(M_CAR(region1)))
	return copy_region(region2);
    if ( !TRUEP(M_CAR(region2)))
	return copy_region(region1);
    strips_union = Nil;
    strips2 = M_CAR(region2);
    prior_strip2 = Nil;
    temp = FIRST(strips2);
    top2 = CAR(temp);
    strips1 = M_CAR(region1);
    prior_strip1 = Nil;
    top1 = Nil;
    if ( !TRUEP(strips2)) {
	temp_1 = strips1;
	strips1 = strips2;
	strips2 = temp_1;
	temp_1 = top1;
	top1 = top2;
	top2 = temp_1;
	temp_1 = prior_strip1;
	prior_strip1 = prior_strip2;
	prior_strip2 = temp_1;
    }
  next_loop:
    if ( !TRUEP(strips1))
	goto end_loop;
    temp = FIRST(strips1);
    top1 = CAR(temp);
    if ( !FIXNUM_EQ(top1,top2)) {
	if (FIXNUM_GT(top1,top2)) {
	    temp_1 = strips1;
	    strips1 = strips2;
	    strips2 = temp_1;
	    temp_1 = top1;
	    top1 = top2;
	    top2 = temp_1;
	    temp_1 = prior_strip1;
	    prior_strip1 = prior_strip2;
	    prior_strip2 = temp_1;
	}
	temp = FIRST(strips1);
	strip_intervals = union_intervals(CDR(temp),CDR(prior_strip2));
	temp = FIRST(strips_union);
	temp = CDR(temp);
	if (EQUAL(strip_intervals,temp)) {
	    interval = Nil;
	    ab_loop_list_ = strip_intervals;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    interval = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    inline_note_reclaim_cons(interval,Qregion);
	    if (ISVREF(Available_region_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_region_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = interval;
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = interval;
	    }
	    else {
		temp_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = interval;
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = interval;
	    }
	    M_CDR(interval) = Nil;
	    goto next_loop_1;
	  end_loop_1:
	    reclaim_region_list_1(strip_intervals);
	}
	else {
	    new_cons = ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_1 = Available_region_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_region_cons_pool();
	    M_CAR(gensymed_symbol) = top1;
	    M_CDR(gensymed_symbol) = strip_intervals;
	    inline_note_allocate_cons(gensymed_symbol,Qregion);
	    strips_union = region_cons_1(gensymed_symbol,strips_union);
	}
    }
    temp = M_CDR(strips1);
    prior_strip1 = FIRST(strips1);
    strips1 = temp;
    goto next_loop;
  end_loop:
    temp_2 = strips_union;
    strip = Nil;
    ab_loop_list_ = strips2;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    strip = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    if (strip) {
	region_strip_top = CAR(strip);
	left = Nil;
	right = Nil;
	ab_loop_list__1 = CDR(strip);
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_3;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	left = CAR(ab_loop_desetq_);
	right = CDR(ab_loop_desetq_);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_region_cons_pool();
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_region_cons_pool();
	M_CAR(gensymed_symbol_2) = left;
	M_CDR(gensymed_symbol_2) = right;
	inline_note_allocate_cons(gensymed_symbol_2,Qregion);
	M_CAR(gensymed_symbol_1) = gensymed_symbol_2;
	M_CDR(gensymed_symbol_1) = Nil;
	inline_note_allocate_cons(gensymed_symbol_1,Qregion);
	ab_loopvar__4 = gensymed_symbol_1;
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
	goto next_loop_3;
      end_loop_3:
	region_strip_intervals = ab_loopvar__2;
	goto end_1;
	region_strip_intervals = Qnil;
      end_1:;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_region_cons_pool();
	M_CAR(gensymed_symbol_1) = region_strip_top;
	M_CDR(gensymed_symbol_1) = region_strip_intervals;
	inline_note_allocate_cons(gensymed_symbol_1,Qregion);
    }
    else
	gensymed_symbol_1 = Nil;
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_2;
  end_loop_2:
    temp = ab_loopvar_;
    goto end_2;
    temp = Qnil;
  end_2:;
    region_strips = nreconc(temp_2,temp);
    region_bounding_box = union_region_bounding_box(M_CDR(region1),
	    M_CDR(region2));
    new_cons = ISVREF(Available_region_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_region_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_region_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_region_cons_pool();
    M_CAR(gensymed_symbol) = region_strips;
    M_CDR(gensymed_symbol) = region_bounding_box;
    inline_note_allocate_cons(gensymed_symbol,Qregion);
    return VALUES_1(gensymed_symbol);
    return VALUES_1(Qnil);
}

/* INTERSECT-REGION-P-1 */
Object intersect_region_p_1(region_a,region_b)
    Object region_a, region_b;
{
    Object bounding_box_a, bounding_box_b;
    char temp;

    x_note_fn_call(32,189);
    temp =  !TRUEP(M_CAR(region_a));
    if (temp);
    else
	temp =  !TRUEP(M_CAR(region_b));
    if (temp);
    else {
	bounding_box_a = M_CDR(region_a);
	bounding_box_b = M_CDR(region_b);
	temp =  
		!TRUEP(right_open_intervals_intersect_p(M_CAR(bounding_box_a),
		M_CAR(bounding_box_b)));
	if (temp);
	else
	    temp =  
		    !TRUEP(right_open_intervals_intersect_p(M_CDR(bounding_box_a),
		    M_CDR(bounding_box_b)));
    }
    return VALUES_1( !temp ? T : Nil);
}

/* REGIONS-INTERSECT-P */
Object regions_intersect_p(region_a,region_b)
    Object region_a, region_b;
{
    Object intersection_1, temp;

    x_note_fn_call(32,190);
    if (intersect_region_p_1(region_a,region_b)) {
	intersection_1 = intersect_region(region_a,region_b);
	temp =  ! !TRUEP(M_CAR(intersection_1)) ? T : Nil;
	reclaim_region(intersection_1);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* INTERSECT-REGION */
Object intersect_region(region_a,region_b)
    Object region_a, region_b;
{
    Object region_strips_a, region_strips_b, result_top, result_strips;
    Object result_left, result_right, a0, a1, ai, b0, b1, bi, last_bottom_qm;
    Object last_intervals_qm, region_strips_a_old_value, temp, a;
    Object region_strips_b_old_value, b, cantidate_intervals_qm, left_qm;
    Object right_qm, interval, ab_loop_list_, temp_1, svref_arg_2, new_cons;
    Object svref_new_value, gensymed_symbol, region_strips;
    Object region_bounding_box_x_interval, region_bounding_box_y_interval;
    Object region_bounding_box;
    Object result;

    x_note_fn_call(32,191);
    if ( !TRUEP(intersect_region_p_1(region_a,region_b)))
	return make_empty_region();
    region_strips_a = M_CAR(region_a);
    region_strips_b = M_CAR(region_b);
    result_top = Nil;
    result_strips = Nil;
    result_left = Nil;
    result_right = Nil;
    a0 = Nil;
    a1 = Nil;
    ai = Nil;
    b0 = Nil;
    b1 = Nil;
    bi = Nil;
    last_bottom_qm = Nil;
    last_intervals_qm = Nil;
    if ( !TRUEP(CDR(region_strips_a)))
	goto finished_a;
    region_strips_a_old_value = region_strips_a;
    temp = FIRST(region_strips_a_old_value);
    region_strips_a = REST(region_strips_a_old_value);
    a = temp;
    ai = CDR(a);
    a0 = CAR(a);
    temp = FIRST(region_strips_a);
    a1 = CAR(temp);
    if ( !TRUEP(CDR(region_strips_b)))
	goto finished_b;
    region_strips_b_old_value = region_strips_b;
    temp = FIRST(region_strips_b_old_value);
    region_strips_b = REST(region_strips_b_old_value);
    b = temp;
    bi = CDR(b);
    b0 = CAR(b);
    temp = FIRST(region_strips_b);
    b1 = CAR(temp);
  loop_body:
    if (FIXNUM_LT(a0,b0)) {
	if (FIXNUM_LT(a1,b0))
	    goto adv_a;
	else if (FIXNUM_LE(b1,a1)) {
	    if ( !FIXNUM_EQ(b0,b1)) {
		result = intersect_intervals(ai,bi);
		MVS_3(result,cantidate_intervals_qm,left_qm,right_qm);
		if (cantidate_intervals_qm) {
		    if (last_bottom_qm) {
			result_left = FIXNUM_MIN(result_left,left_qm);
			result_right = FIXNUM_MAX(result_right,right_qm);
		    }
		    else {
			result_left = left_qm;
			result_right = right_qm;
			result_top = b0;
		    }
		    if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,b0) && 
			    EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
			interval = Nil;
			ab_loop_list_ = cantidate_intervals_qm;
		      next_loop:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop;
			interval = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			inline_note_reclaim_cons(interval,Qregion);
			if (ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_region_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			else {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			M_CDR(interval) = Nil;
			goto next_loop;
		      end_loop:
			reclaim_region_list_1(cantidate_intervals_qm);
		    }
		    else {
			if (last_bottom_qm) {
			    if ( !FIXNUM_EQ(last_bottom_qm,b0)) {
				new_cons = 
					ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    temp_1 = Available_region_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(temp_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_region_conses_vector,
					    IFIX(Current_thread_index)))) {
					temp_1 = 
						Available_region_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(temp_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol = new_cons;
				}
				else
				    gensymed_symbol = Nil;
				if ( !TRUEP(gensymed_symbol))
				    gensymed_symbol = 
					    replenish_region_cons_pool();
				M_CAR(gensymed_symbol) = last_bottom_qm;
				M_CDR(gensymed_symbol) = Nil;
				inline_note_allocate_cons(gensymed_symbol,
					Qregion);
				result_strips = 
					region_cons_1(gensymed_symbol,
					result_strips);
			    }
			}
			new_cons = ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = Available_region_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_region_cons_pool();
			M_CAR(gensymed_symbol) = b0;
			M_CDR(gensymed_symbol) = cantidate_intervals_qm;
			inline_note_allocate_cons(gensymed_symbol,Qregion);
			result_strips = region_cons_1(gensymed_symbol,
				result_strips);
			last_intervals_qm = cantidate_intervals_qm;
		    }
		    last_bottom_qm = b1;
		}
	    }
	    goto adv_b;
	}
	else if (FIXNUM_LT(a1,b1)) {
	    if ( !FIXNUM_EQ(b0,a1)) {
		result = intersect_intervals(ai,bi);
		MVS_3(result,cantidate_intervals_qm,left_qm,right_qm);
		if (cantidate_intervals_qm) {
		    if (last_bottom_qm) {
			result_left = FIXNUM_MIN(result_left,left_qm);
			result_right = FIXNUM_MAX(result_right,right_qm);
		    }
		    else {
			result_left = left_qm;
			result_right = right_qm;
			result_top = b0;
		    }
		    if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,b0) && 
			    EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
			interval = Nil;
			ab_loop_list_ = cantidate_intervals_qm;
		      next_loop_1:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_1;
			interval = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			inline_note_reclaim_cons(interval,Qregion);
			if (ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_region_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			else {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			M_CDR(interval) = Nil;
			goto next_loop_1;
		      end_loop_1:
			reclaim_region_list_1(cantidate_intervals_qm);
		    }
		    else {
			if (last_bottom_qm) {
			    if ( !FIXNUM_EQ(last_bottom_qm,b0)) {
				new_cons = 
					ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    temp_1 = Available_region_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(temp_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_region_conses_vector,
					    IFIX(Current_thread_index)))) {
					temp_1 = 
						Available_region_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(temp_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol = new_cons;
				}
				else
				    gensymed_symbol = Nil;
				if ( !TRUEP(gensymed_symbol))
				    gensymed_symbol = 
					    replenish_region_cons_pool();
				M_CAR(gensymed_symbol) = last_bottom_qm;
				M_CDR(gensymed_symbol) = Nil;
				inline_note_allocate_cons(gensymed_symbol,
					Qregion);
				result_strips = 
					region_cons_1(gensymed_symbol,
					result_strips);
			    }
			}
			new_cons = ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = Available_region_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_region_cons_pool();
			M_CAR(gensymed_symbol) = b0;
			M_CDR(gensymed_symbol) = cantidate_intervals_qm;
			inline_note_allocate_cons(gensymed_symbol,Qregion);
			result_strips = region_cons_1(gensymed_symbol,
				result_strips);
			last_intervals_qm = cantidate_intervals_qm;
		    }
		    last_bottom_qm = a1;
		}
	    }
	    goto adv_a;
	}
    }
    else if (FIXNUM_LT(b1,a0))
	goto adv_b;
    else if (FIXNUM_LE(a1,b1)) {
	if ( !FIXNUM_EQ(a0,a1)) {
	    result = intersect_intervals(ai,bi);
	    MVS_3(result,cantidate_intervals_qm,left_qm,right_qm);
	    if (cantidate_intervals_qm) {
		if (last_bottom_qm) {
		    result_left = FIXNUM_MIN(result_left,left_qm);
		    result_right = FIXNUM_MAX(result_right,right_qm);
		}
		else {
		    result_left = left_qm;
		    result_right = right_qm;
		    result_top = a0;
		}
		if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,a0) && 
			EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
		    interval = Nil;
		    ab_loop_list_ = cantidate_intervals_qm;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_2;
		    interval = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    inline_note_reclaim_cons(interval,Qregion);
		    if (ISVREF(Available_region_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = interval;
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
		    }
		    else {
			temp_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
		    }
		    M_CDR(interval) = Nil;
		    goto next_loop_2;
		  end_loop_2:
		    reclaim_region_list_1(cantidate_intervals_qm);
		}
		else {
		    if (last_bottom_qm) {
			if ( !FIXNUM_EQ(last_bottom_qm,a0)) {
			    new_cons = 
				    ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_region_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_1,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_region_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = replenish_region_cons_pool();
			    M_CAR(gensymed_symbol) = last_bottom_qm;
			    M_CDR(gensymed_symbol) = Nil;
			    inline_note_allocate_cons(gensymed_symbol,Qregion);
			    result_strips = region_cons_1(gensymed_symbol,
				    result_strips);
			}
		    }
		    new_cons = ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_region_cons_pool();
		    M_CAR(gensymed_symbol) = a0;
		    M_CDR(gensymed_symbol) = cantidate_intervals_qm;
		    inline_note_allocate_cons(gensymed_symbol,Qregion);
		    result_strips = region_cons_1(gensymed_symbol,
			    result_strips);
		    last_intervals_qm = cantidate_intervals_qm;
		}
		last_bottom_qm = a1;
	    }
	}
	goto adv_a;
    }
    else if (FIXNUM_LT(b1,a1)) {
	if ( !FIXNUM_EQ(a0,b1)) {
	    result = intersect_intervals(ai,bi);
	    MVS_3(result,cantidate_intervals_qm,left_qm,right_qm);
	    if (cantidate_intervals_qm) {
		if (last_bottom_qm) {
		    result_left = FIXNUM_MIN(result_left,left_qm);
		    result_right = FIXNUM_MAX(result_right,right_qm);
		}
		else {
		    result_left = left_qm;
		    result_right = right_qm;
		    result_top = a0;
		}
		if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,a0) && 
			EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
		    interval = Nil;
		    ab_loop_list_ = cantidate_intervals_qm;
		  next_loop_3:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_3;
		    interval = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    inline_note_reclaim_cons(interval,Qregion);
		    if (ISVREF(Available_region_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = interval;
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
		    }
		    else {
			temp_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
		    }
		    M_CDR(interval) = Nil;
		    goto next_loop_3;
		  end_loop_3:
		    reclaim_region_list_1(cantidate_intervals_qm);
		}
		else {
		    if (last_bottom_qm) {
			if ( !FIXNUM_EQ(last_bottom_qm,a0)) {
			    new_cons = 
				    ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_region_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_1,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_region_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = replenish_region_cons_pool();
			    M_CAR(gensymed_symbol) = last_bottom_qm;
			    M_CDR(gensymed_symbol) = Nil;
			    inline_note_allocate_cons(gensymed_symbol,Qregion);
			    result_strips = region_cons_1(gensymed_symbol,
				    result_strips);
			}
		    }
		    new_cons = ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_region_cons_pool();
		    M_CAR(gensymed_symbol) = a0;
		    M_CDR(gensymed_symbol) = cantidate_intervals_qm;
		    inline_note_allocate_cons(gensymed_symbol,Qregion);
		    result_strips = region_cons_1(gensymed_symbol,
			    result_strips);
		    last_intervals_qm = cantidate_intervals_qm;
		}
		last_bottom_qm = b1;
	    }
	}
	goto adv_b;
    }
  adv_a:
    if ( !TRUEP(CDR(region_strips_a)))
	goto finished_a;
    region_strips_a_old_value = region_strips_a;
    temp = FIRST(region_strips_a_old_value);
    region_strips_a = REST(region_strips_a_old_value);
    a = temp;
    ai = CDR(a);
    a0 = CAR(a);
    temp = FIRST(region_strips_a);
    a1 = CAR(temp);
    goto next;
  adv_b:
    if ( !TRUEP(CDR(region_strips_b)))
	goto finished_b;
    region_strips_b_old_value = region_strips_b;
    temp = FIRST(region_strips_b_old_value);
    region_strips_b = REST(region_strips_b_old_value);
    b = temp;
    bi = CDR(b);
    b0 = CAR(b);
    temp = FIRST(region_strips_b);
    b1 = CAR(temp);
    goto next;
  finished_a:
  finished_b:
    if (last_bottom_qm) {
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = last_bottom_qm;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	result_strips = region_cons_1(gensymed_symbol,result_strips);
	region_strips = nreverse(result_strips);
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = result_left;
	M_CDR(gensymed_symbol) = result_right;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box_x_interval = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = result_top;
	M_CDR(gensymed_symbol) = last_bottom_qm;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box_y_interval = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = region_bounding_box_x_interval;
	M_CDR(gensymed_symbol) = region_bounding_box_y_interval;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = region_strips;
	M_CDR(gensymed_symbol) = region_bounding_box;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	return VALUES_1(gensymed_symbol);
    }
    else {
	region_strips = Nil;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = FIX((SI_Long)0L);
	M_CDR(gensymed_symbol) = FIX((SI_Long)0L);
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box_x_interval = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = FIX((SI_Long)0L);
	M_CDR(gensymed_symbol) = FIX((SI_Long)0L);
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box_y_interval = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = region_bounding_box_x_interval;
	M_CDR(gensymed_symbol) = region_bounding_box_y_interval;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = region_strips;
	M_CDR(gensymed_symbol) = region_bounding_box;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	return VALUES_1(gensymed_symbol);
    }
  next:
    goto loop_body;
    return VALUES_1(Qnil);
}

/* SUBTRACT-REGION */
Object subtract_region(region_a,region_b)
    Object region_a, region_b;
{
    Object region_strips_a, region_strips_b, result_top, result_strips;
    Object result_left, result_right, a0, a1, ai, b0, b1, bi, last_bottom_qm;
    Object last_intervals_qm, region_strips_a_old_value, temp, a;
    Object region_strips_b_old_value, b, left, right, ab_loop_list_, left_max;
    Object ab_loop_maxmin_fl_, right_max, ab_loop_maxmin_fl__1;
    Object cantidate_intervals_qm, ab_loopvar_, ab_loopvar__1, ab_loop_desetq_;
    Object interval, temp_1, svref_arg_2, new_cons, svref_new_value;
    Object gensymed_symbol, left_qm, right_qm, region_strips;
    Object region_bounding_box_x_interval, region_bounding_box_y_interval;
    Object region_bounding_box;
    Object result;

    x_note_fn_call(32,192);
    if ( !TRUEP(intersect_region_p_1(region_a,region_b)))
	return copy_region(region_a);
    region_strips_a = M_CAR(region_a);
    region_strips_b = M_CAR(region_b);
    result_top = Nil;
    result_strips = Nil;
    result_left = Nil;
    result_right = Nil;
    a0 = Nil;
    a1 = Nil;
    ai = Nil;
    b0 = Nil;
    b1 = Nil;
    bi = Nil;
    last_bottom_qm = Nil;
    last_intervals_qm = Nil;
    if ( !TRUEP(CDR(region_strips_a)))
	goto finished_a;
    region_strips_a_old_value = region_strips_a;
    temp = FIRST(region_strips_a_old_value);
    region_strips_a = REST(region_strips_a_old_value);
    a = temp;
    ai = CDR(a);
    a0 = CAR(a);
    temp = FIRST(region_strips_a);
    a1 = CAR(temp);
    if ( !TRUEP(CDR(region_strips_b)))
	goto finished_b;
    region_strips_b_old_value = region_strips_b;
    temp = FIRST(region_strips_b_old_value);
    region_strips_b = REST(region_strips_b_old_value);
    b = temp;
    bi = CDR(b);
    b0 = CAR(b);
    temp = FIRST(region_strips_b);
    b1 = CAR(temp);
  loop_body:
    if (FIXNUM_LT(a0,b0)) {
	if (FIXNUM_LT(a1,b0)) {
	    if ( !FIXNUM_EQ(a0,a1)) {
		left = Nil;
		right = Nil;
		ab_loop_list_ = ai;
		left_max = FIX((SI_Long)0L);
		ab_loop_maxmin_fl_ = T;
		right_max = FIX((SI_Long)0L);
		ab_loop_maxmin_fl__1 = T;
		cantidate_intervals_qm = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loop_desetq_ = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		ab_loop_desetq_ = M_CAR(ab_loop_list_);
		left = CAR(ab_loop_desetq_);
		right = CDR(ab_loop_desetq_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ab_loop_maxmin_fl_) {
		    ab_loop_maxmin_fl_ = Nil;
		    left_max = left;
		}
		else
		    left_max = lmin(left_max,left);
		if (ab_loop_maxmin_fl__1) {
		    ab_loop_maxmin_fl__1 = Nil;
		    right_max = right;
		}
		else
		    right_max = lmax(right_max,right);
		ab_loopvar__1 = region_cons_1(region_cons_1(left,right),Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    cantidate_intervals_qm = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
		goto next_loop;
	      end_loop:
		if (cantidate_intervals_qm) {
		    if (last_bottom_qm) {
			result_left = FIXNUM_MIN(result_left,left_max);
			result_right = FIXNUM_MAX(result_right,right_max);
		    }
		    else {
			result_left = left_max;
			result_right = right_max;
			result_top = a0;
		    }
		    if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,a0) && 
			    EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
			interval = Nil;
			ab_loop_list_ = cantidate_intervals_qm;
		      next_loop_1:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_1;
			interval = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			inline_note_reclaim_cons(interval,Qregion);
			if (ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_region_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			else {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			M_CDR(interval) = Nil;
			goto next_loop_1;
		      end_loop_1:
			reclaim_region_list_1(cantidate_intervals_qm);
		    }
		    else {
			if (last_bottom_qm) {
			    if ( !FIXNUM_EQ(last_bottom_qm,a0)) {
				new_cons = 
					ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    temp_1 = Available_region_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(temp_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_region_conses_vector,
					    IFIX(Current_thread_index)))) {
					temp_1 = 
						Available_region_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(temp_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol = new_cons;
				}
				else
				    gensymed_symbol = Nil;
				if ( !TRUEP(gensymed_symbol))
				    gensymed_symbol = 
					    replenish_region_cons_pool();
				M_CAR(gensymed_symbol) = last_bottom_qm;
				M_CDR(gensymed_symbol) = Nil;
				inline_note_allocate_cons(gensymed_symbol,
					Qregion);
				result_strips = 
					region_cons_1(gensymed_symbol,
					result_strips);
			    }
			}
			new_cons = ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = Available_region_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_region_cons_pool();
			M_CAR(gensymed_symbol) = a0;
			M_CDR(gensymed_symbol) = cantidate_intervals_qm;
			inline_note_allocate_cons(gensymed_symbol,Qregion);
			result_strips = region_cons_1(gensymed_symbol,
				result_strips);
			last_intervals_qm = cantidate_intervals_qm;
		    }
		    last_bottom_qm = a1;
		}
	    }
	    goto adv_a;
	}
	else if (FIXNUM_LE(b1,a1)) {
	    if ( !FIXNUM_EQ(a0,b0)) {
		left = Nil;
		right = Nil;
		ab_loop_list_ = ai;
		left_max = FIX((SI_Long)0L);
		ab_loop_maxmin_fl_ = T;
		right_max = FIX((SI_Long)0L);
		ab_loop_maxmin_fl__1 = T;
		cantidate_intervals_qm = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loop_desetq_ = Nil;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		ab_loop_desetq_ = M_CAR(ab_loop_list_);
		left = CAR(ab_loop_desetq_);
		right = CDR(ab_loop_desetq_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ab_loop_maxmin_fl_) {
		    ab_loop_maxmin_fl_ = Nil;
		    left_max = left;
		}
		else
		    left_max = lmin(left_max,left);
		if (ab_loop_maxmin_fl__1) {
		    ab_loop_maxmin_fl__1 = Nil;
		    right_max = right;
		}
		else
		    right_max = lmax(right_max,right);
		ab_loopvar__1 = region_cons_1(region_cons_1(left,right),Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    cantidate_intervals_qm = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
		goto next_loop_2;
	      end_loop_2:
		if (cantidate_intervals_qm) {
		    if (last_bottom_qm) {
			result_left = FIXNUM_MIN(result_left,left_max);
			result_right = FIXNUM_MAX(result_right,right_max);
		    }
		    else {
			result_left = left_max;
			result_right = right_max;
			result_top = a0;
		    }
		    if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,a0) && 
			    EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
			interval = Nil;
			ab_loop_list_ = cantidate_intervals_qm;
		      next_loop_3:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_3;
			interval = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			inline_note_reclaim_cons(interval,Qregion);
			if (ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_region_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			else {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			M_CDR(interval) = Nil;
			goto next_loop_3;
		      end_loop_3:
			reclaim_region_list_1(cantidate_intervals_qm);
		    }
		    else {
			if (last_bottom_qm) {
			    if ( !FIXNUM_EQ(last_bottom_qm,a0)) {
				new_cons = 
					ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    temp_1 = Available_region_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(temp_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_region_conses_vector,
					    IFIX(Current_thread_index)))) {
					temp_1 = 
						Available_region_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(temp_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol = new_cons;
				}
				else
				    gensymed_symbol = Nil;
				if ( !TRUEP(gensymed_symbol))
				    gensymed_symbol = 
					    replenish_region_cons_pool();
				M_CAR(gensymed_symbol) = last_bottom_qm;
				M_CDR(gensymed_symbol) = Nil;
				inline_note_allocate_cons(gensymed_symbol,
					Qregion);
				result_strips = 
					region_cons_1(gensymed_symbol,
					result_strips);
			    }
			}
			new_cons = ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = Available_region_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_region_cons_pool();
			M_CAR(gensymed_symbol) = a0;
			M_CDR(gensymed_symbol) = cantidate_intervals_qm;
			inline_note_allocate_cons(gensymed_symbol,Qregion);
			result_strips = region_cons_1(gensymed_symbol,
				result_strips);
			last_intervals_qm = cantidate_intervals_qm;
		    }
		    last_bottom_qm = b0;
		}
	    }
	    if ( !FIXNUM_EQ(b0,b1)) {
		result = subtract_intervals(ai,bi);
		MVS_3(result,cantidate_intervals_qm,left_qm,right_qm);
		if (cantidate_intervals_qm) {
		    if (last_bottom_qm) {
			result_left = FIXNUM_MIN(result_left,left_qm);
			result_right = FIXNUM_MAX(result_right,right_qm);
		    }
		    else {
			result_left = left_qm;
			result_right = right_qm;
			result_top = b0;
		    }
		    if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,b0) && 
			    EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
			interval = Nil;
			ab_loop_list_ = cantidate_intervals_qm;
		      next_loop_4:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_4;
			interval = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			inline_note_reclaim_cons(interval,Qregion);
			if (ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_region_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			else {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			M_CDR(interval) = Nil;
			goto next_loop_4;
		      end_loop_4:
			reclaim_region_list_1(cantidate_intervals_qm);
		    }
		    else {
			if (last_bottom_qm) {
			    if ( !FIXNUM_EQ(last_bottom_qm,b0)) {
				new_cons = 
					ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    temp_1 = Available_region_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(temp_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_region_conses_vector,
					    IFIX(Current_thread_index)))) {
					temp_1 = 
						Available_region_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(temp_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol = new_cons;
				}
				else
				    gensymed_symbol = Nil;
				if ( !TRUEP(gensymed_symbol))
				    gensymed_symbol = 
					    replenish_region_cons_pool();
				M_CAR(gensymed_symbol) = last_bottom_qm;
				M_CDR(gensymed_symbol) = Nil;
				inline_note_allocate_cons(gensymed_symbol,
					Qregion);
				result_strips = 
					region_cons_1(gensymed_symbol,
					result_strips);
			    }
			}
			new_cons = ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = Available_region_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_region_cons_pool();
			M_CAR(gensymed_symbol) = b0;
			M_CDR(gensymed_symbol) = cantidate_intervals_qm;
			inline_note_allocate_cons(gensymed_symbol,Qregion);
			result_strips = region_cons_1(gensymed_symbol,
				result_strips);
			last_intervals_qm = cantidate_intervals_qm;
		    }
		    last_bottom_qm = b1;
		}
	    }
	    a0 = b1;
	    goto adv_b;
	}
	else if (FIXNUM_LT(a1,b1)) {
	    if ( !FIXNUM_EQ(a0,b0)) {
		left = Nil;
		right = Nil;
		ab_loop_list_ = ai;
		left_max = FIX((SI_Long)0L);
		ab_loop_maxmin_fl_ = T;
		right_max = FIX((SI_Long)0L);
		ab_loop_maxmin_fl__1 = T;
		cantidate_intervals_qm = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loop_desetq_ = Nil;
	      next_loop_5:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_5;
		ab_loop_desetq_ = M_CAR(ab_loop_list_);
		left = CAR(ab_loop_desetq_);
		right = CDR(ab_loop_desetq_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ab_loop_maxmin_fl_) {
		    ab_loop_maxmin_fl_ = Nil;
		    left_max = left;
		}
		else
		    left_max = lmin(left_max,left);
		if (ab_loop_maxmin_fl__1) {
		    ab_loop_maxmin_fl__1 = Nil;
		    right_max = right;
		}
		else
		    right_max = lmax(right_max,right);
		ab_loopvar__1 = region_cons_1(region_cons_1(left,right),Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    cantidate_intervals_qm = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
		goto next_loop_5;
	      end_loop_5:
		if (cantidate_intervals_qm) {
		    if (last_bottom_qm) {
			result_left = FIXNUM_MIN(result_left,left_max);
			result_right = FIXNUM_MAX(result_right,right_max);
		    }
		    else {
			result_left = left_max;
			result_right = right_max;
			result_top = a0;
		    }
		    if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,a0) && 
			    EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
			interval = Nil;
			ab_loop_list_ = cantidate_intervals_qm;
		      next_loop_6:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_6;
			interval = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			inline_note_reclaim_cons(interval,Qregion);
			if (ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_region_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			else {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			M_CDR(interval) = Nil;
			goto next_loop_6;
		      end_loop_6:
			reclaim_region_list_1(cantidate_intervals_qm);
		    }
		    else {
			if (last_bottom_qm) {
			    if ( !FIXNUM_EQ(last_bottom_qm,a0)) {
				new_cons = 
					ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    temp_1 = Available_region_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(temp_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_region_conses_vector,
					    IFIX(Current_thread_index)))) {
					temp_1 = 
						Available_region_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(temp_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol = new_cons;
				}
				else
				    gensymed_symbol = Nil;
				if ( !TRUEP(gensymed_symbol))
				    gensymed_symbol = 
					    replenish_region_cons_pool();
				M_CAR(gensymed_symbol) = last_bottom_qm;
				M_CDR(gensymed_symbol) = Nil;
				inline_note_allocate_cons(gensymed_symbol,
					Qregion);
				result_strips = 
					region_cons_1(gensymed_symbol,
					result_strips);
			    }
			}
			new_cons = ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = Available_region_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_region_cons_pool();
			M_CAR(gensymed_symbol) = a0;
			M_CDR(gensymed_symbol) = cantidate_intervals_qm;
			inline_note_allocate_cons(gensymed_symbol,Qregion);
			result_strips = region_cons_1(gensymed_symbol,
				result_strips);
			last_intervals_qm = cantidate_intervals_qm;
		    }
		    last_bottom_qm = b0;
		}
	    }
	    if ( !FIXNUM_EQ(b0,a1)) {
		result = subtract_intervals(ai,bi);
		MVS_3(result,cantidate_intervals_qm,left_qm,right_qm);
		if (cantidate_intervals_qm) {
		    if (last_bottom_qm) {
			result_left = FIXNUM_MIN(result_left,left_qm);
			result_right = FIXNUM_MAX(result_right,right_qm);
		    }
		    else {
			result_left = left_qm;
			result_right = right_qm;
			result_top = b0;
		    }
		    if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,b0) && 
			    EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
			interval = Nil;
			ab_loop_list_ = cantidate_intervals_qm;
		      next_loop_7:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_7;
			interval = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			inline_note_reclaim_cons(interval,Qregion);
			if (ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_region_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			else {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = interval;
			}
			M_CDR(interval) = Nil;
			goto next_loop_7;
		      end_loop_7:
			reclaim_region_list_1(cantidate_intervals_qm);
		    }
		    else {
			if (last_bottom_qm) {
			    if ( !FIXNUM_EQ(last_bottom_qm,b0)) {
				new_cons = 
					ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    temp_1 = Available_region_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(temp_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_region_conses_vector,
					    IFIX(Current_thread_index)))) {
					temp_1 = 
						Available_region_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(temp_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol = new_cons;
				}
				else
				    gensymed_symbol = Nil;
				if ( !TRUEP(gensymed_symbol))
				    gensymed_symbol = 
					    replenish_region_cons_pool();
				M_CAR(gensymed_symbol) = last_bottom_qm;
				M_CDR(gensymed_symbol) = Nil;
				inline_note_allocate_cons(gensymed_symbol,
					Qregion);
				result_strips = 
					region_cons_1(gensymed_symbol,
					result_strips);
			    }
			}
			new_cons = ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = Available_region_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_region_cons_pool();
			M_CAR(gensymed_symbol) = b0;
			M_CDR(gensymed_symbol) = cantidate_intervals_qm;
			inline_note_allocate_cons(gensymed_symbol,Qregion);
			result_strips = region_cons_1(gensymed_symbol,
				result_strips);
			last_intervals_qm = cantidate_intervals_qm;
		    }
		    last_bottom_qm = a1;
		}
	    }
	    goto adv_a;
	}
    }
    else if (FIXNUM_LT(b1,a0))
	goto adv_b;
    else if (FIXNUM_LE(a1,b1)) {
	if ( !FIXNUM_EQ(a0,a1)) {
	    result = subtract_intervals(ai,bi);
	    MVS_3(result,cantidate_intervals_qm,left_qm,right_qm);
	    if (cantidate_intervals_qm) {
		if (last_bottom_qm) {
		    result_left = FIXNUM_MIN(result_left,left_qm);
		    result_right = FIXNUM_MAX(result_right,right_qm);
		}
		else {
		    result_left = left_qm;
		    result_right = right_qm;
		    result_top = a0;
		}
		if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,a0) && 
			EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
		    interval = Nil;
		    ab_loop_list_ = cantidate_intervals_qm;
		  next_loop_8:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_8;
		    interval = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    inline_note_reclaim_cons(interval,Qregion);
		    if (ISVREF(Available_region_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = interval;
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
		    }
		    else {
			temp_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
		    }
		    M_CDR(interval) = Nil;
		    goto next_loop_8;
		  end_loop_8:
		    reclaim_region_list_1(cantidate_intervals_qm);
		}
		else {
		    if (last_bottom_qm) {
			if ( !FIXNUM_EQ(last_bottom_qm,a0)) {
			    new_cons = 
				    ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_region_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_1,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_region_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = replenish_region_cons_pool();
			    M_CAR(gensymed_symbol) = last_bottom_qm;
			    M_CDR(gensymed_symbol) = Nil;
			    inline_note_allocate_cons(gensymed_symbol,Qregion);
			    result_strips = region_cons_1(gensymed_symbol,
				    result_strips);
			}
		    }
		    new_cons = ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_region_cons_pool();
		    M_CAR(gensymed_symbol) = a0;
		    M_CDR(gensymed_symbol) = cantidate_intervals_qm;
		    inline_note_allocate_cons(gensymed_symbol,Qregion);
		    result_strips = region_cons_1(gensymed_symbol,
			    result_strips);
		    last_intervals_qm = cantidate_intervals_qm;
		}
		last_bottom_qm = a1;
	    }
	}
	goto adv_a;
    }
    else if (FIXNUM_LT(b1,a1)) {
	if ( !FIXNUM_EQ(a0,b1)) {
	    result = subtract_intervals(ai,bi);
	    MVS_3(result,cantidate_intervals_qm,left_qm,right_qm);
	    if (cantidate_intervals_qm) {
		if (last_bottom_qm) {
		    result_left = FIXNUM_MIN(result_left,left_qm);
		    result_right = FIXNUM_MAX(result_right,right_qm);
		}
		else {
		    result_left = left_qm;
		    result_right = right_qm;
		    result_top = a0;
		}
		if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,a0) && 
			EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
		    interval = Nil;
		    ab_loop_list_ = cantidate_intervals_qm;
		  next_loop_9:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_9;
		    interval = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    inline_note_reclaim_cons(interval,Qregion);
		    if (ISVREF(Available_region_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = interval;
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
		    }
		    else {
			temp_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
		    }
		    M_CDR(interval) = Nil;
		    goto next_loop_9;
		  end_loop_9:
		    reclaim_region_list_1(cantidate_intervals_qm);
		}
		else {
		    if (last_bottom_qm) {
			if ( !FIXNUM_EQ(last_bottom_qm,a0)) {
			    new_cons = 
				    ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_region_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_1,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_region_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = replenish_region_cons_pool();
			    M_CAR(gensymed_symbol) = last_bottom_qm;
			    M_CDR(gensymed_symbol) = Nil;
			    inline_note_allocate_cons(gensymed_symbol,Qregion);
			    result_strips = region_cons_1(gensymed_symbol,
				    result_strips);
			}
		    }
		    new_cons = ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_region_cons_pool();
		    M_CAR(gensymed_symbol) = a0;
		    M_CDR(gensymed_symbol) = cantidate_intervals_qm;
		    inline_note_allocate_cons(gensymed_symbol,Qregion);
		    result_strips = region_cons_1(gensymed_symbol,
			    result_strips);
		    last_intervals_qm = cantidate_intervals_qm;
		}
		last_bottom_qm = b1;
	    }
	}
	a0 = b1;
	goto adv_b;
    }
  adv_a:
    if ( !TRUEP(CDR(region_strips_a)))
	goto finished_a;
    region_strips_a_old_value = region_strips_a;
    temp = FIRST(region_strips_a_old_value);
    region_strips_a = REST(region_strips_a_old_value);
    a = temp;
    ai = CDR(a);
    a0 = CAR(a);
    temp = FIRST(region_strips_a);
    a1 = CAR(temp);
    goto next;
  adv_b:
    if ( !TRUEP(CDR(region_strips_b)))
	goto finished_b;
    region_strips_b_old_value = region_strips_b;
    temp = FIRST(region_strips_b_old_value);
    region_strips_b = REST(region_strips_b_old_value);
    b = temp;
    bi = CDR(b);
    b0 = CAR(b);
    temp = FIRST(region_strips_b);
    b1 = CAR(temp);
    goto next;
  finished_b:
    if (FIXNUM_LT(b1,a1)) {
	if ( !FIXNUM_EQ(a0,a1)) {
	    left = Nil;
	    right = Nil;
	    ab_loop_list_ = ai;
	    left_max = FIX((SI_Long)0L);
	    ab_loop_maxmin_fl_ = T;
	    right_max = FIX((SI_Long)0L);
	    ab_loop_maxmin_fl__1 = T;
	    cantidate_intervals_qm = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop_10:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_10;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    left = CAR(ab_loop_desetq_);
	    right = CDR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (ab_loop_maxmin_fl_) {
		ab_loop_maxmin_fl_ = Nil;
		left_max = left;
	    }
	    else
		left_max = lmin(left_max,left);
	    if (ab_loop_maxmin_fl__1) {
		ab_loop_maxmin_fl__1 = Nil;
		right_max = right;
	    }
	    else
		right_max = lmax(right_max,right);
	    ab_loopvar__1 = region_cons_1(region_cons_1(left,right),Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		cantidate_intervals_qm = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop_10;
	  end_loop_10:
	    if (cantidate_intervals_qm) {
		if (last_bottom_qm) {
		    result_left = FIXNUM_MIN(result_left,left_max);
		    result_right = FIXNUM_MAX(result_right,right_max);
		}
		else {
		    result_left = left_max;
		    result_right = right_max;
		    result_top = a0;
		}
		if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,a0) && 
			EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
		    interval = Nil;
		    ab_loop_list_ = cantidate_intervals_qm;
		  next_loop_11:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_11;
		    interval = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    inline_note_reclaim_cons(interval,Qregion);
		    if (ISVREF(Available_region_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_region_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = interval;
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
		    }
		    else {
			temp_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = interval;
		    }
		    M_CDR(interval) = Nil;
		    goto next_loop_11;
		  end_loop_11:
		    reclaim_region_list_1(cantidate_intervals_qm);
		}
		else {
		    if (last_bottom_qm) {
			if ( !FIXNUM_EQ(last_bottom_qm,a0)) {
			    new_cons = 
				    ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_region_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_1,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_region_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_region_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = replenish_region_cons_pool();
			    M_CAR(gensymed_symbol) = last_bottom_qm;
			    M_CDR(gensymed_symbol) = Nil;
			    inline_note_allocate_cons(gensymed_symbol,Qregion);
			    result_strips = region_cons_1(gensymed_symbol,
				    result_strips);
			}
		    }
		    new_cons = ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_region_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_region_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_region_cons_pool();
		    M_CAR(gensymed_symbol) = a0;
		    M_CDR(gensymed_symbol) = cantidate_intervals_qm;
		    inline_note_allocate_cons(gensymed_symbol,Qregion);
		    result_strips = region_cons_1(gensymed_symbol,
			    result_strips);
		    last_intervals_qm = cantidate_intervals_qm;
		}
		last_bottom_qm = a1;
	    }
	}
    }
  next_loop_12:
    if ( !TRUEP(CDR(region_strips_a)))
	goto finished_a;
    region_strips_a_old_value = region_strips_a;
    temp = FIRST(region_strips_a_old_value);
    region_strips_a = REST(region_strips_a_old_value);
    a = temp;
    ai = CDR(a);
    a0 = CAR(a);
    temp = FIRST(region_strips_a);
    a1 = CAR(temp);
    if ( !FIXNUM_EQ(a0,a1)) {
	left = Nil;
	right = Nil;
	ab_loop_list_ = ai;
	left_max = FIX((SI_Long)0L);
	ab_loop_maxmin_fl_ = T;
	right_max = FIX((SI_Long)0L);
	ab_loop_maxmin_fl__1 = T;
	cantidate_intervals_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_13:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_12;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	left = CAR(ab_loop_desetq_);
	right = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (ab_loop_maxmin_fl_) {
	    ab_loop_maxmin_fl_ = Nil;
	    left_max = left;
	}
	else
	    left_max = lmin(left_max,left);
	if (ab_loop_maxmin_fl__1) {
	    ab_loop_maxmin_fl__1 = Nil;
	    right_max = right;
	}
	else
	    right_max = lmax(right_max,right);
	ab_loopvar__1 = region_cons_1(region_cons_1(left,right),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    cantidate_intervals_qm = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_13;
      end_loop_12:
	if (cantidate_intervals_qm) {
	    if (last_bottom_qm) {
		result_left = FIXNUM_MIN(result_left,left_max);
		result_right = FIXNUM_MAX(result_right,right_max);
	    }
	    else {
		result_left = left_max;
		result_right = right_max;
		result_top = a0;
	    }
	    if (last_bottom_qm && FIXNUM_EQ(last_bottom_qm,a0) && 
		    EQUAL(cantidate_intervals_qm,last_intervals_qm)) {
		interval = Nil;
		ab_loop_list_ = cantidate_intervals_qm;
	      next_loop_14:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_13;
		interval = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		inline_note_reclaim_cons(interval,Qregion);
		if (ISVREF(Available_region_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_region_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = interval;
		    temp_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = interval;
		}
		else {
		    temp_1 = Available_region_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = interval;
		    temp_1 = Available_region_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = interval;
		}
		M_CDR(interval) = Nil;
		goto next_loop_14;
	      end_loop_13:
		reclaim_region_list_1(cantidate_intervals_qm);
	    }
	    else {
		if (last_bottom_qm) {
		    if ( !FIXNUM_EQ(last_bottom_qm,a0)) {
			new_cons = ISVREF(Available_region_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_region_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_region_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = Available_region_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_region_cons_pool();
			M_CAR(gensymed_symbol) = last_bottom_qm;
			M_CDR(gensymed_symbol) = Nil;
			inline_note_allocate_cons(gensymed_symbol,Qregion);
			result_strips = region_cons_1(gensymed_symbol,
				result_strips);
		    }
		}
		new_cons = ISVREF(Available_region_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_1 = Available_region_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_region_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_1 = Available_region_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_region_cons_pool();
		M_CAR(gensymed_symbol) = a0;
		M_CDR(gensymed_symbol) = cantidate_intervals_qm;
		inline_note_allocate_cons(gensymed_symbol,Qregion);
		result_strips = region_cons_1(gensymed_symbol,result_strips);
		last_intervals_qm = cantidate_intervals_qm;
	    }
	    last_bottom_qm = a1;
	}
    }
    goto next_loop_12;
  end_loop_14:;
  finished_a:
    if (last_bottom_qm) {
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = last_bottom_qm;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	result_strips = region_cons_1(gensymed_symbol,result_strips);
	region_strips = nreverse(result_strips);
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = result_left;
	M_CDR(gensymed_symbol) = result_right;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box_x_interval = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = result_top;
	M_CDR(gensymed_symbol) = last_bottom_qm;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box_y_interval = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = region_bounding_box_x_interval;
	M_CDR(gensymed_symbol) = region_bounding_box_y_interval;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = region_strips;
	M_CDR(gensymed_symbol) = region_bounding_box;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	return VALUES_1(gensymed_symbol);
    }
    else {
	region_strips = Nil;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = FIX((SI_Long)0L);
	M_CDR(gensymed_symbol) = FIX((SI_Long)0L);
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box_x_interval = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = FIX((SI_Long)0L);
	M_CDR(gensymed_symbol) = FIX((SI_Long)0L);
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box_y_interval = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = region_bounding_box_x_interval;
	M_CDR(gensymed_symbol) = region_bounding_box_y_interval;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	region_bounding_box = gensymed_symbol;
	new_cons = ISVREF(Available_region_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_region_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_region_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_region_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_region_cons_pool();
	M_CAR(gensymed_symbol) = region_strips;
	M_CDR(gensymed_symbol) = region_bounding_box;
	inline_note_allocate_cons(gensymed_symbol,Qregion);
	return VALUES_1(gensymed_symbol);
    }
  next:
    goto loop_body;
    return VALUES_1(Qnil);
}

/* TRANSFORM-REGION-IN-PLACE */
Object transform_region_in_place(region,x_transform,y_transform)
    Object region, x_transform, y_transform;
{
    Object tail, strip, temp, tail_1, interval, box;

    x_note_fn_call(32,193);
    tail = M_CAR(region);
    strip = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	strip = CAR(tail);
	temp = FUNCALL_1(y_transform,CAR(strip));
	M_CAR(strip) = temp;
	tail_1 = CDR(strip);
	interval = Nil;
	for ( ; !ENDP(tail_1); tail_1 = CDR(tail_1)) {
	    interval = CAR(tail_1);
	    temp = FUNCALL_1(x_transform,M_CAR(interval));
	    M_CAR(interval) = temp;
	    temp = FUNCALL_1(x_transform,M_CDR(interval));
	    M_CDR(interval) = temp;
	}
    }
    box = M_CDR(region);
    interval = M_CAR(box);
    temp = FUNCALL_1(x_transform,M_CAR(interval));
    M_CAR(interval) = temp;
    temp = FUNCALL_1(x_transform,M_CDR(interval));
    M_CDR(interval) = temp;
    interval = M_CDR(box);
    temp = FUNCALL_1(y_transform,M_CAR(interval));
    M_CAR(interval) = temp;
    temp = FUNCALL_1(y_transform,M_CDR(interval));
    M_CDR(interval) = temp;
    return VALUES_1(region);
}

/* NUMBER-OF-RECTANGLES-IN-REGION */
Object number_of_rectangles_in_region(region)
    Object region;
{
    Object sum, region_strip, top, bottom, region_strip_1;
    Object remaining_region_strips, ab_loop_list_, region_strip_2, a, b, left;
    Object right, ab_loop_list__1, ab_loop_desetq_;

    x_note_fn_call(32,194);
    sum = FIX((SI_Long)0L);
    region_strip = Nil;
    top = Nil;
    bottom = Nil;
    region_strip_1 = Nil;
    remaining_region_strips = Nil;
    ab_loop_list_ = M_CAR(region);
    region_strip_2 = Nil;
    a = Nil;
    b = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    region_strip_1 = CAR(ab_loop_list_);
    remaining_region_strips = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(remaining_region_strips))
	goto end_loop;
    region_strip_2 = FIRST(remaining_region_strips);
    a = CAR(region_strip_1);
    b = CAR(region_strip_2);
    if ( !FIXNUM_EQ(a,b)) {
	top = a;
	bottom = b;
	region_strip = region_strip_1;
	left = Nil;
	right = Nil;
	ab_loop_list__1 = CDR(region_strip);
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	left = CAR(ab_loop_desetq_);
	right = CDR(ab_loop_desetq_);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !FIXNUM_EQ(left,right))
	    sum = FIXNUM_ADD1(sum);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(sum);
}

/* EXACTLY-ONE-RECTANGLE-IN-REGION-P */
Object exactly_one_rectangle_in_region_p(region)
    Object region;
{
    Object sum, region_strip, top, bottom, region_strip_1;
    Object remaining_region_strips, ab_loop_list_, region_strip_2, a, b, left;
    Object right, ab_loop_list__1, ab_loop_desetq_;

    x_note_fn_call(32,195);
    sum = FIX((SI_Long)0L);
    region_strip = Nil;
    top = Nil;
    bottom = Nil;
    region_strip_1 = Nil;
    remaining_region_strips = Nil;
    ab_loop_list_ = M_CAR(region);
    region_strip_2 = Nil;
    a = Nil;
    b = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    region_strip_1 = CAR(ab_loop_list_);
    remaining_region_strips = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(remaining_region_strips))
	goto end_loop;
    region_strip_2 = FIRST(remaining_region_strips);
    a = CAR(region_strip_1);
    b = CAR(region_strip_2);
    if ( !FIXNUM_EQ(a,b)) {
	top = a;
	bottom = b;
	region_strip = region_strip_1;
	left = Nil;
	right = Nil;
	ab_loop_list__1 = CDR(region_strip);
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	left = CAR(ab_loop_desetq_);
	right = CDR(ab_loop_desetq_);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !FIXNUM_EQ(left,right)) {
	    sum = FIXNUM_ADD1(sum);
	    if (IFIX(sum) >= (SI_Long)2L)
		goto end_count;
	}
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
  end_count:
    return VALUES_1(IFIX(sum) == (SI_Long)1L ? T : Nil);
}

/* SPLIT-SYMBOL */
Object split_symbol(symbol,delimiter)
    Object symbol, delimiter;
{
    Object string_1, end_1, i, j, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object character_1, start, temp, substring;
    SI_Long i_1, ab_loop_bind_;

    x_note_fn_call(32,196);
    string_1 = SYMBOL_NAME(symbol);
    end_1 = length(string_1);
    i = FIX((SI_Long)0L);
    j = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !FIXNUM_LT(i,end_1))
	goto end_loop;
    character_1 = delimiter;
    start = FIXNUM_ADD1(i);
    i_1 = IFIX(start);
    ab_loop_bind_ = IFIX(length(string_1));
  next_loop_1:
    if (i_1 >= ab_loop_bind_)
	goto end_loop_1;
    temp = CHR(ICHAR(string_1,i_1));
    if (CHAR_EQUAL(character_1,temp)) {
	temp = FIX(i_1);
	goto end_2;
    }
    i_1 = i_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    temp = Qnil;
  end_2:;
    if (temp);
    else
	temp = end_1;
    j = temp;
    if (FIXNUM_NE(i,j)) {
	substring = gensym_string_substring(string_1,i,j);
	ab_loopvar__2 = gensym_cons_1(intern_gensym_string(2,substring,
		Ab_package_1),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    i = FIXNUM_ADD1(j);
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

Object The_type_description_of_pending_activity = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_pending_activitys, Qchain_of_available_pending_activitys);

DEFINE_VARIABLE_WITH_SYMBOL(Pending_activity_count, Qpending_activity_count);

Object Chain_of_available_pending_activitys_vector = UNBOUND;

/* PENDING-ACTIVITY-STRUCTURE-MEMORY-USAGE */
Object pending_activity_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(32,197);
    temp = Pending_activity_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PENDING-ACTIVITY-COUNT */
Object outstanding_pending_activity_count()
{
    Object def_structure_pending_activity_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(32,198);
    gensymed_symbol = IFIX(Pending_activity_count);
    def_structure_pending_activity_variable = 
	    Chain_of_available_pending_activitys;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_pending_activity_variable))
	goto end_loop;
    def_structure_pending_activity_variable = 
	    ISVREF(def_structure_pending_activity_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PENDING-ACTIVITY-1 */
Object reclaim_pending_activity_1(pending_activity)
    Object pending_activity;
{
    Object temp, svref_arg_2;

    x_note_fn_call(32,199);
    inline_note_reclaim_cons(pending_activity,Nil);
    temp = ISVREF(Chain_of_available_pending_activitys_vector,
	    IFIX(Current_thread_index));
    SVREF(pending_activity,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_pending_activitys_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = pending_activity;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PENDING-ACTIVITY */
Object reclaim_structure_for_pending_activity(pending_activity)
    Object pending_activity;
{
    x_note_fn_call(32,200);
    return reclaim_pending_activity_1(pending_activity);
}

static Object Qg2_defstruct_structure_name_pending_activity_g2_struct;  /* g2-defstruct-structure-name::pending-activity-g2-struct */

/* MAKE-PERMANENT-PENDING-ACTIVITY-STRUCTURE-INTERNAL */
Object make_permanent_pending_activity_structure_internal()
{
    Object def_structure_pending_activity_variable;
    Object defstruct_g2_pending_activity_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(32,201);
    def_structure_pending_activity_variable = Nil;
    atomic_incff_symval(Qpending_activity_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_pending_activity_variable = Nil;
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
	defstruct_g2_pending_activity_variable = the_array;
	SVREF(defstruct_g2_pending_activity_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pending_activity_g2_struct;
	def_structure_pending_activity_variable = 
		defstruct_g2_pending_activity_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_pending_activity_variable);
}

/* MAKE-PENDING-ACTIVITY-1 */
Object make_pending_activity_1(parent_of_pending_activity_qm,
	    name_of_pending_activity,continuation_of_pending_activity_qm)
    Object parent_of_pending_activity_qm, name_of_pending_activity;
    Object continuation_of_pending_activity_qm;
{
    Object def_structure_pending_activity_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,202);
    def_structure_pending_activity_variable = 
	    ISVREF(Chain_of_available_pending_activitys_vector,
	    IFIX(Current_thread_index));
    if (def_structure_pending_activity_variable) {
	svref_arg_1 = Chain_of_available_pending_activitys_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_pending_activity_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_pending_activity_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pending_activity_g2_struct;
    }
    else
	def_structure_pending_activity_variable = 
		make_permanent_pending_activity_structure_internal();
    inline_note_allocate_cons(def_structure_pending_activity_variable,Nil);
    SVREF(def_structure_pending_activity_variable,FIX((SI_Long)2L)) = 
	    parent_of_pending_activity_qm;
    SVREF(def_structure_pending_activity_variable,FIX((SI_Long)1L)) = 
	    name_of_pending_activity;
    SVREF(def_structure_pending_activity_variable,FIX((SI_Long)5L)) = 
	    continuation_of_pending_activity_qm;
    SVREF(def_structure_pending_activity_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_pending_activity_variable,FIX((SI_Long)4L)) = T;
    return VALUES_1(def_structure_pending_activity_variable);
}

/* BLOCK-PENDING-ACTIVITY */
Object block_pending_activity(parent_activity,child_activity)
    Object parent_activity, child_activity;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(32,203);
    gensym_push_modify_macro_arg = child_activity;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(parent_activity,(SI_Long)3L);
    svref_new_value = gensym_cons_1(car_1,cdr_1);
    SVREF(parent_activity,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(child_activity);
}

static Object Kfinished;           /* :finished */

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* FINISH-PENDING-ACTIVITY */
Object finish_pending_activity(pending_activity)
    Object pending_activity;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, parent_qm;
    Object svref_new_value;

    x_note_fn_call(32,204);
    if (ISVREF(pending_activity,(SI_Long)5L)) {
	gensymed_symbol = ISVREF(pending_activity,(SI_Long)5L);
	gensymed_symbol_1 = pending_activity;
	gensymed_symbol_2 = Kfinished;
	inline_funcall_2(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2);
    }
    parent_qm = ISVREF(pending_activity,(SI_Long)2L);
    if (parent_qm) {
	svref_new_value = delete_gensym_element_1(pending_activity,
		ISVREF(parent_qm,(SI_Long)3L));
	SVREF(parent_qm,FIX((SI_Long)3L)) = svref_new_value;
	if ( !TRUEP(ISVREF(parent_qm,(SI_Long)3L)))
	    finish_pending_activity(parent_qm);
    }
    gensymed_symbol = ISVREF(pending_activity,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = pending_activity;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(Nil);
}

/* CANCEL-PENDING-ACTIVITY */
Object cancel_pending_activity(pending_activity)
    Object pending_activity;
{
    x_note_fn_call(32,205);
    cancel_pending_activity_1(pending_activity);
    return VALUES_1(Nil);
}

static Object Kcanceled;           /* :canceled */

/* CANCEL-PENDING-ACTIVITY-1 */
Object cancel_pending_activity_1(pending_activity)
    Object pending_activity;
{
    Object child, ab_loop_list_, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2;

    x_note_fn_call(32,206);
    child = Nil;
    ab_loop_list_ = ISVREF(pending_activity,(SI_Long)3L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    child = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    SVREF(child,FIX((SI_Long)2L)) = Nil;
    cancel_pending_activity_1(child);
    goto next_loop;
  end_loop:;
    if (ISVREF(pending_activity,(SI_Long)5L)) {
	gensymed_symbol = ISVREF(pending_activity,(SI_Long)5L);
	gensymed_symbol_1 = pending_activity;
	gensymed_symbol_2 = Kcanceled;
	inline_funcall_2(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2);
    }
    gensymed_symbol = ISVREF(pending_activity,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = pending_activity;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* CANCEL-IDENTIFIED-DRAWING-ACTIVITY-IF-ANY */
Object cancel_identified_drawing_activity_if_any(pending_activity_qm)
    Object pending_activity_qm;
{
    x_note_fn_call(32,207);
    if (pending_activity_qm)
	return cancel_pending_activity(pending_activity_qm);
    else
	return VALUES_1(Nil);
}

/* CANCEL-LIST-OF-PENDING-ACTIVITY */
Object cancel_list_of_pending_activity(list_of_pending_activities)
    Object list_of_pending_activities;
{
    Object pending_activity, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, parents_1, parent_1;

    x_note_fn_call(32,208);
    pending_activity = Nil;
    ab_loop_list_ = list_of_pending_activities;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pending_activity = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(pending_activity,(SI_Long)2L)) {
	ab_loopvar__2 = gensym_cons_1(pending_activity,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    parents_1 = ab_loopvar_;
    goto end_1;
    parents_1 = Qnil;
  end_1:;
    parent_1 = Nil;
    ab_loop_list_ = parents_1;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    parent_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    cancel_pending_activity(parent_1);
    goto next_loop_1;
  end_loop_1:
    reclaim_gensym_list_1(list_of_pending_activities);
    reclaim_gensym_list_1(parents_1);
    return VALUES_1(Qnil);
}

/* TEXT-STRING-SEARCH-SIMPLE */
Object text_string_search_simple(text_string1,text_string2)
    Object text_string1, text_string2;
{
    Object text_string1_length, text_string2_length, ab_loop_it_;
    SI_Long text_string2_index, ab_loop_bind_, text_string1_index;
    SI_Long ab_loop_bind__1;
    char temp;

    x_note_fn_call(32,209);
    text_string1_length = text_string_length(text_string1);
    text_string2_length = text_string_length(text_string2);
    if (FIXNUM_GT(text_string1_length,text_string2_length))
	return VALUES_1(Nil);
    else {
	text_string2_index = (SI_Long)0L;
	ab_loop_bind_ = IFIX(FIXNUM_MINUS(text_string2_length,
		text_string1_length));
	ab_loop_it_ = Nil;
      next_loop:
	if (text_string2_index > ab_loop_bind_)
	    goto end_loop;
	text_string1_index = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(text_string1_length);
      next_loop_1:
	if (text_string1_index >= ab_loop_bind__1)
	    goto end_loop_1;
	if ( !(UBYTE_16_ISAREF_1(text_string1,text_string1_index) == 
		UBYTE_16_ISAREF_1(text_string2,text_string1_index + 
		text_string2_index))) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	text_string1_index = text_string1_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
	ab_loop_it_ = temp ? FIX(text_string2_index) : Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	text_string2_index = text_string2_index + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* TEXT-STRING-SEARCH-COMPLEX */
Object text_string_search_complex(text_string1,text_string2,from_end,test,
	    test_not,key,start1,start2,end1,end2)
    Object text_string1, text_string2, from_end, test, test_not, key, start1;
    Object start2, end1, end2;
{
    Object span1, ab_loop_it_, raw_element1, raw_element2, element1, element2;
    SI_Long text_string2_index, ab_loop_bind_, text_string1_index;
    SI_Long ab_loop_bind__1;
    char temp;

    x_note_fn_call(32,210);
    if ( !TRUEP(end1))
	end1 = text_string_length(text_string1);
    if ( !TRUEP(end2))
	end2 = text_string_length(text_string2);
    span1 = FIXNUM_MINUS(end1,start1);
    if (FIXNUM_GT(span1,FIXNUM_MINUS(end2,start2)))
	return VALUES_1(Nil);
    else if (from_end) {
	text_string2_index = IFIX(FIXNUM_MINUS(end2,span1));
	ab_loop_bind_ = IFIX(start2);
	ab_loop_it_ = Nil;
      next_loop:
	if (text_string2_index < ab_loop_bind_)
	    goto end_loop;
	text_string1_index = IFIX(start1);
	ab_loop_bind__1 = IFIX(end1);
	raw_element1 = Nil;
	raw_element2 = Nil;
	element1 = Nil;
	element2 = Nil;
      next_loop_1:
	if (text_string1_index >= ab_loop_bind__1)
	    goto end_loop_1;
	raw_element1 = FIX(UBYTE_16_ISAREF_1(text_string1,text_string1_index));
	raw_element2 = FIX(UBYTE_16_ISAREF_1(text_string2,
		text_string1_index + text_string2_index));
	element1 = key ? FUNCALL_1(key,raw_element1) : raw_element1;
	element2 = key ? FUNCALL_1(key,raw_element2) : raw_element2;
	if ( !(test ? TRUEP(FUNCALL_2(test,element1,element2)) : TRUEP(T))) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	if (test_not && FUNCALL_2(test_not,element1,element2)) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	text_string1_index = text_string1_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
	ab_loop_it_ = temp ? FIX(text_string2_index) : Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	text_string2_index = text_string2_index - (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	text_string2_index = IFIX(start2);
	ab_loop_bind_ = IFIX(FIXNUM_MINUS(end2,span1));
	ab_loop_it_ = Nil;
      next_loop_2:
	if (text_string2_index > ab_loop_bind_)
	    goto end_loop_2;
	text_string1_index = IFIX(start1);
	ab_loop_bind__1 = IFIX(end1);
	raw_element1 = Nil;
	raw_element2 = Nil;
	element1 = Nil;
	element2 = Nil;
      next_loop_3:
	if (text_string1_index >= ab_loop_bind__1)
	    goto end_loop_3;
	raw_element1 = FIX(UBYTE_16_ISAREF_1(text_string1,text_string1_index));
	raw_element2 = FIX(UBYTE_16_ISAREF_1(text_string2,
		text_string1_index + text_string2_index));
	element1 = key ? FUNCALL_1(key,raw_element1) : raw_element1;
	element2 = key ? FUNCALL_1(key,raw_element2) : raw_element2;
	if ( !(test ? TRUEP(FUNCALL_2(test,element1,element2)) : TRUEP(T))) {
	    temp = TRUEP(Nil);
	    goto end_2;
	}
	if (test_not && FUNCALL_2(test_not,element1,element2)) {
	    temp = TRUEP(Nil);
	    goto end_2;
	}
	text_string1_index = text_string1_index + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:
	temp = TRUEP(T);
	goto end_2;
	temp = TRUEP(T);
	goto end_2;
	temp = TRUEP(Qnil);
      end_2:;
	ab_loop_it_ = temp ? FIX(text_string2_index) : Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	text_string2_index = text_string2_index + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
}

/* TEXT-STRING=-GIVEN-INDICES */
Object text_string_eq_given_indices(string1,string2,start1,end1,start2,end2)
    Object string1, string2, start1, end1, start2, end2;
{
    Object ab_loop_iter_flag_;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;

    x_note_fn_call(32,211);
    length1 = IFIX(FIXNUM_MINUS(end1,start1));
    length2 = IFIX(FIXNUM_MINUS(end2,start2));
    if (length1 != length2)
	return VALUES_1(Nil);
    else {
	index1 = IFIX(start1);
	ab_loop_bind_ = IFIX(end1);
	index2 = IFIX(start2);
	ab_loop_bind__1 = IFIX(end2);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (index1 >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index2 = index2 + (SI_Long)1L;
	if (index2 >= ab_loop_bind__1)
	    goto end_loop;
	if ( !(UBYTE_16_ISAREF_1(string1,index1) == 
		UBYTE_16_ISAREF_1(string2,index2)))
	    return VALUES_1(Nil);
	ab_loop_iter_flag_ = Nil;
	index1 = index1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
}

/* TEXT-STRING-EQUAL-GIVEN-INDICES */
Object text_string_equal_given_indices(string1,string2,start1,end1,start2,end2)
    Object string1, string2, start1, end1, start2, end2;
{
    Object ab_loop_iter_flag_, temp, temp_1;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    SI_Long code;

    x_note_fn_call(32,212);
    length1 = IFIX(FIXNUM_MINUS(end1,start1));
    length2 = IFIX(FIXNUM_MINUS(end2,start2));
    if (length1 != length2)
	return VALUES_1(Nil);
    else {
	index1 = IFIX(start1);
	ab_loop_bind_ = IFIX(end1);
	index2 = IFIX(start2);
	ab_loop_bind__1 = IFIX(end2);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (index1 >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index2 = index2 + (SI_Long)1L;
	if (index2 >= ab_loop_bind__1)
	    goto end_loop;
	code = UBYTE_16_ISAREF_1(string1,index1);
	if (code < (SI_Long)127L)
	    temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? FIX(code 
		    + (SI_Long)32L) : FIX(code);
	else {
	    temp = unicode_lowercase_if_uppercase(FIX(code));
	    if (temp);
	    else
		temp = FIX(code);
	}
	code = UBYTE_16_ISAREF_1(string2,index2);
	if (code < (SI_Long)127L)
	    temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
		    FIX(code + (SI_Long)32L) : FIX(code);
	else {
	    temp_1 = unicode_lowercase_if_uppercase(FIX(code));
	    if (temp_1);
	    else
		temp_1 = FIX(code);
	}
	if ( !NUM_EQ(temp,temp_1))
	    return VALUES_1(Nil);
	ab_loop_iter_flag_ = Nil;
	index1 = index1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
}

/* TEXT-STRING-PARSE-INTEGER-FUNCTION */
Object text_string_parse_integer_function(string_1,start,end_1,junk_allowed)
    Object string_1, start, end_1, junk_allowed;
{
    Object length_1, accum, parsing_started_p, this_char, this_digit_qm, temp;
    SI_Long index_1, ab_loop_bind_, index2;
    char temp_1;

    x_note_fn_call(32,213);
    length_1 = text_string_length(string_1);
    if ( !TRUEP(end_1))
	end_1 = length_1;
    if (IFIX(start) < (SI_Long)0L || IFIX(end_1) < (SI_Long)0L || 
	    FIXNUM_GT(start,length_1) || FIXNUM_GT(end_1,length_1) || 
	    FIXNUM_GT(start,end_1))
	return VALUES_1(Nil);
    else {
	index_1 = IFIX(start);
	ab_loop_bind_ = IFIX(end_1);
	accum = FIX((SI_Long)0L);
	parsing_started_p = Nil;
	this_char = Nil;
	this_digit_qm = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	this_char = FIX(UBYTE_16_ISAREF_1(string_1,index_1));
	temp = this_char;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    this_digit_qm = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 48:
		this_digit_qm = FIX((SI_Long)0L);
		break;
	      case 49:
		this_digit_qm = FIX((SI_Long)1L);
		break;
	      case 50:
		this_digit_qm = FIX((SI_Long)2L);
		break;
	      case 51:
		this_digit_qm = FIX((SI_Long)3L);
		break;
	      case 52:
		this_digit_qm = FIX((SI_Long)4L);
		break;
	      case 53:
		this_digit_qm = FIX((SI_Long)5L);
		break;
	      case 54:
		this_digit_qm = FIX((SI_Long)6L);
		break;
	      case 55:
		this_digit_qm = FIX((SI_Long)7L);
		break;
	      case 56:
		this_digit_qm = FIX((SI_Long)8L);
		break;
	      case 57:
		this_digit_qm = FIX((SI_Long)9L);
		break;
	      default:
		this_digit_qm = Nil;
		break;
	    }
	if ( !TRUEP(parsing_started_p) && this_digit_qm)
	    parsing_started_p = T;
	if (blank_p(this_char)) {
	    if (parsing_started_p && junk_allowed)
		return VALUES_2(accum,FIX(index_1 + (SI_Long)1L));
	    else if (parsing_started_p) {
		index2 = index_1;
		ab_loop_bind_ = IFIX(end_1);
		this_char = Nil;
	      next_loop_1:
		if (index2 >= ab_loop_bind_)
		    goto end_loop_1;
		this_char = FIX(UBYTE_16_ISAREF_1(string_1,index2));
		if ( !TRUEP(blank_p(this_char))) {
		    temp_1 = TRUEP(Nil);
		    goto end_2;
		}
		index2 = index2 + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:
		temp_1 = TRUEP(T);
		goto end_2;
		temp_1 = TRUEP(Qnil);
	      end_2:;
		if (temp_1)
		    return VALUES_2(accum,FIX(index_1 + (SI_Long)1L));
		else
		    return VALUES_2(Nil,Nil);
	    }
	}
	else if (this_digit_qm)
	    accum = FIX(IFIX(accum) * (SI_Long)10L + IFIX(this_digit_qm));
	else if (junk_allowed && parsing_started_p)
	    return VALUES_2(accum,FIX(index_1 + (SI_Long)1L));
	else if (junk_allowed);
	else
	    return VALUES_2(Nil,Nil);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_2(accum,FIX(index_1));
	return VALUES_1(Qnil);
    }
}

/* TEXT-STRING-PARSE-SYMBOL-FUNCTION */
Object text_string_parse_symbol_function(text_string,start,end_1)
    Object text_string, start, end_1;
{
    Object length_1, text_for_symbol, end_index, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object parsing_started_p, this_char, thing, temp, schar_arg_2;
    Object schar_new_value, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_2, index_1;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(32,214);
    length_1 = text_string_length(text_string);
    text_for_symbol = Nil;
    end_index = Nil;
    if ( !TRUEP(end_1))
	end_1 = length_1;
    if (IFIX(start) < (SI_Long)0L || IFIX(end_1) < (SI_Long)0L || 
	    FIXNUM_GT(start,length_1) || FIXNUM_GT(end_1,length_1) || 
	    FIXNUM_GT(start,end_1))
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
		  index_1 = IFIX(start);
		  ab_loop_bind_ = IFIX(end_1);
		  parsing_started_p = Nil;
		  this_char = Nil;
		next_loop:
		  if (index_1 >= ab_loop_bind_)
		      goto end_loop;
		  this_char = FIX(UBYTE_16_ISAREF_1(text_string,index_1));
		  if ( !TRUEP(parsing_started_p) &&  
			  !TRUEP(blank_p(this_char)))
		      parsing_started_p = T;
		  if (blank_p(this_char)) {
		      end_index = FIX(index_1 + (SI_Long)1L);
		      goto end_2;
		  }
		  else if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = this_char;
		      twrite_wide_character(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = this_char;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  index_1 = index_1 + (SI_Long)1L;
		  goto next_loop;
		end_loop:
		  end_index = FIX(index_1);
		end_2:;
		  text_for_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	nstring_upcasew(text_for_symbol);
	temp_1 = intern_text_string(1,text_for_symbol);
	return VALUES_2(temp_1,end_index);
    }
}

/* COMMAND-LINE-TOKEN-EQUAL-GIVEN-INDICES */
Object command_line_token_equal_given_indices(token1,token2,start1,end1,
	    start2,end2)
    Object token1, token2, start1, end1, start2, end2;
{
    x_note_fn_call(32,215);
    if (EQ(G2_machine_type,Qvms))
	return text_string_equal_given_indices(token1,token2,start1,end1,
		start2,end2);
    else
	return text_string_eq_given_indices(token1,token2,start1,end1,
		start2,end2);
}

static Object array_constant_6;    /* # */

/* COMMAND-LINE-KEYWORD-P */
Object command_line_keyword_p(keyword_as_text_string)
    Object keyword_as_text_string;
{
    x_note_fn_call(32,216);
    return text_string_equal_given_indices(keyword_as_text_string,
	    array_constant_6,FIX((SI_Long)0L),FIX((SI_Long)1L),
	    FIX((SI_Long)0L),FIX((SI_Long)1L));
}

/* GET-COMMAND-LINE-KEYWORD-ARGUMENT */
Object get_command_line_keyword_argument varargs_1(int, n)
{
    Object keyword;
    Object keyword_instance_number, no_import_p, keyword_as_text_string;
    Object matching_keyword_instance, arg_qm, temp, temp_1;
    SI_Long keyword_comparison_start_index, i;
    char temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,217);
    INIT_ARGS_nonrelocating();
    keyword = REQUIRED_ARG_nonrelocating();
    keyword_instance_number = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)1L);
    no_import_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    keyword_as_text_string = copy_text_string(keyword);
    keyword_comparison_start_index = 
	    command_line_keyword_p(keyword_as_text_string) ? (SI_Long)1L : 
	    (SI_Long)0L;
    matching_keyword_instance = FIX((SI_Long)0L);
    i = (SI_Long)1L;
    arg_qm = Nil;
  next_loop:
    arg_qm = get_gensym_command_line_argument_as_text_string(FIX(i));
    if ( !TRUEP(arg_qm))
	goto end_loop;
    if (command_line_keyword_p(arg_qm)) {
	temp = arg_qm;
	temp_1 = text_string_length(arg_qm);
	if (text_string_equal_given_indices(temp,keyword_as_text_string,
		FIX((SI_Long)1L),temp_1,
		FIX(keyword_comparison_start_index),
		text_string_length(keyword_as_text_string))) {
	    matching_keyword_instance = FIXNUM_ADD1(matching_keyword_instance);
	    temp_2 = TRUEP(matching_keyword_instance);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2 ? FIXNUM_EQ(matching_keyword_instance,
	    keyword_instance_number) : TRUEP(Nil)) {
	temp = no_import_p ? get_gensym_command_line_argument(FIX(i + 
		(SI_Long)1L)) : 
		get_gensym_command_line_argument_as_text_string(FIX(i + 
		(SI_Long)1L));
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    reclaim_text_string(keyword_as_text_string);
    return VALUES_1(temp);
}

/* GET-COMMAND-LINE-KEYWORD-ARGUMENT-AS-INTEGER */
Object get_command_line_keyword_argument_as_integer varargs_1(int, n)
{
    Object keyword;
    Object keyword_instance_number_qm, arg_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,218);
    INIT_ARGS_nonrelocating();
    keyword = REQUIRED_ARG_nonrelocating();
    keyword_instance_number_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)1L);
    END_ARGS_nonrelocating();
    arg_qm = get_command_line_keyword_argument(2,keyword,
	    keyword_instance_number_qm);
    if (arg_qm)
	return text_string_parse_integer_function(arg_qm,FIX((SI_Long)0L),
		Nil,T);
    else
	return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-KEYWORD-ARGUMENT-AS-MEMORY-SIZE */
Object get_command_line_keyword_argument_as_memory_size varargs_1(int, n)
{
    Object keyword;
    Object keyword_instance_number_qm, arg_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,219);
    INIT_ARGS_nonrelocating();
    keyword = REQUIRED_ARG_nonrelocating();
    keyword_instance_number_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)1L);
    END_ARGS_nonrelocating();
    arg_qm = get_command_line_keyword_argument(2,keyword,
	    keyword_instance_number_qm);
    if (arg_qm)
	return read_memory_size_from_string(arg_qm);
    else
	return VALUES_1(Nil);
}

/* READ-MEMORY-SIZE-FROM-STRING */
Object read_memory_size_from_string(string_1)
    Object string_1;
{
    x_note_fn_call(32,220);
    return l_abs(read_float_from_string(string_1,FIX((SI_Long)0L),
	    length(string_1)));
}

/* GET-COMMAND-LINE-FLAG-ARGUMENT */
Object get_command_line_flag_argument varargs_1(int, n)
{
    Object flag;
    Object require_hyphen_qm, flag_as_text_string, arg_qm, temp, temp_1;
    SI_Long flag_comparison_start_index, i;
    char temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,221);
    INIT_ARGS_nonrelocating();
    flag = REQUIRED_ARG_nonrelocating();
    require_hyphen_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    flag_as_text_string = copy_text_string(flag);
    flag_comparison_start_index = 
	    command_line_keyword_p(flag_as_text_string) ? (SI_Long)1L : 
	    (SI_Long)0L;
    i = (SI_Long)1L;
    arg_qm = Nil;
  next_loop:
    arg_qm = get_gensym_command_line_argument_as_text_string(FIX(i));
    if ( !TRUEP(arg_qm))
	goto end_loop;
    if ( !TRUEP(command_line_keyword_p(arg_qm))) {
	if ( !TRUEP(require_hyphen_qm)) {
	    temp = arg_qm;
	    temp_1 = text_string_length(arg_qm);
	    temp_2 = TRUEP(text_string_equal_given_indices(temp,
		    flag_as_text_string,FIX((SI_Long)0L),temp_1,
		    FIX(flag_comparison_start_index),
		    text_string_length(flag_as_text_string)));
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else {
	temp = arg_qm;
	temp_1 = text_string_length(arg_qm);
	temp_2 = TRUEP(text_string_equal_given_indices(temp,
		flag_as_text_string,FIX((SI_Long)1L),temp_1,
		FIX(flag_comparison_start_index),
		text_string_length(flag_as_text_string)));
    }
    if (temp_2) {
	temp_1 = arg_qm;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    reclaim_text_string(flag_as_text_string);
    return VALUES_1(temp_1);
}

/* GET-GENSYM-ENVIRONMENT-VARIABLE */
Object get_gensym_environment_variable(variable_name_string)
    Object variable_name_string;
{
    x_note_fn_call(32,222);
    return foreign_get_environment_variable(variable_name_string);
}

/* READ-NUMBER-FOR-GENSYM-ENVIRONMENT-VARIABLE */
Object read_number_for_gensym_environment_variable(variable_name)
    Object variable_name;
{
    Object string_to_parse_qm, temp;

    x_note_fn_call(32,223);
    string_to_parse_qm = get_gensym_environment_variable(variable_name);
    if (string_to_parse_qm) {
	temp = text_string_parse_integer_function(string_to_parse_qm,
		FIX((SI_Long)0L),Nil,T);
	reclaim_text_string(string_to_parse_qm);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* READ-MEMORY-SIZE-FOR-GENSYM-ENVIRONMENT-VARIABLE */
Object read_memory_size_for_gensym_environment_variable(variable_name)
    Object variable_name;
{
    Object string_to_parse_qm, temp;

    x_note_fn_call(32,224);
    string_to_parse_qm = get_gensym_environment_variable(variable_name);
    if (string_to_parse_qm) {
	temp = read_memory_size_from_string(string_to_parse_qm);
	reclaim_text_string(string_to_parse_qm);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_gensym_user_home_directory, Qcached_gensym_user_home_directory);

DEFINE_VARIABLE_WITH_SYMBOL(All_command_line_keyword_arguments, Qall_command_line_keyword_arguments);

/* GET-ALL-COMMAND-LINE-KEYWORD-ARGUMENTS */
Object get_all_command_line_keyword_arguments(keyword)
    Object keyword;
{
    Object arg_qm, this_keyword_argument_qm, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, temp_1;
    SI_Long keyword_comparison_start_index, i;
    char temp_2;

    x_note_fn_call(32,225);
    keyword_comparison_start_index = command_line_keyword_p(keyword) ? 
	    (SI_Long)1L : (SI_Long)0L;
    i = (SI_Long)1L;
    arg_qm = Nil;
    this_keyword_argument_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    arg_qm = get_gensym_command_line_argument_as_text_string(FIX(i));
    if ( !TRUEP(arg_qm))
	goto end_loop;
    if (command_line_keyword_p(arg_qm)) {
	temp = arg_qm;
	temp_1 = text_string_length(arg_qm);
	temp_2 = TRUEP(text_string_equal_given_indices(temp,keyword,
		FIX((SI_Long)1L),temp_1,
		FIX(keyword_comparison_start_index),
		text_string_length(keyword)));
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	this_keyword_argument_qm = 
		get_gensym_command_line_argument_as_text_string(FIX(i + 
		(SI_Long)1L));
	temp_2 = TRUEP(this_keyword_argument_qm);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	ab_loopvar__2 = gensym_cons_1(this_keyword_argument_qm,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

Object Command_line_plist_element_getter_prop = UNBOUND;

Object Command_line_argument_processor_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(All_known_command_line_plist_elements, Qall_known_command_line_plist_elements);

DEFINE_VARIABLE_WITH_SYMBOL(Used_positional_command_line_argument_default, Qused_positional_command_line_argument_default);

static Object Qcommand_line_plist_element_getter;  /* command-line-plist-element-getter */

/* GET-COMMAND-LINE-ARGUMENTS */
Object get_command_line_arguments()
{
    Object used_positional_command_line_argument_default, indicator;
    Object ab_loop_list_, value_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_;
    Declare_special(1);
    Object result;

    x_note_fn_call(32,226);
    used_positional_command_line_argument_default = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Used_positional_command_line_argument_default,Qused_positional_command_line_argument_default,used_positional_command_line_argument_default,
	    0);
      indicator = Nil;
      ab_loop_list_ = All_known_command_line_plist_elements;
      value_qm = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      indicator = CAR(ab_loop_desetq_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      value_qm = 
	      FUNCALL_0(getfq_function_no_default(INLINE_SYMBOL_PLIST(indicator),
	      Qcommand_line_plist_element_getter));
      ab_loopvar__2 = value_qm ? gensym_list_2(indicator,value_qm) : Nil;
      if (ab_loopvar__2) {
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = last(ab_loopvar__2,_);
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(ab_loopvar_);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* GET-INITIAL-COMMAND-LINE-ARGUMENTS */
Object get_initial_command_line_arguments()
{
    x_note_fn_call(32,227);
    All_known_command_line_plist_elements = 
	    sort_list(All_known_command_line_plist_elements,Qnum_lt,Qcdr);
    return get_command_line_arguments();
}

Object Command_line_arguments = UNBOUND;

/* COMMAND-LINE-PROCESS-PASSWORD */
Object command_line_process_password(value_qm)
    Object value_qm;
{
    x_note_fn_call(32,228);
    if (value_qm)
	return encode_user_password_string_function(value_qm);
    else
	return VALUES_1(Nil);
}

static Object array_constant_7;    /* # */

static Object Qpassword;           /* password */

static Object Qcommand_line_argument_processor;  /* command-line-argument-processor */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-PASSWORD */
Object get_command_line_plist_element_for_password()
{
    Object value_qm, temp;

    x_note_fn_call(32,229);
    value_qm = get_command_line_keyword_argument(1,array_constant_7);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpassword),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

/* COMMAND-LINE-PROCESS-LANGUAGE */
Object command_line_process_language(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,230);
    return VALUES_1(arg_qm);
}

static Object array_constant_8;    /* # */

static Object Qlanguage;           /* language */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-LANGUAGE */
Object get_command_line_plist_element_for_language()
{
    Object arg_qm, temp;

    x_note_fn_call(32,231);
    arg_qm = get_command_line_keyword_argument(1,array_constant_8);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlanguage),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

static Object list_constant_3;     /* # */

static Object string_constant_17;  /* "Note: ~A is not valid for the -cjk-language option.~
				    *          ~%It should be either Chinese, Japanese, or Korean."
				    */

/* COMMAND-LINE-PROCESS-CJK-LANGUAGE */
Object command_line_process_cjk_language(value_qm)
    Object value_qm;
{
    x_note_fn_call(32,232);
    if (value_qm) {
	if (member_eql(value_qm,list_constant_3)) {
	    notify_user_at_console(2,string_constant_17,value_qm);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(value_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_9;    /* # */

static Object Qcjk_language;       /* cjk-language */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-CJK-LANGUAGE */
Object get_command_line_plist_element_for_cjk_language()
{
    Object value_qm, temp;

    x_note_fn_call(32,233);
    value_qm = get_command_line_keyword_argument(1,array_constant_9);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcjk_language),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

/* COMMAND-LINE-PROCESS-INIT-STRING */
Object command_line_process_init_string(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,234);
    return VALUES_1(arg_qm);
}

static Object array_constant_10;   /* # */

static Object Qinit_string;        /* init-string */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-INIT-STRING */
Object get_command_line_plist_element_for_init_string()
{
    Object arg_qm, temp;

    x_note_fn_call(32,235);
    arg_qm = get_command_line_keyword_argument(1,array_constant_10);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinit_string),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-DISCARD-USER-SETTINGS */
Object command_line_process_discard_user_settings(value_qm)
    Object value_qm;
{
    x_note_fn_call(32,236);
    if (value_qm)
	return VALUES_1(T);
    else
	return VALUES_1(Nil);
}

static Object array_constant_11;   /* # */

static Object Qdiscard_user_settings;  /* discard-user-settings */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DISCARD-USER-SETTINGS */
Object get_command_line_plist_element_for_discard_user_settings()
{
    Object value_qm, temp;

    x_note_fn_call(32,237);
    value_qm = get_command_line_flag_argument(2,array_constant_11,T);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdiscard_user_settings),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

/* COMMAND-LINE-PROCESS-USER-MODE */
Object command_line_process_user_mode(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,238);
    return VALUES_1(arg_qm);
}

static Object array_constant_12;   /* # */

static Object Quser_mode;          /* user-mode */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USER-MODE */
Object get_command_line_plist_element_for_user_mode()
{
    Object arg_qm, temp;

    x_note_fn_call(32,239);
    arg_qm = get_command_line_keyword_argument(1,array_constant_12);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_mode),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-WINDOW */
Object command_line_process_window(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,240);
    return VALUES_1(arg_qm);
}

static Object array_constant_13;   /* # */

static Object Qwindow;             /* window */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOW */
Object get_command_line_plist_element_for_window()
{
    Object arg_qm, temp;

    x_note_fn_call(32,241);
    arg_qm = get_command_line_keyword_argument(1,array_constant_13);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwindow),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-USER-NAME */
Object command_line_process_user_name(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,242);
    return VALUES_1(arg_qm);
}

static Object array_constant_14;   /* # */

static Object Quser_name;          /* user-name */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USER-NAME */
Object get_command_line_plist_element_for_user_name()
{
    Object arg_qm, temp;

    x_note_fn_call(32,243);
    arg_qm = get_command_line_keyword_argument(1,array_constant_14);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_name),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-WINDOWHANDLE */
Object command_line_process_windowhandle(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,244);
    return VALUES_1(arg_qm);
}

static Object array_constant_15;   /* # */

static Object Qwindowhandle;       /* windowhandle */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOWHANDLE */
Object get_command_line_plist_element_for_windowhandle()
{
    Object arg_qm, temp;

    x_note_fn_call(32,245);
    arg_qm = get_command_line_keyword_argument(1,array_constant_15);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwindowhandle),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

static Object string_constant_18;  /* "windowhandle" */

static Object string_constant_19;  /* "" */

/* GET-PARENT-WINDOWHANDLE */
Object get_parent_windowhandle()
{
    Object temp;

    x_note_fn_call(32,246);
    temp = get_command_line_keyword_argument(1,string_constant_18);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_19);
}

static Object string_constant_20;  /* "-window-style" */

/* COMMAND-LINE-PROCESS-WINDOW-STYLE */
Object command_line_process_window_style(value_qm)
    Object value_qm;
{
    x_note_fn_call(32,247);
    if (value_qm)
	return validate_window_style_command_line_argument(value_qm,
		string_constant_20);
    else
	return VALUES_1(Nil);
}

static Object array_constant_16;   /* # */

static Object Qwindow_style;       /* window-style */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOW-STYLE */
Object get_command_line_plist_element_for_window_style()
{
    Object value_qm, temp;

    x_note_fn_call(32,248);
    value_qm = get_command_line_keyword_argument(1,array_constant_16);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwindow_style),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

static Object list_constant_4;     /* # */

static Object string_constant_21;  /* "The ~a argument ~s is not recognized. It should be one of ~L,|" */

/* VALIDATE-WINDOW-STYLE-COMMAND-LINE-ARGUMENT */
Object validate_window_style_command_line_argument(argument,argument_string)
    Object argument, argument_string;
{
    Object styles, style, ab_loop_list_;

    x_note_fn_call(32,249);
    styles = list_constant_4;
    style = Nil;
    ab_loop_list_ = styles;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    style = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (string_equalw(argument,symbol_namew(style)))
	return VALUES_1(style);
    goto next_loop;
  end_loop:
    notify_user_at_console(4,string_constant_21,argument_string,argument,
	    styles);
    return VALUES_1(Qnil);
}

/* COMMAND-LINE-PROCESS-NO-NATIVE-FONTS */
Object command_line_process_no_native_fonts(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,250);
    return VALUES_1(arg_qm);
}

static Object array_constant_17;   /* # */

static Object Qno_native_fonts;    /* no-native-fonts */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-NATIVE-FONTS */
Object get_command_line_plist_element_for_no_native_fonts()
{
    Object arg_qm, temp;

    x_note_fn_call(32,251);
    arg_qm = get_command_line_flag_argument(2,array_constant_17,T);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qno_native_fonts),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-NATIVE-FONTS */
Object command_line_process_native_fonts(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,252);
    return VALUES_1(arg_qm);
}

static Object array_constant_18;   /* # */

static Object Qnative_fonts;       /* native-fonts */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NATIVE-FONTS */
Object get_command_line_plist_element_for_native_fonts()
{
    Object arg_qm, temp;

    x_note_fn_call(32,253);
    arg_qm = get_command_line_flag_argument(2,array_constant_18,T);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnative_fonts),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-NO-NATIVE-CLIPBOARD */
Object command_line_process_no_native_clipboard(value_qm)
    Object value_qm;
{
    x_note_fn_call(32,254);
    if (value_qm)
	return VALUES_1(T);
    else
	return VALUES_1(Nil);
}

static Object array_constant_19;   /* # */

static Object Qno_native_clipboard;  /* no-native-clipboard */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-NATIVE-CLIPBOARD */
Object get_command_line_plist_element_for_no_native_clipboard()
{
    Object value_qm, temp;

    x_note_fn_call(32,255);
    value_qm = get_command_line_flag_argument(2,array_constant_19,T);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qno_native_clipboard),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

static Object array_constant_20;   /* # */

/* COMMAND-LINE-PROCESS-G2PASSWDEXE */
Object command_line_process_g2passwdexe(value_qm)
    Object value_qm;
{
    Object temp;

    x_note_fn_call(32,256);
    temp = value_qm;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(array_constant_20);
}

static Object array_constant_21;   /* # */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-G2PASSWDEXE */
Object get_command_line_plist_element_for_g2passwdexe()
{
    Object value_qm, temp;

    x_note_fn_call(32,257);
    value_qm = get_command_line_keyword_argument(1,array_constant_21);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2passwdexe),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

/* COMMAND-LINE-PROCESS-NO-BACKING-STORE */
Object command_line_process_no_backing_store(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,258);
    return VALUES_1(arg_qm);
}

static Object array_constant_22;   /* # */

static Object Qno_backing_store;   /* no-backing-store */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-BACKING-STORE */
Object get_command_line_plist_element_for_no_backing_store()
{
    Object arg_qm, temp;

    x_note_fn_call(32,259);
    arg_qm = get_command_line_flag_argument(2,array_constant_22,T);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qno_backing_store),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-PRIVATE-COLORMAP */
Object command_line_process_private_colormap(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,260);
    return VALUES_1(arg_qm);
}

static Object array_constant_23;   /* # */

static Object Qprivate_colormap;   /* private-colormap */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-PRIVATE-COLORMAP */
Object get_command_line_plist_element_for_private_colormap()
{
    Object arg_qm, temp;

    x_note_fn_call(32,261);
    arg_qm = get_command_line_flag_argument(2,array_constant_23,T);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qprivate_colormap),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-FILE-OPERATION-TIMEOUT */
Object command_line_process_file_operation_timeout(value_qm)
    Object value_qm;
{
    x_note_fn_call(32,262);
    return VALUES_1(value_qm);
}

static Object array_constant_24;   /* # */

static Object Qfile_operation_timeout;  /* file-operation-timeout */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-FILE-OPERATION-TIMEOUT */
Object get_command_line_plist_element_for_file_operation_timeout()
{
    Object value_qm, temp;

    x_note_fn_call(32,263);
    value_qm = get_command_line_keyword_argument(1,array_constant_24);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfile_operation_timeout),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

/* COMMAND-LINE-PROCESS-USE-OS-EMULATION */
Object command_line_process_use_os_emulation(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,264);
    return VALUES_1(arg_qm);
}

static Object array_constant_25;   /* # */

static Object Quse_os_emulation;   /* use-os-emulation */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USE-OS-EMULATION */
Object get_command_line_plist_element_for_use_os_emulation()
{
    Object arg_qm, temp;

    x_note_fn_call(32,265);
    arg_qm = get_command_line_flag_argument(2,array_constant_25,T);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Quse_os_emulation),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-COPY-MESSAGES-ON-LOGBOOK */
Object command_line_process_copy_messages_on_logbook(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,266);
    return VALUES_1(arg_qm);
}

static Object array_constant_26;   /* # */

static Object Qcopy_messages_on_logbook;  /* copy-messages-on-logbook */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-COPY-MESSAGES-ON-LOGBOOK */
Object get_command_line_plist_element_for_copy_messages_on_logbook()
{
    Object arg_qm, temp;

    x_note_fn_call(32,267);
    arg_qm = get_command_line_flag_argument(2,array_constant_26,T);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcopy_messages_on_logbook),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-COPY-LOGBOOK-ON-CONSOLE */
Object command_line_process_copy_logbook_on_console(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,268);
    return VALUES_1(arg_qm);
}

static Object array_constant_27;   /* # */

static Object Qcopy_logbook_on_console;  /* copy-logbook-on-console */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-COPY-LOGBOOK-ON-CONSOLE */
Object get_command_line_plist_element_for_copy_logbook_on_console()
{
    Object arg_qm, temp;

    x_note_fn_call(32,269);
    arg_qm = get_command_line_flag_argument(2,array_constant_27,T);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcopy_logbook_on_console),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-DEBUG-FRAME-REFERENCE-BALANCE */
Object command_line_process_debug_frame_reference_balance(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,270);
    return VALUES_1(arg_qm);
}

static Object array_constant_28;   /* # */

static Object Qdebug_frame_reference_balance;  /* debug-frame-reference-balance */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DEBUG-FRAME-REFERENCE-BALANCE */
Object get_command_line_plist_element_for_debug_frame_reference_balance()
{
    Object arg_qm, temp;

    x_note_fn_call(32,271);
    arg_qm = get_command_line_flag_argument(2,array_constant_28,T);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdebug_frame_reference_balance),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-XCLIP */
Object command_line_process_xclip(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,272);
    return VALUES_1(arg_qm);
}

static Object array_constant_29;   /* # */

static Object Qxclip;              /* xclip */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-XCLIP */
Object get_command_line_plist_element_for_xclip()
{
    Object arg_qm, temp;

    x_note_fn_call(32,273);
    arg_qm = get_command_line_flag_argument(2,array_constant_29,T);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qxclip),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

static Object Kall;                /* :all */

/* COMMAND-LINE-PROCESS-BACKGROUND */
Object command_line_process_background(arg_qm)
    Object arg_qm;
{
    Object arg_with_case_conversion, symbol;

    x_note_fn_call(32,274);
    if (arg_qm) {
	arg_with_case_conversion = 
		copy_wide_string_with_case_conversion(arg_qm,Kall);
	symbol = intern_text_string(1,arg_with_case_conversion);
	if (rgb_from_color(symbol))
	    return VALUES_1(symbol);
	else if (get_tiling_pattern(symbol))
	    return VALUES_1(symbol);
	else
	    return copy_wide_string(arg_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_30;   /* # */

static Object Qbackground;         /* background */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-BACKGROUND */
Object get_command_line_plist_element_for_background()
{
    Object arg_qm, temp;

    x_note_fn_call(32,275);
    arg_qm = get_command_line_keyword_argument(1,array_constant_30);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qbackground),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

Object Known_ui_styles = UNBOUND;

static Object string_constant_22;  /* "The -ui argument ~s must either be ~(~L,|~). Assuming ~(~s~)." */

/* COMMAND-LINE-PROCESS-UI */
Object command_line_process_ui(value_qm)
    Object value_qm;
{
    Object temp;

    x_note_fn_call(32,276);
    temp = parse_ui_style(value_qm);
    if (temp)
	return VALUES_1(temp);
    else {
	notify_user_at_console(4,string_constant_22,value_qm,
		Known_ui_styles,gensym_default_ui());
	return gensym_default_ui();
    }
}

static Object array_constant_31;   /* # */

static Object Qui;                 /* ui */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-UI */
Object get_command_line_plist_element_for_ui()
{
    Object value_qm, temp;

    x_note_fn_call(32,277);
    value_qm = get_command_line_keyword_argument(1,array_constant_31);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qui),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

/* PARSE-UI-STYLE */
Object parse_ui_style(value_qm)
    Object value_qm;
{
    Object ui, ab_loop_list_, temp;

    x_note_fn_call(32,278);
    if ( !TRUEP(value_qm))
	return gensym_default_ui();
    else {
	ui = Nil;
	ab_loop_list_ = Known_ui_styles;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ui = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (string_equalw(value_qm,stringw(ui))) {
	    temp = ui;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qab_standard;        /* standard */

/* GENSYM-DEFAULT-UI */
Object gensym_default_ui()
{
    x_note_fn_call(32,279);
    return VALUES_1(Qab_standard);
}

/* COMMAND-LINE-PROCESS-NETINFO */
Object command_line_process_netinfo(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,280);
    return VALUES_1(arg_qm);
}

static Object array_constant_32;   /* # */

static Object Qnetinfo;            /* netinfo */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NETINFO */
Object get_command_line_plist_element_for_netinfo()
{
    Object arg_qm, temp;

    x_note_fn_call(32,281);
    arg_qm = get_command_line_flag_argument(2,array_constant_32,T);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnetinfo),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-VERBOSE */
Object command_line_process_verbose(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,282);
    return VALUES_1(arg_qm);
}

static Object array_constant_33;   /* # */

static Object Qverbose;            /* verbose */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-VERBOSE */
Object get_command_line_plist_element_for_verbose()
{
    Object arg_qm, temp;

    x_note_fn_call(32,283);
    arg_qm = get_command_line_flag_argument(2,array_constant_33,T);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qverbose),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-SILENT */
Object command_line_process_silent(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,284);
    return VALUES_1(arg_qm);
}

static Object array_constant_34;   /* # */

static Object Qsilent;             /* silent */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-SILENT */
Object get_command_line_plist_element_for_silent()
{
    Object arg_qm, temp;

    x_note_fn_call(32,285);
    arg_qm = get_command_line_flag_argument(2,array_constant_34,T);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsilent),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-EXIT-ON-ABORT */
Object command_line_process_exit_on_abort(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,286);
    return VALUES_1(arg_qm);
}

static Object array_constant_35;   /* # */

static Object Qexit_on_abort;      /* exit-on-abort */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-EXIT-ON-ABORT */
Object get_command_line_plist_element_for_exit_on_abort()
{
    Object arg_qm, temp;

    x_note_fn_call(32,287);
    arg_qm = get_command_line_flag_argument(2,array_constant_35,T);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexit_on_abort),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

static Object array_constant_36;   /* # */

/* EXIT-ON-ABORT-P */
Object exit_on_abort_p()
{
    Object temp;

    x_note_fn_call(32,288);
    temp = get_command_line_flag_argument(1,array_constant_36);
    return VALUES_1(temp);
}

/* COMMAND-LINE-PROCESS-USE-JIT */
Object command_line_process_use_jit(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,289);
    return VALUES_1(arg_qm);
}

static Object array_constant_37;   /* # */

static Object Quse_jit;            /* use-jit */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USE-JIT */
Object get_command_line_plist_element_for_use_jit()
{
    Object arg_qm, temp;

    x_note_fn_call(32,290);
    arg_qm = get_command_line_flag_argument(2,array_constant_37,T);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Quse_jit),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Use_jit_p, Quse_jit_p);

Object Secure_icp_initialized_p = UNBOUND;

Object Secure_icp_default_p = UNBOUND;

Object Cache_server_cert_name = UNBOUND;

/* COMMAND-LINE-PROCESS-SECURE */
Object command_line_process_secure(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,291);
    return VALUES_1(arg_qm);
}

static Object array_constant_38;   /* # */

static Object Qsecure;             /* secure */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-SECURE */
Object get_command_line_plist_element_for_secure()
{
    Object arg_qm, temp;

    x_note_fn_call(32,292);
    arg_qm = get_command_line_flag_argument(2,array_constant_38,T);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsecure),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

static Object array_constant_39;   /* # */

/* SECURE-ICP-REQUESTED-P */
Object secure_icp_requested_p()
{
    x_note_fn_call(32,293);
    return get_command_line_flag_argument(1,array_constant_39);
}

/* COMMAND-LINE-PROCESS-CERT */
Object command_line_process_cert(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(32,294);
    return VALUES_1(arg_qm);
}

static Object array_constant_40;   /* # */

static Object Qcert;               /* cert */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-CERT */
Object get_command_line_plist_element_for_cert()
{
    Object arg_qm, temp;

    x_note_fn_call(32,295);
    arg_qm = get_command_line_keyword_argument(1,array_constant_40);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcert),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* UPDATE-SERVER-CERTIFICATE */
Object update_server_certificate(newcert)
    Object newcert;
{
    x_note_fn_call(32,296);
    if ( !TRUEP(Secure_icp_initialized_p)) {
	Cache_server_cert_name = newcert;
	return VALUES_1(Cache_server_cert_name);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_23;  /* "cert" */

static Object string_constant_24;  /* "G2_CERT" */

/* SERVER-CERTIFICATE-NAME */
Object server_certificate_name()
{
    Object temp;

    x_note_fn_call(32,297);
    temp = get_command_line_keyword_argument(1,string_constant_23);
    if (temp);
    else
	temp = Cache_server_cert_name;
    if (temp)
	return VALUES_1(temp);
    else {
	Cache_server_cert_name = 
		get_gensym_environment_variable(string_constant_24);
	return VALUES_1(Cache_server_cert_name);
    }
}

/* STRING-PREFIX=W */
Object string_prefix_eq_w(prefix,string_1)
    Object prefix, string_1;
{
    SI_Long length_1, length_2, i, ab_loop_bind_;

    x_note_fn_call(32,298);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(prefix));
    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LE(FIX(UBYTE_16_ISAREF_1(prefix,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(prefix,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    FIX(UBYTE_16_ISAREF_1(string_1,length_2 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_2 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)))) {
	i = (SI_Long)0L;
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(prefix));
	ab_loop_bind_ = UBYTE_16_ISAREF_1(prefix,length_1 - (SI_Long)2L) + 
		((UBYTE_16_ISAREF_1(prefix,length_1 - (SI_Long)1L) & 
		(SI_Long)8191L) << (SI_Long)16L);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if ( !(UBYTE_16_ISAREF_1(prefix,i) == UBYTE_16_ISAREF_1(string_1,i)))
	    return VALUES_1(Nil);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Knetwork_type;       /* :network-type */

static Object Kuse_default;        /* :use-default */

static Object Ksecure_p;           /* :secure-p */

static Object array_constant_41;   /* # */

static Object string_constant_25;  /* "/SSL" */

/* SECURE-ICP-STRING */
Object secure_icp_string varargs_1(int, n)
{
    Object network_type_p, network_type, use_default_p, use_default;
    Object secure_p_p, secure_p;
    Declare_varargs;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(32,299);
    SAVE_STACK();
    INIT_ARGS();
    SAVE_ARGS();
    network_type_p = KEYWORD_ARG_P(Knetwork_type);
    network_type = network_type_p ? KEYWORD_ARG(network_type_p) : Nil;
    use_default_p = KEYWORD_ARG_P(Kuse_default);
    use_default = use_default_p ? KEYWORD_ARG(use_default_p) : Nil;
    secure_p_p = KEYWORD_ARG_P(Ksecure_p);
    secure_p = secure_p_p ? KEYWORD_ARG(secure_p_p) : T;
    if (secure_p && ( !TRUEP(network_type) || 
	    string_prefix_eq_w(array_constant_41,network_type)) && 
	    (use_default ? TRUEP(Secure_icp_default_p) : 
	    TRUEP(Secure_icp_initialized_p))) {
	RESTORE_STACK();
	return VALUES_1(string_constant_25);
    }
    else {
	RESTORE_STACK();
	return VALUES_1(string_constant_19);
    }
}

/* C-SET-SECURE-ICP */
Object c_set_secure_icp(certificate)
    Object certificate;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(32,300);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(certificate);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = certificate;
    temp = FIX(g2ext_set_secure_icp(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

static Object string_constant_26;  /* "WARNING: SSL encryption is not available in this executable." */

/* SET-UP-SECURE-ICP */
Object set_up_secure_icp varargs_1(int, n)
{
    Object default_p, temp, rc;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,301);
    INIT_ARGS_nonrelocating();
    default_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(Secure_icp_initialized_p)) {
	temp = server_certificate_name();
	if (temp);
	else
	    temp = string_constant_19;
	rc = c_set_secure_icp(temp);
	if (IFIX(rc) == (SI_Long)0L)
	    notify_user_at_console(1,string_constant_26);
	Secure_icp_default_p = default_p;
	Secure_icp_initialized_p = IFIX(rc) != (SI_Long)0L ? T : Nil;
	return VALUES_1(Secure_icp_initialized_p);
    }
    else
	return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-ICP-LOG-INTENSITY */
Object command_line_process_icp_log_intensity(value_qm)
    Object value_qm;
{
    Object integer_qm;

    x_note_fn_call(32,302);
    if (value_qm) {
	integer_qm = read_fixnum_from_string(1,value_qm);
	if (integer_qm);
	else
	    integer_qm = FIX((SI_Long)7L);
    }
    else
	integer_qm = Nil;
    if (integer_qm) {
	if (IFIX(integer_qm) < (SI_Long)0L || IFIX(integer_qm) > (SI_Long)6L)
	    integer_qm = FIX((SI_Long)7L);
    }
    return VALUES_1(integer_qm);
}

static Object array_constant_42;   /* # */

static Object Qicp_log_intensity;  /* icp-log-intensity */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-ICP-LOG-INTENSITY */
Object get_command_line_plist_element_for_icp_log_intensity()
{
    Object value_qm, temp;

    x_note_fn_call(32,303);
    value_qm = get_command_line_keyword_argument(1,array_constant_42);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qicp_log_intensity),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

Object Foreign_struct_info_prop = UNBOUND;

Object The_type_description_of_foreign_struct_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_foreign_struct_infos, Qchain_of_available_foreign_struct_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Foreign_struct_info_count, Qforeign_struct_info_count);

Object Chain_of_available_foreign_struct_infos_vector = UNBOUND;

/* FOREIGN-STRUCT-INFO-STRUCTURE-MEMORY-USAGE */
Object foreign_struct_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(32,304);
    temp = Foreign_struct_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FOREIGN-STRUCT-INFO-COUNT */
Object outstanding_foreign_struct_info_count()
{
    Object def_structure_foreign_struct_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(32,305);
    gensymed_symbol = IFIX(Foreign_struct_info_count);
    def_structure_foreign_struct_info_variable = 
	    Chain_of_available_foreign_struct_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_foreign_struct_info_variable))
	goto end_loop;
    def_structure_foreign_struct_info_variable = 
	    ISVREF(def_structure_foreign_struct_info_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-FOREIGN-STRUCT-INFO-1 */
Object reclaim_foreign_struct_info_1(foreign_struct_info)
    Object foreign_struct_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(32,306);
    inline_note_reclaim_cons(foreign_struct_info,Nil);
    temp = ISVREF(Chain_of_available_foreign_struct_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(foreign_struct_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_foreign_struct_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = foreign_struct_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FOREIGN-STRUCT-INFO */
Object reclaim_structure_for_foreign_struct_info(foreign_struct_info)
    Object foreign_struct_info;
{
    x_note_fn_call(32,307);
    return reclaim_foreign_struct_info_1(foreign_struct_info);
}

static Object Qg2_defstruct_structure_name_foreign_struct_info_g2_struct;  /* g2-defstruct-structure-name::foreign-struct-info-g2-struct */

/* MAKE-PERMANENT-FOREIGN-STRUCT-INFO-STRUCTURE-INTERNAL */
Object make_permanent_foreign_struct_info_structure_internal()
{
    Object def_structure_foreign_struct_info_variable;
    Object defstruct_g2_foreign_struct_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(32,308);
    def_structure_foreign_struct_info_variable = Nil;
    atomic_incff_symval(Qforeign_struct_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_foreign_struct_info_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_foreign_struct_info_variable = the_array;
	SVREF(defstruct_g2_foreign_struct_info_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_foreign_struct_info_g2_struct;
	def_structure_foreign_struct_info_variable = 
		defstruct_g2_foreign_struct_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_foreign_struct_info_variable);
}

/* MAKE-FOREIGN-STRUCT-INFO-1 */
Object make_foreign_struct_info_1()
{
    Object def_structure_foreign_struct_info_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(32,309);
    def_structure_foreign_struct_info_variable = 
	    ISVREF(Chain_of_available_foreign_struct_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_foreign_struct_info_variable) {
	svref_arg_1 = Chain_of_available_foreign_struct_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_foreign_struct_info_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_foreign_struct_info_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_foreign_struct_info_g2_struct;
    }
    else
	def_structure_foreign_struct_info_variable = 
		make_permanent_foreign_struct_info_structure_internal();
    inline_note_allocate_cons(def_structure_foreign_struct_info_variable,Nil);
    SVREF(def_structure_foreign_struct_info_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_foreign_struct_info_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_foreign_struct_info_variable,FIX((SI_Long)3L)) = Nil;
    ISVREF(def_structure_foreign_struct_info_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_foreign_struct_info_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_foreign_struct_info_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_foreign_struct_info_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Next_eq_hash_value, Qnext_eq_hash_value);

Object The_type_description_of_eq_hash_table = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_eq_hash_tables, Qchain_of_available_eq_hash_tables);

DEFINE_VARIABLE_WITH_SYMBOL(Eq_hash_table_count, Qeq_hash_table_count);

Object Chain_of_available_eq_hash_tables_vector = UNBOUND;

/* EQ-HASH-TABLE-STRUCTURE-MEMORY-USAGE */
Object eq_hash_table_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(32,310);
    temp = Eq_hash_table_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EQ-HASH-TABLE-COUNT */
Object outstanding_eq_hash_table_count()
{
    Object def_structure_eq_hash_table_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(32,311);
    gensymed_symbol = IFIX(Eq_hash_table_count);
    def_structure_eq_hash_table_variable = Chain_of_available_eq_hash_tables;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_eq_hash_table_variable))
	goto end_loop;
    def_structure_eq_hash_table_variable = 
	    ISVREF(def_structure_eq_hash_table_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EQ-HASH-TABLE-INTERNAL-1 */
Object reclaim_eq_hash_table_internal_1(eq_hash_table)
    Object eq_hash_table;
{
    Object temp, svref_arg_2;

    x_note_fn_call(32,312);
    inline_note_reclaim_cons(eq_hash_table,Nil);
    temp = ISVREF(Chain_of_available_eq_hash_tables_vector,
	    IFIX(Current_thread_index));
    SVREF(eq_hash_table,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_eq_hash_tables_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = eq_hash_table;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EQ-HASH-TABLE */
Object reclaim_structure_for_eq_hash_table(eq_hash_table)
    Object eq_hash_table;
{
    x_note_fn_call(32,313);
    return reclaim_eq_hash_table_internal_1(eq_hash_table);
}

static Object Qg2_defstruct_structure_name_eq_hash_table_g2_struct;  /* g2-defstruct-structure-name::eq-hash-table-g2-struct */

/* MAKE-PERMANENT-EQ-HASH-TABLE-STRUCTURE-INTERNAL */
Object make_permanent_eq_hash_table_structure_internal()
{
    Object def_structure_eq_hash_table_variable;
    Object defstruct_g2_eq_hash_table_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(32,314);
    def_structure_eq_hash_table_variable = Nil;
    atomic_incff_symval(Qeq_hash_table_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_eq_hash_table_variable = Nil;
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
	defstruct_g2_eq_hash_table_variable = the_array;
	SVREF(defstruct_g2_eq_hash_table_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_eq_hash_table_g2_struct;
	def_structure_eq_hash_table_variable = 
		defstruct_g2_eq_hash_table_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_eq_hash_table_variable);
}

/* MAKE-EQ-HASH-TABLE-INTERNAL-1 */
Object make_eq_hash_table_internal_1()
{
    Object def_structure_eq_hash_table_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(32,315);
    def_structure_eq_hash_table_variable = 
	    ISVREF(Chain_of_available_eq_hash_tables_vector,
	    IFIX(Current_thread_index));
    if (def_structure_eq_hash_table_variable) {
	svref_arg_1 = Chain_of_available_eq_hash_tables_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_eq_hash_table_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_eq_hash_table_g2_struct;
    }
    else
	def_structure_eq_hash_table_variable = 
		make_permanent_eq_hash_table_structure_internal();
    inline_note_allocate_cons(def_structure_eq_hash_table_variable,Nil);
    SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_eq_hash_table_variable);
}

/* MAKE-EQ-HASH-TABLE */
Object make_eq_hash_table(size,key_reclaimer_qm,value_reclaimer_qm)
    Object size, key_reclaimer_qm, value_reclaimer_qm;
{
    Object table, vec, svref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(32,316);
    table = make_eq_hash_table_internal_1();
    vec = allocate_managed_simple_vector(size);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(size);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    ISVREF(vec,i) = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    svref_new_value = vec;
    goto end_1;
    svref_new_value = Qnil;
  end_1:;
    SVREF(table,FIX((SI_Long)1L)) = svref_new_value;
    SVREF(table,FIX((SI_Long)2L)) = size;
    ISVREF(table,(SI_Long)3L) = FIX((SI_Long)0L);
    SVREF(table,FIX((SI_Long)4L)) = key_reclaimer_qm;
    SVREF(table,FIX((SI_Long)5L)) = value_reclaimer_qm;
    return VALUES_1(table);
}

/* RECLAIM-EQ-HASH-TABLE */
Object reclaim_eq_hash_table(table)
    Object table;
{
    Object vector_1, length_1, key_reclaimer_qm, value_reclaimer_qm, chain;
    Object pair, ab_loop_list_, key, value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(32,317);
    vector_1 = ISVREF(table,(SI_Long)1L);
    length_1 = ISVREF(table,(SI_Long)2L);
    key_reclaimer_qm = ISVREF(table,(SI_Long)4L);
    value_reclaimer_qm = ISVREF(table,(SI_Long)5L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    chain = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    chain = ISVREF(vector_1,i);
    if (chain) {
	if (key_reclaimer_qm && value_reclaimer_qm) {
	    pair = Nil;
	    ab_loop_list_ = chain;
	    key = Nil;
	    value = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    pair = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    key = CAR(pair);
	    value = CDR(pair);
	    FUNCALL_1(key_reclaimer_qm,key);
	    FUNCALL_1(value_reclaimer_qm,value);
	    reclaim_gensym_cons_1(pair);
	    goto next_loop_1;
	  end_loop_1:;
	    reclaim_gensym_list_1(chain);
	}
	else if (value_reclaimer_qm) {
	    pair = Nil;
	    ab_loop_list_ = chain;
	    value = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    pair = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    value = CDR(pair);
	    FUNCALL_1(value_reclaimer_qm,value);
	    reclaim_gensym_cons_1(pair);
	    goto next_loop_2;
	  end_loop_2:;
	    reclaim_gensym_list_1(chain);
	}
	else if (key_reclaimer_qm) {
	    pair = Nil;
	    ab_loop_list_ = chain;
	    key = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    pair = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    key = CAR(pair);
	    FUNCALL_1(key_reclaimer_qm,key);
	    reclaim_gensym_cons_1(pair);
	    goto next_loop_3;
	  end_loop_3:;
	    reclaim_gensym_list_1(chain);
	}
	else {
	    pair = Nil;
	    ab_loop_list_ = chain;
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_4;
	    pair = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    reclaim_gensym_cons_1(pair);
	    goto next_loop_4;
	  end_loop_4:;
	    reclaim_gensym_list_1(chain);
	}
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    reclaim_managed_simple_vector(vector_1);
    return reclaim_eq_hash_table_internal_1(table);
}

/* EQ-GETHASH */
Object eq_gethash(table,key_object,default_value_qm)
    Object table, key_object, default_value_qm;
{
    Object thing, hash_code, length_1, vector_1, chain, temp_1, pair;
    SI_Long temp;

    x_note_fn_call(32,318);
    thing = key_object;
    hash_code = FIXNUMP(thing) ? (IFIX(thing) < (SI_Long)0L ? 
	    FIXNUM_NEGATE(thing) : thing) : FIX(SXHASH_SYMBOL_1(thing) & 
	    IFIX(Most_positive_fixnum));
    length_1 = ISVREF(table,(SI_Long)2L);
    vector_1 = ISVREF(table,(SI_Long)1L);
    temp = IFIX(hash_code) % IFIX(length_1);
    chain = ISVREF(vector_1,temp);
  next_loop:
    if ( !TRUEP(chain)) {
	temp_1 = default_value_qm;
	goto end_1;
    }
    pair = M_CAR(chain);
    if (EQ(M_CAR(pair),key_object)) {
	temp_1 = M_CDR(pair);
	goto end_1;
    }
    chain = M_CDR(chain);
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* EQ-PUTHASH */
Object eq_puthash(table,key_object,value_object)
    Object table, key_object, value_object;
{
    Object thing, hash_code, length_1, vector_1, chain, tail;
    Object value_reclaimer_qm, svref_new_value, pair, old_value_object;
    SI_Long temp, index_1;

    x_note_fn_call(32,319);
    thing = key_object;
    hash_code = FIXNUMP(thing) ? (IFIX(thing) < (SI_Long)0L ? 
	    FIXNUM_NEGATE(thing) : thing) : FIX(SXHASH_SYMBOL_1(thing) & 
	    IFIX(Most_positive_fixnum));
    length_1 = ISVREF(table,(SI_Long)2L);
    vector_1 = ISVREF(table,(SI_Long)1L);
    temp = IFIX(hash_code) % IFIX(length_1);
    index_1 = temp;
    chain = ISVREF(vector_1,index_1);
    tail = chain;
    value_reclaimer_qm = ISVREF(table,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(tail)) {
	svref_new_value = gensym_cons_1(gensym_cons_1(key_object,
		value_object),chain);
	ISVREF(vector_1,index_1) = svref_new_value;
	goto end_1;
    }
    pair = M_CAR(tail);
    if (EQ(M_CAR(pair),key_object)) {
	old_value_object = M_CDR(pair);
	M_CDR(pair) = value_object;
	if (value_reclaimer_qm)
	    FUNCALL_1(value_reclaimer_qm,old_value_object);
	goto end_1;
    }
    tail = M_CDR(tail);
    goto next_loop;
  end_loop:
  end_1:;
    return VALUES_1(value_object);
}

/* EQ-REMHASH */
Object eq_remhash(table,key_object)
    Object table, key_object;
{
    Object thing, hash_code, length_1, vector_1, chain, tail, prev_tail;
    Object key_reclaimer_qm, value_reclaimer_qm, temp_1, pair;
    Object old_value_object, temp_2;
    SI_Long temp, index_1;

    x_note_fn_call(32,320);
    thing = key_object;
    hash_code = FIXNUMP(thing) ? (IFIX(thing) < (SI_Long)0L ? 
	    FIXNUM_NEGATE(thing) : thing) : FIX(SXHASH_SYMBOL_1(thing) & 
	    IFIX(Most_positive_fixnum));
    length_1 = ISVREF(table,(SI_Long)2L);
    vector_1 = ISVREF(table,(SI_Long)1L);
    temp = IFIX(hash_code) % IFIX(length_1);
    index_1 = temp;
    chain = ISVREF(vector_1,index_1);
    tail = chain;
    prev_tail = Nil;
    key_reclaimer_qm = ISVREF(table,(SI_Long)4L);
    value_reclaimer_qm = ISVREF(table,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(tail)) {
	temp_1 = Nil;
	goto end_1;
    }
    pair = M_CAR(tail);
    if (EQ(M_CAR(pair),key_object)) {
	old_value_object = M_CDR(pair);
	if (prev_tail) {
	    temp_2 = M_CDR(tail);
	    M_CDR(prev_tail) = temp_2;
	}
	else {
	    temp_2 = M_CDR(tail);
	    ISVREF(vector_1,index_1) = temp_2;
	}
	if (key_reclaimer_qm)
	    FUNCALL_1(key_reclaimer_qm,key_object);
	if (value_reclaimer_qm)
	    FUNCALL_1(value_reclaimer_qm,old_value_object);
	reclaim_gensym_cons_1(tail);
	reclaim_gensym_cons_1(pair);
	temp_1 = Nil;
	goto end_1;
    }
    prev_tail = tail;
    tail = M_CDR(tail);
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

static Object string_constant_27;  /* "Version ~d." */

static Object string_constant_28;  /* "~d" */

static Object Qalpha_or_beta;      /* alpha-or-beta */

static Object Qpatch_level;        /* patch-level */

static Object string_constant_29;  /* " ~a~c" */

static Object string_constant_30;  /* " ~a" */

static Object Qbrief_description;  /* brief-description */

/* TWRITE-SYSTEM-VERSION */
Object twrite_system_version varargs_1(int, n)
{
    Object system_version;
    Object suppress_brief_description_of_system_version_qm, tenths, hundredths;
    Object temp, alpha_or_beta_qm, patch_level_qm, brief_description_qm;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(32,321);
    INIT_ARGS_nonrelocating();
    system_version = REQUIRED_ARG_nonrelocating();
    suppress_brief_description_of_system_version_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    tformat(2,string_constant_27,FIRST(system_version));
    result = l_round(SECOND(system_version),FIX((SI_Long)10L));
    MVS_2(result,tenths,hundredths);
    tformat(2,string_constant_28,tenths);
    temp = FIX((SI_Long)0L);
    if (NUM_NE(hundredths,temp))
	tformat(2,string_constant_28,hundredths);
    alpha_or_beta_qm = getf(CDDR(system_version),Qalpha_or_beta,_);
    patch_level_qm = getf(CDDR(system_version),Qpatch_level,_);
    if (alpha_or_beta_qm) {
	if (patch_level_qm)
	    tformat(3,string_constant_29,alpha_or_beta_qm,
		    CODE_CHAR(add(patch_level_qm,FIX((SI_Long)96L))));
	else
	    tformat(2,string_constant_30,alpha_or_beta_qm);
    }
    if ( !TRUEP(suppress_brief_description_of_system_version_qm)) {
	brief_description_qm = getf(CDDR(system_version),Qbrief_description,_);
	if (brief_description_qm)
	    return tformat(2,string_constant_30,brief_description_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_31;  /* "Version ~d.~d " */

static Object string_constant_32;  /* "Enterprise" */

static Object string_constant_33;  /* "Standard" */

static Object string_constant_34;  /* ", ~a" */

/* TWRITE-SYSTEM-VERSION-IN-G2-TITLE */
Object twrite_system_version_in_g2_title varargs_1(int, n)
{
    Object system_version;
    Object suppress_brief_description_of_system_version_qm;
    Object brief_description_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(32,322);
    INIT_ARGS_nonrelocating();
    system_version = REQUIRED_ARG_nonrelocating();
    suppress_brief_description_of_system_version_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    tformat(3,string_constant_31,External_version,
	    Revision_number_of_current_gensym_product_line);
    tformat(1,g2_enterprise_p() ? string_constant_32 : string_constant_33);
    if ( !TRUEP(suppress_brief_description_of_system_version_qm)) {
	brief_description_qm = getf(CDDR(system_version),Qbrief_description,_);
	if (brief_description_qm)
	    return tformat(2,string_constant_34,brief_description_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-LOCAL-IDENTIFICATION-INFO-TEXT-STRING */
Object write_local_identification_info_text_string()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(32,323);
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
	      write_local_identification_info_text_string_1(T);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object Expiration_date_for_display_in_title = UNBOUND;

static Object string_constant_35;  /* "Host: ~a" */

static Object string_constant_36;  /* "; ~a: ~a~a" */

static Object string_constant_37;  /* "~%Expiration Day:~a~%" */

static Object string_constant_38;  /* "~%" */

/* WRITE-LOCAL-IDENTIFICATION-INFO-TEXT-STRING-1 */
Object write_local_identification_info_text_string_1(write_machine_id_p)
    Object write_machine_id_p;
{
    Object host_name, port_list, network_type, address, secure_p;
    Object ab_loop_list_, ab_loop_desetq_, temp, temp_1;
    Object result;

    x_note_fn_call(32,324);
    result = get_raw_network_info();
    MVS_2(result,host_name,port_list);
    tformat(2,string_constant_35,host_name);
    network_type = Nil;
    address = Nil;
    secure_p = Nil;
    ab_loop_list_ = port_list;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    network_type = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    address = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    secure_p = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = network_type;
    temp_1 = address;
    tformat(4,string_constant_36,temp,temp_1,secure_icp_string(4,Ksecure_p,
	    secure_p,Knetwork_type,network_type));
    goto next_loop;
  end_loop:;
    reclaim_raw_network_info(host_name,port_list);
    if (write_machine_id_p)
	print_first_string_in_pool_group();
    if (Expiration_date_for_display_in_title)
	return tformat(2,string_constant_37,
		Expiration_date_for_display_in_title);
    else
	return tformat(1,string_constant_38);
}

static Object string_constant_39;  /* "(Unknown Host)" */

static Object array_constant_43;   /* # */

static Object array_constant_44;   /* # */

static Object array_constant_45;   /* # */

static Object string_constant_40;  /* "~a" */

/* GET-RAW-NETWORK-INFO */
Object get_raw_network_info()
{
    Object temp, temp_1, network_addresses, type_of_network, address, secure_p;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, temp_2;

    x_note_fn_call(32,325);
    temp = get_local_host_name();
    if (temp);
    else
	temp = string_constant_39;
    temp_1 = copy_text_string(temp);
    network_addresses = get_local_host_addresses();
    type_of_network = Nil;
    address = Nil;
    secure_p = Nil;
    ab_loop_list_ = network_addresses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    type_of_network = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    address = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    secure_p = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_2 = copy_text_string(equalw(type_of_network,array_constant_43) ? 
	    array_constant_44 : array_constant_45);
    temp = tformat_text_string(2,string_constant_40,address);
    ab_loopvar__2 = gensym_cons_1(gensym_list_3(temp_2,temp,secure_p),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    reclaim_network_addresses(network_addresses);
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_2(temp_1,temp);
}

/* RECLAIM-RAW-NETWORK-INFO */
Object reclaim_raw_network_info(host_name,port_list)
    Object host_name, port_list;
{
    x_note_fn_call(32,326);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(host_name) != (SI_Long)0L)
	reclaim_wide_string(host_name);
    return reclaim_gensym_tree_with_text_strings(port_list);
}

/* ALLOCATE-MANAGED-SIMPLE-VECTOR-WITH-ZEROS */
Object allocate_managed_simple_vector_with_zeros(len)
    Object len;
{
    Object v;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(32,327);
    v = allocate_managed_simple_vector(len);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(sub1(len));
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    ISVREF(v,i) = FIX((SI_Long)0L);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(v);
}

/* READ-HEX-NUMBER-FROM-TEXT-STRING */
Object read_hex_number_from_text_string(str,si_init,ei_init)
    Object str, si_init, ei_init;
{
    Object number, result_1, temp, y, incf_arg;
    SI_Long si, ei, length_1, x, ab_loop_bind_, tmp, gensymed_symbol, i;
    SI_Long ab_loop_bind__1;

    x_note_fn_call(32,328);
    si = IFIX(si_init);
    ei = IFIX(ei_init);
    number = FIX((SI_Long)0L);
    ei = ei - (SI_Long)1L;
    si = si + (SI_Long)2L;
    if (UBYTE_16_ISAREF_1(str,(SI_Long)0L) == (SI_Long)48L && 
	    (UBYTE_16_ISAREF_1(str,(SI_Long)1L) == (SI_Long)120L || 
	    UBYTE_16_ISAREF_1(str,(SI_Long)1L) == (SI_Long)88L)) {
	result_1 = FIX((SI_Long)1L);
	length_1 = ei - si;
	x = (SI_Long)0L;
	ab_loop_bind_ = length_1;
      next_loop:
	if (x > ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(result_1))
	    goto end_loop;
	tmp = UBYTE_16_ISAREF_1(str,ei - x);
	gensymed_symbol = tmp;
	result_1 = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		(SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
	if ( !TRUEP(result_1)) {
	    if (tmp == (SI_Long)97L || tmp == (SI_Long)65L)
		result_1 = FIX((SI_Long)10L);
	    else if (tmp == (SI_Long)98L || tmp == (SI_Long)66L)
		result_1 = FIX((SI_Long)11L);
	    else if (tmp == (SI_Long)99L || tmp == (SI_Long)67L)
		result_1 = FIX((SI_Long)12L);
	    else if (tmp == (SI_Long)100L || tmp == (SI_Long)68L)
		result_1 = FIX((SI_Long)13L);
	    else if (tmp == (SI_Long)101L || tmp == (SI_Long)69L)
		result_1 = FIX((SI_Long)14L);
	    else if (tmp == (SI_Long)102L || tmp == (SI_Long)70L)
		result_1 = FIX((SI_Long)15L);
	    else if ( !TRUEP(result_1))
		number = FIX((SI_Long)0L);
	}
	if (result_1) {
	    temp = result_1;
	    y = FIX((SI_Long)1L);
	    i = (SI_Long)1L;
	    ab_loop_bind__1 = x;
	  next_loop_1:
	    if (i > ab_loop_bind__1)
		goto end_loop_1;
	    y = ltimes(y,FIX((SI_Long)16L));
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	    incf_arg = ltimes(temp,y);
	    number = add(number,incf_arg);
	}
	x = x + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(number);
}

void utilities3_INIT()
{
    Object temp, reclaim_structure_for_temporary_constant_1, integer;
    Object reclaim_structure_for_pending_activity_1;
    Object all_known_command_line_plist_elements_new_value;
    Object reclaim_structure_for_foreign_struct_info_1;
    Object reclaim_structure_for_eq_hash_table_1;
    SI_int64 long_1, zero;
    Object AB_package, Qeq_hash_table, Qreclaim_structure;
    Object Qoutstanding_eq_hash_table_count;
    Object Qeq_hash_table_structure_memory_usage, Qutilities2;
    Object string_constant_61, Qtype_description_of_type, string_constant_60;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qforeign_struct_info;
    Object Qoutstanding_foreign_struct_info_count;
    Object Qforeign_struct_info_structure_memory_usage, string_constant_59;
    Object string_constant_58, list_constant_46;
    Object Qget_command_line_plist_element_for_icp_log_intensity;
    Object Qcommand_line_process_icp_log_intensity, list_constant_45;
    Object Qget_command_line_plist_element_for_cert;
    Object Qcommand_line_process_cert, list_constant_44;
    Object Qget_command_line_plist_element_for_secure;
    Object Qcommand_line_process_secure, list_constant_43;
    Object Qget_command_line_plist_element_for_use_jit;
    Object Qcommand_line_process_use_jit, list_constant_42;
    Object Qget_command_line_plist_element_for_exit_on_abort;
    Object Qcommand_line_process_exit_on_abort, list_constant_41;
    Object Qget_command_line_plist_element_for_silent;
    Object Qcommand_line_process_silent, list_constant_40;
    Object Qget_command_line_plist_element_for_verbose;
    Object Qcommand_line_process_verbose, list_constant_39;
    Object Qget_command_line_plist_element_for_netinfo;
    Object Qcommand_line_process_netinfo, list_constant_38;
    Object Qget_command_line_plist_element_for_ui, Qcommand_line_process_ui;
    Object list_constant_37, Qknown_ui_styles, Qclassic, list_constant_36;
    Object Qget_command_line_plist_element_for_background;
    Object Qcommand_line_process_background, list_constant_35;
    Object Qget_command_line_plist_element_for_xclip;
    Object Qcommand_line_process_xclip, list_constant_34;
    Object Qget_command_line_plist_element_for_debug_frame_reference_balance;
    Object Qcommand_line_process_debug_frame_reference_balance;
    Object list_constant_33;
    Object Qget_command_line_plist_element_for_copy_logbook_on_console;
    Object Qcommand_line_process_copy_logbook_on_console, list_constant_32;
    Object Qget_command_line_plist_element_for_copy_messages_on_logbook;
    Object Qcommand_line_process_copy_messages_on_logbook, list_constant_31;
    Object Qget_command_line_plist_element_for_use_os_emulation;
    Object Qcommand_line_process_use_os_emulation, list_constant_30;
    Object Qget_command_line_plist_element_for_file_operation_timeout;
    Object Qcommand_line_process_file_operation_timeout, list_constant_29;
    Object Qget_command_line_plist_element_for_private_colormap;
    Object Qcommand_line_process_private_colormap, list_constant_28;
    Object Qget_command_line_plist_element_for_no_backing_store;
    Object Qcommand_line_process_no_backing_store, list_constant_27;
    Object Qget_command_line_plist_element_for_g2passwdexe;
    Object Qcommand_line_process_g2passwdexe, list_constant_26;
    Object Qget_command_line_plist_element_for_no_native_clipboard;
    Object Qcommand_line_process_no_native_clipboard, list_constant_25;
    Object Qget_command_line_plist_element_for_native_fonts;
    Object Qcommand_line_process_native_fonts, list_constant_24;
    Object Qget_command_line_plist_element_for_no_native_fonts;
    Object Qcommand_line_process_no_native_fonts, Qg2_5_dot_x, Qstandard_large;
    Object list_constant_23, Qget_command_line_plist_element_for_window_style;
    Object Qcommand_line_process_window_style, list_constant_22;
    Object Qget_command_line_plist_element_for_windowhandle;
    Object Qcommand_line_process_windowhandle, list_constant_21;
    Object Qget_command_line_plist_element_for_user_name;
    Object Qcommand_line_process_user_name, list_constant_20;
    Object Qget_command_line_plist_element_for_window;
    Object Qcommand_line_process_window, list_constant_19;
    Object Qget_command_line_plist_element_for_user_mode;
    Object Qcommand_line_process_user_mode, list_constant_18;
    Object Qget_command_line_plist_element_for_discard_user_settings;
    Object Qcommand_line_process_discard_user_settings, list_constant_17;
    Object Qget_command_line_plist_element_for_init_string;
    Object Qcommand_line_process_init_string, list_constant_16;
    Object Qget_command_line_plist_element_for_cjk_language;
    Object Qcommand_line_process_cjk_language, Qchinese_traditional;
    Object Qchinese_simplified, Qkorean, Qjapanese, Qchinese, list_constant_15;
    Object Qget_command_line_plist_element_for_language;
    Object Qcommand_line_process_language, list_constant_14;
    Object Qget_command_line_plist_element_for_password;
    Object Qcommand_line_process_password, list_constant_13, Qutilities3;
    Object Qcommand_line_arguments, Qget_initial_command_line_arguments;
    Object Kfuncall, Qpending_activity, Qoutstanding_pending_activity_count;
    Object Qpending_activity_structure_memory_usage, string_constant_57;
    Object string_constant_56, list_constant_12, list_constant_11;
    Object Qmake_region_from_rectangle, string_constant_55;
    Object Qregion_cons_memory_usage, Qoutstanding_region_conses, Qutilities1;
    Object list_constant_6, Qregion_cons_counter_vector, list_constant_5;
    Object Qavailable_region_conses_tail_vector;
    Object Qavailable_region_conses_vector, string_constant_54;
    Object string_constant_53, string_constant_52, string_constant_51;
    Object list_constant_10, list_constant_9, Qrandom_seed_3, Qrandom_seed_2;
    Object Qrandom_seed_1, Qrandom_seed_0, Qlarge_shift, Qlarge_mask;
    Object array_constant_57, array_constant_56, array_constant_55;
    Object array_constant_54, array_constant_53, array_constant_52;
    Object array_constant_51, array_constant_50, array_constant_49;
    Object array_constant_48, array_constant_47, array_constant_46;
    Object Qmaximum_length_of_g2_symbol_name, Qmost_positive_fixnum_floor_2;
    Object Qmost_negative_fixnum_ceiling_10, Qmost_positive_fixnum_floor_10;
    Object Qfalsity, Qtruth, Qget_memory_used_for_interned_text_strings;
    Object string_constant_50, string_constant_49, Qschedule;
    Object Qoutstanding_temporary_constant_count;
    Object Qtemporary_constant_structure_memory_usage, string_constant_48;
    Object string_constant_47, list_constant_8, Qallocate_managed_array;
    Object Qmask_for_ieee_exponent, string_constant_46;
    Object Qoutstanding_simple_long_array_pool_arrays, Qutilities0;
    Object list_constant_7, string_constant_45, Qlong_array_cons_memory_usage;
    Object Qoutstanding_long_array_conses, Qlong_array_cons_counter_vector;
    Object Qavailable_long_array_conses_tail_vector;
    Object Qavailable_long_array_conses_vector;
    Object Qmaximum_managed_simple_long_array_size;
    Object Qmaximum_managed_float_array_size;
    Object Qmaximum_managed_float_array_buffer_size, Qmanaged_float_array;
    Object string_constant_44, Qoversized_sflap_memory_usage;
    Object Qoutstanding_oversized_simple_float_array_pool_arrays;
    Object string_constant_43, Qsflap_memory_usage;
    Object Qoutstanding_simple_float_array_pool_arrays;
    Object Qallocate_initial_vector_of_simple_float_array_pools;
    Object string_constant_42, Qfloat_array_cons_memory_usage;
    Object Qoutstanding_float_array_conses, Qfloat_array_cons_counter_vector;
    Object Qmake_thread_array, Qavailable_float_array_conses_tail_vector;
    Object Qavailable_float_array_conses_vector;
    Object Qmaximum_oversized_managed_simple_float_array_size;
    Object Qmaximum_managed_simple_float_array_size, string_constant_41;

    x_note_fn_call(32,329);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qno_arg = STATIC_SYMBOL("NO-ARG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qno_arg,No_arg);
    if (No_arg == UNBOUND)
	No_arg = LIST_1(Qno_arg);
    if (Write_console_p == UNBOUND)
	Write_console_p = Nil;
    Qiso_8859_1_gensym_string = STATIC_SYMBOL("ISO-8859-1-GENSYM-STRING",
	    AB_package);
    string_constant_41 = STATIC_STRING("the ~(~A~) ");
    if (Actual_arg == UNBOUND)
	Actual_arg = string_constant_41;
    float_constant = STATIC_FLOAT(0.0);
    Floating_zero = float_constant;
    Qmaximum_managed_simple_float_array_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-SIMPLE-FLOAT-ARRAY-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_managed_simple_float_array_size,
	    FIX((SI_Long)1024L));
    Qmaximum_oversized_managed_simple_float_array_size = 
	    STATIC_SYMBOL("MAXIMUM-OVERSIZED-MANAGED-SIMPLE-FLOAT-ARRAY-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_oversized_managed_simple_float_array_size,
	    FIX((SI_Long)1048576L));
    Qavailable_float_array_conses = 
	    STATIC_SYMBOL("AVAILABLE-FLOAT-ARRAY-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_float_array_conses,
	    Available_float_array_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_float_array_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_float_array_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-FLOAT-ARRAY-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_float_array_conses_tail,
	    Available_float_array_conses_tail);
    record_system_variable(Qavailable_float_array_conses_tail,Qutilities1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_float_array_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-FLOAT-ARRAY-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_float_array_conses_vector,
	    Available_float_array_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_float_array_conses_vector,
	    Qutilities1,list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qavailable_float_array_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-FLOAT-ARRAY-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_float_array_conses_tail_vector,
	    Available_float_array_conses_tail_vector);
    record_system_variable(Qavailable_float_array_conses_tail_vector,
	    Qutilities1,list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qfloat_array_cons_counter_vector = 
	    STATIC_SYMBOL("FLOAT-ARRAY-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfloat_array_cons_counter_vector,
	    Float_array_cons_counter_vector);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qfloat_array_cons_counter_vector,Qutilities1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qfloat_array_cons_counter = STATIC_SYMBOL("FLOAT-ARRAY-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfloat_array_cons_counter,
	    Float_array_cons_counter);
    record_system_variable(Qfloat_array_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_float_array_conses = 
	    STATIC_SYMBOL("OUTSTANDING-FLOAT-ARRAY-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_float_array_conses,
	    STATIC_FUNCTION(outstanding_float_array_conses,NIL,FALSE,0,0));
    Qfloat_array_cons_memory_usage = 
	    STATIC_SYMBOL("FLOAT-ARRAY-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qfloat_array_cons_memory_usage,
	    STATIC_FUNCTION(float_array_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_42 = STATIC_STRING("1q83-UDy9k83-UCy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_float_array_conses);
    push_optimized_constant(Qfloat_array_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_42));
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qvector_of_simple_float_array_pools = 
	    STATIC_SYMBOL("VECTOR-OF-SIMPLE-FLOAT-ARRAY-POOLS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvector_of_simple_float_array_pools,
	    Vector_of_simple_float_array_pools);
    Qutilities0 = STATIC_SYMBOL("UTILITIES0",AB_package);
    Qallocate_initial_vector_of_simple_float_array_pools = 
	    STATIC_SYMBOL("ALLOCATE-INITIAL-VECTOR-OF-SIMPLE-FLOAT-ARRAY-POOLS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qallocate_initial_vector_of_simple_float_array_pools,
	    STATIC_FUNCTION(allocate_initial_vector_of_simple_float_array_pools,
	    NIL,FALSE,0,0));
    list_constant_7 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qallocate_initial_vector_of_simple_float_array_pools);
    record_system_variable(Qvector_of_simple_float_array_pools,Qutilities0,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qvector_of_oversized_simple_float_array_pools = 
	    STATIC_SYMBOL("VECTOR-OF-OVERSIZED-SIMPLE-FLOAT-ARRAY-POOLS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvector_of_oversized_simple_float_array_pools,
	    Vector_of_oversized_simple_float_array_pools);
    record_system_variable(Qvector_of_oversized_simple_float_array_pools,
	    Qutilities0,list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcreated_simple_float_array_pool_arrays,
	    Created_simple_float_array_pool_arrays);
    record_system_variable(Qcreated_simple_float_array_pool_arrays,
	    Qutilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qcreated_oversized_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-OVERSIZED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcreated_oversized_simple_float_array_pool_arrays,
	    Created_oversized_simple_float_array_pool_arrays);
    record_system_variable(Qcreated_oversized_simple_float_array_pool_arrays,
	    Qutilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimple_float_array_pool_memory_usage,
	    Simple_float_array_pool_memory_usage);
    record_system_variable(Qsimple_float_array_pool_memory_usage,
	    Qutilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoversized_simple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("OVERSIZED-SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoversized_simple_float_array_pool_memory_usage,
	    Oversized_simple_float_array_pool_memory_usage);
    record_system_variable(Qoversized_simple_float_array_pool_memory_usage,
	    Qutilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("OUTSTANDING-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_simple_float_array_pool_arrays,
	    STATIC_FUNCTION(outstanding_simple_float_array_pool_arrays,NIL,
	    FALSE,0,0));
    Qsflap_memory_usage = STATIC_SYMBOL("SFLAP-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qsflap_memory_usage,
	    STATIC_FUNCTION(sflap_memory_usage,NIL,FALSE,0,0));
    string_constant_43 = STATIC_STRING("1q83-dby1m83a1y83-+ky83t9y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_simple_float_array_pool_arrays);
    push_optimized_constant(Qsflap_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_43));
    Qoutstanding_oversized_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("OUTSTANDING-OVERSIZED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_oversized_simple_float_array_pool_arrays,
	    STATIC_FUNCTION(outstanding_oversized_simple_float_array_pool_arrays,
	    NIL,FALSE,0,0));
    Qoversized_sflap_memory_usage = 
	    STATIC_SYMBOL("OVERSIZED-SFLAP-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qoversized_sflap_memory_usage,
	    STATIC_FUNCTION(oversized_sflap_memory_usage,NIL,FALSE,0,0));
    string_constant_44 = STATIC_STRING("1q83-day1m83a1y83-+ky83-POy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_oversized_simple_float_array_pool_arrays);
    push_optimized_constant(Qoversized_sflap_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_44));
    Replenished_simple_float_array_size_limit = FIX((SI_Long)10L);
    Replenished_simple_float_arrays_to_make_at_a_time = FIX((SI_Long)10L);
    Qmanaged_simple_float_array = 
	    STATIC_SYMBOL("MANAGED-SIMPLE-FLOAT-ARRAY",AB_package);
    Qmanaged_float_array = STATIC_SYMBOL("MANAGED-FLOAT-ARRAY",AB_package);
    if (Managed_float_array_unique_marker == UNBOUND)
	Managed_float_array_unique_marker = CONS(Qmanaged_float_array,Nil);
    Qmaximum_managed_float_array_buffer_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-FLOAT-ARRAY-BUFFER-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_managed_float_array_buffer_size,
	    FIX((SI_Long)1024L));
    Qmaximum_managed_float_array_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-FLOAT-ARRAY-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_managed_float_array_size,FIX((SI_Long)1046528L));
    if (Bytes_per_double_float_simple_array_cached == UNBOUND)
	Bytes_per_double_float_simple_array_cached = 
		bytes_per_double_float_simple_array(FIX((SI_Long)1L));
    list_constant = STATIC_LIST((SI_Long)2L,Qsigned_byte,FIX((SI_Long)64L));
    Qmaximum_managed_simple_long_array_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-SIMPLE-LONG-ARRAY-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_managed_simple_long_array_size,
	    FIX((SI_Long)1024L));
    Qavailable_long_array_conses = 
	    STATIC_SYMBOL("AVAILABLE-LONG-ARRAY-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_long_array_conses,
	    Available_long_array_conses);
    record_system_variable(Qavailable_long_array_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_long_array_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-LONG-ARRAY-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_long_array_conses_tail,
	    Available_long_array_conses_tail);
    record_system_variable(Qavailable_long_array_conses_tail,Qutilities1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_long_array_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-LONG-ARRAY-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_long_array_conses_vector,
	    Available_long_array_conses_vector);
    record_system_variable(Qavailable_long_array_conses_vector,Qutilities1,
	    list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qavailable_long_array_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-LONG-ARRAY-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_long_array_conses_tail_vector,
	    Available_long_array_conses_tail_vector);
    record_system_variable(Qavailable_long_array_conses_tail_vector,
	    Qutilities1,list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qlong_array_cons_counter_vector = 
	    STATIC_SYMBOL("LONG-ARRAY-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlong_array_cons_counter_vector,
	    Long_array_cons_counter_vector);
    record_system_variable(Qlong_array_cons_counter_vector,Qutilities1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qlong_array_cons_counter = STATIC_SYMBOL("LONG-ARRAY-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlong_array_cons_counter,
	    Long_array_cons_counter);
    record_system_variable(Qlong_array_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_long_array_conses = 
	    STATIC_SYMBOL("OUTSTANDING-LONG-ARRAY-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_long_array_conses,
	    STATIC_FUNCTION(outstanding_long_array_conses,NIL,FALSE,0,0));
    Qlong_array_cons_memory_usage = 
	    STATIC_SYMBOL("LONG-ARRAY-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qlong_array_cons_memory_usage,
	    STATIC_FUNCTION(long_array_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_45 = STATIC_STRING("1q83-dHy9k83-dGy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_long_array_conses);
    push_optimized_constant(Qlong_array_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_45));
    Qlong_array = STATIC_SYMBOL("LONG-ARRAY",AB_package);
    Qvector_of_simple_long_array_pools = 
	    STATIC_SYMBOL("VECTOR-OF-SIMPLE-LONG-ARRAY-POOLS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvector_of_simple_long_array_pools,
	    Vector_of_simple_long_array_pools);
    record_system_variable(Qvector_of_simple_long_array_pools,Qutilities0,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qcreated_simple_long_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-LONG-ARRAY-POOL-ARRAYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcreated_simple_long_array_pool_arrays,
	    Created_simple_long_array_pool_arrays);
    record_system_variable(Qcreated_simple_long_array_pool_arrays,
	    Qutilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qsimple_long_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-LONG-ARRAY-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimple_long_array_pool_memory_usage,
	    Simple_long_array_pool_memory_usage);
    record_system_variable(Qsimple_long_array_pool_memory_usage,
	    Qutilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qsimple_long_array_pool_memory_usage,
	    STATIC_FUNCTION(simple_long_array_pool_memory_usage,NIL,FALSE,
	    0,0));
    Qoutstanding_simple_long_array_pool_arrays = 
	    STATIC_SYMBOL("OUTSTANDING-SIMPLE-LONG-ARRAY-POOL-ARRAYS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_simple_long_array_pool_arrays,
	    STATIC_FUNCTION(outstanding_simple_long_array_pool_arrays,NIL,
	    FALSE,0,0));
    string_constant_46 = STATIC_STRING("1q83-dcy1m83a1y83-WGy83t9y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_simple_long_array_pool_arrays);
    push_optimized_constant(Qsimple_long_array_pool_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_46));
    Replenished_simple_long_array_size_limit = FIX((SI_Long)10L);
    Replenished_simple_long_arrays_to_make_at_a_time = FIX((SI_Long)10L);
    Qmanaged_simple_long_array = STATIC_SYMBOL("MANAGED-SIMPLE-LONG-ARRAY",
	    AB_package);
    if (Bytes_per_long_simple_array_cached == UNBOUND)
	Bytes_per_long_simple_array_cached = 
		bytes_per_long_simple_array(FIX((SI_Long)1L));
    Qgensym_float = STATIC_SYMBOL("GENSYM-FLOAT",AB_package);
    float_constant_1 = STATIC_FLOAT(-1.0);
    float_constant_2 = STATIC_FLOAT(1.0);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    if (Partition_float_union == UNBOUND)
	Partition_float_union = make_partition_float_or_long_union();
    if (Partition_long_union == UNBOUND)
	Partition_long_union = make_partition_float_or_long_union();
    Qmask_for_ieee_exponent = STATIC_SYMBOL("MASK-FOR-IEEE-EXPONENT",
	    AB_package);
    SET_SYMBOL_VALUE(Qmask_for_ieee_exponent,FIX((SI_Long)32752L));
    Qvms = STATIC_SYMBOL("VMS",AB_package);
    Qmanaged_bignum_pool = STATIC_SYMBOL("MANAGED-BIGNUM-POOL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmanaged_bignum_pool,Managed_bignum_pool);
    Qutilities3 = STATIC_SYMBOL("UTILITIES3",AB_package);
    Qallocate_managed_array = STATIC_SYMBOL("ALLOCATE-MANAGED-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qallocate_managed_array,
	    STATIC_FUNCTION(allocate_managed_array,NIL,TRUE,1,3));
    list_constant_8 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qallocate_managed_array,FIX((SI_Long)10L));
    record_system_variable(Qmanaged_bignum_pool,Qutilities3,
	    list_constant_8,Qnil,Qnil,Qnil,Qnil);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtemporary_constant = STATIC_SYMBOL("TEMPORARY-CONSTANT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_temporary_constant_g2_struct,
	    Qtemporary_constant,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qtemporary_constant,
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_temporary_constant == UNBOUND)
	The_type_description_of_temporary_constant = Nil;
    string_constant_47 = 
	    STATIC_STRING("43Dy8m83nhy1n83nhy8n8k1l8n0000001l1n8y83-64y1m83t1y83t0yknk0k0");
    temp = The_type_description_of_temporary_constant;
    The_type_description_of_temporary_constant = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_47));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_temporary_constant_g2_struct,
	    The_type_description_of_temporary_constant,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qtemporary_constant,
	    The_type_description_of_temporary_constant,
	    Qtype_description_of_type);
    Qoutstanding_temporary_constant_count = 
	    STATIC_SYMBOL("OUTSTANDING-TEMPORARY-CONSTANT-COUNT",AB_package);
    Qtemporary_constant_structure_memory_usage = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_48 = STATIC_STRING("1q83nhy8s83-sKy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_temporary_constant_count);
    push_optimized_constant(Qtemporary_constant_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_48));
    Qchain_of_available_temporary_constants = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TEMPORARY-CONSTANTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_temporary_constants,
	    Chain_of_available_temporary_constants);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_temporary_constants,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qtemporary_constant_count = STATIC_SYMBOL("TEMPORARY-CONSTANT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtemporary_constant_count,
	    Temporary_constant_count);
    record_system_variable(Qtemporary_constant_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_temporary_constants_vector == UNBOUND)
	Chain_of_available_temporary_constants_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtemporary_constant_structure_memory_usage,
	    STATIC_FUNCTION(temporary_constant_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_temporary_constant_count,
	    STATIC_FUNCTION(outstanding_temporary_constant_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_temporary_constant_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_temporary_constant,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtemporary_constant,
	    reclaim_structure_for_temporary_constant_1);
    Qrecycled_resumption_conses = 
	    STATIC_SYMBOL("RECYCLED-RESUMPTION-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrecycled_resumption_conses,
	    Recycled_resumption_conses);
    Qschedule = STATIC_SYMBOL("SCHEDULE",AB_package);
    record_system_variable(Qrecycled_resumption_conses,Qschedule,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qcount_of_interned_gensym_strings = 
	    STATIC_SYMBOL("COUNT-OF-INTERNED-GENSYM-STRINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_interned_gensym_strings,
	    Count_of_interned_gensym_strings);
    record_system_variable(Qcount_of_interned_gensym_strings,Qutilities3,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qmemory_used_for_interned_gensym_strings = 
	    STATIC_SYMBOL("MEMORY-USED-FOR-INTERNED-GENSYM-STRINGS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmemory_used_for_interned_gensym_strings,
	    Memory_used_for_interned_gensym_strings);
    record_system_variable(Qmemory_used_for_interned_gensym_strings,
	    Qutilities3,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    string_constant_49 = STATIC_STRING("NIL");
    if (Nil_interned == UNBOUND)
	Nil_interned = intern(string_constant_49,_);
    Qget_memory_used_for_interned_text_strings = 
	    STATIC_SYMBOL("GET-MEMORY-USED-FOR-INTERNED-TEXT-STRINGS",
	    AB_package);
    string_constant_50 = STATIC_STRING("1q83-vjy83-2y83-Oxy83-Oxy09k");
    clear_optimized_constants();
    push_optimized_constant(Qget_memory_used_for_interned_text_strings);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_50));
    SET_SYMBOL_FUNCTION(Qget_memory_used_for_interned_text_strings,
	    STATIC_FUNCTION(get_memory_used_for_interned_text_strings,NIL,
	    FALSE,0,0));
    Qtruth = STATIC_SYMBOL("TRUTH",AB_package);
    SET_SYMBOL_VALUE(Qtruth,FIX((SI_Long)1000L));
    Qfalsity = STATIC_SYMBOL("FALSITY",AB_package);
    SET_SYMBOL_VALUE(Qfalsity,FIX((SI_Long)-1000L));
    Qmost_positive_fixnum_floor_10 = 
	    STATIC_SYMBOL("MOST-POSITIVE-FIXNUM-FLOOR-10",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_positive_fixnum_floor_10,
	    Most_positive_fixnum_floor_10);
    SET_SYMBOL_VALUE(Qmost_positive_fixnum_floor_10,
	    chestnut_floorf_function(Most_positive_fixnum,FIX((SI_Long)10L)));
    Qmost_negative_fixnum_ceiling_10 = 
	    STATIC_SYMBOL("MOST-NEGATIVE-FIXNUM-CEILING-10",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_negative_fixnum_ceiling_10,
	    Most_negative_fixnum_ceiling_10);
    SET_SYMBOL_VALUE(Qmost_negative_fixnum_ceiling_10,
	    ceiling(Most_negative_fixnum,FIX((SI_Long)10L)));
    string_constant = STATIC_STRING("number is too large");
    string_constant_1 = STATIC_STRING("negative number is too large");
    integer = timesn(3,FIX((SI_Long)66024901L),FIX((SI_Long)77608531L),
	    FIX((SI_Long)180L));
    long_1 = INTEGER_TO_INT64(integer);
    zero = (SI_int64)(SI_Long)0L;
    Most_positive_int64_floor_10 = add(INT64_TO_INTEGER(long_1),
	    INT64_TO_INTEGER(zero));
    Qoverflow = STATIC_SYMBOL("OVERFLOW",AB_package);
    integer = ltimes(ltimes(FIX((SI_Long)66024901L),
	    FIX((SI_Long)77608531L)),FIX((SI_Long)-180L));
    long_1 = INTEGER_TO_INT64(integer);
    zero = (SI_int64)(SI_Long)0L;
    Most_negative_int64_ceiling_10 = add(INT64_TO_INTEGER(long_1),
	    INT64_TO_INTEGER(zero));
    Qunderflow = STATIC_SYMBOL("UNDERFLOW",AB_package);
    Qmost_positive_fixnum_floor_2 = 
	    STATIC_SYMBOL("MOST-POSITIVE-FIXNUM-FLOOR-2",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_positive_fixnum_floor_2,
	    Most_positive_fixnum_floor_2);
    SET_SYMBOL_VALUE(Qmost_positive_fixnum_floor_2,
	    chestnut_floorf_function(Most_positive_fixnum,FIX((SI_Long)2L)));
    float_constant_3 = STATIC_FLOAT(308.25471127925886);
    string_constant_2 = STATIC_STRING("exponent of number is out of range");
    Qmaximum_length_of_g2_symbol_name = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-OF-G2-SYMBOL-NAME",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_length_of_g2_symbol_name,FIX((SI_Long)5000L));
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_3 = STATIC_STRING("symbol is too big");
    Knil = STATIC_SYMBOL("NIL",Pkeyword);
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)35L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)36L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)41L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)43L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)44L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)45L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)46L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)47L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)48L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)54L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)55L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)32L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)35L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)37L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)41L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)42L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)43L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)45L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)46L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)54L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)55L,(SI_Long)57344L);
    array_constant_46 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)0L,(SI_Long)74L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)7L,(SI_Long)57344L);
    array_constant_47 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)7L,(SI_Long)57344L);
    array_constant_48 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)7L,(SI_Long)57344L);
    array_constant_49 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)7L,(SI_Long)57344L);
    array_constant_50 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)2L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)7L,(SI_Long)57344L);
    array_constant_51 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)0L,(SI_Long)74L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)7L,(SI_Long)57344L);
    array_constant_52 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)0L,(SI_Long)74L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)7L,(SI_Long)57344L);
    array_constant_53 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)7L,(SI_Long)57344L);
    array_constant_54 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)7L,(SI_Long)57344L);
    array_constant_55 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)7L,(SI_Long)57344L);
    array_constant_56 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)7L,(SI_Long)57344L);
    array_constant_57 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)7L,(SI_Long)57344L);
    list_constant_2 = STATIC_LIST((SI_Long)12L,array_constant_46,
	    array_constant_47,array_constant_48,array_constant_49,
	    array_constant_50,array_constant_51,array_constant_52,
	    array_constant_53,array_constant_54,array_constant_55,
	    array_constant_56,array_constant_57);
    array_constant_4 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    Qlarge_mask = STATIC_SYMBOL("LARGE-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlarge_mask,Large_mask);
    SET_SYMBOL_VALUE(Qlarge_mask,FIXNUM_SUB1(FIX((SI_Long)8388608L)));
    Qlarge_shift = STATIC_SYMBOL("LARGE-SHIFT",AB_package);
    SET_SYMBOL_VALUE(Qlarge_shift,FIX((SI_Long)23L));
    if (Random_state_array == UNBOUND)
	Random_state_array = Nil;
    if (Random_state_array_current_pointer == UNBOUND)
	Random_state_array_current_pointer = FIX((SI_Long)54L);
    if (Random_state_array_24_pointer == UNBOUND)
	Random_state_array_24_pointer = FIX((SI_Long)24L);
    Qrandom_seed_0 = STATIC_SYMBOL("RANDOM-SEED-0",AB_package);
    SET_SYMBOL_VALUE(Qrandom_seed_0,FIX((SI_Long)6460045L));
    Qrandom_seed_1 = STATIC_SYMBOL("RANDOM-SEED-1",AB_package);
    SET_SYMBOL_VALUE(Qrandom_seed_1,FIX((SI_Long)4757733L));
    Qrandom_seed_2 = STATIC_SYMBOL("RANDOM-SEED-2",AB_package);
    SET_SYMBOL_VALUE(Qrandom_seed_2,FIX((SI_Long)6397164L));
    Qrandom_seed_3 = STATIC_SYMBOL("RANDOM-SEED-3",AB_package);
    SET_SYMBOL_VALUE(Qrandom_seed_3,FIX((SI_Long)7884262L));
    if (Random_variation == UNBOUND)
	Random_variation = FIX((SI_Long)0L);
    if (Random_variation_2 == UNBOUND)
	Random_variation_2 = FIX((SI_Long)0L);
    if (User_random_seed_qm == UNBOUND)
	User_random_seed_qm = Nil;
    reset_g2_random_state(Nil);
    Qsimple_type_specification = STATIC_SYMBOL("SIMPLE-TYPE-SPECIFICATION",
	    AB_package);
    Simple_type_specification_prop = Qsimple_type_specification;
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qsatisfies,Qsymbolp);
    mutate_global_property(Qsymbol,list_constant_9,Qsimple_type_specification);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qsatisfies,Qconsp);
    mutate_global_property(Qcons,list_constant_10,Qsimple_type_specification);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Qmanaged_number = STATIC_SYMBOL("MANAGED-NUMBER",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qtype_error_printer = STATIC_SYMBOL("TYPE-ERROR-PRINTER",AB_package);
    Type_error_printer_prop = Qtype_error_printer;
    string_constant_51 = STATIC_STRING("neither true nor false");
    mutate_global_property(Qboolean,string_constant_51,Qtype_error_printer);
    string_constant_52 = STATIC_STRING("not a symbol");
    mutate_global_property(Qsymbol,string_constant_52,Qtype_error_printer);
    string_constant_53 = STATIC_STRING("not a simple integer");
    mutate_global_property(Qfixnum,string_constant_53,Qtype_error_printer);
    string_constant_54 = STATIC_STRING("not a number");
    mutate_global_property(Qgensym_float,string_constant_54,
	    Qtype_error_printer);
    mutate_global_property(Qmanaged_number,string_constant_54,
	    Qtype_error_printer);
    mutate_global_property(Qtemporary_constant,string_constant_54,
	    Qtype_error_printer);
    string_constant_4 = STATIC_STRING("~(~A is ~)");
    Qmanaged_float = STATIC_SYMBOL("MANAGED-FLOAT",AB_package);
    Qslot_value_float = STATIC_SYMBOL("SLOT-VALUE-FLOAT",AB_package);
    string_constant_5 = STATIC_STRING(" not a number.");
    string_constant_6 = STATIC_STRING("~A.");
    string_constant_7 = STATIC_STRING("~( not ~A~A~).");
    string_constant_8 = STATIC_STRING(".");
    string_constant_9 = STATIC_STRING("~(not ~A~).");
    string_constant_10 = STATIC_STRING("~( neither ~A nor ~A~).");
    string_constant_11 = STATIC_STRING("not one of ");
    string_constant_12 = STATIC_STRING("~(~A~)");
    string_constant_13 = STATIC_STRING(", or ");
    string_constant_14 = STATIC_STRING(", ");
    string_constant_15 = 
	    STATIC_STRING("~(not an appropriate value (e.g., ~A, ~A, etc.)~)");
    Qsimple_type_writer = STATIC_SYMBOL("SIMPLE-TYPE-WRITER",AB_package);
    Simple_type_writer_prop = Qsimple_type_writer;
    string_constant_16 = STATIC_STRING("~(~S~)");
    Qavailable_region_conses = STATIC_SYMBOL("AVAILABLE-REGION-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_region_conses,
	    Available_region_conses);
    record_system_variable(Qavailable_region_conses,Qutilities1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_region_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-REGION-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_region_conses_tail,
	    Available_region_conses_tail);
    record_system_variable(Qavailable_region_conses_tail,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_region_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-REGION-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_region_conses_vector,
	    Available_region_conses_vector);
    record_system_variable(Qavailable_region_conses_vector,Qutilities1,
	    list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qavailable_region_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-REGION-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_region_conses_tail_vector,
	    Available_region_conses_tail_vector);
    record_system_variable(Qavailable_region_conses_tail_vector,
	    Qutilities1,list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qregion_cons_counter_vector = 
	    STATIC_SYMBOL("REGION-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qregion_cons_counter_vector,
	    Region_cons_counter_vector);
    record_system_variable(Qregion_cons_counter_vector,Qutilities1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qregion_cons_counter = STATIC_SYMBOL("REGION-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qregion_cons_counter,Region_cons_counter);
    record_system_variable(Qregion_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_region_conses = STATIC_SYMBOL("OUTSTANDING-REGION-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_region_conses,
	    STATIC_FUNCTION(outstanding_region_conses,NIL,FALSE,0,0));
    Qregion_cons_memory_usage = STATIC_SYMBOL("REGION-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qregion_cons_memory_usage,
	    STATIC_FUNCTION(region_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_55 = STATIC_STRING("1q83-lpy9k83-loy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_region_conses);
    push_optimized_constant(Qregion_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_55));
    Qregion = STATIC_SYMBOL("REGION",AB_package);
    Qscratch_rectangle_region = STATIC_SYMBOL("SCRATCH-RECTANGLE-REGION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qscratch_rectangle_region,
	    Scratch_rectangle_region);
    Qmake_region_from_rectangle = 
	    STATIC_SYMBOL("MAKE-REGION-FROM-RECTANGLE",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_region_from_rectangle,
	    STATIC_FUNCTION(make_region_from_rectangle,NIL,FALSE,4,4));
    list_constant_11 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_12 = STATIC_LIST_STAR((SI_Long)6L,Kfuncall,
	    Qmake_region_from_rectangle,FIX((SI_Long)0L),FIX((SI_Long)0L),
	    FIX((SI_Long)0L),list_constant_11);
    record_system_variable(Qscratch_rectangle_region,Qutilities3,
	    list_constant_12,Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_pending_activity_g2_struct = 
	    STATIC_SYMBOL("PENDING-ACTIVITY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpending_activity = STATIC_SYMBOL("PENDING-ACTIVITY",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_pending_activity_g2_struct,
	    Qpending_activity,Qab_name_of_unique_structure_type);
    mutate_global_property(Qpending_activity,
	    Qg2_defstruct_structure_name_pending_activity_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_pending_activity == UNBOUND)
	The_type_description_of_pending_activity = Nil;
    string_constant_56 = 
	    STATIC_STRING("43Dy8m83EJy1n83EJy8n8k1l8n0000001l1n8y83-52y1n83Xay83WEy83Inykqk0k0");
    temp = The_type_description_of_pending_activity;
    The_type_description_of_pending_activity = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_56));
    mutate_global_property(Qg2_defstruct_structure_name_pending_activity_g2_struct,
	    The_type_description_of_pending_activity,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qpending_activity,
	    The_type_description_of_pending_activity,
	    Qtype_description_of_type);
    Qoutstanding_pending_activity_count = 
	    STATIC_SYMBOL("OUTSTANDING-PENDING-ACTIVITY-COUNT",AB_package);
    Qpending_activity_structure_memory_usage = 
	    STATIC_SYMBOL("PENDING-ACTIVITY-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_57 = STATIC_STRING("1q83EJy8s83-ihy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_pending_activity_count);
    push_optimized_constant(Qpending_activity_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_57));
    Qchain_of_available_pending_activitys = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PENDING-ACTIVITYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_pending_activitys,
	    Chain_of_available_pending_activitys);
    record_system_variable(Qchain_of_available_pending_activitys,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qpending_activity_count = STATIC_SYMBOL("PENDING-ACTIVITY-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpending_activity_count,Pending_activity_count);
    record_system_variable(Qpending_activity_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_pending_activitys_vector == UNBOUND)
	Chain_of_available_pending_activitys_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qpending_activity_structure_memory_usage,
	    STATIC_FUNCTION(pending_activity_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_pending_activity_count,
	    STATIC_FUNCTION(outstanding_pending_activity_count,NIL,FALSE,0,0));
    reclaim_structure_for_pending_activity_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_pending_activity,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qpending_activity,
	    reclaim_structure_for_pending_activity_1);
    Kfinished = STATIC_SYMBOL("FINISHED",Pkeyword);
    Kcanceled = STATIC_SYMBOL("CANCELED",Pkeyword);
    array_constant_6 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    if (Cached_gensym_user_home_directory == UNBOUND)
	Cached_gensym_user_home_directory = Nil;
    Qall_command_line_keyword_arguments = 
	    STATIC_SYMBOL("ALL-COMMAND-LINE-KEYWORD-ARGUMENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qall_command_line_keyword_arguments,
	    All_command_line_keyword_arguments);
    record_system_variable(Qall_command_line_keyword_arguments,Qutilities3,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qcommand_line_plist_element_getter = 
	    STATIC_SYMBOL("COMMAND-LINE-PLIST-ELEMENT-GETTER",AB_package);
    Command_line_plist_element_getter_prop = 
	    Qcommand_line_plist_element_getter;
    Qcommand_line_argument_processor = 
	    STATIC_SYMBOL("COMMAND-LINE-ARGUMENT-PROCESSOR",AB_package);
    Command_line_argument_processor_prop = Qcommand_line_argument_processor;
    if (All_known_command_line_plist_elements == UNBOUND)
	All_known_command_line_plist_elements = Nil;
    Qcommand_line_arguments = STATIC_SYMBOL("COMMAND-LINE-ARGUMENTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcommand_line_arguments,Command_line_arguments);
    Qget_initial_command_line_arguments = 
	    STATIC_SYMBOL("GET-INITIAL-COMMAND-LINE-ARGUMENTS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_initial_command_line_arguments,
	    STATIC_FUNCTION(get_initial_command_line_arguments,NIL,FALSE,0,0));
    list_constant_13 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qget_initial_command_line_arguments);
    record_system_variable(Qcommand_line_arguments,Qutilities3,
	    list_constant_13,Qnil,Qnil,Qnil,Qnil);
    Qcommand_line_process_password = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-PASSWORD",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_password,
	    STATIC_FUNCTION(command_line_process_password,NIL,FALSE,1,1));
    Qpassword = STATIC_SYMBOL("PASSWORD",AB_package);
    mutate_global_property(Qpassword,Qcommand_line_process_password,
	    Qcommand_line_argument_processor);
    array_constant_7 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_password = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-PASSWORD",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_password,
	    STATIC_FUNCTION(get_command_line_plist_element_for_password,
	    NIL,FALSE,0,0));
    mutate_global_property(Qpassword,
	    Qget_command_line_plist_element_for_password,
	    Qcommand_line_plist_element_getter);
    list_constant_14 = STATIC_CONS(Qpassword,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_14,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_language = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-LANGUAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_language,
	    STATIC_FUNCTION(command_line_process_language,NIL,FALSE,1,1));
    Qlanguage = STATIC_SYMBOL("LANGUAGE",AB_package);
    mutate_global_property(Qlanguage,Qcommand_line_process_language,
	    Qcommand_line_argument_processor);
    array_constant_8 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_language = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-LANGUAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_language,
	    STATIC_FUNCTION(get_command_line_plist_element_for_language,
	    NIL,FALSE,0,0));
    mutate_global_property(Qlanguage,
	    Qget_command_line_plist_element_for_language,
	    Qcommand_line_plist_element_getter);
    list_constant_15 = STATIC_CONS(Qlanguage,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_15,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qchinese = STATIC_SYMBOL("CHINESE",AB_package);
    Qjapanese = STATIC_SYMBOL("JAPANESE",AB_package);
    Qkorean = STATIC_SYMBOL("KOREAN",AB_package);
    Qchinese_simplified = STATIC_SYMBOL("CHINESE-SIMPLIFIED",AB_package);
    Qchinese_traditional = STATIC_SYMBOL("CHINESE-TRADITIONAL",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)5L,Qchinese,Qjapanese,Qkorean,
	    Qchinese_simplified,Qchinese_traditional);
    string_constant_17 = 
	    STATIC_STRING("Note: ~A is not valid for the -cjk-language option.~\n         ~%It should be either Chinese, Japanese, or Korean.");
    Qcommand_line_process_cjk_language = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-CJK-LANGUAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_cjk_language,
	    STATIC_FUNCTION(command_line_process_cjk_language,NIL,FALSE,1,1));
    Qcjk_language = STATIC_SYMBOL("CJK-LANGUAGE",AB_package);
    mutate_global_property(Qcjk_language,
	    Qcommand_line_process_cjk_language,
	    Qcommand_line_argument_processor);
    array_constant_9 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)74L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_cjk_language = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-CJK-LANGUAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_cjk_language,
	    STATIC_FUNCTION(get_command_line_plist_element_for_cjk_language,
	    NIL,FALSE,0,0));
    mutate_global_property(Qcjk_language,
	    Qget_command_line_plist_element_for_cjk_language,
	    Qcommand_line_plist_element_getter);
    list_constant_16 = STATIC_CONS(Qcjk_language,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_16,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_init_string = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-INIT-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_init_string,
	    STATIC_FUNCTION(command_line_process_init_string,NIL,FALSE,1,1));
    Qinit_string = STATIC_SYMBOL("INIT-STRING",AB_package);
    mutate_global_property(Qinit_string,Qcommand_line_process_init_string,
	    Qcommand_line_argument_processor);
    array_constant_10 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_init_string = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-INIT-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_init_string,
	    STATIC_FUNCTION(get_command_line_plist_element_for_init_string,
	    NIL,FALSE,0,0));
    mutate_global_property(Qinit_string,
	    Qget_command_line_plist_element_for_init_string,
	    Qcommand_line_plist_element_getter);
    list_constant_17 = STATIC_CONS(Qinit_string,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_17,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_discard_user_settings = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-DISCARD-USER-SETTINGS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_discard_user_settings,
	    STATIC_FUNCTION(command_line_process_discard_user_settings,NIL,
	    FALSE,1,1));
    Qdiscard_user_settings = STATIC_SYMBOL("DISCARD-USER-SETTINGS",AB_package);
    mutate_global_property(Qdiscard_user_settings,
	    Qcommand_line_process_discard_user_settings,
	    Qcommand_line_argument_processor);
    array_constant_11 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_discard_user_settings = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DISCARD-USER-SETTINGS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_discard_user_settings,
	    STATIC_FUNCTION(get_command_line_plist_element_for_discard_user_settings,
	    NIL,FALSE,0,0));
    mutate_global_property(Qdiscard_user_settings,
	    Qget_command_line_plist_element_for_discard_user_settings,
	    Qcommand_line_plist_element_getter);
    list_constant_18 = STATIC_CONS(Qdiscard_user_settings,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_18,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_user_mode = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-USER-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_user_mode,
	    STATIC_FUNCTION(command_line_process_user_mode,NIL,FALSE,1,1));
    Quser_mode = STATIC_SYMBOL("USER-MODE",AB_package);
    mutate_global_property(Quser_mode,Qcommand_line_process_user_mode,
	    Qcommand_line_argument_processor);
    array_constant_12 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_user_mode = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USER-MODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_user_mode,
	    STATIC_FUNCTION(get_command_line_plist_element_for_user_mode,
	    NIL,FALSE,0,0));
    mutate_global_property(Quser_mode,
	    Qget_command_line_plist_element_for_user_mode,
	    Qcommand_line_plist_element_getter);
    list_constant_19 = STATIC_CONS(Quser_mode,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_19,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_window = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-WINDOW",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_window,
	    STATIC_FUNCTION(command_line_process_window,NIL,FALSE,1,1));
    Qwindow = STATIC_SYMBOL("WINDOW",AB_package);
    mutate_global_property(Qwindow,Qcommand_line_process_window,
	    Qcommand_line_argument_processor);
    array_constant_13 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_window = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_window,
	    STATIC_FUNCTION(get_command_line_plist_element_for_window,NIL,
	    FALSE,0,0));
    mutate_global_property(Qwindow,
	    Qget_command_line_plist_element_for_window,
	    Qcommand_line_plist_element_getter);
    list_constant_20 = STATIC_CONS(Qwindow,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_20,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_user_name = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-USER-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_user_name,
	    STATIC_FUNCTION(command_line_process_user_name,NIL,FALSE,1,1));
    Quser_name = STATIC_SYMBOL("USER-NAME",AB_package);
    mutate_global_property(Quser_name,Qcommand_line_process_user_name,
	    Qcommand_line_argument_processor);
    array_constant_14 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_user_name = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USER-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_user_name,
	    STATIC_FUNCTION(get_command_line_plist_element_for_user_name,
	    NIL,FALSE,0,0));
    mutate_global_property(Quser_name,
	    Qget_command_line_plist_element_for_user_name,
	    Qcommand_line_plist_element_getter);
    list_constant_21 = STATIC_CONS(Quser_name,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_21,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_windowhandle = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-WINDOWHANDLE",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_windowhandle,
	    STATIC_FUNCTION(command_line_process_windowhandle,NIL,FALSE,1,1));
    Qwindowhandle = STATIC_SYMBOL("WINDOWHANDLE",AB_package);
    mutate_global_property(Qwindowhandle,
	    Qcommand_line_process_windowhandle,
	    Qcommand_line_argument_processor);
    array_constant_15 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_windowhandle = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOWHANDLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_windowhandle,
	    STATIC_FUNCTION(get_command_line_plist_element_for_windowhandle,
	    NIL,FALSE,0,0));
    mutate_global_property(Qwindowhandle,
	    Qget_command_line_plist_element_for_windowhandle,
	    Qcommand_line_plist_element_getter);
    list_constant_22 = STATIC_CONS(Qwindowhandle,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_22,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    string_constant_18 = STATIC_STRING("windowhandle");
    string_constant_19 = STATIC_STRING("");
    string_constant_20 = STATIC_STRING("-window-style");
    Qcommand_line_process_window_style = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-WINDOW-STYLE",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_window_style,
	    STATIC_FUNCTION(command_line_process_window_style,NIL,FALSE,1,1));
    Qwindow_style = STATIC_SYMBOL("WINDOW-STYLE",AB_package);
    mutate_global_property(Qwindow_style,
	    Qcommand_line_process_window_style,
	    Qcommand_line_argument_processor);
    array_constant_16 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_window_style = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOW-STYLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_window_style,
	    STATIC_FUNCTION(get_command_line_plist_element_for_window_style,
	    NIL,FALSE,0,0));
    mutate_global_property(Qwindow_style,
	    Qget_command_line_plist_element_for_window_style,
	    Qcommand_line_plist_element_getter);
    list_constant_23 = STATIC_CONS(Qwindow_style,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_23,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qstandard_large = STATIC_SYMBOL("STANDARD-LARGE",AB_package);
    Qab_standard = STATIC_SYMBOL("STANDARD",AB_package);
    Qg2_5_dot_x = STATIC_SYMBOL("G2-5.X",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qstandard_large,Qab_standard,
	    Qg2_5_dot_x);
    string_constant_21 = 
	    STATIC_STRING("The ~a argument ~s is not recognized. It should be one of ~L,|");
    Qcommand_line_process_no_native_fonts = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NO-NATIVE-FONTS",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_no_native_fonts,
	    STATIC_FUNCTION(command_line_process_no_native_fonts,NIL,FALSE,
	    1,1));
    Qno_native_fonts = STATIC_SYMBOL("NO-NATIVE-FONTS",AB_package);
    mutate_global_property(Qno_native_fonts,
	    Qcommand_line_process_no_native_fonts,
	    Qcommand_line_argument_processor);
    array_constant_17 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_no_native_fonts = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-NATIVE-FONTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_no_native_fonts,
	    STATIC_FUNCTION(get_command_line_plist_element_for_no_native_fonts,
	    NIL,FALSE,0,0));
    mutate_global_property(Qno_native_fonts,
	    Qget_command_line_plist_element_for_no_native_fonts,
	    Qcommand_line_plist_element_getter);
    list_constant_24 = STATIC_CONS(Qno_native_fonts,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_24,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_native_fonts = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NATIVE-FONTS",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_native_fonts,
	    STATIC_FUNCTION(command_line_process_native_fonts,NIL,FALSE,1,1));
    Qnative_fonts = STATIC_SYMBOL("NATIVE-FONTS",AB_package);
    mutate_global_property(Qnative_fonts,
	    Qcommand_line_process_native_fonts,
	    Qcommand_line_argument_processor);
    array_constant_18 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_native_fonts = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NATIVE-FONTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_native_fonts,
	    STATIC_FUNCTION(get_command_line_plist_element_for_native_fonts,
	    NIL,FALSE,0,0));
    mutate_global_property(Qnative_fonts,
	    Qget_command_line_plist_element_for_native_fonts,
	    Qcommand_line_plist_element_getter);
    list_constant_25 = STATIC_CONS(Qnative_fonts,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_25,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_no_native_clipboard = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NO-NATIVE-CLIPBOARD",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_no_native_clipboard,
	    STATIC_FUNCTION(command_line_process_no_native_clipboard,NIL,
	    FALSE,1,1));
    Qno_native_clipboard = STATIC_SYMBOL("NO-NATIVE-CLIPBOARD",AB_package);
    mutate_global_property(Qno_native_clipboard,
	    Qcommand_line_process_no_native_clipboard,
	    Qcommand_line_argument_processor);
    array_constant_19 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_no_native_clipboard = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-NATIVE-CLIPBOARD",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_no_native_clipboard,
	    STATIC_FUNCTION(get_command_line_plist_element_for_no_native_clipboard,
	    NIL,FALSE,0,0));
    mutate_global_property(Qno_native_clipboard,
	    Qget_command_line_plist_element_for_no_native_clipboard,
	    Qcommand_line_plist_element_getter);
    list_constant_26 = STATIC_CONS(Qno_native_clipboard,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_26,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    array_constant_20 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)57344L);
    Qcommand_line_process_g2passwdexe = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-G2PASSWDEXE",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_g2passwdexe,
	    STATIC_FUNCTION(command_line_process_g2passwdexe,NIL,FALSE,1,1));
    Qg2passwdexe = STATIC_SYMBOL("G2PASSWDEXE",AB_package);
    mutate_global_property(Qg2passwdexe,Qcommand_line_process_g2passwdexe,
	    Qcommand_line_argument_processor);
    array_constant_21 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)9L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)10L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_g2passwdexe = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-G2PASSWDEXE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_g2passwdexe,
	    STATIC_FUNCTION(get_command_line_plist_element_for_g2passwdexe,
	    NIL,FALSE,0,0));
    mutate_global_property(Qg2passwdexe,
	    Qget_command_line_plist_element_for_g2passwdexe,
	    Qcommand_line_plist_element_getter);
    list_constant_27 = STATIC_CONS(Qg2passwdexe,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_27,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_no_backing_store = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NO-BACKING-STORE",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_no_backing_store,
	    STATIC_FUNCTION(command_line_process_no_backing_store,NIL,
	    FALSE,1,1));
    Qno_backing_store = STATIC_SYMBOL("NO-BACKING-STORE",AB_package);
    mutate_global_property(Qno_backing_store,
	    Qcommand_line_process_no_backing_store,
	    Qcommand_line_argument_processor);
    array_constant_22 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)11L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)13L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)23L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_no_backing_store = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-BACKING-STORE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_no_backing_store,
	    STATIC_FUNCTION(get_command_line_plist_element_for_no_backing_store,
	    NIL,FALSE,0,0));
    mutate_global_property(Qno_backing_store,
	    Qget_command_line_plist_element_for_no_backing_store,
	    Qcommand_line_plist_element_getter);
    list_constant_28 = STATIC_CONS(Qno_backing_store,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_28,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_private_colormap = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-PRIVATE-COLORMAP",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_private_colormap,
	    STATIC_FUNCTION(command_line_process_private_colormap,NIL,
	    FALSE,1,1));
    Qprivate_colormap = STATIC_SYMBOL("PRIVATE-COLORMAP",AB_package);
    mutate_global_property(Qprivate_colormap,
	    Qcommand_line_process_private_colormap,
	    Qcommand_line_argument_processor);
    array_constant_23 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)13L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)23L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_private_colormap = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-PRIVATE-COLORMAP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_private_colormap,
	    STATIC_FUNCTION(get_command_line_plist_element_for_private_colormap,
	    NIL,FALSE,0,0));
    mutate_global_property(Qprivate_colormap,
	    Qget_command_line_plist_element_for_private_colormap,
	    Qcommand_line_plist_element_getter);
    list_constant_29 = STATIC_CONS(Qprivate_colormap,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_29,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_file_operation_timeout = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-FILE-OPERATION-TIMEOUT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_file_operation_timeout,
	    STATIC_FUNCTION(command_line_process_file_operation_timeout,
	    NIL,FALSE,1,1));
    Qfile_operation_timeout = STATIC_SYMBOL("FILE-OPERATION-TIMEOUT",
	    AB_package);
    mutate_global_property(Qfile_operation_timeout,
	    Qcommand_line_process_file_operation_timeout,
	    Qcommand_line_argument_processor);
    array_constant_24 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)8L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)11L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)12L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)13L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)16L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)17L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)18L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)19L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)20L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)21L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)31L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_file_operation_timeout = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-FILE-OPERATION-TIMEOUT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_file_operation_timeout,
	    STATIC_FUNCTION(get_command_line_plist_element_for_file_operation_timeout,
	    NIL,FALSE,0,0));
    mutate_global_property(Qfile_operation_timeout,
	    Qget_command_line_plist_element_for_file_operation_timeout,
	    Qcommand_line_plist_element_getter);
    list_constant_30 = STATIC_CONS(Qfile_operation_timeout,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_30,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_use_os_emulation = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-USE-OS-EMULATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_use_os_emulation,
	    STATIC_FUNCTION(command_line_process_use_os_emulation,NIL,
	    FALSE,1,1));
    Quse_os_emulation = STATIC_SYMBOL("USE-OS-EMULATION",AB_package);
    mutate_global_property(Quse_os_emulation,
	    Qcommand_line_process_use_os_emulation,
	    Qcommand_line_argument_processor);
    array_constant_25 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_use_os_emulation = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USE-OS-EMULATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_use_os_emulation,
	    STATIC_FUNCTION(get_command_line_plist_element_for_use_os_emulation,
	    NIL,FALSE,0,0));
    mutate_global_property(Quse_os_emulation,
	    Qget_command_line_plist_element_for_use_os_emulation,
	    Qcommand_line_plist_element_getter);
    list_constant_31 = STATIC_CONS(Quse_os_emulation,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_31,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_copy_messages_on_logbook = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-COPY-MESSAGES-ON-LOGBOOK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_copy_messages_on_logbook,
	    STATIC_FUNCTION(command_line_process_copy_messages_on_logbook,
	    NIL,FALSE,1,1));
    Qcopy_messages_on_logbook = STATIC_SYMBOL("COPY-MESSAGES-ON-LOGBOOK",
	    AB_package);
    mutate_global_property(Qcopy_messages_on_logbook,
	    Qcommand_line_process_copy_messages_on_logbook,
	    Qcommand_line_argument_processor);
    array_constant_26 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)8L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)10L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)12L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)13L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)16L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)17L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)18L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)19L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)20L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)21L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)22L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)23L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)31L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_copy_messages_on_logbook = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-COPY-MESSAGES-ON-LOGBOOK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_copy_messages_on_logbook,
	    STATIC_FUNCTION(get_command_line_plist_element_for_copy_messages_on_logbook,
	    NIL,FALSE,0,0));
    mutate_global_property(Qcopy_messages_on_logbook,
	    Qget_command_line_plist_element_for_copy_messages_on_logbook,
	    Qcommand_line_plist_element_getter);
    list_constant_32 = STATIC_CONS(Qcopy_messages_on_logbook,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_32,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_copy_logbook_on_console = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-COPY-LOGBOOK-ON-CONSOLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_copy_logbook_on_console,
	    STATIC_FUNCTION(command_line_process_copy_logbook_on_console,
	    NIL,FALSE,1,1));
    Qcopy_logbook_on_console = STATIC_SYMBOL("COPY-LOGBOOK-ON-CONSOLE",
	    AB_package);
    mutate_global_property(Qcopy_logbook_on_console,
	    Qcommand_line_process_copy_logbook_on_console,
	    Qcommand_line_argument_processor);
    array_constant_27 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)8L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)9L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)10L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)11L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)12L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)13L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)16L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)17L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)18L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)19L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)20L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)21L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)22L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)31L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_copy_logbook_on_console = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-COPY-LOGBOOK-ON-CONSOLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_copy_logbook_on_console,
	    STATIC_FUNCTION(get_command_line_plist_element_for_copy_logbook_on_console,
	    NIL,FALSE,0,0));
    mutate_global_property(Qcopy_logbook_on_console,
	    Qget_command_line_plist_element_for_copy_logbook_on_console,
	    Qcommand_line_plist_element_getter);
    list_constant_33 = STATIC_CONS(Qcopy_logbook_on_console,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_33,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_debug_frame_reference_balance = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-DEBUG-FRAME-REFERENCE-BALANCE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_debug_frame_reference_balance,
	    STATIC_FUNCTION(command_line_process_debug_frame_reference_balance,
	    NIL,FALSE,1,1));
    Qdebug_frame_reference_balance = 
	    STATIC_SYMBOL("DEBUG-FRAME-REFERENCE-BALANCE",AB_package);
    mutate_global_property(Qdebug_frame_reference_balance,
	    Qcommand_line_process_debug_frame_reference_balance,
	    Qcommand_line_argument_processor);
    array_constant_28 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)8L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)9L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)10L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)12L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)13L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)16L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)17L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)18L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)19L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)20L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)21L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)22L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)23L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)24L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)25L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)26L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)27L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)28L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)31L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_debug_frame_reference_balance = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DEBUG-FRAME-REFERENCE-BALANCE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_debug_frame_reference_balance,
	    STATIC_FUNCTION(get_command_line_plist_element_for_debug_frame_reference_balance,
	    NIL,FALSE,0,0));
    mutate_global_property(Qdebug_frame_reference_balance,
	    Qget_command_line_plist_element_for_debug_frame_reference_balance,
	    Qcommand_line_plist_element_getter);
    list_constant_34 = STATIC_CONS(Qdebug_frame_reference_balance,
	    FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_34,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_xclip = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-XCLIP",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_xclip,
	    STATIC_FUNCTION(command_line_process_xclip,NIL,FALSE,1,1));
    Qxclip = STATIC_SYMBOL("XCLIP",AB_package);
    mutate_global_property(Qxclip,Qcommand_line_process_xclip,
	    Qcommand_line_argument_processor);
    array_constant_29 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_xclip = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-XCLIP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_xclip,
	    STATIC_FUNCTION(get_command_line_plist_element_for_xclip,NIL,
	    FALSE,0,0));
    mutate_global_property(Qxclip,
	    Qget_command_line_plist_element_for_xclip,
	    Qcommand_line_plist_element_getter);
    list_constant_35 = STATIC_CONS(Qxclip,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_35,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Kall = STATIC_SYMBOL("ALL",Pkeyword);
    Qcommand_line_process_background = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-BACKGROUND",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_background,
	    STATIC_FUNCTION(command_line_process_background,NIL,FALSE,1,1));
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    mutate_global_property(Qbackground,Qcommand_line_process_background,
	    Qcommand_line_argument_processor);
    array_constant_30 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)9L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_background = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-BACKGROUND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_background,
	    STATIC_FUNCTION(get_command_line_plist_element_for_background,
	    NIL,FALSE,0,0));
    mutate_global_property(Qbackground,
	    Qget_command_line_plist_element_for_background,
	    Qcommand_line_plist_element_getter);
    list_constant_36 = STATIC_CONS(Qbackground,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_36,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qknown_ui_styles = STATIC_SYMBOL("KNOWN-UI-STYLES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qknown_ui_styles,Known_ui_styles);
    Qclassic = STATIC_SYMBOL("CLASSIC",AB_package);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qclassic,Qab_standard);
    SET_SYMBOL_VALUE(Qknown_ui_styles,list_constant_37);
    string_constant_22 = 
	    STATIC_STRING("The -ui argument ~s must either be ~(~L,|~). Assuming ~(~s~).");
    Qcommand_line_process_ui = STATIC_SYMBOL("COMMAND-LINE-PROCESS-UI",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_ui,
	    STATIC_FUNCTION(command_line_process_ui,NIL,FALSE,1,1));
    Qui = STATIC_SYMBOL("UI",AB_package);
    mutate_global_property(Qui,Qcommand_line_process_ui,
	    Qcommand_line_argument_processor);
    array_constant_31 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_ui = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-UI",AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_ui,
	    STATIC_FUNCTION(get_command_line_plist_element_for_ui,NIL,
	    FALSE,0,0));
    mutate_global_property(Qui,Qget_command_line_plist_element_for_ui,
	    Qcommand_line_plist_element_getter);
    list_constant_38 = STATIC_CONS(Qui,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_38,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_netinfo = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NETINFO",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_netinfo,
	    STATIC_FUNCTION(command_line_process_netinfo,NIL,FALSE,1,1));
    Qnetinfo = STATIC_SYMBOL("NETINFO",AB_package);
    mutate_global_property(Qnetinfo,Qcommand_line_process_netinfo,
	    Qcommand_line_argument_processor);
    array_constant_32 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_netinfo = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NETINFO",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_netinfo,
	    STATIC_FUNCTION(get_command_line_plist_element_for_netinfo,NIL,
	    FALSE,0,0));
    mutate_global_property(Qnetinfo,
	    Qget_command_line_plist_element_for_netinfo,
	    Qcommand_line_plist_element_getter);
    list_constant_39 = STATIC_CONS(Qnetinfo,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_39,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_verbose = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-VERBOSE",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_verbose,
	    STATIC_FUNCTION(command_line_process_verbose,NIL,FALSE,1,1));
    Qverbose = STATIC_SYMBOL("VERBOSE",AB_package);
    mutate_global_property(Qverbose,Qcommand_line_process_verbose,
	    Qcommand_line_argument_processor);
    array_constant_33 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)5L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_verbose = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-VERBOSE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_verbose,
	    STATIC_FUNCTION(get_command_line_plist_element_for_verbose,NIL,
	    FALSE,0,0));
    mutate_global_property(Qverbose,
	    Qget_command_line_plist_element_for_verbose,
	    Qcommand_line_plist_element_getter);
    list_constant_40 = STATIC_CONS(Qverbose,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_40,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_silent = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-SILENT",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_silent,
	    STATIC_FUNCTION(command_line_process_silent,NIL,FALSE,1,1));
    Qsilent = STATIC_SYMBOL("SILENT",AB_package);
    mutate_global_property(Qsilent,Qcommand_line_process_silent,
	    Qcommand_line_argument_processor);
    array_constant_34 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)4L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_silent = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-SILENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_silent,
	    STATIC_FUNCTION(get_command_line_plist_element_for_silent,NIL,
	    FALSE,0,0));
    mutate_global_property(Qsilent,
	    Qget_command_line_plist_element_for_silent,
	    Qcommand_line_plist_element_getter);
    list_constant_41 = STATIC_CONS(Qsilent,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_41,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_exit_on_abort = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-EXIT-ON-ABORT",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_exit_on_abort,
	    STATIC_FUNCTION(command_line_process_exit_on_abort,NIL,FALSE,1,1));
    Qexit_on_abort = STATIC_SYMBOL("EXIT-ON-ABORT",AB_package);
    mutate_global_property(Qexit_on_abort,
	    Qcommand_line_process_exit_on_abort,
	    Qcommand_line_argument_processor);
    array_constant_35 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)8L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)9L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)10L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)11L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_exit_on_abort = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-EXIT-ON-ABORT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_exit_on_abort,
	    STATIC_FUNCTION(get_command_line_plist_element_for_exit_on_abort,
	    NIL,FALSE,0,0));
    mutate_global_property(Qexit_on_abort,
	    Qget_command_line_plist_element_for_exit_on_abort,
	    Qcommand_line_plist_element_getter);
    list_constant_42 = STATIC_CONS(Qexit_on_abort,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_42,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    array_constant_36 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)8L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)23L,(SI_Long)57344L);
    Qcommand_line_process_use_jit = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-USE-JIT",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_use_jit,
	    STATIC_FUNCTION(command_line_process_use_jit,NIL,FALSE,1,1));
    Quse_jit = STATIC_SYMBOL("USE-JIT",AB_package);
    mutate_global_property(Quse_jit,Qcommand_line_process_use_jit,
	    Qcommand_line_argument_processor);
    array_constant_37 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)4L,(SI_Long)74L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_use_jit = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USE-JIT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_use_jit,
	    STATIC_FUNCTION(get_command_line_plist_element_for_use_jit,NIL,
	    FALSE,0,0));
    mutate_global_property(Quse_jit,
	    Qget_command_line_plist_element_for_use_jit,
	    Qcommand_line_plist_element_getter);
    list_constant_43 = STATIC_CONS(Quse_jit,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_43,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    if (Use_jit_p == UNBOUND)
	Use_jit_p = Nil;
    Secure_icp_initialized_p = Nil;
    Secure_icp_default_p = Nil;
    Cache_server_cert_name = Nil;
    Qcommand_line_process_secure = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-SECURE",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_secure,
	    STATIC_FUNCTION(command_line_process_secure,NIL,FALSE,1,1));
    Qsecure = STATIC_SYMBOL("SECURE",AB_package);
    mutate_global_property(Qsecure,Qcommand_line_process_secure,
	    Qcommand_line_argument_processor);
    array_constant_38 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)4L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_secure = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-SECURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_secure,
	    STATIC_FUNCTION(get_command_line_plist_element_for_secure,NIL,
	    FALSE,0,0));
    mutate_global_property(Qsecure,
	    Qget_command_line_plist_element_for_secure,
	    Qcommand_line_plist_element_getter);
    list_constant_44 = STATIC_CONS(Qsecure,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_44,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    array_constant_39 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)15L,(SI_Long)57344L);
    Qcommand_line_process_cert = STATIC_SYMBOL("COMMAND-LINE-PROCESS-CERT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_cert,
	    STATIC_FUNCTION(command_line_process_cert,NIL,FALSE,1,1));
    Qcert = STATIC_SYMBOL("CERT",AB_package);
    mutate_global_property(Qcert,Qcommand_line_process_cert,
	    Qcommand_line_argument_processor);
    array_constant_40 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_cert = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-CERT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_cert,
	    STATIC_FUNCTION(get_command_line_plist_element_for_cert,NIL,
	    FALSE,0,0));
    mutate_global_property(Qcert,Qget_command_line_plist_element_for_cert,
	    Qcommand_line_plist_element_getter);
    list_constant_45 = STATIC_CONS(Qcert,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_45,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    string_constant_23 = STATIC_STRING("cert");
    string_constant_24 = STATIC_STRING("G2_CERT");
    Knetwork_type = STATIC_SYMBOL("NETWORK-TYPE",Pkeyword);
    Kuse_default = STATIC_SYMBOL("USE-DEFAULT",Pkeyword);
    Ksecure_p = STATIC_SYMBOL("SECURE-P",Pkeyword);
    array_constant_41 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)57344L);
    string_constant_25 = STATIC_STRING("/SSL");
    string_constant_26 = 
	    STATIC_STRING("WARNING: SSL encryption is not available in this executable.");
    Qcommand_line_process_icp_log_intensity = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-ICP-LOG-INTENSITY",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_icp_log_intensity,
	    STATIC_FUNCTION(command_line_process_icp_log_intensity,NIL,
	    FALSE,1,1));
    Qicp_log_intensity = STATIC_SYMBOL("ICP-LOG-INTENSITY",AB_package);
    mutate_global_property(Qicp_log_intensity,
	    Qcommand_line_process_icp_log_intensity,
	    Qcommand_line_argument_processor);
    array_constant_42 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)6L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)8L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)9L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)12L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)13L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)14L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)15L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)16L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)23L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_icp_log_intensity = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-ICP-LOG-INTENSITY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_icp_log_intensity,
	    STATIC_FUNCTION(get_command_line_plist_element_for_icp_log_intensity,
	    NIL,FALSE,0,0));
    mutate_global_property(Qicp_log_intensity,
	    Qget_command_line_plist_element_for_icp_log_intensity,
	    Qcommand_line_plist_element_getter);
    list_constant_46 = STATIC_CONS(Qicp_log_intensity,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_46,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qforeign_struct_info = STATIC_SYMBOL("FOREIGN-STRUCT-INFO",AB_package);
    Foreign_struct_info_prop = Qforeign_struct_info;
    Qg2_defstruct_structure_name_foreign_struct_info_g2_struct = 
	    STATIC_SYMBOL("FOREIGN-STRUCT-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_foreign_struct_info_g2_struct,
	    Qforeign_struct_info,Qab_name_of_unique_structure_type);
    mutate_global_property(Qforeign_struct_info,
	    Qg2_defstruct_structure_name_foreign_struct_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_foreign_struct_info == UNBOUND)
	The_type_description_of_foreign_struct_info = Nil;
    string_constant_58 = 
	    STATIC_STRING("43Dy8m83hPy1n83hPy8n8k1l8n0000000krk0k0");
    temp = The_type_description_of_foreign_struct_info;
    The_type_description_of_foreign_struct_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_58));
    mutate_global_property(Qg2_defstruct_structure_name_foreign_struct_info_g2_struct,
	    The_type_description_of_foreign_struct_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qforeign_struct_info,
	    The_type_description_of_foreign_struct_info,
	    Qtype_description_of_type);
    Qoutstanding_foreign_struct_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-FOREIGN-STRUCT-INFO-COUNT",AB_package);
    Qforeign_struct_info_structure_memory_usage = 
	    STATIC_SYMBOL("FOREIGN-STRUCT-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_59 = STATIC_STRING("1q83hPy8s83-Ugy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_foreign_struct_info_count);
    push_optimized_constant(Qforeign_struct_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_59));
    Qchain_of_available_foreign_struct_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FOREIGN-STRUCT-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_foreign_struct_infos,
	    Chain_of_available_foreign_struct_infos);
    record_system_variable(Qchain_of_available_foreign_struct_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qforeign_struct_info_count = STATIC_SYMBOL("FOREIGN-STRUCT-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforeign_struct_info_count,
	    Foreign_struct_info_count);
    record_system_variable(Qforeign_struct_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_foreign_struct_infos_vector == UNBOUND)
	Chain_of_available_foreign_struct_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qforeign_struct_info_structure_memory_usage,
	    STATIC_FUNCTION(foreign_struct_info_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_foreign_struct_info_count,
	    STATIC_FUNCTION(outstanding_foreign_struct_info_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_foreign_struct_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_foreign_struct_info,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qforeign_struct_info,
	    reclaim_structure_for_foreign_struct_info_1);
    if (Next_eq_hash_value == UNBOUND)
	Next_eq_hash_value = FIX((SI_Long)0L);
    Qg2_defstruct_structure_name_eq_hash_table_g2_struct = 
	    STATIC_SYMBOL("EQ-HASH-TABLE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qeq_hash_table = STATIC_SYMBOL("EQ-HASH-TABLE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_eq_hash_table_g2_struct,
	    Qeq_hash_table,Qab_name_of_unique_structure_type);
    mutate_global_property(Qeq_hash_table,
	    Qg2_defstruct_structure_name_eq_hash_table_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_eq_hash_table == UNBOUND)
	The_type_description_of_eq_hash_table = Nil;
    string_constant_60 = 
	    STATIC_STRING("43Dy8m83h4y1n83h4y8n8k1l8n0000001m1m8y83-3Xy1m83My83-ABykqk0k0");
    temp = The_type_description_of_eq_hash_table;
    The_type_description_of_eq_hash_table = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_60));
    mutate_global_property(Qg2_defstruct_structure_name_eq_hash_table_g2_struct,
	    The_type_description_of_eq_hash_table,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qeq_hash_table,
	    The_type_description_of_eq_hash_table,Qtype_description_of_type);
    Qoutstanding_eq_hash_table_count = 
	    STATIC_SYMBOL("OUTSTANDING-EQ-HASH-TABLE-COUNT",AB_package);
    Qeq_hash_table_structure_memory_usage = 
	    STATIC_SYMBOL("EQ-HASH-TABLE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_61 = STATIC_STRING("1q83h4y8s83-Swy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_eq_hash_table_count);
    push_optimized_constant(Qeq_hash_table_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_61));
    Qchain_of_available_eq_hash_tables = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EQ-HASH-TABLES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_eq_hash_tables,
	    Chain_of_available_eq_hash_tables);
    record_system_variable(Qchain_of_available_eq_hash_tables,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qeq_hash_table_count = STATIC_SYMBOL("EQ-HASH-TABLE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qeq_hash_table_count,Eq_hash_table_count);
    record_system_variable(Qeq_hash_table_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_eq_hash_tables_vector == UNBOUND)
	Chain_of_available_eq_hash_tables_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qeq_hash_table_structure_memory_usage,
	    STATIC_FUNCTION(eq_hash_table_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_eq_hash_table_count,
	    STATIC_FUNCTION(outstanding_eq_hash_table_count,NIL,FALSE,0,0));
    reclaim_structure_for_eq_hash_table_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_eq_hash_table,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qeq_hash_table,
	    reclaim_structure_for_eq_hash_table_1);
    string_constant_27 = STATIC_STRING("Version ~d.");
    string_constant_28 = STATIC_STRING("~d");
    Qalpha_or_beta = STATIC_SYMBOL("ALPHA-OR-BETA",AB_package);
    Qpatch_level = STATIC_SYMBOL("PATCH-LEVEL",AB_package);
    string_constant_29 = STATIC_STRING(" ~a~c");
    string_constant_30 = STATIC_STRING(" ~a");
    Qbrief_description = STATIC_SYMBOL("BRIEF-DESCRIPTION",AB_package);
    string_constant_31 = STATIC_STRING("Version ~d.~d ");
    string_constant_32 = STATIC_STRING("Enterprise");
    string_constant_33 = STATIC_STRING("Standard");
    string_constant_34 = STATIC_STRING(", ~a");
    Expiration_date_for_display_in_title = Nil;
    string_constant_35 = STATIC_STRING("Host: ~a");
    string_constant_36 = STATIC_STRING("; ~a: ~a~a");
    string_constant_37 = STATIC_STRING("~%Expiration Day:~a~%");
    string_constant_38 = STATIC_STRING("~%");
    string_constant_39 = STATIC_STRING("(Unknown Host)");
    array_constant_43 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)3L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)15L,(SI_Long)57344L);
    array_constant_44 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)3L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)7L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)15L,(SI_Long)57344L);
    array_constant_45 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)14L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)16L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)23L,(SI_Long)57344L);
    string_constant_40 = STATIC_STRING("~a");
}
