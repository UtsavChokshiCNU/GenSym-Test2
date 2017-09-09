/* utlts1.c
 * Input file:  utilities1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "utlts1.h"


Object String_allocation_schemes = UNBOUND;

Object Maximum_gensym_string_length = UNBOUND;

Object Maximum_gensym_string_length_exceeded_message = UNBOUND;

/* MAXIMUM-GENSYM-STRING-LENGTH-ERROR */
Object maximum_gensym_string_length_error(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(23,0);
    temp = error((SI_Long)3L,
	    "Attempting to allocate ~a element string, which is beyond the established maximum of ~a.",
	    length_1,Maximum_gensym_string_length);
    return VALUES_1(temp);
}

/* NEW-SHORT-SIMPLE-GENSYM-STRING-VECTOR */
Object new_short_simple_gensym_string_vector(initial_element)
    Object initial_element;
{
    Object temp;

    x_note_fn_call(23,1);
    temp = make_array(3,
	    FIXNUM_ADD1(Maximum_suggested_length_for_simple_gensym_strings),
	    Kinitial_element,initial_element);
    return VALUES_1(temp);
}

/* NEW-PARTIAL-BUFFER-GENSYM-STRING-VECTOR */
Object new_partial_buffer_gensym_string_vector(initial_element)
    Object initial_element;
{
    Object temp;

    x_note_fn_call(23,2);
    temp = make_array(3,
	    FIXNUM_ADD1(partial_buffer_pool_index_given_length(Maximum_gensym_string_length,
	    String_allocation_schemes)),Kinitial_element,initial_element);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Short_simple_gensym_strings, Qshort_simple_gensym_strings);

DEFINE_VARIABLE_WITH_SYMBOL(Long_simple_gensym_strings, Qlong_simple_gensym_strings);

DEFINE_VARIABLE_WITH_SYMBOL(Adjustable_gensym_strings, Qadjustable_gensym_strings);

DEFINE_VARIABLE_WITH_SYMBOL(Short_simple_gensym_string_counts, Qshort_simple_gensym_string_counts);

DEFINE_VARIABLE_WITH_SYMBOL(Long_simple_gensym_string_counts, Qlong_simple_gensym_string_counts);

DEFINE_VARIABLE_WITH_SYMBOL(Adjustable_gensym_string_counts, Qadjustable_gensym_string_counts);

DEFINE_VARIABLE_WITH_SYMBOL(Available_string_pool_conses, Qavailable_string_pool_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_string_pool_conses_tail, Qavailable_string_pool_conses_tail);

Object Available_string_pool_conses_vector = UNBOUND;

Object Available_string_pool_conses_tail_vector = UNBOUND;

Object String_pool_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(String_pool_cons_counter, Qstring_pool_cons_counter);

/* OUTSTANDING-STRING-POOL-CONSES */
Object outstanding_string_pool_conses()
{
    Object temp;

    x_note_fn_call(23,3);
    temp = FIXNUM_MINUS(String_pool_cons_counter,
	    length(Available_string_pool_conses));
    return VALUES_1(temp);
}

/* STRING-POOL-CONS-MEMORY-USAGE */
Object string_pool_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(23,4);
    temp = FIXNUM_TIMES(String_pool_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-STRING-POOL-CONS-POOL */
Object replenish_string_pool_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(23,5);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qstring_pool_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_string_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_string_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_string_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = String_pool_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qstring_pool;        /* string-pool */

/* STRING-POOL-CONS-1 */
Object string_pool_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(23,6);
    new_cons = ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_string_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_string_pool_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_string_pool_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qstring_pool);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-STRING-POOL-LIST-POOL */
Object replenish_string_pool_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(23,7);
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
    if (ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_string_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_string_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_string_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qstring_pool_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-STRING-POOL-LIST-1 */
Object make_string_pool_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(23,8);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_string_pool_conses_vector,
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
	replenish_string_pool_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_string_pool_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qstring_pool);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_string_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_string_pool_conses_tail_vector;
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

/* STRING-POOL-LIST-2 */
Object string_pool_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(23,9);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_string_pool_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qstring_pool);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_string_pool_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_string_pool_conses_tail_vector;
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

/* STRING-POOL-LIST-3 */
Object string_pool_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(23,10);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_string_pool_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qstring_pool);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_string_pool_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_string_pool_conses_tail_vector;
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

/* STRING-POOL-LIST-4 */
Object string_pool_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(23,11);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_string_pool_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qstring_pool);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_string_pool_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_string_pool_conses_tail_vector;
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

/* STRING-POOL-LIST-TRACE-HOOK */
Object string_pool_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(23,12);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-STRING-POOL-CONSES-1 */
Object copy_tree_using_string_pool_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(23,13);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_string_pool_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_string_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_string_pool_cons_pool();
	temp_1 = copy_tree_using_string_pool_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstring_pool);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_string_pool_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_string_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_string_pool_cons_pool();
	temp_1 = 
		copy_tree_using_string_pool_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstring_pool);
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

/* COPY-LIST-USING-STRING-POOL-CONSES-1 */
Object copy_list_using_string_pool_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(23,14);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_string_pool_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_string_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_string_pool_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstring_pool);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_string_pool_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_string_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_string_pool_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstring_pool);
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

