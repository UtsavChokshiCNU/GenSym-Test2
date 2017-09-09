/* gram4a.c
 * Input file:  grammar4a.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram4a.h"


/* WRITE-CONSTANT-DESIGNATION-FROM-SLOT */
Object write_constant_designation_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(198,0);
    return print_designation(value);
}

static Object Qnone;               /* none */

/* COMPILE-CONSTANT-VARIABLE-DESIGNATION?-FOR-SLOT */
Object compile_constant_variable_designation_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,1);
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
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

static Object array_constant;      /* # */

/* WRITE-CONSTANT-VARIABLE-DESIGNATION?-FROM-SLOT */
Object write_constant_variable_designation_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(198,2);
    if (value)
	return print_designation(value);
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object Qnormalized;         /* normalized */

/* COMPILE-CONSTANT-DESIGNATION-LIST?-FOR-SLOT */
Object compile_constant_designation_list_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,3);
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
	return VALUES_1(Nil);
    else if (CONSP(parse_result)) {
	if (EQ(CAR(parse_result),Qnormalized))
	    return VALUES_1(CDR(parse_result));
	else {
	    simplify_associative_list_operation_all_at_once(parse_result);
	    return VALUES_1(CDR(parse_result));
	}
    }
    else
	return VALUES_1(Qnil);
}

/* COMPILE-CONSTANT-DESIGNATION-LIST-FOR-SLOT */
Object compile_constant_designation_list_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,4);
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
    simplify_associative_list_operation_all_at_once(parse_result);
    return VALUES_1(CDR(parse_result));
}

/* COMPILE-QUANTITY-LIST-FOR-SLOT */
Object compile_quantity_list_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object quantity, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,5);
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
    simplify_associative_list_operation_all_at_once(parse_result);
    quantity = Nil;
    ab_loop_list_ = CDR(parse_result);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    quantity = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(compile_quantity_for_slot(3,quantity,Nil,
	    Nil),Nil);
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

/* COMPILE-INTEGER-LIST-FOR-SLOT */
Object compile_integer_list_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,6);
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
    simplify_associative_list_operation_all_at_once(parse_result);
    if (CONSP(parse_result))
	return VALUES_1(CDR(parse_result));
    else
	return phrase_cons(parse_result,Nil);
}

/* COMPILE-FLOAT-LIST-FOR-SLOT */
Object compile_float_list_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,7);
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
    simplify_associative_list_operation_all_at_once(parse_result);
    return VALUES_1(CDR(parse_result));
}

/* COMPILE-WHOLE-STRING-LIST-FOR-SLOT */
Object compile_whole_string_list_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,8);
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
    simplify_associative_list_operation_all_at_once(parse_result);
    return VALUES_1(CDR(parse_result));
}

/* COMPILE-TRUTH-VALUE-LIST-FOR-SLOT */
Object compile_truth_value_list_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object truth_value_phrases, remaining_truth_value_phrases, car_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,9);
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
    if (EQ(CAR(parse_result),Qnormalized))
	return VALUES_1(CDR(parse_result));
    else {
	simplify_associative_list_operation_all_at_once(parse_result);
	truth_value_phrases = CDR(parse_result);
	remaining_truth_value_phrases = truth_value_phrases;
      next_loop:
	if ( !TRUEP(remaining_truth_value_phrases))
	    goto end_loop;
	car_new_value = 
		truth_value_phrase_value(CAR(remaining_truth_value_phrases));
	M_CAR(remaining_truth_value_phrases) = car_new_value;
	remaining_truth_value_phrases = M_CDR(remaining_truth_value_phrases);
	goto next_loop;
      end_loop:
	return VALUES_1(truth_value_phrases);
	return VALUES_1(Qnil);
    }
}

/* COMPILE-SYMBOL-LIST-FOR-SLOT */
Object compile_symbol_list_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,10);
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
    simplify_associative_list_operation_all_at_once(parse_result);
    if (CONSP(parse_result))
	return VALUES_1(CDR(parse_result));
    else
	return phrase_cons(parse_result,Nil);
}

/* COMPILE-QUOTED-SYMBOL-LIST-FOR-SLOT */
Object compile_quoted_symbol_list_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,11);
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
    simplify_associative_list_operation_all_at_once(parse_result);
    return VALUES_1(CDR(parse_result));
}

/* COMPILE-LIST-OF-ITEM-AND-DATUM-CONSTANTS?-FOR-SLOT */
Object compile_list_of_item_and_datum_constants_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,12);
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
    if (EQ(CAR(parse_result),Qnormalized))
	return VALUES_1(CDR(parse_result));
    else {
	simplify_associative_list_operation_all_at_once(parse_result);
	return compile_constant_designation_or_datum_list(parse_result,Nil);
    }
}

/* COMPILE-LIST-OF-DATUM-CONSTANTS-FOR-SLOT */
Object compile_list_of_datum_constants_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,13);
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
    if (EQ(CAR(parse_result),Qnormalized))
	return VALUES_1(CDR(parse_result));
    else {
	simplify_associative_list_operation_all_at_once(parse_result);
	return compile_constant_designation_or_datum_list(parse_result,T);
    }
}

static Object Qcm;                 /* \, */

/* COMPILE-CONSTANT-DESIGNATION-OR-DATUM-LIST */
Object compile_constant_designation_or_datum_list(parse_result,datum_only_p_qm)
    Object parse_result, datum_only_p_qm;
{
    Object designation_or_datum_cons, cons_value, cdr_new_value;
    Object cons_pointer_for_splice, symbol_element, ab_loop_list_;
    Object new_symbol_element, top_level_cons, previous_top_level_cons;
    Object ab_loop_iter_flag_;

    x_note_fn_call(198,14);
    designation_or_datum_cons = CDR(parse_result);
    cons_value = Nil;
  next_loop:
    if ( !TRUEP(designation_or_datum_cons))
	goto end_loop;
    cons_value = CAR(designation_or_datum_cons);
    if (EQ(cons_value,Qnone))
	M_CAR(designation_or_datum_cons) = Nil;
    else if (truth_value_phrase_p(cons_value)) {
	cdr_new_value = phrase_cons(CDR(cons_value),Nil);
	M_CDR(cons_value) = cdr_new_value;
	M_CAR(designation_or_datum_cons) = cons_value;
    }
    else if (SYMBOLP(cons_value) || phrase_number_p(cons_value) || 
	    text_string_p(cons_value));
    else if (ATOM(cons_value));
    else if (EQ(CAR(cons_value),Qcm)) {
	cons_pointer_for_splice = CDR(designation_or_datum_cons);
	symbol_element = Nil;
	ab_loop_list_ = CDR(cons_value);
	new_symbol_element = Nil;
	top_level_cons = designation_or_datum_cons;
	previous_top_level_cons = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	symbol_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	new_symbol_element = datum_only_p_qm ? symbol_element : 
		phrase_list_2(Symbol_initial_value_marker,symbol_element);
	if ( !TRUEP(ab_loop_iter_flag_))
	    top_level_cons = phrase_cons(new_symbol_element,Nil);
	if ( !TRUEP(previous_top_level_cons))
	    M_CAR(designation_or_datum_cons) = new_symbol_element;
	else
	    M_CDR(previous_top_level_cons) = top_level_cons;
	previous_top_level_cons = top_level_cons;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:
	M_CDR(previous_top_level_cons) = cons_pointer_for_splice;
    }
    else if (slot_value_number_p(CAR(cons_value)));
    else;
    designation_or_datum_cons = M_CDR(designation_or_datum_cons);
    goto next_loop;
  end_loop:;
    return VALUES_1(CDR(parse_result));
}

/* WRITE-CONSTANT-DESIGNATION-LIST?-FROM-SLOT */
Object write_constant_designation_list_qm_from_slot(constant_designation_list_qm,
	    frame)
    Object constant_designation_list_qm, frame;
{
    x_note_fn_call(198,15);
    if ( !TRUEP(constant_designation_list_qm))
	return twrite(Qnone);
    else
	return print_item_and_datum_constant_list(2,
		constant_designation_list_qm,frame);
}

/* WRITE-CONSTANT-DESIGNATION-LIST-FROM-SLOT */
Object write_constant_designation_list_from_slot(constant_designation_list,
	    gensymed_symbol)
    Object constant_designation_list, gensymed_symbol;
{
    x_note_fn_call(198,16);
    return print_designation_list(constant_designation_list);
}

/* WRITE-QUANTITY-LIST-FROM-SLOT */
Object write_quantity_list_from_slot(number_list,frame)
    Object number_list, frame;
{
    x_note_fn_call(198,17);
    if ( !TRUEP(number_list))
	return twrite(Qnone);
    else
	return print_item_and_datum_constant_list(2,number_list,frame);
}

/* WRITE-INTEGER-LIST-FROM-SLOT */
Object write_integer_list_from_slot(integer_list,frame)
    Object integer_list, frame;
{
    x_note_fn_call(198,18);
    if ( !TRUEP(integer_list))
	return twrite(Qnone);
    else
	return print_item_and_datum_constant_list(2,integer_list,frame);
}

/* WRITE-FLOAT-LIST-FROM-SLOT */
Object write_float_list_from_slot(float_list,frame)
    Object float_list, frame;
{
    x_note_fn_call(198,19);
    if ( !TRUEP(float_list))
	return twrite(Qnone);
    else
	return print_item_and_datum_constant_list(2,float_list,frame);
}

/* WRITE-WHOLE-STRING-LIST-FROM-SLOT */
Object write_whole_string_list_from_slot(whole_string_list,frame)
    Object whole_string_list, frame;
{
    x_note_fn_call(198,20);
    if ( !TRUEP(whole_string_list))
	return twrite(Qnone);
    else
	return print_item_and_datum_constant_list(2,whole_string_list,frame);
}

/* WRITE-TRUTH-VALUE-LIST-FROM-SLOT */
Object write_truth_value_list_from_slot(truth_value_list,frame)
    Object truth_value_list, frame;
{
    x_note_fn_call(198,21);
    if ( !TRUEP(truth_value_list))
	return twrite(Qnone);
    else
	return print_item_and_datum_constant_list(2,truth_value_list,frame);
}

/* WRITE-SYMBOL-LIST-FROM-SLOT */
Object write_symbol_list_from_slot(symbol_list,frame)
    Object symbol_list, frame;
{
    x_note_fn_call(198,22);
    if ( !TRUEP(symbol_list))
	return twrite(Qnone);
    else
	return print_item_and_datum_constant_list(2,symbol_list,frame);
}

/* WRITE-QUOTED-SYMBOL-LIST-FROM-SLOT */
Object write_quoted_symbol_list_from_slot(symbol_list,gensymed_symbol)
    Object symbol_list, gensymed_symbol;
{
    x_note_fn_call(198,23);
    return print_quoted_symbol_list(symbol_list);
}

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object string_constant;     /* "and" */

/* PRINT-QUOTED-SYMBOL-LIST */
Object print_quoted_symbol_list(symbol_list)
    Object symbol_list;
{
    x_note_fn_call(198,24);
    if (CDR(symbol_list))
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)12L));
    else
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)11L));
    return write_list_in_chicago_style(2,symbol_list,string_constant);
}

static Object array_constant_3;    /* # */

/* PRINT-DESIGNATION-LIST */
Object print_designation_list(designation_list)
    Object designation_list;
{
    Object designations;

    x_note_fn_call(198,25);
    designations = designation_list;
  next_loop:
    if ( !TRUEP(designations))
	goto end_loop;
    print_designation(FIRST(designations));
    if (CDR(designations))
	twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)2L));
    designations = M_CDR(designations);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PRINT-CONSTANT-LIST */
Object print_constant_list(constant_list,constant_type)
    Object constant_list, constant_type;
{
    Object constant_values;

    x_note_fn_call(198,26);
    constant_values = constant_list;
  next_loop:
    if ( !TRUEP(constant_values))
	goto end_loop;
    print_constant(2,FIRST(constant_values),constant_type);
    if (CDR(constant_values))
	twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)2L));
    constant_values = M_CDR(constant_values);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* WRITE-LIST-OF-ITEM-AND-DATUM-CONSTANTS?-FROM-SLOT */
Object write_list_of_item_and_datum_constants_qm_from_slot(constant_or_datum_designation_list_qm,
	    frame)
    Object constant_or_datum_designation_list_qm, frame;
{
    x_note_fn_call(198,27);
    if ( !TRUEP(constant_or_datum_designation_list_qm))
	return twrite(Qnone);
    else
	return print_item_and_datum_constant_list(2,
		constant_or_datum_designation_list_qm,frame);
}

/* WRITE-LIST-OF-DATUM-CONSTANTS-FROM-SLOT */
Object write_list_of_datum_constants_from_slot(constant_designation_list_qm,
	    frame)
    Object constant_designation_list_qm, frame;
{
    x_note_fn_call(198,28);
    if ( !TRUEP(constant_designation_list_qm))
	return twrite(Qnone);
    else
	return print_item_and_datum_constant_list(2,
		constant_designation_list_qm,frame);
}

static Object Qvalue_array;        /* value-array */

static Object string_constant_1;   /* "the symbol ~a" */

static Object Qsymbol_array;       /* symbol-array */

static Object Qtruth_value_array;  /* truth-value-array */

static Object Qtruth_value;        /* truth-value */

/* PRINT-ITEM-AND-DATUM-CONSTANT-LIST */
Object print_item_and_datum_constant_list varargs_1(int, n)
{
    Object item_and_datum_constant_list;
    Object frame_qm, cons_of_list, item_datum_or_marked_symbol;
    Object immediately_preceeding_symbol_count, temp;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,29);
    INIT_ARGS_nonrelocating();
    item_and_datum_constant_list = REQUIRED_ARG_nonrelocating();
    frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    cons_of_list = item_and_datum_constant_list;
    item_datum_or_marked_symbol = Nil;
    immediately_preceeding_symbol_count = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(cons_of_list))
	goto end_loop;
    item_datum_or_marked_symbol = CAR(cons_of_list);
    if (SYMBOLP(item_datum_or_marked_symbol) && frame_qm && 
	    EQ(get_foundation_class_for_class(ISVREF(ISVREF(frame_qm,
	    (SI_Long)1L),(SI_Long)1L)),Qvalue_array)) {
	tformat(2,string_constant_1,item_datum_or_marked_symbol);
	if (CDR(cons_of_list))
	    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)2L));
    }
    else {
	if (CONSP(item_datum_or_marked_symbol)) {
	    temp = M_CAR(item_datum_or_marked_symbol);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ((temp_1 ?  !TRUEP(M_CDR(M_CAR(item_datum_or_marked_symbol))) : 
		TRUEP(Nil)) ? EQ(M_CAR(M_CAR(item_datum_or_marked_symbol)),
		Symbol_initial_value_marker_symbol) : TRUEP(Nil)) {
	    if (frame_qm && 
		    EQ(get_foundation_class_for_class(ISVREF(ISVREF(frame_qm,
		    (SI_Long)1L),(SI_Long)1L)),Qsymbol_array))
		print_item_or_datum_constant(M_CAR(M_CDR(item_datum_or_marked_symbol)));
	    else
		tformat(2,string_constant_1,
			M_CAR(M_CDR(item_datum_or_marked_symbol)));
	    if (CDR(cons_of_list))
		twrite_beginning_of_wide_string(array_constant_3,
			FIX((SI_Long)2L));
	}
	else if (frame_qm && 
		EQ(get_foundation_class_for_class(ISVREF(ISVREF(frame_qm,
		(SI_Long)1L),(SI_Long)1L)),Qtruth_value_array)) {
	    print_constant(2,item_datum_or_marked_symbol,Qtruth_value);
	    if (CDR(cons_of_list))
		twrite_beginning_of_wide_string(array_constant_3,
			FIX((SI_Long)2L));
	}
	else {
	    print_item_or_datum_constant(item_datum_or_marked_symbol);
	    if (CDR(cons_of_list))
		twrite_beginning_of_wide_string(array_constant_3,
			FIX((SI_Long)2L));
	    immediately_preceeding_symbol_count = FIX((SI_Long)0L);
	}
    }
    cons_of_list = M_CDR(cons_of_list);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PRINT-DATUM-CONSTANT-LIST */
Object print_datum_constant_list(datum_constant_list)
    Object datum_constant_list;
{
    Object cons_of_list, datum_element, immediately_preceeding_symbol_count;

    x_note_fn_call(198,30);
    cons_of_list = datum_constant_list;
    datum_element = Nil;
    immediately_preceeding_symbol_count = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(cons_of_list))
	goto end_loop;
    datum_element = CAR(cons_of_list);
    if (SYMBOLP(datum_element)) {
	tformat(2,string_constant_1,datum_element);
	if (CDR(cons_of_list))
	    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)2L));
    }
    else {
	print_item_or_datum_constant(datum_element);
	if (CDR(cons_of_list))
	    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)2L));
	immediately_preceeding_symbol_count = FIX((SI_Long)0L);
    }
    cons_of_list = M_CDR(cons_of_list);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_2;   /* "~s" */

static Object Qiteration_state;    /* iteration-state */

/* PRINT-ITEM-OR-DATUM-CONSTANT */
Object print_item_or_datum_constant(item_or_datum_constant)
    Object item_or_datum_constant;
{
    Object car_1, cdr_1, temp, gensymed_symbol, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(198,31);
    if ( !TRUEP(item_or_datum_constant))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(item_or_datum_constant) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_constant)) == 
	    (SI_Long)1L)
	return print_constant(2,item_or_datum_constant,Qnumber);
    else if (slot_value_number_p(item_or_datum_constant))
	return print_constant(2,item_or_datum_constant,Qnumber);
    else if (SYMBOLP(item_or_datum_constant))
	return print_constant(2,item_or_datum_constant,Qsymbol);
    else if (text_string_p(item_or_datum_constant))
	return tformat(2,string_constant_2,item_or_datum_constant);
    else {
	if (CONSP(item_or_datum_constant)) {
	    car_1 = M_CAR(item_or_datum_constant);
	    cdr_1 = M_CDR(item_or_datum_constant);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return print_constant(2,M_CAR(item_or_datum_constant),
		    M_CAR(M_CDR(item_or_datum_constant)));
	else {
	    gensymed_symbol = item_or_datum_constant;
	    temp_1 = FIXNUMP(gensymed_symbol);
	    if (temp_1);
	    else
		temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp_1);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp_1 = EQ(gensymed_symbol,Qtruth_value);
		if (temp_1);
		else
		    temp_1 = EQ(gensymed_symbol,Qiteration_state);
		if (temp_1);
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
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
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
		    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		return write_evaluation_value(1,item_or_datum_constant);
	    else
		return print_designation(item_or_datum_constant);
	}
    }
}

static Object array_constant_4;    /* # */

static Object string_constant_3;   /* "This value is greater than the maximum g2-array length." */

/* COMPILE-G2-ARRAY-LENGTH-FOR-SLOT */
Object compile_g2_array_length_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(198,32);
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
    if (IFIX(parse_result) < (SI_Long)0L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_4,
		FIX((SI_Long)42L));
	return VALUES_2(temp,temp_1);
    }
    else if (FIXNUM_GT(parse_result,G2_array_length_maximum)) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_3);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(parse_result);
}

/* WRITE-G2-ARRAY-LENGTH-FROM-SLOT */
Object write_g2_array_length_from_slot(n_1,gensymed_symbol)
    Object n_1, gensymed_symbol;
{
    x_note_fn_call(198,33);
    return twrite(n_1);
}

/* REPARSE-NTH-ELEMENT-DESIGNATION */
Object reparse_nth_element_designation(parse)
    Object parse;
{
    Object gensymed_symbol, quantifier, role, domain, expression;

    x_note_fn_call(198,34);
    gensymed_symbol = parse;
    quantifier = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    role = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    domain = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expression = CAR(gensymed_symbol);
    return reparse_nth_element_designation_1(quantifier,role,domain,
	    expression);
}

static Object Qobt;                /* [ */

/* REPARSE-NTH-ELEMENT-DESIGNATION-1 */
Object reparse_nth_element_designation_1(quantifier,role,construct,destruct)
    Object quantifier, role, construct, destruct;
{
    Object temp;

    x_note_fn_call(198,35);
    if (EQ(CAR(destruct),Qobt))
	return phrase_list_4(quantifier,role,construct,SECOND(destruct));
    else {
	temp = CAR(destruct);
	if (CONSP(temp) && EQ(CAAR(destruct),Qobt)) {
	    if ( !TRUEP(CDR(destruct))) {
		temp = FIRST(destruct);
		return phrase_list_4(quantifier,role,construct,SECOND(temp));
	    }
	    else {
		temp = FIRST(destruct);
		return reparse_nth_element_designation_1(quantifier,role,
			phrase_list_4(quantifier,role,construct,
			SECOND(temp)),SECOND(destruct));
	    }
	}
	else
	    return VALUES_1(Qnil);
    }
}

/* INITIAL-EVALUATION-ATTRIBUTES */
Object initial_evaluation_attributes(class_1)
    Object class_1;
{
    x_note_fn_call(198,36);
    return VALUES_1(Nil);
}

/* GET-EVALUATION-ATTRIBUTES */
Object get_evaluation_attributes(item)
    Object item;
{
    Object structure;

    x_note_fn_call(198,37);
    structure = allocate_evaluation_structure(Nil);
    add_5_dot_0_evaluation_settings(item,structure);
    return VALUES_1(structure);
}

static Object Qmay_run_while_inactive;  /* may-run-while-inactive */

static Object Qmay_refer_to_inactive_items;  /* may-refer-to-inactive-items */

static Object Qframe_flags;        /* frame-flags */

/* SET-EVALUATION-ATTRIBUTES */
Object set_evaluation_attributes(item,new_value)
    Object item, new_value;
{
    Object runs_while_inactive_qm, refers_to_inactive_items_qm, frame_flags;

    x_note_fn_call(198,38);
    if (new_value) {
	runs_while_inactive_qm = estructure_slot(new_value,
		Qmay_run_while_inactive,Nil);
	refers_to_inactive_items_qm = estructure_slot(new_value,
		Qmay_refer_to_inactive_items,Nil);
	frame_flags = ISVREF(item,(SI_Long)4L);
	frame_flags = runs_while_inactive_qm && 
		evaluation_truth_value_true_p(runs_while_inactive_qm) ? 
		FIXNUM_LOGIOR(frame_flags,Runs_while_inactive_flag) : 
		FIX(IFIX(frame_flags) &  ~IFIX(Runs_while_inactive_flag));
	frame_flags = refers_to_inactive_items_qm && 
		evaluation_truth_value_true_p(refers_to_inactive_items_qm) 
		? FIXNUM_LOGIOR(frame_flags,
		May_refer_to_inactive_items_flag) : FIX(IFIX(frame_flags) 
		&  ~IFIX(May_refer_to_inactive_items_flag));
	change_slot_value(3,item,Qframe_flags,frame_flags);
    }
    return VALUES_1(Nil);
}

static Object Qfloat_array;        /* float-array */

/* ADD-5.0-EVALUATION-SETTINGS */
Object add_5_dot_0_evaluation_settings(item,structure)
    Object item, structure;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_1, temp_2;
    Object amf_result, new_float, gensymed_symbol;
    char value;
    double aref_new_value;

    x_note_fn_call(198,39);
    value = (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)33554432L);
    if (FIXNUMP(value ? T : Nil))
	temp = value ? T : Nil;
    else if ( !value)
	temp = Evaluation_false_value;
    else if (EQ(value ? T : Nil,T))
	temp = Evaluation_true_value;
    else if (SYMBOLP(value ? T : Nil))
	temp = value ? T : Nil;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value ? T : Nil) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value ? T : Nil)) == (SI_Long)1L)
	temp = copy_managed_float(value ? T : Nil);
    else if (FLOATP(value ? T : Nil)) {
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
	temp = value ? T : Nil;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp = new_float;
    }
    else if (INLINE_LONG_VECTOR_P(value ? T : Nil) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value ? T : Nil)) == (SI_Long)1L)
	temp = copy_managed_long(value ? T : Nil);
    else if (INLINE_LONG_P(value ? T : Nil) != (SI_Long)0L)
	temp = make_evaluation_long(value ? T : Nil);
    else if (text_string_p(value ? T : Nil))
	temp = copy_as_wide_string(value ? T : Nil);
    else if (CONSP(value ? T : Nil) && EQ(M_CDR(value ? T : Nil),
		Qtruth_value)) {
	gensymed_symbol = M_CAR(value ? T : Nil);
	if (FIXNUM_EQ(gensymed_symbol,Truth))
	    temp = Evaluation_true_value;
	else if (FIXNUM_EQ(gensymed_symbol,Falsity))
	    temp = Evaluation_false_value;
	else
	    temp = eval_cons_1(gensymed_symbol,Qtruth_value);
    }
    else
	temp = error((SI_Long)2L,
		"Bad type ~a for make-evaluation-value-based-on-type.",
		type_of(value ? T : Nil));
    set_evaluation_structure_slot(structure,Qmay_refer_to_inactive_items,temp);
    value = (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)16777216L);
    if (FIXNUMP(value ? T : Nil))
	temp = value ? T : Nil;
    else if ( !value)
	temp = Evaluation_false_value;
    else if (EQ(value ? T : Nil,T))
	temp = Evaluation_true_value;
    else if (SYMBOLP(value ? T : Nil))
	temp = value ? T : Nil;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value ? T : Nil) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value ? T : Nil)) == (SI_Long)1L)
	temp = copy_managed_float(value ? T : Nil);
    else if (FLOATP(value ? T : Nil)) {
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
	temp = value ? T : Nil;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp = new_float;
    }
    else if (INLINE_LONG_VECTOR_P(value ? T : Nil) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value ? T : Nil)) == (SI_Long)1L)
	temp = copy_managed_long(value ? T : Nil);
    else if (INLINE_LONG_P(value ? T : Nil) != (SI_Long)0L)
	temp = make_evaluation_long(value ? T : Nil);
    else if (text_string_p(value ? T : Nil))
	temp = copy_as_wide_string(value ? T : Nil);
    else if (CONSP(value ? T : Nil) && EQ(M_CDR(value ? T : Nil),
		Qtruth_value)) {
	gensymed_symbol = M_CAR(value ? T : Nil);
	if (FIXNUM_EQ(gensymed_symbol,Truth))
	    temp = Evaluation_true_value;
	else if (FIXNUM_EQ(gensymed_symbol,Falsity))
	    temp = Evaluation_false_value;
	else
	    temp = eval_cons_1(gensymed_symbol,Qtruth_value);
    }
    else
	temp = error((SI_Long)2L,
		"Bad type ~a for make-evaluation-value-based-on-type.",
		type_of(value ? T : Nil));
    set_evaluation_structure_slot(structure,Qmay_run_while_inactive,temp);
    return VALUES_1(Nil);
}

/* BREAKDOWN-TRACING-AND-BREAKPOINTS-LEVELS */
Object breakdown_tracing_and_breakpoints_levels(value)
    Object value;
{
    Object warning_level, tracing_level, breakpoint_level_1;
    SI_Long gensymed_symbol;

    x_note_fn_call(198,40);
    if (value) {
	warning_level = ash(FIX(IFIX(value) & (SI_Long)15L),FIX((SI_Long)0L));
	gensymed_symbol = IFIX(value) & (SI_Long)240L;
	tracing_level = ash(FIX(gensymed_symbol),FIX((SI_Long)-4L));
	breakpoint_level_1 = ash(FIX(IFIX(value) & (SI_Long)3840L),
		FIX((SI_Long)-8L));
	return VALUES_3(FIXNUM_EQ(tracing_level,Message_field_mask) ? Nil :
		 tracing_level,FIXNUM_EQ(warning_level,Message_field_mask) 
		? Nil : warning_level,FIXNUM_EQ(breakpoint_level_1,
		Message_field_mask) ? Nil : breakpoint_level_1);
    }
    else
	return VALUES_3(Nil,Nil,Nil);
}

static Object Qtracing_and_breakpoints;  /* tracing-and-breakpoints */

static Object Qbreak_message_level;  /* break-message-level */

/* ADD-TRACING-AND-BREAKPOINT-EVALUATION-SETTINGS */
Object add_tracing_and_breakpoint_evaluation_settings(item,structure)
    Object item, structure;
{
    Object tracing_level, warning_level, breakpoint_level;
    Declare_special(1);
    Object result;

    x_note_fn_call(198,41);
    result = breakdown_tracing_and_breakpoints_levels(get_lookup_slot_value(item,
	    Qtracing_and_breakpoints));
    MVS_3(result,tracing_level,warning_level,breakpoint_level);
    PUSH_SPECIAL_WITH_SYMBOL(Breakpoint_level,Qbreakpoint_level,breakpoint_level,
	    0);
      set_evaluation_structure_slot(structure,Qbreak_message_level,
	      Breakpoint_level);
      set_evaluation_structure_slot(structure,Qtracing_message_level,
	      tracing_level);
      set_evaluation_structure_slot(structure,Qwarning_message_level,
	      warning_level);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qpart_feature;       /* part-feature */

/* GET-NEW-TABLE-EVALUATION-ATTRIBUTES */
Object get_new_table_evaluation_attributes(new_table)
    Object new_table;
{
    Object default_evaluation_setting, feature_name, feature_value;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, gensymed_symbol, feature_list, structure;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(198,42);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,0);
      default_evaluation_setting = ISVREF(New_table,(SI_Long)20L);
      feature_name = Nil;
      feature_value = Nil;
      ab_loop_list_ = CDR(default_evaluation_setting);
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
    next_loop:
      feature_name = CAR(ab_loop_list_);
      temp = CDR(ab_loop_list_);
      feature_value = CAR(temp);
      ab_loopvar__2 = eval_cons_1(get_user_spelling(feature_name,
	      Qpart_feature),Nil);
      if (ab_loopvar__1)
	  M_CDR(ab_loopvar__1) = ab_loopvar__2;
      else
	  ab_loopvar_ = ab_loopvar__2;
      ab_loopvar__1 = ab_loopvar__2;
      if (FIXNUMP(feature_value))
	  temp = feature_value;
      else if ( !TRUEP(feature_value))
	  temp = Evaluation_false_value;
      else if (EQ(feature_value,T))
	  temp = Evaluation_true_value;
      else if (SYMBOLP(feature_value))
	  temp = feature_value;
      else if (INLINE_DOUBLE_FLOAT_VECTOR_P(feature_value) != (SI_Long)0L 
	      && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(feature_value)) == (SI_Long)1L)
	  temp = copy_managed_float(feature_value);
      else if (FLOATP(feature_value)) {
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
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(feature_value);
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	  temp = new_float;
      }
      else if (INLINE_LONG_VECTOR_P(feature_value) != (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(feature_value)) == (SI_Long)1L)
	  temp = copy_managed_long(feature_value);
      else if (INLINE_LONG_P(feature_value) != (SI_Long)0L)
	  temp = make_evaluation_long(feature_value);
      else if (text_string_p(feature_value))
	  temp = copy_as_wide_string(feature_value);
      else if (CONSP(feature_value) && EQ(M_CDR(feature_value),Qtruth_value)) {
	  gensymed_symbol = M_CAR(feature_value);
	  if (FIXNUM_EQ(gensymed_symbol,Truth))
	      temp = Evaluation_true_value;
	  else if (FIXNUM_EQ(gensymed_symbol,Falsity))
	      temp = Evaluation_false_value;
	  else
	      temp = eval_cons_1(gensymed_symbol,Qtruth_value);
      }
      else
	  temp = error((SI_Long)2L,
		  "Bad type ~a for make-evaluation-value-based-on-type.",
		  type_of(feature_value));
      ab_loopvar__2 = eval_cons_1(temp,Nil);
      if (ab_loopvar__1)
	  M_CDR(ab_loopvar__1) = ab_loopvar__2;
      else
	  ab_loopvar_ = ab_loopvar__2;
      ab_loopvar__1 = ab_loopvar__2;
      ab_loop_list_ = CDDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      goto next_loop;
    end_loop:
      feature_list = ab_loopvar_;
      goto end_1;
      feature_list = Qnil;
    end_1:;
      structure = allocate_evaluation_structure(feature_list);
      add_5_dot_0_evaluation_settings(New_table,structure);
      result = VALUES_1(structure);
    POP_SPECIAL();
    return result;
}

/* GET-PROCEDURE-EVALUATION-ATTRIBUTES */
Object get_procedure_evaluation_attributes(procedure)
    Object procedure;
{
    Object structure;

    x_note_fn_call(198,43);
    structure = allocate_evaluation_structure(Nil);
    add_5_dot_0_evaluation_settings(procedure,structure);
    add_tracing_and_breakpoint_evaluation_settings(procedure,structure);
    return VALUES_1(structure);
}

