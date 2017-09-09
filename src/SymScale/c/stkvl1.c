/* stkvl1.c
 * Input file:  stack-eval1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "stkvl1.h"


/* PPRINT-INFIX-EVALUATOR */
Object pprint_infix_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,0);
    return pprint_infix_evaluator_using_name(ISVREF(description,
	    (SI_Long)0L),pc,byte_code_body,constant_vector,stack,top_of_stack);
}

/* PPRINT-INFIX-EVALUATOR-USING-NAME */
Object pprint_infix_evaluator_using_name(name,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object name, pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(207,1);
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_character(FIX((SI_Long)32L));
    twrite_symbol(1,name);
    twrite_character(FIX((SI_Long)32L));
    return write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,
	    top_of_stack);
}

static Object array_constant;      /* # */

/* PPRINT-FUNCTIONAL-EVALUATOR */
Object pprint_functional_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    Object argument_count;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(207,2);
    argument_count = length(ISVREF(description,(SI_Long)4L));
    twrite_symbol(1,ISVREF(description,(SI_Long)0L));
    twrite_character(FIX((SI_Long)40L));
    index_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(argument_count);
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    if (index_1 != (SI_Long)1L)
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)2L));
    write_stack_argument(FIX(index_1),argument_count,stack,top_of_stack);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return twrite_character(FIX((SI_Long)41L));
}

/* PPRINT-PREFIX-EVALUATOR */
Object pprint_prefix_evaluator(operator_string,stack,top_of_stack)
    Object operator_string, stack, top_of_stack;
{
    x_note_fn_call(207,3);
    twrite_general_string(operator_string);
    twrite_character(FIX((SI_Long)32L));
    return write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,
	    top_of_stack);
}

static Object string_constant;     /* "negate" */

/* PPRINT-NEGATE-EVALUATOR */
Object pprint_negate_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,4);
    return pprint_prefix_evaluator(string_constant,stack,top_of_stack);
}

/* PPRINT-FORMAT-FORM-INSTRUCTION */
Object pprint_format_form_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack,arg_count,result_count)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack, arg_count, result_count;
{
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(207,5);
    twrite_character(FIX((SI_Long)34L));
    index_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(arg_count);
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    twrite_character(FIX((SI_Long)91L));
    write_stack_argument(FIX(index_1),arg_count,stack,top_of_stack);
    twrite_character(FIX((SI_Long)93L));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return twrite_character(FIX((SI_Long)34L));
}

static Object Qseconds;            /* seconds */

static Object array_constant_1;    /* # */

static Object Qtime_stamp;         /* time-stamp */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

/* PPRINT-FORMAT-EVALUATOR */
Object pprint_format_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    Object value_arg, format_arg, format_1;

    x_note_fn_call(207,6);
    if (FIXNUM_EQ(top_of_stack,Cached_top_of_stack)) {
	value_arg = ISVREF(stack,IFIX(FIXNUM_SUB1(top_of_stack)));
	format_arg = ISVREF(stack,IFIX(top_of_stack));
	format_1 = format_arg;
	write_stored_value(value_arg);
	if (EQ(format_1,Qseconds))
	    return twrite_beginning_of_wide_string(array_constant_1,
		    FIX((SI_Long)15L));
	else if (EQ(format_1,Qtime_stamp))
	    return twrite_beginning_of_wide_string(array_constant_2,
		    FIX((SI_Long)16L));
	else
	    return twrite_beginning_of_wide_string(array_constant_3,
		    FIX((SI_Long)22L));
    }
    else {
	twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)36L));
	return write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),
		stack,top_of_stack);
    }
}

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

/* PPRINT-FIXED-FORMAT-EVALUATOR */
Object pprint_fixed_format_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    Object value_arg, integral_size_arg, integral_size, fraction_size_arg;
    Object fraction_size;
    SI_Long x, ab_loop_bind_;

    x_note_fn_call(207,7);
    if (FIXNUM_EQ(top_of_stack,Cached_top_of_stack)) {
	value_arg = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)2L);
	integral_size_arg = ISVREF(stack,IFIX(FIXNUM_SUB1(top_of_stack)));
	integral_size = integral_size_arg;
	fraction_size_arg = ISVREF(stack,IFIX(top_of_stack));
	fraction_size = fraction_size_arg;
	write_stored_value(value_arg);
	twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)4L));
	x = (SI_Long)1L;
	ab_loop_bind_ = IFIX(integral_size);
      next_loop:
	if (x > ab_loop_bind_)
	    goto end_loop;
	twrite_character(FIX((SI_Long)100L));
	x = x + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	twrite_character(FIX((SI_Long)46L));
	x = (SI_Long)1L;
	ab_loop_bind_ = IFIX(fraction_size);
      next_loop_1:
	if (x > ab_loop_bind_)
	    goto end_loop_1;
	twrite_character(FIX((SI_Long)100L));
	x = x + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else {
	twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)22L));
	return write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),
		stack,top_of_stack);
    }
}

/* PPRINT-IS-AND-POSSIBLY-UNKNOWN-INSTRUCTION */
Object pprint_is_and_possibly_unknown_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,8);
    return pprint_is_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack);
}

static Object Qis;                 /* is */

/* PPRINT-IS-INSTRUCTION */
Object pprint_is_instruction(description,pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,9);
    return pprint_infix_evaluator_using_name(Qis,pc,byte_code_body,
	    constant_vector,stack,top_of_stack);
}

static Object array_constant_7;    /* # */

/* PPRINT-FUZZY-EVALUATOR */
Object pprint_fuzzy_evaluator(operator_1,stack,top_of_stack)
    Object operator_1, stack, top_of_stack;
{
    x_note_fn_call(207,10);
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)3L),stack,top_of_stack);
    twrite_character(FIX((SI_Long)32L));
    twrite_symbol(1,operator_1);
    twrite_character(FIX((SI_Long)32L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)3L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)5L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)3L),stack,top_of_stack);
    return twrite_character(FIX((SI_Long)41L));
}

/* PPRINT-FUZZY-<-EVALUATOR */
Object pprint_fuzzy_lt_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,11);
    return pprint_fuzzy_evaluator(Qnum_lt,stack,top_of_stack);
}

/* PPRINT-FUZZY->-EVALUATOR */
Object pprint_fuzzy_gt_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,12);
    return pprint_fuzzy_evaluator(Qnum_gt,stack,top_of_stack);
}

/* PPRINT-FUZZY-=-EVALUATOR */
Object pprint_fuzzy_eq_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,13);
    return pprint_fuzzy_evaluator(Qnum_eq,stack,top_of_stack);
}

/* PPRINT-FUZZY-NOT-=-EVALUATOR */
Object pprint_fuzzy_not_eq_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,14);
    return pprint_fuzzy_evaluator(Qnum_ne,stack,top_of_stack);
}

static Object array_constant_8;    /* # */

/* PPRINT-HISTORY-EVALUATOR-DURING-TIME-INTERVAL */
Object pprint_history_evaluator_during_time_interval(description_string,
	    stack,top_of_stack,argument_count)
    Object description_string, stack, top_of_stack, argument_count;
{
    Object interval;
    char stack_args_ok_qm;

    x_note_fn_call(207,15);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    interval = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack) - 
	    (IFIX(argument_count) - (SI_Long)2L)) : Qnil;
    twrite_general_string(description_string);
    twrite_character(FIX((SI_Long)32L));
    write_stack_argument(FIX((SI_Long)1L),argument_count,stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)17L));
    if (stack_args_ok_qm)
	return print_constant(2,interval,Qseconds);
    else
	return write_stack_argument(FIX((SI_Long)2L),argument_count,stack,
		top_of_stack);
}

static Object string_constant_1;   /* "the average value of" */

/* PPRINT-AVERAGE-VALUE-1-INSTRUCTION */
Object pprint_average_value_1_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,16);
    return pprint_history_evaluator_during_time_interval(string_constant_1,
	    stack,top_of_stack,FIX((SI_Long)4L));
}

static Object string_constant_2;   /* "the sum of the values of" */

/* PPRINT-SUM-OF-VALUES-1-INSTRUCTION */
Object pprint_sum_of_values_1_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,17);
    return pprint_history_evaluator_during_time_interval(string_constant_2,
	    stack,top_of_stack,FIX((SI_Long)4L));
}

static Object string_constant_3;   /* "the minimum value of" */

/* PPRINT-MINIMUM-VALUE-1-INSTRUCTION */
Object pprint_minimum_value_1_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,18);
    return pprint_history_evaluator_during_time_interval(string_constant_3,
	    stack,top_of_stack,FIX((SI_Long)4L));
}

static Object string_constant_4;   /* "the maximum value of" */

/* PPRINT-MAXIMUM-VALUE-1-INSTRUCTION */
Object pprint_maximum_value_1_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,19);
    return pprint_history_evaluator_during_time_interval(string_constant_4,
	    stack,top_of_stack,FIX((SI_Long)4L));
}

static Object string_constant_5;   /* "the standard deviation of" */

/* PPRINT-STANDARD-DEVIATION-1-INSTRUCTION */
Object pprint_standard_deviation_1_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,20);
    return pprint_history_evaluator_during_time_interval(string_constant_5,
	    stack,top_of_stack,FIX((SI_Long)4L));
}

static Object string_constant_6;   /* "the number of history datapoints in" */

/* PPRINT-NUMBER-OF-DATAPOINTS-1-INSTRUCTION */
Object pprint_number_of_datapoints_1_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,21);
    return pprint_history_evaluator_during_time_interval(string_constant_6,
	    stack,top_of_stack,FIX((SI_Long)4L));
}

static Object Qtruth_value;        /* truth-value */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

/* PPRINT-HISTORY-EVALUATOR-BETWEEN-TIME-INTERVALS */
Object pprint_history_evaluator_between_time_intervals(description_string,
	    stack,top_of_stack,argument_count)
    Object description_string, stack, top_of_stack, argument_count;
{
    Object interval_1, interval_2;
    char stack_args_ok_qm;

    x_note_fn_call(207,22);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    interval_1 = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack) - 
	    (IFIX(argument_count) - (SI_Long)2L)) : Qnil;
    interval_2 = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack) - 
	    (IFIX(argument_count) - (SI_Long)3L)) : Qnil;
    twrite_general_string(description_string);
    twrite_character(FIX((SI_Long)32L));
    write_stack_argument(FIX((SI_Long)1L),argument_count,stack,top_of_stack);
    if (CONSP(interval_2) && EQ(M_CDR(interval_2),Qtruth_value)) {
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)12L));
	if (stack_args_ok_qm)
	    print_constant(2,interval_1,Qseconds);
	else
	    write_stack_argument(FIX((SI_Long)2L),argument_count,stack,
		    top_of_stack);
	return twrite_beginning_of_wide_string(array_constant_10,
		FIX((SI_Long)32L));
    }
    else {
	twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)9L));
	if (stack_args_ok_qm)
	    print_constant(2,interval_1,Qseconds);
	else
	    write_stack_argument(FIX((SI_Long)2L),argument_count,stack,
		    top_of_stack);
	twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)4L));
	twrite_beginning_of_wide_string(array_constant_13,FIX((SI_Long)5L));
	if (stack_args_ok_qm)
	    print_constant(2,interval_2,Qseconds);
	else
	    write_stack_argument(FIX((SI_Long)3L),argument_count,stack,
		    top_of_stack);
	return twrite_beginning_of_wide_string(array_constant_12,
		FIX((SI_Long)4L));
    }
}

/* PPRINT-AVERAGE-VALUE-2-INSTRUCTION */
Object pprint_average_value_2_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,23);
    return pprint_history_evaluator_between_time_intervals(string_constant_1,
	    stack,top_of_stack,FIX((SI_Long)5L));
}

/* PPRINT-SUM-OF-VALUES-2-INSTRUCTION */
Object pprint_sum_of_values_2_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,24);
    return pprint_history_evaluator_between_time_intervals(string_constant_2,
	    stack,top_of_stack,FIX((SI_Long)5L));
}

/* PPRINT-MINIMUM-VALUE-2-INSTRUCTION */
Object pprint_minimum_value_2_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,25);
    return pprint_history_evaluator_between_time_intervals(string_constant_3,
	    stack,top_of_stack,FIX((SI_Long)5L));
}

/* PPRINT-MAXIMUM-VALUE-2-INSTRUCTION */
Object pprint_maximum_value_2_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,26);
    return pprint_history_evaluator_between_time_intervals(string_constant_4,
	    stack,top_of_stack,FIX((SI_Long)5L));
}

/* PPRINT-STANDARD-DEVIATION-2-INSTRUCTION */
Object pprint_standard_deviation_2_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,27);
    return pprint_history_evaluator_between_time_intervals(string_constant_5,
	    stack,top_of_stack,FIX((SI_Long)5L));
}

/* PPRINT-NUMBER-OF-DATAPOINTS-2-INSTRUCTION */
Object pprint_number_of_datapoints_2_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,28);
    return pprint_history_evaluator_between_time_intervals(string_constant_6,
	    stack,top_of_stack,FIX((SI_Long)5L));
}

static Object array_constant_14;   /* # */

/* PPRINT-HISTORY-EVALUATOR-WITH-TIME-UNITS-DURING-TIME-INTERVAL */
Object pprint_history_evaluator_with_time_units_during_time_interval(description_string,
	    stack,top_of_stack,argument_count)
    Object description_string, stack, top_of_stack, argument_count;
{
    Object interval_qm;
    char stack_args_ok_qm;

    x_note_fn_call(207,29);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    interval_qm = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack) - 
	    (IFIX(argument_count) - (SI_Long)3L)) : Qnil;
    twrite_general_string(description_string);
    twrite_character(FIX((SI_Long)32L));
    write_stack_argument(FIX((SI_Long)2L),argument_count,stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_14,FIX((SI_Long)4L));
    write_stack_argument(FIX((SI_Long)1L),argument_count,stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)17L));
    if (interval_qm)
	return print_constant(2,interval_qm,Qseconds);
    else
	return write_stack_argument(FIX((SI_Long)3L),argument_count,stack,
		top_of_stack);
}

static Object string_constant_7;   /* "the rate of change per" */

/* PPRINT-RATE-OF-CHANGE-1-INSTRUCTION */
Object pprint_rate_of_change_1_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,30);
    return pprint_history_evaluator_with_time_units_during_time_interval(string_constant_7,
	    stack,top_of_stack,FIX((SI_Long)5L));
}

static Object string_constant_8;   /* "the integral in" */

/* PPRINT-INTEGRAL-1-INSTRUCTION */
Object pprint_integral_1_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,31);
    return pprint_history_evaluator_with_time_units_during_time_interval(string_constant_8,
	    stack,top_of_stack,FIX((SI_Long)5L));
}

/* PPRINT-HISTORY-EVALUATOR-WITH-TIME-UNITS-BETWEEN-TIME-INTERVALS */
Object pprint_history_evaluator_with_time_units_between_time_intervals(description_string,
	    stack,top_of_stack,argument_count)
    Object description_string, stack, top_of_stack, argument_count;
{
    Object interval_1_qm, interval_2_qm;
    char stack_args_ok_qm;

    x_note_fn_call(207,32);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    interval_1_qm = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack) - 
	    (IFIX(argument_count) - (SI_Long)3L)) : Qnil;
    interval_2_qm = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack) - 
	    (IFIX(argument_count) - (SI_Long)4L)) : Qnil;
    twrite_general_string(description_string);
    twrite_character(FIX((SI_Long)32L));
    write_stack_argument(FIX((SI_Long)2L),argument_count,stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_14,FIX((SI_Long)4L));
    write_stack_argument(FIX((SI_Long)1L),argument_count,stack,top_of_stack);
    if (CONSP(interval_2_qm) && EQ(M_CDR(interval_2_qm),Qtruth_value)) {
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)12L));
	if (stack_args_ok_qm)
	    print_constant(2,interval_1_qm,Qseconds);
	else
	    write_stack_argument(FIX((SI_Long)3L),argument_count,stack,
		    top_of_stack);
	return twrite_beginning_of_wide_string(array_constant_10,
		FIX((SI_Long)32L));
    }
    else {
	twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)9L));
	if (stack_args_ok_qm)
	    print_constant(2,interval_1_qm,Qseconds);
	else
	    write_stack_argument(FIX((SI_Long)3L),argument_count,stack,
		    top_of_stack);
	twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)4L));
	twrite_beginning_of_wide_string(array_constant_13,FIX((SI_Long)5L));
	if (stack_args_ok_qm)
	    print_constant(2,interval_2_qm,Qseconds);
	else
	    write_stack_argument(FIX((SI_Long)4L),argument_count,stack,
		    top_of_stack);
	return twrite_beginning_of_wide_string(array_constant_12,
		FIX((SI_Long)4L));
    }
}

/* PPRINT-RATE-OF-CHANGE-2-INSTRUCTION */
Object pprint_rate_of_change_2_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,33);
    return pprint_history_evaluator_with_time_units_between_time_intervals(string_constant_7,
	    stack,top_of_stack,FIX((SI_Long)6L));
}

/* PPRINT-INTEGRAL-2-INSTRUCTION */
Object pprint_integral_2_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,34);
    return pprint_history_evaluator_with_time_units_between_time_intervals(string_constant_8,
	    stack,top_of_stack,FIX((SI_Long)6L));
}

/* PPRINT-NUMBER-OF-DATAPOINTS-0-INSTRUCTION */
Object pprint_number_of_datapoints_0_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,35);
    return pprint_prefix_evaluator(string_constant_6,stack,top_of_stack);
}

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

/* PPRINT-HISTORIC-VALUE-INSTRUCTION */
Object pprint_historic_value_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    Object interval_qm;
    char stack_args_ok_qm;

    x_note_fn_call(207,36);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    interval_qm = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack) - 
	    (SI_Long)2L) : Qnil;
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)13L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)4L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_16,FIX((SI_Long)7L));
    if (interval_qm)
	print_constant(2,interval_qm,Qseconds);
    else
	write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)4L),stack,
		top_of_stack);
    return twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)4L));
}

static Object array_constant_17;   /* # */

/* PPRINT-VALUE-OF-PREVIOUS-DATAPOINT-INSTRUCTION */
Object pprint_value_of_previous_datapoint_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,37);
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)13L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)4L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_16,FIX((SI_Long)7L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)4L),stack,top_of_stack);
    return twrite_beginning_of_wide_string(array_constant_17,
	    FIX((SI_Long)15L));
}

static Object array_constant_18;   /* # */

/* PPRINT-INTERPOLATED-VALUE-INSTRUCTION */
Object pprint_interpolated_value_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    Object interval_qm;
    char stack_args_ok_qm;

    x_note_fn_call(207,38);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    interval_qm = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack) - 
	    (SI_Long)2L) : Qnil;
    twrite_beginning_of_wide_string(array_constant_18,FIX((SI_Long)26L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)4L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_16,FIX((SI_Long)7L));
    if (interval_qm)
	print_constant(2,interval_qm,Qseconds);
    else
	write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)4L),stack,
		top_of_stack);
    return twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)4L));
}

static Object array_constant_19;   /* # */

/* PPRINT-DISTANCE-BETWEEN-EVALUATOR */
Object pprint_distance_between_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,39);
    twrite_beginning_of_wide_string(array_constant_19,FIX((SI_Long)21L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_13,FIX((SI_Long)5L));
    return write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,
	    top_of_stack);
}

static Object array_constant_20;   /* # */

/* PPRINT-DISTANCE-BETWEEN-AND-THE-NEAREST-EVALUATOR */
Object pprint_distance_between_and_the_nearest_evaluator(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,40);
    twrite_beginning_of_wide_string(array_constant_19,FIX((SI_Long)21L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_20,FIX((SI_Long)17L));
    return write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,
	    top_of_stack);
}

static Object array_constant_21;   /* # */

/* PPRINT-HAS-A-VALUE-INSTRUCTION */
Object pprint_has_a_value_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,41);
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,top_of_stack);
    return twrite_beginning_of_wide_string(array_constant_21,
	    FIX((SI_Long)12L));
}

static Object array_constant_22;   /* # */

/* PPRINT-FIRST-THAT-HAS-A-VALUE-INSTRUCTION */
Object pprint_first_that_has_a_value_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,42);
    twrite_beginning_of_wide_string(array_constant_22,FIX((SI_Long)23L));
    return write_stack_argument(FIX((SI_Long)3L),FIX((SI_Long)3L),stack,
	    top_of_stack);
}

static Object array_constant_23;   /* # */

/* PPRINT-EXISTS-INSTRUCTION */
Object pprint_exists_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,43);
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    return twrite_beginning_of_wide_string(array_constant_23,FIX((SI_Long)7L));
}

static Object array_constant_24;   /* # */

/* PPRINT-CURRENT-TIME-EVALUATOR */
Object pprint_current_time_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,44);
    return twrite_beginning_of_wide_string(array_constant_24,
	    FIX((SI_Long)16L));
}

static Object array_constant_25;   /* # */

/* PPRINT-CURRENT-REAL-TIME-EVALUATOR */
Object pprint_current_real_time_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,45);
    return twrite_beginning_of_wide_string(array_constant_25,
	    FIX((SI_Long)21L));
}

static Object array_constant_26;   /* # */

/* PPRINT-COLLECTION-TIME-OF-INSTRUCTION */
Object pprint_collection_time_of_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,46);
    twrite_beginning_of_wide_string(array_constant_26,FIX((SI_Long)23L));
    return write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,
	    top_of_stack);
}

/* PPRINT-COLLECTION-TIME-OF-PREVIOUS-DATAPOINT-INSTRUCTION */
Object pprint_collection_time_of_previous_datapoint_instruction(description,
	    pc,byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,47);
    twrite_beginning_of_wide_string(array_constant_26,FIX((SI_Long)23L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)4L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_16,FIX((SI_Long)7L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)4L),stack,top_of_stack);
    return twrite_beginning_of_wide_string(array_constant_17,
	    FIX((SI_Long)15L));
}

static Object array_constant_27;   /* # */

/* PPRINT-EXPIRATION-TIME-OF-INSTRUCTION */
Object pprint_expiration_time_of_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,48);
    twrite_beginning_of_wide_string(array_constant_27,FIX((SI_Long)23L));
    return write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,
	    top_of_stack);
}

static Object array_constant_28;   /* # */

/* PPRINT-G2-LIST-OR-SEQUENCE-MEMBER-P-INSTRUCTION */
Object pprint_g2_list_or_sequence_member_p_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,49);
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_28,FIX((SI_Long)16L));
    return write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,
	    top_of_stack);
}

static Object array_constant_29;   /* # */

/* PPRINT-G2-LIST-OR-SEQUENCE-LENGTH-EVALUATOR */
Object pprint_g2_list_or_sequence_length_evaluator(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,50);
    twrite_beginning_of_wide_string(array_constant_29,FIX((SI_Long)26L));
    return write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,
	    top_of_stack);
}

static Object array_constant_30;   /* # */

/* PPRINT-ATTRIBUTE-NAME-EVALUATOR */
Object pprint_attribute_name_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,51);
    twrite_beginning_of_wide_string(array_constant_30,FIX((SI_Long)22L));
    return write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,
	    top_of_stack);
}

static Object array_constant_31;   /* # */

/* PPRINT-IS-RELATED-EVALUATOR */
Object pprint_is_related_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,52);
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)3L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)4L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)3L),stack,top_of_stack);
    twrite_character(FIX((SI_Long)32L));
    return write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)3L),stack,
	    top_of_stack);
}

static Object array_constant_32;   /* # */

/* PPRINT-IS-NOT-RELATED-EVALUATOR */
Object pprint_is_not_related_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,53);
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)3L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_32,FIX((SI_Long)8L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)3L),stack,top_of_stack);
    twrite_character(FIX((SI_Long)32L));
    return write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)3L),stack,
	    top_of_stack);
}

static Object array_constant_33;   /* # */

/* PPRINT-FALSE-EVALUATOR */
Object pprint_false_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,54);
    twrite_beginning_of_wide_string(array_constant_33,FIX((SI_Long)4L));
    return write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,
	    top_of_stack);
}

static Object array_constant_34;   /* # */

/* PPRINT-IS-OF-CLASS-EVALUATOR */
Object pprint_is_of_class_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,55);
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_34,FIX((SI_Long)9L));
    return write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,
	    top_of_stack);
}

static Object array_constant_35;   /* # */

/* PPRINT-IS-ACTIVE-EVALUATOR */
Object pprint_is_active_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,56);
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    return twrite_beginning_of_wide_string(array_constant_35,
	    FIX((SI_Long)19L));
}

static Object array_constant_36;   /* # */

/* PPRINT-HAS-A-NAME-EVALUATOR */
Object pprint_has_a_name_evaluator(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(207,57);
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    return twrite_beginning_of_wide_string(array_constant_36,
	    FIX((SI_Long)11L));
}

/* ADD-EVALUATION-QUANTITIES */
Object add_evaluation_quantities(x,y)
    Object x, y;
{
    Object temp;
    SI_int64 aref_new_value;
    double aref_new_value_1, temp_1, temp_2;

    x_note_fn_call(207,58);
    if (FIXNUMP(x)) {
	if (FIXNUMP(y))
	    temp = FIXNUM_ADD(x,y);
	else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L) {
	    temp = add(x,aref1(y,FIX((SI_Long)0L)));
	    aref_new_value = INTEGER_TO_INT64(temp);
	    set_aref1(y,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
	    temp = y;
	}
	else {
	    aref_new_value_1 = (double)IFIX(x) + DFLOAT_ISAREF_1(y,
		    (SI_Long)0L);
	    DFLOAT_ISASET_1(y,(SI_Long)0L,aref_new_value_1);
	    temp = y;
	}
    }
    else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L) {
	if (FIXNUMP(y)) {
	    temp = add(aref1(x,FIX((SI_Long)0L)),y);
	    aref_new_value = INTEGER_TO_INT64(temp);
	    set_aref1(x,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
	    temp = x;
	}
	else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L) {
	    temp = add(aref1(x,FIX((SI_Long)0L)),aref1(y,FIX((SI_Long)0L)));
	    aref_new_value = INTEGER_TO_INT64(temp);
	    set_aref1(y,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
	    reclaim_managed_simple_long_array_of_length_1(x);
	    temp = y;
	}
	else {
	    temp = normalize_to_gensym_float(x);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    aref_new_value_1 = temp_1 + DFLOAT_ISAREF_1(y,(SI_Long)0L);
	    DFLOAT_ISASET_1(y,(SI_Long)0L,aref_new_value_1);
	    reclaim_managed_simple_long_array_of_length_1(x);
	    temp = y;
	}
    }
    else if (FIXNUMP(y)) {
	aref_new_value_1 = DFLOAT_ISAREF_1(x,(SI_Long)0L) + (double)IFIX(y);
	DFLOAT_ISASET_1(x,(SI_Long)0L,aref_new_value_1);
	temp = x;
    }
    else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L) {
	temp_2 = DFLOAT_ISAREF_1(x,(SI_Long)0L);
	temp = normalize_to_gensym_float(y);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	aref_new_value_1 = temp_2 + temp_1;
	DFLOAT_ISASET_1(x,(SI_Long)0L,aref_new_value_1);
	reclaim_managed_simple_long_array_of_length_1(y);
	temp = x;
    }
    else {
	aref_new_value_1 = DFLOAT_ISAREF_1(x,(SI_Long)0L) + 
		DFLOAT_ISAREF_1(y,(SI_Long)0L);
	DFLOAT_ISASET_1(x,(SI_Long)0L,aref_new_value_1);
	reclaim_managed_simple_float_array_of_length_1(y);
	temp = x;
    }
    return VALUES_1(temp);
}

/* SUBTRACT-EVALUATION-QUANTITIES */
Object subtract_evaluation_quantities(x,y)
    Object x, y;
{
    Object temp;
    double aref_new_value, temp_1, temp_2;

    x_note_fn_call(207,59);
    if (FIXNUMP(x)) {
	if (FIXNUMP(y))
	    temp = FIXNUM_MINUS(x,y);
	else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L)
	    temp = minus(x,aref1(y,FIX((SI_Long)0L)));
	else {
	    aref_new_value = (double)IFIX(x) - DFLOAT_ISAREF_1(y,(SI_Long)0L);
	    DFLOAT_ISASET_1(y,(SI_Long)0L,aref_new_value);
	    temp = y;
	}
    }
    else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L) {
	if (FIXNUMP(y))
	    temp = minus(aref1(x,FIX((SI_Long)0L)),y);
	else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L)
	    temp = minus(aref1(x,FIX((SI_Long)0L)),aref1(y,FIX((SI_Long)0L)));
	else {
	    temp = normalize_to_gensym_float(x);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    aref_new_value = temp_1 - DFLOAT_ISAREF_1(y,(SI_Long)0L);
	    DFLOAT_ISASET_1(y,(SI_Long)0L,aref_new_value);
	    temp = y;
	}
    }
    else if (FIXNUMP(y)) {
	aref_new_value = DFLOAT_ISAREF_1(x,(SI_Long)0L) - (double)IFIX(y);
	DFLOAT_ISASET_1(x,(SI_Long)0L,aref_new_value);
	temp = x;
    }
    else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L) {
	temp_2 = DFLOAT_ISAREF_1(x,(SI_Long)0L);
	temp = normalize_to_gensym_float(y);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	aref_new_value = temp_2 - temp_1;
	DFLOAT_ISASET_1(x,(SI_Long)0L,aref_new_value);
	temp = x;
    }
    else {
	aref_new_value = DFLOAT_ISAREF_1(x,(SI_Long)0L) - 
		DFLOAT_ISAREF_1(y,(SI_Long)0L);
	DFLOAT_ISASET_1(x,(SI_Long)0L,aref_new_value);
	reclaim_managed_simple_float_array_of_length_1(y);
	temp = x;
    }
    return VALUES_1(temp);
}

/* MULTIPLY-EVALUATION-QUANTITIES */
Object multiply_evaluation_quantities(x,y)
    Object x, y;
{
    Object temp;
    SI_int64 aref_new_value;
    double aref_new_value_1, temp_1, temp_2;

    x_note_fn_call(207,60);
    if (FIXNUMP(x)) {
	if (FIXNUMP(y))
	    temp = FIXNUM_TIMES(x,y);
	else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L) {
	    temp = ltimes(x,aref1(y,FIX((SI_Long)0L)));
	    aref_new_value = INTEGER_TO_INT64(temp);
	    set_aref1(y,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
	    temp = y;
	}
	else {
	    aref_new_value_1 = (double)IFIX(x) * DFLOAT_ISAREF_1(y,
		    (SI_Long)0L);
	    DFLOAT_ISASET_1(y,(SI_Long)0L,aref_new_value_1);
	    temp = y;
	}
    }
    else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L) {
	if (FIXNUMP(y)) {
	    temp = ltimes(aref1(x,FIX((SI_Long)0L)),y);
	    aref_new_value = INTEGER_TO_INT64(temp);
	    set_aref1(x,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
	    temp = x;
	}
	else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L) {
	    temp = ltimes(aref1(x,FIX((SI_Long)0L)),aref1(y,FIX((SI_Long)0L)));
	    aref_new_value = INTEGER_TO_INT64(temp);
	    set_aref1(x,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
	    reclaim_managed_simple_long_array_of_length_1(y);
	    temp = x;
	}
	else {
	    temp = normalize_to_gensym_float(x);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    aref_new_value_1 = temp_1 * DFLOAT_ISAREF_1(y,(SI_Long)0L);
	    DFLOAT_ISASET_1(y,(SI_Long)0L,aref_new_value_1);
	    reclaim_managed_simple_float_array_of_length_1(y);
	    temp = y;
	}
    }
    else if (FIXNUMP(y)) {
	aref_new_value_1 = DFLOAT_ISAREF_1(x,(SI_Long)0L) * (double)IFIX(y);
	DFLOAT_ISASET_1(x,(SI_Long)0L,aref_new_value_1);
	temp = x;
    }
    else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L) {
	temp_2 = DFLOAT_ISAREF_1(x,(SI_Long)0L);
	temp = normalize_to_gensym_float(y);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	aref_new_value_1 = temp_2 * temp_1;
	DFLOAT_ISASET_1(x,(SI_Long)0L,aref_new_value_1);
	reclaim_managed_simple_long_array_of_length_1(y);
	temp = x;
    }
    else {
	aref_new_value_1 = DFLOAT_ISAREF_1(x,(SI_Long)0L) * 
		DFLOAT_ISAREF_1(y,(SI_Long)0L);
	DFLOAT_ISASET_1(x,(SI_Long)0L,aref_new_value_1);
	reclaim_managed_simple_float_array_of_length_1(y);
	temp = x;
    }
    return VALUES_1(temp);
}

static Object Qfloat_array;        /* float-array */

/* EXPT-EVALUATION-QUANTITIES */
Object expt_evaluation_quantities(base_number,power_number,top_of_stack)
    Object base_number, power_number, top_of_stack;
{
    Object e_float_base, amf_available_array_cons_qm, amf_array, temp, temp_1;
    Object amf_result, new_float, temp_2, e_float_power;
    double aref_new_value;

    x_note_fn_call(207,61);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(base_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(base_number)) == (SI_Long)1L)
	e_float_base = base_number;
    else {
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
	if (FIXNUMP(base_number))
	    aref_new_value = (double)IFIX(base_number);
	else if (INLINE_LONG_VECTOR_P(base_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(base_number)) == (SI_Long)1L) {
	    temp_2 = convert_g2longint_to_double(aref1(base_number,
		    FIX((SI_Long)0L)));
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	}
	else
	    aref_new_value = DFLOAT_ISAREF_1(base_number,(SI_Long)0L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_2 = new_float;
	reclaim_evaluation_quantity(base_number);
	e_float_base = temp_2;
    }
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(power_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(power_number)) == (SI_Long)1L)
	e_float_power = power_number;
    else {
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
	if (FIXNUMP(power_number))
	    aref_new_value = (double)IFIX(power_number);
	else if (INLINE_LONG_VECTOR_P(power_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(power_number)) == (SI_Long)1L) {
	    temp_2 = convert_g2longint_to_double(aref1(power_number,
		    FIX((SI_Long)0L)));
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	}
	else
	    aref_new_value = DFLOAT_ISAREF_1(power_number,(SI_Long)0L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_2 = new_float;
	reclaim_evaluation_quantity(power_number);
	e_float_power = temp_2;
    }
    return g2_exponent_evaluation_float(e_float_base,e_float_power,
	    top_of_stack);
}

static Object string_constant_9;   /* "The arguments to the exponent operator were a base ~NV and a ~
				    *                negative power ~NV.  These values produce an undefined result."
				    */

static Object string_constant_10;  /* "The arguments to the exponent operator were a negative ~
				    *                 base ~NV and a floating point power ~NV.  These values ~
				    *                 produce a complex number, which is not supported in G2."
				    */

/* G2-EXPONENT-EVALUATION-FLOAT */
Object g2_exponent_evaluation_float(evaluation_float_base,
	    evaluation_float_power,top_of_stack)
    Object evaluation_float_base, evaluation_float_power, top_of_stack;
{
    Object top_of_stack_1, message_1, truncated_power, temp;
    double arg, arg_1, aref_new_value;

    x_note_fn_call(207,62);
    arg = DFLOAT_ISAREF_1(evaluation_float_base,(SI_Long)0L);
    arg_1 = 0.0;
    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	aref_new_value = pow(DFLOAT_ISAREF_1(evaluation_float_base,
		(SI_Long)0L),DFLOAT_ISAREF_1(evaluation_float_power,
		(SI_Long)0L));
	DFLOAT_ISASET_1(evaluation_float_base,(SI_Long)0L,aref_new_value);
	reclaim_managed_simple_float_array_of_length_1(evaluation_float_power);
	return VALUES_1(evaluation_float_base);
    }
    else {
	arg = DFLOAT_ISAREF_1(evaluation_float_base,(SI_Long)0L);
	arg_1 = 0.0;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    arg = DFLOAT_ISAREF_1(evaluation_float_power,(SI_Long)0L);
	    arg_1 = 0.0;
	    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		DFLOAT_ISASET_1(evaluation_float_base,(SI_Long)0L,1.0);
		reclaim_managed_simple_float_array_of_length_1(evaluation_float_power);
		return VALUES_1(evaluation_float_base);
	    }
	    else {
		arg = DFLOAT_ISAREF_1(evaluation_float_power,(SI_Long)0L);
		arg_1 = 0.0;
		if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    DFLOAT_ISASET_1(evaluation_float_base,(SI_Long)0L,0.0);
		    reclaim_managed_simple_float_array_of_length_1(evaluation_float_power);
		    return VALUES_1(evaluation_float_base);
		}
		else {
		    top_of_stack_1 = top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_9,evaluation_float_base,
			    evaluation_float_power);
		    return raw_stack_error_named_error(top_of_stack_1,
			    message_1);
		}
	    }
	}
	else {
	    truncated_power = 
		    ltruncate(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(evaluation_float_power,
		    (SI_Long)0L)),_);
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(evaluation_float_power,
		    (SI_Long)0L));
	    if (NUM_EQ(temp,truncated_power)) {
		temp = 
			expt(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(evaluation_float_base,
			(SI_Long)0L)),truncated_power);
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
		DFLOAT_ISASET_1(evaluation_float_base,(SI_Long)0L,
			aref_new_value);
		reclaim_managed_simple_float_array_of_length_1(evaluation_float_power);
		return VALUES_1(evaluation_float_base);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_10,evaluation_float_base,
			evaluation_float_power);
		return raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
    }
}

static Object Qpush_constant;      /* push-constant */

/* QUOTE-STACK-NODE-CONVERTER */
Object quote_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol;

    x_note_fn_call(207,63);
    gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
	    SECOND(expression));
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qab_let;             /* let */

/* LET-STACK-NODE-CONVERTER */
Object let_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, bindings, sub_expression, binding_name;
    Object binding_expression_qm, ab_loop_list_, var_spot, expression_list;
    Object ab_loopvar_, ab_loopvar__1, var_spot_list, ab_loopvar__2;
    Object ab_loop_desetq_, temp, new_node, svref_new_value;

    x_note_fn_call(207,64);
    gensymed_symbol = expression;
    gensymed_symbol = CDR(gensymed_symbol);
    bindings = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    sub_expression = CAR(gensymed_symbol);
    binding_name = Nil;
    binding_expression_qm = Nil;
    ab_loop_list_ = bindings;
    var_spot = Nil;
    expression_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    var_spot_list = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    binding_name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    binding_expression_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    var_spot = generate_new_stack_frame_var_spot(Qitem_or_datum);
    if (binding_expression_qm) {
	ab_loopvar__1 = 
		stack_cons_1(convert_expression_to_stack_node_tree(binding_expression_qm),
		Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    expression_list = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    if (binding_expression_qm) {
	ab_loopvar__1 = phrase_cons(var_spot,Nil);
	if (ab_loopvar__2)
	    M_CDR(ab_loopvar__2) = ab_loopvar__1;
	else
	    var_spot_list = ab_loopvar__1;
	ab_loopvar__2 = ab_loopvar__1;
    }
    Expression_bound_local_names = phrase_cons(phrase_cons(binding_name,
	    var_spot),Expression_bound_local_names);
    goto next_loop;
  end_loop:
    gensymed_symbol = make_stack_node_instruction_1_1(Qab_let,var_spot_list);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    new_node = gensymed_symbol;
    temp = expression_list;
    svref_new_value = nconc2(temp,
	    stack_cons_1(convert_expression_to_stack_node_tree(sub_expression),
	    Nil));
    SVREF(new_node,FIX((SI_Long)2L)) = svref_new_value;
    temp = new_node;
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

/* LET-I-CHOOSER */
Object let_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, unknown_arguments_qm;
    Object argument_nodes, binding_expressions, binding_type, temp;
    Object result_expression, cons_1, temp_1, result_type;

    x_note_fn_call(207,65);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    unknown_arguments_qm = Nil;
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    binding_expressions = argument_nodes;
    binding_type = 
	    maybe_add_no_item_implies_unknown(maybe_add_unknown(list_constant_2,
	    unknown_allowed_qm),no_item_implies_unknown_allowed_qm);
    temp = last(argument_nodes,_);
    result_expression = CAR(temp);
    cons_1 = binding_expressions;
  next_loop:
    if ( !TRUEP(cons_1))
	goto end_loop;
    if ( !TRUEP(M_CDR(cons_1)))
	goto end_loop;
    temp_1 = choose_stack_node_instructions_and_types(2,CAR(cons_1),
	    binding_type);
    M_CAR(cons_1) = temp_1;
    if ( !TRUEP(unknown_arguments_qm) && 
	    type_specification_subtype_p(list_constant,ISVREF(CAR(cons_1),
	    (SI_Long)6L)))
	unknown_arguments_qm = T;
    cons_1 = M_CDR(cons_1);
    goto next_loop;
  end_loop:;
    result_expression = choose_stack_node_instructions_and_types(2,
	    result_expression,required_type);
    temp_1 = last(argument_nodes,_);
    M_CAR(temp_1) = result_expression;
    result_type = ISVREF(result_expression,(SI_Long)6L);
    if ( !TRUEP(type_specification_subtype_p(list_constant,result_type)) 
	    && unknown_arguments_qm)
	result_type = make_type_specification_union(result_type,list_constant);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = result_type;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* LET-I-EMIT */
Object let_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object var_spots, argument_nodes, binding_expressions, var_spot;
    Object ab_loop_list_, binding_expression, ab_loop_list__1, temp;

    x_note_fn_call(207,66);
    var_spots = extra_info;
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    binding_expressions = argument_nodes;
    var_spot = Nil;
    ab_loop_list_ = var_spots;
    binding_expression = Nil;
    ab_loop_list__1 = binding_expressions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    var_spot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    binding_expression = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    emit_stack_node_tree(byte_code_stream,binding_expression);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,var_spot);
    goto next_loop;
  end_loop:;
    temp = last(argument_nodes,_);
    emit_stack_node_tree(byte_code_stream,CAR(temp));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qformat_form;        /* format-form */

/* FORMAT-FORM-STACK-NODE-CONVERTER */
Object format_form_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, format_form_node, argument, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(207,67);
    gensymed_symbol = make_stack_node_instruction_1_1(Qformat_form,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    format_form_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(text_string_p(argument) && IFIX(text_string_length(argument)) 
	    == (SI_Long)0L)) {
	ab_loopvar__2 = 
		stack_cons_1(convert_expression_to_stack_node_tree(argument),
		Nil);
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
    SVREF(format_form_node,FIX((SI_Long)2L)) = ab_loopvar_;
    GENSYM_RETURN_ONE(format_form_node);
    return VALUES_1(Nil);
}

static Object list_constant_3;     /* # */

static Object Qdatum;              /* datum */

static Object list_constant_4;     /* # */

static Object Qtext;               /* text */

/* FORMAT-FORM-I-CHOOSER */
Object format_form_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm, argument_nodes;
    Object unknown_argument_qm, argument_node_cons, temp;

    x_note_fn_call(207,68);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_argument_qm = Nil;
    argument_node_cons = argument_nodes;
  next_loop:
    if ( !TRUEP(argument_node_cons))
	goto end_loop;
    temp = choose_stack_node_instructions_and_types(2,
	    CAR(argument_node_cons),unknown_allowed_qm ? list_constant_3 : 
	    Qdatum);
    M_CAR(argument_node_cons) = temp;
    if (type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_node_cons),(SI_Long)6L)))
	unknown_argument_qm = T;
    argument_node_cons = M_CDR(argument_node_cons);
    goto next_loop;
  end_loop:;
    temp = unknown_argument_qm ? list_constant_4 : Qtext;
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* FORMAT-FORM-I-EMIT */
Object format_form_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, node, ab_loop_list_;

    x_note_fn_call(207,69);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    node = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,node);
    goto next_loop;
  end_loop:;
    emit_funcall_instruction_byte_codes(4,byte_code_stream,Qformat_form,
	    length(argument_nodes),FIX((SI_Long)1L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qsymbol_name_wide_string;  /* symbol-name-wide-string */

static Object Qab_gensym;          /* gensym */

/* FUNCALL-FORMAT-FORM-INST */
Object funcall_format_form_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object index_1, string_1_qm, general_cases, arg, incff_1_arg_1;
    Object gensymed_symbol_4, list_1, wide_string_bv16, wide_string_list;
    Object length_3, temp_1, result_1, source_arg, source_string;
    Object gensymed_symbol_5, gensym_pop_store, cons_1, next_cons, temp_2;
    Object svref_arg_2, wide_string_bv16_1;
    SI_Long arg_count, first_index, last_index, total_length, length_1;
    SI_Long length_2, incff_1_arg, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long tmpf, gensymed_symbol_2, gensymed_symbol_3, fill_1, bv16_length;
    SI_Long aref_arg_2, aref_new_value;
    Object result;

    x_note_fn_call(207,70);
    arg_count = IFIX(ISVREF(local_stack,IFIX(top_of_stack)));
    first_index = IFIX(top_of_stack) - arg_count;
    last_index = IFIX(FIXNUM_SUB1(top_of_stack));
    index_1 = FIX(first_index);
    total_length = (SI_Long)0L;
    string_1_qm = Nil;
    length_1 = (SI_Long)0L;
    general_cases = Qnil;
  next_loop:
    if (IFIX(index_1) > last_index)
	goto end_loop;
    arg = ISVREF(local_stack,IFIX(index_1));
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(arg) != (SI_Long)0L) {
	length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg));
	incff_1_arg = UBYTE_16_ISAREF_1(arg,length_2 - (SI_Long)2L) + 
		((UBYTE_16_ISAREF_1(arg,length_2 - (SI_Long)1L) & 
		(SI_Long)8191L) << (SI_Long)16L);
	total_length = total_length + incff_1_arg;
	if (IFIX(index_1) == (SI_Long)0L) {
	    string_1_qm = arg;
	    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg));
	    length_1 = UBYTE_16_ISAREF_1(arg,length_2 - (SI_Long)2L) + 
		    ((UBYTE_16_ISAREF_1(arg,length_2 - (SI_Long)1L) & 
		    (SI_Long)8191L) << (SI_Long)16L);
	}
    }
    else if (FIXNUMP(arg)) {
	gensymed_symbol = IFIX(arg);
	if (gensymed_symbol == IFIX(Most_negative_fixnum))
	    incff_1_arg_1 = Length_of_most_negative_fixnum_as_string;
	else if (gensymed_symbol <= (SI_Long)999999L && gensymed_symbol >= 
		(SI_Long)-999999L) {
	    gensymed_symbol_1 = gensymed_symbol < (SI_Long)0L ? 
		    (SI_Long)1L : (SI_Long)0L;
	    gensymed_symbol = ABS(gensymed_symbol);
	    gensymed_symbol = gensymed_symbol < (SI_Long)10000L ? 
		    (gensymed_symbol < (SI_Long)100L ? (gensymed_symbol < 
		    (SI_Long)10L ? (SI_Long)1L : (SI_Long)2L) : 
		    gensymed_symbol < (SI_Long)1000L ? (SI_Long)3L : 
		    (SI_Long)4L) : gensymed_symbol < (SI_Long)1000000L ? 
		    (gensymed_symbol < (SI_Long)100000L ? (SI_Long)5L : 
		    (SI_Long)6L) : gensymed_symbol < (SI_Long)10000000L ? 
		    (SI_Long)7L : gensymed_symbol < (SI_Long)100000000L ? 
		    (SI_Long)8L : (SI_Long)9L;
	    incff_1_arg_1 = FIX(gensymed_symbol_1 + gensymed_symbol);
	}
	else {
	    temp = ABS(gensymed_symbol) / (SI_Long)1000000L;
	    tmpf = temp;
	    gensymed_symbol = gensymed_symbol < (SI_Long)0L ? (SI_Long)1L :
		     (SI_Long)0L;
	    gensymed_symbol_1 = (SI_Long)6L;
	    gensymed_symbol_2 = tmpf;
	    if (gensymed_symbol_2 <= (SI_Long)999999L)
		gensymed_symbol_2 = gensymed_symbol_2 < (SI_Long)10000L ? 
			(gensymed_symbol_2 < (SI_Long)100L ? 
			(gensymed_symbol_2 < (SI_Long)10L ? (SI_Long)1L : 
			(SI_Long)2L) : gensymed_symbol_2 < (SI_Long)1000L ?
			 (SI_Long)3L : (SI_Long)4L) : gensymed_symbol_2 < 
			(SI_Long)1000000L ? (gensymed_symbol_2 < 
			(SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) : 
			gensymed_symbol_2 < (SI_Long)10000000L ? 
			(SI_Long)7L : gensymed_symbol_2 < 
			(SI_Long)100000000L ? (SI_Long)8L : (SI_Long)9L;
	    else {
		temp = gensymed_symbol_2 / (SI_Long)1000000L;
		tmpf = temp;
		gensymed_symbol_2 = (SI_Long)6L;
		gensymed_symbol_3 = tmpf;
		gensymed_symbol_3 = gensymed_symbol_3 < (SI_Long)10000L ? 
			(gensymed_symbol_3 < (SI_Long)100L ? 
			(gensymed_symbol_3 < (SI_Long)10L ? (SI_Long)1L : 
			(SI_Long)2L) : gensymed_symbol_3 < (SI_Long)1000L ?
			 (SI_Long)3L : (SI_Long)4L) : gensymed_symbol_3 < 
			(SI_Long)1000000L ? (gensymed_symbol_3 < 
			(SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) : 
			gensymed_symbol_3 < (SI_Long)10000000L ? 
			(SI_Long)7L : gensymed_symbol_3 < 
			(SI_Long)100000000L ? (SI_Long)8L : (SI_Long)9L;
		gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
	    }
	    incff_1_arg_1 = FIX(gensymed_symbol + gensymed_symbol_1 + 
		    gensymed_symbol_2);
	}
	total_length = total_length + IFIX(incff_1_arg_1);
    }
    else if (arg && SYMBOLP(arg)) {
	gensymed_symbol_4 = arg;
	list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol_4);
      next_loop_1:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qsymbol_name_wide_string))
	    goto end_loop_1;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_1;
      end_loop_1:
	wide_string_bv16 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	if (wide_string_bv16);
	else
	    wide_string_bv16 = mutate_global_property(gensymed_symbol_4,
		    make_symbol_name_wide_string(gensymed_symbol_4),
		    Qsymbol_name_wide_string);
	length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	incff_1_arg = UBYTE_16_ISAREF_1(wide_string_bv16,length_2 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16,
		length_2 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	total_length = total_length + incff_1_arg;
    }
    else {
	result = write_evaluation_value_to_wide_string_list(arg);
	MVS_2(result,wide_string_list,length_3);
	incff_1_arg_1 = length_3;
	total_length = total_length + IFIX(incff_1_arg_1);
	general_cases = nconc2(general_cases,
		gensym_cons_1(wide_string_list,Nil));
    }
    index_1 = FIXNUM_ADD1(index_1);
    goto next_loop;
  end_loop:
    if (total_length > IFIX(Maximum_length_for_user_text_strings))
	temp_1 = format_form_too_long(local_stack,top_of_stack,
		FIX(arg_count),FIX(total_length),general_cases);
    else if (string_1_qm && total_length <= 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1_qm)) - (SI_Long)3L) {
	result_1 = string_1_qm;
	fill_1 = length_1;
	index_1 = FIX(first_index + (SI_Long)1L);
      next_loop_2:
	if (IFIX(index_1) > last_index)
	    goto end_loop_2;
	source_arg = ISVREF(local_stack,IFIX(index_1));
	length_2 = (SI_Long)0L;
	if (FIXNUMP(source_arg))
	    length_2 = IFIX(twrite_fixnum_into_wide_string(source_arg,
		    result_1,FIX(fill_1)));
	else if (source_arg && SYMBOLP(source_arg)) {
	    source_string = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(source_arg),
		    Qsymbol_name_wide_string);
	    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(source_string));
	    length_2 = UBYTE_16_ISAREF_1(source_string,length_2 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(source_string,
		    length_2 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	    gensymed_symbol_4 = source_string;
	    gensymed_symbol = (SI_Long)0L;
	    gensymed_symbol_5 = result_1;
	    gensymed_symbol_1 = fill_1;
	    gensymed_symbol_2 = length_2 - (SI_Long)0L;
	    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_4),
		    gensymed_symbol,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_5),
		    gensymed_symbol_1,gensymed_symbol_2);
	}
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(source_arg) != (SI_Long)0L) {
	    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(source_arg));
	    length_2 = UBYTE_16_ISAREF_1(source_arg,length_2 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(source_arg,length_2 
		    - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	    gensymed_symbol_4 = source_arg;
	    gensymed_symbol = (SI_Long)0L;
	    gensymed_symbol_5 = result_1;
	    gensymed_symbol_1 = fill_1;
	    gensymed_symbol_2 = length_2 - (SI_Long)0L;
	    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_4),
		    gensymed_symbol,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_5),
		    gensymed_symbol_1,gensymed_symbol_2);
	    reclaim_wide_string(source_arg);
	}
	else {
	    gensym_pop_store = Nil;
	    cons_1 = general_cases;
	    if (cons_1) {
		gensym_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qab_gensym);
		if (ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = cons_1;
		    temp_2 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		}
		else {
		    temp_2 = Available_gensym_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		    temp_2 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    general_cases = next_cons;
	    length_2 = 
		    IFIX(copy_wide_string_list_text_to_wide_string_and_reclaim(gensym_pop_store,
		    result_1,FIX(fill_1)));
	    reclaim_evaluation_value(source_arg);
	}
	incff_1_arg = length_2;
	fill_1 = fill_1 + incff_1_arg;
	index_1 = FIXNUM_ADD1(index_1);
	goto next_loop_2;
      end_loop_2:
	if (general_cases)
	    reclaim_gensym_list_1(general_cases);
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(result_1));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = total_length & (SI_Long)65535L;
	UBYTE_16_ISASET_1(result_1,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | total_length >>  -  - (SI_Long)16L;
	UBYTE_16_ISASET_1(result_1,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(result_1,total_length,(SI_Long)0L);
	ISVREF(local_stack,first_index) = result_1;
	temp_1 = Nil;
    }
    else {
	wide_string_bv16_1 = allocate_byte_vector_16(FIX(total_length + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16_1));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = total_length & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16_1,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | total_length >>  -  - (SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16_1,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16_1,total_length,(SI_Long)0L);
	result_1 = wide_string_bv16_1;
	fill_1 = (SI_Long)0L;
	index_1 = FIX(first_index + (SI_Long)0L);
      next_loop_3:
	if (IFIX(index_1) > last_index)
	    goto end_loop_3;
	source_arg = ISVREF(local_stack,IFIX(index_1));
	length_2 = (SI_Long)0L;
	if (FIXNUMP(source_arg))
	    length_2 = IFIX(twrite_fixnum_into_wide_string(source_arg,
		    result_1,FIX(fill_1)));
	else if (source_arg && SYMBOLP(source_arg)) {
	    source_string = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(source_arg),
		    Qsymbol_name_wide_string);
	    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(source_string));
	    length_2 = UBYTE_16_ISAREF_1(source_string,length_2 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(source_string,
		    length_2 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	    gensymed_symbol_4 = source_string;
	    gensymed_symbol = (SI_Long)0L;
	    gensymed_symbol_5 = result_1;
	    gensymed_symbol_1 = fill_1;
	    gensymed_symbol_2 = length_2 - (SI_Long)0L;
	    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_4),
		    gensymed_symbol,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_5),
		    gensymed_symbol_1,gensymed_symbol_2);
	}
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(source_arg) != (SI_Long)0L) {
	    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(source_arg));
	    length_2 = UBYTE_16_ISAREF_1(source_arg,length_2 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(source_arg,length_2 
		    - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	    gensymed_symbol_4 = source_arg;
	    gensymed_symbol = (SI_Long)0L;
	    gensymed_symbol_5 = result_1;
	    gensymed_symbol_1 = fill_1;
	    gensymed_symbol_2 = length_2 - (SI_Long)0L;
	    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_4),
		    gensymed_symbol,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_5),
		    gensymed_symbol_1,gensymed_symbol_2);
	    reclaim_wide_string(source_arg);
	}
	else {
	    gensym_pop_store = Nil;
	    cons_1 = general_cases;
	    if (cons_1) {
		gensym_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qab_gensym);
		if (ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = cons_1;
		    temp_2 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		}
		else {
		    temp_2 = Available_gensym_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		    temp_2 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    general_cases = next_cons;
	    length_2 = 
		    IFIX(copy_wide_string_list_text_to_wide_string_and_reclaim(gensym_pop_store,
		    result_1,FIX(fill_1)));
	    reclaim_evaluation_value(source_arg);
	}
	incff_1_arg = length_2;
	fill_1 = fill_1 + incff_1_arg;
	index_1 = FIXNUM_ADD1(index_1);
	goto next_loop_3;
      end_loop_3:
	if (general_cases)
	    reclaim_gensym_list_1(general_cases);
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(result_1));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = total_length & (SI_Long)65535L;
	UBYTE_16_ISASET_1(result_1,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | total_length >>  -  - (SI_Long)16L;
	UBYTE_16_ISASET_1(result_1,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(result_1,total_length,(SI_Long)0L);
	ISVREF(local_stack,first_index) = result_1;
	temp_1 = Nil;
    }
    return VALUES_1(temp_1);
}

static Object Qwide_string;        /* wide-string */

/* WRITE-EVALUATION-VALUE-TO-WIDE-STRING-LIST */
Object write_evaluation_value_to_wide_string_list(evaluation_value)
    Object evaluation_value;
{
    Object evaluation_value_writing_target_length_qm, wide_string_bv16;
    Object new_wide_string, current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object aref_arg_1, aref_arg_2_1, wide_string_list, string_1, ab_loop_list_;
    Object ab_loopvar_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(207,71);
    evaluation_value_writing_target_length_qm = 
	    Maximum_length_for_user_text_strings;
    PUSH_SPECIAL_WITH_SYMBOL(Evaluation_value_writing_target_length_qm,Qevaluation_value_writing_target_length_qm,evaluation_value_writing_target_length_qm,
	    5);
      wide_string_bv16 = 
	      allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
	      + (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = IFIX(Wide_string_list_maximum_length) & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,
	      IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
      new_wide_string = wide_string_bv16;
      current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	      4);
	current_wide_string = new_wide_string;
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
		write_evaluation_value(1,evaluation_value);
		aref_arg_1 = Current_wide_string;
		aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(aref_arg_1));
		aref_arg_2 = bv16_length - (SI_Long)2L;
		aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
		UBYTE_16_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
		aref_arg_2 = bv16_length - (SI_Long)1L;
		aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2_1) >>  
			-  - (SI_Long)16L;
		UBYTE_16_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
		UBYTE_16_ISASET_1(aref_arg_1,IFIX(aref_arg_2_1),(SI_Long)0L);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	wide_string_list = Current_wide_string_list;
      POP_SPECIAL();
      string_1 = Nil;
      ab_loop_list_ = wide_string_list;
      ab_loopvar_ = FIX((SI_Long)0L);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      string_1 = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
      ab_loopvar_ = add(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
	      (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
	      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),ab_loopvar_);
      goto next_loop;
    end_loop:
      temp = ab_loopvar_;
      goto end_1;
      temp = Qnil;
    end_1:;
      result = VALUES_2(wide_string_list,temp);
    POP_SPECIAL();
    return result;
}

/* COPY-WIDE-STRING-LIST-TEXT-TO-WIDE-STRING-AND-RECLAIM */
Object copy_wide_string_list_text_to_wide_string_and_reclaim(wide_string_list,
	    destination_string,destination_start)
    Object wide_string_list, destination_string, destination_start;
{
    Object string_1, ab_loop_list_, dest_start, length_1, ab_loopvar_;
    Object ab_loop_iter_flag_, gensymed_symbol, gensymed_symbol_2, temp_1;
    SI_Long length_2, arg, arg_1, arg_2, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;

    x_note_fn_call(207,72);
    string_1 = Nil;
    ab_loop_list_ = wide_string_list;
    dest_start = destination_start;
    length_1 = Nil;
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	dest_start = FIXNUM_ADD(dest_start,length_1);
    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    length_1 = FIX(UBYTE_16_ISAREF_1(string_1,length_2 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_2 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L));
    if (EQ(string_1,destination_string)) {
	if ((SI_Long)0L == IFIX(length_1))
	    temp = TRUEP(T);
	else {
	    temp = (SI_Long)0L < IFIX(dest_start) ? FIXNUM_LT(dest_start,
		    length_1) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = IFIX(dest_start);
		arg_1 = (SI_Long)0L;
		arg_2 = IFIX(dest_start) + (IFIX(length_1) - (SI_Long)0L);
		temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp) {
		copy_byte_vector_16_portion_carefully(string_1,
			FIX((SI_Long)0L),destination_string,dest_start,
			FIX(IFIX(length_1) - (SI_Long)0L));
		temp = TRUEP(T);
	    }
	    else
		temp = TRUEP(Qnil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp);
    else {
	gensymed_symbol = string_1;
	gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = destination_string;
	gensymed_symbol_3 = IFIX(dest_start);
	gensymed_symbol_4 = IFIX(length_1) - (SI_Long)0L;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    reclaim_wide_string(string_1);
    ab_loopvar_ = add(length_1,ab_loopvar_);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    reclaim_gensym_list_1(wide_string_list);
    return VALUES_1(temp_1);
}

static Object Qdo_not_use;         /* do-not-use */

static Object string_constant_11;  /* "A text value cannot contain more than ~a characters.  The text ~
				    *                   begins with \"~a...\" and contains ~a characters."
				    */

/* FORMAT-FORM-TOO-LONG */
Object format_form_too_long(local_stack,top_of_stack,arg_count,
	    result_text_length,general_case_list)
    Object local_stack, top_of_stack, arg_count, result_text_length;
    Object general_case_list;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object n_1, arg, string_1, evaluation_value_writing_target_length_qm;
    Object small_formatted_string, error_string, wsl, ab_loop_list_, ws;
    Object ab_loop_list__1;
    SI_Long bv16_length, temp, aref_new_value, length_1, i, ab_loop_repeat_;
    SI_Long decff_1_arg;
    Declare_special(11);

    x_note_fn_call(207,73);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    10);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      temp = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
      temp = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      9);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		8);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  7);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    6);
	      n_1 = FIX((SI_Long)20L);
	      i = IFIX(FIXNUM_MINUS(top_of_stack,arg_count));
	      arg = Nil;
	      ab_loop_repeat_ = IFIX(arg_count);
	    next_loop:
	      arg = ISVREF(local_stack,i);
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(arg) != (SI_Long)0L)
		  string_1 = copy_wide_string(arg);
	      else {
		  evaluation_value_writing_target_length_qm = 
			  FIX((SI_Long)20L);
		  PUSH_SPECIAL_WITH_SYMBOL(Evaluation_value_writing_target_length_qm,Qevaluation_value_writing_target_length_qm,evaluation_value_writing_target_length_qm,
			  5);
		    current_wide_string_list = Qdo_not_use;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			    4);
		      wide_string_bv16 = 
			      allocate_byte_vector_16(FIX((SI_Long)2048L + 
			      (SI_Long)3L));
		      bv16_length = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		      temp = bv16_length - (SI_Long)2L;
		      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		      temp = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		      UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
			      write_evaluation_value(1,arg);
			      string_1 = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	      length_1 = UBYTE_16_ISAREF_1(string_1,length_1 - 
		      (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 
		      - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	      twrite_beginning_of_wide_string(string_1,FIX(MIN(IFIX(n_1),
		      length_1)));
	      reclaim_wide_string(string_1);
	      decff_1_arg = length_1;
	      temp = IFIX(n_1) - decff_1_arg;
	      n_1 = FIX(temp);
	      if ( !(IFIX(n_1) > (SI_Long)0L))
		  goto end_loop;
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      small_formatted_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    error_string = tformat_stack_error_text_string(4,string_constant_11,
	    Maximum_length_for_user_text_strings,small_formatted_string,
	    result_text_length);
    reclaim_wide_string(small_formatted_string);
    wsl = Nil;
    ab_loop_list_ = general_case_list;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    wsl = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ws = Nil;
    ab_loop_list__1 = wsl;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    ws = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    reclaim_wide_string(ws);
    goto next_loop_2;
  end_loop_2:;
    reclaim_gensym_list_1(wsl);
    goto next_loop_1;
  end_loop_1:
    reclaim_gensym_list_1(general_case_list);
    return VALUES_1(error_string);
}

static Object string_constant_12;  /* "Unrecognized format control argument ~a" */

/* EVAL-FORMAT-FUNCALLED */
Object eval_format_funcalled(value,format_string_or_unit)
    Object value, format_string_or_unit;
{
    Object quantity_value, format_value, text_value, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object top_of_stack, message_1, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);

    x_note_fn_call(207,74);
    quantity_value = evaluation_quantity_value(value);
    format_value = evaluation_value_value(format_string_or_unit);
    text_value = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Text_value,Qtext_value,text_value,5);
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
		if (EQ(format_value,Qtime_stamp))
		    print_constant(2,quantity_value,Qtime_stamp);
		else if (EQ(format_value,Qseconds))
		    print_constant(2,quantity_value,Qseconds);
		else {
		    top_of_stack = Cached_top_of_stack;
		    message_1 = tformat_stack_error_text_string(2,
			    string_constant_12,format_value);
		    raw_stack_error_named_error(top_of_stack,message_1);
		}
		Text_value = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      reclaim_evaluation_quantity(value);
      reclaim_evaluation_value(format_string_or_unit);
      temp = Text_value;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* EVAL-FIXED-FORMAT-FUNCALLED */
Object eval_fixed_format_funcalled(number,integral_size,fraction_size)
    Object number, integral_size, fraction_size;
{
    Object number_value, integral_size_value, fraction_size_value, text_value;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);

    x_note_fn_call(207,75);
    number_value = evaluation_quantity_value(number);
    integral_size_value = integral_size;
    fraction_size_value = fraction_size;
    text_value = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Text_value,Qtext_value,text_value,5);
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
		write_floating_point_number(7,number_value,
			integral_size_value,fraction_size_value,
			FIX((SI_Long)16L),Nil,Nil,Nil);
		Text_value = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      reclaim_evaluation_quantity(number);
      temp = Text_value;
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object string_constant_13;  /* "~NV is not a ddd.dddd format." */

static Object array_constant_37;   /* # */

static Object Qoverflow;           /* overflow */

static Object Qunderflow;          /* underflow */

static Object string_constant_14;  /* "~NV causes ~NV when formatted as a number." */

static Object string_constant_15;  /* "~NV could not be formatted as a number." */

static Object string_constant_16;  /* "~NV is not the text of a number, ~
				    *                                            an expired number, nor ****"
				    */

static Object array_constant_38;   /* # */

/* EVAL-FORMAT-NUMERIC-TEXT-FUNCALLED */
Object eval_format_numeric_text_funcalled(number_as_text,format_text_1)
    Object number_as_text, format_text_1;
{
    Object format_left_qm, format_right, top_of_stack, message_1, text_value;
    Object expired_p, string1, end1, end2, ab_loop_iter_flag_, temp_1;
    Object number_value_qm, temp_2, end_1, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(6);
    Object result;

    x_note_fn_call(207,76);
    result = decode_format(intern_text_string_no_reclaim(1,format_text_1));
    MVS_2(result,format_left_qm,format_right);
    if ( !TRUEP(format_left_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_13,
		format_text_1);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    text_value = Nil;
    expired_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Text_value,Qtext_value,text_value,5);
      string1 = number_as_text;
      end1 = text_string_length(number_as_text);
      end2 = text_string_length(array_constant_37);
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
	  if ( !(UBYTE_16_ISAREF_1(string1,index1) == 
		  UBYTE_16_ISAREF_1(array_constant_37,index2))) {
	      temp = TRUEP(Nil);
	      goto end_2;
	  }
	  ab_loop_iter_flag_ = Nil;
	  index1 = index1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  temp = TRUEP(T);
	  goto end_2;
	  temp = TRUEP(Qnil);
	end_2:;
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  Text_value = 
		  copy_constant_wide_string_given_length(array_constant_37,
		  FIX((SI_Long)4L));
      else {
	  result = read_number_from_text_string(1,number_as_text);
	  MVS_4(result,number_value_qm,temp_2,temp_2,end_1);
	  if (EQ(number_value_qm,Qoverflow) || EQ(number_value_qm,
		      Qunderflow)) {
	      top_of_stack = Cached_top_of_stack;
	      message_1 = tformat_stack_error_text_string(3,
		      string_constant_14,number_as_text,number_value_qm);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	  else if ( !TRUEP(number_value_qm)) {
	      top_of_stack = Cached_top_of_stack;
	      message_1 = tformat_stack_error_text_string(2,
		      string_constant_15,number_as_text);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	  else {
	      temp_2 = FIXNUM_ADD1(end_1);
	      if (FIXNUM_EQ(temp_2,text_string_length(number_as_text))) {
		  if (UBYTE_16_ISAREF_1(number_as_text,IFIX(end_1)) == 
			  (SI_Long)42L)
		      expired_p = T;
		  else {
		      top_of_stack = Cached_top_of_stack;
		      message_1 = tformat_stack_error_text_string(2,
			      string_constant_16,number_as_text);
		      raw_stack_error_named_error(top_of_stack,message_1);
		  }
	      }
	  }
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L 
		    + (SI_Long)3L));
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
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    write_floating_point_number(7,number_value_qm,
			    format_left_qm,format_right,FIX((SI_Long)16L),
			    Nil,Nil,Nil);
		    if (expired_p)
			twrite(array_constant_38);
		    Text_value = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      reclaim_text_string(number_as_text);
      reclaim_text_string(format_text_1);
      temp_2 = Text_value;
    POP_SPECIAL();
    return VALUES_1(temp_2);
}

static Object Qiteration_state;    /* iteration-state */

static Object string_constant_17;  /* "The ~a operator received the invalid argument ~NV." */

static Object string_constant_18;  /* "The ~a operator received the invalid argument ~A." */

/* INVALID-ARGUMENT-TYPE-EVAL-ERROR-MESSAGE */
Object invalid_argument_type_eval_error_message(stack_arg,evaluator_name)
    Object stack_arg, evaluator_name;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(207,77);
    gensymed_symbol = stack_arg;
    temp = FIXNUMP(gensymed_symbol);
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L;
    if (temp);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp = EQ(gensymed_symbol,Qtruth_value);
	if (temp);
	else
	    temp = EQ(gensymed_symbol,Qiteration_state);
	if (temp);
	else if (SYMBOLP(gensymed_symbol)) {
	    skip_list = CDR(Defined_evaluation_value_types);
	    key_value = gensymed_symbol;
	    key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop:
	    if (level < ab_loop_bind_)
		goto end_loop;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_1:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_2:
	    if ( !TRUEP(marked))
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_2;
	  end_loop_1:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_1;
	    goto next_loop_1;
	  end_loop_2:
	  end_1:
	    level = level - (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    return tformat_stack_error_text_string(3,temp ? string_constant_17 : 
	    string_constant_18,evaluator_name,stack_arg);
}

static Object string_constant_19;  /* "In a ~a expression, the values ~NE and ~NE are not of the same type." */

/* ARGUMENT-MISMATCH-EVAL-ERROR-MESSAGE */
Object argument_mismatch_eval_error_message(stack_arg_1,stack_arg_2,
	    evaluator_name)
    Object stack_arg_1, stack_arg_2, evaluator_name;
{
    x_note_fn_call(207,78);
    return tformat_stack_error_text_string(4,string_constant_19,
	    evaluator_name,stack_arg_1,stack_arg_2);
}

/* STACK-EVAL>FUNCTION */
Object stack_eval_gt_function(stack_arg_1,stack_arg_2,top_of_stack)
    Object stack_arg_1, stack_arg_2, top_of_stack;
{
    Object temp, temp_1;

    x_note_fn_call(207,79);
    if (FIXNUMP(stack_arg_1) || INLINE_DOUBLE_FLOAT_VECTOR_P(stack_arg_1) 
	    != (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_1)) 
	    == (SI_Long)1L || INLINE_LONG_VECTOR_P(stack_arg_1) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_1)) == 
	    (SI_Long)1L) {
	if (FIXNUMP(stack_arg_2) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(stack_arg_2) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_2)) == 
		(SI_Long)1L || INLINE_LONG_VECTOR_P(stack_arg_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_2)) == (SI_Long)1L) {
	    if (evaluation_quantity_gt(stack_arg_1,stack_arg_2))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_gt));
    }
    else if (text_string_p(stack_arg_1)) {
	if (text_string_p(stack_arg_2)) {
	    if (string_greaterpw(stack_arg_1,stack_arg_2))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_gt));
    }
    else if (CONSP(stack_arg_1) && EQ(M_CDR(stack_arg_1),Qtruth_value)) {
	if (CONSP(stack_arg_2) && EQ(M_CDR(stack_arg_2),Qtruth_value)) {
	    temp = M_CAR(stack_arg_1);
	    temp_1 = M_CAR(stack_arg_2);
	    if (NUM_GT(temp,temp_1))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_gt));
    }
    else
	return raw_stack_error_named_error(top_of_stack,
		invalid_argument_type_eval_error_message(stack_arg_1,Qnum_gt));
}

/* STACK-EVAL>=FUNCTION */
Object stack_eval_gt_eq_function(stack_arg_1,stack_arg_2,top_of_stack)
    Object stack_arg_1, stack_arg_2, top_of_stack;
{
    Object temp, temp_1;

    x_note_fn_call(207,80);
    if (FIXNUMP(stack_arg_1) || INLINE_DOUBLE_FLOAT_VECTOR_P(stack_arg_1) 
	    != (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_1)) 
	    == (SI_Long)1L || INLINE_LONG_VECTOR_P(stack_arg_1) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_1)) == 
	    (SI_Long)1L) {
	if (FIXNUMP(stack_arg_2) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(stack_arg_2) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_2)) == 
		(SI_Long)1L || INLINE_LONG_VECTOR_P(stack_arg_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_2)) == (SI_Long)1L) {
	    if (evaluation_quantity_gt_eq(stack_arg_1,stack_arg_2))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_ge));
    }
    else if (text_string_p(stack_arg_1)) {
	if (text_string_p(stack_arg_2)) {
	    if (string_not_lesspw(stack_arg_1,stack_arg_2))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_ge));
    }
    else if (CONSP(stack_arg_1) && EQ(M_CDR(stack_arg_1),Qtruth_value)) {
	if (CONSP(stack_arg_2) && EQ(M_CDR(stack_arg_2),Qtruth_value)) {
	    temp = M_CAR(stack_arg_1);
	    temp_1 = M_CAR(stack_arg_2);
	    if (NUM_GE(temp,temp_1))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_ge));
    }
    else
	return raw_stack_error_named_error(top_of_stack,
		invalid_argument_type_eval_error_message(stack_arg_1,Qnum_ge));
}

/* STACK-EVAL<FUNCTION */
Object stack_eval_lt_function(stack_arg_1,stack_arg_2,top_of_stack)
    Object stack_arg_1, stack_arg_2, top_of_stack;
{
    Object temp, temp_1;

    x_note_fn_call(207,81);
    if (FIXNUMP(stack_arg_1) || INLINE_DOUBLE_FLOAT_VECTOR_P(stack_arg_1) 
	    != (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_1)) 
	    == (SI_Long)1L || INLINE_LONG_VECTOR_P(stack_arg_1) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_1)) == 
	    (SI_Long)1L) {
	if (FIXNUMP(stack_arg_2) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(stack_arg_2) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_2)) == 
		(SI_Long)1L || INLINE_LONG_VECTOR_P(stack_arg_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_2)) == (SI_Long)1L) {
	    if (evaluation_quantity_lt(stack_arg_1,stack_arg_2))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_lt));
    }
    else if (text_string_p(stack_arg_1)) {
	if (text_string_p(stack_arg_2)) {
	    if (string_lesspw(stack_arg_1,stack_arg_2))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_lt));
    }
    else if (CONSP(stack_arg_1) && EQ(M_CDR(stack_arg_1),Qtruth_value)) {
	if (CONSP(stack_arg_2) && EQ(M_CDR(stack_arg_2),Qtruth_value)) {
	    temp = M_CAR(stack_arg_1);
	    temp_1 = M_CAR(stack_arg_2);
	    if (NUM_LT(temp,temp_1))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_lt));
    }
    else
	return raw_stack_error_named_error(top_of_stack,
		invalid_argument_type_eval_error_message(stack_arg_1,Qnum_lt));
}

/* STACK-EVAL<=FUNCTION */
Object stack_eval_lt_eq_function(stack_arg_1,stack_arg_2,top_of_stack)
    Object stack_arg_1, stack_arg_2, top_of_stack;
{
    Object temp, temp_1;

    x_note_fn_call(207,82);
    if (FIXNUMP(stack_arg_1) || INLINE_DOUBLE_FLOAT_VECTOR_P(stack_arg_1) 
	    != (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_1)) 
	    == (SI_Long)1L || INLINE_LONG_VECTOR_P(stack_arg_1) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_1)) == 
	    (SI_Long)1L) {
	if (FIXNUMP(stack_arg_2) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(stack_arg_2) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_2)) == 
		(SI_Long)1L || INLINE_LONG_VECTOR_P(stack_arg_2) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_arg_2)) == (SI_Long)1L) {
	    if (evaluation_quantity_lt_eq(stack_arg_1,stack_arg_2))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_le));
    }
    else if (text_string_p(stack_arg_1)) {
	if (text_string_p(stack_arg_2)) {
	    if (string_not_greaterpw(stack_arg_1,stack_arg_2))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_le));
    }
    else if (CONSP(stack_arg_1) && EQ(M_CDR(stack_arg_1),Qtruth_value)) {
	if (CONSP(stack_arg_2) && EQ(M_CDR(stack_arg_2),Qtruth_value)) {
	    temp = M_CAR(stack_arg_1);
	    temp_1 = M_CAR(stack_arg_2);
	    if (NUM_LE(temp,temp_1))
		return VALUES_1(Evaluation_true_value);
	    else
		return VALUES_1(Evaluation_false_value);
	}
	else
	    return raw_stack_error_named_error(top_of_stack,
		    argument_mismatch_eval_error_message(stack_arg_1,
		    stack_arg_2,Qnum_le));
    }
    else
	return raw_stack_error_named_error(top_of_stack,
		invalid_argument_type_eval_error_message(stack_arg_1,Qnum_le));
}

/* IS-STACK-NODE-CONVERTER */
Object is_stack_node_converter(expression)
    Object expression;
{
    Object symbol_expression, symbol_value_1, gensymed_symbol, is_node;
    Object svref_new_value;

    x_note_fn_call(207,83);
    symbol_expression = 
	    convert_expression_to_stack_node_tree(SECOND(expression));
    symbol_value_1 = convert_expression_to_stack_node_tree(THIRD(expression));
    gensymed_symbol = make_stack_node_instruction_1_1(Qis,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    is_node = gensymed_symbol;
    svref_new_value = stack_list_2(symbol_expression,symbol_value_1);
    SVREF(is_node,FIX((SI_Long)2L)) = svref_new_value;
    GENSYM_RETURN_ONE(is_node);
    return VALUES_1(Nil);
}

static Object Qboolean;            /* boolean */

/* IS-I-CHOOSER */
Object is_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, argument_nodes, value_type;
    Object temp, temp_1;

    x_note_fn_call(207,84);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    value_type = Qboolean;
    temp = choose_stack_node_instructions_and_types(2,
	    FIRST(argument_nodes),Qitem_or_datum);
    M_FIRST(argument_nodes) = temp;
    temp = choose_stack_node_instructions_and_types(2,
	    SECOND(argument_nodes),Qsymbol);
    M_SECOND(argument_nodes) = temp;
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_unknown(value_type,temp_1);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qis_and_possibly_unknown;  /* is-and-possibly-unknown */

/* IS-I-EMIT */
Object is_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_is_allowed_qm;

    x_note_fn_call(207,85);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_is_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
    emit_stack_node_tree(byte_code_stream,SECOND(argument_nodes));
    if (unknown_is_allowed_qm)
	emit_funcall_instruction_byte_codes(2,byte_code_stream,
		Qis_and_possibly_unknown);
    else
	emit_funcall_instruction_byte_codes(2,byte_code_stream,Qis);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_20;  /* "The first value, ~NV, in the IS expression is not a symbol." */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object string_constant_21;  /* "The first argument to IS, the ~a of ~NF, denoted ~
				    *                           more than one value.  IS requires one value only."
				    */

static Object string_constant_22;  /* "The first argument to IS, the ~a of ~NF, held no value." */

static Object string_constant_23;  /* "The first argument to IS, ~NA, which was the ~a ~
				    *                        of ~NF, was not a symbol."
				    */

static Object string_constant_24;  /* "The first argument to IS, ~NF, is not a symbol." */

static Object string_constant_25;  /* "The first argument to IS, ~NF, is not a parameter." */

static Object string_constant_26;  /* "The first argument to IS, ~NF, is an item which is neither a ~
				    *           parameter or an attribute with a possible symbolic value of ~a."
				    */

/* FUNCALL-IS-INST */
Object funcall_is_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object item_or_datum_arg, gensymed_symbol, datum_arg_qm;
    Object symbolic_value_arg, symbolic_value, attribute_class_qm;
    Object implied_attribute_name_qm, implied_attribute_role_qm, result_qm;
    Object top_of_stack_1, message_1, target_class, attribute_qm, class_qm;
    Object error_qm, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object attribute_value, role_expiration_qm, extra_objects_qm, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, sub_class_bit_vector, managed_current_value;
    Object current_value, svref_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, key_hash_value;
    SI_Long bottom_level, level, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;
    Declare_special(7);
    Object result;

    x_note_fn_call(207,86);
    item_or_datum_arg = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
    gensymed_symbol = item_or_datum_arg;
    temp = FIXNUMP(gensymed_symbol);
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L;
    if (temp);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp = EQ(gensymed_symbol,Qtruth_value);
	if (temp);
	else
	    temp = TRUEP(memq_function(gensymed_symbol,
		    Defined_evaluation_datum_types));
    }
    else
	temp = TRUEP(Nil);
    datum_arg_qm = temp ? item_or_datum_arg : Nil;
    symbolic_value_arg = ISVREF(local_stack,IFIX(top_of_stack));
    symbolic_value = symbolic_value_arg;
    attribute_class_qm = Nil;
    implied_attribute_name_qm = Nil;
    implied_attribute_role_qm = Nil;
    result_qm = Nil;
    if (datum_arg_qm) {
	if (datum_arg_qm && SYMBOLP(datum_arg_qm)) {
	    if (EQ(datum_arg_qm,symbolic_value))
		result_qm = T;
	    else
		result_qm = Nil;
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_20,datum_arg_qm);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else {
	if ( !TRUEP(datum_arg_qm)) {
	    target_class = ISVREF(ISVREF(item_or_datum_arg,(SI_Long)1L),
		    (SI_Long)1L);
	    result = implied_attribute_of_class_qm(target_class,
		    symbolic_value);
	    MVS_3(result,attribute_qm,class_qm,error_qm);
	    if (error_qm) {
		top_of_stack_1 = top_of_stack;
		text_string = Nil;
		snapshots = Nil;
		snapshots_of_related_blocks = Nil;
		note_blocks_in_tformat = 
			SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			6);
		  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			  5);
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
			      twrite_general_string(error_qm);
			      reclaim_text_string(error_qm);
			      text_string = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    snapshots = Snapshots_of_related_blocks;
		    Snapshots_of_related_blocks = Nil;
		    if (Snapshots_of_related_blocks) {
			reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			Snapshots_of_related_blocks = Nil;
		    }
		  POP_SPECIAL();
		POP_SPECIAL();
		message_1 = make_error_text(text_string,snapshots);
		result = raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else
		result = VALUES_2(attribute_qm,class_qm);
	    MVS_2(result,implied_attribute_name_qm,attribute_class_qm);
	}
	if (implied_attribute_name_qm) {
	    if (attribute_class_qm)
		implied_attribute_role_qm = 
			eval_list_3(Qclass_qualified_name,
			attribute_class_qm,implied_attribute_name_qm);
	    else
		implied_attribute_role_qm = implied_attribute_name_qm;
	    result = serve_unique_item_or_evaluation_value_of_role(implied_attribute_role_qm,
		    item_or_datum_arg,Nil,T);
	    MVS_3(result,attribute_value,role_expiration_qm,extra_objects_qm);
	    if ( !TRUEP(role_expiration_qm)) {
		if (extra_objects_qm) {
		    top_of_stack_1 = top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_21,implied_attribute_name_qm,
			    item_or_datum_arg);
		    raw_stack_error_named_error(top_of_stack_1,message_1);
		}
		else {
		    top_of_stack_1 = top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_22,implied_attribute_name_qm,
			    item_or_datum_arg);
		    raw_stack_error_named_error(top_of_stack_1,message_1);
		}
	    }
	    else if (attribute_value && SYMBOLP(attribute_value)) {
		if (EQ(attribute_value,symbolic_value))
		    result_qm = T;
		else
		    result_qm = Nil;
	    }
	    else {
		gensymed_symbol = attribute_value;
		temp = FIXNUMP(gensymed_symbol);
		if (temp);
		else
		    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp);
		else
		    temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp);
		else
		    temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			    TRUEP(Qnil);
		if (temp);
		else
		    temp = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L;
		if (temp);
		else if (CONSP(gensymed_symbol)) {
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    temp = EQ(gensymed_symbol,Qtruth_value);
		    if (temp);
		    else
			temp = EQ(gensymed_symbol,Qiteration_state);
		    if (temp);
		    else if (SYMBOLP(gensymed_symbol)) {
			skip_list = CDR(Defined_evaluation_value_types);
			key_value = gensymed_symbol;
			key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop:
			if (level < ab_loop_bind_)
			    goto end_loop;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_1:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_2:
			if ( !TRUEP(marked))
			    goto end_loop_1;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_2;
		      end_loop_1:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_1;
			goto next_loop_1;
		      end_loop_2:
		      end_1:
			level = level - (SI_Long)1L;
			goto next_loop;
		      end_loop:;
			temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    top_of_stack_1 = top_of_stack;
		    text_string = Nil;
		    snapshots = Nil;
		    snapshots_of_related_blocks = Nil;
		    note_blocks_in_tformat = 
			    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			    6);
		      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			      5);
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
				  tformat(4,string_constant_23,
					  attribute_value,
					  implied_attribute_name_qm,
					  item_or_datum_arg);
				  reclaim_evaluation_value(attribute_value);
				  text_string = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			snapshots = Snapshots_of_related_blocks;
			Snapshots_of_related_blocks = Nil;
			if (Snapshots_of_related_blocks) {
			    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			    Snapshots_of_related_blocks = Nil;
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		    message_1 = make_error_text(text_string,snapshots);
		    raw_stack_error_named_error(top_of_stack_1,message_1);
		}
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(attribute_value,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Parameter_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			if (EQ(type_specification_of_variable_or_parameter_value(attribute_value),
				Qsymbol)) {
			    managed_current_value = ISVREF(attribute_value,
				    (SI_Long)23L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_current_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_current_value)) 
				    == (SI_Long)1L)
				current_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_current_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_current_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_current_value)) 
				    == (SI_Long)1L)
				current_value = 
					aref1(managed_current_value,
					FIX((SI_Long)0L));
			    else
				current_value = managed_current_value;
			    if (EQ(current_value,symbolic_value))
				result_qm = T;
			    else
				result_qm = Nil;
			}
			else {
			    top_of_stack_1 = top_of_stack;
			    message_1 = tformat_stack_error_text_string(2,
				    string_constant_24,item_or_datum_arg);
			    raw_stack_error_named_error(top_of_stack_1,
				    message_1);
			}
		    }
		    else {
			top_of_stack_1 = top_of_stack;
			message_1 = tformat_stack_error_text_string(2,
				string_constant_25,attribute_value);
			raw_stack_error_named_error(top_of_stack_1,message_1);
		    }
		}
	    }
	    if (CONSP(implied_attribute_role_qm)) {
		reclaim_eval_list_1(implied_attribute_role_qm);
		implied_attribute_role_qm = Nil;
	    }
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(item_or_datum_arg,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if (EQ(type_specification_of_variable_or_parameter_value(item_or_datum_arg),
			Qsymbol)) {
		    managed_current_value = ISVREF(item_or_datum_arg,
			    (SI_Long)23L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_current_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_current_value)) 
			    == (SI_Long)1L)
			current_value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_current_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_current_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_current_value)) 
			    == (SI_Long)1L)
			current_value = aref1(managed_current_value,
				FIX((SI_Long)0L));
		    else
			current_value = managed_current_value;
		    if (EQ(current_value,symbolic_value))
			result_qm = T;
		    else
			result_qm = Nil;
		}
		else {
		    top_of_stack_1 = top_of_stack;
		    message_1 = tformat_stack_error_text_string(2,
			    string_constant_24,item_or_datum_arg);
		    raw_stack_error_named_error(top_of_stack_1,message_1);
		}
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_26,item_or_datum_arg,symbolic_value);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
    }
    if ( !(FIXNUMP(item_or_datum_arg) || SYMBOLP(item_or_datum_arg) || 
	    SIMPLE_VECTOR_P(item_or_datum_arg)))
	reclaim_if_evaluation_value_1(item_or_datum_arg);
    reclaim_evaluation_value(symbolic_value_arg);
    top_of_stack = FIXNUM_SUB1(top_of_stack);
    svref_new_value = result_qm ? Evaluation_true_value : 
	    Evaluation_false_value;
    SVREF(local_stack,top_of_stack) = svref_new_value;
    return VALUES_1(Nil);
}

static Object string_constant_27;  /* "The first value passed to IS, ~NV, was not a symbol." */

static Object string_constant_28;  /* "The first argument to IS, the ~a of ~NF, denoted ~
				    *                            more than one value.  IS requires one value only."
				    */

static Object string_constant_29;  /* "The first argument to IS, ~NA, which was the ~a ~
				    *                         of ~NF, was not a symbol."
				    */

static Object string_constant_30;  /* "The first argument to IS, ~NV, which was the value ~
				    *                     of ~NF, was not a symbol."
				    */

static Object string_constant_31;  /* "The first argument to IS, ~NF, was not a variable or a parameter." */

static Object string_constant_32;  /* "The first argument to IS, ~NV, which was the value ~
				    *                of ~NF, was not a symbol."
				    */

static Object string_constant_33;  /* "The first argument to IS, ~NF, was an item which was not a variable ~
				    *           or parameter nor did it have an attribute with a possible symbolic ~
				    *           value of ~a."
				    */

/* FUNCALL-IS-AND-POSSIBLY-UNKNOWN-INST */
Object funcall_is_and_possibly_unknown_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object item_or_datum_arg, gensymed_symbol, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, temp_2, entry_hash;
    Object datum_arg_qm, symbolic_value_arg, symbolic_value;
    Object attribute_class_qm, implied_attribute_name_qm;
    Object implied_attribute_role_qm, result_qm, top_of_stack_1, message_1;
    Object target_class, attribute_qm, class_qm, error_qm, text_string;
    Object snapshots, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object attribute_value, role_expiration_qm, extra_objects_qm;
    Object sub_class_bit_vector, value_qm, svref_new_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;
    Declare_special(7);
    Object result;

    x_note_fn_call(207,87);
    item_or_datum_arg = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
    gensymed_symbol = item_or_datum_arg;
    temp = FIXNUMP(gensymed_symbol);
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L;
    if (temp);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp = EQ(gensymed_symbol,Qtruth_value);
	if (temp);
	else
	    temp = EQ(gensymed_symbol,Qiteration_state);
	if (temp);
	else if (SYMBOLP(gensymed_symbol)) {
	    skip_list = CDR(Defined_evaluation_value_types);
	    key_value = gensymed_symbol;
	    key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop:
	    if (level < ab_loop_bind_)
		goto end_loop;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_1:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_2:
	    if ( !TRUEP(marked))
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_2;
	  end_loop_1:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_1;
	    goto next_loop_1;
	  end_loop_2:
	  end_1:
	    level = level - (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    datum_arg_qm = temp ? item_or_datum_arg : Nil;
    symbolic_value_arg = ISVREF(local_stack,IFIX(top_of_stack));
    symbolic_value = evaluation_value_value(symbolic_value_arg);
    attribute_class_qm = Nil;
    implied_attribute_name_qm = Nil;
    implied_attribute_role_qm = Nil;
    result_qm = Nil;
    if (datum_arg_qm &&  !TRUEP(evaluation_value_value(datum_arg_qm))) {
	result_qm = Nil;
	Stack_expiration = Nil;
    }
    else if (datum_arg_qm) {
	if (datum_arg_qm && SYMBOLP(datum_arg_qm)) {
	    if (EQ(datum_arg_qm,symbolic_value))
		result_qm = T;
	    else
		result_qm = Nil;
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_27,datum_arg_qm);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else {
	if ( !TRUEP(datum_arg_qm)) {
	    target_class = ISVREF(ISVREF(item_or_datum_arg,(SI_Long)1L),
		    (SI_Long)1L);
	    result = implied_attribute_of_class_qm(target_class,
		    symbolic_value);
	    MVS_3(result,attribute_qm,class_qm,error_qm);
	    if (error_qm) {
		top_of_stack_1 = top_of_stack;
		text_string = Nil;
		snapshots = Nil;
		snapshots_of_related_blocks = Nil;
		note_blocks_in_tformat = 
			SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			6);
		  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			  5);
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
			      twrite_general_string(error_qm);
			      reclaim_text_string(error_qm);
			      text_string = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    snapshots = Snapshots_of_related_blocks;
		    Snapshots_of_related_blocks = Nil;
		    if (Snapshots_of_related_blocks) {
			reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			Snapshots_of_related_blocks = Nil;
		    }
		  POP_SPECIAL();
		POP_SPECIAL();
		message_1 = make_error_text(text_string,snapshots);
		result = raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else
		result = VALUES_2(attribute_qm,class_qm);
	    MVS_2(result,implied_attribute_name_qm,attribute_class_qm);
	}
	if (implied_attribute_name_qm) {
	    if (attribute_class_qm)
		implied_attribute_role_qm = 
			eval_list_3(Qclass_qualified_name,
			attribute_class_qm,implied_attribute_name_qm);
	    else
		implied_attribute_role_qm = implied_attribute_name_qm;
	    result = serve_unique_item_or_evaluation_value_of_role(implied_attribute_role_qm,
		    item_or_datum_arg,Nil,T);
	    MVS_3(result,attribute_value,role_expiration_qm,extra_objects_qm);
	    if ( !TRUEP(role_expiration_qm)) {
		if (extra_objects_qm) {
		    top_of_stack_1 = top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_28,implied_attribute_name_qm,
			    item_or_datum_arg);
		    raw_stack_error_named_error(top_of_stack_1,message_1);
		}
		else {
		    top_of_stack_1 = top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_22,implied_attribute_name_qm,
			    item_or_datum_arg);
		    raw_stack_error_named_error(top_of_stack_1,message_1);
		}
	    }
	    else if (attribute_value && SYMBOLP(attribute_value)) {
		if (EQ(attribute_value,symbolic_value))
		    result_qm = T;
		else
		    result_qm = Nil;
	    }
	    else {
		gensymed_symbol = attribute_value;
		temp = FIXNUMP(gensymed_symbol);
		if (temp);
		else
		    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp);
		else
		    temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp);
		else
		    temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			    TRUEP(Qnil);
		if (temp);
		else
		    temp = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L;
		if (temp);
		else if (CONSP(gensymed_symbol)) {
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    temp = EQ(gensymed_symbol,Qtruth_value);
		    if (temp);
		    else
			temp = EQ(gensymed_symbol,Qiteration_state);
		    if (temp);
		    else if (SYMBOLP(gensymed_symbol)) {
			skip_list = CDR(Defined_evaluation_value_types);
			key_value = gensymed_symbol;
			key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_3:
			if (level < ab_loop_bind_)
			    goto end_loop_3;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_4:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_5:
			if ( !TRUEP(marked))
			    goto end_loop_4;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_5;
		      end_loop_4:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_2;
			goto next_loop_4;
		      end_loop_5:
		      end_2:
			level = level - (SI_Long)1L;
			goto next_loop_3;
		      end_loop_3:;
			temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    top_of_stack_1 = top_of_stack;
		    text_string = Nil;
		    snapshots = Nil;
		    snapshots_of_related_blocks = Nil;
		    note_blocks_in_tformat = 
			    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			    6);
		      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			      5);
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
				  tformat(4,string_constant_29,
					  attribute_value,
					  implied_attribute_name_qm,
					  item_or_datum_arg);
				  reclaim_evaluation_value(attribute_value);
				  text_string = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			snapshots = Snapshots_of_related_blocks;
			Snapshots_of_related_blocks = Nil;
			if (Snapshots_of_related_blocks) {
			    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			    Snapshots_of_related_blocks = Nil;
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		    message_1 = make_error_text(text_string,snapshots);
		    raw_stack_error_named_error(top_of_stack_1,message_1);
		}
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(attribute_value,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Variable_or_parameter_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			value_qm = 
				get_current_evaluation_value(attribute_value,
				Nil);
			if ( !TRUEP(value_qm))
			    result_qm = Nil;
			else if ( !(value_qm && SYMBOLP(value_qm))) {
			    top_of_stack_1 = top_of_stack;
			    message_1 = tformat_stack_error_text_string(3,
				    string_constant_30,value_qm,
				    item_or_datum_arg);
			    raw_stack_error_named_error(top_of_stack_1,
				    message_1);
			}
			else if ( !EQ(value_qm,symbolic_value))
			    result_qm = Nil;
			else
			    result_qm = T;
			if ( !(FIXNUMP(value_qm) || SYMBOLP(value_qm) || 
				SIMPLE_VECTOR_P(value_qm)))
			    reclaim_if_evaluation_value_1(value_qm);
		    }
		    else {
			top_of_stack_1 = top_of_stack;
			message_1 = tformat_stack_error_text_string(2,
				string_constant_31,attribute_value);
			raw_stack_error_named_error(top_of_stack_1,message_1);
		    }
		}
	    }
	    if (CONSP(implied_attribute_role_qm)) {
		reclaim_eval_list_1(implied_attribute_role_qm);
		implied_attribute_role_qm = Nil;
	    }
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(item_or_datum_arg,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_or_parameter_class_description,
		    (SI_Long)18L));
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		value_qm = get_current_evaluation_value(item_or_datum_arg,Nil);
		if ( !TRUEP(value_qm))
		    result_qm = Nil;
		else if ( !(value_qm && SYMBOLP(value_qm))) {
		    top_of_stack_1 = top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_32,value_qm,item_or_datum_arg);
		    raw_stack_error_named_error(top_of_stack_1,message_1);
		}
		else if ( !EQ(value_qm,symbolic_value))
		    result_qm = Nil;
		else
		    result_qm = T;
		if ( !(FIXNUMP(value_qm) || SYMBOLP(value_qm) || 
			SIMPLE_VECTOR_P(value_qm)))
		    reclaim_if_evaluation_value_1(value_qm);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_33,item_or_datum_arg,symbolic_value);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
    }
    if ( !(FIXNUMP(item_or_datum_arg) || SYMBOLP(item_or_datum_arg) || 
	    SIMPLE_VECTOR_P(item_or_datum_arg)))
	reclaim_if_evaluation_value_1(item_or_datum_arg);
    reclaim_evaluation_value(symbolic_value_arg);
    top_of_stack = FIXNUM_SUB1(top_of_stack);
    svref_new_value = result_qm ? Evaluation_true_value : 
	    Evaluation_false_value;
    SVREF(local_stack,top_of_stack) = svref_new_value;
    return VALUES_1(Nil);
}

/* IS-NOT-STACK-NODE-CONVERTER */
Object is_not_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(207,88);
    GENSYM_RETURN_ONE(convert_expression_to_stack_node_tree(phrase_list_2(Qnot,
	    phrase_cons(Qis,CDR(expression)))));
    return VALUES_1(Nil);
}

/* AND-STACK-NODE-CONVERTER */
Object and_stack_node_converter(expression)
    Object expression;
{
    Object argument, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object arguments, gensymed_symbol, and_node;

    x_note_fn_call(207,89);
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    arguments = ab_loopvar_;
    goto end_1;
    arguments = Qnil;
  end_1:;
    gensymed_symbol = make_stack_node_instruction_1_1(Qand,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    and_node = gensymed_symbol;
    SVREF(and_node,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(and_node);
    return VALUES_1(Nil);
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

/* AND-I-CHOOSER */
Object and_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, argument_nodes;
    Object unknown_argument_qm, all_boolean_arguments_qm, type_spec;
    Object argument_node_cons, temp, temp_1;

    x_note_fn_call(207,90);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_argument_qm = Nil;
    all_boolean_arguments_qm = T;
    type_spec = Qtruth_value;
    type_spec = 
	    maybe_add_no_item_implies_unknown(maybe_add_unknown(type_spec,
	    unknown_allowed_qm),no_item_implies_unknown_allowed_qm);
    argument_node_cons = argument_nodes;
  next_loop:
    if ( !TRUEP(argument_node_cons))
	goto end_loop;
    temp = choose_stack_node_instructions_and_types(2,
	    CAR(argument_node_cons),type_spec);
    M_CAR(argument_node_cons) = temp;
    if (type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_node_cons),(SI_Long)6L)))
	unknown_argument_qm = T;
    if ( !(type_specification_subtype_p(Qboolean,
	    ISVREF(CAR(argument_node_cons),(SI_Long)6L)) &&  
	    !TRUEP(type_specification_subtype_p(Qtruth_value,
	    ISVREF(CAR(argument_node_cons),(SI_Long)6L)))))
	all_boolean_arguments_qm = Nil;
    argument_node_cons = M_CDR(argument_node_cons);
    goto next_loop;
  end_loop:;
    if (unknown_argument_qm) {
	temp = all_boolean_arguments_qm ? list_constant_5 : list_constant_6;
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
	if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	    temp_1 = generate_new_stack_frame_var_spot(Qdatum);
	    temp = phrase_list_2(temp_1,
		    generate_new_stack_frame_var_spot(Qdatum));
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    else {
	temp = all_boolean_arguments_qm ? Qboolean : Qtruth_value;
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
	SVREF(stack_node_instruction,FIX((SI_Long)12L)) = Nil;
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* AND-I-EMIT */
Object and_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, expiration_var_qm, cached_global_expiration_var_qm;
    Object end_of_and_tag, node, ab_loop_list_, false_tag, first_known_tag;
    Object argument_node, argument_known_tag;

    x_note_fn_call(207,91);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    expiration_var_qm = FIRST(extra_info);
    cached_global_expiration_var_qm = SECOND(extra_info);
    end_of_and_tag = generate_new_goto_tag();
    if ( !TRUEP(expiration_var_qm)) {
	emit_stack_node_tree(byte_code_stream,CAR(argument_nodes));
	node = Nil;
	ab_loop_list_ = CDR(argument_nodes);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	emit_branch_long_if_false_byte_codes(byte_code_stream,end_of_and_tag);
	emit_stack_node_tree(byte_code_stream,node);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)79L));
	goto next_loop;
      end_loop:;
	register_tag_in_byte_code_stream(2,byte_code_stream,end_of_and_tag);
    }
    else {
	false_tag = generate_new_goto_tag();
	first_known_tag = generate_new_goto_tag();
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	emit_stack_node_tree(byte_code_stream,CAR(argument_nodes));
	emit_branch_long_if_known_byte_codes(byte_code_stream,first_known_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	register_tag_in_byte_code_stream(2,byte_code_stream,first_known_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	emit_branch_long_if_false_byte_codes(byte_code_stream,false_tag);
	argument_node = Nil;
	ab_loop_list_ = CDR(argument_nodes);
	argument_known_tag = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	argument_node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	argument_known_tag = generate_new_goto_tag();
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	emit_stack_node_tree(byte_code_stream,argument_node);
	emit_branch_long_if_known_byte_codes(byte_code_stream,
		argument_known_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		argument_known_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)79L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	emit_branch_long_if_false_byte_codes(byte_code_stream,false_tag);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	goto next_loop_1;
      end_loop_1:;
	register_tag_in_byte_code_stream(2,byte_code_stream,false_tag);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qab_or;              /* or */

/* OR-STACK-NODE-CONVERTER */
Object or_stack_node_converter(expression)
    Object expression;
{
    Object argument, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object arguments, gensymed_symbol, or_node;

    x_note_fn_call(207,92);
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    arguments = ab_loopvar_;
    goto end_1;
    arguments = Qnil;
  end_1:;
    gensymed_symbol = make_stack_node_instruction_1_1(Qab_or,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    or_node = gensymed_symbol;
    SVREF(or_node,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(or_node);
    return VALUES_1(Nil);
}

/* OR-I-CHOOSER */
Object or_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm, argument_nodes;
    Object no_item_implies_unknown_allowed_qm, unknown_argument_qm;
    Object all_boolean_arguments_qm, type_spec, argument_node_cons, temp;
    Object temp_1;

    x_note_fn_call(207,93);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    unknown_argument_qm = Nil;
    all_boolean_arguments_qm = T;
    type_spec = Qtruth_value;
    type_spec = 
	    maybe_add_no_item_implies_unknown(maybe_add_unknown(type_spec,
	    unknown_allowed_qm),no_item_implies_unknown_allowed_qm);
    argument_node_cons = argument_nodes;
  next_loop:
    if ( !TRUEP(argument_node_cons))
	goto end_loop;
    temp = choose_stack_node_instructions_and_types(2,
	    CAR(argument_node_cons),type_spec);
    M_CAR(argument_node_cons) = temp;
    if (type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_node_cons),(SI_Long)6L)))
	unknown_argument_qm = T;
    if ( !(type_specification_subtype_p(Qboolean,
	    ISVREF(CAR(argument_node_cons),(SI_Long)6L)) &&  
	    !TRUEP(type_specification_subtype_p(Qtruth_value,
	    ISVREF(CAR(argument_node_cons),(SI_Long)6L)))))
	all_boolean_arguments_qm = Nil;
    argument_node_cons = M_CDR(argument_node_cons);
    goto next_loop;
  end_loop:;
    if (unknown_argument_qm) {
	temp = all_boolean_arguments_qm ? list_constant_5 : list_constant_6;
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
	if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	    temp_1 = generate_new_stack_frame_var_spot(Qdatum);
	    temp = phrase_list_2(temp_1,
		    generate_new_stack_frame_var_spot(Qdatum));
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    else {
	temp = all_boolean_arguments_qm ? Qboolean : Qtruth_value;
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
	SVREF(stack_node_instruction,FIX((SI_Long)12L)) = Nil;
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* OR-I-EMIT */
Object or_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, expiration_var_qm, cached_global_expiration_var_qm;
    Object end_of_or_tag, node, ab_loop_list_, true_tag, first_known_tag;
    Object argument_node, argument_known_tag;

    x_note_fn_call(207,94);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    expiration_var_qm = FIRST(extra_info);
    cached_global_expiration_var_qm = SECOND(extra_info);
    end_of_or_tag = generate_new_goto_tag();
    if ( !TRUEP(expiration_var_qm)) {
	emit_stack_node_tree(byte_code_stream,CAR(argument_nodes));
	node = Nil;
	ab_loop_list_ = CDR(argument_nodes);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	emit_branch_long_if_true_byte_codes(byte_code_stream,end_of_or_tag);
	emit_stack_node_tree(byte_code_stream,node);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)80L));
	goto next_loop;
      end_loop:;
	register_tag_in_byte_code_stream(2,byte_code_stream,end_of_or_tag);
    }
    else {
	true_tag = generate_new_goto_tag();
	first_known_tag = generate_new_goto_tag();
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	emit_stack_node_tree(byte_code_stream,CAR(argument_nodes));
	emit_branch_long_if_known_byte_codes(byte_code_stream,first_known_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	register_tag_in_byte_code_stream(2,byte_code_stream,first_known_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	emit_branch_long_if_true_byte_codes(byte_code_stream,true_tag);
	argument_node = Nil;
	ab_loop_list_ = CDR(argument_nodes);
	argument_known_tag = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	argument_node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	argument_known_tag = generate_new_goto_tag();
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	emit_stack_node_tree(byte_code_stream,argument_node);
	emit_branch_long_if_known_byte_codes(byte_code_stream,
		argument_known_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		argument_known_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)80L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	emit_branch_long_if_true_byte_codes(byte_code_stream,true_tag);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	goto next_loop_1;
      end_loop_1:;
	register_tag_in_byte_code_stream(2,byte_code_stream,true_tag);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* NOT-STACK-NODE-CONVERTER */
Object not_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, new_node, svref_new_value;

    x_note_fn_call(207,95);
    gensymed_symbol = make_stack_node_instruction_1_1(Qnot,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    new_node = gensymed_symbol;
    svref_new_value = 
	    stack_cons_1(convert_expression_to_stack_node_tree(SECOND(expression)),
	    Nil);
    SVREF(new_node,FIX((SI_Long)2L)) = svref_new_value;
    GENSYM_RETURN_ONE(new_node);
    return VALUES_1(Nil);
}

/* NOT-I-CHOOSER */
Object not_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_nodes, no_item_implies_unknown_allowed_qm;
    Object unknown_allowed_qm, type_spec, temp;

    x_note_fn_call(207,96);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    type_spec = Qtruth_value;
    type_spec = 
	    maybe_add_no_item_implies_unknown(maybe_add_unknown(type_spec,
	    unknown_allowed_qm),no_item_implies_unknown_allowed_qm);
    temp = choose_stack_node_instructions_and_types(2,CAR(argument_nodes),
	    unknown_allowed_qm ? list_constant_6 : Qtruth_value);
    M_CAR(argument_nodes) = temp;
    temp = ISVREF(CAR(argument_nodes),(SI_Long)6L);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* NOT-I-EMIT */
Object not_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object temp;

    x_note_fn_call(207,97);
    temp = ISVREF(stack_node_instruction,(SI_Long)2L);
    emit_stack_node_tree(byte_code_stream,FIRST(temp));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)50L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_34;  /* "The fuzzy comparator band value ~a is less than zero." */

/* NEGATIVE-FUZZY-BAND-EVAL-ERROR-MESSAGE */
Object negative_fuzzy_band_eval_error_message(band_value)
    Object band_value;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(207,98);
    gensymed_symbol = band_value;
    temp = FIXNUMP(gensymed_symbol);
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L;
    if (temp);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp = EQ(gensymed_symbol,Qtruth_value);
	if (temp);
	else
	    temp = EQ(gensymed_symbol,Qiteration_state);
	if (temp);
	else if (SYMBOLP(gensymed_symbol)) {
	    skip_list = CDR(Defined_evaluation_value_types);
	    key_value = gensymed_symbol;
	    key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop:
	    if (level < ab_loop_bind_)
		goto end_loop;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_1:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_2:
	    if ( !TRUEP(marked))
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_2;
	  end_loop_1:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_1;
	    goto next_loop_1;
	  end_loop_2:
	  end_1:
	    level = level - (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    return tformat_stack_error_text_string(2,string_constant_34,temp ? 
	    evaluation_value_value(band_value) : band_value);
}

/* EVAL-FUZZY-<-FUNCALLED */
Object eval_fuzzy_lt_funcalled(value1,value2,band_value)
    Object value1, value2, band_value;
{
    Object quantity_value1, quantity_value2, band_value_value, result_value;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    double gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, arg, arg_1;
    double low_band_float, high_band_float;

    x_note_fn_call(207,99);
    quantity_value1 = evaluation_quantity_value(value1);
    quantity_value2 = evaluation_quantity_value(value2);
    band_value_value = evaluation_quantity_value(band_value);
    result_value = Nil;
    gensymed_symbol = quantity_value1;
    gensymed_symbol_1 = quantity_value2;
    gensymed_symbol_2 = band_value_value;
    if (FIXNUMP(gensymed_symbol))
	gensymed_symbol_3 = (double)IFIX(gensymed_symbol);
    else
	gensymed_symbol_3 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol);
    if (FIXNUMP(gensymed_symbol_1))
	gensymed_symbol_4 = (double)IFIX(gensymed_symbol_1);
    else
	gensymed_symbol_4 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    if (FIXNUMP(gensymed_symbol_2))
	gensymed_symbol_5 = (double)IFIX(gensymed_symbol_2);
    else
	gensymed_symbol_5 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_2);
    arg = gensymed_symbol_5;
    arg_1 = 0.0;
    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	low_band_float = gensymed_symbol_4 - gensymed_symbol_5;
	high_band_float = gensymed_symbol_4 + gensymed_symbol_5;
	arg = gensymed_symbol_3;
	arg_1 = low_band_float;
	if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    result_value = Truth;
	else {
	    arg = gensymed_symbol_3;
	    arg_1 = high_band_float;
	    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		result_value = 
			FIXNUM_MINUS(l_round(DOUBLE_TO_DOUBLE_FLOAT((high_band_float 
			- gensymed_symbol_3) * 1000.0 / gensymed_symbol_5),
			_),Truth);
	    else
		result_value = Falsity;
	}
    }
    else {
	arg = gensymed_symbol_5;
	arg_1 = 0.0;
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp = Cached_top_of_stack;
	    result_value = raw_stack_error_named_error(temp,
		    negative_fuzzy_band_eval_error_message(band_value));
	}
	else {
	    arg = gensymed_symbol_3;
	    arg_1 = gensymed_symbol_4;
	    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		result_value = Truth;
	    else
		result_value = Falsity;
	}
    }
    reclaim_evaluation_quantity(value1);
    reclaim_evaluation_quantity(value2);
    reclaim_evaluation_quantity(band_value);
    if (FIXNUM_EQ(result_value,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(result_value,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(result_value,Qtruth_value);
    return VALUES_1(temp);
}

/* EVAL-FUZZY->-FUNCALLED */
Object eval_fuzzy_gt_funcalled(value1,value2,band_value)
    Object value1, value2, band_value;
{
    Object quantity_value1, quantity_value2, band_value_value, result_value;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    double gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, arg, arg_1;
    double low_band_float, high_band_float;

    x_note_fn_call(207,100);
    quantity_value1 = evaluation_quantity_value(value1);
    quantity_value2 = evaluation_quantity_value(value2);
    band_value_value = evaluation_quantity_value(band_value);
    result_value = Nil;
    gensymed_symbol = quantity_value1;
    gensymed_symbol_1 = quantity_value2;
    gensymed_symbol_2 = band_value_value;
    if (FIXNUMP(gensymed_symbol))
	gensymed_symbol_3 = (double)IFIX(gensymed_symbol);
    else
	gensymed_symbol_3 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol);
    if (FIXNUMP(gensymed_symbol_1))
	gensymed_symbol_4 = (double)IFIX(gensymed_symbol_1);
    else
	gensymed_symbol_4 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    if (FIXNUMP(gensymed_symbol_2))
	gensymed_symbol_5 = (double)IFIX(gensymed_symbol_2);
    else
	gensymed_symbol_5 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_2);
    arg = gensymed_symbol_5;
    arg_1 = 0.0;
    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	low_band_float = gensymed_symbol_4 - gensymed_symbol_5;
	high_band_float = gensymed_symbol_4 + gensymed_symbol_5;
	arg = gensymed_symbol_3;
	arg_1 = low_band_float;
	if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    temp = Truth;
	else {
	    arg = gensymed_symbol_3;
	    arg_1 = high_band_float;
	    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		temp = 
			FIXNUM_MINUS(l_round(DOUBLE_TO_DOUBLE_FLOAT((high_band_float 
			- gensymed_symbol_3) * 1000.0 / gensymed_symbol_5),
			_),Truth);
	    else
		temp = Falsity;
	}
    }
    else {
	arg = gensymed_symbol_5;
	arg_1 = 0.0;
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp = Cached_top_of_stack;
	    temp = raw_stack_error_named_error(temp,
		    negative_fuzzy_band_eval_error_message(band_value));
	}
	else {
	    arg = gensymed_symbol_3;
	    arg_1 = gensymed_symbol_4;
	    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		temp = Truth;
	    else
		temp = Falsity;
	}
    }
    result_value = negate(temp);
    reclaim_evaluation_quantity(value1);
    reclaim_evaluation_quantity(value2);
    reclaim_evaluation_quantity(band_value);
    if (FIXNUM_EQ(result_value,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(result_value,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(result_value,Qtruth_value);
    return VALUES_1(temp);
}

/* EVAL-FUZZY-=-FUNCALLED */
Object eval_fuzzy_eq_funcalled(value1,value2,band_value)
    Object value1, value2, band_value;
{
    Object quantity_value1, quantity_value2, band_value_value, result_value;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp_1;
    double gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, arg, arg_1;
    double temp, difference_float;

    x_note_fn_call(207,101);
    quantity_value1 = evaluation_quantity_value(value1);
    quantity_value2 = evaluation_quantity_value(value2);
    band_value_value = evaluation_quantity_value(band_value);
    result_value = Nil;
    gensymed_symbol = quantity_value1;
    gensymed_symbol_1 = quantity_value2;
    gensymed_symbol_2 = band_value_value;
    if (FIXNUMP(gensymed_symbol))
	gensymed_symbol_3 = (double)IFIX(gensymed_symbol);
    else
	gensymed_symbol_3 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol);
    if (FIXNUMP(gensymed_symbol_1))
	gensymed_symbol_4 = (double)IFIX(gensymed_symbol_1);
    else
	gensymed_symbol_4 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    if (FIXNUMP(gensymed_symbol_2))
	gensymed_symbol_5 = (double)IFIX(gensymed_symbol_2);
    else
	gensymed_symbol_5 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_2);
    arg = gensymed_symbol_5;
    arg_1 = 0.0;
    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	temp = gensymed_symbol_3 - gensymed_symbol_4;
	difference_float = ABS(temp);
	arg = difference_float;
	arg_1 = gensymed_symbol_5;
	result_value = arg < arg_1 &&  !inline_nanp_for_comparison(arg) && 
		 !inline_nanp_for_comparison(arg_1) ? FIXNUM_MINUS(Truth,
		l_round(DOUBLE_TO_DOUBLE_FLOAT(2.0 * 1000.0 * 
		difference_float / gensymed_symbol_5),_)) : Falsity;
    }
    else {
	arg = gensymed_symbol_5;
	arg_1 = 0.0;
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp_1 = Cached_top_of_stack;
	    result_value = raw_stack_error_named_error(temp_1,
		    negative_fuzzy_band_eval_error_message(band_value));
	}
	else {
	    arg = gensymed_symbol_3;
	    arg_1 = gensymed_symbol_4;
	    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		result_value = Truth;
	    else
		result_value = Falsity;
	}
    }
    reclaim_evaluation_quantity(value1);
    reclaim_evaluation_quantity(value2);
    reclaim_evaluation_quantity(band_value);
    if (FIXNUM_EQ(result_value,Truth))
	temp_1 = Evaluation_true_value;
    else if (FIXNUM_EQ(result_value,Falsity))
	temp_1 = Evaluation_false_value;
    else
	temp_1 = eval_cons_1(result_value,Qtruth_value);
    return VALUES_1(temp_1);
}

/* EVAL-FUZZY-NOT-=-FUNCALLED */
Object eval_fuzzy_not_eq_funcalled(value1,value2,band_value)
    Object value1, value2, band_value;
{
    Object quantity_value1, quantity_value2, band_value_value, result_value;
    Object temp, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    double gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, arg, arg_1;
    double temp_1, difference_float;

    x_note_fn_call(207,102);
    quantity_value1 = evaluation_quantity_value(value1);
    quantity_value2 = evaluation_quantity_value(value2);
    band_value_value = evaluation_quantity_value(band_value);
    result_value = Nil;
    temp = FIX((SI_Long)0L);
    if (NUM_LT(band_value_value,temp)) {
	temp = Cached_top_of_stack;
	result_value = raw_stack_error_named_error(temp,
		negative_fuzzy_band_eval_error_message(band_value));
    }
    else {
	gensymed_symbol = quantity_value1;
	gensymed_symbol_1 = quantity_value2;
	gensymed_symbol_2 = band_value_value;
	if (FIXNUMP(gensymed_symbol))
	    gensymed_symbol_3 = (double)IFIX(gensymed_symbol);
	else
	    gensymed_symbol_3 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol);
	if (FIXNUMP(gensymed_symbol_1))
	    gensymed_symbol_4 = (double)IFIX(gensymed_symbol_1);
	else
	    gensymed_symbol_4 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
	if (FIXNUMP(gensymed_symbol_2))
	    gensymed_symbol_5 = (double)IFIX(gensymed_symbol_2);
	else
	    gensymed_symbol_5 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_2);
	arg = gensymed_symbol_5;
	arg_1 = 0.0;
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp_1 = gensymed_symbol_3 - gensymed_symbol_4;
	    difference_float = ABS(temp_1);
	    arg = difference_float;
	    arg_1 = gensymed_symbol_5;
	    temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1) ? 
		    FIXNUM_MINUS(Truth,l_round(DOUBLE_TO_DOUBLE_FLOAT(2.0 
		    * 1000.0 * difference_float / gensymed_symbol_5),_)) : 
		    Falsity;
	}
	else {
	    arg = gensymed_symbol_5;
	    arg_1 = 0.0;
	    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		temp = Cached_top_of_stack;
		temp = raw_stack_error_named_error(temp,
			negative_fuzzy_band_eval_error_message(band_value));
	    }
	    else {
		arg = gensymed_symbol_3;
		arg_1 = gensymed_symbol_4;
		if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    temp = Truth;
		else
		    temp = Falsity;
	    }
	}
	result_value = negate(temp);
    }
    reclaim_evaluation_quantity(value1);
    reclaim_evaluation_quantity(value2);
    reclaim_evaluation_quantity(band_value);
    if (FIXNUM_EQ(result_value,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(result_value,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(result_value,Qtruth_value);
    return VALUES_1(temp);
}

/* EVAL-IS-MORE-TRUE-THAN-FUNCALLED */
Object eval_is_more_true_than_funcalled(truth_value_1,truth_value_2)
    Object truth_value_1, truth_value_2;
{
    Object truth_value_value_1, truth_value_value_2, result_value;

    x_note_fn_call(207,103);
    truth_value_value_1 = M_CAR(truth_value_1);
    truth_value_value_2 = M_CAR(truth_value_2);
    result_value = Nil;
    result_value = FIXNUM_GT(truth_value_value_1,truth_value_value_2) ? 
	    Evaluation_true_value : Evaluation_false_value;
    if ( !(EQ(truth_value_1,Evaluation_true_value) || EQ(truth_value_1,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(truth_value_1);
    if ( !(EQ(truth_value_2,Evaluation_true_value) || EQ(truth_value_2,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(truth_value_2);
    return VALUES_1(result_value);
}

/* EVAL-IS-NOT-MORE-TRUE-THAN-FUNCALLED */
Object eval_is_not_more_true_than_funcalled(truth_value_1,truth_value_2)
    Object truth_value_1, truth_value_2;
{
    Object truth_value_value_1, truth_value_value_2, result_value;

    x_note_fn_call(207,104);
    truth_value_value_1 = M_CAR(truth_value_1);
    truth_value_value_2 = M_CAR(truth_value_2);
    result_value = Nil;
    result_value = FIXNUM_GT(truth_value_value_1,truth_value_value_2) ? 
	    Evaluation_false_value : Evaluation_true_value;
    if ( !(EQ(truth_value_1,Evaluation_true_value) || EQ(truth_value_1,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(truth_value_1);
    if ( !(EQ(truth_value_2,Evaluation_true_value) || EQ(truth_value_2,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(truth_value_2);
    return VALUES_1(result_value);
}

/* EVAL-IS-LESS-TRUE-THAN-FUNCALLED */
Object eval_is_less_true_than_funcalled(truth_value_1,truth_value_2)
    Object truth_value_1, truth_value_2;
{
    Object truth_value_value_1, truth_value_value_2, result_value;

    x_note_fn_call(207,105);
    truth_value_value_1 = M_CAR(truth_value_1);
    truth_value_value_2 = M_CAR(truth_value_2);
    result_value = Nil;
    result_value = FIXNUM_LT(truth_value_value_1,truth_value_value_2) ? 
	    Evaluation_true_value : Evaluation_false_value;
    if ( !(EQ(truth_value_1,Evaluation_true_value) || EQ(truth_value_1,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(truth_value_1);
    if ( !(EQ(truth_value_2,Evaluation_true_value) || EQ(truth_value_2,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(truth_value_2);
    return VALUES_1(result_value);
}

/* EVAL-IS-NOT-LESS-TRUE-THAN-FUNCALLED */
Object eval_is_not_less_true_than_funcalled(truth_value_1,truth_value_2)
    Object truth_value_1, truth_value_2;
{
    Object truth_value_value_1, truth_value_value_2, result_value;

    x_note_fn_call(207,106);
    truth_value_value_1 = M_CAR(truth_value_1);
    truth_value_value_2 = M_CAR(truth_value_2);
    result_value = Nil;
    result_value = FIXNUM_LT(truth_value_value_1,truth_value_value_2) ? 
	    Evaluation_false_value : Evaluation_true_value;
    if ( !(EQ(truth_value_1,Evaluation_true_value) || EQ(truth_value_1,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(truth_value_1);
    if ( !(EQ(truth_value_2,Evaluation_true_value) || EQ(truth_value_2,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(truth_value_2);
    return VALUES_1(result_value);
}

static Object Qif_expression;      /* if-expression */

/* IF-EXPRESSION-STACK-NODE-CONVERTER */
Object if_expression_stack_node_converter(expression)
    Object expression;
{
    Object argument, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object arguments, gensymed_symbol, if_node;

    x_note_fn_call(207,107);
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    arguments = ab_loopvar_;
    goto end_1;
    arguments = Qnil;
  end_1:;
    gensymed_symbol = make_stack_node_instruction_1_1(Qif_expression,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    if_node = gensymed_symbol;
    SVREF(if_node,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(if_node);
    return VALUES_1(Nil);
}

static Object string_constant_35;  /* "if-expression emitter" */

static Object string_constant_36;  /* "Non-union unknown type returned from then or else clause." */

static Object string_constant_37;  /* "~a ~a ~a" */

static Object string_constant_38;  /* "An IF with no ELSE clause cannot be used in procedures (except within " */

static Object string_constant_39;  /* "a COLLECT DATA or WAIT statement), since a missing ELSE can produce " */

static Object string_constant_40;  /* "the value unknown." */

/* IF-EXPRESSION-I-CHOOSER */
Object if_expression_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm, argument_nodes;
    Object no_item_implies_unknown_allowed_qm, unknown_argument_qm;
    Object then_and_else_types_without_unknown, no_else_qm, type_spec, temp;
    Object argument_node_cons, argument_type, argument_type_without_unknown;

    x_note_fn_call(207,108);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    unknown_argument_qm = Nil;
    then_and_else_types_without_unknown = Nil;
    no_else_qm = Nil;
    type_spec = Qtruth_value;
    type_spec = 
	    maybe_add_no_item_implies_unknown(maybe_add_unknown(type_spec,
	    unknown_allowed_qm),no_item_implies_unknown_allowed_qm);
    temp = choose_stack_node_instructions_and_types(2,CAR(argument_nodes),
	    type_spec);
    M_CAR(argument_nodes) = temp;
    if (type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_nodes),(SI_Long)6L)))
	unknown_argument_qm = T;
    argument_node_cons = CDR(argument_nodes);
    argument_type = Nil;
    argument_type_without_unknown = Nil;
  next_loop:
    if ( !TRUEP(argument_node_cons))
	goto end_loop;
    argument_type = Nil;
    argument_type_without_unknown = Nil;
    temp = choose_stack_node_instructions_and_types(2,
	    CAR(argument_node_cons),required_type);
    M_CAR(argument_node_cons) = temp;
    argument_type = ISVREF(CAR(argument_node_cons),(SI_Long)6L);
    if (type_specification_subtype_p(list_constant,argument_type)) {
	unknown_argument_qm = T;
	if (union_type_specification_p(argument_type))
	    argument_type_without_unknown = 
		    type_specification_union_minus_type(argument_type,
		    list_constant);
	else {
	    compiler_bug(2,string_constant_35,string_constant_36);
	    argument_type_without_unknown = Qitem_or_datum;
	}
    }
    else
	argument_type_without_unknown = argument_type;
    if ( !TRUEP(then_and_else_types_without_unknown))
	then_and_else_types_without_unknown = argument_type_without_unknown;
    else
	then_and_else_types_without_unknown = 
		make_type_specification_union(then_and_else_types_without_unknown,
		argument_type_without_unknown);
    argument_node_cons = M_CDR(argument_node_cons);
    goto next_loop;
  end_loop:;
    if (IFIX(length(argument_nodes)) == (SI_Long)2L) {
	no_else_qm = T;
	if ( !TRUEP(unknown_allowed_qm))
	    compiler_error(4,string_constant_37,string_constant_38,
		    string_constant_39,string_constant_40);
    }
    if (unknown_argument_qm || no_else_qm) {
	temp = 
		make_type_specification_union(then_and_else_types_without_unknown,
		list_constant);
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    }
    else
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = 
		then_and_else_types_without_unknown;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_41;  /* "if expression emitter" */

static Object string_constant_42;  /* "There is no else clause and unknown is not allowed." */

/* IF-EXPRESSION-I-EMIT */
Object if_expression_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, end_of_if_expression_tag, could_be_unknown_qm;
    Object else_or_end_tag, truth_value_could_be_unknown_qm;
    Object known_truth_value_tag;

    x_note_fn_call(207,109);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    end_of_if_expression_tag = generate_new_goto_tag();
    could_be_unknown_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    else_or_end_tag = THIRD(argument_nodes) || could_be_unknown_qm ? 
	    generate_new_goto_tag() : end_of_if_expression_tag;
    truth_value_could_be_unknown_qm = 
	    type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_nodes),(SI_Long)6L));
    known_truth_value_tag = truth_value_could_be_unknown_qm ? 
	    generate_new_goto_tag() : Nil;
    emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
    if (truth_value_could_be_unknown_qm) {
	emit_branch_long_if_known_byte_codes(byte_code_stream,
		known_truth_value_tag);
	emit_pop_values_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	emit_branch_long_byte_codes(byte_code_stream,end_of_if_expression_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		known_truth_value_tag);
    }
    emit_branch_long_if_not_true_byte_codes(byte_code_stream,else_or_end_tag);
    emit_stack_node_tree(byte_code_stream,SECOND(argument_nodes));
    if (THIRD(argument_nodes)) {
	emit_branch_long_byte_codes(byte_code_stream,end_of_if_expression_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,else_or_end_tag);
	emit_stack_node_tree(byte_code_stream,THIRD(argument_nodes));
    }
    else if (could_be_unknown_qm) {
	emit_branch_long_byte_codes(byte_code_stream,end_of_if_expression_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,else_or_end_tag);
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)2L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
    }
    else
	compiler_bug(2,string_constant_41,string_constant_42);
    register_tag_in_byte_code_stream(2,byte_code_stream,
	    end_of_if_expression_tag);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qaverage_value;      /* average-value */

static Object Qaverage_value_2;    /* average-value-2 */

static Object Qaverage_value_1;    /* average-value-1 */

/* AVERAGE-VALUE-STACK-NODE-CONVERTER */
Object average_value_stack_node_converter(expression)
    Object expression;
{
    Object argument_count, temp, gensymed_symbol, instruction_node, argument;
    Object ab_loop_list_, converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,110);
    argument_count = length(CDR(expression));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),argument_count) && 
	    FIXNUM_LE(argument_count,FIX((SI_Long)127L))))
	temp = Qaverage_value;
    else
	switch (INTEGER_TO_CHAR(argument_count)) {
	  case 4:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qaverage_value;
	    break;
	  case 3:
	    temp = Qaverage_value_2;
	    if (temp);
	    else
		temp = Qaverage_value;
	    break;
	  case 2:
	    temp = Qaverage_value_1;
	    if (temp);
	    else
		temp = Qaverage_value;
	    break;
	  case 1:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qaverage_value;
	    break;
	  case 0:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qaverage_value;
	    break;
	  default:
	    temp = Qaverage_value;
	    break;
	}
    gensymed_symbol = make_stack_node_instruction_1_1(temp,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

/* AVERAGE-VALUE-1-I-CHOOSER */
Object average_value_1_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,111);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* AVERAGE-VALUE-2-I-CHOOSER */
Object average_value_2_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,112);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* AVERAGE-VALUE-1-I-EMIT */
Object average_value_1_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,113);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qaverage_value_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* AVERAGE-VALUE-2-I-EMIT */
Object average_value_2_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,114);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qaverage_value_2);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_43;  /* "average value" */

static Object Qending_with;        /* ending-with */

static Object string_constant_44;  /* "Illegal use of a truth-value in computing a history." */

static Object Qsimulator;          /* simulator */

static Object Qsimulated_value;    /* simulated-value */

static Object string_constant_45;  /* "Cannot compute the ~a of ~NF during the ~NC ~
				    *                          ending with the collection time. ~
				    *                          There are no values in the history for the interval specified."
				    */

static Object string_constant_46;  /* "Cannot compute the ~a of ~NF during the ~NC ~
				    *                          ending with the collection time. ~
				    *                          This object is not keeping history values."
				    */

static Object string_constant_47;  /* "Cannot compute the ~a of ~NF between ~NC ago and ~NC ago. ~
				    *                          There are no values in the history for the interval specified."
				    */

static Object string_constant_48;  /* "Cannot compute the ~a of ~NF between ~NC ago and ~NC ago. ~
				    *                          This object is not keeping history values."
				    */

static Object string_constant_49;  /* "Cannot compute the ~a of ~NF during the last ~NC. ~
				    *                     There are no values in the history for the interval specified."
				    */

static Object string_constant_50;  /* "Cannot compute the ~a of ~NF during the last ~NC. ~
				    *                     This object is not keeping history values."
				    */

static Object string_constant_51;  /* "Cannot compute the ~a of ~NF.  There are no values in its history." */

static Object string_constant_52;  /* "Cannot compute the ~a of ~NF.  This object is not keeping ~
				    *                  history values."
				    */

/* FUNCALL-AVERAGE-VALUE-1-INST */
Object funcall_average_value_1_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,115);
    stack_arg_count = (SI_Long)4L;
    stack_error_string = string_constant_43;
    stack_error_if_empty_history_qm = T;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)3L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)));
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)))),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack))));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = get_averaged_value(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

/* FUNCALL-AVERAGE-VALUE-2-INST */
Object funcall_average_value_2_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,116);
    stack_arg_count = (SI_Long)5L;
    stack_error_string = string_constant_43;
    stack_error_if_empty_history_qm = T;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)4L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)3L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		(SI_Long)2L);
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		    (SI_Long)2L);
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L)),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = get_averaged_value(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qsum_of_values;      /* sum-of-values */

static Object Qsum_of_values_2;    /* sum-of-values-2 */

static Object Qsum_of_values_1;    /* sum-of-values-1 */

/* SUM-OF-VALUES-STACK-NODE-CONVERTER */
Object sum_of_values_stack_node_converter(expression)
    Object expression;
{
    Object argument_count, temp, gensymed_symbol, instruction_node, argument;
    Object ab_loop_list_, converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,117);
    argument_count = length(CDR(expression));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),argument_count) && 
	    FIXNUM_LE(argument_count,FIX((SI_Long)127L))))
	temp = Qsum_of_values;
    else
	switch (INTEGER_TO_CHAR(argument_count)) {
	  case 4:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qsum_of_values;
	    break;
	  case 3:
	    temp = Qsum_of_values_2;
	    if (temp);
	    else
		temp = Qsum_of_values;
	    break;
	  case 2:
	    temp = Qsum_of_values_1;
	    if (temp);
	    else
		temp = Qsum_of_values;
	    break;
	  case 1:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qsum_of_values;
	    break;
	  case 0:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qsum_of_values;
	    break;
	  default:
	    temp = Qsum_of_values;
	    break;
	}
    gensymed_symbol = make_stack_node_instruction_1_1(temp,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* SUM-OF-VALUES-1-I-CHOOSER */
Object sum_of_values_1_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,118);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SUM-OF-VALUES-2-I-CHOOSER */
Object sum_of_values_2_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,119);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SUM-OF-VALUES-1-I-EMIT */
Object sum_of_values_1_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,120);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qsum_of_values_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SUM-OF-VALUES-2-I-EMIT */
Object sum_of_values_2_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,121);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qsum_of_values_2);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_53;  /* "sum of values" */

/* FUNCALL-SUM-OF-VALUES-1-INST */
Object funcall_sum_of_values_1_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,122);
    stack_arg_count = (SI_Long)4L;
    stack_error_string = string_constant_53;
    stack_error_if_empty_history_qm = Nil;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)3L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)));
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)))),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack))));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = get_sum_of_values(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object string_constant_54;  /* "sum of value" */

/* FUNCALL-SUM-OF-VALUES-2-INST */
Object funcall_sum_of_values_2_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,123);
    stack_arg_count = (SI_Long)5L;
    stack_error_string = string_constant_54;
    stack_error_if_empty_history_qm = Nil;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)4L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)3L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		(SI_Long)2L);
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		    (SI_Long)2L);
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L)),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = get_sum_of_values(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qminimum_value;      /* minimum-value */

static Object Qminimum_value_2;    /* minimum-value-2 */

static Object Qminimum_value_1;    /* minimum-value-1 */

/* MINIMUM-VALUE-STACK-NODE-CONVERTER */
Object minimum_value_stack_node_converter(expression)
    Object expression;
{
    Object argument_count, temp, gensymed_symbol, instruction_node, argument;
    Object ab_loop_list_, converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,124);
    argument_count = length(CDR(expression));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),argument_count) && 
	    FIXNUM_LE(argument_count,FIX((SI_Long)127L))))
	temp = Qminimum_value;
    else
	switch (INTEGER_TO_CHAR(argument_count)) {
	  case 4:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qminimum_value;
	    break;
	  case 3:
	    temp = Qminimum_value_2;
	    if (temp);
	    else
		temp = Qminimum_value;
	    break;
	  case 2:
	    temp = Qminimum_value_1;
	    if (temp);
	    else
		temp = Qminimum_value;
	    break;
	  case 1:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qminimum_value;
	    break;
	  case 0:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qminimum_value;
	    break;
	  default:
	    temp = Qminimum_value;
	    break;
	}
    gensymed_symbol = make_stack_node_instruction_1_1(temp,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* MINIMUM-VALUE-1-I-CHOOSER */
Object minimum_value_1_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,125);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MINIMUM-VALUE-2-I-CHOOSER */
Object minimum_value_2_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,126);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MINIMUM-VALUE-1-I-EMIT */
Object minimum_value_1_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,127);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qminimum_value_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MINIMUM-VALUE-2-I-EMIT */
Object minimum_value_2_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,128);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qminimum_value_2);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_55;  /* "minimum value" */

/* FUNCALL-MINIMUM-VALUE-1-INST */
Object funcall_minimum_value_1_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,129);
    stack_arg_count = (SI_Long)4L;
    stack_error_string = string_constant_55;
    stack_error_if_empty_history_qm = T;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)3L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)));
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)))),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack))));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = get_minimum_value(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

/* FUNCALL-MINIMUM-VALUE-2-INST */
Object funcall_minimum_value_2_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,130);
    stack_arg_count = (SI_Long)5L;
    stack_error_string = string_constant_55;
    stack_error_if_empty_history_qm = T;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)4L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)3L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		(SI_Long)2L);
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		    (SI_Long)2L);
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L)),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = get_minimum_value(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qmaximum_value;      /* maximum-value */

static Object Qmaximum_value_2;    /* maximum-value-2 */

static Object Qmaximum_value_1;    /* maximum-value-1 */

/* MAXIMUM-VALUE-STACK-NODE-CONVERTER */
Object maximum_value_stack_node_converter(expression)
    Object expression;
{
    Object argument_count, temp, gensymed_symbol, instruction_node, argument;
    Object ab_loop_list_, converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,131);
    argument_count = length(CDR(expression));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),argument_count) && 
	    FIXNUM_LE(argument_count,FIX((SI_Long)127L))))
	temp = Qmaximum_value;
    else
	switch (INTEGER_TO_CHAR(argument_count)) {
	  case 4:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qmaximum_value;
	    break;
	  case 3:
	    temp = Qmaximum_value_2;
	    if (temp);
	    else
		temp = Qmaximum_value;
	    break;
	  case 2:
	    temp = Qmaximum_value_1;
	    if (temp);
	    else
		temp = Qmaximum_value;
	    break;
	  case 1:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qmaximum_value;
	    break;
	  case 0:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qmaximum_value;
	    break;
	  default:
	    temp = Qmaximum_value;
	    break;
	}
    gensymed_symbol = make_stack_node_instruction_1_1(temp,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* MAXIMUM-VALUE-1-I-CHOOSER */
Object maximum_value_1_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,132);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MAXIMUM-VALUE-2-I-CHOOSER */
Object maximum_value_2_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,133);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MAXIMUM-VALUE-1-I-EMIT */
Object maximum_value_1_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,134);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qmaximum_value_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MAXIMUM-VALUE-2-I-EMIT */
Object maximum_value_2_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,135);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qmaximum_value_2);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_56;  /* "maximum value" */

/* FUNCALL-MAXIMUM-VALUE-1-INST */
Object funcall_maximum_value_1_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,136);
    stack_arg_count = (SI_Long)4L;
    stack_error_string = string_constant_56;
    stack_error_if_empty_history_qm = T;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)3L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)));
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)))),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack))));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = get_maximum_value(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

/* FUNCALL-MAXIMUM-VALUE-2-INST */
Object funcall_maximum_value_2_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,137);
    stack_arg_count = (SI_Long)5L;
    stack_error_string = string_constant_56;
    stack_error_if_empty_history_qm = T;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)4L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)3L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		(SI_Long)2L);
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		    (SI_Long)2L);
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L)),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = get_maximum_value(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qstandard_deviation;  /* standard-deviation */

static Object Qstandard_deviation_2;  /* standard-deviation-2 */

static Object Qstandard_deviation_1;  /* standard-deviation-1 */

/* STANDARD-DEVIATION-STACK-NODE-CONVERTER */
Object standard_deviation_stack_node_converter(expression)
    Object expression;
{
    Object argument_count, temp, gensymed_symbol, instruction_node, argument;
    Object ab_loop_list_, converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,138);
    argument_count = length(CDR(expression));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),argument_count) && 
	    FIXNUM_LE(argument_count,FIX((SI_Long)127L))))
	temp = Qstandard_deviation;
    else
	switch (INTEGER_TO_CHAR(argument_count)) {
	  case 4:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qstandard_deviation;
	    break;
	  case 3:
	    temp = Qstandard_deviation_2;
	    if (temp);
	    else
		temp = Qstandard_deviation;
	    break;
	  case 2:
	    temp = Qstandard_deviation_1;
	    if (temp);
	    else
		temp = Qstandard_deviation;
	    break;
	  case 1:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qstandard_deviation;
	    break;
	  case 0:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qstandard_deviation;
	    break;
	  default:
	    temp = Qstandard_deviation;
	    break;
	}
    gensymed_symbol = make_stack_node_instruction_1_1(temp,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* STANDARD-DEVIATION-1-I-CHOOSER */
Object standard_deviation_1_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,139);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* STANDARD-DEVIATION-2-I-CHOOSER */
Object standard_deviation_2_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,140);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* STANDARD-DEVIATION-1-I-EMIT */
Object standard_deviation_1_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,141);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qstandard_deviation_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* STANDARD-DEVIATION-2-I-EMIT */
Object standard_deviation_2_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,142);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qstandard_deviation_2);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_57;  /* "standard deviation" */

/* FUNCALL-STANDARD-DEVIATION-1-INST */
Object funcall_standard_deviation_1_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,143);
    stack_arg_count = (SI_Long)4L;
    stack_error_string = string_constant_57;
    stack_error_if_empty_history_qm = T;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)3L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)));
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)))),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack))));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = 
		get_standard_deviation_of_value(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

/* FUNCALL-STANDARD-DEVIATION-2-INST */
Object funcall_standard_deviation_2_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,144);
    stack_arg_count = (SI_Long)5L;
    stack_error_string = string_constant_57;
    stack_error_if_empty_history_qm = T;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)4L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)3L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		(SI_Long)2L);
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		    (SI_Long)2L);
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L)),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = 
		get_standard_deviation_of_value(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qnumber_of_datapoints;  /* number-of-datapoints */

static Object Qnumber_of_datapoints_2;  /* number-of-datapoints-2 */

static Object Qnumber_of_datapoints_1;  /* number-of-datapoints-1 */

static Object Qnumber_of_datapoints_0;  /* number-of-datapoints-0 */

/* NUMBER-OF-DATAPOINTS-STACK-NODE-CONVERTER */
Object number_of_datapoints_stack_node_converter(expression)
    Object expression;
{
    Object argument_count, temp, gensymed_symbol, instruction_node, argument;
    Object ab_loop_list_, converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,145);
    argument_count = length(CDR(expression));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),argument_count) && 
	    FIXNUM_LE(argument_count,FIX((SI_Long)127L))))
	temp = Qnumber_of_datapoints;
    else
	switch (INTEGER_TO_CHAR(argument_count)) {
	  case 4:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qnumber_of_datapoints;
	    break;
	  case 3:
	    temp = Qnumber_of_datapoints_2;
	    if (temp);
	    else
		temp = Qnumber_of_datapoints;
	    break;
	  case 2:
	    temp = Qnumber_of_datapoints_1;
	    if (temp);
	    else
		temp = Qnumber_of_datapoints;
	    break;
	  case 1:
	    temp = Qnumber_of_datapoints_0;
	    if (temp);
	    else
		temp = Qnumber_of_datapoints;
	    break;
	  case 0:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qnumber_of_datapoints;
	    break;
	  default:
	    temp = Qnumber_of_datapoints;
	    break;
	}
    gensymed_symbol = make_stack_node_instruction_1_1(temp,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* NUMBER-OF-DATAPOINTS-0-I-CHOOSER */
Object number_of_datapoints_0_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,146);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* NUMBER-OF-DATAPOINTS-1-I-CHOOSER */
Object number_of_datapoints_1_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,147);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* NUMBER-OF-DATAPOINTS-2-I-CHOOSER */
Object number_of_datapoints_2_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,148);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* NUMBER-OF-DATAPOINTS-0-I-EMIT */
Object number_of_datapoints_0_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,149);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qnumber_of_datapoints_0);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* NUMBER-OF-DATAPOINTS-1-I-EMIT */
Object number_of_datapoints_1_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,150);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qnumber_of_datapoints_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* NUMBER-OF-DATAPOINTS-2-I-EMIT */
Object number_of_datapoints_2_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,151);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qnumber_of_datapoints_2);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_58;  /* "number of history datapoints" */

/* FUNCALL-NUMBER-OF-DATAPOINTS-0-INST */
Object funcall_number_of_datapoints_0_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,152);
    stack_arg_count = (SI_Long)3L;
    stack_error_string = string_constant_58;
    stack_error_if_empty_history_qm = Nil;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)2L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack)))) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(top_of_stack));
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,IFIX(top_of_stack));
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(top_of_stack))),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(top_of_stack)));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = number_of_datapoints(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

/* FUNCALL-NUMBER-OF-DATAPOINTS-1-INST */
Object funcall_number_of_datapoints_1_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,153);
    stack_arg_count = (SI_Long)4L;
    stack_error_string = string_constant_58;
    stack_error_if_empty_history_qm = Nil;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)3L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)));
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)))),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack))));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = number_of_datapoints(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

/* FUNCALL-NUMBER-OF-DATAPOINTS-2-INST */
Object funcall_number_of_datapoints_2_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, stack_error_if_empty_history_qm;
    Object variable_or_parameter_qm, start_of_interval_qm, evaluation_value;
    Object end_of_interval_qm, top_of_stack_1, message_1, unknown_allowed;
    Object no_item_allowed, in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, collection_time_qm, result_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, i, ab_loop_bind_, decff_1_arg;
    SI_Long top_of_stack_new_value;
    char start_interval_p, end_interval_p;
    double aref_new_value, simulation_time;

    x_note_fn_call(207,154);
    stack_arg_count = (SI_Long)5L;
    stack_error_string = string_constant_58;
    stack_error_if_empty_history_qm = Nil;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)4L);
    start_interval_p = stack_arg_count > (SI_Long)3L;
    end_interval_p = stack_arg_count > (SI_Long)4L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)3L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		(SI_Long)2L);
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		    (SI_Long)2L);
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L)),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = number_of_datapoints(variable_or_parameter_qm,
		in_simulator_qm,beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    if (stack_error_if_empty_history_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_45,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(5,
			string_constant_46,stack_error_string,
			variable_or_parameter_qm,start_of_interval_qm,
			Qseconds);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_47,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_48,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	if (stack_error_if_empty_history_qm) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_49,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_50,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (stack_error_if_empty_history_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_51,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_52,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qrate_of_change;     /* rate-of-change */

static Object Qrate_of_change_2;   /* rate-of-change-2 */

static Object Qrate_of_change_1;   /* rate-of-change-1 */

/* RATE-OF-CHANGE-STACK-NODE-CONVERTER */
Object rate_of_change_stack_node_converter(expression)
    Object expression;
{
    Object argument_count, temp, gensymed_symbol, instruction_node, argument;
    Object ab_loop_list_, converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,155);
    argument_count = length(CDR(expression));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),argument_count) && 
	    FIXNUM_LE(argument_count,FIX((SI_Long)127L))))
	temp = Qrate_of_change;
    else
	switch (INTEGER_TO_CHAR(argument_count)) {
	  case 4:
	    temp = Qrate_of_change_2;
	    if (temp);
	    else
		temp = Qrate_of_change;
	    break;
	  case 3:
	    temp = Qrate_of_change_1;
	    if (temp);
	    else
		temp = Qrate_of_change;
	    break;
	  case 2:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qrate_of_change;
	    break;
	  case 1:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qrate_of_change;
	    break;
	  case 0:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qrate_of_change;
	    break;
	  default:
	    temp = Qrate_of_change;
	    break;
	}
    gensymed_symbol = make_stack_node_instruction_1_1(temp,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* RATE-OF-CHANGE-1-I-CHOOSER */
Object rate_of_change_1_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,156);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qt ? Qsymbol : Qnumber,
		unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* RATE-OF-CHANGE-2-I-CHOOSER */
Object rate_of_change_2_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,157);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qt ? Qsymbol : Qnumber,
		unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* RATE-OF-CHANGE-1-I-EMIT */
Object rate_of_change_1_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,158);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qrate_of_change_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* RATE-OF-CHANGE-2-I-EMIT */
Object rate_of_change_2_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,159);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qrate_of_change_2);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_59;  /* "rate of change" */

static Object Qminute;             /* minute */

static Object Qminutes;            /* minutes */

static Object Qhour;               /* hour */

static Object Qhours;              /* hours */

static Object Qday;                /* day */

static Object Qdays;               /* days */

static Object Qweek;               /* week */

static Object Qweeks;              /* weeks */

static Object string_constant_60;  /* "Cannot compute the ~a of ~NF.  ~NV is an invalid time-unit." */

static Object string_constant_61;  /* "Cannot compute the ~a of ~NF.  ~a is an invalid time unit." */

static Object string_constant_62;  /* "Cannot compute the ~a of ~NF during the ~NC ~
				    *                      ending with the collection time. ~
				    *                      There are no values in the history for the interval specified."
				    */

static Object string_constant_63;  /* "Cannot compute the ~a of ~NF between ~NC ago and ~NC ago. ~
				    *                      There are no values in the history for the interval specified."
				    */

static Object string_constant_64;  /* "Cannot compute the ~a of ~NF during the last ~NC. ~
				    *                  There are no values in the history for the interval specified."
				    */

static Object string_constant_65;  /* "Cannot compute the ~a of ~NF.  There are no values in its ~
				    *                  history."
				    */

/* FUNCALL-RATE-OF-CHANGE-1-INST */
Object funcall_rate_of_change_1_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, variable_or_parameter_qm, time_units_qm;
    Object start_of_interval_qm, evaluation_value, end_of_interval_qm;
    Object top_of_stack_1, message_1, unknown_allowed, no_item_allowed;
    Object in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, gensymed_symbol;
    Object converted_units_qm, collection_time_qm, result_qm, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, i, decff_1_arg, top_of_stack_new_value;
    char start_interval_p, end_interval_p, temp;
    double aref_new_value, simulation_time;
    Object result;

    x_note_fn_call(207,160);
    stack_arg_count = (SI_Long)5L;
    stack_error_string = string_constant_59;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)4L);
    time_units_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)3L);
    start_interval_p = stack_arg_count > (SI_Long)4L;
    end_interval_p = stack_arg_count > (SI_Long)5L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)));
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)))),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack))));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	if (time_units_qm) {
	    gensymed_symbol = time_units_qm;
	    if (EQ(gensymed_symbol,Qnumber))
		converted_units_qm = FIX((SI_Long)1L);
	    else if (EQ(gensymed_symbol,Qsecond) || EQ(gensymed_symbol,
		    Qseconds))
		converted_units_qm = FIX((SI_Long)1L);
	    else if (EQ(gensymed_symbol,Qminute) || EQ(gensymed_symbol,
		    Qminutes))
		converted_units_qm = FIX((SI_Long)60L);
	    else if (EQ(gensymed_symbol,Qhour) || EQ(gensymed_symbol,Qhours))
		converted_units_qm = FIX((SI_Long)3600L);
	    else if (EQ(gensymed_symbol,Qday) || EQ(gensymed_symbol,Qdays))
		converted_units_qm = FIX((SI_Long)86400L);
	    else if (EQ(gensymed_symbol,Qweek) || EQ(gensymed_symbol,Qweeks))
		converted_units_qm = FIX((SI_Long)604800L);
	    else
		converted_units_qm = FIX((SI_Long)1L);
	}
	else
	    converted_units_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (time_units_qm &&  !TRUEP(converted_units_qm)) {
	    gensymed_symbol = time_units_qm;
	    temp = FIXNUMP(gensymed_symbol);
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp = EQ(gensymed_symbol,Qtruth_value);
		if (temp);
		else
		    temp = EQ(gensymed_symbol,Qiteration_state);
		if (temp);
		else if (SYMBOLP(gensymed_symbol)) {
		    skip_list = CDR(Defined_evaluation_value_types);
		    key_value = gensymed_symbol;
		    key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop:
		    if (level < ab_loop_bind_)
			goto end_loop;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_1;
		    goto next_loop_1;
		  end_loop_2:
		  end_1:
		    level = level - (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_60,stack_error_string,
			variable_or_parameter_qm,time_units_qm);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_61,stack_error_string,
			variable_or_parameter_qm,time_units_qm);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = get_rate_of_change_of_value(variable_or_parameter_qm,
		in_simulator_qm,converted_units_qm,
		beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_62,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_63,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_64,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_65,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop_3:
    if (i >= ab_loop_bind_)
	goto end_loop_3;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

/* FUNCALL-RATE-OF-CHANGE-2-INST */
Object funcall_rate_of_change_2_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, variable_or_parameter_qm, time_units_qm;
    Object start_of_interval_qm, evaluation_value, end_of_interval_qm;
    Object top_of_stack_1, message_1, unknown_allowed, no_item_allowed;
    Object in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, gensymed_symbol;
    Object converted_units_qm, collection_time_qm, result_qm, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, i, decff_1_arg, top_of_stack_new_value;
    char start_interval_p, end_interval_p, temp;
    double aref_new_value, simulation_time;
    Object result;

    x_note_fn_call(207,161);
    stack_arg_count = (SI_Long)6L;
    stack_error_string = string_constant_59;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)5L);
    time_units_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)4L);
    start_interval_p = stack_arg_count > (SI_Long)4L;
    end_interval_p = stack_arg_count > (SI_Long)5L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)3L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		(SI_Long)2L);
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		    (SI_Long)2L);
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L)),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	if (time_units_qm) {
	    gensymed_symbol = time_units_qm;
	    if (EQ(gensymed_symbol,Qnumber))
		converted_units_qm = FIX((SI_Long)1L);
	    else if (EQ(gensymed_symbol,Qsecond) || EQ(gensymed_symbol,
		    Qseconds))
		converted_units_qm = FIX((SI_Long)1L);
	    else if (EQ(gensymed_symbol,Qminute) || EQ(gensymed_symbol,
		    Qminutes))
		converted_units_qm = FIX((SI_Long)60L);
	    else if (EQ(gensymed_symbol,Qhour) || EQ(gensymed_symbol,Qhours))
		converted_units_qm = FIX((SI_Long)3600L);
	    else if (EQ(gensymed_symbol,Qday) || EQ(gensymed_symbol,Qdays))
		converted_units_qm = FIX((SI_Long)86400L);
	    else if (EQ(gensymed_symbol,Qweek) || EQ(gensymed_symbol,Qweeks))
		converted_units_qm = FIX((SI_Long)604800L);
	    else
		converted_units_qm = FIX((SI_Long)1L);
	}
	else
	    converted_units_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (time_units_qm &&  !TRUEP(converted_units_qm)) {
	    gensymed_symbol = time_units_qm;
	    temp = FIXNUMP(gensymed_symbol);
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp = EQ(gensymed_symbol,Qtruth_value);
		if (temp);
		else
		    temp = EQ(gensymed_symbol,Qiteration_state);
		if (temp);
		else if (SYMBOLP(gensymed_symbol)) {
		    skip_list = CDR(Defined_evaluation_value_types);
		    key_value = gensymed_symbol;
		    key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop:
		    if (level < ab_loop_bind_)
			goto end_loop;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_1;
		    goto next_loop_1;
		  end_loop_2:
		  end_1:
		    level = level - (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_60,stack_error_string,
			variable_or_parameter_qm,time_units_qm);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_61,stack_error_string,
			variable_or_parameter_qm,time_units_qm);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = get_rate_of_change_of_value(variable_or_parameter_qm,
		in_simulator_qm,converted_units_qm,
		beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_62,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_63,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_64,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_65,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop_3:
    if (i >= ab_loop_bind_)
	goto end_loop_3;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qintegral;           /* integral */

static Object Qintegral_2;         /* integral-2 */

static Object Qintegral_1;         /* integral-1 */

/* INTEGRAL-STACK-NODE-CONVERTER */
Object integral_stack_node_converter(expression)
    Object expression;
{
    Object argument_count, temp, gensymed_symbol, instruction_node, argument;
    Object ab_loop_list_, converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,162);
    argument_count = length(CDR(expression));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),argument_count) && 
	    FIXNUM_LE(argument_count,FIX((SI_Long)127L))))
	temp = Qintegral;
    else
	switch (INTEGER_TO_CHAR(argument_count)) {
	  case 4:
	    temp = Qintegral_2;
	    if (temp);
	    else
		temp = Qintegral;
	    break;
	  case 3:
	    temp = Qintegral_1;
	    if (temp);
	    else
		temp = Qintegral;
	    break;
	  case 2:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qintegral;
	    break;
	  case 1:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qintegral;
	    break;
	  case 0:
	    temp = Qnil;
	    if (temp);
	    else
		temp = Qintegral;
	    break;
	  default:
	    temp = Qintegral;
	    break;
	}
    gensymed_symbol = make_stack_node_instruction_1_1(temp,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* INTEGRAL-1-I-CHOOSER */
Object integral_1_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,163);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qt ? Qsymbol : Qnumber,
		unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* INTEGRAL-2-I-CHOOSER */
Object integral_2_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,164);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qt ? Qsymbol : Qnumber,
		unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* INTEGRAL-1-I-EMIT */
Object integral_1_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,165);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qintegral_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* INTEGRAL-2-I-EMIT */
Object integral_2_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,166);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qintegral_2);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_66;  /* "integral" */

/* FUNCALL-INTEGRAL-1-INST */
Object funcall_integral_1_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, variable_or_parameter_qm, time_units_qm;
    Object start_of_interval_qm, evaluation_value, end_of_interval_qm;
    Object top_of_stack_1, message_1, unknown_allowed, no_item_allowed;
    Object in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, gensymed_symbol;
    Object converted_units_qm, collection_time_qm, result_qm, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, i, decff_1_arg, top_of_stack_new_value;
    char start_interval_p, end_interval_p, temp;
    double aref_new_value, simulation_time;
    Object result;

    x_note_fn_call(207,167);
    stack_arg_count = (SI_Long)5L;
    stack_error_string = string_constant_66;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)4L);
    time_units_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)3L);
    start_interval_p = stack_arg_count > (SI_Long)4L;
    end_interval_p = stack_arg_count > (SI_Long)5L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)));
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack)))),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(FIXNUM_SUB1(top_of_stack))));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	if (time_units_qm) {
	    gensymed_symbol = time_units_qm;
	    if (EQ(gensymed_symbol,Qnumber))
		converted_units_qm = FIX((SI_Long)1L);
	    else if (EQ(gensymed_symbol,Qsecond) || EQ(gensymed_symbol,
		    Qseconds))
		converted_units_qm = FIX((SI_Long)1L);
	    else if (EQ(gensymed_symbol,Qminute) || EQ(gensymed_symbol,
		    Qminutes))
		converted_units_qm = FIX((SI_Long)60L);
	    else if (EQ(gensymed_symbol,Qhour) || EQ(gensymed_symbol,Qhours))
		converted_units_qm = FIX((SI_Long)3600L);
	    else if (EQ(gensymed_symbol,Qday) || EQ(gensymed_symbol,Qdays))
		converted_units_qm = FIX((SI_Long)86400L);
	    else if (EQ(gensymed_symbol,Qweek) || EQ(gensymed_symbol,Qweeks))
		converted_units_qm = FIX((SI_Long)604800L);
	    else
		converted_units_qm = FIX((SI_Long)1L);
	}
	else
	    converted_units_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (time_units_qm &&  !TRUEP(converted_units_qm)) {
	    gensymed_symbol = time_units_qm;
	    temp = FIXNUMP(gensymed_symbol);
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp = EQ(gensymed_symbol,Qtruth_value);
		if (temp);
		else
		    temp = EQ(gensymed_symbol,Qiteration_state);
		if (temp);
		else if (SYMBOLP(gensymed_symbol)) {
		    skip_list = CDR(Defined_evaluation_value_types);
		    key_value = gensymed_symbol;
		    key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop:
		    if (level < ab_loop_bind_)
			goto end_loop;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_1;
		    goto next_loop_1;
		  end_loop_2:
		  end_1:
		    level = level - (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_60,stack_error_string,
			variable_or_parameter_qm,time_units_qm);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_61,stack_error_string,
			variable_or_parameter_qm,time_units_qm);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = 
		get_integral_of_value_over_interval(variable_or_parameter_qm,
		in_simulator_qm,converted_units_qm,
		beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_62,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_63,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_64,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_65,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop_3:
    if (i >= ab_loop_bind_)
	goto end_loop_3;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

/* FUNCALL-INTEGRAL-2-INST */
Object funcall_integral_2_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object stack_error_string, variable_or_parameter_qm, time_units_qm;
    Object start_of_interval_qm, evaluation_value, end_of_interval_qm;
    Object top_of_stack_1, message_1, unknown_allowed, no_item_allowed;
    Object in_simulator_qm, begin_qm, end_qm;
    Object beginning_of_interval_for_environment_qm;
    Object end_of_interval_for_environment_qm, gensymed_symbol;
    Object converted_units_qm, collection_time_qm, result_qm, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, integer_portion, micro_time, aref_arg_1;
    Object managed_number_or_value, return_value_qm, stack_arg;
    SI_Long stack_arg_count, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, i, decff_1_arg, top_of_stack_new_value;
    char start_interval_p, end_interval_p, temp;
    double aref_new_value, simulation_time;
    Object result;

    x_note_fn_call(207,168);
    stack_arg_count = (SI_Long)6L;
    stack_error_string = string_constant_66;
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)5L);
    time_units_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)4L);
    start_interval_p = stack_arg_count > (SI_Long)4L;
    end_interval_p = stack_arg_count > (SI_Long)5L;
    start_of_interval_qm = start_interval_p ? 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)3L)) : Nil;
    if (end_interval_p) {
	evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		(SI_Long)2L);
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - 
		    (SI_Long)2L);
	    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		    Qtruth_value) ? EQ(M_CAR(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L)),Truth) : TRUEP(Nil))
		end_of_interval_qm = Qending_with;
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		end_of_interval_qm = 
			raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    end_of_interval_qm = 
		    evaluation_quantity_value(ISVREF(local_stack,
		    IFIX(top_of_stack) - (SI_Long)2L));
    }
    else
	end_of_interval_qm = Nil;
    unknown_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)2L) - 
	    (SI_Long)1L)));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (stack_arg_count - (stack_arg_count - (SI_Long)1L) - 
	    (SI_Long)1L)));
    if (variable_or_parameter_qm) {
	in_simulator_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
	if (in_simulator_qm);
	else
	    in_simulator_qm = EQ(Current_environment,Qsimulated_value) ? T 
		    : Nil;
	begin_qm = start_of_interval_qm;
	end_qm = end_of_interval_qm;
	beginning_of_interval_for_environment_qm = Nil;
	end_of_interval_for_environment_qm = Nil;
	if (time_units_qm) {
	    gensymed_symbol = time_units_qm;
	    if (EQ(gensymed_symbol,Qnumber))
		converted_units_qm = FIX((SI_Long)1L);
	    else if (EQ(gensymed_symbol,Qsecond) || EQ(gensymed_symbol,
		    Qseconds))
		converted_units_qm = FIX((SI_Long)1L);
	    else if (EQ(gensymed_symbol,Qminute) || EQ(gensymed_symbol,
		    Qminutes))
		converted_units_qm = FIX((SI_Long)60L);
	    else if (EQ(gensymed_symbol,Qhour) || EQ(gensymed_symbol,Qhours))
		converted_units_qm = FIX((SI_Long)3600L);
	    else if (EQ(gensymed_symbol,Qday) || EQ(gensymed_symbol,Qdays))
		converted_units_qm = FIX((SI_Long)86400L);
	    else if (EQ(gensymed_symbol,Qweek) || EQ(gensymed_symbol,Qweeks))
		converted_units_qm = FIX((SI_Long)604800L);
	    else
		converted_units_qm = FIX((SI_Long)1L);
	}
	else
	    converted_units_qm = Nil;
	collection_time_qm = Nil;
	result_qm = Nil;
	if (time_units_qm &&  !TRUEP(converted_units_qm)) {
	    gensymed_symbol = time_units_qm;
	    temp = FIXNUMP(gensymed_symbol);
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp = EQ(gensymed_symbol,Qtruth_value);
		if (temp);
		else
		    temp = EQ(gensymed_symbol,Qiteration_state);
		if (temp);
		else if (SYMBOLP(gensymed_symbol)) {
		    skip_list = CDR(Defined_evaluation_value_types);
		    key_value = gensymed_symbol;
		    key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop:
		    if (level < ab_loop_bind_)
			goto end_loop;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_1;
		    goto next_loop_1;
		  end_loop_2:
		  end_1:
		    level = level - (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_60,stack_error_string,
			variable_or_parameter_qm,time_units_qm);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_61,stack_error_string,
			variable_or_parameter_qm,time_units_qm);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	if (in_simulator_qm) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    simulation_time = 
		    DFLOAT_ISAREF_1(Simulation_time_managed_float,(SI_Long)0L);
	    beginning_of_interval_for_environment_qm = begin_qm ? 
		    minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),
		    begin_qm) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(simulation_time),end_qm);
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(simulation_time);
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	else {
	    if (EQ(end_qm,Qending_with)) {
		managed_number_or_value = ISVREF(variable_or_parameter_qm,
			(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    collection_time_qm = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    collection_time_qm = 
			    copy_text_string(managed_number_or_value);
		else
		    collection_time_qm = managed_number_or_value;
	    }
	    beginning_of_interval_for_environment_qm = begin_qm ? minusn(3,
		    EQ(end_qm,Qending_with) ? collection_time_qm : 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),begin_qm,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))) : Nil;
	    if (end_qm)
		end_of_interval_for_environment_qm = EQ(end_qm,
			Qending_with) ? minus(collection_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L))) : minusn(3,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L)),end_qm,
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L)));
	    else if (begin_qm)
		end_of_interval_for_environment_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L));
	    else
		end_of_interval_for_environment_qm = Nil;
	}
	result_qm = 
		get_integral_of_value_over_interval(variable_or_parameter_qm,
		in_simulator_qm,converted_units_qm,
		beginning_of_interval_for_environment_qm,
		end_of_interval_for_environment_qm);
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else if (end_of_interval_qm && start_of_interval_qm) {
	if (EQ(end_of_interval_qm,Qending_with)) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_62,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(7,
		    string_constant_63,stack_error_string,
		    variable_or_parameter_qm,start_of_interval_qm,Qseconds,
		    end_of_interval_qm,Qseconds);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else if (start_of_interval_qm) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_64,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(5,string_constant_65,
		stack_error_string,variable_or_parameter_qm,
		start_of_interval_qm,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    i = (SI_Long)1L;
    ab_loop_bind_ = stack_arg_count;
    stack_arg = Nil;
  next_loop_3:
    if (i >= ab_loop_bind_)
	goto end_loop_3;
    stack_arg = ISVREF(local_stack,IFIX(top_of_stack) - (stack_arg_count - 
	    i - (SI_Long)1L));
    if (stack_arg)
	reclaim_evaluation_value(stack_arg);
    i = i + (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    decff_1_arg = stack_arg_count - (SI_Long)1L;
    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qhistoric_value;     /* historic-value */

/* HISTORIC-VALUE-STACK-NODE-CONVERTER */
Object historic_value_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, instruction_node, argument, ab_loop_list_;
    Object converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,169);
    gensymed_symbol = make_stack_node_instruction_1_1(Qhistoric_value,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* HISTORIC-VALUE-I-CHOOSER */
Object historic_value_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,170);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qdatum,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* HISTORIC-VALUE-I-EMIT */
Object historic_value_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,171);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qhistoric_value);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_67;  /* "Cannot reference the value of ~NF as of ~NC ago.  ~
				    *               There was no value at that time."
				    */

/* FUNCALL-HISTORIC-VALUE-INST */
Object funcall_historic_value_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object variable_or_parameter_qm, interval, unknown_allowed;
    Object no_item_allowed, gensymed_symbol, integer_portion, micro_time;
    Object aref_arg_1, result_qm, return_value_qm, top_of_stack_1, message_1;
    Object evaluation_truth_value;
    SI_Long top_of_stack_new_value;
    double aref_new_value;

    x_note_fn_call(207,172);
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)3L);
    interval = evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L));
    unknown_allowed = M_CAR(ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack))));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack)));
    if (variable_or_parameter_qm) {
	if (EQ(Current_environment,Qsimulator) || EQ(Current_environment,
		Qsimulated_value)) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    result_qm = 
		    get_historical_delayed_value(variable_or_parameter_qm,
		    T,
		    minus(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Simulation_time_managed_float,
		    (SI_Long)0L)),interval));
	}
	else
	    result_qm = 
		    get_historical_delayed_value(variable_or_parameter_qm,
		    Nil,minusn(3,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),interval,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))));
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm) {
	return_value_qm = 
		make_evaluation_value_reclaiming_argument(result_qm,
		type_specification_of_variable_or_parameter_value(variable_or_parameter_qm));
	result_qm = Nil;
    }
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_67,
		variable_or_parameter_qm,interval,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    reclaim_evaluation_quantity(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)2L));
    evaluation_truth_value = ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack)));
    if ( !(EQ(evaluation_truth_value,Evaluation_true_value) || 
	    EQ(evaluation_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(evaluation_truth_value);
    evaluation_truth_value = ISVREF(local_stack,IFIX(top_of_stack));
    if ( !(EQ(evaluation_truth_value,Evaluation_true_value) || 
	    EQ(evaluation_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(evaluation_truth_value);
    top_of_stack_new_value = IFIX(top_of_stack) - (SI_Long)3L;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qvalue_of_previous_datapoint;  /* value-of-previous-datapoint */

/* VALUE-OF-PREVIOUS-DATAPOINT-STACK-NODE-CONVERTER */
Object value_of_previous_datapoint_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, instruction_node, argument, ab_loop_list_;
    Object converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,173);
    gensymed_symbol = 
	    make_stack_node_instruction_1_1(Qvalue_of_previous_datapoint,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* VALUE-OF-PREVIOUS-DATAPOINT-I-CHOOSER */
Object value_of_previous_datapoint_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,174);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qdatum,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* VALUE-OF-PREVIOUS-DATAPOINT-I-EMIT */
Object value_of_previous_datapoint_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,175);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qvalue_of_previous_datapoint);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_68;  /* "Cannot reference the value of ~NF as of ~d datapoints ago.  A ~
				    *       history datapoint must be referenced by a non-negative integer."
				    */

static Object string_constant_69;  /* "Cannot reference the value of ~NF as of ~d datapoints ago.  ~
				    *             There was no value at that time."
				    */

/* FUNCALL-VALUE-OF-PREVIOUS-DATAPOINT-INST */
Object funcall_value_of_previous_datapoint_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object variable_or_parameter_qm, number_of_datapoints_ago, unknown_allowed;
    Object no_item_allowed, result_qm, return_value_qm, top_of_stack_1;
    Object message_1, evaluation_truth_value;
    SI_Long top_of_stack_new_value;

    x_note_fn_call(207,176);
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)3L);
    number_of_datapoints_ago = 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L));
    unknown_allowed = M_CAR(ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack))));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack)));
    result_qm = Nil;
    return_value_qm = Nil;
    if (IFIX(number_of_datapoints_ago) < (SI_Long)0L) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_68,
		variable_or_parameter_qm,number_of_datapoints_ago);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    result_qm = variable_or_parameter_qm ? (EQ(Current_environment,
	    Qsimulator) || EQ(Current_environment,Qsimulated_value) ? 
	    get_value_of_previous_datapoint(variable_or_parameter_qm,T,
	    number_of_datapoints_ago) : 
	    get_value_of_previous_datapoint(variable_or_parameter_qm,Nil,
	    number_of_datapoints_ago)) : Nil;
    if (result_qm) {
	return_value_qm = 
		make_evaluation_value_reclaiming_argument(result_qm,
		type_specification_of_variable_or_parameter_value(variable_or_parameter_qm));
	result_qm = Nil;
    }
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_69,
		variable_or_parameter_qm,number_of_datapoints_ago);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    reclaim_evaluation_quantity(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)2L));
    evaluation_truth_value = ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack)));
    if ( !(EQ(evaluation_truth_value,Evaluation_true_value) || 
	    EQ(evaluation_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(evaluation_truth_value);
    evaluation_truth_value = ISVREF(local_stack,IFIX(top_of_stack));
    if ( !(EQ(evaluation_truth_value,Evaluation_true_value) || 
	    EQ(evaluation_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(evaluation_truth_value);
    top_of_stack_new_value = IFIX(top_of_stack) - (SI_Long)3L;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qinterpolated_value;  /* interpolated-value */

/* INTERPOLATED-VALUE-STACK-NODE-CONVERTER */
Object interpolated_value_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, instruction_node, argument, ab_loop_list_;
    Object converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(207,177);
    gensymed_symbol = make_stack_node_instruction_1_1(Qinterpolated_value,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* INTERPOLATED-VALUE-I-CHOOSER */
Object interpolated_value_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(207,178);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_8,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* INTERPOLATED-VALUE-I-EMIT */
Object interpolated_value_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(207,179);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qinterpolated_value);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_70;  /* "Cannot reference the value of ~NF as of ~NC ago.  ~
				    *            There was no value at that time."
				    */

/* FUNCALL-INTERPOLATED-VALUE-INST */
Object funcall_interpolated_value_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object variable_or_parameter_qm, interval_ago, unknown_allowed;
    Object no_item_allowed, gensymed_symbol, integer_portion, micro_time;
    Object aref_arg_1, result_qm, return_value_qm, top_of_stack_1, message_1;
    Object evaluation_truth_value;
    SI_Long top_of_stack_new_value;
    double aref_new_value;

    x_note_fn_call(207,180);
    variable_or_parameter_qm = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)3L);
    interval_ago = evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L));
    unknown_allowed = M_CAR(ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack))));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack)));
    if (variable_or_parameter_qm) {
	if (EQ(Current_environment,Qsimulator) || EQ(Current_environment,
		Qsimulated_value)) {
	    gensymed_symbol = get_current_time_in_simulation_environment();
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    result_qm = 
		    get_interpolated_delayed_value(variable_or_parameter_qm,
		    T,
		    minus(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Simulation_time_managed_float,
		    (SI_Long)0L)),interval_ago));
	}
	else
	    result_qm = 
		    get_interpolated_delayed_value(variable_or_parameter_qm,
		    Nil,minusn(3,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)),interval_ago,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L))));
    }
    else
	result_qm = Nil;
    return_value_qm = Nil;
    if (result_qm)
	return_value_qm = make_evaluation_quantity(result_qm);
    else if ( !TRUEP(variable_or_parameter_qm))
	return_value_qm = Nil;
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_70,
		variable_or_parameter_qm,interval_ago,Qseconds);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    reclaim_evaluation_quantity(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)2L));
    evaluation_truth_value = ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack)));
    if ( !(EQ(evaluation_truth_value,Evaluation_true_value) || 
	    EQ(evaluation_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(evaluation_truth_value);
    evaluation_truth_value = ISVREF(local_stack,IFIX(top_of_stack));
    if ( !(EQ(evaluation_truth_value,Evaluation_true_value) || 
	    EQ(evaluation_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(evaluation_truth_value);
    top_of_stack_new_value = IFIX(top_of_stack) - (SI_Long)3L;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object string_constant_71;  /* "The distance between ~NF and ~NF could not be computed, ~
				    *    since they were not on the same workspace."
				    */

/* ITEM-DISTANCE-EVAL-ERROR-MESSAGE */
Object item_distance_eval_error_message(item1,item2)
    Object item1, item2;
{
    x_note_fn_call(207,181);
    return tformat_stack_error_text_string(3,string_constant_71,item1,item2);
}

static Object string_constant_72;  /* "Could not locate a non-active item of type ~a." */

/* NO-ITEM-OF-CLASS-EVAL-ERROR-MESSAGE */
Object no_item_of_class_eval_error_message(class_1)
    Object class_1;
{
    x_note_fn_call(207,182);
    return tformat_stack_error_text_string(2,string_constant_72,class_1);
}

static Object Qinference_engine;   /* inference-engine */

static Object float_constant;      /* 1.0 */

/* EVAL-DISTANCE-BETWEEN-AND-THE-NEAREST-FUNCALLED */
Object eval_distance_between_and_the_nearest_funcalled(item,class_1)
    Object item, class_1;
{
    Object class_name, class_description_qm, result_float, closest_instance_qm;
    Object temp, amf_available_array_cons_qm, amf_array, temp_1, temp_2;
    Object amf_result, new_float;
    double aref_new_value;

    x_note_fn_call(207,183);
    class_name = class_1;
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    result_float = Nil;
    closest_instance_qm = class_description_qm && 
	    ISVREF(class_description_qm,(SI_Long)16L) ? 
	    find_nearest_active_instance_of_class_to_entity(class_description_qm,
	    item) : Nil;
    if (closest_instance_qm)
	result_float = 
		distance_between_icons_if_in_same_workspace(closest_instance_qm,
		item);
    else if (EQ(Current_environment,Qinference_engine)) {
	Stack_expiration = Nil;
	result_float = float_constant;
    }
    else {
	temp = Cached_top_of_stack;
	result_float = raw_stack_error_named_error(temp,
		no_item_of_class_eval_error_message(class_name));
    }
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp_1 = Vector_of_simple_float_array_pools;
	temp_2 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_float_array_conses_tail_vector,
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
    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(result_float);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* DISTANCE-BETWEEN-ICONS-IF-IN-SAME-WORKSPACE */
Object distance_between_icons_if_in_same_workspace(entity1,entity2)
    Object entity1, entity2;
{
    Object workspace_qm, temp;
    double delta_x, delta_y;

    x_note_fn_call(207,184);
    workspace_qm = get_workspace_if_any(entity1);
    if (workspace_qm && EQ(workspace_qm,get_workspace_if_any(entity2))) {
	temp = item_x_position(entity1);
	delta_x = (double)IFIX(FIXNUM_MINUS(temp,item_x_position(entity2)));
	temp = item_y_position(entity1);
	delta_y = (double)IFIX(FIXNUM_MINUS(temp,item_y_position(entity2)));
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(sqrt(delta_x * delta_x + 
		delta_y * delta_y)));
    }
    else
	return VALUES_1(Nil);
}

static Object Qhas_a_current_value;  /* has-a-current-value */

/* HAS-A-CURRENT-VALUE-STACK-NODE-CONVERTER */
Object has_a_current_value_stack_node_converter(expression)
    Object expression;
{
    Object arguments, gensymed_symbol, stack_node_instruction;

    x_note_fn_call(207,185);
    arguments = 
	    stack_cons_1(convert_expression_to_stack_node_tree(SECOND(expression)),
	    Nil);
    gensymed_symbol = make_stack_node_instruction_1_1(Qhas_a_current_value,
	    Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    stack_node_instruction = gensymed_symbol;
    SVREF(stack_node_instruction,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(stack_node_instruction);
    return VALUES_1(Nil);
}

static Object list_constant_9;     /* # */

/* HAS-A-CURRENT-VALUE-I-CHOOSER */
Object has_a_current_value_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_nodes, unknown_allowed_qm, temp, temp_1;

    x_note_fn_call(207,186);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    temp = choose_stack_node_instructions_and_types(2,CAR(argument_nodes),
	    list_constant_9);
    M_CAR(argument_nodes) = temp;
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = Qboolean;
    if (type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_nodes),(SI_Long)6L))) {
	if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	    temp_1 = generate_new_stack_frame_var_spot(Qtruth_value);
	    temp = phrase_list_2(temp_1,unknown_allowed_qm ? 
		    generate_new_stack_frame_var_spot(Qdatum) : Nil);
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* HAS-A-CURRENT-VALUE-I-EMIT */
Object has_a_current_value_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object surrounding_data_seeking_cache_var_qm, previous_expiration_cache_qm;
    Object argument_nodes, value_could_be_unknown_qm, known_value_tag_qm;
    Object has_a_value_tag, end_of_expression_tag;

    x_note_fn_call(207,187);
    surrounding_data_seeking_cache_var_qm = CAR(extra_info);
    previous_expiration_cache_qm = SECOND(extra_info);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    value_could_be_unknown_qm = type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_nodes),(SI_Long)6L));
    known_value_tag_qm = value_could_be_unknown_qm ? 
	    generate_new_goto_tag() : Qnil;
    has_a_value_tag = generate_new_goto_tag();
    end_of_expression_tag = generate_new_goto_tag();
    if (value_could_be_unknown_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)82L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
	if (previous_expiration_cache_qm) {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		    previous_expiration_cache_qm);
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	}
	emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
	emit_branch_long_if_known_byte_codes(byte_code_stream,
		known_value_tag_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	if (previous_expiration_cache_qm) {
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    previous_expiration_cache_qm);
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	}
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	emit_branch_long_byte_codes(byte_code_stream,end_of_expression_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		known_value_tag_qm);
	if (previous_expiration_cache_qm) {
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    previous_expiration_cache_qm);
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	}
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)96L));
	emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		has_a_value_tag);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	emit_branch_long_byte_codes(byte_code_stream,end_of_expression_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,has_a_value_tag);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		end_of_expression_tag);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
    }
    else {
	emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)96L));
	emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		has_a_value_tag);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	emit_branch_long_byte_codes(byte_code_stream,end_of_expression_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,has_a_value_tag);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		end_of_expression_tag);
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* HAS-NO-CURRENT-VALUE-STACK-NODE-CONVERTER */
Object has_no_current_value_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(207,188);
    GENSYM_RETURN_ONE(convert_expression_to_stack_node_tree(phrase_list_2(Qnot,
	    phrase_cons(Qhas_a_current_value,CDR(expression)))));
    return VALUES_1(Nil);
}

static Object Qhas_a_value;        /* has-a-value */

/* HAS-A-VALUE-STACK-NODE-CONVERTER */
Object has_a_value_stack_node_converter(expression)
    Object expression;
{
    Object arguments, gensymed_symbol, stack_node_instruction;

    x_note_fn_call(207,189);
    arguments = 
	    stack_cons_1(convert_expression_to_stack_node_tree(SECOND(expression)),
	    Nil);
    gensymed_symbol = make_stack_node_instruction_1_1(Qhas_a_value,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    stack_node_instruction = gensymed_symbol;
    SVREF(stack_node_instruction,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(stack_node_instruction);
    return VALUES_1(Nil);
}

static Object string_constant_73;  /* "The HAS A VALUE expression can only be executed in contexts where ~
				    *          unknown can be returned, such as within a rule or a COLLECT DATA ~
				    *          statement in procedures.  The HAS A CURRENT VALUE expression does not ~
				    * ? have this restriction and could be used here."
				    */

/* HAS-A-VALUE-I-CHOOSER */
Object has_a_value_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_nodes, temp;
    Object no_item_implies_unknown_allowed_qm, argument_could_be_unknown_qm;
    Object temp_1;

    x_note_fn_call(207,190);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if ( !TRUEP(type_specification_subtype_p(list_constant,required_type)))
	compiler_error(1,string_constant_73);
    temp = choose_stack_node_instructions_and_types(2,CAR(argument_nodes),
	    list_constant_9);
    M_CAR(argument_nodes) = temp;
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_1,required_type);
    argument_could_be_unknown_qm = 
	    type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_nodes),(SI_Long)6L));
    temp_1 = argument_could_be_unknown_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_unknown(Qboolean,temp_1);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    if (argument_could_be_unknown_qm) {
	if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	    temp_1 = generate_new_stack_frame_var_spot(Qtruth_value);
	    temp = phrase_list_2(temp_1,
		    generate_new_stack_frame_var_spot(Qdatum));
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* HAS-A-VALUE-I-EMIT */
Object has_a_value_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object surrounding_data_seeking_cache_var_qm, previous_expiration_cache_qm;
    Object argument_nodes, has_a_value_tag, end_of_expression_tag;

    x_note_fn_call(207,191);
    surrounding_data_seeking_cache_var_qm = CAR(extra_info);
    previous_expiration_cache_qm = SECOND(extra_info);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (surrounding_data_seeking_cache_var_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)82L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)118L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		previous_expiration_cache_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)90L));
	emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
	emit_funcall_instruction_byte_codes(2,byte_code_stream,Qhas_a_value);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		previous_expiration_cache_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
    }
    else {
	has_a_value_tag = generate_new_goto_tag();
	end_of_expression_tag = generate_new_goto_tag();
	emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)96L));
	emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		has_a_value_tag);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	emit_branch_long_byte_codes(byte_code_stream,end_of_expression_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,has_a_value_tag);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		end_of_expression_tag);
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qnever;              /* never */

/* FUNCALL-HAS-A-VALUE-INST */
Object funcall_has_a_value_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object wake_ups_count, new_wake_ups_count, value_qm, result_1;
    Object variable_cons, count_1, end_count, ab_loop_it_, variable, thing;
    Object svref_new_value;
    char temp;

    x_note_fn_call(207,192);
    wake_ups_count = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
    new_wake_ups_count = length(Variables_that_did_not_have_values);
    value_qm = ISVREF(local_stack,IFIX(top_of_stack));
    if (Stack_expiration)
	result_1 = value_qm && evaluation_value_value(value_qm) ? Truth : 
		Falsity;
    else {
	temp = (IFIX(Current_computation_flags) & (SI_Long)2L) != (SI_Long)0L;
	if (temp);
	else
	    temp = FIXNUM_LE(new_wake_ups_count,wake_ups_count);
	if (temp);
	else {
	    variable_cons = Variables_that_did_not_have_values;
	    count_1 = FIX((SI_Long)1L);
	    end_count = FIXNUM_MINUS(new_wake_ups_count,wake_ups_count);
	    ab_loop_it_ = Nil;
	  next_loop:
	    if (FIXNUM_GT(count_1,end_count))
		goto end_loop;
	    variable = CAR(variable_cons);
	    ab_loop_it_ = (SI_Long)0L != (IFIX(ISVREF(variable,
		    (SI_Long)5L)) & (SI_Long)32L) ? T : Nil;
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    variable_cons = CDR(variable_cons);
	    count_1 = FIXNUM_ADD1(count_1);
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(Qnil);
	  end_1:;
	}
	if (temp) {
	    Stack_expiration = Qnever;
	    result_1 = Falsity;
	}
	else {
	    Stack_expiration = Nil;
	    result_1 = Falsity;
	}
    }
    thing = ISVREF(local_stack,IFIX(top_of_stack));
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    top_of_stack = FIXNUM_SUB1(top_of_stack);
    if (FIXNUM_EQ(result_1,Truth))
	svref_new_value = Evaluation_true_value;
    else if (FIXNUM_EQ(result_1,Falsity))
	svref_new_value = Evaluation_false_value;
    else
	svref_new_value = eval_cons_1(result_1,Qtruth_value);
    SVREF(local_stack,top_of_stack) = svref_new_value;
    return VALUES_1(Nil);
}

/* HAS-NO-VALUE-STACK-NODE-CONVERTER */
Object has_no_value_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(207,193);
    GENSYM_RETURN_ONE(convert_expression_to_stack_node_tree(phrase_list_2(Qnot,
	    phrase_cons(Qhas_a_value,CDR(expression)))));
    return VALUES_1(Nil);
}

static Object Qcurrent_value_of;   /* current-value-of */

/* CURRENT-VALUE-OF-STACK-NODE-CONVERTER */
Object current_value_of_stack_node_converter(expression)
    Object expression;
{
    Object arguments, gensymed_symbol, stack_node_instruction;

    x_note_fn_call(207,194);
    arguments = 
	    stack_cons_1(convert_expression_to_stack_node_tree(SECOND(expression)),
	    Nil);
    gensymed_symbol = make_stack_node_instruction_1_1(Qcurrent_value_of,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    stack_node_instruction = gensymed_symbol;
    SVREF(stack_node_instruction,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(stack_node_instruction);
    return VALUES_1(Nil);
}

static Object list_constant_10;    /* # */

/* CURRENT-VALUE-OF-I-CHOOSER */
Object current_value_of_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_nodes, no_item_allowed_qm;
    Object unknown_allowed_qm, temp;

    x_note_fn_call(207,195);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    temp = choose_stack_node_instructions_and_types(2,CAR(argument_nodes),
	    type_specification_subtype_p(required_type,list_constant_10) ? 
	    required_type : maybe_add_unknown(maybe_add_no_item(Qdatum,
	    no_item_allowed_qm),unknown_allowed_qm));
    M_CAR(argument_nodes) = temp;
    temp = ISVREF(CAR(argument_nodes),(SI_Long)6L);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    if (type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_nodes),(SI_Long)6L)) && unknown_allowed_qm) {
	if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	    temp = 
		    phrase_cons(generate_new_stack_frame_var_spot(Qtruth_value),
		    Nil);
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    else
	SVREF(stack_node_instruction,FIX((SI_Long)12L)) = Nil;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CURRENT-VALUE-OF-I-EMIT */
Object current_value_of_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object surrounding_data_seeking_cache_var_qm, argument_nodes;

    x_note_fn_call(207,196);
    surrounding_data_seeking_cache_var_qm = CAR(extra_info);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (surrounding_data_seeking_cache_var_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)82L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
	emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
    }
    else
	emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qvalue_of;           /* value-of */

/* VALUE-OF-STACK-NODE-CONVERTER */
Object value_of_stack_node_converter(expression)
    Object expression;
{
    Object arguments, gensymed_symbol, stack_node_instruction;

    x_note_fn_call(207,197);
    arguments = 
	    stack_cons_1(convert_expression_to_stack_node_tree(SECOND(expression)),
	    Nil);
    gensymed_symbol = make_stack_node_instruction_1_1(Qvalue_of,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    stack_node_instruction = gensymed_symbol;
    SVREF(stack_node_instruction,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(stack_node_instruction);
    return VALUES_1(Nil);
}

/* VALUE-OF-I-CHOOSER */
Object value_of_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_nodes, unknown_allowed_qm;
    Object no_item_allowed_qm, temp;

    x_note_fn_call(207,198);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    temp = choose_stack_node_instructions_and_types(2,CAR(argument_nodes),
	    type_specification_subtype_p(required_type,list_constant_10) ? 
	    required_type : maybe_add_unknown(maybe_add_no_item(Qdatum,
	    no_item_allowed_qm),unknown_allowed_qm));
    M_CAR(argument_nodes) = temp;
    temp = ISVREF(CAR(argument_nodes),(SI_Long)6L);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    if (type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_nodes),(SI_Long)6L)) && unknown_allowed_qm) {
	if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	    temp = 
		    phrase_cons(generate_new_stack_frame_var_spot(Qtruth_value),
		    Nil);
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    else
	SVREF(stack_node_instruction,FIX((SI_Long)12L)) = Nil;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* VALUE-OF-I-EMIT */
Object value_of_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object surrounding_data_seeking_cache_var_qm, argument_nodes;

    x_note_fn_call(207,199);
    surrounding_data_seeking_cache_var_qm = CAR(extra_info);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (surrounding_data_seeking_cache_var_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)82L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)118L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
	emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
    }
    else
	emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qfirst_that_has_a_current_value;  /* first-that-has-a-current-value */

/* FIRST-THAT-HAS-A-CURRENT-VALUE-STACK-NODE-CONVERTER */
Object first_that_has_a_current_value_stack_node_converter(expression)
    Object expression;
{
    Object argument, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object arguments, gensymed_symbol, instruction_node;

    x_note_fn_call(207,200);
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    arguments = ab_loopvar_;
    goto end_1;
    arguments = Qnil;
  end_1:;
    gensymed_symbol = 
	    make_stack_node_instruction_1_1(Qfirst_that_has_a_current_value,
	    Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    SVREF(instruction_node,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

static Object list_constant_11;    /* # */

static Object string_constant_74;  /* "~a ~a" */

static Object string_constant_75;  /* "The last expression within the FIRST OF THE FOLLOWING EXPRESSIONS " */

static Object string_constant_76;  /* "THAT HAS A CURRENT VALUE must not produce an unknown value." */

/* FIRST-THAT-HAS-A-CURRENT-VALUE-I-CHOOSER */
Object first_that_has_a_current_value_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_nodes, primary_argument_required_type;
    Object primary_value_type, unknown_allowed_qm, unknown_argument_qm;
    Object unknown_last_argument_qm, but_last_argument_type;
    Object last_argument_type, argument_type, argument_node_cons, temp, temp_1;

    x_note_fn_call(207,201);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    primary_argument_required_type = 
	    primary_type_of_type_specification(required_type);
    primary_value_type = Nil;
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    unknown_argument_qm = Nil;
    unknown_last_argument_qm = Nil;
    if ( 
	    !TRUEP(type_specification_subtype_p(primary_argument_required_type,
	    Qdatum)))
	primary_argument_required_type = Qdatum;
    but_last_argument_type = 
	    make_type_specification_union(primary_argument_required_type,
	    list_constant_11);
    last_argument_type = 
	    make_type_specification_union(primary_argument_required_type,
	    list_constant_11);
    argument_type = Nil;
    argument_node_cons = argument_nodes;
  next_loop:
    if ( !TRUEP(argument_node_cons))
	goto end_loop;
    temp = choose_stack_node_instructions_and_types(2,
	    CAR(argument_node_cons),CDR(argument_node_cons) ? 
	    but_last_argument_type : last_argument_type);
    M_CAR(argument_node_cons) = temp;
    argument_type = ISVREF(CAR(argument_node_cons),(SI_Long)6L);
    primary_value_type = most_general_primary_type(argument_type,
	    primary_value_type);
    if (type_specification_subtype_p(list_constant,argument_type)) {
	unknown_argument_qm = T;
	if ( !TRUEP(CDR(argument_node_cons)))
	    unknown_last_argument_qm = T;
    }
    argument_node_cons = M_CDR(argument_node_cons);
    goto next_loop;
  end_loop:
    if (unknown_last_argument_qm &&  !TRUEP(unknown_allowed_qm))
	compiler_error(3,string_constant_74,string_constant_75,
		string_constant_76);
    if (unknown_argument_qm) {
	temp = make_type_specification_union(primary_value_type,list_constant);
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
	if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	    temp_1 = generate_new_stack_frame_var_spot(Qdatum);
	    temp = phrase_list_2(temp_1,
		    generate_new_stack_frame_var_spot(Qdatum));
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    else {
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = primary_value_type;
	if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	    temp_1 = generate_new_stack_frame_var_spot(Qdatum);
	    temp = phrase_list_2(temp_1,
		    generate_new_stack_frame_var_spot(Qdatum));
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MOST-GENERAL-PRIMARY-TYPE */
Object most_general_primary_type(argument_type,type_qm)
    Object argument_type, type_qm;
{
    Object primary_argument_type, primary_value_type;

    x_note_fn_call(207,202);
    primary_argument_type = primary_type_of_type_specification(argument_type);
    primary_value_type = type_qm ? 
	    primary_type_of_type_specification(type_qm) : Qnil;
    if ( !TRUEP(primary_value_type) || 
	    type_specification_subtype_p(primary_value_type,
	    primary_argument_type))
	primary_value_type = primary_argument_type;
    else if (type_specification_subtype_p(primary_argument_type,
	    primary_value_type));
    else
	primary_value_type = Qdatum;
    return VALUES_1(primary_value_type);
}

/* FIRST-THAT-HAS-A-CURRENT-VALUE-I-EMIT */
Object first_that_has_a_current_value_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, surrounding_data_seeking_cache_var_qm;
    Object global_expiration_cache_var_qm, end_of_instruction_tag;
    Object argument_node_cons, argument_node, known_value_tag, next_value_tag;

    x_note_fn_call(207,203);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    surrounding_data_seeking_cache_var_qm = CAR(extra_info);
    global_expiration_cache_var_qm = SECOND(extra_info);
    if (T) {
	end_of_instruction_tag = generate_new_goto_tag();
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)82L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		global_expiration_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	argument_node_cons = argument_nodes;
	argument_node = Nil;
	known_value_tag = Nil;
	next_value_tag = Nil;
      next_loop:
	if ( !TRUEP(argument_node_cons))
	    goto end_loop;
	argument_node = FIRST(argument_node_cons);
	known_value_tag = generate_new_goto_tag();
	next_value_tag = generate_new_goto_tag();
	emit_stack_node_tree(byte_code_stream,argument_node);
	emit_branch_long_if_known_byte_codes(byte_code_stream,known_value_tag);
	emit_branch_long_byte_codes(byte_code_stream,next_value_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,known_value_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)96L));
	emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		end_of_instruction_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,next_value_tag);
	if (CDR(argument_node_cons)) {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	}
	argument_node_cons = M_CDR(argument_node_cons);
	goto next_loop;
      end_loop:;
	register_tag_in_byte_code_stream(2,byte_code_stream,
		end_of_instruction_tag);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		global_expiration_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qfirst_that_has_a_value;  /* first-that-has-a-value */

/* FIRST-THAT-HAS-A-VALUE-STACK-NODE-CONVERTER */
Object first_that_has_a_value_stack_node_converter(expression)
    Object expression;
{
    Object argument, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object arguments, gensymed_symbol, instruction_node;

    x_note_fn_call(207,204);
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    arguments = ab_loopvar_;
    goto end_1;
    arguments = Qnil;
  end_1:;
    gensymed_symbol = 
	    make_stack_node_instruction_1_1(Qfirst_that_has_a_value,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    SVREF(instruction_node,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

static Object string_constant_77;  /* "The FIRST OF THE FOLLOWING EXPRESSIONS THAT HAS A VALUE expression ~
				    *          can only be executed in contexts where ~
				    *          unknown can be returned, such as within a rule or a COLLECT DATA ~
				    *          statement in procedures.  The HAS A CURRENT VALUE form of this ~
				    *          expression does not have this restriction and could be used here."
				    */

static Object list_constant_12;    /* # */

/* FIRST-THAT-HAS-A-VALUE-I-CHOOSER */
Object first_that_has_a_value_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_nodes, primary_argument_required_type;
    Object primary_value_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object unknown_argument_qm, but_last_argument_type, last_argument_type;
    Object argument_type, argument_node_cons, temp, temp_1, temp_2;

    x_note_fn_call(207,205);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    primary_argument_required_type = 
	    primary_type_of_type_specification(required_type);
    primary_value_type = Nil;
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = unknown_allowed_qm;
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    unknown_argument_qm = Nil;
    if ( !TRUEP(type_specification_subtype_p(list_constant,required_type)))
	compiler_error(1,string_constant_77);
    if ( 
	    !TRUEP(type_specification_subtype_p(primary_argument_required_type,
	    Qdatum)))
	primary_argument_required_type = Qdatum;
    but_last_argument_type = 
	    make_type_specification_union(primary_argument_required_type,
	    list_constant_12);
    last_argument_type = 
	    maybe_add_unknown(maybe_add_no_item_implies_unknown(maybe_add_no_item(primary_argument_required_type,
	    no_item_allowed_qm),unknown_allowed_qm),
	    no_item_implies_unknown_allowed_qm);
    argument_type = Nil;
    argument_node_cons = argument_nodes;
  next_loop:
    if ( !TRUEP(argument_node_cons))
	goto end_loop;
    temp = choose_stack_node_instructions_and_types(2,
	    CAR(argument_node_cons),CDR(argument_node_cons) ? 
	    but_last_argument_type : last_argument_type);
    M_CAR(argument_node_cons) = temp;
    argument_type = ISVREF(CAR(argument_node_cons),(SI_Long)6L);
    primary_value_type = most_general_primary_type(argument_type,
	    primary_value_type);
    if (type_specification_subtype_p(list_constant,argument_type))
	unknown_argument_qm = T;
    argument_node_cons = M_CDR(argument_node_cons);
    goto next_loop;
  end_loop:;
    if (unknown_argument_qm) {
	temp = make_type_specification_union(primary_value_type,list_constant);
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
	if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	    temp_1 = generate_new_stack_frame_var_spot(Qdatum);
	    temp_2 = generate_new_stack_frame_var_spot(Qdatum);
	    temp = phrase_list_3(temp_1,temp_2,
		    generate_new_stack_frame_var_spot(Qdatum));
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    else {
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = primary_value_type;
	if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	    temp_1 = generate_new_stack_frame_var_spot(Qdatum);
	    temp_2 = generate_new_stack_frame_var_spot(Qdatum);
	    temp = phrase_list_3(temp_1,temp_2,
		    generate_new_stack_frame_var_spot(Qdatum));
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* FIRST-THAT-HAS-A-VALUE-I-EMIT */
Object first_that_has_a_value_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, surrounding_data_seeking_cache_var_qm;
    Object global_expiration_cache_var_qm;
    Object previous_expression_could_supply_value_var_qm;
    Object end_of_instruction_tag, argument_node_cons, argument_node;
    Object test_if_known_tag, known_value_tag, next_argument_tag;

    x_note_fn_call(207,206);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    surrounding_data_seeking_cache_var_qm = CAR(extra_info);
    global_expiration_cache_var_qm = SECOND(extra_info);
    previous_expression_could_supply_value_var_qm = THIRD(extra_info);
    if (T) {
	end_of_instruction_tag = generate_new_goto_tag();
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)82L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)118L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		previous_expression_could_supply_value_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		global_expiration_cache_var_qm);
	argument_node_cons = argument_nodes;
	argument_node = Nil;
	test_if_known_tag = Nil;
	known_value_tag = Nil;
	next_argument_tag = Nil;
      next_loop:
	if ( !TRUEP(argument_node_cons))
	    goto end_loop;
	argument_node = FIRST(argument_node_cons);
	test_if_known_tag = generate_new_goto_tag();
	known_value_tag = generate_new_goto_tag();
	next_argument_tag = generate_new_goto_tag();
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)90L));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		previous_expression_could_supply_value_var_qm);
	emit_stack_node_tree(byte_code_stream,argument_node);
	emit_funcall_instruction_byte_codes(2,byte_code_stream,
		Qfirst_that_has_a_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		previous_expression_could_supply_value_var_qm);
	emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		test_if_known_tag);
	if (CDR(argument_node_cons))
	    emit_branch_long_byte_codes(byte_code_stream,next_argument_tag);
	else {
	    emit_push_constant_byte_codes(byte_code_stream,Nil);
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)22L));
	    emit_branch_long_byte_codes(byte_code_stream,
		    end_of_instruction_tag);
	}
	register_tag_in_byte_code_stream(2,byte_code_stream,test_if_known_tag);
	emit_branch_long_if_known_byte_codes(byte_code_stream,known_value_tag);
	emit_branch_long_byte_codes(byte_code_stream,next_argument_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,known_value_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)96L));
	emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		end_of_instruction_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,next_argument_tag);
	if (CDR(argument_node_cons))
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	argument_node_cons = M_CDR(argument_node_cons);
	goto next_loop;
      end_loop:;
	register_tag_in_byte_code_stream(2,byte_code_stream,
		end_of_instruction_tag);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		global_expiration_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		surrounding_data_seeking_cache_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* FUNCALL-FIRST-THAT-HAS-A-VALUE-INST */
Object funcall_first_that_has_a_value_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object wake_ups_count, stack_arg_1, previous_expression_could_supply_value;
    Object value_qm, new_wake_ups_count, variable_cons, count_1, end_count;
    Object ab_loop_it_, variable, svref_arg_2_1, svref_new_value;
    SI_Long svref_arg_2;
    char temp;

    x_note_fn_call(207,207);
    wake_ups_count = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)2L);
    stack_arg_1 = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
    previous_expression_could_supply_value = M_CAR(stack_arg_1);
    value_qm = ISVREF(local_stack,IFIX(top_of_stack));
    new_wake_ups_count = length(Variables_that_did_not_have_values);
    if ( !TRUEP(Stack_expiration)) {
	temp = FIXNUM_EQ(previous_expression_could_supply_value,Truth);
	if (temp);
	else
	    temp = (IFIX(Current_computation_flags) & (SI_Long)2L) != 
		    (SI_Long)0L;
	if (temp);
	else
	    temp = FIXNUM_LE(new_wake_ups_count,wake_ups_count);
	if (temp);
	else {
	    variable_cons = Variables_that_did_not_have_values;
	    count_1 = FIX((SI_Long)1L);
	    end_count = FIXNUM_MINUS(new_wake_ups_count,wake_ups_count);
	    ab_loop_it_ = Nil;
	  next_loop:
	    if (FIXNUM_GT(count_1,end_count))
		goto end_loop;
	    variable = CAR(variable_cons);
	    ab_loop_it_ = (SI_Long)0L != (IFIX(ISVREF(variable,
		    (SI_Long)5L)) & (SI_Long)32L) ? T : Nil;
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    variable_cons = CDR(variable_cons);
	    count_1 = FIXNUM_ADD1(count_1);
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(Qnil);
	  end_1:;
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	previous_expression_could_supply_value = Truth;
    if ( !(EQ(stack_arg_1,Evaluation_true_value) || EQ(stack_arg_1,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(stack_arg_1);
    svref_arg_2 = IFIX(top_of_stack) - (SI_Long)2L;
    ISVREF(local_stack,svref_arg_2) = value_qm;
    svref_arg_2_1 = FIXNUM_SUB1(top_of_stack);
    if (FIXNUM_EQ(previous_expression_could_supply_value,Truth))
	svref_new_value = Evaluation_true_value;
    else if (FIXNUM_EQ(previous_expression_could_supply_value,Falsity))
	svref_new_value = Evaluation_false_value;
    else
	svref_new_value = 
		eval_cons_1(previous_expression_could_supply_value,
		Qtruth_value);
    SVREF(local_stack,svref_arg_2_1) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qsimulated_value_of;  /* simulated-value-of */

/* SIMULATED-VALUE-OF-STACK-NODE-CONVERTER */
Object simulated_value_of_stack_node_converter(expression)
    Object expression;
{
    Object arguments, gensymed_symbol, stack_node_instruction;

    x_note_fn_call(207,208);
    arguments = 
	    stack_cons_1(convert_expression_to_stack_node_tree(SECOND(expression)),
	    Nil);
    gensymed_symbol = make_stack_node_instruction_1_1(Qsimulated_value_of,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    stack_node_instruction = gensymed_symbol;
    SVREF(stack_node_instruction,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(stack_node_instruction);
    return VALUES_1(Nil);
}

/* SIMULATED-VALUE-OF-I-CHOOSER */
Object simulated_value_of_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_nodes, primary_argument_required_type;
    Object unknown_allowed_qm, no_item_allowed_qm, temp;

    x_note_fn_call(207,209);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    primary_argument_required_type = 
	    primary_type_of_type_specification(required_type);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_7,
	    required_type);
    if ( 
	    !TRUEP(type_specification_subtype_p(primary_argument_required_type,
	    Qdatum)))
	primary_argument_required_type = Qdatum;
    temp = choose_stack_node_instructions_and_types(2,CAR(argument_nodes),
	    maybe_add_unknown(maybe_add_no_item(primary_argument_required_type,
	    no_item_allowed_qm),unknown_allowed_qm));
    M_CAR(argument_nodes) = temp;
    temp = ISVREF(CAR(argument_nodes),(SI_Long)6L);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    if ( !TRUEP(ISVREF(stack_node_instruction,(SI_Long)12L))) {
	temp = phrase_cons(generate_new_stack_frame_var_spot(Qsymbol),Nil);
	SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SIMULATED-VALUE-OF-I-EMIT */
Object simulated_value_of_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object temp;

    x_note_fn_call(207,210);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)104L));
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    FIRST(extra_info));
    emit_push_constant_byte_codes(byte_code_stream,Qsimulated_value);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)105L));
    temp = ISVREF(stack_node_instruction,(SI_Long)2L);
    emit_stack_node_tree(byte_code_stream,FIRST(temp));
    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
	    FIRST(extra_info));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)105L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

void stack_eval1_INIT()
{
    Object float_contagion_stack_operators_new_value;
    Object quote_stack_node_converter_1, let_stack_node_converter_1;
    Object let_i_chooser_1, let_i_emit_1, format_form_stack_node_converter_1;
    Object format_form_i_chooser_1, format_form_i_emit_1;
    Object is_stack_node_converter_1, is_i_chooser_1, is_i_emit_1;
    Object is_not_stack_node_converter_1, and_stack_node_converter_1;
    Object and_i_chooser_1, and_i_emit_1, or_stack_node_converter_1;
    Object or_i_chooser_1, or_i_emit_1, not_stack_node_converter_1;
    Object not_i_chooser_1, not_i_emit_1, if_expression_stack_node_converter_1;
    Object if_expression_i_chooser_1, if_expression_i_emit_1;
    Object average_value_stack_node_converter_1, average_value_1_i_chooser_1;
    Object average_value_2_i_chooser_1, average_value_1_i_emit_1;
    Object average_value_2_i_emit_1, sum_of_values_stack_node_converter_1;
    Object sum_of_values_1_i_chooser_1, sum_of_values_2_i_chooser_1;
    Object sum_of_values_1_i_emit_1, sum_of_values_2_i_emit_1;
    Object minimum_value_stack_node_converter_1, minimum_value_1_i_chooser_1;
    Object minimum_value_2_i_chooser_1, minimum_value_1_i_emit_1;
    Object minimum_value_2_i_emit_1, maximum_value_stack_node_converter_1;
    Object maximum_value_1_i_chooser_1, maximum_value_2_i_chooser_1;
    Object maximum_value_1_i_emit_1, maximum_value_2_i_emit_1;
    Object standard_deviation_stack_node_converter_1;
    Object standard_deviation_1_i_chooser_1, standard_deviation_2_i_chooser_1;
    Object standard_deviation_1_i_emit_1, standard_deviation_2_i_emit_1;
    Object number_of_datapoints_stack_node_converter_1;
    Object number_of_datapoints_0_i_chooser_1;
    Object number_of_datapoints_1_i_chooser_1;
    Object number_of_datapoints_2_i_chooser_1, number_of_datapoints_0_i_emit_1;
    Object number_of_datapoints_1_i_emit_1, number_of_datapoints_2_i_emit_1;
    Object rate_of_change_stack_node_converter_1, rate_of_change_1_i_chooser_1;
    Object rate_of_change_2_i_chooser_1, rate_of_change_1_i_emit_1;
    Object rate_of_change_2_i_emit_1, integral_stack_node_converter_1;
    Object integral_1_i_chooser_1, integral_2_i_chooser_1, integral_1_i_emit_1;
    Object integral_2_i_emit_1, historic_value_stack_node_converter_1;
    Object historic_value_i_chooser_1, historic_value_i_emit_1;
    Object value_of_previous_datapoint_stack_node_converter_1;
    Object value_of_previous_datapoint_i_chooser_1;
    Object value_of_previous_datapoint_i_emit_1;
    Object interpolated_value_stack_node_converter_1;
    Object interpolated_value_i_chooser_1, interpolated_value_i_emit_1;
    Object has_a_current_value_stack_node_converter_1;
    Object has_a_current_value_i_chooser_1, has_a_current_value_i_emit_1;
    Object has_no_current_value_stack_node_converter_1;
    Object has_a_value_stack_node_converter_1, has_a_value_i_chooser_1;
    Object has_a_value_i_emit_1, has_no_value_stack_node_converter_1;
    Object current_value_of_stack_node_converter_1;
    Object current_value_of_i_chooser_1, current_value_of_i_emit_1;
    Object value_of_stack_node_converter_1, value_of_i_chooser_1;
    Object value_of_i_emit_1;
    Object first_that_has_a_current_value_stack_node_converter_1;
    Object first_that_has_a_current_value_i_chooser_1;
    Object first_that_has_a_current_value_i_emit_1;
    Object first_that_has_a_value_stack_node_converter_1;
    Object first_that_has_a_value_i_chooser_1, first_that_has_a_value_i_emit_1;
    Object simulated_value_of_stack_node_converter_1;
    Object simulated_value_of_i_chooser_1, simulated_value_of_i_emit_1;
    Object Qcount_datapoints_that_evaluate_true_with_eventflag;
    Object Qpprint_functional_evaluator;
    Object Qeval_count_datapoints_that_evaluate_true_with_eventflag_in_line;
    Object list_constant_42, Qall, AB_package, list_constant_15;
    Object list_constant_40, Qcount_datapoints_that_evaluate_true;
    Object Qeval_count_datapoints_that_evaluate_true_in_line, list_constant_41;
    Object list_constant_26, Qquantitative_parameter, Qab_class;
    Object Qstack_node_instruction_emitter, Qpreferred_instruction_chooser;
    Object Qstack_special_form_converter, Qexpiration_special_form_operator_p;
    Object Qfuncall_first_that_has_a_value_inst;
    Object Qpprint_first_that_has_a_value_instruction, list_constant_23;
    Object list_constant_39, list_constant_38, list_constant_37, Qhas_no_value;
    Object Qfuncall_has_a_value_inst, Qpprint_has_a_value_instruction;
    Object Qhas_no_current_value;
    Object Qeval_distance_between_and_the_nearest_funcalled;
    Object Qpprint_distance_between_and_the_nearest_evaluator;
    Object list_constant_36, Qdistance_between_and_the_nearest;
    Object list_constant_35, list_constant_32, Qexpiration_source_operator_p;
    Object Qpprint_distance_between_evaluator, Qeval_distance_between_in_line;
    Object list_constant_33, Qdistance_between;
    Object Qfuncall_interpolated_value_inst;
    Object Qpprint_interpolated_value_instruction, Qis_nan;
    Object Qeval_is_nan_in_line, list_constant_20;
    Object Qfuncall_value_of_previous_datapoint_inst;
    Object Qpprint_value_of_previous_datapoint_instruction;
    Object Qfuncall_historic_value_inst, Qpprint_historic_value_instruction;
    Object Qfuncall_integral_2_inst, Qpprint_integral_2_instruction;
    Object Qfuncall_integral_1_inst, Qpprint_integral_1_instruction;
    Object Qfuncall_rate_of_change_2_inst;
    Object Qpprint_rate_of_change_2_instruction;
    Object Qfuncall_rate_of_change_1_inst;
    Object Qpprint_rate_of_change_1_instruction;
    Object Qfuncall_number_of_datapoints_2_inst;
    Object Qpprint_number_of_datapoints_2_instruction;
    Object Qfuncall_number_of_datapoints_1_inst;
    Object Qpprint_number_of_datapoints_1_instruction;
    Object Qfuncall_number_of_datapoints_0_inst;
    Object Qpprint_number_of_datapoints_0_instruction;
    Object Qfuncall_standard_deviation_2_inst;
    Object Qpprint_standard_deviation_2_instruction;
    Object Qfuncall_standard_deviation_1_inst;
    Object Qpprint_standard_deviation_1_instruction;
    Object Qfuncall_maximum_value_2_inst, Qpprint_maximum_value_2_instruction;
    Object Qfuncall_maximum_value_1_inst, Qpprint_maximum_value_1_instruction;
    Object Qfuncall_minimum_value_2_inst, Qpprint_minimum_value_2_instruction;
    Object Qfuncall_minimum_value_1_inst, Qpprint_minimum_value_1_instruction;
    Object Qfuncall_sum_of_values_2_inst, Qpprint_sum_of_values_2_instruction;
    Object Qfuncall_sum_of_values_1_inst, Qpprint_sum_of_values_1_instruction;
    Object Qfuncall_average_value_2_inst, Qpprint_average_value_2_instruction;
    Object Qfuncall_average_value_1_inst, Qpprint_average_value_1_instruction;
    Object Qvariable_or_parameter, Qeval_is_not_less_true_than_funcalled;
    Object list_constant_29, Qis_not_less_true_than;
    Object Qeval_is_less_true_than_funcalled, Qis_less_true_than;
    Object Qeval_is_not_more_true_than_funcalled, Qis_not_more_true_than;
    Object Qeval_is_more_true_than_funcalled, Qis_more_true_than;
    Object Qeval_fuzzy_not_eq_funcalled, Qpprint_fuzzy_not_eq_evaluator;
    Object list_constant_34, Qfuzzy_not_eq, Qeval_fuzzy_eq_funcalled;
    Object Qpprint_fuzzy_eq_evaluator, Qfuzzy_eq, Qeval_fuzzy_gt_funcalled;
    Object Qpprint_fuzzy_gt_evaluator, Qfuzzy_gt, Qeval_fuzzy_lt_funcalled;
    Object Qpprint_fuzzy_lt_evaluator, Qfuzzy_lt, list_constant_14;
    Object list_constant_22, Qeval_same_as_in_line, Qsame_as, Qitem, Qis_not;
    Object Qfuncall_is_and_possibly_unknown_inst;
    Object Qpprint_is_and_possibly_unknown_instruction, Qfuncall_is_inst;
    Object Qpprint_is_instruction, Qeval_lt_eq_datum_in_line, list_constant_31;
    Object Qlt_eq_datum, Qeval_lt_eq_text_in_line, list_constant_27;
    Object Qlt_eq_text, Qeval_lt_eq_float_in_line, list_constant_16;
    Object Qlt_eq_float, Qeval_lt_eq_integer_in_line, Qlt_eq_integer;
    Object Qeval_lt_eq_quantity_in_line, Qlt_eq_quantity;
    Object Qeval_lt_datum_in_line, Qlt_datum, Qeval_lt_text_in_line, Qlt_text;
    Object Qeval_lt_float_in_line, Qlt_float, Qeval_lt_integer_in_line;
    Object Qlt_integer, Qeval_lt_quantity_in_line, Qlt_quantity;
    Object Qeval_gt_eq_datum_in_line, Qgt_eq_datum, Qeval_gt_eq_text_in_line;
    Object Qgt_eq_text, Qeval_gt_eq_float_in_line, Qgt_eq_float;
    Object Qeval_gt_eq_integer_in_line, Qgt_eq_integer;
    Object Qeval_gt_eq_quantity_in_line, Qgt_eq_quantity;
    Object Qeval_gt_datum_in_line, Qgt_datum, Qeval_gt_text_in_line, Qgt_text;
    Object Qeval_gt_float_in_line, Qgt_float, Qeval_gt_integer_in_line;
    Object Qgt_integer, Qeval_gt_quantity_in_line, Qgt_quantity;
    Object Qeval_sl_eq_datum_in_line, Qsl_eq_datum;
    Object Qeval_sl_eq_truth_value_in_line, Qsl_eq_truth_value;
    Object Qeval_sl_eq_text_in_line, Qsl_eq_text, Qeval_sl_eq_symbol_in_line;
    Object list_constant_28, Qsl_eq_symbol, Qeval_sl_eq_float_in_line;
    Object Qsl_eq_float, Qeval_sl_eq_integer_in_line, Qsl_eq_integer;
    Object Qeval_sl_eq_quantity_in_line, Qsl_eq_quantity;
    Object Qeval_eq_datum_in_line, Qeq_datum, list_constant_30;
    Object Qeval_eq_truth_value_in_line, Qeq_truth_value;
    Object Qeval_eq_text_in_line, Qeq_text, Qeval_eq_symbol_in_line;
    Object Qeq_symbol, Qeval_eq_float_in_line, Qeq_float;
    Object Qeval_eq_integer_in_line, Qeq_integer, Qeval_eq_quantity_in_line;
    Object Qeq_quantity, Qeval_format_numeric_text_funcalled;
    Object Qformat_numeric_text, list_constant_13;
    Object Qeval_fixed_format_funcalled, Qpprint_fixed_format_evaluator;
    Object Qfixed_format, Qeval_format_funcalled, Qpprint_format_evaluator;
    Object list_constant_25, Qab_format, Qfuncall_format_form_inst;
    Object Qpprint_format_form_instruction, list_constant_24, Qprocedure;
    Object Qinference, Qno_item, Qno_item_implies_unknown, Qunknown_datum;
    Object Qeval_ct_float_in_line, Qct_float, Qct, Qeval_ct_quantity_in_line;
    Object Qct_quantity, Qeval_sl_float_in_line, Qsl_float;
    Object Qeval_star_long_in_line, Qlong, list_constant_17, Qstar_long;
    Object Qeval_star_float_in_line, Qstar_float, Qeval_star_integer_in_line;
    Object Qstar_integer, Qeval_star_quantity_in_line, Qstar_quantity;
    Object Qpprint_negate_evaluator, Qeval_negate_long_in_line;
    Object list_constant_21, Qnegate_long, Qeval_negate_float_in_line;
    Object Qnegate_float, Qeval_negate_integer_in_line, list_constant_19;
    Object Qnegate_integer, Qeval_negate_in_line, list_constant_18, Qnegate;
    Object Qeval_subtract_long_in_line, Qsubtract_long;
    Object Qeval_subtract_float_in_line, Qsubtract_float;
    Object Qeval_subtract_integer_in_line, Qsubtract_integer;
    Object Qeval_subtract_quantity_in_line, Qsubtract_quantity;
    Object Qeval_plus_long_in_line, Qplus_long, Qeval_plus_float_in_line;
    Object Qplus_float, Qeval_plus_integer_in_line, Qplus_integer;
    Object Qeval_plus_quantity_in_line, Qplus_quantity;

    x_note_fn_call(207,211);
    SET_PACKAGE("AB");
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    string_constant = STATIC_STRING("negate");
    AB_package = STATIC_PACKAGE("AB");
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    Qtime_stamp = STATIC_SYMBOL("TIME-STAMP",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)33L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)34L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)39L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)57344L);
    Qis = STATIC_SYMBOL("IS",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)43L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)57344L);
    string_constant_1 = STATIC_STRING("the average value of");
    string_constant_2 = STATIC_STRING("the sum of the values of");
    string_constant_3 = STATIC_STRING("the minimum value of");
    string_constant_4 = STATIC_STRING("the maximum value of");
    string_constant_5 = STATIC_STRING("the standard deviation of");
    string_constant_6 = STATIC_STRING("the number of history datapoints in");
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)39L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    string_constant_7 = STATIC_STRING("the rate of change per");
    string_constant_8 = STATIC_STRING("the integral in");
    array_constant_15 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)17L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)20L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)24L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)31L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)23L,(SI_Long)57344L);
    array_constant_21 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)17L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)20L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)31L,(SI_Long)57344L);
    array_constant_23 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)23L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)19L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)21L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)31L,(SI_Long)57344L);
    array_constant_27 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)21L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)31L,(SI_Long)57344L);
    array_constant_28 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)9L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)23L,(SI_Long)57344L);
    array_constant_29 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)31L,(SI_Long)57344L);
    array_constant_30 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)9L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)31L,(SI_Long)57344L);
    array_constant_31 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)57344L);
    array_constant_32 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)15L,(SI_Long)57344L);
    array_constant_33 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)57344L);
    array_constant_34 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)5L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)15L,(SI_Long)57344L);
    array_constant_35 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)5L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)14L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)23L,(SI_Long)57344L);
    array_constant_36 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)15L,(SI_Long)57344L);
    float_contagion_stack_operators_new_value = adjoin(2,Qplus,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qplus_quantity = STATIC_SYMBOL("+-QUANTITY",AB_package);
    Qall = STATIC_SYMBOL("ALL",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qnumber,Qnumber);
    Qeval_plus_quantity_in_line = STATIC_SYMBOL("EVAL-+-QUANTITY-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qplus,
	    Qplus_quantity,FIX((SI_Long)4L),Qall,list_constant_14,Qnumber,
	    Nil,Qeval_plus_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)0L),T,Nil,
	    Nil),FIX((SI_Long)0L));
    Qplus_integer = STATIC_SYMBOL("+-INTEGER",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qinteger,Qinteger);
    Qeval_plus_integer_in_line = STATIC_SYMBOL("EVAL-+-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qplus,
	    Qplus_integer,FIX((SI_Long)1L),Qall,list_constant_15,Qinteger,
	    Nil,Qeval_plus_integer_in_line,T,
	    FIXNUM_ADD1(Base_in_line_evaluator_number),Nil,Nil,Nil),
	    FIX((SI_Long)1L));
    Qplus_float = STATIC_SYMBOL("+-FLOAT",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qfloat,Qfloat);
    Qeval_plus_float_in_line = STATIC_SYMBOL("EVAL-+-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qplus,
	    Qplus_float,FIX((SI_Long)2L),Qall,list_constant_16,Qfloat,Nil,
	    Qeval_plus_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)2L),T,Nil,
	    Nil),FIX((SI_Long)2L));
    Qplus_long = STATIC_SYMBOL("+-LONG",AB_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qlong,Qlong);
    Qeval_plus_long_in_line = STATIC_SYMBOL("EVAL-+-LONG-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qplus,Qplus_long,
	    FIX((SI_Long)3L),Qall,list_constant_17,Qlong,Nil,
	    Qeval_plus_long_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)100L),T,Nil,
	    Nil),FIX((SI_Long)100L));
    float_contagion_stack_operators_new_value = adjoin(2,Qminus,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qsubtract_quantity = STATIC_SYMBOL("SUBTRACT-QUANTITY",AB_package);
    Qeval_subtract_quantity_in_line = 
	    STATIC_SYMBOL("EVAL-SUBTRACT-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qminus,
	    Qsubtract_quantity,FIX((SI_Long)4L),Qall,list_constant_14,
	    Qnumber,Nil,Qeval_subtract_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)3L),T,Nil,
	    Nil),FIX((SI_Long)3L));
    Qsubtract_integer = STATIC_SYMBOL("SUBTRACT-INTEGER",AB_package);
    Qeval_subtract_integer_in_line = 
	    STATIC_SYMBOL("EVAL-SUBTRACT-INTEGER-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qminus,
	    Qsubtract_integer,FIX((SI_Long)1L),Qall,list_constant_15,
	    Qinteger,Nil,Qeval_subtract_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)4L),Nil,Nil,
	    Nil),FIX((SI_Long)4L));
    Qsubtract_float = STATIC_SYMBOL("SUBTRACT-FLOAT",AB_package);
    Qeval_subtract_float_in_line = 
	    STATIC_SYMBOL("EVAL-SUBTRACT-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qminus,
	    Qsubtract_float,FIX((SI_Long)2L),Qall,list_constant_16,Qfloat,
	    Nil,Qeval_subtract_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)5L),T,Nil,
	    Nil),FIX((SI_Long)5L));
    Qsubtract_long = STATIC_SYMBOL("SUBTRACT-LONG",AB_package);
    Qeval_subtract_long_in_line = 
	    STATIC_SYMBOL("EVAL-SUBTRACT-LONG-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qminus,
	    Qsubtract_long,FIX((SI_Long)3L),Qall,list_constant_17,Qlong,
	    Nil,Qeval_subtract_long_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)102L),T,Nil,
	    Nil),FIX((SI_Long)102L));
    Qnegate = STATIC_SYMBOL("NEGATE",AB_package);
    list_constant_18 = STATIC_CONS(Qnumber,Qnil);
    Qeval_negate_in_line = STATIC_SYMBOL("EVAL-NEGATE-IN-LINE",AB_package);
    Qpprint_negate_evaluator = STATIC_SYMBOL("PPRINT-NEGATE-EVALUATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_negate_evaluator,
	    STATIC_FUNCTION(pprint_negate_evaluator,NIL,FALSE,6,6));
    register_in_line_evaluator(make_evaluator_description(Qminus,Qnegate,
	    FIX((SI_Long)3L),Qall,list_constant_18,Qnumber,Nil,
	    Qeval_negate_in_line,T,FIX(IFIX(Base_in_line_evaluator_number) 
	    + (SI_Long)6L),T,SYMBOL_FUNCTION(Qpprint_negate_evaluator),
	    Nil),FIX((SI_Long)6L));
    Qnegate_integer = STATIC_SYMBOL("NEGATE-INTEGER",AB_package);
    list_constant_19 = STATIC_CONS(Qinteger,Qnil);
    Qeval_negate_integer_in_line = 
	    STATIC_SYMBOL("EVAL-NEGATE-INTEGER-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qminus,
	    Qnegate_integer,FIX((SI_Long)1L),Qall,list_constant_19,
	    Qinteger,Nil,Qeval_negate_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)7L),Nil,
	    SYMBOL_FUNCTION(Qpprint_negate_evaluator),Nil),FIX((SI_Long)7L));
    Qnegate_float = STATIC_SYMBOL("NEGATE-FLOAT",AB_package);
    list_constant_20 = STATIC_CONS(Qfloat,Qnil);
    Qeval_negate_float_in_line = STATIC_SYMBOL("EVAL-NEGATE-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qminus,
	    Qnegate_float,FIX((SI_Long)2L),Qall,list_constant_20,Qfloat,
	    Nil,Qeval_negate_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)8L),T,
	    SYMBOL_FUNCTION(Qpprint_negate_evaluator),Nil),FIX((SI_Long)8L));
    Qnegate_long = STATIC_SYMBOL("NEGATE-LONG",AB_package);
    list_constant_21 = STATIC_CONS(Qlong,Qnil);
    Qeval_negate_long_in_line = STATIC_SYMBOL("EVAL-NEGATE-LONG-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qminus,
	    Qnegate_long,FIX((SI_Long)2L),Qall,list_constant_21,Qlong,Nil,
	    Qeval_negate_long_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)104L),T,
	    SYMBOL_FUNCTION(Qpprint_negate_evaluator),Nil),FIX((SI_Long)104L));
    float_contagion_stack_operators_new_value = adjoin(2,Qstar,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qstar_quantity = STATIC_SYMBOL("*-QUANTITY",AB_package);
    Qeval_star_quantity_in_line = STATIC_SYMBOL("EVAL-*-QUANTITY-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qstar,
	    Qstar_quantity,FIX((SI_Long)4L),Qall,list_constant_14,Qnumber,
	    Nil,Qeval_star_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)9L),T,Nil,
	    Nil),FIX((SI_Long)9L));
    Qstar_integer = STATIC_SYMBOL("*-INTEGER",AB_package);
    Qeval_star_integer_in_line = STATIC_SYMBOL("EVAL-*-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qstar,
	    Qstar_integer,FIX((SI_Long)1L),Qall,list_constant_15,Qinteger,
	    Nil,Qeval_star_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)10L),Nil,
	    Nil,Nil),FIX((SI_Long)10L));
    Qstar_float = STATIC_SYMBOL("*-FLOAT",AB_package);
    Qeval_star_float_in_line = STATIC_SYMBOL("EVAL-*-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qstar,
	    Qstar_float,FIX((SI_Long)2L),Qall,list_constant_16,Qfloat,Nil,
	    Qeval_star_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)11L),T,Nil,
	    Nil),FIX((SI_Long)11L));
    Qstar_long = STATIC_SYMBOL("*-LONG",AB_package);
    Qeval_star_long_in_line = STATIC_SYMBOL("EVAL-*-LONG-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qstar,Qstar_long,
	    FIX((SI_Long)2L),Qall,list_constant_17,Qlong,Nil,
	    Qeval_star_long_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)101L),T,Nil,
	    Nil),FIX((SI_Long)101L));
    float_contagion_stack_operators_new_value = adjoin(2,Qslash,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qsl_float = STATIC_SYMBOL("/-FLOAT",AB_package);
    Qeval_sl_float_in_line = STATIC_SYMBOL("EVAL-/-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qslash,Qsl_float,
	    FIX((SI_Long)2L),Qall,list_constant_16,Qfloat,Nil,
	    Qeval_sl_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)12L),T,Nil,
	    Nil),FIX((SI_Long)12L));
    Qct = STATIC_SYMBOL("^",AB_package);
    float_contagion_stack_operators_new_value = adjoin(2,Qct,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qct_quantity = STATIC_SYMBOL("^-QUANTITY",AB_package);
    Qeval_ct_quantity_in_line = STATIC_SYMBOL("EVAL-^-QUANTITY-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qct,Qct_quantity,
	    FIX((SI_Long)3L),Qall,list_constant_14,Qnumber,Nil,
	    Qeval_ct_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)13L),Nil,
	    Nil,Nil),FIX((SI_Long)13L));
    Qct_float = STATIC_SYMBOL("^-FLOAT",AB_package);
    Qeval_ct_float_in_line = STATIC_SYMBOL("EVAL-^-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qct,Qct_float,
	    FIX((SI_Long)2L),Qall,list_constant_16,Qfloat,Nil,
	    Qeval_ct_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)14L),Nil,
	    Nil,Nil),FIX((SI_Long)14L));
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    string_constant_9 = 
	    STATIC_STRING("The arguments to the exponent operator were a base ~NV and a ~\n               negative power ~NV.  These values produce an undefined result.");
    string_constant_10 = 
	    string_append2(STATIC_STRING("The arguments to the exponent operator were a negative ~\n                base ~NV and a floating point power ~NV.  These values ~\n                produce a complex number, whi"),
	    STATIC_STRING("ch is not supported in G2."));
    Qstack_special_form_converter = 
	    STATIC_SYMBOL("STACK-SPECIAL-FORM-CONVERTER",AB_package);
    Qpush_constant = STATIC_SYMBOL("PUSH-CONSTANT",AB_package);
    quote_stack_node_converter_1 = 
	    STATIC_FUNCTION(quote_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qquote,quote_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qab_let = STATIC_SYMBOL("LET",AB_package);
    Qexpiration_special_form_operator_p = 
	    STATIC_SYMBOL("EXPIRATION-SPECIAL-FORM-OPERATOR-P",AB_package);
    mutate_global_property(Qab_let,T,Qexpiration_special_form_operator_p);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    let_stack_node_converter_1 = STATIC_FUNCTION(let_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qab_let,let_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qpreferred_instruction_chooser = 
	    STATIC_SYMBOL("PREFERRED-INSTRUCTION-CHOOSER",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant = STATIC_CONS(Qunknown_datum,Qnil);
    Qno_item_implies_unknown = STATIC_SYMBOL("NO-ITEM-IMPLIES-UNKNOWN",
	    AB_package);
    list_constant_1 = STATIC_CONS(Qno_item_implies_unknown,Qnil);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_7 = STATIC_CONS(Qno_item,Qnil);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_7);
    let_i_chooser_1 = STATIC_FUNCTION(let_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qab_let,let_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qstack_node_instruction_emitter = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-EMITTER",AB_package);
    let_i_emit_1 = STATIC_FUNCTION(let_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qab_let,let_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qformat_form = STATIC_SYMBOL("FORMAT-FORM",AB_package);
    format_form_stack_node_converter_1 = 
	    STATIC_FUNCTION(format_form_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qformat_form,format_form_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    list_constant_22 = STATIC_CONS(list_constant,Qnil);
    list_constant_3 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qdatum,
	    list_constant_22);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qtext,
	    list_constant_22);
    format_form_i_chooser_1 = STATIC_FUNCTION(format_form_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qformat_form,format_form_i_chooser_1,
	    Qpreferred_instruction_chooser);
    format_form_i_emit_1 = STATIC_FUNCTION(format_form_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qformat_form,format_form_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qsymbol_name_wide_string = STATIC_SYMBOL("SYMBOL-NAME-WIDE-STRING",
	    AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qinference = STATIC_SYMBOL("INFERENCE",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qinference,Qprocedure);
    list_constant_24 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    Qfuncall_format_form_inst = STATIC_SYMBOL("FUNCALL-FORMAT-FORM-INST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_format_form_inst,
	    STATIC_FUNCTION(funcall_format_form_inst,NIL,FALSE,2,2));
    Qpprint_format_form_instruction = 
	    STATIC_SYMBOL("PPRINT-FORMAT-FORM-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_format_form_instruction,
	    STATIC_FUNCTION(pprint_format_form_instruction,NIL,FALSE,8,8));
    make_and_register_funcalled_instruction_description(Qformat_form,
	    FIX((SI_Long)32L),list_constant_23,list_constant_24,
	    FIX((SI_Long)1L),SYMBOL_FUNCTION(Qfuncall_format_form_inst),
	    Qnil,SYMBOL_FUNCTION(Qpprint_format_form_instruction),
	    Qfuncall_format_form_inst);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    string_constant_11 = 
	    STATIC_STRING("A text value cannot contain more than ~a characters.  The text ~\n                  begins with \"~a...\" and contains ~a characters.");
    string_constant_12 = 
	    STATIC_STRING("Unrecognized format control argument ~a");
    Qab_format = STATIC_SYMBOL("FORMAT",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qnumber,Qdatum);
    Qeval_format_funcalled = STATIC_SYMBOL("EVAL-FORMAT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_format_funcalled,
	    STATIC_FUNCTION(eval_format_funcalled,NIL,FALSE,2,2));
    Qpprint_format_evaluator = STATIC_SYMBOL("PPRINT-FORMAT-EVALUATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_format_evaluator,
	    STATIC_FUNCTION(pprint_format_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qab_format,
	    Qab_format,FIX((SI_Long)1L),list_constant_23,list_constant_25,
	    Qtext,Qnil,SYMBOL_FUNCTION(Qeval_format_funcalled),Nil,
	    FIX((SI_Long)0L),Nil,SYMBOL_FUNCTION(Qpprint_format_evaluator),
	    Qeval_format_funcalled),FIX((SI_Long)0L),Funcall_eval_type_2_arg);
    Qfixed_format = STATIC_SYMBOL("FIXED-FORMAT",AB_package);
    list_constant_26 = STATIC_CONS(Qnumber,list_constant_15);
    Qeval_fixed_format_funcalled = 
	    STATIC_SYMBOL("EVAL-FIXED-FORMAT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_fixed_format_funcalled,
	    STATIC_FUNCTION(eval_fixed_format_funcalled,NIL,FALSE,3,3));
    Qpprint_fixed_format_evaluator = 
	    STATIC_SYMBOL("PPRINT-FIXED-FORMAT-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_fixed_format_evaluator,
	    STATIC_FUNCTION(pprint_fixed_format_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qfixed_format,
	    Qfixed_format,FIX((SI_Long)1L),list_constant_23,
	    list_constant_26,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_fixed_format_funcalled),Nil,
	    FIX((SI_Long)1L),Nil,
	    SYMBOL_FUNCTION(Qpprint_fixed_format_evaluator),
	    Qeval_fixed_format_funcalled),FIX((SI_Long)1L),
	    Funcall_eval_type_3_arg);
    string_constant_13 = STATIC_STRING("~NV is not a ddd.dddd format.");
    array_constant_37 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)57344L);
    Qoverflow = STATIC_SYMBOL("OVERFLOW",AB_package);
    Qunderflow = STATIC_SYMBOL("UNDERFLOW",AB_package);
    string_constant_14 = 
	    STATIC_STRING("~NV causes ~NV when formatted as a number.");
    string_constant_15 = 
	    STATIC_STRING("~NV could not be formatted as a number.");
    string_constant_16 = 
	    STATIC_STRING("~NV is not the text of a number, ~\n                                           an expired number, nor ****");
    array_constant_38 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)57344L);
    Qformat_numeric_text = STATIC_SYMBOL("FORMAT-NUMERIC-TEXT",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qtext,Qtext);
    Qeval_format_numeric_text_funcalled = 
	    STATIC_SYMBOL("EVAL-FORMAT-NUMERIC-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_format_numeric_text_funcalled,
	    STATIC_FUNCTION(eval_format_numeric_text_funcalled,NIL,FALSE,2,2));
    Qpprint_functional_evaluator = 
	    STATIC_SYMBOL("PPRINT-FUNCTIONAL-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_functional_evaluator,
	    STATIC_FUNCTION(pprint_functional_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qformat_numeric_text,
	    Qformat_numeric_text,FIX((SI_Long)1L),list_constant_23,
	    list_constant_27,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_format_numeric_text_funcalled),Nil,
	    FIX((SI_Long)121L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_format_numeric_text_funcalled),FIX((SI_Long)121L),
	    Funcall_eval_type_2_arg);
    Qeq_quantity = STATIC_SYMBOL("=-QUANTITY",AB_package);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Qeval_eq_quantity_in_line = STATIC_SYMBOL("EVAL-=-QUANTITY-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_eq,
	    Qeq_quantity,FIX((SI_Long)3L),Qall,list_constant_14,Qboolean,
	    Nil,Qeval_eq_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)16L),T,Nil,
	    Nil),FIX((SI_Long)16L));
    Qeq_integer = STATIC_SYMBOL("=-INTEGER",AB_package);
    Qeval_eq_integer_in_line = STATIC_SYMBOL("EVAL-=-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_eq,
	    Qeq_integer,FIX((SI_Long)1L),Qall,list_constant_15,Qboolean,
	    Nil,Qeval_eq_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)17L),Nil,
	    Nil,Nil),FIX((SI_Long)17L));
    Qeq_float = STATIC_SYMBOL("=-FLOAT",AB_package);
    Qeval_eq_float_in_line = STATIC_SYMBOL("EVAL-=-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_eq,
	    Qeq_float,FIX((SI_Long)2L),Qall,list_constant_16,Qboolean,Nil,
	    Qeval_eq_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)18L),T,Nil,
	    Nil),FIX((SI_Long)18L));
    Qeq_symbol = STATIC_SYMBOL("=-SYMBOL",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qsymbol,Qsymbol);
    Qeval_eq_symbol_in_line = STATIC_SYMBOL("EVAL-=-SYMBOL-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_eq,
	    Qeq_symbol,FIX((SI_Long)1L),list_constant_23,list_constant_28,
	    Qboolean,Nil,Qeval_eq_symbol_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)19L),Nil,
	    Nil,Nil),FIX((SI_Long)19L));
    Qeq_text = STATIC_SYMBOL("=-TEXT",AB_package);
    Qeval_eq_text_in_line = STATIC_SYMBOL("EVAL-=-TEXT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_eq,Qeq_text,
	    FIX((SI_Long)1L),list_constant_23,list_constant_27,Qboolean,
	    Nil,Qeval_eq_text_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)20L),T,Nil,
	    Nil),FIX((SI_Long)20L));
    Qeq_truth_value = STATIC_SYMBOL("=-TRUTH-VALUE",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qtruth_value,Qtruth_value);
    Qeval_eq_truth_value_in_line = 
	    STATIC_SYMBOL("EVAL-=-TRUTH-VALUE-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_eq,
	    Qeq_truth_value,FIX((SI_Long)1L),list_constant_23,
	    list_constant_29,Qboolean,Nil,Qeval_eq_truth_value_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)21L),T,Nil,
	    Nil),FIX((SI_Long)21L));
    Qeq_datum = STATIC_SYMBOL("=-DATUM",AB_package);
    list_constant_30 = STATIC_CONS(Qdatum,Qnil);
    list_constant_31 = STATIC_CONS(Qdatum,list_constant_30);
    Qeval_eq_datum_in_line = STATIC_SYMBOL("EVAL-=-DATUM-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_eq,
	    Qeq_datum,FIX((SI_Long)4L),list_constant_23,list_constant_31,
	    Qboolean,Nil,Qeval_eq_datum_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)22L),T,Nil,
	    Nil),FIX((SI_Long)22L));
    Qsl_eq_quantity = STATIC_SYMBOL("/=-QUANTITY",AB_package);
    Qeval_sl_eq_quantity_in_line = 
	    STATIC_SYMBOL("EVAL-/=-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ne,
	    Qsl_eq_quantity,FIX((SI_Long)3L),Qall,list_constant_14,
	    Qboolean,Nil,Qeval_sl_eq_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)23L),T,Nil,
	    Nil),FIX((SI_Long)23L));
    Qsl_eq_integer = STATIC_SYMBOL("/=-INTEGER",AB_package);
    Qeval_sl_eq_integer_in_line = STATIC_SYMBOL("EVAL-/=-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ne,
	    Qsl_eq_integer,FIX((SI_Long)1L),Qall,list_constant_15,Qboolean,
	    Nil,Qeval_sl_eq_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)24L),Nil,
	    Nil,Nil),FIX((SI_Long)24L));
    Qsl_eq_float = STATIC_SYMBOL("/=-FLOAT",AB_package);
    Qeval_sl_eq_float_in_line = STATIC_SYMBOL("EVAL-/=-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ne,
	    Qsl_eq_float,FIX((SI_Long)2L),Qall,list_constant_16,Qboolean,
	    Nil,Qeval_sl_eq_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)25L),T,Nil,
	    Nil),FIX((SI_Long)25L));
    Qsl_eq_symbol = STATIC_SYMBOL("/=-SYMBOL",AB_package);
    Qeval_sl_eq_symbol_in_line = STATIC_SYMBOL("EVAL-/=-SYMBOL-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ne,
	    Qsl_eq_symbol,FIX((SI_Long)1L),list_constant_23,
	    list_constant_28,Qboolean,Nil,Qeval_sl_eq_symbol_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)26L),Nil,
	    Nil,Nil),FIX((SI_Long)26L));
    Qsl_eq_text = STATIC_SYMBOL("/=-TEXT",AB_package);
    Qeval_sl_eq_text_in_line = STATIC_SYMBOL("EVAL-/=-TEXT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ne,
	    Qsl_eq_text,FIX((SI_Long)1L),list_constant_23,list_constant_27,
	    Qboolean,Nil,Qeval_sl_eq_text_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)27L),T,Nil,
	    Nil),FIX((SI_Long)27L));
    Qsl_eq_truth_value = STATIC_SYMBOL("/=-TRUTH-VALUE",AB_package);
    Qeval_sl_eq_truth_value_in_line = 
	    STATIC_SYMBOL("EVAL-/=-TRUTH-VALUE-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ne,
	    Qsl_eq_truth_value,FIX((SI_Long)1L),list_constant_23,
	    list_constant_29,Qboolean,Nil,Qeval_sl_eq_truth_value_in_line,
	    T,FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)28L),T,
	    Nil,Nil),FIX((SI_Long)28L));
    Qsl_eq_datum = STATIC_SYMBOL("/=-DATUM",AB_package);
    Qeval_sl_eq_datum_in_line = STATIC_SYMBOL("EVAL-/=-DATUM-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ne,
	    Qsl_eq_datum,FIX((SI_Long)4L),list_constant_23,
	    list_constant_31,Qboolean,Nil,Qeval_sl_eq_datum_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)29L),T,Nil,
	    Nil),FIX((SI_Long)29L));
    float_contagion_stack_operators_new_value = adjoin(2,Qnum_gt,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qgt_quantity = STATIC_SYMBOL(">-QUANTITY",AB_package);
    Qeval_gt_quantity_in_line = STATIC_SYMBOL("EVAL->-QUANTITY-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_gt,
	    Qgt_quantity,FIX((SI_Long)3L),Qall,list_constant_14,Qboolean,
	    Nil,Qeval_gt_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)30L),T,Nil,
	    Nil),FIX((SI_Long)30L));
    Qgt_integer = STATIC_SYMBOL(">-INTEGER",AB_package);
    Qeval_gt_integer_in_line = STATIC_SYMBOL("EVAL->-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_gt,
	    Qgt_integer,FIX((SI_Long)1L),Qall,list_constant_15,Qboolean,
	    Nil,Qeval_gt_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)31L),Nil,
	    Nil,Nil),FIX((SI_Long)31L));
    Qgt_float = STATIC_SYMBOL(">-FLOAT",AB_package);
    Qeval_gt_float_in_line = STATIC_SYMBOL("EVAL->-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_gt,
	    Qgt_float,FIX((SI_Long)2L),Qall,list_constant_16,Qboolean,Nil,
	    Qeval_gt_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)32L),T,Nil,
	    Nil),FIX((SI_Long)32L));
    Qgt_text = STATIC_SYMBOL(">-TEXT",AB_package);
    Qeval_gt_text_in_line = STATIC_SYMBOL("EVAL->-TEXT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_gt,Qgt_text,
	    FIX((SI_Long)1L),Qall,list_constant_27,Qboolean,Nil,
	    Qeval_gt_text_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)33L),T,Nil,
	    Nil),FIX((SI_Long)33L));
    Qgt_datum = STATIC_SYMBOL(">-DATUM",AB_package);
    Qeval_gt_datum_in_line = STATIC_SYMBOL("EVAL->-DATUM-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_gt,
	    Qgt_datum,FIX((SI_Long)4L),list_constant_23,list_constant_31,
	    Qboolean,Nil,Qeval_gt_datum_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)34L),T,Nil,
	    Nil),FIX((SI_Long)34L));
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    string_constant_17 = 
	    STATIC_STRING("The ~a operator received the invalid argument ~NV.");
    string_constant_18 = 
	    STATIC_STRING("The ~a operator received the invalid argument ~A.");
    string_constant_19 = 
	    STATIC_STRING("In a ~a expression, the values ~NE and ~NE are not of the same type.");
    float_contagion_stack_operators_new_value = adjoin(2,Qnum_ge,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qgt_eq_quantity = STATIC_SYMBOL(">=-QUANTITY",AB_package);
    Qeval_gt_eq_quantity_in_line = 
	    STATIC_SYMBOL("EVAL->=-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ge,
	    Qgt_eq_quantity,FIX((SI_Long)3L),Qall,list_constant_14,
	    Qboolean,Nil,Qeval_gt_eq_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)35L),T,Nil,
	    Nil),FIX((SI_Long)35L));
    Qgt_eq_integer = STATIC_SYMBOL(">=-INTEGER",AB_package);
    Qeval_gt_eq_integer_in_line = STATIC_SYMBOL("EVAL->=-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ge,
	    Qgt_eq_integer,FIX((SI_Long)1L),Qall,list_constant_15,Qboolean,
	    Nil,Qeval_gt_eq_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)36L),Nil,
	    Nil,Nil),FIX((SI_Long)36L));
    Qgt_eq_float = STATIC_SYMBOL(">=-FLOAT",AB_package);
    Qeval_gt_eq_float_in_line = STATIC_SYMBOL("EVAL->=-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ge,
	    Qgt_eq_float,FIX((SI_Long)2L),Qall,list_constant_16,Qboolean,
	    Nil,Qeval_gt_eq_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)37L),T,Nil,
	    Nil),FIX((SI_Long)37L));
    Qgt_eq_text = STATIC_SYMBOL(">=-TEXT",AB_package);
    Qeval_gt_eq_text_in_line = STATIC_SYMBOL("EVAL->=-TEXT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ge,
	    Qgt_eq_text,FIX((SI_Long)1L),Qall,list_constant_27,Qboolean,
	    Nil,Qeval_gt_eq_text_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)38L),T,Nil,
	    Nil),FIX((SI_Long)38L));
    Qgt_eq_datum = STATIC_SYMBOL(">=-DATUM",AB_package);
    Qeval_gt_eq_datum_in_line = STATIC_SYMBOL("EVAL->=-DATUM-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_ge,
	    Qgt_eq_datum,FIX((SI_Long)4L),list_constant_23,
	    list_constant_31,Qboolean,Nil,Qeval_gt_eq_datum_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)39L),T,Nil,
	    Nil),FIX((SI_Long)39L));
    float_contagion_stack_operators_new_value = adjoin(2,Qnum_lt,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qlt_quantity = STATIC_SYMBOL("<-QUANTITY",AB_package);
    Qeval_lt_quantity_in_line = STATIC_SYMBOL("EVAL-<-QUANTITY-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_lt,
	    Qlt_quantity,FIX((SI_Long)3L),Qall,list_constant_14,Qboolean,
	    Nil,Qeval_lt_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)40L),T,Nil,
	    Nil),FIX((SI_Long)40L));
    Qlt_integer = STATIC_SYMBOL("<-INTEGER",AB_package);
    Qeval_lt_integer_in_line = STATIC_SYMBOL("EVAL-<-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_lt,
	    Qlt_integer,FIX((SI_Long)1L),Qall,list_constant_15,Qboolean,
	    Nil,Qeval_lt_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)41L),Nil,
	    Nil,Nil),FIX((SI_Long)41L));
    Qlt_float = STATIC_SYMBOL("<-FLOAT",AB_package);
    Qeval_lt_float_in_line = STATIC_SYMBOL("EVAL-<-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_lt,
	    Qlt_float,FIX((SI_Long)2L),Qall,list_constant_16,Qboolean,Nil,
	    Qeval_lt_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)42L),T,Nil,
	    Nil),FIX((SI_Long)42L));
    Qlt_text = STATIC_SYMBOL("<-TEXT",AB_package);
    Qeval_lt_text_in_line = STATIC_SYMBOL("EVAL-<-TEXT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_lt,Qlt_text,
	    FIX((SI_Long)1L),list_constant_23,list_constant_27,Qboolean,
	    Nil,Qeval_lt_text_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)43L),T,Nil,
	    Nil),FIX((SI_Long)43L));
    Qlt_datum = STATIC_SYMBOL("<-DATUM",AB_package);
    Qeval_lt_datum_in_line = STATIC_SYMBOL("EVAL-<-DATUM-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_lt,
	    Qlt_datum,FIX((SI_Long)4L),list_constant_23,list_constant_31,
	    Qboolean,Nil,Qeval_lt_datum_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)44L),T,Nil,
	    Nil),FIX((SI_Long)44L));
    float_contagion_stack_operators_new_value = adjoin(2,Qnum_le,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qlt_eq_quantity = STATIC_SYMBOL("<=-QUANTITY",AB_package);
    Qeval_lt_eq_quantity_in_line = 
	    STATIC_SYMBOL("EVAL-<=-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_le,
	    Qlt_eq_quantity,FIX((SI_Long)3L),Qall,list_constant_14,
	    Qboolean,Nil,Qeval_lt_eq_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)45L),T,Nil,
	    Nil),FIX((SI_Long)45L));
    Qlt_eq_integer = STATIC_SYMBOL("<=-INTEGER",AB_package);
    Qeval_lt_eq_integer_in_line = STATIC_SYMBOL("EVAL-<=-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_le,
	    Qlt_eq_integer,FIX((SI_Long)1L),Qall,list_constant_15,Qboolean,
	    Nil,Qeval_lt_eq_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)46L),Nil,
	    Nil,Nil),FIX((SI_Long)46L));
    Qlt_eq_float = STATIC_SYMBOL("<=-FLOAT",AB_package);
    Qeval_lt_eq_float_in_line = STATIC_SYMBOL("EVAL-<=-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_le,
	    Qlt_eq_float,FIX((SI_Long)2L),Qall,list_constant_16,Qboolean,
	    Nil,Qeval_lt_eq_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)47L),T,Nil,
	    Nil),FIX((SI_Long)47L));
    Qlt_eq_text = STATIC_SYMBOL("<=-TEXT",AB_package);
    Qeval_lt_eq_text_in_line = STATIC_SYMBOL("EVAL-<=-TEXT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_le,
	    Qlt_eq_text,FIX((SI_Long)1L),Qall,list_constant_27,Qboolean,
	    Nil,Qeval_lt_eq_text_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)48L),T,Nil,
	    Nil),FIX((SI_Long)48L));
    Qlt_eq_datum = STATIC_SYMBOL("<=-DATUM",AB_package);
    Qeval_lt_eq_datum_in_line = STATIC_SYMBOL("EVAL-<=-DATUM-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qnum_le,
	    Qlt_eq_datum,FIX((SI_Long)4L),list_constant_23,
	    list_constant_31,Qboolean,Nil,Qeval_lt_eq_datum_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)49L),T,Nil,
	    Nil),FIX((SI_Long)49L));
    is_stack_node_converter_1 = STATIC_FUNCTION(is_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qis,is_stack_node_converter_1,
	    Qstack_special_form_converter);
    is_i_chooser_1 = STATIC_FUNCTION(is_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qis,is_i_chooser_1,Qpreferred_instruction_chooser);
    Qexpiration_source_operator_p = 
	    STATIC_SYMBOL("EXPIRATION-SOURCE-OPERATOR-P",AB_package);
    mutate_global_property(Qis,T,Qexpiration_source_operator_p);
    Qis_and_possibly_unknown = STATIC_SYMBOL("IS-AND-POSSIBLY-UNKNOWN",
	    AB_package);
    is_i_emit_1 = STATIC_FUNCTION(is_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qis,is_i_emit_1,Qstack_node_instruction_emitter);
    string_constant_20 = 
	    STATIC_STRING("The first value, ~NV, in the IS expression is not a symbol.");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    string_constant_21 = 
	    STATIC_STRING("The first argument to IS, the ~a of ~NF, denoted ~\n                          more than one value.  IS requires one value only.");
    string_constant_22 = 
	    STATIC_STRING("The first argument to IS, the ~a of ~NF, held no value.");
    string_constant_23 = 
	    STATIC_STRING("The first argument to IS, ~NA, which was the ~a ~\n                       of ~NF, was not a symbol.");
    string_constant_24 = 
	    STATIC_STRING("The first argument to IS, ~NF, is not a symbol.");
    string_constant_25 = 
	    STATIC_STRING("The first argument to IS, ~NF, is not a parameter.");
    string_constant_26 = 
	    STATIC_STRING("The first argument to IS, ~NF, is an item which is neither a ~\n          parameter or an attribute with a possible symbolic value of ~a.");
    Qfuncall_is_inst = STATIC_SYMBOL("FUNCALL-IS-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_is_inst,STATIC_FUNCTION(funcall_is_inst,
	    NIL,FALSE,2,2));
    Qpprint_is_instruction = STATIC_SYMBOL("PPRINT-IS-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_is_instruction,
	    STATIC_FUNCTION(pprint_is_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qis,
	    FIX((SI_Long)33L),list_constant_23,FIX((SI_Long)2L),
	    FIX((SI_Long)1L),SYMBOL_FUNCTION(Qfuncall_is_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_is_instruction),Qfuncall_is_inst);
    string_constant_27 = 
	    STATIC_STRING("The first value passed to IS, ~NV, was not a symbol.");
    string_constant_28 = 
	    STATIC_STRING("The first argument to IS, the ~a of ~NF, denoted ~\n                           more than one value.  IS requires one value only.");
    string_constant_29 = 
	    STATIC_STRING("The first argument to IS, ~NA, which was the ~a ~\n                        of ~NF, was not a symbol.");
    string_constant_30 = 
	    STATIC_STRING("The first argument to IS, ~NV, which was the value ~\n                    of ~NF, was not a symbol.");
    string_constant_31 = 
	    STATIC_STRING("The first argument to IS, ~NF, was not a variable or a parameter.");
    string_constant_32 = 
	    STATIC_STRING("The first argument to IS, ~NV, which was the value ~\n               of ~NF, was not a symbol.");
    string_constant_33 = 
	    STATIC_STRING("The first argument to IS, ~NF, was an item which was not a variable ~\n          or parameter nor did it have an attribute with a possible symbolic ~\n          value of ~a.");
    Qfuncall_is_and_possibly_unknown_inst = 
	    STATIC_SYMBOL("FUNCALL-IS-AND-POSSIBLY-UNKNOWN-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_is_and_possibly_unknown_inst,
	    STATIC_FUNCTION(funcall_is_and_possibly_unknown_inst,NIL,FALSE,
	    2,2));
    Qpprint_is_and_possibly_unknown_instruction = 
	    STATIC_SYMBOL("PPRINT-IS-AND-POSSIBLY-UNKNOWN-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_is_and_possibly_unknown_instruction,
	    STATIC_FUNCTION(pprint_is_and_possibly_unknown_instruction,NIL,
	    FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qis_and_possibly_unknown,
	    FIX((SI_Long)34L),list_constant_23,FIX((SI_Long)2L),
	    FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_is_and_possibly_unknown_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_is_and_possibly_unknown_instruction),
	    Qfuncall_is_and_possibly_unknown_inst);
    Qis_not = STATIC_SYMBOL("IS-NOT",AB_package);
    is_not_stack_node_converter_1 = 
	    STATIC_FUNCTION(is_not_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qis_not,is_not_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qsame_as = STATIC_SYMBOL("SAME-AS",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_33 = STATIC_LIST((SI_Long)2L,list_constant_32,
	    list_constant_32);
    Qeval_same_as_in_line = STATIC_SYMBOL("EVAL-SAME-AS-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qsame_as,
	    Qsame_as,FIX((SI_Long)1L),Qall,list_constant_33,Qboolean,Nil,
	    Qeval_same_as_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)50L),T,Nil,
	    Nil),FIX((SI_Long)50L));
    and_stack_node_converter_1 = STATIC_FUNCTION(and_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qand,and_stack_node_converter_1,
	    Qstack_special_form_converter);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qboolean,
	    list_constant_22);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qtruth_value,
	    list_constant_22);
    and_i_chooser_1 = STATIC_FUNCTION(and_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qand,and_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qand,T,Qexpiration_special_form_operator_p);
    and_i_emit_1 = STATIC_FUNCTION(and_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qand,and_i_emit_1,Qstack_node_instruction_emitter);
    or_stack_node_converter_1 = STATIC_FUNCTION(or_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qab_or,or_stack_node_converter_1,
	    Qstack_special_form_converter);
    or_i_chooser_1 = STATIC_FUNCTION(or_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qab_or,or_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qab_or,T,Qexpiration_special_form_operator_p);
    or_i_emit_1 = STATIC_FUNCTION(or_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qab_or,or_i_emit_1,Qstack_node_instruction_emitter);
    not_stack_node_converter_1 = STATIC_FUNCTION(not_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qnot,not_stack_node_converter_1,
	    Qstack_special_form_converter);
    not_i_chooser_1 = STATIC_FUNCTION(not_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qnot,not_i_chooser_1,
	    Qpreferred_instruction_chooser);
    not_i_emit_1 = STATIC_FUNCTION(not_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qnot,not_i_emit_1,Qstack_node_instruction_emitter);
    string_constant_34 = 
	    STATIC_STRING("The fuzzy comparator band value ~a is less than zero.");
    Qfuzzy_lt = STATIC_SYMBOL("FUZZY-<",AB_package);
    list_constant_34 = STATIC_CONS(Qnumber,list_constant_14);
    Qeval_fuzzy_lt_funcalled = STATIC_SYMBOL("EVAL-FUZZY-<-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_fuzzy_lt_funcalled,
	    STATIC_FUNCTION(eval_fuzzy_lt_funcalled,NIL,FALSE,3,3));
    Qpprint_fuzzy_lt_evaluator = STATIC_SYMBOL("PPRINT-FUZZY-<-EVALUATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_fuzzy_lt_evaluator,
	    STATIC_FUNCTION(pprint_fuzzy_lt_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qfuzzy_lt,
	    Qfuzzy_lt,FIX((SI_Long)1L),list_constant_23,list_constant_34,
	    Qtruth_value,Qnil,SYMBOL_FUNCTION(Qeval_fuzzy_lt_funcalled),
	    Nil,FIX((SI_Long)2L),Nil,
	    SYMBOL_FUNCTION(Qpprint_fuzzy_lt_evaluator),
	    Qeval_fuzzy_lt_funcalled),FIX((SI_Long)2L),
	    Funcall_eval_type_3_arg);
    Qfuzzy_gt = STATIC_SYMBOL("FUZZY->",AB_package);
    Qeval_fuzzy_gt_funcalled = STATIC_SYMBOL("EVAL-FUZZY->-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_fuzzy_gt_funcalled,
	    STATIC_FUNCTION(eval_fuzzy_gt_funcalled,NIL,FALSE,3,3));
    Qpprint_fuzzy_gt_evaluator = STATIC_SYMBOL("PPRINT-FUZZY->-EVALUATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_fuzzy_gt_evaluator,
	    STATIC_FUNCTION(pprint_fuzzy_gt_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qfuzzy_gt,
	    Qfuzzy_gt,FIX((SI_Long)1L),list_constant_23,list_constant_34,
	    Qtruth_value,Qnil,SYMBOL_FUNCTION(Qeval_fuzzy_gt_funcalled),
	    Nil,FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qpprint_fuzzy_gt_evaluator),
	    Qeval_fuzzy_gt_funcalled),FIX((SI_Long)3L),
	    Funcall_eval_type_3_arg);
    Qfuzzy_eq = STATIC_SYMBOL("FUZZY-=",AB_package);
    Qeval_fuzzy_eq_funcalled = STATIC_SYMBOL("EVAL-FUZZY-=-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_fuzzy_eq_funcalled,
	    STATIC_FUNCTION(eval_fuzzy_eq_funcalled,NIL,FALSE,3,3));
    Qpprint_fuzzy_eq_evaluator = STATIC_SYMBOL("PPRINT-FUZZY-=-EVALUATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_fuzzy_eq_evaluator,
	    STATIC_FUNCTION(pprint_fuzzy_eq_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qfuzzy_eq,
	    Qfuzzy_eq,FIX((SI_Long)1L),list_constant_23,list_constant_34,
	    Qtruth_value,Qnil,SYMBOL_FUNCTION(Qeval_fuzzy_eq_funcalled),
	    Nil,FIX((SI_Long)4L),Nil,
	    SYMBOL_FUNCTION(Qpprint_fuzzy_eq_evaluator),
	    Qeval_fuzzy_eq_funcalled),FIX((SI_Long)4L),
	    Funcall_eval_type_3_arg);
    Qfuzzy_not_eq = STATIC_SYMBOL("FUZZY-NOT-=",AB_package);
    Qeval_fuzzy_not_eq_funcalled = 
	    STATIC_SYMBOL("EVAL-FUZZY-NOT-=-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_fuzzy_not_eq_funcalled,
	    STATIC_FUNCTION(eval_fuzzy_not_eq_funcalled,NIL,FALSE,3,3));
    Qpprint_fuzzy_not_eq_evaluator = 
	    STATIC_SYMBOL("PPRINT-FUZZY-NOT-=-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_fuzzy_not_eq_evaluator,
	    STATIC_FUNCTION(pprint_fuzzy_not_eq_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qfuzzy_not_eq,
	    Qfuzzy_not_eq,FIX((SI_Long)1L),list_constant_23,
	    list_constant_34,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qeval_fuzzy_not_eq_funcalled),Nil,
	    FIX((SI_Long)5L),Nil,
	    SYMBOL_FUNCTION(Qpprint_fuzzy_not_eq_evaluator),
	    Qeval_fuzzy_not_eq_funcalled),FIX((SI_Long)5L),
	    Funcall_eval_type_3_arg);
    Qis_more_true_than = STATIC_SYMBOL("IS-MORE-TRUE-THAN",AB_package);
    Qeval_is_more_true_than_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-MORE-TRUE-THAN-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_more_true_than_funcalled,
	    STATIC_FUNCTION(eval_is_more_true_than_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qis_more_true_than,
	    Qis_more_true_than,FIX((SI_Long)1L),list_constant_23,
	    list_constant_29,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_more_true_than_funcalled),Nil,
	    FIX((SI_Long)6L),Nil,Nil,Qeval_is_more_true_than_funcalled),
	    FIX((SI_Long)6L),Funcall_eval_type_2_arg);
    Qis_not_more_true_than = STATIC_SYMBOL("IS-NOT-MORE-TRUE-THAN",AB_package);
    Qeval_is_not_more_true_than_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-NOT-MORE-TRUE-THAN-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_not_more_true_than_funcalled,
	    STATIC_FUNCTION(eval_is_not_more_true_than_funcalled,NIL,FALSE,
	    2,2));
    register_funcalled_evaluator(make_evaluator_description(Qis_not_more_true_than,
	    Qis_not_more_true_than,FIX((SI_Long)1L),list_constant_23,
	    list_constant_29,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_not_more_true_than_funcalled),Nil,
	    FIX((SI_Long)7L),Nil,Nil,
	    Qeval_is_not_more_true_than_funcalled),FIX((SI_Long)7L),
	    Funcall_eval_type_2_arg);
    Qis_less_true_than = STATIC_SYMBOL("IS-LESS-TRUE-THAN",AB_package);
    Qeval_is_less_true_than_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-LESS-TRUE-THAN-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_less_true_than_funcalled,
	    STATIC_FUNCTION(eval_is_less_true_than_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qis_less_true_than,
	    Qis_less_true_than,FIX((SI_Long)1L),list_constant_23,
	    list_constant_29,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_less_true_than_funcalled),Nil,
	    FIX((SI_Long)8L),Nil,Nil,Qeval_is_less_true_than_funcalled),
	    FIX((SI_Long)8L),Funcall_eval_type_2_arg);
    Qis_not_less_true_than = STATIC_SYMBOL("IS-NOT-LESS-TRUE-THAN",AB_package);
    Qeval_is_not_less_true_than_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-NOT-LESS-TRUE-THAN-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_not_less_true_than_funcalled,
	    STATIC_FUNCTION(eval_is_not_less_true_than_funcalled,NIL,FALSE,
	    2,2));
    register_funcalled_evaluator(make_evaluator_description(Qis_not_less_true_than,
	    Qis_not_less_true_than,FIX((SI_Long)1L),list_constant_23,
	    list_constant_29,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_not_less_true_than_funcalled),Nil,
	    FIX((SI_Long)9L),Nil,Nil,
	    Qeval_is_not_less_true_than_funcalled),FIX((SI_Long)9L),
	    Funcall_eval_type_2_arg);
    Qif_expression = STATIC_SYMBOL("IF-EXPRESSION",AB_package);
    if_expression_stack_node_converter_1 = 
	    STATIC_FUNCTION(if_expression_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qif_expression,
	    if_expression_stack_node_converter_1,
	    Qstack_special_form_converter);
    string_constant_35 = STATIC_STRING("if-expression emitter");
    string_constant_36 = 
	    STATIC_STRING("Non-union unknown type returned from then or else clause.");
    string_constant_37 = STATIC_STRING("~a ~a ~a");
    string_constant_38 = 
	    STATIC_STRING("An IF with no ELSE clause cannot be used in procedures (except within ");
    string_constant_39 = 
	    STATIC_STRING("a COLLECT DATA or WAIT statement), since a missing ELSE can produce ");
    string_constant_40 = STATIC_STRING("the value unknown.");
    if_expression_i_chooser_1 = STATIC_FUNCTION(if_expression_i_chooser,
	    NIL,FALSE,1,1);
    mutate_global_property(Qif_expression,if_expression_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qif_expression,T,
	    Qexpiration_special_form_operator_p);
    string_constant_41 = STATIC_STRING("if expression emitter");
    string_constant_42 = 
	    STATIC_STRING("There is no else clause and unknown is not allowed.");
    if_expression_i_emit_1 = STATIC_FUNCTION(if_expression_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qif_expression,if_expression_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qaverage_value_1 = STATIC_SYMBOL("AVERAGE-VALUE-1",AB_package);
    mutate_global_property(Qaverage_value_1,T,Qexpiration_source_operator_p);
    Qaverage_value_2 = STATIC_SYMBOL("AVERAGE-VALUE-2",AB_package);
    mutate_global_property(Qaverage_value_2,T,Qexpiration_source_operator_p);
    Qaverage_value = STATIC_SYMBOL("AVERAGE-VALUE",AB_package);
    average_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(average_value_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qaverage_value,
	    average_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qvariable_or_parameter);
    average_value_1_i_chooser_1 = 
	    STATIC_FUNCTION(average_value_1_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qaverage_value_1,average_value_1_i_chooser_1,
	    Qpreferred_instruction_chooser);
    average_value_2_i_chooser_1 = 
	    STATIC_FUNCTION(average_value_2_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qaverage_value_2,average_value_2_i_chooser_1,
	    Qpreferred_instruction_chooser);
    average_value_1_i_emit_1 = STATIC_FUNCTION(average_value_1_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qaverage_value_1,average_value_1_i_emit_1,
	    Qstack_node_instruction_emitter);
    average_value_2_i_emit_1 = STATIC_FUNCTION(average_value_2_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qaverage_value_2,average_value_2_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_43 = STATIC_STRING("average value");
    Qending_with = STATIC_SYMBOL("ENDING-WITH",AB_package);
    string_constant_44 = 
	    STATIC_STRING("Illegal use of a truth-value in computing a history.");
    Qsimulator = STATIC_SYMBOL("SIMULATOR",AB_package);
    Qsimulated_value = STATIC_SYMBOL("SIMULATED-VALUE",AB_package);
    string_constant_45 = 
	    string_append2(STATIC_STRING("Cannot compute the ~a of ~NF during the ~NC ~\n                         ending with the collection time. ~\n                         There are no values in the history for the i"),
	    STATIC_STRING("nterval specified."));
    string_constant_46 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF during the ~NC ~\n                         ending with the collection time. ~\n                         This object is not keeping history values.");
    string_constant_47 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF between ~NC ago and ~NC ago. ~\n                         There are no values in the history for the interval specified.");
    string_constant_48 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF between ~NC ago and ~NC ago. ~\n                         This object is not keeping history values.");
    string_constant_49 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF during the last ~NC. ~\n                    There are no values in the history for the interval specified.");
    string_constant_50 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF during the last ~NC. ~\n                    This object is not keeping history values.");
    string_constant_51 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF.  There are no values in its history.");
    string_constant_52 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF.  This object is not keeping ~\n                 history values.");
    Qfuncall_average_value_1_inst = 
	    STATIC_SYMBOL("FUNCALL-AVERAGE-VALUE-1-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_average_value_1_inst,
	    STATIC_FUNCTION(funcall_average_value_1_inst,NIL,FALSE,2,2));
    Qpprint_average_value_1_instruction = 
	    STATIC_SYMBOL("PPRINT-AVERAGE-VALUE-1-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_average_value_1_instruction,
	    STATIC_FUNCTION(pprint_average_value_1_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qaverage_value_1,
	    FIX((SI_Long)49L),Qall,FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_average_value_1_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_average_value_1_instruction),
	    Qfuncall_average_value_1_inst);
    Qfuncall_average_value_2_inst = 
	    STATIC_SYMBOL("FUNCALL-AVERAGE-VALUE-2-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_average_value_2_inst,
	    STATIC_FUNCTION(funcall_average_value_2_inst,NIL,FALSE,2,2));
    Qpprint_average_value_2_instruction = 
	    STATIC_SYMBOL("PPRINT-AVERAGE-VALUE-2-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_average_value_2_instruction,
	    STATIC_FUNCTION(pprint_average_value_2_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qaverage_value_2,
	    FIX((SI_Long)50L),Qall,FIX((SI_Long)5L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_average_value_2_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_average_value_2_instruction),
	    Qfuncall_average_value_2_inst);
    Qsum_of_values_1 = STATIC_SYMBOL("SUM-OF-VALUES-1",AB_package);
    mutate_global_property(Qsum_of_values_1,T,Qexpiration_source_operator_p);
    Qsum_of_values_2 = STATIC_SYMBOL("SUM-OF-VALUES-2",AB_package);
    mutate_global_property(Qsum_of_values_2,T,Qexpiration_source_operator_p);
    Qsum_of_values = STATIC_SYMBOL("SUM-OF-VALUES",AB_package);
    sum_of_values_stack_node_converter_1 = 
	    STATIC_FUNCTION(sum_of_values_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qsum_of_values,
	    sum_of_values_stack_node_converter_1,
	    Qstack_special_form_converter);
    sum_of_values_1_i_chooser_1 = 
	    STATIC_FUNCTION(sum_of_values_1_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qsum_of_values_1,sum_of_values_1_i_chooser_1,
	    Qpreferred_instruction_chooser);
    sum_of_values_2_i_chooser_1 = 
	    STATIC_FUNCTION(sum_of_values_2_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qsum_of_values_2,sum_of_values_2_i_chooser_1,
	    Qpreferred_instruction_chooser);
    sum_of_values_1_i_emit_1 = STATIC_FUNCTION(sum_of_values_1_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qsum_of_values_1,sum_of_values_1_i_emit_1,
	    Qstack_node_instruction_emitter);
    sum_of_values_2_i_emit_1 = STATIC_FUNCTION(sum_of_values_2_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qsum_of_values_2,sum_of_values_2_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_53 = STATIC_STRING("sum of values");
    Qfuncall_sum_of_values_1_inst = 
	    STATIC_SYMBOL("FUNCALL-SUM-OF-VALUES-1-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_sum_of_values_1_inst,
	    STATIC_FUNCTION(funcall_sum_of_values_1_inst,NIL,FALSE,2,2));
    Qpprint_sum_of_values_1_instruction = 
	    STATIC_SYMBOL("PPRINT-SUM-OF-VALUES-1-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_sum_of_values_1_instruction,
	    STATIC_FUNCTION(pprint_sum_of_values_1_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qsum_of_values_1,
	    FIX((SI_Long)85L),Qall,FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_sum_of_values_1_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_sum_of_values_1_instruction),
	    Qfuncall_sum_of_values_1_inst);
    string_constant_54 = STATIC_STRING("sum of value");
    Qfuncall_sum_of_values_2_inst = 
	    STATIC_SYMBOL("FUNCALL-SUM-OF-VALUES-2-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_sum_of_values_2_inst,
	    STATIC_FUNCTION(funcall_sum_of_values_2_inst,NIL,FALSE,2,2));
    Qpprint_sum_of_values_2_instruction = 
	    STATIC_SYMBOL("PPRINT-SUM-OF-VALUES-2-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_sum_of_values_2_instruction,
	    STATIC_FUNCTION(pprint_sum_of_values_2_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qsum_of_values_2,
	    FIX((SI_Long)86L),Qall,FIX((SI_Long)5L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_sum_of_values_2_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_sum_of_values_2_instruction),
	    Qfuncall_sum_of_values_2_inst);
    Qminimum_value_1 = STATIC_SYMBOL("MINIMUM-VALUE-1",AB_package);
    mutate_global_property(Qminimum_value_1,T,Qexpiration_source_operator_p);
    Qminimum_value_2 = STATIC_SYMBOL("MINIMUM-VALUE-2",AB_package);
    mutate_global_property(Qminimum_value_2,T,Qexpiration_source_operator_p);
    Qminimum_value = STATIC_SYMBOL("MINIMUM-VALUE",AB_package);
    minimum_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(minimum_value_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qminimum_value,
	    minimum_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    minimum_value_1_i_chooser_1 = 
	    STATIC_FUNCTION(minimum_value_1_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qminimum_value_1,minimum_value_1_i_chooser_1,
	    Qpreferred_instruction_chooser);
    minimum_value_2_i_chooser_1 = 
	    STATIC_FUNCTION(minimum_value_2_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qminimum_value_2,minimum_value_2_i_chooser_1,
	    Qpreferred_instruction_chooser);
    minimum_value_1_i_emit_1 = STATIC_FUNCTION(minimum_value_1_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qminimum_value_1,minimum_value_1_i_emit_1,
	    Qstack_node_instruction_emitter);
    minimum_value_2_i_emit_1 = STATIC_FUNCTION(minimum_value_2_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qminimum_value_2,minimum_value_2_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_55 = STATIC_STRING("minimum value");
    Qfuncall_minimum_value_1_inst = 
	    STATIC_SYMBOL("FUNCALL-MINIMUM-VALUE-1-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_minimum_value_1_inst,
	    STATIC_FUNCTION(funcall_minimum_value_1_inst,NIL,FALSE,2,2));
    Qpprint_minimum_value_1_instruction = 
	    STATIC_SYMBOL("PPRINT-MINIMUM-VALUE-1-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_minimum_value_1_instruction,
	    STATIC_FUNCTION(pprint_minimum_value_1_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qminimum_value_1,
	    FIX((SI_Long)51L),Qall,FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_minimum_value_1_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_minimum_value_1_instruction),
	    Qfuncall_minimum_value_1_inst);
    Qfuncall_minimum_value_2_inst = 
	    STATIC_SYMBOL("FUNCALL-MINIMUM-VALUE-2-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_minimum_value_2_inst,
	    STATIC_FUNCTION(funcall_minimum_value_2_inst,NIL,FALSE,2,2));
    Qpprint_minimum_value_2_instruction = 
	    STATIC_SYMBOL("PPRINT-MINIMUM-VALUE-2-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_minimum_value_2_instruction,
	    STATIC_FUNCTION(pprint_minimum_value_2_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qminimum_value_2,
	    FIX((SI_Long)52L),Qall,FIX((SI_Long)5L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_minimum_value_2_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_minimum_value_2_instruction),
	    Qfuncall_minimum_value_2_inst);
    Qmaximum_value_1 = STATIC_SYMBOL("MAXIMUM-VALUE-1",AB_package);
    mutate_global_property(Qmaximum_value_1,T,Qexpiration_source_operator_p);
    Qmaximum_value_2 = STATIC_SYMBOL("MAXIMUM-VALUE-2",AB_package);
    mutate_global_property(Qmaximum_value_2,T,Qexpiration_source_operator_p);
    Qmaximum_value = STATIC_SYMBOL("MAXIMUM-VALUE",AB_package);
    maximum_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(maximum_value_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qmaximum_value,
	    maximum_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    maximum_value_1_i_chooser_1 = 
	    STATIC_FUNCTION(maximum_value_1_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qmaximum_value_1,maximum_value_1_i_chooser_1,
	    Qpreferred_instruction_chooser);
    maximum_value_2_i_chooser_1 = 
	    STATIC_FUNCTION(maximum_value_2_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qmaximum_value_2,maximum_value_2_i_chooser_1,
	    Qpreferred_instruction_chooser);
    maximum_value_1_i_emit_1 = STATIC_FUNCTION(maximum_value_1_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qmaximum_value_1,maximum_value_1_i_emit_1,
	    Qstack_node_instruction_emitter);
    maximum_value_2_i_emit_1 = STATIC_FUNCTION(maximum_value_2_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qmaximum_value_2,maximum_value_2_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_56 = STATIC_STRING("maximum value");
    Qfuncall_maximum_value_1_inst = 
	    STATIC_SYMBOL("FUNCALL-MAXIMUM-VALUE-1-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_maximum_value_1_inst,
	    STATIC_FUNCTION(funcall_maximum_value_1_inst,NIL,FALSE,2,2));
    Qpprint_maximum_value_1_instruction = 
	    STATIC_SYMBOL("PPRINT-MAXIMUM-VALUE-1-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_maximum_value_1_instruction,
	    STATIC_FUNCTION(pprint_maximum_value_1_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qmaximum_value_1,
	    FIX((SI_Long)53L),Qall,FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_maximum_value_1_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_maximum_value_1_instruction),
	    Qfuncall_maximum_value_1_inst);
    Qfuncall_maximum_value_2_inst = 
	    STATIC_SYMBOL("FUNCALL-MAXIMUM-VALUE-2-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_maximum_value_2_inst,
	    STATIC_FUNCTION(funcall_maximum_value_2_inst,NIL,FALSE,2,2));
    Qpprint_maximum_value_2_instruction = 
	    STATIC_SYMBOL("PPRINT-MAXIMUM-VALUE-2-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_maximum_value_2_instruction,
	    STATIC_FUNCTION(pprint_maximum_value_2_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qmaximum_value_2,
	    FIX((SI_Long)54L),Qall,FIX((SI_Long)5L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_maximum_value_2_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_maximum_value_2_instruction),
	    Qfuncall_maximum_value_2_inst);
    Qstandard_deviation_1 = STATIC_SYMBOL("STANDARD-DEVIATION-1",AB_package);
    mutate_global_property(Qstandard_deviation_1,T,
	    Qexpiration_source_operator_p);
    Qstandard_deviation_2 = STATIC_SYMBOL("STANDARD-DEVIATION-2",AB_package);
    mutate_global_property(Qstandard_deviation_2,T,
	    Qexpiration_source_operator_p);
    Qstandard_deviation = STATIC_SYMBOL("STANDARD-DEVIATION",AB_package);
    standard_deviation_stack_node_converter_1 = 
	    STATIC_FUNCTION(standard_deviation_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qstandard_deviation,
	    standard_deviation_stack_node_converter_1,
	    Qstack_special_form_converter);
    standard_deviation_1_i_chooser_1 = 
	    STATIC_FUNCTION(standard_deviation_1_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qstandard_deviation_1,
	    standard_deviation_1_i_chooser_1,Qpreferred_instruction_chooser);
    standard_deviation_2_i_chooser_1 = 
	    STATIC_FUNCTION(standard_deviation_2_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qstandard_deviation_2,
	    standard_deviation_2_i_chooser_1,Qpreferred_instruction_chooser);
    standard_deviation_1_i_emit_1 = 
	    STATIC_FUNCTION(standard_deviation_1_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qstandard_deviation_1,
	    standard_deviation_1_i_emit_1,Qstack_node_instruction_emitter);
    standard_deviation_2_i_emit_1 = 
	    STATIC_FUNCTION(standard_deviation_2_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qstandard_deviation_2,
	    standard_deviation_2_i_emit_1,Qstack_node_instruction_emitter);
    string_constant_57 = STATIC_STRING("standard deviation");
    Qfuncall_standard_deviation_1_inst = 
	    STATIC_SYMBOL("FUNCALL-STANDARD-DEVIATION-1-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_standard_deviation_1_inst,
	    STATIC_FUNCTION(funcall_standard_deviation_1_inst,NIL,FALSE,2,2));
    Qpprint_standard_deviation_1_instruction = 
	    STATIC_SYMBOL("PPRINT-STANDARD-DEVIATION-1-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_standard_deviation_1_instruction,
	    STATIC_FUNCTION(pprint_standard_deviation_1_instruction,NIL,
	    FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qstandard_deviation_1,
	    FIX((SI_Long)55L),Qall,FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_standard_deviation_1_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_standard_deviation_1_instruction),
	    Qfuncall_standard_deviation_1_inst);
    Qfuncall_standard_deviation_2_inst = 
	    STATIC_SYMBOL("FUNCALL-STANDARD-DEVIATION-2-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_standard_deviation_2_inst,
	    STATIC_FUNCTION(funcall_standard_deviation_2_inst,NIL,FALSE,2,2));
    Qpprint_standard_deviation_2_instruction = 
	    STATIC_SYMBOL("PPRINT-STANDARD-DEVIATION-2-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_standard_deviation_2_instruction,
	    STATIC_FUNCTION(pprint_standard_deviation_2_instruction,NIL,
	    FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qstandard_deviation_2,
	    FIX((SI_Long)56L),Qall,FIX((SI_Long)5L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_standard_deviation_2_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_standard_deviation_2_instruction),
	    Qfuncall_standard_deviation_2_inst);
    Qnumber_of_datapoints_0 = STATIC_SYMBOL("NUMBER-OF-DATAPOINTS-0",
	    AB_package);
    mutate_global_property(Qnumber_of_datapoints_0,T,
	    Qexpiration_source_operator_p);
    Qnumber_of_datapoints_1 = STATIC_SYMBOL("NUMBER-OF-DATAPOINTS-1",
	    AB_package);
    mutate_global_property(Qnumber_of_datapoints_1,T,
	    Qexpiration_source_operator_p);
    Qnumber_of_datapoints_2 = STATIC_SYMBOL("NUMBER-OF-DATAPOINTS-2",
	    AB_package);
    mutate_global_property(Qnumber_of_datapoints_2,T,
	    Qexpiration_source_operator_p);
    Qnumber_of_datapoints = STATIC_SYMBOL("NUMBER-OF-DATAPOINTS",AB_package);
    number_of_datapoints_stack_node_converter_1 = 
	    STATIC_FUNCTION(number_of_datapoints_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qnumber_of_datapoints,
	    number_of_datapoints_stack_node_converter_1,
	    Qstack_special_form_converter);
    number_of_datapoints_0_i_chooser_1 = 
	    STATIC_FUNCTION(number_of_datapoints_0_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qnumber_of_datapoints_0,
	    number_of_datapoints_0_i_chooser_1,Qpreferred_instruction_chooser);
    number_of_datapoints_1_i_chooser_1 = 
	    STATIC_FUNCTION(number_of_datapoints_1_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qnumber_of_datapoints_1,
	    number_of_datapoints_1_i_chooser_1,Qpreferred_instruction_chooser);
    number_of_datapoints_2_i_chooser_1 = 
	    STATIC_FUNCTION(number_of_datapoints_2_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qnumber_of_datapoints_2,
	    number_of_datapoints_2_i_chooser_1,Qpreferred_instruction_chooser);
    number_of_datapoints_0_i_emit_1 = 
	    STATIC_FUNCTION(number_of_datapoints_0_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qnumber_of_datapoints_0,
	    number_of_datapoints_0_i_emit_1,Qstack_node_instruction_emitter);
    number_of_datapoints_1_i_emit_1 = 
	    STATIC_FUNCTION(number_of_datapoints_1_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qnumber_of_datapoints_1,
	    number_of_datapoints_1_i_emit_1,Qstack_node_instruction_emitter);
    number_of_datapoints_2_i_emit_1 = 
	    STATIC_FUNCTION(number_of_datapoints_2_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qnumber_of_datapoints_2,
	    number_of_datapoints_2_i_emit_1,Qstack_node_instruction_emitter);
    string_constant_58 = STATIC_STRING("number of history datapoints");
    Qfuncall_number_of_datapoints_0_inst = 
	    STATIC_SYMBOL("FUNCALL-NUMBER-OF-DATAPOINTS-0-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_number_of_datapoints_0_inst,
	    STATIC_FUNCTION(funcall_number_of_datapoints_0_inst,NIL,FALSE,
	    2,2));
    Qpprint_number_of_datapoints_0_instruction = 
	    STATIC_SYMBOL("PPRINT-NUMBER-OF-DATAPOINTS-0-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_number_of_datapoints_0_instruction,
	    STATIC_FUNCTION(pprint_number_of_datapoints_0_instruction,NIL,
	    FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qnumber_of_datapoints_0,
	    FIX((SI_Long)57L),Qall,FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_number_of_datapoints_0_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_number_of_datapoints_0_instruction),
	    Qfuncall_number_of_datapoints_0_inst);
    Qfuncall_number_of_datapoints_1_inst = 
	    STATIC_SYMBOL("FUNCALL-NUMBER-OF-DATAPOINTS-1-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_number_of_datapoints_1_inst,
	    STATIC_FUNCTION(funcall_number_of_datapoints_1_inst,NIL,FALSE,
	    2,2));
    Qpprint_number_of_datapoints_1_instruction = 
	    STATIC_SYMBOL("PPRINT-NUMBER-OF-DATAPOINTS-1-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_number_of_datapoints_1_instruction,
	    STATIC_FUNCTION(pprint_number_of_datapoints_1_instruction,NIL,
	    FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qnumber_of_datapoints_1,
	    FIX((SI_Long)58L),Qall,FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_number_of_datapoints_1_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_number_of_datapoints_1_instruction),
	    Qfuncall_number_of_datapoints_1_inst);
    Qfuncall_number_of_datapoints_2_inst = 
	    STATIC_SYMBOL("FUNCALL-NUMBER-OF-DATAPOINTS-2-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_number_of_datapoints_2_inst,
	    STATIC_FUNCTION(funcall_number_of_datapoints_2_inst,NIL,FALSE,
	    2,2));
    Qpprint_number_of_datapoints_2_instruction = 
	    STATIC_SYMBOL("PPRINT-NUMBER-OF-DATAPOINTS-2-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_number_of_datapoints_2_instruction,
	    STATIC_FUNCTION(pprint_number_of_datapoints_2_instruction,NIL,
	    FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qnumber_of_datapoints_2,
	    FIX((SI_Long)59L),Qall,FIX((SI_Long)5L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_number_of_datapoints_2_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_number_of_datapoints_2_instruction),
	    Qfuncall_number_of_datapoints_2_inst);
    Qrate_of_change_1 = STATIC_SYMBOL("RATE-OF-CHANGE-1",AB_package);
    mutate_global_property(Qrate_of_change_1,T,Qexpiration_source_operator_p);
    Qrate_of_change_2 = STATIC_SYMBOL("RATE-OF-CHANGE-2",AB_package);
    mutate_global_property(Qrate_of_change_2,T,Qexpiration_source_operator_p);
    Qrate_of_change = STATIC_SYMBOL("RATE-OF-CHANGE",AB_package);
    rate_of_change_stack_node_converter_1 = 
	    STATIC_FUNCTION(rate_of_change_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qrate_of_change,
	    rate_of_change_stack_node_converter_1,
	    Qstack_special_form_converter);
    rate_of_change_1_i_chooser_1 = 
	    STATIC_FUNCTION(rate_of_change_1_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qrate_of_change_1,rate_of_change_1_i_chooser_1,
	    Qpreferred_instruction_chooser);
    rate_of_change_2_i_chooser_1 = 
	    STATIC_FUNCTION(rate_of_change_2_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qrate_of_change_2,rate_of_change_2_i_chooser_1,
	    Qpreferred_instruction_chooser);
    rate_of_change_1_i_emit_1 = STATIC_FUNCTION(rate_of_change_1_i_emit,
	    NIL,FALSE,3,3);
    mutate_global_property(Qrate_of_change_1,rate_of_change_1_i_emit_1,
	    Qstack_node_instruction_emitter);
    rate_of_change_2_i_emit_1 = STATIC_FUNCTION(rate_of_change_2_i_emit,
	    NIL,FALSE,3,3);
    mutate_global_property(Qrate_of_change_2,rate_of_change_2_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_59 = STATIC_STRING("rate of change");
    Qminute = STATIC_SYMBOL("MINUTE",AB_package);
    Qminutes = STATIC_SYMBOL("MINUTES",AB_package);
    Qhour = STATIC_SYMBOL("HOUR",AB_package);
    Qhours = STATIC_SYMBOL("HOURS",AB_package);
    Qday = STATIC_SYMBOL("DAY",AB_package);
    Qdays = STATIC_SYMBOL("DAYS",AB_package);
    Qweek = STATIC_SYMBOL("WEEK",AB_package);
    Qweeks = STATIC_SYMBOL("WEEKS",AB_package);
    string_constant_60 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF.  ~NV is an invalid time-unit.");
    string_constant_61 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF.  ~a is an invalid time unit.");
    string_constant_62 = 
	    string_append2(STATIC_STRING("Cannot compute the ~a of ~NF during the ~NC ~\n                     ending with the collection time. ~\n                     There are no values in the history for the interval "),
	    STATIC_STRING("specified."));
    string_constant_63 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF between ~NC ago and ~NC ago. ~\n                     There are no values in the history for the interval specified.");
    string_constant_64 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF during the last ~NC. ~\n                 There are no values in the history for the interval specified.");
    string_constant_65 = 
	    STATIC_STRING("Cannot compute the ~a of ~NF.  There are no values in its ~\n                 history.");
    Qfuncall_rate_of_change_1_inst = 
	    STATIC_SYMBOL("FUNCALL-RATE-OF-CHANGE-1-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_rate_of_change_1_inst,
	    STATIC_FUNCTION(funcall_rate_of_change_1_inst,NIL,FALSE,2,2));
    Qpprint_rate_of_change_1_instruction = 
	    STATIC_SYMBOL("PPRINT-RATE-OF-CHANGE-1-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_rate_of_change_1_instruction,
	    STATIC_FUNCTION(pprint_rate_of_change_1_instruction,NIL,FALSE,
	    6,6));
    make_and_register_funcalled_instruction_description(Qrate_of_change_1,
	    FIX((SI_Long)60L),Qall,FIX((SI_Long)5L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_rate_of_change_1_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_rate_of_change_1_instruction),
	    Qfuncall_rate_of_change_1_inst);
    Qfuncall_rate_of_change_2_inst = 
	    STATIC_SYMBOL("FUNCALL-RATE-OF-CHANGE-2-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_rate_of_change_2_inst,
	    STATIC_FUNCTION(funcall_rate_of_change_2_inst,NIL,FALSE,2,2));
    Qpprint_rate_of_change_2_instruction = 
	    STATIC_SYMBOL("PPRINT-RATE-OF-CHANGE-2-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_rate_of_change_2_instruction,
	    STATIC_FUNCTION(pprint_rate_of_change_2_instruction,NIL,FALSE,
	    6,6));
    make_and_register_funcalled_instruction_description(Qrate_of_change_2,
	    FIX((SI_Long)61L),Qall,FIX((SI_Long)6L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_rate_of_change_2_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_rate_of_change_2_instruction),
	    Qfuncall_rate_of_change_2_inst);
    Qintegral_1 = STATIC_SYMBOL("INTEGRAL-1",AB_package);
    mutate_global_property(Qintegral_1,T,Qexpiration_source_operator_p);
    Qintegral_2 = STATIC_SYMBOL("INTEGRAL-2",AB_package);
    mutate_global_property(Qintegral_2,T,Qexpiration_source_operator_p);
    Qintegral = STATIC_SYMBOL("INTEGRAL",AB_package);
    integral_stack_node_converter_1 = 
	    STATIC_FUNCTION(integral_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qintegral,integral_stack_node_converter_1,
	    Qstack_special_form_converter);
    integral_1_i_chooser_1 = STATIC_FUNCTION(integral_1_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qintegral_1,integral_1_i_chooser_1,
	    Qpreferred_instruction_chooser);
    integral_2_i_chooser_1 = STATIC_FUNCTION(integral_2_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qintegral_2,integral_2_i_chooser_1,
	    Qpreferred_instruction_chooser);
    integral_1_i_emit_1 = STATIC_FUNCTION(integral_1_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qintegral_1,integral_1_i_emit_1,
	    Qstack_node_instruction_emitter);
    integral_2_i_emit_1 = STATIC_FUNCTION(integral_2_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qintegral_2,integral_2_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_66 = STATIC_STRING("integral");
    Qfuncall_integral_1_inst = STATIC_SYMBOL("FUNCALL-INTEGRAL-1-INST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_integral_1_inst,
	    STATIC_FUNCTION(funcall_integral_1_inst,NIL,FALSE,2,2));
    Qpprint_integral_1_instruction = 
	    STATIC_SYMBOL("PPRINT-INTEGRAL-1-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_integral_1_instruction,
	    STATIC_FUNCTION(pprint_integral_1_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qintegral_1,
	    FIX((SI_Long)62L),Qall,FIX((SI_Long)5L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_integral_1_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_integral_1_instruction),
	    Qfuncall_integral_1_inst);
    Qfuncall_integral_2_inst = STATIC_SYMBOL("FUNCALL-INTEGRAL-2-INST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_integral_2_inst,
	    STATIC_FUNCTION(funcall_integral_2_inst,NIL,FALSE,2,2));
    Qpprint_integral_2_instruction = 
	    STATIC_SYMBOL("PPRINT-INTEGRAL-2-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_integral_2_instruction,
	    STATIC_FUNCTION(pprint_integral_2_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qintegral_2,
	    FIX((SI_Long)63L),Qall,FIX((SI_Long)6L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_integral_2_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_integral_2_instruction),
	    Qfuncall_integral_2_inst);
    Qhistoric_value = STATIC_SYMBOL("HISTORIC-VALUE",AB_package);
    mutate_global_property(Qhistoric_value,T,Qexpiration_source_operator_p);
    historic_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(historic_value_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qhistoric_value,
	    historic_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    historic_value_i_chooser_1 = STATIC_FUNCTION(historic_value_i_chooser,
	    NIL,FALSE,1,1);
    mutate_global_property(Qhistoric_value,historic_value_i_chooser_1,
	    Qpreferred_instruction_chooser);
    historic_value_i_emit_1 = STATIC_FUNCTION(historic_value_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qhistoric_value,historic_value_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_67 = 
	    STATIC_STRING("Cannot reference the value of ~NF as of ~NC ago.  ~\n              There was no value at that time.");
    Qfuncall_historic_value_inst = 
	    STATIC_SYMBOL("FUNCALL-HISTORIC-VALUE-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_historic_value_inst,
	    STATIC_FUNCTION(funcall_historic_value_inst,NIL,FALSE,2,2));
    Qpprint_historic_value_instruction = 
	    STATIC_SYMBOL("PPRINT-HISTORIC-VALUE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_historic_value_instruction,
	    STATIC_FUNCTION(pprint_historic_value_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qhistoric_value,
	    FIX((SI_Long)64L),Qall,FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_historic_value_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_historic_value_instruction),
	    Qfuncall_historic_value_inst);
    Qvalue_of_previous_datapoint = 
	    STATIC_SYMBOL("VALUE-OF-PREVIOUS-DATAPOINT",AB_package);
    mutate_global_property(Qvalue_of_previous_datapoint,T,
	    Qexpiration_source_operator_p);
    value_of_previous_datapoint_stack_node_converter_1 = 
	    STATIC_FUNCTION(value_of_previous_datapoint_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qvalue_of_previous_datapoint,
	    value_of_previous_datapoint_stack_node_converter_1,
	    Qstack_special_form_converter);
    value_of_previous_datapoint_i_chooser_1 = 
	    STATIC_FUNCTION(value_of_previous_datapoint_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qvalue_of_previous_datapoint,
	    value_of_previous_datapoint_i_chooser_1,
	    Qpreferred_instruction_chooser);
    value_of_previous_datapoint_i_emit_1 = 
	    STATIC_FUNCTION(value_of_previous_datapoint_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qvalue_of_previous_datapoint,
	    value_of_previous_datapoint_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_68 = 
	    STATIC_STRING("Cannot reference the value of ~NF as of ~d datapoints ago.  A ~\n      history datapoint must be referenced by a non-negative integer.");
    string_constant_69 = 
	    STATIC_STRING("Cannot reference the value of ~NF as of ~d datapoints ago.  ~\n            There was no value at that time.");
    Qfuncall_value_of_previous_datapoint_inst = 
	    STATIC_SYMBOL("FUNCALL-VALUE-OF-PREVIOUS-DATAPOINT-INST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_value_of_previous_datapoint_inst,
	    STATIC_FUNCTION(funcall_value_of_previous_datapoint_inst,NIL,
	    FALSE,2,2));
    Qpprint_value_of_previous_datapoint_instruction = 
	    STATIC_SYMBOL("PPRINT-VALUE-OF-PREVIOUS-DATAPOINT-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_value_of_previous_datapoint_instruction,
	    STATIC_FUNCTION(pprint_value_of_previous_datapoint_instruction,
	    NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qvalue_of_previous_datapoint,
	    FIX((SI_Long)65L),Qall,FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_value_of_previous_datapoint_inst),
	    Qnil,
	    SYMBOL_FUNCTION(Qpprint_value_of_previous_datapoint_instruction),
	    Qfuncall_value_of_previous_datapoint_inst);
    Qis_nan = STATIC_SYMBOL("IS-NAN",AB_package);
    Qeval_is_nan_in_line = STATIC_SYMBOL("EVAL-IS-NAN-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qis_nan,Qis_nan,
	    FIX((SI_Long)1L),Qall,list_constant_20,Qboolean,Nil,
	    Qeval_is_nan_in_line,T,FIX(IFIX(Base_in_line_evaluator_number) 
	    + (SI_Long)54L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)54L));
    mutate_global_or_kb_specific_property_value(Qis_nan,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    Qinterpolated_value = STATIC_SYMBOL("INTERPOLATED-VALUE",AB_package);
    mutate_global_property(Qinterpolated_value,T,
	    Qexpiration_source_operator_p);
    interpolated_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(interpolated_value_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qinterpolated_value,
	    interpolated_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    interpolated_value_i_chooser_1 = 
	    STATIC_FUNCTION(interpolated_value_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qinterpolated_value,
	    interpolated_value_i_chooser_1,Qpreferred_instruction_chooser);
    interpolated_value_i_emit_1 = 
	    STATIC_FUNCTION(interpolated_value_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qinterpolated_value,interpolated_value_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_70 = 
	    STATIC_STRING("Cannot reference the value of ~NF as of ~NC ago.  ~\n           There was no value at that time.");
    Qfuncall_interpolated_value_inst = 
	    STATIC_SYMBOL("FUNCALL-INTERPOLATED-VALUE-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_interpolated_value_inst,
	    STATIC_FUNCTION(funcall_interpolated_value_inst,NIL,FALSE,2,2));
    Qpprint_interpolated_value_instruction = 
	    STATIC_SYMBOL("PPRINT-INTERPOLATED-VALUE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_interpolated_value_instruction,
	    STATIC_FUNCTION(pprint_interpolated_value_instruction,NIL,
	    FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qinterpolated_value,
	    FIX((SI_Long)66L),Qall,FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_interpolated_value_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_interpolated_value_instruction),
	    Qfuncall_interpolated_value_inst);
    string_constant_71 = 
	    STATIC_STRING("The distance between ~NF and ~NF could not be computed, ~\n   since they were not on the same workspace.");
    Qdistance_between = STATIC_SYMBOL("DISTANCE-BETWEEN",AB_package);
    Qeval_distance_between_in_line = 
	    STATIC_SYMBOL("EVAL-DISTANCE-BETWEEN-IN-LINE",AB_package);
    Qpprint_distance_between_evaluator = 
	    STATIC_SYMBOL("PPRINT-DISTANCE-BETWEEN-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_distance_between_evaluator,
	    STATIC_FUNCTION(pprint_distance_between_evaluator,NIL,FALSE,6,6));
    register_in_line_evaluator(make_evaluator_description(Qdistance_between,
	    Qdistance_between,FIX((SI_Long)1L),list_constant_23,
	    list_constant_33,Qfloat,Nil,Qeval_distance_between_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)55L),Nil,
	    SYMBOL_FUNCTION(Qpprint_distance_between_evaluator),Nil),
	    FIX((SI_Long)55L));
    Qdistance_between_and_the_nearest = 
	    STATIC_SYMBOL("DISTANCE-BETWEEN-AND-THE-NEAREST",AB_package);
    mutate_global_property(Qdistance_between_and_the_nearest,T,
	    Qexpiration_source_operator_p);
    string_constant_72 = 
	    STATIC_STRING("Could not locate a non-active item of type ~a.");
    Qinference_engine = STATIC_SYMBOL("INFERENCE-ENGINE",AB_package);
    float_constant = STATIC_FLOAT(1.0);
    list_constant_35 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_36 = STATIC_CONS(list_constant_32,list_constant_35);
    Qeval_distance_between_and_the_nearest_funcalled = 
	    STATIC_SYMBOL("EVAL-DISTANCE-BETWEEN-AND-THE-NEAREST-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_distance_between_and_the_nearest_funcalled,
	    STATIC_FUNCTION(eval_distance_between_and_the_nearest_funcalled,
	    NIL,FALSE,2,2));
    Qpprint_distance_between_and_the_nearest_evaluator = 
	    STATIC_SYMBOL("PPRINT-DISTANCE-BETWEEN-AND-THE-NEAREST-EVALUATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_distance_between_and_the_nearest_evaluator,
	    STATIC_FUNCTION(pprint_distance_between_and_the_nearest_evaluator,
	    NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qdistance_between_and_the_nearest,
	    Qdistance_between_and_the_nearest,FIX((SI_Long)1L),
	    list_constant_23,list_constant_36,Qfloat,Qnil,
	    SYMBOL_FUNCTION(Qeval_distance_between_and_the_nearest_funcalled),
	    Nil,FIX((SI_Long)26L),Nil,
	    SYMBOL_FUNCTION(Qpprint_distance_between_and_the_nearest_evaluator),
	    Qeval_distance_between_and_the_nearest_funcalled),
	    FIX((SI_Long)26L),Funcall_eval_type_2_arg);
    Qhas_a_current_value = STATIC_SYMBOL("HAS-A-CURRENT-VALUE",AB_package);
    has_a_current_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(has_a_current_value_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qhas_a_current_value,
	    has_a_current_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    list_constant_9 = STATIC_LIST((SI_Long)5L,Qab_or,Qdatum,list_constant,
	    list_constant_7,list_constant_1);
    has_a_current_value_i_chooser_1 = 
	    STATIC_FUNCTION(has_a_current_value_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qhas_a_current_value,
	    has_a_current_value_i_chooser_1,Qpreferred_instruction_chooser);
    mutate_global_property(Qhas_a_current_value,T,
	    Qexpiration_special_form_operator_p);
    has_a_current_value_i_emit_1 = 
	    STATIC_FUNCTION(has_a_current_value_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qhas_a_current_value,
	    has_a_current_value_i_emit_1,Qstack_node_instruction_emitter);
    Qhas_no_current_value = STATIC_SYMBOL("HAS-NO-CURRENT-VALUE",AB_package);
    has_no_current_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(has_no_current_value_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qhas_no_current_value,
	    has_no_current_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qhas_a_value = STATIC_SYMBOL("HAS-A-VALUE",AB_package);
    has_a_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(has_a_value_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qhas_a_value,has_a_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    string_constant_73 = 
	    string_append2(STATIC_STRING("The HAS A VALUE expression can only be executed in contexts where ~\n         unknown can be returned, such as within a rule or a COLLECT DATA ~\n         statement in procedure"),
	    STATIC_STRING("s.  The HAS A CURRENT VALUE expression does not ~\n\t have this restriction and could be used here."));
    has_a_value_i_chooser_1 = STATIC_FUNCTION(has_a_value_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qhas_a_value,has_a_value_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qhas_a_value,T,Qexpiration_special_form_operator_p);
    has_a_value_i_emit_1 = STATIC_FUNCTION(has_a_value_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qhas_a_value,has_a_value_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qfuncall_has_a_value_inst = STATIC_SYMBOL("FUNCALL-HAS-A-VALUE-INST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_has_a_value_inst,
	    STATIC_FUNCTION(funcall_has_a_value_inst,NIL,FALSE,2,2));
    Qpprint_has_a_value_instruction = 
	    STATIC_SYMBOL("PPRINT-HAS-A-VALUE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_has_a_value_instruction,
	    STATIC_FUNCTION(pprint_has_a_value_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qhas_a_value,
	    FIX((SI_Long)35L),list_constant_23,FIX((SI_Long)2L),
	    FIX((SI_Long)1L),SYMBOL_FUNCTION(Qfuncall_has_a_value_inst),
	    Qnil,SYMBOL_FUNCTION(Qpprint_has_a_value_instruction),
	    Qfuncall_has_a_value_inst);
    Qhas_no_value = STATIC_SYMBOL("HAS-NO-VALUE",AB_package);
    has_no_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(has_no_value_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qhas_no_value,
	    has_no_value_stack_node_converter_1,Qstack_special_form_converter);
    Qcurrent_value_of = STATIC_SYMBOL("CURRENT-VALUE-OF",AB_package);
    current_value_of_stack_node_converter_1 = 
	    STATIC_FUNCTION(current_value_of_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qcurrent_value_of,
	    current_value_of_stack_node_converter_1,
	    Qstack_special_form_converter);
    list_constant_37 = STATIC_CONS(list_constant_7,Qnil);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,Qdatum,
	    list_constant,list_constant_37);
    current_value_of_i_chooser_1 = 
	    STATIC_FUNCTION(current_value_of_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qcurrent_value_of,current_value_of_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qcurrent_value_of,T,
	    Qexpiration_special_form_operator_p);
    current_value_of_i_emit_1 = STATIC_FUNCTION(current_value_of_i_emit,
	    NIL,FALSE,3,3);
    mutate_global_property(Qcurrent_value_of,current_value_of_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qvalue_of = STATIC_SYMBOL("VALUE-OF",AB_package);
    value_of_stack_node_converter_1 = 
	    STATIC_FUNCTION(value_of_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qvalue_of,value_of_stack_node_converter_1,
	    Qstack_special_form_converter);
    value_of_i_chooser_1 = STATIC_FUNCTION(value_of_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qvalue_of,value_of_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qvalue_of,T,Qexpiration_special_form_operator_p);
    value_of_i_emit_1 = STATIC_FUNCTION(value_of_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qvalue_of,value_of_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qfirst_that_has_a_current_value = 
	    STATIC_SYMBOL("FIRST-THAT-HAS-A-CURRENT-VALUE",AB_package);
    first_that_has_a_current_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(first_that_has_a_current_value_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qfirst_that_has_a_current_value,
	    first_that_has_a_current_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    list_constant_38 = STATIC_CONS(list_constant_1,Qnil);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,list_constant_7,
	    list_constant,list_constant_38);
    string_constant_74 = STATIC_STRING("~a ~a");
    string_constant_75 = 
	    STATIC_STRING("The last expression within the FIRST OF THE FOLLOWING EXPRESSIONS ");
    string_constant_76 = 
	    STATIC_STRING("THAT HAS A CURRENT VALUE must not produce an unknown value.");
    first_that_has_a_current_value_i_chooser_1 = 
	    STATIC_FUNCTION(first_that_has_a_current_value_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qfirst_that_has_a_current_value,
	    first_that_has_a_current_value_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qfirst_that_has_a_current_value,T,
	    Qexpiration_special_form_operator_p);
    first_that_has_a_current_value_i_emit_1 = 
	    STATIC_FUNCTION(first_that_has_a_current_value_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qfirst_that_has_a_current_value,
	    first_that_has_a_current_value_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qfirst_that_has_a_value = STATIC_SYMBOL("FIRST-THAT-HAS-A-VALUE",
	    AB_package);
    first_that_has_a_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(first_that_has_a_value_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qfirst_that_has_a_value,
	    first_that_has_a_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    string_constant_77 = 
	    string_append2(STATIC_STRING("The FIRST OF THE FOLLOWING EXPRESSIONS THAT HAS A VALUE expression ~\n         can only be executed in contexts where ~\n         unknown can be returned, such as within a rule "),
	    STATIC_STRING("or a COLLECT DATA ~\n         statement in procedures.  The HAS A CURRENT VALUE form of this ~\n         expression does not have this restriction and could be used here."));
    list_constant_39 = STATIC_LIST_STAR((SI_Long)3L,list_constant,
	    list_constant_7,list_constant_38);
    list_constant_12 = STATIC_CONS(Qab_or,list_constant_39);
    first_that_has_a_value_i_chooser_1 = 
	    STATIC_FUNCTION(first_that_has_a_value_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qfirst_that_has_a_value,
	    first_that_has_a_value_i_chooser_1,Qpreferred_instruction_chooser);
    mutate_global_property(Qfirst_that_has_a_value,T,
	    Qexpiration_special_form_operator_p);
    first_that_has_a_value_i_emit_1 = 
	    STATIC_FUNCTION(first_that_has_a_value_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qfirst_that_has_a_value,
	    first_that_has_a_value_i_emit_1,Qstack_node_instruction_emitter);
    Qfuncall_first_that_has_a_value_inst = 
	    STATIC_SYMBOL("FUNCALL-FIRST-THAT-HAS-A-VALUE-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_first_that_has_a_value_inst,
	    STATIC_FUNCTION(funcall_first_that_has_a_value_inst,NIL,FALSE,
	    2,2));
    Qpprint_first_that_has_a_value_instruction = 
	    STATIC_SYMBOL("PPRINT-FIRST-THAT-HAS-A-VALUE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_first_that_has_a_value_instruction,
	    STATIC_FUNCTION(pprint_first_that_has_a_value_instruction,NIL,
	    FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qfirst_that_has_a_value,
	    FIX((SI_Long)36L),list_constant_23,FIX((SI_Long)3L),
	    FIX((SI_Long)2L),
	    SYMBOL_FUNCTION(Qfuncall_first_that_has_a_value_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_first_that_has_a_value_instruction),
	    Qfuncall_first_that_has_a_value_inst);
    Qsimulated_value_of = STATIC_SYMBOL("SIMULATED-VALUE-OF",AB_package);
    mutate_global_property(Qsimulated_value_of,T,
	    Qexpiration_special_form_operator_p);
    simulated_value_of_stack_node_converter_1 = 
	    STATIC_FUNCTION(simulated_value_of_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qsimulated_value_of,
	    simulated_value_of_stack_node_converter_1,
	    Qstack_special_form_converter);
    simulated_value_of_i_chooser_1 = 
	    STATIC_FUNCTION(simulated_value_of_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qsimulated_value_of,
	    simulated_value_of_i_chooser_1,Qpreferred_instruction_chooser);
    simulated_value_of_i_emit_1 = 
	    STATIC_FUNCTION(simulated_value_of_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qsimulated_value_of,simulated_value_of_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qcount_datapoints_that_evaluate_true = 
	    STATIC_SYMBOL("COUNT-DATAPOINTS-THAT-EVALUATE-TRUE",AB_package);
    Qquantitative_parameter = STATIC_SYMBOL("QUANTITATIVE-PARAMETER",
	    AB_package);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qquantitative_parameter);
    list_constant_41 = STATIC_LIST_STAR((SI_Long)4L,list_constant_40,
	    Qinteger,Qinteger,list_constant_26);
    Qeval_count_datapoints_that_evaluate_true_in_line = 
	    STATIC_SYMBOL("EVAL-COUNT-DATAPOINTS-THAT-EVALUATE-TRUE-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qcount_datapoints_that_evaluate_true,
	    Qcount_datapoints_that_evaluate_true,FIX((SI_Long)1L),Qall,
	    list_constant_41,Qfloat,Nil,
	    Qeval_count_datapoints_that_evaluate_true_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)99L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)99L));
    mutate_global_or_kb_specific_property_value(Qcount_datapoints_that_evaluate_true,
	    FIX((SI_Long)6L),Argument_range_gkbprop);
    Qcount_datapoints_that_evaluate_true_with_eventflag = 
	    STATIC_SYMBOL("COUNT-DATAPOINTS-THAT-EVALUATE-TRUE-WITH-EVENTFLAG",
	    AB_package);
    list_constant_42 = STATIC_LIST_STAR((SI_Long)7L,list_constant_40,
	    Qinteger,Qinteger,Qnumber,list_constant_40,Qinteger,
	    list_constant_15);
    Qeval_count_datapoints_that_evaluate_true_with_eventflag_in_line = 
	    STATIC_SYMBOL("EVAL-COUNT-DATAPOINTS-THAT-EVALUATE-TRUE-WITH-EVENTFLAG-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qcount_datapoints_that_evaluate_true_with_eventflag,
	    Qcount_datapoints_that_evaluate_true_with_eventflag,
	    FIX((SI_Long)1L),Qall,list_constant_42,Qfloat,Nil,
	    Qeval_count_datapoints_that_evaluate_true_with_eventflag_in_line,
	    T,FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)103L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)103L));
    mutate_global_or_kb_specific_property_value(Qcount_datapoints_that_evaluate_true_with_eventflag,
	    FIX((SI_Long)8L),Argument_range_gkbprop);
}
