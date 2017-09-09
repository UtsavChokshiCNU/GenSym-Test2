/* icons.c
 * Input file:  icons.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "icons.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_slot_value_conses, Qavailable_slot_value_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_slot_value_conses_tail, Qavailable_slot_value_conses_tail);

Object Available_slot_value_conses_vector = UNBOUND;

Object Available_slot_value_conses_tail_vector = UNBOUND;

Object Slot_value_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Slot_value_cons_counter, Qslot_value_cons_counter);

/* OUTSTANDING-SLOT-VALUE-CONSES */
Object outstanding_slot_value_conses()
{
    Object temp;

    x_note_fn_call(63,0);
    temp = FIXNUM_MINUS(Slot_value_cons_counter,
	    length(Available_slot_value_conses));
    return VALUES_1(temp);
}

/* SLOT-VALUE-CONS-MEMORY-USAGE */
Object slot_value_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(63,1);
    temp = FIXNUM_TIMES(Slot_value_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-SLOT-VALUE-CONS-POOL */
Object replenish_slot_value_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(63,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qslot_value_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_slot_value_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_slot_value_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_slot_value_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Slot_value_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qab_slot_value;      /* slot-value */

/* SLOT-VALUE-CONS-1 */
Object slot_value_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(63,3);
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_slot_value_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-SLOT-VALUE-LIST-POOL */
Object replenish_slot_value_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(63,4);
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
    if (ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_slot_value_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_slot_value_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_slot_value_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qslot_value_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-SLOT-VALUE-LIST-1 */
Object make_slot_value_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(63,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_slot_value_conses_vector,
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
	replenish_slot_value_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_slot_value_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_slot_value_conses_tail_vector;
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

/* SLOT-VALUE-LIST-2 */
Object slot_value_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(63,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_slot_value_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qab_slot_value);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_slot_value_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_slot_value_conses_tail_vector;
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

/* SLOT-VALUE-LIST-3 */
Object slot_value_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(63,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_slot_value_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qab_slot_value);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_slot_value_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_slot_value_conses_tail_vector;
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

/* SLOT-VALUE-LIST-4 */
Object slot_value_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(63,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_slot_value_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qab_slot_value);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_slot_value_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_slot_value_conses_tail_vector;
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

/* SLOT-VALUE-LIST-TRACE-HOOK */
Object slot_value_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(63,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-SLOT-VALUE-CONSES-1 */
Object copy_tree_using_slot_value_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(63,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	temp_1 = copy_tree_using_slot_value_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	temp_1 = 
		copy_tree_using_slot_value_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
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

/* COPY-LIST-USING-SLOT-VALUE-CONSES-1 */
Object copy_list_using_slot_value_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(63,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
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

/* RECLAIM-SLOT-VALUE-CONS-1 */
Object reclaim_slot_value_cons_1(slot_value_cons)
    Object slot_value_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(63,12);
    inline_note_reclaim_cons(slot_value_cons,Qab_slot_value);
    if (ISVREF(Available_slot_value_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = slot_value_cons;
	temp = Available_slot_value_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = slot_value_cons;
    }
    else {
	temp = Available_slot_value_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = slot_value_cons;
	temp = Available_slot_value_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = slot_value_cons;
    }
    M_CDR(slot_value_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-SLOT-VALUE-LIST-1 */
Object reclaim_slot_value_list_1(slot_value_list)
    Object slot_value_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(63,13);
    if (slot_value_list) {
	last_1 = slot_value_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qab_slot_value);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = slot_value_list;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = slot_value_list;
	    temp = Available_slot_value_conses_tail_vector;
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

/* RECLAIM-SLOT-VALUE-LIST*-1 */
Object reclaim_slot_value_list_star_1(slot_value_list)
    Object slot_value_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(63,14);
    if (CONSP(slot_value_list)) {
	temp = last(slot_value_list,_);
	M_CDR(temp) = Nil;
	if (slot_value_list) {
	    last_1 = slot_value_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qab_slot_value);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qab_slot_value);
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = slot_value_list;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = slot_value_list;
		temp = Available_slot_value_conses_tail_vector;
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

/* RECLAIM-SLOT-VALUE-TREE-1 */
Object reclaim_slot_value_tree_1(tree)
    Object tree;
{
    Object e, e2, slot_value_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(63,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_slot_value_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		slot_value_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(slot_value_cons,Qab_slot_value);
		if (EQ(slot_value_cons,e))
		    goto end_1;
		else if ( !TRUEP(slot_value_cons))
		    goto end_1;
		else
		    slot_value_cons = CDR(slot_value_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_slot_value_conses_tail_vector;
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

/* DELETE-SLOT-VALUE-ELEMENT-1 */
Object delete_slot_value_element_1(element,slot_value_list)
    Object element, slot_value_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(63,16);
    if (slot_value_list) {
	if (EQ(element,M_CAR(slot_value_list))) {
	    temp = CDR(slot_value_list);
	    inline_note_reclaim_cons(slot_value_list,Qab_slot_value);
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = slot_value_list;
		temp_1 = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = slot_value_list;
	    }
	    else {
		temp_1 = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = slot_value_list;
		temp_1 = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = slot_value_list;
	    }
	    M_CDR(slot_value_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = slot_value_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qab_slot_value);
		if (ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_slot_value_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_slot_value_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_slot_value_conses_tail_vector;
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
	    temp = slot_value_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-SLOT-VALUE-CONS-1 */
Object delete_slot_value_cons_1(slot_value_cons,slot_value_list)
    Object slot_value_cons, slot_value_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(63,17);
    if (EQ(slot_value_cons,slot_value_list))
	temp = CDR(slot_value_list);
    else {
	l_trailer_qm = Nil;
	l = slot_value_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,slot_value_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = slot_value_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_slot_value_cons_1(slot_value_cons);
    return VALUES_1(temp);
}

/* RECLAIM-SLOT-VALUE-LIST-FUNCTION */
Object reclaim_slot_value_list_function(slot_value_list)
    Object slot_value_list;
{
    x_note_fn_call(63,18);
    return reclaim_slot_value_list_1(slot_value_list);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_entity_conses, Qavailable_entity_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_entity_conses_tail, Qavailable_entity_conses_tail);

Object Available_entity_conses_vector = UNBOUND;

Object Available_entity_conses_tail_vector = UNBOUND;

Object Entity_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Entity_cons_counter, Qentity_cons_counter);

/* OUTSTANDING-ENTITY-CONSES */
Object outstanding_entity_conses()
{
    Object temp;

    x_note_fn_call(63,19);
    temp = FIXNUM_MINUS(Entity_cons_counter,length(Available_entity_conses));
    return VALUES_1(temp);
}

/* ENTITY-CONS-MEMORY-USAGE */
Object entity_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(63,20);
    temp = FIXNUM_TIMES(Entity_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-ENTITY-CONS-POOL */
Object replenish_entity_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(63,21);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qentity_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_entity_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_entity_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_entity_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_entity_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Entity_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qentity;             /* entity */

/* ENTITY-CONS-1 */
Object entity_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(63,22);
    new_cons = ISVREF(Available_entity_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_entity_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_entity_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_entity_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qentity);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-ENTITY-LIST-POOL */
Object replenish_entity_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(63,23);
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
    if (ISVREF(Available_entity_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_entity_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_entity_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_entity_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qentity_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-ENTITY-LIST-1 */
Object make_entity_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(63,24);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_entity_conses_vector,
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
	replenish_entity_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_entity_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qentity);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_entity_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_entity_conses_tail_vector;
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

/* ENTITY-LIST-2 */
Object entity_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(63,25);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_entity_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_entity_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qentity);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_entity_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_entity_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_entity_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_entity_conses_tail_vector;
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

/* ENTITY-LIST-3 */
Object entity_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(63,26);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_entity_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_entity_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qentity);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_entity_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_entity_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_entity_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_entity_conses_tail_vector;
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

/* ENTITY-LIST-4 */
Object entity_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(63,27);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_entity_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_entity_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qentity);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_entity_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_entity_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_entity_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_entity_conses_tail_vector;
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

/* ENTITY-LIST-TRACE-HOOK */
Object entity_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(63,28);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-ENTITY-CONSES-1 */
Object copy_tree_using_entity_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(63,29);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_entity_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_entity_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_entity_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_entity_cons_pool();
	temp_1 = copy_tree_using_entity_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qentity);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_entity_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_entity_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_entity_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_entity_cons_pool();
	temp_1 = copy_tree_using_entity_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qentity);
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

/* COPY-LIST-USING-ENTITY-CONSES-1 */
Object copy_list_using_entity_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(63,30);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_entity_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_entity_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_entity_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_entity_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qentity);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_entity_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_entity_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_entity_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_entity_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_entity_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qentity);
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

/* RECLAIM-ENTITY-CONS-1 */
Object reclaim_entity_cons_1(entity_cons)
    Object entity_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(63,31);
    inline_note_reclaim_cons(entity_cons,Qentity);
    if (ISVREF(Available_entity_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_entity_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = entity_cons;
	temp = Available_entity_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = entity_cons;
    }
    else {
	temp = Available_entity_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = entity_cons;
	temp = Available_entity_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = entity_cons;
    }
    M_CDR(entity_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-ENTITY-LIST-1 */
Object reclaim_entity_list_1(entity_list)
    Object entity_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(63,32);
    if (entity_list) {
	last_1 = entity_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qentity);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qentity);
	if (ISVREF(Available_entity_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_entity_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = entity_list;
	    temp = Available_entity_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_entity_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = entity_list;
	    temp = Available_entity_conses_tail_vector;
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

/* RECLAIM-ENTITY-LIST*-1 */
Object reclaim_entity_list_star_1(entity_list)
    Object entity_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(63,33);
    if (CONSP(entity_list)) {
	temp = last(entity_list,_);
	M_CDR(temp) = Nil;
	if (entity_list) {
	    last_1 = entity_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qentity);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qentity);
	    if (ISVREF(Available_entity_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_entity_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = entity_list;
		temp = Available_entity_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_entity_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = entity_list;
		temp = Available_entity_conses_tail_vector;
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

/* RECLAIM-ENTITY-TREE-1 */
Object reclaim_entity_tree_1(tree)
    Object tree;
{
    Object e, e2, entity_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(63,34);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_entity_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		entity_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(entity_cons,Qentity);
		if (EQ(entity_cons,e))
		    goto end_1;
		else if ( !TRUEP(entity_cons))
		    goto end_1;
		else
		    entity_cons = CDR(entity_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_entity_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_entity_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_entity_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_entity_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_entity_conses_tail_vector;
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

/* DELETE-ENTITY-ELEMENT-1 */
Object delete_entity_element_1(element,entity_list)
    Object element, entity_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(63,35);
    if (entity_list) {
	if (EQ(element,M_CAR(entity_list))) {
	    temp = CDR(entity_list);
	    inline_note_reclaim_cons(entity_list,Qentity);
	    if (ISVREF(Available_entity_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_entity_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = entity_list;
		temp_1 = Available_entity_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = entity_list;
	    }
	    else {
		temp_1 = Available_entity_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = entity_list;
		temp_1 = Available_entity_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = entity_list;
	    }
	    M_CDR(entity_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = entity_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qentity);
		if (ISVREF(Available_entity_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_entity_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_entity_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_entity_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_entity_conses_tail_vector;
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
	    temp = entity_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-ENTITY-CONS-1 */
Object delete_entity_cons_1(entity_cons,entity_list)
    Object entity_cons, entity_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(63,36);
    if (EQ(entity_cons,entity_list))
	temp = CDR(entity_list);
    else {
	l_trailer_qm = Nil;
	l = entity_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,entity_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = entity_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_entity_cons_1(entity_cons);
    return VALUES_1(temp);
}

Object The_type_description_of_icon_description = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icon_descriptions, Qchain_of_available_icon_descriptions);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_description_count, Qicon_description_count);

Object Chain_of_available_icon_descriptions_vector = UNBOUND;

/* ICON-DESCRIPTION-STRUCTURE-MEMORY-USAGE */
Object icon_description_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(63,37);
    temp = Icon_description_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)14L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICON-DESCRIPTION-COUNT */
Object outstanding_icon_description_count()
{
    Object def_structure_icon_description_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(63,38);
    gensymed_symbol = IFIX(Icon_description_count);
    def_structure_icon_description_variable = 
	    Chain_of_available_icon_descriptions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icon_description_variable))
	goto end_loop;
    def_structure_icon_description_variable = 
	    ISVREF(def_structure_icon_description_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICON-DESCRIPTION-INTERNAL-1 */
Object reclaim_icon_description_internal_1(icon_description)
    Object icon_description;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(63,39);
    inline_note_reclaim_cons(icon_description,Nil);
    structure_being_reclaimed = icon_description;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_line_drawing_description(ISVREF(icon_description,(SI_Long)8L));
      SVREF(icon_description,FIX((SI_Long)8L)) = Nil;
      reclaim_icon_renderings(ISVREF(icon_description,(SI_Long)9L));
      SVREF(icon_description,FIX((SI_Long)9L)) = Nil;
      reclaim_icon_region_extrema_qm(ISVREF(icon_description,(SI_Long)11L));
      SVREF(icon_description,FIX((SI_Long)11L)) = Nil;
      reclaim_slot_value(ISVREF(icon_description,(SI_Long)13L));
      SVREF(icon_description,FIX((SI_Long)13L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_icon_descriptions_vector,
	    IFIX(Current_thread_index));
    SVREF(icon_description,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icon_descriptions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icon_description;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICON-DESCRIPTION */
Object reclaim_structure_for_icon_description(icon_description)
    Object icon_description;
{
    x_note_fn_call(63,40);
    return reclaim_icon_description_internal_1(icon_description);
}

static Object Qg2_defstruct_structure_name_icon_description_g2_struct;  /* g2-defstruct-structure-name::icon-description-g2-struct */

/* MAKE-PERMANENT-ICON-DESCRIPTION-STRUCTURE-INTERNAL */
Object make_permanent_icon_description_structure_internal()
{
    Object def_structure_icon_description_variable;
    Object defstruct_g2_icon_description_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(63,41);
    def_structure_icon_description_variable = Nil;
    atomic_incff_symval(Qicon_description_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icon_description_variable = Nil;
	gensymed_symbol = (SI_Long)14L;
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
	defstruct_g2_icon_description_variable = the_array;
	SVREF(defstruct_g2_icon_description_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_description_g2_struct;
	def_structure_icon_description_variable = 
		defstruct_g2_icon_description_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icon_description_variable);
}

/* MAKE-ICON-DESCRIPTION-1 */
Object make_icon_description_1(width_of_icon,height_of_icon,
	    x_offset_for_fine_positioning_of_icon_qm,
	    y_offset_for_fine_positioning_of_icon_qm,icon_line_color_qm,
	    icon_x_magnification_qm,icon_y_magnification_qm,
	    icon_line_drawing_description,icon_color_pattern_qm,
	    icon_region_extrema_qm)
    Object width_of_icon, height_of_icon;
    Object x_offset_for_fine_positioning_of_icon_qm;
    Object y_offset_for_fine_positioning_of_icon_qm, icon_line_color_qm;
    Object icon_x_magnification_qm, icon_y_magnification_qm;
    Object icon_line_drawing_description, icon_color_pattern_qm;
    Object icon_region_extrema_qm;
{
    Object def_structure_icon_description_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(63,42);
    def_structure_icon_description_variable = 
	    ISVREF(Chain_of_available_icon_descriptions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icon_description_variable) {
	svref_arg_1 = Chain_of_available_icon_descriptions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_icon_description_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icon_description_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icon_description_g2_struct;
    }
    else
	def_structure_icon_description_variable = 
		make_permanent_icon_description_structure_internal();
    inline_note_allocate_cons(def_structure_icon_description_variable,Nil);
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)1L)) = 
	    width_of_icon;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)2L)) = 
	    height_of_icon;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)3L)) = 
	    x_offset_for_fine_positioning_of_icon_qm;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)4L)) = 
	    y_offset_for_fine_positioning_of_icon_qm;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)5L)) = 
	    icon_line_color_qm;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)6L)) = 
	    icon_x_magnification_qm;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)7L)) = 
	    icon_y_magnification_qm;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)8L)) = 
	    icon_line_drawing_description;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)10L)) = 
	    icon_color_pattern_qm;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)11L)) = 
	    icon_region_extrema_qm;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_icon_description_variable,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(def_structure_icon_description_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(G2gl_object_icon_substitutions_may_be_in_use_p, Qg2gl_object_icon_substitutions_may_be_in_use_p);

/* RECLAIM-ICON-DESCRIPTION */
Object reclaim_icon_description(icon_description)
    Object icon_description;
{
    x_note_fn_call(63,43);
    if (G2gl_object_icon_substitutions_may_be_in_use_p)
	revert_if_g2gl_object_icon_substitution(icon_description);
    return reclaim_icon_description_internal_1(icon_description);
}

/* RECLAIM-LINE-DRAWING-DESCRIPTION */
Object reclaim_line_drawing_description(slot_value)
    Object slot_value;
{
    Object temp, svref_arg_2, temp_1;

    x_note_fn_call(63,44);
    if (SYMBOLP(slot_value) || FIXNUMP(slot_value))
	return VALUES_1(Nil);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L) {
	reclaim_managed_simple_float_array_of_length_1(slot_value);
	return VALUES_1(Nil);
    }
    else if (CONSP(slot_value)) {
	reclaim_line_drawing_description(M_CAR(slot_value));
	reclaim_line_drawing_description(M_CDR(slot_value));
	inline_note_reclaim_cons(slot_value,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = slot_value;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = slot_value;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = slot_value;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = slot_value;
	}
	M_CDR(slot_value) = Nil;
	return VALUES_1(Nil);
    }
    else if (text_string_p(slot_value))
	return reclaim_text_string(slot_value);
    else {
	temp_1 = STRINGP(slot_value) ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else
	    return error((SI_Long)2L,
		    "reclaim line drawing description unexpected value ~s",
		    slot_value);
    }
}

/* ICON-OWNER-CLASS-FUNCTION */
Object icon_owner_class_function(icon_description)
    Object icon_description;
{
    x_note_fn_call(63,45);
    return VALUES_1(ISVREF(icon_description,(SI_Long)12L));
}

/* SET-ICON-OWNER-CLASS */
Object set_icon_owner_class(class_name,icon_description)
    Object class_name, icon_description;
{
    x_note_fn_call(63,46);
    return VALUES_1(SVREF(icon_description,FIX((SI_Long)12L)) = class_name);
}

DEFINE_VARIABLE_WITH_SYMBOL(Icon_renderings_being_bulk_decached, Qicon_renderings_being_bulk_decached);

/* REMOVE-ICON-RENDERING-FROM-ICON-DESCRIPTION */
Object remove_icon_rendering_from_icon_description(icon_rendering,
	    icon_description)
    Object icon_rendering, icon_description;
{
    Object temp, icon_renderings_tail, rest_of_icon_renderings, temp_1;

    x_note_fn_call(63,47);
    temp = Icon_renderings_being_bulk_decached;
    if (temp)
	return VALUES_1(temp);
    else {
	icon_renderings_tail = Nil;
	rest_of_icon_renderings = ISVREF(icon_description,(SI_Long)9L);
      next_loop:
	if ( !TRUEP(rest_of_icon_renderings))
	    goto end_loop;
	if (EQ(CAR(rest_of_icon_renderings),icon_rendering)) {
	    if (icon_renderings_tail) {
		temp_1 = CDR(rest_of_icon_renderings);
		M_CDR(icon_renderings_tail) = temp_1;
	    }
	    else {
		temp_1 = CDR(rest_of_icon_renderings);
		SVREF(icon_description,FIX((SI_Long)9L)) = temp_1;
	    }
	    reclaim_entity_cons_1(rest_of_icon_renderings);
	    return VALUES_0();
	}
	icon_renderings_tail = rest_of_icon_renderings;
	rest_of_icon_renderings = M_CDR(rest_of_icon_renderings);
	goto next_loop;
      end_loop:
      nil:
	return VALUES_1(Qnil);
    }
}

/* RECLAIM-ICON-RENDERINGS */
Object reclaim_icon_renderings(icon_renderings)
    Object icon_renderings;
{
    Object icon_rendering, ab_loop_list_;

    x_note_fn_call(63,48);
    icon_rendering = Nil;
    ab_loop_list_ = icon_renderings;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    icon_rendering = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_icon_rendering_and_raster(icon_rendering);
    goto next_loop;
  end_loop:;
    return reclaim_entity_list_1(icon_renderings);
}

/* RECLAIM-ICON-DESCRIPTION-OF-SLOT-DESCRIPTION */
Object reclaim_icon_description_of_slot_description(icon_description)
    Object icon_description;
{
    x_note_fn_call(63,49);
    return reclaim_icon_description(icon_description);
}