/* GET-SIMULATION-SUBTABLE-EVALUATION-ATTRIBUTES */
Object get_simulation_subtable_evaluation_attributes(subtable)
    Object subtable;
{
    Object structure;

    x_note_fn_call(198,44);
    structure = allocate_evaluation_structure(Nil);
    add_5_dot_0_evaluation_settings(subtable,structure);
    add_tracing_and_breakpoint_evaluation_settings(subtable,structure);
    return VALUES_1(structure);
}

static Object Qpriority;           /* priority */

static Object Qscan_interval;      /* scan-interval */

static Object Qmay_request_event_updates;  /* may-request-event-updates */

static Object Qmay_request_data_seeking;  /* may-request-data-seeking */

static Object Qmay_provide_data_on_request;  /* may-provide-data-on-request */

static Object Qmay_provide_event_updates;  /* may-provide-event-updates */

/* GET-RULE-EVALUATION-ATTRIBUTES */
Object get_rule_evaluation_attributes(rule)
    Object rule;
{
    Object temp, evaluation_quantity, temp_1, temp_2, temp_3, structure;

    x_note_fn_call(198,45);
    temp = eval_list_2(Qpriority,ISVREF(rule,(SI_Long)26L));
    if (ISVREF(rule,(SI_Long)20L)) {
	evaluation_quantity = ISVREF(rule,(SI_Long)20L);
	if (FIXNUMP(evaluation_quantity))
	    temp_1 = evaluation_quantity;
	else if (INLINE_LONG_VECTOR_P(evaluation_quantity) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity)) == 
		(SI_Long)1L)
	    temp_1 = copy_managed_long(evaluation_quantity);
	else
	    temp_1 = copy_managed_float(evaluation_quantity);
	temp_2 = eval_list_2(Qscan_interval,temp_1);
    }
    else
	temp_2 = Nil;
    temp_3 = eval_list_2(Qmay_request_event_updates,(SI_Long)0L != 
	    (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)8L) ? 
	    Evaluation_true_value : Evaluation_false_value);
    temp_1 = eval_list_2(Qmay_request_data_seeking,(SI_Long)0L != 
	    (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)16L) ? 
	    Evaluation_true_value : Evaluation_false_value);
    structure = allocate_evaluation_structure(nconc2(temp,nconc2(temp_2,
	    nconc2(temp_3,nconc2(temp_1,
	    nconc2(eval_list_2(Qmay_provide_data_on_request,(SI_Long)0L != 
	    (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)2L) ? 
	    Evaluation_true_value : Evaluation_false_value),
	    eval_list_2(Qmay_provide_event_updates,(SI_Long)0L != 
	    (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)32768L) ? 
	    Evaluation_true_value : Evaluation_false_value)))))));
    add_5_dot_0_evaluation_settings(rule,structure);
    add_tracing_and_breakpoint_evaluation_settings(rule,structure);
    return VALUES_1(structure);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qab_structure;       /* structure */

/* GET-GENERIC-ACTION-BUTTON-EVALUATION-ATTRIBUTES */
Object get_generic_action_button_evaluation_attributes(generic_action_button)
    Object generic_action_button;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    Object structure;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(198,46);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qpriority;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qpriority;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = action_button_priority_function(generic_action_button);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = action_button_priority_function(generic_action_button);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    structure = eval_cons_1(gensymed_symbol,Qab_structure);
    add_5_dot_0_evaluation_settings(generic_action_button,structure);
    return VALUES_1(structure);
}

static Object Quser_menu_choice_priority;  /* user-menu-choice-priority */

/* GET-USER-MENU-CHOICE-EVALUATION-ATTRIBUTES */
Object get_user_menu_choice_evaluation_attributes(user_menu_choice)
    Object user_menu_choice;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    Object structure;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(198,47);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qpriority;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qpriority;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = get_lookup_slot_value(user_menu_choice,
		Quser_menu_choice_priority);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = get_lookup_slot_value(user_menu_choice,
		Quser_menu_choice_priority);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    structure = eval_cons_1(gensymed_symbol,Qab_structure);
    add_5_dot_0_evaluation_settings(user_menu_choice,structure);
    return VALUES_1(structure);
}

static Object Qdisplay_update_priority;  /* display-update-priority */

static Object Qdisplay_update_interval;  /* display-update-interval */

static Object Qdisplay_wait_interval;  /* display-wait-interval */

static Object Qinitial_scan_wait_interval;  /* initial-scan-wait-interval */

/* GET-DISPLAY-EVALUATION-ATTRIBUTES */
Object get_display_evaluation_attributes(display)
    Object display;
{
    Object temp, display_update_interval_qm, temp_1, display_wait_interval_qm;
    Object temp_2, structure;

    x_note_fn_call(198,48);
    temp = eval_list_2(Qpriority,get_lookup_slot_value(display,
	    Qdisplay_update_priority));
    if (get_lookup_slot_value(display,Qdisplay_update_interval)) {
	display_update_interval_qm = get_lookup_slot_value(display,
		Qdisplay_update_interval);
	temp_1 = eval_list_2(Qscan_interval,
		INLINE_DOUBLE_FLOAT_VECTOR_P(display_update_interval_qm) 
		!= (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(display_update_interval_qm)) 
		== (SI_Long)1L ? 
		copy_managed_float(display_update_interval_qm) : 
		display_update_interval_qm);
    }
    else
	temp_1 = Nil;
    if (get_lookup_slot_value(display,Qdisplay_wait_interval)) {
	display_wait_interval_qm = get_lookup_slot_value(display,
		Qdisplay_wait_interval);
	temp_2 = eval_list_2(Qinitial_scan_wait_interval,
		INLINE_DOUBLE_FLOAT_VECTOR_P(display_wait_interval_qm) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(display_wait_interval_qm)) 
		== (SI_Long)1L ? 
		copy_managed_float(display_wait_interval_qm) : 
		display_wait_interval_qm);
    }
    else
	temp_2 = Nil;
    structure = allocate_evaluation_structure(nconc2(temp,nconc2(temp_1,
	    temp_2)));
    add_tracing_and_breakpoint_evaluation_settings(display,structure);
    add_5_dot_0_evaluation_settings(display,structure);
    return VALUES_1(structure);
}

static Object Qnever;              /* never */

static Object Qdata_point_collection_time;  /* data-point-collection-time */

static Object Qdata_point_expiration_time;  /* data-point-expiration-time */

/* GET-EVALUATION-VALUE-OF-VARIABLE-OR-PARAMETER */
Object get_evaluation_value_of_variable_or_parameter(variable_or_parameter,
	    use_unix_time_p)
    Object variable_or_parameter, use_unix_time_p;
{
    Object sub_class_bit_vector, variable_p, expiration_time;
    Object value_is_current_p, value, current_value, collection_time;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char logical_qm;
    double aref_new_value;

    x_note_fn_call(198,49);
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	variable_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	variable_p = Nil;
    expiration_time = variable_p ? ISVREF(variable_or_parameter,
	    (SI_Long)26L) : Nil;
    value_is_current_p =  !TRUEP(expiration_time) ? T : Nil;
    if (value_is_current_p);
    else
	value_is_current_p = EQ(expiration_time,Qnever) ? T : Nil;
    if (value_is_current_p);
    else
	value_is_current_p = FIXNUM_GE(expiration_time,Gensym_time) ? T : Nil;
    if (value_is_current_p) {
	logical_qm = EQ(ISVREF(variable_or_parameter,(SI_Long)20L),
		Qtruth_value);
	value = ISVREF(variable_or_parameter,(SI_Long)23L);
	if (logical_qm) {
	    if (FIXNUM_EQ(value,Truth))
		current_value = Evaluation_true_value;
	    else if (FIXNUM_EQ(value,Falsity))
		current_value = Evaluation_false_value;
	    else
		current_value = eval_cons_1(value,Qtruth_value);
	}
	else
	    current_value = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
		    (SI_Long)0L ? copy_wide_string(value) : FIXNUMP(value) 
		    || SYMBOLP(value) ? value : copy_evaluation_value_1(value);
    }
    else
	current_value = Nil;
    collection_time = ISVREF(variable_or_parameter,(SI_Long)21L);
    if (use_unix_time_p) {
	if (FIXNUMP(expiration_time)) {
	    if (EQL(expiration_time,Some_time_ago))
		expiration_time = Nil;
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
		aref_new_value = (double)IFIX(FIXNUM_MINUS(expiration_time,
			Gensym_time_at_start)) + 
			DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		expiration_time = new_float;
	    }
	}
	collection_time = INLINE_DOUBLE_FLOAT_VECTOR_P(collection_time) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(collection_time)) == 
		(SI_Long)1L ? copy_managed_float(collection_time) : Qnil;
    }
    else {
	if (FIXNUMP(expiration_time))
	    expiration_time = EQL(expiration_time,Some_time_ago) ? Nil : 
		    expiration_time;
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(collection_time) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(collection_time)) == 
		(SI_Long)1L) {
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
	    aref_new_value = DFLOAT_ISAREF_1(collection_time,(SI_Long)0L) 
		    - DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    collection_time = new_float;
	}
	else
	    collection_time = Nil;
    }
    if (current_value || collection_time || expiration_time) {
	temp_2 = current_value ? eval_list_2(Qdata_point_value,
		current_value) : Qnil;
	return allocate_evaluation_structure(nconc2(temp_2,
		nconc2(collection_time ? 
		eval_list_2(Qdata_point_collection_time,collection_time) : 
		Qnil,expiration_time ? 
		eval_list_2(Qdata_point_expiration_time,expiration_time) : 
		Qnil)));
    }
    else
	return VALUES_1(Nil);
}

static Object Qsupplied;           /* supplied */

static Object string_constant_4;   /* "Trying to set the current value of ~NF to ~NV, which is not a ~NT" */

static Object Qvalidity_interval;  /* validity-interval */

static Object Qindefinite;         /* indefinite */

/* PUT-EVALUATION-VALUE-OF-VARIABLE-OR-PARAMETER */
Object put_evaluation_value_of_variable_or_parameter(variable_or_parameter,
	    new_value,use_unix_time_p)
    Object variable_or_parameter, new_value, use_unix_time_p;
{
    Object current_value, current_value_is_copy, collection_time;
    Object collection_time_is_new_p, expiration_time, sub_class_bit_vector;
    Object restore_supplied_p, stored_type, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float;
    Object current_computation_frame, old_collection_time, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    double aref_new_value, gensymed_symbol_3, arg, arg_1;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(198,50);
    current_value = new_value ? estructure_slot(new_value,
	    Qdata_point_value,Nil) : Nil;
    current_value_is_copy = Nil;
    collection_time = new_value ? estructure_slot(new_value,
	    Qdata_point_collection_time,Nil) : Nil;
    collection_time_is_new_p = Nil;
    expiration_time = new_value ? estructure_slot(new_value,
	    Qdata_point_expiration_time,Nil) : Nil;
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    restore_supplied_p = temp ? (EQ(Qsupplied,ISVREF(variable_or_parameter,
	    (SI_Long)27L)) ? T : Nil) : Nil;
    stored_type = ISVREF(variable_or_parameter,(SI_Long)20L);
    if ( !TRUEP(current_value));
    else if (type_specification_type_p(current_value,stored_type));
    else if (FIXNUMP(current_value) && EQ(stored_type,Qfloat)) {
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
	aref_new_value = (double)IFIX(current_value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	current_value = new_float;
	current_value_is_copy = T;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value)) == (SI_Long)1L 
	    && EQ(stored_type,Qinteger)) {
	current_value = 
		LONG_TO_FIXNUM(inline_floor_1(DFLOAT_ISAREF_1(current_value,
		(SI_Long)0L)));
	current_value_is_copy = T;
    }
    else
	return tformat_text_string(4,string_constant_4,
		variable_or_parameter,current_value,stored_type);
    if (restore_supplied_p) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable_or_parameter,Qvalidity_interval);
	SVREF(variable_or_parameter,FIX((SI_Long)27L)) = Qindefinite;
    }
    if (use_unix_time_p) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(expiration_time) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(expiration_time)) == 
		(SI_Long)1L) {
	    gensymed_symbol_3 = DFLOAT_ISAREF_1(expiration_time,
		    (SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L) + (double)IFIX(Gensym_time_at_start);
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
	    expiration_time = temp ? Most_negative_fixnum : 
		    LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol_3));
	}
    }
    else if (FIXNUMP(collection_time)) {
	collection_time_is_new_p = T;
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
	aref_new_value = (double)IFIX(collection_time) + 
		DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	collection_time = new_float;
    }
    else
	collection_time = Nil;
    if (collection_time) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    current_computation_frame = variable_or_parameter;
	    old_collection_time = ISVREF(variable_or_parameter,(SI_Long)21L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		    0);
	      if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_collection_time) != 
		      (SI_Long)0L && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_collection_time)) 
		      == (SI_Long)1L)
		  reclaim_managed_simple_float_array_of_length_1(old_collection_time);
	      temp_1 = Some_time_ago;
	      ISVREF(variable_or_parameter,(SI_Long)21L) = temp_1;
	      if (current_value) {
		  temp_3 = current_value_is_copy ? current_value : 
			  FIXNUMP(current_value) || current_value && 
			  SYMBOLP(current_value) ? current_value : 
			  copy_evaluation_value_1(current_value);
		  temp_3 = 
			  put_current_evaluation_value(variable_or_parameter,
			  temp_3,expiration_time,collection_time,Nil);
	      }
	      else
		  temp_3 = put_has_no_value(variable_or_parameter);
	    POP_SPECIAL();
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (collection_time_is_new_p)
	    reclaim_evaluation_value(collection_time);
	if (restore_supplied_p) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(variable_or_parameter,
			Qvalidity_interval);
	    SVREF(variable_or_parameter,FIX((SI_Long)27L)) = Qsupplied;
	}
	return VALUES_1(temp_3);
    }
    else {
	temp_3 = 
		put_current_value_for_virtual_attribute(variable_or_parameter,
		current_value);
	if (current_value_is_copy)
	    reclaim_evaluation_value(current_value);
	return VALUES_1(temp_3);
    }
}

/* INITIAL-VALUE-STRUCTURE */
Object initial_value_structure(class_1)
    Object class_1;
{
    x_note_fn_call(198,51);
    return VALUES_1(Nil);
}

/* GET-VALUE-STRUCTURE */
Object get_value_structure(variable_or_parameter)
    Object variable_or_parameter;
{
    Object temp;

    x_note_fn_call(198,52);
    temp = 
	    get_evaluation_value_of_variable_or_parameter(variable_or_parameter,
	    Nil);
    return VALUES_1(temp);
}

/* SET-VALUE-STRUCTURE */
Object set_value_structure(variable_or_parameter,new_value)
    Object variable_or_parameter, new_value;
{
    Object temp;

    x_note_fn_call(198,53);
    temp = 
	    put_evaluation_value_of_variable_or_parameter(variable_or_parameter,
	    new_value,Nil);
    return VALUES_1(temp);
}

/* INITIAL-VALUE-STRUCTURE-USING-UNIX-TIME */
Object initial_value_structure_using_unix_time(class_1)
    Object class_1;
{
    x_note_fn_call(198,54);
    return VALUES_1(Nil);
}

/* GET-VALUE-STRUCTURE-USING-UNIX-TIME */
Object get_value_structure_using_unix_time(variable_or_parameter)
    Object variable_or_parameter;
{
    Object temp;

    x_note_fn_call(198,55);
    temp = 
	    get_evaluation_value_of_variable_or_parameter(variable_or_parameter,
	    T);
    return VALUES_1(temp);
}

/* SET-VALUE-STRUCTURE-USING-UNIX-TIME */
Object set_value_structure_using_unix_time(variable_or_parameter,new_value)
    Object variable_or_parameter, new_value;
{
    Object temp;

    x_note_fn_call(198,56);
    temp = 
	    put_evaluation_value_of_variable_or_parameter(variable_or_parameter,
	    new_value,T);
    return VALUES_1(temp);
}

static Object Qproblem_putting_current_value_into_history_keeper;  /* problem-putting-current-value-into-history-keeper */

static Object Qproblem_putting_current_value_into_variable_or_parameter;  /* problem-putting-current-value-into-variable-or-parameter */

static Object string_constant_5;   /* "Can't assign No Value to parameter ~NF" */

/* PUT-CURRENT-VALUE-FOR-VIRTUAL-ATTRIBUTE */
Object put_current_value_for_virtual_attribute(variable_or_parameter,new_value)
    Object variable_or_parameter, new_value;
{
    Object current_computation_frame, g2_time_at_start;
    Object collection_time_for_put_current_evaluation_value;
    Object previous_time_of_most_recent_value, svref_new_value;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(198,57);
    if (new_value) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    current_computation_frame = variable_or_parameter;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		    1);
	      if (ISVREF(variable_or_parameter,(SI_Long)24L)) {
		  g2_time_at_start = G2_time_at_start;
		  PUSH_SPECIAL_WITH_SYMBOL(G2_time_at_start,Qg2_time_at_start,g2_time_at_start,
			  0);
		    collection_time_for_put_current_evaluation_value = 
			    get_default_collection_time_for_put_current_value(variable_or_parameter);
		    previous_time_of_most_recent_value = 
			    ISVREF(variable_or_parameter,(SI_Long)21L);
		    reclaim_evaluation_value(previous_time_of_most_recent_value);
		    svref_new_value = Some_time_ago;
		    ISVREF(variable_or_parameter,(SI_Long)21L) = 
			    svref_new_value;
		    result = put_current_value_for_virtual_attribute_1(variable_or_parameter,
			    new_value,
			    collection_time_for_put_current_evaluation_value,
			    Qproblem_putting_current_value_into_history_keeper);
		  POP_SPECIAL();
	      }
	      else
		  result = put_current_value_for_virtual_attribute_1(variable_or_parameter,
			  new_value,Nil,
			  Qproblem_putting_current_value_into_variable_or_parameter);
	    POP_SPECIAL();
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
		(SI_Long)18L));
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
	if (temp)
	    return put_has_no_value(variable_or_parameter);
	else
	    return tformat_text_string(2,string_constant_5,
		    variable_or_parameter);
    }
}

/* PUT-CURRENT-VALUE-FOR-VIRTUAL-ATTRIBUTE-1 */
Object put_current_value_for_virtual_attribute_1(variable_or_parameter,
	    new_value,collection_time_qm,potential_problem_name)
    Object variable_or_parameter, new_value, collection_time_qm;
    Object potential_problem_name;
{
    Object sub_class_bit_vector, restore_supplied_p, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(198,58);
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    restore_supplied_p = temp ? (EQ(Qsupplied,ISVREF(variable_or_parameter,
	    (SI_Long)27L)) ? T : Nil) : Nil;
    if (restore_supplied_p) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable_or_parameter,Qvalidity_interval);
	SVREF(variable_or_parameter,FIX((SI_Long)27L)) = Qindefinite;
    }
    temp_1 = put_current_evaluation_value(variable_or_parameter,
	    FIXNUMP(new_value) || new_value && SYMBOLP(new_value) ? 
	    new_value : copy_evaluation_value_1(new_value),Nil,
	    collection_time_qm,Nil);
    if (restore_supplied_p) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable_or_parameter,Qvalidity_interval);
	SVREF(variable_or_parameter,FIX((SI_Long)27L)) = Qsupplied;
    }
    return VALUES_1(temp_1);
}

/* INITIAL-LAST-RECORDED-VALUE-TEXT */
Object initial_last_recorded_value_text(class_1)
    Object class_1;
{
    x_note_fn_call(198,59);
    return VALUES_1(Nil);
}

static Object array_constant_5;    /* # */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant_6;    /* # */

/* GET-LAST-RECORDED-VALUE-TEXT */
Object get_last_recorded_value_text(variable_or_parameter)
    Object variable_or_parameter;
{
    Object sub_class_bit_vector, temp_1, text_to_return, value, value_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object expiration_time_of_current_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    char temp, logical_qm;
    Declare_special(5);

    x_note_fn_call(198,60);
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
	temp_1 = ISVREF(variable_or_parameter,(SI_Long)21L);
	temp = EQL(temp_1,Some_time_ago);
    }
    else
	temp = TRUEP(Nil);
    text_to_return = temp ? copy_as_wide_string(array_constant_5) : Nil;
    if (text_to_return)
	temp_1 = text_to_return;
    else {
	logical_qm = EQ(ISVREF(variable_or_parameter,(SI_Long)20L),
		Qtruth_value);
	value = ISVREF(variable_or_parameter,(SI_Long)23L);
	if (logical_qm) {
	    if (FIXNUM_EQ(value,Truth))
		value_qm = Evaluation_true_value;
	    else if (FIXNUM_EQ(value,Falsity))
		value_qm = Evaluation_false_value;
	    else
		value_qm = eval_cons_1(value,Qtruth_value);
	}
	else
	    value_qm = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
		    (SI_Long)0L ? copy_wide_string(value) : FIXNUMP(value) 
		    || SYMBOLP(value) ? value : copy_evaluation_value_1(value);
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
		  if (value_qm)
		      write_evaluation_value(1,value_qm);
		  else
		      twrite(array_constant_5);
		  if (value_qm) {
		      sub_class_bit_vector = 
			      ISVREF(ISVREF(variable_or_parameter,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Variable_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
		      if (sub_class_vector_index < 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				  {
			  gensymed_symbol = 
				  UBYTE_8_ISAREF_1(sub_class_bit_vector,
				  sub_class_vector_index);
			  gensymed_symbol_1 = (SI_Long)1L;
			  gensymed_symbol_2 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_1 = gensymed_symbol_1 << 
				  gensymed_symbol_2;
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      expiration_time_of_current_value = 
			      ISVREF(variable_or_parameter,(SI_Long)26L);
		      temp =  !(EQ(expiration_time_of_current_value,
			      Qnever) || 
			      FIXNUM_GE(expiration_time_of_current_value,
			      Gensym_time));
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      twrite(array_constant_6);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if ( !(FIXNUMP(value_qm) || SYMBOLP(value_qm) || 
		SIMPLE_VECTOR_P(value_qm)))
	    reclaim_if_evaluation_value_1(value_qm);
    }
    return VALUES_1(temp_1);
}

/* INITIAL-EFFECTIVE-DATA-TYPE */
Object initial_effective_data_type(class_1)
    Object class_1;
{
    x_note_fn_call(198,61);
    return VALUES_1(Nil);
}

static Object Qdatum;              /* datum */

static Object Qvalue;              /* value */

static Object Qquantity;           /* quantity */

static Object Qlong;               /* long */

/* GET-EFFECTIVE-DATA-TYPE */
Object get_effective_data_type(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector, variable_or_parameter;
    Object stored_data_type, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(198,62);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Variable_or_parameter_class_description,(SI_Long)18L));
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
    if (temp)
	variable_or_parameter = item;
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Simulation_subtable_class_description,
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
	if (temp)
	    variable_or_parameter = ISVREF(item,(SI_Long)22L);
	else
	    variable_or_parameter = Qnil;
    }
    if (variable_or_parameter) {
	stored_data_type = ISVREF(variable_or_parameter,(SI_Long)20L);
	if (symbolic_type_specification_subtype_p(stored_data_type,Qdatum)) {
	    if (EQ(stored_data_type,Qdatum))
		temp_1 = Qvalue;
	    else if (EQ(stored_data_type,Qnumber))
		temp_1 = Qquantity;
	    else
		temp_1 = stored_data_type;
	}
	else if (EQ(stored_data_type,Qnumber) || EQ(stored_data_type,
		Qinteger) || EQ(stored_data_type,Qfloat) || 
		EQ(stored_data_type,Qlong) || 
		lookup_global_or_kb_specific_property_value(stored_data_type,
		Numeric_data_type_gkbprop))
	    temp_1 = Qquantity;
	else
	    temp_1 = Qvalue;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* GET-ITEM-HISTORY-INFORMATION */
Object get_item_history_information(item,
	    make_history_enclosure_if_not_present_p)
    Object item, make_history_enclosure_if_not_present_p;
{
    Object gensymed_symbol, sub_class_bit_vector, storing_simulated_value_qm;
    Object item_for_specs, x2, history_specification, temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(198,63);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Variable_or_parameter_class_description,(SI_Long)18L));
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
    if (temp)
	storing_simulated_value_qm = Nil;
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Simulation_subtable_class_description,
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
	if (temp)
	    storing_simulated_value_qm = T;
	else
	    return VALUES_1(Nil);
    }
    item_for_specs = storing_simulated_value_qm ? ISVREF(item,
	    (SI_Long)22L) : item;
    if (storing_simulated_value_qm) {
	if (SIMPLE_VECTOR_P(item_for_specs) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_for_specs)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_for_specs,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_for_specs,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(Nil);
    history_specification = ISVREF(item_for_specs,(SI_Long)25L);
    temp_1 = type_specification_of_variable_or_parameter_value(item_for_specs);
    temp_2 = history_specification ? 
	    (make_history_enclosure_if_not_present_p ? 
	    get_or_make_history_buffer(item,history_specification) : 
	    storing_simulated_value_qm ? ISVREF(item,(SI_Long)20L) : 
	    ISVREF(item,(SI_Long)24L)) : Nil;
    return VALUES_4(storing_simulated_value_qm,temp_1,
	    history_specification,temp_2);
}

/* GET-HISTORY-EVALUATION-STRUCTURE */
Object get_history_evaluation_structure(item,use_unix_time_p)
    Object item, use_unix_time_p;
{
    Object temp, storing_simulated_value_qm, data_type, temp_1;
    Object history_enclosure_qm;
    Object result;

    x_note_fn_call(198,64);
    result = get_item_history_information(item,Nil);
    MVS_4(result,storing_simulated_value_qm,data_type,temp_1,
	    history_enclosure_qm);
    temp_1 = history_enclosure_qm ? 
	    get_history_evaluation_structure_from_cascade(history_enclosure_qm,
	    data_type,storing_simulated_value_qm,use_unix_time_p,Nil,Nil) :
	     Nil;
    return VALUES_1(temp_1);
}

static Object Qhistory_value;      /* history-value */

static Object Qhistory_collection_time;  /* history-collection-time */

/* GET-HISTORY-EVALUATION-STRUCTURE-FROM-CASCADE */
Object get_history_evaluation_structure_from_cascade(history_enclosure_qm,
	    data_type,storing_simulated_value_qm,use_unix_time_p,
	    start_index,end_index)
    Object history_enclosure_qm, data_type, storing_simulated_value_qm;
    Object use_unix_time_p, start_index, end_index;
{
    Object history_elements, temp, ring_buffer, oldest_active_element_index;
    Object newest_active_element_index, element_index, history_value;
    Object history_collection_time, vector_1, value;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, gensymed_symbol, item_or_value, x2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char logicalp, temp_3;
    double aref_new_value;

    x_note_fn_call(198,65);
    history_elements = Nil;
    if ( !TRUEP(cascaded_ring_buffer_empty_qm(history_enclosure_qm))) {
	logicalp = EQ(data_type,Qtruth_value);
	temp = ISVREF(history_enclosure_qm,(SI_Long)4L);
	ring_buffer = CAR(temp);
	oldest_active_element_index = start_index;
	if (oldest_active_element_index);
	else
	    oldest_active_element_index = ISVREF(ring_buffer,(SI_Long)2L);
	newest_active_element_index = end_index;
	if (newest_active_element_index);
	else
	    newest_active_element_index = ISVREF(ring_buffer,(SI_Long)1L);
	element_index = oldest_active_element_index;
	history_value = Nil;
	history_collection_time = Nil;
      next_loop:
	vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(element_index,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
	    if (logicalp) {
		if (FIXNUM_EQ(value,Truth))
		    history_value = Evaluation_true_value;
		else if (FIXNUM_EQ(value,Falsity))
		    history_value = Evaluation_false_value;
		else
		    history_value = eval_cons_1(value,Qtruth_value);
	    }
	    else
		history_value = FIXNUMP(value) || value && SYMBOLP(value) ?
			 value : copy_evaluation_value_1(value);
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
	    aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
		    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    history_value = new_float;
	}
	history_collection_time = use_unix_time_p ? 
		get_history_g2_time_as_evaluation_value(history_enclosure_qm,
		element_index,storing_simulated_value_qm) : 
		get_history_current_time_as_evaluation_value(history_enclosure_qm,
		element_index,storing_simulated_value_qm);
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qhistory_value;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qhistory_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = history_value;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_1 = temp_3 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = history_value;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_2 = temp_3 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = temp_2;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qhistory_collection_time;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qhistory_collection_time;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = history_collection_time;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_1 = temp_3 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = history_collection_time;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_2 = temp_3 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = temp_2;
	}
	history_elements = eval_cons_1(eval_cons_1(gensymed_symbol,
		Qab_structure),history_elements);
	if (FIXNUM_EQ(element_index,newest_active_element_index))
	    goto end_loop;
	element_index = FIXNUM_EQ(element_index,
		FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
	goto next_loop;
      end_loop:;
	temp = allocate_evaluation_sequence(nreverse(history_elements));
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object string_constant_6;   /* "Trying to set a history value of ~NF to ~NV, which is not a ~NT" */

/* SET-HISTORY-EVALUATION-STRUCTURE */
Object set_history_evaluation_structure(item,use_unix_time_p,new_value)
    Object item, use_unix_time_p, new_value;
{
    Object storing_simulated_value_qm, data_type, history_specification;
    Object history_enclosure_qm, gensymed_symbol, held_vector, history_element;
    Object value, elt_1, validated_elt, firstp, timestamp, value_is_copy;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;
    SI_Long next_index, length_1;
    char logicalp;
    double aref_new_value, gensym_time_since_start;
    Object result;

    x_note_fn_call(198,66);
    result = get_item_history_information(item,T);
    MVS_4(result,storing_simulated_value_qm,data_type,
	    history_specification,history_enclosure_qm);
    if (history_specification) {
	clear_history_buffer(history_enclosure_qm);
	if (new_value) {
	    gensymed_symbol = new_value;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    history_element = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop:
	    if (next_index >= length_1)
		goto end_loop;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    history_element = validated_elt;
	    value = estructure_slot(history_element,Qhistory_value,Nil);
	    if ( !(type_specification_type_p(value,data_type) || 
		    FIXNUMP(value) && EQ(data_type,Qfloat) || 
		    INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L 
		    && EQ(data_type,Qinteger)))
		return tformat_text_string(4,string_constant_6,item,value,
			data_type);
	    goto next_loop;
	  end_loop:;
	    logicalp = EQ(data_type,Qtruth_value);
	    firstp = T;
	    gensymed_symbol = new_value;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    history_element = Nil;
	    value = Nil;
	    timestamp = Nil;
	    value_is_copy = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    history_element = validated_elt;
	    value = estructure_slot(history_element,Qhistory_value,Nil);
	    timestamp = estructure_slot(history_element,
		    Qhistory_collection_time,Nil);
	    if (type_specification_type_p(value,data_type))
		value_is_copy = Nil;
	    else if (FIXNUMP(value) && EQ(data_type,Qfloat)) {
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
		aref_new_value = (double)IFIX(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		value = new_float;
		value_is_copy = T;
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L 
		    && EQ(data_type,Qinteger)) {
		value = 
			LONG_TO_FIXNUM(inline_floor_1(DFLOAT_ISAREF_1(value,
			(SI_Long)0L)));
		value_is_copy = T;
	    }
	    else
		value_is_copy = Qnil;
	    if (firstp) {
		temp = copy_managed_float(timestamp);
		SVREF(history_enclosure_qm,FIX((SI_Long)10L)) = temp;
	    }
	    if ( !(FIXNUMP(timestamp) || 
		    INLINE_DOUBLE_FLOAT_VECTOR_P(timestamp) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(timestamp)) == 
		    (SI_Long)1L))
		timestamp = FIX((SI_Long)0L);
	    if ( !TRUEP(use_unix_time_p)) {
		if (FIXNUMP(timestamp))
		    gensym_time_since_start = (double)IFIX(timestamp);
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(timestamp) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(timestamp)) == 
			(SI_Long)1L)
		    gensym_time_since_start = DFLOAT_ISAREF_1(timestamp,
			    (SI_Long)0L);
		else
		    gensym_time_since_start = 0.0;
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
		aref_new_value = DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L) + gensym_time_since_start;
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		timestamp = new_float;
	    }
	    store_history_value(history_enclosure_qm,history_specification,
		    logicalp ? M_CAR(value) : value,timestamp,
		    storing_simulated_value_qm);
	    if (value_is_copy)
		reclaim_evaluation_value(value);
	    if ( !TRUEP(use_unix_time_p))
		reclaim_managed_simple_float_array_of_length_1(timestamp);
	    firstp = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	    temp_2 = Nil;
	}
	else
	    temp_2 = Nil;
    }
    else
	temp_2 = Nil;
    return VALUES_1(temp_2);
}