/* RECLAIM-STRING-POOL-CONS-1 */
Object reclaim_string_pool_cons_1(string_pool_cons)
    Object string_pool_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(23,15);
    inline_note_reclaim_cons(string_pool_cons,Qstring_pool);
    if (ISVREF(Available_string_pool_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_string_pool_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = string_pool_cons;
	temp = Available_string_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = string_pool_cons;
    }
    else {
	temp = Available_string_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = string_pool_cons;
	temp = Available_string_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = string_pool_cons;
    }
    M_CDR(string_pool_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-STRING-POOL-LIST-1 */
Object reclaim_string_pool_list_1(string_pool_list)
    Object string_pool_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(23,16);
    if (string_pool_list) {
	last_1 = string_pool_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qstring_pool);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qstring_pool);
	if (ISVREF(Available_string_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_string_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = string_pool_list;
	    temp = Available_string_pool_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_string_pool_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = string_pool_list;
	    temp = Available_string_pool_conses_tail_vector;
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

/* RECLAIM-STRING-POOL-LIST*-1 */
Object reclaim_string_pool_list_star_1(string_pool_list)
    Object string_pool_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(23,17);
    if (CONSP(string_pool_list)) {
	temp = last(string_pool_list,_);
	M_CDR(temp) = Nil;
	if (string_pool_list) {
	    last_1 = string_pool_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qstring_pool);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qstring_pool);
	    if (ISVREF(Available_string_pool_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_string_pool_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = string_pool_list;
		temp = Available_string_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_string_pool_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = string_pool_list;
		temp = Available_string_pool_conses_tail_vector;
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

/* RECLAIM-STRING-POOL-TREE-1 */
Object reclaim_string_pool_tree_1(tree)
    Object tree;
{
    Object e, e2, string_pool_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(23,18);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_string_pool_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		string_pool_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(string_pool_cons,Qstring_pool);
		if (EQ(string_pool_cons,e))
		    goto end_1;
		else if ( !TRUEP(string_pool_cons))
		    goto end_1;
		else
		    string_pool_cons = CDR(string_pool_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_string_pool_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_string_pool_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_string_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_string_pool_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_string_pool_conses_tail_vector;
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

/* DELETE-STRING-POOL-ELEMENT-1 */
Object delete_string_pool_element_1(element,string_pool_list)
    Object element, string_pool_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(23,19);
    if (string_pool_list) {
	if (EQ(element,M_CAR(string_pool_list))) {
	    temp = CDR(string_pool_list);
	    inline_note_reclaim_cons(string_pool_list,Qstring_pool);
	    if (ISVREF(Available_string_pool_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_string_pool_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = string_pool_list;
		temp_1 = Available_string_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = string_pool_list;
	    }
	    else {
		temp_1 = Available_string_pool_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = string_pool_list;
		temp_1 = Available_string_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = string_pool_list;
	    }
	    M_CDR(string_pool_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = string_pool_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qstring_pool);
		if (ISVREF(Available_string_pool_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_string_pool_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_string_pool_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_string_pool_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_string_pool_conses_tail_vector;
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
	    temp = string_pool_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-STRING-POOL-CONS-1 */
Object delete_string_pool_cons_1(string_pool_cons,string_pool_list)
    Object string_pool_cons, string_pool_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(23,20);
    if (EQ(string_pool_cons,string_pool_list))
	temp = CDR(string_pool_list);
    else {
	l_trailer_qm = Nil;
	l = string_pool_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,string_pool_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = string_pool_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_string_pool_cons_1(string_pool_cons);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Simple_gensym_string_counter, Qsimple_gensym_string_counter);

DEFINE_VARIABLE_WITH_SYMBOL(Simple_gensym_string_byte_use_counter, Qsimple_gensym_string_byte_use_counter);

/* SUM-RECLAIMED-STRINGS */
Object sum_reclaimed_strings(vector_1)
    Object vector_1;
{
    Object incff_1_arg, temp;
    SI_Long sum1, index_1, ab_loop_bind_;

    x_note_fn_call(23,21);
    sum1 = (SI_Long)0L;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1));
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    incff_1_arg = length(ISVREF(vector_1,index_1));
    sum1 = sum1 + IFIX(incff_1_arg);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = FIX(sum1);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* OUTSTANDING-SIMPLE-GENSYM-STRINGS */
Object outstanding_simple_gensym_strings()
{
    Object temp, temp_1;

    x_note_fn_call(23,22);
    temp = Simple_gensym_string_counter;
    temp_1 = sum_reclaimed_strings(Short_simple_gensym_strings);
    temp_1 = FIXNUM_MINUS(temp,FIXNUM_ADD(temp_1,
	    sum_reclaimed_strings(Long_simple_gensym_strings)));
    return VALUES_1(temp_1);
}

/* COMPUTE-MEMORY-USED-BY-SIMPLE-GENSYM-STRINGS */
Object compute_memory_used_by_simple_gensym_strings()
{
    x_note_fn_call(23,23);
    return VALUES_1(Simple_gensym_string_byte_use_counter);
}

DEFINE_VARIABLE_WITH_SYMBOL(String_pool_number_to_malloc, Qstring_pool_number_to_malloc);

DEFINE_VARIABLE_WITH_SYMBOL(Largest_non_malloced_string_pool_index, Qlargest_non_malloced_string_pool_index);

static Object Qsimple_gensym_string;  /* simple-gensym-string */

/* OBTAIN-SIMPLE-GENSYM-STRING */
Object obtain_simple_gensym_string(length_1)
    Object length_1;
{
    Object pool_qm, temp, temp_1, temp_2, string_1, trailing_cons_qm;
    Object pool_cons;
    SI_Long pool_index, temp_3;

    x_note_fn_call(23,24);
    if (FIXNUM_LE(length_1,
		Maximum_suggested_length_for_simple_gensym_strings)) {
	pool_qm = ISVREF(Short_simple_gensym_strings,IFIX(length_1));
	if (pool_qm) {
	    temp = M_CAR(pool_qm);
	    temp_1 = Short_simple_gensym_strings;
	    temp_2 = M_CDR(pool_qm);
	    SVREF(temp_1,length_1) = temp_2;
	    inline_note_reclaim_cons(pool_qm,Qstring_pool);
	    if (ISVREF(Available_string_pool_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_string_pool_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = pool_qm;
		temp_1 = Available_string_pool_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = pool_qm;
	    }
	    else {
		temp_1 = Available_string_pool_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = pool_qm;
		temp_1 = Available_string_pool_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = pool_qm;
	    }
	    M_CDR(pool_qm) = Nil;
	    string_1 = temp;
	}
	else
	    string_1 = allocate_new_simple_gensym_string(length_1,Nil);
    }
    else if (FIXNUM_GT(length_1,Maximum_gensym_string_length))
	string_1 = maximum_gensym_string_length_error(length_1);
    else {
	pool_index = IFIX(partial_buffer_pool_index_given_length(length_1,
		String_allocation_schemes));
	trailing_cons_qm = Nil;
	pool_cons = ISVREF(Long_simple_gensym_strings,pool_index);
      next_loop:
	if ( !TRUEP(pool_cons))
	    goto end_loop;
	if (FIXNUM_EQ(length_1,SIMPLE_ARRAY_ANY_1_LENGTH(M_CAR(pool_cons)))) {
	    if (trailing_cons_qm) {
		temp_1 = M_CDR(pool_cons);
		M_CDR(trailing_cons_qm) = temp_1;
	    }
	    else {
		temp_1 = Long_simple_gensym_strings;
		temp_2 = M_CDR(pool_cons);
		ISVREF(temp_1,pool_index) = temp_2;
	    }
	    temp = M_CAR(pool_cons);
	    inline_note_reclaim_cons(pool_cons,Qstring_pool);
	    if (ISVREF(Available_string_pool_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_string_pool_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = pool_cons;
		temp_1 = Available_string_pool_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = pool_cons;
	    }
	    else {
		temp_1 = Available_string_pool_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = pool_cons;
		temp_1 = Available_string_pool_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = pool_cons;
	    }
	    M_CDR(pool_cons) = Nil;
	    string_1 = temp;
	    goto end_1;
	}
	trailing_cons_qm = pool_cons;
	pool_cons = M_CDR(pool_cons);
	goto next_loop;
      end_loop:
	if (IFIX(String_pool_number_to_malloc) == (SI_Long)-1L || 
		pool_index < IFIX(String_pool_number_to_malloc))
	    string_1 = allocate_new_simple_gensym_string(length_1,Nil);
	else {
	    temp_3 = IFIX(Largest_non_malloced_string_pool_index);
	    Largest_non_malloced_string_pool_index = FIX(MAX(temp_3,
		    pool_index));
	    string_1 = allocate_new_simple_gensym_string(length_1,T);
	}
	goto end_1;
	string_1 = Qnil;
      end_1:;
    }
    inline_note_allocate_cons(string_1,Qsimple_gensym_string);
    return VALUES_1(string_1);
}

/* OBTAIN-SIMPLE-GENSYM-STRING-OF-QUANTIZED-LENGTH */
Object obtain_simple_gensym_string_of_quantized_length(length_1)
    Object length_1;
{
    Object temp, rounded_up_length, string_1;

    x_note_fn_call(23,25);
    if (FIXNUM_LE(length_1,Maximum_suggested_length_for_simple_gensym_strings))
	return obtain_simple_gensym_string(length_1);
    else {
	temp = 
		buffer_size_and_pool_for_partial_buffer(FIXNUM_ADD1(length_1),
		String_allocation_schemes);
	rounded_up_length = temp;
	string_1 = obtain_simple_gensym_string(rounded_up_length);
	temp = CHR('\000');
	SET_SCHAR(string_1,length_1,temp);
	return VALUES_1(string_1);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Log_simple_string_data, Qlog_simple_string_data);

DEFINE_VARIABLE_WITH_SYMBOL(Log_simple_string_reclaims, Qlog_simple_string_reclaims);

DEFINE_VARIABLE_WITH_SYMBOL(Min_string_length_to_report, Qmin_string_length_to_report);

DEFINE_VARIABLE_WITH_SYMBOL(String_report_frequency, Qstring_report_frequency);

DEFINE_VARIABLE_WITH_SYMBOL(String_allocations_until_next_report, Qstring_allocations_until_next_report);

DEFINE_VARIABLE_WITH_SYMBOL(String_reclaims_until_next_report, Qstring_reclaims_until_next_report);

DEFINE_VARIABLE_WITH_SYMBOL(String_chars_to_print, Qstring_chars_to_print);

/* SET-MALLOCED-STRING-THRESHHOLD */
Object set_malloced_string_threshhold(length_1)
    Object length_1;
{
    Object rounded_up_length, pool_index;
    Object result;

    x_note_fn_call(23,26);
    if (IFIX(length_1) == (SI_Long)-1L) {
	String_pool_number_to_malloc = FIX((SI_Long)-1L);
	return VALUES_1(String_pool_number_to_malloc);
    }
    else {
	result = buffer_size_and_pool_for_partial_buffer(length_1,
		String_allocation_schemes);
	MVS_2(result,rounded_up_length,pool_index);
	if (FIXNUM_GT(pool_index,Largest_non_malloced_string_pool_index))
	    String_pool_number_to_malloc = pool_index;
	return VALUES_1(rounded_up_length);
    }
}

/* FREE-MALLOCED-STRINGS */
Object free_malloced_strings()
{
    Object array_list, array, ab_loop_list_, svref_arg_1;
    SI_Long pool_index, ab_loop_bind_;

    x_note_fn_call(23,27);
    if (IFIX(String_pool_number_to_malloc) >= (SI_Long)0L) {
	pool_index = IFIX(String_pool_number_to_malloc);
	ab_loop_bind_ = IFIX(length(Long_simple_gensym_strings));
      next_loop:
	if (pool_index >= ab_loop_bind_)
	    goto end_loop;
	array_list = ISVREF(Long_simple_gensym_strings,pool_index);
	array = Nil;
	ab_loop_list_ = array_list;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	array = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	atomic_incff_symval(Qsimple_gensym_string_counter,FIX( - (SI_Long)1L));
	atomic_incff_symval(Qsimple_gensym_string_byte_use_counter,
		FIXNUM_NEGATE(bytes_per_simple_string(length(array))));
	g2rtl_free_malloced_array_internal(array);
	goto next_loop_1;
      end_loop_1:;
	reclaim_string_pool_list_1(array_list);
	svref_arg_1 = Long_simple_gensym_strings;
	ISVREF(svref_arg_1,pool_index) = Nil;
	svref_arg_1 = Long_simple_gensym_string_counts;
	ISVREF(svref_arg_1,pool_index) = FIX((SI_Long)0L);
	pool_index = pool_index + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* ALLOCATE-NEW-SIMPLE-GENSYM-STRING */
Object allocate_new_simple_gensym_string(length_1,malloc_p)
    Object length_1, malloc_p;
{
    Object svref_arg_1, temp, svref_new_value, temp_1;
    XDeclare_area(1);

    x_note_fn_call(23,28);
    if (FIXNUM_GT(length_1,Maximum_gensym_string_length))
	maximum_gensym_string_length_error(length_1);
    atomic_incff_symval(Qsimple_gensym_string_counter,FIX((SI_Long)1L));
    atomic_incff_symval(Qsimple_gensym_string_byte_use_counter,
	    bytes_per_simple_string(length_1));
    if (FIXNUM_LE(length_1,
		Maximum_suggested_length_for_simple_gensym_strings)) {
	svref_arg_1 = Short_simple_gensym_string_counts;
	temp = FIXNUM_ADD1(ISVREF(svref_arg_1,IFIX(length_1)));
	SVREF(svref_arg_1,length_1) = temp;
    }
    else {
	svref_arg_1 = Long_simple_gensym_string_counts;
	temp = partial_buffer_pool_index_given_length(length_1,
		String_allocation_schemes);
	svref_new_value = FIXNUM_ADD1(ISVREF(svref_arg_1,IFIX(temp)));
	SVREF(svref_arg_1,temp) = svref_new_value;
	if (Log_simple_string_data) {
	    if (FIXNUM_GE(length_1,Min_string_length_to_report)) {
		if (zerop(String_allocations_until_next_report)) {
		    report_simple_string_allocation(length_1);
		    String_allocations_until_next_report = 
			    FIXNUM_SUB1(String_report_frequency);
		}
		else
		    atomic_incff_symval(Qstring_allocations_until_next_report,
			    FIX( - (SI_Long)1L));
	    }
	}
    }
    if (malloc_p)
	temp_1 = g2rtl_make_malloced_string(IFIX(length_1));
    else {
	if (PUSH_AREA(Dynamic_area,0))
	    temp_1 = make_string(1,length_1);
	POP_AREA(0);
    }
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_custom_reclamation_stamp_qm, Qcurrent_custom_reclamation_stamp_qm);

/* RECLAIM-SIMPLE-GENSYM-STRING */
Object reclaim_simple_gensym_string(simple_gensym_string)
    Object simple_gensym_string;
{
    Object string_pool_vector, temp, ab_loop_iter_flag_, temp_1, temp_2;
    Object new_cons, svref_new_value, gensymed_symbol;
    SI_Long gensym_string_length_1, index_1, schar_arg_2, i, ab_loop_bind_, j;
    SI_Long ab_loop_bind__1;
    char short_string_qm;
    char schar_new_value;

    x_note_fn_call(23,29);
    inline_note_reclaim_cons(simple_gensym_string,Qsimple_gensym_string);
    gensym_string_length_1 = 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(simple_gensym_string));
    short_string_qm = gensym_string_length_1 <= 
	    IFIX(Maximum_suggested_length_for_simple_gensym_strings);
    string_pool_vector = short_string_qm ? Short_simple_gensym_strings : 
	    Long_simple_gensym_strings;
    index_1 = short_string_qm ? gensym_string_length_1 : 
	    IFIX(partial_buffer_pool_index_given_length(FIX(gensym_string_length_1),
	    String_allocation_schemes));
    if (Log_simple_string_data && Log_simple_string_reclaims) {
	if (gensym_string_length_1 >= IFIX(Min_string_length_to_report)) {
	    if (zerop(String_reclaims_until_next_report)) {
		report_simple_string_reclamation(simple_gensym_string,
			FIX(gensym_string_length_1));
		String_reclaims_until_next_report = 
			FIXNUM_SUB1(String_report_frequency);
	    }
	    else
		atomic_incff_symval(Qstring_reclaims_until_next_report,
			FIX( - (SI_Long)1L));
	}
    }
    if (gensym_string_length_1 > (SI_Long)0L) {
	temp = CHR('&');
	SET_SCHAR(simple_gensym_string,FIX((SI_Long)0L),temp);
	schar_arg_2 = gensym_string_length_1 - (SI_Long)1L;
	SET_ISCHAR(simple_gensym_string,schar_arg_2,'&');
	if (Current_custom_reclamation_stamp_qm) {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(length(Current_custom_reclamation_stamp_qm));
	    j = (SI_Long)1L;
	    ab_loop_bind__1 = gensym_string_length_1 - (SI_Long)1L;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    if ( !TRUEP(ab_loop_iter_flag_))
		j = j + (SI_Long)1L;
	    if (j >= ab_loop_bind__1)
		goto end_loop;
	    schar_new_value = ICHAR(Current_custom_reclamation_stamp_qm,i);
	    SET_ISCHAR(simple_gensym_string,j,schar_new_value);
	    ab_loop_iter_flag_ = Nil;
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
    }
    if (Free_malloced_arrays && IFIX(String_pool_number_to_malloc) <= 
	    index_1 &&  !(IFIX(String_pool_number_to_malloc) == 
	    (SI_Long)-1L) &&  !short_string_qm) {
	atomic_incff_symval(Qsimple_gensym_string_counter,FIX( - (SI_Long)1L));
	atomic_incff_symval(Qsimple_gensym_string_byte_use_counter,
		FIXNUM_NEGATE(bytes_per_simple_string(length(simple_gensym_string))));
	temp_1 = Long_simple_gensym_string_counts;
	temp_2 = FIXNUM_SUB1(ISVREF(temp_1,index_1));
	ISVREF(temp_1,index_1) = temp_2;
	g2rtl_free_malloced_array_internal(simple_gensym_string);
    }
    else {
	new_cons = ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_string_pool_conses_vector;
	    temp_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,temp_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_string_pool_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_string_pool_cons_pool();
	M_CAR(gensymed_symbol) = simple_gensym_string;
	temp_1 = ISVREF(string_pool_vector,index_1);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstring_pool);
	ISVREF(string_pool_vector,index_1) = gensymed_symbol;
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Adjustable_gensym_string_counter, Qadjustable_gensym_string_counter);

DEFINE_VARIABLE_WITH_SYMBOL(Adjustable_gensym_string_byte_use_counter, Qadjustable_gensym_string_byte_use_counter);

/* OUTSTANDING-ADJUSTABLE-GENSYM-STRINGS */
Object outstanding_adjustable_gensym_strings()
{
    Object temp;

    x_note_fn_call(23,30);
    temp = Adjustable_gensym_string_counter;
    temp = FIXNUM_MINUS(temp,sum_reclaimed_strings(Adjustable_gensym_strings));
    return VALUES_1(temp);
}

/* COMPUTE-MEMORY-USED-BY-ADJUSTABLE-GENSYM-STRINGS */
Object compute_memory_used_by_adjustable_gensym_strings()
{
    x_note_fn_call(23,31);
    return VALUES_1(Adjustable_gensym_string_byte_use_counter);
}

/* OBTAIN-ADJUSTABLE-GENSYM-STRING */
Object obtain_adjustable_gensym_string()
{
    Object temp;

    x_note_fn_call(23,32);
    temp = obtain_long_enough_adjustable_gensym_string(FIX((SI_Long)1024L));
    return VALUES_1(temp);
}

static Object Qadjustable_gensym_string;  /* adjustable-gensym-string */

/* OBTAIN-LONG-ENOUGH-ADJUSTABLE-GENSYM-STRING */
Object obtain_long_enough_adjustable_gensym_string(length_1)
    Object length_1;
{
    Object pool_qm, temp, temp_1, temp_2, string_1;
    SI_Long pool_index;

    x_note_fn_call(23,33);
    if (FIXNUM_GT(length_1,Maximum_gensym_string_length))
	maximum_gensym_string_length_error(length_1);
    pool_index = IFIX(partial_buffer_pool_index_given_length(length_1,
	    String_allocation_schemes));
    pool_qm = ISVREF(Adjustable_gensym_strings,pool_index);
    if (pool_qm) {
	temp = M_CAR(pool_qm);
	temp_1 = Adjustable_gensym_strings;
	temp_2 = M_CDR(pool_qm);
	ISVREF(temp_1,pool_index) = temp_2;
	inline_note_reclaim_cons(pool_qm,Qstring_pool);
	if (ISVREF(Available_string_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_string_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = pool_qm;
	    temp_1 = Available_string_pool_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = pool_qm;
	}
	else {
	    temp_1 = Available_string_pool_conses_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = pool_qm;
	    temp_1 = Available_string_pool_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = pool_qm;
	}
	M_CDR(pool_qm) = Nil;
	string_1 = temp;
    }
    else
	string_1 = 
		allocate_new_adjustable_gensym_string(buffer_size_for_partial_buffer(length_1,
		String_allocation_schemes));
    SET_FILL_POINTER(string_1,length_1);
    temp_1 = CODE_CHAR(FIX((SI_Long)0L));
    SET_CHAR(string_1,length_1,temp_1);
    inline_note_allocate_cons(string_1,Qadjustable_gensym_string);
    return VALUES_1(string_1);
}

/* ALLOCATE-NEW-ADJUSTABLE-GENSYM-STRING */
Object allocate_new_adjustable_gensym_string(length_1)
    Object length_1;
{
    Object temp_1;
    SI_Long temp;
    XDeclare_area(1);

    x_note_fn_call(23,34);
    atomic_incff_symval(Qadjustable_gensym_string_counter,FIX((SI_Long)1L));
    temp = IFIX(length_1) / IFIX(Bytes_per_rtl_ptr);
    atomic_incff_symval(Qadjustable_gensym_string_byte_use_counter,
	    FIX((SI_Long)36L + IFIX(FIXNUM_TIMES(FIX(temp),
	    Bytes_per_rtl_ptr))));
    atomic_incff_svslot(Adjustable_gensym_string_counts,
	    partial_buffer_pool_index_given_length(length_1,
	    String_allocation_schemes),FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp_1 = make_array(7,length_1,Kelement_type,Qstring_char,
		Kfill_pointer,length_1,Kadjustable,T);
    POP_AREA(0);
    return VALUES_1(temp_1);
}

/* RECLAIM-ADJUSTABLE-GENSYM-STRING */
Object reclaim_adjustable_gensym_string(adjustable_gensym_string)
    Object adjustable_gensym_string;
{
    Object length_1, temp, svref_arg_1, new_cons, temp_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol;
    SI_Long pool_index;

    x_note_fn_call(23,35);
    inline_note_reclaim_cons(adjustable_gensym_string,
	    Qadjustable_gensym_string);
    length_1 = array_dimension(adjustable_gensym_string,FIX((SI_Long)0L));
    pool_index = IFIX(partial_buffer_pool_index_given_length(length_1,
	    String_allocation_schemes));
    if (IFIX(length_1) > (SI_Long)0L) {
	temp = CHR('\?');
	SET_CHAR(adjustable_gensym_string,FIX((SI_Long)0L),temp);
    }
    svref_arg_1 = Adjustable_gensym_strings;
    new_cons = ISVREF(Available_string_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_string_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_string_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_string_pool_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_string_pool_cons_pool();
    M_CAR(gensymed_symbol) = adjustable_gensym_string;
    temp_1 = ISVREF(Adjustable_gensym_strings,pool_index);
    M_CDR(gensymed_symbol) = temp_1;
    inline_note_allocate_cons(gensymed_symbol,Qstring_pool);
    return VALUES_1(ISVREF(svref_arg_1,pool_index) = gensymed_symbol);
}

/* RECLAIM-GENSYM-STRING */
Object reclaim_gensym_string(gensym_string)
    Object gensym_string;
{
    x_note_fn_call(23,36);
    if (SIMPLE_STRING_P(gensym_string))
	reclaim_simple_gensym_string(gensym_string);
    else
	reclaim_adjustable_gensym_string(gensym_string);
    return VALUES_1(Nil);
}

/* RECLAIM-IF-GENSYM-STRING-FUNCTION */
Object reclaim_if_gensym_string_function(thing)
    Object thing;
{
    x_note_fn_call(23,37);
    if (STRINGP(thing))
	return reclaim_gensym_string(thing);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-GENSYM-STRINGS-IN-LIST */
Object reclaim_gensym_strings_in_list(list_1)
    Object list_1;
{
    Object gensym_string, ab_loop_list_;

    x_note_fn_call(23,38);
    gensym_string = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensym_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (STRINGP(gensym_string))
	reclaim_gensym_string(gensym_string);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* GENSYM-STRING-SUBSTRING */
Object gensym_string_substring(string_1,start_qm,end_qm)
    Object string_1, start_qm, end_qm;
{
    Object end_1, start, new_string, temp, ab_loop_iter_flag_;
    SI_Long i, ab_loop_bind_, j;
    char string_is_simple_qm;
    char schar_new_value;

    x_note_fn_call(23,39);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    end_1 = end_qm;
    if (end_1);
    else
	end_1 = string_is_simple_qm ? SIMPLE_ARRAY_ANY_1_LENGTH(string_1) :
		 length(string_1);
    start = start_qm;
    if (start);
    else
	start = FIX((SI_Long)0L);
    new_string = obtain_simple_gensym_string(FIXNUM_MINUS(end_1,start));
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    i = IFIX(temp);
    ab_loop_bind_ = IFIX(end_1);
    j = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	j = j + (SI_Long)1L;
    schar_new_value = string_is_simple_qm ? ISCHAR(string_1,i) : 
	    ICHAR(string_1,i);
    SET_ISCHAR(new_string,j,schar_new_value);
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(new_string);
    return VALUES_1(Qnil);
}

/* RECLAIM-GENSYM-TREE-WITH-TEXT-STRINGS */
Object reclaim_gensym_tree_with_text_strings(tree)
    Object tree;
{
    Object tail, car_1, next_tail;

    x_note_fn_call(23,40);
    tail = tree;
    car_1 = Nil;
    next_tail = Nil;
  next_loop:
    if (ATOM(tail))
	goto end_loop;
    car_1 = CAR(tail);
    next_tail = CDR(tail);
    reclaim_gensym_tree_with_text_strings(car_1);
    reclaim_gensym_cons_1(tail);
    tail = next_tail;
    goto next_loop;
  end_loop:
    if (text_string_p(tail))
	reclaim_text_string(tail);
    else if (STRINGP(tail))
	reclaim_gensym_string(tail);
    return VALUES_1(Nil);
}

/* COPY-GENSYM-TREE-WITH-TEXT-STRINGS */
Object copy_gensym_tree_with_text_strings(tree)
    Object tree;
{
    Object temp;

    x_note_fn_call(23,41);
    if (CONSP(tree)) {
	temp = copy_gensym_tree_with_text_strings(CAR(tree));
	return gensym_cons_1(temp,
		copy_gensym_tree_with_text_strings(CDR(tree)));
    }
    else if (text_string_p(tree) || STRINGP(tree))
	return copy_text_string(tree);
    else
	return VALUES_1(tree);
}

/* COPY-NULL-TERMINATED-STRING-AS-GENSYM-STRING */
Object copy_null_terminated_string_as_gensym_string(string_1)
    Object string_1;
{
    Object length_if_null_terminated_qm;

    x_note_fn_call(23,42);
    length_if_null_terminated_qm = length_of_null_terminated_string(string_1);
    if (length_if_null_terminated_qm)
	return gensym_string_substring(string_1,FIX((SI_Long)0L),
		length_if_null_terminated_qm);
    else
	return copy_gensym_string(string_1);
}

/* LENGTH-OF-NULL-TERMINATED-STRING */
Object length_of_null_terminated_string(string_1)
    Object string_1;
{
    SI_Long string_length, i, ab_loop_bind_;
    char string_is_simple_qm;

    x_note_fn_call(23,43);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    string_length = string_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1)) : IFIX(length(string_1));
    i = (SI_Long)0L;
    ab_loop_bind_ = string_length;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (CHAR_EQ(string_is_simple_qm ? CHR(ISCHAR(string_1,i)) : 
	    CHR(ICHAR(string_1,i)),CHR('\000')))
	return VALUES_1(FIX(i));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REQUIRE-SIMPLE-GENSYM-STRING */
Object require_simple_gensym_string(gensym_string)
    Object gensym_string;
{
    Object temp;

    x_note_fn_call(23,44);
    if ( !ARRAY_HAS_FILL_POINTER_P(gensym_string))
	temp = gensym_string;
    else {
	temp = copy_gensym_string(gensym_string);
	reclaim_gensym_string(gensym_string);
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Outputting_to_gensym_string, Qoutputting_to_gensym_string);

DEFINE_VARIABLE_WITH_SYMBOL(Current_gensym_string, Qcurrent_gensym_string);

DEFINE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_gensym_string, Qfill_pointer_for_current_gensym_string);

DEFINE_VARIABLE_WITH_SYMBOL(Total_length_of_current_gensym_string, Qtotal_length_of_current_gensym_string);

DEFINE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);

/* COPY-CURRENT-GENSYM-STRING */
Object copy_current_gensym_string(truncate_if_overly_long_qm)
    Object truncate_if_overly_long_qm;
{
    Object length_1, simple_qm, i, gensymed_symbol, gensymed_symbol_1;
    Object new_gensym_string, adjustable_gensym_string;
    SI_Long incff_1_arg, i_new_value, i_1, ab_loop_bind_;
    char temp;
    char temp_1;

    x_note_fn_call(23,45);
    length_1 = Fill_pointer_for_current_gensym_string;
    simple_qm = FIXNUM_LE(length_1,
	    Maximum_suggested_length_for_simple_gensym_strings) ? T : Nil;
    if (simple_qm);
    else if (truncate_if_overly_long_qm) {
	i = FIX((SI_Long)0L);
      next_loop:
	length_1 = i;
	gensymed_symbol = Current_gensym_string;
	gensymed_symbol_1 = T;
	temp = gensymed_symbol_1 ? CHARACTER_TO_CHAR(SCHAR(gensymed_symbol,
		i)) : CHARACTER_TO_CHAR(CHAR(gensymed_symbol,i));
	i = FIXNUM_ADD1(i);
	switch (temp) {
	  case '@':
	  case '~':
	    i = FIXNUM_ADD1(i);
	    break;
	  case '\\':
	    incff_1_arg = IFIX(CHAR_INT(gensymed_symbol_1 ? 
		    SCHAR(gensymed_symbol,i) : CHAR(gensymed_symbol,i))) < 
		    (SI_Long)40L ? (SI_Long)3L : (SI_Long)2L;
	    i_new_value = IFIX(i) + incff_1_arg;
	    i = FIX(i_new_value);
	    break;
	  default:
	    break;
	}
	if (FIXNUM_GT(i,Maximum_suggested_length_for_simple_gensym_strings))
	    goto end_loop;
	goto next_loop;
      end_loop:
	simple_qm = T;
	goto end_1;
	simple_qm = Qnil;
      end_1:;
    }
    else
	simple_qm = Nil;
    if (simple_qm)
	new_gensym_string = obtain_simple_gensym_string(length_1);
    else {
	adjustable_gensym_string = 
		obtain_long_enough_adjustable_gensym_string(length_1);
	SET_FILL_POINTER(adjustable_gensym_string,length_1);
	new_gensym_string = adjustable_gensym_string;
    }
    if (simple_qm) {
	i_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length_1);
      next_loop_1:
	if (i_1 >= ab_loop_bind_)
	    goto end_loop_1;
	temp_1 = ISCHAR(Current_gensym_string,i_1);
	SET_ISCHAR(new_gensym_string,i_1,temp_1);
	i_1 = i_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    else {
	i_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length_1);
      next_loop_2:
	if (i_1 >= ab_loop_bind_)
	    goto end_loop_2;
	temp_1 = ISCHAR(Current_gensym_string,i_1);
	SET_ICHAR(new_gensym_string,i_1,temp_1);
	i_1 = i_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
    }
    return VALUES_1(new_gensym_string);
}

/* COPY-OUT-CURRENT-GENSYM-STRING */
Object copy_out_current_gensym_string()
{
    Object temp;

    x_note_fn_call(23,46);
    temp = copy_current_gensym_string(Nil);
    reclaim_gensym_string(Current_gensym_string);
    return VALUES_1(temp);
}

/* COPY-GENSYM-STRING */
Object copy_gensym_string(string_1)
    Object string_1;
{
    Object new_gensym_string;
    SI_Long string_length, i, ab_loop_bind_;
    char string_is_simple_qm;
    char schar_new_value;

    x_note_fn_call(23,47);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    string_length = string_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1)) : IFIX(length(string_1));
    new_gensym_string = obtain_simple_gensym_string(FIX(string_length));
    if (string_is_simple_qm) {
	i = (SI_Long)0L;
	ab_loop_bind_ = string_length;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	schar_new_value = ISCHAR(string_1,i);
	SET_ISCHAR(new_gensym_string,i,schar_new_value);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else {
	i = (SI_Long)0L;
	ab_loop_bind_ = string_length;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	schar_new_value = ICHAR(string_1,i);
	SET_ISCHAR(new_gensym_string,i,schar_new_value);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(new_gensym_string);
}

/* COPY-PARTIAL-GENSYM-STRING */
Object copy_partial_gensym_string(string_1,part_length)
    Object string_1, part_length;
{
    Object new_gensym_string;
    SI_Long i, ab_loop_bind_;
    char string_is_simple_qm;
    char schar_new_value;

    x_note_fn_call(23,48);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    new_gensym_string = obtain_simple_gensym_string(part_length);
    if (string_is_simple_qm) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(part_length);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	schar_new_value = ISCHAR(string_1,i);
	SET_ISCHAR(new_gensym_string,i,schar_new_value);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(part_length);
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	schar_new_value = ICHAR(string_1,i);
	SET_ISCHAR(new_gensym_string,i,schar_new_value);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(new_gensym_string);
}

/* COPY-GENSYM-STRING-PORTION */
Object copy_gensym_string_portion(string_1,start,end_1)
    Object string_1, start, end_1;
{
    Object part_length, new_gensym_string, ab_loop_iter_flag_;
    SI_Long i, ab_loop_bind_, j;
    char string_is_simple_qm;
    char schar_new_value;

    x_note_fn_call(23,49);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    part_length = FIXNUM_MINUS(end_1,start);
    new_gensym_string = obtain_simple_gensym_string(part_length);
    if (string_is_simple_qm) {
	i = IFIX(start);
	ab_loop_bind_ = IFIX(end_1);
	j = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	schar_new_value = ISCHAR(string_1,i);
	SET_ISCHAR(new_gensym_string,j,schar_new_value);
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else {
	i = IFIX(start);
	ab_loop_bind_ = IFIX(end_1);
	j = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	schar_new_value = ICHAR(string_1,i);
	SET_ISCHAR(new_gensym_string,j,schar_new_value);
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(new_gensym_string);
}

/* COPY-GENSYM-STRING-INTO-SIMPLE-OR-ADJUSTABLE-GENSYM-STRING */
Object copy_gensym_string_into_simple_or_adjustable_gensym_string(string_1)
    Object string_1;
{
    Object new_gensym_string;
    SI_Long string_length, i, ab_loop_bind_;
    char string_is_simple_qm, new_string_is_simple_qm;
    char temp;

    x_note_fn_call(23,50);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    string_length = string_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1)) : IFIX(length(string_1));
    new_gensym_string = string_length > 
	    IFIX(Maximum_suggested_length_for_simple_gensym_strings) ? 
	    obtain_long_enough_adjustable_gensym_string(FIX(string_length)) 
	    : obtain_simple_gensym_string(FIX(string_length));
    new_string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(new_gensym_string);
    if (string_is_simple_qm) {
	if (new_string_is_simple_qm) {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = string_length;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    temp = ISCHAR(string_1,i);
	    SET_ISCHAR(new_gensym_string,i,temp);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	else {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = string_length;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    temp = ISCHAR(string_1,i);
	    SET_ICHAR(new_gensym_string,i,temp);
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
    }
    else if (new_string_is_simple_qm) {
	i = (SI_Long)0L;
	ab_loop_bind_ = string_length;
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
	temp = ICHAR(string_1,i);
	SET_ISCHAR(new_gensym_string,i,temp);
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
    }
    else {
	i = (SI_Long)0L;
	ab_loop_bind_ = string_length;
      next_loop_3:
	if (i >= ab_loop_bind_)
	    goto end_loop_3;
	temp = ICHAR(string_1,i);
	SET_ICHAR(new_gensym_string,i,temp);
	i = i + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
    }
    return VALUES_1(new_gensym_string);
}

/* COPY-PORTION-OF-STRING-INTO-SIMPLE-GENSYM-STRING */
Object copy_portion_of_string_into_simple_gensym_string(source_string,
	    source_start,source_end,destination_string,destination_start)
    Object source_string, source_start, source_end, destination_string;
    Object destination_start;
{
    Object ab_loop_iter_flag_;
    SI_Long i, ab_loop_bind_, j;
    char source_string_is_simple_qm;
    char schar_new_value;

    x_note_fn_call(23,51);
    source_string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(source_string);
    if (source_string_is_simple_qm) {
	i = IFIX(source_start);
	ab_loop_bind_ = IFIX(source_end);
	j = IFIX(destination_start);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	schar_new_value = ISCHAR(source_string,i);
	SET_ISCHAR(destination_string,j,schar_new_value);
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	i = IFIX(source_start);
	ab_loop_bind_ = IFIX(source_end);
	j = IFIX(destination_start);
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	schar_new_value = ICHAR(source_string,i);
	SET_ISCHAR(destination_string,j,schar_new_value);
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* COPY-PORTION-OF-STRING-INTO-GENSYM-STRING */
Object copy_portion_of_string_into_gensym_string(source_string,
	    source_start,source_end,destination_string,destination_start)
    Object source_string, source_start, source_end, destination_string;
    Object destination_start;
{
    Object ab_loop_iter_flag_;
    SI_Long i, ab_loop_bind_, j;
    char source_string_is_simple_qm;
    char char_new_value;

    x_note_fn_call(23,52);
    source_string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(source_string);
    if (source_string_is_simple_qm) {
	i = IFIX(source_start);
	ab_loop_bind_ = IFIX(source_end);
	j = IFIX(destination_start);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	char_new_value = ISCHAR(source_string,i);
	SET_ICHAR(destination_string,j,char_new_value);
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	i = IFIX(source_start);
	ab_loop_bind_ = IFIX(source_end);
	j = IFIX(destination_start);
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	char_new_value = ICHAR(source_string,i);
	SET_ICHAR(destination_string,j,char_new_value);
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Write_symbols_parsably_qm, Qwrite_symbols_parsably_qm);

/* POSITION-IN-GENSYM-STRING */
Object position_in_gensym_string(character_1,gensym_string)
    Object character_1, gensym_string;
{
    Object len, ch, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(23,53);
    if ( !ARRAY_HAS_FILL_POINTER_P(gensym_string)) {
	len = length(gensym_string);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(len);
	ch = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ch = CHR(ISCHAR(gensym_string,i));
	if (CHAR_EQ(ch,character_1)) {
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
	len = length(gensym_string);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(len);
	ch = Nil;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	ch = CHR(ICHAR(gensym_string,i));
	if (CHAR_EQ(ch,character_1)) {
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

/* FIND-IN-GENSYM-STRING */
Object find_in_gensym_string(character_1,string_1)
    Object character_1, string_1;
{
    Object char_1, temp;
    SI_Long i, ab_loop_bind_;
    char string_is_simple_qm;

    x_note_fn_call(23,54);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = string_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1)) : IFIX(length(string_1));
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_1 = string_is_simple_qm ? CHR(ISCHAR(string_1,i)) : 
	    CHR(ICHAR(string_1,i));
    if (CHAR_EQ(char_1,character_1)) {
	temp = char_1;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FIND-GENSYM-CHARACTER-IN-LIST */
Object find_gensym_character_in_list(character_1,list_1)
    Object character_1, list_1;
{
    Object char_1, ab_loop_list_, temp;
    SI_Long i;

    x_note_fn_call(23,55);
    i = (SI_Long)0L;
    char_1 = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    char_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CHAR_EQ(char_1,character_1)) {
	temp = char_1;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FIND-GENSYM-CHARACTER-IN-SEQUENCE */
Object find_gensym_character_in_sequence(character_1,bag)
    Object character_1, bag;
{
    Object temp;

    x_note_fn_call(23,56);
    if (STRINGP(bag))
	temp = find_in_gensym_string(character_1,bag);
    else if (LISTP(bag))
	temp = find_gensym_character_in_list(character_1,bag);
    else
	temp = find(4,character_1,bag,Ktest,SYMBOL_FUNCTION(Qchar_eq));
    return VALUES_1(temp);
}

/* POSITION-OF-ASCII-CHARACTER-NOT-IN-BAG-FUNCTION */
Object position_of_ascii_character_not_in_bag_function(string_1,bag,start,
	    end_1)
    Object string_1, bag, start, end_1;
{
    Object temp;
    SI_Long i, ab_loop_bind_;
    char string_is_simple_qm;

    x_note_fn_call(23,57);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    temp = start;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    i = IFIX(temp);
    temp = end_1;
    if (temp);
    else
	temp = string_is_simple_qm ? SIMPLE_ARRAY_ANY_1_LENGTH(string_1) : 
		length(string_1);
    ab_loop_bind_ = IFIX(temp);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(find_gensym_character_in_sequence(string_is_simple_qm ? 
	    CHR(ISCHAR(string_1,i)) : CHR(ICHAR(string_1,i)),bag)))
	return VALUES_1(FIX(i));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* POSITION-OF-ASCII-CHARACTER-IN-BAG-FUNCTION */
Object position_of_ascii_character_in_bag_function(string_1,bag,start,end_1)
    Object string_1, bag, start, end_1;
{
    Object temp;
    SI_Long i, ab_loop_bind_;
    char string_is_simple_qm;

    x_note_fn_call(23,58);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    temp = start;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    i = IFIX(temp);
    temp = end_1;
    if (temp);
    else
	temp = string_is_simple_qm ? SIMPLE_ARRAY_ANY_1_LENGTH(string_1) : 
		length(string_1);
    ab_loop_bind_ = IFIX(temp);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (find_gensym_character_in_sequence(string_is_simple_qm ? 
	    CHR(ISCHAR(string_1,i)) : CHR(ICHAR(string_1,i)),bag))
	return VALUES_1(FIX(i));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* POSITION-OF-ASCII-CHARACTER-NOT-IN-BAG-FROM-END-FUNCTION */
Object position_of_ascii_character_not_in_bag_from_end_function(string_1,
	    bag,start,end_1)
    Object string_1, bag, start, end_1;
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    char string_is_simple_qm;

    x_note_fn_call(23,59);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    temp = end_1;
    if (temp);
    else
	temp = string_is_simple_qm ? SIMPLE_ARRAY_ANY_1_LENGTH(string_1) : 
		length(string_1);
    gensymed_symbol = IFIX(temp);
    gensymed_symbol_1 = (SI_Long)1L;
    i = gensymed_symbol - gensymed_symbol_1;
    temp = start;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    ab_loop_bind_ = IFIX(temp);
  next_loop:
    if (i < ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(find_gensym_character_in_sequence(string_is_simple_qm ? 
	    CHR(ISCHAR(string_1,i)) : CHR(ICHAR(string_1,i)),bag)))
	return VALUES_1(FIX(i));
    i = i - (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PARSE-ASCII-TEXT-LINE-GIVEN-GROUPING-BAG */
Object parse_ascii_text_line_given_grouping_bag(ascii_text_line,
	    delimiter_bag,trim_bag,start,end_1,grouping_bag)
    Object ascii_text_line, delimiter_bag, trim_bag, start, end_1;
    Object grouping_bag;
{
    Object temp, grouping_start_char, grouping_end_char, substart, i0_qm;
    Object in_group_p, i, peek_p, j, k, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, this_char, ab_loop_it_, group_start_p;
    SI_Long start_1, end_2, i2, ab_loop_bind_;

    x_note_fn_call(23,60);
    temp = start;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start_1 = IFIX(temp);
    temp = end_1;
    if (temp);
    else
	temp = length(ascii_text_line);
    end_2 = IFIX(temp);
    grouping_start_char = CHAR(grouping_bag,FIX((SI_Long)0L));
    grouping_end_char = CHAR(grouping_bag,FIX((SI_Long)1L));
    substart = FIX(start_1);
    i0_qm = Nil;
    in_group_p = Nil;
    i = Nil;
    peek_p = Nil;
    j = Nil;
    k = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !(IFIX(substart) < end_2))
	goto end_loop;
    i0_qm = 
	    position_of_ascii_character_not_in_bag_function(ascii_text_line,
	    trim_bag,substart,FIX(end_2));
    if ( !TRUEP(i0_qm))
	goto end_loop;
    temp = CHAR(ascii_text_line,i0_qm);
    in_group_p = EQ(temp,grouping_start_char) ? T : Nil;
    i = in_group_p ? FIXNUM_ADD1(i0_qm) : i0_qm;
    peek_p = Nil;
    if (in_group_p) {
	i2 = IFIX(i);
	ab_loop_bind_ = end_2;
	this_char = Nil;
	ab_loop_it_ = Nil;
      next_loop_1:
	if (i2 >= ab_loop_bind_)
	    goto end_loop_1;
	this_char = CHR(ICHAR(ascii_text_line,i2));
	ab_loop_it_ = EQ(this_char,grouping_end_char) ? FIX(i2) : Qnil;
	if (ab_loop_it_) {
	    j = ab_loop_it_;
	    goto end_3;
	}
	i2 = i2 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	j = FIX(end_2);
	goto end_3;
	j = Qnil;
      end_3:;
    }
    else {
	i2 = IFIX(i);
	ab_loop_bind_ = end_2;
	this_char = Nil;
	group_start_p = Nil;
	ab_loop_it_ = Nil;
      next_loop_2:
	if (i2 >= ab_loop_bind_)
	    goto end_loop_2;
	this_char = CHR(ICHAR(ascii_text_line,i2));
	group_start_p = EQ(this_char,grouping_start_char) ? T : Nil;
	if (group_start_p)
	    peek_p = T;
	ab_loop_it_ = group_start_p || 
		find_gensym_character_in_sequence(this_char,delimiter_bag) 
		? FIX(i2) : Qnil;
	if (ab_loop_it_) {
	    j = ab_loop_it_;
	    goto end_4;
	}
	i2 = i2 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	j = Qnil;
      end_4:;
    }
    k = in_group_p ? Nil : 
	    position_of_ascii_character_not_in_bag_from_end_function(ascii_text_line,
	    trim_bag,i,j);
    ab_loopvar__2 = gensym_cons_1(gensym_string_substring(ascii_text_line,
	    i,k ? FIXNUM_ADD1(k) : j),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    if ( !TRUEP(j))
	goto end_loop;
    substart = peek_p ? j : FIXNUM_ADD1(j);
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_5;
    temp = Qnil;
  end_5:;
    return VALUES_1(temp);
}

/* PARSE-ASCII-TEXT-LINE-INTO-LIST-OF-ASCII-STRINGS-FUNCTION */
Object parse_ascii_text_line_into_list_of_ascii_strings_function(ascii_text_line,
	    delimiter_bag,trim_bag,start,end_1,grouping_bag)
    Object ascii_text_line, delimiter_bag, trim_bag, start, end_1;
    Object grouping_bag;
{
    Object temp, substart, i, j, k, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long start_1, end_2;

    x_note_fn_call(23,61);
    if (grouping_bag)
	return parse_ascii_text_line_given_grouping_bag(ascii_text_line,
		delimiter_bag,trim_bag,start,end_1,grouping_bag);
    else {
	temp = start;
	if (temp);
	else
	    temp = FIX((SI_Long)0L);
	start_1 = IFIX(temp);
	temp = end_1;
	if (temp);
	else
	    temp = length(ascii_text_line);
	end_2 = IFIX(temp);
	substart = FIX(start_1);
	i = Nil;
	j = Nil;
	k = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !(IFIX(substart) <= end_2))
	    goto end_loop;
	temp = 
		position_of_ascii_character_not_in_bag_function(ascii_text_line,
		trim_bag,substart,FIX(end_2));
	if (temp);
	else
	    temp = FIX(end_2);
	i = temp;
	j = position_of_ascii_character_in_bag_function(ascii_text_line,
		delimiter_bag,i,FIX(end_2));
	k = 
		position_of_ascii_character_not_in_bag_from_end_function(ascii_text_line,
		trim_bag,i,j);
	ab_loopvar__2 = 
		gensym_cons_1(gensym_string_substring(ascii_text_line,i,k ?
		 FIXNUM_ADD1(k) : j),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	if ( !TRUEP(j))
	    goto end_loop;
	substart = FIXNUM_ADD1(j);
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* PARSE-COLON-DELIMITED-ASCII-TEXT-LINE-INTO-LIST-OF-ASCII-STRINGS */
Object parse_colon_delimited_ascii_text_line_into_list_of_ascii_strings(ascii_text_line)
    Object ascii_text_line;
{
    x_note_fn_call(23,62);
    return parse_ascii_text_line_into_list_of_ascii_strings_function(ascii_text_line,
	    list_constant,list_constant_1,Nil,Nil,Nil);
}

/* PARSE-SPACE-DELIMITED-ASCII-TEXT-LINE-INTO-LIST-OF-ASCII-STRINGS */
Object parse_space_delimited_ascii_text_line_into_list_of_ascii_strings(ascii_text_line)
    Object ascii_text_line;
{
    x_note_fn_call(23,63);
    return parse_ascii_text_line_into_list_of_ascii_strings_function(ascii_text_line,
	    list_constant_1,list_constant_1,Nil,Nil,Nil);
}

static Object Qwide_string;        /* wide-string */

/* TWRITE-CHARACTER */
Object twrite_character(simple_character)
    Object simple_character;
{
    Object thing, temp, schar_arg_2, schar_new_value;

    x_note_fn_call(23,64);
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = simple_character;
	return twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) :
		 thing);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = simple_character;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
	return VALUES_1(Fill_pointer_for_current_gensym_string);
    }
}

Object Extend_current_gensym_string_error_message = UNBOUND;

/* EXTEND-CURRENT-GENSYM-STRING */
Object extend_current_gensym_string varargs_1(int, n)
{
    Object minimum_new_total_length_qm, temp, minimum_new_total_length, temp_1;
    Object new_total_length, new_gensym_string;
    SI_Long temp_2, i, ab_loop_bind_;
    char schar_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(23,65);
    INIT_ARGS_nonrelocating();
    minimum_new_total_length_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = minimum_new_total_length_qm;
    if (temp);
    else
	temp = FIXNUM_ADD1(Total_length_of_current_gensym_string);
    NUM_GT(temp,Maximum_length_for_user_gensym_strings);
    minimum_new_total_length = minimum_new_total_length_qm;
    if (minimum_new_total_length);
    else
	minimum_new_total_length = FIX((SI_Long)0L);
    temp_1 = Maximum_gensym_string_length;
    temp_2 = IFIX(Total_length_of_current_gensym_string) * (SI_Long)3L / 
	    (SI_Long)2L;
    temp = FIX(temp_2);
    temp = FIXNUM_MAX(temp,minimum_new_total_length);
    new_total_length = FIXNUM_MIN(temp_1,temp);
    new_gensym_string = obtain_simple_gensym_string(new_total_length);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Fill_pointer_for_current_gensym_string);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    schar_new_value = ISCHAR(Current_gensym_string,i);
    SET_ISCHAR(new_gensym_string,i,schar_new_value);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    reclaim_simple_gensym_string(Current_gensym_string);
    Current_gensym_string = new_gensym_string;
    Total_length_of_current_gensym_string = new_total_length;
    return VALUES_1(Total_length_of_current_gensym_string);
}

/* TWRITE-N-SPACES */
Object twrite_n_spaces(spaces_count)
    Object spaces_count;
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long ab_loop_repeat_, thing;

    x_note_fn_call(23,66);
    ab_loop_repeat_ = IFIX(spaces_count);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = (SI_Long)32L;
	twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = (SI_Long)32L;
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

/* TWRITE-SPACES-IF-NECESSARY */
Object twrite_spaces_if_necessary(minimum_width,actual_width)
    Object minimum_width, actual_width;
{
    x_note_fn_call(23,67);
    if (FIXNUM_GT(minimum_width,actual_width))
	return twrite_n_spaces(FIXNUM_MINUS(minimum_width,actual_width));
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Calling_tformat_for_give_warning_qm, Qcalling_tformat_for_give_warning_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Write_symbols_in_lower_case_qm, Qwrite_symbols_in_lower_case_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Write_strings_parsably_qm, Qwrite_strings_parsably_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Block_class_description, Qblock_class_description);

static Object string_constant;     /* "-9223372036854775808" */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* TWRITE */
Object twrite(x)
    Object x;
{
    Object temp, thing, temp_1, schar_arg_2, schar_new_value;
    Object write_strings_parsably_qm, x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    SI_int64 positive_long;
    char thing_1;
    char temp_2;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(23,68);
    if (SYMBOLP(x))
	temp = twrite_symbol(2,x, !TRUEP(Write_symbols_in_lower_case_qm) ? 
		T : Nil);
    else if (FIXNUMP(x))
	temp = twrite_fixnum(x);
    else if (text_string_p(x) || STRINGP(x))
	temp = twrite_general_string(x);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
	temp = write_floating_point_number_simple_c_format(1,
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,(SI_Long)0L)));
    else if (FLOATP(x))
	temp = write_floating_point_number_simple_c_format(1,x);
    else if (CHARACTERP(x)) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = x;
	    temp = twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = x;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	    temp = Fill_pointer_for_current_gensym_string;
	}
    }
    else if (INLINE_LONG_P(x) != (SI_Long)0L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (NUM_EQ(x,Most_negative_int64)) {
		write_strings_parsably_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
			0);
		  temp = twrite_general_string(string_constant);
		POP_SPECIAL();
	    }
	    else {
		temp = FIX((SI_Long)0L);
		if (NUM_LT(x,temp)) {
		    if (EQ(Current_twriting_output_type,Qwide_string))
			twrite_wide_character(FIX((SI_Long)45L));
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_1 = Current_gensym_string;
			schar_arg_2 = Fill_pointer_for_current_gensym_string;
			temp = CHR('-');
			SET_SCHAR(temp_1,schar_arg_2,temp);
			temp_1 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_1;
		    }
		    temp = negate(x);
		    positive_long = INTEGER_TO_INT64(temp);
		}
		else
		    positive_long = INTEGER_TO_INT64(x);
		temp = 
			twrite_positive_bignum_in_radix(INT64_TO_INTEGER(positive_long),
			FIX((SI_Long)10L));
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else if (INTEGERP(x)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = FIX((SI_Long)0L);
	    if (NUM_LT(x,temp)) {
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing_1 = '-';
		    twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_1 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing_1 = '-';
		    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		    temp_1 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_1;
		}
		temp = twrite_positive_bignum(negate(x));
	    }
	    else
		temp = twrite_positive_bignum(x);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else if (Calling_tformat_for_give_warning_qm) {
	if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
		(SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(x,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    sub_class_bit_vector = ISVREF(ISVREF(x,(SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		temp_2 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp = temp_2 ? twrite(get_or_make_up_designation_for_block(x)) : Nil;
    }
    else
	temp = write_random_s_expression(x);
    return VALUES_1(temp);
}

/* TWRITE-PARSABLY */
Object twrite_parsably(x)
    Object x;
{
    Object write_symbols_parsably_qm, write_strings_parsably_qm, temp;
    Declare_special(2);

    x_note_fn_call(23,69);
    write_symbols_parsably_qm = T;
    write_strings_parsably_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
	      0);
	temp = twrite(x);
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* TWRITE-LINE-BREAK */
Object twrite_line_break()
{
    x_note_fn_call(23,70);
    return twrite_line_separator();
}

/* TPRIN */
Object tprin(x,enclose_strings_in_quotes_qm)
    Object x, enclose_strings_in_quotes_qm;
{
    x_note_fn_call(23,71);
    if (enclose_strings_in_quotes_qm && (text_string_p(x) || STRINGP(x)))
	return twrite_parsably(x);
    else
	return twrite(x);
}

static Object list_constant_2;     /* # */

/* BEGINS-WITH-VOWEL? */
Object begins_with_vowel_qm(symbol_or_string)
    Object symbol_or_string;
{
    x_note_fn_call(23,72);
    if (CONSP(symbol_or_string))
	symbol_or_string = CAR(symbol_or_string);
    return memq_function(CHAR(SYMBOLP(symbol_or_string) ? 
	    SYMBOL_NAME(symbol_or_string) : symbol_or_string,
	    FIX((SI_Long)0L)),list_constant_2);
}

static Object string_constant_1;   /* "an " */

static Object string_constant_2;   /* "a " */

/* SUPPLY-A-OR-AN */
Object supply_a_or_an(symbol_or_string)
    Object symbol_or_string;
{
    x_note_fn_call(23,73);
    if (CONSP(symbol_or_string))
	symbol_or_string = CAR(symbol_or_string);
    if (begins_with_vowel_qm(symbol_or_string))
	return VALUES_1(string_constant_1);
    else
	return VALUES_1(string_constant_2);
}

DEFINE_VARIABLE_WITH_SYMBOL(Note_blocks_in_tformat, Qnote_blocks_in_tformat);

DEFINE_VARIABLE_WITH_SYMBOL(Tformat_fresh_line_is_newline_p, Qtformat_fresh_line_is_newline_p);

DEFINE_VARIABLE_WITH_SYMBOL(In_text_for_item_or_value_p, Qin_text_for_item_or_value_p);

static Object string_constant_3;   /* ";" */

static Object string_constant_4;   /* "," */

static Object string_constant_5;   /* " " */

static Object string_constant_6;   /* "or" */

static Object string_constant_7;   /* "and" */

static Object list_constant_3;     /* # */

/* TFORMAT */
Object tformat varargs_1(int, n)
{
    Object control_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg_index;
    Object write_symbols_in_lower_case_qm, directive_colon_p;
    Object directive_atsign_p, i, string_length, character_1, thing_1, temp_1;
    Object schar_arg_2, schar_new_value, temp_2, arg, temp_3, temp_4;
    SI_Long temp, thing_2, i_1, ab_loop_bind_;
    char gensym_string_p, gensym_string_is_simple_qm;
    char thing;
    char temp_5;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(23,74);
    INIT_ARGS_nonrelocating();
    control_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    arg_index = FIX((SI_Long)0L);
    write_symbols_in_lower_case_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    0);
      directive_colon_p = Nil;
      directive_atsign_p = Nil;
      i = FIX((SI_Long)0L);
      gensym_string_p = STRINGP(control_string);
      gensym_string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(control_string);
      string_length = gensym_string_p ? (gensym_string_is_simple_qm ? 
	      SIMPLE_ARRAY_ANY_1_LENGTH(control_string) : 
	      length(control_string)) : lengthw(control_string);
      character_1 = Nil;
    next_loop:
      if (FIXNUM_EQ(i,string_length))
	  goto end_loop;
      if (gensym_string_p) {
	  thing = gensym_string_is_simple_qm ? 
		  CHARACTER_TO_CHAR(SCHAR(control_string,i)) : 
		  CHARACTER_TO_CHAR(CHAR(control_string,i));
	  character_1 = CHARACTERP(CHAR_TO_CHARACTER(thing)) ? 
		  CHAR_CODE(CHAR_TO_CHARACTER(thing)) : 
		  CHAR_TO_CHARACTER(thing);
      }
      else
	  character_1 = charw_function(control_string,i);
      i = FIXNUM_ADD1(i);
      temp = IFIX(character_1);
      if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L)) {
	  if (EQ(Current_twriting_output_type,Qwide_string)) {
	      thing_1 = character_1;
	      twrite_wide_character(CHARACTERP(thing_1) ? 
		      CHAR_CODE(thing_1) : thing_1);
	  }
	  else {
	      if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		      Total_length_of_current_gensym_string))
		  extend_current_gensym_string(0);
	      temp_1 = Current_gensym_string;
	      schar_arg_2 = Fill_pointer_for_current_gensym_string;
	      thing_1 = character_1;
	      schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		      CHAR_CODE(thing_1) : thing_1);
	      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	      temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	      Fill_pointer_for_current_gensym_string = temp_1;
	  }
      }
      else
	  switch ((char)temp) {
	    case 10:
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing_2 = (SI_Long)8232L;
		  twrite_wide_character(CHARACTERP(FIX(thing_2)) ? 
			  CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp_1 = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing_2 = (SI_Long)8232L;
		  schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_2)) ? 
			  CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
		  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		  temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp_1;
	      }
	      break;
	    case 126:
	      if (FIXNUM_EQ(i,string_length))
		  goto end_loop;
	      directive_colon_p = Nil;
	      directive_atsign_p = Nil;
	    next_loop_1:
	      if (gensym_string_p) {
		  thing = gensym_string_is_simple_qm ? 
			  CHARACTER_TO_CHAR(SCHAR(control_string,i)) : 
			  CHARACTER_TO_CHAR(CHAR(control_string,i));
		  character_1 = CHARACTERP(CHAR_TO_CHARACTER(thing)) ? 
			  CHAR_CODE(CHAR_TO_CHARACTER(thing)) : 
			  CHAR_TO_CHARACTER(thing);
	      }
	      else
		  character_1 = charw_function(control_string,i);
	      i = FIXNUM_ADD1(i);
	      temp = IFIX(character_1);
	      if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L)) {
		  temp_2 = character_1;
		  goto end_1;
	      }
	      else
		  switch ((char)temp) {
		    case 58:
		      directive_colon_p = T;
		      break;
		    case 64:
		      directive_atsign_p = T;
		      break;
		    default:
		      temp_2 = character_1;
		      goto end_1;
		      break;
		  }
	      goto next_loop_1;
	    end_loop_1:
	      temp_2 = Qnil;
	    end_1:
	      if (! !(FIXNUMP(temp_2) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_2) && FIXNUM_LE(temp_2,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_2)) {
		    case 65:
		    case 97:
		    case 83:
		    case 115:
		    case 67:
		    case 99:
		    case 68:
		    case 100:
		    case 66:
		    case 98:
		    case 79:
		    case 111:
		    case 88:
		    case 120:
		    case 70:
		    case 102:
		    case 78:
		    case 110:
		    case 76:
		    case 108:
		      arg_index = FIXNUM_ADD1(arg_index);
		      temp_2 = arg_index;
		      if ( !(FIXNUMP(temp_2) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_2) && 
			      FIXNUM_LE(temp_2,FIX((SI_Long)127L))))
			  arg = Nil;
		      else
			  switch (INTEGER_TO_CHAR(temp_2)) {
			    case 1:
			      arg = arg1;
			      break;
			    case 2:
			      arg = arg2;
			      break;
			    case 3:
			      arg = arg3;
			      break;
			    case 4:
			      arg = arg4;
			      break;
			    case 5:
			      arg = arg5;
			      break;
			    case 6:
			      arg = arg6;
			      break;
			    case 7:
			      arg = arg7;
			      break;
			    case 8:
			      arg = arg8;
			      break;
			    case 9:
			      arg = arg9;
			      break;
			    default:
			      arg = Nil;
			      break;
			  }
		      temp_2 = character_1;
		      if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp_2) && 
			      FIXNUM_LE(temp_2,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_2)) {
			    case 65:
			    case 97:
			      twrite(arg);
			      break;
			    case 83:
			    case 115:
			      twrite_parsably(arg);
			      break;
			    case 67:
			    case 99:
			      if (EQ(Current_twriting_output_type,
				      Qwide_string)) {
				  thing_1 = arg;
				  twrite_wide_character(CHARACTERP(thing_1) 
					  ? CHAR_CODE(thing_1) : thing_1);
			      }
			      else {
				  if ( 
					  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					  Total_length_of_current_gensym_string))
				      extend_current_gensym_string(0);
				  temp_1 = Current_gensym_string;
				  schar_arg_2 = 
					  Fill_pointer_for_current_gensym_string;
				  thing_1 = arg;
				  schar_new_value = 
					  CODE_CHAR(CHARACTERP(thing_1) ? 
					  CHAR_CODE(thing_1) : thing_1);
				  SET_SCHAR(temp_1,schar_arg_2,
					  schar_new_value);
				  temp_1 = 
					  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				  Fill_pointer_for_current_gensym_string = 
					  temp_1;
			      }
			      break;
			    case 68:
			    case 100:
			      twrite(arg);
			      break;
			    case 66:
			    case 98:
			    case 79:
			    case 111:
			    case 88:
			    case 120:
			      temp_2 = character_1;
			      if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_2) 
				      && FIXNUM_LE(temp_2,FIX((SI_Long)127L))))
				  temp_2 = FIX((SI_Long)16L);
			      else
				  switch (INTEGER_TO_CHAR(temp_2)) {
				    case 66:
				    case 98:
				      temp_2 = FIX((SI_Long)2L);
				      break;
				    case 79:
				    case 111:
				      temp_2 = FIX((SI_Long)8L);
				      break;
				    default:
				      temp_2 = FIX((SI_Long)16L);
				      break;
				  }
			      twrite_positive_fixnum_in_radix(arg,temp_2);
			      break;
			    case 70:
			    case 102:
			      twrite(arg);
			      break;
			    case 78:
			    case 110:
			      if (gensym_string_p) {
				  thing = gensym_string_is_simple_qm ? 
					  CHARACTER_TO_CHAR(SCHAR(control_string,
					  i)) : 
					  CHARACTER_TO_CHAR(CHAR(control_string,
					  i));
				  character_1 = 
					  CHARACTERP(CHAR_TO_CHARACTER(thing)) 
					  ? 
					  CHAR_CODE(CHAR_TO_CHARACTER(thing)) 
					  : CHAR_TO_CHARACTER(thing);
			      }
			      else
				  character_1 = 
					  charw_function(control_string,i);
			      i = FIXNUM_ADD1(i);
			      temp = IFIX(character_1);
			      if (! !((SI_Long)-128L <= temp && temp <= 
				      (SI_Long)127L))
				  switch ((char)temp) {
				    case 70:
				    case 102:
				      if (In_text_for_item_or_value_p)
					  twrite_designation_for_item(arg);
				      else if (framep_function(arg) && 
					      block_p_function(arg)) {
					  twrite(get_or_make_up_designation_for_block(arg));
					  if (framep_function(arg) && 
						  block_p_function(arg) && 
						  Note_blocks_in_tformat)
					      inline_funcall_1(Note_blocks_in_tformat,
						      arg);
				      }
				      else
					  twrite(arg);
				      break;
				    case 65:
				    case 97:
				      write_block_or_evaluation_value(1,arg);
				      break;
				    case 78:
				    case 110:
				      write_name_denotation(arg);
				      break;
				    case 68:
				    case 100:
				      print_designation(arg);
				      break;
				    case 69:
				    case 101:
				      write_expression(arg);
				      break;
				    case 84:
				    case 116:
				      write_type_specification(arg);
				      break;
				    case 86:
				    case 118:
				      write_evaluation_value(1,arg);
				      break;
				    case 80:
				    case 112:
				      write_gensym_pathname(arg);
				      break;
				    case 87:
				    case 119:
				      write_error_text(arg);
				      break;
				    case 67:
				    case 99:
				      arg_index = FIXNUM_ADD1(arg_index);
				      temp_2 = arg_index;
				      if ( !(FIXNUMP(temp_2) && 
					      FIXNUM_LE(FIX((SI_Long)-128L),
					      temp_2) && FIXNUM_LE(temp_2,
					      FIX((SI_Long)127L))))
					  temp_2 = Nil;
				      else
					  switch (INTEGER_TO_CHAR(temp_2)) {
					    case 1:
					      temp_2 = arg1;
					      break;
					    case 2:
					      temp_2 = arg2;
					      break;
					    case 3:
					      temp_2 = arg3;
					      break;
					    case 4:
					      temp_2 = arg4;
					      break;
					    case 5:
					      temp_2 = arg5;
					      break;
					    case 6:
					      temp_2 = arg6;
					      break;
					    case 7:
					      temp_2 = arg7;
					      break;
					    case 8:
					      temp_2 = arg8;
					      break;
					    case 9:
					      temp_2 = arg9;
					      break;
					    default:
					      temp_2 = Nil;
					      break;
					  }
				      print_constant(2,arg,temp_2);
				      break;
				    case 83:
				    case 115:
				      arg_index = FIXNUM_ADD1(arg_index);
				      temp_2 = arg_index;
				      if ( !(FIXNUMP(temp_2) && 
					      FIXNUM_LE(FIX((SI_Long)-128L),
					      temp_2) && FIXNUM_LE(temp_2,
					      FIX((SI_Long)127L))))
					  temp_2 = Nil;
				      else
					  switch (INTEGER_TO_CHAR(temp_2)) {
					    case 1:
					      temp_2 = arg1;
					      break;
					    case 2:
					      temp_2 = arg2;
					      break;
					    case 3:
					      temp_2 = arg3;
					      break;
					    case 4:
					      temp_2 = arg4;
					      break;
					    case 5:
					      temp_2 = arg5;
					      break;
					    case 6:
					      temp_2 = arg6;
					      break;
					    case 7:
					      temp_2 = arg7;
					      break;
					    case 8:
					      temp_2 = arg8;
					      break;
					    case 9:
					      temp_2 = arg9;
					      break;
					    default:
					      temp_2 = Nil;
					      break;
					  }
				      write_name_denotation_for_slot(arg,
					      temp_2);
				      break;
				    case 81:
				    case 113:
				      arg_index = FIXNUM_ADD1(arg_index);
				      temp_2 = arg_index;
				      if ( !(FIXNUMP(temp_2) && 
					      FIXNUM_LE(FIX((SI_Long)-128L),
					      temp_2) && FIXNUM_LE(temp_2,
					      FIX((SI_Long)127L))))
					  temp_2 = Nil;
				      else
					  switch (INTEGER_TO_CHAR(temp_2)) {
					    case 1:
					      temp_2 = arg1;
					      break;
					    case 2:
					      temp_2 = arg2;
					      break;
					    case 3:
					      temp_2 = arg3;
					      break;
					    case 4:
					      temp_2 = arg4;
					      break;
					    case 5:
					      temp_2 = arg5;
					      break;
					    case 6:
					      temp_2 = arg6;
					      break;
					    case 7:
					      temp_2 = arg7;
					      break;
					    case 8:
					      temp_2 = arg8;
					      break;
					    case 9:
					      temp_2 = arg9;
					      break;
					    default:
					      temp_2 = Nil;
					      break;
					  }
				      write_name_denotation_components(arg,
					      temp_2);
				      break;
				    case 82:
				    case 114:
				      if (framep_function(arg) && 
					      block_p_function(arg) && 
					      Note_blocks_in_tformat)
					  inline_funcall_1(Note_blocks_in_tformat,
						  arg);
				      arg_index = FIXNUM_ADD1(arg_index);
				      temp_2 = arg_index;
				      if ( !(FIXNUMP(temp_2) && 
					      FIXNUM_LE(FIX((SI_Long)-128L),
					      temp_2) && FIXNUM_LE(temp_2,
					      FIX((SI_Long)127L))))
					  temp_2 = Nil;
				      else
					  switch (INTEGER_TO_CHAR(temp_2)) {
					    case 1:
					      temp_2 = arg1;
					      break;
					    case 2:
					      temp_2 = arg2;
					      break;
					    case 3:
					      temp_2 = arg3;
					      break;
					    case 4:
					      temp_2 = arg4;
					      break;
					    case 5:
					      temp_2 = arg5;
					      break;
					    case 6:
					      temp_2 = arg6;
					      break;
					    case 7:
					      temp_2 = arg7;
					      break;
					    case 8:
					      temp_2 = arg8;
					      break;
					    case 9:
					      temp_2 = arg9;
					      break;
					    default:
					      temp_2 = Nil;
					      break;
					  }
				      twrite(temp_2);
				      break;
				    case 66:
				    case 98:
				      arg_index = FIXNUM_ADD1(arg_index);
				      temp_2 = arg_index;
				      if ( !(FIXNUMP(temp_2) && 
					      FIXNUM_LE(FIX((SI_Long)-128L),
					      temp_2) && FIXNUM_LE(temp_2,
					      FIX((SI_Long)127L))))
					  temp_2 = Nil;
				      else
					  switch (INTEGER_TO_CHAR(temp_2)) {
					    case 1:
					      temp_2 = arg1;
					      break;
					    case 2:
					      temp_2 = arg2;
					      break;
					    case 3:
					      temp_2 = arg3;
					      break;
					    case 4:
					      temp_2 = arg4;
					      break;
					    case 5:
					      temp_2 = arg5;
					      break;
					    case 6:
					      temp_2 = arg6;
					      break;
					    case 7:
					      temp_2 = arg7;
					      break;
					    case 8:
					      temp_2 = arg8;
					      break;
					    case 9:
					      temp_2 = arg9;
					      break;
					    default:
					      temp_2 = Nil;
					      break;
					  }
				      denote_component_of_block(3,T,arg,
					      temp_2);
				      break;
				    default:
				      break;
				  }
			      break;
			    case 76:
			    case 108:
			      temp_2 = LISTP(arg) ? arg : Nil;
			      if (gensym_string_p) {
				  thing = gensym_string_is_simple_qm ? 
					  CHARACTER_TO_CHAR(SCHAR(control_string,
					  i)) : 
					  CHARACTER_TO_CHAR(CHAR(control_string,
					  i));
				  character_1 = 
					  CHARACTERP(CHAR_TO_CHARACTER(thing)) 
					  ? 
					  CHAR_CODE(CHAR_TO_CHARACTER(thing)) 
					  : CHAR_TO_CHARACTER(thing);
			      }
			      else
				  character_1 = 
					  charw_function(control_string,i);
			      i = FIXNUM_ADD1(i);
			      temp = IFIX(character_1);
			      if ( !((SI_Long)-128L <= temp && temp <= 
				      (SI_Long)127L))
				  temp_3 = Nil;
			      else
				  switch ((char)temp) {
				    case 59:
				      temp_3 = string_constant_3;
				      break;
				    case 44:
				      temp_3 = string_constant_4;
				      break;
				    case 32:
				      temp_3 = string_constant_5;
				      break;
				    default:
				      temp_3 = Nil;
				      break;
				  }
			      if (gensym_string_p) {
				  thing = gensym_string_is_simple_qm ? 
					  CHARACTER_TO_CHAR(SCHAR(control_string,
					  i)) : 
					  CHARACTER_TO_CHAR(CHAR(control_string,
					  i));
				  character_1 = 
					  CHARACTERP(CHAR_TO_CHARACTER(thing)) 
					  ? 
					  CHAR_CODE(CHAR_TO_CHARACTER(thing)) 
					  : CHAR_TO_CHARACTER(thing);
			      }
			      else
				  character_1 = 
					  charw_function(control_string,i);
			      i = FIXNUM_ADD1(i);
			      temp = IFIX(character_1);
			      if ( !((SI_Long)-128L <= temp && temp <= 
				      (SI_Long)127L))
				  temp_4 = Nil;
			      else
				  switch ((char)temp) {
				    case 124:
				      temp_4 = string_constant_6;
				      break;
				    case 38:
				      temp_4 = string_constant_7;
				      break;
				    case 45:
				      temp_4 = Nil;
				      break;
				    default:
				      temp_4 = Nil;
				      break;
				  }
			      write_symbol_list(4,temp_2,temp_3,temp_4, 
				      !LISTP(arg) ? arg : Nil);
			      break;
			    default:
			      break;
			  }
		      break;
		    case 40:
		      Write_symbols_in_lower_case_qm = T;
		      break;
		    case 41:
		      Write_symbols_in_lower_case_qm = Nil;
		      break;
		    case 37:
		      twrite_line_separator();
		      break;
		    case 38:
		      if (Tformat_fresh_line_is_newline_p)
			  twrite_line_separator();
		      else if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing_2 = (SI_Long)32L;
			  twrite_wide_character(CHARACTERP(FIX(thing_2)) ? 
				  CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp_1 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing_2 = (SI_Long)32L;
			  schar_new_value = 
				  CODE_CHAR(CHARACTERP(FIX(thing_2)) ? 
				  CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
			  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			  temp_1 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_1;
		      }
		      break;
		    case 10:
		    next_loop_2:
		      if (FIXNUM_EQ(i,string_length))
			  goto end_loop_2;
		      if (gensym_string_p) {
			  thing = gensym_string_is_simple_qm ? 
				  CHARACTER_TO_CHAR(SCHAR(control_string,
				  i)) : 
				  CHARACTER_TO_CHAR(CHAR(control_string,i));
			  character_1 = 
				  CHARACTERP(CHAR_TO_CHARACTER(thing)) ? 
				  CHAR_CODE(CHAR_TO_CHARACTER(thing)) : 
				  CHAR_TO_CHARACTER(thing);
		      }
		      else
			  character_1 = charw_function(control_string,i);
		      i = FIXNUM_ADD1(i);
		      if ( !TRUEP(wide_character_member(character_1,
			      list_constant_3)))
			  goto end_loop_2;
		      goto next_loop_2;
		    end_loop_2:
		      i = FIXNUM_SUB1(i);
		      break;
		    case 91:
		      arg_index = FIXNUM_ADD1(arg_index);
		      temp_2 = arg_index;
		      if ( !(FIXNUMP(temp_2) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_2) && 
			      FIXNUM_LE(temp_2,FIX((SI_Long)127L))))
			  arg = Nil;
		      else
			  switch (INTEGER_TO_CHAR(temp_2)) {
			    case 1:
			      arg = arg1;
			      break;
			    case 2:
			      arg = arg2;
			      break;
			    case 3:
			      arg = arg3;
			      break;
			    case 4:
			      arg = arg4;
			      break;
			    case 5:
			      arg = arg5;
			      break;
			    case 6:
			      arg = arg6;
			      break;
			    case 7:
			      arg = arg7;
			      break;
			    case 8:
			      arg = arg8;
			      break;
			    case 9:
			      arg = arg9;
			      break;
			    default:
			      arg = Nil;
			      break;
			  }
		      if (directive_atsign_p) {
			  if (arg)
			      arg_index = FIXNUM_SUB1(arg_index);
			  else {
			    next_loop_3:
			      if (FIXNUM_EQ(i,string_length))
				  goto end_loop_3;
			      if (gensym_string_p) {
				  thing = gensym_string_is_simple_qm ? 
					  CHARACTER_TO_CHAR(SCHAR(control_string,
					  i)) : 
					  CHARACTER_TO_CHAR(CHAR(control_string,
					  i));
				  character_1 = 
					  CHARACTERP(CHAR_TO_CHARACTER(thing)) 
					  ? 
					  CHAR_CODE(CHAR_TO_CHARACTER(thing)) 
					  : CHAR_TO_CHARACTER(thing);
			      }
			      else
				  character_1 = 
					  charw_function(control_string,i);
			      i = FIXNUM_ADD1(i);
			      temp = IFIX(character_1);
			      if (! !((SI_Long)-128L <= temp && temp <= 
				      (SI_Long)127L))
				  switch ((char)temp) {
				    case 126:
				      if (FIXNUM_EQ(i,string_length))
					  goto end_2;
				      directive_colon_p = Nil;
				      directive_atsign_p = Nil;
				    next_loop_4:
				      if (gensym_string_p) {
					  thing = 
						  gensym_string_is_simple_qm 
						  ? 
						  CHARACTER_TO_CHAR(SCHAR(control_string,
						  i)) : 
						  CHARACTER_TO_CHAR(CHAR(control_string,
						  i));
					  character_1 = 
						  CHARACTERP(CHAR_TO_CHARACTER(thing)) 
						  ? 
						  CHAR_CODE(CHAR_TO_CHARACTER(thing)) 
						  : CHAR_TO_CHARACTER(thing);
				      }
				      else
					  character_1 = 
						  charw_function(control_string,
						  i);
				      i = FIXNUM_ADD1(i);
				      temp = IFIX(character_1);
				      if ( !((SI_Long)-128L <= temp && 
					      temp <= (SI_Long)127L)) {
					  temp_2 = character_1;
					  goto end_3;
				      }
				      else
					  switch ((char)temp) {
					    case 58:
					      directive_colon_p = T;
					      break;
					    case 64:
					      directive_atsign_p = T;
					      break;
					    default:
					      temp_2 = character_1;
					      goto end_3;
					      break;
					  }
				      goto next_loop_4;
				    end_loop_4:
				      temp_2 = Qnil;
				    end_3:
				      if (! !(FIXNUMP(temp_2) && 
					      FIXNUM_LE(FIX((SI_Long)-128L),
					      temp_2) && FIXNUM_LE(temp_2,
					      FIX((SI_Long)127L))))
					  switch (INTEGER_TO_CHAR(temp_2)) {
					    case 93:
					      goto end_2;
					      break;
					    default:
					      break;
					  }
				      break;
				    default:
				      break;
				  }
			      goto next_loop_3;
			    end_loop_3:
			      goto end_2;
			    end_2:;
			  }
		      }
		      else if (directive_colon_p) {
			  if (arg) {
			    next_loop_5:
			      if (FIXNUM_EQ(i,string_length))
				  goto end_loop_5;
			      if (gensym_string_p) {
				  thing = gensym_string_is_simple_qm ? 
					  CHARACTER_TO_CHAR(SCHAR(control_string,
					  i)) : 
					  CHARACTER_TO_CHAR(CHAR(control_string,
					  i));
				  character_1 = 
					  CHARACTERP(CHAR_TO_CHARACTER(thing)) 
					  ? 
					  CHAR_CODE(CHAR_TO_CHARACTER(thing)) 
					  : CHAR_TO_CHARACTER(thing);
			      }
			      else
				  character_1 = 
					  charw_function(control_string,i);
			      i = FIXNUM_ADD1(i);
			      temp = IFIX(character_1);
			      if (! !((SI_Long)-128L <= temp && temp <= 
				      (SI_Long)127L))
				  switch ((char)temp) {
				    case 126:
				      if (FIXNUM_EQ(i,string_length))
					  goto end_4;
				      directive_colon_p = Nil;
				      directive_atsign_p = Nil;
				    next_loop_6:
				      if (gensym_string_p) {
					  thing = 
						  gensym_string_is_simple_qm 
						  ? 
						  CHARACTER_TO_CHAR(SCHAR(control_string,
						  i)) : 
						  CHARACTER_TO_CHAR(CHAR(control_string,
						  i));
					  character_1 = 
						  CHARACTERP(CHAR_TO_CHARACTER(thing)) 
						  ? 
						  CHAR_CODE(CHAR_TO_CHARACTER(thing)) 
						  : CHAR_TO_CHARACTER(thing);
				      }
				      else
					  character_1 = 
						  charw_function(control_string,
						  i);
				      i = FIXNUM_ADD1(i);
				      temp = IFIX(character_1);
				      if ( !((SI_Long)-128L <= temp && 
					      temp <= (SI_Long)127L)) {
					  temp_2 = character_1;
					  goto end_5;
				      }
				      else
					  switch ((char)temp) {
					    case 58:
					      directive_colon_p = T;
					      break;
					    case 64:
					      directive_atsign_p = T;
					      break;
					    default:
					      temp_2 = character_1;
					      goto end_5;
					      break;
					  }
				      goto next_loop_6;
				    end_loop_6:
				      temp_2 = Qnil;
				    end_5:
				      if (! !(FIXNUMP(temp_2) && 
					      FIXNUM_LE(FIX((SI_Long)-128L),
					      temp_2) && FIXNUM_LE(temp_2,
					      FIX((SI_Long)127L))))
					  switch (INTEGER_TO_CHAR(temp_2)) {
					    case 59:
					      goto end_4;
					      break;
					    case 93:
					      goto end_4;
					      break;
					    default:
					      break;
					  }
				      break;
				    default:
				      break;
				  }
			      goto next_loop_5;
			    end_loop_5:
			      goto end_4;
			    end_4:;
			  }
		      }
		      else {
			  i_1 = (SI_Long)0L;
			  ab_loop_bind_ = IFIX(arg);
			next_loop_7:
			  if (i_1 >= ab_loop_bind_)
			      goto end_loop_7;
			next_loop_8:
			  if (i_1 == IFIX(string_length))
			      goto end_loop_8;
			  if (gensym_string_p) {
			      thing = gensym_string_is_simple_qm ? 
				      ISCHAR(control_string,i_1) : 
				      ICHAR(control_string,i_1);
			      character_1 = 
				      CHARACTERP(CHAR_TO_CHARACTER(thing)) 
				      ? 
				      CHAR_CODE(CHAR_TO_CHARACTER(thing)) :
				       CHAR_TO_CHARACTER(thing);
			  }
			  else
			      character_1 = charw_function(control_string,
				      FIX(i_1));
			  i_1 = i_1 + (SI_Long)1L;
			  temp = IFIX(character_1);
			  if (! !((SI_Long)-128L <= temp && temp <= 
				  (SI_Long)127L))
			      switch ((char)temp) {
				case 126:
				  if (i_1 == IFIX(string_length)) {
				      temp_5 = TRUEP(Nil);
				      goto end_6;
				  }
				  directive_colon_p = Nil;
				  directive_atsign_p = Nil;
				next_loop_9:
				  if (gensym_string_p) {
				      thing = gensym_string_is_simple_qm ? 
					      ISCHAR(control_string,i_1) : 
					      ICHAR(control_string,i_1);
				      character_1 = 
					      CHARACTERP(CHAR_TO_CHARACTER(thing)) 
					      ? 
					      CHAR_CODE(CHAR_TO_CHARACTER(thing)) 
					      : CHAR_TO_CHARACTER(thing);
				  }
				  else
				      character_1 = 
					      charw_function(control_string,
					      FIX(i_1));
				  i_1 = i_1 + (SI_Long)1L;
				  temp = IFIX(character_1);
				  if ( !((SI_Long)-128L <= temp && temp <= 
					  (SI_Long)127L)) {
				      temp_2 = character_1;
				      goto end_7;
				  }
				  else
				      switch ((char)temp) {
					case 58:
					  directive_colon_p = T;
					  break;
					case 64:
					  directive_atsign_p = T;
					  break;
					default:
					  temp_2 = character_1;
					  goto end_7;
					  break;
				      }
				  goto next_loop_9;
				end_loop_9:
				  temp_2 = Qnil;
				end_7:
				  if (! !(FIXNUMP(temp_2) && 
					  FIXNUM_LE(FIX((SI_Long)-128L),
					  temp_2) && FIXNUM_LE(temp_2,
					  FIX((SI_Long)127L))))
				      switch (INTEGER_TO_CHAR(temp_2)) {
					case 59:
					  temp_5 = TRUEP(T);
					  goto end_6;
					  break;
					case 93:
					  temp_5 = TRUEP(Nil);
					  goto end_6;
					  break;
					default:
					  break;
				      }
				  break;
				default:
				  break;
			      }
			  goto next_loop_8;
			end_loop_8:
			  temp_5 = TRUEP(Nil);
			  goto end_6;
			  temp_5 = TRUEP(Qnil);
			end_6:
			  if ( !temp_5)
			      goto end_8;
			  i_1 = i_1 + (SI_Long)1L;
			  goto next_loop_7;
			end_loop_7:
			end_8:;
		      }
		      break;
		    case 59:
		    next_loop_10:
		      if (FIXNUM_EQ(i,string_length))
			  goto end_loop_10;
		      if (gensym_string_p) {
			  thing = gensym_string_is_simple_qm ? 
				  CHARACTER_TO_CHAR(SCHAR(control_string,
				  i)) : 
				  CHARACTER_TO_CHAR(CHAR(control_string,i));
			  character_1 = 
				  CHARACTERP(CHAR_TO_CHARACTER(thing)) ? 
				  CHAR_CODE(CHAR_TO_CHARACTER(thing)) : 
				  CHAR_TO_CHARACTER(thing);
		      }
		      else
			  character_1 = charw_function(control_string,i);
		      i = FIXNUM_ADD1(i);
		      temp = IFIX(character_1);
		      if (! !((SI_Long)-128L <= temp && temp <= (SI_Long)127L))
			  switch ((char)temp) {
			    case 126:
			      if (FIXNUM_EQ(i,string_length))
				  goto end_9;
			      directive_colon_p = Nil;
			      directive_atsign_p = Nil;
			    next_loop_11:
			      if (gensym_string_p) {
				  thing = gensym_string_is_simple_qm ? 
					  CHARACTER_TO_CHAR(SCHAR(control_string,
					  i)) : 
					  CHARACTER_TO_CHAR(CHAR(control_string,
					  i));
				  character_1 = 
					  CHARACTERP(CHAR_TO_CHARACTER(thing)) 
					  ? 
					  CHAR_CODE(CHAR_TO_CHARACTER(thing)) 
					  : CHAR_TO_CHARACTER(thing);
			      }
			      else
				  character_1 = 
					  charw_function(control_string,i);
			      i = FIXNUM_ADD1(i);
			      temp = IFIX(character_1);
			      if ( !((SI_Long)-128L <= temp && temp <= 
				      (SI_Long)127L)) {
				  temp_2 = character_1;
				  goto end_10;
			      }
			      else
				  switch ((char)temp) {
				    case 58:
				      directive_colon_p = T;
				      break;
				    case 64:
				      directive_atsign_p = T;
				      break;
				    default:
				      temp_2 = character_1;
				      goto end_10;
				      break;
				  }
			      goto next_loop_11;
			    end_loop_11:
			      temp_2 = Qnil;
			    end_10:
			      if (! !(FIXNUMP(temp_2) && 
				      FIXNUM_LE(FIX((SI_Long)-128L),
				      temp_2) && FIXNUM_LE(temp_2,
				      FIX((SI_Long)127L))))
				  switch (INTEGER_TO_CHAR(temp_2)) {
				    case 93:
				      goto end_9;
				      break;
				    default:
				      break;
				  }
			      break;
			    default:
			      break;
			  }
		      goto next_loop_10;
		    end_loop_10:
		      goto end_9;
		    end_9:
		      break;
		    case 93:
		      break;
		    case 126:
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing_2 = (SI_Long)126L;
			  twrite_wide_character(CHARACTERP(FIX(thing_2)) ? 
				  CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp_1 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing_2 = (SI_Long)126L;
			  schar_new_value = 
				  CODE_CHAR(CHARACTERP(FIX(thing_2)) ? 
				  CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
			  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			  temp_1 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_1;
		      }
		      break;
		    default:
		      break;
		  }
	      break;
	    default:
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing_1 = character_1;
		  twrite_wide_character(CHARACTERP(thing_1) ? 
			  CHAR_CODE(thing_1) : thing_1);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp_1 = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing_1 = character_1;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
			  CHAR_CODE(thing_1) : thing_1);
		  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		  temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp_1;
	      }
	      break;
	  }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qgensym_string;      /* gensym-string */

/* TFORMAT-GENSYM-STRING */
Object tformat_gensym_string varargs_1(int, n)
{
    Object control_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Declare_varargs_nonrelocating;
    Declare_special(4);
    Object result;

    x_note_fn_call(23,75);
    INIT_ARGS_nonrelocating();
    control_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    current_gensym_string = obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  0);
	    tformat(10,control_string,arg1,arg2,arg3,arg4,arg5,arg6,arg7,
		    arg8,arg9);
	    result = copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* WRITE-RANDOM-S-EXPRESSION */
Object write_random_s_expression(s_expression)
    Object s_expression;
{
    x_note_fn_call(23,76);
    return write_s_expression(s_expression);
}

static Object string_constant_8;   /* "(" */

static Object string_constant_9;   /* " . " */

static Object string_constant_10;  /* ")" */

/* WRITE-S-EXPRESSION */
Object write_s_expression(s_expression)
    Object s_expression;
{
    Object adjustable_gensym_string, standard_output, temp, string_1;
    Object write_strings_parsably_qm, s_expression_old_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(23,77);
    SAVE_STACK();
    if (ATOM(s_expression)) {
	if (STRINGP(s_expression) || text_string_p(s_expression) || 
		SYMBOLP(s_expression) || FLOATP(s_expression) || 
		INTEGERP(s_expression) || CHARACTERP(s_expression)) {
	    result = twrite_parsably(s_expression);
	    RESTORE_STACK();
	    return result;
	}
	else {
	    adjustable_gensym_string = obtain_adjustable_gensym_string();
	    SET_FILL_POINTER(adjustable_gensym_string,FIX((SI_Long)0L));
	    if (PUSH_AREA(Dynamic_area,0)) {
		standard_output = 
			extend_string_output_stream(adjustable_gensym_string);
		PUSH_SPECIAL_WITH_SYMBOL(Standard_output,Qstandard_output,standard_output,
			0);
		  if (PUSH_UNWIND_PROTECT(0))
		      pm_prin1(s_expression);
		  POP_UNWIND_PROTECT(0);
		  lclose(1,Standard_output);
		  CONTINUE_UNWINDING(0);
		POP_SPECIAL();
	    }
	    POP_AREA(0);
	    if ( !FIXNUM_GT(FILL_POINTER(adjustable_gensym_string),
		    Maximum_suggested_length_for_simple_gensym_strings)) {
		temp = copy_gensym_string(adjustable_gensym_string);
		reclaim_adjustable_gensym_string(adjustable_gensym_string);
		string_1 = temp;
	    }
	    else
		string_1 = adjustable_gensym_string;
	    write_strings_parsably_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		    0);
	      twrite_general_string(string_1);
	      result = reclaim_gensym_string(string_1);
	    POP_SPECIAL();
	    RESTORE_STACK();
	    return result;
	}
    }
    else {
	write_strings_parsably_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		0);
	  twrite_general_string(string_constant_8);
	POP_SPECIAL();
      next_loop:
	s_expression_old_value = s_expression;
	temp = FIRST(s_expression_old_value);
	s_expression = REST(s_expression_old_value);
	write_s_expression(temp);
	if (ATOM(s_expression))
	    goto end_loop;
	twrite_character(FIX((SI_Long)32L));
	goto next_loop;
      end_loop:
	if ( !EQ(s_expression,Nil)) {
	    write_strings_parsably_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		    0);
	      twrite_general_string(string_constant_9);
	    POP_SPECIAL();
	    write_s_expression(s_expression);
	}
	write_strings_parsably_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		0);
	  twrite_general_string(string_constant_10);
	POP_SPECIAL();
	RESTORE_STACK();
	return VALUES_1(Qnil);
    }
}

static Object string_constant_11;  /* "none" */

static Object string_constant_12;  /* "~a " */

static Object string_constant_13;  /* " ~(~a~) " */

static Object string_constant_14;  /* "~(~a~)" */

/* WRITE-SYMBOL-LIST */
Object write_symbol_list varargs_1(int, n)
{
    Object symbol_list;
    Object separator_qm, conjunction_qm, empty_list_symbol_or_string_qm;
    Object suffix_alist_qm, temp, listed_symbol, entry_for_symbol_to_suffix_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(23,78);
    INIT_ARGS_nonrelocating();
    symbol_list = REQUIRED_ARG_nonrelocating();
    separator_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    conjunction_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    empty_list_symbol_or_string_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    suffix_alist_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(symbol_list)) {
	temp = empty_list_symbol_or_string_qm;
	if (temp);
	else
	    temp = string_constant_11;
	return twrite(temp);
    }
    else {
	if ( !TRUEP(separator_qm))
	    separator_qm = string_constant_4;
	listed_symbol = symbol_list;
      next_loop:
	if ( !TRUEP(listed_symbol))
	    goto end_loop;
	twrite(CAR(listed_symbol));
	entry_for_symbol_to_suffix_qm = assq_function(CAR(listed_symbol),
		suffix_alist_qm);
	if (entry_for_symbol_to_suffix_qm)
	    twrite_general_string(CDR(entry_for_symbol_to_suffix_qm));
	if (CDR(listed_symbol)) {
	    if (CDDR(listed_symbol))
		tformat(2,string_constant_12,separator_qm);
	    else if (IFIX(length(symbol_list)) == (SI_Long)2L) {
		if (conjunction_qm) {
		    if (SYMBOLP(conjunction_qm))
			tformat(2,string_constant_13,conjunction_qm);
		    else {
			twrite_general_string(string_constant_5);
			twrite_general_string(conjunction_qm);
			twrite_general_string(string_constant_5);
		    }
		}
		else
		    tformat(2,string_constant_12,separator_qm);
	    }
	    else if (conjunction_qm) {
		tformat(2,string_constant_12,separator_qm);
		if (SYMBOLP(conjunction_qm))
		    tformat(2,string_constant_14,conjunction_qm);
		else
		    twrite_general_string(conjunction_qm);
		twrite_general_string(string_constant_5);
	    }
	    else
		tformat(2,string_constant_12,separator_qm);
	}
	listed_symbol = M_CDR(listed_symbol);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* TWRITE-LIST-FUNCTION */
Object twrite_list_function(list_1,element_writer,empty,conjoiner,separator)
    Object list_1, element_writer, empty, conjoiner, separator;
{
    Object sublist, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(23,79);
    if ( !TRUEP(list_1) && empty)
	return twrite_general_string(empty);
    else {
	sublist = list_1;
      next_loop:
	if ( !TRUEP(sublist))
	    goto end_loop;
	gensymed_symbol = element_writer;
	gensymed_symbol_1 = CAR(sublist);
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	if ( !TRUEP(CDR(sublist)));
	else if ( !TRUEP(CDDR(sublist)) && conjoiner)
	    twrite_general_string(conjoiner);
	else if (separator)
	    twrite_general_string(separator);
	sublist = M_CDR(sublist);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object Qnon_simple_character_code;  /* non-simple-character-code */

static Object Qbad_character_following_at;  /* bad-character-following-@ */

static Object Qbad_character_following_tl;  /* bad-character-following-~ */

static Object Qillegal_characters_following_bs;  /* ILLEGAL-CHARACTERS-FOLLOWING-\\ */

static Object Qincomplete_escape_sequence;  /* incomplete-escape-sequence */

/* COPY-STRING-FILTERING-OUT-NON-GENSYM-CHARACTERS */
Object copy_string_filtering_out_non_gensym_characters(ascii_string)
    Object ascii_string;
{
    Object gensym_string, string_length_exceeded_p, bad_state_p;
    Object escape_character_qm, first_character_code_following_bs_qm;
    Object second_character_code_following_bs_qm;
    Object third_character_code_following_bs_qm, kanji_character_code_qm;
    Object last_character_p, skip_this_character_p, temp;
    SI_Long string_length, character_code, last_char_index, character_index;
    char character_1;
    char string_is_simple_p;

    x_note_fn_call(23,80);
    string_length = IFIX(length(ascii_string));
    gensym_string = string_length > 
	    IFIX(Maximum_suggested_length_for_simple_gensym_strings) ? 
	    obtain_long_enough_adjustable_gensym_string(FIX(string_length)) 
	    : obtain_simple_gensym_string(FIX(string_length));
    string_length_exceeded_p = Nil;
    character_code = (SI_Long)0L;
    character_1 = 'a';
    string_is_simple_p =  !ARRAY_HAS_FILL_POINTER_P(gensym_string);
    bad_state_p = Nil;
    escape_character_qm = Nil;
    first_character_code_following_bs_qm = Nil;
    second_character_code_following_bs_qm = Nil;
    third_character_code_following_bs_qm = Nil;
    kanji_character_code_qm = Nil;
    last_char_index = string_length - (SI_Long)1L;
    character_index = (SI_Long)0L;
    last_character_p = Nil;
    skip_this_character_p = Nil;
  next_loop:
    if ( !(character_index < string_length))
	goto end_loop;
    last_character_p = character_index == last_char_index ? T : Nil;
    skip_this_character_p = Nil;
    character_1 = ICHAR(ascii_string,character_index);
    character_code = IFIX(CHAR_CODE(CHAR_TO_CHARACTER(character_1)));
    if ( !TRUEP(skip_this_character_p)) {
	if (string_is_simple_p)
	    SET_ISCHAR(gensym_string,character_index,character_1);
	else
	    SET_ICHAR(gensym_string,character_index,character_1);
	if (bad_state_p);
	else if ( !((SI_Long)32L <= character_code && character_code <= 
		(SI_Long)126L))
	    bad_state_p = Qnon_simple_character_code;
	else if (escape_character_qm) {
	    if (! !CHARACTERP(escape_character_qm))
		switch (ICHAR_CODE(escape_character_qm)) {
		  case '@':
		    switch (character_1) {
		      case 'P':
		      case 'L':
			temp = T;
			break;
		      default:
			temp = Nil;
			break;
		    }
		    if (temp)
			escape_character_qm = Nil;
		    else
			bad_state_p = Qbad_character_following_at;
		    break;
		  case '~':
		    if (ISVREF(Roman_font_special_character_code_map,
			    IFIX(CHAR_INT(CHAR_TO_CHARACTER(character_1))) 
			    - (SI_Long)32L))
			escape_character_qm = Nil;
		    else
			bad_state_p = Qbad_character_following_tl;
		    break;
		  case '\\':
		    if ( !TRUEP(first_character_code_following_bs_qm))
			first_character_code_following_bs_qm = 
				FIX(character_code);
		    else if ( !TRUEP(second_character_code_following_bs_qm)) {
			second_character_code_following_bs_qm = 
				FIX(character_code);
			if ( !(IFIX(first_character_code_following_bs_qm) 
				< (SI_Long)40L))
			    kanji_character_code_qm = FIX((SI_Long)95L * 
				    IFIX(first_character_code_following_bs_qm) 
				    + 
				    IFIX(second_character_code_following_bs_qm) 
				    + (SI_Long)4360L);
		    }
		    else {
			third_character_code_following_bs_qm = 
				FIX(character_code);
			kanji_character_code_qm = 
				FIX((IFIX(first_character_code_following_bs_qm) 
				<< (SI_Long)13L) + (SI_Long)95L * 
				IFIX(second_character_code_following_bs_qm) 
				+ 
				IFIX(third_character_code_following_bs_qm) 
				+ (SI_Long)-265976L);
		    }
		    if (first_character_code_following_bs_qm && 
			    second_character_code_following_bs_qm && 
			    (third_character_code_following_bs_qm ||  
			    !(IFIX(first_character_code_following_bs_qm) < 
			    (SI_Long)40L))) {
			if ( !TRUEP(kanji_character_code_qm))
			    bad_state_p = Qillegal_characters_following_bs;
			else {
			    escape_character_qm = Nil;
			    first_character_code_following_bs_qm = Nil;
			    second_character_code_following_bs_qm = Nil;
			    third_character_code_following_bs_qm = Nil;
			    kanji_character_code_qm = Nil;
			}
		    }
		    break;
		  default:
		    break;
		}
	}
	else if (CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('@')) || 
		CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('~')) || 
		CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('\\')))
	    escape_character_qm = CHAR_TO_CHARACTER(character_1);
    }
    if (last_character_p &&  !TRUEP(bad_state_p) && escape_character_qm)
	bad_state_p = Qincomplete_escape_sequence;
    character_index = skip_this_character_p ? character_index : 
	    character_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (bad_state_p) {
	temp = 
		copy_illegal_gensym_string_without_bad_characters(gensym_string);
	reclaim_gensym_string(gensym_string);
	gensym_string = temp;
    }
    return VALUES_2(gensym_string,string_length_exceeded_p);
}

/* COPY-ILLEGAL-GENSYM-STRING-WITHOUT-BAD-CHARACTERS */
Object copy_illegal_gensym_string_without_bad_characters(string_1)
    Object string_1;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object i, character_1, temp, character_following_at_qm, thing, temp_2;
    Object schar_arg_2, schar_new_value, character_following_tl_qm;
    Object first_character_following_bs_qm, second_character_following_bs_qm;
    Object third_character_following_bs_qm;
    SI_Long end_1, arg, arg_1, arg_2;
    char string_is_simple_qm, temp_1;
    Declare_special(4);
    Object result;

    x_note_fn_call(23,81);
    current_gensym_string = obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  0);
	    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
	    end_1 = string_is_simple_qm ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1)) : 
		    IFIX(length(string_1));
	    i = FIX((SI_Long)0L);
	    character_1 = Nil;
	  next_loop:
	    if (IFIX(i) >= end_1)
		goto end_loop;
	    temp = string_is_simple_qm ? SCHAR(string_1,i) : CHAR(string_1,i);
	    i = FIXNUM_ADD1(i);
	    character_1 = temp;
	    switch (ICHAR_CODE(character_1)) {
	      case '@':
		if (IFIX(i) < end_1) {
		    temp = string_is_simple_qm ? SCHAR(string_1,i) : 
			    CHAR(string_1,i);
		    i = FIXNUM_ADD1(i);
		    character_following_at_qm = temp;
		}
		else
		    character_following_at_qm = Nil;
		if (character_following_at_qm) {
		    arg = (SI_Long)32L;
		    arg_1 = IFIX(CHAR_INT(character_following_at_qm));
		    arg_2 = (SI_Long)126L;
		    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    if ( !CHARACTERP(character_following_at_qm))
			temp_1 = TRUEP(Nil);
		    else
			switch (ICHAR_CODE(character_following_at_qm)) {
			  case 'P':
			  case 'L':
			    temp_1 = TRUEP(T);
			    break;
			  default:
			    temp_1 = TRUEP(Nil);
			    break;
			}
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_1;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			schar_arg_2 = Fill_pointer_for_current_gensym_string;
			thing = character_1;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_following_at_qm;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			schar_arg_2 = Fill_pointer_for_current_gensym_string;
			thing = character_following_at_qm;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		}
		break;
	      case '~':
		if (IFIX(i) < end_1) {
		    temp = string_is_simple_qm ? SCHAR(string_1,i) : 
			    CHAR(string_1,i);
		    i = FIXNUM_ADD1(i);
		    character_following_tl_qm = temp;
		}
		else
		    character_following_tl_qm = Nil;
		if (character_following_tl_qm) {
		    arg = (SI_Long)32L;
		    arg_1 = IFIX(CHAR_INT(character_following_tl_qm));
		    arg_2 = (SI_Long)126L;
		    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? 
			TRUEP(ISVREF(Roman_font_special_character_code_map,
			IFIX(CHAR_INT(character_following_tl_qm)) - 
			(SI_Long)32L)) : TRUEP(Nil)) {
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_1;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			schar_arg_2 = Fill_pointer_for_current_gensym_string;
			thing = character_1;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_following_tl_qm;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			schar_arg_2 = Fill_pointer_for_current_gensym_string;
			thing = character_following_tl_qm;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		}
		break;
	      case '\\':
		if (IFIX(i) < end_1) {
		    temp = string_is_simple_qm ? SCHAR(string_1,i) : 
			    CHAR(string_1,i);
		    i = FIXNUM_ADD1(i);
		    first_character_following_bs_qm = temp;
		}
		else
		    first_character_following_bs_qm = Nil;
		if (IFIX(i) < end_1) {
		    temp = string_is_simple_qm ? SCHAR(string_1,i) : 
			    CHAR(string_1,i);
		    i = FIXNUM_ADD1(i);
		    second_character_following_bs_qm = temp;
		}
		else
		    second_character_following_bs_qm = Nil;
		if (first_character_following_bs_qm) {
		    arg = (SI_Long)32L;
		    arg_1 = IFIX(CHAR_INT(first_character_following_bs_qm));
		    arg_2 = (SI_Long)126L;
		    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? TRUEP(second_character_following_bs_qm) : 
			TRUEP(Nil)) {
		    arg = (SI_Long)32L;
		    arg_1 = IFIX(CHAR_INT(second_character_following_bs_qm));
		    arg_2 = (SI_Long)126L;
		    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    if (IFIX(CHAR_INT(first_character_following_bs_qm)) < 
			    (SI_Long)40L) {
			if (IFIX(i) < end_1) {
			    temp = string_is_simple_qm ? SCHAR(string_1,i) 
				    : CHAR(string_1,i);
			    i = FIXNUM_ADD1(i);
			    third_character_following_bs_qm = temp;
			}
			else
			    third_character_following_bs_qm = Nil;
			if (third_character_following_bs_qm) {
			    arg = (SI_Long)32L;
			    arg_1 = 
				    IFIX(CHAR_INT(third_character_following_bs_qm));
			    arg_2 = (SI_Long)126L;
			    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : 
				    TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    if (T) {
				if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				    thing = character_1;
				    twrite_wide_character(CHARACTERP(thing) 
					    ? CHAR_CODE(thing) : thing);
				}
				else {
				    if ( 
					    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					    Total_length_of_current_gensym_string))
					extend_current_gensym_string(0);
				    temp_2 = Current_gensym_string;
				    schar_arg_2 = 
					    Fill_pointer_for_current_gensym_string;
				    thing = character_1;
				    schar_new_value = 
					    CODE_CHAR(CHARACTERP(thing) ? 
					    CHAR_CODE(thing) : thing);
				    SET_SCHAR(temp_2,schar_arg_2,
					    schar_new_value);
				    temp_2 = 
					    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				    Fill_pointer_for_current_gensym_string 
					    = temp_2;
				}
				if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				    thing = first_character_following_bs_qm;
				    twrite_wide_character(CHARACTERP(thing) 
					    ? CHAR_CODE(thing) : thing);
				}
				else {
				    if ( 
					    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					    Total_length_of_current_gensym_string))
					extend_current_gensym_string(0);
				    temp_2 = Current_gensym_string;
				    schar_arg_2 = 
					    Fill_pointer_for_current_gensym_string;
				    thing = first_character_following_bs_qm;
				    schar_new_value = 
					    CODE_CHAR(CHARACTERP(thing) ? 
					    CHAR_CODE(thing) : thing);
				    SET_SCHAR(temp_2,schar_arg_2,
					    schar_new_value);
				    temp_2 = 
					    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				    Fill_pointer_for_current_gensym_string 
					    = temp_2;
				}
				if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				    thing = second_character_following_bs_qm;
				    twrite_wide_character(CHARACTERP(thing) 
					    ? CHAR_CODE(thing) : thing);
				}
				else {
				    if ( 
					    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					    Total_length_of_current_gensym_string))
					extend_current_gensym_string(0);
				    temp_2 = Current_gensym_string;
				    schar_arg_2 = 
					    Fill_pointer_for_current_gensym_string;
				    thing = second_character_following_bs_qm;
				    schar_new_value = 
					    CODE_CHAR(CHARACTERP(thing) ? 
					    CHAR_CODE(thing) : thing);
				    SET_SCHAR(temp_2,schar_arg_2,
					    schar_new_value);
				    temp_2 = 
					    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				    Fill_pointer_for_current_gensym_string 
					    = temp_2;
				}
				if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				    thing = third_character_following_bs_qm;
				    twrite_wide_character(CHARACTERP(thing) 
					    ? CHAR_CODE(thing) : thing);
				}
				else {
				    if ( 
					    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					    Total_length_of_current_gensym_string))
					extend_current_gensym_string(0);
				    temp_2 = Current_gensym_string;
				    schar_arg_2 = 
					    Fill_pointer_for_current_gensym_string;
				    thing = third_character_following_bs_qm;
				    schar_new_value = 
					    CODE_CHAR(CHARACTERP(thing) ? 
					    CHAR_CODE(thing) : thing);
				    SET_SCHAR(temp_2,schar_arg_2,
					    schar_new_value);
				    temp_2 = 
					    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				    Fill_pointer_for_current_gensym_string 
					    = temp_2;
				}
			    }
			}
		    }
		    else if (T) {
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_1;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    schar_arg_2 = 
				    Fill_pointer_for_current_gensym_string;
			    thing = character_1;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = first_character_following_bs_qm;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    schar_arg_2 = 
				    Fill_pointer_for_current_gensym_string;
			    thing = first_character_following_bs_qm;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = second_character_following_bs_qm;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    schar_arg_2 = 
				    Fill_pointer_for_current_gensym_string;
			    thing = second_character_following_bs_qm;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		}
		break;
	      default:
		arg = (SI_Long)32L;
		arg_1 = IFIX(CHAR_INT(character_1));
		arg_2 = (SI_Long)126L;
		if (arg <= arg_1 && arg_1 <= arg_2) {
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_1;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			schar_arg_2 = Fill_pointer_for_current_gensym_string;
			thing = character_1;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		}
		break;
	    }
	    goto next_loop;
	  end_loop:;
	    result = copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* ALLOCATE-SMALL-2D-ARRAY */