/* ICON-DESCRIPTION-SLOT-INIT-FORM-P */
Object icon_description_slot_init_form_p(slot_init_form)
    Object slot_init_form;
{
    x_note_fn_call(63,50);
    if (SIMPLE_VECTOR_P(slot_init_form))
	return VALUES_1(EQ(ISVREF(slot_init_form,(SI_Long)0L),
		Qg2_defstruct_structure_name_icon_description_g2_struct) ? 
		T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qpolychrome;         /* polychrome */

/* GET-POLYCHROME-HEADER-FROM-ICON-DESCRIPTION-IF-ANY */
Object get_polychrome_header_from_icon_description_if_any(icon_description)
    Object icon_description;
{
    Object line_drawing_description, first_element;

    x_note_fn_call(63,51);
    line_drawing_description = ISVREF(icon_description,(SI_Long)8L);
    first_element = CAR(line_drawing_description);
    if (CONSP(first_element) && EQ(CAR(first_element),Qpolychrome))
	return VALUES_1(first_element);
    else
	return VALUES_1(Nil);
}

/* SINGLE-COLOR-LINE-DRAWING-DESCRIPTION-P */
Object single_color_line_drawing_description_p(line_drawing_description)
    Object line_drawing_description;
{
    Object first_element, temp;

    x_note_fn_call(63,52);
    first_element = CAR(line_drawing_description);
    temp = CONSP(first_element) && EQ(CAR(first_element),Qpolychrome) ? 
	    first_element : Nil;
    temp = CDR(temp);
    return VALUES_1( !TRUEP(CDR(temp)) ? T : Nil);
}

/* SINGLE-COLOR-ICON-DESCRIPTION-P */
Object single_color_icon_description_p(icon_description)
    Object icon_description;
{
    Object temp;

    x_note_fn_call(63,53);
    temp = 
	    get_polychrome_header_from_icon_description_if_any(icon_description);
    temp = CDR(temp);
    return VALUES_1( !TRUEP(CDR(temp)) ? T : Nil);
}

/* LOOKUP-SYMBOL-AS-ICON-VARIABLE */
Object lookup_symbol_as_icon_variable(symbol_to_find)
    Object symbol_to_find;
{
    Object temp;

    x_note_fn_call(63,54);
    temp = getfq_function_no_default(Current_icon_variables_override_plist,
	    symbol_to_find);
    if (temp)
	return VALUES_1(temp);
    else
	return getfq_function_no_default(Current_icon_variables_plist,
		symbol_to_find);
}

static Object Qwidth;              /* width */

static Object Qheight;             /* height */

/* SIMPLE-EVAL-FOR-ICON */
Object simple_eval_for_icon(form)
    Object form;
{
    Object temp;

    x_note_fn_call(63,55);
    if (SYMBOLP(form)) {
	temp = lookup_symbol_as_icon_variable(form);
	if (temp);
	else if (EQ(form,Qwidth))
	    temp = Current_icon_untransformed_width;
	else if (EQ(form,Qheight))
	    temp = Current_icon_untransformed_height;
	else
	    temp = Qnil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(form);
    }
    else if (ATOM(form))
	return VALUES_1(form);
    else if (LISTP(form))
	return simple_apply_for_icon(FIRST(form),REST(form));
    else
	return VALUES_1(Qnil);
}

/* SIMPLE-APPLY-FOR-ICON */
Object simple_apply_for_icon(function,args)
    Object function, args;
{
    Object arg_1, arg_2;

    x_note_fn_call(63,56);
    if (EQ(function,Qplus) || EQ(function,Qminus) || EQ(function,Qstar) || 
	    EQ(function,Qslash)) {
	arg_1 = simple_eval_for_icon(FIRST(args));
	if ( !TRUEP(CDR(args))) {
	    if (EQ(function,Qplus))
		return VALUES_1(arg_1);
	    else if (EQ(function,Qminus))
		return VALUES_1(FIXNUM_NEGATE(arg_1));
	    else
		return VALUES_1(Qnil);
	}
	else {
	    arg_2 = simple_eval_for_icon(SECOND(args));
	    if (EQ(function,Qplus))
		return VALUES_1(FIXNUM_ADD(arg_1,arg_2));
	    else if (EQ(function,Qminus))
		return VALUES_1(FIXNUM_MINUS(arg_1,arg_2));
	    else if (EQ(function,Qstar))
		return VALUES_1(FIXNUM_TIMES(arg_1,arg_2));
	    else if (EQ(function,Qslash)) {
		if (IFIX(arg_2) == (SI_Long)0L)
		    return VALUES_1(FIX((SI_Long)0L));
		else
		    return l_round(arg_1,arg_2);
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qvariables;          /* variables */

/* GET-VARIABLE-SPECIFICATION-IF-ANY */
Object get_variable_specification_if_any(remaining_parse_result)
    Object remaining_parse_result;
{
    Object spec_list, ab_loop_list_, temp;

    x_note_fn_call(63,57);
    spec_list = Nil;
    ab_loop_list_ = remaining_parse_result;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    spec_list = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(spec_list)) {
	if (EQ(M_CAR(spec_list),Qvariables)) {
	    temp = spec_list;
	    goto end_1;
	}
    }
    else if (SYMBOLP(spec_list)) {
	temp = Nil;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qbackground_layer;   /* background-layer */

/* GET-ICON-BACKGROUND-LAYER-IF-ANY */
Object get_icon_background_layer_if_any(remaining_parse_result)
    Object remaining_parse_result;
{
    Object spec_list, ab_loop_list_, temp;

    x_note_fn_call(63,58);
    spec_list = Nil;
    ab_loop_list_ = remaining_parse_result;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    spec_list = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(spec_list)) {
	if (EQ(M_CAR(spec_list),Qbackground_layer)) {
	    temp = spec_list;
	    goto end_1;
	}
    }
    else if (SYMBOLP(spec_list)) {
	temp = Nil;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qstipple;            /* stipple */

/* GET-ICON-STIPPLE-IF-ANY */
Object get_icon_stipple_if_any(remaining_parse_result)
    Object remaining_parse_result;
{
    Object x, ab_loop_list_, temp;

    x_note_fn_call(63,59);
    x = Nil;
    ab_loop_list_ = remaining_parse_result;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(x)) {
	if (EQ(CAR(x),Qstipple)) {
	    temp = SECOND(x);
	    goto end_1;
	}
    }
    else if (SYMBOLP(x)) {
	temp = Nil;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* GET-COMPUTED-VALUES-PLIST */
Object get_computed_values_plist(icon_attributes_plist)
    Object icon_attributes_plist;
{
    Object temp;

    x_note_fn_call(63,60);
    temp = icon_attributes_plist ? 
	    getfq_function_no_default(icon_attributes_plist,Qvariables) : Qnil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_icon_substitution_list, Qcurrent_icon_substitution_list);

/* HELP-SUBSTITUTE-VALUES-FOR-VARIABLES */
Object help_substitute_values_for_variables(x)
    Object x;
{
    Object subst_qm, temp;

    x_note_fn_call(63,61);
    if (ATOM(x)) {
	if (SYMBOLP(x)) {
	    subst_qm = assq_function(x,Current_icon_substitution_list);
	    if (subst_qm)
		return VALUES_1(CADR(subst_qm));
	    else
		return VALUES_1(x);
	}
	else if (STRINGP(x))
	    return copy_text_string(x);
	else
	    return VALUES_1(x);
    }
    else {
	temp = help_substitute_values_for_variables(CAR(x));
	return slot_value_cons_1(temp,
		help_substitute_values_for_variables(CDR(x)));
    }
}

/* SUBSTITUTE-VALUES-FOR-VARIABLES-IN-LINE-DRAWING-DESCRIPTION */
Object substitute_values_for_variables_in_line_drawing_description(line_drawing_description,
	    substitution_list)
    Object line_drawing_description, substitution_list;
{
    Object current_icon_substitution_list;
    Declare_special(1);
    Object result;

    x_note_fn_call(63,62);
    current_icon_substitution_list = substitution_list;
    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_substitution_list,Qcurrent_icon_substitution_list,current_icon_substitution_list,
	    0);
      result = help_substitute_values_for_variables(line_drawing_description);
    POP_SPECIAL();
    return result;
}

/* VARIABLE-SPEC-EQ */
Object variable_spec_eq(spec_1,spec_2)
    Object spec_1, spec_2;
{
    x_note_fn_call(63,63);
    return VALUES_1(EQ(CAR(spec_1),CAR(spec_2)) ? T : Nil);
}

/* SUBSTITUTE-SORTED-COMPUTED-VALUES-IN-VARIABLE-SPEC-LIST */
Object substitute_sorted_computed_values_in_variable_spec_list(sorted_values,
	    default_sorted_values)
    Object sorted_values, default_sorted_values;
{
    Object match_p, result_1, remaining_default_sorted_values;
    Object remaining_sorted_values, default_value, ab_loop_list_;

    x_note_fn_call(63,64);
    match_p = Nil;
    result_1 = Nil;
    remaining_default_sorted_values = default_sorted_values;
    remaining_sorted_values = sorted_values;
  next_loop:
    if ( !TRUEP(remaining_sorted_values)) {
	default_value = Nil;
	ab_loop_list_ = remaining_default_sorted_values;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	default_value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	result_1 = slot_value_cons_1(copy_for_slot_value(default_value),
		result_1);
	goto next_loop_1;
      end_loop:
	result_1 = nreverse(result_1);
	return VALUES_1(result_1);
	return VALUES_1(Qnil);
    }
    else if ( !TRUEP(remaining_default_sorted_values))
	error((SI_Long)2L,
		"default-values-plist was incomplete for the given computed values!\n         Missing variable for ~s~%",
		CAR(remaining_sorted_values));
    else if (variable_spec_eq(CAR(remaining_sorted_values),
	    CAR(remaining_default_sorted_values))) {
	result_1 = 
		slot_value_cons_1(copy_for_slot_value(CAR(remaining_sorted_values)),
		result_1);
	match_p = T;
    }
    else {
	result_1 = 
		slot_value_cons_1(copy_for_slot_value(CAR(remaining_default_sorted_values)),
		result_1);
	match_p = Nil;
    }
    remaining_default_sorted_values = CDR(remaining_default_sorted_values);
    remaining_sorted_values = match_p ? CDR(remaining_sorted_values) : 
	    remaining_sorted_values;
    goto next_loop;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* SORTED-PLIST-MATCH-P */
Object sorted_plist_match_p(plist_1,plist_2)
    Object plist_1, plist_2;
{
    Object variable_spec_1_tail, variable_spec_2_tail, variable_spec_1;
    Object variable_spec_2, ab_loop_iter_flag_, temp;

    x_note_fn_call(63,65);
    variable_spec_1_tail = plist_1;
    variable_spec_2_tail = plist_2;
    variable_spec_1 = Nil;
    variable_spec_2 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(variable_spec_1_tail))
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	variable_spec_2_tail = M_CDR(variable_spec_2_tail);
    if ( !TRUEP(variable_spec_2_tail))
	goto end_loop;
    variable_spec_1 = M_CAR(variable_spec_1_tail);
    variable_spec_2 = M_CAR(variable_spec_2_tail);
    if ( !(INLINE_UNSIGNED_BYTE_16_VECTOR_P(variable_spec_1) != 
	    (SI_Long)0L && 
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(variable_spec_2) != 
	    (SI_Long)0L ? TRUEP(string_eq_w(variable_spec_1,
	    variable_spec_2)) : EQ(variable_spec_1,variable_spec_2))) {
	temp = Nil;
	goto end_1;
    }
    ab_loop_iter_flag_ = Nil;
    variable_spec_1_tail = M_CDR(variable_spec_1_tail);
    goto next_loop;
  end_loop:
    variable_spec_2_tail = CDR(variable_spec_2_tail);
    temp =  !(variable_spec_1_tail || variable_spec_2_tail) ? T : Nil;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object list_constant;       /* # */

/* BITMAP-SIZE-PARAMETERS-FOR-ICON-RENDERING */
Object bitmap_size_parameters_for_icon_rendering(x_scale,y_scale,width,
	    height,reflection_and_rotation,region_extrema,
	    line_drawing_description)
    Object x_scale, y_scale, width, height, reflection_and_rotation;
    Object region_extrema, line_drawing_description;
{
    Object first_element, polychrome_header_qm, polychrome_header_rest_qm;
    Object color_region_and_symbol_pairs, color_region, ab_loop_list_;
    Object region_extrema_entry_qm, bitmap_sizes, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_desetq_, x_offset_for_stored_raster_qm;
    Object y_offset_for_stored_raster_qm, x_max_for_stored_raster_qm;
    Object y_max_for_stored_raster_qm, actual_width, actual_height;
    Object tile_edge_size_in_pixels, rows, columns;
    Object result;

    x_note_fn_call(63,66);
    first_element = CAR(line_drawing_description);
    polychrome_header_qm = CONSP(first_element) && EQ(CAR(first_element),
	    Qpolychrome) ? first_element : Nil;
    polychrome_header_rest_qm = CDR(polychrome_header_qm);
    color_region_and_symbol_pairs = polychrome_header_rest_qm;
    if (color_region_and_symbol_pairs);
    else
	color_region_and_symbol_pairs = list_constant;
    color_region = Nil;
    ab_loop_list_ = color_region_and_symbol_pairs;
    region_extrema_entry_qm = Nil;
    bitmap_sizes = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color_region = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    region_extrema_entry_qm = CAR(region_extrema);
    result = get_x_y_max_and_offset(region_extrema_entry_qm,x_scale,
	    y_scale,width,height,reflection_and_rotation);
    MVS_4(result,x_offset_for_stored_raster_qm,
	    y_offset_for_stored_raster_qm,x_max_for_stored_raster_qm,
	    y_max_for_stored_raster_qm);
    result = raster_dimensions_given_max_and_offset(width,height,
	    x_max_for_stored_raster_qm,x_offset_for_stored_raster_qm,
	    y_max_for_stored_raster_qm,y_offset_for_stored_raster_qm);
    MVS_2(result,actual_width,actual_height);
    tile_edge_size_in_pixels = 
	    compute_tile_size_given_required_area(actual_width,actual_height);
    result = compute_rows_columns_given_tile_size(tile_edge_size_in_pixels,
	    actual_width,actual_height);
    MVS_2(result,rows,columns);
    ab_loopvar__1 = entity_cons_1(entity_list_3(tile_edge_size_in_pixels,
	    rows,columns),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	bitmap_sizes = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    region_extrema = CDR(region_extrema);
    goto next_loop;
  end_loop:
    return VALUES_1(bitmap_sizes);
    return VALUES_1(Qnil);
}

static Object list_constant_1;     /* # */

/* COUNT-BITMAPS-NEEDED-FOR-THIS-ICON-RENDERING */
Object count_bitmaps_needed_for_this_icon_rendering(x_scale,y_scale,
	    width_of_icon,height_of_icon,reflection_and_rotation,
	    icon_region_extrema,line_drawing_description)
    Object x_scale, y_scale, width_of_icon, height_of_icon;
    Object reflection_and_rotation, icon_region_extrema;
    Object line_drawing_description;
{
    Object vector_of_bitmaps, bitmap_size_parameters, tile_edge_size_in_pixels;
    Object rows, columns, ab_loop_list_, ab_loop_iter_flag_, ab_loop_desetq_;
    Object temp, ab_loop_list__1, elem;
    SI_Long count_1, index_1, old_value, x, i, svref_new_value;

    x_note_fn_call(63,67);
    vector_of_bitmaps = allocate_managed_simple_vector(FIX((SI_Long)14L));
    bitmap_size_parameters = 
	    bitmap_size_parameters_for_icon_rendering(x_scale,y_scale,
	    width_of_icon,height_of_icon,reflection_and_rotation,
	    icon_region_extrema,line_drawing_description);
    fill_managed_simple_vector(vector_of_bitmaps,FIX((SI_Long)0L),
	    FIX((SI_Long)0L),FIX((SI_Long)14L));
    tile_edge_size_in_pixels = Nil;
    rows = Nil;
    columns = Nil;
    ab_loop_list_ = bitmap_size_parameters;
    count_1 = (SI_Long)0L;
    index_1 = (SI_Long)0L;
    old_value = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    tile_edge_size_in_pixels = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    rows = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    columns = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	count_1 = count_1 + (SI_Long)1L;
    x = (SI_Long)0L;
    ab_loop_list__1 = list_constant_1;
    i = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    x = IFIX(M_CAR(ab_loop_list__1));
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    if (IFIX(tile_edge_size_in_pixels) == x) {
	index_1 = i;
	goto end_1;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:
    index_1 = (SI_Long)0L;
    goto end_1;
    index_1 = IFIX(Qnil);
  end_1:;
    old_value = IFIX(ISVREF(vector_of_bitmaps,index_1));
    svref_new_value = old_value + IFIX(FIXNUM_TIMES(rows,columns));
    ISVREF(vector_of_bitmaps,index_1) = FIX(svref_new_value);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    elem = Nil;
    ab_loop_list_ = bitmap_size_parameters;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    elem = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_entity_list_1(elem);
    goto next_loop_2;
  end_loop_2:;
    reclaim_entity_list_1(bitmap_size_parameters);
    return VALUES_1(vector_of_bitmaps);
}

static Object list_constant_2;     /* # */

/* BITMAP-MEMORY-USAGE-FOR-ICON-RENDERING */
Object bitmap_memory_usage_for_icon_rendering(array_of_bitmap_counts)
    Object array_of_bitmap_counts;
{
    Object memory_used, total_bitmaps, bitmaps_of_this_size, incff_1_arg;
    SI_Long index_1;

    x_note_fn_call(63,68);
    index_1 = (SI_Long)5L;
    memory_used = FIX((SI_Long)0L);
    total_bitmaps = FIX((SI_Long)0L);
    bitmaps_of_this_size = Nil;
  next_loop:
    if (index_1 > (SI_Long)13L)
	goto end_loop;
    bitmaps_of_this_size = ISVREF(array_of_bitmap_counts,index_1);
    if ((SI_Long)0L < IFIX(bitmaps_of_this_size)) {
	incff_1_arg = bitmaps_of_this_size;
	total_bitmaps = FIXNUM_ADD(total_bitmaps,incff_1_arg);
	incff_1_arg = FIXNUM_TIMES(bitmaps_of_this_size,nth(FIX(index_1),
		list_constant_2));
	memory_used = FIXNUM_ADD(memory_used,incff_1_arg);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_2(total_bitmaps,memory_used);
    return VALUES_1(Qnil);
}

/* DECACHE-THIS-ICON-RENDERING-P */
Object decache_this_icon_rendering_p(desired_sizes_array,candidate_array)
    Object desired_sizes_array, candidate_array;
{
    Object match, all_done;
    SI_Long index_1, desired_number, actual_number, svref_new_value;

    x_note_fn_call(63,69);
    index_1 = (SI_Long)5L;
    desired_number = (SI_Long)0L;
    actual_number = (SI_Long)0L;
    match = Nil;
    all_done = T;
  next_loop:
    if (index_1 > (SI_Long)13L)
	goto end_loop;
    desired_number = IFIX(ISVREF(desired_sizes_array,index_1));
    actual_number = IFIX(ISVREF(candidate_array,index_1));
    if ((SI_Long)0L < desired_number) {
	if (actual_number < desired_number)
	    all_done = Nil;
	if ((SI_Long)0L < actual_number) {
	    match = T;
	    svref_new_value = actual_number < desired_number ? 
		    desired_number - actual_number : (SI_Long)0L;
	    ISVREF(desired_sizes_array,index_1) = FIX(svref_new_value);
	}
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (match) {
	if (all_done)
	    return VALUES_1(T);
	else
	    return VALUES_1(desired_sizes_array);
    }
    else
	return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* DECACHE-EXACT-SIZE-ICON-BITMAPS */
Object decache_exact_size_icon_bitmaps(window_for_icon_rendering,
	    array_of_bitmap_counts)
    Object window_for_icon_rendering, array_of_bitmap_counts;
{
    Object decached_all_desired_sizes_p, desired_bitmap_sizes, gensymed_symbol;
    Object gensymed_symbol_3, svref_new_value, queue_head, icon_rendering;
    Object next, candidate_bitmap_sizes, candidate_window, decache_qm;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;

    x_note_fn_call(63,70);
    decached_all_desired_sizes_p = Nil;
    desired_bitmap_sizes = allocate_managed_simple_vector(FIX((SI_Long)14L));
    gensymed_symbol = array_of_bitmap_counts;
    gensymed_symbol_1 = (SI_Long)0L;
    gensymed_symbol_2 = gensymed_symbol_1 + (SI_Long)14L;
    gensymed_symbol_3 = desired_bitmap_sizes;
    gensymed_symbol_4 = (SI_Long)0L;
  next_loop:
    if ( !(gensymed_symbol_1 < gensymed_symbol_2))
	goto end_loop;
    svref_new_value = ISVREF(gensymed_symbol,gensymed_symbol_1);
    ISVREF(gensymed_symbol_3,gensymed_symbol_4) = svref_new_value;
    gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
    gensymed_symbol_4 = gensymed_symbol_4 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    queue_head = ISVREF(Icon_rendering_lru_queue,(SI_Long)1L);
    icon_rendering =  !EQ(queue_head,Icon_rendering_lru_queue) ? 
	    queue_head : Nil;
    if (icon_rendering);
    else
	icon_rendering = Icon_rendering_lru_queue;
    next = Nil;
  next_loop_1:
    next = ISVREF(icon_rendering,(SI_Long)1L);
    if (EQ(icon_rendering,Icon_rendering_lru_queue))
	goto end_loop_1;
    candidate_bitmap_sizes = ISVREF(icon_rendering,(SI_Long)19L);
    candidate_window = ISVREF(icon_rendering,(SI_Long)17L);
    decache_qm = EQ(window_for_icon_rendering,candidate_window) ? 
	    decache_this_icon_rendering_p(desired_bitmap_sizes,
	    candidate_bitmap_sizes) : Qnil;
    if (decache_qm) {
	decache_icon_rendering(icon_rendering);
	decached_all_desired_sizes_p = EQ(T,decache_qm) ? T : Nil;
	if (decached_all_desired_sizes_p)
	    goto end_decache_exact_size;
    }
    icon_rendering = next;
    goto next_loop_1;
  end_loop_1:;
  end_decache_exact_size:
    reclaim_managed_simple_vector(desired_bitmap_sizes);
    return VALUES_1(decached_all_desired_sizes_p);
}

/* UPDATE-BITMAP-COUNT-AND-DECACHE-IF-APPROPRIATE */
Object update_bitmap_count_and_decache_if_appropriate(window_for_icon_rendering,
	    array_of_bitmap_counts,number_of_bitmaps_for_rendering,
	    bitmap_memory_used_for_rendering)
    Object window_for_icon_rendering, array_of_bitmap_counts;
    Object number_of_bitmaps_for_rendering, bitmap_memory_used_for_rendering;
{
    Object incff_1_arg, svref_new_value, queue_head, icon_rendering, next;

    x_note_fn_call(63,71);
    incff_1_arg = number_of_bitmaps_for_rendering;
    svref_new_value = FIXNUM_ADD(ISVREF(window_for_icon_rendering,
	    (SI_Long)36L),incff_1_arg);
    SVREF(window_for_icon_rendering,FIX((SI_Long)36L)) = svref_new_value;
    incff_1_arg = bitmap_memory_used_for_rendering;
    svref_new_value = FIXNUM_ADD(ISVREF(window_for_icon_rendering,
	    (SI_Long)37L),incff_1_arg);
    SVREF(window_for_icon_rendering,FIX((SI_Long)37L)) = svref_new_value;
    if (time_to_decache_p(window_for_icon_rendering)) {
	if ( 
		!TRUEP(decache_exact_size_icon_bitmaps(window_for_icon_rendering,
		array_of_bitmap_counts))) {
	    if (time_to_decache_p(window_for_icon_rendering)) {
		queue_head = ISVREF(Icon_rendering_lru_queue,(SI_Long)1L);
		icon_rendering =  !EQ(queue_head,Icon_rendering_lru_queue) 
			? queue_head : Nil;
		if (icon_rendering);
		else
		    icon_rendering = Icon_rendering_lru_queue;
		next = Nil;
	      next_loop:
		next = ISVREF(icon_rendering,(SI_Long)1L);
		if (EQ(icon_rendering,Icon_rendering_lru_queue))
		    goto end_loop;
		if (EQ(window_for_icon_rendering,ISVREF(icon_rendering,
			(SI_Long)17L))) {
		    decache_icon_rendering(icon_rendering);
		    time_to_decache_p(window_for_icon_rendering);
		    return VALUES_1(Nil);
		}
		icon_rendering = next;
		goto next_loop;
	      end_loop:
		return VALUES_1(Qnil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qreflection_and_rotation;  /* reflection-and-rotation */

static Object Qy_magnification;    /* y-magnification */

static Object Qx_magnification;    /* x-magnification */

static Object list_constant_3;     /* # */

/* GET-OR-MAKE-ICON-RENDERING */
Object get_or_make_icon_rendering(icon_description,icon_attributes_plist)
    Object icon_description, icon_attributes_plist;
{
    Object reflection_and_rotation_property, y_magnification_property;
    Object x_magnification_property, height_property, width_property;
    Object variables_property, icon_attributes_plist_tail, key, tail, value;
    Object computed_values_plist, temp, x_magnification_qm, y_magnification_qm;
    Object reflection_and_rotation, rotation_by_90_qm;
    Object rotated_x_magnification_qm, rotated_y_magnification_qm;
    Object window_for_icon_rendering, maximum_renderings_for_class;
    Object number_of_renderings_to_delete, deletable_tail_qm, ll, l;
    Object icon_rendering, temp_1, icon_renderings_being_bulk_decached;
    Object rendering, ab_loop_list_, array_of_bitmap_counts;
    Object number_of_bitmaps_for_rendering, bitmap_memory_used_for_rendering;
    SI_Long width_of_icon, height_of_icon, x_scale, y_scale, count_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(63,72);
    reflection_and_rotation_property = Nil;
    y_magnification_property = Nil;
    x_magnification_property = Nil;
    height_property = Nil;
    width_property = Nil;
    variables_property = Nil;
    icon_attributes_plist_tail = icon_attributes_plist;
    key = Nil;
    tail = Nil;
    value = Nil;
  next_loop:
    if ( !TRUEP(icon_attributes_plist_tail))
	goto end_loop;
    key = M_CAR(icon_attributes_plist_tail);
    tail = M_CDR(icon_attributes_plist_tail);
    value = M_CAR(tail);
    if (EQ(key,Qreflection_and_rotation))
	reflection_and_rotation_property = value;
    else if (EQ(key,Qy_magnification))
	y_magnification_property = value;
    else if (EQ(key,Qx_magnification))
	x_magnification_property = value;
    else if (EQ(key,Qheight))
	height_property = value;
    else if (EQ(key,Qwidth))
	width_property = value;
    else if (EQ(key,Qvariables))
	variables_property = value;
    icon_attributes_plist_tail = M_CDR(tail);
    goto next_loop;
  end_loop:;
    computed_values_plist = variables_property;
    temp = width_property;
    if (temp);
    else
	temp = ISVREF(icon_description,(SI_Long)1L);
    width_of_icon = IFIX(temp);
    temp = height_property;
    if (temp);
    else
	temp = ISVREF(icon_description,(SI_Long)2L);
    height_of_icon = IFIX(temp);
    x_magnification_qm = x_magnification_property;
    if (x_magnification_qm);
    else
	x_magnification_qm = ISVREF(icon_description,(SI_Long)6L);
    y_magnification_qm = y_magnification_property;
    if (y_magnification_qm);
    else
	y_magnification_qm = ISVREF(icon_description,(SI_Long)7L);
    reflection_and_rotation = reflection_and_rotation_property;
    rotation_by_90_qm = reflection_and_rotation ? 
	    memq_function(reflection_and_rotation,list_constant_3) : Qnil;
    rotated_x_magnification_qm = rotation_by_90_qm ? y_magnification_qm : 
	    x_magnification_qm;
    rotated_y_magnification_qm = rotation_by_90_qm ? x_magnification_qm : 
	    y_magnification_qm;
    x_scale = rotated_x_magnification_qm ? 
	    IFIX(FIXNUM_TIMES(Current_image_x_scale,
	    rotated_x_magnification_qm)) + (SI_Long)128L >>  -  - 
	    (SI_Long)8L : IFIX(Current_image_x_scale);
    y_scale = rotated_y_magnification_qm ? 
	    IFIX(FIXNUM_TIMES(Current_image_y_scale,
	    rotated_y_magnification_qm)) + (SI_Long)128L >>  -  - 
	    (SI_Long)8L : IFIX(Current_image_y_scale);
    window_for_icon_rendering = Current_window;
    result = icon_decaching_parameters(ISVREF(icon_description,(SI_Long)12L));
    MVS_2(result,maximum_renderings_for_class,number_of_renderings_to_delete);
    deletable_tail_qm = Nil;
    ll = Nil;
    count_1 = (SI_Long)0L;
    l = ISVREF(icon_description,(SI_Long)9L);
    icon_rendering = Nil;
  next_loop_1:
    if ( !TRUEP(l))
	goto end_loop_1;
    icon_rendering = CAR(l);
    if (x_scale == IFIX(ISVREF(icon_rendering,(SI_Long)3L)) && y_scale == 
	    IFIX(ISVREF(icon_rendering,(SI_Long)4L)) && 
	    EQ(reflection_and_rotation,ISVREF(icon_rendering,(SI_Long)5L)) 
	    && EQ(ISVREF(icon_rendering,(SI_Long)17L),
	    window_for_icon_rendering) && width_of_icon == 
	    IFIX(ISVREF(icon_rendering,(SI_Long)13L)) && height_of_icon == 
	    IFIX(ISVREF(icon_rendering,(SI_Long)14L)) && 
	    sorted_plist_match_p(computed_values_plist,
	    ISVREF(icon_rendering,(SI_Long)9L))) {
	if (ll) {
	    temp_1 = CDR(l);
	    M_CDR(ll) = temp_1;
	    temp_1 = ISVREF(icon_description,(SI_Long)9L);
	    M_CDR(l) = temp_1;
	    SVREF(icon_description,FIX((SI_Long)9L)) = l;
	}
	temp = icon_rendering;
	goto end_1;
    }
    if (count_1 >= IFIX(number_of_renderings_to_delete)) {
	if (deletable_tail_qm)
	    deletable_tail_qm = M_CDR(deletable_tail_qm);
	else
	    deletable_tail_qm = ISVREF(icon_description,(SI_Long)9L);
    }
    ll = l;
    count_1 = count_1 + (SI_Long)1L;
    l = M_CDR(l);
    goto next_loop_1;
  end_loop_1:
    if (count_1 >= IFIX(maximum_renderings_for_class)) {
	icon_renderings_being_bulk_decached = CDR(deletable_tail_qm);
	PUSH_SPECIAL_WITH_SYMBOL(Icon_renderings_being_bulk_decached,Qicon_renderings_being_bulk_decached,icon_renderings_being_bulk_decached,
		0);
	  M_CDR(deletable_tail_qm) = Nil;
	  rendering = Nil;
	  ab_loop_list_ = Icon_renderings_being_bulk_decached;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  rendering = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  decache_icon_rendering(rendering);
	  goto next_loop_2;
	end_loop_2:;
	  reclaim_entity_list_1(Icon_renderings_being_bulk_decached);
	POP_SPECIAL();
    }
    temp = Qnil;
  end_1:;
    if (temp);
    else {
	array_of_bitmap_counts = 
		count_bitmaps_needed_for_this_icon_rendering(FIX(x_scale),
		FIX(y_scale),FIX(width_of_icon),FIX(height_of_icon),
		reflection_and_rotation,ISVREF(icon_description,
		(SI_Long)11L),ISVREF(icon_description,(SI_Long)8L));
	result = bitmap_memory_usage_for_icon_rendering(array_of_bitmap_counts);
	MVS_2(result,number_of_bitmaps_for_rendering,
		bitmap_memory_used_for_rendering);
	update_bitmap_count_and_decache_if_appropriate(window_for_icon_rendering,
		array_of_bitmap_counts,number_of_bitmaps_for_rendering,
		bitmap_memory_used_for_rendering);
	icon_rendering = create_icon_rendering(icon_description,
		copy_tree_including_leaves_using_gensym_conses(computed_values_plist),
		window_for_icon_rendering,FIX(x_scale),FIX(y_scale),
		FIX(width_of_icon),FIX(height_of_icon),
		reflection_and_rotation,rotation_by_90_qm,
		array_of_bitmap_counts,number_of_bitmaps_for_rendering,
		bitmap_memory_used_for_rendering);
	temp_1 = entity_cons_1(icon_rendering,ISVREF(icon_description,
		(SI_Long)9L));
	SVREF(icon_description,FIX((SI_Long)9L)) = temp_1;
	temp = icon_rendering;
    }
    return VALUES_1(temp);
}

/* CREATE-ICON-RENDERING */
Object create_icon_rendering(icon_description,computed_values_plist,
	    window_for_icon_rendering,x_scale,y_scale,width_of_icon,
	    height_of_icon,reflection_and_rotation,rotation_by_90_qm,
	    array_of_bitmap_counts,number_of_bitmaps,memory_used_by_bitmaps)
    Object icon_description, computed_values_plist, window_for_icon_rendering;
    Object x_scale, y_scale, width_of_icon, height_of_icon;
    Object reflection_and_rotation, rotation_by_90_qm, array_of_bitmap_counts;
    Object number_of_bitmaps, memory_used_by_bitmaps;
{
    Object scale, value, line_drawing_description, ok_qm;
    Object information_if_not_ok_or_extrema_if_ok_qm, first_element, temp;
    SI_Long overflow_units, gensymed_symbol, unshifted_result;
    SI_Long gensymed_symbol_1, width_of_rendering_structure;
    SI_Long height_of_rendering_structure, temp_1;
    Object result;

    x_note_fn_call(63,73);
    overflow_units = MAX((SI_Long)1L,(SI_Long)1L);
    scale = x_scale;
    value = rotation_by_90_qm ? height_of_icon : width_of_icon;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(scale,value));
    gensymed_symbol_1 = overflow_units;
    width_of_rendering_structure = gensymed_symbol + gensymed_symbol_1;
    scale = y_scale;
    value = rotation_by_90_qm ? width_of_icon : height_of_icon;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(scale,value));
    gensymed_symbol_1 = overflow_units;
    height_of_rendering_structure = gensymed_symbol + gensymed_symbol_1;
    line_drawing_description = ISVREF(icon_description,(SI_Long)8L);
    result = valid_line_drawing_description_p(width_of_icon,height_of_icon,
	    line_drawing_description,computed_values_plist);
    MVS_2(result,ok_qm,information_if_not_ok_or_extrema_if_ok_qm);
    if (ok_qm) {
	first_element = CAR(line_drawing_description);
	temp = CONSP(first_element) && EQ(CAR(first_element),Qpolychrome) ?
		 first_element : Nil;
	temp_1 = IFIX(length(CDR(temp)));
	temp = make_decacheable_icon_rendering(18,line_drawing_description,
		computed_values_plist,x_scale,y_scale,
		reflection_and_rotation,width_of_icon,height_of_icon,
		FIX(width_of_rendering_structure),
		FIX(height_of_rendering_structure),FIX(MAX((SI_Long)1L,
		temp_1)),icon_description,window_for_icon_rendering,
		information_if_not_ok_or_extrema_if_ok_qm,
		array_of_bitmap_counts,number_of_bitmaps,
		memory_used_by_bitmaps,
		FIX(MAX(width_of_rendering_structure,
		height_of_rendering_structure)),T);
    }
    else
	temp = Qt;
    return VALUES_1(temp);
}

static Object Qx11_pixmap;         /* x11-pixmap */

static Object Qicp;                /* icp */

/* MAKE-RENDERING-STRUCTURE */
Object make_rendering_structure(gensym_window_in_non_icp_case_qm,
	    icon_rendering)
    Object gensym_window_in_non_icp_case_qm, icon_rendering;
{
    Object line_drawing_description, sorted_computed_variables, first_element;
    Object polychrome_header_qm, polychrome_header_rest_qm;
    Object line_drawing_description_following_header;
    Object color_region_and_symbol_pairs, width, height, x_scale, y_scale;
    Object reflection_and_rotation, icon_stipple_qm;
    Object minimum_width_for_scratchpad_raster;
    Object minimum_height_for_scratchpad_raster, rest_of_region_extrema;
    Object color_region, ab_loop_list_, region_extrema_entry_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_;
    Object x_offset_for_stored_raster_qm, y_offset_for_stored_raster_qm;
    Object x_max_for_stored_raster_qm, y_max_for_stored_raster_qm;
    Object gensymed_symbol, scratchpad_raster_type, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, new_region_bounds_and_raster;
    Object current_scratchpad_raster_type, current_scratchpad_raster_tiled_p;
    Object current_scratchpad_raster_width, current_scratchpad_raster_height;
    Object current_scratchpad_raster_depth, on_monochrome_raster_list_p;
    Object current_x_offset_for_stored_raster_qm;
    Object current_y_offset_for_stored_raster_qm;
    Object current_x_max_for_stored_raster_qm;
    Object current_y_max_for_stored_raster_qm, current_scratchpad_raster, temp;
    Object new_stored_raster;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(11);
    Object result;

    x_note_fn_call(63,74);
    SAVE_STACK();
    line_drawing_description = ISVREF(icon_rendering,(SI_Long)8L);
    sorted_computed_variables = ISVREF(icon_rendering,(SI_Long)9L);
    first_element = CAR(line_drawing_description);
    polychrome_header_qm = CONSP(first_element) && EQ(CAR(first_element),
	    Qpolychrome) ? first_element : Nil;
    polychrome_header_rest_qm = CDR(polychrome_header_qm);
    line_drawing_description_following_header = polychrome_header_qm ? 
	    CDR(line_drawing_description) : line_drawing_description;
    color_region_and_symbol_pairs = polychrome_header_rest_qm;
    if (color_region_and_symbol_pairs);
    else
	color_region_and_symbol_pairs = list_constant;
    width = ISVREF(icon_rendering,(SI_Long)13L);
    height = ISVREF(icon_rendering,(SI_Long)14L);
    x_scale = ISVREF(icon_rendering,(SI_Long)3L);
    y_scale = ISVREF(icon_rendering,(SI_Long)4L);
    reflection_and_rotation = ISVREF(icon_rendering,(SI_Long)5L);
    icon_stipple_qm = get_icon_stipple_if_any(line_drawing_description);
    minimum_width_for_scratchpad_raster = ISVREF(icon_rendering,(SI_Long)10L);
    minimum_height_for_scratchpad_raster = ISVREF(icon_rendering,(SI_Long)11L);
    if (gensym_window_in_non_icp_case_qm) {
	rest_of_region_extrema = ISVREF(icon_rendering,(SI_Long)18L);
	color_region = Nil;
	ab_loop_list_ = color_region_and_symbol_pairs;
	region_extrema_entry_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	color_region = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	region_extrema_entry_qm = CAR(rest_of_region_extrema);
	result = get_x_y_max_and_offset(region_extrema_entry_qm,x_scale,
		y_scale,width,height,reflection_and_rotation);
	MVS_4(result,x_offset_for_stored_raster_qm,
		y_offset_for_stored_raster_qm,x_max_for_stored_raster_qm,
		y_max_for_stored_raster_qm);
	gensymed_symbol = gensym_window_in_non_icp_case_qm;
	scratchpad_raster_type = ISVREF(gensymed_symbol,(SI_Long)23L);
	if (EQ(scratchpad_raster_type,Qx11_pixmap)) {
	    gensymed_symbol = x_offset_for_stored_raster_qm;
	    gensymed_symbol_1 = y_offset_for_stored_raster_qm;
	    gensymed_symbol_2 = x_max_for_stored_raster_qm;
	    gensymed_symbol_3 = y_max_for_stored_raster_qm;
	    new_region_bounds_and_raster = make_region_bounds_and_raster_1();
	    LOCK(Scratchpad_raster);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_scratchpad_raster_type = 
			ISVREF(gensym_window_in_non_icp_case_qm,(SI_Long)23L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			10);
		  current_scratchpad_raster_tiled_p = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_tiled_p,Qcurrent_scratchpad_raster_tiled_p,current_scratchpad_raster_tiled_p,
			  9);
		    current_scratchpad_raster_width = 
			    minimum_width_for_scratchpad_raster;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_width,Qcurrent_scratchpad_raster_width,current_scratchpad_raster_width,
			    8);
		      current_scratchpad_raster_height = 
			      minimum_height_for_scratchpad_raster;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_height,Qcurrent_scratchpad_raster_height,current_scratchpad_raster_height,
			      7);
			current_scratchpad_raster_depth = FIX((SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_depth,Qcurrent_scratchpad_raster_depth,current_scratchpad_raster_depth,
				6);
			  on_monochrome_raster_list_p = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(On_monochrome_raster_list_p,Qon_monochrome_raster_list_p,on_monochrome_raster_list_p,
				  5);
			    current_x_offset_for_stored_raster_qm = 
				    gensymed_symbol;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_x_offset_for_stored_raster_qm,Qcurrent_x_offset_for_stored_raster_qm,current_x_offset_for_stored_raster_qm,
				    4);
			      current_y_offset_for_stored_raster_qm = 
				      gensymed_symbol_1;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_y_offset_for_stored_raster_qm,Qcurrent_y_offset_for_stored_raster_qm,current_y_offset_for_stored_raster_qm,
				      3);
				current_x_max_for_stored_raster_qm = 
					gensymed_symbol_2;
				PUSH_SPECIAL_WITH_SYMBOL(Current_x_max_for_stored_raster_qm,Qcurrent_x_max_for_stored_raster_qm,current_x_max_for_stored_raster_qm,
					2);
				  current_y_max_for_stored_raster_qm = 
					  gensymed_symbol_3;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_y_max_for_stored_raster_qm,Qcurrent_y_max_for_stored_raster_qm,current_y_max_for_stored_raster_qm,
					  1);
				    current_scratchpad_raster = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster,Qcurrent_scratchpad_raster,current_scratchpad_raster,
					    0);
				      initialize_scratchpad_raster(gensym_window_in_non_icp_case_qm,
					      minimum_width_for_scratchpad_raster,
					      minimum_height_for_scratchpad_raster,
					      FIX((SI_Long)1L),Nil);
				      paint_one_bitmap_for_icon_on_scratchpad_raster(color_region,
					      line_drawing_description_following_header,
					      width,height,x_scale,y_scale,
					      FIX((SI_Long)1L),
					      reflection_and_rotation,
					      sorted_computed_variables,
					      minimum_width_for_scratchpad_raster,
					      minimum_height_for_scratchpad_raster,
					      icon_stipple_qm);
				      temp = 
					      convert_current_scratchpad_raster_to_stored_raster(gensym_window_in_non_icp_case_qm,
					      minimum_width_for_scratchpad_raster,
					      minimum_height_for_scratchpad_raster,
					      FIX((SI_Long)1L),Nil);
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
		SAVE_VALUES(VALUES_1(temp));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Scratchpad_raster);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    new_stored_raster = result;
	    SVREF(new_region_bounds_and_raster,FIX((SI_Long)1L)) = 
		    gensymed_symbol;
	    SVREF(new_region_bounds_and_raster,FIX((SI_Long)2L)) = 
		    gensymed_symbol_1;
	    SVREF(new_region_bounds_and_raster,FIX((SI_Long)3L)) = 
		    gensymed_symbol_2;
	    SVREF(new_region_bounds_and_raster,FIX((SI_Long)4L)) = 
		    gensymed_symbol_3;
	    SVREF(new_region_bounds_and_raster,FIX((SI_Long)5L)) = 
		    new_stored_raster;
	    temp = new_region_bounds_and_raster;
	}
	else {
	    new_region_bounds_and_raster = make_region_bounds_and_raster_1();
	    LOCK(Scratchpad_raster);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_scratchpad_raster_type = 
			ISVREF(gensym_window_in_non_icp_case_qm,(SI_Long)23L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			10);
		  current_scratchpad_raster_tiled_p = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_tiled_p,Qcurrent_scratchpad_raster_tiled_p,current_scratchpad_raster_tiled_p,
			  9);
		    current_scratchpad_raster_width = 
			    minimum_width_for_scratchpad_raster;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_width,Qcurrent_scratchpad_raster_width,current_scratchpad_raster_width,
			    8);
		      current_scratchpad_raster_height = 
			      minimum_height_for_scratchpad_raster;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_height,Qcurrent_scratchpad_raster_height,current_scratchpad_raster_height,
			      7);
			current_scratchpad_raster_depth = FIX((SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_depth,Qcurrent_scratchpad_raster_depth,current_scratchpad_raster_depth,
				6);
			  on_monochrome_raster_list_p = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(On_monochrome_raster_list_p,Qon_monochrome_raster_list_p,on_monochrome_raster_list_p,
				  5);
			    current_x_offset_for_stored_raster_qm = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_x_offset_for_stored_raster_qm,Qcurrent_x_offset_for_stored_raster_qm,current_x_offset_for_stored_raster_qm,
				    4);
			      current_y_offset_for_stored_raster_qm = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_y_offset_for_stored_raster_qm,Qcurrent_y_offset_for_stored_raster_qm,current_y_offset_for_stored_raster_qm,
				      3);
				current_x_max_for_stored_raster_qm = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Current_x_max_for_stored_raster_qm,Qcurrent_x_max_for_stored_raster_qm,current_x_max_for_stored_raster_qm,
					2);
				  current_y_max_for_stored_raster_qm = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_y_max_for_stored_raster_qm,Qcurrent_y_max_for_stored_raster_qm,current_y_max_for_stored_raster_qm,
					  1);
				    current_scratchpad_raster = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster,Qcurrent_scratchpad_raster,current_scratchpad_raster,
					    0);
				      initialize_scratchpad_raster(gensym_window_in_non_icp_case_qm,
					      minimum_width_for_scratchpad_raster,
					      minimum_height_for_scratchpad_raster,
					      FIX((SI_Long)1L),Nil);
				      paint_one_bitmap_for_icon_on_scratchpad_raster(color_region,
					      line_drawing_description_following_header,
					      width,height,x_scale,y_scale,
					      FIX((SI_Long)1L),
					      reflection_and_rotation,
					      sorted_computed_variables,
					      minimum_width_for_scratchpad_raster,
					      minimum_height_for_scratchpad_raster,
					      icon_stipple_qm);
				      temp = 
					      convert_current_scratchpad_raster_to_stored_raster(gensym_window_in_non_icp_case_qm,
					      minimum_width_for_scratchpad_raster,
					      minimum_height_for_scratchpad_raster,
					      FIX((SI_Long)1L),Nil);
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
		SAVE_VALUES(VALUES_1(temp));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Scratchpad_raster);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    new_stored_raster = result;
	    SVREF(new_region_bounds_and_raster,FIX((SI_Long)5L)) = 
		    new_stored_raster;
	    temp = new_region_bounds_and_raster;
	}
	ab_loopvar__2 = gensym_cons_1(temp,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	rest_of_region_extrema = CDR(rest_of_region_extrema);
	goto next_loop;
      end_loop:
	RESTORE_STACK();
	return VALUES_1(ab_loopvar_);
	RESTORE_STACK();
	return VALUES_1(Qnil);
    }
    else {
	current_scratchpad_raster_type = Qicp;
	PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		0);
	  rest_of_region_extrema = ISVREF(icon_rendering,(SI_Long)18L);
	  color_region = Nil;
	  ab_loop_list_ = color_region_and_symbol_pairs;
	  region_extrema_entry_qm = Nil;
	  ab_loop_desetq_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  color_region = CAR(ab_loop_desetq_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  region_extrema_entry_qm = CAR(rest_of_region_extrema);
	  result = get_x_y_max_and_offset(region_extrema_entry_qm,x_scale,
		  y_scale,width,height,reflection_and_rotation);
	  MVS_4(result,x_offset_for_stored_raster_qm,
		  y_offset_for_stored_raster_qm,x_max_for_stored_raster_qm,
		  y_max_for_stored_raster_qm);
	  if (x_offset_for_stored_raster_qm)
	      send_icp_region_extrema_for_stored_raster(FIX(MAX((SI_Long)0L,
		      IFIX(x_offset_for_stored_raster_qm))),
		      FIX(MAX((SI_Long)0L,
		      IFIX(y_offset_for_stored_raster_qm))),
		      x_max_for_stored_raster_qm,y_max_for_stored_raster_qm);
	  send_icp_end_message_block();
	  paint_one_bitmap_for_icon_on_scratchpad_raster(color_region,
		  line_drawing_description_following_header,width,height,
		  x_scale,y_scale,FIX((SI_Long)1L),reflection_and_rotation,
		  sorted_computed_variables,
		  minimum_width_for_scratchpad_raster,
		  minimum_height_for_scratchpad_raster,icon_stipple_qm);
	  send_icp_end_message_block();
	  rest_of_region_extrema = CDR(rest_of_region_extrema);
	  goto next_loop_1;
	end_loop_1:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Printing_icon_current_region_index_qm, Qprinting_icon_current_region_index_qm);

static Object Qforeground;         /* foreground */

static Object Qbackground;         /* background */

static Object Qworkspace_foreground;  /* workspace-foreground */

static Object Qtransparent;        /* transparent */

static Object Qlines;              /* lines */

static Object Qoutline;            /* outline */

static Object Qsolid_rectangle;    /* solid-rectangle */

static Object Qcircle;             /* circle */

static Object Qfilled_circle;      /* filled-circle */

static Object Qrounded_rectangle;  /* rounded-rectangle */

static Object Qfilled_rounded_rectangle;  /* filled-rounded-rectangle */

static Object Qpoint;              /* point */

static Object Qstippled_area;      /* stippled-area */

static Object Qnormal;             /* normal */

static Object Qclockwise_90;       /* clockwise-90 */

static Object Qclockwise_270;      /* clockwise-270 */

static Object Qreflected_clockwise_270;  /* reflected-clockwise-270 */

static Object Qclockwise_180;      /* clockwise-180 */

static Object Qreflected_clockwise_90;  /* reflected-clockwise-90 */

static Object Qreflected;          /* reflected */

static Object Qreflected_clockwise_180;  /* reflected-clockwise-180 */

static Object Qfilled_polygon;     /* filled-polygon */

static Object Qimage;              /* image */

static Object Qtext;               /* text */

/* PAINT-ONE-BITMAP-FOR-ICON-ON-SCRATCHPAD-RASTER */
Object paint_one_bitmap_for_icon_on_scratchpad_raster(color_region_to_paint_or_the_icon_color_pattern,
	    line_drawing_description_following_header,width,height,x_scale,
	    y_scale,foreground_icon_line_color_value,
	    reflection_and_rotation,sorted_computed_variables,
	    width_for_icon,height_for_icon,global_icon_stipple_qm)
    Object color_region_to_paint_or_the_icon_color_pattern;
    Object line_drawing_description_following_header, width, height, x_scale;
    Object y_scale, foreground_icon_line_color_value, reflection_and_rotation;
    Object sorted_computed_variables, width_for_icon, height_for_icon;
    Object global_icon_stipple_qm;
{
    Object temp, default_variables, started_painting_p, icon_line_color_value;
    Object points, line_drawing_directive, icon_stipple_qm;
    Object description_element, ab_loop_list_, region_info, ab_loop_list__1;
    Object ab_loop_iter_flag_, color_or_metacolor;
    Object current_icon_untransformed_width, current_icon_untransformed_height;
    Object current_icon_variables_plist, current_icon_variables_override_plist;
    Object point, temp_1, temp_2, temp_3, first_point, second_point;
    Object third_point, temp_4, temp_5, x1, y1_1, x2, y2;
    Object reflection_and_rotation_qm, x1_temp, x2_temp, scale, value_1;
    Object image_name, point_qm, scale_qm, x, y, new_x_scale, new_y_scale;
    Object text_reflection_and_rotation;
    SI_Long stipple_area_left_edge, stipple_area_top_edge;
    SI_Long stipple_area_right_edge, stipple_area_bottom_edge, region_index;
    SI_Long temp_6, value, unshifted_result;
    Declare_special(4);

    x_note_fn_call(63,75);
    temp = 
	    get_variable_specification_if_any(line_drawing_description_following_header);
    default_variables = CDR(temp);
    started_painting_p = 
	    CONSP(color_region_to_paint_or_the_icon_color_pattern) ? T : Nil;
    icon_line_color_value = 
	    CONSP(color_region_to_paint_or_the_icon_color_pattern) || 
	    EQ(color_region_to_paint_or_the_icon_color_pattern,
	    Qforeground) ? foreground_icon_line_color_value : FIX((SI_Long)0L);
    points = Nil;
    line_drawing_directive = Nil;
    icon_stipple_qm = global_icon_stipple_qm;
    stipple_area_left_edge = (SI_Long)0L;
    stipple_area_top_edge = (SI_Long)0L;
    stipple_area_right_edge = IFIX(width_for_icon);
    stipple_area_bottom_edge = IFIX(height_for_icon);
    description_element = Nil;
    ab_loop_list_ = line_drawing_description_following_header;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    description_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ATOM(description_element)) {
	if ( !TRUEP(global_icon_stipple_qm)) {
	    if (icon_stipple_qm) {
		if (FIXNUM_LT(Icp_window_protocol_supports_raster_stipples,
			ISVREF(Current_window,(SI_Long)11L)))
		    stipple_rectangle_in_current_scratchpad_raster(FIX(stipple_area_left_edge),
			    FIX(stipple_area_top_edge),
			    FIX(stipple_area_right_edge),
			    FIX(stipple_area_bottom_edge),
			    foreground_icon_line_color_value,icon_stipple_qm);
		icon_stipple_qm = Nil;
	    }
	}
	if (CONSP(color_region_to_paint_or_the_icon_color_pattern)) {
	    if (T) {
		region_info = Nil;
		ab_loop_list__1 = 
			color_region_to_paint_or_the_icon_color_pattern;
		region_index = (SI_Long)0L;
		ab_loop_iter_flag_ = T;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		region_info = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if ( !TRUEP(ab_loop_iter_flag_))
		    region_index = region_index + (SI_Long)1L;
		temp = CAR(region_info);
		if (EQL(description_element,temp)) {
		    Printing_icon_current_region_index_qm = FIX(region_index);
		    color_or_metacolor = CDR(region_info);
		    if (EQ(color_or_metacolor,Qbackground))
			temp = Current_background_color_value;
		    else if (EQ(color_or_metacolor,Qforeground) || 
			    EQ(color_or_metacolor,Qworkspace_foreground))
			temp = Current_foreground_color_value;
		    else if (EQ(color_or_metacolor,Qtransparent))
			temp = Current_background_color_value;
		    else
			temp = map_to_color_value(color_or_metacolor);
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		goto next_loop_1;
	      end_loop_1:
		temp = Qnil;
	      end_1:;
		if (temp);
		else
		    temp = FIX((SI_Long)0L);
		icon_line_color_value = temp;
	    }
	    else
		icon_line_color_value = Nil;
	}
	else if (EQ(description_element,
		color_region_to_paint_or_the_icon_color_pattern))
	    icon_line_color_value = foreground_icon_line_color_value;
	else
	    icon_line_color_value = FIX((SI_Long)0L);
    }
    else if (started_painting_p || IFIX(icon_line_color_value) != 
		(SI_Long)0L) {
	started_painting_p = T;
	points = CDR(description_element);
	line_drawing_directive = FIRST(description_element);
	current_icon_untransformed_width = width;
	PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
		3);
	  current_icon_untransformed_height = height;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
		  2);
	    current_icon_variables_plist = default_variables;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
		    1);
	      current_icon_variables_override_plist = 
		      sorted_computed_variables;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
		      0);
		if (EQ(line_drawing_directive,Qlines) || 
			EQ(line_drawing_directive,Qoutline))
		    orient_and_scale_and_paint_polyline(points,
			    EQ(line_drawing_directive,Qoutline) ? T : Nil,
			    x_scale,y_scale,width,height,
			    reflection_and_rotation,icon_line_color_value);
		else if (EQ(line_drawing_directive,Qsolid_rectangle)) {
		    point = FIRST(points);
		    temp = FIXNUMP(FIRST(point)) ? FIRST(point) : 
			    simple_eval_for_icon(FIRST(point));
		    point = FIRST(points);
		    temp_1 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
			    simple_eval_for_icon(SECOND(point));
		    point = SECOND(points);
		    temp_2 = FIXNUMP(FIRST(point)) ? FIRST(point) : 
			    simple_eval_for_icon(FIRST(point));
		    point = SECOND(points);
		    temp_3 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
			    simple_eval_for_icon(SECOND(point));
		    orient_and_scale_and_paint_solid_rectangle(temp,temp_1,
			    temp_2,temp_3,x_scale,y_scale,width,height,
			    reflection_and_rotation,icon_line_color_value);
		}
		else if (EQ(line_drawing_directive,Qcircle) || 
			EQ(line_drawing_directive,Qfilled_circle)) {
		    first_point = FIRST(points);
		    second_point = SECOND(points);
		    third_point = THIRD(points);
		    temp = FIXNUMP(FIRST(first_point)) ? 
			    FIRST(first_point) : 
			    simple_eval_for_icon(FIRST(first_point));
		    temp_1 = FIXNUMP(SECOND(first_point)) ? 
			    SECOND(first_point) : 
			    simple_eval_for_icon(SECOND(first_point));
		    temp_2 = FIXNUMP(FIRST(second_point)) ? 
			    FIRST(second_point) : 
			    simple_eval_for_icon(FIRST(second_point));
		    temp_3 = FIXNUMP(SECOND(second_point)) ? 
			    SECOND(second_point) : 
			    simple_eval_for_icon(SECOND(second_point));
		    temp_4 = FIXNUMP(FIRST(third_point)) ? 
			    FIRST(third_point) : 
			    simple_eval_for_icon(FIRST(third_point));
		    temp_5 = FIXNUMP(SECOND(third_point)) ? 
			    SECOND(third_point) : 
			    simple_eval_for_icon(SECOND(third_point));
		    orient_and_scale_and_paint_arc_or_circle(temp,temp_1,
			    temp_2,temp_3,temp_4,temp_5,x_scale,y_scale,
			    width,height,reflection_and_rotation,
			    icon_line_color_value,T,
			    EQ(line_drawing_directive,Qfilled_circle) ? T :
			     Nil);
		}
		else if (EQ(line_drawing_directive,Qrounded_rectangle) || 
			EQ(line_drawing_directive,Qfilled_rounded_rectangle)) {
		    point = FIRST(points);
		    temp = FIXNUMP(FIRST(point)) ? FIRST(point) : 
			    simple_eval_for_icon(FIRST(point));
		    point = FIRST(points);
		    temp_1 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
			    simple_eval_for_icon(SECOND(point));
		    point = SECOND(points);
		    temp_2 = FIXNUMP(FIRST(point)) ? FIRST(point) : 
			    simple_eval_for_icon(FIRST(point));
		    point = SECOND(points);
		    temp_3 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
			    simple_eval_for_icon(SECOND(point));
		    orient_and_scale_and_paint_rounded_rectangle(temp,
			    temp_1,temp_2,temp_3,x_scale,y_scale,width,
			    height,reflection_and_rotation,
			    icon_line_color_value,
			    EQ(line_drawing_directive,
			    Qfilled_rounded_rectangle) ? T : Nil);
		}
		else if (EQ(line_drawing_directive,Qpoint)) {
		    point = FIRST(points);
		    temp = FIXNUMP(FIRST(point)) ? FIRST(point) : 
			    simple_eval_for_icon(FIRST(point));
		    point = FIRST(points);
		    temp_1 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
			    simple_eval_for_icon(SECOND(point));
		    orient_and_scale_and_paint_point(temp,temp_1,x_scale,
			    y_scale,width,height,reflection_and_rotation,
			    icon_line_color_value);
		}
		else if (EQ(line_drawing_directive,Qstippled_area)) {
		    if ( !TRUEP(global_icon_stipple_qm)) {
			if (IFIX(icon_line_color_value) != (SI_Long)0L) {
			    icon_stipple_qm = SECOND(description_element);
			    if (CDDR(description_element)) {
				point = THIRD(description_element);
				x1 = FIXNUMP(FIRST(point)) ? FIRST(point) :
					 simple_eval_for_icon(FIRST(point));
				point = THIRD(description_element);
				y1_1 = FIXNUMP(SECOND(point)) ? 
					SECOND(point) : 
					simple_eval_for_icon(SECOND(point));
				point = FOURTH(description_element);
				x2 = FIXNUMP(FIRST(point)) ? FIRST(point) :
					 simple_eval_for_icon(FIRST(point));
				point = FOURTH(description_element);
				y2 = FIXNUMP(SECOND(point)) ? 
					SECOND(point) : 
					simple_eval_for_icon(SECOND(point));
				reflection_and_rotation_qm = 
					reflection_and_rotation;
				if (reflection_and_rotation_qm) {
				    if (EQ(reflection_and_rotation_qm,
						Qnormal));
				    else if (EQ(reflection_and_rotation_qm,
					    Qclockwise_90)) {
					x1_temp = FIXNUM_MINUS(height,y1_1);
					y1_1 = x1;
					x1 = x1_temp;
					x2_temp = FIXNUM_MINUS(height,y2);
					y2 = x2;
					x2 = x2_temp;
				    }
				    else if (EQ(reflection_and_rotation_qm,
					    Qclockwise_270)) {
					x1_temp = y1_1;
					y1_1 = FIXNUM_MINUS(width,x1);
					x1 = x1_temp;
					x2_temp = y2;
					y2 = FIXNUM_MINUS(width,x2);
					x2 = x2_temp;
				    }
				    else if (EQ(reflection_and_rotation_qm,
					    Qreflected_clockwise_270)) {
					x1_temp = y1_1;
					y1_1 = x1;
					x1 = x1_temp;
					x2_temp = y2;
					y2 = x2;
					x2 = x2_temp;
				    }
				    else if (EQ(reflection_and_rotation_qm,
					    Qclockwise_180)) {
					x1 = FIXNUM_MINUS(width,x1);
					y1_1 = FIXNUM_MINUS(height,y1_1);
					x2 = FIXNUM_MINUS(width,x2);
					y2 = FIXNUM_MINUS(height,y2);
				    }
				    else if (EQ(reflection_and_rotation_qm,
					    Qreflected_clockwise_90)) {
					x1_temp = FIXNUM_MINUS(height,y1_1);
					y1_1 = FIXNUM_MINUS(width,x1);
					x1 = x1_temp;
					x2_temp = FIXNUM_MINUS(height,y2);
					y2 = FIXNUM_MINUS(width,x2);
					x2 = x2_temp;
				    }
				    else if (EQ(reflection_and_rotation_qm,
					    Qreflected)) {
					x1 = FIXNUM_MINUS(width,x1);
					x2 = FIXNUM_MINUS(width,x2);
				    }
				    else if (EQ(reflection_and_rotation_qm,
					    Qreflected_clockwise_180)) {
					y1_1 = FIXNUM_MINUS(height,y1_1);
					y2 = FIXNUM_MINUS(height,y2);
				    }
				}
				scale = x_scale;
				temp_6 = IFIX(FIXNUM_MIN(x1,x2));
				value = MAX((SI_Long)0L,temp_6);
				if (IFIX(scale) == (SI_Long)4096L)
				    stipple_area_left_edge = value;
				else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					scale) && FIXNUM_LT(scale,
					Isqrt_of_most_positive_fixnum) && 
					IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
					< value && value < 
					IFIX(Isqrt_of_most_positive_fixnum)) {
				    unshifted_result = IFIX(scale) * value 
					    + (SI_Long)2048L;
				    stipple_area_left_edge = 
					    unshifted_result >>  -  - 
					    (SI_Long)12L;
				}
				else
				    stipple_area_left_edge = 
					    IFIX(scalef_function(scale,
					    FIX(value)));
				scale = y_scale;
				temp_6 = IFIX(FIXNUM_MIN(y1_1,y2));
				value = MAX((SI_Long)0L,temp_6);
				if (IFIX(scale) == (SI_Long)4096L)
				    stipple_area_top_edge = value;
				else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					scale) && FIXNUM_LT(scale,
					Isqrt_of_most_positive_fixnum) && 
					IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
					< value && value < 
					IFIX(Isqrt_of_most_positive_fixnum)) {
				    unshifted_result = IFIX(scale) * value 
					    + (SI_Long)2048L;
				    stipple_area_top_edge = 
					    unshifted_result >>  -  - 
					    (SI_Long)12L;
				}
				else
				    stipple_area_top_edge = 
					    IFIX(scalef_function(scale,
					    FIX(value)));
				scale = x_scale;
				temp = FIXNUM_MAX(x1,x2);
				value_1 = FIXNUM_MIN(temp,width_for_icon);
				if (IFIX(scale) == (SI_Long)4096L)
				    stipple_area_right_edge = IFIX(value_1);
				else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					scale) && FIXNUM_LT(scale,
					Isqrt_of_most_positive_fixnum) && 
					FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					value_1) && FIXNUM_LT(value_1,
					Isqrt_of_most_positive_fixnum)) {
				    unshifted_result = 
					    IFIX(FIXNUM_TIMES(scale,
					    value_1)) + (SI_Long)2048L;
				    stipple_area_right_edge = 
					    unshifted_result >>  -  - 
					    (SI_Long)12L;
				}
				else
				    stipple_area_right_edge = 
					    IFIX(scalef_function(scale,
					    value_1));
				scale = y_scale;
				temp = FIXNUM_MAX(y1_1,y2);
				value_1 = FIXNUM_MIN(temp,height_for_icon);
				if (IFIX(scale) == (SI_Long)4096L)
				    stipple_area_bottom_edge = IFIX(value_1);
				else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					scale) && FIXNUM_LT(scale,
					Isqrt_of_most_positive_fixnum) && 
					FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					value_1) && FIXNUM_LT(value_1,
					Isqrt_of_most_positive_fixnum)) {
				    unshifted_result = 
					    IFIX(FIXNUM_TIMES(scale,
					    value_1)) + (SI_Long)2048L;
				    stipple_area_bottom_edge = 
					    unshifted_result >>  -  - 
					    (SI_Long)12L;
				}
				else
				    stipple_area_bottom_edge = 
					    IFIX(scalef_function(scale,
					    value_1));
			    }
			}
		    }
		}
		else if (EQ(line_drawing_directive,Qfilled_polygon))
		    orient_and_scale_and_paint_filled_polygon(description_element,
			    x_scale,y_scale,width,height,
			    reflection_and_rotation,icon_line_color_value);
		else if (EQ(line_drawing_directive,Qimage)) {
		    image_name = 
			    simple_eval_for_icon(SECOND(description_element));
		    point_qm = THIRD(description_element);
		    scale_qm = FOURTH(description_element);
		    x = point_qm ? (FIXNUMP(FIRST(point_qm)) ? 
			    FIRST(point_qm) : 
			    simple_eval_for_icon(FIRST(point_qm))) : 
			    FIX((SI_Long)0L);
		    y = point_qm ? (FIXNUMP(SECOND(point_qm)) ? 
			    SECOND(point_qm) : 
			    simple_eval_for_icon(SECOND(point_qm))) : 
			    FIX((SI_Long)0L);
		    if (scale_qm) {
			scale = x_scale;
			value_1 = FIRST(scale_qm);
			if (IFIX(scale) == (SI_Long)4096L)
			    new_x_scale = value_1;
			else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				scale) && FIXNUM_LT(scale,
				Isqrt_of_most_positive_fixnum) && 
				FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				value_1) && FIXNUM_LT(value_1,
				Isqrt_of_most_positive_fixnum)) {
			    unshifted_result = IFIX(FIXNUM_TIMES(scale,
				    value_1)) + (SI_Long)2048L;
			    new_x_scale = FIX(unshifted_result >>  -  - 
				    (SI_Long)12L);
			}
			else
			    new_x_scale = scalef_function(scale,value_1);
		    }
		    else
			new_x_scale = x_scale;
		    if (scale_qm) {
			scale = y_scale;
			value_1 = SECOND(scale_qm);
			if (IFIX(scale) == (SI_Long)4096L)
			    new_y_scale = value_1;
			else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				scale) && FIXNUM_LT(scale,
				Isqrt_of_most_positive_fixnum) && 
				FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				value_1) && FIXNUM_LT(value_1,
				Isqrt_of_most_positive_fixnum)) {
			    unshifted_result = IFIX(FIXNUM_TIMES(scale,
				    value_1)) + (SI_Long)2048L;
			    new_y_scale = FIX(unshifted_result >>  -  - 
				    (SI_Long)12L);
			}
			else
			    new_y_scale = scalef_function(scale,value_1);
		    }
		    else
			new_y_scale = y_scale;
		    paint_icon_image_if_any(image_name,x,y,new_x_scale,
			    new_y_scale,width,height,
			    reflection_and_rotation,icon_line_color_value);
		}
		else if (EQ(line_drawing_directive,Qtext)) {
		    text_reflection_and_rotation = Nil;
		    scale_qm = text_reflection_and_rotation ? 
			    SIXTH(description_element) : 
			    FIFTH(description_element);
		    if (scale_qm) {
			scale = x_scale;
			value_1 = FIRST(scale_qm);
			if (IFIX(scale) == (SI_Long)4096L)
			    new_x_scale = value_1;
			else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				scale) && FIXNUM_LT(scale,
				Isqrt_of_most_positive_fixnum) && 
				FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				value_1) && FIXNUM_LT(value_1,
				Isqrt_of_most_positive_fixnum)) {
			    unshifted_result = IFIX(FIXNUM_TIMES(scale,
				    value_1)) + (SI_Long)2048L;
			    new_x_scale = FIX(unshifted_result >>  -  - 
				    (SI_Long)12L);
			}
			else
			    new_x_scale = scalef_function(scale,value_1);
		    }
		    else
			new_x_scale = x_scale;
		    if (scale_qm) {
			scale = y_scale;
			value_1 = SECOND(scale_qm);
			if (IFIX(scale) == (SI_Long)4096L)
			    new_y_scale = value_1;
			else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				scale) && FIXNUM_LT(scale,
				Isqrt_of_most_positive_fixnum) && 
				FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				value_1) && FIXNUM_LT(value_1,
				Isqrt_of_most_positive_fixnum)) {
			    unshifted_result = IFIX(FIXNUM_TIMES(scale,
				    value_1)) + (SI_Long)2048L;
			    new_y_scale = FIX(unshifted_result >>  -  - 
				    (SI_Long)12L);
			}
			else
			    new_y_scale = scalef_function(scale,value_1);
		    }
		    else
			new_y_scale = y_scale;
		    orient_and_scale_and_paint_text(description_element,
			    new_x_scale,new_y_scale,width,height,
			    reflection_and_rotation,icon_line_color_value);
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    goto next_loop;
  end_loop:
    if (icon_stipple_qm) {
	if (FIXNUM_LT(Icp_window_protocol_supports_raster_stipples,
		ISVREF(Current_window,(SI_Long)11L)))
	    stipple_rectangle_in_current_scratchpad_raster(FIX(stipple_area_left_edge),
		    FIX(stipple_area_top_edge),
		    FIX(stipple_area_right_edge),
		    FIX(stipple_area_bottom_edge),
		    foreground_icon_line_color_value,icon_stipple_qm);
    }
    return VALUES_1(Nil);
}