/* INITIAL-HISTORY */
Object initial_history(class_1)
    Object class_1;
{
    x_note_fn_call(198,67);
    return VALUES_1(Nil);
}

/* GET-HISTORY */
Object get_history(item)
    Object item;
{
    Object temp;

    x_note_fn_call(198,68);
    temp = get_history_evaluation_structure(item,Nil);
    return VALUES_1(temp);
}

/* SET-HISTORY */
Object set_history(item,new_value)
    Object item, new_value;
{
    x_note_fn_call(198,69);
    set_history_evaluation_structure(item,Nil,new_value);
    return VALUES_1(Nil);
}

/* INITIAL-HISTORY-USING-UNIX-TIME */
Object initial_history_using_unix_time(class_1)
    Object class_1;
{
    x_note_fn_call(198,70);
    return VALUES_1(Nil);
}

/* GET-HISTORY-USING-UNIX-TIME */
Object get_history_using_unix_time(item)
    Object item;
{
    Object temp;

    x_note_fn_call(198,71);
    temp = get_history_evaluation_structure(item,T);
    return VALUES_1(temp);
}

/* SET-HISTORY-USING-UNIX-TIME */
Object set_history_using_unix_time(item,new_value)
    Object item, new_value;
{
    Object temp;

    x_note_fn_call(198,72);
    temp = set_history_evaluation_structure(item,T,new_value);
    return VALUES_1(temp);
}

/* INITIAL-G2-ARRAY-SEQUENCE */
Object initial_g2_array_sequence(class_1)
    Object class_1;
{
    x_note_fn_call(198,73);
    return VALUES_1(Nil);
}

/* GET-G2-ARRAY-SEQUENCE */
Object get_g2_array_sequence(g2_array)
    Object g2_array;
{
    Object value, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, x2, temp_1;
    SI_Long index_1, ab_loop_bind_;
    char temp;

    x_note_fn_call(198,74);
    if (ISVREF(g2_array,(SI_Long)24L) || (SI_Long)0L != 
	    (IFIX(ISVREF(g2_array,(SI_Long)5L)) & (SI_Long)1L)) {
	if (ISVREF(g2_array,(SI_Long)23L)) {
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(ISVREF(g2_array,(SI_Long)20L));
	    value = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop;
	    value = g2_array_aref_item_or_evaluation_value(g2_array,
		    FIX(index_1));
	    if (SIMPLE_VECTOR_P(value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp =  !temp;
	    if (temp);
	    else
		temp = TRUEP(serve_item_p(value));
	    ab_loopvar__2 = eval_cons_1(temp ? value : Nil,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp_1 = ab_loopvar_;
	    goto end_1;
	    temp_1 = Qnil;
	  end_1:;
	}
	else
	    temp_1 = Nil;
	temp_1 = allocate_evaluation_sequence(temp_1);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object string_constant_7;   /* "cannot reset/disable array ~NF by concluding no-value in g2-array-sequence" */

static Object string_constant_8;   /* "Cannot set the g2-array-sequence of ~NF because it is neither a permanent array nor active" */

static Object Qg2_array_length;    /* g2-array-length */

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qitem_or_value;      /* item-or-value */

static Object string_constant_9;   /* "element ~D, ~NA, is not of type ~S" */

/* SET-G2-ARRAY-SEQUENCE */
Object set_g2_array_sequence(g2_array,new_value)
    Object g2_array, new_value;
{
    Object temp, element_type, length_1, length_sd, error_string;
    Object allow_no_value_p, gensymed_symbol, held_vector, item_or_datum_qm;
    Object elt_1, validated_elt, x2, gensymed_symbol_1, sub_class_bit_vector;
    Object temp_2, temp_3, existing_length, desired_length, delete_p;
    Object current_element;
    SI_Long next_index, length_2, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, index_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(198,75);
    if ( !TRUEP(new_value))
	temp = ISVREF(g2_array,(SI_Long)23L) ? tformat_text_string(2,
		string_constant_7,g2_array) : Nil;
    else if ( !(ISVREF(g2_array,(SI_Long)24L) || (SI_Long)0L != 
	    (IFIX(ISVREF(g2_array,(SI_Long)5L)) & (SI_Long)1L)))
	temp = tformat_text_string(2,string_constant_8,g2_array);
    else {
	element_type = ISVREF(g2_array,(SI_Long)21L);
	length_1 = FIX((SI_Long)0L);
	length_sd = 
		get_slot_description_of_class_description_function(Qg2_array_length,
		ISVREF(g2_array,(SI_Long)1L),Nil);
	error_string = Nil;
	temp =  ! 
		!TRUEP(lookup_global_or_kb_specific_property_value(element_type,
		Class_description_gkbprop)) ? T : Nil;
	if (temp);
	else
	    temp = EQ(element_type,Qitem_or_datum) ? T : Nil;
	allow_no_value_p = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Allow_no_value_p,Qallow_no_value_p,allow_no_value_p,
		0);
	  gensymed_symbol = new_value;
	  held_vector = Nil;
	  next_index = (SI_Long)1L;
	  length_2 = (SI_Long)0L;
	  item_or_datum_qm = Nil;
	  held_vector = M_CAR(gensymed_symbol);
	  length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	next_loop:
	  if (next_index >= length_2)
	      goto end_loop;
	  elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(held_vector,
		  next_index + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	  validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		  Nil,Nil) : Nil;
	  next_index = next_index + (SI_Long)1L;
	  item_or_datum_qm = validated_elt;
	  temp_1 = Allow_no_value_p ?  !TRUEP(item_or_datum_qm) : TRUEP(Qnil);
	  if (temp_1);
	  else
	      temp_1 = TRUEP(type_specification_type_p(item_or_datum_qm,
		      element_type));
	  if (temp_1);
	  else {
	      if (SIMPLE_VECTOR_P(item_or_datum_qm) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_qm)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_datum_qm,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_datum_qm,(SI_Long)1L);
		  gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? x2 : Qnil;
	      }
	      else
		  gensymed_symbol = Nil;
	      if (gensymed_symbol) {
		  gensymed_symbol_1 = 
			  lookup_global_or_kb_specific_property_value(element_type,
			  Class_description_gkbprop);
		  if (gensymed_symbol_1) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
			  temp_1 = (SI_Long)0L < gensymed_symbol_2;
		      }
		      else
			  temp_1 = TRUEP(Nil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	  }
	  if ( !temp_1) {
	      temp_2 = length_1;
	      temp = item_or_datum_qm;
	      if (EQ(element_type,Qitem_or_datum))
		  temp_3 = Qitem_or_value;
	      else if (EQ(element_type,Qdatum))
		  temp_3 = Qvalue;
	      else if (EQ(element_type,Qnumber))
		  temp_3 = Qquantity;
	      else
		  temp_3 = element_type;
	      error_string = tformat_text_string(4,string_constant_9,
		      temp_2,temp,temp_3);
	      goto end_1;
	  }
	  length_1 = FIXNUM_ADD1(length_1);
	  goto next_loop;
	end_loop:
	end_1:;
	POP_SPECIAL();
	if (error_string)
	    temp = error_string;
	else {
	    existing_length = get_slot_description_value(g2_array,length_sd);
	    desired_length = Append_into_arrays_and_lists ? 
		    FIXNUM_ADD(existing_length,length_1) : length_1;
	    if ( !FIXNUM_EQ(existing_length,desired_length))
		change_slot_description_value_function(g2_array,length_sd,
			desired_length,Nil,Nil);
	    delete_p = Delete_old_elements_from_arrays_and_lists;
	    index_1 = Append_into_arrays_and_lists ? IFIX(existing_length) 
		    : (SI_Long)0L;
	    current_element = Nil;
	    gensymed_symbol = new_value;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    item_or_datum_qm = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    current_element = delete_p ? 
		    g2_array_aref_item_or_evaluation_value(g2_array,
		    FIX(index_1)) : Nil;
	    if (next_index >= length_2)
		goto end_loop_1;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    item_or_datum_qm = validated_elt;
	    temp = FIX(index_1);
	    mutate_g2_array(g2_array,temp,FIXNUMP(item_or_datum_qm) || 
		    item_or_datum_qm && SYMBOLP(item_or_datum_qm) || 
		    SIMPLE_VECTOR_P(item_or_datum_qm) ? item_or_datum_qm : 
		    copy_if_evaluation_value_1(item_or_datum_qm),T,T);
	    if (SIMPLE_VECTOR_P(current_element) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(current_element,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(current_element,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		delete_frame_for_rpc(current_element);
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	    temp = Nil;
	}
    }
    return VALUES_1(temp);
}

/* GET-LIST-CONTENTS-AS-SEQUENCE */
Object get_list_contents_as_sequence(g2_list)
    Object g2_list;
{
    Object ab_loopvar_, ab_loopvar__1, item_or_evaluation_value_element;
    Object ab_loopvar__2, ab_loopvar__3, ab_loopvar__4, x2, temp_1;
    char temp;

    x_note_fn_call(198,76);
    if ( !TRUEP(g2_list_empty_p(g2_list))) {
	ab_loopvar_ = ISVREF(g2_list,(SI_Long)20L);
	ab_loopvar__1 = Nil;
	item_or_evaluation_value_element = Nil;
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
	ab_loopvar__1 = ab_loopvar_ ? 
		g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
		ab_loopvar_) : Nil;
      next_loop:
	if ( !TRUEP(ab_loopvar__1))
	    goto end_loop;
	item_or_evaluation_value_element = ISVREF(ab_loopvar__1,(SI_Long)4L);
	ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
	if (SIMPLE_VECTOR_P(item_or_evaluation_value_element) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value_element)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(item_or_evaluation_value_element,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_evaluation_value_element,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
	if (temp);
	else
	    temp = TRUEP(serve_item_p(item_or_evaluation_value_element));
	if (temp) {
	    ab_loopvar__4 = 
		    eval_cons_1(FIXNUMP(item_or_evaluation_value_element) 
		    || item_or_evaluation_value_element && 
		    SYMBOLP(item_or_evaluation_value_element) || 
		    SIMPLE_VECTOR_P(item_or_evaluation_value_element) ? 
		    item_or_evaluation_value_element : 
		    copy_if_evaluation_value_1(item_or_evaluation_value_element),
		    Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	}
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar__2;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = Nil;
    temp_1 = allocate_evaluation_sequence(temp_1);
    return VALUES_1(temp_1);
}

/* INITIAL-G2-LIST-SEQUENCE */
Object initial_g2_list_sequence(class_1)
    Object class_1;
{
    x_note_fn_call(198,77);
    return VALUES_1(Nil);
}

/* GET-G2-LIST-SEQUENCE */
Object get_g2_list_sequence(g2_list)
    Object g2_list;
{
    Object temp;

    x_note_fn_call(198,78);
    temp = get_list_contents_as_sequence(g2_list);
    return VALUES_1(temp);
}

/* SET-G2-LIST-SEQUENCE */
Object set_g2_list_sequence(g2_list,new_value)
    Object g2_list, new_value;
{
    Object element_type, error_string, temp, allow_no_value_p, gensymed_symbol;
    Object held_vector, item_or_datum_qm, ab_loop_iter_flag_, elt_1;
    Object validated_elt, x2, gensymed_symbol_1, sub_class_bit_vector, temp_2;
    Object temp_3, ab_loopvar_, ab_loopvar__1;
    Object item_or_evaluation_value_element, ab_loopvar__2, ab_loopvar__3;
    Object ab_loopvar__4, frames_to_delete, frame_qm, ab_loop_list_, element;
    SI_Long next_index, length_1, length_2, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(198,79);
    element_type = ISVREF(g2_list,(SI_Long)21L);
    error_string = Nil;
    temp =  ! 
	    !TRUEP(lookup_global_or_kb_specific_property_value(element_type,
	    Class_description_gkbprop)) ? T : Nil;
    if (temp);
    else
	temp = EQ(element_type,Qitem_or_datum) ? T : Nil;
    allow_no_value_p = temp;
    PUSH_SPECIAL_WITH_SYMBOL(Allow_no_value_p,Qallow_no_value_p,allow_no_value_p,
	    0);
      gensymed_symbol = new_value;
      held_vector = Nil;
      next_index = (SI_Long)1L;
      length_1 = (SI_Long)0L;
      item_or_datum_qm = Nil;
      length_2 = (SI_Long)0L;
      ab_loop_iter_flag_ = T;
      held_vector = M_CAR(gensymed_symbol);
      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
    next_loop:
      if (next_index >= length_1)
	  goto end_loop;
      elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(held_vector,next_index 
	      + IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(held_vector,(next_index >>  -  - (SI_Long)10L) 
	      + (SI_Long)2L),next_index & (SI_Long)1023L);
      validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	      Nil) : Nil;
      next_index = next_index + (SI_Long)1L;
      item_or_datum_qm = validated_elt;
      if ( !TRUEP(ab_loop_iter_flag_))
	  length_2 = length_2 + (SI_Long)1L;
      temp_1 = Allow_no_value_p ?  !TRUEP(item_or_datum_qm) : TRUEP(Qnil);
      if (temp_1);
      else
	  temp_1 = TRUEP(type_specification_type_p(item_or_datum_qm,
		  element_type));
      if (temp_1);
      else {
	  if (SIMPLE_VECTOR_P(item_or_datum_qm) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_qm)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_datum_qm,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_datum_qm,(SI_Long)1L);
	      gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? x2 : Qnil;
	  }
	  else
	      gensymed_symbol = Nil;
	  if (gensymed_symbol) {
	      gensymed_symbol_1 = 
		      lookup_global_or_kb_specific_property_value(element_type,
		      Class_description_gkbprop);
	      if (gensymed_symbol_1) {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
		      temp_1 = (SI_Long)0L < gensymed_symbol_2;
		  }
		  else
		      temp_1 = TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
      }
      if ( !temp_1) {
	  temp_2 = FIX(length_2);
	  temp = item_or_datum_qm;
	  if (EQ(element_type,Qitem_or_datum))
	      temp_3 = Qitem_or_value;
	  else if (EQ(element_type,Qdatum))
	      temp_3 = Qvalue;
	  else if (EQ(element_type,Qnumber))
	      temp_3 = Qquantity;
	  else
	      temp_3 = element_type;
	  error_string = tformat_text_string(4,string_constant_9,temp_2,
		  temp,temp_3);
	  goto end_1;
      }
      ab_loop_iter_flag_ = Nil;
      goto next_loop;
    end_loop:
    end_1:;
    POP_SPECIAL();
    if (error_string)
	temp = error_string;
    else {
	if ( !TRUEP(Append_into_arrays_and_lists)) {
	    if (Delete_old_elements_from_arrays_and_lists) {
		ab_loopvar_ = ISVREF(g2_list,(SI_Long)20L);
		ab_loopvar__1 = Nil;
		item_or_evaluation_value_element = Nil;
		ab_loopvar__2 = Nil;
		ab_loopvar__3 = Nil;
		ab_loopvar__4 = Nil;
		ab_loopvar__1 = ab_loopvar_ ? 
			g2_list_structure_next(ISVREF(ab_loopvar_,
			(SI_Long)2L),ab_loopvar_) : Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loopvar__1))
		    goto end_loop_1;
		item_or_evaluation_value_element = ISVREF(ab_loopvar__1,
			(SI_Long)4L);
		ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,
			ab_loopvar_);
		if (SIMPLE_VECTOR_P(item_or_evaluation_value_element) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value_element)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(item_or_evaluation_value_element,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_evaluation_value_element,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    ab_loopvar__4 = 
			    gensym_cons_1(item_or_evaluation_value_element,
			    Nil);
		    if (ab_loopvar__3)
			M_CDR(ab_loopvar__3) = ab_loopvar__4;
		    else
			ab_loopvar__2 = ab_loopvar__4;
		    ab_loopvar__3 = ab_loopvar__4;
		}
		goto next_loop_1;
	      end_loop_1:
		frames_to_delete = ab_loopvar__2;
		goto end_2;
		frames_to_delete = Qnil;
	      end_2:;
		frame_qm = Nil;
		ab_loop_list_ = frames_to_delete;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		frame_qm = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		delete_frame(frames_to_delete);
		goto next_loop_2;
	      end_loop_2:
		reclaim_gensym_list_1(frames_to_delete);
	    }
	    clear_g2_list(g2_list);
	}
	gensymed_symbol = new_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_3:
	if (next_index >= length_1)
	    goto end_loop_3;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	element = validated_elt;
	g2_list_insert_at_end(3,FIXNUMP(element) || element && 
		SYMBOLP(element) || SIMPLE_VECTOR_P(element) ? element : 
		copy_if_evaluation_value_1(element),g2_list,T);
	goto next_loop_3;
      end_loop_3:;
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object list_constant;       /* # */

/* G2-ARRAY-LENGTH-EVALUATION-SETTER */
Object g2_array_length_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,80);
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
			      Qinteger,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_g2_array_length_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_g2_array_length_evaluation_setter:
    return result;
}

/* G2-ARRAY-LENGTH-EVALUATION-GETTER */
Object g2_array_length_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,81);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* ELEMENT-TYPE-EVALUATION-GETTER */
Object element_type_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(198,82);
    if (EQ(slot_value,Qdatum))
	temp = Qvalue;
    else if (EQ(slot_value,Qitem_or_datum))
	temp = Qitem_or_value;
    else if (EQ(slot_value,Qnumber))
	temp = Qquantity;
    else
	temp = slot_value;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_10;  /* "There is no g2 expression that names ~NF" */

/* COPY-EVALUATION-CONSTANT-TO-PHRASE */
Object copy_evaluation_constant_to_phrase(element,top_level_p,items_allowed_p)
    Object element, top_level_p, items_allowed_p;
{
    Object value, new_long, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float, x2, designation_qm, temp_3, temp_4;
    SI_int64 aref_new_value;
    char temp_2;
    double aref_new_value_1;

    x_note_fn_call(198,83);
    if (element && SYMBOLP(element)) {
	if (top_level_p && items_allowed_p)
	    return phrase_list_2(Symbol_initial_value_marker,element);
	else
	    return VALUES_1(element);
    }
    else if (FIXNUMP(element))
	return VALUES_1(element);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(element) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) == (SI_Long)1L) {
	if (top_level_p) {
	    value = evaluation_value_value(element);
	    if (FIXNUMP(value))
		return VALUES_1(value);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L) {
		new_long = allocate_managed_long_box();
		aref_new_value = INTEGER_TO_INT64(value);
		set_aref1(new_long,FIX((SI_Long)0L),
			INT64_TO_INTEGER(aref_new_value));
		return note_use_of_managed_long_in_phrase(new_long);
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
		aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
		return note_use_of_managed_float_in_phrase(new_float);
	    }
	}
	else if (FIXNUMP(element) || element && SYMBOLP(element))
	    return VALUES_1(element);
	else
	    return copy_evaluation_value_1(element);
    }
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(element) != (SI_Long)0L) {
	if (top_level_p)
	    return copy_for_phrase(element);
	else if (FIXNUMP(element) || element && SYMBOLP(element))
	    return VALUES_1(element);
	else
	    return copy_evaluation_value_1(element);
    }
    else if (CONSP(element) && EQ(M_CDR(element),Qtruth_value)) {
	if (top_level_p)
	    return make_slot_constant_using_phrase_conses(M_CAR(element),
		    Qtruth_value);
	else if (FIXNUMP(element) || element && SYMBOLP(element))
	    return VALUES_1(element);
	else
	    return copy_evaluation_value_1(element);
    }
    else if (CONSP(element) && EQ(M_CDR(element),Qab_structure))
	return copy_evaluation_structure_to_phrase(element);
    else if (CONSP(element) && EQ(M_CDR(element),Qsequence))
	return copy_evaluation_sequence_to_phrase(element);
    else {
	if (SIMPLE_VECTOR_P(element) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L &&  
		!EQ(ISVREF(element,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(element,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    designation_qm = generate_designation_for_block(element);
	    if (designation_qm)
		return VALUES_1(designation_qm);
	    else {
		temp_3 = Bad_phrase;
		temp_4 = tformat_text_string(2,string_constant_10,element);
		return VALUES_2(temp_3,temp_4);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
}

/* COPY-EVALUATION-STRUCTURE-TO-PHRASE */
Object copy_evaluation_structure_to_phrase(evaluation_structure)
    Object evaluation_structure;
{
    Object value_as_phrase, error_string_qm, gensymed_symbol, held_vector;
    Object name, attribute_value, value, plist, ab_loopvar_, ab_loopvar__1;
    SI_Long next_index, length_1, gensymed_symbol_1;
    Object result;

    x_note_fn_call(198,84);
    value_as_phrase = Nil;
    error_string_qm = Nil;
    gensymed_symbol = evaluation_structure;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    name = Nil;
    attribute_value = Nil;
    value = Nil;
    plist = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    gensymed_symbol_1 = next_index + (SI_Long)1L;
    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,
	    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & (SI_Long)1023L);
    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
    next_index = next_index + (SI_Long)2L;
    result = copy_evaluation_constant_to_phrase(value,Nil,Nil);
    MVS_2(result,value_as_phrase,error_string_qm);
    if (EQ(value_as_phrase,Bad_phrase))
	return VALUES_2(Bad_phrase,error_string_qm);
    ab_loopvar__1 = phrase_cons(name,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	plist = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    ab_loopvar__1 = phrase_cons(value_as_phrase,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	plist = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    return phrase_cons(plist,Phrase_structure_marker);
    return VALUES_1(Qnil);
}

/* COPY-EVALUATION-SEQUENCE-TO-PHRASE */
Object copy_evaluation_sequence_to_phrase(evaluation_sequence)
    Object evaluation_sequence;
{
    Object element_as_phrase, error_string_qm, gensymed_symbol, held_vector;
    Object element, list_of_elements, ab_loopvar_, ab_loopvar__1, elt_1;
    Object validated_elt;
    SI_Long next_index, length_1;
    Object result;

    x_note_fn_call(198,85);
    element_as_phrase = Nil;
    error_string_qm = Nil;
    gensymed_symbol = evaluation_sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
    list_of_elements = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    element = validated_elt;
    result = copy_evaluation_constant_to_phrase(element,Nil,Nil);
    MVS_2(result,element_as_phrase,error_string_qm);
    if (EQ(element_as_phrase,Bad_phrase))
	return VALUES_2(Bad_phrase,error_string_qm);
    ab_loopvar__1 = phrase_cons(element_as_phrase,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	list_of_elements = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    return phrase_cons(list_of_elements,Phrase_sequence_marker);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Designation_marker, Qdesignation_marker);

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object Qab_class;           /* class */

static Object Qname;               /* name */

/* SYMBOL-OR-CLASS-QUALIFIED-NAME-TO-EVALUATION-VALUE */
Object symbol_or_class_qualified_name_to_evaluation_value(name)
    Object name;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(198,86);
    if (CONSP(name)) {
	if (EQ(CAR(name),Qclass_qualified_name)) {
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qab_class;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qab_class;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = CADR(name);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = CADR(name);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qname;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qname;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = CADDR(name);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = CADDR(name);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    temp_2 = eval_cons_1(gensymed_symbol,Qab_structure);
	}
	else
	    temp_2 = Nil;
    }
    else
	temp_2 = name;
    return VALUES_1(temp_2);
}

static Object Qitem;               /* item */

/* CONSTANT-DESIGNATION-TO-EVALUATION-VALUE */
Object constant_designation_to_evaluation_value(designation)
    Object designation;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(198,87);
    temp = symbol_or_class_qualified_name_to_evaluation_value(designation);
    if (temp);
    else if (CONSP(designation) && EQ(CAR(designation),Qthe)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qname;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qname;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    symbol_or_class_qualified_name_to_evaluation_value(CADR(designation));
	    if (item_or_value);
	    else {
		temp = CADR(designation);
		item_or_value = CONSP(temp) ? 
			symbol_or_class_qualified_name_to_evaluation_value(CAADR(designation)) 
			: Nil;
	    }
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = 
		    symbol_or_class_qualified_name_to_evaluation_value(CADR(designation));
	    if (item_or_value);
	    else {
		temp = CADR(designation);
		item_or_value = CONSP(temp) ? 
			symbol_or_class_qualified_name_to_evaluation_value(CAADR(designation)) 
			: Nil;
	    }
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qitem;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qitem;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    constant_designation_to_evaluation_value(CADDR(designation));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = 
		    constant_designation_to_evaluation_value(CADDR(designation));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EVALUATION-VALUE-TO-SYMBOL-OR-CLASS-QUALIFIED-NAME-PHRASE */
Object evaluation_value_to_symbol_or_class_qualified_name_phrase(value)
    Object value;
{
    Object temp, class_1, name;

    x_note_fn_call(198,88);
    if (SYMBOLP(value))
	temp = value;
    else if (CONSP(value) && EQ(M_CDR(value),Qab_structure)) {
	class_1 = estructure_slot(value,Qab_class,Nil);
	name = estructure_slot(value,Qname,Nil);
	temp = class_1 && name ? phrase_list_3(Qclass_qualified_name,
		class_1,name) : Nil;
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

static Object array_constant_7;    /* # */

/* EVALUATION-VALUE-TO-CONSTANT-DESIGNATION-PHRASE */
Object evaluation_value_to_constant_designation_phrase(value)
    Object value;
{
    Object temp, name, item;

    x_note_fn_call(198,89);
    temp = evaluation_value_to_symbol_or_class_qualified_name_phrase(value);
    if (temp)
	return VALUES_1(temp);
    else if ( !(CONSP(value) && EQ(M_CDR(value),Qab_structure))) {
	temp = copy_constant_wide_string_given_length(array_constant_7,
		FIX((SI_Long)23L));
	return VALUES_2(Nil,temp);
    }
    else {
	name = estructure_slot(value,Qname,Nil);
	item = estructure_slot(value,Qitem,Nil);
	if (name && item) {
	    temp = 
		    evaluation_value_to_symbol_or_class_qualified_name_phrase(name);
	    return phrase_list_3(Qthe,temp,
		    evaluation_value_to_constant_designation_phrase(item));
	}
	else {
	    temp = copy_constant_wide_string_given_length(array_constant_7,
		    FIX((SI_Long)23L));
	    return VALUES_2(Nil,temp);
	}
    }
}

static Object string_constant_11;  /* "Could not find item for ~ND" */

static Object Qitems;              /* items */

/* INITIAL-VALUES-TO-EVALUATION-VALUE */
Object initial_values_to_evaluation_value(slot_value,values_allowed_p,
	    items_allowed_p)
    Object slot_value, values_allowed_p, items_allowed_p;
{
    Object any_designation_p, any_value_p, use_designations_p, element;
    Object ab_loop_list_, evaluation_value, designation_p, values_list_1;
    Object ab_loopvar_, ab_loopvar__1, designations_list, ab_loopvar__2, temp;
    Object gensymed_symbol, values_sequence, designations_sequence;
    char temp_1;

    x_note_fn_call(198,90);
    if ( !TRUEP(slot_value))
	return VALUES_1(Nil);
    else {
	any_designation_p = Nil;
	any_value_p = Nil;
	use_designations_p = 
		Array_initialization_evaluation_values_use_designations_p;
	element = Nil;
	ab_loop_list_ = slot_value;
	evaluation_value = Nil;
	designation_p = Nil;
	values_list_1 = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	designations_list = Nil;
	ab_loopvar__2 = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (text_string_p(element))
	    evaluation_value = copy_as_wide_string(element);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(element) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) == (SI_Long)1L)
	    evaluation_value = copy_managed_float(element);
	else {
	    if (CONSP(element)) {
		temp = CDR(element);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(CADR(element),Qtruth_value) : TRUEP(Nil)) {
		gensymed_symbol = CAR(element);
		if (FIXNUM_EQ(gensymed_symbol,Truth))
		    evaluation_value = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		    evaluation_value = Evaluation_false_value;
		else
		    evaluation_value = eval_cons_1(gensymed_symbol,
			    Qtruth_value);
	    }
	    else {
		if (CONSP(element)) {
		    temp = M_CAR(element);
		    temp_1 = CONSP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
		if ((temp_1 ?  !TRUEP(M_CDR(M_CAR(element))) : TRUEP(Nil)) 
			? EQ(M_CAR(M_CAR(element)),
			Symbol_initial_value_marker_symbol) : TRUEP(Nil))
		    evaluation_value = M_CAR(M_CDR(element));
		else if (FIXNUMP(element))
		    evaluation_value = element;
		else if (CONSP(element) && EQ(M_CDR(element),Qsequence) || 
			CONSP(element) && EQ(M_CDR(element),Qab_structure))
		    evaluation_value = FIXNUMP(element) || element && 
			    SYMBOLP(element) ? element : 
			    copy_evaluation_value_1(element);
		else if ( !TRUEP(items_allowed_p))
		    evaluation_value = element;
		else if (use_designations_p)
		    evaluation_value = Designation_marker;
		else {
		    temp = evaluate_designation(element,Nil);
		    if (temp);
		    else
			temp = tformat_text_string(2,string_constant_11,
				element);
		    evaluation_value = temp;
		}
	    }
	}
	designation_p = EQ(evaluation_value,Designation_marker) ? T : Nil;
	if (designation_p)
	    any_designation_p = T;
	else
	    any_value_p = T;
	ab_loopvar__1 = eval_cons_1(designation_p ? Nil : evaluation_value,
		Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    values_list_1 = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	ab_loopvar__1 = eval_cons_1(designation_p ? 
		constant_designation_to_evaluation_value(element) : Nil,Nil);
	if (ab_loopvar__2)
	    M_CDR(ab_loopvar__2) = ab_loopvar__1;
	else
	    designations_list = ab_loopvar__1;
	ab_loopvar__2 = ab_loopvar__1;
	goto next_loop;
      end_loop:
	if (any_value_p && (values_allowed_p ||  !TRUEP(use_designations_p)))
	    values_sequence = allocate_evaluation_sequence(values_list_1);
	else {
	    reclaim_eval_list_1(values_list_1);
	    values_sequence = Nil;
	}
	if (any_designation_p && items_allowed_p)
	    designations_sequence = 
		    allocate_evaluation_sequence(designations_list);
	else {
	    reclaim_eval_list_1(designations_list);
	    designations_sequence = Nil;
	}
	if (values_allowed_p && items_allowed_p && designations_sequence)
	    return allocate_evaluation_structure(nconc2(values_sequence ? 
		    eval_list_2(Qvalues,values_sequence) : Nil,
		    eval_list_2(Qitems,designations_sequence)));
	else {
	    temp = values_sequence;
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1(designations_sequence);
	}
	return VALUES_1(Qnil);
    }
}

/* SEQUENCES-TO-INITIAL-VALUES-PHRASE */
Object sequences_to_initial_values_phrase(values_1,items,values_allowed_p,
	    items_allowed_p)
    Object values_1, items, values_allowed_p, items_allowed_p;
{
    Object value_qm, item_designation_qm, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, gensymed_symbol, phrase_value, error_string_qm, temp;
    SI_Long values_length, items_length, index_1, ab_loop_bind_;
    SI_Long gensymed_symbol_1;
    Object result;

    x_note_fn_call(198,91);
    values_length = values_1 ? IFIX(FIXNUM_SUB1(ISVREF(M_CAR(values_1),
	    (SI_Long)1L))) : (SI_Long)0L;
    items_length = items ? IFIX(FIXNUM_SUB1(ISVREF(M_CAR(items),
	    (SI_Long)1L))) : (SI_Long)0L;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = MAX(values_length,items_length);
    value_qm = Nil;
    item_designation_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (index_1 < values_length) {
	gensymed_symbol = M_CAR(values_1);
	gensymed_symbol_1 = index_1 + (SI_Long)1L;
	value_qm = FIXNUM_LE(ISVREF(M_CAR(values_1),(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(M_CAR(values_1),
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
    }
    else
	value_qm = Nil;
    if (index_1 < items_length) {
	gensymed_symbol = M_CAR(items);
	gensymed_symbol_1 = index_1 + (SI_Long)1L;
	item_designation_qm = FIXNUM_LE(ISVREF(M_CAR(items),(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(M_CAR(items),
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
    }
    else
	item_designation_qm = Nil;
    if (value_qm) {
	result = copy_evaluation_constant_to_phrase(value_qm,T,
		items_allowed_p);
	MVS_2(result,phrase_value,error_string_qm);
	if (EQ(phrase_value,Bad_phrase))
	    return VALUES_2(Bad_phrase,error_string_qm);
	else
	    temp = phrase_value;
    }
    else
	temp = Nil;
    if (temp);
    else
	temp = 
		evaluation_value_to_constant_designation_phrase(item_designation_qm);
    ab_loopvar__2 = phrase_cons(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return phrase_cons(Qnormalized,temp);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object string_constant_12;  /* "~NT " */

static Object string_constant_13;  /* "~NV must be one of the following types: ~a" */

/* EVALUATION-VALUE-TO-INITIAL-VALUES-PHRASE */
Object evaluation_value_to_initial_values_phrase(evaluation_value,
	    values_allowed_p,items_allowed_p)
    Object evaluation_value, values_allowed_p, items_allowed_p;
{
    Object gensymed_symbol, values_1, items, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string, temp, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(198,92);
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_1))
	return VALUES_1(Qnil);
    else if (type_specification_type_p(gensymed_symbol,list_constant_2))
	return sequences_to_initial_values_phrase(values_allowed_p ? 
		evaluation_value : Nil,items_allowed_p &&  
		!TRUEP(values_allowed_p) ? evaluation_value : Nil,
		values_allowed_p,items_allowed_p);
    else if (type_specification_type_p(gensymed_symbol,list_constant_3)) {
	values_1 = estructure_slot(evaluation_value,Qvalues,Nil);
	items = estructure_slot(evaluation_value,Qitems,Nil);
	return sequences_to_initial_values_phrase(values_1,items,
		values_allowed_p,items_allowed_p);
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
		  tformat(2,string_constant_12,list_constant_1);
		  tformat(2,string_constant_12,list_constant_2);
		  tformat(2,string_constant_12,list_constant_3);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_13,gensymed_symbol,
		type_string);
	return VALUES_2(temp,temp_1);
    }
}

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

/* LIST-OF-ITEM-AND-DATUM-CONSTANTS?-EVALUATION-SETTER */
Object list_of_item_and_datum_constants_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,93);
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
			  list_constant_4))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_5,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_list_of_item_and_datum_constants_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = evaluation_value_to_initial_values_phrase(evaluation_value,T,T);
  end_list_of_item_and_datum_constants_qm_evaluation_setter:
    return result;
}

/* LIST-OF-ITEM-AND-DATUM-CONSTANTS?-EVALUATION-GETTER */
Object list_of_item_and_datum_constants_qm_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object current_computation_frame, temp;
    Declare_special(1);

    x_note_fn_call(198,94);
    current_computation_frame = frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      temp = initial_values_to_evaluation_value(slot_value,T,T);
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

/* CONSTANT-DESIGNATION-LIST?-EVALUATION-SETTER */
Object constant_designation_list_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,95);
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
			  list_constant_6))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_7,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_constant_designation_list_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = evaluation_value_to_initial_values_phrase(evaluation_value,Nil,T);
  end_constant_designation_list_qm_evaluation_setter:
    return result;
}

/* CONSTANT-DESIGNATION-LIST?-EVALUATION-GETTER */
Object constant_designation_list_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object current_computation_frame, temp;
    Declare_special(1);

    x_note_fn_call(198,96);
    current_computation_frame = frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      temp = initial_values_to_evaluation_value(slot_value,Nil,T);
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

/* LIST-OF-DATUM-CONSTANTS-EVALUATION-SETTER */
Object list_of_datum_constants_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,97);
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
		      goto end_list_of_datum_constants_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = evaluation_value_to_initial_values_phrase(evaluation_value,T,Nil);
  end_list_of_datum_constants_evaluation_setter:
    return result;
}

/* LIST-OF-DATUM-CONSTANTS-EVALUATION-GETTER */
Object list_of_datum_constants_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,98);
    GENSYM_RETURN_ONE(initial_values_to_evaluation_value(slot_value,T,Nil));
    return VALUES_1(Nil);
}

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

/* SYMBOL-LIST-EVALUATION-SETTER */
Object symbol_list_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, thing, held_vector;
    Object element, ab_loopvar_, ab_loopvar__1, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,99);
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
		      goto end_symbol_list_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    thing = Nil;
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar_ = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    element = validated_elt;
    if ( !TRUEP(thing)) {
	thing = phrase_list_2(Qcm,element);
	temp_1 = thing;
    }
    else {
	thing = phrase_list_3(Qcm,thing,element);
	temp_1 = thing;
    }
    ab_loopvar_ = phrase_cons(temp_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar_;
    else;
    ab_loopvar__1 = ab_loopvar_;
    goto next_loop;
  end_loop:
    goto end_1;
  end_1:;
    result = VALUES_1(thing);
  end_symbol_list_evaluation_setter:
    return result;
}

/* SYMBOL-LIST-EVALUATION-GETTER */
Object symbol_list_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object temp;

    x_note_fn_call(198,100);
    element = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = eval_cons_1(element,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

/* WHOLE-STRING-LIST-EVALUATION-SETTER */
Object whole_string_list_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, thing, held_vector;
    Object element, ab_loopvar_, ab_loopvar__1, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,101);
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
		      goto end_whole_string_list_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    thing = Nil;
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar_ = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    element = validated_elt;
    if ( !TRUEP(thing)) {
	thing = phrase_list_2(Qcm,copy_for_phrase(element));
	temp_1 = thing;
    }
    else {
	temp_1 = thing;
	thing = phrase_list_3(Qcm,temp_1,copy_for_phrase(element));
	temp_1 = thing;
    }
    ab_loopvar_ = phrase_cons(temp_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar_;
    else;
    ab_loopvar__1 = ab_loopvar_;
    goto next_loop;
  end_loop:
    goto end_1;
  end_1:;
    result = VALUES_1(thing);
  end_whole_string_list_evaluation_setter:
    return result;
}

/* WHOLE-STRING-LIST-EVALUATION-GETTER */
Object whole_string_list_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object temp;

    x_note_fn_call(198,102);
    element = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = eval_cons_1(copy_as_wide_string(element),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_14;    /* # */

static Object list_constant_15;    /* # */

static Object string_constant_14;  /* "Illegal value, ~NV; it should be of type truth-value" */

/* TRUTH-VALUE-LIST-EVALUATION-SETTER */
Object truth_value_list_evaluation_setter(evaluation_sequence,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_sequence, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object evaluation_value, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,103);
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
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_sequence,
			  list_constant_14))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_sequence,
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
		      goto end_truth_value_list_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    evaluation_value = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    evaluation_value = validated_elt;
    if ( !(CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qtruth_value))) {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_14,evaluation_value);
	result = VALUES_2(temp,temp_1);
	goto end_set_form_for_truth_value_list;
    }
    ab_loopvar__2 = phrase_cons(M_CAR(evaluation_value),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    result = phrase_cons(Qnormalized,temp_1);
  end_set_form_for_truth_value_list:
  end_truth_value_list_evaluation_setter:
    return result;
}