Object allocate_small_2d_array(size_of_each_dimension)
    Object size_of_each_dimension;
{
    Object array;
    SI_Long index_1;

    x_note_fn_call(23,82);
    array = allocate_managed_simple_vector(Maximum_managed_simple_vector_size);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 > (SI_Long)1023L)
	goto end_loop;
    ISVREF(array,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(array);
}

DEFINE_VARIABLE_WITH_SYMBOL(The_g2_defstruct_package, Qthe_g2_defstruct_package);

/* ALLOCATED-NAMED-GENSYM-STRUCTURE-P */
Object allocated_named_gensym_structure_p(thing)
    Object thing;
{
    Object temp;
    char temp_1;

    x_note_fn_call(23,83);
    if (SIMPLE_VECTOR_P(thing) && FIXNUM_GE(length(thing),FIX((SI_Long)1L))) {
	temp = ISVREF(thing,(SI_Long)0L);
	temp_1 = SYMBOLP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(EQ(SYMBOL_PACKAGE(ISVREF(thing,(SI_Long)0L)),
		The_g2_defstruct_package) ? T : Nil);
    else
	return VALUES_1(Nil);
}

Object Type_description_of_unique_type_name_of_gensym_structure_prop = UNBOUND;

Object Type_description_of_type_prop = UNBOUND;

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* TYPE-DESCRIPTION-OF */
Object type_description_of(thing)
    Object thing;
{
    Object possible_type_name_qm;
    char temp;

    x_note_fn_call(23,84);
    possible_type_name_qm = Nil;
    if (SIMPLE_VECTOR_P(thing) && FIXNUM_LE(FIX((SI_Long)1L),length(thing))) {
	possible_type_name_qm = ISVREF(thing,(SI_Long)0L);
	temp = TRUEP(possible_type_name_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? SYMBOLP(possible_type_name_qm) : TRUEP(Nil))
	return getfq_function_no_default(INLINE_SYMBOL_PLIST(possible_type_name_qm),
		Qtype_description_of_unique_type_name_of_gensym_structure);
    else
	return VALUES_1(Nil);
}

static Object Qtype_description_of_type;  /* type-description-of-type */

/* SUBTYPE-P-USING-TYPE-DESCRIPTIONS */
Object subtype_p_using_type_descriptions(refined_type_description,
	    superior_type_description)
    Object refined_type_description, superior_type_description;
{
    Object superior_type, ab_loop_list_, temp;

    x_note_fn_call(23,85);
    superior_type = Nil;
    ab_loop_list_ = ISVREF(refined_type_description,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superior_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(superior_type),
	    Qtype_description_of_type);
    if (EQL(temp,superior_type_description)) {
	temp = T;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(The_type_description_of_t, Qthe_type_description_of_t);

Object Maximum_number_of_structure_methods = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Table_to_map_structure_id_to_method_name, Qtable_to_map_structure_id_to_method_name);

Object Undefined_structure_method_message = UNBOUND;

/* UNDEFINED-STRUCTURE-METHOD-FUNCTION */
Object undefined_structure_method_function varargs_1(int, n)
{
    Object structure_type;
    Declare_varargs_nonrelocating;

    x_note_fn_call(23,86);
    INIT_ARGS_nonrelocating();
    structure_type = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return error((SI_Long)1L,
	    "Call to structure method where none was defined.");
}

static Object Qundefined_structure_method_function;  /* undefined-structure-method-function */

/* MAKE-STRUCTURE-METHOD-TABLE */
Object make_structure_method_table(superior_dispatch_table_qm)
    Object superior_dispatch_table_qm;
{
    Object dispatch_table;

    x_note_fn_call(23,87);
    dispatch_table = superior_dispatch_table_qm ? make_array(3,
	    Maximum_number_of_structure_methods,Kinitial_contents,
	    superior_dispatch_table_qm) : make_array(3,
	    Maximum_number_of_structure_methods,Kinitial_element,
	    Qundefined_structure_method_function);
    SVREF(dispatch_table,FIX((SI_Long)0L)) = superior_dispatch_table_qm;
    return VALUES_1(dispatch_table);
}

/* DB-FORMAT */
Object db_format varargs_1(int, n)
{
    Declare_varargs;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(23,88);
    SAVE_STACK();
    INIT_ARGS();
    SAVE_ARGS();
    REST_ARG();
    RESTORE_STACK();
    return VALUES_1(Nil);
}

/* CHECK-KEYWORD-LIST-SYNTAX */
Object check_keyword_list_syntax(list_1,allowed_keywords)
    Object list_1, allowed_keywords;
{
    Object keyword, ab_loop_list_;

    x_note_fn_call(23,89);
    keyword = Nil;
    ab_loop_list_ = list_1;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    keyword = CAR(ab_loop_list_);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

void utilities1_INIT()
{
    Object temp, temp_1, temp_2, temp_3, temp_4, temp_5, temp_6, temp_7;
    Object temp_8, temp_9, temp_10, temp_11, temp_12, temp_13, temp_14;
    Object named_dynamic_extent_description, gensymed_symbol, the_array;
    Object svref_arg_1;
    SI_Long i, ab_loop_bind_;
    Object Qexport_cached_explanation_node, AB_package;
    Object Qreturn_cached_explanation_if_valid, Qmake_cached_explanation_node;
    Object Qget_cached_explanation_evaled_variables_if_any, Qhandle_g2_reset;
    Object Qhandle_network_close, Qhandle_network_accept;
    Object Qhandle_network_connect, Qhandle_write_event, Qhandle_read_event;
    Object Qmap_unicode_to_code_if_any, Qmap_code_to_unicode;
    Object Qtwrite_for_export_from_transcoder, Qexport_as_string;
    Object Qexport_character, Qtranscode_as_text_string;
    Object Qtwrite_unicode_from_transcoder, Qtranscode_character;
    Object Qread_character_from_text_sequence;
    Object Qinitialize_text_sequence_string, Qclean_up_structure;
    Object Qread_character_code, Qresume_workstation_context;
    Object Qsuspend_workstation_context, Qsetup_workstation_context;
    Object Qvalid_workstation_context_p, Qreclaim_structure;
    Object Qtrack_mouse_into_spot, Qclean_up_workstation_context;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object string_constant_20, Qnamed_dynamic_extent_description, Qutilities1;
    Object string_constant_19, string_constant_18;
    Object Qcompute_memory_used_by_adjustable_gensym_strings;
    Object Qoutstanding_adjustable_gensym_strings, string_constant_17;
    Object Qcompute_memory_used_by_simple_gensym_strings;
    Object Qoutstanding_simple_gensym_strings, string_constant_16;
    Object Qstring_pool_cons_memory_usage, Qoutstanding_string_pool_conses;
    Object list_constant_11, Qstring_pool_cons_counter_vector, list_constant_8;
    Object Qmake_thread_array, Kfuncall, list_constant_10;
    Object Qavailable_string_pool_conses_tail_vector;
    Object Qavailable_string_pool_conses_vector, list_constant_5;
    Object list_constant_9, Qnew_partial_buffer_gensym_string_vector;
    Object list_constant_7, Qnew_short_simple_gensym_string_vector;
    Object list_constant_6, list_constant_4, string_constant_15;

    x_note_fn_call(23,90);
    SET_PACKAGE("AB");
    temp = make_partial_buffer_info(FIX((SI_Long)128L),FIX((SI_Long)32L),
	    FIX((SI_Long)0L),FIX((SI_Long)5L));
    temp_1 = make_partial_buffer_info(FIX((SI_Long)256L),FIX((SI_Long)64L),
	    FIX((SI_Long)3L),FIX((SI_Long)6L));
    temp_2 = make_partial_buffer_info(FIX((SI_Long)512L),
	    FIX((SI_Long)128L),FIX((SI_Long)5L),FIX((SI_Long)7L));
    temp_3 = make_partial_buffer_info(FIX((SI_Long)1024L),
	    FIX((SI_Long)256L),FIX((SI_Long)7L),FIX((SI_Long)8L));
    temp_4 = make_partial_buffer_info(FIX((SI_Long)2048L),
	    FIX((SI_Long)512L),FIX((SI_Long)9L),FIX((SI_Long)9L));
    temp_5 = make_partial_buffer_info(FIX((SI_Long)4096L),
	    FIX((SI_Long)1024L),FIX((SI_Long)11L),FIX((SI_Long)10L));
    temp_6 = make_partial_buffer_info(FIX((SI_Long)8192L),
	    FIX((SI_Long)2048L),FIX((SI_Long)13L),FIX((SI_Long)11L));
    temp_7 = make_partial_buffer_info(FIX((SI_Long)16384L),
	    FIX((SI_Long)4096L),FIX((SI_Long)15L),FIX((SI_Long)12L));
    temp_8 = make_partial_buffer_info(FIX((SI_Long)32768L),
	    FIX((SI_Long)8192L),FIX((SI_Long)17L),FIX((SI_Long)13L));
    temp_9 = make_partial_buffer_info(FIX((SI_Long)65536L),
	    FIX((SI_Long)16384L),FIX((SI_Long)19L),FIX((SI_Long)14L));
    temp_10 = make_partial_buffer_info(FIX((SI_Long)131072L),
	    FIX((SI_Long)32768L),FIX((SI_Long)21L),FIX((SI_Long)15L));
    temp_11 = make_partial_buffer_info(FIX((SI_Long)262144L),
	    FIX((SI_Long)65536L),FIX((SI_Long)23L),FIX((SI_Long)16L));
    temp_12 = make_partial_buffer_info(FIX((SI_Long)524288L),
	    FIX((SI_Long)131072L),FIX((SI_Long)25L),FIX((SI_Long)17L));
    temp_13 = make_partial_buffer_info(FIX((SI_Long)1048576L),
	    FIX((SI_Long)262144L),FIX((SI_Long)27L),FIX((SI_Long)18L));
    temp_14 = make_partial_buffer_info(FIX((SI_Long)2097152L),
	    FIX((SI_Long)524288L),FIX((SI_Long)29L),FIX((SI_Long)19L));
    String_allocation_schemes = list(16,temp,temp_1,temp_2,temp_3,temp_4,
	    temp_5,temp_6,temp_7,temp_8,temp_9,temp_10,temp_11,temp_12,
	    temp_13,temp_14,
	    make_partial_buffer_info(FIX((SI_Long)4194304L),
	    FIX((SI_Long)1048576L),FIX((SI_Long)31L),FIX((SI_Long)20L)));
    Maximum_gensym_string_length = ltimes(FIX((SI_Long)4L),
	    FIX((SI_Long)1048576L));
    string_constant_15 = 
	    STATIC_STRING("Attempting to allocate ~a element string, ~\n   which is beyond the established maximum of ~a.");
    Maximum_gensym_string_length_exceeded_message = string_constant_15;
    AB_package = STATIC_PACKAGE("AB");
    Qshort_simple_gensym_strings = 
	    STATIC_SYMBOL("SHORT-SIMPLE-GENSYM-STRINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qshort_simple_gensym_strings,
	    Short_simple_gensym_strings);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qnew_short_simple_gensym_string_vector = 
	    STATIC_SYMBOL("NEW-SHORT-SIMPLE-GENSYM-STRING-VECTOR",AB_package);
    SET_SYMBOL_FUNCTION(Qnew_short_simple_gensym_string_vector,
	    STATIC_FUNCTION(new_short_simple_gensym_string_vector,NIL,
	    FALSE,1,1));
    list_constant_4 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qnew_short_simple_gensym_string_vector,Qnil);
    record_system_variable(Qshort_simple_gensym_strings,Qutilities1,
	    list_constant_4,Qnil,Qt,Qnil,Qnil);
    Qlong_simple_gensym_strings = 
	    STATIC_SYMBOL("LONG-SIMPLE-GENSYM-STRINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlong_simple_gensym_strings,
	    Long_simple_gensym_strings);
    Qnew_partial_buffer_gensym_string_vector = 
	    STATIC_SYMBOL("NEW-PARTIAL-BUFFER-GENSYM-STRING-VECTOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnew_partial_buffer_gensym_string_vector,
	    STATIC_FUNCTION(new_partial_buffer_gensym_string_vector,NIL,
	    FALSE,1,1));
    list_constant_5 = STATIC_CONS(Qnil,Qnil);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qnew_partial_buffer_gensym_string_vector,list_constant_5);
    record_system_variable(Qlong_simple_gensym_strings,Qutilities1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qadjustable_gensym_strings = STATIC_SYMBOL("ADJUSTABLE-GENSYM-STRINGS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qadjustable_gensym_strings,
	    Adjustable_gensym_strings);
    record_system_variable(Qadjustable_gensym_strings,Qutilities1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qshort_simple_gensym_string_counts = 
	    STATIC_SYMBOL("SHORT-SIMPLE-GENSYM-STRING-COUNTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qshort_simple_gensym_string_counts,
	    Short_simple_gensym_string_counts);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qnew_short_simple_gensym_string_vector,FIX((SI_Long)0L));
    record_system_variable(Qshort_simple_gensym_string_counts,Qutilities1,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qlong_simple_gensym_string_counts = 
	    STATIC_SYMBOL("LONG-SIMPLE-GENSYM-STRING-COUNTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlong_simple_gensym_string_counts,
	    Long_simple_gensym_string_counts);
    list_constant_8 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qnew_partial_buffer_gensym_string_vector,list_constant_8);
    record_system_variable(Qlong_simple_gensym_string_counts,Qutilities1,
	    list_constant_9,Qnil,Qt,Qnil,Qnil);
    Qadjustable_gensym_string_counts = 
	    STATIC_SYMBOL("ADJUSTABLE-GENSYM-STRING-COUNTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qadjustable_gensym_string_counts,
	    Adjustable_gensym_string_counts);
    record_system_variable(Qadjustable_gensym_string_counts,Qutilities1,
	    list_constant_9,Qnil,Qt,Qnil,Qnil);
    Qavailable_string_pool_conses = 
	    STATIC_SYMBOL("AVAILABLE-STRING-POOL-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_string_pool_conses,
	    Available_string_pool_conses);
    record_system_variable(Qavailable_string_pool_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_string_pool_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-STRING-POOL-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_string_pool_conses_tail,
	    Available_string_pool_conses_tail);
    record_system_variable(Qavailable_string_pool_conses_tail,Qutilities1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_string_pool_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-STRING-POOL-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_string_pool_conses_vector,
	    Available_string_pool_conses_vector);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qmake_thread_array,list_constant_5);
    record_system_variable(Qavailable_string_pool_conses_vector,
	    Qutilities1,list_constant_10,Qnil,Qt,Qnil,Qnil);
    Qavailable_string_pool_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-STRING-POOL-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_string_pool_conses_tail_vector,
	    Available_string_pool_conses_tail_vector);
    record_system_variable(Qavailable_string_pool_conses_tail_vector,
	    Qutilities1,list_constant_10,Qnil,Qt,Qnil,Qnil);
    Qstring_pool_cons_counter_vector = 
	    STATIC_SYMBOL("STRING-POOL-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstring_pool_cons_counter_vector,
	    String_pool_cons_counter_vector);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qmake_thread_array,list_constant_8);
    record_system_variable(Qstring_pool_cons_counter_vector,Qutilities1,
	    list_constant_11,Qnil,Qt,Qnil,Qnil);
    Qstring_pool_cons_counter = STATIC_SYMBOL("STRING-POOL-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstring_pool_cons_counter,
	    String_pool_cons_counter);
    record_system_variable(Qstring_pool_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_string_pool_conses = 
	    STATIC_SYMBOL("OUTSTANDING-STRING-POOL-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_string_pool_conses,
	    STATIC_FUNCTION(outstanding_string_pool_conses,NIL,FALSE,0,0));
    Qstring_pool_cons_memory_usage = 
	    STATIC_SYMBOL("STRING-POOL-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qstring_pool_cons_memory_usage,
	    STATIC_FUNCTION(string_pool_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_16 = STATIC_STRING("1q83-r3y9k83-r2y09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_string_pool_conses);
    push_optimized_constant(Qstring_pool_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Qstring_pool = STATIC_SYMBOL("STRING-POOL",AB_package);
    Qsimple_gensym_string_counter = 
	    STATIC_SYMBOL("SIMPLE-GENSYM-STRING-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimple_gensym_string_counter,
	    Simple_gensym_string_counter);
    record_system_variable(Qsimple_gensym_string_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qsimple_gensym_string_byte_use_counter = 
	    STATIC_SYMBOL("SIMPLE-GENSYM-STRING-BYTE-USE-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimple_gensym_string_byte_use_counter,
	    Simple_gensym_string_byte_use_counter);
    record_system_variable(Qsimple_gensym_string_byte_use_counter,
	    Qutilities1,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_simple_gensym_strings = 
	    STATIC_SYMBOL("OUTSTANDING-SIMPLE-GENSYM-STRINGS",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_simple_gensym_strings,
	    STATIC_FUNCTION(outstanding_simple_gensym_strings,NIL,FALSE,0,0));
    Qcompute_memory_used_by_simple_gensym_strings = 
	    STATIC_SYMBOL("COMPUTE-MEMORY-USED-BY-SIMPLE-GENSYM-STRINGS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_memory_used_by_simple_gensym_strings,
	    STATIC_FUNCTION(compute_memory_used_by_simple_gensym_strings,
	    NIL,FALSE,0,0));
    string_constant_17 = STATIC_STRING("1q83-pQy83-pTy83-pPy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_simple_gensym_strings);
    push_optimized_constant(Qcompute_memory_used_by_simple_gensym_strings);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_17));
    Qsimple_gensym_string = STATIC_SYMBOL("SIMPLE-GENSYM-STRING",AB_package);
    if (Log_simple_string_data == UNBOUND)
	Log_simple_string_data = Nil;
    if (Log_simple_string_reclaims == UNBOUND)
	Log_simple_string_reclaims = T;
    if (Min_string_length_to_report == UNBOUND)
	Min_string_length_to_report = FIX((SI_Long)2100L);
    if (String_report_frequency == UNBOUND)
	String_report_frequency = FIX((SI_Long)10L);
    if (String_allocations_until_next_report == UNBOUND)
	String_allocations_until_next_report = FIX((SI_Long)0L);
    if (String_reclaims_until_next_report == UNBOUND)
	String_reclaims_until_next_report = FIX((SI_Long)0L);
    if (String_chars_to_print == UNBOUND)
	String_chars_to_print = FIX((SI_Long)200L);
    if (Largest_non_malloced_string_pool_index == UNBOUND)
	Largest_non_malloced_string_pool_index = FIX((SI_Long)-1L);
    if (String_pool_number_to_malloc == UNBOUND)
	String_pool_number_to_malloc = FIX((SI_Long)-1L);
    Qstring_allocations_until_next_report = 
	    STATIC_SYMBOL("STRING-ALLOCATIONS-UNTIL-NEXT-REPORT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstring_allocations_until_next_report,
	    String_allocations_until_next_report);
    if (Current_custom_reclamation_stamp_qm == UNBOUND)
	Current_custom_reclamation_stamp_qm = Nil;
    Qstring_reclaims_until_next_report = 
	    STATIC_SYMBOL("STRING-RECLAIMS-UNTIL-NEXT-REPORT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstring_reclaims_until_next_report,
	    String_reclaims_until_next_report);
    Qadjustable_gensym_string_counter = 
	    STATIC_SYMBOL("ADJUSTABLE-GENSYM-STRING-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qadjustable_gensym_string_counter,
	    Adjustable_gensym_string_counter);
    record_system_variable(Qadjustable_gensym_string_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qadjustable_gensym_string_byte_use_counter = 
	    STATIC_SYMBOL("ADJUSTABLE-GENSYM-STRING-BYTE-USE-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qadjustable_gensym_string_byte_use_counter,
	    Adjustable_gensym_string_byte_use_counter);
    record_system_variable(Qadjustable_gensym_string_byte_use_counter,
	    Qutilities1,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_adjustable_gensym_strings = 
	    STATIC_SYMBOL("OUTSTANDING-ADJUSTABLE-GENSYM-STRINGS",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_adjustable_gensym_strings,
	    STATIC_FUNCTION(outstanding_adjustable_gensym_strings,NIL,
	    FALSE,0,0));
    Qcompute_memory_used_by_adjustable_gensym_strings = 
	    STATIC_SYMBOL("COMPUTE-MEMORY-USED-BY-ADJUSTABLE-GENSYM-STRINGS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_memory_used_by_adjustable_gensym_strings,
	    STATIC_FUNCTION(compute_memory_used_by_adjustable_gensym_strings,
	    NIL,FALSE,0,0));
    string_constant_18 = STATIC_STRING("1q83-JKy9k83-JJy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qstring);
    push_optimized_constant(Qoutstanding_adjustable_gensym_strings);
    push_optimized_constant(Qcompute_memory_used_by_adjustable_gensym_strings);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_18));
    Qadjustable_gensym_string = STATIC_SYMBOL("ADJUSTABLE-GENSYM-STRING",
	    AB_package);
    string_constant_19 = STATIC_STRING("OUTPUTTING-TO-GENSYM-STRING");
    if (Outputting_to_gensym_string == UNBOUND)
	Outputting_to_gensym_string = make_recursive_lock(2,Kname,
		string_constant_19);
    Qoutputting_to_gensym_string = 
	    STATIC_SYMBOL("OUTPUTTING-TO-GENSYM-STRING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoutputting_to_gensym_string,
	    Outputting_to_gensym_string);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qoutputting_to_gensym_string,
	    Qutilities1,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qoutputting_to_gensym_string,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Write_symbols_parsably_qm == UNBOUND)
	Write_symbols_parsably_qm = Nil;
    list_constant = STATIC_CONS(CHR(':'),Qnil);
    list_constant_1 = STATIC_LIST((SI_Long)2L,CHR(' '),CHR('\t'));
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_20 = 
	    STATIC_STRING("Trying to write a string longer than 1MB!");
    Extend_current_gensym_string_error_message = string_constant_20;
    if (Calling_tformat_for_give_warning_qm == UNBOUND)
	Calling_tformat_for_give_warning_qm = Nil;
    if (Write_symbols_in_lower_case_qm == UNBOUND)
	Write_symbols_in_lower_case_qm = Nil;
    string_constant = STATIC_STRING("-9223372036854775808");
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    if (Write_strings_parsably_qm == UNBOUND)
	Write_strings_parsably_qm = Nil;
    list_constant_2 = STATIC_LIST((SI_Long)10L,CHR('a'),CHR('e'),CHR('i'),
	    CHR('o'),CHR('u'),CHR('A'),CHR('E'),CHR('I'),CHR('O'),CHR('U'));
    string_constant_1 = STATIC_STRING("an ");
    string_constant_2 = STATIC_STRING("a ");
    if (Note_blocks_in_tformat == UNBOUND)
	Note_blocks_in_tformat = Nil;
    if (Tformat_fresh_line_is_newline_p == UNBOUND)
	Tformat_fresh_line_is_newline_p = T;
    if (In_text_for_item_or_value_p == UNBOUND)
	In_text_for_item_or_value_p = Nil;
    string_constant_3 = STATIC_STRING(";");
    string_constant_4 = STATIC_STRING(",");
    string_constant_5 = STATIC_STRING(" ");
    string_constant_6 = STATIC_STRING("or");
    string_constant_7 = STATIC_STRING("and");
    list_constant_3 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)32L),
	    FIX((SI_Long)9L),FIX((SI_Long)10L),FIX((SI_Long)10L),
	    FIX((SI_Long)13L));
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    string_constant_8 = STATIC_STRING("(");
    string_constant_9 = STATIC_STRING(" . ");
    string_constant_10 = STATIC_STRING(")");
    string_constant_11 = STATIC_STRING("none");
    string_constant_12 = STATIC_STRING("~a ");
    string_constant_13 = STATIC_STRING(" ~(~a~) ");
    string_constant_14 = STATIC_STRING("~(~a~)");
    Qnon_simple_character_code = STATIC_SYMBOL("NON-SIMPLE-CHARACTER-CODE",
	    AB_package);
    Qbad_character_following_at = 
	    STATIC_SYMBOL("BAD-CHARACTER-FOLLOWING-@",AB_package);
    Qbad_character_following_tl = 
	    STATIC_SYMBOL("BAD-CHARACTER-FOLLOWING-~",AB_package);
    Qillegal_characters_following_bs = 
	    STATIC_SYMBOL("ILLEGAL-CHARACTERS-FOLLOWING-\\",AB_package);
    Qincomplete_escape_sequence = 
	    STATIC_SYMBOL("INCOMPLETE-ESCAPE-SEQUENCE",AB_package);
    string_constant_21 = STATIC_STRING("G2-DEFSTRUCT-STRUCTURE-NAME");
    if (The_g2_defstruct_package == UNBOUND)
	The_g2_defstruct_package = find_package(string_constant_21);
    string_constant_22 = STATIC_STRING("TYPE-DESCRIPTION-G2-STRUCT");
    intern(string_constant_22,The_g2_defstruct_package);
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    Type_description_of_unique_type_name_of_gensym_structure_prop = 
	    Qtype_description_of_unique_type_name_of_gensym_structure;
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    Type_description_of_type_prop = Qtype_description_of_type;
    string_constant_23 = STATIC_STRING("43Dy8m8k00000004ukkkkkkkkkk0kkk0k0");
    if (The_type_description_of_t == UNBOUND)
	The_type_description_of_t = 
		regenerate_optimized_constant(string_constant_23);
    mutate_global_property(T,The_type_description_of_t,
	    Qtype_description_of_type);
    Maximum_number_of_structure_methods = FIX((SI_Long)40L);
    if (Table_to_map_structure_id_to_method_name == UNBOUND) {
	gensymed_symbol = Maximum_number_of_structure_methods;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	Table_to_map_structure_id_to_method_name = the_array;
    }
    string_constant_24 = 
	    STATIC_STRING("Call to structure method where none was defined.");
    Undefined_structure_method_message = string_constant_24;
    Qundefined_structure_method_function = 
	    STATIC_SYMBOL("UNDEFINED-STRUCTURE-METHOD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qundefined_structure_method_function,
	    STATIC_FUNCTION(undefined_structure_method_function,NIL,TRUE,1,
	    12));
    Qclean_up_workstation_context = 
	    STATIC_SYMBOL("CLEAN-UP-WORKSTATION-CONTEXT",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Qclean_up_workstation_context;
    Qtrack_mouse_into_spot = STATIC_SYMBOL("TRACK-MOUSE-INTO-SPOT",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qtrack_mouse_into_spot;
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)3L)) = Qreclaim_structure;
    Qvalid_workstation_context_p = 
	    STATIC_SYMBOL("VALID-WORKSTATION-CONTEXT-P",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = Qvalid_workstation_context_p;
    Qsetup_workstation_context = STATIC_SYMBOL("SETUP-WORKSTATION-CONTEXT",
	    AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)5L)) = Qsetup_workstation_context;
    Qsuspend_workstation_context = 
	    STATIC_SYMBOL("SUSPEND-WORKSTATION-CONTEXT",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = Qsuspend_workstation_context;
    Qresume_workstation_context = 
	    STATIC_SYMBOL("RESUME-WORKSTATION-CONTEXT",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = Qresume_workstation_context;
    Qread_character_code = STATIC_SYMBOL("READ-CHARACTER-CODE",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = Qread_character_code;
    Qclean_up_structure = STATIC_SYMBOL("CLEAN-UP-STRUCTURE",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = Qclean_up_structure;
    Qinitialize_text_sequence_string = 
	    STATIC_SYMBOL("INITIALIZE-TEXT-SEQUENCE-STRING",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)10L)) = Qinitialize_text_sequence_string;
    Qread_character_from_text_sequence = 
	    STATIC_SYMBOL("READ-CHARACTER-FROM-TEXT-SEQUENCE",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qread_character_from_text_sequence;
    Qtranscode_character = STATIC_SYMBOL("TRANSCODE-CHARACTER",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)12L)) = Qtranscode_character;
    Qtwrite_unicode_from_transcoder = 
	    STATIC_SYMBOL("TWRITE-UNICODE-FROM-TRANSCODER",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)13L)) = Qtwrite_unicode_from_transcoder;
    Qtranscode_as_text_string = STATIC_SYMBOL("TRANSCODE-AS-TEXT-STRING",
	    AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)14L)) = Qtranscode_as_text_string;
    Qexport_character = STATIC_SYMBOL("EXPORT-CHARACTER",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)15L)) = Qexport_character;
    Qexport_as_string = STATIC_SYMBOL("EXPORT-AS-STRING",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)16L)) = Qexport_as_string;
    Qtwrite_for_export_from_transcoder = 
	    STATIC_SYMBOL("TWRITE-FOR-EXPORT-FROM-TRANSCODER",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)17L)) = Qtwrite_for_export_from_transcoder;
    Qmap_code_to_unicode = STATIC_SYMBOL("MAP-CODE-TO-UNICODE",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)18L)) = Qmap_code_to_unicode;
    Qmap_unicode_to_code_if_any = 
	    STATIC_SYMBOL("MAP-UNICODE-TO-CODE-IF-ANY",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)19L)) = Qmap_unicode_to_code_if_any;
    Qhandle_read_event = STATIC_SYMBOL("HANDLE-READ-EVENT",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)20L)) = Qhandle_read_event;
    Qhandle_write_event = STATIC_SYMBOL("HANDLE-WRITE-EVENT",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)21L)) = Qhandle_write_event;
    Qhandle_network_connect = STATIC_SYMBOL("HANDLE-NETWORK-CONNECT",
	    AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)22L)) = Qhandle_network_connect;
    Qhandle_network_accept = STATIC_SYMBOL("HANDLE-NETWORK-ACCEPT",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)23L)) = Qhandle_network_accept;
    Qhandle_network_close = STATIC_SYMBOL("HANDLE-NETWORK-CLOSE",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)24L)) = Qhandle_network_close;
    Qhandle_g2_reset = STATIC_SYMBOL("HANDLE-G2-RESET",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)25L)) = Qhandle_g2_reset;
    Qget_cached_explanation_evaled_variables_if_any = 
	    STATIC_SYMBOL("GET-CACHED-EXPLANATION-EVALED-VARIABLES-IF-ANY",
	    AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)26L)) = 
	    Qget_cached_explanation_evaled_variables_if_any;
    Qmake_cached_explanation_node = 
	    STATIC_SYMBOL("MAKE-CACHED-EXPLANATION-NODE",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)27L)) = Qmake_cached_explanation_node;
    Qreturn_cached_explanation_if_valid = 
	    STATIC_SYMBOL("RETURN-CACHED-EXPLANATION-IF-VALID",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)28L)) = Qreturn_cached_explanation_if_valid;
    Qexport_cached_explanation_node = 
	    STATIC_SYMBOL("EXPORT-CACHED-EXPLANATION-NODE",AB_package);
    svref_arg_1 = Table_to_map_structure_id_to_method_name;
    SVREF(svref_arg_1,FIX((SI_Long)29L)) = Qexport_cached_explanation_node;
}