/* PAINT-ICON-IMAGE-IF-ANY */
Object paint_icon_image_if_any(image_name,x_in_icon,y_in_icon,x_scale,
	    y_scale,icon_width,icon_height,reflection_and_rotation,
	    icon_line_color_value)
    Object image_name, x_in_icon, y_in_icon, x_scale, y_scale, icon_width;
    Object icon_height, reflection_and_rotation, icon_line_color_value;
{
    Object image_data_qm, slow_is_better_p, send_image_data_immediately_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(63,76);
    image_data_qm = find_image_data(image_name);
    if (image_data_qm) {
	slow_is_better_p = native_printing_p();
	if (slow_is_better_p);
	else
	    slow_is_better_p = (IFIX(x_scale) < (SI_Long)4096L || 
		    IFIX(y_scale) < (SI_Long)4096L) && 
		    IFIX(ISVREF(image_data_qm,(SI_Long)5L)) <= 
		    (SI_Long)64L ? (IFIX(ISVREF(image_data_qm,
		    (SI_Long)6L)) <= (SI_Long)64L ? T : Nil) : Qnil;
	send_image_data_immediately_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Send_image_data_immediately_qm,Qsend_image_data_immediately_qm,send_image_data_immediately_qm,
		0);
	  if (window_supports_painting_this_image_data(Current_window,
		  image_data_qm) &&  !TRUEP(slow_is_better_p))
	      result = paint_image_in_current_scratchpad_raster(image_data_qm,
		      x_in_icon,y_in_icon,x_scale,y_scale,icon_width,
		      icon_height,reflection_and_rotation,Nil,
		      icon_line_color_value);
	  else
	      result = slowly_draw_image_data_on_current_scratchpad(image_data_qm,
		      x_in_icon,y_in_icon,x_scale,y_scale,icon_width,
		      icon_height,reflection_and_rotation,
		      icon_line_color_value);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qarc;                /* arc */

/* ORIENT-AND-SCALE-AND-PAINT-POLYLINE */
Object orient_and_scale_and_paint_polyline(points,outline_case_qm,x_scale,
	    y_scale,width_at_normalized_scale,height_at_normalized_scale,
	    reflection_and_rotation_qm,color_value)
    Object points, outline_case_qm, x_scale, y_scale;
    Object width_at_normalized_scale, height_at_normalized_scale;
    Object reflection_and_rotation_qm, color_value;
{
    Object x1, y1_1, x2, y2, x3, y3, remaining_points, temp, point, width;
    Object height, x1_temp, x2_temp, x3_temp, temp_2, temp_3, temp_4;
    SI_Long unshifted_result;
    char temp_1;

    x_note_fn_call(63,77);
    x1 = Nil;
    y1_1 = Nil;
    x2 = Nil;
    y2 = Nil;
    x3 = Nil;
    y3 = Nil;
    remaining_points = points;
  next_loop:
    if ( !TRUEP(remaining_points))
	goto end_loop;
    if (CDR(remaining_points)) {
	temp = SECOND(remaining_points);
	temp_1 = EQ(FIRST(temp),Qarc);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	point = FIRST(remaining_points);
	x1 = FIXNUMP(FIRST(point)) ? FIRST(point) : 
		simple_eval_for_icon(FIRST(point));
	point = FIRST(remaining_points);
	y1_1 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
		simple_eval_for_icon(SECOND(point));
	temp = SECOND(remaining_points);
	point = SECOND(temp);
	x2 = FIXNUMP(FIRST(point)) ? FIRST(point) : 
		simple_eval_for_icon(FIRST(point));
	temp = SECOND(remaining_points);
	point = SECOND(temp);
	y2 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
		simple_eval_for_icon(SECOND(point));
	point = CDDR(remaining_points) ? THIRD(remaining_points) : CAR(points);
	x3 = FIXNUMP(FIRST(point)) ? FIRST(point) : 
		simple_eval_for_icon(FIRST(point));
	point = CDDR(remaining_points) ? THIRD(remaining_points) : CAR(points);
	y3 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
		simple_eval_for_icon(SECOND(point));
	width = width_at_normalized_scale;
	height = height_at_normalized_scale;
	if (reflection_and_rotation_qm) {
	    if (EQ(reflection_and_rotation_qm,Qnormal));
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
		x1_temp = FIXNUM_MINUS(height,y1_1);
		y1_1 = x1;
		x1 = x1_temp;
		x2_temp = FIXNUM_MINUS(height,y2);
		y2 = x2;
		x2 = x2_temp;
		x3_temp = FIXNUM_MINUS(height,y3);
		y3 = x3;
		x3 = x3_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
		x1_temp = y1_1;
		y1_1 = FIXNUM_MINUS(width,x1);
		x1 = x1_temp;
		x2_temp = y2;
		y2 = FIXNUM_MINUS(width,x2);
		x2 = x2_temp;
		x3_temp = y3;
		y3 = FIXNUM_MINUS(width,x3);
		x3 = x3_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
		x1_temp = y1_1;
		y1_1 = x1;
		x1 = x1_temp;
		x2_temp = y2;
		y2 = x2;
		x2 = x2_temp;
		x3_temp = y3;
		y3 = x3;
		x3 = x3_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
		x1 = FIXNUM_MINUS(width,x1);
		y1_1 = FIXNUM_MINUS(height,y1_1);
		x2 = FIXNUM_MINUS(width,x2);
		y2 = FIXNUM_MINUS(height,y2);
		x3 = FIXNUM_MINUS(width,x3);
		y3 = FIXNUM_MINUS(height,y3);
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
		x1_temp = FIXNUM_MINUS(height,y1_1);
		y1_1 = FIXNUM_MINUS(width,x1);
		x1 = x1_temp;
		x2_temp = FIXNUM_MINUS(height,y2);
		y2 = FIXNUM_MINUS(width,x2);
		x2 = x2_temp;
		x3_temp = FIXNUM_MINUS(height,y3);
		y3 = FIXNUM_MINUS(width,x3);
		x3 = x3_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected)) {
		x1 = FIXNUM_MINUS(width,x1);
		x2 = FIXNUM_MINUS(width,x2);
		x3 = FIXNUM_MINUS(width,x3);
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180)) {
		y1_1 = FIXNUM_MINUS(height,y1_1);
		y2 = FIXNUM_MINUS(height,y2);
		y3 = FIXNUM_MINUS(height,y3);
	    }
	}
	paint_arc_or_circle_in_current_scratchpad_raster(x1,y1_1,x2,y2,x3,
		y3,x_scale,y_scale,color_value,Nil,Nil);
	remaining_points = CDDR(remaining_points);
    }
    else if (CDR(remaining_points) || outline_case_qm) {
	point = FIRST(remaining_points);
	x1 = FIXNUMP(FIRST(point)) ? FIRST(point) : 
		simple_eval_for_icon(FIRST(point));
	point = FIRST(remaining_points);
	y1_1 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
		simple_eval_for_icon(SECOND(point));
	point = CDR(remaining_points) ? SECOND(remaining_points) : CAR(points);
	x2 = FIXNUMP(FIRST(point)) ? FIRST(point) : 
		simple_eval_for_icon(FIRST(point));
	point = CDR(remaining_points) ? SECOND(remaining_points) : CAR(points);
	y2 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
		simple_eval_for_icon(SECOND(point));
	width = width_at_normalized_scale;
	height = height_at_normalized_scale;
	if (reflection_and_rotation_qm) {
	    if (EQ(reflection_and_rotation_qm,Qnormal));
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
		x1_temp = FIXNUM_MINUS(height,y1_1);
		y1_1 = x1;
		x1 = x1_temp;
		x2_temp = FIXNUM_MINUS(height,y2);
		y2 = x2;
		x2 = x2_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
		x1_temp = y1_1;
		y1_1 = FIXNUM_MINUS(width,x1);
		x1 = x1_temp;
		x2_temp = y2;
		y2 = FIXNUM_MINUS(width,x2);
		x2 = x2_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
		x1_temp = y1_1;
		y1_1 = x1;
		x1 = x1_temp;
		x2_temp = y2;
		y2 = x2;
		x2 = x2_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
		x1 = FIXNUM_MINUS(width,x1);
		y1_1 = FIXNUM_MINUS(height,y1_1);
		x2 = FIXNUM_MINUS(width,x2);
		y2 = FIXNUM_MINUS(height,y2);
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
		x1_temp = FIXNUM_MINUS(height,y1_1);
		y1_1 = FIXNUM_MINUS(width,x1);
		x1 = x1_temp;
		x2_temp = FIXNUM_MINUS(height,y2);
		y2 = FIXNUM_MINUS(width,x2);
		x2 = x2_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected)) {
		x1 = FIXNUM_MINUS(width,x1);
		x2 = FIXNUM_MINUS(width,x2);
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180)) {
		y1_1 = FIXNUM_MINUS(height,y1_1);
		y2 = FIXNUM_MINUS(height,y2);
	    }
	}
	if (IFIX(x_scale) == (SI_Long)4096L)
	    temp = x1;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) 
		&& FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x1) && 
		FIXNUM_LT(x1,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x1)) + (SI_Long)2048L;
	    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp = scalef_function(x_scale,x1);
	if (IFIX(y_scale) == (SI_Long)4096L)
	    temp_2 = y1_1;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) 
		&& FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y1_1) && 
		FIXNUM_LT(y1_1,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y1_1)) + 
		    (SI_Long)2048L;
	    temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_2 = scalef_function(y_scale,y1_1);
	if (IFIX(x_scale) == (SI_Long)4096L)
	    temp_3 = x2;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) 
		&& FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x2) && 
		FIXNUM_LT(x2,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x2)) + (SI_Long)2048L;
	    temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_3 = scalef_function(x_scale,x2);
	if (IFIX(y_scale) == (SI_Long)4096L)
	    temp_4 = y2;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) 
		&& FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y2) && 
		FIXNUM_LT(y2,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y2)) + (SI_Long)2048L;
	    temp_4 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_4 = scalef_function(y_scale,y2);
	paint_line_in_current_scratchpad_raster(temp,temp_2,temp_3,temp_4,
		color_value,T);
	remaining_points = CDR(remaining_points);
    }
    else
	remaining_points = CDR(remaining_points);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ORIENT-AND-SCALE-AND-PAINT-POINT */