/* TRUTH-VALUE-LIST-EVALUATION-GETTER */
Object truth_value_list_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object temp;

    x_note_fn_call(198,104);
    element = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_EQ(element,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(element,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(element,Qtruth_value);
    ab_loopvar__1 = eval_cons_1(temp,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_16;    /* # */

static Object list_constant_17;    /* # */

/* QUANTITY-LIST-EVALUATION-SETTER */
Object quantity_list_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, thing, held_vector;
    Object element, ab_loopvar_, ab_loopvar__1, elt_1, validated_elt, value;
    Object new_long, amf_available_array_cons_qm, amf_array, temp_2, temp_3;
    Object amf_result, new_float;
    SI_Long next_index, length_1;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,105);
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
		      goto end_quantity_list_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    thing = Nil;
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar_ = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    element = validated_elt;
    if ( !TRUEP(thing)) {
	value = evaluation_value_value(element);
	if (FIXNUMP(value))
	    temp_1 = value;
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
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
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    temp_1 = note_use_of_managed_float_in_phrase(new_float);
	}
	thing = phrase_list_2(Qcm,temp_1);
	temp_1 = thing;
    }
    else {
	temp_1 = thing;
	value = evaluation_value_value(element);
	if (FIXNUMP(value))
	    temp = value;
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    temp = note_use_of_managed_long_in_phrase(new_long);
	}
	else {
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
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    temp = note_use_of_managed_float_in_phrase(new_float);
	}
	thing = phrase_list_3(Qcm,temp_1,temp);
	temp_1 = thing;
    }
    ab_loopvar_ = phrase_cons(temp_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar_;
    else;
    ab_loopvar__1 = ab_loopvar_;
    goto next_loop;
  end_loop:
    goto end_1;
  end_1:;
    result = VALUES_1(thing);
  end_quantity_list_evaluation_setter:
    return result;
}

/* QUANTITY-LIST-EVALUATION-GETTER */
Object quantity_list_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object temp;

    x_note_fn_call(198,106);
    element = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = eval_cons_1(INLINE_DOUBLE_FLOAT_VECTOR_P(element) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) == 
	    (SI_Long)1L ? copy_managed_float(element) : element,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_18;    /* # */

static Object list_constant_19;    /* # */

/* FLOAT-LIST-EVALUATION-SETTER */
Object float_list_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, thing, held_vector;
    Object element, ab_loopvar_, ab_loopvar__1, elt_1, validated_elt, value;
    Object new_long, amf_available_array_cons_qm, amf_array, temp_2, temp_3;
    Object amf_result, new_float;
    SI_Long next_index, length_1;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,107);
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
			  list_constant_18))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_19,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_float_list_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    thing = Nil;
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar_ = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    element = validated_elt;
    if ( !TRUEP(thing)) {
	value = evaluation_value_value(element);
	if (FIXNUMP(value))
	    temp_1 = value;
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
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
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    temp_1 = note_use_of_managed_float_in_phrase(new_float);
	}
	thing = phrase_list_2(Qcm,temp_1);
	temp_1 = thing;
    }
    else {
	temp_1 = thing;
	value = evaluation_value_value(element);
	if (FIXNUMP(value))
	    temp = value;
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    temp = note_use_of_managed_long_in_phrase(new_long);
	}
	else {
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
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    temp = note_use_of_managed_float_in_phrase(new_float);
	}
	thing = phrase_list_3(Qcm,temp_1,temp);
	temp_1 = thing;
    }
    ab_loopvar_ = phrase_cons(temp_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar_;
    else;
    ab_loopvar__1 = ab_loopvar_;
    goto next_loop;
  end_loop:
    goto end_1;
  end_1:;
    result = VALUES_1(thing);
  end_float_list_evaluation_setter:
    return result;
}

/* FLOAT-LIST-EVALUATION-GETTER */
Object float_list_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object temp;

    x_note_fn_call(198,108);
    element = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = eval_cons_1(copy_managed_float(element),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_20;    /* # */

static Object list_constant_21;    /* # */

/* INTEGER-LIST-EVALUATION-SETTER */
Object integer_list_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, thing, held_vector;
    Object element, ab_loopvar_, ab_loopvar__1, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,109);
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
			  list_constant_20))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_21,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_integer_list_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    thing = Nil;
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar_ = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    element = validated_elt;
    if ( !TRUEP(thing)) {
	thing = phrase_list_2(Qcm,element);
	temp_1 = thing;
    }
    else {
	thing = phrase_list_3(Qcm,thing,element);
	temp_1 = thing;
    }
    ab_loopvar_ = phrase_cons(temp_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar_;
    else;
    ab_loopvar__1 = ab_loopvar_;
    goto next_loop;
  end_loop:
    goto end_1;
  end_1:;
    result = VALUES_1(thing);
  end_integer_list_evaluation_setter:
    return result;
}

/* INTEGER-LIST-EVALUATION-GETTER */
Object integer_list_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object temp;

    x_note_fn_call(198,110);
    element = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = eval_cons_1(element,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_22;    /* # */

static Object list_constant_23;    /* # */

/* ALIGNMENT-EVALUATION-SETTER */
Object alignment_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,111);
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
			  list_constant_22))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_23,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_alignment_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_alignment_evaluation_setter:
    return result;
}

/* ALIGNMENT-EVALUATION-GETTER */
Object alignment_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,112);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_24;    /* # */

static Object list_constant_25;    /* # */

static Object Qfor_different_selections;  /* for-different-selections */

static Object Qif_different;       /* if-different */

/* WHEN-TO-ALLOW-MULTIPLE-MENUS-EVALUATION-SETTER */
Object when_to_allow_multiple_menus_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,113);
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
			  list_constant_24))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_25,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_when_to_allow_multiple_menus_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qfor_different_selections))
	result = VALUES_1(Qif_different);
    else
	result = VALUES_1(evaluation_value);
  end_when_to_allow_multiple_menus_evaluation_setter:
    return result;
}

/* WHEN-TO-ALLOW-MULTIPLE-MENUS-EVALUATION-GETTER */
Object when_to_allow_multiple_menus_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,114);
    GENSYM_RETURN_ONE(EQ(slot_value,Qif_different) ? 
	    Qfor_different_selections : slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_26;    /* # */

/* CURRENT-LANGUAGE-EVALUATION-SETTER */
Object current_language_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,115);
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
			  list_constant_26))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qsymbol,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_current_language_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_current_language_evaluation_setter:
    return result;
}

/* CURRENT-LANGUAGE-EVALUATION-GETTER */
Object current_language_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,116);
    GENSYM_RETURN_ONE(slot_value ? slot_value : Default_language);
    return VALUES_1(Nil);
}

static Object list_constant_27;    /* # */

static Object list_constant_28;    /* # */

/* COLOR-MENU-ORDERING-EVALUATION-SETTER */
Object color_menu_ordering_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,117);
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
			  list_constant_27))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_28,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_color_menu_ordering_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_color_menu_ordering_evaluation_setter:
    return result;
}

/* COLOR-MENU-ORDERING-EVALUATION-GETTER */
Object color_menu_ordering_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,118);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_29;    /* # */

static Object list_constant_30;    /* # */

/* COLOR-SET-SPEC-EVALUATION-SETTER */
Object color_set_spec_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,119);
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
			  list_constant_29))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_30,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_color_set_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,Qsymbol))
	result = VALUES_1(evaluation_value);
    else if (type_specification_type_p(gensymed_symbol,list_constant_2)) {
	temp = phrase_cons(Qcm,Nil);
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	element = validated_elt;
	ab_loopvar__2 = phrase_cons(element,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	result = VALUES_1(nconc2(temp,temp_1));
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
		  tformat(2,string_constant_12,Qsymbol);
		  tformat(2,string_constant_12,list_constant_2);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_13,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_color_set_spec_evaluation_setter:
    return result;
}

/* COLOR-SET-SPEC-EVALUATION-GETTER */
Object color_set_spec_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object temp;

    x_note_fn_call(198,120);
    if (slot_value) {
	if (CONSP(slot_value)) {
	    element = Nil;
	    ab_loop_list_ = slot_value;
	    gensymed_symbol = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__1 = eval_cons_1(element,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop;
	  end_loop:
	    temp = allocate_evaluation_sequence(gensymed_symbol);
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	else
	    temp = slot_value;
    }
    else
	temp = Qnone;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_31;    /* # */

static Object list_constant_32;    /* # */

/* NUMBER-OF-MENU-COLUMNS-SPEC-EVALUATION-SETTER */
Object number_of_menu_columns_spec_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,121);
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
			  list_constant_31))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_32,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_number_of_menu_columns_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_number_of_menu_columns_spec_evaluation_setter:
    return result;
}

/* NUMBER-OF-MENU-COLUMNS-SPEC-EVALUATION-GETTER */
Object number_of_menu_columns_spec_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,122);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_33;    /* # */

static Object list_constant_34;    /* # */

static Object Qpalette_name;       /* palette-name */

static Object Qimage_name;         /* image-name */

/* IMAGE-PALETTE-EVALUATION-SETTER */
Object image_palette_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,123);
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
			  list_constant_33))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_34,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_image_palette_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,Qsymbol))
	result = VALUES_1(evaluation_value);
    else if (type_specification_type_p(gensymed_symbol,list_constant_3)) {
	gensymed_symbol = evaluation_value;
	temp_1 = estructure_slot(gensymed_symbol,Qpalette_name,Nil);
	result = phrase_list_2(temp_1,estructure_slot(gensymed_symbol,
		Qimage_name,Nil));
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
		  tformat(2,string_constant_12,Qsymbol);
		  tformat(2,string_constant_12,list_constant_3);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_13,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_image_palette_evaluation_setter:
    return result;
}

/* IMAGE-PALETTE-EVALUATION-GETTER */
Object image_palette_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(198,124);
    if (CONSP(slot_value)) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	set_evaluation_structure_slot(gensymed_symbol,Qpalette_name,
		FIRST(slot_value));
	set_evaluation_structure_slot(gensymed_symbol,Qimage_name,
		SECOND(slot_value));
	temp = gensymed_symbol;
    }
    else
	temp = slot_value;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_35;    /* # */

static Object list_constant_36;    /* # */

/* WARNING-MESSAGE-LEVEL-EVALUATION-SETTER */
Object warning_message_level_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,125);
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
			  list_constant_35))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_36,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_warning_message_level_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_warning_message_level_evaluation_setter:
    return result;
}

/* WARNING-MESSAGE-LEVEL-EVALUATION-GETTER */
Object warning_message_level_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,126);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_37;    /* # */

/* TRACING-MESSAGE-LEVEL-EVALUATION-SETTER */
Object tracing_message_level_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,127);
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
			  list_constant_37))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_36,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_tracing_message_level_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_tracing_message_level_evaluation_setter:
    return result;
}

/* TRACING-MESSAGE-LEVEL-EVALUATION-GETTER */
Object tracing_message_level_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,128);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_38;    /* # */

/* BREAKPOINT-LEVEL-EVALUATION-SETTER */
Object breakpoint_level_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,129);
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
			  list_constant_38))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_36,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_breakpoint_level_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_breakpoint_level_evaluation_setter:
    return result;
}

/* BREAKPOINT-LEVEL-EVALUATION-GETTER */
Object breakpoint_level_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,130);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_39;    /* # */

static Object list_constant_40;    /* # */

/* SOURCE-STEPPING-LEVEL-EVALUATION-SETTER */
Object source_stepping_level_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,131);
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
			  list_constant_39))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_40,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_source_stepping_level_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_source_stepping_level_evaluation_setter:
    return result;
}

/* SOURCE-STEPPING-LEVEL-EVALUATION-GETTER */
Object source_stepping_level_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,132);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_41;    /* # */

static Object list_constant_42;    /* # */

/* INTERFACE-WARNING-MESSAGE-LEVEL-EVALUATION-SETTER */
Object interface_warning_message_level_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,133);
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
			  list_constant_41))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_42,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_interface_warning_message_level_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_interface_warning_message_level_evaluation_setter:
    return result;
}

/* INTERFACE-WARNING-MESSAGE-LEVEL-EVALUATION-GETTER */
Object interface_warning_message_level_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(198,134);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_43;    /* # */

static Object list_constant_44;    /* # */

static Object array_constant_8;    /* # */

static Object Qdisplay_expression;  /* display-expression */

/* DISPLAY-EXPRESSION-EVALUATION-SETTER */
Object display_expression_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,135);
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
			  list_constant_43))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_display_expression_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qdisplay_expression,frame);
  end_display_expression_evaluation_setter:
    return result;
}

/* DISPLAY-EXPRESSION-EVALUATION-GETTER */
Object display_expression_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,136);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_45;    /* # */

static Object Qtext;               /* text */

static Object Qembedded_rule;      /* embedded-rule */

/* EMBEDDED-RULE-EVALUATION-SETTER */
Object embedded_rule_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,137);
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
			  list_constant_45))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,Qtext,
			      Value_at_type_failure,Type_at_type_failure,
			      Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_embedded_rule_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qembedded_rule,frame);
  end_embedded_rule_evaluation_setter:
    return result;
}

/* EMBEDDED-RULE-EVALUATION-GETTER */
Object embedded_rule_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,138);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : 
	    copy_constant_wide_string_given_length(array_constant_8,
	    FIX((SI_Long)0L)));
    return VALUES_1(Nil);
}

static Object list_constant_46;    /* # */

static Object Qexpression;         /* expression */

/* EXPRESSION-EVALUATION-SETTER */
Object expression_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,139);
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
			  list_constant_46))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_expression_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qexpression,frame);
  end_expression_evaluation_setter:
    return result;
}

/* EXPRESSION-EVALUATION-GETTER */
Object expression_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,140);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_47;    /* # */

static Object Qforeign_function_declaration;  /* foreign-function-declaration */

/* FOREIGN-FUNCTION-DECLARATION-EVALUATION-SETTER */
Object foreign_function_declaration_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,141);
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
			  list_constant_47))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_foreign_function_declaration_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qforeign_function_declaration,frame);
  end_foreign_function_declaration_evaluation_setter:
    return result;
}

/* FOREIGN-FUNCTION-DECLARATION-EVALUATION-GETTER */
Object foreign_function_declaration_evaluation_getter(text_qm,frame,
	    slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,142);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_48;    /* # */

static Object Qfunction_definition;  /* function-definition */

/* FUNCTION-DEFINITION-EVALUATION-SETTER */
Object function_definition_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,143);
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
			  list_constant_48))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_function_definition_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qfunction_definition,frame);
  end_function_definition_evaluation_setter:
    return result;
}

/* FUNCTION-DEFINITION-EVALUATION-GETTER */
Object function_definition_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,144);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_49;    /* # */

static Object Qgeneric_formula;    /* generic-formula */

/* GENERIC-FORMULA-EVALUATION-SETTER */
Object generic_formula_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,145);
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
			  list_constant_49))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_generic_formula_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qgeneric_formula,frame);
  end_generic_formula_evaluation_setter:
    return result;
}

/* GENERIC-FORMULA-EVALUATION-GETTER */
Object generic_formula_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,146);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_50;    /* # */

static Object Qgeneric_simulation_formula;  /* generic-simulation-formula */

/* GENERIC-SIMULATION-FORMULA-EVALUATION-SETTER */
Object generic_simulation_formula_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,147);
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
			  list_constant_50))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_generic_simulation_formula_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qgeneric_simulation_formula,frame);
  end_generic_simulation_formula_evaluation_setter:
    return result;
}

/* GENERIC-SIMULATION-FORMULA-EVALUATION-GETTER */
Object generic_simulation_formula_evaluation_getter(text_qm,frame,
	    slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,148);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_51;    /* # */

static Object Qgfi_output_values;  /* gfi-output-values */

/* GFI-OUTPUT-VALUES-EVALUATION-SETTER */
Object gfi_output_values_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,149);
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
			  list_constant_51))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_gfi_output_values_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qgfi_output_values,frame);
  end_gfi_output_values_evaluation_setter:
    return result;
}

/* GFI-OUTPUT-VALUES-EVALUATION-GETTER */
Object gfi_output_values_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,150);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_52;    /* # */

static Object Qinstance_formula;   /* instance-formula */

/* INSTANCE-FORMULA-EVALUATION-SETTER */
Object instance_formula_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,151);
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
			  list_constant_52))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_instance_formula_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qinstance_formula,frame);
  end_instance_formula_evaluation_setter:
    return result;
}

/* INSTANCE-FORMULA-EVALUATION-GETTER */
Object instance_formula_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,152);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_53;    /* # */

static Object Qitem_designations_for_model;  /* item-designations-for-model */

/* ITEM-DESIGNATIONS-FOR-MODEL-EVALUATION-SETTER */
Object item_designations_for_model_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,153);
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
			  list_constant_53))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_item_designations_for_model_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qitem_designations_for_model,frame);
  end_item_designations_for_model_evaluation_setter:
    return result;
}

/* ITEM-DESIGNATIONS-FOR-MODEL-EVALUATION-GETTER */
Object item_designations_for_model_evaluation_getter(text_qm,frame,
	    slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,154);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_54;    /* # */

static Object Qlanguage_translation;  /* language-translation */

/* LANGUAGE-TRANSLATION-EVALUATION-SETTER */
Object language_translation_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,155);
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
			  list_constant_54))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_language_translation_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qlanguage_translation,frame);
  end_language_translation_evaluation_setter:
    return result;
}

/* LANGUAGE-TRANSLATION-EVALUATION-GETTER */
Object language_translation_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,156);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_55;    /* # */

static Object Qlist_of_graph_expressions;  /* list-of-graph-expressions */

/* LIST-OF-GRAPH-EXPRESSIONS-EVALUATION-SETTER */
Object list_of_graph_expressions_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,157);
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
			  list_constant_55))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_list_of_graph_expressions_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qlist_of_graph_expressions,frame);
  end_list_of_graph_expressions_evaluation_setter:
    return result;
}

/* LIST-OF-GRAPH-EXPRESSIONS-EVALUATION-GETTER */
Object list_of_graph_expressions_evaluation_getter(text_qm,frame,
	    slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,158);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_56;    /* # */

static Object Qlogical_instance_formula;  /* logical-instance-formula */

/* LOGICAL-INSTANCE-FORMULA-EVALUATION-SETTER */
Object logical_instance_formula_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,159);
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
			  list_constant_56))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_logical_instance_formula_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qlogical_instance_formula,frame);
  end_logical_instance_formula_evaluation_setter:
    return result;
}

/* LOGICAL-INSTANCE-FORMULA-EVALUATION-GETTER */
Object logical_instance_formula_evaluation_getter(text_qm,frame,
	    slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,160);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_57;    /* # */

static Object Qprocedure_definition;  /* procedure-definition */

/* PROCEDURE-DEFINITION-EVALUATION-SETTER */
Object procedure_definition_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,161);
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
			  list_constant_57))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_procedure_definition_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qprocedure_definition,frame);
  end_procedure_definition_evaluation_setter:
    return result;
}

/* PROCEDURE-DEFINITION-EVALUATION-GETTER */
Object procedure_definition_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,162);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_58;    /* # */

static Object Qremote_procedure_declaration;  /* remote-procedure-declaration */

/* REMOTE-PROCEDURE-DECLARATION-EVALUATION-SETTER */
Object remote_procedure_declaration_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,163);
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
			  list_constant_58))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_remote_procedure_declaration_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qremote_procedure_declaration,frame);
  end_remote_procedure_declaration_evaluation_setter:
    return result;
}

/* REMOTE-PROCEDURE-DECLARATION-EVALUATION-GETTER */
Object remote_procedure_declaration_evaluation_getter(text_qm,frame,
	    slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,164);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_59;    /* # */

static Object Qrule;               /* rule */

/* RULE-EVALUATION-SETTER */
Object rule_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,165);
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
			  list_constant_59))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_rule_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qrule,frame);
  end_rule_evaluation_setter:
    return result;
}

/* RULE-EVALUATION-GETTER */
Object rule_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,166);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_60;    /* # */

static Object Qspecific_simulation_formula;  /* specific-simulation-formula */

/* SPECIFIC-SIMULATION-FORMULA-EVALUATION-SETTER */
Object specific_simulation_formula_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,167);
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
			  list_constant_60))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_specific_simulation_formula_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qspecific_simulation_formula,frame);
  end_specific_simulation_formula_evaluation_setter:
    return result;
}

/* SPECIFIC-SIMULATION-FORMULA-EVALUATION-GETTER */
Object specific_simulation_formula_evaluation_getter(text_qm,frame,
	    slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,168);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_61;    /* # */

static Object Qtext_conversion_style_name;  /* text-conversion-style-name */

/* TEXT-CONVERSION-STYLE-NAME-EVALUATION-SETTER */
Object text_conversion_style_name_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,169);
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
			  list_constant_61))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_text_conversion_style_name_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qtext_conversion_style_name,frame);
  end_text_conversion_style_name_evaluation_setter:
    return result;
}

/* TEXT-CONVERSION-STYLE-NAME-EVALUATION-GETTER */
Object text_conversion_style_name_evaluation_getter(text_qm,frame,
	    slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,170);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_62;    /* # */

static Object Qunits_declaration;  /* units-declaration */

/* UNITS-DECLARATION-EVALUATION-SETTER */
Object units_declaration_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,171);
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
			  list_constant_62))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_units_declaration_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qunits_declaration,frame);
  end_units_declaration_evaluation_setter:
    return result;
}

/* UNITS-DECLARATION-EVALUATION-GETTER */
Object units_declaration_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,172);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_63;    /* # */

static Object Quser_menu_choice_expression;  /* user-menu-choice-expression */

/* USER-MENU-CHOICE-EXPRESSION-EVALUATION-SETTER */
Object user_menu_choice_expression_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,173);
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
			  list_constant_63))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_user_menu_choice_expression_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Quser_menu_choice_expression,frame);
  end_user_menu_choice_expression_evaluation_setter:
    return result;
}

/* USER-MENU-CHOICE-EXPRESSION-EVALUATION-GETTER */
Object user_menu_choice_expression_evaluation_getter(text_qm,frame,
	    slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,174);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_64;    /* # */

/* FREE-EVALUATION-SETTER */
Object free_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,175);
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
			  list_constant_64))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_free_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(Nil);
  end_free_evaluation_setter:
    return result;
}

/* FREE-EVALUATION-GETTER */
Object free_evaluation_getter(text_qm,frame,slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(198,176);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_65;    /* # */

static Object Quser_menu_choice_expression_initialization;  /* user-menu-choice-expression-initialization */

/* USER-MENU-CHOICE-EXPRESSION-INITIALIZATION-EVALUATION-SETTER */
Object user_menu_choice_expression_initialization_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,177);
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
			  list_constant_65))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_user_menu_choice_expression_initialization_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,
	    Quser_menu_choice_expression_initialization,frame);
  end_user_menu_choice_expression_initialization_evaluation_setter:
    return result;
}

static Object Qslot_value_writer;  /* slot-value-writer */

static Object string_constant_15;  /* "[deleted attribute]" */

/* USER-MENU-CHOICE-EXPRESSION-INITIALIZATION-EVALUATION-GETTER */
Object user_menu_choice_expression_initialization_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object slot_value_writer_qm, write_symbols_in_lower_case_qm;
    Object write_symbols_parsably_qm, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(198,178);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    6);
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
	      5);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		4);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  3);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    2);
	      slot_value_writer_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_menu_choice_expression_initialization),
		      Qslot_value_writer);
	      if (slot_value_writer_qm) {
		  write_symbols_in_lower_case_qm = T;
		  write_symbols_parsably_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			    0);
		      inline_funcall_2(slot_value_writer_qm,slot_value,frame);
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else
		  twrite(string_constant_15);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_66;    /* # */

static Object Qconstant_variable_designation_qm;  /* constant-variable-designation? */

/* CONSTANT-VARIABLE-DESIGNATION?-EVALUATION-SETTER */
Object constant_variable_designation_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,179);
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
			  list_constant_66))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_constant_variable_designation_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qconstant_variable_designation_qm,
	    frame);
  end_constant_variable_designation_qm_evaluation_setter:
    return result;
}

/* CONSTANT-VARIABLE-DESIGNATION?-EVALUATION-GETTER */
Object constant_variable_designation_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object slot_value_writer_qm, write_symbols_in_lower_case_qm;
    Object write_symbols_parsably_qm, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(198,180);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    6);
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
	      5);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		4);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  3);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    2);
	      slot_value_writer_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconstant_variable_designation_qm),
		      Qslot_value_writer);
	      if (slot_value_writer_qm) {
		  write_symbols_in_lower_case_qm = T;
		  write_symbols_parsably_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			    0);
		      inline_funcall_2(slot_value_writer_qm,slot_value,frame);
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else
		  twrite(string_constant_15);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_67;    /* # */

static Object Qgfi_interface_object;  /* gfi-interface-object */

/* GFI-INTERFACE-OBJECT-EVALUATION-SETTER */
Object gfi_interface_object_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,181);
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
			  list_constant_67))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_gfi_interface_object_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qgfi_interface_object,frame);
  end_gfi_interface_object_evaluation_setter:
    return result;
}

/* GFI-INTERFACE-OBJECT-EVALUATION-GETTER */
Object gfi_interface_object_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object slot_value_writer_qm, write_symbols_in_lower_case_qm;
    Object write_symbols_parsably_qm, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(198,182);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    6);
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
	      5);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		4);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  3);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    2);
	      slot_value_writer_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgfi_interface_object),
		      Qslot_value_writer);
	      if (slot_value_writer_qm) {
		  write_symbols_in_lower_case_qm = T;
		  write_symbols_parsably_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			    0);
		      inline_funcall_2(slot_value_writer_qm,slot_value,frame);
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else
		  twrite(string_constant_15);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_68;    /* # */

static Object Qgfi_file_pathname;  /* gfi-file-pathname */