Object orient_and_scale_and_paint_point(x,y,x_scale,y_scale,
	    width_at_normalized_scale,height_at_normalized_scale,
	    reflection_and_rotation_qm,color_value)
    Object x, y, x_scale, y_scale, width_at_normalized_scale;
    Object height_at_normalized_scale, reflection_and_rotation_qm, color_value;
{
    Object width, height, x_temp, temp, temp_1;
    SI_Long unshifted_result;

    x_note_fn_call(63,78);
    width = width_at_normalized_scale;
    height = height_at_normalized_scale;
    if (reflection_and_rotation_qm) {
	if (EQ(reflection_and_rotation_qm,Qnormal));
	else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
	    x_temp = FIXNUM_MINUS(height,y);
	    y = x;
	    x = x_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
	    x_temp = y;
	    y = FIXNUM_MINUS(width,x);
	    x = x_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
	    x_temp = y;
	    y = x;
	    x = x_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
	    x = FIXNUM_MINUS(width,x);
	    y = FIXNUM_MINUS(height,y);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
	    x_temp = FIXNUM_MINUS(height,y);
	    y = FIXNUM_MINUS(width,x);
	    x = x_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected))
	    x = FIXNUM_MINUS(width,x);
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180))
	    y = FIXNUM_MINUS(height,y);
    }
    if (IFIX(x_scale) == (SI_Long)4096L)
	temp = x;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) && 
	    FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
	    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x)) + (SI_Long)2048L;
	temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp = scalef_function(x_scale,x);
    if (IFIX(y_scale) == (SI_Long)4096L)
	temp_1 = y;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
	    FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y)) + (SI_Long)2048L;
	temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp_1 = scalef_function(y_scale,y);
    return paint_point_in_current_scratchpad_raster(temp,temp_1,color_value);
}

/* GET-X-Y-MAX-AND-OFFSET */
Object get_x_y_max_and_offset(region_extrema_entry_qm,x_scale,y_scale,
	    width,height,reflection_and_rotation)
    Object region_extrema_entry_qm, x_scale, y_scale, width, height;
    Object reflection_and_rotation;
{
    x_note_fn_call(63,79);
    if (region_extrema_entry_qm && SECOND(region_extrema_entry_qm))
	return orient_and_scale_region_extrema(SECOND(region_extrema_entry_qm),
		THIRD(region_extrema_entry_qm),
		FOURTH(region_extrema_entry_qm),
		FIFTH(region_extrema_entry_qm),x_scale,y_scale,width,
		height,reflection_and_rotation);
    else
	return VALUES_4(Nil,Nil,Nil,Nil);
}

/* ORIENT-AND-SCALE-REGION-EXTREMA */
Object orient_and_scale_region_extrema(x_offset_for_stored_raster,
	    y_offset_for_stored_raster,x_max_for_stored_raster,
	    y_max_for_stored_raster,x_scale,y_scale,
	    width_at_normalized_scale,height_at_normalized_scale,
	    reflection_and_rotation_qm)
    Object x_offset_for_stored_raster, y_offset_for_stored_raster;
    Object x_max_for_stored_raster, y_max_for_stored_raster, x_scale, y_scale;
    Object width_at_normalized_scale, height_at_normalized_scale;
    Object reflection_and_rotation_qm;
{
    Object width, height, x_offset_for_stored_raster_temp;
    Object x_max_for_stored_raster_temp, y_offset_for_stored_raster_temp, temp;
    Object temp_1, temp_2;
    SI_Long unshifted_result, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(63,80);
    width = width_at_normalized_scale;
    height = height_at_normalized_scale;
    if (reflection_and_rotation_qm) {
	if (EQ(reflection_and_rotation_qm,Qnormal));
	else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
	    x_offset_for_stored_raster_temp = FIXNUM_MINUS(height,
		    y_offset_for_stored_raster);
	    y_offset_for_stored_raster = x_offset_for_stored_raster;
	    x_offset_for_stored_raster = x_offset_for_stored_raster_temp;
	    x_max_for_stored_raster_temp = FIXNUM_MINUS(height,
		    y_max_for_stored_raster);
	    y_max_for_stored_raster = x_max_for_stored_raster;
	    x_max_for_stored_raster = x_max_for_stored_raster_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
	    x_offset_for_stored_raster_temp = y_offset_for_stored_raster;
	    y_offset_for_stored_raster = FIXNUM_MINUS(width,
		    x_offset_for_stored_raster);
	    x_offset_for_stored_raster = x_offset_for_stored_raster_temp;
	    x_max_for_stored_raster_temp = y_max_for_stored_raster;
	    y_max_for_stored_raster = FIXNUM_MINUS(width,
		    x_max_for_stored_raster);
	    x_max_for_stored_raster = x_max_for_stored_raster_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
	    x_offset_for_stored_raster_temp = y_offset_for_stored_raster;
	    y_offset_for_stored_raster = x_offset_for_stored_raster;
	    x_offset_for_stored_raster = x_offset_for_stored_raster_temp;
	    x_max_for_stored_raster_temp = y_max_for_stored_raster;
	    y_max_for_stored_raster = x_max_for_stored_raster;
	    x_max_for_stored_raster = x_max_for_stored_raster_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
	    x_offset_for_stored_raster = FIXNUM_MINUS(width,
		    x_offset_for_stored_raster);
	    y_offset_for_stored_raster = FIXNUM_MINUS(height,
		    y_offset_for_stored_raster);
	    x_max_for_stored_raster = FIXNUM_MINUS(width,
		    x_max_for_stored_raster);
	    y_max_for_stored_raster = FIXNUM_MINUS(height,
		    y_max_for_stored_raster);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
	    x_offset_for_stored_raster_temp = FIXNUM_MINUS(height,
		    y_offset_for_stored_raster);
	    y_offset_for_stored_raster = FIXNUM_MINUS(width,
		    x_offset_for_stored_raster);
	    x_offset_for_stored_raster = x_offset_for_stored_raster_temp;
	    x_max_for_stored_raster_temp = FIXNUM_MINUS(height,
		    y_max_for_stored_raster);
	    y_max_for_stored_raster = FIXNUM_MINUS(width,
		    x_max_for_stored_raster);
	    x_max_for_stored_raster = x_max_for_stored_raster_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected)) {
	    x_offset_for_stored_raster = FIXNUM_MINUS(width,
		    x_offset_for_stored_raster);
	    x_max_for_stored_raster = FIXNUM_MINUS(width,
		    x_max_for_stored_raster);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180)) {
	    y_offset_for_stored_raster = FIXNUM_MINUS(height,
		    y_offset_for_stored_raster);
	    y_max_for_stored_raster = FIXNUM_MINUS(height,
		    y_max_for_stored_raster);
	}
    }
    if (FIXNUM_GT(x_offset_for_stored_raster,x_max_for_stored_raster)) {
	x_offset_for_stored_raster_temp = x_max_for_stored_raster;
	x_max_for_stored_raster = x_offset_for_stored_raster;
	x_offset_for_stored_raster = x_offset_for_stored_raster_temp;
    }
    if (FIXNUM_GT(y_offset_for_stored_raster,y_max_for_stored_raster)) {
	y_offset_for_stored_raster_temp = y_max_for_stored_raster;
	y_max_for_stored_raster = y_offset_for_stored_raster;
	y_offset_for_stored_raster = y_offset_for_stored_raster_temp;
    }
    if (IFIX(x_scale) == (SI_Long)4096L)
	temp = x_offset_for_stored_raster;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) && 
	    FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    x_offset_for_stored_raster) && 
	    FIXNUM_LT(x_offset_for_stored_raster,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale,
		x_offset_for_stored_raster)) + (SI_Long)2048L;
	temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp = scalef_function(x_scale,x_offset_for_stored_raster);
    if (IFIX(y_scale) == (SI_Long)4096L)
	temp_1 = y_offset_for_stored_raster;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    y_offset_for_stored_raster) && 
	    FIXNUM_LT(y_offset_for_stored_raster,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,
		y_offset_for_stored_raster)) + (SI_Long)2048L;
	temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp_1 = scalef_function(y_scale,y_offset_for_stored_raster);
    if (IFIX(x_scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(x_max_for_stored_raster);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) && 
	    FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    x_max_for_stored_raster) && FIXNUM_LT(x_max_for_stored_raster,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale,
		x_max_for_stored_raster)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(x_scale,
		x_max_for_stored_raster));
    gensymed_symbol_1 = (SI_Long)1L;
    temp_2 = FIX(gensymed_symbol + gensymed_symbol_1);
    if (IFIX(y_scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(y_max_for_stored_raster);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    y_max_for_stored_raster) && FIXNUM_LT(y_max_for_stored_raster,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,
		y_max_for_stored_raster)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(y_scale,
		y_max_for_stored_raster));
    gensymed_symbol_1 = (SI_Long)1L;
    return VALUES_4(temp,temp_1,temp_2,FIX(gensymed_symbol + 
	    gensymed_symbol_1));
}

/* ORIENT-AND-SCALE-AND-PAINT-LINE */
Object orient_and_scale_and_paint_line(x1,y1_1,x2,y2,x_scale,y_scale,
	    width_at_normalized_scale,height_at_normalized_scale,
	    reflection_and_rotation_qm,color_value)
    Object x1, y1_1, x2, y2, x_scale, y_scale, width_at_normalized_scale;
    Object height_at_normalized_scale, reflection_and_rotation_qm, color_value;
{
    Object width, height, x1_temp, x2_temp, temp, temp_1, temp_2, temp_3;
    SI_Long unshifted_result;

    x_note_fn_call(63,81);
    width = width_at_normalized_scale;
    height = height_at_normalized_scale;
    if (reflection_and_rotation_qm) {
	if (EQ(reflection_and_rotation_qm,Qnormal));
	else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
	    x1_temp = FIXNUM_MINUS(height,y1_1);
	    y1_1 = x1;
	    x1 = x1_temp;
	    x2_temp = FIXNUM_MINUS(height,y2);
	    y2 = x2;
	    x2 = x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
	    x1_temp = y1_1;
	    y1_1 = FIXNUM_MINUS(width,x1);
	    x1 = x1_temp;
	    x2_temp = y2;
	    y2 = FIXNUM_MINUS(width,x2);
	    x2 = x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
	    x1_temp = y1_1;
	    y1_1 = x1;
	    x1 = x1_temp;
	    x2_temp = y2;
	    y2 = x2;
	    x2 = x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
	    x1 = FIXNUM_MINUS(width,x1);
	    y1_1 = FIXNUM_MINUS(height,y1_1);
	    x2 = FIXNUM_MINUS(width,x2);
	    y2 = FIXNUM_MINUS(height,y2);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
	    x1_temp = FIXNUM_MINUS(height,y1_1);
	    y1_1 = FIXNUM_MINUS(width,x1);
	    x1 = x1_temp;
	    x2_temp = FIXNUM_MINUS(height,y2);
	    y2 = FIXNUM_MINUS(width,x2);
	    x2 = x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected)) {
	    x1 = FIXNUM_MINUS(width,x1);
	    x2 = FIXNUM_MINUS(width,x2);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180)) {
	    y1_1 = FIXNUM_MINUS(height,y1_1);
	    y2 = FIXNUM_MINUS(height,y2);
	}
    }
    if (IFIX(x_scale) == (SI_Long)4096L)
	temp = x1;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) && 
	    FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x1) && 
	    FIXNUM_LT(x1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x1)) + (SI_Long)2048L;
	temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp = scalef_function(x_scale,x1);
    if (IFIX(y_scale) == (SI_Long)4096L)
	temp_1 = y1_1;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y1_1) && 
	    FIXNUM_LT(y1_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y1_1)) + (SI_Long)2048L;
	temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp_1 = scalef_function(y_scale,y1_1);
    if (IFIX(x_scale) == (SI_Long)4096L)
	temp_2 = x2;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) && 
	    FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x2) && 
	    FIXNUM_LT(x2,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x2)) + (SI_Long)2048L;
	temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp_2 = scalef_function(x_scale,x2);
    if (IFIX(y_scale) == (SI_Long)4096L)
	temp_3 = y2;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y2) && 
	    FIXNUM_LT(y2,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y2)) + (SI_Long)2048L;
	temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp_3 = scalef_function(y_scale,y2);
    return paint_line_in_current_scratchpad_raster(temp,temp_1,temp_2,
	    temp_3,color_value,T);
}

/* POINT-LIST-TO-UNSIGNED-POINT-LIST */
Object point_list_to_unsigned_point_list(point_list)
    Object point_list;
{
    Object result_1, count_1, p, ab_loop_list_, x, y;

    x_note_fn_call(63,82);
    result_1 = Nil;
    count_1 = FIX((SI_Long)0L);
    p = Nil;
    ab_loop_list_ = point_list;
    x = Nil;
    y = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    p = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    x = FIXNUMP(FIRST(p)) ? FIRST(p) : simple_eval_for_icon(FIRST(p));
    y = FIXNUMP(SECOND(p)) ? SECOND(p) : simple_eval_for_icon(SECOND(p));
    if ( !FIXNUM_LT(count_1,Maximum_polygon_points))
	goto end_loop;
    count_1 = FIXNUM_ADD1(count_1);
    result_1 = gensym_cons_1(FIX(IFIX(x) + (SI_Long)8192L),result_1);
    result_1 = gensym_cons_1(FIX(IFIX(y) + (SI_Long)8192L),result_1);
    goto next_loop;
  end_loop:
    return nreverse(result_1);
    return VALUES_1(Qnil);
}