/* GFI-FILE-PATHNAME-EVALUATION-SETTER */
Object gfi_file_pathname_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(198,183);
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
			  list_constant_68))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_gfi_file_pathname_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_8;
    result = parse_text_string(3,temp_1,Qgfi_file_pathname,frame);
  end_gfi_file_pathname_evaluation_setter:
    return result;
}

/* GFI-FILE-PATHNAME-EVALUATION-GETTER */
Object gfi_file_pathname_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object slot_value_writer_qm, write_symbols_in_lower_case_qm;
    Object write_symbols_parsably_qm, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(198,184);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    6);
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
	      5);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		4);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  3);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    2);
	      slot_value_writer_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgfi_file_pathname),
		      Qslot_value_writer);
	      if (slot_value_writer_qm) {
		  write_symbols_in_lower_case_qm = T;
		  write_symbols_parsably_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			    0);
		      inline_funcall_2(slot_value_writer_qm,slot_value,frame);
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else
		  twrite(string_constant_15);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

void grammar4a_INIT()
{
    Object temp, temp_1, g2_array_length_evaluation_setter_1;
    Object g2_array_length_evaluation_getter_1;
    Object element_type_evaluation_getter_1;
    Object list_of_item_and_datum_constants_qm_evaluation_setter_1;
    Object list_of_item_and_datum_constants_qm_evaluation_getter_1;
    Object constant_designation_list_qm_evaluation_setter_1;
    Object constant_designation_list_qm_evaluation_getter_1;
    Object list_of_datum_constants_evaluation_setter_1;
    Object list_of_datum_constants_evaluation_getter_1;
    Object symbol_list_evaluation_setter_1, symbol_list_evaluation_getter_1;
    Object whole_string_list_evaluation_setter_1;
    Object whole_string_list_evaluation_getter_1;
    Object truth_value_list_evaluation_setter_1;
    Object truth_value_list_evaluation_getter_1;
    Object quantity_list_evaluation_setter_1;
    Object quantity_list_evaluation_getter_1, float_list_evaluation_setter_1;
    Object float_list_evaluation_getter_1, integer_list_evaluation_setter_1;
    Object integer_list_evaluation_getter_1, alignment_evaluation_setter_1;
    Object alignment_evaluation_getter_1;
    Object when_to_allow_multiple_menus_evaluation_setter_1;
    Object when_to_allow_multiple_menus_evaluation_getter_1;
    Object current_language_evaluation_setter_1;
    Object current_language_evaluation_getter_1;
    Object color_menu_ordering_evaluation_setter_1;
    Object color_menu_ordering_evaluation_getter_1;
    Object color_set_spec_evaluation_setter_1;
    Object color_set_spec_evaluation_getter_1;
    Object number_of_menu_columns_spec_evaluation_setter_1;
    Object number_of_menu_columns_spec_evaluation_getter_1;
    Object image_palette_evaluation_setter_1;
    Object image_palette_evaluation_getter_1;
    Object warning_message_level_evaluation_setter_1;
    Object warning_message_level_evaluation_getter_1;
    Object tracing_message_level_evaluation_setter_1;
    Object tracing_message_level_evaluation_getter_1;
    Object breakpoint_level_evaluation_setter_1;
    Object breakpoint_level_evaluation_getter_1;
    Object source_stepping_level_evaluation_setter_1;
    Object source_stepping_level_evaluation_getter_1;
    Object interface_warning_message_level_evaluation_setter_1;
    Object interface_warning_message_level_evaluation_getter_1;
    Object display_expression_evaluation_setter_1;
    Object display_expression_evaluation_getter_1;
    Object embedded_rule_evaluation_setter_1;
    Object embedded_rule_evaluation_getter_1, expression_evaluation_setter_1;
    Object expression_evaluation_getter_1;
    Object foreign_function_declaration_evaluation_setter_1;
    Object foreign_function_declaration_evaluation_getter_1;
    Object function_definition_evaluation_setter_1;
    Object function_definition_evaluation_getter_1;
    Object generic_formula_evaluation_setter_1;
    Object generic_formula_evaluation_getter_1;
    Object generic_simulation_formula_evaluation_setter_1;
    Object generic_simulation_formula_evaluation_getter_1;
    Object gfi_output_values_evaluation_setter_1;
    Object gfi_output_values_evaluation_getter_1;
    Object instance_formula_evaluation_setter_1;
    Object instance_formula_evaluation_getter_1;
    Object item_designations_for_model_evaluation_setter_1;
    Object item_designations_for_model_evaluation_getter_1;
    Object language_translation_evaluation_setter_1;
    Object language_translation_evaluation_getter_1;
    Object list_of_graph_expressions_evaluation_setter_1;
    Object list_of_graph_expressions_evaluation_getter_1;
    Object logical_instance_formula_evaluation_setter_1;
    Object logical_instance_formula_evaluation_getter_1;
    Object procedure_definition_evaluation_setter_1;
    Object procedure_definition_evaluation_getter_1;
    Object remote_procedure_declaration_evaluation_setter_1;
    Object remote_procedure_declaration_evaluation_getter_1;
    Object rule_evaluation_setter_1, rule_evaluation_getter_1;
    Object specific_simulation_formula_evaluation_setter_1;
    Object specific_simulation_formula_evaluation_getter_1;
    Object text_conversion_style_name_evaluation_setter_1;
    Object text_conversion_style_name_evaluation_getter_1;
    Object units_declaration_evaluation_setter_1;
    Object units_declaration_evaluation_getter_1;
    Object user_menu_choice_expression_evaluation_setter_1;
    Object user_menu_choice_expression_evaluation_getter_1;
    Object free_evaluation_setter_1, free_evaluation_getter_1;
    Object user_menu_choice_expression_initialization_evaluation_setter_1;
    Object user_menu_choice_expression_initialization_evaluation_getter_1;
    Object constant_variable_designation_qm_evaluation_setter_1;
    Object constant_variable_designation_qm_evaluation_getter_1;
    Object gfi_interface_object_evaluation_setter_1;
    Object gfi_interface_object_evaluation_getter_1;
    Object gfi_file_pathname_evaluation_setter_1;
    Object gfi_file_pathname_evaluation_getter_1;
    Object Qnamed, Qtype_specification_simple_expansion, AB_package;
    Object Qtext_category_slot_access_extracter, Qcategory_extracter_function;
    Object Qfree, Qtext_category_slot_access_committer;
    Object Qcategory_committer_function, list_constant_248, list_constant_247;
    Object list_constant_92, list_constant_76, list_constant_217, Qab_or;
    Object Qinterface_warning_message_level, list_constant_246;
    Object list_constant_216, Qimage_palette, list_constant_245;
    Object list_constant_244, list_constant_243, list_constant_242;
    Object list_constant_241, list_constant_240, list_constant_239;
    Object list_constant_238, Qcustom_colors, Qcustom_grays, Qextended_colors;
    Object Qextended_grays, Qstandard_colors, Qstandard_grays;
    Object Qblack_and_white, list_constant_237, list_constant_236;
    Object Qnumber_of_menu_columns_spec, Qcolor_set_spec, list_constant_235;
    Object list_constant_234, list_constant_233, Qcolor_or_metacolor;
    Object Qstandard_set, Qall, list_constant_232, list_constant_228;
    Object Qcolor_menu_ordering, Qhue, Qalphabetic, Qintensity;
    Object Qcurrent_language, Qwhen_to_allow_multiple_menus, Qalways;
    Object Qalignment, Qright, Qcenter, Qleft, Qinteger_list, Qfloat_list;
    Object Qquantity_list, Qtruth_value_list, Qwhole_string_list, Qsymbol_list;
    Object Qlist_of_datum_constants, Qconstant_designation_list_qm;
    Object list_constant_231, list_constant_230, list_constant_229;
    Object Qlist_of_item_and_datum_constants_qm, list_constant_227;
    Object list_constant_226, list_constant_225, list_constant_224;
    Object list_constant_223, list_constant_222, list_constant_221;
    Object list_constant_220, list_constant_219, list_constant_218;
    Object list_constant_215, Qelement_type, list_constant_214;
    Object Qset_g2_list_sequence, Qget_g2_list_sequence;
    Object Qinitial_g2_list_sequence, list_constant_210, list_constant_213;
    Object Qg2_list_sequence, Qg2_list, Qvirtual_attributes_local_to_class;
    Object Qset_g2_array_sequence, Qget_g2_array_sequence;
    Object Qinitial_g2_array_sequence, list_constant_212, list_constant_211;
    Object Qg2_array_sequence, Qg2_array, Qset_history_using_unix_time;
    Object Qget_history_using_unix_time, Qinitial_history_using_unix_time;
    Object list_constant_209, list_constant_201, Qhistory_using_unix_time;
    Object Qset_history, Qget_history, Qinitial_history, Qhistory;
    Object Qexclude_from_wildcard_denotation, list_constant_208;
    Object list_constant_207, list_constant_206, list_constant_205;
    Object list_constant_204, list_constant_203, list_constant_202;
    Object Qget_effective_data_type, Qinitial_effective_data_type;
    Object Qeffective_data_type, list_constant_178, list_constant_184;
    Object Qget_last_recorded_value_text, Qinitial_last_recorded_value_text;
    Object list_constant_200, Qlast_recorded_value_text;
    Object Qvariable_or_parameter, Qset_value_structure_using_unix_time;
    Object Qget_value_structure_using_unix_time;
    Object Qinitial_value_structure_using_unix_time, list_constant_199;
    Object Qvalue_structure_using_unix_time, Qset_value_structure;
    Object Qget_value_structure, Qinitial_value_structure, Qvalue_structure;
    Object list_constant_198, list_constant_197, list_constant_196;
    Object list_constant_195, list_constant_194, list_constant_193;
    Object list_constant_192, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qset_evaluation_attributes, Qget_evaluation_attributes;
    Object Qinitial_evaluation_attributes, list_constant_191;
    Object list_constant_190, Qevaluation_attributes, list_constant_189;
    Object list_constant_188, list_constant_187, list_constant_186;
    Object list_constant_185, Qno_item, list_constant_183, list_constant_182;
    Object list_constant_181, list_constant_180, list_constant_179;
    Object list_constant_177, list_constant_176, list_constant_175;
    Object list_constant_174, list_constant_173, list_constant_172;
    Object list_constant_171, list_constant_170, Qnetwork_interface;
    Object Qnon_action_button, Qtrend_chart, Qsimulation_subtable;
    Object Qfreeform_table, Qreadout_table, Qmeter, Qdial, Quser_menu_choice;
    Object Qgeneric_action_button, Qprocedure, list_constant_169;
    Object list_constant_168, Qdesignation_list, Qcall_assignment_action;
    Object list_constant_82, Qexpression_list, Qdesignation, list_constant_167;
    Object Qcall_action, list_constant_166, list_constant_165, Qmake_transient;
    Object list_constant_164, Qmake_permanent, list_constant_163;
    Object list_constant_84, Qmake_subworkspace, list_constant_162;
    Object list_constant_152, Qcreate_by_cloning, list_constant_161;
    Object Qcreate_explanation, list_constant_160, Qcreate_connection_spec;
    Object Qother, Qcreate_connection, list_constant_159, list_constant_90;
    Object Qnupec_synchronize, list_constant_158, Qupdate, list_constant_157;
    Object list_constant_114, Qtransfer, list_constant_156, Qg2_list_remove;
    Object list_constant_155, Qg2_list_insert, list_constant_154;
    Object list_constant_123, list_constant_153, Qcreate, list_constant_151;
    Object Qremove_relation, list_constant_150, Qadd_relation;
    Object list_constant_149, Qkb_change, list_constant_148, list_constant_147;
    Object Qstart_thread, list_constant_146, Qstart, list_constant_145;
    Object Qcolor_changes, Qchange_item_color_pattern, list_constant_144;
    Object Qchange_item_color, list_constant_143, list_constant_142, Qhide;
    Object Qshow_or_hide_argument_list, list_constant_141, Qshow;
    Object list_constant_140, Qinform_option, Qmessage_text;
    Object Qmessage_designation, Qinform, list_constant_139, Qhalt;
    Object list_constant_138, Qinvoke, list_constant_137;
    Object Qwith_unsaved_changes, list_constant_136, Qin_the_tracked_item_set;
    Object list_constant_135, Qattribute_name, list_constant_134;
    Object list_constant_107, Qceases_to_be_related, list_constant_133;
    Object Qbecomes_related, list_constant_132, Qcontaining_string;
    Object list_constant_131, Qcontaining_symbol, list_constant_130;
    Object Qfails_to_receive_a_value, list_constant_129, Qwith_notes;
    Object list_constant_128, list_constant_127, Qfound_on_the_workspace;
    Object list_constant_126, Qin_the_category, list_constant_125;
    Object Qwhich_has_the_focal_class, list_constant_124;
    Object Qwhich_has_the_focal_object, list_constant_85, list_constant_83;
    Object list_constant_86, list_constant_81, list_constant_122;
    Object Qnumber_of_datapoints, list_constant_121, list_constant_120;
    Object Qrate_of_change, list_constant_104, list_constant_119, Qintegral;
    Object list_constant_118, Qstandard_deviation, list_constant_117;
    Object Qminimum_value, list_constant_116, Qmaximum_value;
    Object list_constant_115, Qsum_of_values, list_constant_113;
    Object Qaverage_value, list_constant_112, list_constant_79;
    Object Qcollection_time_of_previous_datapoint, list_constant_111;
    Object Qvalue_of_previous_datapoint, list_constant_110, Qhistoric_value;
    Object list_constant_109, Qinterpolated_value, list_constant_108;
    Object Qis_not_related, list_constant_106, Qis_related, list_constant_105;
    Object Qab_format, list_constant_103, Qg2_list_or_sequence_member_p;
    Object list_constant_102, Qg2_list_or_sequence_length, list_constant_101;
    Object list_constant_94, Qfor_every_literal, list_constant_100;
    Object Qthere_exists_literal, list_constant_99, Qaggregated_average;
    Object list_constant_98, list_constant_97, Qminimum, list_constant_96;
    Object Qmaximum, list_constant_95, Qproduct, Qscope, list_constant_93;
    Object Qsum, list_constant_91, Qdistance_between_and_the_nearest;
    Object list_constant_89, list_constant_88, Qdistance_between;
    Object list_constant_87, Qicon_color_of, Qexists, Qnot_same_as, Qsame_as;
    Object Qis_of_class, list_constant_80, Qis_not, list_constant_78, Qis;
    Object list_constant_77, Qhas_a_name, Qreparse_nth_element_designation;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, Qwrite_g2_array_length_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_g2_array_length_for_slot;
    Object string_constant_34, Qwrite_list_of_datum_constants_from_slot;
    Object Qwrite_list_of_item_and_datum_constants_qm_from_slot;
    Object Qwrite_quoted_symbol_list_from_slot, Qquoted_symbol_list;
    Object Qwrite_symbol_list_from_slot, Qwrite_truth_value_list_from_slot;
    Object Qwrite_whole_string_list_from_slot, Qwrite_float_list_from_slot;
    Object Qwrite_integer_list_from_slot, Qwrite_quantity_list_from_slot;
    Object Qwrite_constant_designation_list_from_slot;
    Object Qconstant_designation_list;
    Object Qwrite_constant_designation_list_qm_from_slot;
    Object Qcompile_list_of_datum_constants_for_slot;
    Object Qcompile_list_of_item_and_datum_constants_qm_for_slot;
    Object Qcompile_quoted_symbol_list_for_slot, Qcompile_symbol_list_for_slot;
    Object Qcompile_truth_value_list_for_slot;
    Object Qcompile_whole_string_list_for_slot, Qcompile_float_list_for_slot;
    Object Qcompile_integer_list_for_slot, Qcompile_quantity_list_for_slot;
    Object Qcompile_constant_designation_list_for_slot;
    Object Qcompile_constant_designation_list_qm_for_slot, string_constant_33;
    Object string_constant_32, Qquoted_symbol_list_and_datum;
    Object Qconstant_designation_quoted_symbol_list_and_datum;
    Object Qsymbol_list_with_and, Qtruth_value_attribute, Qwhole_string;
    Object Qlong_list, Qconstant_designation;
    Object Qwrite_constant_variable_designation_qm_from_slot;
    Object Qcompile_constant_variable_designation_qm_for_slot;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object Qtranslate_role_local_name_and_preposition;
    Object Qtranslate_role_and_preposition;
    Object Qwrite_constant_designation_from_slot, string_constant_28;
    Object string_constant_27, string_constant_26, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, Qend;
    Object Qfilter_out_the_text_of_and_region_icon_color;
    Object Qfilter_out_the_text_of_as_a_special_case, string_constant_17;
    Object list_constant_75, Qweeks, Qdays, Qhours, Qminutes, Qseconds;
    Object string_constant_16, list_constant_74, Qweek, Qday, Qhour, Qminute;
    Object list_constant_73, list_constant_72, Qbelow, Qabove, Qby, Qconnected;
    Object Qvia, Qacross, Quntil, Qover, Qduring, Qper, Qupon, Qin, Qon;
    Object Qbetween, Qwith, Qab_at, Qfor, Qof, Qan, Qa, Qone, Qany, Qthat;
    Object Qelse, Qthen, Qab_if, list_constant_71, Qinterpolated, Qcurrent;
    Object Qpast, Qago, Qrules, Qsend, Qconclude, Qfocus, Qfalse, Qtrue, Qdown;
    Object list_constant_70, Qnearest, Qthis, Qoutput, Qinput, Qyes, Qab_no;
    Object Qmoved, Qundefined, Qshould, Qcould, Qwill, Qwere, Qwas, Qbecomes;
    Object Qhas, Qbe, Qto, Qchange, Qrate, Qdeviation, Qab_standard, Qaverage;
    Object list_constant_69, Qsimulated, Qcolor_pattern, Qchecking, Qwait;
    Object Qexit, Qrepeat, Qinfer, Qcall, Qbegin, Qworkspace, Qsubworkspace;
    Object Qeverything, Qnothing, Qthere, Qcollection, Qexpiration, Qsame;
    Object Qgiving, Qusing;

    x_note_fn_call(198,185);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qab_if = STATIC_SYMBOL("IF",AB_package);
    Qthen = STATIC_SYMBOL("THEN",AB_package);
    Qelse = STATIC_SYMBOL("ELSE",AB_package);
    Qthat = STATIC_SYMBOL("THAT",AB_package);
    Qany = STATIC_SYMBOL("ANY",AB_package);
    Qone = STATIC_SYMBOL("ONE",AB_package);
    Qall = STATIC_SYMBOL("ALL",AB_package);
    Qa = STATIC_SYMBOL("A",AB_package);
    Qan = STATIC_SYMBOL("AN",AB_package);
    Qof = STATIC_SYMBOL("OF",AB_package);
    Qfor = STATIC_SYMBOL("FOR",AB_package);
    Qab_at = STATIC_SYMBOL("AT",AB_package);
    Qwith = STATIC_SYMBOL("WITH",AB_package);
    Qbetween = STATIC_SYMBOL("BETWEEN",AB_package);
    Qon = STATIC_SYMBOL("ON",AB_package);
    Qin = STATIC_SYMBOL("IN",AB_package);
    Qupon = STATIC_SYMBOL("UPON",AB_package);
    Qper = STATIC_SYMBOL("PER",AB_package);
    Qduring = STATIC_SYMBOL("DURING",AB_package);
    Qover = STATIC_SYMBOL("OVER",AB_package);
    Quntil = STATIC_SYMBOL("UNTIL",AB_package);
    Qacross = STATIC_SYMBOL("ACROSS",AB_package);
    Qvia = STATIC_SYMBOL("VIA",AB_package);
    Qconnected = STATIC_SYMBOL("CONNECTED",AB_package);
    Qby = STATIC_SYMBOL("BY",AB_package);
    Qabove = STATIC_SYMBOL("ABOVE",AB_package);
    Qbelow = STATIC_SYMBOL("BELOW",AB_package);
    Qdown = STATIC_SYMBOL("DOWN",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qminute = STATIC_SYMBOL("MINUTE",AB_package);
    Qminutes = STATIC_SYMBOL("MINUTES",AB_package);
    Qhour = STATIC_SYMBOL("HOUR",AB_package);
    Qhours = STATIC_SYMBOL("HOURS",AB_package);
    Qday = STATIC_SYMBOL("DAY",AB_package);
    Qdays = STATIC_SYMBOL("DAYS",AB_package);
    Qweek = STATIC_SYMBOL("WEEK",AB_package);
    Qweeks = STATIC_SYMBOL("WEEKS",AB_package);
    Qfocus = STATIC_SYMBOL("FOCUS",AB_package);
    Qinvoke = STATIC_SYMBOL("INVOKE",AB_package);
    Qconclude = STATIC_SYMBOL("CONCLUDE",AB_package);
    Qsend = STATIC_SYMBOL("SEND",AB_package);
    Qrules = STATIC_SYMBOL("RULES",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qago = STATIC_SYMBOL("AGO",AB_package);
    Qpast = STATIC_SYMBOL("PAST",AB_package);
    Qcurrent = STATIC_SYMBOL("CURRENT",AB_package);
    Qinterpolated = STATIC_SYMBOL("INTERPOLATED",AB_package);
    Qmaximum = STATIC_SYMBOL("MAXIMUM",AB_package);
    Qminimum = STATIC_SYMBOL("MINIMUM",AB_package);
    Qaverage = STATIC_SYMBOL("AVERAGE",AB_package);
    Qsum = STATIC_SYMBOL("SUM",AB_package);
    Qproduct = STATIC_SYMBOL("PRODUCT",AB_package);
    Qab_standard = STATIC_SYMBOL("STANDARD",AB_package);
    Qdeviation = STATIC_SYMBOL("DEVIATION",AB_package);
    Qrate = STATIC_SYMBOL("RATE",AB_package);
    Qchange = STATIC_SYMBOL("CHANGE",AB_package);
    Qintegral = STATIC_SYMBOL("INTEGRAL",AB_package);
    Qis = STATIC_SYMBOL("IS",AB_package);
    Qto = STATIC_SYMBOL("TO",AB_package);
    Qbe = STATIC_SYMBOL("BE",AB_package);
    Qhas = STATIC_SYMBOL("HAS",AB_package);
    Qbecomes = STATIC_SYMBOL("BECOMES",AB_package);
    Qwas = STATIC_SYMBOL("WAS",AB_package);
    Qwere = STATIC_SYMBOL("WERE",AB_package);
    Qwill = STATIC_SYMBOL("WILL",AB_package);
    Qcould = STATIC_SYMBOL("COULD",AB_package);
    Qshould = STATIC_SYMBOL("SHOULD",AB_package);
    Qab_format = STATIC_SYMBOL("FORMAT",AB_package);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qundefined = STATIC_SYMBOL("UNDEFINED",AB_package);
    Qmoved = STATIC_SYMBOL("MOVED",AB_package);
    Qab_no = STATIC_SYMBOL("NO",AB_package);
    Qyes = STATIC_SYMBOL("YES",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qthis = STATIC_SYMBOL("THIS",AB_package);
    Qnearest = STATIC_SYMBOL("NEAREST",AB_package);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    Qgiving = STATIC_SYMBOL("GIVING",AB_package);
    Qsame = STATIC_SYMBOL("SAME",AB_package);
    Qexpiration = STATIC_SYMBOL("EXPIRATION",AB_package);
    Qcollection = STATIC_SYMBOL("COLLECTION",AB_package);
    Qthere = STATIC_SYMBOL("THERE",AB_package);
    Qexists = STATIC_SYMBOL("EXISTS",AB_package);
    Qnothing = STATIC_SYMBOL("NOTHING",AB_package);
    Qeverything = STATIC_SYMBOL("EVERYTHING",AB_package);
    Qsubworkspace = STATIC_SYMBOL("SUBWORKSPACE",AB_package);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qbegin = STATIC_SYMBOL("BEGIN",AB_package);
    Qend = STATIC_SYMBOL("END",AB_package);
    Qcall = STATIC_SYMBOL("CALL",AB_package);
    Qstart = STATIC_SYMBOL("START",AB_package);
    Qinfer = STATIC_SYMBOL("INFER",AB_package);
    Qrepeat = STATIC_SYMBOL("REPEAT",AB_package);
    Qexit = STATIC_SYMBOL("EXIT",AB_package);
    Qwait = STATIC_SYMBOL("WAIT",AB_package);
    Qchecking = STATIC_SYMBOL("CHECKING",AB_package);
    Qcolor_pattern = STATIC_SYMBOL("COLOR-PATTERN",AB_package);
    Qsimulated = STATIC_SYMBOL("SIMULATED",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qusing = STATIC_SYMBOL("USING",AB_package);
    list_constant_69 = STATIC_CONS(Qusing,Qnil);
    list_constant_70 = STATIC_LIST_STAR((SI_Long)32L,Qsymbol,Qgiving,
	    Qnearest,Qsame,Qconnected,Qexpiration,Qcollection,Qthere,
	    Qexists,Qnothing,Qeverything,Qnil,Qsubworkspace,Qworkspace,
	    Qbegin,Qend,Qreturn,Qcall,Qstart,Qinfer,Qrepeat,Qexit,Qgo,
	    Qwait,Qchecking,Qdo,Qcase,Qminus,Qcolor_pattern,Qsimulated,
	    Qavailable_frame_vector,list_constant_69);
    list_constant_71 = STATIC_LIST_STAR((SI_Long)32L,Qaverage,Qsum,
	    Qproduct,Qcount,Qab_standard,Qdeviation,Qrate,Qchange,
	    Qintegral,Qis,Qto,Qbe,Qhas,Qbecomes,Qwas,Qwere,Qwill,Qcould,
	    Qshould,Qab_format,Qname,Qundefined,Qmoved,Qab_no,Qyes,Qnone,
	    Qinput,Qoutput,Qthis,Qnearest,Qnamed,list_constant_70);
    list_constant_72 = STATIC_LIST_STAR((SI_Long)32L,Qdown,Qand,Qab_or,
	    Qnot,Qtrue,Qfalse,Qsecond,Qseconds,Qminute,Qminutes,Qhour,
	    Qhours,Qday,Qdays,Qweek,Qweeks,Qfocus,Qinvoke,Qset,Qconclude,
	    Qsend,Qrules,Qvalue,Qvalues,Qago,Qpast,Qcurrent,Qlast,
	    Qinterpolated,Qmaximum,Qminimum,list_constant_71);
    list_constant_73 = STATIC_LIST_STAR((SI_Long)32L,Qab_if,Qthen,Qelse,
	    Qwhen,Qthat,Qthe,Qfirst,Qany,Qevery,Qone,Qall,Qa,Qan,Qof,Qfor,
	    Qab_at,Qwith,Qbetween,Qon,Qin,Qupon,Qper,Qduring,Qover,Quntil,
	    Qacross,Qvia,Qconnected,Qby,Qabove,Qbelow,list_constant_72);
    reserve_words(list_constant_73);
    list_constant_74 = STATIC_LIST((SI_Long)5L,Qsecond,Qminute,Qhour,Qday,
	    Qweek);
    reserve_words(list_constant_74);
    string_constant_16 = 
	    STATIC_STRING("1p1m83-D*y1m9k9l1m83-D*y1m9k833Ty1m83-D*y1m9k833Oy1m83-D*y1m9k833+y1m83-D*y1m9k83Fty");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsecond);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_16));
    list_constant_75 = STATIC_LIST((SI_Long)5L,Qseconds,Qminutes,Qhours,
	    Qdays,Qweeks);
    reserve_words(list_constant_75);
    string_constant_17 = 
	    STATIC_STRING("1p1m83lYy1m9k832Ky1m83lYy1m9k83-6my1m83lYy1m9k83-*Ky1m83lYy1m9k83uey1m83lYy1m9k83-Ggy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_17));
    Qfilter_out_the_text_of_as_a_special_case = 
	    STATIC_SYMBOL("FILTER-OUT-THE-TEXT-OF-AS-A-SPECIAL-CASE",
	    AB_package);
    Qfilter_out_the_text_of_and_region_icon_color = 
	    STATIC_SYMBOL("FILTER-OUT-THE-TEXT-OF-AND-REGION-ICON-COLOR",
	    AB_package);
    Qtranslate_role_and_preposition = 
	    STATIC_SYMBOL("TRANSLATE-ROLE-AND-PREPOSITION",AB_package);
    Qtranslate_role_local_name_and_preposition = 
	    STATIC_SYMBOL("TRANSLATE-ROLE-LOCAL-NAME-AND-PREPOSITION",
	    AB_package);
    string_constant_18 = 
	    STATIC_STRING("13Qy1m833ny834Hy1m833ny83BFy1m833ny1n1m9k9l83gFy833ny1o833ny1o1m9k9l83*my1m9k83-Ty833ny1n9lmo9m1o833ny1p1m9k9l83*my83*Zy1m9k83-T");
    string_constant_19 = 
	    STATIC_STRING("y833ny1n9l2lmnp9n1n833ny1q1m9k9l83-Gy1m9k83=my83*my1m9k83-Ty833ny1n9l1n830=ymoq1n833ny1r1m9k9l83-Gy1m9k83=my83*my83*Zy1m9k83-Ty8");
    string_constant_20 = 
	    STATIC_STRING("33ny1n9l2l1n830=ymopr1o83gFy1m83-Gy83t=y1mlm9o1o83gFy1n83-Gy83*Zy83t=y1nlmn9p1n83gFy1m1m9k83*qy1m9k83-Ty1n834Zy83*qy83=uy1n83gFy");
    string_constant_21 = 
	    STATIC_STRING("1n1m9k83*qy83*Zy1m9k83-Ty2l1n834Zy83*qy83=uym1n83gFy1m1m9k83b5y1m9k83-Ty1n834Zy83b5y83=uy1n83gFy1n1m9k83b5y83*Zy1m9k83-Ty2l1n834");
    string_constant_22 = 
	    STATIC_STRING("Zy83b5y83=uym1n83t=y1m1m9k8319y1m9k83gHy83key1n83t=y1m1m9k83Igy1m9k83=3y83gBy1n83t=y1p1m9k83Igy1m9k83=Gy1m9k9l839jy1m9k83-Ty1m83");
    string_constant_23 = 
	    STATIC_STRING("pqyo1n83t=y1p1m9k83Igy1m9k83=Gy1m9k9l1m9k83dy1m9k83=3y83f8y1n83t=y1p1m9k83Igy1m9k83=Gy1m9k83=ay1m9k83dy1m9k83=3y83f8y1n83t=y1p1m");
    string_constant_24 = 
	    STATIC_STRING("9k83Igy1m9k83=Gy1m9k9l1m9k83dy1m9k83-Ty83f8y1n83t=y1p1m9k83Igy1m9k83=Gy1m9k83=ay1m9k83dy1m9k83-Ty83f8y1n83t=y1p1m9k83Igy1m9k83=G");
    string_constant_25 = 
	    STATIC_STRING("y1m9k9l1m9k83py1m9k83-Ty83f9y1n83t=y1p1m9k83Igy1m9k83=Gy1m9k83=ay1m9k83py1m9k83-Ty83f9y1n83t=y1p1m9k83=Gy1m9k9l1m9k83dy1m9k9q1m9");
    string_constant_26 = 
	    STATIC_STRING("k83-Ty83poy1n83t=y1p1m9k83=Gy1m9k83=ay1m9k83dy1m9k9q1m9k83-Ty83poy1n83t=y1p1m9k83=Gy1m9k9l1m9k83py1m9k9q1m9k83-Ty83ppy1n83t=y1p1");
    string_constant_27 = 
	    STATIC_STRING("m9k83=Gy1m9k83=ay1m9k83py1m9k9q1m9k83-Ty83ppy1n83t=y1o1m9k83=Gy1m9k83gxy1m9k9q1m9k83-Ty83pny1n83t=y1o1m9k83=Gy1m9k83=ay1m9k9q1m9");
    string_constant_28 = 
	    STATIC_STRING("k83-Ty83pny1m83-OOy833ny1m83-OOy1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qfilter_out_the_text_of_as_a_special_case);
    push_optimized_constant(Qfilter_out_the_text_of_and_region_icon_color);
    push_optimized_constant(Qtranslate_role_and_preposition);
    push_optimized_constant(Qtranslate_role_local_name_and_preposition);
    push_optimized_constant(Qend);
    add_grammar_rules_function(regenerate_optimized_constant(list(11,
	    string_constant_18,string_constant_19,string_constant_20,
	    string_constant_21,string_constant_22,string_constant_23,
	    string_constant_24,string_constant_25,string_constant_26,
	    string_constant_27,string_constant_28)));
    Qconstant_designation = STATIC_SYMBOL("CONSTANT-DESIGNATION",AB_package);
    Qwrite_constant_designation_from_slot = 
	    STATIC_SYMBOL("WRITE-CONSTANT-DESIGNATION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_constant_designation_from_slot,
	    STATIC_FUNCTION(write_constant_designation_from_slot,NIL,FALSE,
	    2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qconstant_designation,
	    SYMBOL_FUNCTION(Qwrite_constant_designation_from_slot),
	    Qslot_value_writer);
    string_constant_29 = 
	    STATIC_STRING("1t1m83-OQy83-GSy1m83-OQy1n1m9k9l83gFy833ny1m83-OQy1n1m9k9l83-OMy833ny1o83-OMy1m83*my1m9k83-Ty1mlm9m1o83-OMy1o83-Gy1m9k83=my83*my");
    string_constant_30 = 
	    STATIC_STRING("1m9k83-Ty1n830=yln9m1o83-OMy1n83*my83*Zy1m9k83-Ty1nlmn9n1o83-OMy1p83-Gy1m9k83=my83*my83*Zy1m9k83-Ty1n830=yln9m1m8383y83-OQy1m838");
    string_constant_31 = STATIC_STRING("3y1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qtranslate_role_and_preposition);
    push_optimized_constant(Qtranslate_role_local_name_and_preposition);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_29,
	    string_constant_30,string_constant_31)));
    Qconstant_variable_designation_qm = 
	    STATIC_SYMBOL("CONSTANT-VARIABLE-DESIGNATION\?",AB_package);
    Qcompile_constant_variable_designation_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-CONSTANT-VARIABLE-DESIGNATION\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_constant_variable_designation_qm_for_slot,
	    STATIC_FUNCTION(compile_constant_variable_designation_qm_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qconstant_variable_designation_qm,
	    SYMBOL_FUNCTION(Qcompile_constant_variable_designation_qm_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qconstant_variable_designation_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_76 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_76,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_constant_variable_designation_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-CONSTANT-VARIABLE-DESIGNATION\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_constant_variable_designation_qm_from_slot,
	    STATIC_FUNCTION(write_constant_variable_designation_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qconstant_variable_designation_qm,
	    SYMBOL_FUNCTION(Qwrite_constant_variable_designation_qm_from_slot),
	    Qslot_value_writer);
    Qconstant_designation_list_qm = 
	    STATIC_SYMBOL("CONSTANT-DESIGNATION-LIST\?",AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    add_grammar_rules_for_list(6,Qconstant_designation_list_qm,
	    Qconstant_designation,Qcm,Nil,Qnone,Nil);
    Qquantity_list = STATIC_SYMBOL("QUANTITY-LIST",AB_package);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    add_grammar_rules_for_list(6,Qquantity_list,Qquantity,Qcm,Nil,Nil,Nil);
    Qinteger_list = STATIC_SYMBOL("INTEGER-LIST",AB_package);
    add_grammar_rules_for_list(6,Qinteger_list,Qinteger,Qcm,Nil,Nil,Nil);
    Qlong_list = STATIC_SYMBOL("LONG-LIST",AB_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    add_grammar_rules_for_list(6,Qlong_list,Qlong,Qcm,Nil,Nil,Nil);
    Qfloat_list = STATIC_SYMBOL("FLOAT-LIST",AB_package);
    add_grammar_rules_for_list(6,Qfloat_list,Qfloat,Qcm,Nil,Nil,Nil);
    Qwhole_string_list = STATIC_SYMBOL("WHOLE-STRING-LIST",AB_package);
    Qwhole_string = STATIC_SYMBOL("WHOLE-STRING",AB_package);
    add_grammar_rules_for_list(6,Qwhole_string_list,Qwhole_string,Qcm,Nil,
	    Nil,Nil);
    Qtruth_value_list = STATIC_SYMBOL("TRUTH-VALUE-LIST",AB_package);
    Qtruth_value_attribute = STATIC_SYMBOL("TRUTH-VALUE-ATTRIBUTE",AB_package);
    add_grammar_rules_for_list(6,Qtruth_value_list,Qtruth_value_attribute,
	    Qcm,Nil,Nil,Nil);
    Qsymbol_list = STATIC_SYMBOL("SYMBOL-LIST",AB_package);
    add_grammar_rules_for_list(6,Qsymbol_list,Qsymbol,Qcm,Nil,Nil,Nil);
    Qsymbol_list_with_and = STATIC_SYMBOL("SYMBOL-LIST-WITH-AND",AB_package);
    add_grammar_rules_for_list(6,Qsymbol_list_with_and,Qsymbol,Qcm,Qand,
	    Nil,Nil);
    Qlist_of_item_and_datum_constants_qm = 
	    STATIC_SYMBOL("LIST-OF-ITEM-AND-DATUM-CONSTANTS\?",AB_package);
    Qconstant_designation_quoted_symbol_list_and_datum = 
	    STATIC_SYMBOL("CONSTANT-DESIGNATION-QUOTED-SYMBOL-LIST-AND-DATUM",
	    AB_package);
    add_grammar_rules_for_list(6,Qlist_of_item_and_datum_constants_qm,
	    Qconstant_designation_quoted_symbol_list_and_datum,Qcm,Nil,
	    Qnone,Nil);
    Qlist_of_datum_constants = STATIC_SYMBOL("LIST-OF-DATUM-CONSTANTS",
	    AB_package);
    Qquoted_symbol_list_and_datum = 
	    STATIC_SYMBOL("QUOTED-SYMBOL-LIST-AND-DATUM",AB_package);
    add_grammar_rules_for_list(6,Qlist_of_datum_constants,
	    Qquoted_symbol_list_and_datum,Qcm,Nil,Nil,Nil);
    string_constant_32 = 
	    STATIC_STRING("1w1m83-ONy833ny1m83-ONy83-l6y1m83-l6y83-l5y1m83-l6y83-OPy1n83-l5y1n1m9k9l1m9k83-2y83-2y1m83vyn1m83-OPy83Sy1m83-OPy83=By1m83-OPy9");
    string_constant_33 = 
	    STATIC_STRING("m1m83-OPy834my1m83-OPy83-Uy1m83-OPy830Sy1m83-OPy8s");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_32,
	    string_constant_33)));
    Qnormalized = STATIC_SYMBOL("NORMALIZED",AB_package);
    Qcompile_constant_designation_list_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-CONSTANT-DESIGNATION-LIST\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_constant_designation_list_qm_for_slot,
	    STATIC_FUNCTION(compile_constant_designation_list_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qconstant_designation_list_qm,
	    SYMBOL_FUNCTION(Qcompile_constant_designation_list_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qconstant_designation_list_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qconstant_designation_list = STATIC_SYMBOL("CONSTANT-DESIGNATION-LIST",
	    AB_package);
    Qcompile_constant_designation_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-CONSTANT-DESIGNATION-LIST-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_constant_designation_list_for_slot,
	    STATIC_FUNCTION(compile_constant_designation_list_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qconstant_designation_list,
	    SYMBOL_FUNCTION(Qcompile_constant_designation_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qconstant_designation_list,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_quantity_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-QUANTITY-LIST-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_quantity_list_for_slot,
	    STATIC_FUNCTION(compile_quantity_list_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qquantity_list,
	    SYMBOL_FUNCTION(Qcompile_quantity_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qquantity_list,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_integer_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTEGER-LIST-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_integer_list_for_slot,
	    STATIC_FUNCTION(compile_integer_list_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qinteger_list,
	    SYMBOL_FUNCTION(Qcompile_integer_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinteger_list,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_float_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-FLOAT-LIST-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_float_list_for_slot,
	    STATIC_FUNCTION(compile_float_list_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qfloat_list,
	    SYMBOL_FUNCTION(Qcompile_float_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qfloat_list,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_whole_string_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-WHOLE-STRING-LIST-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_whole_string_list_for_slot,
	    STATIC_FUNCTION(compile_whole_string_list_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qwhole_string_list,
	    SYMBOL_FUNCTION(Qcompile_whole_string_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qwhole_string_list,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_truth_value_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-TRUTH-VALUE-LIST-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_truth_value_list_for_slot,
	    STATIC_FUNCTION(compile_truth_value_list_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qtruth_value_list,
	    SYMBOL_FUNCTION(Qcompile_truth_value_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtruth_value_list,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_symbol_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-SYMBOL-LIST-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_symbol_list_for_slot,
	    STATIC_FUNCTION(compile_symbol_list_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qsymbol_list,
	    SYMBOL_FUNCTION(Qcompile_symbol_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qsymbol_list,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qquoted_symbol_list = STATIC_SYMBOL("QUOTED-SYMBOL-LIST",AB_package);
    Qcompile_quoted_symbol_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-QUOTED-SYMBOL-LIST-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_quoted_symbol_list_for_slot,
	    STATIC_FUNCTION(compile_quoted_symbol_list_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qquoted_symbol_list,
	    SYMBOL_FUNCTION(Qcompile_quoted_symbol_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qquoted_symbol_list,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_list_of_item_and_datum_constants_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-LIST-OF-ITEM-AND-DATUM-CONSTANTS\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_list_of_item_and_datum_constants_qm_for_slot,
	    STATIC_FUNCTION(compile_list_of_item_and_datum_constants_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qlist_of_item_and_datum_constants_qm,
	    SYMBOL_FUNCTION(Qcompile_list_of_item_and_datum_constants_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlist_of_item_and_datum_constants_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_list_of_datum_constants_for_slot = 
	    STATIC_SYMBOL("COMPILE-LIST-OF-DATUM-CONSTANTS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_list_of_datum_constants_for_slot,
	    STATIC_FUNCTION(compile_list_of_datum_constants_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qlist_of_datum_constants,
	    SYMBOL_FUNCTION(Qcompile_list_of_datum_constants_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlist_of_datum_constants,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_constant_designation_list_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-CONSTANT-DESIGNATION-LIST\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_constant_designation_list_qm_from_slot,
	    STATIC_FUNCTION(write_constant_designation_list_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qconstant_designation_list_qm,
	    SYMBOL_FUNCTION(Qwrite_constant_designation_list_qm_from_slot),
	    Qslot_value_writer);
    Qwrite_constant_designation_list_from_slot = 
	    STATIC_SYMBOL("WRITE-CONSTANT-DESIGNATION-LIST-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_constant_designation_list_from_slot,
	    STATIC_FUNCTION(write_constant_designation_list_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qconstant_designation_list,
	    SYMBOL_FUNCTION(Qwrite_constant_designation_list_from_slot),
	    Qslot_value_writer);
    Qwrite_quantity_list_from_slot = 
	    STATIC_SYMBOL("WRITE-QUANTITY-LIST-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_quantity_list_from_slot,
	    STATIC_FUNCTION(write_quantity_list_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qquantity_list,
	    SYMBOL_FUNCTION(Qwrite_quantity_list_from_slot),
	    Qslot_value_writer);
    Qwrite_integer_list_from_slot = 
	    STATIC_SYMBOL("WRITE-INTEGER-LIST-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_integer_list_from_slot,
	    STATIC_FUNCTION(write_integer_list_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qinteger_list,
	    SYMBOL_FUNCTION(Qwrite_integer_list_from_slot),Qslot_value_writer);
    Qwrite_float_list_from_slot = 
	    STATIC_SYMBOL("WRITE-FLOAT-LIST-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_float_list_from_slot,
	    STATIC_FUNCTION(write_float_list_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qfloat_list,
	    SYMBOL_FUNCTION(Qwrite_float_list_from_slot),Qslot_value_writer);
    Qwrite_whole_string_list_from_slot = 
	    STATIC_SYMBOL("WRITE-WHOLE-STRING-LIST-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_whole_string_list_from_slot,
	    STATIC_FUNCTION(write_whole_string_list_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qwhole_string_list,
	    SYMBOL_FUNCTION(Qwrite_whole_string_list_from_slot),
	    Qslot_value_writer);
    Qwrite_truth_value_list_from_slot = 
	    STATIC_SYMBOL("WRITE-TRUTH-VALUE-LIST-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_truth_value_list_from_slot,
	    STATIC_FUNCTION(write_truth_value_list_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qtruth_value_list,
	    SYMBOL_FUNCTION(Qwrite_truth_value_list_from_slot),
	    Qslot_value_writer);
    Qwrite_symbol_list_from_slot = 
	    STATIC_SYMBOL("WRITE-SYMBOL-LIST-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_symbol_list_from_slot,
	    STATIC_FUNCTION(write_symbol_list_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qsymbol_list,
	    SYMBOL_FUNCTION(Qwrite_symbol_list_from_slot),Qslot_value_writer);
    Qwrite_quoted_symbol_list_from_slot = 
	    STATIC_SYMBOL("WRITE-QUOTED-SYMBOL-LIST-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_quoted_symbol_list_from_slot,
	    STATIC_FUNCTION(write_quoted_symbol_list_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qquoted_symbol_list,
	    SYMBOL_FUNCTION(Qwrite_quoted_symbol_list_from_slot),
	    Qslot_value_writer);
    array_constant_1 = STATIC_ARRAY(list_constant_76,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_76,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    string_constant = STATIC_STRING("and");
    array_constant_3 = STATIC_ARRAY(list_constant_76,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_list_of_item_and_datum_constants_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-LIST-OF-ITEM-AND-DATUM-CONSTANTS\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_list_of_item_and_datum_constants_qm_from_slot,
	    STATIC_FUNCTION(write_list_of_item_and_datum_constants_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qlist_of_item_and_datum_constants_qm,
	    SYMBOL_FUNCTION(Qwrite_list_of_item_and_datum_constants_qm_from_slot),
	    Qslot_value_writer);
    Qwrite_list_of_datum_constants_from_slot = 
	    STATIC_SYMBOL("WRITE-LIST-OF-DATUM-CONSTANTS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_list_of_datum_constants_from_slot,
	    STATIC_FUNCTION(write_list_of_datum_constants_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qlist_of_datum_constants,
	    SYMBOL_FUNCTION(Qwrite_list_of_datum_constants_from_slot),
	    Qslot_value_writer);
    Qvalue_array = STATIC_SYMBOL("VALUE-ARRAY",AB_package);
    string_constant_1 = STATIC_STRING("the symbol ~a");
    Qsymbol_array = STATIC_SYMBOL("SYMBOL-ARRAY",AB_package);
    Qtruth_value_array = STATIC_SYMBOL("TRUTH-VALUE-ARRAY",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    string_constant_2 = STATIC_STRING("~s");
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    string_constant_34 = STATIC_STRING("1l1m835Ey83*7y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_34));
    array_constant_4 = STATIC_ARRAY(list_constant_76,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)38L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)40L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)41L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)46L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)47L,(SI_Long)57344L);
    string_constant_3 = 
	    STATIC_STRING("This value is greater than the maximum g2-array length.");
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    Qcompile_g2_array_length_for_slot = 
	    STATIC_SYMBOL("COMPILE-G2-ARRAY-LENGTH-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_g2_array_length_for_slot,
	    STATIC_FUNCTION(compile_g2_array_length_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qg2_array_length,
	    SYMBOL_FUNCTION(Qcompile_g2_array_length_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qg2_array_length,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_g2_array_length_from_slot = 
	    STATIC_SYMBOL("WRITE-G2-ARRAY-LENGTH-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_g2_array_length_from_slot,
	    STATIC_FUNCTION(write_g2_array_length_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qg2_array_length,
	    SYMBOL_FUNCTION(Qwrite_g2_array_length_from_slot),
	    Qslot_value_writer);
    Qreparse_nth_element_designation = 
	    STATIC_SYMBOL("REPARSE-NTH-ELEMENT-DESIGNATION",AB_package);
    string_constant_35 = 
	    STATIC_STRING("1s1m833*y83-7ay1m830By83-7ay1m8330y83-7ay1o83-7ay1m83*Zy83-rPy1o9k1m83Way83=Kylm9l1o83-7ay1o1m9m83-9y830By1m9m83-Ay83-rPy1o9k1m8");
    string_constant_36 = 
	    STATIC_STRING("3Way83=Kymo9l1m83-rPy83r1y1m83-rPy1m83r1y83-rPy1n83r1y1n1m9m832sy83=xy1m9m832ty1mlm");
    clear_optimized_constants();
    push_optimized_constant(Qthe);
    push_optimized_constant(Qreparse_nth_element_designation);
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_35,
	    string_constant_36)));
    string_constant_37 = 
	    STATIC_STRING("1q1m83F2y83-ply1o83-ply1m83*Zy83-psy1o9k1m83Way83=Kylm9l1o83-ply1o1m9m83-9y83F2y1m9m83-Ay83-psy1o9k1m83Way83=Kymo9l1m83-psy83-pc");
    string_constant_38 = 
	    STATIC_STRING("y1m83-psy1m83r1y83-psy1n83-pcy1n1m9m832sy836Ey1m9m832ty1mlm");
    clear_optimized_constants();
    push_optimized_constant(Qthe);
    push_optimized_constant(Qreparse_nth_element_designation);
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_37,
	    string_constant_38)));
    SET_SYMBOL_FUNCTION(Qreparse_nth_element_designation,
	    STATIC_FUNCTION(reparse_nth_element_designation,NIL,FALSE,1,1));
    Qobt = STATIC_SYMBOL("[",AB_package);
    Qhas_a_name = STATIC_SYMBOL("HAS-A-NAME",AB_package);
    Qdesignation = STATIC_SYMBOL("DESIGNATION",AB_package);
    list_constant_77 = STATIC_LIST((SI_Long)2L,Qhas_a_name,Qdesignation);
    def_function_template(list_constant_77);
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    list_constant_78 = STATIC_LIST((SI_Long)3L,Qis,Qdesignation,Qexpression);
    def_function_template(list_constant_78);
    Qis_not = STATIC_SYMBOL("IS-NOT",AB_package);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qdesignation,Qexpression);
    list_constant_80 = STATIC_CONS(Qis_not,list_constant_79);
    def_function_template(list_constant_80);
    Qis_of_class = STATIC_SYMBOL("IS-OF-CLASS",AB_package);
    list_constant_81 = STATIC_CONS(Qis_of_class,list_constant_79);
    def_function_template(list_constant_81);
    Qsame_as = STATIC_SYMBOL("SAME-AS",AB_package);
    list_constant_82 = STATIC_CONS(Qdesignation,Qnil);
    list_constant_83 = STATIC_LIST_STAR((SI_Long)3L,Qsame_as,Qdesignation,
	    list_constant_82);
    def_function_template(list_constant_83);
    Qnot_same_as = STATIC_SYMBOL("NOT-SAME-AS",AB_package);
    list_constant_84 = STATIC_CONS(Qdesignation,list_constant_82);
    list_constant_85 = STATIC_CONS(Qnot_same_as,list_constant_84);
    def_function_template(list_constant_85);
    list_constant_86 = STATIC_CONS(Qexists,list_constant_82);
    def_function_template(list_constant_86);
    Qicon_color_of = STATIC_SYMBOL("ICON-COLOR-OF",AB_package);
    list_constant_87 = STATIC_CONS(Qicon_color_of,list_constant_82);
    def_function_template(list_constant_87);
    Qdistance_between = STATIC_SYMBOL("DISTANCE-BETWEEN",AB_package);
    list_constant_88 = STATIC_CONS(Qdistance_between,list_constant_84);
    def_function_template(list_constant_88);
    Qother = STATIC_SYMBOL("OTHER",AB_package);
    list_constant_89 = STATIC_LIST((SI_Long)2L,Qquote,Qother);
    def_function_template(list_constant_89);
    Qdistance_between_and_the_nearest = 
	    STATIC_SYMBOL("DISTANCE-BETWEEN-AND-THE-NEAREST",AB_package);
    list_constant_90 = STATIC_CONS(Qother,Qnil);
    list_constant_91 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdistance_between_and_the_nearest,Qdesignation,list_constant_90);
    def_function_template(list_constant_91);
    Qscope = STATIC_SYMBOL("SCOPE",AB_package);
    list_constant_92 = STATIC_CONS(Qexpression,Qnil);
    list_constant_93 = STATIC_LIST_STAR((SI_Long)3L,Qsum,Qscope,
	    list_constant_92);
    def_function_template(list_constant_93);
    list_constant_94 = STATIC_CONS(Qscope,list_constant_92);
    list_constant_95 = STATIC_CONS(Qproduct,list_constant_94);
    def_function_template(list_constant_95);
    list_constant_96 = STATIC_CONS(Qmaximum,list_constant_94);
    def_function_template(list_constant_96);
    list_constant_97 = STATIC_CONS(Qminimum,list_constant_94);
    def_function_template(list_constant_97);
    list_constant_98 = STATIC_CONS(Qcount,list_constant_94);
    def_function_template(list_constant_98);
    Qaggregated_average = STATIC_SYMBOL("AGGREGATED-AVERAGE",AB_package);
    list_constant_99 = STATIC_CONS(Qaggregated_average,list_constant_94);
    def_function_template(list_constant_99);
    Qthere_exists_literal = STATIC_SYMBOL("THERE-EXISTS-LITERAL",AB_package);
    list_constant_100 = STATIC_CONS(Qthere_exists_literal,list_constant_94);
    def_function_template(list_constant_100);
    Qfor_every_literal = STATIC_SYMBOL("FOR-EVERY-LITERAL",AB_package);
    list_constant_101 = STATIC_CONS(Qfor_every_literal,list_constant_94);
    def_function_template(list_constant_101);
    Qg2_list_or_sequence_length = 
	    STATIC_SYMBOL("G2-LIST-OR-SEQUENCE-LENGTH",AB_package);
    list_constant_102 = STATIC_CONS(Qg2_list_or_sequence_length,
	    list_constant_92);
    def_function_template(list_constant_102);
    Qg2_list_or_sequence_member_p = 
	    STATIC_SYMBOL("G2-LIST-OR-SEQUENCE-MEMBER-P",AB_package);
    list_constant_103 = STATIC_LIST_STAR((SI_Long)3L,
	    Qg2_list_or_sequence_member_p,Qexpression,list_constant_92);
    def_function_template(list_constant_103);
    list_constant_104 = STATIC_CONS(Qexpression,list_constant_92);
    list_constant_105 = STATIC_CONS(Qab_format,list_constant_104);
    def_function_template(list_constant_105);
    Qis_related = STATIC_SYMBOL("IS-RELATED",AB_package);
    list_constant_106 = STATIC_LIST_STAR((SI_Long)3L,Qis_related,
	    Qexpression,list_constant_84);
    def_function_template(list_constant_106);
    Qis_not_related = STATIC_SYMBOL("IS-NOT-RELATED",AB_package);
    list_constant_107 = STATIC_CONS(Qexpression,list_constant_84);
    list_constant_108 = STATIC_CONS(Qis_not_related,list_constant_107);
    def_function_template(list_constant_108);
    Qinterpolated_value = STATIC_SYMBOL("INTERPOLATED-VALUE",AB_package);
    list_constant_109 = STATIC_CONS(Qinterpolated_value,list_constant_79);
    def_function_template(list_constant_109);
    Qhistoric_value = STATIC_SYMBOL("HISTORIC-VALUE",AB_package);
    list_constant_110 = STATIC_CONS(Qhistoric_value,list_constant_79);
    def_function_template(list_constant_110);
    Qvalue_of_previous_datapoint = 
	    STATIC_SYMBOL("VALUE-OF-PREVIOUS-DATAPOINT",AB_package);
    list_constant_111 = STATIC_CONS(Qvalue_of_previous_datapoint,
	    list_constant_79);
    def_function_template(list_constant_111);
    Qcollection_time_of_previous_datapoint = 
	    STATIC_SYMBOL("COLLECTION-TIME-OF-PREVIOUS-DATAPOINT",AB_package);
    list_constant_112 = STATIC_CONS(Qcollection_time_of_previous_datapoint,
	    list_constant_79);
    def_function_template(list_constant_112);
    Qaverage_value = STATIC_SYMBOL("AVERAGE-VALUE",AB_package);
    list_constant_113 = STATIC_LIST_STAR((SI_Long)3L,Qaverage_value,
	    Qdesignation,list_constant_104);
    def_function_template(list_constant_113);
    Qsum_of_values = STATIC_SYMBOL("SUM-OF-VALUES",AB_package);
    list_constant_114 = STATIC_CONS(Qdesignation,list_constant_104);
    list_constant_115 = STATIC_CONS(Qsum_of_values,list_constant_114);
    def_function_template(list_constant_115);
    Qmaximum_value = STATIC_SYMBOL("MAXIMUM-VALUE",AB_package);
    list_constant_116 = STATIC_CONS(Qmaximum_value,list_constant_114);
    def_function_template(list_constant_116);
    Qminimum_value = STATIC_SYMBOL("MINIMUM-VALUE",AB_package);
    list_constant_117 = STATIC_CONS(Qminimum_value,list_constant_114);
    def_function_template(list_constant_117);
    Qstandard_deviation = STATIC_SYMBOL("STANDARD-DEVIATION",AB_package);
    list_constant_118 = STATIC_CONS(Qstandard_deviation,list_constant_114);
    def_function_template(list_constant_118);
    list_constant_119 = STATIC_LIST_STAR((SI_Long)4L,Qintegral,
	    Qdesignation,Qexpression,list_constant_104);
    def_function_template(list_constant_119);
    Qrate_of_change = STATIC_SYMBOL("RATE-OF-CHANGE",AB_package);
    list_constant_120 = STATIC_LIST_STAR((SI_Long)3L,Qdesignation,
	    Qexpression,list_constant_104);
    list_constant_121 = STATIC_CONS(Qrate_of_change,list_constant_120);
    def_function_template(list_constant_121);
    Qnumber_of_datapoints = STATIC_SYMBOL("NUMBER-OF-DATAPOINTS",AB_package);
    list_constant_122 = STATIC_CONS(Qnumber_of_datapoints,list_constant_114);
    def_function_template(list_constant_122);
    def_function_template(list_constant_81);
    def_function_template(list_constant_86);
    def_function_template(list_constant_83);
    def_function_template(list_constant_85);
    Qwhich_has_the_focal_object = 
	    STATIC_SYMBOL("WHICH-HAS-THE-FOCAL-OBJECT",AB_package);
    list_constant_123 = STATIC_CONS(Qdesignation,list_constant_90);
    list_constant_124 = STATIC_CONS(Qwhich_has_the_focal_object,
	    list_constant_123);
    def_function_template(list_constant_124);
    Qwhich_has_the_focal_class = STATIC_SYMBOL("WHICH-HAS-THE-FOCAL-CLASS",
	    AB_package);
    list_constant_125 = STATIC_CONS(Qwhich_has_the_focal_class,
	    list_constant_123);
    def_function_template(list_constant_125);
    Qin_the_category = STATIC_SYMBOL("IN-THE-CATEGORY",AB_package);
    list_constant_126 = STATIC_CONS(Qin_the_category,list_constant_123);
    def_function_template(list_constant_126);
    Qfound_on_the_workspace = STATIC_SYMBOL("FOUND-ON-THE-WORKSPACE",
	    AB_package);
    list_constant_127 = STATIC_CONS(Qfound_on_the_workspace,list_constant_123);
    def_function_template(list_constant_127);
    list_constant_128 = STATIC_CONS(Qname,list_constant_82);
    def_function_template(list_constant_128);
    Qwith_notes = STATIC_SYMBOL("WITH-NOTES",AB_package);
    list_constant_129 = STATIC_CONS(Qwith_notes,list_constant_82);
    def_function_template(list_constant_129);
    Qfails_to_receive_a_value = STATIC_SYMBOL("FAILS-TO-RECEIVE-A-VALUE",
	    AB_package);
    list_constant_130 = STATIC_CONS(Qfails_to_receive_a_value,
	    list_constant_82);
    def_function_template(list_constant_130);
    Qcontaining_symbol = STATIC_SYMBOL("CONTAINING-SYMBOL",AB_package);
    list_constant_131 = STATIC_CONS(Qcontaining_symbol,list_constant_123);
    def_function_template(list_constant_131);
    Qcontaining_string = STATIC_SYMBOL("CONTAINING-STRING",AB_package);
    list_constant_132 = STATIC_CONS(Qcontaining_string,list_constant_123);
    def_function_template(list_constant_132);
    Qbecomes_related = STATIC_SYMBOL("BECOMES-RELATED",AB_package);
    list_constant_133 = STATIC_CONS(Qbecomes_related,list_constant_107);
    def_function_template(list_constant_133);
    Qceases_to_be_related = STATIC_SYMBOL("CEASES-TO-BE-RELATED",AB_package);
    list_constant_134 = STATIC_CONS(Qceases_to_be_related,list_constant_107);
    def_function_template(list_constant_134);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    list_constant_135 = STATIC_CONS(Qattribute_name,list_constant_82);
    def_function_template(list_constant_135);
    Qin_the_tracked_item_set = STATIC_SYMBOL("IN-THE-TRACKED-ITEM-SET",
	    AB_package);
    list_constant_136 = STATIC_CONS(Qin_the_tracked_item_set,list_constant_82);
    def_function_template(list_constant_136);
    Qwith_unsaved_changes = STATIC_SYMBOL("WITH-UNSAVED-CHANGES",AB_package);
    list_constant_137 = STATIC_CONS(Qwith_unsaved_changes,list_constant_82);
    def_function_template(list_constant_137);
    list_constant_138 = STATIC_LIST_STAR((SI_Long)3L,Qinvoke,Qother,
	    list_constant_82);
    def_action_template(list_constant_138);
    Qhalt = STATIC_SYMBOL("HALT",AB_package);
    list_constant_139 = STATIC_CONS(Qhalt,list_constant_92);
    def_action_template(list_constant_139);
    Qinform = STATIC_SYMBOL("INFORM",AB_package);
    Qmessage_designation = STATIC_SYMBOL("MESSAGE-DESIGNATION",AB_package);
    Qmessage_text = STATIC_SYMBOL("MESSAGE-TEXT",AB_package);
    Qinform_option = STATIC_SYMBOL("INFORM-OPTION",AB_package);
    list_constant_140 = STATIC_LIST((SI_Long)6L,Qinform,
	    Qmessage_designation,Qmessage_text,Qinform_option,
	    Qinform_option,Qinform_option);
    def_action_template(list_constant_140);
    Qshow = STATIC_SYMBOL("SHOW",AB_package);
    Qshow_or_hide_argument_list = 
	    STATIC_SYMBOL("SHOW-OR-HIDE-ARGUMENT-LIST",AB_package);
    list_constant_141 = STATIC_LIST_STAR((SI_Long)3L,Qshow,Qdesignation,
	    Qshow_or_hide_argument_list);
    def_action_template(list_constant_141);
    Qhide = STATIC_SYMBOL("HIDE",AB_package);
    list_constant_142 = STATIC_CONS(Qdesignation,Qshow_or_hide_argument_list);
    list_constant_143 = STATIC_CONS(Qhide,list_constant_142);
    def_action_template(list_constant_143);
    Qchange_item_color = STATIC_SYMBOL("CHANGE-ITEM-COLOR",AB_package);
    list_constant_144 = STATIC_CONS(Qchange_item_color,list_constant_114);
    def_action_template(list_constant_144);
    Qchange_item_color_pattern = STATIC_SYMBOL("CHANGE-ITEM-COLOR-PATTERN",
	    AB_package);
    Qcolor_changes = STATIC_SYMBOL("COLOR-CHANGES",AB_package);
    list_constant_145 = STATIC_LIST_STAR((SI_Long)3L,
	    Qchange_item_color_pattern,Qdesignation,Qcolor_changes);
    def_action_template(list_constant_145);
    Qexpression_list = STATIC_SYMBOL("EXPRESSION-LIST",AB_package);
    list_constant_146 = STATIC_LIST_STAR((SI_Long)6L,Qstart,Qdesignation,
	    Qexpression_list,Qexpression,Qexpression,list_constant_82);
    def_action_template(list_constant_146);
    Qstart_thread = STATIC_SYMBOL("START-THREAD",AB_package);
    list_constant_147 = STATIC_LIST_STAR((SI_Long)5L,Qdesignation,
	    Qexpression_list,Qexpression,Qexpression,list_constant_82);
    list_constant_148 = STATIC_CONS(Qstart_thread,list_constant_147);
    def_action_template(list_constant_148);
    Qkb_change = STATIC_SYMBOL("KB-CHANGE",AB_package);
    list_constant_149 = STATIC_CONS(Qkb_change,list_constant_114);
    def_action_template(list_constant_149);
    Qadd_relation = STATIC_SYMBOL("ADD-RELATION",AB_package);
    list_constant_150 = STATIC_LIST_STAR((SI_Long)4L,Qadd_relation,Qother,
	    Qdesignation,list_constant_123);
    def_action_template(list_constant_150);
    Qremove_relation = STATIC_SYMBOL("REMOVE-RELATION",AB_package);
    list_constant_151 = STATIC_LIST_STAR((SI_Long)3L,Qremove_relation,
	    Qother,list_constant_84);
    def_action_template(list_constant_151);
    Qcreate = STATIC_SYMBOL("CREATE",AB_package);
    list_constant_152 = STATIC_CONS(Qexpression,list_constant_82);
    list_constant_153 = STATIC_CONS(Qcreate,list_constant_152);
    def_action_template(list_constant_153);
    list_constant_154 = STATIC_CONS(Qdelete,list_constant_123);
    def_action_template(list_constant_154);
    Qg2_list_insert = STATIC_SYMBOL("G2-LIST-INSERT",AB_package);
    list_constant_155 = STATIC_LIST_STAR((SI_Long)5L,Qg2_list_insert,
	    Qdesignation,Qexpression,Qexpression,list_constant_90);
    def_action_template(list_constant_155);
    Qg2_list_remove = STATIC_SYMBOL("G2-LIST-REMOVE",AB_package);
    list_constant_156 = STATIC_LIST_STAR((SI_Long)5L,Qg2_list_remove,
	    Qdesignation,Qexpression,Qother,list_constant_90);
    def_action_template(list_constant_156);
    Qtransfer = STATIC_SYMBOL("TRANSFER",AB_package);
    list_constant_157 = STATIC_LIST_STAR((SI_Long)3L,Qtransfer,
	    Qdesignation,list_constant_114);
    def_action_template(list_constant_157);
    Qupdate = STATIC_SYMBOL("UPDATE",AB_package);
    list_constant_158 = STATIC_CONS(Qupdate,list_constant_82);
    def_action_template(list_constant_158);
    Qnupec_synchronize = STATIC_SYMBOL("NUPEC-SYNCHRONIZE",AB_package);
    Qdesignation_list = STATIC_SYMBOL("DESIGNATION-LIST",AB_package);
    list_constant_159 = STATIC_LIST_STAR((SI_Long)4L,Qnupec_synchronize,
	    Qdesignation,Qdesignation_list,list_constant_90);
    def_action_template(list_constant_159);
    Qcreate_connection = STATIC_SYMBOL("CREATE-CONNECTION",AB_package);
    Qcreate_connection_spec = STATIC_SYMBOL("CREATE-CONNECTION-SPEC",
	    AB_package);
    list_constant_160 = STATIC_LIST_STAR((SI_Long)4L,Qcreate_connection,
	    Qother,Qcreate_connection_spec,list_constant_82);
    def_action_template(list_constant_160);
    Qcreate_explanation = STATIC_SYMBOL("CREATE-EXPLANATION",AB_package);
    list_constant_161 = STATIC_CONS(Qcreate_explanation,list_constant_84);
    def_action_template(list_constant_161);
    Qcreate_by_cloning = STATIC_SYMBOL("CREATE-BY-CLONING",AB_package);
    list_constant_162 = STATIC_CONS(Qcreate_by_cloning,list_constant_152);
    def_action_template(list_constant_162);
    Qmake_subworkspace = STATIC_SYMBOL("MAKE-SUBWORKSPACE",AB_package);
    list_constant_163 = STATIC_CONS(Qmake_subworkspace,list_constant_84);
    def_action_template(list_constant_163);
    Qmake_permanent = STATIC_SYMBOL("MAKE-PERMANENT",AB_package);
    list_constant_164 = STATIC_CONS(Qmake_permanent,list_constant_82);
    def_action_template(list_constant_164);
    Qmake_transient = STATIC_SYMBOL("MAKE-TRANSIENT",AB_package);
    list_constant_165 = STATIC_CONS(Qmake_transient,list_constant_82);
    def_action_template(list_constant_165);
    list_constant_166 = STATIC_CONS(Qprint,list_constant_82);
    def_action_template(list_constant_166);
    Qcall_action = STATIC_SYMBOL("CALL-ACTION",AB_package);
    list_constant_167 = STATIC_LIST_STAR((SI_Long)4L,Qcall_action,
	    Qdesignation,Qexpression_list,list_constant_82);
    def_action_template(list_constant_167);
    Qcall_assignment_action = STATIC_SYMBOL("CALL-ASSIGNMENT-ACTION",
	    AB_package);
    list_constant_168 = STATIC_LIST_STAR((SI_Long)3L,Qdesignation,
	    Qexpression_list,list_constant_82);
    list_constant_169 = STATIC_LIST_STAR((SI_Long)3L,
	    Qcall_assignment_action,Qdesignation_list,list_constant_168);
    def_action_template(list_constant_169);
    Qevaluation_attributes = STATIC_SYMBOL("EVALUATION-ATTRIBUTES",AB_package);
    temp = CONS(Qevaluation_attributes,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qevaluation_attributes,
	    Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    Qmay_run_while_inactive = STATIC_SYMBOL("MAY-RUN-WHILE-INACTIVE",
	    AB_package);
    Qmay_refer_to_inactive_items = 
	    STATIC_SYMBOL("MAY-REFER-TO-INACTIVE-ITEMS",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    list_constant_170 = STATIC_LIST((SI_Long)2L,Qab_class,Qprocedure);
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    list_constant_171 = STATIC_LIST((SI_Long)2L,Qab_class,Qrule);
    Qgeneric_action_button = STATIC_SYMBOL("GENERIC-ACTION-BUTTON",AB_package);
    list_constant_172 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qgeneric_action_button);
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    list_constant_173 = STATIC_LIST((SI_Long)2L,Qab_class,Quser_menu_choice);
    Qdial = STATIC_SYMBOL("DIAL",AB_package);
    list_constant_174 = STATIC_LIST((SI_Long)2L,Qab_class,Qdial);
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    list_constant_175 = STATIC_LIST((SI_Long)2L,Qab_class,Qmeter);
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    list_constant_176 = STATIC_LIST((SI_Long)2L,Qab_class,Qreadout_table);
    Qfreeform_table = STATIC_SYMBOL("FREEFORM-TABLE",AB_package);
    list_constant_177 = STATIC_LIST((SI_Long)2L,Qab_class,Qfreeform_table);
    Qsimulation_subtable = STATIC_SYMBOL("SIMULATION-SUBTABLE",AB_package);
    list_constant_178 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qsimulation_subtable);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    list_constant_179 = STATIC_LIST((SI_Long)2L,Qab_class,Qtrend_chart);
    Qchart = STATIC_SYMBOL("CHART",AB_package);
    list_constant_180 = STATIC_LIST((SI_Long)2L,Qab_class,Qchart);
    Qgeneric_formula = STATIC_SYMBOL("GENERIC-FORMULA",AB_package);
    list_constant_181 = STATIC_LIST((SI_Long)2L,Qab_class,Qgeneric_formula);
    Qnon_action_button = STATIC_SYMBOL("NON-ACTION-BUTTON",AB_package);
    list_constant_182 = STATIC_LIST((SI_Long)2L,Qab_class,Qnon_action_button);
    Qnetwork_interface = STATIC_SYMBOL("NETWORK-INTERFACE",AB_package);
    list_constant_183 = STATIC_LIST((SI_Long)2L,Qab_class,Qnetwork_interface);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    list_constant_184 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qvariable_or_parameter);
    list_constant_190 = STATIC_LIST((SI_Long)16L,Qab_or,list_constant_170,
	    list_constant_171,list_constant_172,list_constant_173,
	    list_constant_174,list_constant_175,list_constant_176,
	    list_constant_177,list_constant_178,list_constant_179,
	    list_constant_180,list_constant_181,list_constant_182,
	    list_constant_183,list_constant_184);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_1 = STATIC_CONS(Qno_item,Qnil);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_185 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_186 = STATIC_CONS(Qmay_refer_to_inactive_items,
	    list_constant_185);
    list_constant_187 = STATIC_CONS(Qmay_run_while_inactive,list_constant_185);
    list_constant_188 = STATIC_LIST((SI_Long)2L,list_constant_186,
	    list_constant_187);
    list_constant_189 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_188);
    list_constant_191 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_1,
	    list_constant_189);
    Qinitial_evaluation_attributes = 
	    STATIC_SYMBOL("INITIAL-EVALUATION-ATTRIBUTES",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_evaluation_attributes,
	    STATIC_FUNCTION(initial_evaluation_attributes,NIL,FALSE,1,1));
    Qget_evaluation_attributes = STATIC_SYMBOL("GET-EVALUATION-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_evaluation_attributes,
	    STATIC_FUNCTION(get_evaluation_attributes,NIL,FALSE,1,1));
    Qset_evaluation_attributes = STATIC_SYMBOL("SET-EVALUATION-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_evaluation_attributes,
	    STATIC_FUNCTION(set_evaluation_attributes,NIL,FALSE,2,2));
    add_virtual_attribute(Qevaluation_attributes,list_constant_190,
	    list_constant_191,Qnil,
	    SYMBOL_FUNCTION(Qinitial_evaluation_attributes),
	    SYMBOL_FUNCTION(Qget_evaluation_attributes),
	    SYMBOL_FUNCTION(Qset_evaluation_attributes));
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    Qbreak_message_level = STATIC_SYMBOL("BREAK-MESSAGE-LEVEL",AB_package);
    Qtracing_message_level = STATIC_SYMBOL("TRACING-MESSAGE-LEVEL",AB_package);
    Qwarning_message_level = STATIC_SYMBOL("WARNING-MESSAGE-LEVEL",AB_package);
    Qpart_feature = STATIC_SYMBOL("PART-FEATURE",AB_package);
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    Qscan_interval = STATIC_SYMBOL("SCAN-INTERVAL",AB_package);
    Qmay_request_event_updates = STATIC_SYMBOL("MAY-REQUEST-EVENT-UPDATES",
	    AB_package);
    Qmay_request_data_seeking = STATIC_SYMBOL("MAY-REQUEST-DATA-SEEKING",
	    AB_package);
    Qmay_provide_data_on_request = 
	    STATIC_SYMBOL("MAY-PROVIDE-DATA-ON-REQUEST",AB_package);
    Qmay_provide_event_updates = STATIC_SYMBOL("MAY-PROVIDE-EVENT-UPDATES",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Quser_menu_choice_priority = STATIC_SYMBOL("USER-MENU-CHOICE-PRIORITY",
	    AB_package);
    Qdisplay_update_priority = STATIC_SYMBOL("DISPLAY-UPDATE-PRIORITY",
	    AB_package);
    Qdisplay_update_interval = STATIC_SYMBOL("DISPLAY-UPDATE-INTERVAL",
	    AB_package);
    Qdisplay_wait_interval = STATIC_SYMBOL("DISPLAY-WAIT-INTERVAL",AB_package);
    Qinitial_scan_wait_interval = 
	    STATIC_SYMBOL("INITIAL-SCAN-WAIT-INTERVAL",AB_package);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qdata_point_value = STATIC_SYMBOL("DATA-POINT-VALUE",AB_package);
    Qdata_point_collection_time = 
	    STATIC_SYMBOL("DATA-POINT-COLLECTION-TIME",AB_package);
    Qdata_point_expiration_time = 
	    STATIC_SYMBOL("DATA-POINT-EXPIRATION-TIME",AB_package);
    Qsupplied = STATIC_SYMBOL("SUPPLIED",AB_package);
    string_constant_4 = 
	    STATIC_STRING("Trying to set the current value of ~NF to ~NV, which is not a ~NT");
    Qvalidity_interval = STATIC_SYMBOL("VALIDITY-INTERVAL",AB_package);
    Qindefinite = STATIC_SYMBOL("INDEFINITE",AB_package);
    Qvalue_structure = STATIC_SYMBOL("VALUE-STRUCTURE",AB_package);
    temp = CONS(Qvalue_structure,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qvariable_or_parameter),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qvalue_structure,temp_1);
    set_property_value_function(get_symbol_properties_function(Qvariable_or_parameter),
	    Qvirtual_attributes_local_to_class,temp);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    list_constant_194 = STATIC_LIST((SI_Long)2L,Qdata_point_value,Qdatum);
    list_constant_195 = STATIC_LIST((SI_Long)2L,
	    Qdata_point_collection_time,Qnumber);
    list_constant_192 = STATIC_LIST((SI_Long)2L,Qmember,Qnever);
    list_constant_193 = STATIC_LIST((SI_Long)3L,Qab_or,Qnumber,
	    list_constant_192);
    list_constant_196 = STATIC_LIST((SI_Long)2L,
	    Qdata_point_expiration_time,list_constant_193);
    list_constant_197 = STATIC_LIST((SI_Long)3L,list_constant_194,
	    list_constant_195,list_constant_196);
    list_constant_198 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_197);
    list_constant_199 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_1,
	    list_constant_198);
    Qinitial_value_structure = STATIC_SYMBOL("INITIAL-VALUE-STRUCTURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_value_structure,
	    STATIC_FUNCTION(initial_value_structure,NIL,FALSE,1,1));
    Qget_value_structure = STATIC_SYMBOL("GET-VALUE-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_value_structure,
	    STATIC_FUNCTION(get_value_structure,NIL,FALSE,1,1));
    Qset_value_structure = STATIC_SYMBOL("SET-VALUE-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_value_structure,
	    STATIC_FUNCTION(set_value_structure,NIL,FALSE,2,2));
    add_virtual_attribute(Qvalue_structure,list_constant_184,
	    list_constant_199,Qnil,
	    SYMBOL_FUNCTION(Qinitial_value_structure),
	    SYMBOL_FUNCTION(Qget_value_structure),
	    SYMBOL_FUNCTION(Qset_value_structure));
    Qvalue_structure_using_unix_time = 
	    STATIC_SYMBOL("VALUE-STRUCTURE-USING-UNIX-TIME",AB_package);
    temp = CONS(Qvalue_structure_using_unix_time,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qvariable_or_parameter),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qvalue_structure_using_unix_time,temp_1);
    set_property_value_function(get_symbol_properties_function(Qvariable_or_parameter),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_value_structure_using_unix_time = 
	    STATIC_SYMBOL("INITIAL-VALUE-STRUCTURE-USING-UNIX-TIME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_value_structure_using_unix_time,
	    STATIC_FUNCTION(initial_value_structure_using_unix_time,NIL,
	    FALSE,1,1));
    Qget_value_structure_using_unix_time = 
	    STATIC_SYMBOL("GET-VALUE-STRUCTURE-USING-UNIX-TIME",AB_package);
    SET_SYMBOL_FUNCTION(Qget_value_structure_using_unix_time,
	    STATIC_FUNCTION(get_value_structure_using_unix_time,NIL,FALSE,
	    1,1));
    Qset_value_structure_using_unix_time = 
	    STATIC_SYMBOL("SET-VALUE-STRUCTURE-USING-UNIX-TIME",AB_package);
    SET_SYMBOL_FUNCTION(Qset_value_structure_using_unix_time,
	    STATIC_FUNCTION(set_value_structure_using_unix_time,NIL,FALSE,
	    2,2));
    add_virtual_attribute(Qvalue_structure_using_unix_time,
	    list_constant_184,list_constant_199,Qnil,
	    SYMBOL_FUNCTION(Qinitial_value_structure_using_unix_time),
	    SYMBOL_FUNCTION(Qget_value_structure_using_unix_time),
	    SYMBOL_FUNCTION(Qset_value_structure_using_unix_time));
    Qproblem_putting_current_value_into_history_keeper = 
	    STATIC_SYMBOL("PROBLEM-PUTTING-CURRENT-VALUE-INTO-HISTORY-KEEPER",
	    AB_package);
    Qproblem_putting_current_value_into_variable_or_parameter = 
	    STATIC_SYMBOL("PROBLEM-PUTTING-CURRENT-VALUE-INTO-VARIABLE-OR-PARAMETER",
	    AB_package);
    string_constant_5 = 
	    STATIC_STRING("Can\'t assign No Value to parameter ~NF");
    Qlast_recorded_value_text = STATIC_SYMBOL("LAST-RECORDED-VALUE-TEXT",
	    AB_package);
    temp = CONS(Qlast_recorded_value_text,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qvariable_or_parameter),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qlast_recorded_value_text,temp_1);
    set_property_value_function(get_symbol_properties_function(Qvariable_or_parameter),
	    Qvirtual_attributes_local_to_class,temp);
    array_constant_5 = STATIC_ARRAY(list_constant_76,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_76,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_200 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_1,Qtext);
    Qinitial_last_recorded_value_text = 
	    STATIC_SYMBOL("INITIAL-LAST-RECORDED-VALUE-TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_last_recorded_value_text,
	    STATIC_FUNCTION(initial_last_recorded_value_text,NIL,FALSE,1,1));
    Qget_last_recorded_value_text = 
	    STATIC_SYMBOL("GET-LAST-RECORDED-VALUE-TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_last_recorded_value_text,
	    STATIC_FUNCTION(get_last_recorded_value_text,NIL,FALSE,1,1));
    add_virtual_attribute(Qlast_recorded_value_text,list_constant_184,
	    list_constant_200,Qnil,
	    SYMBOL_FUNCTION(Qinitial_last_recorded_value_text),
	    SYMBOL_FUNCTION(Qget_last_recorded_value_text),Nil);
    Qeffective_data_type = STATIC_SYMBOL("EFFECTIVE-DATA-TYPE",AB_package);
    temp = CONS(Qeffective_data_type,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qeffective_data_type,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    list_constant_201 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_184,
	    list_constant_178);
    Qinitial_effective_data_type = 
	    STATIC_SYMBOL("INITIAL-EFFECTIVE-DATA-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_effective_data_type,
	    STATIC_FUNCTION(initial_effective_data_type,NIL,FALSE,1,1));
    Qget_effective_data_type = STATIC_SYMBOL("GET-EFFECTIVE-DATA-TYPE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_effective_data_type,
	    STATIC_FUNCTION(get_effective_data_type,NIL,FALSE,1,1));
    add_virtual_attribute(Qeffective_data_type,list_constant_201,Qsymbol,
	    Qnil,SYMBOL_FUNCTION(Qinitial_effective_data_type),
	    SYMBOL_FUNCTION(Qget_effective_data_type),Nil);
    Qhistory_value = STATIC_SYMBOL("HISTORY-VALUE",AB_package);
    Qhistory_collection_time = STATIC_SYMBOL("HISTORY-COLLECTION-TIME",
	    AB_package);
    string_constant_6 = 
	    STATIC_STRING("Trying to set a history value of ~NF to ~NV, which is not a ~NT");
    Qhistory = STATIC_SYMBOL("HISTORY",AB_package);
    temp = CONS(Qhistory,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qhistory,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    list_constant_202 = STATIC_CONS(Qdatum,Qnil);
    list_constant_203 = STATIC_CONS(Qhistory_value,list_constant_202);
    list_constant_204 = STATIC_LIST((SI_Long)2L,Qhistory_collection_time,
	    Qfloat);
    list_constant_205 = STATIC_LIST((SI_Long)2L,list_constant_203,
	    list_constant_204);
    list_constant_206 = STATIC_LIST((SI_Long)3L,Qand,Qhistory_value,
	    Qhistory_collection_time);
    list_constant_207 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_205,list_constant_206);
    list_constant_208 = STATIC_LIST((SI_Long)3L,Qsequence,
	    list_constant_207,FIX((SI_Long)1L));
    list_constant_209 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_1,
	    list_constant_208);
    Qexclude_from_wildcard_denotation = 
	    STATIC_SYMBOL("EXCLUDE-FROM-WILDCARD-DENOTATION",AB_package);
    list_constant_210 = STATIC_LIST((SI_Long)2L,
	    Qexclude_from_wildcard_denotation,Qt);
    Qinitial_history = STATIC_SYMBOL("INITIAL-HISTORY",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_history,STATIC_FUNCTION(initial_history,
	    NIL,FALSE,1,1));
    Qget_history = STATIC_SYMBOL("GET-HISTORY",AB_package);
    SET_SYMBOL_FUNCTION(Qget_history,STATIC_FUNCTION(get_history,NIL,FALSE,
	    1,1));
    Qset_history = STATIC_SYMBOL("SET-HISTORY",AB_package);
    SET_SYMBOL_FUNCTION(Qset_history,STATIC_FUNCTION(set_history,NIL,FALSE,
	    2,2));
    add_virtual_attribute(Qhistory,list_constant_201,list_constant_209,
	    list_constant_210,SYMBOL_FUNCTION(Qinitial_history),
	    SYMBOL_FUNCTION(Qget_history),SYMBOL_FUNCTION(Qset_history));
    Qhistory_using_unix_time = STATIC_SYMBOL("HISTORY-USING-UNIX-TIME",
	    AB_package);
    temp = CONS(Qhistory_using_unix_time,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qhistory_using_unix_time,
	    Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    Qinitial_history_using_unix_time = 
	    STATIC_SYMBOL("INITIAL-HISTORY-USING-UNIX-TIME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_history_using_unix_time,
	    STATIC_FUNCTION(initial_history_using_unix_time,NIL,FALSE,1,1));
    Qget_history_using_unix_time = 
	    STATIC_SYMBOL("GET-HISTORY-USING-UNIX-TIME",AB_package);
    SET_SYMBOL_FUNCTION(Qget_history_using_unix_time,
	    STATIC_FUNCTION(get_history_using_unix_time,NIL,FALSE,1,1));
    Qset_history_using_unix_time = 
	    STATIC_SYMBOL("SET-HISTORY-USING-UNIX-TIME",AB_package);
    SET_SYMBOL_FUNCTION(Qset_history_using_unix_time,
	    STATIC_FUNCTION(set_history_using_unix_time,NIL,FALSE,2,2));
    add_virtual_attribute(Qhistory_using_unix_time,list_constant_201,
	    list_constant_209,list_constant_210,
	    SYMBOL_FUNCTION(Qinitial_history_using_unix_time),
	    SYMBOL_FUNCTION(Qget_history_using_unix_time),
	    SYMBOL_FUNCTION(Qset_history_using_unix_time));
    Qg2_array_sequence = STATIC_SYMBOL("G2-ARRAY-SEQUENCE",AB_package);
    temp = CONS(Qg2_array_sequence,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qg2_array),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qg2_array_sequence,temp_1);
    set_property_value_function(get_symbol_properties_function(Qg2_array),
	    Qvirtual_attributes_local_to_class,temp);
    string_constant_7 = 
	    STATIC_STRING("cannot reset/disable array ~NF by concluding no-value in g2-array-sequence");
    string_constant_8 = 
	    STATIC_STRING("Cannot set the g2-array-sequence of ~NF because it is neither a permanent array nor active");
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    string_constant_9 = STATIC_STRING("element ~D, ~NA, is not of type ~S");
    list_constant_211 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_array);
    list_constant_2 = STATIC_CONS(Qsequence,Qnil);
    list_constant_212 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_1,
	    list_constant_2);
    Qinitial_g2_array_sequence = STATIC_SYMBOL("INITIAL-G2-ARRAY-SEQUENCE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_g2_array_sequence,
	    STATIC_FUNCTION(initial_g2_array_sequence,NIL,FALSE,1,1));
    Qget_g2_array_sequence = STATIC_SYMBOL("GET-G2-ARRAY-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_g2_array_sequence,
	    STATIC_FUNCTION(get_g2_array_sequence,NIL,FALSE,1,1));
    Qset_g2_array_sequence = STATIC_SYMBOL("SET-G2-ARRAY-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_g2_array_sequence,
	    STATIC_FUNCTION(set_g2_array_sequence,NIL,FALSE,2,2));
    add_virtual_attribute(Qg2_array_sequence,list_constant_211,
	    list_constant_212,list_constant_210,
	    SYMBOL_FUNCTION(Qinitial_g2_array_sequence),
	    SYMBOL_FUNCTION(Qget_g2_array_sequence),
	    SYMBOL_FUNCTION(Qset_g2_array_sequence));
    Qg2_list_sequence = STATIC_SYMBOL("G2-LIST-SEQUENCE",AB_package);
    temp = CONS(Qg2_list_sequence,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qg2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qg2_list),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qg2_list_sequence,temp_1);
    set_property_value_function(get_symbol_properties_function(Qg2_list),
	    Qvirtual_attributes_local_to_class,temp);
    list_constant_213 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_list);
    Qinitial_g2_list_sequence = STATIC_SYMBOL("INITIAL-G2-LIST-SEQUENCE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_g2_list_sequence,
	    STATIC_FUNCTION(initial_g2_list_sequence,NIL,FALSE,1,1));
    Qget_g2_list_sequence = STATIC_SYMBOL("GET-G2-LIST-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_g2_list_sequence,
	    STATIC_FUNCTION(get_g2_list_sequence,NIL,FALSE,1,1));
    Qset_g2_list_sequence = STATIC_SYMBOL("SET-G2-LIST-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_g2_list_sequence,
	    STATIC_FUNCTION(set_g2_list_sequence,NIL,FALSE,2,2));
    add_virtual_attribute(Qg2_list_sequence,list_constant_213,
	    list_constant_2,list_constant_210,
	    SYMBOL_FUNCTION(Qinitial_g2_list_sequence),
	    SYMBOL_FUNCTION(Qget_g2_list_sequence),
	    SYMBOL_FUNCTION(Qset_g2_list_sequence));
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qg2_array_length),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qg2_array_length,Qinteger);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qg2_array_length);
    g2_array_length_evaluation_setter_1 = 
	    STATIC_FUNCTION(g2_array_length_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qg2_array_length,
	    g2_array_length_evaluation_setter_1);
    g2_array_length_evaluation_getter_1 = 
	    STATIC_FUNCTION(g2_array_length_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qg2_array_length,
	    g2_array_length_evaluation_getter_1);
    Qelement_type = STATIC_SYMBOL("ELEMENT-TYPE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qelement_type),
	    Qtype_specification_simple_expansion,Qnil);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_214 = STATIC_LIST((SI_Long)10L,Qmember,Qvalue,
	    Qitem_or_value,Qquantity,Qtext,Qtruth_value,Qitem,Qinteger,
	    Qfloat,Qsymbol);
    define_type_specification_explicit_complex_type(Qelement_type,
	    list_constant_214);
    element_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(element_type_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qelement_type,
	    element_type_evaluation_getter_1);
    string_constant_10 = 
	    STATIC_STRING("There is no g2 expression that names ~NF");
    if (Array_initialization_evaluation_values_use_designations_p == UNBOUND)
	Array_initialization_evaluation_values_use_designations_p = T;
    Qdesignation_marker = STATIC_SYMBOL("DESIGNATION-MARKER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdesignation_marker,Designation_marker);
    if (Designation_marker == UNBOUND)
	Designation_marker = LIST_1(Qdesignation_marker);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_76,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)57344L);
    string_constant_11 = STATIC_STRING("Could not find item for ~ND");
    Qitems = STATIC_SYMBOL("ITEMS",AB_package);
    list_constant_3 = STATIC_CONS(Qab_structure,Qnil);
    string_constant_12 = STATIC_STRING("~NT ");
    string_constant_13 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    list_constant_215 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_1,
	    list_constant_2,list_constant_3);
    set_property_value_function(get_symbol_properties_function(Qlist_of_item_and_datum_constants_qm),
	    Qtype_specification_simple_expansion,list_constant_215);
    list_constant_216 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_226 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    Qitem_or_datum,list_constant_216);
    list_constant_217 = STATIC_CONS(list_constant_1,Qnil);
    list_constant_218 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_217);
    list_constant_219 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_218,list_constant_216);
    list_constant_222 = STATIC_LIST((SI_Long)2L,Qvalues,list_constant_219);
    list_constant_220 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qdatum,
	    list_constant_217);
    list_constant_221 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_220,list_constant_216);
    list_constant_223 = STATIC_LIST((SI_Long)2L,Qitems,list_constant_221);
    list_constant_224 = STATIC_LIST((SI_Long)2L,list_constant_222,
	    list_constant_223);
    list_constant_225 = STATIC_LIST((SI_Long)2L,Qand,Qitems);
    list_constant_227 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_224,list_constant_225);
    list_constant_5 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_1,
	    list_constant_226,list_constant_227);
    define_type_specification_explicit_complex_type(Qlist_of_item_and_datum_constants_qm,
	    list_constant_5);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qlist_of_item_and_datum_constants_qm);
    list_of_item_and_datum_constants_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(list_of_item_and_datum_constants_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlist_of_item_and_datum_constants_qm,
	    list_of_item_and_datum_constants_qm_evaluation_setter_1);
    list_of_item_and_datum_constants_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(list_of_item_and_datum_constants_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlist_of_item_and_datum_constants_qm,
	    list_of_item_and_datum_constants_qm_evaluation_getter_1);
    list_constant_228 = STATIC_CONS(list_constant_2,Qnil);
    list_constant_229 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_1,list_constant_2,list_constant_228);
    set_property_value_function(get_symbol_properties_function(Qconstant_designation_list_qm),
	    Qtype_specification_simple_expansion,list_constant_229);
    list_constant_230 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_231 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_230,list_constant_216);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qdatum,
	    list_constant_216);
    list_constant_7 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_1,
	    list_constant_231,list_constant_9);
    define_type_specification_explicit_complex_type(Qconstant_designation_list_qm,
	    list_constant_7);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qconstant_designation_list_qm);
    constant_designation_list_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(constant_designation_list_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qconstant_designation_list_qm,
	    constant_designation_list_qm_evaluation_setter_1);
    constant_designation_list_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(constant_designation_list_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconstant_designation_list_qm,
	    constant_designation_list_qm_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qlist_of_datum_constants),
	    Qtype_specification_simple_expansion,list_constant_2);
    define_type_specification_explicit_complex_type(Qlist_of_datum_constants,
	    list_constant_9);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qnamed,Qlist_of_datum_constants);
    list_of_datum_constants_evaluation_setter_1 = 
	    STATIC_FUNCTION(list_of_datum_constants_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qlist_of_datum_constants,
	    list_of_datum_constants_evaluation_setter_1);
    list_of_datum_constants_evaluation_getter_1 = 
	    STATIC_FUNCTION(list_of_datum_constants_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlist_of_datum_constants,
	    list_of_datum_constants_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qsymbol_list),
	    Qtype_specification_simple_expansion,list_constant_2);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qsymbol,
	    list_constant_216);
    define_type_specification_explicit_complex_type(Qsymbol_list,
	    list_constant_11);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qnamed,Qsymbol_list);
    symbol_list_evaluation_setter_1 = 
	    STATIC_FUNCTION(symbol_list_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qsymbol_list,
	    symbol_list_evaluation_setter_1);
    symbol_list_evaluation_getter_1 = 
	    STATIC_FUNCTION(symbol_list_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsymbol_list,
	    symbol_list_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qwhole_string_list),
	    Qtype_specification_simple_expansion,list_constant_2);
    list_constant_13 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qtext,
	    list_constant_216);
    define_type_specification_explicit_complex_type(Qwhole_string_list,
	    list_constant_13);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qnamed,Qwhole_string_list);
    whole_string_list_evaluation_setter_1 = 
	    STATIC_FUNCTION(whole_string_list_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qwhole_string_list,
	    whole_string_list_evaluation_setter_1);
    whole_string_list_evaluation_getter_1 = 
	    STATIC_FUNCTION(whole_string_list_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qwhole_string_list,
	    whole_string_list_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qtruth_value_list),
	    Qtype_specification_simple_expansion,list_constant_2);
    list_constant_15 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qtruth_value,
	    list_constant_216);
    define_type_specification_explicit_complex_type(Qtruth_value_list,
	    list_constant_15);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qnamed,Qtruth_value_list);
    string_constant_14 = 
	    STATIC_STRING("Illegal value, ~NV; it should be of type truth-value");
    truth_value_list_evaluation_setter_1 = 
	    STATIC_FUNCTION(truth_value_list_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtruth_value_list,
	    truth_value_list_evaluation_setter_1);
    truth_value_list_evaluation_getter_1 = 
	    STATIC_FUNCTION(truth_value_list_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtruth_value_list,
	    truth_value_list_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qquantity_list),
	    Qtype_specification_simple_expansion,list_constant_2);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qnumber,
	    list_constant_216);
    define_type_specification_explicit_complex_type(Qquantity_list,
	    list_constant_17);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qnamed,Qquantity_list);
    quantity_list_evaluation_setter_1 = 
	    STATIC_FUNCTION(quantity_list_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qquantity_list,
	    quantity_list_evaluation_setter_1);
    quantity_list_evaluation_getter_1 = 
	    STATIC_FUNCTION(quantity_list_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qquantity_list,
	    quantity_list_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qfloat_list),
	    Qtype_specification_simple_expansion,list_constant_2);
    list_constant_19 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qfloat,
	    list_constant_216);
    define_type_specification_explicit_complex_type(Qfloat_list,
	    list_constant_19);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qnamed,Qfloat_list);
    float_list_evaluation_setter_1 = 
	    STATIC_FUNCTION(float_list_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfloat_list,
	    float_list_evaluation_setter_1);
    float_list_evaluation_getter_1 = 
	    STATIC_FUNCTION(float_list_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfloat_list,
	    float_list_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qinteger_list),
	    Qtype_specification_simple_expansion,list_constant_2);
    list_constant_21 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qinteger,
	    list_constant_216);
    define_type_specification_explicit_complex_type(Qinteger_list,
	    list_constant_21);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qnamed,Qinteger_list);
    integer_list_evaluation_setter_1 = 
	    STATIC_FUNCTION(integer_list_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qinteger_list,
	    integer_list_evaluation_setter_1);
    integer_list_evaluation_getter_1 = 
	    STATIC_FUNCTION(integer_list_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinteger_list,
	    integer_list_evaluation_getter_1);
    Qalignment = STATIC_SYMBOL("ALIGNMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qalignment),
	    Qtype_specification_simple_expansion,Qnil);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)4L,Qmember,Qleft,Qcenter,Qright);
    define_type_specification_explicit_complex_type(Qalignment,
	    list_constant_23);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qnamed,Qalignment);
    alignment_evaluation_setter_1 = 
	    STATIC_FUNCTION(alignment_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qalignment,
	    alignment_evaluation_setter_1);
    alignment_evaluation_getter_1 = 
	    STATIC_FUNCTION(alignment_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qalignment,
	    alignment_evaluation_getter_1);
    Qwhen_to_allow_multiple_menus = 
	    STATIC_SYMBOL("WHEN-TO-ALLOW-MULTIPLE-MENUS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qwhen_to_allow_multiple_menus),
	    Qtype_specification_simple_expansion,Qnil);
    Qalways = STATIC_SYMBOL("ALWAYS",AB_package);
    Qfor_different_selections = STATIC_SYMBOL("FOR-DIFFERENT-SELECTIONS",
	    AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)4L,Qmember,Qnever,Qalways,
	    Qfor_different_selections);
    define_type_specification_explicit_complex_type(Qwhen_to_allow_multiple_menus,
	    list_constant_25);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qwhen_to_allow_multiple_menus);
    Qif_different = STATIC_SYMBOL("IF-DIFFERENT",AB_package);
    when_to_allow_multiple_menus_evaluation_setter_1 = 
	    STATIC_FUNCTION(when_to_allow_multiple_menus_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qwhen_to_allow_multiple_menus,
	    when_to_allow_multiple_menus_evaluation_setter_1);
    when_to_allow_multiple_menus_evaluation_getter_1 = 
	    STATIC_FUNCTION(when_to_allow_multiple_menus_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qwhen_to_allow_multiple_menus,
	    when_to_allow_multiple_menus_evaluation_getter_1);
    Qcurrent_language = STATIC_SYMBOL("CURRENT-LANGUAGE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qcurrent_language),
	    Qtype_specification_simple_expansion,Qsymbol);
    define_type_specification_explicit_complex_type(Qcurrent_language,Qsymbol);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qnamed,Qcurrent_language);
    current_language_evaluation_setter_1 = 
	    STATIC_FUNCTION(current_language_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qcurrent_language,
	    current_language_evaluation_setter_1);
    current_language_evaluation_getter_1 = 
	    STATIC_FUNCTION(current_language_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qcurrent_language,
	    current_language_evaluation_getter_1);
    Qcolor_menu_ordering = STATIC_SYMBOL("COLOR-MENU-ORDERING",AB_package);
    set_property_value_function(get_symbol_properties_function(Qcolor_menu_ordering),
	    Qtype_specification_simple_expansion,Qnil);
    Qintensity = STATIC_SYMBOL("INTENSITY",AB_package);
    Qalphabetic = STATIC_SYMBOL("ALPHABETIC",AB_package);
    Qhue = STATIC_SYMBOL("HUE",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)4L,Qmember,Qintensity,
	    Qalphabetic,Qhue);
    define_type_specification_explicit_complex_type(Qcolor_menu_ordering,
	    list_constant_28);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qnamed,Qcolor_menu_ordering);
    color_menu_ordering_evaluation_setter_1 = 
	    STATIC_FUNCTION(color_menu_ordering_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qcolor_menu_ordering,
	    color_menu_ordering_evaluation_setter_1);
    color_menu_ordering_evaluation_getter_1 = 
	    STATIC_FUNCTION(color_menu_ordering_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qcolor_menu_ordering,
	    color_menu_ordering_evaluation_getter_1);
    Qcolor_set_spec = STATIC_SYMBOL("COLOR-SET-SPEC",AB_package);
    list_constant_232 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnil,
	    list_constant_228);
    set_property_value_function(get_symbol_properties_function(Qcolor_set_spec),
	    Qtype_specification_simple_expansion,list_constant_232);
    Qstandard_set = STATIC_SYMBOL("STANDARD-SET",AB_package);
    list_constant_234 = STATIC_LIST((SI_Long)4L,Qmember,Qall,Qnone,
	    Qstandard_set);
    Qcolor_or_metacolor = STATIC_SYMBOL("COLOR-OR-METACOLOR",AB_package);
    list_constant_233 = STATIC_LIST((SI_Long)2L,Qnamed,Qcolor_or_metacolor);
    list_constant_235 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_233,list_constant_216);
    list_constant_30 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_234,
	    list_constant_235);
    define_type_specification_explicit_complex_type(Qcolor_set_spec,
	    list_constant_30);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qnamed,Qcolor_set_spec);
    color_set_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(color_set_spec_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qcolor_set_spec,
	    color_set_spec_evaluation_setter_1);
    color_set_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(color_set_spec_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qcolor_set_spec,
	    color_set_spec_evaluation_getter_1);
    Qnumber_of_menu_columns_spec = 
	    STATIC_SYMBOL("NUMBER-OF-MENU-COLUMNS-SPEC",AB_package);
    set_property_value_function(get_symbol_properties_function(Qnumber_of_menu_columns_spec),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_32 = STATIC_LIST((SI_Long)8L,Qmember,FIX((SI_Long)1L),
	    FIX((SI_Long)2L),FIX((SI_Long)3L),FIX((SI_Long)4L),
	    FIX((SI_Long)5L),FIX((SI_Long)6L),FIX((SI_Long)7L));
    define_type_specification_explicit_complex_type(Qnumber_of_menu_columns_spec,
	    list_constant_32);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qnumber_of_menu_columns_spec);
    number_of_menu_columns_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(number_of_menu_columns_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qnumber_of_menu_columns_spec,
	    number_of_menu_columns_spec_evaluation_setter_1);
    number_of_menu_columns_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(number_of_menu_columns_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qnumber_of_menu_columns_spec,
	    number_of_menu_columns_spec_evaluation_getter_1);
    Qimage_palette = STATIC_SYMBOL("IMAGE-PALETTE",AB_package);
    list_constant_236 = STATIC_CONS(list_constant_3,Qnil);
    list_constant_237 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnil,
	    list_constant_236);
    set_property_value_function(get_symbol_properties_function(Qimage_palette),
	    Qtype_specification_simple_expansion,list_constant_237);
    Qblack_and_white = STATIC_SYMBOL("BLACK-AND-WHITE",AB_package);
    Qstandard_grays = STATIC_SYMBOL("STANDARD-GRAYS",AB_package);
    Qstandard_colors = STATIC_SYMBOL("STANDARD-COLORS",AB_package);
    Qextended_grays = STATIC_SYMBOL("EXTENDED-GRAYS",AB_package);
    Qextended_colors = STATIC_SYMBOL("EXTENDED-COLORS",AB_package);
    list_constant_244 = STATIC_LIST((SI_Long)6L,Qmember,Qblack_and_white,
	    Qstandard_grays,Qstandard_colors,Qextended_grays,Qextended_colors);
    Qpalette_name = STATIC_SYMBOL("PALETTE-NAME",AB_package);
    Qcustom_grays = STATIC_SYMBOL("CUSTOM-GRAYS",AB_package);
    Qcustom_colors = STATIC_SYMBOL("CUSTOM-COLORS",AB_package);
    list_constant_238 = STATIC_LIST((SI_Long)3L,Qmember,Qcustom_grays,
	    Qcustom_colors);
    list_constant_240 = STATIC_LIST((SI_Long)2L,Qpalette_name,
	    list_constant_238);
    Qimage_name = STATIC_SYMBOL("IMAGE-NAME",AB_package);
    list_constant_239 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_241 = STATIC_CONS(Qimage_name,list_constant_239);
    list_constant_242 = STATIC_LIST((SI_Long)2L,list_constant_240,
	    list_constant_241);
    list_constant_243 = STATIC_LIST((SI_Long)3L,Qand,Qpalette_name,
	    Qimage_name);
    list_constant_245 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_242,list_constant_243);
    list_constant_34 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_244,
	    list_constant_245);
    define_type_specification_explicit_complex_type(Qimage_palette,
	    list_constant_34);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qnamed,Qimage_palette);
    image_palette_evaluation_setter_1 = 
	    STATIC_FUNCTION(image_palette_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qimage_palette,
	    image_palette_evaluation_setter_1);
    image_palette_evaluation_getter_1 = 
	    STATIC_FUNCTION(image_palette_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qimage_palette,
	    image_palette_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qwarning_message_level),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_36 = STATIC_LIST((SI_Long)5L,Qmember,FIX((SI_Long)0L),
	    FIX((SI_Long)1L),FIX((SI_Long)2L),FIX((SI_Long)3L));
    define_type_specification_explicit_complex_type(Qwarning_message_level,
	    list_constant_36);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qnamed,Qwarning_message_level);
    warning_message_level_evaluation_setter_1 = 
	    STATIC_FUNCTION(warning_message_level_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qwarning_message_level,
	    warning_message_level_evaluation_setter_1);
    warning_message_level_evaluation_getter_1 = 
	    STATIC_FUNCTION(warning_message_level_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qwarning_message_level,
	    warning_message_level_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qtracing_message_level),
	    Qtype_specification_simple_expansion,Qnil);
    define_type_specification_explicit_complex_type(Qtracing_message_level,
	    list_constant_36);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qnamed,Qtracing_message_level);
    tracing_message_level_evaluation_setter_1 = 
	    STATIC_FUNCTION(tracing_message_level_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qtracing_message_level,
	    tracing_message_level_evaluation_setter_1);
    tracing_message_level_evaluation_getter_1 = 
	    STATIC_FUNCTION(tracing_message_level_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtracing_message_level,
	    tracing_message_level_evaluation_getter_1);
    Qbreakpoint_level = STATIC_SYMBOL("BREAKPOINT-LEVEL",AB_package);
    set_property_value_function(get_symbol_properties_function(Qbreakpoint_level),
	    Qtype_specification_simple_expansion,Qnil);
    define_type_specification_explicit_complex_type(Qbreakpoint_level,
	    list_constant_36);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qnamed,Qbreakpoint_level);
    breakpoint_level_evaluation_setter_1 = 
	    STATIC_FUNCTION(breakpoint_level_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qbreakpoint_level,
	    breakpoint_level_evaluation_setter_1);
    breakpoint_level_evaluation_getter_1 = 
	    STATIC_FUNCTION(breakpoint_level_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qbreakpoint_level,
	    breakpoint_level_evaluation_getter_1);
    Qsource_stepping_level = STATIC_SYMBOL("SOURCE-STEPPING-LEVEL",AB_package);
    set_property_value_function(get_symbol_properties_function(Qsource_stepping_level),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_40 = STATIC_LIST_STAR((SI_Long)3L,Qmember,
	    FIX((SI_Long)0L),list_constant_216);
    define_type_specification_explicit_complex_type(Qsource_stepping_level,
	    list_constant_40);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qnamed,Qsource_stepping_level);
    source_stepping_level_evaluation_setter_1 = 
	    STATIC_FUNCTION(source_stepping_level_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qsource_stepping_level,
	    source_stepping_level_evaluation_setter_1);
    source_stepping_level_evaluation_getter_1 = 
	    STATIC_FUNCTION(source_stepping_level_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsource_stepping_level,
	    source_stepping_level_evaluation_getter_1);
    Qinterface_warning_message_level = 
	    STATIC_SYMBOL("INTERFACE-WARNING-MESSAGE-LEVEL",AB_package);
    set_property_value_function(get_symbol_properties_function(Qinterface_warning_message_level),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_246 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)0L),
	    FIX((SI_Long)1L),FIX((SI_Long)2L),FIX((SI_Long)3L));
    list_constant_42 = STATIC_LIST_STAR((SI_Long)3L,Qmember,
	    Qwarning_message_level,list_constant_246);
    define_type_specification_explicit_complex_type(Qinterface_warning_message_level,
	    list_constant_42);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qinterface_warning_message_level);
    interface_warning_message_level_evaluation_setter_1 = 
	    STATIC_FUNCTION(interface_warning_message_level_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qinterface_warning_message_level,
	    interface_warning_message_level_evaluation_setter_1);
    interface_warning_message_level_evaluation_getter_1 = 
	    STATIC_FUNCTION(interface_warning_message_level_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinterface_warning_message_level,
	    interface_warning_message_level_evaluation_getter_1);
    Qdisplay_expression = STATIC_SYMBOL("DISPLAY-EXPRESSION",AB_package);
    note_text_category_evaluator_interface(Qdisplay_expression);
    list_constant_44 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qtext,
	    list_constant_217);
    set_property_value_function(get_symbol_properties_function(Qdisplay_expression),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qdisplay_expression,
	    list_constant_44);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qnamed,Qdisplay_expression);
    array_constant_8 = STATIC_ARRAY(list_constant_76,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    display_expression_evaluation_setter_1 = 
	    STATIC_FUNCTION(display_expression_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qdisplay_expression,
	    display_expression_evaluation_setter_1);
    display_expression_evaluation_getter_1 = 
	    STATIC_FUNCTION(display_expression_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qdisplay_expression,
	    display_expression_evaluation_getter_1);
    Qcategory_committer_function = 
	    STATIC_SYMBOL("CATEGORY-COMMITTER-FUNCTION",AB_package);
    Qtext_category_slot_access_committer = 
	    STATIC_SYMBOL("TEXT-CATEGORY-SLOT-ACCESS-COMMITTER",AB_package);
    SET_SYMBOL_FUNCTION(Qtext_category_slot_access_committer,
	    STATIC_FUNCTION(text_category_slot_access_committer,NIL,FALSE,
	    3,3));
    set_property_value_function(get_symbol_properties_function(Qdisplay_expression),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    Qcategory_extracter_function = 
	    STATIC_SYMBOL("CATEGORY-EXTRACTER-FUNCTION",AB_package);
    Qtext_category_slot_access_extracter = 
	    STATIC_SYMBOL("TEXT-CATEGORY-SLOT-ACCESS-EXTRACTER",AB_package);
    SET_SYMBOL_FUNCTION(Qtext_category_slot_access_extracter,
	    STATIC_FUNCTION(text_category_slot_access_extracter,NIL,FALSE,
	    2,2));
    set_property_value_function(get_symbol_properties_function(Qdisplay_expression),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qembedded_rule = STATIC_SYMBOL("EMBEDDED-RULE",AB_package);
    note_text_category_evaluator_interface(Qembedded_rule);
    set_property_value_function(get_symbol_properties_function(Qembedded_rule),
	    Qtype_specification_simple_expansion,Qtext);
    define_type_specification_explicit_complex_type(Qembedded_rule,Qtext);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qnamed,Qembedded_rule);
    embedded_rule_evaluation_setter_1 = 
	    STATIC_FUNCTION(embedded_rule_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qembedded_rule,
	    embedded_rule_evaluation_setter_1);
    embedded_rule_evaluation_getter_1 = 
	    STATIC_FUNCTION(embedded_rule_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qembedded_rule,
	    embedded_rule_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qembedded_rule),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qembedded_rule),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    note_text_category_evaluator_interface(Qexpression);
    set_property_value_function(get_symbol_properties_function(Qexpression),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qexpression,
	    list_constant_44);
    list_constant_46 = STATIC_CONS(Qnamed,list_constant_92);
    expression_evaluation_setter_1 = 
	    STATIC_FUNCTION(expression_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qexpression,
	    expression_evaluation_setter_1);
    expression_evaluation_getter_1 = 
	    STATIC_FUNCTION(expression_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qexpression,
	    expression_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qexpression),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qexpression),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qforeign_function_declaration = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-DECLARATION",AB_package);
    note_text_category_evaluator_interface(Qforeign_function_declaration);
    set_property_value_function(get_symbol_properties_function(Qforeign_function_declaration),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qforeign_function_declaration,
	    list_constant_44);
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qforeign_function_declaration);
    foreign_function_declaration_evaluation_setter_1 = 
	    STATIC_FUNCTION(foreign_function_declaration_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qforeign_function_declaration,
	    foreign_function_declaration_evaluation_setter_1);
    foreign_function_declaration_evaluation_getter_1 = 
	    STATIC_FUNCTION(foreign_function_declaration_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qforeign_function_declaration,
	    foreign_function_declaration_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qforeign_function_declaration),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qforeign_function_declaration),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qfunction_definition = STATIC_SYMBOL("FUNCTION-DEFINITION",AB_package);
    note_text_category_evaluator_interface(Qfunction_definition);
    set_property_value_function(get_symbol_properties_function(Qfunction_definition),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qfunction_definition,
	    list_constant_44);
    list_constant_48 = STATIC_LIST((SI_Long)2L,Qnamed,Qfunction_definition);
    function_definition_evaluation_setter_1 = 
	    STATIC_FUNCTION(function_definition_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qfunction_definition,
	    function_definition_evaluation_setter_1);
    function_definition_evaluation_getter_1 = 
	    STATIC_FUNCTION(function_definition_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfunction_definition,
	    function_definition_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qfunction_definition),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qfunction_definition),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    note_text_category_evaluator_interface(Qgeneric_formula);
    set_property_value_function(get_symbol_properties_function(Qgeneric_formula),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qgeneric_formula,
	    list_constant_44);
    list_constant_247 = STATIC_CONS(Qgeneric_formula,Qnil);
    list_constant_49 = STATIC_CONS(Qnamed,list_constant_247);
    generic_formula_evaluation_setter_1 = 
	    STATIC_FUNCTION(generic_formula_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgeneric_formula,
	    generic_formula_evaluation_setter_1);
    generic_formula_evaluation_getter_1 = 
	    STATIC_FUNCTION(generic_formula_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgeneric_formula,
	    generic_formula_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qgeneric_formula),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qgeneric_formula),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qgeneric_simulation_formula = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA",AB_package);
    note_text_category_evaluator_interface(Qgeneric_simulation_formula);
    set_property_value_function(get_symbol_properties_function(Qgeneric_simulation_formula),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qgeneric_simulation_formula,
	    list_constant_44);
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qgeneric_simulation_formula);
    generic_simulation_formula_evaluation_setter_1 = 
	    STATIC_FUNCTION(generic_simulation_formula_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgeneric_simulation_formula,
	    generic_simulation_formula_evaluation_setter_1);
    generic_simulation_formula_evaluation_getter_1 = 
	    STATIC_FUNCTION(generic_simulation_formula_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgeneric_simulation_formula,
	    generic_simulation_formula_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qgeneric_simulation_formula),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qgeneric_simulation_formula),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qgfi_output_values = STATIC_SYMBOL("GFI-OUTPUT-VALUES",AB_package);
    note_text_category_evaluator_interface(Qgfi_output_values);
    set_property_value_function(get_symbol_properties_function(Qgfi_output_values),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qgfi_output_values,
	    list_constant_44);
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qnamed,Qgfi_output_values);
    gfi_output_values_evaluation_setter_1 = 
	    STATIC_FUNCTION(gfi_output_values_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgfi_output_values,
	    gfi_output_values_evaluation_setter_1);
    gfi_output_values_evaluation_getter_1 = 
	    STATIC_FUNCTION(gfi_output_values_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgfi_output_values,
	    gfi_output_values_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qgfi_output_values),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qgfi_output_values),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qinstance_formula = STATIC_SYMBOL("INSTANCE-FORMULA",AB_package);
    note_text_category_evaluator_interface(Qinstance_formula);
    set_property_value_function(get_symbol_properties_function(Qinstance_formula),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qinstance_formula,
	    list_constant_44);
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qnamed,Qinstance_formula);
    instance_formula_evaluation_setter_1 = 
	    STATIC_FUNCTION(instance_formula_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qinstance_formula,
	    instance_formula_evaluation_setter_1);
    instance_formula_evaluation_getter_1 = 
	    STATIC_FUNCTION(instance_formula_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinstance_formula,
	    instance_formula_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qinstance_formula),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qinstance_formula),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qitem_designations_for_model = 
	    STATIC_SYMBOL("ITEM-DESIGNATIONS-FOR-MODEL",AB_package);
    note_text_category_evaluator_interface(Qitem_designations_for_model);
    set_property_value_function(get_symbol_properties_function(Qitem_designations_for_model),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qitem_designations_for_model,
	    list_constant_44);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qitem_designations_for_model);
    item_designations_for_model_evaluation_setter_1 = 
	    STATIC_FUNCTION(item_designations_for_model_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qitem_designations_for_model,
	    item_designations_for_model_evaluation_setter_1);
    item_designations_for_model_evaluation_getter_1 = 
	    STATIC_FUNCTION(item_designations_for_model_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qitem_designations_for_model,
	    item_designations_for_model_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qitem_designations_for_model),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qitem_designations_for_model),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qlanguage_translation = STATIC_SYMBOL("LANGUAGE-TRANSLATION",AB_package);
    note_text_category_evaluator_interface(Qlanguage_translation);
    set_property_value_function(get_symbol_properties_function(Qlanguage_translation),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qlanguage_translation,
	    list_constant_44);
    list_constant_54 = STATIC_LIST((SI_Long)2L,Qnamed,Qlanguage_translation);
    language_translation_evaluation_setter_1 = 
	    STATIC_FUNCTION(language_translation_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qlanguage_translation,
	    language_translation_evaluation_setter_1);
    language_translation_evaluation_getter_1 = 
	    STATIC_FUNCTION(language_translation_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlanguage_translation,
	    language_translation_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qlanguage_translation),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qlanguage_translation),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qlist_of_graph_expressions = STATIC_SYMBOL("LIST-OF-GRAPH-EXPRESSIONS",
	    AB_package);
    note_text_category_evaluator_interface(Qlist_of_graph_expressions);
    set_property_value_function(get_symbol_properties_function(Qlist_of_graph_expressions),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qlist_of_graph_expressions,
	    list_constant_44);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qlist_of_graph_expressions);
    list_of_graph_expressions_evaluation_setter_1 = 
	    STATIC_FUNCTION(list_of_graph_expressions_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlist_of_graph_expressions,
	    list_of_graph_expressions_evaluation_setter_1);
    list_of_graph_expressions_evaluation_getter_1 = 
	    STATIC_FUNCTION(list_of_graph_expressions_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlist_of_graph_expressions,
	    list_of_graph_expressions_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qlist_of_graph_expressions),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qlist_of_graph_expressions),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qlogical_instance_formula = STATIC_SYMBOL("LOGICAL-INSTANCE-FORMULA",
	    AB_package);
    note_text_category_evaluator_interface(Qlogical_instance_formula);
    set_property_value_function(get_symbol_properties_function(Qlogical_instance_formula),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qlogical_instance_formula,
	    list_constant_44);
    list_constant_56 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qlogical_instance_formula);
    logical_instance_formula_evaluation_setter_1 = 
	    STATIC_FUNCTION(logical_instance_formula_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qlogical_instance_formula,
	    logical_instance_formula_evaluation_setter_1);
    logical_instance_formula_evaluation_getter_1 = 
	    STATIC_FUNCTION(logical_instance_formula_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlogical_instance_formula,
	    logical_instance_formula_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qlogical_instance_formula),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qlogical_instance_formula),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qprocedure_definition = STATIC_SYMBOL("PROCEDURE-DEFINITION",AB_package);
    note_text_category_evaluator_interface(Qprocedure_definition);
    set_property_value_function(get_symbol_properties_function(Qprocedure_definition),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qprocedure_definition,
	    list_constant_44);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qnamed,Qprocedure_definition);
    procedure_definition_evaluation_setter_1 = 
	    STATIC_FUNCTION(procedure_definition_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qprocedure_definition,
	    procedure_definition_evaluation_setter_1);
    procedure_definition_evaluation_getter_1 = 
	    STATIC_FUNCTION(procedure_definition_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qprocedure_definition,
	    procedure_definition_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qprocedure_definition),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qprocedure_definition),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qremote_procedure_declaration = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-DECLARATION",AB_package);
    note_text_category_evaluator_interface(Qremote_procedure_declaration);
    set_property_value_function(get_symbol_properties_function(Qremote_procedure_declaration),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qremote_procedure_declaration,
	    list_constant_44);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qremote_procedure_declaration);
    remote_procedure_declaration_evaluation_setter_1 = 
	    STATIC_FUNCTION(remote_procedure_declaration_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qremote_procedure_declaration,
	    remote_procedure_declaration_evaluation_setter_1);
    remote_procedure_declaration_evaluation_getter_1 = 
	    STATIC_FUNCTION(remote_procedure_declaration_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qremote_procedure_declaration,
	    remote_procedure_declaration_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qremote_procedure_declaration),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qremote_procedure_declaration),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    note_text_category_evaluator_interface(Qrule);
    set_property_value_function(get_symbol_properties_function(Qrule),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qrule,list_constant_44);
    list_constant_248 = STATIC_CONS(Qrule,Qnil);
    list_constant_59 = STATIC_CONS(Qnamed,list_constant_248);
    rule_evaluation_setter_1 = STATIC_FUNCTION(rule_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qrule,rule_evaluation_setter_1);
    rule_evaluation_getter_1 = STATIC_FUNCTION(rule_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qrule,
	    rule_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qrule),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qrule),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qspecific_simulation_formula = 
	    STATIC_SYMBOL("SPECIFIC-SIMULATION-FORMULA",AB_package);
    note_text_category_evaluator_interface(Qspecific_simulation_formula);
    set_property_value_function(get_symbol_properties_function(Qspecific_simulation_formula),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qspecific_simulation_formula,
	    list_constant_44);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qspecific_simulation_formula);
    specific_simulation_formula_evaluation_setter_1 = 
	    STATIC_FUNCTION(specific_simulation_formula_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qspecific_simulation_formula,
	    specific_simulation_formula_evaluation_setter_1);
    specific_simulation_formula_evaluation_getter_1 = 
	    STATIC_FUNCTION(specific_simulation_formula_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qspecific_simulation_formula,
	    specific_simulation_formula_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qspecific_simulation_formula),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qspecific_simulation_formula),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qtext_conversion_style_name = 
	    STATIC_SYMBOL("TEXT-CONVERSION-STYLE-NAME",AB_package);
    note_text_category_evaluator_interface(Qtext_conversion_style_name);
    set_property_value_function(get_symbol_properties_function(Qtext_conversion_style_name),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qtext_conversion_style_name,
	    list_constant_44);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtext_conversion_style_name);
    text_conversion_style_name_evaluation_setter_1 = 
	    STATIC_FUNCTION(text_conversion_style_name_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtext_conversion_style_name,
	    text_conversion_style_name_evaluation_setter_1);
    text_conversion_style_name_evaluation_getter_1 = 
	    STATIC_FUNCTION(text_conversion_style_name_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtext_conversion_style_name,
	    text_conversion_style_name_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qtext_conversion_style_name),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qtext_conversion_style_name),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qunits_declaration = STATIC_SYMBOL("UNITS-DECLARATION",AB_package);
    note_text_category_evaluator_interface(Qunits_declaration);
    set_property_value_function(get_symbol_properties_function(Qunits_declaration),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qunits_declaration,
	    list_constant_44);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qnamed,Qunits_declaration);
    units_declaration_evaluation_setter_1 = 
	    STATIC_FUNCTION(units_declaration_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qunits_declaration,
	    units_declaration_evaluation_setter_1);
    units_declaration_evaluation_getter_1 = 
	    STATIC_FUNCTION(units_declaration_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qunits_declaration,
	    units_declaration_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qunits_declaration),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qunits_declaration),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Quser_menu_choice_expression = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-EXPRESSION",AB_package);
    note_text_category_evaluator_interface(Quser_menu_choice_expression);
    set_property_value_function(get_symbol_properties_function(Quser_menu_choice_expression),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Quser_menu_choice_expression,
	    list_constant_44);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Quser_menu_choice_expression);
    user_menu_choice_expression_evaluation_setter_1 = 
	    STATIC_FUNCTION(user_menu_choice_expression_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Quser_menu_choice_expression,
	    user_menu_choice_expression_evaluation_setter_1);
    user_menu_choice_expression_evaluation_getter_1 = 
	    STATIC_FUNCTION(user_menu_choice_expression_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Quser_menu_choice_expression,
	    user_menu_choice_expression_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Quser_menu_choice_expression),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Quser_menu_choice_expression),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qfree = STATIC_SYMBOL("FREE",AB_package);
    note_text_category_evaluator_interface(Qfree);
    set_property_value_function(get_symbol_properties_function(Qfree),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qfree,list_constant_44);
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qnamed,Qfree);
    free_evaluation_setter_1 = STATIC_FUNCTION(free_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qfree,free_evaluation_setter_1);
    free_evaluation_getter_1 = STATIC_FUNCTION(free_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfree,
	    free_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qfree),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    set_property_value_function(get_symbol_properties_function(Qfree),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Quser_menu_choice_expression_initialization = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-EXPRESSION-INITIALIZATION",
	    AB_package);
    note_text_category_evaluator_interface(Quser_menu_choice_expression_initialization);
    set_property_value_function(get_symbol_properties_function(Quser_menu_choice_expression_initialization),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Quser_menu_choice_expression_initialization,
	    list_constant_44);
    list_constant_65 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Quser_menu_choice_expression_initialization);
    user_menu_choice_expression_initialization_evaluation_setter_1 = 
	    STATIC_FUNCTION(user_menu_choice_expression_initialization_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Quser_menu_choice_expression_initialization,
	    user_menu_choice_expression_initialization_evaluation_setter_1);
    string_constant_15 = STATIC_STRING("[deleted attribute]");
    user_menu_choice_expression_initialization_evaluation_getter_1 = 
	    STATIC_FUNCTION(user_menu_choice_expression_initialization_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Quser_menu_choice_expression_initialization,
	    user_menu_choice_expression_initialization_evaluation_getter_1);
    note_text_category_evaluator_interface(Qconstant_variable_designation_qm);
    set_property_value_function(get_symbol_properties_function(Qconstant_variable_designation_qm),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qconstant_variable_designation_qm,
	    list_constant_44);
    list_constant_66 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qconstant_variable_designation_qm);
    constant_variable_designation_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(constant_variable_designation_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qconstant_variable_designation_qm,
	    constant_variable_designation_qm_evaluation_setter_1);
    constant_variable_designation_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(constant_variable_designation_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconstant_variable_designation_qm,
	    constant_variable_designation_qm_evaluation_getter_1);
    Qgfi_interface_object = STATIC_SYMBOL("GFI-INTERFACE-OBJECT",AB_package);
    note_text_category_evaluator_interface(Qgfi_interface_object);
    set_property_value_function(get_symbol_properties_function(Qgfi_interface_object),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qgfi_interface_object,
	    list_constant_44);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qnamed,Qgfi_interface_object);
    gfi_interface_object_evaluation_setter_1 = 
	    STATIC_FUNCTION(gfi_interface_object_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qgfi_interface_object,
	    gfi_interface_object_evaluation_setter_1);
    gfi_interface_object_evaluation_getter_1 = 
	    STATIC_FUNCTION(gfi_interface_object_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgfi_interface_object,
	    gfi_interface_object_evaluation_getter_1);
    Qgfi_file_pathname = STATIC_SYMBOL("GFI-FILE-PATHNAME",AB_package);
    note_text_category_evaluator_interface(Qgfi_file_pathname);
    set_property_value_function(get_symbol_properties_function(Qgfi_file_pathname),
	    Qtype_specification_simple_expansion,list_constant_44);
    define_type_specification_explicit_complex_type(Qgfi_file_pathname,
	    list_constant_44);
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qnamed,Qgfi_file_pathname);
    gfi_file_pathname_evaluation_setter_1 = 
	    STATIC_FUNCTION(gfi_file_pathname_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgfi_file_pathname,
	    gfi_file_pathname_evaluation_setter_1);
    gfi_file_pathname_evaluation_getter_1 = 
	    STATIC_FUNCTION(gfi_file_pathname_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgfi_file_pathname,
	    gfi_file_pathname_evaluation_getter_1);
}