/* ORIENT-AND-SCALE-AND-PAINT-FILLED-POLYGON */
Object orient_and_scale_and_paint_filled_polygon(description_element,
	    x_scale,y_scale,width_at_normalized_scale,
	    height_at_normalized_scale,reflection_and_rotation_qm,color_value)
    Object description_element, x_scale, y_scale, width_at_normalized_scale;
    Object height_at_normalized_scale, reflection_and_rotation_qm, color_value;
{
    Object points, result_1, point, ab_loop_list_, point_x, point_y, width;
    Object height, point_x_temp, temp, temp_1, polygon_points;
    Object unsigned_polygon_points, point_1, point_2, point_3, x1, y1_1, x2;
    Object y2, x3, y3, ab_loop_desetq_, x1_temp, x2_temp, x3_temp, temp_2;
    Object temp_3, temp_4, temp_5;
    SI_Long unshifted_result;

    x_note_fn_call(63,83);
    if ( !TRUEP(printing_window_p(Current_window)) && ( 
	    !EQ(ISVREF(Current_window,(SI_Long)1L),Qicp) || 
	    printing_window_p(Current_window) || 
	    FIXNUM_LT(Icp_window_protocol_supports_un_decomposed_polygons,
	    ISVREF(Current_window,(SI_Long)11L)))) {
	points = CADR(description_element);
	result_1 = Nil;
	point = Nil;
	ab_loop_list_ = points;
	point_x = Nil;
	point_y = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	point = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	point_x = FIXNUMP(FIRST(point)) ? FIRST(point) : 
		simple_eval_for_icon(FIRST(point));
	point_y = FIXNUMP(SECOND(point)) ? SECOND(point) : 
		simple_eval_for_icon(SECOND(point));
	width = width_at_normalized_scale;
	height = height_at_normalized_scale;
	if (reflection_and_rotation_qm) {
	    if (EQ(reflection_and_rotation_qm,Qnormal));
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
		point_x_temp = FIXNUM_MINUS(height,point_y);
		point_y = point_x;
		point_x = point_x_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
		point_x_temp = point_y;
		point_y = FIXNUM_MINUS(width,point_x);
		point_x = point_x_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
		point_x_temp = point_y;
		point_y = point_x;
		point_x = point_x_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
		point_x = FIXNUM_MINUS(width,point_x);
		point_y = FIXNUM_MINUS(height,point_y);
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
		point_x_temp = FIXNUM_MINUS(height,point_y);
		point_y = FIXNUM_MINUS(width,point_x);
		point_x = point_x_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected))
		point_x = FIXNUM_MINUS(width,point_x);
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180))
		point_y = FIXNUM_MINUS(height,point_y);
	}
	if (IFIX(x_scale) == (SI_Long)4096L)
	    temp = point_x;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) 
		&& FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,point_x) 
		&& FIXNUM_LT(point_x,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(x_scale,point_x)) + 
		    (SI_Long)2048L;
	    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp = scalef_function(x_scale,point_x);
	if (IFIX(y_scale) == (SI_Long)4096L)
	    temp_1 = point_y;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) 
		&& FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,point_y) 
		&& FIXNUM_LT(point_y,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(y_scale,point_y)) + 
		    (SI_Long)2048L;
	    temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_1 = scalef_function(y_scale,point_y);
	result_1 = gensym_cons_1(gensym_list_2(temp,temp_1),result_1);
	goto next_loop;
      end_loop:
	polygon_points = nreverse(result_1);
	goto end_1;
	polygon_points = Qnil;
      end_1:;
	unsigned_polygon_points = 
		point_list_to_unsigned_point_list(polygon_points);
	paint_filled_polygon_in_current_scratchpad_raster(unsigned_polygon_points,
		color_value);
	reclaim_gensym_tree_1(polygon_points);
	return reclaim_gensym_list_1(unsigned_polygon_points);
    }
    else {
	point_1 = Nil;
	point_2 = Nil;
	point_3 = Nil;
	ab_loop_list_ = CDDR(description_element);
	x1 = Nil;
	y1_1 = Nil;
	x2 = Nil;
	y2 = Nil;
	x3 = Nil;
	y3 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	point_1 = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	point_2 = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	point_3 = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	x1 = FIXNUMP(FIRST(point_1)) ? FIRST(point_1) : 
		simple_eval_for_icon(FIRST(point_1));
	y1_1 = FIXNUMP(SECOND(point_1)) ? SECOND(point_1) : 
		simple_eval_for_icon(SECOND(point_1));
	x2 = FIXNUMP(FIRST(point_2)) ? FIRST(point_2) : 
		simple_eval_for_icon(FIRST(point_2));
	y2 = FIXNUMP(SECOND(point_2)) ? SECOND(point_2) : 
		simple_eval_for_icon(SECOND(point_2));
	x3 = FIXNUMP(FIRST(point_3)) ? FIRST(point_3) : 
		simple_eval_for_icon(FIRST(point_3));
	y3 = FIXNUMP(SECOND(point_3)) ? SECOND(point_3) : 
		simple_eval_for_icon(SECOND(point_3));
	width = width_at_normalized_scale;
	height = height_at_normalized_scale;
	if (reflection_and_rotation_qm) {
	    if (EQ(reflection_and_rotation_qm,Qnormal));
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
		x1_temp = FIXNUM_MINUS(height,y1_1);
		y1_1 = x1;
		x1 = x1_temp;
		x2_temp = FIXNUM_MINUS(height,y2);
		y2 = x2;
		x2 = x2_temp;
		x3_temp = FIXNUM_MINUS(height,y3);
		y3 = x3;
		x3 = x3_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
		x1_temp = y1_1;
		y1_1 = FIXNUM_MINUS(width,x1);
		x1 = x1_temp;
		x2_temp = y2;
		y2 = FIXNUM_MINUS(width,x2);
		x2 = x2_temp;
		x3_temp = y3;
		y3 = FIXNUM_MINUS(width,x3);
		x3 = x3_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
		x1_temp = y1_1;
		y1_1 = x1;
		x1 = x1_temp;
		x2_temp = y2;
		y2 = x2;
		x2 = x2_temp;
		x3_temp = y3;
		y3 = x3;
		x3 = x3_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
		x1 = FIXNUM_MINUS(width,x1);
		y1_1 = FIXNUM_MINUS(height,y1_1);
		x2 = FIXNUM_MINUS(width,x2);
		y2 = FIXNUM_MINUS(height,y2);
		x3 = FIXNUM_MINUS(width,x3);
		y3 = FIXNUM_MINUS(height,y3);
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
		x1_temp = FIXNUM_MINUS(height,y1_1);
		y1_1 = FIXNUM_MINUS(width,x1);
		x1 = x1_temp;
		x2_temp = FIXNUM_MINUS(height,y2);
		y2 = FIXNUM_MINUS(width,x2);
		x2 = x2_temp;
		x3_temp = FIXNUM_MINUS(height,y3);
		y3 = FIXNUM_MINUS(width,x3);
		x3 = x3_temp;
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected)) {
		x1 = FIXNUM_MINUS(width,x1);
		x2 = FIXNUM_MINUS(width,x2);
		x3 = FIXNUM_MINUS(width,x3);
	    }
	    else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180)) {
		y1_1 = FIXNUM_MINUS(height,y1_1);
		y2 = FIXNUM_MINUS(height,y2);
		y3 = FIXNUM_MINUS(height,y3);
	    }
	}
	if (IFIX(x_scale) == (SI_Long)4096L)
	    temp = x1;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) 
		&& FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x1) && 
		FIXNUM_LT(x1,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x1)) + (SI_Long)2048L;
	    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp = scalef_function(x_scale,x1);
	if (IFIX(y_scale) == (SI_Long)4096L)
	    temp_1 = y1_1;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) 
		&& FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y1_1) && 
		FIXNUM_LT(y1_1,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y1_1)) + 
		    (SI_Long)2048L;
	    temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_1 = scalef_function(y_scale,y1_1);
	if (IFIX(x_scale) == (SI_Long)4096L)
	    temp_2 = x2;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) 
		&& FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x2) && 
		FIXNUM_LT(x2,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x2)) + (SI_Long)2048L;
	    temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_2 = scalef_function(x_scale,x2);
	if (IFIX(y_scale) == (SI_Long)4096L)
	    temp_3 = y2;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) 
		&& FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y2) && 
		FIXNUM_LT(y2,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y2)) + (SI_Long)2048L;
	    temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_3 = scalef_function(y_scale,y2);
	if (IFIX(x_scale) == (SI_Long)4096L)
	    temp_4 = x3;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) 
		&& FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x3) && 
		FIXNUM_LT(x3,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x3)) + (SI_Long)2048L;
	    temp_4 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_4 = scalef_function(x_scale,x3);
	if (IFIX(y_scale) == (SI_Long)4096L)
	    temp_5 = y3;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) 
		&& FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y3) && 
		FIXNUM_LT(y3,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y3)) + (SI_Long)2048L;
	    temp_5 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_5 = scalef_function(y_scale,y3);
	paint_filled_triangle_in_current_scratchpad_raster(temp,temp_1,
		temp_2,temp_3,temp_4,temp_5,color_value);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* ORIENT-AND-SCALE-AND-PAINT-SOLID-RECTANGLE */
Object orient_and_scale_and_paint_solid_rectangle(x1,y1_1,x2,y2,x_scale,
	    y_scale,width_at_normalized_scale,height_at_normalized_scale,
	    reflection_and_rotation_qm,color_value)
    Object x1, y1_1, x2, y2, x_scale, y_scale, width_at_normalized_scale;
    Object height_at_normalized_scale, reflection_and_rotation_qm, color_value;
{
    Object width, height, x1_temp, x2_temp, scale, value, temp, temp_1, temp_2;
    SI_Long delta, unshifted_result, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(63,84);
    width = width_at_normalized_scale;
    height = height_at_normalized_scale;
    if (reflection_and_rotation_qm) {
	if (EQ(reflection_and_rotation_qm,Qnormal));
	else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
	    x1_temp = FIXNUM_MINUS(height,y1_1);
	    y1_1 = x1;
	    x1 = x1_temp;
	    x2_temp = FIXNUM_MINUS(height,y2);
	    y2 = x2;
	    x2 = x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
	    x1_temp = y1_1;
	    y1_1 = FIXNUM_MINUS(width,x1);
	    x1 = x1_temp;
	    x2_temp = y2;
	    y2 = FIXNUM_MINUS(width,x2);
	    x2 = x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
	    x1_temp = y1_1;
	    y1_1 = x1;
	    x1 = x1_temp;
	    x2_temp = y2;
	    y2 = x2;
	    x2 = x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
	    x1 = FIXNUM_MINUS(width,x1);
	    y1_1 = FIXNUM_MINUS(height,y1_1);
	    x2 = FIXNUM_MINUS(width,x2);
	    y2 = FIXNUM_MINUS(height,y2);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
	    x1_temp = FIXNUM_MINUS(height,y1_1);
	    y1_1 = FIXNUM_MINUS(width,x1);
	    x1 = x1_temp;
	    x2_temp = FIXNUM_MINUS(height,y2);
	    y2 = FIXNUM_MINUS(width,x2);
	    x2 = x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected)) {
	    x1 = FIXNUM_MINUS(width,x1);
	    x2 = FIXNUM_MINUS(width,x2);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180)) {
	    y1_1 = FIXNUM_MINUS(height,y1_1);
	    y2 = FIXNUM_MINUS(height,y2);
	}
    }
    delta = native_printing_p() ? (SI_Long)0L : (SI_Long)1L;
    scale = x_scale;
    value = FIXNUM_MIN(x1,x2);
    if (IFIX(scale) == (SI_Long)4096L)
	temp = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp = scalef_function(scale,value);
    scale = y_scale;
    value = FIXNUM_MIN(y1_1,y2);
    if (IFIX(scale) == (SI_Long)4096L)
	temp_1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp_1 = scalef_function(scale,value);
    scale = x_scale;
    value = FIXNUM_MAX(x1,x2);
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(scale,value));
    gensymed_symbol_1 = delta;
    temp_2 = FIX(gensymed_symbol + gensymed_symbol_1);
    scale = y_scale;
    value = FIXNUM_MAX(y1_1,y2);
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(scale,value));
    gensymed_symbol_1 = delta;
    return paint_solid_rectangle_in_current_scratchpad_raster(temp,temp_1,
	    temp_2,FIX(gensymed_symbol + gensymed_symbol_1),color_value);
}

/* ORIENT-AND-SCALE-AND-PAINT-ROUNDED-RECTANGLE */
Object orient_and_scale_and_paint_rounded_rectangle(x1,y1_1,x2,y2,x_scale,
	    y_scale,width_at_normalized_scale,height_at_normalized_scale,
	    reflection_and_rotation_qm,color_value,filled_qm)
    Object x1, y1_1, x2, y2, x_scale, y_scale, width_at_normalized_scale;
    Object height_at_normalized_scale, reflection_and_rotation_qm, color_value;
    Object filled_qm;
{
    Object temp, temp_1, d, inner_x1, inner_y1, arc_x1, arc_y1, inner_x2;
    Object inner_y2, arc_x2, arc_y2, width, height, x1_temp, x2_temp;
    Object inner_x1_temp, inner_x2_temp, arc_x1_temp, arc_x2_temp, y1_temp;
    Object inner_y1_temp, arc_y1_temp, x1_in_window, y1_in_window;
    Object x2_in_window, y2_in_window, inner_x1_in_window, inner_y1_in_window;
    Object inner_x2_in_window, inner_y2_in_window;
    SI_Long temp_2, radius, unshifted_result;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(63,85);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = FIXNUM_MINUS(x2,x1);
	temp_1 = FIXNUM_ABS(temp);
	temp = FIXNUM_MINUS(y2,y1_1);
	temp = FIXNUM_ABS(temp);
	temp_2 = 
		IFIX(l_round(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_MIN(temp_1,
		temp)) / 3.0),_));
    }
    POP_LOCAL_ALLOCATION(0,0);
    radius = MIN((SI_Long)13L,temp_2);
    d = l_round(DOUBLE_TO_DOUBLE_FLOAT(0.2929 * (double)radius),_);
    inner_x1 = FIX(IFIX(x1) + radius);
    inner_y1 = FIX(IFIX(y1_1) + radius);
    arc_x1 = FIXNUM_ADD(x1,d);
    arc_y1 = FIXNUM_ADD(y1_1,d);
    inner_x2 = FIX(IFIX(x2) - radius);
    inner_y2 = FIX(IFIX(y2) - radius);
    arc_x2 = FIXNUM_MINUS(x2,d);
    arc_y2 = FIXNUM_MINUS(y2,d);
    width = width_at_normalized_scale;
    height = height_at_normalized_scale;
    if (reflection_and_rotation_qm) {
	if (EQ(reflection_and_rotation_qm,Qnormal));
	else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
	    x1_temp = FIXNUM_MINUS(height,y1_1);
	    y1_1 = x1;
	    x1 = x1_temp;
	    x2_temp = FIXNUM_MINUS(height,y2);
	    y2 = x2;
	    x2 = x2_temp;
	    inner_x1_temp = FIXNUM_MINUS(height,inner_y1);
	    inner_y1 = inner_x1;
	    inner_x1 = inner_x1_temp;
	    inner_x2_temp = FIXNUM_MINUS(height,inner_y2);
	    inner_y2 = inner_x2;
	    inner_x2 = inner_x2_temp;
	    arc_x1_temp = FIXNUM_MINUS(height,arc_y2);
	    arc_y2 = arc_x1;
	    arc_x1 = arc_x1_temp;
	    arc_x2_temp = FIXNUM_MINUS(height,arc_y2);
	    arc_y2 = arc_x2;
	    arc_x2 = arc_x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
	    x1_temp = y1_1;
	    y1_1 = FIXNUM_MINUS(width,x1);
	    x1 = x1_temp;
	    x2_temp = y2;
	    y2 = FIXNUM_MINUS(width,x2);
	    x2 = x2_temp;
	    inner_x1_temp = inner_y1;
	    inner_y1 = FIXNUM_MINUS(width,inner_x1);
	    inner_x1 = inner_x1_temp;
	    inner_x2_temp = inner_y2;
	    inner_y2 = FIXNUM_MINUS(width,inner_x2);
	    inner_x2 = inner_x2_temp;
	    arc_x1_temp = arc_y2;
	    arc_y2 = FIXNUM_MINUS(width,arc_x1);
	    arc_x1 = arc_x1_temp;
	    arc_x2_temp = arc_y2;
	    arc_y2 = FIXNUM_MINUS(width,arc_x2);
	    arc_x2 = arc_x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
	    x1_temp = y1_1;
	    y1_1 = x1;
	    x1 = x1_temp;
	    x2_temp = y2;
	    y2 = x2;
	    x2 = x2_temp;
	    inner_x1_temp = inner_y1;
	    inner_y1 = inner_x1;
	    inner_x1 = inner_x1_temp;
	    inner_x2_temp = inner_y2;
	    inner_y2 = inner_x2;
	    inner_x2 = inner_x2_temp;
	    arc_x1_temp = arc_y2;
	    arc_y2 = arc_x1;
	    arc_x1 = arc_x1_temp;
	    arc_x2_temp = arc_y2;
	    arc_y2 = arc_x2;
	    arc_x2 = arc_x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
	    x1 = FIXNUM_MINUS(width,x1);
	    y1_1 = FIXNUM_MINUS(height,y1_1);
	    x2 = FIXNUM_MINUS(width,x2);
	    y2 = FIXNUM_MINUS(height,y2);
	    inner_x1 = FIXNUM_MINUS(width,inner_x1);
	    inner_y1 = FIXNUM_MINUS(height,inner_y1);
	    inner_x2 = FIXNUM_MINUS(width,inner_x2);
	    inner_y2 = FIXNUM_MINUS(height,inner_y2);
	    arc_x1 = FIXNUM_MINUS(width,arc_x1);
	    arc_y2 = FIXNUM_MINUS(height,arc_y2);
	    arc_x2 = FIXNUM_MINUS(width,arc_x2);
	    arc_y2 = FIXNUM_MINUS(height,arc_y2);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
	    x1_temp = FIXNUM_MINUS(height,y1_1);
	    y1_1 = FIXNUM_MINUS(width,x1);
	    x1 = x1_temp;
	    x2_temp = FIXNUM_MINUS(height,y2);
	    y2 = FIXNUM_MINUS(width,x2);
	    x2 = x2_temp;
	    inner_x1_temp = FIXNUM_MINUS(height,inner_y1);
	    inner_y1 = FIXNUM_MINUS(width,inner_x1);
	    inner_x1 = inner_x1_temp;
	    inner_x2_temp = FIXNUM_MINUS(height,inner_y2);
	    inner_y2 = FIXNUM_MINUS(width,inner_x2);
	    inner_x2 = inner_x2_temp;
	    arc_x1_temp = FIXNUM_MINUS(height,arc_y2);
	    arc_y2 = FIXNUM_MINUS(width,arc_x1);
	    arc_x1 = arc_x1_temp;
	    arc_x2_temp = FIXNUM_MINUS(height,arc_y2);
	    arc_y2 = FIXNUM_MINUS(width,arc_x2);
	    arc_x2 = arc_x2_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected)) {
	    x1 = FIXNUM_MINUS(width,x1);
	    x2 = FIXNUM_MINUS(width,x2);
	    inner_x1 = FIXNUM_MINUS(width,inner_x1);
	    inner_x2 = FIXNUM_MINUS(width,inner_x2);
	    arc_x1 = FIXNUM_MINUS(width,arc_x1);
	    arc_x2 = FIXNUM_MINUS(width,arc_x2);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180)) {
	    y1_1 = FIXNUM_MINUS(height,y1_1);
	    y2 = FIXNUM_MINUS(height,y2);
	    inner_y1 = FIXNUM_MINUS(height,inner_y1);
	    inner_y2 = FIXNUM_MINUS(height,inner_y2);
	    arc_y2 = FIXNUM_MINUS(height,arc_y2);
	    arc_y2 = FIXNUM_MINUS(height,arc_y2);
	}
    }
    if (FIXNUM_GT(x1,x2)) {
	x1_temp = x2;
	x2 = x1;
	x1 = x1_temp;
	inner_x1_temp = inner_x2;
	inner_x2 = inner_x1;
	inner_x1 = inner_x1_temp;
	arc_x1_temp = arc_x2;
	arc_x2 = arc_x1;
	arc_x1 = arc_x1_temp;
    }
    if (FIXNUM_GT(y1_1,y2)) {
	y1_temp = y2;
	y2 = y1_1;
	y1_1 = y1_temp;
	inner_y1_temp = inner_y2;
	inner_y2 = inner_y1;
	inner_y1 = inner_y1_temp;
	arc_y1_temp = arc_y2;
	arc_y2 = arc_y1;
	arc_y1 = arc_y1_temp;
    }
    if (IFIX(x_scale) == (SI_Long)4096L)
	x1_in_window = x1;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) && 
	    FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x1) && 
	    FIXNUM_LT(x1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x1)) + (SI_Long)2048L;
	x1_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	x1_in_window = scalef_function(x_scale,x1);
    if (IFIX(y_scale) == (SI_Long)4096L)
	y1_in_window = y1_1;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y1_1) && 
	    FIXNUM_LT(y1_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y1_1)) + (SI_Long)2048L;
	y1_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	y1_in_window = scalef_function(y_scale,y1_1);
    if (IFIX(x_scale) == (SI_Long)4096L)
	x2_in_window = x2;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) && 
	    FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x2) && 
	    FIXNUM_LT(x2,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x2)) + (SI_Long)2048L;
	x2_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	x2_in_window = scalef_function(x_scale,x2);
    if (IFIX(y_scale) == (SI_Long)4096L)
	y2_in_window = y2;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y2) && 
	    FIXNUM_LT(y2,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y2)) + (SI_Long)2048L;
	y2_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	y2_in_window = scalef_function(y_scale,y2);
    if (IFIX(x_scale) == (SI_Long)4096L)
	inner_x1_in_window = inner_x1;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) && 
	    FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,inner_x1) && 
	    FIXNUM_LT(inner_x1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale,inner_x1)) + 
		(SI_Long)2048L;
	inner_x1_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	inner_x1_in_window = scalef_function(x_scale,inner_x1);
    if (IFIX(y_scale) == (SI_Long)4096L)
	inner_y1_in_window = inner_y1;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,inner_y1) && 
	    FIXNUM_LT(inner_y1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,inner_y1)) + 
		(SI_Long)2048L;
	inner_y1_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	inner_y1_in_window = scalef_function(y_scale,inner_y1);
    if (IFIX(x_scale) == (SI_Long)4096L)
	inner_x2_in_window = inner_x2;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) && 
	    FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,inner_x2) && 
	    FIXNUM_LT(inner_x2,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale,inner_x2)) + 
		(SI_Long)2048L;
	inner_x2_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	inner_x2_in_window = scalef_function(x_scale,inner_x2);
    if (IFIX(y_scale) == (SI_Long)4096L)
	inner_y2_in_window = inner_y2;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,inner_y2) && 
	    FIXNUM_LT(inner_y2,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,inner_y2)) + 
		(SI_Long)2048L;
	inner_y2_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	inner_y2_in_window = scalef_function(y_scale,inner_y2);
    paint_arc_or_circle_in_current_scratchpad_raster(x1,inner_y1,arc_x1,
	    arc_y1,FIXNUM_ADD1(inner_x1),y1_1,x_scale,y_scale,color_value,
	    filled_qm,filled_qm);
    paint_arc_or_circle_in_current_scratchpad_raster(x2,inner_y1,arc_x2,
	    arc_y1,FIXNUM_SUB1(inner_x2),y1_1,x_scale,y_scale,color_value,
	    filled_qm,filled_qm);
    paint_arc_or_circle_in_current_scratchpad_raster(x1,inner_y2,arc_x1,
	    arc_y2,FIXNUM_ADD1(inner_x1),y2,x_scale,y_scale,color_value,
	    filled_qm,filled_qm);
    paint_arc_or_circle_in_current_scratchpad_raster(x2,inner_y2,arc_x2,
	    arc_y2,FIXNUM_SUB1(inner_x2),y2,x_scale,y_scale,color_value,
	    filled_qm,filled_qm);
    if (filled_qm) {
	paint_solid_rectangle_in_current_scratchpad_raster(inner_x1_in_window,
		y1_in_window,inner_x2_in_window,inner_y1_in_window,
		color_value);
	paint_solid_rectangle_in_current_scratchpad_raster(x1_in_window,
		inner_y1_in_window,x2_in_window,inner_y2_in_window,
		color_value);
	return paint_solid_rectangle_in_current_scratchpad_raster(inner_x1_in_window,
		inner_y2_in_window,inner_x2_in_window,y2_in_window,
		color_value);
    }
    else {
	paint_line_in_current_scratchpad_raster(inner_x1_in_window,
		y1_in_window,inner_x2_in_window,y1_in_window,color_value,T);
	paint_line_in_current_scratchpad_raster(inner_x1_in_window,
		y2_in_window,inner_x2_in_window,y2_in_window,color_value,T);
	paint_line_in_current_scratchpad_raster(x1_in_window,
		inner_y1_in_window,x1_in_window,inner_y2_in_window,
		color_value,T);
	return paint_line_in_current_scratchpad_raster(x2_in_window,
		inner_y1_in_window,x2_in_window,inner_y2_in_window,
		color_value,T);
    }
}

/* ORIENT-AND-SCALE-AND-PAINT-ARC-OR-CIRCLE */
Object orient_and_scale_and_paint_arc_or_circle(x1,y1_1,x2,y2,x3,y3,
	    x_scale,y_scale,width_at_normalized_scale,
	    height_at_normalized_scale,reflection_and_rotation_qm,
	    color_value,circle_qm,filled_qm)
    Object x1, y1_1, x2, y2, x3, y3, x_scale, y_scale;
    Object width_at_normalized_scale, height_at_normalized_scale;
    Object reflection_and_rotation_qm, color_value, circle_qm, filled_qm;
{
    Object width, height, x1_temp, x2_temp, x3_temp;

    x_note_fn_call(63,86);
    width = width_at_normalized_scale;
    height = height_at_normalized_scale;
    if (reflection_and_rotation_qm) {
	if (EQ(reflection_and_rotation_qm,Qnormal));
	else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
	    x1_temp = FIXNUM_MINUS(height,y1_1);
	    y1_1 = x1;
	    x1 = x1_temp;
	    x2_temp = FIXNUM_MINUS(height,y2);
	    y2 = x2;
	    x2 = x2_temp;
	    x3_temp = FIXNUM_MINUS(height,y3);
	    y3 = x3;
	    x3 = x3_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
	    x1_temp = y1_1;
	    y1_1 = FIXNUM_MINUS(width,x1);
	    x1 = x1_temp;
	    x2_temp = y2;
	    y2 = FIXNUM_MINUS(width,x2);
	    x2 = x2_temp;
	    x3_temp = y3;
	    y3 = FIXNUM_MINUS(width,x3);
	    x3 = x3_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
	    x1_temp = y1_1;
	    y1_1 = x1;
	    x1 = x1_temp;
	    x2_temp = y2;
	    y2 = x2;
	    x2 = x2_temp;
	    x3_temp = y3;
	    y3 = x3;
	    x3 = x3_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
	    x1 = FIXNUM_MINUS(width,x1);
	    y1_1 = FIXNUM_MINUS(height,y1_1);
	    x2 = FIXNUM_MINUS(width,x2);
	    y2 = FIXNUM_MINUS(height,y2);
	    x3 = FIXNUM_MINUS(width,x3);
	    y3 = FIXNUM_MINUS(height,y3);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
	    x1_temp = FIXNUM_MINUS(height,y1_1);
	    y1_1 = FIXNUM_MINUS(width,x1);
	    x1 = x1_temp;
	    x2_temp = FIXNUM_MINUS(height,y2);
	    y2 = FIXNUM_MINUS(width,x2);
	    x2 = x2_temp;
	    x3_temp = FIXNUM_MINUS(height,y3);
	    y3 = FIXNUM_MINUS(width,x3);
	    x3 = x3_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected)) {
	    x1 = FIXNUM_MINUS(width,x1);
	    x2 = FIXNUM_MINUS(width,x2);
	    x3 = FIXNUM_MINUS(width,x3);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180)) {
	    y1_1 = FIXNUM_MINUS(height,y1_1);
	    y2 = FIXNUM_MINUS(height,y2);
	    y3 = FIXNUM_MINUS(height,y3);
	}
    }
    return paint_arc_or_circle_in_current_scratchpad_raster(x1,y1_1,x2,y2,
	    x3,y3,x_scale,y_scale,color_value,circle_qm,filled_qm);
}

/* ROTATE-POINT-IN-LINE-DRAWING-DESCRIPTION */
Object rotate_point_in_line_drawing_description(reflection_and_rotation,
	    block_width,block_height,x,y)
    Object reflection_and_rotation, block_width, block_height, x, y;
{
    Object reflection_and_rotation_qm, width, height, x_temp;

    x_note_fn_call(63,87);
    reflection_and_rotation_qm = reflection_and_rotation;
    width = block_width;
    height = block_height;
    if (reflection_and_rotation_qm) {
	if (EQ(reflection_and_rotation_qm,Qnormal));
	else if (EQ(reflection_and_rotation_qm,Qclockwise_90)) {
	    x_temp = FIXNUM_MINUS(height,y);
	    y = x;
	    x = x_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_270)) {
	    x_temp = y;
	    y = FIXNUM_MINUS(width,x);
	    x = x_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_270)) {
	    x_temp = y;
	    y = x;
	    x = x_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qclockwise_180)) {
	    x = FIXNUM_MINUS(width,x);
	    y = FIXNUM_MINUS(height,y);
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_90)) {
	    x_temp = FIXNUM_MINUS(height,y);
	    y = FIXNUM_MINUS(width,x);
	    x = x_temp;
	}
	else if (EQ(reflection_and_rotation_qm,Qreflected))
	    x = FIXNUM_MINUS(width,x);
	else if (EQ(reflection_and_rotation_qm,Qreflected_clockwise_180))
	    y = FIXNUM_MINUS(height,y);
    }
    return VALUES_2(x,y);
}

Object Reflection_and_rotation_multiplication_table_prop = UNBOUND;

static Object Qreflection_and_rotation_multiplication_table;  /* reflection-and-rotation-multiplication-table */

/* MULTIPLY-REFLECTION-AND-ROTATION */
Object multiply_reflection_and_rotation(reflection_and_rotation_1,
	    reflection_and_rotation_2)
    Object reflection_and_rotation_1, reflection_and_rotation_2;
{
    x_note_fn_call(63,88);
    if ( !TRUEP(reflection_and_rotation_1) || EQ(reflection_and_rotation_1,
	    Qnormal))
	return VALUES_1(reflection_and_rotation_2);
    else
	return getfq_function_no_default(getfq_function_no_default(INLINE_SYMBOL_PLIST(reflection_and_rotation_1),
		Qreflection_and_rotation_multiplication_table),
		reflection_and_rotation_2);
}

/* INVERT-REFLECTION-AND-ROTATION */
Object invert_reflection_and_rotation(reflection_and_rotation)
    Object reflection_and_rotation;
{
    Object multiplier, product, ab_loop_list_, temp;

    x_note_fn_call(63,89);
    if ( !TRUEP(reflection_and_rotation) || EQ(reflection_and_rotation,
	    Qnormal))
	return VALUES_1(Qnormal);
    else {
	multiplier = Nil;
	product = Nil;
	ab_loop_list_ = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(reflection_and_rotation),
		Qreflection_and_rotation_multiplication_table);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	multiplier = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	product = CAR(temp);
	if (EQ(product,Qnormal))
	    return VALUES_1(multiplier);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* LEGAL-REFLECTION-AND-ROTATION-SYMBOL-P */
Object legal_reflection_and_rotation_symbol_p(candidate_symbol)
    Object candidate_symbol;
{
    x_note_fn_call(63,90);
    return VALUES_1( ! 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(candidate_symbol),
	    Qreflection_and_rotation_multiplication_table)) ? T : Nil);
}

static Object Qicon_color;         /* icon-color */

/* CREATE-ICON-DESCRIPTION */
Object create_icon_description varargs_1(int, n)
{
    Object width_of_icon, height_of_icon, icon_line_drawing_description;
    Object icon_line_color_qm, icon_x_magnification_qm;
    Object icon_y_magnification_qm, x_offset_for_fine_positioning_of_icon_qm;
    Object y_offset_for_fine_positioning_of_icon_qm, region_extrema_qm;
    Object first_element, polychrome_header, slot_value_push_modify_macro_arg;
    Object car_1, cdr_1, cdr_new_value, temp, temp_1, icon_description;
    Declare_varargs_nonrelocating;

    x_note_fn_call(63,91);
    INIT_ARGS_nonrelocating();
    width_of_icon = REQUIRED_ARG_nonrelocating();
    height_of_icon = REQUIRED_ARG_nonrelocating();
    icon_line_drawing_description = REQUIRED_ARG_nonrelocating();
    icon_line_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    icon_x_magnification_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    icon_y_magnification_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    x_offset_for_fine_positioning_of_icon_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    y_offset_for_fine_positioning_of_icon_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    region_extrema_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    first_element = CAR(icon_line_drawing_description);
    if ( !(CONSP(first_element) && EQ(CAR(first_element),Qpolychrome) ? 
	    TRUEP(first_element) : TRUEP(Nil))) {
	polychrome_header = slot_value_cons_1(Qpolychrome,Nil);
	icon_line_drawing_description = 
		slot_value_cons_1(polychrome_header,
		icon_line_drawing_description);
	if (icon_line_color_qm) {
	    slot_value_push_modify_macro_arg = 
		    slot_value_cons_1(Qicon_color,icon_line_color_qm);
	    car_1 = slot_value_push_modify_macro_arg;
	    cdr_1 = CDR(polychrome_header);
	    cdr_new_value = slot_value_cons_1(car_1,cdr_1);
	    M_CDR(polychrome_header) = cdr_new_value;
	    car_1 = Qicon_color;
	    cdr_1 = CDR(icon_line_drawing_description);
	    cdr_new_value = slot_value_cons_1(car_1,cdr_1);
	    M_CDR(icon_line_drawing_description) = cdr_new_value;
	}
	if (memq_function(Qforeground,CDR(icon_line_drawing_description))) {
	    slot_value_push_modify_macro_arg = 
		    slot_value_cons_1(Qforeground,Qforeground);
	    car_1 = slot_value_push_modify_macro_arg;
	    cdr_1 = CDR(polychrome_header);
	    cdr_new_value = slot_value_cons_1(car_1,cdr_1);
	    M_CDR(polychrome_header) = cdr_new_value;
	}
    }
    temp = icon_line_drawing_description;
    first_element = CAR(icon_line_drawing_description);
    temp_1 = CONSP(first_element) && EQ(CAR(first_element),Qpolychrome) ? 
	    first_element : Nil;
    icon_description = make_icon_description_1(width_of_icon,
	    height_of_icon,x_offset_for_fine_positioning_of_icon_qm,
	    y_offset_for_fine_positioning_of_icon_qm,icon_line_color_qm,
	    icon_x_magnification_qm,icon_y_magnification_qm,temp,
	    CDR(temp_1),region_extrema_qm);
    return VALUES_1(icon_description);
}

static Object Qimage_info;         /* image-info */

/* GET-SAVABLE-IMAGE-INFO-FOR-IMAGE-NAME */
Object get_savable_image_info_for_image_name(image_name)
    Object image_name;
{
    x_note_fn_call(63,92);
    return slot_value_cons_1(Qimage_info,Nil);
}

static Object list_constant_4;     /* # */

static Object Qaquamarine;         /* aquamarine */

/* CREATE-GENSYM-LOGO-DESCRIPTION */
Object create_gensym_logo_description(bar_width)
    Object bar_width;
{
    Object half, diamonds_offset, half_diamonds_offset, bar_center, i, top;
    Object bottom, left, right, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_iter_flag_, temp;
    SI_Long logo_height, logo_width, x;

    x_note_fn_call(63,93);
    logo_height = (SI_Long)19L * IFIX(bar_width) - (SI_Long)1L;
    half = l_round(FIX(logo_height),FIX((SI_Long)2L));
    diamonds_offset = l_round(FIX((SI_Long)5L * IFIX(bar_width)),_);
    half_diamonds_offset = l_round(diamonds_offset,FIX((SI_Long)2L));
    logo_width = logo_height + IFIX(diamonds_offset);
    bar_center = FIXNUM_ADD(diamonds_offset,l_round(FIX(logo_height),
	    FIX((SI_Long)2L)));
    x = (SI_Long)0L;
    i = Nil;
    top = FIX((SI_Long)0L);
    bottom = Nil;
    left = Nil;
    right = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (x > (SI_Long)9L)
	goto end_loop;
    i = x < (SI_Long)5L ? FIX(x) : FIX((SI_Long)9L - x);
    if ( !TRUEP(ab_loop_iter_flag_))
	top = FIX(IFIX(top) + (IFIX(bar_width) << (SI_Long)1L));
    bottom = FIXNUM_ADD(bar_width,top);
    left = FIX(IFIX(bar_center) - (SI_Long)2L * IFIX(i) * IFIX(bar_width));
    right = FIX(IFIX(bar_center) + (SI_Long)2L * IFIX(i) * IFIX(bar_width));
    if (x == (SI_Long)0L) {
	ab_loopvar__2 = 
		LIST_1(create_filled_polygon_icon_description_element(LIST_3(CONS(bar_center,
		list_constant_4),LIST_2(FIXNUM_MINUS(bar_center,bar_width),
		bar_width),LIST_2(FIXNUM_ADD(bar_center,bar_width),
		bar_width))));
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    else if (x < (SI_Long)5L) {
	ab_loopvar__2 = 
		LIST_1(create_filled_polygon_icon_description_element(LIST_4(LIST_2(FIXNUM_MINUS(bar_center,
		top),top),LIST_2(FIXNUM_ADD(bar_center,top),top),
		LIST_2(FIXNUM_ADD(bar_center,bottom),bottom),
		LIST_2(FIXNUM_MINUS(bar_center,bottom),bottom))));
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    else if (x < (SI_Long)9L) {
	ab_loopvar__2 = 
		LIST_1(create_filled_polygon_icon_description_element(LIST_4(LIST_2(FIXNUM_MINUS(left,
		bar_width),top),LIST_2(FIXNUM_ADD(right,bar_width),top),
		LIST_2(right,bottom),LIST_2(left,bottom))));
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    else {
	ab_loopvar__2 = 
		LIST_1(create_filled_polygon_icon_description_element(LIST_3(LIST_2(FIXNUM_MINUS(bar_center,
		bar_width),top),LIST_2(FIXNUM_ADD(bar_center,bar_width),
		top),LIST_2(bar_center,FIX(logo_height)))));
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = 
		LIST_1(create_filled_polygon_icon_description_element(list(6,
		CONS(half,list_constant_4),LIST_2(FIX((SI_Long)0L),half),
		LIST_2(half,FIX(logo_height)),LIST_2(FIXNUM_ADD(half,
		half_diamonds_offset),FIX(logo_height - 
		IFIX(half_diamonds_offset))),LIST_2(diamonds_offset,half),
		LIST_2(FIXNUM_ADD(half,half_diamonds_offset),
		half_diamonds_offset))));
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    ab_loop_iter_flag_ = Nil;
    x = x + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return create_icon_description(4,FIX(logo_width),FIX(logo_height),temp,
	    Qaquamarine);
}

static Object Qlight_gray;         /* light-gray */

static Object Qpending_indicator;  /* pending-indicator */

static Object Qextra_light_gray;   /* extra-light-gray */

static Object Qg2_icon_light_shading;  /* g2-icon-light-shading */

static Object Qdark_gray;          /* dark-gray */

static Object Qg2_icon_dark_shading;  /* g2-icon-dark-shading */

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

/* CREATE-ACTION-BUTTON-DESCRIPTION */
Object create_action_button_description varargs_1(int, n)
{
    Object width, height;
    Object extra_color_pattern_elements, extra_line_drawing_elements;
    Object pending_indicator_override_color_qm;
    Object light_shading_override_color_qm, dark_shading_override_color_qm;
    Object temp, temp_1, temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(63,94);
    INIT_ARGS_nonrelocating();
    width = REQUIRED_ARG_nonrelocating();
    height = REQUIRED_ARG_nonrelocating();
    extra_color_pattern_elements = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    extra_line_drawing_elements = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    pending_indicator_override_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    light_shading_override_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    dark_shading_override_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = pending_indicator_override_color_qm;
    if (temp);
    else
	temp = Qlight_gray;
    temp_1 = CONS(Qpending_indicator,temp);
    temp = light_shading_override_color_qm;
    if (temp);
    else
	temp = Qextra_light_gray;
    temp_2 = CONS(Qg2_icon_light_shading,temp);
    temp = dark_shading_override_color_qm;
    if (temp);
    else
	temp = Qdark_gray;
    return create_icon_description(9,width,height,list_star(8,list_star(5,
	    Qpolychrome,temp_1,temp_2,CONS(Qg2_icon_dark_shading,temp),
	    extra_color_pattern_elements),Qpending_indicator,
	    list_constant_5,Qg2_icon_light_shading,list_constant_6,
	    Qg2_icon_dark_shading,list_constant_7,
	    extra_line_drawing_elements),Qnil,Nil,Nil,Nil,Nil,Nil);
}

static Object Qleft;               /* left */

static Object Qup;                 /* up */

static Object Qright;              /* right */

static Object list_constant_8;     /* # */

static Object Qdown;               /* down */

static Object list_constant_9;     /* # */

/* CREATE-ARROW-DESCRIPTION */
Object create_arrow_description(direction,arrow_width)
    Object direction, arrow_width;
{
    Object triangle, temp;

    x_note_fn_call(63,95);
    if (EQ(direction,Qleft))
	triangle = LIST_3(LIST_2(arrow_width,arrow_width),
		LIST_2(FIX((SI_Long)0L),FIX(IFIX(arrow_width) >>  -  - 
		(SI_Long)1L)),CONS(arrow_width,list_constant_4));
    else if (EQ(direction,Qup))
	triangle = LIST_3(LIST_2(FIX((SI_Long)0L),arrow_width),
		LIST_2(FIX(IFIX(arrow_width) >>  -  - (SI_Long)1L),
		FIX((SI_Long)0L)),LIST_2(arrow_width,arrow_width));
    else if (EQ(direction,Qright))
	triangle = LIST_3(list_constant_8,LIST_2(arrow_width,
		FIX(IFIX(arrow_width) >>  -  - (SI_Long)1L)),
		LIST_2(FIX((SI_Long)0L),arrow_width));
    else if (EQ(direction,Qdown))
	triangle = LIST_3(list_constant_8,LIST_2(FIX(IFIX(arrow_width) >>  
		-  - (SI_Long)1L),arrow_width),CONS(arrow_width,
		list_constant_4));
    else
	triangle = Qnil;
    temp = LIST_2(triangle,triangle);
    return create_icon_description(3,arrow_width,arrow_width,
	    LIST_4(list_constant_9,Qpending_indicator,Qforeground,
	    CONS(Qfilled_polygon,temp)));
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_region_minimum_x, Qcurrent_region_minimum_x);

DEFINE_VARIABLE_WITH_SYMBOL(Current_region_minimum_y, Qcurrent_region_minimum_y);

DEFINE_VARIABLE_WITH_SYMBOL(Current_region_maximum_x, Qcurrent_region_maximum_x);

DEFINE_VARIABLE_WITH_SYMBOL(Current_region_maximum_y, Qcurrent_region_maximum_y);

static Object Qlight_stipple;      /* light-stipple */

static Object Qmedium_stipple;     /* medium-stipple */

static Object Qdark_stipple;       /* dark-stipple */

static Object Qlight_texture;      /* light-texture */

static Object Qmedium_texture;     /* medium-texture */

static Object Qdark_texture;       /* dark-texture */

/* VALID-LINE-DRAWING-DESCRIPTION-P */
Object valid_line_drawing_description_p(width,height,
	    line_drawing_description,computed_values_plist)
    Object width, height, line_drawing_description, computed_values_plist;
{
    Object current_region_minimum_x, current_region_minimum_y;
    Object current_region_maximum_x, current_region_maximum_y, first_element;
    Object polychrome_header_qm, variable_header_qm, background_header_qm;
    Object region_extrema, current_region_qm, stipple_header_qm, header_count;
    Object description_elements, current_icon_untransformed_width;
    Object current_icon_untransformed_height, current_icon_variables_plist;
    Object current_icon_variables_override_plist, description_element;
    Object ab_loop_list_, temp, points, thing, point, remaining_points, p1, p2;
    Object p3, temp_2, temp_3, temp_4, temp_5, min_x, min_y, max_x, max_y;
    Object stipple, point_1_or_nil, point_2_or_nil, ab_loop_list__1;
    Object extrema_for_image_drawing_element, scale_qm, scale_x_qm, scale_y_qm;
    Object extrema_for_text_drawing_element;
    SI_Long unshifted_result;
    char temp_1, outline_case_qm;
    Declare_special(12);
    Object result;

    x_note_fn_call(63,96);
    current_region_minimum_x = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_region_minimum_x,Qcurrent_region_minimum_x,current_region_minimum_x,
	    11);
      current_region_minimum_y = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_region_minimum_y,Qcurrent_region_minimum_y,current_region_minimum_y,
	      10);
	current_region_maximum_x = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_region_maximum_x,Qcurrent_region_maximum_x,current_region_maximum_x,
		9);
	  current_region_maximum_y = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_region_maximum_y,Qcurrent_region_maximum_y,current_region_maximum_y,
		  8);
	    first_element = CAR(line_drawing_description);
	    polychrome_header_qm = CONSP(first_element) && 
		    EQ(CAR(first_element),Qpolychrome) ? first_element : Nil;
	    variable_header_qm = 
		    get_variable_specification_if_any(line_drawing_description);
	    background_header_qm = 
		    get_icon_background_layer_if_any(line_drawing_description);
	    region_extrema = initialize_region_extrema(polychrome_header_qm);
	    current_region_qm = Qforeground;
	    stipple_header_qm = 
		    get_icon_stipple_if_any(line_drawing_description);
	    header_count = FIX((SI_Long)0L);
	    if (polychrome_header_qm)
		header_count = FIXNUM_ADD1(header_count);
	    if (variable_header_qm)
		header_count = FIXNUM_ADD1(header_count);
	    if (background_header_qm)
		header_count = FIXNUM_ADD1(header_count);
	    if (stipple_header_qm)
		header_count = FIXNUM_ADD1(header_count);
	    description_elements = nthcdr(header_count,
		    line_drawing_description);
	    current_icon_untransformed_width = width;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
		    7);
	      current_icon_untransformed_height = height;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
		      6);
		current_icon_variables_plist = CDR(variable_header_qm);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
			5);
		  current_icon_variables_override_plist = 
			  computed_values_plist;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
			  4);
		    description_element = Nil;
		    ab_loop_list_ = description_elements;
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    description_element = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (ATOM(description_element)) {
			if (EQ(description_element,Qbackground) || 
				EQ(description_element,Qtransparent) || 
				EQ(description_element,Qforeground) || 
				polychrome_header_qm && 
				assq_function(description_element,
				CDR(polychrome_header_qm))) {
			    if (Current_region_minimum_x)
				add_extrema_to_current_region(region_extrema,
					current_region_qm,width,height,
					Current_region_minimum_x,
					Current_region_minimum_y,
					Current_region_maximum_x,
					Current_region_maximum_y);
			    Current_region_minimum_x = Nil;
			    Current_region_minimum_y = Nil;
			    Current_region_maximum_x = Nil;
			    Current_region_maximum_y = Nil;
			    current_region_qm = description_element;
			    temp = T;
			}
			else
			    temp = Nil;
		    }
		    else {
			points = CDR(description_element);
			current_icon_untransformed_width = width;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
				3);
			  current_icon_untransformed_height = height;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
				  2);
			    current_icon_variables_plist = 
				    CDR(variable_header_qm);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
				    1);
			      current_icon_variables_override_plist = 
				      computed_values_plist;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
				      0);
				temp = CAR(description_element);
				if (EQ(temp,Qpoint)) {
				    thing = CAR(points);
				    if (CONSP(thing)) {
					temp = CDR(thing);
					temp_1 = CONSP(temp);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if ((temp_1 ?  !TRUEP(CDDR(thing)) : 
					    TRUEP(Nil)) ?  
					    !TRUEP(CDR(points)) : TRUEP(Nil)) {
					point = CAR(points);
					temp = FIXNUMP(FIRST(point)) ? 
						FIRST(point) : 
						simple_eval_for_icon(FIRST(point));
					point = CAR(points);
					update_extrema_for_current_region(temp,
						FIXNUMP(SECOND(point)) ? 
						SECOND(point) : 
						simple_eval_for_icon(SECOND(point)));
					temp = T;
				    }
				    else
					temp = Nil;
				}
				else if (EQ(temp,Qlines) || EQ(temp,
					    Qoutline)) {
				    thing = CAR(points);
				    if (CONSP(thing)) {
					temp = CDR(thing);
					temp_1 = CONSP(temp);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1 ?  !TRUEP(CDDR(thing)) : 
					    TRUEP(Nil)) {
					if ( !TRUEP(CDR(points))) {
					    point = CAR(points);
					    temp = FIXNUMP(FIRST(point)) ? 
						    FIRST(point) : 
						    simple_eval_for_icon(FIRST(point));
					    point = CAR(points);
					    update_extrema_for_current_region(temp,
						    FIXNUMP(SECOND(point)) 
						    ? SECOND(point) : 
						    simple_eval_for_icon(SECOND(point)));
					    temp = T;
					}
					else {
					    outline_case_qm = 
						    EQ(FIRST(description_element),
						    Qoutline);
					    remaining_points = points;
					  next_loop_1:
					    if ( !TRUEP(remaining_points))
						goto end_loop_1;
					    thing = CAR(remaining_points);
					    if (CONSP(thing)) {
						temp = CDR(thing);
						temp_1 = CONSP(temp);
					    }
					    else
						temp_1 = TRUEP(Nil);
					    if ((temp_1 ?  
						    !TRUEP(CDDR(thing)) : 
						    TRUEP(Nil)) ? 
						    TRUEP(CDR(remaining_points)) 
						    : TRUEP(Nil)) {
						temp = CDR(remaining_points);
						thing = CAR(temp);
						if (CONSP(thing) && 
							EQ(M_CAR(thing),
							    Qarc)) {
						    temp = M_CDR(thing);
						    temp_1 = CONSP(temp);
						}
						else
						    temp_1 = TRUEP(Nil);
						if (temp_1 ?  
							!TRUEP(M_CDR(M_CDR(thing))) 
							: TRUEP(Nil)) {
						    thing = 
							    M_CAR(M_CDR(thing));
						    if (CONSP(thing)) {
							temp = CDR(thing);
							temp_1 = CONSP(temp);
						    }
						    else
							temp_1 = TRUEP(Nil);
						    temp_1 = temp_1 ?  
							    !TRUEP(CDDR(thing)) 
							    : TRUEP(Nil);
						}
						else
						    temp_1 = TRUEP(Nil);
					    }
					    else
						temp_1 = TRUEP(Nil);
					    if (temp_1) {
						if (CDDR(remaining_points)) {
						    temp = 
							    CDDR(remaining_points);
						    thing = CAR(temp);
						    if (CONSP(thing)) {
							temp = CDR(thing);
							temp_1 = CONSP(temp);
						    }
						    else
							temp_1 = TRUEP(Nil);
						    temp_1 = temp_1 ?  
							    !TRUEP(CDDR(thing)) 
							    : TRUEP(Nil);
						}
						else
						    temp_1 = outline_case_qm;
					    }
					    else
						temp_1 = TRUEP(Nil);
					    if (temp_1) {
						p1 = FIRST(remaining_points);
						temp = 
							SECOND(remaining_points);
						p2 = SECOND(temp);
						p3 = 
							CDDR(remaining_points) 
							? 
							THIRD(remaining_points) 
							: CAR(points);
						if (CONSP(p3) && 
							EQ(M_CAR(p3),Qarc)) {
						    temp = M_CDR(p3);
						    temp_1 = CONSP(temp);
						}
						else
						    temp_1 = TRUEP(Nil);
						if (temp_1 ?  
							!TRUEP(M_CDR(M_CDR(p3))) 
							: TRUEP(Nil)) {
						    thing = M_CAR(M_CDR(p3));
						    if (CONSP(thing)) {
							temp = CDR(thing);
							temp_1 = CONSP(temp);
						    }
						    else
							temp_1 = TRUEP(Nil);
						    temp_1 = temp_1 ?  
							    !TRUEP(CDDR(thing)) 
							    : TRUEP(Nil);
						}
						else
						    temp_1 = TRUEP(Nil);
						if (temp_1)
						    temp = Nil;
						else {
						    temp_2 = 
							    FIXNUMP(FIRST(p1)) 
							    ? FIRST(p1) : 
							    simple_eval_for_icon(FIRST(p1));
						    temp_3 = 
							    FIXNUMP(SECOND(p1)) 
							    ? SECOND(p1) : 
							    simple_eval_for_icon(SECOND(p1));
						    temp_4 = 
							    FIXNUMP(FIRST(p2)) 
							    ? FIRST(p2) : 
							    simple_eval_for_icon(FIRST(p2));
						    temp_5 = 
							    FIXNUMP(SECOND(p2)) 
							    ? SECOND(p2) : 
							    simple_eval_for_icon(SECOND(p2));
						    temp = 
							    FIXNUMP(FIRST(p3)) 
							    ? FIRST(p3) : 
							    simple_eval_for_icon(FIRST(p3));
						    result = compute_arc_bounding_box(temp_2,
							    temp_3,temp_4,
							    temp_5,temp,
							    FIXNUMP(SECOND(p3)) 
							    ? SECOND(p3) : 
							    simple_eval_for_icon(SECOND(p3)));
						    MVS_4(result,min_x,
							    min_y,max_x,max_y);
						    update_extrema_for_current_region(min_x,
							    min_y);
						    update_extrema_for_current_region(max_x,
							    max_y);
						    remaining_points = 
							    CDDR(remaining_points);
						    temp = T;
						}
					    }
					    else {
						thing = CAR(remaining_points);
						if (CONSP(thing)) {
						    temp = CDR(thing);
						    temp_1 = CONSP(temp);
						}
						else
						    temp_1 = TRUEP(Nil);
						if (temp_1 ?  
							!TRUEP(CDDR(thing)) 
							: TRUEP(Nil)) {
						    if (CDR(remaining_points)) 
								{
							temp = 
								CDR(remaining_points);
							thing = CAR(temp);
							if (CONSP(thing)) {
							    temp = CDR(thing);
							    temp_1 = 
								    CONSP(temp);
							}
							else
							    temp_1 = 
								    TRUEP(Nil);
							temp_1 = temp_1 ?  
								!TRUEP(CDDR(thing)) 
								: TRUEP(Nil);
						    }
						    else
							temp_1 = 
								outline_case_qm;
						}
						else
						    temp_1 = TRUEP(Nil);
						if (temp_1) {
						    p1 = CAR(remaining_points);
						    if (outline_case_qm)
							p2 = CAR(points);
						    else {
							temp = 
								CDR(remaining_points);
							p2 = CAR(temp);
						    }
						    temp = 
							    FIXNUMP(FIRST(p1)) 
							    ? FIRST(p1) : 
							    simple_eval_for_icon(FIRST(p1));
						    update_extrema_for_current_region(temp,
							    FIXNUMP(SECOND(p1)) 
							    ? SECOND(p1) : 
							    simple_eval_for_icon(SECOND(p1)));
						    temp = 
							    FIXNUMP(FIRST(p2)) 
							    ? FIRST(p2) : 
							    simple_eval_for_icon(FIRST(p2));
						    update_extrema_for_current_region(temp,
							    FIXNUMP(SECOND(p2)) 
							    ? SECOND(p2) : 
							    simple_eval_for_icon(SECOND(p2)));
						    remaining_points = 
							    outline_case_qm 
							    ? 
							    CDR(remaining_points) 
							    : 
							    CDR(remaining_points);
						    temp = T;
						}
						else {
						    thing = 
							    CAR(remaining_points);
						    if (CONSP(thing)) {
							temp = CDR(thing);
							temp_1 = CONSP(temp);
						    }
						    else
							temp_1 = TRUEP(Nil);
						    if (temp_1 ?  
							    !TRUEP(CDDR(thing)) 
							    : TRUEP(Nil)) {
							p1 = 
								CAR(remaining_points);
							temp = 
								FIXNUMP(FIRST(p1)) 
								? 
								FIRST(p1) :
								 
								simple_eval_for_icon(FIRST(p1));
							update_extrema_for_current_region(temp,
								FIXNUMP(SECOND(p1)) 
								? 
								SECOND(p1) 
								: 
								simple_eval_for_icon(SECOND(p1)));
							remaining_points = 
								CDR(remaining_points);
							temp = T;
						    }
						    else
							temp = Nil;
						}
					    }
					    if ( !TRUEP(temp)) {
						temp = Nil;
						goto end_1;
					    }
					    goto next_loop_1;
					  end_loop_1:
					    temp = T;
					    goto end_1;
					    temp = Qnil;
					  end_1:;
					    if (temp);
					    else
						temp = Qnil;
					}
				    }
				    else
					temp = Nil;
				}
				else if (EQ(temp,Qcircle) || EQ(temp,
					Qfilled_circle)) {
				    p1 = FIRST(points);
				    p2 = SECOND(points);
				    p3 = THIRD(points);
				    if (IFIX(length(points)) == (SI_Long)3L) {
					if (CONSP(p1)) {
					    temp = CDR(p1);
					    temp_1 = CONSP(temp);
					}
					else
					    temp_1 = TRUEP(Nil);
					temp_1 = temp_1 ?  
						!TRUEP(CDDR(p1)) : TRUEP(Nil);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1) {
					if (CONSP(p2)) {
					    temp = CDR(p2);
					    temp_1 = CONSP(temp);
					}
					else
					    temp_1 = TRUEP(Nil);
					temp_1 = temp_1 ?  
						!TRUEP(CDDR(p2)) : TRUEP(Nil);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1) {
					if (CONSP(p3)) {
					    temp = CDR(p3);
					    temp_1 = CONSP(temp);
					}
					else
					    temp_1 = TRUEP(Nil);
					temp_1 = temp_1 ?  
						!TRUEP(CDDR(p3)) : TRUEP(Nil);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1) {
					temp_2 = FIXNUMP(FIRST(p1)) ? 
						FIRST(p1) : 
						simple_eval_for_icon(FIRST(p1));
					temp_3 = FIXNUMP(SECOND(p1)) ? 
						SECOND(p1) : 
						simple_eval_for_icon(SECOND(p1));
					temp_4 = FIXNUMP(FIRST(p2)) ? 
						FIRST(p2) : 
						simple_eval_for_icon(FIRST(p2));
					temp_5 = FIXNUMP(SECOND(p2)) ? 
						SECOND(p2) : 
						simple_eval_for_icon(SECOND(p2));
					temp = FIXNUMP(FIRST(p3)) ? 
						FIRST(p3) : 
						simple_eval_for_icon(FIRST(p3));
					result = compute_circle_bounding_box(temp_2,
						temp_3,temp_4,temp_5,temp,
						FIXNUMP(SECOND(p3)) ? 
						SECOND(p3) : 
						simple_eval_for_icon(SECOND(p3)));
					MVS_4(result,min_x,min_y,max_x,max_y);
					update_extrema_for_current_region(min_x,
						min_y);
					update_extrema_for_current_region(max_x,
						max_y);
					temp = T;
				    }
				    else
					temp = Nil;
				}
				else if (EQ(temp,Qrounded_rectangle) || 
					EQ(temp,Qfilled_rounded_rectangle) 
					|| EQ(temp,Qsolid_rectangle)) {
				    p1 = FIRST(points);
				    p2 = SECOND(points);
				    if (CONSP(p1)) {
					temp = CDR(p1);
					temp_1 = CONSP(temp);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1 ?  !TRUEP(CDDR(p1)) : 
					    TRUEP(Nil)) {
					if (CONSP(p2)) {
					    temp = CDR(p2);
					    temp_1 = CONSP(temp);
					}
					else
					    temp_1 = TRUEP(Nil);
					temp_1 = temp_1 ?  
						!TRUEP(CDDR(p2)) : TRUEP(Nil);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1) {
					temp = FIXNUMP(FIRST(p1)) ? 
						FIRST(p1) : 
						simple_eval_for_icon(FIRST(p1));
					update_extrema_for_current_region(temp,
						FIXNUMP(SECOND(p1)) ? 
						SECOND(p1) : 
						simple_eval_for_icon(SECOND(p1)));
					temp = FIXNUMP(FIRST(p2)) ? 
						FIRST(p2) : 
						simple_eval_for_icon(FIRST(p2));
					update_extrema_for_current_region(temp,
						FIXNUMP(SECOND(p2)) ? 
						SECOND(p2) : 
						simple_eval_for_icon(SECOND(p2)));
					temp = T;
				    }
				    else
					temp = Nil;
				}
				else if (EQ(temp,Qstippled_area)) {
				    stipple = SECOND(description_element);
				    point_1_or_nil = 
					    THIRD(description_element);
				    point_2_or_nil = 
					    FOURTH(description_element);
				    if (EQ(stipple,Qlight_stipple) || 
					    EQ(stipple,Qmedium_stipple) || 
					    EQ(stipple,Qdark_stipple) || 
					    EQ(stipple,Qlight_texture) || 
					    EQ(stipple,Qmedium_texture) || 
					    EQ(stipple,Qdark_texture)) {
					temp =  
						!TRUEP(CDDR(description_element)) 
						? T : Nil;
					if (temp);
					else {
					    if (CONSP(point_1_or_nil)) {
						temp = CDR(point_1_or_nil);
						temp_1 = CONSP(temp);
					    }
					    else
						temp_1 = TRUEP(Nil);
					    if (temp_1 ?  
						    !TRUEP(CDDR(point_1_or_nil)) 
						    : TRUEP(Nil)) {
						if (CONSP(point_2_or_nil)) {
						    temp = CDR(point_2_or_nil);
						    temp_1 = CONSP(temp);
						}
						else
						    temp_1 = TRUEP(Nil);
						temp = temp_1 ? ( 
							!TRUEP(CDDR(point_2_or_nil)) 
							? T : Nil) : Nil;
					    }
					    else
						temp = Nil;
					}
				    }
				    else
					temp = Nil;
				}
				else if (EQ(temp,Qfilled_polygon)) {
				    point = Nil;
				    ab_loop_list__1 = 
					    SECOND(description_element);
				  next_loop_2:
				    if ( !TRUEP(ab_loop_list__1))
					goto end_loop_2;
				    point = M_CAR(ab_loop_list__1);
				    ab_loop_list__1 = M_CDR(ab_loop_list__1);
				    if (CONSP(point)) {
					temp = CDR(point);
					temp_1 = CONSP(temp);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1 ?  !TRUEP(CDDR(point)) : 
					    TRUEP(Nil)) {
					temp = FIXNUMP(FIRST(point)) ? 
						FIRST(point) : 
						simple_eval_for_icon(FIRST(point));
					update_extrema_for_current_region(temp,
						FIXNUMP(SECOND(point)) ? 
						SECOND(point) : 
						simple_eval_for_icon(SECOND(point)));
				    }
				    else {
					temp = Nil;
					goto end_2;
				    }
				    goto next_loop_2;
				  end_loop_2:
				    temp = T;
				    goto end_2;
				    temp = Qnil;
				  end_2:;
				}
				else if (EQ(temp,Qimage)) {
				    extrema_for_image_drawing_element = 
					    extrema_for_line_drawing_element(description_element,
					    slot_value_list_4(Nil,Nil,Nil,
					    Nil));
				    scale_qm = FOURTH(description_element);
				    scale_x_qm = CAR(scale_qm);
				    scale_y_qm = SECOND(scale_qm);
				    min_x = 
					    CAR(extrema_for_image_drawing_element);
				    min_y = 
					    SECOND(extrema_for_image_drawing_element);
				    max_x = 
					    THIRD(extrema_for_image_drawing_element);
				    max_y = 
					    FOURTH(extrema_for_image_drawing_element);
				    if (scale_qm) {
					if (IFIX(min_x) == (SI_Long)4096L)
					    min_x = scale_x_qm;
					else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						min_x) && FIXNUM_LT(min_x,
						Isqrt_of_most_positive_fixnum) 
						&& 
						FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						scale_x_qm) && 
						FIXNUM_LT(scale_x_qm,
						Isqrt_of_most_positive_fixnum)) 
						    {
					    unshifted_result = 
						    IFIX(FIXNUM_TIMES(min_x,
						    scale_x_qm)) + 
						    (SI_Long)2048L;
					    min_x = FIX(unshifted_result 
						    >>  -  - (SI_Long)12L);
					}
					else
					    min_x = scalef_function(min_x,
						    scale_x_qm);
					if (IFIX(min_y) == (SI_Long)4096L)
					    min_y = scale_y_qm;
					else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						min_y) && FIXNUM_LT(min_y,
						Isqrt_of_most_positive_fixnum) 
						&& 
						FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						scale_y_qm) && 
						FIXNUM_LT(scale_y_qm,
						Isqrt_of_most_positive_fixnum)) 
						    {
					    unshifted_result = 
						    IFIX(FIXNUM_TIMES(min_y,
						    scale_y_qm)) + 
						    (SI_Long)2048L;
					    min_y = FIX(unshifted_result 
						    >>  -  - (SI_Long)12L);
					}
					else
					    min_y = scalef_function(min_y,
						    scale_y_qm);
					if (IFIX(max_x) == (SI_Long)4096L)
					    max_x = scale_x_qm;
					else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						max_x) && FIXNUM_LT(max_x,
						Isqrt_of_most_positive_fixnum) 
						&& 
						FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						scale_x_qm) && 
						FIXNUM_LT(scale_x_qm,
						Isqrt_of_most_positive_fixnum)) 
						    {
					    unshifted_result = 
						    IFIX(FIXNUM_TIMES(max_x,
						    scale_x_qm)) + 
						    (SI_Long)2048L;
					    max_x = FIX(unshifted_result 
						    >>  -  - (SI_Long)12L);
					}
					else
					    max_x = scalef_function(max_x,
						    scale_x_qm);
					if (IFIX(max_y) == (SI_Long)4096L)
					    max_y = scale_y_qm;
					else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						max_y) && FIXNUM_LT(max_y,
						Isqrt_of_most_positive_fixnum) 
						&& 
						FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						scale_y_qm) && 
						FIXNUM_LT(scale_y_qm,
						Isqrt_of_most_positive_fixnum)) 
						    {
					    unshifted_result = 
						    IFIX(FIXNUM_TIMES(max_y,
						    scale_y_qm)) + 
						    (SI_Long)2048L;
					    max_y = FIX(unshifted_result 
						    >>  -  - (SI_Long)12L);
					}
					else
					    max_y = scalef_function(max_y,
						    scale_y_qm);
				    }
				    reclaim_slot_value(extrema_for_image_drawing_element);
				    update_extrema_for_current_region(min_x,
					    min_y);
				    update_extrema_for_current_region(max_x,
					    max_y);
				    temp = T;
				}
				else if (EQ(temp,Qtext)) {
				    extrema_for_text_drawing_element = 
					    compute_extrema_for_text_drawing_element(description_element,
					    slot_value_list_4(Nil,Nil,Nil,
					    Nil));
				    scale_qm = FIFTH(description_element);
				    scale_x_qm = CAR(scale_qm);
				    scale_y_qm = SECOND(scale_qm);
				    min_x = 
					    CAR(extrema_for_text_drawing_element);
				    min_y = 
					    SECOND(extrema_for_text_drawing_element);
				    max_x = 
					    THIRD(extrema_for_text_drawing_element);
				    max_y = 
					    FOURTH(extrema_for_text_drawing_element);
				    if (scale_qm) {
					if (IFIX(min_x) == (SI_Long)4096L)
					    min_x = scale_x_qm;
					else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						min_x) && FIXNUM_LT(min_x,
						Isqrt_of_most_positive_fixnum) 
						&& 
						FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						scale_x_qm) && 
						FIXNUM_LT(scale_x_qm,
						Isqrt_of_most_positive_fixnum)) 
						    {
					    unshifted_result = 
						    IFIX(FIXNUM_TIMES(min_x,
						    scale_x_qm)) + 
						    (SI_Long)2048L;
					    min_x = FIX(unshifted_result 
						    >>  -  - (SI_Long)12L);
					}
					else
					    min_x = scalef_function(min_x,
						    scale_x_qm);
					if (IFIX(min_y) == (SI_Long)4096L)
					    min_y = scale_y_qm;
					else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						min_y) && FIXNUM_LT(min_y,
						Isqrt_of_most_positive_fixnum) 
						&& 
						FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						scale_y_qm) && 
						FIXNUM_LT(scale_y_qm,
						Isqrt_of_most_positive_fixnum)) 
						    {
					    unshifted_result = 
						    IFIX(FIXNUM_TIMES(min_y,
						    scale_y_qm)) + 
						    (SI_Long)2048L;
					    min_y = FIX(unshifted_result 
						    >>  -  - (SI_Long)12L);
					}
					else
					    min_y = scalef_function(min_y,
						    scale_y_qm);
					if (IFIX(max_x) == (SI_Long)4096L)
					    max_x = scale_x_qm;
					else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						max_x) && FIXNUM_LT(max_x,
						Isqrt_of_most_positive_fixnum) 
						&& 
						FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						scale_x_qm) && 
						FIXNUM_LT(scale_x_qm,
						Isqrt_of_most_positive_fixnum)) 
						    {
					    unshifted_result = 
						    IFIX(FIXNUM_TIMES(max_x,
						    scale_x_qm)) + 
						    (SI_Long)2048L;
					    max_x = FIX(unshifted_result 
						    >>  -  - (SI_Long)12L);
					}
					else
					    max_x = scalef_function(max_x,
						    scale_x_qm);
					if (IFIX(max_y) == (SI_Long)4096L)
					    max_y = scale_y_qm;
					else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						max_y) && FIXNUM_LT(max_y,
						Isqrt_of_most_positive_fixnum) 
						&& 
						FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						scale_y_qm) && 
						FIXNUM_LT(scale_y_qm,
						Isqrt_of_most_positive_fixnum)) 
						    {
					    unshifted_result = 
						    IFIX(FIXNUM_TIMES(max_y,
						    scale_y_qm)) + 
						    (SI_Long)2048L;
					    max_y = FIX(unshifted_result 
						    >>  -  - (SI_Long)12L);
					}
					else
					    max_y = scalef_function(max_y,
						    scale_y_qm);
				    }
				    reclaim_slot_value(extrema_for_text_drawing_element);
				    update_extrema_for_current_region(min_x,
					    min_y);
				    update_extrema_for_current_region(max_x,
					    max_y);
				    temp = T;
				}
				else
				    temp = Nil;
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			if (temp);
			else
			    temp = Qnil;
		    }
		    if ( !TRUEP(temp)) {
			result = VALUES_2(Nil,description_element);
			goto end_3;
		    }
		    goto next_loop;
		  end_loop:
		    if (Current_region_minimum_x)
			add_extrema_to_current_region(region_extrema,
				current_region_qm,width,height,
				Current_region_minimum_x,
				Current_region_minimum_y,
				Current_region_maximum_x,
				Current_region_maximum_y);
		    result = VALUES_2(T,region_extrema);
		    goto end_3;
		    result = VALUES_1(Qnil);
		  end_3:;
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* INITIALIZE-REGION-EXTREMA */
Object initialize_region_extrema(polychrome_header_qm)
    Object polychrome_header_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, region_pair, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, car_new_value;

    x_note_fn_call(63,97);
    if ( !TRUEP(polychrome_header_qm)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qforeground;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	return gensym_cons_1(gensymed_symbol,Nil);
    }
    else if ( !TRUEP(CDR(polychrome_header_qm))) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qforeground;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	return gensym_cons_1(gensymed_symbol,Nil);
    }
    else {
	region_pair = Nil;
	ab_loop_list_ = CDR(polychrome_header_qm);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	region_pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	car_new_value = CAR(region_pair);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	ab_loopvar__2 = gensym_cons_1(gensymed_symbol,Nil);
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
}

/* ADD-EXTREMA-TO-CURRENT-REGION */
Object add_extrema_to_current_region(region_extrema,current_region,width,
	    height,minimum_x,minimum_y,maximum_x,maximum_y)
    Object region_extrema, current_region, width, height, minimum_x, minimum_y;
    Object maximum_x, maximum_y;
{
    Object entry, temp, temp_1;

    x_note_fn_call(63,98);
    minimum_x = FIX(MAX(IFIX(minimum_x),(SI_Long)0L));
    minimum_y = FIX(MAX(IFIX(minimum_y),(SI_Long)0L));
    maximum_x = FIXNUM_MIN(maximum_x,width);
    maximum_y = FIXNUM_MIN(maximum_y,height);
    entry = assq_function(current_region,region_extrema);
    temp =  !TRUEP(entry) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if ( !TRUEP(SECOND(entry))) {
	M_SECOND(entry) = minimum_x;
	M_THIRD(entry) = minimum_y;
	M_FOURTH(entry) = maximum_x;
	return VALUES_1(M_FIFTH(entry) = maximum_y);
    }
    else {
	temp = SECOND(entry);
	temp_1 = FIXNUM_MIN(minimum_x,temp);
	M_SECOND(entry) = temp_1;
	temp = THIRD(entry);
	temp_1 = FIXNUM_MIN(minimum_y,temp);
	M_THIRD(entry) = temp_1;
	temp = FOURTH(entry);
	temp_1 = FIXNUM_MAX(maximum_x,temp);
	M_FOURTH(entry) = temp_1;
	temp = FIFTH(entry);
	temp_1 = FIXNUM_MAX(maximum_y,temp);
	return VALUES_1(M_FIFTH(entry) = temp_1);
    }
}

/* UPDATE-EXTREMA-FOR-CURRENT-REGION */
Object update_extrema_for_current_region(x,y)
    Object x, y;
{
    Object temp;

    x_note_fn_call(63,99);
    temp = x;
    if (temp);
    else
	temp = Current_region_minimum_x;
    x = temp;
    temp = y;
    if (temp);
    else
	temp = Current_region_minimum_y;
    y = temp;
    if ( !TRUEP(Current_region_minimum_x)) {
	Current_region_minimum_x = x;
	Current_region_minimum_y = y;
	Current_region_maximum_x = x;
	Current_region_maximum_y = y;
	return VALUES_1(Current_region_maximum_y);
    }
    else {
	Current_region_minimum_x = FIXNUM_MIN(Current_region_minimum_x,x);
	Current_region_minimum_y = FIXNUM_MIN(Current_region_minimum_y,y);
	Current_region_maximum_x = FIXNUM_MAX(Current_region_maximum_x,x);
	Current_region_maximum_y = FIXNUM_MAX(Current_region_maximum_y,y);
	return VALUES_1(Current_region_maximum_y);
    }
}

/* CREATE-FILLED-POLYGON-ICON-DESCRIPTION-ELEMENT */
Object create_filled_polygon_icon_description_element(simple_polygon)
    Object simple_polygon;
{
    x_note_fn_call(63,100);
    return list_star(3,Qfilled_polygon,simple_polygon,decompose_polygon(2,
	    simple_polygon,Qcons));
}

DEFINE_VARIABLE_WITH_SYMBOL(Global_temp_1, Qglobal_temp_1);

DEFINE_VARIABLE_WITH_SYMBOL(Global_temp_2, Qglobal_temp_2);

DEFINE_VARIABLE_WITH_SYMBOL(Global_temp_3, Qglobal_temp_3);

/* SENSE-OF-VECTOR-ANGLE */
Object sense_of_vector_angle(x1,y1_1,x2,y2)
    Object x1, y1_1, x2, y2;
{
    Object temp;

    x_note_fn_call(63,101);
    Global_temp_1 = ltimes(x1,y2);
    Global_temp_2 = ltimes(x2,y1_1);
    Global_temp_3 = minus(Global_temp_1,Global_temp_2);
    temp = FIX((SI_Long)0L);
    if (NUM_EQ(Global_temp_3,temp))
	return VALUES_1(FIX((SI_Long)0L));
    else {
	temp = FIX((SI_Long)0L);
	if (NUM_LT(Global_temp_3,temp))
	    return VALUES_1(FIX((SI_Long)-1L));
	else
	    return VALUES_1(FIX((SI_Long)1L));
    }
}

/* LINES-INTERSECT-P */
Object lines_intersect_p(x1,y1_1,x2,y2,x3,y3,x4,y4)
    Object x1, y1_1, x2, y2, x3, y3, x4, y4;
{
    Object s1_1, s2_1, s3, s4, temp;

    x_note_fn_call(63,102);
    if ((FIXNUM_LE(x1,x3) ? FIXNUM_GE(FIXNUM_MAX(x1,x2),FIXNUM_MIN(x3,x4)) 
	    : FIXNUM_GE(FIXNUM_MAX(x3,x4),FIXNUM_MIN(x1,x2))) && 
	    (FIXNUM_LE(y1_1,y3) ? FIXNUM_GE(FIXNUM_MAX(y1_1,y2),
	    FIXNUM_MIN(y3,y4)) : FIXNUM_GE(FIXNUM_MAX(y3,y4),
	    FIXNUM_MIN(y1_1,y2)))) {
	s1_1 = sense_of_vector_angle(FIXNUM_MINUS(x2,x1),FIXNUM_MINUS(y2,
		y1_1),FIXNUM_MINUS(x3,x1),FIXNUM_MINUS(y3,y1_1));
	s2_1 = sense_of_vector_angle(FIXNUM_MINUS(x2,x1),FIXNUM_MINUS(y2,
		y1_1),FIXNUM_MINUS(x4,x1),FIXNUM_MINUS(y4,y1_1));
	if (IFIX(s1_1) >= (SI_Long)0L && IFIX(s2_1) <= (SI_Long)0L || 
		IFIX(s1_1) <= (SI_Long)0L && IFIX(s2_1) >= (SI_Long)0L) {
	    s3 = sense_of_vector_angle(FIXNUM_MINUS(x4,x3),FIXNUM_MINUS(y4,
		    y3),FIXNUM_MINUS(x1,x3),FIXNUM_MINUS(y1_1,y3));
	    s4 = sense_of_vector_angle(FIXNUM_MINUS(x4,x3),FIXNUM_MINUS(y4,
		    y3),FIXNUM_MINUS(x2,x3),FIXNUM_MINUS(y2,y3));
	    temp = IFIX(s3) >= (SI_Long)0L ? (IFIX(s4) <= (SI_Long)0L ? T :
		     Nil) : Qnil;
	    if (temp)
		return VALUES_1(temp);
	    else if (IFIX(s3) <= (SI_Long)0L)
		return VALUES_1(IFIX(s4) >= (SI_Long)0L ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* SIMPLE-POLYGON-P */
Object simple_polygon_p(polygon)
    Object polygon;
{
    Object tail, p1, p2, temp, length_1, tail_1, x1, y1_1, x2, y2;
    Object ab_loop_iter_flag_, tail_2, p3, p4, x3, y3, x4, y4;
    SI_Long i, ab_loop_bind_, j, ab_loop_bind__1;
    char temp_1;

    x_note_fn_call(63,103);
    tail = polygon;
    p1 = Nil;
    p2 = Nil;
  next_loop:
    if ( !TRUEP(tail))
	goto end_loop;
    p1 = FIRST(tail);
    p2 = CDR(tail) ? SECOND(tail) : FIRST(polygon);
    temp = FIXNUMP(FIRST(p1)) ? FIRST(p1) : simple_eval_for_icon(FIRST(p1));
    if (FIXNUM_EQ(temp,FIXNUMP(FIRST(p2)) ? FIRST(p2) : 
	    simple_eval_for_icon(FIRST(p2)))) {
	temp = FIXNUMP(SECOND(p1)) ? SECOND(p1) : 
		simple_eval_for_icon(SECOND(p1));
	temp_1 = FIXNUM_EQ(temp,FIXNUMP(SECOND(p2)) ? SECOND(p2) : 
		simple_eval_for_icon(SECOND(p2)));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_1 = TRUEP(Nil);
	goto end_1;
    }
    tail = M_CDR(tail);
    goto next_loop;
  end_loop:
    temp_1 = TRUEP(T);
    goto end_1;
    temp_1 = TRUEP(Qnil);
  end_1:;
    if (temp_1) {
	length_1 = length(polygon);
	i = (SI_Long)1L;
	ab_loop_bind_ = IFIX(length_1) - (SI_Long)2L;
	tail_1 = polygon;
	p1 = Nil;
	p2 = Nil;
	x1 = Nil;
	y1_1 = Nil;
	x2 = Nil;
	y2 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (i > ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    tail_1 = M_CDR(tail_1);
	if ( !TRUEP(tail_1))
	    goto end_loop_1;
	p1 = FIRST(tail_1);
	p2 = SECOND(tail_1);
	x1 = FIXNUMP(FIRST(p1)) ? FIRST(p1) : simple_eval_for_icon(FIRST(p1));
	y1_1 = FIXNUMP(SECOND(p1)) ? SECOND(p1) : 
		simple_eval_for_icon(SECOND(p1));
	x2 = FIXNUMP(FIRST(p2)) ? FIRST(p2) : simple_eval_for_icon(FIRST(p2));
	y2 = FIXNUMP(SECOND(p2)) ? SECOND(p2) : 
		simple_eval_for_icon(SECOND(p2));
	j = i + (SI_Long)2L;
	ab_loop_bind__1 = i == (SI_Long)1L ? IFIX(FIXNUM_SUB1(length_1)) : 
		IFIX(length_1);
	tail_2 = CDDR(tail_1);
	p3 = Nil;
	p4 = Nil;
	x3 = Nil;
	y3 = Nil;
	x4 = Nil;
	y4 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_2:
	if (j > ab_loop_bind__1)
	    goto end_loop_2;
	if ( !TRUEP(ab_loop_iter_flag_))
	    tail_2 = M_CDR(tail_2);
	if ( !TRUEP(tail_2))
	    goto end_loop_2;
	p3 = FIRST(tail_2);
	p4 = CDR(tail_2) ? SECOND(tail_2) : FIRST(polygon);
	x3 = FIXNUMP(FIRST(p3)) ? FIRST(p3) : simple_eval_for_icon(FIRST(p3));
	y3 = FIXNUMP(SECOND(p3)) ? SECOND(p3) : 
		simple_eval_for_icon(SECOND(p3));
	x4 = FIXNUMP(FIRST(p4)) ? FIRST(p4) : simple_eval_for_icon(FIRST(p4));
	y4 = FIXNUMP(SECOND(p4)) ? SECOND(p4) : 
		simple_eval_for_icon(SECOND(p4));
	if (lines_intersect_p(x1,y1_1,x2,y2,x3,y3,x4,y4)) {
	    temp_1 = TRUEP(Nil);
	    goto end_2;
	}
	ab_loop_iter_flag_ = Nil;
	j = j + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	temp_1 = TRUEP(T);
	goto end_2;
	temp_1 = TRUEP(Qnil);
      end_2:;
	if ( !temp_1)
	    return VALUES_1(Nil);
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CLOCKWISE-POLYGON-P */
Object clockwise_polygon_p(polygon)
    Object polygon;
{
    Object node_num, min_x_value, min_y_value, p1, p2, p3, x1, y1_1, x2, y2;
    Object x3, y3, vertex, ab_loop_list_, x_value, y_value, ab_loop_iter_flag_;
    Object temp;
    SI_Long n_1;

    x_note_fn_call(63,104);
    node_num = FIX((SI_Long)1L);
    min_x_value = Most_positive_fixnum;
    min_y_value = min_x_value;
    p1 = Nil;
    p2 = Nil;
    p3 = Nil;
    x1 = Nil;
    y1_1 = Nil;
    x2 = Nil;
    y2 = Nil;
    x3 = Nil;
    y3 = Nil;
    vertex = Nil;
    ab_loop_list_ = polygon;
    x_value = Nil;
    y_value = Nil;
    n_1 = (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    vertex = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    x_value = FIXNUMP(FIRST(vertex)) ? FIRST(vertex) : 
	    simple_eval_for_icon(FIRST(vertex));
    y_value = FIXNUMP(SECOND(vertex)) ? SECOND(vertex) : 
	    simple_eval_for_icon(SECOND(vertex));
    if ( !TRUEP(ab_loop_iter_flag_))
	n_1 = n_1 + (SI_Long)1L;
    if (FIXNUM_LT(x_value,min_x_value) || FIXNUM_EQ(x_value,min_x_value) 
	    && FIXNUM_LE(y_value,min_y_value)) {
	node_num = FIX(n_1);
	min_x_value = x_value;
	min_y_value = y_value;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    if (IFIX(node_num) == (SI_Long)1L) {
	temp = last(polygon,_);
	p1 = FIRST(temp);
    }
    else
	p1 = nth(FIX(IFIX(node_num) - (SI_Long)2L),polygon);
    p2 = nth(FIXNUM_SUB1(node_num),polygon);
    p3 = IFIX(node_num) == n_1 ? FIRST(polygon) : nth(node_num,polygon);
    x1 = FIXNUMP(FIRST(p1)) ? FIRST(p1) : simple_eval_for_icon(FIRST(p1));
    y1_1 = FIXNUMP(SECOND(p1)) ? SECOND(p1) : simple_eval_for_icon(SECOND(p1));
    x2 = FIXNUMP(FIRST(p2)) ? FIRST(p2) : simple_eval_for_icon(FIRST(p2));
    y2 = FIXNUMP(SECOND(p2)) ? SECOND(p2) : simple_eval_for_icon(SECOND(p2));
    x3 = FIXNUMP(FIRST(p3)) ? FIRST(p3) : simple_eval_for_icon(FIRST(p3));
    y3 = FIXNUMP(SECOND(p3)) ? SECOND(p3) : simple_eval_for_icon(SECOND(p3));
    return VALUES_1(IFIX(sense_of_vector_angle(FIXNUM_MINUS(x2,x1),
	    FIXNUM_MINUS(y2,y1_1),FIXNUM_MINUS(x3,x2),FIXNUM_MINUS(y3,
	    y2))) >= (SI_Long)0L ? T : Nil);
    return VALUES_1(Qnil);
}

static Object Qphrase_cons;        /* phrase-cons */

/* DECOMPOSE-POLYGON */
Object decompose_polygon varargs_1(int, n)
{
    Object polygon;
    Object cons_function_qm, result_1, element, ab_loop_list_, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(63,105);
    INIT_ARGS_nonrelocating();
    polygon = REQUIRED_ARG_nonrelocating();
    cons_function_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(clockwise_polygon_p(polygon))) {
	result_1 = Nil;
	element = Nil;
	ab_loop_list_ = polygon;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = cons_function_qm;
	if (temp);
	else
	    temp = Qphrase_cons;
	result_1 = FUNCALL_2(temp,element,result_1);
	goto next_loop;
      end_loop:
	temp_1 = result_1;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = polygon;
    temp = cons_function_qm;
    if (temp);
    else
	temp = Qphrase_cons;
    return decompose_polygon_1(temp_1,temp);
}

/* DECOMPOSE-POLYGON-1 */
Object decompose_polygon_1(clockwise_polygon,cons_function)
    Object clockwise_polygon, cons_function;
{
    Object poly_1, poly_2, temp;
    Object result;

    x_note_fn_call(63,106);
    if (IFIX(length(clockwise_polygon)) == (SI_Long)3L)
	return FUNCALL_2(cons_function,clockwise_polygon,Nil);
    else {
	result = divide_polygon(clockwise_polygon,cons_function);
	MVS_2(result,poly_1,poly_2);
	temp = decompose_polygon_1(poly_1,cons_function);
	return VALUES_1(nconc2(temp,decompose_polygon_1(poly_2,
		cons_function)));
    }
}

/* DIVIDE-POLYGON */
Object divide_polygon(polygon,cons_function)
    Object polygon, cons_function;
{
    Object length_1, tail_1, v1, x1, y1_1, ab_loop_iter_flag_, poly_1, poly_2;
    Object tail_2, v2, x2, y2, tail_3, v3, v4, temp, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long i, ab_loop_bind_, j, ab_loop_bind__1, k, r, ab_loop_bind__2;
    char temp_7;

    x_note_fn_call(63,107);
    length_1 = length(polygon);
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(length_1) - (SI_Long)2L;
    tail_1 = polygon;
    v1 = Nil;
    x1 = Nil;
    y1_1 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	tail_1 = M_CDR(tail_1);
    if ( !TRUEP(tail_1))
	goto end_loop;
    v1 = CAR(tail_1);
    x1 = FIXNUMP(FIRST(v1)) ? FIRST(v1) : simple_eval_for_icon(FIRST(v1));
    y1_1 = FIXNUMP(SECOND(v1)) ? SECOND(v1) : simple_eval_for_icon(SECOND(v1));
    poly_1 = Nil;
    poly_2 = Nil;
    j = i + (SI_Long)2L;
    ab_loop_bind__1 = IFIX(length_1);
    tail_2 = CDDR(tail_1);
    v2 = Nil;
    x2 = Nil;
    y2 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if (j > ab_loop_bind__1)
	goto end_loop_1;
    if ( !TRUEP(ab_loop_iter_flag_))
	tail_2 = M_CDR(tail_2);
    if ( !TRUEP(tail_2))
	goto end_loop_1;
    v2 = CAR(tail_2);
    x2 = FIXNUMP(FIRST(v2)) ? FIRST(v2) : simple_eval_for_icon(FIRST(v2));
    y2 = FIXNUMP(SECOND(v2)) ? SECOND(v2) : simple_eval_for_icon(SECOND(v2));
    if (i != (SI_Long)1L || j != IFIX(length_1)) {
	tail_3 = polygon;
	k = (SI_Long)1L;
	v3 = Nil;
	v4 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_2:
	if ( !TRUEP(tail_3))
	    goto end_loop_2;
	if ( !TRUEP(ab_loop_iter_flag_))
	    k = k + (SI_Long)1L;
	v3 = FIRST(tail_3);
	v4 = CDR(tail_3) ? SECOND(tail_3) : FIRST(polygon);
	if ((i == (SI_Long)1L ? k != IFIX(length_1) : k != i - 
		(SI_Long)1L) && k != i && k != j - (SI_Long)1L && k != j) {
	    temp = x1;
	    temp_1 = y1_1;
	    temp_2 = x2;
	    temp_3 = y2;
	    temp_4 = FIXNUMP(FIRST(v3)) ? FIRST(v3) : 
		    simple_eval_for_icon(FIRST(v3));
	    temp_5 = FIXNUMP(SECOND(v3)) ? SECOND(v3) : 
		    simple_eval_for_icon(SECOND(v3));
	    temp_6 = FIXNUMP(FIRST(v4)) ? FIRST(v4) : 
		    simple_eval_for_icon(FIRST(v4));
	    temp_7 = TRUEP(lines_intersect_p(temp,temp_1,temp_2,temp_3,
		    temp_4,temp_5,temp_6,FIXNUMP(SECOND(v4)) ? SECOND(v4) :
		     simple_eval_for_icon(SECOND(v4))));
	}
	else
	    temp_7 = TRUEP(Nil);
	if (temp_7) {
	    temp_7 = TRUEP(Nil);
	    goto end_1;
	}
	ab_loop_iter_flag_ = Nil;
	tail_3 = M_CDR(tail_3);
	goto next_loop_2;
      end_loop_2:
	temp_7 = TRUEP(T);
	goto end_1;
	temp_7 = TRUEP(Qnil);
      end_1:;
    }
    else
	temp_7 = TRUEP(Nil);
    if (temp_7) {
	r = i - (SI_Long)1L;
	ab_loop_bind__2 = j - (SI_Long)1L;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_3:
	if (r > ab_loop_bind__2)
	    goto end_loop_3;
	ab_loopvar__2 = FUNCALL_2(cons_function,nth(FIX(r),polygon),Nil);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	r = r + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:
	poly_1 = ab_loopvar_;
	goto end_2;
	poly_1 = Qnil;
      end_2:;
	r = j - (SI_Long)1L;
	ab_loop_bind__2 = i - (SI_Long)1L + IFIX(length_1);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_4:
	if (r > ab_loop_bind__2)
	    goto end_loop_4;
	ab_loopvar__2 = FUNCALL_2(cons_function,nth(mod(FIX(r),length_1),
		polygon),Nil);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	r = r + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:
	poly_2 = ab_loopvar_;
	goto end_3;
	poly_2 = Qnil;
      end_3:;
	if (clockwise_polygon_p(poly_1) && clockwise_polygon_p(poly_2))
	    return VALUES_2(poly_1,poly_2);
    }
    ab_loop_iter_flag_ = Nil;
    j = j + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* OVERRIDE-ICON-DESCRIPTION-FOR-SYSTEM-DEFINED-CLASS */
Object override_icon_description_for_system_defined_class varargs_1(int, n)
{
    Object system_defined_class, icon_description;
    Object stub_feature_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(63,108);
    INIT_ARGS_nonrelocating();
    system_defined_class = REQUIRED_ARG_nonrelocating();
    icon_description = REQUIRED_ARG_nonrelocating();
    stub_feature_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return override_icon_description_for_system_defined_class_ab(3,
	    system_defined_class,icon_description,stub_feature_qm);
}

void icons_INIT()
{
    Object temp, reclaim_structure_for_icon_description_1;
    Object AB_package, list_constant_50, list_constant_49, list_constant_48;
    Object list_constant_47, list_constant_46, list_constant_45;
    Object list_constant_34, list_constant_32, list_constant_44;
    Object list_constant_36, list_constant_43, list_constant_37;
    Object list_constant_35, list_constant_31, list_constant_30;
    Object list_constant_28, list_constant_42, list_constant_41;
    Object list_constant_38, list_constant_40, list_constant_39;
    Object list_constant_33, list_constant_29, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object list_constant_23, list_constant_22, list_constant_21;
    Object list_constant_20, list_constant_19, list_constant_18;
    Object list_constant_17, list_constant_16, list_constant_15;
    Object list_constant_14, list_constant_13, list_constant_12, Qicons;
    Object Qicon_description, Qreclaim_structure;
    Object Qoutstanding_icon_description_count;
    Object Qicon_description_structure_memory_usage, Qutilities2;
    Object string_constant_3, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_2, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_1;
    Object Qentity_cons_memory_usage, Qoutstanding_entity_conses, Qentities;
    Object list_constant_11, Qentity_cons_counter_vector, list_constant_10;
    Object Qavailable_entity_conses_tail_vector;
    Object Qavailable_entity_conses_vector, string_constant;
    Object Qslot_value_cons_memory_usage, Qoutstanding_slot_value_conses;
    Object Qslot_value_cons_counter_vector, Qmake_thread_array, Kfuncall;
    Object Qavailable_slot_value_conses_tail_vector;
    Object Qavailable_slot_value_conses_vector;

    x_note_fn_call(63,109);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_slot_value_conses = 
	    STATIC_SYMBOL("AVAILABLE-SLOT-VALUE-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_slot_value_conses,
	    Available_slot_value_conses);
    Qicons = STATIC_SYMBOL("ICONS",AB_package);
    record_system_variable(Qavailable_slot_value_conses,Qicons,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_slot_value_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-SLOT-VALUE-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_slot_value_conses_tail,
	    Available_slot_value_conses_tail);
    record_system_variable(Qavailable_slot_value_conses_tail,Qicons,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_slot_value_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-SLOT-VALUE-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_slot_value_conses_vector,
	    Available_slot_value_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_slot_value_conses_vector,Qicons,
	    list_constant_10,Qnil,Qt,Qnil,Qnil);
    Qavailable_slot_value_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-SLOT-VALUE-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_slot_value_conses_tail_vector,
	    Available_slot_value_conses_tail_vector);
    record_system_variable(Qavailable_slot_value_conses_tail_vector,Qicons,
	    list_constant_10,Qnil,Qt,Qnil,Qnil);
    Qslot_value_cons_counter_vector = 
	    STATIC_SYMBOL("SLOT-VALUE-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qslot_value_cons_counter_vector,
	    Slot_value_cons_counter_vector);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qslot_value_cons_counter_vector,Qicons,
	    list_constant_11,Qnil,Qt,Qnil,Qnil);
    Qslot_value_cons_counter = STATIC_SYMBOL("SLOT-VALUE-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qslot_value_cons_counter,
	    Slot_value_cons_counter);
    record_system_variable(Qslot_value_cons_counter,Qicons,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_slot_value_conses = 
	    STATIC_SYMBOL("OUTSTANDING-SLOT-VALUE-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_slot_value_conses,
	    STATIC_FUNCTION(outstanding_slot_value_conses,NIL,FALSE,0,0));
    Qslot_value_cons_memory_usage = 
	    STATIC_SYMBOL("SLOT-VALUE-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qslot_value_cons_memory_usage,
	    STATIC_FUNCTION(slot_value_cons_memory_usage,NIL,FALSE,0,0));
    string_constant = STATIC_STRING("1q83-q6y9k83-q5y09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_slot_value_conses);
    push_optimized_constant(Qslot_value_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant));
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qavailable_entity_conses = STATIC_SYMBOL("AVAILABLE-ENTITY-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_entity_conses,
	    Available_entity_conses);
    Qentities = STATIC_SYMBOL("ENTITIES",AB_package);
    record_system_variable(Qavailable_entity_conses,Qentities,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_entity_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-ENTITY-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_entity_conses_tail,
	    Available_entity_conses_tail);
    record_system_variable(Qavailable_entity_conses_tail,Qentities,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_entity_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-ENTITY-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_entity_conses_vector,
	    Available_entity_conses_vector);
    record_system_variable(Qavailable_entity_conses_vector,Qentities,
	    list_constant_10,Qnil,Qt,Qnil,Qnil);
    Qavailable_entity_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-ENTITY-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_entity_conses_tail_vector,
	    Available_entity_conses_tail_vector);
    record_system_variable(Qavailable_entity_conses_tail_vector,Qentities,
	    list_constant_10,Qnil,Qt,Qnil,Qnil);
    Qentity_cons_counter_vector = 
	    STATIC_SYMBOL("ENTITY-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qentity_cons_counter_vector,
	    Entity_cons_counter_vector);
    record_system_variable(Qentity_cons_counter_vector,Qentities,
	    list_constant_11,Qnil,Qt,Qnil,Qnil);
    Qentity_cons_counter = STATIC_SYMBOL("ENTITY-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qentity_cons_counter,Entity_cons_counter);
    record_system_variable(Qentity_cons_counter,Qentities,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    Qoutstanding_entity_conses = STATIC_SYMBOL("OUTSTANDING-ENTITY-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_entity_conses,
	    STATIC_FUNCTION(outstanding_entity_conses,NIL,FALSE,0,0));
    Qentity_cons_memory_usage = STATIC_SYMBOL("ENTITY-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qentity_cons_memory_usage,
	    STATIC_FUNCTION(entity_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_1 = STATIC_STRING("1q83-Sty9k83-Ssy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_entity_conses);
    push_optimized_constant(Qentity_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_icon_description_g2_struct = 
	    STATIC_SYMBOL("ICON-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icon_description_g2_struct,
	    Qicon_description,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qicon_description,
	    Qg2_defstruct_structure_name_icon_description_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icon_description == UNBOUND)
	The_type_description_of_icon_description = Nil;
    string_constant_2 = 
	    STATIC_STRING("43Dy8m8u1n8u8n8k1l8n0000001m1m83My83-AWy1n8y83-4Fy1u83-Gmy83-*3y83-H8y83-HEy83-*qy83-*uy83-*vy83-*ry83-*Py83-*tykyk0k0");
    temp = The_type_description_of_icon_description;
    The_type_description_of_icon_description = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_2));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icon_description_g2_struct,
	    The_type_description_of_icon_description,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qicon_description,
	    The_type_description_of_icon_description,
	    Qtype_description_of_type);
    Qoutstanding_icon_description_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICON-DESCRIPTION-COUNT",AB_package);
    Qicon_description_structure_memory_usage = 
	    STATIC_SYMBOL("ICON-DESCRIPTION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_3 = STATIC_STRING("1q8u8s83-YPy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icon_description_count);
    push_optimized_constant(Qicon_description_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qchain_of_available_icon_descriptions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICON-DESCRIPTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icon_descriptions,
	    Chain_of_available_icon_descriptions);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_icon_descriptions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qicon_description_count = STATIC_SYMBOL("ICON-DESCRIPTION-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_description_count,Icon_description_count);
    record_system_variable(Qicon_description_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icon_descriptions_vector == UNBOUND)
	Chain_of_available_icon_descriptions_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicon_description_structure_memory_usage,
	    STATIC_FUNCTION(icon_description_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icon_description_count,
	    STATIC_FUNCTION(outstanding_icon_description_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_icon_description_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icon_description,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qicon_description,
	    reclaim_structure_for_icon_description_1);
    Qg2gl_object_icon_substitutions_may_be_in_use_p = 
	    STATIC_SYMBOL("G2GL-OBJECT-ICON-SUBSTITUTIONS-MAY-BE-IN-USE-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2gl_object_icon_substitutions_may_be_in_use_p,
	    G2gl_object_icon_substitutions_may_be_in_use_p);
    record_system_variable(Qg2gl_object_icon_substitutions_may_be_in_use_p,
	    Qicons,T,Qnil,Qnil,Qnil,Qnil);
    if (Icon_renderings_being_bulk_decached == UNBOUND)
	Icon_renderings_being_bulk_decached = Nil;
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    Qvariables = STATIC_SYMBOL("VARIABLES",AB_package);
    Qbackground_layer = STATIC_SYMBOL("BACKGROUND-LAYER",AB_package);
    Qstipple = STATIC_SYMBOL("STIPPLE",AB_package);
    if (Current_icon_substitution_list == UNBOUND)
	Current_icon_substitution_list = Nil;
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    list_constant_12 = STATIC_CONS(Qforeground,Qforeground);
    list_constant = STATIC_CONS(list_constant_12,Qnil);
    list_constant_1 = STATIC_LIST((SI_Long)14L,FIX((SI_Long)4L),
	    FIX((SI_Long)8L),FIX((SI_Long)12L),FIX((SI_Long)16L),
	    FIX((SI_Long)24L),FIX((SI_Long)32L),FIX((SI_Long)56L),
	    FIX((SI_Long)64L),FIX((SI_Long)104L),FIX((SI_Long)128L),
	    FIX((SI_Long)152L),FIX((SI_Long)200L),FIX((SI_Long)256L),
	    FIX((SI_Long)400L));
    list_constant_2 = STATIC_LIST((SI_Long)14L,FIX((SI_Long)18L),
	    FIX((SI_Long)24L),FIX((SI_Long)34L),FIX((SI_Long)48L),
	    FIX((SI_Long)88L),FIX((SI_Long)144L),FIX((SI_Long)408L),
	    FIX((SI_Long)528L),FIX((SI_Long)1368L),FIX((SI_Long)2064L),
	    FIX((SI_Long)2904L),FIX((SI_Long)5016L),FIX((SI_Long)8208L),
	    FIX((SI_Long)20016L));
    Qreflection_and_rotation = STATIC_SYMBOL("REFLECTION-AND-ROTATION",
	    AB_package);
    Qy_magnification = STATIC_SYMBOL("Y-MAGNIFICATION",AB_package);
    Qx_magnification = STATIC_SYMBOL("X-MAGNIFICATION",AB_package);
    Qclockwise_90 = STATIC_SYMBOL("CLOCKWISE-90",AB_package);
    Qreflected_clockwise_90 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-90",
	    AB_package);
    Qclockwise_270 = STATIC_SYMBOL("CLOCKWISE-270",AB_package);
    Qreflected_clockwise_270 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-270",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)4L,Qclockwise_90,
	    Qreflected_clockwise_90,Qclockwise_270,Qreflected_clockwise_270);
    Qx11_pixmap = STATIC_SYMBOL("X11-PIXMAP",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qlines = STATIC_SYMBOL("LINES",AB_package);
    Qoutline = STATIC_SYMBOL("OUTLINE",AB_package);
    Qsolid_rectangle = STATIC_SYMBOL("SOLID-RECTANGLE",AB_package);
    Qcircle = STATIC_SYMBOL("CIRCLE",AB_package);
    Qfilled_circle = STATIC_SYMBOL("FILLED-CIRCLE",AB_package);
    Qrounded_rectangle = STATIC_SYMBOL("ROUNDED-RECTANGLE",AB_package);
    Qfilled_rounded_rectangle = STATIC_SYMBOL("FILLED-ROUNDED-RECTANGLE",
	    AB_package);
    Qpoint = STATIC_SYMBOL("POINT",AB_package);
    Qstippled_area = STATIC_SYMBOL("STIPPLED-AREA",AB_package);
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    Qclockwise_180 = STATIC_SYMBOL("CLOCKWISE-180",AB_package);
    Qreflected = STATIC_SYMBOL("REFLECTED",AB_package);
    Qreflected_clockwise_180 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-180",
	    AB_package);
    Qfilled_polygon = STATIC_SYMBOL("FILLED-POLYGON",AB_package);
    Qimage = STATIC_SYMBOL("IMAGE",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qarc = STATIC_SYMBOL("ARC",AB_package);
    Qreflection_and_rotation_multiplication_table = 
	    STATIC_SYMBOL("REFLECTION-AND-ROTATION-MULTIPLICATION-TABLE",
	    AB_package);
    Reflection_and_rotation_multiplication_table_prop = 
	    Qreflection_and_rotation_multiplication_table;
    list_constant_13 = STATIC_CONS(Qreflected_clockwise_270,Qnil);
    list_constant_14 = STATIC_LIST_STAR((SI_Long)18L,Qnil,Qnormal,Qnormal,
	    Qnormal,Qclockwise_90,Qclockwise_90,Qclockwise_180,
	    Qclockwise_180,Qclockwise_270,Qclockwise_270,Qreflected,
	    Qreflected,Qreflected_clockwise_90,Qreflected_clockwise_90,
	    Qreflected_clockwise_180,Qreflected_clockwise_180,
	    Qreflected_clockwise_270,list_constant_13);
    mutate_global_property(Qnormal,mutate_global_property(Qnil,
	    list_constant_14,
	    Qreflection_and_rotation_multiplication_table),
	    Qreflection_and_rotation_multiplication_table);
    list_constant_15 = STATIC_LIST((SI_Long)18L,Qnil,Qclockwise_90,Qnormal,
	    Qclockwise_90,Qclockwise_90,Qclockwise_180,Qclockwise_180,
	    Qclockwise_270,Qclockwise_270,Qnormal,Qreflected,
	    Qreflected_clockwise_270,Qreflected_clockwise_90,Qreflected,
	    Qreflected_clockwise_180,Qreflected_clockwise_90,
	    Qreflected_clockwise_270,Qreflected_clockwise_180);
    mutate_global_property(Qclockwise_90,list_constant_15,
	    Qreflection_and_rotation_multiplication_table);
    list_constant_16 = STATIC_LIST((SI_Long)18L,Qnil,Qclockwise_180,
	    Qnormal,Qclockwise_180,Qclockwise_90,Qclockwise_270,
	    Qclockwise_180,Qnormal,Qclockwise_270,Qclockwise_90,Qreflected,
	    Qreflected_clockwise_180,Qreflected_clockwise_90,
	    Qreflected_clockwise_270,Qreflected_clockwise_180,Qreflected,
	    Qreflected_clockwise_270,Qreflected_clockwise_90);
    mutate_global_property(Qclockwise_180,list_constant_16,
	    Qreflection_and_rotation_multiplication_table);
    list_constant_17 = STATIC_LIST((SI_Long)18L,Qnil,Qclockwise_270,
	    Qnormal,Qclockwise_270,Qclockwise_90,Qnormal,Qclockwise_180,
	    Qclockwise_90,Qclockwise_270,Qclockwise_180,Qreflected,
	    Qreflected_clockwise_90,Qreflected_clockwise_90,
	    Qreflected_clockwise_180,Qreflected_clockwise_180,
	    Qreflected_clockwise_270,Qreflected_clockwise_270,Qreflected);
    mutate_global_property(Qclockwise_270,list_constant_17,
	    Qreflection_and_rotation_multiplication_table);
    list_constant_18 = STATIC_LIST((SI_Long)18L,Qnil,Qreflected,Qnormal,
	    Qreflected,Qclockwise_90,Qreflected_clockwise_90,
	    Qclockwise_180,Qreflected_clockwise_180,Qclockwise_270,
	    Qreflected_clockwise_270,Qreflected,Qnormal,
	    Qreflected_clockwise_90,Qclockwise_90,Qreflected_clockwise_180,
	    Qclockwise_180,Qreflected_clockwise_270,Qclockwise_270);
    mutate_global_property(Qreflected,list_constant_18,
	    Qreflection_and_rotation_multiplication_table);
    list_constant_19 = STATIC_LIST((SI_Long)18L,Qnil,
	    Qreflected_clockwise_90,Qnormal,Qreflected_clockwise_90,
	    Qclockwise_90,Qreflected_clockwise_180,Qclockwise_180,
	    Qreflected_clockwise_270,Qclockwise_270,Qreflected,Qreflected,
	    Qclockwise_270,Qreflected_clockwise_90,Qnormal,
	    Qreflected_clockwise_180,Qclockwise_90,
	    Qreflected_clockwise_270,Qclockwise_180);
    mutate_global_property(Qreflected_clockwise_90,list_constant_19,
	    Qreflection_and_rotation_multiplication_table);
    list_constant_20 = STATIC_LIST((SI_Long)18L,Qnil,
	    Qreflected_clockwise_180,Qnormal,Qreflected_clockwise_180,
	    Qclockwise_90,Qreflected_clockwise_270,Qclockwise_180,
	    Qreflected,Qclockwise_270,Qreflected_clockwise_90,Qreflected,
	    Qclockwise_180,Qreflected_clockwise_90,Qclockwise_270,
	    Qreflected_clockwise_180,Qnormal,Qreflected_clockwise_270,
	    Qclockwise_90);
    mutate_global_property(Qreflected_clockwise_180,list_constant_20,
	    Qreflection_and_rotation_multiplication_table);
    list_constant_21 = STATIC_LIST((SI_Long)18L,Qnil,
	    Qreflected_clockwise_270,Qnormal,Qreflected_clockwise_270,
	    Qclockwise_90,Qreflected,Qclockwise_180,
	    Qreflected_clockwise_90,Qclockwise_270,
	    Qreflected_clockwise_180,Qreflected,Qclockwise_90,
	    Qreflected_clockwise_90,Qclockwise_180,
	    Qreflected_clockwise_180,Qclockwise_270,
	    Qreflected_clockwise_270,Qnormal);
    mutate_global_property(Qreflected_clockwise_270,list_constant_21,
	    Qreflection_and_rotation_multiplication_table);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    Qimage_info = STATIC_SYMBOL("IMAGE-INFO",AB_package);
    list_constant_4 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    Qaquamarine = STATIC_SYMBOL("AQUAMARINE",AB_package);
    Qlight_gray = STATIC_SYMBOL("LIGHT-GRAY",AB_package);
    Qpending_indicator = STATIC_SYMBOL("PENDING-INDICATOR",AB_package);
    Qextra_light_gray = STATIC_SYMBOL("EXTRA-LIGHT-GRAY",AB_package);
    Qg2_icon_light_shading = STATIC_SYMBOL("G2-ICON-LIGHT-SHADING",AB_package);
    Qdark_gray = STATIC_SYMBOL("DARK-GRAY",AB_package);
    Qg2_icon_dark_shading = STATIC_SYMBOL("G2-ICON-DARK-SHADING",AB_package);
    list_constant_22 = STATIC_CONS(FIX((SI_Long)2L),Qnil);
    list_constant_25 = STATIC_CONS(FIX((SI_Long)2L),list_constant_22);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)3L,Qminus,Qwidth,
	    list_constant_22);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)3L,Qminus,Qheight,
	    list_constant_22);
    list_constant_26 = STATIC_LIST((SI_Long)2L,list_constant_23,
	    list_constant_24);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qsolid_rectangle,
	    list_constant_25,list_constant_26);
    list_constant_8 = STATIC_CONS(FIX((SI_Long)0L),list_constant_4);
    list_constant_36 = STATIC_CONS(Qwidth,list_constant_4);
    list_constant_27 = STATIC_CONS(FIX((SI_Long)3L),Qnil);
    list_constant_28 = STATIC_LIST_STAR((SI_Long)3L,Qminus,Qwidth,
	    list_constant_27);
    list_constant_37 = STATIC_CONS(list_constant_28,list_constant_27);
    list_constant_33 = STATIC_CONS(FIX((SI_Long)3L),list_constant_27);
    list_constant_29 = STATIC_LIST_STAR((SI_Long)3L,Qminus,Qheight,
	    list_constant_27);
    list_constant_30 = STATIC_CONS(list_constant_29,Qnil);
    list_constant_34 = STATIC_CONS(FIX((SI_Long)3L),list_constant_30);
    list_constant_31 = STATIC_CONS(Qheight,Qnil);
    list_constant_32 = STATIC_CONS(FIX((SI_Long)0L),list_constant_31);
    list_constant_35 = STATIC_CONS(list_constant_32,Qnil);
    list_constant_38 = STATIC_LIST_STAR((SI_Long)3L,list_constant_33,
	    list_constant_34,list_constant_35);
    list_constant_39 = STATIC_LIST_STAR((SI_Long)4L,list_constant_8,
	    list_constant_36,list_constant_37,list_constant_38);
    list_constant_40 = STATIC_LIST((SI_Long)3L,list_constant_8,
	    list_constant_36,list_constant_37);
    list_constant_41 = STATIC_LIST((SI_Long)3L,list_constant_8,
	    list_constant_37,list_constant_33);
    list_constant_42 = STATIC_LIST((SI_Long)3L,list_constant_33,
	    list_constant_32,list_constant_8);
    list_constant_6 = STATIC_LIST((SI_Long)6L,Qfilled_polygon,
	    list_constant_39,list_constant_40,list_constant_38,
	    list_constant_41,list_constant_42);
    list_constant_43 = STATIC_CONS(list_constant_28,list_constant_30);
    list_constant_44 = STATIC_CONS(Qwidth,list_constant_31);
    list_constant_45 = STATIC_LIST_STAR((SI_Long)6L,list_constant_34,
	    list_constant_43,list_constant_37,list_constant_36,
	    list_constant_44,list_constant_35);
    list_constant_46 = STATIC_LIST((SI_Long)3L,list_constant_43,
	    list_constant_37,list_constant_36);
    list_constant_47 = STATIC_LIST((SI_Long)3L,list_constant_44,
	    list_constant_34,list_constant_43);
    list_constant_48 = STATIC_LIST((SI_Long)3L,list_constant_43,
	    list_constant_36,list_constant_44);
    list_constant_49 = STATIC_LIST((SI_Long)3L,list_constant_44,
	    list_constant_32,list_constant_34);
    list_constant_7 = STATIC_LIST((SI_Long)6L,Qfilled_polygon,
	    list_constant_45,list_constant_46,list_constant_47,
	    list_constant_48,list_constant_49);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qup = STATIC_SYMBOL("UP",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qdown = STATIC_SYMBOL("DOWN",AB_package);
    list_constant_50 = STATIC_CONS(Qpending_indicator,Qtransparent);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Qpolychrome,
	    list_constant_50,list_constant);
    Qlight_stipple = STATIC_SYMBOL("LIGHT-STIPPLE",AB_package);
    Qmedium_stipple = STATIC_SYMBOL("MEDIUM-STIPPLE",AB_package);
    Qdark_stipple = STATIC_SYMBOL("DARK-STIPPLE",AB_package);
    Qlight_texture = STATIC_SYMBOL("LIGHT-TEXTURE",AB_package);
    Qmedium_texture = STATIC_SYMBOL("MEDIUM-TEXTURE",AB_package);
    Qdark_texture = STATIC_SYMBOL("DARK-TEXTURE",AB_package);
    if (Global_temp_1 == UNBOUND)
	Global_temp_1 = Nil;
    if (Global_temp_2 == UNBOUND)
	Global_temp_2 = Nil;
    if (Global_temp_3 == UNBOUND)
	Global_temp_3 = Nil;
    Qphrase_cons = STATIC_SYMBOL("PHRASE-CONS",AB_package);
}
